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
 *  $Id: ioc_manage.c 504 2015-12-24 01:22:56Z witz-itoyo $
 */

/*
 *		IOC module
 */
#include "ioc_impl.h"
#include "check.h"

/*
 *  The default definition of the trace log macro
 */
#ifndef LOG_IOCSEND_ENTER
#define LOG_IOCSEND_ENTER(senderid)
#endif /* LOG_IOCSEND_ENTER */

#ifndef LOG_IOCSEND_LEAVE
#define LOG_IOCSEND_LEAVE(ercd)
#endif /* LOG_IOCSEND_LEAVE */

#ifndef LOG_IOCWRITE_ENTER
#define LOG_IOCWRITE_ENTER(senderid)
#endif /* LOG_IOCWRITE_ENTER */

#ifndef LOG_IOCWRITE_LEAVE
#define LOG_IOCWRITE_LEAVE(ercd)
#endif /* LOG_IOCWRITE_LEAVE */

#ifndef LOG_IOCRECEIVE_ENTER
#define LOG_IOCRECEIVE_ENTER(iocid)
#endif /* LOG_IOCRECEIVE_ENTER */

#ifndef LOG_IOCRECEIVE_LEAVE
#define LOG_IOCRECEIVE_LEAVE(ercd)
#endif /* LOG_IOCRECEIVE_LEAVE */

#ifndef LOG_IOCREAD_ENTER
#define LOG_IOCREAD_ENTER(iocid)
#endif /* LOG_IOCREAD_ENTER */

#ifndef LOG_IOCREAD_LEAVE
#define LOG_IOCREAD_LEAVE(ercd)
#endif /* LOG_IOCREAD_LEAVE */

#ifndef LOG_IOCEMPTYQUEUE_ENTER
#define LOG_IOCEMPTYQUEUE_ENTER(iocid)
#endif /* LOG_IOCEMPTYQUEUE_ENTER */

#ifndef LOG_IOCEMPTUQUEUE_LEAVE
#define LOG_IOCEMPTUQUEUE_LEAVE(ercd)
#endif /* LOG_IOCEMPTUQUEUE_LEAVE */


/* Prototype declaration of internal functions */
LOCAL_INLINE void ioc_memcpy(void *p_dst, const void *p_src, uint32 sz);


/*
 *  Initialization function
 */
void
ioc_initialize(void)
{
	IocType			i;
	IOCCB			*p_ioccb;
	const IOCINIB	*p_iocinib;

	/* Queue initialization */
	for (i = 0U; i < tnum_queueioc; i++) {
		p_ioccb = &ioccb_table[i];
		p_ioccb->quecnt = 0U;
		p_ioccb->head = 0U;
		p_ioccb->tail = 0U;
		p_ioccb->lostflg = FALSE;
	}

	/* Buffer initialization of each IOC */
	for (i = 0U; i < tnum_ioc; i++) {
		if (ioc_inival_table[i] != NULL) {
			p_iocinib = &iocinib_table[i];
			ioc_memcpy((void *) (p_iocinib->p_iocmb), ioc_inival_table[i], p_iocinib->datasz);
		}
	}
}



LOCAL_INLINE void
ioc_memcpy(void *p_dst, const void *p_src, uint32 sz)
{
	uint8		*p_tmp_dst = (uint8 *) p_dst;
	const uint8	*p_tmp_src = (const uint8 *) p_src;
	CounterType	i;

	for (i = 0U; i < sz; i++) {
		p_tmp_dst[i] = p_tmp_src[i];
	}
}


Std_ReturnType
ioc_send_generic(IocType IocWrapperId, const void *in)
{
	const IOCWRPINIB	*p_iocwrpinib;
	const IOCINIB		*p_iocinib;
	IOCCB				*p_ioccb;
	Std_ReturnType		ercd = IOC_E_OK;

	p_iocwrpinib = get_iocwrpinib(IocWrapperId);
	p_iocinib = get_iocinib(IOCID(p_iocwrpinib));
	p_ioccb = get_ioccb(IOCID(p_iocwrpinib));

	LOG_IOCSEND_ENTER(p_iocwrpinib->senderid);

	CHECK_IOC_CALLEVEL_DISABLEDINT(CALLEVEL_IOCSEND);
	CHECK_IOC_ACCESS(p_iocwrpinib->p_sndosapcb == p_runosap);
	CHECK_IOC_MEM_READ((const MemoryStartAddressType) in, p_iocinib->datasz, p_iocinib->alignsz);

	x_nested_lock_os_int();

	S_D_CHECK_IOC_LIMIT(p_ioccb->quecnt < p_iocinib->maxque);
	ioc_memcpy((void *) ((uint32) p_iocinib->p_iocmb + ((p_iocinib->datasz) * (p_ioccb->tail))), in, p_iocinib->datasz);
	p_ioccb->quecnt++;
	p_ioccb->tail++;
	if (p_ioccb->tail >= p_iocinib->maxque) {
		p_ioccb->tail = 0U;
	}

 /* d_exit_no_errorhook: */
	x_nested_unlock_os_int();
  exit_no_errorhook:
	LOG_IOCSEND_LEAVE(ercd);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  d_exit_errorhook:
	goto errorhook_start;

  exit_errorhook:
	x_nested_lock_os_int();
  errorhook_start:
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.iocid = IOCID(p_iocwrpinib);
	_errorhook_par2.senderid = p_iocwrpinib->senderid;
#endif /* CFG_USE_PARAMETERACCESS */
	if (p_iocinib->groupflg != FALSE) {
		call_errorhook(ercd, IOCServiceId_IOC_SendGroup);
	}
	else {
		call_errorhook(ercd, IOCServiceId_IOC_Send);
	}
	x_nested_unlock_os_int();
	goto exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}


Std_ReturnType
ioc_write_generic(IocType IocWrapperId, const void *in)
{
	const IOCWRPINIB	*p_iocwrpinib;
	const IOCINIB		*p_iocinib;
	Std_ReturnType		ercd = IOC_E_OK;

	p_iocwrpinib = get_iocwrpinib(IocWrapperId);
	p_iocinib = get_iocinib(IOCID(p_iocwrpinib));

	LOG_IOCWRITE_ENTER(p_iocwrpinib->senderid);

	CHECK_IOC_CALLEVEL_DISABLEDINT(CALLEVEL_IOCWRITE);
	CHECK_IOC_ACCESS(p_iocwrpinib->p_sndosapcb == p_runosap);
	CHECK_IOC_MEM_READ((const MemoryStartAddressType) in, p_iocinib->datasz, p_iocinib->alignsz);

	x_nested_lock_os_int();

	ioc_memcpy((void *) (p_iocinib->p_iocmb), in, p_iocinib->datasz);

  /*d_exit_no_errorhook:*/
	x_nested_unlock_os_int();
  exit_no_errorhook:
	LOG_IOCWRITE_LEAVE(ercd);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
 /* d_exit_errorhook: */
	goto errorhook_start;

  exit_errorhook:
	x_nested_lock_os_int();
  errorhook_start:
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.iocid = IOCID(p_iocwrpinib);
	_errorhook_par2.senderid = p_iocwrpinib->senderid;
#endif /* CFG_USE_PARAMETERACCESS */
	if (p_iocinib->groupflg != FALSE) {
		call_errorhook(ercd, IOCServiceId_IOC_WriteGroup);
	}
	else {
		call_errorhook(ercd, IOCServiceId_IOC_Write);
	}
	x_nested_unlock_os_int();
	goto exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}


Std_ReturnType
ioc_receive_generic(IocType IocId, void *out)
{
	const IOCINIB	*p_iocinib;
	IOCCB			*p_ioccb;
	Std_ReturnType	ercd = IOC_E_OK;

	LOG_IOCRECEIVE_ENTER(IocId);

	p_iocinib = get_iocinib(IocId);
	p_ioccb = get_ioccb(IocId);

	CHECK_IOC_CALLEVEL_DISABLEDINT(CALLEVEL_IOCRECEIVE);
	CHECK_IOC_ACCESS(p_iocinib->p_rcvosapcb == p_runosap);
	CHECK_IOC_MEM_WRITE(out, p_iocinib->datasz, p_iocinib->alignsz);

	x_nested_lock_os_int();

	S_D_CHECK_IOC_NO_DATA(p_ioccb->quecnt > 0U);
	ioc_memcpy(out, (void *) ((uint32) p_iocinib->p_iocmb + ((p_iocinib->datasz) * (p_ioccb->head))), p_iocinib->datasz);

	p_ioccb->quecnt--;
	p_ioccb->head++;
	if (p_ioccb->head >= p_iocinib->maxque) {
		p_ioccb->head = 0U;
	}

	S_D_CHECK_IOC_LOST(p_ioccb->lostflg == FALSE);

  /*d_exit_no_errorhook:*/
	x_nested_unlock_os_int();
  exit_no_errorhook:
	LOG_IOCRECEIVE_LEAVE(ercd);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  d_exit_errorhook:
	goto errorhook_start;

  exit_errorhook:
	x_nested_lock_os_int();
  errorhook_start:
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.iocid = IocId;
#endif /* CFG_USE_PARAMETERACCESS */
	if (p_iocinib->groupflg != FALSE) {
		call_errorhook(ercd, IOCServiceId_IOC_ReceiveGroup);
	}
	else {
		call_errorhook(ercd, IOCServiceId_IOC_Receive);
	}
	x_nested_unlock_os_int();
	goto exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}


Std_ReturnType
ioc_read_generic(IocType IocId, void *out)
{
	const IOCINIB	*p_iocinib;
	Std_ReturnType	ercd = IOC_E_OK;

	LOG_IOCREAD_ENTER(IocId);

	p_iocinib = get_iocinib(IocId);

	CHECK_IOC_CALLEVEL_DISABLEDINT(CALLEVEL_IOCREAD);
	CHECK_IOC_ACCESS(p_iocinib->p_rcvosapcb == p_runosap);
	CHECK_IOC_MEM_WRITE(out, p_iocinib->datasz, p_iocinib->alignsz);

	x_nested_lock_os_int();

	ioc_memcpy(out, (void *) (p_iocinib->p_iocmb), p_iocinib->datasz);

  /*d_exit_no_errorhook:*/
	x_nested_unlock_os_int();
  exit_no_errorhook:
	LOG_IOCREAD_LEAVE(ercd);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  /*d_exit_errorhook:*/
	goto errorhook_start;

  exit_errorhook:
	x_nested_lock_os_int();
  errorhook_start:
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.iocid = IocId;
#endif /* CFG_USE_PARAMETERACCESS */
	if (p_iocinib->groupflg != FALSE) {
		call_errorhook(ercd, IOCServiceId_IOC_ReadGroup);
	}
	else {
		call_errorhook(ercd, IOCServiceId_IOC_Read);
	}
	x_nested_unlock_os_int();
	goto exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}


Std_ReturnType
ioc_empty_queue_generic(IocType IocId)
{
	IOCCB			*p_ioccb;
	const IOCINIB	*p_iocinib;
	Std_ReturnType	ercd = IOC_E_OK;

	p_ioccb = get_ioccb(IocId);
	p_iocinib = get_iocinib(IocId);

	CHECK_IOC_CALLEVEL_DISABLEDINT(CALLEVEL_IOCEMPTYQUEUE);
	CHECK_IOC_ACCESS(p_iocinib->p_rcvosapcb == p_runosap);

	x_nested_lock_os_int();

	p_ioccb->quecnt = 0U;
	p_ioccb->head = 0U;
	p_ioccb->tail = 0U;
	p_ioccb->lostflg = FALSE;

  /*d_exit_no_errorhook:*/
	x_nested_unlock_os_int();
  exit_no_errorhook:
	LOG_IOCREAD_LEAVE(ercd);
	return(ercd);

#ifdef CFG_USE_ERRORHOOK
  /*d_exit_errorhook:*/
	goto errorhook_start;

  exit_errorhook:
	x_nested_lock_os_int();
  errorhook_start:
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.iocid = IocId;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, IOCServiceId_IOC_EmptyQueue);
	x_nested_unlock_os_int();
	goto exit_no_errorhook;
#endif /* CFG_USE_ERRORHOOK */
}
