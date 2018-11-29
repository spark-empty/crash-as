/**
    @file    Gpt_LLD.h
    @version 2.0.0

    @brief   AUTOSAR Gpt - Gpt driver header file..
    @details GPT driver header file, containing variables, functions prototypes, data types and/or
             defines and macros that:
             - are Autosar specific and are not exported by the GPT driver.
             - are not related to the GPT driver related IPs.

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

@section GPT_LLD_H_REF1
    MISRA-C:2004   19.1:  Violates   MISRA  2004  Advisory  Rule   19.1,  only preprocessor
    statements and comments before '#include'
    This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement
    MEMMAP003.

@section GPT_LLD_H_REF2
    MISRA-C:2004   19.15:  Repeated include file
    This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement
    MEMMAP003.

@section GPT_LLD_H_REF3
    MISRA-C:2004 19.7 VIOLATION: Use of function like macro. This
violation is due to function like macros defined for register operations.
Function like macros are used to reduce code complexity.
*/

#ifndef GPT_LLD_H
#define GPT_LLD_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#if (GPT_DUAL_CLOCK_MODE == STD_ON)
#include "Gpt_NonASR.h"
#endif /* GPT_DUAL_CLOCK_MODE */

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@{
@brief   Source file version information
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define GPT_LLD_VENDOR_ID           43
#define GPT_LLD_AR_MAJOR_VERSION    3
#define GPT_LLD_AR_MINOR_VERSION    0
#define GPT_LLD_AR_PATCH_VERSION    0
#define GPT_LLD_SW_MAJOR_VERSION    2
#define GPT_LLD_SW_MINOR_VERSION    0
#define GPT_LLD_SW_PATCH_VERSION    0
/**@}*/
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/**
@{
@brief macro for GPT_WAKE_UP
@details macro for GPT_WAKE_UP status
*/
#define GPT_WAKE_UP_DISABLED          ((uint8)0x00U)
/**
@brief Macro to enable the wakeup on channel.
*/
#define GPT_WAKE_UP_ENABLED           ((uint8)0x01U)
/**@}*/

/**
@{
@brief macro for GPT_NOTIFICATION
@details macro for GPT_NOTIFICATION status
*/
#define GPT_NOTIFICATION_DISABLED     ((uint8)0x00U)
/**
@brief  Macro to disable the notification
*/
#define GPT_NOTIFICATION_ENABLED      ((uint8)0x01U)
/**@}*/

/* ---------------------------------------------- * | 5 bit | 1 bit | 1 bit | 1 bit | * | ....  | CH.MODE | WAKE_UP | NOTIF
   | * ---------------------------------------------- */
/*lint -save -e961 */
/**
@brief   macro for retrieving the channel mode
@details returns the channel mode from the Gpt_LLD_ChannelInfo array

@param[in]     channel         Numeric identifier of the GPT channel

@return value describing the channel mode
 @note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro See @ref GPT_LLD_H_REF_3
*/
#define GPT_GET_CHANNEL_MODE(channel)           (((Gpt_LLD_ChannelInfo[(channel)].BitInfo)&(uint8)0x04U)>>2U)

/**
@brief   macro for setting the channel mode
@details sets the channel's mode in the Gpt_LLD_ChannelInfo array

@param[in]     channel         Numeric identifier of the GPT channel
@param[in]     value           new value for channel mode
 @note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro See @ref GPT_LLD_H_REF_3 
*/
#define GPT_SET_CHANNEL_MODE(channel, value)    ((Gpt_LLD_ChannelInfo[(channel)].BitInfo) = ((uint8)((value)<<2U)|((Gpt_LLD_ChannelInfo[(channel)].BitInfo)&(uint8)~0x04U)))

/**
@brief   macro for retrieving the channel's WAKE_UP bit
@details returns the channel's GPT_WAKE_UP configuration from the Gpt_LLD_ChannelInfo array

@param[in]     channel         Numeric identifier of the GPT channel

@return value describing the channel's WAKE_UP configuration
@note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro See @ref GPT_LLD_H_REF_3 
*/
#define GPT_GET_WAKE_UP(channel)                (((Gpt_LLD_ChannelInfo[(channel)].BitInfo)&(uint8)0x02U)>>1U)

/**
@brief   macro for setting the channel's WAKE_UP bit
@details sets the chanel's GPT_WAKE_UP configuration in the Gpt_LLD_ChannelInfo array

@param[in]     channel         Numeric identifier of the GPT channel
@param[in]     value           new value for WAKE_UP
@note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro See @ref GPT_LLD_H_REF_3 
*/
#define GPT_SET_WAKE_UP(channel, value)         ((Gpt_LLD_ChannelInfo[(channel)].BitInfo) = ((uint8)((value)<<1U)|((Gpt_LLD_ChannelInfo[(channel)].BitInfo)&(uint8)~0x02U)))

/**
@brief   macro for retrieving the channel's NOTIFICATION bit
@details returns the channel's NOTIFICATION configuration from the Gpt_LLD_ChannelInfo array

@param[in]     channel         Numeric identifier of the GPT channel

@return value describing the channel's WAKE_UP configuration
 @note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro See @ref GPT_LLD_H_REF_3 
*/
#define GPT_GET_NOTIFICATION(channel)           ((Gpt_LLD_ChannelInfo[(channel)].BitInfo)&(uint8)0x01U)

/**
@brief   macro for setting the channel's NOTIFICATION bit
@details sets the channel's NOTIFICATION configuration in the Gpt_LLD_ChannelInfo array

@param[in]     channel         Numeric identifier of the GPT channel
@param[in]     value           new value for NOTIFICATION
@note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro See @ref GPT_LLD_H_REF_3 
*/
#define GPT_SET_NOTIFICATION(channel, value)    ((Gpt_LLD_ChannelInfo[(channel)].BitInfo) = ((value)|((Gpt_LLD_ChannelInfo[(channel)].BitInfo)&(uint8)~0x01U)))

/**
@brief   macro for retrieving the channel's WAKE_UP_CAPABILITY bit
@details returns the channel's WAKE_UP_CAPABILITY configuration from the Gpt_LLD_ChannelInfo array

@param[in]     channel         Numeric identifier of the GPT channel

@return value describing the channel's WAKE_UP_CAPABILITY configuration
 @note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro See @ref GPT_LLD_H_REF_3 
*/
#define GPT_LLD_GET_WAKE_UP_CAPABILITY(channel)\
            ((Gpt_LLD_ChannelConfigPtr[(channel)].Gpt_EnableWakeup == (boolean)TRUE) ? (TRUE) : (FALSE))
/* MISRA-C:2004 19.7 VIOLATION: End of code block */
/*lint -restore */

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/**
@brief Low level configuration for channel specific parameters
@remarks Implements DGPT02400
*/
typedef struct
{
    VAR(Gpt_ValueType, GPT_VAR) Gpt_ReloadValue; /**< @brief for a STM channel, it represents the timeout value; for RTC channel, it represents the start time value  */
    VAR(uint8, GPT_VAR) BitInfo;                 /**< @brief stores information about channel mode, wake up, notification - each on 1 bit */
} Gpt_LLD_ChannelInfoType;

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/* put all GPT variables into defined section */
#define GPT_START_SEC_VAR_UNSPECIFIED
/** @file Gpt_LLD.h */
/** @note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref GPT_LLD_H_REF1 */
/** @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref GPT_LLD_H_REF2 */
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if header file and MemMap.h file are of the same Autosar version */
    #if ((GPT_LLD_AR_MAJOR_VERSION != MEMMAP_AR_MAJOR_VERSION) || \
         (GPT_LLD_AR_MINOR_VERSION != MEMMAP_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Gpt_LLD.h and MemMap.h are different"
    #endif
#endif

/**
@brief  Array containing "HW channel" vs "logical channel correspondence" for EMIOS:
@remarks Implements DGPT03102
*/
extern VAR(uint8, GPT_VAR) GPT_LLD_EMIOS_HardwareMap[GPT_EMIOS_CHAN_NUM];

/**
@brief  Array containing "HW channel" vs "logical channel correspondence" for PIT:
@remarks Implements DGPT03103
*/
extern VAR(uint8, GPT_VAR) GPT_LLD_PITRTI_HardwareMap[GPT_PITRTI_CHAN_NUM];

/**
@brief  Array containing "HW channel" vs "logical channel correspondence" for STM:
@remarks Implements DGPT03104
*/
extern VAR(uint8, GPT_VAR) GPT_LLD_STM_HardwareMap[GPT_STM_CHAN_NUM];


/** 
@brief Pointer to a data structure containing channel configuration information (set in tresos)
@remarks Implements DGPT03100
*/
extern P2CONST(Gpt_LLD_ChannelConfigType, GPT_VAR, GPT_APPL_CONST) Gpt_LLD_ChannelConfigPtr;

/**
@brief Array of data structure elements storing timeout, channel mode, wakeup and notification
       information.
@remarks Implements DGPT03101
*/
extern VAR(Gpt_LLD_ChannelInfoType, GPT_VAR) Gpt_LLD_ChannelInfo[GPT_HW_CHANNEL_NUM];

#define GPT_STOP_SEC_VAR_UNSPECIFIED
/** @file Gpt_LLD.h */
/** @note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref GPT_LLD_H_REF1*/
/** @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref GPT_LLD_H_REF2*/
#include "MemMap.h"
/*lint -restore*/

#ifdef GPT_PRECOMPILE_SUPPORT

#define GPT_START_SEC_CONST_UNSPECIFIED
/** @file Gpt_LLD.h */
/** @note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref GPT_LLD_H_REF1*/
/** @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref GPT_LLD_H_REF2*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

    /* Configuration structures for PC */
    extern CONST(Gpt_ConfigType, GPT_CONST) Gpt_InitConfigPC;

#define GPT_STOP_SEC_CONST_UNSPECIFIED
/** @file Gpt_LLD.h */
/** @note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref GPT_LLD_H_REF1 */
/** @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref GPT_LLD_H_REF2*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

#endif


/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#define GPT_START_SEC_CODE
/** @file Gpt_LLD.h */
/** @note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref GPT_LLD_H_REF1*/
/** @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref GPT_LLD_H_REF2*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

/******************************************************************
| exported function prototypes
|-----------------------------------------------------------------*/
/**
@brief   Gpt driver Autosar independent and IP dependent initialization function.
@details This function is called only once and sets up all the channels from the current configuration.
         It initializes the internal GPT driver variables and arrays and calls the IP-specific
         initialization function.

@remarks Implements DGPT03208
*/
/*************************************************************************************************/

FUNC (void, GPT_CODE) Gpt_LLD_Init(void);
/*************************************************************************************************/
/**
@brief   Gpt driver Autosar independent and IP dependent de-initialization function.
@details This function is called only once and sets up all the channels from the current configuration.
         It de-initializes the internal GPT driver variables and calls the IP-specific de-initialization function.

@remarks Implements DGPT03201
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Gpt_LLD_DeInit(void);

/*************************************************************************************************/
/**
@brief   Gpt driver Autosar independent and IP dependent function for checking the timeout value of
         a channel.
@details It determines the type of the HW channel (e.g. eTimer, STM,etc...) and checks the
         provided value against the maximum supported HW value.

@param[in]     channel       Numeric identifier of the GPT channel
@param[in]     value         Timeout period (in ticks) after which a notification shall occur (if
                             enabled).

@pre  requires GPT_DEV_ERROR_DETECT = STD_ON

@remarks Implements DGPT03213
*/
/*************************************************************************************************/
FUNC (Std_ReturnType, GPT_CODE) Gpt_LLD_CheckStartTimeoutValue(VAR(Gpt_ChannelType, AUTOMATIC) channel,
                                                               VAR(Gpt_ValueType, AUTOMATIC) value);
/*************************************************************************************************/
/**
@brief   Gpt driver Autosar independent and IP dependent function for starting the timer channel.
@details It determines the type of the HW channel (e.g. eMios, STM,etc...), calculates
         its ID and calls the appropriate IP function for starting the timer channel.

@param[in]     channel       Numeric identifier of the GPT channel
@param[in]     value         Timeout period (in ticks) after which a notification shall occur (if
                             enabled).

@remarks Implements DGPT03211
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Gpt_LLD_StartTimer(VAR(Gpt_ChannelType, AUTOMATIC) channel,
                                                   VAR(Gpt_ValueType, AUTOMATIC) value);
/*************************************************************************************************/
/**
@brief   Gpt driver Autosar independent and IP dependent function for stopping the timer channel.
@details It determines the type of the HW channel (e.g. eMios, STM,etc...), calculates
         its ID and calls the appropriate IP function for stopping the timer channel.

@param[in]     channel       Numeric identifier of the GPT channel

@remarks Implements DGPT03212
*/
/*************************************************************************************************/

FUNC (void, GPT_CODE) Gpt_LLD_StopTimer(VAR(Gpt_ChannelType, AUTOMATIC) channel);
/** 
@brief   PITRTI_Gpt_ProcessInterrupt.
@details Non-AutoSar support function used by interrupt service routines to call notification 
         functions if provided and enabled
    
@param[in]     hwChannel      hardware channel index

@remarks Covers GPT206, GPT208, GPT233, GPT261, GPT326, GPT327
@remarks Implements DGPT04132
*/
FUNC (void, GPT_CODE) PITRTI_Gpt_ProcessInterrupt(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel);


/** 
@brief   STM_Gpt_ProcessInterrupt.
@details Non-AutoSar support function used by interrupt service routines to call notification 
         functions if provided and enabled
    
@param[in]     hwChannel      hardware channel index

@remarks Covers GPT206, GPT208, GPT233, GPT261, GPT326, GPT327
@remarks Implements DGPT04133
*/
FUNC (void, GPT_CODE) STM_Gpt_ProcessInterrupt(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel);

/** 
@brief   EMIOS_Gpt_LLD_ProcessInterrupt.
@details Non-AutoSar support function used by interrupt service routines to call notification 
         functions if provided and enabled
    
@param[in]     hwChannel      hardware channel index

@remarks Covers GPT206, GPT208, GPT233, GPT261, GPT326, GPT327
@remarks Implements DGPT04131
*/
FUNC (void, GPT_CODE) EMIOS_Gpt_LLD_ProcessInterrupt(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel);

#if (GPT_TIME_ELAPSED_API == STD_ON)
/*************************************************************************************************/
/**
@brief   Gpt driver Autosar independent and IP dependent function for fetching the elapsed timer value.
@details It determines the type of the HW channel (e.g. eTimer, STM,etc...) and calls the
         appropriate IP function for reading the HW timer and then it calculates the
         elapsed timer value.

@param[in]     channel         Numeric identifier of the GPT channel
@param[out]    returnValuePtr  Pointer to elapsed timer value

@pre  requires GPT_TIME_ELAPSED_API = STD_ON

@remarks Implements DGPT03206
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Gpt_LLD_GetTimeElapsed(VAR(Gpt_ChannelType, AUTOMATIC) channel,
                                             P2VAR(Gpt_ValueType, AUTOMATIC, GPT_APPL_DATA) returnValuePtr);
#endif


#if (GPT_TIME_REMAINING_API == STD_ON)
/*************************************************************************************************/
/**
@brief   Gpt driver Autosar independent and IP dependent function for fetching the remaining timer value.
@details It determines the type of the HW channel (e.g. eTimer, STM,etc...) and calls the
         appropriate IP function for reading the HW timer and then it calculates the
         remaining timer value.

@param[in]     channel         Numeric identifier of the GPT channel
@param[out]    returnValuePtr  Pointer to elapsed timer value

@pre  requires GPT_TIME_REMAINING_API = STD_ON

@remarks Implements DGPT03207
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Gpt_LLD_GetTimeRemaining(VAR(Gpt_ChannelType, AUTOMATIC) channel,
                                               P2VAR(Gpt_ValueType, AUTOMATIC, GPT_APPL_DATA) returnValuePtr);
#endif

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/**
@brief   Gpt driver Autosar independent and IP dependent function for setting the SLEEP mode.
@details For each of the configured channels, it determines the type of the HW channel
         (e.g. eTimer, STM,etc...) and stops the non-wake-up capable channel. The wake-up capable
         channels are not stopped.

@pre  requires GPT_WAKEUP_FUNCTIONALITY_API = STD_ON

@remarks Implements DGPT03210
*/
FUNC (void, GPT_CODE) Gpt_LLD_SetSleepMode(void);
/*************************************************************************************************/
/**
@brief   Gpt driver Autosar independent and IP dependent function for setting the Normal mode.
@details For each of the configured channels, it determines the type of the HW channel
         (e.g. eMios, STM,etc...) and enables the ocunter for STM and RTC channels.

@pre  requires GPT_WAKEUP_FUNCTIONALITY_API = STD_ON

@remarks Implements DGPT03209
*/
/*************************************************************************************************/

FUNC (void, GPT_CODE) Gpt_LLD_SetNormalMode(void);
#endif
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
/*************************************************************************************************/
/**
@brief   Gpt driver Autosar independent and IP dependent function for enabling the timer channel notification.
@details It resets the notification bit-field of Gpt_LLD_ChannelInfo[channel] and determines the
         type of the HW channel (e.g. eTimer, STM,etc...), and enables the corresponding IRQ, for
         all the channels except for the STM channels.

@param[in]     channel       Numeric identifier of the GPT channel

@pre  requires GPT_ENABLE_DISABLE_NOTIFICATION_API = STD_ON

@remarks Implements DGPT03204
*/
/*************************************************************************************************/

FUNC (void, GPT_CODE) Gpt_LLD_EnableNotification(VAR(Gpt_ChannelType, AUTOMATIC) channel);
/*************************************************************************************************/
/**
@brief   Gpt driver Autosar independent and IP dependent function for disabling the timer channel notification.
@details It resets the notification bit-field of Gpt_LLD_ChannelInfo[channel] and determines the
         type of the HW channel (e.g. eMios, STM,etc...), and disables the corresponding IRQ, for
         all the channels except for the STM channels.

@param[in]     channel       Numeric identifier of the GPT channel

@remarks Implements DGPT03202
*/
/*************************************************************************************************/


/**
@brief   Gpt driver Autosar independent and IP dependent function for disabling the timer channel notification.
@details It resets the notification bit-field of Gpt_LLD_ChannelInfo[channel] and determines the
         type of the HW channel (e.g. eTimer, STM,etc...), and disables the corresponding IRQ, for
         all the channels except for the STM channels.

@param[in]     channel       Numeric identifier of the GPT channel

@pre  requires GPT_ENABLE_DISABLE_NOTIFICATION_API = STD_ON

@remarks Implements DGPT03202
*/
FUNC (void, GPT_CODE) Gpt_LLD_DisableNotification(VAR(Gpt_ChannelType, AUTOMATIC) channel);
#endif

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/*************************************************************************************************/
/**
@brief   Gpt driver Autosar independent and IP dependent function for disabling the wakeup interrupt invocation
         of a timer channel.
@details It resets the wakeup bit-field of Gpt_LLD_ChannelInfo[channel].

@param[in]     channel       Numeric identifier of the GPT channel

@pre  requires GPT_WAKEUP_FUNCTIONALITY_API = STD_ON

@remarks Implements DGPT03203
*/
FUNC (void, GPT_CODE) Gpt_LLD_DisableWakeup(VAR(Gpt_ChannelType, AUTOMATIC) channel);

/**
@brief   Gpt driver Autosar independent and IP dependent function for enabling the wakeup interrupt invocation
         of a timer channel.
@details It sets the wakeup bit-field of Gpt_LLD_ChannelInfo[channel].

@param[in]     channel       Numeric identifier of the GPT channel

@pre  requires GPT_WAKEUP_FUNCTIONALITY_API = STD_ON

@remarks Implements DGPT03205
*/
/*************************************************************************************************/

FUNC (void, GPT_CODE) Gpt_LLD_EnableWakeup(VAR(Gpt_ChannelType, AUTOMATIC) channel);

/**
@brief   Gpt driver Autosar independent and IP dependent function for checking if a GPT channel is the source for
         wakeup event .
@details It checks if a GPT channel is the source for wakeup event and calls the ECU state manager
         service EcuM_SetWakeupEvent in case of a valid GPT channel wakeup event.
         channel wakeup event.

@param[in]     wakeupSource        Information on wakeup source to be checked.

@pre  requires GPT_WAKEUP_FUNCTIONALITY_API == STD_ON

@remarks Implements DGPT03200
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Gpt_LLD_Cbk_CheckWakeup(VAR(EcuM_WakeupSourceType, AUTOMATIC) wakeupSource);
/* GPT_WAKEUP_FUNCTIONALITY_API == STD_ON */
#endif 


#if (GPT_DUAL_CLOCK_MODE == STD_ON)
/*************************************************************************************************/
/**
@brief      This function changes the channel prescaler.
@details    This function sets all channels prescalers based on the input mode.

@param[in]  ClkMode  - clock mode ( Normal or Alternate )
@remarks    Covers PR-MCAL-3196
@remarks Implements DGPT11024
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Gpt_LLD_SelectPrescaler(VAR(Gpt_ClockModeType, AUTOMATIC) ClkMode);
/* GPT_DUAL_CLOCK_MODE == STD_ON */
#endif 
/*********************************************************************/

#define GPT_STOP_SEC_CODE
/** @file Gpt_LLD.h */
/** @note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref GPT_LLD_H_REF1*/
/** @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref GPT_LLD_H_REF2*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif

#endif /*GPT_LLD_H*/
