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
#ifndef _ELFINTERNAL_H_
#define _ELFINTERNAL_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include <stdlib.h>
#include "vfs.h"
#include "elf.h"
#include "elfloader.h"
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
#define ELF32_MAGIC  0xEEFF3322
#define ELF64_MAGIC  0xEEFF6644

/* Section names */
#define ELF_BSS                 ".bss"         /* uninitialized data */
#define ELF_DATA                ".data"        /* initialized data */
#define ELF_DEBUG               ".debug"       /* debug */
#define ELF_DYNAMIC             ".dynamic"     /* dynamic linking information */
#define ELF_DYNSTR              ".dynstr"      /* dynamic string table */
#define ELF_DYNSYM              ".dynsym"      /* dynamic symbol table */
#define ELF_FINI                ".fini"        /* termination code */
#define ELF_GOT                 ".got"         /* global offset table */
#define ELF_HASH                ".hash"        /* symbol hash table */
#define ELF_INIT                ".init"        /* initialization code */
#define ELF_REL_DATA            ".rel.data"    /* relocation data */
#define ELF_REL_FINI            ".rel.fini"    /* relocation termination code */
#define ELF_REL_INIT            ".rel.init"    /* relocation initialization code */
#define ELF_REL_DYN             ".rel.dyn"     /* relocaltion dynamic link info */
#define ELF_REL_RODATA          ".rel.rodata"  /* relocation read-only data */
#define ELF_REL_TEXT            ".rel.text"    /* relocation code */
#define ELF_RODATA              ".rodata"      /* read-only data */
#define ELF_SHSTRTAB            ".shstrtab"    /* section header string table */
#define ELF_STRTAB              ".strtab"      /* string table */
#define ELF_SYMTAB              ".symtab"      /* symbol table */
#define ELF_TEXT                ".text"        /* code */

#define IS_PROG(s)        (s.sh_type == SHT_PROGBITS)
#define IS_NOPROG(s)      (s.sh_type == SHT_NOBITS)
#define IS_REL(s)         (s.sh_type == SHT_REL)
#define IS_RELA(s)        (s.sh_type == SHT_RELA)
#define IS_ALLOC(s)       (s.sh_flags == SHF_ALLOC)
#define IS_AX(s)          ((s.sh_flags & SHF_ALLOC) && (s.sh_flags & SHF_EXECINSTR))
#define IS_AW(s)          ((s.sh_flags & SHF_ALLOC) && (s.sh_flags & SHF_WRITE))

/* ============================ [ TYPES     ] ====================================================== */
typedef struct
{
	void       *addr;
	char* name;
}ELF32_SymtabType;

typedef struct
{
	uint32_t magic;
	uint32_t vstart_addr;
	uint32_t size;
	uint32_t nsym;
	void* space;
	int (*entry)(int argc, char* argv[]);
	ELF32_SymtabType* symtab;
}ELF32_ObjectType;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void* ELF32_Load(void* elfFile);
int ELF32_Relocate(ELF32_ObjectType *elfObj, Elf32_Rel *rel, Elf32_Addr sym_val);
void* ELF32_LookupSymbol(ELF32_ObjectType *elfObj, const char *symbol);
void ELF32_Close(ELF32_ObjectType *elfObj);

void* ELF_FindSymbol(const char* name);

#endif /* _ELFINTERNAL_H_ */
