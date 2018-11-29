/**
    @file    Stm_Gpt_LLD_CfgEx.h
    @version 2.0.0

    @brief   AUTOSAR Gpt - Brief description.
    @details Detailed description.

    Project AUTOSAR 3.0 MCAL
    Patform PA
    Peripheral eMIOS200_Stm_PitRti
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
#ifndef STM_GPT_LLD_CFG_EX_H
#define STM_GPT_LLD_CFG_EX_H

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
@brief Parameters that shall be published within the Gpt driver header file and also in the
       module's description file
@remarks Covers BSW00374, BSW00379, BSW00318
@{
*/
#define STM_GPT_LLD_CFG_EX_VENDOR_ID            43
#define STM_GPT_LLD_CFG_EX_AR_MAJOR_VERSION     3
#define STM_GPT_LLD_CFG_EX_AR_MINOR_VERSION     0
#define STM_GPT_LLD_CFG_EX_AR_PATCH_VERSION     0
#define STM_GPT_LLD_CFG_EX_SW_MAJOR_VERSION     2
#define STM_GPT_LLD_CFG_EX_SW_MINOR_VERSION     0
#define STM_GPT_LLD_CFG_EX_SW_PATCH_VERSION     0
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
/* API SERVICE IDs */
/**
@brief API service ID for STM_Gpt_ProcessInterrupt  function
@details Parameters used when raising a CER error/exception
*/
#define GPT_STM_INTERRUPT_ID          (uint8)0x03U

/**
@{
@brief STM Channels defines
*/
#define STM_CH_0  (uint8)0
#define STM_CH_1  (uint8)1
#define STM_CH_2  (uint8)2
#define STM_CH_3  (uint8)3
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

#define GPT_START_SEC_CODE
#include "MemMap.h"

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if header file and MemMap.h file are of the same Autosar version */
    #if ((STM_GPT_LLD_CFG_EX_AR_MAJOR_VERSION != MEMMAP_AR_MAJOR_VERSION) || \
         (STM_GPT_LLD_CFG_EX_AR_MINOR_VERSION != MEMMAP_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Stm_Gpt_LLD_CfgEx.h and MemMap.h are different"
    #endif
#endif

#define GPT_STOP_SEC_CODE
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /*STM_GPT_LLD_CFG_EX_H*/
