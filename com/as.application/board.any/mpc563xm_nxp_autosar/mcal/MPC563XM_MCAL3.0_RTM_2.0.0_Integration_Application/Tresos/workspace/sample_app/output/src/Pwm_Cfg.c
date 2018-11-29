
 /**
     @file    Pwm_Cfg.c
     @version 2.0.0

     @brief   AUTOSAR Pwm - Pwm precompile configuration file.
     @details precompile configuration structure instance.

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
/**
@page misra_violations MISRA-C:2004 violations

@section Pwm_Cfg_C_REF_1
Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
before "#include"
MemMap.h included after each section define in order to set the current memory section

@section Pwm_Cfg_C_REF_2
Violates MISRA 2004 Advisory Rule 8.10,All declarations and definitions of objects or functions
at file scope shall have internal linkage unless external linkage is required.

*/

#ifdef __cplusplus
extern "C" {
#endif


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Pwm.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@{
@brief Parameters that shall be published within the Pwm driver header file and also in the
       module's description file
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define PWM_VENDOR_ID_PC_CFG_C             43
#define PWM_MODULE_ID_PC_CFG_C             121

#define PWM_AR_MAJOR_VERSION_PC_CFG_C      3
#define PWM_AR_MINOR_VERSION_PC_CFG_C      0
#define PWM_AR_PATCH_VERSION_PC_CFG_C      0

#define PWM_SW_MAJOR_VERSION_PC_CFG_C      2
#define PWM_SW_MINOR_VERSION_PC_CFG_C      0
#define PWM_SW_PATCH_VERSION_PC_CFG_C      0
/**@}*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/


#if (PWM_VENDOR_ID_PC_CFG_C != PWM_VENDOR_ID)
    #error "Pwm_Cfg.c and Pwm.h have different vendor ids"
#endif


#ifdef CHECK_AUTOSAR_VERSION
    #if ((PWM_AR_MAJOR_VERSION_PC_CFG_C != PWM_AR_MAJOR_VERSION) || \
         (PWM_AR_MINOR_VERSION_PC_CFG_C != PWM_AR_MINOR_VERSION) || \
         (PWM_AR_PATCH_VERSION_PC_CFG_C != PWM_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Pwm_Cfg.c and Pwm.h are different"
    #endif
#endif


#if ((PWM_SW_MAJOR_VERSION_PC_CFG_C != PWM_SW_MAJOR_VERSION) || \
     (PWM_SW_MINOR_VERSION_PC_CFG_C != PWM_SW_MINOR_VERSION)  || \
     (PWM_SW_PATCH_VERSION_PC_CFG_C != PWM_SW_PATCH_VERSION))
#error "Software Version Numbers of Pwm_Cfg.c and Pwm.h are different"
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

/*lint -save -e961 -e537 -e451 */
/* put Pwm_InitChannel structure into specified section */
#define PWM_START_SEC_CONST_UNSPECIFIED
/** @file Pwm_Cfg.c
    @note Violates MISRA 2004 Advisory Rule 19.1 : See @ref Pwm_Cfg_C_REF_1*/
#include "MemMap.h"
/*lint -restore */


#ifdef PWM_PRECOMPILE_SUPPORT




/**
    @brief Prototype of User Notifications
*/


extern void Pwm_Led1Notification(void);




/*  --- EMIOS Clock Tree Debug information ---


Clock source: MCU


McuClockReferencePointFrequency  : 6.0E7 Hz
EmiosA_LowPower : false
McuEMIOS0_Global_DIV : 60.0
EMIOS0_ClockFrequency : 1000000.0 Hz

*/




/**
    @brief Number of configured Pwm channels
*/
#define PWM_CONF_CHANNELS_PC  (Pwm_ChannelType)1



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
    /** @file Pwm_Cfg.c
    @note Violates MISRA 2004 Advisory Rule 8.10 : See @ref Pwm_Cfg_C_REF_2*/
CONST(Pwm_ChannelConfigType, PWM_CONST) Pwm_Channels_PC[PWM_CONF_CHANNELS_PC] =
{
{
PWM_FIXED_PERIOD,/* channel type: Variable/Fixed period */
PWM_HIGH,/* signal polarity */


/* --- Unified Channel clock debug information ---
PwmPeriodDefaultUnits:Period_in_seconds
PwmPeriodDefault:0.02
this_unified_channel_period_in_ticks:5000

emios unified channel clock source: INTERNAL COUNTER
this_unified_channel_prescaler_value:4
this_unified_channel_clock_frequency:250000.0 Hz
this_unified_channel_clock_period:4.0E-6
configured_channel_period:0.02 seconds
configured_channel_freq:50.0 Hz

    
period_error:0.0 seconds
    


*/
(Pwm_PeriodType)0x1388, /* 5000 ticks - default period value */
(uint16)0x4000,/* default duty cycle value */
PWM_LOW,/* signal idle state */
        &Pwm_Led1Notification, /* Pwm notification function */

PWM_EMIOS_CHANNEL, /* channel ip type */
/* PWM eMIOS channel specific configuration structure */
    {{
             (Pwm_ChannelType)Pwm_Led1_EMIOS_0_CH_9,/* assigned eMIOS HW channel id */
    /*EMiOS  channel Addr*/
                
                   (uint32)0xc3fa0000UL, /*EMiOS 0 Module Addr*/
           
           (uint32)0xc3fa0140UL, /*EMiOS 0 channel Addr*/
           (Pwm_EmiosCtrlParamType)(PWM_BUS_INTERNAL_COUNTER | PWM_MODE_OPWFMB   | PWM_FREEZE_ENABLE

 | PWM_PRES_4
 
 
    
 ),

0U,/* leading edge of the PWM output pulse in OPWMB, OPWMT modes */
#ifdef PWM_FEATURE_OPWMT
    #if (PWM_FEATURE_OPWMT == STD_ON)
    (Pwm_PeriodType)0,/* delay for generating the trigger event in OPWMT mode */
    #endif
#endif
}}
}


};

/**
@brief   pwm high level configuration structure
@details This is the type of data structure containing the initialization data for the PWM driver.
         \n ChannelCount - number of configured channels
         \n ChannelsPtr - pointer to the configured channels
@remarks Covers     PWM111
@remarks Implements DPWM05004
*/
CONST(Pwm_ConfigType, PWM_CONST) Pwm_InitConfig_PC =
{
    PWM_CONF_CHANNELS_PC,  /* number of configured PWM channels in the array */
    Pwm_Channels_PC        /* pointer to array of channes */
};



#endif  /* end #ifdef PWM_PRECOMPILE_SUPPORT*/

/*lint -save -e961 -e537 -e451 */
/* stop putting configuration structure into section PWM_STOP_SEC_CONST_UNSPECIFIED */
#define PWM_STOP_SEC_CONST_UNSPECIFIED
/** @file Pwm_Cfg.c
    @note Violates MISRA 2004 Advisory Rule 19.1 : See @ref Pwm_Cfg_C_REF_1*/
#include "MemMap.h"
/*lint -restore */


 /*==================================================================================================
                                        GLOBAL VARIABLES
 ==================================================================================================*/

 /*==================================================================================================
                                    LOCAL FUNCTION PROTOTYPES
 ==================================================================================================*/

 /*==================================================================================================
                                        LOCAL FUNCTIONS
 ==================================================================================================*/

 /*==================================================================================================
                                        GLOBAL FUNCTIONS
 ==================================================================================================*/


#ifdef __cplusplus
}
#endif

