[!CODE!][!//
/**
    @file    Adc_Cfg.c
    @version 2.0.0

    @brief   AUTOSAR Adc - Pre-Compile configurations for ADC driver.
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
 * @page    misra_violations MISRA-C:2004 violations
 *
 * @section Adc_Cgf_c_REF_1
 *          Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
 *          '#include'. The usage of the MemMap.h file violates this rule, but this mechanism is
 *          used to properly place into their sections the code and variables.
 *
 * @section Adc_Cgf_c_REF_2
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

#ifdef ADC_PRECOMPILE_SUPPORT

[!NOCODE!][!//
[!INCLUDE "Adc_VersionCheck_Src.m"!][!//
[!ENDNOCODE!][!//

[!NOCODE!][!//
[!INCLUDE "Adc_RegOperations.m"!][!//
[!ENDNOCODE!][!//


/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/** @remarks Covers BSW00374, BSW00318 */
#define ADC_VENDOR_ID_CFG_C         43
#define ADC_AR_MAJOR_VERSION_CFG_C  3
#define ADC_AR_MINOR_VERSION_CFG_C  0
#define ADC_AR_PATCH_VERSION_CFG_C  0
#define ADC_SW_MAJOR_VERSION_CFG_C  2
#define ADC_SW_MINOR_VERSION_CFG_C  0
#define ADC_SW_PATCH_VERSION_CFG_C  0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and ADC header file are of the same vendor */
#if (ADC_VENDOR_ID_CFG_C != ADC_VENDOR_ID)
    #error "Adc_Cfg.c and Adc.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and ADC header file are of the same Autosar version */
    #if ((ADC_AR_MAJOR_VERSION_CFG_C != ADC_AR_MAJOR_VERSION) || \
         (ADC_AR_MINOR_VERSION_CFG_C != ADC_AR_MINOR_VERSION) || \
         (ADC_AR_PATCH_VERSION_CFG_C != ADC_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of Adc_Cfg.c and Adc.h are different"
    #endif
#endif
/* Check if source file and ADC header file are of the same Software version */
#if ((ADC_SW_MAJOR_VERSION_CFG_C != ADC_SW_MAJOR_VERSION) || \
     (ADC_SW_MINOR_VERSION_CFG_C != ADC_SW_MINOR_VERSION) || \
     (ADC_SW_PATCH_VERSION_CFG_C != ADC_SW_PATCH_VERSION))
    #error "Software Version Numbers of Adc_Cfg.c and Adc.h are different"
#endif

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/
/**
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
'#include' - See @ref Adc_Cfg_c_REF_1
@note Violates MISRA 2004 Advisory Rule 19.15, repeated include file MemMap.h
- See @ref Adc_Cfg_c_REF_2
*/
/* Configurations */
/* put configuration structures into specified section */
#define ADC_START_SEC_CONST_UNSPECIFIED
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

/** @brief Adc Notifications */
[!LOOP "AdcConfigSet/*[1]/AdcHwUnit/*/AdcGroup/*"!][!//
[!IF "../../../../../../AdcGeneral/AdcGrpNotifCapability = 'true'"!][!//
[!IF "AdcNotification != 'NULL_PTR'"!] extern void [!"AdcNotification"!](void);[!ENDIF!]
[!ENDIF!][!//
[!ENDLOOP!][!//

[!LOOP "AdcConfigSet/*[1]/AdcHwUnit/*/AdcGroup/*"!][!//
[!IF "AdcGroupAccessMode = 'ADC_ACCESS_MODE_SINGLE'"!][!//
extern VAR(Adc_ValueGroupType, AUTOMATIC) [!"AdcResultBufferPointer"!][ADC_CFGSET1_GROUP_[!"AdcGroupId"!]_CHANNELS];
[!ELSE!][!//
extern VAR(Adc_ValueGroupType, AUTOMATIC) [!"AdcResultBufferPointer"!][ADC_CFGSET1_GROUP_[!"AdcGroupId"!]_CHANNELS][[!"AdcStreamingNumSamples"!]];
[!ENDIF!][!//
[!ENDLOOP!][!//

/** @brief total number of groups in Config0 */
#define ADC_GROUPS                [!"num:i(count(AdcConfigSet/*[1]/AdcHwUnit/*/AdcGroup/*))"!]

/** @brief Adc Result Buffer RAM initializations */
STATIC P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) ADC_ResultsBufferPtr[ADC_GROUPS] =
{
[!VAR "MAX_NUM"="count(AdcConfigSet/*[1]/AdcHwUnit/*/AdcGroup/*)"!][!//
[!VAR "CRT_NUM"="1"!][!//
[!LOOP "AdcConfigSet/*[1]/AdcHwUnit/*/AdcGroup/*"!][!//
  NULL_PTR[!IF "$CRT_NUM<$MAX_NUM"!],[!ELSE!][!ENDIF!]
[!VAR "CRT_NUM"="$CRT_NUM+1"!][!//
[!ENDLOOP!][!//
};

[!LOOP "AdcConfigSet/*[1]/AdcHwUnit/*/AdcGroup/*"!][!//
[!IF "../../AdcHwUnitId = '0'"!][!//
/** @brief Group Assignments ADC0 */
STATIC CONST(Adc_ChannelType, ADC_CONST) ADC_Group[!"AdcGroupId"!]_Assignment_PC_0[ADC_CFGSET1_GROUP_[!"AdcGroupId"!]_CHANNELS] =
{
[!VAR "MAX_COUNT" = "count(AdcGroupDefinition/*)-1"!][!//
[!VAR "CRT_COUNT" = "0"!][!//
[!LOOP "AdcGroupDefinition/*"!][!//
[!VAR "CurrAdcChannel" = "."!][!//
[!VAR "CurrAdcChannel1" = "substring-after(substring-after(substring-after(substring-after(substring-after($CurrAdcChannel,'/'),'/'),'/'),'/'),'/')"!][!//
[!VAR "INDEX" = "0"!][!//
[!LOOP "../../../../AdcChannel/*"!][!//
[!IF "@name = $CurrAdcChannel1"!][!//
    [!"num:i($INDEX)"!]U[!IF "$CRT_COUNT < $MAX_COUNT"!],[!ELSE!][!ENDIF!]
[!ENDIF!][!//
[!VAR "INDEX" = "$INDEX + 1"!][!//
[!ENDLOOP!][!//
[!VAR "CRT_COUNT" = "$CRT_COUNT + 1"!][!//
[!ENDLOOP!][!//
};
[!ENDIF!][!//
[!ENDLOOP!][!//

[!LOOP "AdcConfigSet/*[1]/AdcHwUnit/*/AdcGroup/*"!][!//
[!IF "../../AdcHwUnitId = '1'"!][!//
/** @brief Group Assignments ADC1 */
STATIC CONST(Adc_ChannelType, ADC_CONST) ADC_Group[!"AdcGroupId"!]_Assignment_PC_1[ADC_CFGSET1_GROUP_[!"AdcGroupId"!]_CHANNELS] =
{
[!VAR "MAX_COUNT" = "count(AdcGroupDefinition/*)-1"!][!//
[!VAR "CRT_COUNT" = "0"!][!//
[!LOOP "AdcGroupDefinition/*"!][!//
[!VAR "CurrAdcChannel" = "."!][!//
[!VAR "CurrAdcChannel1" = "substring-after(substring-after(substring-after(substring-after(substring-after($CurrAdcChannel,'/'),'/'),'/'),'/'),'/')"!][!//
[!VAR "INDEX" = "0"!][!//
[!LOOP "../../../../AdcChannel/*"!][!//
[!IF "@name = $CurrAdcChannel1"!][!//
    [!"num:i($INDEX)"!]U[!IF "$CRT_COUNT<$MAX_COUNT"!],[!ELSE!][!ENDIF!]
[!ENDIF!][!//
[!VAR "INDEX" = "$INDEX + 1"!][!//
[!ENDLOOP!][!//
[!VAR "CRT_COUNT" = "$CRT_COUNT + 1"!][!//
[!ENDLOOP!][!//
};
[!ENDIF!][!//
[!ENDLOOP!][!//

[!VAR "MAX_COUNT"="num:i(count(AdcConfigSet/*[1]/AdcHwUnit/*))"!][!//
/** @brief definition of Hw units */
STATIC CONST(Adc_LLD_HWUnitConfiguration, ADC_CONST) Adc_HWUnit_CfgPC[[!"$MAX_COUNT"!]] =
{
[!VAR "MAX_COUNT"="count(AdcConfigSet/*[1]/AdcHwUnit/*) - 1"!][!//
[!VAR "CRT_COUNT"="0"!][!//
[!LOOP "AdcConfigSet/*[1]/AdcHwUnit/*"!][!//
[!CODE!][!//
  /* Hardware Unit [!"AdcHwUnitId"!] */
  {
    (ADC_ADCn_EN[!IF "AdcExternalMultiplexing = 'true'"!] | ADC_ADCn_EMUX[!ENDIF!][!IF "AdcClockSource = '0'"!] | ADC_ADCn_CLK_PS_[!"AdcPrescale"!][!ELSE!] | ADCn_CLK_SEL[!ENDIF!]),
    #if (ADC_CALIBRATION == STD_ON)
        [!IF "AdcCalibration"!]ADC_CAL_ON[!ELSE!]ADC_CAL_OFF[!ENDIF!] /* calibration is/isn't performed  */
    #endif
  }[!IF "$CRT_COUNT<$MAX_COUNT"!],[!ELSE!][!ENDIF!]
[!VAR "CRT_COUNT"="$CRT_COUNT+1"!][!//
[!ENDCODE!][!//
[!ENDLOOP!][!//
};

[!VAR "ADC0_EXISTS" = "0"!][!//
[!VAR "ADC1_EXISTS" = "0"!][!//
[!LOOP "AdcConfigSet/*[1]/AdcHwUnit/*"!][!//
[!IF "AdcHwUnitId = '0'"!][!//
[!VAR "ADC0_EXISTS" = "1"!][!//
[!ENDIF!][!//
[!IF "AdcHwUnitId = '1'"!][!//
[!VAR "ADC1_EXISTS" = "1"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//


[!IF "num:i($ADC0_EXISTS) = '1'"!]
[!VAR "MAX_COUNT"="num:i(count(AdcConfigSet/*[1]/AdcHwUnit/*[AdcHwUnitId=0]/AdcChannel/*))"!][!//
/** @brief definition of channels ADC0*/
STATIC CONST(Adc_LLD_ChannelConfiguration, ADC_CONST) Adc_Channels_CfgPC_0[[!"$MAX_COUNT"!]] = /* array of conversion command messages */
{
[!VAR "MAX_COUNT"="count(AdcConfigSet/*[1]/AdcHwUnit/*[AdcHwUnitId=0]/AdcChannel/*)-1"!][!//
[!VAR "CRT_COUNT"="0"!][!//
[!LOOP "AdcConfigSet/*[1]/AdcHwUnit/*/AdcChannel/*"!][!//
[!IF "../../AdcHwUnitId = '0'"!][!//
  /* Hardware Unit [!"../../AdcHwUnitId"!]  --  [!"AdcHwChannel"!] */
  {
        (uint32)(ADC_CONV_COM_BN0 [!IF "AdcChannelCalibration = 'true'"!] | ADC_CONV_COM_CAL [!ENDIF!] | [!IF "AdcChannelSampTime = '0'"!]ADC_2_CLOCK_CYCLES[!ELSEIF "AdcChannelSampTime = '1'"!]ADC_8_CLOCK_CYCLES[!ELSEIF "AdcChannelSampTime = '2'"!]ADC_64_CLOCK_CYCLES[!ELSE!]ADC_128_CLOCK_CYCLES[!ENDIF!] | ADC_CONV_COM_FMT_RJU | ((uint32)[!"AdcHwChannel"!]<<8)), /* Adc channel,s command */
    [!IF "AdcChannelResolution = '8'"!][!//
    (Adc_ResolutionType)EQADC_BITS_RESOLUTION_8 /* 8 Bit resolution */
    [!ELSE!][!IF "AdcChannelResolution = '10'"!][!//
    (Adc_ResolutionType)EQADC_BITS_RESOLUTION_10 /* 10 Bit resolution */
    [!ELSE!][!IF "AdcChannelResolution = '12'"!][!//
    (Adc_ResolutionType)EQADC_BITS_RESOLUTION_12 /* 12 Bit resolution */
    [!ENDIF!][!//
    [!ENDIF!][!//
    [!ENDIF!]
  }[!IF "$CRT_COUNT<$MAX_COUNT"!],[!ELSE!][!ENDIF!]
[!VAR "CRT_COUNT"="$CRT_COUNT+1"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
};
[!ENDIF!][!//


[!IF "num:i($ADC1_EXISTS) = '1'"!]
[!VAR "MAX_COUNT"="num:i(count(AdcConfigSet/*[1]/AdcHwUnit/*[AdcHwUnitId=1]/AdcChannel/*))"!][!//
/** @brief definition of channels ADC1*/
STATIC CONST(Adc_LLD_ChannelConfiguration, ADC_CONST) Adc_Channels_CfgPC_1[[!"$MAX_COUNT"!]] = /* array of conversion command messages */
{
[!VAR "MAX_COUNT"="count(AdcConfigSet/*[1]/AdcHwUnit/*[AdcHwUnitId=1]/AdcChannel/*)-1"!][!//
[!VAR "CRT_COUNT"="0"!][!//
[!LOOP "AdcConfigSet/*[1]/AdcHwUnit/*/AdcChannel/*"!][!//
[!IF "../../AdcHwUnitId = '1'"!][!//
  /* Hardware Unit [!"../../AdcHwUnitId"!]  --  [!"AdcHwChannel"!] */
  {
        (uint32)(ADC_CONV_COM_BN1 [!IF "AdcChannelCalibration = 'true'"!] | ADC_CONV_COM_CAL [!ENDIF!] | [!IF "AdcChannelSampTime = '0'"!]ADC_2_CLOCK_CYCLES[!ELSEIF "AdcChannelSampTime = '1'"!]ADC_8_CLOCK_CYCLES[!ELSEIF "AdcChannelSampTime = '2'"!]ADC_64_CLOCK_CYCLES[!ELSE!]ADC_128_CLOCK_CYCLES[!ENDIF!] | ADC_CONV_COM_FMT_RJU | ((uint32)[!"AdcHwChannel"!]<<8)), /* Adc channel,s command */
    [!IF "AdcChannelResolution = '8'"!][!//
    (Adc_ResolutionType)EQADC_BITS_RESOLUTION_8 /* 8 Bit resolution */
    [!ELSE!][!IF "AdcChannelResolution = '10'"!][!//
    (Adc_ResolutionType)EQADC_BITS_RESOLUTION_10 /* 10 Bit resolution */
    [!ELSE!][!IF "AdcChannelResolution = '12'"!][!//
    (Adc_ResolutionType)EQADC_BITS_RESOLUTION_12 /* 12 Bit resolution */
    [!ENDIF!][!//
    [!ENDIF!][!//
    [!ENDIF!]
  }[!IF "$CRT_COUNT<$MAX_COUNT"!],[!ELSE!][!ENDIF!]
[!VAR "CRT_COUNT"="$CRT_COUNT+1"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
};
[!ENDIF!][!//

/** @brief definition of ch's pointer*/
STATIC P2CONST(Adc_LLD_ChannelConfiguration, AUTOMATIC, ADC_APPL_DATA) Adc_Channels_CfgPC[ADC_MAX_HW_UNITS] =
{
[!IF "AdcConfigSet/*[1]/AdcHwUnit/*/AdcHwUnitId = '0'"!][!//
  Adc_Channels_CfgPC_0,
[!ELSE!][!//
  NULL_PTR,
[!ENDIF!][!//
[!IF "AdcConfigSet/*[1]/AdcHwUnit/*/AdcHwUnitId = '1'"!][!//
  Adc_Channels_CfgPC_1
[!ELSE!][!//
  NULL_PTR
[!ENDIF!][!//
};


[!VAR "LoopVar"="0"!][!//

/** @brief definition of groups */
STATIC CONST(Adc_LLD_GroupConfiguration, ADC_CONST) Adc_Groups_CfgPC[ADC_GROUPS] =
{
[!FOR "x" = "0" TO "num:i(count(AdcConfigSet/*[1]/AdcHwUnit/*/AdcGroup/*)-1)"!][!//
[!LOOP "AdcConfigSet/*[1]/AdcHwUnit/*/AdcGroup/*"!][!//
[!VAR "Loop"="num:i($LoopVar)"!][!//
[!IF "AdcGroupId = $Loop"!][!//
  /* Group[!"AdcGroupId"!] -- Hardware Unit [!"../../AdcHwUnitId"!] */
  {
    (Adc_HwUnitType)[!"../../AdcHwUnitId"!], /* Hardware unit configured */
    [!"AdcGroupAccessMode"!], /* Access mode */
    [!"AdcGroupConversionMode"!], /* Conversion mode */
    [!IF "AdcGroupISRAlignSamples = 'true'"!][!//
    ADC_ISR_RIGHT_ALIGH, /* Right Align */
    [!ELSE!][!//
    ADC_ISR_NOT_RIGHT_ALIGH, /* NOT Align */
    [!ENDIF!][!//
    #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
    [!IF "../../../../../AdcGeneral/AdcPriorityImplementation != 'ADC_PRIORITY_NONE'"!]ADC_GROUP_PRIORITY([!"AdcGroupPriority"!]),[!ELSE!]ADC_GROUP_PRIORITY(0U),[!ENDIF!]
    #endif
    ADC_GROUP_REPL_ABORT_RESTART,
    [!"AdcGroupTriggSrc"!],
    #if (STD_ON==ADC_HW_TRIGGER_API)
    [!IF "(../../../../../../AdcGeneral/AdcHwTriggerApi = 'true') and (AdcGroupTriggSrc = 'ADC_TRIGG_SRC_HW')"!][!"AdcHwTrigSignal"!],[!ELSE!]ADC_HW_TRIG_BOTH_EDGES,[!ENDIF!]
    (Adc_HwTriggerTimerType)[!"AdcHwTrigSrc"!],
    #endif
    #if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
    [!IF "../../../../../../AdcGeneral/AdcGrpNotifCapability = 'true'"!][!//
    [!IF "AdcNotification != 'NULL_PTR'"!]&[!"AdcNotification"!],[!ELSE!][!"AdcNotification"!],[!ENDIF!]
    [!ELSE!]NULL_PTR,
    [!ENDIF!][!//
    #endif
    [!"substring-after(AdcGroupFifo,'ADC_FIFO_')"!]U,  /* CFIFO used for group */
    ADC_ResultsBufferPtr,
    [!"AdcStreamingBufferMode"!],
    ADC_STREAMING_NUM_SAMPLES([!"AdcStreamingNumSamples"!]),
    [!IF "../../AdcHwUnitId = '0' "!]ADC_Group[!"AdcGroupId"!]_Assignment_PC_0[!ELSE!]ADC_Group[!"AdcGroupId"!]_Assignment_PC_1[!ENDIF!],
    (Adc_ChannelType)ADC_CFGSET1_GROUP_[!"AdcGroupId"!]_CHANNELS
[!ENDIF!][!//
[!ENDLOOP!][!//
  }[!IF "$x < (count(AdcConfigSet/*[1]/AdcHwUnit/*/AdcGroup/*)-1)"!],[!ELSE!][!ENDIF!]
[!VAR "LoopVar"="$LoopVar + 1"!][!//
[!ENDFOR!][!//
};


/** @brief Configuration structure */
CONST(Adc_ConfigType, ADC_CONST) Adc_ConfigPC =
{
    Adc_HWUnit_CfgPC, /* pointer to Hw unit configurations */
    Adc_Groups_CfgPC, /* pointer to group configurations */
    Adc_Channels_CfgPC, /* pointer to channel configurations */
    (Adc_GroupType)ADC_GROUPS, /* total number of groups */
    #if(ADC_HW_TRIGGER_API == STD_ON)
      (uint8)[!"num:inttohex(AdcConfigSet/*[1]/AdcDigitalFilterLength)"!], /* low 8 bits of EQADC_ETDFR, minimum system clock count to recognize a hw trigger is 2^[!"num:i(AdcConfigSet/*[1]/AdcDigitalFilterLength)"!]+1 */
    #endif
    /* Miscellaneous configuration parameters. - Adc_LLD_MultiConfig */
    {
  [!IF "AdcConfigSet/*[1]/AdcGeneric/AdcTransferType = 'ADC_DMA'"!][!//
    [!"AdcConfigSet/*[1]/AdcGeneric/AdcTransferType"!], /* DMA driven mode.  */
  [!ELSE!][!//
    ADC_INTERRUPT, /* Interrupt driven Mode */
  [!ENDIF!][!//
    [!"num:i(count(AdcConfigSet/*[1]/AdcHwUnit/*/AdcGroup/*))"!]U, /* the number of the maximum groups in the current configuration */
      [!"AdcConfigSet/*[1]/AdcGeneric/AdcPriorityQueueMaxDepth"!]U, /* depth of the queue */ [!//
  [!VAR "channels_hw_unit0" = "0"!][!//
  [!VAR "channels_hw_unit1" = "0"!][!//
  [!LOOP "AdcConfigSet/*[1]/AdcHwUnit/*/AdcChannel/*"!][!//
    [!IF "../../AdcHwUnitId = '0'"!][!//
      [!VAR "channels_hw_unit0" = "$channels_hw_unit0 + 1"!][!//
    [!ENDIF!][!//
    [!IF "../../AdcHwUnitId = '1'"!][!//
      [!VAR "channels_hw_unit1" = "$channels_hw_unit1 + 1"!][!//
    [!ENDIF!][!//
  [!ENDLOOP!]
    {
      [!"num:i($channels_hw_unit0)"!]U, /* number of channels of the hw unit 0 */
      [!"num:i($channels_hw_unit1)"!]U  /* number of channels of the hw unit 1 */
    },
    {[!//
      [!IF "AdcConfigSet/*[1]/AdcGeneric/AdcTransferType = 'ADC_DMA'"!]
        [!"ecu:get('AdcDMAeQADCA_FISR0_CFFF0')"!]U, /* the EQADC_A_CFIFI0_DMA_CHANNEL number */
        [!"ecu:get('AdcDMAeQADCA_FISR0_RFDF0')"!]U, /* the EQADC_A_RFIFI0_DMA_CHANNEL number */
        [!"ecu:get('AdcDMAeQADCA_FISR1_CFFF1')"!]U, /* the EQADC_A_CFIFI1_DMA_CHANNEL number */
        [!"ecu:get('AdcDMAeQADCA_FISR1_RFDF1')"!]U, /* the EQADC_A_RFIFI1_DMA_CHANNEL number */
        [!"ecu:get('AdcDMAeQADCA_FISR2_CFFF2')"!]U, /* the EQADC_A_CFIFI2_DMA_CHANNEL number */
        [!"ecu:get('AdcDMAeQADCA_FISR2_RFDF2')"!]U, /* the EQADC_A_RFIFI2_DMA_CHANNEL number */
        [!"ecu:get('AdcDMAeQADCA_FISR3_CFFF3')"!]U, /* the EQADC_A_CFIFI3_DMA_CHANNEL number */
        [!"ecu:get('AdcDMAeQADCA_FISR3_RFDF3')"!]U, /* the EQADC_A_RFIFI3_DMA_CHANNEL number */
        [!"ecu:get('AdcDMAeQADCA_FISR4_CFFF4')"!]U, /* the EQADC_A_CFIFI4_DMA_CHANNEL number */
        [!"ecu:get('AdcDMAeQADCA_FISR4_RFDF4')"!]U, /* the EQADC_A_RFIFI4_DMA_CHANNEL number */
        [!"ecu:get('AdcDMAeQADCA_FISR5_CFFF5')"!]U, /* the EQADC_A_CFIFI5_DMA_CHANNEL number */
        [!"ecu:get('AdcDMAeQADCA_FISR5_RFDF5')"!]U /* the EQADC_A_RFIFI5_DMA_CHANNEL number */[!//
      [!ELSE!]
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U
      [!ENDIF!]
    },
    {
      [!IF "AdcConfigSet/*[1]/AdcHwUnit/*/AdcHwUnitId = '0'"!](uint8)STD_ON[!ELSE!](uint8)STD_OFF[!ENDIF!], /* ADC_HW_UNIT_0 - ON/OFF */
      [!IF "AdcConfigSet/*[1]/AdcHwUnit/*/AdcHwUnitId = '1'"!](uint8)STD_ON[!ELSE!](uint8)STD_OFF[!ENDIF!] /* ADC_HW_UNIT_1 - ON/OFF */
    }
    }
};


[!ENDCODE!][!//
/**
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
'#include' - See @ref Adc_Cfg_c_REF_1
@note Violates MISRA 2004 Advisory Rule 19.15, repeated include file MemMap.h
- See @ref Adc_Cfg_c_REF_2
*/
/* put Adc_ConfigPC structure into specified section */
#define ADC_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#endif  /* ADC_PRECOMPILE_SUPPORT */

