/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2018  AS <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */
/* ============================ [ INCLUDES  ] ====================================================== */
#include "elfinternal.h"
/* ============================ [ MACROS    ] ====================================================== */
#define AS_LOG_X86ELF 0
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
int ELF32_Relocate(ELF32_ObjectType *elfObj, Elf32_Rel *rel, Elf32_Addr sym_val)
{
	Elf32_Addr *where, tmp;
	Elf32_Sword addend, offset;
	uint32_t upper, lower, sign, j1, j2;

	where = (Elf32_Addr *)(elfObj->space
						   + rel->r_offset
						   - elfObj->vstart_addr);
	asAssert(where < (Elf32_Addr *)(elfObj->space + elfObj->size));
	switch (ELF32_R_TYPE(rel->r_info))
	{
		case R_X86_64_GLOB_DAT:
		case R_X86_64_JUMP_SLOT:
			*where = (Elf32_Addr)sym_val;

			ASLOG(X86ELF,"R_X86_64_JUMP_SLOT: 0x%x -> 0x%x 0x%x\n",
				  (uint32_t)where, *where, sym_val);
			break;
		case R_X86_64_RELATIVE:
			*where = (Elf32_Addr)sym_val + *where;
			ASLOG(X86ELF, "R_X86_64_RELATIVE: 0x%x -> 0x%x 0x%x\n",
				  (uint32_t)where, *where, sym_val);
			break;
		default:
			ASLOG(ERROR, "X86ELF: invalid relocate TYPE %d\n", ELF32_R_TYPE(rel->r_info));
			return -1;
	}

	return 0;

}
