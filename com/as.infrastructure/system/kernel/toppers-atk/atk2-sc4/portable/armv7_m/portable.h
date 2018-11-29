#ifndef _PORTABLE_H_
#define _PORTABLE_H_
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
#ifndef _MACRO_ONLY
#include "Std_Types.h"
#if  defined(CHIP_STM32F10X)
#include "stm32f10x.h"
#elif defined(CHIP_AT91SAM3S)
#include "SAM3S.h"
#include "board.h"
#elif defined(CHIP_LM3S6965)
#include "hw_ints.h"
#else
#error "CHIP is not known, please select the CHIP_STM32F10X or CHIP_AT91SAM3S"
#endif
#include <core_cm3.h>
#endif
/* ============================ [ MACROS    ] ====================================================== */
#define OMIT_STKMPUINFOB
#define OMIT_OSAPMPUINFOB

#define TOPPERS_SVC_FUNCCALL
#define TARGET_SVC_NUM 0
#define TARGET_SVC_TABLE

#define SIL_PRE_LOC
#define SIL_LOC_INT()
#define SIL_UNL_INT()

/* Program status register (PSR) */
#define TS_PSR_N               0x80000000        /* Condition flag Negative */
#define TS_PSR_Z               0x40000000        /* Zero */
#define TS_PSR_C               0x20000000        /* Carry */
#define TS_PSR_V               0x10000000        /* Overflow */
#define TS_PSR_T               0x01000000        /* Thumb mode */

/* Interrupt  mask register (Primask) */
#define TS_PMK_D               0x1               /* Interrupt disable */
#define TS_PMK_E               0x0               /* Interrupt enable */

/* Except  mask register (Faultmask) */
#define TS_FMK_D               0x1               /* Except disable */
#define TS_FMK_E               0x0               /* Except enable */

/* Control register (Control) */
#define TS_CTL_MSP             0x0               /* Select MSP */
#define TS_CTL_PSP             0x2               /* Select PSP */
#define TS_CTL_SVC             0x0               /* Select supervisor mode */
#define TS_CTL_USR             0x1               /* Select user mode */
/* ============================ [ TYPES     ] ====================================================== */
#ifndef _MACRO_ONLY
typedef uint32   uintptr;
typedef sint32   sintptr;
typedef char     char8;

typedef struct{
	void* sp;
	void  (*pc)(void);
}TSKCTXB;
#endif
/* ============================ [ DECLARES  ] ====================================================== */
#define TP_TIMER_MAX_TICK ((TickType)0xFFFFFFFF)
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifndef _MACRO_ONLY
extern void target_initialize(void);
extern void target_exit(void);

extern void dispatch(void);
extern void start_dispatch(void);
extern void exit_and_dispatch(void);
extern void exit_and_dispatch_nohook(void);
#endif
#endif /* _PORTABLE_H_ */
