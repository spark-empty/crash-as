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
#ifndef _ELFLOADER_H_
#define _ELFLOADER_H_
/* ============================ [ INCLUDES  ] ====================================================== */

/* ============================ [ MACROS    ] ====================================================== */
#if defined(__LINUX__) || defined(__WINDOWS__)
#elif defined(__GNUC__)
#define USE_ELF_SYMTAB
#endif

#ifdef USE_ELF_SYMTAB
#define ELF_EXPORT(fnc) \
	const ELF_SymbolType const __attribute__((section("ELFSymTab"))) fnc##Ref = { #fnc, fnc};
#define ELF_EXPORT_ALIAS(fnc, name) \
	const ELF_SymbolType const __attribute__((section("ELFSymTab"))) fnc##Ref = { name, fnc};

#else
#define ELF_EXPORT(fnc)
#define ELF_EXPORT_ALIAS(fnc, name)
#endif
/* ============================ [ TYPES     ] ====================================================== */
typedef struct
{
	const char* name;
	void* entry;
} ELF_SymbolType;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void* ELF_Open(const char* filename);
void* ELF_LookupSymbol(void *handle, const char *symbol);
int   ELF_Close(void *handle);
#endif /* _ELFLOADER_H_ */
