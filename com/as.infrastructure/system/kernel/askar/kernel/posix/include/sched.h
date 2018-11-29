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
#ifndef _ASKAR_SCHED_H_
#define _ASKAR_SCHED_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include <sys/queue.h>
/* ============================ [ MACROS    ] ====================================================== */
/* Scheduling algorithms.  */
#define SCHED_OTHER		0
#define SCHED_FIFO		1
#define SCHED_RR		2

#define PTHREAD_EXPLICIT_SCHED      0
#define PTHREAD_INHERIT_SCHED       1
/* ============================ [ TYPES     ] ====================================================== */
struct sched_param
{
	int sched_priority;
};

struct TaskVar;
typedef TAILQ_HEAD(TaskList, TaskVar) TaskListType;

typedef unsigned long sigset_t;

/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void sched_yield(void);
#endif /* _ASKAR_SCHED_H_ */
