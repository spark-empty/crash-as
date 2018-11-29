/**
    @file    Icu.h
    @version 2.0.0

    @brief   AUTOSAR Icu - ICU driver header file.
    @details ICU driver header file, containing the Autosar API specification and other variables
             and functions that are exported by the ICU driver.

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

#ifndef ICU_H
#define ICU_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
@file    Icu.h
@remarks Implements DICU02000
*/

/**
@page misra_violations MISRA-C:2004 violations

@section Icu_h_1
Violates MISRA-C:2004 Advisory Rule 19.15 Precautions shall be taken in order to prevent the
contents of a header file being included twice
This is not a violation since all header files are protected against multiple inclusions
*/


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/**
 @file Icu.h
 @remarks Covers ICU190
*/
/**
@file  Icu.h
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref Icu_h_1 */
/*lint -save -e537*/
#include "Std_Types.h"
#include "Icu_Cfg.h"
#include "Reg_Macros.h"
#if (ICU_REPORT_WAKEUP_SOURCE == STD_ON)
#include "EcuM_Cbk.h"
/* ICU_REPORT_WAKEUP_SOURCE */
#endif  
/*lint -restore*/


/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@{
@brief   Header file version information
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define ICU_VENDOR_ID           43
#define ICU_MODULE_ID           122

#define ICU_AR_MAJOR_VERSION    3
#define ICU_AR_MINOR_VERSION    0
#define ICU_AR_PATCH_VERSION    1
#define ICU_SW_MAJOR_VERSION    2
#define ICU_SW_MINOR_VERSION    0
#define ICU_SW_PATCH_VERSION    0
/**@}*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#ifdef CHECK_AUTOSAR_VERSION
    /**
     @file Icu.h
     @remarks Covers ICU005
    */
    /* Check if header file and Std_Types.h file are of the same Autosar version */
    #if ((ICU_AR_MAJOR_VERSION != STD_TYPES_AR_MAJOR_VERSION) || \
         (ICU_AR_MINOR_VERSION != STD_TYPES_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Icu.h and Std_Types.h are different"
    #endif
#endif

/* Check if source file and ICU configuration header file are of the same vendor */
#if (ICU_VENDOR_ID != ICU_VENDOR_ID_CFG)
    #error "Icu.h and ICU_Cfg.h have different vendor IDs"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if header file and ICU configuration header file are of the same Autosar version */
    #if ((ICU_AR_MAJOR_VERSION != ICU_AR_MAJOR_VERSION_CFG) || \
         (ICU_AR_MINOR_VERSION != ICU_AR_MINOR_VERSION_CFG) || \
         (ICU_AR_PATCH_VERSION != ICU_AR_PATCH_VERSION_CFG))
    #error "AutoSar Version Numbers of Icu.h and ICU_Cfg.h are different"
    #endif
#endif
/* Check if header file and ICU configuration header file are of the same software version */
#if ((ICU_SW_MAJOR_VERSION != ICU_SW_MAJOR_VERSION_CFG) || \
     (ICU_SW_MINOR_VERSION != ICU_SW_MINOR_VERSION_CFG) || \
     (ICU_SW_PATCH_VERSION != ICU_SW_PATCH_VERSION_CFG))
#error "Software Version Numbers of Icu.h and ICU_Cfg.h are different"
#endif

#if (ICU_REPORT_WAKEUP_SOURCE == STD_ON)
    #ifdef CHECK_AUTOSAR_VERSION
        /* Check if header file and EcuM_Cbk.h file are of the same Autosar version */
        #if ((ICU_AR_MAJOR_VERSION != ECUM_CBK_AR_MAJOR_VERSION) || \
             (ICU_AR_MINOR_VERSION != ECUM_CBK_AR_MINOR_VERSION))
        #error "AutoSar Version Numbers of Icu.h and EcuM_Cbk.h are different"
        #endif
    #endif
/* ICU_REPORT_WAKEUP_SOURCE */
#endif  



/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/


/**
@brief   API Icu_Init service called with wrong parameter
@remarks Covers     ICU001, ICU118
*/
#define ICU_E_PARAM_CONFIG              0x0AU

/**
@brief   API service used with an invalid channel identifier or channel was not configured for
         the functionality of the calling API
@remarks Covers     ICU001, ICU118
*/
#define ICU_E_PARAM_CHANNEL             0x0BU

/**
@brief   API service used with an invalid or not feasible activation
@remarks Covers     ICU001, ICU118
*/
#define ICU_E_PARAM_ACTIVATION          0x0CU

/**
@brief   API service used with an invalid application-buffer pointer
@remarks Covers     ICU001, ICU118
*/
#define ICU_E_PARAM_BUFFER_PTR          0x0DU

/**
@brief   API service used with an invalid buffer size
@remarks Covers     ICU001, ICU118
*/
#define ICU_E_PARAM_BUFFER_SIZE         0x0EU

/**
@brief   API service Icu_SetMode used with an invalid mode
@remarks Covers     ICU001, ICU118
*/
#define ICU_E_PARAM_MODE                0x0FU

/**
@brief   API service used without module initialization
@remarks Covers     ICU001, ICU118
*/
#define ICU_E_UNINIT                    0x14U

/**
@brief   API service Icu_StopTimestamp called on a channel which was not
         started or already stopped
@remarks Covers     ICU001, ICU118
*/
#define ICU_E_NOT_STARTED               0x15U

/**
@brief   API service Icu_SetMode is called while a running operation
@remarks Covers     ICU001, ICU118
*/
#define ICU_E_BUSY_OPERATION            0x16U

/**
@brief   API Icu_Init service called when the ICU driver and the Hardware
         are already initialized
@remarks Covers     ICU001, ICU118
*/
#define ICU_E_ALREADY_INITIALIZED       0x17U

/**
@brief   API Icu_GetEdgeNumbers service called when the Counter rolls over
@remarks Covers     ICU004, ICU118
*/
#define ICU_E_EDGECOUNTING_OVERFLOW     0x18U

/**
@brief   API Icu_GetTimestampIndex service called when the Time stamp count overflows
@remarks Covers     ICU004, ICU118
*/
#define ICU_E_TIMESTAMP_OVERFLOW        0x19U

/**
@brief   API Icu_GetTimeElapsed service called when the Time elapsed overflows
@remarks Covers     ICU004, ICU118
*/
#define ICU_E_MEASUREMENT_OVERFLOW      0x1AU




/**
@brief API service ID for Icu_Init function
@details Parameters used when raising an error/exception
*/
#define ICU_INIT_ID                     0x00U

/**
@brief API service ID for Icu_DeInit function
@details Parameters used when raising an error/exception
*/
#define ICU_DEINIT_ID                   0x01U

/**
@brief API service ID for Icu_SetMode function
@details Parameters used when raising an error/exception
*/
#define ICU_SETMODE_ID                  0x02U

/**
@brief API service ID for Icu_DisableWakeup function
@details Parameters used when raising an error/exception
*/
#define ICU_DISABLEWAKEUP_ID            0x03U

/**
@brief API service ID for Icu_EnableWakeup function
@details Parameters used when raising an error/exception
*/
#define ICU_ENABLEWAKEUP_ID             0x04U

/**
@brief API service ID for Icu_SetActivationCondition function
@details Parameters used when raising an error/exception
*/
#define ICU_SETACTIVATIONCONDITION_ID   0x05U

/**
@brief API service ID for Icu_DisableNotification function
@details Parameters used when raising an error/exception
*/
#define ICU_DISABLENOTIFICATION_ID      0x06U

/**
@brief API service ID for Icu_EnableNotification function
@details Parameters used when raising an error/exception
*/
#define ICU_ENABLENOTIFICATION_ID       0x07U

/**
@brief API service ID for Icu_GetInputState function
@details Parameters used when raising an error/exception
*/
#define ICU_GETINPUTSTATE_ID            0x08U

/**
@brief API service ID for Icu_StartTimestamp function
@details Parameters used when raising an error/exception
*/
#define ICU_STARTTIMESTAMP_ID           0x09U

/**
@brief API service ID for Icu_StopTimestamp function
@details Parameters used when raising an error/exception
*/
#define ICU_STOPTIMESTAMP_ID            0x0AU

/**
@brief API service ID for Icu_GetTimestampIndex function
@details Parameters used when raising an error/exception
*/
#define ICU_GETTIMESTAMPINDEX_ID        0x0BU

/**
@brief API service ID for Icu_ResetEdgeCount function
@details Parameters used when raising an error/exception
*/
#define ICU_RESETEDGECOUNT_ID           0x0CU

/**
@brief API service ID for Icu_EnableEdgeCount function
@details Parameters used when raising an error/exception
*/
#define ICU_ENABLEEDGECOUNT_ID          0x0DU

/**
@brief API service ID for Icu_DisableEdgeCount function
@details Parameters used when raising an error/exception
*/
#define ICU_DISABLEEDGECOUNT_ID         0x0EU

/**
@brief API service ID for Icu_GetEdgeNumbers function
@details Parameters used when raising an error/exception
*/
#define ICU_GETEDGENUMBERS_ID           0x0FU

/**
@brief API service ID for Icu_GetTimeElapsed function
@details Parameters used when raising an error/exception
*/
#define ICU_GETTIMEELAPSED_ID           0x10U

/**
@brief API service ID for Icu_GetDutyCycleValues function
@details Parameters used when raising an error/exception
*/
#define ICU_GETDUTYCYCLEVALUES_ID       0x11U

/**
@brief API service ID for Icu_GetVersionInfo function
@details Parameters used when raising an error/exception
*/
#define ICU_GETVERSIONINFO_ID           0x12U

/**
@brief API service ID for Icu_StartSignalMeasurement function
@details Parameters used when raising an error/exception
*/
#define ICU_STARTSIGNALMEASUREMENT_ID   0x13U

/**
@brief API service ID for Icu_StopSignalMeasurement function
@details Parameters used when raising an error/exception
*/
#define ICU_STOPSIGNALMEASUREMENT_ID    0x14U




/*================================================================================================*/
/**
@typedef   Icu_ChannelType
           This gives the numeric ID (hardware channel number) of an ICU channel
*/
/*================================================================================================*/
typedef uint8                           Icu_ChannelType;
/*================================================================================================*/
/**
@typedef   Icu_ParamType
           Icu_ParamType is defined as a uint32.
           The Icu_ParamValue contains combined bit fields for initialization options,
           for different registers.
*/
/*================================================================================================*/
typedef uint32                          Icu_ParamType;
/*================================================================================================*/
/**
@typedef   Icu_ValueType
           Type for saving the timer register width value
*/
/*================================================================================================*/
typedef Icu_TimerRegisterWidthType      Icu_ValueType;
/*================================================================================================*/
/**
@typedef   Icu_IndexType
           Type for saving the ICU Hardware specific index
*/
/*================================================================================================*/
typedef Icu_HwSpecificIndexType         Icu_IndexType;
/*================================================================================================*/
/**
@typedef   Icu_EdgeNumberType
           Type for saving hardware specific edge number
*/
/*================================================================================================*/
typedef Icu_HwSpecificEdgeNumberType    Icu_EdgeNumberType;
/*================================================================================================*/
/**
@typedef   Icu_WakeupValue
           Type for saving the Wakeup value
*/
/*================================================================================================*/
typedef uint32                          Icu_WakeupValue;
/*================================================================================================*/
/**
@typedef   Icu_MeasurementSubModeType
           Type for saving the ICU measurement submode type
*/
/*================================================================================================*/
typedef uint8                           Icu_MeasurementSubModeType;

/* The notification functions shall have no parameters and no return value. */
typedef void (*Icu_NotifyType)(void);

#ifdef ICU_CUSTOM_NOTIFICATION_API
/* Notification handler for custom purposes */
typedef void (*Icu_CustomNotifyType)(uint16);
/* ICU_CUSTOM_NOTIFICATION_API */
#endif  


/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/**
@enum   Icu_ModeType
        Allow enabling / disabling of all interrupts which are not required for the ECU wakeup.
@remarks Covers ICU190
@remarks Implements DICU50001
*/
typedef enum
{
    /** ICU_MODE_NORMAL = Normal operation, all used interrupts are enabled according to
        the notification requests. */
    ICU_MODE_NORMAL = 0U,
    /** ICU_MODE_SLEEP = Reduced power operation. In sleep mode only those notifications
        are available which are configured as wakeup capable. */
    ICU_MODE_SLEEP
} Icu_ModeType;

/**
@enum   Icu_InputStateType
        Input state of an ICU channel.
@remarks Covers ICU190
@remarks Implements DICU50002
*/
typedef enum
{
    /** ICU_ACTIVE = An activation edge has been detected */
    ICU_ACTIVE = 0U,
    /** ICU_IDLE = No activation edge has been detected since the last call
        of Icu_GetInputState() or Icu_Init(). */
    ICU_IDLE
} Icu_InputStateType;


/**
@enum   Icu_MeasurementModeType
        Definition of the measurement mode type.
@remarks Covers ICU039
@remarks Implements DICU50004
*/
typedef enum
{
    /** ICU_MODE_SIGNAL_EDGE_DETECT = Mode for detecting edges */
    ICU_MODE_SIGNAL_EDGE_DETECT = 0U,
    /** ICU_MODE_SIGNAL_MEASUREMENT = Mode for measuring different times between various
        configurable edges */
    ICU_MODE_SIGNAL_MEASUREMENT,
    /** ICU_MODE_TIMESTAMP = Mode for capturing timer values on configurable edges */
    ICU_MODE_TIMESTAMP,
    /** ICU_MODE_EDGE_COUNTER = Mode for counting edges on configurable edges */
    ICU_MODE_EDGE_COUNTER
} Icu_MeasurementModeType;

/**
@enum   Icu_SignalMeasurementPropertyType
        Definition of the measurement property type.
@remarks Covers ICU039
@remarks Implements DICU50005
*/
typedef enum
{
    /** ICU_LOW_TIME = The channel is configured for reading the elapsed Signal Low Time */
    ICU_LOW_TIME = 0U,
    /** ICU_HIGH_TIME = The channel is configured for reading the elapsed Signal High Time */
    ICU_HIGH_TIME,
    /** ICU_PERIOD_TIME = The channel is configured for reading the elapsed Signal Period Time */
    ICU_PERIOD_TIME,
    /** ICU_DUTY_CYCLE = The channel is configured to read values which are needed for calculating
        the duty cycle (coherent Active and Period Time). */
    ICU_DUTY_CYCLE
} Icu_SignalMeasurementPropertyType;


/**
@enum   Icu_TimestampBufferType
        Definition of the timestamp measurement property type.
@remarks Covers ICU039
@remarks Implements DICU50006
*/
typedef enum
{
    /** ICU_LINEAR_BUFFER = The buffer will just be filled once */
    ICU_LINEAR_BUFFER = 0U,
    /** ICU_CIRCULAR_BUFFER = After reaching the end of the buffer, the driver restarts at the
        beginning of the buffer */
    ICU_CIRCULAR_BUFFER
} Icu_TimestampBufferType;


/**
@enum   Icu_ActivationType
        Definition of the type of activation of an ICU channel.
@remarks Covers ICU039
@remarks Implements DICU50003
*/
typedef enum
{
    /** ICU_FALLING_EDGE = An appropriate action shall be executed when a falling edge
        occurs on the ICU input signal. */
    ICU_FALLING_EDGE = 0x0U,
    /** ICU_RISING_EDGE = An appropriate action shall be executed when a rising edge
        occurs on the ICU input signal. */
    ICU_RISING_EDGE  = 0x1U,
    /** ICU_BOTH_EDGES = An appropriate action shall be executed when either a rising
        or falling edge occur on the ICU input signal. */
    ICU_BOTH_EDGES   = 0x2U
} Icu_ActivationType;


/**
@enum   Icu_WakeupCapableType
        Definition of the type of wake up capability of an ICU channel.
@remarks Covers ICU038
@remarks Implements DICU50007
*/
typedef enum
{
    /** ICU_WAKEUP_NOTCAPABLE = Channel is not wakeup capable */
    ICU_WAKEUP_NOTCAPABLE = 0x0U,
    /** ICU_WAKEUP_CAPABLE = Channel is wakeup capable. */
    ICU_WAKEUP_CAPABLE    = 0x1U
} Icu_WakeupCapableType;

/**
@brief  Definition of bit mask to isolate the wake up capability  bitfield
 */
#define ICU_WAKEUP_MASK         (uint32)BIT31
/**
@brief  Definition wake up capability bitfield position
 */
#define ICU_WAKEUP_SHIFT        (uint32)31U

/**
@brief  Definition of bit mask to isolate the configured edge activation type
 */
#define ICU_EDGE_PARAM_MASK     (uint32)(BIT30|BIT29)
/**
@brief  Definition edge activation type bitfield position
 */
#define ICU_EDGE_PARAM_SHIFT    (uint32)29U


#ifdef ICU_CUSTOM_NOTIFICATION_API
/**
@brief Definition of Custom Notification Handler Enabled bitfield
 */
#define ICU_CUSTOM_NOTIFICATION_ENABLED         BIT0
/**
@brief Definition of bit mask to isolate the Custom Notification Handler Enabled bitfield
 */
#define ICU_CUSTOM_NOTIFICATION_ENABLED_MASK    (uint32)BIT28
/**
@brief  Definition of Custom Notification Handler Enabled bitfield position
 */
#define ICU_CUSTOM_NOTIFICATION_ENABLED_SHIFT   (uint32)28U
/* ICU_CUSTOM_NOTIFICATION_API */
#endif  


/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/**
@struct Icu_DutyCycleType
        Structure that contains ICU Duty cycle parameters.
        It contains contain the values, needed for calculating duty cycles i.e Period time value and
        Active time value.
@remarks Covers ICU039
@remarks Implements DICU50201
*/
typedef struct
{
    /**
    @brief Low or High time value
    */
    Icu_ValueType ActiveTime;
    /**
    @brief Period time value
    */
    Icu_ValueType PeriodTime;
} Icu_DutyCycleType;

/**
@struct Icu_ChannelConfigType
        Structure that contains ICU channel configuration.
        It contains the information like Icu Channel Mode, Channel Notification function,
        Overflow Notification function.

@remarks Implements DICU50202
*/
typedef struct
{
    /**
    @brief Configuration parameters of eMIOS registers
    */
    Icu_ParamType Icu_ParamValue;
    /**
    @brief Icu Measurement mode type i.e EDGE_DETECT, TIME_STAMP, SIGNAL_MEASUREMENT or
    EDGE_COUNTER
    */
    Icu_MeasurementModeType Icu_Channel_Mode;
    /**
    @brief Icu Channel Property type i.e CIRCULAR_BUFFER or LINEAR_BUFFER for TIME_STAMP,
    DUTY_CYCLE, HIGH_TIME, LOW_TIME or PERIOD_TIME for SIGNAL_MEASUREMENT and RISING_EDGE,
    FALLING_EDGE or BOTH_EDGES for EDGE_COUNTER.
    */
    Icu_MeasurementSubModeType Icu_Channel_Property;
    /**
    @brief Icu Channel Notification function for TIME_STAMP or EDGE_COUNTER mode
    */
    Icu_NotifyType Icu_Channel_Notification;
    /**
    @brief Icu Custom notification function
    */
#ifdef ICU_CUSTOM_NOTIFICATION_API
    Icu_CustomNotifyType Icu_Custom_Notification;
/* ICU_CUSTOM_NOTIFICATION_API */    
#endif  
    /**
    @brief Icu Channel Overflow Notification function
    */
#if defined(ICU_OVERFLOW_NOTIFICATION_API) && (ICU_OVERFLOW_NOTIFICATION_API == STD_ON)
    Icu_NotifyType Icu_Channel_OverFlowNotification;
/* ICU_OVERFLOW_NOTIFICATION_API */    
#endif  
    /**
    @brief EcuM wakeup source Id
    */
    Icu_WakeupValue Icu_Channel_WakeupValue;
} Icu_ChannelConfigType;


/**
@struct Icu_ConfigType
        This type contains initialization data.
        The notification functions shall be configurable
        as function pointers within the initialization data structure (Icu_ConfigType).
        This type of the external data structure shall contain the
        initialization data for the ICU driver. It shall contain:
        - Wakeup Module Info (in case the wakeup-capability is true)
        - ICU dependent properties for used HW units
        - Clock source with optional prescaler (if provided by HW)
@remarks Covers ICU038, ICU039,ICU190
@remarks Implements DICU50200
*/
typedef struct
{
    /**
    @brief The number of configured channels
    */
    CONST(Icu_ChannelType, ICU_CONST) Icu_MaxChannels;
    /**
    @brief Pointer to Icu channel configuration
    */
    P2CONST(Icu_ChannelConfigType, ICU_VAR, ICU_APPL_CONST) Icu_ChannelConfigPtr;
    /**
    @brief  This index relates the Icu Channel number with the respective global variable,
            depending on the measurement mode Each kind of measurement mode has an array(s)
            in the ICU driver.
    */
    P2CONST(Icu_ChannelType, ICU_VAR, ICU_APPL_CONST) Icu_ChannelIndex;
    /**
        @brief Array for mapping the Icu channels to hardware channels
    */
    P2CONST(Icu_ChannelType, ICU_VAR, ICU_APPL_CONST) Icu_ChannelId;
    /**
    @brief This index relates the Hardware channels with the respective ICU channel.
    */
    P2CONST(Icu_ChannelType, ICU_VAR, ICU_APPL_CONST) Icu_HWMap;
    /**
    @brief This index relates the Wakeup pins with the respective ICU channel.
    */
    P2CONST(Icu_ChannelType, ICU_VAR, ICU_APPL_CONST) Icu_HWWKMap;
} Icu_ConfigType;


/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

#ifndef ICU_PRECOMPILE_SUPPORT
#define ICU_START_CONFIG_DATA_UNSPECIFIED
/**
@file  Icu.h
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref Icu_h_1
*/
/*lint -save -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

ICU_CFG_EXTERN_DECLARATIONS

#define ICU_STOP_CONFIG_DATA_UNSPECIFIED
/**
@file  Icu.h
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref Icu_h_1
*/
/*lint -save -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/
/* #ifndef ICU_PRECOMPILE_SUPPORT*/
#endif 


/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#define ICU_START_SEC_CODE
/**
@file  Icu.h
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref Icu_h_1
*/
/*lint -save -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

/*================================================================================================*/
/**
@brief      This function initializes the driver.
@details    This service is a non reentrant function used for driver initialization.
        The  Initialization function  shall initialize  all relevant  registers of  the configured
        hardware with the  values of the  structure referenced by  the parameter ConfigPtr.
         If  the  hardware  allows  for   only  one  usage   of  the  register,   the  driver module
         implementing that functionality is responsible for initializing the register.
         The initialization function of this module shall always have a pointer as a parameter, even
         though for Variant PC no configuration set shall be given.
         Instead a NULL pointer shall be passed to the initialization function.
         The Icu  module environment  shall not  call Icu_Init  during a  running operation (e. g.
         timestamp measurement or edge counting).
@param[in]     ConfigPtr        Pointer to a selected configuration structure.
@remarks Covers ICU002, ICU111, ICU220, ICU023, ICU054, ICU060
@remarks Implements DICU20100, DICU01015, DICU10001
*/
/*================================================================================================*/
extern FUNC (void, ICU_CODE) Icu_Init(P2CONST(Icu_ConfigType, AUTOMATIC, ICU_APPL_CONST) ConfigPtr);


#if (ICU_DE_INIT_API == STD_ON)
/*================================================================================================*/
/**
@brief   This function de-initializes the ICU module.
@details This service is a Non reentrant function used for ICU De-Initialization
         After the call of this service, the state of the peripherals used by configuration shall be
         the  same as  after power  on reset.  Values of  registers which  are not  writable  are
         excluded.
         This service shall disable all used interrupts and notifications.
         The Icu module environment shall not  call Icu_DeInit during a running  operation  (e. g.
         timestamp measurement or edge counting)
@pre Icu_Init must be called before.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU091, ICU036
@remarks Implements DICU01002, DICU10002
*/
/*================================================================================================*/
extern FUNC (void, ICU_CODE) Icu_DeInit(void);
/* ICU_DE_INIT_API */
#endif 


#if (ICU_SET_MODE_API == STD_ON)
/*================================================================================================*/
/**
@brief   This function sets the ICU mode.
@details This service is a non reentrant function used for ICU mode  selection.
         This service shall  set the  operation mode  to the given mode parameter.
         This service  can be  called during  running operations.  If so,  an ongoing operation that
         generates interrupts on a wakeup capable  channel like e.g. time stamping or  edge counting
         might lead to the  ICU module not being  able to properly enter sleep  mode. This is then a
         system or ECU configuration issue not a problem of this specification.
@param[in]      Mode        Specifies the operation mode
@pre Icu_Init must be called before.
@remarks Covers ICU002, ICU111, ICU022, ICU048, ICU095, ICU125, ICU011, ICU012
@remarks Implements DICU01020, DICU10003
*/
/*================================================================================================*/
extern FUNC (void, ICU_CODE) Icu_SetMode(VAR(Icu_ModeType, AUTOMATIC) Mode);
/* ICU_SET_MODE_API */
#endif 


#if (ICU_DISABLE_WAKEUP_API == STD_ON)
/*================================================================================================*/
/**
@brief   This function disables the wakeup capability of a single ICU channel.
@details This service is reentrant function and shall disable  the wakeup capability of
         a single ICU channel.This  service is only feasible for ICU channels configured statically
         as wakeup capable true.
         The  function  Icu_DisableWakeup shall  be  pre compile  time  configurable On/Off  by  the
         configuration parameter IcuDisableWakeupApi.
@param[in]     Channel          Numeric identifier of the ICU channel
@pre Icu_Init must be called before.
@remarks Covers ICU002, ICU111, ICU022, ICU048, ICU024, ICU059
@remarks Implements DICU01005, DICU10004
*/
/*================================================================================================*/
extern FUNC (void, ICU_CODE) Icu_DisableWakeup(VAR(Icu_ChannelType, AUTOMATIC) Channel);
/* ICU_DISABLE_WAKEUP_API */
#endif 


#if (ICU_ENABLE_WAKEUP_API == STD_ON)
/*================================================================================================*/
/**
@brief   This function (re-)enables the wakeup capability of the given ICU channel.
@details The function is reentrant and re-enable the wake-up capability of a single ICU channel.
@param[in]     Channel          Numeric identifier of the ICU channel
@pre Icu_Init must be called before.
@pre The channel must be configured as wakeup capable.
@remarks Covers ICU002, ICU111, ICU022, ICU048, ICU155, ICU156
@remarks Implements DICU01008, DICU10005
*/
/*================================================================================================*/
extern FUNC (void, ICU_CODE) Icu_EnableWakeup(VAR(Icu_ChannelType, AUTOMATIC) Channel);
/* ICU_ENABLE_WAKEUP_API */
#endif 


/*================================================================================================*/
/**
@brief   This function sets the activation-edge for the given channel.
@details This service  is reentrant and shall set  the  activation-edge according to Activation
         parameter for the given channel.
         This service shall support channels which are configured
         for  the following Icu_MeasurementMode:
         - ICU_MODE_SIGNAL_EDGE_DETECT
         - ICU_MODE_TIMESTAMP
         - ICU_MODE_EDGE_COUNTER
@param[in]     Channel          Numeric identifier of the ICU channel
@param[in]     Activation       Type of activation.
@pre Icu_Init must be called before.
@pre The channel must be properly configured (ICU_MODE_SIGNAL_EDGE_DETECT,
     ICU_MODE_TIMESTAMP, ICU_MODE_EDGE_COUNTER).
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU159, ICU043
@remarks Implements DICU01019, DICU10006
*/
/*================================================================================================*/
extern FUNC (void, ICU_CODE) Icu_SetActivationCondition(VAR(Icu_ChannelType, AUTOMATIC) Channel,
                                                     VAR(Icu_ActivationType, AUTOMATIC) Activation);


/*================================================================================================*/
/**
@brief   This function disables the notification of a channel.
@details This function is reentrant and disables the notification of a channel.
@param[in]     Channel          Numeric identifier of the ICU channel
@pre Icu_Init must be called before.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU160
@remarks Implements DICU01004, DICU10007
*/
/*================================================================================================*/
extern FUNC (void, ICU_CODE) Icu_DisableNotification(VAR(Icu_ChannelType, AUTOMATIC) Channel);


/*================================================================================================*/
/**
@brief   This function enables the notification on the given channel.
@details This function is reentrant and enables the notification on the given channel.
@param[in]     Channel          Numeric identifier of the ICU channel
@pre Icu_Init must be called before.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU161
@remarks Implements DICU01007, DICU10008
*/
/*================================================================================================*/
extern FUNC (void, ICU_CODE) Icu_EnableNotification(VAR(Icu_ChannelType, AUTOMATIC) Channel);


#if (ICU_GET_INPUT_STATE_API == STD_ON)
/*================================================================================================*/
/**
@brief   This function returns the status of the ICU input.
@details This service is reentrant shall return the status of  the ICU input.
         Only channels which are configured for the following Icu_MeasurementMode shall be supported:
         - ICU_MODE_SIGNAL_EDGE_DETECT,
         - ICU_MODE_SIGNAL_MEASUREMENT.
@param[in]     Channel          Numeric identifier of the ICU channel
@return Icu_InputStateType
         - ICU_ACTIVE: An activation edge has been detected
         - ICU_IDLE: No activation edge has been detected since the last call of
                    Icu_GetInputState() or Icu_Init().
@pre Icu_Init must be called before.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU162
@remarks Implements DICU01011, DICU10009
*/
/*================================================================================================*/
extern FUNC (Icu_InputStateType, ICU_CODE) Icu_GetInputState(
                                                           VAR(Icu_ChannelType, AUTOMATIC) Channel);
/* ICU_GET_INPUT_STATE_API */
#endif 


#if (ICU_TIMESTAMP_API == STD_ON)
/*================================================================================================*/
/**
@brief   This function starts the capturing of timer values on the edges.
@details This function is reentrant and starts the capturing of timer values on the edges activated
         by the service Icu_SetActivationCondition() to an external buffer.
@param[in]     Channel          Numeric identifier of the ICU channel
@param[in]     BufferPtr        Pointer to the buffer-array where the timestamp values shall be
                                placed.
@param[in]     BufferSize       Size of the external buffer (number of entries)
@param[in]     NotifyInterval   Notification interval (number of events).
@pre Icu_Init must be called before.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU163, ICU120, ICU108
@remarks Implements DICU01022, DICU10010
*/
/*================================================================================================*/
extern FUNC (void, ICU_CODE) Icu_StartTimestamp(VAR(Icu_ChannelType, AUTOMATIC) Channel,
                                           P2VAR(Icu_ValueType, AUTOMATIC, ICU_APPL_DATA) BufferPtr,
                                           VAR(uint16, AUTOMATIC) BufferSize,
                                           VAR(uint16, AUTOMATIC) NotifyInterval);


/*================================================================================================*/
/**
@brief   This function stops the timestamp measurement of the given channel.
@details This function is reentrant and stops the timestamp measurement of the given channel.
@param[in]     Channel          Numeric identifier of the ICU channel
@pre Icu_Init must be called before.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU164, ICU166
@remarks Implements DICU01024, DICU10011
*/
/*================================================================================================*/
extern FUNC (void, ICU_CODE) Icu_StopTimestamp(VAR(Icu_ChannelType, AUTOMATIC) Channel);


/*================================================================================================*/
/**
@brief   This function reads the timestamp index of the given channel.
@details This function reentrant and reads the timestamp index of the given channel,
         which is next to be written.
@param[in]     Channel          Numeric identifier of the ICU channel
@return Icu_IndexType - Timestamp index of the given channel
@pre Icu_Init must be called before.
@pre Icu_StartTimestamp must be called before.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU169, ICU107, ICU004
@remarks Implements DICU01013, DICU10012
*/
/*================================================================================================*/
extern FUNC (Icu_IndexType, ICU_CODE) Icu_GetTimestampIndex(
                                                           VAR(Icu_ChannelType, AUTOMATIC) Channel);
/* ICU_TIMESTAMP_API */
#endif 


#if (ICU_EDGE_COUNT_API == STD_ON)
/*================================================================================================*/
/**
@brief   This function resets the value of the counted edges to zero.
@details This function is reentrant and resets the value of the counted edges to zero.
@param[in]     Channel          Numeric identifier of the ICU channel.
@pre Icu_Init must be called before.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU171
@remarks Implements DICU01018, DICU10013
*/
/*================================================================================================*/
extern FUNC (void, ICU_CODE) Icu_ResetEdgeCount(VAR(Icu_ChannelType, AUTOMATIC) Channel);


/*================================================================================================*/
/**
@brief   This function enables the counting of edges of the given channel.
@details This service is reentrant and shall enable the counting of  edges of the given channel.
         Note: This  service doesnot do the real counting itself. This is done by the hardware
        (capture unit).
         Only the configured edges shall be counted (rising edge / falling edge / both edges).

         Configuration  of  the  edge  is  done  in  Icu_Init  or  Icu_SetActivationCondition.   The
         configured edge can be  changed during runtime using  Icu_SetActivationCondition.Interrupts
         are not required for edge counting.If interrupts are enabled, the interrupt service routine
         will set the overflow flag if more than 0xFFFFFF edges are measured.
@param[in]     Channel          Numeric identifier of the ICU channel
@pre Icu_Init must be called before.
@pre The given channel must be configured in Measurement Mode Edge Counter.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU172
@remarks Implements DICU01006, DICU10014
*/
/*================================================================================================*/
extern FUNC (void, ICU_CODE) Icu_EnableEdgeCount(VAR(Icu_ChannelType, AUTOMATIC) Channel);


/*================================================================================================*/
/**
@brief   This function disables the counting of edges of the given channel.
@details This function is reentrant and disables the counting of edges of the given channel.
@param[in]     Channel          Numeric identifier of the ICU channel
@pre Icu_Init must be called before.
@pre The given channel must be configured in Measurement Mode Edge Counter.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU173
@remarks Implements DICU01003, DICU10015
*/
/*================================================================================================*/
extern FUNC (void, ICU_CODE) Icu_DisableEdgeCount(VAR(Icu_ChannelType, AUTOMATIC) Channel);


/*================================================================================================*/
/**
@brief   This function reads the number of counted edges.
@details This function is reentrant reads the number of counted edges after the last call
         of Icu_ResetEdgeCount().
@param[in]     Channel          Numeric identifier of the ICU channel
@return Icu_EdgeNumberType - Number of the counted edges.
@pre Icu_Init must be called before.
@pre The given channel must be configured in Measurement Mode Edge Counter.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU107, ICU174, ICU175, ICU004
@remarks Implements DICU01010, DICU10016
*/
/*================================================================================================*/
extern FUNC (Icu_EdgeNumberType, ICU_CODE) Icu_GetEdgeNumbers(
                                                           VAR(Icu_ChannelType, AUTOMATIC) Channel);
/* ICU_EDGE_COUNT_API */
#endif 


#if (ICU_GET_TIME_ELAPSED_API== STD_ON)
/*================================================================================================*/
/**
@brief   This function reads the elapsed Signal Low/High/Period Time for the given channel.
@details This service is reentrant and reads the elapsed Signal Low Time for the given channel
         that is configured  in Measurement Mode Signal Measurement, Signal Low Time.
         The elapsed time is measured between a falling edge and the consecutive rising edge of  the
         channel.
         This service reads the elapsed Signal High Time for the given channel that is configured in
         Measurement Mode Signal Measurement,Signal High Time.The elapsed time is measured between
         a rising edge and the consecutive falling edge of the channel.
         This service reads the elapsed Signal Period Time for the given channel that is  configured
         in Measurement Mode Signal Measurement,  Signal Period Time.The elapsed time  is measured
         between consecutive  rising (or  falling) edges  of the  channel. The  period start edge is
         configurable.
@param[in]     Channel          Numeric identifier of the ICU channel
@return Icu_ValueType - The elapsed Signal Low Time for the given channel
@pre Icu_Init must be called before.
@pre The given channel must be configured in Measurement Mode Signal Measurement.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU107, ICU178, ICU004, ICU179, ICU136
@remarks Implements DICU01012, DICU10019
*/
/*================================================================================================*/
extern FUNC (Icu_ValueType, ICU_CODE) Icu_GetTimeElapsed(VAR(Icu_ChannelType, AUTOMATIC) Channel);
/* ICU_GET_TIME_ELAPSED_API */
#endif 


#if (ICU_GET_DUTY_CYCLE_VALUES_API == STD_ON)
/*================================================================================================*/
/**
@brief   This function reads the coherent active time and period time for the given ICU Channel.
@details The function is reentrant and reads the coherent active time and period time for
         the given ICU Channel, if it is configured in Measurement Mode Signal Measurement, Duty 
         Cycle Values.
@param[in]     Channel          Numeric identifier of the ICU channel
@param[out]    DutyCycleValues  Pointer to a buffer where the results (high time and period time) 
                                shall be placed.
@pre Icu_Init must be called before.
@pre The given channel must be configured in Measurement Mode Signal Measurement, Duty Cycle Values.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU180, ICU107, ICU004, ICu181, ICU137
@remarks Implements DICU01009, DICU10020
*/
/*================================================================================================*/
extern FUNC (void, ICU_CODE) Icu_GetDutyCycleValues(VAR(Icu_ChannelType, AUTOMATIC) Channel,
                                P2VAR(Icu_DutyCycleType, AUTOMATIC, ICU_APPL_DATA) DutyCycleValues);
/* ICU_GET_DUTY_CYCLE_VALUES_API */
#endif 


#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
/*================================================================================================*/
/**
@brief   This function starts the measurement of signals.
@details This service is reentrant and starts the measurement of signals beginning with the
         configured default start edge which occurs first after the call of this service.
         This service shall only be available in Measurement Mode ICU_MODE_SIGNAL_MEASUREMENT.
         This service shall reset the state for the given channel to ICU_IDLE.
@param[in]     Channel          Numeric identifier of the ICU channel
@pre Icu_Init must be called before.
@pre The given channel must be configured in Measurement Mode Signal Measurement.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU176
@remarks Implements DICU01021, DICU10017
*/
/*================================================================================================*/
extern FUNC (void, ICU_CODE) Icu_StartSignalMeasurement(VAR(Icu_ChannelType, AUTOMATIC) Channel);


/*================================================================================================*/
/**
@brief   This function stops the measurement of signals of the given channel.
@details This function is reentrant and stops the measurement of signals of the given channel.
@param[in]     Channel          Numeric identifier of the ICU channel
@pre Icu_Init must be called before.
@pre The given channel must be configured in Measurement Mode Signal Measurement.
@remarks Covers ICU002, ICU111, ICU112, ICU022, ICU048, ICU177
@remarks Implements DICU01023, DICU10018
*/
/*================================================================================================*/
extern FUNC (void, ICU_CODE) Icu_StopSignalMeasurement(VAR(Icu_ChannelType, AUTOMATIC) Channel);
/* ICU_SIGNAL_MEASUREMENT_API */
#endif 


#if (ICU_GET_VERSION_INFO_API == STD_ON)
/*================================================================================================*/
/**
@brief   This service returns the version information of this module.
@details This  service is Non reentrant and returns the version information of this module.
         The version information includes:
         - Module Id
         - Vendor Id
         - Vendor specific version numbers
         If source code for caller and callee of this function is available this function should  be
         realized as a macro. The macro should be defined in the modules header file.
@param[out]    versioninfo      Pointer to location to store version info
@remarks Covers ICU005
@remarks Implements DICU01014
*/
/*================================================================================================*/
FUNC(void, ICU_CODE) Icu_GetVersionInfo(
                                    P2VAR(Std_VersionInfoType,AUTOMATIC,ICU_APPL_DATA) versioninfo);
/* ICU_GET_VERSION_INFO_API == STD_ON */
#endif  



#define ICU_STOP_SEC_CODE
/**
@file  Icu.h
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref Icu_h_1
*/
/*lint -save -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/


#ifdef __cplusplus
}
#endif
/* ICU_H */
#endif  

