/**
    @file    Stm_Gpt_LLD.h
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


@section STM_GPT_LLD_H_REF_1
Violates MISRA 2004 Advisory Rule  19.7:Use of fucntion like macro.This vioaltion is due to function like
macro defined for register operations .Function like macro are used to reduce code complexity.


@section STM_GPT_LLD_H_REF_2
Violates MISRA 2004 Advisory Rule 19.1, :  Violates   MISRA  2004  Advisory  Rule   19.1,  only preprocessor
statements and comments before "#include"
This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement
MEMMAP003.

@section STM_GPT_LLD_H_REF_3
Violates MISRA 2004 Advisory Rule 19.15 : Repeated include file
This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement
MEMMAP003.

 
*/
#ifndef STM_GPT_LLD_H
#define STM_GPT_LLD_H

#ifdef __cplusplus
extern "C"{
#endif
/**
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file See @ref STM_GPT_LLD_H_REF_3
*/
/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Std_Types.h"

#include "Gpt.h"


/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@brief Parameters that shall be published within the Gpt driver header file and also in the
       module's description file
@remarks Covers BSW00374, BSW00379, BSW00318
@{
*/
#define STM_GPT_LLD_VENDOR_ID            43
#define STM_GPT_LLD_AR_MAJOR_VERSION     3
#define STM_GPT_LLD_AR_MINOR_VERSION     0
#define STM_GPT_LLD_AR_PATCH_VERSION     0
#define STM_GPT_LLD_SW_MAJOR_VERSION     2
#define STM_GPT_LLD_SW_MINOR_VERSION     0
#define STM_GPT_LLD_SW_PATCH_VERSION     0
/**@}*/
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if header file and Std_Types.h file are of the same Autosar version */
    #if ((STM_GPT_LLD_AR_MAJOR_VERSION != STD_TYPES_AR_MAJOR_VERSION) || \
         (STM_GPT_LLD_AR_MINOR_VERSION != STD_TYPES_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Stm_Gpt_LLD.h and Std_Types.h are different"
    #endif
#endif

#if (STM_GPT_LLD_VENDOR_ID != GPT_VENDOR_ID)
#error "Stm_Gpt_LLD.h and Gpt.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if header file and Gpt header file are of the same Autosar version */
    #if ((STM_GPT_LLD_AR_MAJOR_VERSION != GPT_AR_MAJOR_VERSION) || \
         (STM_GPT_LLD_AR_MINOR_VERSION != GPT_AR_MINOR_VERSION) || \
         (STM_GPT_LLD_AR_PATCH_VERSION != GPT_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Stm_Gpt_LLD.h and Gpt.h are different"
    #endif
#endif
/* Check if header file and Gpt header file are of the same software version */
#if ((STM_GPT_LLD_SW_MAJOR_VERSION != GPT_SW_MAJOR_VERSION) || \
     (STM_GPT_LLD_SW_MINOR_VERSION != GPT_SW_MINOR_VERSION) || \
     (STM_GPT_LLD_SW_PATCH_VERSION != GPT_SW_PATCH_VERSION))
#error "Software Version Numbers of Stm_Gpt_LLD.h and Gpt.h are different"
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
#if (GPT_DEV_ERROR_DETECT == STD_ON)
/**

@note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro - See @ref STM_GPT_LLD_H_REF_1
*/
/* This is applicable for the following lines of code */
/*lint -save -e961 */
/**
@brief  STM specific macro for checking the timeout value.
@param[in]       value     Timeout vaule
@return     Boolean
@retval     TRUE - Time out value is valid
@retval     FALSE - Time out value is Invalid
@remarks Implements DGPT08210
*/
#define STM_LLD_INVALID_TIMEOUT_VALUE(value)    (value > STM_CNT_MAX_VALUE)
/* MISRA-C:2004 19.7 VIOLATION: End of code block */
/*lint -restore */
#endif

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
@file  Stm_Gpt_LLD.h
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref STM_GPT_LLD_H_REF_2
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref STM_GPT_LLD_H_REF_3
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if header file and MemMap.h file are of the same Autosar version */
    #if ((STM_GPT_LLD_AR_MAJOR_VERSION != MEMMAP_AR_MAJOR_VERSION) || \
         (STM_GPT_LLD_AR_MINOR_VERSION != MEMMAP_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Stm_Gpt_LLD.h and MemMap.h are different"
    #endif
#endif

#define GPT_STOP_CONFIG_DATA_UNSPECIFIED
/**
@file  Stm_Gpt_LLD.h
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref STM_GPT_LLD_H_REF_2
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref STM_GPT_LLD_H_REF_3
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/
#endif

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#define GPT_START_SEC_CODE
/**
@file  Stm_Gpt_LLD.h
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref STM_GPT_LLD_H_REF_2
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref STM_GPT_LLD_H_REF_3
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

/******************************************************************
| exported function prototypes
|-----------------------------------------------------------------*/
/*************************************************************************************************/
/**
@brief   Gpt driver initialization function for Stm module.
@details This function is called separately for each STM hw channel corresponding to the configured
         timer channels, and:
         - sets the prescaler value
         - configures the freeze mode (enabled/disabled)
         - enables the STM counter
         - disables the STM channel
         - clears the (pending) interrupt flag corresponding to Stm channel
         - clears the compare register correponding to the Stm channel.

@param[in]     freezeEnable     indicates if the Freeze mode is enabled
@param[in]     channelPrescale  prescaler value for the corresponding Stm channel
@param[in]     hwChannel        Stm hw channel ID

@remarks Implements DGPT08205
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Stm_LLD_InitChannel(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel,
                                          VAR(Gpt_PrescaleType, AUTOMATIC) channelPrescale,
                                          VAR(boolean, AUTOMATIC) freezeEnable);
/*************************************************************************************************/
/**
@brief   Gpt driver de-initialization function for Stm module.
@details This function is called separately for each STM hw channel corresponding to the configured
         timer channels, and:
         - disables the STM counter
         - resets the prescaler bits in the control register
         - disables the STM channel
         - clears the (pending) interrupt flag corresponding to Stm channel
         - clears the compare register correponding to the Stm channel.

@param[in]     hwChannel        Stm hw channel ID

@remarks Implements DGPT08200
*/
/*************************************************************************************************/

FUNC (void, GPT_CODE) Stm_LLD_DeInit(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel);
/*************************************************************************************************/
/**
@brief   Gpt driver function for starting the Stm timer channel.
@details This function:
         - reads the current counter register value and sets the compare register to the sum of
           counter register value plus the timeout value
         - enables the STM channel

@param[in]     hwChannel        Stm hw channel ID
@param[in]     value            channel timeout value

@remarks Implements DGPT08208
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Stm_LLD_StartTimer(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel,
                                         VAR(Gpt_ValueType, AUTOMATIC) value);
/*************************************************************************************************/
/**
@brief   Gpt driver function for stopping the Stm timer channel.
@details This function:
         - disables the STM channel
         - clears the (pending) interrupt flag corresponding to Stm channel

@param[in]     hwChannel        Stm hw channel ID

@remarks Implements DGPT08209
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Stm_LLD_StopTimer(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel);
/*************************************************************************************************/
/**
@brief   Gpt driver function for getting the time elapsed for an Stm timer channel.
@details This function:
         - reads the STM channel compare register
         - reads the STM counter register
         - depending on above and on channel timeout value it calculates and returns the elapsed
           time

@param[in]     hwChannel        Stm hw channel ID
@param[in]     timeOutValue     channel timeout value
@param[out]    returnValuePtr   elapsed time value

@remarks Implements DGPT08203
*/
/*************************************************************************************************/

FUNC (void, GPT_CODE) Stm_LLD_GetTimeElapsed(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel,
                                             VAR(Gpt_ValueType, AUTOMATIC) timeOutValue,
                                             P2VAR(Gpt_ValueType, AUTOMATIC, GPT_APPL_DATA) returnValuePtr);
/*************************************************************************************************/
/**
@brief   Gpt driver function for putting the Stm timer channel in SLEEP mode.
@details This function is called separately for each STM hw channel corresponding to the configured
         timer channels, and:
         - clears the (pending) interrupt flag corresponding to Stm channel
         - disable the Stm channel

@param[in]     hwChannel        Stm hw channel ID
@param[in]     wakeUpEnabled    Indicates whether wake up functionality is enabled or not for the
                                corresponding channel.
@param[in]     enableStmCounter  Enable or disable the Stm counter

@remarks Implements DGPT08207
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Stm_LLD_SetSleepMode(VAR(uint8, AUTOMATIC) hwChannel,
                                           VAR(boolean, AUTOMATIC) wakeUpEnabled,
                                           VAR(boolean, AUTOMATIC) enableStmCounter);
/*************************************************************************************************/
/**
@brief   Gpt driver function for putting the Stm timer channel in NORMAL mode.
@details This function enables the Stm counter


@remarks Implements DGPT08206
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Stm_LLD_SetNormalMode(void);
 
#if (GPT_DUAL_CLOCK_MODE == STD_ON)
/*************************************************************************************************/
/**
@brief      The function changes the STM prescaler value.
@details    This function sets the STM prescaler based on the input mode.

@param[in]  chPrescale     prescaler value

@remarks    Covers PR-MCAL-3196
@remarks Implements DGPT11025
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Stm_LLD_SelectPrescaler(VAR(Gpt_PrescaleType, AUTOMATIC) chPrescale);
/* GPT_DUAL_CLOCK_MODE == STD_ON */
#endif 


#define GPT_STOP_SEC_CODE
/**
@file  Stm_Gpt_LLD.h
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref STM_GPT_LLD_H_REF_2
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref STM_GPT_LLD_H_REF_3
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif

#endif /*STM_GPT_LLD_H*/
