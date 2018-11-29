/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2015  AS <parai@foxmail.com>
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
#if defined(__WINDOWS__)
#include <windows.h>
#endif
#include "asdebug.h"
#include <stdarg.h>

#define in_range(c, lo, up)  ((uint8_t)c >= lo && (uint8_t)c <= up)
#define isprint(c)           in_range(c, 0x20, 0x7f)

#if defined(__LINUX__)
#ifndef __TERMUX__
#include <execinfo.h>
#endif
#endif

/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
typedef void (*aslog_t)(char*,char*);
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
#if defined(__WINDOWS__) || defined(__LINUX__)
static int g_argc=0;
static char** g_argv = 0;
#endif
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void asmem(const char* prefix, const void* address,size_t size)
{
	uint32 i,j;
	uint8 *src;
	src = (uint8*)address;
#if defined(__WINDOWS__) || defined(__LINUX__)
	if(8 == sizeof(unsigned long))
	{
		printf("%16s :: 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n",prefix);
	}
	else
#endif
	{
		printf("%8s :: 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n",prefix);
	}

	for(i=0; i<(size+15)/16; i++)
	{
		unsigned long a = (unsigned long)src+i*16;
#if defined(__WINDOWS__) || defined(__LINUX__)
		if( 8 == sizeof(unsigned long))
		{
			printf("%08X%08X ::",(uint32_t)(a>>32),(uint32_t)a);
		}
		else
#endif
		{
			printf("%08X ::",(uint32_t)a);
		}
#if defined(__WINDOWS__) || defined(__LINUX__)
		fflush(stdout);
#endif
		for(j=0;j<16;j++)
		{
			if((i*16+j)<size)
			{
				printf(" %02X",src[i*16+j]);
			}
			else
			{
				printf("   ");
			}
		}
		printf("\t");
		for(j=0;j<16;j++)
		{
			if(((i*16+j)<size) && isprint(src[i*16+j]))
			{
				printf("%c",src[i*16+j]);
			}
			else
			{
				printf(".");
			}
		}
		printf("\n");
	}
#if defined(__WINDOWS__) || defined(__LINUX__)
    fflush(stdout);
#endif
}
#if defined(__WINDOWS__) || defined(__LINUX__)
char* ashex(unsigned long a)
{
	char *buf = (char*)malloc(20);
	asAssert(buf);

	if( 8 == sizeof(unsigned long))
	{
		sprintf(buf,"%08X%08Xh",(uint32_t)(a>>32),(uint32_t)a);
	}
	else
	{
		sprintf(buf,"%08Xh",(uint32_t)a);
	}

	return buf;
}
#endif

#if defined(__LINUX__)
void  asPrintCallStack(void)
{
	#ifndef __TERMUX__
	int blen,i;
	void* buffer[256];
	char** names;
	blen = backtrace(buffer,256);
	names = backtrace_symbols(buffer,blen);
	printf("call stack trace is:\n");
	for(i=blen-1;i >= 0;i--)
	{
		printf("  %3d: %32s\n",blen-1-i,names[i]);
	}

	free(names);
	#endif
}
#endif

#if defined(__WINDOWS__)
void asPrintCallStack( void )
{
	int *f=NULL;
	*f = 0;
}
#endif
void __weak Sched_ShowRdyQ(void) {}
void __weak flush_stdio(void) {}
void asAssertErrorHook(void)
{
#if defined(__WINDOWS__) || defined(__LINUX__)
	asPrintCallStack();
	exit(-1);
#else
	Irq_Disable();
#ifdef USE_ASKAR
#ifdef USE_SHELL
	extern int statOsFunc(int argc, char* argv[]);
	statOsFunc(1, NULL);
	Sched_ShowRdyQ();
	while(1) flush_stdio();
#endif
#endif
	while(1);
#endif
}
ELF_EXPORT(asAssertErrorHook);

void _assert (const char *_Message, const char *_File, unsigned _Line)
{
	printf("assert(%s) failed @ %s %u\n", _Message, _File, _Line);
	asAssertErrorHook();
}
ELF_EXPORT(_assert);

void __assert_func (const char * file, int line, const char * func, const char * msg)
{
	printf("assert(%s) failed @ %u %s %s\n", msg, line, func, file);
	asAssertErrorHook();
}
ELF_EXPORT(__assert_func);
#if defined(__LINUX__) || defined(__WINDOWS__)
void asPerfSet(asperf_t *m)
{
	gettimeofday(m,NULL);
}
void asPerfLog(asperf_t *m0,asperf_t *m1,char* infor)
{
	float rv = m1->tv_sec-m0->tv_sec;

	if(m1->tv_usec > m0->tv_usec)
	{
		rv += (float)(m1->tv_usec-m0->tv_usec)/1000000.0;
	}
	else
	{
		rv = rv - 1 + (float)(1000000.0+m1->tv_usec-m0->tv_usec)/1000000.0;
	}

	printf("%s :: cost %f s\n",infor,rv);
}

void asEnvInit(int argc,char* argv[])
{
#if defined(__WINDOWS__)
	if(0 != LoadLibraryA("backtrace.dll"))
	{
		printf("load backtrace.dll failed\n");
	}
#endif
	g_argc = argc;
	g_argv = argv;
}
char* asEnvGet(int index)
{
	if(index < g_argc)
	{
		return g_argv[index];
	}
	else
	{
		/* default env */
		switch(index)
		{
			case 1: /* OSEK NM node ID */
				return "0";
				break;
			case 2: /* remote gui websock uri:port */
				return "127.0.0.1:8080";
				break;
			default:
				asAssert(0);
				break;
		}
	}

	return NULL;
}
#endif


