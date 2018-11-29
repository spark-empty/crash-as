/**
@file    Pwm.h
@version 2.0.0

@brief   AUTOSAR Pwm - Pwm module API header.
@details Pwm APIs and defines

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
/*===============================================================================================
===============================================================================================*/

/**
@page misra_violations MISRA-C:2004 violations

@section Pwm_H_REF_1
Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments 
                                        before "#include"
MemMap.h included after each section define in order to set the current memory section

@section Pwm_H_REF_2
Violates MISRA 2004 Advisory Rule 19.15, :  Repeated include files,  Precautions shall be taken in
order to prevent the contents of a header file being included twice This is not a violation since
all header files are protected against multiple inclusions
*/

#ifndef PWM_H
#define PWM_H

#ifdef __cplusplus
extern "C" {
#endif

/*===============================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
===============================================================================================*/
/*lint -save -e961 -e537 -e451 */
/** @file Pwm.h
    @note Violates MISRA 2004 Advisory Rule 19.15 : See @ref Pwm_H_REF_2 */
#include "Std_Types.h"
/*lint -restore */
#include "Pwm_Cfg.h"

/*===============================================================================================
                               SOURCE FILE VERSION INFORMATION
===============================================================================================*/
/**
@{
@brief Parameters that shall be published within the Pwm driver header file and also in the
       module's description file
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define PWM_VENDOR_ID            43
#define PWM_MODULE_ID            121
#define PWM_AR_MAJOR_VERSION     2
#define PWM_AR_MINOR_VERSION     2
#define PWM_AR_PATCH_VERSION     1
#define PWM_SW_MAJOR_VERSION     2
#define PWM_SW_MINOR_VERSION     0
#define PWM_SW_PATCH_VERSION     0
/**@}*/

/*===============================================================================================
                                      FILE VERSION CHECKS
===============================================================================================*/

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Std_Types.h are of the same Autosar version */
    #if ((PWM_AR_MAJOR_VERSION != STD_TYPES_AR_MAJOR_VERSION) || \
         (PWM_AR_MINOR_VERSION != STD_TYPES_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Pwm.h and Std_Types.h are different"
    #endif
#endif


/* Check if source file and PWM configuration header file are of the same vendor */
#if (PWM_VENDOR_ID != PWM_VENDOR_ID_CFG_H)
    #error "Pwm.h and Pwm_Cfg.h have different vendor ids"
#endif


#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and PWM configuration header file are of the same Autosar version */
    #if ((PWM_AR_MAJOR_VERSION != PWM_AR_MAJOR_VERSION_CFG_H) || \
         (PWM_AR_MINOR_VERSION != PWM_AR_MINOR_VERSION_CFG_H) || \
         (PWM_AR_PATCH_VERSION != PWM_AR_PATCH_VERSION_CFG_H))
    #error "AutoSar Version Numbers of Pwm.h and Pwm_Cfg.h are different"
    #endif
#endif

/* Check if source file and PWM configuration header file are of the same software version */
#if ((PWM_SW_MAJOR_VERSION != PWM_SW_MAJOR_VERSION_CFG_H) || \
     (PWM_SW_MINOR_VERSION != PWM_SW_MINOR_VERSION_CFG_H) || \
     (PWM_SW_PATCH_VERSION != PWM_SW_PATCH_VERSION_CFG_H))
#error "Software Version Numbers of Pwm.h and Pwm_Cfg.h are different"
#endif

/*===============================================================================================
                                           CONSTANTS
===============================================================================================*/

/*===============================================================================================
                                       DEFINES AND MACROS
===============================================================================================*/

/**
@brief   100% dutycycle
@details Errors and exceptions that will be detected by the PWM driver generated when
         Pwm_SetDutyCycle or Pwm_SetPeriodAndDuty are called with a value for dutycyle
         out of valid range [0x0000, 0x8000]

@remarks Covers     PWM002, PWM006
*/
#define PWM_DUTY_CYCLE_100 ((uint16)0x8000U)

/**
@brief   API Pwm_Init service called with wrong parameter
@details Errors and exceptions that will be detected by the PWM driver
@remarks Implements DPWM01013
@remarks Covers     PWM002
*/
#define PWM_E_PARAM_CONFIG         0x10U

/**
@brief   API service used without module initialization
@details Errors and exceptions that will be detected by the PWM driver
@remarks Implements DPWM01017
@remarks Covers     PWM002
*/
#define PWM_E_UNINIT               0x11U

/**
@brief   API service used with an invalid channel Identifier
@details Errors and exceptions that will be detected by the PWM driver
@remarks Implements DPWM01012
@remarks Covers     PWM002
*/
#define PWM_E_PARAM_CHANNEL        0x12U

/**
@brief   Usage of unauthorized PWM service on PWM channel configured a fixed period
@details Errors and exceptions that will be detected by the PWM driver
@remarks Implements DPWM01016
@remarks Covers     PWM002
*/
#define PWM_E_PERIOD_UNCHANGEABLE  0x13U

/**
@brief   API Pwm_Init service called while the PWM driver has already been initialised
@details Errors and exceptions that will be detected by the PWM driver
@remarks Implements DPWM01010
@remarks Covers     PWM002
*/
#define PWM_E_ALREADY_INITIALIZED  0x14U

/**
@brief   Will be generated when an invalid polarity, edge notification is requested for 
         one pwm channel.
         Due to the limitations that are present in the eMIOS implementation not all 
         the polarity notifications combinations can be supported.
@details Errors and exceptions that will be detected by the PWM driver
@remarks Implements DPWM01014
@remarks Covers     PWM002, PWM006
*/
#define PWM_E_PARAM_NOTIFICATION   0x15U

/**
@brief   Will be generated when a NULL function is configured as notification callback for 
         one pwm channel and Pwm_EnableNotification is called for that channel
@details Errors and exceptions that will be detected by the PWM driver
@remarks Implements DPWM01015
@remarks Covers     PWM002, PWM006
*/
#define PWM_E_PARAM_NOTIFICATION_NULL  0x16U

/**
@brief   generated when Pwm_SetDutyCycle or Pwm_SetPeriodAndDuty are called with a value 
         for dutycyle out of valid range [0x0000, 0x8000]
@details Errors and exceptions that will be detected by the PWM driver
@remarks Implements DPWM01011
@remarks Covers     PWM002, PWM006
*/
#define PWM_E_DUTYCYCLE_RANGE          0x17U

/**
@brief   generated when a NULL pointer is passed to Pwm_GetVersionInfo function
@details Errors and exceptions that will be detected by the PWM driver

@remarks Covers     PWM002, PWM006
*/
#define PWM_E_PARAM_VERSIONINFO_NULL   0x18U

/**
@brief   API service ID of Pwm_Init function
@details Parameters used when raising an error/exception
@remarks Covers     PWM095
*/
#define PWM_INIT_ID                0x00U

/**
@brief   API service ID of Pwm_DeInit function
@details Parameters used when raising an error/exception
@remarks Covers     PWM096
*/
#define PWM_DEINIT_ID              0x01U

/**
@brief   API service ID of Pwm_SetDutyCycle function
@details Parameters used when raising an error/exception
@remarks Covers     PWM097
*/
#define PWM_SETDUTYCYCLE_ID        0x02U

/**
@brief   API service ID of Pwm_SetPeriodAndDuty function
@details Parameters used when raising an error/exception
@remarks Covers     PWM098
*/
#define PWM_SETPERIODANDDUTY_ID    0x03U

/**
@brief   API service ID of Pwm_SetOutputToIdle function
@details Parameters used when raising an error/exception
@remarks Covers     PWM099
*/
#define PWM_SETOUTPUTTOIDLE_ID     0x04U

/**
@brief   API service ID of Pwm_GetOutputState function
@details Parameters used when raising an error/exception
@remarks Covers     PWM100
*/
#define PWM_GETOUTPUTSTATE_ID      0x05U

/**
@brief   API service ID of Pwm_DisableNotification function
@details Parameters used when raising an error/exception
@remarks Covers     PWM101
*/
#define PWM_DISABLENOTIFICATION_ID 0x06U

/**
@brief   API service ID of Pwm_EnableNotification function
@details Parameters used when raising an error/exception
@remarks Covers     PWM102
*/
#define PWM_ENABLENOTIFICATION_ID  0x07U

/**
@brief   API service ID of Pwm_GetVersionInfo function
@details Parameters used when raising an error/exception
@remarks Covers     PWM103
*/
#define PWM_GETVERSIONINFO_ID      0x08U



/*===============================================================================================
                                             ENUMS
===============================================================================================*/

/*===============================================================================================
                            STRUCTURES AND OTHER TYPEDEFS
===============================================================================================*/

/*===============================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
===============================================================================================*/

/*lint -save -e961 -e537 -e451 */
#define PWM_START_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"
/*lint -restore */


#ifndef PWM_PRECOMPILE_SUPPORT
PWM_INIT_CONFIG_PB_DEFINES
#endif

#ifdef PWM_PRECOMPILE_SUPPORT
PWM_INIT_CONFIG_PC_DEFINE
#endif

#define PWM_STOP_CONFIG_DATA_UNSPECIFIED
/*lint -save -e961 -e537 -e451 */
/** @file Pwm.h
    @note Violates MISRA 2004 Advisory Rule 19.1, 19.15 : See @ref Pwm_H_REF_1, Pwm_H_REF_2 */
#include "MemMap.h"
/*lint -restore */

/*===============================================================================================
                                     FUNCTION PROTOTYPES
===============================================================================================*/

/*lint -save -e961 -e537 -e451 */
/** @file Pwm.h
    @note Violates MISRA 2004 Advisory Rule 19.1, 19.15 : See @ref Pwm_H_REF_1, Pwm_H_REF_2 */
#define PWM_START_SEC_CODE
#include "MemMap.h"
/*lint -restore */

/**
@brief   This function initializes the Pwm driver.

@details The function Pwm_Init shall initialize all internals variables and the used 
         PWM structure of the microcontroller according to the parameters 
         specified in ConfigPtr.

    If the duty cycle parameter equals:

        - 0% or 100% : Then the PWM output signal shall be in the state according 
                       to the configured polarity parameter;

        - >0% and <100%: Then the PWM output signal shall be modulated according 
                         to parameters period, duty cycle and configured polarity.

    The function Pwm_SetDutyCycle shall update the duty cycle always at the end 
    of the period if supported by the implementation and configured 
    with PwmDutycycleUpdatedEndperiod.

    The driver shall avoid spikes on the PWM output signal when updating 
    the PWM period and duty.

    If development error detection for the Pwm module is enabled, the PWM functions 
    shall check the channel class type and raise development error PWM_E_PERIOD_UNCHANGEABLE 
    if the PWM channel is not declared as a variable period type.

    If development error detection for the Pwm module is enabled, the PWM functions 
    shall check the parameter ChannelNumber and raise development error PWM_E_PARAM_CHANNEL 
    if the parameter ChannelNumber is invalid.

    If development error detection for the Pwm module is enabled, when a development 
    error occurs, the corresponding PWM function shall:

        - Report the error to the Development Error Tracer.

        - Skip the desired functionality in order to avoid any corruptions of 
        data or hardware registers (this means leave the function without any actions).

        - Return pwm level low for the function Pwm_GetOutputState.

    The function Pwm_Init shall disable all notifications. The reason is that the users 
    of these notifications may not be ready. They can call Pwm_EnableNotification 
    to start notifications.

    The function Pwm_Init shall only initialize the configured resources and shall not touch 
    resources that are not configured in the configuration file.

    If the PwmDevErorDetect switch is enabled, API parameter checking is enabled. 
    The detailed description of the detected errors can be found in chapter 
    Error classification and chapter API specification (see PWM_SWS).

    If development error detection is enabled, calling the routine Pwm_Init 
    while the PWM driver and hardware are already initialized will cause a 
    development error PWM_E_ALREADY_INITIALIZED. 
    The desired functionality shall be left without any action.

    For pre-compile and link time configuration variants, a NULL pointer shall be passed 
    to the initialization routine. In this case the check for this NULL pointer 
    has to be omitted.

    If development error detection for the Pwm module is enabled, if any function 
    (except Pwm_Init) is called before Pwm_Init has been called, the called function 
    shall raise development error PWM_E_UNINIT.

@param[in] ConfigPtr pointer to PWM top configuration structure

@remarks Covers     PWM007, PWM009, PWM046, PWM047, PWM051, PWM052, PWM062, PWM064, PWM095, PWM117,
                    PWM118, PWM120
@remarks Implements DPWM01001
*/
extern FUNC (void, PWM_CODE) Pwm_Init
                             (
                                 P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr
                             );

#if (PWM_DE_INIT_API == STD_ON)
/**
@brief   This function deinitializes the Pwm driver.

@details The function Pwm_DeInit shall deinitialize the PWM module.

    The function Pwm_DeInit shall set the state of the PWM output signals 
    to the idle state.

    The function Pwm_DeInit shall disable PWM interrupts and PWM signal edge notifications.

    The function Pwm_DeInit shall be pre-compile time configurable On/Off by the 
    configuration parameter PwmDeInitApi function prototype.

    If development error detection for the Pwm module is enabled, 
    when a development error occurs, the corresponding PWM function shall:

        - Report the error to the Development Error Tracer.

        - Skip the desired functionality in order to avoid any corruptions 
        of data or hardware registers (this means leave the function without any actions).

        - Return pwm level low for the function Pwm_GetOutputState.

    If development error detection for the Pwm module is enabled, if any function 
    (except Pwm_Init) is called before Pwm_Init has been called, the called function 
    shall raise development error PWM_E_UNINIT.


@remarks Covers     PWM010, PWM011, PWM012, PWM051, PWM080, PWM096, PWM117
@remarks Implements DPWM01002
*/
extern FUNC (void, PWM_CODE) Pwm_DeInit(void);
#endif

#if (PWM_SET_DUTY_CYCLE_API == STD_ON)
/**
@brief   This function sets the dutycycle for the specified Pwm channel.

@details The function Pwm_SetDutyCycle shall set the duty cycle of the PWM channel.

    The function Pwm_SetDutyCycle shall set the PWM output state according 
    to the configured polarity parameter, when the duty cycle = 0% or 100%.

    The function Pwm_SetDutyCycle shall modulate the PWM output signal according 
    to parameters period, duty cycle and configured polarity, 
    when the duty cycle > 0 % and < 100%.

    The function Pwm_SetDutyCycle shall update the duty cycle always at the end 
    of the period if supported by the implementation and 
    configured with PwmDutycycleUpdatedEndperiod.

    The driver shall avoid spikes on the PWM output signal when 
    updating the PWM period and duty.
    
    If development error detection for the Pwm module is enabled, the PWM functions 
    shall check the channel class type and raise development error PWM_E_PERIOD_UNCHANGEABLE 
    if the PWM channel is not declared as a variable period type.

    If development error detection for the Pwm module is enabled, 
    the PWM functions shall check the parameter ChannelNumber and raise development error 
    PWM_E_PARAM_CHANNEL if the parameter ChannelNumber is invalid.

    If development error detection for the Pwm module is enabled, 
    when a development error occurs, the corresponding PWM function shall:

        - Report the error to the Development Error Tracer.

        - Skip the desired functionality in order to avoid any corruptions 
        of data or hardware registers (this means leave the function without any actions).

        - Return pwm level low for the function Pwm_GetOutputState.

    The width of the duty cycle parameter is 16 Bits.

    The Pwm module shall comply with the following scaling scheme for the duty cycle:

        - 0x0000 means 0%.
    
        - 0x8000 means 100%.

        - 0x8000 gives the highest resolution while allowing 100% duty cycle to be 
        represented with a 16 bit value.

    As an implementation guide, the following source code example is given:

        - AbsoluteDutyCycle = ((uint32)AbsolutePeriodTime * RelativeDutyCycle) >> 15;

    If the PwmDevErorDetect switch is enabled, API parameter checking is enabled. 
    The detailed description of the detected errors can be found in chapter 
    Error classification and chapter API specification (see PWM_SWS).

    All functions from the PWM module except Pwm_Init, Pwm_DeInit and Pwm_GetVersionInfo 
    shall be re-entrant for different PWM channel numbers. In order to keep a simple module 
    implementation, no check of PWM088 must be performed by the module.

    All time units used within the API services of the PWM module shall be of the unit ticks.

    The function Pwm_SetDutyCycle shall be pre compile time configurable On/Off by 
    the configuration parameter PwmSetDutyCycle.

    All functions from the PWM module except Pwm_Init, Pwm_DeInit and Pwm_GetVersionInfo 
    shall be re-entrant for different PWM channel numbers. In order to keep a simple module 
    implementation, no check of PWM088 must be performed by the module.

    After the call of the function Pwm_SetOutputToIdle, variable period type channels 
    shall be reactivated either using the Api Pwm_SetPeriodAndDuty() to activate 
    the PWM channel with the new passed period or Api Pwm_SetDutyCycle() to activate 
    the PWM channel with the old period.

    After the call of the function Pwm_SetOutputToIdle, fixed period type channels 
    shall be reactivated using only the API Api Pwm_SetDutyCycle() to activate the 
    PWM channel with the old period.

    If development error detection for the Pwm module is enabled, if any function 
    (except Pwm_Init) is called before Pwm_Init has been called, the called function shall 
    raise development error PWM_E_UNINIT.

@param[in]     ChannelNumber - pwm channel id
@param[in]     DutyCycle     - pwm dutycycle value 0x0000 for 0% ... 0x8000 for 100%

@remarks Covers     PWM013, PWM014, PWM016, PWM017, PWM020, PWM047, PWM051, PWM058, PWM059, PWM064,
                    PWM070, PWM082, PWM086, PWM088, PWM097, PWM117, PWM119
@remarks Implements DPWM01003
*/
extern FUNC (void, PWM_CODE) Pwm_SetDutyCycle
                             (
                                 VAR(Pwm_ChannelType, AUTOMATIC) ChannelNumber, 
                                 VAR(uint16, AUTOMATIC) DutyCycle
                             );
#endif

#if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
/**
@brief   This function sets the period and the dutycycle for the specified Pwm channel.

@details The function Pwm_SetPeriodAndDuty shall set the period and the duty cycle 
         of a PWM channel.

    The driver shall avoid spikes on the PWM output signal when updating the 
    PWM period and duty.

    The function Pwm_SetPeriodAndDuty shall allow changing the period only 
    for the PWM channel declared as variable period type.

    If development error detection for the Pwm module is enabled, the PWM functions shall 
    check the channel class type and raise development error PWM_E_PERIOD_UNCHANGEABLE 
    if the PWM channel is not declared as a variable period type.

    If development error detection for the Pwm module is enabled, the PWM functions shall 
    check the parameter ChannelNumber and raise development error PWM_E_PARAM_CHANNEL 
    if the parameter ChannelNumber is invalid.

    If development error detection for the Pwm module is enabled, 
    when a development error occurs, the corresponding PWM function shall:

        - Report the error to the Development Error Tracer.

        - Skip the desired functionality in order to avoid any corruptions of data 
        or hardware registers (this means leave the function without any actions).

        - Return pwm level low for the function Pwm_GetOutputState.

    The width of the duty cycle parameter is 16 Bits.

    The Pwm module shall comply with the following scaling scheme for the duty cycle:

        - 0x0000 means 0%.
    
        - 0x8000 means 100%.

        - 0x8000 gives the highest resolution while allowing 100% duty cycle to be 
        represented with a 16 bit value.

    As an implementation guide, the following source code example is given:

        - AbsoluteDutyCycle = ((uint32)AbsolutePeriodTime * RelativeDutyCycle) >> 15;

    If the PwmDevErorDetect switch is enabled, API parameter checking is enabled. 
    The detailed description of the detected errors can be found in chapter 
    Error classification and chapter API specification (see PWM_SWS).

    All functions from the PWM module except Pwm_Init, Pwm_DeInit and Pwm_GetVersionInfo 
    shall be re-entrant for different PWM channel numbers. In order to keep a simple module 
    implementation, no check of PWM088 must be performed by the module.

    All time units used within the API services of the PWM module shall be of the unit ticks.

    The function Pwm_SetPeriodAndDuty shall update the period always at the end 
    of the current period if supported by the implementation and configured 
    with PwmPeriodUpdatedEndperiod.

    The function Pwm_SetPeriodAndDuty shall be pre compile time configurable On/Off by the 
    configuration parameter PwmSetPeriodAndDuty.

    After the call of the function Pwm_SetOutputToIdle, variable period type channels 
    shall be reactivated either using the Api Pwm_SetPeriodAndDuty() to activate 
    the PWM channel with the new passed period or Api Pwm_SetDutyCycle() to activate 
    the PWM channel with the old period.

    After the call of the function Pwm_SetOutputToIdle, fixed period type channels 
    shall be reactivated using only the API Api Pwm_SetDutyCycle() to activate 
    the PWM channel with the old period.

    If development error detection for the Pwm module is enabled, if any function 
    (except Pwm_Init) is called before Pwm_Init has been called, the called function 
    shall raise development error PWM_E_UNINIT.

@param[in]     ChannelNumber - pwm channel id
@param[in]     Period        - pwm signal period value
@param[in]     DutyCycle     - pwm dutycycle value 0x0000 for 0% ... 0x8000 for 100%

@remarks Covers     PWM019, PWM020, PWM041, PWM045, PWM047, PWM051, PWM058, PWM059, PWM064, PWM070,
                    PWM076, PWM083, PWM086, PWM088, PWM098, PWM117
@remarks Implements DPWM01004
*/
extern FUNC (void, PWM_CODE) Pwm_SetPeriodAndDuty
                             (
                                 VAR(Pwm_ChannelType, AUTOMATIC) ChannelNumber, 
                                 VAR(Pwm_PeriodType, AUTOMATIC) Period, 
                                 VAR(uint16, AUTOMATIC) DutyCycle
                             );
#endif

#if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
/**
@brief This function sets the generated pwm signal to the idle value configured.

@details The function Pwm_SetOutputToIdle shall set immediately the 
         PWM output to the configured Idle state.

    If development error detection for the Pwm module is enabled, the PWM functions 
    shall check the parameter ChannelNumber and raise development error PWM_E_PARAM_CHANNEL 
    if the parameter ChannelNumber is invalid.

    If development error detection for the Pwm module is enabled, when a 
    development error occurs, the corresponding PWM function shall:

        - Report the error to the Development Error Tracer.

        - Skip the desired functionality in order to avoid any corruptions of data 
        or hardware registers (this means leave the function without any actions).

        - Return pwm level low for the function Pwm_GetOutputState.

    If the PwmDevErorDetect switch is enabled, API parameter checking is enabled. 
    The detailed description of the detected errors can be found in chapter 
    Error classification and chapter API specification (see PWM_SWS).

    All functions from the PWM module except Pwm_Init, Pwm_DeInit and Pwm_GetVersionInfo 
    shall be re-entrant for different PWM channel numbers. In order to keep a simple module 
    implementation, no check of PWM088 must be performed by the module.

    The function Pwm_SetOutputToIdle shall be pre compile time configurable On/Off by the 
    configuration parameter PwmSetOutputToIdle.

    After the call of the function Pwm_SetOutputToIdle, variable period type channels 
    shall be reactivated either using the Api Pwm_SetPeriodAndDuty() to activate 
    the PWM channel with the new passed period or Api Pwm_SetDutyCycle() to activate 
    the PWM channel with the old period.

    After the call of the function Pwm_SetOutputToIdle, fixed period type channels 
    shall be reactivated using only the API Api Pwm_SetDutyCycle() to activate 
    the PWM channel with the old period.

    If development error detection for the Pwm module is enabled, if any function 
    (except Pwm_Init) is called before Pwm_Init has been called, the called function 
    shall raise development error PWM_E_UNINIT.

@param[in]     ChannelNumber - pwm channel id

@remarks Covers     PWM021, PWM047, PWM051, PWM064, PWM084, PWM086, PWM088, PWM099, PWM117
@remarks Implements DPWM01005
*/
extern FUNC (void, PWM_CODE) Pwm_SetOutputToIdle
                             (
                                 VAR(Pwm_ChannelType, AUTOMATIC) ChannelNumber
                             );
#endif

#if (PWM_GET_OUTPUT_STATE_API == STD_ON)
/**
@brief   This function returns the signal output state.

@details The function Pwm_GetOutputState shall read the internal state of 
         the PWM output signal and return it as defined in the diagram below (see PWM_SWS).

    If development error detection for the Pwm module is enabled, 
    the PWM functions shall check the parameter ChannelNumber and 
    raise development error PWM_E_PARAM_CHANNEL if the parameter ChannelNumber is invalid.

    If development error detection for the Pwm module is enabled, when a 
    development error occurs, the corresponding PWM function shall:

        - Report the error to the Development Error Tracer.

        - Skip the desired functionality in order to avoid any corruptions of 
        data or hardware registers (this means leave the function without any actions).

        - Return pwm level low for the function Pwm_GetOutputState.

    If the PwmDevErorDetect switch is enabled, API parameter checking is enabled. 
    The detailed description of the detected errors can be found in chapter 
    Error classification and chapter API specification (see PWM_SWS).

    All functions from the PWM module except Pwm_Init, Pwm_DeInit and 
    Pwm_GetVersionInfo shall be re-entrant for different PWM channel numbers. 
    In order to keep a simple module implementation, 
    no check of PWM088 must be performed by the module.

    The function Pwm_GetOutputState shall be pre compile time configurable On/Off by the 
    configuration parameter: PwmGetOutputState.

    Due to real time constraint and setting of the PWM channel (project dependant), 
    the output state can be modified just after the call of the service Pwm_GetOutputState.

    Regarding error detection, the requirements PWM117, PWM047 and PWM051 
    are applicable to this function.

    If development error detection for the Pwm module is enabled, if any function 
    (except Pwm_Init) is called before Pwm_Init has been called, the called function 
    shall raise development error PWM_E_UNINIT.

@param[in]     ChannelNumber - pwm channel id
@return Pwm_OutputStateType  pwm signal output logic value
    -PWM_LOW -  The output state of PWM channel is low
    -PWM_HIGH - The output state of PWM channel is high

@remarks Covers     PWM022, PWM047, PWM051, PWM064, PWM085, PWM088, PWM100, PWM117
@remarks Implements DPWM01006
*/
extern FUNC (Pwm_OutputStateType, PWM_CODE) Pwm_GetOutputState
                                            (
                                                VAR(Pwm_ChannelType, AUTOMATIC) ChannelNumber
                                            );
#endif

#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
/**
@brief   This function enables the user notifications.

@details The function Pwm_EnableNotification shall enable the PWM signal edge notification 
         according to notification parameter.

    If development error detection for the Pwm module is enabled:

        - The PWM functions shall check the parameter ChannelNumber and raise 
        development error PWM_E_PARAM_CHANNEL if the parameter ChannelNumber is invalid.

    If development error detection for the Pwm module is enabled, when a development error 
    occurs, the corresponding PWM function shall:

        - Report the error to the Development Error Tracer.

        - Skip the desired functionality in order to avoid any corruptions of 
        data or hardware registers (this means leave the function without any actions).

        - Return pwm level low for the function Pwm_GetOutputState.

    If the PwmDevErorDetect switch is enabled, API parameter checking is enabled. 
    The detailed description of the detected errors can be found in chapter 
    Error classification and chapter API specification (see PWM_SWS).

    All functions from the PWM module except Pwm_Init, Pwm_DeInit and Pwm_GetVersionInfo 
    shall be re-entrant for different PWM channel numbers. In order to keep a simple module 
    implementation, no check of PWM088 must be performed by the module.

    The function Pwm_DisableNotification shall be pre compile time configurable On/Off by 
    the configuration parameter: PwmNotificationSupported.

    Regarding error detection, the requirements PWM117, PWM047 and PWM051 
    are applicable to this function.

    If development error detection for the Pwm module is enabled, if any function 
    (except Pwm_Init) is called before Pwm_Init has been called, the called function 
    shall raise development error PWM_E_UNINIT.

@param[in]     ChannelNumber - pwm channel id
@param[in]     Notification  - notification type to be enabled

@remarks Covers     PWM024, PWM047, PWM051, PWM064, PWM081, PWM088, PWM102, PWM113, PWM117
@remarks Implements DPWM01008
*/
extern FUNC (void, PWM_CODE) Pwm_EnableNotification
                             (
                                 VAR(Pwm_ChannelType, AUTOMATIC) ChannelNumber, 
                                 VAR(Pwm_EdgeNotificationType, AUTOMATIC) Notification
                             );
#endif

#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
/**
@brief   This function disables the user notifications.

@details The function Pwm_DisableNotification shall disable the PWM signal edge notification

    If development error detection for the Pwm module is enabled:

        - The PWM functions shall check the parameter ChannelNumber and raise 
        development error PWM_E_PARAM_CHANNEL if the parameter ChannelNumber is invalid.

    If development error detection for the Pwm module is enabled, 
    when a development error occurs, the corresponding PWM function shall:

        - Report the error to the Development Error Tracer.

        - Skip the desired functionality in order to avoid any corruptions of 
        data or hardware registers (this means leave the function without any actions).

        - Return pwm level low for the function Pwm_GetOutputState.

    If the PwmDevErorDetect switch is enabled, API parameter checking is enabled. 
    The detailed description of the detected errors can be found in chapter 
    Error classification and chapter API specification (see PWM_SWS).

    All functions from the PWM module except Pwm_Init, Pwm_DeInit and Pwm_GetVersionInfo 
    shall be re-entrant for different PWM channel numbers. In order to keep a simple module 
    implementation, no check of PWM088 must be performed by the module.

    The function Pwm_DisableNotification shall be pre compile time configurable On/Off by the
    configuration parameter: PwmNotificationSupported.

    Regarding error detection, the requirements PWM117, PWM047 and PWM051 
    are applicable to this function.

    If development error detection for the Pwm module is enabled, if any function 
    (except Pwm_Init) is called before Pwm_Init has been called, the called function shall 
    raise development error PWM_E_UNINIT.

@param[in]     ChannelNumber - pwm channel id

@remarks Covers     PWM023, PWM047, PWM051, PWM064, PWM088, PWM101, PWM112, PWM117
@remarks Implements DPWM01007
*/
extern FUNC (void, PWM_CODE) Pwm_DisableNotification
                             (
                                 VAR(Pwm_ChannelType, AUTOMATIC) ChannelNumber
                             );
#endif

#if (PWM_VERSION_INFO_API == STD_ON)
/**
@brief   returns Pwm driver version details

@details    The function Pwm_GetVersionInfo shall return the version information 
            of this module.
            The version information includes: Module Id, Vendor Id, Vendor 
            specific version number.

@param[in,out] versioninfo - pointer to Std_VersionInfoType output variable

@remarks Covers     PWM103, PWM051, PWM054, PWM068, PWM069, PWM114, PWM117
@remarks Implements DPWM01009
*/
extern FUNC(void, PWM_CODE) Pwm_GetVersionInfo
                            (
                                P2VAR(Std_VersionInfoType , AUTOMATIC, PWM_APPL_DATA) versioninfo
                            );
#endif

#define PWM_STOP_SEC_CODE
/*lint -save -e961 -e537 -e451 */
/** @file Pwm.h
    @note Violates MISRA 2004 Advisory Rule 19.1, 19.15 : See @ref Pwm_H_REF_1, Pwm_H_REF_2 */
#include "MemMap.h"
/*lint -restore */


#ifdef __cplusplus
}
#endif

#endif /* PWM_H */
