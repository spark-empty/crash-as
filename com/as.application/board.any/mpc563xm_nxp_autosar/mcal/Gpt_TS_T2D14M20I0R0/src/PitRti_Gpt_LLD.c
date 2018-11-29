/**
    @file    PitRti_Gpt_LLD.c
    @version 2.0.0

    @brief   AUTOSAR Gpt - Brief description.
    @details Detailed description.

    Project AUTOSAR 3.0 MCAL
    Platform PA
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

@section PitRti_Gpt_LLD_C_REF_1
Violates MISRA 2004 Advisory Rule 19.1:  only preprocessor statements and comments before "#include". 
This violation is not fixed since the inclusion  of MemMap.h  is as  per Autosar  requirement MEMMAP003.

@section PitRti_Gpt_LLD_C_REF_2
Violates MISRA 2004 Advisory Rule 19.15 : Repeated include file. This violation is not fixed
since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003.

 @section PitRti_Gpt_LLD_C_REF_3
Violates MISRA 2004 Advisory Rule 11.1 : cast from unsigned long to pointer.
This violation is due to the Casting pointers to other types used in macros
for Reading or writing data from address location of controller register 

@section PitRti_Gpt_LLD_C_REF_4
 Violates MISRA 2004 Rule 1.4: Identifier clash.
This violation is due to the usage of identical MACRO name upto 32 chanracter which is as per BSW naming convention which cannot 
be fixed.
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
#include "PitRti_Gpt_LLD.h"
#include "Reg_eSys_PITRTI.h"
#include "Dem_IntErrId.h"
#include "Dem_Types.h"
#include "Dem.h"
/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/**
@brief Parameters that shall be published within the Gpt driver header file and also in the
       module's description file
@remarks Covers BSW00374, BSW00379, BSW00318
@{
*/
#define PITRTI_GPT_LLD_VENDOR_ID_C         43
/**@note  Violates MISRA 2004 Rule 1.4: Identifier clash. - See PitRti_Gpt_LLD_C_REF_4 */
/*lint -save -e621 */
#define PITRTI_GPT_LLD_AR_MAJOR_VERSION_C  3
#define PITRTI_GPT_LLD_AR_MINOR_VERSION_C  0
#define PITRTI_GPT_LLD_AR_PATCH_VERSION_C  0
#define PITRTI_GPT_LLD_SW_MAJOR_VERSION_C  2
#define PITRTI_GPT_LLD_SW_MINOR_VERSION_C  0
#define PITRTI_GPT_LLD_SW_PATCH_VERSION_C  0
/*lint -restore */

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#if ( PITRTI_GPT_LLD_VENDOR_ID_C!= PITRTI_GPT_LLD_VENDOR_ID)
#error "PitRti_Gpt_LLD.c and PitRti_Gpt_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if header file and Gpt header file are of the same Autosar version */
    #if ((PITRTI_GPT_LLD_AR_MAJOR_VERSION_C != PITRTI_GPT_LLD_AR_MAJOR_VERSION) || \
         (PITRTI_GPT_LLD_AR_MINOR_VERSION_C != PITRTI_GPT_LLD_AR_MINOR_VERSION) || \
         (PITRTI_GPT_LLD_AR_PATCH_VERSION_C != PITRTI_GPT_LLD_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of PitRti_Gpt_LLD.c and PitRti_Gpt_LLD.h are different"
    #endif
#endif
/* Check if source file and GPT header file are of the same Software version */
#if ((PITRTI_GPT_LLD_SW_MAJOR_VERSION_C != PITRTI_GPT_LLD_SW_MAJOR_VERSION) || \
     (PITRTI_GPT_LLD_SW_MINOR_VERSION_C != PITRTI_GPT_LLD_SW_MINOR_VERSION) || \
     (PITRTI_GPT_LLD_SW_PATCH_VERSION_C != PITRTI_GPT_LLD_SW_PATCH_VERSION) )
    #error "Software Version Numbers of PitRti_Gpt_LLD.c and PitRti_Gpt_LLD.h are different"
#endif

#if ( PITRTI_GPT_LLD_VENDOR_ID_C!= REG_ESYS_PITRTI_VENDOR_ID)
#error "PitRti_Gpt_LLD.c and Reg_eSys_PITRTI.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if header file and Gpt header file are of the same Autosar version */
    #if ((PITRTI_GPT_LLD_AR_MAJOR_VERSION_C != REG_ESYS_PITRTI_AR_MAJOR_VERSION) || \
         (PITRTI_GPT_LLD_AR_MINOR_VERSION_C != REG_ESYS_PITRTI_AR_MINOR_VERSION) || \
         (PITRTI_GPT_LLD_AR_PATCH_VERSION_C != REG_ESYS_PITRTI_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of PitRti_Gpt_LLD.c and Reg_eSys_PITRTI.h are different"
    #endif
#endif
/* Check if source file and GPT header file are of the same Software version */
#if ((PITRTI_GPT_LLD_SW_MAJOR_VERSION_C != REG_ESYS_PITRTI_SW_MAJOR_VERSION) || \
     (PITRTI_GPT_LLD_SW_MINOR_VERSION_C != REG_ESYS_PITRTI_SW_MINOR_VERSION) || \
     (PITRTI_GPT_LLD_SW_PATCH_VERSION_C != REG_ESYS_PITRTI_SW_PATCH_VERSION) )
    #error "Software Version Numbers of PitRti_Gpt_LLD.c and Reg_eSys_PITRTI.h are different"
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
@file   Pitrti_Gpt_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref PITRTI_GPT_LLD_C_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref PITRTI_GPT_LLD_C_REF_2
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

/*************************************************************************************************/
/**
@brief   Gpt driver initialization function for PitRti module.
@details This function is called separately for each PITRTI hw channel corresponding to the configured
         timer channels, and:
         - enables the PITRTI module
         - configures the freeze mode (enabled/disabled)
         - disables the IRQ correpsonding to the PITRTI channel
         - clears the (pending) interrupt flag corresponding to PitRti channel
         - disables the PITRTI timer channel
         - clears the Load Value register correponding to the PitRti channel.

@param[in]     freezeEnable     indicates if the Freeze mode is enabled
@param[in]     hwChannel        PitRti hw channel ID

@remarks Implements DGPT09205
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) PitRti_LLD_InitChannel(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel,
                                          VAR(boolean, AUTOMATIC) freezeEnable)
{
    /*
    */

/**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer - See PitRti_Gpt_LLD_C_REF_3 */
    PITRTI_ENABLE_MODULE();

 
    if ((boolean)TRUE == freezeEnable)
    {
        /*
        */
/**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer - See PitRti_Gpt_LLD_C_REF_3 */
        PITRTI_FREEZE_ENABLE();

    }

    /* [GPT107]: By default, notifications shall be disabled after module initialization */
    if ((Gpt_ChannelType)PITRTI_RTC_CH_0 == hwChannel)
    {
/**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer - See PitRti_Gpt_LLD_C_REF_3 */
   /* This is applicable for the following lines of code */
        PITRTI_RTC_INT_DISABLE();

        /* Clear pending interrupts */
        PITRTI_RTC_CLEAR_INTERRUPT();

        /* Stop Channel to Configure Channel */
        PITRTI_RTC_COUNTER_DISABLE();

        /* Set Compare Value to 0 */
        PITRTI_RTC_SET_VALUE(0);

        /* Start Channel to Configure Channel */
        PITRTI_ENABLE_RTI_CLOCK();
    /* MISRA-C:2004 11.1 VIOLATION: End of code block */
    }
    else
    {
/**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer - See PitRti_Gpt_LLD_C_REF_3 */
   /* This is applicable for the following lines of code */
        PITRTI_INTERRUPT_DISABLE(hwChannel);
        /* Clear pending interrupts */
        PITRTI_CLEAR_INT_FLAG(hwChannel);
        /* Stop Channel to Configure Channel */
        PITRTI_TIMER_DISABLE(hwChannel);
        /* Set Compare Value to 0 */
        PITRTI_SETLOADVALUE(hwChannel, 0);
    /* MISRA-C:2004 11.1 VIOLATION: End of code block */
    }
}

/*************************************************************************************************/
/**
@brief   Gpt driver de-initialization function for PitRti module.
@details This function is called separately for each PITRTI hw channel corresponding to the configured
         timer channels, and:
         - disables the PITRTI channel
         - disables the freeze mode
         - disables IRQ corresponding to PitRti channel
         - clears the (pending) interrupt flag corresponding to PitRti channel

@param[in]     hwChannel        PitRti hw channel ID

@remarks Implements DGPT09200
*/
/*************************************************************************************************/
#if (GPT_DEINIT_API == STD_ON)
FUNC (void, GPT_CODE) PitRti_LLD_DeInit(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel)
{
    /* Reset Status and Control Register */
    /*
    */
/**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer - See PitRti_Gpt_LLD_C_REF_3 */
    PITRTI_FREEZE_DISABLE();

    if ((Gpt_ChannelType)PITRTI_RTC_CH_0 == hwChannel)
    {
/**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer - See PitRti_Gpt_LLD_C_REF_3 */
   /* This is applicable for the following lines of code */
        PITRTI_RTC_COUNTER_DISABLE();
        PITRTI_RTC_INT_DISABLE();
        /* Clear Interrupt Flag */
        PITRTI_RTC_CLEAR_INTERRUPT();
        PITRTI_DISABLE_RTI_CLOCK();
    /* MISRA-C:2004 11.1 VIOLATION: End of code block */
    }
    else
    {
/**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer - See PitRti_Gpt_LLD_C_REF_3 */
        PITRTI_TIMER_DISABLE(hwChannel);
        /*
        */
/**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer - See PitRti_Gpt_LLD_C_REF_3 */
   /* This is applicable for the following lines of code */  
        PITRTI_INTERRUPT_DISABLE(hwChannel);
        /* Clear Interrupt Flag */
        PITRTI_CLEAR_INT_FLAG(hwChannel);
    /* MISRA-C:2004 11.1 VIOLATION: End of code block */
    }
}
#endif

/*************************************************************************************************/
/**
@brief   Gpt driver function for starting the PitRti timer channel.
@details This function:
         - clears the (pending) interrupt flag corresponding to PitRti channel
         - disables the PITRTI timer channel
         - sets the load/timeout value into the PITRTI timer channel register
         - enables the PITRTI timer channel
         - enables the IRQ corresponding to the PITRTI timer channel

@param[in]     hwChannel        PitRti hw channel ID
@param[in]     value            channel timeout value
@param[in]     channelMode      One Shot or Continous


@remarks Implements DGPT09208
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) PitRti_LLD_StartTimer(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel,
                                         VAR(Gpt_ValueType, AUTOMATIC) value,
                                         VAR(Gpt_ChannelModeType, AUTOMATIC) channelMode)
{
    VAR(uint16,AUTOMATIC) timeout=PITRTI_TIMEOUT_VALUE;
    if ((Gpt_ChannelType)PITRTI_RTC_CH_0 == hwChannel)
    {
/**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer - See PitRti_Gpt_LLD_C_REF_3 */
   /* This is applicable for the following lines of code */  
        PITRTI_RTC_CLEAR_INTERRUPT();
        PITRTI_RTC_COUNTER_DISABLE();
        PITRTI_RTC_SET_VALUE(value);
        PITRTI_RTC_COUNTER_ENABLE();
    /* MISRA-C:2004 11.1 VIOLATION: End of code block */
        if ((Gpt_ChannelModeType)GPT_MODE_ONESHOT == channelMode)
        {
/**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer - See PitRti_Gpt_LLD_C_REF_3 */
            PITRTI_RTC_INT_ENABLE();
            /* in One Shot mode the RTC channel is disabled within the RTI ISR */
        }
    }
    else
    {
 /**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer  - See PitRti_Gpt_LLD_C_REF_3 */
   /* This is applicable for the following lines of code */
        PITRTI_CLEAR_INT_FLAG(hwChannel);
        PITRTI_TIMER_DISABLE(hwChannel);
        PITRTI_SETLOADVALUE(hwChannel, value);
        while(((PITRTI_READTIMERVALUE(hwChannel)) !=  value) && (timeout > 0U))
        {
          timeout--;
        }
        if(timeout == 0x0U)
        {
         /* Report the error to DEM */
            Dem_ReportErrorStatus((uint16)GPT_E_TIMEOUT_TRANSITION,(uint8)DEM_EVENT_STATUS_FAILED);
        }
        else
        {
            PITRTI_TIMER_ENABLE(hwChannel);
         /* MISRA-C:2004 11.1 VIOLATION: End of code block */
            if (GPT_MODE_ONESHOT == channelMode)
            {
/**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer - See PitRti_Gpt_LLD_C_REF_3 */
               PITRTI_INTERRUPT_ENABLE(hwChannel);
               /* in One Shot mode the PITRTI channel is disabled within the Gpt ISR */
            }
        }
    }
}

/*************************************************************************************************/
/**
@brief   Gpt driver function for stopping the PitRti timer channel.
@details This function disables the PITRTI channel

@param[in]     hwChannel        PitRti hw channel ID

@remarks Implements DGPT09209
*/
/*************************************************************************************************/
FUNC (void, GPT_CODE) PitRti_LLD_StopTimer(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel)
{
    if ((Gpt_ChannelType)PITRTI_RTC_CH_0 == hwChannel)
    {
 /**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer - See PitRti_Gpt_LLD_C_REF_3 */
   /* This is applicable for the following lines of code */
        PITRTI_RTC_COUNTER_DISABLE();
        /* Clear Interrupt Flag */
        PITRTI_RTC_CLEAR_INTERRUPT();
    /* MISRA-C:2004 11.1 VIOLATION: End of code block */
    }
    else
    {
 /**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer - See PitRti_Gpt_LLD_C_REF_3 */
   /* This is applicable for the following lines of code */
        PITRTI_TIMER_DISABLE(hwChannel);
        /* Clear Interrupt Flag */
        PITRTI_CLEAR_INT_FLAG(hwChannel);
    /* MISRA-C:2004 11.1 VIOLATION: End of code block */
    }
}

/*************************************************************************************************/
/**
@brief   Gpt driver function for getting the time elapsed for an PitRti timer channel.
@details This function:
         - reads the PITRTI channel load register
         - reads the PITRTI counter register
         - depending on above it calculates and returns the elapsed time

@param[in]     hwChannel        PitRti hw channel ID
@param[out]    returnValuePtr   elapsed time value

@remarks Implements DGPT09203
*/
/*************************************************************************************************/
#if (GPT_TIME_ELAPSED_API == STD_ON)
FUNC (void, GPT_CODE) PitRti_LLD_GetTimeElapsed(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel,
                                             P2VAR(Gpt_ValueType, AUTOMATIC, GPT_APPL_DATA) returnValuePtr)
{
    VAR(uint32, AUTOMATIC) loadValue, currentTimerValue;

    if ((Gpt_ChannelType)PITRTI_RTC_CH_0 == hwChannel)
    {
 /**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer - See PitRti_Gpt_LLD_C_REF_3 */
   /* This is applicable for the following lines of code */
        loadValue = PITRTI_RTC_GET_VALUE();
        currentTimerValue = PITRTI_RTC_GET_COUNTER();
    /* MISRA-C:2004 11.1 VIOLATION: End of code block */
    }
    else
    {
 /**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer - See PitRti_Gpt_LLD_C_REF_3 */
   /* This is applicable for the following lines of code */
        loadValue = PITRTI_GETLOADVALUE(hwChannel);
        currentTimerValue = PITRTI_READTIMERVALUE(hwChannel);
    /* MISRA-C:2004 11.1 VIOLATION: End of code block */
    }
    *returnValuePtr = loadValue - currentTimerValue;
}
#endif

/*************************************************************************************************/
/**
@brief   Gpt driver function for getting the remaining time for an PitRti timer channel.
@details This function reads the PITRTI counter register and returns the elapsed time

@param[in]     hwChannel        PitRti hw channel ID
@param[out]    returnValuePtr   elapsed time value

@remarks Implements DGPT09204
*/
/*************************************************************************************************/
#if (GPT_TIME_REMAINING_API == STD_ON)
FUNC (void, GPT_CODE) PitRti_LLD_GetTimeRemaining(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel,
                                               P2VAR(Gpt_ValueType, AUTOMATIC, GPT_APPL_DATA) returnValuePtr)
{
    if ((Gpt_ChannelType)PITRTI_RTC_CH_0 == hwChannel)
    {
    /**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer  - See PitRti_Gpt_LLD_C_REF_3 */
        *returnValuePtr = PITRTI_RTC_GET_COUNTER();
    }
    else
    {
    /**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer  - See PitRti_Gpt_LLD_C_REF_3 */
        *returnValuePtr = PITRTI_READTIMERVALUE(hwChannel);
    }
}
#endif

/*************************************************************************************************/
/**
@brief   Gpt driver function for putting the PitRti timer channel in SLEEP mode.
@details This function is called separately for each PITRTI hw channel corresponding to the configured
         timer channels, and:
         - clears the (pending) interrupt flag corresponding to PitRti timer channel
         - disable the PitRti timer channel if the channel wakeup function is disabled
         - enable the PitRti timer channel if the channel wakeup function is enabled

@param[in]     hwChannel        PitRti hw channel ID
@param[in]     wakeUpEnabled    Indicates whether wake up functionality is enabled or not for the
                                corresponding channel.

@remarks Implements DGPT09207
*/
/*************************************************************************************************/
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
FUNC (void, GPT_CODE) PitRti_LLD_SetSleepMode(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel, VAR(boolean, AUTOMATIC) wakeUpEnabled)
{
    if ((Gpt_ChannelType)PITRTI_RTC_CH_0 == hwChannel)
    {
    /**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer  - See PitRti_Gpt_LLD_C_REF_3 */
        PITRTI_RTC_CLEAR_INTERRUPT();

        /* Check if wake-up is NOT enabled */
        if ((boolean)FALSE == wakeUpEnabled)
        {
    /**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer  - See PitRti_Gpt_LLD_C_REF_3 */
            PITRTI_RTC_COUNTER_DISABLE();
        }
        else
        {
    /**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer  - See PitRti_Gpt_LLD_C_REF_3 */
            PITRTI_RTC_INT_ENABLE();
        }
    }
    else
    {
    /**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer  - See PitRti_Gpt_LLD_C_REF_3 */
        PITRTI_CLEAR_INT_FLAG(hwChannel);

        /* Check if wake-up is NOT enabled */
        if ((boolean)FALSE == wakeUpEnabled)
        {
    /**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer  - See PitRti_Gpt_LLD_C_REF_3 */
            PITRTI_TIMER_DISABLE(hwChannel);
        }
        else
        {
    /**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer  - See PitRti_Gpt_LLD_C_REF_3 */
            PITRTI_INTERRUPT_ENABLE(hwChannel);
        }
    }
}
#endif

/*************************************************************************************************/
/**
@brief   Gpt driver function for enabling the PitRti timer channel notification/IRQ.
@details This function:
         - enables the IRQ corresponding to the PitRti timer channel

@param[in]     hwChannel        PitRti hw channel ID

@remarks Implements DGPT09202
*/
/*************************************************************************************************/
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
FUNC (void, GPT_CODE) PitRti_LLD_EnableNotification(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel)
{
    if ((Gpt_ChannelType)PITRTI_RTC_CH_0 == hwChannel)
    {
    /**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer  - See PitRti_Gpt_LLD_C_REF_3 */
        PITRTI_RTC_INT_ENABLE();
    }
    else
    {
    /**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer  - See PitRti_Gpt_LLD_C_REF_3 */
        PITRTI_INTERRUPT_ENABLE(hwChannel);
    }
}
#endif

/*************************************************************************************************/
/**
@brief   Gpt driver function for disabling the PitRti timer channel notification/IRQ.
@details This function disables the IRQ corresponding to the PitRti timer channel

@param[in]     hwChannel        PitRti hw channel ID

@remarks Implements DGPT09201
*/
/*************************************************************************************************/
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
FUNC (void, GPT_CODE) PitRti_LLD_DisableNotification(VAR(Gpt_ChannelType, AUTOMATIC) hwChannel)
{
    if ((Gpt_ChannelType)PITRTI_RTC_CH_0 == hwChannel)
    {
    /**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer  - See PitRti_Gpt_LLD_C_REF_3 */
        PITRTI_RTC_INT_DISABLE();
    }
    else
    {
    /**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer  - See PitRti_Gpt_LLD_C_REF_3 */
        PITRTI_INTERRUPT_DISABLE(hwChannel);
    }
}
#endif

#define GPT_STOP_SEC_CODE
/**
@file   Pitrti_Gpt_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref PITRTI_GPT_LLD_C_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref PITRTI_GPT_LLD_C_REF_2
*//*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif
