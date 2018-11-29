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
 *  $Id: interrupt.h 504 2015-12-24 01:22:56Z witz-itoyo $
 */

/*
 *		Interrupt management functions
 */

#ifndef TOPPERS_INTERRUPT_H
#define TOPPERS_INTERRUPT_H

#include "resource.h"
#include "osap.h"
#include "timingprotection.h"

/*
 *  Definition of priority values (internal representation)
 */
#define TPRI_MINISR		(-1)            /* Lowest interrupt priority */

/*
 *  Macro for taking out the ISRCB by ISRID
 */
#define get_isrcb(isrid)	(&(isrcb_table[(isrid)]))

/*
 *  Macro for extracting ISRID from ISRCB 
 */
#define ISR2ID(p_isrcb)	((ISRType) ((p_isrcb) - isrcb_table))

#ifndef OMIT_INITIALIZE_INTERRUPT

/*
 *  Interrupt request line initialization block
 */
typedef struct interrupt_request_initialization_block {
	InterruptNumberType	intno;          /* Interrupt number */
	AttributeType		intatr;         /* Interrupt attribute */
	PriorityType		intpri;         /* Interrupt priority */
#if defined(TOPPERS_CFG1_OUT) || defined(CFG_USE_STACKMONITORING)
	MemorySizeType remain_stksz;        /* Stack size stack remaining check scheme */
#endif /* defined(TOPPERS_CFG1_OUT) || defined(CFG_USE_STACKMONITORING) */
} INTINIB;

/*
 *  The number of interrupt request line 
 */
extern const InterruptNumberType	tnum_intno;

/*
 *  Interrupt request line initialization block area 
 */
extern const INTINIB				intinib_table[];

/*
 *  Macro to determine the interrupt number from ISRCB
 */
#define GET_INTNO(p_isrcb)	((p_isrcb)->p_isrinib->p_intinib->intno)

/*
 *  Macro to determine the interrupt priority from ISRCB
 */
#define GET_INTPRI(p_isrcb)	((p_isrcb)->p_isrinib->p_intinib->intpri)

#endif /* OMIT_INITIALIZE_INTERRUPT */

typedef struct isr_initialization_block {
	const INTINIB	*p_intinib;     /* Pointer to the interrupt request line initialization block */
	OSAPCB			*p_osapcb;      /* Management block belongs to OS application */
	uint32			acsbtmp;        /* Permissions OS application bitmap */
	TFTIME			time_frame;     /* Minimum arrival time */
} ISRINIB;

typedef struct isr_control_block {
	const ISRINIB	*p_isrinib;
	RESCB			*p_lastrescb;   /* A pointer to the last acquired resource management block */
#ifdef CFG_USE_PROTECTIONHOOK
	boolean	calltfn;                /* Trust function call in the flag */
#endif /* CFG_USE_PROTECTIONHOOK */
	TPACB 			tpacb;          /* Arrival interval protection protection management block */
} ISRCB;

/*
 *  Declaration of the variable that holds the C2ISR number
 */
extern const ISRType	tnum_isr2;                         /* Number of C2ISR */

/*
 *  Of initialization block of C2ISR area
 */
extern const ISRINIB	isrinib_table[];

/*
 *  C2ISR area of the management block 
 */
extern ISRCB			isrcb_table[];

/*
 *  C2ISR running
 *
 *  When you are not running the C2ISR will be to NULL
 */
extern ISRCB			*p_runisr;

/*
 *  SuspendAllInterrupts Nesting number
 */
extern uint8			sus_all_cnt;

/*
 *  SuspendOSInterrupts Nesting number
 */
extern uint8			sus_os_cnt;

/*
 *  Interrupt priority of the first call to SuspendOSInterrupts
 */
extern PriorityType		sus_os_prevpri;

/*
 * OS interrupt disable time budget
 */
extern const TickType	osinterruptlock_budget;

/*
 *  The difference between the remaining time of the OS interrupt disable time 
 * budget and the original monitoring items
 */
extern TickType			os_difftime;

/*
 *  Previous monitoring items
 */
extern MonitoringType	os_saved_watchtype;

/*
 *  Initialization of interrupt management functions
 */
extern void interrupt_initialize(void);

/*
 *  Forced release of interrupt disabled
 */

extern void release_interrupts(OSServiceIdType serviceId);

/*
 *  C2ISR at the end of the check function
 */
extern void exit_isr2(void);

/* target dependent interrupt access */
extern void x_nested_lock_os_int(void);
extern void x_nested_unlock_os_int(void);
extern void x_lock_all_int(void);
extern void x_unlock_all_int(void);
extern void x_config_int(InterruptNumberType intno,AttributeType attr,PriorityType prio);
extern boolean x_is_called_in_c1isr(void);
extern void    x_set_ipm_c2isr_disable(void);
extern boolean target_is_int_controllable(InterruptNumberType intno);
extern void    x_enable_int(InterruptNumberType intno);
extern void    x_disable_int(InterruptNumberType intno);

extern void x_set_ipm(PriorityType prio);
extern PriorityType x_get_ipm(void);

#endif /* TOPPERS_INTERRUPT_H */
