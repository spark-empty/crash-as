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
 *  $Id: scheduletable.h 504 2015-12-24 01:22:56Z witz-itoyo $
 */

/*
 *		Schedule table function
 */

#ifndef TOPPERS_SCHEDULETABLE_H
#define TOPPERS_SCHEDULETABLE_H

#include "counter.h"

/*
 *  Special expiration point index for the expiration point table control
 */
#define EXPPTINDEX_TOP			((uint8) 0x00)
#define EXPPTINDEX_INITIAL		((uint8) 0xff)

/*
 *  Macro for taking out the schedule table management block from the schedule table ID
 */
#define get_schtblcb(schtblid)	(&(schtblcb_table[(schtblid)]))

/*
 *  The definition of implicit synchronization schedule table
 */
#define is_implschtbl(schtblid)	((schtblid) < tnum_implscheduletable)

/*
 *  Individual expiration point table type
 */
typedef struct scheduletable_expire_point_block {
	TickType		offset;                                 /* Offset value */
	FunctionRefType	expptfnt;                               /* Pointer of expiration point processing function */
} SCHTBLEXPPTCB;


/*
 *  Schedule table initialization block
 */
typedef struct scheduletable_initialization_block {
	CNTCB				*p_cntcb;                           /* Pointer of the drive counter management block */
	TickType			length;                             /* The length of the cycle */
	AppModeType			autosta;                            /* Starting up for the application mode */
	AttributeType		actatr;                             /* Automatic start of attributes */
	TickType			staval;                             /* Automatic start tick value */
	const SCHTBLEXPPTCB	*p_exppt;                           /* Head pointer of the expiration point table */
	boolean				repeat;                             /* The presence or absence of periodic control */
	uint8				tnum_exppt;                         /* Expiration score */
	OSAPCB				*p_osapcb;                          /* Management block belongs to OS application */
	uint32				acsbtmp;                            /* Permissions OS application bitmap */
} SCHTBLINIB;

/*
 *  Schedule table management block
 */
typedef struct scheduletable_control_block {
	CNTEXPINFO							cntexpinfo;         /* Counter expiration information (need to enter at the top of the structure) */
	const SCHTBLINIB					*p_schtblinib;      /* A pointer to the initialization block */
	struct scheduletable_control_block	*p_prevschtblcb;    /* A pointer to the schedule table management block that myself Next */
	struct scheduletable_control_block	*p_nextschtblcb;    /* A pointer to the Next schedule table management block */
	ScheduleTableStatusType				status;             /* Schedule table state */
	uint8								expptindex;         /* Expiration point index */
} SCHTBLCB;

/*
 *  Expiration processing execution management information
 */
typedef struct scheduletable_expire_info {
	SCHTBLCB *p_schtblcb;                                   /* Address of the schedule table management block */
} SCHTBLEXPINFO;

/*
 *  Declaration of the variable to hold the number of schedule table
 */
extern const ScheduleTableType	tnum_scheduletable;         /* The total number of the schedule table */
extern const ScheduleTableType	tnum_implscheduletable;     /* Number of implicit synchronization schedule table */

/*
 *  Area of the schedule table initialization block
 */
extern const SCHTBLINIB			schtblinib_table[];
/*
 *  Area of the schedule table management block
 */
extern SCHTBLCB					schtblcb_table[];

/*
 *  Initialization of the schedule table object
 */
extern void schtbl_initialize(void);

/*
 *  Schedule table expiration processing function
 */
extern void schtbl_expire(CNTEXPINFO *p_cntexpinfo, const CNTCB *p_cntcb);

/*
 *  Run from the expiration processing function of each timing processing
 */
extern void schtbl_expiry_process(SCHTBLEXPINFO *p_schtblexpinfo, const CNTCB *p_cntcb);

/*
 *  Start processing of the schedule table
 */
extern boolean schtbl_head(SCHTBLCB *p_schtblcb, const CNTCB *p_cntcb);

/*
 *  Each expiration point processing of the schedule table
 */
extern boolean schtbl_exppoint_process(SCHTBLCB *p_schtblcb, const CNTCB *p_cntcb);

/*
 *  Termination of the schedule table
 */
extern boolean schtbl_tail(SCHTBLCB *p_schtblcb, SCHTBLEXPINFO *p_schtblexpinfo, const CNTCB *p_cntcb);

/*
 *  Forced termination of OSAP belongs to schedule table
 */
extern void force_term_osap_schtbl(OSAPCB *p_osapcb);

#endif /* TOPPERS_SCHEDULETABLE_H */
