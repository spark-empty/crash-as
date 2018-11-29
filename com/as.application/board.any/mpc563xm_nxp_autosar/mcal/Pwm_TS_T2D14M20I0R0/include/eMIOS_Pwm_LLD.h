/**
@file    eMIOS_Pwm_LLD.h
@version 2.0.0

@brief   AUTOSAR Pwm - Pwm Emios LLD API.
@details Pwm Emios LLD API.

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

@section eMIOS_Pwm_LLD_H_REF_1
Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
                                        before "#include"
MemMap.h included after each section define in order to set the current memory section

@section eMIOS_Pwm_LLD_H_REF_2
Violates MISRA 2004 Advisory Rule 19.15, :  Repeated include files,  Precautions shall be taken in
order to prevent the contents of a header file being included twice This is not a violation since
all header files are protected against multiple inclusions

@section eMIOS_Pwm_LLD_H_REF_3
Violates MISRA 2004 Advisory Rule MISRA 2004 Rules 1.2, 1.4 and 5.1 : Identifier clash
All compiler used to validate the code can make the difference between two symbols
*/
#ifndef EMIOS_PWM_LLD_H
#define EMIOS_PWM_LLD_H

#ifdef __cplusplus
extern "C"{
#endif

/*===============================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
===============================================================================================*/
/*lint -e537 */
/** @file eMIOS_Pwm_LLD.h
    @note Violates MISRA 2004 Advisory Rule 19.15, See @ref eMIOS_Pwm_LLD_H_REF_2 */
#include "Std_Types.h"
/*lint -restore */


/*===============================================================================================
                               SOURCE FILE VERSION INFORMATION
===============================================================================================*/
/** @remarks Covers BSW00374, BSW00379, BSW00318 */
#define PWM_VENDOR_ID_EMIOS_LLD_H            43
#define PWM_MODULE_ID_EMIOS_LLD_H            121
/*lint -e621 */
/** @file eMIOS_Pwm_LLD.h
    @note Violates MISRA 2004 Advisory Rule 1.2, 1.4 and 5.1 : See @ref eMIOS_Pwm_LLD_H_REF_3 */
#define PWM_AR_MAJOR_VERSION_EMIOS_LLD_H     3
#define PWM_AR_MINOR_VERSION_EMIOS_LLD_H     0
#define PWM_AR_PATCH_VERSION_EMIOS_LLD_H     0
#define PWM_SW_MAJOR_VERSION_EMIOS_LLD_H     2
#define PWM_SW_MINOR_VERSION_EMIOS_LLD_H     0
#define PWM_SW_PATCH_VERSION_EMIOS_LLD_H     0
/*lint -restore */


/*===============================================================================================
                                      FILE VERSION CHECKS
===============================================================================================*/
/* Check if source file and Std_Types.h are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((PWM_AR_MAJOR_VERSION_EMIOS_LLD_H != STD_TYPES_AR_MAJOR_VERSION) || \
         (PWM_AR_MINOR_VERSION_EMIOS_LLD_H != STD_TYPES_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of eMIOS_Pwm_LLD.h and Std_Types.h are different"
    #endif
#endif


/*===============================================================================================
                                           CONSTANTS
===============================================================================================*/


/*===============================================================================================
                                       DEFINES AND MACROS
===============================================================================================*/


/*===============================================================================================
                                             ENUMS
===============================================================================================*/


/*===============================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
===============================================================================================*/

/*===============================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
===============================================================================================*/
#define PWM_START_CONFIG_DATA_UNSPECIFIED
/*lint -save -e961 -e537 -e451 */
/** @file eMIOS_Pwm_LLD.h
    @note Violates MISRA 2004 Advisory Rule 19.15, See @ref eMIOS_Pwm_LLD_H_REF_2 */
#include "MemMap.h"
/*lint -restore */

#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
    /**
    @brief   array used for reverse translation between Hw channel and Logical channel
             used to call the logical channel notification in the hw channel ISR

    */
    extern VAR(Pwm_ChannelType, PWM_VAR) Pwm_EMIOS_LLD_RevHardwareTable[ PWM_EMIOS_HW_CHANNELS ];
#endif

#define PWM_STOP_CONFIG_DATA_UNSPECIFIED
/*lint -save -e961 -e537 -e451 */
/** @file eMIOS_Pwm_LLD.h
    @note Violates MISRA 2004 Advisory Rule 19.15, See @ref eMIOS_Pwm_LLD_H_REF_2 */
#include "MemMap.h"
/*lint -restore */

/*===============================================================================================
                                     FUNCTION PROTOTYPES
===============================================================================================*/
#define PWM_START_SEC_CODE
/*lint -save -e961 -e537 -e451 */
/** @file eMIOS_Pwm_LLD.h
    @note Violates MISRA 2004 Advisory Rule 19.1,19.15: See @ref eMIOS_Pwm_LLD_H_REF_1,
    eMIOS_Pwm_LLD_H_REF_2 */
#include "MemMap.h"
/*lint -restore */

/**
@brief   Service for initializing the hardware timer module (low level)
@details This function initializes all the configured hardware channels as per the
         configured mode
         - puts the channel in GPIO mode
         - disables the interrupt corresponding to Emios channel
         - ulear pending interrupt flag for the channel
         - enables/disables the Freeze Mode
         - clears the (pending) interrupt flag corresponding to Emios channel
         - get the Period that the current UC is using and also calculates the dutycycle
         - update registers A and B with the dutycycle and period value for the configured mode
         - force a match on B register for OPWFMB mode
         - force a match on A register for OPWMB and OPWMT modes
         - write trigger delay to alternate A register for OPWMT mode and offset to A register
           for OPWMB and OPWMT modes
         - FLAG assigned to DMA request and FLAG event is enabled for OPWMT mode
         - FLAG event is disabled for OPWMB and OPWFMB modes
         - sets the prescaler value
         - enable prescaler which will start the internal counter, for Counter Bus


@param[in] ConfigPtr - pointer to PWM top configuration structure

@remarks Covers   PWM009, PWM018, PWM020, PWM052, PWM062, PWM080


@remarks Implements   DPWM03005
*/
FUNC (void, PWM_CODE) EMIOS_Pwm_LLD_Init
                      (
                          P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr
                      );


/**
@brief   This function deinitializes all eMIOS channels assigned to PWM
@details This function
         - sets the channel output to the configured Idle state
         - Reset Timer control register, Internal Counter, A, B registers
         - clears the (pending) interrupt flag corresponding to Emios channel

@remarks Covers PWM011, PWM012, PWM062

@remarks Implements DPWM03001
*/
#if (PWM_DE_INIT_API == STD_ON)
    FUNC (void, PWM_CODE) EMIOS_Pwm_LLD_DeInit(void);
#endif


/**
@brief   This function sets the dutycycle for the specified eMIOS channel
@details This function:
         - disable the interrupt and clear the interrupt flag
         - sets the A register with value 0 for OPWFMB mode for 0% dutycycle
         - sets the A and B registers with value 0 for OPWMB mode for 0% dutycycle
         - sets the A and B registers with value 1 for OPWMT mode for 0% dutycycle
         - sets the A register with value period for OPWFMB mode for 100% dutycycle
         - sets the A register with 0 and B register with period for OPWMB mode for
           100% dutycycle
         - sets the A register with 1 and B register with period+1 for OPWMT mode for
           100% dutycycle
         - for dutycycle not equal to 0% and 100%, FLAG event is enabled
         - sets the A register with value dutycycle for OPWFMB mode
         - sets the A register with value offset+1 and B register with dutycycle+offset
           for OPWMB mode
         - sets the A register with value offset+1 and B register with
           (dutycycle + offset) % period for OPWMT mode

@param[in]     LogicalChannelNumber - pwm channel id
@param[in]     DutyCycle     - pwm dutycycle value 0x0000 for 0% ... 0x8000 for 100%
@param[in]     useSection    - critical section for logical channel
@note      EMIOS_Pwm_LLD_SetDutyCycle is used by EMIOS_Pwm_LLD_SetCounterBus
           it is enabled when at least one of the APIs is enabled

@remarks Covers PWM013, PWM014, PWM016, PWM024, PWM058, PWM059, PWM062, PWM082, PWM086

@remarks Implements DPWM03006
*/
#if ((PWM_SET_DUTY_CYCLE_API == STD_ON) || (PWM_SETCOUNTERBUS_API == STD_ON))
FUNC (void, PWM_CODE) EMIOS_Pwm_LLD_SetDutyCycle
                      (
                          VAR(Pwm_ChannelType, AUTOMATIC) LogicalChannelNumber,
                          VAR(uint16, AUTOMATIC) DutyCycle,
                          VAR(uint8,  AUTOMATIC) useSection
                      );
#endif


/**
@brief   This function sets the period and the dutycycle for the specified eMIOS channel
@details This function is applicable for mode OPWFMB
         - disable the interrupt and clear the interrupt flag
         - sets the A register with value 0 and B register with period for 0% dutycycle
         - sets the A and B registers with value period for 100% dutycycle
         - for dutycycle not equal to 0% and 100% set the A register with value dutycycle
           and B register with value period

@param[in]     LogicalChannelNumber - pwm channel id
@param[in]     Period        - pwm signal period value
@param[in]     DutyCycle     - pwm dutycycle value 0x0000 for 0% ... 0x8000 for 100%

@remarks Covers PWM083, PWM062, PWM059, PWM086, PWM024, PWM076

@remarks Implements DPWM03008
*/
#if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
FUNC (void, PWM_CODE) EMIOS_Pwm_LLD_SetPeriodAndDuty
                      (
                          VAR(Pwm_ChannelType, AUTOMATIC) LogicalChannelNumber,
                          VAR(Pwm_PeriodType,  AUTOMATIC) Period,
                          VAR(uint16,          AUTOMATIC) DutyCycle
                      );
#endif


/**
@brief   This function sets the generated eMIOS channel to the idle value configured
@details This function
         - puts the channel in High or Low state by writing to the Control Register
           based on the configured Idle state
         - puts the Emios channel into GPIO mode

@param[in]     LogicalChannelNumber - pwm channel id

@remarks Covers PWM084, PWM062, PWM021

@remarks Implements DPWM03007
*/
#if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
FUNC (void, PWM_CODE) EMIOS_Pwm_LLD_SetOutputToIdle
                      (
                          VAR(Pwm_ChannelType, AUTOMATIC) LogicalChannelNumber
                      );
#endif


/**
@brief   This function returns the pwm signal output state
@details This function returns the PWM Channel state as High or Low

@param[in]     LogicalChannelNumber - pwm channel id

@return        Pwm_OutputStateType - pwm signal output logic value
               - PWM_LOW - The output state of PWM channel is low
               - PWM_HIGH - The output state of PWM channel is high

@remarks Covers PWM085, PWM062, PWM022

@remarks Implements DPWM03004
*/
#if (PWM_GET_OUTPUT_STATE_API == STD_ON)
FUNC (Pwm_OutputStateType, PWM_CODE) EMIOS_Pwm_LLD_GetOutputState
                                     (
                                         VAR(Pwm_ChannelType, AUTOMATIC) LogicalChannelNumber
                                     );
#endif


/**
@brief   This function disables the user notifications
@details This function
         - enables the notification
         - sets the Edge select bit in control register if notification is both edges
         - clears the Edge select bit in control register if notification is both edges
         - clears the interrupt flag and enables the FLAG event for OPWMB and OPWFMB modes
         - clear interrupt flag in Status register and clear the DMA bit in
           Control register for OPWMT mode


@param[in]     LogicalChannelNumber - pwm channel id
@param[in]     Notification  - notification type to be enabled

@remarks Covers PWM112, PWM113, PWM064, PWM051, PWM062, PWM024, PWM081

@remarks Implements DPWM03003
*/
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
FUNC (void, PWM_CODE) EMIOS_Pwm_LLD_EnableNotification
                      (
                          VAR(Pwm_ChannelType, AUTOMATIC) LogicalChannelNumber,
                          VAR(Pwm_EdgeNotificationType, AUTOMATIC) Notification
                      );
#endif


/**
@brief   This function disables the user notifications
@details This function
         - disables the notification
         - disables the FEN bit in Control register for OPWMB and OPWFMB modes
         - clear interrupt flag in Status register and Set the DMA bit in
           Control register for OPWMT mode

@param[in]     LogicalChannelNumber - pwm channel id

@remarks Covers PWM062, PWM023

@remarks Implements DPWM03002
*/
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
FUNC (void, PWM_CODE) EMIOS_Pwm_LLD_DisableNotification
                      (
                          VAR(Pwm_ChannelType, AUTOMATIC) LogicalChannelNumber
                      );
#endif


/**
@brief   Implementation specific function to set the frequency of pwm channel
         running on PWM_MODE_OPWMB or PWM_MODE_OPWMT mode
@details This function
         - changes the counter bus from Bus A to Bus Diverse or vice versa
         - Bus selection bits will be configured in Control register
         - update dutycycle to the configured default value

@param[in] LogicalChannelNumber - pwm channel id
@param[in] Bus           - the eMIOS bus to change to

@remarks Covers PWM062, PWM023,PWM_CUSTOM001

@remarks Implements   DPWM03009
*/
#if (PWM_SETCOUNTERBUS_API == STD_ON)
FUNC (void, PWM_CODE) EMIOS_Pwm_LLD_SetCounterBus
                      (
                          VAR(Pwm_ChannelType, AUTOMATIC) LogicalChannelNumber,
                          VAR(uint32, AUTOMATIC)          Bus
                      );
#endif


/**
@brief   Implementation specific function to set the state of the PWM pin as requested
         for the current cycle
@details This function is useful to to set the state of the PWM pin as requested
         for the current cycle and continues
         with normal PWM operation from the next cycle
         - OPWFMB: if the passed state is Active, force a match on B Register otherwise
           force a match on A Register
         - OPWMB or OPWMT: if the passed state is Active, force a match on A Register
           otherwise force a match on B Register
         - the force match is done by setting the FORCMA and FORCMB bits is Control Register

@param[in] LogicalChannelNumber - pwm channel id
@param[in] State           - Active/Inactive state of the channel

@remarks Covers PR-MCAL-3173

@remarks Implements   DPWM03010
*/
#if (PWM_SETCHANNELOUTPUT_API == STD_ON)
FUNC (void, PWM_CODE) EMIOS_Pwm_LLD_SetChannelOutput
                      (
                          VAR(Pwm_ChannelType, AUTOMATIC) LogicalChannelNumber,
                          VAR(Pwm_StateType, AUTOMATIC)          State
                      );
#endif


/**
@brief Implementation specific function to set the channel prescaler.
@details This function is useful to set the value of the channel prescaler.
         For this purpose, the following actions are taken for each configured channel
         running on internal counter bus:
         - write 0 at both GPREN bit in EMIOSMCR register and UCPREN bit in EMIOSC[n] register,
           thus disabling prescalers;
         - write the desired value for prescaling rate at UCPRE[0:1] bits in EMIOSC[n] register;
         - enable channel prescaler by writing 1 at UCPREN bit in EMIOSC[n] register;
         - enable global prescaler by writing 1 at GPREN bit in EMIOSMCR register.

@param[in] Prescaler - prescaler type

@remarks Covers PR-MCAL-3199

@remarks Implements   DPWM03011
*/
#if (PWM_DUAL_CLOCK_MODE == STD_ON)
FUNC (void, PWM_CODE) EMIOS_Pwm_LLD_SelectPrescaler
                      (
                          VAR(Pwm_SelectPrescalerType, AUTOMATIC) Prescaler
                      );
#endif

#ifdef PWM_FEATURE_OPWMT
    #if (PWM_FEATURE_OPWMT == STD_ON)
/**
@brief   Implementation specific function to set the trigger delay  for  pwm channel
         running on PWM_MODE_OPWMT mode
         - write trigger delay to alternate A register for OPWMT mode 
        
@param[in] ChannelNumber - pwm channel id
@param[in] State         - triggerdelay

@remarks Covers       PR-MCAL-3234
@remarks Implements   DPWM07050
*/
#if (PWM_SET_TRIGGER_DELAY_API == STD_ON)
FUNC (void, PWM_CODE) EMIOS_Pwm_LLD_SetTriggerDelay
                      (
                          VAR(Pwm_ChannelType, AUTOMATIC) LogicalChannelNumber,
                          VAR(uint16, AUTOMATIC)  TriggerDelay
                      );

#endif
#endif
#endif

#define PWM_STOP_SEC_CODE
/*lint -save -e961 -e537 -e451 */
/** @file eMIOS_Pwm_LLD.h
    @note Violates MISRA 2004 Advisory Rule 19.1,19.15: See @ref eMIOS_Pwm_LLD_H_REF_1,
    eMIOS_Pwm_LLD_H_REF_2 */
#include "MemMap.h"
/*lint -restore */


#ifdef __cplusplus
}
#endif


#endif   /* EMIOS_PWM_LLD_H */
