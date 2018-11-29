/*
 *  TOPPERS ATK2
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *      Automotive Kernel Version 2
 *
 *  Copyright (C) 2011-2015 by Center for Embedded Computing Systems
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2011-2015 by FUJI SOFT INCORPORATED, JAPAN
 *  Copyright (C) 2011-2013 by Spansion LLC, USA
 *  Copyright (C) 2011-2015 by NEC Communication Systems, Ltd., JAPAN
 *  Copyright (C) 2011-2015 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
 *  Copyright (C) 2011-2014 by Renesas Electronics Corporation, JAPAN
 *  Copyright (C) 2011-2015 by Sunny Giken Inc., JAPAN
 *  Copyright (C) 2011-2015 by TOSHIBA CORPORATION, JAPAN
 *  Copyright (C) 2011-2015 by Witz Corporation
 *  Copyright (C) 2014-2015 by AISIN COMCRUISE Co., Ltd., JAPAN
 *  Copyright (C) 2014-2015 by eSOL Co.,Ltd., JAPAN
 *  Copyright (C) 2014-2015 by SCSK Corporation, JAPAN
 *  Copyright (C) 2015 by SUZUKI MOTOR CORPORATION
 *  Copyright (C) 2016 by Fan Wang(parai@foxmail.com), China
 * 
 * The above copyright holders grant permission gratis to use,
 * duplicate, modify, or redistribute (hereafter called use) this
 * software (including the one made by modifying this software),
 * provided that the following four conditions (1) through (4) are
 * satisfied.
 * 
 * (1) When this software is used in the form of source code, the above
 *    copyright notice, this use conditions, and the disclaimer shown
 *    below must be retained in the source code without modification.
 *
 * (2) When this software is redistributed in the forms usable for the
 *    development of other software, such as in library form, the above
 *    copyright notice, this use conditions, and the disclaimer shown
 *    below must be shown without modification in the document provided
 *    with the redistributed software, such as the user manual.
 *
 * (3) When this software is redistributed in the forms unusable for the
 *    development of other software, such as the case when the software
 *    is embedded in a piece of equipment, either of the following two
 *    conditions must be satisfied:
 *
 *  (a) The above copyright notice, this use conditions, and the
 *      disclaimer shown below must be shown without modification in
 *      the document provided with the redistributed software, such as
 *      the user manual.
 *
 *  (b) How the software is to be redistributed must be reported to the
 *      TOPPERS Project according to the procedure described
 *      separately.
 *
 * (4) The above copyright holders and the TOPPERS Project are exempt
 *    from responsibility for any type of damage directly or indirectly
 *    caused from the use of this software and are indemnified by any
 *    users or end users of this software from any and all causes of
 *    action whatsoever.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS." THE ABOVE COPYRIGHT HOLDERS AND
 * THE TOPPERS PROJECT DISCLAIM ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, ITS APPLICABILITY TO A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS AND THE
 * TOPPERS PROJECT BE LIABLE FOR ANY TYPE OF DAMAGE DIRECTLY OR
 * INDIRECTLY CAUSED FROM THE USE OF THIS SOFTWARE.
 *
 *  $Id: Os.h 520 2015-12-24 12:19:40Z witz-itoyo $
 */
 
/*
 *		ATK2 OS header file
 *
 * Header file that contains ATK2 and is a system service that supports declaration, 
 * required data types, constants, the definition of the macro
 *
 * When you include this file from the assembly language source file is, by this 
 * to be defined the TOPPERS_MACRO_ONLY, so that except for the non-macro definition
 *
 * No files that should be included before including this file
 */

#ifndef TOPPERS_OS_H
#define TOPPERS_OS_H

#ifdef TOPPERS_TRUSTED
#define TOPPERS_SVC_FUNCCALL
#endif

#if defined(TOPPERS_TRUSTED) && defined(TOPPERS_NON_TRUSTED)
#error "both TOPPERS_TRUSTED and TOPPERS_NON_TRUSTED are defined!"
#endif

/*
 *  Common data types, constants, macros
 */
#include "Std_Types.h"
#include "MemMap.h"
#include "portable.h"

#ifndef TOPPERS_MACRO_ONLY

/*
 *  AUTOSAR standard type definitions
 */

/*
 *  Type definiton
 */
typedef uint8 	StatusType;						/* return status of OS API call */
typedef uint8	TaskStateType;                  /* task state */
typedef uint32	EventMaskType;                  /* event mask */
typedef uint32	TickType;                       /* counter value in tick */
typedef uint32	AppModeType;                    /* applicantion mode */
typedef uint8	OSServiceIdType;                /* system service ID */
typedef uint8	ScheduleTableStatusType;        /* schedule table state */
typedef uint8	ProtectionReturnType;           /* the return value from protection hook */
typedef uintptr	MemorySizeType;                 /* memory area size */
typedef uint8	ApplicationType;                /* OS application ID */
typedef uint8	ObjectTypeType;                 /* OS object type */
typedef uint8	ApplicationStateType;           /* OS applicantion state */
typedef uint8	AccessType;                     /* memory access rights */
typedef boolean	ObjectAccessType;               /* OS object access rights */
typedef uint8	RestartType;                    /* OSAP restart attribute */
typedef uint8	MonitoringType;                 /* monitoring project */

typedef struct {
	TickType	maxallowedvalue;                /* Counter-specified maximum value*/
	TickType	ticksperbase;                   /* OS counter increase number of ticks per base cycle */
	TickType	mincycle;                       /* Cycle specified minimum value*/
} AlarmBaseType;

/*
 *  To optimize, dependent part redefinition  type
 */
#ifndef OMIT_DATA_TYPE
typedef uint32	TimeType;                       /* Time */
typedef uint32	AlarmType;                      /* Alarm ID */
typedef uint32	ResourceType;                   /* Resource ID */
typedef uint32	TaskType;                       /* Task ID */
typedef uint32	ISRType;                        /* ISR ID */
typedef uint32	CounterType;                    /* Counter ID */
typedef uint32	ScheduleTableType;              /* Schedule table ID */
typedef float32	PhysicalTimeType;               /* (And for the conversion from tick time) time*/
typedef uint32	IocType;                        /* IOC ID */
typedef uint8	SenderIdType;                   /* Sender ID */
typedef uint32	TrustedFunctionIndexType;       /* Trusted Function Index */
#endif /* OMIT_DATA_TYPE */

typedef AlarmBaseType *				AlarmBaseRefType;
typedef TaskType *					TaskRefType;
typedef TaskStateType *				TaskStateRefType;
typedef EventMaskType *				EventMaskRefType;
typedef TickType *					TickRefType;
typedef ScheduleTableStatusType *	ScheduleTableStatusRefType;
typedef ApplicationStateType *		ApplicationStateRefType;
typedef void *						MemoryStartAddressType;             /* memory area start address */
typedef void *						TrustedFunctionParameterRefType;    /* Trusted Function Parameter */

/*
 *  Type of processing unit that caused the protection violation
 */
typedef uint8 FaultyContextType;

/*
 *  Macro for OS object declaration
 */
#define DeclareTask(TaskIdentifier)
#define DeclareResource(ResourceIdentifier)
#define DeclareEvent(EventIdentifier)
#define DeclareAlarm(AlarmIdentifier)

/*
 *  Macro for the main routine definition
 */
#define TASK(TaskName)		void TaskMain ## TaskName(void)
#define ISR(ISRName)		void ISRMain ## ISRName(void)
#ifndef C1ISR
#define C1ISR(ISRName)	void C1ISRMain ## ISRName(void)
#endif /* C1ISR */

#define TRUSTEDFUNCTION(TrustedFunctionName, FunctionIndex, FunctionParams)	\
	StatusType TrustedFunctionName(											\
		TrustedFunctionIndexType FunctionIndex,								\
		TrustedFunctionParameterRefType FunctionParams						\
		)

/*
 *  Type definition for the memory area reservation
 */
#ifndef TOPPERS_STK_T
#define TOPPERS_STK_T	sintptr
#endif /* TOPPERS_STK_T */
typedef	TOPPERS_STK_T StackType;    /* Type for securing a stack area */

/*
 *  Definitions for the system service parameter acquisition
 */
typedef union {
	TaskType						tskid;
	TaskRefType						p_tskid;
	TaskStateRefType				p_stat;
	ResourceType					resid;
	EventMaskType					mask;
	EventMaskRefType				p_mask;
	AlarmType						almid;
	AlarmBaseRefType				p_info;
	TickRefType						p_tick;
	TickRefType						p_val;
	TickRefType						p_eval;
	TickType						incr;
	TickType						cycle;
	TickType						start;
	AppModeType						mode;
	CounterType						cntid;
	ScheduleTableType				schtblid;
	TickType						offset;
	ScheduleTableType				schtblid_from;
	ScheduleTableType				schtblid_to;
	ScheduleTableStatusRefType		p_schtblstate;
	StatusType						error;
	ISRType							isrid;
	IocType							iocid;
	SenderIdType					senderid;
	TrustedFunctionIndexType		tfnid;
	TrustedFunctionParameterRefType	tfnpr;
	MemoryStartAddressType			adr;
	MemorySizeType					sz;
	ApplicationType					applid;
	ApplicationStateRefType			p_appstat;
	RestartType						restartoption;
} _ErrorHook_Par;


/*
 *  Macros for memory area securing
 *
 *  Defining the following TOPPERS_COUNT_SZ and TOPPERS_ROUND_SZ assumes 
 *  that the unit is a power of the width of two.
 */
#ifndef TOPPERS_COUNT_SZ
#define TOPPERS_COUNT_SZ(sz, unit)	((((sz) + (unit)) - (1U)) / (unit))
#endif /* TOPPERS_COUNT_SZ */
#ifndef TOPPERS_ROUND_SZ
#define TOPPERS_ROUND_SZ(sz, unit)	((((sz) + (unit)) - (1U)) & (~((unit) - (1U))))
#endif /* TOPPERS_ROUND_SZ */

#define COUNT_STK_T(sz)		(TOPPERS_COUNT_SZ((sz), sizeof(StackType)))
#define ROUND_STK_T(sz)		(TOPPERS_ROUND_SZ((sz), sizeof(StackType)))

/*
 *  Hook routine
 */
#ifdef CFG_USE_ERRORHOOK
extern void ErrorHook(StatusType Error);
#endif /* CFG_USE_ERRORHOOK */

#ifdef CFG_USE_PRETASKHOOK
extern void PreTaskHook(void);
#endif /* CFG_USE_PRETASKHOOK */

#ifdef CFG_USE_POSTTASKHOOK
extern void PostTaskHook(void);
#endif /* CFG_USE_POSTTASKHOOK */

#ifdef CFG_USE_STARTUPHOOK
extern void StartupHook(void);
#endif /* CFG_USE_STARTUPHOOK */

#ifdef CFG_USE_SHUTDOWNHOOK
extern void ShutdownHook(StatusType Error);
#endif /* CFG_USE_SHUTDOWNHOOK */

#ifdef CFG_USE_PROTECTIONHOOK
extern ProtectionReturnType ProtectionHook(StatusType FatalError);
#endif /* CFG_USE_PROTECTIONHOOK */

/*
 *  System services to be provided by the library
 */
extern ObjectAccessType CheckObjectAccess(ApplicationType ApplID, ObjectTypeType ObjectType, ...);
extern ApplicationType CheckObjectOwnership(ObjectTypeType ObjectType, ...);

/*
 *  File name, variable for the reference line number
 */
extern const char8	*fatal_file_name;   /* file name */
extern sint32		fatal_line_num;     /* line number */

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  Definitions and declarations for the system service call
 */
#include "kernel_fncode.h"              /* The definition of the function code */
#include "svc_funccall.h"               /* system service call definition  */

/*
 *  OS error code
 */
#define E_OS_ACCESS							UINT_C(1)
#define E_OS_CALLEVEL						UINT_C(2)
#define E_OS_ID								UINT_C(3)
#define E_OS_LIMIT							UINT_C(4)
#define E_OS_NOFUNC							UINT_C(5)
#define E_OS_RESOURCE						UINT_C(6)
#define E_OS_STATE							UINT_C(7)
#define E_OS_VALUE							UINT_C(8)
#define E_OS_SERVICEID						UINT_C(9)
#define E_OS_ILLEGAL_ADDRESS				UINT_C(10)
#define E_OS_MISSINGEND						UINT_C(11)
#define E_OS_DISABLEDINT					UINT_C(12)
#define E_OS_STACKFAULT						UINT_C(13)
#define E_OS_PROTECTION_MEMORY				UINT_C(14)
#define E_OS_PROTECTION_TIME_TASK			UINT_C(15)
#define E_OS_PROTECTION_TIME_ISR			UINT_C(16)
#define E_OS_PROTECTION_ARRIVAL_TASK		UINT_C(17)
#define E_OS_PROTECTION_ARRIVAL_ISR			UINT_C(18)
#define E_OS_PROTECTION_LOCKED_RESOURCE		UINT_C(19)
#define E_OS_PROTECTION_LOCKED_OSINT		UINT_C(20)
#define E_OS_PROTECTION_LOCKED_ALLINT		UINT_C(21)
#define E_OS_PROTECTION_EXCEPTION			UINT_C(22)
#define E_OS_PROTECTION_FATAL				UINT_C(23)
#define E_OS_MODE							UINT_C(24)
#define E_OS_SHUTDOWN_FATAL					UINT_C(25)
#define E_OS_PARAM_POINTER					UINT_C(26)
#define E_OS_SYS_ASSERT_FATAL				UINT_C(27)
#define E_OS_STACKINSUFFICIENT				UINT_C(28)
#define E_OS_CORE							UINT_C(29)
#define E_OS_SPINLOCK						UINT_C(30)
#define E_OS_INTERFERENCE_DEADLOCK			UINT_C(31)
#define E_OS_NESTING_DEADLOCK				UINT_C(32)
#define E_OS_SHUTDOWN_OTHER_CORE			UINT_C(33)
#define E_OS_TIMEINSUFFICIENT				UINT_C(34)
#define E_OS_PROTECTION_TIMEWINDOW			UINT_C(35)
#define E_OS_PROTECTION_COUNT_ISR			UINT_C(36)

/* Compatibility consideration of the AUTOSAR specification R4.0.3 */
#define OS_E_PARAM_POINTER					E_OS_PARAM_POINTER

#define ERRCODE_NUM							UINT_C(36) /* Number of error code */
/*
 *  IOC error code
 */
#define IOC_E_OK			UINT_C(0)
#define IOC_E_NOK			UINT_C(1)
#define IOC_E_LIMIT			UINT_C(130)
#define IOC_E_LOST_DATA		UINT_C(64)
#define IOC_E_NO_DATA		UINT_C(131)

/*
 *  Other constant values
 */
#define UINT32_INVALID		UINT_C(0xffffffff)
#define UINT8_INVALID		UINT_C(0xff)

#define SUSPENDED			((TaskStateType) 0) /* Hibernation */
#define RUNNING				((TaskStateType) 1) /* Execution state */
#define READY				((TaskStateType) 2) /* Executable state */
#define WAITING				((TaskStateType) 3) /* Wait state */

/*
 *  Timing protection for numerical
 */
#define NON_MONITORING				((MonitoringType) 0)        /* It is not monitoring */
#define TASK_MONITORING				((MonitoringType) 1)        /* Task execution time monitoring */
#define RESOURCE_MONITORING			((MonitoringType) 2)        /* Resource occupation time monitoring */
#define LOCKOSINT_MONITORING		((MonitoringType) 3)        /* OS interrupt disable time monitoring */

#define ARRIVAL_TASK		UINT_C(0x00)        /* Task start */
#define ARRIVAL_C2ISR		UINT_C(0x01)        /* C2ISR start */

/*
 *  To optimize, it must be re-defined in the dependent part
 */
#ifndef OMIT_DATA_TYPE
#define INVALID_TASK			((TaskType) UINT32_INVALID)
#define INVALID_ISR				((ISRType) UINT32_INVALID)
#endif /* OMIT_DATA_TYPE */
#define INVALID_APPMODETYPE		((AppModeType) UINT32_INVALID)
#define INVALID_OSAPPLICATION	((ApplicationType) UINT8_INVALID)

/*
 *  Status defined for schedule table
 */
#define SCHEDULETABLE_STOPPED					((ScheduleTableStatusType) 0x01)
#define SCHEDULETABLE_NEXT						((ScheduleTableStatusType) 0x02)
#define SCHEDULETABLE_WAITING					((ScheduleTableStatusType) 0x04)
#define SCHEDULETABLE_RUNNING					((ScheduleTableStatusType) 0x08)
#define SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS	((ScheduleTableStatusType) 0x10)

/*
 *  The state of the OS application
 */
#define APPLICATION_ACCESSIBLE	((ApplicationStateType) 0)  /* Available state */
#define APPLICATION_RESTARTING	((ApplicationStateType) 1)  /* Restart state */
#define APPLICATION_TERMINATED	((ApplicationStateType) 2)  /* Application termination state */

/*
 *  Access information
 */
#define ACCESS		(TRUE)
#define NO_ACCESS	(FALSE)

/*
 *  System Services ID
 */
#define OSServiceId_GetApplicationID			((OSServiceIdType) 0x00)
#define OSServiceId_GetISRID					((OSServiceIdType) 0x01)
#define OSServiceId_CallTrustedFunction			((OSServiceIdType) 0x02)
#define OSServiceId_CheckISRMemoryAccess		((OSServiceIdType) 0x03)
#define OSServiceId_CheckTaskMemoryAccess		((OSServiceIdType) 0x04)
#define OSServiceId_StartScheduleTableRel		((OSServiceIdType) 0x07)
#define OSServiceId_StartScheduleTableAbs		((OSServiceIdType) 0x08)
#define OSServiceId_StopScheduleTable			((OSServiceIdType) 0x09)
#define OSServiceId_NextScheduleTable			((OSServiceIdType) 0x0a)
#define OSServiceId_GetScheduleTableStatus		((OSServiceIdType) 0x0e)
#define OSServiceId_IncrementCounter			((OSServiceIdType) 0x0f)
#define OSServiceId_GetCounterValue				((OSServiceIdType) 0x10)
#define OSServiceId_GetElapsedValue				((OSServiceIdType) 0x11)
#define OSServiceId_TerminateApplication		((OSServiceIdType) 0x12)
#define OSServiceId_AllowAccess					((OSServiceIdType) 0x13)
#define OSServiceId_GetApplicationState			((OSServiceIdType) 0x14)
#define IOCServiceId_IOC_Send					((OSServiceIdType) 0x1e)
#define IOCServiceId_IOC_Write					((OSServiceIdType) 0x1f)
#define IOCServiceId_IOC_SendGroup				((OSServiceIdType) 0x20)
#define IOCServiceId_IOC_WriteGroup				((OSServiceIdType) 0x21)
#define IOCServiceId_IOC_Receive				((OSServiceIdType) 0x22)
#define IOCServiceId_IOC_Read					((OSServiceIdType) 0x23)
#define IOCServiceId_IOC_ReceiveGroup			((OSServiceIdType) 0x24)
#define IOCServiceId_IOC_ReadGroup				((OSServiceIdType) 0x25)
#define IOCServiceId_IOC_EmptyQueue				((OSServiceIdType) 0x26)

#define OSServiceId_EnableInterruptSource		((OSServiceIdType) 0xa0)
#define OSServiceId_DisableInterruptSource		((OSServiceIdType) 0xa1)
#define OSServiceId_CheckTaskAccess				((OSServiceIdType) 0xa2)
#define OSServiceId_CheckISRAccess				((OSServiceIdType) 0xa3)
#define OSServiceId_CheckAlarmAccess			((OSServiceIdType) 0xa4)
#define OSServiceId_CheckResourceAccess			((OSServiceIdType) 0xa5)
#define OSServiceId_CheckCounterAccess			((OSServiceIdType) 0xa6)
#define OSServiceId_CheckScheduleTableAccess	((OSServiceIdType) 0xa7)
#define OSServiceId_CheckTaskOwnership			((OSServiceIdType) 0xa9)
#define OSServiceId_CheckISROwnership			((OSServiceIdType) 0xaa)
#define OSServiceId_CheckAlarmOwnership			((OSServiceIdType) 0xab)
#define OSServiceId_CheckCounterOwnership		((OSServiceIdType) 0xac)
#define OSServiceId_CheckScheduleTableOwnership	((OSServiceIdType) 0xad)
#define OSServiceId_TaskMissingEnd				((OSServiceIdType) 0xaf)
#define OSServiceId_ISRMissingEnd				((OSServiceIdType) 0xb0)
#define OSServiceId_HookMissingEnd				((OSServiceIdType) 0xb1)

#define OSServiceId_ActivateTask				((OSServiceIdType) 0xe0)
#define OSServiceId_TerminateTask				((OSServiceIdType) 0xe1)
#define OSServiceId_ChainTask					((OSServiceIdType) 0xe2)
#define OSServiceId_Schedule					((OSServiceIdType) 0xe3)
#define OSServiceId_GetTaskID					((OSServiceIdType) 0xe4)
#define OSServiceId_GetTaskState				((OSServiceIdType) 0xe5)
#define OSServiceId_EnableAllInterrupts			((OSServiceIdType) 0xe6)
#define OSServiceId_DisableAllInterrupts		((OSServiceIdType) 0xe7)
#define OSServiceId_ResumeAllInterrupts			((OSServiceIdType) 0xe8)
#define OSServiceId_SuspendAllInterrupts		((OSServiceIdType) 0xe9)
#define OSServiceId_ResumeOSInterrupts			((OSServiceIdType) 0xea)
#define OSServiceId_SuspendOSInterrupts			((OSServiceIdType) 0xeb)
#define OSServiceId_GetResource					((OSServiceIdType) 0xec)
#define OSServiceId_ReleaseResource				((OSServiceIdType) 0xed)
#define OSServiceId_SetEvent					((OSServiceIdType) 0xee)
#define OSServiceId_ClearEvent					((OSServiceIdType) 0xef)
#define OSServiceId_GetEvent					((OSServiceIdType) 0xf0)
#define OSServiceId_WaitEvent					((OSServiceIdType) 0xf1)
#define OSServiceId_GetAlarmBase				((OSServiceIdType) 0xf2)
#define OSServiceId_GetAlarm					((OSServiceIdType) 0xf3)
#define OSServiceId_SetRelAlarm					((OSServiceIdType) 0xf4)
#define OSServiceId_SetAbsAlarm					((OSServiceIdType) 0xf5)
#define OSServiceId_CancelAlarm					((OSServiceIdType) 0xf6)
#define OSServiceId_GetActiveApplicationMode	((OSServiceIdType) 0xf7)
#define OSServiceId_StartOS						((OSServiceIdType) 0xf8)
#define OSServiceId_ShutdownOS					((OSServiceIdType) 0xf9)

#define OSServiceId_INVALID						((OSServiceIdType) 0xff)  /* Invalid system service ID */

/*
 *  Definition of the processing unit that caused the protection violation
 */
#define FC_INVALID			UINT_C(0x00)        /* It is not possible to identify the processing unit that caused the protection violation */
#define FC_TASK				UINT_C(0x01)        /* And it caused the protection violation processing unit task */
#define FC_C2ISR			UINT_C(0x02)        /* And it caused the protection violation processing units C2ISR */
#define FC_SYSTEM_HOOK		UINT_C(0x03)        /* Processing unit that caused the protection violation hook */
#define FC_TRUSTED_FUNC		UINT_C(0x04)        /* Trust function processing unit that caused the protection violation */

/*
 *  Definitions for the system service parameter acquisition
 */
#ifndef TOPPERS_MACRO_ONLY

/*
 *  When the error hook OFF, service ID acquisition and parameter acquisition also becomes OFF
 */
#ifdef CFG_USE_ERRORHOOK

#ifdef CFG_USE_GETSERVICEID
extern OSServiceIdType	_errorhook_svcid;
#endif /* CFG_USE_GETSERVICEID */

#ifdef CFG_USE_PARAMETERACCESS
extern _ErrorHook_Par	errorhook_par1;
extern _ErrorHook_Par	errorhook_par2;
extern _ErrorHook_Par	errorhook_par3;
#endif /* CFG_USE_PARAMETERACCESS */

#endif /* CFG_USE_ERRORHOOK */

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  When the error hook OFF, service ID acquisition and parameter acquisition also becomes OFF
 */
#ifdef CFG_USE_ERRORHOOK

/*
 *  The definition of the macro
 */
#ifdef CFG_USE_GETSERVICEID
#define OSErrorGetServiceId()				(_errorhook_svcid)
#endif /* CFG_USE_GETSERVICEID */

/*
 *  System service ID that caused the error
 */
#ifdef CFG_USE_PARAMETERACCESS
#define OSError_StartOS_Mode()									(errorhook_par1.mode)
#define OSError_ActivateTask_TaskID()							(errorhook_par1.tskid)
#define OSError_ChainTask_TaskID()								(errorhook_par1.tskid)
#define OSError_GetTaskID_TaskID()								(errorhook_par1.p_tskid)
#define OSError_GetTaskState_TaskID()							(errorhook_par1.tskid)
#define OSError_GetTaskState_State()							(errorhook_par2.p_stat)
#define OSError_GetResource_ResID()								(errorhook_par1.resid)
#define OSError_ReleaseResource_ResID()							(errorhook_par1.resid)
#define OSError_SetEvent_TaskID()								(errorhook_par1.tskid)
#define OSError_SetEvent_Mask()									(errorhook_par2.mask)
#define OSError_ClearEvent_Mask()								(errorhook_par1.mask)
#define OSError_GetEvent_TaskID()								(errorhook_par1.tskid)
#define OSError_GetEvent_Event()								(errorhook_par2.p_mask)
#define OSError_WaitEvent_Mask()								(errorhook_par1.mask)
#define OSError_GetAlarmBase_AlarmID()							(errorhook_par1.almid)
#define OSError_GetAlarmBase_Info()								(errorhook_par2.p_info)
#define OSError_GetAlarm_AlarmID()								(errorhook_par1.almid)
#define OSError_GetAlarm_Tick()									(errorhook_par2.p_tick)
#define OSError_SetRelAlarm_AlarmID()							(errorhook_par1.almid)
#define OSError_SetRelAlarm_increment()							(errorhook_par2.incr)
#define OSError_SetRelAlarm_cycle()								(errorhook_par3.cycle)
#define OSError_SetAbsAlarm_AlarmID()							(errorhook_par1.almid)
#define OSError_SetAbsAlarm_start()								(errorhook_par2.start)
#define OSError_SetAbsAlarm_cycle()								(errorhook_par3.cycle)
#define OSError_CancelAlarm_AlarmID()							(errorhook_par1.almid)
#define OSError_IncrementCounter_CounterID()					(errorhook_par1.cntid)
#define OSError_GetCounterValue_CounterID()						(errorhook_par1.cntid)
#define OSError_GetCounterValue_Value()							(errorhook_par2.p_val)
#define OSError_GetElapsedValue_CounterID()						(errorhook_par1.cntid)
#define OSError_GetElapsedValue_Value()							(errorhook_par2.p_val)
#define OSError_GetElapsedValue_ElapsedValue()					(errorhook_par3.p_eval)
#define OSError_StartScheduleTableRel_ScheduleTableID()			(errorhook_par1.schtblid)
#define OSError_StartScheduleTableRel_Offset()					(errorhook_par2.offset)
#define OSError_StartScheduleTableAbs_ScheduleTableID()			(errorhook_par1.schtblid)
#define OSError_StartScheduleTableAbs_Start()					(errorhook_par2.start)
#define OSError_StopScheduleTable_ScheduleTableID()				(errorhook_par1.schtblid)
#define OSError_NextScheduleTable_ScheduleTableID_From()		(errorhook_par1.schtblid_from)
#define OSError_NextScheduleTable_ScheduleTableID_To()			(errorhook_par2.schtblid_to)
#define OSError_GetScheduleTableStatus_ScheduleTableID()		(errorhook_par1.schtblid)
#define OSError_GetScheduleTableStatus_ScheduleStatus()			(errorhook_par2.p_schtblstate)
#define OSError_ShutdownOS_Error()								(errorhook_par1.error)
#define OSError_DisableInterruptSource_DisableISR()				(errorhook_par1.isrid)
#define OSError_EnableInterruptSource_EnableISR()				(errorhook_par1.isrid)
#define OSError_GetApplicationState_Application()				(errorhook_par1.applid)
#define OSError_GetApplicationState_Value()						(errorhook_par2.p_appstat)
#define OSError_CallTrustedFunction_FunctionIndex()				(errorhook_par1.tfnid)
#define OSError_CallTrustedFunction_FunctionParams()			(errorhook_par2.tfnpr)
#define OSError_CheckISRMemoryAccess_ISRID()					(errorhook_par1.isrid)
#define OSError_CheckISRMemoryAccess_Address()					(errorhook_par2.adr)
#define OSError_CheckISRMemoryAccess_Size()						(errorhook_par3.sz)
#define OSError_CheckTaskMemoryAccess_TaskID()					(errorhook_par1.tskid)
#define OSError_CheckTaskMemoryAccess_Address()					(errorhook_par2.adr)
#define OSError_CheckTaskMemoryAccess_Size()					(errorhook_par3.sz)
#define OSError_CheckTaskAccess_ApplID()						(errorhook_par1.applid)
#define OSError_CheckTaskAccess_TaskID()						(errorhook_par2.tskid)
#define OSError_CheckISRAccess_ApplID()							(errorhook_par1.applid)
#define OSError_CheckISRAccess_ISRID()							(errorhook_par2.isrid)
#define OSError_CheckAlarmAccess_ApplID()						(errorhook_par1.applid)
#define OSError_CheckAlarmAccess_AlarmID()						(errorhook_par2.almid)
#define OSError_CheckResourceAccess_ApplID()					(errorhook_par1.applid)
#define OSError_CheckResourceAccess_ResID()						(errorhook_par2.resid)
#define OSError_CheckCounterAccess_ApplID()						(errorhook_par1.applid)
#define OSError_CheckCounterAccess_CounterID()					(errorhook_par2.cntid)
#define OSError_CheckScheduleTableAccess_ApplID()				(errorhook_par1.applid)
#define OSError_CheckScheduleTableAccess_ScheduleTableID()		(errorhook_par2.schtblid)
#define OSError_CheckTaskOwnership_TaskID()						(errorhook_par1.tskid)
#define OSError_CheckISROwnership_ISRID()						(errorhook_par1.isrid)
#define OSError_CheckAlarmOwnership_AlarmID()					(errorhook_par1.almid)
#define OSError_CheckCounterOwnership_CounterID()				(errorhook_par1.cntid)
#define OSError_CheckScheduleTableOwnership_ScheduleTableID()	(errorhook_par1.schtblid)
#define OSError_IocSend_IocId()									(errorhook_par1.iocid)
#define OSError_IocSend_SenderId()								(errorhook_par2.senderid)
#define OSError_IocWrite_IocId()								(errorhook_par1.iocid)
#define OSError_IocWrite_SenderId()								(errorhook_par2.senderid)
#define OSError_IocReceive_IocId()								(errorhook_par1.iocid)
#define OSError_IocRead_IocId()									(errorhook_par1.iocid)
#define OSError_IocEmptyQueue_IocId()							(errorhook_par1.iocid)
#define OSError_TerminateApplication_Application()				(errorhook_par1.applid)
#define OSError_TerminateApplication_RestartOption()			(errorhook_par2.restartoption)

#endif /* CFG_USE_PARAMETERACCESS */

#endif /* CFG_USE_ERRORHOOK */

/*
 *  Macro of protection hook relationship
 */
#define PRO_IGNORE					UINT_C(0x00)
#define PRO_SHUTDOWN				UINT_C(0x01)
#define PRO_TERMINATETASKISR		UINT_C(0x02)
#define PRO_TERMINATEAPPL			UINT_C(0x03)
#define PRO_TERMINATEAPPL_RESTART	UINT_C(0x04)

/*
 *  Macro of OSAP end / restart relationship
 */
#define NO_RESTART					UINT_C(0x00)
#define RESTART						UINT_C(0x01)

/*
 *  Macros for memory access authority check
 */

/*
 *  Memory area authority
 */

#define AP_NoAccess		UINT_C(0x0)
#define AP_Executable	UINT_C(0x1)
#define AP_Readable		UINT_C(0x2)
#define AP_Writable		UINT_C(0x4)
#define AP_StackSpace	UINT_C(0x8)

/*
 *  Access check macro
 */
#define OSMEMORY_IS_READABLE(AccessType)	((AccessType) & AP_Readable)
#define OSMEMORY_IS_WRITEABLE(AccessType)	((AccessType) & AP_Writable)
#define OSMEMORY_IS_EXECUTABLE(AccessType)	((AccessType) & AP_Executable)
#define OSMEMORY_IS_STACKSPACE(AccessType)	((AccessType) & AP_StackSpace)

/*
 *   Object Type
 */
#define OBJECT_TASK				UINT_C(0x01)
#define OBJECT_ISR				UINT_C(0x02)
#define OBJECT_ALARM			UINT_C(0x03)
#define OBJECT_RESOURCE			UINT_C(0x04)
#define OBJECT_COUNTER			UINT_C(0x05)
#define OBJECT_SCHEDULETABLE	UINT_C(0x06)

/*
 *  version information
 */
#define OS_SW_MAJOR_VERSION				UINT_C(1)   /* Supplier version*/
#define OS_SW_MINOR_VERSION				UINT_C(4)
#define OS_SW_PATCH_VERSION				UINT_C(0)

#define OS_AR_RELEASE_MAJOR_VERSION		UINT_C(4)   /* AUTOSAR release version */
#define OS_AR_RELEASE_MINOR_VERSION		UINT_C(0)
#define OS_AR_RELEASE_REVISION_VERSION	UINT_C(3)

#define TKERNEL_NAME	"TOPPERS/ATK2-SC4"  /* Kernel name (proprietary) */

#endif /* TOPPERS_OS_H */
