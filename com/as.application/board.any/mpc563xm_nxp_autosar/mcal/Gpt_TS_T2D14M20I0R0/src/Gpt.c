/**
    @file    Gpt.c
    @version 2.0.0

    @brief   AUTOSAR Gpt - GPT driver source file.
    @details GPT driver source file, containing the C implementation of Autosar API specification
             and other variables and functions that are exported by the GPT driver.

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

@section GPT_C_REF_1
Violates MISRA 2004 Advisory Rule 19.1: Violates  MISRA 2004  Advisory  Rule 19.1, only preprocessor
statements and comments before "#include"
This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement
MEMMAP003.

@section GPT_C_REF_2
Violates MISRA 2004 Advisory Rule 19.15: Repeated include file
This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement
MEMMAP003.

@section GPT_C_REF_3
Violates MISRA 2004 Advisory Rule  1.2: Taking address of near auto variable
The pointer is used only within scope.

@section GPT_C_REF_4
 MISRA-C:2004  17.4: pointer arithmetic other than array indexing used
 This violation is due to the use of pointer arithmatic, which is used for the speed optimization,
 the indexing of the pointer is taken care and hence the unintended memory location will not be
 accessed.

@section GPT_C_REF_5
 MISRA-C:2004   10.1:  Implicit conversion changes signedness.
 The used values are predefined in an enumeration.
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
/** @remarks Covers GPT293 */
/**@remarks Implements DGPT11029 */ 
#include "Gpt.h"
/**@remarks Implements DGPT11033*/
#include "Gpt_LLD.h"

#include "SchM_Gpt.h"

#include "Dem.h"
#if (GPT_DEV_ERROR_DETECT == STD_ON)
    #include "Det.h"
#endif

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/** @remarks Covers BSW00374, BSW00318, GPT256 */
/* [GPT256]: The integration of incompatible files shall be avoided. */
/* Minimum implementation is the version check of the header file. */
/* For included header files: GPT_AR_MAJOR_VERSION and GPT_AR_MINOR_VERSION shall be identical. */
/* For the module internal c and h files: */
/* GPT_SW_MAJOR_VERSION, GPT_SW_MINOR_VERSION,GPT_SW_PATCH_VERSION, */
/*  GPT_AR_MAJOR_VERSION, GPT_AR_MINOR_VERSION, GPT_AR_PATCH_VERSION shall be identical. */
/**
@brief Parameters that shall be published within the Gpt driver header file and also in the
       module's description file
@remarks Covers BSW00374, BSW00379, BSW00318
@{
*/

#define GPT_VENDOR_ID_C         43
#define GPT_AR_MAJOR_VERSION_C  3
#define GPT_AR_MINOR_VERSION_C  0
#define GPT_AR_PATCH_VERSION_C  0
#define GPT_SW_MAJOR_VERSION_C  2
#define GPT_SW_MINOR_VERSION_C  0
#define GPT_SW_PATCH_VERSION_C  0
/**@}*/
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/*
*/
/* Check if source file and GPT header file are of the same vendor */
#if (GPT_VENDOR_ID_C != GPT_VENDOR_ID)
    #error "Gpt.c and Gpt.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
/* Check if source file and GPT header file are of the same Autosar version */
#if ((GPT_AR_MAJOR_VERSION_C != GPT_AR_MAJOR_VERSION) || \
     (GPT_AR_MINOR_VERSION_C != GPT_AR_MINOR_VERSION) || \
     (GPT_AR_PATCH_VERSION_C != GPT_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Gpt.c and Gpt.h are different"
#endif
#endif
/* Check if source file and GPT header file are of the same Software version */
#if ((GPT_SW_MAJOR_VERSION_C != GPT_SW_MAJOR_VERSION) || \
     (GPT_SW_MINOR_VERSION_C != GPT_SW_MINOR_VERSION) || \
     (GPT_SW_PATCH_VERSION_C != GPT_SW_PATCH_VERSION))
    #error "Software Version Numbers of Gpt.c and Gpt.h are different"
#endif

#if (GPT_VENDOR_ID_C != GPT_LLD_VENDOR_ID)
    #error "Gpt.c and Gpt_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
/* Check if source file and GPT LLD header file are of the same Autosar version */
#if ((GPT_AR_MAJOR_VERSION_C != GPT_LLD_AR_MAJOR_VERSION) || \
     (GPT_AR_MINOR_VERSION_C != GPT_LLD_AR_MINOR_VERSION) || \
     (GPT_AR_PATCH_VERSION_C != GPT_LLD_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Gpt.c and Gpt_LLD.h are different"
#endif
#endif
/* Check if source file and GPT LLD header file are of the same Software version */
#if ((GPT_SW_MAJOR_VERSION_C != GPT_LLD_SW_MAJOR_VERSION) || \
     (GPT_SW_MINOR_VERSION_C != GPT_LLD_SW_MINOR_VERSION) || \
     (GPT_SW_PATCH_VERSION_C != GPT_LLD_SW_PATCH_VERSION))
    #error "Software Version Numbers of Gpt.c and Gpt_LLD.h are different"
#endif

    #ifdef CHECK_AUTOSAR_VERSION
/* Check if source file and SchM Gpt header file are of the same version */
#if ((GPT_AR_MAJOR_VERSION_C != SCHM_GPT_AR_MAJOR_VERSION) || \
     (GPT_AR_MINOR_VERSION_C != SCHM_GPT_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Gpt.c and SchM_Gpt.h are different"
#endif
#endif

#ifdef CHECK_AUTOSAR_VERSION
/* Check if source file and Dem header file are of the same version */
#if ((GPT_AR_MAJOR_VERSION_C != DEM_AR_MAJOR_VERSION) || \
     (GPT_AR_MINOR_VERSION_C != DEM_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Gpt.c and Dem.h are different"
#endif
#endif

#if (GPT_DEV_ERROR_DETECT == STD_ON)
#ifdef CHECK_AUTOSAR_VERSION
/* Check if source file and DET header file are of the same version */
#if ((GPT_AR_MAJOR_VERSION_C != DET_AR_MAJOR_VERSION) || \
     (GPT_AR_MINOR_VERSION_C != DET_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Gpt.c and Det.h are different"
#endif
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
#define GPT_START_SEC_VAR_UNSPECIFIED
/**
@file  Gpt.c
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref GPT_C_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref GPT_C_REF_2
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

/* there is no version check with MemMap.h as checks were made:
   - Gpt.h vs Gpt.c
   - Gpt.h vs MemMap.h
   therefore there is no need to add checks for MemMap.h in both .c and .h files
*/

/**
@brief   Global variable used for indicating the current GPT driver mode.

@remarks Implements DGPT02102
*/
VAR(Gpt_ModeType, GPT_VAR) Gpt_Current_Mode = GPT_MODE_NORMAL;

/**
@brief   Global array used for indicating the current status of the GPT channels.

@remarks Implements DGPT02101
*/
VAR(Gpt_ChannelStatusType, GPT_VAR) Gpt_ChannelStatus[GPT_HW_CHANNEL_NUM];

/**
@brief   Global variable (pointer) used for storing the GPT driver configuration data.

@remarks Implements DGPT02100
*/
P2CONST(Gpt_ConfigType, GPT_VAR, GPT_APPL_CONST) Gpt_Cfg_Ptr = NULL_PTR;

#define GPT_STOP_SEC_VAR_UNSPECIFIED

/**
@file  Gpt.c
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref GPT_C_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref GPT_C_REF_2
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
#define GPT_START_SEC_CODE
/**
@file  Gpt.c
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref GPT_C_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref GPT_C_REF_2
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

/*************************************************************************************************/
/**
@brief   This function returns the version information of this module.
@details This service returns the version information of this module. The version information
         includes:
                   Module Id
                   Vendor Id
                   Vendor specific version numbers (BSW00407).


@param[out]    versioninfo - pointer to location to store version info



@remarks Covers GPT279, GPT181, GPT273, GPT182, GPT273
@remarks Implements DGPT02208
*/
/*************************************************************************************************/
#if (GPT_VERSION_INFO_API == STD_ON)
FUNC(void, GPT_CODE) Gpt_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, GPT_APPL_DATA) versioninfo)
{
/*
*/

/* [GPT182]: This function shall be pre compile time configurable On/Off */
/* by the configuration parameter: GPT_VERSION_INFO_API */
/* [GPT204]: If development error detection is enabled for the GPT Driver, */
/* the following API parameter checking shall be performed according to the */
/* respective functions (see table below). The error shall be reported to the Development Error Tracer. */
/* GetVersionInfo - GPT_E_UNINIT - Function called prior to initialization */
/* [GPT221]: If development error detection is enabled and Gpt_DeInit is called prior to */
/* initializing the driver, the development error code GPT_E_UNINIT will be reported */
/* Hint: If source code for caller and callee of this function is available this function */
/* should be realized as a macro. The macro should be defined in the modules header file. */
    versioninfo->vendorID         = (uint16)GPT_VENDOR_ID;
    versioninfo->moduleID         = (uint16)GPT_MODULE_ID;
    versioninfo->instanceID       = (uint8)GPT_INSTANCE_ID;
    versioninfo->sw_major_version = (uint8)GPT_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = (uint8)GPT_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = (uint8)GPT_SW_PATCH_VERSION;
}
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
FUNC (void, GPT_CODE) Gpt_Init(P2CONST(Gpt_ConfigType, AUTOMATIC, GPT_APPL_CONST) configPtr)
{
    VAR(Gpt_ChannelType, AUTOMATIC) channelIndex;

    /* [GPT178]: Detected development errors shall be reported to the */
    /* Det_ReportError service of the Development Error Tracer (DET) */
    /* if the preprocessor switch GPT_DEV_ERROR_DETECT is set */
    /* [GPT204]: If development error detection is enabled for the GPT Driver, */
    /* the following API parameter checking shall be performed according to the */
    /* respective functions (see table below). The error shall be reported to the Development Error Tracer. */
    /* Init - GPT_E_PARAM_CONFIG - ConfigPtr = NULL */

#if (GPT_DEV_ERROR_DETECT == STD_ON)
/* If already initialized, error */
    if (NULL_PTR != Gpt_Cfg_Ptr)
    {
        Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                        (uint8)GPT_INIT_ID, (uint8)GPT_E_ALREADY_INITIALIZED);
    }

#ifndef GPT_PRECOMPILE_SUPPORT
    else if (NULL_PTR == configPtr)
    {
        Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                        (uint8)GPT_INIT_ID, (uint8)GPT_E_PARAM_CONFIG);
    }
#endif
    else
    {

#endif

#ifdef GPT_PRECOMPILE_SUPPORT
        if (NULL_PTR == configPtr)
        {
            Gpt_Cfg_Ptr = &Gpt_InitConfigPC;
        }
        else
#endif
        {
            Gpt_Cfg_Ptr = configPtr;
        }

        /* Reset Channel STATUS */
        for (channelIndex = GPT_LOOP_INIT; channelIndex < (Gpt_ChannelType)GPT_HW_CHANNEL_NUM; channelIndex++)
        {
            Gpt_ChannelStatus[channelIndex] = GPT_STATUS_UNINITIALIZED;
        }

        Gpt_Current_Mode = GPT_MODE_NORMAL;

        Gpt_LLD_Init();

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    }
#endif
}

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
/* [GPT194]: This function shall be pre compile time configurable */
/* On/Off by the configuration parameter: GPT_DEINIT_API */
#if (GPT_DEINIT_API == STD_ON)
FUNC (void, GPT_CODE) Gpt_DeInit(void)
{
    VAR(Gpt_ChannelType, AUTOMATIC) channelIndex;

    /* [GPT178]: Detected development errors shall be reported to the */
    /* Det_ReportError service of the Development Error Tracer (DET) */
    /* if the preprocessor switch GPT_DEV_ERROR_DETECT is set */
    /* [GPT204]: If development error detection is enabled for the GPT Driver, */
    /* the following API parameter checking shall be performed according to the */
    /* respective functions (see table below). The error shall be reported to the Development Error Tracer. */
    /* DeInit - GPT_E_UNINIT - Function called prior to initialization */
    /* GPT_E_BUSY - Function called while timer is running */
#if (GPT_DEV_ERROR_DETECT == STD_ON)

    VAR(StatusType, AUTOMATIC) tempExit = (StatusType) E_OK;
    /* [GPT220] - If development error detection is enabled and Gpt_DeInit is called */
    /* prior to initializing the driver, the development error code GPT_E_UNINIT will be raised */
    if (NULL_PTR == Gpt_Cfg_Ptr)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                        (uint8)GPT_DEINIT_ID, (uint8)GPT_E_UNINIT);
        tempExit = (StatusType)E_NOT_OK;
    }
    else
    {
        /* [GPT234] - If development error detection is enabled and Gpt_DeInit is called, */
        /* while the timer is running, the driver shall report GPT_E_BUSY and the desired */
        /* deinitialization functionality shall be left without any action */
        for (channelIndex = GPT_LOOP_INIT; channelIndex < Gpt_Cfg_Ptr->Gpt_Channel_Count; channelIndex++)
        {
            if (GPT_STATUS_RUNNING == Gpt_ChannelStatus[channelIndex])
            {
                Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                                (uint8)GPT_DEINIT_ID, (uint8)GPT_E_BUSY);
                tempExit = (StatusType)E_NOT_OK;
            }
        }
    }
    if ((StatusType) E_OK == tempExit)
    {
#endif

        /* [GPT161] - After the call of this service, the state of the peripherals */
        /* used by configuration shall be the same as after power on reset. */
        /* Values of registers, which are not writable, are excluded. */
        /* Reset configured channels back to reset state */
        /* Low Level De-initialization */
        Gpt_LLD_DeInit();

        /* Reset Channel STATUS */
        for (channelIndex = GPT_LOOP_INIT; channelIndex < (Gpt_ChannelType)GPT_HW_CHANNEL_NUM; channelIndex++)
        {
            Gpt_ChannelStatus[channelIndex] = GPT_STATUS_UNINITIALIZED;
        }

        Gpt_Current_Mode = GPT_MODE_NORMAL;
        Gpt_Cfg_Ptr = NULL_PTR;

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    }
#endif
}
#endif

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
/* [GPT195]: This function shall be pre compile time configurable On/Off */
/* by the configuration parameter: GPT_TIME_ELAPSED_API */
#if (GPT_TIME_ELAPSED_API == STD_ON)
FUNC (Gpt_ValueType, GPT_CODE) Gpt_GetTimeElapsed(VAR(Gpt_ChannelType, AUTOMATIC) channel)
{
    VAR(Gpt_ValueType, AUTOMATIC) tempReturn = 0U;

    /* [GPT178]: Detected development errors shall be reported to the */
    /* Det_ReportError service of the Development Error Tracer (DET) */
    /* if the preprocessor switch GPT_DEV_ERROR_DETECT is set */
    /* [GPT204]: If development error detection is enabled for the GPT Driver, the following API parameter checking shall
       be performed according to the respective functions (see table below). The error shall be reported to the Development
       Error Tracer. GPT_E_UNINIT - called prior to initialization GPT_E_NOT_STARTED - called prior to starting the timer
       channel GPT_E_NOT_STARTED - called on a stopped channel GPT_E_NOT_STARTED - called on an expired ch. in oneshot mode
       GPT_E_PARAM_CHANNEL - channel out of range */
#if (GPT_DEV_ERROR_DETECT == STD_ON)

    if (NULL_PTR == Gpt_Cfg_Ptr)
    {
        Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID, (uint8)GPT_TIMEELAPSED_ID,
                                                                             (uint8)GPT_E_UNINIT);
    }
    /* [GPT210]: If development error detection is enabled and Gpt_GetTimeElapsed is called with an invalid channel
       parameter, the development error code GPT_E_PARAM_CHANNEL will be raised. In this case, value 0 is returned. */
    else if (channel >= Gpt_Cfg_Ptr->Gpt_Channel_Count)
    {
        Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID, (uint8)GPT_TIMEELAPSED_ID,
                                                                       (uint8)GPT_E_PARAM_CHANNEL);
    }
    /* [GPT097]: Calling Gpt_GetTimeElapsed prior to starting the specified timer channel will cause a development error
       and the error code GPT_E_NOT_STARTED shall be raised. In this case, value 0 is returned . */
    /* [GPT267]: When Calling this function on a stopped timer channel (channel has been initialized and started before),
       value 0 is returned. If development error detection is enabled, GPT_E_NOT_STARTED shall be raised (see section
       7.2) The rationale is to have the same behaviour for a stopped channel like a never started channel. */
    /* [GPT100]: When calling this function on a channel configured for one shot mode, after the timeout period has already
       expired, value 0 is returned. If development error detection is enabled, GPT_E_NOT_STARTED shall be raised in (see
       section 7.2). */
    else
    {
#endif
        if (GPT_STATUS_RUNNING != Gpt_ChannelStatus[channel])
        {
            /*
            @remarks Covers GPT295, GPT296, GPT297, GPT298, GPT299
            @remarks Implements DGPT11010, DGPT11011, DGPT11013
            if DET is enabled, raise GPT_E_NOT_STARTED
            do nothing in order to return 0
            */
#if (GPT_DEV_ERROR_DETECT == STD_ON)
            Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                            (uint8)GPT_TIMEELAPSED_ID, (uint8)GPT_E_NOT_STARTED);
#endif
        }
        else
        {
            /**
            @note  Violates MISRA 2004 Advisory Rule 1.2, taking address of near auto variable - See @ref GPT_C_REF_3
            */
            /*lint -save -e961*/
            Gpt_LLD_GetTimeElapsed(channel, &tempReturn);
            /*lint -restore*/
        }

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    }
#endif
    return (tempReturn);
}
#endif

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
/* [GPT196]: This function shall be pre compile time configurable On/Off */
/* by the configuration parameter: GPT_TIME_REMAINING_API */
#if (GPT_TIME_REMAINING_API == STD_ON)
FUNC (Gpt_ValueType, GPT_CODE) Gpt_GetTimeRemaining(VAR(Gpt_ChannelType, AUTOMATIC) channel)
{
    VAR(Gpt_ValueType, AUTOMATIC) tempReturn = 0U;

    /* [GPT178]: Detected development errors shall be reported to the */
    /* Det_ReportError service of the Development Error Tracer (DET) */
    /* if the preprocessor switch GPT_DEV_ERROR_DETECT is set */
    /* [GPT204]: If development error detection is enabled for the GPT Driver, */
    /* the following API parameter checking shall be performed according to the */
    /* respective functions (see table below). The error shall be reported to the Development Error Tracer. */
    /* StartTimer - GPT_E_UNINIT - Called prior to initialization */
    /* GPT_E_NOT_STARTED - Called prior to start the timer channel */
    /* GPT_E_NOT_STARTED - Called on a stopped channel */
    /* GPT_E_PARAM_CHANNEL - Channel out of range */
#if (GPT_DEV_ERROR_DETECT == STD_ON)

    /* [GPT223]: If development error detection is enabled and Gpt_GetTimeRemaining is called prior to initializing the
       driver, the development error code GPT_E_UNINIT will be raised. In this case, value 0 is returned. */
    if (NULL_PTR == Gpt_Cfg_Ptr)
    {
        Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                        (uint8)GPT_TIMEREMAINING_ID, (uint8)GPT_E_UNINIT);
    }
    /* [GPT211]: If development error detection is enabled and Gpt_GetTimeElapsed is called with an invalid channel
       parameter, the development error code GPT_E_PARAM_CHANNEL will be raised. In this case, value 0 is returned. */
    else if (channel >= Gpt_Cfg_Ptr->Gpt_Channel_Count)
    {
        Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                        (uint8)GPT_TIMEREMAINING_ID, (uint8)GPT_E_PARAM_CHANNEL);
    }
    /* [GPT101]: Calling Gpt_GetTimeRemaining prior to starting the specified timer channel will cause a development error
       and the error code GPT_E_NOT_STARTED shall be raised. In this case, value 0 is returned . */
    /* [GPT268]: When Calling this function on a stopped timer channel (channel has been initialized and started before),
       value 0 is returned. If development error detection is enabled, GPT_E_NOT_STARTED shall be raised (see section
       7.2) The rationale is to have the same behaviour for a stopped channel like a never started channel. */
    /* [GPT102]: When calling this function on a channel configured for one shot mode, after the timeout period has already
       expired, value 0 is returned. If development error detection is enabled, GPT_E_NOT_STARTED shall be raised in (see
       section 7.2). */
    else
    {
#endif
        if (GPT_STATUS_RUNNING != Gpt_ChannelStatus[channel])
        {
            /*
            @remarks Covers GPT301, GPT303, GPT305, GPT302, GPT303
            @remarks Implements DGPT11010, DGPT11011, DGPT11013
            if DET is enabled, raise GPT_E_NOT_STARTED
            do nothing in order to return 0
            */
#if (GPT_DEV_ERROR_DETECT == STD_ON)
            Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                            (uint8)GPT_TIMEREMAINING_ID, (uint8)GPT_E_NOT_STARTED);
#endif
        }
        else
        {
            /**
            @note  Violates MISRA 2004 Advisory Rule 1.2, taking address of near auto variable - See @ref GPT_C_REF_3
            */
            /*lint -save -e961*/
            Gpt_LLD_GetTimeRemaining(channel, &tempReturn);
            /*lint -restore*/
        }

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    }
#endif
    return (tempReturn);
}
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
FUNC (void, GPT_CODE) Gpt_StartTimer(VAR(Gpt_ChannelType, AUTOMATIC) channel,
                                     VAR(Gpt_ValueType, AUTOMATIC) value)
{
    /* [GPT178]: Detected development errors shall be reported to the */
    /* Det_ReportError service of the Development Error Tracer (DET) */
    /* if the preprocessor switch GPT_DEV_ERROR_DETECT is set */
    /* [GPT204]: If development error detection is enabled for the GPT Driver, */
    /* the following API parameter checking shall be performed according to the */
    /* respective functions (see table below). The error shall be reported to the Development Error Tracer. */
    /* StartTimer - GPT_E_UNINIT - Function called prior to initialization */
    /* GPT_E_BUSY - Function called while ch. is already running */
    /* GPT_E_PARAM_CHANNEL - Channel out of range */
    /* GPT_E_PARAM_VALUE - Passed timer value out of range */
#if (GPT_DEV_ERROR_DETECT == STD_ON)

    VAR(Std_ReturnType, AUTOMATIC) returnCode = (Std_ReturnType)E_OK;

    /* [GPT224]: If development error detection is enabled and Gpt_StartTimer is called prior */
    /* to initializing the driver, the development error code GPT_E_UNINIT will be raised. */
    if (NULL_PTR == Gpt_Cfg_Ptr)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                        (uint8)GPT_STARTTIMER_ID, (uint8)GPT_E_UNINIT);
    }

    /*
    @remarks Covers GPT212

    */
    else if (channel >= Gpt_Cfg_Ptr->Gpt_Channel_Count)
    {
        Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                        (uint8)GPT_STARTTIMER_ID, (uint8)GPT_E_PARAM_CHANNEL);
    }
    /* [GPT084]: Calling Gpt_StartTimer on a channel, which is already started */
    /* and still running, will raise a development error (GPT_E_BUSY) and the */
    /* start service shall be left without any action. */
    else if (GPT_STATUS_RUNNING == Gpt_ChannelStatus[channel])
    {
        Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                        (uint8)GPT_STARTTIMER_ID, (uint8)GPT_E_BUSY);
    }

    else
    {
        /*
        */
        returnCode = Gpt_LLD_CheckStartTimeoutValue(channel, value);

        /*
        @remarks Covers GPT218

        Check timeout value value
        */
        if (GPT_E_PARAM_VALUE == returnCode)
        {
            Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                            (uint8)GPT_STARTTIMER_ID, (uint8)GPT_E_PARAM_VALUE);
        }
        else
        {
#endif

        /* Enter critical section */
            SchM_Enter_Gpt(SCHM_GPT_INSTANCE_0, (Gpt_ChannelType)2*channel);

        /* Call low level start timer */
        Gpt_LLD_StartTimer(channel, value);

        /* Change GPT status */
        Gpt_ChannelStatus[channel] = GPT_STATUS_RUNNING;

        /* Exit critical section */
            SchM_Exit_Gpt(SCHM_GPT_INSTANCE_0, (Gpt_ChannelType)2*channel);

#if (GPT_DEV_ERROR_DETECT == STD_ON)
        }
    }
#endif
}

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
FUNC (void, GPT_CODE) Gpt_StopTimer(VAR(Gpt_ChannelType, AUTOMATIC) channel)
{

    /* [GPT178]: Detected development errors shall be reported to the */
    /* Det_ReportError service of the Development Error Tracer (DET) */
    /* if the preprocessor switch GPT_DEV_ERROR_DETECT is set */
    /* [GPT204]: If development error detection is enabled for the GPT Driver, */
    /* the following API parameter checking shall be performed according to the */
    /* respective functions (see table below). The error shall be reported to the Development Error Tracer. */
    /* StopTimer - GPT_E_UNINIT - Function called prior to initialization */
    /* GPT_E_PARAM_CHANNEL - Channel out of range */

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* [GPT225]: If development error detection is enabled and Gpt_StopTimer is called prior */
    /* to initializing the driver, the development error code GPT_E_UNINIT will be raised. */
    if (NULL_PTR == Gpt_Cfg_Ptr)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                        (uint8)GPT_STOPTIMER_ID, (uint8)GPT_E_UNINIT);
    }
    /* [GPT213]: - If development error detection is enabled and Gpt_StopTimer is */
    /* called with an invalid channel parameter, the development error code */
    /* GPT_E_PARAM_CHANNEL will be raised. */
    else if (channel >= Gpt_Cfg_Ptr->Gpt_Channel_Count)
    {
        Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                        (uint8)GPT_STOPTIMER_ID, (uint8)GPT_E_PARAM_CHANNEL);
    }
    else
    {
#endif
        SchM_Enter_Gpt(SCHM_GPT_INSTANCE_0, (Gpt_ChannelType)2*channel);
        /* Call low level stop timer */
        Gpt_LLD_StopTimer(channel);

        /* Change GPT status */
        Gpt_ChannelStatus[channel] = GPT_STATUS_STOPPED;
        SchM_Exit_Gpt(SCHM_GPT_INSTANCE_0, (Gpt_ChannelType)2*channel);

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    }
#endif
}
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
/* [GPT199]: This function shall be pre compile time configurable On/Off */
/* by the configuration parameter: GPT_ENABLE_DISABLE_NOTIFICATION_API */
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
FUNC (void, GPT_CODE) Gpt_EnableNotification(VAR(Gpt_ChannelType, AUTOMATIC) channel)
{

    /* [GPT178]: Detected development errors shall be reported to the */
    /* Det_ReportError service of the Development Error Tracer (DET) */
    /* if the preprocessor switch GPT_DEV_ERROR_DETECT is set */
    /* [GPT204]: If development error detection is enabled for the GPT Driver, */
    /* the following API parameter checking shall be performed according to the */
    /* respective functions (see table below). The error shall be reported to the Development Error Tracer. */
    /* EnableNotification - GPT_E_UNINIT - Function called prior to initialization */
    /* GPT_E_PARAM_CHANNEL - Channel out of range */
#if (GPT_DEV_ERROR_DETECT == STD_ON)

    /* [GPT226]: If development error detection is enabled and Gpt_EnableNotification is called */
    /* prior to initializing the driver, the development error code GPT_E_UNINIT will be raised. */
    if (NULL_PTR == Gpt_Cfg_Ptr)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                        (uint8)GPT_ENABLENOTIFICATION_ID, (uint8)GPT_E_UNINIT);
    }
    /* [GPT214]: - If development error detection is enabled and Gpt_EnableNotification */
    /* is called with an invalid channel parameter, the development error code */
    /* GPT_E_PARAM_CHANNEL will be raised. */
    else if (channel >= Gpt_Cfg_Ptr->Gpt_Channel_Count)
    {
        Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                        (uint8)GPT_ENABLENOTIFICATION_ID, (uint8)GPT_E_PARAM_CHANNEL);
    }
    else
    {
#endif
        SchM_Enter_Gpt(SCHM_GPT_INSTANCE_0, ((Gpt_ChannelType)2*channel)+(Gpt_ChannelType)1);
        Gpt_LLD_EnableNotification(channel);
        SchM_Exit_Gpt(SCHM_GPT_INSTANCE_0, ((Gpt_ChannelType)2*channel)+(Gpt_ChannelType)1);

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    }
#endif

}
#endif

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
/* [GPT200]: This function shall be pre compile time configurable On/Off */
/* by the configuration parameter: GPT_ENABLE_DISABLE_NOTIFICATION_API */
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
FUNC (void, GPT_CODE) Gpt_DisableNotification(VAR(Gpt_ChannelType, AUTOMATIC) channel)
{
    /* [GPT178]: Detected development errors shall be reported to the */
    /* Det_ReportError service of the Development Error Tracer (DET) */
    /* if the preprocessor switch GPT_DEV_ERROR_DETECT is set */
    /* [GPT204]: If development error detection is enabled for the GPT Driver, */
    /* the following API parameter checking shall be performed according to the */
    /* respective functions (see table below). The error shall be reported to the Development Error Tracer. */
    /* DisableNotification - GPT_E_UNINIT - Function called */
#if (GPT_DEV_ERROR_DETECT == STD_ON)

    /* [GPT227]: If development error detection is enabled and Gpt_DisableNotification is called */
    /* prior to initializing the driver, the development error code GPT_E_UNINIT will be raised. */
    if (NULL_PTR == Gpt_Cfg_Ptr)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                        (uint8)GPT_DISABLENOTIFICATION_ID, (uint8)GPT_E_UNINIT);
    }
    /* [GPT217]: If development error detection is enabled and Gpt_DisableNotification */
    /* is called with an invalid channel parameter, the development error code */
    /* GPT_E_PARAM_CHANNEL will be raised. */
    else if (channel >= Gpt_Cfg_Ptr->Gpt_Channel_Count)
    {
        Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                        (uint8)GPT_DISABLENOTIFICATION_ID, (uint8)GPT_E_PARAM_CHANNEL);
    }
    else
    {
#endif
        SchM_Enter_Gpt(SCHM_GPT_INSTANCE_0, ((Gpt_ChannelType)2*channel)+(Gpt_ChannelType)1);
        Gpt_LLD_DisableNotification(channel);
        SchM_Exit_Gpt(SCHM_GPT_INSTANCE_0, ((Gpt_ChannelType)2*channel)+(Gpt_ChannelType)1);

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    }
#endif
}
#endif

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
/* [GPT201]: This function shall be pre compile time configurable On/Off */
/* by the configuration parameter: GPT_WAKEUP_FUNCTIONALITY _API */
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
FUNC (void, GPT_CODE) Gpt_SetMode(VAR(Gpt_ModeType, AUTOMATIC) mode)
{
    /* [GPT255]: This service is only feasible, if GPT_REPORT_WAKEUP_SOURCE is statically configured available. */
    #if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
    /* [GPT178]: Detected development errors shall be reported to the */
    /* Det_ReportError service of the Development Error Tracer (DET) */
    /* if the preprocessor switch GPT_DEV_ERROR_DETECT is set */
    /* [GPT204]: If development error detection is enabled for the GPT Driver, */
    /* the following API parameter checking shall be performed according to the */
    /* respective functions (see table below). The error shall be reported to the Development Error Tracer. */
#if (GPT_DEV_ERROR_DETECT == STD_ON)

    /* [GPT228]: If development error detection is enabled and Gpt_SetMode is called */
    /* prior to initializing the driver, the development error code GPT_E_UNINIT will be raised. */
    if (NULL_PTR == Gpt_Cfg_Ptr)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                        (uint8)GPT_SETMODE_ID, (uint8)GPT_E_UNINIT);
    }
    /* [GPT231]: - If development error detection is enabled and Gpt_SetMode is called with an */
    /* invalid mode parameter, the development error code GPT_E_PARAM_MODE will be raised. */
    else if ((GPT_MODE_NORMAL != mode) && (GPT_MODE_SLEEP != mode))
    {
        Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                        (uint8)GPT_SETMODE_ID, (uint8)GPT_E_PARAM_MODE);
    }
    else
    {
#endif
        SchM_Enter_Gpt(SCHM_GPT_INSTANCE_0, GPT_EXCLUSIVE_AREA_64);
        if (GPT_MODE_SLEEP == mode)
        {
            /* [GPT153]: In GPT_MODE_SLEEP mode interrupts are only enabled for those */
            /* channels which are configured as wakeup capable and which are not disabled via */
            /* service Gpt_DisableWakeup. All other interrupts are disabled and must not lead */
            /* to an exit from the reduced power mode state (e.g. idle, halt) of the MCU if the */
            /* wakeup timer expires */
            /* [GPT164]: In GPT_MODE_SLEEP, all non-wakeup capable timer channels */
            /* shall be stopped. Only those channels, which can serve as a wakeup */
            /* source are running.  Stop all timer channels that are not wakeup capable */
            Gpt_LLD_SetSleepMode();
        }
        else
        {
            /* [GPT150]: By calling Gpt_SetMode with mode parameter "GPT_MODE_NORMAL", */
            /* the ECU State Manager switches the GPT back to normal operation mode */
            /* [GPT165]: When waking up from sleep mode and the mode is set back to */
            /* GPT_MODE_NORMAL, the timer channels which have been stopped by entering */
            /* the sleep mode are not restarted automatically. */
            Gpt_LLD_SetNormalMode();
        }
        /* Change power mode status */
        Gpt_Current_Mode = mode;
        SchM_Exit_Gpt(SCHM_GPT_INSTANCE_0, GPT_EXCLUSIVE_AREA_64);

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    }
#endif
#endif
}
#endif

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
/* [GPT202]: This function shall be pre compile time configurable On/Off */
/* by the configuration parameter: GPT_WAKEUP_FUNCTIONALITY _API */
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
FUNC (void, GPT_CODE) Gpt_DisableWakeup(VAR(Gpt_ChannelType, AUTOMATIC) channel)
{
    /* [GPT157]: This service is only feasible, if GPT_REPORT_WAKEUP_SOURCE is statically configured available */
    #if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
    /* [GPT178]: Detected development errors shall be reported to the */
    /* Det_ReportError service of the Development Error Tracer (DET) */
    /* if the preprocessor switch GPT_DEV_ERROR_DETECT is set */
    /* [GPT204]: If development error detection is enabled for the GPT Driver, */
    /* the following API parameter checking shall be performed according to the */
    /* respective functions (see table below). The error shall be reported to the Development Error Tracer. */
#if (GPT_DEV_ERROR_DETECT == STD_ON)

    /* [GPT229]: If development error detection is enabled and Gpt_DisableWakeup is called prior */
    /* to initializing the driver, the development error code GPT_E_UNINIT will be raised. */
    if (NULL_PTR == Gpt_Cfg_Ptr)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                        (uint8)GPT_DISABLEWAKEUP_ID, (uint8)GPT_E_UNINIT);
    }
    /* [GPT215]: If development error detection is enabled and Gpt_DisableWakeup */
    /* is called with an invalid channel parameter or on a non-wakeup capable channel, */
    /* the development error code GPT_E_PARAM_CHANNEL will be raised. */
    /*
                    */
/** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_C_REF_4 */
    else if ((channel >= Gpt_Cfg_Ptr->Gpt_Channel_Count) ||
             ((uint8)FALSE == Gpt_Cfg_Ptr->Gpt_ChannelConfigPtr[channel].Gpt_EnableWakeup))
    {
        Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                        (uint8)GPT_DISABLEWAKEUP_ID, (uint8)GPT_E_PARAM_CHANNEL);
    }
    else
    {
#endif
        /* Call low level function */
        Gpt_LLD_DisableWakeup(channel);

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    }
#endif
#endif
}
#endif

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
/* [GPT203]: This function shall be pre compile time configurable On/Off */
/* by the configuration parameter: GPT_WAKEUP_FUNCTIONALITY_API */
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
FUNC (void, GPT_CODE) Gpt_EnableWakeup(VAR(Gpt_ChannelType, AUTOMATIC) channel)
{
/* [GPT158]: This service is only feasible, if GPT_REPORT_WAKEUP_SOURCE is statically configured available */
    #if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
    /* [GPT178]: Detected development errors shall be reported to the */
    /* Det_ReportError service of the Development Error Tracer (DET) */
    /* if the preprocessor switch GPT_DEV_ERROR_DETECT is set */
    /* [GPT204]: If development error detection is enabled for the GPT Driver, */
    /* the following API parameter checking shall be performed according to the */
    /* respective functions (see table below). The error shall be reported to the Development Error Tracer. */
#if (GPT_DEV_ERROR_DETECT == STD_ON)

    /* [GPT230]: If development error detection is enabled and Gpt_EnableWakeup is called */
    /* prior to initializing the driver, the development error code GPT_E_UNINIT will be raised. */
    if (NULL_PTR == Gpt_Cfg_Ptr)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                        (uint8)GPT_ENABLEWAKEUP_ID, (uint8)GPT_E_UNINIT);
    }
    /* [GPT216]: If development error detection is enabled and Gpt_EnableWakeup */
    /* is called with an invalid channel parameter or on a non-wakeup capable channel, */
    /* the development error code GPT_E_PARAM_CHANNEL will be raised. */
    /*
                    */
/** @note  Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used - See @ref GPT_C_REF_4 */
    else if ((channel >= Gpt_Cfg_Ptr->Gpt_Channel_Count) ||
             ((uint8)FALSE == Gpt_Cfg_Ptr->Gpt_ChannelConfigPtr[channel].Gpt_EnableWakeup))
    {
        Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                        (uint8)GPT_ENABLEWAKEUP_ID, (uint8)GPT_E_PARAM_CHANNEL);
    }
    else
    {
#endif
        /* Call low level function */
        Gpt_LLD_EnableWakeup(channel);

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    }
#endif
#endif
}

#endif


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
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
FUNC (void, GPT_CODE) Gpt_Cbk_CheckWakeup(VAR(EcuM_WakeupSourceType, AUTOMATIC) wakeupSource)
{

#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
#if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* [GPT230]: If development error detection is enabled and Gpt_EnableWakeup is called */
    /* prior to initializing the driver, the development error code GPT_E_UNINIT will be raised. */
    if (NULL_PTR == Gpt_Cfg_Ptr)
    {
        /* Call Det_ReportError */
        Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                        (uint8)GPT_CBK_CHECKWAKEUP_ID, (uint8)GPT_E_UNINIT);
    }
    else
    {
#endif

        Gpt_LLD_Cbk_CheckWakeup(wakeupSource);

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    }
#endif
#endif /* GPT_REPORT_WAKEUP_SOURCE */
}
#endif /* GPT_WAKEUP_FUNCTIONALITY_API */


#define GPT_STOP_SEC_CODE
/**
@file  Gpt.c
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref GPT_C_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref GPT_C_REF_2
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/
#ifdef __cplusplus
}
#endif
