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
/* ============================ [ INCLUDES  ] ====================================================== */
#include "rtthread.h"
#include "rthw.h"
#include "Os.h"
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
#define AS_LOG_OS 1
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
TickType				OsTickCounter;
#ifndef USE_STDRT
#ifdef RT_USING_HEAP
static rt_uint8_t heap[RT_HEAP_SIZE];
#endif
#endif
/* ============================ [ LOCALS    ] ====================================================== */
#if RT_THREAD_PRIORITY_MAX  < TASK_NUM
#error please set RT_THREAD_PRIORITY_MAX  bigger than TASK_NUM
#endif
static struct rt_thread taskId[TASK_NUM];
static struct rt_event  taskEvent[TASK_NUM];
static struct rt_timer  osTmr[ALARM_NUM];

static void _TaskProcess(void *p_arg)
{
	for( ;; )
	{
		WaitEvent(OS_EVENT_TASK_ACTIVATION);
		ClearEvent(OS_EVENT_TASK_ACTIVATION);
		TaskList[(uint32)p_arg].main();
	}

}

static void _AlarmProcess(void *parg)
{
	AlarmList[(uint32)parg].main();
}
/* ============================ [ FUNCTIONS ] ====================================================== */

FUNC(StatusType,MEM_ACTIVATE_TASK) 	 ActivateTask    ( TaskType TaskId)
{
	StatusType ercd = E_OK;
	if (TaskId < TASK_NUM)
	{
#ifdef __WINDOWS__
		ercd = SetEvent2(TaskId,OS_EVENT_TASK_ACTIVATION);
#else
		ercd = SetEvent(TaskId,OS_EVENT_TASK_ACTIVATION);
#endif
	}
	else
	{
		ercd = E_OS_ID;
		asAssert(0);
	}
	return ercd;
}

FUNC(StatusType,MEM_ACTIVATE_TASK) 	 TerminateTask   ( void )
{
	StatusType ercd = E_OK;
	/*   This is just empty, let the Task return form then main entry to
	 * the _TaskProcess handle, and then the Task wait its next activation
	 * by set the activation event<OS_EVENT_TASK_ACTIVATION> */
	return ercd;
}

FUNC(StatusType,MEM_GetTaskID) 		GetTaskID     ( TaskRefType TaskID )
{
	StatusType ercd = E_OK;
	rt_thread_t curThread;

	rt_enter_critical();

	curThread = rt_thread_self();

	if(curThread->init_priority < TASK_NUM)
	{
		*TaskID = curThread->init_priority;
	}
	else
	{
		ercd = E_OS_ACCESS;
		asAssert(0);
	}

	rt_exit_critical();

	return ercd;
}
FUNC(StatusType,MEM_GetResource) GetResource ( ResourceType ResID )
{
	StatusType ercd = E_OK;

	return ercd;
}

FUNC(StatusType,MEM_ReleaseResource) ReleaseResource ( ResourceType ResID )
{
	StatusType ercd = E_OK;

	return ercd;
}

#ifdef __WINDOWS__
FUNC(StatusType,MEM_SetEvent)        SetEvent2        ( TaskType tskid , EventMaskType mask )
#else
FUNC(StatusType,MEM_SetEvent)        SetEvent        ( TaskType tskid , EventMaskType mask )
#endif
{
	StatusType ercd = E_OK;

	if (tskid < TASK_NUM)
	{
		rt_err_t err = rt_event_send(&taskEvent[tskid],mask);
		if(err != RT_EOK)
		{
			ercd = E_OS_ACCESS;
			asAssert(0);
		}
	}
	else
	{
		ercd = E_OS_ID;
		asAssert(0);
	}
	return ercd;
}


StatusType ClearEvent ( EventMaskType mask )
{
	StatusType ercd = E_OK;

	TaskType tskid;

	GetTaskID(&tskid);

	if (tskid < TASK_NUM)
	{
		rt_err_t err = rt_event_recv(&taskEvent[tskid],mask,RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR,0,NULL);
		if(err != RT_EOK)
		{
			ercd = E_OS_ACCESS;
			asAssert(0);
		}
	}
	else
	{
		ercd = E_OS_ID;
		asAssert(0);
	}

	return ercd;
}

StatusType GetEvent ( TaskType tskid , EventMaskRefType p_mask )
{
	StatusType ercd = E_OK;

	if (tskid < TASK_NUM)
	{
		rt_err_t err = rt_event_recv(&taskEvent[tskid],0xFFFFFFFFUL,RT_EVENT_FLAG_OR,0,p_mask);
		if(err != RT_EOK)
		{
			if(err == -RT_ETIMEOUT)
			{
				*p_mask=0;
			}
			else
			{
				ercd = E_OS_ACCESS;
				asAssert(0);
			}
		}
	}
	else
	{
		ercd = E_OS_ID;
		asAssert(0);
	}
	return ercd;
}

StatusType WaitEvent ( EventMaskType mask )
{
	StatusType ercd = E_OK;
	TaskType tskid;

	GetTaskID(&tskid);

	if (tskid < TASK_NUM)
	{
		rt_err_t err = rt_event_recv(&taskEvent[tskid],mask,RT_EVENT_FLAG_OR,-1,NULL);
		if(err != RT_EOK)
		{
			ercd = E_OS_ACCESS;
			asAssert(0);
		}
	}
	else
	{
		ercd = E_OS_ID;
		asAssert(0);
	}
	return ercd;
}

FUNC(void,MEM_OsTick) OsTick ( void )
{
	OsTickCounter ++;

	if(0 == OsTickCounter)
	{
		OsTickCounter = 1;
	}
}

FUNC(StatusType,MEM_GetAlarmBase) GetAlarmBase ( AlarmType AlarmId, AlarmBaseRefType Info )
{

	Info[0].maxallowedvalue = RT_TICK_MAX/2;
	Info[0].ticksperbase     = 1u;
	Info[0].mincycle        = 1u;

	return E_OK;
}

FUNC(StatusType,MEM_GetAlarm) GetAlarm(AlarmType AlarmId, TickRefType Tick)
{
	return E_OS_NOFUNC;
}

FUNC(StatusType,MEM_SetRelAlarm) SetRelAlarm ( AlarmType AlarmId, TickType Increment, TickType Cycle )
{
	StatusType ercd = E_OK;

	if(AlarmId < ALARM_NUM)
	{
		if(osTmr[AlarmId].parent.flag & RT_TIMER_FLAG_ACTIVATED)
		{
			ercd = E_OS_STATE;
		}
		else
		{
			rt_err_t err;

			if(Cycle > 0)
			{
				rt_timer_control(&osTmr[AlarmId], RT_TIMER_CTRL_SET_TIME, &Cycle);
				rt_timer_control(&osTmr[AlarmId], RT_TIMER_CTRL_SET_PERIODIC, NULL);
			}
			else
			{
				rt_timer_control(&osTmr[AlarmId], RT_TIMER_CTRL_SET_TIME, &Increment);
				rt_timer_control(&osTmr[AlarmId], RT_TIMER_CTRL_SET_ONESHOT, NULL);
			}

			err = rt_timer_start(&osTmr[AlarmId]);
			if(RT_EOK != err)
			{
				ercd = E_OS_ACCESS;
			}
		}
	}
	else
	{
		ercd = E_OS_ID;
	}
	return ercd;   
}

FUNC(StatusType,MEM_SetAbsAlarm) SetAbsAlarm ( AlarmType AlarmId, TickType Start, TickType Cycle )
{
	return SetRelAlarm(AlarmId,Start-rt_tick_get(),Cycle);
}

FUNC(StatusType,MEM_CancelAlarm) CancelAlarm ( AlarmType AlarmId )
{
	StatusType ercd = E_OK;
	if(AlarmId < ALARM_NUM)
	{
		/* timer maybe already stopped, so no check of the error code */
		(void)rt_timer_stop(&osTmr[AlarmId]);
	}
	else
	{
		ercd = E_OS_ID;
	}
	return ercd;
}

FUNC(StatusType,MEM_Schedule)       Schedule ( void )
{
	StatusType ercd = E_OK;

	rt_thread_delay(1);
	
	return ercd;
}

FUNC(void,MEM_StartOS)              StartOS       ( AppModeType Mode )
{
	uint32 i;
	rt_err_t  ercd;
	const task_declare_t* td;

	for(i=0;i<TASK_NUM;i++)
	{
		td = &TaskList[i];
		ercd = rt_thread_init(&taskId[i],td->name,_TaskProcess,(void*)i,td->pstk,td->stk_size,td->priority,1);
		asAssert(ercd==RT_EOK);
		ercd = rt_event_init(&taskEvent[i],td->name,0);
		asAssert(ercd==RT_EOK);
		ercd = rt_thread_startup(&taskId[i]);
		asAssert(ercd==RT_EOK);		
		if(td->autostart)
		{
			ActivateTask(i);
		}
	}

	for(i=0;i<ALARM_NUM;i++)
	{
		rt_timer_init(&osTmr[i],AlarmList[i].name, _AlarmProcess, (void*)(long)i,
					  0,
					  RT_TIMER_FLAG_ONE_SHOT);
	}

	StartupHook();
}

FUNC(void,MEM_ShutdownOS)  ShutdownOS ( StatusType ercd )
{
	(void)ercd;
	while(1);
}
