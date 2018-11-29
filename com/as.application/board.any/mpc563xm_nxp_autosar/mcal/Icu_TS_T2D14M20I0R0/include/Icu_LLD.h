/**
    @file Icu_LLD.h
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
@file    Icu_LLD.h
@remarks Implements DICU03000
*/

/**
@page misra_violations MISRA-C:2004 violations

@section Icu_LLD_h_REF_1
Violates MISRA-C 2004 Advisory Rule 19.7, Function-like macro defined
This violation is due to function like macros defined for register operations.
Function like macros are used to reduce code complexity.

@section Icu_LLD_h_REF_2
Violates MISRA-C:2004 Advisory Rule 19.15 Precautions shall be taken in order to prevent
the contents of a header file being included twice
This is not a violation since all header files are protected against multiple inclusions
*/



#ifndef ICU_LLD_H
#define ICU_LLD_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/**
@file  Icu_LLD.h
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice  See @ref Icu_LLD_h_REF_2
*/

/*lint -save -e537*/
#include "Icu.h"

#if (ICU_DUAL_CLOCK_MODE == STD_ON)
    #include "Icu_NonASR.h"
/* ICU_DUAL_CLOCK_MODE */
#endif 

#include "Std_Types.h"

#include "eMIOS_Icu_LLD.h"
#include "eMIOS_Icu_LLD_CfgEx.h"
#include "Siu_Icu_LLD.h"
#include "Siu_Icu_LLD_CfgEx.h"

/*lint -restore*/


/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@{
@brief   Header file version information
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define ICU_LLD_VENDOR_ID           43

#define ICU_LLD_AR_MAJOR_VERSION    3
#define ICU_LLD_AR_MINOR_VERSION    0
#define ICU_LLD_AR_PATCH_VERSION    0
#define ICU_LLD_SW_MAJOR_VERSION    2
#define ICU_LLD_SW_MINOR_VERSION    0
#define ICU_LLD_SW_PATCH_VERSION    0
/**@}*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if header file Icu_LLD.h and eMIOS_Icu_LLD.h header  file have the same Vendor Id
   version */
#if (ICU_LLD_VENDOR_ID != EMIOS_ICU_LLD_VENDOR_ID)
#error "Icu_LLD.h and eMIOS_Icu_LLD.h have different vendor IDs"
#endif

/* Check if header file Icu_LLD.h and eMIOS_Icu_LLD.h header file are of the Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((ICU_LLD_AR_MAJOR_VERSION != EMIOS_ICU_LLD_AR_MAJOR_VERSION) || \
         (ICU_LLD_AR_MINOR_VERSION != EMIOS_ICU_LLD_AR_MINOR_VERSION) || \
         (ICU_LLD_AR_PATCH_VERSION != EMIOS_ICU_LLD_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Icu_LLD.h and eMIOS_Icu_LLD.h are different"
    #endif
#endif
/* Check if header file Icu_LLD.h and eMIOS_Icu_LLD.h header file are of the same software
   version */
#if ((ICU_LLD_SW_MAJOR_VERSION != EMIOS_ICU_LLD_SW_MAJOR_VERSION) || \
     (ICU_LLD_SW_MINOR_VERSION != EMIOS_ICU_LLD_SW_MINOR_VERSION) || \
     (ICU_LLD_SW_PATCH_VERSION != EMIOS_ICU_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of Icu_LLD.h and eMIOS_Icu_LLD.h are different"
#endif


/* Check if header file Icu_LLD.h and eMIOS_Icu_LLD_CfgEx.h header  file have the same Vendor Id
   version */
#if (ICU_LLD_VENDOR_ID != EMIOS_ICU_LLD_CFG_EX_VENDOR_ID)
#error "Icu_LLD.h and eMIOS_Icu_LLD_CfgEx.h have different vendor IDs"
#endif

/* Check if header file Icu_LLD.h and eMIOS_Icu_LLD_CfgEx.h header file are of the Autosar
   version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((ICU_LLD_AR_MAJOR_VERSION != EMIOS_ICU_LLD_CFG_EX_AR_MAJOR_VERSION) || \
         (ICU_LLD_AR_MINOR_VERSION != EMIOS_ICU_LLD_CFG_EX_AR_MINOR_VERSION) || \
         (ICU_LLD_AR_PATCH_VERSION != EMIOS_ICU_LLD_CFG_EX_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Icu_LLD.h and eMIOS_Icu_LLD_CfgEx.h are different"
    #endif
#endif
/* Check if header file Icu_LLD.h and eMIOS_Icu_LLD_CfgEx.h header file are of the same software
   version */
#if ((ICU_LLD_SW_MAJOR_VERSION != EMIOS_ICU_LLD_CFG_EX_SW_MAJOR_VERSION) || \
     (ICU_LLD_SW_MINOR_VERSION != EMIOS_ICU_LLD_CFG_EX_SW_MINOR_VERSION) || \
     (ICU_LLD_SW_PATCH_VERSION != EMIOS_ICU_LLD_CFG_EX_SW_PATCH_VERSION))
#error "Software Version Numbers of Icu_LLD.h and eMIOS_Icu_LLD_CfgEx.h are different"
#endif


/* Check if header file Icu_LLD.h and SIU_Icu_LLD_CfgEx.h header  file have the same Vendor Id
   version */
#if (ICU_LLD_VENDOR_ID != SIU_ICU_LLD_CFG_EX_VENDOR_ID)
#error "Icu_LLD.h and SIU_Icu_LLD_CfgEx.h have different vendor IDs"
#endif

/* Check if header file Icu_LLD.h and SIU_Icu_LLD_CfgEx.h header file are of the Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((ICU_LLD_AR_MAJOR_VERSION != SIU_ICU_LLD_CFG_EX_AR_MAJOR_VERSION) || \
         (ICU_LLD_AR_MINOR_VERSION != SIU_ICU_LLD_CFG_EX_AR_MINOR_VERSION) || \
         (ICU_LLD_AR_PATCH_VERSION != SIU_ICU_LLD_CFG_EX_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Icu_LLD.h and SIU_Icu_LLD_CfgEx.h are different"
    #endif
#endif
/* Check if header file Icu_LLD.h and SIU_Icu_LLD_CfgEx.h header file are of the same software
   version */
#if ((ICU_LLD_SW_MAJOR_VERSION != SIU_ICU_LLD_CFG_EX_SW_MAJOR_VERSION) || \
     (ICU_LLD_SW_MINOR_VERSION != SIU_ICU_LLD_CFG_EX_SW_MINOR_VERSION) || \
     (ICU_LLD_SW_PATCH_VERSION != SIU_ICU_LLD_CFG_EX_SW_PATCH_VERSION))
#error "Software Version Numbers of Icu_LLD.h and SIU_Icu_LLD_CfgEx.h are different"

#endif

/* Check if header file Icu_LLD.h and Icu.h header file have the same Vendor Id version */
#if (ICU_LLD_VENDOR_ID != ICU_VENDOR_ID)
#error "Icu_LLD.h and Icu.h have different vendor IDs"
#endif

/* Check if header file Icu_LLD.h and Icu.h header file are of the Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((ICU_LLD_AR_MAJOR_VERSION != ICU_AR_MAJOR_VERSION) || \
         (ICU_LLD_AR_MINOR_VERSION != ICU_AR_MINOR_VERSION) || \
         (ICU_LLD_AR_PATCH_VERSION != ICU_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Icu_LLD.h and Icu.h are different"
    #endif
#endif
/* Check if header file Icu_LLD.h and Icu.h header file are of the same software version */
#if ((ICU_LLD_SW_MAJOR_VERSION != ICU_SW_MAJOR_VERSION) || \
     (ICU_LLD_SW_MINOR_VERSION != ICU_SW_MINOR_VERSION) || \
     (ICU_LLD_SW_PATCH_VERSION != ICU_SW_PATCH_VERSION))
#error "Software Version Numbers of Icu_LLD.h and Icu.h are different"
#endif

#if (ICU_DUAL_CLOCK_MODE == STD_ON)
    /* Check if header file Icu_LLD.h and Icu_NonASR.h header file have the same Vendor Id
       version */
    #if (ICU_LLD_VENDOR_ID != ICU_NONASR_VENDOR_ID_H)
    #error "Icu_LLD.h and Icu_NonASR.h have different vendor IDs"
    #endif

    /* Check if header file Icu_LLD.h and Icu_NonASR.h header file are of the Autosar
       version */
    #ifdef CHECK_AUTOSAR_VERSION
        #if ((ICU_LLD_AR_MAJOR_VERSION != ICU_NONASR_AR_MAJOR_VERSION_H) || \
             (ICU_LLD_AR_MINOR_VERSION != ICU_NONASR_AR_MINOR_VERSION_H) || \
             (ICU_LLD_AR_PATCH_VERSION != ICU_NONASR_AR_PATCH_VERSION_H))
        #error "AutoSar Version Numbers of Icu_LLD.h and Icu_NonASR.h are different"
        #endif
    #endif

    /* Check if header file Icu_LLD.h and Icu_NonASR.h header file are of the same software
       version */
    #if ((ICU_LLD_SW_MAJOR_VERSION != ICU_NONASR_SW_MAJOR_VERSION_H) || \
         (ICU_LLD_SW_MINOR_VERSION != ICU_NONASR_SW_MINOR_VERSION_H) || \
         (ICU_LLD_SW_PATCH_VERSION != ICU_NONASR_SW_PATCH_VERSION_H))
    #error "Software Version Numbers of Icu_LLD.h and Icu_NonASR.h are different"
    #endif
/* ICU_DUAL_CLOCK_MODE */
#endif 

/* Check if header file Icu_LLD.h and Std_Types.h header file are of the Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((ICU_LLD_AR_MAJOR_VERSION != STD_TYPES_AR_MAJOR_VERSION) || \
         (ICU_LLD_AR_MINOR_VERSION != STD_TYPES_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Icu_LLD.h and Std_Types.h are different"
    #endif
#endif


/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
/* Macros to name the HW channels (eMIOS and IRQ's) */
/**
@{
@brief      eMIOS Channels
@details    eMIOS Hardware Channels
*/
#define ICU_EMIOS_0_CH_0        0U
#define ICU_EMIOS_0_CH_1        (ICU_EMIOS_0_CH_0 +  1U)
#define ICU_EMIOS_0_CH_2        (ICU_EMIOS_0_CH_0 +  2U)
#define ICU_EMIOS_0_CH_3        (ICU_EMIOS_0_CH_0 +  3U)
#define ICU_EMIOS_0_CH_4        (ICU_EMIOS_0_CH_0 +  4U)
#define ICU_EMIOS_0_CH_5        (ICU_EMIOS_0_CH_0 +  5U)
#define ICU_EMIOS_0_CH_6        (ICU_EMIOS_0_CH_0 +  6U)
#define ICU_EMIOS_0_CH_7        (ICU_EMIOS_0_CH_0 +  7U)
#define ICU_EMIOS_0_CH_8        (ICU_EMIOS_0_CH_0 +  8U)
#define ICU_EMIOS_0_CH_9        (ICU_EMIOS_0_CH_0 +  9U)
#define ICU_EMIOS_0_CH_10       (ICU_EMIOS_0_CH_0 + 10U)
#define ICU_EMIOS_0_CH_11       (ICU_EMIOS_0_CH_0 + 11U)
#define ICU_EMIOS_0_CH_12       (ICU_EMIOS_0_CH_0 + 12U)
#define ICU_EMIOS_0_CH_13       (ICU_EMIOS_0_CH_0 + 13U)
#define ICU_EMIOS_0_CH_14       (ICU_EMIOS_0_CH_0 + 14U)
#define ICU_EMIOS_0_CH_15       (ICU_EMIOS_0_CH_0 + 15U)
#define ICU_EMIOS_0_CH_16       (ICU_EMIOS_0_CH_0 + 16U)
#define ICU_EMIOS_0_CH_17       (ICU_EMIOS_0_CH_0 + 17U)
#define ICU_EMIOS_0_CH_18       (ICU_EMIOS_0_CH_0 + 18U)
#define ICU_EMIOS_0_CH_19       (ICU_EMIOS_0_CH_0 + 19U)
#define ICU_EMIOS_0_CH_20       (ICU_EMIOS_0_CH_0 + 20U)
#define ICU_EMIOS_0_CH_21       (ICU_EMIOS_0_CH_0 + 21U)
#define ICU_EMIOS_0_CH_22       (ICU_EMIOS_0_CH_0 + 22U)
#define ICU_EMIOS_0_CH_23       (ICU_EMIOS_0_CH_0 + 23U)

/**@}*/
/**@}*/

/**
@{
@brief      External Interrupt Channels
@details    SIU IRQ Channels
*/
#define ICU_IRQ_0           (ICU_EMIOS_0_CH_23 + 1U)
#define ICU_IRQ_1           (ICU_IRQ_0 +  1U)
#define ICU_IRQ_2           (ICU_IRQ_0 +  2U)
#define ICU_IRQ_3           (ICU_IRQ_0 +  3U)
#define ICU_IRQ_4           (ICU_IRQ_0 +  4U)
#define ICU_IRQ_5           (ICU_IRQ_0 +  5U)
#define ICU_IRQ_6           (ICU_IRQ_0 +  6U)
#define ICU_IRQ_7           (ICU_IRQ_0 +  7U)
#define ICU_IRQ_8           (ICU_IRQ_0 +  8U)
#define ICU_IRQ_9           (ICU_IRQ_0 +  9U)
#define ICU_IRQ_10          (ICU_IRQ_0 + 10U)
#define ICU_IRQ_11          (ICU_IRQ_0 + 11U)
#define ICU_IRQ_12          (ICU_IRQ_0 + 12U)
#define ICU_IRQ_13          (ICU_IRQ_0 + 13U)
#define ICU_IRQ_14          (ICU_IRQ_0 + 14U)
#define ICU_IRQ_15          (ICU_IRQ_0 + 15U)
/**@}*/

/**@}*/
/*
 * Macros regarding the maximum count value of ICU EMIOS channel internal counter
 */
/**
@{
@brief      EMIOS_INTERNAL_COUNTER_MAX_COUNT - the maximum count of eMIOS
channel's internal counter
@details    Represents the maximum count of eMIOS channel's internal counter
*/

#define EMIOS_INTERNAL_COUNTER_MAX_COUNT        0xffffff
/*
 * Macros regarding the maximum number of HW channels from different IP modules
 */
/**
@{
@brief      ICU_MAX_eMIOS_CHANNELS - the maximum number of eMIOS channels
@details    Represents the maximum number of eMIOS channels, not necessary all
            are available for a specific derivative. If some channels are
            missing for a derivative, the encoding of the channels will be not
            contiguous.
*/
#define ICU_MAX_eMIOS_CHANNELS      (ICU_IRQ_0)
/**@}*/

/**
@{
@brief      ICU_MAX_IRQ_CHANNELS - the maximum number of IRQ channels
@details    Represents the maximum number of IRQ channels, not necessary all
            are available for a specific derivative. If some channels are
            missing for a derivative, the encoding of the channels will be not
            contiguous.
*/
#define ICU_MAX_IRQ_CHANNELS        (ICU_IRQ_15 + 1U)
/**@}*/

/**@}*/
/**
@{
@brief      ICU_MAX_HW_CHANNELS - the highest ICU hardware channel number
@details    Represents the maximum number of IRQ channels, not necessary all
            are available for a specific derivative. If some channels are
            missing for a derivative, the encoding of the channels will be not
            contiguous.
*/
#define ICU_MAX_HW_CHANNELS         ICU_MAX_IRQ_CHANNELS
/**@}*/

/**
@{
 * @brief Macros to translate ICU generic channels to specific hardware channels
 */
 /**
 @note  Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined See
        @ref Icu_LLD_h_REF_1 */

/*lint -save -e961*/
#if (eMIOS_N_CHANNELS == 32)
#define ICU_eMIOS_CHANNEL(ch)       (ch)
#define eMIOS_ICU_CHANNEL(ch)       (ch)
#else
#define ICU_eMIOS_CHANNEL(ch)       (((( ((uint8)((ch) / eMIOS_N_CHANNELS)) << EMIOS_MOD_SHIFT ) & \
        EMIOS_MOD_MASK) | (( ((uint8)((ch) % eMIOS_N_CHANNELS)) << EMIOS_CH_SHIFT ) &  \
        EMIOS_CH_MASK)))
#define eMIOS_ICU_CHANNEL(ch)       (((((ch) & EMIOS_MOD_MASK)>> EMIOS_MOD_SHIFT) *  \
        eMIOS_N_CHANNELS) + ((ch) & EMIOS_CH_MASK) >> EMIOS_CH_SHIFT)
#endif

#define ICU_IRQ_CHANNEL(ch)         ((ch) - ICU_IRQ_0)
#define IRQ_ICU_CHANNEL(ch)         ((ch) + ICU_IRQ_0)

/*lint -restore*/
/**@}*/

/* Specific IRQ Channel parameters
 *  - defines the bitfields used in Icu_ParamValue member for ICU External Interrupt Channels
 */
/* No specific IRQ Channel parameters */


/**
@{
@brief Specific eMIOS Channel parameters
@remarks defines for bitfields used in Icu_ParamValue member for ICU eMIOS Channels
*/
#define ICU_EMIOS_PRESC_ALT_PARAM_MASK          (uint32)(BIT14|BIT13)
#define ICU_EMIOS_PRESC_ALT_PARAM_SHIFT         (uint32)13U
#define ICU_EMIOS_UC_MODE_PARAM_MASK            (uint32)(BIT12|BIT11|BIT10|BIT9)
#define ICU_EMIOS_UC_MODE_PARAM_SHIFT           (uint32)9U

#define ICU_EMIOS_FREEZE_PARAM_MASK             (uint32)BIT8
#define ICU_EMIOS_FREEZE_PARAM_SHIFT            (uint32)8U

#define ICU_EMIOS_PRESCALER_PARAM_MASK          (uint32)(BIT7|BIT6)
#define ICU_EMIOS_PRESCALER_PARAM_SHIFT         (uint32)6U

#define ICU_EMIOS_DIG_FILTER_PARAM_MASK         (uint32)(BIT5|BIT4|BIT3|BIT2)
#define ICU_EMIOS_DIG_FILTER_PARAM_SHIFT    (uint32)2U

#define ICU_EMIOS_BUS_SELECT_PARAM_MASK         (uint32)(BIT1|BIT0)
#define ICU_EMIOS_BUS_SELECT_PARAM_SHIFT        (uint32)0U
/**@}*/
/**
@{
@brief Used for identifying the not configured channels
*/
#define ICU_INDEX_NULL                          0xFFU
/**@}*/

/**
@{
@brief   Macros for handling the actual states of the ICU Channels
@remarks These bitfields are used to set Icu_ChannelState array
*/

/**
@brief Wakeup feature is currently enabled
*/
#define ICU_CHANNEL_STATE_WKUP                  (Icu_ChannelStateType)BIT0
#define ICU_CHANNEL_STATE_WKUP_SHIFT            0U
#define ICU_CHANNEL_STATE_WKUP_MASK             (Icu_ChannelStateType)BIT0

/**
@brief The current channel status - IDLE / ACTIVE
*/
#define ICU_CHANNEL_STATE_IDLE                  (Icu_ChannelStateType)BIT1
#define ICU_CHANNEL_STATE_IDLE_SHIFT            1U
#define ICU_CHANNEL_STATE_IDLE_MASK             (Icu_ChannelStateType)BIT1

/**
@brief Notification is enabled
*/
#define ICU_CHANNEL_STATE_NOTIFICATION          (Icu_ChannelStateType)BIT2
#define ICU_CHANNEL_STATE_NOTIF_SHIFT           2U
#define ICU_CHANNEL_STATE_NOTIF_MASK            (Icu_ChannelStateType)BIT2

/**
@brief The current channel state
*/
#define ICU_CHANNEL_STATE_RUNNING               (Icu_ChannelStateType)BIT3
#define ICU_CHANNEL_STATE_RUNNING_SHIFT         3U
#define ICU_CHANNEL_STATE_RUNNING_MASK          (Icu_ChannelStateType)BIT3

/**
@brief Overflow flag
*/
#define ICU_CHANNEL_STATE_OVERFLOW              (Icu_ChannelStateType)BIT4
#define ICU_CHANNEL_STATE_OVERFLOW_SHIFT        4U
#define ICU_CHANNEL_STATE_OVERFLOW_MASK         (Icu_ChannelStateType)BIT4

/**
@brief Rising edge
*/
#define ICU_CHANNEL_STATE_RISING                (Icu_ChannelStateType)BIT5
#define ICU_CHANNEL_STATE_RISING_SHIFT          5U
#define ICU_CHANNEL_STATE_RISING_MASK           (Icu_ChannelStateType)BIT5

/**
@brief Falling edge
*/
#define ICU_CHANNEL_STATE_FALLING               (Icu_ChannelStateType)BIT6
#define ICU_CHANNEL_STATE_FALLING_SHIFT         6U
#define ICU_CHANNEL_STATE_FALLING_MASK          (Icu_ChannelStateType)BIT6

/**
@brief Both edges
*/
#define ICU_CHANNEL_STATE_BOTH_EDGES            (Icu_ChannelStateType)(BIT6|BIT5)
#define ICU_CHANNEL_STATE_BOTH_EDGES_SHIFT      5U
#define ICU_CHANNEL_STATE_BOTH_EDGES_MASK       (Icu_ChannelStateType)(BIT6|BIT5)
/**@}*/


/*==================================================================================================
                                             ENUMS
==================================================================================================*/


/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/*================================================================================================*/
/**
@typedef   Icu_ChannelStateType
           ICU Channel state type
*/
/*================================================================================================*/
typedef uint8 Icu_ChannelStateType;

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

#ifdef ICU_PRECOMPILE_SUPPORT
/**
@brief External declaration of the ICU configuration structure for pre-compiled mode
*/
extern CONST(Icu_ConfigType, ICU_CONST) Icu_Configs_PC;
/* ICU_PRECOMPILE_SUPPORT */
#endif  

extern P2CONST(Icu_ConfigType, ICU_VAR, ICU_APPL_CONST) Icu_Cfg_Ptr;

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
/*================================================================================================*/
/**
@brief      Icu driver function that initializes the ICU hardware channel.
@details    This function initializes a hardware ICU channel

@param[in]  tempPtr     - Pointer to configuration structure
@param[in]  numChl      - The index of ICU channel for current configuration structure
@param[in]  msChannel   - This index relates the Icu Channel number with the respective global
                          variable, depending on the measurement mode. Each kind of measurement
                          mode has an array(s) in the ICU driver, this index points to the
                          corresponding variable within the ICU channel.
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_InitChannel(
                                  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_APPL_CONST) tempPtr,
                                  VAR(Icu_ChannelType, AUTOMATIC) numChl,
                                  CONST(Icu_ChannelType, AUTOMATIC) msChannel);

/*================================================================================================*/
/**
@brief      Icu driver function that de-initializes the ICU hardware channel.
@details    This function de-initializes the ICU hardware channel.

@param[in]  numChl - The index of ICU channel for current configuration structure
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_DeInitChannel(VAR(Icu_ChannelType, AUTOMATIC) numChl);

#if (ICU_SET_MODE_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that sets the ICU hardware channel into sleep mode.
@details    This function sets the ICU hardware channels (eMIOS, SIUL or WKUP) into SLEEP mode

@param[in]  numChl - The index of ICU channel for current configuration structure
@param[in]  active - ICU channel is active during SLEEP mode (wakeup was enabled)
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_SetSleepMode(VAR(Icu_ChannelType, AUTOMATIC) numChl,
                                           VAR(boolean, AUTOMATIC) active);

/*================================================================================================*/
/**
@brief      Icu driver function that sets the ICU hardware channel into NORMAL mode.
@details    This function sets the ICU hardware channels (eMIOS, SIUL or WKUP) into NORMAL mode,
            Enables the notification for the channel.

@param[in]  numChl - The index of ICU channel for current configuration structure
@param[in]  active - ICU channel is active during NORMAL mode (notification was enabled)
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_SetNormalMode(VAR(Icu_ChannelType, AUTOMATIC) numChl,
                                            VAR(boolean, AUTOMATIC) active);
 /* ICU_SET_MODE_API == STD_ON */
#endif 

#if (ICU_DISABLE_WAKEUP_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that disables the wakeup for channel.
@details    This function disables wakeup for ICU hardware channels.
@param[in]  numChl - The index of ICU channel for current configuration structure
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_DisableWakeup(VAR(Icu_ChannelType, AUTOMATIC) numChl);
/* ICU_DISABLE_WAKEUP_API == STD_ON */
#endif  

#if (ICU_ENABLE_WAKEUP_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that enables the wakeup for channel.
@details    This function enables wakeup for ICU hardware channels.

@param[in]  numChl - The index of ICU channel for current configuration structure
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_EnableWakeup(VAR(Icu_ChannelType, AUTOMATIC) numChl);
 /* ICU_ENABLE_WAKEUP_API == STD_ON */
#endif 

/*================================================================================================*/
/**
@brief      Icu driver function that sets activation conditiond for channel with requested
            activation type.
@details    This function sets the requested Activation for the channels (eMIOS, SIUL or WKUP)

@param[in]  numChl     - The index of ICU channel for current configuration structure
@param[in]  Activation - the type of activation for the ICU channel.
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_SetActivationCondition(VAR(Icu_ChannelType, AUTOMATIC) numChl,
                                                     VAR(Icu_ActivationType, AUTOMATIC) Activation);

/*================================================================================================*/
/**
@brief      Icu driver function that disables the notification for channel.
@details    This function disables notification for an ICU Hardware Channel.
            For disabling notification, for some ICU channels, the interrupt
            for the channel must be also disabled

@param[in]  numChl - The index of ICU channel for current configuration structure
@param[in]  DisableInterrupt - true if the interrupt must be also disabled
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_DisableNotification(VAR(Icu_ChannelType, AUTOMATIC) numChl,
                                                  VAR(boolean, AUTOMATIC) DisableInterrupt);

/*================================================================================================*/
/**
@brief      Icu driver function that enables the notification for channel.
@details    This function enables notification for an ICU Hardware Channel.
            For enabling notifications for some ICU channels, the interrupt
            for the channel must be also re-enabled

@param[in]  numChl - The index of ICU channel for current configuration structure
@param[in]  EnableInterrupt - true if interrupt of the channel must be also enabled
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_EnableNotification(VAR(Icu_ChannelType, AUTOMATIC) numChl,
                                                 VAR(boolean, AUTOMATIC) EnableInterrupt);

#if (ICU_GET_INPUT_STATE_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that gets the input state of ICU hardware channel.
@details    This function gets the state of ICU channel (eMIOS, SIUL or WKUP)

@param[in]  numChl - The index of ICU channel for current configuration structure

@return     Icu_InputStateType
             - ICU_ACTIVE - An activation edge has been detected
             - ICU_IDLE - No activation edge has been detected.
*/
/*================================================================================================*/
FUNC (Icu_InputStateType, ICU_CODE) Icu_LLD_GetInputState(VAR(Icu_ChannelType, AUTOMATIC) numChl);
/* ICU_GET_INPUT_STATE_API == STD_ON */
#endif  

#if (ICU_TIMESTAMP_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that starts the time stamp of ICU hardware channel.
@details    This function starts the time stamp measurement of ICU channel.

@param[in]  numChl - The index of ICU channel for current configuration structure
@param[in]  msChannel - The index of Logical ICU channel
@param[in]  BufferPtr - Pointer to the buffer
@param[in]  BufferSize - Size of buffer
@param[in]  NotifyInterval - Notification interval time
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_StartTimestamp(VAR(Icu_ChannelType, AUTOMATIC) numChl,
                                          CONST(Icu_ChannelType, AUTOMATIC) msChannel,
                                          P2VAR(Icu_ValueType, AUTOMATIC, ICU_APPL_DATA) BufferPtr,
                                          VAR(uint16, AUTOMATIC) BufferSize,
                                          VAR(uint16, AUTOMATIC) NotifyInterval);

/*================================================================================================*/
/**
@brief      Icu driver function that stops the time stamp of ICU hardware channel.
@details    This function stops the time stamp measurement of ICU channel.

@param[in]  numChl - The index of ICU channel for current configuration structure
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_StopTimestamp(VAR(Icu_ChannelType, AUTOMATIC) numChl);

/*================================================================================================*/
/**
@brief      Icu driver function that gets the time stamp index of ICU logical channel.
@details    This function gets the time stamp measurement index of ICU logical channel.
            If Buffer pointer of channel is NULL_PTR then it returns value as 0 else
            it returns the value of time stamp index.

@param[in]  msChannel - The index of ICU channel for current configuration structure

@return     Icu_IndexType - Timestamp index
*/
/*================================================================================================*/
FUNC (Icu_IndexType, ICU_CODE) Icu_LLD_GetTimestampIndex(
                                                       CONST(Icu_ChannelType, AUTOMATIC) msChannel);

 /* ICU_TIMESTAMP_API == STD_ON */
#endif 

#if ((ICU_EDGE_COUNT_API == STD_ON) || (ICU_TIMESTAMP_API == STD_ON))
/*================================================================================================*/
/**
@brief      Icu driver function that gets the status of ICU hardware channel.
@details    This function returns TRUE if channel is running else returns FALSE.

@param[in]  numChl - The index of ICU channel for current configuration structure

@return     boolean
             - true - if the given channel is running
             - false - if the channel is in idle state
*/
/*================================================================================================*/
FUNC (boolean, ICU_CODE) Icu_LLD_Channel_Get_Status(VAR(Icu_ChannelType, AUTOMATIC) numChl);
/*((ICU_EDGE_COUNT_API == STD_ON) || (ICU_TIMESTAMP_API == STD_ON))*/
#endif 

#if (ICU_EDGE_COUNT_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that resets the edge counter measurement of ICU channel.
@details    This function:
             - Clears the overflow flag
             - Resets the edge counter measurement of ICU hardware channel

@param[in]  numChl - The index of ICU channel for current configuration structure
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_ResetEdgeCount(VAR(Icu_ChannelType, AUTOMATIC) numChl);

/*================================================================================================*/
/**
@brief      Icu driver function that enables the edge counter measurement of ICU channel.
@details    This function enables the edge counter measurement of ICU hardware channel

@param[in]  numChl - The index of ICU channel for current configuration structure
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_EnableEdgeCount(VAR(Icu_ChannelType, AUTOMATIC) numChl);

/*================================================================================================*/
/**
@brief      Icu driver function that disables the edge counter measurement of ICU channel.
@details    This function disables the edge counter measurement of ICU hardware channel

@param[in]  numChl - The index of ICU channel for current configuration structure
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_DisableEdgeCount(VAR(Icu_ChannelType, AUTOMATIC) numChl);

/*================================================================================================*/
/**
@brief      Icu driver function thatgets edge counter measurement of ICU channel.
@details    his function returns counter value (the number of counter edges) of ICU channel

@param[in]  numChl - The index of ICU channel for current configuration structure

@return     Icu_EdgeNumberType - Counted edges number
*/
/*================================================================================================*/
FUNC (Icu_EdgeNumberType, ICU_CODE) Icu_LLD_GetEdgeNumbers(VAR(Icu_ChannelType, AUTOMATIC) numChl);
 /* ICU_EDGE_COUNT_API == STD_ON */
#endif 

#if ((ICU_EDGE_COUNT_API == STD_ON) || (ICU_TIMESTAMP_API == STD_ON) || \
     (ICU_GET_TIME_ELAPSED_API == STD_ON) || (ICU_GET_DUTY_CYCLE_VALUES_API == STD_ON) )
/*================================================================================================*/
/**
@brief      Icu driver function that checks overflow flag status of ICU channel
@details    This function returns the overflow status for the given channel and
            resets the channel status flag

@param[in]  numChl - The index of ICU channel for current configuration structure

@return     boolean
             - true - if an overflow event occurred for the given channel
             - false - if no overflow event occurred for the given channel
*/
/*================================================================================================*/
FUNC (boolean, ICU_CODE) Icu_LLD_Get_Overflow(VAR(Icu_ChannelType, AUTOMATIC) numChl);
/* ICU_EDGE_COUNT_API == STD_ON */
#endif  

#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that starts the signal measurement of ICU channel.
@details    This function:
            - Configures the Activation type depends on tempProperty value
            - starts the signal measurement of ICU channel.


@param[in]  tempPtr - Buffer pointer
@param[in]  hwChannel - ICU hardware channel number
@param[in]  tempProperty - Time measurement type (HIGH or LOW)
@param[in]  msChannel - The index of ICU logical channel
@param[in]  numChl - The index of ICU channel for current configuration structure
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_StartSignalMeasurement(
                                  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_APPL_CONST) tempPtr,
                                  CONST(Icu_ChannelType, AUTOMATIC) hwChannel,
                                  VAR(Icu_ParamType, AUTOMATIC) tempProperty,
                                  CONST(Icu_ChannelType, AUTOMATIC) msChannel,
                                  VAR(Icu_ChannelType, AUTOMATIC) numChl);

/*================================================================================================*/
/**
@brief      Icu driver function that stops the signal measurement of ICU channel.
@details    This function stops the signal measurement of ICU channel.

@param[in]  numChl - The index of ICU channel for current configuration structure
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_StopSignalMeasurement(VAR(Icu_ChannelType, AUTOMATIC) numChl);
/* ICU_SIGNAL_MEASUREMENT_API == STD_ON */
#endif  

/*================================================================================================*/
/**
@brief      Icu driver function that handles the interrupt of ICU channel.
@details    Interrupt function  that may  jump to  the WakeUp  function (Depending  on the  selected
            configuration)  and branches  to the  proper actions  depending the  mode in  which the
            channel is operating.

@param[in]  numChl - ICU logical channel
@param[in]  flags  - Interrupts Status Flags

@remarks    Covers ICU020, ICU021, ICU055, ICU056, ICU057
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_ProcessCommonInterrupt(VAR(Icu_ChannelType, AUTOMATIC) numChl,
                                                 VAR(uint32, AUTOMATIC) flags);

#if (ICU_DUAL_CLOCK_MODE == STD_ON)
/*================================================================================================*/
/**
@brief      This function changes the channel prescaler.
@details    This function sets all channels prescalers based on the input mode.

@param[in]  tempPtr   - Pointer to configuration structure
@param[in]  numChl    - The index of ICU channel for current configuration structure
@param[in]  Prescaler - Prescaler type ( Normal or Alternate )
@remarks    Covers PR-MCAL-3195
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_SelectPrescaler(
                                  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_APPL_CONST) tempPtr,
                                  VAR(Icu_ChannelType, AUTOMATIC) numChl,
                                  VAR(Icu_SelectPrescalerType, AUTOMATIC) Prescaler);
/* ICU_DUAL_CLOCK_MODE == STD_ON */
#endif 


#ifdef __cplusplus
}
#endif
/* ICU_LLD_H */
#endif  
