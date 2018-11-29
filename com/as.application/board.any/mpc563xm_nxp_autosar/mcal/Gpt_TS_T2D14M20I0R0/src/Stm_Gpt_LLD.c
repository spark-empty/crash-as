/**
    @file    Stm_Gpt_LLD.c
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

@section STM_GPT_LLD_C_REF_1
Violates MISRA 2004 Advisory Rule 19.1, :  Violates   MISRA  2004  Advisory  Rule   19.1,  only preprocessor
statements and comments before "#include"
This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement
MEMMAP003.

@section STM_GPT_LLD_C_REF_2
Violates MISRA 2004 Advisory Rule 19.15 : Repeated include file
This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement
MEMMAP003.

@section STM_GPT_LLD_C_REF_3
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
#include "Stm_Gpt_LLD.h"
#include "Reg_eSys_STM.h"

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/**
@brief Parameters that shall be published within the Gpt driver header file and also in the
       module's description file
@remarks Covers BSW00374, BSW00379, BSW00318
@{
*/

#define STM_GPT_LLD_VENDOR_ID_C         43
#define STM_GPT_LLD_AR_MAJOR_VERSION_C  3
#define STM_GPT_LLD_AR_MINOR_VERSION_C  0
#define STM_GPT_LLD_AR_PATCH_VERSION_C  0
#define STM_GPT_LLD_SW_MAJOR_VERSION_C  2
#define STM_GPT_LLD_SW_MINOR_VERSION_C  0
#define STM_GPT_LLD_SW_PATCH_VERSION_C  0
/**@}*/
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#if (STM_GPT_LLD_VENDOR_ID_C != STM_GPT_LLD_VENDOR_ID)
#error "Stm_Gpt_LLD.c and Stm_Gpt_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if header file and Gpt header file are of the same Autosar version */
    #if ((STM_GPT_LLD_AR_MAJOR_VERSION_C != STM_GPT_LLD_AR_MAJOR_VERSION) || \
         (STM_GPT_LLD_AR_MINOR_VERSION_C != STM_GPT_LLD_AR_MINOR_VERSION) || \
         (STM_GPT_LLD_AR_PATCH_VERSION_C != STM_GPT_LLD_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Stm_Gpt_LLD.c and Stm_Gpt_LLD.h are different"
    #endif
#endif
/* Check if source file and GPT header file are of the same Software version */
#if ((STM_GPT_LLD_SW_MAJOR_VERSION_C != STM_GPT_LLD_SW_MAJOR_VERSION) || \
     (STM_GPT_LLD_SW_MINOR_VERSION_C != STM_GPT_LLD_SW_MINOR_VERSION) || \
     (STM_GPT_LLD_SW_PATCH_VERSION_C != STM_GPT_LLD_SW_PATCH_VERSION) )
    #error "Software Version Numbers of Stm_Gpt_LLD.c and Stm_Gpt_LLD.h are different"
#endif


#if (STM_GPT_LLD_VENDOR_ID_C != REG_ESYS_STM_VENDOR_ID)
#error "Stm_Gpt_LLD.c and Reg_eSys_STM.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if header file and Gpt header file are of the same Autosar version */
    #if ((STM_GPT_LLD_AR_MAJOR_VERSION_C != REG_ESYS_STM_AR_MAJOR_VERSION) || \
         (STM_GPT_LLD_AR_MINOR_VERSION_C != REG_ESYS_STM_AR_MINOR_VERSION) || \
         (STM_GPT_LLD_AR_PATCH_VERSION_C != REG_ESYS_STM_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Stm_Gpt_LLD.c and Reg_eSys_STM.h are different"
    #endif
#endif
/* Check if source file and GPT header file are of the same Software version */
#if ((STM_GPT_LLD_SW_MAJOR_VERSION_C != REG_ESYS_STM_SW_MAJOR_VERSION) || \
     (STM_GPT_LLD_SW_MINOR_VERSION_C != REG_ESYS_STM_SW_MINOR_VERSION) || \
     (STM_GPT_LLD_SW_PATCH_VERSION_C != REG_ESYS_STM_SW_PATCH_VERSION) )
    #error "Software Version Numbers of Stm_Gpt_LLD.c and Reg_eSys_STM.h are different"
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

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define GPT_START_SEC_CODE
/**
@file   Stm_Gpt_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref STM_GPT_LLD_C_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref STM_GPT_LLD_C_REF_2
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

/*************************************************************************************************/
/**
@brief   Gpt driver initialization function for Stm module.
@details This function is called separately for each STM hw channel corresponding to the configured
         timer channels, and:
         - sets the prescaler value
         - configures the freeze mode (enabled/disabled)
         - enables the STM counter
         - disables the STM channel
         - clears the (pending) interrupt flag corresponding to Stm channel
         - clears the compare register correponding to the Stm channel.

@param[in]     freezeEnable     indicates if the Freeze mode is enabled
@param[in]     channelPrescale  prescaler value for the corresponding Stm channel
@param[in]     hwChannel        Stm hw channel ID

@remarks Implements DGPT08205
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Stm_LLD_InitChannel(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel,
                                          VAR(Gpt_PrescaleType, AUTOMATIC) channelPrescale,
                                          VAR(boolean, AUTOMATIC) freezeEnable)
{
   /*
     Set Global prescaler
   */
       /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref STM_GPT_LLD_C_REF_3*/
    STM_SET_PRESCALER(channelPrescale);
    if ((boolean)TRUE == freezeEnable)
    {
     /** @note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref STM_GPT_LLD_C_REF_3*/
        STM_SET_FRZ();
    }
    else
    {
     /** @note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref STM_GPT_LLD_C_REF_3*/
        STM_CLR_FRZ();
    }

   /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref STM_GPT_LLD_C_REF_3*/
   /* This is applicable for the following lines of code */
    /* Timer Counter is enabled */
    STM_TIMER_COUNTER_ENABLE();

    /* STM channel disabled */
     /** @note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref STM_GPT_LLD_C_REF_3*/
    STM_CH_DISABLE(hwChannel);

    /* Clear interrupt request */
     /** @note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref STM_GPT_LLD_C_REF_3*/
    STM_CH_CLEAR_ISR_REQ(hwChannel);

    /* Set Compare Value to 0 */
     /** @note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref STM_GPT_LLD_C_REF_3*/
    STM_SET_COMPARE(hwChannel, 0U);
    
}
#if (GPT_DEINIT_API == STD_ON)
/*************************************************************************************************/
/**
@brief   Gpt driver de-initialization function for Stm module.
@details This function is called separately for each STM hw channel corresponding to the configured
         timer channels, and:
         - disables the STM counter
         - resets the prescaler bits in the control register
         - disables the STM channel
         - clears the (pending) interrupt flag corresponding to Stm channel
         - clears the compare register correponding to the Stm channel.

@param[in]     hwChannel        Stm hw channel ID

@remarks Implements DGPT08200
*/
/*************************************************************************************************/

FUNC (void, GPT_CODE) Stm_LLD_DeInit(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel)
{
   /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref STM_GPT_LLD_C_REF_3*/
   /* This is applicable for the following lines of code */
    /* Timer Counter is disabled */
    STM_TIMER_COUNTER_DISABLE();

    /* Reset Prescaler */
     /** @note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref STM_GPT_LLD_C_REF_3*/
    STM_SET_PRESCALER(0U);

    /* disable channel configured */
     /** @note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref STM_GPT_LLD_C_REF_3*/
    STM_CH_DISABLE(hwChannel);

    /* Set Compare Value to 0 */
     /** @note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref STM_GPT_LLD_C_REF_3*/
    STM_SET_COMPARE(hwChannel, 0UL);

    /* Clear Interrupt Flag */
     /** @note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref STM_GPT_LLD_C_REF_3*/
    STM_CH_CLEAR_ISR_REQ(hwChannel);
}
#endif

/*************************************************************************************************/
/**
@brief   Gpt driver function for starting the Stm timer channel.
@details This function:
         - reads the current counter register value and sets the compare register to the sum of
           counter register value plus the timeout value
         - enables the STM channel

@param[in]     hwChannel        Stm hw channel ID
@param[in]     value            channel timeout value

@remarks Implements DGPT08208
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Stm_LLD_StartTimer(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel,
                                         VAR(Gpt_ValueType, AUTOMATIC) value)
{
    VAR(uint32, AUTOMATIC) counterValue;

    /* Configure channel compare register */
   /** @note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref STM_GPT_LLD_C_REF_3*/
    counterValue = STM_GET_COUNTER();

   /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref STM_GPT_LLD_C_REF_3*/
    STM_SET_COMPARE(hwChannel, ((uint32)(counterValue + value)));

   /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref STM_GPT_LLD_C_REF_3*/
    /* Enable hardware channel */
    STM_CH_ENABLE(hwChannel);

    /* for STM, there is no need to enable the corresponding timer channel IRQ, as there is no HW
       support for enabling/disabling the STM IRQ */
}

/*************************************************************************************************/
/**
@brief   Gpt driver function for stopping the Stm timer channel.
@details This function:
         - disables the STM channel
         - clears the (pending) interrupt flag corresponding to Stm channel

@param[in]     hwChannel        Stm hw channel ID

@remarks Implements DGPT08209
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Stm_LLD_StopTimer(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel)
{
   /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref STM_GPT_LLD_C_REF_3*/
    /* Disable hardware channel */
    STM_CH_DISABLE(hwChannel);

   /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref STM_GPT_LLD_C_REF_3*/
    /* Clear interrupt flag */
    STM_CH_CLEAR_ISR_REQ(hwChannel);
}
#if ((GPT_TIME_ELAPSED_API == STD_ON) || (GPT_TIME_REMAINING_API == STD_ON))
/*************************************************************************************************/
/**
@brief   Gpt driver function for getting the time elapsed for an Stm timer channel.
@details This function:
         - reads the STM channel compare register
         - reads the STM counter register
         - depending on above and on channel timeout value it calculates and returns the elapsed
           time

@param[in]     hwChannel        Stm hw channel ID
@param[in]     timeOutValue     channel timeout value
@param[out]    returnValuePtr   elapsed time value

@remarks Implements DGPT08203
*/
/*************************************************************************************************/

FUNC (void, GPT_CODE) Stm_LLD_GetTimeElapsed(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel,
                                             VAR(Gpt_ValueType, AUTOMATIC) timeOutValue,
                                             P2VAR(Gpt_ValueType, AUTOMATIC, GPT_APPL_DATA) returnValuePtr)
{
    VAR(uint32, AUTOMATIC) compareValue;
    VAR(uint32, AUTOMATIC) conterValue;
    VAR(uint32, AUTOMATIC) timeElapsedValue = (uint32)0;

    /* Read compare and counter registers */
   /** @note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref STM_GPT_LLD_C_REF_3*/
    compareValue = STM_GET_COMPARE(hwChannel);
   /** @note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref STM_GPT_LLD_C_REF_3*/
    conterValue = STM_GET_COUNTER();

    /*
    notes on how is the time elapsed value calculated - there are two cases: the channel is in the
    ONE SHOT mode or in CONTINOUS mode. For each of these modes, there can be considered 2 cases:
    1. 0 <= startTime < compareValue < GPT_STM_MAX_VALUE + STM_OVERFLOW_PAD
    2. 0 <= compareValue < startTime < GPT_STM_MAX_VALUE + STM_OVERFLOW_PAD

    startTime is the STM counter value when Gpt_StartTimer had been invoked.
    compareValue = startTime + timeOutValue for case 1.
    compareValue = startTime + timeOutValue - (GPT_STM_MAX_VALUE + STM_OVERFLOW_PAD) for case 2.

    For both cases and for each channel mode, timeElapsedValue calculations reveal the formulas
    below.

    Note that in CONTINOUS mode, the calculations are correct only if the channel notification is
    enabled. Otherwise, there is no mechanism for getting the elapsed time (except for polling,
    which is not efficient)
    */
    if (conterValue >= compareValue)
    {
        timeElapsedValue = (timeOutValue - ((STM_CNT_MAX_VALUE - conterValue) + compareValue)) +
                    STM_OVERFLOW_PAD;
    }
    else
    {
        timeElapsedValue = timeOutValue - (compareValue - conterValue);
    }

    /* Calculate the elapsed time */
    *returnValuePtr = timeElapsedValue;
}
#endif
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/*************************************************************************************************/
/**
@brief   Gpt driver function for putting the Stm timer channel in SLEEP mode.
@details This function is called separately for each STM hw channel corresponding to the configured
         timer channels, and:
         - clears the (pending) interrupt flag corresponding to Stm channel
         - disable the Stm channel

@param[in]     hwChannel        Stm hw channel ID
@param[in]     wakeUpEnabled    Indicates whether wake up functionality is enabled or not for the
                                corresponding channel.
@param[in]     enableStmCounter  Enable or disable the Stm counter

@remarks Implements DGPT08207
*/
/*************************************************************************************************/

FUNC (void, GPT_CODE) Stm_LLD_SetSleepMode(VAR(uint8, AUTOMATIC) hwChannel,
                                           VAR(boolean, AUTOMATIC) wakeUpEnabled,
                                           VAR(boolean, AUTOMATIC) enableStmCounter
                                          )
{
    if ((boolean)FALSE == enableStmCounter)
    {
        /* Disable Timer Counter */
       /** @note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref STM_GPT_LLD_C_REF_3*/
        STM_TIMER_COUNTER_DISABLE();
    }
    else
    {
        /* Enable Timer Counter */
       /** @note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref STM_GPT_LLD_C_REF_3*/
        STM_TIMER_COUNTER_ENABLE();
    }

    /* Check if wake-up is NOT enabled */
    if ((boolean)FALSE == wakeUpEnabled)
    {
        /* Clear interrupt request */
       /** @note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref STM_GPT_LLD_C_REF_3*/
        STM_CH_CLEAR_ISR_REQ(hwChannel);

        /* disable all channel configured */
       /** @note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref STM_GPT_LLD_C_REF_3*/
        STM_CH_DISABLE(hwChannel);
    }
}
#endif
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/*************************************************************************************************/
/**
@brief   Gpt driver function for putting the Stm timer channel in NORMAL mode.
@details This function enables the Stm counter


@remarks Implements DGPT08206
*/
/*************************************************************************************************/

FUNC (void, GPT_CODE) Stm_LLD_SetNormalMode()
{
   /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref STM_GPT_LLD_C_REF_3*/
    /* Timer Counter is re-enabled */
    STM_TIMER_COUNTER_ENABLE();
}
#endif
 
 /*lint -save -e961 */
#if (GPT_DUAL_CLOCK_MODE == STD_ON)
/*lint -restore */
/*************************************************************************************************/
/**
@brief      The function changes the STM prescaler value.
@details    This function sets the STM prescaler based on the input mode.

@param[in]  chPrescale     prescaler value

@remarks    Covers PR-MCAL-3196
@remarks Implements DGPT11025
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) Stm_LLD_SelectPrescaler(VAR(Gpt_PrescaleType, AUTOMATIC) chPrescale)
{

   /**@note  Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer - See @ref STM_GPT_LLD_C_REF_3*/
    STM_SET_PRESCALER(chPrescale);
}
#endif
#define GPT_STOP_SEC_CODE
/**
@file   Stm_Gpt_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref STM_GPT_LLD_C_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref STM_GPT_LLD_C_REF_2
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif
