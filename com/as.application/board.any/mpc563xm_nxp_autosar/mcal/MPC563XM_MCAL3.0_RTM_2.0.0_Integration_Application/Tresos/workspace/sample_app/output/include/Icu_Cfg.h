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


/**@brief General Configuration Containers */
/**
@{
@brief Maximum number of ICU channels configured
*/
#define ICU_MAX_CHANNEL               (Icu_ChannelType)1

/**@}*/
/**
@brief  Switches the Development Error Detection and Notification on or off.
        STD_ON: Enabled. STD_OFF: Disabled.
@remark Covers ICU232
*/
#define ICU_DEV_ERROR_DETECT            (STD_ON)

/**
@brief  Switch for enabling Wakeup source reporting.
        STD_ON: Report Wakeup source. STD_OFF: Do not report Wakeup source.
@remark Covers ICU233
*/
#define ICU_REPORT_WAKEUP_SOURCE        (STD_ON)

/**
@{
@brief Configuration of Optional API's
*/
/**
@brief  Adds / removes the service Icu_GetVersionInfo() from the code.
        STD_ON: Icu_GetVersionInfo() can be used. STD_OFF: Icu_GetVersionInfo() can not be used.
@remark Covers ICU240
*/
#define ICU_GET_VERSION_INFO_API        (STD_ON)

/**
@brief  Adds / removes the service Icu_DeInit() from the code.
        STD_ON: Icu_DeInit() can be used. STD_OFF: Icu_DeInit() can not be used.
@remark Covers ICU234
*/
#define ICU_DE_INIT_API                 (STD_ON)

/**
@brief  Adds / removes the service Icu_SetMode() from the code.
        STD_ON: Icu_SetMode() can be used. STD_OFF: Icu_SetMode() can not be used.
@remark Covers ICU241
*/
#define ICU_SET_MODE_API                (STD_ON)

/**
@brief  Adds / removes the service Icu_DisableWakeup() from the code.
        STD_ON: Icu_DisableWakeup() can be used. STD_OFF: Icu_DisableWakeup() can not be used.
@remark Covers ICU235
*/
#define ICU_DISABLE_WAKEUP_API          (STD_ON)

/**
@brief  Adds / removes the service Icu_EnableWakeup() from the code.
        STD_ON: Icu_EnableWakeup() can be used. STD_OFF: Icu_EnableWakeup() can not be used.
@remark Covers ICU236
*/
#define ICU_ENABLE_WAKEUP_API           (STD_ON)

/**
@brief  Adds / removes all services related to the timestamping functionality as listed
        below from the code: Icu_StartTimestamp(), Icu_StopTimestamp(), Icu_GetTimestampIndex().
        STD_ON: The services listed above can be used. STD_OFF: The services listed above can not
       be used.
@remark Covers ICU123
*/
#define ICU_TIMESTAMP_API               (STD_ON)

/**
@brief  Adds / removes all services related to the edge counting functionality as listed below,
        from the code: Icu_ResetEdgeCount(), Icu_EnableEdgeCount(), Icu_DisableEdgeCount(),
        Icu_GetEdgeNumbers().
        STD_ON: The services listed above can be used. STD_OFF: The services listed above can not
        be used.
@remark Covers ICU124
*/
#define ICU_EDGE_COUNT_API              (STD_ON)

/**
@brief  Adds / removes the service Icu_GetTimeElapsed() from the code.
        STD_ON: Icu_GetTimeElapsed() can be used. STD_OFF: Icu_GetTimeElapsed() can not be used.
@remark Covers ICU239
*/
#define ICU_GET_TIME_ELAPSED_API        (STD_ON)

/**
@brief  Adds / removes the service Icu_GetDutyCycleValues() from the code.
        STD_ON: Icu_GetDutyCycleValues() can be used. STD_OFF: Icu_GetDutyCycleValues() can not be
        used.
@remark Covers ICU237
*/
#define ICU_GET_DUTY_CYCLE_VALUES_API   (STD_ON)

/**
@brief  Adds / removes the service Icu_GetInputState() from the code.
        STD_ON: Icu_GetInputState() can be used. STD_OFF: Icu_GetInputState() can not be used.
@remark Covers ICU238
*/
#define ICU_GET_INPUT_STATE_API         (STD_ON)

/**
@brief  Adds / removes the services Icu_StartSignalMeasurement() and Icu_StopSignalMeasurement()
        from the code.
        STD_ON: Icu_StartSignalMeasurement() and Icu_StopSignalMeasurement() can be used.
        STD_OFF: Icu_StartSignalMeasurement() and Icu_StopSignalMeasurement() can not be used.
@remark Covers ICU242
*/
#define ICU_SIGNAL_MEASUREMENT_API      (STD_ON)

/**
@brief  Implementation specific parameter
        Adds/Removes the code related to overflow notification
        STD_ON: Overflow notification function will be called if overflow occurs
        STD_OFF: Overflow notification function will not be called though overflow occurs
*/
#define ICU_OVERFLOW_NOTIFICATION_API   (STD_OFF)

/**
@brief  Adds / removes the service Icu_SetClockMode() from the code.
        STD_ON: Icu_SetClockMode() can be used.
        STD_OFF: Icu_SetClockMode() can not be used.
@remarks Covers PR-MCAL-3195
*/
#define ICU_DUAL_CLOCK_MODE             (STD_OFF)
/**@}*/

/**@brief   External declaration of the ICU configuration structure */
#define ICU_CFG_EXTERN_DECLARATIONS \
extern CONST(Icu_ConfigType, ICU_CONST) IcuConfigSet_0;

/**
@brief Icu Channel symbolic names
@details Get All Symbolic Names from configuration tool
@remark Covers ICU221
@{
*/
#define Pwm_measure      (Icu_ChannelType)0
/**@}*/

/**
@brief ISR's configured for Icu channels
@details Macros for channels used in ISR
@{
*/
#define ICU_EMIOS_0_CH_8_ISR_USED
/**@}*/





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

