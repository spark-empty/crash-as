#ifndef OSALMAPI_H
#define OSALMAPI_H
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
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/inc/osalmapi.h,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  API for OSEK OS alarms  
*
* Notes:        
*
******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/* Note! Condition '#if defined OSALARM' is equivalent to condition '#if OSNUSERALMS > 0' */
/* Note! Condition '#if OSNALMS > 0' is equivalent to conditions '#if OSNUSERALMS > 0 || OSNSCTALMS > 0' */

/*  OS internal type */
                                                               
#if (OSNALMS > 0)

/*  Constructional elements */

#if (OSNUSERALMS > 0)
#define DeclareAlarm(Alarm) extern OSBYTE osdummy
#endif

#if (OSNUSERALMS > 0)

/*  Configuration Data */
extern const OSALM OsAlarmsCfg[OSNUSERALMS];

#if defined(OSAUTOALARMS)
extern const OSALMAUTOTYPE OsAutoAlarms[OSNAUTOALMS];
#if (OSNAPPMODES > 1)            
void OSInitAutoAlarms( AppModeType mode );
#else   /* (OSNAPPMODES > 1) */
void OSInitAutoAlarms( void );
#endif  /* (OSNAPPMODES > 1) */
#endif /* defined(OSAUTOALARMS) */

#if (OSNSCTALMS == 0)
/*  Global OS variables */
#define OSALMARRAY OsAlarms
#else
#define OSALMARRAY OsAllAlarms.OsAlarms
#endif

#endif /* (OSNUSERALMS > 0) */

/*  Private OS Services */
extern void  OSCheckAlarms( OSWORD ctrId );
extern void  OSCounterNotify( OSWORD ctrId );
#if defined(OSAPPLICATION)
#if (OSNUSERALMS > 0)
extern void OSKillAppAlarms(void);
#endif
#endif

/* prototypes */
#if (OSNALMS > 0)
extern void OSKillAlarm(OSAlmType alarmPtr);
extern void OSNotifyAlarmAction( OSALMACT *action );
extern void OSInsertAlarm( OSAlmType almId );
#endif 
#endif  /* OSNALMS > 0 */

#if defined(OSSCHEDULETABLES)
OSAlmType  OSProcessScheduleTable( OSSCTALMCB *almId );
#endif /* defined(OSSCHEDULETABLES) */

#if OSNUSERALMS > 0

/* OS Services  */

extern StatusType OS_GetAlarmBase( AlarmType almId, AlarmBaseRefType info );
extern StatusType OS_GetAlarm( AlarmType almId, TickRefType tickRef );
extern StatusType OS_SetRelAlarm( AlarmType almId, TickType increment, TickType cycle );
extern StatusType OS_SetAbsAlarm( AlarmType almId, TickType start, TickType cycle );
extern StatusType OS_CancelAlarm( AlarmType almId );

#if defined(OSMEMPROTECTION)

/* inline wrappers for OS services */

OSINLINE StatusType GetAlarmBase( AlarmType almId, AlarmBaseRefType info ) 
{
    return OSServiceCall2( StatusType, almId, info, GetAlarmBase );
}

OSINLINE StatusType GetAlarm( AlarmType almId, TickRefType tickRef )
{
    return OSServiceCall2( StatusType, almId, tickRef, GetAlarm );
}

OSINLINE StatusType SetRelAlarm( AlarmType almId, TickType increment, TickType cycle )
{
    return OSServiceCall3( StatusType, almId, increment, cycle, SetRelAlarm );
}

OSINLINE StatusType SetAbsAlarm( AlarmType almId, TickType start, TickType cycle )
{
    return OSServiceCall3( StatusType, almId, start, cycle, SetAbsAlarm );
}

OSINLINE StatusType CancelAlarm( AlarmType almId )
{
    return OSServiceCall1(StatusType, almId, CancelAlarm);
}

#else  /* defined(OSMEMPROTECTION) */
#define GetAlarmBase(almId, info)            OS_GetAlarmBase(almId, info)
#define GetAlarm(almId, tickRef)             OS_GetAlarm(almId, tickRef)
#define SetRelAlarm(almId, increment, cycle) OS_SetRelAlarm(almId, increment, cycle)
#define SetAbsAlarm(almId, start, cycle)     OS_SetAbsAlarm(almId, start, cycle)
#define CancelAlarm(almId)                   OS_CancelAlarm(almId )
#endif /* defined(OSMEMPROTECTION) */

#if defined(OSAUTOALARMS)
#define OSALMABSOLUTE ((OSBYTE)1)     /* Alarm absolute autostart type */
#define OSALMRELATIVE ((OSBYTE)2)     /* Alarm absolute autostart type */
#endif

#endif /* OSNUSERALMS > 0 */


/*** Schedule Tables ***/

#if defined(OSSCHEDULETABLES)

/* Bits in schedule table status (field in TagOSSCTCB struct) */ 
#define OSSCTCBDIRSIGN  ( (ScheduleTableStatusType)0x10 ) /* Schedule table correct.direction flag */
#define OSSCTCBSYNCUP   ( (ScheduleTableStatusType)0x20 ) /* Schedule table sync.correction flag */
#define OSSCTCBEND      ( (ScheduleTableStatusType)0x80 ) /* flag of Schedule table end (in the OSSCTCB status field) */
#define OSSCTCBSTATUS   ( (ScheduleTableStatusType)0x0F ) /* mask for Schedule table status bits */

#define OSSctCBGetStatus(s) ((s) & OSSCTCBSTATUS) /* get schedule table status */

#if (OSNUSERALMS == 0)
#define OSALMSCTARRAY OsSCTAlarms
#else
#define OSALMSCTARRAY OsAllAlarms.OsSCTAlarms
#endif

/* Bit flags in Schedule Table configuration 'state' field,used by sg only */ 
#define OSSCTCFGPERIODIC    ((ScheduleTableStatusType)0x1)  /* Schedule table is periodic */

#define OSSCTCFGIMPLICIT    ((ScheduleTableStatusType)0x2)  /* Sync strategy is implicit */
#define OSSCTCFGEXPLICIT    ((ScheduleTableStatusType)0x4)  /* Sync strategy is explicit */
/* Masks for Schedule Table configuration 'state' field */ 
#define OSSCTCFGPERIODICMASK    ((OSWORD)0x100)             /* Schedule table is periodic */

#define OSSCTCFGIMPLMASK        ((OSWORD)0x200)             /* Implicit strategy mask */
#define OSSCTCFGEXPLMASK        ((OSWORD)0x400)             /* Exlicit strategy mask */

/*  Configuration Data  */

extern const OSSCT OsScheduleTablesCfg[OSNSCTS];

#if defined(OSAUTOSCHEDULETABLES)
extern const OSSCTAUTOTYPE OsAutoScheduleTablesCfg[OSNAUTOSCTS];
#endif

/*  Private OS Services */
#if defined(OSNAUTOSCTS)
#if (OSNAPPMODES > 1)
extern void OSInitAutoScheduleTables(AppModeType mode);
#else   /* (OSNAPPMODES > 1) */
extern void OSInitAutoScheduleTables(void);
#endif  /* (OSNAPPMODES > 1) */
#endif /* defined(OSNAUTOSCTS) */

#if defined(OSAPPLICATION)
extern void OSKillAppScheduleTables(void);
#endif

/*  OS Services  */
extern StatusType OS_StartScheduleTableAbs( ScheduleTableType sctId, TickType tickValue );
extern StatusType OS_StartScheduleTableRel( ScheduleTableType sctId, TickType offset );
extern StatusType OS_StopScheduleTable( ScheduleTableType sctId );
extern StatusType OS_NextScheduleTable( ScheduleTableType sctId_current, ScheduleTableType sctId_next );

extern StatusType OS_StartScheduleTableSynchron( ScheduleTableType sctId );
extern StatusType OS_SyncScheduleTable( ScheduleTableType sctId, GlobalTimeTickType globalTime );
extern StatusType OS_SetScheduleTableAsync( ScheduleTableType sctId );

extern StatusType OS_GetScheduleTableStatus( ScheduleTableType sctId, ScheduleTableStatusRefType scheduleStatus );

#if defined(OSMEMPROTECTION)
/* inline wrappers for OS services */

OSINLINE StatusType StartScheduleTableAbs( ScheduleTableType sctId, TickType tickValue )
{
    return OSServiceCall2( StatusType, sctId, tickValue, StartScheduleTableAbs );
}
OSINLINE StatusType StartScheduleTableRel( ScheduleTableType sctId, TickType offset )
{
    return OSServiceCall2( StatusType, sctId, offset, StartScheduleTableRel );
}
OSINLINE StatusType StopScheduleTable( ScheduleTableType sctId )
{
   return OSServiceCall1( StatusType, sctId, StopScheduleTable );
}
OSINLINE StatusType NextScheduleTable( ScheduleTableType sctId_current, ScheduleTableType sctId_next )
{
    return OSServiceCall2( StatusType, sctId_current, sctId_next, NextScheduleTable );
}

OSINLINE StatusType StartScheduleTableSynchron( ScheduleTableType sctId )
{
    return OSServiceCall1( StatusType, sctId, StartScheduleTableSynchron );
}
OSINLINE StatusType SyncScheduleTable( ScheduleTableType sctId, GlobalTimeTickType globalTime )
{
    return OSServiceCall2( StatusType, sctId, globalTime, SyncScheduleTable );
}
OSINLINE StatusType SetScheduleTableAsync( ScheduleTableType sctId ) 
{
    return OSServiceCall1( StatusType, sctId, SetScheduleTableAsync );
}

OSINLINE StatusType GetScheduleTableStatus( ScheduleTableType sctId, ScheduleTableStatusRefType scheduleStatus )
{
    return OSServiceCall2( StatusType, sctId, scheduleStatus, GetScheduleTableStatus );
}

#else  /* defined(OSMEMPROTECTION) */

#define StartScheduleTableAbs(sctId, tickValue)       OS_StartScheduleTableAbs(sctId, tickValue)
#define StartScheduleTableRel(sctId, offset)          OS_StartScheduleTableRel(sctId, offset)
#define StopScheduleTable(sctId)                      OS_StopScheduleTable(sctId)
#define GetScheduleTableStatus(sctId, scheduleStatus) OS_GetScheduleTableStatus(sctId, scheduleStatus)
#define NextScheduleTable(sctId_current, sctId_next)  OS_NextScheduleTable(sctId_current, sctId_next)

#define StartScheduleTableSynchron(sctId)             OS_StartScheduleTableSynchron(sctId)
#define SyncScheduleTable(sctId, globalTime)          OS_SyncScheduleTable(sctId, globalTime)
#define SetScheduleTableAsync(sctId)                  OS_SetScheduleTableAsync(sctId)

#endif /* defined(OSMEMPROTECTION) */

#endif  /* defined(OSSCHEDULETABLES) */


#if (OSNALMS > 0)
/******************************************************************************
 * Function:    OSAbsTick value
 *
 * Description:
 *
 * Returns:     Absolute tick value
 *
 * Notes:
 *
 ******************************************************************************/
OSINLINE TickType OSAbsTickValue( OSWORD ctrInd, TickType rel )
{
#if defined(OSSWCOUNTER)
#if defined(OSHWCOUNTER)
    if( ctrInd >= OSNHWCTRS )
#endif
    {
        if( (OsCountersCfg[ctrInd].maxallowedvalue - OSSWCtrValue(ctrInd)) < rel )
        {
            rel -= (OsCountersCfg[ctrInd].maxallowedvalue - OSSWCtrValue(ctrInd) + 1);
        }
        else
        {
            rel += OSSWCtrValue(ctrInd);
        }        
    }
#endif  /* defined(OSSWCOUNTER) */
#if defined(OSHWCOUNTER)
#if defined(OSSWCOUNTER)
    else
#endif  /* defined(OSSWCOUNTER) */
    {
        OsTimVal = OSHWCtrValue( ctrInd ); /* set OsTimValue to the current counter value */ 

        if( (OsCounters[ctrInd].alarm != OSALM0) && OSInterruptRaised( ctrInd ) )
        { /* if there was an alarm and HW counter has crossed old OC value */
            OsTimVal = OSHWCtrGetOC( ctrInd ); /* set OsTimValue to the current value of the OC register */ 
                                               /* to achive valid comparision in OsSetAlarm */
            rel += OSHWCtrValue( ctrInd );
        }
        else
        {
            rel += OsTimVal;
        }
        rel = OSCTRBITS(rel);
    }
#endif  /* defined(OSHWCOUNTER) */

    return rel;
}

#if defined(OSHWCOUNTER)
/******************************************************************************
 * Function:    OSSetTimVal
 *
 * Description:
 *
 * Returns:
 *
 * Notes:
 *
 ******************************************************************************/
OSINLINE void OSSetTimVal( OSWORD ctrInd )
{
#if defined(OSSWCOUNTER)
    if( ctrInd < OSNHWCTRS )
#endif
    {
        OsTimVal = OSHWCtrValue( ctrInd ); /* set OsTimValue to the current counter value */
        if( OsCounters[ctrInd].alarm != OSALM0 )
        { /* if there was an alarm */
            if( OSInterruptRaised( ctrInd ) ) /* and HW counter has crossed old OC value */
            {                                       
                OsTimVal = OSHWCtrGetOC( ctrInd );  /* set OsTimValue to the current value of the OC register */ 
            }                                       /* to achive valid comparision in OsSetAlarm */
        }
    }
}
#else
#define OSSetTimVal( ctrInd )
#endif  /* defined(OSHWCOUNTER) */

#endif /* #if (OSNALMS > 0) */

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* OSALMAPI_H */
