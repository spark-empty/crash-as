#define OSALM_C
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
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/src/osalm.c,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* Functions:    
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  Function code to support AUTOSAR OS alarms and schedule tables
*
* Notes:        
*
******************************************************************************/

#define OS_INTERNAL 1
#include    <os.h>
#undef OS_INTERNAL

#define OSTEXT_START_SEC_CODE
#include "ossections.h"

#define userAlmId ((OSALMCB *) almId)

/* Local prototypes */
#if (OSNALMS > 0)
void OSKillAlarm(OSAlmType alarmPtr);
void OSNotifyAlarmAction( OSALMACT *action );
#endif 
#if OSNUSERALMS > 0
void OSSetAlarm( OSALMCB *almId, TickType start, TickType cycle );
#endif

#if (OSNALMS > 0)
#if (OSNUSERALMS > 0)
#define OSALMIDISINVALID(almId) ((OS_GETOBJTYP(almId) != OBJECT_ALARM) || (almId >= OS_MKOBJID(OBJECT_ALARM,OSNUSERALMS)))
#endif 
#endif /* (OSNALMS > 0) */

#if (OSNALMS > 0)

 /*****************************************************************************
 * Function:    OSKillAlarm
 *
 * Description: Stop the alarm without checkings (unlike OS_CancelAlarm)
 *
 * Returns:     none
 *
 * Notes:       used in TerminateApplication
 *
 ******************************************************************************/
void OSKillAlarm(OSAlmType alarmPtr)
{
#if defined(OSHWCOUNTER)
    OSAlmType   almRef;
    OSAlmType   min = OSALMCBPTR0;
    OSWORD      ctrInd;

    ctrInd = alarmPtr->ctrIndex;
#endif

    ( alarmPtr->prev )->next = alarmPtr->next;
    if( alarmPtr->next != OSALMCBPTR0 )             /* Is this alarm last in the list ? */
    {
        alarmPtr->next->prev = alarmPtr->prev;
    }
#if defined(OSHWCOUNTER)
#if defined(OSSWCOUNTER)
    if( ctrInd < OSNHWCTRS )
#endif
    {
        alarmPtr->prev = OSALMCBPTR0;               /* It is necessary for check E_OS_STATE */
        OsTimVal = OSHWCtrGetOC( ctrInd );          /* set osTimVal */
        if( OsCounters[ctrInd].alarm == OSALM0 )
        {                                           /* if there are no more alarms on HW counter */
            OSHWCtrCancel( ctrInd );                /* then cancel it */
        }
        else
        {                                           /* reArm counter and check for expiried alarms */
            volatile OSHWTickType time1, time2;

            almRef = OsCounters[ctrInd].alarm;
            do{
#ifdef OSCWPPC  /* to remove this comment from end-user code */
                /* Temporary calculation - workaround for CW bug. Similar to this code is used in many places */
#endif
                time2 = OSCTRBITS( almRef->value - OsTimVal );

                if( ( min == OSALMCBPTR0 ) || ( OSCTRBITS( min->value - OsTimVal ) > time2 ) )
                {
                    min = almRef;
                }
                almRef = almRef->next;

            } while( almRef != OSALM0 );
            
            if( min->value != OsTimVal )                     /* an other alarm to be armed */
            {
                OsTimVal = OSHWCtrValue( ctrInd );           /* set OsTimVal the current counter value */
                if( OSInterruptRaised( ctrInd ) )            /* Interrupt raised since last OSDI() */
                {
                    OsTimVal = OSHWCtrGetOC( ctrInd );       /* set OsTimVal the current value of the OC register */
                }
                OSHWCtrArm( ctrInd, min->value );

                time1 = OSCTRBITS( OSHWCtrValue( ctrInd ) - OsTimVal );
                time2 = OSCTRBITS( OSHWCtrGetOC( ctrInd ) - OsTimVal );

                /* if new alarm already expiried  */
                if( time1 >= time2 )
                {
                    OSCounterNotify( ctrInd );
                }
            }
        }

    }
#if defined(OSSWCOUNTER)
    else
#endif  /* defined(OSSWCOUNTER) */
#endif  /* defined(OSHWCOUNTER) */
    {
        alarmPtr->prev = OSALMCBPTR0;           /* It is necessary for check E_OS_STATE */
    }
}

/***************************************************************************
 * Function:    OSNotifyAlarmAction
 *
 * Description: 
 *
 * Notes:
 *
 **************************************************************************/

void OSNotifyAlarmAction( OSALMACT *action )
{

#if defined(OSBCC)
    if( OSTASKACTEXHAUSTED(action->taskIndex) ) 
    {
        OSErrorHook_noPar( E_OS_LIMIT );      /* attempt to multiply activation */
    }
    else
    {
        {
#if defined(OSNOFASTTERMINATE) || defined(OSINRES)
            OSActivateTaskInAlm( action->taskIndex );
#else
            OSTask2Ready(action->taskIndex);
#endif
        }
    }

#elif defined(OSECC) 

#if (OSNXTSKS > 0) 
#if defined(OSALMSETEVENT) || defined(OSSCTSETEVENT)
    if( action->event )
    {
        if( (OSTASKSTATUS(action->taskIndex) & OSTCBNOSUSPENDED) == 0 )
        {
            OSErrorHook_noPar( E_OS_STATE );  /* the task is in a suspended state */
        }
        else
        {
            OSSetEventInAlm( &OsTaskTable[action->taskIndex], action->event );
        }
        return;
    }
    else
#endif  /* defined(OSALMSETEVENT) || defined(OSSCTSETEVENT) */
    {                                   
        if( OSTASKACTEXHAUSTED(action->taskIndex) )
        {
            OSErrorHook_noPar( E_OS_LIMIT );  /* attempt to multiply activation */
        }
        else        
        {                               
            OsTaskTable[action->taskIndex].set_event = OSNOEVENTS;
                                        /* set flag that task has no valid context  yet */
            OSActivateTaskInAlm( action->taskIndex );
        }
    }
#else   /* OSNXTSKS > 0     */
    if( OSTASKACTEXHAUSTED(action->taskIndex) )
    {
        OSErrorHook_noPar( E_OS_LIMIT );      /* attempt to multiply activation */
    }
    else        
    {                                /* set flag that task has no valid context yet */
        OSActivateTaskInAlm( action->taskIndex );
    }
#endif  /* OSNXTSKS > 0     */
#endif  /* defined(OSECC)  */
    return;
}


#if defined(OSHWCOUNTER)
/***************************************************************************
 * Function :   OSCounterNotify
 *
 * Description: check for expiried alarms and perform appropriate actions
 *
 * Returns:
 *
 * Notes:       1. called only if at least one alarm expired.
 *              2. this is intended for alarms on "HW" counters only
 *
 **************************************************************************/
void  OSCounterNotify( OSWORD ctrInd )
{
    OSAlmType     almId;                         /* current alarm        */
    OSAlmType    *almRef;                        /* temporary pointer    */
    OSHWTickType  minVal;
    OSHWTickType    delta;
#if defined(OSSCHEDULETABLES)
    OSAlmType     newAlmId = OSALM0;
#endif
#if defined(OSALMINCCOUNTER)
    OSWORD index;
#endif

again:

    OsTimVal = OSHWCtrGetOC( ctrInd );          /* set osTimVal */
    minVal = OsTimVal - 1;
    delta  = OSCTRBITS(0xFFFFFFFFul);

#if defined(OSSCHEDULETABLES)
almAdded:
#endif /* defined(OSSCHEDULETABLES) */

    almRef = &(OsCounters[ctrInd].alarm);

    do{
        if( (*almRef)->value == OsTimVal )
        {
            almId = *almRef;

#if defined(OSSCHEDULETABLES)
#if (OSNUSERALMS > 0)  
            
            if( almId  >= ( (OSAlmType)&OSALMSCTARRAY[0] ) )   /* if it is schedule table alarm. */
                /* Note: the array of user alarms is located in the memory before the array of schedule table alarms. */
            {            
#endif
                newAlmId = OSProcessScheduleTable( (OSSCTALMCB *)almId );
#if (OSNUSERALMS > 0)           
            }
            else 
#endif
#endif /* defined(OSSCHEDULETABLES) */
#if (OSNUSERALMS > 0)  
#if defined(OSALMCALLBACK)
            if( userAlmId->callBack )
            {
#if defined(OSGETSERVICEID)
                OSServiceIdType tmpId;
                tmpId = OsService;
                OSCLEARPARAM();
#endif
                OsIsrLevel |= OSISRLEVELCALLBACK;
                userAlmId->callBack();
                OsIsrLevel &= (OSISRLEVELTYPE)(~OSISRLEVELCALLBACK);
#if defined(OSGETSERVICEID)
                OsService = tmpId;
#endif
            }
            else
#endif  /* defined(OSALMCALLBACK) */
#if defined(OSALMINCCOUNTER)
            if( userAlmId->ctrIndexInc != OSCTR0 )
            {
                OsCtrIncValue[userAlmId->ctrIndexInc-OSNHWCTRS]++;
                OsCtrIncCounter++;

                while ( OsCtrIncCounter != 0 )
                {
                    /* Check for all SW counters */
                    for( index = OSNHWCTRS; index < OSNCTRS; index++ )
                    {
                        if( OsCtrIncValue[index-OSNHWCTRS] > 0 )
                        {
                            OsCtrIncValue[index-OSNHWCTRS]--;
                            OsCtrIncCounter--;
                            OSCounterTrigger(index);
                        }
                    }
                }
            }
            else
#endif  /* defined(OSALMINCCOUNTER) */
            {
                OSNotifyAlarmAction( &userAlmId->action );              /* perform alarm action */
            }
#endif /* (OSNUSERALMS > 0) */

            if( almId->cycle == 0 )
            {                                       /* remove alarm from list if it is not cyclic */
                (almId->prev)->next = almId->next;
                if( almId->next != OSALMCBPTR0 )    /* Is it the last alarm in the list ?   */
                {
                    (almId->next)->prev = almId->prev;
                }
                almId->prev = OSALMCBPTR0;          /* It is necessary for check E_OS_STATE */
            }
            else
            {                                       /* reinsert alarm if it is cyclic       */
                almId->value = OSCTRBITS(almId->value + almId->cycle);    
                if( OSCTRBITS( almId->value - OsTimVal ) < delta )
                {
                    minVal = almId->value;
                    delta  = OSCTRBITS( minVal - OsTimVal );
                }
                almRef = &(*almRef)->next;
            }

#if defined(OSSCHEDULETABLES)
            if( newAlmId != OSALMCBPTR0 )
            {
                /* Easy insert into head of list */
                newAlmId->next = OsCounters[ctrInd].alarm;     
                OsCounters[ctrInd].alarm = newAlmId;
                newAlmId->prev = (OSAlmType)(&(OsCounters[ctrInd].alarm)); /* The counter node is previous for first in list */
                if( newAlmId->next != OSALMCBPTR0 )            /* There are already alarms in the list */
                {
                    ( newAlmId->next )->prev = newAlmId;
                }
                goto almAdded;
            }
#endif /* defined(OSSCHEDULETABLES) */

        }
        else
        {
            if( OSCTRBITS( (*almRef)->value - OsTimVal ) < delta )
            {
                minVal = (*almRef)->value;
                delta  = OSCTRBITS( minVal - OsTimVal );
            }
            almRef = &(*almRef)->next;
        }

    }while( *almRef != OSALM0 );

    if( OsCounters[ctrInd].alarm != OSALM0 )
    {                                           /* arm counter if there are attached alarms */
        volatile OSHWTickType time1, time2;

        OSHWCtrArm( ctrInd, minVal );

        time1 = OSCTRBITS( OSHWCtrValue( ctrInd ) - OsTimVal );
        time2 = OSCTRBITS( minVal - OsTimVal );

        if( time1 >= time2 )            /* if new alarm already expiried            */
        {
            OSHWCtrCancel( ctrInd );            /* disable interrupt and clear channel flag */
            goto again;                         /* repeat notification                      */
        }
    }
    else
    {                                           /* otherwise inform it that no more alarms  */
        OSHWCtrCancel( ctrInd );
    }
}
#endif  /* defined(OSHWCOUNTER) */


/***************************************************************************
 * Function:    OSCheckAlarms
 *
 * Description: Check linked alarms
 *
 * Returns:
 *
 * Notes:       for SW counters
 *
 **************************************************************************/
void OSCheckAlarms( OSWORD ctrInd )
{
    OSAlmType   almId;                          /* current alarm        */
    TickType   *delta;
#if defined(OSSCHEDULETABLES)
    OSAlmType newAlmId = OSALM0;

almAdded:
#endif /* defined(OSSCHEDULETABLES) */

    almId = OsCounters[ctrInd].alarm;
    while( almId != OSALMCBPTR0 )
    {
        delta = &almId->value;
        if( *delta == OsCounters[ctrInd].value )
        {
#if defined(OSSCHEDULETABLES)
#if (OSNUSERALMS > 0)
            if( almId >= ( (OSAlmType)&OSALMSCTARRAY[0] ) )    /* if it is schedule table alarm. */
                /* Note: the array of user alarms is located in the memory before the array of schedule table alarms. */
            {            
#endif
                newAlmId = OSProcessScheduleTable( (OSSCTALMCB *)almId );
#if (OSNUSERALMS > 0)
            }
            else
#endif
#endif /* defined(OSSCHEDULETABLES) */
#if (OSNUSERALMS > 0)
#if defined(OSALMCALLBACK)
            if( userAlmId->callBack )
            {
#if defined(OSGETSERVICEID)
                OSServiceIdType tmpId;
                tmpId = OsService;
                OSCLEARPARAM();
#endif
                OsIsrLevel |= OSISRLEVELCALLBACK;
                userAlmId->callBack();
                OsIsrLevel &= (OSISRLEVELTYPE)(~OSISRLEVELCALLBACK);
#if defined(OSGETSERVICEID)
                OsService = tmpId;
#endif
            }
            else 
#endif /* defined(OSALMCALLBACK) */
#if defined(OSALMINCCOUNTER)
            if( userAlmId->ctrIndexInc != OSCTR0 )
            {
                OsCtrIncValue[userAlmId->ctrIndexInc-OSNHWCTRS]++;
                OsCtrIncCounter++;
            }
            else
#endif /* defined(OSALMINCCOUNTER) */
            {
                OSNotifyAlarmAction( &userAlmId->action );           /* perform alarm action                             */
            }
#endif /* (OSNUSERALMS > 0) */

            if( almId->cycle == 0 )            
            {                                  /* remove alarm from list if it is not cyclic */
                (almId->prev)->next = almId->next;
                if( almId->next != OSALMCBPTR0 )                 /* Is it alarme last in the list ? */
                {
                    (almId->next)->prev = almId->prev;
                }
                almId->prev = OSALMCBPTR0;           /* It is necessary for check E_OS_STATE */
            }
            else
            {
                /* reinsert alarm if it is cyclic   */

                if( ( OsCountersCfg[ctrInd].maxallowedvalue - *delta ) < almId->cycle )
                {
                    /* if next counter value for cyclic alarm is higher than maxallowedvalue */
                    *delta += ( almId->cycle - OsCountersCfg[ctrInd].maxallowedvalue ) - 1;
                }
                else
                {
                    *delta += almId->cycle;
                }
            }
#if defined(OSSCHEDULETABLES)
            if( newAlmId != OSALMCBPTR0 )
            {                                       /* insert into head of list */
                newAlmId->next = OsCounters[ctrInd].alarm;     
                OsCounters[ctrInd].alarm = newAlmId;
                newAlmId->prev = (OSAlmType)(&(OsCounters[ctrInd].alarm)); /* "previous" is counter link    */
                if( newAlmId->next != OSALMCBPTR0 )            /* There are already alarms in the list */
                {
                    (newAlmId->next)->prev = newAlmId;
                }
                goto almAdded;
            }
#endif /* defined(OSSCHEDULETABLES) */
        }
        almId = almId->next;
    }
}


/******************************************************************************
 * Function :   OSInsertAlarm
 *
 * Description: Insert alarm into list attached to counter,
 *              arm HW counter if it is the first alarm.
 *
 * Notes:       called with interrupts disabled
 *
 ******************************************************************************/
 void OSInsertAlarm( OSAlmType almId )
{
    OSWORD  ctrInd;
    TickType start;

    ctrInd = almId->ctrIndex;
    start = almId->value;

    almId->next = OsCounters[ctrInd].alarm;     /* Alarm is linked into head of the list */
    OsCounters[ctrInd].alarm = almId;
    almId->prev = (OSAlmType)(&(OsCounters[ctrInd].alarm)); /* The counter node is previous for first in list */
    if( almId->next != OSALMCBPTR0 )            /* There are already alarms in the list */
    {
        ( almId->next )->prev = almId;
    }

#if defined(OSHWCOUNTER)
#if defined(OSSWCOUNTER)
    if( ctrInd < OSNHWCTRS )
#endif
    {        
        volatile OSHWTickType time1, time2;

        time1 = OSCTRBITS( OSHWCtrGetOC( ctrInd ) - OsTimVal );
        time2 = OSCTRBITS( start - OsTimVal );

        if( ( almId->next == OSALMCBPTR0 ) || ( time1 > time2 ) )
        {                                   /* if new HW alarm is the first to expire */
            OSHWCtrArm( ctrInd, start );     /* then arm it */
        }
                                            /* check if alarm(s) just expiried */
        time1 = OSCTRBITS( OSHWCtrValue( ctrInd ) - OsTimVal );
        time2 = OSCTRBITS( OSHWCtrGetOC( ctrInd ) - OsTimVal );

        if( time1 >= time2 )
        {
            OSCounterNotify( ctrInd );
        }
    }
#if defined(OSSWCOUNTER)
    else
#endif  /* defined(OSSWCOUNTER) */
#endif  /* defined(OSHWCOUNTER) */

#if defined(OSSWCOUNTER)
    {
        if( start == OSSWCtrValue( ctrInd ) )
        {
            OSCheckAlarms( ctrInd );
        }
    }
#endif  /* defined(OSSWCOUNTER) */
}

#endif /* OSNALMS > 0 */


#if OSNUSERALMS > 0

#if defined(OSAPPLICATION)
/***************************************************************************
 * Function:    OSKillAppAlarms
 *
 * Description: kills all alarms of given application
 *
 * Notes:
 *
 **************************************************************************/
void OSKillAppAlarms(void)
{
    OSWORD i;
    OSALMCB *almRef;
    
    almRef = &OSALMARRAY[0];

    for(i = 0; i < OSNUSERALMS; i++, almRef++ )
    {
        if( (OSGetCurApp() == almRef->appId ) && (almRef->prev != OSALMCBPTR0) )
        {
            OSKillAlarm( (OSAlmType)almRef );
        }
    }
}
#endif /* defined(OSAPPLICATION) */

/******************************************************************************
 * Function:    GetAlarmBase
 *
 * Description: Get the alarm base characteristics
 *
 * Returns:     E_OK    no errors
 *              E_OS_ID    (ext.status) the identifier is invalid
 *
 * Notes:
 ******************************************************************************/

StatusType OS_GetAlarmBase( AlarmType almId, AlarmBaseRefType info )
{
    OSWORD ctrInd;
#if defined(OSAPPLICATION)
    OSWORD almInd;
#endif


    OSOrtiSetServiceWatch( OSServiceId_GetAlarmBase );        /* set watch to this service */ 

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK |
                         OSISRLEVELHOOKERROR | OSISRLEVELHOOKAPPERROR | OSISRLEVELHOOKTASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_GetAlarmBase, almId );
        }
        else
#endif
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_GetAlarmBase, almId ); 
        }
    }
#endif /* defined(OSCHECKCONTEXT) */

#if defined(OSEXTSTATUS)
    if( OSALMIDISINVALID(almId) ) /* invalid ID */
    {                                     
        OSRETERROR( E_OS_ID, OSServiceId_GetAlarmBase, almId );
    }
#endif /* OSEXTSTATUS */

#if defined(OSAPPLICATION)
    almInd = OS_GETOBJIND( almId );
    OSCHECKACCESSRIGHTS( OSALMARRAY[ almInd ].appMask, OSServiceId_GetAlarmBase, almId );
    ctrInd = OSALMARRAY[ almInd ].ctrIndex;
#else
    ctrInd = OSALMARRAY[ OS_GETOBJIND( almId ) ].ctrIndex;
#endif

    OSCHECKWRITEACCESS2( info, sizeof(AlarmBaseType), OSServiceId_GetAlarmBase, almId );

    info->maxallowedvalue = OsCountersCfg[ctrInd].maxallowedvalue;
    info->ticksperbase = OsCountersCfg[ctrInd].ticksperbase;

#if defined(OSEXTSTATUS)
    info->mincycle = OsCountersCfg[ctrInd].mincycle;
#endif  /* defined(OSEXTSTATUS) */

    OSOrtiServiceWatchOnExit( OSServiceId_GetAlarmBase ); 
    return( E_OK );
}

/******************************************************************************
 * Function:    GetAlarm
 *
 * Description: Get the number of tick before alarm expires
 *
 * Returns:     E_OK, E_OS_NOFUNC, E_OS_ID
 *
 * Notes:
 *
 ******************************************************************************/

StatusType OS_GetAlarm( AlarmType almId, TickRefType tickRef )
{
    OSWORD      ctrInd;
    OSALMCB     *almRef;
    OSIMSAVE                                    /* OSINTMASKTYPE save;       */


    OSOrtiSetServiceWatch( OSServiceId_GetAlarm );  /* set watch to this service */ 

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK |
                         OSISRLEVELHOOKERROR | OSISRLEVELHOOKAPPERROR | OSISRLEVELHOOKTASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_GetAlarm, almId );
        }
        else
#endif
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_GetAlarm, almId ); 
        }
    }
#endif /* defined(OSCHECKCONTEXT) */

#if defined(OSEXTSTATUS)
    if( OSALMIDISINVALID(almId) ) /* invalid ID */
    {                                     
        OSRETERROR( E_OS_ID, OSServiceId_GetAlarm, almId );
    }
#endif /* OSEXTSTATUS */

    almRef = &OSALMARRAY[OS_GETOBJIND(almId)];
    ctrInd = almRef->ctrIndex;

    if( almRef->prev == OSALMCBPTR0 )               /* Alarm is not linked in the list - not used alarm */
    {                                               /* The alarm is not used */
        OSRETERROR( E_OS_NOFUNC, OSServiceId_GetAlarm, almId );
    }

    OSCHECKACCESSRIGHTS( OSALMARRAY[ OS_GETOBJIND( almId ) ].appMask, OSServiceId_GetAlarm, almId );
    OSCHECKWRITEACCESS2( tickRef, sizeof(TickType), OSServiceId_GetAlarm, almId );

    OSDIS( save );
#if defined(OSSWCOUNTER)
#if defined(OSHWCOUNTER)
    if( ctrInd >= OSNHWCTRS )
#endif
    {
        *tickRef = OSSWCtrValue(ctrInd);
    }
#endif  /* defined(OSSWCOUNTER) */

#if defined(OSHWCOUNTER)
#if defined(OSSWCOUNTER)
    else
#endif  /* defined(OSSWCOUNTER) */
    {
        *tickRef = OSHWCtrValue(ctrInd);
    }
#endif  /* defined(OSHWCOUNTER) */
    if( almRef->value >= *tickRef )
    {
        *tickRef = almRef->value - *tickRef;
    }
    else
    {
        *tickRef = almRef->value + OsCountersCfg[ctrInd].maxallowedvalue + 1 - *tickRef;
    }

    OSRI( save );

    OSOrtiServiceWatchOnExit( OSServiceId_GetAlarm );
    return( E_OK );
}


/***************************************************************************
 * Function :   OSSetAlarm
 *
 * Description: Insert alarm into list attached to counter
 *
 * Returns:
 *
 * Notes:       called with interrupts disabled
 *
 **************************************************************************/

void OSSetAlarm( OSALMCB *almId, TickType start, TickType cycle )
{
    almId->value = start;
    almId->cycle = cycle;

    OSInsertAlarm( (OSAlmType)almId );

    OSCLEARPARAM(); 

    if( ( OsRunning != OSGETMAXPRIOTASK )
#if defined(OSISRENTRYEXIT)
        && ( OsIsrLevel == 0 )
#endif
        )
    {
        OSDISPATCH( );
    }
    return;
}

#if defined(OSAUTOALARMS)
/***************************************************************************
 * Function :   OSInitAutoAlarms
 *
 * Description: Initialize autostarted alarms
 *
 * Notes:       used only by OSStartUp
 *
 **************************************************************************/
#if (OSNAPPMODES > 1)            
void OSInitAutoAlarms(AppModeType mode)
#else   /* (OSNAPPMODES > 1) */
void OSInitAutoAlarms()
#endif  /* (OSNAPPMODES > 1) */
{
    OSCARDINAL  i;
    OSWORD ctrInd;
    OSALMCB *almId;
    TickType start;

    for( i = 0; i < OSNAUTOALMS; i++  )
    {
#if (OSNAPPMODES > 1)            
        if( (OsAutoAlarms[i].autostart & (1 << mode)) != 0 )
        {
#endif  /* (OSNAPPMODES > 1) */
            almId = OsAutoAlarms[i].almId;
            ctrInd = almId->ctrIndex;
            start = OsAutoAlarms[i].time;

            if( OsAutoAlarms[i].type == OSALMRELATIVE )
            {
                start = OSAbsTickValue( ctrInd, start );
            }
            else
            {
                OSSetTimVal( ctrInd );
            }
                /*********** insert alarm into list **************/
            almId->value = start;
            almId->cycle = OsAutoAlarms[i].cycle;

            OSInsertAlarm( (OSAlmType)almId );

#if (OSNAPPMODES > 1)
        }
#endif  /* (OSNAPPMODES > 1) */
    }
}
#endif  /* defined(OSAUTOALARMS) */

/******************************************************************************
 * Function:    SetRelAlarm
 *
 * Description: Start the relative alarm
 *
 * Returns:     E_OK, E_OS_STATE, E_OS_ID, E_OS_VALUE
 *
 * Notes:
 *
 ******************************************************************************/
StatusType OS_SetRelAlarm( AlarmType almId, TickType increment, TickType cycle )
{
#if defined(OSEXTSTATUS) || defined(OSHWCOUNTER) || defined(OSSWCOUNTER)
    OSWORD     ctrInd;
#endif
    OSALMCB *almRef;
    OSIMSAVE                                       /* OSINTMASKTYPE save;       */


    OSOrtiSetServiceWatch( OSServiceId_SetRelAlarm ); /* set watch to this service */ 

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_SetRelAlarm, almId ); 
        }
        else
#endif
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_SetRelAlarm, almId ); 
        }
    }
#endif /* defined(OSCHECKCONTEXT) */

    if( increment == 0 ) 
    {                           /* zero increment value is ambiguous */
        OSRETERROR( E_OS_VALUE, OSServiceId_SetRelAlarm, almId );   
    }

#if defined(OSEXTSTATUS)
    if( OSALMIDISINVALID(almId) ) /* invalid ID */
    {                                     
        OSRETERROR( E_OS_ID, OSServiceId_SetRelAlarm, almId );
    }
#endif /* OSEXTSTATUS */

    almRef = &OSALMARRAY[OS_GETOBJIND(almId)];

#if defined(OSEXTSTATUS) || defined(OSHWCOUNTER) || defined(OSSWCOUNTER)
    ctrInd = almRef->ctrIndex;
#endif

#if defined(OSEXTSTATUS)
    /* Check initial value and cycle value */
    if( increment > OsCountersCfg[ctrInd].maxallowedvalue ) /* increment value is outside of admissible limit */
    {
        OSRETERROR( E_OS_VALUE, OSServiceId_SetRelAlarm, almId );
    }
    if( (cycle != 0 ) && ( ( cycle > OsCountersCfg[ctrInd].maxallowedvalue || (cycle < OsCountersCfg[ctrInd].mincycle ) ) ) )
    {                                         /* cycle value is outside of admissible limit */
        OSRETERROR( E_OS_VALUE, OSServiceId_SetRelAlarm, almId );
    }
#endif /* defined(OSEXTSTATUS) */

    OSCHECKACCESSRIGHTS( OSALMARRAY[ OS_GETOBJIND( almId ) ].appMask, OSServiceId_SetRelAlarm, almId );

    OSDIS( save );
    /* Check state of the alarm */
    if( almRef->prev != OSALMCBPTR0 )                   /* Alarm is linked in the list - running alarm */
    {                                                   /* The alarm is already in use */
        OSRI( save );
        OSRETERROR( E_OS_STATE, OSServiceId_SetRelAlarm, almId );
    }

    OSOrtiSetOldServiceID( OSServiceId_SetRelAlarm ); 

    increment = OSAbsTickValue( ctrInd, increment );

    OSPUTPARAM( OSServiceId_SetRelAlarm, almId );
    OSSetAlarm( almRef, increment, cycle );

    OSOrtiResetIdOnExit();
    OSRI( save );
    return( E_OK );
}

/******************************************************************************
 * Function:    SetAbsAlarm
 *
 * Description: Start the alarm
 *
 * Returns:     E_OK, E_OS_STATE, E_OS_ID, E_OS_VALUE
 *
 * Notes:
 *
 ******************************************************************************/
StatusType OS_SetAbsAlarm(  AlarmType almId, TickType start, TickType cycle )
{
#if defined(OSEXTSTATUS) || defined(OSHWCOUNTER) || defined(OSSWCOUNTER)
    OSWORD  ctrInd;             
#endif

    OSALMCB  *almRef;
    OSIMSAVE                                       /* OSINTMASKTYPE save;       */


    OSOrtiSetServiceWatch( OSServiceId_SetAbsAlarm ); /* set watch to this service */ 

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_SetAbsAlarm, almId ); 
        }
        else
#endif
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_SetAbsAlarm, almId ); 
        }
    }
#endif /* defined(OSCHECKCONTEXT) */

#if defined(OSEXTSTATUS)
    if( OSALMIDISINVALID(almId) ) /* invalid ID */
    {                                     
        OSRETERROR( E_OS_ID, OSServiceId_SetAbsAlarm, almId );
    }
#endif /* OSEXTSTATUS */

    almRef = &OSALMARRAY[OS_GETOBJIND(almId)];

#if defined(OSEXTSTATUS) || defined(OSHWCOUNTER) || defined(OSSWCOUNTER)
    ctrInd = almRef->ctrIndex;
#endif
    
#if defined(OSEXTSTATUS)
    /* Check initial value and cycle value */
    if( start > OsCountersCfg[ctrInd].maxallowedvalue )             /* start value is outside of admissible limit */
    {                                           
        OSRETERROR( E_OS_VALUE, OSServiceId_SetAbsAlarm, almId );
    }
    if( ( cycle != 0) && ( ( cycle > OsCountersCfg[ctrInd].maxallowedvalue || (cycle < OsCountersCfg[ctrInd].mincycle ) ) ) )
    {                                                               /* cycle value is outside of admissible limit */
        OSRETERROR( E_OS_VALUE, OSServiceId_SetAbsAlarm, almId );
    }
#endif /* defined(OSEXTSTATUS) */

    OSCHECKACCESSRIGHTS( OSALMARRAY[ OS_GETOBJIND( almId ) ].appMask, OSServiceId_SetAbsAlarm, almId );

    OSDIS( save );
    /* Check state of the alarm */
    if( almRef->prev != OSALMCBPTR0 )                      /* Alarm is linked in the list - running alarm */
    {                                                      /* The alarm is already in use */
        OSRI( save );
        OSRETERROR( E_OS_STATE, OSServiceId_SetAbsAlarm, almId );
    }

    OSOrtiSetOldServiceID( OSServiceId_SetAbsAlarm ); 

    OSSetTimVal( ctrInd );

    OSPUTPARAM( OSServiceId_SetAbsAlarm, almId );
    OSSetAlarm( almRef, start, cycle );

    OSOrtiResetIdOnExit( );
    OSRI( save );

    return( E_OK );
}

 /*****************************************************************************
 * Function:    CancelAlarm
 *
 * Description: Stop the alarm
 *
 * Returns:     E_OK, E_OS_NOFUNC, E_OS_ID
 *
 * Notes:
 *
 ******************************************************************************/
StatusType OS_CancelAlarm( AlarmType almId )
{
    OSALMCB   *almRf0;
    OSIMSAVE                                        /* OSINTMASKTYPE save;       */


    OSOrtiSetServiceWatch( OSServiceId_CancelAlarm ); /* set watch to this service */

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_CancelAlarm, almId ); 
        }
        else
#endif
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_CancelAlarm, almId ); 
        }
    }
#endif /* defined(OSCHECKCONTEXT) */

#if defined(OSEXTSTATUS)
    if( OSALMIDISINVALID(almId) ) /* invalid ID */
    {                                     
        OSRETERROR( E_OS_ID, OSServiceId_CancelAlarm, almId );
    }
#endif /* OSEXTSTATUS */

    OSCHECKACCESSRIGHTS( OSALMARRAY[ OS_GETOBJIND( almId ) ].appMask, OSServiceId_CancelAlarm, almId );

    almRf0 = &OSALMARRAY[OS_GETOBJIND(almId)];

    OSDIS( save );

    if( almRf0->prev == OSALMCBPTR0 )           /* Alarm is not used                */
    {                                           /* The alarm is not used            */
        OSRI( save );                           /* attempt to multiply deactivation */
        OSRETERROR( E_OS_NOFUNC, OSServiceId_CancelAlarm, almId );
    }

    OSOrtiSetOldServiceID( OSServiceId_CancelAlarm );
    OSPUTPARAM( OSServiceId_CancelAlarm, almId);
    OSKillAlarm((OSAlmType)almRf0);
    OSCLEARPARAM( ); 

    if( ( OsRunning != OSGETMAXPRIOTASK )
#if defined(OSISRENTRYEXIT)
        && ( OsIsrLevel == 0 )
#endif
        )
    {
        OSDISPATCH( );
    }

    OSOrtiResetIdOnExit( );
    OSRI( save );

    return( E_OK );
}

#endif /* OSNUSERALMS > 0 */

