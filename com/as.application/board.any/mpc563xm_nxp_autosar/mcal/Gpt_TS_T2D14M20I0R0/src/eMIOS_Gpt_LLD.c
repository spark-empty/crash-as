/**
    @file    eMIOS_Gpt_LLD.c
    @version 2.0.0

    @brief   AUTOSAR Gpt - Brief description.
    @details Detailed description.

    Project AUTOSAR 3.0 MCAL
    Patform PA
    Peripheral eMIOS200_Stm_PitRti
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

@section eMIOS_Gpt_LLD_C_REF_1
Violates MISRA 2004 Advisory Rule 19.1, :  Violates   MISRA  2004  Advisory  Rule   19.1, only
preprocessor statements and comments before "#include". This violation is not fixed since the
inclusion  of MemMap.h  is as  per Autosar  requirement MEMMAP003.

@section eMIOS_Gpt_LLD_C_REF_2
Violates MISRA 2004 Advisory Rule 19.15 : Repeated include file. This violation is not fixed
since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003.

@section eMIOS_Gpt_LLD_C_REF_3
Violates MISRA 2004 Advisory Rule  1.2:  Both sides have side effects
There are no side effects for this construct, register address is taken from an array.

@section eMIOS_Gpt_LLD_C_REF_4
Violates MISRA 2004 Advisory Rule 11.1 : cast from unsigned long to pointer.
This violation is due to the Casting pointers to other types used in macros
for Reading or writing data from address location of controller register

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
#include "eMIOS_Gpt_LLD.h"
#include "Reg_eSys_EMIOS.h"

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/**
@brief Parameters that shall be published within the Gpt driver header file and also in the
       module's description file
@remarks Covers BSW00374, BSW00379, BSW00318
@{
*/

#define EMIOS_GPT_LLD_VENDOR_ID_C         43
#define EMIOS_GPT_LLD_AR_MAJOR_VERSION_C  3
#define EMIOS_GPT_LLD_AR_MINOR_VERSION_C  0
#define EMIOS_GPT_LLD_AR_PATCH_VERSION_C  0
#define EMIOS_GPT_LLD_SW_MAJOR_VERSION_C  2
#define EMIOS_GPT_LLD_SW_MINOR_VERSION_C  0
#define EMIOS_GPT_LLD_SW_PATCH_VERSION_C  0
/**@}*/
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/


/* Check if source file and GPT header file are of the same Software version */
#if (EMIOS_GPT_LLD_VENDOR_ID_C != EMIOS_GPT_LLD_VENDOR_ID)
    #error "eMIOS_Gpt_LLD.c and eMIOS_Gpt_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((EMIOS_GPT_LLD_AR_MAJOR_VERSION_C != EMIOS_GPT_LLD_AR_MAJOR_VERSION) || \
         (EMIOS_GPT_LLD_AR_MINOR_VERSION_C != EMIOS_GPT_LLD_AR_MINOR_VERSION) || \
         (EMIOS_GPT_LLD_AR_PATCH_VERSION_C != EMIOS_GPT_LLD_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of eMIOS_Gpt_LLD.c and eMIOS_Gpt_LLD.h are different"
    #endif
#endif
#if ((EMIOS_GPT_LLD_SW_MAJOR_VERSION_C != EMIOS_GPT_LLD_SW_MAJOR_VERSION) || \
     (EMIOS_GPT_LLD_SW_MINOR_VERSION_C != EMIOS_GPT_LLD_SW_MINOR_VERSION) || \
     (EMIOS_GPT_LLD_SW_PATCH_VERSION_C != EMIOS_GPT_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of eMIOS_Gpt_LLD.c and eMIOS_Gpt_LLD.h are different"
#endif
/* check if eMIOS_Gpt_LLD.c and Reg_eSys_EMIOS.h are of the same Software version */
#if (EMIOS_GPT_LLD_VENDOR_ID_C != REG_ESYS_EMIOS_H_VENDOR_ID)
    #error "eMIOS_Gpt_LLD.c and Reg_eSys_EMIOS.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((EMIOS_GPT_LLD_AR_MAJOR_VERSION_C != REG_ESYS_EMIOS_H_AR_MAJOR_VERSION) || \
         (EMIOS_GPT_LLD_AR_MINOR_VERSION_C != REG_ESYS_EMIOS_H_AR_MINOR_VERSION) || \
         (EMIOS_GPT_LLD_AR_PATCH_VERSION_C != REG_ESYS_EMIOS_H_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of eMIOS_Gpt_LLD.c and Reg_eSys_EMIOS.h are different"
    #endif
#endif
#if ((EMIOS_GPT_LLD_SW_MAJOR_VERSION_C != REG_ESYS_EMIOS_H_SW_MAJOR_VERSION) || \
     (EMIOS_GPT_LLD_SW_MINOR_VERSION_C != REG_ESYS_EMIOS_H_SW_MINOR_VERSION) || \
     (EMIOS_GPT_LLD_SW_PATCH_VERSION_C != REG_ESYS_EMIOS_H_SW_PATCH_VERSION))
#error "Software Version Numbers of eMIOS_Gpt_LLD.c and Reg_eSys_EMIOS.h are different"
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
#define GPT_START_SEC_VAR_UNSPECIFIED
/**
@file    eMIOS_Gpt_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref eMIOS_Gpt_LLD_C_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref eMIOS_Gpt_LLD_C_REF_2
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

#define GPT_STOP_SEC_VAR_UNSPECIFIED
/**
@file   eMIOS_Gpt_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref eMIOS_Gpt_LLD_C_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref eMIOS_Gpt_LLD_C_REF_2
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define GPT_START_SEC_CODE
/**
@file   eMIOS_Gpt_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include"- See @ref eMIOS_Gpt_LLD_C_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref eMIOS_Gpt_LLD_C_REF_2
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

/*************************************************************************************************/
/**
@brief   Gpt driver initialization function for Emios module.
@details This function is called separately for each EMIOS hw channel corresponding to the configured
         timer channels, and:
         - disables the interrupt corresponding to Emios channel
         - puts the Emios channel into GPIO mode
         - sets the prescaler value
         - enables/disables the Freeze Mode
         - clears the (pending) interrupt flag corresponding to Emios channel
         - resets the UC A register.

@param[in]     freezeEnable     indicates if the Freeze mode is enabled
@param[in]     channelPrescale  prescaler value for the corresponding Emios channel
@param[in]     hwChannel        Emios hw channel ID

@remarks Implements DGPT07208
*/
/*************************************************************************************************/

FUNC (void, GPT_CODE) Emios_LLD_InitChannel(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel,
                                            VAR(Gpt_PrescaleType, AUTOMATIC) channelPrescale,
                                            VAR(boolean, AUTOMATIC) freezeEnable)
{
/*
*/
    VAR(uint32, GPT_VAR) tempParam;
    VAR(Gpt_ChannelType, AUTOMATIC) mIdx;   /**  assigned eMIOS HW module  index */
    VAR(Gpt_ChannelType, AUTOMATIC) chIdx;  /**  assigned eMIOS HW channel index */

    mIdx  = (uint8)((uint8)hwChannel >> (uint8)5U);
    chIdx = (uint8)((uint8)hwChannel &  (uint8)0x1FU);

    /* only write UCDIS register if it's available */
    #ifdef EMIOS_UCDIS
        /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref eMIOS_Gpt_LLD_C_REF_4*/
        /* enable unified channel to make registers writable */
        REG_BIT_CLEAR32( EMIOS_UCDIS(mIdx), (uint32)((uint32)1<<(chIdx)) );
    #endif

    /* [GPT107]: By default, notifications shall be disabled after module initialization */
    /* This is applicable for the following lines of code */
    /* Timer_int_disable(hwChannel); */
    /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref eMIOS_Gpt_LLD_C_REF_4*/
    REG_BIT_CLEAR32(EMIOS_CCR(mIdx, chIdx),CCR_FEN_MASK);

    /* Stop Channel to Configure Channel */
    /* Timer_gpio_input_mode(hwChannel); */
    /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref eMIOS_Gpt_LLD_C_REF_4*/
    REG_RMW32(EMIOS_CCR(mIdx, chIdx), (CCR_MODE_MASK|CCR_EDSEL_MASK), (CCR_MODE_GPI|CCR_EDSEL_MASK));

    /* Save current emios channel param value in local variable */
    if ((boolean)TRUE == freezeEnable)
    {
        tempParam = ((channelPrescale<<CCR_UCPRE_SHIFT) | CCR_FREN_MASK | CCR_BSL_MASK);
    }
    else
    {
        tempParam = ((channelPrescale<<CCR_UCPRE_SHIFT) | CCR_BSL_MASK);
    }

    /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref eMIOS_Gpt_LLD_C_REF_4*/
    /* Initialize prescale value, channel filter, freeze enable, and bus select and disable the prescaler */
    /* Timer_init_control(hwChannel, tempParam); */
    REG_RMW32(EMIOS_CCR(mIdx, chIdx), (CCR_FREN_MASK|CCR_UCPRE_MASK|CCR_UCPREN_MASK|CCR_IF_MASK|CCR_FCK_MASK|CCR_BSL_MASK), ((tempParam)&(CCR_FREN_MASK|CCR_UCPRE_MASK|CCR_UCPREN_MASK|CCR_IF_MASK|CCR_FCK_MASK|CCR_BSL_MASK)));

    /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref eMIOS_Gpt_LLD_C_REF_4*/
    /* Clear pending interrupts */
    /* Timer_flag_clear(hwChannel); */
    REG_WRITE32(EMIOS_CSR(mIdx, chIdx), CSR_FLAG_BIT);

    /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref eMIOS_Gpt_LLD_C_REF_4*/
    /* Set Compare Value to 1 (writing 0 may lead to unpredictable result ) */
    /* Timer_set_regA(hwChannel, 1); */
    REG_WRITE32(EMIOS_CADR(mIdx, chIdx), 1);
}
#if (GPT_DEINIT_API == STD_ON)
/*************************************************************************************************/
/**
@brief   Gpt driver de-initialization function for Emios module.
@details This function is called separately for each EMIOS hw channel corresponding to the configured
         timer channels, and:
         - resets the Emios channel control register
         - resets the UC A register.
         - clears the (pending) interrupt flag corresponding to Emios channel

@param[in]     hwChannel        Emios hw channel ID

@remarks Implements DGPT07201
*/
/*************************************************************************************************/

FUNC (void, GPT_CODE) Emios_LLD_DeInit(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel)
{
    VAR(Gpt_ChannelType, AUTOMATIC) mIdx;   /**  assigned eMIOS HW module  index */
    VAR(Gpt_ChannelType, AUTOMATIC) chIdx;  /**  assigned eMIOS HW channel index */

    mIdx  = (uint8)((uint8)hwChannel >> (uint8)5U);
    chIdx = (uint8)((uint8)hwChannel &  (uint8)0x1FU);

    /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref eMIOS_Gpt_LLD_C_REF_4*/
    /* Reset Timer control register */
    /* Internal Counter is also cleared when entering GPIO Mode */
    /* This is applicable for the following lines of code */
    /* Timer_reset(hwChannel); */
    REG_WRITE32(EMIOS_CCR(mIdx, chIdx), 0x0UL);

    /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref eMIOS_Gpt_LLD_C_REF_4*/
    /* Set Compare Value to 1 (writing 0 may lead to unpredictable result ) */
    /* Timer_set_regA(hwChannel, 1); */
    REG_WRITE32(EMIOS_CADR(mIdx, chIdx), 1);

    /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref eMIOS_Gpt_LLD_C_REF_4*/
    /* Clear Interrupt Flag */
    /* Timer_flag_clear(hwChannel); */
    REG_WRITE32(EMIOS_CSR(mIdx, chIdx), CSR_FLAG_BIT);

    /* only write UCDIS register if it's available */
    #ifdef EMIOS_UCDIS
        /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref eMIOS_Gpt_LLD_C_REF_4*/
        /* disable unified channel */
        REG_BIT_SET32( EMIOS_UCDIS(mIdx), (uint32)((uint32)1<<(chIdx)) );
    #endif
}
#endif

/*************************************************************************************************/
/**
@brief   Gpt driver function for starting the Emios timer channel.
@details This function:
         - puts the Emios channel into GPIO mode
         - enables the channel prescaler
         - programs the UC A register with the value passed as input parameter
         - sets the Emios channel mode to Modulus Counter Buffered (Up counter)
         - enables the IRQ for the Emios channel, if channel configured in One Shot mode.

@param[in]     hwChannel        Emios hw channel ID
@param[in]     value            channel timeout value
@param[in]     channelMode      channel mode: Continous or One Shot

@remarks Implements DGPT07211
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Emios_LLD_StartTimer(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel,
                                         VAR(Gpt_ValueType, AUTOMATIC) value,
                                         VAR(Gpt_ChannelModeType, AUTOMATIC) channelMode)
{
    VAR(Gpt_ChannelType, AUTOMATIC) mIdx;   /** assigned eMIOS HW module  index */
    VAR(Gpt_ChannelType, AUTOMATIC) chIdx;  /**  assigned eMIOS HW channel index */

    mIdx  = (uint8)((uint8)hwChannel >> (uint8)5U);
    chIdx = (uint8)((uint8)hwChannel &  (uint8)0x1FU);

    /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref eMIOS_Gpt_LLD_C_REF_4*/
    /* Timer_gpio_input_mode(hwChannel); */
    REG_RMW32(EMIOS_CCR(mIdx, chIdx), (CCR_MODE_MASK|CCR_EDSEL_MASK), (CCR_MODE_GPI|CCR_EDSEL_MASK));

    /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref eMIOS_Gpt_LLD_C_REF_4*/
    /* Timer_channel_pres_enable(hwChannel); */
    REG_BIT_SET32(EMIOS_CCR(mIdx, chIdx), CCR_UCPREN_MASK);

    /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref eMIOS_Gpt_LLD_C_REF_4*/
    /* Note that the internal counter is set to 0x1 when its value matches A1 value and a clock
       tick occurs */
    /* Timer_set_regA(hwChannel, value); */
    REG_WRITE32(EMIOS_CADR(mIdx, chIdx), value);
    /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref eMIOS_Gpt_LLD_C_REF_4*/
    /* Timer_mcb_mode(hwChannel); */
    REG_RMW32(EMIOS_CCR(mIdx, chIdx), CCR_MODE_MASK, CCR_MODE_MCB_INT_CLOCK);

    /* For one-shot channels, interrupts are required to shut down the channel */
    /* This is a workaround for the lack of one-shot mode in the hardware */
    /* Notifications must still be turned on using Gpt_EnableNotification */
    if (GPT_MODE_ONESHOT == channelMode)
    {
        /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref eMIOS_Gpt_LLD_C_REF_4*/
        /* Note - another option is to add here a check for GPT_GET_NOTIFICATION(hwChannel) and call
        access the register only if there is no notification set for the channel */
        /* Timer_int_enable(hwChannel); */
        REG_BIT_SET32(EMIOS_CCR(mIdx, chIdx), CCR_FEN_MASK);
    }
}

/*************************************************************************************************/
/**
@brief   Gpt driver function for stopping the Emios timer channel.
@details This function puts the Emios channel into GPIO mode

@param[in]     hwChannel        Emios hw channel ID

@remarks Implements DGPT07212
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Emios_LLD_StopTimer(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel)
{
    VAR(Gpt_ChannelType, AUTOMATIC) mIdx;   /*  assigned eMIOS HW module  index */
    VAR(Gpt_ChannelType, AUTOMATIC) chIdx;  /*  assigned eMIOS HW channel index */

    mIdx  = (uint8)((uint8)hwChannel >> (uint8)5U);
    chIdx = (uint8)((uint8)hwChannel &  (uint8)0x1FU);
    /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref eMIOS_Gpt_LLD_C_REF_4*/
    /* Timer_gpio_input_mode(hwChannel); */
    REG_RMW32(EMIOS_CCR(mIdx, chIdx), (CCR_MODE_MASK|CCR_EDSEL_MASK), (CCR_MODE_GPI|CCR_EDSEL_MASK));
}
#if (GPT_TIME_ELAPSED_API == STD_ON)
/*************************************************************************************************/
/**
@brief   Gpt driver function for getting the time elapsed for an Emios timer channel.
@details This function is called for reading the Emios channel counter register.

@param[in]     hwChannel        Emios hw channel ID
@param[out]    returnValuePtr   elapsed time value

@remarks Implements DGPT07206
*/
/*************************************************************************************************/

FUNC (void, GPT_CODE) Emios_LLD_GetTimeElapsed(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel,
                                             P2VAR(Gpt_ValueType, AUTOMATIC, GPT_APPL_DATA) returnValuePtr)
{
    VAR(Gpt_ChannelType, AUTOMATIC) mIdx;   /**  assigned eMIOS HW module  index */
    VAR(Gpt_ChannelType, AUTOMATIC) chIdx;  /**  assigned eMIOS HW channel index */

    mIdx  = (uint8)((uint8)hwChannel >> (uint8)5U);
    chIdx = (uint8)((uint8)hwChannel &  (uint8)0x1FU);
/*
*/

/*    if (Timer_read_mode(hwChannel) == MTSC_MODE_MCB) */
    if (CCR_MODE_MCB_INT_CLOCK == (REG_READ32(EMIOS_CCR(mIdx, chIdx)) & CCR_MODE_MASK))
    {
/*
*/
        /* *returnValuePtr = Timer_read_counter(hwChannel); */
        *returnValuePtr = REG_READ32(EMIOS_CCNTR(mIdx, chIdx));
    }
    else
    {
        /* the execution can arrive on this branch only someone else (other than GPT driver) writes
           the channel mode bits for this channel */
        *returnValuePtr = (Gpt_ValueType)0;
    }
}
#endif
#if (GPT_TIME_REMAINING_API == STD_ON)
/*************************************************************************************************/
/**
@brief   Gpt driver function for getting the time remaining for an Emios timer channel.
@details This function is called for reading the Emios channel counter register(s) to return the remaining time.

@param[in]     hwChannel        Emios hw channel ID
@param[out]    returnValuePtr   remaining time value

@remarks Implements DGPT07207
*/
/*************************************************************************************************/

FUNC (void, GPT_CODE) Emios_LLD_GetTimeRemaining(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel,
                                               P2VAR(Gpt_ValueType, AUTOMATIC, GPT_APPL_DATA) returnValuePtr)
{
    VAR(Gpt_ChannelType, AUTOMATIC) mIdx;   /**  assigned eMIOS HW module  index */
    VAR(Gpt_ChannelType, AUTOMATIC) chIdx;  /**  assigned eMIOS HW channel index */

    mIdx  = (uint8)((uint8)hwChannel >> (uint8)5U);
    chIdx = (uint8)((uint8)hwChannel &  (uint8)0x1FU);
/*
*/
/*  if (Timer_read_mode(hwChannel) == MTSC_MODE_MCB) */
    if (CCR_MODE_MCB_INT_CLOCK == (REG_READ32(EMIOS_CCR(mIdx, chIdx)) & CCR_MODE_MASK))
    {
        /* *returnValuePtr = Timer_read_regA(hwChannel) - Timer_read_counter(hwChannel); */
        /**

        @note  Violates MISRA 2004 Advisory Rule 1.2, Both Sides have side effects - See @ref eMIOS_Gpt_LLD_C_REF_3
        */
        /*lint -save -e961*/
        *returnValuePtr = REG_READ32(EMIOS_CADR(mIdx, chIdx)) - REG_READ32(EMIOS_CCNTR(mIdx, chIdx));
        /*lint -restore */
    }
/*
*/
    else
    {
        /* the execution can arrive on this branch only someone else (other than GPT driver) writes
           the channel mode bits for this channel */
        *returnValuePtr = (Gpt_ValueType)0;
    }
}
#endif
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/*************************************************************************************************/
/**
@brief   Gpt driver function for putting the Emios timer channel in SLEEP mode.
@details This function is called separately for each EMIOS hw channel corresponding to the configured
         timer channels, and:
         - clears the (pending) interrupt flag corresponding to Emios channel
         - puts the Emios channel into GPIO mode, if the wake up functionality is disabled
         - enables the IRQ for the Emios channel, if the wake up functionality is enabled

@param[in]     hwChannel        Emios hw channel ID
@param[in]     wakeUpEnabled    Indicates whether wake up functionality is enabled or not for the
                                corresponding channel.

@remarks Implements DGPT07210
*/
/*************************************************************************************************/

FUNC (void, GPT_CODE) Emios_LLD_SetSleepMode(VAR(uint8, AUTOMATIC) hwChannel, boolean wakeUpEnabled)
{
    VAR(Gpt_ChannelType, AUTOMATIC) mIdx;   /**  assigned eMIOS HW module  index */
    VAR(Gpt_ChannelType, AUTOMATIC) chIdx;  /**  assigned eMIOS HW channel index */

    mIdx  = (uint8)((uint8)hwChannel >> (uint8)5U);
    chIdx = (uint8)((uint8)hwChannel &  (uint8)0x1FU);

    /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref eMIOS_Gpt_LLD_C_REF_4*/
    /* Timer_flag_clear(hwChannel); */
    REG_WRITE32(EMIOS_CSR(mIdx, chIdx), CSR_FLAG_MASK);

    /* Check if wake-up is NOT enabled */
    if ((boolean)FALSE == wakeUpEnabled)
    {
        /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref eMIOS_Gpt_LLD_C_REF_4*/
        /* Timer_gpio_input_mode(hwChannel); */
        REG_RMW32(EMIOS_CCR(mIdx, chIdx), (CCR_MODE_MASK|CCR_EDSEL_MASK), (CCR_MODE_GPI|CCR_EDSEL_MASK));
    }
    else
    {
        /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref eMIOS_Gpt_LLD_C_REF_4*/
        /* Timer_int_enable(hwChannel); */
        REG_BIT_SET32(EMIOS_CCR(mIdx, chIdx), CCR_FEN_MASK);
    }
}
#endif
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
/*************************************************************************************************/
/**
@brief   Gpt driver function for enabling the Emios timer channel notifification/IRQ.
@details This function:
         - clears the (pending) interrupt flag corresponding to Emios channel
         - enables the IRQ corresponding to the Emios channel

@param[in]     hwChannel        Emios hw channel ID

@remarks Implements DGPT07204
*/
/*************************************************************************************************/

FUNC (void, GPT_CODE) Emios_LLD_EnableNotification(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel)
{
    VAR(Gpt_ChannelType, AUTOMATIC) mIdx;   /**  assigned eMIOS HW module  index */
    VAR(Gpt_ChannelType, AUTOMATIC) chIdx;  /**  assigned eMIOS HW channel index */

    mIdx  = (uint8)((uint8)hwChannel >> (uint8)5U);
    chIdx = (uint8)((uint8)hwChannel &  (uint8)0x1FU);
    /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref eMIOS_Gpt_LLD_C_REF_4*/
    /* Enable Timer Interrupt if it's not already enabled */
    /* Timer_flag_clear(hwChannel); */
    REG_WRITE32(EMIOS_CSR(mIdx, chIdx), CSR_FLAG_MASK);
    /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref eMIOS_Gpt_LLD_C_REF_4*/
    /* Timer_int_enable(hwChannel); */
    REG_BIT_SET32(EMIOS_CCR(mIdx, chIdx), CCR_FEN_MASK);
}
#endif
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
/*************************************************************************************************/
/**
@brief   Gpt driver function for disabling the Emios timer channel notifification/IRQ.
@details This function disables the IRQ corresponding to the Emios channel

@param[in]     hwChannel        Emios hw channel ID

@remarks Implements DGPT07202
*/
/*************************************************************************************************/

FUNC (void, GPT_CODE) Emios_LLD_DisableNotification(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel)
{
    VAR(Gpt_ChannelType, AUTOMATIC) mIdx;   /**  assigned eMIOS HW module  index */
    VAR(Gpt_ChannelType, AUTOMATIC) chIdx;  /**  assigned eMIOS HW channel index */

    mIdx  = (uint8)((uint8)hwChannel >> (uint8)5U);
    chIdx = (uint8)((uint8)hwChannel &  (uint8)0x1FU);
    /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref eMIOS_Gpt_LLD_C_REF_4*/
    /* Timer_int_disable(hwChannel); */
    REG_BIT_CLEAR32(EMIOS_CCR(mIdx, chIdx), CCR_FEN_MASK);
}
#endif

#if (GPT_DUAL_CLOCK_MODE == STD_ON)
/*************************************************************************************************/
/**
@brief      The function changes the EMIOS channel prescaler value.
@details    This function sets the EMIOS channel prescaler based on the input mode.

@param[in]  chPrescale     prescaler value for the corresponding Emios channel
@param[in]  hwChannel      Emios hw channel ID

@remarks    Covers PR-MCAL-3196
@remarks Implements DGPT11027
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Emios_LLD_SelectPrescaler(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel,
                                                VAR(Gpt_PrescaleType, AUTOMATIC) chPrescale)
{
    VAR(uint32, GPT_VAR) tempParam;
    VAR(Gpt_ChannelType, AUTOMATIC) mIdx;   /**  assigned eMIOS HW module  index */
    VAR(Gpt_ChannelType, AUTOMATIC) chIdx;  /**  assigned eMIOS HW channel index */

    mIdx  = (uint8)((uint8)hwChannel >> (uint8)5U);
    chIdx = (uint8)((uint8)hwChannel &  (uint8)0x1FU);

    /* Save current emios channel param value in local variable */
    tempParam = REG_READ32(EMIOS_CCR(mIdx, chIdx));
    tempParam &= ~((uint32)CCR_UCPRE_MASK);
    tempParam |= ((((uint32)chPrescale)<<CCR_UCPRE_SHIFT) & (uint32)CCR_UCPRE_MASK);

    /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref eMIOS_Gpt_LLD_C_REF_4*/
    REG_WRITE32(EMIOS_CCR(mIdx, chIdx), tempParam);
}
/* GPT_DUAL_CLOCK_MODE == STD_ON */
#endif 
/*********************************************************************/

#define GPT_STOP_SEC_CODE
/**
@file   eMIOS_Gpt_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref eMIOS_Gpt_LLD_C_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref eMIOS_Gpt_LLD_C_REF_2
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/
#ifdef __cplusplus
}
#endif
