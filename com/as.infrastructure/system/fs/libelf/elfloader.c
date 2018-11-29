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
/* http://infocenter.arm.com/help/topic/com.arm.doc.ihi0044f/IHI0044F_aaelf.pdf */
/* ============================ [ INCLUDES  ] ====================================================== */
#include "elfinternal.h"
/* ============================ [ MACROS    ] ====================================================== */
#define ISELF(elfFile) ( (((Elf32_Ehdr*)elfFile)->e_ident[EI_MAG0] == ELFMAG0) && \
						 (((Elf32_Ehdr*)elfFile)->e_ident[EI_MAG1] == ELFMAG1) && \
						 (((Elf32_Ehdr*)elfFile)->e_ident[EI_MAG2] == ELFMAG2) && \
						 (((Elf32_Ehdr*)elfFile)->e_ident[EI_MAG3] == ELFMAG3) )
#define ISELF32(elfFile) ( ((Elf32_Ehdr*)elfFile)->e_ident[EI_CLASS] == ELFCLASS32 )
#define ISELF64(elfFile) ( ((Elf32_Ehdr*)elfFile)->e_ident[EI_CLASS] == ELFCLASS64 )

/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
#if defined(USE_ELF_SYMTAB)
extern const ELF_SymbolType __elfsymtab_start[];
extern const ELF_SymbolType __elfsymtab_end[];
#endif
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
static void* do_load_elf(void* elfFile)
{
	void* elf = NULL;

	if (!ISELF(elfFile))
	{
		/* Invalid ELF */
	}
	else if (ISELF32(elfFile))
	{
		elf = ELF32_Load(elfFile);
	}
	else
	{
		/*ELF64 not supported now */
	}

	return elf;
}
/* ============================ [ FUNCTIONS ] ====================================================== */
void* ELF_Open(const char* filename)
{
	void* elf = NULL;
	void* faddr = NULL;
	VFS_FILE* fp;
	vfs_stat_t st;

	if( (0==vfs_stat(filename, &st)) &&
		(VFS_ISREG(st.st_mode)) )
	{
		fp = vfs_fopen(filename, "rb");

		if(NULL != fp)
		{
			faddr = malloc(st.st_size);
			if(NULL != faddr)
			{
				vfs_fread(faddr, st.st_size, 1, fp);
			}
			vfs_fclose(fp);
		}
	}

	if(NULL != faddr)
	{
		elf = do_load_elf(faddr);
		free(faddr);
	}

	return elf;
}

void* ELF_LookupSymbol(void *handle, const char *symbol)
{
	void* addr = NULL;
	ELF32_ObjectType* elfObj = handle;

	if(ELF32_MAGIC == elfObj->magic)
	{
		addr = ELF32_LookupSymbol(elfObj, symbol);
	}

	return addr;
}

int   ELF_Close(void *handle)
{
	ELF32_ObjectType* elfObj = handle;

	if(ELF32_MAGIC == elfObj->magic)
	{
		ELF32_Close(elfObj);
	}

	return 0;
}

/* This is an internal API */
void* ELF_FindSymbol(const char* name)
{
	void* addr = 0;
#if defined(USE_ELF_SYMTAB)
	const ELF_SymbolType* psym;
	for(psym=__elfsymtab_start; psym<__elfsymtab_end; psym++)
	{
		if(0 == strcmp(psym->name, name))
		{
			addr = psym->entry;
			break;
		}
	}
#endif
	return addr;
}

/* export some standard API */
#include <stdio.h>
ELF_EXPORT(printf);
ELF_EXPORT(sprintf);
ELF_EXPORT(snprintf);
ELF_EXPORT(puts);
ELF_EXPORT(putchar);
#include <stdlib.h>
ELF_EXPORT(malloc);
ELF_EXPORT(free);
ELF_EXPORT(calloc);
#include <string.h>
ELF_EXPORT(memcpy);
ELF_EXPORT(memset);
ELF_EXPORT(strlen);
ELF_EXPORT(strcpy);
ELF_EXPORT(strcmp);
ELF_EXPORT(strncmp);
ELF_EXPORT(strtoul);
