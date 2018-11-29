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
//#include "Cpu.h"
//#include "Ramlog.h"
#include "Os.h"
//#include "isr.h"

//#define USE_LDEBUG_PRINTF 1
#include "asdebug.h"
#include "hw_memmap.h"
#include "hw_types.h"
#include "gpio.h"
#include "lm3sinterrupt.h"
#include "sysctl.h"
#include "uart.h"
#include "systick.h"

/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
static void Usart_Init(void)
{
    /* Enable the peripherals used by this example. */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    /* Enable processor interrupts. */
    /* IntMasterEnable(); */

    /* Set GPIO A0 and A1 as UART pins. */
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    /* Configure the UART for 115,200, 8-N-1 operation. */
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                         UART_CONFIG_PAR_NONE));

    /* Enable the UART interrupt.
     *
     * IntEnable(INT_UART0);
     * UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
     */
}
/* ============================ [ FUNCTIONS ] ====================================================== */
void __putchar(char ch)
{
  UARTCharPut(UART0_BASE, ch);
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
  return SysCtlClockGet();
}
Std_ReturnType Mcu_InitClock( const Mcu_ClockType ClockSetting ) {

    /* Set the clocking to run directly from the crystal. */
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_8MHZ);
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

void Mcu_DistributePllClock( void )
{
	Usart_Init();

	SysTickPeriodSet(McuE_GetSystemClock() / 1000);
	SysTickIntEnable();
	SysTickEnable();
}
#ifdef __ASKAR_OS__
void knl_system_tick_handler(void)
{
	SignalCounter(0);
}
#endif
