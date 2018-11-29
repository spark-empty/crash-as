/**
    @file    Siu_Icu_LLD.h
    @version 2.0.0

    @brief   AUTOSAR Icu - Brief description.
    @details Detailed description.

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
@file    Siu_Icu_LLD.h
*/

#ifndef SIU_ICU_LLD_H
#define SIU_ICU_LLD_H


/**
@page misra_violations MISRA-C:2004 violations

@section Siu_Icu_LLD_h_REF_1
Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
This violation is due to function like macros defined for register operations.
Function like macros are used to reduce code complexity.

@section SIUL_Icu_LLD_h_REF_2 - MISRA-C:2004  19.15 Precautions shall be taken in order to prevent
         the contents of a
header file being included twice
This is not a violation since all header files are protected against multiple inclusions.
*/


#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/* MISRA-C:2004  19.15 WARNING : Refer to SIUL_Icu_LLD_h_REF_1 above */
/*lint -save -e537*/
#include "Std_Types.h"
#include "Reg_Macros.h"
#include "Icu_Cfg.h"
/*lint -restore*/

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** @remarks Covers BSW00374, BSW00379, BSW00318 */
#define SIU_ICU_LLD_VENDOR_ID            43

#define SIU_ICU_LLD_AR_MAJOR_VERSION     3
#define SIU_ICU_LLD_AR_MINOR_VERSION     0
#define SIU_ICU_LLD_AR_PATCH_VERSION     0
#define SIU_ICU_LLD_SW_MAJOR_VERSION     2
#define SIU_ICU_LLD_SW_MINOR_VERSION     0
#define SIU_ICU_LLD_SW_PATCH_VERSION     0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if header file and Std_Types.h file are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((SIU_ICU_LLD_AR_MAJOR_VERSION != STD_AR_MAJOR_VERSION) || \
         (SIU_ICU_LLD_AR_MINOR_VERSION != STD_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Siu_Icu_LLD.h and Std_Types.h are different"
    #endif
#endif

/* Check if header file and Icu_Cfg.h file are of the same vendor */
#if (SIU_ICU_LLD_VENDOR_ID != ICU_VENDOR_ID_CFG)
#error "Siu_Icu_LLD.h and Icu_Cfg.h have different vendor IDs"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((SIU_ICU_LLD_AR_MAJOR_VERSION != ICU_AR_MAJOR_VERSION_CFG) || \
         (SIU_ICU_LLD_AR_MINOR_VERSION != ICU_AR_MINOR_VERSION_CFG) || \
         (SIU_ICU_LLD_AR_PATCH_VERSION != ICU_AR_PATCH_VERSION_CFG))
    #error "AutoSar Version Numbers of Siu_Icu_LLD.h and Icu_Cfg.h are different"
    #endif
#endif
/* Check if source file and ICU header file are of the same Software version */
#if ((SIU_ICU_LLD_SW_MAJOR_VERSION != ICU_SW_MAJOR_VERSION_CFG) || \
     (SIU_ICU_LLD_SW_MINOR_VERSION != ICU_SW_MINOR_VERSION_CFG) || \
     (SIU_ICU_LLD_SW_PATCH_VERSION != ICU_SW_PATCH_VERSION_CFG))
#error "Software Version Numbers of Siu_Icu_LLD.h and Icu_Cfg.h are different"
#endif


/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
/**
@{
@brief   SIU_IRQ_CHANNEL_MASK - used for masking IRQ Channels
@remarks Beside IRQ Channels, SIU provides also NMI capabilities. In order to not alter NMI settings
         all the operations will be masked.
*/
#define SIU_IRQ_CHANNEL_MASK            ((uint32)0x0000FFFF)
/**@}*/
/**
@{
@brief   SIU_IRQ4_IRQ15_MASK - used for masking IRQ Channels 4 ..15
@remarks In order to not alter NMI settings and channels IRQ0, IRQ1,IRQ2, IRQ3
         all the operations will be masked.
*/
#define SIU_IRQ4_IRQ15_MASK            ((uint32)0x0000FFF0)
/**@}*/

/**
@note  Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined -
       See @ref Siu_Icu_LLD_h_REF_1
*/
/*lint -save -e961*/
#define SIU_CHANNEL_MASK(hwChannel)  (((uint32)BIT0 << (uint32)(hwChannel))  & SIU_IRQ_CHANNEL_MASK)
/*lint -restore*/

/**
@{
@brief SIU_EIISR_ESEL - compute EIISR.ESEL bitfield value for a given channel
@note  Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
       - See @ref Siu_Icu_LLD_h_REF_1
*/
/*lint -save -e961*/
#define SIU_EIISR_ESEL(hwChannel, value)  (((uint32)(value)) << ((uint32)(hwChannel) << (uint32)1U))
/*lint -restore*/
/**@}*/

/**
@{
@brief Define that indicates that the  source for the external interrupts is selected from
       SIU_ISEL1 register
*/
#define SIU_ISEL1_REG               (uint32)0x00
/**@}*/

/**
@{
@brief Define that indicates that the  source for the external interrupts is selected from
       SIU_ISEL2 register
*/
#define SIU_ISEL2_REG               (uint32)0x01
/**@}*/
/**
@{
@brief Define that indicates that the  source for the external interrupts is selected from
       SIU_ISEL2A register
*/
#define SIU_ISEL2A_REG              (uint32)0x02
/**@}*/

/**
@{
@brief Defines that specifies the input port when the source is selected from ISEL1 reg
*/
#define SIU_ISEL1_PB                (uint32)0x00
#define SIU_ISEL1_PC                (uint32)0x01
#define SIU_ISEL1_PD                (uint32)0x02
/**@}*/

/**
@{
@brief Defines that specifies the input port when the source is selected from ISEL2 reg
*/
#define SIU_ISEL2_PE                (uint32)0x00
#define SIU_ISEL2_PF                (uint32)0x01
#define SIU_ISEL2_PG                (uint32)0x02
/**@}*/

/**
@{
@brief Defines that specifies the input port when the source is selected from ISEL2A reg
*/
#define SIU_ISEL2A_PH               (uint32)0x00
#define SIU_ISEL2A_PJ               (uint32)0x01
#define SIU_ISEL2A_PK               (uint32)0x02
/**@}*/

/**
@{
@brief Specific SIU Channel parameters
@remarks defines for bitfields used in Icu_ParamValue member for ICU IRQ Channels
*/
#define SIU_ISEL_REG_PARAM_SHIFT    (uint32)(2)
#define SIU_ISEL_REG_PARAM_MASK     (uint32)(BIT3|BIT2)
#define SIU_ISEL_PORT_PARAM_SHIFT   (uint32)(0)
#define SIU_ISEL_PORT_PARAM_MASK    (uint32)(BIT1|BIT0)
/**@}*/

/*==================================================================================================
                                             ENUMS
==================================================================================================*/
typedef enum
{
    SIU_FALLING_EDGE = 0x0U,
    SIU_RISING_EDGE  = 0x1U,
    SIU_BOTH_EDGES   = 0x2U
} SIU_ActivationType;

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
typedef uint32 SIU_Icu_IRQ_ParamType;
typedef uint8  SIU_Icu_IRQ_ChannelType;

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
#define ICU_START_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

#define ICU_STOP_CONFIG_DATA_UNSPECIFIED
/* MISRA-C:2004  19.1 VIOLATION : Refer to REF 1 above*/
/*lint -save -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/


/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
#define ICU_START_SEC_CODE
/* MISRA-C:2004  19.1 VIOLATION : Refer to REF 1 above*/
/*lint -save -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

/**
@brief      SIU_LLD_InitChannel
@details    Initialize the ICU Channel
@param[in]  ParamValue
@param[in]  hwChannel - IRQ HW Channel
*/
FUNC (void, ICU_CODE) SIU_LLD_InitChannel(CONST(SIU_Icu_IRQ_ParamType, AUTOMATIC) ParamValue,
                                      CONST(SIU_Icu_IRQ_ChannelType, AUTOMATIC) hwChannel);

/**
@brief      SIU_LLD_DeInit
@details    Deinitialize the ICU Channel
@param[in]  hwChannel   - IRQ HW Channel
*/
FUNC (void, ICU_CODE) SIU_LLD_DeInitChannel(VAR(SIU_Icu_IRQ_ChannelType, AUTOMATIC) hwChannel);

#if (ICU_SET_MODE_API == STD_ON)
/**
@brief      SIU_LLD_SetSleepMode
@details    Sets the ICU Channel mode
@param[in]  hwChannel      - IRQ HW Channel
@param[in]  WakeUpEnabled  - channel wakeup feature is enabled
*/
FUNC (void, ICU_CODE) SIU_LLD_SetSleepMode(VAR(SIU_Icu_IRQ_ChannelType, AUTOMATIC) hwChannel,
                                       VAR(boolean, AUTOMATIC) WakeUpEnabled);

/**
@brief      SIU_LLD_SetNormalMode
@details    Sets the ICU channel to normal mode
@param[in]  hwChannel   - IRQ HW Channel
@param[in]  NotificationActive          - channel notification is activated
*/
FUNC (void, ICU_CODE) SIU_LLD_SetNormalMode(VAR(SIU_Icu_IRQ_ChannelType, AUTOMATIC) hwChannel,
                                        VAR(boolean, AUTOMATIC) NotificationActive);
#endif  /* ICU_SET_MODE_API  */

/**
@brief      SIU_LLD_SetActivationCondition
@details    Set the activation condition for the given SIU IRQ Channel
@param[in]  hwChannel   - IRQ HW Channel
@param[in]  Activation       - activation condition
*/
FUNC (void, ICU_CODE) SIU_LLD_SetActivationCondition(
                                            VAR(SIU_Icu_IRQ_ChannelType, AUTOMATIC) hwChannel,
                        VAR(SIU_ActivationType, AUTOMATIC) Activation);

/**
@brief      SIU_LLD_DisableNotification
@details    Disable notification for IRQ HW Channel
@param[in]  hwChannel   - IRQ HW Channel
*/
FUNC (void, ICU_CODE) SIU_LLD_DisableNotification(
                                         VAR(SIU_Icu_IRQ_ChannelType, AUTOMATIC) hwChannel);

/**
@brief      SIU_LLD_EnableNotification
@details    Enable notification for IRQ HW Channel
@param[in]  hwChannel   - IRQ HW Channel
*/
FUNC (void, ICU_CODE) SIU_LLD_EnableNotification(VAR(SIU_Icu_IRQ_ChannelType, AUTOMATIC) hwChannel);

#if (ICU_GET_INPUT_STATE_API == STD_ON)
/**
@brief      SIU_LLD_GetInputState
@details    Gets the input state of ICU hardware channel
@param[in]  hwChannel - IRQ HW Channel
@retval     ICU_ACTIVE - Icu_InputStateType
@retval     ICU_IDLE   - Icu_InputStateType
*/
FUNC (boolean, ICU_CODE) SIU_LLD_GetInputState(VAR(SIU_Icu_IRQ_ChannelType, AUTOMATIC) hwChannel);
#endif  /* ICU_GET_INPUT_STATE_API */

/**
@brief      Siu_Icu_LLD_ProcessInterrupt
@details
@param[in]  hwChannel - IRQ HW Channel
*/
FUNC (void, ICU_CODE) Siu_Icu_LLD_ProcessInterrupt(CONST(uint8, AUTOMATIC) hwChannel);


#define ICU_STOP_SEC_CODE
/* MISRA-C:2004  19.1 VIOLATION : Refer to REF 1 above*/
/*lint -save -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif

#endif  /* SIU_ICU_LLD_H */
