/**************************************************************************************
* 
*   Freescale(TM) and the Freescale logo are trademarks of Freescale Semiconductor, Inc. 
*   All other product or service names are the property of their respective owners. 
*   (C) Freescale Semiconductor, Inc. 2006-2009
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

#include    <os.h>                           /* OS API */

unsigned short ind, taskSnd1, taskSnd2, taskCnt;

/* User's hooks: */

int msgAnum;
int volatile hookNmb;                           /* to prevent hooks from linker optimization  */

#define OSHOOK_START_SEC_CODE
#include "memmap.h"

void    ErrorHook( StatusType Error )           /* Error handling routine   */
{
    hookNmb=1;
}

void    PreTaskHook( void )                     /* Routine to call before entering task context */
{
    hookNmb=2;
}

void    PostTaskHook( void )                    /* Routine to call after saving task context */
{
    hookNmb=3;
}

#define APP_START_SEC_CODE
#include "MemMap.h"

/* User's functions: */

/***************************************************************************
 * Function:    TASKSND1
 *
 * Description: Task sender - is activated by Time Scale
 *
 * PROPERTIES:  priority = 3, Basic, preemptive
 *
 **************************************************************************/

TASK( TASKSND1 )
{
    volatile StatusType status;                 /* variable to check system status */
    MSGATYPE Msg_A;                             /* message date */

    taskSnd1++;
                                                /* GetResource to access to message */
    status = GetResource( MSGAACCESS );         /* get resource */

    Msg_A.value=msgAnum++;                      /* modify MsgA  */
                                                
    status = SendMessage( MsgA, &Msg_A );       /* Send message A */

                                                /* Release Resource to access to message */
    status = ReleaseResource( MSGAACCESS );     /* release resource and terminate */
    status = TerminateTask( );
}

/***************************************************************************
 * Function:    TASKSND2
 *
 * Description: Task sender - is activated by Time Scale
 *
 * PROPERTIES:   priority = 2, Basic, preemptive
 *
 **************************************************************************/

TASK( TASKSND2 )
{
    static MSGBTYPE Msg_B;                      /* declare message MsgB */
    volatile StatusType status;                 /* variable to check system status */

    taskSnd2++;
                                                
    ind += 30;
    if( ind >= 50 )
    {
        ind -= 51;
        Msg_B.msg = ind+1000;                   /* just to have some data   */
        status = GetCounterValue( SYSTEMTIMER, &Msg_B.ts );
        status = GetResource( MSGBACCESS );     /* get resource */
                                                /* Send state message */
        status = SendMessage( MsgB, &Msg_B );
                                                /* Release Resource to access to message */
        status = ReleaseResource( MSGBACCESS ); /* release resource and terminate */
    }
    status = TerminateTask( );
}

/***************************************************************************
 * Function:    TASKCNT
 *
 * Description: Task - increment TSCOUNTER value
 *
 * PROPERTIES:  priority = 1, Basic, nonpreemptive
 *
 **************************************************************************/

TASK( TASKCNT )
{
    volatile StatusType status;                     /* variable to check system status */

    taskCnt++;

    status = IncrementCounter( STCOUNTER );
    status = TerminateTask( );
}

#define APP_STOP_SEC_CODE
#include "MemMap.h"
