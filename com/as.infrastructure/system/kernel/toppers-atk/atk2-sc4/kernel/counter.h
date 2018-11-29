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
 *  $Id: counter.h 504 2015-12-24 01:22:56Z witz-itoyo $
 */

/*
 *		Counter function
 */

#ifndef TOPPERS_COUNTER_H
#define TOPPERS_COUNTER_H

#include "queue.h"

/*
 *  The definition of the counter state
 *  IncrementCounter nest prevention measures
 */
#define CS_NULL		(FALSE)         /* In the non-operation */
#define CS_DOING	(TRUE)          /* During operation */

/*
 *  Macro for taking out the counter management block from the counter IC
 */
#define get_cntcb(cntid)	(&(cntcb_table[(cntid)]))

/*
 *  Hardware counter or check for macros in counter ID
 */
#define is_hwcnt(cntid)		((cntid) < tnum_hardcounter)

/*
 *  Macro for extracting counter ID from CNTCB
 */
#define CNTID(p_cntcb)	((CounterType) ((p_cntcb) - cntcb_table))

/*
 *  Attribute of expiration action
 */
#define ACTIVATETASK		UINT_C(0x01)    /* Task start */
#define SETEVENT			UINT_C(0x02)    /* Event set */
#define CALLBACK			UINT_C(0x04)    /* Callback */
#define INCREMENTCOUNTER	UINT_C(0x08)    /* Counter increment */

/*
 *  Automatic start of attributes
 */
#define ABSOLUTE			UINT_C(0x10)    /* Absolute value start */
#define RELATIVE			UINT_C(0x20)    /* relative value start */

/*
 *  Each hardware counter processing function type
 */
typedef void (*HardwareCounterInitRefType)(TickType maxval, TimeType nspertick);    /* Initialization function type */
typedef void (*HardwareCounterStartRefType)(void);                                  /* Start function type */
typedef void (*HardwareCounterStopRefType)(void);                                   /* Stop function type */
typedef void (*HardwareCounterSetRefType)(TickType exprtick);                       /* Time setting function type */
typedef TickType (*HardwareCounterGetRefType)(void);                                /* Time acquisition function type */
typedef void (*HardwareCounterCancelRefType)(void);                                 /* Set time cancel function type */
typedef void (*HardwareCounterTriggerRefType)(void);                                /* Force the interrupt request function type */
typedef void (*HardwareCounterIntClearRefType)(void);                               /* Interrupt request clear function type */
typedef void (*HardwareCounterIntCancelRefType)(void);                              /* Interrupt request cancellation function type */
typedef void (*HardwareCounterIncrementRefType)(void);                              /* Increment function type */

/*
 *  Hardware counter processing function type
 */
typedef struct hardware_counter_initialization_block {
	HardwareCounterInitRefType		init;               /* Initialization function pointer */
	HardwareCounterStartRefType		start;              /* Start function pointer */
	HardwareCounterStopRefType		stop;               /* Stop function pointer */
	HardwareCounterSetRefType		set;                /* Time setting function pointer */
	HardwareCounterGetRefType		get;                /* Time acquisition function pointer*/
	HardwareCounterCancelRefType	cancel;             /* Time cancellation function pointer */
	HardwareCounterTriggerRefType	trigger;            /* Force interrupt request function pointer */
	HardwareCounterIntClearRefType	intclear;           /* Interrupt request clear function type */
	HardwareCounterIntCancelRefType	intcancel;          /* Interrupt request cancellation function type */
	HardwareCounterIncrementRefType	increment;          /* Increment function pointer */
	TimeType						nspertick;          /* Weight of one tick of the hardware counter(ns unit) */
} HWCNTINIB;

/*
 *  Counter initialization block
 */
typedef struct counter_initialization_block {
	TickType	maxval;                                 /* The maximum value of the counter */
	TickType	maxval2;                                /* 2 times the maximum value of the counter+1 */
	TickType	tickbase;                               /* Is not used in the OS inside, the value that the user is free to use */
	TickType	mincyc;                                 /* The minimum value of the cycle */
	OSAPCB		*p_osapcb;                              /* Management block belongs to OS application */
	uint32		acsbtmp;                                /* Permissions OS application bitmap*/
} CNTINIB;

/*
 *  Counter management block
 */
typedef struct counter_control_block {
	QUEUE							cntexpque;          /* Counter expiration queue */
	const CNTINIB					*p_cntinib;         /* Counter initialization block pointer */
	TickType						curval;             /* Current tick of counter */
	struct counter_control_block	*p_prevcntcb;       /* A pointer to the acquired counter management block before */
	boolean							cstat;              /* Counter-operation flag */
	boolean							hwset;              /* Hardware counter set flag */
} CNTCB;

/*
 *  Counter expiration information
 */
typedef struct counter_expire_info CNTEXPINFO;

/*
 *  Expiration processing function type
 */
typedef void (*EXPFP)(CNTEXPINFO *p_cntexpinfo, const CNTCB *p_cntcb);

/*
 *  Counter expiration information
 */
struct counter_expire_info {
	QUEUE		cntexpque;                              /* Counter expiration queue (need to enter at the top of the structure) */
	TickType	expiretick;                             /* The expiration to counter Ueno tick value */
	EXPFP		expirefunc;                             /* Expiration processing function pointer */
};


/*
 *  Declaration of the variable to hold the number of hardware counter
 */
extern const CounterType	tnum_hardcounter;

/*
 *  Declaration of the variable to hold the number of counter
 */
extern const CounterType	tnum_counter;

/*
 *  Area of counter initialization block
 */
extern const CNTINIB		cntinib_table[];

/*
 *  Of counter management block area
 */
extern CNTCB				cntcb_table[];

/*
 *  Hardware counter processing function table
 */
extern const HWCNTINIB		hwcntinib_table[];

/*
 *  Addition of the tick value
 */
LOCAL_INLINE TickType
add_tick(TickType val, TickType incr, TickType maxval2)
{
	TickType result;
	/*
	 *  Although straightforward condition is val + incr <= maxval2, 
	 * in this condition, since the val + incr is not properly determine 
	 * if it exceeds the range represented by TickType, it has the 
	 * following conditional expression
	 */
	if (incr <= (maxval2 - val)) {
		result = val + incr;
	}
	else {
		/*
		 *  By equation below, but there is a case in which val + incr 
		 * and maxval2 + 1 exceeds the range expressed by TickType, no 
		 * problem for correct calculated values are also overflows
		 */
		result = (val + incr) - (maxval2 + 1U);
	}
	return(result);
}

/*
 *  The difference between the tick value
 */
LOCAL_INLINE TickType
diff_tick(TickType val1, TickType val2, TickType maxval2)
{
	TickType result;

	if (val1 >= val2) {
		result = val1 - val2;
	}
	else {
		/*
		 *  In formula below, val1 - val2 and although maxval2 + 1 in 
		 * some cases exceeds the range represented by TickType, permissible 
		 * for the correct calculated values are also overflows
		 */
		result = (val1 - val2) + (maxval2 + 1U);
	}
	return(result);
}

/*
 *  The current value of the counter acquisition
 *  In the case of software counter, in the case of a hardware counter 
 * that returns the curval data of CNTCB, and returns the latest current time
 */
LOCAL_INLINE TickType
get_curval(const CNTCB *p_cntcb, CounterType cntid)
{
	TickType curval;

	/* Acquisition of counter value */
	if (is_hwcnt(cntid)) {
		curval = (hwcntinib_table[cntid].get)();
	}
	else {
		curval = p_cntcb->curval;
	}

	return(curval);
}

/*
 *  Counter value acquisition from the specified relative time (obtained from API)
 */
extern TickType get_reltick(const CNTCB *p_cntcb, TickType relval);

/*
 *  The specified counter value acquisition from the absolute time (obtained from API)
 */
extern TickType get_abstick(const CNTCB *p_cntcb, TickType absval);

/*
 *  Initialization of counter function
 */
extern void counter_initialize(void);

/*
 *  End processing of counter function
 */
extern void counter_terminate(void);

/*
 *  Insertion into the counter expiration queue
 */
extern void insert_cnt_expr_que(CNTEXPINFO *p_cntexpinfo, CNTCB *p_cntcb);

/*
 *  Delete from the counter expiration queue
 */
extern void delete_cnt_expr_que(CNTEXPINFO *p_cntexpinfo, CNTCB *p_cntcb);

/*
 *  Expiration processing of counter
 */
extern void expire_process(CNTCB *p_cntcb, CounterType cntid);

/*
 *  Hardware counter expiration processing
 */
extern void notify_hardware_counter(CounterType cntid);

/*
 *  Increment of the counter
 *
 *  Conditions: it is called in the interrupt disabled state
 */
extern StatusType incr_counter_process(CNTCB *p_cntcb, CounterType CounterID);

/*
 *  Increment of the counter by the alarm expiration
 *
 *  Conditions: it is called in the interrupt disabled state
 */
extern StatusType incr_counter_action(OSAPCB *p_expire_osapcb, CounterType CounterID);

/*
 *  Forced termination of counter that OSAP belongs
 */
extern void force_term_osap_counter(OSAPCB *p_osapcb);

#endif /* TOPPERS_COUNTER_H */
