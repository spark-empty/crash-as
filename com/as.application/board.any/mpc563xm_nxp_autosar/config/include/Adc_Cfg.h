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
#define ADC_HW_TRIGGER_API STD_OFF

/**
 * @brief   group notification mechanism is/isn't (STD_ON/STD_OFF) available at runtime
 *
 * @remarks Implements DADC08003.
 */
#define ADC_GRP_NOTIF_CAPABILITY STD_ON

/**
@{
@brief   Prioritization mechanism
@details Type of prioritization mechanism ADC_PRIORITY_HW, ADC_PRIORITY_HW_SW and ADC_PRIORITY_NONE
*/
#define ADC_PRIORITY_HW 0U
#define ADC_PRIORITY_HW_SW 1U
#define ADC_PRIORITY_NONE 2U
/**@}*/

#define ADC_PRIORITY_IMPLEMENTATION ADC_PRIORITY_NONE

#define ADC_DMA 0U
#define ADC_INTERRUPT 1U

/**
 * @brief   adds/removes (STD_ON/STD_OFF) the powerup calibration code to/from Adc_Init function.
 */
#define ADC_CALIBRATION                     (STD_ON)

/**
 * @brief   ADC timeout value used to wait while the FIFO's status is updating for the EOQ or to read the result or to disable the FIFO.
 */
#define ADC_TIMEOUT_COUNTER                 0xffffU


/** @brief  Defines the IP version for Monaco 1.5M */
#define IPV_EQADC 1001000UL
/** @brief max number of hw units - is 2 on Monaco 1.5M */
#define ADC_MAX_HW_UNITS 2U


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "EQADC_LLD_CfgEx.h"



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



/* Pre-compile configuration parameters - Autosar */
/**
 * @brief   development error detection enabled/disabled (STD_ON/STD_OFF)
 *
 * @remarks Implements DADC08002.
 */
#define ADC_DEV_ERROR_DETECT                STD_ON

/**
 * @brief   Add/remove (STD_ON/STD_OFF) the service Adc_GetVersionInfo()
 *          from the code.
 *
 * @remarks Implements DADC08004.
 */
#define ADC_VERSION_INFO_API                STD_ON

/**
 * @brief   Add/remove (STD_ON/STD_OFF) the service Adc_DeInit() from the
 *          code.
 *
 * @remarks Implements DADC08005.
 */
#define ADC_DEINIT_API                      STD_ON

/**
 * @brief   Add/remove (STD_ON/STD_OFF) the services
 *          Adc_StartGroupConversion()and Adc_StopGroupConversion() from
 *          the code.
 *
 * @remarks Implements DADC08006.
 */
#define ADC_ENABLE_START_STOP_GROUP_API     STD_ON

/**
 * @brief   Add/ Remove the services Adc_ReadGroup() from the code.
 */
#define ADC_READ_GROUP_API                  STD_ON

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
#define ADC_READ_GROUP_OPTIMIZATION (STD_OFF)

#define ADC_ENABLE_QUEUING      STD_ON



/* Enables the eQADC_A FIFO's */
#define ADC_EQADC_A_FIFO0_ENABLED   (STD_ON)
#define ADC_EQADC_A_FIFO1_ENABLED   (STD_OFF)
#define ADC_EQADC_A_FIFO2_ENABLED   (STD_OFF)
#define ADC_EQADC_A_FIFO3_ENABLED   (STD_OFF)
#define ADC_EQADC_A_FIFO4_ENABLED   (STD_OFF)
#define ADC_EQADC_A_FIFO5_ENABLED   (STD_OFF)

#define ADC_EQADC_A_CFIFO_ENABLED   (STD_ON)
#define ADC_EQADC_A_RFIFO_ENABLED   (STD_ON)
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


/**
 * @brief   Max queue depth configured across all configset.
 */
#define ADC_QUEUE_MAX_DEPTH_MAX 1U

/**
 * @brief   Max number of channels in one group across all configset.
 */
#define ADC_MAX_GROUP_CHANNELS 114U

/**
 * @brief   Max number of groups configured across all configset.
 */
#define ADC_MAX_GROUPS 1U

/**
 * @brief   Symbolic names of hardware units.
 *
 * @remarks Implements DADC08038
 */
#define  AdcHwUnit_0                0


/**
 * @brief   AUTOSAR Symbolic names of channels on all HW units.
 *
 * @remarks Implements DADC08019.
 */
#define  AdcChannel_0                0



/**
 * @brief Symbolic names of groups.
 *
 * @remarks Implements DADC08029.
 */
#define  AdcGroup_0                  0

/** @brief number of channels in respective groups */
#define ADC_CFGSET1_GROUP_0_CHANNELS      1

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

extern CONST(Adc_ConfigType, ADC_CONST)  AdcConfigSet_0;
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
extern Adc_ValueGroupType AdcResultBufferPointer[1];

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
