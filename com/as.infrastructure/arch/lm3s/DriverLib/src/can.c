//*****************************************************************************
//
// can.c - Driver for the CAN module.
//
// Copyright (c) 2006-2007 Luminary Micro, Inc.  All rights reserved.
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
//! \addtogroup can_api
//! @{
//
//*****************************************************************************
#include "../hw_ints.h"
#include "../hw_memmap.h"
#include "../hw_types.h"
#include "../hw_nvic.h"
#include "../hw_can.h"
#include "debug.h"
#include "sysctl.h"
#include "lm3scan.h"
#include "lm3sinterrupt.h"

//*****************************************************************************
//
// This is the maximum number that can be stored as an 11bit Message
// identifier
//
//*****************************************************************************
#define CAN_MAX_11BIT_MSG_ID    (0x7ff)

//*****************************************************************************
//
// This is used as the loop delay for accessing the CAN controller registers.
//
//*****************************************************************************
#define CAN_RW_DELAY            (5)

//*****************************************************************************
//
//! Reads a CAN controller register.
//!
//! \param ulRegAddress is the full address of the CAN register to be read.
//!
//! This function takes care of the synchronization necessary to read from a
//! CAN controller register.
//!
//! \note This function takes care of delay required to access CAN registers.
//! This delay is required when accessing CAN registers directly.
//!
//! \return The current value of the register that was requested by
//! ulRegAddress.
//
//*****************************************************************************
unsigned long
CANReadReg(unsigned long ulRegAddress)
{
    volatile int iDelay;
    unsigned long ulRetVal;
    unsigned long ulIntNumber;
    unsigned long ulReenableInts;

    //
    // Get the CAN interrupt number from the register base address.
    //
    ulIntNumber = CANGetIntNumber(ulRegAddress & 0xfffff000);

    //
    // Make sure that the CAN base address was valid.
    //
    ASSERT(ulIntNumber != (unsigned long)-1);

    //
    // Remember current state so that CAN interrupts are only re-enabled if
    // they were already enabled.
    //
    ulReenableInts = HWREG(NVIC_EN1) & (1 << (ulIntNumber - 48));

    //
    // If the CAN interrupt was enabled then disable it.
    //
    if(ulReenableInts)
    {
        IntDisable(ulIntNumber);
    }

    //
    // Trigger the inital read to the CAN controller.  The value returned at
    // this point is not valid.
    //
    HWREG(ulRegAddress);

    //
    // This delay is necessary for the CAN have the correct data on the bus.
    //
    for(iDelay = 0; iDelay < CAN_RW_DELAY; iDelay++)
    {
    }

    //
    // Do the final read that has the valid value of the register.
    //
    ulRetVal = HWREG(ulRegAddress);

    //
    // Reenable CAN interrupts if they were enabled before this call.
    //
    if(ulReenableInts)
    {
        IntEnable(ulIntNumber);
    }

    return(ulRetVal);
}

//*****************************************************************************
//
//! Writes a CAN controller register.
//!
//! \param ulRegAddress is the full address of the CAN register to be written.
//! \param ulRegValue is the value to write into the register specified by
//! ulRegAddress.
//!
//! This function takes care of the synchronization necessary to write to a
//! CAN controller register.
//!
//! \note The delays in this function are required when accessing CAN registers
//! directly.
//!
//! \return None.
//
//*****************************************************************************
void
CANWriteReg(unsigned long ulRegAddress, unsigned long ulRegValue)
{
    volatile int iDelay;

    //
    // Trigger the inital write to the CAN controller.  The value will not make
    // it out to the CAN controller for CAN_RW_DELAY cycles.
    //
    HWREG(ulRegAddress) = ulRegValue;

    //
    // Delay to allow the CAN controller to receive the new data.
    //
    for(iDelay = 0; iDelay < CAN_RW_DELAY; iDelay++)
    {
    }
}

//*****************************************************************************
//
//! This function copies data from a buffer to the CAN Data registers.
//!
//! \param pucData is a pointer to the data to be written out to the CAN
//! controller's data registers.
//! \param pulRegister is an unsigned long pointer to the first register of
//! the CAN controller's data registers.  For example in order to use the IF1
//! register set on CAN controller 0 the value would be: (CAN0_BASE
//! + CAN_O_IF1DA1).
//! \param iSize is the number of bytes to copy into the CAN controller.
//!
//! This function takes the steps necessary to copy data from a contiguous
//! buffer in memory into the non-contiguous data registers used by the CAN
//! controller. This function is rarely used outside of the CANMessageSet()
//! function.
//!
//! \return None.
//
//*****************************************************************************
void
CANWriteDataReg(unsigned char *pucData, unsigned long *pulRegister, int iSize)
{
    int iIdx;
    unsigned long ulValue;

    //
    // Loop always copies 1 or 2 bytes per iteration.
    //
    for(iIdx = 0; iIdx < iSize; )
    {

        //
        // Write out the data 16 bits at a time since this is how the
        // registers are aligned in memory.
        //
        ulValue = pucData[iIdx++];

        //
        // Only write the second byte if needed otherwise it will be zero.
        //
        if(iIdx < iSize)
        {
            ulValue |= (pucData[iIdx++] << 8);
        }
        CANWriteReg((unsigned long)(pulRegister++), ulValue);
    }
}

//*****************************************************************************
//
//! This function copies data from a buffer to the CAN Data registers.
//!
//! \param pucData is a pointer to location to store the data read from the
//! CAN controller's data registers.
//! \param pulRegister is an unsigned long pointer to the first register of
//! the CAN controller's data registers.  For example in order to use the IF1
//! register set on CAN controller 1 the value would be: (CAN0_BASE
//! + CAN_O_IF1DA1).
//! \param iSize is the number of bytes to copy from the CAN controller.
//!
//! This function takes the steps necessary to copy data to a contiguous
//! buffer in memory from the non-contiguous data registers used by the CAN
//! controller.  This function is rarely used outside of the CANMessageGet()
//! function.
//!
//! \return None.
//
//*****************************************************************************
void
CANReadDataReg(unsigned char *pucData, unsigned long *pulRegister, int iSize)
{
    int iIdx;
    unsigned long ulValue;

    //
    // Loop always copies 1 or 2 bytes per iteration.
    //
    for(iIdx = 0; iIdx < iSize; )
    {
        //
        // Read out the data 16 bits at a time since this is how the
        // registers are aligned in memory.
        //
        ulValue = CANReadReg((unsigned long)(pulRegister++));

        //
        // Store the first byte.
        //
        pucData[iIdx++] = (unsigned char)ulValue;

        //
        // Only read the second byte if needed.
        //
        if(iIdx < iSize)
        {
            pucData[iIdx++] = (unsigned char)(ulValue >> 8);
        }
    }
}

//*****************************************************************************
//
//! Initializes the CAN controller after reset.
//!
//! \param ulBase is the base address of the CAN controller.
//!
//! After reset, the CAN controller is left in the disabled state.  However,
//! the memory used for message objects contains undefined values and must
//! be cleared prior to enabling the CAN controller the first time.
//! This prevents unwanted transmission or reception of data before the message
//! objects are configured.  This function must be called before enabling the
//! controller the first time.
//!
//! \return None.
//
//*****************************************************************************
void
CANInit(unsigned long ulBase)
{
    int iMsg;

    //
    // Make sure that the address passed in is valid.
    //
    ASSERT((ulBase == CAN0_BASE) ||
           (ulBase == CAN1_BASE) ||
           (ulBase == CAN2_BASE));

    //
    // Place CAN controller in init state, regardless of previous state
    // This will put controller in idle, and allow the message object
    // RAM to be programmed.
    //
    CANWriteReg(ulBase + CAN_O_CTL, CAN_CTL_INIT);

    //
    // Wait for busy bit to clear
    //
    while(CANReadReg(ulBase + CAN_O_IF1CRQ) & CAN_IFCRQ_BUSY)
    {
    }

    //
    // Clear the message value bit in the arbitration register.
    // This indicates the message is not valid and is a "safe"
    // condition to leave the message object.  The same arb reg
    // is used to program all the message objects.
    //
    CANWriteReg(ulBase + CAN_O_IF1CMSK, CAN_IFCMSK_WRNRD | CAN_IFCMSK_ARB |
                CAN_IFCMSK_CONTROL);
    CANWriteReg(ulBase + CAN_O_IF1ARB2, 0);
    CANWriteReg(ulBase + CAN_O_IF1MCTL, 0);

    //
    // Loop through to program all 32 message objects
    //
    for(iMsg = 1; iMsg <= 32; iMsg++)
    {
        //
        // Wait for busy bit to clear
        //
        while(CANReadReg(ulBase + CAN_O_IF1CRQ) & CAN_IFCRQ_BUSY)
        {
        }

        //
        // Initiate programming the message object
        //
        CANWriteReg(ulBase + CAN_O_IF1CRQ, iMsg);
    }

    //
    // Make sure that the interrupt and new data flags are updated for the
    // message objects.
    //
    CANWriteReg(ulBase + CAN_O_IF1CMSK, CAN_IFCMSK_NEWDAT |
                CAN_IFCMSK_CLRINTPND);

    //
    // Loop through to program all 32 message objects
    //
    for(iMsg = 1; iMsg <= 32; iMsg++)
    {
        //
        // Wait for busy bit to clear.
        //
        while(CANReadReg(ulBase + CAN_O_IF1CRQ) & CAN_IFCRQ_BUSY)
        {
        }

        //
        // Initiate programming the message object
        //
        CANWriteReg(ulBase + CAN_O_IF1CRQ, iMsg);
    }

    //
    // Acknowledge any pending status interrupts.
    //
    CANReadReg(ulBase + CAN_O_STS);
}

//*****************************************************************************
//
//! Enables the CAN controller.
//!
//! \param ulBase is the base address of the CAN controller to enable.
//!
//! Enables the CAN controller for message processing.  Once enabled, the
//! controller will automatically transmit any pending frames, and process
//! any received frames.  The controller can be stopped by calling
//! CANDisable().  Prior to calling CANEnable(), CANInit() should have been
//! called to initialize the controller and the CAN bus clock should be
//! configured by calling CANSetBitTiming().
//!
//! \return None.
//
//*****************************************************************************
void
CANEnable(unsigned long ulBase)
{
    //
    // Make sure that the address passed in is valid.
    //
    ASSERT((ulBase == CAN0_BASE) ||
           (ulBase == CAN1_BASE) ||
           (ulBase == CAN2_BASE));

    //
    // Clear the init bit in the control register.
    //
    CANWriteReg(ulBase + CAN_O_CTL,
                CANReadReg(ulBase + CAN_O_CTL) & ~CAN_CTL_INIT);
}

//*****************************************************************************
//
//! Disables the CAN controller.
//!
//! \param ulBase is the base address of the CAN controller to disable.
//!
//! Disables the CAN controller for message processing.  When disabled, the
//! controller will no longer automatically process data on the CAN bus.
//! The controller can be restarted by calling CANEnable().  The state of the
//! CAN controller and the message objects in the controller are left as they
//! were before this call was made.
//!
//! \return None.
//
//*****************************************************************************
void
CANDisable(unsigned long ulBase)
{
    //
    // Make sure that the address passed in is valid.
    //
    ASSERT((ulBase == CAN0_BASE) ||
           (ulBase == CAN1_BASE) ||
           (ulBase == CAN2_BASE));

    //
    // Set the init bit in the control register.
    //
    CANWriteReg(ulBase + CAN_O_CTL,
                CANReadReg(ulBase + CAN_O_CTL) | CAN_CTL_INIT);
}

//*****************************************************************************
//
//! Reads the current settings for the CAN controller bit timing.
//!
//! \param ulBase is the base address of the CAN controller.
//! \param pClkParms is a pointer to a structure to hold the timing parameters.
//!
//! This function reads the current configuration of the CAN controller bit
//! clock timing, and stores the resulting information in the structure
//! supplied by the caller.  Refer to CANSetBitTiming() for the meaning of the
//! values that are returned in the structure pointed to by \e pClkParms.
//!
//! \return None.
//
//*****************************************************************************
void
CANGetBitTiming(unsigned long ulBase, tCANBitClkParms *pClkParms)
{
    unsigned int uBitReg;

    //
    // Make sure that the address passed in is valid and the pointer is not
    // NULL.
    //
    ASSERT((ulBase == CAN0_BASE) ||
           (ulBase == CAN1_BASE) ||
           (ulBase == CAN2_BASE));
    ASSERT(pClkParms != 0);

    //
    // Read out all the bit timing values from the CAN controller registers.
    //
    uBitReg = CANReadReg(ulBase + CAN_O_BIT);

    //
    // Set the phase 2 segment.
    //
    pClkParms->uPhase2Seg = ((uBitReg & CAN_BIT_TSEG2) >> 12) + 1;

    //
    // Set the phase 1 segment.
    //
    pClkParms->uSyncPropPhase1Seg = ((uBitReg & CAN_BIT_TSEG1) >> 8) + 1;

    //
    // Set the sychronous jump width.
    //
    pClkParms->uSJW = ((uBitReg & CAN_BIT_SJW) >> 6) + 1;

    //
    // Set the pre-divider for the CAN bus bit clock.
    //
    pClkParms->uQuantumPrescaler =
        ((uBitReg & CAN_BIT_BRP) |
        ((CANReadReg(ulBase + CAN_O_BRPE) & CAN_BRPE_BRPE) << 6)) + 1;
}

//*****************************************************************************
//
//! Configures the CAN controller bit timing.
//!
//! \param ulBase is the base address of the CAN controller.
//! \param pClkParms points to the structure with the clock parameters
//!
//! Configures the various timing parameters for the CAN bus bit timing:
//! Propagation segment, Phase Buffer 1 segment, Phase Buffer 2 segment, and
//! the Synchronization Jump Width.  The values for Propagation and Phase
//! Buffer 1 segments are derived from the combination parameter
//! \e pClkParms->uSyncPropPhase1Seg.  Phase Buffer 2 is determined from the
//! parameter \e pClkParms->uPhase2Seg.  These two parameters, along with
//! \e pClkParms->uSJW are based in units of bit time quanta.
//! The actual quantum time is determined by the
//! \e pClkParms->uQuantumPrescaler value, which specifies what the divisor for
//! the CAN module clock.
//!
//! The total bit time, in quanta, will be the sum of the two Seg
//! parameters, as follows:
//!
//! bit_time_q = uSyncPropPhase1Seg + uPhase2Seg + 1
//!
//! Note that the Sync_Seg is always one quantum in duration, and will be
//! added to derive the correct duration of Prop_Seg and Phase1_Seg.
//!
//! The equation to determine the actual bit rate is as follows:
//!
//! CAN Clock /
//! ((\e uSyncPropPhase1Seg + \e uPhase2Seg + 1)*(\e uQuantumPrescaler))
//!
//! This means that with \e uSyncPropPhase1Seg = 4, \e uPhase2Seg = 1,
//! \e uQuantumPrescaler = 2 and a 8MHz CAN clock, that the bit rate will be
//! (8MHz)/((5 + 2 + 1)*2) or 500 KBit/sec.
//!
//! \return None.
//
//*****************************************************************************
void
CANSetBitTiming(unsigned long ulBase, tCANBitClkParms *pClkParms)
{
    unsigned int uBitReg;
    unsigned int uSavedInit;

    //
    // Make sure that the address passed in is valid and the pClkParms is not
    // NULL.
    //
    ASSERT((ulBase == CAN0_BASE) ||
           (ulBase == CAN1_BASE) ||
           (ulBase == CAN2_BASE));
    ASSERT(pClkParms != 0);

    //
    // The phase 1 segment must be in the range from 2 to 16.
    //
    ASSERT((pClkParms->uSyncPropPhase1Seg >= 2) &&
           (pClkParms->uSyncPropPhase1Seg <= 16));

    //
    // The phase 2 segment must be in the range from 1 to 8.
    //
    ASSERT((pClkParms->uPhase2Seg >= 1) && (pClkParms->uPhase2Seg <= 8));

    //
    // The synchronous jump windows must be in the range from 1 to 4.
    //
    ASSERT((pClkParms->uSJW >= 1) && (pClkParms->uSJW <= 4));

    //
    // The CAN clock pre-divider must be in the range from 1 to 1024.
    //
    ASSERT((pClkParms->uQuantumPrescaler <= 1024) &&
           (pClkParms->uQuantumPrescaler >= 1));

    //
    // To set the bit timing register, the controller must be placed
    // in init mode (if not already), and also configuration change
    // bit enabled.  State of the init bit should be saved so it can
    // be restored at the end.
    //
    uSavedInit = CANReadReg(ulBase + CAN_O_CTL);
    CANWriteReg(ulBase + CAN_O_CTL, uSavedInit | CAN_CTL_INIT | CAN_CTL_CCE);

    //
    // Set the bit fields of the bit timing register according to the parms
    //
    uBitReg = ((pClkParms->uPhase2Seg - 1) << 12) & CAN_BIT_TSEG2;
    uBitReg |= ((pClkParms->uSyncPropPhase1Seg - 1) << 8) & CAN_BIT_TSEG1;
    uBitReg |= ((pClkParms->uSJW - 1) << 6) & CAN_BIT_SJW;
    uBitReg |= (pClkParms->uQuantumPrescaler - 1) & CAN_BIT_BRP;
    CANWriteReg(ulBase + CAN_O_BIT, uBitReg);

    //
    // Set the divider upper bits in the extension register
    //
    CANWriteReg(ulBase + CAN_O_BRPE,
                ((pClkParms->uQuantumPrescaler - 1) >> 6) & CAN_BRPE_BRPE);
    //
    // Clear the config change bit, and restore the init bit
    //
    uSavedInit &= ~CAN_CTL_CCE;

    //
    // If Init was not set before, then clear it.
    //
    if(uSavedInit & CAN_CTL_INIT)
    {
        uSavedInit &= ~CAN_CTL_INIT;
    }
    CANWriteReg(ulBase + CAN_O_CTL, uSavedInit);
}

//*****************************************************************************
//
//! Returns the CAN controller interrupt number.
//!
//! \param ulBase is the base address of the selected CAN controller
//!
//! Given a CAN controller base address, returns the corresponding interrupt
//! number.
//!
//! \return Returns a CAN interrupt number, or -1 if \e ulPort is invalid.
//
//*****************************************************************************
long
CANGetIntNumber(unsigned long ulBase)
{
    long lIntNumber;

    //
    // Return the interrupt number for the given CAN controller.
    //
    switch(ulBase)
    {
        //
        // Return the interrupt number for CAN 0
        //
        case CAN0_BASE:
        {
            lIntNumber = INT_CAN0;
            break;
        }

        //
        // Return the interrupt number for CAN 1
        //
        case CAN1_BASE:
        {
            lIntNumber = INT_CAN1;
            break;
        }

        //
        // Return the interrupt number for CAN 2
        //
        case CAN2_BASE:
        {
            lIntNumber = INT_CAN2;
            break;
        }

        //
        // Return -1 to indicate a bad address was passed in.
        //
        default:
        {
            lIntNumber = -1;
        }
    }
    return(lIntNumber);
}

//*****************************************************************************
//
//! Registers an interrupt handler for the CAN controller.
//!
//! \param ulBase is the base address of the CAN controller.
//! \param pfnHandler is a pointer to the function to be called when the
//! enabled CAN interrupts occur.
//!
//! This function registers the interrupt handler in the interrupt vector
//! table, and enables CAN interrupts on the interrupt controller; specific
//! CAN interrupt sources must be enabled using CANIntEnable().  The
//! interrupt handler being registered must clear the source of the interrupt
//! using CANIntClear();
//!
//! If the application is using a static interrupt vector table stored
//! in flash, then it is not necessary to register the interrupt handler
//! this way.  Instead, IntEnable() should be used to enable CAN interrupts
//! on the interrupt controller.
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
CANIntRegister(unsigned long ulBase, void (*pfnHandler)(void))
{
    unsigned long ulIntNumber;

    //
    // Make sure that the address passed in is valid.
    //
    ASSERT((ulBase == CAN0_BASE) ||
           (ulBase == CAN1_BASE) ||
           (ulBase == CAN2_BASE));

    //
    // Get the actual interrupt number for this CAN controller.
    //
    ulIntNumber = CANGetIntNumber(ulBase);

    //
    // Register the interrupt handler.
    //
    IntRegister(ulIntNumber, pfnHandler);

    //
    // Enable the Ethernet interrupt.
    //
    IntEnable(ulIntNumber);
}

//*****************************************************************************
//
//! Unregisters an interrupt handler for the CAN controller.
//!
//! \param ulBase is the base address of the controller.
//!
//! This function unregisters the previously registered interrupt handler
//! and disables the interrupt on the interrupt controller.
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
CANIntUnregister(unsigned long ulBase)
{
    unsigned long ulIntNumber;

    //
    // Check the arguments.
    //
    ASSERT((ulBase == CAN0_BASE) ||
           (ulBase == CAN1_BASE) ||
           (ulBase == CAN2_BASE));

    //
    // Get the actual interrupt number for this CAN controller.
    //
    ulIntNumber = CANGetIntNumber(ulBase);

    //
    // Register the interrupt handler.
    //
    IntUnregister(ulIntNumber);

    //
    // Disable the CAN interrupt.
    //
    IntDisable(ulIntNumber);
}

//*****************************************************************************
//
//! Enables individual CAN controller interrupt sources.
//!
//! \param ulBase is the base address of the CAN controller.
//! \param ulIntFlags is the bit mask of the interrupt sources to be enabled.
//!
//! Enables specific interrupt sources of the CAN controller.  Only enabled
//! sources will cause a processor interrupt.
//!
//! The parameter \e ulIntFlags is the logical OR of any of the following:
//!
//! - CAN_INT_ERROR - controller error condition has occurred
//! - CAN_INT_STATUS - a message transfer completed, or bus error detected
//! - CAN_INT_MASTER - allow CAN controller to generate interrupts
//!
//! In order to generate any interrupts, CAN_INT_MASTER must be enabled.
//! Further, for any particular transaction from a message object to
//! generate an interrupt, that message object must have interrupts enabled
//! (see CANMessageSet()).  CAN_INT_ERROR will generate an interrupt if the
//! controller enters the "bus off" condition, or if the error counters reach a
//! limit.  CAN_INT_STATUS will generate an interrupt under quite a few status
//! conditions and may provide more interrupts than the application needs to
//! handle.  When an interrupt occurs, use CANIntStatus() to determine the
//! cause.
//!
//! \return None.
//
//*****************************************************************************
void
CANIntEnable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == CAN0_BASE) ||
           (ulBase == CAN1_BASE) ||
           (ulBase == CAN2_BASE));
    ASSERT((ulIntFlags & ~(CAN_CTL_EIE | CAN_CTL_SIE | CAN_CTL_IE)) == 0);

    //
    // Enable the specified interrupts.
    //
    CANWriteReg(ulBase + CAN_O_CTL,
                CANReadReg(ulBase + CAN_O_CTL) | ulIntFlags);
}

//*****************************************************************************
//
//! Disables individual CAN controller interrupt sources.
//!
//! \param ulBase is the base address of the CAN controller.
//! \param ulIntFlags is the bit mask of the interrupt sources to be disabled.
//!
//! Disables the specified CAN controller interrupt sources.  Only enabled
//! interrupt sources can cause a processor interrupt.
//!
//! The parameter \e ulIntFlags has the same definition as in the function
//! CANIntEnable().
//!
//! \return None.
//
//*****************************************************************************
void
CANIntDisable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == CAN0_BASE) ||
           (ulBase == CAN1_BASE) ||
           (ulBase == CAN2_BASE));
    ASSERT((ulIntFlags & ~(CAN_CTL_EIE | CAN_CTL_SIE | CAN_CTL_IE)) == 0);

    //
    // Disable the specified interrupts.
    //
    CANWriteReg(ulBase + CAN_O_CTL,
                CANReadReg(ulBase + CAN_O_CTL) & ~(ulIntFlags));
}

//*****************************************************************************
//
//! Returns the current CAN controller interrupt status.
//!
//! \param ulBase is the base address of the CAN controller.
//! \param eIntStsReg indicates which interrupt status register to read
//!
//! Returns the value of one of two interrupt status registers.  The
//! interrupt status register read is determined by the parameter
//! \e eIntStsReg, which can have one of the following values:
//! - CAN_INT_STS_CAUSE - indicates the cause of the interrupt
//! - CAN_INT_STS_OBJECT - indicates pending interrupts of all message objects
//!
//! CAN_INT_STS_CAUSE returns the value of the controller interrupt register
//! and indicates the cause of the interrupt.  It will be a value of
//! CAN_INT_INTID_STATUS if the cause is a status interrupt.  In this case,
//! the status register should be read with the CANStatusGet() function.
//! Calling this function to read the status will also clear the status
//! interrupt.  If the value of the interrupt register is in the range 1-32,
//! then this indicates the number of the highest priority message object that
//! has an interrupt pending. The message object interrupt can be cleared by
//! using the CANIntClear() function, or by reading the message using
//! CANMessageGet() in the case of a received message.  The interrupt handler
//! can read the interrupt status again to make sure all pending interrupts are
//! cleared before returning from the interrupt.
//!
//! CAN_INT_STS_OBJECT returns a bit mask indicating which message objects
//! have pending interrupts.  This can be used to discover all of the
//! pending interrupts at once, as opposed to repeatedly reading the interrupt
//! register by using CAN_INT_STS_CAUSE.
//!
//! \return The value of one of the interrupt status registers.
//
//*****************************************************************************
unsigned long
CANIntStatus(unsigned long ulBase, tCANIntStsReg eIntStsReg)
{
    unsigned long ulStatus;

    //
    // Check the arguments.
    //
    ASSERT((ulBase == CAN0_BASE) ||
           (ulBase == CAN1_BASE) ||
           (ulBase == CAN2_BASE));

    //
    // See which status the caller is looking for.
    //
    switch(eIntStsReg)
    {
        //
        // The caller wants the global interrupt status for the CAN controller
        // specified by ulBase.
        //
        case CAN_INT_STS_CAUSE:
        {
            ulStatus = CANReadReg(ulBase + CAN_O_INT);
            break;
        }

        //
        // The caller wants the current message status interrupt for all
        // messages.
        //
        case CAN_INT_STS_OBJECT:
        {
            //
            // Read and combine both 16 bit values into one 32bit status.
            //
            ulStatus = (CANReadReg(ulBase + CAN_O_MSGINT1) &
                        CAN_MSGINT1_INTPND);
            ulStatus |= (CANReadReg(ulBase + CAN_O_MSGINT2) << 16);
            break;
        }

        //
        // Request was for unknown status so just return 0.
        //
        default:
        {
            ulStatus = 0;
            break;
        }
    }
    //
    // Return the interrupt status value
    //
    return(ulStatus);
}

//*****************************************************************************
//
//! This call is used to clears a CAN interrupt source.
//!
//! \param ulBase is the base address of the CAN controller.
//! \param ulIntClr is a value indicating which interrupt source to clear
//!
//! This function can be used to clear a specific interrupt source.  The
//! parameter \e ulIntClr should be one of the following values:
//! - CAN_INT_INTID_STATUS - Clears a status interrupt.
//! - 1-32 - Clear the specified message object interrupt
//!
//! It is not necessary to use this function to clear an interrupt.  This
//! should only be used if the application wants to clear an interrupt source
//! without taking the normal interrupt action.
//!
//! Normally, the status interrupt is cleared by reading the controller status,
//! by calling CANStatusGet().  A specific message object interrupt is normally
//! cleared by reading the message object (see CANMessageGet()).
//!
//! \return None.
//
//*****************************************************************************
void
CANIntClear(unsigned long ulBase, unsigned long ulIntClr)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == CAN0_BASE) ||
           (ulBase == CAN1_BASE) ||
           (ulBase == CAN2_BASE));
    ASSERT((ulIntClr == CAN_INT_INTID_STATUS) ||
           ((ulIntClr>=1) && (ulIntClr <=32)));

    if(ulIntClr == CAN_INT_INTID_STATUS)
    {
        //
        // Simply read and discard the status to clear the interrupt.
        //
        CANReadReg(ulBase + CAN_O_STS);
    }
    else
    {
        //
        // Wait to be sure that this interface is not busy.
        //
        while(CANReadReg(ulBase + CAN_O_IF1CRQ) & CAN_IFCRQ_BUSY)
        {
        }

        //
        // Only change the interrupt pending state by setting only the
        // CAN_IFCMSK_CLRINTPND bit.
        //
        CANWriteReg(ulBase + CAN_O_IF1CMSK, CAN_IFCMSK_CLRINTPND);

        //
        // Send the clear pending interrupt command to the CAN controller.
        //
        CANWriteReg(ulBase + CAN_O_IF1CRQ, ulIntClr & CAN_IFCRQ_MNUM_MSK);

        //
        // Wait to be sure that this interface is not busy.
        //
        while(CANReadReg(ulBase + CAN_O_IF1CRQ) & CAN_IFCRQ_BUSY)
        {
        }
    }
}

//*****************************************************************************
//
//! Sets the CAN controller auto-retransmission behavior.
//!
//! \param ulBase is the base address of the CAN controller.
//! \param bAutoRetry enables auto-retransmission
//!
//! Enables or disables automatic retransmission of messages with detected
//! errors.  If \e bAutoRetry is \b true, then auto-retransmission is enabled,
//! otherwise it is disabled.
//!
//! \return None.
//
//*****************************************************************************
void
CANRetrySet(unsigned long ulBase, tBoolean bAutoRetry)
{
    unsigned long ulCtlReg;

    //
    // Check the arguments.
    //
    ASSERT((ulBase == CAN0_BASE) ||
           (ulBase == CAN1_BASE) ||
           (ulBase == CAN2_BASE));

    ulCtlReg = CANReadReg(ulBase + CAN_O_CTL);

    //
    // Conditionally set the DAR bit to enable/disable auto-retry.
    //
    if(bAutoRetry)
    {
        //
        // Clearing the DAR bit tells the controller to not disable the
        // auto-retry of messages which were not transmited or received
        // correctly.
        //
        ulCtlReg &= ~CAN_CTL_DAR;
    }
    else
    {
        //
        // Setting the DAR bit tells the controller to disable the auto-retry
        // of messages which were not transmited or received correctly.
        //
        ulCtlReg |= CAN_CTL_DAR;
    }

    CANWriteReg(ulBase + CAN_O_CTL, ulCtlReg);
}

//*****************************************************************************
//
//! Returns the current setting for auto-retransmission.
//!
//! \param ulBase is the base address of the CAN controller.
//!
//! Reads the current setting of the auto-retransmission setting in the CAN
//! controller and returns it to the caller.
//!
//! \return \b true if automatic retransmission is enabled, \b false otherwise.
//
//*****************************************************************************
tBoolean
CANRetryGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == CAN0_BASE) ||
           (ulBase == CAN1_BASE) ||
           (ulBase == CAN2_BASE));

    //
    // Read the disable automatic retry setting from the CAN controller.
    //
    if(CANReadReg(ulBase + CAN_O_CTL) & CAN_CTL_DAR)
    {
        //
        // Automatic data retransmission is not enabled.
        //
        return(false);
    }

    //
    // Automatic data retransmission is enabled.
    //
    return(true);
}

//*****************************************************************************
//
//! Reads one of the controller status registers.
//!
//! \param ulBase is the base address of the CAN controller.
//! \param eStatusReg is the status register to read
//!
//! Reads a status register of the CAN controller and returns it to the
//! caller.  The different status registers are:
//!
//! - CAN_STS_CONTROL - the main controller status
//! - CAN_STS_TXREQUEST - bit mask of objects pending transmission
//! - CAN_STS_NEWDAT - bit mask of objects with new data
//! - CAN_STS_MSGVAL - bit mask of objects with valid configuration
//!
//! When reading the main controller status register, a pending status
//! interrupt will be cleared.  This should be used in the interrupt handler
//! for the CAN controller if the cause is a status interrupt.  The fields of
//! controller status register are as follows:
//!
//! - CAN_STS_BOFF - controller is in bus-off condition
//! - CAN_STS_EWARN - an error counter has reached a limit of at least 96
//! - CAN_STS_EPASS - CAN controller is in the error passive state
//! - CAN_STS_RXOK - a message was received successfully (independent of
//! any message filtering.
//! - CAN_STS_TXOK - a message was successfully transmitted
//! - CAN_STS_LEC_MSK - mask of last error code bits (3 bits)
//! - CAN_STS_LEC_NONE - no error
//! - CAN_STS_LEC_STUFF - stuffing error detected
//! - CAN_STS_LEC_FORM - a format error in the fixed format part of a message
//! - CAN_STS_LEC_ACK - a transmitted message was not acknowledged
//! - CAN_STS_LEC_BIT1 - dominant level detected when trying to send recessive
//! - CAN_STS_LEC_BIT0 - recessive level detected when trying to send dominant
//! - CAN_STS_LEC_CRC - CRC error in received message
//!
//! The remaining status registers are 32-bit bit maps to the message
//! objects. They can be used to quickly obtain information about the status
//! of all the message object without needing to query each one.  They contain
//! the following information:
//!
//! - CAN_STS_TXREQUEST - if a message object's TxRequest bit is set, that
//! means that a transmission is pending on that object.  The application
//! can use this to determine which objects are still waiting to send a
//! message.
//! - CAN_STS_NEWDAT - if a message object's NewDat bit is set, that means
//! that a new message has been received in that object, and has not yet
//! been picked up by the host application
//! - CAN_STS_MSGVAL - if a message object's MsgVal bit is set, that means
//! it has a valid configuration programmed.  The host application can use
//! this to determine which message objects are empty/unused.
//!
//! \return The value of the status register.
//
//*****************************************************************************
unsigned long
CANStatusGet(unsigned long ulBase, tCANStsReg eStatusReg)
{
    unsigned long ulStatus;

    //
    // Check the arguments.
    //
    ASSERT((ulBase == CAN0_BASE) ||
           (ulBase == CAN1_BASE) ||
           (ulBase == CAN2_BASE));

    switch (eStatusReg)
    {
        //
        // Just return the global CAN status register since that is what was
        // requested.
        //
        case CAN_STS_CONTROL:
        {
            ulStatus = CANReadReg(ulBase + CAN_O_STS);
            CANWriteReg(
                ulBase + CAN_O_STS,
                ~(CAN_STS_RXOK | CAN_STS_TXOK | CAN_STS_LEC_MSK));
            break;
        }

        //
        // Combine the Transmit status bits into one 32bit value.
        //
        case CAN_STS_TXREQUEST:
        {
            ulStatus = CANReadReg(ulBase + CAN_O_TXRQ1);
            ulStatus |= CANReadReg(ulBase + CAN_O_TXRQ2) << 16;
            break;
        }

        //
        // Combine the New Data status bits into one 32bit value.
        //
        case CAN_STS_NEWDAT:
        {
            ulStatus = CANReadReg(ulBase + CAN_O_NWDA1);
            ulStatus |= CANReadReg(ulBase + CAN_O_NWDA2) << 16;
            break;
        }

        //
        // Combine the Message valid status bits into one 32bit value.
        //
        case CAN_STS_MSGVAL:
        {
            ulStatus = CANReadReg(ulBase + CAN_O_MSGVAL1);
            ulStatus |= CANReadReg(ulBase + CAN_O_MSGVAL2) << 16;
            break;
        }

        //
        // Unknown CAN status requested so return 0.
        //
        default:
        {
            ulStatus = 0;
            break;
        }
    }
    return(ulStatus);
}

//*****************************************************************************
//
//! Reads the CAN controller error counter register.
//!
//! \param ulBase is the base address of the CAN controller.
//! \param pulRxCount is a pointer to storage for the receive error counter.
//! \param pulTxCount is a pointer to storage for the transmit error counter.
//!
//! Reads the error counter register and returns the transmit and receive
//! error counts to the caller along with a flag indicating if the controller
//! receive counter has reached the error passive limit.
//! The values of the receive and transmit error counters are returned through
//! the pointers provided as parameters.
//!
//! After this call, \e *pulRxCount will hold the current receive error count
//! and \e *pulTxCount will hold the current transmit error count.
//!
//! \return
//! - \b true if the receive error count has reached the error passive limit.
//! - \b false if the error count is below the error passive limit.
//
//*****************************************************************************
tBoolean
CANErrCntrGet(unsigned long ulBase, unsigned long *pulRxCount,
              unsigned long *pulTxCount)
{
    unsigned long ulCANError;

    //
    // Check the arguments.
    //
    ASSERT((ulBase == CAN0_BASE) ||
           (ulBase == CAN1_BASE) ||
           (ulBase == CAN2_BASE));

    //
    // Read the current count of transmit/receive errors.
    //
    ulCANError = CANReadReg(ulBase + CAN_O_ERR);

    //
    // Extract the error numbers from the register value.
    //
    *pulRxCount = (ulCANError & CAN_ERR_REC_MASK) >> CAN_ERR_REC_SHIFT;
    *pulTxCount = (ulCANError & CAN_ERR_TEC_MASK) >> CAN_ERR_TEC_SHIFT;

    if(ulCANError & CAN_ERR_RP)
    {
        return(true);
    }
    return(false);
}

//*****************************************************************************
//
//! Configures a message object in the CAN controller.
//!
//! \param ulBase is the base address of the CAN controller.
//! \param ulObjID is the object number to configure (1-32)
//! \param pMsgObject is a pointer to a structure containing message object
//! settings.
//! \param eMsgType Indicates what type of message this object is.
//!
//! This function is used to configure any one of the 32 message objects in the
//! CAN controller.  A message object can be configured as any type of CAN
//! message object as well as several options for automatic transmission and
//! reception.  This call also allows the message object to be configured to
//! generate interrupts on completion of message receipt or transmission.  The
//! message object can also be configured with a filter/mask so that actions
//! are only taken when a message that meets certain parameters is seen on the
//! CAN bus.
//!
//! The \e eMsgType parameter must be one of the following values:
//!
//! - MSG_OBJ_TYPE_TX - CAN transmit message object.
//! - MSG_OBJ_TYPE_TX_REMOTE - CAN transmit remote request message
//! object.
//! - MSG_OBJ_TYPE_RX - CAN receive message object.
//! - MSG_OBJ_TYPE_RX_REMOTE - CAN receive remote request message object.
//! - MSG_OBJ_TYPE_RXTX_REMOTE - CAN remote frame receive remote, then
//! transmit message object.
//!
//! The message object pointed to by \e pMsgObject must be populated by the
//! caller, as follows:
//!
//! - \e ulMsgID - contains the message ID, either 11 or 29 bits.
//! - \e ulMsgIDMask - mask of bits from \e ulMsgID that must match if
//! identifier filtering is enabled.
//! - \e ulFlags
//!   - Set MSG_OBJ_TX_INT_ENABLE flag to enable interrupt on transmission.
//!   - Set MSG_OBJ_RX_INT_ENABLE flag to enable interrupt on receipt.
//!   - Set MSG_OBJ_USE_ID_FILTER flag to enable filtering based on the
//!   identifier mask specified by \e ulMsgIDMask.
//! - \e ulMsgLen - the number of bytes in the message data.  This should be
//! non-zero even for a remote frame - it should match the expected bytes of
//! the data responding data frame.
//! - \e pucMsgData - points to a buffer containing up to 8 bytes of data
//! for a data frame
//!
//! To send a data frame or remote frame directly, take the following steps:
//!
//! - set \e tMsgObjType to MSG_OBJ_TYPE_TX.
//! - set \e ulMsgID to the message ID.
//! - set \e ulFlags Set MSG_OBJ_TX_INT_ENABLE to to get an interrupt when the
//! message is sent. To disable filtering based on message identifiers, do not
//! set MSG_OBJ_USE_ID_FILTER.
//! - set \e ulMsgLen to the number of bytes in the data frame.
//! - set \e pucMsgData to point to an array containing the bytes in the
//! message (if a data frame, n/a if remote frame, though it is a good
//! idea to set this to point to a valid buffer).
//! - call this function with \e ulObjID set to one of the 32 object buffers.
//!
//! To receive a specific data frame, take the following steps:
//!
//! - set \e tMsgObjType to MSG_OBJ_TYPE_RX.
//! - set \e ulMsgID to the full message ID, or a partial mask to use partial
//! ID matching.
//! - set \e ulMsgIDMask bits that should be used for masking during
//! comparison.
//! - \e ulFlags
//!   - Set MSG_OBJ_TX_INT_ENABLE flag to be interrupted when the data frame is
//!   received.
//!   - Set MSG_OBJ_USE_ID_FILTER flag to enable identifier based filtering.
//! - set \e ulMsgLen to the number of bytes in the expected data frame
//! - the buffer pointed to by \e pucMsgData is not used for this call
//! - call this function with \e ulObjID set to one of the 32 object buffers
//!
//! If you specify a message object buffer that already contains a message
//! definition, it will be overwritten.
//!
//! \return None.
//
//*****************************************************************************
void
CANMessageSet(unsigned long ulBase, unsigned long ulObjID,
              tCANMsgObject *pMsgObject, tMsgObjType eMsgType)
{
    unsigned short usCmdMaskReg;
    unsigned short usMaskReg[2];
    unsigned short usArbReg[2];
    unsigned short usMsgCtrl;
    tBoolean bTransferData;
    tBoolean bUseExtendedID;

    bTransferData = 0;

    //
    // Check the arguments.
    //
    ASSERT((ulBase == CAN0_BASE) ||
           (ulBase == CAN1_BASE) ||
           (ulBase == CAN2_BASE));
    ASSERT((ulObjID <= 32) && (ulObjID != 0));
    ASSERT((eMsgType == MSG_OBJ_TYPE_TX) ||
           (eMsgType == MSG_OBJ_TYPE_TX_REMOTE) ||
           (eMsgType == MSG_OBJ_TYPE_RX) ||
           (eMsgType == MSG_OBJ_TYPE_RX_REMOTE) ||
           (eMsgType == MSG_OBJ_TYPE_TX_REMOTE) ||
           (eMsgType == MSG_OBJ_TYPE_RXTX_REMOTE));

    //
    // Wait for busy bit to clear
    //
    while(CANReadReg(ulBase + CAN_O_IF1CRQ) & CAN_IFCRQ_BUSY)
    {
    }

    //
    // See if we need to use an extended identifier or not.
    //
    if((pMsgObject->ulMsgID > CAN_MAX_11BIT_MSG_ID) ||
       (pMsgObject->ulFlags & MSG_OBJ_EXTENDED_ID))
    {
        bUseExtendedID = 1;
    }
    else
    {
        bUseExtendedID = 0;
    }

    //
    // This is always a write to the Message object as this call is setting
    // a message object.
    // This call will also always set all size bits so it sets both data bits.
    // The call will use the CONTROL register to set control bits so this bit
    // needs to be set as well.
    //
    usCmdMaskReg = CAN_IFCMSK_WRNRD | CAN_IFCMSK_DATAA | CAN_IFCMSK_DATAB |
        CAN_IFCMSK_CONTROL;

    //
    // Initialize the values to a known state before filling them in based
    // on the type of message object that is being configured.
    //
    usArbReg[0] = 0;
    usMsgCtrl = 0;
    usMaskReg[0] = 0;
    usMaskReg[1] = 0;

    switch(eMsgType)
    {
        //
        // Transmit message object.
        //
        case MSG_OBJ_TYPE_TX:
        {
            //
            // Set the TXRQST bit and the reset the rest of the register.
            //
            usMsgCtrl |= CAN_IFMCTL_TXRQST;
            usArbReg[1] = CAN_IFARB2_DIR;
            bTransferData = 1;
            break;
        }

        //
        // Transmit remote request message object
        //
        case MSG_OBJ_TYPE_TX_REMOTE:
        {
            //
            // Set the TXRQST bit and the reset the rest of the register.
            //
            usMsgCtrl |= CAN_IFMCTL_TXRQST;
            usArbReg[1] = 0;
            break;
        }

        //
        // Receive message object.
        //
        case MSG_OBJ_TYPE_RX:
        {
            //
            // This clears the DIR bit along with everthing else.  The
            // TXRQST bit was cleard by defaulting usMsgCtrl to 0.
            //
            usArbReg[1] = 0;
            break;
        }

        //
        // Receive remote request message object.
        //
        case MSG_OBJ_TYPE_RX_REMOTE:
        {
            //
            // The DIR bit is set to one for remote receivers.  The
            // TXRQST bit was cleard by defaulting usMsgCtrl to 0.
            //
            usArbReg[1] = CAN_IFARB2_DIR;

            //
            // Set this object so that it only indicates that a remote frame
            // was received and allow for software to handle it by sending back
            // a data frame.
            //
            usMsgCtrl = CAN_IFMCTL_UMASK;

            //
            // Use the full Identifier by default.
            //
            usMaskReg[0] = 0xffff;
            usMaskReg[1] = 0x1fff;

            //
            // Make sure to send the mask to the message object.
            //
            usCmdMaskReg |= CAN_IFCMSK_MASK;
            break;
        }

        //
        // Remote frame receive remote, with auto-transmit message object.
        //
        case MSG_OBJ_TYPE_RXTX_REMOTE:
        {
            //
            // Oddly the DIR bit is set to one for remote receivers.
            //
            usArbReg[1] = CAN_IFARB2_DIR;

            //
            // Set this object to auto answer if a matching identifier is seen.
            //
            usMsgCtrl = CAN_IFMCTL_RMTEN | CAN_IFMCTL_UMASK;

            //
            // The data to be returned needs to be filled in.
            //
            bTransferData = 1;
            break;
        }

        //
        // This case should never happen due to the ASSERT statement at the
        // beginning of this function.
        //
        default:
        {
            return;
        }
    }

    //
    // Configure the Mask Registers.
    //
    if(pMsgObject->ulFlags & MSG_OBJ_USE_ID_FILTER)
    {
        if(bUseExtendedID)
        {
            //
            // Set the 29 bits of Identifier mask that were requested.
            //
            usMaskReg[0] = pMsgObject->ulMsgIDMask & CAN_IFMSK1_MSK;
            usMaskReg[1] = (pMsgObject->ulMsgIDMask >> 16) & CAN_IFMSK2_MSK;
        }
        else
        {
            //
            // Lower 16 bit are unused so set them to zero.
            //
            usMaskReg[0] = 0;
            //
            // Put the 11 bit Mask Identifier into the upper bits of the field
            // in the register.
            //
            usMaskReg[1] = (pMsgObject->ulMsgIDMask << 2) & CAN_IFMSK2_MSK;
        }
    }

    //
    // If the caller wants to filter on the extended ID bit then set it.
    //
    if((pMsgObject->ulFlags & MSG_OBJ_USE_EXT_FILTER) ==
        MSG_OBJ_USE_EXT_FILTER)
    {
        usMaskReg[1] |= CAN_IFMSK2_MXTD;
    }

    //
    // The caller wants to filter on the message direction field.
    //
    if((pMsgObject->ulFlags & MSG_OBJ_USE_DIR_FILTER) ==
        MSG_OBJ_USE_DIR_FILTER)
    {
        usMaskReg[1] |= CAN_IFMSK2_MDIR;
    }

    if(pMsgObject->ulFlags & (MSG_OBJ_USE_ID_FILTER | MSG_OBJ_USE_DIR_FILTER |
       MSG_OBJ_USE_EXT_FILTER))
    {
        //
        // Set the UMASK bit to enable using the mask register.
        //
        usMsgCtrl |= CAN_IFMCTL_UMASK;

        //
        // Set the MASK bit so that this gets trasferred to the Message Object.
        //
        usCmdMaskReg |= CAN_IFCMSK_MASK;
    }

    //
    // Set the Arb bit so that this gets transferred to the Message object.
    //
    usCmdMaskReg |= CAN_IFCMSK_ARB;

    //
    // Configure the Arbitration registers.
    //
    if(bUseExtendedID)
    {
        //
        // Set the 29 bit version of the Identifier for this message object.
        //
        usArbReg[0] |= pMsgObject->ulMsgID & CAN_IFARB1_ID;
        usArbReg[1] |= (pMsgObject->ulMsgID >> 16) & CAN_IFARB2_ID;

        //
        // Mark the message as valid and set the extended ID bit.
        //
        usArbReg[1] |= CAN_IFARB2_MSGVAL | CAN_IFARB2_XTD;
    }
    else
    {
        //
        // Set the 11 bit version of the Identifier for this message object.
        // The lower 18 bits are set to zero.
        //
        usArbReg[1] |= (pMsgObject->ulMsgID << 2) & CAN_IFARB2_ID;

        //
        // Mark the message as valid.
        //
        usArbReg[1] |= CAN_IFARB2_MSGVAL;
    }

    //
    // Set the data length since this is set for all transfers.
    // This is also a single transfer and not a FIFO transfer so set EOB bit.
    //
    usMsgCtrl |= (pMsgObject->ulMsgLen & CAN_IFMCTL_DLC) | CAN_IFMCTL_EOB;

    //
    // Enable transmit interrupts if they should be enabled.
    //
    if(pMsgObject->ulFlags & MSG_OBJ_TX_INT_ENABLE)
    {
        usMsgCtrl |= CAN_IFMCTL_TXIE;
    }

    //
    // Enable receive interrupts if they should be enabled.
    //
    if(pMsgObject->ulFlags & MSG_OBJ_RX_INT_ENABLE)
    {
        usMsgCtrl |= CAN_IFMCTL_RXIE;
    }

    //
    // Write the data out to the CAN Data registers if needed.
    //
    if(bTransferData)
    {
        CANWriteDataReg(
            pMsgObject->pucMsgData,
            (unsigned long *)(ulBase + CAN_O_IF1DA1), pMsgObject->ulMsgLen);
    }

    //
    // Write out the registers to program the message object.
    //
    CANWriteReg(ulBase + CAN_O_IF1CMSK, usCmdMaskReg);
    CANWriteReg(ulBase + CAN_O_IF1MSK1, usMaskReg[0]);
    CANWriteReg(ulBase + CAN_O_IF1MSK2, usMaskReg[1]);
    CANWriteReg(ulBase + CAN_O_IF1ARB1, usArbReg[0]);
    CANWriteReg(ulBase + CAN_O_IF1ARB2, usArbReg[1]);
    CANWriteReg(ulBase + CAN_O_IF1MCTL, usMsgCtrl);

    //
    // Transfer the message object to the message object specifiec by ulObjID.
    //
    CANWriteReg(ulBase + CAN_O_IF1CRQ, ulObjID & CAN_IFCRQ_MNUM_MSK);

    return;
}

//*****************************************************************************
//
//! Reads a CAN message from one of the message object buffers
//!
//! \param ulBase is the base address of the CAN controller.
//! \param ulObjID is the object number to read (1-32)
//! \param pMsgObject points to a structure containing message object fields
//! \param bClrPendingInt indicates whether an associated interrupt should
//! be cleared
//!
//! This function is used to read the contents of one of the 32 message
//! objects in the CAN controller, and return it to the caller.  The data
//! returned is stored in the fields of the caller supplied structure pointed
//! to by \e pMsgObject.  The data consists of all of the parts of a CAN
//! message, plus some control and status information.
//!
//! Normally this is used to read a message object that has received and
//! stored a CAN message with a certain identifier.  However this could also be
//! used to read the contents of a message object in order to load the fields
//! of the structure in case only part of the structure needs to be changed
//! from a previous setting.
//!
//! When using CANMessageGet, all of the same fields of the structure are
//! populated in the same way as when the CANMessageSet() function is used,
//! with the following exceptions:
//!
//! \e pMsgObject->ulFlags:
//!
//! - MSG_OBJ_NEW_DATA indicates if this is new data since the last
//! time it was read
//! - MSG_OBJ_DATA_LOST indicates that at least one message was received
//! on this message object, and not read by the host before being
//! overwritten.
//!
//! \return None.
//
//*****************************************************************************
void
CANMessageGet(unsigned long ulBase, unsigned long ulObjID,
              tCANMsgObject *pMsgObject, tBoolean bClrPendingInt)
{
    unsigned short usCmdMaskReg;
    unsigned short usMaskReg[2];
    unsigned short usArbReg[2];
    unsigned short usMsgCtrl;

    //
    // Check the arguments.
    //
    ASSERT((ulBase == CAN0_BASE) ||
           (ulBase == CAN1_BASE) ||
           (ulBase == CAN2_BASE));
    ASSERT((ulObjID <= 32) && (ulObjID != 0));

    //
    // This is always a read to the Message object as this call is setting
    // a message object.
    //
    usCmdMaskReg = CAN_IFCMSK_DATAA | CAN_IFCMSK_DATAB | CAN_IFCMSK_CONTROL |
                   CAN_IFCMSK_MASK | CAN_IFCMSK_ARB;

    //
    // Clear a pending interrupt and new data in a message object.
    //
    if(bClrPendingInt)
    {
        usCmdMaskReg |= CAN_IFCMSK_CLRINTPND;
    }

    //
    // Set up the request for data from the message object.
    //
    CANWriteReg(ulBase + CAN_O_IF2CMSK, usCmdMaskReg);

    //
    // Transfer the message object to the message object specifiec by ulObjID.
    //
    CANWriteReg(ulBase + CAN_O_IF2CRQ, ulObjID & CAN_IFCRQ_MNUM_MSK);

    //
    // Wait for busy bit to clear
    //
    while(CANReadReg(ulBase + CAN_O_IF2CRQ) & CAN_IFCRQ_BUSY)
    {
    }

    //
    // Read out the IF Registers.
    //
    usMaskReg[0] = CANReadReg(ulBase + CAN_O_IF2MSK1);
    usMaskReg[1] = CANReadReg(ulBase + CAN_O_IF2MSK2);
    usArbReg[0] = CANReadReg(ulBase + CAN_O_IF2ARB1);
    usArbReg[1] = CANReadReg(ulBase + CAN_O_IF2ARB2);
    usMsgCtrl = CANReadReg(ulBase + CAN_O_IF2MCTL);

    pMsgObject->ulFlags = MSG_OBJ_NO_FLAGS;

    //
    // Determine if this is a remote frame by checking the TXRQST and DIR bits.
    //
    if((!(usMsgCtrl & CAN_IFMCTL_TXRQST) && (usArbReg[1] & CAN_IFARB2_DIR)) ||
       ((usMsgCtrl & CAN_IFMCTL_TXRQST) && (!(usArbReg[1] & CAN_IFARB2_DIR))))
    {
        pMsgObject->ulFlags |= MSG_OBJ_REMOTE_FRAME;
    }

    //
    // Get the Identifier out of the register, the format depends on size of
    // the Mask.
    //
    if(usArbReg[1] & CAN_IFARB2_XTD)
    {
        //
        // Set the 29 bit version of the Identifier for this message object.
        //
        pMsgObject->ulMsgID = ((usArbReg[1] & CAN_IFARB2_ID) << 16) |
            usArbReg[0];

        pMsgObject->ulFlags |= MSG_OBJ_EXTENDED_ID;
    }
    else
    {
        //
        // The Identifier is an 11 bit value.
        //
        pMsgObject->ulMsgID = (usArbReg[1] & CAN_IFARB2_ID) >> 2;
    }

    //
    // Indicate that we lost some data.
    //
    if(usMsgCtrl & CAN_IFMCTL_MSGLST)
    {
        pMsgObject->ulFlags |= MSG_OBJ_DATA_LOST;
    }

    //
    // Set the flag to indicate if ID masking was used.
    //
    if(usMsgCtrl & CAN_IFMCTL_UMASK)
    {
        if(usArbReg[1] & CAN_IFARB2_XTD)
        {
            //
            // The Identifier Mask is assumed to also be a 29 bit value.
            //
            pMsgObject->ulMsgIDMask =
                ((usMaskReg[1] & CAN_IFMSK2_MSK) << 16) | usMaskReg[0];
            //
            // If this is a fully specified Mask and a remote frame then don't
            // set the MSG_OBJ_USE_ID_FILTER because the ID was not really
            // filtered.
            //
            if((pMsgObject->ulMsgIDMask != 0x1fffffff) ||
               ((pMsgObject->ulFlags & MSG_OBJ_REMOTE_FRAME) == 0))
            {
                pMsgObject->ulFlags |= MSG_OBJ_USE_ID_FILTER;
            }
        }
        else
        {
            //
            // The Identifier Mask is assumed to also be an 11 bit value.
            //
            pMsgObject->ulMsgIDMask = (usMaskReg[1] & CAN_IFMSK2_MSK) >> 2;

            //
            // If this is a fully specified Mask and a remote frame then don't
            // set the MSG_OBJ_USE_ID_FILTER because the ID was not really
            // filtered.
            //
            if((pMsgObject->ulMsgIDMask != 0x7ff) ||
               ((pMsgObject->ulFlags & MSG_OBJ_REMOTE_FRAME) == 0))
            {
                pMsgObject->ulFlags |= MSG_OBJ_USE_ID_FILTER;
            }
        }

        //
        // Indicate if the extended bit was used in filtering.
        //
        if(usMaskReg[1] & CAN_IFMSK2_MXTD)
        {
            pMsgObject->ulFlags |= MSG_OBJ_USE_EXT_FILTER;
        }

        //
        // Indicate if direction filtering was enabled.
        //
        if(usMaskReg[1] & CAN_IFMSK2_MDIR)
        {
            pMsgObject->ulFlags |= MSG_OBJ_USE_DIR_FILTER;
        }
    }

    //
    // Set the interupt flags.
    //
    if(usMsgCtrl & CAN_IFMCTL_TXIE)
    {
        pMsgObject->ulFlags |= MSG_OBJ_TX_INT_ENABLE;
    }
    if(usMsgCtrl & CAN_IFMCTL_RXIE)
    {
        pMsgObject->ulFlags |= MSG_OBJ_RX_INT_ENABLE;
    }

    //
    // See if there is new data available.
    //
    if(usMsgCtrl & CAN_IFMCTL_NEWDAT)
    {
        //
        // Get the amount of data needed to be read.
        //
        pMsgObject->ulMsgLen = (usMsgCtrl & CAN_IFMCTL_DLC);

        //
        // Don't read any data for a remote frame, there is nothing valid
        // in that buffer anyway.
        //
        if((pMsgObject->ulFlags & MSG_OBJ_REMOTE_FRAME) == 0)
        {
            //
            // Read out the data from the CAN registers.
            //
            CANReadDataReg(pMsgObject->pucMsgData,
                           (unsigned long *)(ulBase + CAN_O_IF2DA1),
                           pMsgObject->ulMsgLen);
        }

        //
        // Now clear out the new data flag.
        //
        CANWriteReg(ulBase + CAN_O_IF2CMSK, CAN_IFCMSK_NEWDAT);

        //
        // Transfer the message object to the message object specifiec by
        // ulObjID.
        //
        CANWriteReg(ulBase + CAN_O_IF2CRQ, ulObjID & CAN_IFCRQ_MNUM_MSK);

        //
        // Wait for busy bit to clear
        //
        while(CANReadReg(ulBase + CAN_O_IF2CRQ) & CAN_IFCRQ_BUSY)
        {
        }

        //
        // Indicate that there is new data in this message.
        //
        pMsgObject->ulFlags |= MSG_OBJ_NEW_DATA;
    }
    else
    {
        //
        // Along with the MSG_OBJ_NEW_DATA not being set the amount of data
        // needs to be set to zero if none was available.
        //
        pMsgObject->ulMsgLen = 0;
    }
}

//*****************************************************************************
//
//! Clears a message object so that it is no longer used
//!
//! \param ulBase is the base address of the CAN controller.
//! \param ulObjID is the message object number to disable (1-32)
//!
//! This function frees the specified message object from use.  Once a
//! message object has been "cleared" it will no longer automatically
//! send or receive messages, or generate interrupts.
//!
//! \return None.
//
//*****************************************************************************
void
CANMessageClear(unsigned long ulBase, unsigned long ulObjID)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == CAN0_BASE) ||
           (ulBase == CAN1_BASE) ||
           (ulBase == CAN2_BASE));
    ASSERT((ulObjID >= 1) && (ulObjID <= 32));

    //
    // Wait for busy bit to clear
    //
    while(CANReadReg(ulBase + CAN_O_IF1CRQ) & CAN_IFCRQ_BUSY)
    {
    }

    //
    // Clear the message value bit in the arbitration register.
    // This indicates the message is not valid.
    //
    CANWriteReg(ulBase + CAN_O_IF1CMSK, CAN_IFCMSK_WRNRD | CAN_IFCMSK_ARB);
    CANWriteReg(ulBase + CAN_O_IF1ARB1, 0);
    CANWriteReg(ulBase + CAN_O_IF1ARB2, 0);

    //
    // Initiate programming the message object
    //
    CANWriteReg(ulBase + CAN_O_IF1CRQ, ulObjID & CAN_IFCRQ_MNUM_MSK);
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
