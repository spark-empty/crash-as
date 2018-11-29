/**
    @file    eMIOS_Icu_LLD_CfgEx.h
    @version 2.0.0

    @brief   AUTOSAR Icu - Brief description.
    @details Detailed description.

    Project AUTOSAR 3.0 MCAL
    Patform PA
    Peripheral eMIOS200
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

@section eMIOS_Icu_LLD_CfgEx_h_1
Violates MISRA-C:2004  19.15 Precautions shall be taken in order to prevent the contents of a
header file being included twice
This is not a violation since all header files are protected against multiple inclusions
*/
#ifndef EMIOS_ICU_LLD_CFG_EX_H
#define EMIOS_ICU_LLD_CFG_EX_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@{
@brief   Header file version information
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define EMIOS_ICU_LLD_CFG_EX_VENDOR_ID            43
#define EMIOS_ICU_LLD_CFG_EX_MODULE_ID            122
#define EMIOS_ICU_LLD_CFG_EX_AR_MAJOR_VERSION     3
#define EMIOS_ICU_LLD_CFG_EX_AR_MINOR_VERSION     0
#define EMIOS_ICU_LLD_CFG_EX_AR_PATCH_VERSION     0
#define EMIOS_ICU_LLD_CFG_EX_SW_MAJOR_VERSION     2
#define EMIOS_ICU_LLD_CFG_EX_SW_MINOR_VERSION     0
#define EMIOS_ICU_LLD_CFG_EX_SW_PATCH_VERSION     0
/**@}*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
/**
@{
@brief   Possible dividers for an Emios channel
*/
/**
@brief channel prescaler = 1
*/
#define EMIOS_ICU_LLD_CH_PRES_1   0
/**
@brief channel prescaler = 2
*/
#define EMIOS_ICU_LLD_CH_PRES_2   1
/**
@brief channel prescaler = 3
*/
#define EMIOS_ICU_LLD_CH_PRES_3   2
/**
@brief channel prescaler = 4
*/
#define EMIOS_ICU_LLD_CH_PRES_4   3
/**@}*/

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

/*lint -save -e961 -e537 -e451 */
#define ICU_START_SEC_CODE
/**
@file  eMIOS_Icu_LLD_CfgEx.h
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref eMIOS_Icu_LLD_CfgEx_h_1 */

#include "MemMap.h"
/*lint -restore*/

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if header file and MemMap.h file are of the same Autosar version */
    #if ((EMIOS_ICU_LLD_CFG_EX_AR_MAJOR_VERSION != MEMMAP_AR_MAJOR_VERSION) || \
         (EMIOS_ICU_LLD_CFG_EX_AR_MINOR_VERSION != MEMMAP_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of eMios_Icu_LLD_CfgEx.h and MemMap.h are different"
    #endif
#endif

/*lint -save -e961 -e537 -e451 */
#define ICU_STOP_SEC_CODE
/**
@file  eMIOS_Icu_LLD_CfgEx.h
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref eMIOS_Icu_LLD_CfgEx_h_1 */
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif
/*EMIOS_ICU_LLD_CFG_EX_H*/
#endif 

