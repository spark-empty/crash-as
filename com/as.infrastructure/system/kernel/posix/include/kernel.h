/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2016  AS <parai@foxmail.com>
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
#ifndef KERNEL_H_
#define KERNEL_H_
/* ============================ [ INCLUDES  ] ====================================================== */

/* ============================ [ MACROS    ] ====================================================== */
#define __POSIX_OSAL__
/*
 *  Macro for declare Task/Alarm/ISR Entry
 */
#define TASKNAME(TaskName)	TaskMain##TaskName
#define TASK(TaskName)		void TaskMain##TaskName(void)
#define ISRNAME(ISRName)	ISRMain##ISRName
#define ISR(ISRName)		void ISRMain##ISRName(void)
#define ALARMCALLBACKNAME(AlarmCallBackName) 	\
							AlarmMain##AlarmCallBackName
#define ALARMCALLBACK(AlarmCallBackName)	\
							void AlarmMain##AlarmCallBackName(void)

/*
 *  OS Status (error code)
 */
#define E_OS_ACCESS		((StatusType) 1)
#define E_OS_CALLEVEL	((StatusType) 2)
#define E_OS_ID			((StatusType) 3)
#define E_OS_LIMIT		((StatusType) 4)
#define E_OS_NOFUNC		((StatusType) 5)
#define E_OS_RESOURCE	((StatusType) 6)
#define E_OS_STATE		((StatusType) 7)
#define E_OS_VALUE		((StatusType) 8)

#define RES_SCHEDULER		((ResourceType) 0)	/* Constant of data type ResourceType (see (osek)chapter 8, Resource management). */


#define OSDEFAULTAPPMODE	((AppModeType) 0x01)

#define SUSPENDED                  ((StatusType) 0)
#define RUNNING                    ((StatusType) 1)
#define READY                      ((StatusType) 2)
#define WAITING                    ((StatusType) 3)
/* ============================ [ TYPES     ] ====================================================== */
typedef uint32_t		StatusType;

typedef uint32_t		TaskType;			/* Task ID */
typedef TaskType*		TaskRefType;
typedef uint32_t		TaskStateType;
typedef TaskStateType*	TaskStateRefType;
typedef uint32_t		TaskStateType;		/* Task State */
typedef uint32_t		ResourceType;		/* Resource ID */
typedef uint32_t		EventMaskType;		/* Event Mask in bit */
typedef EventMaskType*	EventMaskRefType;
typedef uint32_t		TickType;			/* Time Tick */
typedef TickType*		TickRefType;
typedef uint32_t		AlarmType;			/* Alarm ID */
typedef uint32_t		AppModeType;		/* OS Application Mode */
typedef uint32_t		OSServiceIdType;	/* OS service API ID */
typedef uint32_t		IsrType;			/* ISR ID */
typedef uint32_t		CounterType;		/* Counter ID */
typedef struct
{
	TickType maxallowedvalue;
	TickType ticksperbase;
	TickType mincycle;
} AlarmBaseType;
typedef AlarmBaseType*	AlarmBaseRefType;

typedef	unsigned char		UINT8;		/* 8 bit unsigned integer */
typedef	unsigned short  	UINT16;		/* 16 bit unsigned integer */

typedef void		*VP;			/* void pointer */
typedef void		(*FP)(void);	/* function pointer */
typedef uint32_t	Priority;		/* priority for task/resource/ISR */
typedef	uint32_t	IPL;			/* interrupt processing level */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void EnableAllInterrupts(void);
void DisableAllInterrupts(void);
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
FUNC(StatusType,MEM_SetEvent)        SetEvent        ( TaskType tskid , EventMaskType mask );
FUNC(StatusType,MEM_ClearEvent)      ClearEvent      ( EventMaskType mask );
FUNC(StatusType,MEM_GetEvent)        GetEvent        ( TaskType tskid , EventMaskRefType p_mask );
FUNC(StatusType,MEM_WaitEvent)       WaitEvent       ( EventMaskType mask );
#endif /* KERNEL_H_ */
