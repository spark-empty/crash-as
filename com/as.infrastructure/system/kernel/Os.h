/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2015  AS <parai@foxmail.com>
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
#ifndef _OS_H_
#define _OS_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
#ifndef NO_OSCFG
#include "Os_Cfg.h"
#include "ksm_cfg.h"
#endif
#ifdef USE_PROTOTHREAD
#include "contiki.h"
#endif

/* ============================ [ MACROS    ] ====================================================== */
#if !defined(__FREERTOS__)
#define OsActivateTask(x)		ActivateTask(TASK_ID_##x)
#define OsTerminateTask(x)		TerminateTask()
#define OsSetRelAlarm(x,a,b)	SetRelAlarm(ALARM_ID_##x,a,b)
#define OsSetAbsAlarm(x,a,b)	SetAbsAlarm(ALARM_ID_##x,a,b)
#define OsCancelAlarm(x)		CancelAlarm(ALARM_ID_##x)
#ifdef __WINDOWS__
#define OsSetEvent(task,event)    SetEvent2(TASK_ID_##task,EVENT_MASK_##task##_##event)
#else
#define OsSetEvent(task,event)    SetEvent(TASK_ID_##task,EVENT_MASK_##task##_##event)
#endif
#define OsGetEvent(task,event)    GetEvent(TASK_ID_##task,EVENT_MASK_##task##_##event)
#define OsClearEvent(task,event)  ClearEvent(EVENT_MASK_##task##_##event)
#define OsWaitEvent(task,event)   WaitEvent(EVENT_MASK_##task##_##event)
#endif /* __FREERTOS__ */

#if defined(__FREEOSEK__)
#define ALARM(AlarmName)  ALARMCALLBACK(AlarmName)
#endif

#ifdef __CONTIKI_OS__
#define OS_TASK_BEGIN() PROCESS_BEGIN()
#define OS_TASK_END()	PROCESS_END()
#else
#define OS_TASK_BEGIN()
#define OS_TASK_END()
#endif

/* KSM states */
#define KSM_S_INIT                0x00
#define KSM_S_START               0x01
#define KSM_S_STOP                0x02
#define KSM_S_INVALID             0xFF

#if(KSM_NUM > 0)
#define KSM_INIT() 		KsmInit()
#define KSM_EXECUTE() 	KsmExecute()
#else
#define KSM_INIT()
#define KSM_EXECUTE()
#endif

#define TICK_MAX                (TickType)-1

/* define the state handle of kernel state machine(KSM) */
#define KSM(_Ksm,State) void Ksm##_Ksm##_##State(void)
/* trigger the KSM go to next state */
#define KGS(Ksm,State)  KsmSetState(KSM_ID_##Ksm,KSM_##Ksm##_##State)

#ifdef NO_OSCFG
#define OSDEFAULTAPPMODE 0
#endif
/* ============================ [ TYPES     ] ====================================================== */
#if(KSM_NUM < 0xFF)
typedef uint8 KsmID_Type;
#elif(KSM_NUM < 0xFFFF)
typedef uint16 KsmID_Type;
#else
typedef uint32 KsmID_Type;
#endif

#ifdef NO_OSCFG
typedef uint32 TickType;
typedef uint8 AppModeType;
typedef uint8 StatusType;
typedef uint8 KSMState_Type;
#endif
/* Kernel Timer.
 * If Tick is 1ms per Tick,
 * then counter max time is (0xFFFFFFFF)ms = 49.71 days.
 */
typedef TickType TimerType;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
extern TickType OsTickCounter;
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
extern void StartOS( AppModeType app_mode );
extern void StartupHook( void );
extern void ShutdownOS(StatusType ercd);
extern void KsmInit(void);
extern void KsmStart(void);
extern void KsmStop(void);
extern void KsmExecute(void);
extern void KsmSetState(KsmID_Type Ksm,KSMState_Type state);
extern KSMState_Type KsmGetState(KsmID_Type Ksm);

static inline void StartTimer(TimerType* timer)
{
	*timer = OsTickCounter;
}
static inline void StopTimer(TimerType* timer)
{
	*timer = 0;
}
static inline TimerType GetTimer(TimerType* timer)
{
	TimerType time;

	if(0 == *timer)
	{
		time = 0;
	}
	else
	{
		if (OsTickCounter >= *timer)
		{
			 time = (OsTickCounter - *timer);
		}
		else
		{
			time = (TICK_MAX - *timer + OsTickCounter);
		}
	}
	return time;
}

static inline TickType GetOsTick(void)
{
	return OsTickCounter;
}

static inline TickType GetOsElapsedTick  ( TickType prevTick )
{
    if (OsTickCounter >= prevTick) {
		return(OsTickCounter - prevTick);
	}
	else {
		return(prevTick - OsTickCounter + (TICK_MAX + 1));
	}
}
#endif /* _OS_H_ */
