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

#include <os.h>                           /* OS API */

/* Global 'send' application data */
#define SND_APP_START_SEC_VAR_FAST_16BIT
#include "MemMap.h"
volatile unsigned short ind, taskSnd1, taskSnd2, taskCnt;
#define SND_APP_STOP_SEC_VAR_FAST_16BIT
#include "MemMap.h"

#define SND_APP_START_SEC_VAR_FAST_32BIT
#include "MemMap.h"
    static int msgAnum;
#define SND_APP_STOP_SEC_VAR_FAST_32BIT
#include "MemMap.h"

#define SND_APP_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
    static MSGBTYPE Msg_B;                      /* declare message MsgB */
#define SND_APP_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"


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
  
    if( taskSnd2 == 22 )
    {
        for( ; ; );       /* endless loop shall cause timing violation */
    }

    if( taskSnd2 == 72 )
    {
        taskRcv1 = 101;   /* taskRcv belongs to another application, forces memory violation */
        for( ; ; );       /* never reached */
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
    IncrementCounter( STCOUNTER );
    status = TerminateTask( );
}

#define APP_STOP_SEC_CODE
#include "MemMap.h"
