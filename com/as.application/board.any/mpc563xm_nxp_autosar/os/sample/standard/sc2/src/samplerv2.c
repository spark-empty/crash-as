/******************************************************************************
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
* Description:  AUTOSAR OS sample application
*
* Notes:        
*
******************************************************************************/

#include <os.h>                              /* OS API */

unsigned short taskRcv1, taskRcv2, taskStop;


/* Macro definitions for manipulations with GPIO */
/*  NOTE: GPIO188 is connected to LED1 on XPC56xx EVB motherboard */
#define BASE_ADDR       0xC3F90000
#define GPIO_NUM        188

#define SIU_PCRn  ( *(volatile unsigned short*)(BASE_ADDR+0x40+GPIO_NUM*2) )   /* Pad Configuration Register */
#define PCR        0x0200           /* PA = 0 - GPIO OBE = 1 - enable the pad group as outputs
                                                     IBE = 0 - disable the pad group as inputs */
#define SIU_GPIOn ( *(volatile unsigned char*)(BASE_ADDR+0x600+GPIO_NUM) )     /* Output-Only Data Value Out */

#define InitGPIO()      \
        SIU_PCRn = PCR; \
        SIU_GPIOn = 0x1


#define OSHOOK_START_SEC_CODE
#include "memmap.h"

/***************************************************************************
 * Function:    ProtectionHook
 *
 * Description:  The protection hook is always called if a serious error occurs 
 *
 **************************************************************************/
ProtectionReturnType ProtectionHook( StatusType FatalError )
{
    volatile StatusType err;

    if( OsViolatorTaskId != TASKRCV1 )
    {
        err = E_OS_SYS_FATAL;
        return( PRO_SHUTDOWN );
    }
    /********
    switch( Fatalerror ) {
    case E_OS_PROTECTION_MEMORY:
    case E_OS_PROTECTION_TIME:
    case E_OS_PROTECTION_LOCKED:
    case E_OS_PROTECTION_EXCEPTION:
    case E_OS_PROTECTION_RATE:
    default:
        break;
    }
    ********/
    err = FatalError;
    
    SIU_GPIOn = 0x0;	/* LED1 ON */
    
    return( PRO_SHUTDOWN );
}

#define APP_START_SEC_CODE
#include "MemMap.h"

/***************************************************************************
 * Function:    main
 *
 * Description: inits variables and starts OS 
 *
 **************************************************************************/

void main( void )
{
    ind      = 0;
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
    static OSDWORD repeat;                      /* number of iteration */
    volatile StatusType status;                 /* variable to check system status */
    EventMaskType event;                        /* variable for event masks */
    MSGATYPE Msg_A;                             /* object to recive message MsgA */

    InitGPIO();
    repeat = 0;
    Msg_A.value = 0;
    StartCOM(ComAppMode);
    InitMessage(MsgAReceived, &Msg_A);            /* set initial value    */

    for( ; ; )                                  /* main endless loop    */
    {
        DisableAllInterrupts();  /* to stop 2nd Timer and allow to use a breakepoint on next line */
        taskRcv1++;
        EnableAllInterrupts();

        status = InitCounter( STCOUNTER, 0 );
        status = SetAbsAlarm( STOPALARM, 10, 0 );
        status = StartScheduleTableRel( SCHEDTAB, 1 );

        for( ; ; )                                  
        {
            status = ClearEvent( MSGAEVENT | TIMLIMITEVENT );
            status = SetRelAlarm( TIMLIMITALARM, 125, 0 );
                                                    
            status = WaitEvent( MSGAEVENT | TIMLIMITEVENT );
        
            status = GetEvent( TASKRCV1, &event );

            if ( event == MSGAEVENT )
            {
                status = CancelAlarm( TIMLIMITALARM );
                status = GetResource( MSGAACCESS );
                status = ReceiveMessage( MsgAReceived, &Msg_A );    /* get message data */
                status = ReleaseResource( MSGAACCESS );
            }
            else                                    
            {
                if( ++repeat >= 5 )
                {
                    for( ; ; );  /* forced timing protection, see ProtectionHook. */
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
                                                /* GetResource to have exclusive access to the message */
    taskRcv2++;

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
    DisableAllInterrupts();  /* to stop 2nd Timer and allow to use a breakepoint on next line */
    taskStop ++;
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
