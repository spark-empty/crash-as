/*
 *  TOPPERS ATK2
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *      Automotive Kernel Version 2
 *
 *  Copyright (C) 2011-2015 by Center for Embedded Computing Systems
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2011-2015 by FUJI SOFT INCORPORATED, JAPAN
 *  Copyright (C) 2011-2013 by Spansion LLC, USA
 *  Copyright (C) 2011-2015 by NEC Communication Systems, Ltd., JAPAN
 *  Copyright (C) 2011-2015 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
 *  Copyright (C) 2011-2014 by Renesas Electronics Corporation, JAPAN
 *  Copyright (C) 2011-2015 by Sunny Giken Inc., JAPAN
 *  Copyright (C) 2011-2015 by TOSHIBA CORPORATION, JAPAN
 *  Copyright (C) 2011-2015 by Witz Corporation
 *  Copyright (C) 2014-2015 by AISIN COMCRUISE Co., Ltd., JAPAN
 *  Copyright (C) 2014-2015 by eSOL Co.,Ltd., JAPAN
 *  Copyright (C) 2014-2015 by SCSK Corporation, JAPAN
 *  Copyright (C) 2015 by SUZUKI MOTOR CORPORATION
 *  Copyright (C) 2016 by Fan Wang(parai@foxmail.com), China
 * 
 * The above copyright holders grant permission gratis to use,
 * duplicate, modify, or redistribute (hereafter called use) this
 * software (including the one made by modifying this software),
 * provided that the following four conditions (1) through (4) are
 * satisfied.
 * 
 * (1) When this software is used in the form of source code, the above
 *    copyright notice, this use conditions, and the disclaimer shown
 *    below must be retained in the source code without modification.
 *
 * (2) When this software is redistributed in the forms usable for the
 *    development of other software, such as in library form, the above
 *    copyright notice, this use conditions, and the disclaimer shown
 *    below must be shown without modification in the document provided
 *    with the redistributed software, such as the user manual.
 *
 * (3) When this software is redistributed in the forms unusable for the
 *    development of other software, such as the case when the software
 *    is embedded in a piece of equipment, either of the following two
 *    conditions must be satisfied:
 *
 *  (a) The above copyright notice, this use conditions, and the
 *      disclaimer shown below must be shown without modification in
 *      the document provided with the redistributed software, such as
 *      the user manual.
 *
 *  (b) How the software is to be redistributed must be reported to the
 *      TOPPERS Project according to the procedure described
 *      separately.
 *
 * (4) The above copyright holders and the TOPPERS Project are exempt
 *    from responsibility for any type of damage directly or indirectly
 *    caused from the use of this software and are indemnified by any
 *    users or end users of this software from any and all causes of
 *    action whatsoever.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS." THE ABOVE COPYRIGHT HOLDERS AND
 * THE TOPPERS PROJECT DISCLAIM ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, ITS APPLICABILITY TO A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS AND THE
 * TOPPERS PROJECT BE LIABLE FOR ANY TYPE OF DAMAGE DIRECTLY OR
 * INDIRECTLY CAUSED FROM THE USE OF THIS SOFTWARE.
 *
 *  $Id: task.h 504 2015-12-24 01:22:56Z witz-itoyo $
 */

/*
 *		Task management function
 */

#ifndef TOPPERS_TASK_H
#define TOPPERS_TASK_H

#include "queue.h"
#include "resource.h"

typedef struct task_control_block TCB;
#include "osap.h"
#include "counter.h"
#include "timingprotection.h"

/*
 *  The definition of the event mask value
 */
#define EVTMASK_NONE	((EventMaskType) 0) /* None Event */

/*
 *  Range of priority (external representation)
 */
#define TMIN_TPRI		UINT_C(0)       /* The minimum value of the task priority (the lowest value) */
#define TMAX_TPRI		UINT_C(15)      /* The maximum value of the task priority (maximum value) */

/*
 *  Definition of the number of stages of priority
 */
#define TNUM_TPRI		((TMAX_TPRI - TMIN_TPRI) + 1U)

/*
 *  Definition of priority values (internal representation)
 */
#define TPRI_MINTASK	((PriorityType) (TNUM_TPRI - 1U))               /* Lowest task priority */
#define TPRI_MAXTASK	((PriorityType) (0))                            /* Highest task priority */

/*
 *  Macro for taking out the TCB from the task ID
 */
#define get_tcb(tskid)		(&(tcb_table[(tskid)]))

/*
 *  Macro for taking out the task ID from the TCB
 *  p_tcb There can not be used in the case of NULL
 */
#define TSKID(p_tcb)	((TaskType) ((p_tcb) - tcb_table))

#ifndef OMIT_BITMAP_SEARCH
#define BITMAP_NUM		15       /* bitmap_search_tableのサイズ */
#endif /* OMIT_BITMAP_SEARCH */

/*
 *  Declaration of the variable to hold the number of tasks
 */
extern const TaskType	tnum_task;          /* The number of tasks */
extern const TaskType	tnum_exttask;       /* The number of extension task */


/*
 *  Task initialization block
 *
 *  The information about the task, and the part that can be placed in ROM 
 * in order to value does not change (task initialization block), part of 
 * the value must be placed in RAM in order to change (task control block, TCB) 
 * separated into, in the TCBPut a pointer to the corresponding task 
 * initialization block
 *  Person how to put a pointer to the TCB corresponding to the task 
 * initialization block, is desirable from the viewpoint of saving the 
 * RAM, are not employed for the execution efficiency deteriorates
 *  It treated similarly for the other objects
 */
typedef struct task_initialization_block {
	FunctionRefType	task;       /* Start address of the task */

#ifdef USE_TSKINICTXB
	TSKINICTXB tskinictxb;           /* Task initialization context block */
#else /* USE_TSKINICTXB */
	MemorySizeType	sstksz;         /* The size of the system stack area (rounded value) */
	void			*sstk;          /* Bottom address of the system stack area(SC3) */
	MemorySizeType	ustksz;         /* The size of the stack area (rounded value) */
	void			*ustk;          /* Bottom address of the stack area(SC3) */
#endif /* USE_TSKINICTXB */
	OSAPCB			*p_osapcb;      /* Management block belongs to OS application */
	uint32			acsbtmp;        /* Permissions OS application bitmap*/
	PriorityType	inipri;         /* Initial priority (internal representation) */
	PriorityType	exepri;         /* Run at the start priority of (internal representation) */
	uint8			maxact;         /* The maximum number of multiple start-up request */
	AppModeType		autoact;        /* Starting up for the mode */
#ifndef OMIT_STKMPUINFOB
	STKMPUINFOB	stkmpu;             /* MPU information of the stack */
#endif
	TFTIME		time_frame;                     /* Minimum arrival time */
	TickType	execution_budget;               /* Run time budget */
	uint8		monitoring;                     /* Time monitoring bitmap */
} TINIB;

/*
 *  Task management block
 */
struct task_control_block {
	QUEUE			task_queue;             /* Task queue (need to enter at the top of the structure) */
	const TINIB		*p_tinib;               /* A pointer to the initialization block */
	PriorityType	curpri;                 /* The current priority (internal representation)*/
	TaskStateType	tstat;                  /* Task state (internal representation)*/
	uint8			actcnt;                 /* Multiple activation request number */
	EventMaskType	curevt;                 /* The current value of the event */
	EventMaskType	waievt;                 /* Events waiting */
	RESCB			*p_lastrescb;           /* A pointer to the last acquired resource management block */
	CNTCB			*p_lastcntcb;           /* Finally, a pointer to the operation to counter management block */
	TSKCTXB			tskctxb;                /* Task context block */
	TickType		remaining_execution;    /* The remaining run time */
	MonitoringType	watchtype;              /* Current monitoring in item */
	TPACB			tpacb;                  /* Arrival interval protection protection management block */
#ifdef CFG_USE_PROTECTIONHOOK
	boolean			calltfn;                /* Trust function call in the flag */
#endif /* CFG_USE_PROTECTIONHOOK */
};

/*
 *  Of the execution state task
 *
 *  If there is no task in the RUNNING state, it wants to NULL
 */
extern TCB			*p_runtsk;

/*
 *  Highest priority task
 *
 *  During task execution is consistent with runtask
 *  To, I want to NULL if there is no task of execution can state 
 * (execution state or executable state)
 */
extern TCB			*p_schedtsk;

/*
 *  Highest priority in the ready queue
 *
 *  Since the ready queue contains only executable state task, 
 * to hold the highest priority in the executable state task
 *  When ready queue is empty (when there is no executable state tasks) you want to TPRI_MINTASK
 */
extern PriorityType	nextpri;

/*
 *  Ready queue
 *
 *  Ready queue is ready queue is a queue for managing the tasks ready for execution, 
 * TCB of a task that consists of the task queue for each priority level is 
 * registered in the priority relevant queue
 */
extern QUEUE		ready_queue[TNUM_TPRI];

/*
 *  Bit map for the ready queue search
 *
 *  To perform the search of the ready queue efficiently, and provides a bitmap 
 * indicating whether the entered tasks in the task queue for each priority
 *  By using the bit map, it is possible to reduce the number of memory accesses, 
 * the processor bit manipulation instruction is not substantial, if the number 
 * of stages of priority is low, because of the overhead of the bitmap operation, 
 * reverse there is also a possibility that the efficiency falls
 *
 *  Because the priority is assumed to be a 16 phase, it is as uint16 type
 */
extern uint16		ready_primap;

/*
 *  Task initialization block area (kernel_mem.c)
 */
extern const TINIB	tinib_table[];

/*
 *  TCB of area
 */
extern TCB			tcb_table[];

/*
 *  Initialization of the task management module
 */
extern void task_initialize(void);

/*
 *  Activation of a task
 *
 *  And performs initialization required for startup of the starting 
 * (and task specified by p_tcb) (cell transition to a state that can be 
 * performed from hibernation) task the task
 */
extern boolean make_active(TCB *p_tcb);

/*
 *  Transition to a state that can be executed
 *
 *  Priority of the task for transitioning to a state that can perform the task 
 * (task specified in the p_tcb) is higher than the priority of the highest 
 * priority task (schedtsk) is to the target task and the new highest priority 
 * task,It puts the highest priority task until it to the top of the ready queue
 *  Otherwise, when the target task to put the target task to the end of the 
 * ready queue with the highest priority task, returns TRUE
 */
extern boolean make_runnable(TCB *p_tcb);

/*
 *  The transition from the state that can be run to another state
 */
extern void make_non_runnable(void);

/*
 *  Search for the highest priority task
 *
 *  Search for the task of highest priority in the ready queue
 *  If the ready queue is empty, do not call this function
 */
extern void search_schedtsk(void);

/*
 *  Task preemption
 *
 *  Moves the current task to the READY state, after returning from the function 
 * to the highest priority task in the running state, it is assumed to switch 
 * calls the dispatch to other tasks
 */
extern void preempt(void);

/*
 *  It will be a running task in SUSPENDED state
 */
extern void suspend(void);

/*
 *  Release of resources
 */
extern void release_taskresources(TCB *p_tcb);

/*
 *  Initialization of the counter
 */
extern void cancel_taskcounters(TCB *p_tcb);

/*
 *  Starting the expiration processing dedicated task
 *
 *  Conditions: it is called by the OS interrupt disable state
 */
extern StatusType activate_task_action(OSAPCB *p_expire_osapcb, TaskType TaskID);

/*
 *  Set of expiration processing dedicated event
 *
 *  Conditions: it is called by the OS interrupt disable state
 */
extern StatusType set_event_action(OSAPCB *p_expire_osapcb, TaskType TaskID, EventMaskType Mask);

/*
 *  You want to delete a task from the ready queue
 */
extern void remove_task_from_queue(TCB *p_tcb, PriorityType remove_task_pri);

/*
 *  It will be a task that has entered the ready queue in hibernation
 */
extern void suspend_ready_task(TCB *p_tcb, PriorityType remove_task_pri);

/*
 *  Forced termination of its own task
 */
extern void force_terminate_task(TCB *p_tcb);

/*
 *  Function to call when the task unauthorized end
 */
extern void exit_task(void);

/*
 *  Forced termination of SAP belongs to the task
 */
extern void force_term_osap_task(OSAPCB *p_osapcb);

/*
 *  to save the p_schedtsk to the top of the ready queue
 */
extern void move_schedtsk(void);

/* target dependent TCB processing */
extern void activate_force_term_osap_main(TCB* tcb);
extern void activate_context(TCB* tcb);

#endif /* TOPPERS_TASK_H_ */
