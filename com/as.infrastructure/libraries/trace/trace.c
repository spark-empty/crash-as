/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2018  AS <parai@foxmail.com>
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
#include "trace.h"
#include <string.h>
#include "asdebug.h"
#ifdef USE_SHELL
#include "Os.h"
#include "shell.h"
#endif
/* ============================ [ MACROS    ] ====================================================== */
#ifndef TRACE_PERF_RECORD_NUM
#define TRACE_PERF_RECORD_NUM 32
#endif

/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
#ifdef USE_SHELL
static int shellTrace(int argc, char *argv[]);
#endif
/* ============================ [ DATAS     ] ====================================================== */
static Trace_PerfRecordType tracePerfRecord[TRACE_PERF_RECORD_NUM];
#ifdef USE_SHELL
static SHELL_CONST ShellCmdT cmdTrace  = {
		shellTrace,
		0,1,
		"trace",
		"trace",
		"show trace information and reset\n",
		{NULL,NULL}
};
SHELL_CMD_EXPORT(cmdTrace)
#endif
/* ============================ [ LOCALS    ] ====================================================== */
#ifdef USE_SHELL
static int shellTrace(int argc, char *argv[])
{
	int i;
	imask_t imask;

	Irq_Save(imask);

	#ifdef TASK_ID_TaskShell
	Trace_PerfStop(TASK_ID_TaskShell);
	#endif

	SHELL_printf(" ID      sumH     sumL      max      min    times (FREQ=%d)\n",TRACE_TIMER_FREQ);
	for(i=0; i<TRACE_PERF_RECORD_NUM; i++)
	{
		if(tracePerfRecord[i].times > 0)
		{
			SHELL_printf("%3d %8X %8X %8X %8X %8X\n", i,
					tracePerfRecord[i].sumH, tracePerfRecord[i].sumL,
					tracePerfRecord[i].max, tracePerfRecord[i].min,
					tracePerfRecord[i].times);
		}
	}

	Trace_PerfReset();

	#ifdef TASK_ID_TaskShell
	Trace_PerfStart(TASK_ID_TaskShell);
	#endif

	Irq_Restore(imask);

	return 0;
}
#endif
/* ============================ [ FUNCTIONS ] ====================================================== */
void Trace_Init(void)
{
	TRACE_TIMER_INIT;
	memset(tracePerfRecord, 0, sizeof(tracePerfRecord));
#if !defined(USE_SHELL_SYMTAB) && defined(USE_SHELL)
	SHELL_AddCmd(&cmdTrace);
#endif
}

void Trace_PerfStart(uint32_t Id)
{
	asAssert(Id < TRACE_PERF_RECORD_NUM);
	tracePerfRecord[Id].tmp = TRACE_TIMER_VALUE;
}

void Trace_PerfStop(uint32_t Id)
{
	uint32_t tmp,pre;
	asAssert(Id < TRACE_PERF_RECORD_NUM);
	tmp = TRACE_TIMER_VALUE;
	pre = tracePerfRecord[Id].tmp;

#if(TRACE_TIMER_TYPE == TRACE_TIMER_TYPE_UP)
	if(tmp > pre)
	{
		tmp = tmp - pre;
	}
	else
	{
		tmp = TRACE_TIMER_MAX - pre + 1 + tmp;
	}
#else
	if(pre > tmp)
	{
		tmp = pre - tmp;
	}
	else
	{
		tmp = TRACE_TIMER_MAX - tmp + 1 + pre;
	}
#endif

	tracePerfRecord[Id].times ++;
	if(tracePerfRecord[Id].sumL > (0xFFFFFFFFUL - tmp))
	{
		tracePerfRecord[Id].sumH += 1;
		tracePerfRecord[Id].sumL = tmp - (0xFFFFFFFFUL - tracePerfRecord[Id].sumL + 1);
	}
	else
	{
		tracePerfRecord[Id].sumL += tmp;
	}

	if(tmp > tracePerfRecord[Id].max)
	{
		tracePerfRecord[Id].max = tmp;
	}
	else if((tmp < tracePerfRecord[Id].min)
			|| (0u == tracePerfRecord[Id].min))
	{
		tracePerfRecord[Id].min= tmp;
	}
	else
	{
		/* do nothing */
	}
}

void Trace_PerfReset(void)
{
	memset(tracePerfRecord, 0, sizeof(tracePerfRecord));
}
