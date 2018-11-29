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
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
TaskVarType TaskVarArray[TASK_NUM+OS_PTHREAD_NUM];
#ifdef USE_SHELL
static const char* statsNames[] =
{
	"SUSPENDED",
	"RUNNING",
	"READY",
	"WAITING"
};
#endif
/* ============================ [ LOCALS    ] ====================================================== */
static void InitContext(TaskVarType* pTaskVar)
{
	pTaskVar->state = READY;
	pTaskVar->priority = pTaskVar->pConst->initPriority;
	pTaskVar->currentResource = INVALID_RESOURCE;

	#ifdef EXTENDED_TASK
	if(NULL != pTaskVar->pConst->pEventVar)
	{
		pTaskVar->pConst->pEventVar->set = 0u;
		pTaskVar->pConst->pEventVar->wait = 0u;
	}
	#endif

	Os_PortInitContext(pTaskVar);
}
#ifdef USE_SHELL
static const char* taskStateToString(TaskStateType state)
{
	const char* p = "unknown";
	if((state&OSEK_TASK_STATE_MASK) < sizeof(statsNames)/sizeof(char*))
	{
		p = statsNames[state&OSEK_TASK_STATE_MASK];
	}

	if( (state&(PTHREAD_STATE_SLEEPING|PTHREAD_STATE_WAITING))
			== (PTHREAD_STATE_SLEEPING|PTHREAD_STATE_WAITING) )
	{
		p = "TIMEDWAIT";
	}
	else if(state&PTHREAD_STATE_WAITING)
	{
		p = "WAITLIST";
	}
	else if(state&PTHREAD_STATE_SLEEPING)
	{
		p = "SLEEPING";
	}

	return p;
}
static int checkStackUsage(const TaskConstType* pTaskConst, uint32_t* used)
{
	uint32_t i;
	uint8_t* pStack = pTaskConst->pStack;

	for(i=0; (i<pTaskConst->stackSize) && (0u == *pStack); i++, pStack++)
	{
		/* do nothing */
	}

	*used = pTaskConst->stackSize - i;
	/* round up */
	return (*used +(pTaskConst->stackSize/100 -1))*100/pTaskConst->stackSize;
}
#endif
/* ============================ [ FUNCTIONS ] ====================================================== */
/* |------------------+------------------------------------------------------------| */
/* | Syntax:          | StatusType ActivateTask ( TaskType <TaskID> )              | */
/* |------------------+------------------------------------------------------------| */
/* | Parameter (In):  | TaskID: Task reference                                     | */
/* |------------------+------------------------------------------------------------| */
/* | Parameter (Out): | none                                                       | */
/* |------------------+------------------------------------------------------------| */
/* | Description:     | The task <TaskID> is transferred from the suspended state  | */
/* |                  | into the ready state. The operating system encheckStackUsagesures that    | */
/* |                  | the task code is being executed from the first statement.  | */
/* |------------------+------------------------------------------------------------| */
/* | Particularities: | 1) The service may be called from interrupt level and from | */
/* |                  | task level (see Figure 12-1(os223.doc)).                   | */
/* |                  | 2) Rescheduling after the call to ActivateTask depends on  | */
/* |                  | the place it is called from (ISR, non preemptable task,    | */
/* |                  | preemptable task).                                         | */
/* |                  | 3)If E_OS_LIMIT is returned the activation is ignored.     | */
/* |                  | 4)When an extended task is transferred from suspended      | */
/* |                  | state into ready state all its events are cleared.         | */
/* |------------------+------------------------------------------------------------| */
/* | Status:          | Standard:                                                  | */
/* |                  | 1) No error, E_OK                                          | */
/* |                  | 2) Too many task activations of <TaskID>, E_OS_LIMIT       | */
/* |                  | Extended:                                                  | */
/* |                  | 1) Task <TaskID> is invalid, E_OS_ID                       | */
/* |------------------+------------------------------------------------------------| */
/* | Conformance:     | BCC1, BCC2, ECC1, ECC2                                     | */
/* |------------------+------------------------------------------------------------| */
StatusType ActivateTask ( TaskType TaskID )
{
	StatusType ercd = E_OK;
	TaskVarType* pTaskVar;
	imask_t imask;

	#if(OS_STATUS == EXTENDED)
	if( TaskID < TASK_NUM )
	{
	#endif
		pTaskVar   = &TaskVarArray[TaskID];
		Irq_Save(imask);
		if(SUSPENDED == TASK_STATE(pTaskVar))
		{
			InitContext(pTaskVar);

			#ifdef MULTIPLY_TASK_ACTIVATION
			pTaskVar-> activation = 1;
			#endif

			OS_TRACE_TASK_ACTIVATION(pTaskVar);

			Sched_AddReady(TaskID);
		}
		else
		{
			#ifdef MULTIPLY_TASK_ACTIVATION
			if(pTaskVar->activation < pTaskVar->pConst->maxActivation)
			{
				OS_TRACE_TASK_ACTIVATION(pTaskVar);
				pTaskVar-> activation++;
				#ifndef USE_SCHED_LIST
				Sched_AddReady(TaskID);
				#endif
			}
			else
			#endif
			{
				ercd = E_OS_LIMIT;
			}
		}

		if( (E_OK == ercd) &&
			(TCL_TASK == CallLevel) &&
			(ReadyVar->priority > RunningVar->priority) )
		{
			Sched_Preempt();
			Os_PortDispatch();
		}

		Irq_Restore(imask);
	#if(OS_STATUS == EXTENDED)
	}
	else
	{
		ercd = E_OS_ID;
	}
	#endif

	OSErrorOne(ActivateTask,TaskID);

	return ercd;
}

/* |------------------+--------------------------------------------------------------| */
/* | Syntax:          | StatusType TerminateTask ( void )                            | */
/* |------------------+--------------------------------------------------------------| */
/* | Parameter (In):  | none                                                         | */
/* |------------------+--------------------------------------------------------------| */
/* | Parameter (Out): | none                                                         | */
/* |------------------+--------------------------------------------------------------| */
/* | Description:     | This service causes the termination of the calling task. The | */
/* |                  | calling task is transferred from the running state into the  | */
/* |                  | suspended state.                                             | */
/* |------------------+--------------------------------------------------------------| */
/* | Particularities: | 1) An internal resource assigned to the calling task is      | */
/* |                  | automatically released. Other resources occupied by the task | */
/* |                  | shall have been released before the call to TerminateTask.   | */
/* |                  | If a resource is still occupied in standard status the       | */
/* |                  | behaviour is undefined.                                      | */
/* |                  | 2) If the call was successful, TerminateTask does not return | */
/* |                  | to the call level and the status can not be evaluated.       | */
/* |                  | 3) If the version with extended status is used, the service  | */
/* |                  | returns in case of error, and provides a status which can be | */
/* |                  | evaluated in the application.                                | */
/* |                  | 4) If the service TerminateTask is called successfully, it   | */
/* |                  | enforces a rescheduling.                                     | */
/* |                  | 5) Ending a task function without call to TerminateTask or   | */
/* |                  | ChainTask is strictly forbidden and may leave the system in  | */
/* |                  | an undefined state.                                          | */
/* |------------------+--------------------------------------------------------------| */
/* | Status:          | Standard:                                                    | */
/* |                  | 1)No return to call level                                    | */
/* |                  | Extended:                                                    | */
/* |                  | 1) Task still occupies resources, E_OS_RESOURCE              | */
/* |                  | 2) Call at interrupt level, E_OS_CALLEVEL                    | */
/* |------------------+--------------------------------------------------------------| */
/* | Conformance:     | BCC1, BCC2, ECC1, ECC2                                       | */
/* |------------------+--------------------------------------------------------------| */
StatusType TerminateTask( void )
{
	StatusType ercd = E_OK;
	imask_t mask;
	#if(OS_STATUS == EXTENDED)
	if( CallLevel != TCL_TASK )
	{
		ercd = E_OS_CALLEVEL;
	}
	else if(RunningVar->currentResource != INVALID_RESOURCE)
	{
		ercd = E_OS_RESOURCE;
	}
	#endif

	if(E_OK == ercd)
	{
		Irq_Save(mask);
		#ifdef MULTIPLY_TASK_ACTIVATION
		asAssert(RunningVar->activation > 0);
		RunningVar->activation--;
		if(RunningVar->activation > 0)
		{
			InitContext(RunningVar);
			#ifdef USE_SCHED_LIST
			Sched_AddReady(RunningVar - TaskVarArray);
			#endif
		}
		else
		#endif
		{
			RunningVar->state = SUSPENDED;
		}

		Sched_GetReady();
		OSPostTaskHook();
		Os_PortStartDispatch();

		Irq_Restore(mask);
	}

	OSErrorNone(TerminateTask);
	return ercd;
}

/* |------------------+-------------------------------------------------------------| */
/* | Syntax:          | StatusType ChainTask ( TaskType <TaskID> )                  | */
/* |------------------+-------------------------------------------------------------| */
/* | Parameter (In):  | TaskID Reference to the sequential succeeding task to       | */
/* |                  | be activated.                                               | */
/* |------------------+-------------------------------------------------------------| */
/* | Parameter (Out): | none                                                        | */
/* |------------------+-------------------------------------------------------------| */
/* | Description:     | This service causes the termination of the calling task.    | */
/* |                  | After termination of the calling task a succeeding task     | */
/* |                  | <TaskID> is activated. Using this service, it ensures       | */
/* |                  | that the succeeding task starts to run at the earliest      | */
/* |                  | after the calling task has been terminated.                 | */
/* |------------------+-------------------------------------------------------------| */
/* | Particularities: | 1. If the succeeding task is identical with the current     | */
/* |                  | task, this does not result in multiple requests. The task   | */
/* |                  | is not transferred to the suspended state, but will         | */
/* |                  | immediately become ready again.                             | */
/* |                  | 2. An internal resource assigned to the calling task is     | */
/* |                  | automatically released, even if the succeeding task is      | */
/* |                  | identical with the current task. Other resources occupied   | */
/* |                  | by the calling shall have been released before ChainTask    | */
/* |                  | is called. If a resource is still occupied in standard      | */
/* |                  | status the behaviour is undefined.                          | */
/* |                  | 3. If called successfully, ChainTask does not return to     | */
/* |                  | the call level and the status can not be evaluated.         | */
/* |                  | 4. In case of error the service returns to the calling      | */
/* |                  | task and provides a status which can then be evaluated      | */
/* |                  | in the application.                                         | */
/* |                  | 5.If the service ChainTask is called successfully, this     | */
/* |                  | enforces a rescheduling.                                    | */
/* |                  | 6. Ending a task function without call to TerminateTask     | */
/* |                  | or ChainTask is strictly forbidden and may leave the system | */
/* |                  | in an undefined state.                                      | */
/* |                  | 7. If E_OS_LIMIT is returned the activation is ignored.     | */
/* |                  | 8. When an extended task is transferred from suspended      | */
/* |                  | state into ready state all its events are cleared.          | */
/* |------------------+-------------------------------------------------------------| */
/* | Status:          | Standard:                                                   | */
/* |                  | 1. No return to call level                                  | */
/* |                  | 2. Too many task activations of <TaskID>, E_OS_LIMIT        | */
/* |                  | Extended:                                                   | */
/* |                  | 1. Task <TaskID> is invalid, E_OS_ID                        | */
/* |                  | 2. Calling task still occupies resources, E_OS_RESOURCE     | */
/* |                  | 3. Call at interrupt level, E_OS_CALLEVEL                   | */
/* |------------------+-------------------------------------------------------------| */
/* | Conformance:     | BCC1, BCC2, ECC1, ECC2                                      | */
/* |------------------+-------------------------------------------------------------| */
StatusType ChainTask    ( TaskType TaskID )
{
	StatusType ercd = E_OK;
	imask_t mask;
	TaskVarType* pTaskVar;
	
	#if(OS_STATUS == EXTENDED)
	if( TaskID >= TASK_NUM )
	{
		ercd = E_OS_ID;
	}
	else if(RunningVar->currentResource != INVALID_RESOURCE)
	{
		ercd = E_OS_RESOURCE;
	}
	else if( CallLevel != TCL_TASK )
	{
		ercd = E_OS_CALLEVEL;
	}
	#endif

	if(E_OK == ercd)
	{
		pTaskVar = &TaskVarArray[TaskID];

		if(pTaskVar == RunningVar)
		{
			Irq_Save(mask);
			InitContext(RunningVar);
			Sched_AddReady(TaskID);
			Irq_Restore(mask);
		}
		else
		{
			Irq_Save(mask);
			if(SUSPENDED == TASK_STATE(pTaskVar))
			{
				InitContext(pTaskVar);

				#ifdef MULTIPLY_TASK_ACTIVATION
				pTaskVar-> activation = 1;
				#endif

				Sched_AddReady(TaskID);
			}
			else
			{
				#ifdef MULTIPLY_TASK_ACTIVATION
				if(pTaskVar->activation < pTaskVar->pConst->maxActivation)
				{
					pTaskVar-> activation++;
					#ifndef USE_SCHED_LIST
					Sched_AddReady(TaskID);
					#endif
				}
				else
				#endif
				{
					ercd = E_OS_LIMIT;
				}
			}
			Irq_Restore(mask);

			if(ercd == E_OK)
			{
				Irq_Save(mask);
				#ifdef MULTIPLY_TASK_ACTIVATION
				asAssert(RunningVar->activation > 0);
				RunningVar->activation--;
				if(RunningVar->activation > 0)
				{
					InitContext(RunningVar);
					#ifdef USE_SCHED_LIST
					Sched_AddReady(RunningVar - TaskVarArray);
					#endif
				}
				else
				#endif
				{
					RunningVar->state = SUSPENDED;
				}
				Irq_Restore(mask);
			}
		}

		if(ercd == E_OK)
		{
			OS_TRACE_TASK_ACTIVATION(pTaskVar);
			Irq_Save(mask);
			Sched_GetReady();
			OSPostTaskHook();
			Os_PortStartDispatch();
			Irq_Restore(mask);
		}
	}

	OSErrorOne(ChainTask, TaskID);

	return ercd;

}
/* |------------------+-------------------------------------------------------------| */
/* | Syntax:          | StatusType Schedule ( void )                                | */
/* |------------------+-------------------------------------------------------------| */
/* | Parameter (In):  | none                                                        | */
/* |------------------+-------------------------------------------------------------| */
/* | Parameter (Out): | none                                                        | */
/* |------------------+-------------------------------------------------------------| */
/* | Description:     | If a higher-priority task is ready, the internal resource   | */
/* |                  | of the task is released, the current task is put into the   | */
/* |                  | ready state, its context is saved and the higher-priority   | */
/* |                  | task is executed. Otherwise the calling task is continued.  | */
/* |------------------+-------------------------------------------------------------| */
/* | Particularities: | Rescheduling only takes place if the task an internal       | */
/* |                  | resource is assigned to the calling task during             | */
/* |                  | system generation. For these tasks, Schedule enables a      | */
/* |                  | processor assignment to other tasks with lower or equal     | */
/* |                  | priority than the ceiling priority of the internal resource | */
/* |                  | and higher priority than the priority of the calling task   | */
/* |                  | in application-specific locations. When returning from      | */
/* |                  | Schedule, the internal resource has been taken again.       | */
/* |                  | This service has no influence on tasks with no internal     | */
/* |                  | resource assigned (preemptable tasks).                      | */
/* |------------------+-------------------------------------------------------------| */
/* | Status:          | Standard:                                                   | */
/* |                  | 1. No error, E_OK                                           | */
/* |                  | Extended:                                                   | */
/* |                  | 1. Call at interrupt level, E_OS_CALLEVEL                   | */
/* |                  | 2. Calling task occupies resources, E_OS_RESOURCE           | */
/* |------------------+-------------------------------------------------------------| */
/* | Conformance:     | BCC1, BCC2, ECC1, ECC2                                      | */
/* |------------------+-------------------------------------------------------------| */
StatusType Schedule     ( void )
{
	StatusType ercd = E_OK;
	imask_t mask;

	#if(OS_STATUS == EXTENDED)
	if( CallLevel != TCL_TASK )
	{
		ercd = E_OS_CALLEVEL;
	}
	else if(RunningVar->currentResource != INVALID_RESOURCE)
	{
		ercd = E_OS_RESOURCE;
	}
	#endif

	if(E_OK == ercd)
	{
		Irq_Save(mask);

		RunningVar->priority = RunningVar->pConst->initPriority;
		if(Sched_Schedule())
		{
			Os_PortDispatch();
		}
		RunningVar->priority = RunningVar->pConst->runPriority;
		Irq_Restore(mask);
	}

	OSErrorNone(Schedule);

	return ercd;
}

/* |------------------+---------------------------------------------------------| */
/* | Syntax:          | StatusType GetTaskID ( TaskRefType <TaskID> )           | */
/* |------------------+---------------------------------------------------------| */
/* | Parameter (In):  | none                                                    | */
/* |------------------+---------------------------------------------------------| */
/* | Parameter (Out): | TaskID Reference to the task which is currently running | */
/* |------------------+---------------------------------------------------------| */
/* | Description:     | GetTaskID returns the information about the TaskID of   | */
/* |                  | the task which is currently running.                    | */
/* |------------------+---------------------------------------------------------| */
/* | Particularities: | 1. Allowed on task level, ISR level and in several hook | */
/* |                  | routines (see Figure 12-1(os223)).                      | */
/* |                  | 2. This service is intended to be used by library       | */
/* |                  | functions and hook routines.                            | */
/* |                  | 3. If <TaskID> can't be evaluated (no task currently    | */
/* |                  | running), the service returns INVALID_TASK as TaskType. | */
/* |------------------+---------------------------------------------------------| */
/* | Status:          | Standard:  No error, E_OK                               | */
/* |                  | Extended:  No error, E_OK                               | */
/* |------------------+---------------------------------------------------------| */
/* | Conformance:     | BCC1, BCC2, ECC1, ECC2                                  | */
/* |------------------+---------------------------------------------------------| */
StatusType GetTaskID    ( TaskRefType pTaskType )
{
	imask_t mask;

	Irq_Save(mask);
	if(RunningVar !=  NULL)
	{
		*pTaskType = RunningVar - TaskVarArray;
	}
	else
	{
		*pTaskType = INVALID_TASK;
	}
	Irq_Restore(mask);

	return E_OK;
}

/* |------------------+-------------------------------------------------------| */
/* | Syntax:          | StatusType GetTaskState ( TaskType <TaskID>,          | */
/* |                  | TaskStateRefType <State> )                            | */
/* |------------------+-------------------------------------------------------| */
/* | Parameter (In):  | TaskID: Task reference                                | */
/* |------------------+-------------------------------------------------------| */
/* | Parameter (Out): | State: Reference to the state of the task <TaskID>    | */
/* |------------------+-------------------------------------------------------| */
/* | Description:     | Returns the state of a task (running, ready, waiting, | */
/* |                  | suspended) at the time of calling GetTaskState.       | */
/* |------------------+-------------------------------------------------------| */
/* | Particularities: | The service may be called from interrupt service      | */
/* |                  | routines, task level, and some hook routines (see     | */
/* |                  | Figure 12-1(os223.doc)). When a call is made from a   | */
/* |                  | task in a full preemptive system, the result may      | */
/* |                  | already be incorrect at the time of evaluation.       | */
/* |                  | When the service is called for a task, which is       | */
/* |                  | activated more than once, the state is set to         | */
/* |                  | running if any instance of the task is running.       | */
/* |------------------+-------------------------------------------------------| */
/* | Status:          | Standard: No error, E_OK                              | */
/* |                  | Extended: Task <TaskID> is invalid, E_OS_ID           | */
/* |------------------+-------------------------------------------------------| */
/* | Conformance:     | BCC1, BCC2, ECC1, ECC2                                | */
/* |------------------+-------------------------------------------------------| */
StatusType GetTaskState ( TaskType TaskID,TaskStateRefType State )
{
	StatusType ercd = E_OK;
	TaskVarType* pTaskVar;
	imask_t mask;

	#if(OS_STATUS == EXTENDED)
	if( TaskID < TASK_NUM )
	{
	#endif
		Irq_Save(mask);
		pTaskVar = &TaskVarArray[TaskID];
		if(RunningVar == pTaskVar)
		{
			*State = RUNNING;
		}
		else
		{
			*State   = pTaskVar->state;
		}
		Irq_Restore(mask);
	#if(OS_STATUS == EXTENDED)
	}
	else
	{
		ercd = E_OS_ID;

	}
	#endif

	OSErrorTwo(GetTaskState, TaskID, State);
	return ercd;
}

void Os_TaskInit(AppModeType appMode)
{
	TaskType id;

	const TaskConstType* pTaskConst;
	TaskVarType* pTaskVar;

	for(id=0; id < TASK_NUM; id++)
	{
		pTaskConst = &TaskConstArray[id];
		pTaskVar   = &TaskVarArray[id];

		pTaskVar->state = SUSPENDED;
		pTaskVar->pConst = pTaskConst;
		#ifdef USE_SHELL
		pTaskVar->actCnt = 0;
		#endif

		if(pTaskConst->appModeMask&appMode)
		{
			(void)ActivateTask(id);
		}
	}
#if(OS_PTHREAD_NUM > 0)
	for(id=0; id < OS_PTHREAD_NUM; id++)
	{
		pTaskVar   = &TaskVarArray[TASK_NUM+id];
		pTaskVar->pConst = NULL;
	}
#endif
}

#ifdef USE_SHELL
void statOsTask(void)
{
	TaskType id;

	const TaskConstType* pTaskConst;
	TaskVarType* pTaskVar;
	int pused;
	uint32_t used;
	SHELL_printf("Name             State      Prio IPrio RPrio  StackBase  StackSize"
			"   Used       Event(set/wait)   Act/ActSum parent\n");
#if(OS_PTHREAD_NUM > 0)
	SHELL_printf("                                                                  "
			"              list/entry\n");
#endif

	for(id=0; id < TASK_NUM; id++)
	{
		pTaskConst = &TaskConstArray[id];
		pTaskVar   = &TaskVarArray[id];
		pused = checkStackUsage(pTaskConst,&used);
		SHELL_printf("%-16s %-9s %3d  %3d   %3d     0x%08X 0x%08X %2d%%(0x%04X) ",
				pTaskConst->name, taskStateToString(pTaskVar->state),
				pTaskVar->priority, pTaskConst->initPriority, pTaskConst->runPriority,
				pTaskConst->pStack, pTaskConst->stackSize, pused, used);
		if(NULL != pTaskConst->pEventVar)
		{
			SHELL_printf("%08X/%08X %3d/%-6d ",
					pTaskConst->pEventVar->set, pTaskConst->pEventVar->wait,
#ifdef MULTIPLY_TASK_ACTIVATION
					pTaskVar->activation,
#else
					1,
#endif
					pTaskVar->actCnt);
		}
		else
		{
			SHELL_printf("null              %3d/%-6d ",
#ifdef MULTIPLY_TASK_ACTIVATION
					pTaskVar->activation,
#else
					1,
#endif
					pTaskVar->actCnt);
		}

		SHELL_printf(" %s\n", (pTaskVar == RunningVar)?"<-RunningVar":"");
	}

#if(OS_PTHREAD_NUM > 0)
	for(id=0; id < OS_PTHREAD_NUM; id++)
	{
		struct pthread* tid;
		pTaskVar   = &TaskVarArray[TASK_NUM+id];
		pTaskConst = pTaskVar->pConst;
		tid = (struct pthread*)pTaskConst;
		if(tid > (struct pthread*)1)
		{
			SHELL_printf("pthread%-9d %-9s %3d  %3d   %3d     0x%08X 0x%08X %2d%%(0x%04X) %p/%p %3d/%-6d ",
					id, taskStateToString(pTaskVar->state),
					pTaskVar->priority, pTaskConst->initPriority, pTaskConst->runPriority,
					pTaskConst->pStack, pTaskConst->stackSize, pused, used,
					pTaskVar->list, tid->start,
#ifdef MULTIPLY_TASK_ACTIVATION
					pTaskVar->activation,
#else
					1,
#endif				 
					pTaskVar->actCnt);
#ifdef USE_PTHREAD_PARENT
			asAssert(tid->parent);
			if((tid->parent-TaskVarArray) < TASK_NUM)
			{
				SHELL_printf(" %s", tid->parent->pConst->name);
			}
			else
			{
				SHELL_printf(" pthread%d", tid->parent -TaskVarArray);
			}
#endif
			SHELL_printf(" %s\n", (pTaskVar == RunningVar)?"<-RunningVar":"");
		}
	}
#endif
}
#endif
