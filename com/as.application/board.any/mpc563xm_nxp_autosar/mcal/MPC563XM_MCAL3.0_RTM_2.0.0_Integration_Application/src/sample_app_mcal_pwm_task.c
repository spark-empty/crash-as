/**
    @file        sample_app_mcal_pwm_task.c
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

#include "sample_app_mcal_pwm_task.h"
#include "Pwm_Cfg.h"

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
/**
@brief This constant defines the maximum value of the pwm's duty cycle
*/
#define PWM_DUTY_CYCLE_MAX_VALUE 0x8000U

/**
@brief This constant defines number of periods
*/
#define PWM_PERIODS              10U
#define PWM_DUTY_TRIM            0x30U
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

/**
@brief      Pwm_Led1Notification - Notification function for channel Pwm_Led1
@details    This notification starts the Icu signal measurement and sets icu in the finish
            measurement state, after a number of PWM_PERIODS had passed

@return     void

@pre None
@post None
*/
void Pwm_Led1Notification(void)
{
    uint8 IcuState = stSampleAppData.stIcuData.ucState;

    if ( ICU_INITIAL_STATE == IcuState )
    {
        /* Start the duty cycle measurement of PWM signals using ICU*/
        if (6 >= --stSampleAppData.stPwmData.ucNoOfSamples)
        {
            Icu_StartSignalMeasurement(Pwm_measure);
            stSampleAppData.stIcuData.ucState         = ICU_RUNNING_STATE;
        }
    }
    else if( ICU_RUNNING_STATE == IcuState )
    {
           if (0 == --stSampleAppData.stPwmData.ucNoOfSamples)
           {
               /* after a certain number of periods the icu is switch to finish measurement state*/
               stSampleAppData.stIcuData.ucState = ICU_FINISHED_MEASUREMENT_STATE;
               Pwm_DisableNotification(Pwm_Led1);
           }

    }
    else
    {
        stSampleAppData.stIcuData.ucState = ICU_ERROR_STATE;
        stSampleAppData.stPwmData.ucState = PWM_ERROR_STATE;
        Pwm_DisableNotification(Pwm_Led1);
        CONSOLE_MESSAGE("PWM Error: ICU was not in INITIAL STATE nor RUNNING STATE when the PWM notification was called");
    }

}

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

/**
@brief      SampleAppPwmInit - Initialize the Pwm task
@details    After calling this function the task containing PWM should be initialize

@return     Returns the value of success
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*================================================================================================*/
FUNC (Std_ReturnType, SAMPLE_APP_CODE) SampleAppPwmInit(P2VAR(SampleAppData_T, AUTOMATIC, SAMPLE_APP_VAR) pstSampleAppData)
{
    Std_ReturnType stdRet = E_OK;
    extern P2CONST(Pwm_ConfigType, ADC_VAR, ADC_APPL_CONST) Pwm_Cfg_Ptr;

    pstSampleAppData->stPwmData.pPwmDriverConfig = (Pwm_ConfigType *)(&PwmChannelConfigSet_0);

    /* Initialize the PWM with the post build configuration pointer*/
    Pwm_Init(pstSampleAppData->stPwmData.pPwmDriverConfig);

    /* Set up the state of the state machine depending on the success of initialization*/
    if (pstSampleAppData->stPwmData.pPwmDriverConfig == Pwm_Cfg_Ptr)
    {
        pstSampleAppData->stPwmData.ucState = PWM_INITIAL_STATE;
    }
    else
    {
        pstSampleAppData->stPwmData.ucState = PWM_ERROR_STATE;
        CONSOLE_MESSAGE("PWM Error at initialization");
        stdRet = E_NOT_OK;
    }

    return stdRet;
}


/**
@brief      SampleAppPwmTask - Contains the Pwm task
@details

@return     Returns the value of success of executing the Pwm task
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*================================================================================================*/
FUNC (Std_ReturnType, SAMPLE_APP_CODE) SampleAppPwmTask(P2VAR(SampleAppData_T, AUTOMATIC, SAMPLE_APP_VAR) pstSampleAppData)
{
    Std_ReturnType stdRet = E_OK;

    /* Pwm state machine*/
    switch(pstSampleAppData->stPwmData.ucState)
    {
        case PWM_INITIAL_STATE:
            if (pstSampleAppData->stAdcData.ucState == ADC_COMPLETE_STATE)
            {
                pstSampleAppData->stPwmData.ucNoOfSamples    = PWM_PERIODS;
                pstSampleAppData->stPwmData.usDutyCycle      = (uint16)( (pstSampleAppData->stAdcData.usValueConverted * PWM_DUTY_CYCLE_MAX_VALUE) /pstSampleAppData->stAdcData.usAdcMaxValueRes);
                pstSampleAppData->stPwmData.ucState          = PWM_INITIALIZED_STATE;

                /* Compensate duty at limit values for the ICU readings*/
                if ( (PWM_DUTY_CYCLE_100 - PWM_DUTY_TRIM) <= pstSampleAppData->stPwmData.usDutyCycle)
                {
                    pstSampleAppData->stPwmData.usDutyCycle = PWM_DUTY_CYCLE_100 - PWM_DUTY_TRIM;
                }
                else if(PWM_DUTY_TRIM >= pstSampleAppData->stPwmData.usDutyCycle)
                {
                    pstSampleAppData->stPwmData.usDutyCycle = PWM_DUTY_TRIM;
                }
            }
            else
            {
                break;
            }

        case PWM_INITIALIZED_STATE:

            /* Enable the notification service and set up the pwm duty cycle*/
            pstSampleAppData->stPwmData.ucState = PWM_RUNNING_STATE;

            Pwm_SetDutyCycle(Pwm_Led1, pstSampleAppData->stPwmData.usDutyCycle);
            Pwm_EnableNotification(Pwm_Led1,PWM_RISING_EDGE);


        case PWM_RUNNING_STATE:

            if (pstSampleAppData->stIcuData.ucState == ICU_FINISHED_MEASUREMENT_STATE)
            {
                pstSampleAppData->stPwmData.ucState = PWM_COMPLETE_STATE;
                /*CONSOLE_MESSAGE("PWM state-machine state:%d", pstSampleAppData->stPwmData.ucState);*/
            }
            else
            {
                break;
            }

        case PWM_COMPLETE_STATE:

            stdRet = E_OK;

            break;

        case PWM_ERROR_STATE:

            stdRet = E_NOT_OK;

            break;

        default:

            stdRet = E_NOT_OK;

            break;
    }
    return (stdRet);
}


/*================================================================================================*/
/*================================================================================================*/
#ifdef __cplusplus
}
#endif
