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
 *  $Id: task.c 504 2015-12-24 01:22:56Z witz-itoyo $
 */

/*
 *		Task control module
 */

#include "kernel_impl.h"
#include "check.h"
#include "task.h"
#include "interrupt.h"
/*
 *  The default definition of the trace log macro
 */
#ifndef LOG_TSKSTAT
#define LOG_TSKSTAT(p_tcb)
#endif /* LOG_TSKSTAT */

/* Prototype declaration of internal functions */
LOCAL_INLINE uint16 bitmap_search(uint16 bitmap);
LOCAL_INLINE boolean primap_empty(void);
LOCAL_INLINE PriorityType primap_search(void);
LOCAL_INLINE void primap_set(PriorityType pri);
LOCAL_INLINE void primap_clear(PriorityType pri);

#ifdef TOPPERS_task_initialize

/*
 *  Of the execution state task
 */
TCB				*p_runtsk;

/*
 *  Highest priority task
 */
TCB				*p_schedtsk;

/*
 *  Highest priority in the ready queue
 */
PriorityType	nextpri;

/*
 *  Ready queue
 */
QUEUE			ready_queue[TNUM_TPRI];

/*
 *  Bit map for the ready queue search
 */
uint16			ready_primap;

/*
 *  Initialization of the task management module
 */
void
task_initialize(void)
{
	TaskType	i;
	TCB			*p_tcb;

	p_runtsk = NULL;
	p_schedtsk = NULL;

	for (i = 0U; i < TNUM_TPRI; i++) {
		queue_initialize(&(ready_queue[i]));
	}
	nextpri = TPRI_MINTASK;
	ready_primap = 0U;

	for (i = 0U; i < tnum_task; i++) {
		p_tcb = &(tcb_table[i]);
		p_tcb->p_tinib = &(tinib_table[i]);
		p_tcb->actcnt = 0U;
		p_tcb->tstat = SUSPENDED;
		p_tcb->tpacb.lastarrival.tfcount = 0U;
		p_tcb->tpacb.lastarrival.tftick = 0U;
		p_tcb->tpacb.is_not_first = FALSE;
		p_tcb->remaining_execution = 0U;
		p_tcb->watchtype = NON_MONITORING;
#ifdef CFG_USE_PROTECTIONHOOK
		p_tcb->calltfn = FALSE;
#endif /* CFG_USE_PROTECTIONHOOK */

		if ((p_tcb->p_tinib->autoact & ((AppModeType) 1 << appmodeid)) != APPMODE_NONE) {
			p_tcb->tpacb.is_not_first = TRUE;
			(void) make_active(p_tcb);
		}
	}
}

#endif /* TOPPERS_task_initialize */

/*
 *  Bit map search function
 *
 *  Of one bit in the bitmap, and searches the one of the most backward (right), 
 * and returns the bit number
 *  The bit number is the least significant bit is set to 0. Do not specify 
 * 0 for the bitmap. In this function, it is assumed that the bitmap 
 * is 16-bit, you are the type uint16
 *
 *  In the processor with a bit search instruction, those who rewrite to
 * use the bit search instruction in some cases efficient
 *  In such cases, define a bitmap_search that uses a bit search 
 * instruction in the target-dependent part, and also may be macro
 * defines the OMIT_BITMAP_SEARCH, corresponding search direction of the 
 * bit search instruction of the reason in the priority and bits such as 
 * reverse If you want to change, it is sufficient to define a macro PRIMAP_BIT
 *
 *  There also, if the standard library is ffs, also defined potential efficiency 
 * is better to use the standard library is as follows:
 *		#define	bitmap_search(bitmap) (ffs(bitmap) - 1)
 */
#ifndef PRIMAP_BIT
#define PRIMAP_BIT(pri)		((uint16) ((uint16) 1U << (pri)))
#endif /* PRIMAP_BIT */

#ifndef OMIT_BITMAP_SEARCH

LOCAL_INLINE uint16
bitmap_search(uint16 bitmap)
{
	/*
	 *  Table for the bit map search function
	 */
	const uint8	bitmap_search_table[BITMAP_NUM] = {
		0U, 1U, 0U, 2U, 0U, 1U, 0U,
		3U, 0U, 1U, 0U, 2U, 0U, 1U, 0U
	};

	uint16		n = 0U;

	ASSERT(bitmap != 0U);
	if ((bitmap & 0x00ffU) == 0U) {
		bitmap >>= 8U;
		n += 8U;
	}
	if ((bitmap & 0x0fU) == 0U) {
		bitmap >>= 4U;
		n += 4U;
	}
	return(n + bitmap_search_table[(bitmap & 0x000fU) - 1U]);
}

#endif /* OMIT_BITMAP_SEARCH */

/*
 *  Empty or check priority bitmap
 */
LOCAL_INLINE boolean
primap_empty(void)
{
	return(ready_primap == 0U);
}

/*
 *  Search priority bitmap
 */
LOCAL_INLINE PriorityType
primap_search(void)
{
	return((PriorityType) bitmap_search(ready_primap));
}

/*
 *  Set of priority bitmap
 */
LOCAL_INLINE void
primap_set(PriorityType pri)
{
	ready_primap |= PRIMAP_BIT(pri);
}

/*
 *  Clear priority bitmap
 */
LOCAL_INLINE void
primap_clear(PriorityType pri)
{
	ready_primap &= (uint16) ~PRIMAP_BIT(pri);
}

/*
 *  Search for the highest priority task
 */
#ifdef TOPPERS_search_schedtsk

void
search_schedtsk(void)
{
	if (primap_empty() != FALSE) {
		p_schedtsk = NULL;
	}
	else {
		p_schedtsk = (TCB *) (queue_delete_next(&(ready_queue[nextpri])));
		if (queue_empty(&(ready_queue[nextpri])) != FALSE) {
			primap_clear(nextpri);
			nextpri = (primap_empty() != FALSE) ?
					  TPRI_MINTASK : primap_search();
		}
	}
}

#endif /* TOPPERS_search_schedtsk */

/*
 *  Transition to a state that can be executed
 */
#ifdef TOPPERS_make_runnable

boolean
make_runnable(TCB *p_tcb)
{
	PriorityType	pri, schedpri;
	boolean			is_next_schedtsk = TRUE;

	if (p_tcb->p_tinib->execution_budget != 0U) {
		p_tcb->watchtype = TASK_MONITORING;
	}
	else {
		p_tcb->watchtype = NON_MONITORING;
	}
	p_tcb->remaining_execution = p_tcb->p_tinib->execution_budget;

	p_tcb->tstat = READY;
	LOG_TSKSTAT(p_tcb);
	if (p_schedtsk != NULL) {
		pri = p_tcb->curpri;
		schedpri = p_schedtsk->curpri;
		if (pri >= schedpri) {
			/*
			 *  If schedtsk has a higher priority,
			 * put p_tcb to the end of the ready queue
			 */
			queue_insert_prev(&(ready_queue[pri]), &(p_tcb->task_queue));
			primap_set(pri);
			if (pri < nextpri) {
				nextpri = pri;
			}
			is_next_schedtsk = FALSE;
		}
		else {
			/*
			 *  If p_tcb has a higher priority, place the schedtsk to
			 * the start of the ready queue, and the p_tcb becomes the new schedtsk
			 */
			queue_insert_next(&(ready_queue[schedpri]), &(p_schedtsk->task_queue));
			primap_set(schedpri);
			nextpri = schedpri;
		}
	}

	if (is_next_schedtsk != FALSE) {
		p_schedtsk = p_tcb;
	}
	return(is_next_schedtsk);
}

#endif /* TOPPERS_make_runnable */

/*
 *  The transition from the state that can be run to another state
 *
 *  Implement the make_non_runable also SC1 for make_non_runnable is 
 * implemented in SC1-MC, SC1 also match the function configuration of SC1-MC
 *  (In SC1-MC, it is necessary to put the process to make sure that the p_runtsk 
 * and p_schedtsk is consistent, in SC1, is set to search_schedtsk only call processing)
 */
#ifdef TOPPERS_make_non_runnable

void
make_non_runnable(void)
{
	search_schedtsk();
}

#endif /* TOPPERS_make_non_runnable */

/*
 *  Activation of a task
 *
 *  In TerminateTask and ChainTask, be careful because there 
 * is a case to call make_active to own task
 */
#ifdef TOPPERS_make_active

boolean
make_active(TCB *p_tcb)
{
	p_tcb->curpri = p_tcb->p_tinib->inipri;
	if (TSKID(p_tcb) < tnum_exttask) {
		p_tcb->curevt = EVTMASK_NONE;
		p_tcb->waievt = EVTMASK_NONE;
	}
	p_tcb->p_lastrescb = NULL;
	p_tcb->p_lastcntcb = NULL;

	activate_context(p_tcb);
	return(make_runnable(p_tcb));
}

#endif /* TOPPERS_make_active */

/*
 *  Task preemption
 */
#ifdef TOPPERS_preempt

void
preempt(void)
{
	PriorityType pri;

	ASSERT(p_runtsk == p_schedtsk);
	pri = p_runtsk->curpri;
	queue_insert_next(&(ready_queue[pri]), &(p_runtsk->task_queue));
	primap_set(pri);
	search_schedtsk();
}

#endif /* TOPPERS_preempt */

/*
 *  There is a need to call in a state where the resources 
 * released to the running task in SUSPENDED state
 */
#ifdef TOPPERS_suspend

void
suspend(void)
{
	p_runtsk->tstat = SUSPENDED;
	if (is_tp_timer_running == TRUE) {
		/* Timing protection timer is stopped */
		tp_stop_task_monitor();
	}
	LOG_TSKSTAT(p_runtsk);
	make_non_runnable();
	if (p_runtsk->actcnt > 0U) {
		p_runtsk->actcnt -= 1U;
		(void) make_active(p_runtsk);
	}
}

#endif /* TOPPERS_suspend */

/*
 *  All resources return of the task
 */
#ifdef TOPPERS_release_taskresources

void
release_taskresources(TCB *p_tcb)
{
	if (p_tcb->p_lastrescb != NULL) {
		if (p_tcb->curpri <= TPRI_MINISR) {
			/* It is to interrupt enable If free resources all */
			x_set_ipm((PriorityType) TIPM_ENAALL);
		}
		/* By freeing the resources all the process returns to the executing priority */
		p_tcb->curpri = p_tcb->p_tinib->exepri;

		/* It comes with the OS interrupt disable state abnormality p_tcb->p_lastrescb != NULL */
		do {
			p_tcb->p_lastrescb->lockflg = FALSE;
			p_tcb->p_lastrescb->res_saved_watchtype = NON_MONITORING;
			p_tcb->p_lastrescb->res_difftime = 0U;
			p_tcb->p_lastrescb = p_tcb->p_lastrescb->p_prevrescb;
		} while (p_tcb->p_lastrescb != NULL);
	}
}

#endif /* TOPPERS_release_taskresources */

/*
 *  All the counter state of the task I return to CS_NULL
 */
#ifdef TOPPERS_cancel_taskcounters

void
cancel_taskcounters(TCB *p_tcb)
{
	if (p_tcb->p_lastcntcb != NULL) {

		/* It comes with the OS interrupt disable state abnormality */
		do {
			p_tcb->p_lastcntcb->cstat = CS_NULL;
			p_tcb->p_lastcntcb = p_tcb->p_lastcntcb->p_prevcntcb;
		} while (p_tcb->p_lastcntcb != NULL);
	}
}
#endif /* TOPPERS_cancel_taskcounters */

/*
 *  Protection of fraud at the end of task
 *  TerminateTask (), ChainTask () No end of the current task in the processing 
 * of the case where the (return from the function of the task)
 */
#ifdef TOPPERS_exit_task

void
exit_task(void)
{
	x_nested_lock_os_int();

	/* To cancel the interrupt prohibition in the case of interrupt disabled state */
	release_interrupts(OSServiceId_Invalid);

	/* To release the resources in the case of remains resource reservation */
	release_taskresources(p_runtsk);

#ifdef CFG_USE_ERRORHOOK
	/* Call the error hook */
	call_errorhook(E_OS_MISSINGEND, OSServiceId_TaskMissingEnd);
#endif /* CFG_USE_ERRORHOOK */

	suspend();

	/* Post task hook is called when the post task hook is valid */
	exit_and_dispatch();
}

#endif /* TOPPERS_exit_task */

#ifdef TOPPERS_remove_task_from_queue

/*
 *  You want to delete a task from the ready queue
 */
void
remove_task_from_queue(TCB *p_tcb, PriorityType remove_task_pri)
{
	queue_delete(&(p_tcb->task_queue));
	if (queue_empty(&(ready_queue[remove_task_pri])) != FALSE) {
		primap_clear(remove_task_pri);
		nextpri = (primap_empty() != FALSE) ?	TPRI_MINTASK : primap_search();
	}
}

#endif /* TOPPERS_remove_task_from_queue */

/*
 *  Forced termination of its own task
 *    It is called only from ProtectionHook
 *      Resources of the release, after the release of the interrupt disable
 *       Do processing of TerminateTask equivalent
 *      If forced task completed, because it does not call the PostTaskHook to TerminateTask
 *      It is handled differently than
 *  This function is assumed to be called in the OS interrupt disable state
 */
#ifdef TOPPERS_force_terminate_task

void
force_terminate_task(TCB *p_tcb)
{
	/*
	 *  You want to cancel the interrupt prohibition
	 *  Because it is not called the error hook, and the OSServiceId_Invalid argument
	 */
	release_interrupts(OSServiceId_Invalid);

	/* If the as-resource reservation, resource release */
	release_taskresources(p_tcb);
	/* Initialize the state of the counter */
	cancel_taskcounters(p_tcb);

	suspend();

	exit_and_dispatch_nohook();
}

#endif /* TOPPERS_force_terminate_task */

/*
 *  Forced termination of SAP belongs to the task
 */
#ifdef TOPPERS_force_term_osap_task

void
force_term_osap_task(OSAPCB *p_osapcb)
{
	/* To kill the task that belongs to the OSAP */
	TaskType		i;
	TCB				*p_tcb;
	PriorityType	remove_task_pri;

	for (i = 0U; i < tnum_task; i++) {
		p_tcb = &tcb_table[i];
		if ((tinib_table[i].p_osapcb == p_osapcb) &&
			(p_tcb != p_runtsk)) {
			/*
			 *  Forced termination of tasks than OSAP end / restart
			 */
			p_tcb->actcnt = 0U;
#ifdef CFG_USE_PROTECTIONHOOK
			p_tcb->calltfn = FALSE;
#endif /* CFG_USE_PROTECTIONHOOK */

			if (p_tcb->tstat == READY) {
				/* corresponding to the case where curpri and inipri it has been 
				 * linked to the ready queue with a different value */
				remove_task_pri = p_tcb->curpri;

				/* If the as-resource reservation, resource release */
				release_taskresources(p_tcb);

				/* Initialize the state of the counter */
				cancel_taskcounters(p_tcb);

				/* The target task is set to SUSPEND state, to be removed from the ready queue */
				p_tcb->tstat = SUSPENDED;
				remove_task_from_queue(p_tcb, remove_task_pri);
			}
			else {
				p_tcb->tstat = SUSPENDED;
			}

			/*
			 *  Here we accept the C2ISR.
			 *  Since nested_lock_os_int_cnt such is 2 or more if you came here from the hook, 
			 * it is not released interrupt disabled.
			 *  Even in SusOS state, interrupt priority mask because while being held, 
			 * C2ISR does not occur.
			 */
			x_nested_unlock_os_int();

			/* Here it will be the interrupt disable */
			x_nested_lock_os_int();
		}
	}

	p_tcb = p_runtsk;
	/* Because it is called from the restart task to kill the OSAP */
	/* No need to initialize the resource release and counter state of */
	/* It will be the target task and SUSPEND state */
	/* update of p_schedtsk will be carried out from the back to the force_term_osap_main */
	p_tcb->tstat = SUSPENDED;
}

#endif /* TOPPERS_force_term_osap_task */

/*
 *  to save the p_schedtsk to the top of the ready queue
 */
#ifdef TOPPERS_move_schedtsk

void
move_schedtsk(void)
{
	queue_insert_next(&(ready_queue[p_schedtsk->curpri]), &(p_schedtsk->task_queue));
	primap_set(p_schedtsk->curpri);
	nextpri = p_schedtsk->curpri;
}

#endif /* TOPPERS_move_schedtsk */
