/**
    @file    Gpt_PBcfg.c
    @version 2.0.0

    @brief   AUTOSAR Gpt - GPT driver source file.
    @details GPT driver source file, containing C and XPath constructs for generating Gpt
    configuration source file for the Post-build configuration variant.

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

/*lint -save -e961 */
#include "Gpt.h"
/*lint -restore */

#ifndef GPT_PRECOMPILE_SUPPORT

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
/**
@{
@brief   Source file version information
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define GPT_VENDOR_ID_PBCFG_C           43
#define GPT_AR_MAJOR_VERSION_PBCFG_C    3
#define GPT_AR_MINOR_VERSION_PBCFG_C    0
#define GPT_AR_PATCH_VERSION_PBCFG_C    0
#define GPT_SW_MAJOR_VERSION_PBCFG_C    2
#define GPT_SW_MINOR_VERSION_PBCFG_C    0
#define GPT_SW_PATCH_VERSION_PBCFG_C    0
/** @} */

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#if (GPT_VENDOR_ID_PBCFG_C != GPT_VENDOR_ID)
    #error "Gpt_PBcfg.c and Gpt.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((GPT_AR_MAJOR_VERSION_PBCFG_C != GPT_AR_MAJOR_VERSION) || \
         (GPT_AR_MINOR_VERSION_PBCFG_C != GPT_AR_MINOR_VERSION) || \
         (GPT_AR_PATCH_VERSION_PBCFG_C != GPT_AR_PATCH_VERSION))
      #error "AutoSar Version Numbers of Gpt_PBcfg.c and Gpt.h are different"
    #endif
#endif
#if ((GPT_SW_MAJOR_VERSION_PBCFG_C != GPT_SW_MAJOR_VERSION) || \
     (GPT_SW_MINOR_VERSION_PBCFG_C != GPT_SW_MINOR_VERSION) || \
     (GPT_SW_PATCH_VERSION_PBCFG_C != GPT_SW_PATCH_VERSION))
  #error "Software Version Numbers of Gpt_PBcfg.c and Gpt.h are different"
#endif

/**
@brief Gpt user notifications
@remarks Covers GPT087, GPT232, GPT292
*/
extern void SampleAppGptLed(void);

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
/**

@remarks Implements DGPT11026
*/
#define GPT_START_CONFIG_DATA_UNSPECIFIED
/* MISRA-C:2004 19.1 VIOLATION: Refer to REF 1 above*/
/* MISRA-C:2004  19.15 VIOLATION : Refer to REF 2 above*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/
/* there is no need for version checking as the Gpt.h is included here */

STATIC CONST(Gpt_LLD_ChannelConfigType, GPT_CONST) Gpt_InitChannelPB_1[GPT_CHANNEL_NUM_1]=
{
    {
        (Gpt_ChannelType)(PITRTI_CH_0), /* GPT physical channel no. */
        (Gpt_ChannelType)(GPT_PITRTI_MODULE), /* hardware module ID */
        GPT_MODE_CONTINOUS, /* Timer mode:continous/one-shot */
        (uint8)0, /* not used*/
        (Gpt_PrescaleType)0, /* Not used */
        (boolean)TRUE, /* Freeze Enable */
        (boolean)FALSE, /* Wakeup capability */
       &SampleAppGptLed, /* Channel notification */
        (Gpt_WakeUpType)(0) /* Wakeup information */
    }

};

CONST(Gpt_ConfigType, GPT_CONST) GptChannelConfigSet_0 =
{
    (Gpt_ChannelType)GPT_CHANNEL_NUM_1,
    Gpt_InitChannelPB_1
};

#define GPT_STOP_CONFIG_DATA_UNSPECIFIED
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
#endif  /* GPT_PRECOMPILE_SUPPORT */









