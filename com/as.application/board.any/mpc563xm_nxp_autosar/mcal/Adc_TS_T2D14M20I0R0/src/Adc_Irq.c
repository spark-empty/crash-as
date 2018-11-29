/*!
 * @addtogroup ADC
 * @{
 */
/**
    @file    Adc_Irq.c
    @version 2.0.0

    @brief   AUTOSAR Adc - Interrupt Low Level Driver source file
    @details Autosar Adc Interrupt Low Level Driver source file.

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

@section Adc_Irq_c_REF_1
Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before '#include'.
The usage of the MemMap.h file violates this rule, but this mechanism is used to properly place into
their sections the code and variables.

@section Adc_Irq_c_REF_2
Violates MISRA 2004 Advisory Rul e 19.15, repeated include file MemMap.h. There are different kinds
of execution code section.

@section Adc_Irq_c_REF_3
Violates MISRA 2004 Advisory Rule 11.3, cast from unsigned long to pointer. This macro compute the
address of any register by using the hardware ofsset of the controller. The address calculated as an
unsigned int is passed to  a amcro for initializing the pointer with that address.

@section Adc_Irq_c_REF_4
Violates MISRA 2004 Advisory Rule 14.7, return statement before end of function. The return
statement are used to simplify the code structure and easier readability.

@section Adc_Irq_c_REF_5
Violates MISRA 2004 Advisory Rule 11.4, cast from pointer to pointer. This is used for the Speed
optimization of the memory access.

@section Adc_Irq_c_REF_6
Violates MISRA 2004 Advisory Rule 14.2, expected void type, assignment, increment or decrement.
This is used to read an unused value from an ADC register.

@section Adc_Irq_c_REF_7
Violates MISRA 2004 Advisory Rule 8.1, functions defined without a prototype in scope.
Not required from Autosar.

@section Adc_Irq_c_REF_8
Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer. This macro compute the
address of any register by using the hardware ofsset of the controller. The address calculated as an
unsigned int is passed to  a amcro for initializing the pointer with that address.

@section Adc_Irq_c_REF_9
Violates MISRA 2004 Advisory Rule 12.4, the right-hand operand of a logical "&&" or "||" operator
shall not contain side effects. This is necessary to simplify the code structure and easier
readability.
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/**
 * @brief   Dependencies to other modules.
 * @details The ADC module shall report production errors to the
 *          Diagnostic Event Manager (DEM).
 *
 * @note    The ADC module shall report production errors to the
 *          Diagnostic Event Manager (DEM).
 *
 * @requirements            ADC355, ADC267.
 *
 * @remarks Cover:          ADC355, ADC267.
 */
#include "Adc.h"
#include "Adc_LLD.h"
#include "Dma_LLD.h"
#include "Siu_Adc_LLD.h"
#include "Mcal.h"
#include "SchM_Adc.h"
#include "Dem.h"

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/**
@{
@brief   Source file version information
@remarks Covers BSW00374, BSW00318
*/
#define ADC_AR_VENDOR_ID_IRQ_C      43
#define ADC_AR_MAJOR_VERSION_IRQ_C  3
#define ADC_AR_MINOR_VERSION_IRQ_C  0
#define ADC_AR_PATCH_VERSION_IRQ_C  0
#define ADC_SW_MAJOR_VERSION_IRQ_C  2
#define ADC_SW_MINOR_VERSION_IRQ_C  0
#define ADC_SW_PATCH_VERSION_IRQ_C  0
/**@}*/
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/**
 * @brief   The integration of incompatible files is to be avoided, so
 *          the minimum implementation is the version check between .c
 *          files and .h files.
 * @details The version check consist in check for included header files,
 *          it's between Adc.h and Std_Types .h; check for internal
 *          module .c and .h files, it's between Adc.h and Adc_Cfg.h.
 *
 * @note    Check version is between Adc.h and Std_Types.h and Adc.h and
 *          Adc_Cfg.h.
 *
 * @requirements            ADC124.
 *
 * @remarks Cover:          ADC124.
 */
/* Check if source file and ADC header file are from the same vendor */
#if (ADC_AR_VENDOR_ID_IRQ_C != ADC_VENDOR_ID)
    #error "Adc_Irq.c and Adc.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and ADC header file are of the same Autosar version */
    #if ((ADC_AR_MAJOR_VERSION_IRQ_C != ADC_AR_MAJOR_VERSION) || \
         (ADC_AR_MINOR_VERSION_IRQ_C != ADC_AR_MINOR_VERSION) || \
         (ADC_AR_PATCH_VERSION_IRQ_C != ADC_AR_PATCH_VERSION))
      #error "AutoSar Version Numbers of Adc_Irq.c and Adc.h are different"
    #endif
#endif
/* Check if source file and ADC header file are of the same Software version */
#if ((ADC_SW_MAJOR_VERSION_IRQ_C != ADC_SW_MAJOR_VERSION) || \
     (ADC_SW_MINOR_VERSION_IRQ_C != ADC_SW_MINOR_VERSION) || \
     (ADC_SW_PATCH_VERSION_IRQ_C != ADC_SW_PATCH_VERSION))
  #error "Software Version Numbers of Adc_Irq.c and Adc.h are different"
#endif

/* Check if source file and ADC header file are from the same vendor */
#if (ADC_AR_VENDOR_ID_IRQ_C != ADC_VENDOR_ID_LLD_H)
    #error "Adc_Irq.c and Adc_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and ADC header file are of the same Autosar version */
    #if ((ADC_AR_MAJOR_VERSION_IRQ_C != ADC_AR_MAJOR_VERSION_LLD_H) || \
         (ADC_AR_MINOR_VERSION_IRQ_C != ADC_AR_MINOR_VERSION_LLD_H) || \
         (ADC_AR_PATCH_VERSION_IRQ_C != ADC_AR_PATCH_VERSION_LLD_H))
      #error "AutoSar Version Numbers of Adc_Irq.c and Adc_LLD.h are different"
    #endif
#endif
/* Check if source file and ADC header file are of the same Software version */
#if ((ADC_SW_MAJOR_VERSION_IRQ_C != ADC_SW_MAJOR_VERSION_LLD_H) || \
     (ADC_SW_MINOR_VERSION_IRQ_C != ADC_SW_MINOR_VERSION_LLD_H) || \
     (ADC_SW_PATCH_VERSION_IRQ_C != ADC_SW_PATCH_VERSION_LLD_H))
  #error "Software Version Numbers of Adc_Irq.c and Adc_LLD.h are different"
#endif

/* Check if source file and DMA header file are from the same vendor */
#if (ADC_AR_VENDOR_ID_IRQ_C != DMA_VENDOR_ID)
    #error "Adc_Irq.c and Dma_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and DMA header file are of the same Autosar version */
    #if ((ADC_AR_MAJOR_VERSION_IRQ_C != DMA_AR_MAJOR_VERSION) || \
         (ADC_AR_MINOR_VERSION_IRQ_C != DMA_AR_MINOR_VERSION) || \
         (ADC_AR_PATCH_VERSION_IRQ_C != DMA_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of Adc_Irq.c and Dma_LLD.h are different"
    #endif
#endif
/* Check if source file and DMA header file are of the same Software version */
#if ((ADC_SW_MAJOR_VERSION_IRQ_C != DMA_SW_MAJOR_VERSION) || \
     (ADC_SW_MINOR_VERSION_IRQ_C != DMA_SW_MINOR_VERSION) || \
     (ADC_SW_PATCH_VERSION_IRQ_C != DMA_SW_PATCH_VERSION))
    #error "Software Version Numbers of Adc_Irq.c and Dma_LLD.h are different"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Dem header file are of the same version */
    #if ((ADC_AR_MAJOR_VERSION_IRQ_C != SCHM_ADC_AR_MAJOR_VERSION) || \
         (ADC_AR_MINOR_VERSION_IRQ_C != SCHM_ADC_AR_MINOR_VERSION))
        #error "AutoSar Version Numbers of Adc_Irq.c and SchM_Adc.h are different"
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

/* put all ADC code into defined section */
#define ADC_START_SEC_CODE
/**
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
'#include' - See @ref Adc_Irq_c_REF_1
*/
/**
@note Violates MISRA 2004 Advisory Rule 19.15, repeated include file MemMap.h
- See @ref Adc_Irq_c_REF_2
*/
/*lint -save -e961 -e537 -e451 */
#include "MemMap.h"
/*lint -restore*/

#ifdef ADC_DMA_SUPPORTED

#if (ADC_EQADC_A_FIFO0_ENABLED == STD_ON)
ISR(Adc_Irq_eQADCA_PopResult0);
#endif /* ADC_EQADC_A_FIFO0_ENABLED == STD_ON */

#if (ADC_EQADC_A_FIFO1_ENABLED == STD_ON)
ISR(Adc_Irq_eQADCA_PopResult1);
#endif /* ADC_EQADC_A_FIFO1_ENABLED == STD_ON */

#if (ADC_EQADC_A_FIFO2_ENABLED == STD_ON)
ISR(Adc_Irq_eQADCA_PopResult2);
#endif /* ADC_EQADC_A_FIFO2_ENABLED == STD_ON */

#if (ADC_EQADC_A_FIFO3_ENABLED == STD_ON)
ISR(Adc_Irq_eQADCA_PopResult3);
#endif /* ADC_EQADC_A_FIFO3_ENABLED == STD_ON */

#if (ADC_EQADC_A_FIFO4_ENABLED == STD_ON)
ISR(Adc_Irq_eQADCA_PopResult4);
#endif /* ADC_EQADC_A_FIFO4_ENABLED == STD_ON */

#if (ADC_EQADC_A_FIFO5_ENABLED == STD_ON)
ISR(Adc_Irq_eQADCA_PopResult5);
#endif /* ADC_EQADC_A_FIFO5_ENABLED == STD_ON */

STATIC FUNC (void, ADC_CODE) Adc_Dma_Interrupt_Common_Func(VAR(Adc_HwUnitType, ADC_VAR) unit,
             VAR(uint32, AUTOMATIC) eQADC_AorB, VAR(uint32, AUTOMATIC) AdcFifoindex);

#endif /* #ifdef ADC_DMA_SUPPORTED */

#if (ADC_EQADC_A_FIFO0_ENABLED == STD_ON)
ISR(Adc_Irq_eQADCA_CFIFO0_Empty);
ISR(Adc_Irq_eQADCA_RFIFO0_Full);
#endif /* ADC_EQADC_A_FIFO0_ENABLED == STD_ON */

#if (ADC_EQADC_A_FIFO1_ENABLED == STD_ON)
ISR(Adc_Irq_eQADCA_CFIFO1_Empty);
ISR(Adc_Irq_eQADCA_RFIFO1_Full);
#endif /* ADC_EQADC_A_FIFO1_ENABLED == STD_ON */

#if (ADC_EQADC_A_FIFO2_ENABLED == STD_ON)
ISR(Adc_Irq_eQADCA_CFIFO2_Empty);
ISR(Adc_Irq_eQADCA_RFIFO2_Full);
#endif /* ADC_EQADC_A_FIFO2_ENABLED == STD_ON */

#if (ADC_EQADC_A_FIFO3_ENABLED == STD_ON)
ISR(Adc_Irq_eQADCA_CFIFO3_Empty);
ISR(Adc_Irq_eQADCA_RFIFO3_Full);
#endif /* ADC_EQADC_A_FIFO3_ENABLED == STD_ON */

#if (ADC_EQADC_A_FIFO4_ENABLED == STD_ON)
ISR(Adc_Irq_eQADCA_CFIFO4_Empty);
ISR(Adc_Irq_eQADCA_RFIFO4_Full);
#endif /* ADC_EQADC_A_FIFO4_ENABLED == STD_ON */

#if (ADC_EQADC_A_FIFO5_ENABLED == STD_ON)
ISR(Adc_Irq_eQADCA_CFIFO5_Empty);
ISR(Adc_Irq_eQADCA_RFIFO5_Full);
#endif /* ADC_EQADC_A_FIFO5_ENABLED == STD_ON */

#if (ADC_EQADC_A_CFIFO_ENABLED == STD_ON)
STATIC FUNC (void, ADC_CODE) Adc_Irq_CFIFO_Empty_Common_Func(VAR(Adc_HwUnitType, ADC_VAR) unit,
             VAR(uint32, AUTOMATIC) eQADC_AorB, VAR(uint32, AUTOMATIC) AdcFifoindex);
#endif /* (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) */

#if (ADC_EQADC_A_RFIFO_ENABLED == STD_ON)
STATIC FUNC (void, ADC_CODE) Adc_Irq_RFIFO_Full_Common_Func(VAR(Adc_HwUnitType, ADC_VAR) unit,
             VAR(uint32, AUTOMATIC) eQADC_AorB, VAR(uint32, AUTOMATIC) AdcFifoindex);

STATIC FUNC (Std_ReturnType, ADC_CODE) Adc_FIFO_Disable_Func(VAR(uint32, AUTOMATIC) eQADC_AorB,
             VAR(uint32, AUTOMATIC) AdcFifoindex);
#endif /* (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) */

/*=============================================================================
                                       LOCAL FUNCTIONS
===============================================================================*/

#if defined(ADC_DMA_SUPPORTED) || defined(__DOXYGEN__)
#if (ADC_EQADC_A_FIFO0_ENABLED == STD_ON) || defined(__DOXYGEN__)
/*=============================================================================*/
/**
 * @brief   This function implements the ISR for the conversion done from RFIFO0
 *          on the HW unit0 or unit1 of eQADC_A.
 *
 * @details The function implements the ISR for the HW unit0 or unit1 of eQADC_A.
 *
 * @param[in]       None.
 * @param[out]      None.
 * @param[in,out]   None.
 *
 * @return          None.
 *
 * @pre             None.
 * @post            None.
 *
 * @remarks Covers
 * @remarks Implements DADC05000
 * @remarks Test_case
 *
 * @isr
 */
/*=============================================================================*/

ISR(Adc_Irq_eQADCA_PopResult0)
{
     /* reset DMA channel interrupt flag (IRQ ACK) */
    Dma_ack_interrupt(EQADC_DMAeQADCA_FISR0_RFDF0);
    /* enter critical region */
    SchM_Enter_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_13);
Adc_Dma_Interrupt_Common_Func((Adc_HwUnitType)ADC_UNIT_0, (uint32)ADC_EQADC_A, (uint32)ADC_FIFO_0);
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref Adc_Irq_c_REF_8
*/
    /*lint -save -e961 */
    EXIT_INTERRUPT();
    /*lint -restore */
    /* exit critical region is done inside Adc_Dma_Interrupt_Common_Func */
}
#endif /* ADC_EQADC_A_FIFO0_ENABLED == STD_ON */

#if (ADC_EQADC_A_FIFO1_ENABLED == STD_ON) || defined(__DOXYGEN__)
/*=============================================================================*/
/**
 * @brief   This function implements the ISR for the conversion done from RFIFO1
 *          on the HW unit0 of eQADC_A.
 *
 * @details The function implements the ISR for the HW unit0  of eQADC_A.
 *
 * @param[in]       None.
 * @param[out]      None.
 * @param[in,out]   None.
 *
 * @return          None.
 *
 * @pre             None.
 * @post            None.
 *
 * @remarks Covers.
 * @remarks Implements DADC05000.
 * @remarks Test_case.
 *
 * @isr
 */
/*=============================================================================*/

ISR(Adc_Irq_eQADCA_PopResult1)
{
    /* reset DMA channel interrupt flag (IRQ ACK) */
    Dma_ack_interrupt(EQADC_DMAeQADCA_FISR1_RFDF1);
    /* enter critical region */
    SchM_Enter_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_13);
Adc_Dma_Interrupt_Common_Func((Adc_HwUnitType)ADC_UNIT_0, (uint32)ADC_EQADC_A, (uint32)ADC_FIFO_1);
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref Adc_Irq_c_REF_8
*/
    /*lint -save -e961 */
    EXIT_INTERRUPT();
    /*lint -restore */
    /* exit critical region is done inside Adc_Dma_Interrupt_Common_Func */
}
#endif /* ADC_EQADC_A_FIFO1_ENABLED == STD_ON */

#if (ADC_EQADC_A_FIFO2_ENABLED == STD_ON) || defined(__DOXYGEN__)
/*=============================================================================*/
/**
 * @brief   This function implements the ISR for the conversion done from RFIFO2
 *          on the HW unit0 of eQADC_A.
 *
 * @details The function implements the ISR for the HW unit0 of eQADC_A.
 *
 * @param[in]       None.
 * @param[out]      None.
 * @param[in,out]   None.
 *
 * @return          None.
 *
 * @pre             None.
 * @post            None.
 *
 * @remarks Covers.
 * @remarks Implements DADC05000.
 * @remarks Test_case.
 *
 * @isr
 */
/*=============================================================================*/

ISR(Adc_Irq_eQADCA_PopResult2)
{
    /* reset DMA channel interrupt flag (IRQ ACK) */
    Dma_ack_interrupt(EQADC_DMAeQADCA_FISR2_RFDF2);
    /* enter critical region */
    SchM_Enter_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_13);
Adc_Dma_Interrupt_Common_Func((Adc_HwUnitType)ADC_UNIT_0, (uint32)ADC_EQADC_A, (uint32)ADC_FIFO_2);
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref Adc_Irq_c_REF_8
*/
    /*lint -save -e961 */
    EXIT_INTERRUPT();
    /*lint -restore */
    /* exit critical region is done inside Adc_Dma_Interrupt_Common_Func */
}
#endif /* ADC_EQADC_A_FIFO2_ENABLED == STD_ON */

#if (ADC_EQADC_A_FIFO3_ENABLED == STD_ON) || defined(__DOXYGEN__)
/*================================================================================================*/
/**
 * @brief   This function implements the ISR for the conversion done from RFIFO3
 *  on the HW unit1 eQADC_A.
 *
 * @details The function implements the ISR for the HW unit1 of eQADC_A.
 *
 * @param[in]       None.
 * @param[out]      None.
 * @param[in,out]   None.
 *
 * @return          None.
 *
 * @pre             None.
 * @post            None.
 *
 * @remarks Covers.
 * @remarks Implements DADC05000.
 * @remarks Test_case.
 *
 * @isr
 */
/*================================================================================================*/

ISR(Adc_Irq_eQADCA_PopResult3)
{
    /* reset DMA channel interrupt flag (IRQ ACK) */
    Dma_ack_interrupt(EQADC_DMAeQADCA_FISR3_RFDF3);
    /* enter critical region */
    SchM_Enter_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_13);
Adc_Dma_Interrupt_Common_Func((Adc_HwUnitType)ADC_UNIT_1, (uint32)ADC_EQADC_A, (uint32)ADC_FIFO_3);
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref Adc_Irq_c_REF_8
*/
    /*lint -save -e961 */
    EXIT_INTERRUPT();
    /*lint -restore */
    /* exit critical region is done inside Adc_Dma_Interrupt_Common_Func */
}
#endif /* ADC_EQADC_A_FIFO3_ENABLED == STD_ON */

#if (ADC_EQADC_A_FIFO4_ENABLED == STD_ON) || defined(__DOXYGEN__)
/*================================================================================================*/
/**
 * @brief   This function implements the ISR for the conversion done from RFIFO4
 *          on the HW unit1 of eQADC_A.
 *
 * @details The function implements the ISR for the HW unit1 of eQADC_A.
 *
 * @param[in]       None.
 * @param[out]      None.
 * @param[in,out]   None.
 *
 * @return          None.
 *
 * @pre             None.
 * @post            None.
 *
 * @remarks Covers.
 * @remarks Implements DADC05000.
 * @remarks Test_case.
 *
 * @isr
 */
/*================================================================================================*/

ISR(Adc_Irq_eQADCA_PopResult4)
{
    /* reset DMA channel interrupt flag (IRQ ACK) */
    Dma_ack_interrupt(EQADC_DMAeQADCA_FISR4_RFDF4);
    /* enter critical region */
    SchM_Enter_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_13);
Adc_Dma_Interrupt_Common_Func((Adc_HwUnitType)ADC_UNIT_1, (uint32)ADC_EQADC_A, (uint32)ADC_FIFO_4);
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref Adc_Irq_c_REF_8
*/
    /*lint -save -e961 */
    EXIT_INTERRUPT();
    /*lint -restore */
    /* exit critical region is done inside Adc_Dma_Interrupt_Common_Func */
}
#endif /* ADC_EQADC_A_FIFO4_ENABLED == STD_ON */

#if (ADC_EQADC_A_FIFO5_ENABLED == STD_ON) || defined(__DOXYGEN__)
/*================================================================================================*/
/**
 * @brief   This function implements the ISR for the conversion done from RFIFO5
 *          on the HW unit1 of eQADC_A.
 *
 * @details The function implements the ISR for the HW unit1 of eQADC_A.
 *
 * @param[in]       None.
 * @param[out]      None.
 * @param[in,out]   None.
 *
 * @return          None.
 *
 * @pre             None.
 * @post            None.
 *
 * @remarks Covers.
 * @remarks Implements DADC05000.
 * @remarks Test_case.
 *
 * @isr
 */
/*================================================================================================*/

ISR(Adc_Irq_eQADCA_PopResult5)
{
    /* reset DMA channel interrupt flag (IRQ ACK) */
    Dma_ack_interrupt(EQADC_DMAeQADCA_FISR5_RFDF5);
    /* enter critical region */
    SchM_Enter_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_13);
Adc_Dma_Interrupt_Common_Func((Adc_HwUnitType)ADC_UNIT_1, (uint32)ADC_EQADC_A, (uint32)ADC_FIFO_5);
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref Adc_Irq_c_REF_8
*/
    /*lint -save -e961 */
    EXIT_INTERRUPT();
    /*lint -restore */
    /* exit critical region is done inside Adc_Dma_Interrupt_Common_Func */
}
#endif /* ADC_EQADC_A_FIFO5_ENABLED == STD_ON */

/*================================================================================================*/
/**
 * @brief   This function implements the ISR for the conversion done from RFIFO
 *          on the HW unit0 or unit1 of eQADC_A.
 *
 * @details The function implements the ISR for the HW unit0 or unit1 of eQADC_A.
 *
 * @param[in] eQADC_AorB   AdcFifoindex.
 * @param[in] eQADC_AorB   Always ADC_EQADC_A.
 * @param[in] AdcFifoindex 0 to 5.
 * @param[out]      None.
 * @param[in,out]   None.
 *
 * @return          None.
 *
 * @pre             None.
 * @post            None.
 *
 * @remarks Covers ADC078.
 * @remarks Implements DADC05000.
 * @rearks Test_case.
 *
 * @api
 */
/*================================================================================================*/
STATIC FUNC(void, ADC_CODE)Adc_Dma_Interrupt_Common_Func(VAR(Adc_HwUnitType, AUTOMATIC) unit,
            VAR(uint32, AUTOMATIC) eQADC_AorB, VAR(uint32, AUTOMATIC) AdcFifoindex)
{
    VAR(Adc_GroupType, AUTOMATIC) Group = (Adc_GroupType)0U;
    P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) pResult = NULL_PTR;
    VAR(Adc_ChannelType, ADC_VAR) ch = (Adc_ChannelType)0U;
    /* Streaming num samples should be atleast 1U */
    VAR(Adc_StreamNumSampleType, ADC_VAR) GroupSamples = (Adc_StreamNumSampleType)1U;
    VAR(volatile Adc_ChannelType, AUTOMATIC) ChIndex;
    VAR(Adc_ChannelType, AUTOMATIC) Temp;
    VAR(Std_ReturnType, AUTOMATIC) FuncReturn = (Std_ReturnType)E_OK;

    /*Obtain the active group*/
    Group=ADC_UnitStatus[unit].Queue[0];

pResult = (Adc_Cfg_Ptr->Groups[Group].ResultsBufferPtr[Group] + ADC_GroupStatus[Group].ResultIndex);
    GroupSamples = (Adc_Cfg_Ptr->Groups[Group].NumSamples);
    /* if ISR Alignment Samples is true, then align to right the samples of current group */
    if(Adc_Cfg_Ptr->Groups[Group].ISRAlignSamples == ADC_ISR_RIGHT_ALIGH)
    {
    for(ch=(Adc_ChannelType)0U;ch <Adc_Cfg_Ptr->Groups[Group].AssignedChannelCount; ch++)
      {
          ChIndex = EQADC_GroupChannelIndex(Group, ch);
          Temp = (14U - (Adc_Cfg_Ptr->Channels[unit][ChIndex].Res));
          /* Read RFIFO into RAM buffer  after right aligned */
          *(pResult + (ch*(GroupSamples))) = ((*(pResult + (ch*(GroupSamples))))>>Temp);
      }
    }
  /* increment ResultIndex with modulo 'NumSamples' to remember that another sample is completed */
    ADC_GroupStatus[Group].ResultIndex++;
    /* at least once the group was converted */
    ADC_GroupStatus[Group].AlreadyConverted = ADC_ALREADY_CONVERTED;
    if(ADC_GroupStatus[Group].Conversion ==ADC_BUSY)
    {
        /* ADC224*/
        ADC_GroupStatus[Group].Conversion=ADC_COMPLETED;
    }
    /* if all samples completed, wrap to 0 */
    if (ADC_GroupStatus[Group].ResultIndex >= Adc_Cfg_Ptr->Groups[Group].NumSamples)
    {
        /* ADC325*/
        ADC_GroupStatus[Group].Conversion=ADC_STREAM_COMPLETED;
        if((Adc_Cfg_Ptr->Groups[Group].BufferMode == ADC_STREAM_BUFFER_LINEAR)&&
           (Adc_Cfg_Ptr->Groups[Group].AccessMode==ADC_ACCESS_MODE_STREAMING))
        {
            /* Stop Conversion [ADC316] */
            /* the below func will stop the conversion and abort the current group conversion,
            is important to abort the current, othewise, another interrupt occurs after the stop */
            FuncReturn = Adc_FIFO_Disable_Func(eQADC_AorB, AdcFifoindex);
            if (FuncReturn == (Std_ReturnType)E_OK)
            {
                ADC_UnitStatus[unit].Status=ADC_IDLE;
                /* hardware triggered group */
                #if (STD_ON==ADC_HW_TRIGGER_API)
                if (Adc_Cfg_Ptr->Groups[Group].TriggerSource==ADC_TRIGG_SRC_HW)
                {
                    ADC_UnitStatus[unit].HwQueue[0] =0U;
                    ADC_UnitStatus[unit].HwQueueIndex = 0U;   /* Filled slots in the Hw queue */
                    /* Disable the hardware trigger source */
                    SIU_LLD_DisableHwTrigger((uint8)eQADC_AorB, (uint8)AdcFifoindex);
                }
                #endif
                #if (ADC_ENABLE_QUEUING == STD_ON)
                /* Check the group at zero'th location in the Queue */
                if(ADC_UnitStatus[unit].Queue[0]==Group)
                {
                    EQADC_RemoveFromQueue(unit,(uint8)0U);
                    if (ADC_UnitStatus[unit].QueueIndex> (Adc_QueueIndexType)0U)
                    {
                        EQADC_LLD_StartNormalConversion((Adc_HwUnitType)unit);
                    }
                }
                #else
                        /* no element will be present in the queue */
                        ADC_UnitStatus[unit].QueueIndex= (Adc_QueueIndexType)0;
                #endif
                #if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
                /* ADC083 -- ADC416 -- ADC080 -- ADC060*/
                if ((ADC_NOTIFICATION_ENABLED==ADC_GroupStatus[Group].Notification)&&
                    (Adc_Cfg_Ptr->Groups[Group].Notification != NULL_PTR))
                {
                    /* exit critical region */
                    SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_13);
                    /* ADC078 -- ADC104 -- ADC085*/
                    Adc_Cfg_Ptr->Groups[Group].Notification();
                }
                else
                #endif
                {
                    /* exit critical region */
                    SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_13);
                }
            }
            else
            {
                /* exit critical region */
                SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_13);
            }
            return;
        }

    }
    if (Adc_Cfg_Ptr->Groups[Group].mode==ADC_CONV_MODE_CONTINUOUS)
    {/* continuous conversion */
        if(ADC_UnitStatus[unit].Queue[0]==Group)
        {
            /* if all samples completed, wrap to 0 */
            if (ADC_GroupStatus[Group].ResultIndex >= Adc_Cfg_Ptr->Groups[Group].NumSamples)
            {
                ADC_GroupStatus[Group].ResultIndex = 0U;
                pResult = Adc_Cfg_Ptr->Groups[Group].ResultsBufferPtr[Group];
                /* configure the destination result address in TCD of the DMA channels */
           LLM_Wr_DMA_TCD_DADDR(((AdcFifoindex*2U) + (eQADC_AorB*EQADCB_DMACH_START) + 1U),pResult);
            }
        }
        #if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /* ADC083 -- ADC416 -- ADC080 -- ADC060*/
        if ((ADC_NOTIFICATION_ENABLED==ADC_GroupStatus[Group].Notification)&&
            (Adc_Cfg_Ptr->Groups[Group].Notification != NULL_PTR))
        {
          /* ADC078 -- ADC104 -- ADC085*/
          /* exit critical region */
          SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_13);
          Adc_Cfg_Ptr->Groups[Group].Notification();
        }
        else
        #endif
        {
          /* exit critical region */
          SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_13);
        }
        /* Start the DMA channel */
        Dma_start_channel((uint8)((AdcFifoindex*2U) + (eQADC_AorB*EQADCB_DMACH_START)));
        Dma_start_channel((uint8)((AdcFifoindex*2U) + (eQADC_AorB*EQADCB_DMACH_START) + 1U));
    }
    else if (Adc_Cfg_Ptr->Groups[Group].mode==ADC_CONV_MODE_ONESHOT)
    { /* one-shot conversion */
        if (Adc_Cfg_Ptr->Groups[Group].TriggerSource==ADC_TRIGG_SRC_SW) /* software trigger group */
        {
            ADC_UnitStatus[unit].Status=ADC_COMPLETED;
            ADC_GroupStatus[Group].ResultIndex = 0U;
            /* Disable the FIFO */
            FuncReturn = Adc_FIFO_Disable_Func(eQADC_AorB, AdcFifoindex);
            if (FuncReturn == (Std_ReturnType)E_OK)
            {
                #if (ADC_ENABLE_QUEUING == STD_ON)
                /* Check the group at zero'th location in the Queue */
                if(ADC_UnitStatus[unit].Queue[0]==Group)
                {
                    EQADC_RemoveFromQueue(unit,(uint8)0U);
                    if (ADC_UnitStatus[unit].QueueIndex> (Adc_QueueIndexType)0U)
                    {
                        EQADC_LLD_StartNormalConversion((Adc_HwUnitType)unit);
                    }
                }
                #else
                        /* no element will be present in the queue */
                        ADC_UnitStatus[unit].QueueIndex= (Adc_QueueIndexType)0;
                #endif
                #if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
                /* ADC083 -- ADC416 -- ADC080 -- ADC060*/
                if ((ADC_NOTIFICATION_ENABLED==ADC_GroupStatus[Group].Notification)&&
                    (Adc_Cfg_Ptr->Groups[Group].Notification != NULL_PTR))
                {
                    /* ADC078 -- ADC104 -- ADC085*/
                    /* exit critical region */
                    SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_13);
                    Adc_Cfg_Ptr->Groups[Group].Notification();
                }
                else
                #endif
                {
                    /* exit critical region */
                    SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_13);
                }
            }
            else
            {
                /* exit critical region */
                SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_13);
            }
        }
        #if (STD_ON == ADC_HW_TRIGGER_API)
        /* hardware trigger group */
        else if (Adc_Cfg_Ptr->Groups[Group].TriggerSource==ADC_TRIGG_SRC_HW)
        {
            if(ADC_UnitStatus[unit].Queue[0]==Group)
            {
               /* if all samples completed, wrap to 0 */
               if (ADC_GroupStatus[Group].ResultIndex >= Adc_Cfg_Ptr->Groups[Group].NumSamples)
               {
                    ADC_GroupStatus[Group].ResultIndex = 0U;
                    pResult = Adc_Cfg_Ptr->Groups[Group].ResultsBufferPtr[Group];
                    /* configure the destination result address in TCD of the DMA channels */
           LLM_Wr_DMA_TCD_DADDR(((AdcFifoindex*2U) + (eQADC_AorB*EQADCB_DMACH_START) + 1U),pResult);
               }
                /* Start the DMA channel0 */
               Dma_start_channel((uint8)((AdcFifoindex*2U) + (eQADC_AorB*EQADCB_DMACH_START)));
               Dma_start_channel((uint8)((AdcFifoindex*2U) + (eQADC_AorB*EQADCB_DMACH_START) + 1U));
            }
            #if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
            /* ADC083 -- ADC416 -- ADC080 -- ADC060*/
            if ((ADC_NOTIFICATION_ENABLED==ADC_GroupStatus[Group].Notification)&&
                (Adc_Cfg_Ptr->Groups[Group].Notification != NULL_PTR))
            {
                /* ADC078 -- ADC104 -- ADC085*/
                /* exit critical region */
                SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_13);
                Adc_Cfg_Ptr->Groups[Group].Notification();
            }
            else
            #endif
            {
                /* exit critical region */
                SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_13);
            }
        }
        else
        {
            /* Catastrophic Errors Recovery (CER) */
            Cer_ReportError((uint16)ADC_MODULE_ID, (uint8)0U,
                            (uint8)ADC_DMA_INTERRUPT_COMMON_FUNC_ID, (uint8)ADC_CER_TRIG_SRC_TYPE);
        }
        #endif
    }
    else
    {
       /* Catastrophic Errors Recovery (CER) */
       Cer_ReportError((uint16)ADC_MODULE_ID, (uint8)0U,
                       (uint8)ADC_DMA_INTERRUPT_COMMON_FUNC_ID, (uint8)ADC_CER_MODE_TYPE_INT);
    }
}
#endif /* #ifdef ADC_DMA_SUPPORTED */


#if (ADC_EQADC_A_FIFO0_ENABLED == STD_ON) || defined(__DOXYGEN__)
/*================================================================================================*/
/**
 * @brief   This function implements the ISR is called when CFIFO0 is not full
 *          on the HW unit0 of eQADC_A.
 *
 *@details  The function implements the ISR for the HW unit0 or unit1 of eQADC_A.
 *
 * @param[in]     None.
 * @param[out]    None.
 * @param[in,out] None.
 *
 * @return        None.
 *
 * @pre           None.
 * @post          None.
 *
 * @remarks       Covers.
 * @remarks       Implements DADC05000.
 * @remarks       Test_case.
 *
 * @isr
 */
/*================================================================================================*/
ISR(Adc_Irq_eQADCA_CFIFO0_Empty)
{

#if (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
Adc_Irq_CFIFO_Empty_Common_Func((Adc_HwUnitType)ADC_UNIT_0, (uint32)ADC_EQADC_A, (uint32)ADC_FIFO_0);
#endif /* (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) */
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref Adc_Irq_c_REF_8
*/
    /*lint -save -e961 */
    EXIT_INTERRUPT();
    /*lint -restore */
}

/*================================================================================================*/
/**
 * @brief   This function implements the ISR is called when RFIFO0 have data for
 *          the HW unit0 of eQADC_A.
 *
 * @details The function implements the ISR is called when RFIFO0 have data for
 *          the HW unit0 of eQADC_A.
 *
 * @param[in]     None.
 * @param[out]    None.
 * @param[in,out] None.
 *
 * @return        None.
 *
 * @pre           None.
 * @post          None.
 *
 * @remarks Covers.
 * @remarks Implements DADC05000.
 * @remarks Test_case.
 *
 * @isr
 */
/*================================================================================================*/
ISR(Adc_Irq_eQADCA_RFIFO0_Full)
{

#if (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
Adc_Irq_RFIFO_Full_Common_Func((Adc_HwUnitType)ADC_UNIT_0, (uint32)ADC_EQADC_A, (uint32)ADC_FIFO_0);
#endif /* (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) */
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref Adc_Irq_c_REF_8
*/
    /*lint -save -e961 */
    EXIT_INTERRUPT();
    /*lint -restore */
}
#endif /* (ADC_EQADC_A_FIFO1_ENABLED == STD_ON) */

#if (ADC_EQADC_A_FIFO1_ENABLED == STD_ON) || defined(__DOXYGEN__)
/*================================================================================================*/
/**
 * @brief   This function implements the ISR is called when CFIFO1 is not full on the HW unit0
 *          of eQADC_A.
 *
 * @details The function implements the ISR for the HW unit0 of eQADC_A.
 *
 * @param[in]     None.
 * @param[out]    None.
 * @param[in,out] None.
 *
 * @return        None.
 *
 * @pre           None.
 * @post          None.
 *
 * @remarks Covers.
 * @remarks Implements DADC05000.
 * @remarks Test_case.
 *
 * @isr
 */
/*================================================================================================*/
ISR(Adc_Irq_eQADCA_CFIFO1_Empty)
{

#if (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
Adc_Irq_CFIFO_Empty_Common_Func((Adc_HwUnitType)ADC_UNIT_0, (uint32)ADC_EQADC_A, (uint32)ADC_FIFO_1);
#endif /* (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) */
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref Adc_Irq_c_REF_8
*/
    /*lint -save -e961 */
    EXIT_INTERRUPT();
    /*lint -restore */
}

/*================================================================================================*/
/**
 * @brief   This function implements the ISR is called when RFIFO1 have data for the HW unit0 of
 *          eQADC_A.
 *
 * @details The function implements the ISR is called when RFIFO1 have data for the HW unit0 of
 *          eQADC_A.
 *
 * @param[in]     None.
 * @param[out]    None.
 * @param[in,out] None.
 *
 * @return        None.
 *
 * @pre           None.
 * @post          None.
 *
 * @remarks Covers.
 * @remarks Implements DADC05000.
 * @remarks Test_case.
 *
 * @isr
 */
/*================================================================================================*/
ISR(Adc_Irq_eQADCA_RFIFO1_Full)
{

#if (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
Adc_Irq_RFIFO_Full_Common_Func((Adc_HwUnitType)ADC_UNIT_0, (uint32)ADC_EQADC_A, (uint32)ADC_FIFO_1);
#endif /* (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) */
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref Adc_Irq_c_REF_8
*/
    /*lint -save -e961 */
    EXIT_INTERRUPT();
    /*lint -restore */
}
#endif /* (ADC_EQADC_A_FIFO1_ENABLED == STD_ON) */

#if (ADC_EQADC_A_FIFO2_ENABLED == STD_ON) || defined(__DOXYGEN__)
/*================================================================================================*/
/**
 * @brief   This function implements the ISR is called when CFIFO2 is not full on the HW unit0
 *          of eQADC_A.
 *
 * @details The function implements the ISR for the HW unit0 of eQADC_A.
 *
 * @param[in]     None.
 * @param[out]    None.
 * @param[in,out] None.
 *
 * @return        None.
 *
 * @pre           None.
 * @post          None.
 *
 * @remarks Covers.
 * @remarks Implements DADC05000.
 * @remarks Test_case.
 *
 * @isr
 */
/*================================================================================================*/
ISR(Adc_Irq_eQADCA_CFIFO2_Empty)
{

#if (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
Adc_Irq_CFIFO_Empty_Common_Func((Adc_HwUnitType)ADC_UNIT_0, (uint32)ADC_EQADC_A, (uint32)ADC_FIFO_2);
#endif /* (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) */
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref Adc_Irq_c_REF_8
*/
    /*lint -save -e961 */
    EXIT_INTERRUPT();
    /*lint -restore */
}
/*================================================================================================*/
/**
 * @brief   This function implements the ISR is called when RFIFO2 have data for the HW unit0 of
 *          eQADC_A.
 *
 * @details The function implements the ISR is called when RFIFO2 have data for the HW unit0 of
 *          eQADC_A.
 *
 * @param[in]     None.
 * @param[out]    None.
 * @param[in,out] None.
 *
 * @return        None.
 *
 * @pre           None.
 * @post          None.
 *
 * @remarks Covers.
 * @remarks Implements DADC05000.
 * @remarks Test_case.
 *
 * @isr
 */
/*================================================================================================*/
ISR(Adc_Irq_eQADCA_RFIFO2_Full)
{

#if (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
Adc_Irq_RFIFO_Full_Common_Func((Adc_HwUnitType)ADC_UNIT_0, (uint32)ADC_EQADC_A, (uint32)ADC_FIFO_2);
#endif /* (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) */
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref Adc_Irq_c_REF_8
*/
    /*lint -save -e961 */
    EXIT_INTERRUPT();
    /*lint -restore */
}
#endif /* (ADC_EQADC_A_FIFO2_ENABLED == STD_ON) */

#if (ADC_EQADC_A_FIFO3_ENABLED == STD_ON) || defined(__DOXYGEN__)
/*================================================================================================*/
/**
 * @brief   This function implements the ISR is called when CFIFO3 is not full on the HW unit1 of
 *          eQADC_A.
 *
 * @details The function implements the ISR for the HW unit1 of eQADC_A.
 *
 * @param[in]     None.
 * @param[out]    None.
 * @param[in,out] None.
 *
 * @return        None.
 *
 * @pre           None.
 * @post          None.
 *
 * @remarks Covers.
 * @remarks Implements DADC05000.
 * @remarks Test_case.
 *
 * @isr
 */
/*================================================================================================*/
ISR(Adc_Irq_eQADCA_CFIFO3_Empty)
{

#if (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
Adc_Irq_CFIFO_Empty_Common_Func((Adc_HwUnitType)ADC_UNIT_1, (uint32)ADC_EQADC_A,(uint32)ADC_FIFO_3);
#endif /* (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) */
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref Adc_Irq_c_REF_8
*/
    /*lint -save -e961 */
    EXIT_INTERRUPT();
    /*lint -restore */
}

/*================================================================================================*/
/**
 * @brief   This function implements the ISR is called when RFIFO3 have data for the HW unit1 of
 *          eQADC_A.
 *
 * @details The function implements the ISR is called when RFIFO3 have data for the HW unit1 of
 *          eQADC_A.
 *
 * @param[in]     None.
 * @param[out]    None.
 * @param[in,out] None.
 *
 * @return        None.
 *
 * @pre           None.
 * @post          None.
 *
 * @remarks Covers.
 * @remarks Implements DADC05000.
 * @remarks Test_case.
 *
 * @isr
 */
/*================================================================================================*/
ISR(Adc_Irq_eQADCA_RFIFO3_Full)
{

#if (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
Adc_Irq_RFIFO_Full_Common_Func((Adc_HwUnitType)ADC_UNIT_1, (uint32)ADC_EQADC_A, (uint32)ADC_FIFO_3);
#endif /* (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) */
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref Adc_Irq_c_REF_8
*/
    /*lint -save -e961 */
    EXIT_INTERRUPT();
    /*lint -restore */
}
#endif /* (ADC_EQADC_A_FIFO3_ENABLED == STD_ON) */

#if (ADC_EQADC_A_FIFO4_ENABLED == STD_ON) || defined(__DOXYGEN__)
/*================================================================================================*/
/**
 * @brief   This function implements the ISR is called when CFIFO4 is not full on the HW unit1 of
 *          eQADC_A.
 *
 * @details The function implements the ISR for the HW unit1 of eQADC_A.
 *
 * @param[in]     None.
 * @param[out]    None.
 * @param[in,out] None.
 *
 * @return        None.
 *
 * @pre           None.
 * @post          None.
 *
 * @remarks Covers.
 * @remarks Implements DADC05000.
 * @remarks Test_case.
 *
 * @isr
 */
/*================================================================================================*/
ISR(Adc_Irq_eQADCA_CFIFO4_Empty)
{

#if (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
Adc_Irq_CFIFO_Empty_Common_Func((Adc_HwUnitType)ADC_UNIT_1, (uint32)ADC_EQADC_A,(uint32)ADC_FIFO_4);
#endif /* (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) */
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref Adc_Irq_c_REF_8
*/
    /*lint -save -e961 */
    EXIT_INTERRUPT();
    /*lint -restore */
}

/*================================================================================================*/
/**
 * @brief   This function implements the ISR is called when RFIFO4 have data for the HW unit1 of
 *          eQADC_A.
 *
 * @details The function implements the ISR is called when RFIFO4 have data for the HW unit1 of
 *          eQADC_A.
 *
 * @param[in]     None.
 * @param[out]    None.
 * @param[in,out] None.
 *
 * @return        None.
 *
 * @pre           None.
 * @post          None.
 *
 * @remarks Covers.
 * @remarks Implements DADC05000.
 * @remarks Test_case.
 *
 * @isr
 */
/*================================================================================================*/
ISR(Adc_Irq_eQADCA_RFIFO4_Full)
{

#if (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
Adc_Irq_RFIFO_Full_Common_Func((Adc_HwUnitType)ADC_UNIT_1, (uint32)ADC_EQADC_A, (uint32)ADC_FIFO_4);
#endif /* (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) */
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref Adc_Irq_c_REF_8
*/
    /*lint -save -e961 */
    EXIT_INTERRUPT();
    /*lint -restore */
}
#endif /* (ADC_EQADC_A_FIFO4_ENABLED == STD_ON) */

#if (ADC_EQADC_A_FIFO5_ENABLED == STD_ON) || defined(__DOXYGEN__)
/*================================================================================================*/
/**
 * @brief   This function implements the ISR is called when CFIFO5 is not full on the HW unit1 of
 *          eQADC_A.
 *
 * @details The function implements the ISR for the HW unit1 of eQADC_A.
 *
 * @param[in]     None.
 * @param[out]    None.
 * @param[in,out] None.
 *
 * @return        None.
 *
 * @pre           None.
 * @post          None.
 *
 * @remarks Covers.
 * @remarks Implements DADC05000.
 * @remarks Test_case.
 *
 * @isr
 */
/*================================================================================================*/
ISR(Adc_Irq_eQADCA_CFIFO5_Empty)
{

#if (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
Adc_Irq_CFIFO_Empty_Common_Func((Adc_HwUnitType)ADC_UNIT_1, (uint32)ADC_EQADC_A,(uint32)ADC_FIFO_5);
#endif /* (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) */
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref Adc_Irq_c_REF_8
*/
    /*lint -save -e961 */
    EXIT_INTERRUPT();
    /*lint -restore */
}

/*================================================================================================*/
/**
 * @brief   This function implements the ISR is called when RFIFO5 have data for the HW unit1 of
 *          eQADC_A.
 *
 * @details The function implements the ISR is called when RFIFO5 have data for the HW unit1 of
 *          eQADC_A.
 *
 * @param[in]     None.
 * @param[out]    None.
 * @param[in,out] None.
 *
 * @return        None.
 *
 * @pre           None.
 * @post          None.
 *
 * @remarks Covers.
 * @remarks Implements DADC05000.
 * @remarks Test_case.
 *
 * @isr
 */
/*================================================================================================*/
ISR(Adc_Irq_eQADCA_RFIFO5_Full)
{

#if (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
Adc_Irq_RFIFO_Full_Common_Func((Adc_HwUnitType)ADC_UNIT_1, (uint32)ADC_EQADC_A, (uint32)ADC_FIFO_5);
#endif /* (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) */
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref Adc_Irq_c_REF_8
*/
    /*lint -save -e961 */
    EXIT_INTERRUPT();
    /*lint -restore */
}
#endif /* (ADC_EQADC_A_FIFO5_ENABLED == STD_ON) */

#if (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
/*================================================================================================*/
/**
 * @brief   This function implements the ISR is called when CFIFO is not full on the HW unit0 or
 *          unit1 of eQADC_A.
 *
 * @details The function implements the ISR for the HW unit0 or unit1 of eQADC_A.
 *
 * @param[in] eQADC_AorB   AdcFifoindex.
 * @param[in] eQADC_AorB   Always ADC_EQADC_A.
 * @param[in] AdcFifoindex 0 to 5.
 * @param[out]    None.
 * @param[in,out] None.
 *
 * @return        None.
 *
 * @pre           None.
 * @post          None.
 *
 * @remarks Covers ADC078.
 * @remarks Implements DADC05000.
 * @remarks Test_case.
 *
 * @api
 */
/*================================================================================================*/
STATIC FUNC (void, ADC_CODE) Adc_Irq_CFIFO_Empty_Common_Func(VAR(Adc_HwUnitType, AUTOMATIC) unit,
             VAR(uint32, AUTOMATIC) eQADC_AorB, VAR(uint32, AUTOMATIC) AdcFifoindex)
{
    VAR(volatile Adc_ChannelType, AUTOMATIC) ChannelsInGrp;
    VAR(volatile Adc_ChannelType, AUTOMATIC) ChIndex;
    VAR(volatile uint32, AUTOMATIC) FifoCmdmsg;
    VAR(Adc_GroupType, AUTOMATIC) Group = (Adc_GroupType)0U;

    /* enter critical region */
    SchM_Enter_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_14);
    /*Obtain the active group*/
    Group=ADC_UnitStatus[unit].Queue[0];
    ChannelsInGrp = EQADC_GroupChannels(Group);
    ChIndex = EQADC_GroupChannelIndex(Group,EQADC_CFIFOChannelCount[eQADC_AorB][AdcFifoindex]);
    if ((EQADC_CFIFOChannelCount[eQADC_AorB][AdcFifoindex] == (ChannelsInGrp-1U)) &&
        (Adc_Cfg_Ptr->Groups[Group].mode == ADC_CONV_MODE_ONESHOT))
    {
        /* Last ADC channel, hence set the EOQ Flag */
        FifoCmdmsg = ((Adc_Cfg_Ptr->Channels[unit][ChIndex].Msg)|(RESULT_FIFO_OFFSET*AdcFifoindex) |
                      ADC_WRITE_CONFIG_EOQ);
    }
    else
    {
        FifoCmdmsg = ((Adc_Cfg_Ptr->Channels[unit][ChIndex].Msg)|(RESULT_FIFO_OFFSET*AdcFifoindex));
    }
     /* 12 Bit conversion result */
    if (Adc_Cfg_Ptr->Channels[unit][ChIndex].Res == EQADC_BITS_RESOLUTION_12)
    {
        FifoCmdmsg = (FifoCmdmsg | EQADC_STD_CONFIG_SEL_12BIT_RES);
    }
     /* 10 Bit conversion result */
    else if (Adc_Cfg_Ptr->Channels[unit][ChIndex].Res == EQADC_BITS_RESOLUTION_10)
    {
        FifoCmdmsg = (FifoCmdmsg | EQADC_ALT_CONFIG_SEL_10BIT_RES);
    }
     /* 8 Bit conversion result */
    else if (Adc_Cfg_Ptr->Channels[unit][ChIndex].Res == EQADC_BITS_RESOLUTION_8)
    {
        FifoCmdmsg = (FifoCmdmsg | EQADC_ALT_CONFIG_SEL_8BIT_RES);
    }
    else
    {
        /* Catastrophic Errors Recovery (CER) */
        Cer_ReportError((uint16)ADC_MODULE_ID, (uint8)0U, (uint8)ADC_IRQ_CFIFO_EMPTY_COMMON_FUNC_ID,
                        (uint8)ADC_CER_CORRUPTED_RES_TYPE);
    }
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref Adc_Irq_c_REF_8
*/
    /*lint -save -e961 */
    /* Write command data to CFIFO PUSH register*/
    REG_WRITE32((EQADC_CFPR0(eQADC_AorB)+((uint32)(AdcFifoindex)<<2U)),FifoCmdmsg);
    /*lint -restore */
    /* Clear the CFFF bit in FISR1 register by writing 1 to it */
    /* ADC078 */
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref Adc_Irq_c_REF_8
*/
    /*lint -save -e961 */
    REG_WRITE32((EQADC_FISR0(eQADC_AorB)+((uint32)(AdcFifoindex)<<2U)),EQADC_FISRx_CFFF);
    /*lint -restore */
    /* Increment count for number of messages transferred to CFIFO*/
    EQADC_CFIFOChannelCount[eQADC_AorB][AdcFifoindex]++;
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref Adc_Irq_c_REF_8
*/
    /*lint -save -e961 */
    /* Disable till conversion is complete */
    REG_BIT_CLEAR16((EQADC_IDCR0(eQADC_AorB)+((uint32)(AdcFifoindex)<<1U)), EQADC_IDCR_CFFE);
    /*lint -restore */

    if((EQADC_CFIFOChannelCount[eQADC_AorB][AdcFifoindex]) == ChannelsInGrp)
    {
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref Adc_Irq_c_REF_8
*/
        /*lint -save -e961 */
        /* All commands for the group written, so Disable interrupt*/
        REG_BIT_CLEAR16((EQADC_IDCR0(eQADC_AorB)+((uint32)(AdcFifoindex)<<1U)), EQADC_IDCR_CFFE);
        /*lint -restore */
    }
    /* exit critical region */
    SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_14);
}
#endif /* (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) */


#if (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
/*================================================================================================*/
/**
 * @brief   This function implements the ISR is called when RFIFO have data for the HW unit0 or
 *          unit1 of eQADC_A.
 *
 * @details The function implements the ISR is called when RFIFO5 have data for the HW unit0 or
 *          unit1 of eQADC.
 *
 * @param[in] eQADC_AorB   AdcFifoindex.
 * @param[in] eQADC_AorB   Always ADC_EQADC_A.
 * @param[in] AdcFifoindex 0 to 5.
 * @param[out]    None.
 * @param[in,out] None.
 *
 * @return        None.
 *
 * @pre           None.
 * @post          None.
 *
 * @remarks Covers ADC078.
 * @remarks Implements DADC05000.
 * @remarks Test_case.
 *
 * @api
 */
/*================================================================================================*/
STATIC FUNC (void, ADC_CODE) Adc_Irq_RFIFO_Full_Common_Func(VAR(Adc_HwUnitType, ADC_VAR) unit,
             VAR(uint32, AUTOMATIC) eQADC_AorB, VAR(uint32, AUTOMATIC) AdcFifoindex)
{
    P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) pResult = NULL_PTR;
    VAR(Adc_ChannelType, ADC_VAR) ChannelsInGrp;
    /* Streaming num samples should be atleast 1U */
    VAR(Adc_StreamNumSampleType, AUTOMATIC) GroupSamples = (Adc_StreamNumSampleType)1U;
    VAR(Adc_GroupType, AUTOMATIC) Group = (Adc_GroupType)0;
    VAR(uint16, AUTOMATIC) ResultIdx;
    VAR(volatile Adc_ChannelType, AUTOMATIC) ChIndex;
    VAR(Adc_ChannelType, AUTOMATIC) Temp;
    VAR(volatile uint32, AUTOMATIC) tempBuffer;
    VAR(Std_ReturnType, AUTOMATIC) FuncReturn = (Std_ReturnType)E_OK;
    #if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        VAR(uint8, ADC_VAR) callNotification = (uint8)0;
    #endif /* STD_ON==ADC_GRP_NOTIF_CAPABILITY */

    /* enter critical region */
    SchM_Enter_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_15);
    /* To make sure tht the command is placed in the FIFO's push register to avoid any
       wrong result to be returned */
    if (EQADC_CFIFOChannelCount[eQADC_AorB][AdcFifoindex] !=0x00U)
    {
        /*Obtain the active group*/
        Group=ADC_UnitStatus[unit].Queue[0];
        ChannelsInGrp = EQADC_GroupChannels(Group);

        pResult = (Adc_Cfg_Ptr->Groups[Group].ResultsBufferPtr[Group]);
        GroupSamples = (Adc_Cfg_Ptr->Groups[Group].NumSamples);
        ResultIdx =((GroupSamples * EQADC_RFIFOChannelCount[eQADC_AorB][AdcFifoindex]) +
                    ADC_GroupStatus[Group].ResultIndex);
        ChIndex = EQADC_GroupChannelIndex(Group, EQADC_RFIFOChannelCount[eQADC_AorB][AdcFifoindex]);
        Temp = (14U - (Adc_Cfg_Ptr->Channels[unit][ChIndex].Res));
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref Adc_Irq_c_REF_8
*/
        /*lint -save -e961 */
        /* Read RFIFO into RAM buffer  after right aligned */
        pResult[ResultIdx] = (REG_READ16((EQADC_RFPR0(eQADC_AorB) +
                             ((uint32)(AdcFifoindex) << 2U)) + 2U) >>Temp);
        /*lint -restore */
/**
@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned int to pointer
- See @ref Adc_Irq_c_REF_8
*/
        /*lint -save -e961 */
        /* Clear the RFDF bit in FISR0 register by writing 1 to it */
        /* ADC078 */
        REG_WRITE32((EQADC_FISR0(eQADC_AorB) + ((uint32)(AdcFifoindex) << 2U)), EQADC_FISRx_RFDF);
        /*lint -restore */
        /* Increment count for messages read from RFIFO */
        EQADC_RFIFOChannelCount[eQADC_AorB][AdcFifoindex]++;
        if ((EQADC_RFIFOChannelCount[eQADC_AorB][AdcFifoindex]) == ChannelsInGrp)
        {
            /* Clear variable for next use */
            EQADC_CFIFOChannelCount[eQADC_AorB][AdcFifoindex] = 0U;
            EQADC_RFIFOChannelCount[eQADC_AorB][AdcFifoindex] = 0U;

       /* Disable CFIFO and RFIFO interrupt */
       REG_BIT_CLEAR16((EQADC_IDCR0(eQADC_AorB) + ((uint32)(AdcFifoindex) << 1U)), EQADC_IDCR_CFFE);
       REG_BIT_CLEAR16((EQADC_IDCR0(eQADC_AorB) + ((uint32)(AdcFifoindex) << 1U)), EQADC_IDCR_RFDE);

   /* increment ResultIndex with modulo 'NumSamples' to remember that another sample is completed */
            ADC_GroupStatus[Group].ResultIndex++;
            /* at least once the group was converted */
            ADC_GroupStatus[Group].AlreadyConverted = ADC_ALREADY_CONVERTED;

            if(ADC_GroupStatus[Group].Conversion ==ADC_BUSY)
            {
                ADC_GroupStatus[Group].Conversion=ADC_COMPLETED; /* ADC224*/
            }

            if (ADC_GroupStatus[Group].ResultIndex >= GroupSamples) /* if all samples completed, wrap to 0 */
            {
                    /* ADC325*/
                    ADC_GroupStatus[Group].Conversion=ADC_STREAM_COMPLETED;
                    if((Adc_Cfg_Ptr->Groups[Group].BufferMode == ADC_STREAM_BUFFER_LINEAR)&&
                       (Adc_Cfg_Ptr->Groups[Group].AccessMode==ADC_ACCESS_MODE_STREAMING))
                    {
          /* ADC078 Disable Interrupt Status*/
          /* Stop Conversion [ADC316] */
          /* the following func stop the conversion and abort the current group conversion,
             is important to abort the current, othewise, another interrupt occurs after the stop */
                        FuncReturn = Adc_FIFO_Disable_Func(eQADC_AorB, AdcFifoindex);
                        if (FuncReturn == (Std_ReturnType)E_OK)
                        {
                            ADC_UnitStatus[unit].Status=ADC_IDLE;

                            /* hardware triggered group */
                            #if (STD_ON==ADC_HW_TRIGGER_API)
                            if (Adc_Cfg_Ptr->Groups[Group].TriggerSource==ADC_TRIGG_SRC_HW)
                            {
                                ADC_UnitStatus[unit].HwQueue[0] =0U;
                                /* Filled slots in the Hw queue */
                                ADC_UnitStatus[unit].HwQueueIndex = 0U;
                                /* Disable the hardware trigger source */
                                SIU_LLD_DisableHwTrigger((uint8)eQADC_AorB, (uint8)AdcFifoindex);
                            }
                            #endif
                            #if (ADC_ENABLE_QUEUING == STD_ON)
                            /* Check the group at zero'th location in the Queue */
                            if(ADC_UnitStatus[unit].Queue[0]==Group)
                            {
                                EQADC_RemoveFromQueue(unit,(uint8)0U);
                                if (ADC_UnitStatus[unit].QueueIndex> (Adc_QueueIndexType)0U)
                                {
                                    EQADC_LLD_StartNormalConversion((Adc_HwUnitType)unit);
                                }
                            }
                            #else
                                    /* no element will be present in the queue */
                                    ADC_UnitStatus[unit].QueueIndex= (Adc_QueueIndexType)0;
                            #endif
                            #if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
                            /* ADC083 -- ADC416 -- ADC080 -- ADC060*/
                            if ((ADC_NOTIFICATION_ENABLED==ADC_GroupStatus[Group].Notification)&&
                                (Adc_Cfg_Ptr->Groups[Group].Notification != NULL_PTR))
                            {
                                /* exit critical region */
                                SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_15);
                                /* ADC078 -- ADC104 -- ADC085*/
                                Adc_Cfg_Ptr->Groups[Group].Notification();
                            }
                            else
                            #endif
                            {
                                /* exit critical region */
                                SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_15);
                            }
                        }
                        else
                        {
                            /* exit critical region */
                            SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_15);
                        }
/**
@note Violates MISRA 2004 Advisory Rule 14.7, return statement before end of function
- See @ref Adc_Irq_c_REF_4
*/
                    /*lint -save -e961 */
                    return;
                    /*lint -restore */
                    }
                    ADC_GroupStatus[Group].ResultIndex = 0U;
            }

            if (Adc_Cfg_Ptr->Groups[Group].mode==ADC_CONV_MODE_CONTINUOUS)
            {   /* continuous conversion */
                if((ADC_UnitStatus[unit].QueueIndex>0U) && (EQADC_CurrentGroup(unit) == Group))
                {
                    /* Enable CFIFO Fill and RFIFO Drain Interrupts */
         REG_BIT_SET16((EQADC_IDCR0(eQADC_AorB) + ((uint32)(AdcFifoindex) << 1U)), EQADC_IDCR_CFFE);
         REG_BIT_SET16((EQADC_IDCR0(eQADC_AorB) + ((uint32)(AdcFifoindex) << 1U)), EQADC_IDCR_RFDE);
                }
                #if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
                 /* ADC083 -- ADC416 -- ADC080 -- ADC060*/
                if ((ADC_NOTIFICATION_ENABLED==ADC_GroupStatus[Group].Notification)&&
                    (Adc_Cfg_Ptr->Groups[Group].Notification != NULL_PTR))
                {
                    /* ADC078 -- ADC104 -- ADC085*/
                    callNotification= (uint8) 1;
                }
                #endif
            }
            else if (Adc_Cfg_Ptr->Groups[Group].mode==ADC_CONV_MODE_ONESHOT)
            {   /* one-shot conversion software trigger source */
                if (Adc_Cfg_Ptr->Groups[Group].TriggerSource==ADC_TRIGG_SRC_SW)
                {
                    /* Change currentUnit.Mode=IDLE */
                    /* ADC325*/
                    ADC_GroupStatus[Group].Conversion=ADC_STREAM_COMPLETED;
                    ADC_UnitStatus[unit].Status=ADC_COMPLETED;
                    /* Disable the FIFO */
                    FuncReturn = Adc_FIFO_Disable_Func(eQADC_AorB, AdcFifoindex);
                    if (FuncReturn == (Std_ReturnType)E_OK)
                    {
                        #if (ADC_ENABLE_QUEUING == STD_ON)
                        /* Check the group at zero'th location in the Queue */
                        if(ADC_UnitStatus[unit].Queue[0]==Group)
                        {
                            EQADC_RemoveFromQueue(unit,(uint8)0U);
                            if (ADC_UnitStatus[unit].QueueIndex> (Adc_QueueIndexType)0U)
                            {
                                EQADC_LLD_StartNormalConversion((Adc_HwUnitType)unit);
                            }
                        }
                        #else
                            /* no element will be present in the queue */
                            ADC_UnitStatus[unit].QueueIndex= (Adc_QueueIndexType)0;
                        #endif
                        #if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
                         /* ADC083 -- ADC416 -- ADC080 -- ADC060*/
                        if ((ADC_NOTIFICATION_ENABLED==ADC_GroupStatus[Group].Notification)&&
                            (Adc_Cfg_Ptr->Groups[Group].Notification != NULL_PTR))
                        {
                            /* ADC078 -- ADC104 -- ADC085*/
                            callNotification= (uint8) 1;
                        }
                        #endif
                    }
                }/* one-shot conversion hardware trigger source */
                #if (ADC_HW_TRIGGER_API == STD_ON)
                else if (Adc_Cfg_Ptr->Groups[Group].TriggerSource==ADC_TRIGG_SRC_HW)
                {
                    /* Enable CFIFO Fill and RFIFO Drain Interrupts */
         REG_BIT_SET16((EQADC_IDCR0(eQADC_AorB) + ((uint32)(AdcFifoindex) << 1U)), EQADC_IDCR_CFFE);
         REG_BIT_SET16((EQADC_IDCR0(eQADC_AorB) + ((uint32)(AdcFifoindex) << 1U)), EQADC_IDCR_RFDE);
                    #if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
                     /* ADC083 -- ADC416 -- ADC080 -- ADC060*/
                    if ((ADC_NOTIFICATION_ENABLED==ADC_GroupStatus[Group].Notification)&&
                        (Adc_Cfg_Ptr->Groups[Group].Notification != NULL_PTR))
                    {
                        /* ADC078 -- ADC104 -- ADC085*/
                        callNotification= (uint8) 1;
                    }
                    #endif
                }
                else
                {
                    /* Catastrophic Errors Recovery (CER) */
                    Cer_ReportError((uint16)ADC_MODULE_ID, (uint8)0U,
                            (uint8)ADC_IRQ_RFIFO_FULL_COMMON_FUNC_ID, (uint8)ADC_CER_TRIG_SRC_TYPE);
                }
                #endif
            }
            else
            {
                /* Catastrophic Errors Recovery (CER) */
                Cer_ReportError((uint16)ADC_MODULE_ID, (uint8)0U,
                            (uint8)ADC_IRQ_RFIFO_FULL_COMMON_FUNC_ID, (uint8)ADC_CER_MODE_TYPE_INT);
            }
        }
        else
        {
            if ((EQADC_CFIFOChannelCount[eQADC_AorB][AdcFifoindex]))
            {
             /* Enable the CFIFO interrupt */
             REG_BIT_SET16((EQADC_IDCR0(eQADC_AorB)+((uint32)(AdcFifoindex)<< 1U)),EQADC_IDCR_CFFE);
            }
        }
    }
    else
    {
        for (Temp=0U; Temp < EQADC_FIFO_MAX_DEPTH; Temp++)
        {
           tempBuffer = REG_READ16((EQADC_RFPR0(eQADC_AorB) + ((uint32)(AdcFifoindex) << 2U)) + 2U);
        }
        /* Clear the RFDF bit in FISR0 register by writing 1 to it */
        REG_WRITE32((EQADC_FISR0(eQADC_AorB) + ((uint32)(AdcFifoindex) << 2U)), EQADC_FISRx_RFDF);
    }
    /* exit critical region */
    SchM_Exit_Adc( SCHM_ADC_INSTANCE_0, ADC_EXCLUSIVE_AREA_15);
    if (FuncReturn == (Std_ReturnType)E_OK)
    {
        #if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /* ADC083 -- ADC416 -- ADC080-- ADC060*/
        if (callNotification==(uint8)1)
        {
            /* call group notification */
            /* ADC078 -- ADC104 -- ADC085*/
            Adc_Cfg_Ptr->Groups[Group].Notification();
        }
        #endif
    }
}

/*================================================================================================*/
/**
 * @brief   This function is called from the ISR to disable the FIFO's of eQADC_A.
 *
 * @details This function is called from the ISR to disable the FIFO's of eQADC_A.
 *
 * @param[in] eQADC_AorB   AdcFifoindex.
 * @param[in] eQADC_AorB   Always ADC_EQADC_A.
 * @param[in] AdcFifoindex 0 to 5.
 * @param[out]    None.
 * @param[in,out] None.
 *
 * @return Std_ReturnType  Standard return type.
 * @retval E_OK: return on successul functionality excution.
 * @retval E_NOT_OK: return when the functionality is failed to excute due to production error.
 *
 * @pre           None.
 * @post          None.
 *
 * @remarks Covers ADC078.
 * @remarks Implements DADC05000.
 * @remarks Test_case.
 *
 * @api
 */
/*================================================================================================*/
STATIC FUNC(Std_ReturnType, ADC_CODE) Adc_FIFO_Disable_Func(VAR(uint32, AUTOMATIC) eQADC_AorB,
            VAR(uint32, AUTOMATIC) AdcFifoindex)
{
    VAR(volatile uint32, AUTOMATIC) tempBuffer;
    VAR(volatile uint32, AUTOMATIC) Timeout;
    VAR(Std_ReturnType, AUTOMATIC) TempReturn = (Std_ReturnType)E_OK;

    /* Disable the CFIFO */
    REG_WRITE16((EQADC_CFCR0(eQADC_AorB) + (((uint32)AdcFifoindex) << 1U)),EQADC_CFCR_MODE_DISABLED);
    /* Reload counter */
    Timeout = ADC_TIMEOUT_COUNTER;
/**
@note Violates MISRA 2004 Advisory Rule 12.4, the right-hand operand of a logical "&&" or "||"
operator shall not contain side effects - See @ref Adc_Irq_c_REF_9
*/
    /*lint -save -e961 */
    while((((REG_READ32(EQADC_CFSR(eQADC_AorB)))&((EQADC_CFSR_CFS0)>>(AdcFifoindex*2U)))!= 0x00U)&&
          (Timeout > (uint32)0U))
    {
        /* Decrease counter */
        Timeout--;
    }
    /*lint -restore */
    /** Test for FIFO's Status failure. */
    if ( Timeout == (uint32)0U )
    {
        /** Report production error and Return from function.  */
        Dem_ReportErrorStatus( (uint16)ADC_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
        TempReturn = (Std_ReturnType)E_NOT_OK;
/**
@note Violates MISRA 2004 Advisory Rule 14.7, return statement before end of function
- See @ref Adc_Irq_c_REF_4
*/
        /*lint -save -e961 */
        return(TempReturn);
        /*lint -restore */
    }
    EQADC_Disable_FIFO((uint8)eQADC_AorB, (uint8)AdcFifoindex);

    /* Clear RFIFO counter */
    /* Reload counter */
    Timeout = ADC_TIMEOUT_COUNTER;
/**
@note Violates MISRA 2004 Advisory Rule 12.4, the right-hand operand of a logical "&&" or "||"
operator shall not contain side effects - See @ref Adc_Irq_c_REF_9
*/
/*lint -save -e961 */
while((((REG_READ32(EQADC_FISR0(eQADC_AorB)+((uint32)(AdcFifoindex)<<2U)))& EQADC_FISRx_RFCTR)!=0x00U) &&
      (Timeout > (uint32)0U))
    {
        tempBuffer = REG_READ32(EQADC_RFPR0(eQADC_AorB) + ((uint32)(AdcFifoindex)<<2U));
        /* Decrease counter */
        Timeout--;
    }
    /*lint -restore */
    /** Test for FIFO's status failure. */
    if ( Timeout == (uint32)0U )
    {
        /** Report production error and Return from function.  */
        Dem_ReportErrorStatus( (uint16)ADC_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
        TempReturn = (Std_ReturnType)E_NOT_OK;
/**
@note Violates MISRA 2004 Advisory Rule 14.7, return statement before end of function
- See @ref Adc_Irq_c_REF_4
*/
        /*lint -save -e961 */
        return(TempReturn);
        /*lint -restore */
    }
    REG_WRITE32((EQADC_FISR0(eQADC_AorB) + ((uint32)(AdcFifoindex) << 2U)), (EQADC_FISRx_EOQF | EQADC_FISRx_RFDF | EQADC_FISRx_CFUF));
    #ifdef ADC_DMA_SUPPORTED
        /* Disable EQADC_AorB DMA interrupt */
        Dma_disable_interrupt((uint8)((AdcFifoindex*2U) + (eQADC_AorB*EQADCB_DMACH_START)));
        Dma_disable_interrupt((uint8)((AdcFifoindex*2U) + (eQADC_AorB*EQADCB_DMACH_START) + 1U));
    #endif /* #ifdef ADC_DMA_SUPPORTED */
    return(TempReturn);
}
#endif /* (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) */



#define ADC_STOP_SEC_CODE
/**
@note Violates MISRA 2004 Advisory Rule 19.15, repeated include file MemMap.h
- See @ref Adc_LLD_h_REF_2
*/
/**
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
'#include' - See @ref Adc_Irq_c_REF_1
*/
/*lint -save -e961 -e537 -e451 */
#include "MemMap.h"
/*lint -restore */


#ifdef __cplusplus
}
#endif
/** @} */
