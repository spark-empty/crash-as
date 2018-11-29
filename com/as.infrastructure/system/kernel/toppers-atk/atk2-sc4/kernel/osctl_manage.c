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
 *  $Id: osctl_manage.c 504 2015-12-24 01:22:56Z witz-itoyo $
 */

/*
 *		OS management module
 */

#include "kernel_impl.h"
#include "check.h"
#include "interrupt.h"

/*
 *  The default definition of the trace log macro
 */
#ifndef LOG_GETAAM_ENTER
#define LOG_GETAAM_ENTER()
#endif /* LOG_GETAAM_ENTER */

#ifndef LOG_GETAAM_LEAVE
#define LOG_GETAAM_LEAVE(mode)
#endif /* LOG_GETAAM_LEAVE */

#ifndef LOG_STAOS_ENTER
#define LOG_STAOS_ENTER(mode)
#endif /* LOG_STAOS_ENTER */

#ifndef LOG_STAOS_LEAVE
#define LOG_STAOS_LEAVE()
#endif /* LOG_STAOS_LEAVE */

#ifndef LOG_STAHOOK_ENTER
#define LOG_STAHOOK_ENTER()
#endif /* LOG_STAHOOK_ENTER */

#ifndef LOG_STAHOOK_LEAVE
#define LOG_STAHOOK_LEAVE()
#endif /* LOG_STAHOOK_LEAVE */

#ifdef TOPPERS_StartOS

/*
 *  Variable for OS execution control
 */
uint16		callevel_stat = 0U;             /* Context of running */
AppModeType	appmodeid;                      /* Application mode ID */

/*
 *  Kernel operating state flag
 */
boolean		kerflg = FALSE;

/*
 *  Flag indicating whether running in privileged mode
 */
boolean		run_trusted;

boolean		pre_protection_supervised;

/*
 *  File name, variable for the reference line number
 */
const char8	*fatal_file_name = NULL;                    /* file name */
sint32		fatal_line_num = 0;                         /* line number */

/*
 *  Starting the OS
 */

void
StartOS(AppModeType Mode)
{

	LOG_STAOS_ENTER(Mode);
	if (kerflg != FALSE) {
		/* During OS boot it calls the error hook */
#ifdef CFG_USE_ERRORHOOK
		x_nested_lock_os_int();
#ifdef CFG_USE_PARAMETERACCESS
		_errorhook_par1.mode = Mode;
#endif /* CFG_USE_PARAMETERACCESS */
		call_errorhook(E_OS_ACCESS, OSServiceId_StartOS);
		x_nested_unlock_os_int();
#endif /* CFG_USE_ERRORHOOK */
	}
	else {

		/* The transition to all interrupt disabled state */
		x_lock_all_int();

#ifdef CFG_USE_STACKMONITORING
		/*
		 *  Initialization of stack monitoring function
		 *  Initialization of the magic number area for stack monitoring function
		 */
		init_stack_magic_region();
#endif /* CFG_USE_STACKMONITORING */

		/* Setting the application mode */
		appmodeid = Mode;

		/* Initialization of target-dependent */
		target_initialize();

		/* Initialization of each module */
		object_initialize();

		callevel_stat = TCL_NULL;

		/* Kernel running */
		kerflg = TRUE;

		run_trusted = TRUE;

		/*
		 *  If Mode was incorrect, this time to perform the OS 
		 * shutdown, start-up hook is not called
		 */
		if (Mode >= tnum_appmode) {
			/*
			 *  and release all interrupts disabled state to the OS interrupt
			 * disable state before calling internal_shutdownos
			 */
			x_nested_lock_os_int();
			x_unlock_all_int();
			internal_shutdownos(E_OS_MODE);
		}

#ifdef CFG_USE_STARTUPHOOK
		/* The OS interrupt disable state, release all interrupt disabled state */
		x_nested_lock_os_int();
		x_unlock_all_int();

		/*
		 *  StartupHook callout
		 */
		ENTER_CALLEVEL(TCL_STARTUP);
		LOG_STAHOOK_ENTER();
		StartupHook();
		LOG_STAHOOK_LEAVE();
		LEAVE_CALLEVEL(TCL_STARTUP);

		/* Original interrupt mask priority and to all the interrupt disable state */
		x_lock_all_int();
		x_nested_unlock_os_int();
#endif /* CFG_USE_STARTUPHOOK */


		ENTER_CALLEVEL(TCL_TASK);
		LOG_STAOS_LEAVE();
		start_dispatch();
		ASSERT_NO_REACHED;
	}
}

#endif /* TOPPERS_StartOS */

/*
 *  Acquisition of the current application mode
 */
#ifdef TOPPERS_GetActiveApplicationMode

AppModeType
GetActiveApplicationMode(void)
{
	AppModeType	appmode;
	StatusType	ercd;

	LOG_GETAAM_ENTER();
	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_GETACTIVEAPPMODE);

	appmode = appmodeid;

  exit_finish:
	LOG_GETAAM_LEAVE(appmode);
	return(appmode);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
	/*
	 *  When an error occurs but INVALID_APPMODETYPE is returned, 
	 * in order to distinguish whether the error does not exist 
	 * C2ISR running what has occurred, it is referred to as the error hook
	 */
	call_errorhook(ercd, OSServiceId_GetActiveApplicationMode);
	x_nested_unlock_os_int();
#endif /* CFG_USE_ERRORHOOK */

	/* exit_no_errorhook: */
	appmode = INVALID_APPMODETYPE;
	goto exit_finish;
}

#endif /* TOPPERS_GetActiveApplicationMode */

/*
 *  The end of the OS
 */
#ifdef TOPPERS_ShutdownOS

void
ShutdownOS(StatusType Error)
{
	StatusType ercd = Error;

	/*
	 *  If the caller belongs OS application of trust / untrusted check caller 
	 * reliable function is a hook I run ShutdownOS ()
	 */
	if (run_trusted == FALSE) {
		/* It is called an error hook when it is called from the untrusted */
#ifdef CFG_USE_ERRORHOOK
		x_nested_lock_os_int();
#ifdef CFG_USE_PARAMETERACCESS
		_errorhook_par1.error = Error;
#endif /* CFG_USE_PARAMETERACCESS */
		call_errorhook(E_OS_ACCESS, OSServiceId_ShutdownOS);
		x_nested_unlock_os_int();
#endif /* CFG_USE_ERRORHOOK */
	}
	else {

		/*
		 *  Even if you call from unauthorized processing unit, 
		 * as those that called ShutdownOS the Error as E_OS_SHUTDOWN_FATAL, 
		 * to perform the shutdown process
		 */
		if (((callevel_stat & TCLMASK) | (CALLEVEL_SHUTDOWNOS)) != (CALLEVEL_SHUTDOWNOS)) {
			ercd = E_OS_SHUTDOWN_FATAL;
		}

		/*
		 *  If the error code that is not defined by the OS is specified, 
		 * as that called ShutdownOS the Error as E_OS_SHUTDOWN_FATAL, 
		 * it does shutdown process
		 */
		if (ercd > ERRCODE_NUM) {
			ercd = E_OS_SHUTDOWN_FATAL;
		}

		internal_shutdownos(ercd);
	}
}
#endif /* TOPPERS_ShutdownOS */

/*
 *  Acquisition of a processing unit that caused the protection violation
 */
#ifdef TOPPERS_GetFaultyContext

FaultyContextType
GetFaultyContext(void)
{
	FaultyContextType faultycontext = FC_INVALID;

#ifdef CFG_USE_PROTECTIONHOOK
	if ((callevel_stat & CALLEVEL_GETFAULTYCONTEXT) != 0U) {

		/* Occur outside C1ISR */
		if ((callevel_stat & TSYS_ISR1) == 0U) {
			if ((callevel_stat & (TCL_ERROR | TCL_PREPOST | TCL_STARTUP | TCL_SHUTDOWN)) != 0U) {
				/* Raised in the hook */
				faultycontext = FC_SYSTEM_HOOK;
			}
			else if ((callevel_stat & TCL_ISR2) != 0U) {
				if (p_runisr->calltfn != FALSE) {
					/* Raised in trust function you call from C2ISR */
					faultycontext = FC_TRUSTED_FUNC;
				}
				else {
					faultycontext = FC_C2ISR;
				}
			}
			else if ((callevel_stat & TCL_TASK) != 0U) {
				if (p_runtsk->calltfn != FALSE) {
					/* Raised in trust function you call from the task */
					faultycontext = FC_TRUSTED_FUNC;
				}
				else {
					faultycontext = FC_TASK;
				}
			}
			else {
				/* Otherwise, it does not perform processing (return value: FC_INVALID) */
			}
		}
	}
#endif /* CFG_USE_PROTECTIONHOOK */

	return(faultycontext);
}
#endif /* TOPPERS_GetFaultyContext */
