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
#include "ucos_ii.h"
#include "Os.h"
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
#define AS_LOG_OS 1
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
TickType				OsTickCounter;
/* ============================ [ LOCALS    ] ====================================================== */
static OS_CPU_SR  cpu_sr = 0u;
static uint32_t isrDisableCounter = 0;


#if OS_MAX_FLAGS < TASK_NUM
#error please set OS_MAX_FLAGS bigger than TASK_NUM
#endif
static OS_FLAG_GRP* taskEvent[TASK_NUM];

#if OS_TMR_CFG_MAX < ALARM_NUM
#error please set OS_TMR_CFG_MAX bigger than ALARM_NUM
#endif
static OS_TMR* osTmr[ALARM_NUM];

static void uCOS_TaskProcess(void *p_arg)
{
	for( ;; )
	{
		WaitEvent(OS_EVENT_TASK_ACTIVATION);
		ClearEvent(OS_EVENT_TASK_ACTIVATION);
		TaskList[(uint32)p_arg].main();
	}

}

static void uCOS_AlarmProcess(void *ptmr, void *parg)
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
	 * the uCOS_TaskProcess handle, and then the Task wait its next activation
	 * by set the activation event<OS_EVENT_TASK_ACTIVATION> */
	return ercd;
}

FUNC(StatusType,MEM_GetTaskID) 		GetTaskID     ( TaskRefType TaskID )
{
#if      OS_CRITICAL_METHOD == 3
	OS_CPU_SR cpu_sr = 0u;
#endif
	StatusType ercd = E_OK;

	OS_ENTER_CRITICAL();
	if((OSTCBCur->OSTCBPrio>0) && (OSTCBCur->OSTCBPrio <= TASK_NUM))
	{
		*TaskID = OSTCBCur->OSTCBPrio-1;
	}
	else
	{
		ercd = E_OS_ACCESS;
		asAssert(0);
	}
	OS_EXIT_CRITICAL();

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
		OSFlagPost(taskEvent[tskid],(OS_FLAGS)mask,OS_FLAG_SET,&ercd);
		if(ercd != OS_ERR_NONE)
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
		OSFlagPost(taskEvent[tskid],(OS_FLAGS)mask,OS_FLAG_CLR,&ercd);
		if(ercd != OS_ERR_NONE)
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
		*p_mask = OSFlagQuery(taskEvent[tskid],&ercd);
		if(ercd != OS_ERR_NONE)
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

StatusType WaitEvent ( EventMaskType mask )
{
	StatusType ercd = E_OK;
	TaskType tskid;

	GetTaskID(&tskid);

	if (tskid < TASK_NUM)
	{
		OSFlagPend(taskEvent[tskid],(OS_FLAGS)mask,OS_FLAG_WAIT_SET_ANY,0,&ercd);

		if(ercd != OS_ERR_NONE)
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

	Info[0].maxallowedvalue = TICK_MAX;
	Info[0].ticksperbase     = 1u;
	Info[0].mincycle        = 1u;

	return E_OK;
}

FUNC(StatusType,MEM_GetAlarm) GetAlarm(AlarmType AlarmId, TickRefType Tick)
{
	return E_OK;
}

FUNC(StatusType,MEM_SetRelAlarm) SetRelAlarm ( AlarmType AlarmId, TickType Increment, TickType Cycle )
{
	StatusType ercd = E_OK;

	if(AlarmId < ALARM_NUM)
	{
		if(NULL == osTmr[AlarmId])
		{
			osTmr[AlarmId] = OSTmrCreate(Increment,Cycle,(0==Cycle)?OS_TMR_OPT_ONE_SHOT:OS_TMR_OPT_PERIODIC, \
										 uCOS_AlarmProcess,(void*)AlarmId,NULL,&ercd);
			if(OS_ERR_NONE == ercd)
			{
				OSTmrStart(osTmr[AlarmId],&ercd);
				if(OS_ERR_NONE != ercd)
				{
					OSTmrDel(osTmr[AlarmId],&ercd);
					osTmr[AlarmId] = NULL;
				}
			}

			if(OS_ERR_NONE != ercd)
			{
				ercd = E_OS_ACCESS;
				asAssert(0);
			}
		}
		else
		{
			ercd = E_OS_STATE;
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
	return SetRelAlarm(AlarmId,Start,Cycle);
}

FUNC(StatusType,MEM_CancelAlarm) CancelAlarm ( AlarmType AlarmId )
{
	StatusType ercd = E_OK;
	if(AlarmId < ALARM_NUM)
	{
		if(NULL != osTmr[AlarmId])
		{
			OSTmrStop(osTmr[AlarmId],OS_TMR_OPT_NONE,NULL,&ercd);
			if(OS_ERR_NONE == ercd)
			{
				OSTmrDel(osTmr[AlarmId],&ercd);
				osTmr[AlarmId] = NULL;
			}
			
			if(OS_ERR_NONE != ercd)
			{
				ercd = E_OS_ACCESS;
				asAssert(0);
			}
		}
		else
		{
			ercd = E_OS_STATE;
		}
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

	OSTimeDly(1);
	
	return ercd;
}

FUNC(void,MEM_StartOS)              StartOS       ( AppModeType Mode )
{
	uint32 i;
	uint8  ercd;
	const task_declare_t* td;

	OSInit();

	for(i=0;i<TASK_NUM;i++)
	{
		td = &TaskList[i];
		ercd = OSTaskCreate(uCOS_TaskProcess, (void *)i, (OS_STK*)&td->pstk[td->stk_size-1], i+1);
		asAssert(OS_ERR_NONE == ercd);
		taskEvent[i] = OSFlagCreate(0,&ercd);
		asAssert(OS_ERR_NONE == ercd);

		if(td->app_mode&Mode)
		{
			ActivateTask(i);
		}
	}

	StartupHook();

	OSStart();
}

FUNC(void,MEM_ShutdownOS)  ShutdownOS ( StatusType ercd )
{
	(void)ercd;
	while(1);
}


imask_t __Irq_Save(void)
{
	isrDisableCounter ++ ;
	if(1u == isrDisableCounter)
	{
		OS_ENTER_CRITICAL();
	}
	return 0;
}

void Irq_Restore(imask_t irq_state)
{

	isrDisableCounter --;
	if(0u == isrDisableCounter)
	{
		OS_EXIT_CRITICAL();
	}

	(void)irq_state;
}
