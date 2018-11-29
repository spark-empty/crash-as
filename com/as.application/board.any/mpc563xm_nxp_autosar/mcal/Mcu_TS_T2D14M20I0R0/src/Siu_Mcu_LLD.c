/**
    @file    SIU_Mcu_LLD.c
    @version 2.0.0

@brief   AUTOSAR Mcu - SIU source file support for MCU driver.
@details SIU source file, containing the variables and functions that are exported by the SIU driver

Project AUTOSAR 3.0 MCAL
Platform PA
Peripheral FMPLL
Dependencies none

ARVersion 3.0.0
ARRevision ASR_REL_3_0_REV_0003
ARConfVariant
SWVersion 2.0.0
BuildVersion XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223

(c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
All Rights Reserved.
*/
/*==================================================================================================
==================================================================================================*/

/**
@page misra_violations MISRA-C:2004 violations

@section Siu_Mcu_LLD_c_1
Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before "#include"
MemMap.h included after each section define in order to set the current memory section

@section Siu_Mcu_LLD_c_2
MISRA-C:2004  19.15 Precautions shall be taken in order to prevent the contents of a
header file being included twice.
This is not a violation since all header files are protected against multiple inclusions.

@section Siu_Mcu_LLD_c_3
MISRA-C 2004  11.1 VIOLATION, cast from unsigned long to pointer.
The cast can not be avoided as it is used to access memory mapped registers.

@section Siu_Mcu_LLD_c_4
MISRA-C 2004  12.4 VIOLATION, side effects on right hand of logical operator: '&&'
The violation is because of complex statemnt.
*/

#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
2) needed interfaces from external units
3) internal and external interfaces from this unit
==================================================================================================*/

#include "Mcu_LLD.h"

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/** @remarks Covers BSW00374, BSW00318 */
#define SIU_MCU_LLD_VENDOR_ID_C         43
#define SIU_MCU_LLD_AR_MAJOR_VERSION_C  3
#define SIU_MCU_LLD_AR_MINOR_VERSION_C  0
#define SIU_MCU_LLD_AR_PATCH_VERSION_C  0
#define SIU_MCU_LLD_SW_MAJOR_VERSION_C  2
#define SIU_MCU_LLD_SW_MINOR_VERSION_C  0
#define SIU_MCU_LLD_SW_PATCH_VERSION_C  0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and Mcu_LLD.h file are of the same vendor */
#if (SIU_MCU_LLD_VENDOR_ID_C != MCU_LLD_VENDOR_ID)
#error "SIU_Mcu_LLD.c and Mcu_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
#if ((SIU_MCU_LLD_AR_MAJOR_VERSION_C != MCU_LLD_AR_MAJOR_VERSION) || \
(SIU_MCU_LLD_AR_MINOR_VERSION_C != MCU_LLD_AR_MINOR_VERSION) || \
(SIU_MCU_LLD_AR_PATCH_VERSION_C != MCU_LLD_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of SIU_Mcu_LLD.c and Mcu_LLD.h are different"
#endif
#endif
/* Check if source file and MCU_LLD.h header file are of the same Software version */
#if ((SIU_MCU_LLD_SW_MAJOR_VERSION_C != MCU_LLD_SW_MAJOR_VERSION) || \
(SIU_MCU_LLD_SW_MINOR_VERSION_C != MCU_LLD_SW_MINOR_VERSION) || \
(SIU_MCU_LLD_SW_PATCH_VERSION_C != MCU_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of SIU_Mcu_LLD.c and Mcu_LLD.h are different"
#endif

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/
#define MCU_START_SEC_VAR_UNSPECIFIED
/** @note Violates MISRA 2004  19.1, 19.15 :Repeated include file MemMap.h,
See @ref Siu_Mcu_LLD_c_1, Siu_Mcu_LLD_c_2 above*/
/*lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

#define MCU_STOP_SEC_VAR_UNSPECIFIED
/** @note Violates MISRA 2004  19.1, 19.15 :Repeated include file MemMap.h,
See @ref Siu_Mcu_LLD_c_1, Siu_Mcu_LLD_c_2 above*/
/*lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define MCU_START_SEC_CODE
/** @note Violates MISRA 2004  19.1, 19.15 :Repeated include file MemMap.h,
See @ref Siu_Mcu_LLD_c_1, Siu_Mcu_LLD_c_2 above*/
/*lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

/**
@brief   This function retruns the reset reason.
@details The function reads the reset reason from hardware and returns the reason.

@return RawReset reset reason

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers MCU052, MCU005
@remarks Implements DMCU04000
*/
    FUNC(Mcu_ResetType, MCU_CODE) Mcu_SIU_GetResetReason(VAR(void, MCU_VAR))
    {

        VAR(Mcu_ResetType, MCU_VAR) ResetType = (Mcu_ResetType) MCU_RESET_UNDEFINED;
/* Return enumerated reset reasons as per reset status register SIU_RSR */
/*Check for Power On Reser*/
    /** @note Violates MISRA 2004  11.1 :cast from unsigned long to pointer,See @ref Siu_Mcu_LLD_c_3 above*/        
        /*lint -save -e923*/
        if ((((REG_READ32(SIU_RSR)) & SIU_RSR_PORS) == SIU_RSR_PORS))
        {
            ResetType = MCU_POWER_ON_RESET;
        }
/*Check for External Reset Status*/
        else if ((((REG_READ32(SIU_RSR)) & SIU_RSR_ERS) == SIU_RSR_ERS))
        {
            ResetType = (Mcu_ResetType) MCU_EXTERNAL_RESET;
        }
/*Check for Loss of lock Reset Status*/
        else if ((((REG_READ32(SIU_RSR)) & SIU_RSR_LLRS) == SIU_RSR_LLRS))
        {
            ResetType = (Mcu_ResetType) MCU_LOSS_OF_LOCK_RESET;
        }
/*Check for Loss of clock Reset Status*/
        else if ((((REG_READ32(SIU_RSR)) & SIU_RSR_LCRS) == SIU_RSR_LCRS))
        {
            ResetType = (Mcu_ResetType) MCU_LOSS_OF_CLOCK_RESET;
        }
/*Check for Watchdog Timer/Debug Reset  Status*/
        else if ((((REG_READ32(SIU_RSR)) & SIU_RSR_WDRS) == SIU_RSR_WDRS))
        {
            ResetType = (Mcu_ResetType) MCU_WATCHDOG_RESET;
        }
#ifdef IPV_SIU
    /* if != Andorra 4M and != Monaco 1.5M and !=MAMBA*/
    #if ((IPV_SIU != IPV_SIU_00_02_11_00) && (IPV_SIU != IPV_SIU_00_02_08_07) \
        && (IPV_SIU != IPV_SIU_00_02_07_03_3)) 
/*Check for Checkstop Reset Status*/
        else if ((((REG_READ32(SIU_RSR)) & SIU_RSR_CRS) == SIU_RSR_CRS))
        {
            ResetType = (Mcu_ResetType) MCU_CHECKSTOP_RESET;
        }
    #endif
#endif

#ifdef IPV_SIU
    #if (IPV_SIU != IPV_SIU_00_02_07_03_5) /* if != Fado */
/*Check for Platform software watch dog reset Status*/
        else if ((((REG_READ32(SIU_RSR)) & SIU_RSR_SWTRS) == SIU_RSR_SWTRS))
        {
            ResetType = (Mcu_ResetType) MCU_SW_WATCHDOG_RESET;
        }
/*Check for Software External Reset Status*/
        else if ((((REG_READ32(SIU_RSR)) & SIU_RSR_SERS) == SIU_RSR_SERS))
        {
            ResetType = (Mcu_ResetType) MCU_SW_EXT_RESET;
        }
    #endif
#endif
/*Check for Software System Reset Status*/
        else if ((((REG_READ32(SIU_RSR)) & SIU_RSR_SSRS) == SIU_RSR_SSRS))
        {
            ResetType = (Mcu_ResetType) MCU_SW_RESET;
        }
        /*lint -restore*/
        else
        {
/* Do Nothing */
        }
/* Return the Reset type */
        return ResetType;
    }

/**
@brief   This function returns the raw reset value.
@details This function reads the reset raw value from the hardware register.

@return         RawResetReg raw reset reason

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers MCU006, MCU135
@remarks Implements DMCU04000
*/
    FUNC(Mcu_RawResetType, MCU_CODE) Mcu_SIU_GetResetRawValue(VAR(void, MCU_VAR))
    {
        VAR(Mcu_RawResetType, AUTOMATIC) RawResetReg = MCU_RAW_RESET_DEFAULT;

/** @remarks Covers MCU135 */
/* Return SIU Reset Status Register (SIU_RSR). */
        /** @note Violates MISRA 2004  11.1 :cast from unsigned long to pointer,See @ref Siu_Mcu_LLD_c_3 above*/
        RawResetReg = (REG_READ32(SIU_RSR));
        return RawResetReg;
    }

/**
  @brief   This function initializes the System Clock Register
  @details The System Clock Register is initialised with the configured system clock parameters

@param[in]     ClockPtr      Pointer to clock configuration structure

@return void

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers MCU137
@remarks Implements DMCU04000
*/
    FUNC(void, MCU_CODE) Mcu_SIU_Init_SystemClock( \
        P2CONST(Mcu_ClockConfigType, AUTOMATIC, MCU_APPL_DATA) ClockPtr)
    {
/* Write the System Clock register, SIU_SYSDIV with configured system clock parameters */
        /** @note Violates MISRA 2004  11.1 :cast from unsigned long to pointer,See @ref Siu_Mcu_LLD_c_3 above*/
        REG_WRITE32(SIU_SYSDIV, (uint32)(ClockPtr->SystemClockParam));
    }

/**
   @brief   This function initializes the ExternalClock Register
   @details The ExternalClock Register is initialised with configured External Clock  parameters

@param[in]     ClockPtr      Pointer to clock configuration structure

@return void

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers MCU137
@remarks Implements DMCU04000
*/
    FUNC(void, MCU_CODE) Mcu_SIU_Init_ExternalClock( \
        P2CONST(Mcu_ClockConfigType, AUTOMATIC, MCU_APPL_DATA) ClockPtr)
    {
/* Write the External Clock Control Register ,SIU_ECCR with configured External Clock  parameters */
        /** @note Violates MISRA 2004  11.1 :cast from unsigned long to pointer,
        See @ref Siu_Mcu_LLD_c_3 above*/
        REG_WRITE32(SIU_ECCR, (uint32)(ClockPtr->ExternalClockParam));
    }

/**
@brief   This function initializes the Halt Register
@details The Halt Register is initialised with configured Halt bit  parameters

@param[in]     ModePtr      Pointer to mode configuration structure

@return void

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers MCU147
@remarks Implements DMCU04000
*/
    FUNC(void, MCU_CODE) Mcu_SIU_Init_Halt( \
        P2CONST(Mcu_ModeConfigType, AUTOMATIC, MCU_APPL_DATA) ModePtr)
    {
        VAR(uint32, AUTOMATIC) Loop = 0UL;

#ifdef IPV_SIU
    /* if Andorra 4M or Monaco 1.5M*/
    #if ((IPV_SIU == IPV_SIU_00_02_11_00) || (IPV_SIU == IPV_SIU_00_02_08_07))
       VAR(uint32, AUTOMATIC) timeout;
       timeout = 0UL;
    #endif
#endif

#ifdef IPV_SIU
    #if (IPV_SIU == IPV_SIU_00_02_07_03_5) /* if Fado */
/* Write the Halt Register, SIU_HLT with configured parameters */
        /** @note Violates MISRA 2004  11.1 :cast from unsigned long to pointer,
        See @ref Siu_Mcu_LLD_c_3 above*/
        /*lint -save -e923*/
        REG_WRITE32(SIU_HLT0, (uint32)(ModePtr->SIU_Hlt));
        REG_WRITE32(SIU_HLT1, (uint32)(ModePtr->SIU_Hlt1));
        /*lint -restore*/
    /* if Andorra 4M or Monaco 1.5M*/
    #elif ((IPV_SIU == IPV_SIU_00_02_11_00) || (IPV_SIU == IPV_SIU_00_02_08_07))
        /* Write the Halt Register, SIU_HLT with configured parameters */
        REG_WRITE32(SIU_HLT, (uint32)(ModePtr->SIU_Hlt));
    #if (MCU_ENTER_LOW_POWER_MODE == STD_ON)
        if( (REG_READ32(SIU_HLT) & (uint32)MCU_HALT_CPU_AND_PLATFORM_CLOCK) == \
            (uint32)MCU_HALT_CPU_AND_PLATFORM_CLOCK)
        {
            EXECUTE_WAIT();
            /* before returning, wait for HLTACK signal */
            while (timeout < (ModePtr->HLTACKTimeOut)){
                timeout++;
                /* HLT bit is set  */
                if( (REG_READ32(SIU_HLT) & MCU_HALT_CPU_AND_PLATFORM_CLOCK) ==  \
                       (uint32)MCU_HALT_CPU_AND_PLATFORM_CLOCK){
                    break;
                }
            }
        }
    #endif
    #else /* Mamba */
        /* Write the Halt Register, SIU_HLT with configured parameters */
        /** @note Violates MISRA 2004  11.1 :cast from unsigned long to pointer,
                     See @ref Siu_Mcu_LLD_c_3 above*/
        REG_WRITE32(SIU_HLT, (uint32)(ModePtr->SIU_Hlt));
    #endif
#endif
        do
        {
            if (Loop > ModePtr->HLTACKTimeOut)
            {
/* the user can configure the timeout to allow acknowledge in the SIU_HLTACK register*/
                break;
            }
            Loop++;
        }

#ifdef IPV_SIU
    #if (IPV_SIU == IPV_SIU_00_02_07_03_5) /* if Fado */
        /** @note MISRA-C:2004 11.1, 12.4: cast from unsigned long to pointer,side effects on right hand of 
        logical operator,Refer to Siu_Mcu_LLD_c_3, Siu_Mcu_LLD_c_4 above*/
        /*lint -save -e923, -e960*/
        while ((((uint32)REG_READ32(SIU_HLTACK0) & (uint32)(ModePtr->SIU_Hlt)) != \
                (uint32)(ModePtr->SIU_Hlt)) &&
               (((uint32)REG_READ32(SIU_HLTACK1) & (uint32)(ModePtr->SIU_Hlt1)) != \
                (uint32)(ModePtr->SIU_Hlt1)));
        /*lint -restore*/

    #else /* Mamba */
        /** @note Violates MISRA 2004  11.1 :cast from unsigned long to pointer,See @ref Siu_Mcu_LLD_c_3 above*/
        while (((uint32)REG_READ32(SIU_HLTACK) & (uint32)(ModePtr->SIU_Hlt)) != \
                ((uint32)(ModePtr->SIU_Hlt) & (~MCU_HALT_CPU_AND_PLATFORM_CLOCK)));

#if (MCU_ENTER_LOW_POWER_MODE == STD_ON)
        ASM_KEYWORD(" msync");
        ASM_KEYWORD(" se_isync");
        EXECUTE_WAIT();
#endif

    #endif /* #if (IPV_SIU == IPV_SIU_00_02_07_03_5) */
#endif
    }


/**
@brief   This function performs a microcontroller reset.
@details This function performs a microcontroller reset by using the hardware feature of the
         microcontroller.

@param[in]     Mcu_Cfg_Ptr

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers MCU055, MCU143, MCU144
@remarks Implements DMCU04000
*/
#if MCU_PERFORM_RESET_API == STD_ON
    FUNC(void, MCU_CODE) Mcu_SIU_PerformReset(P2CONST (Mcu_ConfigType, AUTOMATIC, MCU_APPL_DATA) \
            Mcu_Cfg_Ptr)
    {
/* Write the System Reset Control register in the SIU_SRCR with configured reset type */
        /** @note Violates MISRA 2004  11.1 :cast from unsigned long to pointer,See @ref Siu_Mcu_LLD_c_3 above*/
        REG_WRITE32(SIU_SRCR,(Mcu_Cfg_Ptr->McuLLD_Config->SWReseType));
    }
#endif/* #if MCU_PERFORM_RESET_API == STD_ON */

/**
@brief   This function Halts all the periferals 
@details This function will set the system clock to 16MHz IRC and will 
         halt all preiferals used prior to entering the sleep mode

@param[in]     timeout - timeout for the while loop waitng for the periferals to halt

@return void

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers MCU147
@remarks Implements DMCU04000
*/
#if (IPV_SIU == IPV_SIU_00_02_07_03_5) /* if Fado */
    FUNC(void, AUTOMATIC) Mcu_SIU_Halt_All(VAR(uint32, AUTOMATIC) timeout)
    {
        VAR(uint32, AUTOMATIC) Loop = (uint32)0;
        VAR(uint32, AUTOMATIC) reg0;
        VAR(uint32, AUTOMATIC) reg1;
        
        /** @note Violates MISRA 2004  11.1 :cast from unsigned long to pointer,
        See @ref Siu_Mcu_LLD_c_3 above*/
        /*lint -save -e923*/
        REG_WRITE32(SIU_HLT0, (uint32)MCU_SIUHLT0_ALL);
        REG_WRITE32(SIU_HLT1, (uint32)MCU_SIUHLT1_ALL);
        /*lint -restore*/
        do
        {
            /** @note Violates MISRA 2004  11.1 :cast from unsigned long to pointer,
            See @ref Siu_Mcu_LLD_c_3 above*/
            /*lint -save -e923*/
            reg0 = (uint32)MCU_SIUHLT0_ALL ^ REG_READ32(SIU_HLTACK0);
            reg1 = (uint32)MCU_SIUHLT1_ALL ^ REG_READ32(SIU_HLTACK1);
            /*lint -restore*/
            reg0 |= reg1;
/* the user can configure the timeout to allow acknowledge in the SIU_HLTACK register*/
            Loop++;
        }while (((uint32)0x0 != reg0) && (Loop < timeout));

        /* Select system clock to 16MHZ IRC clock for sleep mode*/
        /** @note Violates MISRA 2004  11.1 :cast from unsigned long to pointer,
        See @ref Siu_Mcu_LLD_c_3 above*/
        REG_WRITE32(SIU_SYSDIV, (uint32)0x0);
    }
#endif /* (IPV_SIU == IPV_SIU_00_02_07_03_5) */

#define MCU_STOP_SEC_CODE
/** @note Violates MISRA 2004  19.1, 19.15 :Repeated include file MemMap.h,
See @ref Siu_Mcu_LLD_c_1, Siu_Mcu_LLD_c_2 above*/
/*lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif
