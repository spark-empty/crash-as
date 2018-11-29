//*****************************************************************************
//
// hibernate.c - Driver for the hibernation module
//
// Copyright (c) 2007 Luminary Micro, Inc.  All rights reserved.
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
//! \addtogroup hibernate_api
//! @{
//
//*****************************************************************************

#include "../hw_memmap.h"
#include "../hw_types.h"
#include "../hw_ints.h"
#include "../hw_hibernate.h"
#include "sysctl.h"
#include "hibernate.h"
#include "debug.h"
#include "lm3sinterrupt.h"

//*****************************************************************************
//
// The delay in microseconds for writing to the Hibernation module registers.
//
//*****************************************************************************
#define DELAY_USECS             95

//*****************************************************************************
//
// The number of processor cycles to execute one pass of the delay loop.
//
//*****************************************************************************
#define LOOP_CYCLES             3

//*****************************************************************************
//
// The calculated number of delay loops to achieve the write delay.
//
//*****************************************************************************
static unsigned long g_ulWriteDelay;

//*****************************************************************************
//
//! \internal
//!
//! Provides a small delay.
//!
//! \param ulCount is the number of delay loop iterations to perform.
//!
//! Since the hibernation module needs a delay between words written to it,
//! this function provides a means of generating that delay.  It is written in
//! assembly to keep the delay consistent across tool chains, avoiding the need
//! to tune the delay based on the tool chain in use.
//!
//! The loop below in theory takes 4 cycles/loop.
//!
//! \return None.
//
//*****************************************************************************
#if defined(ewarm)
static void
HibernateWriteDelay(unsigned long ulCount)
{
    __asm("    subs    r0, #1\n"
          "    bne     HibernateWriteDelay\n"
          "    bx      lr");
}
#endif
#if defined(gcc) || defined(sourcerygxx)
static void __attribute__((naked))
HibernateWriteDelay(unsigned long ulCount)
{
    __asm("    subs    r0, #1\n"
          "    bne     HibernateWriteDelay\n"
          "    bx      lr");
}
#endif
#if defined(rvmdk) || defined(__ARMCC_VERSION)
__asm void
HibernateWriteDelay(unsigned long ulCount)
{
    subs    r0, #1;
    bne     HibernateWriteDelay;
    bx      lr;
}
#endif

//*****************************************************************************
//
//! Enables the hibernation module for operation.
//!
//! \param ulHibClk is the rate of the clock supplied to the hibernateion
//! module.
//!
//! Enables the hibernation module for operation.  This function should be
//! called before any of the hibernation module features are used.
//!
//! The peripheral clock will be the same as the processor clock.  This will be
//! the value returned by SysCtlClockGet(), or it can be explicitly hard coded
//! if it is constant and known (to save the code/execution overhead of a call
//! to SysCtlClockGet()).
//!
//! This function replaces the original HibernateEnable() API and performs the
//! same actions.  A macro is provided in <tt>hibernate.h</tt> to map the
//! original API to this API.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateEnableExpClk(unsigned long ulHibClk)
{
    //
    // Turn on the clock enable bit.
    //
    HWREG(HIB_CTL) |= HIB_CTL_CLK32EN;

    //
    // Compute the number of delay loops that must be used to achieve the
    // desired delay for writes to the hibernation registers.  This value
    // will be used in calls to HibernateWriteDelay().
    //
    g_ulWriteDelay = ((ulHibClk / 1000) * DELAY_USECS) / (1000L * LOOP_CYCLES);
    g_ulWriteDelay++;
}

//*****************************************************************************
//
//! Disables the hibernation module for operation.
//!
//! Disables the hibernation module for operation.  After this function is
//! called, none of the hibernation module features are available.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateDisable(void)
{
    //
    // Turn off the clock enable bit.
    //
    HWREG(HIB_CTL) &= ~HIB_CTL_CLK32EN;
}

//*****************************************************************************
//
//! Selects the clock input for the hibernation module.
//!
//! \param ulClockInput specifies the clock input.
//!
//! Configures the clock input for the hibernation module.  The configuration
//! option chosen depends entirely on hardware design.  The clock input for the
//! module will either be a 32.768 kHz oscillator or a 4.194304 MHz crystal.
//! The parameter \e ulClockFlags must be one of the following:
//!
//! - HIBERNATE_CLOCK_SEL_RAW - use the raw signal from a 32.768 kHz
//!                             oscillator.
//! - HIBERNATE_CLOCK_SEL_DIV128 - use the crystal input, divided by 128.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateClockSelect(unsigned long ulClockInput)
{
    //
    // Check the arguments.
    //
    ASSERT((ulClockInput == HIBERNATE_CLOCK_SEL_RAW) ||
           (ulClockInput == HIBERNATE_CLOCK_SEL_DIV128));

    //
    // Set the clock selection bit according to the parameter.
    //
    HWREG(HIB_CTL) = ulClockInput | (HWREG(HIB_CTL) & ~HIB_CTL_CLKSEL);
}

//*****************************************************************************
//
//! Enables the RTC feature of the hibernation module.
//!
//! Enables the RTC in the hibernation module.  The RTC can be used to wake the
//! processor from hibernation at a certain time, or to generate interrupts at
//! certain times.  This function must be called before using any of the RTC
//! features of the hibernation module.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateRTCEnable(void)
{
    //
    // Turn on the RTC enable bit.
    //
    HWREG(HIB_CTL) |= HIB_CTL_RTCEN;
}

//*****************************************************************************
//
//! Disables the RTC feature of the hibernation module.
//!
//! Disables the RTC in the hibernation module.  After calling this function
//! the RTC features of the hibernation module will not be available.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateRTCDisable(void)
{
    //
    // Turn off the RTC enable bit.
    //
    HWREG(HIB_CTL) &= ~HIB_CTL_RTCEN;
}

//*****************************************************************************
//
//! Configures the wake conditions for the hibernation module.
//!
//! \param ulWakeFlags specifies which conditions should be used for waking.
//!
//! Enables the conditions under which the hibernation module will wake.  The
//! parameter \e ulWakeFlags is the logical or of any combination of the
//! following:
//!
//! - HIBERNATE_WAKE_PIN - wake when the external wake pin is asserted.
//! - HIBERNATE_WAKE_RTC - wake when one of the RTC matches occurs.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateWakeSet(unsigned long ulWakeFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(!(ulWakeFlags & ~(HIBERNATE_WAKE_PIN | HIBERNATE_WAKE_RTC)));

    //
    // Set the specified wake flags in the control register.
    //
    HWREG(HIB_CTL) = (ulWakeFlags |
                      (HWREG(HIB_CTL) &
                       ~(HIBERNATE_WAKE_PIN | HIBERNATE_WAKE_RTC)));
}

//*****************************************************************************
//
//! Gets the currently configured wake conditions for the hibernation module.
//!
//! Returns the flags representing the wake configuration for the hibernation
//! module.  The return value will be a combination of the following flags:
//!
//! - HIBERNATE_WAKE_PIN - wake when the external wake pin is asserted.
//! - HIBERNATE_WAKE_RTC - wake when one of the RTC matches occurs.
//!
//! \return flags indicating the configured wake conditions.
//
//*****************************************************************************
unsigned long
HibernateWakeGet(void)
{
    //
    // Read the wake bits from the control register and return
    // those bits to the caller.
    //
    return(HWREG(HIB_CTL) & (HIBERNATE_WAKE_PIN | HIBERNATE_WAKE_RTC));
}

//*****************************************************************************
//
//! Configures the low battery detection.
//!
//! \param ulLowBatFlags specifies behavior of low battery detection.
//!
//! Enables the low battery detection and whether hibernation is allowed if a
//! low battery is detected.  If low battery detection is enabled, then a low
//! battery condition will be indicated in the raw interrupt status register,
//! and can also trigger an interrupt.  Optionally, hibernation can be aborted
//! if a low battery is detected.
//!
//! The parameter \e ulLowBatFlags is one of the following values:
//!
//! - HIBERNATE_LOW_BAT_DETECT - detect a low battery condition.
//! - HIBERNATE_LOW_BAT_ABORT - detect a low battery condition, and abort
//!                             hibernation if low battery is detected.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateLowBatSet(unsigned long ulLowBatFlags)
{
    //
    // Check the arguments.
    //
    ASSERT((ulLowBatFlags == HIBERNATE_LOW_BAT_DETECT) ||
           (ulLowBatFlags == HIBERNATE_LOW_BAT_ABORT));

    //
    // Set the low battery detect and abort bits in the control register,
    // according to the parameter.
    //
    HWREG(HIB_CTL) = (ulLowBatFlags |
                      (HWREG(HIB_CTL) & ~HIBERNATE_LOW_BAT_ABORT));
}

//*****************************************************************************
//
//! Gets the currently configured low battery detection behavior.
//!
//! Returns a value representing the currently configured low battery detection
//! behavior.  The return value will be one of the following:
//!
//! - HIBERNATE_LOW_BAT_DETECT - detect a low battery condition.
//! - HIBERNATE_LOW_BAT_ABORT - detect a low battery condition, and abort
//!                             hibernation if low battery is detected.
//!
//! \return a value indicating the configured low battery detection.
//
//*****************************************************************************
unsigned long
HibernateLowBatGet(void)
{
    //
    // Read the low bat bits from the control register and return those bits to
    // the caller.
    //
    return(HWREG(HIB_CTL) & HIBERNATE_LOW_BAT_ABORT);
}

//*****************************************************************************
//
//! Sets the value of the real time clock (RTC) counter.
//!
//! \param ulRTCValue is the new value for the RTC.
//!
//! Sets the value of the RTC.  The RTC will count seconds if the hardware is
//! configured correctly.  The RTC must be enabled by calling
//! HibernateRTCEnable() before calling this function.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateRTCSet(unsigned long ulRTCValue)
{
    //
    // Write the new RTC value to the RTC load register.
    //
    HWREG(HIB_RTCLD) = ulRTCValue;

    //
    // Add a delay here to enforce the required delay between write accesses to
    // certain hibernation module registers.
    //
    HibernateWriteDelay(g_ulWriteDelay);
}

//*****************************************************************************
//
//! Gets the value of the real time clock (RTC) counter.
//!
//! Gets the value of the RTC and returns it to the caller.
//!
//! \return the value of the RTC.
//
//*****************************************************************************
unsigned long
HibernateRTCGet(void)
{
    //
    // Return the value of the RTC counter register to the caller.
    //
    return(HWREG(HIB_RTCC));
}

//*****************************************************************************
//
//! Sets the value of the RTC match 0 register.
//!
//! \param ulMatch is the value for the match register.
//!
//! Sets the match 0 register for the RTC.  The hibernation module can be
//! configured to wake from hibernation, and/or generate an interrupt when the
//! value of the RTC counter is the same as the match register.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateRTCMatch0Set(unsigned long ulMatch)
{
    //
    // Write the new match value to the match register.
    //
    HWREG(HIB_RTCM0) = ulMatch;

    //
    // Add a delay here to enforce the required delay between write accesses to
    // certain hibernation module registers.
    //
    HibernateWriteDelay(g_ulWriteDelay);
}

//*****************************************************************************
//
//! Gets the value of the RTC match 0 register.
//!
//! Gets the value of the match 0 register for the RTC.
//!
//! \return the value of the match register.
//
//*****************************************************************************
unsigned long
HibernateRTCMatch0Get(void)
{
    //
    // Return the value of the match register to the caller.
    //
    return(HWREG(HIB_RTCM0));
}

//*****************************************************************************
//
//! Sets the value of the RTC match 1 register.
//!
//! \param ulMatch is the value for the match register.
//!
//! Sets the match 1 register for the RTC.  The hibernation module can be
//! configured to wake from hibernation, and/or generate an interrupt when the
//! value of the RTC counter is the same as the match register.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateRTCMatch1Set(unsigned long ulMatch)
{
    //
    // Write the new match value to the match register.
    //
    HWREG(HIB_RTCM1) = ulMatch;

    //
    // Add a delay here to enforce the required delay between write accesses to
    // certain hibernation module registers.
    //
    HibernateWriteDelay(g_ulWriteDelay);
}

//*****************************************************************************
//
//! Gets the value of the RTC match 1 register.
//!
//! Gets the value of the match 1 register for the RTC.
//!
//! \return the value of the match register.
//
//*****************************************************************************
unsigned long
HibernateRTCMatch1Get(void)
{
    //
    // Return the value of the match register to the caller.
    //
    return(HWREG(HIB_RTCM1));
}

//*****************************************************************************
//
//! Sets the value of the RTC predivider trim register.
//!
//! \param ulTrim is the new value for the pre-divider trim register.
//!
//! Sets the value of the pre-divider trim register.  The input time source is
//! divided by the pre-divider to achieve a one second clock rate.  Once every
//! 64 seconds, the value of the pre-divider trim register is applied to the
//! predivider to allow fine tuning of the RTC rate, in order to make
//! corrections to the rate.  The software application can make adjustments to
//! the predivider trim register to account for variations in the accuracy of
//! the input time source.  The nominal value is 0x7FFF, and it can be adjusted
//! up or down in order to fine tune the RTC rate.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateRTCTrimSet(unsigned long ulTrim)
{
    //
    // Check the arguments.
    //
    ASSERT(ulTrim < 0x10000);

    //
    // Write the new trim value to the trim register.
    //
    HWREG(HIB_RTCT) = ulTrim;

    //
    // Add a delay here to enforce the required delay between write accesses to
    // certain hibernation module registers.
    //
    HibernateWriteDelay(g_ulWriteDelay);
}

//*****************************************************************************
//
//! Gets the value of the RTC predivider trim register.
//!
//! Gets the value of the pre-divider trim register.  This function can be used
//! to get the current value of the trim register prior to making an adjustment
//! by using the HibernateRTCTrimSet() function.
//!
//! \return None.
//
//*****************************************************************************
unsigned long
HibernateRTCTrimGet(void)
{
    //
    // Return the value of the trim register to the caller.
    //
    return(HWREG(HIB_RTCT));
}

//*****************************************************************************
//
//! Stores data in the non-volatile memory of the hibernation module.
//!
//! \param pulData points to the data that the caller wants to store in the
//! memory of the hibernation module.
//! \param ulCount is the count of 32 bit words to store.
//!
//! Stores a set of data in the hibernation module non-volatile memory.  This
//! memory will be preserved when the power to the processor is turned off, and
//! can be used to store application state information which will be available
//! when the processor wakes.  Up to 64 32-bit words can be stored in the
//! non-volatile memory.  The data can be restored by calling the
//! HibernateDataGet() function.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateDataSet(unsigned long *pulData, unsigned long ulCount)
{
    unsigned int uIdx;

    //
    // Check the arguments.
    //
    ASSERT(ulCount <= 64);
    ASSERT(pulData != 0);

    //
    // Loop through all the words to be stored, storing one at a time.
    //
    for(uIdx = 0; uIdx < ulCount; uIdx++)
    {
        //
        // Write a word to the non-volatile storage area.
        //
        HWREG(HIB_DATA + (uIdx * 4)) = pulData[uIdx];

        //
        // Add a delay between writes to the data area.
        //
        HibernateWriteDelay(g_ulWriteDelay);
    }
}

//*****************************************************************************
//
//! Reads a set of data from the non-volatile memory of the hibernation module.
//!
//! \param pulData points to a location where the data that is read from the
//! hibernation module will be stored.
//! \param ulCount is the count of 32 bit words to read.
//!
//! Retrieves a set of data from the hibernation module non-volatile memory
//! that was previously stored with the HibernateDataSet() function.  The
//! caller must ensure that \e pulData points to a large enough memory block to
//! hold all the data that is read from the non-volatile memory.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateDataGet(unsigned long *pulData, unsigned long ulCount)
{
    unsigned int uIdx;

    //
    // Check the arguments.
    //
    ASSERT(ulCount <= 64);
    ASSERT(pulData != 0);

    //
    // Loop through all the words to be restored, reading one at a time.
    //
    for(uIdx = 0; uIdx < ulCount; uIdx++)
    {
        //
        // Read a word from the non-volatile storage area.  No delay is
        // required between reads.
        //
        pulData[uIdx] = HWREG(HIB_DATA + (uIdx * 4));
    }
}

//*****************************************************************************
//
//! Requests Hibernation mode.
//!
//! This function requests the Hibernation module to disable the external
//! regulator, thus removing power from the processor and all peripherals.  The
//! hibernation module will remain powered from the battery or auxiliary power
//! supply.
//!
//! The hibernation module will re-enable the external regulator when one of
//! the configured wake conditions occurs (such as RTC match or external WAKE
//! pin).  When the power is restored the processor will go through a normal
//! power-on reset.  The processor can retrieve saved state information with
//! the HibernateDataGet() function.  Prior to calling the function to request
//! hibernation mode, the conditions for waking must have already been set by
//! using the HibernateWakeSet() function.
//!
//! Note that this function may return because some time may elapse before the
//! power is actually removed, or it may not be removed at all.  For this
//! reason the processor will continue to execute instructions for some time
//! and the caller should be prepared for this function to return.  There are
//! various reasons why the power may not be removed.  For example if the
//! HibernationLowBatSet() function was used to configure an abort if low
//! battery is detected, then the power will not be removed if the battery
//! voltage is too low.  There may be other reasons, related to the external
//! circuit design, why a request for hibernation may not actually occur.
//!
//! For all these reasons, the caller must be prepared for this function to
//! return.  The simplest way to handle it is to just enter an infinite loop
//! and wait for the power to be removed.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateRequest(void)
{
    //
    // Set the bit in the control register to cut main power to the processor.
    //
    HWREG(HIB_CTL) |= HIB_CTL_HIBREQ;
}

//*****************************************************************************
//
//! Enables interrupts for the Hibernation module.
//!
//! \param ulIntFlags is the bit mask of the interrupts to be enabled.
//!
//! Enables the specified interrupt sources from the hibernation module.
//!
//! The parameter \e ulIntFlags must be the logical OR of any combination of
//! the following:
//!
//! - HIBERNATE_INT_PIN_WAKE - wake from pin interrupt
//! - HIBERNATE_INT_LOW_BAT - low battery interrupt
//! - HIBERNATE_INT_RTC_MATCH_0 - RTC match 0 interrupt
//! - HIBERNATE_INT_RTC_MATCH_1 - RTC match 1 interrupt
//!
//! \return None.
//
//*****************************************************************************
void
HibernateIntEnable(unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(!(ulIntFlags & ~(HIBERNATE_INT_PIN_WAKE | HIBERNATE_INT_LOW_BAT |
                            HIBERNATE_INT_RTC_MATCH_0 |
                            HIBERNATE_INT_RTC_MATCH_1)));

    //
    // Set the specified interrupt mask bits.
    //
    HWREG(HIB_IM) |= ulIntFlags;
}

//*****************************************************************************
//
//! Disables interrupts for the Hibernation module.
//!
//! \param ulIntFlags is the bit mask of the interrupts to be disabled.
//!
//! Disables the specified interrupt sources from the hibernation module.
//!
//! The parameter \e ulIntFlags has the same definition as in the
//! HibernateIntEnable() function.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateIntDisable(unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(!(ulIntFlags & ~(HIBERNATE_INT_PIN_WAKE | HIBERNATE_INT_LOW_BAT |
                            HIBERNATE_INT_RTC_MATCH_0 |
                            HIBERNATE_INT_RTC_MATCH_1)));

    //
    // Clear the specified interrupt mask bits.
    //
    HWREG(HIB_IM) &= ~ulIntFlags;
}

//*****************************************************************************
//
//! Registers an interrupt handler for the hibernation module interrupt.
//!
//! \param pfnHandler points to the function to be called when a hibernation
//! interrupt occurs.
//!
//! Registers the interrupt handler in the system interrupt controller.  The
//! interrupt is enabled at the global level, but individual interrupt sources
//! must still be enabled with a call to HibernateIntEnable().
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateIntRegister(void (*pfnHandler)(void))
{
    //
    // Register the interrupt handler.
    //
    IntRegister(INT_HIBERNATE, pfnHandler);

    //
    // Enable the hibernate module interrupt.
    //
    IntEnable(INT_HIBERNATE);
}

//*****************************************************************************
//
//! Unregisters an interrupt handler for the hibernation module interrupt.
//!
//! Unregisters the interrupt handler in the system interrupt controller.  The
//! interrupt is disabled at the global level, and the interrupt handler will
//! no longer be called.
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateIntUnregister(void)
{
    //
    // Disable the hibernate interrupt.
    //
    IntDisable(INT_HIBERNATE);

    //
    // Unregister the interrupt handler.
    //
    IntUnregister(INT_HIBERNATE);
}

//*****************************************************************************
//
//! Gets the current interrupt status of the Hibernation module.
//!
//! \param bMasked is false to retrieve the raw interrupt status, and true to
//! retrieve the masked interrupt status.
//!
//! Returns the interrupt status of the hibernation module.  The caller can use
//! this to determine the cause of a hibernation interrupt.  Either the masked
//! or raw interrupt status can be returned.
//!
//! \return The interrupt status as a bit field with the values as described in
//! the HibernateIntEnable() function.
//
//*****************************************************************************
unsigned long
HibernateIntStatus(tBoolean bMasked)
{
    //
    // Read and return the hibernation module raw or masked interrupt status.
    //
    if(bMasked == true)
    {
        return(HWREG(HIB_MIS) & 0xf);
    }
    else
    {
        return(HWREG(HIB_RIS) & 0xf);
    }
}

//*****************************************************************************
//
//! Clears pending interrupts from the Hibernation module.
//!
//! \param ulIntFlags is the bit mask of the interrupts to be cleared.
//!
//! Clears the specified interrupt sources.  This must be done from within the
//! interrupt handler or else the handler will be called again upon exit.
//!
//! The parameter \e ulIntFlags has the same definition as in the
//! HibernateIntEnable() function.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateIntClear(unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(!(ulIntFlags & ~(HIBERNATE_INT_PIN_WAKE | HIBERNATE_INT_LOW_BAT |
                            HIBERNATE_INT_RTC_MATCH_0 |
                            HIBERNATE_INT_RTC_MATCH_1)));

    //
    // Write the specified interrupt bits into the interrupt clear register.
    //
    HWREG(HIB_IC) |= ulIntFlags;
}

//*****************************************************************************
//
//! Checks to see if the Hibernation module is already powered up.
//!
//! This function queries the control register to determine if the module is
//! already active.  This function can be called at a power-on reset to help
//! determine if the reset is due to a wake from hibernation or a cold start.
//! If the Hibernation module is already active, then it does not need to be
//! re-enabled and it's status can be queried immediately.
//!
//! The software application should also use the HibernateIntStatus() function
//! to read the raw interrupt status to determine the cause of the wake.  The
//! HibernateDataGet() function can be used to restore state.  These
//! combinations of functions can be used by the software to determine if the
//! processor is waking from hibernation and the appropriate action to take as
//! a result.
//!
//! \return True if the module is already active, false if not.
//
//*****************************************************************************
unsigned int
HibernateIsActive(void)
{
    //
    // Read the control register, and return true if the module is enabled.
    //
    return(HWREG(HIB_CTL) & HIB_CTL_CLK32EN ? 1 : 0);
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
