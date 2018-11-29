/**
    @file    Mcu_LLD.h
    @version 2.0.0

@brief   AUTOSAR Mcu - Brief description.
@details Detailed description.

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

@section Mcu_LLD_h_REF_1
Violates MISRA 2004 Advisory Rule 19.15, : Repeated include files, Precautions shall be taken in
order to prevent the contents of a header file being included twice This is not a violation since
all header files are protected against multiple inclusions

@section Mcu_LLD_h_REF_2
MISRA 2004 Advisory Rule 20.2, Re-use of C90 reserved identifier
This violation is due to the use of "_" which is required as per Autosar

@section Mcu_LLD_h_REF_3
MISRA-C:2004 19.7 VIOLATION: Use of function like macro.
This violation is due to function like macros defined for register operations.
Function like macros are used to reduce code complexity.
*/

#ifndef MCU_LLD_H
#define MCU_LLD_H

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
/** @remarks Covers MCU108, MCU152 */
/** @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file, See @ref Mcu_LLD_h_REF_1
*/

/*lint -save -e537*/
#include "Std_Types.h"
#include "Reg_Macros.h"
#include "Reg_eSys_EMIOS.h"
#include "Reg_eSys_FLASHC.h"
#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "Reg_eSys_FMPLL.h"
#include "Reg_eSys_SIU.h"
#include "Siu_Mcu_LLD.h"
#include "FMPLL_Mcu_LLD.h"
#include "eMIOS_Mcu_LLD.h"
#include "Dma_LLD.h"
#include "Mcal.h"
/*lint -restore*/
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** @remarks Covers BSW00374, BSW00379, BSW00318 */
#define MCU_LLD_VENDOR_ID            43
#define MCU_LLD_AR_MAJOR_VERSION     3
#define MCU_LLD_AR_MINOR_VERSION     0
#define MCU_LLD_AR_PATCH_VERSION     0
#define MCU_LLD_SW_MAJOR_VERSION     2
#define MCU_LLD_SW_MINOR_VERSION     0
#define MCU_LLD_SW_PATCH_VERSION     0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if MCU_LLD header file and MCU header file are of the same vendor */
#if (MCU_LLD_VENDOR_ID != MCU_VENDOR_ID)
#error "Mcu_LLD.h and Mcu.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
/* Check if MCU_LLD header file and MCU header file are of the same software version */
#if ((MCU_LLD_AR_MAJOR_VERSION != MCU_AR_MAJOR_VERSION) || \
(MCU_LLD_AR_MINOR_VERSION != MCU_AR_MINOR_VERSION) || \
(MCU_LLD_AR_PATCH_VERSION != MCU_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of Mcu_LLD.h and Mcu.h are different"
#endif
#endif
/* Check if MCU_LLD header file and MCU header file are of the same software version */
#if ((MCU_LLD_SW_MAJOR_VERSION != MCU_SW_MAJOR_VERSION) || \
(MCU_LLD_SW_MINOR_VERSION != MCU_SW_MINOR_VERSION) || \
(MCU_LLD_SW_PATCH_VERSION != MCU_SW_PATCH_VERSION))
#error "Software Version Numbers of Mcu_LLD.h and Mcu.h are different"
#endif

/* Check if MCU_LLD header file and MCU configuration header file are of the same vendor */
#if (MCU_LLD_VENDOR_ID != MCU_VENDOR_ID_CFG)
#error "Mcu_LLD.h and Mcu_Cfg.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
/* Check if MCU_LLD header file and configuration header file are of the same software version */
#if ((MCU_LLD_AR_MAJOR_VERSION != MCU_AR_MAJOR_VERSION_CFG) || \
(MCU_LLD_AR_MINOR_VERSION != MCU_AR_MINOR_VERSION_CFG) || \
(MCU_LLD_AR_PATCH_VERSION != MCU_AR_PATCH_VERSION_CFG))
#error "AutoSar Version Numbers of Mcu_LLD.h and Mcu_Cfg.h are different"
#endif
#endif
/* Check if MCU_LLD header file and configuration header file are of the same software version */
#if ((MCU_LLD_SW_MAJOR_VERSION != MCU_SW_MAJOR_VERSION_CFG) || \
(MCU_LLD_SW_MINOR_VERSION != MCU_SW_MINOR_VERSION_CFG) || \
(MCU_LLD_SW_PATCH_VERSION != MCU_SW_PATCH_VERSION_CFG))
#error "Software Version Numbers of Mcu_LLD.h and Mcu_Cfg.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
/* Check if Std_Types and MCU_LLD  header file are of the same Autosar version */
#if ((MCU_LLD_AR_MAJOR_VERSION != STD_TYPES_AR_MAJOR_VERSION) || \
(MCU_LLD_AR_MINOR_VERSION != STD_TYPES_AR_MINOR_VERSION))
#error "AutoSar Version Numbers of Mcu_LLD.h and Std_Types.h are different"
#endif
#endif

/* Check if MCU_LLD headers and FMPLL_Mcu_LLD header file are of the same vendor */
#if (MCU_LLD_VENDOR_ID != FMPLL_MCU_LLD_VENDOR_ID)
#error "Mcu_LLD.h and FMPLL_Mcu_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
/* Check if FMPLL_Mcu_LLD and MCU  header file are of the same Autosar version */
#if ((MCU_LLD_AR_MAJOR_VERSION != FMPLL_MCU_LLD_AR_MAJOR_VERSION) || \
(MCU_LLD_AR_MINOR_VERSION != FMPLL_MCU_LLD_AR_MINOR_VERSION) || \
(MCU_LLD_AR_PATCH_VERSION != FMPLL_MCU_LLD_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of Mcu_LLD.h and FMPLL_Mcu_LLD.h are different"
#endif
#endif
/* Check if FMPLL_Mcu_LLD and MCU header file are of the same software version */
#if ((MCU_LLD_SW_MAJOR_VERSION != FMPLL_MCU_LLD_SW_MAJOR_VERSION) || \
(MCU_LLD_SW_MINOR_VERSION != FMPLL_MCU_LLD_SW_MINOR_VERSION) || \
(MCU_LLD_SW_PATCH_VERSION != FMPLL_MCU_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of Mcu_LLD.h and FMPLL_Mcu_LLD.h are different"
#endif

/* Check if source file and eMIOS_Mcu_LLD header file are of the same vendor */
#if (MCU_LLD_VENDOR_ID != EMIOS_MCU_LLD_VENDOR_ID)
#error "Mcu_LLD.h and eMIOS_Mcu_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
/* Check if eMIOS_Mcu_LLD and MCU header file are of the same Autosar version */
#if ((MCU_LLD_AR_MAJOR_VERSION != EMIOS_MCU_LLD_AR_MAJOR_VERSION) || \
(MCU_LLD_AR_MINOR_VERSION != EMIOS_MCU_LLD_AR_MINOR_VERSION) || \
(MCU_LLD_AR_PATCH_VERSION != EMIOS_MCU_LLD_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of Mcu_LLD.h and eMIOS_Mcu_LLD.h are different"
#endif
#endif
/* Check if eMIOS_Mcu_LLD and MCU header file are of the same software version */
#if ((MCU_LLD_SW_MAJOR_VERSION != EMIOS_MCU_LLD_SW_MAJOR_VERSION) || \
(MCU_LLD_SW_MINOR_VERSION != EMIOS_MCU_LLD_SW_MINOR_VERSION) || \
(MCU_LLD_SW_PATCH_VERSION != EMIOS_MCU_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of Mcu_LLD.h and eMIOS_Mcu_LLD.h are different"
#endif

/* Check if MCU_LLD header file and Siu_Mcu_LLD header file are of the same vendor */
#if (MCU_LLD_VENDOR_ID != SIU_MCU_LLD_VENDOR_ID)
#error "Mcu_LLD.h and Siu_Mcu_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
/* Check if Siu_Mcu_LLD and MCU_LLD header file are of the same Autosar version */
#if ((MCU_LLD_AR_MAJOR_VERSION != SIU_MCU_LLD_AR_MAJOR_VERSION) || \
(MCU_LLD_AR_MINOR_VERSION != SIU_MCU_LLD_AR_MINOR_VERSION) || \
(MCU_LLD_AR_PATCH_VERSION != SIU_MCU_LLD_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of Mcu_LLD.h and Siu_Mcu_LLD.h are different"
#endif
#endif
/* Check if Siu_Mcu_LLD and MCU_LLD header file are of the same software version */
#if ((MCU_LLD_SW_MAJOR_VERSION != SIU_MCU_LLD_SW_MAJOR_VERSION) || \
(MCU_LLD_SW_MINOR_VERSION != SIU_MCU_LLD_SW_MINOR_VERSION) || \
(MCU_LLD_SW_PATCH_VERSION != SIU_MCU_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of Mcu_LLD.h and Siu_Mcu_LLD.h are different"
#endif

/* Check if MCU_LLD header file and DMA header file are of the same vendor */
#if (MCU_LLD_VENDOR_ID != DMA_VENDOR_ID)
#error "Mcu_LLD.h and Dma_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
/* Check if Dma_LLD and MCU_LLD header file are of the same Autosar version */
#if ((MCU_LLD_AR_MAJOR_VERSION != DMA_AR_MAJOR_VERSION) || \
(MCU_LLD_AR_MINOR_VERSION != DMA_AR_MINOR_VERSION) || \
(MCU_LLD_AR_PATCH_VERSION != DMA_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of Mcu_LLD.h and Dma_LLD.h are different"
#endif
#endif
/* Check if Dma_LLD and MCU_LLD header file are of the same software version */
#if ((MCU_LLD_SW_MAJOR_VERSION != DMA_SW_MAJOR_VERSION) || \
(MCU_LLD_SW_MINOR_VERSION != DMA_SW_MINOR_VERSION) || \
(MCU_LLD_SW_PATCH_VERSION != DMA_SW_PATCH_VERSION))
#error "Software Version Numbers of Mcu_LLD.h and Dma_LLD.h are different"
#endif
/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/** @brief Reset related masks */
#define MCU_EIGHT_VALUE                          (uint32)0x8UL
#define MCU_32_BIT_MASK                          (uint32)0xFFFFFFFFUL
#define MCU_SHIFT_TEN                            (uint32)10UL
#define MCU_SHIFT_TWENTY_EIGHT                   (uint32)28UL

/** @brief Modes for PLL functionalities */
#define MCU_PLL_FM_MODE                          (uint8)1U
#define MCU_PLL_UNUSED_MODE                      (uint8)2U

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
/**
@brief   This function activates the main PLL as the system clock source.
@details This function on Mamba is a stub.

@param[in]    clkNotification Indicates if notification is enabled

@return void

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers MCU140, MCU056
@remarks Implements DMCU02000
*/
/** @note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro, See @ref Mcu_LLD_h_REF_3*/
#define Mcu_LLD_DistributePllClock(clkNotification) {;}
/*==================================================================================================
                                         ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#define MCU_START_SEC_CODE
/** @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file, See @ref Mcu_LLD_h_REF_1*/
#include "MemMap.h"

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
extern FUNC (void, MCU_CODE) Mcu_LLD_Init (P2CONST (McuLLD_ConfigType, AUTOMATIC, MCU_APPL_DATA) ConfigLLDPtr);

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
extern FUNC (Std_ReturnType, MCU_CODE) Mcu_LLD_InitClock (P2CONST (Mcu_ClockConfigType, AUTOMATIC, MCU_APPL_DATA) ClockPtr,
        VAR (Mcu_ClockNotificationType, AUTOMATIC) ClockNotification);

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
    extern FUNC(void, MCU_CODE) Mcu_LLD_PerformReset(VAR(void, MCU_VAR));
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
extern FUNC(Mcu_ResetType, MCU_CODE) Mcu_LLD_GetResetReason(VAR(void, MCU_VAR));

/**
@brief   This function returns the raw reset value.
@details This function reads the reset raw value from the hardware register.

@return         RawResetReg raw reset reason

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers
@remarks Implements DMCU02000
*/
extern FUNC(Mcu_RawResetType, MCU_CODE) Mcu_LLD_GetResetRawValue(VAR(void, MCU_VAR));

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
extern FUNC(Mcu_PllStatusType, MCU_CODE) Mcu_LLD_GetPllStatus(VAR(void, MCU_VAR));

/**
@brief   This function applies the power mode requested.
@details This calls ip low level diver function with the requested mode.

@return void

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers
@remarks Implements DMCU02000
*/
extern FUNC(void, MCU_CODE) Mcu_LLD_Apply_Mode(VAR (Mcu_ModeType, AUTOMATIC) McuMode);
#define MCU_STOP_SEC_CODE
/** @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file, See @ref Mcu_LLD_h_REF_1*/
#include "MemMap.h"

#define MCU_START_SEC_VAR_UNSPECIFIED
/** @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file, See @ref Mcu_LLD_h_REF_1*/
#include "MemMap.h"

/**
@brief   This function initializes global settings for the flash memory.
@details The function initializes settings like Address Pipelining Control, Write Wait State Control, Read Wait State Control,
           Read-While-Write Control, Page Buffer Configuration, Page Buffer Configuration, Data Prefetch Enable, Instruction Prefetch Enable,
           Prefetch Limit, Buffer Enable, Arbitration Mode, Master Prefetch Disable, Master Access Protection.
@param[in]     ConfigLLDPtr      Mcu configuration pointer

@return Description of the returned value
@retval void

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers
@remarks Implements DMCU01700
 */
extern P2FUNC (void, const, Mcu_Flash_Init)(P2CONST(McuLLD_ConfigType, AUTOMATIC, MCU_APPL_DATA) ConfigLLDPtr);

/**
@brief   This function configures clock dependent settings for the flash memory.
@details The function configures clock dependent settings like Address Pipelining Control, Write Wait State Control, Read Wait State Control.
@param[in]     Mcu_CFlash_Conf      Mcu code flash configuration value
@param[in]     Mcu_DFlash_Conf      Mcu data flash configuration value

@return Description of the returned value
@retval void

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers MCU116
@remarks Implements 
 */
extern P2FUNC (void, const, Mcu_Flash_Configure)(VAR(uint32, MCU_VAR) Mcu_CFlash_Conf, VAR(uint32, MCU_VAR) Mcu_DFlash_Conf);

#define MCU_STOP_SEC_VAR_UNSPECIFIED
/** @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file, See @ref Mcu_LLD_h_1*/
#include "MemMap.h"

#ifdef __cplusplus
}
#endif
#endif                                            /*MCU_LLD_H*/
