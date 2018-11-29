/**
    @file    Mcu_Irq.c
    @version 2.0.0

@brief   AUTOSAR Mcu - File used by MCU that contain the ISRs.
@details This file contains the ISR functions used to serve the MCU interrupts.

Project AUTOSAR 3.0 MCAL
Platform PA
Peripheral FMPLL
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
/*!

 *  @addtogroup MCU
 *  @{
 */

/**
@page misra_violations MISRA-C:2004 violations

@section Mcu_IRQ_c_REF_1
Violates MISRA 2004 Advisory Rule 19.15, : Repeated include file MemMap.h, Precautions shall be
taken in order to prevent the contents of a header file being included twice This is not a violation
since all header files are protected against multiple inclusions

@section Mcu_IRQ_c_REF_2
MISRA-C 2004  11.1 VIOLATION, cast from unsigned long to pointer.
The cast can not be avoided as it is used to access memory mapped registers.

@section Mcu_IRQ_c_REF_3
MISRA-C 2004  11.1 VIOLATION, cast from unsigned int to pointer.
The cast can not be avoided as it is used to access memory mapped registers.

@section Mcu_IRQ_c_REF_4
MISRA-C 2004  8.1 VIOLATION, Function defined without a prototype in scope.
This violation is because of prototype of ISR function (No return typr, No argument)

@section Mcu_IRQ_c_REF_5
 MISRA  2004 Advisory  Rule  19.1,  only preprocessor statements and comments before
'#include'.This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003
*/
#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
2) needed interfaces from external units
3) internal and external interfaces from this unit
==================================================================================================*/
#include "Mcu_LLD.h"
/** @remarks Covers MCU051, MCU109 */
#include "Dem.h"
/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/** @remarks Covers BSW00374, BSW00318 */
#define MCU_IRQ_VENDOR_ID_C         43
#define MCU_IRQ_AR_MAJOR_VERSION_C  3
#define MCU_IRQ_AR_MINOR_VERSION_C  0
#define MCU_IRQ_AR_PATCH_VERSION_C  0
#define MCU_IRQ_SW_MAJOR_VERSION_C  2
#define MCU_IRQ_SW_MINOR_VERSION_C  0
#define MCU_IRQ_SW_PATCH_VERSION_C  0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and MCU_IRQ header file are of the same vendor */
#if (MCU_IRQ_VENDOR_ID_C != MCU_LLD_VENDOR_ID)
#error "Mcu_Irq.c and Mcu_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
/* Check if source file and MCU_IRQ header file are of the same Autosar version */
#if ((MCU_IRQ_AR_MAJOR_VERSION_C != MCU_LLD_AR_MAJOR_VERSION) || \
(MCU_IRQ_AR_MINOR_VERSION_C != MCU_LLD_AR_MINOR_VERSION) || \
(MCU_IRQ_AR_PATCH_VERSION_C != MCU_LLD_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of Mcu_Irq.c and Mcu_LLD.h are different"
#endif
#endif
/* Check if source file and MCU_IRQ header file are of the same Software version */
#if ((MCU_IRQ_SW_MAJOR_VERSION_C != MCU_LLD_SW_MAJOR_VERSION) || \
(MCU_IRQ_SW_MINOR_VERSION_C != MCU_LLD_SW_MINOR_VERSION) || \
(MCU_IRQ_SW_PATCH_VERSION_C != MCU_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of Mcu_Irq.c and Mcu_LLD.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
/* Check if source file and Dem header file are of the same version */
#if ((MCU_IRQ_AR_MAJOR_VERSION_C != DEM_AR_MAJOR_VERSION) || \
(MCU_IRQ_AR_MINOR_VERSION_C != DEM_AR_MINOR_VERSION))
#error "AutoSar Version Numbers of Monitor_LLD.c and Dem.h are different"
#endif
#endif
/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

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

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define MCU_START_SEC_CODE
/** @note Violates MISRA 2004  Advisory Rule 19.1, 19.15 : See @ref Mcu_IRQ_c_REF_1, Mcu_IRQ_c_REF_5 above*/
#include "MemMap.h"

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
    /**
     *   @brief   This function represents the ISR for loss of clock.
     *   @details If the loss of clock interrupt is enabled and an invalid 
     *            condition is detected, then the interrupt is triggered and the 
     *            event is reported.
     *
     *   @isr    
     */
    /**
    @remarks Covers
    @remarks Implements DMCU06000
     */
/**@remarks Covers MCU051, MCU053*/
#if ((MCU_CLOCKLOSS_ISR_USED == STD_ON) || defined(__DOXYGEN__))
/** @note   Violates MISRA 2004 Advisory Rule 8.1, See @ref Mcu_IRQ_c_REF_4 above*/
    ISR(Mcu_ClockLoss_ISR)
    {
    /** @note   Violates MISRA 2004 Advisory Rule 11.1, See @ref Mcu_IRQ_c_REF_2*/
        REG_WRITE32(FMPLL_SYNSR, FMPLL_SYNSR_LOCF);
/** @remarks Covers MCU051, MCU053 */
        Dem_ReportErrorStatus((uint16) MCU_E_CLOCK_FAILURE, DEM_EVENT_STATUS_FAILED);
    /** @note  Violates MISRA 2004 Advisory Rule 11.1, See @ref Mcu_IRQ_c_REF_3*/
        EXIT_INTERRUPT();
    }
#endif

    /**
     *   @brief   This function represents the ISR for loss of lock.
     *   @details If the loss of lock interrupt is enabled and an invalid 
     *            condition is detected, then the interrupt is triggered and the 
     *            event is reported.
     *
     *   @isr    
     */
    /**
    @remarks Covers MCU053
    @remarks Implements DMCU06000
     */
/**@remarks Covers MCU051, MCU053*/
#if ((MCU_LOCKLOSS_ISR_USED == STD_ON) || defined(__DOXYGEN__))
/** @note   Violates MISRA 2004 Advisory Rule 8.1, See @ref Mcu_IRQ_c_REF_4*/
    ISR(Mcu_LockLoss_ISR)
    {
    /** @note   Violates MISRA 2004 Advisory Rule 11.1, See @ref Mcu_IRQ_c_REF_2*/
        REG_WRITE32(FMPLL_SYNSR, FMPLL_SYNSR_LOLF);
/** @remarks Covers MCU051, MCU053 */
        Dem_ReportErrorStatus((uint16) MCU_E_CLOCK_FAILURE, DEM_EVENT_STATUS_FAILED);
    /** @note   Violates MISRA 2004 Advisory Rule 11.1, See @ref Mcu_IRQ_c_REF_3*/
        EXIT_INTERRUPT();
    }
#endif

#define MCU_STOP_SEC_CODE
/** @note  Violates MISRA 2004 Advisory Rule 19.15,19.1: See @ref Mcu_IRQ_c_REF_1,Mcu_IRQ_c_REF_5*/
#include "MemMap.h"

#ifdef __cplusplus
}
#endif
/** @} */
