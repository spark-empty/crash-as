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
 *
 * osal: Operating System Abstraction Layer
 */
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Os.h"
#include "contiki.h"
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
#ifndef CONTIKI_OS_STACK_SIZE
#define CONTIKI_OS_STACK_SIZE (4096)
#endif
/* ============================ [ TYPES     ] ====================================================== */
typedef struct
{
	struct ctimer timer;
	TickType period;
} AlarmContrlBlockType;
/* ============================ [ DECLARES  ] ====================================================== */
#ifdef USE_CONTIKI
extern alarm_declare_t AlarmList[ALARM_NUM];
extern void loadsp( void* sp );
#endif
/* ============================ [ DATAS     ] ====================================================== */
PROCINIT(&etimer_process);

PROTO_AUTOSTART_PROCESS_END();

#ifdef USE_CONTIKI
static AlarmContrlBlockType alarmcb[ALARM_NUM];	/* alarm control block */
TickType OsTickCounter = 0;
static long osstack[CONTIKI_OS_STACK_SIZE];
TaskType tskact[TASK_NUM];
#endif
/* ============================ [ LOCALS    ] ====================================================== */
#ifdef USE_CONTIKI
static void AlarmProcess(void* param)
{
	AlarmType AlarmId = (AlarmType)(long)param;

	AlarmList[AlarmId].main();

	if(0 != alarmcb[AlarmId].period)
	{
		ctimer_set(&(alarmcb[AlarmId].timer),alarmcb[AlarmId].period,AlarmProcess,(void*)(long)AlarmId);
	}
}
#endif
/* ============================ [ FUNCTIONS ] ====================================================== */
void StartContiki(void)
{
	process_init();

	procinit_init();

	ctimer_init();
#ifdef USE_CONTIKI
	memset(taskEvcb, 0, sizeof(taskEvcb));
	memset(tskact, 0, sizeof(tskact));
	StartupHook();
#endif
	autostart_start(autostart_processes);

}

void ScheduleContiki(void)
{
	process_run();
}

#ifdef USE_CONTIKI
void OsTick ( void )
{
	OsTickCounter ++;

	if(0 == OsTickCounter)
	{
		OsTickCounter = 1;
	}
}

void ShutdownOS(StatusType ercd)
{

}

void PollTask(void)
{
	TaskType TaskId;
	for(TaskId = 0; TaskId < TASK_NUM; TaskId++)
	{
		if(tskact[TaskId] > 0)
		{
			tskact[TaskId] --;
			process_start(TaskList[TaskId], NULL);
		}
	}
}

void StartOS(AppModeType app_mode)
{
	loadsp(&osstack[CONTIKI_OS_STACK_SIZE-4]);
	StartContiki();

	while(1) {
		PollTask();
		ScheduleContiki();
		etimer_request_poll();
	}
}

StatusType Schedule(void)
{
	ScheduleContiki();

	etimer_request_poll();

	return E_OK;
}

StatusType SetRelAlarm ( AlarmType AlarmId, TickType Increment, TickType Cycle )
{
	asAssert(AlarmId<ALARM_NUM);

	alarmcb[AlarmId].period = Cycle;

	ctimer_set(&(alarmcb[AlarmId].timer),Increment,AlarmProcess,(void*)(long)AlarmId);

	return E_OK;
}

StatusType SetAbsAlarm ( AlarmType AlarmId, TickType Start, TickType Cycle )
{
	asAssert(AlarmId<ALARM_NUM);

	alarmcb[AlarmId].period = Cycle;

	ctimer_set(&(alarmcb[AlarmId].timer),Start-OsTickCounter,AlarmProcess,(void*)(long)AlarmId);

	return E_OK;
}

StatusType CancelAlarm ( AlarmType AlarmId )
{
	asAssert(AlarmId<ALARM_NUM);
	ctimer_stop(&(alarmcb[AlarmId].timer));
	return E_OK;
}

StatusType ActivateTask    ( TaskType TaskId)
{
	StatusType ercd = E_OK;

	if(TaskId < TASK_NUM)
	{
		tskact[TaskId] ++;
	}
	else
	{
		ercd = E_OS_ID;
	}
	return ercd;
}
#endif

