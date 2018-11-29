/**
  @file    Adc_PBcfg.c
  @version 2.0.0

  @brief   AUTOSAR Adc - Post Build Configuration source file.
  @details Detailed description.

  Project AUTOSAR 3.0 MCAL
  Platform PA
  Peripheral ADC_10B
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
 * @page misra_violations MISRA-C:2004 violations
 *
 * @section Adc_PBcfg_c_REF_1
 *          Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
 *          '#include'. The usage of the MemMap.h file violates this rule, but this mechanism is
 *          used to properly place into their sections the code and variables.
 *
 * @section Adc_PBcfg_c_REF_2
 *          Violates MISRA 2004 Advisory Rul e 19.15, repeated include file MemMap.h. There are
 *          different kinds of execution code section.
*/
/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Adc.h"

#ifndef ADC_PRECOMPILE_SUPPORT

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/



/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/** @remarks Covers BSW00374, BSW00318 */
#define ADC_VENDOR_ID_PBCFG_C         43
#define ADC_AR_MAJOR_VERSION_PBCFG_C  3
#define ADC_AR_MINOR_VERSION_PBCFG_C  0
#define ADC_AR_PATCH_VERSION_PBCFG_C  0
#define ADC_SW_MAJOR_VERSION_PBCFG_C  2
#define ADC_SW_MINOR_VERSION_PBCFG_C  0
#define ADC_SW_PATCH_VERSION_PBCFG_C  0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and ADC header file are of the same vendor */
#if (ADC_VENDOR_ID_PBCFG_C != ADC_VENDOR_ID)
    #error "Adc_PBcfg.c and Adc.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and ADC header file are of the same Autosar version */
    #if ((ADC_AR_MAJOR_VERSION_PBCFG_C != ADC_AR_MAJOR_VERSION) || \
         (ADC_AR_MINOR_VERSION_PBCFG_C != ADC_AR_MINOR_VERSION) || \
         (ADC_AR_PATCH_VERSION_PBCFG_C != ADC_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of Adc_PBcfg.c and Adc.h are different"
    #endif
#endif
/* Check if source file and ADC header file are of the same Software version */
#if ((ADC_SW_MAJOR_VERSION_PBCFG_C != ADC_SW_MAJOR_VERSION) || \
     (ADC_SW_MINOR_VERSION_PBCFG_C != ADC_SW_MINOR_VERSION) || \
     (ADC_SW_PATCH_VERSION_PBCFG_C != ADC_SW_PATCH_VERSION))
    #error "Software Version Numbers of Adc_PBcfg.c and Adc.h are different"
#endif

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/
/* Configurations */
/* put configuration structures into specified section */

/**
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
'#include' - See @ref Adc_PBcfg_c_REF_1
@note Violates MISRA 2004 Advisory Rule 19.15, repeated include file MemMap.h
- See @ref Adc_PBcfg_c_REF_2
*/
#define ADC_START_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

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


/** @brief total number of groups in Config 1 */
#define ADC_GROUPS_1  1

/** @brief Adc Notifications*/


extern VAR(Adc_ValueGroupType, AUTOMATIC) AdcResultBufferPointer[ADC_CFGSET1_GROUP_0_CHANNELS];

/** @brief Adc Result Buffer RAM initializations*/
STATIC P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) ADC_ResultsBufferPtr[ADC_MAX_GROUPS] =
{
 
  NULL_PTR
};



/* Group Assignments ADC0 - Configuration 1 */
STATIC CONST(Adc_ChannelType, ADC_CONST) ADC_Group0_Assignment_PB_0_1[ADC_CFGSET1_GROUP_0_CHANNELS] =
{
    0U
};






/** @brief definition of Hw units Configuration 1 */
STATIC CONST(Adc_LLD_HWUnitConfiguration, ADC_CONST) Adc_HWUnit_CfgPB_1[1] =
{
  /* Hardware Unit 0 */
  {
    (ADC_ADCn_EN | ADC_ADCn_CLK_PS_31),
    #if (ADC_CALIBRATION == STD_ON)
        ADC_CAL_ON /* calibration is/isn't performed  */
    #endif
  }
};





/** @brief definition of channels ADC0 - Configuration 1 */
STATIC CONST(Adc_LLD_ChannelConfiguration, ADC_CONST) Adc_Channels_CfgPB_0_1[1] = /* array of conversion command messages */
{
  /* Hardware Unit 0  --  AN_0 */
  {
        (uint32)(ADC_CONV_COM_BN0  | ADC_CONV_COM_CAL  | ADC_128_CLOCK_CYCLES | ADC_CONV_COM_FMT_RJU | ((uint32)AN_0<<8)), /* Adc channel,s command */
        (Adc_ResolutionType)EQADC_BITS_RESOLUTION_12 /* 12 Bit resolution */
            
  }
};





/** @brief definition of ch's pointer for configuration 1 */
STATIC P2CONST(Adc_LLD_ChannelConfiguration, AUTOMATIC, ADC_APPL_DATA) Adc_Channels_CfgPB_1[ADC_MAX_HW_UNITS] =
{
  Adc_Channels_CfgPB_0_1,
  NULL_PTR
};




/** @brief definition of groups for configuration 1 */
STATIC CONST(Adc_LLD_GroupConfiguration, ADC_CONST) Adc_Groups_CfgPB_1[ADC_GROUPS_1] =
{
  /* Group0 -- Hardware Unit 0 */
  {
    (Adc_HwUnitType)0,
    ADC_ACCESS_MODE_SINGLE,
    ADC_CONV_MODE_ONESHOT,
        ADC_ISR_RIGHT_ALIGH, /* Right Align */
        #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
    ADC_GROUP_PRIORITY(0U),
    #endif
    ADC_GROUP_REPL_ABORT_RESTART,
    ADC_TRIGG_SRC_SW,
    #if (STD_ON==ADC_HW_TRIGGER_API)
    ADC_HW_TRIG_BOTH_EDGES,
    (Adc_HwTriggerTimerType)PIT0,
    #endif
    #if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        NULL_PTR,
        #endif
    0U,  /* CFIFO used for group */
    ADC_ResultsBufferPtr,
    ADC_STREAM_BUFFER_LINEAR,
    ADC_STREAMING_NUM_SAMPLES(1),
    ADC_Group0_Assignment_PB_0_1,
    (Adc_ChannelType)ADC_CFGSET1_GROUP_0_CHANNELS
  }
};




/* Configuration structure 1 */
CONST(Adc_ConfigType, ADC_CONST) AdcConfigSet_0 =
{
    Adc_HWUnit_CfgPB_1, /* pointer to Hw unit configurations */
    Adc_Groups_CfgPB_1, /* pointer to group configurations */
    Adc_Channels_CfgPB_1, /* pointer to channel configurations */
    (Adc_GroupType)ADC_GROUPS_1, /* total number of groups */
    #if(ADC_HW_TRIGGER_API == STD_ON)
      (uint8)0x5, /* low 8 bits of EQADC_ETDFR, minimum system clock count to recognize a hw trigger is 2^5+1 */
    #endif
        /* Miscellaneous configuration parameters. - Adc_LLD_MultiConfig */
    {
      ADC_INTERRUPT, /* Interrupt driven Mode */
      1U, /* the number of the maximum groups in the current configuration */
      1U, /* depth of the queue */                           
    {
      1U, /* number of channels of the hw unit 0 */
      0U /* number of channels of the hw unit 1 */
    },
    {      
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U
      
    },
    {
      (uint8)STD_ON, /* ADC_HW_UNIT_0 - ON/OFF */
      (uint8)STD_OFF /* ADC_HW_UNIT_1 - ON/OFF */
    }
    }
};

/**
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
'#include' - See @ref Adc_PBcfg_c_REF_1
@note Violates MISRA 2004 Advisory Rule 19.15, repeated include file MemMap.h
- See @ref Adc_PBcfg_c_REF_2
*/
#define ADC_STOP_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"
/**
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
'#include' - See @ref Adc_PBcfg_c_REF_1
*/
/*lint -restore */
#endif /* #ifndef ADC_PRECOMPILE_SUPPORT */


