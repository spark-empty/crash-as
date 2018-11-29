/**
    @file    Siu_Adc_LLD.h
    @version 2.0.0

    @brief   AUTOSAR Adc - Brief description.
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
@page misra_violations MISRA-C:2004 violations

@section Siu_Adc_LLD_h_1
Violates MISRA 2004 Advisory Rule 19.15 : Repeated include file
This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement
MEMMAP003.
*/

#ifndef SIU_ADC_LLD_H
#define SIU_ADC_LLD_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Std_Types.h"
#include "Mcal.h"
#include "Adc_Cfg.h"
#include "Reg_eSys_SIU.h"
#include "Reg_Macros.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@{
@brief   Header file version information
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define SIU_ADC_LLD_VENDOR_ID            43

#define SIU_ADC_LLD_AR_MAJOR_VERSION     3
#define SIU_ADC_LLD_AR_MINOR_VERSION     0
#define SIU_ADC_LLD_AR_PATCH_VERSION     0
#define SIU_ADC_LLD_SW_MAJOR_VERSION     2
#define SIU_ADC_LLD_SW_MINOR_VERSION     0
#define SIU_ADC_LLD_SW_PATCH_VERSION     0
/**@}*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if header file and Std_Types.h file are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((SIU_ADC_LLD_AR_MAJOR_VERSION != STD_AR_MAJOR_VERSION) || \
         (SIU_ADC_LLD_AR_MINOR_VERSION != STD_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of SIU_Adc_LLD.h and Std_Types.h are different"
    #endif
#endif

/* Check if header file and Adc_Cfg.h file are of the same vendor */
#if (SIU_ADC_LLD_VENDOR_ID != ADC_VENDOR_ID_CFG)
#error "SIU_Adc_LLD.h and Adc_Cfg.h have different vendor IDs"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((SIU_ADC_LLD_AR_MAJOR_VERSION != ADC_AR_MAJOR_VERSION_CFG) || \
         (SIU_ADC_LLD_AR_MINOR_VERSION != ADC_AR_MINOR_VERSION_CFG) || \
         (SIU_ADC_LLD_AR_PATCH_VERSION != ADC_AR_PATCH_VERSION_CFG))
    #error "AutoSar Version Numbers of Siu_Adc_LLD.h and Adc_Cfg.h are different"
    #endif
#endif
/* Check if source file and ADC header file are of the same Software version */
#if ((SIU_ADC_LLD_SW_MAJOR_VERSION != ADC_SW_MAJOR_VERSION_CFG) || \
     (SIU_ADC_LLD_SW_MINOR_VERSION != ADC_SW_MINOR_VERSION_CFG) || \
     (SIU_ADC_LLD_SW_PATCH_VERSION != ADC_SW_PATCH_VERSION_CFG))
#error "Software Version Numbers of Siu_Adc_LLD.h and Adc_Cfg.h are different"
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
#define ADC_START_CONFIG_DATA_UNSPECIFIED
/**
@file  Siu_Adc_LLD.h
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h  See @ref Siu_Adc_LLD_h_1
*/
/*lint -save -e961 -e537 -e451 */
#include "MemMap.h"
/*lint -restore*/

/* Check if header file and MemMap.h file are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((SIU_ADC_LLD_AR_MAJOR_VERSION != MEMMAP_AR_MAJOR_VERSION) || \
         (SIU_ADC_LLD_AR_MINOR_VERSION != MEMMAP_AR_MINOR_VERSION) || \
         (SIU_ADC_LLD_AR_PATCH_VERSION != MEMMAP_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of SIU_Adc_LLD.h and MemMap.h are different"
    #endif
#endif

#define ADC_STOP_CONFIG_DATA_UNSPECIFIED
/**
@file  Siu_Adc_LLD.h
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h  See @ref Siu_Adc_LLD_h_1
*/
/*lint -save -e961 -e537 -e451 */
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
#define ADC_START_SEC_CODE
/**
@file  Siu_Adc_LLD.h
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h  See @ref Siu_Adc_LLD_h_1
*/
/* lint -save -e961 -e537 -e451 */
#include "MemMap.h"
/*lint -restore*/

#if (STD_ON == ADC_HW_TRIGGER_API)

#ifdef IPV_SIU
    #if (IPV_SIU != IPV_SIU_00_02_07_03_5) /* if ! Fado */
/*================================================================================================*/
/**
@brief      SIU_LLD_ResetAllHwTrigger
@details    Resets all hardware triggers
*/
/*================================================================================================*/
FUNC (void, ADC_CODE) SIU_LLD_ResetAllHwTrigger(void);

/*================================================================================================*/
/**
@brief      SIU_LLD_EnableHwTrigger
@details    This function will enable the hardware trigger source for the called FIFO.

@param[in]  GrpPtr - Pointer to group configurration
@param[in]  eQADC_AorB - eQADCA or eQADCB
@param[in]  Fifo_no - Fifo number
*/
/*================================================================================================*/
FUNC (void, ADC_CODE) SIU_LLD_EnableHwTrigger(P2CONST(Adc_LLD_GroupConfiguration, AUTOMATIC, ADC_APPL_DATA) GrpPtr, VAR(uint8, AUTOMATIC) eQADC_AorB, VAR(uint8, AUTOMATIC) Fifo_no);

/*================================================================================================*/
/**
@brief      SIU_LLD_DisableHwTrigger
@details    This function will disables the hardware trigger source for the called FIFO.

@param[in]  eQADC_AorB - eQADCA or eQADCB
@param[in]  Fifo_no - Fifo number
*/
/*================================================================================================*/
FUNC (void, ADC_CODE) SIU_LLD_DisableHwTrigger(VAR(uint8, AUTOMATIC) eQADC_AorB, VAR(uint8, AUTOMATIC) Fifo_no);
      #endif /* #if (IPV_SIU != IPV_SIU_00_02_07_03_5) */
      /* if Fado */
      #if (IPV_SIU == IPV_SIU_00_02_07_03_5)
#define SIU_ADC_LLM_Enable_Ext_Trigger(ext_trigg_src)   REG_WRITE16(SIU_ISEL4, (ext_trigg_src));
      #endif /* #if (IPV_SIU == IPV_SIU_00_02_07_03_5) */
#endif /* #ifdef IPV_SIU */

#endif /* #if (STD_ON == ADC_HW_TRIGGER_API) */
#define ADC_STOP_SEC_CODE
/**
@file  Siu_Adc_LLD.h
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h  See @ref Siu_Adc_LLD_h_1
*/
/* lint -save -e961 -e537 -e451 */
#include "MemMap.h"
/*lint -restore*/
#ifdef __cplusplus
}
#endif

#endif  /* SIU_ADC_LLD_H */
