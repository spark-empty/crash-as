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

#include <Windows.h>
#include "Std_Types.h"
#include "osek_kernel.h"
#include "task.h"
#include <setjmp.h>
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
#define AS_LOG_OS 0
#define configASSERT(x)	asAssert(x)

#define pdFALSE			( ( BaseType_t ) 0 )
#define pdTRUE			( ( BaseType_t ) 1 )

#define pdPASS			( pdTRUE )
#define pdFAIL			( pdFALSE )

#define portTICK_PERIOD_MS 1

#define portMAX_INTERRUPTS				( ( uint32_t ) sizeof( uint32_t ) * 8UL ) /* The number of bits in an uint32_t. */
#define portNO_CRITICAL_NESTING 		( ( uint32_t ) 0 )

/* ============================ [ TYPES     ] ====================================================== */
/* The WIN32 simulator runs each task in a thread.  The context switching is
managed by the threads, so the task stack does not have to be managed directly,
although the task stack is still used to hold an xThreadState structure this is
the only thing it will ever hold.  The structure indirectly maps the task handle
to a thread handle. */
typedef struct
{
	/* Handle of the thread that executes the task. */
	void *pvThread;
	/* Handle of the thread that task has been activated */
	void *pvEvent;
	jmp_buf jmp;
} xThreadState;

typedef long BaseType_t;

typedef TickType TickType_t;
typedef uint8    StackType_t;
typedef void (*TaskFunction_t)( void * );
/* ============================ [ DECLARES  ] ====================================================== */
void vPortEnterCritical( void );
void vPortExitCritical( void );
/* ============================ [ DATAS     ] ====================================================== */
/* Simulated interrupts waiting to be processed.  This is a bit mask where each
bit represents one interrupt, so a maximum of 32 interrupts can be simulated. */
static volatile uint32_t ulPendingInterrupts = 0UL;

/* An event used to inform the simulated interrupt processing thread (a high
priority thread that simulated interrupt processing) that an interrupt is
pending. */
static void *pvInterruptEvent = NULL;

/* Mutex used to protect all the simulated interrupt variables that are accessed
by multiple threads. */
static void *pvInterruptEventMutex = NULL;

/* The critical nesting count for the currently executing task.  This is
initialised to a non-zero value so interrupts do not become enabled during
the initialisation phase.  As each task has its own critical nesting value
ulCriticalNesting will get set to zero when the first task runs.  This
initialisation is probably not critical in this simulated environment as the
simulated interrupt handlers do not get created until the FreeRTOS scheduler is
started anyway. */
static uint32_t ulCriticalNesting = 9999UL;

/* Handlers for all the simulated software interrupts.  The first two positions
are used for the Yield and Tick interrupts so are handled slightly differently,
all the other interrupts can be user defined. */
static uint32_t (*ulIsrHandler[ portMAX_INTERRUPTS ])( void ) = { 0 };

/* Used to ensure nothing is processed during the startup sequence. */
static BaseType_t xPortRunning = pdFALSE;

static xThreadState portThreadState[TASK_NUM];
/* ============================ [ LOCALS    ] ====================================================== */
/*
 * Created as a high priority thread, this function uses a timer to simulate
 * a tick interrupt being generated on an embedded target.  In this Windows
 * environment the timer does not achieve anything approaching real time
 * performance though.
 */
static DWORD WINAPI prvSimulatedPeripheralTimer( LPVOID lpParameter );

/*
 * Process all the simulated interrupts - each represented by a bit in
 * ulPendingInterrupts variable.
 */
static void prvProcessSimulatedInterrupts( void );

/*
 * Interrupt handlers used by the kernel itself.  These are executed from the
 * simulated interrupt handler thread.
 */
static uint32_t prvProcessYieldInterrupt( void );
static uint32_t prvProcessTickInterrupt( void );

/*
 * Called when the process exits to let Windows know the high timer resolution
 * is no longer required.
 */
static BOOL WINAPI prvEndProcess( DWORD dwCtrlType );
static DWORD WINAPI prvSimulatedPeripheralTimer( LPVOID lpParameter )
{
TickType_t xMinimumWindowsBlockTime;
TIMECAPS xTimeCaps;

	/* Set the timer resolution to the maximum possible. */
	if( timeGetDevCaps( &xTimeCaps, sizeof( xTimeCaps ) ) == MMSYSERR_NOERROR )
	{
		xMinimumWindowsBlockTime = ( TickType_t ) xTimeCaps.wPeriodMin;
		timeBeginPeriod( xTimeCaps.wPeriodMin );

		/* Register an exit handler so the timeBeginPeriod() function can be
		matched with a timeEndPeriod() when the application exits. */
		SetConsoleCtrlHandler( prvEndProcess, TRUE );
	}
	else
	{
		xMinimumWindowsBlockTime = ( TickType_t ) 20;
	}

	/* Just to prevent compiler warnings. */
	( void ) lpParameter;

	for( ;; )
	{
		/* Wait until the timer expires and we can access the simulated interrupt
		variables.  *NOTE* this is not a 'real time' way of generating tick
		events as the next wake time should be relative to the previous wake
		time, not the time that Sleep() is called.  It is done this way to
		prevent overruns in this very non real time simulated/emulated
		environment. */
		if( portTICK_PERIOD_MS < xMinimumWindowsBlockTime )
		{
			Sleep( xMinimumWindowsBlockTime );
		}
		else
		{
			Sleep( portTICK_PERIOD_MS );
		}

		while( FALSE == xPortRunning ) Sleep(1);

		WaitForSingleObject( pvInterruptEventMutex, INFINITE );

		/* The timer has expired, generate the simulated tick event. */
		ulPendingInterrupts |= ( 1 << portINTERRUPT_TICK );

		/* The interrupt is now pending - notify the simulated interrupt
		handler thread. */
		if( ulCriticalNesting == 0 )
		{
			SetEvent( pvInterruptEvent );
		}

		/* Give back the mutex so the simulated interrupt handler unblocks
		and can	access the interrupt handler variables. */
		ReleaseMutex( pvInterruptEventMutex );
	}

	#ifdef __GNUC__
		/* Should never reach here - MingW complains if you leave this line out,
		MSVC complains if you put it in. */
		return 0;
	#endif
}
/*-----------------------------------------------------------*/

static BOOL WINAPI prvEndProcess( DWORD dwCtrlType )
{
TIMECAPS xTimeCaps;

	( void ) dwCtrlType;

	if( timeGetDevCaps( &xTimeCaps, sizeof( xTimeCaps ) ) == MMSYSERR_NOERROR )
	{
		/* Match the call to timeBeginPeriod( xTimeCaps.wPeriodMin ) made when
		the process started with a timeEndPeriod() as the process exits. */
		timeEndPeriod( xTimeCaps.wPeriodMin );
	}

	return pdPASS;
}
/*-----------------------------------------------------------*/

static uint32_t prvProcessYieldInterrupt( void )
{
	return pdTRUE;
}

static uint32_t prvProcessTickInterrupt( void )
{
	uint32_t ulSwitchRequired;
	uint8_t saved_callevel  = callevel;

	/* Process the tick itself. */
	asAssert( xPortRunning );

	callevel = TCL_ISR2;
	SignalCounter(0);
	callevel = saved_callevel;

	if(schedtsk != runtsk)
	{
		ulSwitchRequired = TRUE;
	}
	else
	{
		ulSwitchRequired = FALSE;
	}

	return ulSwitchRequired;
}
static void prvToppersOSEK_TaskProcess(void * param)
{
	TaskType taskId= (TaskType)(uint32)param;
	for(;;)
	{
		int rv;
		(void)WaitForSingleObject(portThreadState[taskId].pvEvent,INFINITE);
		rv = setjmp(portThreadState[taskId].jmp);
		if(0 == rv)
		{
			lock_cpu();
			call_pretaskhook();
			unlock_cpu();
			tcb_curpri[runtsk] = tinib_exepri[runtsk];
			tinib_task[taskId]();
		}
		else
		{
			/* terminate */
		}
	}
}

static void prvProcessSimulatedInterrupts( void )
{
uint32_t ulSwitchRequired, i;
xThreadState *pxThreadState;
void *pvObjectList[ 2 ];

	/* Going to block on the mutex that ensured exclusive access to the simulated
	interrupt objects, and the event that signals that a simulated interrupt
	should be processed. */
	pvObjectList[ 0 ] = pvInterruptEventMutex;
	pvObjectList[ 1 ] = pvInterruptEvent;

	/* Create a pending tick to ensure the first task is started as soon as
	this thread pends. */
	ulPendingInterrupts |= ( 1 << portINTERRUPT_TICK );
	SetEvent( pvInterruptEvent );

	xPortRunning = pdTRUE;
	ASLOG(OS,"portable is running...\n");
	for(;;)
	{
		WaitForMultipleObjects( sizeof( pvObjectList ) / sizeof( void * ), pvObjectList, TRUE, INFINITE );

		/* Used to indicate whether the simulated interrupt processing has
		necessitated a context switch to another task/thread. */
		ulSwitchRequired = pdFALSE;

		/* For each interrupt we are interested in processing, each of which is
		represented by a bit in the 32bit ulPendingInterrupts variable. */
		for( i = 0; i < portMAX_INTERRUPTS; i++ )
		{
			/* Is the simulated interrupt pending? */
			if( ulPendingInterrupts & ( 1UL << i ) )
			{
				/* Is a handler installed? */
				if( ulIsrHandler[ i ] != NULL )
				{
					/* Run the actual handler. */
					if( ulIsrHandler[ i ]() != pdFALSE )
					{
						ulSwitchRequired |= ( 1 << i );
					}
				}

				/* Clear the interrupt pending bit. */
				ulPendingInterrupts &= ~( 1UL << i );
			}
		}

		if( ulSwitchRequired != pdFALSE )
		{
			/* If the task selected to enter the running state is not the task
			that is already in the running state. */
			if( runtsk != schedtsk )
			{
				ASLOG(OS,"swtich from task<%d> to task<%d>\n",runtsk,schedtsk);

				if(runtsk!=INVALID_TASK)
				{
					/* Suspend the old thread. */
					pxThreadState = &portThreadState[runtsk];
					SuspendThread( pxThreadState->pvThread );
				}

				runtsk = schedtsk;

				if(runtsk!=INVALID_TASK)
				{
					callevel = TCL_TASK;
					/* Obtain the state of the task now selected to enter the
					Running state. */
					pxThreadState = &portThreadState[runtsk];
					ResumeThread( pxThreadState->pvThread );
				}
				else
				{
					callevel = TCL_NULL;
				}
			}
		}

		ReleaseMutex( pvInterruptEventMutex );
	}
}
/* ============================ [ FUNCTIONS ] ====================================================== */

void disable_int(void)
{
	while(ulCriticalNesting!=0)	Sleep(1);
	vPortEnterCritical();

	ASLOG(OS,"lock_cpu()\n");
}
void enable_int(void)
{
	vPortExitCritical();

	ASLOG(OS,"unlock_cpu()\n");
}

void dispatch(void)
{
	unlock_cpu();
	vPortGenerateSimulatedInterrupt( portINTERRUPT_YIELD );
	lock_cpu();
}
/*-----------------------------------------------------------*/

void vPortDeleteThread( void *pvTaskToDelete )
{
xThreadState *pxThreadState;
uint32_t ulErrorCode;

	/* Remove compiler warnings if configASSERT() is not defined. */
	( void ) ulErrorCode;

	/* Find the handle of the thread being deleted. */
	pxThreadState = ( xThreadState * ) ( *( uint32_t *) pvTaskToDelete );

	/* Check that the thread is still valid, it might have been closed by
	vPortCloseRunningThread() - which will be the case if the task associated
	with the thread originally deleted itself rather than being deleted by a
	different task. */
	if( pxThreadState->pvThread != NULL )
	{
		WaitForSingleObject( pvInterruptEventMutex, INFINITE );

		ulErrorCode = TerminateThread( pxThreadState->pvThread, 0 );
		configASSERT( ulErrorCode );

		ulErrorCode = CloseHandle( pxThreadState->pvThread );
		configASSERT( ulErrorCode );

		ReleaseMutex( pvInterruptEventMutex );
	}
}
/*-----------------------------------------------------------*/

void vPortCloseRunningThread( void *pvTaskToDelete, volatile BaseType_t *pxPendYield )
{
xThreadState *pxThreadState;
void *pvThread;
uint32_t ulErrorCode;

	/* Remove compiler warnings if configASSERT() is not defined. */
	( void ) ulErrorCode;

	/* Find the handle of the thread being deleted. */
	pxThreadState = ( xThreadState * ) ( *( uint32_t *) pvTaskToDelete );
	pvThread = pxThreadState->pvThread;

	/* Raise the Windows priority of the thread to ensure the FreeRTOS scheduler
	does not run and swap it out before it is closed.  If that were to happen
	the thread would never run again and effectively be a thread handle and
	memory leak. */
	SetThreadPriority( pvThread, THREAD_PRIORITY_ABOVE_NORMAL );

	/* This function will not return, therefore a yield is set as pending to
	ensure a context switch occurs away from this thread on the next tick. */
	*pxPendYield = pdTRUE;

	/* Mark the thread associated with this task as invalid so
	vPortDeleteThread() does not try to terminate it. */
	pxThreadState->pvThread = NULL;

	/* Close the thread. */
	ulErrorCode = CloseHandle( pvThread );
	configASSERT( ulErrorCode );

	ExitThread( 0 );
}
/*-----------------------------------------------------------*/

void vPortEndScheduler( void )
{
	/* This function IS NOT TESTED! */
	TerminateProcess( GetCurrentProcess(), 0 );
}
/*-----------------------------------------------------------*/

void vPortGenerateSimulatedInterrupt( uint32_t ulInterruptNumber )
{
	configASSERT( xPortRunning );

	if( ( ulInterruptNumber < portMAX_INTERRUPTS ) && ( pvInterruptEventMutex != NULL ) )
	{
		/* Yield interrupts are processed even when critical nesting is non-zero. */
		WaitForSingleObject( pvInterruptEventMutex, INFINITE );
		ulPendingInterrupts |= ( 1 << ulInterruptNumber );

		/* The simulated interrupt is now held pending, but don't actually process it
		yet if this call is within a critical section.  It is possible for this to
		be in a critical section as calls to wait for mutexes are accumulative. */
		if( ulCriticalNesting == 0 )
		{
			SetEvent( pvInterruptEvent );
		}

		ReleaseMutex( pvInterruptEventMutex );
	}
}
/*-----------------------------------------------------------*/

void vPortSetInterruptHandler( uint32_t ulInterruptNumber, uint32_t (*pvHandler)( void ) )
{
	if( ulInterruptNumber < portMAX_INTERRUPTS )
	{
		if( pvInterruptEventMutex != NULL )
		{
			WaitForSingleObject( pvInterruptEventMutex, INFINITE );
			ulIsrHandler[ ulInterruptNumber ] = pvHandler;
			ReleaseMutex( pvInterruptEventMutex );
		}
		else
		{
			ulIsrHandler[ ulInterruptNumber ] = pvHandler;
		}
	}
}
/*-----------------------------------------------------------*/

void vPortEnterCritical( void )
{
	if( xPortRunning == pdTRUE )
	{
		/* The interrupt event mutex is held for the entire critical section,
		effectively disabling (simulated) interrupts. */
		WaitForSingleObject( pvInterruptEventMutex, INFINITE );
		ulCriticalNesting++;
	}
	else
	{
		ulCriticalNesting++;
	}

	ASLOG(OFF,"vPortEnterCritical %d\n",ulCriticalNesting);
}
/*-----------------------------------------------------------*/

void vPortExitCritical( void )
{
int32_t lMutexNeedsReleasing;

	/* The interrupt event mutex should already be held by this thread as it was
	obtained on entry to the critical section. */

	lMutexNeedsReleasing = pdTRUE;

	if( ulCriticalNesting > portNO_CRITICAL_NESTING )
	{
		if( ulCriticalNesting == ( portNO_CRITICAL_NESTING + 1 ) )
		{
			ulCriticalNesting--;

			/* Were any interrupts set to pending while interrupts were
			(simulated) disabled? */
			if( ulPendingInterrupts != 0UL )
			{
				configASSERT( xPortRunning );
				SetEvent( pvInterruptEvent );

				/* Mutex will be released now, so does not require releasing
				on function exit. */
				lMutexNeedsReleasing = pdFALSE;
				ReleaseMutex( pvInterruptEventMutex );
			}
		}
		else
		{
			/* Tick interrupts will still not be processed as the critical
			nesting depth will not be zero. */
			ulCriticalNesting--;
		}
	}

	if( pvInterruptEventMutex != NULL )
	{
		if( lMutexNeedsReleasing == pdTRUE )
		{
			configASSERT( xPortRunning );
			ReleaseMutex( pvInterruptEventMutex );
		}
	}
	ASLOG(OFF,"vPortExitCritical  %d\n",ulCriticalNesting);
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
	void *pvHandle;
	int32_t lSuccess = pdPASS;
	xThreadState *pxThreadState;

	/* Install the interrupt handlers used by the scheduler itself. */
	vPortSetInterruptHandler( portINTERRUPT_YIELD, prvProcessYieldInterrupt );
	vPortSetInterruptHandler( portINTERRUPT_TICK, prvProcessTickInterrupt );

	/* Create the events and mutexes that are used to synchronise all the
	threads. */
	pvInterruptEventMutex = CreateMutex( NULL, FALSE, NULL );
	pvInterruptEvent = CreateEvent( NULL, FALSE, FALSE, NULL );

	if( ( pvInterruptEventMutex == NULL ) || ( pvInterruptEvent == NULL ) )
	{
		lSuccess = pdFAIL;
	}

	/* Set the priority of this thread such that it is above the priority of
	the threads that run tasks.  This higher priority is required to ensure
	simulated interrupts take priority over tasks. */
	pvHandle = GetCurrentThread();
	if( pvHandle == NULL )
	{
		lSuccess = pdFAIL;
	}

	if( lSuccess == pdPASS )
	{
		if( SetThreadPriority( pvHandle, THREAD_PRIORITY_NORMAL ) == 0 )
		{
			lSuccess = pdFAIL;
		}
		SetThreadPriorityBoost( pvHandle, TRUE );
		SetThreadAffinityMask( pvHandle, 0x01 );
	}

	if( lSuccess == pdPASS )
	{
		/* Start the thread that simulates the timer peripheral to generate
		tick interrupts.  The priority is set below that of the simulated
		interrupt handler so the interrupt event mutex is used for the
		handshake / overrun protection. */
		pvHandle = CreateThread( NULL, 0, prvSimulatedPeripheralTimer, NULL, 0, NULL );
		if( pvHandle != NULL )
		{
			SetThreadPriority( pvHandle, THREAD_PRIORITY_BELOW_NORMAL );
			SetThreadPriorityBoost( pvHandle, TRUE );
			SetThreadAffinityMask( pvHandle, 0x01 );
		}

		runtsk = schedtsk;

		ulCriticalNesting = portNO_CRITICAL_NESTING;

		if(runtsk != INVALID_TASK)
		{
			ASLOG(OS,"swtich to task<%d>\n",runtsk);
			/* Start the highest priority task by obtaining its associated thread
			state structure, in which is stored the thread handle. */
			pxThreadState = &portThreadState[runtsk];

			callevel = TCL_TASK;
			/* Bump up the priority of the thread that is going to run, in the
			hope that this will assist in getting the Windows thread scheduler to
			behave as an embedded engineer might expect. */
			ResumeThread( pxThreadState->pvThread );
		}

		/* Handle all simulated interrupts - including yield requests and
		simulated ticks. */
		prvProcessSimulatedInterrupts();
	}

	/* Would not expect to return from prvProcessSimulatedInterrupts(), so should
	not get here. */
	return;
}
void exit_and_dispatch(void)
{
	TaskType save_runtsk = runtsk;

	call_posttaskhook();

	unlock_cpu();

	vPortGenerateSimulatedInterrupt( portINTERRUPT_YIELD );

	longjmp(portThreadState[save_runtsk].jmp,1);
}
void activate_context(TaskType TaskID)
{
	if(NULL == portThreadState[TaskID].pvThread)
	{
		/* Create the thread itself. */
		portThreadState[TaskID].pvThread = CreateThread( NULL, 0, ( LPTHREAD_START_ROUTINE ) prvToppersOSEK_TaskProcess, (void*)(uint32)TaskID, CREATE_SUSPENDED, NULL );
		asAssert( portThreadState[TaskID].pvThread );
		SetThreadAffinityMask( portThreadState[TaskID].pvThread, 0x01 );
		SetThreadPriorityBoost( portThreadState[TaskID].pvThread, TRUE );
		SetThreadPriority( portThreadState[TaskID].pvThread, THREAD_PRIORITY_IDLE );
		/* Create the event for the thread */
		portThreadState[TaskID].pvEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
		asAssert(portThreadState[TaskID].pvEvent != NULL);
	}
	/* each time when do activate, make event ready */
	SetEvent(portThreadState[TaskID].pvEvent);
}

void cpu_initialize(void)
{
	memset(portThreadState,0,sizeof(portThreadState));
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

imask_t __Irq_Save(void)
{
	vPortEnterCritical();
	return ulCriticalNesting;
}
void Irq_Restore(imask_t irq_state)
{
	vPortExitCritical();
}

