/**
    @file        sample_app_mcal_spi_task.c
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

#include "sample_app_mcal_spi_task.h"

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


/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/

/**
@brief This is the global variable that holds all the sample app specific data
*/
#define SPI_TRANSMIT_TIMEOUT              10000
#define SPI_DATA_LENGTH                   8

#define SPI_CALLBACK_CALLED               0xFF

/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/
const Spi_DataType ucSource[SPI_DATA_LENGTH] = {0xA0, 0x0A, 0xAA, 0x05, 0x50, 0x55, 0xFF, 0x00};
Spi_DataType ucDest[SPI_DATA_LENGTH];

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

#if (USE_SPI_MODULE==STD_ON)

/*================================================================================================*/
/**
@brief      Spi_Job0_EndNotification - Notification function called from Spi driver
@details    This notification function is called by Spi driver after job end.

@return     none
@retval     none

@pre None
@post None
*/
/* Job End Notifications */
void Spi_Job0_EndNotification(void) /* End Notification for Job 'SpiJob_0' */
{
}

/*================================================================================================*/
/**
@brief      Spi_Seq0_EndNotification - Notification function called from Spi driver
@details    This notification function is called by Spi driver after sequence end.

@return     none
@retval     none

@pre None
@post None
*/
/* Sequence End Notifications */
void Spi_Seq0_EndNotification(void) /* End Notification for Sequence 'SpiSequence_0' */
{
    stSampleAppData.stSpiData.bFlags = SPI_CALLBACK_CALLED;
}

/*================================================================================================*/
/**
@brief      SampleAppSpiInit - Initialize the Spi task
@details    After calling this function the task containing Spi driver should be initialized

@return     Returns the value of success
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
FUNC (Std_ReturnType, SAMPLE_APP_CODE) SampleAppSpiInit(P2VAR(SampleAppData_T, AUTOMATIC, SAMPLE_APP_VAR) pstSampleAppData)
{
    /* local variables here */
    Std_ReturnType stdRet;

    /* set the first state in the state-machine */
    pstSampleAppData->stSpiData.ucState = SPI_INITIAL_STATE;
    /*CONSOLE_MESSAGE("SPI state-machine state:%d", pstSampleAppData->stSpiData.ucState);*/

    /* setup the Spi PB configuration pointer */
    pstSampleAppData->stSpiData.pSpiDriverConfig = (Spi_ConfigType *)(&SpiDriver_0);

    Spi_Init(pstSampleAppData->stSpiData.pSpiDriverConfig);

    stdRet = Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    if (stdRet != E_OK)
    {
        CONSOLE_MESSAGE("SPI Error %d returned by Spi_SetAsyncMode(SPI_INTERRUPT_MODE)", stdRet);
        /*CONSOLE_MESSAGE("SPI state-machine state:%d", pstSampleAppData->stSpiData.ucState);*/
        pstSampleAppData->stSpiData.ucState = SPI_ERROR_STATE;
        return (E_OK);
    }

    /* everything worked fine - set the state-machine and return E_OK */
    pstSampleAppData->stSpiData.ucState = SPI_INITIALIZED_STATE;
    /*CONSOLE_MESSAGE("SPI state-machine state:%d", pstSampleAppData->stSpiData.ucState);*/
    return(E_OK);
}
/*================================================================================================*/
/**
@brief      SampleAppSpiTask - Contains the Spi task
@details

@return     Returns the value of success of executing the Spi task
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
FUNC (Std_ReturnType, SAMPLE_APP_CODE) SampleAppSpiTask(P2VAR(SampleAppData_T, AUTOMATIC, SAMPLE_APP_VAR) pstSampleAppData)
{
    /* local variables here */
    Std_ReturnType stdRet;
    uint32 ulCounter;

    /* state-machine logic */
    switch(pstSampleAppData->stSpiData.ucState)
    {
        case SPI_INITIALIZED_STATE:
        {
            stdRet = Spi_WriteIB( SpiChannel_0, ucSource);
            if (stdRet != E_OK)
            {
                CONSOLE_MESSAGE("SPI Error %d returned by Spi_WriteIB( SpiChannel_0, ucTemp)", stdRet);
                /*CONSOLE_MESSAGE("SPI state-machine state:%d", pstSampleAppData->stSpiData.ucState);*/
                pstSampleAppData->stSpiData.ucState = SPI_ERROR_STATE;
                return (E_OK);
            }

            /* change the state */
            pstSampleAppData->stSpiData.ucState = SPI_TRANSMIT_STATE;
            return (E_OK);
        }
        /*break;*/

        case SPI_TRANSMIT_STATE:
        {
            stdRet = Spi_AsyncTransmit(SpiSequence_0);
            if (stdRet != E_OK)
            {
                CONSOLE_MESSAGE("SPI Error %d returned by Spi_AsyncTransmit(SpiSequence_0)", stdRet);
                /*CONSOLE_MESSAGE("SPI state-machine state:%d", pstSampleAppData->stSpiData.ucState);*/
                pstSampleAppData->stSpiData.ucState = SPI_ERROR_STATE;
                return (E_OK);
            }

            /* setup the timer */
            pstSampleAppData->stSpiData.ulTimeout = SPI_TRANSMIT_TIMEOUT;

            /* reset the callback flag */
            pstSampleAppData->stSpiData.bFlags = 0;

            /* change the state */
            pstSampleAppData->stSpiData.ucState = SPI_TX_PENDING_STATE;
            return (E_OK);
        }
        /*break;*/

        case SPI_TX_PENDING_STATE:
        {
            stdRet =  Spi_GetSequenceResult(SpiSequence_0);
            if (stdRet == SPI_SEQ_PENDING)
            {
                if (pstSampleAppData->stSpiData.ulTimeout > 0)
                {
                    /* decrease the timer*/
                    pstSampleAppData->stSpiData.ulTimeout--;
                    return (E_OK);
                }
                else
                {
                    /* the sequence is still pending and we have timeout */
                    CONSOLE_MESSAGE("SPI Error: Transmission timeout");
                    /*CONSOLE_MESSAGE("SPI state-machine state:%d", pstSampleAppData->stSpiData.ucState);*/
                    /* change the state */
                    pstSampleAppData->stSpiData.ucState = SPI_ERROR_STATE;
                    return (E_OK);
                }
            }

            /* check if the sequence has been transmitted ok */
            /* also check that the notification callback has been called */
            if ((stdRet == SPI_SEQ_OK) && (pstSampleAppData->stSpiData.bFlags == SPI_CALLBACK_CALLED))
            {
                stdRet = Spi_ReadIB( SpiChannel_0, ucDest);
                if (stdRet != E_OK)
                {
                    CONSOLE_MESSAGE("SPI Error %d returned by Spi_ReadIB( SpiChannel_0, ucDest)", stdRet);
                    /*CONSOLE_MESSAGE("SPI state-machine state:%d", pstSampleAppData->stSpiData.ucState);*/
                    pstSampleAppData->stSpiData.ucState = SPI_ERROR_STATE;
                    return (E_OK);
                }

                /* now compare the data and validate them */
                for (ulCounter = 0; ulCounter < SPI_DATA_LENGTH; ulCounter++)
                {
                    if (ucSource[ulCounter] != ucDest[ulCounter])
                    {
                        CONSOLE_MESSAGE("SPI Error: Tx/Rx data does not match ucSource[%d]=%d, ucDest[%d]=%d",
                                ulCounter, ucSource[ulCounter], ulCounter, ucDest[ulCounter] );
                        /*CONSOLE_MESSAGE("SPI state-machine state:%d", pstSampleAppData->stSpiData.ucState);*/
                        pstSampleAppData->stSpiData.ucState = SPI_ERROR_STATE;
                        return (E_OK);
                    }
                }

                /* everything went fine if we are here */
                pstSampleAppData->stSpiData.ucState = SPI_FINAL_STATE;
                return (E_OK);
            }
            else
            {
                /* the sequence transmission is canceled */
                CONSOLE_MESSAGE("SPI Error: sequence transmission is canceled");
                /*CONSOLE_MESSAGE("SPI state-machine state:%d", pstSampleAppData->stSpiData.ucState);*/
                /* change the state */
                pstSampleAppData->stSpiData.ucState = SPI_ERROR_STATE;
                return (E_OK);
            }
        }
        /*break;*/

        case SPI_FINAL_STATE:
        {
            /* the task ended successfully */
            CONSOLE_MESSAGE("SPI task ended OK.\n");
            /*CONSOLE_MESSAGE("SPI state-machine state:%d", pstSampleAppData->stSpiData.ucState);*/
            pstSampleAppData->stSpiData.ucState = SPI_STALLED_STATE;
            /*CONSOLE_MESSAGE("SPI state-machine state:%d", pstSampleAppData->stSpiData.ucState);*/
            return (E_OK);
        }
        /*break;*/

        case SPI_INITIAL_STATE:
        {
            CONSOLE_MESSAGE("SPI Error: SPI not initialized");
            /*CONSOLE_MESSAGE("SPI state-machine state:%d", pstSampleAppData->stSpiData.ucState);*/
            pstSampleAppData->stSpiData.ucState = SPI_ERROR_STATE;
            return (E_OK);
        }
        /*break;*/

        case SPI_ERROR_STATE:
        {
            /* we ended up in error - do nothing */
            return (E_OK);
        }
        /*break;*/

        case SPI_STALLED_STATE:
        {
            asm("nop");
            /*pstSampleAppData->stSpiData.ucState = SPI_INITIALIZED_STATE;*/
            return (E_OK);
        }
        /*break;*/

        default:
        {
            /* if we got here, something went terribly wrong*/
        }
        break;
    }

    return (E_NOT_OK);

}
/*================================================================================================*/
#ifdef DSPI_0_ENABLED
#if (DSPI_0_ENABLED == STD_OFF)
ISR(Spi_LLD_IsrEOQ_DSPI_0)
{
}
#endif
#endif

/*================================================================================================*/
#ifdef DSPI_1_ENABLED
#if (DSPI_1_ENABLED == STD_OFF)
ISR(Spi_LLD_IsrEOQ_DSPI_1)
{
}
#endif
#endif

/*================================================================================================*/
#ifdef DSPI_2_ENABLED
#if (DSPI_2_ENABLED == STD_OFF)
ISR(Spi_LLD_IsrEOQ_DSPI_2)
{
}
#endif
#endif

#endif /* (USE_SPI_MODULE==STD_ON) */
/*================================================================================================*/
/*================================================================================================*/
#ifdef __cplusplus
}
#endif
