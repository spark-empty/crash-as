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
#define GPT_DEV_ERROR_DETECT ([!IF "GptDriverConfiguration/GptDevErrorDetect"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
/**
@brief Report Wakeup Source switch
*/
#define GPT_REPORT_WAKEUP_SOURCE ([!IF "GptDriverConfiguration/GptReportWakeupSource"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

/**
@{
@remarks Covers GPT193
@remarks Implements DGPT06200
*/
/**
@brief GPT_VERSION_INFO_API switch
*/
#define GPT_VERSION_INFO_API ([!IF "GptConfigurationOfOptApiServices/GptVersionInfoApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
/**
@brief GPT_DEINIT_API switch
*/
#define GPT_DEINIT_API ([!IF "GptConfigurationOfOptApiServices/GptDeinitApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
/**
@brief GPT_TIME_ELAPSED_API switch
*/
#define GPT_TIME_ELAPSED_API ([!IF "GptConfigurationOfOptApiServices/GptTimeElapsedApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
/**
@brief GPT_TIME_REMAINING_API switch
*/
#define GPT_TIME_REMAINING_API ([!IF "GptConfigurationOfOptApiServices/GptTimeRemainingApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
/**
@brief GPT_ENABLE_DISABLE_NOTIFICATION_API switch
*/
#define GPT_ENABLE_DISABLE_NOTIFICATION_API ([!IF "GptConfigurationOfOptApiServices/GptEnableDisableNotificationApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
/**
@brief GPT_WAKEUP_FUNCTIONALITY_API switch
*/
#define GPT_WAKEUP_FUNCTIONALITY_API ([!IF "GptConfigurationOfOptApiServices/GptWakeupFunctionalityApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
/**
@brief Enable Non-Autosar API for Dual Mode support.
@remarks Covers PR-MCAL-3196
*/
#define GPT_DUAL_CLOCK_MODE ([!IF "GptNonAUTOSAR/GptEnableDualClockMode"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

#define GPT_EMIOS_MODULE    0u
#define GPT_PITRTI_MODULE   1u
#define GPT_STM_MODULE      2u

/* EMIOS counter has 24 bits - Monaco specific */
#define EMIOS_EMIOSCNT_MAX_VALUE      (Gpt_ValueType)0x00FFFFFFuL

[!MACRO "CHECK_FREEZE" , "MODULE_TYPE"!]
[!LOOP "GptChannelConfigSet/*"!]
[!VAR "num_channels" = "0"!][!//
[!VAR "freezeenabled_channels" = "0"!][!//
[!LOOP "GptChannelConfiguration/*/GptHwChannel[contains(., $MODULE_TYPE)]/.."!]
[!IF "GptFreezeEnable"!] [!VAR "freezeenabled_channels" = "$freezeenabled_channels + 1"!][!ENDIF!][!//
[!VAR "num_channels" = "$num_channels + 1"!][!//
[!ENDLOOP!]
[!IF "not($num_channels = $freezeenabled_channels) and not($freezeenabled_channels = 0)"!]
[!ERROR !][!//
Module [!"$MODULE_TYPE"!] has channels configured with different values for FreezeEnable. Please select the same value for FreezeEnable accross all [!"$MODULE_TYPE"!] channels
[!ENDERROR!][!//
[!ENDIF!]
[!ENDLOOP!]
[!ENDMACRO!]

[!NOCODE!]
[!//PITRTI and STM channels have a generic FreezeEnable bit. Check that FreezeEnable is consistent.
[!CALL "CHECK_FREEZE","MODULE_TYPE"="string('STM')"!]
[!CALL "CHECK_FREEZE","MODULE_TYPE"="string('PITRTI')"!]
[!ENDNOCODE!]

[!NOCODE!][!//
[!CODE!][!//
[!IF "IMPLEMENTATION_CONFIG_VARIANT ='VariantPreCompile'"!]
/* Gpt Pre Compile Switch */
#define GPT_PRECOMPILE_SUPPORT
[!ENDIF!]
[!ENDCODE!][!//
[!ENDNOCODE!][!//

/**
@{
@brief Number of Gpt channels configured
*/
[!LOOP "GptChannelConfigSet/*"!][!//
#define GPT_CHANNEL_NUM_[!"num:i(@index+1)"!]   [!"num:i(count(GptChannelConfiguration/*))"!]
[!ENDLOOP!][!//
/** @} */

[!NOCODE!][!//
// Loop on all Configuration Sets
[!LOOP "GptChannelConfigSet/*"!][!//
    [!VAR "ConfigSetIndex" = "../../@index"!][!//
    // Loop on all STM channels inside the same Configuration Set
    [!LOOP "./GptChannelConfiguration/*"!][!//
        [!VAR "SavedIndex" = "GptChannelId"!][!//
        [!VAR "Name" = "@name"!][!//
        // Loop on all other Configuration Sets
        [!LOOP "../../../*[@index>$ConfigSetIndex]/GptChannelConfiguration/*"!][!//
            [!IF "($Name = node:name(.))"!][!//
                [!IF "($SavedIndex != GptChannelId)"!][!//
                    // Error!!!!!!!!
                    [!ERROR !][!//
                        [!"$Name"!][!"'- Symbolic name for channels can be repeated only if they have the same ChannelId in each of the config set.'"!][!//
                    [!ENDERROR!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!][!//

/**
@{
@brief Symbolic names of channels
*/
[!VAR "already_parsed_names"!][!ENDVAR!][!//
[!LOOP "GptChannelConfigSet/*/GptChannelConfiguration/*"!]
[!IF "contains($already_parsed_names, concat(node:name(.),'|')) = false()"!][!//
#define [!"node:name(.)"!]  (Gpt_ChannelType)[!"GptChannelId"!]
[!VAR "already_parsed_names"="concat($already_parsed_names,node:name(.),'|')"!][!//
[!ENDIF!]
[!ENDLOOP!]
/*@}*/

/**
@{
@brief IRQ Defines
*/
[!VAR "already_parsed"!][!ENDVAR!][!//
[!LOOP "GptChannelConfigSet/*/GptChannelConfiguration/*/GptHwChannel"!][!//
[!IF "contains($already_parsed, concat(.,'|')) = false()"!][!//
[!IF "contains(.,'STM') and num:i(substring-after(substring-after(.,'_'),'_')) > 1"!][!//
[!IF "contains($already_parsed, concat('GPT_STM_CH_1','|')) = false()"!][!//
[!VAR "already_parsed"="concat($already_parsed,'GPT_STM_CH_1','|')"!][!//
#define GPT_STM_CH_1_ISR_USED
[!ENDIF!][!//
[!ELSE!][!//
#define GPT_[!"."!]_ISR_USED
[!VAR "already_parsed"="concat($already_parsed,.,'|')"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
/** @} */
/* ISR 1 is shared between channels 1, 2, 3 - Monaco specific*/
#define GPT_STM_ISR_1_SHARED

[!IF "IMPLEMENTATION_CONFIG_VARIANT ='VariantPostBuild'"!]
/* Configuration structures for PB*/
#define GPT_CFG_EXTERN_DECLARATIONS \
[!NOCODE!][!VAR "var_count1"="num:i(count(GptChannelConfigSet/*))"!][!VAR "w"="0"!][!ENDNOCODE!][!//
[!LOOP "GptChannelConfigSet/*"!][!VAR "w"="$w + 1"!][!//
extern CONST(Gpt_ConfigType, GPT_CONST) [!"@name"!];[!IF "$w < $var_count1"!]\[!ENDIF!]
[!ENDLOOP!][!//
[!ENDIF!]

/**
@brief The number of HW channels
*/
#define GPT_HW_CHANNEL_NUM   [!"num:i(count(ecu:list('Gpt.GptChannelConfigSet.GptChannelConfiguration.GptHwChannel')))"!]


/**
@brief The number of EMIOS HW channels
*/
[!NOCODE!][!//
[!VAR "MAX_CH"="num:i(-1)"!] [!//max number of channels for the hardware unit with the higher number - will be calculated
[!VAR "CRT_HW"="num:i(-1)"!] [!//number of hardware units available for this derivative - will be calculated
[!VAR "MAX_HW" = "num:i(1)"!] [!//max number of hardware units available for this family
[!//calculate MAX_HW
[!FOR "x" = "0" TO "$MAX_HW"!]
    [!IF "count(text:grep(ecu:list('Gpt.GptChannelConfigSet.GptChannelConfiguration.GptHwChannel'),concat('EMIOS_',$x,'.*'))) > 0"!]
    [!VAR "CRT_HW"="$x"!]
[!ENDIF!]
[!ENDFOR!]

[!LOOP "text:grep(ecu:list('Gpt.GptChannelConfigSet.GptChannelConfiguration.GptHwChannel'),concat('EMIOS_',$CRT_HW,'.*'))"!]
    [!VAR "CRT_CH" = "substring-after(.,concat('EMIOS_',$CRT_HW,'_CH_'))"!]
    [!IF "$MAX_CH < $CRT_CH"!]
        [!VAR "MAX_CH" = "$CRT_CH"!]
    [!ENDIF!]
[!ENDLOOP!]

[!IF "$MAX_CH > -1"!]
    [!VAR "MAX_CH"="num:i($CRT_HW*32 + $MAX_CH + 1)"!]
[!ELSE!][!//
    [!ERROR !][!//
        [!"$Name"!][!"'-MAX_CH should be >= 0 at this stage'"!][!//
    [!ENDERROR!][!//
[!ENDIF!]
[!ENDNOCODE!][!//

#define GPT_EMIOS_CHAN_NUM    [!"$MAX_CH"!]

/**
@brief The number of PITRTI HW channels
*/
#define GPT_PITRTI_CHAN_NUM   [!"num:i(count(text:grep(ecu:list('Gpt.GptChannelConfigSet.GptChannelConfiguration.GptHwChannel'),'PITRTI.*')))"!]

/**
@brief The number of STM HW channels
*/
#define GPT_STM_CHAN_NUM      [!"num:i(count(text:grep(ecu:list('Gpt.GptChannelConfigSet.GptChannelConfiguration.GptHwChannel'),'STM.*')))"!]

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
