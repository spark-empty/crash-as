#define OSSCH_C
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
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/src/ossch.c,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* Functions:    
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  OSEK OS scheduler           
*
* Notes:        
*
******************************************************************************/

#define OS_INTERNAL 1
#include    <os.h>
#undef OS_INTERNAL

#define OSTEXT_START_SEC_CODE
#include "ossections.h"
#define OS_START_SEC_VAR_UNSPECIFIED
#include "ossections.h"
#define OS_START_ONCE_SEC_VAR_FAST_UNSPECIFIED
#include "ossections.h"
#define OS_START_SEC_CONST_UNSPECIFIED
#include "ossections.h"

            
/*  Global OS variables */


#if defined(OSUSETCB) 
#if defined(OSRESOURCE) || defined(OSINRES)

OSTSKCBPTR OsPrioLink[OSNPRIORS]; /* Priority Link table                                  */

#endif /* defined(OSRESOURCE) || defined(OSINRES) */
#endif /* defined(OSUSETCB) */


/* Prototypes */
#if defined(OSMEMPROTECTION)
void OSProtectedCallTask( void );  /* for MISRA */
#endif

/*  Scheduler services  */

/*  Private OS Services */

#if defined(OSMEMPROTECTION)
/******************************************************************************
 * Function :   OSProtectedCallTask
 *
 * Description: Task caller with memory protection switch
 *
 * Returns:     none
 *
 * Notes:
 *
 ******************************************************************************/
void OSProtectedCallTask(void)
{
#if (OSNNOTTRUSTEDAPPS > 0) 
    OSTASKENTRY tsk = OS_TASK_ENTRY_PTR;
#endif

    OSSetCurApp(OsRunning->appId);

    OSOrtiResetIdOnExit( );     /* set that the caller service is finished  */
    OSCallPreTaskHook();

#if (OSNNOTTRUSTEDAPPS > 0) 
    if( OSMP_IS_NONTRUSTEDAPP(OsRunning->appId) ) 
    {
        OSDHI();
        OSISRALLON();
        OSMP_APP_OPEN_DATA();
        OS2UserModeEHI();
        (*tsk)();
        /* Task returned w/o TerminateTask  */
        OSSystemCall0( OsIdExceptionDispatch );
        /* never return here */
    }
    else 
#endif /* (OSNNOTTRUSTEDAPPS > 0) */
    {
        OSEI();
        OSCallTask();
    }
}
#endif /* defined(OSMEMPROTECTION) */

#if defined(OSSC1)
#if defined(OSBCC)
#if defined(OSNOFASTTERMINATE) 
/******************************************************************************
 * Function :   OSTaskForceDispatch
 *
 * Description: Task dispatcher for BCC1 w/o FastTerminate
 *
 * Returns:     none
 *
 * Notes:       interrupts are disabled before call
 *
 ******************************************************************************/

void OSTaskForceDispatch( void )
{
    OSTSKCBPTR osOldRunning;                    /* pointer to currently running task CB */
    
    OSCheckMainStack( );                        /* check main stack overflow            */

    osOldRunning = OsRunning;                   /* save running task (if any)          */

#if defined(OSHOOKPOSTTASK)
    if( OSTSKIND( OsRunning ) != OSNULLTASK )
    {
        OSPostTaskHook( );                      /* user hook or empty macro            */
    }
#endif

    OsRunning = OSGETMAXPRIOTASK;
    OSOrtiSetRunningId();

    if( OSSetJmp( osOldRunning->context ) )
    {
        OSSETBITRUNPRIO( );                     /* Restore internal resource priotity  */
        OSDI( );
        OSOrtiResetIdOnExit( );                 /* set that the caller service is finished */
        OSPreTaskHook( );
        return;
    }
    if( ( OSRUNNINGSTATUS & OSTCBFIRST ) != 0 ) /* if task not running yet             */
    {
        OSRUNNINGSTATUS &= (OSBYTE)(~OSTCBFIRST); /* task already running                */
        /* Save previous value of the SPRG1 into preempted task context and */
        /* set new SPRG1 value as address of the preempted task context */
        OSSAVECONTEXTADDR( osOldRunning->context );

        OSSETRUNPRIO( );                        /* set internal resource priotity, if any  */

        OSOrtiResetIdOnExit( );                 /* set that the caller service is finished */
        OSCallPreTaskHook( );
        OSEI( ); 
        OSCallTask( );
        /* Task returned w/o TerminateTask  */            
        OSDispatchOnError();                    /* ShutdownOS in STANDARD status */
    }
    OSLOADCONTEXTADDR( OsRunning->context );
    OSLongJmp( OsRunning->context );            /* restore context of preempted task */
    /* never return to this point */
    OSWARNSUPPRESS                              /* For extra CW warning suppress */
}

/******************************************************************************
 * Function :   OSTaskTerminateDispatch
 *
 * Description: Reduced analog of OSTaskForceDispatch()  (SC1, BCC) for 
 *              Terminate/ChainTask services; changes Task state to SUSPENDED.
 *
 * Returns:     never
 *
 * Notes:       interrupts are disabled before call
 *
 ******************************************************************************/

void OSTaskTerminateDispatch( void )
{
    OSPostTaskHook( );                          /* call user hook       */

    OSResetInternalPrio2( );

    if( (OSRUNNINGSTATUS & OSTCBFIRST) == 0 )
    {                                           /* if ChainTask was not called */
        OSRUNNINGSTATUS &= (~OSTCBNOSUSPENDED); /* clear "nonsuspended" flag */    
        OSRUNNINGSTATUS |= OSTCBFIRST;          /* set flag that task has no valid context  yet */  
        OSREMOVETASK( OsRunning );
    }
    OSCheckMainStack( );                        /* check main stack overflow */

    OsRunning = OSGETMAXPRIOTASK;
    OSOrtiSetRunningId();

    if( ( OSRUNNINGSTATUS & OSTCBFIRST ) != 0 )    /* if task not running yet                        */
    {
        OSRUNNINGSTATUS &= (OSBYTE)(~OSTCBFIRST);  /* task already running                           */
        OSLOADBASICSP( );

        OSSETRUNPRIO( );                           /* set internal resource priotity, if any         */

        OSOrtiResetIdOnExit( );                    /* set that the caller service is finished        */
        OSCallPreTaskHook( );
        OSEI( );
        OSCallTask( );
        /* Task returned w/o TerminateTask  */            
        OSDispatchOnError();                       /* ShutdownOS in STANDARD status */
    }
    OSLOADCONTEXTADDR( OsRunning->context );
    OSLongJmp( OsRunning->context );               /* restore context of preempted task */
    /* never return at this point */
    OSWARNSUPPRESS                                 /* For extra CW warning suppress                  */
}

#else  /* defined(OSNOFASTTERMINATE) */
/******************************************************************************
 * Function :   OSTaskForceDispatch
 *
 * Description: Task dispatcher for BCC1 with FastTerminate
 *
 * Returns:     none
 *
 * Notes:
 *
 ******************************************************************************/
void OSTaskForceDispatch( void )
{
#if defined(OSRESOURCE)
    OSTSKCBPTR osOldRunning;                   /* pointer to currently running task CB */
#else
    OSTASKTYPE osOldRunning;                   /* currently running task   */
#endif

    OSTASKTYPE osChainTask;                    /* task to be chain (if any)    */
    
    OSCheckMainStack( );                       /* check main stack overflow */

    osOldRunning = OsRunning;                  /* save running task (if any)   */

#if defined(OSHOOKPOSTTASK)
    if( OSTSKIND( OsRunning ) != OSNULLTASK )
    {
        OSPostTaskHook( );                     /* user hook or empty macro */
    }
#endif
    
    while( (OsRunning = OSGETMAXPRIOTASK) != osOldRunning ) /* cycle to launch all preempting tasks */
    { 
        OSOrtiSetRunningId();
        OSSETRUNPRIO( );                       /* set internal resource priotity, if any       */
#if defined(OSRESOURCE) || defined(OSINRES)
        OSRUNNINGSTATUS |= OSTCBNOSUSPENDED;      /* set "nonsuspended" flag */   
#endif /* defined(OSRESOURCE) || defined(OSINRES) */

        OSOrtiResetIdOnExit();                 /* set that the caller service is finished  */
        OSCallPreTaskHook();
        OSEI();
        osChainTask = OSCallTask();            /* execute the task, and get the ID of chained task */
        OSDI();
        OSCheckMainStack();                    /* check main stack overflow */

#if defined(OSORTICURRENTSERVICEID)
        /* in case of FastTerminate all work of Chain/TerminateTask services    */
        /* is done in the dispatcher, so ORTI trace setting is done here too    */
        if( osChainTask != OSNULLTASK )
        {
            OSOrtiSetServiceWatch( OSServiceId_ChainTask );
            OSOrtiSetOldServiceID( OSServiceId_ChainTask );
        }
        else
        {
            OSOrtiSetServiceWatch( OSServiceId_TerminateTask );
            OSOrtiSetOldServiceID( OSServiceId_TerminateTask );
        }
#endif

#if defined(OSRESOURCE) || defined(OSINRES)
        OSRUNNINGSTATUS &= (~OSTCBNOSUSPENDED);  /* clear "nonsuspended" flag */    
#endif
        OSResetInternalPrio2( );

        OSREMOVETASK( OsRunning );

        if( osChainTask != OSNULLTASK )          /* if some task needs to be chained */
        {
            OSTask2Ready( osChainTask );         /* then readies chained task */      
        }
        OSPostTaskHook( );                       /* user hook or empty macro */
    }                                               
    OSOrtiSetRunningId();
    OSSETBITRUNPRIO( );         /* restore internal resource priotity */
    OSOrtiResetIdOnExit( );     /* set that the caller service is finished  */
    OSPreTaskHook( );           /* call user hook           */

    return;
    OSWARNSUPPRESS              /* For extra CW warning suppress */
}
#endif /* defined(OSNOFASTTERMINATE) */
#endif /* OSBCC */

#if defined(OSECC)
/******************************************************************************
 * Function :   OSTaskForceDispatch
 *
 * Description: Task dispatcher for ECC1, SC1
 *
 * Returns:     none
 *
 * Notes:       interrupts are disabled before call
 *
 ******************************************************************************/
void OSTaskForceDispatch( void )
{
    OSTSKCBPTR  osOldRunning; /* pointer to currently running task CB */

    osOldRunning = OsRunning;
 
#if defined(OSHOOKPOSTTASK)
    if( OSTSKIND(osOldRunning) != OSNULLTASK )
    {
        OSPostTaskHook( );                      /* call user hook                    */
    }
#endif /* defined(OSHOOKPOSTTASK)*/

    OSCheckMainStack( );                        /* check main stack overflow         */
    OSCheckStack( );                            /* check stack overflow              */
    OsRunning = OSGETMAXPRIOTASK;
    OSOrtiSetRunningId();

    if( OSSetJmp( osOldRunning->context ) ) /* save context of preempted task     */
    {   /* return point from dispatched tasks */

        OSSETBITRUNPRIO( );                 /* restore internal resource priotity */
        OSOrtiResetIdOnExit( );             /* set that the caller service is finished */
        OSPreTaskHook( );
        return;                         
    }

#if (OSNXTSKS > 0)
    if( (osOldRunning->status & OSTCBEXTENDED) == 0 )
#endif
    {
        /* Save previous value of the SPRG1 into preempted basic task context and */
        /* set new SPRG1 value as address of the preempted task context */
        OSSAVECONTEXTADDR( osOldRunning->context );
    }    

    if( ( OsRunning->status & OSTCBFIRST ) != 0 )   /* if task not running yet */
    {
                                                    /* start-up the task    */
        OsRunning->status &= (OSBYTE)(~OSTCBFIRST); /* task is running      */

#if (OSNXTSKS > 0)
        if( ( OsRunning->status & OSTCBEXTENDED ) != 0 )
        {
            OSLOADSP( OsRunning->tos );
        }
        else
        {
            if( ( osOldRunning->status & OSTCBEXTENDED ) != 0 ) 
            {                                       /* if preempted task is EXTENDED */
                OSLOADBASICSP();
            }
        }
#endif

        OSSETRUNPRIO( );        /* set internal resource priotity, if any       */

        OSOrtiResetIdOnExit( ); /* set that the caller service is finished  */
        OSCallPreTaskHook( );
        OSEI( );
        OSCallTask( );          /* start task via conventional call */
        /* Task returned w/o TerminateTask  */            
        OSDispatchOnError();    /* ShutdownOS in STANDARD status */
    }
  
#if (OSNXTSKS > 0)
    if( ( OsRunning->status & OSTCBEXTENDED ) == 0 )
#endif
    {
        /* Restore previous value of the SPRG1 from the preempted task context */
        OSLOADCONTEXTADDR( OsRunning->context );
    }
    OSLongJmp( OsRunning->context );        /* restore context of preempted task   */
    /* never return to this point */
    OSWARNSUPPRESS                          /* For extra CW warning suppress */
}

/******************************************************************************
 * Function :   OSTaskTerminateDispatch
 *
 * Description: Reduced analog of OSTaskForceDispatch()  (SC1, ECC) for 
 *              Terminate/ChainTask services; changes Task state to SUSPENDED.
 *
 * Returns:     never
 *
 * Notes:       interrupts are disabled before call
 *
 ******************************************************************************/

void OSTaskTerminateDispatch( void )
{
    OSPostTaskHook( );                      /* call user hook       */

    OSResetInternalPrio2( );

    if( (OSRUNNINGSTATUS & OSTCBFIRST) == 0 )
    {                                           /* if ChainTask was not called */
        OSRUNNINGSTATUS &= (~OSTCBNOSUSPENDED); /* clear "nonsuspended" flag */    
        OSRUNNINGSTATUS |= OSTCBFIRST;          /* set flag that task has no valid context  yet */  
        OSREMOVETASK( OsRunning );
    }

    OSCheckMainStack( );                            /* check main stack overflow */
    OSCheckStack( );                                /* check stack overflow */
    OsRunning = OSGETMAXPRIOTASK;
    OSOrtiSetRunningId();

    if( ( OsRunning->status & OSTCBFIRST ) != 0 )   /* if task not running yet */
    {
                                                    /* start-up the task    */
        OsRunning->status &= (OSBYTE)(~OSTCBFIRST);

#if (OSNXTSKS > 0)
        if( (OsRunning->status & OSTCBEXTENDED) != 0 )
        {
            OSLOADSP( OsRunning->tos );
        }
        else
#endif
        {
            OSLOADBASICSP( );
        }
        OSSETRUNPRIO( );                /* set internal resource priotity, if any       */
        OSOrtiResetIdOnExit( );         /* set that the caller service is finished  */
        OSCallPreTaskHook( );
        OSEI( ); 
        OSCallTask( );                  /* start task (via conventional call or jump)   */
        /* Task returned w/o TerminateTask  */            
        OSDispatchOnError();            /* ShutdownOS in STANDARD status */
    }
    
#if (OSNXTSKS > 0)
    if( ( OsRunning->status & OSTCBEXTENDED ) == 0 )
#endif
    {
        OSLOADCONTEXTADDR( OsRunning->context );
    }

    OSLongJmp( OsRunning->context );        /* restore context of preempted task   */
    /* never return at this point */
    OSWARNSUPPRESS                          /* For extra CW warning suppress */
}
#endif /* OSECC */

#if defined(OSEXTSTATUS)
/******************************************************************************
 * Function :   OSDispatchOnError
 *
 * Description: stripped Task dispatcher for error cases in SC1
 *
 * Returns:     never
 *
 * Notes:       called from OS*Dispatch and OSLeaveISR with new OsRunning set
 *
 ******************************************************************************/
void OSDispatchOnError( void )
{
RescheduleOnError:              
    OSDI();                           
    OSErrorHook_noPar( E_OS_MISSINGEND );   /* Task returned w/o TerminateTask  */
    OSCheckMainStack( );                            /* check main stack overflow */
    OSCheckStack( );                                /* check stack overflow */
    OSPostTaskHook( );
    OSKillRunningTask();    /* remove Task from list and clear Resources */
    OsRunning = OSGETMAXPRIOTASK;
    OSOrtiSetRunningId();

    if( ( OsRunning->status & OSTCBFIRST ) != 0 )   /* if task is not running yet */
    {                                               /* start-up the task */
        OSRUNNINGSTATUS &= (OSBYTE)(~OSTCBFIRST);   /* task already running */
#if defined(OSECC)
#if (OSNXTSKS > 0)
        if( (OsRunning->status & OSTCBEXTENDED) != 0 )
        {
            OSLOADSP( OsRunning->tos );
        }
        else
#endif
        {
            OSLOADBASICSP( );
        }
#else  /* defined(OSECC) */
        OSLOADBASICSP( );
#endif /* defined(OSECC) */
        OSSETRUNPRIO( );        /* set internal resource priotity, if any   */
        OSOrtiResetIdOnExit( ); /* set that the caller service is finished  */
        OSCallPreTaskHook( );
        OSEI( ); 
        OSCallTask();
        /* Task returns w/o TerminateTask */
        goto RescheduleOnError;
    }
#if (OSNXTSKS > 0)
    if( ( OsRunning->status & OSTCBEXTENDED ) == 0 )
#endif
    {
        OSLOADCONTEXTADDR( OsRunning->context );
    }

    OSLongJmp( OsRunning->context );        /* restore context of preempted task   */
    /* OSLongJmp never returns */
    OSWARNSUPPRESS                          /* For extra CW warning suppress */
}
#endif /* defined(OSEXTSTATUS) */

#else   /* defined(OSSC1) */

/******************************************************************************
 * Function :   OSTaskInternalDispatch
 *
 * Description: Main part of Task dispatcher for protected environment (SC2..4)
 *
 * Returns:     never
 *
 * Notes:       called from OS*Dispatch and OSLeaveISR with new OsRunning set
 *
 ******************************************************************************/
void OSTaskInternalDispatch( void )
{
RescheduleOnError:              /* old Task is killed before "goto" this label */
    OSOrtiSetRunningId();

    if( ( OsRunning->status & OSTCBFIRST ) != 0 )   /* if task not running yet */
    {
        OSTPResumeTaskBudget();
                                                    /* start-up the task    */
        OsRunning->status &= (OSBYTE)(~OSTCBFIRST); /* task is running      */

#if defined(OSMEMPROTECTION)
        OSDHI();
        OSMP_TASK_OPEN_STACK();
#endif
        OSLOADSP( OsRunning->tos );
#if defined(OSMEMPROTECTION)        /* when stack area is protected by MPU */
        OSEHI();                    /* stack switch is done with all interrupts disabled */
#endif
        OSSETRUNPRIO( );            /* set internal resource priotity, if any       */

#if defined(OSMEMPROTECTION)
        OSProtectedCallTask( );     /* start task (via conventional call or jump)   */
#else
#if defined(OSAPPLICATION)
        OSSetCurApp( OsRunning->appId );
#endif
        OSOrtiResetIdOnExit( );     /* set that the caller service is finished  */
        OSCallPreTaskHook( );
        OSEI( ); 
        OSCallTask();
#endif
        OSDI();                           
        OSErrorHook_noPar( E_OS_MISSINGEND );   /* Task returned w/o TerminateTask  */
        OSPostTaskHook( );
        OSKillRunningTask();    /* remove Task from list and clear Resources */

        OSTPResetTaskBudget();
        OsRunning = OSGETMAXPRIOTASK;
        goto RescheduleOnError;
    }

    OSTPResumeTaskBudget();
  
    OSSetCurApp(OsRunning->appId);
#if defined(OSMEMPROTECTION)
    OSMP_NONTRUSTEDAPP_OPEN_DATA_DHI();
    OSDHI();
    OSMP_TASK_OPEN_STACK();
#endif /* defined(OSMEMPROTECTION) */
    OSLongJmp( OsRunning->context );        /* restore context of preempted task   */
    /* never return here */
    OSWARNSUPPRESS                          /* For extra CW warning suppress */
}

#if defined(OSMEMPROTECTION)
/******************************************************************************
 * Function :   OS_ExceptionDispatch
 *
 * Description: Dispatch in case of Task returned w/o Terminate from OSCallTask 
 *
 * Returns:     never
 *
 ******************************************************************************/

void OS_ExceptionDispatch( void )       
{
    OSDI();
    OSErrorHook_noPar( E_OS_MISSINGEND );   /* Task returned w/o TerminateTask  */
    OSKillRunningTask();                    /* remove Task from list and clear Resources    */
    OSTPResetTaskBudget();

    OsRunning = OSGETMAXPRIOTASK;

    OSTaskInternalDispatch();
    /* unreachable point */

    OSWARNSUPPRESS
}

#endif/*defined(OSMEMPROTECTION)*/

/******************************************************************************
 * Function :   OSTaskForceDispatch
 *
 * Description: Task dispatcher for protected environment (SC2..4)
 *
 * Returns:     none
 *
 * Notes:       interrupts shall be disabled before call
 *
 ******************************************************************************/

void OSTaskForceDispatch( void )
{
    OSTSKCBPTR  osOldRunning; /* pointer to currently running task CB */

    osOldRunning = OsRunning;
 
    if( OSTSKIND(osOldRunning) != OSNULLTASK )
    {
        OSPostTaskHook( );                  /* call user hook       */
        OSCHECKSTACK_TP( );                 /* check stack overflow and save TP state */
    }

    OsRunning = OSGETMAXPRIOTASK;

    if( OSSetJmp( osOldRunning->context ) ) /* save context of preempted task     */
    { 
#if defined(OSMEMPROTECTION)
        OSEHI();
#endif
        OSSETBITRUNPRIO( );                 /* restore internal resource priotity */
        OSOrtiResetIdOnExit( );             /* set that the caller service is finished */
        OSPreTaskHook( );
        /* return point from dispatched tasks */
        return;                         
    }
    OSTaskInternalDispatch();
    /* unreachable point */
}

/******************************************************************************
 * Function :   OSTaskTerminateDispatch
 *
 * Description: Reduced analog of OSTaskForceDispatch()  (SC2..4) for 
 *              Terminate/ChainTask services; changes Task state to SUSPENDED.
 *
 * Returns:     never
 *
 * Notes:       interrupts shall be disabled before call
 *
 ******************************************************************************/

void OSTaskTerminateDispatch( void )
{
    OSPostTaskHook( );                  /* call user hook       */

    OSResetInternalPrio2( );

    if( (OSRUNNINGSTATUS & OSTCBFIRST) == 0 )
    {                                           /* if ChainTask was not called */
        OSRUNNINGSTATUS &= (~OSTCBNOSUSPENDED); /* clear "nonsuspended" flag */    
        OSRUNNINGSTATUS |= OSTCBFIRST;          /* set flag that task has no valid context  yet */  
        OSREMOVETASK( OsRunning );
    }
    
#if defined(OSSYSSTKCHECK)
    OSCheckStack();
    OsKilled &= ~OSRUNTSKKILLED;
#endif
    OSTPResetTaskBudget();

    OsRunning = OSGETMAXPRIOTASK;

    OSTaskInternalDispatch();
    /* unreachable point */
}

#endif  /* defined(OSSC1) */


/*** Public OS Services ***/

/******************************************************************************
 * Function :   Schedule
 *
 * Description: Yield the processor to the task with higher priority, if any
 *
 * Returns:     E_OK                    no errors
 *              E_OS_CALLEVEL (ext.status) call at interrupt level
 *
 * Notes:
 *
 ******************************************************************************/

StatusType OS_Schedule( void )
{
    OSOrtiSetServiceWatch( OSServiceId_Schedule );
    
#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_Schedule, 0 ); 
        }
        else
#endif
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_Schedule, 0 ); 
        }
    }
#endif /* defined(OSCHECKCONTEXT) */

#if defined(OSEXTSTATUS)
#if defined(OSRESOURCE)
    if( OsRunning->resources != OSNULLRES )
    {                                       
        OSRETERROR( E_OS_RESOURCE, OSServiceId_Schedule, 0 ); /* resource is occupied */
    }
#endif
#endif /* OSEXTSTATUS */

    OSDI( ); /* It is not necessary to save./restore int.mask  because */
             /* this service may be called with enabled interrupts only */
    OSOrtiSetOldServiceID( OSServiceId_Schedule );
    
    OSResetInternalPrio( );
    if( ( OSGETMAXPRIOTASK != OsRunning )
#if defined(OSRESOURCEISR) && !defined(OSEXTSTATUS)
          && ( OsIsrLevel == 0 )                  /* Scheduler is called  only in case when */
                                                  /* ISR resources are not occupied */
#endif
      )
    {
        OSTaskForceDispatch( );
    }
#if defined(OSINRES)
    else
    {
        OSSETRUNPRIO( );
    }
#endif

    OSOrtiResetIdOnExit( );                     /* set that the caller service is finished  */
    OSEI( );
    return( E_OK );
    OSWARNSUPPRESS                              /* For extra CW warning suppress */
}
