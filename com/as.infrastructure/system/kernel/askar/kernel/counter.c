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
#include "kernel_internal.h"
#if (COUNTER_NUM > 0)
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
StatusType SignalCounter(CounterType CounterID)
{
	StatusType ercd = E_OK;
	imask_t imask;
	AlarmVarType *pVar;
	AlarmType AlarmID;
	unsigned int savedLevel;
	TickType curValue;

	if(CounterID < COUNTER_NUM)
	{
		Irq_Save(imask);
		savedLevel = CallLevel;
		CallLevel = TCL_LOCK;
		/* yes, only software counter supported */
		CounterVarArray[CounterID].value++;
		curValue = CounterVarArray[CounterID].value;
		#if (ALARM_NUM > 0)
		while(NULL != (pVar = TAILQ_FIRST(&CounterVarArray[CounterID].head))) /* intended '=' */
		{
			if (pVar->value == curValue)
			{
				AlarmID = pVar - AlarmVarArray;
				TAILQ_REMOVE(&CounterVarArray[CounterID].head, &AlarmVarArray[AlarmID], entry);
				OS_STOP_ALARM(&AlarmVarArray[AlarmID]);
				if(AlarmVarArray[AlarmID].period != 0)
				{
					Os_StartAlarm(AlarmID,
						(TickType)(curValue+AlarmVarArray[AlarmID].period),
						AlarmVarArray[AlarmID].period);
				}

				Irq_Restore(imask);
				AlarmConstArray[AlarmID].Action();
				Irq_Save(imask);

			}
			else
			{
				break;
			}
		}
		#endif
		CallLevel = savedLevel;
		Irq_Restore(imask);
	}
	else
	{
		ercd = E_OS_ID;
	}
	
	return ercd;
}

void Os_CounterInit(void)
{
	CounterType id;

	for(id=0; id < COUNTER_NUM; id++)
	{
		CounterVarArray[id].value = 0;
		TAILQ_INIT(&CounterVarArray[id].head);
	}
}
#ifdef USE_SHELL
void statOsCounter(void)
{
	CounterType id;
	AlarmVarType *pVar;
	imask_t mask;

	Irq_Save(mask);

	SHELL_printf("\nName\n");
	for(id=0; id < COUNTER_NUM; id++)
	{
		SHELL_printf("%-16s ", CounterConstArray[id].name);
		TAILQ_FOREACH(pVar, &(CounterVarArray[id].head), entry)
		{
			SHELL_printf("%s(%d) -> ",
					AlarmConstArray[pVar-AlarmVarArray].name,
					pVar->value);
		}
	}

	Irq_Restore(mask);
}
#endif
#else
#ifdef USE_SHELL
void statOsCounter(void)
{
	printf("Counter is not configured!\n");
}
#endif
#endif /* #if (COUNTER_NUM > 0) */
