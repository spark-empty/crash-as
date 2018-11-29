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
 *  $Id: osap.h 504 2015-12-24 01:22:56Z witz-itoyo $
 */

/*
 *		OS application management function
 */

#ifndef TOPPERS_OSAP_H
#define TOPPERS_OSAP_H

/*
 *  OS application attributes
 */
#define TA_NONTRUSTED			(FALSE)
#define TA_TRUSTED				(TRUE)

/*
 *  Macro for extracting OSAPINIB from OS application ID
 */
#define get_osapinib(osapid)	(&(osapinib_table[(osapid)]))

/*
 *  Macro for extracting OSAPCB from OSAPID
 */
#define get_osapcb(osapid)		(&(osapcb_table[(osapid)]))

/*
 *  Macro for taking out the OS application ID from OSAPCB
 */
#define OSAPID(p_osapcb)	((ApplicationType) ((p_osapcb) - osapcb_table))

#ifndef TOPPERS_MACRO_ONLY

typedef struct os_application_control_block OSAPCB;
#include "task.h"

/*
 *  OS application initialization block
 *
 *  Information about the OS applications, it is defined as the OS application 
 * control block
 *  The other object is constituted by a control block placed in the initialization 
 * block and RAM put in ROM, since the information on the OS application not be 
 * changed at runtime, using the initialization block as a control block
 *
 *  In ATK2-SC3, but to have the information for memory protection function,
 * since the memory protection implementation is dependent on the CPU, the
 * main body of the memory protection information is to have the machine-dependent parts
 */
typedef struct os_application_initialization_block {
	TCB		*p_restart_tcb;                             /* A pointer to the restart task management block of OSAP */
	boolean	osap_trusted;                               /* OS application attributes */
	uint32	btptn;                                      /* Of non-confidence OS application bit pattern */
#ifndef OMIT_OSAPMPUINFOB
	OSAPMPUINFOB osap_mpu;                              /* CPU information of OS applications */
#endif

} OSAPINIB;

/*
 *  OS application management block
 */
struct os_application_control_block {
	const OSAPINIB			*p_osapinib;                /* A pointer to the initialization block */
	ApplicationStateType	osap_stat;                  /* OSAP state */
};

/*
 *  Declaration of the variable to hold the number of OS application
 */
extern const ApplicationType			tnum_osap;      /* The number of OS applications */

extern const TrustedFunctionIndexType	tnum_tfn;       /* The number of trust function */

typedef StatusType (*TrustedFunctionRefType)(TrustedFunctionIndexType FunctionIndex,
											 TrustedFunctionParameterRefType FunctionParams);

/*
 *  Trust function initialization block
 */
typedef struct trusted_function_initialization_block {
	TrustedFunctionRefType	trs_func;   /* Start address of the trust function */
	MemorySizeType			tf_stksz;   /* Stack size */
	TickType				tf_budget;  /* Trust function execution time budget */
} TFINIB;

/*
 *  OSAPCB area 
 */
extern OSAPCB			osapcb_table[];

/*
 *  OS application running
 */
extern OSAPCB			*p_runosap;

/*
 *  External references OSAPINIB (kernel_mem.c)
 */
extern const OSAPINIB	osapinib_table[];

/*
 *  External references TFINIB
 */
extern const TFINIB		tfinib_table[];

/*
 *  Function to terminate / restart the specified OSAP (also called from the protection hook)
 */
extern void force_term_osap(OSAPCB *p_osapcb, RestartType RestartOption);

/*
 *  Initialization of OS application management module
 */
extern void osap_initialize(void);

/* target dependent statck and memory check */
extern StatusType trustedfunc_stack_check(MemorySizeType sz);
extern AccessType probe_trusted_osap_mem(MemoryStartAddressType sadr, MemoryStartAddressType eadr);

#endif /* TOPPERS_MACRO_ONLY */

#endif /* TOPPERS_OSAP_H_ */
