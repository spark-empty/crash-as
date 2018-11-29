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
#ifndef COM_CLANG_C_TOPPERS_OSEK_PORTABLE_ARMV7_M_PORTABLE_H_
#define COM_CLANG_C_TOPPERS_OSEK_PORTABLE_ARMV7_M_PORTABLE_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#ifndef _MACRO_ONLY
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
#define SYSTEM_STACK_SIZE 1024

#define disable_int() 		__asm("cpsid   i")
#define enable_int()  		__asm("cpsie   i")
#define dispatch()	  		{ __asm("cpsie   i");SCB->ICSR = SCB_ICSR_PENDSVSET_Msk; }
#define start_dispatch()	{ knl_dispatch_started=TRUE;__asm("cpsie   i"); __asm("svc 0"); }
#define exit_and_dispatch() { PostTaskHook(); start_dispatch();   }

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
#ifndef _MACRO_ONLY
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
extern uint32 knl_dispatch_started;
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */

extern void set_ipl(IPL ipl);
extern IPL  current_ipl(void);
extern void activate_context(TaskType TaskID);

extern void cpu_terminate(void);
extern void sys_exit(void);

extern void cpu_initialize(void);
extern void sys_initialize(void);
extern void tool_initialize(void);
#endif
#endif /* COM_CLANG_C_TOPPERS_OSEK_PORTABLE_ARMV7_M_PORTABLE_H_ */
