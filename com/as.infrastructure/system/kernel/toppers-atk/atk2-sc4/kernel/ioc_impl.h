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
 *  $Id: ioc_impl.h 504 2015-12-24 01:22:56Z witz-itoyo $
 */

/*
 *		IOC function
 */

#ifndef TOPPERS_IOC_IMPL_H
#define TOPPERS_IOC_IMPL_H

#include "kernel_impl.h"
#include "osap.h"

/*
 *  Macro for extracting IOCWRPINIB from Wrapper ID
 */
#define get_iocwrpinib(WrapperId)	(&iocwrpinib_table[(WrapperId)])

/*
 *  IOCCB from IOC ID, macro for extracting IOCINIB
 */
#define get_ioccb(iocid)		(&ioccb_table[(iocid)])
#define get_iocinib(iocid)		(&iocinib_table[(iocid)])

/*
 *  Macro for extracting IOC ID from IOCWRPINIB
 */
#define IOCID(p_iocwrpinib)	((IocType) (((p_iocwrpinib)->p_iocinib) - iocinib_table))



/*
 *  IOC initialization block
 */
typedef struct ioc_initialization_block {
	uint32	maxque;                 /* Number of queues */
	uint32	datasz;                 /* Data size */
	uint32	alignsz;                /* Aligned size */
#ifdef CFG_USE_ERRORHOOK
	boolean	groupflg;            /* Group communication flag */
#endif /* CFG_USE_ERRORHOOK */
	OSAPCB	*p_rcvosapcb;        /* A pointer to the initialization block of OSAP the Receiver belongs */
	void	*p_iocmb;
} IOCINIB;

/*
 *  IOC management block
 */
typedef struct ioc_control_block {
	uint32	quecnt;                 /* Current number of queue */
	uint32	head;                   /* The head of the queue */
	uint32	tail;                   /* Queue last */
	boolean	lostflg;                /* Flag queue full error (E_LOST_DATA) */
} IOCCB;

/*
 *  IOC Wrapper initialization block
 */
typedef struct ioc_wrapper_initialization_block {
	const IOCINIB	*p_iocinib;         /* A pointer to the IOC initialization block */
	OSAPCB			*p_sndosapcb;       /* A pointer to the SOAP initialization block the Sender belongs */
	SenderIdType	senderid;           /* SenderID */
} IOCWRPINIB;


extern const IocType	tnum_ioc;       /* The number of IOC */
extern const IocType	tnum_queueioc;  /* The number of queues There IOC */

/*
 *  IOC Wrapper initialization block
 */
extern const IOCWRPINIB	iocwrpinib_table[];

/*
 *  IOC initialization block 
 */
extern const IOCINIB	iocinib_table[];

/*
 *  IOC management block
 */
extern IOCCB			ioccb_table[];

/*
 *  IOC WRAPPER initialization block
 */
extern const IOCWRPINIB	iocwrpinib_table[];

/*
 *  IOC initialization value table
 */
extern void				*ioc_inival_table[];

/*
 *  Initialization of the IOC management module
 */
extern void ioc_initialize(void);

#endif /* TOPPERS_IOC_IMPL_H */
