/**
    @file    Mcu_LLD.c
    @version 2.0.0

@brief   AUTOSAR Mcu - Low level part of MCU driver.
@details This file contains the low level part of the functions defined by AutoSAR.

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

@section Mcu_LLD_c_REF_1
Violates MISRA 2004 Advisory Rule 19.15, : Repeated include file MemMap.h, Precautions shall be
taken in order to prevent the contents of a header file being included twice This is not a violation
since all header files are protected against multiple inclusions

@section Mcu_LLD_c_REF_2
Violates MISRA 2004 Advisory Rule 17.4, Array indexing shall be the only allowed form of pointer
arithmetic.This violation is due to the use of pointer arithematic, to access the channel parameters,
the indexing of the pointer is taken care and hence the unintended memory location will not
be accessed

@section Mcu_LLD_c_REF_3
Violates MISRA 2004 Advisory Rule 14.7, A function shall have a single point of exit at the end of the
function.Return statement before end of function 'Mcu_LLD_GetPllStatus(void)', added to 
improve performance

@section Mcu_LLD_c_REF_4
Violates MISRA 2004 Advisory  Rule  19.1, only preprocessor statements and comments before
'#include'.This violation is not fixed since the inclusion of MemMap.h is as per 
Autosar requirement MEMMAP003
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
#include "SchM_Mcu.h"
/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/** @remarks Covers BSW00374, BSW00318 */
#define MCU_LLD_VENDOR_ID_C         43
#define MCU_LLD_AR_MAJOR_VERSION_C  3
#define MCU_LLD_AR_MINOR_VERSION_C  0
#define MCU_LLD_AR_PATCH_VERSION_C  0
#define MCU_LLD_SW_MAJOR_VERSION_C  2
#define MCU_LLD_SW_MINOR_VERSION_C  0
#define MCU_LLD_SW_PATCH_VERSION_C  0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and MCU_LLD header file are of the same vendor */
#if (MCU_LLD_VENDOR_ID_C != MCU_LLD_VENDOR_ID)
#error "Mcu_LLD.c and Mcu_LLD.h have different vendor ids"
#endif
/* Check if source file and MCU_LLD header file are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
#if ((MCU_LLD_AR_MAJOR_VERSION_C != MCU_LLD_AR_MAJOR_VERSION) || \
(MCU_LLD_AR_MINOR_VERSION_C != MCU_LLD_AR_MINOR_VERSION) || \
(MCU_LLD_AR_PATCH_VERSION_C != MCU_LLD_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of Mcu_LLD.c and Mcu_LLD.h are different"
#endif
#endif
/* Check if source file and MCU_LLD header file are of the same Software version */
#if ((MCU_LLD_SW_MAJOR_VERSION_C != MCU_LLD_SW_MAJOR_VERSION) || \
(MCU_LLD_SW_MINOR_VERSION_C != MCU_LLD_SW_MINOR_VERSION) || \
(MCU_LLD_SW_PATCH_VERSION_C != MCU_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of Mcu_LLD.c and Mcu_LLD.h are different"
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
/** @note Violates MISRA 2004 Advisory  Rule 19.1, 19.15 :See @refMcu_LLD_c_REF_1, Mcu_LLD_c_REF_4 above*/
#include "MemMap.h"
/**
@brief pointer to initialization structure
@remarks Covers MCU126
*/

    extern P2CONST (Mcu_ConfigType, MCU_VAR, MCU_APPL_CONST) Mcu_Cfg_Ptr;

    STATIC P2CONST (Mcu_ClockConfigType, MCU_CONST, MCU_APPL_DATA) Mcu_pClockConfig = NULL_PTR;

#define MCU_STOP_SEC_VAR_UNSPECIFIED
/** @note Violates MISRA 2004 Advisory  Rule 19.1, 19.15 :See @refMcu_LLD_c_REF_1, Mcu_LLD_c_REF_4 above*/
#include "MemMap.h"
/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define MCU_START_SEC_CODE
/** @note Violates MISRA 2004 Advisory  Rule 19.1, 19.15 :See @ref Mcu_LLD_c_REF_1, Mcu_LLD_c_REF_4 above*/
#include "MemMap.h"

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

/**
@brief   This function initializes the MCU module.
@details The function initializes specific parameters for DMAv module.

@param[in]     ConfigLLDPtr  Pointer to LLD configuration structure

@return void

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers MCU116
@remarks Implements DMCU02000
*/
    FUNC (void, MCU_CODE) Mcu_LLD_Init (P2CONST (McuLLD_ConfigType, AUTOMATIC, MCU_APPL_DATA) ConfigLLDPtr)
    {
        Dma_Init (&ConfigLLDPtr->DmaConfig);
    /*enter critical region*/
        SchM_Enter_Mcu(SCHM_MCU_INSTANCE_0, MCU_EXCLUSIVE_AREA_00);

    /** @remarks Covers MCU116 */
        Mcu_Flash_Init (ConfigLLDPtr);
    /*exit critical region*/
        SchM_Exit_Mcu(SCHM_MCU_INSTANCE_0, MCU_EXCLUSIVE_AREA_00);
    }

/**
@brief   This function initializes the clock structure.
@details This function intializes the clock structure by configuring the SIU and FMPLL modules.

@param[in]    ClockPtr Pointer to clock configuration structure
@param[in]    ClockNotification Indicates if monitoring the oscillator is enabled

@return Status
@retval E_OK
@retval E_NOT_OK

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers
@remarks Implements DMCU02000
*/
    FUNC (Std_ReturnType, MCU_CODE) Mcu_LLD_InitClock (P2CONST (Mcu_ClockConfigType, AUTOMATIC, MCU_APPL_DATA) ClockPtr,
        VAR (Mcu_ClockNotificationType, AUTOMATIC) ClockNotification)
    {
        VAR (Std_ReturnType, AUTOMATIC) Status = (Std_ReturnType) E_OK;

        Mcu_pClockConfig = ClockPtr;

        Mcu_EMIOS_Init (ClockPtr);
        Mcu_SIU_Init_ExternalClock(ClockPtr);
#if (MCU_FLASH_CONFIGURATION_USED == STD_ON)
        /*enter critical region*/
        SchM_Enter_Mcu(SCHM_MCU_INSTANCE_0, MCU_EXCLUSIVE_AREA_01);         
        Mcu_Flash_Configure((uint32) (RESET_BIUCR_APC_WWSC_RWSC), (uint32) (RESET_BIUCR_APC_WWSC_RWSC)); 
        /*exit critical region*/
        SchM_Exit_Mcu(SCHM_MCU_INSTANCE_0, MCU_EXCLUSIVE_AREA_01);
#endif
        Mcu_FMPLL_Init(ClockPtr);
#if (MCU_FLASH_CONFIGURATION_USED == STD_ON)
        /*enter critical region*/
        SchM_Enter_Mcu(SCHM_MCU_INSTANCE_0, MCU_EXCLUSIVE_AREA_01);         
        Mcu_Flash_Configure((uint32) (ClockPtr->FLASH_BIUCR), (uint32) (ClockPtr->FLASH_BIUCR));
        /*exit critical region*/
        SchM_Exit_Mcu(SCHM_MCU_INSTANCE_0, MCU_EXCLUSIVE_AREA_01);
#endif
        Mcu_SIU_Init_SystemClock(ClockPtr);

        return(Status);
    }

/**
@brief   This function performs a microcontroller reset.
@details This function performs a microcontroller reset by using the hardware feature of the
         microcontroller.

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers
@remarks Implements DMCU02000
*/
#if MCU_PERFORM_RESET_API == STD_ON
FUNC(void, MCU_CODE) Mcu_LLD_PerformReset(VAR(void, MCU_VAR))
{
    Mcu_SIU_PerformReset(Mcu_Cfg_Ptr);
}
#endif                                        /* #if MCU_PERFORM_RESET_API == STD_ON */

/**
@brief   This function retruns the reset reason.
@details The function reads the reset reason from hardware and returns the reason.

@return RawReset reset reason

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers
@remarks Implements DMCU02000
*/
FUNC(Mcu_ResetType, MCU_CODE) Mcu_LLD_GetResetReason(VAR(void, MCU_VAR))
{
    return Mcu_SIU_GetResetReason();
}

/**
@brief   This function returns the raw reset value.
@details This function reads the reset raw value from the hardware register.

@return         RawResetReg raw reset reason

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers
@remarks Implements DMCU02000
*/
FUNC(Mcu_RawResetType, MCU_CODE) Mcu_LLD_GetResetRawValue(VAR(void, MCU_VAR))
{
    return Mcu_SIU_GetResetRawValue();
}

/**
@brief   This function returns the status of the pll.
@details This reads the pll status and returns if the pll locked or not.

@return Status
@retval MCU_PLL_LOCKED
@retval MCU_PLL_UNLOCKED

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers
@remarks Implements DMCU02000
*/
    FUNC(Mcu_PllStatusType, MCU_CODE) Mcu_LLD_GetPllStatus(VAR(void, MCU_VAR))
    {
        VAR(Mcu_PllStatusType, AUTOMATIC) Status = MCU_PLL_UNLOCKED;
        if (Mcu_pClockConfig == NULL_PTR) 
        {
           Status = (Mcu_PllStatusType) MCU_PLL_UNLOCKED;
        }
        else
        {
           Status = Mcu_FMPLL_GetPllStatus(Mcu_pClockConfig, Mcu_Cfg_Ptr->McuTimeout);
        }
        return (Mcu_PllStatusType) Status;
    }

/**
@brief   This function applies the power mode requested.
@details This calls ip low level diver function with the requested mode.

@return void

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers
@remarks Implements DMCU02000
*/
FUNC(void, MCU_CODE) Mcu_LLD_Apply_Mode(VAR (Mcu_ModeType, AUTOMATIC) McuMode)
{
    /** @note Violates MISRA 2004 Advisory Rule 17.4: See @ref Mcu_LLD_c_2 above*/
    Mcu_SIU_Init_Halt(&Mcu_Cfg_Ptr->Mcu_ModeConfig[McuMode]);
}

#define MCU_STOP_SEC_CODE
/** @note Violates MISRA 2004 Advisory Rule 19.1, 19.15: See @refMcu_LLD_c_REF_1, Mcu_LLD_c_REF_4 above*/
#include "MemMap.h"

#ifdef __cplusplus
}
#endif
