/**
    @file    Gpt.h
    @version 2.0.0

    @brief   AUTOSAR Gpt - Gpt driver header file.
    @details GPT driver header file, containing the Autosar API specification and other variables
             and functions that are exported by the GPT driver.

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

@section GPT_H_REF_1
Violates MISRA 2004 Advisory Rule 19.1, :  Violates   MISRA  2004  Advisory  Rule   19.1,  only preprocessor
statements and comments before "#include"
This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement
MEMMAP003.

@section GPT_H_REF_2
Violates MISRA 2004 Advisory Rule 19.15 : Repeated include file
This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement
MEMMAP003.
*/

#ifndef GPT_H
#define GPT_H

#ifdef __cplusplus
extern "C"{
#endif

/**
@file Gpt.h
@remarks Covers GPT262

*/

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/* see figure 1 - AUTOSAR_SWS_GPT_Driver.pdf, V2.2.1 */
/**
@file  Gpt.h
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref GPT_H_REF_2
*/
/**
@file Gpt.h
@remarks Covers Gpt278
*/
#include "Std_Types.h"
/**
@file Gpt.h
@remarks Covers Gpt259
@remarks Implements DGPT11030
*/
#include "Gpt_Cfg.h"

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/* see figure 1 - AUTOSAR_SWS_GPT_Driver.pdf, V2.2.1 */
/**
@file Gpt.h
@remarks Covers GPT271
*/
#include "EcuM_Cbk.h"
#endif
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@brief Parameters that shall be published within the Gpt driver header file and also in the
       module's description file
@remarks Covers BSW00374, BSW00379, BSW00318
@{
*/
#define GPT_VENDOR_ID            43
#define GPT_MODULE_ID            100
#define GPT_AR_MAJOR_VERSION     2
#define GPT_AR_MINOR_VERSION     2
#define GPT_AR_PATCH_VERSION     1
#define GPT_SW_MAJOR_VERSION     2
#define GPT_SW_MINOR_VERSION     0
#define GPT_SW_PATCH_VERSION     0
/**@}*/
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if header file and Std_Types.h file are of the same Autosar version */
    #if ((GPT_AR_MAJOR_VERSION != STD_TYPES_AR_MAJOR_VERSION) || \
         (GPT_AR_MINOR_VERSION != STD_TYPES_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Gpt.h and Std_Types.h are different"
    #endif
#endif

/* Check if source file and ADC configuration header file are of the same vendor */
#if (GPT_VENDOR_ID != GPT_VENDOR_ID_CFG)
    #error "Gpt.h and Gpt_Cfg.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if header file and GPT configuration header file are of the same Autosar version */
    #if ((GPT_AR_MAJOR_VERSION != GPT_AR_MAJOR_VERSION_CFG) || \
         (GPT_AR_MINOR_VERSION != GPT_AR_MINOR_VERSION_CFG) || \
         (GPT_AR_PATCH_VERSION != GPT_AR_PATCH_VERSION_CFG))
    #error "AutoSar Version Numbers of Gpt.h and Gpt_Cfg.h are different"
    #endif
#endif
/* Check if header file and GPT configuration header file are of the same software version */
#if ((GPT_SW_MAJOR_VERSION != GPT_SW_MAJOR_VERSION_CFG) || \
     (GPT_SW_MINOR_VERSION != GPT_SW_MINOR_VERSION_CFG) || \
     (GPT_SW_PATCH_VERSION != GPT_SW_PATCH_VERSION_CFG))
#error "Software Version Numbers of Gpt.h and Gpt_Cfg.h are different"
#endif

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
    #ifdef CHECK_AUTOSAR_VERSION
        /* Check if header file and EcuM_Cbk.h file are of the same Autosar version */
        #if ((GPT_AR_MAJOR_VERSION != ECUM_CBK_AR_MAJOR_VERSION) || \
             (GPT_AR_MINOR_VERSION != ECUM_CBK_AR_MINOR_VERSION))
        #error "AutoSar Version Numbers of Gpt.h and EcuM_Cbk.h are different"
        #endif
    #endif
#endif
/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
/**
@brief wrong module index in switch statement
@details Gpt_HW_Module has an out of range value
*/
#define GPT_CER_WRONGMODULE       (uint8)0x01U

/**
@brief error in interrupt function
@details hw channel has out of range value or configuration pointer is NULL (interrupt occured while
the driver was unitialized or the memory was corrupted)
*/
#define GPT_CER_UNINIT_INTERRUPT (uint8)0x02U

/* [GPT001]: The following development errors shall be detectable */
/* by the GPT driver depending on its build version (development/production mode). */
/* This checking shall be statically configurable (on/off) for those errors that */
/* [GPT174]: Development error values are of type uint8. */
/* only can occur during development */
/**
@brief Gpt DET defines
@remarks Covers GPT174, GPT001

*/
/**
@brief function called prior to initialization
@details Errors and exceptions that will be detected by the GPT driver
*/
#define GPT_E_UNINIT        (uint8)0x0AU
/**
@brief function called while timer is running
@details Errors and exceptions that will be detected by the GPT driver
*/
#define GPT_E_BUSY          (uint8)0x0BU
/**
@brief function called prior to starting the timer channel or called on a stopped channel
@details Errors and exceptions that will be detected by the GPT driver
*/
#define GPT_E_NOT_STARTED   (uint8)0x0CU
/**
@brief function called for channel out of range
@details Errors and exceptions that will be detected by the GPT driver
*/
#define GPT_E_PARAM_CHANNEL (uint8)0x14U
/**
@brief function called with Passed timer value out of range
@details Errors and exceptions that will be detected by the GPT driver
*/
#define GPT_E_PARAM_VALUE   (uint8)0x15U
/**
@brief function called with ConfigPtr = NULL
@details Errors and exceptions that will be detected by the GPT driver
*/
#define GPT_E_PARAM_CONFIG  (uint8)0x1EU
/**
@brief function  called with invalid mode param.
@details Errors and exceptions that will be detected by the GPT driver
*/
#define GPT_E_PARAM_MODE    (uint8)0x1FU
/**
@brief Gpt_Init() called twice
@details Errors and exceptions that will be detected by the GPT driver
*/
#define GPT_E_ALREADY_INITIALIZED (uint8)0x0DU

/* API SERVICE IDs */
/**
@brief API service ID for Gpt_LLD_CheckStartTimeoutValue  function
@details Parameters used when raising a CER error/exception
*/
#define GPT_CHECKTIMEOUTVALUE_ID       (uint8)0x00U

/**
@brief API service ID for Gpt_GetVersionInfo  function
@details Parameters used when raising an error/exception
*/
#define GPT_GETVERSIONINFO_ID       (uint8)0x00U
/**
@brief API service ID for Gpt_Init function
@details Parameters used when raising an error/exception
*/
#define GPT_INIT_ID                 (uint8)0x01U
/**
@brief API service ID for Gpt_DeInit function
@details Parameters used when raising an error/exception
*/
#define GPT_DEINIT_ID               (uint8)0x02U
/**
@brief API service ID for Gpt_GetTimeElapsed function
@details Parameters used when raising an error/exception
*/
#define GPT_TIMEELAPSED_ID          (uint8)0x03U
/**
@brief API service ID for Gpt_GetTimeRemaining function
@details Parameters used when raising an error/exception
*/
#define GPT_TIMEREMAINING_ID        (uint8)0x04U
/**
@brief API service ID for Gpt_StartTimer function
@details Parameters used when raising an error/exception
*/
#define GPT_STARTTIMER_ID           (uint8)0x05U
/**
@brief API service ID for Gpt_StopTimer function
@details Parameters used when raising an error/exception
*/
#define GPT_STOPTIMER_ID            (uint8)0x06U
/**
@brief API service ID for Gpt_EnableNotification function
@details Parameters used when raising an error/exception
*/
#define GPT_ENABLENOTIFICATION_ID   (uint8)0x07U
/**
@brief API service ID for Gpt_DisableNotification function
@details Parameters used when raising an error/exception
*/
#define GPT_DISABLENOTIFICATION_ID  (uint8)0x08U
/**
@brief API service ID for Gpt_SetMode function
@details Parameters used when raising an error/exception
*/
#define GPT_SETMODE_ID              (uint8)0x09U
/**
@brief API service ID for Gpt_DisableWakeup function
@details Parameters used when raising an error/exception
*/
#define GPT_DISABLEWAKEUP_ID        (uint8)0x0AU
/**
@brief API service ID for Gpt_EnableWakeup function
@details Parameters used when raising an error/exception
*/
#define GPT_ENABLEWAKEUP_ID         (uint8)0x0BU
/**
@brief API service ID for Gpt_Cbk_CheckWakeup function
@details Parameters used when raising an error/exception
*/
#define GPT_CBK_CHECKWAKEUP_ID      (uint8)0x0CU

/**
@brief Instance ID of this gpt driver.
*/
#define GPT_INSTANCE_ID   (uint8)0U
/**
@brief Macro to Intialise loop variable to 0.
*/
#define GPT_LOOP_INIT     (uint8)0U
/**
@brief Macro to Intialise loop variable to 0.
*/
#define GPT_INDEX_ZERO    (uint8)0U

/**
@brief one shot mode.
*/
#define GPT_MODE_ONESHOT             ((uint8)0x00U)
/**
@brief continous mode.
*/
#define GPT_MODE_CONTINOUS           ((uint8)0x01U)

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/**
@brief This enumerated type allows the selection of different power modes.

@remarks Implements DGPT02306
*/
typedef enum
{
    GPT_MODE_NORMAL = 0,                    /**< @brief GPT Normal operation mode of the GPT */
    GPT_MODE_SLEEP                          /**< @brief GPT sleep mode */
} Gpt_ModeType;

/**
@brief This enumerated type allows the selection of channel status type.

@remarks Implements DGPT02307
*/
typedef enum
{
    GPT_STATUS_UNINITIALIZED = 0,           /**< @brief GPT channel status - uninitialized */
    GPT_STATUS_INITIALIZED,                 /**< @brief GPT channel status - initialized */
    GPT_STATUS_STOPPED,                     /**< @brief GPT channel status - stopped */
    GPT_STATUS_EXPIRED,                     /**< @brief GPT channel status - expired */
    GPT_STATUS_RUNNING                      /**< @brief GPT channel status - running */
} Gpt_ChannelStatusType;

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/**
@brief Gpt channel ID data type

@remarks Implements DGPT02300
*/
typedef VAR(uint8,GPT_VAR) Gpt_ChannelType;

/**
@brief Gpt timeout value data type.Used for reading the current timer value/setting periodic timer
values (in number of ticks) up to hours
@remarks Implements DGPT02301
*/
typedef VAR(uint32,GPT_VAR) Gpt_ValueType;

/**
@brief Gpt channel notification type.  The callback notifications shall be configurable as pointers
to user defined functions within the configuration structure.
@remarks Implements DGPT02303
*/
typedef P2FUNC (void, GPT_APPL_CODE, Gpt_NotifyType)(void);

/**
@brief Gpt channel mode type. Indicates of whether the channel mode is "CONTINUOUS" or "ONE SHOT".

@remarks Implements DGPT02302
*/
typedef VAR(uint32,GPT_VAR) Gpt_ChannelModeType;

/**
@brief Gpt prescale type. It specifies the GPT module specific prescaler factor per channel.

@remarks Implements DGPT02304
*/
typedef VAR(uint32,GPT_VAR) Gpt_PrescaleType;

/**
@brief Gpt Wake up type.

@remarks Implements DGPT02305
*/
typedef VAR(uint32,GPT_VAR) Gpt_WakeUpType;

/**
@brief Gpt channel configuration type.
@remarks Covers GPT086, GPT209
@remarks Implements DGPT02308
*/
typedef struct
{
    VAR(Gpt_ChannelType, GPT_VAR) Gpt_HW_Channel;              /**< @brief GPT hw channel ID */
    VAR(Gpt_ChannelType, GPT_VAR) Gpt_HW_Module;               /**< @brief GPT hw module used */
    VAR(Gpt_ChannelModeType, GPT_VAR) Gpt_ChannelMode;         /**< @brief GPT channel mode */
    VAR(uint8, GPT_VAR) Gpt_ChannelClkSrc;                     /**< @brief GPT clock source */
    VAR(Gpt_PrescaleType, GPT_VAR) Gpt_ChannelPrescale;        /**< @brief GPT ch prescaler value*/
#if (GPT_DUAL_CLOCK_MODE == STD_ON)
    VAR(Gpt_PrescaleType, GPT_VAR) Gpt_ChannelPrescale_Alternate;/**<@brief ch 2nd prescaler val */
    /* GPT_DUAL_CLOCK_MODE */
#endif 
    VAR(boolean, GPT_VAR) Gpt_FreezeEnable;                    /**<@brief GPT ch freeze enable */
    VAR(boolean, GPT_VAR) Gpt_EnableWakeup;                    /**<@brief GPT ch WakeUp enable */
    VAR(Gpt_NotifyType, GPT_VAR) Gpt_Notification;             /**<@brief pointer to ISR function*/
    VAR(Gpt_WakeUpType, GPT_VAR) Gpt_ChannelWakeUpInfo;        /**<@brief EcuM wake up reference */
} Gpt_LLD_ChannelConfigType;

/**
@brief Gpt configuration type - this is the type of the data structure including the configuration
set required for initializing the GPT driver.
@remarks Covers GPT207
@remarks Implements DGPT02309
*/
typedef struct
{
    VAR(uint8, GPT_VAR) Gpt_Channel_Count;                  /**< @brief the number of GPT channels (configured in tresos plugin builder)*/
    P2CONST(Gpt_LLD_ChannelConfigType, GPT_VAR, GPT_APPL_CONST) Gpt_ChannelConfigPtr;   /**< brief pointer to the GPT channel configuration */
}Gpt_ConfigType;

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/* put all GPT variables into defined section */
#define GPT_START_SEC_VAR_UNSPECIFIED
/**
@file  Gpt.h
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref GPT_H_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref GPT_H_REF_2
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if header file and MemMap.h file are of the same Autosar version */
    #if ((GPT_AR_MAJOR_VERSION != MEMMAP_AR_MAJOR_VERSION) || \
         (GPT_AR_MINOR_VERSION != MEMMAP_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Gpt.h and MemMap.h are different"
    #endif
#endif

/*
*/
/**
@brief   Global array used for indicating the current status of the GPT channels.

@remarks Implements DGPT02101
*/
extern VAR(Gpt_ChannelStatusType, GPT_VAR) Gpt_ChannelStatus[GPT_HW_CHANNEL_NUM];
/**
@brief   Global variable used for indicating the current GPT driver mode.

@remarks Implements DGPT02102
*/
extern VAR(Gpt_ModeType, GPT_VAR) Gpt_Current_Mode;
/**
@brief   Global variable (pointer) used for storing the GPT driver configuration data

@remarks Implements DGPT02100
*/
extern P2CONST(Gpt_ConfigType, GPT_VAR, GPT_APPL_CONST) Gpt_Cfg_Ptr;
/**

@remarks Implements DGPT08102
*/

#define GPT_STOP_SEC_VAR_UNSPECIFIED
/**
@file  Gpt.h
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref GPT_H_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref GPT_H_REF_2
*//*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/


#ifndef GPT_PRECOMPILE_SUPPORT
#define GPT_START_CONFIG_DATA_UNSPECIFIED
/**
@file  Gpt.h
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref GPT_H_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref GPT_H_REF_2
*//*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

/* Import extern declarations of GPT configuration from Gpt_Cfg.h */
GPT_CFG_EXTERN_DECLARATIONS

#define GPT_STOP_CONFIG_DATA_UNSPECIFIED
/**
@file  Gpt.h
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref GPT_H_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref GPT_H_REF_2
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
@file  Gpt.h
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref GPT_H_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref GPT_H_REF_2
*//*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/
#if (GPT_VERSION_INFO_API == STD_ON)
/*************************************************************************************************/
/**
@brief   This function returns the version information of this module.
@details This service returns the version information of this module. The version information
         includes:
                   Module Id
                   Vendor Id
                   Vendor specific version numbers (BSW00407)


@param[out]    versioninfo - pointer to location to store version info



@remarks Covers GPT279, GPT181, GPT273, GPT182, GPT273
@remarks Implements DGPT02208
*/
/*************************************************************************************************/

extern FUNC(void, GPT_CODE) Gpt_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, 
                                                          GPT_APPL_DATA) versioninfo);
#endif
/*************************************************************************************************/
/**
@brief   GPT driver initialization function.
@details Service for driver initialization. The Initialization function shall initialize all relevant
         registers of the configured hardware with the values of the structure referenced by the parameter ConfigPtr.

         All time units used within the API services of the GPT driver shall be of the
         unit ticks.

         This function shall only initialize the configured resources. Resources that are
         not configured in the configuration file shall not be touched.

         The following rules regarding initialization of controller registers shall apply
         to the GPT Driver implementation:

         [1] If the hardware allows for only one usage of the register, the driver
             module implementing that functionality is responsible for initializing the register

         [2] If the register can affect several hardware modules and if it is an I/O register it
             shall be initialized by the PORT driver

         [3] If the register can affect several hardware modules and if it is not an I/O register
             it shall be initialized by the MCU driver

         [4] One-time writable registers that require initialization directly after reset shall be
             initialized by the startup code

         [5] All other registers shall be initialized by the startup code

@param[in]     configPtr        Pointer to a selected configuration structure


@remarks Covers GPT280, GPT006, GPT272, GPT176, GPT178, GPT204, GPT257, GPT258, GPT291, GPT294, GPT006
                GPT055,GPT068,GPT205
@remarks Implements DGPT02208
*/
/*************************************************************************************************/
extern FUNC (void, GPT_CODE) Gpt_Init(P2CONST(Gpt_ConfigType, AUTOMATIC, GPT_APPL_CONST) configPtr);

#if (GPT_DEINIT_API == STD_ON)
/*************************************************************************************************/
/**
@brief   GPT driver de-initialization function.
@details Service for deinitializing all hardware timer channels to their power on reset
         state.

         The state of the peripheral after DeInit shall be the same as after power on
         reset.

         The service influences only the peripherals, which are allocated by static
         configuration and the runtime configuration set passed by the previous call of Gpt_Init()

        The driver needs to be initialized before calling Gpt_DeInit(). Otherwise, the
        function Gpt_DeInit shall raise the development error GPT_E_UNINIT and leave the desired
        deinitialization functionality without any action.


@remarks Covers GPT281, GPT008, GPT161, GPT105, GPT162, GPT308, GPT194, GPT234, GPT220, GPT176, GPT178, GPT204, GPT291
                 GPT008,GPT088, GPT162

@remarks Implements DGPT02201
*/
/*************************************************************************************************/


extern FUNC (void, GPT_CODE) Gpt_DeInit(void);
#endif
#if (GPT_TIME_ELAPSED_API == STD_ON)
/*************************************************************************************************/
/**
@brief   GPT driver function for fetching the elapsed timer value.
@details Service for querying the time already elapsed.

         In one shot mode, this is the value relative to the point in time, the channel has been started
         with Gpt_StartTimer (calculated by the normal operation function by subtracting the current minus
         the initial timer value and returning the absolute value).

         In continuous mode, the function returns the timer value relative to the last timeout / the start
         of the channel.

         All time units used within the API services of the GPT driver shall be of the
         unit ticks.

         Usage of re-entrant capability is only allowed if the callers take care that
         there is no simultaneous usage of the same channel

         To get times out of register values it is necessary to know the oscillator
         frequency, prescalers and so on. Since these settings are made in MCU and/or in other
         modules it is not possible to calculate such times. Hence the conversions between time and
         ticks shall be part of an upper layer.

         The driver needs to be initialized before calling Gpt_GetTimeElapsed(). Otherwise,
         the function Gpt_GetTimeElapsed shall raise the development error GPT_E_UNINIT and return 0.

@param[in]     channel        channel id


@return  Gpt_ValueType
         -Elapsed Time in number of ticks

@remarks Covers GPT055, GPT282, GPT010, GPT295, GPT297, GPT299, GPT113, GPT195, GPT222, GPT210, GPT296,
                GPT298, GPT176, GPT178, GPT204, GPT291, GPT192
@remarks Implements DGPT02206
*/
/*************************************************************************************************/


extern FUNC (Gpt_ValueType, GPT_CODE) Gpt_GetTimeElapsed(VAR(Gpt_ChannelType, AUTOMATIC) channel);
#endif
#if (GPT_TIME_REMAINING_API == STD_ON)
/*************************************************************************************************/
/**
@brief   GPT driver function for fetching the remaining timer value.
@details This function returns the timer value remaining until the next timeout period
         will expire (calculated by the normal operation function by subtracting the timeout minus
         the current timer value and returning the absolute value)

          All time units used within the API services of the GPT driver shall be of the
         unit ticks.

         Usage of re-entrant capability is only allowed if the callers take care that
         there is no simultaneous usage of the same channel.

         To get times out of register values it is necessary to know the oscillator
         frequency, prescalers and so on. Since these settings are made in MCU and/or in other
         modules it is not possible to calculate such times. Hence the conversions between time and
         ticks shall be part of an upper layer.

         The driver needs to be initialized before calling Gpt_GetTimeRemaining(). Otherwise,
         the function Gpt_GetTimeRemaining shall raise the development error GPT_E_UNINIT and return 0.

@param[in]     channel        channel id


@return  Gpt_ValueType
         -Remaining Time in number of ticks

@remarks Covers GPT055, GPT283, GPT083, GPT301, GPT303, GPT305, GPT114, GPT196, GPT223, GPT211, GPT302,
                GPT304, GPT176, GPT178, GPT204, GPT291 GPT192
@remarks Implements DGPT02207
*/
/*************************************************************************************************/


extern FUNC (Gpt_ValueType, GPT_CODE) Gpt_GetTimeRemaining(VAR(Gpt_ChannelType, AUTOMATIC) channel);
#endif

/*************************************************************************************************/
/**
@brief   GPT driver function for starting a timer channel.
@details  The function Gpt_StartTimer shall start the selected timer channel with a
          defined timeout period.

          The function Gpt_StartTimer shall invoke the configured notification for that
          channel (see also GPT292) after the timeout period referenced via the parameter value (if
          enabled).

          All time units used within the API services of the GPT driver shall be of the
          unit ticks.

          In production mode no error is generated. The rational is that it adds no
          additional functionality to the driver. In this case the timer will be restarted with the
          timeout value, given as a parameter to the service.

          Usage of re-entrant capability is only allowed if the callers take care that
          there is no simultaneous usage of the same channel.

          To get times out of register values it is necessary to know the oscillator
          frequency, prescalers and so on. Since these settings are made in MCU and/or in other
          modules it is not possible to calculate such times. Hence the conversions between time and
          ticks shall be part of an upper layer.

         The driver needs to be initialized before calling Gpt_StartTimer(). Otherwise, the
         function Gpt_StartTimer shall raise the development error GPT_E_UNINIT.

@param[in]     channel        channel id
@param[in]     value          timeout period (in number of ticks) after a notification shall occur



@remarks Covers GPT055, GPT284, GPT274, GPT275, GPT115, GPT212, GPT218, GPT224, GPT084, GPT176, GPT178, GPT204, GPT291
                GPT085,GPT192
@remarks Implements DGPT02210
*/
/*************************************************************************************************/
/* GPT_START_STOP_TIMER_API switch is removed as it is removed from GPT SWS ver 2.1.0 */
extern FUNC (void, GPT_CODE) Gpt_StartTimer(VAR(Gpt_ChannelType, AUTOMATIC) channel,
                                            VAR(Gpt_ValueType, AUTOMATIC) value);

/*************************************************************************************************/
/**
@brief   GPT driver function for stopping a timer channel.
@details Service for stopping the selected timer channel

         Stopping a timer channel, not been started before will not return a development error
         Timer channels configured in one shot mode are stopped automatically, when the
         timeout period has expired.

         Usage of re-entrant capability is only allowed if the callers take care that
         there is no simultaneous usage of the same channel.

         The driver needs to be initialized before calling Gpt_StopTimer(). Otherwise,
         the function Gpt_StopTimer shall raise the development error GPT_E_UNINIT.

@param[in]     channel        channel id


@remarks Covers GPT055, GPT285, GPT013, GPT099, GPT103, GPT116, GPT213, GPT225, GPT176, GPT178, GPT204, GPT291
@remarks Implements DGPT02211
*/
/*************************************************************************************************/

extern FUNC (void, GPT_CODE) Gpt_StopTimer(VAR(Gpt_ChannelType, AUTOMATIC) channel);

#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)

/*************************************************************************************************/
/**
@brief   GPT driver function for enabling the notification for a timer channel.
@details  Service for enabling the notification for a channel during runtime.

          This function can be called, while the timer is already running.

          Usage of re-entrant capability is only allowed if the callers take care that
          there is no simultaneous usage of the same channel.

          The driver needs to be initialized before calling Gpt_EnableNotification(). Otherwise,
          the function Gpt_EnableNotification shall raise the development error GPT_E_UNINIT.

@param[in]     channel        channel id


@remarks Covers GPT286, GPT014, GPT117, GPT199, GPT226, GPT214, GPT176, GPT178, GPT204, GPT291, GPT091
@remarks Implements DGPT02204
*/
/*************************************************************************************************/
extern FUNC (void, GPT_CODE) Gpt_EnableNotification(VAR(Gpt_ChannelType, AUTOMATIC) channel);

/*************************************************************************************************/
/**
@brief   GPT driver function for disabling the notification for a timer channel.
@details Service for disabling the notification for a channel during runtime.

         This function can be called, while the timer is already running

         When disabled, no notification will be sent. When re-enabled again, the user
         will not be notified of events, occurred while notifications have been disabled.

         Usage of re-entrant capability is only allowed if the callers take care that
         there is no simultaneous usage of the same channel.

         The driver needs to be initialized before calling Gpt_DisableNotification().
         Otherwise, the function Gpt_DisableNotification shall raise the development error GPT_E_UNINIT.

@param[in]     channel        channel id


@remarks Covers GPT287, GPT015, GPT118, GPT200, GPT227, GPT217, GPT176, GPT178, GPT204, GPT291, GPT092, GPT093
@remarks Implements DGPT02204
*/
/*************************************************************************************************/

extern FUNC (void, GPT_CODE) Gpt_DisableNotification(VAR(Gpt_ChannelType, AUTOMATIC) channel);
#endif

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
/*************************************************************************************************/
/**
@brief   GPT driver function for setting the operation mode.
@details Service for GPT mode selection. This service shall set the operation mode to
         the given mode parameter .

         When sleep mode is requested, the ECU State Manager calls Gpt_SetMode with mode
         parameter "GPT_MODE_SLEEP" and prepares the GPT for sleep mode. The MCU Driver is then
         putting the controller into SLEEP mode

         The driver needs to be initialized before calling Gpt_SetMode(). Otherwise, the
         function Gpt_SetMode shall raise the development error GPT_E_UNINIT.

@param[in]     mode        operation mode


@remarks Covers GPT288, GPT151, GPT255, GPT152, GPT153, GPT164, GPT165, GPT228, GPT231, GPT201, GPT176, GPT178, GPT204, GPT291
                GPT128
@remarks Implements DGPT02209
*/
/*************************************************************************************************/

extern FUNC (void, GPT_CODE) Gpt_SetMode(VAR(Gpt_ModeType, AUTOMATIC) mode);
/*************************************************************************************************/
/**
@brief   GPT driver function for disabling the wakeup interrupt invocation for a timer channel.
@details This service shall disable the wakeup interrupt invocation of a single GPT
         channel.

         Usage of re-entrant capability is only allowed if the callers take care that
         there is no simultaneous usage of the same channel.

         The driver needs to be initialized before calling Gpt_DisableWakeup(). Otherwise, the
         function Gpt_DisableWakeup shall raise the development error GPT_E_UNINIT.

@param[in]     channel        channel id

@remarks Covers GPT289, GPT159, GPT157, GPT155, GPT202, GPT215, GPT229, GPT176, GPT178, GPT204, GPT291
@remarks Implements DGPT02203
*/
/*************************************************************************************************/

extern FUNC (void, GPT_CODE) Gpt_DisableWakeup(VAR(Gpt_ChannelType, AUTOMATIC) channel);

/*************************************************************************************************/
/**
@brief   GPT driver function for enabling the wakeup interrupt invocation for a timer channel.
@details This service shall re-enable the wakeup interrupt invocation of a single GPT
         channel.

         If supported by hardware and enabled, an internal hardware timer can serve as a
         wakeup source

         Usage of re-entrant capability is only allowed if the callers take care that
         there is no simultaneous usage of the same channel.

@param[in]     channel        channel id

@remarks Covers GPT290, GPT158, GPT156, GPT203, GPT230, GPT216, GPT160, GPT176, GPT178, GPT204, GPT291
                GPT127
@remarks Implements DGPT02205
*/
/*************************************************************************************************/

extern FUNC (void, GPT_CODE) Gpt_EnableWakeup(VAR(Gpt_ChannelType, AUTOMATIC) channel);
/*************************************************************************************************/
/**
@brief   GPT driver function for checking if a wakeup capable GPT channel is the source for a
         wakeup event.
@details Checks if a wakeup capable GPT channel is the source for a wakeup event and calls the ECU
         state manager service EcuM_SetWakeupEvent in case of a valid GPT channel wakeup event.

         The driver needs to be initialized before calling Gpt_Cbk_CheckWakeup(). Otherwise, the
         function Gpt_Cbk_CheckWakeup shall raise the development error GPT_E_UNINIT.

@param[in]     wakeupSource        wakeup source


@remarks Covers GPT328, GPT321, GPT322, GPT323, GPT324, GPT325, GPT176, GPT178, GPT204, GPT291, GPT328
@remarks Implements DGPT02200
*/
/*************************************************************************************************/
extern FUNC (void, GPT_CODE) Gpt_Cbk_CheckWakeup(VAR(EcuM_WakeupSourceType, AUTOMATIC) wakeupSource);
#endif
#endif

#define GPT_STOP_SEC_CODE
/**
@file  Gpt.h
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref GPT_H_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref GPT_H_REF_2
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif

#endif /*GPT_H*/
