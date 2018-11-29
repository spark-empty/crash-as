/*!
 * @addtogroup ADC
 * @{
 */
/**
    @file    Adc_LLD.h
    @version 2.0.0

    @brief   AUTOSAR Adc - driver middle layer file.
    @details This file realize the independence of the higher layer from the low layer.

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
 * @page misra_violations MISRA-C:2004 violations
 *
 * @section Adc_LLD_h_REF_1
 *          Violates MISRA 2004 Advisory Rul e 19.7, this violation is due to function like macros
 *          defined for register operations.Function like macros are used to reduce code complexity.
 *
 * @section Adc_LLD_h_REF_2
 *          Violates MISRA 2004 Advisory Rul e 19.15, repeated include file MemMap.h. There are
 *          different kinds of execution code sections.
*/
#ifndef ADC_LLD_H
#define ADC_LLD_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/


#include "EQADC_LLD.h"



/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@{
@brief   Header file version information
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define ADC_VENDOR_ID_LLD_H            43
#define ADC_AR_MAJOR_VERSION_LLD_H     3
#define ADC_AR_MINOR_VERSION_LLD_H     0
#define ADC_AR_PATCH_VERSION_LLD_H     0
#define ADC_SW_MAJOR_VERSION_LLD_H     2
#define ADC_SW_MINOR_VERSION_LLD_H     0
#define ADC_SW_PATCH_VERSION_LLD_H     0
/**@}*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and EQADC_LLD header file are of the same vendor */
#if (ADC_VENDOR_ID_LLD_H != EQADC_VENDOR_ID_LLD)
    #error "Adc_LLD.h and EQADC_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and EQADC_LLD header file are of the same Autosar version */
    #if ((ADC_AR_MAJOR_VERSION_LLD_H != EQADC_AR_MAJOR_VERSION_LLD) || \
         (ADC_AR_MINOR_VERSION_LLD_H != EQADC_AR_MINOR_VERSION_LLD) || \
         (ADC_AR_PATCH_VERSION_LLD_H != EQADC_AR_PATCH_VERSION_LLD))
    #error "AutoSar Version Numbers of Adc_LLD.h and EQADC_LLD.h are different"
    #endif
#endif

/* Check if source file and EQADC_LLD header file are of the same software version */
#if ((ADC_SW_MAJOR_VERSION_LLD_H != EQADC_SW_MAJOR_VERSION_LLD) || \
     (ADC_SW_MINOR_VERSION_LLD_H != EQADC_SW_MINOR_VERSION_LLD) || \
     (ADC_SW_PATCH_VERSION_LLD_H != EQADC_SW_PATCH_VERSION_LLD))
#error "Software Version Numbers of Adc_LLD.h and EQADC_LLD.h are different"
#endif


/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/**
@note Violates MISRA 2004 Advisory Rule 19.7, this violation is due to function like macros defined
for register operations - See @ref Adc_LLD_h_REF_1
*/
/*lint -save -e961 */
#define ResultSet(group)                  (ADC_GroupStatus[group].ResultIndex)
#define CurrentHwGroup(unit)              (ADC_UnitStatus[unit].HwQueue[0])
/*lint -restore */


/**
 * @brief   Defined to check the hardware triggered groups available in Hw Queue.
 */
#define ADC_HW_QUEUE ADC_QUEUE_MAX_DEPTH_MAX

/**
@{
@brief   Function mapping
@details Mapped the LLD functions to eQADC functions
*/
#define Adc_LLD_Init EQADC_LLD_Init
#define Adc_LLD_GetStreamLastPointer EQADC_LLD_GetStreamLastPointer
#define Adc_LLD_StartNormalConversion EQADC_LLD_StartNormalConversion

#if (ADC_DEINIT_API == STD_ON)
  #define Adc_LLD_DeInit EQADC_LLD_DeInit
#endif

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
  #define Adc_LLD_StartGroupConversion EQADC_LLD_StartGroupConversion
  #define Adc_LLD_StopGroupConversion EQADC_LLD_StopGroupConversion
#endif

#if (ADC_HW_TRIGGER_API == STD_ON)
  #define Adc_LLD_EnableHardwareTrigger EQADC_LLD_EnableHardwareTrigger
  #define Adc_LLD_DisableHardwareTrigger EQADC_LLD_DisableHardwareTrigger
#endif

#if (ADC_READ_GROUP_API == STD_ON)
  #define Adc_LLD_ReadGroup EQADC_LLD_ReadGroup
#endif

#ifdef ADC_DMA_SUPPORTED
#define Adc_StartDMAOperation EQADC_StartDMAOperation
#endif
/**@}*/

/**
 * @{
 *   API's service IDs for Catastrophic Errors Recovery (CER).
 *
 */

#define ADC_DMA_INTERRUPT_COMMON_FUNC_ID         0x11U

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

#ifndef ADC_PRECOMPILE_SUPPORT
#define ADC_START_CONFIG_DATA_UNSPECIFIED
/**
@note Violates MISRA 2004 Advisory Rule 19.15, repeated include file MemMap.h
- See @ref Adc_LLD_h_REF_2
*/
/* lint -save -e961 -e537 -e451 */
#include "MemMap.h"
/*lint -restore*/


#define ADC_STOP_CONFIG_DATA_UNSPECIFIED
/**
@note Violates MISRA 2004 Advisory Rule 19.15, repeated include file MemMap.h
- See @ref Adc_LLD_h_REF_2
*/
/* lint -save -e961 -e537 -e451 */
#include "MemMap.h"
/*lint -restore*/
#endif

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#define ADC_START_SEC_CODE
/**
@note Violates MISRA 2004 Advisory Rule 19.15, repeated include file MemMap.h
- See @ref Adc_LLD_h_REF_2
*/
/*lint -save -e961 -e537 -e451 */
#include "MemMap.h"
/*lint -restore*/



#define ADC_STOP_SEC_CODE
/**
@note Violates MISRA 2004 Advisory Rule 19.15, repeated include file MemMap.h
- See @ref Adc_LLD_h_REF_2
*/
/*lint -save -e961 -e537 -e451 */
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif

#endif /* ADC_LLD_H */
/** @} */