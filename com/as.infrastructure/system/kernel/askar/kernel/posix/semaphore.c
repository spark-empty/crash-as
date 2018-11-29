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
#include "semaphore.h"
#include <stdlib.h>
#include <stdarg.h>
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* this type is for named semaphore */
struct semaphore
{
	sem_t sem;
	unsigned int refcount;
	unsigned int unlinked;
	char* name;
	TAILQ_ENTRY(semaphore) entry;
};
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
static TAILQ_HEAD(semaphore_list, semaphore) OsSemaphoreList = TAILQ_HEAD_INITIALIZER(OsSemaphoreList);
/* ============================ [ LOCALS    ] ====================================================== */
static struct semaphore * sem_find(const char *name)
{
	struct semaphore *sem = NULL;

	TAILQ_FOREACH(sem, &OsSemaphoreList, entry)
	{
		if(0u == strcmp(sem->name, name))
		{
			break;
		}
	}

	return sem;
}

static struct semaphore * sem_find2(struct semaphore *sem2)
{
	struct semaphore *sem = NULL;

	TAILQ_FOREACH(sem, &OsSemaphoreList, entry)
	{
		if(sem == sem2)
		{
			break;
		}
	}

	return sem;
}
/* ============================ [ FUNCTIONS ] ====================================================== */
int sem_init(sem_t *sem, int pshared, unsigned int value)
{
	(void)pshared;

	TAILQ_INIT(&(sem->head));

	sem->value = value;

	return 0;
}
ELF_EXPORT(sem_init);

int sem_getvalue(sem_t *sem, int *sval)
{
	imask_t imask;

	Irq_Save(imask);
	*sval  = sem->value;
	Irq_Restore(imask);

	return 0;
}
ELF_EXPORT(sem_getvalue);

int sem_destroy(sem_t *sem)
{
	(void)sem;

	return 0;
}
ELF_EXPORT(sem_destroy);

int sem_timedwait(sem_t *sem, const struct timespec *abstime)
{
	int ercd = 0;
	imask_t imask;

	Irq_Save(imask);

	if(sem->value > 0)
	{
		sem->value --;
	}
	else
	{
		ercd = Os_ListWait(&(sem->head), abstime);
	}

	Irq_Restore(imask);

	return ercd;
}
ELF_EXPORT(sem_timedwait);

int sem_trywait(sem_t *sem)
{
	struct timespec tm = { 0, 0 };
	return sem_timedwait(sem, &tm);
}
ELF_EXPORT(sem_trywait);

int sem_wait(sem_t *sem)
{
	return sem_timedwait(sem, NULL);
}
ELF_EXPORT(sem_wait);

int sem_post(sem_t *sem)
{
	int ercd = 0;
	imask_t imask;

	Irq_Save(imask);

	if(0 != Os_ListPost(&(sem->head), TRUE))
	{
		sem->value ++;
	}

	Irq_Restore(imask);

	return ercd;
}
ELF_EXPORT(sem_post);

sem_t *sem_open(const char *name, int oflag, ...)
{
	imask_t imask;
	struct semaphore *sem = NULL;
	va_list arg;
	mode_t mode;
	unsigned int value;

	asAssert(name != NULL);

	Irq_Save(imask);
	sem = sem_find(name);
	Irq_Restore(imask);

	if( (NULL == sem) && (0 != (oflag & O_CREAT)))
	{
		va_start(arg, oflag);
		mode = (mode_t)va_arg(arg, mode_t);
		mode = mode;
		value = (unsigned int)va_arg(arg, unsigned int);
		va_end(arg);

		sem = malloc(sizeof(struct semaphore) + strlen(name)+1);
		sem->name = (char*)&sem[1];
		strcpy(sem->name, name);
		sem->refcount = 0;
		sem->unlinked = 0;
		Irq_Save(imask);
		/* no consideration of the sem_create race condition,
		 * so just assert if such condition */
		asAssert(NULL == sem_find(name));
		TAILQ_INSERT_TAIL(&OsSemaphoreList, sem, entry);
		Irq_Restore(imask);
	}

	if(NULL != sem)
	{
		Irq_Save(imask);
		sem->refcount++;
		Irq_Restore(imask);
	}

	return &(sem->sem);
}
ELF_EXPORT(sem_open);

int     sem_close(sem_t* sem2)
{
	int ercd = 0;
	imask_t imask;
	struct semaphore *sem;

	Irq_Save(imask);
	sem = sem_find2((struct semaphore *)sem2);
	if((NULL != sem) && (sem->refcount > 0))
	{
		sem->refcount --;
		if((0 == sem->refcount) &&  (sem->unlinked))
		{
			TAILQ_REMOVE(&OsSemaphoreList, sem, entry);
			free(sem);
		}
	}
	else
	{
		ercd = -EACCES;
	}
	Irq_Restore(imask);

	return ercd;
}
ELF_EXPORT(sem_close);

int     sem_unlink(const char *name)
{
	int ercd = 0;
	imask_t imask;
	struct semaphore *sem;

	Irq_Save(imask);
	sem = sem_find(name);
	if(NULL != sem)
	{
		sem->unlinked = 1;
		if(0 == sem->refcount)
		{
			TAILQ_REMOVE(&OsSemaphoreList, sem, entry);
			free(sem);
		}
	}
	Irq_Restore(imask);

	return ercd;

}
ELF_EXPORT(sem_unlink);

#endif /* OS_PTHREAD_NUM > 0 */

