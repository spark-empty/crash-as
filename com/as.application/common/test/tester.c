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
#include "Std_Types.h"
#include "Os.h"
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
#define AS_LOG_KSM 0
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
extern void tester_time_1000ms_runnable(void);
extern void tester_nvm_1000ms_runnable(void);
extern void pthread_test(void);
extern void fdt_test_init(void);
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
static TimerType timer;
/* ============================ [ FUNCTIONS ] ====================================================== */
KSM(Tester,Init)
{
	KGS(Tester,RoundRobin);
	StartTimer(&timer);
#ifdef USE_PTHREAD_TEST
	pthread_test();
#endif
#if defined(USE_SHELL) && defined(USE_VFS) && defined(USE_FDT)
	fdt_test_init();
#endif
}

KSM(Tester,Start)
{

}

KSM(Tester,Stop)
{

}


KSM(Tester,RoundRobin)
{
	if(GetTimer(&timer) > MS2TICKS(1000))
	{
		ASLOG(KSM,"Teter 1s runnable\n");
		StartTimer(&timer);
		tester_time_1000ms_runnable();
		tester_nvm_1000ms_runnable();
	}
}
