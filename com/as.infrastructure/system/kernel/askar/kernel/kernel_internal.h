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
#ifndef KERNEL_INTERNAL_H_
#define KERNEL_INTERNAL_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Os.h"
#include <sys/queue.h>
#include "portable.h"
#ifdef USE_SHELL
#include "shell.h"
#endif
#ifdef USE_PTHREAD
#include "sched.h"
#endif
/* ============================ [ MACROS    ] ====================================================== */
#ifndef USE_PTHREAD
#undef OS_PTHREAD_NUM
#define OS_PTHREAD_NUM 0
#endif
/*
 * BCC1 (only basic tasks, limited to one activation request per task and one task per
 * priority, while all tasks have different priorities)
 * BCC2 (like BCC1, plus more than one task per priority possible and multiple requesting
 * of task activation allowed)
 * ECC1 (like BCC1, plus extended tasks)
 * ECC2 (like ECC1, plus more than one task per priority possible and multiple requesting
 * of task activation allowed for basic tasks)
 */
enum {
	BCC1,
	BCC2,
	ECC1,
	ECC2
};

enum {
	STANDARD,
	EXTENDED
};

#define TASK_STATE(pTaskVar) (((pTaskVar)->state)&OSEK_TASK_STATE_MASK)
/*
 *  kernel call level
 */
#define TCL_NULL		((unsigned int) 0x00)	/* invalid kernel call level */
#define TCL_TASK		((unsigned int) 0x01)	/* task level */
#define TCL_ISR2		((unsigned int) 0x02)	/* interrupt type 2 ISR */
#define TCL_ERROR		((unsigned int) 0x04)	/* ErrorHook */
#define TCL_PREPOST		((unsigned int) 0x08)	/* PreTaskHook & PostTaskHook */
#define TCL_STARTUP		((unsigned int) 0x10)	/* StartupHook */
#define TCL_SHUTDOWN	((unsigned int) 0x20)	/* ShutdownHook */
#define TCL_LOCK		((unsigned int) 0x40)	/* lock dispatcher */


#define INVALID_PRIORITY	((PriorityType)-1)

#ifdef OS_USE_ERROR_HOOK
/* OSErrorOne/OSErrorTwo/OSErrorThree
 * a. Each API MUST keep the parameter name the same with
 * the "param" of OSError_##api##_##param.
 * b. Each API block MUST have the "ercd" variable.
 */
/* for those API only with no parameter */
#define OSErrorNone(api) do { \
	if(ercd != E_OK) { \
		unsigned int savedLevel; \
		imask_t mask; \
		Irq_Save(mask); \
		_errorhook_svcid = OSServiceId_##api; \
		savedLevel = CallLevel; \
		CallLevel = TCL_ERROR; \
		ErrorHook(ercd); \
		CallLevel = savedLevel; \
		Irq_Restore(mask); \
	} \
} while(0)

/* for those API only with 1 parameter */
#define OSErrorOne(api, param) do { \
	if(ercd != E_OK) { \
		unsigned int savedLevel; \
		imask_t mask; \
		Irq_Save(mask); \
		_errorhook_svcid = OSServiceId_##api; \
		OSError_##api##_##param() = param; \
		savedLevel = CallLevel; \
		CallLevel = TCL_ERROR; \
		ErrorHook(ercd); \
		CallLevel = savedLevel; \
		Irq_Restore(mask); \
	} \
} while(0)

/* for those API with 2 parameters */
#define OSErrorTwo(api, param0, param1) do { \
	if(ercd != E_OK) { \
		unsigned int savedLevel; \
		imask_t mask; \
		Irq_Save(mask); \
		_errorhook_svcid = OSServiceId_##api; \
		OSError_##api##_##param0() = param0; \
		OSError_##api##_##param1() = param1; \
		savedLevel = CallLevel; \
		CallLevel = TCL_ERROR; \
		ErrorHook(ercd); \
		CallLevel = savedLevel; \
		Irq_Restore(mask); \
	} \
} while(0)

/* for those API with 3 parameters */
#define OSErrorThree(api, param0, param1, param2) do { \
	if(ercd != E_OK) { \
		unsigned int savedLevel; \
		imask_t mask; \
		Irq_Save(mask); \
		_errorhook_svcid = OSServiceId_##api; \
		OSError_##api##_##param0() = param0; \
		OSError_##api##_##param1() = param1; \
		OSError_##api##_##param2() = param2; \
		savedLevel = CallLevel; \
		CallLevel = TCL_ERROR; \
		ErrorHook(ercd); \
		CallLevel = savedLevel; \
		Irq_Restore(mask); \
	} \
} while(0)
#else
#define OSErrorNone(api)
#define OSErrorOne(api, param)
#define OSErrorTwo(api, param0, param1)
#define OSErrorThree(api, param0, param1, param2)
#endif

#ifdef OS_USE_STARTUP_HOOK
#define OSStartupHook() do { \
	unsigned int savedLevel; \
	imask_t mask; \
	Irq_Save(mask); \
	savedLevel = CallLevel; \
	CallLevel = TCL_STARTUP; \
	StartupHook(); \
	CallLevel = savedLevel; \
	Irq_Restore(mask); \
} while(0)
#else
#define OSStartupHook()
#endif

#ifdef OS_USE_SHUTDOWN_HOOK
#define OSShutdownHook(ercd) do { \
	unsigned int savedLevel; \
	imask_t mask; \
	Irq_Save(mask); \
	savedLevel = CallLevel; \
	CallLevel = TCL_SHUTDOWN; \
	ShutdownHook(ercd); \
	CallLevel = savedLevel; \
	Irq_Restore(mask); \
} while(0)
#else
#define OSShutdownHook(ercd)
#endif

#ifdef OS_USE_PRETASK_HOOK
#define OSPreTaskHook() do { \
	unsigned int savedLevel; \
	imask_t mask; \
	Irq_Save(mask); \
	savedLevel = CallLevel; \
	CallLevel = TCL_PREPOST; \
	PreTaskHook(); \
	CallLevel = savedLevel; \
	Irq_Restore(mask); \
} while(0)
#else
#define OSPreTaskHook()
#endif

#ifdef OS_USE_POSTTASK_HOOK
#define OSPostTaskHook() do { \
	unsigned int savedLevel; \
	imask_t mask; \
	Irq_Save(mask); \
	savedLevel = CallLevel; \
	CallLevel = TCL_PREPOST; \
	PostTaskHook(); \
	CallLevel = savedLevel; \
	Irq_Restore(mask); \
} while(0)
#else
#define OSPostTaskHook()
#endif

#if !defined(USE_SCHED_BUBBLE) && !defined(USE_SCHED_FIFO) && !defined(USE_SCHED_LIST)
#define USE_SCHED_BUBBLE
#endif

#define OS_IS_ALARM_STARTED(pVar) (NULL != ((pVar)->entry.tqe_prev))
#define OS_STOP_ALARM(pVar) do { ((pVar)->entry.tqe_prev) = NULL; } while(0)

#if(OS_PTHREAD_NUM > 0)
#define PTHREAD_DEFAULT_STACK_SIZE  4096
#define PTHREAD_DEFAULT_PRIORITY    (OS_PTHREAD_PRIORITY/2)
#endif

/* PTHREAD TASK flag mask */
#define PTHREAD_DYNAMIC_CREATED_MASK 0x10
#define PTHREAD_JOINABLE_MASK        0x20
#define PTHREAD_JOINED_MASK          0x40


#ifdef USE_SHELL
#define OS_TRACE_TASK_ACTIVATION(pTaskVar) do { (pTaskVar)->actCnt++; } while(0)
#else
#define OS_TRACE_TASK_ACTIVATION(pTaskVar)
#endif

#if defined(USE_SHELL) && defined(USE_LIBDL)
#define USE_PTHREAD_PARENT
#endif

/* ============================ [ TYPES     ] ====================================================== */
typedef uint8					PriorityType;

typedef void	(*TaskMainEntryType)(void);
typedef void	(*AlarmMainEntryType)(void);
typedef void	(*FP)(void);

typedef struct
{
	PriorityType ceilPrio;
} ResourceConstType;

typedef struct
{
	PriorityType prevPrio;
	ResourceType prevRes;
} ResourceVarType;

typedef struct
{
	EventMaskType set;
	EventMaskType wait;
} EventVarType;

typedef struct
{
	void* pStack;
	uint32_t stackSize;
	TaskMainEntryType entry;
	#ifdef EXTENDED_TASK
	EventVarType* pEventVar;
	#endif
	AppModeType appModeMask;
	#if (OS_STATUS == EXTENDED)
	boolean (*CheckAccess)(ResourceType);
	#endif
	const char* name;
	PriorityType initPriority;
	PriorityType runPriority;
	#ifdef MULTIPLY_TASK_ACTIVATION
	uint8 maxActivation;
	#endif
	#ifdef USE_PTHREAD
	uint8 flag;
	#endif
} TaskConstType;

typedef struct TaskVar
{
	TaskContextType context;
	PriorityType priority;
	const TaskConstType* pConst;
	#ifdef MULTIPLY_TASK_ACTIVATION
	uint8 activation;
	#endif
	volatile StatusType state;
	ResourceType currentResource;
	#ifdef USE_SHELL
	uint32 actCnt;
	#endif
	#if defined(USE_SCHED_LIST)
	TAILQ_ENTRY(TaskVar) rentry;
	#endif
	#if (OS_PTHREAD_NUM > 0)
	/* generic entry for event/timer/mutex/semaphore etc. */
	TAILQ_ENTRY(TaskVar) entry;
	TaskListType* list; /* the list that the task is waiting on*/
	/* for sleep purpose */
	TickType sleep_tick;
	TAILQ_ENTRY(TaskVar) sentry;
	#endif
} TaskVarType;

struct AlarmVar;

typedef struct
{
	TickType value;
	TAILQ_HEAD(AlarmVarHead,AlarmVar) head;
} CounterVarType;

typedef struct
{
	const char* name;
	CounterVarType     *pVar;
	const AlarmBaseType base;
} CounterConstType;

typedef struct AlarmVar
{
	TickType value;
	TickType period;
	TAILQ_ENTRY(AlarmVar) entry;
} AlarmVarType;

typedef struct
{
	const char* name;
	AlarmVarType*     pVar;
	const CounterConstType* pCounter;
	void (*Action)(void);
	AppModeType appModeMask;
	TickType start;
	TickType period;
} AlarmConstType;

typedef struct
{
	const uint8 max;
	TaskType* pFIFO;
} ReadyFIFOType;

#if(OS_PTHREAD_NUM > 0)
#ifdef USE_PTHREAD_SIGNAL
struct signal;
#endif
#ifdef USE_PTHREAD_CLEANUP
struct cleanup;
#endif
struct pthread
{
	TaskConstType TaskConst;
	TaskVarType* pTaskVar;
#ifdef USE_PTHREAD_PARENT
	TaskVarType* parent;
#endif
	TaskListType joinList;
#ifdef USE_PTHREAD_CLEANUP
	TAILQ_HEAD(cleanup_list, cleanup) cleanupList;
#endif
#ifdef USE_PTHREAD_SIGNAL
	TaskListType sigList;
	int          signo;
	sigset_t     sigWait;
	TAILQ_HEAD(signal_list, signal) signalList;
#endif
	void *(*start) (void *);
	void* arg;
	void* ret;
};
#endif
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
extern TaskVarType* RunningVar;
extern TaskVarType* ReadyVar;
extern unsigned int CallLevel;
extern const TaskConstType TaskConstArray[TASK_NUM];
extern TaskVarType TaskVarArray[TASK_NUM+OS_PTHREAD_NUM];
extern CounterVarType CounterVarArray[COUNTER_NUM];
extern const CounterConstType CounterConstArray[COUNTER_NUM];
extern AlarmVarType AlarmVarArray[ALARM_NUM];
extern const AlarmConstType AlarmConstArray[ALARM_NUM];
extern TickType OsTickCounter;
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
extern void Os_TaskInit(AppModeType appMode);
extern void Os_ResourceInit(void);
extern void Os_CounterInit(void);
extern void Os_AlarmInit(AppModeType appMode);
extern void Os_StartAlarm(AlarmType AlarmID, TickType Start ,TickType Cycle);

extern void Os_PortInit(void);
extern void Os_PortInitContext(TaskVarType* pTaskVar);
extern void Os_PortStartDispatch(void);
extern void Os_PortDispatch(void);

extern void Sched_Init(void);
extern void Sched_AddReady(TaskType TaskID);
extern void Sched_RemoveReady(TaskType TaskID);
extern void Sched_GetReady(void);
extern void Sched_Preempt(void);
extern boolean Sched_Schedule(void);
extern void OsTick(void);
#if(OS_PTHREAD_NUM > 0)
extern void Os_SleepInit(void);
extern void Os_SleepTick(void);
extern void Os_Sleep(TickType tick);
extern void Os_SleepAdd(TaskVarType* pTaskVar, TickType ticks);
extern void Os_SleepRemove(TaskVarType* pTaskVar);
extern int Os_ListWait(TaskListType* list, const struct timespec *abstime);
extern int Os_ListPost(TaskListType* list, boolean schedule);
extern void Os_ListDetach(TaskVarType *pTaskVar, boolean AddReady);
extern int Os_PortInstallSignal(TaskVarType* pTaskVar, int sig, void* handler);
extern void Os_FreeSignalHandler(struct pthread* tid);
extern void Os_SignalInit(void);
extern void Os_SignalBroadCast(int signo);
#endif
#endif /* KERNEL_INTERNAL_H_ */
