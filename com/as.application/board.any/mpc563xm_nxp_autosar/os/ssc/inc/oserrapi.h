#ifndef OSERRAPI_H
#define OSERRAPI_H
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
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/inc/oserrapi.h,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  API for OSEK OS Error handling
*
* Notes:        
*
******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/*  Constants */
/*  Error codes */

/* #define E_OK                   ( (StatusType) 0 )    -- defined in osbasapi.h   */
#define E_OS_ACCESS               ( (StatusType) 1 )   /* Access to the service/object denied  */
#define E_OS_CALLEVEL             ( (StatusType) 2 )   /* Access to the service from the ISR is not permitted  */
#define E_OS_ID                   ( (StatusType) 3 )   /* Object ID is invalid */
#define E_OS_LIMIT                ( (StatusType) 4 )   /* Limit of services/objects exceeded   */
#define E_OS_NOFUNC               ( (StatusType) 5 )   /* The object is not used, service rejected */  
#define E_OS_RESOURCE             ( (StatusType) 6 )   /* Task still occupies resource */
#define E_OS_STATE                ( (StatusType) 7 )   /* The state of the object is not correct for the required service */
#define E_OS_VALUE                ( (StatusType) 8 )   /* Value outside of the admissible limit    */
#define E_OS_SERVICEID            ( (StatusType) 9 )   /* Service can not be called */

#define E_OS_ILLEGAL_ADDRESS      ( (StatusType)11 )   /* An invalid address is given as a parameter to a service */
#define E_OS_MISSINGEND           ( (StatusType)12 )   /* Tasks terminates without a TerminateTask() or ChainTask() call */
#define E_OS_DISABLEDINT          ( (StatusType)13 )   /* A service of the OS is called inside an interrupt disable/enable pair */
#define E_OS_STACKFAULT           ( (StatusType)14 )   /* A stack fault detected via stack monitoring by the OS */
#define E_OS_PROTECTION_MEMORY    ( (StatusType)15 )   /* A memory access violation occurred */
#define E_OS_PROTECTION_TIME      ( (StatusType)16 )   /* A Task/Category 2 ISR exceeds its execution time budget */
#define E_OS_PROTECTION_LOCKED    ( (StatusType)17 )   /* A Task/Category 2 ISR blocks for too long */
#define E_OS_PROTECTION_EXCEPTION ( (StatusType)18 )   /* A trap occurred */
#define E_OS_PROTECTION_ARRIVAL   ( (StatusType)19 )   /* A Task/Category 2 ISR arrives before its timeframe has expired */
#define E_OS_PROTECTION_ISR_ARRIVAL ( (StatusType)20 ) /* additioanal error code. It is used only by OS. */

/* Implementation specific error codes */
#define E_OS_SYS_FATAL            ( (StatusType)21 )   /* OS fatal error */
#define E_OS_SYS_RCWAIT           ( (StatusType)22 )   /* remote call wait code */
#define E_OS_SYS_ORDER            ( (StatusType)23 )   /* Incorrect order of function calling  */

/* Multicore error codes */

/* com errors - must be 32...63 */                                                
#define E_COM_ID                  ((StatusType)(3+32)) /* message or mode id is out of range or invalid    */
#define E_COM_NOMSG               ((StatusType)(9+32)) /* message queue is empty       */
#define E_COM_LIMIT               ((StatusType)(4+32)) /* overflow of message queue.   */
#define E_COM_LENGTH              ((StatusType)(8+32)) /* not used in internal COM     */


/* macros for ErrorHook */
#if !defined(OSHOOKERROR)
/* no sence to have it defined w/o ErrorHook */
#undef OSGETSERVICEID
#undef OSPARAMETERACCESS
#endif

#if (defined(OSPARAMETERACCESS) || defined(OSORTICURRENTSERVICEID)) && !defined(OSGETSERVICEID)
#define OSGETSERVICEID
#endif

#if defined(OSGETSERVICEID)
#define OSErrorGetServiceId()       OsService
#endif

#if !defined(OSCOMHOOKERROR)
/* no sence to have it defined w/o COMErrorHook */
#undef OSCOMGETSERVICEID
#undef OSCOMPARAMETERACCESS
#endif

#if defined(OSCOMPARAMETERACCESS) && !defined(OSCOMGETSERVICEID)
#define OSCOMGETSERVICEID
#endif


#if defined(OSORTICURRENTSERVICEID)  || defined(OSGETSERVICEID) || defined(OSCOMGETSERVICEID) || defined(OSCOMPARAMETERACCESS)

/* OSEK OS sevices groups identifiers */
#define OSSYSTEMSERVICEIDBASE        0x00   /* operating system execution control services */
#define OSTASKSERVICEIDBASE          0x20   /* task management services */
#define OSISRSERVICEIDBASE           0x30   /* interrupt handling services */
#define OSRESOURCESERVICEIDBASE      0x50   /* resource management services */
#define OSEVENTSERVICEIDBASE         0x60   /* event control services */
#define OSMESSAGESERVICEIDBASE       0x70   /* messages services */
#define OSCOUNTERSERVICEIDBASE       0x90   /* counters services */
#define OSALARMSERVICEIDBASE         0xA0   /* alarms services */
#define OSHOOKSERVICEIDBASE          0xB0   /* hook routines */
#define OSSCHEDULETABLESERVICEIDBASE 0xC0   /* schedule table routines */
#define OSMULTICORESERVICEIDBASE     0xD0   /* multicore routines */

#define OSServiceId_NoService                   (OSServiceIdType)0

/*  some services does not call ErrorHook but listed here */
                                               
#define OSServiceId_StartOS                     (OSServiceIdType)( OSSYSTEMSERVICEIDBASE + 0x02 )
#define OSServiceId_ShutdownOS                  (OSServiceIdType)( OSSYSTEMSERVICEIDBASE + 0x04 )
#define OSServiceId_GetActiveApplicationMode    (OSServiceIdType)( OSSYSTEMSERVICEIDBASE + 0x06 )
#define OSServiceId_GetApplicationID            (OSServiceIdType)( OSSYSTEMSERVICEIDBASE + 0x08 )
#define OSServiceId_CallTrustedFunction         (OSServiceIdType)( OSSYSTEMSERVICEIDBASE + 0x0A )
#define OSServiceId_CheckISRMemoryAccess        (OSServiceIdType)( OSSYSTEMSERVICEIDBASE + 0x0C )
#define OSServiceId_CheckTaskMemoryAccess       (OSServiceIdType)( OSSYSTEMSERVICEIDBASE + 0x0E )
#define OSServiceId_CheckObjectAccess           (OSServiceIdType)( OSSYSTEMSERVICEIDBASE + 0x10 )
#define OSServiceId_CheckObjectOwnership        (OSServiceIdType)( OSSYSTEMSERVICEIDBASE + 0x12 )
#define OSServiceId_TerminateApplication        (OSServiceIdType)( OSSYSTEMSERVICEIDBASE + 0x14 )
                                    /* task management services */
#define OSServiceId_ActivateTask                (OSServiceIdType)( OSTASKSERVICEIDBASE + 0x00 )
#define OSServiceId_TerminateTask               (OSServiceIdType)( OSTASKSERVICEIDBASE + 0x02 )
#define OSServiceId_ChainTask                   (OSServiceIdType)( OSTASKSERVICEIDBASE + 0x04 )
#define OSServiceId_Schedule                    (OSServiceIdType)( OSTASKSERVICEIDBASE + 0x06 )
#define OSServiceId_GetTaskID                   (OSServiceIdType)( OSTASKSERVICEIDBASE + 0x08 )
#define OSServiceId_GetTaskState                (OSServiceIdType)( OSTASKSERVICEIDBASE + 0x0A )
                                    /* interrupt handling services */
#define OSServiceId_ResumeAllInterrupts         (OSServiceIdType)( OSISRSERVICEIDBASE + 0x00 )
#define OSServiceId_SuspendAllInterrupts        (OSServiceIdType)( OSISRSERVICEIDBASE + 0x02 )
#define OSServiceId_ResumeOSInterrupts          (OSServiceIdType)( OSISRSERVICEIDBASE + 0x04 )
#define OSServiceId_SuspendOSInterrupts         (OSServiceIdType)( OSISRSERVICEIDBASE + 0x06 )
#define OSServiceId_EnableAllInterrupts         (OSServiceIdType)( OSISRSERVICEIDBASE + 0x08 )
#define OSServiceId_DisableAllInterrupts        (OSServiceIdType)( OSISRSERVICEIDBASE + 0x0A )
#define OSServiceId_EnableInterruptSource       (OSServiceIdType)( OSISRSERVICEIDBASE + 0x0C )
#define OSServiceId_DisableInterruptSource      (OSServiceIdType)( OSISRSERVICEIDBASE + 0x0E )
#define OSServiceId_GetISRID                    (OSServiceIdType)( OSISRSERVICEIDBASE + 0x10 )
                                    /* resource management services */
#define OSServiceId_GetResource                 (OSServiceIdType)( OSRESOURCESERVICEIDBASE + 0x00 )
#define OSServiceId_ReleaseResource             (OSServiceIdType)( OSRESOURCESERVICEIDBASE + 0x02 )
                                    /* event control services */
#define OSServiceId_SetEvent                    (OSServiceIdType)( OSEVENTSERVICEIDBASE + 0x00 )
#define OSServiceId_ClearEvent                  (OSServiceIdType)( OSEVENTSERVICEIDBASE + 0x02 )
#define OSServiceId_GetEvent                    (OSServiceIdType)( OSEVENTSERVICEIDBASE + 0x04 )
#define OSServiceId_WaitEvent                   (OSServiceIdType)( OSEVENTSERVICEIDBASE + 0x06 )
                                    /* message services - used only for ORTI */
#define OSServiceId_SendMessage                 (OSServiceIdType)( OSMESSAGESERVICEIDBASE + 0x00 )
#define OSServiceId_ReceiveMessage              (OSServiceIdType)( OSMESSAGESERVICEIDBASE + 0x02 )
#define OSServiceId_GetMessageStatus            (OSServiceIdType)( OSMESSAGESERVICEIDBASE + 0x08 )
#define OSServiceId_StartCOM                    (OSServiceIdType)( OSMESSAGESERVICEIDBASE + 0x0A )
#define OSServiceId_StopCOM                     (OSServiceIdType)( OSMESSAGESERVICEIDBASE + 0x0C )
#define OSServiceId_ReadFlag                    (OSServiceIdType)( OSMESSAGESERVICEIDBASE + 0x12 )
#define OSServiceId_ResetFlag                   (OSServiceIdType)( OSMESSAGESERVICEIDBASE + 0x14 )
#define OSServiceId_GetCOMApplicationMode       (OSServiceIdType)( OSMESSAGESERVICEIDBASE + 0x16 )
#define OSServiceId_InitMessage                 (OSServiceIdType)( OSMESSAGESERVICEIDBASE + 0x18 )

#if (OSNMSGS > 0)
typedef enum   
{ 
    COMServiceId_SendMessage           =        OSServiceId_SendMessage,
    COMServiceId_ReceiveMessage        =        OSServiceId_ReceiveMessage,
    COMServiceId_GetMessageStatus      =        OSServiceId_GetMessageStatus,
    COMServiceId_StartCOM              =        OSServiceId_StartCOM,
    COMServiceId_StopCOM               =        OSServiceId_StopCOM,
    COMServiceId_GetCOMApplicationMode =        OSServiceId_GetCOMApplicationMode,
    COMServiceId_InitMessage           =        OSServiceId_InitMessage,
    COMServiceId_ReadFlag              =        OSServiceId_ReadFlag,
    COMServiceId_ResetFlag             =        OSServiceId_ResetFlag
} COMServiceIdType;
#endif /* (OSNMSGS > 0) */
                                    /* counters services */
#define OSServiceId_InitCounter                 (OSServiceIdType)( OSCOUNTERSERVICEIDBASE + 0x00 )
#define OSServiceId_IncrementCounter            (OSServiceIdType)( OSCOUNTERSERVICEIDBASE + 0x02 )
#define OSServiceId_GetCounterValue             (OSServiceIdType)( OSCOUNTERSERVICEIDBASE + 0x04 )
#define OSServiceId_GetElapsedCounterValue      (OSServiceIdType)( OSCOUNTERSERVICEIDBASE + 0x06 )
#define OSServiceId_GetCounterInfo              (OSServiceIdType)( OSCOUNTERSERVICEIDBASE + 0x08 )
                                    /* alarms services */
#define OSServiceId_GetAlarmBase                (OSServiceIdType)( OSALARMSERVICEIDBASE + 0x00 )
#define OSServiceId_GetAlarm                    (OSServiceIdType)( OSALARMSERVICEIDBASE + 0x02 )
#define OSServiceId_SetRelAlarm                 (OSServiceIdType)( OSALARMSERVICEIDBASE + 0x04 )
#define OSServiceId_SetAbsAlarm                 (OSServiceIdType)( OSALARMSERVICEIDBASE + 0x06 )
#define OSServiceId_CancelAlarm                 (OSServiceIdType)( OSALARMSERVICEIDBASE + 0x08 )
                                    /* hook routines */
#define OSServiceId_ErrorHook                    (OSServiceIdType)( OSHOOKSERVICEIDBASE + 0x00 )
#define OSServiceId_PreTaskHook                  (OSServiceIdType)( OSHOOKSERVICEIDBASE + 0x02 )
#define OSServiceId_PostTaskHook                 (OSServiceIdType)( OSHOOKSERVICEIDBASE + 0x04 )
#define OSServiceId_StartupHook                  (OSServiceIdType)( OSHOOKSERVICEIDBASE + 0x06 )
#define OSServiceId_ShutdownHook                 (OSServiceIdType)( OSHOOKSERVICEIDBASE + 0x08 )
#define OSServiceId_IdleLoopHook                 (OSServiceIdType)( OSHOOKSERVICEIDBASE + 0x0A )      /* extra service */
#define OSServiceId_COMErrorHook                 (OSServiceIdType)( OSHOOKSERVICEIDBASE + 0x0C )
#define OSServiceId_ProtectionHook               (OSServiceIdType)( OSHOOKSERVICEIDBASE + 0x0E )
                                    /* schedule table routines */
#define OSServiceId_StartScheduleTableAbs       (OSServiceIdType)( OSSCHEDULETABLESERVICEIDBASE + 0x00 )
#define OSServiceId_StartScheduleTableRel       (OSServiceIdType)( OSSCHEDULETABLESERVICEIDBASE + 0x02 )
#define OSServiceId_StopScheduleTable           (OSServiceIdType)( OSSCHEDULETABLESERVICEIDBASE + 0x04 )
#define OSServiceId_NextScheduleTable           (OSServiceIdType)( OSSCHEDULETABLESERVICEIDBASE + 0x06 )
#define OSServiceId_SyncScheduleTable           (OSServiceIdType)( OSSCHEDULETABLESERVICEIDBASE + 0x08 )
#define OSServiceId_SetScheduleTableAsync       (OSServiceIdType)( OSSCHEDULETABLESERVICEIDBASE + 0x0A )
#define OSServiceId_GetScheduleTableStatus      (OSServiceIdType)( OSSCHEDULETABLESERVICEIDBASE + 0x0C )
#define OSServiceId_StartScheduleTableSynchron  (OSServiceIdType)( OSSCHEDULETABLESERVICEIDBASE + 0x0E )
                                    /* multicore routines */
#define OSServiceId_GetSpinlock                 (OSServiceIdType)( OSMULTICORESERVICEIDBASE + 0x00 )
#define OSServiceId_TryToGetSpinlock            (OSServiceIdType)( OSMULTICORESERVICEIDBASE + 0x02 )
#define OSServiceId_ReleaseSpinlock             (OSServiceIdType)( OSMULTICORESERVICEIDBASE + 0x04 )
#define OSServiceId_GetCoreID                   (OSServiceIdType)( OSMULTICORESERVICEIDBASE + 0x06 )
#define OSServiceId_StartCore                   (OSServiceIdType)( OSMULTICORESERVICEIDBASE + 0x08 )
#define OSServiceId_StartNonAUTOSARCore         (OSServiceIdType)( OSMULTICORESERVICEIDBASE + 0x0A )
#endif  /* defined(OSGETSERVICEID) */


#if defined(OSPARAMETERACCESS)
/* macros for access of OS services 1st parameter */
                                   /* task management services */
#define OSError_StartOS_Mode()              (AppModeType)OsObjId
#define OSError_ActivateTask_TaskID()       (TaskType)OsObjId
#define OSError_ChainTask_TaskID()          (TaskType)OsObjId                   
#define OSError_GetTaskState_TaskID()       (TaskType)OsObjId                
                                   /* resource management services */
#define OSError_GetResource_ResID()         (ResourceType)OsObjId
#define OSError_ReleaseResource_ResID()     (ResourceType)OsObjId             
                                   /* event control services */
#define OSError_SetEvent_TaskID()           (TaskType)OsObjId                    
#define OSError_GetEvent_TaskID()           (TaskType)OsObjId                    
                                   /* messages services moved into osmsgapi.h */

                                   /* alarms services */
#define OSError_GetAlarmBase_AlarmID()      (AlarmType)OsObjId                
#define OSError_GetAlarm_AlarmID()          (AlarmType)OsObjId                    
#define OSError_SetRelAlarm_AlarmID()       (AlarmType)OsObjId                 
#define OSError_SetAbsAlarm_AlarmID()       (AlarmType)OsObjId                 
#define OSError_CancelAlarm_AlarmID()       (AlarmType)OsObjId                 
                                   /* counters services */
#define OSError_InitCounter_CounterID()     (CounterType)OsObjId                 
#define OSError_IncrementCounter_CounterID() (CounterType)OsObjId              
#define OSError_GetCounterValue_CounterID() (CounterType)OsObjId             
#define OSError_GetCounterInfo_CounterID()  (CounterType)OsObjId              
                                   /* ScheduleTable */
#define OSError_StartScheduleTableAbs_ScheduleTableID() (ScheduleTableType)OsObjId    
#define OSError_StartScheduleTableRel_ScheduleTableID() (ScheduleTableType)OsObjId    
#define OSError_StopScheduleTable_ScheduleTableID()     (ScheduleTableType)OsObjId    
#define OSError_NextScheduleTable_ScheduleTableID()     (ScheduleTableType)OsObjId    
#define OSError_StartScheduleTableSynchron_ScheduleTableID() (ScheduleTableType)OsObjId    
#define OSError_SyncScheduleTable_ScheduleTableID()     (ScheduleTableType)OsObjId    
#define OSError_SetScheduleTableAsync_ScheduleTableID() (ScheduleTableType)OsObjId    
#define OSError_GetScheduleTableStatus_ScheduleTableID() (ScheduleTableType)OsObjId    

#endif  /* defined(OSPARAMETERACCESS) */


#if defined(OSGETSERVICEID) || defined(OSPARAMETERACCESS)

#define OSPUTPARAM(ID, parm) \
    if( OsService == OSServiceId_NoService ) \
    { \
        OsService = ID; OsObjId = (OSDWORD)parm; \
    }

#define OSCLEARPARAM() (OsService = OSServiceId_NoService)

#else   /* defined(OSGETSERVICEID) || defined(OSPARAMETERACCESS) */

#define OSPUTPARAM(ID, parm)
#define OSCLEARPARAM()

#endif  /* defined(OSGETSERVICEID) || defined(OSPARAMETERACCESS) */

#if(OSORTIDEBUGLEVEL > 0)
#define OSPUTERROR( error ) OsLastError = error;  
#else  /* (OSORTIDEBUGLEVEL > 0 ) */
#define OSPUTERROR( error )  
#endif /* (OSORTIDEBUGLEVEL > 0 ) */

#if (OSORTIDEBUGLEVEL != 0)

/* set Task Id in special variable and generate OTM for SC1,2 */
#if defined(OSUSETCB)

#if defined(OSMEMPROTECTION) || (OSORTIDEBUGLEVEL == OSORTIDEBUGLEVELSTATIC)
#define OSOrtiSetRunningId() OsOrtiRunning = OsRunning->taskId
#else
#define OSOrtiSetRunningId() OsOrtiRunning = OsRunning->taskId; OSSetPID0( OsOrtiRunning )
#endif 	

#else  /* defined(OSUSETCB) */

#if (OSORTIDEBUGLEVEL == OSORTIDEBUGLEVELSTATIC)
#define OSOrtiSetRunningId() OsOrtiRunning = (OSBYTE)OsRunning
#else
#define OSOrtiSetRunningId() OsOrtiRunning = (OSBYTE)OsRunning; OSSetPID0( OsOrtiRunning )
#endif 	

#endif /* defined(OSUSETCB) */
	
#else  /* (OSORTIDEBUGLEVEL != 0) */
#define OSOrtiSetRunningId()
#endif /* (OSORTIDEBUGLEVEL != 0) */


#if defined(OSHOOKERROR)
#define OSHOOK_START_SEC_CODE
#include "ossections.h"
void ErrorHook( StatusType error );
#define OSTEXT_START_SEC_CODE
#include "ossections.h"
#endif


#if defined(OSHOOKERROR) || defined(OSAPPHOOKERROR)
extern void OSErrorHook_noPar( StatusType error );

#if defined(OSGETSERVICEID) || defined(OSPARAMETERACCESS)
extern void OSErrorHook( StatusType error, OSServiceIdType ID, OSObjectType param );
#else
extern void OSErrorHook_1( StatusType error );
#define OSErrorHook( error, ID, param ) OSErrorHook_1( error )
#endif

#define OSRETERROR( error, ID, param ) \
    OSErrorHook( error, ID, param ); \
    OSOrtiServiceWatchOnExit( ID ); \
    return(error)

#else  /* defined(OSHOOKERROR) || defined(OSAPPHOOKERROR)*/

#define OSRETERROR( error, ID, param )  \
    OSPUTERROR( error ); \
    OSOrtiServiceWatchOnExit( ID ); \
    return( error )

#define OSErrorHook_noPar( error )
#endif /* defined(OSHOOKERROR) || defined(OSAPPHOOKERROR) */

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* OSERRAPI_H */
