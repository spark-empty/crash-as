/**
    @file        main.c
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
#include "typedefs.h"

#include "sample_app_mcal_uart_console.h"
#include "sample_app_mcal_data_definition.h"
#include "sample_app_mcal_initialization_task.h"
#include "sample_app_mcal_task_1.h"
#include "sample_app_mcal_task_2.h"
#include "sample_app_mcal_task_3.h"
#include "Mcal.h"


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


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/

/**
@brief This is the global variable that holds all the sample app specific data
*/

extern volatile SampleAppData_T  stSampleAppData;
static SampleAppData_T * p_stSampleAppData = (SampleAppData_T *)&stSampleAppData;

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
@brief   Main function of the sample application using Leds.
@details The sample configures the processor and uses leds and keys from the mainboard the following way:
                LED1 - Ligth intensity controlled by Potetiometer
                LED2 - Wil stay ON while Key1 is pressed and will go OFF when watchdog will run out
                LED3 - Blinking drived by GPT
                LED4 - Always ON
                KEY1 - disable watchdog and switch on the LED2
          The function will never return.
@return Returns ok
@retval 0 - Ok
@pre None
@post None
*/
int main( )
{
#if defined(AUTOSAR_OS_NOT_USED)
    Std_ReturnType ret = E_OK;
    uint32 task;
#endif  /* AUTOSAR_OS_NOT_USED */
    /* OS/stand-alone initialization - prepare the tasks(for OS), or the threads when no OS is used(uses Timers) */


/******************************************************************************/
/* WDG                                                                        */
/******************************************************************************/
#if (USE_WDG_MODULE==STD_ON)
    /* SIU.DIRER.B.NMISEL0 = 1; */
    (*(volatile uint32*)(0xC3F90000 + 0x18)) |= (uint32)(0x00800000);

    Wdg_Init(&WdgModeConfig);
    Wdg_SetMode(WDGIF_OFF_MODE);
#endif

#if defined(AUTOSAR_OS_NOT_USED)

    /* call Initialization task */
    ret = SampleAppInitTask( p_stSampleAppData );

    task = 1;

    while(E_OK == ret)
    {
        switch(task)
        {
            case 1:
            {
                /* call Task 1 */
                ret = SampleAppTask1( p_stSampleAppData );
                break;
            };

            case 2:
            {
                /* call Task 2 */
                ret = SampleAppTask2( p_stSampleAppData );
                break;
            };

            case 3:
            {
                /* call Task 3 */
                ret = SampleAppTask3( p_stSampleAppData );
                break;
            };

            default:
            {
                task = 0;
                break;
            };

        }

        task++;

#if (USE_FEE_MODULE == STD_ON)
        Fee_MainFunction();
#endif
#if (USE_FLS_MODULE == STD_ON)
        Fls_MainFunction();
#endif
        /* switch context when a task returns or within the timer ISR */
    }
    CONSOLE_FLUSH();
#else
    StartOS(Mode01);
#endif
    return 0;
}

#ifndef AUTOSAR_OS_NOT_USED

/****************************************************************************
 * Hooks (Remember to activate these in the ProOSEK configurator if desired!)
 ****************************************************************************/

void StartupHook(void)
{
    /* can be used to do some initialization before the first task runs */
    /* call Initialization task */
    SampleAppInitTask( p_stSampleAppData );
}


void ErrorHook(StatusType myError)
{
    if (myError == E_OS_LIMIT) return; /* Can happen after debugger break */
    ShutdownOS(myError);
}

TASK(LoopTask)
{
    while(1)
    {
#if (USE_FEE_MODULE == STD_ON)  && (USE_FLS_MODULE == STD_ON)

        if (FEE_FINAL_STATE != stSampleAppData.stFeeData.ucState)
        {
            MemIf_StatusType memif_status;

            memif_status = Fee_GetStatus();
            if (MEMIF_IDLE != memif_status)
            {
                Fee_MainFunction();
            }

            memif_status = Fls_GetStatus();
            if (MEMIF_IDLE != memif_status)
            {
                Fls_MainFunction();
            }
        }
        else
#endif  /*USE_FEE_MODULE && USE_FLS_MODULE */
        {
            (void)TerminateTask();
        }
    }
}

TASK(TASK1)
{
     while(1)
    {
        ClearEvent(OsEvent_Task1);
        SampleAppTask1( p_stSampleAppData );
        WaitEvent(OsEvent_Task1);
    }
}
TASK(TASK2)
{
    while(1)
    {
        ClearEvent(OsEvent_Task2);
        SampleAppTask2( p_stSampleAppData );
        WaitEvent(OsEvent_Task2);
    }
}
TASK(TASK3)
{
    while(1)
    {
        ClearEvent(OsEvent_Task3);
        SampleAppTask3( p_stSampleAppData );
        WaitEvent(OsEvent_Task3);
    }
}
#endif

#ifdef __cplusplus
}
#endif
