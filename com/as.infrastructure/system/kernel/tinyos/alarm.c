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
#include "Os.h"
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
TickType				OsTickCounter = 1;	/* zero mask as not started */

STATIC TickType			 	AlarmTick[ALARM_NUM];
STATIC TickType			 	AlarmPeriod[ALARM_NUM];
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
FUNC(void,MEM_OsTick) OsTick ( void )
{
	AlarmType AlarmId;
	OsTickCounter ++;

	if(0 == OsTickCounter)
	{
		OsTickCounter = 1;
	}

	for(AlarmId=0; AlarmId<ALARM_NUM; AlarmId++)
	{
		if(AlarmTick[AlarmId] > 0)
		{
			AlarmTick[AlarmId]--;
			if(0u == AlarmTick[AlarmId])
			{
				AlarmList[AlarmId].main();
				AlarmTick[AlarmId] = AlarmPeriod[AlarmId];
			}
		}
	}
}

FUNC(StatusType,MEM_GetAlarmBase) GetAlarmBase ( AlarmType AlarmId, AlarmBaseRefType Info )
{
	asAssert(AlarmId<ALARM_NUM);

    Info[0].maxallowedvalue = TICK_MAX;
    Info[0].ticksperbase     = 1u;
    Info[0].mincycle        = 1u;

	return E_OK;
}

FUNC(StatusType,MEM_GetAlarm) GetAlarm(AlarmType AlarmId, TickRefType Tick)
{
	asAssert(AlarmId<ALARM_NUM);

	Tick[0] = AlarmTick[AlarmId];

	return E_OK;
}

FUNC(StatusType,MEM_SetRelAlarm) SetRelAlarm ( AlarmType AlarmId, TickType Increment, TickType Cycle )
{
	asAssert(AlarmId<ALARM_NUM);

	AlarmTick[AlarmId] = Increment;
	AlarmPeriod[AlarmId] = Cycle;

	return E_OK;
}

FUNC(StatusType,MEM_SetAbsAlarm) SetAbsAlarm ( AlarmType AlarmId, TickType Start, TickType Cycle )
{
	asAssert(AlarmId<ALARM_NUM);

	if (OsTickCounter < Start)
	{
		Start = Start - OsTickCounter;
	}
	else
	{
		Start = TICK_MAX - OsTickCounter + Start + 1;
	}

	AlarmTick[AlarmId] = Start;
	AlarmPeriod[AlarmId] = Cycle;

	return E_OK;
}

FUNC(StatusType,MEM_CancelAlarm) CancelAlarm ( AlarmType AlarmId )
{
	asAssert(AlarmId<ALARM_NUM);

	AlarmTick[AlarmId] = 0;
	AlarmPeriod[AlarmId] = 0;

	return E_OK;
}

FUNC(void,MEM_OsAlarmInit) OsAlarmInit ( void )
{
    memset(AlarmTick,0,sizeof(AlarmTick));
    memset(AlarmPeriod,0,sizeof(AlarmPeriod));
}

