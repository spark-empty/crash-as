/**
    @file        sample_app_mcal_initialization_task.c
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
#include "sample_app_mcal_initialization_task.h"

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

#define SIUL_PCR_OBE_MASK           (uint16)0x0200
#define SIUL_PCR_IBE_MASK           (uint16)0x0100

/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/
#if defined(AUTOSAR_OS_NOT_USED)
extern const vuint32_t IntcVectorTableHw[];
#endif

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
FUNC (void, SAMPLE_APP_CODE) SampleApp_Int_Init(void);


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

/**
@brief      SampleApp_Int_Init - Interrupt initialization
@details    This function is called at the initialization stage to setup interrupts priorities

@return     none
@retval     none

@pre None
@post None
*/
#if defined(AUTOSAR_OS_NOT_USED)
FUNC (void, SAMPLE_APP_CODE) SampleApp_Int_Init(void)
{
    /* Setup all the needed interrupts(and their priorities) */

    /* Gpt interrupts*/
    REG_WRITE8(INTC_PSR(301), 7);    /* PIT0 */

#if 0
    /* Wdg interrupts*/
    REG_WRITE8(INTC_PSR(8), 7);      /* Wdg_Isr */
#endif

    /* Adc Interrupts */
    REG_WRITE8(INTC_PSR(104), 7);    /* eQADC Command FIFO 0 Fill Flag */
    REG_WRITE8(INTC_PSR(105), 7);    /* eQADC Receive FIFO 0 Drain Flag */

    /* Pwm Interrupts */
    REG_WRITE8(INTC_PSR(60), 7);    /* eMIOS_0_9 */

    /* Icu Interrupts */
    REG_WRITE8(INTC_PSR(59), 7);    /* eMIOS_0_8 */

    /* SPI Interrupts */
    REG_WRITE8(INTC_PSR(132), 7);    /* DSPI1_EOQF */

    /* UART APP Interrupts */
    REG_WRITE8(INTC_PSR(146), 7);   /* eSCIA */

    /* LIN Interrupts */
    REG_WRITE8(INTC_PSR(149), 7);   /* eSCIB */

    /* Ensure INTC's current priority is 0 */
    /* INTC.CPR_PRC0.B.PRI = 0; */
    (*(volatile uint32*)(0xFFF48008))= (uint32)(0);

    /* Enable external interrupts */
    ASM_KEYWORD(" wrteei 1");
}
#endif

/**
@brief      SampleAppInitTask - Sample Application Initialization
@details    This function is called at the initialization stage to initialize all MCAL drivers

@return     Returns the value of success
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
FUNC (Std_ReturnType, SAMPLE_APP_CODE) SampleAppInitTask(P2VAR(SampleAppData_T, AUTOMATIC, SAMPLE_APP_VAR) pstSampleAppData)
{
    /* local variables here */
    Std_ReturnType stdRet = E_OK;
/******************************************************************************/
/* DEM                                                                        */
/******************************************************************************/
    Dem_ReportErrorStatus(0, 0);
    Dem_SetEventStatus(0, 0);

/******************************************************************************/
/* DET                                                                        */
/******************************************************************************/
    Det_Init();
    Det_ReportError(0, 0, 0, 0);
    Det_Start();

/******************************************************************************/
/* MCU                                                                        */
/******************************************************************************/
#if (USE_MCU_MODULE==STD_ON)
    Mcu_Init( &McuConfigPB_0 );
    stdRet = Mcu_InitClock(McuClockReferencePoin_0);
    if (stdRet != E_OK)
    {
        return (E_NOT_OK);
    }

/******************************************************************************/
/* PORT                                                                       */
/******************************************************************************/
#if (USE_PORT_MODULE==STD_ON)
    Port_Init(&PortConfigSet_0);
#endif

/******************************************************************************/
/* ECUM                                                                       */
/******************************************************************************/
    EcuM_SetWakeupEvent(0);
    EcuM_ValidateWakeupEvent(0);
    EcuM_CheckWakeup(0);

/******************************************************************************/
/* FEE                                                                        */
/******************************************************************************/
#if (USE_FEE_MODULE==STD_ON)
    stdRet = SampleAppFeeInit(pstSampleAppData);
#endif

    while (Mcu_GetPllStatus() != MCU_PLL_LOCKED)
    {
    }

    Mcu_DistributePllClock();
#endif

/******************************************************************************/
/* Init uart console                                                          */
/******************************************************************************/
uart_console_init();

/******************************************************************************/
/* ADC                                                                        */
/******************************************************************************/
#if (USE_ADC_MODULE==STD_ON)
    stdRet = SampleAppAdcInit(pstSampleAppData);
    if (stdRet != E_OK)
    {
        return (E_NOT_OK);
    }
#endif

/******************************************************************************/
/* CAN                                                                        */
/******************************************************************************/
#if (USE_CAN_MODULE==STD_ON)
    stdRet = SampleAppCanInit(pstSampleAppData);
#endif

/******************************************************************************/
/* DIO                                                                        */
/******************************************************************************/
#if (USE_DIO_MODULE==STD_ON)
#endif

/******************************************************************************/
/* FLS                                                                        */
/******************************************************************************/
#if (USE_FLS_MODULE==STD_ON)
#endif

/******************************************************************************/
/* FR                                                                        */
/******************************************************************************/
#if (USE_FR_MODULE==STD_ON)
    stdRet = SampleAppFrInit(pstSampleAppData);
#endif

/******************************************************************************/
/* LIN                                                                        */
/******************************************************************************/
#if (USE_LIN_MODULE==STD_ON)
    stdRet = SampleAppLinInit(pstSampleAppData);
#endif

/******************************************************************************/
/* GPT                                                                        */
/******************************************************************************/
#if (USE_GPT_MODULE==STD_ON)
    Gpt_Init(&GptChannelConfigSet_0);
#endif

/******************************************************************************/
/* ICU                                                                        */
/******************************************************************************/
#if (USE_ICU_MODULE==STD_ON)
    stdRet = SampleAppIcuInit(pstSampleAppData);
    if (stdRet != E_OK)
    {
        return (E_NOT_OK);
    }
#endif

/******************************************************************************/
/* SPI                                                                        */
/******************************************************************************/
#if (USE_SPI_MODULE==STD_ON)
    stdRet = SampleAppSpiInit(pstSampleAppData);
    if (stdRet != E_OK)
    {
        return (E_NOT_OK);
    }
#endif

/******************************************************************************/
/* PWM                                                                        */
/******************************************************************************/
#if (USE_PWM_MODULE==STD_ON)
    stdRet = SampleAppPwmInit(pstSampleAppData);
    if (stdRet != E_OK)
    {
        return (E_NOT_OK);
    }
#endif

#if defined(AUTOSAR_OS_NOT_USED)
/******************************************************************************/
/* Init interrupts                                                            */
/******************************************************************************/
    SampleApp_Int_Init();
#endif

    CONSOLE_MESSAGE("\n!!!MCAL INTEGRATION APPLICATION!!!\n");

    return (E_OK);
}
/*================================================================================================*/

#ifdef __cplusplus
}
#endif
