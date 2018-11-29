/**
    @file    Gpt_Cfg.c
    @version 2.0.0

    @brief   AUTOSAR Gpt - GPT driver source file.
    @details GPT driver source file, containing C and XPath constructs for generating Gpt
    configuration source file for the Precompile configuration variant.

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

/*  REF 1  - MISRA-C:2004   19.1:  Violates   MISRA  2004  Advisory  Rule   19.1,  only preprocessor
    statements and comments before '#include'
    This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement
    MEMMAP003. */

/*  REF 2  - MISRA-C:2004   19.15:  Repeated include file
    This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement
    MEMMAP003. */

/*==================================================================================================
                                         INCLUDE FILES
==================================================================================================*/
#include "Gpt.h"


#ifdef GPT_PRECOMPILE_SUPPORT

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
/**
@{
@brief   Source file version information
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define GPT_VENDOR_ID_CFG_C         43
#define GPT_AR_MAJOR_VERSION_CFG_C  3
#define GPT_AR_MINOR_VERSION_CFG_C  0
#define GPT_AR_PATCH_VERSION_CFG_C  0
#define GPT_SW_MAJOR_VERSION_CFG_C  2
#define GPT_SW_MINOR_VERSION_CFG_C  0
#define GPT_SW_PATCH_VERSION_CFG_C  0
/** @} */

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#if (GPT_VENDOR_ID_CFG_C != GPT_VENDOR_ID)
    #error "Gpt_Cfg.c and Gpt.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((GPT_AR_MAJOR_VERSION_CFG_C != GPT_AR_MAJOR_VERSION) || \
         (GPT_AR_MINOR_VERSION_CFG_C != GPT_AR_MINOR_VERSION) || \
         (GPT_AR_PATCH_VERSION_CFG_C != GPT_AR_PATCH_VERSION))
      #error "AutoSar Version Numbers of Gpt_Cfg.c and Gpt.h are different"
    #endif
#endif
#if ((GPT_SW_MAJOR_VERSION_CFG_C != GPT_SW_MAJOR_VERSION) || \
     (GPT_SW_MINOR_VERSION_CFG_C != GPT_SW_MINOR_VERSION) || \
     (GPT_SW_PATCH_VERSION_CFG_C != GPT_SW_PATCH_VERSION))
  #error "Software Version Numbers of Gpt_Cfg.c and Gpt.h are different"
#endif

/*================================================================================================*/
/**
@brief Gpt user notifications
@remarks Covers GPT087, GPT232, GPT292
*/
[!VAR "already_parsed_notification"!][!ENDVAR!][!//
[!LOOP "GptChannelConfigSet/*[1]/GptChannelConfiguration/*/GptNotification"!][!//
[!IF "(. != 'NULL_PTR') and (. != 'NULL')"!][!//
[!IF "contains($already_parsed_notification, concat(.,'|')) = false()"!][!//
extern void [!"."!](void);
[!VAR "already_parsed_notification"="concat($already_parsed_notification,.,'|')"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//

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

#define GPT_START_SEC_CONST_UNSPECIFIED
/* MISRA-C:2004 19.1 VIOLATION: Refer to REF 1 above*/
/* MISRA-C:2004  19.15 VIOLATION : Refer to REF 2 above*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

STATIC CONST(Gpt_LLD_ChannelConfigType, GPT_CONST) Gpt_InitChannelPC_[!"num:i(@index+1)"!][GPT_CHANNEL_NUM_[!"num:i(@index+1)"!]]=
{
[!VAR "GptPrescConf" = "(number(GptChannelConfigSet/*[1]/GptSTMChannelPrescale))"!][!//
[!VAR "GptPrescConf_Alt" = "(number(GptChannelConfigSet/*[1]/GptSTMChannelPrescale_Alternate))"!][!//
[!FOR "x" = "0" TO "num:i(count(GptChannelConfigSet/*[1]/GptChannelConfiguration/*))"!][!//
[!SELECT "GptChannelConfigSet/*[1]/GptChannelConfiguration/*/GptChannelId[.=$x]/.."!][!//
    {
        (Gpt_ChannelType)([!"GptHwChannel"!]), /* GPT physical channel no. */
        (Gpt_ChannelType)(GPT_[!"substring-before(GptHwChannel, '_')"!]_MODULE), /* hardware module ID */
        [!"GptChannelMode"!], /* Timer mode:continous/one-shot */
        (uint8)0, /* not used*/
[!IF "contains(GptHwChannel, 'STM')"!][!//
        (Gpt_PrescaleType)([!"num:dectoint(($GptPrescConf)-1)"!]U), /* STM Clock divider */
[!ELSEIF "contains(GptHwChannel, 'EMIOS')"!][!//
[!IF "node:exists(GptChannelPrescale)"!][!//
        (Gpt_PrescaleType)EMIOS_GPT_LLD_CH_PRES_[!"GptChannelPrescale"!],/* EMIOS Clock divider */
[!ENDIF!][!//
[!ELSE!][!//
        (Gpt_PrescaleType)0, /* Not used */
[!ENDIF!][!//
[!IF "../../../../GptNonAUTOSAR/GptEnableDualClockMode"!][!//
#if GPT_DUAL_CLOCK_MODE==STD_ON
    [!IF "contains(GptHwChannel, 'STM')"!][!//
    (Gpt_PrescaleType)([!"num:dectoint(($GptPrescConf_Alt)-1)"!]U), /* STM Clock Dual Mode divider */
    [!ELSEIF "contains(GptHwChannel, 'EMIOS')"!][!//
        (Gpt_PrescaleType)EMIOS_GPT_LLD_CH_PRES_[!"GptChannelPrescale_Alternate"!],/* EMIOS Clock Dual Mode divider */
    [!ELSE!][!//
        (Gpt_PrescaleType)0, /* Not used */
    [!ENDIF!][!//
#endif
  [!ENDIF!][!//
        [!IF "GptFreezeEnable"!](boolean)TRUE[!ELSE!](boolean)FALSE[!ENDIF!], /* Freeze Enable */
        [!IF "GptEnableWakeup"!](boolean)TRUE[!ELSE!](boolean)FALSE[!ENDIF!], /* Wakeup capability */
       [!IF "(GptNotification != '') and (GptNotification != 'NULL_PTR') and (GptNotification != 'NULL')"!]&[!"GptNotification"!][!ELSE!]NULL_PTR[!ENDIF!], /* Channel notification */
        (Gpt_WakeUpType)([!IF "GptEnableWakeup"!][!SELECT "node:ref(GptWakeupConfiguration/GptWakeupSourceRef)"!][!"EcuMWakeupSourceId"!][!ENDSELECT!][!ELSE!]0[!ENDIF!]) /* Wakeup information */
    }[!//
[!ENDSELECT!][!//
[!IF "$x < num:i(count(GptChannelConfigSet/*[1]/GptChannelConfiguration/*)) - 1"!],[!ENDIF!]
[!ENDFOR!][!//
};

CONST(Gpt_ConfigType, GPT_CONST) Gpt_InitConfigPC =
{
    (Gpt_ChannelType)GPT_CHANNEL_NUM_[!"num:i(@index+1)"!],
    Gpt_InitChannelPC_[!"num:i(@index+1)"!]
};


#define GPT_STOP_SEC_CONST_UNSPECIFIED
/* MISRA-C:2004 19.1 VIOLATION: Refer to REF 1 above*/
/* MISRA-C:2004  19.15 VIOLATION : Refer to REF 2 above*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

#endif  

