/**
    @file    Gpt_Irq.c
    @version 2.0.0

    @brief   AUTOSAR Gpt - GPT driver source file.
    @details GPT driver source file, containing the C implementation of functions prototypes that:
             - are Autosar specific and are not exported by the GPT driver.
             - are not related to the GPT driver related IPs.
    Project AUTOSAR 3.0 MCAL
    Platform PA
    Peripheral eMIOS200_Stm_PitRti
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

@section GPT_IRQ_REF1
MISRA-C:2004   19.1:  Only preprocessor statements and comments before '#include'
This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003

@section GPT_IRQ_REF2
MISRA-C:2004   19.15:  Repeated include file. Precautions shall be taken in order to prevent the
contents of a header file being included twice. This is not a violation since all header files are
protected against multiple inclusions.

@section GPT_IRQ_REF3
 MISRA-C:2004  17.4: pointer arithmetic other than array indexing used
 This violation is due to the use of pointer arithmatic, which is used for the speed optimization,
 the indexing of the pointer is taken care and hence the unintended memory location will not be
 accessed.
 
@section  GPT_IRQ_REF4
Violates MISRA 2004 Advisory Rule 11.1 : cast from unsigned long to pointer.
This violation is due to the Casting pointers to other types used in macros
for Reading or writing data from address location of controller register


*/

#ifdef __cplusplus
extern "C"
{
#endif

/*=================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
=================================================================================================*/
/**
@remarks Implements DGPT11042,DGPT11045,DGPT11047,DGPT11033
*/
#include "Gpt.h"
#include "Gpt_LLD.h"
#include "Reg_eSys_EMIOS.h"
#include "Reg_eSys_STM.h"
#include "Reg_eSys_PITRTI.h"
#include "Mcal.h"

/*=================================================================================================
                                        LOCAL MACROS
=================================================================================================*/
/**
@{
@brief   Source file version information
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define GPT_IRQ_VENDOR_ID                 43
#define GPT_IRQ_AR_MAJOR_VERSION_C        3
#define GPT_IRQ_AR_MINOR_VERSION_C        0
#define GPT_IRQ_AR_PATCH_VERSION_C        0
#define GPT_IRQ_SW_MAJOR_VERSION_C        2
#define GPT_IRQ_SW_MINOR_VERSION_C        0
#define GPT_IRQ_SW_PATCH_VERSION_C        0
/**@}*/

/*=================================================================================================
                                      FILE VERSION CHECKS
=================================================================================================*/
#if (GPT_IRQ_VENDOR_ID != GPT_VENDOR_ID)
    #error "Gpt_Irq.c and Gpt.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((GPT_IRQ_AR_MAJOR_VERSION_C != GPT_AR_MAJOR_VERSION) || \
         (GPT_IRQ_AR_MINOR_VERSION_C != GPT_AR_MINOR_VERSION) || \
         (GPT_IRQ_AR_PATCH_VERSION_C != GPT_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Gpt_Irq.c and Gpt.h are different"
    #endif
#endif
#if ((GPT_IRQ_SW_MAJOR_VERSION_C != GPT_SW_MAJOR_VERSION) || \
     (GPT_IRQ_SW_MINOR_VERSION_C != GPT_SW_MINOR_VERSION) || \
     (GPT_IRQ_SW_PATCH_VERSION_C != GPT_SW_PATCH_VERSION))
#error "Software Version Numbers of Gpt_Irq.c and Gpt.h are different"
#endif

#if (GPT_IRQ_VENDOR_ID != GPT_LLD_VENDOR_ID)
    #error "Gpt_Irq.c and Gpt_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((GPT_IRQ_AR_MAJOR_VERSION_C != GPT_LLD_AR_MAJOR_VERSION) || \
         (GPT_IRQ_AR_MINOR_VERSION_C != GPT_LLD_AR_MINOR_VERSION) || \
         (GPT_IRQ_AR_PATCH_VERSION_C != GPT_LLD_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Gpt_Irq.c and Gpt_LLD.h are different"
    #endif
#endif
#if ((GPT_IRQ_SW_MAJOR_VERSION_C != GPT_LLD_SW_MAJOR_VERSION) || \
     (GPT_IRQ_SW_MINOR_VERSION_C != GPT_LLD_SW_MINOR_VERSION) || \
     (GPT_IRQ_SW_PATCH_VERSION_C != GPT_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of Gpt_Irq.c and Gpt_LLD.h are different"
#endif

#if (GPT_IRQ_VENDOR_ID != REG_ESYS_EMIOS_H_VENDOR_ID)
    #error "Gpt_Irq.c and Reg_eSys_EMIOS.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((GPT_IRQ_AR_MAJOR_VERSION_C != REG_ESYS_EMIOS_H_AR_MAJOR_VERSION) || \
         (GPT_IRQ_AR_MINOR_VERSION_C != REG_ESYS_EMIOS_H_AR_MINOR_VERSION) || \
         (GPT_IRQ_AR_PATCH_VERSION_C != REG_ESYS_EMIOS_H_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Gpt_Irq.c and Reg_eSys_EMIOS.h are different"
    #endif
#endif
#if ((GPT_IRQ_SW_MAJOR_VERSION_C != REG_ESYS_EMIOS_H_SW_MAJOR_VERSION) || \
     (GPT_IRQ_SW_MINOR_VERSION_C != REG_ESYS_EMIOS_H_SW_MINOR_VERSION) || \
     (GPT_IRQ_SW_PATCH_VERSION_C != REG_ESYS_EMIOS_H_SW_PATCH_VERSION))
#error "Software Version Numbers of Gpt_Irq.c and Reg_eSys_EMIOS.h are different"
#endif

#if (GPT_IRQ_VENDOR_ID != REG_ESYS_STM_VENDOR_ID)
    #error "Gpt_Irq.c and Reg_eSys_STM.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((GPT_IRQ_AR_MAJOR_VERSION_C != REG_ESYS_STM_AR_MAJOR_VERSION) || \
         (GPT_IRQ_AR_MINOR_VERSION_C != REG_ESYS_STM_AR_MINOR_VERSION) || \
         (GPT_IRQ_AR_PATCH_VERSION_C != REG_ESYS_STM_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Gpt_Irq.c and Reg_eSys_STM.h are different"
    #endif
#endif
#if ((GPT_IRQ_SW_MAJOR_VERSION_C != REG_ESYS_STM_SW_MAJOR_VERSION) || \
     (GPT_IRQ_SW_MINOR_VERSION_C != REG_ESYS_STM_SW_MINOR_VERSION) || \
     (GPT_IRQ_SW_PATCH_VERSION_C != REG_ESYS_STM_SW_PATCH_VERSION))
#error "Software Version Numbers of Gpt_Irq.c and Reg_eSys_STM.h are different"
#endif

#if (GPT_IRQ_VENDOR_ID != REG_ESYS_PITRTI_VENDOR_ID)
    #error "Gpt_Irq.c and Reg_eSys_PITRTI.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((GPT_IRQ_AR_MAJOR_VERSION_C != REG_ESYS_PITRTI_AR_MAJOR_VERSION) || \
         (GPT_IRQ_AR_MINOR_VERSION_C != REG_ESYS_PITRTI_AR_MINOR_VERSION) || \
         (GPT_IRQ_AR_PATCH_VERSION_C != REG_ESYS_PITRTI_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Gpt_Irq.c and Reg_eSys_PITRTI.h are different"
    #endif
#endif
#if ((GPT_IRQ_SW_MAJOR_VERSION_C != REG_ESYS_PITRTI_SW_MAJOR_VERSION) || \
     (GPT_IRQ_SW_MINOR_VERSION_C != REG_ESYS_PITRTI_SW_MINOR_VERSION) || \
     (GPT_IRQ_SW_PATCH_VERSION_C != REG_ESYS_PITRTI_SW_PATCH_VERSION))
#error "Software Version Numbers of Gpt_Irq.c and Reg_eSys_PITRTI.h are different"
#endif

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
=================================================================================================*/


/*=================================================================================================
                                       LOCAL CONSTANTS
=================================================================================================*/


/*=================================================================================================
                                       LOCAL VARIABLES
=================================================================================================*/


/*=================================================================================================
                                       GLOBAL CONSTANTS
=================================================================================================*/


/*=================================================================================================
                                       GLOBAL VARIABLES
=================================================================================================*/
#define GPT_START_SEC_CODE
/**
@file   Gpt_Irq.c
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref GPT_IRQ_C_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref GPT_IRQ_C_REF_2
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS PROTOTYPES
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

/*************************************************************************************************/
/**
@brief    This function is called from ISR Routine
@details Non-AutoSar support function used by interrupt service routines to call notification
         functions if provided and enabled

@param[in]     hwChannel      hardware channel index

@remarks Covers GPT206, GPT208, GPT233, GPT261, GPT326, GPT327
@remarks Implements DGPT04131
*/
FUNC (void, GPT_CODE) EMIOS_Gpt_LLD_ProcessInterrupt(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel)
{
    P2CONST(Gpt_LLD_ChannelConfigType, AUTOMATIC, GPT_APPL_CONST) tempPtr;
    VAR(uint8, GPT_VAR) LogicChannel;
    VAR(Gpt_ChannelType, AUTOMATIC) mIdx;   /**< @brief assigned eMIOS HW module index */
    VAR(Gpt_ChannelType, AUTOMATIC) chIdx;  /**< @brief assigned eMIOS HW channel index */

    mIdx  = (uint8)((uint8)hwChannel >> (uint8)5U);
    chIdx = (uint8)((uint8)hwChannel &  (uint8)0x1FU);

    LogicChannel = GPT_LLD_EMIOS_HardwareMap[hwChannel];
    if (((uint8)0xffu != LogicChannel) && (NULL_PTR != Gpt_Cfg_Ptr))
    {
        /* Find hardware channel number in global GPT initialization structure */
        /* using Hardware Map Array */
        /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_IRQ_REF3 */
        tempPtr = &Gpt_LLD_ChannelConfigPtr[LogicChannel];
        /* [GPT206]: The ISRs, providing the timeout period events, shall be responsible */
        /* for resetting the interrupt flags (if needed by hardware) and calling the according */
        /* notification function. */
        /* Timer_flag_clear(hwChannel); */
        /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref GPT_IRQ_REF4*/
        REG_WRITE32(EMIOS_CSR(mIdx, chIdx), CSR_FLAG_BIT);

        /* If channel mode is one-shot, stop the channel and disable interrupts */
        if (GPT_MODE_ONESHOT == (tempPtr->Gpt_ChannelMode))
        {
        /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref GPT_IRQ_REF4*/

            /* Putting the channel in GPIO mode stops the channel */
            /* Turn of edge notifications in GPIO Input mode */
            /* Timer_gpio_input_mode(hwChannel); */
            REG_RMW32(EMIOS_CCR(mIdx, chIdx), (CCR_MODE_MASK|CCR_EDSEL_MASK), (CCR_MODE_GPI|CCR_EDSEL_MASK));

            /* Disable Interrupts */
            /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref GPT_IRQ_REF4*/
            REG_BIT_CLEAR32(EMIOS_CCR(mIdx, chIdx), CCR_FEN_MASK);
            Gpt_ChannelStatus[LogicChannel] = GPT_STATUS_EXPIRED;
        }

        /* [GPT208]: If a callback notification is configured as null pointer, no callback shall be executed. */
        /* Check if a notification exists for the channel */
        if ((NULL_PTR != tempPtr->Gpt_Notification) && (GPT_NOTIFICATION_DISABLED != GPT_GET_NOTIFICATION(LogicChannel)))
        {
            /* [GPT207]: The callback notifications shall be configurable as function pointers */
            /* within the initialization data structure (Gpt_ConfigType). */
            /* [GPT233]: The GPT Driver shall provide a notification per channel */
            /* that is called whenever the defined time period is over. */
            tempPtr->Gpt_Notification();
        }

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
        if (GPT_MODE_SLEEP == Gpt_Current_Mode)
        {
            EcuM_CheckWakeup(tempPtr->Gpt_ChannelWakeUpInfo);
        }
#endif
#endif
    }
    else
    {
        Cer_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID, (uint8)GPT_EMIOS_INTERRUPT_ID, (uint8)GPT_CER_UNINIT_INTERRUPT);
    }
}

/*************************************************************************************************/
/**
@brief   PITRTI_Gpt_ProcessInterrupt.
@details Non-AutoSar support function used by interrupt service routines to call notification
         functions if provided and enabled

@param[in]     hwChannel      hardware channel index

@remarks Covers GPT206, GPT208, GPT233, GPT261, GPT326, GPT327
@remarks Implements DGPT04132
*/
FUNC (void, GPT_CODE) PITRTI_Gpt_ProcessInterrupt(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel)
{
    P2CONST(Gpt_LLD_ChannelConfigType, AUTOMATIC, GPT_APPL_CONST) tempPtr;
    VAR(uint8, GPT_VAR) LogicChannel;

    LogicChannel = GPT_LLD_PITRTI_HardwareMap[hwChannel];
    if (((uint8)0xffu != LogicChannel) && (NULL_PTR != Gpt_Cfg_Ptr))
    {
        /* Find hardware channel number in global GPT initialization structure */
        /* using Hardware Map Array */
        /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_IRQ_REF3 */
        tempPtr = &Gpt_LLD_ChannelConfigPtr[LogicChannel];
        /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref GPT_IRQ_REF4*/
        if (PITRTI_RTC_CH_0 == hwChannel)
        {
            PITRTI_RTC_CLEAR_INTERRUPT();
            /* If channel mode is one-shot, stop the channel and disable interrupts */
            if (GPT_MODE_ONESHOT == (tempPtr->Gpt_ChannelMode))
            {
                PITRTI_RTC_COUNTER_DISABLE();
                /* Disable Interrupts */
                PITRTI_RTC_INT_DISABLE();
                Gpt_ChannelStatus[LogicChannel] = GPT_STATUS_EXPIRED;
            }
        }
        else
        {
            PITRTI_CLEAR_INT_FLAG(hwChannel);
            /* If channel mode is one-shot, stop the channel and disable interrupts */
            if (GPT_MODE_ONESHOT == (tempPtr->Gpt_ChannelMode))
            {
         /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref GPT_IRQ_REF4*/
                PITRTI_TIMER_DISABLE(hwChannel);
                /* Disable Interrupts */
             /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref GPT_IRQ_REF4*/
                PITRTI_INTERRUPT_DISABLE(hwChannel);
            Gpt_ChannelStatus[LogicChannel] = GPT_STATUS_EXPIRED;
            }
        }

        /* [GPT208]: If a callback notification is configured as null pointer, no callback shall be executed. */
        /* Check if a notification exists for the channel */
        if ((NULL_PTR != tempPtr->Gpt_Notification) && (GPT_NOTIFICATION_DISABLED != GPT_GET_NOTIFICATION(LogicChannel)))
        {
            /* [GPT207]: The callback notifications shall be configurable as function pointers */
            /* within the initialization data structure (Gpt_ConfigType). */
            /* [GPT233]: The GPT Driver shall provide a notification per channel */
            /* that is called whenever the defined time period is over. */
            tempPtr->Gpt_Notification();
        }

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
        if (GPT_MODE_SLEEP == Gpt_Current_Mode)
        {
            EcuM_CheckWakeup(tempPtr->Gpt_ChannelWakeUpInfo);
        }
#endif
#endif
    }
    else
    {
        Cer_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID, (uint8)GPT_PITRTI_INTERRUPT_ID, (uint8)GPT_CER_UNINIT_INTERRUPT);
    }
}

/*************************************************************************************************/
/**
@brief   STM_Gpt_ProcessInterrupt.
@details Non-AutoSar support function used by interrupt service routines to call notification
         functions if provided and enabled

@param[in]     hwChannel      hardware channel index

@remarks Covers GPT206, GPT208, GPT233, GPT261, GPT326, GPT327
@remarks Implements DGPT04133
*/
FUNC (void, GPT_CODE) STM_Gpt_ProcessInterrupt(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel)
{
    P2CONST(Gpt_LLD_ChannelConfigType, AUTOMATIC, GPT_APPL_CONST) tempPtr;
    VAR(uint8, GPT_VAR) LogicChannel;
    VAR(uint32, AUTOMATIC) tempCompare;

    LogicChannel = GPT_LLD_STM_HardwareMap[hwChannel];
    if (((uint8)0xffu != LogicChannel) && (NULL_PTR != Gpt_Cfg_Ptr))
    {
        /* Find hardware channel number in global GPT initialization structure */
        /* using Hardware Map Array */
        /** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_IRQ_REF3 */
        tempPtr = &Gpt_LLD_ChannelConfigPtr[LogicChannel];
        /* Disable channel before clearing interrupt status flag, errata e500 */
         /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref GPT_IRQ_REF4*/
        STM_CH_DISABLE(hwChannel);

        /* [GPT206]: The ISRs, providing the timeout period events, shall be responsible */
        /* for resetting the interrupt flags (if needed by hardware) and calling the according */
        /* notification function. */
         /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref GPT_IRQ_REF4*/
        STM_CH_CLEAR_ISR_REQ(hwChannel);

        /* If channel mode is one-shot, stop the channel and disable interrupts */
        if (GPT_MODE_ONESHOT == (tempPtr->Gpt_ChannelMode))
        {
            /* Change internal channel status */
            Gpt_ChannelStatus[LogicChannel] = GPT_STATUS_EXPIRED;
        }
        /* CONTINUOUS MODE */
        else
        {
            /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref GPT_IRQ_REF4*/
            tempCompare = STM_GET_COMPARE(hwChannel);
             /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref GPT_IRQ_REF4*/
            STM_SET_COMPARE(hwChannel, tempCompare + Gpt_LLD_ChannelInfo[LogicChannel].Gpt_ReloadValue);
            /* Enable hardware channel */
             /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref GPT_IRQ_REF4*/
            STM_CH_ENABLE(hwChannel);
        }

        /* [GPT208]: If a callback notification is configured as null pointer, no callback shall be executed. */
        /* Check if a notification exists for the channel */
        if ((NULL_PTR != tempPtr->Gpt_Notification) && (GPT_NOTIFICATION_DISABLED != GPT_GET_NOTIFICATION(LogicChannel)))
        {
            /* [GPT207]: The callback notifications shall be configurable as function pointers */
            /* within the initialization data structure (Gpt_ConfigType). */
            /* [GPT233]: The GPT Driver shall provide a notification per channel */
            /* that is called whenever the defined time period is over. */
            tempPtr->Gpt_Notification();
        }
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
        if (GPT_MODE_SLEEP == Gpt_Current_Mode)
        {
            EcuM_CheckWakeup(tempPtr->Gpt_ChannelWakeUpInfo);
        }
#endif
#endif
    }
    else
    {
        Cer_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID, (uint8)GPT_STM_INTERRUPT_ID, (uint8)GPT_CER_UNINIT_INTERRUPT);
   }
}


#define GPT_STOP_SEC_CODE
/**
@file   Gpt_Irq.c
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref GPT_IRQ_C_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref GPT_IRQ_C_REF_2
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/
#ifdef __cplusplus
}
#endif

/* End of file */
