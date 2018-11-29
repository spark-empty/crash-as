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
#if(OS_PTHREAD_NUM > 0)
#include "pthread.h"
#include <errno.h>
#include <stdlib.h>
#include <asdebug.h>
#ifdef USE_PTHREAD_SIGNAL
#include "signal.h"
#endif
/* ============================ [ MACROS    ] ====================================================== */
#define AS_LOG_PTHREAD 0
/* ============================ [ TYPES     ] ====================================================== */
struct cleanup
{
	TAILQ_ENTRY(cleanup) entry;
	void (*routine)(void*);
	void* arg;
};
/* ============================ [ DECLARES  ] ====================================================== */
extern const pthread_attr_t pthread_default_attr;
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
static TaskVarType* pthread_malloc_tcb(void)
{
	TaskType id;

	TaskVarType* pTaskVar = NULL;

	for(id=0; id < OS_PTHREAD_NUM; id++)
	{
		if(NULL == TaskVarArray[TASK_NUM+id].pConst)
		{
			pTaskVar = &TaskVarArray[TASK_NUM+id];
			pTaskVar->pConst = (void*)1; /* reservet it */
			break;
		}
	}

	return pTaskVar;
}
static void pthread_entry_main(void)
{
	void* r;
	pthread_t pthread;

	pthread = (pthread_t)RunningVar->pConst;

	asAssert(pthread->pTaskVar == RunningVar);

	r = pthread->start(pthread->arg);

	pthread_exit(r);

}

static boolean pthread_CheckAccess(ResourceType ResID)
{
	(void) ResID;
	/* not allowd to access any OSEK resource */
	return FALSE;
}
#ifdef USE_PTHREAD_PARENT
static TaskVarType* pthread_get_parent(TaskVarType *pTaskVar)
{
	TaskVarType* pParent;
	pthread_t tid;
	if(pTaskVar-TaskVarArray < TASK_NUM)
	{
		pParent = pTaskVar;
	}
	else
	{
		tid = (pthread_t)(pTaskVar->pConst);
		if(NULL != tid->parent)
		{
			pParent = pthread_get_parent(tid->parent);
		}
		else
		{
			pParent = pTaskVar;
		}
	}

	return pParent;
}
#endif
/* ============================ [ FUNCTIONS ] ====================================================== */
int pthread_create (pthread_t *tid, const pthread_attr_t *attr,
    void *(*start) (void *), void *arg)
{
	int ercd = 0;
	imask_t imask;
	TaskVarType* pTaskVar;
	TaskConstType* pTaskConst;
	pthread_t pthread;

	Irq_Save(imask);

	pTaskVar = pthread_malloc_tcb();

	Irq_Restore(imask);

	if(NULL != pTaskVar)
	{
		memset(pTaskVar, 0, sizeof(TaskVarType));
		if((NULL != attr) && (NULL != attr->stack_base))
		{	/* to create it totally static by using stack to allocate pthread */
			pthread = (pthread_t)attr->stack_base;
			pthread->pTaskVar = pTaskVar;
			pTaskConst = &(pthread->TaskConst);

			pTaskConst->pStack = attr->stack_base+sizeof(struct pthread);
			pTaskConst->stackSize = attr->stack_size - sizeof(struct pthread);
			pTaskConst->initPriority = attr->priority;
			pTaskConst->runPriority = attr->priority;
			pTaskConst->flag = 0;
			asAssert(attr->priority < OS_PTHREAD_PRIORITY);
		}
		else
		{
			if(NULL == attr)
			{
				attr = &pthread_default_attr;
			}
			pthread = malloc(attr->stack_size+sizeof(struct pthread));
			if(NULL == pthread)
			{
				ercd = -ENOMEM;
			}
			else
			{
				pthread->pTaskVar = pTaskVar;
				pTaskConst = &(pthread->TaskConst);
				pTaskConst->pStack = ((void*)pthread)+sizeof(struct pthread);
				pTaskConst->stackSize = attr->stack_size;
				pTaskConst->initPriority = attr->priority;
				pTaskConst->runPriority = attr->priority;
				pTaskConst->flag = PTHREAD_DYNAMIC_CREATED_MASK;
			}
		}
	}
	else
	{
		ercd = -ENOMEM;
	}

	if(NULL != tid)
	{
		*tid = pthread;
	}

	if(0 == ercd)
	{
#ifdef USE_PTHREAD_PARENT
		pthread->parent = pthread_get_parent(RunningVar);
#endif
		pthread->arg = arg;
		pthread->start = start;
		pTaskConst->entry = pthread_entry_main;
		pTaskConst->CheckAccess = pthread_CheckAccess;
		pTaskConst->name = "pthread";
		#ifdef MULTIPLY_TASK_ACTIVATION
		pTaskConst->maxActivation = 1;
		pTaskVar->activation = 1;
		#endif
		pTaskVar->state = READY;
		memset(pTaskConst->pStack, 0, pTaskConst->stackSize);
		pTaskVar->currentResource = INVALID_RESOURCE;
		pTaskVar->pConst = pTaskConst;
		pTaskVar->priority = pTaskConst->initPriority;
		Os_PortInitContext(pTaskVar);

		ASLOG(PTHREAD, "pthread%d created\n", (pTaskVar-TaskVarArray-TASK_NUM));
		TAILQ_INIT(&pthread->joinList);
#ifdef USE_PTHREAD_CLEANUP
		TAILQ_INIT(&pthread->cleanupList);
#endif
#ifdef USE_PTHREAD_SIGNAL
		TAILQ_INIT(&pthread->signalList);
		TAILQ_INIT(&pthread->sigList);
		sigemptyset(&pthread->sigWait);
#endif

		Irq_Save(imask);
		if((NULL == attr) || (PTHREAD_CREATE_JOINABLE == attr->detachstate))
		{
			pTaskConst->flag |= PTHREAD_JOINABLE_MASK;
		}
		Sched_AddReady(pTaskVar - TaskVarArray);
		Irq_Restore(imask);
	}

	return ercd;
}
ELF_EXPORT(pthread_create);

#ifdef USE_PTHREAD_CLEANUP
void pthread_cleanup_push(void (*routine)(void*), void *arg)
{
	struct cleanup* cleanup;
	pthread_t tid;
	imask_t imask;

	tid = pthread_self();

	cleanup = malloc(sizeof(struct cleanup));
	if(NULL != cleanup)
	{
		cleanup->routine = routine;
		cleanup->arg = arg;
		Irq_Save(imask);
		TAILQ_INSERT_HEAD(&tid->cleanupList, cleanup, entry);
		Irq_Restore(imask);
	}
	else
	{
		asAssert(0);
	}
}
ELF_EXPORT(pthread_cleanup_push);

void pthread_cleanup_pop(int execute)
{
	struct cleanup* cleanup;
	pthread_t tid;
	imask_t imask;
	struct cleanup cls;

	tid = pthread_self();

	Irq_Save(imask);

	cleanup = TAILQ_FIRST(&tid->cleanupList);

	if(NULL != cleanup)
	{
		TAILQ_REMOVE(&tid->cleanupList, cleanup, entry);
		if(execute)
		{
			asAssert(cleanup->routine);
			cls = *cleanup;
			free(cleanup); /* free immediately in case that the routine call 'exit' */
			cls.routine(cls.arg);
		}
	}

	Irq_Restore(imask);
}
ELF_EXPORT(pthread_cleanup_pop);
#endif
void pthread_exit (void *value_ptr)
{
	pthread_t tid;

	tid = pthread_self();

	Irq_Disable();

	ASLOG(PTHREAD, "pthread%d exit\n", (RunningVar-TaskVarArray-TASK_NUM));

#ifdef USE_PTHREAD_CLEANUP
	while(FALSE == TAILQ_EMPTY(&tid->cleanupList))
	{
		pthread_cleanup_pop(1);
	}
#endif

#ifdef USE_PTHREAD_SIGNAL
	/* free signal handler */
	Os_FreeSignalHandler(tid);
	Sched_RemoveReady(RunningVar-TaskVarArray);
#endif

	Os_ListDetach(tid->pTaskVar, FALSE);

	if(tid->TaskConst.flag & PTHREAD_JOINABLE_MASK)
	{
		ASLOG(PTHREAD, "pthread%d signal jion\n", (RunningVar-TaskVarArray-TASK_NUM));
		tid->TaskConst.flag |= PTHREAD_JOINED_MASK;
		tid->ret = value_ptr;
		if(0 == Os_ListPost(&tid->joinList, FALSE))
		{
			asAssert(TAILQ_EMPTY(&tid->joinList));
		}
	}
	else
	{
		tid->pTaskVar->pConst = NULL;
		if(tid->TaskConst.flag & PTHREAD_DYNAMIC_CREATED_MASK)
		{
			free(tid);
		}
	}

	Sched_GetReady();
	Os_PortDispatch();

	while(1) asAssert(0);
}
ELF_EXPORT(pthread_exit);

#ifdef USE_PTHREAD_SIGNAL
void exit (int code)
{
	pthread_t tid;
#ifdef USE_PTHREAD_PARENT
	TaskType id;
	TaskVarType *pParent;
	TaskVarType *pTaskVar;
	const TaskConstType *pTaskConst;
#endif

	tid = pthread_self();
	Irq_Disable();

	Os_ListDetach(tid->pTaskVar, FALSE);

#ifdef USE_PTHREAD_PARENT
	pParent = tid->parent;
	for(id=0; id < OS_PTHREAD_NUM; id++)
	{
		pTaskVar   = &TaskVarArray[TASK_NUM+id];
		pTaskConst = pTaskVar->pConst;
		if( (((pthread_t)pTaskConst) != tid) &&
			(pTaskConst > (TaskConstType *)1) &&
			(pParent == (((pthread_t)pTaskConst)->parent)) )
		{	/* force exit of its children */
			(void)pthread_detach((pthread_t)pTaskConst);
			if(0 == pthread_cancel((pthread_t)pTaskConst))
			{	/* sleep 1 tick to make sure that child exit fully */
				Os_Sleep(1);
			}
		}
	}
#endif
	pthread_exit((void*)code);

	while(1) asAssert(0);
}
ELF_EXPORT(exit);
#endif

int pthread_detach(pthread_t tid)
{
	int ercd = 0;
	imask_t imask;

	asAssert(tid);
	asAssert((tid->pTaskVar-TaskVarArray) >= TASK_NUM);
	asAssert((tid->pTaskVar-TaskVarArray) < (TASK_NUM+OS_PTHREAD_NUM));

	Irq_Save(imask);
	if(tid->TaskConst.flag & PTHREAD_JOINED_MASK)
	{	/* the tid is already exited */
		tid->pTaskVar->pConst = NULL;
		if(tid->TaskConst.flag & PTHREAD_DYNAMIC_CREATED_MASK)
		{
			free(tid);
		}
	}
	else
	{
		tid->TaskConst.flag &= ~PTHREAD_JOINABLE_MASK;
	}
	Irq_Restore(imask);

	return ercd;
}
ELF_EXPORT(pthread_detach);

int pthread_join(pthread_t tid, void ** thread_return)
{
	int ercd = 0;
	imask_t imask;

	asAssert(tid);
	asAssert((tid->pTaskVar-TaskVarArray) >= TASK_NUM);
	asAssert((tid->pTaskVar-TaskVarArray) < (TASK_NUM+OS_PTHREAD_NUM));

	Irq_Save(imask);
	if(tid->TaskConst.flag & PTHREAD_JOINABLE_MASK)
	{
		if(0u == (tid->TaskConst.flag & PTHREAD_JOINED_MASK))
		{
			(void)Os_ListWait(&tid->joinList, NULL);
		}
		asAssert(tid->TaskConst.flag & PTHREAD_JOINED_MASK);
		tid->pTaskVar->pConst = NULL;
		if(NULL != thread_return)
		{
			*thread_return = tid->ret;
		}

		ASLOG(PTHREAD, "pthread%d join %d\n",
				(RunningVar-TaskVarArray-TASK_NUM),
				(tid->pTaskVar-TaskVarArray-TASK_NUM));
		if(tid->TaskConst.flag & PTHREAD_DYNAMIC_CREATED_MASK)
		{
			free(tid);
		}
	}
	else
	{
		ercd = -EACCES;
	}
	Irq_Restore(imask);

	return ercd;
}
ELF_EXPORT(pthread_join);

pthread_t pthread_self(void)
{
	pthread_t tid;

	asAssert((RunningVar-TaskVarArray) >= TASK_NUM);
	asAssert((RunningVar-TaskVarArray) < (TASK_NUM+OS_PTHREAD_NUM));

	tid = (pthread_t)(RunningVar->pConst);

	return tid;
}
ELF_EXPORT(pthread_self);

#ifdef USE_PTHREAD_SIGNAL
int pthread_cancel (pthread_t tid)
{
	int ercd = 0;
	imask_t imask;

	asAssert(tid);
	asAssert((tid->pTaskVar-TaskVarArray) >= TASK_NUM);
	asAssert((tid->pTaskVar-TaskVarArray) < (TASK_NUM+OS_PTHREAD_NUM));

	ASLOG(PTHREAD, "pthread%d cancel\n", (tid->pTaskVar-TaskVarArray-TASK_NUM));
	if(tid == pthread_self())
	{
		ercd = -EINVAL;
	}
	else
	{
		Irq_Save(imask);

		if(tid->pTaskVar->pConst > (TaskConstType*)1)
		{
			if(READY != tid->pTaskVar->state)
			{
				Os_ListDetach(tid->pTaskVar, TRUE);
			}

			ercd = pthread_kill(tid, SIGKILL);
		}
		else
		{
			/* the tid is already dead */
		}

		Irq_Restore(imask);
	}

	return ercd;
}
ELF_EXPORT(pthread_cancel);
#endif

void pthread_testcancel(void)
{

}
ELF_EXPORT(pthread_testcancel);

int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)
{
	(void)attr;

	TAILQ_INIT(&(mutex->head));

	mutex->locked = FALSE;

	return 0;
}
ELF_EXPORT(pthread_mutex_init);

int pthread_mutex_destroy(pthread_mutex_t *mutex)
{
	(void)mutex;
	return 0;
}
ELF_EXPORT(pthread_mutex_destroy);

int pthread_mutex_lock(pthread_mutex_t *mutex)
{
	int ercd = 0;
	imask_t imask;

	Irq_Save(imask);

	if(TRUE == mutex->locked)
	{
		/* wait it forever */
		Os_ListWait(&mutex->head, NULL);
	}

	mutex->locked = TRUE;


	Irq_Restore(imask);

	return ercd;
}
ELF_EXPORT(pthread_mutex_lock);

int pthread_mutex_unlock(pthread_mutex_t *mutex)
{
	int ercd = 0;
	imask_t imask;

	Irq_Save(imask);

	if(TRUE == mutex->locked)
	{
		if(0 != Os_ListPost(&mutex->head, TRUE))
		{
			mutex->locked = FALSE;
		}
	}
	else
	{
		ercd = -EACCES;
	}

	Irq_Restore(imask);

	return ercd;
}
ELF_EXPORT(pthread_mutex_unlock);

int pthread_mutex_trylock(pthread_mutex_t *mutex)
{
	int ercd = 0;
	imask_t imask;

	Irq_Save(imask);

	if(TRUE == mutex->locked)
	{
		ercd = -EBUSY;
	}
	else
	{
		mutex->locked = TRUE;
	}

	Irq_Restore(imask);

	return ercd;
}
ELF_EXPORT(pthread_mutex_trylock);


int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr)
{
	(void)attr;

	TAILQ_INIT(&(cond->head));

	cond->signals = 0;

	return 0;
}
ELF_EXPORT(pthread_cond_init);

int pthread_cond_destroy(pthread_cond_t *cond)
{
	(void)cond;
	return 0;
}
ELF_EXPORT(pthread_cond_destroy);

int pthread_cond_broadcast(pthread_cond_t *cond)
{
	imask_t imask;

	Irq_Save(imask);

	while(0 == Os_ListPost(&(cond->head), FALSE))
		;

	(void) Schedule();

	Irq_Restore(imask);

	return 0;
}
ELF_EXPORT(pthread_cond_broadcast);

int pthread_cond_signal(pthread_cond_t *cond)
{
	int ercd = 0;
	imask_t imask;

	Irq_Save(imask);

	if(0 != Os_ListPost(&cond->head, TRUE))
	{
		cond->signals ++;
	}

	Irq_Restore(imask);

	return ercd;
}
ELF_EXPORT(pthread_cond_signal);

int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
	return pthread_cond_timedwait(cond, mutex, NULL);

}
ELF_EXPORT(pthread_cond_wait);

int pthread_cond_timedwait(pthread_cond_t        *cond,
                           pthread_mutex_t       *mutex,
                           const struct timespec *abstime)
{
	int ercd = 0;
	imask_t imask;
	TickType ticks;

	asAssert(mutex->locked);

	Irq_Save(imask);

	if(0 == cond->signals)
	{
		ercd = pthread_mutex_unlock(mutex);

		if(0 == ercd)
		{
			ercd = Os_ListWait(&(cond->head), abstime);

			(void)pthread_mutex_lock(mutex);
		}
	}
	else
	{
		cond->signals --;
	}

	Irq_Restore(imask);

	return ercd;
}
ELF_EXPORT(pthread_cond_timedwait);

int pthread_once (pthread_once_t *once, void (*init_routine)(void))
{
	asAssert((NULL != once) && (NULL != init_routine));

	if(PTHREAD_ONCE_INIT == *once)
	{
		*once =  ~PTHREAD_ONCE_INIT;
		init_routine();
	}

	return 0;
}
ELF_EXPORT(pthread_once);

void sched_yield(void)
{
	ASLOG(PTHREAD, "pthread%d yield\n", (RunningVar-TaskVarArray-TASK_NUM));
	Schedule();
}
ELF_EXPORT(sched_yield);

pid_t getpid(void)
{
	return (RunningVar-TaskVarArray);
}
ELF_EXPORT(getpid);
#endif
