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

#include <assert.h>
#include <string.h>
#include "Std_Types.h"
#include "Mcu.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#if defined(USE_DEM)
#include "Dem.h"
#endif
#include "Os.h"
#ifndef USE_STDRT
#include "serial.h"
#include "irq.h"
#else
#include "rthw.h"
#endif
#include "asdebug.h"

#include "stdio_cfg.h"
/* ============================ [ MACROS    ] ====================================================== */
#define RESET() ((reset_t)(0x8040))()
/* ============================ [ TYPES     ] ====================================================== */
typedef void (*reset_t)(void);
/* ============================ [ DECLARES  ] ====================================================== */
extern void timer_init(void (*cbk)(void));
#ifdef USE_STDRT
void rt_console_putc(int c);
#endif
extern void vic_setup(void);
extern unsigned int _start;
#ifdef USE_CLIB_STDIO_CAN
extern void Can_putc(char ch);
#endif
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void Stdio_PutChar(char ch)
{
#ifndef USE_STDRT
	serial_send_char(ch);
#else
	rt_console_putc(ch);
#endif

#ifdef USE_CLIB_STDIO_CAN
	Can_putc(ch);
#endif
}

void Mcu_Init(const Mcu_ConfigType *configPtr)
{
	(void)configPtr;
}

void Mcu_SetMode( Mcu_ModeType McuMode ) {
	(void)McuMode;
}

/**
 * Get the system clock in Hz. It calculates the clock from the
 * different register settings in HW.
 */
uint32_t McuE_GetSystemClock(void)
{
  return 0u;
}
Std_ReturnType Mcu_InitClock( const Mcu_ClockType ClockSetting ) {
	(void)ClockSetting;

    return E_OK;
}

void Mcu_PerformReset( void ) {
	imask_t mask;
	Irq_Save(mask);
    RESET();
}

Mcu_PllStatusType Mcu_GetPllStatus( void ) {
	return MCU_PLL_LOCKED;
}


Mcu_ResetType Mcu_GetResetReason( void )
{
	return MCU_POWER_ON_RESET;
}

void StartOsTick(void)
{
	timer_init(NULL);
}

void tpl_shutdown(void)
{
	imask_t mask;
	Irq_Save(mask);
	while(1);
}
#ifdef __RTTHREAD_OS__

void rt_low_level_init(void)
{
	/* copy ISR */
	memcpy((void*)0x0000,(void*)0x8000,64);
}
void machine_shutdown(void)
{
	rt_hw_interrupt_disable();
	while(1);
}
#endif

void Mcu_DistributePllClock( void )
{
	imask_t mask;
#ifndef USE_STDRT
	vic_setup();
	irq_init();
	serial_init();
#endif

	Irq_Save(mask);
#ifndef USE_STDRT
#ifndef __AS_BOOTLOADER__
	timer_init(NULL);
#endif
	printf(" >> versatilepb startup done,start @%p\n",&_start);
#endif
}

void TaskIdleHook(void)
{
	FLUSH_STDIO_IF(1);
}
