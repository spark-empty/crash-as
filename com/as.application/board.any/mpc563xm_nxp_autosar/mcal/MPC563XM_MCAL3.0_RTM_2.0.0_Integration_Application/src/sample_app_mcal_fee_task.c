/**
    @file        sample_app_mcal_fee_task.c
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

#include "sample_app_mcal_fee_task.h"
#include "Fls_sectors_unlock.h"
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

CONST (uint8, AUTOMATIC) buff[32]={0x55,0xAA,0x55,0xAA,0x55,0xAA,0x55,0xAA,
                                   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                   0x55,0xAA,0x55,0xAA,0x55,0xAA,0x55,0xAA};

/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/
VAR (uint8, AUTOMATIC)  buffrd[32]={0};


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
@brief      SampleAppFee_memcmp - Compare two buffers of memory 
@details    This function compare the contents of two buffer of the same length.

@return     E_OK when buffers contents match, E_NOT_OK when the buffers are different
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
static FUNC (Std_ReturnType, SAMPLE_APP_CODE) SampleAppFee_memcmp(P2VAR(uint8, AUTOMATIC, SAMPLE_APP_VAR) src1,
                                                 P2VAR(uint8, AUTOMATIC, SAMPLE_APP_VAR) src2,
                                                 VAR(uint16, AUTOMATIC) len) 
{
    /* local variables here */
    Std_ReturnType stdRet = E_OK;
    uint16 i;
    
    i = 0U;
    do
    {
        if (0x0U != (src1[i]^src2[i]))
        {
              stdRet = E_NOT_OK;
        }
        i++;
    }
    while((stdRet==E_OK) && (i<len));
    
    return stdRet;
}
/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
/**
@brief      Fee_JobEndNotif - Notification function called from Fee driver 
@details    This notification function is called by Fee driver after job end.

@return     none
@retval     none

@pre None
@post None
*/
/* Job End Notifications */
FUNC (void, SAMPLE_APP_CODE) Fee_JobEndNotif(void) 
{
#if (USE_FEE_MODULE==STD_ON) && (USE_FLS_MODULE==STD_ON)
    switch(stSampleAppData.stFeeData.ucState)
    {
        case FEE_ERASE_BUSY_STATE:
        {
            stSampleAppData.stFeeData.ucState = FEE_WRITE_STATE;
            break;  
        }
        case FEE_WRITE_BUSY_STATE:
        {
            stSampleAppData.stFeeData.ucState = FEE_READ_STATE;
            break;  
        }
        case FEE_READ_BUSY_STATE:
        {
            stSampleAppData.stFeeData.ucState = FEE_VALIDATE_STATE;
            break;  
        }
        default:
        {
            stSampleAppData.stFeeData.ucState = FEE_ERROR_STATE;
            CONSOLE_MESSAGE("FEE Error from Fee_JobEndNotif");
        }
    }
#endif
}

/**
@brief      Fee_JobErrorNotif - Notification function called from Fee driver 
@details    This notification function is called by Fee driver when an error occurs in the job.

@return     none
@retval     none

@pre None
@post None
*/
/*================================================================================================*/
/* Job Error Notifications */
FUNC (void, SAMPLE_APP_CODE) Fee_JobErrorNotif(void) 
{
#if (USE_FEE_MODULE==STD_ON) && (USE_FLS_MODULE==STD_ON)
    stSampleAppData.stFeeData.ucState = FEE_ERROR_STATE;
    CONSOLE_MESSAGE("FEE: Job Error Notification Handler!\n");
#endif
}

#if (USE_FEE_MODULE==STD_ON) && (USE_FLS_MODULE==STD_ON)
/**
@brief      SampleAppFeeInit - Initialize the Fee task
@details    After calling this function the task containing Fee and Fls drivers should be initialized

@return     Returns the value of success
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*================================================================================================*/
FUNC (Std_ReturnType, SAMPLE_APP_CODE) SampleAppFeeInit(P2VAR(SampleAppData_T, AUTOMATIC, SAMPLE_APP_VAR) pstSampleAppData)
{
    
    /* set the first state in the state-machine */
    pstSampleAppData->stFeeData.ucState = FEE_INITIAL_STATE;
    /*CONSOLE_MESSAGE("FEE state-machine state:%d", pstSampleAppData->stFeeData.ucState);*/
    
    /* setup the Fee PB configuration pointer */
    pstSampleAppData->stFeeData.pFlsDriverConfig = (Fls_ConfigType *)(&FlsConfigSet_0);
    
    /* FLS unprotect/unlock */
    Fls_SectorsUnlock();
    
    /* init Fls driver */
    Fls_Init(pstSampleAppData->stFeeData.pFlsDriverConfig);
    
    /* init Fee driver */
    Fee_Init();
    
    /* everything worked fine - set the state-machine and return E_OK */
    pstSampleAppData->stFeeData.ucState = FEE_ERASE_STATE;
    /*CONSOLE_MESSAGE("FEE state-machine state:%d", pstSampleAppData->stFeeData.ucState);*/
    return(E_OK);
}

/**
@brief      SampleAppFeeTask - Contains the Fee task
@details

@return     Returns the value of success of executing the Fee task
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*================================================================================================*/
FUNC (Std_ReturnType, SAMPLE_APP_CODE) SampleAppFeeTask(P2VAR(SampleAppData_T, AUTOMATIC, SAMPLE_APP_VAR) pstSampleAppData)
{
    /* local variables here */
    Std_ReturnType stdRet = E_NOT_OK;
    MemIf_StatusType memif_status;

    memif_status = Fee_GetStatus();
    /* state-machine logic */
    switch(pstSampleAppData->stFeeData.ucState)
    {
        case FEE_ERASE_STATE:
        {
            if (MEMIF_IDLE == memif_status)
            {
                stdRet = Fee_EraseImmediateBlock(FEE_BLOCK_1);
                if (stdRet != E_OK)
                {
                    CONSOLE_MESSAGE("FEE Error %d returned by Fee_EraseImmediateBlock()", stdRet);
                    /*CONSOLE_MESSAGE("FEE state-machine state:%d", pstSampleAppData->stFeeData.ucState);*/
                    pstSampleAppData->stFeeData.ucState = FEE_ERROR_STATE;
                }
                else
                {
                    /* change the state */
                    pstSampleAppData->stFeeData.ucState = FEE_ERASE_BUSY_STATE;
                    stdRet = E_OK;
                }
            }
            else
            {
                stdRet = E_OK;
            }
        }
        break;
        
        case FEE_WRITE_STATE:
        {
            if (MEMIF_IDLE == memif_status)
            {
                stdRet = Fee_Write(FEE_BLOCK_1, (uint8 *)buff);
                if (stdRet != E_OK)
                {
                    CONSOLE_MESSAGE("FEE Error %d returned by Fee_Write()", stdRet);
                    /*CONSOLE_MESSAGE("FEE state-machine state:%d", pstSampleAppData->stFeeData.ucState);*/
                    pstSampleAppData->stFeeData.ucState = FEE_ERROR_STATE;
                }
                else
                {
                    /* change the state */
                    pstSampleAppData->stFeeData.ucState = FEE_WRITE_BUSY_STATE;
                    stdRet = E_OK;
                }
            }
            else
            {
                stdRet = E_OK;
            }
        }
        break;

        case FEE_READ_STATE:
        {
            if (MEMIF_IDLE == memif_status)
            {
                stdRet = Fee_Read(FEE_BLOCK_1, 0, buffrd, 32u);
                if (stdRet != E_OK)
                {
                    CONSOLE_MESSAGE("FEE Error %d returned by Fee_Read()", stdRet);
                    /*CONSOLE_MESSAGE("FEE state-machine state:%d", pstSampleAppData->stFeeData.ucState);*/
                    pstSampleAppData->stFeeData.ucState = FEE_ERROR_STATE;
                }
                else
                {
                    /* change the state */
                    pstSampleAppData->stFeeData.ucState = FEE_READ_BUSY_STATE;
                }
            }
            else
            {
                stdRet = E_OK;
            }
        }
        break;
       
        case FEE_VALIDATE_STATE:
        {
            /* compare the read buffer with the written one */
            stdRet = SampleAppFee_memcmp((uint8 *)buff, buffrd, 32u);
            if (stdRet != E_OK)
            {
                CONSOLE_MESSAGE("FEE Error %d returned by SampleAppFee_memcmp()", stdRet);
                /*CONSOLE_MESSAGE("FEE state-machine state:%d", pstSampleAppData->stFeeData.ucState);*/
                pstSampleAppData->stFeeData.ucState = FEE_READ_ERROR_STATE;
                CONSOLE_MESSAGE("Fee task READ ERROR!\n");
            }
            else
            {
                /* change the state */
                pstSampleAppData->stFeeData.ucState = FEE_FINAL_STATE;
                CONSOLE_MESSAGE("Fee task ended OK.\n");
            }
        }
        break;
        case FEE_ERASE_BUSY_STATE:
        case FEE_WRITE_BUSY_STATE:
        case FEE_READ_BUSY_STATE:
        case FEE_FINAL_STATE:
        {
                stdRet = E_OK;
        }
        break;
        case FEE_READ_ERROR_STATE:
        case FEE_ERROR_STATE:
        {
            stdRet = E_NOT_OK;
        }
        break;
        
        default:
        {
            /* if we got here, something went terribly wrong*/
            CONSOLE_MESSAGE("FEE Error that should not apear");
            stdRet = E_NOT_OK;
        }
        break;
    }
    return (stdRet);
    
}
#endif  /* (USE_FEE_MODULE==STD_ON) && (USE_FLS_MODULE==STD_ON) */

/*================================================================================================*/
#ifdef __cplusplus
}
#endif
