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
 *  $Id: counter.c 504 2015-12-24 01:22:56Z witz-itoyo $
 */

/*
 *		Counter control module
 */

#include "kernel_impl.h"
#include "task.h"
#include "counter.h"
#include "interrupt.h"

/*
 *  The default definition of the trace log macro
 */
#ifndef LOG_INCCNT_ENTER
#define LOG_INCCNT_ENTER(cntid)
#endif /* LOG_INCCNT_ENTER */

#ifndef LOG_INCCNT_LEAVE
#define LOG_INCCNT_LEAVE(ercd)
#endif /* LOG_INCCNT_LEAVE */

#ifndef LOG_GETCNT_ENTER
#define LOG_GETCNT_ENTER(cntid, p_val)
#endif /* LOG_GETCNT_ENTER */

#ifndef LOG_GETCNT_LEAVE
#define LOG_GETCNT_LEAVE(ercd, val)
#endif /* LOG_GETCNT_LEAVE */

#ifndef LOG_GETECT_ENTER
#define LOG_GETECT_ENTER(cntid, val, p_eval)
#endif /* LOG_GETECT_ENTER */

#ifndef LOG_GETECT_LEAVE
#define LOG_GETECT_LEAVE(ercd, val, eval)
#endif /* LOG_GETECT_LEAVE */

/*
 *  Insertion into the counter expiration queue
 */
#ifdef TOPPERS_insert_cnt_expr_que

void
insert_cnt_expr_que(CNTEXPINFO *p_cntexpinfo, CNTCB *p_cntcb)
{
	TickType	enqval, curval;
	QUEUE		*next;
	CounterType cntid;

	enqval = p_cntexpinfo->expiretick;

	/*
	 *  A reference point for determining the insertion position to the counter expired queue
	 *
	 *  In the case of hardware counter, the reference point for determining the insertion
     * position to the counter expiration queue using the values that are updated at the 
	 * time of expiration processing, does not get the current value from the hardware 
	 * (tick value on the hardware counter has expired but if it is not already running 
	 * the expiration process, since the reference for the insertion position is shifted)
	 */
	curval = p_cntcb->curval;

	/* Insert location of the search */
	next = p_cntcb->cntexpque.p_next;

	if (curval < enqval) {
		/* If the counter of the overflow does not occur */
		while ((next != &(p_cntcb->cntexpque)) &&
			   (curval <= ((CNTEXPINFO *) next)->expiretick) &&
			   (((CNTEXPINFO *) next)->expiretick <= enqval)) {
			next = next->p_next;
		}
	}
	else {
		/* If a counter overflow occurs */
		while ((next != &(p_cntcb->cntexpque)) &&
			   ((curval <= ((CNTEXPINFO *) next)->expiretick)
				|| (((CNTEXPINFO *) next)->expiretick <= enqval))) {
			next = next->p_next;
		}
	}

	queue_insert_prev(next, &(p_cntexpinfo->cntexpque));

	/*
	 *  If you have inserted into a hardware counter and top, there is a need 
	 * to re-set the expiration time to the hardware counter again
	 */
	cntid = CNTID(p_cntcb);
	if (is_hwcnt(cntid) && (p_cntcb->cntexpque.p_next == &(p_cntexpinfo->cntexpque))) {

		/* Cancel the time currently set */
		(hwcntinib_table[cntid].cancel)();

		/* The re-set to the inserted time to top */
		(hwcntinib_table[cntid].set)(enqval);
		p_cntcb->hwset = TRUE;

		/*
		 *  The check has passed the following expiration time during the reconfiguration
		 *
		 *  If it has passed, if the forced interrupt by executing an expiration process
		 * also time that was set and the get of time are the same, it is assumed to have 
		 * missed in the hardware, it is not missed by the hardware to generate a forced 
		 * interrupt no problem even caused the forced interruption in the case
		 */
		if (diff_tick((hwcntinib_table[cntid].get)(), enqval,
					  p_cntcb->p_cntinib->maxval2) <= p_cntcb->p_cntinib->maxval) {
			/* Cancel the time currently set */
			(hwcntinib_table[cntid].cancel)();
			/* Generate a forced interruption */
			(hwcntinib_table[cntid].trigger)();
		}
	}
}

#endif /* TOPPERS_insert_cnt_expr_que */

/*
 *  Delete from the counter expiration queue
 */
#ifdef TOPPERS_delete_cnt_expr_que

void
delete_cnt_expr_que(CNTEXPINFO *p_cntexpinfo, CNTCB *p_cntcb)
{
	CounterType cntid;
	QUEUE		*p_cntexpque;

	/* Top queue retention of before you remove the expiration processing from the counter queue */
	p_cntexpque = p_cntcb->cntexpque.p_next;

	queue_delete(&(p_cntexpinfo->cntexpque));
	queue_initialize(&(p_cntexpinfo->cntexpque));

	/*
	 *  Hardware counter and expiration processing to be deleted in the case of
     * the head of the counter expiration, to cancel the timer
	 */
	cntid = CNTID(p_cntcb);
	if (is_hwcnt(cntid) && (p_cntcb->cntexpque.p_next != p_cntexpque)) {

		/* Cancel the time currently set */
		(hwcntinib_table[cntid].cancel)();

		/* Cancel the interrupt request pending */
		(hwcntinib_table[cntid].intcancel)();

		/*
		 *  after the expiration processing Delete specified in p_cntexpinfo, 
		 * to set the expiration point of counter expiration following expiration processing
		 */
		if (queue_empty(&(p_cntcb->cntexpque)) == FALSE) {

			/* The re-set to the inserted time to top */
			(hwcntinib_table[cntid].set)(((CNTEXPINFO *) p_cntcb->cntexpque.p_next)->expiretick);
			p_cntcb->hwset = TRUE;

			/*
			 * The check has passed the following expiration time during the reconfiguration
			 *
			 *  If it has passed, if the forced interrupt by executing an expiration process 
			 * also time that was set and the get of time are the same, it is assumed to have 
			 * missed in the hardware, it is not missed by the hardware to generate a forced 
			 * interrupt no problem even caused the forced interruption in the case
			 */
			if (diff_tick((hwcntinib_table[cntid].get)(),
						  ((CNTEXPINFO *) p_cntcb->cntexpque.p_next)->expiretick,
						  p_cntcb->p_cntinib->maxval2) <= p_cntcb->p_cntinib->maxval) {
				/* Cancel the time currently set */
				(hwcntinib_table[cntid].cancel)();
				/* Generate a forced interruption */
				(hwcntinib_table[cntid].trigger)();
			}
		}
	}

}

#endif /* TOPPERS_delete_cnt_expr_que */

/*
 *  Initialization of counter function
 */
#ifdef TOPPERS_counter_initialize

void
counter_initialize(void)
{
	CounterType	i;
	CNTCB		*p_cntcb;

	for (i = 0U; i < tnum_counter; i++) {
		p_cntcb = &(cntcb_table[i]);
		p_cntcb->p_cntinib = &(cntinib_table[i]);
		p_cntcb->curval = 0U;
		p_cntcb->p_prevcntcb = NULL;
		queue_initialize(&(p_cntcb->cntexpque));
		p_cntcb->cstat = CS_NULL;
	}

	for (i = 0U; i < tnum_hardcounter; i++) {
		(hwcntinib_table[i].init)(cntinib_table[i].maxval2,
								  hwcntinib_table[i].nspertick);
		(hwcntinib_table[i].start)();
	}

}

#endif /* TOPPERS_counter_initialize */

/*
 *  End processing of counter function
 */
#ifdef TOPPERS_counter_terminate

void
counter_terminate(void)
{
	CounterType i;

	for (i = 0U; i < tnum_hardcounter; i++) {
		(hwcntinib_table[i].stop)();
	}
}

#endif /* TOPPERS_counter_terminate */

/*
 *  Counter value acquisition from the specified relative time (obtained from API)
 *
 *  Return as the current value and the return value the updated value summation 
 * the passed-in relative value of the specified counter
 */
#ifdef TOPPERS_get_reltick

TickType
get_reltick(const CNTCB *p_cntcb, TickType relval)
{
	CounterType	cntid;
	TickType	result;
	TickType	curval;

	cntid = CNTID(p_cntcb);

	curval = get_curval(p_cntcb, cntid);

	/* And calculates the time that has passed a specified offset from the current time */
	result = add_tick(curval, relval, p_cntcb->p_cntinib->maxval2);

	return(result);
}

#endif /* TOPPERS_get_reltick */

/*
 *  The specified counter value acquisition from the absolute time (obtained from API)
 *
 *  It converts the absolute value that was passed as an argument to 
 * the current value of the specified counter to return the updated value as the return value
 */
#ifdef TOPPERS_get_abstick

TickType
get_abstick(const CNTCB *p_cntcb, TickType absval)
{
	CounterType	cntid;
	TickType	result;
	TickType	curval;
	TickType	nextval;

	cntid = CNTID(p_cntcb);

	curval = get_curval(p_cntcb, cntid);

	/* convert to absolute time considering the maxval2 */
	nextval = absval +  p_cntcb->p_cntinib->maxval + 1U;

	if (curval < (p_cntcb->p_cntinib->maxval + 1U)) {
		/*
		 *  If the current value of the counter is between 0~maxval, because 
		 * it is not yet reached the absolute time, it returns the absolute time
		 */
		if (absval > curval) {
			result = absval;
		}
		else {
			result = nextval;
		}
	}
	else {
		/*
		 *  If the current value of the counter is between maxval~maxval2, 
		 * because beyond the absolute that maxval2 taken into consideration, 
		 * and returns the absolute time
		 */
		if (nextval <= curval) {
			result = absval;
		}
		else {
			result = nextval;
		}
	}

	return(result);
}

#endif /* TOPPERS_get_abstick */

/*
 *  Expiration processing of counter
 */
#ifdef TOPPERS_expire_process

void
expire_process(CNTCB *p_cntcb, CounterType cntid)
{
	CNTEXPINFO	*p_cntexpinfo;
	TickType	nowval;

	p_cntcb->hwset = FALSE;
	nowval = get_curval(p_cntcb, cntid);

	/*
	 *  Expiration processing of counter
	 *
	 *  Queue is not empty, if already expiration time of the head of 
	 * the queue when viewed from the real-time current time only, to 
	 * run the expiration processing
	 *
	 *  To get each time a real-time current time, it is possible to cover 
	 * even exceeds the expiration time of interest when resetting the expiration 
	 * time of the first expiration processing queue
	 */
	while ((queue_empty(&(p_cntcb->cntexpque)) == FALSE) &&
		   (diff_tick(nowval, ((CNTEXPINFO *) p_cntcb->cntexpque.p_next)->expiretick,
					  p_cntcb->p_cntinib->maxval2) <= p_cntcb->p_cntinib->maxval)) {

		/* The expiration processing at the head of the counter expiration queue, removed from the queue */
		p_cntexpinfo = (CNTEXPINFO *) p_cntcb->cntexpque.p_next;
		queue_delete(&(p_cntexpinfo->cntexpque));
		queue_initialize(&(p_cntexpinfo->cntexpque));

		if (is_hwcnt(cntid)) {
			/*
			 *  When updated at the expiration point of the expiration process the counter value, 
			 * to insert an expiration point expires processing queue is used at the insertion 
			 * point comparison of expiration processing queue
			 */
			p_cntcb->curval = p_cntexpinfo->expiretick;

			/*
			 *  Setting of the next expiration point
			 *  Set if the following expiration point has not elapsed real time
			 */
			if ((queue_empty(&(p_cntcb->cntexpque)) == FALSE) && ((diff_tick((hwcntinib_table[cntid].get)(),
																			 ((CNTEXPINFO *) p_cntcb->cntexpque.p_next)->expiretick, p_cntcb->p_cntinib->maxval2)) >
																  p_cntcb->p_cntinib->maxval)) {
				(hwcntinib_table[cntid].set)(((CNTEXPINFO *) p_cntcb->cntexpque.p_next)->expiretick);
				p_cntcb->hwset = TRUE;
			}
		}

		/* Counter expiration processing call */
		(p_cntexpinfo->expirefunc)(p_cntexpinfo, p_cntcb);

		/*
		 *  When calling from the task, because if it becomes a high priority 
		 * task ready state, dispatching checks
		 */
		if ((p_runtsk != p_schedtsk) && (callevel_stat == TCL_TASK)) {
			dispatch();
		}

		/*
		 *  Considering interrupt response, and implementation once the interrupt
		 * enable / disable after one of the expiration point processing
		 */
		x_nested_unlock_os_int();
		x_nested_lock_os_int();

		nowval = get_curval(p_cntcb, cntid);
	}

	if (is_hwcnt(cntid) && (queue_empty(&(p_cntcb->cntexpque)) == FALSE) && (p_cntcb->hwset == FALSE)) {
		(hwcntinib_table[cntid].set)(((CNTEXPINFO *) p_cntcb->cntexpque.p_next)->expiretick);
	}
}
#endif /* TOPPERS_expire_process */

/*
 *  Forced termination of counter that SAP belongs
 */
#ifdef TOPPERS_force_term_osap_counter

void
force_term_osap_counter(OSAPCB *p_osapcb)
{
	CounterType	i;
	CNTCB		*p_cntcb;

	/* It wants to clear the state*/
	/* Initialize the current value to 0 */
	for (i = 0U; i < tnum_counter; i++) {
		if (cntinib_table[i].p_osapcb == p_osapcb) {
			p_cntcb = &cntcb_table[i];
			p_cntcb->curval = 0U;
			p_cntcb->cstat = CS_NULL;
		}
	}
}

#endif /* TOPPERS_force_term_osap_counter */
