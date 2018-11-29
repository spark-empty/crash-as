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
#ifndef _TRACE_CFG_H_
#define _TRACE_CFG_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#if defined(USE_MPC5634M_MLQB80)
#include "mpc56xx.h"
#endif
#if defined(__WINDOWS__) || defined(__LINUX__)
#include <sys/time.h>
#include <time.h>
#endif
/* ============================ [ MACROS    ] ====================================================== */
#if defined(USE_MPC5634M_MLQB80)
#define TRACE_TIMER_FREQ      64000000
#define TRACE_TIMER_MAX       0xFFFFFFFFUL
#define TRACE_TIMER_TYPE      TRACE_TIMER_TYPE_DOWN
#define TRACE_TIMER_VALUE     PIT.TIMER[0].CVAL.R
#define TRACE_TIMER_INIT					\
	do {									\
		PIT.TIMER[0].LDVAL.R=0xFFFFFFFFUL;	\
		PIT.TIMER[0].TCTRL.B.TEN=1;			\
	} while(0)
#endif

#if defined(__WINDOWS__) || defined(__LINUX__)
#define TRACE_TIMER_FREQ      1000000
#define TRACE_TIMER_MAX       0xFFFFFFFFUL
#define TRACE_TIMER_TYPE      TRACE_TIMER_TYPE_UP
#define TRACE_TIMER_VALUE     clock()
#define TRACE_TIMER_INIT
#endif

/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#endif /* _TRACE_CFG_H_ */
