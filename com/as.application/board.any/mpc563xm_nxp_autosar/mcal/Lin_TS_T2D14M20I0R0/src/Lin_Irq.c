/**
    @file     Lin_Irq.c
    @version  2.0.0
    
    @brief    AUTOSAR Lin - Interrupt request handler implementation
    @details  Interrupt request handler implementation
    
    Project        AUTOSAR 3.0 MCAL
    Platform       PA
    Peripheral     ESCI
    Dependencies   
    
    ARVersion      3.0.0
    ARRevision     ASR_REL_3_0_REV_0003
    ARConfVariant  
    SWVersion      2.0.0
    BuildVersion   XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223
    
    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
    All Rights Reserved.
*/
/*==================================================================================================
==================================================================================================*/

/**
 * @page misra_violations MISRA-C:2004 violations
 *
 * @section LIN_IRQ_C_REF_1
 * Violates MISRA 2004 Required Rule 11.1, Conversions shall not be performed between a pointer 
 * to a function and any type other than an integral type. This violation is due to the pointer 
 * arithematic used to write/read the data to/from the registers.
 *
 * @section LIN_IRQ_C_REF_2
 * Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor directives or comments before 
 * "#include". This violation is not fixed since the inclusion of MemMap.h is as per Autosar 
 * requirement MEMMAP003.
 *
 * @section LIN_IRQ_C_REF_3
 * Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to prevent the 
 * contents of a header file being included twice. This is not a violation since all header 
 * files are protected against multiple inclusions.
 *
 * @section LIN_IRQ_C_REF_4
 * Violates MISRA 2004 Required Rule 19.15, Repeated include file Mcal.h 
 * This comes from the order of includes in the .c file and from include dependencies. 
 * As a safe approach, any file must include all its dependencies.
 */

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/*
#include "os.h"
* @remarks Covers LIN023
*/
#include "Std_Types.h"
#include "Lin.h"
#include "ESCI_LLD.h"
/**
 * @file Lin_Irq.c
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file Mcal.h: 
 *       See @ref LIN_IRQ_C_REF_4
 */
#include "Mcal.h"

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

#define LIN_AR_MAJOR_VERSION_IRQ_C   3
#define LIN_AR_MINOR_VERSION_IRQ_C   0
#define LIN_AR_PATCH_VERSION_IRQ_C   0

#define LIN_SW_MAJOR_VERSION_IRQ_C   2
#define LIN_SW_MINOR_VERSION_IRQ_C   0
#define LIN_SW_PATCH_VERSION_IRQ_C   0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/** @remarks Covers LIN062 */
#ifdef CHECK_AUTOSAR_VERSION
  #if (((LIN_AR_MAJOR_VERSION_IRQ_C != LIN_AR_MAJOR_VERSION) || \
        (LIN_AR_MINOR_VERSION_IRQ_C != LIN_AR_MINOR_VERSION)) || \
        (LIN_AR_PATCH_VERSION_IRQ_C != LIN_AR_PATCH_VERSION))
      #error "AutoSar Version Numbers of Lin_Irq.c and Lin.h are different"
  #endif
#endif

#if ((LIN_SW_MAJOR_VERSION_IRQ_C != LIN_SW_MAJOR_VERSION) || \
     (LIN_SW_MINOR_VERSION_IRQ_C != LIN_SW_MINOR_VERSION))
    #error "Software Version Numbers of Lin_Irq.c and Lin.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
  #if ((LIN_AR_MAJOR_VERSION_IRQ_C != STD_TYPES_AR_MAJOR_VERSION) || \
       (LIN_AR_MINOR_VERSION_IRQ_C != STD_TYPES_AR_MINOR_VERSION) || \
       (LIN_AR_PATCH_VERSION_IRQ_C != STD_TYPES_AR_PATCH_VERSION))
      #error "AutoSar Version Numbers of Lin_Irq.c and Std_Types.h are different"
  #endif
#endif

#ifdef CHECK_AUTOSAR_VERSION
  #if ((LIN_AR_MAJOR_VERSION_IRQ_C != ECUM_CFG_AR_MAJOR_VERSION) || \
       (LIN_AR_MINOR_VERSION_IRQ_C != ECUM_CFG_AR_MINOR_VERSION))
      #error "Software Version Numbers of Lin_Irq.c and EcuM_Cfg.h are different"
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

#define LIN_START_SEC_CODE
#include "MemMap.h"

#if defined(LinHWCh_0)
  ISR(Lin_LLD_InterruptHandler_ESCI_0);
#endif /* defined(LinHWCh_0) */

#if defined(LinHWCh_1)
  ISR(Lin_LLD_InterruptHandler_ESCI_1);
#endif /* defined(LinHWCh_1) */

#if defined(LIN_HWCh_0_USE_DMA)
  #if (LIN_HWCh_0_USE_DMA == STD_ON)
    ISR(Lin_InterruptFrame_eSci_A_Tx);
    ISR(Lin_InterruptFrame_eSci_A_Rx);
  #endif /* (LIN_HWCh_0_USE_DMA == STD_ON) */
#endif /* defined(LIN_HWCh_0_USE_DMA) */

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

#if defined(LinHWCh_0) || defined(__DOXYGEN__)
/**
 * @brief   Interrupt handler on ESCI_0
 * @details This function implements the ISR occurring on ESCI_0
 * 
 * @note    This interrupt handler is only present if Hardware 
 *          Channel 0 is used (with or without DMA).
 * 
 * @isr
 * 
 * @remarks Implements DLIN03000
 */
ISR(Lin_LLD_InterruptHandler_ESCI_0)
{
    ESCI_LLD_InterruptHandler(LinHWCh_0);
    /**
     * @note Violates MISRA 2004 Required Rule 11.1, Cast from unsigned int to pointer: 
     *       See @ref LIN_IRQ_C_REF_1
     */
    EXIT_INTERRUPT();
}
#endif /* defined(LinHWCh_0) */

#if defined(LinHWCh_1) || defined(__DOXYGEN__)
/**
 * @brief   Interrupt handler on ESCI_1
 * @details This function implements the ISR occurring on ESCI_1
 * 
 * @note    This interrupt handler is only present if Hardware 
 *          Channel 1 is used (with or without DMA).
 * 
 * @isr
 * 
 * @remarks Implements DLIN03000
 */
ISR(Lin_LLD_InterruptHandler_ESCI_1)
{
    ESCI_LLD_InterruptHandler(LinHWCh_1);
    /**
     * @note Violates MISRA 2004 Required Rule 11.1, Cast from unsigned int to pointer: 
     *       See @ref LIN_IRQ_C_REF_1
     */
    EXIT_INTERRUPT();
}
#endif /* defined(LinHWCh_1) */


#if defined(LIN_HWCh_0_USE_DMA) || defined(__DOXYGEN__)
#if (LIN_HWCh_0_USE_DMA == STD_ON) || defined(__DOXYGEN__)
/**
 * @brief   DMA Tx interrupt handler on ESCI_0
 * @details This function implements the ISR occurring on DMA Tx on ESCI_0
 * 
 * @note    This interrupt handler is only present if Hardware 
 *          Channel 0 is used with DMA.
 * 
 * @isr
 * 
 * @remarks Implements DLIN03000
 */
ISR(Lin_InterruptFrame_eSci_A_Tx)
{
     ESCI_LLD_Tx_InterruptHandler_eDma(LinHWCh_0);
     /**
      * @note Violates MISRA 2004 Required Rule 11.1, Cast from unsigned int to pointer: 
      *       See @ref LIN_IRQ_C_REF_1
      */
     EXIT_INTERRUPT();
}

/**
 * @brief   DMA Rx interrupt handler on ESCI_0
 * @details This function implements the ISR occurring on DMA Rx on ESCI_0
 * 
 * @note    This interrupt handler is only present if Hardware 
 *          Channel 0 is used with DMA.
 * 
 * @isr
 * 
 * @remarks Implements DLIN03000
 */
ISR(Lin_InterruptFrame_eSci_A_Rx)
{
     ESCI_LLD_Rx_InterruptHandler_eDma(LinHWCh_0);
     /**
      * @note Violates MISRA 2004 Required Rule 11.1, Cast from unsigned int to pointer: 
      *       See @ref LIN_IRQ_C_REF_1
      */
     EXIT_INTERRUPT();
}
#endif /* (LIN_HWCh_0_USE_DMA == STD_ON) */
#endif /* defined(LIN_HWCh_0_USE_DMA) */

#define LIN_STOP_SEC_CODE
/**
 * @file Lin_Irq.c
 * @note Violates MISRA 2004 Advisory Rule 19.1, Declaration before '#include': 
 *       See @ref LIN_IRQ_C_REF_2
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h: 
 *       See @ref LIN_IRQ_C_REF_3
 */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

/*! @} */
/* End of File */
