/**
    @file             Can_Irq.c
    @version          2.0.0

    @brief            AUTOSAR Can module interface
    @details          Interrupt routines for Can driver.

    Project           AUTOSAR 3.0 MCAL
    Platform          PA
    Peripheral        FLEXCAN
    Dependencies      

    ARVersion         3.0.0
    ARRevision        ASR_REL_3_0_REV_0003
    ARConfVariant
    SWVersion         2.0.0
    BuildVersion      XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223

    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
    All Rights Reserved.
*/
/*==================================================================================================
==================================================================================================*/
/**
@page misra_violations MISRA-C:2004 violations

@section Can_Irq_c_REF_1
Violates MISRA 2004 Advisory Rule 19.12, Multiple use of '#/##' operators in macro definition.
This violation is due to the use of multiple #/## in a macro because some interrupts can process both Tx/Rx
in the same interrupt routine and have use twice this parameter. the parameter obtained with #/## is the same for
all functions called in the interrupt routine.

@section Can_Irq_c_REF_2
Violates MISRA 2004 Advisory Rule 19.13,'#/##' operator used.
This violation is due to the use of ## used to concatenate the Controller Index (A, B, ..) in ISR function name.

@section Can_Irq_c_REF_3
Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives.
This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003.

@section Can_Irq_c_REF_4
Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
This violation is because many controllers have defined Interrupt handlers with only 1 macro.

@section Can_Irq_c_REF_5
Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h
There are different kinds of execution code sections.

@section Can_Irq_c_REF_6
Violates MISRA 2004 Advisory Rule 17.4 , Array indexing shall be the only allowed form of pointer arithmetic.
This violation is due to the use of pointer arithematic, to access the channel parameters,
the indexing of the pointer is taken care and hence the unintended memory location will not
be accessed.

@section Can_Irq_c_REF_7
Violates MISRA 2004 Advisory Rule 11.1 [Encompasses MISRA 2004 Rule 11.1] cast from unsigned long to pointer.
This macro compute the address of any register by using the hardware ofsset of the controller. The address calculated as an unsigned int
is passed to  a amcro for initializing the pointer with that address. (ex: see REG_WRITE32 macro).
*/


/**
@file     Can_Irq.c
@brief    (CAN035) The module Can_Irq.c contains the implementation of interrupt frames.The implementation of the interrupt service routine shall be in Can.c
@remarks  Covers CAN035
@remarks  Implements DCAN00035
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
#include "Can.h"
#include "Can_LLD.h"
#include "CanIf_Cbk.h"
#include "Mcal.h"
#if (CAN_WAKEUP_SUPPORT == STD_ON)
  #include "EcuM_Cbk.h"
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */


/*==================================================================================================
                                    SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/* The integration of incompatible files shall be avoided. */
#define CAN_AR_MAJOR_VERSION_IRQ_C      3
#define CAN_AR_MINOR_VERSION_IRQ_C      0
#define CAN_AR_PATCH_VERSION_IRQ_C      0
#define CAN_SW_MAJOR_VERSION_IRQ_C      2
#define CAN_SW_MINOR_VERSION_IRQ_C      0
#define CAN_SW_PATCH_VERSION_IRQ_C      0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check of AUTOSAR specification version */
#ifdef CHECK_AUTOSAR_VERSION
#if ((CAN_AR_MAJOR_VERSION_LLD  != CAN_AR_MAJOR_VERSION_IRQ_C)|| \
     (CAN_AR_MINOR_VERSION_LLD  != CAN_AR_MINOR_VERSION_IRQ_C)|| \
     (CAN_AR_PATCH_VERSION_LLD  != CAN_AR_PATCH_VERSION_IRQ_C))
#error "Autosar Version number of Can_Irq.c and Can_LLD.h are different"
#endif
#endif

/* Check of vendor specific implementation version */
#if ((CAN_SW_MAJOR_VERSION_LLD  != CAN_SW_MAJOR_VERSION_IRQ_C)|| \
     (CAN_SW_MINOR_VERSION_LLD  != CAN_SW_MINOR_VERSION_IRQ_C)|| \
     (CAN_SW_PATCH_VERSION_LLD  != CAN_SW_PATCH_VERSION_IRQ_C))
#error "Incorrect version of CAN module included"
#endif

#define CAN_START_SEC_CODE
/**
@file  Can_Irq.c
@note  Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives. - See @ref Can_Irq_c_REF_3
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref Can_Irq_c_REF_5
*/
/*lint -save -e537 -e961*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                                    ISR FUNCTIONS PROTOTYPES
==================================================================================================*/
/* CAN controller A interrupts */
#ifdef CAN_FCA_INDEX

    ISR(Can_IsrFCA_ERR);

    #if (CAN_A_BUSOFFINT_SUPPORTED == STD_ON)
        ISR(Can_IsrFCA_BO);
    #endif /* (CAN_A_BUSOFFINT_SUPPORTED == STD_ON) */

    #if (CAN_WAKEUP_SUPPORT == STD_ON)
        #if (CAN_A_WAKEUPINT_SUPPORTED == STD_ON)
            #if (CAN_WKP_INT_SUPPORT == STD_ON)
                ISR(Can_IsrFCA_WKP);
            #endif /* (CAN_WKP_INT_SUPPORT == STD_ON) */
        #endif /* (CAN_A_WAKEUPINT_SUPPORTED == STD_ON) */
    #endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */

    #if ((CAN_A_TXINT_SUPPORTED == STD_ON) && (CAN_A_RXINT_SUPPORTED == STD_ON))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            ISR(Can_IsrFCA_UNI);
        #else /* (CAN_ISROPTCODESIZE == STD_OFF) */
            #if (CAN_A_FIFO_EN == STD_ON)
                #if (CAN_RXFIFO_EVENT_UNIFIED == STD_ON)
                    ISR(Can_IsrFCA_RxFifoEvents);
                #else /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
                    ISR(Can_IsrFCA_FrameAv);
                    ISR(Can_IsrFCA_Overf);
                    ISR(Can_IsrFCA_Warn);
                #endif /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
            #else /* (CAN_A_FIFO_EN == STD_OFF) */
                ISR(Can_IsrFCA_MB_00);
                ISR(Can_IsrFCA_MB_01);
                ISR(Can_IsrFCA_MB_02);
                ISR(Can_IsrFCA_MB_03);
                ISR(Can_IsrFCA_MB_04);
                ISR(Can_IsrFCA_MB_05);
                ISR(Can_IsrFCA_MB_06);
                ISR(Can_IsrFCA_MB_07);
            #endif /* (CAN_A_FIFO_EN == STD_OFF) */

            ISR(Can_IsrFCA_MB_08);
            ISR(Can_IsrFCA_MB_09);
            ISR(Can_IsrFCA_MB_10);
            ISR(Can_IsrFCA_MB_11);
            ISR(Can_IsrFCA_MB_12);
            ISR(Can_IsrFCA_MB_13);
            ISR(Can_IsrFCA_MB_14);
            ISR(Can_IsrFCA_MB_15);
            ISR(Can_IsrFCA_MB_16_31);
            ISR(Can_IsrFCA_MB_32_63);
        #endif /* (CAN_ISROPTCODESIZE == STD_OFF) */

    #elif ((CAN_A_TXINT_SUPPORTED == STD_OFF) && (CAN_A_RXINT_SUPPORTED == STD_ON))
        #if (CAN_ISROPTCODESIZE == STD_ON)
           ISR(Can_IsrFCA_UNI);
        #else /* (CAN_ISROPTCODESIZE == STD_OFF) */
            #if (CAN_A_FIFO_EN == STD_ON)
                #if (CAN_RXFIFO_EVENT_UNIFIED == STD_ON)
                    ISR(Can_IsrFCA_RxFifoEvents);
                #else /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
                    ISR(Can_IsrFCA_FrameAv);
                    ISR(Can_IsrFCA_Overf);
                    ISR(Can_IsrFCA_Warn);
                #endif /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
            #else /* (CAN_A_FIFO_EN == STD_OFF) */
                ISR(Can_IsrFCA_MB_00);
                ISR(Can_IsrFCA_MB_01);
                ISR(Can_IsrFCA_MB_02);
                ISR(Can_IsrFCA_MB_03);
                ISR(Can_IsrFCA_MB_04);
                ISR(Can_IsrFCA_MB_05);
                ISR(Can_IsrFCA_MB_06);
                ISR(Can_IsrFCA_MB_07);
            #endif /* (CAN_A_FIFO_EN == STD_OFF) */

            ISR(Can_IsrFCA_MB_08);
            ISR(Can_IsrFCA_MB_09);
            ISR(Can_IsrFCA_MB_10);
            ISR(Can_IsrFCA_MB_11);
            ISR(Can_IsrFCA_MB_12);
            ISR(Can_IsrFCA_MB_13);
            ISR(Can_IsrFCA_MB_14);
            ISR(Can_IsrFCA_MB_15);
            ISR(Can_IsrFCA_MB_16_31);
            ISR(Can_IsrFCA_MB_32_63);
        #endif /* (CAN_ISROPTCODESIZE == STD_OFF) */

    #elif ((CAN_A_TXINT_SUPPORTED == STD_ON) && (CAN_A_RXINT_SUPPORTED == STD_OFF))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            ISR(Can_IsrFCA_UNI);
        #else /* (CAN_ISROPTCODESIZE == STD_ON) */
            #if (CAN_A_FIFO_EN == STD_OFF)
                ISR(Can_IsrFCA_MB_00);
                ISR(Can_IsrFCA_MB_01);
                ISR(Can_IsrFCA_MB_02);
                ISR(Can_IsrFCA_MB_03);
                ISR(Can_IsrFCA_MB_04);
                ISR(Can_IsrFCA_MB_05);
                ISR(Can_IsrFCA_MB_06);
                ISR(Can_IsrFCA_MB_07);
            #endif /* (CAN_A_FIFO_EN == STD_OFF) */

            ISR(Can_IsrFCA_MB_08);
            ISR(Can_IsrFCA_MB_09);
            ISR(Can_IsrFCA_MB_10);
            ISR(Can_IsrFCA_MB_11);
            ISR(Can_IsrFCA_MB_12);
            ISR(Can_IsrFCA_MB_13);
            ISR(Can_IsrFCA_MB_14);
            ISR(Can_IsrFCA_MB_15);
            ISR(Can_IsrFCA_MB_16_31);
            ISR(Can_IsrFCA_MB_32_63);
        #endif /* (CAN_ISROPTCODESIZE == STD_ON) */
    #endif /* ((CAN_A_TXINT_SUPPORTED == STD_ON) && (CAN_A_RXINT_SUPPORTED == STD_OFF)) */
#endif /* CAN_FCA_INDEX */


/* CAN controller C interrupts */
#ifdef CAN_FCC_INDEX
    ISR(Can_IsrFCC_ERR);
    #if (CAN_C_BUSOFFINT_SUPPORTED == STD_ON)
        ISR(Can_IsrFCC_BO);
    #endif /* (CAN_C_BUSOFFINT_SUPPORTED == STD_ON) */

    #if (CAN_WAKEUP_SUPPORT == STD_ON)
        #if (CAN_C_WAKEUPINT_SUPPORTED == STD_ON)
            #if (CAN_WKP_INT_SUPPORT == STD_ON)
                ISR(Can_IsrFCC_WKP);
            #endif /* (CAN_WKP_INT_SUPPORT == STD_ON) */
        #endif /* (CAN_C_WAKEUPINT_SUPPORTED == STD_ON) */
    #endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */

    #if ((CAN_C_TXINT_SUPPORTED == STD_ON) && (CAN_C_RXINT_SUPPORTED == STD_ON))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            ISR(Can_IsrFCC_UNI);
        #else /* (CAN_ISROPTCODESIZE == STD_OFF) */
            #if (CAN_C_FIFO_EN == STD_ON)
                #if (CAN_RXFIFO_EVENT_UNIFIED == STD_ON)
                    ISR(Can_IsrFCC_RxFifoEvents);
                #else /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
                    ISR(Can_IsrFCC_FrameAv);
                    ISR(Can_IsrFCC_Overf);
                    ISR(Can_IsrFCC_Warn);
                #endif /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
            #else /* (CAN_C_FIFO_EN == STD_OFF) */
                ISR(Can_IsrFCC_MB_00);
                ISR(Can_IsrFCC_MB_01);
                ISR(Can_IsrFCC_MB_02);
                ISR(Can_IsrFCC_MB_03);
                ISR(Can_IsrFCC_MB_04);
                ISR(Can_IsrFCC_MB_05);
                ISR(Can_IsrFCC_MB_06);
                ISR(Can_IsrFCC_MB_07);
            #endif /* (CAN_C_FIFO_EN == STD_OFF) */

            ISR(Can_IsrFCC_MB_08);
            ISR(Can_IsrFCC_MB_09);
            ISR(Can_IsrFCC_MB_10);
            ISR(Can_IsrFCC_MB_11);
            ISR(Can_IsrFCC_MB_12);
            ISR(Can_IsrFCC_MB_13);
            ISR(Can_IsrFCC_MB_14);
            ISR(Can_IsrFCC_MB_15);
            ISR(Can_IsrFCC_MB_16_31);
        #endif /* (CAN_ISROPTCODESIZE == STD_OFF) */
    #elif ((CAN_C_TXINT_SUPPORTED == STD_OFF) && (CAN_C_RXINT_SUPPORTED == STD_ON))
        #if (CAN_ISROPTCODESIZE == STD_ON)
           ISR(Can_IsrFCC_UNI);
        #else /* (CAN_ISROPTCODESIZE == STD_OFF) */
            #if (CAN_C_FIFO_EN == STD_ON)
                #if (CAN_RXFIFO_EVENT_UNIFIED == STD_ON)
                    ISR(Can_IsrFCC_RxFifoEvents);
                #else /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
                    ISR(Can_IsrFCC_FrameAv);
                    ISR(Can_IsrFCC_Overf);
                    ISR(Can_IsrFCC_Warn);
                #endif /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
            #else /* (CAN_C_FIFO_EN == STD_OFF) */
                ISR(Can_IsrFCC_MB_00);
                ISR(Can_IsrFCC_MB_01);
                ISR(Can_IsrFCC_MB_02);
                ISR(Can_IsrFCC_MB_03);
                ISR(Can_IsrFCC_MB_04);
                ISR(Can_IsrFCC_MB_05);
                ISR(Can_IsrFCC_MB_06);
                ISR(Can_IsrFCC_MB_07);
            #endif /* (CAN_C_FIFO_EN == STD_OFF) */

            ISR(Can_IsrFCC_MB_08);
            ISR(Can_IsrFCC_MB_09);
            ISR(Can_IsrFCC_MB_10);
            ISR(Can_IsrFCC_MB_11);
            ISR(Can_IsrFCC_MB_12);
            ISR(Can_IsrFCC_MB_13);
            ISR(Can_IsrFCC_MB_14);
            ISR(Can_IsrFCC_MB_15);
            ISR(Can_IsrFCC_MB_16_31);
        #endif /* (CAN_ISROPTCODESIZE == STD_OFF) */

    #elif ((CAN_C_TXINT_SUPPORTED == STD_ON) && (CAN_C_RXINT_SUPPORTED == STD_OFF))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            ISR(Can_IsrFCC_UNI);
        #else /* (CAN_ISROPTCODESIZE == STD_OFF) */
            #if (CAN_C_FIFO_EN == STD_OFF)
                ISR(Can_IsrFCC_MB_00);
                ISR(Can_IsrFCC_MB_01);
                ISR(Can_IsrFCC_MB_02);
                ISR(Can_IsrFCC_MB_03);
                ISR(Can_IsrFCC_MB_04);
                ISR(Can_IsrFCC_MB_05);
                ISR(Can_IsrFCC_MB_06);
                ISR(Can_IsrFCC_MB_07);
            #endif /* (CAN_C_FIFO_EN == STD_OFF) */

            ISR(Can_IsrFCC_MB_08);
            ISR(Can_IsrFCC_MB_09);
            ISR(Can_IsrFCC_MB_10);
            ISR(Can_IsrFCC_MB_11);
            ISR(Can_IsrFCC_MB_12);
            ISR(Can_IsrFCC_MB_13);
            ISR(Can_IsrFCC_MB_14);
            ISR(Can_IsrFCC_MB_15);
            ISR(Can_IsrFCC_MB_16_31);
        #endif /* (CAN_ISROPTCODESIZE == STD_OFF) */
    #endif /* ((CAN_C_TXINT_SUPPORTED == STD_ON) && (CAN_C_RXINT_SUPPORTED == STD_OFF)) */
#endif /* CAN_FCC_INDEX */


/*==================================================================================================*/
/**
@brief      Interrupt routine for Rx fifo Suppport.
@details    Defined as macro.

@remarks    The controller ID is transmitted with the ## operator for the interrupt handler.
            FC - Can hardware channel: A, C.
*/
/*==================================================================================================*/
/**
@note Violates MISRA 2004 Advisory Rule 19.12, Multiple use of '#/##' operators in macro definition. - See @ref Can_Irq_c_REF_1
@note Violates MISRA 2004 Advisory Rule 19.13, '#/##' operator used. - See @ref Can_Irq_c_REF_2
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined. - See @ref Can_Irq_c_REF_4
*/
/*lint -save -e960 -e961*/
#if (CAN_RXFIFO_ENABLE == STD_ON)
    #if (CAN_RXFIFO_EVENT_UNIFIED == STD_ON)
        #define CAN_RXFIFO_EVENTS(FC) \
            ISR(Can_IsrFC##FC##_RxFifoEvents) { \
                Can_RxFifoFrameAvNotif(CAN_FC##FC##_INDEX); \
                if (NULL_PTR != Can_CurrentConfigPtr->ControlerDescriptors[CAN_FC##FC##_INDEX].Can_RxFifoOverflowNotification) { \
                    Can_CurrentConfigPtr->ControlerDescriptors[CAN_FC##FC##_INDEX].Can_RxFifoOverflowNotification(); \
                } \
                if (NULL_PTR != Can_CurrentConfigPtr->ControlerDescriptors[CAN_FC##FC##_INDEX].Can_RxFifoWarningNotification) { \
                    Can_CurrentConfigPtr->ControlerDescriptors[CAN_FC##FC##_INDEX].Can_RxFifoWarningNotification(); \
                } \
                EXIT_INTERRUPT(); \
            }
    #endif /* (CAN_RXFIFO_EVENT_UNIFIED == STD_ON) */
#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */
/*lint -restore*/


/*==================================================================================================*/
/**
@brief      Interrupt routine for RxFifo suppport.
@details    Defined as macro.

@remarks    The controller ID is transmitted with the ## operator for the interrupt handler.
            FC - Can hardware channel: A, C.
*/
/*==================================================================================================*/
/**
@note Violates MISRA 2004 Advisory Rule 19.12, Multiple use of '#/##' operators in macro definition. - See @ref Can_Irq_c_REF_1
@note Violates MISRA 2004 Advisory Rule 19.13, '#/##' operator used. - See @ref Can_Irq_c_REF_2
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined. - See @ref Can_Irq_c_REF_4
*/
/*lint -save -e960 -e961*/
#if (CAN_RXFIFO_ENABLE == STD_ON)
    #if (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF)
        #define CAN_MB_RXOVER(FC) \
            ISR(Can_IsrFC##FC##_Overf) { \
                if (NULL_PTR != Can_CurrentConfigPtr->ControlerDescriptors[CAN_FC##FC##_INDEX].Can_RxFifoOverflowNotification) { \
                    Can_CurrentConfigPtr->ControlerDescriptors[CAN_FC##FC##_INDEX].Can_RxFifoOverflowNotification(); \
                } \
                EXIT_INTERRUPT(); \
            }
    #endif /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */
/*lint -restore*/


/*==================================================================================================*/
/**
@brief      Interrupt routine for RxFifo suppport.
@details    Defined as macro.

@remarks    The controller ID is transmitted with the ## operator for the interrupt handler.
            FC - Can hardware channel: A, C.
*/
/*==================================================================================================*/
/**
@note Violates MISRA 2004 Advisory Rule 19.12, Multiple use of '#/##' operators in macro definition. - See @ref Can_Irq_c_REF_1
@note Violates MISRA 2004 Advisory Rule 19.13, '#/##' operator used. - See @ref Can_Irq_c_REF_2
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined. - See @ref Can_Irq_c_REF_4
*/
/*lint -save -e960 -e961*/
#if (CAN_RXFIFO_ENABLE == STD_ON)
    #if (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF)
        #define CAN_MB_RXWARN(FC) \
            ISR(Can_IsrFC##FC##_Warn) { \
                if (NULL_PTR != Can_CurrentConfigPtr->ControlerDescriptors[CAN_FC##FC##_INDEX].Can_RxFifoWarningNotification) { \
                    Can_CurrentConfigPtr->ControlerDescriptors[CAN_FC##FC##_INDEX].Can_RxFifoWarningNotification(); \
                } \
                EXIT_INTERRUPT(); \
            }
    #endif /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */
/*lint -restore*/


/*==================================================================================================*/
/**
@brief      Interrupt routine for Rx fifo Suppport.
@details    Defined as macro.

@remarks    The controller ID is transmitted with the ## operator for the interrupt handler.
            FC - Can hardware channel: A, C.
*/
/*==================================================================================================*/
/**
@note Violates MISRA 2004 Advisory Rule 19.12, Multiple use of '#/##' operators in macro definition. - See @ref Can_Irq_c_REF_1
@note Violates MISRA 2004 Advisory Rule 19.13, '#/##' operator used. - See @ref Can_Irq_c_REF_2
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined. - See @ref Can_Irq_c_REF_4
*/
/*lint -save -e960 -e961*/
#if (CAN_RXFIFO_ENABLE == STD_ON)
    #if (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF)
        #define CAN_MB_FRAV(FC) \
            ISR(Can_IsrFC##FC##_FrameAv) { \
                Can_RxFifoFrameAvNotif( CAN_FC##FC##_INDEX); \
                EXIT_INTERRUPT(); \
            }
    #endif /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */
/*lint -restore*/


/*==================================================================================================*/
/**
@brief      Interrupt routine for all MBs - optimization code size.
@details    Process all MBs defined for current controller. MBs are grouped: HRHs first, the HTHs.

@remarks    The controller ID is transmitted with the ## operator for the interrupt handler.
            FC - Can hardware channel: A, C.
*/
/*==================================================================================================*/
/**
@note Violates MISRA 2004 Advisory Rule 19.12, Multiple use of '#/##' operators in macro definition. - See @ref Can_Irq_c_REF_1
@note Violates MISRA 2004 Advisory Rule 19.13, '#/##' operator used. - See @ref Can_Irq_c_REF_2
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined. - See @ref Can_Irq_c_REF_4
*/
/*lint -save -e960 -e961*/
#if (CAN_ISROPTCODESIZE == STD_ON)
    #define CAN_MB_UNIISRS(FC) \
        ISR(Can_IsrFC##FC##_UNI) { \
            /* Rx: process from 0 to (FirstTx-1) */ \
            Can_Process_Rx( CAN_FC##FC##_INDEX, \
                            (uint8)0U, \
                            (uint8)(Can_ControllerStatuses[CAN_FC##FC##_INDEX].FirstTxMBIndex - (uint8)1U) ); \
            /* Tx: process from FirstTx to (MaxMB-1) */ \
            Can_Process_Tx( CAN_FC##FC##_INDEX, \
                            (uint8)Can_ControllerStatuses[CAN_FC##FC##_INDEX].FirstTxMBIndex, \
                            (uint8)(Can_CurrentConfigPtr->ControlerDescriptors[CAN_FC##FC##_INDEX].MaxMBCount - (uint8)1U) ); \
            EXIT_INTERRUPT(); \
        }
#endif /* (CAN_ISROPTCODESIZE == STD_ON) */
/*lint -restore*/


/*==================================================================================================*/
/**
@brief      Interrupt routine for all MBs  - optimization code size, TX only.
@details    Process all MBs that are configured for Tx.

@remarks    The controller ID is transmitted with the ## operator for the interrupt handler.
            FC - Can hardware channel: A, C.
*/
/*==================================================================================================*/
/**
@note Violates MISRA 2004 Advisory Rule 19.12, Multiple use of '#/##' operators in macro definition. - See @ref Can_Irq_c_REF_1
@note Violates MISRA 2004 Advisory Rule 19.13, '#/##' operator used. - See @ref Can_Irq_c_REF_2
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined. - See @ref Can_Irq_c_REF_4
*/
/*lint -save -e960 -e961*/
#if (CAN_ISROPTCODESIZE == STD_ON)
    #define CAN_MB_UNITXISRS(FC) \
        ISR(Can_IsrFC##FC##_UNI) { \
            /* Tx: process all Tx MBs */ \
            Can_Process_Tx( CAN_FC##FC##_INDEX, \
                            (uint8)Can_ControllerStatuses[CAN_FC##FC##_INDEX].FirstTxMBIndex, \
                            (uint8)(Can_CurrentConfigPtr->ControlerDescriptors[CAN_FC##FC##_INDEX].MaxMBCount - (uint8)1U) ); \
            EXIT_INTERRUPT(); \
        }
#endif /* (CAN_ISROPTCODESIZE == STD_ON) */
/*lint -restore*/


/*==================================================================================================*/
/**
@brief      Interrupt routine for all MBs  - optimization code size, RX only.
@details    Process all MBs that are configured for Rx.

@remarks    The controller ID is transmitted with the ## operator for the interrupt handler.
            FC - Can hardware channel: A, C.
*/
/*==================================================================================================*/
/**
@note Violates MISRA 2004 Advisory Rule 19.12, Multiple use of '#/##' operators in macro definition. - See @ref Can_Irq_c_REF_1
@note Violates MISRA 2004 Advisory Rule 19.13, '#/##' operator used. - See @ref Can_Irq_c_REF_2
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined. - See @ref Can_Irq_c_REF_4
*/
/*lint -save -e960 -e961*/
#if (CAN_ISROPTCODESIZE == STD_ON)
    #define CAN_MB_UNIRXISRS(FC) \
        ISR(Can_IsrFC##FC##_UNI) { \
            /* Rx: process from 0 to (FirstTx-1) */ \
            Can_Process_Rx( CAN_FC##FC##_INDEX, \
                            (uint8)0U, \
                            (uint8)(Can_ControllerStatuses[CAN_FC##FC##_INDEX].FirstTxMBIndex - (uint8)1U) ); \
            EXIT_INTERRUPT(); \
        }
#endif /* (CAN_ISROPTCODESIZE == STD_ON) */
/*lint -restore*/


/*==================================================================================================*/
/**
@brief      Interrupt routine for a range of MBs. ( for MBs from 16 to 63)
@details    Process all MBs defined for current controller, but between a definite range.
            MBs are grouped: HRHs first, the HTHs.

@remarks    FC - Can hardware channel: A, C.
            Name - Suggestive name for the Int purpose
            IdMin, IdMax - minimum/maximum MB id that interrupt is related for.
*/
/*==================================================================================================*/
/**
@note Violates MISRA 2004 Advisory Rule 19.12, Multiple use of '#/##' operators in macro definition. - See @ref Can_Irq_c_REF_1
@note Violates MISRA 2004 Advisory Rule 19.13, '#/##' operator used. - See @ref Can_Irq_c_REF_2
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined. - See @ref Can_Irq_c_REF_4
*/
/*lint -save -e960 -e961*/
#if (CAN_ISROPTCODESIZE == STD_OFF)
    #define CAN_MB_ISRS(FC, Name, IdMin, IdMax) \
        ISR(Can_IsrFC##FC##_##Name) { \
            if ( (Can_ControllerStatuses[CAN_FC##FC##_INDEX].FirstTxMBIndex) <= ( (((Can_CurrentConfigPtr->ControlerDescriptors[CAN_FC##FC##_INDEX].MaxMBCount - (uint8)1U)) < (IdMax)) ? ((Can_CurrentConfigPtr->ControlerDescriptors[CAN_FC##FC##_INDEX].MaxMBCount - (uint8)1U)) : (IdMax)) ) { \
                Can_Process_Tx( CAN_FC##FC##_INDEX, \
                                ( (Can_ControllerStatuses[CAN_FC##FC##_INDEX].FirstTxMBIndex) > (IdMin)) ? (Can_ControllerStatuses[CAN_FC##FC##_INDEX].FirstTxMBIndex) : (IdMin), \
                                ( ((Can_CurrentConfigPtr->ControlerDescriptors[CAN_FC##FC##_INDEX].MaxMBCount - (uint8)1U)) < (IdMax)) ? ((Can_CurrentConfigPtr->ControlerDescriptors[CAN_FC##FC##_INDEX].MaxMBCount - (uint8)1U)) : (IdMax)); \
            } \
            if ( (Can_ControllerStatuses[CAN_FC##FC##_INDEX].FirstTxMBIndex) > (IdMin) ) { \
                Can_Process_Rx( CAN_FC##FC##_INDEX, \
                                IdMin, \
                                ((Can_ControllerStatuses[CAN_FC##FC##_INDEX].FirstTxMBIndex) > ( ( ((Can_CurrentConfigPtr->ControlerDescriptors[CAN_FC##FC##_INDEX].MaxMBCount - (uint8)1U)) < (IdMax) ) ? ((Can_CurrentConfigPtr->ControlerDescriptors[CAN_FC##FC##_INDEX].MaxMBCount - (uint8)1U)) : (IdMax)) ) ? /* condition */ \
                                    ( ((Can_CurrentConfigPtr->ControlerDescriptors[CAN_FC##FC##_INDEX].MaxMBCount - (uint8)1U) < IdMax) ? ((Can_CurrentConfigPtr->ControlerDescriptors[CAN_FC##FC##_INDEX].MaxMBCount - (uint8)1U)) : (IdMax)) : /* value if condition is true */ \
                                    (Can_ControllerStatuses[CAN_FC##FC##_INDEX].FirstTxMBIndex - (uint8)1U) ); /* value if condition is false */ \
            } \
            EXIT_INTERRUPT(); \
        }
#endif /* (CAN_ISROPTCODESIZE == STD_OFF) */
/*lint -restore*/


/*==================================================================================================*/
/**
@brief      Interrupt routine for a range of MBs - TX only ( for MBs from 16 to 63).
@details    Process all MBs that are configured for Tx, but between a definite range.

@remarks    FC - Can hardware channel: A, C.
@remarks    Name - Suggestive name for the Int purpose.
@remarks    IdMin, IdMax - minimum/maximum MB id that interrupt is related for.
*/
/*==================================================================================================*/
/**
@note Violates MISRA 2004 Advisory Rule 19.12, Multiple use of '#/##' operators in macro definition. - See @ref Can_Irq_c_REF_1
@note Violates MISRA 2004 Advisory Rule 19.13, '#/##' operator used. - See @ref Can_Irq_c_REF_2
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined. - See @ref Can_Irq_c_REF_4
*/
/*lint -save -e960 -e961*/
#if (CAN_ISROPTCODESIZE == STD_OFF)
    #define CAN_MB_TXISRS(FC, Name, IdMin, IdMax) \
        ISR(Can_IsrFC##FC##_##Name) { \
            Can_Process_Tx( CAN_FC##FC##_INDEX, \
                            ( (Can_ControllerStatuses[CAN_FC##FC##_INDEX].FirstTxMBIndex) > (IdMin)) ? (Can_ControllerStatuses[CAN_FC##FC##_INDEX].FirstTxMBIndex) : (IdMin), \
                            ( ((Can_CurrentConfigPtr->ControlerDescriptors[CAN_FC##FC##_INDEX].MaxMBCount - (uint8)1U)) < (IdMax) ) ? ((Can_CurrentConfigPtr->ControlerDescriptors[CAN_FC##FC##_INDEX].MaxMBCount - (uint8)1U)) : (IdMax)); \
            EXIT_INTERRUPT(); \
        }
#endif /* (CAN_ISROPTCODESIZE == STD_OFF) */
/*lint -restore*/


/*==================================================================================================*/
/**
@brief      Interrupt routine for a range of MBs - RX only ( for MBs from 16 to 63).
@details    Process all MBs that are configured for Tx, but between a definite range.

@remarks    FC - Can hardware channel: A, C.
@remarks    Name - Suggestive name for the Int purpose
@remarks    IdMin, IdMax - minimum/maximum MB id that interrupt is related for.
*/
/*==================================================================================================*/
/**
@note Violates MISRA 2004 Advisory Rule 19.12, Multiple use of '#/##' operators in macro definition. - See @ref Can_Irq_c_REF_1
@note Violates MISRA 2004 Advisory Rule 19.13, '#/##' operator used. - See @ref Can_Irq_c_REF_2
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined. - See @ref Can_Irq_c_REF_4
*/
/*lint -save -e960 -e961*/
#if (CAN_ISROPTCODESIZE == STD_OFF)
    #define CAN_MB_RXISRS(FC, Name, IdMin, IdMax) \
        ISR(Can_IsrFC##FC##_##Name) { \
            Can_Process_Rx( CAN_FC##FC##_INDEX, \
                            IdMin, \
                            (Can_ControllerStatuses[CAN_FC##FC##_INDEX].FirstTxMBIndex) > ( (((Can_CurrentConfigPtr->ControlerDescriptors[CAN_FC##FC##_INDEX].MaxMBCount - (uint8)1U)) < (IdMax)) ? ((Can_CurrentConfigPtr->ControlerDescriptors[CAN_FC##FC##_INDEX].MaxMBCount - (uint8)1U)) : (IdMax)) ? /* condition */ \
                                ( (((Can_CurrentConfigPtr->ControlerDescriptors[CAN_FC##FC##_INDEX].MaxMBCount - (uint8)1U)) < (IdMax)) ? ((Can_CurrentConfigPtr->ControlerDescriptors[CAN_FC##FC##_INDEX].MaxMBCount - (uint8)1U)) : (IdMax)) : /* result if condition is true */ \
                                (Can_ControllerStatuses[CAN_FC##FC##_INDEX].FirstTxMBIndex - (uint8)1U) ); /* result if condition is false */ \
            EXIT_INTERRUPT(); \
        }
#endif /* (CAN_ISROPTCODESIZE == STD_OFF) */
/*lint -restore*/


/*==================================================================================================*/
/**
@brief      Interrupt routine for BusOff.
@details    Defined as macro.

@remarks    FC - Can hardware channel: A, C.
*/
/*==================================================================================================*/
/**
@note Violates MISRA 2004 Advisory Rule 19.12, Multiple use of '#/##' operators in macro definition. - See @ref Can_Irq_c_REF_1
@note Violates MISRA 2004 Advisory Rule 19.13, '#/##' operator used. - See @ref Can_Irq_c_REF_2
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined. - See @ref Can_Irq_c_REF_4
*/
/*lint -save -e960 -e961*/
#define CAN_BOISR(FC) \
    ISR(Can_IsrFC##FC##_BO) { \
        /* Process BusOff condition for controller ID of FlexCAN FC */ \
        Can_Process_BusOff( CAN_FC##FC##_INDEX); \
        EXIT_INTERRUPT(); \
    }
/*lint -restore*/


/*==================================================================================================*/
/**
@brief      Interrupt routine for WakeUp.
@details    Defined as macro.
@remarks   Covers CAN364
@remarks   Implements DCAN00364

@remarks    FC - Can hardware channel: A, C.
*/
/*==================================================================================================*/
/**
@note Violates MISRA 2004 Advisory Rule 19.12, Multiple use of '#/##' operators in macro definition. - See @ref Can_Irq_c_REF_1
@note Violates MISRA 2004 Advisory Rule 19.13, '#/##' operator used. - See @ref Can_Irq_c_REF_2
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined. - See @ref Can_Irq_c_REF_4
*/
/*lint -save -e960 -e961*/
#if ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WKP_INT_SUPPORT == STD_ON))
    #define CAN_WKPISR(FC) \
        ISR(Can_IsrFC##FC##_WKP) { \
            /* EcuM_CheckWakeup must be called by the ISR of a wakeup source to set up the PLL */ \
            /** \
            @brief   (CAN364) If the ISR for wakeup events is called, it shall call EcuM_CheckWakeup in turn. \
            */ \
            EcuM_CheckWakeup( Can_CurrentConfigPtr->ControlerDescriptors[CAN_FC##FC##_INDEX].CanWakeupSourceID ); \
            /* Process Bus off condition for controller ID of FlexCAN */ \
            Can_Process_Wakeup( CAN_FC##FC##_INDEX ); \
            EXIT_INTERRUPT(); \
        }
#endif /* ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WKP_INT_SUPPORT == STD_ON)) */
/*lint -restore*/


/*==================================================================================================*/
/**
@brief      Interrupt routine for Error.
@details    Defined as macro.

@remarks    FC - Can hardware channel: A, C.
*/
/*==================================================================================================*/
/**
@note Violates MISRA 2004 Advisory Rule 19.12, Multiple use of '#/##' operators in macro definition. - See @ref Can_Irq_c_REF_1
@note Violates MISRA 2004 Advisory Rule 19.13, '#/##' operator used. - See @ref Can_Irq_c_REF_2
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined. - See @ref Can_Irq_c_REF_4
*/
/*lint -save -e960 -e961*/
#define CAN_ERRISR(FC) \
    ISR(Can_IsrFC##FC##_ERR) { /* Error Isr */ \
        FLEXCAN_SET_ESR_ERRINT(CAN_FC##FC##_INDEX); \
        if ( NULL_PTR != Can_CurrentConfigPtr->ControlerDescriptors[CAN_FC##FC##_INDEX].Can_ErrorNotification) { \
            Can_CurrentConfigPtr->ControlerDescriptors[CAN_FC##FC##_INDEX].Can_ErrorNotification(); \
        } \
        EXIT_INTERRUPT(); \
    }
/*lint -restore*/




/*==================================================================================================
    INTERRUPT SERVICE ROUTINES FOR FLEXCAN A
==================================================================================================*/
#ifdef CAN_FCA_INDEX

    /* Error */
    /**
    @note Violates MISRA 2004 Advisory Rule 17.4, cast from unsigned long to pointer. - See @ref Can_Irq_c_REF_6
    @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref Can_Irq_c_REF_7
    */
    CAN_ERRISR(A)

    #if (CAN_A_BUSOFFINT_SUPPORTED == STD_ON)
        /* Bus Off */
        /**
        @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref Can_Irq_c_REF_7
        */
        CAN_BOISR(A)
    #endif /* (CAN_A_BUSOFFINT_SUPPORTED == STD_ON) */

    #if (CAN_WAKEUP_SUPPORT == STD_ON)
        #if (CAN_A_WAKEUPINT_SUPPORTED == STD_ON)
            #if (CAN_WKP_INT_SUPPORT == STD_ON)
                /* Internal Wake-Up */
                /**
                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref Can_Irq_c_REF_7
                */
            CAN_WKPISR(A)
            #endif /* (CAN_WKP_INT_SUPPORT == STD_ON) */
        #endif /* (CAN_A_WAKEUPINT_SUPPORTED == STD_ON) */
    #endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */

    #if ((CAN_A_TXINT_SUPPORTED == STD_ON) && (CAN_A_RXINT_SUPPORTED == STD_ON))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            /* All MBs */
            /**
            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref Can_Irq_c_REF_7
            */
            CAN_MB_UNIISRS(A)
        #else /* (CAN_ISROPTCODESIZE == STD_ON) */
            #if (CAN_A_FIFO_EN == STD_ON)
                #if (CAN_RXFIFO_EVENT_UNIFIED == STD_ON)
                    /* All events of Rx fifo */
                    CAN_RXFIFO_EVENTS(A)
                #else /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
                    /* Rx Fifo Frame Available Interrupt */
                    CAN_MB_FRAV(A)
                    /* RX Fifo Overflow Interrupt*/
                    CAN_MB_RXOVER(A)
                    /* Rx Fifo Warning Interrupt */
                    CAN_MB_RXWARN(A)
                #endif /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
            #else /* (CAN_A_FIFO_EN == STD_OFF) */
                /* Message Buffer 00 */
                CAN_MB_ISRS(A, MB_00, 0U, 0U)
                /* Message Buffer 01 */
                CAN_MB_ISRS(A, MB_01, 1U, 1U)
                /* Message Buffer 02 */
                CAN_MB_ISRS(A, MB_02, 2U, 2U)
                /* Message Buffer 03 */
                CAN_MB_ISRS(A, MB_03, 3U, 3U)
                /* Message Buffer 04 */
                CAN_MB_ISRS(A, MB_04, 4U, 4U)
                /* Message Buffer 05 */
                CAN_MB_ISRS(A, MB_05, 5U, 5U)
                /* Message Buffer 06 */
                CAN_MB_ISRS(A, MB_06, 6U, 6U)
                /* Message Buffer 07 */
                CAN_MB_ISRS(A, MB_07, 7U, 7U)
            #endif /* (CAN_A_FIFO_EN == STD_OFF) */

            /* Message Buffer 08 */
            CAN_MB_ISRS(A, MB_08, 8U, 8U)
            /* Message Buffer 09 */
            CAN_MB_ISRS(A, MB_09, 9U, 9U)
            /* Message Buffer 10 */
            CAN_MB_ISRS(A, MB_10, 10U, 10U)
            /* Message Buffer 11 */
            CAN_MB_ISRS(A, MB_11, 11U, 11U)
            /* Message Buffer 12 */
            CAN_MB_ISRS(A, MB_12, 12U, 12U)
            /* Message Buffer 13 */
            CAN_MB_ISRS(A, MB_13, 13U, 13U)
            /* Message Buffer 14 */
            CAN_MB_ISRS(A, MB_14, 14U, 14U)
            /* Message Buffer 15 */
            CAN_MB_ISRS(A, MB_15, 15U, 15U)
            /* Message Buffer 16_31 */
            CAN_MB_ISRS(A, MB_16_31, 16U, 31U)
            /* Message Buffer 32_63 */
            CAN_MB_ISRS(A, MB_32_63, 32U, 63U)
        #endif /* (CAN_ISROPTCODESIZE == STD_ON) */

    #elif ((CAN_A_TXINT_SUPPORTED == STD_OFF) && (CAN_A_RXINT_SUPPORTED == STD_ON))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            /* All MBs */
            CAN_MB_UNIRXISRS(A)
        #else /* (CAN_ISROPTCODESIZE == STD_ON) */
            #if (CAN_A_FIFO_EN == STD_ON)
                #if (CAN_RXFIFO_EVENT_UNIFIED == STD_ON)
                    /* All events of Rx fifo */
                    CAN_RXFIFO_EVENTS(A)
                #else /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
                    /* Rx Fifo Frame Available Interrupt */
                    CAN_MB_FRAV(A)
                    /* RX Fifo Overflow Interrupt*/
                    CAN_MB_RXOVER(A)
                    /* Rx Fifo Warning Interrupt */
                    CAN_MB_RXWARN(A)
                #endif /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
            #else /* (CAN_A_FIFO_EN == STD_OFF) */
                /* Message Buffer 00 */
                CAN_MB_RXISRS(A, MB_00, 0U, 0U)
                /* Message Buffer 01 */
                CAN_MB_RXISRS(A, MB_01, 1U, 1U)
                /* Message Buffer 02 */
                CAN_MB_RXISRS(A, MB_02, 2U, 2U)
                /* Message Buffer 03 */
                CAN_MB_RXISRS(A, MB_03, 3U, 3U)
                /* Message Buffer 04 */
                CAN_MB_RXISRS(A, MB_04, 4U, 4U)
                /* Message Buffer 05 */
                CAN_MB_RXISRS(A, MB_05, 5U, 5U)
                /* Message Buffer 06 */
                CAN_MB_RXISRS(A, MB_06, 6U, 6U)
                /* Message Buffer 07 */
                CAN_MB_RXISRS(A, MB_07, 7U, 7U)
            #endif /* (CAN_A_FIFO_EN == STD_OFF) */

            /* Message Buffer 08 */
            CAN_MB_RXISRS(A, MB_08, 8U, 8U)
            /* Message Buffer 09 */
            CAN_MB_RXISRS(A, MB_09, 9U, 9U)
            /* Message Buffer 10 */
            CAN_MB_RXISRS(A, MB_10, 10U, 10U)
            /* Message Buffer 11 */
            CAN_MB_RXISRS(A, MB_11, 11U, 11U)
            /* Message Buffer 12 */
            CAN_MB_RXISRS(A, MB_12, 12U, 12U)
            /* Message Buffer 13 */
            CAN_MB_RXISRS(A, MB_13, 13U, 13U)
            /* Message Buffer 14 */
            CAN_MB_RXISRS(A, MB_14, 14U, 14U)
            /* Message Buffer 15 */
            CAN_MB_RXISRS(A, MB_15, 15U, 15U)
            /* Message Buffer 16_31 */
            CAN_MB_RXISRS(A, MB_16_31, 16U, 31U)
            /* Message Buffer 32_63 */
            CAN_MB_RXISRS(A, MB_32_63, 32U, 63U)
        #endif /* (CAN_ISROPTCODESIZE == STD_ON) */

    #elif ((CAN_A_TXINT_SUPPORTED == STD_ON) && (CAN_A_RXINT_SUPPORTED == STD_OFF))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            /* All MBs */
            CAN_MB_UNITXISRS(A)
        #else /* (CAN_ISROPTCODESIZE == STD_OFF) */
            #if (CAN_A_FIFO_EN == STD_OFF)
                /* Message Buffer 00 */
                CAN_MB_TXISRS(A, MB_00, 0U, 0U)
                /* Message Buffer 01 */
                CAN_MB_TXISRS(A, MB_01, 1U, 1U)
                /* Message Buffer 02 */
                CAN_MB_TXISRS(A, MB_02, 2U, 2U)
                /* Message Buffer 03 */
                CAN_MB_TXISRS(A, MB_03, 3U, 3U)
                /* Message Buffer 04 */
                CAN_MB_TXISRS(A, MB_04, 4U, 4U)
                /* Message Buffer 05 */
                CAN_MB_TXISRS(A, MB_05, 5U, 5U)
                /* Message Buffer 06 */
                CAN_MB_TXISRS(A, MB_06, 6U, 6U)
                /* Message Buffer 07 */
                CAN_MB_TXISRS(A, MB_07, 7U, 7U)
            #endif /* (CAN_A_FIFO_EN == STD_OFF) */

            /* Message Buffer 08 */
            CAN_MB_TXISRS(A, MB_08, 8U, 8U)
            /* Message Buffer 09 */
            CAN_MB_TXISRS(A, MB_09, 9U, 9U)
            /* Message Buffer 10 */
            CAN_MB_TXISRS(A, MB_10, 10U, 10U)
            /* Message Buffer 11 */
            CAN_MB_TXISRS(A, MB_11, 11U, 11U)
            /* Message Buffer 12 */
            CAN_MB_TXISRS(A, MB_12, 12U, 12U)
            /* Message Buffer 13 */
            CAN_MB_TXISRS(A, MB_13, 13U, 13U)
            /* Message Buffer 14 */
            CAN_MB_TXISRS(A, MB_14, 14U, 14U)
            /* Message Buffer 15 */
            CAN_MB_TXISRS(A, MB_15, 15U, 15U)
            /* Message Buffer 16_31 */
            CAN_MB_TXISRS(A, MB_16_31, 16U, 31U)
            /* Message Buffer 32_63 */
            CAN_MB_TXISRS(A, MB_32_63, 32U, 63U)
        #endif /* (CAN_ISROPTCODESIZE == STD_OFF) */
    #endif /* ((CAN_A_TXINT_SUPPORTED == STD_ON) && (CAN_A_RXINT_SUPPORTED == STD_ON)) */
#endif /* CAN_FCA_INDEX */



/*==================================================================================================
    INTERRUPT SERVICE ROUTINES FOR FLEXCAN C
==================================================================================================*/
#ifdef CAN_FCC_INDEX

    /* Error */
    /**
    @note Violates MISRA 2004 Advisory Rule 17.4, cast from unsigned long to pointer. - See @ref Can_Irq_c_REF_6
    @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref Can_Irq_c_REF_7
    */
    CAN_ERRISR(C)

    #if (CAN_C_BUSOFFINT_SUPPORTED == STD_ON)
        /* Bus Off */
        /**
        @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref Can_Irq_c_REF_7
        */
        CAN_BOISR(C)
    #endif /* (CAN_C_BUSOFFINT_SUPPORTED == STD_ON) */

    #if (CAN_WAKEUP_SUPPORT == STD_ON)
        #if (CAN_C_WAKEUPINT_SUPPORTED == STD_ON)
            #if (CAN_WKP_INT_SUPPORT == STD_ON)
                /* Internal Wake-Up */
                /**
                @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref Can_Irq_c_REF_7
                */
                CAN_WKPISR(C)
            #endif /* (CAN_WKP_INT_SUPPORT == STD_ON) */
        #endif /* (CAN_C_WAKEUPINT_SUPPORTED == STD_ON) */
    #endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */

    #if ((CAN_C_TXINT_SUPPORTED == STD_ON) && (CAN_C_RXINT_SUPPORTED == STD_ON))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            /* All MBs */
            /**
            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref Can_Irq_c_REF_7
            */
            CAN_MB_UNIISRS(C)
        #else /* (CAN_ISROPTCODESIZE == STD_ON) */
            #if (CAN_C_FIFO_EN == STD_ON)
                #if (CAN_RXFIFO_EVENT_UNIFIED == STD_ON)
                    /* All events of Rx fifo */
                    CAN_RXFIFO_EVENTS(C)
                #else /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
                    /* Rx Fifo Frame Available Interrupt */
                    CAN_MB_FRAV(C)
                    /* RX Fifo Overflow Interrupt*/
                    CAN_MB_RXOVER(C)
                    /* Rx Fifo Warning Interrupt */
                    CAN_MB_RXWARN(C)
                #endif /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
            #else /* (CAN_C_FIFO_EN == STD_OFF) */
                /* Message Buffer 00 */
                CAN_MB_ISRS(C, MB_00, 0U, 0U)
                /* Message Buffer 01 */
                CAN_MB_ISRS(C, MB_01, 1U, 1U)
                /* Message Buffer 02 */
                CAN_MB_ISRS(C, MB_02, 2U, 2U)
                /* Message Buffer 03 */
                CAN_MB_ISRS(C, MB_03, 3U, 3U)
                /* Message Buffer 04 */
                CAN_MB_ISRS(C, MB_04, 4U, 4U)
                /* Message Buffer 05 */
                CAN_MB_ISRS(C, MB_05, 5U, 5U)
                /* Message Buffer 06 */
                CAN_MB_ISRS(C, MB_06, 6U, 6U)
                /* Message Buffer 07 */
                CAN_MB_ISRS(C, MB_07, 7U, 7U)
            #endif /* (CAN_C_FIFO_EN == STD_OFF) */

            /* Message Buffer 08 */
            CAN_MB_ISRS(C, MB_08, 8U, 8U)
            /* Message Buffer 09 */
            CAN_MB_ISRS(C, MB_09, 9U, 9U)
            /* Message Buffer 10 */
            CAN_MB_ISRS(C, MB_10, 10U, 10U)
            /* Message Buffer 11 */
            CAN_MB_ISRS(C, MB_11, 11U, 11U)
            /* Message Buffer 12 */
            CAN_MB_ISRS(C, MB_12, 12U, 12U)
            /* Message Buffer 13 */
            CAN_MB_ISRS(C, MB_13, 13U, 13U)
            /* Message Buffer 14 */
            CAN_MB_ISRS(C, MB_14, 14U, 14U)
            /* Message Buffer 15 */
            CAN_MB_ISRS(C, MB_15, 15U, 15U)
            /* Message Buffer 16_31 */
            CAN_MB_ISRS(C, MB_16_31, 16U, 31U)
            /**
            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref Can_Irq_c_REF_7
            */
        #endif /* (CAN_ISROPTCODESIZE == STD_ON) */

    #elif ((CAN_C_TXINT_SUPPORTED == STD_OFF) && (CAN_C_RXINT_SUPPORTED == STD_ON))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            /* All MBs */
            /**
            @note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref Can_Irq_c_REF_7
            */
            CAN_MB_UNIRXISRS(C)
        #else /* (CAN_ISROPTCODESIZE == STD_ON) */
            #if (CAN_C_FIFO_EN == STD_ON)
                #if (CAN_RXFIFO_EVENT_UNIFIED == STD_ON)
                    /* All events of Rx fifo */
                    CAN_RXFIFO_EVENTS(C)
                #else /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
                    /* Rx Fifo Frame Available Interrupt */
                    CAN_MB_FRAV(C)
                    /* RX Fifo Overflow Interrupt*/
                    CAN_MB_RXOVER(C)
                    /* Rx Fifo Warning Interrupt */
                    CAN_MB_RXWARN(C)
                 #endif /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
            #else /* (CAN_C_FIFO_EN == STD_OFF) */
                /* Message Buffer 00 */
                CAN_MB_RXISRS(C, MB_00, 0U, 0U)
                /* Message Buffer 01 */
                CAN_MB_RXISRS(C, MB_01, 1U, 1U)
                /* Message Buffer 02 */
                CAN_MB_RXISRS(C, MB_02, 2U, 2U)
                /* Message Buffer 03 */
                CAN_MB_RXISRS(C, MB_03, 3U, 3U)
                /* Message Buffer 04 */
                CAN_MB_RXISRS(C, MB_04, 4U, 4U)
                /* Message Buffer 05 */
                CAN_MB_RXISRS(C, MB_05, 5U, 5U)
                /* Message Buffer 06 */
                CAN_MB_RXISRS(C, MB_06, 6U, 6U)
                /* Message Buffer 07 */
                CAN_MB_RXISRS(C, MB_07, 7U, 7U)
            #endif /* (CAN_C_FIFO_EN == STD_OFF) */

            /* Message Buffer 08 */
            CAN_MB_RXISRS(C, MB_08, 8U, 8U)
            /* Message Buffer 09 */
            CAN_MB_RXISRS(C, MB_09, 9U, 9U)
            /* Message Buffer 10 */
            CAN_MB_RXISRS(C, MB_10, 10U, 10U)
            /* Message Buffer 11 */
            CAN_MB_RXISRS(C, MB_11, 11U, 11U)
            /* Message Buffer 12 */
            CAN_MB_RXISRS(C, MB_12, 12U, 12U)
            /* Message Buffer 13 */
            CAN_MB_RXISRS(C, MB_13, 13U, 13U)
            /* Message Buffer 14 */
            CAN_MB_RXISRS(C, MB_14, 14U, 14U)
            /* Message Buffer 15 */
            CAN_MB_RXISRS(C, MB_15, 15U, 15U)
            /* Message Buffer 16_31 */
            CAN_MB_RXISRS(C, MB_16_31, 16U, 31U)
        #endif /* (CAN_ISROPTCODESIZE == STD_ON) */

    #elif ((CAN_C_TXINT_SUPPORTED == STD_ON) && (CAN_C_RXINT_SUPPORTED == STD_OFF))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            /* All MBs */
            CAN_MB_UNITXISRS(C)
        #else /* (CAN_ISROPTCODESIZE == STD_OFF) */
            #if (CAN_C_FIFO_EN == STD_OFF)
                /* Message Buffer 00 */
                CAN_MB_TXISRS(C, MB_00, 0U, 0U)
                /* Message Buffer 01 */
                CAN_MB_TXISRS(C, MB_01, 1U, 1U)
                /* Message Buffer 02 */
                CAN_MB_TXISRS(C, MB_02, 2U, 2U)
                /* Message Buffer 03 */
                CAN_MB_TXISRS(C, MB_03, 3U, 3U)
                /* Message Buffer 04 */
                CAN_MB_TXISRS(C, MB_04, 4U, 4U)
                /* Message Buffer 05 */
                CAN_MB_TXISRS(C, MB_05, 5U, 5U)
                /* Message Buffer 06 */
                CAN_MB_TXISRS(C, MB_06, 6U, 6U)
                /* Message Buffer 07 */
                CAN_MB_TXISRS(C, MB_07, 7U, 7U)
            #endif /* (CAN_C_FIFO_EN == STD_OFF) */

            /* Message Buffer 08 */
            CAN_MB_TXISRS(C, MB_08, 8U, 8U)
            /* Message Buffer 09 */
            CAN_MB_TXISRS(C, MB_09, 9U, 9U)
            /* Message Buffer 10 */
            CAN_MB_TXISRS(C, MB_10, 10U, 10U)
            /* Message Buffer 11 */
            CAN_MB_TXISRS(C, MB_11, 11U, 11U)
            /* Message Buffer 12 */
            CAN_MB_TXISRS(C, MB_12, 12U, 12U)
            /* Message Buffer 13 */
            CAN_MB_TXISRS(C, MB_13, 13U, 13U)
            /* Message Buffer 14 */
            CAN_MB_TXISRS(C, MB_14, 14U, 14U)
            /* Message Buffer 15 */
            CAN_MB_TXISRS(C, MB_15, 15U, 15U)
            /* Message Buffer 16_31 */
            CAN_MB_TXISRS(C, MB_16_31, 16U, 31U)
        #endif /* (CAN_ISROPTCODESIZE == STD_OFF) */
    #endif /* ((CAN_C_TXINT_SUPPORTED == STD_ON) && (CAN_C_RXINT_SUPPORTED == STD_ON)) */
#endif /* CAN_FCC_INDEX */


#define CAN_STOP_SEC_CODE
/**
@file  Can_Irq.c
@note  Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives. - See @ref Can_Irq_c_REF_3
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref Can_Irq_c_REF_5
*/
/*lint -save -e537 -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif

