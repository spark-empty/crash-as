#define OSSCT_C
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
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/src/ossct.c,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* Functions:    
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  Function code to support AUTOSAR OS Schedule Tables
*
* Notes:        
*
******************************************************************************/

#define OS_INTERNAL 1
#include    <os.h>
#undef OS_INTERNAL


#if defined(OSSCHEDULETABLES)

#if !defined(OSEXTSTATUS)
#define sctInd sctId
#endif

#define OSSCTIDISINVALID(sctId)  ((OS_GETOBJTYP(sctId) != OBJECT_SCHEDULETABLE) || \
                                  (sctId >= OS_MKOBJID(OBJECT_SCHEDULETABLE,OSNSCTS)))

#define OSSctCBSetStatus(t,s) ( *((ScheduleTableStatusType*)&(t) + 1) = (s) ) /* change of the schedule table status */

/***************************************************************************
 * inline function :   OSKillScheduleTable
 *
 * Description: Kills schedule table with given pointer
 *
 * Returns:     nothing
 *
 * Notes:       none
 *
 **************************************************************************/
OSINLINE void OSKillScheduleTable( OSSCTCB *sctCB )
{
    if( sctCB->nextId != OSSCT0 )
    {      /* "next" schedule table doesn't start and it's state changed to SCHEDULETABLE_STOPPED (OS453) */
        OSSctCBSetStatus( sctCB->nextId->state, SCHEDULETABLE_STOPPED );
    }

    if( sctCB->almId->prev != OSALMCBPTR0 )     /* check that alarm is set */
    {
        OSKillAlarm( (OSAlmType)sctCB->almId );
    }

    OSSctCBSetStatus( sctCB->state, SCHEDULETABLE_STOPPED );
}

#if defined(OSAPPLICATION)
/***************************************************************************
 * Function:    OSKillAppScheduleTables
 *
 * Description: kills all schedule tables of given application
 *
 * Notes:
 *
 **************************************************************************/
void OSKillAppScheduleTables(void)
{
    OSDWORD i;
    OSSCTCB *sctCB;

    for( i = 0; i < OSNSCTS; i++ )
    {
        sctCB = &OsScheduleTables[i];
        if( sctCB->appId == OSGetCurApp() )
        {
            OSKillScheduleTable(sctCB);
        }
    }
}
#endif /* defined(OSAPPLICATION) */


/***************************************************************************
 * Function :   OSStartScheduleTable
 *
 * Description: 
 *
 * Notes:
 *
 **************************************************************************/
OSINLINE void OSStartScheduleTable( OSSCTCB *sctCB, TickType abs, OSBYTE is_alarm_hnd )
{
    sctCB->currentEP = sctCB->firstEP;   /* running action */

    OSSctCBSetStatus( sctCB->state, SCHEDULETABLE_RUNNING );

#if defined(OSSCTSYNCIMPLICIT)
    if( ( sctCB->state & OSSCTCFGIMPLMASK ) != 0 )  /* Schedule Table is IMPLICIT */
    {
        OSSctCBSetStatus( sctCB->state, SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS );
    }
#endif

    sctCB->nextId = OSSCT0;

    sctCB->almId->value = abs;
    sctCB->almId->cycle = 0;

#if defined(OSSCTSYNCEXPLICIT)
    sctCB->state &= ~OSSCTCBSYNCUP;
#endif
    if( is_alarm_hnd == OSFALSE )
    {
        OSInsertAlarm( (OSAlmType)sctCB->almId );
    }
}

/***************************************************************************
 * Function :   OSProcessScheduleTable
 *
 * Description: Check notification parameters of the Schedule Tables
 *              expiry points, and perform notification
 *
 * Returns:     valid new almId if next Schedule Tables started, otherwise
 *              OSALM0
 *
 **************************************************************************/
OSAlmType  OSProcessScheduleTable( OSSCTALMCB *almId )
{
    OSSCTCB *sctCB;         /* current Schedule Table */
    const OSSCTEP *sctEP;  
    OSAlmType newAlmId = OSALM0;

#if defined(OSSCTSYNCEXPLICIT)
    TickType adj;           /*  current adjustment value */
#endif
    sctCB = &OsScheduleTables[almId - &OSALMSCTARRAY[0]];
    sctEP = sctCB->currentEP;

    do  /* Actions for all expiry points with equal offsets */
    {
        if( sctCB->state & OSSCTCBEND ) 
        {
            OSSCTCB *nextId;
            nextId = sctCB->nextId;

            if( nextId != OSSCT0 )
            {
                OSStartScheduleTable( nextId, almId->value, OSTRUE );   /* In almId->value - current counter value */
                newAlmId = (OSAlmType)nextId->almId;                    /* almId for next Schedule Table */
                sctCB->nextId = OSSCT0;

#if !defined(OSSCTNEXTNONSTOP)          /* spec. next feature is not defined -> change status and return */
                OSSctCBSetStatus( sctCB->state, SCHEDULETABLE_STOPPED );
                almId->cycle = 0;
                return  newAlmId;
#endif
            }
            if( ( sctCB->state & OSSCTCFGPERIODICMASK ) == 0 )          /* check that Schedule Table is non periodic */
            {
                OSSctCBSetStatus( sctCB->state, SCHEDULETABLE_STOPPED );
                almId->cycle = 0;
                return  newAlmId;
            }

            sctCB->state &= ~OSSCTCBEND;
        }

#if defined(OSSCTSYNCEXPLICIT)
        if( sctEP == sctCB->firstEP )
        {
            sctCB->syncOffset = 0;              /* local time of Schedule Table equal to zero in the first EP */
        }
#endif
        almId->cycle = sctEP->delta;                            /* new time to next EP */

#if defined(OSSCTSYNCEXPLICIT)
        if( ( ( sctCB->state & OSSCTCFGEXPLMASK ) != 0 ) && ( almId->cycle != 0 ) )
        {                                             /* EXPLICIT synchronization is applicable for the Schedule Table */
            if( ( sctCB->state & OSSCTCBSYNCUP ) != 0 )         /* check flag of sync.correction */
            {
                if( sctCB->deviation != 0 )
                {                                               /* it is an additional condition for status changing */
                    if( sctCB->deviation < sctCB->precision )
                    {
                        sctCB->state &= ~OSSCTCBSTATUS;         /* the Schedule Table gets a synchronous status */
                        sctCB->state |= SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS;
                    }
                    if( ( sctCB->state & OSSCTCBDIRSIGN ) != 0 )
                    {
                        adj = sctEP->maxRetard;                 /* retard value */
                    }
                    else
                    {
                        adj = sctEP->maxAdvance;                /* advance value */
                    }

                    if( sctCB->deviation < adj )
                    {                                           /* deviation is less than correction value,*/
                        adj = sctCB->deviation;                 /* it corrects to zero */
                    }

                    sctCB->deviation -= adj;                    /* deviation is corrected */

                    if( ( sctCB->state & OSSCTCBDIRSIGN ) != 0 )
                    {                                           /* decreasing of current span */
                        almId->cycle = sctEP->delta - adj;      /* delta is always greater,it's checked by SG */
                    }
                    else
                    {
                        almId->cycle = sctEP->delta + adj;      /* increasing of current span */
                    }
                }
                else
                {   /* the Schedule Table gets a synchronous status */
                    sctCB->state &= ~( OSSCTCBSTATUS | OSSCTCBSYNCUP );
                    sctCB->state |= SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS;
                }
            }
            sctCB->syncOffset += sctEP->delta;                  /* the next EP offset calculation */
        }
#endif /* defined(OSSCTSYNCEXPLICIT) */

        if( sctEP->action.taskIndex != OSNTSKS )
        {                                                       /* if it isn't a null point */
            OSNotifyAlarmAction( (OSALMACT *)&sctEP->action );
        }
        
        sctEP = sctEP->next;                                    /* set pointer to the next EP */
        sctCB->currentEP = sctEP;

        if( sctEP == sctCB->firstEP )
        {
            sctCB->state |= OSSCTCBEND;                         /* it's a last EP */

        }
    } while( almId->cycle == 0 );

    return  newAlmId;
}

/***************************************************************************
 * Function: StartScheduleTableAbs
 *
 * Description: Start the processing of a Schedule Table at its first
 *              expiry point after the underlaying counter reaches
 *              <tickvalue>
 *
 * Returns:  E_OK 
 *           E_OS_ID (only in EXTENDED status), 
 *           E_OS_VALUE (only in EXTENDED status)
 *           E_OS_STATE
 *
 * Notes:
 *
 **************************************************************************/
StatusType OS_StartScheduleTableAbs( ScheduleTableType sctId, TickType tickvalue )
{
    OSSCTCB *sctCB;
    OSWORD ctrInd;

    OSIMSAVE                                        /* OSINTMASKTYPE save;       */


    OSOrtiSetServiceWatch( OSServiceId_StartScheduleTableAbs );  /* set watch to this service */ 

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_StartScheduleTableAbs, sctId ); 
        }
        else
#endif
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_StartScheduleTableAbs, sctId ); 
        }
    }
#endif /* defined(OSCHECKCONTEXT) */

#if defined(OSEXTSTATUS)
    if( OSSCTIDISINVALID(sctId) )
    {
        OSRETERROR( E_OS_ID, OSServiceId_StartScheduleTableAbs, sctId );
    }
#endif  /* defined(OSEXTSTATUS) */

    sctCB = &OsScheduleTables[OS_GETOBJIND(sctId)];
    ctrInd = sctCB->ctrIndex;

#if defined(OSEXTSTATUS)
    if ( tickvalue > OsCountersCfg[ctrInd].maxallowedvalue ) 
    {
        OSRETERROR( E_OS_VALUE, OSServiceId_StartScheduleTableAbs, sctId );
    }   
#endif  /* defined(OSEXTSTATUS) */

    OSCHECKACCESSRIGHTS( sctCB->appMask, OSServiceId_StartScheduleTableAbs, sctId );

    OSDIS( save );

    if( OSSctCBGetStatus(sctCB->state) != SCHEDULETABLE_STOPPED )
    {   /* if Schedule Table is already started('waiting' inclusive) or 'next' */
        OSRI( save );
        OSRETERROR( E_OS_STATE, OSServiceId_StartScheduleTableAbs, sctId );
    }
    
    OSOrtiSetOldServiceID( OSServiceId_StartScheduleTableAbs );

    OSSetTimVal( ctrInd );

    OSPUTPARAM( OSServiceId_StartScheduleTableAbs, sctId );

    OSStartScheduleTable( sctCB, tickvalue, OSFALSE );

    OSCLEARPARAM();

    if( ( OsRunning != OSGETMAXPRIOTASK )
#if defined(OSISRENTRYEXIT)
        && ( OsIsrLevel == 0 )
#endif
        )
    {
        OSDISPATCH( );
    }

    OSOrtiResetIdOnExit();
    OSRI( save );

    return E_OK;
}

/******************************************************************************
 * Function:    StartScheduleTableRel
 *
 * Description: Start the processing of a Schedule Table at its first
 *              expiry point after offset <offset> ticks have elapsed
 *
 * Returns:     E_OK 
 *              E_OS_ID (only in EXTENDED status), 
 *              E_OS_VALUE (only in EXTENDED status)
 *              E_OS_STATE
 *
 * Notes:
 *
 ******************************************************************************/
StatusType OS_StartScheduleTableRel( ScheduleTableType sctId, TickType increment )
{
    OSSCTCB *sctCB;
    OSWORD ctrInd;
    OSIMSAVE                                        /* OSINTMASKTYPE save;       */


    OSOrtiSetServiceWatch( OSServiceId_StartScheduleTableRel );  /* set watch to this service */ 

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_StartScheduleTableRel, sctId ); 
        }
        else
#endif
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_StartScheduleTableRel, sctId ); 
        }
    }
#endif /* defined(OSCHECKCONTEXT) */

#if defined(OSEXTSTATUS)
    if( OSSCTIDISINVALID(sctId) )
    {
        OSRETERROR( E_OS_ID, OSServiceId_StartScheduleTableRel, sctId );
    }
#endif /* defined(OSEXTSTATUS) */

    sctCB = &OsScheduleTables[OS_GETOBJIND(sctId)];
    ctrInd = sctCB->ctrIndex;

#if defined(OSEXTSTATUS)
#if defined(OSSCTSYNCIMPLICIT)
    if( ( sctCB->state & OSSCTCFGIMPLMASK ) != 0 )
    {   /* Schedule Table is implicitely sinchronized */
        OSRETERROR( E_OS_ID, OSServiceId_StartScheduleTableRel, sctId );
    }
#endif

    if( ( increment == 0 ) || ( increment > ( OsCountersCfg[ctrInd].maxallowedvalue 
        - sctCB->initialOffset  /* OS276 */
      ) ) )
    {
        OSRETERROR( E_OS_VALUE, OSServiceId_StartScheduleTableRel, sctId );
    }
#endif /* defined(OSEXTSTATUS) */

    OSCHECKACCESSRIGHTS( sctCB->appMask, OSServiceId_StartScheduleTableRel, sctId );

    OSDIS( save );

    if( OSSctCBGetStatus( sctCB->state ) != SCHEDULETABLE_STOPPED ) 
    {       /* if Schedule Table is already started('waiting' inclusive) or 'next' */
        OSRI( save );
        OSRETERROR( E_OS_STATE, OSServiceId_StartScheduleTableRel, sctId );
    }

    OSOrtiSetOldServiceID( OSServiceId_StartScheduleTableRel );

    increment = OSAbsTickValue( ctrInd, increment );

    OSPUTPARAM( OSServiceId_StartScheduleTableRel, sctId );

    OSStartScheduleTable( sctCB, increment, OSFALSE );

    OSCLEARPARAM();

    if( ( OsRunning != OSGETMAXPRIOTASK )
#if defined(OSISRENTRYEXIT)
        && ( OsIsrLevel == 0 )
#endif
        )
    {
        OSDISPATCH( );
    }

    OSOrtiResetIdOnExit();
    OSRI( save );

    return E_OK;
}

/******************************************************************************
 * Function:    StopScheduleTable
 *
 * Description: Stop the Schedule Table from processing any further
 *              expiry points
 *
 * Returns:     E_OK 
 *              E_OS_ID (only in EXTENDED status)
 *              E_OS_NOFUNC
 * 
 * Notes:
 *
 ******************************************************************************/
StatusType OS_StopScheduleTable( ScheduleTableType sctId )
{
    OSSCTCB *sctCB;

    OSIMSAVE                                        /* OSINTMASKTYPE save;       */


    OSOrtiSetServiceWatch( OSServiceId_StopScheduleTable );  /* set watch to this service */ 

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_StopScheduleTable, sctId ); 
        }
        else
#endif
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_StopScheduleTable, sctId ); 
        }
    }
#endif /* defined(OSCHECKCONTEXT) */

#if defined(OSEXTSTATUS)
    if( OSSCTIDISINVALID(sctId) )
    {
        OSRETERROR( E_OS_ID, OSServiceId_StopScheduleTable, sctId );
    }
#endif  /* defined(OSEXTSTATUS) */

    sctCB = &OsScheduleTables[OS_GETOBJIND(sctId)];

    OSCHECKACCESSRIGHTS( sctCB->appMask, OSServiceId_StopScheduleTable, sctId );

    OSDIS( save );

    if( OSSctCBGetStatus( sctCB->state ) == SCHEDULETABLE_STOPPED ) 
    {   /* Schedule Table was already stopped */
        OSRI( save );
        OSRETERROR( E_OS_NOFUNC, OSServiceId_StopScheduleTable, sctId );
    }

    OSOrtiSetOldServiceID( OSServiceId_StopScheduleTable );

    OSKillScheduleTable(sctCB);

    if( ( OsRunning != OSGETMAXPRIOTASK )
#if defined(OSISRENTRYEXIT)
        && ( OsIsrLevel == 0 )
#endif
        )
    {
        OSDISPATCH( );
    }

    OSOrtiResetIdOnExit();
    OSRI( save );

    return E_OK;
}


/******************************************************************************
 * Function: NextScheduleTable
 *
 * Description: Start the processing of Schedule Table <sctId_next>
 *              after <sctId_current> reaches its period/length
 *
 * Returns:  E_OK 
 *           E_OS_ID (only in EXTENDED status)
 *           E_OS_NOFUNC 
 *           E_OS_STATE (only in EXTENDED status)
 *
 * Notes:
 *
 ******************************************************************************/
StatusType OS_NextScheduleTable( ScheduleTableType sctId_current, ScheduleTableType sctId_next )
{
    OSSCTCB *sctCB_current;
    OSSCTCB *sctCB_next;

    OSIMSAVE                                        /* OSINTMASKTYPE save;       */

    OSOrtiSetServiceWatch( OSServiceId_NextScheduleTable );  /* set watch to this service */ 

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_NextScheduleTable, sctId_current ); 
        }
        else
#endif
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_NextScheduleTable, sctId_current ); 
        }
    }
#endif /* defined(OSCHECKCONTEXT) */

#if defined(OSEXTSTATUS)
    if( OSSCTIDISINVALID(sctId_next) )
    {
        OSRETERROR( E_OS_ID, OSServiceId_NextScheduleTable, sctId_current );
    }

    if( OSSCTIDISINVALID(sctId_current) )
    {
        OSRETERROR( E_OS_ID, OSServiceId_NextScheduleTable, sctId_current );
    }
#endif  /* defined(OSEXTSTATUS) */

    sctCB_current = &OsScheduleTables[OS_GETOBJIND(sctId_current)];
    sctCB_next = &OsScheduleTables[OS_GETOBJIND(sctId_next)];

    OSCHECKACCESSRIGHTS( sctCB_current->appMask, OSServiceId_NextScheduleTable, sctId_current );
    OSCHECKACCESSRIGHTS( sctCB_next->appMask, OSServiceId_NextScheduleTable, sctId_current );

    OSDIS( save );

#if defined(OSEXTSTATUS)
    if( sctCB_current->ctrIndex != sctCB_next->ctrIndex )
    {
        OSRI( save );  
        OSRETERROR( E_OS_ID, OSServiceId_NextScheduleTable, sctId_current );
    }
    if( OSSctCBGetStatus( sctCB_next->state ) != SCHEDULETABLE_STOPPED )
    {                                           /* next Schedule Table is already started or next */
        OSRI( save );
        OSRETERROR( E_OS_STATE, OSServiceId_NextScheduleTable, sctId_current) ;
    }
#endif  /* defined(OSEXTSTATUS) */

    if( ( OSSctCBGetStatus( sctCB_current->state ) == SCHEDULETABLE_STOPPED ) ||
        ( OSSctCBGetStatus( sctCB_current->state ) == SCHEDULETABLE_NEXT ) )   
    {
        OSRI( save );
        OSRETERROR( E_OS_NOFUNC, OSServiceId_NextScheduleTable, sctId_current );
    }

    if( sctCB_current->nextId != OSSCT0 )       /* restore status of previos next table (OS324) */
    {
        OSSctCBSetStatus( sctCB_current->nextId->state, SCHEDULETABLE_STOPPED );
    }

    sctCB_current->nextId = sctCB_next;

    OSSctCBSetStatus( sctCB_next->state, SCHEDULETABLE_NEXT );

    OSOrtiServiceWatchOnExit(  OSServiceId_NextScheduleTable );
    OSRI( save );

    return E_OK;
}


/******************************************************************************
 * Function:    StartScheduleTableSynchron
 *
 * Description: It is used for processing of Schedule Table at first expiry point after the 
 *              global time is set.
 *
 * Returns:     E_OK 
 *              E_OS_ID (only in EXTENDED status)
 *              E_OS_STATE
 *              E_OS_VALUE (only in EXTENDED status)
 * Notes:
 *
 ******************************************************************************/
StatusType OS_StartScheduleTableSynchron( ScheduleTableType sctId )
{
#if defined(OSSCTSYNCEXPLICIT)
    OSSCTCB *sctCB;
#if defined(OSHWCOUNTER)
    OSWORD ctrInd;
#endif
#endif /* defined(OSSCTSYNCEXPLICIT) */

    OSIMSAVE                                        /* OSINTMASKTYPE save;       */

    OSOrtiSetServiceWatch( OSServiceId_StartScheduleTableSynchron );  /* set watch to this service */ 

#if !defined(OSSCTSYNCEXPLICIT)
#if defined(OSEXTSTATUS)
    OSRETERROR( E_OS_ID, OSServiceId_StartScheduleTableSynchron, sctId );
#else
    OSOrtiServiceWatchOnExit( OSServiceId_StartScheduleTableSynchron );
    return E_OK;
#endif

#else /* !defined(OSSCTSYNCEXPLICIT) */

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_StartScheduleTableSynchron, sctId ); 
        }
        else
#endif
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_StartScheduleTableSynchron, sctId ); 
        }
    }
#endif /* defined(OSCHECKCONTEXT) */

#if defined(OSEXTSTATUS)
    if( OSSCTIDISINVALID(sctId) )
    {
        OSRETERROR( E_OS_ID, OSServiceId_StartScheduleTableSynchron, sctId );
    }
#endif  /* defined(OSEXTSTATUS) */
    
    sctCB = &OsScheduleTables[OS_GETOBJIND(sctId)];

    OSCHECKACCESSRIGHTS( sctCB->appMask, OSServiceId_StartScheduleTableSynchron, sctId );

#if defined(OSEXTSTATUS)
    if( ( sctCB->state & OSSCTCFGEXPLMASK ) == 0 )  /* Schedule Table can't be synchronized */
    {
        OSRETERROR( E_OS_ID, OSServiceId_StartScheduleTableSynchron, sctId );
    }
#endif /* defined(OSEXTSTATUS) */

    OSDIS(save);

    if( OSSctCBGetStatus( sctCB->state ) != SCHEDULETABLE_STOPPED ) 
    {   /* Schedule Table was already started */
        OSRI( save );
        OSRETERROR( E_OS_STATE, OSServiceId_StartScheduleTableSynchron, sctId );
    }


    OSSctCBSetStatus( sctCB->state, SCHEDULETABLE_WAITING );    /* the Schedule Table gets the waiting status */

    OSRI(save);

    OSOrtiServiceWatchOnExit( OSServiceId_StartScheduleTableSynchron );
    return E_OK;

#endif /* !defined(OSSCTSYNCEXPLICIT) */
}


/******************************************************************************
 * Function:    SyncScheduleTable
 *
 * Description: It is used to synchronize the processing of the
 *              Schedule Table to global time.
 *
 * Returns:     E_OK 
 *              E_OS_ID (only in EXTENDED status)
 *              E_OS_STATE
 * Notes:
 *
 ******************************************************************************/
StatusType OS_SyncScheduleTable( ScheduleTableType sctId, GlobalTimeTickType globalTime )
{
#if defined(OSSCTSYNCEXPLICIT)
#if defined(OSEXTSTATUS)
    OSWORD  sctInd;                                 /* index in the Schedule Tables */
#endif
    OSSCTCB *sctCB;

    TickType ctrValue;
    OSWORD   ctrInd;
    TickType deltaTime, dev1, dev2;                 /* auxiliary variables */
#endif /* defined(OSSCTSYNCEXPLICIT) */

    OSIMSAVE                                        /* OSINTMASKTYPE save */

    OSOrtiSetServiceWatch( OSServiceId_SyncScheduleTable );  /* set watch to this service */

#if !defined(OSSCTSYNCEXPLICIT)
#if defined(OSEXTSTATUS)
    OSRETERROR( E_OS_ID, OSServiceId_SyncScheduleTable, sctId );
#else
    OSOrtiServiceWatchOnExit(  OSServiceId_SyncScheduleTable );
    return E_OK;
#endif

#else /* !defined(OSSCTSYNCEXPLICIT) */

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_SyncScheduleTable, sctId );
        }
        else
#endif
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_SyncScheduleTable, sctId ); 
        }
    }
#endif /* defined(OSCHECKCONTEXT) */

#if defined(OSEXTSTATUS)
    if( OSSCTIDISINVALID(sctId) )
    {
        OSRETERROR( E_OS_ID, OSServiceId_SyncScheduleTable, sctId );
    }
#endif  /* defined(OSEXTSTATUS) */

#if defined(OSEXTSTATUS)
    sctInd = OS_GETOBJIND(sctId);
#endif

    sctCB = &OsScheduleTables[sctInd];
    ctrInd = sctCB->ctrIndex;

    OSCHECKACCESSRIGHTS( sctCB->appMask, OSServiceId_SyncScheduleTable, sctId );

    OSDIS(save);
                                                    /* fix the counter value as soon as possible! */
#if defined(OSSWCOUNTER)
#if defined(OSHWCOUNTER)
    if( ctrInd >= OSNHWCTRS )
#endif
    {
        ctrValue = OSSWCtrValue( ctrInd );          /* get counter value for SW counter */
    }
#endif  /* defined(OSSWCOUNTER) */

#if defined(OSHWCOUNTER)
#if defined(OSSWCOUNTER)
    else
#endif
    {
        ctrValue = OSHWCtrValue( ctrInd );          /* get counter value for HW counter */
    }
#endif  /* defined(OSHWCOUNTER) */

#if defined(OSEXTSTATUS)
    if( ( sctCB->state & OSSCTCFGEXPLMASK ) == 0 )  /* the Schedule Table can not be synchronized */
    {
        OSRI( save );
        OSRETERROR( E_OS_ID, OSServiceId_SyncScheduleTable, sctId );
    }
#endif /* defined(OSEXTSTATUS) */

#if defined(OSEXTSTATUS)                            /* global time can not be more than Schedule Table lenght */
    if( globalTime >= sctCB->length )
    {
        OSRI( save );
        OSRETERROR( E_OS_VALUE, OSServiceId_SyncScheduleTable, sctId );
    }
#endif /* defined(OSEXTSTATUS) */

    if( ( OSSctCBGetStatus( sctCB->state ) == SCHEDULETABLE_STOPPED ) || 
        ( OSSctCBGetStatus( sctCB->state ) == SCHEDULETABLE_NEXT ) )
    {   /* if Schedule Table hasn't been started or in next status(OS363) */
#if defined(OSEXTSTATUS)
        OSRI( save );
        OSRETERROR( E_OS_STATE, OSServiceId_SyncScheduleTable, sctId );
#else
        OSOrtiServiceWatchOnExit( OSServiceId_SyncScheduleTable );
        OSRI(save);

        return E_OK;
#endif /* defined(OSEXTSTATUS) */
    }

    if( OSSctCBGetStatus( sctCB->state ) == SCHEDULETABLE_WAITING )
    {                                                   /* StartScheduleTableSynchron() has been called */
        deltaTime = sctCB->length - globalTime ;        /* start of the Schedule Table should be set to zero of this table */

        deltaTime = OSAbsTickValue( ctrInd, deltaTime );

            /* restart of the Schedule Table from WAITING state */
        OSStartScheduleTable( sctCB, deltaTime, OSFALSE );

        {   /* in this case the Schedule Table gets a synchronous status */
            OSSctCBSetStatus( sctCB->state, SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS );
        }
        OSOrtiSetOldServiceID( OSServiceId_SyncScheduleTable );

        if( ( OsRunning != OSGETMAXPRIOTASK )
#if defined(OSISRENTRYEXIT)
            && ( OsIsrLevel == 0 )
#endif
            )
        {
            OSDISPATCH( );
        }

        OSOrtiResetIdOnExit();
        OSRI(save);

        return E_OK;

    }
    deltaTime = sctCB->almId->value - ctrValue;         /* time before next EP */

    if( ctrValue > sctCB->almId->value )
    {
        deltaTime += OsCountersCfg[ctrInd].maxallowedvalue + 1;
    }

    /* calculation of current local time */
    if( sctCB->almId->cycle == 0 )
    {                                                   /* case when a local time hasn't come yet */
        deltaTime = sctCB->length - ( deltaTime % sctCB->length );
    }
    else
    {                                                   /* local time is present,syncOffset has an offset of next EP */
        deltaTime = sctCB->syncOffset - deltaTime;
    }

    if( deltaTime == globalTime )
    {   /* the Schedule Table gets a synchronous status */
        sctCB->state &= ~( OSSCTCBSTATUS | OSSCTCBSYNCUP );
        sctCB->state |= SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS;
    }
    else
    {
        /* calculation of deviation and adjustment */
        dev2 = deltaTime - globalTime;
        dev1 = globalTime - deltaTime;

        if( dev1 > sctCB->length ) 
        {
            dev1 += sctCB->length;
        }
        if( dev2 > sctCB->length )
        {
            dev2 += sctCB->length;
        }
        if( dev1 > dev2 )
        {                                           /* get deviation and increment/decrement flag */
            sctCB->state &= ~(OSSCTCBDIRSIGN);      /* flag of increase of the span's values */
            sctCB->deviation = dev2;
        }
        else
        {
            sctCB->state |= OSSCTCBDIRSIGN;         /* flag of decrease of the span's values */
            sctCB->deviation = dev1;
        }

        sctCB->state &= ~OSSCTCBSTATUS;

        if( sctCB->deviation < sctCB->precision )   /* deviation is compared with PRECISSION value */
        {
            sctCB->state |= SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS; /* the Schedule Table gets sync.status */
        }
        else
        {
            sctCB->state |= SCHEDULETABLE_RUNNING;  /* the Schedule Table gets async.status */
        }

        sctCB->state |= OSSCTCBSYNCUP;              /* setting flag of the sync.correction  */
    }

    OSOrtiServiceWatchOnExit(  OSServiceId_SyncScheduleTable );
    OSRI( save );

    return E_OK;
#endif /* !defined(OSSCTSYNCEXPLICIT) */
}

/******************************************************************************
 * Function:    SetScheduleTableAsync
 *
 * Description: Set the synchronization status of the sctId to asynchronous.
 *
 * Returns:     E_OK 
 *              E_OS_ID (only in EXTENDED status)
 *
 * Notes:
 *
 ******************************************************************************/
StatusType OS_SetScheduleTableAsync( ScheduleTableType sctId )
{
#if defined(OSSCTSYNCEXPLICIT)
    OSSCTCB *sctCB;
#endif

    OSIMSAVE                                        /* OSINTMASKTYPE save;       */

    OSOrtiSetServiceWatch( OSServiceId_SetScheduleTableAsync );  /* set watch to this service */ 

#if !defined(OSSCTSYNCEXPLICIT)
#if defined(OSEXTSTATUS)
    OSRETERROR( E_OS_ID, OSServiceId_SetScheduleTableAsync, sctId );
#else
    OSOrtiServiceWatchOnExit( OSServiceId_SetScheduleTableAsync );
    return E_OK;
#endif

#else /* !defined(OSSCTSYNCEXPLICIT) */

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_SetScheduleTableAsync, sctId ); 
        }
        else
#endif
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_SetScheduleTableAsync, sctId ); 
        }
    }
#endif /* defined(OSCHECKCONTEXT) */

#if defined(OSEXTSTATUS)
    if( OSSCTIDISINVALID(sctId) )
    {
        OSRETERROR( E_OS_ID, OSServiceId_SetScheduleTableAsync, sctId );
    }
#endif  /* defined(OSEXTSTATUS) */

    sctCB = &OsScheduleTables[OS_GETOBJIND(sctId)];

    OSCHECKACCESSRIGHTS( sctCB->appMask, OSServiceId_SetScheduleTableAsync, sctId );

#if defined(OSEXTSTATUS)
    if( ( sctCB->state & OSSCTCFGEXPLMASK ) == 0 )  /* Schedule Table can't be synchronized */
    {
        OSRETERROR( E_OS_ID, OSServiceId_SetScheduleTableAsync, sctId );
    }
#endif

    OSDIS(save);

    if( ( sctCB->state & OSSCTCFGEXPLMASK ) != 0 )  /* Schedule Table is EXPLICIT */
    {
#if defined(OSEXTSTATUS)
        if( ( OSSctCBGetStatus( sctCB->state ) != SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS ) &&
            ( OSSctCBGetStatus( sctCB->state ) != SCHEDULETABLE_RUNNING ) )
        {   
            /* applicable only for Schedule Tables with SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS or SCHEDULETABLE_RUNNING */
            OSRI( save );
            OSRETERROR( E_OS_STATE, OSServiceId_SetScheduleTableAsync, sctId );
        }
#endif
        /* the operation stops further synchronization until SyncScheduleTable() call is made (OS362) */
        sctCB->state &= ~( OSSCTCBSTATUS | OSSCTCBSYNCUP );
        sctCB->state |= SCHEDULETABLE_RUNNING;  /* the Schedule Table gets a running status */
    }

    OSRI(save);
    OSOrtiServiceWatchOnExit( OSServiceId_SetScheduleTableAsync );

    return E_OK;

#endif /* !defined(OSSCTSYNCEXPLICIT) */
}

/******************************************************************************
 * Function:    GetScheduleTableStatus
 *
 * Description: Get the Schedule Table status
 *
 * Returns:     E_OK 
 *              E_OS_ID (only in EXTENDED status)
 *
 * Notes:
 *
 ******************************************************************************/
StatusType OS_GetScheduleTableStatus( ScheduleTableType sctId, ScheduleTableStatusRefType scheduleStatus )
{


    OSOrtiSetServiceWatch( OSServiceId_GetScheduleTableStatus );  /* set watch to this service */ 

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_GetScheduleTableStatus, sctId ); 
        }
        else
#endif
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_GetScheduleTableStatus, sctId ); 
        }
    }
#endif /* defined(OSCHECKCONTEXT) */

#if defined(OSEXTSTATUS)
    if( OSSCTIDISINVALID(sctId) )
    {
        OSRETERROR( E_OS_ID, OSServiceId_GetScheduleTableStatus, sctId );
    }
#endif  /* defined(OSEXTSTATUS) */

    OSCHECKACCESSRIGHTS( OsScheduleTables[OS_GETOBJIND(sctId)].appMask, OSServiceId_GetScheduleTableStatus, sctId );
    OSCHECKWRITEACCESS( scheduleStatus, sizeof(ScheduleTableStatusType), OSServiceId_GetScheduleTableStatus, sctId );

    *scheduleStatus = (OSWORD)OSSctCBGetStatus( OsScheduleTables[OS_GETOBJIND(sctId)].state );

    OSOrtiServiceWatchOnExit( OSServiceId_GetScheduleTableStatus );

    return E_OK;
}


#if OSNAUTOSCTS > 0

/***************************************************************************
 * Function :   OSInitAutoScheduleTables
 *
 * Description: Initialize autostarted Schedule Tables
 *
 * Notes:       used only by OSStartUp
 *
 **************************************************************************/
#if (OSNAPPMODES > 1)            
void OSInitAutoScheduleTables(AppModeType mode)
#else   /* (OSNAPPMODES > 1) */
void OSInitAutoScheduleTables(void)
#endif  /* (OSNAPPMODES > 1) */
{
    OSCARDINAL  i;
    OSWORD ctrInd;
    TickType start;
    OSSCTCB *sctCB;
    const OSSCTAUTOTYPE *acfg;

    for( i = 0; i < OSNAUTOSCTS; i++  ) 
    {
        acfg = &OsAutoScheduleTablesCfg[i];
#if (OSNAPPMODES > 1)
        if( (acfg->autostart & (1 << mode)) != 0 )
        {
#endif  /* (OSNAPPMODES > 1) */
            sctCB = &OsScheduleTables[acfg->sctIndex];
            ctrInd = sctCB->ctrIndex;

            if( acfg->type == OSSCTSYNCHRON )
            {
                OSSctCBSetStatus( sctCB->state, SCHEDULETABLE_WAITING ); /* the Schedule Table gets the waiting status */
            }
            else
            {
                start = acfg->offset;
                if( acfg->type == OSSCTABSOLUTE)
                {
                    OSSetTimVal( ctrInd );
                }
                else
                {
                    if( acfg->type == OSSCTRELATIVE )
                    {
                        start = OSAbsTickValue( ctrInd, start );
                    }
                }
                OSStartScheduleTable( sctCB, start, OSFALSE );
            }
#if (OSNAPPMODES > 1)
        }
#endif  /* (OSNAPPMODES > 1) */
    }
}

#endif /* defined(OSNAUTOSCTS) */

#endif  /* defined(OSSCHEDULETABLES) */
