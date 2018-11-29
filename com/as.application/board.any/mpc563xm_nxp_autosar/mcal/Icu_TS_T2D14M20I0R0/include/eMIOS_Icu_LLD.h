/**
    @file    eMIOS_Icu_LLD.h
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
@page misra_violations MISRA-C:2004 violations

@section eMIOS_Icu_LLD_h_1
Violates MISRA-C:2004  19.15 Precautions shall be taken in order to prevent the contents of a
header file being included twice
This is not a violation since all header files are protected against multiple inclusions
*/

#ifndef EMIOS_ICU_LLD_H
#define EMIOS_ICU_LLD_H

#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/**
@file  eMIOS_Icu_LLD.h
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref eMIOS_Icu_LLD_h_1
*/
/*lint -save -e537*/
#include "Std_Types.h"
#include "Icu_Cfg.h"
/*lint -restore*/

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@{
@brief   Header file version information
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define EMIOS_ICU_LLD_VENDOR_ID           43
#define EMIOS_ICU_LLD_MODULE_ID           122

#define EMIOS_ICU_LLD_AR_MAJOR_VERSION    3
#define EMIOS_ICU_LLD_AR_MINOR_VERSION    0
#define EMIOS_ICU_LLD_AR_PATCH_VERSION    0
#define EMIOS_ICU_LLD_SW_MAJOR_VERSION    2
#define EMIOS_ICU_LLD_SW_MINOR_VERSION    0
#define EMIOS_ICU_LLD_SW_PATCH_VERSION    0
/**@}*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if eMIOS_Icu_LLD.h file and Std_Types.h file are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((EMIOS_ICU_LLD_AR_MAJOR_VERSION != STD_TYPES_AR_MAJOR_VERSION) || \
         (EMIOS_ICU_LLD_AR_MINOR_VERSION != STD_TYPES_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of eMIOS_Icu_LLD.h and Std_Types.h are different"
    #endif
#endif

/* Check if eMIOS_Icu_LLD.h file and Icu_Cfg.h header file are of the same vendor */
#if (EMIOS_ICU_LLD_VENDOR_ID != ICU_VENDOR_ID_CFG)
#error "eMIOS_Icu_LLD.h and Icu_Cfg.h have different vendor IDs"
#endif

/* Check if eMIOS_Icu_LLD.h file and Icu_Cfg.h file are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((EMIOS_ICU_LLD_AR_MAJOR_VERSION != ICU_AR_MAJOR_VERSION_CFG) || \
         (EMIOS_ICU_LLD_AR_MINOR_VERSION != ICU_AR_MINOR_VERSION_CFG) || \
         (EMIOS_ICU_LLD_AR_PATCH_VERSION != ICU_AR_PATCH_VERSION_CFG))
    #error "AutoSar Version Numbers of eMIOS_Icu_LLD.h and Icu_Cfg.h are different"
    #endif
#endif
/* Check if eMIOS_Icu_LLD.h file and Icu_Cfg.h header file are of the same Software version */
#if ((EMIOS_ICU_LLD_SW_MAJOR_VERSION != ICU_SW_MAJOR_VERSION_CFG) || \
     (EMIOS_ICU_LLD_SW_MINOR_VERSION != ICU_SW_MINOR_VERSION_CFG) || \
     (EMIOS_ICU_LLD_SW_PATCH_VERSION != ICU_SW_PATCH_VERSION_CFG))
    #error "Software Version Numbers of eMIOS_Icu_LLD.h and Icu_Cfg.h are different"
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/**
@brief ID for edge overflow
@details Additional errors that are detected because of specific implementation
         and/or specific hardware properties shall be added in the ICU device specific
         implementation specification. The classification and enumeration shall be compatible
         with the errors listed above.
*/
#define ICU_E_EDGE_OVERFLOW     0x18U

/**
@brief   Define for configuring Falling edge
@details To automatically set the value in the eMios cfg register
*/
#define EMIOS_FALLING_EDGE_PARAM     (uint32)((0x0U << CCR_EDSEL_SHIFT)|(0x0U << CCR_EDPOL_SHIFT))

/**
@brief   Define for configuring Rising edge
@details To automatically set the value in the eMios cfg register
*/
#define EMIOS_RISING_EDGE_PARAM      (uint32)((0x0U << CCR_EDSEL_SHIFT)|(BIT0 << CCR_EDPOL_SHIFT))

/**
@brief   Define for configuring Both edge
@details To automatically set the value in the eMios cfg register
*/
#define EMIOS_BOTH_EDGES_PARAM       (uint32)((BIT0 << CCR_EDSEL_SHIFT)|(0x0U << CCR_EDPOL_SHIFT))

/**
@{
@brief EMIOS unified channel specific control register bits desctiption
@remarks Hardware Dependent Definition - DO NOT CHANGE
*/
#define EMIOS_BUS_A                         (uint32)0x0U
#define EMIOS_BUS_DIVERSE                   (uint32)0x1U
#define EMIOS_BUS_INTERNAL_COUNTER          (uint32)0x3U

#define EMIOS_DIGITAL_FILTER_BYPASSED       (uint32)0U
#define EMIOS_DIGITAL_FILTER_02             (uint32)BIT0
#define EMIOS_DIGITAL_FILTER_04             (uint32)BIT1
#define EMIOS_DIGITAL_FILTER_08             (uint32)BIT2
#define EMIOS_DIGITAL_FILTER_16             (uint32)BIT3

#define EMIOS_PRESCALER_DIVIDE_1            (uint32)0U
#define EMIOS_PRESCALER_DIVIDE_2            (uint32)1U
#define EMIOS_PRESCALER_DIVIDE_3            (uint32)2U
#define EMIOS_PRESCALER_DIVIDE_4            (uint32)3U

#define EMIOS_FREEZE_ENABLE                 (uint32)0x1U
/**@}*/

/**
@{
@brief EMIOS controller register values
*/
/* EMIOS register values */
#define EMIOS_CCR_CLEAR                     (uint32)0x00000000U
#define EMIOS_CADR_CLEAR                    (uint32)0x00000000U
#define EMIOS_INIT_CADR                     (uint32)0x00FFFFFFU
#define EMIOS_CBDR_CLEAR                    (uint32)0x00000000U
#define EMIOS_CCNTR_CLEAR                   (uint32)0x00000000U
#define EMIOS_INIT_CCNTR                    (uint32)0x00000000U
#define EMIOS_CCNTR_INIT                    (uint32)0x00000000U
#define EMIOS_CSR_CLEAR                     (uint32)0xFFFFFFFFU
#define EMIOS_IFER_ENABLE                   (uint32)0x0000FFFFU
/**@}*/

/**
@{
@brief Number of channels on a eMIOS module
*/
#define eMIOS_N_CHANNELS   32
/**@}*/

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*================================================================================================*/
/**
@{
@enum   eMIOS_ChannelModeType
        Type that indicates the channel mode type(Counter mode, Detect mode or Capture mode).
*/
/*================================================================================================*/
typedef enum
{
    /** EMIOS_CHANNEL_MODE_EDGE_DETECT = Mode for detecting edges. */
    EMIOS_CHANNEL_MODE_EDGE_DETECT = 0U,
    /** EMIOS_CHANNEL_MODE_EDGE_COUNTER = Mode for counting edges on configurable edges. */
    EMIOS_CHANNEL_MODE_EDGE_COUNTER,
    /** EMIOS_CHANNEL_MODE_CAPTURE_MODE = Mode for capturing edges. */
    EMIOS_CHANNEL_MODE_CAPTURE_MODE
} eMIOS_ChannelModeType;
/**@}*/

/*================================================================================================*/
/**
@{
@enum  eMIOS_ActivationType
       Type that indicates the channel activation type(Rising, Falling, Both Edges or Opposite 
       Edges).
*/
/*================================================================================================*/
typedef enum
{
    /** EMIOS_OPPOSITE_EDGES = An appropriate action shall be executed when either a falling or
        rising edge occur on the ICU input signal. */
#ifdef SIGNAL_MEASUREMENT_USES_SAIC_MODE
    EMIOS_OPPOSITE_EDGES    = 0x3U,
/* SIGNAL_MEASUREMENT_USES_SAIC_MODE */
#endif   
    /** EMIOS_FALLING_EDGE = An appropriate action shall be executed when a falling edge occurs
        on the ICU input signal. */
    EMIOS_FALLING_EDGE      = 0x0U,
    /** EMIOS_RISING_EDGE = An appropriate action shall be executed when a rising edge occurs on
        the ICU input signal.*/
    EMIOS_RISING_EDGE       = 0x1U,
    /** EMIOS_RISING_EDGE = An appropriate action shall be executed when either a rising or
        falling edge occur on the ICU input signal.*/
    EMIOS_BOTH_EDGES        = 0x2U
} eMIOS_ActivationType;
/**@}*/

/*================================================================================================*/
/**
@{
@enum  eMIOS_OperationMode
       eMIOS Unified Channel Modes of Operation.
       These macros are used in ICU plug-in for specifying the UC mode to be used
*/
/*================================================================================================*/
typedef enum
{
    /** EMIOS_UC_DAOC_MODE = eMIOS channel in default mode */
    EMIOS_UC_UNSPECIFIED_MODE = 0x0U,
    /** EMIOS_UC_DAOC_MODE = eMIOS channel in Double Action Output Compare mode */
    EMIOS_UC_DAOC_MODE,
    /** EMIOS_UC_GPIO_MODE = eMIOS channel in General purpose Input/Output mode */
    EMIOS_UC_GPIO_MODE,
    /** EMIOS_UC_IPM_MODE = eMIOS channel in Input Period Measurement mode */
    EMIOS_UC_IPM_MODE,
    /** EMIOS_UC_IPWM_MODE = eMIOS channel in Input Pulse Width Measurement mode */
    EMIOS_UC_IPWM_MODE,
    /** EMIOS_UC_MC_MODE = eMIOS channel in Modulus Counter mode */
    EMIOS_UC_MC_MODE,
    /** EMIOS_UC_MCB_MODE = eMIOS channel in Modulus Counter Buffered mode */
    EMIOS_UC_MCB_MODE,
    /** EMIOS_UC_OPWMB_MODE = eMIOS channel in Output Pulse Width Modulation Buffered mode */
    EMIOS_UC_OPWMB_MODE,
    /** EMIOS_UC_OPWMT_MODE = eMIOS channel in Output Pulse Width Modulation with Trigger
        mode */
    EMIOS_UC_OPWMT_MODE,
    /** EMIOS_UC_OPWFMB_MODE = eMIOS channel in Output Pulse Width and Frequency
        Modulation Buffered mode*/
    EMIOS_UC_OPWFMB_MODE,
    /** EMIOS_UC_OPWMCB_MODE = eMIOS channel in Output Pulse Width Modulation
        Counter Buffered mode */
    EMIOS_UC_OPWMCB_MODE,
    /** EMIOS_UC_SAIC_MODE = eMIOS channel in Single Action Input Capture mode */
    EMIOS_UC_SAIC_MODE,
    /** EMIOS_UC_SAOC_MODE = eMIOS channel in Single Action Output Capture mode */
    EMIOS_UC_SAOC_MODE
} eMIOS_OperationMode;
/**@}*/


/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/



/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
#define ICU_START_SEC_CODE
/**
@file  eMIOS_Icu_LLD.h
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref eMIOS_Icu_LLD_h_1
*/
#include "MemMap.h"

/*================================================================================================*/
/**
@brief      Icu driver function that handles the interrupt of eMIOS channel.
@details    This function:
             - Reads the status register
             - Clears the pending interrupt
             - Processes interrupt for corresponding eMIOS channel

@param[in]  hwChannel - eMIOS hardware channel

@remarks    Covers ICU020, ICU021
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) EMIOS_Icu_LLD_ProcessInterrupt(CONST(uint8, AUTOMATIC) hwChannel);

/*================================================================================================*/
/**
@brief      Icu driver function that checks the overflow flag
@details    This function returns true if the overflow flag is set

@param[in]  flags - the flags to be checked

@return     boolean
             - true -  if the parameter's value contains overflow flag
             - false - if the parameter's value doesnot contains overflow flag
*/
/*================================================================================================*/
FUNC (boolean, ICU_CODE) eMIOS_LLD_CheckOverflowFlag(CONST(uint32, AUTOMATIC) flags);

/*================================================================================================*/
/**
@brief      Icu driver initialization function for eMIOS module.
@details    This function is called separately for each EMIOS hw channel corresponding to
            the configured Icu channels, and:
            - Disables the interrupt corresponding to eMIOS channel
            - Initializes prescaler value, channel filter, freeze enable, and bus select fields
            - Defines on which edge the period starts
            - Clears the (pending) interrupt flag corresponding to eMIOS channel
            - Resets the UC A register.
            - Enables the SAIC mode for eMIOS channels.
@param[in]  ParamValue  - contains the parameters to initialize the hardware channel
@param[in]  channelMode - Chanel mode
@param[in]  hwChannel   - eMIOS encoded hardware channel
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) eMIOS_LLD_InitChannel(CONST(uint32, AUTOMATIC) ParamValue,
                                            CONST(eMIOS_ChannelModeType, AUTOMATIC) channelMode,
                                            CONST(uint8, AUTOMATIC) hwChannel);

/*================================================================================================*/
/**
@brief      Icu driver de-initialization function for eMIOS module.
@details    This function is called separately for each EMIOS hw channel corresponding to the
            configured Icu channels, and:
            - Resets the eMIOS channel control register
            - Resets the UC A register.
            - Clears the (pending) interrupt flag corresponding to eMIOS channel
@param[in]  hwChannel   - eMIOS encoded hardware channel
@param[in]  reg_EMIOSCNT_available  - indicates the availability of register EMIOS UC Counter
            - true - is available
            - false - is not available
@param[in]  reg_EMIOSB_available  - indicates the availability of register EMIOS UC B register
            - true - is available
            - false - is not available
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) eMIOS_LLD_DeInitChannel(CONST(uint8, AUTOMATIC) hwChannel,
                                              VAR(boolean,AUTOMATIC) reg_EMIOSCNT_available,
                                              VAR(boolean,AUTOMATIC) reg_EMIOSB_available);
#if (ICU_SET_MODE_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that puts eMIOS timer channel in SLEEP mode.
@details    This function is called separately for each EMIOS hw channel corresponding to the
            configured Icu channels, and:
            - Enables the interrupt for the eMIOS channel,
                if the wake up functionality is enabled
            - Disables the interrupt for the eMIOS channel,
                if the wake up functionality is disabled
@param[in]  hwChannel     - eMIOS encoded hardware channel
@param[in]  WakeUpEnabled - specifies if channel is wake-up enabled
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) eMIOS_LLD_SetSleepMode(VAR(uint8, AUTOMATIC) hwChannel, 
                                             VAR(boolean, AUTOMATIC) WakeUpEnabled);

/*================================================================================================*/
/**
@brief      Icu driver function that puts the eMIOS timer channel in NORMAL mode.
@details    This function:
            - Enables the interrupt for the eMIOS channel, if the Notification is active
            - Disables the interrupt for the eMIOS channel, if the Notification is not enabled
              for the channel
@param[in]  hwChannel          - eMIOS encoded hardware channel
@param[in]  NotificationActive - specifies if channel has notification activated
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) eMIOS_LLD_SetNormalMode(VAR(uint8, AUTOMATIC) hwChannel, 
                                              VAR(boolean, AUTOMATIC) NotificationActive);
/* ICU_SET_MODE_API */
#endif  

/*================================================================================================*/
/**
@brief      Icu driver function that sets activation condition of eMIOS channel
@details    This function enables the requested activation condition(rising, falling or both edges)
            for corresponding eMIOS channels.
@param[in]  hwChannel   - eMIOS encoded hardware channel
@param[in]  activation  - edge activation type
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) eMIOS_LLD_SetActivationCondition(VAR(uint8, AUTOMATIC) hwChannel,
                                                   VAR(eMIOS_ActivationType, AUTOMATIC) activation);

/*================================================================================================*/
/**
@brief       Icu driver function that disables the eMIOS channel notifification/IRQ.
@details     This function disables the interrupt corresponding to the eMIOS channel.

@param[in]   hwChannel   - eMIOS encoded hardware channel
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) eMIOS_LLD_DisableNotification(VAR(uint8, AUTOMATIC) hwChannel);

/*================================================================================================*/
/**
@brief      Icu driver function that enables the eMIOS channel notifification/IRQ.
@details    This function enables the interrupt corresponding to the eMIOS channel.

@param[in]  hwChannel   - eMIOS encoded hardware channel
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) eMIOS_LLD_EnableNotification(VAR(uint8, AUTOMATIC) hwChannel);

#if (ICU_GET_INPUT_STATE_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that gets the input state of eMIOS channel.
@details    This function:
            - Checks if interrupt flags for corresponding eMIOS channel is set then
            it clears the interrupt flag and returns the value as true.

@param[in]  hwChannel - eMIOS encoded hardware channel

@return     boolean
             - true - if channel is active
             - false - if channel is idle
*/
/*================================================================================================*/
FUNC (boolean, ICU_CODE) eMIOS_LLD_GetInputState(VAR(uint8, AUTOMATIC) hwChannel);
/* ICU_GET_INPUT_STATE_API */
#endif 

#if (ICU_TIMESTAMP_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that starts time stamp measurement of eMIOS channel.
@details    This function:
            - Puts the eMIOS channel into GPIO mode
            - Clears the pending interrupts
            - Enables SAIC mode for the channel
            - Enbales the interrupt for the channel

@param[in]  hwChannel   - eMIOS encoded hardware channel
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) eMIOS_LLD_StartTimestamp(VAR(uint8, AUTOMATIC) hwChannel);

/*================================================================================================*/
/**
@brief      Icu driver function that stops time stamp measurement of eMIOS channel.
@details    This function:
            - Puts the eMIOS channel into GPIO mode
            - Disables the interrupt for the channel

@param[in]  hwChannel   - eMIOS encoded hardware channel
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) eMIOS_LLD_StopTimestamp(VAR(uint8, AUTOMATIC) hwChannel);

/*================================================================================================*/
/**
@brief      Icu driver function that returns the time stamp index of eMIOS channel.
@details    Returns the captured value in register A

@param[in]  hwChannel - eMIOS encoded hardware channel

@return     uint32 - The captured value in register A
*/
/*================================================================================================*/
FUNC(uint32, ICU_CODE) eMIOS_GetTimeStamp(VAR(uint8, AUTOMATIC) hwChannel);
/* ICU_TIMESTAMP_API */
#endif 

#if (ICU_EDGE_COUNT_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that resets the edge counter measurement of eMIOS channel.
@details    The function:
            - Puts the eMIOS channel into GPIO mode
            - Resets the counter to initial value
            - Loads the initial value to the RegisterA
            - Clears the pending interrupts
            - Restores the previous mode

@param[in]  hwChannel   - eMIOS encoded hardware channel
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) eMIOS_LLD_ResetEdgeCount(VAR(uint8, AUTOMATIC) hwChannel);

/*================================================================================================*/
/**
@brief      Icu driver function that enables the edge counter measurement of eMIOS channel.
@details    The function:
            - Puts the eMIOS channel into GPIO mode
            - Counter register is loaded with startValue
            - Loads initial value to RegisterA
            - Clears the pending interrupts
            - Sets the mode to Modulus counter mode
            - Enables the interrupt for eMIOS channel

@param[in]  hwChannel   - eMIOS encoded hardware channel
@param[in]  startValue  - starting value
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) eMIOS_LLD_EnableEdgeCount(VAR(uint8, AUTOMATIC) hwChannel, 
                                                VAR(uint32, AUTOMATIC) startValue);

/*================================================================================================*/
/**
@brief      Icu driver function that disables the edge counter measurement of eMIOS channel.
@details    The function:
            - Disables the eMIOS channel interrupt
            - Clears the pending interrupts
            - Save the current counter value before entering into GPIO mode
            - Puts the channel into GPIO mode
            - Disables MCB mode for the channel

@param[in]  hwChannel    - eMIOS encoded hardware channel
@param[out] currentValue - the current value of the channel's counter
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) eMIOS_LLD_DisableEdgeCount(VAR(uint8, AUTOMATIC) hwChannel, 
                                              P2VAR(uint32, AUTOMATIC, ICU_APPL_DATA) currentValue);

/*================================================================================================*/
/**
@brief      Icu driver function that gets edge counter measurement of eMIOS channel.
@details    This function returns counter value (the number of counter edges) of eMIOS channel

@param[in]  hwChannel   - eMIOS encoded hardware channel

@return     uint32 - Counted edges number
*/
/*================================================================================================*/
FUNC (uint32, ICU_CODE) eMIOS_LLD_GetEdgeNumbers(VAR(uint8, AUTOMATIC) hwChannel);
/* ICU_EDGE_COUNT_API */
#endif 

#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that starts the signal measurement of eMIOS channel.
@details    This function:
            - Disables the interrupt of eMIOS channel
            - Puts the eMIOS channel into GPIO mode
            - Sets activation condition (Rising, Falling or Both edges)
            - Puts the eMIOS channel into requested mode (IPWM, IPM or SAIC)
            - Clears pending interrupts
            - Enables the interrupt for eMIOS channel

@param[in]  hwChannel  - eMIOS encoded hardware channel
@param[in]  activation - edge activation type
@param[in]  mode       - Unified Chanel mode of operation
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) eMIOS_LLD_StartSignalMeasurement(VAR(uint8, AUTOMATIC) hwChannel,
                                                    VAR(eMIOS_ActivationType, AUTOMATIC) activation,
                                                    VAR(eMIOS_OperationMode, AUTOMATIC) mode);
/*================================================================================================*/
/**
@brief      Icu driver function that stops the signal measurement of eMIOS channel.
@details    This function:
            - Puts the eMIOS channel into GPIO mode
            - Disables the interrupt for requsted eMIOS channel
            - Clears pending interrupts

@param[in]  hwChannel  - eMIOS encoded hardware channel
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) eMIOS_LLD_StopSignalMeasurement(VAR(uint8, AUTOMATIC) hwChannel);

/*================================================================================================*/
/**
@brief      Icu driver function that gets the RegisterA value of eMIOS channel
@details    This function returns the register A of the given eMIOS Unified Channel
@param[in]  hwChannel  - eMIOS encoded hardware channel
@return     uint32 - Captured value of the register A
*/
/*================================================================================================*/
FUNC(uint32, ICU_CODE) eMIOS_LLD_GetCaptureRegA(VAR(uint8, AUTOMATIC) hwChannel);

/*================================================================================================*/
/**
@brief      Icu driver function that gets the RegisterB value of eMIOS channel
@details    This function returns the register B of the given eMIOS Unified Channel
@param[in]  hwChannel  - eMIOS encoded hardware channel
@return     uint32 - Captured value of the register B
*/
/*================================================================================================*/
FUNC(uint32, ICU_CODE) eMIOS_LLD_GetCaptureRegB(VAR(uint8, AUTOMATIC) hwChannel);

/* ICU_SIGNAL_MEASUREMENT_API */
#endif  


#if (ICU_DUAL_CLOCK_MODE == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that sets the channel prescaler.
@details    This function:
            - Clears GPREN bit in EMIOSMCR register and UCPREN bit in EMIOSC[n] register
            - Writes prescaling rate at UCPRE[0:1] bits in EMIOSC[n] register
            - Enables channel prescaler by setting UCPREN bit in EMIOSC[n] register
            - Enables global prescaler by setting GPREN bit in EMIOSMCR register

@param[in]  ParamValue     - contains the parameters to initialize the hardware channel
@param[in]  hwChannel      - eMIOS encoded hardware channel
@remarks    Covers PR-MCAL-3195
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) eMIOS_Icu_LLD_SelectPrescaler(CONST(uint32, AUTOMATIC) ParamValue,
                                                    CONST(uint8, AUTOMATIC) hwChannel);
/* ICU_DUAL_CLOCK_MODE */
#endif  


#define ICU_STOP_SEC_CODE
/**
@file  eMIOS_Icu_LLD.h
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref eMIOS_Icu_LLD_h_1
*/
#include "MemMap.h"

#ifdef __cplusplus
}
#endif
/* EMIOS_ICU_LLD_H */
#endif  

