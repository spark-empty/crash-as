/**
@file    Pwm_LLD.h
@version 2.0.0

@brief   AUTOSAR Pwm - Pwm LLD API.
@details Pwm LLD API.

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

@section Pwm_LLD_h_REF_1
Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
Pwm LLD layer need to implement function-like macros to hide implementation specifics
from the upper layers.

*/


#ifndef PWM_LLD_H
#define PWM_LLD_H

#ifdef __cplusplus
extern "C"{
#endif

/*===============================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
===============================================================================================*/
#include "eMIOS_Pwm_LLD.h"
#include "eMIOS_Pwm_LLD_CfgEx.h"
#include "Reg_eSys_EMIOS.h"
/*===============================================================================================
                               SOURCE FILE VERSION INFORMATION
===============================================================================================*/
/**
@{
@brief Parameters that shall be published within the Pwm driver header file and also in the
       module's description file
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define PWM_VENDOR_ID_LLD_H            43
#define PWM_MODULE_ID_LLD_H            121
#define PWM_AR_MAJOR_VERSION_LLD_H     3
#define PWM_AR_MINOR_VERSION_LLD_H     0
#define PWM_AR_PATCH_VERSION_LLD_H     0
#define PWM_SW_MAJOR_VERSION_LLD_H     2
#define PWM_SW_MINOR_VERSION_LLD_H     0
#define PWM_SW_PATCH_VERSION_LLD_H     0
/**@}*/


/*===============================================================================================
                                      FILE VERSION CHECKS
===============================================================================================*/


#if (PWM_VENDOR_ID_LLD_H != PWM_VENDOR_ID_EMIOS_LLD_H)
    #error "Pwm_LLD.h and eMIOS_Pwm_LLD.h have different vendor ids"
#endif


#ifdef CHECK_AUTOSAR_VERSION
    #if ((PWM_AR_MAJOR_VERSION_LLD_H != PWM_AR_MAJOR_VERSION_EMIOS_LLD_H) || \
         (PWM_AR_MINOR_VERSION_LLD_H != PWM_AR_MINOR_VERSION_EMIOS_LLD_H) || \
         (PWM_AR_PATCH_VERSION_LLD_H != PWM_AR_PATCH_VERSION_EMIOS_LLD_H))
    #error "AutoSar Version Numbers of Pwm_LLD.h and eMIOS_Pwm_LLD.h are different"
    #endif
#endif


#if ((PWM_SW_MAJOR_VERSION_LLD_H != PWM_SW_MAJOR_VERSION_EMIOS_LLD_H) || \
    (PWM_SW_MINOR_VERSION_LLD_H != PWM_SW_MINOR_VERSION_EMIOS_LLD_H)  || \
    (PWM_SW_PATCH_VERSION_LLD_H != PWM_SW_PATCH_VERSION_EMIOS_LLD_H))
#error "Software Version Numbers of Pwm_LLD.h and eMIOS_Pwm_LLD.h are different"
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

/*lint -save -e961 -e537 -e451 */
#define PWM_START_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"
/*lint -restore */

    /**
    @brief pointer to the top level configuration structure - valid only when the driver is
           in the initialized state
    */
    extern P2CONST(Pwm_ConfigType, PWM_VAR, PWM_APPL_CONST) Pwm_Cfg_Ptr;

/*lint -save -e961 -e537 -e451 */
#define PWM_STOP_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"
/*lint -restore */

/*===============================================================================================
                                     FUNCTION PROTOTYPES
===============================================================================================*/
/*lint -save -e961 -e537 -e451 */
/** @file Pwm_LLD.h
    @note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
                                                  before "#include": See @ref Pwm_LLD_h_REF_1 */
#define PWM_START_SEC_CODE
#include "MemMap.h"
    /**
    @brief  Mapping between low level layer and high level layer for Pwm_LLD_Init function.
    @note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined:
                                                  See @ref Pwm_LLD_h_REF_1
    */
    #define Pwm_LLD_Init(ConfigPtr)   EMIOS_Pwm_LLD_Init(ConfigPtr)


#if (PWM_DE_INIT_API == STD_ON)

    /**
    @brief  Mapping between low level layer and high level layer for Pwm_LLD_DeInit function.
    @remarks Covers PWM080
    @note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined:
                                                  See @ref Pwm_LLD_h_REF_1
    */
    #define Pwm_LLD_DeInit()          EMIOS_Pwm_LLD_DeInit()
#endif


#if (PWM_SET_DUTY_CYCLE_API == STD_ON)
    /**
    @brief  Mapping between low level layer and high level layer for
            Pwm_LLD_SetDutyCycle function.
    @remarks Covers PWM082
    @note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined:
                                                  See @ref Pwm_LLD_h_REF_1
    */
    #define Pwm_LLD_SetDutyCycle( ch_id, DutyCycle)  EMIOS_Pwm_LLD_SetDutyCycle \
                                                     ( \
                                                         ch_id, \
                                                         DutyCycle, \
                                                         (uint8)STD_ON \
                                                     )
#endif


#if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
    /**
    @brief  Mapping between low level layer and high level layer for
            Pwm_LLD_SetPeriodAndDuty function.
    @remarks Covers PWM083
    @note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined:
                                                  See @ref Pwm_LLD_h_REF_1
    */
    #define Pwm_LLD_SetPeriodAndDuty(ch_id, Period, DutyCycle)  EMIOS_Pwm_LLD_SetPeriodAndDuty \
                                                                ( \
                                                                    ch_id, \
                                                                    Period, \
                                                                    DutyCycle \
                                                                )
#endif


#if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
    /**
    @brief  Mapping between low level layer and high level layer for
            Pwm_LLD_SetOutputToIdle function.
    @remarks Covers PWM084
    @note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined:
                                                  See @ref Pwm_LLD_h_REF_1
    */
    #define Pwm_LLD_SetOutputToIdle(ch_id)  EMIOS_Pwm_LLD_SetOutputToIdle(ch_id)
#endif


#if (PWM_GET_OUTPUT_STATE_API == STD_ON)
    /**
    @brief  Mapping between low level layer and high level layer for
            Pwm_LLD_GetOutputState function.
    @remarks Covers PWM085
    @note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined:
                                                  See @ref Pwm_LLD_h_REF_1
    */
    #define Pwm_LLD_GetOutputState(ch_id)   EMIOS_Pwm_LLD_GetOutputState(ch_id)
#endif


#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
    /**
    @brief  Mapping between low level layer and high level layer for
            Pwm_LLD_EnableNotification function.
    @remarks Covers PWM112
    @note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined:
                                                  See @ref Pwm_LLD_h_REF_1
    */
    #define Pwm_LLD_EnableNotification( ch_id, Notification) EMIOS_Pwm_LLD_EnableNotification \
                                                             ( \
                                                                 ch_id, \
                                                                 Notification \
                                                             )
    /**
    @brief  Mapping between low level layer and high level layer for
            Pwm_LLD_DisableNotification function.
    @remarks Covers PWM113
    @note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined:
                                                  See @ref Pwm_LLD_h_REF_1
    */
    #define Pwm_LLD_DisableNotification(ch_id) EMIOS_Pwm_LLD_DisableNotification (ch_id)
#endif


#if (PWM_SETCOUNTERBUS_API == STD_ON)
    /**
    @brief  Mapping between low level layer and high level layer for
            Pwm_LLD_SetCounterBus function.
    @remarks Covers PWM_CUSTOM001
    @note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined:
                                                  See @ref Pwm_LLD_h_REF_1
    */
    #define Pwm_LLD_SetCounterBus( ch_id, Bus )   EMIOS_Pwm_LLD_SetCounterBus( ch_id, Bus )
#endif

#if (PWM_SETCHANNELOUTPUT_API == STD_ON)
    /**
    @brief  Mapping between low level layer and high level layer for
            Pwm_LLD_SetChannelOutput function.
    @remarks Covers PR-MCAL-3173
    @note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined:
                                                  See @ref Pwm_LLD_h_REF_1
    */
    #define Pwm_LLD_SetChannelOutput(ch_id, State)  EMIOS_Pwm_LLD_SetChannelOutput(ch_id, State)
#endif

#if (PWM_DUAL_CLOCK_MODE == STD_ON)
    /**
    @brief  Mapping between low level layer and high level layer for
            Pwm_LLD_SelectPrescaler function.
    @remarks Covers PR-MCAL-3199
    @note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined:
                                                  See @ref Pwm_LLD_h_REF_1
    */
    #define Pwm_LLD_SelectPrescaler( Prescaler )   EMIOS_Pwm_LLD_SelectPrescaler( Prescaler )
#endif

#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
    FUNC (void, PWM_CODE) Pwm_LLD_ProcessInterrupt( VAR(Pwm_ChannelType, AUTOMATIC) ch_id );
#endif

#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
    FUNC (void, PWM_CODE) EMIOS_Pwm_LLD_ProcessInterrupt( VAR(Pwm_ChannelType, AUTOMATIC) hw_ch_id );
#endif

/*lint -save -e961 -e537 -e451 */
/** @file Pwm_LLD.h
    @note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
                                                  before "#include": See @ref Pwm_LLD_h_REF_1 */
#define PWM_STOP_SEC_CODE
#include "MemMap.h"
/*lint -restore */




#ifdef __cplusplus
}
#endif

#endif /* PWM_LLD_H*/
