/*!
 * @addtogroup ADC
 *@{
 */
/**
    @file    Adc_Cfg.h
    @version 2.0.0

    @brief   AUTOSAR Adc - module interface.
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
 * @section Adc_Cfg_h_REF_1
 *          Violates MISRA 2004 Advisory Rul e 19.7, use of function like macro. This violation is
 *          due to function like macros defined for register operations. Function like macros are
 *          used to reduce code complexity.
 *
 * @section Adc_Cfg_h_REF_2
 *          Violates MISRA 2004 Advisory Rul e 19.1, only preprocessor statements and comments before
 *          '#include'. The usage of the MemMap.h file violates this rule, but this mechanism is
 *          used to properly place into their sections the code and variables.
*/
#ifndef ADC_CFG_H
#define ADC_CFG_H

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief   The following definitions SHOULD be before the inclusion of the EQADC_LLD_CfgEx.h header
 *          file, cause in this file some conditional compilation flags are defined, and in the
 *          EQADC_LLD_CfgEx.h file some structure members are guarded by these defines.
 *          According to this, these definitions should be predefined before the inclusion of the mentioned
 *          header file, in order to correctly define the ADC driver internal structures.
 *          Due to the fact that these structures are Low Level Driver related, they must stay in the
 *          EQADC_LLD_CfgEx.h file.
 */

/**
 * @brief   Adds/removes (STD_ON/STD_OFF) the services Adc_EnableHardwareTrigger()
 *          and Adc_DisableHardwareTrigger() from the code.
 *
 * @remarks Implements DADC08007.
 */
#define ADC_HW_TRIGGER_API [!IF "AdcGeneral/AdcHwTriggerApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/**
 * @brief   group notification mechanism is/isn't (STD_ON/STD_OFF) available at runtime
 *
 * @remarks Implements DADC08003.
 */
#define ADC_GRP_NOTIF_CAPABILITY [!IF "AdcGeneral/AdcGrpNotifCapability"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/**
@{
@brief   Prioritization mechanism
@details Type of prioritization mechanism ADC_PRIORITY_HW, ADC_PRIORITY_HW_SW and ADC_PRIORITY_NONE
*/
#define ADC_PRIORITY_HW 0U
#define ADC_PRIORITY_HW_SW 1U
#define ADC_PRIORITY_NONE 2U
/**@}*/

#define ADC_PRIORITY_IMPLEMENTATION [!"AdcGeneral/AdcPriorityImplementation"!]

#define ADC_DMA 0U
#define ADC_INTERRUPT 1U

/**
 * @brief   adds/removes (STD_ON/STD_OFF) the powerup calibration code to/from Adc_Init function.
 */
#define ADC_CALIBRATION                     ([!IF "AdcGeneral/AdcCalibrationApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

/**
 * @brief   ADC timeout value used to wait while the FIFO's status is updating for the EOQ or to read the result or to disable the FIFO.
 */
#define ADC_TIMEOUT_COUNTER                 [!"num:inttohex(AdcGeneral/AdcTimeout,4)"!]U

[!NOCODE!]
[!VAR "DMA_ENABLED"="0"!]
[!LOOP "AdcConfigSet/*"!][!//
[!IF "AdcGeneric/AdcTransferType = 'ADC_DMA'"!][!//
[!VAR "DMA_ENABLED"="1"!]
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!][!//
[!IF "$DMA_ENABLED = 1"!][!//
#define ADC_DMA_SUPPORTED /* DMA driven mode.  */
[!ENDIF!][!//

[!SELECT "as:modconf('Resource')[1]"!][!//
[!IF "(ResourceGeneral/ResourceSubderivative = 'mpc5674fmvva264_tepbga516') or [!//
      (ResourceGeneral/ResourceSubderivative = 'mpc5674fmvza264_tepbga324') or [!//
      (ResourceGeneral/ResourceSubderivative = 'mpc5673fmvva264_tepbga516') or [!//
      (ResourceGeneral/ResourceSubderivative = 'mpc5673fmvza264_tepbga324') or [!//
      (ResourceGeneral/ResourceSubderivative = 'mpc5673l_tepbga324') or [!//
      (ResourceGeneral/ResourceSubderivative = 'mpc5671l_tepbga324')"!][!//
/** @brief  Defines the IP version for Mamba */
#define IPV_EQADC 1000700UL
/** @brief max number of hw units - is 4 on Mamba */
#define ADC_MAX_HW_UNITS 4U

[!ELSEIF "(ResourceGeneral/ResourceSubderivative = 'mpc5644a_lqfp176') or [!//
          (ResourceGeneral/ResourceSubderivative = 'mpc5644a_lbga208') or [!//
          (ResourceGeneral/ResourceSubderivative = 'mpc5644a_pbga324') or [!//
          (ResourceGeneral/ResourceSubderivative = 'spc564a_lqfp176') or [!//
          (ResourceGeneral/ResourceSubderivative = 'spc564a_lbga208') or [!//
          (ResourceGeneral/ResourceSubderivative = 'spc564a_pbga324')"!][!//
/** @brief  Defines the IP version for Andorra4M */
#define IPV_EQADC 1001101UL
/** @brief max number of hw units - is 2 on Andorra4M */
#define ADC_MAX_HW_UNITS 2U

[!ELSEIF "(ResourceGeneral/ResourceSubderivative = 'mpc5634m_bga208') or [!//
          (ResourceGeneral/ResourceSubderivative = 'mpc5634m_qfp144') or [!//
          (ResourceGeneral/ResourceSubderivative = 'mpc5634m_qfp176') or [!//
          (ResourceGeneral/ResourceSubderivative = 'spc563xm64_qfp144') or [!//
          (ResourceGeneral/ResourceSubderivative = 'spc563xm64_qfp176')"!][!//
/** @brief  Defines the IP version for Monaco 1.5M */
#define IPV_EQADC 1001000UL
/** @brief max number of hw units - is 2 on Monaco 1.5M */
#define ADC_MAX_HW_UNITS 2U

[!ENDIF!][!//
[!ENDSELECT!][!//

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "EQADC_LLD_CfgEx.h"

[!NOCODE!][!//
[!INCLUDE "Adc_VersionCheck_Inc.m"!][!//
[!ENDNOCODE!][!//

[!NOCODE!][!//
[!INCLUDE "Adc_RegOperations.m"!][!//
[!ENDNOCODE!][!//

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** @remarks Covers BSW00374, BSW00379, BSW00318 */
#define ADC_VENDOR_ID_CFG            43
#define ADC_AR_MAJOR_VERSION_CFG     3
#define ADC_AR_MINOR_VERSION_CFG     0
#define ADC_AR_PATCH_VERSION_CFG     0
#define ADC_SW_MAJOR_VERSION_CFG     2
#define ADC_SW_MINOR_VERSION_CFG     0
#define ADC_SW_PATCH_VERSION_CFG     0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/
/** @brief Queue depth for the hardware triggered group */
#define ADC_QUEUE_HW 1U

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

[!IF "IMPLEMENTATION_CONFIG_VARIANT='VariantPreCompile'"!]#define ADC_PRECOMPILE_SUPPORT[!ENDIF!]

/* Pre-compile configuration parameters - Autosar */
/**
 * @brief   development error detection enabled/disabled (STD_ON/STD_OFF)
 *
 * @remarks Implements DADC08002.
 */
#define ADC_DEV_ERROR_DETECT                [!IF "AdcGeneral/AdcDevErrorDetect"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/**
 * @brief   Add/remove (STD_ON/STD_OFF) the service Adc_GetVersionInfo()
 *          from the code.
 *
 * @remarks Implements DADC08004.
 */
#define ADC_VERSION_INFO_API                [!IF "AdcGeneral/AdcVersionInfoApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/**
 * @brief   Add/remove (STD_ON/STD_OFF) the service Adc_DeInit() from the
 *          code.
 *
 * @remarks Implements DADC08005.
 */
#define ADC_DEINIT_API                      [!IF "AdcGeneral/AdcDeInitApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/**
 * @brief   Add/remove (STD_ON/STD_OFF) the services
 *          Adc_StartGroupConversion()and Adc_StopGroupConversion() from
 *          the code.
 *
 * @remarks Implements DADC08006.
 */
#define ADC_ENABLE_START_STOP_GROUP_API     [!IF "AdcGeneral/AdcEnableStartStopGroupApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/**
 * @brief   Add/ Remove the services Adc_ReadGroup() from the code.
 */
#define ADC_READ_GROUP_API                  [!IF "AdcGeneral/AdcReadGroupApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/**
 * @brief   Remove the services Adc_SetMode() from the code.
 */
#define ADC_SET_MODE_API                    STD_OFF

#define ADC_SW_INJ_CONFIGURED               STD_OFF

#define ADC_ENABLE_HWTRIG_NONAUTO_API       STD_OFF

#define ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API       STD_OFF

#define ADC_DUAL_CLOCK_MODE                 STD_OFF

/**
 * @brief   Add/Remove the AdcReadGroup() API optimization.
 */
[!IF "NonAutosar/AdcReadGroupOptimization = 'true'"!][!//
#define ADC_READ_GROUP_OPTIMIZATION (STD_ON)
[!ELSE!][!//
#define ADC_READ_GROUP_OPTIMIZATION (STD_OFF)
[!ENDIF!][!//

[!IF "AdcGeneral/AdcPriorityImplementation = 'ADC_PRIORITY_NONE'"!][!//
#define ADC_ENABLE_QUEUING      [!IF "AdcGeneral/AdcEnableQueuing"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ELSE!][!//
    #define ADC_ENABLE_QUEUING      STD_ON
[!ENDIF!][!//

[!NOCODE!][!//
[!VAR "ADC_EQADC_A_Fifo0Counter" = "0"!][!//
[!VAR "ADC_EQADC_A_Fifo1Counter" = "0"!][!//
[!VAR "ADC_EQADC_A_Fifo2Counter" = "0"!][!//
[!VAR "ADC_EQADC_A_Fifo3Counter" = "0"!][!//
[!VAR "ADC_EQADC_A_Fifo4Counter" = "0"!][!//
[!VAR "ADC_EQADC_A_Fifo5Counter" = "0"!][!//
[!//
[!LOOP "AdcConfigSet/*/AdcHwUnit/*/AdcGroup/*"!][!//
[!IF "(../../AdcHwUnitId = '0') or (../../AdcHwUnitId = '1')"!][!//
[!IF "AdcGroupFifo='ADC_FIFO_0'"!]
[!VAR "ADC_EQADC_A_Fifo0Counter" = "$ADC_EQADC_A_Fifo0Counter + 1"!]
[!ENDIF!][!//
[!ENDIF!][!//
[!//
[!IF "(../../AdcHwUnitId = '0') or (../../AdcHwUnitId = '1')"!][!//
[!IF "AdcGroupFifo='ADC_FIFO_1'"!]
[!VAR "ADC_EQADC_A_Fifo1Counter" = "$ADC_EQADC_A_Fifo1Counter + 1"!]
[!ENDIF!][!//
[!ENDIF!][!//
[!//
[!IF "(../../AdcHwUnitId = '0') or (../../AdcHwUnitId = '1')"!][!//
[!IF "AdcGroupFifo='ADC_FIFO_2'"!]
[!VAR "ADC_EQADC_A_Fifo2Counter" = "$ADC_EQADC_A_Fifo2Counter + 1"!]
[!ENDIF!][!//
[!ENDIF!][!//
[!//
[!IF "(../../AdcHwUnitId = '0') or (../../AdcHwUnitId = '1')"!][!//
[!IF "AdcGroupFifo='ADC_FIFO_3'"!]
[!VAR "ADC_EQADC_A_Fifo3Counter" = "$ADC_EQADC_A_Fifo3Counter + 1"!]
[!ENDIF!][!//
[!ENDIF!][!//
[!//
[!IF "(../../AdcHwUnitId = '0') or (../../AdcHwUnitId = '1')"!][!//
[!IF "AdcGroupFifo='ADC_FIFO_4'"!]
[!VAR "ADC_EQADC_A_Fifo4Counter" = "$ADC_EQADC_A_Fifo4Counter + 1"!]
[!ENDIF!][!//
[!ENDIF!][!//
[!//
[!IF "(../../AdcHwUnitId = '0') or (../../AdcHwUnitId = '1')"!][!//
[!IF "AdcGroupFifo='ADC_FIFO_5'"!]
[!VAR "ADC_EQADC_A_Fifo5Counter" = "$ADC_EQADC_A_Fifo5Counter + 1"!]
[!ENDIF!][!//
[!ENDIF!][!//
[!//
[!ENDLOOP!][!//
[!ENDNOCODE!][!//

[!NOCODE!][!//
[!VAR "ADC_EQADC_A_Fifo0Enable" = "0"!][!//
[!VAR "ADC_EQADC_A_Fifo1Enable" = "0"!][!//
[!VAR "ADC_EQADC_A_Fifo2Enable" = "0"!][!//
[!VAR "ADC_EQADC_A_Fifo3Enable" = "0"!][!//
[!VAR "ADC_EQADC_A_Fifo4Enable" = "0"!][!//
[!VAR "ADC_EQADC_A_Fifo5Enable" = "0"!][!//
[!ENDNOCODE!][!//

/* Enables the eQADC_A FIFO's */
[!IF "$ADC_EQADC_A_Fifo0Counter > 0"!][!//
#define ADC_EQADC_A_FIFO0_ENABLED   (STD_ON)
[!VAR "ADC_EQADC_A_Fifo0Enable" = "$ADC_EQADC_A_Fifo0Enable + 1"!][!//
[!ELSE!][!//
#define ADC_EQADC_A_FIFO0_ENABLED   (STD_OFF)
[!ENDIF!][!//
[!//
[!IF "$ADC_EQADC_A_Fifo1Counter > 0"!][!//
#define ADC_EQADC_A_FIFO1_ENABLED   (STD_ON)
[!VAR "ADC_EQADC_A_Fifo1Enable" = "$ADC_EQADC_A_Fifo1Enable + 1"!][!//
[!ELSE!][!//
#define ADC_EQADC_A_FIFO1_ENABLED   (STD_OFF)
[!ENDIF!][!//
[!//
[!IF "$ADC_EQADC_A_Fifo2Counter > 0"!][!//
#define ADC_EQADC_A_FIFO2_ENABLED   (STD_ON)
[!VAR "ADC_EQADC_A_Fifo2Enable" = "$ADC_EQADC_A_Fifo2Enable + 1"!][!//
[!ELSE!][!//
#define ADC_EQADC_A_FIFO2_ENABLED   (STD_OFF)
[!ENDIF!][!//
[!//
[!IF "$ADC_EQADC_A_Fifo3Counter > 0"!][!//
#define ADC_EQADC_A_FIFO3_ENABLED   (STD_ON)
[!VAR "ADC_EQADC_A_Fifo3Enable" = "$ADC_EQADC_A_Fifo3Enable + 1"!][!//
[!ELSE!][!//
#define ADC_EQADC_A_FIFO3_ENABLED   (STD_OFF)
[!ENDIF!][!//
[!//
[!IF "$ADC_EQADC_A_Fifo4Counter > 0"!][!//
#define ADC_EQADC_A_FIFO4_ENABLED   (STD_ON)
[!VAR "ADC_EQADC_A_Fifo4Enable" = "$ADC_EQADC_A_Fifo4Enable + 1"!][!//
[!ELSE!][!//
#define ADC_EQADC_A_FIFO4_ENABLED   (STD_OFF)
[!ENDIF!][!//
[!//
[!IF "$ADC_EQADC_A_Fifo5Counter > 0"!][!//
#define ADC_EQADC_A_FIFO5_ENABLED   (STD_ON)
[!VAR "ADC_EQADC_A_Fifo5Enable" = "$ADC_EQADC_A_Fifo5Enable + 1"!][!//
[!ELSE!][!//
#define ADC_EQADC_A_FIFO5_ENABLED   (STD_OFF)
[!ENDIF!][!//
[!//
[!IF "($ADC_EQADC_A_Fifo0Enable >=1) or ($ADC_EQADC_A_Fifo1Enable >=1) or ($ADC_EQADC_A_Fifo2Enable >=1) or ($ADC_EQADC_A_Fifo3Enable >=1) or ($ADC_EQADC_A_Fifo4Enable >=1) or ($ADC_EQADC_A_Fifo5Enable >=1)"!]
#define ADC_EQADC_A_CFIFO_ENABLED   (STD_ON)
#define ADC_EQADC_A_RFIFO_ENABLED   (STD_ON)
[!ELSE!][!//
#define ADC_EQADC_A_CFIFO_ENABLED   (STD_OFF)
#define ADC_EQADC_A_RFIFO_ENABLED   (STD_OFF)
[!ENDIF!][!//
[!//
/* Disables the eQADC_B FIFO's */
#define ADC_EQADC_B_FIFO0_ENABLED   (STD_OFF)
#define ADC_EQADC_B_FIFO1_ENABLED   (STD_OFF)
#define ADC_EQADC_B_FIFO2_ENABLED   (STD_OFF)
#define ADC_EQADC_B_FIFO3_ENABLED   (STD_OFF)
#define ADC_EQADC_B_FIFO4_ENABLED   (STD_OFF)
#define ADC_EQADC_B_FIFO5_ENABLED   (STD_OFF)
#define ADC_EQADC_B_CFIFO_ENABLED   (STD_OFF)
#define ADC_EQADC_B_RFIFO_ENABLED   (STD_OFF)

#define ADC_MULTIPLE_HARDWARE_TRIGGERS (STD_OFF)

#define ADC_EQADC_A 0
#define ADC_EQADC_B 1
#define ADC_UNIT_0 0
#define ADC_UNIT_1 1
#define ADC_UNIT_2 2
#define ADC_UNIT_3 3

/*lint -save -e961 */
/**
@note Violates MISRA 2004 Advisory Rule 19.7, use of function like macro - See @ref Adc_Cfg_h_REF_1
*/
#define ADC_HW_UNITS(unit) (Adc_Cfg_Ptr->Misc.ADC_HW_UNIT[unit])
/**
@note Violates MISRA 2004 Advisory Rule 19.7, use of function like macro - See @ref Adc_Cfg_h_REF_1
*/
/*lint -restore */

/**
@brief Maximum queue depth
*/
[!NOCODE!][!//
[!VAR "maxQueue" = "1"!][!//
[!VAR "maxGrpChannel" = "1"!][!//
[!VAR "maxGrp" = "1"!][!//
[!VAR "tempVal" = "0"!][!//
[!LOOP "AdcConfigSet/*"!][!//
 [!VAR "tempVal" = "num:i(AdcGeneric/AdcPriorityQueueMaxDepth)"!][!//
 [!IF "num:i($tempVal) > num:i($maxQueue)"!][!VAR "maxQueue" = "$tempVal"!][!ENDIF!][!//
[!ENDLOOP!][!//
[!VAR "tempVal" = "0"!][!//
[!LOOP "AdcConfigSet/*"!][!//
 [!VAR "tempVal" = "num:i(AdcGeneric/AdcMaxGroupChannels)"!][!//
 [!IF "num:i($tempVal) > num:i($maxGrpChannel)"!][!VAR "maxGrpChannel" = "$tempVal"!][!ENDIF!][!//
[!ENDLOOP!][!//
[!VAR "tempVal" = "0"!][!//
[!VAR "maxGrp" = "num:i(count(AdcConfigSet/*[1]/AdcHwUnit/*/AdcGroup/*))"!]
[!LOOP "AdcConfigSet/*"!][!//
[!VAR "tempVal" = "num:i(count(AdcHwUnit/*/AdcGroup/*))"!]
 [!IF "num:i($tempVal) > num:i($maxGrp)"!][!VAR "maxGrp" = "$tempVal"!][!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!]

/**
 * @brief   Max queue depth configured across all configset.
 */
#define ADC_QUEUE_MAX_DEPTH_MAX [!"num:i($maxQueue)"!]U

/**
 * @brief   Max number of channels in one group across all configset.
 */
#define ADC_MAX_GROUP_CHANNELS [!"num:i($maxGrpChannel)"!]U

/**
 * @brief   Max number of groups configured across all configset.
 */
#define ADC_MAX_GROUPS [!"num:i($maxGrp)"!]U

/**
 * @brief   Symbolic names of hardware units.
 *
 * @remarks Implements DADC08038
 */
[!NOCODE!][!//
[!VAR "OuterLoopCounter" = "0"!][!//
[!VAR "InnerLoopCounter" = "0"!][!//
[!LOOP "AdcConfigSet/*/AdcHwUnit/*"!][!//
[!VAR "OuterLoopCounter" = "$OuterLoopCounter + 1"!]
    [!VAR "InnerLoopCounter" = "0"!]
    [!VAR "Matchcounter" = "0"!]
    [!VAR "Name" = "node:name(.)"!]
    [!VAR "HwUnitId" = "AdcHwUnitId"!]
    [!LOOP "../../../*/AdcHwUnit/*"!]
    [!VAR "InnerLoopCounter" = "$InnerLoopCounter + 1"!]
    [!IF "$OuterLoopCounter >= $InnerLoopCounter"!]
      [!IF "($Name = node:name(.))"!]
          [!IF "($HwUnitId = AdcHwUnitId)"!]
            [!VAR "Matchcounter" = "$Matchcounter + 1"!]
          [!ELSE!]
          [!ERROR!]AdcHwUnitId should not be different for the same symbolic name "[!"@name"!]". Change the symbolic name. [!ENDERROR!]
          [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "$Matchcounter = 1"!]
[!CODE!]#define  [!"name(.)"!]                [!"AdcHwUnitId"!]
[!ENDCODE!]
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!]

/**
 * @brief   AUTOSAR Symbolic names of channels on all HW units.
 *
 * @remarks Implements DADC08019.
 */
[!LOOP "AdcConfigSet/*/AdcHwUnit/*/AdcChannel/*"!][!//
#define  [!"name(.)"!]                [!"AdcChannelId"!]
[!ENDLOOP!][!//

[!NOCODE!][!//
[!IF "NonAutosar/AdcChIndexSymNames = 'true'"!][!//
// Loop on all Configuration Sets
[!LOOP "AdcConfigSet/*"!][!//
    [!VAR "ConfigSetIndex" = "./@index"!][!//
    [!LOOP "./AdcHwUnit/*/AdcGroup/*"!][!//
        [!VAR "Groupname" = "name(.)"!][!//
        [!VAR "grp_ch_index" = "0"!][!//
        [!LOOP "AdcGroupDefinition/*"!][!//
            [!VAR "CurrAdcChannel" = "."!][!//
            [!VAR "CurrAdcChannel1" = "substring-after(substring-after(substring-after(substring-after(substring-after($CurrAdcChannel,'/'),'/'),'/'),'/'),'/')"!][!//
                    [!VAR "Channelname" = "$CurrAdcChannel1"!][!//
                    // Loop on all other Configuration Sets
                    [!LOOP "../../../../../../../*[@index>$ConfigSetIndex]/AdcHwUnit/*/AdcGroup/*"!][!//
                        [!IF "($Groupname = node:name(.))"!][!//
                            [!VAR "grp_ch_index_" = "0"!][!//
                            [!LOOP "AdcGroupDefinition/*"!][!//
                                [!VAR "CurrAdcChannel_" = "."!][!//
                                [!VAR "CurrAdcChannel1_" = "substring-after(substring-after(substring-after(substring-after(substring-after($CurrAdcChannel_,'/'),'/'),'/'),'/'),'/')"!][!//
                                    [!IF "($Channelname = $CurrAdcChannel1_)"!][!//
                                        [!IF "($grp_ch_index != $grp_ch_index_)"!][!//
                                            // Error!!!!!!!!
                                            [!ERROR!][!//
[!"$Groupname"!]_[!"$Channelname"!][!"' - Non AUTOSAR Symbolic name for channels can be repeated only if they have the same index in each of the config set.'"!][!//
                                            [!ENDERROR!][!//
                                        [!ENDIF!][!//
                                    [!ELSE!][!//
                                        [!VAR "grp_ch_index_" = "$grp_ch_index_ + 1"!][!//
                                    [!ENDIF!][!//
                            [!ENDLOOP!][!//
                        [!ENDIF!][!//
                    [!ENDLOOP!][!//
                    // End Loop on all other Configuration Sets
            [!VAR "grp_ch_index" = "$grp_ch_index + 1"!][!//
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
[!ENDLOOP!][!//
// End Loop on all Configuration Sets
[!ENDIF!][!//
[!ENDNOCODE!][!//

[!IF "NonAutosar/AdcChIndexSymNames = 'true'"!][!//
[!VAR "already_parsed_names"!][!ENDVAR!][!//
/**
 * @brief   NON AUTOSAR Symbolic names of channels on all HW units.
 */
[!LOOP "AdcConfigSet/*/AdcHwUnit/*/AdcGroup/*"!][!//
[!VAR "Groupname" = "name(.)"!][!//
[!VAR "index" = "0"!][!//
[!LOOP "AdcGroupDefinition/*"!][!//
[!VAR "CurrAdcChannel" = "."!][!//
[!VAR "CurrAdcChannel1" = "substring-after(substring-after(substring-after(substring-after(substring-after($CurrAdcChannel,'/'),'/'),'/'),'/'),'/')"!][!//
[!LOOP "../../../../AdcChannel/*"!][!//
[!IF "@name = $CurrAdcChannel1"!][!//
[!IF "contains($already_parsed_names, concat($Groupname, '_', node:name(.), '|')) = false()"!][!//
#define  [!"$Groupname"!]_[!"name(.)"!]                [!"num:i($index)"!]
[!VAR "already_parsed_names"="concat($already_parsed_names, $Groupname, '_', node:name(.), '|')"!][!//
[!VAR "index" = "$index + 1"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDLOOP!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//

/**
 * @brief Symbolic names of groups.
 *
 * @remarks Implements DADC08029.
 */
[!LOOP "AdcConfigSet/*/AdcHwUnit/*/AdcGroup/*"!][!//
#define  [!"name(.)"!]                  [!"AdcGroupId"!]
[!ENDLOOP!][!//

/** @brief number of channels in respective groups */
[!LOOP "AdcConfigSet/*"!][!//
[!VAR "CSET_NR" = "@index+1"!][!//
[!LOOP "AdcHwUnit/*/AdcGroup/*"!][!//
#define ADC_CFGSET[!"num:i($CSET_NR)"!]_GROUP_[!"AdcGroupId"!]_CHANNELS      [!"num:i(count(AdcGroupDefinition/*))"!]
[!ENDLOOP!][!//
[!ENDLOOP!][!//

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
 * @brief   Structure for Configuration data.
 *
 * @api
 */
typedef struct
{
  P2CONST(Adc_LLD_HWUnitConfiguration, ADC_VAR, ADC_APPL_CONST) ADC; /* pointer to hw unit configurations */
  P2CONST(Adc_LLD_GroupConfiguration, AUTOMATIC, ADC_APPL_DATA) Groups; /* pointer to group configurations */
  P2P2CONST(Adc_LLD_ChannelConfiguration, ADC_VAR, ADC_APPL_CONST) Channels; /* pointer to channel configurations */
  VAR(Adc_GroupType, ADC_VAR) GroupCount; /* total number of groups */
  #if (ADC_HW_TRIGGER_API == STD_ON)
  VAR(uint8, ADC_VAR) EtriggerDigitalFilter;                             /* low 8 bits of  EQADC_ETDFR */
  #endif
  CONST(Adc_LLD_MultiConfig, ADC_CONST) Misc; /* Miscellaneous configuration parameters */
} Adc_ConfigType;

/**
 * @brief   Structure for group status.
 *
 * @api
*/
typedef struct
{
  Adc_StatusType Conversion; /* group status */
  Adc_GroupConversionStateType AlreadyConverted; /* indicate if a group was previously converted or not */
#if (STD_ON==ADC_HW_TRIGGER_API)
  Adc_HWTriggeringType HwTriggering; /* hw trigger enabled/disabled */
#endif
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
  Adc_NotificationType Notification; /* notification enabled/disabled */
#endif
  Adc_StreamNumSampleType ResultIndex; /* index into streaming buffer that is currently being filled */
} Adc_GroupStatusType;

/**
 * @brief   Structure for hardware unit status.
 *
 * @api
*/
typedef struct
{
  Adc_StatusType Status; /* Status of the HW unit: IDLE, BUSY, COMPLETED */
  Adc_QueueIndexType QueueIndex; /* Filled slots in the queue */
  Adc_GroupType Queue[ADC_QUEUE_MAX_DEPTH_MAX]; /* Queued groups indexes 0..[ADC_QUEUE_DEPTH], always executing Queue[0] */
#if (STD_ON==ADC_HW_TRIGGER_API)
  Adc_GroupType HwQueue[ADC_QUEUE_HW]; /* Has been simulated the Hw queue with only one depth*/
  Adc_QueueIndexType HwQueueIndex; /* Filled slots in the Hw queue */
#endif
  boolean InjConvOngoin;
} Adc_UnitStatusType;

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
/**
 * @brief   Declaration Configuration sets.
 */
#ifdef ADC_PRECOMPILE_SUPPORT

extern CONST(Adc_ConfigType, ADC_CONST) Adc_ConfigPC;

#else

[!LOOP "AdcConfigSet/*"!][!//
extern CONST(Adc_ConfigType, ADC_CONST)  [!"node:name(.)"!];
[!ENDLOOP!][!//
#endif

/**
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" - See @ref Adc_Cfg_h_REF_2
*/
#define ADC_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

/**
 * @brief   Adc Conversion Result Buffer.
 */
[!NOCODE!][!//
[!VAR "OuterLoopCounter" = "0"!][!//
[!VAR "InnerLoopCounter" = "0"!][!//
[!VAR "MatchSingleBufferCnt" = "0"!][!//
[!VAR "MatchStreamingBufferCnt" = "0"!][!//
[!VAR "MatchMixedBufferCnt" = "0"!][!//
[!VAR "TEMP" = "0"!][!//
[!LOOP "AdcConfigSet/*/AdcHwUnit/*/AdcGroup/*"!][!//
    [!//Check if Result buffer pointer is a valid pointer
    [!IF "AdcResultBufferPointer != 'NULL_PTR'"!][!//
        [!VAR "MatchSingleBufferCnt" = "0"!][!//
        [!VAR "MatchMixedBufferCnt" = "0"!][!//
        [!VAR "MatchStreamingBufferCnt" = "0"!][!//
        [!VAR "OuterLoopCounter" = "$OuterLoopCounter + 1"!][!//
        [!VAR "InnerLoopCounter" = "0"!][!//
        [!VAR "Matchcounter" = "0"!][!//
        [!//Store AccessMode, ResultBuffer, Streaming samples and number of channels in the group
        [!VAR "ModeName" = "AdcGroupAccessMode"!]
        [!VAR "Buffername" = "AdcResultBufferPointer"!][!//
        [!VAR "MaxGroupdefinition" = "num:i(count(AdcGroupDefinition/*))"!][!//
        [!VAR "MaxNumsamples" = "AdcStreamingNumSamples"!][!//
        [!LOOP "../../../../../*/AdcHwUnit/*/AdcGroup/*"!][!//
            [!IF "AdcResultBufferPointer != 'NULL_PTR'"!][!//
                [!VAR "InnerLoopCounter" = "$InnerLoopCounter + 1"!][!//
                [!IF "$OuterLoopCounter >= $InnerLoopCounter"!][!//
                   [!//Check if the result buffer name is same for any other group
                   [!IF "($Buffername = AdcResultBufferPointer)"!][!//
                     [!IF "($Matchcounter = 0)"!][!//
                        [!LOOP "../../../../../*/AdcHwUnit/*/AdcGroup/*"!][!//
                            [!//Check if the result buffer name is same for any other group
                            [!IF "($Buffername = AdcResultBufferPointer)"!][!//
                                [!//Check if the access mode configured is Single Access and is same for the different groups.
                                [!IF "($ModeName='ADC_ACCESS_MODE_SINGLE')and($ModeName = AdcGroupAccessMode)"!]
                                    [!VAR "MatchSingleBufferCnt" = "$MatchSingleBufferCnt + 1"!][!//
                                [!//Check if the access mode configured is Streaming Access and is same for the different groups.
                                [!ELSEIF "($ModeName='ADC_ACCESS_MODE_STREAMING') and ($ModeName = AdcGroupAccessMode)"!]
                                    [!VAR "MatchStreamingBufferCnt" = "$MatchStreamingBufferCnt + 1"!][!//
                                [!/* Check if the access mode configured is Streaming Access for one group
                                 and is Single access for other group.   */!]
                                [!ELSE!]
                                    [!VAR "MatchMixedBufferCnt" = "$MatchMixedBufferCnt + 1"!][!//
                                [!ENDIF!]
                                [!IF "($MaxGroupdefinition <= num:i(count(AdcGroupDefinition/*)))"!][!//
                                    [!// Stores the maximum number of channels across all groups
                                    [!VAR "MaxGroupdefinition" = "num:i(count(AdcGroupDefinition/*))"!][!//
                                [!ENDIF!][!//
                                [!IF "(($MaxNumsamples <= AdcStreamingNumSamples))"!][!//
                                    [!// Stores the maximum number of channels across all groups
                                    [!VAR "MaxNumsamples" = "AdcStreamingNumSamples"!][!//
                                [!ENDIF!][!//
                            [!ENDIF!][!//
                        [!ENDLOOP!][!//
                      [!ENDIF!][!//
                    [!VAR "Matchcounter" = "$Matchcounter + 1"!][!//
                   [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//

        [!// If Result buffer configured is same for different groups with Access mode as "Single"
        [!IF "$Matchcounter =1 and $MatchSingleBufferCnt >0 and $MatchMixedBufferCnt<=0"!][!//
            [!CODE!][!//
extern Adc_ValueGroupType [!"AdcResultBufferPointer"!][[!"num:i($MaxGroupdefinition)"!]];
[!ENDCODE!][!//
        [!// If Result buffer configured is same for different groups with Access mode as "Streaming"
        [!ELSEIF "$Matchcounter =1 and $MatchStreamingBufferCnt >0 and $MatchMixedBufferCnt<=0"!][!//
            [!CODE!][!//
extern Adc_ValueGroupType [!"AdcResultBufferPointer"!][[!"num:i($MaxGroupdefinition)"!]][[!"num:i($MaxNumsamples)"!]];
[!ENDCODE!][!//
        [!// If Result buffer configured is same for different groups with Access mode as "Single" and "Streaming"
        [!ELSEIF "$Matchcounter =1"!][!//
            [!CODE!][!//
extern Adc_ValueGroupType [!"AdcResultBufferPointer"!][[!"num:i($MaxGroupdefinition)"!]][[!"num:i($MaxNumsamples)"!]];
[!ENDCODE!][!//
        [!ENDIF!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!]
/**
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" - See @ref Adc_Cfg_h_REF_2
*/
#define ADC_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ADC_CFG_H */
/** @} */
