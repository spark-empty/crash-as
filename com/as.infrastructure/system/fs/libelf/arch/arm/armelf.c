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
#define AS_LOG_ARMELF 0
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
		case R_ARM_NONE:
			ASLOG(ARMELF, "R_ARM_NONE\n");
			break;
		case R_ARM_ABS32:
			*where += (Elf32_Addr)sym_val;
			ASLOG(ARMELF,"R_ARM_ABS32: %x -> %x\n", where, *where);
			break;
		case R_ARM_PC24:
		case R_ARM_PLT32:
		case R_ARM_CALL:
		case R_ARM_JUMP24:
			addend = *where & 0x00ffffff;
			if (addend & 0x00800000)
				addend |= 0xff000000;
			tmp = sym_val - (Elf32_Addr)where + (addend << 2);
			tmp >>= 2;
			*where = (*where & 0xff000000) | (tmp & 0x00ffffff);
			ASLOG(ARMELF, "R_ARM_PC24: %x -> %x\n",
										   where, *where);
			break;
		case R_ARM_REL32:
			*where += sym_val - (Elf32_Addr)where;
			ASLOG(ARMELF, "R_ARM_REL32: %x -> %x, sym %x, offset %x\n",
						  where, *where, sym_val, rel->r_offset);
			break;
		case R_ARM_V4BX:
			*where &= 0xf000000f;
			*where |= 0x01a0f000;
			ASLOG(ARMELF,"R_ARM_V4BX: %x -> %x\n", where, *where);
			break;
		case R_ARM_GLOB_DAT:
		case R_ARM_JUMP_SLOT:
			*where = (Elf32_Addr)sym_val;
			ASLOG(ARMELF,"R_ARM_JUMP_SLOT: 0x%x -> 0x%x 0x%x\n",
										   where, *where, sym_val);
			break;
		case R_ARM_RELATIVE:
			*where = (Elf32_Addr)sym_val + *where;
			ASLOG(ARMELF,"R_ARM_RELATIVE: 0x%x -> 0x%x 0x%x\n",
										   where, *where, sym_val);
			break;
		case R_ARM_THM_PC22:
		case R_ARM_THM_JUMP24:
			ASLOG(ARMELF,"R_ARM_THM_PC22: %x\n", where);
			upper  = *(uint16_t *)where;
			lower  = *(uint16_t *)((Elf32_Addr)where + 2);

			sign   = (upper >> 10) & 1;
			j1     = (lower >> 13) & 1;
			j2     = (lower >> 11) & 1;
			offset = (sign << 24) |
					 ((~(j1 ^ sign) & 1) << 23) |
					 ((~(j2 ^ sign) & 1) << 22) |
					 ((upper & 0x03ff) << 12) |
					 ((lower & 0x07ff) << 1);
			if (offset & 0x01000000)
				offset -= 0x02000000;
			offset += sym_val - (Elf32_Addr)where;

			if (!(offset & 1) ||
				offset <= (int32_t)0xff000000 ||
				offset >= (int32_t)0x01000000)
			{
				ASLOG(ERROR, "ARMELF: Only Thumb addresses allowed\n");

				return -1;
			}

			sign = (offset >> 24) & 1;
			j1   = sign ^ (~(offset >> 23) & 1);
			j2   = sign ^ (~(offset >> 22) & 1);
			*(uint16_t *)where = (uint16_t)((upper & 0xf800) |
								 (sign << 10) |
								 ((offset >> 12) & 0x03ff));
			*(uint16_t *)(where + 2) = (uint16_t)((lower & 0xd000) |
										(j1 << 13) | (j2 << 11) |
										((offset >> 1) & 0x07ff));
			upper = *(uint16_t *)where;
			lower = *(uint16_t *)((Elf32_Addr)where + 2);
			break;
		default:
			ASLOG(ERROR, "ARMELF: invalid relocate TYPE %d\n", ELF32_R_TYPE(rel->r_info));
			return -1;
	}

	return 0;

}
