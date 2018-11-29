/*!
 * @addtogroup ADC
 *@{
 */
/**
  @file    Adc_NonASR.h
  @version 2.0.0

  @brief   AUTOSAR Adc - driver API.
  @details This file contains the ADC Non Autosar driver API.

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
 * @page    misra_violations MISRA-C:2004 violations
 *
 * @section Adc_NonASR_h_REF_1
 *          Violates MISRA 2004 Advisory Rul e 19.15, repeated include file MemMap.h. There are
 *          different kinds of execution code section.
*/

#ifndef ADC_NONASR_H
#define ADC_NONASR_H

#ifdef __cplusplus
extern "C"{
#endif



/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
 * @remarks Covers:         BSW00374, BSW00379, BSW00318, ADC030
 */
#define ADC_VENDOR_ID_NONASR            43
#define ADC_AR_MAJOR_VERSION_NONASR     3
#define ADC_AR_MINOR_VERSION_NONASR     0
#define ADC_AR_PATCH_VERSION_NONASR     2
#define ADC_SW_MAJOR_VERSION_NONASR     2
#define ADC_SW_MINOR_VERSION_NONASR     0
#define ADC_SW_PATCH_VERSION_NONASR     0

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/**
 *  Dependencies to other modules.
 *  The ADC module shall report production errors to the
 *          Diagnostic Event Manager (DEM).
 *
 * @note    The ADC module shall report production errors to the
 *          Diagnostic Event Manager (DEM).
 *
 *
 */
#include "Std_Types.h"
#include "Mcal.h"
#include "Adc_Cfg.h"


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/**
 *  The integration of incompatible files is to be avoided, so
 *  the minimum implementation is the version check between .c
 *  files and .h files.
 *
 * @note    Check if ADC ASR header file and ADC NON ASR sources file are of the
 *          same software version
 *
 */
/* Check if ADC ASR source file and ADC NON ASR sources file are of the same software version */
#if ((ADC_SW_MAJOR_VERSION_CFG != ADC_SW_MAJOR_VERSION_NONASR) || \
     (ADC_SW_MINOR_VERSION_CFG != ADC_SW_MINOR_VERSION_NONASR) || \
     (ADC_SW_PATCH_VERSION_CFG != ADC_SW_PATCH_VERSION_NONASR))
#error "Software Version Numbers of Adc_Cfg.h and Adc_NonASR.h are different"
#endif



/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

#if (ADC_ENABLE_HWTRIG_NONAUTO_API == STD_ON) || defined(__DOXYGEN__)
/**
 * @brief   API service ID's.
 *
 * @remarks Implements.
 * @remarks Covers.
 */
#define ADC_HWRESULTREADGROUP_ID    0x0DU
#define ADC_ENABLEHWTRIGGER_ID      0x0EU
#define ADC_DISABLEHWTRIGGER_ID     0x0FU

/**
 * @brief   Development errors generated for Non-Autsoar API's.
 */
#define ADC_E_PARAM_TRIGGER         (uint8)0x1CU
#endif

#if (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON)
#define ADC_E_WRONG_EN_CH_DIS_CH_GROUP  (uint8)0x1DU
#define ADC_E_WRONG_EN_CH_DIS_CH_ID     (uint8)0x1EU
#define ADC_ENABLE_CHANNEL_ID                   (uint8)0x12U
#define ADC_DISABLE_CHANNEL_ID                  (uint8)0x13U
#define ADC_CER_CHANNEL_ID_CORRUPTED_TYPE       (uint8)0x14U
#endif
/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/**
 * @enum    Adc_GroupAccessModeType
 *          Used for value received by Tressos interface configuration.
 *          Group Access mode type
 */
typedef enum
{
  ADC_NORMAL = 0U, /* Normal mode */
  ADC_ALTERNATE   /* Alternate mode */
} Adc_NonASR_DualClockModeType;

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
 * @brief          This structure is used to manipulate the MHT Multiple Hardware Triggered groups
 *
 * @api
 *
 * @requirements
 * @implements
 */
#if (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON)
typedef struct
{
 uint32 Adc_NCMR0; /* Precision configured channels */
 uint32 Adc_NCMR1; /* extended configured channels */
 uint32 Adc_NCMR2; /* External configured channels */
} Adc_NCMR_Type;
#endif /* (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON) */
/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

/*lint -save -e961 -e537 -e451 */
/**
@note Violates MISRA 2004 Advisory Rule 19.15, repeated include file MemMap.h
- See @ref Adc_NonASR_h_REF_1
*/
#define ADC_START_SEC_CODE
#include "MemMap.h"
/*lint -restore */

#if (ADC_HW_TRIGGER_API == STD_ON) || defined(__DOXYGEN__)
#if (ADC_ENABLE_HWTRIG_NONAUTO_API == STD_ON) || defined(__DOXYGEN__)

/**
 * @brief   Function enables the TriggerSource for group selected by "Group" parameter.
 *
 * @details This non autosar API is used to enable any one of the configured
 *          TriggerSource of the Group. When this non autosar API is used to
 *          enable the trigger source the CTU interrupt will be disabled by the
 *          driver. So user has to call the non autosar API Adc_HwResultReadGroup
 *          to read the converted result from the ADC hardware register.
 *
 * @note        The function Service ID[hex]: 0x0E.
 * @param[in]   Group         Index of group
 * @param[in]   TriggerSource Trigger source to be use for the group.
 *                           (Configuration file should contain the TriggerSource for called group).
 *
 * @remarks Covers       PR-MCAL-3176, PR-MCAL-3188.
 *                       DADC10000.
 * @remarks Implements
 */
FUNC(void, ADC_CODE) Adc_EnableHwTrigger
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(Adc_HwTriggerTimerType, AUTOMATIC) TriggerSource
);

/**
 * @brief   Function disable the TriggerSource for group selected by 'Group' parameter.
 *
 * @details This non autosar API is used to disable the already enabled
 *          TriggerSource of the Group.
 *
 * @note    The function Service ID[hex]: 0x0F.
 *
 * @param[in]  Group          Index of group
 * @param[in]  TriggerSource  Trigger source to be disable for the group.
 *                           (Configuration file should contain the TriggerSource for called group).
 *
 * @remarks Covers       PR-MCAL-3189, PR-MCAL-3190.
 *                       DADC10001.
 * @remarks Implements
 */
FUNC(void, ADC_CODE) Adc_DisableHwTrigger
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(Adc_HwTriggerTimerType, AUTOMATIC) TriggerSource
);

/**
 * @brief       Function reads the result of the hardware triggered
 *              groups conversion result.
 *
 * @details     This non autosar API is used to read the result of the hardware
 *              triggered groups conversion result from the ADC hardware register
 *              in this case the CTU interrupt will be disabled for the group.
 *
 * @note        The function Service ID[hex]: 0x0D.
 *
 * @param[in]   Group     Index of group.
 * @param[out]  DataPtr   Pointer to a buffer which will be filled by the
 *                       conversion results.
 *
 * @return      Adc_ValueGroupType pointer to internal buffer.
 *
 * @remarks Covers       PR-MCAL-3191, PR-MCAL-3192.
 *                       DADC10002.
 * @remarks Implements
 */
FUNC(Std_ReturnType, ADC_CODE) Adc_HwResultReadGroup
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) DataPtr
);

#endif /* #if (ADC_HW_TRIGGER_API == STD_ON) */
#endif /* #if (ADC_ENABLE_HWTRIG_NONAUTO_API == STD_ON) */

#if (ADC_DUAL_CLOCK_MODE == STD_ON) || defined(__DOXYGEN__)
FUNC(Std_ReturnType, ADC_CODE) ADC_SetClockMode
(
  VAR(Adc_NonASR_DualClockModeType, AUTOMATIC) ClockMode
);
#endif
/*lint -save -e961 -e537 -e451 */
/**
@note Violates MISRA 2004 Advisory Rule 19.15, repeated include file MemMap.h
- See @ref Adc_NonASR_h_REF_1
*/

/**
 * @brief   Function Enabling/Disabling a particular channel inside group.
 *
 * @details This Non Autosar API is used to enable/disable a channel
 *          of the Group.
 *
 * @note    The function Service ID[hex]: 0x12.
 *
 * @param[in]  Group          Index of group
 * @param[in]  Channel        Index of channel
 *
 * @remarks Covers       PR-MCAL-3233, DADCxxxxx.
 * @remarks Implements
 */
#if (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON)
FUNC(void, ADC_CODE) Adc_EnableChannel
(
  VAR(Adc_GroupType, AUTOMATIC) GroupId,
  VAR(Adc_ChannelType, AUTOMATIC) ChannelId
);
FUNC(void, ADC_CODE) Adc_DisableChannel
(
  VAR(Adc_GroupType, AUTOMATIC) GroupId,
  VAR(Adc_ChannelType, AUTOMATIC) ChannelId
);
#endif

#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/*lint -restore */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ADC_NONASR_H */
/** @} */
