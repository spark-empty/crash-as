/**
    @file    Reg_eSys_STM.h
    @version 2.0.0

    @brief   AUTOSAR Gpt - Brief description.
    @details Detailed description.

    Project AUTOSAR 3.0 MCAL
    Patform PA
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


@section REG_ESYS_STM_H_REF_1
Violates MISRA 2004 Advisory Rule  19.7:Use of fucntion like macro.This vioaltion is due to function like
macro defined for register operations .Function like macro are used to reduce code complexity.


@section REG_ESYS_STM_H_REF_2
Violates MISRA 2004 Advisory Rule 19.1, :  Violates   MISRA  2004  Advisory  Rule   19.1,  only preprocessor
statements and comments before "#include"
This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement
MEMMAP003.

@section REG_ESYS_STM_H_REF_3
Violates MISRA 2004 Advisory Rule 19.15 : Repeated include file
This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement
MEMMAP003.

*/
#ifndef REG_ESYS_STM_H
#define REG_ESYS_STM_H

#ifdef __cplusplus
extern "C"{
#endif
/**
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file See @ref REG_ESYS_STM_H_REF_3
*/
/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Reg_eSys.h"
#include "Reg_Macros.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@brief Parameters that shall be published within the Gpt driver header file and also in the
       module's description file
@remarks Covers BSW00374, BSW00379, BSW00318
@{
*/
#define REG_ESYS_STM_VENDOR_ID            43
#define REG_ESYS_STM_AR_MAJOR_VERSION     3
#define REG_ESYS_STM_AR_MINOR_VERSION     0
#define REG_ESYS_STM_AR_PATCH_VERSION     0
#define REG_ESYS_STM_SW_MAJOR_VERSION     2
#define REG_ESYS_STM_SW_MINOR_VERSION     0
#define REG_ESYS_STM_SW_PATCH_VERSION     0
/**@}*/
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/*
*/
/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/


/**
@{
@brief System Timer Module (STM) Registers address
*/
#define STM_CR                  (STM_BASEADDR + (uint32)0x0UL)
#define STM_CNT                 (STM_BASEADDR + (uint32)0x4UL)

#define STM_CCR0                (STM_BASEADDR + (uint32)0x10UL)
#define STM_CIR0                (STM_BASEADDR + (uint32)0x14UL)
/**

@note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro - See @ref REG_ESYS_STM_H_REF_1
*/
/*lint -save -e961 */
#define STM_CIR(channel)        (STM_BASEADDR + (uint32)0x14UL + ((uint32)0x10UL*(uint32)channel))
/*lint -restore*/
#define STM_CMP0                (STM_BASEADDR + (uint32)0x18UL)

#define STM_CCR1                (STM_BASEADDR + (uint32)0x20UL)
#define STM_CIR1                (STM_BASEADDR + (uint32)0x24UL)
#define STM_CMP1                (STM_BASEADDR + (uint32)0x28UL)

#define STM_CCR2                (STM_BASEADDR + (uint32)0x30UL)
#define STM_CIR2                (STM_BASEADDR + (uint32)0x34UL)
#define STM_CMP2                (STM_BASEADDR + (uint32)0x38UL)

#define STM_CCR3                (STM_BASEADDR + (uint32)0x40UL)
#define STM_CIR3                (STM_BASEADDR + (uint32)0x44UL)
#define STM_CMP3                (STM_BASEADDR + (uint32)0x48UL)
/**@}*/

  /**
  @{
  @brief Mask Enabling and Disabling function
*/
#define STM_TEN_DISABLED (uint32)0x00000000UL
#define STM_TEN_ENABLED  (uint32)0x00000001UL
#define STM_CCR_DISABLE  (uint32)0x00000000UL
#define STM_CCR_ENABLE   (uint32)0x00000001UL
#define STM_CIR_CLEAR    (uint32)0x00000001UL
#define STM_FRZ_ENABLE   (uint32)0x00000002UL

#define STM_OVERFLOW_PAD         ((uint8)1U)
/* Mask for prescaler setting */
#define STM_PRESCALER_MASK (uint32)0x0000FF00UL
/**@}*/

/**
@brief Highest possible value for STM channels
*/
#define STM_CNT_MAX_VALUE                      (uint32)0xFFFFFFFFuL


/**
@brief Macros for System Timer Module (STM) Registers
*/
/**

@note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro - See @ref REG_ESYS_STM_H_REF_1
*/
/* This is applicable for the following lines of code */
/*lint -save -e961 */
#define STM_TIMER_COUNTER_DISABLE()        (REG_BIT_CLEAR32(STM_CR,STM_TEN_ENABLED))  /**< @brief Macro to Disable STM counter */
#define STM_TIMER_COUNTER_ENABLE()         (REG_BIT_SET32(STM_CR,STM_TEN_ENABLED))  /**< @brief Macro to enable STM counter */
#define STM_CH_DISABLE(channel)            (REG_WRITE32((STM_CCR0+((uint32)0x10UL*(uint32)channel)),STM_CCR_DISABLE))  /**< @brief Macro to disable STM channel */
#define STM_CH_ENABLE(channel)             (REG_WRITE32((STM_CCR0+((uint32)0x10UL*(uint32)channel)),STM_CCR_ENABLE))  /**< @brief Macro to enable STM channel */
#define STM_CH_READ_ISR_REQ(channel)       (REG_READ32(STM_CIR0+((uint32)0x10UL*(uint32)channel)))  /**< @brief Macro to read the interrupt status */
#define STM_CH_CLEAR_ISR_REQ(channel)      (REG_WRITE32((STM_CIR0+((uint32)0x10UL*(uint32)channel)),STM_CIR_CLEAR))  /**< @brief Macro to clear the interrupt flag  */
#define STM_GET_COUNTER()                  (REG_READ32(STM_CNT))  /**< @brief Macro to get the counter value */
#define STM_SET_PRESCALER(value)           (REG_RMW32(STM_CR,STM_PRESCALER_MASK,(uint32)((uint32)value<<(uint32)8U)))  /**< @brief Macro to set the prescaler value  */
#define STM_SET_COMPARE(channel,value)     (REG_WRITE32((STM_CMP0+((uint32)0x10UL*(uint32)channel)),(value)))  /**< @brief Macro to set the compare value */
#define STM_GET_COMPARE(channel)           (REG_READ32((STM_CMP0+((uint32)0x10UL*(uint32)channel))))  /**< @brief Macro to get the compare value */

#define STM_SET_FRZ()                      (REG_BIT_SET32(STM_CR,STM_FRZ_ENABLE))  /**< @brief Macro to enable the Freeze */
#define STM_CLR_FRZ()                      (REG_BIT_CLEAR32(STM_CR,STM_FRZ_ENABLE))  /**< @brief Macro to disbale the Freeze */

/* MISRA-C:2004 19.7 VIOLATION: End of code block */
/*lint -restore */

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

#ifndef GPT_PRECOMPILE_SUPPORT
#define GPT_START_CONFIG_DATA_UNSPECIFIED
/**
@file  Reg_eSys_STM.h
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref REG_ESYS_STM_H_REF_2
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref REG_ESYS_STM_H_REF_3
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if header file and MemMap.h file are of the same Autosar version */
    #if ((REG_ESYS_STM_AR_MAJOR_VERSION != MEMMAP_AR_MAJOR_VERSION) || \
         (REG_ESYS_STM_AR_MINOR_VERSION != MEMMAP_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Reg_eSys_STM.h and MemMap.h are different"
    #endif
#endif

#define GPT_STOP_CONFIG_DATA_UNSPECIFIED
/**
@file  Reg_eSys_STM.h
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref REG_ESYS_STM_H_REF_2
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref REG_ESYS_STM_H_REF_3
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/
#endif

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /*REG_ESYS_STM_H*/
