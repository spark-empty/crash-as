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

/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
STATIC EventMaskType EventBit[TASK_NUM];
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifdef __WINDOWS__
StatusType SetEvent2 ( TaskType tskid , EventMaskType mask )
#else
StatusType SetEvent ( TaskType tskid , EventMaskType mask )
#endif
{
	StatusType ercd = E_OK;

	if (tskid < TASK_NUM)
	{
		EventBit[tskid] |= mask;
	}
	else
	{
		ercd = E_OS_ID;
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
		EventBit[tskid] &= ~mask;
	}
	else
	{
		ercd = E_OS_ID;
	}

	return ercd;
}

StatusType GetEvent ( TaskType tskid , EventMaskRefType p_mask )
{
	StatusType ercd = E_OK;

	if (tskid < TASK_NUM)
	{
		*p_mask = EventBit[tskid];
	}
	else
	{
		ercd = E_OS_ID;
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
		if(0 == (EventBit[tskid]&mask))
		{
			ercd = E_OS_ACCESS;
		}
	}
	else
	{
		ercd = E_OS_ID;
	}
	return ercd;
}
