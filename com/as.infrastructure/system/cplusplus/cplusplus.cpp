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
#include <stdio.h>
#include <stdlib.h>
extern "C" {
#include "asdebug.h"

/* "virtual" is not supported by this implementation */
void __cxa_end_cleanup(void)
{
	asAssert(0);
}

void __gxx_personality_v0(void)
{
	asAssert(0);
}

void __exidx_start(void)
{
	asAssert(0);
}

void __exidx_end(void)
{
	asAssert(0);
}
}

void *operator new(size_t size)
{
	return malloc(size);
}

void *operator new[](size_t size)
{
	return malloc(size);
}

void operator delete(void *ptr)
{
	free(ptr);
}

void operator delete[] (void *ptr)
{
	return free(ptr);
}

