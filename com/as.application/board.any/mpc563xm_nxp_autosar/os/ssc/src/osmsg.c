#define OSMSG_C
/******************************************************************************
*
*   Freescale(TM) and the Freescale logo are trademarks of Freescale Semiconductor, Inc. 
*   All other product or service names are the property of their respective owners. 
*   (C) Freescale Semiconductor, Inc. 2006-2010
*
*   THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
*   BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
*   Freescale Semiconductor, Inc.
*
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/src/osmsg.c,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* Functions:    OSMsgInit, GetMessageStatus, SendMessage, ReceiveMessage, 
*               OSSignalMessage, StartCOM, OSReadFlag, OSResetFlag, StopCOM,
*               InitMessage
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  OSEK OS message management      
*
******************************************************************************/

#define OS_INTERNAL 1
#include    <os.h>
#undef OS_INTERNAL

#define OSTEXT_START_SEC_CODE
#include "ossections.h"

            
#if !defined(OSPROPH)   
#include    "osprop.h"                          /* OS Properties */
#else   /* !defined(OSPROPH)    */
#include    OSPROPH                             /* OS Properties */
#endif  /* !defined(OSPROPH)    */

#if OSNMSGS > 0

#include    <string.h>                          /* memcpy()    */

/**** OS internal macros for local messages ****/

#if !defined(OSCOMEXTSTATUS)
#define mInd Msg
#endif
#define OSOBJISMSG      (OS_GETOBJTYP(Msg) == OBJECT_MESSAGE)

#define OSMB(m)                 OsMessages[m]
#define OSMSGNEXT(msg)          (msg).nextMsg 

#if defined(OSAPPLICATION)
#define OSMSGAPPMASK(msg)       (msg).appMask
#define OSMSGAPPID(msg)         (msg).appId
#endif

#define OSMSGPTR(msg)           (msg).msgPtr 
#define OSMSGSIZE(msg)          (msg).msgSize
#define OSMSGSIGTASK(msg)       (msg).msgSigTask  
#define OSMSGSIGEVENT(msg)      (msg).msgSigEvent  
#define OSMSGSIGCALLBACK(msg)   (msg).msgSigCallBack  
#if OSNQUEMSGS > 0
#define OSMSGINITVALUE(msgID)   OsMsg[msgID].fifoLast 
#else
#define OSMSGINITVALUE(msgID)   OsMsg[msgID].initValue  
#endif

#define OSMSGSTATUS(msg)        (msg).msgStatus 
#define OSMSGFLAG(msg)          (msg).msgFlag 

#if OSNQUEMSGS > 0

#define OSMSGISQUEUED(msg)      ((msg).fifoLength != 0)
#define OSFIFOFIRST(msg)        (msg).msgPtr 
#define OSFIFOLAST(msg)         (msg).fifoLast  
#define OSFIFOLENGTH(msg)       (msg).fifoLength

#define OSFIFOWRITE(msg)        (msg).fifoWrite
#define OSFIFOREAD(msg)         (msg).fifoRead  
#define OSFIFOCNT(msg)          (msg).fifoCnt  

#endif  /* OSNQUEMSGS > 0 */

#if defined(OSCOMHOOKERROR)
void COMErrorHook( StatusType error );
/***************************************************************************
 * Macro:       OSCOMErrorHook
 *
 * Description: calls user defined hook if not nested
 *
 * Notes:       nesting level is shared with OSErrorHook
 *
 **************************************************************************/
#if defined(OSCOMGETSERVICEID)
#define OSCOMErrorHook( error, ID, param ) \
    if( ( OsIsrLevel & OSISRLEVELHOOKCOM ) == 0 )             /* if not nested call */ \
    { \
        OSDIS(save); \
        OsIsrLevel |= OSISRLEVELHOOKCOM;                      /* set special ISR level to avoid nested hooks */ \
        OsComService = ID; \
        OsComObjId = (OSDWORD)param; \
        OSOrtiSetServiceWatch( OSServiceId_COMErrorHook );    /* set watch to this service */ \
        COMErrorHook( error ); \
        OSOrtiServiceWatchOnExit( OSServiceId_COMErrorHook ); /* clean service watch on hook leaving */ \
        OsIsrLevel &= (OSISRLEVELTYPE)(~OSISRLEVELHOOKCOM);   /* reset special ISR level */ \
        OSRI(save); \
    }
#else /* defined(OSCOMGETSERVICEID) */

#define OSCOMErrorHook( error, ID, param ) \
    if( ( OsIsrLevel & OSISRLEVELHOOKCOM ) == 0 )             /* if not nested call */ \
    { \
        OSDIS(save); \
        OsIsrLevel |= OSISRLEVELHOOKCOM;                      /* set special ISR level to avoid nested hooks */ \
        OSOrtiSetServiceWatch( OSServiceId_COMErrorHook );    /* set watch to this service */ \
        COMErrorHook( error ); \
        OSOrtiServiceWatchOnExit( OSServiceId_COMErrorHook ); /* clean service watch on hook leaving */ \
        OsIsrLevel &= (OSISRLEVELTYPE)(~OSISRLEVELHOOKCOM);   /* reset special ISR level */ \
        OSRI(save); \
    }
#endif /* defined(OSCOMGETSERVICEID) */

#define OSCOMRETERROR( error, ID, param )  \
        OSPUTERROR( error ); \
        OSCOMErrorHook( error, ID, param ); \
        OSOrtiServiceWatchOnExit( ID ); \
        return( error )
#else
#define OSCOMRETERROR( error, ID, param ) \
        OSPUTERROR( error ); \
        OSOrtiServiceWatchOnExit( ID ); \
        return( error )
#endif  /* defined(OSCOMHOOKERROR) */

/* Local functions prototypes */

#if defined(OSSIGNAL)
                                                /* internal: generate signal on message arrivance */
static void  OSSignalMessage( OSMSGCBtype* pmsg );

#endif  /* defined(OSSIGNAL) */

/* Functions */

/***************************************************************************
 * Function:    OSMsgInit
 *
 * Description: initializes OS messages data 
 *
 * Returns:     
 *
 **************************************************************************/

void  OSMsgInit( void )
{
    OSBYTE i;
    OSBYTE* mptr;

    for( i = 0; i < OSNSNDMSGS; i++ )
    {
        mptr = (OSBYTE*)OsSndPtr[i];
        if( *mptr == OSMSGINVALID )     /* sending message w/o receivers */
        {
            OsRcvPtr[i] = (OSMSGCBtype*)0;
            continue;
        }
        OsRcvPtr[i] = &(OSMB(*mptr));
        for(;;)
        {
            if( *(mptr+1) == OSMSGINVALID )
            {
                OSMSGNEXT(OSMB(*mptr)) = (OSMSGCBtype*)0;
                break;
            }
            OSMSGNEXT(OSMB(*mptr)) = &(OSMB(*(mptr+1)));
            mptr++;
        }
#if defined(OSAPPLICATION)
       OsSndMessages[i].appMask = OsSndMsg[i].appMask;
       OsSndMessages[i].appId   = OsSndMsg[i].appId;
#endif
    }

    for( i = 0; i < OSNRCVMSGS; i++ )
    {
#if defined(OSAPPLICATION)
        OSMSGAPPMASK(OSMB(i))   = OsMsg[i].appMask;
        OSMSGAPPID(OSMB(i))     = OsMsg[i].appId;
#endif
        OSMSGPTR(OSMB(i))       = OsMsg[i].msgPtr;      /* pointer to message body or to start of Queue */
        OSMSGSIZE(OSMB(i))      = OsMsg[i].msgSize;
#if defined(OSSIGACTIVTASK) || defined(OSSIGEVENT)
        OSMSGSIGTASK(OSMB(i))   = OsMsg[i].msgSigTask;      /* Task to be signaled  */
#endif  /* defined(OSSIGACTIVTASK) || defined(OSSIGEVENT) */
#if defined(OSSIGEVENT)
        OSMSGSIGEVENT(OSMB(i))  = OsMsg[i].msgSigEvent;     /* Event to be set      */
#endif  /* defined(OSSIGEVENT) */
#if defined(OSSIGCALLBACK)
        OSMSGSIGCALLBACK(OSMB(i)) = OsMsg[i].msgSigCallBack; /* message callback    */
#endif  /* defined(OSSIGCALLBACK) */
#if defined(OSSIGFLAG)
        OSMSGFLAG(OSMB(i))      = OsMsg[i].msgSigFlag;      /* Flag to be set       */
#endif  /* defined(OSSIGFLAG) */

#if OSNQUEMSGS > 0
            OSFIFOLAST(OSMB(i)) = OsMsg[i].fifoLast;
            OSFIFOLENGTH(OSMB(i)) = OsMsg[i].fifoLength;
#if OSNRCVMSGS != OSNQUEMSGS
        if( OSMSGISQUEUED(OSMB(i)) )
#endif
        {
            OSFIFOWRITE(OSMB(i)) = (OSBYTEPTR)OsMsg[i].msgPtr;
            OSFIFOREAD(OSMB(i)) = (OSBYTEPTR)OsMsg[i].msgPtr;
            OSFIFOCNT(OSMB(i)) = 0;
            OSMSGSTATUS(OSMB(i)) = 0;
            continue;
        }
#endif /* OSNQUEMSGS > 0 */
        /* no `else' here because of `continue' above   */
#if OSNRCVMSGS != OSNQUEMSGS
        /* clear message object content */
        memset((void*)OSMSGPTR(OSMB(i)), 0, OSMSGSIZE(OSMB(i)));    /* clear message content  */

#endif /* OSNRCVMSGS != OSNQUEMSGS */
    }

#if OSNRCVMSGS != OSNQUEMSGS
    for( i = 0; i < OSNRCVMSGS; i++ )
    {
#if OSNQUEMSGS > 0
        if( !OSMSGISQUEUED(OSMB(i)) )
        {
            if( OSMSGINITVALUE(i) )
            {   /* if there are pointer to initial value then copy data from it */
                memcpy((void*)OSMSGPTR(OSMB(i)), OSMSGINITVALUE(i), OSMSGSIZE(OSMB(i)));
            }
        }
#else /* OSNQUEMSGS > 0 */
        if( OSMSGINITVALUE(i) )
        {   /* if there are pointer to initial value then copy data from it */
            memcpy((void*)OSMSGPTR(OSMB(i)), OSMSGINITVALUE(i), OSMSGSIZE(OSMB(i)));
        }
#endif /* OSNQUEMSGS > 0 */
    }
#endif /* OSNRCVMSGS != OSNQUEMSGS */

}

/******************************************************************************
 * Function:    GetMessageStatus
 *
 * Description: returns status of queued message 
 *
 * Returns:     message status
 *
 ******************************************************************************/

StatusType OS_GetMessageStatus( MessageIdentifier Msg )
{
    OSIMSAVE                                /* OSINTMASKTYPE save;  */
#if defined(OSCOMEXTSTATUS)
    OSWORD  mInd;                /* index in Messages tables */
#endif
    OSOrtiSetServiceWatch( COMServiceId_GetMessageStatus );

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSCOMEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, COMServiceId_GetMessageStatus, Msg );
        }
        else
#endif        
        {
            OSRETERROR( E_OS_CALLEVEL, COMServiceId_GetMessageStatus, Msg ); 
        }
    }
#endif /* defined(OSCHECKCONTEXT) */

#if defined(OSCOMEXTSTATUS)

    mInd = (OSWORD)OS_GETOBJIND(Msg);
                                            /* Check message ID value   */
#if OSNQUEMSGS != 0
    if( (!OSOBJISMSG) || (mInd >= OSNRCVMSGS) || ( !OSMSGISQUEUED(OSMB(mInd)) ) )
#endif
    {
        OSCOMRETERROR( E_COM_ID, COMServiceId_GetMessageStatus, Msg );              
    }
#endif  /* defined(OSCOMEXTSTATUS) */

    OSCHECKACCESSRIGHTS( OsMessages[mInd].appMask, COMServiceId_GetMessageStatus, Msg );

#if OSNQUEMSGS != 0
#if OSNQUEMSGS != OSNRCVMSGS
    if( OSMSGISQUEUED(OSMB(mInd)) )
#endif
    {
        if( OSFIFOCNT(OSMB(mInd)) == 0 )
        {
            OSCOMRETERROR( E_COM_NOMSG, COMServiceId_GetMessageStatus, Msg );              
        }                                       
        if( (OSMSGSTATUS(OSMB(mInd)) & OSMSGOVERFLOW) != 0 )
        {
            OSCOMRETERROR( E_COM_LIMIT, COMServiceId_GetMessageStatus, Msg );              
        }                                       
    }
#endif /* OSNQUEMSGS != 0 */

#if (OSNQUEMSGS != 0) || !defined(OSCOMEXTSTATUS)
    OSOrtiServiceWatchOnExit( COMServiceId_GetMessageStatus );
    return E_OK;
#endif
}

/******************************************************************************
 * Function:    SendMessage
 *
 * Description: Send message
 *
 * Returns:     E_OK            no errors
 *              E_COM_ID        invalid message identifier
 *
 ******************************************************************************/

StatusType OS_SendMessage(MessageIdentifier Msg, ApplicationDataRef DataRef)
{
    OSIMSAVE                                /* OSINTMASKTYPE save;  */
    OSMSGCBtype* p_msg;                     /* pointer to current receiver  */
#if defined(OSCOMEXTSTATUS)
    OSWORD  mInd;                           /* index in Messages tables */
#endif

    OSOrtiSetServiceWatch( COMServiceId_SendMessage );

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSCOMEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, COMServiceId_SendMessage, Msg );
        }
        else
#endif        
        {
            OSRETERROR( E_OS_CALLEVEL, COMServiceId_SendMessage, Msg ); 
        }
    }
#endif /* defined(OSCHECKCONTEXT) */

#if defined(OSCOMEXTSTATUS)

    mInd = (OSWORD)OS_GETOBJIND(Msg);
                                            /* Check message ID value   */
    if( (!OSOBJISMSG) || (mInd >= OSNMSGS) || (mInd < OSNRCVMSGS) )
    {
        OSCOMRETERROR( E_COM_ID, COMServiceId_SendMessage, Msg );
    }
#endif  /* defined(OSCOMEXTSTATUS) */

    OSCHECKACCESSRIGHTS( OsSndMessages[mInd-OSNRCVMSGS].appMask, COMServiceId_SendMessage, Msg );
    p_msg = OsRcvPtr[mInd-OSNRCVMSGS];
    OSCHECKWRITEACCESS( DataRef, OSMSGSIZE(*p_msg), COMServiceId_SendMessage, Msg );

    OSDIS( save );

#if OSNQUEMSGS != 0
    while( p_msg )
    {
#if OSNQUEMSGS != OSNRCVMSGS             
        if( !OSMSGISQUEUED(*p_msg) )
        {
            memcpy( (void*)OSMSGPTR(*p_msg), DataRef, OSMSGSIZE(*p_msg) );
            break;                              /* all non-queued receivers share one message data  */
        }
#endif /* OSNQUEMSGS != OSNRCVMSGS */

#if OSNQUEMSGS != OSNRCVMSGS
        else
#endif
        {
            if( OSFIFOCNT(*p_msg) == OSFIFOLENGTH(*p_msg) )
            {
                OSMSGSTATUS(*p_msg) |= OSMSGOVERFLOW;  /* set overflow status for receiver */
            }                                   /* do not put item into FIFO, simply reject it */
            else
            {                                   /* put message item into the queue */
                memcpy( (void*)OSFIFOWRITE(*p_msg), DataRef, OSMSGSIZE(*p_msg) );
                                                /* advance the write pointer */
                if( OSFIFOWRITE(*p_msg) == OSFIFOLAST(*p_msg) )
                {                               /* end of queue reached */
                    OSFIFOWRITE(*p_msg) = (OSBYTEPTR)OSFIFOFIRST(*p_msg);
                }
                else
                {
                    OSFIFOWRITE(*p_msg) += OSMSGSIZE(*p_msg);
                }

                OSFIFOCNT(*p_msg)++;
            }
        }
        p_msg = OSMSGNEXT(*p_msg);              /* get next receiving message           */
    }
#else  /* OSNQUEMSGS != 0 */
                                        /* all unqueued messages shares one data object */
    if( p_msg )                         /* check that there is a receiving message      */
    {
        memcpy( (void*)OSMSGPTR(*p_msg), DataRef, OSMSGSIZE(*p_msg) );
    }
#endif /* OSNQUEMSGS != 0 */

#if defined(OSSIGNAL)

    OSPUTPARAM( COMServiceId_SendMessage, Msg );

    p_msg = OsRcvPtr[mInd-OSNRCVMSGS];
    while( p_msg )
    {                                           /* send signal for receive messages     */
        OSSignalMessage( p_msg );               /* generate signal on message arrival   */
        p_msg = OSMSGNEXT(*p_msg);              /* get next receiving message           */
    }
    OSCLEARPARAM();
    OSOrtiSetOldServiceID( COMServiceId_SendMessage );

#if defined(OSSIGACTIVTASK) || defined(OSSIGEVENT)


    if( ( OSGETMAXPRIOTASK != OsRunning )       /* if task of higher prio was moved to READY   */
#if defined(OSISRENTRYEXIT)
        && ( OsIsrLevel == 0 )                  /* and it is the task-level call: call dispatcher */
#endif  /* defined(OSISRENTRYEXIT) */
    )
    {
        OSDISPATCH();
    }

#endif /* defined(OSSIGACTIVTASK) || defined(OSSIGEVENT) */
    OSOrtiResetIdOnExit();

#else   /* defined(OSSIGNAL) */

    OSOrtiServiceWatchOnExit( COMServiceId_SendMessage );

#endif  /* defined(OSSIGNAL) */

    OSRI( save );
    return E_OK;
}


/******************************************************************************
 * Function:    ReceiveMessage
 *
 * Description: Receive message
 *
 * Returns:     E_OK            no errors
 *              E_COM_ID        invalid message identifier
 *
 ******************************************************************************/

StatusType OS_ReceiveMessage(MessageIdentifier Msg, ApplicationDataRef DataRef)
{
    OSMSGCBtype* p_msg;                     /* pointer to the receiving message     */
    OSIMSAVE                                /* OSINTMASKTYPE save;  */
#if defined(OSCOMEXTSTATUS)
    OSWORD  mInd;                           /* index in Messages tables */
#endif
#if OSNQUEMSGS > 0
    StatusType  status = E_OK;              /* status of operation - OK by default  */
#endif

    OSOrtiSetServiceWatch( COMServiceId_ReceiveMessage );

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSCOMEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, COMServiceId_ReceiveMessage, Msg );
        }
        else
#endif        
        {
            OSRETERROR( E_OS_CALLEVEL, COMServiceId_ReceiveMessage, Msg ); 
        }
    }
#endif /* defined(OSCHECKCONTEXT) */

#if defined(OSCOMEXTSTATUS)

    mInd = (OSWORD)OS_GETOBJIND(Msg);
                                            /* Check message ID value   */
    if( (!OSOBJISMSG) || (mInd >= OSNRCVMSGS) )
    {
        OSCOMRETERROR( E_COM_ID, COMServiceId_ReceiveMessage, Msg );
    }
                                            /* check correctness of call at ISR level */
#endif  /* defined(OSCOMEXTSTATUS) */

    OSCHECKACCESSRIGHTS( OsMessages[mInd].appMask, COMServiceId_ReceiveMessage, Msg );
    p_msg = &OSMB(mInd);
    OSCHECKWRITEACCESS( DataRef, OSMSGSIZE(*p_msg), COMServiceId_ReceiveMessage, Msg );
    
    OSDIS( save );

#if OSNQUEMSGS != OSNRCVMSGS 
#if OSNQUEMSGS != 0
    if( !OSMSGISQUEUED(*p_msg) )
#endif
    {
        memcpy( DataRef, (void*)OSMSGPTR(*p_msg), OSMSGSIZE(*p_msg) );
    }
#endif /* OSNQUEMSGS != OSNRCVMSGS */

#if OSNQUEMSGS != 0
#if OSNQUEMSGS != OSNRCVMSGS             
    else
#endif
    {
        if( OSFIFOCNT(*p_msg) == 0 )
        {
            OSRI( save );
            OSCOMRETERROR( E_COM_NOMSG, COMServiceId_ReceiveMessage, Msg );
        }

        if( (OSMSGSTATUS(*p_msg) & OSMSGOVERFLOW) != 0 )
        {
            status = E_COM_LIMIT;
            OSMSGSTATUS(*p_msg) &= (OSBYTE)~OSMSGOVERFLOW; /* clear overflow status for receiver */
        }
                                                /* copy message item from the queue */
        memcpy( DataRef, (void*)OSFIFOREAD(*p_msg), OSMSGSIZE(*p_msg) );
                                                /* advance the write pointer */
        if( OSFIFOREAD(*p_msg) == OSFIFOLAST(*p_msg) )
        {                                       /* end of queue reached */
            OSFIFOREAD(*p_msg) = (OSBYTEPTR)OSFIFOFIRST(*p_msg);
        }
        else
        {
            OSFIFOREAD(*p_msg) += OSMSGSIZE(*p_msg);
        }

        OSFIFOCNT(*p_msg)--;
    }
#endif /* OSNQUEMSGS != 0 */

    OSRI( save );

#if OSNQUEMSGS > 0
    if( status != E_OK )
    {
            OSCOMRETERROR( status, COMServiceId_ReceiveMessage, Msg );
    }
#endif
    OSOrtiServiceWatchOnExit( COMServiceId_ReceiveMessage );
    return  E_OK;
}

#if defined(OSSIGNAL)
/***************************************************************************
 * Function:    OSSignalMessage
 *
 * Description: Perform notification on message receiving
 *
 * Notes:       calls OS (not COM) ErrorHook in case of OS error conditions
 *
 **************************************************************************/

static void  OSSignalMessage( OSMSGCBtype* msg )
{

#if defined(OSSIGFLAG)
    if( OSMSGFLAG(*msg) != OSNOFLAG )
    {
        OSMSGFLAG(*msg) = COM_TRUE;
        return;
    }
#endif  /* defined(OSSIGFLAG) */

#if defined(OSSIGCALLBACK)
    if( OSMSGSIGCALLBACK(*msg) )
    {
        (OSMSGSIGCALLBACK(*msg))();             /* call callback function   */
        return;
    }
#endif  /* defined(OSSIGCALLBACK) */

#if defined(OSSIGEVENT)
    if( OSMSGSIGEVENT(*msg) )
    {                                       /* event setting is defined - set event */
        if( OSISTASKNOSUSPEND(OSMSGSIGTASK(*msg)) )
        {
            OSSetEvent( OsTaskTable + OSMSGSIGTASK(*msg), OSMSGSIGEVENT(*msg) );
        }
#if defined(OSHOOKERROR)
        else
        {
            OSErrorHook_noPar( E_OS_STATE );
        }
#endif
    }
#if defined(OSSIGACTIVTASK)
    else
#endif  /* defined(OSSIGACTIVTASK) */
#endif  /* defined(OSSIGEVENT) */
#if defined(OSSIGACTIVTASK)
    {                                       /* no events are defined - activate the task */

        if( OSMSGSIGTASK(*msg) == OSNULLTASK ) 
        {
            return;
        }
                                               
        if( OSISTASKNOSUSPEND(OSMSGSIGTASK(*msg)))
        {
#if defined(OSHOOKERROR)
            OSErrorHook_noPar( E_OS_LIMIT );
#endif
            return;
        }

#if defined(OSECC1) 
#if (OSNXTSKS > 0)
        OsTaskTable[OSMSGSIGTASK(*msg)].set_event = OSNOEVENTS;
#endif
#endif
        OSActivateTask( OSMSGSIGTASK(*msg) );
    }
#endif  /* defined(OSSIGACTIVTASK) */

    return;   
}

#endif  /* defined(OSSIGNAL) */



/******************************************************************************
 * Function:    StartCOM
 *
 * Description: start COM
 *
 * Returns: 
 *
 ******************************************************************************/
StatusType OS_StartCOM( COMApplicationModeType Mode )
{
    OSIMSAVE                                /* OSINTMASKTYPE save;  */
#if defined(OSCOMHOOKSTARTUP) 
    StatusType osRetVal;
#endif

    OSOrtiSetServiceWatch( COMServiceId_StartCOM );

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSCOMEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, COMServiceId_StartCOM, Mode );
        }
        else
#endif        
        {
            OSRETERROR( E_OS_CALLEVEL, COMServiceId_StartCOM, Mode ); 
        }
    }
#endif /* defined(OSCHECKCONTEXT) */

#if defined(OSCOMEXTSTATUS)
    if( Mode >= OSCOMNMODES )
    {
        OSCOMRETERROR( E_COM_ID, COMServiceId_StartCOM, Mode );
    }
#endif

    OSDIS( save );
    OsCOMmode = Mode;
    OSMsgInit();
#if defined(OSCOMHOOKSTARTUP) 
    osRetVal = StartCOMExtension();        /* user extention   */
#endif
    OSOrtiServiceWatchOnExit( COMServiceId_StartCOM );
    OSRI( save );

#if defined(OSCOMHOOKSTARTUP) 
    return osRetVal;
#else
    return( E_OK );
#endif
}

#if defined(OSORTICURRENTSERVICEID)
#if OSNFLAGS > 0

/***************************************************************************
 * Function:    OSReadFlag
 *
 * Description: Read flag
 *
 * Returns:     flag value
 *
 * Notes::      no check for parametr validity
 *
 **************************************************************************/
FlagValue  OSReadFlag( FlagType flag )
{
    FlagValue retValue;

    OSOrtiSetServiceWatch( COMServiceId_ReadFlag );

    retValue = ((*flag == COM_TRUE) ? COM_TRUE : COM_FALSE );

    OSOrtiServiceWatchOnExit( COMServiceId_ReadFlag );
    return retValue;
}

/***************************************************************************
 * Function:    OSResetFlag
 *
 * Description: Reset flag
 *
 * Notes::      no check for parametr validity
 *
 **************************************************************************/
void  OSResetFlag( FlagType flag )
{
    OSOrtiSetServiceWatch( COMServiceId_ResetFlag );
    *flag = COM_FALSE;
    OSOrtiServiceWatchOnExit( COMServiceId_ResetFlag );
}
#endif /* OSNFLAGS > 0 */

#endif  /* defined(OSORTICURRENTSERVICEID) */

/******************************************************************************
 * Function:    StopCOM
 *
 * Description: only check input parameter
 *
 * Returns:     E_OK, no error
 *              E_COM_ID   wrong mode
 *
 ******************************************************************************/

StatusType OS_StopCOM(COMShutdownModeType Mode)
{
    OSIMSAVE                                         /* OSINTMASKTYPE save; used in OSCOMRETERROR */
    OSOrtiSetServiceWatch( COMServiceId_StopCOM );   /* set watch to this service */ 

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSCOMEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, COMServiceId_StopCOM, Mode );
        }
        else
#endif        
        {
            OSRETERROR( E_OS_CALLEVEL, COMServiceId_StopCOM, Mode ); 
        }
    }
#endif /* defined(OSCHECKCONTEXT) */

#if defined(OSCOMEXTSTATUS)
    if( Mode != COM_SHUTDOWN_IMMEDIATE )
    {
        OSCOMRETERROR( E_COM_ID, COMServiceId_StopCOM, Mode );
    }
#endif

    OSOrtiServiceWatchOnExit( COMServiceId_StopCOM );
    return( E_OK );
}

/******************************************************************************
 * Function:    InitMessage
 *
 * Description: set message value or initialize queue
 *
 * Returns:     E_OK, no error
 *              E_COM_ID   wrong nessage
 *
 ******************************************************************************/

StatusType OS_InitMessage (MessageIdentifier Msg, ApplicationDataRef DataRef)
{
    OSIMSAVE                                /* OSINTMASKTYPE save;  */
#if defined(OSCOMEXTSTATUS)
    OSWORD  mInd;                           /* index in Messages tables */
#endif

    OSOrtiSetServiceWatch( COMServiceId_InitMessage );   /* set watch to this service */ 

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSCOMEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, COMServiceId_InitMessage, Msg );
        }
        else
#endif        
        {
            OSRETERROR( E_OS_CALLEVEL, COMServiceId_InitMessage, Msg ); 
        }
    }
#endif /* defined(OSCHECKCONTEXT) */

#if defined(OSCOMEXTSTATUS)
    mInd = (OSWORD)OS_GETOBJIND(Msg);
                                            /* Check message ID value   */
    if( (!OSOBJISMSG) || (mInd >= OSNRCVMSGS) )
    {
        OSCOMRETERROR( E_COM_ID, COMServiceId_InitMessage, Msg );
    }
#endif

    OSCHECKACCESSRIGHTS( OsMessages[mInd].appMask, COMServiceId_InitMessage, Msg );
    OSCHECKWRITEACCESS( DataRef, OSMSGSIZE(OSMB(mInd)), COMServiceId_InitMessage, Msg );

    OSDIS( save );

#if OSNQUEMSGS != 0
#if OSNQUEMSGS != OSNRCVMSGS
    if( OSMSGISQUEUED(OSMB(mInd)) )
#endif
    {
        OSMSGSTATUS(OSMB(mInd)) = 0;
        OSFIFOWRITE(OSMB(mInd)) = OSFIFOREAD(OSMB(mInd)) = (OSBYTEPTR)OSFIFOFIRST(OSMB(mInd));
        OSFIFOCNT(OSMB(mInd)) = 0;
    }
#endif /* OSNQUEMSGS != 0 */
#if OSNQUEMSGS != OSNRCVMSGS
#if OSNQUEMSGS != 0
    else
#endif
    {
        memcpy((void*)OSMSGPTR(OSMB(mInd)), DataRef, OSMSGSIZE(OSMB(mInd)));
    }
#endif
    OSOrtiServiceWatchOnExit( COMServiceId_InitMessage );
    OSRI( save );
    return( E_OK );
}

#endif  /* OSNMSGS > 0 */

