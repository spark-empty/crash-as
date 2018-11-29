/**
    @file    eMIOS_Mcu_LLD.h
    @version 2.0.0

    @brief   AUTOSAR Mcu - Mcu Emios LLD API.
    @details Mcu Emios LLD API.

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

@section eMIOS_Mcu_LLD_H_REF_1
MISRA-C:2004  19.15 Precautions shall be taken in order to prevent the contents of a
header file being included twice.
This is not a violation since all header files are protected against multiple inclusions.

@section eMIOS_Mcu_LLD_H_REF_2
MISRA 2004 Advisory Rule 20.2, Re-use of C90 reserved identifier
This violation is due to the use of "_" which is required as per Autosar
*/

/**
@note Violates MISRA 2004 Advisory Rule 20.2, Re-use of C90 reserved 
identifier:_EMIOS_MCU_LLD_H_- See @ref eMIOS_Mcu_LLD_H_REF_2
*/
#ifndef _EMIOS_MCU_LLD_H_
#define _EMIOS_MCU_LLD_H_

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/** @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file,
See @ref eMIOS_Mcu_LLD_H_REF_1*/
#include "Mcu.h"
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** @remarks Covers BSW00374, BSW00379, BSW00318 */
#define EMIOS_MCU_LLD_VENDOR_ID            43

#define EMIOS_MCU_LLD_AR_MAJOR_VERSION     3
#define EMIOS_MCU_LLD_AR_MINOR_VERSION    0
#define EMIOS_MCU_LLD_AR_PATCH_VERSION      0
#define EMIOS_MCU_LLD_SW_MAJOR_VERSION     2
#define EMIOS_MCU_LLD_SW_MINOR_VERSION     0
#define EMIOS_MCU_LLD_SW_PATCH_VERSION    0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if header file and Mcu.h file are of the same vendor */
#if (EMIOS_MCU_LLD_VENDOR_ID != MCU_VENDOR_ID_CFG)
    #error "eMios_Mcu_LLD.h and Mcu.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Gpt header file are of the same Autosar version */
    #if ((EMIOS_MCU_LLD_AR_MAJOR_VERSION != MCU_AR_MAJOR_VERSION) || \
         (EMIOS_MCU_LLD_AR_MINOR_VERSION != MCU_AR_MINOR_VERSION) || \
         (EMIOS_MCU_LLD_AR_PATCH_VERSION != MCU_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of eMios_Mcu_LLD.h and Mcu.h are different"
    #endif
#endif

/* Check if source file and Mcu header file are of the same software version */
#if ((EMIOS_MCU_LLD_SW_MAJOR_VERSION != MCU_SW_MAJOR_VERSION) || \
     (EMIOS_MCU_LLD_SW_MINOR_VERSION != MCU_SW_MINOR_VERSION) || \
     (EMIOS_MCU_LLD_SW_PATCH_VERSION != MCU_SW_PATCH_VERSION))
#error "Software Version Numbers of eMios_Mcu_LLD.h and Mcu.h are different"
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/


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
/** @note Violates MISRA 2004 Advisory Rule 19.15, Repeated include file,
See @ref eMIOS_Mcu_LLD_H_REF_1*/
#include "MemMap.h"

#define MCU_STOP_CONFIG_DATA_UNSPECIFIED
/** @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file,
See @ref eMIOS_Mcu_LLD_H_REF_1*/
#include "MemMap.h"


/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#define MCU_START_SEC_CODE
/** @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file,
See @ref eMIOS_Mcu_LLD_H_REF_1*/
#include "MemMap.h"

    FUNC (void, MCU_CODE) Mcu_EMIOS_Init (P2CONST(Mcu_ClockConfigType, AUTOMATIC, MCU_APPL_DATA) \
        ClockPtr);

#define MCU_STOP_SEC_CODE
/** @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file,
See @ref eMIOS_Mcu_LLD_H_REF_1*/
#include "MemMap.h"


#ifdef __cplusplus
}
#endif


#endif   /* _EMIOS_MCU_LLD_H_*/
