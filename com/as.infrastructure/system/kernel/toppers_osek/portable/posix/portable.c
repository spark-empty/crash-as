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
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <errno.h>
#include <sys/time.h>
#include <time.h>
#include <sys/times.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include "osek_kernel.h"
#include "task.h"
#include <setjmp.h>
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
#define AS_LOG_OS 0
#define AS_LOG_ISR 1
#define configASSERT(x)	asAssert(x)

#define MAX_NUMBER_OF_TASKS 		( _POSIX_THREAD_THREADS_MAX )

#define pdFALSE			( ( BaseType_t ) 0 )
#define pdTRUE			( ( BaseType_t ) 1 )

#define pdPASS			( pdTRUE )
#define pdFAIL			( pdFALSE )

#define portTICK_PERIOD_MS 1

#define portMAX_INTERRUPTS				( ( uint32_t ) sizeof( uint32_t ) * 8UL ) /* The number of bits in an uint32_t. */
#define portNO_CRITICAL_NESTING 		( ( uint32_t ) 0 )

#define portSTACK_TYPE  unsigned long
#define portBASE_TYPE   long
#define portLONG		int

#define portTickType TickType

/* Posix Signal definitions that can be changed or read as appropriate. */
#define SIG_SUSPEND					SIGUSR1
#define SIG_RESUME					SIGUSR2

/* Enable the following hash defines to make use of the real-time tick where time progresses at real-time. */
#define SIG_TICK					SIGALRM
#define TIMER_TYPE					ITIMER_REAL

#define configTICK_RATE_HZ   1000
#define portTICK_RATE_MS				( ( portTickType ) 1000 / configTICK_RATE_HZ )
#define portTICK_RATE_MICROSECONDS		( ( portTickType ) 1000000 / configTICK_RATE_HZ )

/* ============================ [ TYPES     ] ====================================================== */
/* The WIN32 simulator runs each task in a thread.  The context switching is
managed by the threads, so the task stack does not have to be managed directly,
although the task stack is still used to hold an xThreadState structure this is
the only thing it will ever hold.  The structure indirectly maps the task handle
to a thread handle. */
typedef struct
{
	/* Handle of the thread that executes the task. */
	pthread_t hThread;
	jmp_buf jmp;
} xThreadState;

typedef long BaseType_t;

typedef TickType TickType_t;
typedef uint8    StackType_t;
typedef void (*TaskFunction_t)( void * );
/* ============================ [ DECLARES  ] ====================================================== */

/* ============================ [ DATAS     ] ====================================================== */
static xThreadState pxThreads[TASK_NUM];
static pthread_once_t hSigSetupThread = PTHREAD_ONCE_INIT;
static pthread_attr_t xThreadAttributes;
static pthread_mutex_t xSuspendResumeThreadMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t xSingleThreadMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_t hMainThread = ( pthread_t )NULL;
/*-----------------------------------------------------------*/
static volatile portBASE_TYPE xSentinel = 0;
static volatile portBASE_TYPE xSchedulerEnd = pdFALSE;
static volatile portBASE_TYPE xInterruptsEnabled = pdTRUE;
static volatile unsigned portBASE_TYPE uxCriticalNesting = 0;
static pthread_mutex_t isrAccess = PTHREAD_MUTEX_INITIALIZER;
static volatile portBASE_TYPE xServicingTick = pdFALSE;

/* ============================ [ LOCALS    ] ====================================================== */


/*-----------------------------------------------------------*/

/*
 * Setup the timer to generate the tick interrupts.
 */
void prvSetupTimerInterrupt( void );
void prvSuspendSignalHandler(int sig);
void prvResumeSignalHandler(int sig);
void prvSetupSignalsAndSchedulerPolicy( void );
void prvSuspendThread( pthread_t xThreadId );
void prvResumeThread( pthread_t xThreadId );
/*-----------------------------------------------------------*/

/*
 * Exception handlers.
 */
void vPortYield( void );
void vPortSystemTickHandler( int sig );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
void vPortStartFirstTask( void );
/*-----------------------------------------------------------*/
void vPortStartFirstTask( void )
{
	/* Initialise the critical nesting count ready for the first task. */
	uxCriticalNesting = 0;

	/* Start the first task. */

	callevel = TCL_TASK;

	runtsk = schedtsk;

	ASLOG(OS,"switch to task %d\n",runtsk);

	/* Start the first task. */
	prvResumeThread( pxThreads[runtsk].hThread  );
}
/*-----------------------------------------------------------*/

void vPortYield( void )
{
	if ( 0 == pthread_mutex_lock( &xSingleThreadMutex ) )
	{
		if ( runtsk != schedtsk )
		{
			TaskType saved_runtsk = runtsk;
			/* Switch tasks. */
			ASLOG(OS,"switch from task %d to task %d\n",runtsk,schedtsk);
			runtsk = schedtsk;

			callevel = TCL_TASK;
			prvResumeThread( pxThreads[runtsk].hThread );

			prvSuspendThread( pxThreads[saved_runtsk].hThread );
		}
		else
		{
			/* Yielding to self */
			(void)pthread_mutex_unlock( &xSingleThreadMutex );
		}
	}
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
void prvSetupTimerInterrupt( void )
{
struct itimerval itimer, oitimer;
portTickType xMicroSeconds = portTICK_RATE_MICROSECONDS;

	/* Initialise the structure with the current timer information. */
	if ( 0 == getitimer( TIMER_TYPE, &itimer ) )
	{
		/* Set the interval between timer events. */
		itimer.it_interval.tv_sec = 0;
		itimer.it_interval.tv_usec = xMicroSeconds;

		/* Set the current count-down. */
		itimer.it_value.tv_sec = 0;
		itimer.it_value.tv_usec = xMicroSeconds;

		/* Set-up the timer interrupt. */
		if ( 0 != setitimer( TIMER_TYPE, &itimer, &oitimer ) )
		{
			ASLOG(OS, "Set Timer problem.\n" );
		}
	}
	else
	{
		ASLOG(OS, "Get Timer problem.\n" );
	}
}

void prvProcessTickInterrupt( void )
{
	UINT8 saved_callevel = callevel;
	callevel = TCL_ISR2;
	SignalCounter(0);
	callevel = saved_callevel;

}
/*-----------------------------------------------------------*/
void vPortSystemTickHandler( int sig )
{
	ASLOG(OFF,"xInterruptsEnabled=%d,xServicingTick=%d\n",xInterruptsEnabled,xServicingTick);
	if ( ( pdTRUE == xInterruptsEnabled ) && ( pdTRUE != xServicingTick ) )
	{
		if ( 0 == pthread_mutex_trylock( &xSingleThreadMutex ) )
		{
			xServicingTick = pdTRUE;

			uxCriticalNesting ++;

			// TODO: when this function start running, should make sure all thread suspened
			prvProcessTickInterrupt();

			uxCriticalNesting --;

			/* If the task selected to enter the running state is not the task
			that is already in the running state. */
			if( runtsk != schedtsk )
			{
				TaskType saved_runtsk = runtsk;

				ASLOG(OS,"isr switch from task %d to task %d\n",runtsk,schedtsk);

				runtsk = schedtsk;

				if(runtsk!=INVALID_TASK)
				{
					callevel = TCL_TASK;
					prvResumeThread( pxThreads[runtsk].hThread );
				}
				else
				{
					callevel = TCL_NULL;
				}

				if(saved_runtsk!=INVALID_TASK)
				{
					/* Suspend the old thread. */
					prvSuspendThread( pxThreads[saved_runtsk].hThread );
				}
				else
				{
					(void)pthread_mutex_unlock( &xSingleThreadMutex );
				}
			}
			else
			{
				(void)pthread_mutex_unlock( &xSingleThreadMutex );
			}

			xServicingTick = pdFALSE;
		}
	}
}
/*-----------------------------------------------------------*/

void prvSuspendSignalHandler(int sig)
{
sigset_t xSignals;

	ASLOG(OFF, "prvSuspendSignalHandler\n" );

	/* Only interested in the resume signal. */
	sigemptyset( &xSignals );
	sigaddset( &xSignals, SIG_RESUME );
	xSentinel = 1;

	/* Unlock the Single thread mutex to allow the resumed task to continue. */
	if ( 0 != pthread_mutex_unlock( &xSingleThreadMutex ) )
	{
		ASLOG(OS, "Releasing someone else's lock.\n" );
	}

	/* Wait on the resume signal. */
	if ( 0 != sigwait( &xSignals, &sig ) )
	{
		ASLOG(OS, "SSH: Sw %d\n", sig );
	}
	/* Will resume here when the SIG_RESUME signal is received. */
}
/*-----------------------------------------------------------*/

void prvSuspendThread( pthread_t xThreadId )
{
	ASLOG(OFF, "prvSuspendThread(%Xh)\n", xThreadId);
	portBASE_TYPE xResult = pthread_mutex_lock( &xSuspendResumeThreadMutex );
	if ( 0 == xResult )
	{
		/* Set-up for the Suspend Signal handler? */
		xSentinel = 0;
		xResult = pthread_mutex_unlock( &xSuspendResumeThreadMutex );
		xResult = pthread_kill( xThreadId, SIG_SUSPEND );
		while ( ( xSentinel == 0 ) && ( pdTRUE != xServicingTick ) )
		{
			sched_yield();
		}
	}
}
/*-----------------------------------------------------------*/

void prvResumeSignalHandler(int sig)
{
	ASLOG(OFF, "prvResumeSignalHandler\n" );
	/* Yield the Scheduler to ensure that the yielding thread completes. */
	if ( 0 == pthread_mutex_lock( &xSingleThreadMutex ) )
	{
		(void)pthread_mutex_unlock( &xSingleThreadMutex );
	}
}
/*-----------------------------------------------------------*/

void prvResumeThread( pthread_t xThreadId )
{
portBASE_TYPE xResult;

	ASLOG(OFF, "prvResumeThread(%Xh)\n", xThreadId);
	if ( 0 == pthread_mutex_lock( &xSuspendResumeThreadMutex ) )
	{
		if ( pthread_self() != xThreadId )
		{
			xResult = pthread_kill( xThreadId, SIG_RESUME );
		}
		xResult = pthread_mutex_unlock( &xSuspendResumeThreadMutex );
	}
	(void)xResult;
}
/*-----------------------------------------------------------*/

void prvSetupSignalsAndSchedulerPolicy( void )
{
/* The following code would allow for configuring the scheduling of this task as a Real-time task.
 * The process would then need to be run with higher privileges for it to take affect.
int iPolicy;
int iResult;
int iSchedulerPriority;
	iResult = pthread_getschedparam( pthread_self(), &iPolicy, &iSchedulerPriority );
	iResult = pthread_attr_setschedpolicy( &xThreadAttributes, SCHED_FIFO );
	iPolicy = SCHED_FIFO;
	iResult = pthread_setschedparam( pthread_self(), iPolicy, &iSchedulerPriority );		*/

struct sigaction sigsuspendself, sigresume, sigtick;


	sigsuspendself.sa_flags = 0;
	sigsuspendself.sa_handler = prvSuspendSignalHandler;
	sigfillset( &sigsuspendself.sa_mask );

	sigresume.sa_flags = 0;
	sigresume.sa_handler = prvResumeSignalHandler;
	sigfillset( &sigresume.sa_mask );

	sigtick.sa_flags = 0;
	sigtick.sa_handler = vPortSystemTickHandler;
	sigfillset( &sigtick.sa_mask );

	if ( 0 != sigaction( SIG_SUSPEND, &sigsuspendself, NULL ) )
	{
		ASLOG(OS, "Problem installing SIG_SUSPEND_SELF\n" );
	}
	if ( 0 != sigaction( SIG_RESUME, &sigresume, NULL ) )
	{
		ASLOG(OS, "Problem installing SIG_RESUME\n" );
	}
	if ( 0 != sigaction( SIG_TICK, &sigtick, NULL ) )
	{
		ASLOG(OS, "Problem installing SIG_TICK\n" );
	}
	ASLOG(OS,"Running as PID: %d\n", getpid() );
}

/*-----------------------------------------------------------*/

void vPortFindTicksPerSecond( void )
{
	/* Needs to be reasonably high for accuracy. */
	unsigned long ulTicksPerSecond = sysconf(_SC_CLK_TCK);
	ASLOG(OS, "Timer Resolution for Run TimeStats is %ld ticks per second.\n", ulTicksPerSecond );
}
/*-----------------------------------------------------------*/

unsigned long ulPortGetTimerValue( void )
{
struct tms xTimes;
	unsigned long ulTotalTime = times( &xTimes );
	/* Return the application code times.
	 * The timer only increases when the application code is actually running
	 * which means that the total execution times should add up to 100%.
	 */
	return ( unsigned long ) xTimes.tms_utime;

	/* Should check ulTotalTime for being clock_t max minus 1. */
	(void)ulTotalTime;
}
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
void* prvToppersOSEK_TaskProcess(void * param)
{
	TaskType taskId= (TaskType)(unsigned long)param;

	if ( 0 == pthread_mutex_lock( &xSingleThreadMutex ) )
	{
		prvSuspendThread( pthread_self() );
	}

	for(;;)
	{
		int rv;

		rv = setjmp(pxThreads[taskId].jmp);
		if(0 == rv)
		{
			lock_cpu();
			call_pretaskhook();
			tcb_curpri[runtsk] = tinib_exepri[runtsk];
			unlock_cpu();
			tinib_task[taskId]();
		}
		else
		{
			/* terminate */
			lock_cpu();
			call_posttaskhook();
			unlock_cpu();
			vPortYield();
		}

	}
	return NULL;
}


/* ============================ [ FUNCTIONS ] ====================================================== */

/*-----------------------------------------------------------*/
#if 0
void disable_int(void)
{
	pthread_mutex_lock(&isrAccess);
	asAssert(TRUE==xInterruptsEnabled);
	if(callevel!=TCL_ISR2)
	{
		(void)pthread_mutex_lock( &xSingleThreadMutex );
	}
	xInterruptsEnabled = pdFALSE;
	ASLOG(ISR, "disable_int\n" );
	pthread_mutex_unlock(&isrAccess);
}
void enable_int(void)
{
	pthread_mutex_lock(&isrAccess);
	asAssert(FALSE==xInterruptsEnabled);
	xInterruptsEnabled = pdTRUE;
	if(callevel!=TCL_ISR2)
	{
		(void)pthread_mutex_unlock( &xSingleThreadMutex );
	}
	ASLOG(ISR, "enable_int\n" );
	pthread_mutex_unlock(&isrAccess);
}
imask_t __Irq_Save(void)
{
	imask_t ret;

	pthread_mutex_lock(&isrAccess);

	ret = xInterruptsEnabled;

	if(xInterruptsEnabled)
	{
		(void)pthread_mutex_lock( &xSingleThreadMutex );
	}
	xInterruptsEnabled = pdFALSE;
	ASLOG(ISR, "__Irq_Save(%d)\n",ret);
	//asCallStack();
	pthread_mutex_unlock(&isrAccess);

	return ret;
}
void Irq_Restore(imask_t irq_state)
{
	pthread_mutex_lock(&isrAccess);

	xInterruptsEnabled = irq_state;

	if(xInterruptsEnabled)
	{
		(void)pthread_mutex_unlock( &xSingleThreadMutex );
	}
	ASLOG(ISR, "Irq_Restore(%d)\n",irq_state);
	pthread_mutex_unlock(&isrAccess);
}
#else
void disable_int( void )
{
	pthread_mutex_lock(&isrAccess);

	ASLOG(ISR, "disable_int(%d)\n",uxCriticalNesting);

	uxCriticalNesting ++;

	if(1 == uxCriticalNesting)
	{
		(void)pthread_mutex_lock( &xSingleThreadMutex );
	}
	xInterruptsEnabled = pdFALSE;

	pthread_mutex_unlock(&isrAccess);
}
/*-----------------------------------------------------------*/

void enable_int( void )
{
	pthread_mutex_lock(&isrAccess);
	/* Check for unmatched exits. */
	if ( uxCriticalNesting > 0 )
	{
		uxCriticalNesting--;
	}

	/* If we have reached 0 then re-enable the interrupts. */
	if( uxCriticalNesting == 0 )
	{
		xInterruptsEnabled = pdTRUE;
		(void)pthread_mutex_unlock( &xSingleThreadMutex );
	}

	ASLOG(ISR, "enable_int(%d)\n",uxCriticalNesting);
	pthread_mutex_unlock(&isrAccess);
}

imask_t __Irq_Save(void)
{
	disable_int();

	return 0;
}
void Irq_Restore(imask_t irq_state)
{
	enable_int();
}
#endif
void dispatch(void)
{
	unlock_cpu();
	vPortYield();
	lock_cpu();
}

/*-----------------------------------------------------------*/
void set_ipl(IPL ipl)
{

}
IPL  current_ipl(void)
{
	return 0;
}
void start_dispatch(void)
{
	portBASE_TYPE xResult;
	int iSignal;
	sigset_t xSignals;
	sigset_t xSignalToBlock;
	sigset_t xSignalsBlocked;

	/* Establish the signals to block before they are needed. */
	sigfillset( &xSignalToBlock );

	/* Block until the end */
	(void)pthread_sigmask( SIG_SETMASK, &xSignalToBlock, &xSignalsBlocked );

	/* Start the timer that generates the tick ISR.  Interrupts are disabled
	here already. */
	prvSetupTimerInterrupt();

	/* Start the first task. Will not return unless all threads are killed. */
	vPortStartFirstTask();

	/* This is the end signal we are looking for. */
	sigemptyset( &xSignals );
	sigaddset( &xSignals, SIG_RESUME );

	while ( pdTRUE != xSchedulerEnd )
	{
		if ( 0 != sigwait( &xSignals, &iSignal ) )
		{
			ASLOG(OS, "Main thread spurious signal: %d\n", iSignal );
		}
	}

	ASLOG(OS, "Cleaning Up, Exiting.\n" );
	/* Cleanup the mutexes */
	xResult = pthread_mutex_destroy( &xSuspendResumeThreadMutex );
	xResult = pthread_mutex_destroy( &xSingleThreadMutex );

	(void)xResult;
	/* Should not get here! */
	return;
}
void exit_and_dispatch(void)
{
	unlock_cpu();
	longjmp(pxThreads[runtsk].jmp,1);
}
void activate_context(TaskType TaskID)
{
	(void)pthread_once( &hSigSetupThread, prvSetupSignalsAndSchedulerPolicy );

	if ( (pthread_t)NULL == hMainThread )
	{
		hMainThread = pthread_self();
	}

	/* No need to join the threads. */
	pthread_attr_init( &xThreadAttributes );
	pthread_attr_setdetachstate( &xThreadAttributes, PTHREAD_CREATE_DETACHED );

	/* Create the new pThread. */
	if(0 == pxThreads[TaskID].hThread)
	{
		if ( 0 == pthread_mutex_lock( &xSingleThreadMutex ) )
		{
			xSentinel = 0;
			int ercd = pthread_create( &( pxThreads[ TaskID ].hThread ), &xThreadAttributes, prvToppersOSEK_TaskProcess, (void*)(unsigned long)TaskID );
			/* Create the thread itself. */
			asAssert( (0==ercd) && pxThreads[TaskID].hThread );

			/* Wait until the task suspends. */
			(void)pthread_mutex_unlock( &xSingleThreadMutex );
			while ( xSentinel == 0 );
		}
	}
}

void cpu_initialize(void)
{
	memset(pxThreads,0,sizeof(pxThreads));
}
void sys_initialize(void)
{

}
void tool_initialize(void)
{

}

void cpu_terminate(void)
{

}
void sys_exit(void)
{
	exit(-1);
}


