//*****************************************************************************
//
// uart.c - Driver for the UART.
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
//! \addtogroup uart_api
//! @{
//
//*****************************************************************************

#include "../hw_ints.h"
#include "../hw_memmap.h"
#include "../hw_types.h"
#include "../hw_uart.h"
#include "debug.h"
#include "sysctl.h"
#include "uart.h"
#include "lm3sinterrupt.h"

//*****************************************************************************
//
//! Sets the type of parity.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulParity specifies the type of parity to use.
//!
//! Sets the type of parity to use for transmitting and expect when receiving.
//! The \e ulParity parameter must be one of \b UART_CONFIG_PAR_NONE,
//! \b UART_CONFIG_PAR_EVEN, \b UART_CONFIG_PAR_ODD, \b UART_CONFIG_PAR_ONE,
//! or \b UART_CONFIG_PAR_ZERO.  The last two allow direct control of the
//! parity bit; it will always be either be one or zero based on the mode.
//!
//! \return None.
//
//*****************************************************************************
void
UARTParityModeSet(unsigned long ulBase, unsigned long ulParity)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
           (ulBase == UART2_BASE));
    ASSERT((ulParity == UART_CONFIG_PAR_NONE) ||
           (ulParity == UART_CONFIG_PAR_EVEN) ||
           (ulParity == UART_CONFIG_PAR_ODD) ||
           (ulParity == UART_CONFIG_PAR_ONE) ||
           (ulParity == UART_CONFIG_PAR_ZERO));

    //
    // Set the parity mode.
    //
    HWREG(ulBase + UART_O_LCR_H) = ((HWREG(ulBase + UART_O_LCR_H) &
                                     ~(UART_LCR_H_SPS | UART_LCR_H_EPS |
                                       UART_LCR_H_PEN)) | ulParity);
}

//*****************************************************************************
//
//! Gets the type of parity currently being used.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function gets the type of parity used for transmitting data, and
//! expected when receiving data.
//!
//! \return The current parity settings, specified as one of
//! \b UART_CONFIG_PAR_NONE, \b UART_CONFIG_PAR_EVEN, \b UART_CONFIG_PAR_ODD,
//! \b UART_CONFIG_PAR_ONE, or \b UART_CONFIG_PAR_ZERO.
//
//*****************************************************************************
unsigned long
UARTParityModeGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
           (ulBase == UART2_BASE));

    //
    // Return the current parity setting.
    //
    return(HWREG(ulBase + UART_O_LCR_H) &
           (UART_LCR_H_SPS | UART_LCR_H_EPS | UART_LCR_H_PEN));
}

//*****************************************************************************
//
//! Sets the FIFO level at which interrupts are generated.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulTxLevel is the transmit FIFO interrupt level, specified as one of
//! \b UART_FIFO_TX1_8, \b UART_FIFO_TX2_8, \b UART_FIFO_TX4_8,
//! \b UART_FIFO_TX6_8, or UART_FIFO_TX7_8.
//! \param ulRxLevel is the receive FIFO interrupt level, specified as one of
//! \b UART_FIFO_RX1_8, \b UART_FIFO_RX2_8, \b UART_FIFO_RX4_8,
//! \b UART_FIFO_RX6_8, or \b UART_FIFO_RX7_8.
//!
//! This function sets the FIFO level at which transmit and receive interrupts
//! will be generated.
//!
//! \return None.
//
//*****************************************************************************
void
UARTFIFOLevelSet(unsigned long ulBase, unsigned long ulTxLevel,
                 unsigned long ulRxLevel)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
           (ulBase == UART2_BASE));
    ASSERT((ulTxLevel == UART_FIFO_TX1_8) ||
           (ulTxLevel == UART_FIFO_TX2_8) ||
           (ulTxLevel == UART_FIFO_TX4_8) ||
           (ulTxLevel == UART_FIFO_TX6_8) ||
           (ulTxLevel == UART_FIFO_TX7_8));
    ASSERT((ulRxLevel == UART_FIFO_RX1_8) ||
           (ulRxLevel == UART_FIFO_RX2_8) ||
           (ulRxLevel == UART_FIFO_RX4_8) ||
           (ulRxLevel == UART_FIFO_RX6_8) ||
           (ulRxLevel == UART_FIFO_RX7_8));

    //
    // Set the FIFO interrupt levels.
    //
    HWREG(ulBase + UART_O_IFLS) = ulTxLevel | ulRxLevel;
}

//*****************************************************************************
//
//! Gets the FIFO level at which interrupts are generated.
//!
//! \param ulBase is the base address of the UART port.
//! \param pulTxLevel is a pointer to storage for the transmit FIFO level,
//! returned as one of \b UART_FIFO_TX1_8, \b UART_FIFO_TX2_8,
//! \b UART_FIFO_TX4_8, \b UART_FIFO_TX6_8, or UART_FIFO_TX7_8.
//! \param pulRxLevel is a pointer to storage for the receive FIFO level,
//! returned as one of \b UART_FIFO_RX1_8, \b UART_FIFO_RX2_8,
//! \b UART_FIFO_RX4_8, \b UART_FIFO_RX6_8, or \b UART_FIFO_RX7_8.
//!
//! This function gets the FIFO level at which transmit and receive interrupts
//! will be generated.
//!
//! \return None.
//
//*****************************************************************************
void
UARTFIFOLevelGet(unsigned long ulBase, unsigned long *pulTxLevel,
                 unsigned long *pulRxLevel)
{
    unsigned long ulTemp;

    //
    // Check the arguments.
    //
    ASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
           (ulBase == UART2_BASE));

    //
    // Read the FIFO level register.
    //
    ulTemp = HWREG(ulBase + UART_O_IFLS);

    //
    // Extract the transmit and receive FIFO levels.
    //
    *pulTxLevel = ulTemp & UART_IFLS_TX_MASK;
    *pulRxLevel = ulTemp & UART_IFLS_RX_MASK;
}

//*****************************************************************************
//
//! Sets the configuration of a UART.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulUARTClk is the rate of the clock supplied to the UART module.
//! \param ulBaud is the desired baud rate.
//! \param ulConfig is the data format for the port (number of data bits,
//! number of stop bits, and parity).
//!
//! This function will configure the UART for operation in the specified data
//! format.  The baud rate is provided in the \e ulBaud parameter and the data
//! format in the \e ulConfig parameter.
//!
//! The \e ulConfig parameter is the logical OR of three values: the number of
//! data bits, the number of stop bits, and the parity.  \b UART_CONFIG_WLEN_8,
//! \b UART_CONFIG_WLEN_7, \b UART_CONFIG_WLEN_6, and \b UART_CONFIG_WLEN_5
//! select from eight to five data bits per byte (respectively).
//! \b UART_CONFIG_STOP_ONE and \b UART_CONFIG_STOP_TWO select one or two stop
//! bits (respectively).  \b UART_CONFIG_PAR_NONE, \b UART_CONFIG_PAR_EVEN,
//! \b UART_CONFIG_PAR_ODD, \b UART_CONFIG_PAR_ONE, and \b UART_CONFIG_PAR_ZERO
//! select the parity mode (no parity bit, even parity bit, odd parity bit,
//! parity bit always one, and parity bit always zero, respectively).
//!
//! The peripheral clock will be the same as the processor clock.  This will be
//! the value returned by SysCtlClockGet(), or it can be explicitly hard coded
//! if it is constant and known (to save the code/execution overhead of a call
//! to SysCtlClockGet()).
//!
//! This function replaces the original UARTConfigSet() API and performs the
//! same actions.  A macro is provided in <tt>uart.h</tt> to map the original
//! API to this API.
//!
//! \return None.
//
//*****************************************************************************
void
UARTConfigSetExpClk(unsigned long ulBase, unsigned long ulUARTClk,
                    unsigned long ulBaud, unsigned long ulConfig)
{
    unsigned long ulInt, ulFrac;

    //
    // Check the arguments.
    //
    ASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
           (ulBase == UART2_BASE));
    ASSERT(ulUARTClk >= (ulBaud * 16));
    ASSERT(ulBaud != 0);

    //
    // Stop the UART.
    //
    UARTDisable(ulBase);

    //
    // Compute the fractional baud rate divider.
    //
    ulInt = ulUARTClk / (16 * ulBaud);
    ulFrac = ulUARTClk % (16 * ulBaud);
    ulFrac = ((((2 * ulFrac * 4) / ulBaud) + 1) / 2);

    //
    // Set the baud rate.
    //
    HWREG(ulBase + UART_O_IBRD) = ulInt;
    HWREG(ulBase + UART_O_FBRD) = ulFrac;

    //
    // Set parity, data length, and number of stop bits.
    //
    HWREG(ulBase + UART_O_LCR_H) = ulConfig;

    //
    // Clear the flags register.
    //
    HWREG(ulBase + UART_O_FR) = 0;

    //
    // Start the UART.
    //
    UARTEnable(ulBase);
}

//*****************************************************************************
//
//! Gets the current configuration of a UART.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulUARTClk is the rate of the clock supplied to the UART module.
//! \param pulBaud is a pointer to storage for the baud rate.
//! \param pulConfig is a pointer to storage for the data format.
//!
//! The baud rate and data format for the UART is determined, given an
//! explicitly provided peripheral clock (hence the ExpClk suffix).  The
//! returned baud rate is the actual baud rate; it may not be the exact baud
//! rate requested or an ``official'' baud rate.  The data format returned in
//! \e pulConfig is enumerated the same as the \e ulConfig parameter of
//! UARTConfigSetExpClk().
//!
//! The peripheral clock will be the same as the processor clock.  This will be
//! the value returned by SysCtlClockGet(), or it can be explicitly hard coded
//! if it is constant and known (to save the code/execution overhead of a call
//! to SysCtlClockGet()).
//!
//! This function replaces the original UARTConfigGet() API and performs the
//! same actions.  A macro is provided in <tt>uart.h</tt> to map the original
//! API to this API.
//!
//! \return None.
//
//*****************************************************************************
void
UARTConfigGetExpClk(unsigned long ulBase, unsigned long ulUARTClk,
                    unsigned long *pulBaud, unsigned long *pulConfig)
{
    unsigned long ulInt, ulFrac;

    //
    // Check the arguments.
    //
    ASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
           (ulBase == UART2_BASE));

    //
    // Compute the baud rate.
    //
    ulInt = HWREG(ulBase + UART_O_IBRD);
    ulFrac = HWREG(ulBase + UART_O_FBRD);
    *pulBaud = (ulUARTClk * 4) / ((64 * ulInt) + ulFrac);

    //
    // Get the parity, data length, and number of stop bits.
    //
    *pulConfig = (HWREG(ulBase + UART_O_LCR_H) &
                  (UART_LCR_H_SPS | UART_LCR_H_WLEN | UART_LCR_H_STP2 |
                   UART_LCR_H_EPS | UART_LCR_H_PEN));
}

//*****************************************************************************
//
//! Enables transmitting and receiving.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Sets the UARTEN, TXE, and RXE bits, and enables the transmit and receive
//! FIFOs.
//!
//! \return None.
//
//*****************************************************************************
void
UARTEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
           (ulBase == UART2_BASE));

    //
    // Enable the FIFO.
    //
    HWREG(ulBase + UART_O_LCR_H) |= UART_LCR_H_FEN;

    //
    // Enable RX, TX, and the UART.
    //
    HWREG(ulBase + UART_O_CTL) |= (UART_CTL_UARTEN | UART_CTL_TXE |
                                   UART_CTL_RXE);
}

//*****************************************************************************
//
//! Disables transmitting and receiving.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Clears the UARTEN, TXE, and RXE bits, then waits for the end of
//! transmission of the current character, and flushes the transmit FIFO.
//!
//! \return None.
//
//*****************************************************************************
void
UARTDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
           (ulBase == UART2_BASE));

    //
    // Wait for end of TX.
    //
    while(HWREG(ulBase + UART_O_FR) & UART_FR_BUSY)
    {
    }

    //
    // Disable the FIFO.
    //
    HWREG(ulBase + UART_O_LCR_H) &= ~(UART_LCR_H_FEN);

    //
    // Disable the UART.
    //
    HWREG(ulBase + UART_O_CTL) &= ~(UART_CTL_UARTEN | UART_CTL_TXE |
                                    UART_CTL_RXE);
}

//*****************************************************************************
//
//! Enables SIR (IrDA) mode on specified UART.
//!
//! \param ulBase is the base address of the UART port.
//! \param bLowPower indicates if SIR Low Power Mode is to be used.
//!
//! Enables the SIREN control bit for IrDA mode on the UART.  If the
//! \e bLowPower flag is set, then SIRLP bit will also be set.
//!
//! \note SIR (IrDA) operation is supported only on Fury-class devices.
//!
//! \return None.
//
//*****************************************************************************
void
UARTEnableSIR(unsigned long ulBase, tBoolean bLowPower)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
           (ulBase == UART2_BASE));

    //
    // Return if UART2 is not specified.
    //
    if(ulBase != UART2_BASE)
    {
        return;
    }

    //
    // Enable SIR and SIRLP (if appropriate).
    //
    if(bLowPower)
    {
        HWREG(ulBase + UART_O_CTL) |= (UART_CTL_SIREN | UART_CTL_SIRLP);
    }
    else
    {
        HWREG(ulBase + UART_O_CTL) |= (UART_CTL_SIREN);
    }
}

//*****************************************************************************
//
//! Disables SIR (IrDA) mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Clears the SIREN (IrDA) and SIRLP (Low Power) bits.
//!
//! \note SIR (IrDA) operation is supported only on Fury-class devices.
//!
//! \return None.
//
//*****************************************************************************
void
UARTDisableSIR(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
           (ulBase == UART2_BASE));

    //
    // Return if UART2 is not specified.
    //
    if(ulBase != UART2_BASE)
    {
        return;
    }

    //
    // Disable SIR and SIRLP (if appropriate).
    //
    HWREG(ulBase + UART_O_CTL) &= ~(UART_CTL_SIREN | UART_CTL_SIRLP);
}

//*****************************************************************************
//
//! Determines if there are any characters in the receive FIFO.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function returns a flag indicating whether or not there is data
//! available in the receive FIFO.
//!
//! \return Returns \b true if there is data in the receive FIFO, and \b false
//! if there is no data in the receive FIFO.
//
//*****************************************************************************
tBoolean
UARTCharsAvail(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
           (ulBase == UART2_BASE));

    //
    // Return the availability of characters.
    //
    return((HWREG(ulBase + UART_O_FR) & UART_FR_RXFE) ? false : true);
}

//*****************************************************************************
//
//! Determines if there is any space in the transmit FIFO.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function returns a flag indicating whether or not there is space
//! available in the transmit FIFO.
//!
//! \return Returns \b true if there is space available in the transmit FIFO,
//! and \b false if there is no space available in the transmit FIFO.
//
//*****************************************************************************
tBoolean
UARTSpaceAvail(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
           (ulBase == UART2_BASE));

    //
    // Return the availability of space.
    //
    return((HWREG(ulBase + UART_O_FR) & UART_FR_TXFF) ? false : true);
}

//*****************************************************************************
//
//! Receives a character from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Gets a character from the receive FIFO for the specified port.
//!
//! This function replaces the original UARTCharNonBlockingGet() API and
//! performs the same actions.  A macro is provided in <tt>uart.h</tt> to map
//! the original API to this API.
//!
//! \return Returns the character read from the specified port, cast as a
//! \e long.  A \b -1 will be returned if there are no characters present in
//! the receive FIFO.  The UARTCharsAvail() function should be called before
//! attempting to call this function.
//
//*****************************************************************************
long
UARTCharGetNonBlocking(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
           (ulBase == UART2_BASE));

    //
    // See if there are any characters in the receive FIFO.
    //
    if(!(HWREG(ulBase + UART_O_FR) & UART_FR_RXFE))
    {
        //
        // Read and return the next character.
        //
        return(HWREG(ulBase + UART_O_DR));
    }
    else
    {
        //
        // There are no characters, so return a failure.
        //
        return(-1);
    }
}

//*****************************************************************************
//
//! Waits for a character from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Gets a character from the receive FIFO for the specified port.  If there
//! are no characters available, this function will wait until a character is
//! received before returning.
//!
//! \return Returns the character read from the specified port, cast as an
//! \e int.
//
//*****************************************************************************
long
UARTCharGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
           (ulBase == UART2_BASE));

    //
    // Wait until a char is available.
    //
    while(HWREG(ulBase + UART_O_FR) & UART_FR_RXFE)
    {
    }

    //
    // Now get the char.
    //
    return(HWREG(ulBase + UART_O_DR));
}

//*****************************************************************************
//
//! Sends a character to the specified port.
//!
//! \param ulBase is the base address of the UART port.
//! \param ucData is the character to be transmitted.
//!
//! Writes the character \e ucData to the transmit FIFO for the specified port.
//! This function does not block, so if there is no space available, then a
//! \b false is returned, and the application will have to retry the function
//! later.
//!
//! This function replaces the original UARTCharNonBlockingPut() API and
//! performs the same actions.  A macro is provided in <tt>uart.h</tt> to map
//! the original API to this API.
//!
//! \return Returns \b true if the character was successfully placed in the
//! transmit FIFO, and \b false if there was no space available in the transmit
//! FIFO.
//
//*****************************************************************************
tBoolean
UARTCharPutNonBlocking(unsigned long ulBase, unsigned char ucData)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
           (ulBase == UART2_BASE));

    //
    // See if there is space in the transmit FIFO.
    //
    if(!(HWREG(ulBase + UART_O_FR) & UART_FR_TXFF))
    {
        //
        // Write this character to the transmit FIFO.
        //
        HWREG(ulBase + UART_O_DR) = ucData;

        //
        // Success.
        //
        return(true);
    }
    else
    {
        //
        // There is no space in the transmit FIFO, so return a failure.
        //
        return(false);
    }
}

//*****************************************************************************
//
//! Waits to send a character from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//! \param ucData is the character to be transmitted.
//!
//! Sends the character \e ucData to the transmit FIFO for the specified port.
//! If there is no space available in the transmit FIFO, this function will
//! wait until there is space available before returning.
//!
//! \return None.
//
//*****************************************************************************
void
UARTCharPut(unsigned long ulBase, unsigned char ucData)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
           (ulBase == UART2_BASE));

    //
    // Wait until space is available.
    //
    while(HWREG(ulBase + UART_O_FR) & UART_FR_TXFF)
    {
    }

    //
    // Send the char.
    //
    HWREG(ulBase + UART_O_DR) = ucData;
}

//*****************************************************************************
//
//! Causes a BREAK to be sent.
//!
//! \param ulBase is the base address of the UART port.
//! \param bBreakState controls the output level.
//!
//! Calling this function with \e bBreakState set to \b true will assert a
//! break condition on the UART.  Calling this function with \e bBreakState set
//! to \b false will remove the break condition.  For proper transmission of a
//! break command, the break must be asserted for at least two complete frames.
//!
//! \return None.
//
//*****************************************************************************
void
UARTBreakCtl(unsigned long ulBase, tBoolean bBreakState)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
           (ulBase == UART2_BASE));

    //
    // Set the break condition as requested.
    //
    HWREG(ulBase + UART_O_LCR_H) =
        (bBreakState ?
         (HWREG(ulBase + UART_O_LCR_H) | UART_LCR_H_BRK) :
         (HWREG(ulBase + UART_O_LCR_H) & ~(UART_LCR_H_BRK)));
}

//*****************************************************************************
//
//! Registers an interrupt handler for a UART interrupt.
//!
//! \param ulBase is the base address of the UART port.
//! \param pfnHandler is a pointer to the function to be called when the
//! UART interrupt occurs.
//!
//! This function does the actual registering of the interrupt handler.  This
//! will enable the global interrupt in the interrupt controller; specific UART
//! interrupts must be enabled via UARTIntEnable().  It is the interrupt
//! handler's responsibility to clear the interrupt source.
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
UARTIntRegister(unsigned long ulBase, void (*pfnHandler)(void))
{
    unsigned long ulInt;

    //
    // Check the arguments.
    //
    ASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
           (ulBase == UART2_BASE));

    //
    // Determine the interrupt number based on the UART port.
    //
    ulInt = ((ulBase == UART0_BASE) ? INT_UART0 :
             ((ulBase == UART1_BASE) ? INT_UART1 : INT_UART2));

    //
    // Register the interrupt handler.
    //
    IntRegister(ulInt, pfnHandler);

    //
    // Enable the UART interrupt.
    //
    IntEnable(ulInt);
}

//*****************************************************************************
//
//! Unregisters an interrupt handler for a UART interrupt.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function does the actual unregistering of the interrupt handler.  It
//! will clear the handler to be called when a UART interrupt occurs.  This
//! will also mask off the interrupt in the interrupt controller so that the
//! interrupt handler no longer is called.
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
UARTIntUnregister(unsigned long ulBase)
{
    unsigned long ulInt;

    //
    // Check the arguments.
    //
    ASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
           (ulBase == UART2_BASE));

    //
    // Determine the interrupt number based on the UART port.
    //
    ulInt = ((ulBase == UART0_BASE) ? INT_UART0 :
             ((ulBase == UART1_BASE) ? INT_UART1 : INT_UART2));

    //
    // Disable the interrupt.
    //
    IntDisable(ulInt);

    //
    // Unregister the interrupt handler.
    //
    IntUnregister(ulInt);
}

//*****************************************************************************
//
//! Enables individual UART interrupt sources.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulIntFlags is the bit mask of the interrupt sources to be enabled.
//!
//! Enables the indicated UART interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor.
//!
//! The parameter \e ulIntFlags is the logical OR of any of the following:
//!
//! - UART_INT_OE - Overrun Error interrupt
//! - UART_INT_BE - Break Error interrupt
//! - UART_INT_PE - Parity Error interrupt
//! - UART_INT_FE - Framing Error interrupt
//! - UART_INT_RT - Receive Timeout interrupt
//! - UART_INT_TX - Transmit interrupt
//! - UART_INT_RX - Receive interrupt
//!
//! \return None.
//
//*****************************************************************************
void
UARTIntEnable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
           (ulBase == UART2_BASE));

    //
    // Enable the specified interrupts.
    //
    HWREG(ulBase + UART_O_IM) |= ulIntFlags;
}

//*****************************************************************************
//
//! Disables individual UART interrupt sources.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulIntFlags is the bit mask of the interrupt sources to be disabled.
//!
//! Disables the indicated UART interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor.
//!
//! The parameter \e ulIntFlags has the same definition as the same parameter
//! to UARTIntEnable().
//!
//! \return None.
//
//*****************************************************************************
void
UARTIntDisable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
           (ulBase == UART2_BASE));

    //
    // Disable the specified interrupts.
    //
    HWREG(ulBase + UART_O_IM) &= ~(ulIntFlags);
}

//*****************************************************************************
//
//! Gets the current interrupt status.
//!
//! \param ulBase is the base address of the UART port.
//! \param bMasked is false if the raw interrupt status is required and true
//! if the masked interrupt status is required.
//!
//! This returns the interrupt status for the specified UART.  Either the raw
//! interrupt status or the status of interrupts that are allowed to reflect to
//! the processor can be returned.
//!
//! \return The current interrupt status, enumerated as a bit field of
//! values described in UARTIntEnable().
//
//*****************************************************************************
unsigned long
UARTIntStatus(unsigned long ulBase, tBoolean bMasked)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
           (ulBase == UART2_BASE));

    //
    // Return either the interrupt status or the raw interrupt status as
    // requested.
    //
    if(bMasked)
    {
        return(HWREG(ulBase + UART_O_MIS));
    }
    else
    {
        return(HWREG(ulBase + UART_O_RIS));
    }
}

//*****************************************************************************
//
//! Clears UART interrupt sources.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulIntFlags is a bit mask of the interrupt sources to be cleared.
//!
//! The specified UART interrupt sources are cleared, so that they no longer
//! assert.  This must be done in the interrupt handler to keep it from being
//! called again immediately upon exit.
//!
//! The parameter \e ulIntFlags has the same definition as the same parameter
//! to UARTIntEnable().
//!
//! \return None.
//
//*****************************************************************************
void
UARTIntClear(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
           (ulBase == UART2_BASE));

    //
    // Clear the requested interrupt sources.
    //
    HWREG(ulBase + UART_O_ICR) = ulIntFlags;
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
