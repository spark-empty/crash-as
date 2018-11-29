/**
    @file eMIOS_Icu_LLD.c
    @version 2.0.0

    @brief   AUTOSAR Icu - eMIOS source file support for ICU driver.
    @details eMIOS source file, containing the variables and functions that are exported by the
             eMIOS driver.

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
@file    eMIOS_Icu_LLD.c
@remarks Implements DICU04000
*/
/**
@page misra_violations MISRA-C:2004 violations

@section eMIOS_Icu_LLD_c_1
Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before "#include"
This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003

@section eMIOS_Icu_LLD_c_2
Violates MISRA 2004 Required Rule 12.4, side effects on right hand of logical operator: '&&'
This violation  is not fixed since  the functions execution is not mandatory, both left hand and
right hand side of logical operator && are checking some status values

@section eMIOS_Icu_LLD_c_3
MISRA-C:2004  19.15 Precautions shall be taken in order to prevent the contents of a
header file being included twice.
This is not a violation since all header files are protected against multiple inclusions.

@section eMIOS_Icu_LLD_c_4
MISRA 2004 Required Rule 10.1 Implicit conversion changes signedness
This violation is not fixed since the expressions are constant values

@section eMIOS_Icu_LLD_c_5
MISRA 2004 Rule 11.3 cast from unsigned long to pointer [Encompasses MISRA 2004 Rule 11.1],
This rule can not be avoided because it appears when addressing memory mapped registers
or other hardware specific feature

@section eMIOS_Icu_LLD_c_6
MISRA-C:2004 17.4: Array indexing shall be the only allowed form of pointer arithmetic.
This violation is due to the use of pointer arithematic, to access the channel parameters,
the indexing of the pointer is taken care and hence the unintended memory location will not
be accessed.
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
/**
@file  eMIOS_Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref eMIOS_Icu_LLD_c_3
*/
/*lint -save -e537*/
#include "eMIOS_Icu_LLD.h"
#include "Reg_eSys_EMIOS.h"
#include "Reg_eSys_EMIOS_CfgEx.h"
#include "Reg_Macros.h"
#include "SchM_Icu.h"
#include "Icu_LLD.h"
/*lint -restore*/


/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/**
@{
@brief   Source file version information
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define EMIOS_ICU_LLD_VENDOR_ID_C           43

#define EMIOS_ICU_LLD_AR_MAJOR_VERSION_C    3
#define EMIOS_ICU_LLD_AR_MINOR_VERSION_C    0
#define EMIOS_ICU_LLD_AR_PATCH_VERSION_C    0
#define EMIOS_ICU_LLD_SW_MAJOR_VERSION_C    2
#define EMIOS_ICU_LLD_SW_MINOR_VERSION_C    0
#define EMIOS_ICU_LLD_SW_PATCH_VERSION_C    0
/**@}*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and ICU header file are of the same vendor */
/**
 @file    eMIOS_Icu_LLD.c
 @remarks Covers ICU005
*/
#if (EMIOS_ICU_LLD_VENDOR_ID_C != EMIOS_ICU_LLD_VENDOR_ID)
#error "eMIOS_Icu_LLD.c and eMIOS_Icu_LLD.h have different vendor IDs"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and eMIOS_Icu_LLD header file are of the same Autosar version */
    #if ((EMIOS_ICU_LLD_AR_MAJOR_VERSION_C != EMIOS_ICU_LLD_AR_MAJOR_VERSION) || \
         (EMIOS_ICU_LLD_AR_MINOR_VERSION_C != EMIOS_ICU_LLD_AR_MINOR_VERSION) || \
         (EMIOS_ICU_LLD_AR_PATCH_VERSION_C != EMIOS_ICU_LLD_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of eMIOS_Icu_LLD.c and eMIOS_Icu_LLD.h are different"
    #endif
#endif

/* Check if source file and eMIOS_Icu_LLD header file are of the same Software version */
#if ((EMIOS_ICU_LLD_SW_MAJOR_VERSION_C != EMIOS_ICU_LLD_SW_MAJOR_VERSION) || \
     (EMIOS_ICU_LLD_SW_MINOR_VERSION_C != EMIOS_ICU_LLD_SW_MINOR_VERSION) || \
     (EMIOS_ICU_LLD_SW_PATCH_VERSION_C != EMIOS_ICU_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of eMIOS_Icu_LLD.c and eMIOS_Icu_LLD.h are different"
#endif


#ifdef CHECK_AUTOSAR_VERSION
    /* Check if eMIOS_Icu_LLD.h and SchM_Icu.h file are of the same Autosar version */
    #if ((EMIOS_ICU_LLD_AR_MAJOR_VERSION_C != SCHM_ICU_AR_MAJOR_VERSION) || \
         (EMIOS_ICU_LLD_AR_MINOR_VERSION_C != SCHM_ICU_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of eMIOS_Icu_LLD.c and SchM_Icu.h are different"
    #endif
#endif


/* Check if eMIOS_Icu_LLD.c and Reg_eSys_EMIOS_CfgEx.h file are of the same vendor */
/**
 @file    eMIOS_Icu_LLD.c
 @remarks Covers ICU005
*/
#if (EMIOS_ICU_LLD_VENDOR_ID_C != REG_ESYS_EMIOS_CFGEX_H_VENDOR_ID)
#error "eMIOS_Icu_LLD.c and Reg_eSys_EMIOS_CfgEx.h have different vendor IDs"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if eMIOS_Icu_LLD.c and Reg_eSys_EMIOS_CfgEx.h file are of the same Autosar version */
    #if ((EMIOS_ICU_LLD_AR_MAJOR_VERSION_C != REG_ESYS_EMIOS_CFGEX_H_AR_MAJOR_VERSION) || \
         (EMIOS_ICU_LLD_AR_MINOR_VERSION_C != REG_ESYS_EMIOS_CFGEX_H_AR_MINOR_VERSION) || \
         (EMIOS_ICU_LLD_AR_PATCH_VERSION_C != REG_ESYS_EMIOS_CFGEX_H_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of eMIOS_Icu_LLD.c and Reg_eSys_EMIOS_CfgEx.h are different"
    #endif
#endif
/* Check if eMIOS_Icu_LLD.c and Reg_eSys_EMIOS_CfgEx.h file are of the same Software version */
#if ((EMIOS_ICU_LLD_SW_MAJOR_VERSION_C != REG_ESYS_EMIOS_CFGEX_H_SW_MAJOR_VERSION) || \
     (EMIOS_ICU_LLD_SW_MINOR_VERSION_C != REG_ESYS_EMIOS_CFGEX_H_SW_MINOR_VERSION) || \
     (EMIOS_ICU_LLD_SW_PATCH_VERSION_C != REG_ESYS_EMIOS_CFGEX_H_SW_PATCH_VERSION))
#error "Software Version Numbers of eMIOS_Icu_LLD.c and Reg_eSys_EMIOS_CfgEx.h are different"
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


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/
#define ICU_START_SEC_VAR_UNSPECIFIED
/**
@file  eMIOS_Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
       "#include"
       See @ref eMIOS_Icu_LLD_c_1 */
/*lint -save -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/


#define ICU_STOP_SEC_VAR_UNSPECIFIED
/**
@file  eMIOS_Icu_LLD.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
      "#include"
      See @ref eMIOS_Icu_LLD_c_1 */
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
@file  eMIOS_Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
       "#include"
       See @ref eMIOS_Icu_LLD_c_1 */
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

/*================================================================================================*/
/**
@brief      Icu driver function that enables the eMIOS channel interrupt
@details    This function Clears the pending interrupts of eMIOS channels and
            enables eMIOS Channel interrupt

@param[in]  mIdx  - eMIOS module index
@param[in]  chIdx - eMIOS Channel index
*/
/*================================================================================================*/
STATIC FUNC (void, ICU_CODE) eMIOS_LLD_EnableInterrupt(CONST(uint8, AUTOMATIC) mIdx,
                                                       CONST(uint8, AUTOMATIC) chIdx)
{
    SchM_Enter_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_13);
    {
       /**
       @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5 */
        /* Clear pending flag */
        REG_WRITE32(EMIOS_CSR(mIdx, chIdx), CSR_FLAG_MASK);

       /**
       @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5 */
        /* Enable interrupt */
        REG_BIT_SET32(EMIOS_CCR(mIdx, chIdx), CCR_FEN_MASK);
    }
    SchM_Exit_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_13);
}

/*================================================================================================*/
/**
@brief      Icu driver function that disables the eMIOS channel interrupt
@details    This function disables eMIOS Channel interrupt

@param[in]  mIdx -  eMIOS module index
@param[in]  chIdx - eMIOS Channel index
*/
/*================================================================================================*/
STATIC FUNC (void, ICU_CODE) eMIOS_LLD_DisableInterrupt(CONST(uint8, AUTOMATIC) mIdx,
                                                        CONST(uint8, AUTOMATIC) chIdx)
{
    SchM_Enter_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_14);
    {
        /**
           @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5 */
        /* Disable interrupt */
        REG_BIT_CLEAR32(EMIOS_CCR(mIdx, chIdx), CCR_FEN_MASK);
    }
    SchM_Exit_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_14);
}

/*================================================================================================*/
/**
@brief      Icu driver function that sets the requested mode for eMIOS Channels.
@details    This function sets CCR_MODE bitfield, the mode of operation of the Unified Channel

@param[in]  mIdx  - eMIOS module index
@param[in]  chIdx - eMIOS Channel index
@param[in]  mode  - CCR_MODE bitfield value to be set
*/
/*================================================================================================*/
STATIC FUNC (void, ICU_CODE) eMIOS_LLD_UCSetMode(CONST(uint8, AUTOMATIC) mIdx,
                                                 CONST(uint8, AUTOMATIC) chIdx,
                                                 CONST(uint32, AUTOMATIC) mode)
{
    SchM_Enter_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_15);
    {
        /**
           @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5 */
        /* Clear MODE bitfield - GPIO mode */
        REG_BIT_CLEAR32(EMIOS_CCR(mIdx, chIdx), CCR_MODE_MASK);

       /**
       @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5 */
        /* Set desired mode */
        REG_BIT_SET32(EMIOS_CCR(mIdx, chIdx), mode & CCR_MODE_MASK);
    }
    SchM_Exit_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_15);
}


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

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
                                            CONST(uint8, AUTOMATIC) hwChannel)
{
    CONST(uint8, ICU_CODE) mIdx  = (uint8)((hwChannel & EMIOS_MOD_MASK) >> EMIOS_MOD_SHIFT);
    CONST(uint8, ICU_CODE) chIdx = (uint8)((hwChannel & EMIOS_CH_MASK)  >> EMIOS_CH_SHIFT);

    VAR(uint32, ICU_CODE) regCCR = CCR_UCPREN_MASK | (CCR_FCK_PRESCALED << CCR_FCK_SHIFT);

#ifdef EMIOS_UCDIS_AVAILABLE
#if (EMIOS_UCDIS_AVAILABLE == STD_ON)
    /* Enable eMIOS Channel */
    REG_BIT_CLEAR32(EMIOS_UCDIS(mIdx), (uint32)(BIT0 << chIdx));
/* EMIOS_UCDIS_AVAILABLE */
#endif  
#endif
    /* Enter GPIO Mode to Configure Channel
     * Reset mode for selected channel
     */

       /**
          @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5
          */
    REG_WRITE32(EMIOS_CCR(mIdx, chIdx), (uint32)0x00000000U);


    /* Initialize prescaler value, channel filter, freeze enable, and bus select and disable the
     *  prescaler The definition on which edge the period starts
     * Set Default Edge (included)
     */
    regCCR |= ((ParamValue & ICU_EMIOS_FREEZE_PARAM_MASK) >> ICU_EMIOS_FREEZE_PARAM_SHIFT) <<
            CCR_FREN_SHIFT;
    regCCR |= ((ParamValue & ICU_EMIOS_PRESCALER_PARAM_MASK) >> ICU_EMIOS_PRESCALER_PARAM_SHIFT) <<
            CCR_UCPRE_SHIFT;
    regCCR |= ((ParamValue & ICU_EMIOS_DIG_FILTER_PARAM_MASK) >> ICU_EMIOS_DIG_FILTER_PARAM_SHIFT)
            << CCR_IF_SHIFT;
    regCCR |= ((ParamValue & ICU_EMIOS_BUS_SELECT_PARAM_MASK) >> ICU_EMIOS_BUS_SELECT_PARAM_SHIFT)
            << CCR_BSL_SHIFT;
    /**
       @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5 */
    REG_WRITE32(EMIOS_CCR(mIdx, chIdx), regCCR);

    /* Disable interrupt */
    eMIOS_LLD_DisableInterrupt(mIdx, chIdx);

    /**
     @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5
     */
    /* Clear pending interrupt flag (and other flags) for the channel */
    REG_WRITE32(EMIOS_CSR(mIdx, chIdx), (uint32)(CSR_OVR_MASK | CSR_OVFL_MASK | CSR_FLAG_MASK));

    eMIOS_LLD_SetActivationCondition(hwChannel,
           (eMIOS_ActivationType)((ParamValue & ICU_EDGE_PARAM_MASK) >> ICU_EDGE_PARAM_SHIFT));

    if (EMIOS_CHANNEL_MODE_EDGE_DETECT == channelMode)
    {
        /* Enable SAIC mode */
        eMIOS_LLD_UCSetMode(mIdx, chIdx, CCR_MODE_SAIC);
    }
}

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
                                              VAR(boolean,AUTOMATIC) reg_EMIOSB_available)
{
    CONST(uint8, ICU_CODE) mIdx  = (uint8)((hwChannel & EMIOS_MOD_MASK) >> EMIOS_MOD_SHIFT);
    CONST(uint8, ICU_CODE) chIdx = (uint8)((hwChannel & EMIOS_CH_MASK)  >> EMIOS_CH_SHIFT);

     /**
     @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5 */
    /* Set all channel registers as after reset */
    REG_WRITE32(EMIOS_CCR(mIdx, chIdx), EMIOS_CCR_CLEAR);
    REG_WRITE32(EMIOS_CADR(mIdx, chIdx), EMIOS_CADR_CLEAR);

    if ((boolean)TRUE == reg_EMIOSB_available)
    {
        REG_WRITE32(EMIOS_CBDR(mIdx, chIdx), EMIOS_CBDR_CLEAR);
    }

    /**
   @note  Violates MISRA 2004 Required Rule 10.1 Implicit conversion changes signedness
   @ref eMIOS_Icu_LLD_c_4 */
    if ((boolean)TRUE == reg_EMIOSCNT_available)
    {
        /**
        @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5 */
        REG_WRITE32(EMIOS_CCNTR(mIdx, chIdx), EMIOS_CCNTR_CLEAR);
    }

     /**
    @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5 */
    REG_WRITE32(EMIOS_CSR(mIdx, chIdx), EMIOS_CSR_CLEAR);

#ifdef EMIOS_UCDIS_AVAILABLE
#if (EMIOS_UCDIS_AVAILABLE == STD_ON)
    /* Disable eMIOS Channel */
    REG_BIT_SET32(EMIOS_UCDIS(mIdx), (uint32)(BIT0 << chIdx));
#endif
/* EMIOS_UCDIS_AVAILABLE */
#endif  
}

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
                                             VAR(boolean, AUTOMATIC) WakeUpEnabled)
{
    CONST(uint8, ICU_CODE) mIdx  = (uint8)((hwChannel & EMIOS_MOD_MASK) >> EMIOS_MOD_SHIFT);
    CONST(uint8, ICU_CODE) chIdx = (uint8)((hwChannel & EMIOS_CH_MASK)  >> EMIOS_CH_SHIFT);

    if (WakeUpEnabled)
    {
        eMIOS_LLD_EnableInterrupt(mIdx, chIdx);
    }
    else
    {
        eMIOS_LLD_DisableInterrupt(mIdx, chIdx);
    }
}

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
                                              VAR(boolean, AUTOMATIC) NotificationActive)
{
    CONST(uint8, ICU_CODE) mIdx  = (uint8)((hwChannel & EMIOS_MOD_MASK) >> EMIOS_MOD_SHIFT);
    CONST(uint8, ICU_CODE) chIdx = (uint8)((hwChannel & EMIOS_CH_MASK)  >> EMIOS_CH_SHIFT);

    if (NotificationActive)
    {
        eMIOS_LLD_EnableInterrupt(mIdx, chIdx);
    }
    else
    {
        eMIOS_LLD_DisableInterrupt(mIdx, chIdx);
    }
}
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
                                                    VAR(eMIOS_ActivationType, AUTOMATIC) activation)
{
    CONST(uint8, ICU_CODE) mIdx  = (uint8)((hwChannel & EMIOS_MOD_MASK) >> EMIOS_MOD_SHIFT);
    CONST(uint8, ICU_CODE) chIdx = (uint8)((hwChannel & EMIOS_CH_MASK)  >> EMIOS_CH_SHIFT);
#ifdef SIGNAL_MEASUREMENT_USES_SAIC_MODE
    VAR(uint32, AUTOMATIC) reg_EMIOS_CCR;
/* SIGNAL_MEASUREMENT_USES_SAIC_MODE */
#endif  
    switch (activation)
    {
#ifdef SIGNAL_MEASUREMENT_USES_SAIC_MODE
        case EMIOS_OPPOSITE_EDGES:
            reg_EMIOS_CCR = REG_READ32(EMIOS_CCR(mIdx, chIdx));
            /**
            @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5 */
            REG_WRITE32(EMIOS_CCR(mIdx, chIdx),(reg_EMIOS_CCR ^ CCR_EDPOL_MASK));
            break;
 /* SIGNAL_MEASUREMENT_USES_SAIC_MODE */
#endif 

        case EMIOS_BOTH_EDGES:
            /**
            @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5 */
         /* Disables the flag generation as defined by EDPOL Bit */
            REG_BIT_SET32(EMIOS_CCR(mIdx, chIdx), CCR_EDSEL_MASK);
            break;

        case EMIOS_RISING_EDGE:
            /**
            @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5 */
            REG_BIT_CLEAR32(EMIOS_CCR(mIdx, chIdx), CCR_EDSEL_MASK);
            REG_BIT_SET32(EMIOS_CCR(mIdx, chIdx), CCR_EDPOL_MASK);
            break;

        default:
            /* EMIOS_FALLING_EDGE */
            /**
            @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5 */
            REG_BIT_CLEAR32(EMIOS_CCR(mIdx, chIdx), (CCR_EDSEL_MASK | CCR_EDPOL_MASK));
            break;
    }
}

/*================================================================================================*/
/**
@brief       Icu driver function that disables the eMIOS channel notifification/IRQ.
@details     This function disables the interrupt corresponding to the eMIOS channel.

@param[in]   hwChannel   - eMIOS encoded hardware channel
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) eMIOS_LLD_DisableNotification(VAR(uint8, AUTOMATIC) hwChannel)
{
    CONST(uint8, ICU_CODE) mIdx  = (uint8)((hwChannel & EMIOS_MOD_MASK) >> EMIOS_MOD_SHIFT);
    CONST(uint8, ICU_CODE) chIdx = (uint8)((hwChannel & EMIOS_CH_MASK)  >> EMIOS_CH_SHIFT);

    /* Disable Interrupt */
    eMIOS_LLD_DisableInterrupt(mIdx, chIdx);
}

/*================================================================================================*/
/**
@brief      Icu driver function that enables the eMIOS channel notifification/IRQ.
@details    This function enables the interrupt corresponding to the eMIOS channel.

@param[in]  hwChannel   - eMIOS encoded hardware channel
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) eMIOS_LLD_EnableNotification(VAR(uint8, AUTOMATIC) hwChannel)
{
    CONST(uint8, ICU_CODE) mIdx  = (uint8)((hwChannel & EMIOS_MOD_MASK) >> EMIOS_MOD_SHIFT);
    CONST(uint8, ICU_CODE) chIdx = (uint8)((hwChannel & EMIOS_CH_MASK)  >> EMIOS_CH_SHIFT);

    /* Enable Interrupt */
    eMIOS_LLD_EnableInterrupt(mIdx, chIdx);
}

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
FUNC (boolean, ICU_CODE) eMIOS_LLD_GetInputState(VAR(uint8, AUTOMATIC) hwChannel)
{
    CONST(uint8, ICU_CODE) mIdx  = (uint8)((hwChannel & EMIOS_MOD_MASK) >> EMIOS_MOD_SHIFT);
    CONST(uint8, ICU_CODE) chIdx = (uint8)((hwChannel & EMIOS_CH_MASK)  >> EMIOS_CH_SHIFT);
    VAR(boolean, AUTOMATIC) result = (boolean)FALSE;
    CONST(uint32, ICU_CODE) value_CCR_FEN  = REG_BIT_GET32(EMIOS_CCR(mIdx, chIdx), CCR_FEN_MASK);
    CONST(uint32, ICU_CODE) value_CSR_FLAG = REG_BIT_GET32(EMIOS_CSR(mIdx, chIdx), CSR_FLAG_MASK);


       /**
       @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5 */
    /* Interrupt not enabled, flag bit was set */
    if ( (value_CCR_FEN != CCR_FEN_MASK) &&
         (value_CSR_FLAG == CSR_FLAG_MASK) )
   {
        SchM_Enter_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_16);
        {
            /**
            @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer
            @ref eMIOS_Icu_LLD_c_5 */
            /* Clear pending interrupt */
            REG_WRITE32(EMIOS_CSR(mIdx, chIdx), CSR_FLAG_MASK);
        }
        SchM_Exit_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_16);


        result = (boolean)TRUE;
    }

    return result;
}
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
FUNC (void, ICU_CODE) eMIOS_LLD_StartTimestamp(VAR(uint8, AUTOMATIC) hwChannel)
{
    CONST(uint8, ICU_CODE) mIdx  = (uint8)((hwChannel & EMIOS_MOD_MASK) >> EMIOS_MOD_SHIFT);
    CONST(uint8, ICU_CODE) chIdx = (uint8)((hwChannel & EMIOS_CH_MASK)  >> EMIOS_CH_SHIFT);


    /* Make sure channel is in GPIO mode before switching modes */
    eMIOS_LLD_UCSetMode(mIdx, chIdx, CCR_MODE_GPI);

     /**
       @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5 */
    /* Clear pending interrupts */
    REG_WRITE32(EMIOS_CSR(mIdx, chIdx), (uint32)(CSR_OVR_MASK | CSR_OVFL_MASK | CSR_FLAG_MASK));

    /* Enable SAIC mode */
    eMIOS_LLD_UCSetMode(mIdx, chIdx, CCR_MODE_SAIC);

    /* Enable Interrupt */
    eMIOS_LLD_EnableInterrupt(mIdx, chIdx);
}
/* ICU_TIMESTAMP_API */
#endif  

#if (ICU_TIMESTAMP_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that stops time stamp measurement of eMIOS channel.
@details    This function:
            - Puts the eMIOS channel into GPIO mode
            - Disables the interrupt for the channel

@param[in]  hwChannel   - eMIOS encoded hardware channel
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) eMIOS_LLD_StopTimestamp(VAR(uint8, AUTOMATIC) hwChannel)
{
    CONST(uint8, ICU_CODE) mIdx  = (uint8)((hwChannel & EMIOS_MOD_MASK) >> EMIOS_MOD_SHIFT);
    CONST(uint8, ICU_CODE) chIdx = (uint8)((hwChannel & EMIOS_CH_MASK)  >> EMIOS_CH_SHIFT);

    /* Stop timestamping */
    eMIOS_LLD_UCSetMode(mIdx, chIdx, CCR_MODE_GPI);

    /* Disable interrupt */
    eMIOS_LLD_DisableInterrupt(mIdx, chIdx);
}

/*================================================================================================*/
/**
@brief      Icu driver function that returns the time stamp index of eMIOS channel.
@details    Returns the captured value in register A

@param[in]  hwChannel - eMIOS encoded hardware channel

@return     uint32 - The captured value in register A
*/
/*================================================================================================*/
FUNC(uint32, ICU_CODE) eMIOS_GetTimeStamp(VAR(uint8, AUTOMATIC) hwChannel)
{
    CONST(uint8, ICU_CODE) mIdx  = (uint8)((hwChannel & EMIOS_MOD_MASK) >> EMIOS_MOD_SHIFT);
    CONST(uint8, ICU_CODE) chIdx = (uint8)((hwChannel & EMIOS_CH_MASK)  >> EMIOS_CH_SHIFT);

    return REG_READ32(EMIOS_CADR(mIdx, chIdx));
}
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
FUNC (void, ICU_CODE) eMIOS_LLD_ResetEdgeCount(VAR(uint8, AUTOMATIC) hwChannel)
{
    CONST(uint8, ICU_CODE) mIdx  = (uint8)((hwChannel & EMIOS_MOD_MASK) >> EMIOS_MOD_SHIFT);
    CONST(uint8, ICU_CODE) chIdx = (uint8)((hwChannel & EMIOS_CH_MASK)  >> EMIOS_CH_SHIFT);
    VAR(uint32, ICU_CODE) prevMode;

    prevMode = REG_BIT_GET32(EMIOS_CCR(mIdx, chIdx), CCR_MODE_MASK);

    /* Enter GPIO Mode */
    eMIOS_LLD_UCSetMode(mIdx, chIdx, CCR_MODE_GPI);

    /**
    @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5 */
    /* Reset counter */
    REG_WRITE32(EMIOS_CCNTR(mIdx, chIdx), EMIOS_CCNTR_INIT);

    /**
    @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5 */
    /* Max. value for register A. If reached, overflow interrupt */
    REG_WRITE32(EMIOS_CADR(mIdx, chIdx), EMIOS_INIT_CADR);

     /**
     @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5 */
    /* Clear pending interrupts */
    REG_WRITE32(EMIOS_CSR(mIdx, chIdx), (uint32)(CSR_OVR_MASK | CSR_OVFL_MASK | CSR_FLAG_MASK));

    /* Restore previous mode */
    eMIOS_LLD_UCSetMode(mIdx, chIdx, prevMode);
}
/* ICU_EDGE_COUNT_API */
#endif  

#if (ICU_EDGE_COUNT_API == STD_ON)
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
                                                VAR(uint32, AUTOMATIC) startValue)
{
    CONST(uint8, ICU_CODE) mIdx  = (uint8)((hwChannel & EMIOS_MOD_MASK) >> EMIOS_MOD_SHIFT);
    CONST(uint8, ICU_CODE) chIdx = (uint8)((hwChannel & EMIOS_CH_MASK)  >> EMIOS_CH_SHIFT);

    /* Make sure channel is in GPIO mode before switching modes */
    eMIOS_LLD_UCSetMode(mIdx, chIdx, CCR_MODE_GPI);

    /* Sync. eMIOS counter value. (Needed in case of stopping and re-enabling counting)
     * Note: Setting GPIO mode, the internal counter was cleared and must be restored
     */
     /**
    @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5 */
    REG_WRITE32(EMIOS_CCNTR(mIdx, chIdx), startValue);

    /**
    @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5 */
    /* Set Max. A value */
    REG_WRITE32(EMIOS_CADR(mIdx, chIdx), EMIOS_INIT_CADR);

     /**
    @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5 */
    /* Clear pending interrupts */
    REG_WRITE32(EMIOS_CSR(mIdx, chIdx), (uint32)(CSR_OVR_MASK | CSR_OVFL_MASK | CSR_FLAG_MASK));

    /* Modulus counter mode */
    eMIOS_LLD_UCSetMode(mIdx, chIdx, CCR_MODE_MCB_EXT_CLOCK);

    /* Enable interrupt */
    eMIOS_LLD_EnableInterrupt(mIdx, chIdx);
}
/* ICU_EDGE_COUNT_API */
#endif  

#if (ICU_EDGE_COUNT_API == STD_ON)
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
                                               P2VAR(uint32, AUTOMATIC, ICU_APPL_DATA) currentValue)
{
    CONST(uint8, ICU_CODE) mIdx  = (uint8)((hwChannel & EMIOS_MOD_MASK) >> EMIOS_MOD_SHIFT);
    CONST(uint8, ICU_CODE) chIdx = (uint8)((hwChannel & EMIOS_CH_MASK)  >> EMIOS_CH_SHIFT);

    /* Disable interrupt */
    eMIOS_LLD_DisableInterrupt(mIdx, chIdx);

     /**
    @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5 */
    /* Clear pending interrupts */
    REG_WRITE32(EMIOS_CSR(mIdx, chIdx), (uint32)(CSR_OVR_MASK | CSR_OVFL_MASK | CSR_FLAG_MASK));

    /* Save count, before going to GPIO mode (because counter is reset to 0x0000) */
    *currentValue = REG_READ32(EMIOS_CCNTR(mIdx, chIdx));

    /* Disable MCB mode */
    eMIOS_LLD_UCSetMode(mIdx, chIdx, CCR_MODE_GPI);
}
/* ICU_EDGE_COUNT_API */
#endif  

#if (ICU_EDGE_COUNT_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that gets edge counter measurement of eMIOS channel.
@details    This function returns counter value (the number of counter edges) of eMIOS channel

@param[in]  hwChannel   - eMIOS encoded hardware channel

@return     uint32 - Counted edges number
*/
/*================================================================================================*/
FUNC (uint32, ICU_CODE) eMIOS_LLD_GetEdgeNumbers(VAR(uint8, AUTOMATIC) hwChannel)
{
    CONST(uint8, ICU_CODE) mIdx  = (uint8)((hwChannel & EMIOS_MOD_MASK) >> EMIOS_MOD_SHIFT);
    CONST(uint8, ICU_CODE) chIdx = (uint8)((hwChannel & EMIOS_CH_MASK)  >> EMIOS_CH_SHIFT);

    return REG_READ32(EMIOS_CCNTR(mIdx, chIdx));
}
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
                                                    VAR(eMIOS_OperationMode, AUTOMATIC) mode)
{
    CONST(uint8, ICU_CODE) mIdx  = (uint8)((hwChannel & EMIOS_MOD_MASK) >> EMIOS_MOD_SHIFT);
    CONST(uint8, ICU_CODE) chIdx = (uint8)((hwChannel & EMIOS_CH_MASK)  >> EMIOS_CH_SHIFT);

    /* Disable interrupt */
    eMIOS_LLD_DisableInterrupt(mIdx, chIdx);

    /* Enter GPIO Mode */
    eMIOS_LLD_UCSetMode(mIdx, chIdx, CCR_MODE_GPI);

    /* Set activation condition */
    eMIOS_LLD_SetActivationCondition(hwChannel, activation);

    if (EMIOS_UC_IPWM_MODE == mode)
    {
        /* Enable IPWM mode */
        eMIOS_LLD_UCSetMode(mIdx, chIdx, CCR_MODE_IPWM);

    }
    else if (EMIOS_UC_IPM_MODE == mode)
    {
        /* Enable IPM mode */
        eMIOS_LLD_UCSetMode(mIdx, chIdx, CCR_MODE_IPM);

    }
    else
    {
        /* Enable SAIC mode */
        eMIOS_LLD_UCSetMode(mIdx, chIdx, CCR_MODE_SAIC);
    }
    /**
    @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5 */
    /* Clear pending interrupt flag (and other flags) for the channel */
    REG_WRITE32(EMIOS_CSR(mIdx, chIdx), (uint32)(CSR_OVR_MASK | CSR_OVFL_MASK | CSR_FLAG_MASK));

    /* Enable Interrupt */
    eMIOS_LLD_EnableInterrupt(mIdx, chIdx);
}
/* ICU_SIGNAL_MEASUREMENT_API */
#endif  

#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
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
FUNC (void, ICU_CODE) eMIOS_LLD_StopSignalMeasurement(VAR(uint8, AUTOMATIC) hwChannel)
{
    CONST(uint8, ICU_CODE) mIdx  = (uint8)((hwChannel & EMIOS_MOD_MASK) >> EMIOS_MOD_SHIFT);
    CONST(uint8, ICU_CODE) chIdx = (uint8)((hwChannel & EMIOS_CH_MASK)  >> EMIOS_CH_SHIFT);

    /* Enter GPIO Mode */
    eMIOS_LLD_UCSetMode(mIdx, chIdx, CCR_MODE_GPI);

    /**
    @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5 */
    /* EDSEL is set to 1 to discard the input in GPIO mode (not to repond the input signal
       in GPIO mode)*/
    /* Disables the flag generation as defined by EDPOL Bit */
    REG_BIT_SET32(EMIOS_CCR(mIdx, chIdx), CCR_EDSEL_MASK);


    /* Disable interrupt */
    eMIOS_LLD_DisableInterrupt(mIdx, chIdx);

    /**
    @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5 */
    /* Clear pending interrupt flag (and other flags) for the channel */
    REG_WRITE32(EMIOS_CSR(mIdx, chIdx), (uint32)(CSR_OVR_MASK | CSR_OVFL_MASK | CSR_FLAG_MASK));
}
/* ICU_SIGNAL_MEASUREMENT_API */
#endif  

#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that gets the RegisterA value of eMIOS channel
@details    This function returns the register A of the given eMIOS Unified Channel
@param[in]  hwChannel  - eMIOS encoded hardware channel
@return     uint32 - Captured value of the register A
*/
/*================================================================================================*/
FUNC(uint32, ICU_CODE) eMIOS_LLD_GetCaptureRegA(VAR(uint8, AUTOMATIC) hwChannel)
{
    CONST(uint8, ICU_CODE) mIdx  = (uint8)((hwChannel & EMIOS_MOD_MASK) >> EMIOS_MOD_SHIFT);
    CONST(uint8, ICU_CODE) chIdx = (uint8)((hwChannel & EMIOS_CH_MASK)  >> EMIOS_CH_SHIFT);

    return REG_READ32(EMIOS_CADR(mIdx, chIdx));
}

/*================================================================================================*/
/**
@brief      Icu driver function that gets the RegisterB value of eMIOS channel
@details    This function returns the register B of the given eMIOS Unified Channel
@param[in]  hwChannel  - eMIOS encoded hardware channel
@return     uint32 - Captured value of the register B
*/
/*================================================================================================*/
FUNC(uint32, ICU_CODE) eMIOS_LLD_GetCaptureRegB(VAR(uint8, AUTOMATIC) hwChannel)
{
    CONST(uint8, ICU_CODE) mIdx  = (uint8)((hwChannel & EMIOS_MOD_MASK) >> EMIOS_MOD_SHIFT);
    CONST(uint8, ICU_CODE) chIdx = (uint8)((hwChannel & EMIOS_CH_MASK)  >> EMIOS_CH_SHIFT);

    return REG_READ32(EMIOS_CBDR(mIdx, chIdx));
}
/* ICU_SIGNAL_MEASUREMENT_API */
#endif  

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
FUNC (boolean, ICU_CODE) eMIOS_LLD_CheckOverflowFlag(CONST(uint32, AUTOMATIC) flags)
{
    return ((CSR_OVFL_BIT == (flags & CSR_OVFL_BIT)) ? (boolean)TRUE : (boolean)FALSE);
}

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
FUNC (void, ICU_CODE) EMIOS_Icu_LLD_ProcessInterrupt(CONST(uint8, AUTOMATIC) hwChannel)
{
    CONST(uint8, ICU_CODE) mIdx  = (uint8)((hwChannel & EMIOS_MOD_MASK) >> EMIOS_MOD_SHIFT);
    CONST(uint8, ICU_CODE) chIdx = (uint8)((hwChannel & EMIOS_CH_MASK)  >> EMIOS_CH_SHIFT);
    VAR(uint32, ICU_CODE) regCSR;

    /* Read UC Status Register */
    regCSR = REG_READ32(EMIOS_CSR(mIdx, chIdx));

    /**
    @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref eMIOS_Icu_LLD_c_5 */
    /* Clear pending interrupt serviced */
    REG_WRITE32(EMIOS_CSR(mIdx, chIdx), regCSR & (CSR_OVR_BIT | CSR_OVFL_BIT | CSR_FLAG_BIT));

    /* Process interrupt for ICU logical channel */
    /**
@file  eMIOS_Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4, Array indexing shall be the only allowed form of
pointer arithmetic. being included twice See @ref eMIOS_Icu_LLD_c_6
*/
    Icu_ProcessCommonInterrupt(Icu_Cfg_Ptr->Icu_HWMap[eMIOS_ICU_CHANNEL(hwChannel)], regCSR);
}

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
                                                    CONST(uint8, AUTOMATIC) hwChannel)
{
    CONST(uint8, ICU_CODE) mIdx  = (uint8)((hwChannel & EMIOS_MOD_MASK) >> EMIOS_MOD_SHIFT);
    CONST(uint8, ICU_CODE) chIdx = (uint8)((hwChannel & EMIOS_CH_MASK)  >> EMIOS_CH_SHIFT);

    VAR(uint32, ICU_CODE) regMCR = REG_READ32(EMIOS_MCR(mIdx));
    VAR(uint32, ICU_CODE) regCCR = REG_READ32(EMIOS_CCR(mIdx, chIdx));

    /* Clear GPREN bit */
    REG_BIT_CLEAR32(EMIOS_MCR(mIdx), MCR_GPREN_MASK);

    /* Clear GPRE bit */
    REG_BIT_CLEAR32(EMIOS_CCR(mIdx, chIdx), CCR_UCPREN_MASK );

    /* Write prescaling rate at UCPRE[0:1] bits in EMIOSC[n] */
    REG_BIT_CLEAR32(EMIOS_CCR(mIdx, chIdx), CCR_UCPRE_SHIFT );
    regCCR |= ParamValue;
    REG_WRITE32(EMIOS_CCR(mIdx, chIdx), regCCR);

    /* Enable channel prescaler */
    REG_BIT_SET32(EMIOS_CCR(mIdx, chIdx), CCR_UCPREN_MASK);

    /* Enable global prescaler */
    if ((regMCR & MCR_GPREN_MASK) == MCR_GPREN_MASK)
    {
        REG_BIT_SET32( EMIOS_MCR(mIdx), MCR_GPREN_MASK );
    }
}
/* ICU_DUAL_CLOCK_MODE */
#endif  


#define ICU_STOP_SEC_CODE
/**
@file  eMIOS_Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
       "#include"
       See @ref eMIOS_Icu_LLD_c_1 */
/**
@file  eMIOS_Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref eMIOS_Icu_LLD_c_3
*/       
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif

