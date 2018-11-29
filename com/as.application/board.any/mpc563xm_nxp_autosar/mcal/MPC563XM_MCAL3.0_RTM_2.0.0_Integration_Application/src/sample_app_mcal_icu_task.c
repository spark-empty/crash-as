/**
    @file        sample_app_mcal_icu_task.c
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

#include "sample_app_mcal_icu_task.h"
#include "Icu_Cfg.h"

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
@brief MASK
*/
#define THRESHOLD       2

/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/

extern P2CONST(Icu_ConfigType, ICU_VAR, ICU_APPL_CONST) Icu_Cfg_Ptr;
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
@brief      SampleAppIcuInit - Initialize the Icu task
@details    After calling this function the task containing Icu should be initialize

@return     Returns the value of success
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*================================================================================================*/
FUNC (Std_ReturnType, SAMPLE_APP_CODE) SampleAppIcuInit(P2VAR(SampleAppData_T, AUTOMATIC, SAMPLE_APP_VAR) pstSampleAppData)
{
    Std_ReturnType stdRet = E_OK;

    pstSampleAppData->stIcuData.pIcuDriverConfig = (Icu_ConfigType *)(&IcuConfigSet_0);

    /* Initialize the PWM with the post build configuration pointer*/
    Icu_Init(pstSampleAppData->stIcuData.pIcuDriverConfig);

    /* Set up the state of the state machine depending on the success of initialization*/
     if (pstSampleAppData->stIcuData.pIcuDriverConfig  == Icu_Cfg_Ptr)
     {
         pstSampleAppData->stIcuData.ucState = ICU_INITIAL_STATE;
     }
     else
     {
         pstSampleAppData->stIcuData.ucState = ICU_ERROR_STATE;
         stdRet = E_NOT_OK;
     }

    return stdRet;
}


/**
@brief      SampleAppIcuTask - Contains the Icu task
@details

@return     Returns the value of success of executing the Icu task
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*================================================================================================*/
FUNC (Std_ReturnType, SAMPLE_APP_CODE) SampleAppIcuTask(P2VAR(SampleAppData_T, AUTOMATIC, SAMPLE_APP_VAR) pstSampleAppData)
{
    Std_ReturnType stdRet = E_OK;
    VAR(Icu_DutyCycleType, AUTOMATIC) sigDutyCycle;
    VAR (uint16, AUTOMATIC) IcuValueDutyCycle, AdcPercentageValue;
    VAR (uint16, AUTOMATIC) tol_positive = 0;

    /* ICU state machine*/
     switch(pstSampleAppData->stIcuData.ucState)
    {

        case ICU_FINISHED_MEASUREMENT_STATE:

            /* if the pwm_state was changed in complete, icu state can be also changed*/
            if (PWM_COMPLETE_STATE == pstSampleAppData->stPwmData.ucState)
            {
                if (ICU_ACTIVE != Icu_GetInputState(Pwm_measure))
                {
                    /* ICU measurement not ended */
                    break;
                }
                else
                {
                    Icu_GetDutyCycleValues(Pwm_measure, &sigDutyCycle);
                    pstSampleAppData->stIcuData.IcuDuty.ActiveTime = sigDutyCycle.ActiveTime;
                    pstSampleAppData->stIcuData.IcuDuty.PeriodTime = sigDutyCycle.PeriodTime;
                   
                    Icu_StopSignalMeasurement(Pwm_measure);


                    if (sigDutyCycle.ActiveTime == 0)
                    {
                        pstSampleAppData->stIcuData.ucState = ICU_ERROR_STATE;

                        CONSOLE_MESSAGE("ICU Error: Wrong value measured for Duty Cycle.");
                        stdRet = E_NOT_OK;
                        break;
                    }
                    else
                    {
                        IcuValueDutyCycle  = (sigDutyCycle.ActiveTime * 100) / sigDutyCycle.PeriodTime;
                    }

                    AdcPercentageValue = (pstSampleAppData->stAdcData.usValueConverted * 100) / pstSampleAppData->stAdcData.usAdcMaxValueRes;
                    tol_positive = IcuValueDutyCycle < AdcPercentageValue ? (AdcPercentageValue - IcuValueDutyCycle) : (IcuValueDutyCycle - AdcPercentageValue);

                    if (tol_positive > THRESHOLD)
                    {
                        pstSampleAppData->stIcuData.ucState = ICU_ERROR_STATE;
                        CONSOLE_MESSAGE("ICU Error: Duty cycle measured by ICU, was not the one set up using the value on ADC");
                        stdRet = E_NOT_OK;
                        break;
                    }
                    else
                    {
                        pstSampleAppData->stIcuData.ucState = ICU_COMPLETE_STATE;
                    }
                }
            }
            else
            {
                break;
            }

        case ICU_COMPLETE_STATE:
            /* Set up initial states to Adc, Pwm, Icu state machine*/
            pstSampleAppData->stAdcData.ucState = ADC_INITIAL_STATE;
            pstSampleAppData->stPwmData.ucState = PWM_INITIAL_STATE;
            pstSampleAppData->stIcuData.ucState = ICU_INITIAL_STATE;

        case ICU_INITIAL_STATE:
        case ICU_RUNNING_STATE:
            stdRet = E_OK;
            break;

        case ICU_ERROR_STATE:
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
