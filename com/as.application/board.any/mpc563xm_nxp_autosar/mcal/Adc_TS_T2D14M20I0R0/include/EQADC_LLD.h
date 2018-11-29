/*!
 * @addtogroup ADC
 * @{
 */
 /**
    @file    EQADC_LLD.h
    @version 2.0.0

    @brief   AUTOSAR Adc - low level driver header file.
    @details EQADC low level driver API

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

@section EQADC_LLD_h_REF_1
Violates MISRA 2004 Advisory Rul e 19.15, repeated include file MemMap.h. There are different kinds
of execution code sections.
*/
#ifndef EQADC_LLD_H
#define EQADC_LLD_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Reg_Macros.h"
#include "Reg_eSys_EQADC.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@{
 * @brief   Header file version information.
 *
 * @remarks Covers BSW00374, BSW00379, BSW00318, ADC030
*/
#define EQADC_VENDOR_ID_LLD           43
#define EQADC_AR_MAJOR_VERSION_LLD    3
#define EQADC_AR_MINOR_VERSION_LLD    0
#define EQADC_AR_PATCH_VERSION_LLD    0
#define EQADC_SW_MAJOR_VERSION_LLD    2
#define EQADC_SW_MINOR_VERSION_LLD    0
#define EQADC_SW_PATCH_VERSION_LLD    0
/**@}*/
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and Reg_eSys_EQADC header file are of the same vendor */
#if (EQADC_VENDOR_ID_LLD != EQADC_VENDOR_ID_REG)
    #error "EQADC_LLD.h and Reg_eSys_EQADC.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Reg_eSys_EQADC header file are of the same Autosar version */
    #if ((EQADC_AR_MAJOR_VERSION_LLD != EQADC_AR_MAJOR_VERSION_REG) || \
         (EQADC_AR_MINOR_VERSION_LLD != EQADC_AR_MINOR_VERSION_REG) || \
         (EQADC_AR_PATCH_VERSION_LLD != EQADC_AR_PATCH_VERSION_REG))
    #error "AutoSar Version Numbers of EQADC_LLD.h and Reg_eSys_EQADC.h are different"
    #endif
#endif

/* Check if source file and ADC Reg_eSys_EQADC header file are of the same software version */
#if ((EQADC_SW_MAJOR_VERSION_LLD != EQADC_SW_MAJOR_VERSION_REG) || \
     (EQADC_SW_MINOR_VERSION_LLD != EQADC_SW_MINOR_VERSION_REG) || \
     (EQADC_SW_PATCH_VERSION_LLD != EQADC_SW_PATCH_VERSION_REG))
#error "Software Version Numbers of EQADC_LLD.h and Reg_eSys_EQADC.h are different"
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

/* External Declarations */
extern VAR(Adc_GroupStatusType, ADC_VAR) ADC_GroupStatus[];
extern VAR(Adc_UnitStatusType , ADC_VAR) ADC_UnitStatus[];
extern P2CONST(Adc_ConfigType , ADC_VAR, ADC_APPL_CONST) Adc_Cfg_Ptr;

extern VAR(uint8,ADC_VAR) EQADC_CFIFOChannelCount[EQADC_MAX_UNITS][ADC_MAX_FIFO];
extern VAR(uint8,ADC_VAR) EQADC_RFIFOChannelCount[EQADC_MAX_UNITS][ADC_MAX_FIFO];


/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#define ADC_START_SEC_CODE
/**
 * @file    EQADC_LLD.h.
 *
 * @note Violates MISRA 2004 Advisory Rule 19.15, repeated include file MemMap.h
 * - See @ref EQADC_LLD_h_REF_1
 */
/*lint -save -e961 -e537 -e451 */
#include "MemMap.h"
/*lint -restore*/

/**
 * @brief   This function starts the conversion on the specified hardware unit.
 *
 * @details This function starts the conversion on the specified hardware unit.
 *
 * @param[in]  unit - the used hw unit.
*/
FUNC(void, ADC_CODE) EQADC_LLD_StartNormalConversion(VAR(Adc_HwUnitType, AUTOMATIC) unit);
/**
 * @brief   This function initializes the ADC hardware module, and the ADC driver.
 *
 * @details This function initializes the ADC hardware module, and the ADC driver.
 *
 * @param[in]  CfgPtr  configuration data pointer.
 *
 * @remarks    Covers: ADC056, ADC077 and ADC307.
 * @remarks    Implements: DADC10000.
 */
FUNC(void, ADC_CODE) EQADC_LLD_Init(P2CONST(Adc_ConfigType, ADC_VAR, ADC_APPL_CONST) CfgPtr);

#if (STD_ON == ADC_DEINIT_API)
/**
 * @brief   This function deinitializes the ADC driver, and the ADC hardware.
 *
 * @details This function deinitializes the ADC driver, and ensures that the ADC
 *          hardware will be in the power on after reset state.
 *
 * @remarks    Covers: ADC110, ADC111, ADC228, ADC366, ADC413.
 * @remarks    Implements: DADC10001.
 */
FUNC(void, ADC_CODE) EQADC_LLD_DeInit(void);
#endif /* #if (STD_ON == ADC_DEINIT_API) */

#if (STD_ON == ADC_ENABLE_START_STOP_GROUP_API)
/**
 * @brief   This function starts the group conversion.
 *
 * @details This function starts the group conversion.
 *
 * @param[in]  Group  the group of which conversion will be started.
 * @param[in]  unit   the hardware unit. (on other platforms there are more hw units).
 *
 * @remarks    Covers: ADC061, ADC156, ADC259, ADC311, ADC332, ADC333, ADC340, ADC417.
 * @remarks    Implements: DADC10002.
 */
FUNC(void, ADC_CODE) EQADC_LLD_StartGroupConversion(
  VAR(Adc_GroupType, AUTOMATIC) Group,
  VAR(Adc_HwUnitType, AUTOMATIC) unit
);
/**
 * @brief   This function stops the group conversion.
 *
 * @details This function stops the group conversion.
 *
 * @param[in]  Group  the group of which conversion will be stopped.
 * @param[in]  unit   the hardware unit. (on other platforms there are more hw units).
 *
 * @remarks    Covers: ADC155, ADC260, ADC360, ADC368, ADC385, ADC386.
 * @remarks    Implements: DADC10003.
 */
FUNC(void, ADC_CODE) EQADC_LLD_StopGroupConversion
(
  VAR(Adc_GroupType, AUTOMATIC) Group,
  VAR(Adc_HwUnitType, AUTOMATIC) unit
);
#endif /* #if (STD_ON == ADC_ENABLE_START_STOP_GROUP_API) */

#if (STD_ON == ADC_HW_TRIGGER_API)
/**
 * @brief This function enables the hardware triggers for the specified group.
 *
 * @details This function enables the hardware triggers for the specified group.
 *
 * @param[in]  Group  the group for which the hardware triggers will be enabled.
 * @param[in]  unit   the hardware unit. (on other platforms there are more hw units)
 *
 * @remarks    Covers: ADC114, ADC144, ADC265, ADC311, ADC332, ADC333, ADC340, ADC417,
 *                     ADC336, ADC370, ADC432.
 * @remarks    Implements: DADC10005.
 */
FUNC(void, ADC_CODE) EQADC_LLD_EnableHardwareTrigger
(
  VAR(Adc_GroupType, AUTOMATIC) Group,
  VAR(Adc_HwUnitType, AUTOMATIC) unit
);
/**
 * @brief   This function disables the hardware triggers for the specified group.
 *
 * @details This function disables the hardware triggers for the specified group.
 *
 * @param[in]  Group  the group for which the hardware triggers will be disabled.
 * @param[in]  unit   the hardware unit. (on other platforms there are more hw units).
 *
 * @remarks    Covers: ADC116, ADC145, ADC157, ADC266, ADC361, ADC371, ADC429.
 * @remarks    Implements: DADC10006.
 */
FUNC(void, ADC_CODE) EQADC_LLD_DisableHardwareTrigger
(
  VAR(Adc_GroupType, AUTOMATIC) Group,
  VAR(Adc_HwUnitType, AUTOMATIC) unit
);
#endif /* #if (STD_ON == ADC_HW_TRIGGER_API) */
/**
 * @brief This function returns the first empty position in the result buffer.
 *
 * @details This function returns the first empty position in the result buffer.
 *
 * @param[in]  Group            the group index.
 * @param[in]  PtrToSamplePtr   pointer to the result buffer start address.
 *
 * @return     Number of samples from the result buffer.
 *
 * @remarks    Covers: ADC214, ADC216, ADC326, ADC327, ADC328, ADC375, ADC382, ADC387.
 * @remarks    Implements: DADC10007.
 */
FUNC(Adc_StreamNumSampleType, ADC_CODE) EQADC_LLD_GetStreamLastPointer
(
  VAR(Adc_GroupType, AUTOMATIC) Group,
  P2P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) PtrToSamplePtr
);

#if (STD_ON == ADC_READ_GROUP_API)
/**
 * @brief This function reads the converted data for the requested group.
 *
 *  @details Reads the converted data for the requested group.
 *
 * @param[in]  Group     The group number.
 * @param[out] DataPtr   Pointer to a buffer which will be filled by the conversion results.
 *
 * @return     Result of reading converted data
 *             - E_OK       In case of successfull read of the converted data.
 *             - E_NOT_OK   In case of an ongoing conversion.
 *
 *
 * @remarks    Covers: ADC075, ADC113, ADC122, ADC329, ADC330, ADC331, ADC359, ADC369, ADC383.
 * @remarks    Implements: DADC10004.
*/
FUNC(Std_ReturnType, ADC_CODE) EQADC_LLD_ReadGroup
(
  CONST(Adc_GroupType, ADC_CONST) Group,
  P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) DataPtr
);
#endif /* #if (STD_ON == ADC_READ_GROUP_API) */


#ifdef ADC_DMA_SUPPORTED
/**
 * @brief   This function programs the DMA transfers involved in the ADC conversion process.
 *
 * @details This function programs the DMA transfers involved in the ADC conversion process.
 *
 * @param[in]  unit  the used hw unit.
 */
FUNC(void, ADC_CODE) EQADC_StartDMAOperation(VAR(Adc_HwUnitType, AUTOMATIC) Unit);
#endif /* #ifdef ADC_DMA_SUPPORTED */
/**
 * @brief   This function implements the dequeue operation on the internal ADC queue
 *
 * @param[in]  unit - the used hw unit.
 * @param[in]  i - The current queue index.
 */
FUNC(void, ADC_CODE) EQADC_RemoveFromQueue
(
  CONST(Adc_HwUnitType, ADC_CONST) unit,
  CONST(Adc_QueueIndexType, ADC_CONST) i
);
/**
 * @brief   This function disables the CFIFO depends on the hardware unit and fifo index.
 *
 * @details This function disables the CFIFO depends on the hardware unit and fifo index.
 *
 * @param[in]  eQADC    eQADC number.
 * @param[in]  fifo_no  the fifo number.
 */
FUNC(void, ADC_CODE) EQADC_Disable_FIFO
(
  VAR(uint8, AUTOMATIC) eQADC,
  VAR(uint8, AUTOMATIC) fifo_no
);
#define ADC_STOP_SEC_CODE
/**
 * @file    EQADC_LLD.h.
 *
 * @note Violates MISRA 2004 Advisory Rule 19.15, repeated include file MemMap.h
 * - See @ref EQADC_LLD_h_REF_1
 */
/*lint -save -e961 -e537 -e451 */
#include "MemMap.h"
/*lint -restore*/


#ifdef __cplusplus
}
#endif

#endif /* #ifndef EQADC_LLD_H */
/** @} */
