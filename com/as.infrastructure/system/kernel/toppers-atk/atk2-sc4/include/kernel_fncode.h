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
 *  $Id: kernel_fncode.h 504 2015-12-24 01:22:56Z witz-itoyo $
 */

/*  This file is generated from svc.def by gensvc_atk. */

#ifndef TOPPERS_KERNEL_FNCODE_H
#define TOPPERS_KERNEL_FNCODE_H

#define TMAX_SVCID	(61 + TARGET_SVC_NUM)

#define TFN_STARTOS						UINT_C(0)
#define TFN_SHUTDOWNOS					UINT_C(1)
#define TFN_ACTIVATETASK				UINT_C(2)
#define TFN_TERMINATETASK				UINT_C(3)
#define TFN_CHAINTASK					UINT_C(4)
#define TFN_SCHEDULE					UINT_C(5)
#define TFN_GETTASKID					UINT_C(6)
#define TFN_GETTASKSTATE				UINT_C(7)
#define TFN_ENABLEALLINTERRUPTS			UINT_C(8)
#define TFN_DISABLEALLINTERRUPTS		UINT_C(9)
#define TFN_RESUMEALLINTERRUPTS			UINT_C(10)
#define TFN_SUSPENDALLINTERRUPTS		UINT_C(11)
#define TFN_RESUMEOSINTERRUPTS			UINT_C(12)
#define TFN_SUSPENDOSINTERRUPTS			UINT_C(13)
#define TFN_GETISRID					UINT_C(14)
#define TFN_DISABLEINTERRUPTSOURCE		UINT_C(15)
#define TFN_ENABLEINTERRUPTSOURCE		UINT_C(16)
#define TFN_GETRESOURCE					UINT_C(17)
#define TFN_RELEASERESOURCE				UINT_C(18)
#define TFN_SETEVENT					UINT_C(19)
#define TFN_CLEAREVENT					UINT_C(20)
#define TFN_GETEVENT					UINT_C(21)
#define TFN_WAITEVENT					UINT_C(22)
#define TFN_GETALARMBASE				UINT_C(23)
#define TFN_GETALARM					UINT_C(24)
#define TFN_SETRELALARM					UINT_C(25)
#define TFN_SETABSALARM					UINT_C(26)
#define TFN_CANCELALARM					UINT_C(27)
#define TFN_INCREMENTCOUNTER			UINT_C(28)
#define TFN_GETCOUNTERVALUE				UINT_C(29)
#define TFN_GETELAPSEDVALUE				UINT_C(30)
#define TFN_CHECKISRMEMORYACCESS		UINT_C(31)
#define TFN_CHECKTASKMEMORYACCESS		UINT_C(32)
#define TFN_CHECKTASKACCESS				UINT_C(33)
#define TFN_CHECKISRACCESS				UINT_C(34)
#define TFN_CHECKALARMACCESS			UINT_C(35)
#define TFN_CHECKRESOURCEACCESS			UINT_C(36)
#define TFN_CHECKCOUNTERACCESS			UINT_C(37)
#define TFN_CHECKSCHEDULETABLEACCESS	UINT_C(38)
#define TFN_CHECKTASKOWNERSHIP			UINT_C(39)
#define TFN_CHECKISROWNERSHIP			UINT_C(40)
#define TFN_CHECKALARMOWNERSHIP			UINT_C(41)
#define TFN_CHECKCOUNTEROWNERSHIP		UINT_C(42)
#define TFN_CHECKSCHEDULETABLEOWNERSHIP	UINT_C(43)
#define TFN_GETAPPLICATIONID			UINT_C(44)
#define TFN_CALLTRUSTEDFUNCTION			UINT_C(45)
#define TFN_GETAPPLICATIONSTATE			UINT_C(46)
#define TFN_GETACTIVEAPPLICATIONMODE	UINT_C(47)
#define TFN_STARTSCHEDULETABLEREL		UINT_C(48)
#define TFN_STARTSCHEDULETABLEABS		UINT_C(49)
#define TFN_STOPSCHEDULETABLE			UINT_C(50)
#define TFN_NEXTSCHEDULETABLE			UINT_C(51)
#define TFN_GETSCHEDULETABLESTATUS		UINT_C(52)
#define TFN_GETFAULTYCONTEXT			UINT_C(53)
#define TFN_IOC_SEND_GENERIC			UINT_C(54)
#define TFN_IOC_WRITE_GENERIC			UINT_C(55)
#define TFN_IOC_RECEIVE_GENERIC			UINT_C(56)
#define TFN_IOC_READ_GENERIC			UINT_C(57)
#define TFN_IOC_EMPTY_QUEUE_GENERIC		UINT_C(58)
#define TFN_ALLOWACCESS					UINT_C(59)
#define TFN_TERMINATEAPPLICATION		UINT_C(60)

#endif /* TOPPERS_KERNEL_FNCODE_H */
