/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2017  AS <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */
#ifndef TPL_OS_H
#define TPL_OS_H
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
#include "tpl_os_types.h"
#include "tpl_os_definitions.h"
#include "tpl_os_os.h"
#include "tpl_os_event.h"
#include "tpl_os_resource.h"
#include "tpl_app_config.h"
#include "tpl_os_alarm.h"
#include "tpl_os_task.h"
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */

/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
FUNC(void,MEM_OS_TICK) 				 OsTick 		  ( void );
FUNC(StatusType,MEM_GetAlarmBase) 	 GetAlarmBase    ( AlarmType AlarmId, AlarmBaseRefType Info );
FUNC(StatusType,MEM_GetAlarm) 		 GetAlarm	     ( AlarmType AlarmId, TickRefType Tick );
FUNC(StatusType,MEM_SetRelAlarm) 	 SetRelAlarm     ( AlarmType AlarmId, TickType Increment, TickType Cycle );
FUNC(StatusType,MEM_SetAbsAlarm) 	 SetAbsAlarm     ( AlarmType AlarmId, TickType Increment, TickType Cycle );
FUNC(StatusType,MEM_CancelAlarm)     CancelAlarm     ( AlarmType AlarmId );
FUNC(StatusType,MEM_ACTIVATE_TASK) 	 ActivateTask    ( TaskType TaskId);
FUNC(StatusType,MEM_ACTIVATE_TASK) 	 TerminateTask   ( void );
FUNC(StatusType,MEM_Schedule) 		 Schedule        ( void );
FUNC(StatusType,MEM_GetTaskID) 		 GetTaskID       ( TaskRefType TaskID );
FUNC(StatusType,MEM_GetTaskState) 	 GetTaskState    ( TaskType TaskID,TaskStateRefType State );
FUNC(void,MEM_StartOS)               StartOS         ( AppModeType Mode );
FUNC(StatusType,MEM_GetResource)     GetResource     ( ResourceType ResID );
FUNC(StatusType,MEM_ReleaseResource) ReleaseResource ( ResourceType ResID );
#ifdef __WINDOWS__
FUNC(StatusType,MEM_SetEvent)        SetEvent2        ( TaskType tskid , EventMaskType mask );
#else
FUNC(StatusType,MEM_SetEvent)        SetEvent        ( TaskType tskid , EventMaskType mask );
#endif
FUNC(StatusType,MEM_ClearEvent)      ClearEvent      ( EventMaskType mask );
FUNC(StatusType,MEM_GetEvent)        GetEvent        ( TaskType tskid , EventMaskRefType p_mask );
FUNC(StatusType,MEM_WaitEvent)       WaitEvent       ( EventMaskType mask );

extern void EnableAllInterrupts(void);
extern void DisableAllInterrupts(void);
#endif /* TPL_OS_H */
