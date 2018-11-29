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
#include "mmu.h"
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
#define AS_LOG_MMU 0
/* information from loader, see boot/load.inc */
#define PAGE_DIR_BASE (uint32_t*)0x200000
#define PAGE_TBL_BASE (uint32_t*)0x201000
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void *mmap(void *addr, size_t length, int flags)
{
	uint32_t* pDir = PAGE_DIR_BASE;
	uint32_t* pTblS;
	uint32_t* pTblE;

	uint32_t dir;
	uint32_t table;
	uint32_t offset;

	uint32_t dsz;


	ASLOG(MMU, "mmap %p\n", addr);

	while(*pDir != 0)
	{
		pTblE = pTblS = (uint32_t*)((*pDir)&0xFFFFF000);
		while((*pTblE != 0) && ((pTblE-pTblS)<1024))
		{
			pTblE ++;
		}

		ASLOG(MMU, "DIR%d: %08X -> [%08X(%d) %08X(%d)]\n",
				pDir-PAGE_DIR_BASE,
				*pDir,
				*pTblS, pTblS-PAGE_TBL_BASE,
				*pTblE, pTblE-PAGE_TBL_BASE);
		if(*pTblE == 0)
		{
			break;
		}
		pDir++;
	}

	dsz = length + (uint32_t)addr&0xFFF;

	if(1024 == (pTblE-pTblS))
	{
		pDir ++;
		pTblE ++;
	}

	while(*pTblE != 0) pTblE++;

	pDir--;
	while(dsz > 0)
	{
		pDir++;
		if(*pDir == 0)
		{
			*pDir = *(pDir-1) + (1<<12);
		}

		pTblS = (uint32_t*)((*pDir)&0xFFFFF000);
		pTblE --;

		while(dsz > 0)
		{
			pTblE ++;
			if((pTblE-pTblS)>=1024) break;
			*pTblE = ((uint32_t)addr&0xFFFFF000)|flags;
			if(dsz > 4096)
			{
				dsz -= 4096;
			}
			else
			{
				dsz = 0;
			}
			ASLOG(MMU, "DIR%d: %08X -> [%08X(%d) %08X(%d)]\n",
					pDir-PAGE_DIR_BASE,
					*pDir,
					*pTblS, pTblS-PAGE_TBL_BASE,
					*pTblE, pTblE-PAGE_TBL_BASE);
		}
	}

	dir   = pDir - PAGE_DIR_BASE;
	table =  pTblE - pTblS;
	offset = (uint32_t)addr&0xFFF;

	addr = (void*)((dir<<22) + (table<<12) + offset);

	ASLOG(MMU, " >> %p(%d, %d %d)\n", addr, dir, table, offset);

	return addr;
}

