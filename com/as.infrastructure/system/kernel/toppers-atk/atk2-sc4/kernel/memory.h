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
 *  $Id: memory.h 504 2015-12-24 01:22:56Z witz-itoyo $
 */

/*
 *		Memory access-related functions
 */

#ifndef TOPPERS_MEMORY_H
#define TOPPERS_MEMORY_H

#include "interrupt.h"
#include "task.h"

/*
 *  Memory attribute (used internally by the kernel)
 */
#define TOPPERS_ATTSEC	UINT_C(0x0100)  /* Memory objects that have been registered in the ATT_SEC / ATT_MOD */
#define TOPPERS_ATTMEM	UINT_C(0x0200)  /* Memory objects that have been registered in the ATT_MEM */
#define TOPPERS_USTACK	UINT_C(0x0400)  /* User stack area of the task / C2ISR */

#ifndef TOPPERS_MACRO_ONLY

typedef	uint32 AccessPatternType;      /* Permissions pattern */

/*
 *  Permissions pattern
 */
#define TACP_KERNEL		((uint32) 0U)               /* Allow access only to the kernel domain */
#define TACP_SHARED		(~(uint32) 0U)              /* Allow access from all domains */

#ifndef OMIT_STANDARD_MEMINIB

/*
 *  Memory object initialization block
 */
typedef struct memory_initialization_block {
	AttributeType		mematr;         /* Memory object attributes */
	AccessPatternType	acptnr;         /* Read enabled OS application bit pattern */
	AccessPatternType	acptnw;         /* Light permission OS application bit pattern */
	AccessPatternType	acptnx;         /* Execute permission OS application bit pattern */
} MEMINIB;

/*
 *  The number of memory object initialization block (kernel_mem.c)
 */
extern const uint32		tnum_meminib;

/*
 *  Area of the start address of the memory object (kernel_mem.c)
 */
extern void * const	memtop_table[];

/*
 *  Area of the memory object initialization block (kernel_mem.c)
 */
extern const MEMINIB	meminib_table[];

/*
 *  Search of memory object initialization block
 *
 *  From memory object initialization block, find the memory object that contains 
 * the addr, and returns the index
 */

extern uint32 search_meminib(MemoryStartAddressType addr);

#endif /* OMIT_STANDARD_MEMINIB */

/*
 *  Check whether the memory area is included in the memory object
 *
 *  Memory area of the start address is the size in base size is, returns a
 * FALSE TRUE, if this is not the case if the top address size in mobase is
 * included in the memory object of mosize
 */

LOCAL_INLINE boolean
within_memobj(MemoryStartAddressType base, MemorySizeType size, MemoryStartAddressType mobase, MemorySizeType mosize)
{
	return((mobase <= base) && (size <= mosize)
		   && (((MemorySizeType) base - (MemorySizeType) mobase) <= (mosize - size)));
}

/*
 *  Stack access check body
 */
extern AccessType check_address_stack(const MemoryStartAddressType base, MemorySizeType size, const MemoryStartAddressType mobase, MemorySizeType mosize);

/*
 *  Memory access check
 */
extern AccessType check_osap_memory(OSAPCB *p_osapcb, const MemoryStartAddressType adr, MemorySizeType size);

/*
 *  ISR memory access checking system services (for internal kernel)
 */
extern AccessType check_isr_memory(ISRCB *p_isrcb, const MemoryStartAddressType adr, MemorySizeType size, boolean *over_region);

/*
 *  Task memory access checking system services (for internal kernel)
 */
extern AccessType check_task_memory(const TCB *p_tcb, const MemoryStartAddressType adr, MemorySizeType size, boolean *over_region);

/*
 *  Check the memory access rights
 */
extern AccessType probe_memory_access(const MemoryStartAddressType base, MemorySizeType size);

/*
 *  Check the read rights to the memory
 */
extern boolean probe_memory_read(const MemoryStartAddressType base, MemorySizeType size);

/*
 *  Check of write access to the memory
 */
extern boolean probe_memory_write(const MemoryStartAddressType base, MemorySizeType size);

/*
 *  Check reading came right to the memory
 */
extern boolean probe_memory_read_write(const MemoryStartAddressType base, MemorySizeType size);

/*
 *  Initialization of DATA section and the BSS section
 */
extern void initialize_sections(void);

/*
 *  Macros for memory access rights check
 */
#ifndef PROBE_MEM_WRITE
#define PROBE_MEM_WRITE(p_var, type) \
	(boolean) ((probe_memory_write((MemoryStartAddressType) (p_var), sizeof(type)) != FALSE) && (ALIGNED_TYPE(p_var, type) != FALSE))
#endif /* PROBE_MEM_WRITE */

#ifndef PROBE_MEM_RW
#define PROBE_MEM_RW(p_var, type) \
	(boolean) ((probe_memory_read_write((MemoryStartAddressType) (p_var), sizeof(type)) != FALSE) && (ALIGNED_TYPE(p_var, type) != FALSE))
#endif /* PROBE_MEM_RW */

/*
 *  data section initialization block
 */
typedef struct {
	void	*start_data;        /* the start address of the data section */
	void	*end_data;          /* end address of the data section */
	void	*start_idata;       /* The start address of the initialized data area */
} DATASECINIB;

/*
 *  area of the number and initialization block of data section (kernel_mem_2.c)
 */
extern const uint32			tnum_datasec;
extern const DATASECINIB	datasecinib_table[];

/*
 *  bss section initialization block
 */
typedef struct {
	void	*start_bss;         /* the start address of the bss section */
	void	*end_bss;           /* End address of bss section */
} BSSSECINIB;

/*
 * area of the number and initialization block of bss section (kernel_mem_2.c)
 */
extern const uint32		tnum_bsssec;
extern const BSSSECINIB	bsssecinib_table[];

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_MEMORY_H_ */
