/**
@file    eMIOS_Pwm_LLD_CfgEx.h
@version 2.0.0

@brief   AUTOSAR Pwm - Pwm Emios exported types and defines.
@details Pwm Emios exported types and defines used for configuration.

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

#ifndef EMIOS_PWM_LLD_CfgEx_H
#define EMIOS_PWM_LLD_CfgEx_H

#ifdef __cplusplus
extern "C"{
#endif

/*===============================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
===============================================================================================*/
#include "Std_Types.h"


/*===============================================================================================
                               SOURCE FILE VERSION INFORMATION
===============================================================================================*/
/** @remarks Covers BSW00374, BSW00379, BSW00318 */
#define PWM_VENDOR_ID_EMIOS_LLD_CFGEX_H            43
#define PWM_MODULE_ID_EMIOS_LLD_CFGEX_H            121
#define PWM_AR_MAJOR_VERSION_EMIOS_LLD_CFGEX_H     3
#define PWM_AR_MINOR_VERSION_EMIOS_LLD_CFGEX_H     0
#define PWM_AR_PATCH_VERSION_EMIOS_LLD_CFGEX_H     0
#define PWM_SW_MAJOR_VERSION_EMIOS_LLD_CFGEX_H     2
#define PWM_SW_MINOR_VERSION_EMIOS_LLD_CFGEX_H     0
#define PWM_SW_PATCH_VERSION_EMIOS_LLD_CFGEX_H     0


/*===============================================================================================
                                      FILE VERSION CHECKS
===============================================================================================*/

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Std_Types.h are of the same Autosar version */
    #if ((PWM_AR_MAJOR_VERSION_EMIOS_LLD_CFGEX_H != STD_TYPES_AR_MAJOR_VERSION) || \
         (PWM_AR_MINOR_VERSION_EMIOS_LLD_CFGEX_H != STD_TYPES_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of eMIOS_Pwm_LLD_CfgEx.h and Std_Types.h are different"
    #endif
#endif


/*===============================================================================================
                                           CONSTANTS
===============================================================================================*/


/*===============================================================================================
                                       DEFINES AND MACROS
===============================================================================================*/



/*
 * This should be based on defines from Reg_eSys_EMIOS_Pwm.h but this file
 * inclusion must be avoided in order to avoid exporting all the EMIOS
 * internals to the user
 */

 /**
     @brief   Modulus Up Counter with internal source
  */
#define PWM_MODE_MC                0x00000010UL
 /**
     @brief   Modulus Up Counter Buffered with internal source
  */
#define PWM_MODE_MCB               0x00000050UL
 /**
     @brief   OPWFMB Buffered with Flag on B Match (period)
  */
#define PWM_MODE_OPWFMB            0x00000058UL
 /**
     @brief   Buffered with Flag on B Match (period)
  */
#define PWM_MODE_OPWMB             0x00000060UL
 /**
     @brief   Output Pulse Width Modulation with Trigger
  */
#define PWM_MODE_OPWMT             0x00000026UL
 /**
     @brief   Bus select: counter bus[A]
  */
#define PWM_BUS_A                  0x00000000UL
 /**
     @brief   Bus select: channels [0,7]: counter busB, channels [8,15]:
                                          counter busC, channels [16,23]: counter busD
  */
#define PWM_BUS_DIVERSE            0x00000200UL
 /**
     @brief   Bus select: internal counter
  */
#define PWM_BUS_INTERNAL_COUNTER   0x00000600UL
 /**
     @brief   Bus select mask
  */
#define PWM_BUS_MASK               0x00000600UL
 /**
     @brief   Initialization option to set the channel prescaler value to 1
  */
#define PWM_PRES_1                 0x00000000UL
 /**
     @brief   Initialization option to set the channel prescaler value to 2
  */
#define PWM_PRES_2                 0x04000000UL
 /**
     @brief   Initialization option to set the channel prescaler value to 3
  */
#define PWM_PRES_3                 0x08000000UL
 /**
     @brief   Initialization option to set the channel prescaler value to 4
  */
#define PWM_PRES_4                 0x0C000000UL
 /**
     @brief   Initialization option to enable freeze mode for the channel
  */
#define PWM_FREEZE_ENABLE          0x80000000UL
 /**
     @brief   Channel 24 index
  */
#define PWM_EMIOS_CH_24            24UL


/*===============================================================================================
                                             ENUMS
===============================================================================================*/


/*===============================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
===============================================================================================*/

/**
@brief   EMIOS HW channel id type, make sure it is the same type as Pwm_ChannelType

@remarks Implements DPWM01020
*/
typedef uint8 Pwm_HwChannelType;


/**
@brief   eMIOS unified channel control register value

@remarks Implements DPWM01020
*/
typedef uint32 Pwm_EmiosCtrlParamType;


/**
@brief EMIOS IP specific channel configuration structure for the PWM functionality
@remarks Covers PWM111, PWM061
@remarks Implements DPWM05005
*/
typedef struct
{
    CONST(Pwm_HwChannelType, PWM_CONST) Pwm_HwChannelID;/**< @brief eMIOS HW channel id */
    CONST(uint32,      PWM_CONST)               Pwm_Emios_ModuleAddr; /** @brief Module used from Emios*/
    CONST(uint32,      PWM_CONST)               Pwm_Emios_ChannelAddr;/** @brief Channel used from Emios*/
    CONST(Pwm_EmiosCtrlParamType, PWM_CONST) Pwm_ParamValue;/**< @brief EMIOSC[n] control */
#if (PWM_DUAL_CLOCK_MODE == STD_ON)
    CONST(uint32, PWM_CONST) Pwm_Prescaler_Alternate;/**< @brief prescaler value */
#endif
    CONST(Pwm_PeriodType, PWM_CONST) Pwm_Offset;/**< @brief leading edge of the output pulse */

#ifdef PWM_FEATURE_OPWMT
    #if (PWM_FEATURE_OPWMT == STD_ON)
    CONST(Pwm_PeriodType, PWM_CONST) Pwm_TriggerDelay;/**< @brief delay of trigger generation */
    CONST(boolean, PWM_CONST) Pwm_OffsetTriggerDelayAdjust;/**< @brief delay of trigger delay adjust */
    #endif
#endif

} Pwm_EMIOS_ChannelConfigType;



/*===============================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
===============================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /* EMIOS_PWM_LLD_CfgEx_H */
