/**
    @file        sample_app_mcal_adc_task.c
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

#include "sample_app_mcal_adc_task.h"

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
@brief This is the timeout for the adc conversion
*/
#define SAMPLE_ADC_CONVERSION_TIMEOUT              10000U
#define SAMPLE_ADC_BITS_RESOLUTION                  12U
/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/
VAR(Adc_ValueGroupType, AUTOMATIC) AdcResultBufferPointer[1];
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
@brief      SampleAppAdcInit - Initialize the ADC task
@details    After calling this function the task containing ADC should be initialize

@return     Returns the value of success
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*================================================================================================*/
FUNC (Std_ReturnType, SAMPLE_APP_CODE) SampleAppAdcInit(P2VAR(SampleAppData_T, AUTOMATIC, SAMPLE_APP_VAR) pstSampleAppData)
{
    Std_ReturnType stdRet = E_OK;
    extern P2CONST(Adc_ConfigType, ADC_VAR, ADC_APPL_CONST) Adc_Cfg_Ptr;

    pstSampleAppData->stAdcData.pAdcDriverConfig = (Adc_ConfigType *)(&AdcConfigSet_0);

    /* Initialize the ADC with the post build configuration pointer*/
    Adc_Init(pstSampleAppData->stAdcData.pAdcDriverConfig);

    /* Set up the state of the state machine depending on the success of initialization*/
    if (pstSampleAppData->stAdcData.pAdcDriverConfig  == Adc_Cfg_Ptr)
    {
        pstSampleAppData->stAdcData.usAdcMaxValueRes = (1 << SAMPLE_ADC_BITS_RESOLUTION) ;
        pstSampleAppData->stAdcData.ucState = ADC_INITIAL_STATE;
    }
    else
    {   
        pstSampleAppData->stAdcData.ucState = ADC_ERROR_STATE;
        CONSOLE_MESSAGE("ADC: Error at ADC initialization ");
        stdRet = E_NOT_OK;
    }
    
    return stdRet;
}


/** 
@brief      SampleAppAdcTask - Contains the ADC task
@details

@return     Returns the value of success of executing the ADC task
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*================================================================================================*/
FUNC (Std_ReturnType, SAMPLE_APP_CODE) SampleAppAdcTask(P2VAR(SampleAppData_T, AUTOMATIC, SAMPLE_APP_VAR) pstSampleAppData)
{
    Std_ReturnType stdRet = E_OK;
    
    /* ADC state machine*/
    switch(pstSampleAppData->stAdcData.ucState)
    {
        case ADC_INITIAL_STATE:

            /*Setup the result buffer and the conversion timeout*/
            stdRet = Adc_SetupResultBuffer(AdcGroup_0, AdcResultBufferPointer);
            pstSampleAppData->stAdcData.ulTimeout = SAMPLE_ADC_CONVERSION_TIMEOUT;

            if (stdRet == E_OK)
            {
                pstSampleAppData->stAdcData.ucState = ADC_INITIALIZED_STATE;
            }
            else
            {
                pstSampleAppData->stAdcData.ucState = ADC_ERROR_STATE;
                CONSOLE_MESSAGE("ADC: Error when setting up the result buffer for ADC");
                break;
            }

        case ADC_INITIALIZED_STATE:

            /* Start the group conversion*/
            Adc_StartGroupConversion(AdcGroup_0);

            pstSampleAppData->stAdcData.ucState = ADC_CONVERT_PENDING_STATE;

        case ADC_CONVERT_PENDING_STATE:

            /* Wait for group conversion to be finished*/
            if(ADC_STREAM_COMPLETED == Adc_GetGroupStatus(AdcGroup_0))
            {
                pstSampleAppData->stAdcData.ucState = ADC_FINISH_CONVERT_STATE;
            }
             else
             {
                 if (pstSampleAppData->stAdcData.ulTimeout-- == 0)
                 {
                     pstSampleAppData->stAdcData.ucState = ADC_ERROR_STATE;
                    CONSOLE_MESSAGE("ADC Error: The timeout for ADC conversion has expired");
                     stdRet = E_NOT_OK;
                 }
                 break;
             }



        case ADC_FINISH_CONVERT_STATE:

            /* Stop the group conversion*/
            Adc_StopGroupConversion(AdcGroup_0);

            if(ADC_IDLE == Adc_GetGroupStatus(AdcGroup_0))
            {
                pstSampleAppData->stAdcData.usValueConverted =AdcResultBufferPointer[AdcChannel_0];
                pstSampleAppData->stAdcData.ucState = ADC_COMPLETE_STATE;
            }
            else
            {
                pstSampleAppData->stAdcData.ucState = ADC_ERROR_STATE;
                CONSOLE_MESSAGE("ADC Error: The ADC group conversion could not be stopped");
                stdRet = E_NOT_OK;

                break;
            }


         case ADC_COMPLETE_STATE:

             stdRet = E_OK;

             break;

         case ADC_ERROR_STATE:

             stdRet = E_NOT_OK;

             break;

        default:

            stdRet = E_NOT_OK;

            break;
    }
return stdRet;
}


/*================================================================================================*/
/*================================================================================================*/
#ifdef __cplusplus
}
#endif
