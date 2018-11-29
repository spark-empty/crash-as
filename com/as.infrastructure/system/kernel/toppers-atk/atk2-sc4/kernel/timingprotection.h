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
 *  $Id: timingprotection.h 504 2015-12-24 01:22:56Z witz-itoyo $
 */

/*
 *  Timing protection
 */

#ifndef TOPPERS_TIMINGPROTECTION_H
#define TOPPERS_TIMINGPROTECTION_H

extern volatile boolean	is_tp_timer_running;
extern volatile uint32	tp_time_count;

/*
 *  Arrival interval protection management block
 */
typedef struct timing_arrival_control_block {
	TFTIME	lastarrival;                    /* The last arrival time */
	boolean	is_not_first;                   /* Initial start-up flag */
} TPACB;

void tp_initialize(void);
void tp_terminate(void);
void tp_start_timer(TickType tick);
TickType tp_stop_timer(void);
void tp_stop_task_monitor(void);
void tp_get_current_time(TFTIME *tftime);
boolean tp_check_arrival_time(TFTIME time_frame, TPACB *p_tpacb, uint8 context);
void tp_fault_handler(void);
void tp_timer_handler(void);

/* tartget dependent tp implementation */
void target_tp_initialize(void);
void target_tp_terminate(void);
void target_tp_start_timer(TickType tick);
TickType target_tp_stop_timer(void);
void target_clear_tp_fault_status(void);
void target_clear_tp_timer_status(void);
TickType target_tp_get_remaining_ticks(void);
TickType target_tp_get_elapsed_ticks(void);
boolean  target_tp_sense_interrupt(void);

#define BITMAP_OSINTLOCK		((uint8) (0x01U))       /* OS interrupt disable time monitoring settings */
#define BITMAP_RESLOCK			((uint8) (0x02U))       /* Resource occupation time monitoring settings */

#endif /* TOPPERS_TIMINGPROTECTION_H */
