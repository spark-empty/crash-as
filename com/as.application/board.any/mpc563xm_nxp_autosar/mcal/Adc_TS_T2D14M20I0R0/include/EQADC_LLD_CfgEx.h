/*!
 * @addtogroup ADC
 * @{
 */
/**
    @file    EQADC_LLD_CfgEx.h
    @version 2.0.0

    @brief   AUTOSAR Adc - Brief description.
    @details Detailed description.

    Project AUTOSAR 3.0 MCAL
    Patform PA
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
@page misra_violations MISRA-C:2004 violations

@section EQADC_LLD_CfgEx_h_REF_1
Violates MISRA 2004 Advisory Rul e 19.7, use of function like macro. This violation is due to
function like macros defined for register operations. Function like macros are used to reduce code
complexity.

@section EQADC_LLD_CfgEx_h_REF_2
Violates MISRA 2004 Advisory Rul e 19.15, repeated include file MemMap.h. There are different kinds
of execution code sections.
*/
#ifndef EQADC_LLD_CFGEX_H
#define EQADC_LLD_CFGEX_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Reg_eSys_EQADC.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@{
 * @brief   Header file version information.
 *
 * @remarks Covers BSW00374, BSW00379, BSW00318.
*/
#define EQADC_VENDOR_ID_LLD_CFGEX             43
#define EQADC_AR_MAJOR_VERSION_LLD_CFGEX      3
#define EQADC_AR_MINOR_VERSION_LLD_CFGEX      0
#define EQADC_AR_PATCH_VERSION_LLD_CFGEX      0
#define EQADC_SW_MAJOR_VERSION_LLD_CFGEX      2
#define EQADC_SW_MINOR_VERSION_LLD_CFGEX      0
#define EQADC_SW_PATCH_VERSION_LLD_CFGEX      0
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


/*==================================================================================================
                                             ENUMS
==================================================================================================*/
/**
@{
 * @enum   Adc_PriorityImplementation_Type.
 *         Type that indicates the Priority mechanism.
*/
typedef enum
{
  /** EQADC_PRIORITY_HW = ADC_PRIORITY_HW. */
  EQADC_PRIORITY_HW = 0U,
  /** EQADC_PRIORITY_HW_SW = ADC_PRIORITY_HW_SW. */
  EQADC_PRIORITY_HW_SW,
  /** EQADC_PRIORITY_NONE = ADC_PRIORITY_NONE. */
  EQADC_PRIORITY_NONE
} Adc_PriorityImplementationType;
/**@}*/

/**
@{
 * @enum   Adc_GroupISRAlignSamples_Type.
 *         Type that indicates if group right aligned or not.
*/
typedef enum
{
  /** ADC_ISR_RIGHT_ALIGH = Right alignement of samples group. */
   ADC_ISR_RIGHT_ALIGH,
  /** ADC_ISR_NOT_RIGHT_ALIGH = Samples of group not aligned. */
  ADC_ISR_NOT_RIGHT_ALIGH
} Adc_GroupISRAlignSamples_Type;
/**@}*/

/**
@{
 * @enum   Adc_GroupConversionStateType.
           Type that indicates if group is already converted or not.
*/
typedef enum
{
  /** ADC_NOT_YET_CONVERTED = The group is not yet converted */
  ADC_NOT_YET_CONVERTED = 0U,
  /** ADC_ALREADY_CONVERTED = The group is already converted */
  ADC_ALREADY_CONVERTED
} Adc_GroupConversionStateType;
/**@}*/

/**
@{
 * @enum   Adc_GroupAccessModeType.
 *         Type for configuring the access mode to group conversion results.
*/
typedef enum
{
  /** ADC_ACCESS_MODE_SINGLE = Single value access mode. */
  ADC_ACCESS_MODE_SINGLE = 0U,
  /** ADC_ACCESS_MODE_STREAMING = Streaming access mode. */
  ADC_ACCESS_MODE_STREAMING
} Adc_GroupAccessModeType;
/**@}*/

/**
@{
 * @enum   Adc_GroupConvModeType.
 *         Type for configuring the conversion mode of an ADC Channel group.
*/
typedef enum
{
  /** ADC_CONV_MODE_ONESHOT = Exactly one conversion of each channel in an ADC channel group is
      performed after the configured trigger event. In case of "group trigger source software", a
      started One-Shot conversion can be stopped by a software API call.
      In case of "group trigger source hardware", a started One-Shot conversion can be stopped by
      disabling the trigger event (if supported by hardware).
  */
  ADC_CONV_MODE_ONESHOT = 0U,
  /** ADC_CONV_MODE_CONTINUOUS = Repeated conversions of each ADC channel in an ADC channel group
      are performed."Continuous conversion mode" is only available for "group trigger source
      software". A started "Continuous conversion" can be stopped by a software API call.
  */
  ADC_CONV_MODE_CONTINUOUS
} Adc_GroupConvModeType;
/**@}*/

/**
@{
 * @enum   Adc_GroupReplacementType.
 *         Replacement mechanism, which is used on ADC group level,
 *         if a group conversion is interrupted by a group which has a higher priority.
*/
typedef enum
{
  /** ADC_GROUP_REPL_ABORT_RESTART = Abort/Restart mechanism is used on group level, if a group is
      interrupted by a higher priority group. The complete conversion round of the interrupted group
      (all group channels)is restarted after the higher priority group conversion is finished. If
      the group is configured in streaming access mode, only the results of the interrupted
      conversion round are discarded. Results of previous conversion rounds which are already
      written to the result buffer are not affected.
  */
  ADC_GROUP_REPL_ABORT_RESTART,
  /** ADC_GROUP_REPL_SUSPEND_RESUME = Suspend/Resume mechanism is used on group level,
      if a group is interrupted by a higher priority group. The converions round of
      the interrupted group is completed after the higher priority group conversion is finished.
  */
  ADC_GROUP_REPL_SUSPEND_RESUME
}Adc_GroupReplacementType;
/**@}*/

/**
@{
 * @enum   Adc_StreamBufferModeType.
 *         Type for configuring the streaming access mode buffer type.
*/
typedef enum
{
  /** ADC_STREAM_BUFFER_LINEAR = The ADC Driver stops the conversion as soon as the stream buffer
      is full (number of samples reached).
  */
  ADC_STREAM_BUFFER_LINEAR = 0U,
  /** ADC_STREAM_BUFFER_CIRCULAR = The ADC Driver continues the conversion even if the stream buffer
      is full (number of samples reached) by wrapping around the stream buffer itself.
  */
  ADC_STREAM_BUFFER_CIRCULAR
} Adc_StreamBufferModeType;
/**@}*/

/**
@{
 * @enum   Adc_StatusType.
 *         Current status of the conversion of the requested ADC Channel group.
*/
typedef enum
{
  /** ADC_IDLE = The conversion of the specified group has not been started.*/
  ADC_IDLE = 0U,
  /** ADC_BUSY = The conversion of the specified group has been started and is still going on */
  ADC_BUSY,
  /** ADC_COMPLETED = A conversion round (which is not the final one) of the specified group has
      been finished. */
  ADC_COMPLETED,
  /** ADC_STREAM_COMPLETED = he result buffer is completely filled */
  ADC_STREAM_COMPLETED
} Adc_StatusType;
/**@}*/

/**
@{
 * @enum   Adc_NotificationType.
 *         Type that indicates if group notification is enabled or not
*/
typedef enum
{
  /** ADC_NOTIFICATION_DISABLED = Notification is disabled */
  ADC_NOTIFICATION_DISABLED = 0U,
  /** ADC_NOTIFICATION_ENABLED = Notification is enabled. */
  ADC_NOTIFICATION_ENABLED
} Adc_NotificationType;
/**@}*/

/**
@{
 * @enum  Adc_HwTriggerSignalType
 *        Type for configuring on which edge of the hardware trigger signal the driver should react,
 *        i.e. start the conversion (only if supported by the ADC hardware).
*/
typedef enum
{
  /** ADC_HW_TRIG_RISING_EDGE = React on the rising edge of the hardware trigger signal
  (only if supported by the ADC hardware).
  */
  ADC_HW_TRIG_RISING_EDGE = 0U,
  /** ADC_HW_TRIG_FALLING_EDGE = React on the falling edge of the hardware trigger signal
  (only if supported by the ADC hardware).
  */
  ADC_HW_TRIG_FALLING_EDGE,
  /** ADC_HW_TRIG_BOTH_EDGES = React on both edges of the hardware trigger signal
  (only if supported by the ADC hardware).
  */
  ADC_HW_TRIG_BOTH_EDGES
} Adc_HwTriggerSignalType;
/**@}*/

/**
@{
 * @enum   Adc_TriggerSourceType
 *         Type for configuring the trigger source for an ADC Channel group.
*/
typedef enum
{
/** ADC_TRIGG_SRC_SW = Group is triggered by a software API call. */
  ADC_TRIGG_SRC_SW = 0U
#if (STD_ON == ADC_HW_TRIGGER_API)
,
/** ADC_TRIGG_SRC_HW = Group is triggered by a hardware event. */
  ADC_TRIGG_SRC_HW
#endif
} Adc_TriggerSourceType;
/**@}*/

#if (STD_ON==ADC_HW_TRIGGER_API)
/**
@{
 * @enum   Adc_HWTriggeringType
 *         Type that indicates if hardware trigger for group is enabled or not
*/
typedef enum
{
  /** ADC_HWTRIGGER_DISABLED = Hardware trigger for group is disabled. */
  ADC_HWTRIGGER_DISABLED = 0U,
  /** ADC_HWTRIGGER_ENABLED = Hardware trigger for group is enabled. */
  ADC_HWTRIGGER_ENABLED
} Adc_HWTriggeringType;
/**@}*/
#endif

/* if Andorra 2M and Andorra 4M or Monaco1.5M */
#if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) ||\
    defined(__DOXYGEN__)
/**
*  @brief   maximum hardware across all derviative, used for the array size.
*/
#define ADC_HW_MAX                           2U

/**
 * @brief   maximum eQADC.
 */
#define EQADC_MAX                            1U
#else
/**
 * @brief   maximum hardware across all derviative, used for the array size.
 */
#define ADC_HW_MAX                           4U

/**
 * @brief   maximum eQADC.
 */
#define EQADC_MAX                            2U
#endif /* (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) ||
          defined(__DOXYGEN__) */

/**
 * @brief   maximum ADC hardware per eQADC.
 */
#define EQADC_MAX_UNITS                      2U

/**
 * @brief   max number of FIFO available on ADC.
 */
#define ADC_MAX_FIFO                         6U

/**
@{
 * @brief   FIFOs in ADC.
 *
 * @details Ids for FIFO.
*/
#define ADC_FIFO_0                           0U
#define ADC_FIFO_1                           1U
#define ADC_FIFO_2                           2U
#define ADC_FIFO_3                           3U
#define ADC_FIFO_4                           4U
#define ADC_FIFO_5                           5U
/**@}*/

/**
 * @brief   max number of command FIFOs available on ADC.
 */
#define ADC_MAX_COMMAND_FIFO                 6U

/**
 * @brief   max number of result FIFOs available on ADC.
 */
#define ADC_MAX_RESULT_FIFO                  6U

/*================================================================================================*/
/**
 * @typedef   EQADC_fifo_Dma_Channel
 *            configured dma channels for the eQADC_A and eQADC_B
 *
 * @api
*/
/*================================================================================================*/
typedef uint8 EQADC_fifo_Dma_Channel[(ADC_MAX_COMMAND_FIFO + ADC_MAX_RESULT_FIFO)];
/**
@{
 * @note Violates MISRA 2004 Advisory Rule 19.7, use of function like macro
 * - See @ref EQADC_LLD_CfgEx_h_REF_1
*/
/*lint -save -e961 */
/** @brief Number of streaming samples type casted to Adc_StreamNumSampleType  type */
#define ADC_STREAMING_NUM_SAMPLES(num) (Adc_StreamNumSampleType)(num)

#if (ADC_MAX_HW_UNITS == 1U) || defined(__DOXYGEN__)
/**
 * @brief   Hadrware unit.
 */
#define ADC_GroupUnit(group)                  0U
#else
/**
 * @brief   Hardware unit to which the group belongs to.
 */
#define ADC_GroupUnit(group)                  (Adc_Cfg_Ptr->Groups[group].HWUnit)
#endif

/**
 * @brief Number of channels in the group.
 */
#define EQADC_GroupChannels(group)              (Adc_Cfg_Ptr->Groups[group].AssignedChannelCount)
/**
 * @brief Pointer to assigned channels in the group.
 */
#define EQADC_GroupChannelIndex(group,channel)  (Adc_Cfg_Ptr->Groups[group].Assignment[channel])
/**
 * @brief Group at postion requested.
 */
#define ADC_GroupInQueue(unit,p)                (ADC_UnitStatus[unit].Queue[p])
/**
 * @brief Hardware queue index.
 */
#define ADC_GroupsInHwQueue(unit)               (ADC_UnitStatus[unit].HwQueueIndex)
/**
 * @brief Pripority of the group type casted to Adc_GroupPriorityType type.
 */
#define ADC_GROUP_PRIORITY(Priority)            (Adc_GroupPriorityType)(Priority)
/**
 * @brief Fifo configured for the group.
 */
#define EQADC_GroupFifoIndex(group)             (Adc_Cfg_Ptr->Groups[(group)].AdcGroupFifo)
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) || defined(__DOXYGEN__)
/**
 * @brief Priority of the group.
 */
#define EQADC_GroupPriority(group)              (Adc_Cfg_Ptr->Groups[group].Priority)
#endif

/**
 * @brief Current group in 0th position of queue.
 */
#define EQADC_CurrentGroup(unit)                 (ADC_UnitStatus[(unit)].Queue[0])
/*lint -restore */
/**@}*/

/**
@{
 * @brief   Calibration defines.
 *
 * @details Calibration related defines.
*/
#define ADC_CAL_OFF                         ((uint8)0x00U)
#define ADC_CAL_ON                          ((uint8)0x01U)
#define ADC_CAL_GCC                         ((uint32)0x08000000UL)
#define ADC_IDEAL_RES75_2                   ((uint32)12286UL)
#define ADC_CAL_CONST                       ((uint32)0x80000000UL)
#define ADC_CAL_25VREF                      ((uint32)0x00002C00UL)
#define ADC_CAL_75VREF                      ((uint32)0x00002B00UL)
#define ADC_OCC_REG                         ((uint32)0x0000FFFFUL)
#define ADC_CFPR0_GCCR                      ((uint32)0x4000UL)
#define ADC_CFPR0_OCCR                      ((uint32)0x4000U)
#define ADC_CFPR0_CR                        ((uint32)0x001FU)
#define ADC_CFPR1_CR                        ((uint32)0x001FU)
#define ADC_CFPR2_CR                        ((uint32)0x001FU)
#define ADC_CFPR3_CR                        ((uint32)0x001FU)
#define ADC_CFPR4_CR                        ((uint32)0x001FU)
#define ADC_CFPR5_CR                        ((uint32)0x001FU)
/**@}*/

/**
@{
 * @brief   Channel Resolution.
 *
 * @details eQADC resolution 8/10/12 bits.
 */
#define EQADC_BITS_RESOLUTION_8             (0x08U)
#define EQADC_BITS_RESOLUTION_10            (0x0AU)
#define EQADC_BITS_RESOLUTION_12            (0x0CU)
#define ADC_ACR2_RESSEL_8BIT                 0x80U
#define ADC_ACR1_RESSEL_10BIT                0x40U
#define ADC_CONVERSION_TIMEOUT               0x0254U
#define EQADC_STD_CONFIG_SEL_12BIT_RES       0x0U
#define EQADC_ALT_CONFIG_SEL_10BIT_RES       0x08U
#define EQADC_ALT_CONFIG_SEL_8BIT_RES        0x09U
/**@}*/

/* if Andorra 2M and Andorra4M or Monaco1.5M */
#if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) ||\
    defined(__DOXYGEN__)
/**
@{
 * @brief   Hadrware channels.
 *
 * @details Selects the physical Hardware Adc Channel for eQADC_A.
*/
#define AN_0                               0U
#define AN_1                               1U
#define AN_2                               2U
#define AN_3                               3U
#define AN_4                               4U
#define AN_5                               5U
#define AN_6                               6U
#define AN_7                               7U
#define AN_8                               8U
#define AN_9                               9U
#define AN_10                              10U
#define AN_11                              11U
#define AN_12                              12U
#define AN_13                              13U
#define AN_14                              14U
#define AN_15                              15U
#define AN_16                              16U
#define AN_17                              17U
#define AN_18                              18U
#define AN_19                              19U
#define AN_20                              20U
#define AN_21                              21U
#define AN_22                              22U
#define AN_23                              23U
#define AN_24                              24U
#define AN_25                              25U
#define AN_26                              26U
#define AN_27                              27U
#define AN_28                              28U
#define AN_29                              29U
#define AN_30                              30U
#define AN_31                              31U
#define AN_32                              32U
#define AN_33                              33U
#define AN_34                              34U
#define AN_35                              35U
#define AN_36                              36U
#define AN_37                              37U
#define AN_38                              38U
#define AN_39                              39U
#define VRH_40                             40U
#define VRL_41                             41U
#define VRH_MINUS_VRL_BY_2_42              42U
#define VRH_MINUS_VRL_75PE_43              43U
#define VRH_MINUS_VRL_25PE_44              44U
#define INA_ADC01_0_45                     45U
#define ANW_64                             64U
#define ANW_65                             65U
#define ANW_66                             66U
#define ANW_67                             67U
#define ANW_68                             68U
#define ANW_69                             69U
#define ANW_70                             70U
#define ANW_71                             71U
#define ANX_72                             72U
#define ANX_73                             73U
#define ANX_74                             74U
#define ANX_75                             75U
#define ANX_76                             76U
#define ANX_77                             77U
#define ANX_78                             78U
#define ANX_79                             79U
#define ANY_80                             80U
#define ANY_81                             81U
#define ANY_82                             82U
#define ANY_83                             83U
#define ANY_84                             84U
#define ANY_85                             85U
#define ANY_86                             86U
#define ANY_87                             87U
#define ANZ_88                             88U
#define ANZ_89                             89U
#define ANZ_90                             90U
#define ANZ_91                             91U
#define ANZ_92                             92U
#define ANZ_93                             93U
#define ANZ_94                             94U
#define ANZ_95                             95U
#define DAN0PL_DAN0MI_96                   96U
#define DAN1PL_DAN1MI_97                   97U
#define DAN2PL_DAN2MI_98                   98U
#define DAN3PL_DAN3MI_99                   99U
#define INA_ADC01_1_128                    128U
#define INA_ADC01_2_129                    129U
#define INA_ADC0_3_162                     162U
#define INA_ADC0_4_163                     163U
#define INA_ADC0_5_164                     164U
#define INA_ADC0_6_165                     165U
#define INA_ADC0_7_166                     166U
#define INA_ADC0_8_167                     167U
#define INA_ADC1_3_194                     194U
#define INA_ADC1_4_195                     195U
#define INA_ADC1_5_196                     196U
#define INA_ADC1_6_197                     197U
#define INA_ADC1_7_198                     198U
#define INA_ADC1_8_199                     199U
#define ANR_224                            224U
#define ANR_225                            225U
#define ANR_226                            226U
#define ANR_227                            227U
#define ANR_228                            228U
#define ANR_229                            229U
#define ANR_230                            230U
#define ANR_231                            231U
#define ANS_232                            232U
#define ANS_233                            233U
#define NS_234                            234U
#define ANS_235                            235U
#define ANS_236                            236U
#define ANS_237                            237U
#define ANS_238                            238U
#define ANS_239                            239U
#define ANT_240                            240U
#define ANT_241                            241U
#define ANT_242                            242U
#define ANT_243                            243U
#define ANT_244                            244U
#define ANT_245                            245U
#define ANT_246                            246U
#define ANT_247                            247U
#define ANU_248                            248U
#define ANU_249                            249U
#define ANU_250                            250U
#define ANU_251                            251U
#define ANU_252                            252U
#define ANU_253                            253U
#define ANU_254                            254U
#define ANU_255                            255U
/**@}*/

/**
@{
 * @brief   Trigger sources.
 *
 * @details Defines the source for the eQADC trigger inputs (bits eTSEL0..5 in SIU_ISEL3 register).
*/
#define ETRIG0                             0U
#define ETRIG1                             0U
#define RTI                                1U
#define PIT0                               2U
#define PIT1                               3U
#define PIT2                               4U
#define PIT3                               5U
#define ETRIG2                             7U
#define ETRIG3                             7U
#define eTPU30_PIT0                        8U
#define eTPU31_PIT0                        8U
#define eTPU30_PIT1                        9U
#define eTPU31_PIT1                        9U
#define eTPUA28                            12U
#define eTPUA29                            13U
#define eTPUA30                            14U
#define eTPUA31                            15U
#define eMIOS10_PIT2                       20U
#define eMIOS11_PIT2                       20U
#define eMIOS10_PIT3                       21U
#define eMIOS11_PIT3                       21U
#define eMIOS23                            31U
/**@}*/
#else
/**
@{
 * @brief   Hadrware channels.
 *
 * @details Selects the physical Hardware Adc Channel for eQADC_A and eQADC_B.
*/
#define AN_0                               0U
#define AN_1                               1U
#define AN_2                               2U
#define AN_3                               3U
#define AN_4                               4U
#define AN_5                               5U
#define AN_6                               6U
#define AN_7                               7U
#define AN_8                               8U
#define AN_9                               9U
#define AN_10                              10U
#define AN_11                              11U
#define AN_12                              12U
#define AN_13                              13U
#define AN_14                              14U
#define AN_15                              15U
#define AN_16                              16U
#define AN_17                              17U
#define AN_18                              18U
#define AN_19                              19U
#define AN_20                              20U
#define AN_21                              21U
#define AN_22                              22U
#define AN_23                              23U
#define AN_24                              24U
#define AN_25                              25U
#define AN_26                              26U
#define AN_27                              27U
#define AN_28                              28U
#define AN_29                              29U
#define AN_30                              30U
#define AN_31                              31U
#define AN_32                              32U
#define AN_33                              33U
#define AN_34                              34U
#define AN_35                              35U
#define AN_36                              36U
#define AN_37                              37U
#define AN_38                              38U
#define AN_39                              39U
#define VRH_40                             40U
#define VRL_41                             41U
#define VRH_MINUS_VRL_BY_2_42              42U
#define VRH_MINUS_VRL_75PE_43              43U
#define VRH_MINUS_VRL_25PE_44              44U
#define INA_ADC01_0_45                     45U
#define ANW_64                             64U
#define ANW_65                             65U
#define ANW_66                             66U
#define ANW_67                             67U
#define ANW_68                             68U
#define ANW_69                             69U
#define ANW_70                             70U
#define ANW_71                             71U
#define ANX_72                             72U
#define ANX_73                             73U
#define ANX_74                             74U
#define ANX_75                             75U
#define ANX_76                             76U
#define ANX_77                             77U
#define ANX_78                             78U
#define ANX_79                             79U
#define ANY_80                             80U
#define ANY_81                             81U
#define ANY_82                             82U
#define ANY_83                             83U
#define ANY_84                             84U
#define ANY_85                             85U
#define ANY_86                             86U
#define ANY_87                             87U
#define ANZ_88                             88U
#define ANZ_89                             89U
#define ANZ_90                             90U
#define ANZ_91                             91U
#define ANZ_92                             92U
#define ANZ_93                             93U
#define ANZ_94                             94U
#define ANZ_95                             95U
#define DAN0PL_DAN0MI_96                   96U
#define DAN1PL_DAN1MI_97                   97U
#define DAN2PL_DAN2MI_98                   98U
#define DAN3PL_DAN3MI_99                   99U
#define INA_ADC01_1_128                    128U
#define INA_ADC01_2_129                    129U
#define INA_ADC01_9_144                    144U
#define INA_ADC0_3_162                     162U
#define INA_ADC0_4_163                     163U
#define INA_ADC0_5_164                     164U
#define INA_ADC0_6_165                     165U
#define INA_ADC0_7_166                     166U
#define INA_ADC0_8_167                     167U
#define INA_ADC1_3_194                     194U
#define INA_ADC1_4_195                     195U
#define INA_ADC1_5_196                     196U
#define INA_ADC1_6_197                     197U
#define INA_ADC1_7_198                     198U
#define INA_ADC1_8_199                     199U
#define ANR_224                            224U
#define ANR_225                            225U
#define ANR_226                            226U
#define ANR_227                            227U
#define ANR_228                            228U
#define ANR_229                            229U
#define ANR_230                            230U
#define ANR_231                            231U
#define ANS_232                            232U
#define ANS_233                            233U
#define ANS_234                            234U
#define ANS_235                            235U
#define ANS_236                            236U
#define ANS_237                            237U
#define ANS_238                            238U
#define ANS_239                            239U
#define ANT_240                            240U
#define ANT_241                            241U
#define ANT_242                            242U
#define ANT_243                            243U
#define ANT_244                            244U
#define ANT_245                            245U
#define ANT_246                            246U
#define ANT_247                            247U
#define ANU_248                            248U
#define ANU_249                            249U
#define ANU_250                            250U
#define ANU_251                            251U
#define ANU_252                            252U
#define ANU_253                            253U
#define ANU_254                            254U
#define ANU_255                            255U
/**@}*/

/**
@{
 * @brief   Trigger sources.
 *
 * @details Defines the source for the eQADC trigger inputs (bits TSEL4_7 in SIU_ISEL register).
 *          SIU_ISEL select registers [4:5] are used to select a trigger source
 *          for command FIFOs in eQADC_A.
 *          SIU_ISEL select registers [6:7] are used to select a trigger source
 *          for command FIFOs in eQADC_B.
*/
#define RTI                                 1U
#define PIT0                                2U
#define PIT1                                3U
#define PIT2                                4U
#define PIT3                                5U
#define eTPUA28                             12U
#define eTPUA29                             13U
#define eTPUA30                             14U
#define eTPUA31                             15U
#define eTPUB28                             16U
#define eTPUB29                             17U
#define eTPUB30                             18U
#define eTPUB31                             19U
#define eMIOS16                             24U
#define eMIOS17                             25U
#define eMIOS18                             26U
#define eMIOS19                             27U
#define eMIOS20                             28U
#define eMIOS21                             29U
#define eMIOS22                             30U
#define eMIOS23                             31U
#define eTPUA30_FIFO_0                      32U
#define eTPUA31_FIFO_1                      32U
#define eTPUA29_FIFO_2                      32U
#define eTPUA28_FIFO_3                      32U
#define eTPUA27_FIFO_4                      32U
#define eTPUA26_FIFO_5                      32U
#define eMIOS10_FIFO_0                      64U
#define eMIOS11_FIFO_1                      64U
#define eMIOS15_FIFO_2                      64U
#define eMIOS14_FIFO_3                      64U
#define eMIOS13_FIFO_4                      64U
#define eMIOS12_FIFO_5                      64U
#define ETRIG0                              96U
#define ETRIG1                              96U
/**@}*/
#endif /* (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) ||
          defined(__DOXYGEN__) */

/*================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/*================================================================================================*/
/**
 * @typedef   Adc_NotifyType
 *            Notification function pointer definition
 *
 * @api
*/
/*================================================================================================*/
typedef void (*Adc_NotifyType)(void);
/*================================================================================================*/
/**
 * @typedef   Adc_WdgNotifyType
 *            Notification function pointer definition - WDG
 *
 * @api
*/
/*================================================================================================*/
typedef void (*Adc_WdgNotifyType)(void);
/*================================================================================================*/
/**
 * @typedef   Adc_ChannelType
 *            Numeric ID of an ADC channel.
 *
 * @api
*/
/*================================================================================================*/
typedef uint8 Adc_ChannelType;            /* Numeric ID of an ADC channel.*/
/*================================================================================================*/
/**
 * @typedef   Adc_GroupType
 *            Numeric ID of an ADC channel group. No uC dependent
 *
 * @api
*/
/*================================================================================================*/
typedef uint8 Adc_GroupType;
/*================================================================================================*/
/**
 * @typedef   Adc_ResolutionType
 *           Channel resolution in number of bits
 *
 * @api
*/
/*================================================================================================*/
typedef uint8 Adc_ResolutionType;
/*================================================================================================*/
/**
 * @typedef   Adc_GroupPriorityType
 *            ADC Channel group priority
 *
 * @api
*/
/*================================================================================================*/
typedef uint8 Adc_GroupPriorityType;
/*================================================================================================*/
/**
 * @typedef   Adc_GroupDefType
 *            Definition of channels in a group
 *
 * @api
*/
/*================================================================================================*/
typedef Adc_ChannelType Adc_GroupDefType;
/*================================================================================================*/
/**
 * @typedef   Adc_HwUnitType
 *            Numeric ID of an ADC Hw Unit
 *
 * @api
*/
/*================================================================================================*/
typedef uint8 Adc_HwUnitType;
/*================================================================================================*/
/**
 * @typedef   Adc_ValueGroupType
 *            Type for ADC result of one channel. 10bit for XPC560XP Platform
 *
 * @api
*/
/*================================================================================================*/
typedef uint16 Adc_ValueGroupType;
/*================================================================================================*/
/**
 * @typedef   Adc_ClockSourceType
 *            Clock source for ADC - not used on  XPC560XP
 *
 * @api
*/
/*================================================================================================*/
typedef uint8 Adc_ClockSourceType;
/*================================================================================================*/
/**
 * @typedef   Adc_PrescaleType
 *            Clock prescaler factor
 *
 * @api
*/
/*================================================================================================*/
typedef uint8 Adc_PrescaleType;
/*================================================================================================*/
/**
 * @typedef   Adc_ConversionTimeType
 *            Conversion time
 *
 * @api
*/
/*================================================================================================*/
typedef uint16 Adc_ConversionTimeType;
/*================================================================================================*/
/**
 * @typedef   Adc_SamplingTimeType
 *            Sampling time
 *
 * @api
*/
/*================================================================================================*/
typedef uint8 Adc_SamplingTimeType;
/*================================================================================================*/
/**
 * @typedef   Adc_VoltageSourceType
 *            Reference voltage source
 *
 * @api
*/
/*================================================================================================*/
typedef uint16 Adc_VoltageSourceType;
/*================================================================================================*/
/**
 * @typedef   Adc_StreamNumSampleType
 *            Number of samples of a streaming conversion buffer
 *
 * @api
*/
/*================================================================================================*/
typedef uint16 Adc_StreamNumSampleType;
/*================================================================================================*/
/**
 * @typedef   Adc_HwTriggerTimerType
 *            Type for the reload value of the ADC module embedded timer
 *
 * @api
*/
/*================================================================================================*/
typedef uint16 Adc_HwTriggerTimerType;
/*================================================================================================*/
/**
 * @typedef   Adc_QueueIndexType
 *           Index for the queue of groups
 *
 * @api
*/
/*================================================================================================*/
typedef uint8 Adc_QueueIndexType;

/**
 * @brief Maximum boundary for the Adc_QueueIndexType
*/
#define Adc_QueueIndexType_MAXIMUM 255

/**
 * @brief  Adc_LLD_ChannelConfiguration.
 *         This type contains channel configuration details.
 *         It contains the information like:
 *         - Fifo conversion command message
 *         - Resolution of Adc channel
 *
 * @api
*/
typedef struct
{
/**
 * @brief   Conversion command message.
 */
  CONST(uint32, ADC_CONST) Msg;
/**
 * @brief   Resolution of the ADC hardware (8 or 10 or 12 bits).
 */
  CONST(Adc_ResolutionType, ADC_CONST) Res;
} Adc_LLD_ChannelConfiguration;

/**
 * @brief  Adc_LLD_HWUnitConfiguration.
 *         This type contains hardware configuration details.
 *         It contains the information like:
 *         - Hardware unit id configured
 *         - hardware control register details
 *         - Calibration details
 *
 * @api
*/
typedef struct
{
#if (IPV_EQADC == IPV_EQADC_01_00_07_00) || defined(__DOXYGEN__)
/**
 * @brief   Adc hardware unit id.
 */
  CONST(Adc_HwUnitType, ADC_CONST) AdcHardwareUnitId;
#endif /* (IPV_EQADC == IPV_EQADC_01_00_07_00) || defined(__DOXYGEN__) */
/**
  * @brief  Configuration of ADC hardware control register.
  */
  CONST(uint32, ADC_CONST) AdcControlConfig;
#if (STD_ON == ADC_CALIBRATION) || defined(__DOXYGEN__)
/**
 * @brief   ADCn_CR control register value.
 */
    VAR(uint8, ADC_VAR) AdcCal;                /* ADCn_CR */
#endif/* (IPV_EQADC == IPV_EQADC_01_00_07_00) || defined(__DOXYGEN__) */
} Adc_LLD_HWUnitConfiguration;

/**
 * @brief  Adc_LLD_GroupConfiguration.
 *         This type contains Group configuration details.
 *         It contains the information like:
 *         - Hardware unit id to which the group belongs to
 *         - Access mode of group
 *         - Notification function pointer
 *         - Number of streaming samples for streaming mode
 *         - Number of channels assigned to this group
 *
 * @api
*/
typedef struct
{
/**
 * @brief Hw unit to which the group belongs to.
*/
  CONST(Adc_HwUnitType, ADC_CONST) HWUnit;
/**
 * @brief ADC_ACCESS_MODE_SINGLE, ADC_ACCESS_MODE_STREAMING.
*/
  CONST(Adc_GroupAccessModeType , ADC_CONST) AccessMode;
/**
 * @brief conversion mode (OneShot/Continuous).
*/
  CONST(Adc_GroupConvModeType , ADC_CONST) mode;
/**
 * @brief Samples alignment.
*/
  CONST(Adc_GroupISRAlignSamples_Type, ADC_CONST) ISRAlignSamples;
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) || defined(__DOXYGEN__)
/**
 * @brief Priority of the group.
*/
  CONST(Adc_GroupPriorityType , ADC_CONST) Priority;
#endif
/**
 * @brief Replacement mode (Abort restart or suspend resume) of group.
*/
  CONST(Adc_GroupReplacementType , ADC_CONST) ReplacementMode;
/**
 * @brief Trigger source (Hw/Sw trigger) of group.
*/
  CONST(Adc_TriggerSourceType , ADC_CONST) TriggerSource;
#if (STD_ON==ADC_HW_TRIGGER_API) || defined(__DOXYGEN__)
/**
 * @brief Trigger Edge (Rising or falling) for hardware triggered groups.
*/
  CONST(Adc_HwTriggerSignalType , ADC_CONST) TriggerEdge;
/**
 * @brief Resource of the selected hw trigger.
*/
  CONST(Adc_HwTriggerTimerType, ADC_CONST) HwResource;
#endif
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY) || defined(__DOXYGEN__)
/**
 * @brief Pointer to notification function.
*/
  CONST(Adc_NotifyType , ADC_CONST) Notification;
#endif
/**
 * @brief Fifo used for this group.
*/
  CONST(uint32, ADC_CONST) AdcGroupFifo;
/**
 * @brief Pointer to user defined result buffer.
*/
  P2P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) ResultsBufferPtr;
/**
 * @brief ADC_STREAM_BUFFER_LINEAR, ADC_STREAM_BUFFER_CIRCULAR.
*/
  CONST(Adc_StreamBufferModeType , ADC_CONST) BufferMode;
/**
 * @brief Number of samples in streaming access mode.
*/
  CONST(Adc_StreamNumSampleType , ADC_CONST) NumSamples;
/**
 * @brief Pointer to assigned channels in the group.
*/
  P2CONST(Adc_GroupDefType , ADC_VAR, ADC_APPL_CONST) Assignment;
/**
 * @brief Number of channels configured in the group.
*/
  CONST(Adc_ChannelType , ADC_CONST) AssignedChannelCount;
} Adc_LLD_GroupConfiguration;


/**
 * @brief  Adc_LLD_MultiConfig.
 *         This type contains General configuration details.
 *         It contains the information like:
 *         - Configured mode of ADC i.e DMA or INTERRUPT
 *         - Maximum groups configured in the configuration
 *         - Maximum groups configured in the configuration
 *         - Maximum depath of queue
 *         - Maximum number of channels in hardware unit
 *
 * @api
*/
typedef struct
{
/**
 * @brief   Dma or interrupt driven.
*/
  CONST(uint8, ADC_CONST) ADC_DMA_INTERRUPT;
/**
 * @brief   The number of the maximum groups in the current configuration.
*/
  CONST(uint8, ADC_CONST) ADC_MAX_GROUPS;
#if (IPV_EQADC == IPV_EQADC_01_00_07_00) || defined(__DOXYGEN__)
/**
 * @brief   The number of the maximum number of ADC hardware units configured in the configset.
*/
  CONST(uint8, ADC_CONST) ADC_MAX_HWCFG;
#endif /* (IPV_EQADC == IPV_EQADC_01_00_07_00) || defined(__DOXYGEN__) */
/**
 * @brief    Depth of the queue.
*/
  CONST(uint16, ADC_CONST) ADC_QUEUE_MAX_DEPTH;
/**
 * @brief   Number of channels of the hw unit x.
*/
  CONST(uint8, ADC_CONST) ADC_CHANNELS[ADC_HW_MAX];
/**
 * @brief   If dma driven then indicates the dma channel number for HW UNITS 0 and 1.
*/
  CONST(EQADC_fifo_Dma_Channel, ADC_CONST) EQADC_A_DMA_CHANNEL;
/* if Andorra 2M and Andorra4M or Monaco1.5M */
#if (IPV_EQADC == IPV_EQADC_01_00_11_01)||(IPV_EQADC == IPV_EQADC_01_00_10_00)||defined(__DOXYGEN__)
#else
/**
 * @brief   If dma driven then indicates the dma channel number for HW UNITS 2 and 3.
*/
  CONST(EQADC_fifo_Dma_Channel, ADC_CONST) EQADC_B_DMA_CHANNEL;
#endif /*(IPV_EQADC == IPV_EQADC_01_00_11_01)||(IPV_EQADC == IPV_EQADC_01_00_10_00)||
         defined(__DOXYGEN__) */
/**
 * @brief   Indicate if unit x is active (configured) STD_ON/STD_OFF.
*/
  CONST(uint8, ADC_CONST) ADC_HW_UNIT[ADC_HW_MAX];
} Adc_LLD_MultiConfig;


/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

#ifndef ADC_PRECOMPILE_SUPPORT
#define ADC_START_CONFIG_DATA_UNSPECIFIED
/**
 * @file    EQADC_LLD_CfgEx.h.
 *
 * @note Violates MISRA 2004 Advisory Rule 19.15, repeated include file MemMap.h
 * - See @ref EQADC_LLD_CfgEx_h_REF_2
 */
/*lint -save -e961 -e537 -e451 */
#include "MemMap.h"
/*lint -restore*/


#define ADC_STOP_CONFIG_DATA_UNSPECIFIED
/**
 * @file    EQADC_LLD_CfgEx.h.
 *
 * @note Violates MISRA 2004 Advisory Rule 19.15, repeated include file MemMap.h
 * - See @ref EQADC_LLD_CfgEx_h_REF_2
 */
/*lint -save -e961 -e537 -e451 */
#include "MemMap.h"
/*lint -restore*/
#endif

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#define ADC_START_SEC_CODE
/**
 * @file    EQADC_LLD_CfgEx.h
 *
 * @note Violates MISRA 2004 Advisory Rule 19.15, repeated include file MemMap.h
 * - See @ref EQADC_LLD_CfgEx_h_REF_2
 */
/*lint -save -e961 -e537 -e451 */
#include "MemMap.h"
/*lint -restore*/


#define ADC_STOP_SEC_CODE
/**
 * @file    EQADC_LLD_CfgEx.h.
 *
 * @note Violates MISRA 2004 Advisory Rule 19.15, repeated include file MemMap.h
 * - See @ref EQADC_LLD_CfgEx_h_REF_2
 */
/*lint -save -e961 -e537 -e451 */
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif

#endif /* EQADC_LLD_CFGEX_H */
/** @} */
