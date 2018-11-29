/**
    @file    FMPLL_Mcu_LLD.h
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

@section FMPLL_Mcu_LLD_H_REF_1
MISRA-C:2004  19.15 Precautions shall be taken in order to prevent the contents of a
header file being included twice.
This is not a violation since all header files are protected against multiple inclusions.

@section FMPLL_Mcu_LLD_H_REF_2
MISRA 2004 Advisory Rule 20.2, Re-use of C90 reserved identifier
This violation is due to the use of "_" which is required as per Autosar
*/

/**
@note Violates MISRA 2004 Advisory Rule 20.2, Re-use of C90 reserved 
identifier: _FMPLL_MCU_LLD_H_- See @ref FMPLL_Mcu_LLD_H_REF_2
*/
#ifndef _FMPLL_MCU_LLD_H_
#define _FMPLL_MCU_LLD_H_

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
/** @note   Violates MISRA 2004 Advisory Rule 19.15, Repeated include file,
See @ref FMPLL_Mcu_LLD_H_REF_1*/
#include "Mcu.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** @remarks Covers BSW00374, BSW00379, BSW00318 */
#define FMPLL_MCU_LLD_VENDOR_ID            43

#define FMPLL_MCU_LLD_AR_MAJOR_VERSION     3
#define FMPLL_MCU_LLD_AR_MINOR_VERSION     0
#define FMPLL_MCU_LLD_AR_PATCH_VERSION     0
#define FMPLL_MCU_LLD_SW_MAJOR_VERSION     2
#define FMPLL_MCU_LLD_SW_MINOR_VERSION     0
#define FMPLL_MCU_LLD_SW_PATCH_VERSION     0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if header file and Mcu.h file are of the same vendor */
#if (FMPLL_MCU_LLD_VENDOR_ID != MCU_VENDOR_ID_CFG)
#error "FMPLL_Mcu_LLD.h and Mcu.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
#if ((FMPLL_MCU_LLD_AR_MAJOR_VERSION != MCU_AR_MAJOR_VERSION_CFG) || \
(FMPLL_MCU_LLD_AR_MINOR_VERSION != MCU_AR_MINOR_VERSION_CFG) || \
(FMPLL_MCU_LLD_AR_PATCH_VERSION != MCU_AR_PATCH_VERSION_CFG))
#error "AutoSar Version Numbers of FMPLL_Mcu_LLD.h and Mcu.h are different"
#endif
#endif
/* Check if source file and MCU header file are of the same Software version */
#if ((FMPLL_MCU_LLD_SW_MAJOR_VERSION != MCU_SW_MAJOR_VERSION_CFG) || \
(FMPLL_MCU_LLD_SW_MINOR_VERSION != MCU_SW_MINOR_VERSION_CFG) || \
(FMPLL_MCU_LLD_SW_PATCH_VERSION != MCU_SW_PATCH_VERSION_CFG))
#error "Software Version Numbers of FMPLL_Mcu_LLD.h and Mcu.h are different"
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
/* PLL Macros */

/* when this state is reached, the PLL programming steps are completed */
#define MCU_PLL_WAIT_FINISHED    (uint32)0UL
/* when this state is reached, step 4 from non-fm PLL programming is completed */
#define MCU_Pll_WAIT_NONFMLOCK   (uint32)1UL
/* when this state is reached, step 3 from fm PLL programming is completed */
#define MCU_Pll_WAIT_FMLOCK      (uint32)2UL

/* SYSCLKSEL  bitmask */
#define SIU_SYSCLK_SYSCLKSEL      (uint32)0xC0000000UL

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

#define MCU_START_CONFIG_DATA_UNSPECIFIED
/** @note   Violates MISRA 2004 Advisory Rule 19.15, See @ref FMPLL_Mcu_LLD_H_REF_1*/
/*lint -save -e537*/
#include "MemMap.h"
/*lint -restore*/

/* Check if header file and MemMap.h file are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
#if ((FMPLL_MCU_LLD_AR_MAJOR_VERSION != MEMMAP_AR_MAJOR_VERSION) || \
(FMPLL_MCU_LLD_AR_MINOR_VERSION != MEMMAP_AR_MINOR_VERSION) || \
(FMPLL_MCU_LLD_AR_PATCH_VERSION != MEMMAP_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of FMPLL_Mcu_LLD.h and MemMap.h are different"
#endif
#endif

#define MCU_STOP_CONFIG_DATA_UNSPECIFIED
/** @note   Violates MISRA 2004 Advisory Rule 19.15, See @ref FMPLL_Mcu_LLD_H_REF_1*/
/*lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
#define MCU_START_SEC_CODE
/** @note   Violates MISRA 2004 Advisory Rule 19.15, See @ref FMPLL_Mcu_LLD_H_REF_1*/
/*lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

/**
@brief   This function initializes the pll.
@details The pll is started  by configuring its parameters.

@param[in]     ClockPtr      Pointer to clock configuration structure

@return void

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers MCU138
@remarks Implements DMCU09000
*/
    extern FUNC(void, MCU_CODE) Mcu_FMPLL_Init(P2CONST(Mcu_ClockConfigType, AUTOMATIC, \
        MCU_APPL_DATA) ClockPtr);

/**
@brief   This function returns the status of the pll.
@details This reads the pll status and returns if the pll locked or not.

@param[in]     ClockPtr      Pointer to clock configuration structure

@return Status
@retval MCU_PLL_LOCKED
@retval MCU_PLL_UNLOCKED

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers MCU008
@remarks Implements DMCU09000
*/
    extern FUNC(Mcu_PllStatusType, MCU_CODE) Mcu_FMPLL_GetPllStatus(\
        P2CONST(Mcu_ClockConfigType, AUTOMATIC, MCU_APPL_DATA) ClockPtr,\
        VAR(uint32, MCU_VAR) Mcu_TimeOut);

/**
@brief   This function disables the PLL.
@details The pll is disabled for going to sleep mode.

@return void

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers MCU138
@remarks Implements DMCU09000
*/
    extern FUNC(void, MCU_CODE) Mcu_FMPLL_Sleep(void);

#define MCU_STOP_SEC_CODE
/** @note   Violates MISRA 2004 Advisory Rule 19.15, See @ref FMPLL_Mcu_LLD_H_REF_1*/
/*lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif
#endif                                            /* _FMPLL_MCU_LLD_H_ */
