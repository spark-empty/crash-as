/**************************************************************************************
* 
*   Freescale(TM) and the Freescale logo are trademarks of Freescale Semiconductor, Inc. 
*   All other product or service names are the property of their respective owners. 
*   (C) Freescale Semiconductor, Inc. 2006-2010
* 
*   You can use this example for any purpose on any computer system with the
*   following restrictions:
*
*   1. This example is provided "as is", without warranty.
*
*   2. You don't remove this copyright notice from this example or any direct derivation 
*      thereof.
*
*  Description:  AUTOSAR OS sample application
*
**************************************************************************************/

#include <os.h>                              /* OS API */

/* Global application data: */

unsigned short taskRcv1, taskRcv2, taskStop, pinState, repeatCnt;

#define APP_START_SEC_CODE
#include "MemMap.h"

/* Macro definitions for manipulations with GPIO */
/*  NOTE: GPIO190 is connected to LED3 on XPC56xx EVB motherboard */
#define BASE_ADDR       0xC3F90000
#define GPIO_NUM        190
#define REPEAT_CNT_MAX_VAL 5

#define SIU_PCRn  ( *(volatile unsigned short*)(BASE_ADDR+0x40+GPIO_NUM*2) )   /* Pad Configuration Register */
#define PCR        0x0200           /* PA = 0 - GPIO OBE = 1 - enable the pad group as outputs
                                                     IBE = 0 - disable the pad group as inputs */
#define SIU_GPIOn ( *(volatile unsigned char*)(BASE_ADDR+0x600+GPIO_NUM) )     /* Output-Only Data Value Out */

#define SetGPIO()   SIU_GPIOn = 0x1       /* set pin GPIO_NUM */
#define ClrGPIO()   SIU_GPIOn = 0x0       /* reset pin GPIO_NUM */

#define InitGPIO()      \
        SIU_PCRn = PCR; \
        ClrGPIO()
        
/***************************************************************************
 * Function:    main
 *
 * Description: inits variables and starts OS 
 *
 **************************************************************************/
void main( void )
{
    pinState = 0;
    ind = 0;
    repeatCnt = 0;
    taskRcv1 = 0;
    taskRcv2 = 0;
    taskStop = 0;
    taskSnd1 = 0;
    taskSnd2 = 0;
    taskCnt  = 0;
    StartOS( Mode01 );                            /* jump to OS startup */
}


/* Application Tasks: */

/***************************************************************************
 * Function:    TASKRCV1
 *
 * Description: Task reciever - is activated by start-up and delays itself 
 *
 * PROPERTIES:  priority = 5, Extended, preemptive, activated at start-up
 *
 **************************************************************************/

TASK( TASKRCV1 )
{
    volatile StatusType status;                 /* variable to check system status */
    EventMaskType event;                        /* variable for event masks */
    MSGATYPE Msg_A;                             /* object to recive message MsgA */

    InitGPIO();
    Msg_A.value = 0;
    StartCOM(ComAppMode);
    InitMessage(MsgAReceived, &Msg_A);                  /* set initial value    */

    for( ; ; )                                  /* main endless loop    */
    {
        DisableAllInterrupts();  /* to allow to use a breakepoint on next line */
        hookNmb = 0;
        EnableAllInterrupts();
        status = InitCounter( STCOUNTER, 0 );
        status = SetAbsAlarm( STOPALARM, 20, 0 );
        StartScheduleTableRel(SCHEDTAB, 1);

        for( ; ; )                                  
        {
            taskRcv1++;
            status = ClearEvent( MSGAEVENT | TIMLIMITEVENT );
            status = SetRelAlarm( TIMLIMITALARM, 125, 0 );
                                                    
            status = WaitEvent( MSGAEVENT | TIMLIMITEVENT );
        
            status = GetEvent( TASKRCV1, &event );

            if ( event == MSGAEVENT )
            {
                CancelAlarm( TIMLIMITALARM );
                status = GetResource( MSGAACCESS );
                status = ReceiveMessage( MsgAReceived, &Msg_A );    /* get message data */
                status = ReleaseResource( MSGAACCESS );
            }
            else                                    
            {
            	if( ++repeatCnt >= REPEAT_CNT_MAX_VAL )
                {
                    repeatCnt = 0;
                    pinState = !pinState;
                    if( pinState )
                    { 
                        SetGPIO(); 
                    }
                    else
                    { 
                        ClrGPIO(); 
                    }
                }
                break;
            }
        }

    }

}


/***************************************************************************
 * Function:    TASKRCV2
 *
 * Description: Task reciever - is activated by message B 
 *
 * PROPERTIES:   priority = 4, basic, preemptive
 *
 **************************************************************************/

TASK( TASKRCV2 )
{
    volatile StatusType status;
    MSGBTYPE Msg_B;

    taskRcv2++;
                                                /* GetResource to have exclusive access to the message */
    status = GetResource( MSGBACCESS );
                                                /* receive message */
    status = ReceiveMessage( MsgBReceived, &Msg_B );

    status = ReleaseResource( MSGBACCESS );
    status = TerminateTask( );
}

/***************************************************************************
 * Function:    TASKSTOP
 *
 * Description: Task  - terminate Time Scale processing
 *
 * PROPERTIES:   priority = 0, basic, preemptive
 *
 **************************************************************************/

TASK( TASKSTOP )
{
    volatile StatusType status;
    DisableAllInterrupts();
    taskStop++;
    EnableAllInterrupts();
    status = StopScheduleTable(SCHEDTAB);
    status = TerminateTask();
}


/***************************************************************************
 * Function:    ISR1
 *
 * Description: User's ISR
 *
 * PROPERTIES:  
 *
 **************************************************************************/
ISR( ISR1 )
{
}

#define APP_STOP_SEC_CODE
#include "MemMap.h"

