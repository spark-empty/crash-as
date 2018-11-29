[!CODE!]
 /**
     @file    Pwm_PBcfg.c
     @version 2.0.0

     @brief   AUTOSAR Pwm - Pwm post-build configuration file.
     @details post-build configuration structure instances.

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

@section Pwm_PBcfg_C_REF_1
Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
before "#include"
MemMap.h included after each section define in order to set the current memory section

@section Pwm_PBcfg_C_REF_2
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
#define PWM_VENDOR_ID_PB_CFG_C             43
#define PWM_MODULE_ID_PB_CFG_C             121

#define PWM_AR_MAJOR_VERSION_PB_CFG_C      3
#define PWM_AR_MINOR_VERSION_PB_CFG_C      0
#define PWM_AR_PATCH_VERSION_PB_CFG_C      0

#define PWM_SW_MAJOR_VERSION_PB_CFG_C      2
#define PWM_SW_MINOR_VERSION_PB_CFG_C      0
#define PWM_SW_PATCH_VERSION_PB_CFG_C      0
/**@}*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/


#if (PWM_VENDOR_ID_PB_CFG_C != PWM_VENDOR_ID)
    #error "Pwm_PBCfg.c and Pwm.h have different vendor ids"
#endif


#ifdef CHECK_AUTOSAR_VERSION
    #if ((PWM_AR_MAJOR_VERSION_PB_CFG_C != PWM_AR_MAJOR_VERSION) || \
         (PWM_AR_MINOR_VERSION_PB_CFG_C != PWM_AR_MINOR_VERSION) || \
         (PWM_AR_PATCH_VERSION_PB_CFG_C != PWM_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Pwm_PBCfg.c and Pwm.h are different"
    #endif
#endif


#if ((PWM_SW_MAJOR_VERSION_PB_CFG_C != PWM_SW_MAJOR_VERSION) || \
     (PWM_SW_MINOR_VERSION_PB_CFG_C != PWM_SW_MINOR_VERSION) || \
     (PWM_SW_PATCH_VERSION_PB_CFG_C != PWM_SW_PATCH_VERSION))
#error "Software Version Numbers of Pwm_PBCfg.c and Pwm.h are different"
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
#define PWM_START_CONFIG_DATA_UNSPECIFIED
/** @file Pwm_PBcfg.c
    @note Violates MISRA 2004 Advisory Rule 19.1 : See @ref Pwm_PBcfg_C_REF_1*/
#include "MemMap.h"
/*lint -restore */


#ifndef PWM_PRECOMPILE_SUPPORT




/**
    @brief Prototype of User Notifications
*/
[!NOCODE!]
[!INCLUDE "Pwm_NotifyCheck_Src_PB.m"!]
[!ENDNOCODE!]

[!NOCODE!]
[!CALL "PwmNotifyCheck_PB"!]
[!ENDNOCODE!]


[!NOCODE!]
[!INCLUDE "Pwm_Clock_Tree.m"!]
[!ENDNOCODE!]



/**
    @brief Number of configured Pwm channels
*/
[!VAR "Value"="num:i(count(PwmChannelConfigSet/*[1]/PwmChannel/*))"!]

[!IF "PwmNonAUTOSAR/PwmEnableDualClockMode"!]
[!VAR "SelectPresApi" = "1"!][!//
[!ELSE!]
[!VAR "SelectPresApi" = "0"!][!//
[!ENDIF!][!//
    /** @file Pwm_PBcfg.c
    @note Violates MISRA 2004 Advisory Rule 8.10 : See @ref Pwm_PBcfg_C_REF_2*/
[!LOOP "(PwmChannelConfigSet/*)"!]
    [!VAR "Value1"="num:i(count(PwmChannel/*))"!]
#define PWM_CONF_CHANNELS_PB_[!"@index"!]  (Pwm_ChannelType)[!"num:i(count(PwmChannel/*))"!]
[!ENDLOOP!]

[!IF "$Value1 != $Value"!][!WARNING!][!"'Number of Channels Configured across different PwmChannelConfigSet are not equal.'"!][!ENDWARNING!]
[!ENDIF!]

[!LOOP "PwmChannelConfigSet/*"!]

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
    /** @file Pwm_PBcfg.c
    @note Violates MISRA 2004 Advisory Rule 8.10 : See @ref Pwm_PBcfg_C_REF_2*/
CONST(Pwm_ChannelConfigType, PWM_CONST) Pwm_Channels_PB_[!"num:i(@index)"!][PWM_CONF_CHANNELS_PB_[!"num:i(@index)"!]] =
{
[!FOR "x" = "0" TO "num:i(count(PwmChannel/*))"!][!//
[!SELECT "PwmChannel/*/PwmChannelId[.=$x]/.."!][!//
{
[!IF "PwmChannelClass= 'PWM_FIXED_PERIOD'"!]PWM_FIXED_PERIOD[!ELSEIF "PwmChannelClass= 'PWM_VARIABLE_PERIOD'"!]PWM_VARIABLE_PERIOD[!ENDIF!],/* channel type: Variable/Fixed period */
[!"PwmPolarity"!],/* signal polarity */

[!NOCODE!]

    [!VAR "PwmPrescaler_val" = "substring-after(PwmPrescaler,'PwmPrescalerDiv')"!]

    [!IF "contains(PwmHwChannel,'EMIOS_0_')"!]
            [!VAR "this_unified_channel_clock_frequency" = "$EMIOS0_ClockFrequency div $PwmPrescaler_val"!]
    [!ELSE!]
        [!IF "contains(PwmHwChannel,'EMIOS_1_')"!]
            [!VAR "this_unified_channel_clock_frequency" = "$EMIOS1_ClockFrequency div $PwmPrescaler_val"!]
        [!ENDIF!]
    [!ENDIF!]


    [!VAR "this_unified_channel_clock_period" = "1 div $this_unified_channel_clock_frequency"!]


    [!IF "PwmPeriodDefaultUnits = 'Period_in_seconds'"!]
        /* the pwm signal period is specified in seconds - perform conversion to ticks */
        [!VAR "this_unified_channel_period_in_ticks" = "num:i(round(PwmPeriodDefault div $this_unified_channel_clock_period))"!]
    [!ELSE!]

        [!IF "PwmPeriodDefaultUnits = 'Period_in_ticks'"!]
            /* the pwm signal period is specified in ticks - nothing to do */
            [!VAR "this_unified_channel_period_in_ticks" = "num:i(PwmPeriodDefault)"!]
        [!ELSE!]
            /* the pwm signal period is specified in frequency (Hz) - convert to ticks */
            [!VAR "this_unified_channel_period_in_ticks" = "num:i(round((1 div PwmPeriodDefault) div $this_unified_channel_clock_period))"!]
        [!ENDIF!]

    [!ENDIF!]


    [!IF "$this_unified_channel_period_in_ticks < 1"!]
        [!ERROR!]
The configured period for channel: [!"PwmChannelId"!] is smaller than 1 tick: [!"$this_unified_channel_period_in_ticks"!]
The plugin performs the conversion from Period_in_seconds or Frequency_in_Hz to ticks.
If the result is smaller than 1 tick then this error message is generated.
To solve this problem change the configured Period_in_seconds / Frequency_in_Hz or change the eMIOS
clock tree settings.
        [!ENDERROR!]
    [!ENDIF!]


    [!IF "$this_unified_channel_period_in_ticks > 16777214"!]
        [!ERROR!]
The configured period for channel: [!"PwmChannelId"!] is larger than 16777214 ticks: [!"$this_unified_channel_period_in_ticks"!]
The plugin performs the conversion from Period_in_seconds or Frequency_in_Hz to ticks.
If the result is larger than 16777214 ticks then this error message is generated.
To solve this problem change the configured Period_in_seconds / Frequency_in_Hz or change the eMIOS
clock tree settings.
        [!ENDERROR!]
    [!ENDIF!]

[!IF "../../../../PwmGeneral/PwmGenerateClockTreeDebugInfo = 'true'"!]
[!CODE!]
/* --- Unified Channel clock debug information ---
PwmPeriodDefaultUnits:[!"PwmPeriodDefaultUnits"!]
PwmPeriodDefault:[!"PwmPeriodDefault"!]
this_unified_channel_period_in_ticks:[!"$this_unified_channel_period_in_ticks"!]
[!IF "EmiosUnifiedChannelBusSelect = 'PWM_BUS_INTERNAL_COUNTER'"!]
emios unified channel clock source: INTERNAL COUNTER
this_unified_channel_prescaler_value:[!"$PwmPrescaler_val"!]
this_unified_channel_clock_frequency:[!"$this_unified_channel_clock_frequency"!] Hz
this_unified_channel_clock_period:[!"$this_unified_channel_clock_period"!]
configured_channel_period:[!"number($this_unified_channel_period_in_ticks) * $this_unified_channel_clock_period"!] seconds
configured_channel_freq:[!"1.0 div (number($this_unified_channel_period_in_ticks) * $this_unified_channel_clock_period)"!] Hz
[!IF "PwmPeriodDefaultUnits = 'Frequency_in_Hz'"!]
frequency_error:[!"(1.0 div (number($this_unified_channel_period_in_ticks) * $this_unified_channel_clock_period)) - number(PwmPeriodDefault)"!] Hz
[!ELSE!]
    [!IF "PwmPeriodDefaultUnits = 'Period_in_seconds'"!]
period_error:[!"(number($this_unified_channel_period_in_ticks) * $this_unified_channel_clock_period) - number(PwmPeriodDefault)"!] seconds
    [!ENDIF!]
[!ENDIF!]
[!ELSE!]
[!IF "EmiosUnifiedChannelBusSelect = 'PWM_BUS_A'"!]emios unified channel clock source: BUS_A
[!ELSE!]emios unified channel clock source: PWM_BUS_DIVERSE[!ENDIF!]
[!ENDIF!]
*/[!ENDCODE!]
[!ENDIF!]
[!ENDNOCODE!]
    (Pwm_PeriodType)[!"num:inttohex($this_unified_channel_period_in_ticks)"!], /* [!"$this_unified_channel_period_in_ticks"!] ticks - default period value */
    (uint16)[!"num:inttohex(PwmDutycycleDefault,4)"!],/* default duty cycle value */
    [!"PwmIdleState"!],/* signal idle state */
        [!IF "(PwmNotification = '') or (PwmNotification = 'NULL_PTR') or (PwmNotification = 'NULL')"!]NULL_PTR[!ELSE!]&[!"PwmNotification"!][!ENDIF!], /* Pwm notification function */

PWM_EMIOS_CHANNEL, /* channel ip type */
/* PWM eMIOS channel specific configuration structure */
    {{
             (Pwm_ChannelType)[!"node:name(.)"!]_[!"PwmHwChannel"!],/* assigned eMIOS HW channel id */
    /*EMiOS  channel Addr*/
    [!VAR "pwm_hw_channel_index" = "0"!][!//
    [!VAR "pwm_hw_channel"="0"!][!//
    [!VAR "pwm_hw_channel_macro"="0"!][!//
    [!VAR "pwm_hw_channel"="PwmHwChannel"!][!//

        [!IF "contains(PwmHwChannel,'EMIOS_0')"!][!//
   (uint32)[!"num:inttohex(num:hextoint(ecu:get('Pwm.EMIOS_0_BaseAddress')))"!]UL, /*EMiOS 0 Module Addr*/
           [!VAR "pwm_hw_channel_index"="substring-after($pwm_hw_channel, 'EMIOS_0_CH_')"!]
           (uint32)[!"num:inttohex(num:hextoint(ecu:get('Pwm.EMIOS_0_BaseAddress')) + (32 + (num:i(number($pwm_hw_channel_index)) * 32)))"!]UL, /*EMiOS 0 channel Addr*/
           [!ELSEIF "contains(PwmHwChannel,'EMIOS_1')"!][!//
   (uint32)[!"num:inttohex(num:hextoint(ecu:get('Pwm.EMIOS_1_BaseAddress')))"!]UL, /*EMiOS 1 Module Addr*/
           [!VAR "pwm_hw_channel_index"="substring-after($pwm_hw_channel, 'EMIOS_1_CH_')"!]
           (uint32)[!"num:inttohex(num:hextoint(ecu:get('Pwm.EMIOS_1_BaseAddress')) + (32 + (num:i(number($pwm_hw_channel_index)) * 32)))"!]UL, /*EMiOS 1 channel Addr*/
        [!ENDIF!][!//
    (Pwm_EmiosCtrlParamType)([!"EmiosUnifiedChannelBusSelect"!] | [!"PwmModeSelect"!]  [!IF "PwmFreezeEnable"!] | PWM_FREEZE_ENABLE[!ENDIF!]
[!IF "contains(PwmModeSelect,'OPWFMB')"!][!//
[!IF "contains(EmiosUnifiedChannelBusSelect,'PWM_BUS_INTERNAL_COUNTER')"!][!//
[!IF "node:exists(PwmPrescaler)"!]
[!IF "PwmPrescaler= 'PwmPrescalerDiv1'"!] | PWM_PRES_1
[!ELSEIF "PwmPrescaler= 'PwmPrescalerDiv2'"!] | PWM_PRES_2
[!ELSEIF "PwmPrescaler= 'PwmPrescalerDiv3'"!] | PWM_PRES_3
[!ELSEIF "PwmPrescaler= 'PwmPrescalerDiv4'"!] | PWM_PRES_4[!ENDIF!]
 [!ELSE!] | 0UL /* prescaler not used */[!ENDIF!]
 [!ENDIF!]
 [!ELSE!] | 0UL /* prescaler not used */[!ENDIF!]   
 ),
[!IF "$SelectPresApi = 1"!][!//
[!IF "contains(PwmModeSelect,'OPWFMB')"!][!//
[!IF "contains(EmiosUnifiedChannelBusSelect,'PWM_BUS_INTERNAL_COUNTER')"!][!//   
[!IF "node:exists(PwmPrescaler_Alternate)"!][!//
[!IF "PwmPrescaler_Alternate= 'PwmPrescalerDiv1'"!]PWM_PRES_1,[!//
[!ELSEIF "PwmPrescaler_Alternate= 'PwmPrescalerDiv2'"!]PWM_PRES_2,[!//
[!ELSEIF "PwmPrescaler_Alternate= 'PwmPrescalerDiv3'"!]PWM_PRES_3,[!//
[!ELSEIF "PwmPrescaler_Alternate= 'PwmPrescalerDiv4'"!]PWM_PRES_4,[!//
[!ENDIF!][!//
[!ELSE!][!//
0UL,
[!ENDIF!][!//            
[!ENDIF!][!//
[!ELSE!][!//
0UL,   
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "contains(PwmModeSelect,'OPWMB')"!][!//
[!IF "((contains(EmiosUnifiedChannelBusSelect,'PWM_BUS_A')) or (contains(EmiosUnifiedChannelBusSelect,'PWM_BUS_DIVERSE')))"!][!//
[!IF "node:exists(PwmOffset)"!](Pwm_PeriodType)[!"PwmOffset"!],/* leading edge of the PWM output pulse in OPWMB, OPWMT modes */
[!ENDIF!][!//
[!ENDIF!][!//
[!ELSE!]
0U,/* leading edge of the PWM output pulse in OPWMB, OPWMT modes */[!ENDIF!]
#ifdef PWM_FEATURE_OPWMT
    #if (PWM_FEATURE_OPWMT == STD_ON)
    [!IF "node:exists(PwmTriggerDelay)"!](Pwm_PeriodType)[!"PwmTriggerDelay"!],/* delay for generating the trigger event in OPWMT mode */
    [!ELSE!](Pwm_PeriodType)0,/* delay for generating the trigger event in OPWMT mode */[!ENDIF!]
    #endif
#endif
    }}
}[!ENDSELECT!][!IF "$x < num:i(count(PwmChannel/*)) - 1"!],/* end channel */[!ENDIF!]
[!ENDFOR!]
};

/**
@brief   pwm high level configuration structure
@details This is the type of data structure containing the initialization data for the PWM driver.
         \n ChannelCount - number of configured channels
         \n ChannelsPtr - pointer to the configured channels
@remarks Covers     PWM111
@remarks Implements DPWM05004
*/
CONST(Pwm_ConfigType, PWM_CONST) [!"@name"!] =
{
    PWM_CONF_CHANNELS_PB_[!"num:i(@index)"!], /* number of configured PWM channels in the array */
    Pwm_Channels_PB_[!"num:i(@index)"!]       /* pointer to array of channes */
};
[!ENDLOOP!]


#endif  /* end #ifndef PWM_PRECOMPILE_SUPPORT*/

/*lint -save -e961 -e537 -e451 */
/* stop putting configuration structure into section PWM_STOP_CONFIG_DATA_UNSPECIFIED */
#define PWM_STOP_CONFIG_DATA_UNSPECIFIED
/** @file Pwm_PBcfg.c
    @note Violates MISRA 2004 Advisory Rule 19.1 : See @ref Pwm_PBcfg_C_REF_1*/
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
[!ENDCODE!]
