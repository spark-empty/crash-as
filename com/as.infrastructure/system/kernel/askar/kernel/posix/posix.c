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
#include "kernel_internal.h"
#if(OS_PTHREAD_NUM > 0)
#include "pthread.h"
#include <errno.h>
#include <stdlib.h>
#include <asdebug.h>
#ifdef USE_PTHREAD_SIGNAL
#include "signal.h"
#endif
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
TASK(TaskPosix)
{
	EventMaskType event;
	StatusType ercd;

	while(1)
	{
		/* -1: waiting all event */
		ercd = WaitEvent((EventMaskType)-1);
		if(E_OK == ercd)
		{
			(void)GetEvent(TASK_ID_TaskPosix, &event);
			(void)ClearEvent(event);

			#ifdef USE_PTHREAD_SIGNAL
			if(EVENT_MASK_TaskPosix_EVENT_SIGALRM&event)
			{
				Os_SignalBroadCast(SIGALRM);
			}
			#endif
		}
	}
	OsTerminateTask(TaskPosix);
}
#endif /* OS_PTHREAD_NUM */
