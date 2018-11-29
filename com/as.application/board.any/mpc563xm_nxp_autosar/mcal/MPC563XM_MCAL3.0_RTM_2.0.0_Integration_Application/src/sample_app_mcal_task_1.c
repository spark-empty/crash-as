/**
    @file        sample_app_mcal_task_1.c
    @version     2.0.0

    @brief       AUTOSAR - Autosar  Sample Application.
    @details     Sample application using AutoSar MCAL drivers.

    Project      : AUTOSAR 3.0 MCAL
    Platform     : PA
    Peripheral   : 
    Dependencies : Base Det Dem Port Dio Mcu SchM Wdg WdgIf CanIf LinIf EcuM

    Autosar Version       : 1.9.0
    Autosar Revision      : ASR_REL_1_9_REV_0003
    Autosar Conf. Variant :
    Software Version      : 2.0.0
    Build Version         : MPC563xMxM_MCAL_2_0_0_RTM_ASR_REL_1_9_REV_0003_20110214

    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
    All Rights Reserved.

    You can use this example for any purpose on any computer system with the following restrictions:
    1. This example is provided "as is", without warranty.
    2. You do not remove this copyright notice from this example or any direct derivation thereof.

*/
/*==================================================================================================
==================================================================================================*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

#include "sample_app_mcal_task_1.h"

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/


/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/

STATIC VAR(Dio_LevelType, AUTOMATIC) GptLed_state=STD_HIGH;
STATIC volatile VAR(uint8, AUTOMATIC) wdg_state = 0x0U;

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


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

/**
@brief      SampleAppGptLed - Notification function called from Gpt driver
@details    This notification function is called by Gpt driver after the timer expire.

@return     none
@retval     none

@pre None
@post None
*/
#if (USE_GPT_MODULE == STD_ON)
FUNC (void, SAMPLE_APP_CODE) SampleAppGptLed(void)
{
#if (USE_DIO_MODULE == STD_ON)
    if (STD_HIGH == GptLed_state)
    {
        GptLed_state = STD_LOW;
    }
    else
    {
        GptLed_state = STD_HIGH;
    }

    Dio_WriteChannel((Dio_ChannelType)Dio_Led3, (Dio_LevelType)GptLed_state);
#endif  /* #if (USE_DIO_MODULE == STD_ON) */
}
#endif  /* (USE_GPT_MODULE == STD_ON) */

/*================================================================================================*/
/**
@brief      SampleAppTask1 - Task1 function
@details    This function is called periodically by the OS or by the main() function.

@return     Returns the value of success
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
FUNC (Std_ReturnType, SAMPLE_APP_CODE) SampleAppTask1(P2VAR(SampleAppData_T, AUTOMATIC, SAMPLE_APP_VAR) pstSampleAppData)
{
    /* local variables here */
    Std_ReturnType stdRet = E_OK;

#if ((USE_WDG_MODULE == STD_ON) && (USE_DIO_MODULE == STD_ON))
    VAR(Dio_LevelType, AUTOMATIC) level;

    /* Read the status of the button */
    level = Dio_ReadChannel((Dio_ChannelType)Dio_Key1);

    /* Check if Button pressed */
    if (0x0U != level)
    {
        /* Turn OFF the Led2 */
        Dio_WriteChannel((Dio_ChannelType)Dio_Led2, (Dio_LevelType)STD_HIGH);

        /* Trigger the Watchdog */
        Wdg_Trigger();

        Dem_ReportErrorStatus(0x0U, 0x0U);
        wdg_state = 0x0U;
    }
    else
    {
        /* CONSOLE_MESSAGE("Going to reset NOW"); */
        if (WDG_E_MISS_TRIGGER == Dem_EventId)
        {
            /* Turn OFF the Led2 */
            Dio_WriteChannel((Dio_ChannelType)Dio_Led2, (Dio_LevelType)STD_HIGH);

            /* Restart Wdg */
            Wdg_SetMode(WDGIF_SLOW_MODE);
            wdg_state = 0x1U;
            /* CONSOLE_MESSAGE("WatchDog EVENT!!!\n"); */
        }
        else
        {
            if (0x0U == wdg_state)
            {
                /* Turn ON the Led2 */
                Dio_WriteChannel((Dio_ChannelType)Dio_Led2, (Dio_LevelType)STD_LOW);
                wdg_state = 0x1U;
            }
        }
    }
#endif  /* ((USE_WDG_MODULE == STD_ON) && (USE_DIO_MODULE == STD_ON)) */

#if ((USE_FEE_MODULE == STD_ON) && (USE_FLS_MODULE == STD_ON))

    if (FEE_FINAL_STATE != stSampleAppData.stFeeData.ucState)
    {
        /* start Watchdog and the Gpt timer after the Fee driver finished the execution */
        if (FEE_VALIDATE_STATE == stSampleAppData.stFeeData.ucState)
        {
#if (USE_WDG_MODULE == STD_ON)
            Wdg_SetMode(WDGIF_SLOW_MODE);
#endif  /* (USE_WDG_MODULE == STD_ON) */

#if (USE_GPT_MODULE == STD_ON)
            Gpt_EnableNotification(0);
            Gpt_StartTimer(0, GPT_TIMER_LED_TICKS);
#endif  /* (USE_GPT_MODULE == STD_ON) */
        }
        /* execute Fee task */
        stdRet = SampleAppFeeTask(pstSampleAppData);
    }
#else /* ((USE_FEE_MODULE == STD_ON) && (USE_FLS_MODULE == STD_ON)) */
#if (USE_WDG_MODULE==STD_ON)
    Wdg_SetMode(WDGIF_SLOW_MODE);
#endif /* (USE_WDG_MODULE==STD_ON) */
#if (USE_GPT_MODULE == STD_ON)
    Gpt_EnableNotification(0);
    Gpt_StartTimer(0, GPT_TIMER_LED_TICKS);
#endif  /* (USE_GPT_MODULE == STD_ON) */
#endif  /* ((USE_FEE_MODULE == STD_ON) && (USE_FLS_MODULE == STD_ON)) */

    return (stdRet);
}
/*================================================================================================*/

#ifdef __cplusplus
}
#endif
