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
 *  $Id: memory.c 504 2015-12-24 01:22:56Z witz-itoyo $
 */

#include "kernel_impl.h"
#include "check.h"
#include "task.h"
#include "interrupt.h"
#include "memory.h"

/*
 *		Memory object management module
 */

/*
 *  The default definition of trace macro
 */

#ifndef LOG_CHKISRMEMACS_ENTER
#define LOG_CHKISRMEMACS_ENTER(ISRID, Address, Size)
#endif /* LOG_CHKISRMEMACS_ENTER */

#ifndef LOG_CHKISRMEMACS_LEAVE
#define LOG_CHKISRMEMACS_LEAVE(ercd)
#endif /* LOG_CHKISRMEMACS_LEAVE */

#ifndef LOG_CHKTSKMEMACS_ENTER
#define LOG_CHKTSKMEMACS_ENTER(TaskID, Address, Size)
#endif /* LOG_CHKTSKMEMACS_ENTER */

#ifndef LOG_CHKTSKMEMACS_LEAVE
#define LOG_CHKTSKMEMACS_LEAVE(ercd)
#endif /* LOG_CHKTSKMEMACS_LEAVE */


/*
 *  Prototype declaration of internal functions
 */
#ifndef USE_TSKINICTXB

LOCAL_INLINE AccessType check_address_sstack(const MemoryStartAddressType base, MemorySizeType size, const TINIB *p_tinib);
LOCAL_INLINE AccessType check_address_ustack(const MemoryStartAddressType base, MemorySizeType size, const TINIB *p_tinib);

#endif /* USE_TSKINICTXB */

/*
 *  Task memory access checking system service
 *  Check the access rights of the specified memory area of the specified task
 */
#ifdef TOPPERS_CheckTaskMemoryAccess

AccessType
CheckTaskMemoryAccess(TaskType TaskID, MemoryStartAddressType Address, MemorySizeType Size)
{
	AccessType	access;
	StatusType	ercd;
	TCB			*p_tcb;
	boolean		over_region;

	LOG_CHKTSKMEMACS_ENTER(TaskID, Address, Size);

	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_CHECKTASKMEMORYACCESS);
	CHECK_ID(TaskID < tnum_task);
	CHECK_VALUE(Size > 0U);

	p_tcb = get_tcb(TaskID);

	access = check_task_memory(p_tcb, Address, Size, &over_region);
	CHECK_ILLEGAL_ADDRESS(over_region == FALSE);

  exit_finish:
	LOG_CHKTSKMEMACS_LEAVE(access);
	return(access);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.tskid = TaskID;
	_errorhook_par2.adr = Address;
	_errorhook_par3.sz = Size;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_CheckTaskMemoryAccess);
	x_nested_unlock_os_int();
#endif /* CFG_USE_ERRORHOOK */

	/* exit_no_errorhook: */
	access = AP_NoAccess;
	goto exit_finish;
}

#endif /* TOPPERS_CheckTaskMemoryAccess */

/*
 *  ISR memory access checking system service
 *  Check the access rights of the specified designated ISR memory area
 */
#ifdef TOPPERS_CheckISRMemoryAccess

AccessType
CheckISRMemoryAccess(ISRType ISRID, MemoryStartAddressType Address, MemorySizeType Size)
{
	AccessType	access;
	StatusType	ercd;
	ISRCB		*p_isrcb;
	boolean		over_region;

	LOG_CHKISRMEMACS_ENTER(ISRID, Address, Size);

	CHECK_DISABLEDINT();
	CHECK_CALLEVEL(CALLEVEL_CHECKISRMEMORYACCESS);
	CHECK_ID(ISRID < tnum_isr2);
	CHECK_VALUE(Size > 0U);

	p_isrcb = get_isrcb(ISRID);

	access = check_isr_memory(p_isrcb, Address, Size, &over_region);
	CHECK_ILLEGAL_ADDRESS(over_region == FALSE);

  exit_finish:
	LOG_CHKISRMEMACS_LEAVE(access);
	return(access);

#ifdef CFG_USE_ERRORHOOK
  exit_errorhook:
	x_nested_lock_os_int();
#ifdef CFG_USE_PARAMETERACCESS
	_errorhook_par1.isrid = ISRID;
	_errorhook_par2.adr = Address;
	_errorhook_par3.sz = Size;
#endif /* CFG_USE_PARAMETERACCESS */
	call_errorhook(ercd, OSServiceId_CheckISRMemoryAccess);
	x_nested_unlock_os_int();
#endif /* CFG_USE_ERRORHOOK */

	/* exit_no_errorhook: */
	access = AP_NoAccess;
	goto exit_finish;
}

#endif /* TOPPERS_CheckISRMemoryAccess */

/*
 *  Memory access check function
 */

/*
 *  Stack access check body
 */
#ifdef TOPPERS_check_address_stack

AccessType
check_address_stack(const MemoryStartAddressType base, MemorySizeType size, const MemoryStartAddressType mobase, MemorySizeType mosize)
{
	AccessType result;
	if (within_memobj(base, size, mobase, mosize) != FALSE) {
		result = AP_Readable | AP_Writable | AP_StackSpace;
	}
	else {
		result = NO_ACCESS;
	}
	return(result);
}

#endif /* TOPPERS_check_address_stack */

#ifndef USE_TSKINICTXB

LOCAL_INLINE AccessType
check_address_sstack(const MemoryStartAddressType base, MemorySizeType size, const TINIB *p_tinib)
{
	return(check_address_stack(base, size, p_tinib->sstk, p_tinib->sstksz));
}

LOCAL_INLINE AccessType
check_address_ustack(const MemoryStartAddressType base, MemorySizeType size, const TINIB *p_tinib)
{
	return(check_address_stack(base, size, p_tinib->ustk, p_tinib->ustksz));
}

#endif /* USE_TSKINICTXB */


#ifndef OMIT_STANDARD_MEMINIB
/*
 *  Search of memory object initialization block
 */
#ifdef TOPPERS_search_meminib

uint32
search_meminib(MemoryStartAddressType addr)
{
	uint32 left, right, i;

	left = 0U;
	right = tnum_meminib - 1U;
	while (left < right) {
		i = (left + right + 1U) / 2U;
		if (addr < (MemoryStartAddressType const) memtop_table[i]) {
			right = i - 1U;
		}
		else {
			left = i;
		}
	}
	return(left);
}

#endif /* TOPPERS_search_meminib */
/*
 *  Memory access check
 *   It does check in the memory protection unit (OS application)
 *
 *  In the case of trust OS application, check the background
 *    It can be all area access in the current implementation
 *  In the case of non-confidence OS applications, and returns the attributes of the memory object
 */
#ifdef TOPPERS_check_osap_memory

AccessType
check_osap_memory(OSAPCB *p_osapcb, const MemoryStartAddressType adr, MemorySizeType size)
{
	AccessType				access = AP_NoAccess;
	const MEMINIB			*p_meminib;
	uint32					pos;
	uint32					btptn;
	MemoryStartAddressType	sadr = adr;
	MemoryStartAddressType	eadr = (MemoryStartAddressType) ((MemorySizeType) sadr + size);

	if (p_osapcb->p_osapinib->osap_trusted != FALSE) {
		access = probe_trusted_osap_mem(sadr, eadr);
	}
	else {

		pos = search_meminib(sadr);
		p_meminib = &(meminib_table[pos]);
		if ((pos + 1U) < tnum_meminib) {
			if (((uint8 *) eadr - 1) < (uint8 * const) memtop_table[pos + 1U]) {
				btptn = p_osapcb->p_osapinib->btptn;
				access |= ((p_meminib->acptnr & btptn) != 0U) ? AP_Readable   : AP_NoAccess;
				access |= ((p_meminib->acptnw & btptn) != 0U) ? AP_Writable   : AP_NoAccess;
				access |= ((p_meminib->acptnx & btptn) != 0U) ? AP_Executable : AP_NoAccess;
			}
		}
	}
	return(access);
}

#endif /* TOPPERS_check_osap_memory */

/*
 *  ISR memory access checking system services (for internal kernel)
 */
#ifdef TOPPERS_check_isr_memory

AccessType
check_isr_memory(ISRCB *p_isrcb, const MemoryStartAddressType adr, MemorySizeType size, boolean *over_region)
{
	AccessType				access = AP_NoAccess;
	uint32					pos;
	MemoryStartAddressType	sadr = adr;
	MemorySizeType			memsize;

	pos = search_meminib(sadr);
	memsize = (MemorySizeType) (((uint8 *) (((pos + 1U) < tnum_meminib) ?
											((uint8 * const) memtop_table[pos + 1U]) : 0U)) - (const uint8 *) adr);

	/* The decision whether or across the region */
	if (size > memsize) {
		*over_region = TRUE;
	}
	else {
		*over_region = FALSE;
		access = check_address_stack(adr, size, _ostk, _ostksz);
	}

	/* Since C2ISR In functional level 2 is not only trust, it will allow all access */
	access |= (AP_Readable | AP_Writable | AP_Executable);

	return(access);
}

#endif /* TOPPERS_check_isr_memory */

/*
 *  Task memory access checking system services (for internal kernel)
 */
#ifdef TOPPERS_check_task_memory

AccessType
check_task_memory(const TCB *p_tcb, const MemoryStartAddressType adr, MemorySizeType size, boolean *over_region)
{
	AccessType				access = AP_NoAccess;
	const MEMINIB			*p_meminib;
	uint32					pos;
	uint32					btptn;
	MemoryStartAddressType	sadr = adr;
	MemorySizeType			memsize;

	pos = search_meminib(sadr);
	memsize = (MemorySizeType) (((uint8 *) (((pos + 1U) < tnum_meminib) ?
											((uint8 * const) memtop_table[pos + 1U]) : 0U)) - (const uint8 *) adr);

	/* The decision whether or across the region */
	if (size > memsize) {
		*over_region = TRUE;
	}
	else {
		*over_region = FALSE;
	}

	if (p_tcb->p_tinib->p_osapcb->p_osapinib->osap_trusted != FALSE) {
		access = check_address_sstack(adr, size, p_tcb->p_tinib);

		/* It can be all access in the case of trust task */
		access |= (AP_Readable | AP_Writable | AP_Executable);
	}
	else if (*over_region == FALSE) {
		p_meminib = &(meminib_table[pos]);
		if ((p_meminib->mematr & TOPPERS_USTACK) == 0U) {
			btptn = p_tcb->p_tinib->p_osapcb->p_osapinib->btptn;
			access |= ((p_meminib->acptnr & btptn) != 0U) ? AP_Readable   : AP_NoAccess;
			access |= ((p_meminib->acptnw & btptn) != 0U) ? AP_Writable   : AP_NoAccess;
			access |= ((p_meminib->acptnx & btptn) != 0U) ? AP_Executable : AP_NoAccess;
		}
		else {
			access = check_address_ustack(adr, size, p_tcb->p_tinib);
		}
	}
	else {
		/* Otherwise, it does not perform processing (return value: AP_NoAccess) */
	}

	return(access);
}

#endif /* TOPPERS_check_task_memory */
#endif /* OMIT_STANDARD_MEMINIB */

/*
 *  Check the memory access rights
 */
#ifdef TOPPERS_probe_memory_access

AccessType
probe_memory_access(const MemoryStartAddressType base, MemorySizeType size)
{
	AccessType				access;
	boolean					dummy;
	MemoryStartAddressType	base_adr = base;

	if (run_trusted != FALSE) {
		/* In the case of privileged mode, check the background */
		access = probe_trusted_osap_mem(base, (MemoryStartAddressType) ((uint8 *) base_adr + size));
	}
	else {
		access = check_task_memory(p_runtsk, base, size, &dummy);
	}
	return(access);
}

#endif /* TOPPERS_probe_memory_access */

/*
 *  Check of write access to the memory
 */
#ifdef TOPPERS_probe_memory_read

boolean
probe_memory_read(const MemoryStartAddressType base, MemorySizeType size)
{
	return((probe_memory_access(base, size) & AP_Readable) == AP_Readable);
}

#endif /* TOPPERS_probe_memory_read */

/*
 *  Check of write access to the memory
 */
#ifdef TOPPERS_probe_memory_write

boolean
probe_memory_write(const MemoryStartAddressType base, MemorySizeType size)
{
	return((probe_memory_access(base, size) & AP_Writable) == AP_Writable);
}

#endif /* TOPPERS_probe_memory_write */

/*
 *  Check reading and writing right to the memory
 */
#ifdef TOPPERS_probe_memory_read_write

boolean
probe_memory_read_write(const MemoryStartAddressType base, MemorySizeType size)
{
	return((probe_memory_access(base, size) & (AP_Readable | AP_Writable)) == (AP_Readable | AP_Writable));
}

#endif /* TOPPERS_probe_memory_read_write */

/*
 *  Initialization of DATA section and the BSS section
 */
#ifdef TOPPERS_initialize_sections
#ifndef OMIT_INITIALIZE_SECTIONS

void
initialize_sections(void)
{
	uint32				i;
	uint8				*p_src, *p_dst;
	const DATASECINIB	*p_datasecinib;
	const BSSSECINIB	*p_bsssecinib;

	for (i = 0U; i < tnum_datasec; i++) {
		p_datasecinib = &(datasecinib_table[i]);
		p_src = (uint8 *) p_datasecinib->start_idata;
		for (p_dst = (uint8 *) p_datasecinib->start_data;
			 ((const MemoryStartAddressType) p_dst) < (const MemoryStartAddressType) p_datasecinib->end_data; p_dst++) {
			*p_dst = *p_src;
			p_src++;
		}
	}
	for (i = 0U; i < tnum_bsssec; i++) {
		p_bsssecinib = &(bsssecinib_table[i]);
		for (p_dst = (uint8 *) p_bsssecinib->start_bss;
			 ((const MemoryStartAddressType) p_dst) < (const MemoryStartAddressType) p_bsssecinib->end_bss; p_dst++) {
			*p_dst = 0U;
		}
	}
}

#endif /* OMIT_INITIALIZE_SECTIONS */
#endif /* TOPPERS_initialize_sections */
