//*****************************************************************************
//
// sysctl.c - Driver for the system controller.
//
// Copyright (c) 2005-2007 Luminary Micro, Inc.  All rights reserved.
// 
// Software License Agreement
// 
// Luminary Micro, Inc. (LMI) is supplying this software for use solely and
// exclusively on LMI's microcontroller products.
// 
// The software is owned by LMI and/or its suppliers, and is protected under
// applicable copyright laws.  All rights are reserved.  Any use in violation
// of the foregoing restrictions may subject the user to criminal sanctions
// under applicable laws, as well as to civil liability for the breach of the
// terms and conditions of this license.
// 
// THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
// OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
// LMI SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
// CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 1716 of the Stellaris Peripheral Driver Library.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup sysctl_api
//! @{
//
//*****************************************************************************

#include "../hw_ints.h"
#include "../hw_memmap.h"
#include "../hw_nvic.h"
#include "../hw_sysctl.h"
#include "../hw_types.h"
#include "cpu.h"
#include "debug.h"
#include "sysctl.h"
#include "lm3sinterrupt.h"

//*****************************************************************************
//
// This macro extracts the array index out of the peripheral number.
//
//*****************************************************************************
#define SYSCTL_PERIPH_INDEX(a)  (((a) >> 28) & 0xf)

//*****************************************************************************
//
// This macro constructs the peripheral bit mask from the peripheral number.
//
//*****************************************************************************
#define SYSCTL_PERIPH_MASK(a) (((a) & 0xffff) << (((a) & 0x001f0000) >> 16))

//*****************************************************************************
//
// An array that maps the "peripheral set" number (which is stored in the upper
// nibble of the SYSCTL_PERIPH_* defines) to the SYSCTL DC? register that
// contains the peripheral present bit for that peripheral.
//
//*****************************************************************************
static const unsigned long g_pulDCRegs[] =
{
    SYSCTL_DC1,
    SYSCTL_DC2,
    SYSCTL_DC4,
    SYSCTL_DC1
};

//*****************************************************************************
//
// An array that maps the "peripheral set" number (which is stored in the upper
// nibble of the SYSCTL_PERIPH_* defines) to the SYSCTL_SRCR? register that
// controls the software reset for that peripheral.
//
//*****************************************************************************
static const unsigned long g_pulSRCRRegs[] =
{
    SYSCTL_SRCR0,
    SYSCTL_SRCR1,
    SYSCTL_SRCR2
};

//*****************************************************************************
//
// An array that maps the "peripheral set" number (which is stored in the upper
// nibble of the SYSCTL_PERIPH_* defines) to the SYSCTL_RCGC? register that
// controls the run-mode enable for that peripheral.
//
//*****************************************************************************
static const unsigned long g_pulRCGCRegs[] =
{
    SYSCTL_RCGC0,
    SYSCTL_RCGC1,
    SYSCTL_RCGC2
};

//*****************************************************************************
//
// An array that maps the "peripheral set" number (which is stored in the upper
// nibble of the SYSCTL_PERIPH_* defines) to the SYSCTL_SCGC? register that
// controls the sleep-mode enable for that peripheral.
//
//*****************************************************************************
static const unsigned long g_pulSCGCRegs[] =
{
    SYSCTL_SCGC0,
    SYSCTL_SCGC1,
    SYSCTL_SCGC2
};

//*****************************************************************************
//
// An array that maps the "peripheral set" number (which is stored in the upper
// nibble of the SYSCTL_PERIPH_* defines) to the SYSCTL_DCGC? register that
// controls the deep-sleep-mode enable for that peripheral.
//
//*****************************************************************************
static const unsigned long g_pulDCGCRegs[] =
{
    SYSCTL_DCGC0,
    SYSCTL_DCGC1,
    SYSCTL_DCGC2
};

//*****************************************************************************
//
// An array that maps the crystal number in RCC to a frequency.
//
//*****************************************************************************
static const unsigned long g_pulXtals[] =
{
    1000000,
    1843200,
    2000000,
    2457600,
    3579545,
    3686400,
    4000000,
    4096000,
    4915200,
    5000000,
    5120000,
    6000000,
    6144000,
    7372800,
    8000000,
    8192000
};

//*****************************************************************************
//
//! Gets the size of the SRAM.
//!
//! This function determines the size of the SRAM on the Stellaris device.
//!
//! \return The total number of bytes of SRAM.
//
//*****************************************************************************
unsigned long
SysCtlSRAMSizeGet(void)
{
    //
    // Compute the size of the SRAM.
    //
    return(((HWREG(SYSCTL_DC0) & SYSCTL_DC0_SRAMSZ_MASK) >> 8) + 0x100);
}

//*****************************************************************************
//
//! Gets the size of the flash.
//!
//! This function determines the size of the flash on the Stellaris device.
//!
//! \return The total number of bytes of flash.
//
//*****************************************************************************
unsigned long
SysCtlFlashSizeGet(void)
{
    //
    // Compute the size of the flash.
    //
    return(((HWREG(SYSCTL_DC0) & SYSCTL_DC0_FLASHSZ_MASK) << 11) + 0x800);
}

//*****************************************************************************
//
//! Determines if a pin is present.
//!
//! \param ulPin is the pin in question.
//!
//! Determines if a particular pin is present in the device.  The PWM, analog
//! comparators, ADC, and timers have a varying number of pins across members
//! of the Stellaris family; this will determine which are present on this
//! device.
//!
//! The \b ulPin argument must be only one of the following values:
//! \b SYSCTL_PIN_PWM0, \b SYSCTL_PIN_PWM1, \b SYSCTL_PIN_PWM2,
//! \b SYSCTL_PIN_PWM3, \b SYSCTL_PIN_PWM4, \b SYSCTL_PIN_PWM5,
//! \b SYSCTL_PIN_C0MINUS, \b SYSCTL_PIN_C0PLUS, \b SYSCTL_PIN_C0O,
//! \b SYSCTL_PIN_C1MINUS, \b SYSCTL_PIN_C1PLUS, \b SYSCTL_PIN_C1O,
//! \b SYSCTL_PIN_C2MINUS, \b SYSCTL_PIN_C2PLUS, \b SYSCTL_PIN_C2O,
//! \b SYSCTL_PIN_ADC0, \b SYSCTL_PIN_ADC1, \b SYSCTL_PIN_ADC2,
//! \b SYSCTL_PIN_ADC3, \b SYSCTL_PIN_ADC4, \b SYSCTL_PIN_ADC5,
//! \b SYSCTL_PIN_ADC6, \b SYSCTL_PIN_ADC7, \b SYSCTL_PIN_CCP0,
//! \b SYSCTL_PIN_CCP1, \b SYSCTL_PIN_CCP2, \b SYSCTL_PIN_CCP3,
//! \b SYSCTL_PIN_CCP4, \b SYSCTL_PIN_CCP5, \b SYSCTL_PIN_CCP6,
//! \b SYSCTL_PIN_CCP7, \b SYSCTL_PIN_32KHZ, or \b SYSCTL_PIN_MC_FAULT0.
//!
//! \return Returns \b true if the specified pin is present and \b false if it
//! is not.
//
//*****************************************************************************
tBoolean
SysCtlPinPresent(unsigned long ulPin)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPin == SYSCTL_PIN_PWM0) ||
           (ulPin == SYSCTL_PIN_PWM1) ||
           (ulPin == SYSCTL_PIN_PWM2) ||
           (ulPin == SYSCTL_PIN_PWM3) ||
           (ulPin == SYSCTL_PIN_PWM4) ||
           (ulPin == SYSCTL_PIN_PWM5) ||
           (ulPin == SYSCTL_PIN_C0MINUS) ||
           (ulPin == SYSCTL_PIN_C0PLUS) ||
           (ulPin == SYSCTL_PIN_C0O) ||
           (ulPin == SYSCTL_PIN_C1MINUS) ||
           (ulPin == SYSCTL_PIN_C1PLUS) ||
           (ulPin == SYSCTL_PIN_C1O) ||
           (ulPin == SYSCTL_PIN_C2MINUS) ||
           (ulPin == SYSCTL_PIN_C2PLUS) ||
           (ulPin == SYSCTL_PIN_C2O) ||
           (ulPin == SYSCTL_PIN_MC_FAULT0) ||
           (ulPin == SYSCTL_PIN_ADC0) ||
           (ulPin == SYSCTL_PIN_ADC1) ||
           (ulPin == SYSCTL_PIN_ADC2) ||
           (ulPin == SYSCTL_PIN_ADC3) ||
           (ulPin == SYSCTL_PIN_ADC4) ||
           (ulPin == SYSCTL_PIN_ADC5) ||
           (ulPin == SYSCTL_PIN_ADC6) ||
           (ulPin == SYSCTL_PIN_ADC7) ||
           (ulPin == SYSCTL_PIN_CCP0) ||
           (ulPin == SYSCTL_PIN_CCP1) ||
           (ulPin == SYSCTL_PIN_CCP2) ||
           (ulPin == SYSCTL_PIN_CCP3) ||
           (ulPin == SYSCTL_PIN_CCP4) ||
           (ulPin == SYSCTL_PIN_CCP5) ||
           (ulPin == SYSCTL_PIN_32KHZ));

    //
    // Determine if this pin is present.
    //
    if(HWREG(SYSCTL_DC3) & ulPin)
    {
        return(true);
    }
    else
    {
        return(false);
    }
}

//*****************************************************************************
//
//! Determines if a peripheral is present.
//!
//! \param ulPeripheral is the peripheral in question.
//!
//! Determines if a particular peripheral is present in the device.  Each
//! member of the Stellaris family has a different peripheral set; this will
//! determine which are present on this device.
//!
//! The \b ulPeripheral argument must be only one of the following values:
//! \b SYSCTL_PERIPH_ADC, \b SYSCTL_PERIPH_CAN0, \b SYSCTL_PERIPH_CAN1,
//! \b SYSCTL_PERIPH_CAN2, \b SYSCTL_PERIPH_COMP0, \b SYSCTL_PERIPH_COMP1,
//! \b SYSCTL_PERIPH_COMP2, \b SYSCTL_PERIPH_ETH, \b SYSCTL_PERIPH_GPIOA,
//! \b SYSCTL_PERIPH_GPIOB, \b SYSCTL_PERIPH_GPIOC, \b SYSCTL_PERIPH_GPIOD,
//! \b SYSCTL_PERIPH_GPIOE, \b SYSCTL_PERIPH_GPIOF, \b SYSCTL_PERIPH_GPIOG,
//! \b SYSCTL_PERIPH_GPIOH, \b SYSCTL_PERIPH_HIBERNATE, \b SYSCTL_PERIPH_I2C0,
//! \b SYSCTL_PERIPH_I2C1, \b SYSCTL_PERIPH_MPU, \b SYSCTL_PERIPH_PLL,
//! \b SYSCTL_PERIPH_PWM, \b SYSCTL_PERIPH_QEI0, \b SYSCTL_PERIPH_QEI1,
//! \b SYSCTL_PERIPH_SSI0, \b SYSCTL_PERIPH_SSI1, \b SYSCTL_PERIPH_TEMP,
//! \b SYSCTL_PERIPH_TIMER0, \b SYSCTL_PERIPH_TIMER1, \b SYSCTL_PERIPH_TIMER2,
//! \b SYSCTL_PERIPH_TIMER3, \b SYSCTL_PERIPH_UART0, \b SYSCTL_PERIPH_UART1,
//! \b SYSCTL_PERIPH_UART2, or \b SYSCTL_PERIPH_WDOG.
//!
//! \return Returns \b true if the specified peripheral is present and \b false
//! if it is not.
//
//*****************************************************************************
tBoolean
SysCtlPeripheralPresent(unsigned long ulPeripheral)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPeripheral == SYSCTL_PERIPH_ADC) ||
           (ulPeripheral == SYSCTL_PERIPH_CAN0) ||
           (ulPeripheral == SYSCTL_PERIPH_CAN1) ||
           (ulPeripheral == SYSCTL_PERIPH_CAN2) ||
           (ulPeripheral == SYSCTL_PERIPH_COMP0) ||
           (ulPeripheral == SYSCTL_PERIPH_COMP1) ||
           (ulPeripheral == SYSCTL_PERIPH_COMP2) ||
           (ulPeripheral == SYSCTL_PERIPH_ETH) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOA) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOB) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOC) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOD) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOE) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOF) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOG) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOH) ||
           (ulPeripheral == SYSCTL_PERIPH_HIBERNATE) ||
           (ulPeripheral == SYSCTL_PERIPH_I2C0) ||
           (ulPeripheral == SYSCTL_PERIPH_I2C1) ||
           (ulPeripheral == SYSCTL_PERIPH_MPU) ||
           (ulPeripheral == SYSCTL_PERIPH_PLL) ||
           (ulPeripheral == SYSCTL_PERIPH_PWM) ||
           (ulPeripheral == SYSCTL_PERIPH_QEI0) ||
           (ulPeripheral == SYSCTL_PERIPH_QEI1) ||
           (ulPeripheral == SYSCTL_PERIPH_SSI0) ||
           (ulPeripheral == SYSCTL_PERIPH_SSI1) ||
           (ulPeripheral == SYSCTL_PERIPH_TEMP) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER0) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER1) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER2) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER3) ||
           (ulPeripheral == SYSCTL_PERIPH_UART0) ||
           (ulPeripheral == SYSCTL_PERIPH_UART1) ||
           (ulPeripheral == SYSCTL_PERIPH_UART2) ||
           (ulPeripheral == SYSCTL_PERIPH_WDOG));

    //
    // Read the correct DC register and determine if this peripheral exists.
    //
    if(HWREG(g_pulDCRegs[SYSCTL_PERIPH_INDEX(ulPeripheral)]) &
       SYSCTL_PERIPH_MASK(ulPeripheral))
    {
        return(true);
    }
    else
    {
        return(false);
    }
}

//*****************************************************************************
//
//! Performs a software reset of a peripheral.
//!
//! \param ulPeripheral is the peripheral to reset.
//!
//! This function performs a software reset of the specified peripheral.  An
//! individual peripheral reset signal is asserted for a brief period and then
//! deasserted, leaving the peripheral in a operating state but in its reset
//! condition.
//!
//! The \b ulPeripheral argument must be only one of the following values:
//! \b SYSCTL_PERIPH_ADC, \b SYSCTL_PERIPH_CAN0, \b SYSCTL_PERIPH_CAN1,
//! \b SYSCTL_PERIPH_CAN2, \b SYSCTL_PERIPH_COMP0, \b SYSCTL_PERIPH_COMP1,
//! \b SYSCTL_PERIPH_COMP2, \b SYSCTL_PERIPH_ETH, \b SYSCTL_PERIPH_GPIOA,
//! \b SYSCTL_PERIPH_GPIOB, \b SYSCTL_PERIPH_GPIOC, \b SYSCTL_PERIPH_GPIOD,
//! \b SYSCTL_PERIPH_GPIOE, \b SYSCTL_PERIPH_GPIOF, \b SYSCTL_PERIPH_GPIOG,
//! \b SYSCTL_PERIPH_GPIOH, \b SYSCTL_PERIPH_HIBERNATE, \b SYSCTL_PERIPH_I2C0,
//! \b SYSCTL_PERIPH_I2C1, \b SYSCTL_PERIPH_PWM, \b SYSCTL_PERIPH_QEI0,
//! \b SYSCTL_PERIPH_QEI1, \b SYSCTL_PERIPH_SSI0, \b SYSCTL_PERIPH_SSI1,
//! \b SYSCTL_PERIPH_TIMER0, \b SYSCTL_PERIPH_TIMER1, \b SYSCTL_PERIPH_TIMER2,
//! \b SYSCTL_PERIPH_TIMER3, \b SYSCTL_PERIPH_UART0, \b SYSCTL_PERIPH_UART1,
//! \b SYSCTL_PERIPH_UART2, or \b SYSCTL_PERIPH_WDOG.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralReset(unsigned long ulPeripheral)
{
    volatile unsigned long ulDelay;

    //
    // Check the arguments.
    //
    ASSERT((ulPeripheral == SYSCTL_PERIPH_ADC) ||
           (ulPeripheral == SYSCTL_PERIPH_CAN0) ||
           (ulPeripheral == SYSCTL_PERIPH_CAN1) ||
           (ulPeripheral == SYSCTL_PERIPH_CAN2) ||
           (ulPeripheral == SYSCTL_PERIPH_COMP0) ||
           (ulPeripheral == SYSCTL_PERIPH_COMP1) ||
           (ulPeripheral == SYSCTL_PERIPH_COMP2) ||
           (ulPeripheral == SYSCTL_PERIPH_ETH) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOA) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOB) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOC) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOD) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOE) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOF) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOG) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOH) ||
           (ulPeripheral == SYSCTL_PERIPH_HIBERNATE) ||
           (ulPeripheral == SYSCTL_PERIPH_I2C0) ||
           (ulPeripheral == SYSCTL_PERIPH_I2C1) ||
           (ulPeripheral == SYSCTL_PERIPH_PWM) ||
           (ulPeripheral == SYSCTL_PERIPH_QEI0) ||
           (ulPeripheral == SYSCTL_PERIPH_QEI1) ||
           (ulPeripheral == SYSCTL_PERIPH_SSI0) ||
           (ulPeripheral == SYSCTL_PERIPH_SSI1) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER0) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER1) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER2) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER3) ||
           (ulPeripheral == SYSCTL_PERIPH_UART0) ||
           (ulPeripheral == SYSCTL_PERIPH_UART1) ||
           (ulPeripheral == SYSCTL_PERIPH_UART2) ||
           (ulPeripheral == SYSCTL_PERIPH_WDOG));

    //
    // Put the peripheral into the reset state.
    //
    HWREG(g_pulSRCRRegs[SYSCTL_PERIPH_INDEX(ulPeripheral)]) |=
        SYSCTL_PERIPH_MASK(ulPeripheral);

    //
    // Delay for a little bit.
    //
    for(ulDelay = 0; ulDelay < 16; ulDelay++)
    {
    }

    //
    // Take the peripheral out of the reset state.
    //
    HWREG(g_pulSRCRRegs[SYSCTL_PERIPH_INDEX(ulPeripheral)]) &=
        ~SYSCTL_PERIPH_MASK(ulPeripheral);
}

//*****************************************************************************
//
//! Enables a peripheral.
//!
//! \param ulPeripheral is the peripheral to enable.
//!
//! Peripherals are enabled with this function.  At power-up, all peripherals
//! are disabled; they must be enabled in order to operate or respond to
//! register reads/writes.
//!
//! The \b ulPeripheral argument must be only one of the following values:
//! \b SYSCTL_PERIPH_ADC, \b SYSCTL_PERIPH_CAN0, \b SYSCTL_PERIPH_CAN1,
//! \b SYSCTL_PERIPH_CAN2, \b SYSCTL_PERIPH_COMP0, \b SYSCTL_PERIPH_COMP1,
//! \b SYSCTL_PERIPH_COMP2, \b SYSCTL_PERIPH_ETH, \b SYSCTL_PERIPH_GPIOA,
//! \b SYSCTL_PERIPH_GPIOB, \b SYSCTL_PERIPH_GPIOC, \b SYSCTL_PERIPH_GPIOD,
//! \b SYSCTL_PERIPH_GPIOE, \b SYSCTL_PERIPH_GPIOF, \b SYSCTL_PERIPH_GPIOG,
//! \b SYSCTL_PERIPH_GPIOH, \b SYSCTL_PERIPH_HIBERNATE, \b SYSCTL_PERIPH_I2C0,
//! \b SYSCTL_PERIPH_I2C1, \b SYSCTL_PERIPH_PWM, \b SYSCTL_PERIPH_QEI0,
//! \b SYSCTL_PERIPH_QEI1, \b SYSCTL_PERIPH_SSI0, \b SYSCTL_PERIPH_SSI1,
//! \b SYSCTL_PERIPH_TIMER0, \b SYSCTL_PERIPH_TIMER1, \b SYSCTL_PERIPH_TIMER2,
//! \b SYSCTL_PERIPH_TIMER3, \b SYSCTL_PERIPH_UART0, \b SYSCTL_PERIPH_UART1,
//! \b SYSCTL_PERIPH_UART2, or \b SYSCTL_PERIPH_WDOG.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralEnable(unsigned long ulPeripheral)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPeripheral == SYSCTL_PERIPH_ADC) ||
           (ulPeripheral == SYSCTL_PERIPH_CAN0) ||
           (ulPeripheral == SYSCTL_PERIPH_CAN1) ||
           (ulPeripheral == SYSCTL_PERIPH_CAN2) ||
           (ulPeripheral == SYSCTL_PERIPH_COMP0) ||
           (ulPeripheral == SYSCTL_PERIPH_COMP1) ||
           (ulPeripheral == SYSCTL_PERIPH_COMP2) ||
           (ulPeripheral == SYSCTL_PERIPH_ETH) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOA) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOB) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOC) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOD) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOE) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOF) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOG) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOH) ||
           (ulPeripheral == SYSCTL_PERIPH_HIBERNATE) ||
           (ulPeripheral == SYSCTL_PERIPH_I2C0) ||
           (ulPeripheral == SYSCTL_PERIPH_I2C1) ||
           (ulPeripheral == SYSCTL_PERIPH_PWM) ||
           (ulPeripheral == SYSCTL_PERIPH_QEI0) ||
           (ulPeripheral == SYSCTL_PERIPH_QEI1) ||
           (ulPeripheral == SYSCTL_PERIPH_SSI0) ||
           (ulPeripheral == SYSCTL_PERIPH_SSI1) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER0) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER1) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER2) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER3) ||
           (ulPeripheral == SYSCTL_PERIPH_UART0) ||
           (ulPeripheral == SYSCTL_PERIPH_UART1) ||
           (ulPeripheral == SYSCTL_PERIPH_UART2) ||
           (ulPeripheral == SYSCTL_PERIPH_WDOG));

    //
    // Enable this peripheral.
    //
    HWREG(g_pulRCGCRegs[SYSCTL_PERIPH_INDEX(ulPeripheral)]) |=
        SYSCTL_PERIPH_MASK(ulPeripheral);
}

//*****************************************************************************
//
//! Disables a peripheral.
//!
//! \param ulPeripheral is the peripheral to disable.
//!
//! Peripherals are disabled with this function.  Once disabled, they will not
//! operate or respond to register reads/writes.
//!
//! The \b ulPeripheral argument must be only one of the following values:
//! \b SYSCTL_PERIPH_ADC, \b SYSCTL_PERIPH_CAN0, \b SYSCTL_PERIPH_CAN1,
//! \b SYSCTL_PERIPH_CAN2, \b SYSCTL_PERIPH_COMP0, \b SYSCTL_PERIPH_COMP1,
//! \b SYSCTL_PERIPH_COMP2, \b SYSCTL_PERIPH_ETH, \b SYSCTL_PERIPH_GPIOA,
//! \b SYSCTL_PERIPH_GPIOB, \b SYSCTL_PERIPH_GPIOC, \b SYSCTL_PERIPH_GPIOD,
//! \b SYSCTL_PERIPH_GPIOE, \b SYSCTL_PERIPH_GPIOF, \b SYSCTL_PERIPH_GPIOG,
//! \b SYSCTL_PERIPH_GPIOH, \b SYSCTL_PERIPH_HIBERNATE, \b SYSCTL_PERIPH_I2C0,
//! \b SYSCTL_PERIPH_I2C1, \b SYSCTL_PERIPH_PWM, \b SYSCTL_PERIPH_QEI0,
//! \b SYSCTL_PERIPH_QEI1, \b SYSCTL_PERIPH_SSI0, \b SYSCTL_PERIPH_SSI1,
//! \b SYSCTL_PERIPH_TIMER0, \b SYSCTL_PERIPH_TIMER1, \b SYSCTL_PERIPH_TIMER2,
//! \b SYSCTL_PERIPH_TIMER3, \b SYSCTL_PERIPH_UART0, \b SYSCTL_PERIPH_UART1,
//! \b SYSCTL_PERIPH_UART2, or \b SYSCTL_PERIPH_WDOG.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralDisable(unsigned long ulPeripheral)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPeripheral == SYSCTL_PERIPH_ADC) ||
           (ulPeripheral == SYSCTL_PERIPH_CAN0) ||
           (ulPeripheral == SYSCTL_PERIPH_CAN1) ||
           (ulPeripheral == SYSCTL_PERIPH_CAN2) ||
           (ulPeripheral == SYSCTL_PERIPH_COMP0) ||
           (ulPeripheral == SYSCTL_PERIPH_COMP1) ||
           (ulPeripheral == SYSCTL_PERIPH_COMP2) ||
           (ulPeripheral == SYSCTL_PERIPH_ETH) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOA) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOB) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOC) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOD) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOE) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOF) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOG) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOH) ||
           (ulPeripheral == SYSCTL_PERIPH_HIBERNATE) ||
           (ulPeripheral == SYSCTL_PERIPH_I2C0) ||
           (ulPeripheral == SYSCTL_PERIPH_I2C1) ||
           (ulPeripheral == SYSCTL_PERIPH_PWM) ||
           (ulPeripheral == SYSCTL_PERIPH_QEI0) ||
           (ulPeripheral == SYSCTL_PERIPH_QEI1) ||
           (ulPeripheral == SYSCTL_PERIPH_SSI0) ||
           (ulPeripheral == SYSCTL_PERIPH_SSI1) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER0) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER1) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER2) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER3) ||
           (ulPeripheral == SYSCTL_PERIPH_UART0) ||
           (ulPeripheral == SYSCTL_PERIPH_UART1) ||
           (ulPeripheral == SYSCTL_PERIPH_UART2) ||
           (ulPeripheral == SYSCTL_PERIPH_WDOG));

    //
    // Disable this peripheral.
    //
    HWREG(g_pulRCGCRegs[SYSCTL_PERIPH_INDEX(ulPeripheral)]) &=
        ~SYSCTL_PERIPH_MASK(ulPeripheral);
}

//*****************************************************************************
//
//! Enables a peripheral in sleep mode.
//!
//! \param ulPeripheral is the peripheral to enable in sleep mode.
//!
//! This function allows a peripheral to continue operating when the processor
//! goes into sleep mode.  Since the clocking configuration of the device does
//! not change, any peripheral can safely continue operating while the
//! processor is in sleep mode, and can therefore wake the processor from sleep
//! mode.
//!
//! Sleep mode clocking of peripherals must be enabled via
//! SysCtlPeripheralClockGating(); if disabled, the peripheral sleep mode
//! configuration is maintained but has no effect when sleep mode is entered.
//!
//! The \b ulPeripheral argument must be only one of the following values:
//! \b SYSCTL_PERIPH_ADC, \b SYSCTL_PERIPH_CAN0, \b SYSCTL_PERIPH_CAN1,
//! \b SYSCTL_PERIPH_CAN2, \b SYSCTL_PERIPH_COMP0, \b SYSCTL_PERIPH_COMP1,
//! \b SYSCTL_PERIPH_COMP2, \b SYSCTL_PERIPH_ETH, \b SYSCTL_PERIPH_GPIOA,
//! \b SYSCTL_PERIPH_GPIOB, \b SYSCTL_PERIPH_GPIOC, \b SYSCTL_PERIPH_GPIOD,
//! \b SYSCTL_PERIPH_GPIOE, \b SYSCTL_PERIPH_GPIOF, \b SYSCTL_PERIPH_GPIOG,
//! \b SYSCTL_PERIPH_GPIOH, \b SYSCTL_PERIPH_HIBERNATE, \b SYSCTL_PERIPH_I2C0,
//! \b SYSCTL_PERIPH_I2C1, \b SYSCTL_PERIPH_PWM, \b SYSCTL_PERIPH_QEI0,
//! \b SYSCTL_PERIPH_QEI1, \b SYSCTL_PERIPH_SSI0, \b SYSCTL_PERIPH_SSI1,
//! \b SYSCTL_PERIPH_TIMER0, \b SYSCTL_PERIPH_TIMER1, \b SYSCTL_PERIPH_TIMER2,
//! \b SYSCTL_PERIPH_TIMER3, \b SYSCTL_PERIPH_UART0, \b SYSCTL_PERIPH_UART1,
//! \b SYSCTL_PERIPH_UART2, or \b SYSCTL_PERIPH_WDOG.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralSleepEnable(unsigned long ulPeripheral)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPeripheral == SYSCTL_PERIPH_ADC) ||
           (ulPeripheral == SYSCTL_PERIPH_CAN0) ||
           (ulPeripheral == SYSCTL_PERIPH_CAN1) ||
           (ulPeripheral == SYSCTL_PERIPH_CAN2) ||
           (ulPeripheral == SYSCTL_PERIPH_COMP0) ||
           (ulPeripheral == SYSCTL_PERIPH_COMP1) ||
           (ulPeripheral == SYSCTL_PERIPH_COMP2) ||
           (ulPeripheral == SYSCTL_PERIPH_ETH) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOA) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOB) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOC) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOD) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOE) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOF) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOG) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOH) ||
           (ulPeripheral == SYSCTL_PERIPH_HIBERNATE) ||
           (ulPeripheral == SYSCTL_PERIPH_I2C0) ||
           (ulPeripheral == SYSCTL_PERIPH_I2C1) ||
           (ulPeripheral == SYSCTL_PERIPH_PWM) ||
           (ulPeripheral == SYSCTL_PERIPH_QEI0) ||
           (ulPeripheral == SYSCTL_PERIPH_QEI1) ||
           (ulPeripheral == SYSCTL_PERIPH_SSI0) ||
           (ulPeripheral == SYSCTL_PERIPH_SSI1) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER0) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER1) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER2) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER3) ||
           (ulPeripheral == SYSCTL_PERIPH_UART0) ||
           (ulPeripheral == SYSCTL_PERIPH_UART1) ||
           (ulPeripheral == SYSCTL_PERIPH_UART2) ||
           (ulPeripheral == SYSCTL_PERIPH_WDOG));

    //
    // Enable this peripheral in sleep mode.
    //
    HWREG(g_pulSCGCRegs[SYSCTL_PERIPH_INDEX(ulPeripheral)]) |=
        SYSCTL_PERIPH_MASK(ulPeripheral);
}

//*****************************************************************************
//
//! Disables a peripheral in sleep mode.
//!
//! \param ulPeripheral is the peripheral to disable in sleep mode.
//!
//! This function causes a peripheral to stop operating when the processor goes
//! into sleep mode.  Disabling peripherals while in sleep mode helps to lower
//! the current draw of the device.  If enabled (via SysCtlPeripheralEnable()),
//! the peripheral will automatically resume operation when the processor
//! leaves sleep mode, maintaining its entire state from before sleep mode was
//! entered.
//!
//! Sleep mode clocking of peripherals must be enabled via
//! SysCtlPeripheralClockGating(); if disabled, the peripheral sleep mode
//! configuration is maintained but has no effect when sleep mode is entered.
//!
//! The \b ulPeripheral argument must be only one of the following values:
//! \b SYSCTL_PERIPH_ADC, \b SYSCTL_PERIPH_CAN0, \b SYSCTL_PERIPH_CAN1,
//! \b SYSCTL_PERIPH_CAN2, \b SYSCTL_PERIPH_COMP0, \b SYSCTL_PERIPH_COMP1,
//! \b SYSCTL_PERIPH_COMP2, \b SYSCTL_PERIPH_ETH, \b SYSCTL_PERIPH_GPIOA,
//! \b SYSCTL_PERIPH_GPIOB, \b SYSCTL_PERIPH_GPIOC, \b SYSCTL_PERIPH_GPIOD,
//! \b SYSCTL_PERIPH_GPIOE, \b SYSCTL_PERIPH_GPIOF, \b SYSCTL_PERIPH_GPIOG,
//! \b SYSCTL_PERIPH_GPIOH, \b SYSCTL_PERIPH_HIBERNATE, \b SYSCTL_PERIPH_I2C0,
//! \b SYSCTL_PERIPH_I2C1, \b SYSCTL_PERIPH_PWM, \b SYSCTL_PERIPH_QEI0,
//! \b SYSCTL_PERIPH_QEI1, \b SYSCTL_PERIPH_SSI0, \b SYSCTL_PERIPH_SSI1,
//! \b SYSCTL_PERIPH_TIMER0, \b SYSCTL_PERIPH_TIMER1, \b SYSCTL_PERIPH_TIMER2,
//! \b SYSCTL_PERIPH_TIMER3, \b SYSCTL_PERIPH_UART0, \b SYSCTL_PERIPH_UART1,
//! \b SYSCTL_PERIPH_UART2, or \b SYSCTL_PERIPH_WDOG.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralSleepDisable(unsigned long ulPeripheral)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPeripheral == SYSCTL_PERIPH_ADC) ||
           (ulPeripheral == SYSCTL_PERIPH_CAN0) ||
           (ulPeripheral == SYSCTL_PERIPH_CAN1) ||
           (ulPeripheral == SYSCTL_PERIPH_CAN2) ||
           (ulPeripheral == SYSCTL_PERIPH_COMP0) ||
           (ulPeripheral == SYSCTL_PERIPH_COMP1) ||
           (ulPeripheral == SYSCTL_PERIPH_COMP2) ||
           (ulPeripheral == SYSCTL_PERIPH_ETH) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOA) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOB) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOC) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOD) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOE) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOF) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOG) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOH) ||
           (ulPeripheral == SYSCTL_PERIPH_HIBERNATE) ||
           (ulPeripheral == SYSCTL_PERIPH_I2C0) ||
           (ulPeripheral == SYSCTL_PERIPH_I2C1) ||
           (ulPeripheral == SYSCTL_PERIPH_PWM) ||
           (ulPeripheral == SYSCTL_PERIPH_QEI0) ||
           (ulPeripheral == SYSCTL_PERIPH_QEI1) ||
           (ulPeripheral == SYSCTL_PERIPH_SSI0) ||
           (ulPeripheral == SYSCTL_PERIPH_SSI1) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER0) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER1) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER2) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER3) ||
           (ulPeripheral == SYSCTL_PERIPH_UART0) ||
           (ulPeripheral == SYSCTL_PERIPH_UART1) ||
           (ulPeripheral == SYSCTL_PERIPH_UART2) ||
           (ulPeripheral == SYSCTL_PERIPH_WDOG));

    //
    // Disable this peripheral in sleep mode.
    //
    HWREG(g_pulSCGCRegs[SYSCTL_PERIPH_INDEX(ulPeripheral)]) &=
        ~SYSCTL_PERIPH_MASK(ulPeripheral);
}

//*****************************************************************************
//
//! Enables a peripheral in deep-sleep mode.
//!
//! \param ulPeripheral is the peripheral to enable in deep-sleep mode.
//!
//! This function allows a peripheral to continue operating when the processor
//! goes into deep-sleep mode.  Since the clocking configuration of the device
//! may change, not all peripherals can safely continue operating while the
//! processor is in sleep mode.  Those that must run at a particular frequency
//! (such as a UART) will not work as expected if the clock changes.  It is the
//! responsibility of the caller to make sensible choices.
//!
//! Deep-sleep mode clocking of peripherals must be enabled via
//! SysCtlPeripheralClockGating(); if disabled, the peripheral deep-sleep mode
//! configuration is maintained but has no effect when deep-sleep mode is
//! entered.
//!
//! The \b ulPeripheral argument must be one of the following values:
//! \b SYSCTL_PERIPH_ADC, \b SYSCTL_PERIPH_CAN0, \b SYSCTL_PERIPH_CAN1,
//! \b SYSCTL_PERIPH_CAN2, \b SYSCTL_PERIPH_COMP0, \b SYSCTL_PERIPH_COMP1,
//! \b SYSCTL_PERIPH_COMP2, \b SYSCTL_PERIPH_ETH, \b SYSCTL_PERIPH_GPIOA,
//! \b SYSCTL_PERIPH_GPIOB, \b SYSCTL_PERIPH_GPIOC, \b SYSCTL_PERIPH_GPIOD,
//! \b SYSCTL_PERIPH_GPIOE, \b SYSCTL_PERIPH_GPIOF, \b SYSCTL_PERIPH_GPIOG,
//! \b SYSCTL_PERIPH_GPIOH, \b SYSCTL_PERIPH_HIBERNATE, \b SYSCTL_PERIPH_I2C0,
//! \b SYSCTL_PERIPH_I2C1, \b SYSCTL_PERIPH_PWM, \b SYSCTL_PERIPH_QEI0,
//! \b SYSCTL_PERIPH_QEI1, \b SYSCTL_PERIPH_SSI0, \b SYSCTL_PERIPH_SSI1,
//! \b SYSCTL_PERIPH_TIMER0, \b SYSCTL_PERIPH_TIMER1, \b SYSCTL_PERIPH_TIMER2,
//! \b SYSCTL_PERIPH_TIMER3, \b SYSCTL_PERIPH_UART0, \b SYSCTL_PERIPH_UART1,
//! \b SYSCTL_PERIPH_UART2, or \b SYSCTL_PERIPH_WDOG.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralDeepSleepEnable(unsigned long ulPeripheral)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPeripheral == SYSCTL_PERIPH_ADC) ||
           (ulPeripheral == SYSCTL_PERIPH_CAN0) ||
           (ulPeripheral == SYSCTL_PERIPH_CAN1) ||
           (ulPeripheral == SYSCTL_PERIPH_CAN2) ||
           (ulPeripheral == SYSCTL_PERIPH_COMP0) ||
           (ulPeripheral == SYSCTL_PERIPH_COMP1) ||
           (ulPeripheral == SYSCTL_PERIPH_COMP2) ||
           (ulPeripheral == SYSCTL_PERIPH_ETH) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOA) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOB) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOC) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOD) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOE) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOF) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOG) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOH) ||
           (ulPeripheral == SYSCTL_PERIPH_HIBERNATE) ||
           (ulPeripheral == SYSCTL_PERIPH_I2C0) ||
           (ulPeripheral == SYSCTL_PERIPH_I2C1) ||
           (ulPeripheral == SYSCTL_PERIPH_PWM) ||
           (ulPeripheral == SYSCTL_PERIPH_QEI0) ||
           (ulPeripheral == SYSCTL_PERIPH_QEI1) ||
           (ulPeripheral == SYSCTL_PERIPH_SSI0) ||
           (ulPeripheral == SYSCTL_PERIPH_SSI1) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER0) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER1) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER2) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER3) ||
           (ulPeripheral == SYSCTL_PERIPH_UART0) ||
           (ulPeripheral == SYSCTL_PERIPH_UART1) ||
           (ulPeripheral == SYSCTL_PERIPH_UART2) ||
           (ulPeripheral == SYSCTL_PERIPH_WDOG));

    //
    // Enable this peripheral in deep-sleep mode.
    //
    HWREG(g_pulDCGCRegs[SYSCTL_PERIPH_INDEX(ulPeripheral)]) |=
        SYSCTL_PERIPH_MASK(ulPeripheral);
}

//*****************************************************************************
//
//! Disables a peripheral in deep-sleep mode.
//!
//! \param ulPeripheral is the peripheral to disable in deep-sleep mode.
//!
//! This function causes a peripheral to stop operating when the processor goes
//! into deep-sleep mode.  Disabling peripherals while in deep-sleep mode helps
//! to lower the current draw of the device, and can keep peripherals that
//! require a particular clock frequency from operating when the clock changes
//! as a result of entering deep-sleep mode.  If enabled (via
//! SysCtlPeripheralEnable()), the peripheral will automatically resume
//! operation when the processor leaves deep-sleep mode, maintaining its entire
//! state from before deep-sleep mode was entered.
//!
//! Deep-sleep mode clocking of peripherals must be enabled via
//! SysCtlPeripheralClockGating(); if disabled, the peripheral deep-sleep mode
//! configuration is maintained but has no effect when deep-sleep mode is
//! entered.
//!
//! The \b ulPeripheral argument must be one of the following values:
//! \b SYSCTL_PERIPH_ADC, \b SYSCTL_PERIPH_CAN0, \b SYSCTL_PERIPH_CAN1,
//! \b SYSCTL_PERIPH_CAN2, \b SYSCTL_PERIPH_COMP0, \b SYSCTL_PERIPH_COMP1,
//! \b SYSCTL_PERIPH_COMP2, \b SYSCTL_PERIPH_ETH, \b SYSCTL_PERIPH_GPIOA,
//! \b SYSCTL_PERIPH_GPIOB, \b SYSCTL_PERIPH_GPIOC, \b SYSCTL_PERIPH_GPIOD,
//! \b SYSCTL_PERIPH_GPIOE, \b SYSCTL_PERIPH_GPIOF, \b SYSCTL_PERIPH_GPIOG,
//! \b SYSCTL_PERIPH_GPIOH, \b SYSCTL_PERIPH_HIBERNATE, \b SYSCTL_PERIPH_I2C0,
//! \b SYSCTL_PERIPH_I2C1, \b SYSCTL_PERIPH_PWM, \b SYSCTL_PERIPH_QEI0,
//! \b SYSCTL_PERIPH_QEI1, \b SYSCTL_PERIPH_SSI0, \b SYSCTL_PERIPH_SSI1,
//! \b SYSCTL_PERIPH_TIMER0, \b SYSCTL_PERIPH_TIMER1, \b SYSCTL_PERIPH_TIMER2,
//! \b SYSCTL_PERIPH_TIMER3, \b SYSCTL_PERIPH_UART0, \b SYSCTL_PERIPH_UART1,
//! \b SYSCTL_PERIPH_UART2, or \b SYSCTL_PERIPH_WDOG.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralDeepSleepDisable(unsigned long ulPeripheral)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPeripheral == SYSCTL_PERIPH_ADC) ||
           (ulPeripheral == SYSCTL_PERIPH_CAN0) ||
           (ulPeripheral == SYSCTL_PERIPH_CAN1) ||
           (ulPeripheral == SYSCTL_PERIPH_CAN2) ||
           (ulPeripheral == SYSCTL_PERIPH_COMP0) ||
           (ulPeripheral == SYSCTL_PERIPH_COMP1) ||
           (ulPeripheral == SYSCTL_PERIPH_COMP2) ||
           (ulPeripheral == SYSCTL_PERIPH_ETH) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOA) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOB) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOC) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOD) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOE) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOF) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOG) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOH) ||
           (ulPeripheral == SYSCTL_PERIPH_HIBERNATE) ||
           (ulPeripheral == SYSCTL_PERIPH_I2C0) ||
           (ulPeripheral == SYSCTL_PERIPH_I2C1) ||
           (ulPeripheral == SYSCTL_PERIPH_PWM) ||
           (ulPeripheral == SYSCTL_PERIPH_QEI0) ||
           (ulPeripheral == SYSCTL_PERIPH_QEI1) ||
           (ulPeripheral == SYSCTL_PERIPH_SSI0) ||
           (ulPeripheral == SYSCTL_PERIPH_SSI1) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER0) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER1) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER2) ||
           (ulPeripheral == SYSCTL_PERIPH_TIMER3) ||
           (ulPeripheral == SYSCTL_PERIPH_UART0) ||
           (ulPeripheral == SYSCTL_PERIPH_UART1) ||
           (ulPeripheral == SYSCTL_PERIPH_UART2) ||
           (ulPeripheral == SYSCTL_PERIPH_WDOG));

    //
    // Disable this peripheral in deep-sleep mode.
    //
    HWREG(g_pulDCGCRegs[SYSCTL_PERIPH_INDEX(ulPeripheral)]) &=
        ~SYSCTL_PERIPH_MASK(ulPeripheral);
}

//*****************************************************************************
//
//! Controls peripheral clock gating in sleep and deep-sleep mode.
//!
//! \param bEnable is a boolean that is \b true if the sleep and deep-sleep
//! peripheral configuration should be used and \b false if not.
//!
//! This function controls how peripherals are clocked when the processor goes
//! into sleep or deep-sleep mode.  By default, the peripherals are clocked the
//! same as in run mode; if peripheral clock gating is enabled they are clocked
//! according to the configuration set by SysCtlPeripheralSleepEnable(),
//! SysCtlPeripheralSleepDisable(), SysCtlPeripheralDeepSleepEnable(), and
//! SysCtlPeripheralDeepSleepDisable().
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralClockGating(tBoolean bEnable)
{
    //
    // Enable peripheral clock gating as requested.
    //
    if(bEnable)
    {
        HWREG(SYSCTL_RCC) |= SYSCTL_RCC_ACG;
    }
    else
    {
        HWREG(SYSCTL_RCC) &= ~(SYSCTL_RCC_ACG);
    }
}

//*****************************************************************************
//
//! Registers an interrupt handler for the system control interrupt.
//!
//! \param pfnHandler is a pointer to the function to be called when the system
//! control interrupt occurs.
//!
//! This sets the handler to be called when a system control interrupt occurs.
//! This will enable the global interrupt in the interrupt controller; specific
//! system control interrupts must be enabled via SysCtlIntEnable().  It is the
//! interrupt handler's responsibility to clear the interrupt source via
//! SysCtlIntClear().
//!
//! System control can generate interrupts when the PLL achieves lock, if the
//! internal LDO current limit is exceeded, if the internal oscillator fails,
//! if the main oscillator fails, if the internal LDO output voltage droops too
//! much, if the external voltage droops too much, or if the PLL fails.
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlIntRegister(void (*pfnHandler)(void))
{
    //
    // Register the interrupt handler, returning an error if an error occurs.
    //
    IntRegister(INT_SYSCTL, pfnHandler);

    //
    // Enable the system control interrupt.
    //
    IntEnable(INT_SYSCTL);
}

//*****************************************************************************
//
//! Unregisters the interrupt handler for the system control interrupt.
//!
//! This function will clear the handler to be called when a system control
//! interrupt occurs.  This will also mask off the interrupt in the interrupt
//! controller so that the interrupt handler no longer is called.
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlIntUnregister(void)
{
    //
    // Disable the interrupt.
    //
    IntDisable(INT_SYSCTL);

    //
    // Unregister the interrupt handler.
    //
    IntUnregister(INT_SYSCTL);
}

//*****************************************************************************
//
//! Enables individual system control interrupt sources.
//!
//! \param ulInts is a bit mask of the interrupt sources to be enabled.  Must
//! be a logical OR of \b SYSCTL_INT_PLL_LOCK, \b SYSCTL_INT_CUR_LIMIT,
//! \b SYSCTL_INT_IOSC_FAIL, \b SYSCTL_INT_MOSC_FAIL, \b SYSCTL_INT_POR,
//! \b SYSCTL_INT_BOR, and/or \b SYSCTL_INT_PLL_FAIL.
//!
//! Enables the indicated system control interrupt sources.  Only the sources
//! that are enabled can be reflected to the processor interrupt; disabled
//! sources have no effect on the processor.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlIntEnable(unsigned long ulInts)
{
    //
    // Enable the specified interrupts.
    //
    HWREG(SYSCTL_IMC) |= ulInts;
}

//*****************************************************************************
//
//! Disables individual system control interrupt sources.
//!
//! \param ulInts is a bit mask of the interrupt sources to be disabled.  Must
//! be a logical OR of \b SYSCTL_INT_PLL_LOCK, \b SYSCTL_INT_CUR_LIMIT,
//! \b SYSCTL_INT_IOSC_FAIL, \b SYSCTL_INT_MOSC_FAIL, \b SYSCTL_INT_POR,
//! \b SYSCTL_INT_BOR, and/or \b SYSCTL_INT_PLL_FAIL.
//!
//! Disables the indicated system control interrupt sources.  Only the sources
//! that are enabled can be reflected to the processor interrupt; disabled
//! sources have no effect on the processor.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlIntDisable(unsigned long ulInts)
{
    //
    // Disable the specified interrupts.
    //
    HWREG(SYSCTL_IMC) &= ~(ulInts);
}

//*****************************************************************************
//
//! Clears system control interrupt sources.
//!
//! \param ulInts is a bit mask of the interrupt sources to be cleared.  Must
//! be a logical OR of \b SYSCTL_INT_PLL_LOCK, \b SYSCTL_INT_CUR_LIMIT,
//! \b SYSCTL_INT_IOSC_FAIL, \b SYSCTL_INT_MOSC_FAIL, \b SYSCTL_INT_POR,
//! \b SYSCTL_INT_BOR, and/or \b SYSCTL_INT_PLL_FAIL.
//!
//! The specified system control interrupt sources are cleared, so that they no
//! longer assert.  This must be done in the interrupt handler to keep it from
//! being called again immediately upon exit.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlIntClear(unsigned long ulInts)
{
    //
    // Clear the requested interrupt sources.
    //
    HWREG(SYSCTL_MISC) = ulInts;
}

//*****************************************************************************
//
//! Gets the current interrupt status.
//!
//! \param bMasked is false if the raw interrupt status is required and true if
//! the masked interrupt status is required.
//!
//! This returns the interrupt status for the system controller.  Either the
//! raw interrupt status or the status of interrupts that are allowed to
//! reflect to the processor can be returned.
//!
//! \return The current interrupt status, enumerated as a bit field of
//! \b SYSCTL_INT_PLL_LOCK, \b SYSCTL_INT_CUR_LIMIT, \b SYSCTL_INT_IOSC_FAIL,
//! \b SYSCTL_INT_MOSC_FAIL, \b SYSCTL_INT_POR, \b SYSCTL_INT_BOR, and
//! \b SYSCTL_INT_PLL_FAIL.
//
//*****************************************************************************
unsigned long
SysCtlIntStatus(tBoolean bMasked)
{
    //
    // Return either the interrupt status or the raw interrupt status as
    // requested.
    //
    if(bMasked)
    {
        return(HWREG(SYSCTL_MISC));
    }
    else
    {
        return(HWREG(SYSCTL_RIS));
    }
}

//*****************************************************************************
//
//! Sets the output voltage of the LDO.
//!
//! \param ulVoltage is the required output voltage from the LDO.  Must be one
//! of \b SYSCTL_LDO_2_25V, \b SYSCTL_LDO_2_30V, \b SYSCTL_LDO_2_35V,
//! \b SYSCTL_LDO_2_40V, \b SYSCTL_LDO_2_45V, \b SYSCTL_LDO_2_50V,
//! \b SYSCTL_LDO_2_55V, \b SYSCTL_LDO_2_60V, \b SYSCTL_LDO_2_65V,
//! \b SYSCTL_LDO_2_70V, or \b SYSCTL_LDO_2_75V.
//!
//! This function sets the output voltage of the LDO.  The default voltage is
//! 2.5 V; it can be adjusted +/- 10%.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlLDOSet(unsigned long ulVoltage)
{
    //
    // Check the arguments.
    //
    ASSERT((ulVoltage == SYSCTL_LDO_2_25V) ||
           (ulVoltage == SYSCTL_LDO_2_30V) ||
           (ulVoltage == SYSCTL_LDO_2_35V) ||
           (ulVoltage == SYSCTL_LDO_2_40V) ||
           (ulVoltage == SYSCTL_LDO_2_45V) ||
           (ulVoltage == SYSCTL_LDO_2_50V) ||
           (ulVoltage == SYSCTL_LDO_2_55V) ||
           (ulVoltage == SYSCTL_LDO_2_60V) ||
           (ulVoltage == SYSCTL_LDO_2_65V) ||
           (ulVoltage == SYSCTL_LDO_2_70V) ||
           (ulVoltage == SYSCTL_LDO_2_75V));

    //
    // Set the LDO voltage to the requested value.
    //
    HWREG(SYSCTL_LDOPCTL) = ulVoltage;
}

//*****************************************************************************
//
//! Gets the output voltage of the LDO.
//!
//! This function determines the output voltage of the LDO, as specified by the
//! control register.
//!
//! \return Returns the current voltage of the LDO; will be one of
//! \b SYSCTL_LDO_2_25V, \b SYSCTL_LDO_2_30V, \b SYSCTL_LDO_2_35V,
//! \b SYSCTL_LDO_2_40V, \b SYSCTL_LDO_2_45V, \b SYSCTL_LDO_2_50V,
//! \b SYSCTL_LDO_2_55V, \b SYSCTL_LDO_2_60V, \b SYSCTL_LDO_2_65V,
//! \b SYSCTL_LDO_2_70V, or \b SYSCTL_LDO_2_75V.
//
//*****************************************************************************
unsigned long
SysCtlLDOGet(void)
{
    //
    // Return the LDO voltage setting.
    //
    return(HWREG(SYSCTL_LDOPCTL));
}

//*****************************************************************************
//
//! Configures the LDO failure control.
//!
//! \param ulConfig is the required LDO failure control setting; can be either
//! \b SYSCTL_LDOCFG_ARST or \b SYSCTL_LDOCFG_NORST.
//!
//! This function allows the LDO to be configured to cause a processor reset
//! when the output voltage becomes unregulated.
//!
//! The LDO failure control is only available on Sandstorm-class devices.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlLDOConfigSet(unsigned long ulConfig)
{
    //
    // Check the arguments.
    //
    ASSERT((ulConfig == SYSCTL_LDOCFG_ARST) ||
           (ulConfig == SYSCTL_LDOCFG_NORST));

    //
    // Set the reset control as requested.
    //
    HWREG(SYSCTL_LDOARST) = ulConfig;
}

//*****************************************************************************
//
//! Resets the device.
//!
//! This function will perform a software reset of the entire device.  The
//! processor and all peripherals will be reset and all device registers will
//! return to their default values (with the exception of the reset cause
//! register, which will maintain its current value but have the software reset
//! bit set as well).
//!
//! \return This function does not return.
//
//*****************************************************************************
void
SysCtlReset(void)
{
    //
    // Perform a software reset request.  This will cause the device to reset,
    // no further code will be executed.
    //
    HWREG(NVIC_APINT) = NVIC_APINT_VECTKEY | NVIC_APINT_SYSRESETREQ;

    //
    // The device should have reset, so this should never be reached.  Just in
    // case, loop forever.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
//! Puts the processor into sleep mode.
//!
//! This function places the processor into sleep mode; it will not return
//! until the processor returns to run mode.  The peripherals that are enabled
//! via SysCtlPeripheralSleepEnable() continue to operate and can wake up the
//! processor (if automatic clock gating is enabled with
//! SysCtlPeripheralClockGating(), otherwise all peripherals continue to
//! operate).
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlSleep(void)
{
    //
    // Wait for an interrupt.
    //
    CPUwfi();
}

//*****************************************************************************
//
//! Puts the processor into deep-sleep mode.
//!
//! This function places the processor into deep-sleep mode; it will not return
//! until the processor returns to run mode.  The peripherals that are enabled
//! via SysCtlPeripheralDeepSleepEnable() continue to operate and can wake up
//! the processor (if automatic clock gating is enabled with
//! SysCtlPeripheralClockGating(), otherwise all peripherals continue to
//! operate).
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlDeepSleep(void)
{
    //
    // Enable deep-sleep.
    //
    HWREG(NVIC_SYS_CTRL) |= NVIC_SYS_CTRL_SLEEPDEEP;

    //
    // Wait for an interrupt.
    //
    CPUwfi();

    //
    // Disable deep-sleep so that a future sleep will work correctly.
    //
    HWREG(NVIC_SYS_CTRL) &= ~(NVIC_SYS_CTRL_SLEEPDEEP);
}

//*****************************************************************************
//
//! Gets the reason for a reset.
//!
//! This function will return the reason(s) for a reset.  Since the reset
//! reasons are sticky until either cleared by software or an external reset,
//! multiple reset reasons may be returned if multiple resets have occurred.
//! The reset reason will be a logical OR of \b SYSCTL_CAUSE_LDO,
//! \b SYSCTL_CAUSE_SW, \b SYSCTL_CAUSE_WDOG, \b SYSCTL_CAUSE_BOR,
//! \b SYSCTL_CAUSE_POR, and/or \b SYSCTL_CAUSE_EXT.
//!
//! \return The reason(s) for a reset.
//
//*****************************************************************************
unsigned long
SysCtlResetCauseGet(void)
{
    //
    // Return the reset reasons.
    //
    return(HWREG(SYSCTL_RESC));
}

//*****************************************************************************
//
//! Clears reset reasons.
//!
//! \param ulCauses are the reset causes to be cleared; must be a logical OR of
//! \b SYSCTL_CAUSE_LDO, \b SYSCTL_CAUSE_SW, \b SYSCTL_CAUSE_WDOG,
//! \b SYSCTL_CAUSE_BOR, \b SYSCTL_CAUSE_POR, and/or \b SYSCTL_CAUSE_EXT.
//!
//! This function clears the specified sticky reset reasons.  Once cleared,
//! another reset for the same reason can be detected, and a reset for a
//! different reason can be distinguished (instead of having two reset causes
//! set).  If the reset reason is used by an application, all reset causes
//! should be cleared after they are retrieved with SysCtlResetCauseGet().
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlResetCauseClear(unsigned long ulCauses)
{
    //
    // Clear the given reset reasons.
    //
    HWREG(SYSCTL_RESC) &= ~(ulCauses);
}

//*****************************************************************************
//
//! Configures the brown-out control.
//!
//! \param ulConfig is the desired configuration of the brown-out control.
//! Must be the logical OR of \b SYSCTL_BOR_RESET and/or
//! \b SYSCTL_BOR_RESAMPLE.
//! \param ulDelay is the number of internal oscillator cycles to wait before
//! resampling an asserted brown-out signal.  This value only has meaning when
//! \b SYSCTL_BOR_RESAMPLE is set and must be less than 8192.
//!
//! This function configures how the brown-out control operates.  It can detect
//! a brown-out by looking at only the brown-out output, or it can wait for it
//! to be active for two consecutive samples separated by a configurable time.
//! When it detects a brown-out condition, it can either reset the device or
//! generate a processor interrupt.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlBrownOutConfigSet(unsigned long ulConfig, unsigned long ulDelay)
{
    //
    // Check the arguments.
    //
    ASSERT(!(ulConfig & ~(SYSCTL_BOR_RESET | SYSCTL_BOR_RESAMPLE)));
    ASSERT(ulDelay < 8192);

    //
    // Configure the brown-out reset control.
    //
    HWREG(SYSCTL_PBORCTL) = (ulDelay << SYSCTL_PBORCTL_BOR_SH) | ulConfig;
}

//*****************************************************************************
//
//! Sets the clocking of the device.
//!
//! \param ulConfig is the required configuration of the device clocking.
//!
//! This function configures the clocking of the device.  The input crystal
//! frequency, oscillator to be used, use of the PLL, and the system clock
//! divider are all configured with this function.
//!
//! The \b ulConfig parameter is the logical OR of several different values,
//! many of which are grouped into sets where only one can be chosen.
//!
//! The system clock divider is chosen with one of the following values:
//! \b SYSCTL_SYSDIV_1, \b SYSCTL_SYSDIV_2, \b SYSCTL_SYSDIV_3,
//! \b SYSCTL_SYSDIV_4, \b SYSCTL_SYSDIV_5, \b SYSCTL_SYSDIV_6,
//! \b SYSCTL_SYSDIV_7, \b SYSCTL_SYSDIV_8, \b SYSCTL_SYSDIV_9,
//! \b SYSCTL_SYSDIV_10, \b SYSCTL_SYSDIV_11, \b SYSCTL_SYSDIV_12,
//! \b SYSCTL_SYSDIV_13, \b SYSCTL_SYSDIV_14, \b SYSCTL_SYSDIV_15, or
//! \b SYSCTL_SYSDIV_16.
//!
//! The use of the PLL is chosen with either \b SYSCTL_USE_PLL or
//! \b SYSCTL_USE_OSC.
//!
//! The external crystal frequency is chosen with one of the following values:
//! \b SYSCTL_XTAL_1MHZ, \b SYSCTL_XTAL_1_84MHZ, \b SYSCTL_XTAL_2MHZ,
//! \b SYSCTL_XTAL_2_45MHZ, \b SYSCTL_XTAL_3_57MHZ, \b SYSCTL_XTAL_3_68MHZ,
//! \b SYSCTL_XTAL_4MHZ, \b SYSCTL_XTAL_4_09MHZ, \b SYSCTL_XTAL_4_91MHZ,
//! \b SYSCTL_XTAL_5MHZ, \b SYSCTL_XTAL_5_12MHZ, \b SYSCTL_XTAL_6MHZ,
//! \b SYSCTL_XTAL_6_14MHZ, \b SYSCTL_XTAL_7_37MHZ, \b SYSCTL_XTAL_8MHZ, or
//! \b SYSCTL_XTAL_8_19MHZ.  Values below \b SYSCTL_XTAL_3_57MHZ are not valid
//! when the PLL is in operation.
//!
//! The oscillator source is chosen with one of the following values:
//! \b SYSCTL_OSC_MAIN, \b SYSCTL_OSC_INT, or \b SYSCTL_OSC_INT4.
//!
//! The internal and main oscillators are disabled with the
//! \b SYSCTL_INT_OSC_DIS and \b SYSCTL_MAIN_OSC_DIS flags, respectively.
//! The external oscillator must be enabled in order to use an external clock
//! source.  Note that attempts to disable the oscillator used to clock the
//! device will be prevented by the hardware.
//!
//! To clock the system from an external source (such as an external crystal
//! oscillator), use \b SYSCTL_USE_OSC \b | \b SYSCTL_OSC_MAIN.  To clock the
//! system from the main oscillator, use \b SYSCTL_USE_OSC \b |
//! \b SYSCTL_OSC_MAIN.  To clock the system from the PLL, use
//! \b SYSCTL_USE_PLL \b | \b SYSCTL_OSC_MAIN, and select the appropriate
//! crystal with one of the \b SYSCTL_XTAL_xxx values.
//!
//! \note If selecting the PLL as the system clock source (i.e. via
//! \b SYSCTL_USE_PLL), this function will poll the PLL lock interrupt to
//! determine when the PLL has locked.  If an interrupt handler for the
//! system control interrupt is in place, and it responds to and clears the
//! PLL lock interrupt, this function will delay until its timeout has occurred
//! instead of completing as soon as PLL lock is achieved.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlClockSet(unsigned long ulConfig)
{
    volatile unsigned long ulDelay;
    unsigned long ulRCC;

    //
    // Get the current value of the RCC register.
    //
    ulRCC = HWREG(SYSCTL_RCC);

    //
    // Bypass the PLL and system clock dividers for now.
    //
    ulRCC |= SYSCTL_RCC_BYPASS;
    ulRCC &= ~(SYSCTL_RCC_USE_SYSDIV);

    //
    // Write the new RCC value.
    //
    HWREG(SYSCTL_RCC) = ulRCC;

    //
    // See if either oscillator needs to be enabled.
    //
    if(((ulRCC & SYSCTL_RCC_IOSCDIS) && !(ulConfig & SYSCTL_RCC_IOSCDIS)) ||
       ((ulRCC & SYSCTL_RCC_MOSCDIS) && !(ulConfig & SYSCTL_RCC_MOSCDIS)))
    {
        //
        // Make sure that the required oscillators are enabled.  For now, the
        // previously enabled oscillators must be enabled along with the newly
        // requested oscillators.
        //
        ulRCC &= (~(SYSCTL_RCC_IOSCDIS | SYSCTL_RCC_MOSCDIS) |
                  (ulConfig & (SYSCTL_RCC_IOSCDIS | SYSCTL_RCC_MOSCDIS)));

        //
        // Write the new RCC value.
        //
        HWREG(SYSCTL_RCC) = ulRCC;

        //
        // Wait for a bit in case an oscillator was just started, giving it
        // time to stabilize.
        //
        for(ulDelay = 131072; ulDelay > 0; ulDelay--)
        {
        }
    }

    //
    // Set the new crystal value, oscillator source, and PLL configuration.
    //
    ulRCC &= ~(SYSCTL_RCC_XTAL_MASK | SYSCTL_RCC_OSCSRC_MASK |
               SYSCTL_RCC_PWRDN | SYSCTL_RCC_OE);
    ulRCC |= ulConfig & (SYSCTL_RCC_XTAL_MASK | SYSCTL_RCC_OSCSRC_MASK |
                         SYSCTL_RCC_PWRDN | SYSCTL_RCC_OE);

    //
    // Clear the PLL lock interrupt.
    //
    HWREG(SYSCTL_MISC) = SYSCTL_INT_PLL_LOCK;

    //
    // Write the new RCC value.
    //
    HWREG(SYSCTL_RCC) = ulRCC;

    //
    // Wait for a bit so that new crystal value and oscillator source can take
    // effect.
    //
    for(ulDelay = 16; ulDelay > 0; ulDelay--)
    {
    }

    //
    // Disable the appropriate oscillators.
    //
    ulRCC &= ~(SYSCTL_RCC_IOSCDIS | SYSCTL_RCC_MOSCDIS);
    ulRCC |= ulConfig & (SYSCTL_RCC_IOSCDIS | SYSCTL_RCC_MOSCDIS);

    //
    // Write the new RCC value.
    //
    HWREG(SYSCTL_RCC) = ulRCC;

    //
    // Set the requested system divider.  This will not get written
    // immediately.
    //
    ulRCC &= ~(SYSCTL_RCC_SYSDIV_MASK | SYSCTL_RCC_USE_SYSDIV);
    ulRCC |= ulConfig & (SYSCTL_RCC_SYSDIV_MASK | SYSCTL_RCC_USE_SYSDIV);

    //
    // See if the PLL output is being used to clock the system.
    //
    if(!(ulConfig & SYSCTL_RCC_BYPASS))
    {
        //
        // Wait until the PLL has locked.
        //
        for(ulDelay = 32768; ulDelay > 0; ulDelay--)
        {
            if(HWREG(SYSCTL_RIS) & SYSCTL_INT_PLL_LOCK)
            {
                break;
            }
        }

        //
        // Enable use of the PLL.
        //
        ulRCC &= ~(SYSCTL_RCC_BYPASS);
    }

    //
    // Write the final RCC value.
    //
    HWREG(SYSCTL_RCC) = ulRCC;

    //
    // Delay for a little bit so that the system divider takes effect.
    //
    for(ulDelay = 16; ulDelay > 0; ulDelay--)
    {
    }
}

//*****************************************************************************
//
//! Gets the processor clock rate.
//!
//! This function determines the clock rate of the processor clock.  This is
//! also the clock rate of all the peripheral modules (with the exception of
//! PWM, which has its own clock divider).
//!
//! \note This will not return accurate results if SysCtlClockSet() has not
//! been called to configure the clocking of the device, or if the device is
//! directly clocked from a crystal (or a clock source) that is not one of the
//! supported crystal frequencies.  In the later case, this function should be
//! modified to directly return the correct system clock rate.
//!
//! \return The processor clock rate.
//
//*****************************************************************************
unsigned long
SysCtlClockGet(void)
{
    unsigned long ulRCC, ulRCC2, ulPLL, ulClk;

    //
    // Read RCC and RCC2.  For Sandstorm-class devices (which do not have
    // RCC2), the RCC2 read will return 0, which indicates that RCC2 is
    // disabled (since the SYSCTL_RCC2_USERCC2 bit is clear).
    //
    ulRCC = HWREG(SYSCTL_RCC);
    ulRCC2 = HWREG(SYSCTL_RCC2);

    //
    // Get the base clock rate.
    //
    switch((ulRCC2 & SYSCTL_RCC2_USERCC2) ?
           (ulRCC2 & SYSCTL_RCC2_OSCSRC2_MSK) :
           (ulRCC & SYSCTL_RCC_OSCSRC_MASK))
    {
        //
        // The main oscillator is the clock source.  Determine its rate from
        // the crystal setting field.
        //
        case SYSCTL_RCC_OSCSRC_MAIN:
        {
            ulClk = g_pulXtals[(ulRCC & SYSCTL_RCC_XTAL_MASK) >>
                               SYSCTL_RCC_XTAL_SHIFT];
            break;
        }

        //
        // The internal oscillator is the source clock.
        //
        case SYSCTL_RCC_OSCSRC_INT:
        {
            //
            // See if this is a Sandstorm-class or Fury-class device.
            //
            if(DEVICE_IS_SANDSTORM)
            {
                //
                // The internal oscillator on a Sandstorm-class device is
                // 15 MHz +/- 50%.
                //
                ulClk = 15000000;
            }
            else
            {
                //
                // The internal oscillator on a Fury-class device is 12 MHz
                // +/- 30%.
                //
                ulClk = 12000000;
            }
            break;
        }

        //
        // The internal oscillator divided by four is the source clock.
        //
        case SYSCTL_RCC_OSCSRC_INT4:
        {
            //
            // See if this is a Sandstorm-class or Fury-class device.
            //
            if(DEVICE_IS_SANDSTORM)
            {
                //
                // The internal oscillator on a Sandstorm-class device is
                // 15 MHz +/- 50%.
                //
                ulClk = 15000000 / 4;
            }
            else
            {
                //
                // The internal oscillator on a Fury-class device is 12 MHz
                // +/- 30%.
                //
                ulClk = 12000000 / 4;
            }
            break;
        }

        //
        // The internal 30 KHz oscillator is the source clock.
        //
        case SYSCTL_RCC2_OSCSRC2_30:
        {
            //
            // The internal 30 KHz oscillator has an accuracy of +/- 30%.
            //
            ulClk = 30000;
            break;
        }

        //
        // The 32 KHz clock from the hibernate module is the source clock.
        //
        case SYSCTL_RCC2_OSCSRC2_32:
        {
            ulClk = 32768;
            break;
        }

        //
        // An unknown setting, so return a zero clock (i.e. an unknown clock
        // rate).
        //
        default:
        {
            return(0);
        }
    }

    //
    // See if the PLL is being used.
    //
    if(((ulRCC2 & SYSCTL_RCC2_USERCC2) && !(ulRCC2 & SYSCTL_RCC2_BYPASS2)) ||
       (!(ulRCC2 & SYSCTL_RCC2_USERCC2) && !(ulRCC & SYSCTL_RCC_BYPASS)))
    {
        //
        // Get the PLL configuration.
        //
        ulPLL = HWREG(SYSCTL_PLLCFG);

        //
        // See if this is a Sandstorm-class or Fury-class device.
        //
        if(DEVICE_IS_SANDSTORM)
        {
            //
            // Compute the PLL output frequency based on its input frequency.
            // The formula for a Sandstorm-class devices is
            // "(xtal * (f + 2)) / (r + 2)".
            //
            ulClk = ((ulClk * (((ulPLL & SYSCTL_PLLCFG_F_MASK) >>
                                SYSCTL_PLLCFG_F_SHIFT) + 2)) /
                     (((ulPLL & SYSCTL_PLLCFG_R_MASK) >>
                       SYSCTL_PLLCFG_R_SHIFT) + 2));
        }
        else
        {
            //
            // Compute the PLL output frequency based on its input frequency.
            // The formula for a Fury-class device is
            // "(xtal * f) / ((r + 1) * 2)".
            //
            ulClk = ((ulClk * ((ulPLL & SYSCTL_PLLCFG_F_MASK) >>
                               SYSCTL_PLLCFG_F_SHIFT)) /
                     ((((ulPLL & SYSCTL_PLLCFG_R_MASK) >>
                        SYSCTL_PLLCFG_R_SHIFT) + 1) * 2));
        }

        //
        // See if the optional output divide by 2 is being used.
        //
        if(ulPLL & SYSCTL_PLLCFG_OD_2)
        {
            ulClk /= 2;
        }

        //
        // See if the optional output divide by 4 is being used.
        //
        if(ulPLL & SYSCTL_PLLCFG_OD_4)
        {
            ulClk /= 4;
        }
    }

    //
    // See if the system divider is being used.
    //
    if(ulRCC & SYSCTL_RCC_USE_SYSDIV)
    {
        //
        // Adjust the clock rate by the system clock divider.
        //
        if(ulRCC2 & SYSCTL_RCC2_USERCC2)
        {
            ulClk /= ((ulRCC2 & SYSCTL_RCC2_SYSDIV2_MSK) >>
                      SYSCTL_RCC2_SYSDIV2_S) + 1;
        }
        else
        {
            ulClk /= ((ulRCC & SYSCTL_RCC_SYSDIV_MASK) >>
                      SYSCTL_RCC_SYSDIV_SHIFT) + 1;
        }
    }

    //
    // Return the computed clock rate.
    //
    return(ulClk);
}

//*****************************************************************************
//
//! Sets the PWM clock configuration.
//!
//! \param ulConfig is the configuration for the PWM clock; it must be one of
//! \b SYSCTL_PWMDIV_1, \b SYSCTL_PWMDIV_2, \b SYSCTL_PWMDIV_4,
//! \b SYSCTL_PWMDIV_8, \b SYSCTL_PWMDIV_16, \b SYSCTL_PWMDIV_32, or
//! \b SYSCTL_PWMDIV_64.
//!
//! This function sets the rate of the clock provided to the PWM module as a
//! ratio of the processor clock.  This clock is used by the PWM module to
//! generate PWM signals; its rate forms the basis for all PWM signals.
//!
//! \note The clocking of the PWM is dependent upon the system clock rate as
//! configured by SysCtlClockSet().
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPWMClockSet(unsigned long ulConfig)
{
    //
    // Check the arguments.
    //
    ASSERT((ulConfig == SYSCTL_PWMDIV_1) ||
           (ulConfig == SYSCTL_PWMDIV_2) ||
           (ulConfig == SYSCTL_PWMDIV_4) ||
           (ulConfig == SYSCTL_PWMDIV_8) ||
           (ulConfig == SYSCTL_PWMDIV_16) ||
           (ulConfig == SYSCTL_PWMDIV_32) ||
           (ulConfig == SYSCTL_PWMDIV_64));

    //
    // Check that there is a PWM block on this part.
    //
    ASSERT(HWREG(SYSCTL_DC1) & SYSCTL_DC1_PWM);

    //
    // Set the PWM clock configuration into the run-mode clock configuration
    // register.
    //
    HWREG(SYSCTL_RCC) = ((HWREG(SYSCTL_RCC) &
                          ~(SYSCTL_RCC_USE_PWMDIV | SYSCTL_RCC_PWMDIV_MASK)) |
                         ulConfig);
}

//*****************************************************************************
//
//! Gets the current PWM clock configuration.
//!
//! This function returns the current PWM clock configuration.
//!
//! \return The current PWM clock configuration; will be one of
//! \b SYSCTL_PWMDIV_1, \b SYSCTL_PWMDIV_2, \b SYSCTL_PWMDIV_4,
//! \b SYSCTL_PWMDIV_8, \b SYSCTL_PWMDIV_16, \b SYSCTL_PWMDIV_32, or
//! \b SYSCTL_PWMDIV_64.
//
//*****************************************************************************
unsigned long
SysCtlPWMClockGet(void)
{
    //
    // Check that there is a PWM block on this part.
    //
    ASSERT(HWREG(SYSCTL_DC1) & SYSCTL_DC1_PWM);

    //
    // Return the current PWM clock configuration. Make sure that we return
    // SYSCTL_PWMDIV_1 in all cases where the divider is disabled.
    //
    if(!(HWREG(SYSCTL_RCC) &  SYSCTL_RCC_USE_PWMDIV))
    {
        //
        // The divider is not active so reflect this in the value we return.
        //
        return(SYSCTL_PWMDIV_1);
    }
    else
    {
        //
        // The divider is active so directly return the masked register value.
        //
        return(HWREG(SYSCTL_RCC) &
               (SYSCTL_RCC_USE_PWMDIV | SYSCTL_RCC_PWMDIV_MASK));
    }
}

//*****************************************************************************
//
//! Sets the sample rate of the ADC.
//!
//! \param ulSpeed is the desired sample rate of the ADC; must be one of
//! \b SYSCTL_ADCSPEED_1MSPS, \b SYSCTL_ADCSPEED_500KSPS,
//! \b SYSCTL_ADCSPEED_250KSPS, or \b SYSCTL_ADCSPEED_125KSPS.
//!
//! This function sets the rate at which the ADC samples are captured by the
//! ADC block.  The sampling speed may be limited by the hardware, so the
//! sample rate may end up being slower than requested.  SysCtlADCSpeedGet()
//! will return the actual speed in use.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlADCSpeedSet(unsigned long ulSpeed)
{
    //
    // Check the arguments.
    //
    ASSERT((ulSpeed == SYSCTL_ADCSPEED_1MSPS) ||
           (ulSpeed == SYSCTL_ADCSPEED_500KSPS) ||
           (ulSpeed == SYSCTL_ADCSPEED_250KSPS) ||
           (ulSpeed == SYSCTL_ADCSPEED_125KSPS));

    //
    // Check that there is an ADC block on this part.
    //
    ASSERT(HWREG(SYSCTL_DC1) & SYSCTL_DC1_ADC);

    //
    // Set the ADC speed in run, sleep, and deep-sleep mode.
    //
    HWREG(SYSCTL_RCGC0) = ((HWREG(SYSCTL_RCGC0) & ~(SYSCTL_SET0_ADCSPD_MASK)) |
                           ulSpeed);
    HWREG(SYSCTL_SCGC0) = ((HWREG(SYSCTL_SCGC0) & ~(SYSCTL_SET0_ADCSPD_MASK)) |
                           ulSpeed);
    HWREG(SYSCTL_DCGC0) = ((HWREG(SYSCTL_DCGC0) & ~(SYSCTL_SET0_ADCSPD_MASK)) |
                           ulSpeed);
}

//*****************************************************************************
//
//! Gets the sample rate of the ADC.
//!
//! This function gets the current sample rate of the ADC.
//!
//! \return Returns the current ADC sample rate; will be one of
//! \b SYSCTL_ADCSPEED_1MSPS, \b SYSCTL_ADCSPEED_500KSPS,
//! \b SYSCTL_ADCSPEED_250KSPS, or \b SYSCTL_ADCSPEED_125KSPS.
//
//*****************************************************************************
unsigned long
SysCtlADCSpeedGet(void)
{
    //
    // Check that there is an ADC block on this part.
    //
    ASSERT(HWREG(SYSCTL_DC1) & SYSCTL_DC1_ADC);

    //
    // Return the current ADC speed.
    //
    return(HWREG(SYSCTL_RCGC0) & SYSCTL_SET0_ADCSPD_MASK);
}

//*****************************************************************************
//
//! Configures the internal oscillator verification timer.
//!
//! \param bEnable is a boolean that is \b true if the internal oscillator
//! verification timer should be enabled.
//!
//! This function allows the internal oscillator verification timer to be
//! enabled or disabled.  When enabled, an interrupt will be generated if the
//! internal oscillator ceases to operate.
//!
//! The internal osscillator verification timer is only available on
//! Sandstorm-class devices.
//!
//! \note Both oscillators (main and internal) must be enabled for this
//! verification timer to operate as the main oscillator will verify the
//! internal oscillator.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlIOSCVerificationSet(tBoolean bEnable)
{
    //
    // Enable or disable the internal oscillator verification timer as
    // requested.
    //
    if(bEnable)
    {
        HWREG(SYSCTL_RCC) |= SYSCTL_RCC_IOSCVER;
    }
    else
    {
        HWREG(SYSCTL_RCC) &= ~(SYSCTL_RCC_IOSCVER);
    }
}

//*****************************************************************************
//
//! Configures the main oscillator verification timer.
//!
//! \param bEnable is a boolean that is \b true if the main oscillator
//! verification timer should be enabled.
//!
//! This function allows the main oscillator verification timer to be enabled
//! or disabled.  When enabled, an interrupt will be generated if the main
//! oscillator ceases to operate.
//!
//! The main osscillator verification timer is only available on
//! Sandstorm-class devices.
//!
//! \note Both oscillators (main and internal) must be enabled for this
//! verification timer to operate as the internal oscillator will verify the
//! main oscillator.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlMOSCVerificationSet(tBoolean bEnable)
{
    //
    // Enable or disable the main oscillator verification timer as requested.
    //
    if(bEnable)
    {
        HWREG(SYSCTL_RCC) |= SYSCTL_RCC_MOSCVER;
    }
    else
    {
        HWREG(SYSCTL_RCC) &= ~(SYSCTL_RCC_MOSCVER);
    }
}

//*****************************************************************************
//
//! Configures the PLL verification timer.
//!
//! \param bEnable is a boolean that is \b true if the PLL verification timer
//! should be enabled.
//!
//! This function allows the PLL verification timer to be enabled or disabled.
//! When enabled, an interrupt will be generated if the PLL ceases to operate.
//!
//! The PLL verification timer is only available on Sandstorm-class devices.
//!
//! \note The main oscillator must be enabled for this verification timer to
//! operate as it is used to check the PLL.  Also, the verification timer
//! should be disabled while the PLL is being reconfigured via
//! SysCtlClockSet().
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPLLVerificationSet(tBoolean bEnable)
{
    //
    // Enable or disable the PLL verification timer as requested.
    //
    if(bEnable)
    {
        HWREG(SYSCTL_RCC) |= SYSCTL_RCC_PLLVER;
    }
    else
    {
        HWREG(SYSCTL_RCC) &= ~(SYSCTL_RCC_PLLVER);
    }
}

//*****************************************************************************
//
//! Clears the clock verification status.
//!
//! This function clears the status of the clock verification timers, allowing
//! them to assert another failure if detected.
//!
//! The clock verification timers are only available on Sandstorm-class
//! devices.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlClkVerificationClear(void)
{
    //
    // Clear the clock verification.
    //
    HWREG(SYSCTL_CLKVCLR) = SYSCTL_CLKVCLR_CLR;

    //
    // The bit does not self-reset, so clear it.
    //
    HWREG(SYSCTL_CLKVCLR) = 0;
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
