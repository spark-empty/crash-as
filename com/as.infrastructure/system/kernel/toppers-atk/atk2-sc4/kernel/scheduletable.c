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
 *  $Id: scheduletable.c 504 2015-12-24 01:22:56Z witz-itoyo $
 */

/*
 *		Schedule table management module
 */

#include "kernel_impl.h"
#include "check.h"
#include "scheduletable.h"

/*
 *  The default definition of the trace log macro
 */
#ifndef LOG_STASCHTBLREL_ENTER
#define LOG_STASCHTBLREL_ENTER(schtblid, offset)
#endif /* LOG_STASCHTBLREL_ENTER */

#ifndef LOG_STASCHTBLREL_LEAVE
#define LOG_STASCHTBLREL_LEAVE(ercd)
#endif /* LOG_STASCHTBLREL_LEAVE */

#ifndef LOG_STASCHTBLABS_ENTER
#define LOG_STASCHTBLABS_ENTER(schtblid, start)
#endif /* LOG_STASCHTBLABS_ENTER */

#ifndef LOG_STASCHTBLABS_LEAVE
#define LOG_STASCHTBLABS_LEAVE(ercd)
#endif /* LOG_STASCHTBLABS_LEAVE */

#ifndef LOG_STPSCHTBL_ENTER
#define LOG_STPSCHTBL_ENTER(schtblid)
#endif /* LOG_STPSCHTBL_ENTER */

#ifndef LOG_STPSCHTBL_LEAVE
#define LOG_STPSCHTBL_LEAVE(ercd)
#endif /* LOG_STPSCHTBL_LEAVE */

#ifndef LOG_NXTSCHTBL_ENTER
#define LOG_NXTSCHTBL_ENTER(from, to)
#endif /* LOG_NXTSCHTBL_ENTER */

#ifndef LOG_NXTSCHTBL_LEAVE
#define LOG_NXTSCHTBL_LEAVE(ercd)
#endif /* LOG_NXTSCHTBL_LEAVE */

#ifndef LOG_GETSCHTBLST_ENTER
#define LOG_GETSCHTBLST_ENTER(schtblid)
#endif /* LOG_GETSCHTBLST_ENTER */

#ifndef LOG_GETSCHTBLST_LEAVE
#define LOG_GETSCHTBLST_LEAVE(ercd, p_status)
#endif /* LOG_GETSCHTBLST_LEAVE */

#ifndef LOG_SCHTBL_ENTER
#define LOG_SCHTBL_ENTER(p_schtblcb)
#endif /* LOG_SCHTBL_ENTER */

#ifndef LOG_SCHTBL_LEAVE
#define LOG_SCHTBL_LEAVE(p_schtblcb)
#endif /* LOG_SCHTBL_LEAVE */

/*
 *  Initialization of the schedule table object
 */
#ifdef TOPPERS_schtbl_initialize

void
schtbl_initialize(void)
{
	ScheduleTableType	i;
	SCHTBLCB			*p_schtblcb;
	CNTCB				*p_cntcb;
	TickType			staval;

	for (i = 0U; i < tnum_scheduletable; i++) {
		p_schtblcb = &(schtblcb_table[i]);
		p_schtblcb->p_schtblinib = &(schtblinib_table[i]);

		/*
		 *  When in the STOPPED state, p_nextschtblcb, when RUNNING, 
		 * the NEXT state to initialize the p_prevschtblcb, to initialize the expptindex
		 */
		p_schtblcb->p_nextschtblcb = NULL;
		p_schtblcb->p_prevschtblcb = NULL;
		(p_schtblcb->cntexpinfo).expirefunc = &schtbl_expire;

		if ((p_schtblcb->p_schtblinib->autosta & ((AppModeType) 1 << appmodeid)) != APPMODE_NONE) {
			if (is_implschtbl(i)) {
				p_schtblcb->status = SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS;
			}
			else {
				p_schtblcb->status = SCHEDULETABLE_RUNNING;
			}
			p_schtblcb->expptindex = EXPPTINDEX_INITIAL;

			p_cntcb = p_schtblcb->p_schtblinib->p_cntcb;
			staval = p_schtblcb->p_schtblinib->staval;
			if (p_schtblcb->p_schtblinib->actatr == ABSOLUTE) {
				/*
				 *  Start-up of absolute time
				 *  If the expiration time is 0, the 0 of the timing of the next period
				 * (Already taken into account in get_abstick)
				 */
				(p_schtblcb->cntexpinfo).expiretick = get_abstick(p_cntcb, staval);
			}
			else {
				/* Start-up of the relative time */
				(p_schtblcb->cntexpinfo).expiretick = get_reltick(p_cntcb, staval);
			}

			insert_cnt_expr_que(&(p_schtblcb->cntexpinfo), p_cntcb);
		}
		else {
			p_schtblcb->status = SCHEDULETABLE_STOPPED;

			queue_initialize(&(p_schtblcb->cntexpinfo.cntexpque));
		}
	}
}

#endif /* TOPPERS_schtbl_initialize */

/*
 *  The start of the specified schedule table (relative time)
 */
#ifdef TOPPERS_StartScheduleTableRel

StatusType
StartScheduleTableRel(ScheduleTableType ScheduleTableID, TickType Offset)
{
	StatusType	ercd = E_OK;
	SCHTBLCB	*p_schtblcb;
	CNTCB		*p_cntcb;
	OSAPCB		*p_osapcb;

	LOG_STASCHTBLREL_ENTER(ScheduleTableID, Offset);
	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_STARTSCHEDULETABLEREL);
	CHECK_ID(ScheduleTableID < tnum_scheduletable);
	CHECK_ID(ScheduleTableID >= tnum_implscheduletable);

	p_schtblcb = get_schtblcb(ScheduleTableID);
	CHECK_RIGHT(p_schtblcb->p_schtblinib->acsbtmp);

	p_cntcb = p_schtblcb->p_schtblinib->p_cntcb;
	CHECK_VALUE((Offset != 0U) &&
				((p_cntcb->p_cntinib->maxval - p_schtblcb->p_schtblinib->p_exppt->offset) >= Offset));

	p_osapcb = p_schtblcb->p_schtblinib->p_osapcb;
	x_nested_lock_os_int();

	/* Start checking the OSAP state of the schedule table belongs to */
	D_CHECK_ACCESS((p_osapcb->osap_stat == APPLICATION_ACCESSIBLE) ||
				   ((p_osapcb->osap_stat == APPLICATION_RESTARTING) &&
					(p_osapcb == p_runosap)));
	S_D_CHECK_STATE(p_schtblcb->status == SCHEDULETABLE_STOPPED);

	p_schtblcb->status = SCHEDULETABLE_RUNNING;
	p_schtblcb->expptindex = EXPPTINDEX_INITIAL;
	p_schtblcb->cntexpinfo.expiretick = get_reltick(p_cntcb, Offset);

	insert_cnt_expr_que(&(p_schtblcb->cntexpinfo), p_cntcb);

  d_exit_no_errorhook:
	x_nested_unlock_os_int();
	/* exit_no_errorhook: */
	LOG_STASCHTBLREL_LEAVE(ercd);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
  d_exit_errorhook:
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.schtblid = ScheduleTableID;
	_errorhook_par2.offset = Offset;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_StartScheduleTableRel);
	goto d_exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}

#endif /* TOPPERS_StartScheduleTableRel */

/*
 *  The start of the specified schedule table (absolute time)
 */
#ifdef TOPPERS_StartScheduleTableAbs

StatusType
StartScheduleTableAbs(ScheduleTableType ScheduleTableID, TickType Start)
{
	StatusType	ercd = E_OK;
	SCHTBLCB	*p_schtblcb;
	CNTCB		*p_cntcb;
	OSAPCB		*p_osapcb;

	LOG_STASCHTBLABS_ENTER(ScheduleTableID, Start);
	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_STARTSCHEDULETABLEABS);
	CHECK_ID(ScheduleTableID < tnum_scheduletable);

	p_schtblcb = get_schtblcb(ScheduleTableID);
	CHECK_RIGHT(p_schtblcb->p_schtblinib->acsbtmp);

	p_cntcb = p_schtblcb->p_schtblinib->p_cntcb;
	CHECK_VALUE(p_cntcb->p_cntinib->maxval >= Start);

	p_osapcb = p_schtblcb->p_schtblinib->p_osapcb;
	x_nested_lock_os_int();

	/* Start checking the OSAP state of the schedule table belongs to */
	D_CHECK_ACCESS((p_osapcb->osap_stat == APPLICATION_ACCESSIBLE) ||
				   ((p_osapcb->osap_stat == APPLICATION_RESTARTING) &&
					(p_osapcb == p_runosap)));
	S_D_CHECK_STATE(p_schtblcb->status == SCHEDULETABLE_STOPPED);

	/* In the case of implicit synchronization, it operates in synchronous operation state */
	if (is_implschtbl(ScheduleTableID)) {
		p_schtblcb->status = SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS;
	}
	else {
		p_schtblcb->status = SCHEDULETABLE_RUNNING;
	}
	p_schtblcb->expptindex = EXPPTINDEX_INITIAL;
	p_schtblcb->cntexpinfo.expiretick = get_abstick(p_cntcb, Start);

	insert_cnt_expr_que(&(p_schtblcb->cntexpinfo), p_cntcb);

  d_exit_no_errorhook:
	x_nested_unlock_os_int();
	/* exit_no_errorhook: */
	LOG_STASCHTBLABS_LEAVE(ercd);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
  d_exit_errorhook:
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.schtblid = ScheduleTableID;
	_errorhook_par2.start = Start;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_StartScheduleTableAbs);
	goto d_exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}

#endif /* TOPPERS_StartScheduleTableAbs */

/*
 *  Stop of the specified schedule table
 */
#ifdef TOPPERS_StopScheduleTable

StatusType
StopScheduleTable(ScheduleTableType ScheduleTableID)
{
	StatusType	ercd = E_OK;
	SCHTBLCB	*p_schtblcb, *p_nextcb;
	OSAPCB		*p_osapcb;

	LOG_STPSCHTBL_ENTER(ScheduleTableID);
	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_STOPSCHEDULETABLE);
	CHECK_ID(ScheduleTableID < tnum_scheduletable);

	p_schtblcb = get_schtblcb(ScheduleTableID);

	CHECK_RIGHT(p_schtblcb->p_schtblinib->acsbtmp);

	p_osapcb = p_schtblcb->p_schtblinib->p_osapcb;
	x_nested_lock_os_int();

	/* Start checking the OSAP state of the schedule table belongs to */
	D_CHECK_ACCESS((p_osapcb->osap_stat == APPLICATION_ACCESSIBLE) ||
				   ((p_osapcb->osap_stat == APPLICATION_RESTARTING) &&
					(p_osapcb == p_runosap)));
	S_D_CHECK_NOFUNC(p_schtblcb->status != SCHEDULETABLE_STOPPED);

	/*
	 *  If the specified schedule table is SCHEDULETABLE_NEXT, 
	 * from the schedule table that yourself to Next, remove yourself
	 */
	if (p_schtblcb->status == SCHEDULETABLE_NEXT) {
		p_schtblcb->p_prevschtblcb->p_nextschtblcb = NULL;
		p_schtblcb->p_prevschtblcb = NULL;
	}
	else {
		/*
		 *  If the Next schedule table exists, 
		 * to cancel the reservation of Next schedule table
		 */
		p_nextcb = p_schtblcb->p_nextschtblcb;
		if (p_nextcb != NULL) {
			p_nextcb->status = SCHEDULETABLE_STOPPED;
			p_nextcb->p_prevschtblcb = NULL;
			p_schtblcb->p_nextschtblcb = NULL;
		}

		/* Remove already registered expiration processing from the counter expiration queue */
		delete_cnt_expr_que(&(p_schtblcb->cntexpinfo),
							p_schtblcb->p_schtblinib->p_cntcb);
	}

	p_schtblcb->status = SCHEDULETABLE_STOPPED;

  d_exit_no_errorhook:
	x_nested_unlock_os_int();
	/* exit_no_errorhook: */
	LOG_STPSCHTBL_LEAVE(ercd);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
  d_exit_errorhook:
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.schtblid = ScheduleTableID;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_StopScheduleTable);
	goto d_exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}
#endif /* TOPPERS_StopScheduleTable */

/*
 *  Switching of schedule table
 */
#ifdef TOPPERS_NextScheduleTable

StatusType
NextScheduleTable(ScheduleTableType ScheduleTableID_From,
				  ScheduleTableType ScheduleTableID_To)
{
	StatusType	ercd = E_OK;
	SCHTBLCB	*p_curcb, *p_nextcb;
	OSAPCB		*p_osapcb;

	LOG_NXTSCHTBL_ENTER(ScheduleTableID_From, ScheduleTableID_To);
	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_NEXTSCHEDULETABLE);
	CHECK_ID(ScheduleTableID_From < tnum_scheduletable);
	CHECK_ID(ScheduleTableID_To < tnum_scheduletable);
	CHECK_ID((ScheduleTableID_From < tnum_implscheduletable) ==
			 (ScheduleTableID_To < tnum_implscheduletable));

	p_curcb = get_schtblcb(ScheduleTableID_From);
	p_nextcb = get_schtblcb(ScheduleTableID_To);

	CHECK_RIGHT(p_curcb->p_schtblinib->acsbtmp);
	CHECK_RIGHT(p_nextcb->p_schtblinib->acsbtmp);

	CHECK_ID(p_curcb->p_schtblinib->p_cntcb == p_nextcb->p_schtblinib->p_cntcb);

	x_nested_lock_os_int();
	p_osapcb = p_curcb->p_schtblinib->p_osapcb;
	/* Start checking the OSAP state of the schedule table belongs to */
	D_CHECK_ACCESS((p_osapcb->osap_stat == APPLICATION_ACCESSIBLE) ||
				   ((p_osapcb->osap_stat == APPLICATION_RESTARTING) &&
					(p_osapcb == p_runosap)));

	p_osapcb = p_nextcb->p_schtblinib->p_osapcb;
	/* Start checking the OSAP state of the schedule table belongs to */
	D_CHECK_ACCESS((p_osapcb->osap_stat == APPLICATION_ACCESSIBLE) ||
				   ((p_osapcb->osap_stat == APPLICATION_RESTARTING) &&
					(p_osapcb == p_runosap)));

	/* Status check of ScheduleTableID_From */
	S_D_CHECK_NOFUNC((p_curcb->status & (SCHEDULETABLE_STOPPED | SCHEDULETABLE_NEXT)) == 0U);

	/* Status check of ScheduleTableID_To */
	S_D_CHECK_STATE(p_nextcb->status == SCHEDULETABLE_STOPPED);

	/*
	 *  If you already Next exists against Current, 
	 * we will cancel for the Next of far
	 */
	if (p_curcb->p_nextschtblcb != NULL) {
		p_curcb->p_nextschtblcb->status = SCHEDULETABLE_STOPPED;
		p_curcb->p_nextschtblcb->p_prevschtblcb = NULL;
	}

	p_curcb->p_nextschtblcb = p_nextcb;
	p_nextcb->status = SCHEDULETABLE_NEXT;
	p_nextcb->p_prevschtblcb = p_curcb;

  d_exit_no_errorhook:
	x_nested_unlock_os_int();
	/* exit_no_errorhook: */
	LOG_NXTSCHTBL_LEAVE(ercd);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
  d_exit_errorhook:
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.schtblid_from = ScheduleTableID_From;
	_errorhook_par2.schtblid_to = ScheduleTableID_To;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_NextScheduleTable);
	goto d_exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}

#endif /* TOPPERS_NextScheduleTable */

/*
 *  Acquisition of schedule table state
 */
#ifdef TOPPERS_GetScheduleTableStatus

StatusType
GetScheduleTableStatus(ScheduleTableType ScheduleTableID,
					   ScheduleTableStatusRefType ScheduleStatus)
{
	StatusType	ercd = E_OK;
	SCHTBLCB	*p_schtblcb;
	OSAPCB		*p_osapcb;

	LOG_GETSCHTBLST_ENTER(ScheduleTableID);
	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_GETSCHEDULETABLESTATUS);
	CHECK_ID(ScheduleTableID < tnum_scheduletable);
	CHECK_PARAM_POINTER(ScheduleStatus);
	CHECK_MEM_WRITE(ScheduleStatus, ScheduleTableStatusType);

	p_schtblcb = get_schtblcb(ScheduleTableID);
	CHECK_RIGHT(p_schtblcb->p_schtblinib->acsbtmp);

	/* Check OSAP state of the schedule table belongs */
	p_osapcb = p_schtblcb->p_schtblinib->p_osapcb;
	CHECK_ACCESS((p_osapcb->osap_stat == APPLICATION_ACCESSIBLE) ||
				 ((p_osapcb->osap_stat == APPLICATION_RESTARTING) &&
				  (p_osapcb == p_runosap)));

	*ScheduleStatus = p_schtblcb->status;

  exit_no_errorhook:
	LOG_GETSCHTBLST_LEAVE(ercd, ScheduleStatus);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.schtblid = ScheduleTableID;
	_errorhook_par2.p_schtblstate = ScheduleStatus;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_GetScheduleTableStatus);
	x_nested_unlock_os_int();
	goto exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}

#endif /* TOPPERS_GetScheduleTableStatus */

/*
 *  Schedule expiration processing function
 */
#ifdef TOPPERS_schtbl_expire

void
schtbl_expire(CNTEXPINFO *p_cntexpinfo, const CNTCB *p_cntcb)
{
	SCHTBLEXPINFO schtblexpinfo;

	schtblexpinfo.p_schtblcb = (SCHTBLCB *) p_cntexpinfo;

	schtbl_expiry_process(&schtblexpinfo, p_cntcb);

	if (schtblexpinfo.p_schtblcb != NULL) {
		insert_cnt_expr_que(&(schtblexpinfo.p_schtblcb->cntexpinfo), (CNTCB *) p_cntcb);
	}
}

#endif /* TOPPERS_schtbl_expire */

/*
 *  Run from the expiration processing function of each timing processing
 */
#ifdef TOPPERS_schtbl_expiry_process

void
schtbl_expiry_process(SCHTBLEXPINFO *p_schtblexpinfo, const CNTCB *p_cntcb)
{
	boolean		loopcont = FALSE;
	SCHTBLCB	*p_schtblcb;

	/*
	 *  Since the set expiration point is likely to be soon expire, 
	 * the loop process by repeating information
	 */
	do {
		p_schtblcb = p_schtblexpinfo->p_schtblcb;

		if (p_schtblcb->expptindex < p_schtblcb->p_schtblinib->tnum_exppt) {
			/* During each expiration point */
			loopcont = schtbl_exppoint_process(p_schtblcb, p_cntcb);
		}
		else if (p_schtblcb->expptindex == p_schtblcb->p_schtblinib->tnum_exppt) {
			/* The last time period */
			loopcont = schtbl_tail(p_schtblcb, p_schtblexpinfo, p_cntcb);
		}
		else {
			/*
			 *  At the start of the period
			 *  p_schtblcb-> expptindex == EXPPTINDEX_INITIAL it is not only there is obtained
			 */
			loopcont = schtbl_head(p_schtblcb, p_cntcb);
		}
	} while (loopcont != FALSE);
}

#endif /* TOPPERS_schtbl_expiry_process */

/*
 *  Start processing of the schedule table
 */
#ifdef TOPPERS_schtbl_head

boolean
schtbl_head(SCHTBLCB *p_schtblcb, const CNTCB *p_cntcb)
{
	boolean				loopcont;
	const SCHTBLEXPPTCB	*p_exppoint;

	p_exppoint = &(p_schtblcb->p_schtblinib->p_exppt[EXPPTINDEX_TOP]);

	if (p_exppoint->offset == 0U) {
		/* If the initial offset 0, and performs one second of expiration 
		 * point processing within this time expiration processing */
		loopcont = TRUE;
	}
	else {
		loopcont = FALSE;
		/* The selection of the next time to be activated */
		p_schtblcb->cntexpinfo.expiretick = add_tick(p_schtblcb->cntexpinfo.expiretick,
													 p_exppoint->offset, p_cntcb->p_cntinib->maxval2);
	}

	p_schtblcb->expptindex = EXPPTINDEX_TOP;

	return(loopcont);
}

#endif /* TOPPERS_schtbl_head */

/*
 *  Each expiration point processing of the schedule table
 */
#ifdef TOPPERS_schtbl_exppoint_process

boolean
schtbl_exppoint_process(SCHTBLCB *p_schtblcb, const CNTCB *p_cntcb)
{
	boolean				loopcont = FALSE;
	const SCHTBLEXPPTCB	*p_exppoint;
	const SCHTBLEXPPTCB *pp_exppoint;
	uint8				index;
	TickType			currtime;
	OSAPCB				*p_runosap_saved;

	pp_exppoint = p_schtblcb->p_schtblinib->p_exppt;
	index = p_schtblcb->expptindex;
	p_exppoint = &(pp_exppoint[index]);

	/* Execution of expiration processing */
	LOG_SCHTBL_ENTER(p_schtblcb);
	p_runosap_saved = p_runosap;
	p_runosap = p_schtblcb->p_schtblinib->p_osapcb;

	(p_exppoint->expptfnt)();

	p_runosap = p_runosap_saved;

	LOG_SCHTBL_LEAVE(p_schtblcb);
	/* Save the current time */
	currtime = p_exppoint->offset;
	/* To the next expiration point */
	index++;
	p_schtblcb->expptindex = index;

	if (p_schtblcb->expptindex == p_schtblcb->p_schtblinib->tnum_exppt) {
		/* If the current is the last point of the expiration period */
		if (p_schtblcb->p_schtblinib->length == currtime) {
			/*
			 *  If one-shot schedule table final delay value is 0, for that might Next exists,
			 * the last timing processing of the schedule table
			 */
			loopcont = TRUE;
		}
		else {
			/* For final delay processing, set the expiration time */
			p_schtblcb->cntexpinfo.expiretick = add_tick(p_schtblcb->cntexpinfo.expiretick,
														 (p_schtblcb->p_schtblinib->length - currtime), p_cntcb->p_cntinib->maxval2);
		}
	}
	else {
		p_exppoint = &(pp_exppoint[index]);
		/* Setting the expiration time of the next expiration point */
		p_schtblcb->cntexpinfo.expiretick = add_tick(p_schtblcb->cntexpinfo.expiretick,
													 (p_exppoint->offset - currtime), p_cntcb->p_cntinib->maxval2);
	}

	return(loopcont);
}

#endif /* TOPPERS_schtbl_exppoint_process */

/*
 *  Termination of the schedule table
 */
#ifdef TOPPERS_schtbl_tail

boolean
schtbl_tail(SCHTBLCB *p_schtblcb, SCHTBLEXPINFO *p_schtblexpinfo, const CNTCB *p_cntcb)
{
	boolean				loopcont = FALSE;
	SCHTBLCB			*p_nextcb;
	const SCHTBLEXPPTCB	*p_exppoint;

	/* Finally at check Next to the presence of a cycle */
	if (p_schtblcb->p_nextschtblcb != NULL) {
		p_nextcb = p_schtblcb->p_nextschtblcb;

		/*
		 *  Switching of schedule table
		 *
		 *  In consideration of the switching of implicit synchronization 
		 * with each other, because the state of the takeover is synchronization 
		 * method check in need NextScheduleTable, there is no mismatch of synchronization method
		 */
		p_nextcb->status = p_schtblcb->status;
		p_nextcb->expptindex = EXPPTINDEX_INITIAL;

		/* Expiration point setting standards for Next becomes the expiration time of Prev */
		p_nextcb->cntexpinfo.expiretick = p_schtblcb->cntexpinfo.expiretick;
		p_nextcb->p_prevschtblcb = NULL;

		/* The end processing for scheduled table of execution state until now */
		p_schtblcb->status = SCHEDULETABLE_STOPPED;
		p_schtblcb->p_nextschtblcb = NULL;

		/*
		 *  When you add the initial expiration point of Next to the counter
		 * expiration queue from the upstream side, and is used
		 */
		p_schtblexpinfo->p_schtblcb = p_nextcb;

		loopcont = TRUE;
	}
	else {
		/* The presence or absence check of cycle control */
		if (p_schtblcb->p_schtblinib->repeat != FALSE) {

			p_schtblcb->expptindex = EXPPTINDEX_TOP;
			p_exppoint = &(p_schtblcb->p_schtblinib->p_exppt[EXPPTINDEX_TOP]);

			if (p_exppoint->offset == 0U) {
				/* If the initial offset 0, and performs one second of expiration 
				 * point processing within this time expiration processing */
				loopcont = TRUE;
			}
			else {
				/* For final delay processing, set the expiration time */
				p_schtblcb->cntexpinfo.expiretick = add_tick(p_schtblcb->cntexpinfo.expiretick,
															 p_exppoint->offset, p_cntcb->p_cntinib->maxval2);
			}
		}
		else {
			/* Because it does not cycle start, end processing */
			p_schtblcb->status = SCHEDULETABLE_STOPPED;
			p_schtblexpinfo->p_schtblcb = NULL;
			p_schtblcb->p_prevschtblcb = NULL;
			p_schtblcb->p_nextschtblcb = NULL;
		}
	}

	return(loopcont);
}

#endif /* TOPPERS_schtbl_tail */

/*
 *  Forced termination of SAP belongs to schedule table
 */
#ifdef TOPPERS_force_term_osap_schtbl

void
force_term_osap_schtbl(OSAPCB *p_osapcb)
{
	ScheduleTableType	i;
	SCHTBLCB			*p_schtblcb;
	SCHTBLCB			*p_nextcb;

	for (i = 0U; i < tnum_scheduletable; i++) {
		if (schtblinib_table[i].p_osapcb == p_osapcb) {
			p_schtblcb = &schtblcb_table[i];
			/*
			 *  If the specified schedule table is SCHEDULETABLE_NEXT, 
			 * from the schedule table that yourself to Next, remove yourself
			 */
			if (p_schtblcb->status == SCHEDULETABLE_NEXT) {
				p_schtblcb->p_prevschtblcb->p_nextschtblcb = NULL;
				p_schtblcb->p_prevschtblcb = NULL;
				p_schtblcb->status = SCHEDULETABLE_STOPPED;
			}
			else if ((p_schtblcb->status == SCHEDULETABLE_RUNNING) ||
					 (p_schtblcb->status == SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS)) {
				/*
				 *  If the Next schedule table exists, 
				 * to cancel the reservation of Next schedule table
				 */
				p_nextcb = p_schtblcb->p_nextschtblcb;
				if (p_nextcb != NULL) {
					p_nextcb->status = SCHEDULETABLE_STOPPED;
					p_nextcb->p_prevschtblcb = NULL;
					p_schtblcb->p_nextschtblcb = NULL;
				}

				/* Remove already registered expiration processing from the counter expiration queue */
				delete_cnt_expr_que(&(p_schtblcb->cntexpinfo),
									p_schtblcb->p_schtblinib->p_cntcb);
				p_schtblcb->status = SCHEDULETABLE_STOPPED;
			}
			else {
				/* Never to be implemented */
			}
		}
	}
}

#endif /* TOPPERS_force_term_osap_schtbl */
