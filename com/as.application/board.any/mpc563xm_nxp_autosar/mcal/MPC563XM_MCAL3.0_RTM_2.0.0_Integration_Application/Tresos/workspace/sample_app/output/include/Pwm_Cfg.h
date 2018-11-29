
 /**
     @file    Pwm_Cfg.h
     @version 2.0.0

     @brief   AUTOSAR Pwm - Pwm configuration file.
     @details API flags and structure declarations.

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

#ifndef PWM_CFG_H
#define PWM_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@{
@brief Parameters that shall be published within the Pwm driver header file and also in the
       module's description file
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define PWM_VENDOR_ID_CFG_H             43
#define PWM_MODULE_ID_CFG_H             121

#define PWM_AR_MAJOR_VERSION_CFG_H      3
#define PWM_AR_MINOR_VERSION_CFG_H      0
#define PWM_AR_PATCH_VERSION_CFG_H      0

#define PWM_SW_MAJOR_VERSION_CFG_H      2
#define PWM_SW_MINOR_VERSION_CFG_H      0
#define PWM_SW_PATCH_VERSION_CFG_H      0
/**@}*/

/*==================================================================================================
                                       DEFINES AND MACROS

    Exception - the follwing macros/types are used in the included files and must be defined
                before the include in order to take effect
==================================================================================================*/

/**
@brief   selects between 16bit or 24bit emios implementation
@remarks Covers
@remarks Implements
*/
#define PWM_EMIOS_16_BITS_VARIANT   (STD_OFF)

/**
@brief   Specifies if OPWMT feature/mode is available
@remarks Covers
@remarks Implements
*/
#define PWM_FEATURE_OPWMT    (STD_OFF)

/**
@brief   Switch to indicate that Pwm_SetClockMode API is supported
@remarks Covers     PR-MCAL-3199
@remarks Implements DPWM06042
*/
#define PWM_DUAL_CLOCK_MODE    (STD_OFF)

#ifdef PWM_EMIOS_16_BITS_VARIANT
 #if  (PWM_EMIOS_16_BITS_VARIANT == STD_ON)

    /* 16bit EMIOS */

    /**
    @brief   channel period typedef
    @remarks Covers     PWM107
    @remarks Implements DPWM01021
    */
    typedef uint16 Pwm_PeriodType;

 #else

    /* 24bit EMIOS */

    /**
    @brief   channel period typedef
    @remarks Covers     PWM107
    @remarks Implements DPWM01021
    */
    typedef uint32 Pwm_PeriodType;

 #endif

#else

 #error "Unknown EMIOS type, PWM_EMIOS_16_BITS_VARIANT is undefined";

#endif



/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "eMIOS_Pwm_LLD_CfgEx.h"
#include "Reg_eSys_EMIOS_CfgEx.h"

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and PWM configuration header file are of the same vendor */
#if (PWM_VENDOR_ID_CFG_H != PWM_VENDOR_ID_EMIOS_LLD_CFGEX_H)
    #error "Pwm_Cfg.h and eMIOS_Pwm_LLD_CfgEx.h have different vendor ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and PWM configuration header file are of the same Autosar version */
    #if ((PWM_AR_MAJOR_VERSION_CFG_H != PWM_AR_MAJOR_VERSION_EMIOS_LLD_CFGEX_H) || \
         (PWM_AR_MINOR_VERSION_CFG_H != PWM_AR_MINOR_VERSION_EMIOS_LLD_CFGEX_H) || \
         (PWM_AR_PATCH_VERSION_CFG_H != PWM_AR_PATCH_VERSION_EMIOS_LLD_CFGEX_H))
    #error "AutoSar Version Numbers of Pwm_Cfg.h and eMIOS_Pwm_LLD_CfgEx.h are different"
    #endif
#endif

/* Check if source file and PWM configuration header file are of the same software version */
#if ((PWM_SW_MAJOR_VERSION_CFG_H != PWM_SW_MAJOR_VERSION_EMIOS_LLD_CFGEX_H) || \
     (PWM_SW_MINOR_VERSION_CFG_H != PWM_SW_MINOR_VERSION_EMIOS_LLD_CFGEX_H)  || \
     (PWM_SW_PATCH_VERSION_CFG_H != PWM_SW_PATCH_VERSION_EMIOS_LLD_CFGEX_H))
#error "Software Version Numbers of Pwm_Cfg.h and eMIOS_Pwm_LLD_CfgEx.h are different"
#endif


/* Check if source file and EMIOS configuration header file are of the same vendor */
#if (PWM_VENDOR_ID_CFG_H != REG_ESYS_EMIOS_CFGEX_H_VENDOR_ID)
    #error "Pwm_Cfg.h and Reg_eSys_EMIOS_CfgEx.h have different vendor ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and PWM configuration header file are of the same Autosar version */
    #if ((PWM_AR_MAJOR_VERSION_CFG_H != REG_ESYS_EMIOS_CFGEX_H_AR_MAJOR_VERSION) || \
         (PWM_AR_MINOR_VERSION_CFG_H != REG_ESYS_EMIOS_CFGEX_H_AR_MINOR_VERSION) || \
         (PWM_AR_PATCH_VERSION_CFG_H != REG_ESYS_EMIOS_CFGEX_H_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Pwm_Cfg.h and Reg_eSys_EMIOS_CfgEx.h are different"
    #endif
#endif

/* Check if source file and PWM configuration header file are of the same software version */
#if ((PWM_SW_MAJOR_VERSION_CFG_H != REG_ESYS_EMIOS_CFGEX_H_SW_MAJOR_VERSION) || \
     (PWM_SW_MINOR_VERSION_CFG_H != REG_ESYS_EMIOS_CFGEX_H_SW_MINOR_VERSION)  || \
     (PWM_SW_PATCH_VERSION_CFG_H != REG_ESYS_EMIOS_CFGEX_H_SW_PATCH_VERSION))
#error "Software Version Numbers of Pwm_Cfg.h and Reg_eSys_EMIOS_CfgEx.h are different"
#endif


/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       PLATFORM SPECIFIC DEFINES AND MACROS
==================================================================================================*/


/* Platform specific DET errors */

/**
@brief   generated when the configured offset for the OPWMB channel is >= than the period of the
         associated MCB channel
@remarks Implements
@remarks Covers     PWM002, PWM006
*/
#define PWM_E_OPWMB_CHANNEL_OFFSET_VALUE   0x1AU


/**
@brief   generated when the requested offset value plus the current requested dutycycle leads to
         programming event B over the Period value leading to unexpected behavior of the pwm signal
@remarks Implements
@remarks Covers     PWM002, PWM006
*/
#define PWM_E_OPWMB_CHANNEL_OFFSET_DUTYCYCLE_RANGE     0x1BU


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/


/**
@brief   Switch to indicate that Pwm_DeInit API is supported
@remarks Covers     PWM080, PWM_FSL001
@remarks Implements DPWM06017
*/
#define PWM_DE_INIT_API             (STD_ON)


/**
@brief   Switch to indicate that Pwm_GetOutputState API is supported
@remarks Covers     PWM085, PWM127
@remarks Implements DPWM06032
*/
#define PWM_GET_OUTPUT_STATE_API    (STD_ON)


/**
@brief   Switch to indicate that Pwm_SetDutyCycle API is supported
@remarks Covers     PWM082, PWM128
@remarks Implements DPWM06030
*/
#define PWM_SET_DUTY_CYCLE_API      (STD_ON)


/**
@brief   Switch to indicate that Pwm_SetOutputToIdle API is supported
@remarks Covers     PWM084, PWM129
@remarks Implements DPWM06031
*/
#define PWM_SET_OUTPUT_TO_IDLE_API  (STD_ON)


/**
@brief   Switch to indicate that Pwm_SetPeriodAndDuty API is supported
@remarks Covers     PWM083, PWM130
@remarks Implements DPWM06033
*/
#define PWM_SET_PERIOD_AND_DUTY_API (STD_ON)


/**
@brief   Switch to indicate that Pwm_GetVersionInfo API is supported
@remarks Covers     PWM135
@remarks Implements DPWM06034
*/
#define PWM_VERSION_INFO_API         (STD_ON)


/**
@brief   Switch to indicate that Pwm_SetCounterBus API is supported
@remarks Covers     PWM_CUSTOM001
@remarks Implements DPWM06034
*/
#define PWM_SETCOUNTERBUS_API         (STD_OFF)


/**
@brief   Switch to indicate that Pwm_SetChannelOutput API is supported
@remarks Covers PR-MCAL-3173
@remarks Implements DPWM06051
*/
#define PWM_SETCHANNELOUTPUT_API         (STD_OFF)


/**
@brief   Switch for enabling the development error detection.
@remarks Covers     PWM131, PWM003
@remarks Implements DPWM06018
*/
#define PWM_DEV_ERROR_DETECT (STD_ON)


/**
@brief   Switch to indicate that register A is updated at dutycycle change for OPWMT mode
@remarks Covers     PWM_CUSTOM002

*/
#define PWM_CHANGE_REGISTER_A_SWITCH    (STD_OFF)


/**
@brief   Switch for enabling the update of the duty cycle parameter at the end of the current period
@remarks Covers     PWM132
@remarks Implements DPWM06020
*/
#define PWM_DUTYCYCLE_UPDATED_ENDPERIOD   (STD_ON)


/**
@brief   Switch to indicate that the notifications are supported
@remarks Covers     PWM133
@remarks Implements DPWM06026
*/
#define PWM_NOTIFICATION_SUPPORTED        (STD_ON)


/**
@brief   Switch for enabling the update of the period parameter at the end of the current period
@remarks Covers     PWM134
@remarks Implements DPWM06028
*/
#define PWM_DUTY_PERIOD_UPDATED_ENDPERIOD (STD_ON)

/**
@brief   Specifies the InstanceId of this module instance.
         If only one instance is present it shall have the Id 0.
         Not used in the current implementation
@remarks Covers     PWM122
@remarks Implements DPWM06023
*/
#define PWM_INDEX    (0U)




/**
    @brief Pwm Channels symbolic names
    @details Get All Symbolic Names from configuration tool
    @remarks Covers PWM120
@{
*/

/** @brief Symbolic Names for configured channels */
#define Pwm_Led1         (Pwm_ChannelType)0



/* Symbolic names of hardware channnels */


/** @brief Symbolic Names for configured channels */

#define Pwm_Led1_EMIOS_0_CH_9    (Pwm_ChannelType)EMIOS_0_CH_9
/**@}*/

/**
    @brief ISRs configured for Pwm channels
    @details Macros for Pwm channels used in ISR
    @remarks Covers PWM115
@{
*/

    
#define PWM_EMIOS_0_CH_9_ISR_USED
    
/**@}*/


/**
    @brief emios modules available on this platform
*/
#define PWM_EMIOS_MODULES_CFG        (1UL)
/**
    @brief emios channels available on EMIOS 0
*/
#define PWM_EMIOS_A_HW_CHANNELS_CFG  (24UL)


/**
    @brief This constant specifies the total number of eMIOS channels
              It's used to reserve global ram variables used for each individual pwm channel
*/

#if (PWM_EMIOS_MODULES_CFG == 1UL)

#define PWM_EMIOS_HW_CHANNELS    PWM_EMIOS_A_HW_CHANNELS_CFG

#else

#define PWM_EMIOS_HW_CHANNELS    (PWM_EMIOS_MODULES_CFG * 32U)

#endif



/**
@brief      Output state of a PWM channel
@details PWM_HIGH - The output state of PWM channel is HIGH
         \n PWM_LOW - The output state of PWM channel LOW
@remarks Covers     PWM108
@remarks Implements DPWM01019
*/
typedef enum
{
    PWM_LOW = 0,
    PWM_HIGH
} Pwm_OutputStateType;

/**
@brief   Definition of the type of edge notification of a PWM channel
@details PWM_RISING_EDGE - Notification will be called when a rising edge occurs on the PWM output signal.
         \n PWM_FALLING_EDGE - Notification will be called when a falling edge occurs on the PWM output signal.
         \n PWM_BOTH_EDGES - Notification will be called when either a rising edge or falling edge occur on the PWM output signal.
@remarks Covers     PWM109
@remarks Implements DPWM01017
*/
typedef enum
{
    PWM_RISING_EDGE = 0,
    PWM_FALLING_EDGE,
    PWM_BOTH_EDGES
} Pwm_EdgeNotificationType;

/**
@brief   Defines class of PWM channel
@details PWM_VARIABLE_PERIOD - The PWM channel has a variable period. The duty cycle and the period can be changed.
         \n PWM_FIXED_PERIOD - The PWM channel has a fixed period. Only the duty cycle can be changed.
         \n PWM_FIXED_PERIOD_SHIFTED - The PWM channel has a fixed shifted period. Impossible to change it ( only if supported by hardware)
@remarks Covers     PWM110
@remarks Implements DPWM01015
*/
typedef enum
{
    PWM_VARIABLE_PERIOD = 0,
    PWM_FIXED_PERIOD,
    PWM_FIXED_PERIOD_SHIFTED
} Pwm_ChannelClassType;

#if (PWM_SETCHANNELOUTPUT_API == STD_ON)
/**
@brief   Defines state of PWM channel
@details PWM_ACTIVE - The PWM pin will be in the same state of configured polarity
         \n PWM_INACTIVE - The PWM pin will be in the opposite state of configured polarity
@remarks Covers PR-MCAL-3173
@remarks Implements DPWM01025
*/
typedef enum
{
    PWM_ACTIVE = 0,
    PWM_INACTIVE
} Pwm_StateType;
#endif

/**
@brief   IP used to implement this channel
@details This channel is implemented using one eMIOS HW unified channel
@remarks Implements DPWM01021
*/
typedef enum
{
    PWM_EMIOS_CHANNEL = 0 /**< @brief This channel is implemented using one eMIOS HW unified channel */
} Pwm_IpType;


/*==================================================================================================
                              STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/**
@brief   channel id typedef, used as type for both logical and hw channel ids.
@remarks Covers     PWM106
@remarks Implements DPWM01016
*/
typedef uint8 Pwm_ChannelType;



/**
@brief   channel notification typedef

@remarks Implements DPWM01018
*/
typedef void (*Pwm_NotifyType)(void);


/**
@brief Low level channel configuration structure
@details Pwm channel eMIOS specific configuration structure
@remarks Implements DPWM05001
*/
typedef struct
{
    CONST(Pwm_EMIOS_ChannelConfigType, PWM_CONST)  EmiosCfg; /**< @brief Pwm channel eMIOS specific configuration structure */

} Pwm_LLD_ChannelConfigType;



/**
@brief Prescaler type
@details This represents the prescaler parameter type to be used
@remarks Covers PR-MCAL-3199
@remarks Implements DPWM01026
*/
#if (PWM_DUAL_CLOCK_MODE == STD_ON)
typedef enum
    {
        PWM_NORMAL = 0,
        PWM_ALTERNATE
    } Pwm_SelectPrescalerType;
#endif



/**
@brief   pwm channel high level configuration structure
@details Defines the class of PWM channel
         \n Pwm_ChannelClassValue - channel type: Variable/Fixed period
         \n Pwm_Polarity - Pwm signal polarity:   High or low
         \n Pwm_DefaultPeriodValue - Default value for period
         \n Pwm_DefaultDutyCycleValue - Default value for duty cycle: [0-0x8000] (0-100%)
         \n Pwm_IdleState - Pwm signal idle state: High or low
         \n Pwm_Channel_Notification - Pointer to notification function
         \n IpType - the IP used to implement this specific Pwm channel
         \n SpecificCfg - Pwm channel IP specific parameters
@remarks Covers PWM061
@remarks Implements DPWM05001
*/
typedef struct {

    /* PWM generic parameters, IP independent */
    CONST(Pwm_ChannelClassType, PWM_CONST)       Pwm_ChannelClassValue; /**< @brief channel type: Variable/Fixed period */
    CONST(Pwm_OutputStateType,  PWM_CONST)       Pwm_Polarity; /**< @brief Pwm signal polarity:   High or low  */
    CONST(Pwm_PeriodType,       PWM_CONST)       Pwm_DefaultPeriodValue; /**< @brief Default value for period */
    CONST(uint16,               PWM_CONST)       Pwm_DefaultDutyCycleValue; /**< @brief Default value for duty cycle: [0-0x8000] (0-100%)*/
    CONST(Pwm_OutputStateType,  PWM_CONST)       Pwm_IdleState; /**< @brief Pwm signal idle state: High or low */
    CONST(Pwm_NotifyType,       PWM_CONST)       Pwm_Channel_Notification; /**< @brief Pointer to notification function   */
    CONST(Pwm_IpType,           PWM_CONST)       IpType; /**< @brief the IP used to implement this specific Pwm channel */

    /* IP specific parameters */
    CONST(Pwm_LLD_ChannelConfigType, PWM_CONST)  SpecificCfg; /**< @brief Pwm channel IP specific parameters */

} Pwm_ChannelConfigType;



/**
@brief   pwm high level configuration structure
@details This is the type of data structure containing the initialization data for the PWM driver.
         \n ChannelCount - number of configured channels
         \n ChannelsPtr - pointer to the configured channels
@remarks Covers     PWM111
@remarks Implements DPWM05004
*/
typedef struct {

    CONST(Pwm_ChannelType,       PWM_CONST)   ChannelCount; /**< @brief number of configured channels */
    CONST(Pwm_ChannelConfigType, PWM_CONST)  *ChannelsPtr; /**< @brief pointer to the configured channels */

} Pwm_ConfigType;


 /*==================================================================================================
                                  GLOBAL VARIABLE DECLARATIONS
 ==================================================================================================*/

/**
    @brief   declaration of config sets for PB configuration
*/
#ifndef PWM_PRECOMPILE_SUPPORT

#define PWM_INIT_CONFIG_PB_DEFINES \
extern CONST(Pwm_ConfigType, PWM_CONST) PwmChannelConfigSet_0;


#endif /* PWM_PRECOMPILE_SUPPORT */


 /*==================================================================================================
                                      FUNCTION PROTOTYPES
 ==================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif    /*PWM_CFG_H*/



