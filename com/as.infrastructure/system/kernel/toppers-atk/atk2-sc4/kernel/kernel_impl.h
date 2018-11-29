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
 *  $Id: kernel_impl.h 504 2015-12-24 01:22:56Z witz-itoyo $
 */

/*
 *		ATK2 inside for standard header file
 *
 *  This header file is the standard header file to be included always in the 
 * source file for the program that you want to configure the kernel
 *
 *  When you include this file from the assembly language source file is, by
 * this to be defined the TOPPERS_MACRO_ONLY, so that except for the non-macro definition
 */

#ifndef TOPPERS_KERNEL_IMPL_H
#define TOPPERS_KERNEL_IMPL_H

/*
 *  Definition for using the renaming for internal kernel
 */
#ifndef TOPPERS_SVC_FUNCCALL
#define TOPPERS_SVC_FUNCCALL
#endif

/*
 *  Applications a common header file
 */
#define OMIT_INCLUDE_OS_LCFG
#include "Os.h"

/* Invalid pointer */
#ifndef NULL
#define NULL		NULL_PTR
#endif /* NULL */

/*
 *  Definition of the macro to perform a type cast
 */
#ifndef CAST
#define CAST(type, val)		((type) (val))
#endif /* CAST */

#ifndef TOPPERS_MACRO_ONLY

/* To optimize, dependent part redefinition can type */
#ifndef OMIT_DATA_TYPE
/*
 *  Type of the internal kernel
 */
typedef uint32	InterruptNumberType;            /* Interrupt number */
typedef uint32	AttributeType;                  /* Object Attributes */
typedef sint32	PriorityType;                   /* priority */
#endif /* OMIT_DATA_TYPE */

typedef void (*FunctionRefType)(void);          /* Start address of the program */

/*
 *  When the error hook OFF, service ID acquisition and parameter acquisition also becomes OFF
 */
#ifdef CFG_USE_ERRORHOOK

#ifdef CFG_USE_PARAMETERACCESS
extern _ErrorHook_Par	_errorhook_par1;
extern _ErrorHook_Par	_errorhook_par2;
extern _ErrorHook_Par	_errorhook_par3;
#endif /* CFG_USE_PARAMETERACCESS */

#endif /* CFG_USE_ERRORHOOK */

/*
 *  Call of ShutdownOS from internal OS
 */
extern void internal_shutdownos(StatusType ercd);

#ifdef CFG_USE_SHUTDOWNHOOK
extern void internal_call_shtdwnhk(StatusType ercd);
#endif /* CFG_USE_SHUTDOWNHOOK */

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  ASSERT macro
 */
#ifndef NDEBUG
#define ASSERT(exp) do {								\
		if (!(exp)) {									\
			fatal_file_name = __FILE__;					\
			fatal_line_num = __LINE__;					\
			internal_shutdownos(E_OS_SYS_ASSERT_FATAL);	\
		}												\
} while (0)

#define ASSERT_NO_REACHED do {						\
		fatal_file_name = __FILE__;					\
		fatal_line_num = __LINE__;					\
		internal_shutdownos(E_OS_SYS_ASSERT_FATAL);	\
} while (0)

#else /* NDEBUG */
#define ASSERT(exp)
#define ASSERT_NO_REACHED
#endif /* NDEBUG */

/*
 *  Definition of the order to compile all the function
 */
#ifdef ALLFUNC
#include "allfunc.h"
#endif /* ALLFUNC */

/*
 *  Definition of application mode value
 */
#define APPMODE_NONE	((AppModeType) 0)   /* None Mode */

/*
 *  At the time of the definition TCL_NULL of the value of the context of the 
 * running (lower 12 bits of callevel_stat), and note that the original call 
 * under the context can not be determined
 */
#define TCL_NULL			UINT_C(0x0000)                          /* It can not be called a system service */
#define TCL_TASK			UINT_C(0x0001)                          /* task */
#define TCL_ISR2			UINT_C(0x0002)                          /* C2ISR */
#define TCL_PROTECT			UINT_C(0x0004)                          /* ProtectionHook */
#define TCL_PREPOST			UINT_C(0x0008)                          /* PreTaskHook锛孭ostTaskHook */
#define TCL_STARTUP			UINT_C(0x0010)                          /* StartupHook */
#define TCL_SHUTDOWN		UINT_C(0x0020)                          /* ShutdownHook */
#define TCL_ERROR			UINT_C(0x0040)                          /* ErrorHook */
/* The hook mask of belonging to the OS application */
#define TCLMASK				UINT_C(0x0fff)                          /* Mask of the bit that indicates the call level */

/*
 *  Definition of the value of the system state (upper 4 bits of the callevel_stat)
 */
#define TSYS_NULL			UINT_C(0x0000)      /* System state clear */
#define TSYS_DISALLINT		UINT_C(0x1000)      /* DisableAllInterrupts in issue */
#define TSYS_SUSALLINT		UINT_C(0x2000)      /* SuspendAllInterrupts in issue */
#define TSYS_SUSOSINT		UINT_C(0x4000)      /* SuspendOSInterrupts in issue */
#define TSYS_ISR1			UINT_C(0x8000)      /* C1ISR Started */
#define TSYSMASK			UINT_C(0xf000)      /* Mask bits indicating system status */


#ifdef CFG_USE_STACKMONITORING
#ifndef STACK_MAGIC_NUMBER
/*
 *  Definition of the magic number for the stack monitoring
 *  Definition of the target-dependent portion is priority
 */
#define STACK_MAGIC_NUMBER	0x4E434553      /* NCES ASCII code (0x4E434553) */
#endif /* STACK_MAGIC_NUMBER */

#ifndef TOPPERS_ISTK_MAGIC_REGION
/* Magic number area acquisition macro for the interrupt stack */
#define TOPPERS_ISTK_MAGIC_REGION(stk, stksz)	(stk)
#endif /* TOPPERS_ISTK_MAGIC_REGION */

#ifndef TOPPERS_SSTK_MAGIC_REGION
/* Magic number area acquisition macro for the trust task stack */
#ifndef USE_TSKINICTXB
#define TOPPERS_SSTK_MAGIC_REGION(p_tinib)	((StackType *) ((p_tinib)->sstk))
#endif /* USE_TSKINICTXB */
#endif /* TOPPERS_SSTK_MAGIC_REGION */

#endif /* CFG_USE_STACKMONITORING */

#define TFN_EXIT_TASK	(TMAX_SVCID - TARGET_SVC_NUM)
#define exit_task		(_kernel_exit_task)

/*
 *  Definition of hook type
 */
#define STARTUP_HOOK	UINT_C(0)
#define SHUTDOWN_HOOK	UINT_C(1)
#define ERROR_HOOK		UINT_C(2)

/*
 *  bit manipulation of callevel_stat
 */
#define ENTER_CALLEVEL(bit)		(callevel_stat |= (bit))
#define LEAVE_CALLEVEL(bit)		(callevel_stat &= (uint16) ~((uint32) bit))


/*
 *  Processing unit that invokes each system service
 */
#define CALLEVEL_ACTIVATETASK				(TCL_TASK | TCL_ISR2)
#define CALLEVEL_TERMINATETASK				(TCL_TASK)
#define CALLEVEL_CHAINTASK					(TCL_TASK)
#define CALLEVEL_SCHEDULE					(TCL_TASK)
#define CALLEVEL_GETTASKID					(TSYS_DISALLINT | TSYS_SUSALLINT | TSYS_SUSOSINT | TCL_TASK | TCL_ISR2 | TCL_ERROR | TCL_PREPOST | TCL_PROTECT)
#define CALLEVEL_GETTASKSTATE				(TSYS_DISALLINT | TSYS_SUSALLINT | TSYS_SUSOSINT | TCL_TASK | TCL_ISR2 | TCL_ERROR | TCL_PREPOST)
#define CALLEVEL_GETRESOURCE				(TCL_TASK | TCL_ISR2)
#define CALLEVEL_RELEASERESOURCE			(TCL_TASK | TCL_ISR2)
#define CALLEVEL_SETEVENT					(TCL_TASK | TCL_ISR2)
#define CALLEVEL_CLEAREVENT					(TCL_TASK)
#define CALLEVEL_GETEVENT					(TCL_TASK | TCL_ISR2 | TCL_ERROR | TCL_PREPOST)
#define CALLEVEL_WAITEVENT					(TCL_TASK)
#define CALLEVEL_GETALARMBASE				(TCL_TASK | TCL_ISR2 | TCL_ERROR | TCL_PREPOST)
#define CALLEVEL_GETALARM					(TCL_TASK | TCL_ISR2 | TCL_ERROR | TCL_PREPOST)
#define CALLEVEL_SETRELALARM				(TCL_TASK | TCL_ISR2)
#define CALLEVEL_SETABSALARM				(TCL_TASK | TCL_ISR2)
#define CALLEVEL_CANCELALARM				(TCL_TASK | TCL_ISR2)
#define CALLEVEL_GETACTIVEAPPMODE			(TCL_TASK | TCL_ISR2 | TCL_ERROR | TCL_PREPOST | TCL_STARTUP | TCL_SHUTDOWN)
#define CALLEVEL_SHUTDOWNOS					(TCL_TASK | TCL_ISR2 | TCL_ERROR | TCL_STARTUP)
#define CALLEVEL_GETISRID					(TSYS_DISALLINT | TSYS_SUSALLINT | TSYS_SUSOSINT | TCL_TASK | TCL_ISR2 | TCL_ERROR | TCL_PROTECT)
#define CALLEVEL_INCREMENTCOUNTER			(TCL_TASK | TCL_ISR2)
#define CALLEVEL_GETCOUNTERVALUE			(TCL_TASK | TCL_ISR2)
#define CALLEVEL_GETELAPSEDVALUE			(TCL_TASK | TCL_ISR2)
#define CALLEVEL_STARTSCHEDULETABLEREL		(TCL_TASK | TCL_ISR2)
#define CALLEVEL_STARTSCHEDULETABLEABS		(TCL_TASK | TCL_ISR2)
#define CALLEVEL_STOPSCHEDULETABLE			(TCL_TASK | TCL_ISR2)
#define CALLEVEL_NEXTSCHEDULETABLE			(TCL_TASK | TCL_ISR2)
#define CALLEVEL_GETSCHEDULETABLESTATUS		(TCL_TASK | TCL_ISR2)
#define CALLEVEL_GETAPPLICATIONID			(TSYS_DISALLINT | TSYS_SUSALLINT | TSYS_SUSOSINT | TCL_TASK | TCL_ISR2 | TCL_ERROR | TCL_PREPOST | TCL_STARTUP | TCL_SHUTDOWN | TCL_PROTECT)
#define CALLEVEL_CALLTRUSTEDFUNCTION		(TCL_TASK | TCL_ISR2)
#define CALLEVEL_CHECKISRMEMORYACCESS		(TCL_TASK | TCL_ISR2 | TCL_ERROR | TCL_PROTECT)
#define CALLEVEL_CHECKTASKMEMORYACCESS		(TCL_TASK | TCL_ISR2 | TCL_ERROR | TCL_PROTECT)
#define CALLEVEL_CHECKOBJECTACCESS			(TCL_TASK | TCL_ISR2 | TCL_ERROR | TCL_PROTECT)
#define CALLEVEL_CHECKOBJECTOWNERSHIP		(TCL_TASK | TCL_ISR2 | TCL_ERROR | TCL_PROTECT)
#define CALLEVEL_GETAPPLICATIONSTATE		(TSYS_DISALLINT | TSYS_SUSALLINT | TSYS_SUSOSINT | TCL_TASK | TCL_ISR2 | TCL_ERROR | TCL_PREPOST | TCL_STARTUP | TCL_SHUTDOWN | TCL_PROTECT)
#define CALLEVEL_DISABLEINTERRUPTSOURCE		(TCL_TASK | TCL_ISR2 | TCL_ERROR | TCL_PREPOST | TCL_STARTUP | TCL_SHUTDOWN | TCL_PROTECT | TSYS_DISALLINT | TSYS_SUSALLINT | TSYS_SUSOSINT)
#define CALLEVEL_ENABLEINTERRUPTSOURCE		(TCL_TASK | TCL_ISR2 | TCL_ERROR | TCL_PREPOST | TCL_STARTUP | TCL_SHUTDOWN | TCL_PROTECT | TSYS_DISALLINT | TSYS_SUSALLINT | TSYS_SUSOSINT)
#define CALLEVEL_GETFAULTYCONTEXT			(TCL_PROTECT)
#define CALLEVEL_IOCSEND					(TCL_TASK | TCL_ISR2)
#define CALLEVEL_IOCWRITE					(TCL_TASK | TCL_ISR2)
#define CALLEVEL_IOCRECEIVE					(TCL_TASK | TCL_ISR2)
#define CALLEVEL_IOCREAD					(TCL_TASK | TCL_ISR2)
#define CALLEVEL_IOCEMPTYQUEUE				(TCL_TASK | TCL_ISR2)
#define CALLEVEL_ALLOWACCESS				(TCL_TASK | TCL_ISR2)
#define CALLEVEL_TERMINATEAPPLICATION		(TCL_TASK | TCL_ISR2)

/*
 *  Other constant value (standard interrupt model)
 */
#define TIPM_ENAALL		UINT_C(0)   /* Interrupt priority mask CANCEL */

/*
 *  Definition of the object attributes (standard interrupt model)
 */
#define ENABLE		UINT_C(0x01)
#define DISABLE		UINT_C(0x00)


/*
 *  Invalid system service ID for OS internal
 */
#define OSServiceId_Invalid		((OSServiceIdType) 0xff)

/*
 *  Declaration of a function, variables of the module that does not have a header file
 */
#ifndef TOPPERS_MACRO_ONLY

#ifdef TOPPERS_StartOS
/*
 *  The number of application mode
 */
extern const AppModeType	tnum_appmode;

#endif /* TOPPERS_StartOS */

/*
 *  Variable for OS execution control (osctl_manage.c)
 */
extern uint16				callevel_stat;  /* Context of running */
extern AppModeType			appmodeid;      /* Application mode ID */

/*
 *  Kernel operating state flag
 */
extern boolean				kerflg;

/*
 *  Flag indicating whether running in privileged mode
 */
extern boolean				run_trusted;

extern boolean				pre_protection_supervised;

/*
 *  Declaration for error hook call (ioctl.c)
 */
#ifdef CFG_USE_ERRORHOOK
extern void call_errorhook(StatusType ercd, OSServiceIdType svcid);
#endif /* CFG_USE_ERRORHOOK */

/*
 *  Post task hooks / pre-task hook
 *  Declaration for the initialization / protection hook call stack monitoring function (osctl.c)
 */
#ifdef CFG_USE_POSTTASKHOOK
extern void call_posttaskhook(void);
#endif /* CFG_USE_POSTTASKHOOK */

#ifdef CFG_USE_PRETASKHOOK
extern void call_pretaskhook(void);
#endif /* CFG_USE_PRETASKHOOK */

#ifdef CFG_USE_STACKMONITORING
extern void init_stack_magic_region(void);
#endif /* CFG_USE_STACKMONITORING */

extern void call_protectionhk_main(StatusType protection_error);
#define call_protectionhk_main_stkchg call_protectionhk_main

/*
 *  Initialization of each module
 */
extern void object_initialize(void);

/*
 *  End processing of each module
 */
extern void object_terminate(void);

/*
 *  Stack area for the non-task context
 */
extern const MemorySizeType	_ostksz;        /* The size of the stack area (rounded value) */
extern StackType * const	_ostk;          /* The start address of the stack area */
#ifdef TOPPERS_OSTKPT
extern StackType * const	_ostkpt;        /* The initial value of the stack pointer */
#endif /* TOPPERS_OSTKPT */
/*
 *  Timing protection for time of frame
 */
typedef struct time_frame_time {
	uint32		tfcount;
	TickType	tftick;
} TFTIME;

#endif /* TOPPERS_MACRO_ONLY */

#endif /* TOPPERS_KERNEL_IMPL_H */
