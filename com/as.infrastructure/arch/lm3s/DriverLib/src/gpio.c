//*****************************************************************************
//
// gpio.c - API for GPIO ports
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
//! \addtogroup gpio_api
//! @{
//
//*****************************************************************************

#include "../hw_gpio.h"
#include "../hw_ints.h"
#include "../hw_memmap.h"
#include "../hw_types.h"
#include "debug.h"
#include "gpio.h"

#include "lm3sinterrupt.h"

//*****************************************************************************
//
//! \internal
//! Gets the GPIO interrupt number.
//!
//! \param ulPort is the base address of the GPIO port.
//!
//! Given a GPIO base address, returns the corresponding interrupt number.
//!
//! \return Returns a GPIO interrupt number, or -1 if \e ulPort is invalid.
//
//*****************************************************************************
static long
GPIOGetIntNumber(unsigned long ulPort)
{
    unsigned int ulInt;

    //
    // Determine the GPIO interrupt number for the given module.
    //
    switch(ulPort)
    {
        case GPIO_PORTA_BASE:
        {
            ulInt = INT_GPIOA;
            break;
        }

        case GPIO_PORTB_BASE:
        {
            ulInt = INT_GPIOB;
            break;
        }

        case GPIO_PORTC_BASE:
        {
            ulInt = INT_GPIOC;
            break;
        }

        case GPIO_PORTD_BASE:
        {
            ulInt = INT_GPIOD;
            break;
        }

        case GPIO_PORTE_BASE:
        {
            ulInt = INT_GPIOE;
            break;
        }

        case GPIO_PORTF_BASE:
        {
            ulInt = INT_GPIOF;
            break;
        }

        case GPIO_PORTG_BASE:
        {
            ulInt = INT_GPIOG;
            break;
        }

        case GPIO_PORTH_BASE:
        {
            ulInt = INT_GPIOH;
            break;
        }

        default:
        {
            return(-1);
        }
    }

    //
    // Return GPIO interrupt number.
    //
    return(ulInt);
}

//*****************************************************************************
//
//! Sets the direction and mode of the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port
//! \param ucPins is the bit-packed representation of the pin(s).
//! \param ulPinIO is the pin direction and/or mode.
//!
//! This function will set the specified pin(s) on the selected GPIO port
//! as either an input or output under software control, or it will set the
//! pin to be under hardware control.
//!
//! The parameter \e ulPinIO is an enumerated data type that can be one of
//! the following values:
//!
//! - \b GPIO_DIR_MODE_IN
//! - \b GPIO_DIR_MODE_OUT
//! - \b GPIO_DIR_MODE_HW
//!
//! where \b GPIO_DIR_MODE_IN specifies that the pin will be programmed as
//! a software controlled input, \b GPIO_DIR_MODE_OUT specifies that the pin
//! will be programmed as a software controlled output, and
//! \b GPIO_DIR_MODE_HW specifies that the pin will be placed under
//! hardware control.
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, etc.
//!
//! \return None.
//
//*****************************************************************************
void
GPIODirModeSet(unsigned long ulPort, unsigned char ucPins,
               unsigned long ulPinIO)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPort == GPIO_PORTA_BASE) || (ulPort == GPIO_PORTB_BASE) ||
           (ulPort == GPIO_PORTC_BASE) || (ulPort == GPIO_PORTD_BASE) ||
           (ulPort == GPIO_PORTE_BASE) || (ulPort == GPIO_PORTF_BASE) ||
           (ulPort == GPIO_PORTG_BASE) || (ulPort == GPIO_PORTH_BASE));
    ASSERT((ulPinIO == GPIO_DIR_MODE_IN) || (ulPinIO == GPIO_DIR_MODE_OUT) ||
           (ulPinIO == GPIO_DIR_MODE_HW));

    //
    // Set the pin direction and mode.
    //
    HWREG(ulPort + GPIO_O_DIR) = ((ulPinIO & 1) ?
                                  (HWREG(ulPort + GPIO_O_DIR) | ucPins) :
                                  (HWREG(ulPort + GPIO_O_DIR) & ~(ucPins)));
    HWREG(ulPort + GPIO_O_AFSEL) = ((ulPinIO & 2) ?
                                    (HWREG(ulPort + GPIO_O_AFSEL) | ucPins) :
                                    (HWREG(ulPort + GPIO_O_AFSEL) &
                                     ~(ucPins)));
}

//*****************************************************************************
//
//! Gets the direction and mode of a pin.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPin is the pin number.
//!
//! This function gets the direction and control mode for a specified pin on
//! the selected GPIO port. The pin can be configured as either an input or
//! output under software control, or it can be under hardware control. The
//! type of control and direction are returned as an enumerated data type.
//!
//! \return Returns one of the enumerated data types described for
//! GPIODirModeSet().
//
//*****************************************************************************
unsigned long
GPIODirModeGet(unsigned long ulPort, unsigned char ucPin)
{
    unsigned long ulDir, ulAFSEL;

    //
    // Check the arguments.
    //
    ASSERT((ulPort == GPIO_PORTA_BASE) || (ulPort == GPIO_PORTB_BASE) ||
           (ulPort == GPIO_PORTC_BASE) || (ulPort == GPIO_PORTD_BASE) ||
           (ulPort == GPIO_PORTE_BASE) || (ulPort == GPIO_PORTF_BASE) ||
           (ulPort == GPIO_PORTG_BASE) || (ulPort == GPIO_PORTH_BASE));
    ASSERT(ucPin < 8);

    //
    // Convert from a pin number to a bit position.
    //
    ucPin = 1 << ucPin;

    //
    // Return the pin direction and mode.
    //
    ulDir = HWREG(ulPort + GPIO_O_DIR);
    ulAFSEL = HWREG(ulPort + GPIO_O_AFSEL);
    return(((ulDir & ucPin) ? 1 : 0) | ((ulAFSEL & ucPin) ? 2 : 0));
}

//*****************************************************************************
//
//! Sets the interrupt type for the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//! \param ulIntType specifies the type of interrupt trigger mechanism.
//!
//! This function sets up the various interrupt trigger mechanisms for the
//! specified pin(s) on the selected GPIO port.
//!
//! The parameter \e ulIntType is an enumerated data type that can be one of
//! the following values:
//!
//! - \b GPIO_FALLING_EDGE
//! - \b GPIO_RISING_EDGE
//! - \b GPIO_BOTH_EDGES
//! - \b GPIO_LOW_LEVEL
//! - \b GPIO_HIGH_LEVEL
//!
//! where the different values describe the interrupt detection mechanism
//! (edge or level) and the particular triggering event (falling, rising,
//! or both edges for edge detect, low or high for level detect).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, etc.
//!
//! \note In order to avoid any spurious interrupts, the user must
//! ensure that the GPIO inputs remain stable for the duration of
//! this function.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOIntTypeSet(unsigned long ulPort, unsigned char ucPins,
               unsigned long ulIntType)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPort == GPIO_PORTA_BASE) || (ulPort == GPIO_PORTB_BASE) ||
           (ulPort == GPIO_PORTC_BASE) || (ulPort == GPIO_PORTD_BASE) ||
           (ulPort == GPIO_PORTE_BASE) || (ulPort == GPIO_PORTF_BASE) ||
           (ulPort == GPIO_PORTG_BASE) || (ulPort == GPIO_PORTH_BASE));
    ASSERT((ulIntType == GPIO_FALLING_EDGE) ||
           (ulIntType == GPIO_RISING_EDGE) ||
           (ulIntType == GPIO_BOTH_EDGES) ||
           (ulIntType == GPIO_LOW_LEVEL) ||
           (ulIntType == GPIO_HIGH_LEVEL));

    //
    // Set the pin interrupt type.
    //
    HWREG(ulPort + GPIO_O_IBE) = ((ulIntType & 1) ?
                                  (HWREG(ulPort + GPIO_O_IBE) | ucPins) :
                                  (HWREG(ulPort + GPIO_O_IBE) & ~(ucPins)));
    HWREG(ulPort + GPIO_O_IS) = ((ulIntType & 2) ?
                                 (HWREG(ulPort + GPIO_O_IS) | ucPins) :
                                 (HWREG(ulPort + GPIO_O_IS) & ~(ucPins)));
    HWREG(ulPort + GPIO_O_IEV) = ((ulIntType & 4) ?
                                  (HWREG(ulPort + GPIO_O_IEV) | ucPins) :
                                  (HWREG(ulPort + GPIO_O_IEV) & ~(ucPins)));
}

//*****************************************************************************
//
//! Gets the interrupt type for a pin.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPin is the pin number.
//!
//! This function gets the interrupt type for a specified pin on the selected
//! GPIO port. The pin can be configured as a falling edge, rising edge, or
//! both edge detected interrupt, or it can be configured as a low level or
//! high level detected interrupt. The type of interrupt detection mechanism
//! is returned as an enumerated data type.
//!
//! \return Returns one of the enumerated data types described for
//! GPIOIntTypeSet().
//
//*****************************************************************************
unsigned long
GPIOIntTypeGet(unsigned long ulPort, unsigned char ucPin)
{
    unsigned long ulIBE, ulIS, ulIEV;

    //
    // Check the arguments.
    //
    ASSERT((ulPort == GPIO_PORTA_BASE) || (ulPort == GPIO_PORTB_BASE) ||
           (ulPort == GPIO_PORTC_BASE) || (ulPort == GPIO_PORTD_BASE) ||
           (ulPort == GPIO_PORTE_BASE) || (ulPort == GPIO_PORTF_BASE) ||
           (ulPort == GPIO_PORTG_BASE) || (ulPort == GPIO_PORTH_BASE));
    ASSERT(ucPin < 8);

    //
    // Convert from a pin number to a bit position.
    //
    ucPin = 1 << ucPin;

    //
    // Return the pin interrupt type.
    //
    ulIBE = HWREG(ulPort + GPIO_O_IBE);
    ulIS = HWREG(ulPort + GPIO_O_IS);
    ulIEV = HWREG(ulPort + GPIO_O_IEV);
    return(((ulIBE & ucPin) ? 1 : 0) | ((ulIS & ucPin) ? 2 : 0) |
           ((ulIEV & ucPin) ? 4 : 0));
}

//*****************************************************************************
//
//! Sets the pad configuration for the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//! \param ulStrength specifies the output drive strength.
//! \param ulPinType specifies the pin type.
//!
//! This function sets the drive strength and type for the specified pin(s)
//! on the selected GPIO port.  For pin(s) configured as input ports, the
//! pad is configured as requested, but the only real effect on the input
//! is the configuration of the pull-up or pull-down termination.
//!
//! The parameter \e ulStrength can be one of the following values:
//!
//! - \b GPIO_STRENGTH_2MA
//! - \b GPIO_STRENGTH_4MA
//! - \b GPIO_STRENGTH_8MA
//! - \b GPIO_STRENGTH_8MA_SC
//!
//! where \b GPIO_STRENGTH_xMA specifies either 2, 4, or 8 mA output drive
//! strength, and \b GPIO_OUT_STRENGTH_8MA_SC specifies 8 mA output drive with
//! slew control.
//!
//! The parameter \e ulPinType can be one of the following values:
//!
//! - \b GPIO_PIN_TYPE_STD
//! - \b GPIO_PIN_TYPE_STD_WPU
//! - \b GPIO_PIN_TYPE_STD_WPD
//! - \b GPIO_PIN_TYPE_OD
//! - \b GPIO_PIN_TYPE_OD_WPU
//! - \b GPIO_PIN_TYPE_OD_WPD
//! - \b GPIO_PIN_TYPE_ANALOG
//!
//! where \b GPIO_PIN_TYPE_STD* specifies a push-pull pin, \b GPIO_PIN_TYPE_OD*
//! specifies an open-drain pin, \b *_WPU specifies a weak pull-up, \b *_WPD
//! specifies a weak pull-down, and \b GPIO_PIN_TYPE_ANALOG specifies an
//! analog input (for the comparators).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, etc.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPadConfigSet(unsigned long ulPort, unsigned char ucPins,
                 unsigned long ulStrength, unsigned long ulPinType)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPort == GPIO_PORTA_BASE) || (ulPort == GPIO_PORTB_BASE) ||
           (ulPort == GPIO_PORTC_BASE) || (ulPort == GPIO_PORTD_BASE) ||
           (ulPort == GPIO_PORTE_BASE) || (ulPort == GPIO_PORTF_BASE) ||
           (ulPort == GPIO_PORTG_BASE) || (ulPort == GPIO_PORTH_BASE));
    ASSERT((ulStrength == GPIO_STRENGTH_2MA) ||
           (ulStrength == GPIO_STRENGTH_4MA) ||
           (ulStrength == GPIO_STRENGTH_8MA) ||
           (ulStrength == GPIO_STRENGTH_8MA_SC));
    ASSERT((ulPinType == GPIO_PIN_TYPE_STD) ||
           (ulPinType == GPIO_PIN_TYPE_STD_WPU) ||
           (ulPinType == GPIO_PIN_TYPE_STD_WPD) ||
           (ulPinType == GPIO_PIN_TYPE_OD) ||
           (ulPinType == GPIO_PIN_TYPE_OD_WPU) ||
           (ulPinType == GPIO_PIN_TYPE_OD_WPD) ||
           (ulPinType == GPIO_PIN_TYPE_ANALOG))

    //
    // Set the output drive strength.
    //
    HWREG(ulPort + GPIO_O_DR2R) = ((ulStrength & 1) ?
                                   (HWREG(ulPort + GPIO_O_DR2R) | ucPins) :
                                   (HWREG(ulPort + GPIO_O_DR2R) & ~(ucPins)));
    HWREG(ulPort + GPIO_O_DR4R) = ((ulStrength & 2) ?
                                   (HWREG(ulPort + GPIO_O_DR4R) | ucPins) :
                                   (HWREG(ulPort + GPIO_O_DR4R) & ~(ucPins)));
    HWREG(ulPort + GPIO_O_DR8R) = ((ulStrength & 4) ?
                                   (HWREG(ulPort + GPIO_O_DR8R) | ucPins) :
                                   (HWREG(ulPort + GPIO_O_DR8R) & ~(ucPins)));
    HWREG(ulPort + GPIO_O_SLR) = ((ulStrength & 8) ?
                                  (HWREG(ulPort + GPIO_O_SLR) | ucPins) :
                                  (HWREG(ulPort + GPIO_O_SLR) & ~(ucPins)));

    //
    // Set the pin type.
    //
    HWREG(ulPort + GPIO_O_ODR) = ((ulPinType & 1) ?
                                  (HWREG(ulPort + GPIO_O_ODR) | ucPins) :
                                  (HWREG(ulPort + GPIO_O_ODR) & ~(ucPins)));
    HWREG(ulPort + GPIO_O_PUR) = ((ulPinType & 2) ?
                                  (HWREG(ulPort + GPIO_O_PUR) | ucPins) :
                                  (HWREG(ulPort + GPIO_O_PUR) & ~(ucPins)));
    HWREG(ulPort + GPIO_O_PDR) = ((ulPinType & 4) ?
                                  (HWREG(ulPort + GPIO_O_PDR) | ucPins) :
                                  (HWREG(ulPort + GPIO_O_PDR) & ~(ucPins)));
    HWREG(ulPort + GPIO_O_DEN) = ((ulPinType & 8) ?
                                  (HWREG(ulPort + GPIO_O_DEN) | ucPins) :
                                  (HWREG(ulPort + GPIO_O_DEN) & ~(ucPins)));
}

//*****************************************************************************
//
//! Gets the pad configuration for a pin.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPin is the pin number.
//! \param pulStrength is a pointer to storage for the output drive strength.
//! \param pulPinType is a pointer to storage for the output drive type.
//!
//! This function gets the pad configuration for a specified pin on the
//! selected GPIO port. The values returned in \e eStrength and \e eOutType
//! correspond to the values used in GPIOPadConfigSet(). This function also
//! works for pin(s) configured as input pin(s); however, the only meaningful
//! data returned is whether the pin is terminated with a pull-up or
//! down resistor.
//!
//! \return None
//
//*****************************************************************************
void
GPIOPadConfigGet(unsigned long ulPort, unsigned char ucPin,
                 unsigned long *pulStrength, unsigned long *pulPinType)
{
    unsigned long ulTemp1, ulTemp2, ulTemp3, ulTemp4;

    //
    // Check the arguments.
    //
    ASSERT((ulPort == GPIO_PORTA_BASE) || (ulPort == GPIO_PORTB_BASE) ||
           (ulPort == GPIO_PORTC_BASE) || (ulPort == GPIO_PORTD_BASE) ||
           (ulPort == GPIO_PORTE_BASE) || (ulPort == GPIO_PORTF_BASE) ||
           (ulPort == GPIO_PORTG_BASE) || (ulPort == GPIO_PORTH_BASE));
    ASSERT(ucPin < 8);

    //
    // Convert from a pin number to a bit position.
    //
    ucPin = (1 << ucPin);

    //
    // Get the drive strength for this pin.
    //
    ulTemp1 = HWREG(ulPort + GPIO_O_DR2R);
    ulTemp2 = HWREG(ulPort + GPIO_O_DR4R);
    ulTemp3 = HWREG(ulPort + GPIO_O_DR8R);
    ulTemp4 = HWREG(ulPort + GPIO_O_SLR);
    *pulStrength = (((ulTemp1 & ucPin) ? 1 : 0) | ((ulTemp2 & ucPin) ? 2 : 0) |
                    ((ulTemp3 & ucPin) ? 4 : 0) | ((ulTemp4 & ucPin) ? 8 : 0));

    //
    // Get the pin type.
    //
    ulTemp1 = HWREG(ulPort + GPIO_O_ODR);
    ulTemp2 = HWREG(ulPort + GPIO_O_PUR);
    ulTemp3 = HWREG(ulPort + GPIO_O_PDR);
    ulTemp4 = HWREG(ulPort + GPIO_O_DEN);
    *pulPinType = (((ulTemp1 & ucPin) ? 1 : 0) | ((ulTemp2 & ucPin) ? 2 : 0) |
                   ((ulTemp3 & ucPin) ? 4 : 0) | ((ulTemp4 & ucPin) ? 8 : 0));
}

//*****************************************************************************
//
//! Enables interrupts for the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! Unmasks the interrupt for the specified pin(s).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, etc.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinIntEnable(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPort == GPIO_PORTA_BASE) || (ulPort == GPIO_PORTB_BASE) ||
           (ulPort == GPIO_PORTC_BASE) || (ulPort == GPIO_PORTD_BASE) ||
           (ulPort == GPIO_PORTE_BASE) || (ulPort == GPIO_PORTF_BASE) ||
           (ulPort == GPIO_PORTG_BASE) || (ulPort == GPIO_PORTH_BASE));

    //
    // Enable the interrupts.
    //
    HWREG(ulPort + GPIO_O_IM) |= ucPins;
}

//*****************************************************************************
//
//! Disables interrupts for the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! Masks the interrupt for the specified pin(s).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, etc.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinIntDisable(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPort == GPIO_PORTA_BASE) || (ulPort == GPIO_PORTB_BASE) ||
           (ulPort == GPIO_PORTC_BASE) || (ulPort == GPIO_PORTD_BASE) ||
           (ulPort == GPIO_PORTE_BASE) || (ulPort == GPIO_PORTF_BASE) ||
           (ulPort == GPIO_PORTG_BASE) || (ulPort == GPIO_PORTH_BASE));

    //
    // Disable the interrupts.
    //
    HWREG(ulPort + GPIO_O_IM) &= ~(ucPins);
}

//*****************************************************************************
//
//! Gets interrupt status for the specified GPIO port.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param bMasked specifies whether masked or raw interrupt status is
//! returned.
//!
//! If \e bMasked is set as \b true, then the masked interrupt status is
//! returned; otherwise, the raw interrupt status will be returned.
//!
//! \return Returns a bit-packed byte, where each bit that is set identifies
//! an active masked or raw interrupt, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, etc. Bits
//! 31:8 should be ignored.
//
//*****************************************************************************
long
GPIOPinIntStatus(unsigned long ulPort, tBoolean bMasked)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPort == GPIO_PORTA_BASE) || (ulPort == GPIO_PORTB_BASE) ||
           (ulPort == GPIO_PORTC_BASE) || (ulPort == GPIO_PORTD_BASE) ||
           (ulPort == GPIO_PORTE_BASE) || (ulPort == GPIO_PORTF_BASE) ||
           (ulPort == GPIO_PORTG_BASE) || (ulPort == GPIO_PORTH_BASE));

    //
    // Return the interrupt status.
    //
    if(bMasked)
    {
        return(HWREG(ulPort + GPIO_O_MIS));
    }
    else
    {
        return(HWREG(ulPort + GPIO_O_RIS));
    }
}

//*****************************************************************************
//
//! Clears the interrupt for the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! Clears the interrupt for the specified pin(s).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, etc.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinIntClear(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPort == GPIO_PORTA_BASE) || (ulPort == GPIO_PORTB_BASE) ||
           (ulPort == GPIO_PORTC_BASE) || (ulPort == GPIO_PORTD_BASE) ||
           (ulPort == GPIO_PORTE_BASE) || (ulPort == GPIO_PORTF_BASE) ||
           (ulPort == GPIO_PORTG_BASE) || (ulPort == GPIO_PORTH_BASE));

    //
    // Clear the interrupts.
    //
    HWREG(ulPort + GPIO_O_ICR) = ucPins;
}

//*****************************************************************************
//
//! Registers an interrupt handler for a GPIO port.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param pfIntHandler is a pointer to the GPIO port interrupt handling
//! function.
//!
//! This function will ensure that the interrupt handler specified by \e
//! pfIntHandler is called when an interrupt is detected from the selected
//! GPIO port. This function will also enable the corresponding GPIO
//! interrupt in the interrupt controller; individual pin interrupts and
//! interrupt sources must be enabled with GPIOPinIntEnable().
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPortIntRegister(unsigned long ulPort, void (*pfIntHandler)(void))
{
    //
    // Check the arguments.
    //
    ASSERT((ulPort == GPIO_PORTA_BASE) || (ulPort == GPIO_PORTB_BASE) ||
           (ulPort == GPIO_PORTC_BASE) || (ulPort == GPIO_PORTD_BASE) ||
           (ulPort == GPIO_PORTE_BASE) || (ulPort == GPIO_PORTF_BASE) ||
           (ulPort == GPIO_PORTG_BASE) || (ulPort == GPIO_PORTH_BASE));

    //
    // Get the interrupt number associated with the specified GPIO.
    //
    ulPort = GPIOGetIntNumber(ulPort);

    //
    // Register the interrupt handler.
    //
    IntRegister(ulPort, pfIntHandler);

    //
    // Enable the GPIO interrupt.
    //
    IntEnable(ulPort);
}

//*****************************************************************************
//
//! Removes an interrupt handler for a GPIO port.
//!
//! \param ulPort is the base address of the GPIO port.
//!
//! This function will unregister the interrupt handler for the specified
//! GPIO port.  This function will also disable the corresponding
//! GPIO port interrupt in the interrupt controller; individual GPIO interrupts
//! and interrupt sources must be disabled with GPIOPinIntDisable().
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPortIntUnregister(unsigned long ulPort)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPort == GPIO_PORTA_BASE) || (ulPort == GPIO_PORTB_BASE) ||
           (ulPort == GPIO_PORTC_BASE) || (ulPort == GPIO_PORTD_BASE) ||
           (ulPort == GPIO_PORTE_BASE) || (ulPort == GPIO_PORTF_BASE) ||
           (ulPort == GPIO_PORTG_BASE) || (ulPort == GPIO_PORTH_BASE));

    //
    // Get the interrupt number associated with the specified GPIO.
    //
    ulPort = GPIOGetIntNumber(ulPort);

    //
    // Disable the GPIO interrupt.
    //
    IntDisable(ulPort);

    //
    // Unregister the interrupt handler.
    //
    IntUnregister(ulPort);
}

//*****************************************************************************
//
//! Reads the values present of the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The values at the specified pin(s) are read, as specified by \e ucPins.
//! Values are returned for both input and output pin(s), and the value
//! for pin(s) that are not specified by \e ucPins are set to 0.
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, etc.
//!
//! \return Returns a bit-packed byte providing the state of the specified
//! pin, where bit 0 of the byte represents GPIO port pin 0, bit 1 represents
//! GPIO port pin 1, etc. Any bit that is not specified by \e ucPins
//! is returned as a 0. Bits 31:8 should be ignored.
//
//*****************************************************************************
long
GPIOPinRead(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPort == GPIO_PORTA_BASE) || (ulPort == GPIO_PORTB_BASE) ||
           (ulPort == GPIO_PORTC_BASE) || (ulPort == GPIO_PORTD_BASE) ||
           (ulPort == GPIO_PORTE_BASE) || (ulPort == GPIO_PORTF_BASE) ||
           (ulPort == GPIO_PORTG_BASE) || (ulPort == GPIO_PORTH_BASE));

    //
    // Return the pin value(s).
    //
    return(HWREG(ulPort + (GPIO_O_DATA + (ucPins << 2))));
}

//*****************************************************************************
//
//! Writes a value to the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//! \param ucVal is the value to write to the pin(s).
//!
//! Writes the corresponding bit values to the output pin(s) specified
//! by \e ucPins. Writing to a pin configured as an input pin has no
//! effect.
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, etc.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinWrite(unsigned long ulPort, unsigned char ucPins, unsigned char ucVal)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPort == GPIO_PORTA_BASE) || (ulPort == GPIO_PORTB_BASE) ||
           (ulPort == GPIO_PORTC_BASE) || (ulPort == GPIO_PORTD_BASE) ||
           (ulPort == GPIO_PORTE_BASE) || (ulPort == GPIO_PORTF_BASE) ||
           (ulPort == GPIO_PORTG_BASE) || (ulPort == GPIO_PORTH_BASE));

    //
    // Write the pins.
    //
    HWREG(ulPort + (GPIO_O_DATA + (ucPins << 2))) = ucVal;
}

//*****************************************************************************
//
//! Configures pin(s) for use as a CAN device.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The CAN pins must be properly configured for the CAN peripherals to
//! function correctly.  This function provides a typical configuration for
//! those pin(s); other configurations may work as well depending upon the
//! board setup (for example, using the on-chip pull-ups).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, etc.
//!
//! \note This cannot be used to turn any pin into a CAN pin(s); it only
//! configures a CAN pin(s) for proper operation.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeCAN(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPort == GPIO_PORTA_BASE) || (ulPort == GPIO_PORTB_BASE) ||
           (ulPort == GPIO_PORTC_BASE) || (ulPort == GPIO_PORTD_BASE) ||
           (ulPort == GPIO_PORTE_BASE) || (ulPort == GPIO_PORTF_BASE) ||
           (ulPort == GPIO_PORTG_BASE) || (ulPort == GPIO_PORTH_BASE));

    //
    // Make the pin(s) be inputs.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_HW);

    //
    // Set the pad(s) for standard push-pull operation.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD);
}

//*****************************************************************************
//
//! Configures pin(s) for use as an analog comparator input.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The analog comparator input pins must be properly configured for the analog
//! comparator to function correctly.  This function provides the proper
//! configuration for those pin(s).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, etc.
//!
//! \note This cannot be used to turn any pin into an analog comparator input;
//! it only configures an analog comparator pin for proper operation.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeComparator(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPort == GPIO_PORTA_BASE) || (ulPort == GPIO_PORTB_BASE) ||
           (ulPort == GPIO_PORTC_BASE) || (ulPort == GPIO_PORTD_BASE) ||
           (ulPort == GPIO_PORTE_BASE) || (ulPort == GPIO_PORTF_BASE) ||
           (ulPort == GPIO_PORTG_BASE) || (ulPort == GPIO_PORTH_BASE));

    //
    // Make the pin(s) be inputs.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_IN);

    //
    // Set the pad(s) for analog operation.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_ANALOG);
}

//*****************************************************************************
//
//! Configures pin(s) for use as GPIO inputs.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The GPIO pins must be properly configured in order to function correctly as
//! GPIO inputs; this is especially true of Fury-class devices where the
//! digital input enable is turned off by default.  This function provides the
//! proper configuration for those pin(s).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, etc.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeGPIOInput(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPort == GPIO_PORTA_BASE) || (ulPort == GPIO_PORTB_BASE) ||
           (ulPort == GPIO_PORTC_BASE) || (ulPort == GPIO_PORTD_BASE) ||
           (ulPort == GPIO_PORTE_BASE) || (ulPort == GPIO_PORTF_BASE) ||
           (ulPort == GPIO_PORTG_BASE) || (ulPort == GPIO_PORTH_BASE));

    //
    // Make the pin(s) be inputs.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_IN);

    //
    // Set the pad(s) for standard push-pull operation.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
}

//*****************************************************************************
//
//! Configures pin(s) for use as GPIO outputs.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The GPIO pins must be properly configured in order to function correctly as
//! GPIO outputs; this is especially true of Fury-class devices where the
//! digital input enable is turned off by default.  This function provides the
//! proper configuration for those pin(s).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, etc.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeGPIOOutput(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPort == GPIO_PORTA_BASE) || (ulPort == GPIO_PORTB_BASE) ||
           (ulPort == GPIO_PORTC_BASE) || (ulPort == GPIO_PORTD_BASE) ||
           (ulPort == GPIO_PORTE_BASE) || (ulPort == GPIO_PORTF_BASE) ||
           (ulPort == GPIO_PORTG_BASE) || (ulPort == GPIO_PORTH_BASE));

    //
    // Make the pin(s) be outputs.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_OUT);

    //
    // Set the pad(s) for standard push-pull operation.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
}

//*****************************************************************************
//
//! Configures pin(s) for use as GPIO open drain outputs.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The GPIO pins must be properly configured in order to function correctly as
//! GPIO outputs; this is especially true of Fury-class devices where the
//! digital input enable is turned off by default.  This function provides the
//! proper configuration for those pin(s).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, etc.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeGPIOOutputOD(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPort == GPIO_PORTA_BASE) || (ulPort == GPIO_PORTB_BASE) ||
           (ulPort == GPIO_PORTC_BASE) || (ulPort == GPIO_PORTD_BASE) ||
           (ulPort == GPIO_PORTE_BASE) || (ulPort == GPIO_PORTF_BASE) ||
           (ulPort == GPIO_PORTG_BASE) || (ulPort == GPIO_PORTH_BASE));

    //
    // Make the pin(s) be outputs.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_OUT);

    //
    // Set the pad(s) for standard push-pull operation.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_OD);
}

//*****************************************************************************
//
//! Configures pin(s) for use by the I2C peripheral.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The I2C pins must be properly configured for the I2C peripheral to function
//! correctly.  This function provides the proper configuration for those
//! pin(s).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, etc.
//!
//! \note This cannot be used to turn any pin into an I2C pin; it only
//! configures an I2C pin for proper operation.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeI2C(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPort == GPIO_PORTA_BASE) || (ulPort == GPIO_PORTB_BASE) ||
           (ulPort == GPIO_PORTC_BASE) || (ulPort == GPIO_PORTD_BASE) ||
           (ulPort == GPIO_PORTE_BASE) || (ulPort == GPIO_PORTF_BASE) ||
           (ulPort == GPIO_PORTG_BASE) || (ulPort == GPIO_PORTH_BASE));

    //
    // Make the pin(s) be peripheral controlled.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_HW);

    //
    // Set the pad(s) for open-drain operation with a weak pull-up.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_OD_WPU);
}

//*****************************************************************************
//
//! Configures pin(s) for use by the PWM peripheral.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The PWM pins must be properly configured for the PWM peripheral to function
//! correctly.  This function provides a typical configuration for those
//! pin(s); other configurations may work as well depending upon the board
//! setup (for example, using the on-chip pull-ups).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, etc.
//!
//! \note This cannot be used to turn any pin into a PWM pin; it only
//! configures a PWM pin for proper operation.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypePWM(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPort == GPIO_PORTA_BASE) || (ulPort == GPIO_PORTB_BASE) ||
           (ulPort == GPIO_PORTC_BASE) || (ulPort == GPIO_PORTD_BASE) ||
           (ulPort == GPIO_PORTE_BASE) || (ulPort == GPIO_PORTF_BASE) ||
           (ulPort == GPIO_PORTG_BASE) || (ulPort == GPIO_PORTH_BASE));

    //
    // Make the pin(s) be peripheral controlled.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_HW);

    //
    // Set the pad(s) for standard push-pull operation.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
}

//*****************************************************************************
//
//! Configures pin(s) for use by the QEI peripheral.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The QEI pins must be properly configured for the QEI peripheral to function
//! correctly.  This function provides a typical configuration for those
//! pin(s); other configurations may work as well depending upon the board
//! setup (for example, not using the on-chip pull-ups).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, etc.
//!
//! \note This cannot be used to turn any pin into a QEI pin; it only
//! configures a QEI pin for proper operation.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeQEI(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPort == GPIO_PORTA_BASE) || (ulPort == GPIO_PORTB_BASE) ||
           (ulPort == GPIO_PORTC_BASE) || (ulPort == GPIO_PORTD_BASE) ||
           (ulPort == GPIO_PORTE_BASE) || (ulPort == GPIO_PORTF_BASE) ||
           (ulPort == GPIO_PORTG_BASE) || (ulPort == GPIO_PORTH_BASE));

    //
    // Make the pin(s) be peripheral controlled.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_HW);

    //
    // Set the pad(s) for standard push-pull operation with a weak pull-up.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}

//*****************************************************************************
//
//! Configures pin(s) for use by the SSI peripheral.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The SSI pins must be properly configured for the SSI peripheral to function
//! correctly.  This function provides a typical configuration for those
//! pin(s); other configurations may work as well depending upon the board
//! setup (for example, using the on-chip pull-ups).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, etc.
//!
//! \note This cannot be used to turn any pin into a SSI pin; it only
//! configures a SSI pin for proper operation.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeSSI(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPort == GPIO_PORTA_BASE) || (ulPort == GPIO_PORTB_BASE) ||
           (ulPort == GPIO_PORTC_BASE) || (ulPort == GPIO_PORTD_BASE) ||
           (ulPort == GPIO_PORTE_BASE) || (ulPort == GPIO_PORTF_BASE) ||
           (ulPort == GPIO_PORTG_BASE) || (ulPort == GPIO_PORTH_BASE));

    //
    // Make the pin(s) be peripheral controlled.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_HW);

    //
    // Set the pad(s) for standard push-pull operation.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
}

//*****************************************************************************
//
//! Configures pin(s) for use by the Timer peripheral.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The CCP pins must be properly configured for the timer peripheral to
//! function correctly.  This function provides a typical configuration for
//! those pin(s); other configurations may work as well depending upon the
//! board setup (for example, using the on-chip pull-ups).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, etc.
//!
//! \note This cannot be used to turn any pin into a timer pin; it only
//! configures a timer pin for proper operation.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeTimer(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPort == GPIO_PORTA_BASE) || (ulPort == GPIO_PORTB_BASE) ||
           (ulPort == GPIO_PORTC_BASE) || (ulPort == GPIO_PORTD_BASE) ||
           (ulPort == GPIO_PORTE_BASE) || (ulPort == GPIO_PORTF_BASE) ||
           (ulPort == GPIO_PORTG_BASE) || (ulPort == GPIO_PORTH_BASE));

    //
    // Make the pin(s) be peripheral controlled.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_HW);

    //
    // Set the pad(s) for standard push-pull operation.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
}

//*****************************************************************************
//
//! Configures pin(s) for use by the UART peripheral.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The UART pins must be properly configured for the UART peripheral to
//! function correctly.  This function provides a typical configuration for
//! those pin(s); other configurations may work as well depending upon the
//! board setup (for example, using the on-chip pull-ups).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, etc.
//!
//! \note This cannot be used to turn any pin into a UART pin; it only
//! configures a UART pin for proper operation.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeUART(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPort == GPIO_PORTA_BASE) || (ulPort == GPIO_PORTB_BASE) ||
           (ulPort == GPIO_PORTC_BASE) || (ulPort == GPIO_PORTD_BASE) ||
           (ulPort == GPIO_PORTE_BASE) || (ulPort == GPIO_PORTF_BASE) ||
           (ulPort == GPIO_PORTG_BASE) || (ulPort == GPIO_PORTH_BASE));

    //
    // Make the pin(s) be peripheral controlled.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_HW);

    //
    // Set the pad(s) for standard push-pull operation.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
