/**
    @file    eMIOS_Gpt_LLD.h
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


@section eMIOS_Gpt_LLD_H_REF_1
Violates MISRA 2004 Advisory Rule 19.7: Use of fucntion like macro defined.
This violation is due to function like macros defined for register operations.
Function like macros are used to reduce code complexity.

@section eMIOS_Gpt_LLD_H_REF_2
Violates MISRA 2004 Advisory Rule 19.15: Repeated include file
This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement
MEMMAP003.

@section eMIOS_Gpt_LLD_H_REF_3
Violates MISRA 2004 Advisory Rule 19.1: only preprocessor statements and comments
before "#include". This violation is not fixed since the inclusion of MemMap.h
is as per Autosar requirement MEMMAP003.

*/

#ifndef EMIOS_GPT_LLD_H
#define EMIOS_GPT_LLD_H

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
@file  eMIOS_Gpt_LLD.h
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file Std_Types.h - See @ref eMIOS_Gpt_LLD_H_REF_2
*/
#include "Std_Types.h"

/* modules.h included as eMios200 may be used by Autosar drivers, other than Gpt  */
/**
@file  eMIOS_Gpt_LLD.h
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file modules.h - See @ref eMIOS_Gpt_LLD_H_REF_2
*/
#include "modules.h"
/**
@file  eMIOS_Gpt_LLD.h
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file Gpt.h - See @ref eMIOS_Gpt_LLD_H_REF_2
*/
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
#define EMIOS_GPT_LLD_VENDOR_ID            43
#define EMIOS_GPT_LLD_MODULE_ID            100
#define EMIOS_GPT_LLD_AR_MAJOR_VERSION     3
#define EMIOS_GPT_LLD_AR_MINOR_VERSION     0
#define EMIOS_GPT_LLD_AR_PATCH_VERSION     0
#define EMIOS_GPT_LLD_SW_MAJOR_VERSION     2
#define EMIOS_GPT_LLD_SW_MINOR_VERSION     0
#define EMIOS_GPT_LLD_SW_PATCH_VERSION     0
/**@}*/
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if header file and Std_Types.h file are of the same Autosar version */
    #if ((EMIOS_GPT_LLD_AR_MAJOR_VERSION != STD_TYPES_AR_MAJOR_VERSION) || \
         (EMIOS_GPT_LLD_AR_MINOR_VERSION != STD_TYPES_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of eMios_Gpt_LLD.h and Std_Types.h are different"
    #endif
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if header file and modules.h file are of the same Autosar version */
    #if ((EMIOS_GPT_LLD_AR_MAJOR_VERSION != MODULES_AR_MAJOR_VERSION_H) || \
         (EMIOS_GPT_LLD_AR_MINOR_VERSION != MODULES_AR_MINOR_VERSION_H))
    #error "AutoSar Version Numbers of eMios_Gpt_LLD.h and modules.h are different"
    #endif
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Gpt header file are of the same Autosar version */
    #if ((EMIOS_GPT_LLD_AR_MAJOR_VERSION != GPT_AR_MAJOR_VERSION) || \
         (EMIOS_GPT_LLD_AR_MINOR_VERSION != GPT_AR_MINOR_VERSION) || \
         (EMIOS_GPT_LLD_AR_PATCH_VERSION != GPT_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of eMios_Gpt_LLD.h and Gpt.h are different"
    #endif
#endif

/* Check if source file and Gpt header file are of the same software version */
#if ((EMIOS_GPT_LLD_SW_MAJOR_VERSION != GPT_SW_MAJOR_VERSION) || \
     (EMIOS_GPT_LLD_SW_MINOR_VERSION != GPT_SW_MINOR_VERSION) || \
     (EMIOS_GPT_LLD_SW_PATCH_VERSION != GPT_SW_PATCH_VERSION))
#error "Software Version Numbers of eMios_Gpt_LLD.h and Gpt.h are different"
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
#if (GPT_DEV_ERROR_DETECT == STD_ON)
/**
@brief  Emios specific macro for checking the timeout value.
@param[in]     value     Timeout vaule
@return     Boolean
@retval     TRUE - Time out value is valid
@retval     FALSE - Time out value is Invalid
@remarks Implements DGPT07213
*/
/**
@note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro - See @ref eMIOS_Gpt_LLD_H_REF_1
*/
/*lint -save -e961 */
#define EMIOS_LLD_INVALID_TIMEOUT_VALUE(value)    (value > EMIOS_EMIOSCNT_MAX_VALUE)
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
@file  eMIOS_Gpt_LLD.h
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref eMIOS_Gpt_LLD_H_REF_2
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments
       before "#include" - See @ref eMIOS_Gpt_LLD_H_REF_3
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if header file and MemMap.h file are of the same Autosar version */
    #if ((EMIOS_GPT_LLD_AR_MAJOR_VERSION != MEMMAP_AR_MAJOR_VERSION) || \
         (EMIOS_GPT_LLD_AR_MINOR_VERSION != MEMMAP_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of eMIOS_Gpt_LLD.h and MemMap.h are different"
    #endif
#endif

#define GPT_STOP_CONFIG_DATA_UNSPECIFIED
/**
@file  eMIOS_Gpt_LLD.h
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref eMIOS_Gpt_LLD_H_REF_2
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments
       before "#include" - See @ref eMIOS_Gpt_LLD_H_REF_3
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
@file  eMIOS_Gpt_LLD.h
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref eMIOS_Gpt_LLD_H_REF_2
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments
       before "#include" - See @ref eMIOS_Gpt_LLD_H_REF_3
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

/******************************************************************
| exported function prototypes
|-----------------------------------------------------------------*/
/*************************************************************************************************/
/**
@brief   Gpt driver initialization function for Emios module.
@details This function is called separately for each EMIOS hw channel corresponding to the configured
         timer channels, and:
         - disables the interrupt corresponding to Emios channel
         - puts the Emios channel into GPIO mode
         - sets the prescaler value
         - enables/disables the Freeze Mode
         - clears the (pending) interrupt flag corresponding to Emios channel
         - resets the UC A register.

@param[in]     freezeEnable     indicates if the Freeze mode is enabled
@param[in]     channelPrescale  prescaler value for the corresponding Emios channel
@param[in]     hwChannel        Emios hw channel ID

@remarks Implements DGPT07208
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Emios_LLD_InitChannel(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel,
                                            VAR(Gpt_PrescaleType, AUTOMATIC) channelPrescale,
                                            VAR(boolean, AUTOMATIC) freezeEnable);
#if (GPT_DEINIT_API == STD_ON)
/*************************************************************************************************/
/**
@brief   Gpt driver de-initialization function for Emios module.
@details This function is called for each EMIOS hw channel corresponding to the configured
         timer channels, and:
         - resets the Emios channel control register
         - resets the UC A register.
         - clears the (pending) interrupt flag corresponding to Emios channel

@param[in]     hwChannel        Emios hw channel ID

@remarks Implements DGPT07201
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Emios_LLD_DeInit(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel);
#endif
/*************************************************************************************************/
/**
@brief   Gpt driver function for starting the Emios timer channel.
@details This function:
         - puts the Emios channel into GPIO mode
         - enables the channel prescaler
         - programs the UC A register with the value passed as input parameter
         - sets the Emios channel mode to Modulus Counter Buffered (Up counter)
         - enables the IRQ for the Emios channel, if channel configured in One Shot mode.

@param[in]     hwChannel        Emios hw channel ID
@param[in]     value            channel timeout value
@param[in]     channelMode      channel mode: Continous or One Shot

@remarks Implements DGPT07211
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Emios_LLD_StartTimer(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel,
                                         VAR(Gpt_ValueType, AUTOMATIC) value,
                                         VAR(Gpt_ChannelModeType, AUTOMATIC) channelMode);
/*************************************************************************************************/
/**
@brief   Gpt driver function for stopping the Emios timer channel.
@details This function puts the Emios channel into GPIO mode

@param[in]     hwChannel        Emios hw channel ID

@remarks Implements DGPT07212
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Emios_LLD_StopTimer(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel);

#if (GPT_TIME_ELAPSED_API == STD_ON)
/*************************************************************************************************/
/**
@brief   Gpt driver function for getting the time elapsed for an Emios timer channel.
@details This function is called for reading the Emios channel counter register.

@param[in]     hwChannel        Emios hw channel ID
@param[out]    returnValuePtr   elapsed time value

@remarks Implements DGPT07206
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Emios_LLD_GetTimeElapsed(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel,
                                             P2VAR(Gpt_ValueType, AUTOMATIC, GPT_APPL_DATA) returnValuePtr);
#endif

#if (GPT_TIME_REMAINING_API == STD_ON)
/*************************************************************************************************/
/**
@brief   Gpt driver function for getting the time remaining for an Emios timer channel.
@details This function is called for reading the Emios channel counter register(s) to return the remaining time.

@param[in]     hwChannel        Emios hw channel ID
@param[out]    returnValuePtr   remaining time value

@remarks Implements DGPT07207
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Emios_LLD_GetTimeRemaining(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel,
                                               P2VAR(Gpt_ValueType, AUTOMATIC, GPT_APPL_DATA) returnValuePtr);
#endif

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/*************************************************************************************************/
/**
@brief   Gpt driver function for putting the Emios timer channel in SLEEP mode.
@details This function is called separately for each EMIOS hw channel corresponding to the configured
         timer channels, and:
         - clears the (pending) interrupt flag corresponding to Emios channel
         - puts the Emios channel into GPIO mode, if the wake up functionality is disabled
         - enables the IRQ for the Emios channel, if the wake up functionality is enabled

@param[in]     hwChannel        Emios hw channel ID
@param[in]     wakeUpEnabled    Indicates whether wake up functionality is enabled or not for the
                                corresponding channel.

@remarks Implements DGPT07210
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Emios_LLD_SetSleepMode(VAR(uint8, AUTOMATIC) hwChannel, VAR(boolean, AUTOMATIC) wakeUpEnabled);
#endif

#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
/*************************************************************************************************/
/**
@brief   Gpt driver function for enabling the Emios timer channel notifification/IRQ.
@details This function:
         - clears the (pending) interrupt flag corresponding to Emios channel
         - enables the IRQ corresponding to the Emios channel

@param[in]     hwChannel        Emios hw channel ID

@remarks Implements DGPT07204
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Emios_LLD_EnableNotification(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel);

/*************************************************************************************************/
/**
@brief   Gpt driver function for disabling the Emios timer channel notifification/IRQ.
@details This function disables the IRQ corresponding to the Emios channel

@param[in]     hwChannel        Emios hw channel ID

@remarks Implements DGPT07202
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Emios_LLD_DisableNotification(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel);
#endif

#if (GPT_DUAL_CLOCK_MODE == STD_ON)
/*************************************************************************************************/
/**
@brief      The function changes the EMIOS channel prescaler value.
@details    This function sets the EMIOS channel prescaler based on the input mode.

@param[in]  chPrescale     prescaler value for the corresponding Emios channel
@param[in]  hwChannel      Emios hw channel ID

@remarks    Covers PR-MCAL-3196
@remarks Implements DGPT11027
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Emios_LLD_SelectPrescaler(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel,
                                                VAR(Gpt_PrescaleType, AUTOMATIC) chPrescale);
/* GPT_DUAL_CLOCK_MODE == STD_ON */
#endif 

#define GPT_STOP_SEC_CODE
/**
@file  eMIOS_Gpt_LLD.h
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref eMIOS_Gpt_LLD_H_REF_2
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments
       before "#include" - See @ref eMIOS_Gpt_LLD_H_REF_3
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif

#endif /*EMIOS_GPT_LLD_H*/
