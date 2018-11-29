/**
    @file    PitRti_Gpt_LLD.h
    @version 2.0.0

    @brief   AUTOSAR Gpt - Brief description.
    @details Detailed description.

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

@section PITRTI_Gpt_LLD_H_REF_1
Violates MISRA 2004 Advisory Rule  19.7: Use of fucntion like macro. This vioaltion is due to function like
macro defined for register operations. Function like macro are used to reduce code complexity.

@section PITRTI_Gpt_LLD_H_REF_2
Violates MISRA 2004 Advisory Rule 19.1:  Violates  MISRA 2004  Advisory  Rule  19.1, only preprocessor
statements and comments before "#include"
This violation is not fixed since  the inclusion of MemMap.h  is as  per Autosar requirement
MEMMAP003.

@section PITRTI_Gpt_LLD_H_REF_3
Violates MISRA 2004 Advisory Rule 19.15 : Repeated include file
This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement
MEMMAP003.
*/

#ifndef PITRTI_GPT_LLD_H
#define PITRTI_GPT_LLD_H

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
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file See @ref PITRTI_Gpt_LLD_H_REF_3
*/
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
#define PITRTI_GPT_LLD_VENDOR_ID            43
#define PITRTI_GPT_LLD_MODULE_ID            100
#define PITRTI_GPT_LLD_AR_MAJOR_VERSION     3
#define PITRTI_GPT_LLD_AR_MINOR_VERSION     0
#define PITRTI_GPT_LLD_AR_PATCH_VERSION     0
#define PITRTI_GPT_LLD_SW_MAJOR_VERSION     2
#define PITRTI_GPT_LLD_SW_MINOR_VERSION     0
#define PITRTI_GPT_LLD_SW_PATCH_VERSION     0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if header file and Std_Types.h file are of the same Autosar version */
    #if ((PITRTI_GPT_LLD_AR_MAJOR_VERSION != STD_TYPES_AR_MAJOR_VERSION) || \
         (PITRTI_GPT_LLD_AR_MINOR_VERSION != STD_TYPES_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of PitRti_Gpt_LLD.h and Std_Types.h are different"
    #endif
#endif

#if (PITRTI_GPT_LLD_VENDOR_ID != GPT_VENDOR_ID)
#error "PitRti_Gpt_LLD.h and Gpt.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if header file and Gpt header file are of the same Autosar version */
    #if ((PITRTI_GPT_LLD_AR_MAJOR_VERSION != GPT_AR_MAJOR_VERSION) || \
         (PITRTI_GPT_LLD_AR_MINOR_VERSION != GPT_AR_MINOR_VERSION) || \
         (PITRTI_GPT_LLD_AR_PATCH_VERSION != GPT_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of PitRti_Gpt_LLD.h and Gpt.h are different"
    #endif
#endif
/* Check if header file and Gpt header file are of the same software version */
#if ((PITRTI_GPT_LLD_SW_MAJOR_VERSION != GPT_SW_MAJOR_VERSION) || \
     (PITRTI_GPT_LLD_SW_MINOR_VERSION != GPT_SW_MINOR_VERSION) || \
     (PITRTI_GPT_LLD_SW_PATCH_VERSION != GPT_SW_PATCH_VERSION))
#error "Software Version Numbers of PitRti_Gpt_LLD.h and Gpt.h are different"
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
#define PITRTI_TIMEOUT_VALUE (uint16)0x7FFFU

/*************************************************************************************************/
/**
@brief   PITRTI specific macro for checking the timeout value.
@details PITRTI specific macro for checking the timeout value.

@param[in]     hwChannel     PITRTI hw channel
@param[out]    None
@param[in,out] None

@return        True/False, depending on the correctness of the timeout value

@pre  None
@post None


@remarks Covers None
@remarks Implements DGPT08210
*/
/*************************************************************************************************/
#if (GPT_DEV_ERROR_DETECT == STD_ON)
/**
@note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro - See @ref PITRTI_Gpt_LLD_H_REF_1
*/
/* This is applicable for the following lines of code */
/*lint -save -e961 */
/**
@brief  PITRTI specific macro for checking the timeout value.
@param[in]      value     Timeout vaule
@return     Boolean
@retval     TRUE - Time out value is valid
@retval     FALSE - Time out value is Invalid
@remarks Implements DGPT09210
*/
#define PITRTI_LLD_INVALID_TIMEOUT_VALUE(value)    (value > PITRTI_LDVAL_MAX_VALUE)
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
@file  Pitrti_Gpt_LLD.h
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref PITRTI_Gpt_LLD_H_REF_2
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref PITRTI_Gpt_LLD_H_REF_3
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if header file and MemMap.h file are of the same Autosar version */
    #if ((PITRTI_GPT_LLD_AR_MAJOR_VERSION != MEMMAP_AR_MAJOR_VERSION) || \
         (PITRTI_GPT_LLD_AR_MINOR_VERSION != MEMMAP_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of PitRti_Gpt_LLD.h and MemMap.h are different"
    #endif
#endif

#define GPT_STOP_CONFIG_DATA_UNSPECIFIED
/**
@file  Pitrti_Gpt_LLD.h
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref PITRTI_Gpt_LLD_H_REF_2
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref PITRTI_Gpt_LLD_H_REF_3
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
@file  Pitrti_Gpt_LLD.h
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref PITRTI_Gpt_LLD_H_REF_2
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref PITRTI_Gpt_LLD_H_REF_3
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

/******************************************************************
| exported function prototypes
|-----------------------------------------------------------------*/
/*************************************************************************************************/
/**
@brief   Gpt driver initialization function for Pitrti module.
@details This function is called separately for each PITRTI hw channel corresponding to the configured
         timer channels, and:
         - enables the PITRTI module
         - configures the freeze mode (enabled/disabled)
         - disables the IRQ correpsonding to the PITRTI channel
         - clears the (pending) interrupt flag corresponding to Pitrti channel
         - disables the PITRTI timer channel
         - clears the Load Value register correponding to the Pitrti channel.

@param[in]     freezeEnable     indicates if the Freeze mode is enabled
@param[in]     hwChannel        Pitrti hw channel ID

@remarks Implements DGPT09205
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) PitRti_LLD_InitChannel(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel,
                                          VAR(boolean, AUTOMATIC) freezeEnable);

#if (GPT_DEINIT_API == STD_ON)
/*************************************************************************************************/
/**
@brief   Gpt driver de-initialization function for Pitrti module.
@details This function is called separately for each PITRTI hw channel corresponding to the configured
         timer channels, and:
         - disables the PITRTI channel
         - disables the freeze mode
         - disables IRQ corresponding to Pitrti channel
         - clears the (pending) interrupt flag corresponding to Pitrti channel

@param[in]     hwChannel        Pitrti hw channel ID

@remarks Implements DGPT09200
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) PitRti_LLD_DeInit(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel);
#endif
/*************************************************************************************************/
/**
@brief   Gpt driver function for starting the Pitrit timer channel.
@details This function:
         - clears the (pending) interrupt flag corresponding to Pitrti channel
         - disables the PITRTI timer channel
         - sets the load/timeout value into the PITRTI timer channel register
         - enables the PITRTI timer channel
         - enables the IRQ corresponding to the PITRTI timer channel,if channel configured in One Shot mode.

@param[in]     hwChannel        Pitrti hw channel ID
@param[in]     value            channel timeout value
@param[in]     channelMode      One Shot or Continous


@remarks Implements DGPT09208
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) PitRti_LLD_StartTimer(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel,
                                         VAR(Gpt_ValueType, AUTOMATIC) value,
                                         VAR(Gpt_ChannelModeType, AUTOMATIC) channelMode);
/*************************************************************************************************/
/**
@brief   Gpt driver function for stopping the Pitrti timer channel.
@details This function disables the PITRTIchannel

@param[in]     hwChannel        Pitrti hw channel ID

@remarks Implements DGPT09209
*/
/*************************************************************************************************/

FUNC (void, GPT_CODE) PitRti_LLD_StopTimer(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel);

#if (GPT_TIME_ELAPSED_API == STD_ON)
/*************************************************************************************************/
/**
@brief   Gpt driver function for getting the time elapsed for an Pitrti timer channel.
@details This function:
         - reads the PITRTI channel load register
         - reads the PITRTI counter register
         - depending on above it calculates and returns the elapsed time

@param[in]     hwChannel        Pitrti hw channel ID
@param[out]    returnValuePtr   elapsed time value

@remarks Implements DGPT09203
*/
/*************************************************************************************************/

FUNC (void, GPT_CODE) PitRti_LLD_GetTimeElapsed(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel,
                                             P2VAR(Gpt_ValueType, AUTOMATIC, GPT_APPL_DATA) returnValuePtr);
#endif

#if (GPT_TIME_REMAINING_API == STD_ON)
/*************************************************************************************************/
/**
@brief   Gpt driver function for getting the remaining time for an Pitrti timer channel.
@details This function reads the PITRTI counter register and returns the remaining time

@param[in]     hwChannel        Pitrti hw channel ID
@param[out]    returnValuePtr   elapsed time value

@remarks Implements DGPT09204
*/
/*************************************************************************************************/


FUNC (void, GPT_CODE) PitRti_LLD_GetTimeRemaining(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel,
                                               P2VAR(Gpt_ValueType, AUTOMATIC, GPT_APPL_DATA) returnValuePtr);
#endif

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/*************************************************************************************************/
/**
@brief   Gpt driver function for putting the Pitrti timer channel in SLEEP mode.
@details This function is called separately for each PITRTI hw channel corresponding to the configured
         timer channels, and:
         - clears the (pending) interrupt flag corresponding to Pitrti timer channel
         - disable the Pitrti timer channel if the channel wakeup function is disabled
         - enable the Pitrti timer channel if the channel wakeup function is enabled

@param[in]     hwChannel        Pitrti hw channel ID
@param[in]     wakeUpEnabled    Indicates whether wake up functionality is enabled or not for the
                                corresponding channel.

@remarks Implements DGPT09207
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) PitRti_LLD_SetSleepMode(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel,
                                           VAR(boolean, AUTOMATIC) wakeUpEnabled);
#endif

#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
/*************************************************************************************************/
/**
@brief   Gpt driver function for enabling the Pitrti timer channel notification/IRQ.
@details This function:
         - enables the IRQ corresponding to the Pitrti timer channel

@param[in]     hwChannel        Pitrti hw channel ID

@remarks Implements DGPT09202
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) PitRti_LLD_EnableNotification(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel);
/*************************************************************************************************/
/**
@brief   Gpt driver function for disabling the Pitrti timer channel notification/IRQ.
@details This function disables the IRQ corresponding to the Pitrti timer channel

@param[in]     hwChannel        Pitrti hw channel ID

@remarks Implements DGPT09201
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) PitRti_LLD_DisableNotification(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel);

/*********************************************************************/
#endif

#define GPT_STOP_SEC_CODE
/**
@file  Pitrti_Gpt_LLD.h
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref PITRTI_Gpt_LLD_H_REF_2
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref PITRTI_Gpt_LLD_H_REF_3
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif

#endif /*PITRTI_GPT_LLD_H*/
