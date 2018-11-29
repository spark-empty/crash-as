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
 *  $Id: svc_funccall.h 504 2015-12-24 01:22:56Z witz-itoyo $
 */

/*  This file is generated from svc.def by gensvc_atk. */

#ifndef TOPPERS_SVC_FUNCCALL_H
#define TOPPERS_SVC_FUNCCALL_H

#define SVC_CALL(system_service)	_kernel_ ## system_service

#ifdef TOPPERS_SVC_FUNCCALL
#define StartOS						_kernel_StartOS
#define ShutdownOS					_kernel_ShutdownOS
#define ActivateTask				_kernel_ActivateTask
#define TerminateTask				_kernel_TerminateTask
#define ChainTask					_kernel_ChainTask
#define Schedule					_kernel_Schedule
#define GetTaskID					_kernel_GetTaskID
#define GetTaskState				_kernel_GetTaskState
#define EnableAllInterrupts			_kernel_EnableAllInterrupts
#define DisableAllInterrupts		_kernel_DisableAllInterrupts
#define ResumeAllInterrupts			_kernel_ResumeAllInterrupts
#define SuspendAllInterrupts		_kernel_SuspendAllInterrupts
#define ResumeOSInterrupts			_kernel_ResumeOSInterrupts
#define SuspendOSInterrupts			_kernel_SuspendOSInterrupts
#define GetISRID					_kernel_GetISRID
#define DisableInterruptSource		_kernel_DisableInterruptSource
#define EnableInterruptSource		_kernel_EnableInterruptSource
#define GetResource					_kernel_GetResource
#define ReleaseResource				_kernel_ReleaseResource
#define SetEvent					_kernel_SetEvent
#define ClearEvent					_kernel_ClearEvent
#define GetEvent					_kernel_GetEvent
#define WaitEvent					_kernel_WaitEvent
#define GetAlarmBase				_kernel_GetAlarmBase
#define GetAlarm					_kernel_GetAlarm
#define SetRelAlarm					_kernel_SetRelAlarm
#define SetAbsAlarm					_kernel_SetAbsAlarm
#define CancelAlarm					_kernel_CancelAlarm
#define IncrementCounter			_kernel_IncrementCounter
#define GetCounterValue				_kernel_GetCounterValue
#define GetElapsedValue				_kernel_GetElapsedValue
#define CheckISRMemoryAccess		_kernel_CheckISRMemoryAccess
#define CheckTaskMemoryAccess		_kernel_CheckTaskMemoryAccess
#define CheckTaskAccess				_kernel_CheckTaskAccess
#define CheckISRAccess				_kernel_CheckISRAccess
#define CheckAlarmAccess			_kernel_CheckAlarmAccess
#define CheckResourceAccess			_kernel_CheckResourceAccess
#define CheckCounterAccess			_kernel_CheckCounterAccess
#define CheckScheduleTableAccess	_kernel_CheckScheduleTableAccess
#define CheckTaskOwnership			_kernel_CheckTaskOwnership
#define CheckISROwnership			_kernel_CheckISROwnership
#define CheckAlarmOwnership			_kernel_CheckAlarmOwnership
#define CheckCounterOwnership		_kernel_CheckCounterOwnership
#define CheckScheduleTableOwnership	_kernel_CheckScheduleTableOwnership
#define GetApplicationID			_kernel_GetApplicationID
#define CallTrustedFunction			_kernel_CallTrustedFunction
#define GetApplicationState			_kernel_GetApplicationState
#define GetActiveApplicationMode	_kernel_GetActiveApplicationMode
#define StartScheduleTableRel		_kernel_StartScheduleTableRel
#define StartScheduleTableAbs		_kernel_StartScheduleTableAbs
#define StopScheduleTable			_kernel_StopScheduleTable
#define NextScheduleTable			_kernel_NextScheduleTable
#define GetScheduleTableStatus		_kernel_GetScheduleTableStatus
#define GetFaultyContext			_kernel_GetFaultyContext
#define ioc_send_generic			_kernel_ioc_send_generic
#define ioc_write_generic			_kernel_ioc_write_generic
#define ioc_receive_generic			_kernel_ioc_receive_generic
#define ioc_read_generic			_kernel_ioc_read_generic
#define ioc_empty_queue_generic		_kernel_ioc_empty_queue_generic
#define AllowAccess					_kernel_AllowAccess
#define TerminateApplication		_kernel_TerminateApplication
#endif

#ifndef TOPPERS_MACRO_ONLY

extern void _kernel_StartOS(AppModeType Mode);
extern void _kernel_ShutdownOS(StatusType Error);
extern StatusType _kernel_ActivateTask(TaskType TaskID);
extern StatusType _kernel_TerminateTask(void);
extern StatusType _kernel_ChainTask(TaskType TaskID);
extern StatusType _kernel_Schedule(void);
extern StatusType _kernel_GetTaskID(TaskRefType TaskID);
extern StatusType _kernel_GetTaskState(TaskType TaskID, TaskStateRefType State);
extern void _kernel_EnableAllInterrupts(void);
extern void _kernel_DisableAllInterrupts(void);
extern void _kernel_ResumeAllInterrupts(void);
extern void _kernel_SuspendAllInterrupts(void);
extern void _kernel_ResumeOSInterrupts(void);
extern void _kernel_SuspendOSInterrupts(void);
extern ISRType _kernel_GetISRID(void);
extern StatusType _kernel_DisableInterruptSource(ISRType DisableISR);
extern StatusType _kernel_EnableInterruptSource(ISRType EnableISR);
extern StatusType _kernel_GetResource(ResourceType ResID);
extern StatusType _kernel_ReleaseResource(ResourceType ResID);
extern StatusType _kernel_SetEvent(TaskType TaskID, EventMaskType Mask);
extern StatusType _kernel_ClearEvent(EventMaskType Mask);
extern StatusType _kernel_GetEvent(TaskType TaskID, EventMaskRefType Event);
extern StatusType _kernel_WaitEvent(EventMaskType Mask);
extern StatusType _kernel_GetAlarmBase(AlarmType AlarmID, AlarmBaseRefType Info);
extern StatusType _kernel_GetAlarm(AlarmType AlarmID, TickRefType Tick);
extern StatusType _kernel_SetRelAlarm(AlarmType AlarmID, TickType increment, TickType cycle);
extern StatusType _kernel_SetAbsAlarm(AlarmType AlarmID, TickType start, TickType cycle);
extern StatusType _kernel_CancelAlarm(AlarmType AlarmID);
extern StatusType _kernel_IncrementCounter(CounterType CounterID);
extern StatusType _kernel_GetCounterValue(CounterType CounterID, TickRefType Value);
extern StatusType _kernel_GetElapsedValue(CounterType CounterID, TickRefType Value, TickRefType ElapsedValue);
extern AccessType _kernel_CheckISRMemoryAccess(ISRType ISRID, MemoryStartAddressType Address, MemorySizeType Size);
extern AccessType _kernel_CheckTaskMemoryAccess(TaskType TaskID, MemoryStartAddressType Address, MemorySizeType Size);
extern ObjectAccessType _kernel_CheckTaskAccess(ApplicationType ApplID, TaskType TaskID);
extern ObjectAccessType _kernel_CheckISRAccess(ApplicationType ApplID, ISRType ISRID);
extern ObjectAccessType _kernel_CheckAlarmAccess(ApplicationType ApplID, AlarmType AlarmID);
extern ObjectAccessType _kernel_CheckResourceAccess(ApplicationType ApplID, ResourceType ResID);
extern ObjectAccessType _kernel_CheckCounterAccess(ApplicationType ApplID, CounterType CounterID);
extern ObjectAccessType _kernel_CheckScheduleTableAccess(ApplicationType ApplID, ScheduleTableType ScheduleTableID);
extern ApplicationType _kernel_CheckTaskOwnership(TaskType TaskID);
extern ApplicationType _kernel_CheckISROwnership(ISRType ISRID);
extern ApplicationType _kernel_CheckAlarmOwnership(AlarmType AlarmID);
extern ApplicationType _kernel_CheckCounterOwnership(CounterType CounterID);
extern ApplicationType _kernel_CheckScheduleTableOwnership(ScheduleTableType ScheduleTableID);
extern ApplicationType _kernel_GetApplicationID(void);
extern StatusType _kernel_CallTrustedFunction(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams);
extern StatusType _kernel_GetApplicationState(ApplicationType Application, ApplicationStateRefType Value);
extern AppModeType _kernel_GetActiveApplicationMode(void);
extern StatusType _kernel_StartScheduleTableRel(ScheduleTableType ScheduleTableID, TickType Offset);
extern StatusType _kernel_StartScheduleTableAbs(ScheduleTableType ScheduleTableID, TickType Start);
extern StatusType _kernel_StopScheduleTable(ScheduleTableType ScheduleTableID);
extern StatusType _kernel_NextScheduleTable(ScheduleTableType ScheduleTableID_From, ScheduleTableType ScheduleTableID_To);
extern StatusType _kernel_GetScheduleTableStatus(ScheduleTableType ScheduleTableID, ScheduleTableStatusRefType ScheduleStatus);
extern FaultyContextType _kernel_GetFaultyContext(void);
extern Std_ReturnType _kernel_ioc_send_generic(IocType IocWrapperId, const void *in);
extern Std_ReturnType _kernel_ioc_write_generic(IocType IocWrapperId, const void *in);
extern Std_ReturnType _kernel_ioc_receive_generic(IocType IocId, void *out);
extern Std_ReturnType _kernel_ioc_read_generic(IocType IocId, void *out);
extern Std_ReturnType _kernel_ioc_empty_queue_generic(IocType IocId);
extern StatusType _kernel_AllowAccess(void);
extern StatusType _kernel_TerminateApplication(ApplicationType Application, RestartType RestartOption);

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_SVC_FUNCCALL */
