/**
    @file    Gpt_Cfg.h
    @version 2.0.0

    @brief   AUTOSAR Gpt - Gpt driver header file.
    @details GPT driver header file, containing C and XPath constructs for generating Gpt
    configuration header file.

    Project AUTOSAR 3.0 MCAL
    Platform PA
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

/* PROG044 */
#ifndef GPT_CFG_H
#define GPT_CFG_H

/*==================================================================================================
                                         INCLUDE FILES
==================================================================================================*/
/**

@remarks  Implements DGPT11039,DGPT11043,DGPT11056,DGPT11060
*/
#include "Reg_eSys_EMIOS_CfgEx.h"
#include "eMIOS_Gpt_LLD_CfgEx.h"
#include "Stm_Gpt_LLD_CfgEx.h"
#include "PitRti_Gpt_LLD_CfgEx.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@{
@brief   Source file version information
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define GPT_VENDOR_ID_CFG         43
#define GPT_AR_MAJOR_VERSION_CFG  3
#define GPT_AR_MINOR_VERSION_CFG  0
#define GPT_AR_PATCH_VERSION_CFG  0
#define GPT_SW_MAJOR_VERSION_CFG  2
#define GPT_SW_MINOR_VERSION_CFG  0
#define GPT_SW_PATCH_VERSION_CFG  0
/** @}*/
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#if (GPT_VENDOR_ID_CFG != EMIOS_GPT_LLD_CFG_EX_VENDOR_ID)
    #error "Gpt_Cfg.h and eMios_Gpt_LLD_CfgEx.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if header file and Emios Cfg LLD header file are of the same Autosar version */
    #if ((GPT_AR_MAJOR_VERSION_CFG != EMIOS_GPT_LLD_CFG_EX_AR_MAJOR_VERSION) || \
         (GPT_AR_MINOR_VERSION_CFG != EMIOS_GPT_LLD_CFG_EX_AR_MINOR_VERSION) || \
         (GPT_AR_PATCH_VERSION_CFG != EMIOS_GPT_LLD_CFG_EX_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Gpt_Cfg.h and eMios_Gpt_LLD_CfgEx.h are different"
    #endif
#endif
/* Check if header file and Emios Cfg LLD header file are of the same software version */
#if ((GPT_SW_MAJOR_VERSION_CFG != EMIOS_GPT_LLD_CFG_EX_SW_MAJOR_VERSION) || \
     (GPT_SW_MINOR_VERSION_CFG != EMIOS_GPT_LLD_CFG_EX_SW_MINOR_VERSION) || \
     (GPT_SW_PATCH_VERSION_CFG != EMIOS_GPT_LLD_CFG_EX_SW_PATCH_VERSION))
#error "Software Version Numbers of Gpt_Cfg.h and eMios_Gpt_LLD_CfgEx.h are different"
#endif

#if (GPT_VENDOR_ID_CFG != STM_GPT_LLD_CFG_EX_VENDOR_ID)
    #error "Gpt_Cfg.h and Stm_Gpt_LLD_CfgEx.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
/* Check if header file and Stm Cfg LLD header file are of the same Autosar version */
#if ((GPT_AR_MAJOR_VERSION_CFG != STM_GPT_LLD_CFG_EX_AR_MAJOR_VERSION) || \
     (GPT_AR_MINOR_VERSION_CFG != STM_GPT_LLD_CFG_EX_AR_MINOR_VERSION) || \
     (GPT_AR_PATCH_VERSION_CFG != STM_GPT_LLD_CFG_EX_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of Gpt_Cfg.h and Stm_Gpt_LLD_CfgEx.h are different"
#endif
#endif
/* Check if header file and Stm Cfg LLD header header file are of the same software version */
#if ((GPT_SW_MAJOR_VERSION_CFG != STM_GPT_LLD_CFG_EX_SW_MAJOR_VERSION) || \
     (GPT_SW_MINOR_VERSION_CFG != STM_GPT_LLD_CFG_EX_SW_MINOR_VERSION) || \
     (GPT_SW_PATCH_VERSION_CFG != STM_GPT_LLD_CFG_EX_SW_PATCH_VERSION))
#error "Software Version Numbers of Gpt_Cfg.h and Stm_Gpt_LLD_CfgEx.h are different"
#endif

#if (GPT_VENDOR_ID_CFG != REG_ESYS_EMIOS_CFGEX_H_VENDOR_ID)
    #error "Gpt_Cfg.h and Reg_eSys_EMIOS_Cfgex.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if header file and Reg_eSys_EMIOS_Cfgex header file are of the same Autosar version */
    #if ((GPT_AR_MAJOR_VERSION_CFG != REG_ESYS_EMIOS_CFGEX_H_AR_MAJOR_VERSION) || \
         (GPT_AR_MINOR_VERSION_CFG != REG_ESYS_EMIOS_CFGEX_H_AR_MINOR_VERSION) || \
         (GPT_AR_PATCH_VERSION_CFG != REG_ESYS_EMIOS_CFGEX_H_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Gpt_Cfg.h and Reg_eSys_EMIOS_Cfgex.h are different"
    #endif
#endif
/* Check if header file and Reg_eSys_EMIOS_Cfgex header file are of the same software version */
#if ((GPT_SW_MAJOR_VERSION_CFG != REG_ESYS_EMIOS_CFGEX_H_SW_MAJOR_VERSION) || \
     (GPT_SW_MINOR_VERSION_CFG != REG_ESYS_EMIOS_CFGEX_H_SW_MINOR_VERSION) || \
     (GPT_SW_PATCH_VERSION_CFG != REG_ESYS_EMIOS_CFGEX_H_SW_PATCH_VERSION))
#error "Software Version Numbers of Gpt_Cfg.h and Reg_eSys_EMIOS_Cfgex.h are different"
#endif

#if (GPT_VENDOR_ID_CFG != PITRTI_GPT_LLD_CFG_EX_VENDOR_ID)
    #error "Gpt_Cfg.h and PitRti_Gpt_LLD_CfgEx.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if header file and PitRti Cfg LLD header file are of the same Autosar version */
    #if ((GPT_AR_MAJOR_VERSION_CFG != PITRTI_GPT_LLD_CFG_EX_AR_MAJOR_VERSION) || \
         (GPT_AR_MINOR_VERSION_CFG != PITRTI_GPT_LLD_CFG_EX_AR_MINOR_VERSION) || \
         (GPT_AR_PATCH_VERSION_CFG != PITRTI_GPT_LLD_CFG_EX_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Gpt_Cfg.h and PitRti_Gpt_LLD_CfgEx.h are different"
#endif
#endif
/* Check if header file and PitRti Cfg LLD header file are of the same software version */
#if ((GPT_SW_MAJOR_VERSION_CFG != PITRTI_GPT_LLD_CFG_EX_SW_MAJOR_VERSION) || \
     (GPT_SW_MINOR_VERSION_CFG != PITRTI_GPT_LLD_CFG_EX_SW_MINOR_VERSION) || \
     (GPT_SW_PATCH_VERSION_CFG != PITRTI_GPT_LLD_CFG_EX_SW_PATCH_VERSION))
#error "Software Version Numbers of Gpt_Cfg.h and PitRti_Gpt_LLD_CfgEx.h are different"
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/* [GPT183]: GptDriverConfiguration - This container contains the module-wide configuration */
/* (parameters) of the GPT Driver - GPT_DEV_ERROR_DETECT, GPT_REPORT_WAKEUP_SOURCE */

/* [GPT175]: The detection of development errors is configurable (STD_ON / STD_OFF) */
/* at pre-compile time. The switch GPT_DEV_ERROR_DETECT (see chapter 10) shall activate */
/* or deactivate the detection of all development errors. */

/* [GPT176]: If the GPT_DEV_ERROR_DETECT switch is enabled, API parameter checking is enabled. */
/**
@brief Gpt Dev error detect switch
@remarks Covers GPT175
*/
#define GPT_DEV_ERROR_DETECT (STD_ON)
/**
@brief Report Wakeup Source switch
*/
#define GPT_REPORT_WAKEUP_SOURCE (STD_ON)

/**
@{
@remarks Covers GPT193
@remarks Implements DGPT06200
*/
/**
@brief GPT_VERSION_INFO_API switch
*/
#define GPT_VERSION_INFO_API (STD_ON)
/**
@brief GPT_DEINIT_API switch
*/
#define GPT_DEINIT_API (STD_ON)
/**
@brief GPT_TIME_ELAPSED_API switch
*/
#define GPT_TIME_ELAPSED_API (STD_ON)
/**
@brief GPT_TIME_REMAINING_API switch
*/
#define GPT_TIME_REMAINING_API (STD_ON)
/**
@brief GPT_ENABLE_DISABLE_NOTIFICATION_API switch
*/
#define GPT_ENABLE_DISABLE_NOTIFICATION_API (STD_ON)
/**
@brief GPT_WAKEUP_FUNCTIONALITY_API switch
*/
#define GPT_WAKEUP_FUNCTIONALITY_API (STD_ON)
/**
@brief Enable Non-Autosar API for Dual Mode support.
@remarks Covers PR-MCAL-3196
*/
#define GPT_DUAL_CLOCK_MODE (STD_OFF)

#define GPT_EMIOS_MODULE    0u
#define GPT_PITRTI_MODULE   1u
#define GPT_STM_MODULE      2u

/* EMIOS counter has 24 bits - Monaco specific */
#define EMIOS_EMIOSCNT_MAX_VALUE      (Gpt_ValueType)0x00FFFFFFuL







/**
@{
@brief Number of Gpt channels configured
*/
#define GPT_CHANNEL_NUM_1   1
/** @} */


/**
@{
@brief Symbolic names of channels
*/

#define GptChannelConfigurati_0  (Gpt_ChannelType)0


/*@}*/

/**
@{
@brief IRQ Defines
*/
#define GPT_PITRTI_CH_0_ISR_USED
/** @} */
/* ISR 1 is shared between channels 1, 2, 3 - Monaco specific*/
#define GPT_STM_ISR_1_SHARED


/* Configuration structures for PB*/
#define GPT_CFG_EXTERN_DECLARATIONS \
extern CONST(Gpt_ConfigType, GPT_CONST) GptChannelConfigSet_0;


/**
@brief The number of HW channels
*/
#define GPT_HW_CHANNEL_NUM   17


/**
@brief The number of EMIOS HW channels
*/

#define GPT_EMIOS_CHAN_NUM    24

/**
@brief The number of PITRTI HW channels
*/
#define GPT_PITRTI_CHAN_NUM   5

/**
@brief The number of STM HW channels
*/
#define GPT_STM_CHAN_NUM      4

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#endif  /* GPT_CFG_H */
