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
 *  $Id: interrupt.c 504 2015-12-24 01:22:56Z witz-itoyo $
 */

/*
 *		Interrupt control module
 */

#include "kernel_impl.h"
#include "interrupt.h"

#ifdef TOPPERS_interrupt_initialize
/*
 *  C2ISR running
 */
ISRCB			*p_runisr;

/*
 *  The definition of the variables used in internal interrupt management function
 */

/*
 *  SuspendAllInterrupts Nesting numbers
 */
uint8			sus_all_cnt = 0U;

/*
 *  SuspendOSInterrupts Nesting numbers
 */
uint8			sus_os_cnt = 0U;

/*
 *  Interrupt priority of the first call to SuspendOSInterrupts
 */
PriorityType	sus_os_prevpri;

/*
 *  The difference between the remaining time of the OS interrupt disable time 
 * budget and the original monitoring items
 */
TickType		os_difftime;
/*
 *  Previous monitoring items
 */
MonitoringType	os_saved_watchtype;

/*
 *  Initialization of interrupt management functions
 */
#ifndef OMIT_INITIALIZE_INTERRUPT

void
interrupt_initialize(void)
{
	ISRType				i;
	InterruptNumberType	j;
	ISRCB				*p_isrcb;
	const INTINIB		*p_intinib;

	p_runisr = NULL;

	sus_all_cnt = 0U;
	sus_os_cnt = 0U;

	os_difftime = 0U;
	os_saved_watchtype = NON_MONITORING;

	for (i = 0U; i < tnum_isr2; i++) {
		p_isrcb = &(isrcb_table[i]);
		p_isrcb->p_isrinib = &(isrinib_table[i]);
		p_isrcb->p_lastrescb = NULL;
		p_isrcb->tpacb.lastarrival.tfcount = 0U;
		p_isrcb->tpacb.lastarrival.tftick = 0U;
		p_isrcb->tpacb.is_not_first = FALSE;
#ifdef CFG_USE_PROTECTIONHOOK
		p_isrcb->calltfn = FALSE;
#endif /* CFG_USE_PROTECTIONHOOK */
	}

	for (j = 0U; j < tnum_intno; j++) {
		p_intinib = &(intinib_table[j]);
		x_config_int(p_intinib->intno, p_intinib->intatr, p_intinib->intpri);
	}
}

#endif /* OMIT_INITIALIZE_INTERRUPT */
#endif /* TOPPERS_interrupt_initialize */

/*
 *  Release of the interrupt disable
 */
#ifdef TOPPERS_release_interrupts

void
release_interrupts(OSServiceIdType serviceId)
{
#ifdef CFG_USE_ERRORHOOK
	boolean call_error_hook = FALSE;
#endif /* CFG_USE_ERRORHOOK */

	if (sus_os_cnt > 0U) {
		sus_os_cnt = 0U;

		LEAVE_CALLEVEL(TSYS_SUSOSINT);
		os_saved_watchtype = NON_MONITORING;
		os_difftime = 0U;
		x_set_ipm(sus_os_prevpri);
#ifdef CFG_USE_ERRORHOOK
		call_error_hook = TRUE;
#endif /* CFG_USE_ERRORHOOK */
	}

	if (sus_all_cnt > 0U) {
		sus_all_cnt = 0U;
		LEAVE_CALLEVEL(TSYS_SUSALLINT);
		ASSERT((callevel_stat & TSYS_DISALLINT) == TSYS_NULL);
		x_unlock_all_int();
#ifdef CFG_USE_ERRORHOOK
		call_error_hook = TRUE;
#endif /* CFG_USE_ERRORHOOK */
	}

	/* It will release the DisAll only case of C2ISR */
	if (serviceId == OSServiceId_ISRMissingEnd) {
		if ((callevel_stat & TSYS_DISALLINT) != TSYS_NULL) {
			LEAVE_CALLEVEL(TSYS_DISALLINT);
			x_unlock_all_int();
#ifdef CFG_USE_ERRORHOOK
			call_error_hook = TRUE;
#endif /* CFG_USE_ERRORHOOK */
		}
	}

#ifdef CFG_USE_ERRORHOOK
	if ((serviceId != OSServiceId_Invalid) && (call_error_hook != FALSE)) {
		call_errorhook(E_OS_DISABLEDINT, serviceId);
	}
#endif /* CFG_USE_ERRORHOOK */
}

#endif /* TOPPERS_release_interrupts */

/*
 *  C2ISR at the end of the check function
 */
#ifdef TOPPERS_exit_isr2

/*
 *  All resources return of C2ISR
 */
LOCAL_INLINE void
release_isrresources(ISRCB *p_isrcb)
{

	/* It should come with OS interrupt disable state abnormality */
	if (p_isrcb->p_lastrescb != NULL) {
		do {
			x_set_ipm(p_isrcb->p_lastrescb->prevpri);
			p_isrcb->p_lastrescb->lockflg = FALSE;
			p_isrcb->p_lastrescb = p_isrcb->p_lastrescb->p_prevrescb;
		} while (p_isrcb->p_lastrescb != NULL);

#ifdef CFG_USE_ERRORHOOK
		call_errorhook(E_OS_RESOURCE, OSServiceId_ISRMissingEnd);
#endif /* CFG_USE_ERRORHOOK */
	}
}

void
exit_isr2(void)
{
	x_nested_lock_os_int();

	release_interrupts(OSServiceId_ISRMissingEnd);

	release_isrresources(p_runisr);

	x_nested_unlock_os_int();
}

#endif /* TOPPERS_exit_isr2 */
