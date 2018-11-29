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
 *  $Id: alarm.c 504 2015-12-24 01:22:56Z witz-itoyo $
 */

/*
 *		Alarm management module
 */

#include "kernel_impl.h"
#include "check.h"
#include "alarm.h"

/*
 *  The default definition of the trace log macro
 */
#ifndef LOG_GETALB_ENTER
#define LOG_GETALB_ENTER(almid)
#endif /* LOG_GETALB_ENTER */

#ifndef LOG_GETALB_LEAVE
#define LOG_GETALB_LEAVE(ercd, info)
#endif /* LOG_GETALB_LEAVE */

#ifndef LOG_GETALM_ENTER
#define LOG_GETALM_ENTER(almid)
#endif /* LOG_GETALM_ENTER */

#ifndef LOG_GETALM_LEAVE
#define LOG_GETALM_LEAVE(ercd, p_tick)
#endif /* LOG_GETALM_LEAVE */

#ifndef LOG_SETREL_ENTER
#define LOG_SETREL_ENTER(almid, incr, cycle)
#endif /* LOG_SETREL_ENTER */

#ifndef LOG_SETREL_LEAVE
#define LOG_SETREL_LEAVE(ercd)
#endif /* LOG_SETREL_LEAVE */

#ifndef LOG_SETABS_ENTER
#define LOG_SETABS_ENTER(almid, start, cycle)
#endif /* LOG_SETABS_ENTER */

#ifndef LOG_SETABS_LEAVE
#define LOG_SETABS_LEAVE(ercd)
#endif /* LOG_SETABS_LEAVE */

#ifndef LOG_CANALM_ENTER
#define LOG_CANALM_ENTER(almid)
#endif /* LOG_CANALM_ENTER */

#ifndef LOG_CANALM_LEAVE
#define LOG_CANALM_LEAVE(ercd)
#endif /* LOG_CANALM_LEAVE */

#ifndef LOG_ALM_ENTER
#define LOG_ALM_ENTER(p_cntexpinfo)
#endif /* LOG_ALM_ENTER */

#ifndef LOG_ALM_LEAVE
#define LOG_ALM_LEAVE(p_cntexpinfo)
#endif /* LOG_ALM_LEAVE */

/*
 *  Initialization of alarm function
 */
#ifdef TOPPERS_alarm_initialize

void
alarm_initialize(void)
{
	AlarmType	i;
	ALMCB		*p_almcb;

	for (i = 0U; i < tnum_alarm; i++) {
		p_almcb = &(almcb_table[i]);

		p_almcb->p_alminib = &(alminib_table[i]);
		(p_almcb->cntexpinfo).expirefunc = &alarm_expire;
		if ((p_almcb->p_alminib->autosta & ((AppModeType) 1 << appmodeid)) != APPMODE_NONE) {
			if (p_almcb->p_alminib->actatr == ABSOLUTE) {
				/*
				 *  If the start-up expiration time of absolute time of 0, the 0 of 
				 * the timing of the next cycle (already taken into account in get_abstick)
				 */
				(p_almcb->cntexpinfo).expiretick =
					get_abstick(p_almcb->p_alminib->p_cntcb, p_almcb->p_alminib->almval);
			}
			else {
				/* Start-up of the relative time */
				(p_almcb->cntexpinfo).expiretick =
					get_reltick(p_almcb->p_alminib->p_cntcb, p_almcb->p_alminib->almval);
			}
			p_almcb->cycle = p_almcb->p_alminib->cycle;

			insert_cnt_expr_que(&(p_almcb->cntexpinfo), p_almcb->p_alminib->p_cntcb);
		}
		else {
			queue_initialize(&(p_almcb->cntexpinfo.cntexpque));
		}
	}
}

#endif /* TOPPERS_alarm_initialize */

/*
 *  Acquisition of alarm information
 */
#ifdef TOPPERS_GetAlarmBase

StatusType
GetAlarmBase(AlarmType AlarmID, AlarmBaseRefType Info)
{
	StatusType	ercd = E_OK;
	ALMCB		*p_almcb;
	CNTCB		*p_cntcb;
	OSAPCB		*p_osapcb;

	LOG_GETALB_ENTER(AlarmID);
	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_GETALARMBASE);
	CHECK_ID(AlarmID < tnum_alarm);
	CHECK_PARAM_POINTER(Info);
	CHECK_MEM_WRITE(Info, AlarmBaseType);
	p_almcb = get_almcb(AlarmID);
	CHECK_RIGHT(p_almcb->p_alminib->acsbtmp);
	p_cntcb = p_almcb->p_alminib->p_cntcb;

	p_osapcb = p_almcb->p_alminib->p_osapcb;
	x_nested_lock_os_int();

	/* Check OSAP state of alarm affiliation */
	D_CHECK_ACCESS((p_osapcb->osap_stat == APPLICATION_ACCESSIBLE) ||
				   ((p_osapcb->osap_stat == APPLICATION_RESTARTING) &&
					(p_osapcb == p_runosap)));

	Info->maxallowedvalue = p_cntcb->p_cntinib->maxval;
	Info->ticksperbase = p_cntcb->p_cntinib->tickbase;
	Info->mincycle = p_cntcb->p_cntinib->mincyc;

  d_exit_no_errorhook:
	x_nested_unlock_os_int();
	/* exit_no_errorhook: */
	LOG_GETALB_LEAVE(ercd, Info);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
  d_exit_errorhook:
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.almid = AlarmID;
	_errorhook_par2.p_info = Info;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_GetAlarmBase);
	goto d_exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}

#endif /* TOPPERS_GetAlarmBase */

/*
 *  State reference of alarm
 */
#ifdef TOPPERS_GetAlarm

StatusType
GetAlarm(AlarmType AlarmID, TickRefType Tick)
{
	StatusType	ercd = E_OK;
	TickType	curval;
	ALMCB		*p_almcb;
	CNTCB		*p_cntcb;
	OSAPCB		*p_osapcb;

	LOG_GETALM_ENTER(AlarmID);
	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_GETALARM);
	CHECK_ID(AlarmID < tnum_alarm);
	CHECK_PARAM_POINTER(Tick);
	CHECK_MEM_WRITE(Tick, TickType);
	p_almcb = get_almcb(AlarmID);
	CHECK_RIGHT(p_almcb->p_alminib->acsbtmp);
	p_cntcb = p_almcb->p_alminib->p_cntcb;

	p_osapcb = p_almcb->p_alminib->p_osapcb;
	x_nested_lock_os_int();
	/* Check OSAP state of alarm affiliation */
	D_CHECK_ACCESS((p_osapcb->osap_stat == APPLICATION_ACCESSIBLE) ||
				   ((p_osapcb->osap_stat == APPLICATION_RESTARTING) &&
					(p_osapcb == p_runosap)));

	S_D_CHECK_NOFUNC(queue_empty(&(p_almcb->cntexpinfo.cntexpque)) == FALSE);

	/*
	 *  Get the current value of the counter
	 *  In the case of hardware counter, there is a possibility that has already been completed
	 */
	curval = get_curval(p_cntcb, CNTID(p_cntcb));

	*Tick = diff_tick(p_almcb->cntexpinfo.expiretick, curval, p_cntcb->p_cntinib->maxval2);

  d_exit_no_errorhook:
	x_nested_unlock_os_int();
	/* exit_no_errorhook: */
	LOG_GETALM_LEAVE(ercd, Tick);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
  d_exit_errorhook:
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.almid = AlarmID;
	_errorhook_par2.p_tick = Tick;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_GetAlarm);
	goto d_exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}

#endif /* TOPPERS_GetAlarm */

/*
 *  Alarm setting of (relative value)
 */
#ifdef TOPPERS_SetRelAlarm

StatusType
SetRelAlarm(AlarmType AlarmID, TickType increment, TickType cycle)
{
	StatusType	ercd = E_OK;
	TickType	maxval;
	ALMCB		*p_almcb;
	CNTCB		*p_cntcb;
	OSAPCB		*p_osapcb;

	LOG_SETREL_ENTER(AlarmID, increment, cycle);
	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_SETRELALARM);
	CHECK_ID(AlarmID < tnum_alarm);
	p_almcb = get_almcb(AlarmID);
	CHECK_RIGHT(p_almcb->p_alminib->acsbtmp);
	p_cntcb = p_almcb->p_alminib->p_cntcb;

	maxval = p_cntcb->p_cntinib->maxval;
	CHECK_VALUE((0U < increment) && (increment <= maxval));
	CHECK_VALUE((cycle == 0U)
				|| ((p_cntcb->p_cntinib->mincyc <= cycle) && (cycle <= maxval)));

	p_osapcb = p_almcb->p_alminib->p_osapcb;
	x_nested_lock_os_int();
	/* Check OSAP state of alarm affiliation */
	D_CHECK_ACCESS((p_osapcb->osap_stat == APPLICATION_ACCESSIBLE) ||
				   ((p_osapcb->osap_stat == APPLICATION_RESTARTING) &&
					(p_osapcb == p_runosap)));

	S_D_CHECK_STATE(queue_empty(&(p_almcb->cntexpinfo.cntexpque)) != FALSE);

	p_almcb->cntexpinfo.expiretick = get_reltick(p_cntcb, increment);
	p_almcb->cycle = cycle;

	insert_cnt_expr_que(&(p_almcb->cntexpinfo), p_cntcb);

  d_exit_no_errorhook:
	x_nested_unlock_os_int();
	/* exit_no_errorhook: */
	LOG_SETREL_LEAVE(ercd);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
  d_exit_errorhook:
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.almid = AlarmID;
	_errorhook_par2.incr = increment;
	_errorhook_par3.cycle = cycle;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_SetRelAlarm);
	goto d_exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}

#endif /* TOPPERS_SetRelAlarm */

/*
 *  Alarm setting (absolute value)
 */
#ifdef TOPPERS_SetAbsAlarm

StatusType
SetAbsAlarm(AlarmType AlarmID, TickType start, TickType cycle)
{
	StatusType	ercd = E_OK;
	TickType	maxval;
	ALMCB		*p_almcb;
	CNTCB		*p_cntcb;
	OSAPCB		*p_osapcb;

	LOG_SETABS_ENTER(AlarmID, start, cycle);
	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_SETABSALARM);
	CHECK_ID(AlarmID < tnum_alarm);
	p_almcb = get_almcb(AlarmID);
	CHECK_RIGHT(p_almcb->p_alminib->acsbtmp);
	p_cntcb = p_almcb->p_alminib->p_cntcb;

	maxval = p_cntcb->p_cntinib->maxval;
	CHECK_VALUE(start <= maxval);
	CHECK_VALUE((cycle == 0U)
				|| ((p_cntcb->p_cntinib->mincyc <= cycle) && (cycle <= maxval)));

	p_osapcb = p_almcb->p_alminib->p_osapcb;
	x_nested_lock_os_int();
	/* Check OSAP state of alarm affiliation */
	D_CHECK_ACCESS((p_osapcb->osap_stat == APPLICATION_ACCESSIBLE) ||
				   ((p_osapcb->osap_stat == APPLICATION_RESTARTING) &&
					(p_osapcb == p_runosap)));

	S_D_CHECK_STATE(queue_empty(&(p_almcb->cntexpinfo.cntexpque)) != FALSE);

	p_almcb->cntexpinfo.expiretick = get_abstick(p_cntcb, start);
	p_almcb->cycle = cycle;

	insert_cnt_expr_que(&(p_almcb->cntexpinfo), p_cntcb);

  d_exit_no_errorhook:
	x_nested_unlock_os_int();
	/* exit_no_errorhook: */
	LOG_SETABS_LEAVE(ercd);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
  d_exit_errorhook:
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.almid = AlarmID;
	_errorhook_par2.start = start;
	_errorhook_par3.cycle = cycle;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_SetAbsAlarm);
	goto d_exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}

#endif /* TOPPERS_SetAbsAlarm */

/*
 *  Cancellation of alarm
 */
#ifdef TOPPERS_CancelAlarm

StatusType
CancelAlarm(AlarmType AlarmID)
{
	StatusType	ercd = E_OK;
	ALMCB		*p_almcb;
	OSAPCB		*p_osapcb;

	LOG_CANALM_ENTER(AlarmID);
	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_CANCELALARM);
	CHECK_ID(AlarmID < tnum_alarm);
	p_almcb = get_almcb(AlarmID);
	CHECK_RIGHT(p_almcb->p_alminib->acsbtmp);

	p_osapcb = p_almcb->p_alminib->p_osapcb;
	x_nested_lock_os_int();
	/* Check OSAP state of alarm affiliation */
	D_CHECK_ACCESS((p_osapcb->osap_stat == APPLICATION_ACCESSIBLE) ||
				   ((p_osapcb->osap_stat == APPLICATION_RESTARTING) &&
					(p_osapcb == p_runosap)));

	S_D_CHECK_NOFUNC(queue_empty(&(p_almcb->cntexpinfo.cntexpque)) == FALSE);

	delete_cnt_expr_que(&(p_almcb->cntexpinfo), p_almcb->p_alminib->p_cntcb);

  d_exit_no_errorhook:
	x_nested_unlock_os_int();
	/* exit_no_errorhook: */
	LOG_CANALM_LEAVE(ercd);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
  d_exit_errorhook:
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.almid = AlarmID;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_CancelAlarm);
	goto d_exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}

#endif /* TOPPERS_CancelAlarm */

/*
 *  Alarm expiration action processing function
 */
#ifdef TOPPERS_alarm_expire

void
alarm_expire(CNTEXPINFO *p_cntexpinfo, const CNTCB *p_cntcb)
{
	ALMCB	*p_almcb;
	OSAPCB	*p_runosap_saved;

	p_almcb = (ALMCB *) p_cntexpinfo;

	/* Re-insertion into the counter expiration queue (in the case of a cycle alarm) */
	if (p_almcb->cycle > 0U) {
		p_cntexpinfo->expiretick = add_tick(p_cntexpinfo->expiretick, p_almcb->cycle,
											p_cntcb->p_cntinib->maxval2);
		insert_cnt_expr_que(p_cntexpinfo, (CNTCB *) p_cntcb);
	}

	LOG_ALM_ENTER(p_almcb);

	p_runosap_saved = p_runosap;
	p_runosap = p_almcb->p_alminib->p_osapcb;

	/* Call of alarm expiration action */
	(p_almcb->p_alminib->action)();

	p_runosap = p_runosap_saved;

	LOG_ALM_LEAVE(p_almcb);
}

#endif /* TOPPERS_alarm_expire */

/*
 *  Forced termination of OSAP belongs alarm
 */
#ifdef TOPPERS_force_term_osap_alarm

void
force_term_osap_alarm(OSAPCB *p_osapcb)
{
	/* Turn off from the expiration queue of counter */
	AlarmType	i;
	ALMCB		*p_almcb;

	for (i = 0U; i < tnum_alarm; i++) {
		if (alminib_table[i].p_osapcb == p_osapcb) {
			p_almcb = &almcb_table[i];
			/*
			 *  It wants to remove from the expiration queue
			 *  It has to be performed before the initialization
			 */
			delete_cnt_expr_que(&(p_almcb->cntexpinfo), p_almcb->p_alminib->p_cntcb);
			p_almcb->cycle = 0U;
		}
	}
}

#endif /* TOPPERS_force_term_osap_alarm */
