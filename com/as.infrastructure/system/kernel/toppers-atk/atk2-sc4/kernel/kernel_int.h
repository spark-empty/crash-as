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
 *  $Id: kernel_int.h 504 2015-12-24 01:22:56Z witz-itoyo $
 */

#ifndef TOPPERS_KERNEL_INT_H
#define TOPPERS_KERNEL_INT_H

/*
 *  Kernel standard header file
 */
#include "kernel_impl.h"

/*
 *  Each header file of the kernel
 */
#include "task.h"
#include "counter.h"
#include "alarm.h"
#include "interrupt.h"
#include "resource.h"
#include "scheduletable.h"
#include "memory.h"
#include "ioc_impl.h"
#include "timingprotection.h"

/*
 *  Macro for the main routine definition
 */
#define TASKNAME(TaskName)	TaskMain ## TaskName
#define ISRNAME(ISRName)	ISRMain ## ISRName

/*
 *  The definition of the attributes of an object (used in configuration files only)
 */

/*
 *  Event mask value
 */
#define AUTO		UINT_C(0x00)    /* Event mask value=AUTO */

#define TA_NOWRITE		UINT_C(0x01)    /* Write access ban */
#define TA_NOREAD		UINT_C(0x02)    /* Read access ban */
#define TA_EXEC			UINT_C(0x04)    /* Execute permissions */
#define TA_MEMINI		UINT_C(0x08)    /* Do initialization of memory */
#define TA_MEMPRSV		UINT_C(0x10)    /* It is not performed to initialize the memory */
#define TA_SDATA		UINT_C(0x20)    /* Place the short data area */
#define TA_UNCACHE		UINT_C(0x40)    /* Cacheable */
#define TA_IODEV		UINT_C(0x80)    /* Area of the peripheral device */

#ifdef TOPPERS_TARGET_SUPPORT_ATT_MOD
#define TOPPERS_SUPPORT_ATT_MOD         /* ATT_MOD is supported */
#endif /* TOPPERS_TARGET_SUPPORT_ATT_MOD */

/*
 * OS application ID (protection domain ID of HRP2)
 */
#define TDOM_KERNEL		(-1)            /* Kernel domain */
#define TDOM_NONE		(-2)            /* Independent (not belonging to a protection domain)*/

#define TA_NULL			UINT_C(0)       /* It does not specify the object attributes */

/*
 * Macro OS application relationship
 */
#define TMAX_NTOSAPP		32          /* The maximum number of non-confidence OS application */

#endif /* TOPPERS_KERNEL_INT_H */
