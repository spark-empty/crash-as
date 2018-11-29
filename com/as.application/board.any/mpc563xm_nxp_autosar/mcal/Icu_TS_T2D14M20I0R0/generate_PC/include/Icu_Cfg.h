[!CODE!][!//
/**
    @file Icu_Cfg.h
    @version 2.0.0

    @brief   AUTOSAR Icu - contains the configuration data of the ICU driver
    @details Contains the configuration data of the ICU driver

    Project AUTOSAR 3.0 MCAL
    Platform PA
    Peripheral eMIOS200
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

#ifndef ICU_CFG_H
#define ICU_CFG_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

[!NOCODE!][!//
[!LOOP "IcuConfigSet/*/IcuChannel/*"!][!//
    [!VAR "A"="@name"!][!//
    [!VAR "B"="IcuChannelId"!][!//
    [!LOOP "../../../*/IcuChannel/*"!][!//
        [!IF "($A = @name) and ($B != IcuChannelId)"!][!//
            [!ERROR!]Different IcuChannelId is selected for the same IcuChannel name in different IcuConfigSet".
            [!ENDERROR!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!][!//

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@{
@brief   Configuration header file version information
@details The integration of incompatible files shall be avoided.
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define ICU_VENDOR_ID_CFG           43
#define ICU_AR_MAJOR_VERSION_CFG    3
#define ICU_AR_MINOR_VERSION_CFG    0
#define ICU_AR_PATCH_VERSION_CFG    0
#define ICU_SW_MAJOR_VERSION_CFG    2
#define ICU_SW_MINOR_VERSION_CFG    0
#define ICU_SW_PATCH_VERSION_CFG    0
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
@brief Implementation specific.
       Each channel provides a subset of the functionality available in the unified channel,
       at a resolution of 24 bits.
*/
#define EMIOS_COUNTER_MASK              (Icu_ValueType)0x00FFFFFF
/**@}*/

[!IF "IMPLEMENTATION_CONFIG_VARIANT='VariantPreCompile'"!][!//
/**@brief Pre-compile configuration constants */
#define ICU_PRECOMPILE_SUPPORT
[!ENDIF!][!//

/**@brief General Configuration Containers */
/**
@{
@brief Maximum number of ICU channels configured
*/
[!NOCODE!][!//
[!VAR "MaxNoOfCh" = "0"!]
[!LOOP "IcuConfigSet/*"!]
    [!IF "$MaxNoOfCh < IcuMaxChannel"!]
        [!VAR "MaxNoOfCh" = "IcuMaxChannel"!]
    [!ENDIF!]
[!ENDLOOP!]
[!ENDNOCODE!][!//
#define ICU_MAX_CHANNEL               (Icu_ChannelType)[!"num:i($MaxNoOfCh)"!]

/**@}*/
/**
@brief  Switches the Development Error Detection and Notification on or off.
        STD_ON: Enabled. STD_OFF: Disabled.
@remark Covers ICU232
*/
#define ICU_DEV_ERROR_DETECT            ([!IF "IcuGeneral/IcuDevErrorDetect"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

/**
@brief  Switch for enabling Wakeup source reporting.
        STD_ON: Report Wakeup source. STD_OFF: Do not report Wakeup source.
@remark Covers ICU233
*/
#define ICU_REPORT_WAKEUP_SOURCE        ([!IF "IcuGeneral/IcuReportWakeupSource"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

/**
@{
@brief Configuration of Optional API's
*/
/**
@brief  Adds / removes the service Icu_GetVersionInfo() from the code.
        STD_ON: Icu_GetVersionInfo() can be used. STD_OFF: Icu_GetVersionInfo() can not be used.
@remark Covers ICU240
*/
#define ICU_GET_VERSION_INFO_API        ([!IF "IcuOptionalApis/IcuGetVersionInfoApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

/**
@brief  Adds / removes the service Icu_DeInit() from the code.
        STD_ON: Icu_DeInit() can be used. STD_OFF: Icu_DeInit() can not be used.
@remark Covers ICU234
*/
#define ICU_DE_INIT_API                 ([!IF "IcuOptionalApis/IcuDeInitApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

/**
@brief  Adds / removes the service Icu_SetMode() from the code.
        STD_ON: Icu_SetMode() can be used. STD_OFF: Icu_SetMode() can not be used.
@remark Covers ICU241
*/
#define ICU_SET_MODE_API                ([!IF "IcuOptionalApis/IcuSetModeApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

/**
@brief  Adds / removes the service Icu_DisableWakeup() from the code.
        STD_ON: Icu_DisableWakeup() can be used. STD_OFF: Icu_DisableWakeup() can not be used.
@remark Covers ICU235
*/
#define ICU_DISABLE_WAKEUP_API          ([!IF "IcuOptionalApis/IcuDisableWakeupApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

/**
@brief  Adds / removes the service Icu_EnableWakeup() from the code.
        STD_ON: Icu_EnableWakeup() can be used. STD_OFF: Icu_EnableWakeup() can not be used.
@remark Covers ICU236
*/
#define ICU_ENABLE_WAKEUP_API           ([!IF "IcuOptionalApis/IcuEnableWakeupApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

/**
@brief  Adds / removes all services related to the timestamping functionality as listed
        below from the code: Icu_StartTimestamp(), Icu_StopTimestamp(), Icu_GetTimestampIndex().
        STD_ON: The services listed above can be used. STD_OFF: The services listed above can not
       be used.
@remark Covers ICU123
*/
#define ICU_TIMESTAMP_API               ([!IF "IcuOptionalApis/IcuTimestampApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

/**
@brief  Adds / removes all services related to the edge counting functionality as listed below,
        from the code: Icu_ResetEdgeCount(), Icu_EnableEdgeCount(), Icu_DisableEdgeCount(),
        Icu_GetEdgeNumbers().
        STD_ON: The services listed above can be used. STD_OFF: The services listed above can not
        be used.
@remark Covers ICU124
*/
#define ICU_EDGE_COUNT_API              ([!IF "IcuOptionalApis/IcuEdgeCountApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

/**
@brief  Adds / removes the service Icu_GetTimeElapsed() from the code.
        STD_ON: Icu_GetTimeElapsed() can be used. STD_OFF: Icu_GetTimeElapsed() can not be used.
@remark Covers ICU239
*/
#define ICU_GET_TIME_ELAPSED_API        ([!IF "IcuOptionalApis/IcuGetTimeElapsedApi"!][!IF "IcuOptionalApis/IcuSignalMeasurementApi"!]STD_ON[!ELSE!][!ERROR "If IcuSignalMeasurementApi == OFF this switch is shall also be set to OFF"!][!ENDIF!][!ELSE!]STD_OFF[!ENDIF!])

/**
@brief  Adds / removes the service Icu_GetDutyCycleValues() from the code.
        STD_ON: Icu_GetDutyCycleValues() can be used. STD_OFF: Icu_GetDutyCycleValues() can not be
        used.
@remark Covers ICU237
*/
#define ICU_GET_DUTY_CYCLE_VALUES_API   ([!IF "IcuOptionalApis/IcuGetDutyCycleValuesApi"!][!IF "IcuOptionalApis/IcuSignalMeasurementApi"!]STD_ON[!ELSE!][!ERROR "If IcuSignalMeasurementApi == OFF this switch is shall also be set to OFF"!][!ENDIF!][!ELSE!]STD_OFF[!ENDIF!])

/**
@brief  Adds / removes the service Icu_GetInputState() from the code.
        STD_ON: Icu_GetInputState() can be used. STD_OFF: Icu_GetInputState() can not be used.
@remark Covers ICU238
*/
#define ICU_GET_INPUT_STATE_API         ([!IF "IcuOptionalApis/IcuGetInputStateApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

/**
@brief  Adds / removes the services Icu_StartSignalMeasurement() and Icu_StopSignalMeasurement()
        from the code.
        STD_ON: Icu_StartSignalMeasurement() and Icu_StopSignalMeasurement() can be used.
        STD_OFF: Icu_StartSignalMeasurement() and Icu_StopSignalMeasurement() can not be used.
@remark Covers ICU242
*/
#define ICU_SIGNAL_MEASUREMENT_API      ([!IF "IcuOptionalApis/IcuSignalMeasurementApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

/**
@brief  Implementation specific parameter
        Adds/Removes the code related to overflow notification
        STD_ON: Overflow notification function will be called if overflow occurs
        STD_OFF: Overflow notification function will not be called though overflow occurs
*/
#define ICU_OVERFLOW_NOTIFICATION_API   ([!IF "IcuOptionalApis/IcuOverflowNotificationApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

/**
@brief  Adds / removes the service Icu_SetClockMode() from the code.
        STD_ON: Icu_SetClockMode() can be used.
        STD_OFF: Icu_SetClockMode() can not be used.
@remarks Covers PR-MCAL-3195
*/
#define ICU_DUAL_CLOCK_MODE             ([!IF "IcuNonAUTOSAR/IcuEnableDualClockMode"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
/**@}*/

[!IF "IMPLEMENTATION_CONFIG_VARIANT='VariantPostBuild'"!][!//
/**@brief   External declaration of the ICU configuration structure */
#define ICU_CFG_EXTERN_DECLARATIONS \
[!NOCODE!][!VAR "var_count1"="num:i(count(IcuConfigSet/*))"!][!VAR "w"="0"!][!ENDNOCODE!][!//
[!LOOP "IcuConfigSet/*"!][!VAR "w"="$w + 1"!][!//
extern CONST(Icu_ConfigType, ICU_CONST) [!"@name"!];[!IF "$w < $var_count1"!] \[!ENDIF!]
[!ENDLOOP!][!//
[!ENDIF!][!//

/**
@brief Icu Channel symbolic names
@details Get All Symbolic Names from configuration tool
@remark Covers ICU221
@{
*/
[!NOCODE!][!//
[!VAR "OuterLoopCounter" = "0"!][!//
[!VAR "InnerLoopCounter" = "0"!][!//
[!LOOP "IcuConfigSet/*/IcuChannel/*"!][!//
    [!VAR "OuterLoopCounter" = "$OuterLoopCounter + 1"!][!//
    [!VAR "InnerLoopCounter" = "0"!][!//
    [!VAR "Matchcounter" = "0"!][!//
    [!VAR "Name" = "node:name(.)"!][!//
    [!LOOP "../../../*/IcuChannel/*"!][!//
        [!VAR "InnerLoopCounter" = "$InnerLoopCounter + 1"!][!//
        [!IF "$OuterLoopCounter >= $InnerLoopCounter"!][!//
            [!IF "($Name = node:name(.))"!][!//
                [!VAR "Matchcounter" = "$Matchcounter + 1"!][!//
            [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "$Matchcounter = 1"!][!/*
        */!][!CODE!][!/*
            */!]#define [!"node:name(.)"!]      (Icu_ChannelType)[!"IcuChannelId"!]
[!/*    */!][!ENDCODE!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!][!//
/**@}*/

/**
@brief ISR's configured for Icu channels
@details Macros for channels used in ISR
@{
*/
[!NOCODE!][!//
[!VAR "OuterLoopCounter" = "0"!][!//
[!VAR "InnerLoopCounter" = "0"!][!//
[!LOOP "IcuConfigSet/*/IcuChannel/*"!][!//
    [!VAR "OuterLoopCounter" = "$OuterLoopCounter + 1"!]
    [!VAR "InnerLoopCounter" = "0"!]
    [!VAR "Matchcounter" = "0"!]
    [!VAR "Name" = "node:name(.)"!]
    [!LOOP "../../../*/IcuChannel/*"!]
        [!VAR "InnerLoopCounter" = "$InnerLoopCounter + 1"!]
        [!IF "$OuterLoopCounter >= $InnerLoopCounter"!]
            [!IF "($Name = node:name(.))"!]
                [!VAR "Matchcounter" = "$Matchcounter + 1"!]
            [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "$Matchcounter = 1"!][!/*
        */!][!CODE!][!/*
            */!]#define ICU_[!"IcuHwChannel"!]_ISR_USED
[!/*    */!][!ENDCODE!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!][!//
/**@}*/


[!NOCODE!]
[!VAR "Matchcounter" = "0"!][!//
[!LOOP "IcuConfigSet/*/IcuChannel/*"!]
    [!IF "IcuMeasurementMode ='ICU_MODE_SIGNAL_MEASUREMENT'"!]
        [!IF "not(contains(ecu:list(concat('Icu.ChannelType.', IcuHwChannel)), 'IPM')) or
              not(contains(ecu:list(concat('Icu.ChannelType.', IcuHwChannel)), 'IPWM'))"!]
            [!VAR "Matchcounter" = "1"!]
            [!BREAK!]
        [!ENDIF!]
    [!ENDIF!]
[!ENDLOOP!]

[!IF "$Matchcounter = 1"!]
[!CODE!]
/**
@brief Signal measurement mode
@details define SAIC mode if any channels not supporting IPWM or IPM mode is configured
@{
*/
#define SIGNAL_MEASUREMENT_USES_SAIC_MODE
/**@}*/
[!ENDCODE!][!//
[!ENDIF!][!//
[!ENDNOCODE!]


/*==================================================================================================
                                             ENUMS
==================================================================================================*/


/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
@brief Implementation specific. This type shall be chosen in order to have the most efficient
       implementation on a specific microcontroller platform.
       Range: 0  to width of the timer register.
       Description: Width of the buffer for timestamp ticks and measured elapsed timeticks
*/
typedef uint32 Icu_TimerRegisterWidthType;

/**
@brief Implementation specific. This type shall be chosen in order to have the most efficient
       implementation on a specific microcontroller platform.
       Description: Type, to abstract the return value of the service Icu_GetTimestampIndex().
*/
typedef uint32 Icu_HwSpecificIndexType;

/**
@brief Implementation specific. This type shall be chosen in order to have the most efficient
       implementation on a specific microcontroller platform.
       Description: Type, to abstract the return value of the service Icu_GetEdgeNumbers().
*/
typedef uint32 Icu_HwSpecificEdgeNumberType;


/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif
/* ICU_CFG_H */
#endif    
[!ENDCODE!]
