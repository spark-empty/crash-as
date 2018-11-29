/*!
 * @addtogroup ADC
 *@{
 */
/**
  @file    Adc.h
  @version 2.0.0

  @brief   AUTOSAR Adc - driver API.
  @details This file contains the ADC Autosar driver API.

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
 * @section Adc_h_REF_1
 *          Violates MISRA 2004 Advisory Rul e 19.15, repeated include file MemMap.h. There are
 *          different kinds of execution code section.
*/

#ifndef ADC_H
#define ADC_H

#ifdef __cplusplus
extern "C"{
#endif



/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
 * @remarks Covers:         BSW00374, BSW00379, BSW00318, ADC030
 */
#define ADC_MODULE_ID            123
#define ADC_VENDOR_ID            43
#define ADC_AR_MAJOR_VERSION     3
#define ADC_AR_MINOR_VERSION     0
#define ADC_AR_PATCH_VERSION     2
#define ADC_SW_MAJOR_VERSION     2
#define ADC_SW_MINOR_VERSION     0
#define ADC_SW_PATCH_VERSION     0

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
 *  The version check consist in check for included header files,
 *  it's between Adc.h and Std_Types .h; check for internal
 *  module .c and .h files, it's between Adc.h and Adc_Cfg.h.
 *
 * @note    Check version is between Adc.h and Std_Types.h and Adc.h and
 *          Adc_Cfg.h.
 *
 *
 */
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Std_Types header file are of the same AutoSar version */
    #if ((ADC_AR_MAJOR_VERSION != STD_TYPES_AR_MAJOR_VERSION) || \
         (ADC_AR_MINOR_VERSION != STD_TYPES_AR_MINOR_VERSION))
        #error "AutoSar Version Numbers of Adc.h and Std_Types.h are different"
    #endif
#endif

/* Check if source file and ADC configuration header file are of the same vendor */
#if (ADC_VENDOR_ID != ADC_VENDOR_ID_CFG)
    #error "Adc.h and Adc_Cfg.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and ADC configuration header file are of the same Autosar version */
    #if ((ADC_AR_MAJOR_VERSION != ADC_AR_MAJOR_VERSION_CFG) || \
         (ADC_AR_MINOR_VERSION != ADC_AR_MINOR_VERSION_CFG) || \
         (ADC_AR_PATCH_VERSION != ADC_AR_PATCH_VERSION_CFG))
    #error "AutoSar Version Numbers of Adc.h and Adc_Cfg.h are different"
    #endif
#endif
/* Check if source file and ADC configuration header file are of the same software version */
#if ((ADC_SW_MAJOR_VERSION != ADC_SW_MAJOR_VERSION_CFG) || \
     (ADC_SW_MINOR_VERSION != ADC_SW_MINOR_VERSION_CFG) || \
     (ADC_SW_PATCH_VERSION != ADC_SW_PATCH_VERSION_CFG))
#error "Software Version Numbers of Adc.h and Adc_Cfg.h are different"
#endif



/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/**
 * @{
 *    Development errors. The following errors shall be
 *          detectable by the ADC module depending on its configuration
 *          (development/ production mode).
 *
 *             ADC065, ADC229.
 *
 * @remarks Implements      DADC01001.
 */
#define ADC_E_UNINIT                (uint8)0x0AU
#define ADC_E_BUSY                  (uint8)0x0BU
#define ADC_E_IDLE                  (uint8)0x0CU
#define ADC_E_ALREADY_INITIALIZED   (uint8)0x0DU
#define ADC_E_PARAM_CONFIG          (uint8)0x0EU
#define ADC_E_PARAM_GROUP           (uint8)0x15U
#define ADC_E_WRONG_CONV_MODE       (uint8)0x16U
#define ADC_E_WRONG_TRIGG_SRC       (uint8)0x17U
#define ADC_E_NOTIF_CAPABILITY      (uint8)0x18U
#define ADC_E_BUFFER_UNINIT         (uint8)0x19U
#define ADC_E_QUEUE_FULL            (uint8)0x1AU
#if (ADC_SET_MODE_API == STD_ON)
#define ADC_E_SET_MODE              (uint8)0x1BU
#endif



/**
 * @{
 *    Catastrophic Errors Recovery (CER). The following errors shall be
 *          detectable by the ADC module in case of CER.
 *
 */

#define ADC_CER_TRIG_SRC_TYPE                     (uint8)0x29U
#define ADC_CER_MODE_TYPE_INT                     (uint8)0x2EU
#define ADC_CER_CORRUPTED_RES_TYPE                (uint8)0x30U
/**@}*/

/**
 * @{
 *   API's service IDs
 *
 *
 * @remarks Implements      DADC01002.
 */
#define ADC_INIT_ID 0x00U
#define ADC_DEINIT_ID 0x01U
#define ADC_STARTGROUPCONVERSION_ID 0x02U
#define ADC_STOPGROUPCONVERSION_ID 0x03U
#define ADC_VALUEREADGROUP_ID 0x04U
#define ADC_ENABLEHARDWARETRIGGER_ID 0x05U
#define ADC_DISABLEHARDWARETRIGGER_ID 0x06U
#define ADC_ENABLEGROUPNOTIFICATION_ID 0x07U
#define ADC_DISABLEGROUPNOTIFICATION_ID 0x08U
#define ADC_GETGROUPSTATUS_ID 0x09U
#define ADC_GETSTREAMLASTPOINTER_ID 0x0BU
#define ADC_GETVERSIONINFO_ID 0x0AU
#define ADC_SETUPRESULTBUFFER_ID 0x0CU
#if (ADC_SET_MODE_API == STD_ON)
#define ADC_SETMODE_ID 0x10U
#endif
/**@}*/

/**
 * @{
 *   API's service IDs for Catastrophic Errors Recovery (CER).
 *
 */

#define ADC_COPYQUEUEDATA2DMACOMMMANDBUFFER_ID      0x25U
#define ADC_IRQ_CFIFO_EMPTY_COMMON_FUNC_ID          0x12U
#define ADC_IRQ_RFIFO_FULL_COMMON_FUNC_ID           0x13U
#define ADC_EQADC_LLD_STARTNORMALCONVERSION_ID      0x33U
#define ADC_EQADC_LLD_READGROUP_ID                  0x34U
#define ADC_ENDNORMALCONV_ID                        0x35U
#define ADC_DMAENDNORMALCONV_ID                     0x36U
#define ADC_ADCDIG_LLD_READGROUP_ID                 0x37U
#define ADC_ADCDIG_LLD_GETSTREAMLASTPOINTER_ID      0x38U
/**@}*/
/*==================================================================================================
                                             ENUMS
==================================================================================================*/


/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
/**
@note Violates MISRA 2004 Advisory Rule 19.15, repeated include file MemMap.h - See @ref Adc_h_REF_1
*/
#define ADC_START_SEC_CODE
#include "MemMap.h"

FUNC(void, ADC_CODE) Adc_Init
(
  P2CONST(Adc_ConfigType, ADC_VAR, ADC_APPL_CONST) ConfigPtr
);


FUNC(Std_ReturnType, ADC_CODE) Adc_SetupResultBuffer
(
  VAR(Adc_GroupType, AUTOMATIC) Group,
  P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) DataBufferPtr
);



#if (ADC_DEINIT_API == STD_ON)
  FUNC(void, ADC_CODE) Adc_DeInit(void);
#endif /* #if (ADC_DEINIT_API == STD_ON) */


#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
  FUNC(void, ADC_CODE) Adc_StartGroupConversion
  (
    VAR(Adc_GroupType, AUTOMATIC) Group
  );

  FUNC(void, ADC_CODE) Adc_StopGroupConversion
  (
    VAR(Adc_GroupType, AUTOMATIC) Group
  );
#endif /* #if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */


FUNC(Std_ReturnType, ADC_CODE) Adc_ReadGroup
(
  VAR(Adc_GroupType, AUTOMATIC) Group,
  P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) DataPtr
);


#if (ADC_HW_TRIGGER_API == STD_ON)
  FUNC(void, ADC_CODE) Adc_EnableHardwareTrigger
  (
    VAR(Adc_GroupType, AUTOMATIC) Group
  );

  FUNC(void, ADC_CODE) Adc_DisableHardwareTrigger
  (
    VAR(Adc_GroupType, AUTOMATIC) Group
  );
#endif /* #if (ADC_HW_TRIGGER_API == STD_ON) */


#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
  FUNC(void, ADC_CODE) Adc_EnableGroupNotification
  (
    VAR(Adc_GroupType, AUTOMATIC) Group
  );

  FUNC(void, ADC_CODE) Adc_DisableGroupNotification
  (
    VAR(Adc_GroupType, AUTOMATIC) Group
  );
#endif /* #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON) */

FUNC(Adc_StatusType, ADC_CODE) Adc_GetGroupStatus
(
  VAR(Adc_GroupType, AUTOMATIC) Group
);

FUNC(Adc_StreamNumSampleType, ADC_CODE) Adc_GetStreamLastPointer
(
  VAR(Adc_GroupType, AUTOMATIC) Group,
  P2P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) PtrToSamplePtr
);


#if (ADC_VERSION_INFO_API == STD_ON)
  FUNC(void, ADC_CODE) Adc_GetVersionInfo
  (
    P2VAR(Std_VersionInfoType , AUTOMATIC, ADC_APPL_DATA) versioninfo
  );
#endif /* #if (ADC_VERSION_INFO_API == STD_ON) */

#if (ADC_SET_MODE_API == STD_ON)
  FUNC (Std_ReturnType, ADC_CODE) Adc_SetMode(VAR(Adc_SetModeType, AUTOMATIC) SetMode);
#endif

/**
@note Violates MISRA 2004 Advisory Rule 19.15, repeated include file MemMap.h - See @ref Adc_h_REF_1
*/
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ADC_H */
/** @} */
