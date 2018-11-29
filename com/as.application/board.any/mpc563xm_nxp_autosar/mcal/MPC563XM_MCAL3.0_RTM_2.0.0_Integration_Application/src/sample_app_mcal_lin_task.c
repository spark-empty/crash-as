/**
    @file        sample_app_mcal_lin_task.c
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

#include "sample_app_mcal_lin_task.h"

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
#if defined(AUTOSAR_OS_NOT_USED)
#define LIN_SLEEP_TIMEOUT             0x1000UL
#else
#define LIN_SLEEP_TIMEOUT             0x50UL
#endif

#define LIN_GETSTATUS_TIMEOUT         0x40000UL
#define LIN_LOGICAL_CHANNEL           0x0U

/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/
VAR(uint8,AUTOMATIC) dataToSend[8] = {1, 2, 3, 4, 5, 6, 7, 8};
VAR(uint8,AUTOMATIC) linSdu[8] = {1, 1, 1, 1, 1, 1, 1, 1};
VAR(uint8,AUTOMATIC) *linSduPtr[1];

VAR(uint8,AUTOMATIC) *dataToReceivePtr[1];
VAR(uint8,AUTOMATIC) dataToReceive[8] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};


/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/

/** 
@brief This is the global variable that holds all the sample app specific data
*/

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
#if (USE_LIN_MODULE==STD_ON)
/**
@brief      SampleAppLinInit - Initialize the Lin task
@details    After calling this function the task containing Lin should be initialize

@return     Returns the value of success
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
FUNC (Std_ReturnType, SAMPLE_APP_CODE) SampleAppLinInit(P2VAR(SampleAppData_T, AUTOMATIC, SAMPLE_APP_VAR) pstSampleAppData)
{
    /* local variables here */
    
    /* set the first state in the state-machine */
    pstSampleAppData->stLinData.ucState = LIN_INITIAL_STATE;
    /*CONSOLE_MESSAGE("LIN state-machine state:%d", pstSampleAppData->stLinData.ucState);*/
    
    /* setup the Lin PB configuration pointer */
    pstSampleAppData->stLinData.pLinDriverConfig = (Lin_ConfigType *)(&LinGlobalConfig_0);
    
    Lin_Init(pstSampleAppData->stLinData.pLinDriverConfig);
    Lin_InitChannel(LIN_LOGICAL_CHANNEL, (pstSampleAppData->stLinData.pLinDriverConfig->Lin_Channel[LIN_LOGICAL_CHANNEL]));
    
    /* set the state to initialized */
    pstSampleAppData->stLinData.ucState = LIN_OPERATIONAL_STATE;
    
    return (E_OK);
}
#endif


#if (USE_LIN_MODULE==STD_ON)
/**
@brief      SampleAppLinTask - Contains the Lin task
@details

@return     Returns the value of success of executing the Lin task
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
FUNC (Std_ReturnType, SAMPLE_APP_CODE) SampleAppLinTask(P2VAR(SampleAppData_T, AUTOMATIC, SAMPLE_APP_VAR) pstSampleAppData)
{
    /* local variables here */
    Std_ReturnType stdRet = E_OK;
    dataToReceivePtr[0] = dataToReceive;

    linSduPtr[0] = linSdu;
    


    switch(pstSampleAppData->stLinData.ucState)
    {
        case LIN_OPERATIONAL_STATE:
        {
            stdRet = Lin_GoToSleep(LIN_LOGICAL_CHANNEL);
            /*stdRet = Lin_GoToSleepInternal(LIN_LOGICAL_CHANNEL);*/
            if (stdRet != E_OK)
            {
                CONSOLE_MESSAGE("LIN Error %d returned by Lin_GoToSleep\n", stdRet);
                pstSampleAppData->stLinData.ucState = LIN_ERROR_STATE;
                return (E_OK);
            }
            /* LIN sent to sleep - change state */
            pstSampleAppData->stLinData.ucState = LIN_SLEEP_STATE;
            /* setup the timeout for sleep to LIN_SLEEP_TIMEOUT task executions */
            pstSampleAppData->stLinData.ulSleepTimeout = LIN_SLEEP_TIMEOUT;
            return (E_OK);
        }
        
        case LIN_SLEEP_STATE:
        {
            if (LIN_CH_SLEEP != Lin_GetStatus(LIN_LOGICAL_CHANNEL, dataToReceivePtr))
            {
            if (pstSampleAppData->stLinData.ulSleepTimeout > 0)
            {
                /* LIN is still in sleep state */
                pstSampleAppData->stLinData.ulSleepTimeout--;
                return (E_OK);
            }
            }
            else
            {
                /* sleep timeout finished - try wakeup */
                stdRet = Lin_WakeUp(LIN_LOGICAL_CHANNEL);
                if (stdRet != E_OK)
                {
                    CONSOLE_MESSAGE("LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", stdRet);
                    pstSampleAppData->stLinData.ucState = LIN_ERROR_STATE;
                    return (E_OK);
                }
                /* LIN wakeup OK - proceed to wakeup state */
                pstSampleAppData->stLinData.ucState = LIN_WAKEUP_STATE;
                return (E_OK);
            }
        }
        
        case LIN_WAKEUP_STATE:
        {
            /* we're ready to transmit - proceed to transmit state */
            pstSampleAppData->stLinData.ucState = LIN_TRANSMIT_STATE;
            return (E_OK);
        }
        
        case LIN_TRANSMIT_STATE:
        {
            pstSampleAppData->stLinData.tosend_header.Cs = LIN_ENHANCED_CS;
            pstSampleAppData->stLinData.tosend_header.Drc = LIN_MASTER_RESPONSE;
            pstSampleAppData->stLinData.tosend_header.SduPtr = dataToSend;
            pstSampleAppData->stLinData.tosend_header.Pid = 20;
            pstSampleAppData->stLinData.tosend_header.Dl = 8;
            
            stdRet = Lin_SendHeader(LIN_LOGICAL_CHANNEL, &pstSampleAppData->stLinData.tosend_header);
            if (stdRet != E_OK)
            {
                CONSOLE_MESSAGE("LIN Error %d returned by Lin_SendHeader\n", stdRet);
                pstSampleAppData->stLinData.ucState = LIN_ERROR_STATE;
                return (E_OK);
            }
            
            stdRet = Lin_SendResponse(LIN_LOGICAL_CHANNEL, &pstSampleAppData->stLinData.tosend_header);
            if (stdRet != E_OK)
            {
                CONSOLE_MESSAGE("LIN Error %d returned by Lin_SendResponse\n", stdRet);
                pstSampleAppData->stLinData.ucState = LIN_ERROR_STATE;
                return (E_OK);
            }
                        
            /* we've sent the header and the response and now go to TX pending state */
            pstSampleAppData->stLinData.ucState = LIN_TX_PENDING_STATE;
            pstSampleAppData->stLinData.ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
            return (E_OK);
        }
        
        case LIN_TX_PENDING_STATE:
        {
            stdRet = Lin_GetStatus(LIN_LOGICAL_CHANNEL, linSduPtr);
            
            if ((stdRet == LIN_CH_OPERATIONAL) || (LIN_TX_OK == stdRet))
            {
                /* transmission ended OK - proceed to LIN_FINAL_STATE */
                pstSampleAppData->stLinData.ucState = LIN_FINAL_STATE;
            }
            else
            {
                if(pstSampleAppData->stLinData.ulGetStatusTimeout > 0)
                {
                    /* we're waiting for the transmission completion - decrease timeout */
                    pstSampleAppData->stLinData.ulGetStatusTimeout--;
                    return (E_OK);
                }
                else
                {
                    CONSOLE_MESSAGE("LIN Error - transmission timeout : %d\n", stdRet);
                        pstSampleAppData->stLinData.ucState = LIN_ERROR_STATE;
                    return (E_OK);
                }
            }
            return (E_OK);
        }
        
        case LIN_FINAL_STATE:
        {
            /* the task ended successfully */
            CONSOLE_MESSAGE("LIN task ended OK.\n");
            pstSampleAppData->stLinData.ucState = LIN_STALLED_STATE;
            return (E_OK);
        }
        
        case LIN_STALLED_STATE:
        {
            /* everything went fine for this module - task stalled */
            asm("nop");
            return (E_OK);
        }
        
        case LIN_ERROR_STATE:
        {
            /* we ended up in error - do nothing */
            return (E_OK);
        }
        
        default:
        {
            /* if we got here, something went terribly wrong*/
        }
        break;
    }
    
    return (E_NOT_OK);
}
#endif
/*================================================================================================*/

/*================================================================================================*/
/*================================================================================================*/
#ifdef __cplusplus
}
#endif
