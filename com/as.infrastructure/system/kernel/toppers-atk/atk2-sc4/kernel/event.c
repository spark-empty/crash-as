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
 *  $Id: event.c 504 2015-12-24 01:22:56Z witz-itoyo $
 */

/*
 *		Event Management module
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

#ifndef LOG_SETEVT_ENTER
#define LOG_SETEVT_ENTER(tskid, mask)
#endif /* LOG_SETEVT_ENTER */

#ifndef LOG_SETEVT_LEAVE
#define LOG_SETEVT_LEAVE(ercd)
#endif /* LOG_SETEVT_LEAVE */

#ifndef LOG_CLREVT_ENTER
#define LOG_CLREVT_ENTER(p_runtsk, mask)
#endif /* LOG_CLREVT_ENTER */

#ifndef LOG_CLREVT_LEAVE
#define LOG_CLREVT_LEAVE(ercd)
#endif /* LOG_CLREVT_LEAVE */

#ifndef LOG_GETEVT_ENTER
#define LOG_GETEVT_ENTER(tskid)
#endif /* LOG_GETEVT_ENTER */

#ifndef LOG_GETEVT_LEAVE
#define LOG_GETEVT_LEAVE(ercd, tskid, p_mask)
#endif /* LOG_GETEVT_LEAVE */

#ifndef LOG_WAIEVT_ENTER
#define LOG_WAIEVT_ENTER(p_runtsk, mask)
#endif /* LOG_WAIEVT_ENTER */

#ifndef LOG_WAIEVT_LEAVE
#define LOG_WAIEVT_LEAVE(ercd)
#endif /* LOG_WAIEVT_LEAVE */

/*
 *  Event set
 */
#ifdef TOPPERS_SetEvent

StatusType
SetEvent(TaskType TaskID, EventMaskType Mask)
{
	StatusType		ercd = E_OK;
	TCB				*p_tcb;
	OSAPCB			*p_osapcb;
	EventMaskType	evt = 0U;
	TFTIME			tftime = {
		0U, 0U
	};

	LOG_SETEVT_ENTER(TaskID, Mask);
	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_SETEVENT);
	CHECK_ID(TaskID < tnum_task);
	CHECK_ACCESS(TaskID < tnum_exttask);
	p_tcb = get_tcb(TaskID);
	CHECK_RIGHT(p_tcb->p_tinib->acsbtmp);

	p_osapcb = p_tcb->p_tinib->p_osapcb;
	x_nested_lock_os_int();

	/* Check OSAP of state of the task affiliation */
	D_CHECK_ACCESS((p_osapcb->osap_stat == APPLICATION_ACCESSIBLE) ||
				   ((p_osapcb->osap_stat == APPLICATION_RESTARTING) &&
					(p_osapcb == p_runosap)));
	D_CHECK_STATE(p_tcb->tstat != SUSPENDED);

	evt = p_tcb->curevt | Mask;
	if ((evt & p_tcb->waievt) != EVTMASK_NONE) {
		tftime = p_tcb->p_tinib->time_frame;
		if ((tftime.tftick != 0U) || (tftime.tfcount != 0U)) {
			S_D_CHECK_PROTECTION_ARRIVAL_TASK(tp_check_arrival_time(tftime, &p_tcb->tpacb, ARRIVAL_TASK) != FALSE);
		}

		p_tcb->curevt = evt;
		p_tcb->waievt = EVTMASK_NONE;
		if ((make_runnable(p_tcb) != FALSE) && (callevel_stat == TCL_TASK)) {
			dispatch();
		}
	}
	else {
		p_tcb->curevt = evt;
	}

  d_exit_no_errorhook:
	x_nested_unlock_os_int();
	/* exit_no_errorhook: */
	LOG_SETEVT_LEAVE(ercd);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
  d_exit_errorhook:
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.tskid = TaskID;
	_errorhook_par2.mask = Mask;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_SetEvent);
	goto d_exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}

#endif /* TOPPERS_SetEvent */

/*
 *  Events Clear
 */
#ifdef TOPPERS_ClearEvent

StatusType
ClearEvent(EventMaskType Mask)
{
	StatusType ercd = E_OK;

	LOG_CLREVT_ENTER(p_runtsk, Mask);
	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_CLEAREVENT);
	CHECK_ACCESS(TSKID(p_runtsk) < tnum_exttask);

	x_nested_lock_os_int();
	p_runtsk->curevt &= ~Mask;

  d_exit_no_errorhook:
	x_nested_unlock_os_int();
	/* exit_no_errorhook: */
	LOG_CLREVT_LEAVE(ercd);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.mask = Mask;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_ClearEvent);
	goto d_exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}

#endif /* TOPPERS_ClearEvent */

/*
 *  Events of state reference
 */
#ifdef TOPPERS_GetEvent

StatusType
GetEvent(TaskType TaskID, EventMaskRefType Event)
{
	StatusType	ercd = E_OK;
	TCB			*p_tcb;
	OSAPCB		*p_osapcb;

	LOG_GETEVT_ENTER(TaskID);
	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_GETEVENT);
	CHECK_ID(TaskID < tnum_task);
	CHECK_ACCESS(TaskID < tnum_exttask);
	CHECK_PARAM_POINTER(Event);
	CHECK_MEM_WRITE(Event, EventMaskType);
	p_tcb = get_tcb(TaskID);
	CHECK_RIGHT(p_tcb->p_tinib->acsbtmp);

	p_osapcb = p_tcb->p_tinib->p_osapcb;
	x_nested_lock_os_int();

	/* Check OSAP of state of the task affiliation */
	D_CHECK_ACCESS((p_osapcb->osap_stat == APPLICATION_ACCESSIBLE) ||
				   ((p_osapcb->osap_stat == APPLICATION_RESTARTING) &&
					(p_osapcb == p_runosap)));
	/* It is an error if the target task is in hibernation */
	D_CHECK_STATE((p_tcb->tstat != SUSPENDED) || (p_tcb == p_runtsk));

	*Event = p_tcb->curevt;

  d_exit_no_errorhook:
	x_nested_unlock_os_int();
	/* exit_no_errorhook: */
	LOG_GETEVT_LEAVE(ercd, TaskID, Event);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
  d_exit_errorhook:
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.tskid = TaskID;
	_errorhook_par2.p_mask = Event;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_GetEvent);
	goto d_exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}

#endif /* TOPPERS_GetEvent */

/*
 *  Event waiting
 */
#ifdef TOPPERS_WaitEvent

StatusType
WaitEvent(EventMaskType Mask)
{
	StatusType	ercd = E_OK;
	TFTIME		tftime = {
		0U, 0U
	};

	LOG_WAIEVT_ENTER(p_runtsk, Mask);
	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_WAITEVENT);
	CHECK_ACCESS(TSKID(p_runtsk) < tnum_exttask);
	CHECK_RESOURCE(p_runtsk->p_lastrescb == NULL);

	x_nested_lock_os_int();
	if ((p_runtsk->curevt & Mask) == EVTMASK_NONE) {
		p_runtsk->curpri = p_runtsk->p_tinib->inipri;
		p_runtsk->tstat = WAITING;
		LOG_TSKSTAT(p_runtsk);
		p_runtsk->waievt = Mask;
		make_non_runnable();
		dispatch();
		p_runtsk->curpri = p_runtsk->p_tinib->exepri;
	}
	else {
		tftime = p_runtsk->p_tinib->time_frame;
		if ((tftime.tftick != 0U) || (tftime.tfcount != 0U)) {
			S_D_CHECK_PROTECTION_ARRIVAL_TASK(tp_check_arrival_time(tftime, &p_runtsk->tpacb, ARRIVAL_TASK) != FALSE);
		}
		if (p_runtsk->p_tinib->execution_budget != 0U) {
			p_runtsk->remaining_execution = p_runtsk->p_tinib->execution_budget;
			tp_start_timer(p_runtsk->remaining_execution);
		}
	}

  d_exit_no_errorhook:
	x_nested_unlock_os_int();
	/* exit_no_errorhook: */
	LOG_WAIEVT_LEAVE(ercd);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
  d_exit_errorhook:
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.mask = Mask;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_WaitEvent);
	goto d_exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}

#endif /* TOPPERS_WaitEvent */

/*
 *  Set of expiration processing dedicated event
 *
 *  Conditions: it is called by the OS interrupt disable state
 */
#ifdef TOPPERS_set_event_action

StatusType
set_event_action(OSAPCB *p_expire_osapcb, TaskType TaskID, EventMaskType Mask)
{
	StatusType		ercd = E_OK;
	TCB				*p_tcb;
	OSAPCB			*p_osapcb;
	EventMaskType	evt = 0U;
	TFTIME			tftime = {
		0U, 0U
	};

	LOG_SETEVT_ENTER(TaskID, Mask);
	p_tcb = get_tcb(TaskID);

	p_osapcb = p_tcb->p_tinib->p_osapcb;
	/* Check the status of the expiration point belongs OSAP and set events target task affiliation of OSAP */
	D_CHECK_ACCESS((p_osapcb->osap_stat == APPLICATION_ACCESSIBLE) || (p_expire_osapcb == p_osapcb));
	D_CHECK_STATE(p_tcb->tstat != SUSPENDED);

	evt = p_tcb->curevt | Mask;
	if ((evt & p_tcb->waievt) != EVTMASK_NONE) {
		tftime = p_tcb->p_tinib->time_frame;
		if ((tftime.tftick != 0U) || (tftime.tfcount != 0U)) {
			S_D_CHECK_PROTECTION_ARRIVAL_TASK(tp_check_arrival_time(tftime, &p_tcb->tpacb, ARRIVAL_TASK) != FALSE);
		}

		p_tcb->curevt = evt;
		p_tcb->waievt = EVTMASK_NONE;
		(void) make_runnable(p_tcb);
	}
	else {
		p_tcb->curevt = evt;
	}

  d_exit_no_errorhook:
	LOG_SETEVT_LEAVE(ercd);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  d_exit_errorhook:
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.tskid = TaskID;
	_errorhook_par2.mask = Mask;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_SetEvent);
	goto d_exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}

#endif /* TOPPERS_set_event_action */
