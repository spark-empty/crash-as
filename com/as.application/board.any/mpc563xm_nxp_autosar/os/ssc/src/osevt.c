#define OSEVT_C
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
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/src/osevt.c,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* Functions:    
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  OSEK OS event control   
*
* Notes:        
*
******************************************************************************/

#define OS_INTERNAL 1
#include    <os.h>
#undef OS_INTERNAL

#define OSTEXT_START_SEC_CODE
#include "ossections.h"

#if defined(OSECC) && (OSNXTSKS > 0)

#if !defined(OSEXTSTATUS)
#define taskInd taskId
#endif

/*  Private OS Services */

/***************************************************************************
 * Function : OSSetEvent
 *
 * Description: set event and moves Task to Ready state
 *
 * Returns: none / Scheduler State ( Dispatch is necessary or not )
 *
 * Notes:   return >0 if task is transformed to ready state &
 *          dispatch is necessary else 0(OSEVTWAIT)  
 *
 **************************************************************************/

void OSSetEvent(OSTSKCBPTR task, EventMaskType mask)
{
    task->set_event |= (EventMaskType)(mask);

    if( ( task->status & OSTCBWAIT ) != 0 )
    {
        if( ( task->wait_event & task->set_event) != 0 )    /* Any event is occured */
        {
            OSReleaseTask(task->taskId, mask);
        }
    }
    return;
}

/***************************************************************************
 * Function : OSSetEventInAlm
 *
 * Description: set event and moves Task to Ready state 
 *
 * Returns: none / Scheduler State ( Dispatch is necessary or not )
 *
 * Notes:   - return >0 if task is transformed to ready state &
 *            dispatch is necessary else 0(OSEVTWAIT)  
 *          - shall be called only from alarm/sched.tab event action
 *
 **************************************************************************/
#if (OSNTPTSKARRIV > 0) && defined(OSHOOKPROTECTION)
void OSSetEventInAlm(OSTSKCBPTR task, EventMaskType mask)
{
    task->set_event |= (EventMaskType)(mask);

    if( ( task->status & OSTCBWAIT ) != 0 )
    {
        if( ( task->wait_event & task->set_event) != 0 )    /* Any event is occured */
        {
            OSReleaseTaskInAlm(task->taskId, mask);
        }
    }

    return;
}
#endif /* (OSNTPTSKARRIV > 0) && defined(OSHOOKPROTECTION)*/


/*** Public OS Services ***/

/******************************************************************************
 * Function:    SetEvent
 *
 * Description: set event and performs dispatching if nessesary
 *
 * Returns:     E_OK                    no errors
 *              E_OS_ID       (ext.status) the identifier is invalid
 *              E_OS_ACCESS   (ext.status) the task is the basic task (not extended)
 *              E_OS_STATE    (ext.status) the task is in suspended state
 *
 ******************************************************************************/

StatusType OS_SetEvent( TaskType taskId, EventMaskType mask )
{
    OSIMSAVE /* OSINTMASKTYPE save;       */

    OSTSKCB* task_cb;


    OSOrtiSetServiceWatch( OSServiceId_SetEvent ); /* set watch to this service */ 

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_SetEvent, taskId ); 
        }
        else
#endif        
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_SetEvent, taskId ); 
        }
    }
#endif /* OSCHECKCONTEXT */

#if defined(OSEXTSTATUS)
    if( OSTASKIDISINVALID(taskId) ) /* invalid ID */
    {                                           
        OSRETERROR( E_OS_ID, OSServiceId_SetEvent, taskId );
    }
#endif /* OSEXTSTATUS */

    task_cb = &OsTaskTable[OS_GETOBJIND( taskId )];

#if defined(OSEXTSTATUS)
    if( ( task_cb->status & OSTSKEXTENDED ) == 0 ) /* it isn't an extended task */
    {                                           
        OSRETERROR( E_OS_ACCESS, OSServiceId_SetEvent, taskId );
    }
#endif /* OSEXTSTATUS */

    if( ( task_cb->status & OSTCBNOSUSPENDED ) == 0 )
    {
#if defined(OSEXTSTATUS) /* the task is in a suspended state */
        OSRETERROR( E_OS_STATE, OSServiceId_SetEvent, taskId );
#else
        OSOrtiServiceWatchOnExit( OSServiceId_SetEvent );
        return( E_OK );
#endif
    }

    OSCHECKACCESSRIGHTS( OsTaskTable[ task_cb->taskId ].appMask, OSServiceId_SetEvent, taskId );

    OSDIS( save );
    OSOrtiSetOldServiceID( OSServiceId_SetEvent );

    OSSetEvent( task_cb, mask );
    
#if defined(OSFULLPREEMPT) || defined(OSMIXPREEMPT)
    if( ( OsRunning != OSGETMAXPRIOTASK )
#if defined(OSISRENTRYEXIT)
        && ( OsIsrLevel == 0 )
#endif
        )
    {
        OSDISPATCH( );
    }
    /* no call to dispatcher at all if OSNOPREEMPT */
#endif /* defined(OSFULLPREEMPT) || defined(OSMIXPREEMPT) */
    
    OSOrtiResetIdOnExit( );
    OSRI( save );
    return( E_OK );
}

/******************************************************************************
 * Function :   ClearEvent
 *
 * Description:
 *
 * Returns:     E_OK, E_OS_DISABLEDINT, E_OS_CALLEVEL, E_OS_ACCESS
 *
 ******************************************************************************/

StatusType OS_ClearEvent( EventMaskType mask )
{
    OSIMSAVE /* OSINTMASKTYPE save;       */
    OSOrtiSetServiceWatch( OSServiceId_ClearEvent ); /* set watch to this service */ 

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_ClearEvent, 0 ); 
        }
        else
#endif        
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_ClearEvent, 0 ); 
        }
    }
#endif /* OSCHECKCONTEXT */

#if defined(OSEXTSTATUS)
    if( ( OsRunning->status & OSTSKEXTENDED ) == 0 ) /* it isn't an extended task */
    {
        OSRETERROR( E_OS_ACCESS, OSServiceId_ClearEvent, 0 );
    }
#endif

    OSDIS( save );
    OsRunning->set_event &= (EventMaskType)(~mask);
    OSRI( save );

    OSOrtiServiceWatchOnExit( OSServiceId_ClearEvent );
    return( E_OK );
}

/******************************************************************************
 * Function : WaitEvent
 *
 * Description: wait event; performs dispatching if nessesary
 *
 * Returns: E_OK                    no errors
 *          E_OS_CALLEVEL (ext.status) call at interrupt level
 *          E_OS_ACCESS   (ext.status) the task is the basic task (not extended)
 *          E_OS_RESOURCE (ext.status) the task occupies the resources
 *
 ******************************************************************************/

StatusType OS_WaitEvent( EventMaskType mask )
{
    OSIMSAVE               /* OSINTMASKTYPE save;       */    
    OSOrtiSetServiceWatch( OSServiceId_WaitEvent ); /* set watch to this service */ 

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_WaitEvent, 0 ); 
        }
        else
#endif        
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_WaitEvent, 0 ); 
        }
    }
#endif /* OSCHECKCONTEXT */

#if defined(OSEXTSTATUS)
    if( ( OsRunning->status  & OSTSKEXTENDED ) == 0 ) /* it isn't an extended task */
    {                                           
        OSRETERROR( E_OS_ACCESS, OSServiceId_WaitEvent, 0 );
    }
#if defined(OSRESOURCE)
    if( OsRunning->resources != 0 )                   /* resource is occupied */
    {
        OSRETERROR( E_OS_RESOURCE, OSServiceId_WaitEvent, 0 );
    }
#endif
#endif /* OSEXTSTATUS */

    OSDI( ); /* It is not necessary to save./restore int.mask  because    */
             /* this service shall be called with enabled interrupts only */
    OSOrtiSetOldServiceID( OSServiceId_WaitEvent );

    OSTPSetWAITEVT();

    if( ( ( OsRunning->wait_event = mask ) & OsRunning->set_event ) == 0 )
    {
        OSResetInternalPrio2( );
        OSRUNNINGSTATUS |= OSTCBWAIT;      /* set Task's to waiting state */
        OSREMOVETASK(OsRunning);
        OSTaskForceDispatch( );            /* force dispatcher */
    }
#if defined(OSTIMINGPROTECTION) && ( (OSNTPTSKBGTS > 0) || (OSNTPTSKARRIV > 0) )
    else
    {
#if defined(OSHOOKPROTECTION) && (OSNTPTSKARRIV > 0)
        if( OSTPStartTaskFrame( OsRunning->taskId ) )
#else
        OSTPStartTaskFrame( OsRunning->taskId );
#endif
        {
            OSTPRestartTaskBudget();
        }
#if defined(OSHOOKPROTECTION) && (OSNTPTSKARRIV > 0)
        else    /* there is task arrival rate violation */
        {
            if( OsTPHookAction == PRO_IGNORE ) 
            {
                OsRunning->set_event &= (EventMaskType)~mask;

                OSResetInternalPrio2( );
                OSRUNNINGSTATUS |= OSTCBWAIT;      /* set Task's to waiting state */
                OSREMOVETASK(OsRunning);
                OSTaskForceDispatch( );            /* force dispatcher */
            }
            else 
            {
                OSShutdownOS( E_OS_PROTECTION_ARRIVAL );  /* violator is unknown here */
            }
        }
#endif
    }
#endif /* defined(OSTIMINGPROTECTION) && ( (OSNTPTSKBGTS > 0) || (OSNTPTSKARRIV > 0) ) */
    OSTPClrWAITEVT();
    OSOrtiResetIdOnExit( );
    OSEI( ); 
    return( E_OK );
}

/******************************************************************************
 * Function:    GetEvent
 *
 * Description:
 *
 * Returns:     Status E_OK
 *
 * Notes:       without critical section 
 *
 ******************************************************************************/

StatusType OS_GetEvent( TaskType taskId, EventMaskRefType maskRef )
{
#if defined(OSEXTSTATUS)
    OSWORD  taskInd;              /* index in Tasks tables */
#endif

    OSOrtiSetServiceWatch( OSServiceId_GetEvent );       /* set watch to this service */ 

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK |
                         OSISRLEVELHOOKERROR | OSISRLEVELHOOKAPPERROR | OSISRLEVELHOOKTASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_GetEvent, taskId );
        }
        else
#endif        
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_GetEvent, taskId ); 
        }
    }
#endif /* OSCHECKCONTEXT */

#if defined(OSEXTSTATUS)
    taskInd = (OSWORD)OS_GETOBJIND(taskId);

    if( OSTASKIDISINVALID(taskId) )                           /* invalid ID */
    {                                          
        OSRETERROR( E_OS_ID, OSServiceId_GetEvent, taskId ); 
    }
    if( ( OSTASKSTATUS( taskInd )  & OSTSKEXTENDED ) == 0 )   /* it isn't an extended task */
    {                                          
        OSRETERROR( E_OS_ACCESS, OSServiceId_GetEvent, taskId );
    }
    if( ( OSTASKSTATUS( taskInd ) & OSTCBNOSUSPENDED ) == 0 ) /* the task is in a suspended state */
    {                                          
        OSRETERROR( E_OS_STATE, OSServiceId_GetEvent, taskId );              
    }
#endif

    OSCHECKACCESSRIGHTS( OsTaskTable[ taskInd ].appMask, OSServiceId_GetEvent, taskId );
    OSCHECKWRITEACCESS2( maskRef, sizeof(EventMaskType), OSServiceId_GetEvent, taskId );

    *maskRef = OsTaskTable[taskInd].set_event;

    OSOrtiServiceWatchOnExit( OSServiceId_GetEvent );
    return( E_OK );
}

#endif  /* defined(OSECC)  && (OSNXTSKS > 0)   */
