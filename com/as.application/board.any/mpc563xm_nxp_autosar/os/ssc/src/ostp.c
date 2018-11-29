#define OSTP_V3_C
/******************************************************************************
*
*   Freescale(TM) and the Freescale logo are trademarks of Freescale Semiconductor, Inc. 
*   All other product or service names are the property of their respective owners. 
*   (C) Freescale Semiconductor, Inc. 2006-2010
*
*   THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
*   BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
*   Freescale Semiconductor, Inc.
*
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/src/ostp.c,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  timing protection
*
* Notes: Configuration macros:
*    OSNTPBGTS           - number of tasks and ISRs with execution budget
*    OSNTPTSKBGTS        - number of tasks with execution budget
*    OSNTPISRBGTS        - number of ISR2s with execution budget
*    OSNTPTSKARRIV       - number of tasks with ISR arrival rate
*    OSNTPISRARRIV       - number of ISR2s with ISR arrival rate
*    OSNTPTSKINTLOCKTIME - number of tasks with OS interrupt locking Time
*    OSNTPISRINTLOCKTIME - number of ISR2s with OS interrupt locking Time
*    OSNTPTSKRESLOCKTIME - number of tasks with at least one resource locking Time
*    OSNTPISRRESLOCKTIME - number of ISR2s with at least one resource locking Time
*    OSNTPTSKRESLOCKS    - number of all resource locking time configurations for tasks
*    OSNTPISRRESLOCKS    - number of all resource locking time configurations for ISRs
*
******************************************************************************/

#define OS_INTERNAL 1
#include    <os.h>
#undef OS_INTERNAL

#if defined(OSTIMINGPROTECTION)

#include <string.h>

#define OSTEXT_START_SEC_CODE
#include "ossections.h"

#if defined(OSHOOKPROTECTION)
/* Prototypes */
void OSTPKillObjects( ProtectionReturnType action, StatusType err );
ProtectionReturnType OSTPProtectionHook( OSObjectType object, StatusType err );
#endif

/***************************************************************************
 * Function:    OSTPInitializeTP
 *
 * Description: initialize TP HW and start timer
 *
 * Returns: 
 *
 * Notes:
 *
 **************************************************************************/

#if(OSNAPPMODES > 1)
void OSInitializeTP( AppModeType mode )
#else
void OSInitializeTP( void )
#endif
{
#if (OSNTPTSKRESLOCKTIME > 0) || (OSNTPISRRESLOCKTIME > 0)
    OSTPRESLOCK* tpResLock;
#endif
    OSCARDINAL  i;
#if  (OSNTPTSKARRIV > 0) || (OSNTPISRARRIV > 0)
    OSSIGNEDQWORD curTime;
#endif

#if (OSNTPBGTS > 0) 
    OsTPBudgetObject = OSTPOBJECT0;
#endif
#if (OSNTPTSKINTLOCKTIME >0) || (OSNTPISRINTLOCKTIME > 0)
    OsTPIntLockObject = OSTPOBJECT0;
#endif
#if (OSNTPTSKRESLOCKTIME >0) || (OSNTPISRRESLOCKTIME > 0)
    OsTPResLockObject = OSTPOBJECT0;
#endif

    OSTPTimerInit();    /* init TP HW */
    OsTPForceReason = 0;
#if (OSNTPISRARRIV > 0) || (OSNTPTSKARRIV > 0)
    OsTPOverflowCnt = 0;
#endif

#if  (OSNTPTSKARRIV > 0) || (OSNTPISRARRIV > 0)
    OsTPTimVal = OSTPGetTimVal();
    OSTPGetTime64(curTime);             /* get current TP time counter */
#endif

    /* Init TP for tasks */
#if (OSNTPTSKRESLOCKTIME > 0) || (OSNTPTSKBGTS > 0) || (OSNTPTSKARRIV > 0) || (OSNTPTSKINTLOCKTIME > 0)
    {
        OSTSKCBPTR   task;
        const OSTSK* task_cfg;

#if (OSNTPTSKRESLOCKTIME > 0)
        tpResLock = &OsTPTskResLockTime[0];
#endif
        for( i = 0; i < OSNTSKS; i++ )
        {
            task     = &(OsTaskTable[i]);
            task_cfg = &(OsTaskCfgTable[i]);
#if (OSNTPTSKBGTS > 0) 
            task->tpExecBudget = task_cfg->tpExecBudget;
            task->tpRemained = task->tpExecBudget;
#endif
#if  (OSNTPTSKARRIV > 0) 
            task->tpTimeFrame = task_cfg->tpTimeFrame;
#endif 
#if (OSNTPTSKINTLOCKTIME > 0)
            task->tpIntLockTime = task_cfg->tpIntLockTime;
#endif
#if (OSNTPTSKRESLOCKTIME > 0)
            task->tpResources = OSNULLRES;
            task->tpNumberResLock = task_cfg->tpNumberResLock;
            task->tpResLock = tpResLock;
            memcpy( tpResLock, task_cfg->tpResLock, sizeof(*tpResLock) * task->tpNumberResLock );
            tpResLock += task->tpNumberResLock;
#endif

            /* Start TP for the  auto-startup tasks  */
#if (OSNTPTSKARRIV > 0) 
#if (OSNAPPMODES > 1)
            if( ( task_cfg->autostart & ( 1 << mode ) ) != 0 )
#else
            if( ( task_cfg->property & OSTSKACTIVATE ) != 0 ) 
#endif
            {
                /* Start TP for the task */
                task->tpLast = curTime;
            }
            else
            {
                /* Reset inter-arrival protection for the task */
                task->tpLast = curTime - ((OSSIGNEDQWORD)task->tpTimeFrame);
            }
#endif /* (OSNTPTSKARRIV > 0) */
        }

        /* NULLTASK initialization */
        task  = &(OsTaskTable[OSNTSKS]);
#if (OSNTPTSKBGTS > 0) 
        task->tpExecBudget = 0;
#endif
#if (OSNTPTSKARRIV > 0) 
        task->tpTimeFrame = 0;
#endif 
#if (OSNTPTSKINTLOCKTIME > 0)
        task->tpIntLockTime =0;
#endif
#if (OSNTPTSKRESLOCKTIME > 0)
        task->tpNumberResLock = 0;
        task->tpResources = OSNULLRES;
#endif
    }
#endif /* (OSNTPTSKRESLOCKTIME > 0) || (OSNTPTSKBGTS > 0) || (OSNTPTSKARRIV > 0) || (OSNTPTSKINTLOCKTIME > 0) */


    /* Init TP for ISR2s */
#if (OSNTPISRRESLOCKTIME > 0) || (OSNTPISRBGTS > 0) || (OSNTPISRARRIV > 0) || (OSNTPISRINTLOCKTIME > 0)
    {
        const OSISRCFGTYPE      *isrCfgPtr;
        OS_ISRTYPE              *isrTablePtr;

#if (OSNTPISRRESLOCKTIME > 0)
        tpResLock = &OsTPISRResLockTime[0];
#endif
        isrCfgPtr = &(OsIsrCfg[0]);
        isrTablePtr = &(OsIsrTable[0]);

        for( i = 0; i < OSNISR+1; ++i, ++isrCfgPtr, ++isrTablePtr )
        {
#if (OSNTPISRBGTS > 0) 
            isrTablePtr->tpExecBudget = isrCfgPtr->tpExecBudget;
#endif
#if (OSNTPISRARRIV > 0) 
            isrTablePtr->tpTimeFrame = isrCfgPtr->tpTimeFrame;
            isrTablePtr->tpLast = curTime - isrTablePtr->tpTimeFrame;
#endif 
#if (OSNTPISRINTLOCKTIME > 0)
            isrTablePtr->tpIntLockTime = isrCfgPtr->tpIntLockTime;
#endif
#if (OSNTPISRRESLOCKTIME > 0)
            isrTablePtr->tpNumberResLock = isrCfgPtr->tpNumberResLock;
            isrTablePtr->tpResLock = tpResLock;
            memcpy( tpResLock, isrCfgPtr->tpResLock, sizeof(*tpResLock) * isrTablePtr->tpNumberResLock );
            tpResLock += isrTablePtr->tpNumberResLock;
#endif
        }
    }
#endif /* (OSNTPISRRESLOCKTIME > 0) || (OSNTPISRBGTS > 0) || (OSNTPISRARRIV > 0) || (OSNTPISRINTLOCKTIME > 0) */
}

#if defined(OSHOOKPROTECTION)
/***************************************************************************
 * Function:    OSTPProtectionHook
 *
 * Description: determines violator object and calls the user protection hook
 *
 * Returns:  the action desired by user
 *
 * Notes:
 ***************************************************************************/

ProtectionReturnType OSTPProtectionHook( OSObjectType object, StatusType err )
{
    ProtectionReturnType action;
#if !defined(OSNOISR2)
    OSWORD isrId;
#endif

    if( object != OSTPOBJECT0 )
    {
#if !defined(OSNOISR2)
        if( OSTP_GETOBJTYP(object) == OBJECT_ISR )
        {
            isrId = OSTP_GETOBJIND(object);
            OsViolatorISRId = OS_MKOBJID(OBJECT_ISR, isrId);
#if defined(OSAPPLICATION)
            OsViolatorAppId = OsIsrTable[isrId].appId;
#endif
            OsViolatorTaskId = INVALID_TASK;
        }
        else 
#endif /* !defined(OSNOISR2) */
        {
            OsViolatorTaskId = OS_MKOBJID(OBJECT_TASK, OSTP_GETOBJIND(object));
#if defined(OSAPPLICATION)
            OsViolatorAppId = OsTaskTable[ OSTP_GETOBJIND(object) ].appId;
#endif
            OsViolatorISRId = INVALID_ISR;
        }
    }
    else
    {
        /* This situation is possible if OSTPProtectionHook is called from a alarm action */
        OsViolatorTaskId = INVALID_TASK;
        OsViolatorISRId = INVALID_ISR;
#if defined(OSAPPLICATION)
        OsViolatorAppId = INVALID_OSAPPLICATION;
#endif
    }

    OSOrtiSetServiceWatch( OSServiceId_ProtectionHook );    /* set watch to this service */ 
    OSSETPROTCNXT();
    action = ProtectionHook( err );
    OSCLRPROTCNTX();
    OSOrtiServiceWatchOnExit( OSServiceId_ProtectionHook ); /* clear service watch on hook leaving */ 

    return action;
}

/***************************************************************************
 * Function:    OSTPKillObjects
 *
 * Description: terminates some runables under the action desired by the user
 *
 * Returns:  
 *
 * Notes:  it shall be used only in TP interrupts
 ***************************************************************************/

void OSTPKillObjects( ProtectionReturnType action, StatusType err )
{
#if defined(OSAPPLICATION)
    RestartType restart = RESTART;
#endif

    switch( action ) 
    {        
    case PRO_TERMINATETASKISR:
#if !defined(OSNOISR2)
        if( OsViolatorISRId != INVALID_ISR ) 
        {
            OSWORD isrId = OS_GETOBJIND(OsViolatorISRId);
            
#if defined(OSAPPLICATION)
#if (OSNTRUSTEDFUNCTIONS > 0)           /* restore appId in case it has been changed */
            OsIsrTable[ isrId ].appId = OsIsrCfg[ isrId ].appId;
#endif
#endif
#if (OSNTPISRARRIV > 0)
            if( err != E_OS_PROTECTION_ISR_ARRIVAL )
#endif
            {
                OSKillISR( &OsIsrTable[ isrId ] );
            }
            /* else
                nothing to do because of user's ISR has not been called actually 
            */
        }
        else 
#endif /* !defined(OSNOISR2) */
        {
            OSKillTask( &OsTaskTable[ OS_GETOBJIND(OsViolatorTaskId) ] );
        }

        break;

    case PRO_TERMINATEAPPL:
#if defined(OSAPPLICATION)
        restart = NO_RESTART;   /* no break */
#endif
    case PRO_TERMINATEAPPL_RESTART:
#if defined(OSAPPLICATION)
    {
        OSBYTE tmp = OSGetCurApp();
        OSSetCurApp(OsViolatorAppId);   /* OSTerminateApplication will terminate the violator application */ 
        if( OSTerminateApplication(restart) )
        {
            OSSetCurApp(tmp);   /* restore the application Id */
            break;
        }
    }
    /* No break. ShutdownOS() shall be called */
#endif
    case PRO_IGNORE:    /* OSTPKillObjects cannot be called if the
                           action=PRO_IGNORE and err=E_OS_PROTECTION_ARRIVAL 
                           (see OSTPStartTaskFrame or OSTPISRArrivalRate).
                           And so ShutdownOS shall be called here (OS475) */
    case PRO_SHUTDOWN:        
    default:
#if (OSNTPISRARRIV > 0)
        if( err == E_OS_PROTECTION_ISR_ARRIVAL )
        {
            err = E_OS_PROTECTION_ARRIVAL;
        }
#endif
        OSShutdownOS( err );
    }
}

/***************************************************************************
 * Function:    OSTPHandler
 *
 * Description: Handler of timing protection violation
 *
 * Returns: 
 *
 * Notes:  it shall be used only in TP interrupts
 ***************************************************************************/

#if (OSNTPBGTS > 0) ||            \
    ((OSNTPTSKINTLOCKTIME > 0) || \
     (OSNTPISRINTLOCKTIME > 0) || \
     (OSNTPTSKRESLOCKTIME > 0) || \
     (OSNTPISRRESLOCKTIME > 0))
OSINLINE void OSTPHandler( OSObjectType object, StatusType err )
{
    OSTPKillObjects( OSTPProtectionHook( object, err ), err );
}
#endif

#endif /* defined(OSHOOKPROTECTION) */

#if defined(OSTPSTM123)
#if (OSNTPBGTS > 0) ||            \
    ((OSNTPTSKINTLOCKTIME > 0) || \
     (OSNTPISRINTLOCKTIME > 0) || \
     (OSNTPTSKRESLOCKTIME > 0) || \
     (OSNTPISRRESLOCKTIME > 0))
/***************************************************************************
 * Function:    OSISRTPViolation 
 *
 * Description: OSMPC5674F interrupt handler for 'budget','interrupt locking time',
 *              'resource locking time' STM channels are shared to common node
 *
 * Returns: 
 *
 * Notes: 
 *
 **************************************************************************/
void OSISRTPViolation( void )
{
#if defined(OSHOOKPROTECTION)
#if (OSNTPBGTS > 0)
    if( OSTPTimerInterruptRaised(OSTPCH_BUDGET) )
    {
        OSEHI();
        OSTPHandler( OsTPBudgetObject, E_OS_PROTECTION_TIME );
        OSTPTimerClearFlag( OSTPCH_BUDGET );
    }
#endif /* (OSNTPBGTS > 0) */
#if (OSNTPTSKINTLOCKTIME > 0) || (OSNTPISRINTLOCKTIME > 0)
#if (OSNTPBGTS > 0)
    else
#endif
    if ( OSTPTimerInterruptRaised(OSTPCH_INTLOCK) )
    {
        OSEHI();
        OSTPTimerClearFlag( OSTPCH_INTLOCK );
        OSTPHandler( OsTPIntLockObject, E_OS_PROTECTION_LOCKED );
    }
#endif /* (OSNTPTSKINTLOCKTIME > 0) || (OSNTPISRINTLOCKTIME > 0) */
#if (OSNTPTSKRESLOCKTIME > 0) || (OSNTPISRRESLOCKTIME > 0) 
#if (OSNTPBGTS > 0) || (OSNTPTSKINTLOCKTIME > 0) || (OSNTPISRINTLOCKTIME > 0)
    else
#endif
    if( OSTPTimerInterruptRaised(OSTPCH_RESLOCK) )
    {
        OSEHI();
        OSTPHandler( OsTPResLockObject, E_OS_PROTECTION_LOCKED );
        OSTPTimerClearFlag( OSTPCH_RESLOCK );
    }
#endif /* (OSNTPTSKRESLOCKTIME > 0) || (OSNTPISRRESLOCKTIME > 0) */
    else
    {
        /* Note: It is a workaround for known INTC defect. */
    	return;
    }
    OSDHI(); 
    OSTPLeaveISR(); 
#else
    OSShutdownOS( E_OS_PROTECTION_TIME );
#endif /* defined(OSHOOKPROTECTION) */
}
#endif
#endif /* defined(OSTPSTM123) */

#if !defined(OSTPSTM123)

#if (OSNTPBGTS > 0)
/***************************************************************************
 * Function:    OSISRTPTimerBudget 
 *
 * Description: Interrupt handler for 'budget' STM channel 
 *
 * Returns: 
 *
 * Notes: 
 *
 **************************************************************************/

void OSISRTPTimerBudget( void )
{
#if defined(OSHOOKPROTECTION)
    if( !OSTPTimerInterruptRaised(OSTPCH_BUDGET) )             
    {
        /* Note: It is a workaround for known INTC defect. The
                 situation is possible when TP interrupt is cleared by
                 StopBudget() but nevertheless this interrupt is
                 latched and ocurrs after OSEHI() */
        return;
    }
    OSEHI();
    OSTPHandler( OsTPBudgetObject, E_OS_PROTECTION_TIME );
    OSTPTimerClearFlag( OSTPCH_BUDGET );

    OSDHI(); 
    OSTPLeaveISR(); 
#else
    OSTPTimerClearFlag( OSTPCH_BUDGET );
    OSShutdownOS( E_OS_PROTECTION_TIME );
#endif /* defined(OSHOOKPROTECTION) */
}
#endif /* (OSNTPBGTS > 0) */

#if (OSNTPTSKINTLOCKTIME > 0) || (OSNTPISRINTLOCKTIME > 0)
/***************************************************************************
 * Function:    OSISRTPTimerIntLock
 *
 * Description: Interrupt handler for 'interrupt locking time' STM channel 
 *
 * Returns: 
 *
 * Notes: 
 *
 **************************************************************************/

void OSISRTPTimerIntLock( void )
{
#if defined(OSHOOKPROTECTION)
    OSEHI();
    OSTPTimerClearFlag( OSTPCH_INTLOCK );
    OSTPHandler( OsTPIntLockObject, E_OS_PROTECTION_LOCKED );
    OSDHI(); 
    OSTPLeaveISR(); 
#else
    OSTPTimerClearFlag( OSTPCH_INTLOCK );
    OSShutdownOS( E_OS_PROTECTION_LOCKED );
#endif /* defined(OSHOOKPROTECTION) */
}

#endif /* (OSNTPTSKINTLOCKTIME > 0) || (OSNTPISRINTLOCKTIME > 0) */


#if (OSNTPTSKRESLOCKTIME > 0) || (OSNTPISRRESLOCKTIME > 0) 
/***************************************************************************
 * Function:    OSISRTPTimerResLock
 *
 * Description: Interrupt handler for 'resource locking time' STM channel 
 *
 * Returns: 
 *
 * Notes: 
 *
 **************************************************************************/

void OSISRTPTimerResLock( void )
{
#if defined(OSHOOKPROTECTION)
    if( !OSTPTimerInterruptRaised(OSTPCH_RESLOCK) )             
    {
        /* Note: It is a workaround for known INTC defect. The
                 situation is possible when TP interrupt is cleared by
                 StopBudget() but nevertheless this interrupt is
                 latched and ocurrs after OSEHI() */
        return;
    }
    OSEHI();
    OSTPHandler( OsTPResLockObject, E_OS_PROTECTION_LOCKED );
    OSTPTimerClearFlag( OSTPCH_RESLOCK );
    OSDHI(); 
    OSTPLeaveISR(); 
#else
    OSTPTimerClearFlag( OSTPCH_RESLOCK );
    OSShutdownOS( E_OS_PROTECTION_LOCKED );
#endif /* defined(OSHOOKPROTECTION) */
}

#endif /* (OSNTPTSKRESLOCKTIME > 0) || (OSNTPISRRESLOCKTIME > 0) */
#endif /* !defined(OSTPSTM123) */

/***************************************************************************
 * Function:    OSISRTPForced
 *
 * Description: Force TP handler
 *
 * Returns: 
 *
 * Notes:
 *
 **************************************************************************/

void OSISRTPForced( void )
{
#if defined(OSHOOKPROTECTION)
    OSEHI();
    OSTPTimerForceClearFlag();

#if (OSNTPBGTS > 0) 
    if( (OsTPForceReason & OSTPFORCEBUDGET) != 0 )
    {
        OsTPForceReason &= ~OSTPFORCEBUDGET;
        OSTPHandler( OsTPBudgetObject, E_OS_PROTECTION_TIME );
    }
#endif

#if (OSNTPTSKINTLOCKTIME > 0) || (OSNTPISRINTLOCKTIME > 0)
    if( (OsTPForceReason & OSTPFORCEINTLOCK) != 0 )
    {
        OsTPForceReason &= ~OSTPFORCEINTLOCK;
        OSTPHandler( OsTPIntLockObject, E_OS_PROTECTION_LOCKED );
    }
#endif

#if (OSNTPTSKRESLOCKTIME > 0) || (OSNTPISRRESLOCKTIME > 0)
    if( (OsTPForceReason & OSTPFORCERESLOCK) != 0 )
    {
        OsTPForceReason &= ~OSTPFORCERESLOCK;
        OSTPHandler( OsTPResLockObject, E_OS_PROTECTION_LOCKED );
    }
#endif

#if (OSNTPTSKARRIV > 0) 
    if( (OsTPForceReason & OSTPFORCETSKARRIVAL) != 0 )
    {
        OsTPForceReason &= ~OSTPFORCETSKARRIVAL;
        /* OSTPProtectionHook was called before */ 
        OSTPKillObjects( OsTPHookAction, E_OS_PROTECTION_ARRIVAL);
    }
#endif

#if (OSNTPISRARRIV > 0)
    if( (OsTPForceReason & OSTPFORCEISRARRIVAL) != 0 )
    {
        OsTPForceReason &= ~OSTPFORCEISRARRIVAL;
        /* OSTPProtectionHook was called before */ 
        OSTPKillObjects( OsTPHookAction, E_OS_PROTECTION_ISR_ARRIVAL );
    }
#endif

    OSDHI(); 
    OSTPLeaveISR(); 

#else  /* defined(OSHOOKPROTECTION) */

    StatusType err;

    OSTPTimerForceClearFlag();

    err = E_OS_SYS_FATAL;

#if (OSNTPBGTS > 0) 
    if( (OsTPForceReason & OSTPFORCEBUDGET) != 0 )
    {
        err = E_OS_PROTECTION_TIME;
    }
#endif

#if (OSNTPTSKINTLOCKTIME > 0) || (OSNTPISRINTLOCKTIME > 0)
    if( (OsTPForceReason & OSTPFORCEINTLOCK) != 0 )
    {
        err = E_OS_PROTECTION_LOCKED;
    }
#endif

#if (OSNTPTSKRESLOCKTIME > 0) || (OSNTPISRRESLOCKTIME > 0)
    if( (OsTPForceReason & OSTPFORCERESLOCK) != 0 )
    {
        err = E_OS_PROTECTION_LOCKED;
    }
#endif

    /* TASK/ISR2 inter-arrival rate is handled in OSTPStart(Task/ISR)Budget() */

    OSShutdownOS( err );
#endif  /* defined(OSHOOKPROTECTION) */
}

#if (OSNTPISRARRIV > 0) || (OSNTPTSKARRIV > 0)
/***************************************************************************
 * Function:    OSISRTPTimerOVF
 *
 * Description: Interrupt handler for 'overflow' STM channel 
 *
 * Returns: 
 *
 * Notes:
 *
 **************************************************************************/

void OSISRTPTimerOVF( void )
{
    OsTPOverflowCnt++;
    
#if (OSTPTIMPRESCALER > 64)
    /* It's a workaround for "STM issue on clearing the CIF flag" (FSL_9000_500) in errata for Bolero/Monaco */
    do{
#endif

        OSTPTimerClearFlag( OSTPCH_OVF );

#if (OSTPTIMPRESCALER > 64)
    }while( ( OSSTM_CIR(OSTPCH_OVF) & OSSTMFLBIT ) != 0 );
#endif
}

#endif /* (OSNTPISRARRIV > 0) || (OSNTPTSKARRIV > 0) */

#if(OSNTPBGTS > 0) || (OSNTPTSKRESLOCKTIME > 0) || (OSNTPISRRESLOCKTIME > 0)
/***************************************************************************
 * Function: OSTPStopBudget
 *
 * Description: Stop timing protection (the budget and/or the resource
 *              locking time) when a task or ISR is preempted by ISR2
 *              or system timer
 * Returns: 
 *
 * Notes:
 *
 **************************************************************************/

void OSTPStopBudget( void )
{
    OsTPTimVal = OSTPGetTimVal();       /* get the current timer counter one time */

#if (OSNTPTSKBGTS > 0)
    if( OSTP_GETOBJTYP(OsTPBudgetObject) == OBJECT_TASK )
    {
        OsRunning->tpRemained = OSTPTimerRemained( OSTPCH_BUDGET );
        OSTPResetBudget();
    }
#if (OSNTPISRBGTS > 0)
    else
#endif
#endif /* (OSNTPTSKBGTS > 0) */
#if (OSNTPISRBGTS > 0)
    if( OSTP_GETOBJTYP(OsTPBudgetObject) == OBJECT_ISR )
    {
        OsIsrTable[OSTP_GETOBJIND(OsTPBudgetObject)].tpRemained = OSTPTimerRemained( OSTPCH_BUDGET );
        OSTPResetBudget();
    }
#endif /* (OSNTPISRBGTS > 0) */

#if (OSNTPTSKRESLOCKTIME > 0)
    if( OSTP_GETOBJTYP(OsTPResLockObject) == OBJECT_TASK )
    {
        OsRunning->tpResources->tpRemained = OSTPTimerRemained( OSTPCH_RESLOCK );
        OSTPResetResLock();
    }
#if (OSNTPISRRESLOCKTIME > 0)
    else
#endif
#endif /* (OSNTPTSKRESLOCKTIME > 0) */
#if (OSNTPISRRESLOCKTIME > 0)
    if( OSTP_GETOBJTYP(OsTPResLockObject) == OBJECT_ISR )
    {
        OsIsrTable[OSTP_GETOBJIND(OsTPResLockObject)].tpResources->tpRemained = OSTPTimerRemained( OSTPCH_RESLOCK );
        OSTPResetResLock();
    }
#endif /* (OSNTPISRRESLOCKTIME > 0) */ 
}
#endif /* (OSNTPBGTS > 0) || (OSNTPTSKRESLOCKTIME > 0) || (OSNTPISRRESLOCKTIME > 0) */


#if (OSNTPTSKARRIV > 0)
/***************************************************************************
 * Function: OSTPStartTaskFrameInAlm
 *
 * Description: start control inter-arrival a task is activated or released
 *
 * Returns:     
 *
 * Notes:       
 **************************************************************************/
#if defined(OSHOOKPROTECTION)
OSBYTE OSTPStartTaskFrameInAlm( OSWORD taskId )
#else
void OSTPStartTaskFrameInAlm( OSWORD taskId )
#endif
{
    OSTSKCBPTR task;

    task = &OsTaskTable[taskId];

    /* Inter-arrival time protection */
    if( task->tpTimeFrame > 0 )
    {
        OSSIGNEDQWORD curTime;

        OsTPTimVal = OSTPGetTimVal();
        OSTPGetTime64(curTime);

        if( curTime < (task->tpLast + (OSSIGNEDQWORD)task->tpTimeFrame) )
        {                                       /* an attempt is made to activate a task before the end of task timeframe */
#if defined(OSHOOKPROTECTION)
            /* Note that violator is unknown here */
            OsTPHookAction = OSTPProtectionHook( OSTPOBJECT0, E_OS_PROTECTION_ARRIVAL );
            if( OsTPHookAction != PRO_IGNORE ) 
#endif /* defined(OSHOOKPROTECTION) */
            {
                OSShutdownOS( E_OS_PROTECTION_ARRIVAL );
            }
#if defined(OSHOOKPROTECTION)
            return OSFALSE;
#endif
        }
        task->tpLast = curTime;  
    }
#if defined(OSHOOKPROTECTION)
    return OSTRUE;
#endif
}

#if defined(OSHOOKPROTECTION)
/***************************************************************************
 * Function: OSTPStartTaskFrame
 *
 * Description: start control inter-arrival a task is activated or released
 *
 * Returns:     OSTRUE if Ok, or OSFALSE if it's impossible to
 *              activate/release the task.
 *
 * Notes:       it is implemented as a macro in API header if
 *              OSHOOKPROTECTION is not defined
 *
 **************************************************************************/

OSBYTE OSTPStartTaskFrame( OSWORD taskId )
{
    OSTSKCBPTR task;

    task = &OsTaskTable[taskId];

    /* Inter-arrival time protection */
    if( task->tpTimeFrame > 0 )
    {
        OSSIGNEDQWORD curTime;

        OsTPTimVal = OSTPGetTimVal();
        OSTPGetTime64(curTime);

        if( curTime < (task->tpLast + (OSSIGNEDQWORD)task->tpTimeFrame) )  
        {                                       /* an attempt is made to activate a task before the end of task timeframe */
            OSObjectType object;

#if defined(OSISRENTRYEXIT)
            if( OSISRLEVELMASKED > 0 ) 
            {
                OS_ISRTYPE *isr = OsIsrArray[OSISRLEVELMASKED - 1];
                object = OSTPISROBJECT(isr);
            }
            else
#endif /* defined(OSISRENTRYEXIT) */
            {
                object = OSTPTASKOBJECT(OsRunning);
            }

            OsTPHookAction = OSTPProtectionHook( object, E_OS_PROTECTION_ARRIVAL );

            if(  OsTPHookAction != PRO_IGNORE ) 
            {
                OSTPTimerInterruptForce( OSTPFORCETSKARRIVAL );   /* to kill current runable and maybe some more */
            }

            return OSFALSE;     /* activation is ignored regardless of protection hook action [OS465] */
        }
        task->tpLast = curTime; /* [OS469, OS472] */
    }

    return OSTRUE;
}
#endif /* defined(OSHOOKPROTECTION) */
#endif /* (OSNTPTSKARRIV > 0) */


#if (OSNTPISRARRIV > 0)
/***************************************************************************
 * Function: OSTPISRArrivalRate
 *
 * Description: Start inter-arrival protection for ISR:
 *
 * Returns:  TRUE if no violation
 *
 * Notes: OSShutdownOS will be called if violation occurs AND
 *        Protection Hook is not configured.
 *
 **************************************************************************/

#if defined(OSHOOKPROTECTION)
OSBYTE OSTPISRArrivalRate( OS_ISRTYPE *isr )
#else
void OSTPISRArrivalRate( OS_ISRTYPE *isr )
#endif
{
    OsTPTimVal = OSTPGetTimVal();

    /* Inter-arrival time protection */
    if( isr->tpTimeFrame > 0 )
    {
        OSSIGNEDQWORD curTime;

        OSTPGetTime64(curTime);

        if( curTime < (isr->tpLast + isr->tpTimeFrame) )  
        {                               /*  cat.2 interrupt occurs before the end of ISR timeframe */
#if defined(OSHOOKPROTECTION)
            OsIsrLevel++;       /* it's necessary for service GetISRID() may be invoked from user's ProtectionHook() */
            OsTPHookAction = OSTPProtectionHook( OSTPISROBJECT(isr), E_OS_PROTECTION_ARRIVAL );
            OsIsrLevel--;

            if( OsTPHookAction != PRO_IGNORE )      /* protection hook returned action != PRO_IGNORE */
            {           
                OSTPTimerInterruptForce( OSTPFORCEISRARRIVAL );   /* to kill something */
            }

            return OSFALSE;     /* user provided ISR2 will not executed regardless of protection hook action [OS048] */
#else
            OSShutdownOS( E_OS_PROTECTION_ARRIVAL );
#endif /* defined(OSHOOKPROTECTION) */
        }
        isr->tpLast = curTime;  
    }

#if defined(OSHOOKPROTECTION)
    return OSTRUE;
#endif
}
#endif /* (OSNTPISRARRIV > 0) */


#if (OSNTPTSKRESLOCKTIME > 0) 
/***************************************************************************
 * Function: OSTPStartTaskResLockTime
 *
 * Description: Start resource locking time in a task
 *
 * Returns: 
 *
 * Notes:
 *
 **************************************************************************/

void OSTPStartTaskResLockTime( OSWORD resInd )
{
    OSWORD i;

    OsTPTimVal = OSTPGetTimVal();

    for( i = 0; i < OsRunning->tpNumberResLock; i++ )
    {
        if( OsRunning->tpResLock[i].resId == resInd )
        {
            OSTPTICKTYPE locktime, remained;

            locktime = OsRunning->tpResLock[i].lockTime;

            if( OsRunning->tpResources )  /* there is another resource with started TP locking time */ 
            {
                remained = OSTPTimerRemained(OSTPCH_RESLOCK );

                if( remained <= locktime )
                {
                    break;
                }
                OsRunning->tpResources->tpRemained = remained - locktime;
            }

            OSTPStartResLock( locktime,  OSTPTASKOBJECT(OsRunning) );

            /* Add resource to link of task resources with started TP  */
            OsResources[resInd].tpNextRes = OsRunning->tpResources;
            OsRunning->tpResources = &OsResources[resInd];
            break;
        }
    }
}

/***************************************************************************
 * Function: OSTPResetTaskResLockTime
 *
 * Description: Reset task resource locking time
 *
 * Returns: 
 *
 * Notes:
 *
 **************************************************************************/

void OSTPResetTaskResLockTime( OSResType resRef )
{
    if( resRef == OsRunning->tpResources )
    {
        OSTPTICKTYPE remained;

        OsTPTimVal = OSTPGetTimVal();

        remained = OSTPTimerRemained( OSTPCH_RESLOCK );

        OsRunning->tpResources = resRef->tpNextRes;

        OSTPResetResLock();

        if( OsRunning->tpResources )
        {                       /* restore  locking time of a previos resourse for this task */
            OSTPStartResLock( OsRunning->tpResources->tpRemained + remained, OSTPTASKOBJECT(OsRunning) );
        }
    }
}

#endif /* (OSNTPTSKRESLOCKTIME > 0)  */


#if (OSNTPISRRESLOCKTIME > 0) 
/***************************************************************************
 * Function: OSTPStartISRResLockTime
 *
 * Description: Start resource locking time in a ISR
 *
 * Returns: 
 *
 * Notes:
 *
 **************************************************************************/

void OSTPStartISRResLockTime( OSWORD resInd )
{
    OSWORD i;
    OS_ISRTYPE *isr = OsIsrArray[OSISRLEVELMASKED - 1];

    OsTPTimVal = OSTPGetTimVal();

    for( i = 0; i < isr->tpNumberResLock; i++ )
    {
        if( isr->tpResLock[i].resId == resInd )
        {
            OSTPTICKTYPE locktime, remained;

            locktime = isr->tpResLock[i].lockTime;

            if( isr->tpResources )  /* there is another resouce with started TP locking time */ 
            {
                remained = OSTPTimerRemained( OSTPCH_RESLOCK );

                if( remained <= locktime )
                {
                    break;
                }
                isr->tpResources->tpRemained = remained - locktime;
            }

            OSTPStartResLock( locktime, OSTPISROBJECT(isr) );

            /* Add resource to link of ISR2 resources with started TP  */
            OsResources[resInd].tpNextRes = isr->tpResources;
            isr->tpResources = &OsResources[resInd];
            break;
        }
    }
}


/***************************************************************************
 * Function: OSTPResetISRResLockTime
 *
 * Description: Reset ISR resource locking time
 *
 * Returns: 
 *
 * Notes:
 *
 **************************************************************************/

void OSTPResetISRResLockTime( OSResType resRef )
{
    OS_ISRTYPE *isr = OsIsrArray[OSISRLEVELMASKED - 1];

    if( resRef == isr->tpResources )
    {
        OSTPTICKTYPE remained;

        OsTPTimVal = OSTPGetTimVal();

        remained = OSTPTimerRemained( OSTPCH_RESLOCK );

        isr->tpResources = resRef->tpNextRes;

        OSTPResetResLock();

        if( isr->tpResources )
        {                       /* restore locking time of a previos resourse for this task */
            OSTPStartResLock( isr->tpResources->tpRemained + remained,  OSTPISROBJECT(isr) );
        }
    }
}

#endif /* (OSNTPISRRESLOCKTIME > 0)  */

#endif /* defined(OSTIMINGPROTECTION) */
