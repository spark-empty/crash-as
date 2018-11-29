/**
    @file    Siu_Icu_LLD.c
    @version 2.0.0

    @brief   AUTOSAR Icu - SIU source file support for ICU driver.
    @details SIU source file, containing the variables and functions that are exported by the SIU
             driver.

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
@file    Siu_Icu_LLD.c
@remarks Implements DICU08000
*/

/**
@page misra_violations MISRA-C:2004 violations

@section Siu_Icu_LLD_c_1
Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before "#include"
This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003


@section Siu_Icu_LLD_c_2
MISRA-C:2004  19.15 Precautions shall be taken in order to prevent the contents of a
header file being included twice.
This is not a violation since all header files are protected against multiple inclusions.

@section Siu_Icu_LLD_c_3
MISRA 2004 Rule 11.3 cast from unsigned long to pointer [Encompasses MISRA 2004 Rule 11.1],
This rule can not be avoided because it appears when addressing memory mapped registers
or other hardware specific feature */


#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Siu_Icu_LLD.h"
#include "Siu_Icu_LLD_CfgEx.h"
#include "Reg_eSys_SIU.h"
#include "Icu_LLD.h"
#include "SchM_Icu.h"

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/** @remarks Covers BSW00374, BSW00318 */
#define SIU_ICU_LLD_VENDOR_ID_C         43
#define SIU_ICU_LLD_AR_MAJOR_VERSION_C  3
#define SIU_ICU_LLD_AR_MINOR_VERSION_C  0
#define SIU_ICU_LLD_AR_PATCH_VERSION_C  0
#define SIU_ICU_LLD_SW_MAJOR_VERSION_C  2
#define SIU_ICU_LLD_SW_MINOR_VERSION_C  0
#define SIU_ICU_LLD_SW_PATCH_VERSION_C  0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and Siu_Icu_LLD.h file are of the same vendor */
#if (SIU_ICU_LLD_VENDOR_ID_C != SIU_ICU_LLD_VENDOR_ID)
#error "Siu_Icu_LLD.c and Siu_Icu_LLD.h have different vendor IDs"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((SIU_ICU_LLD_AR_MAJOR_VERSION_C != SIU_ICU_LLD_AR_MAJOR_VERSION) || \
         (SIU_ICU_LLD_AR_MINOR_VERSION_C != SIU_ICU_LLD_AR_MINOR_VERSION) || \
         (SIU_ICU_LLD_AR_PATCH_VERSION_C != SIU_ICU_LLD_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Siu_Icu_LLD.c and Siu_Icu_LLD.h are different"
    #endif
#endif
/* Check if source file and Siu_Icu_LLD.h header file are of the same Software version */
/** @remarks Covers ICU005 */
#if ((SIU_ICU_LLD_SW_MAJOR_VERSION_C != SIU_ICU_LLD_SW_MAJOR_VERSION) || \
     (SIU_ICU_LLD_SW_MINOR_VERSION_C != SIU_ICU_LLD_SW_MINOR_VERSION) || \
     (SIU_ICU_LLD_SW_PATCH_VERSION_C != SIU_ICU_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of Siu_Icu_LLD.c and Siu_Icu_LLD.h are different"
#endif

/* Check if source file and Siu_Icu_LLD_CfgEx.h file are of the same vendor */
#if (SIU_ICU_LLD_VENDOR_ID_C != SIU_ICU_LLD_CFG_EX_VENDOR_ID)
#error "Siu_Icu_LLD.c and Siu_Icu_LLD_CfgEx.h have different vendor IDs"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((SIU_ICU_LLD_AR_MAJOR_VERSION_C != SIU_ICU_LLD_CFG_EX_AR_MAJOR_VERSION) || \
         (SIU_ICU_LLD_AR_MINOR_VERSION_C != SIU_ICU_LLD_CFG_EX_AR_MINOR_VERSION) || \
         (SIU_ICU_LLD_AR_PATCH_VERSION_C != SIU_ICU_LLD_CFG_EX_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Siu_Icu_LLD.c and Siu_Icu_LLD_CfgEx.h are different"
    #endif
#endif
/* Check if source file and Siu_Icu_LLD_CfgEx.h header file are of the same Software version */
/** @remarks Covers ICU005 */
#if ((SIU_ICU_LLD_SW_MAJOR_VERSION_C != SIU_ICU_LLD_CFG_EX_SW_MAJOR_VERSION) || \
     (SIU_ICU_LLD_SW_MINOR_VERSION_C != SIU_ICU_LLD_CFG_EX_SW_MINOR_VERSION) || \
     (SIU_ICU_LLD_SW_PATCH_VERSION_C != SIU_ICU_LLD_CFG_EX_SW_PATCH_VERSION))
#error "Software Version Numbers of Siu_Icu_LLD.c and Siu_Icu_LLD_CfgEx.h are different"
#endif

/* Check if source file and Icu_LLD.h file are of the same vendor */
#if (SIU_ICU_LLD_VENDOR_ID_C != ICU_LLD_VENDOR_ID)
#error "Siu_Icu_LLD.c and Icu_LLD.h have different vendor IDs"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((SIU_ICU_LLD_AR_MAJOR_VERSION_C != ICU_LLD_AR_MAJOR_VERSION) || \
         (SIU_ICU_LLD_AR_MINOR_VERSION_C != ICU_LLD_AR_MINOR_VERSION) || \
         (SIU_ICU_LLD_AR_PATCH_VERSION_C != ICU_LLD_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Siu_Icu_LLD.c and Icu_LLD.h are different"
    #endif
#endif
/* Check if source file and ICU_LLD.h header file are of the same Software version */
/** @remarks Covers ICU005 */
#if ((SIU_ICU_LLD_SW_MAJOR_VERSION_C != ICU_LLD_SW_MAJOR_VERSION) || \
     (SIU_ICU_LLD_SW_MINOR_VERSION_C != ICU_LLD_SW_MINOR_VERSION) || \
     (SIU_ICU_LLD_SW_PATCH_VERSION_C != ICU_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of Siu_Icu_LLD.c and Icu_LLD.h are different"
#endif

/* Check if source file and Reg_eSys_SIU.h file are of the same vendor */
#if (SIU_ICU_LLD_VENDOR_ID_C != SIU_VENDOR_ID_REG)
#error "Siu_Icu_LLD.c and Siu_Icu_LLD.h have different vendor IDs"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((SIU_ICU_LLD_AR_MAJOR_VERSION_C != SIU_AR_MAJOR_VERSION_REG) || \
         (SIU_ICU_LLD_AR_MINOR_VERSION_C != SIU_AR_MINOR_VERSION_REG) || \
         (SIU_ICU_LLD_AR_PATCH_VERSION_C != SIU_AR_PATCH_VERSION_REG))
    #error "AutoSar Version Numbers of Siu_Icu_LLD.c and Siu_Icu_LLD.h are different"
    #endif
#endif
/* Check if source file and Siu_Icu_LLD.h header file are of the same Software version */
#if ((SIU_ICU_LLD_SW_MAJOR_VERSION_C != SIU_SW_MAJOR_VERSION_REG) || \
     (SIU_ICU_LLD_SW_MINOR_VERSION_C != SIU_SW_MINOR_VERSION_REG) || \
     (SIU_ICU_LLD_SW_PATCH_VERSION_C != SIU_SW_PATCH_VERSION_REG))
#error "Software Version Numbers of Siu_Icu_LLD.c and Reg_eSys_SIU.h are different"
#endif


#ifdef CHECK_AUTOSAR_VERSION
    #if ((SIU_ICU_LLD_AR_MAJOR_VERSION_C != SCHM_ICU_AR_MAJOR_VERSION) || \
         (SIU_ICU_LLD_AR_MINOR_VERSION_C != SCHM_ICU_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Siu_Icu_LLD.c and SchM_Icu.h are different"
    #endif
#endif


/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/
/**
@{
@brief   SIU_DIRER_LOW - used for the high nibble of the register
@remarks Beside IRQ Channels, SIU provides also NMI capabilities. In order to not alter NMI settings
         all the writes to the DIRER register will affect only the high part where are
         the bits for Non Maskable Interrupts / Critical Interrupts Selection
*/
#define SIU_DIRER_HIGH           SIU_DIRER
/**@}*/

/**
@{
@brief   SIU_DIRER_LOW - used for the low nibble of the register
@remarks Beside IRQ Channels, SIU provides also NMI capabilities. In order to not alter NMI settings
         all the writes to the DIRER register will affect only the low part where are
         define the External Interrupt Request Enable.
*/
#define SIU_DIRER_LOW            (SIU_DIRER + 0x2U)
/**@}*/

/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/
#define ICU_START_SEC_VAR_UNSPECIFIED
/**
@file  Siu_Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
       "#include" See @ref Siu_Icu_LLD_c_1
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref Siu_Icu_LLD_c_2
       */
/*lint -save -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/


#define ICU_STOP_SEC_VAR_UNSPECIFIED
/**
@file  Siu_Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
       "#include" See @ref Siu_Icu_LLD_c_1
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref Siu_Icu_LLD_c_2
       */
/*lint -save -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define ICU_START_SEC_CODE
/**
@file  Siu_Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
       "#include" See @ref Siu_Icu_LLD_c_1
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref Siu_Icu_LLD_c_2
       */
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/


/**
@brief      SIU_LLD_EnableInterrupt
@details    Enable SIU Channel Interrupt
@param[in]  channelMask - Channel's Bit Mask
*/
STATIC FUNC (void, ICU_CODE) SIU_LLD_EnableInterrupt(VAR(uint32, AUTOMATIC) channelMask)
{
    SchM_Enter_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_17);
    {
        /**
        @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref Siu_Icu_LLD_c_3 */
        /* Clear pending flag */
        REG_WRITE32(SIU_EISR, channelMask);

        /**
        @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref Siu_Icu_LLD_c_3 */
        /* Enable interrupt */
        REG_BIT_SET16(SIU_DIRER_LOW, channelMask);
    }
    SchM_Exit_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_17);
}


/**
@brief      SIU_LLD_DisableInterrupt
@details    Disable SIU Channel Interrupt
@param[in]  channelMask - Channel's Bit Mask
*/
STATIC FUNC (void, ICU_CODE) SIU_LLD_DisableInterrupt(VAR(uint32, AUTOMATIC) channelMask)
{
    SchM_Enter_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_18);
    {
        /**
        @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref Siu_Icu_LLD_c_3 */
        /* Clear pending flag */
        REG_WRITE32(SIU_EISR, channelMask);

        /**
        @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref Siu_Icu_LLD_c_3 */
        /* Disable interrupt */
        REG_BIT_CLEAR16(SIU_DIRER_LOW, channelMask);
    }
    SchM_Exit_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_18);
}



/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

/**
@brief      SIU_LLD_InitChannel
@details    Initialize the ICU Channel
@param[in]  ParamValue
@param[in]  hwChannel - IRQ HW Channel
*/
FUNC (void, ICU_CODE) SIU_LLD_InitChannel(CONST(SIU_Icu_IRQ_ParamType, AUTOMATIC) ParamValue,
                                          CONST(SIU_Icu_IRQ_ChannelType, AUTOMATIC) hwChannel)
{
    VAR(uint32, AUTOMATIC) channelMask = SIU_CHANNEL_MASK(hwChannel);
#if (IPV_SIU == IPV_SIU_00_02_11_00)

    /* Set External IRQ Input Select Register */
    REG_BIT_CLEAR32(SIU_EIISR, SIU_EIISR_ESEL(hwChannel, (BIT1|BIT0)) );

#else
    VAR(uint32, ICU_CODE)  reg_SIU_ISEL = (uint32)((ParamValue & SIU_ISEL_REG_PARAM_MASK) >>
                                                                    SIU_ISEL_REG_PARAM_SHIFT) ;
    CONST(uint32,ICU_CODE)  value_SIU_ISEL = ((ParamValue & SIU_ISEL_PORT_PARAM_MASK) >>
                                                                   SIU_ISEL_PORT_PARAM_SHIFT) ;
    switch (reg_SIU_ISEL)
    {
        case SIU_ISEL1_REG:
            /**
            @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref Siu_Icu_LLD_c_3 */
            REG_BIT_SET32(SIU_ISEL1,SIU_EIISR_ESEL(hwChannel, value_SIU_ISEL));
            break;
        case SIU_ISEL2_REG:
            /**
            @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref Siu_Icu_LLD_c_3 */
            REG_BIT_SET32(SIU_ISEL1,SIU_EIISR_ESEL(hwChannel, BIT1|BIT0));
            REG_BIT_SET32(SIU_ISEL2,SIU_EIISR_ESEL(hwChannel, value_SIU_ISEL));
            break;
        default:
             /**
            @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref Siu_Icu_LLD_c_3 */
            REG_BIT_SET32(SIU_ISEL1,SIU_EIISR_ESEL(hwChannel, BIT1|BIT0));
            REG_BIT_SET32(SIU_ISEL2,SIU_EIISR_ESEL(hwChannel, BIT1|BIT0));
            REG_BIT_SET32(SIU_ISEL2A,SIU_EIISR_ESEL(hwChannel, value_SIU_ISEL));
            break;
    }
#endif
    /* Disable IRQ Interrupt */
    SIU_LLD_DisableInterrupt(channelMask);

    /* Set Activation Condition */
    SIU_LLD_SetActivationCondition(hwChannel,
              (SIU_ActivationType)((ParamValue & ICU_EDGE_PARAM_MASK) >> ICU_EDGE_PARAM_SHIFT));

}


/**
@brief      SIU_LLD_DeInit
@details    Deinitialize the ICU Channel
@param[in]  hwChannel   - IRQ HW Channel
*/
FUNC (void, ICU_CODE) SIU_LLD_DeInitChannel(VAR(SIU_Icu_IRQ_ChannelType, AUTOMATIC) hwChannel)
{
    VAR(uint32, AUTOMATIC) channelMask = SIU_CHANNEL_MASK(hwChannel);

    /* Disable IRQ Interrupt */
    SIU_LLD_DisableInterrupt(channelMask);

    /**
    @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref Siu_Icu_LLD_c_3 */
    /* Clear edge event enable registers */
    REG_BIT_CLEAR32(SIU_IREER, channelMask);
    REG_BIT_CLEAR32(SIU_IFEER, channelMask);

}



#if (ICU_SET_MODE_API == STD_ON)
/**
@brief      SIU_LLD_SetSleepMode
@details    Sets the ICU Channel mode
@param[in]  hwChannel      - IRQ HW Channel
@param[in]  WakeUpEnabled  - channel wakeup feature is enabled
*/
FUNC (void, ICU_CODE) SIU_LLD_SetSleepMode(VAR(SIU_Icu_IRQ_ChannelType, AUTOMATIC) hwChannel,
                                       VAR(boolean, AUTOMATIC) WakeUpEnabled)
{
    VAR(uint32, AUTOMATIC) channelMask = SIU_CHANNEL_MASK(hwChannel);

    if ((boolean)TRUE == WakeUpEnabled)
    {
        /* Enable IRQ Interrupt */
        SIU_LLD_EnableInterrupt(channelMask);
    }
    else
    {
        /* Disable IRQ Interrupt */
        SIU_LLD_DisableInterrupt(channelMask);
    }
}


/**
@brief      SIU_LLD_SetNormalMode
@details    Sets the ICU channel to normal mode
@param[in]  hwChannel   - IRQ HW Channel
@param[in]  NotificationActive          - channel notification is activated
*/
FUNC (void, ICU_CODE) SIU_LLD_SetNormalMode(VAR(SIU_Icu_IRQ_ChannelType, AUTOMATIC) hwChannel,
                                        VAR(boolean, AUTOMATIC) NotificationActive)
{
    VAR(uint32, AUTOMATIC) channelMask = SIU_CHANNEL_MASK(hwChannel);

    if ((boolean)TRUE == NotificationActive)
    {
        /* Enable IRQ Interrupt */
        SIU_LLD_EnableInterrupt(channelMask);
    }
    else
    {
        /* Disable IRQ Interrupt */
        SIU_LLD_DisableInterrupt(channelMask);
    }
}
#endif  /* ICU_SET_MODE_API */


/**
@brief      SIU_LLD_SetActivationCondition
@details    Set the activation condition for the given SIU IRQ Channel
@param[in]  hwChannel   - IRQ HW Channel
@param[in]  Activation       - activation condition
*/
FUNC (void, ICU_CODE) SIU_LLD_SetActivationCondition(
                                           VAR(SIU_Icu_IRQ_ChannelType, AUTOMATIC) hwChannel,
                                           VAR(SIU_ActivationType, AUTOMATIC) Activation)
{
    CONST(uint32, AUTOMATIC) channelMask = SIU_CHANNEL_MASK(hwChannel);

    switch (Activation)
    {
        case SIU_RISING_EDGE:
           /**
           @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref Siu_Icu_LLD_c_3 */
            REG_BIT_SET32(SIU_IREER, channelMask);
            REG_BIT_CLEAR32(SIU_IFEER, channelMask);
            break;

        case SIU_FALLING_EDGE:
           /**
           @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref Siu_Icu_LLD_c_3 */
            REG_BIT_CLEAR32(SIU_IREER, channelMask);
            REG_BIT_SET32(SIU_IFEER, channelMask);
            break;

        default:
            /**
            @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref Siu_Icu_LLD_c_3 */
            REG_BIT_SET32(SIU_IREER, channelMask);
            REG_BIT_SET32(SIU_IFEER, channelMask);
            break;
    }
}


/**
@brief      SIU_LLD_DisableNotification
@details    Disable notification for IRQ HW Channel
@param[in]  hwChannel   - IRQ HW Channel
*/
FUNC (void, ICU_CODE) SIU_LLD_DisableNotification(VAR(SIU_Icu_IRQ_ChannelType, AUTOMATIC) hwChannel)
{
    CONST(uint32, AUTOMATIC) channelMask = SIU_CHANNEL_MASK(hwChannel);

    /* Disable IRQ Interrupt */
    SIU_LLD_DisableInterrupt(channelMask);
}


/**
@brief      SIU_LLD_EnableNotification
@details    Enable notification for IRQ HW Channel
@param[in]  hwChannel   - IRQ HW Channel
*/
FUNC (void, ICU_CODE) SIU_LLD_EnableNotification(VAR(SIU_Icu_IRQ_ChannelType, AUTOMATIC) hwChannel)
{
    CONST(uint32, AUTOMATIC) channelMask = SIU_CHANNEL_MASK(hwChannel);

    /* Enable IRQ Interrupt */
    SIU_LLD_EnableInterrupt(channelMask);
}



#if (ICU_GET_INPUT_STATE_API == STD_ON)
/**
@brief      SIU_LLD_GetInputState
@details    Gets the input state of ICU hardware channel
@param[in]  hwChannel - IRQ HW Channel
@retval     ICU_ACTIVE - Icu_InputStateType
@retval     ICU_IDLE   - Icu_InputStateType
*/
FUNC (boolean, ICU_CODE) SIU_LLD_GetInputState(VAR(SIU_Icu_IRQ_ChannelType, AUTOMATIC) hwChannel)
{
    VAR(uint32, AUTOMATIC) channelMask = SIU_CHANNEL_MASK(hwChannel);
    VAR(boolean, AUTOMATIC) status = (boolean)FALSE;
    VAR(uint32, AUTOMATIC) reg_SIU_EISR  = REG_BIT_GET32(SIU_EISR, channelMask);
    VAR(uint32, AUTOMATIC) reg_SIU_DIRER = REG_BIT_GET32(SIU_DIRER, channelMask);

    /* Interrupt condition activated (ISR), interrupt not enabled (IRER) */
    if ((0x0U !=  reg_SIU_EISR) && (0x0U == reg_SIU_DIRER))
    {
        /**
        @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref Siu_Icu_LLD_c_3 */
        /* Clear IRQ Flag */
        REG_WRITE32(SIU_EISR, channelMask);
        status = (boolean)TRUE;
    }

    return status;
}
#endif  /* ICU_GET_INPUT_STATE_API */


#define ICU_STOP_SEC_CODE
/**
@file  Siu_Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
       "#include" See @ref Siu_Icu_LLD_c_1
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref Siu_Icu_LLD_c_2
       */
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif

