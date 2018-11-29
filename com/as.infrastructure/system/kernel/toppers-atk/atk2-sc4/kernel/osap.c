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
 *  $Id: osap.c 504 2015-12-24 01:22:56Z witz-itoyo $
 */

#include "kernel_impl.h"
#include "check.h"
#include "osap.h"
#include "task.h"
#include "interrupt.h"
#include "counter.h"
#include "alarm.h"
#include "resource.h"
#include "scheduletable.h"
#include "timingprotection.h"

/*
 *		OS application management module
 */

/*
 *  The default definition of trace macro
 */
#ifndef LOG_GETOSAPID_ENTER
#define LOG_GETOSAPID_ENTER()
#endif /* LOG_GETOSAPID_ENTER */

#ifndef LOG_GETOSAPID_LEAVE
#define LOG_GETOSAPID_LEAVE(id)
#endif /* LOG_GETOSAPID_LEAVE */

#ifndef LOG_GETAST_ENTER
#define LOG_GETAST_ENTER(Application)
#endif /* LOG_GETAST_ENTER */

#ifndef LOG_GETAST_LEAVE
#define LOG_GETAST_LEAVE(ercd, p_value)
#endif /* LOG_GETAST_LEAVE */

#ifndef LOG_CALTFN_ENTER
#define LOG_CALTFN_ENTER(FunctionIndex)
#endif /* LOG_CALTFN_ENTER */

#ifndef LOG_CALTFN_LEAVE
#define LOG_CALTFN_LEAVE(FunctionIndex)
#endif /* LOG_CALTFN_LEAVE */

#ifndef LOG_TFN_ENTER
#define LOG_TFN_ENTER(FunctionIndex)
#endif /* LOG_TFN_ENTER */

#ifndef LOG_TFN_LEAVE
#define LOG_TFN_LEAVE(FunctionIndex, ercd)
#endif /* LOG_TFN_LEAVE */

#ifndef LOG_CHKTSKACS_ENTER
#define LOG_CHKTSKACS_ENTER(ApplID, TaskID)
#endif /* LOG_CHKTSKACS_ENTER */

#ifndef LOG_CHKTSKACS_LEAVE
#define LOG_CHKTSKACS_LEAVE(access)
#endif /* LOG_CHKTSKACS_LEAVE */

#ifndef LOG_CHKISRACS_ENTER
#define LOG_CHKISRACS_ENTER(ApplID, ISRID)
#endif /* LOG_CHKISRACS_ENTER */

#ifndef LOG_CHKISRACS_LEAVE
#define LOG_CHKISRACS_LEAVE(access)
#endif /* LOG_CHKISRACS_LEAVE */

#ifndef LOG_CHKALMACS_ENTER
#define LOG_CHKALMACS_ENTER(ApplID, AlarmID)
#endif /* LOG_CHKALMACS_ENTER */

#ifndef LOG_CHKALMACS_LEAVE
#define LOG_CHKALMACS_LEAVE(access)
#endif /* LOG_CHKALMACS_LEAVE */

#ifndef LOG_CHKRESACS_ENTER
#define LOG_CHKRESACS_ENTER(ApplID, ResID)
#endif /* LOG_CHKRESACS_ENTER */

#ifndef LOG_CHKRESACS_LEAVE
#define LOG_CHKRESACS_LEAVE(access)
#endif /* LOG_CHKRESACS_LEAVE */

#ifndef LOG_CHKCNTACS_ENTER
#define LOG_CHKCNTACS_ENTER(ApplID, CounterID)
#endif /* LOG_CHKCNTACS_ENTER */

#ifndef LOG_CHKCNTACS_LEAVE
#define LOG_CHKCNTACS_LEAVE(access)
#endif /* LOG_CHKCNTACS_LEAVE */

#ifndef LOG_CHKSCHTBLACS_ENTER
#define LOG_CHKSCHTBLACS_ENTER(ApplID, ScheduleTableID)
#endif /* LOG_CHKSCHTBLACS_ENTER */

#ifndef LOG_CHKSCHTBLACS_LEAVE
#define LOG_CHKSCHTBLACS_LEAVE(access)
#endif /* LOG_CHKSCHTBLACS_LEAVE */

#ifndef LOG_CHKTSKOWN_ENTER
#define LOG_CHKTSKOWN_ENTER(TaskID)
#endif /* LOG_CHKTSKOWN_ENTER */

#ifndef LOG_CHKTSKOWN_LEAVE
#define LOG_CHKTSKOWN_LEAVE(owner)
#endif /* LOG_CHKTSKOWN_LEAVE */

#ifndef LOG_CHKISROWN_ENTER
#define LOG_CHKISROWN_ENTER(ISRID)
#endif /* LOG_CHKISROWN_ENTER */

#ifndef LOG_CHKISROWN_LEAVE
#define LOG_CHKISROWN_LEAVE(owner)
#endif /* LOG_CHKISROWN_LEAVE */

#ifndef LOG_CHKALMOWN_ENTER
#define LOG_CHKALMOWN_ENTER(AlarmID)
#endif /* LOG_CHKALMOWN_ENTER */

#ifndef LOG_CHKALMOWN_LEAVE
#define LOG_CHKALMOWN_LEAVE(owner)
#endif /* LOG_CHKALMOWN_LEAVE */

#ifndef LOG_CHKCNTOWN_ENTER
#define LOG_CHKCNTOWN_ENTER(CounterID)
#endif /* LOG_CHKCNTOWN_ENTER */

#ifndef LOG_CHKCNTOWN_LEAVE
#define LOG_CHKCNTOWN_LEAVE(owner)
#endif /* LOG_CHKCNTOWN_LEAVE */

#ifndef LOG_CHKSCHTBLOWN_ENTER
#define LOG_CHKSCHTBLOWN_ENTER(ScheduleTableID)
#endif /* LOG_CHKSCHTBLOWN_ENTER */

#ifndef LOG_CHKSCHTBLOWN_LEAVE
#define LOG_CHKSCHTBLOWN_LEAVE(owner)
#endif /* LOG_CHKSCHTBLOWN_LEAVE */

#ifndef LOG_ALLOWACCESS_ENTER
#define LOG_ALLOWACCESS_ENTER()
#endif /* LOG_ALLOWACCESS_ENTER */

#ifndef LOG_ALLOWACCESS_LEAVE
#define LOG_ALLOWACCESS_LEAVE(ercd)
#endif /* LOG_ALLOWACCESS_LEAVE */

#ifndef LOG_TERMINATEAPPLICATION_ENTER
#define LOG_TERMINATEAPPLICATION_ENTER(Application, RestartOption)
#endif /* LOG_TERMINATEAPPLICATION_ENTER */

#ifndef LOG_TERMINATEAPPLICATION_LEAVE
#define LOG_TERMINATEAPPLICATION_LEAVE(ercd)
#endif /* LOG_TERMINATEAPPLICATION_LEAVE */

#ifdef TOPPERS_force_term_osap
/* Prototype declaration of internal functions */
static void force_term_osap_main(void);
#endif /* TOPPERS_force_term_osap */

#ifdef TOPPERS_osap_initialize
/*
 *  OS application running
 */
OSAPCB *p_runosap;

/*
 *  OS application management block initialization
 */
void
osap_initialize(void)
{
	ApplicationType	i;
	OSAPCB			*p_osapcb;

	p_runosap = NULL;
	for (i = 0U; i < tnum_osap; i++) {
		p_osapcb = &osapcb_table[i];
		p_osapcb->p_osapinib = &osapinib_table[i];
		p_osapcb->osap_stat = APPLICATION_ACCESSIBLE;
	}
}

#endif /* TOPPERS_osap_initialize */

/*
 *  OS application ID acquisition of execution state
 */
#ifdef TOPPERS_GetApplicationID

ApplicationType
GetApplicationID(void)
{
	ApplicationType id;
	StatusType		ercd;

	LOG_GETOSAPID_ENTER();

	CHECK_CALLEVEL(CALLEVEL_GETAPPLICATIONID);

	id = (p_runosap == NULL) ? INVALID_OSAPPLICATION : OSAPID(p_runosap);

  exit_finish:
	LOG_GETOSAPID_LEAVE(id);
	return(id);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
	call_errorhook(ercd, OSServiceId_GetApplicationID);
	x_nested_unlock_os_int();
#endif /* CFG_USE_ERRORHOOK */

	/* exit_no_errorhook: */
	id = INVALID_OSAPPLICATION;
	goto exit_finish;
}

#endif /* TOPPERS_GetApplicationID */

/*
 *  System services that the application to the available state
 */
#ifdef TOPPERS_GetApplicationState

StatusType
GetApplicationState(ApplicationType Application, ApplicationStateRefType Value)
{
	StatusType	ercd = E_OK;
	OSAPCB		*p_osapcb;

	LOG_GETAST_ENTER(Application);

	CHECK_CALLEVEL(CALLEVEL_GETAPPLICATIONSTATE);
	CHECK_PARAM_POINTER(Value);
	CHECK_MEM_WRITE(Value, ApplicationStateType);
	CHECK_ID(Application < tnum_osap);

	p_osapcb = get_osapcb(Application);
	*Value = p_osapcb->osap_stat;

  exit_no_errorhook:
	LOG_GETAST_LEAVE(ercd, Value);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.applid = Application;
	_errorhook_par2.p_appstat = Value;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_GetApplicationState);
	x_nested_unlock_os_int();
	goto exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}

#endif /* TOPPERS_GetApplicationState */

#ifdef TOPPERS_CallTrustedFunction

StatusType
CallTrustedFunction(TrustedFunctionIndexType FunctionIndex,
					TrustedFunctionParameterRefType FunctionParams)
{
	StatusType		ercd = E_OK;
	const TFINIB	*p_tfinib;
	boolean			saved_run_trusted;
	TickType		tp_timer;
#ifdef CFG_USE_PROTECTIONHOOK
	boolean			saved_calltfn;
#endif /* CFG_USE_PROTECTIONHOOK */

	LOG_CALTFN_ENTER(FunctionIndex);

	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_CALLTRUSTEDFUNCTION);

	/* Check the function ID */
	CHECK_SERVICEID(FunctionIndex < tnum_tfn);

	/* Check the stack to be used */
	p_tfinib = &(tfinib_table[FunctionIndex]);
	ercd = trustedfunc_stack_check(p_tfinib->tf_stksz);
	CHECK_NO_ERCD(ercd == E_OK);

	/* Trust function execution time monitoring */
	if (is_tp_timer_running != FALSE) {
		tp_timer = target_tp_get_remaining_ticks();
		CHECK_ERROR_ERCD((tp_timer > p_tfinib->tf_budget), E_OS_TIMEINSUFFICIENT);
	}

	saved_run_trusted = run_trusted;
	run_trusted = TRUE;

#ifdef CFG_USE_PROTECTIONHOOK
	/* Trust in a function call flag setting */
	if (callevel_stat == TCL_TASK) {
		saved_calltfn = p_runtsk->calltfn;
		p_runtsk->calltfn = TRUE;
	}
	else {
		saved_calltfn = p_runisr->calltfn;
		p_runisr->calltfn = TRUE;
	}
#endif /* CFG_USE_PROTECTIONHOOK */

	LOG_TFN_ENTER(FunctionIndex);
	/* Run trust function */
	ercd = p_tfinib->trs_func(FunctionIndex, FunctionParams);
	LOG_TFN_LEAVE(FunctionIndex, ercd);

#ifdef CFG_USE_STACKMONITORING
	if ((callevel_stat & TCL_ISR2) != TCL_NULL) {
		if ((*TOPPERS_ISTK_MAGIC_REGION(_ostk, _ostksz)) != STACK_MAGIC_NUMBER) {
			x_nested_lock_os_int();
			pre_protection_supervised = TRUE;
			call_protectionhk_main(E_OS_STACKFAULT);
			ASSERT_NO_REACHED;
		}
	}
	else {
		if ((*TOPPERS_SSTK_MAGIC_REGION(p_runtsk->p_tinib)) != STACK_MAGIC_NUMBER) {
			x_nested_lock_os_int();
			pre_protection_supervised = TRUE;
			call_protectionhk_main_stkchg(E_OS_STACKFAULT);
			ASSERT_NO_REACHED;
		}
	}
#endif /* CFG_USE_STACKMONITORING */

#ifdef CFG_USE_PROTECTIONHOOK
	/* Return in trust function call flag */
	if (callevel_stat == TCL_TASK) {
		p_runtsk->calltfn = saved_calltfn;
	}
	else {
		p_runisr->calltfn = saved_calltfn;
	}
#endif /* CFG_USE_PROTECTIONHOOK */

	run_trusted = saved_run_trusted;

	/* Call the error hook even if the trust function resulted in an error */
	CHECK_NO_ERCD(ercd == E_OK);

  exit_no_errorhook:
	LOG_CALTFN_LEAVE(ercd);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.tfnid = FunctionIndex;
	_errorhook_par2.tfnpr = FunctionParams;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_CallTrustedFunction);
	x_nested_unlock_os_int();
	goto exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}

#endif /* TOPPERS_CallTrustedFunction */

/*
 *  Access check function
 */

/*
 *  Access authority checking system services object of OS applications
 */

/*
 *  Bitmap check macro
 *   For use only this file, and is defined here
 */

#define	CHECK_OSAP_ACS(p_osapinib, btmp)	(ObjectAccessType) ((((p_osapinib)->osap_trusted) != FALSE) || \
																(((p_osapinib)->btptn & (btmp)) != 0U))

/*
 *  Task for the access authority checking system service
 */
#ifdef TOPPERS_CheckTaskAccess

ObjectAccessType
CheckTaskAccess(ApplicationType ApplID, TaskType TaskID)
{
	ObjectAccessType	access;
	StatusType			ercd;
	TCB					*p_tcb;

	LOG_CHKTSKACS_ENTER(ApplID, TaskID);

	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_CHECKOBJECTACCESS);
	CHECK_ID(ApplID < tnum_osap);
	CHECK_ID(TaskID < tnum_task);

	p_tcb = get_tcb(TaskID);

	access = CHECK_OSAP_ACS(get_osapinib(ApplID), p_tcb->p_tinib->acsbtmp);

  exit_finish:
	LOG_CHKTSKACS_LEAVE(access);
	return(access);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.applid = ApplID;
	_errorhook_par2.tskid = TaskID;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_CheckTaskAccess);
	x_nested_unlock_os_int();
#endif /* CFG_USE_ERRORHOOK */

	/* exit_no_errorhook: */
	access = NO_ACCESS;
	goto exit_finish;
}

#endif /* TOPPERS_CheckTaskAccess */

/*
 *  ISR for access authority checking system service
 */
#ifdef TOPPERS_CheckISRAccess

ObjectAccessType
CheckISRAccess(ApplicationType ApplID, ISRType ISRID)
{
	ObjectAccessType	access;
	StatusType			ercd;
	ISRCB				*p_isrcb;

	LOG_CHKISRACS_ENTER(ApplID, ISRID);

	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_CHECKOBJECTACCESS);
	CHECK_ID(ApplID < tnum_osap);
	CHECK_ID(ISRID < tnum_isr2);

	p_isrcb = get_isrcb(ISRID);

	access = CHECK_OSAP_ACS(get_osapinib(ApplID), p_isrcb->p_isrinib->acsbtmp);

  exit_finish:
	LOG_CHKISRACS_LEAVE(access);
	return(access);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.applid = ApplID;
	_errorhook_par2.isrid = ISRID;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_CheckISRAccess);
	x_nested_unlock_os_int();
#endif /* CFG_USE_ERRORHOOK */

	/* exit_no_errorhook: */
	access = NO_ACCESS;
	goto exit_finish;
}

#endif /* TOPPERS_CheckISRAccess */

/*
 *  Alarm for the access authority checking system service
 */
#ifdef TOPPERS_CheckAlarmAccess

ObjectAccessType
CheckAlarmAccess(ApplicationType ApplID, AlarmType AlarmID)
{
	ObjectAccessType	access;
	StatusType			ercd;
	ALMCB				*p_almcb;

	LOG_CHKALMACS_ENTER(ApplID, AlarmID);

	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_CHECKOBJECTACCESS);
	CHECK_ID(ApplID < tnum_osap);
	CHECK_ID(AlarmID < tnum_alarm);

	p_almcb = get_almcb(AlarmID);

	access = CHECK_OSAP_ACS(get_osapinib(ApplID), p_almcb->p_alminib->acsbtmp);

  exit_finish:
	LOG_CHKALMACS_LEAVE(access);
	return(access);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.applid = ApplID;
	_errorhook_par2.almid = AlarmID;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_CheckAlarmAccess);
	x_nested_unlock_os_int();
#endif /* CFG_USE_ERRORHOOK */

	/* exit_no_errorhook: */
	access = NO_ACCESS;
	goto exit_finish;
}

#endif /* TOPPERS_CheckAlarmAccess */

/*
 *  Resources for the access authority checking system service
 */
#ifdef TOPPERS_CheckResourceAccess

ObjectAccessType
CheckResourceAccess(ApplicationType ApplID, ResourceType ResID)
{
	ObjectAccessType	access;
	StatusType			ercd;
	RESCB				*p_rescb;

	LOG_CHKRESACS_ENTER(ApplID, ResID);

	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_CHECKOBJECTACCESS);
	CHECK_ID(ApplID < tnum_osap);
	CHECK_ID(ResID < tnum_stdresource);

	p_rescb = get_rescb(ResID);
	access = CHECK_OSAP_ACS(get_osapinib(ApplID), p_rescb->p_resinib->acsbtmp);

  exit_finish:
	LOG_CHKRESACS_LEAVE(access);
	return(access);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.applid = ApplID;
	_errorhook_par2.resid = ResID;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_CheckResourceAccess);
	x_nested_unlock_os_int();
#endif /* CFG_USE_ERRORHOOK */

	/* exit_no_errorhook: */
	access = NO_ACCESS;
	goto exit_finish;
}

#endif /* TOPPERS_CheckResourceAccess */

/*
 *  Counter for access authority checking system service
 */
#ifdef TOPPERS_CheckCounterAccess

ObjectAccessType
CheckCounterAccess(ApplicationType ApplID, CounterType CounterID)
{
	ObjectAccessType	access;
	StatusType			ercd;
	CNTCB				*p_cntcb;

	LOG_CHKCNTACS_ENTER(ApplID, CounterID);

	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_CHECKOBJECTACCESS);
	CHECK_ID(ApplID < tnum_osap);
	CHECK_ID(CounterID < tnum_counter);

	p_cntcb = get_cntcb(CounterID);

	access = CHECK_OSAP_ACS(get_osapinib(ApplID), p_cntcb->p_cntinib->acsbtmp);

  exit_finish:
	LOG_CHKCNTACS_LEAVE(access);
	return(access);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.applid = ApplID;
	_errorhook_par2.cntid = CounterID;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_CheckCounterAccess);
	x_nested_unlock_os_int();
#endif /* CFG_USE_ERRORHOOK */

	/* exit_no_errorhook: */
	access = NO_ACCESS;
	goto exit_finish;
}

#endif /* TOPPERS_CheckCounterAccess */

/*
 *  Access authority checking system for service schedule table
 */
#ifdef TOPPERS_CheckScheduleTableAccess

ObjectAccessType
CheckScheduleTableAccess(ApplicationType ApplID, ScheduleTableType ScheduleTableID)
{
	ObjectAccessType	access;
	StatusType			ercd;
	SCHTBLCB			*p_schtblcb;

	LOG_CHKSCHTBLACS_ENTER(ApplID, ScheduleTableID);

	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_CHECKOBJECTACCESS);
	CHECK_ID(ApplID < tnum_osap);
	CHECK_ID(ScheduleTableID < tnum_scheduletable);

	p_schtblcb = get_schtblcb(ScheduleTableID);

	access = CHECK_OSAP_ACS(get_osapinib(ApplID), p_schtblcb->p_schtblinib->acsbtmp);

  exit_finish:
	LOG_CHKSCHTBLACS_LEAVE(access);
	return(access);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.applid = ApplID;
	_errorhook_par2.schtblid = ScheduleTableID;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_CheckScheduleTableAccess);
	x_nested_unlock_os_int();
#endif /* CFG_USE_ERRORHOOK */

	/* exit_no_errorhook: */
	access = NO_ACCESS;
	goto exit_finish;
}

#endif /* TOPPERS_CheckScheduleTableAccess */

/*
 *  Ownership check system services object of OS applications
 */

/*
 *  Task for the object owner check system service
 */
#ifdef TOPPERS_CheckTaskOwnership

ApplicationType
CheckTaskOwnership(TaskType TaskID)
{
	ApplicationType	owner;
	StatusType		ercd;
	TCB				*p_tcb;

	LOG_CHKTSKOWN_ENTER(TaskID);

	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_CHECKOBJECTOWNERSHIP);
	CHECK_ID(TaskID < tnum_task);

	p_tcb = get_tcb(TaskID);
	owner = OSAPID(p_tcb->p_tinib->p_osapcb);

  exit_finish:
	LOG_CHKTSKOWN_LEAVE(owner);
	return(owner);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.tskid = TaskID;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_CheckTaskOwnership);
	x_nested_unlock_os_int();
#endif /* CFG_USE_ERRORHOOK */

	/* exit_no_errorhook: */
	owner = INVALID_OSAPPLICATION;
	goto exit_finish;
}

#endif /* TOPPERS_CheckTaskOwnership */

/*
 *  ISR for the object owner check system service
 */
#ifdef TOPPERS_CheckISROwnership

ApplicationType
CheckISROwnership(ISRType ISRID)
{
	ApplicationType	owner;
	StatusType		ercd;
	ISRCB			*p_isrcb;

	LOG_CHKISROWN_ENTER(ISRID);

	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_CHECKOBJECTOWNERSHIP);
	CHECK_ID(ISRID < tnum_isr2);

	p_isrcb = get_isrcb(ISRID);
	owner = OSAPID(p_isrcb->p_isrinib->p_osapcb);

  exit_finish:
	LOG_CHKISROWN_LEAVE(owner);
	return(owner);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.isrid = ISRID;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_CheckISROwnership);
	x_nested_unlock_os_int();
#endif /* CFG_USE_ERRORHOOK */

	/* exit_no_errorhook: */
	owner = INVALID_OSAPPLICATION;
	goto exit_finish;
}

#endif /* TOPPERS_CheckISROwnership */

/*
 *  Alarm for the object owner check system service
 */
#ifdef TOPPERS_CheckAlarmOwnership

ApplicationType
CheckAlarmOwnership(AlarmType AlarmID)
{
	ApplicationType	owner;
	StatusType		ercd;
	ALMCB			*p_almcb;

	LOG_CHKALMOWN_ENTER(AlarmID);

	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_CHECKOBJECTOWNERSHIP);
	CHECK_ID(AlarmID < tnum_alarm);

	p_almcb = get_almcb(AlarmID);
	owner = OSAPID(p_almcb->p_alminib->p_osapcb);

  exit_finish:
	LOG_CHKALMOWN_LEAVE(owner);
	return(owner);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.almid = AlarmID;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_CheckAlarmOwnership);
	x_nested_unlock_os_int();
#endif /* CFG_USE_ERRORHOOK */

	/* exit_no_errorhook: */
	owner = INVALID_OSAPPLICATION;
	goto exit_finish;
}

#endif /* TOPPERS_CheckAlarmOwnership */

/*
 *  Counter for the object owner check system service
 */
#ifdef TOPPERS_CheckCounterOwnership

ApplicationType
CheckCounterOwnership(CounterType CounterID)
{
	ApplicationType	owner;
	StatusType		ercd;
	CNTCB			*p_cntcb;

	LOG_CHKCNTOWN_ENTER(CounterID);

	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_CHECKOBJECTOWNERSHIP);
	CHECK_ID(CounterID < tnum_counter);

	p_cntcb = get_cntcb(CounterID);
	owner = OSAPID(p_cntcb->p_cntinib->p_osapcb);

  exit_finish:
	LOG_CHKCNTOWN_LEAVE(owner);
	return(owner);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.cntid = CounterID;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_CheckCounterOwnership);
	x_nested_unlock_os_int();
#endif /* CFG_USE_ERRORHOOK */

	/* exit_no_errorhook: */
	owner = INVALID_OSAPPLICATION;
	goto exit_finish;
}

#endif /* TOPPERS_CheckCounterOwnership */

/*
 *  Object owner check system for service schedule table
 */
#ifdef TOPPERS_CheckScheduleTableOwnership

ApplicationType
CheckScheduleTableOwnership(ScheduleTableType ScheduleTableID)
{
	ApplicationType	owner;
	StatusType		ercd;
	SCHTBLCB		*p_schtblcb;

	LOG_CHKSCHTBLOWN_ENTER(ScheduleTableID);

	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_CHECKOBJECTOWNERSHIP);
	CHECK_ID(ScheduleTableID < tnum_scheduletable);

	p_schtblcb = get_schtblcb(ScheduleTableID);
	owner = OSAPID(p_schtblcb->p_schtblinib->p_osapcb);

  exit_finish:
	LOG_CHKSCHTBLOWN_LEAVE(owner);
	return(owner);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.schtblid = ScheduleTableID;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_CheckScheduleTableOwnership);
	x_nested_unlock_os_int();
#endif /* CFG_USE_ERRORHOOK */

	/* exit_no_errorhook: */
	owner = INVALID_OSAPPLICATION;
	goto exit_finish;
}

#endif /* TOPPERS_CheckScheduleTableOwnership */

/*
 *  It will be ready for use of the self-SOAP
 */
#ifdef TOPPERS_AllowAccess

StatusType
AllowAccess(void)
{
	StatusType ercd = E_OK;

	LOG_ALLOWACCESS_ENTER();

	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_ALLOWACCESS);
	/* p_runosap (self OSAP) is not NULL If you came here */
	CHECK_STATE(p_runosap->osap_stat == APPLICATION_RESTARTING);

	x_nested_lock_os_int();

	p_runosap->osap_stat = APPLICATION_ACCESSIBLE;

  d_exit_no_errorhook:
	x_nested_unlock_os_int();
	/* exit_no_errorhook: */
	LOG_ALLOWACCESS_LEAVE(ercd);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
	call_errorhook(ercd, OSServiceId_AllowAccess);
	goto d_exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}

#endif /* TOPPERS_AllowAccess */

/*
 *  I terminate / restart the specified OSAP
 */
#ifdef TOPPERS_TerminateApplication

StatusType
TerminateApplication(ApplicationType Application, RestartType RestartOption)
{
	StatusType	ercd = E_OK;
	OSAPCB		*p_osapcb;

	LOG_TERMINATEAPPLICATION_ENTER(Application, RestartOption);

	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_TERMINATEAPPLICATION);
	CHECK_ID((Application < tnum_osap) && (get_osapinib(Application)->osap_trusted == FALSE));
	p_osapcb = get_osapcb(Application);
	CHECK_VALUE((RestartOption == NO_RESTART) || ((RestartOption == RESTART) &&
												  (p_osapcb->p_osapinib->p_restart_tcb->p_tinib->task != NULL)));

	CHECK_ACCESS((run_trusted != FALSE) || (p_osapcb == p_runosap));

	x_nested_lock_os_int();

	S_D_CHECK_STATE((p_osapcb->osap_stat == APPLICATION_ACCESSIBLE) ||
					((p_osapcb->osap_stat == APPLICATION_RESTARTING) &&
					 (p_osapcb == p_runosap) && (RestartOption == NO_RESTART)));

	force_term_osap(p_osapcb, RestartOption);

  d_exit_no_errorhook:
	x_nested_unlock_os_int();
	/* exit_no_errorhook: */
	LOG_TERMINATEAPPLICATION_LEAVE(ercd);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
  d_exit_errorhook:
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.applid = Application;
	_errorhook_par2.restartoption = RestartOption;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_TerminateApplication);
	goto d_exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}

#endif /* TOPPERS_TerminateApplication */

/*
 *  Internal function to terminate / restart the specified OSAP
 */
#ifdef TOPPERS_force_term_osap

static void
force_term_osap_main(void)
{
	OSAPCB *p_osapcb;

	p_osapcb = p_runosap;

	force_term_osap_counter(p_osapcb);
	force_term_osap_task(p_osapcb);

	if (p_osapcb->osap_stat == APPLICATION_RESTARTING) {
		(void) make_active(p_osapcb->p_osapinib->p_restart_tcb);
	}
	/* In order to finish the restart task role of provisional, it performs the processing of the queue */
	search_schedtsk();

	/* Set of task context */
	callevel_stat = TCL_TASK;

	if (sus_os_cnt > 0U) {
		sus_os_cnt = 0U;
		os_saved_watchtype = NON_MONITORING;
		os_difftime = 0U;
		x_set_ipm(sus_os_prevpri);
	}
	/* Because from the self OSAP of call, it does not return to the caller */
	exit_and_dispatch_nohook();
}

/*
 *  It stores the address of the force_term_osap_main to pc restart task
 */
void
force_term_osap(OSAPCB *p_osapcb, RestartType RestartOption)
{
	TCB				*p_tcb;
	PriorityType	remove_task_pri;

	/* update of osap_stat */
	if (RestartOption == RESTART) {
		p_osapcb->osap_stat = APPLICATION_RESTARTING;
		if (p_osapcb->p_osapinib->p_restart_tcb->p_tinib->task == NULL) {
			/* Even though there is no set of restart task,*/
			/* To implement the shut down If you set the RESTART option */
			internal_shutdownos(E_OS_PROTECTION_FATAL);
		}
	}
	else {
		p_osapcb->osap_stat = APPLICATION_TERMINATED;
	}

	force_term_osap_alarm(p_osapcb);
	force_term_osap_schtbl(p_osapcb);

	p_tcb = p_osapcb->p_osapinib->p_restart_tcb;

	/* To be removed from the ready queue If restart task is already in the READY state */
	if (p_tcb->tstat == READY) {
		/* The end of the restart task */
		p_tcb->actcnt = 0U;
#ifdef CFG_USE_PROTECTIONHOOK
		p_tcb->calltfn = FALSE;
#endif /* CFG_USE_PROTECTIONHOOK */
		/* corresponding to the case where curpri and inipri it has been linked to the ready queue with a different value */
		remove_task_pri = p_tcb->curpri;

		/* If the as-resource reservation, resource release */
		release_taskresources(p_tcb);

		/* Initialize the state of the counter */
		cancel_taskcounters(p_tcb);

		/* The target task is set to SUSPEND state, to be removed from the ready queue */
		p_tcb->tstat = SUSPENDED;
		if (p_tcb != p_schedtsk) {
			remove_task_from_queue(p_tcb, remove_task_pri);
			/* to save the p_schedtsk the head of the queue */
			move_schedtsk();
		}
	}
	else if (p_schedtsk != NULL) {
		/* unless p_schedtsk is NULL, and save the head of the queue */
		move_schedtsk();
	}
	else {
		/* it is not nothing if p_schedtsk is NULL */
	}

	/* And stores the address of the force_term_osap_main to pc restart task */
	activate_force_term_osap_main(p_tcb);

	/* Change curpri to the highest priority */
	p_tcb->curpri = TPRI_MAXTASK;

	/* Stores p_restart_tcb to p_schedtsk */
	p_schedtsk = p_tcb;

	if ((callevel_stat & TCL_ISR2) != TCL_NULL) {
		/* If it is called from C2ISR, at the exit processing of C2ISR */
		/* Order to perform the dispatch is not performed here    */
	}
	else if (p_osapcb != p_runosap) {
		/* To terminate / restart another OS performs dispatching */
		dispatch();
	}
	else {
		/* If you want to exit / restart the self OSAP, it does not return to the caller */
		exit_and_dispatch_nohook();
	}
}

#endif /* TOPPERS_force_term_osap */
