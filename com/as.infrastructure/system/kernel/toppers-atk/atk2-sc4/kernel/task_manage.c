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
 *  $Id: task_manage.c 504 2015-12-24 01:22:56Z witz-itoyo $
 */

/*
 *		Task management module
 */

#include "kernel_impl.h"
#include "check.h"
#include "task.h"

#include "timingprotection.h"

/*
 *  The default definition of the trace log macro
 */
#ifndef LOG_TSKSTAT
#define LOG_TSKSTAT(p_tcb)
#endif /* LOG_TSKSTAT */

#ifndef LOG_ACTTSK_ENTER
#define LOG_ACTTSK_ENTER(tskid)
#endif /* LOG_ACTTSK_ENTER */

#ifndef LOG_ACTTSK_LEAVE
#define LOG_ACTTSK_LEAVE(ercd)
#endif /* LOG_ACTTSK_LEAVE */

#ifndef LOG_TERTSK_ENTER
#define LOG_TERTSK_ENTER()
#endif /* LOG_TERTSK_ENTER */

#ifndef LOG_TERTSK_LEAVE
#define LOG_TERTSK_LEAVE(ercd)
#endif /* LOG_TERTSK_LEAVE */

#ifndef LOG_CHNTSK_ENTER
#define LOG_CHNTSK_ENTER(tskid)
#endif /* LOG_CHNTSK_ENTER */

#ifndef LOG_CHNTSK_LEAVE
#define LOG_CHNTSK_LEAVE(ercd)
#endif /* LOG_CHNTSK_LEAVE */

#ifndef LOG_SCHED_LEAVE
#define LOG_SCHED_ENTER()
#endif /* LOG_SCHED_LEAVE */

#ifndef LOG_SCHED_LEAVE
#define LOG_SCHED_LEAVE(ercd)
#endif /* LOG_SCHED_LEAVE */

#ifndef LOG_GETTID_ENTER
#define LOG_GETTID_ENTER()
#endif /* LOG_GETTID_ENTER */

#ifndef LOG_GETTID_LEAVE
#define LOG_GETTID_LEAVE(ercd, p_tskid)
#endif /* LOG_GETTID_LEAVE */

#ifndef LOG_GETTST_ENTER
#define LOG_GETTST_ENTER(tskid)
#endif /* LOG_GETTST_ENTER */

#ifndef LOG_GETTST_LEAVE
#define LOG_GETTST_LEAVE(ercd, p_state)
#endif /* LOG_GETTST_LEAVE */


/*
 *  Activation of a task
 */
#ifdef TOPPERS_ActivateTask

StatusType
ActivateTask(TaskType TaskID)
{
	StatusType	ercd = E_OK;
	TCB			*p_tcb;
	OSAPCB		*p_osapcb;
	TFTIME		tftime = {
		0U, 0U
	};

	LOG_ACTTSK_ENTER(TaskID);
	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_ACTIVATETASK);
	CHECK_ID(TaskID < tnum_task);
	p_tcb = get_tcb(TaskID);
	CHECK_RIGHT(p_tcb->p_tinib->acsbtmp);

	p_osapcb = p_tcb->p_tinib->p_osapcb;
	x_nested_lock_os_int();

	/* Start checking the SOAP of the state of the task belongs to */
	D_CHECK_ACCESS((p_osapcb->osap_stat == APPLICATION_ACCESSIBLE) ||
				   ((p_osapcb->osap_stat == APPLICATION_RESTARTING) &&
					(p_osapcb == p_runosap)));

	tftime = p_tcb->p_tinib->time_frame;
	if ((tftime.tftick != 0U) || (tftime.tfcount != 0U)) {
		S_D_CHECK_PROTECTION_ARRIVAL_TASK(tp_check_arrival_time(tftime, &p_tcb->tpacb, ARRIVAL_TASK) != FALSE);
	}

	if (p_tcb->tstat == SUSPENDED) {
		if ((make_active(p_tcb) != FALSE) && (callevel_stat == TCL_TASK)) {
			dispatch();
		}
	}
	else {
		S_D_CHECK_LIMIT(p_tcb->actcnt < p_tcb->p_tinib->maxact);

		p_tcb->actcnt += 1U;
	}

  d_exit_no_errorhook:
	x_nested_unlock_os_int();
	/* exit_no_errorhook: */
	LOG_ACTTSK_LEAVE(ercd);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
  d_exit_errorhook:
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.tskid = TaskID;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_ActivateTask);
	goto d_exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}

#endif /* TOPPERS_ActivateTask */

/*
 *  The end of the current task
 */
#ifdef TOPPERS_TerminateTask

StatusType
TerminateTask(void)
{
	StatusType ercd = E_OK;

	LOG_TERTSK_ENTER();
	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_TERMINATETASK);
	CHECK_RESOURCE(p_runtsk->p_lastrescb == NULL);

	x_nested_lock_os_int();
	/*
	 *  Since the release of internal resources such only lower the priority, 
	 * where it may not do anything
	 */

	suspend();

	LOG_TERTSK_LEAVE(E_OK);
	exit_and_dispatch();
	ASSERT_NO_REACHED;

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
	call_errorhook(ercd, OSServiceId_TerminateTask);
	x_nested_unlock_os_int();
#endif /* CFG_USE_ERRORHOOK */

	/* exit_no_errorhook: */
	LOG_TERTSK_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_TerminateTask */

/*
 *  Exit and start-up of the task of self-task
 */
#ifdef TOPPERS_ChainTask

StatusType
ChainTask(TaskType TaskID)
{
	/*
	 *  Although the initialization of ercd here originally is not required, 
	 * it is initialized to avoid compiler warnings
	 */
	StatusType	ercd = E_OK;
	TCB			*p_tcb;
	OSAPCB		*p_osapcb;
	TFTIME		tftime = {
		0U, 0U
	};

	LOG_CHNTSK_ENTER(TaskID);
	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_CHAINTASK);
	CHECK_RESOURCE(p_runtsk->p_lastrescb == NULL);
	CHECK_ID(TaskID < tnum_task);
	p_tcb = get_tcb(TaskID);
	CHECK_RIGHT(p_tcb->p_tinib->acsbtmp);

	p_osapcb = p_tcb->p_tinib->p_osapcb;
	x_nested_lock_os_int();

	/* Start checking the SOAP of the state of the task belongs to */
	D_CHECK_ACCESS((p_osapcb->osap_stat == APPLICATION_ACCESSIBLE) ||
				   ((p_osapcb->osap_stat == APPLICATION_RESTARTING) &&
					(p_osapcb == p_runosap)));

	tftime = p_tcb->p_tinib->time_frame;
	if ((tftime.tftick != 0U) || (tftime.tfcount != 0U)) {
		S_D_CHECK_PROTECTION_ARRIVAL_TASK(tp_check_arrival_time(tftime, &p_tcb->tpacb, ARRIVAL_TASK) != FALSE);
	}

	if (p_tcb == p_runtsk) {
		make_non_runnable();
		(void) make_active(p_runtsk);
	}
	else {
		/*
		 *  So as not to leave any side effects in case of an error, error checking, 
		 * it is necessary to perform in front of the task end processing
		 */
		S_D_CHECK_LIMIT((p_tcb->tstat == SUSPENDED)
						|| (p_tcb->actcnt < p_tcb->p_tinib->maxact));

		suspend();

		if (p_tcb->tstat == SUSPENDED) {
			(void) make_active(p_tcb);
		}
		else {
			p_tcb->actcnt += 1U;
		}
	}

	LOG_CHNTSK_LEAVE(E_OK);
	exit_and_dispatch();
	ASSERT_NO_REACHED;

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
  d_exit_errorhook:
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.tskid = TaskID;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_ChainTask);
#endif /* CFG_USE_ERRORHOOK */

  /* d_exit_no_errorhook: */
	x_nested_unlock_os_int();
	/* exit_no_errorhook: */
	LOG_CHNTSK_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_ChainTask */

/*
 *  Call of the scheduler
 */
#ifdef TOPPERS_Schedule

StatusType
Schedule(void)
{
	/*
	 *  Although the initialization of ercd here originally is not required, 
	 * it is initialized to avoid compiler warnings
	 */
	StatusType ercd = E_OK;

	LOG_SCHED_ENTER();
	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_SCHEDULE);
	CHECK_RESOURCE(p_runtsk->p_lastrescb == NULL);

	x_nested_lock_os_int();
	if (p_runtsk->p_tinib->inipri > nextpri) {
		p_runtsk->curpri = p_runtsk->p_tinib->inipri;
		preempt();
		dispatch();
		p_runtsk->curpri = p_runtsk->p_tinib->exepri;
	}

  d_exit_no_errorhook:
	x_nested_unlock_os_int();
	/* exit_no_errorhook: */
	LOG_SCHED_LEAVE(ercd);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
	call_errorhook(ercd, OSServiceId_Schedule);
	goto d_exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}

#endif /* TOPPERS_Schedule */

/*
 *  Reference of the task in the RUNNING state ID
 */
#ifdef TOPPERS_GetTaskID

StatusType
GetTaskID(TaskRefType TaskID)
{
	StatusType ercd = E_OK;

	LOG_GETTID_ENTER();
	CHECK_CALLEVEL(CALLEVEL_GETTASKID);
	CHECK_PARAM_POINTER(TaskID);
	CHECK_MEM_WRITE(TaskID, TaskType);
	*TaskID = (p_runtsk == NULL) ? INVALID_TASK : TSKID(p_runtsk);

  exit_no_errorhook:
	LOG_GETTID_LEAVE(ercd, TaskID);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.p_tskid = TaskID;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_GetTaskID);
	x_nested_unlock_os_int();
	goto exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}

#endif /* TOPPERS_GetTaskID */

/*
 *  Reference of the task state
 */
#ifdef TOPPERS_GetTaskState

StatusType
GetTaskState(TaskType TaskID, TaskStateRefType State)
{
	StatusType	ercd = E_OK;
	TCB			*p_tcb;
	OSAPCB		*p_osapcb;

	LOG_GETTST_ENTER(TaskID);
	CHECK_CALLEVEL(CALLEVEL_GETTASKSTATE);
	CHECK_ID(TaskID < tnum_task);
	CHECK_PARAM_POINTER(State);
	CHECK_MEM_WRITE(State, TaskStateType);
	p_tcb = get_tcb(TaskID);
	CHECK_RIGHT(p_tcb->p_tinib->acsbtmp);

	p_osapcb = p_tcb->p_tinib->p_osapcb;
	x_nested_lock_os_int();

	/* Start checking the OSAP of the state of the task belongs to */
	D_CHECK_ACCESS((p_osapcb->osap_stat == APPLICATION_ACCESSIBLE) ||
				   ((p_osapcb->osap_stat == APPLICATION_RESTARTING) &&
					(p_osapcb == p_runosap)));
	*State = (p_tcb == p_runtsk) ? RUNNING : p_tcb->tstat;

  d_exit_no_errorhook:
	x_nested_unlock_os_int();
	/* exit_no_errorhook: */
	LOG_GETTST_LEAVE(ercd, State);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
  d_exit_errorhook:
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.tskid = TaskID;
	_errorhook_par2.p_stat = State;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_GetTaskState);
	goto d_exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}

#endif /* TOPPERS_GetTaskState */

/*
 *  Starting the expiration processing dedicated task
 *
 *  Conditions: it is called by the OS interrupt disable state
 */
#ifdef TOPPERS_activate_task_action

StatusType
activate_task_action(OSAPCB *p_expire_osapcb, TaskType TaskID)
{
	StatusType	ercd = E_OK;
	TCB			*p_tcb;
	OSAPCB		*p_osapcb;
	TFTIME		tftime = {
		0U, 0U
	};

	LOG_ACTTSK_ENTER(TaskID);
	p_tcb = get_tcb(TaskID);

	tftime = p_tcb->p_tinib->time_frame;
	if ((tftime.tftick != 0U) || (tftime.tfcount != 0U)) {
		S_D_CHECK_PROTECTION_ARRIVAL_TASK(tp_check_arrival_time(tftime, &p_tcb->tpacb, ARRIVAL_TASK) != FALSE);
	}

	p_osapcb = p_tcb->p_tinib->p_osapcb;
	/* Check the status of the OSAP of the task belongs to OSAP and the start of expiration point belongs */
	D_CHECK_ACCESS((p_osapcb->osap_stat == APPLICATION_ACCESSIBLE) || (p_expire_osapcb == p_osapcb));

	if (p_tcb->tstat == SUSPENDED) {
		(void) make_active(p_tcb);
	}
	else {
		S_D_CHECK_LIMIT(p_tcb->actcnt < p_tcb->p_tinib->maxact);

		p_tcb->actcnt += 1U;
	}

  d_exit_no_errorhook:
	LOG_ACTTSK_LEAVE(ercd);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  d_exit_errorhook:
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.tskid = TaskID;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_ActivateTask);
	goto d_exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */

}

#endif /* TOPPERS_activate_task_action */
