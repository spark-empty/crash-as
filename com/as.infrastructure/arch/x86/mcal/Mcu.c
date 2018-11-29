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
#include "Mcu.h"
#include "Os.h"
#include "asdebug.h"
#ifdef USE_STDRT
#include <rtthread.h>
#include <rthw.h>
#endif
/* ============================ [ MACROS    ] ====================================================== */
#define AS_LOG_MCU 1
#define enable_int() asm("sti")
#define disable_int() asm("cli")

/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
extern void serial_putc(const char c);
extern void rt_console_putc(int c);
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void __putchar(char ch)
{
	(void)ch;
#ifdef USE_STDRT
	rt_console_putc(ch);
#else
	serial_putc(ch);
#endif
}

#ifndef __GNUC__
int putchar( int ch )	/* for printf */
{
	__putchar(ch);
  return ch;
}
#endif
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

}

Mcu_PllStatusType Mcu_GetPllStatus( void ) {
	return MCU_PLL_LOCKED;
}


Mcu_ResetType Mcu_GetResetReason( void )
{
	return MCU_POWER_ON_RESET;
}

#ifdef __AS_BOOTLOADER__
void StartOsTick(void)
{

}
#endif

void tpl_shutdown(void)
{
	while(1);
}
#ifdef USE_STDRT
void rt_low_level_init(void)
{
}
void tpl_primary_syscall_handler(void)
{
	while(1);
}
#endif
void Mcu_DistributePllClock( void )
{
}

int EnableInterrupts() {
	enable_int();
	return 0;
}

int DisableInterrupts() {
	disable_int();
	return 0;
}

imask_t __Irq_Save(void)
{
	imask_t level;
	__asm__ __volatile__("pushfl ; popl %0 ; cli":"=g" (level): :"memory");
	return level;
}

void Irq_Restore(imask_t irq_state)
{
	 __asm__ __volatile__("pushl %0 ; popfl": :"g" (irq_state):"memory", "cc");
}

void  Irq_Enable(void)
{
	enable_int();
}

void Irq_Disable(void)
{
	disable_int();
}


#ifdef USE_STDRT
#ifdef RT_USING_DFS
#include <time.h>
time_t mktime (struct tm *tim_p)
{
	return 0;
}
struct tm * localtime(const time_t *timer)
{
	static struct tm tm0 = {0,};

	return &tm0;
}
#endif
#endif
