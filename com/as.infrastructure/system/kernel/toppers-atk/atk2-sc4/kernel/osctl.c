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
 *  $Id: osctl.c 504 2015-12-24 01:22:56Z witz-itoyo $
 */

/*
 *		OS control module
 */

#include "kernel_impl.h"
#include "interrupt.h"
#include "task.h"

/*
 *  The default definition of the trace log macro
 */

#ifndef LOG_ERRHOOK_ENTER
#define LOG_ERRHOOK_ENTER(ercd)
#endif /* LOG_ERRHOOK_ENTER */

#ifndef LOG_ERRHOOK_LEAVE
#define LOG_ERRHOOK_LEAVE()
#endif /* LOG_ERRHOOK_LEAVE */

#ifndef LOG_PROHOOK_ENTER
#define LOG_PROHOOK_ENTER(ercd)
#endif /* LOG_PROHOOK_ENTER */

#ifndef LOG_PROHOOK_LEAVE
#define LOG_PROHOOK_LEAVE(pret)
#endif /* LOG_PROHOOK_LEAVE */

#ifndef LOG_SHUTHOOK_ENTER
#define LOG_SHUTHOOK_ENTER(ercd)
#endif /* LOG_SHUTHOOK_ENTER */

#ifndef LOG_SHUTHOOK_LEAVE
#define LOG_SHUTHOOK_LEAVE()
#endif /* LOG_SHUTHOOK_LEAVE */

#ifndef LOG_STUTOS_ENTER
#define LOG_STUTOS_ENTER(ercd)
#endif /* LOG_STUTOS_ENTER */

#ifndef LOG_STUTOS_LEAVE
#define LOG_STUTOS_LEAVE()
#endif /* LOG_STUTOS_LEAVE */

#ifdef CFG_USE_ERRORHOOK
/*
 *  Variable to store the information to be passed to the error hook
 */
#ifdef TOPPERS_internal_call_errorhook

#ifdef CFG_USE_GETSERVICEID
DEFINE_VAR_SEC_NOBITS(OSServiceIdType, _errorhook_svcid, ".srpw_bss_kernel");
#endif /* CFG_USE_GETSERVICEID */

#ifdef CFG_USE_PARAMETERACCESS
_ErrorHook_Par	_errorhook_par1;
_ErrorHook_Par	_errorhook_par2;
_ErrorHook_Par	_errorhook_par3;
DEFINE_VAR_SEC_NOBITS(_ErrorHook_Par, errorhook_par1, ".srpw_bss_kernel");
DEFINE_VAR_SEC_NOBITS(_ErrorHook_Par, errorhook_par2, ".srpw_bss_kernel");
DEFINE_VAR_SEC_NOBITS(_ErrorHook_Par, errorhook_par3, ".srpw_bss_kernel");
#endif /* CFG_USE_PARAMETERACCESS */

/*
 *  Call of error hook
 */
void
call_errorhook(StatusType ercd, OSServiceIdType svcid)
{
	boolean	saved_run_trusted = run_trusted;

	if ((callevel_stat & (TCL_ERROR | TSYS_ISR1)) == TCL_NULL) {

#ifdef CFG_USE_GETSERVICEID
		_errorhook_svcid = svcid;
#endif /* CFG_USE_GETSERVICEID */

#ifdef CFG_USE_PARAMETERACCESS
		errorhook_par1 = _errorhook_par1;
		errorhook_par2 = _errorhook_par2;
		errorhook_par3 = _errorhook_par3;
#endif /* CFG_USE_PARAMETERACCESS */

		ENTER_CALLEVEL(TCL_ERROR);
		run_trusted = TRUE;

		LOG_ERRHOOK_ENTER(ercd);
		ErrorHook(ercd);
		LOG_ERRHOOK_LEAVE();
		LEAVE_CALLEVEL(TCL_ERROR);
	}

	run_trusted = saved_run_trusted;
}

#endif /* TOPPERS_internal_call_errorhook */

#endif /* CFG_USE_ERRORHOOK */

#ifdef CFG_USE_POSTTASKHOOK
/*
 *  Call of post task hook
 */
#ifdef TOPPERS_call_posttaskhook

void
call_posttaskhook(void)
{
	boolean saved_run_trusted;

	ENTER_CALLEVEL(TCL_PREPOST);
	saved_run_trusted = run_trusted;
	run_trusted = TRUE;

	PostTaskHook();

	run_trusted = saved_run_trusted;

	LEAVE_CALLEVEL(TCL_PREPOST);
}

#endif /* TOPPERS_call_posttaskhook */

#endif /* CFG_USE_POSTTASKHOOK */

#ifdef CFG_USE_PRETASKHOOK
/*
 *  Call of the pre-task hook
 */
#ifdef TOPPERS_call_pretaskhook

void
call_pretaskhook(void)
{
	boolean saved_run_trusted;

	ENTER_CALLEVEL(TCL_PREPOST);
	saved_run_trusted = run_trusted;
	run_trusted = TRUE;

	PreTaskHook();

	run_trusted = saved_run_trusted;

	LEAVE_CALLEVEL(TCL_PREPOST);
}

#endif /* TOPPERS_call_pretaskhook */

#endif /* CFG_USE_PRETASKHOOK */

#ifdef CFG_USE_SHUTDOWNHOOK
void call_shutdownhook(StatusType ercd)
{
	boolean saved_run_trusted;

	ENTER_CALLEVEL(TCL_SHUTDOWN);
	saved_run_trusted = run_trusted;
	run_trusted = TRUE;

	ShutdownHook(ercd);

	run_trusted = saved_run_trusted;

	LEAVE_CALLEVEL(TCL_SHUTDOWN);
}
#endif /* CFG_USE_SHUTDOWNHOOK */

#ifdef CFG_USE_STACKMONITORING

#ifdef TOPPERS_init_stack_magic_region

/*
 *  Initialization of stack monitoring function
 *  Initialization of the magic number area for stack monitoring function
 */
void
init_stack_magic_region(void)
{
	StackType *p_stack_magic_region;

	/*
	 *  For stack monitoring function, the initialization of the magic number 
	 * area of the stack growth direction taking into account the non-task stack
	 */
	p_stack_magic_region = TOPPERS_ISTK_MAGIC_REGION(_ostk, _ostksz);
	*p_stack_magic_region = STACK_MAGIC_NUMBER;
}

#endif /* TOPPERS_init_stack_magic_region */

#endif /* CFG_USE_STACKMONITORING */

/*
 *  Call of protection hook
 *  Most significant bits of the arguments, a role indicating a call points
 */
#ifdef TOPPERS_call_protectionhk_main

void
call_protectionhk_main(StatusType protection_error)
{

#ifdef CFG_USE_PROTECTIONHOOK

	boolean					saved_run_trusted;

	ProtectionReturnType	pret;

	/* If a protection violation occurs during the execution protection hook */
	if ((callevel_stat & TCL_PROTECT) == TCL_PROTECT) {
		internal_shutdownos(E_OS_PROTECTION_FATAL);
	}

	/* Processing to call the following protection hook */
	ENTER_CALLEVEL(TCL_PROTECT);
	saved_run_trusted = run_trusted;

	run_trusted = TRUE;
	LOG_PROHOOK_ENTER(protection_error);
	pret = ProtectionHook(protection_error);
	LOG_PROHOOK_LEAVE(pret);
	run_trusted = saved_run_trusted;

	LEAVE_CALLEVEL(TCL_PROTECT);

	/* Treatment after the following ProtectionHook run*/
	switch (pret) {
	case PRO_SHUTDOWN:
		internal_shutdownos(protection_error);
		break;
	case PRO_TERMINATETASKISR:
		if ((p_runtsk == NULL) || (pre_protection_supervised != FALSE)) {
			/* Hook at the time of shutdown from the trust region */
			internal_shutdownos(E_OS_PROTECTION_FATAL);
		}
		else {
			/* For tasks */
			force_terminate_task(p_runtsk);
		}
		break;
	case PRO_IGNORE:
		if ((protection_error != E_OS_PROTECTION_EXCEPTION) && (protection_error != E_OS_PROTECTION_ARRIVAL_ISR)) {
			internal_shutdownos(E_OS_PROTECTION_FATAL);
		}
		break;
	case PRO_TERMINATEAPPL:
		if ((p_runosap == NULL) || (pre_protection_supervised != FALSE)) {
			internal_shutdownos(E_OS_PROTECTION_FATAL);
		}
		else {
			force_term_osap(p_runosap, NO_RESTART);
		}
		break;
	case PRO_TERMINATEAPPL_RESTART:
		if ((p_runosap == NULL) || (pre_protection_supervised != FALSE)) {
			internal_shutdownos(E_OS_PROTECTION_FATAL);
		}
		else {
			force_term_osap(p_runosap, RESTART);
		}
		break;
	default:
		/* If an invalid value was returned from ProtectionHook */
		internal_shutdownos(E_OS_PROTECTION_FATAL);
		break;
	}

#else /* CFG_USE_PROTECTIONHOOK */

	/*
	 *  If the protection hooks have been disabled during configuration, 
	 * OS performs the OS shut down as the time of processing protection violation
	 *
	 *  In this case, as a parameter of OS shutdown, specify an error code 
	 * indicating the distinction of violation
	 */
	internal_shutdownos(protection_error);
#endif /* CFG_USE_PROTECTIONHOOK */

}

#endif /* TOPPERS_call_protectionhk_main */

/*
 *  Call of ShutdownOS from internal OS
 */
#ifdef TOPPERS_internal_shutdownos

void
internal_shutdownos(StatusType ercd)
{
	LOG_STUTOS_ENTER(ercd);

	x_nested_lock_os_int();

#ifdef CFG_USE_SHUTDOWNHOOK
	call_shutdownhook(ercd);
#endif /* CFG_USE_SHUTDOWNHOOK */

	/* End processing of each module */
	object_terminate();

	/* The transition to all interrupt disabled state */
	x_lock_all_int();

	LOG_STUTOS_LEAVE();

	/* End processing of target-dependent */
	target_exit();

	/*
	 * If the process is returned from the target-dependent module,
	 * Do an infinite loop
	 */
	while (1) {
	}

}

#endif /* TOPPERS_internal_shutdownos */

#ifdef TOPPERS_internal_call_shtdwnhk

#ifdef CFG_USE_SHUTDOWNHOOK

void
internal_call_shtdwnhk(StatusType ercd)
{

	/*
	 *  Shutdown hook is not called a shutdown in shutdown hook
	 */
	if ((callevel_stat & TCL_SHUTDOWN) == TCL_NULL) {

		p_runosap = NULL;

		/*
		 *  ShutdownHook callout
		 */
		ENTER_CALLEVEL(TCL_SHUTDOWN);
		run_trusted = TRUE;
		LOG_SHUTHOOK_ENTER(ercd);
		ShutdownHook(ercd);
		LOG_SHUTHOOK_LEAVE();
		LEAVE_CALLEVEL(TCL_SHUTDOWN);
	}
}
#endif /* CFG_USE_SHUTDOWNHOOK */

#endif /* TOPPERS_internal_call_shtdwnhk */
