#define OSTSK_C
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
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/src/ostsk.c,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* Functions:    
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  OSEK OS task management         
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

#if !defined(OSEXTSTATUS)
#define taskInd taskId
#endif

/*  Task management */

/******************************************************************************
 * Function:    ActivateTask
 *
 * Description: activates the Task, make it RUNNING if conditions are met
 *
 * Returns: E_OK                      no errors
 *          E_OS_DISABLEDINT          service call while interrupts disabled
 *          E_OS_ID    (ext.status)   the identifier is invalid
 *          E_OS_LIMIT (ext.status)   the task is already active
 *
 ******************************************************************************/

StatusType OS_ActivateTask( TaskType taskId )
{
#if defined(OSEXTSTATUS)
    OSWORD  taskInd;              /* index in Tasks tables */
#endif
    OSIMSAVE /* OSINTMASKTYPE save;                        */


    OSOrtiSetServiceWatch( OSServiceId_ActivateTask );

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_ActivateTask, taskId );
        }
        else
#endif        
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_ActivateTask, taskId ); 
        }
    }
#endif /* defined(OSCHECKCONTEXT) */

#if defined(OSEXTSTATUS)
    taskInd = (OSWORD)OS_GETOBJIND( taskId );

    if( OSTASKIDISINVALID(taskId) )
    {
        OSRETERROR( E_OS_ID, OSServiceId_ActivateTask, taskId ); /* invalid ID */
    }
#endif

    OSCHECKACCESSRIGHTS( OsTaskTable[taskInd].appMask, OSServiceId_ActivateTask, taskId );

    OSDIS( save );
    if( OSTASKACTEXHAUSTED( taskInd ) )
    {
        OSRI( save );
        OSRETERROR( E_OS_LIMIT, OSServiceId_ActivateTask, taskId ); /* attempt to multiply activation */
    }
    OSOrtiSetOldServiceID( OSServiceId_ActivateTask );
 
#if defined(OSUSETCB) || defined(OSINRES) 
#if defined(OSECC)
#if (OSNXTSKS > 0)
    OsTaskTable[taskInd].set_event = OSNOEVENTS;
#endif
#endif /* defined(OSECC) */
    OSActivateTask( taskInd );
#else
    OSTask2Ready( taskInd );
#endif /* defined(OSUSETCB)  || defined(OSINRES) */

#if defined(OSFULLPREEMPT) || defined(OSMIXPREEMPT)
    if( ( OsRunning != OSGETMAXPRIOTASK )
#if defined(OSISRENTRYEXIT)
        && ( OsIsrLevel == 0 )
#endif
        )
    {
        OSDISPATCH( );
    }
    /* no call to dispatcher at all if OSNOPREEMPT */
#endif /* defined(OSFULLPREEMPT) || defined(OSMIXPREEMPT) */

    OSOrtiResetIdOnExit( ); /* set that the caller service is finished */
    OSRI( save );
    return( E_OK );
}

#if defined(OSNOFASTTERMINATE)
/******************************************************************************
 * Function:    TerminateTask
 *
 * Description: Terminate the running task
 *
 * Returns:     function doesn't returns if there are no errors
 *              E_OS_RESOURCE (ext.status) task still occupies resources
 *              E_OS_CALLEVEL (ext.status) call at interrupt level
 *
 * Notes:       do not return on success
 *
 ******************************************************************************/

StatusType OS_TerminateTask( void )
{
#if defined(OSEXTSTATUS)
#endif

    OSOrtiSetServiceWatch( OSServiceId_TerminateTask );
 
#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_TerminateTask, 0 ); 
        }
        else
#endif
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_TerminateTask, 0 ); 
        }
    }
#endif /* defined(OSCHECKCONTEXT) */

#if defined(OSEXTSTATUS)
#if defined(OSRESOURCE)
    if( OsRunning->resources != OSNULLRES ) /* resource is occupied */
    {
        OSRETERROR( E_OS_RESOURCE, OSServiceId_TerminateTask, 0 );   
    }
#endif
#endif /* OSEXTSTATUS */

    OSDI( );

    OSOrtiSetOldServiceID( OSServiceId_TerminateTask );
 
    OSTaskTerminateDispatch( ); /* force dispatcher for terminate case */    
    
    /* never return at this point */
    return( E_OK );
}

/******************************************************************************
 * Function:    ChainTask
 *
 * Description: Terminate the running task and start the given task
 *
 * Returns: function doesn't returns if there are no errors
 *          E_OS_ID       (ext.status) the task identifier is invalid
 *          E_OS_RESOURCE (ext.status) calling task still occupies resources
 *          E_OS_CALLEVEL (ext.status) call at interrupt level
 *          E_OS_LIMIT    (ext.status) non-allowed multiply activation of the task
 *
 * Notes:   do not return on success
 *
 ******************************************************************************/
StatusType OS_ChainTask( TaskType taskId )
{
#if defined(OSEXTSTATUS)
    OSWORD  taskInd;
#endif


    OSOrtiSetServiceWatch( OSServiceId_ChainTask );

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_ChainTask, taskId ); 
        }
        else
#endif
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_ChainTask, taskId ); 
        }
    }
#endif /* defined(OSCHECKCONTEXT) */

#if defined(OSEXTSTATUS)
    taskInd = (OSWORD)OS_GETOBJIND( taskId );

#if defined(OSRESOURCE)
    if( OsRunning->resources != OSNULLRES ) /* resource is occupied */
    {
        OSRETERROR( E_OS_RESOURCE, OSServiceId_ChainTask, taskId ); 
    }
#endif

    if( OSTASKIDISINVALID(taskId) ) /* invalid ID */
    {
        OSRETERROR( E_OS_ID, OSServiceId_ChainTask, taskId ); 
    }
#endif /* OSEXTSTATUS */

    OSCHECKACCESSRIGHTS( OsTaskTable[taskInd].appMask, OSServiceId_ChainTask, taskId );

    OSDI( );
    if( ( OSTASKACTEXHAUSTED( taskInd ) ) && ( OSTSKIND( OsRunning ) != taskInd ) )
    {                                           
        OSEI( );
        OSRETERROR( E_OS_LIMIT, OSServiceId_ChainTask, taskId ); /* attempt to multiply activation       */
    }        

#if (OSNXTSKS > 0)
    OsTaskTable[taskInd].set_event = OSNOEVENTS;
#endif

    OSActivateTask( taskInd );
 
    OSOrtiSetOldServiceID( OSServiceId_ChainTask );
    OSTaskTerminateDispatch( );                 /* force dispatcher for terminate case */
    /* never return to this point */    
    return( E_OK );
}

#endif /* defined(OSNOFASTTERMINATE) */

/******************************************************************************
 * Function:    GetTaskId
 *
 * Description: Return the index, corresponding to running task.
 *
 * Returns: E_OK                           no errors
 *          E_OS_CALLEVEL (ext.status)     call in disabled context
 *
 ******************************************************************************/

StatusType OS_GetTaskID( TaskRefType taskIdRef )
{
    OSOrtiSetServiceWatch( OSServiceId_GetTaskID );

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK |
                         OSISRLEVELHOOKERROR | OSISRLEVELHOOKAPPERROR |
                         OSISRLEVELHOOKTASK | OSISRLEVELHOOKPROTECTION ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_GetTaskID, 0 );
        }
        else
#endif        
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_GetTaskID, 0 ); 
        }
    }
#endif /* OSCHECKCONTEXT */

    OSCHECKWRITEACCESS2( taskIdRef, sizeof(TaskType), OSServiceId_GetTaskID, 0 );

    *taskIdRef = (OSWORD)OS_MKOBJID( OBJECT_TASK, (OSWORD)OSTSKIND( OsRunning ) );
    
    OSOrtiServiceWatchOnExit( OSServiceId_GetTaskID ); /* clean service watch on hook leaving */ 
    return( E_OK );
}

/******************************************************************************
 * Function:    GetTaskState
 *
 * Description: Return the status of the given task
 *
 * Returns: E_OK                    no errors
 *          E_OS_ID (ext.status)    task identifier is invalid
 *
 ******************************************************************************/

StatusType OS_GetTaskState ( TaskType taskId, TaskStateRefType stateRef )
{
#if defined(OSEXTSTATUS)
    OSWORD  taskInd;
#endif

    OSIMSAVE /* OSINTMASKTYPE save;       */


    OSOrtiSetServiceWatch( OSServiceId_GetTaskState );

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK |
                         OSISRLEVELHOOKERROR | OSISRLEVELHOOKAPPERROR | OSISRLEVELHOOKTASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_GetTaskState, taskId );
        }
        else
#endif        
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_GetTaskState, taskId ); 
        }
    }
#endif /* OSCHECKCONTEXT */

#if defined(OSEXTSTATUS)
    taskInd = (OSWORD)OS_GETOBJIND(taskId);
#endif
  
#if defined(OSEXTSTATUS)
    if( OSTASKIDISINVALID(taskId) )
    {
        OSRETERROR( E_OS_ID, OSServiceId_GetTaskState, taskId ); /* invalid ID */
    }
#endif

    OSCHECKACCESSRIGHTS( OsTaskTable[taskInd].appMask, OSServiceId_GetTaskState, taskId );
    OSCHECKWRITEACCESS2( stateRef, sizeof(TaskStateType), OSServiceId_GetTaskState, taskId );

    OSDIS( save );

    if( taskInd == OSTSKIND( OsRunning ) )
    {
        *stateRef = RUNNING;
    }
    /* else if ECC1 , there is WAITING state */
#if defined(OSECC) && (OSNXTSKS > 0) 
    else if( ( OSTASKSTATUS( taskInd ) & OSTCBWAIT ) != 0 )
    {
        *stateRef = WAITING;
    }
#endif /* defined(OSECC) && (OSNXTSKS > 0) */
    else
    {
        if( OSISTASKNOSUSPEND( taskInd ) )
        {
            *stateRef = READY;
        }
        else
        {
            *stateRef = SUSPENDED;
        }
    }

    OSRI( save );

    OSOrtiServiceWatchOnExit( OSServiceId_GetTaskState ); /* clean service watch on hook leaving */ 
    return( E_OK );
}

#if defined(OSSYSSTKCHECK) && defined(OSUSETOS)
/***************************************************************************
 * Function:    OSCheckStack
 *
 * Description: Check task stack overflow for preempted Task
 *
 * Returns:     none
 *
 **************************************************************************/
void OSCheckStack( void )
{
#if defined(OSAPPLICATION)
    RestartType restart = RESTART;
#endif

    if( OSTSKIND(OsRunning) == OSNULLTASK )
    {
        return;
    }

#if defined(OSMEMPROTECTION)
    if( OSSTKINVALID( OsRunning->bos ) )
    {
#if defined(OSHOOKPROTECTION)        
        ProtectionReturnType action;

        /* set violator Id */
        OsViolatorTaskId = OS_MKOBJID(OBJECT_TASK, OsRunning->taskId);
        OsViolatorAppId = OsRunning->appId;
        OsViolatorISRId = INVALID_ISR;

        OSOrtiSetServiceWatch( OSServiceId_ProtectionHook );    /* set watch to this service */ 
        OSSETPROTCNXT();
        action = ProtectionHook( E_OS_STACKFAULT );    
        OSCLRPROTCNTX();
        OSOrtiServiceWatchOnExit( OSServiceId_ProtectionHook ); /* clear service watch on hook leaving */ 
        
        switch( action ) /* call user's hook */
        {
        case PRO_KILLTASKISR:
            OSKillTask(OsRunning); 
            break;
            
        case PRO_KILLAPPL: 
            restart = NO_RESTART; /* no break */
            
        case PRO_KILLAPPL_RESTART:
            if( OSTerminateApplication(restart) )
            {
                break;
            }
            /* no break - OSShutdownOS() shall be called */
        case PRO_SHUTDOWN:
        default: 
            OSShutdownOS( E_OS_STACKFAULT );
        }
        OSSTKSETGUARD( OsRunning->bos );        /* restore corrupted stack pad      */
#else
        OSShutdownOS( E_OS_STACKFAULT );
#endif
    }
#else /* defined(OSMEMPROTECTION) */
#if defined(OSSC1)
    if( ((OsRunning->status) & OSTSKEXTENDED ) != 0 ) /* Basic task has single stack*/
#endif
    {
        if( OSSTKINVALID( OsRunning->bos ) )
        {                                       /* call user's hook */
            OSShutdownOS( E_OS_STACKFAULT );
        }
    }
#endif /* defined(OSMEMPROTECTION) */
}

#endif  /* defined(OSSYSSTKCHECK) && defined(OSUSETOS) */

#if defined(OSSYSSTKCHECK)
#if defined(OSSC1)
/***************************************************************************
 * Function:    OSCheckMainStack
 *
 * Description: Check main stack overflow 
 *
 **************************************************************************/
void OSCheckMainStack( void )
{
    if( OSSTKINVALID(OSSTACKBOTTOM) )
    {                                       
        OSShutdownOS( E_OS_STACKFAULT );
    }
} 
#endif

#if defined(OSUSEISRSTACK)
/***************************************************************************
 * Function:    OSCheckIsrStack
 *
 * Description: Check ISR stack overflow 
 *
 * Notes:       for SC2,3,4 check is done in Interrupt dispatcher
 *
 **************************************************************************/
void OSCheckIsrStack( void )
{
    if( OSSTKINVALID(OSISRSTKEND) )
    {
        OSShutdownOS( E_OS_STACKFAULT );
    }
}
#endif /* defined(OSUSEISRSTACK) */
#endif /* defined(OSSYSSTKCHECK) */

#if defined(OSSTKCHECK) || (OSORTIDEBUGLEVEL > 0)

/***************************************************************************
 * Function:   OSGetUsedBytes
 *
 * Description: Calculates number of used bytes
 *
 * input:   start stack pointer, size in long words
 *
 * Returns: number of bytes
 *
 **************************************************************************/
OSWORD OSGetUsedBytes( const OSDWORD* _start, OSWORD num )
{
    for( ; num > 0; num--, _start++ )
    {
        if( *_start != OSORTISTACKPATTERN )
            break;
    }

    return (OSWORD)( num * 4 );
}

/***************************************************************************
 * Function:   GetRunningStackUsage
 *
 * Description: Calculates task stack usage
 *
 * Returns:     stack usage in bytes;
 *              OSSTKNOASSIGNED if Task has no own stack 
 *
 **************************************************************************/
OSWORD GetRunningStackUsage( void )
{
#if defined(OSSC1) && (defined(OSBCC) || (OSNXTSKS == 0))
    return ( OSSTKNOASSIGNED );                 /* single stack */
#else   /* defined(OSSC1) && (defined(OSBCC) || (OSNXTSKS == 0)) */


    if( OSTSKIND(OsRunning) == OSNULLTASK )               /* No running task */
    {
        return ( OSSTKNOASSIGNED );
    }

#if defined(OSSC1)
    if( (OSRUNNINGSTATUS & OSTCBEXTENDED) == 0 ) /* Basic task has single stack*/
    {
        return ( OSSTKNOASSIGNED );
    }
#endif

#if defined(OSAPPLICATION)
    if( (OSCURRENTAPPMASK & OsRunning->appMask) == 0 )
    {                                /* attempt to access stack of other application */
        return( OSSTKNOASSIGNED );
    }
#endif

    return( OSGetUsedBytes( OsRunning->bos, (OSWORD)(OsRunning->tos - OsRunning->bos) ) );
#endif  /* defined(OSSC1) && (defined(OSBCC) || (OSNXTSKS == 0)) */
}

/***************************************************************************
 * Function:    GetStackUsage
 *
 * Description: Calculates task stack usage
 *
 * inp:  task ID
 *
 * Returns:     stack usage in bytes;
 *              OSSTKNOASSIGNED if Task has no own stack 
 *
 **************************************************************************/
OSWORD GetStackUsage( TaskType taskId )
{
#if defined(OSSC1)
#if defined(OSBCC) || (OSNXTSKS == 0)

    return( OSSTKNOASSIGNED );                 /* single stack */
#else   /* defined(OSBCC) || (OSNXTSKS == 0) */
    if( (OSTASKSTATUS(OS_GETOBJIND(taskId)) & OSTCBEXTENDED) == 0 ) /* Basic task has single stack*/
            return ( OSSTKNOASSIGNED );
#endif /* defined(OSBCC) || (OSNXTSKS == 0) */
#endif /* defined(OSSC1) */

#if !defined(OSSC1) || ( (defined(OSECC) && (OSNXTSKS != 0) ) )

#if defined(OSEXTSTATUS)
    if( OSTASKIDISINVALID(taskId) )
#else
    if( OS_GETOBJIND(taskId) >= OSNTSKS )   
#endif
    {   /* invalid taskId */
        return( OSSTKNOASSIGNED );
    }
#if defined(OSAPPLICATION)
    if( (OSCURRENTAPPMASK & OsTaskTable[OS_GETOBJIND(taskId)].appMask) == 0 )
    {                                /* attempt to access stack of other application */
        return( OSSTKNOASSIGNED );
    }
#endif

    return( OSGetUsedBytes( OsTaskTable[OS_GETOBJIND(taskId)].bos, 
                            (OSWORD)(OsTaskTable[OS_GETOBJIND(taskId)].tos - OsTaskTable[OS_GETOBJIND(taskId)].bos) ) );
#endif /* !defined(OSSC1) || ( (defined(OSECC) && (OSNXTSKS != 0) ) ) */
}
#endif  /* defined(OSSTKCHECK) || (OSORTIDEBUGLEVEL > 0) */

#if defined(OSAPPLICATION)
/***************************************************************************
 * function:   OSKillAppTasks()
 *
 * Description: kills all tasks which belong to current application 
 *
 * Returns:     none
 *
 **************************************************************************/
void OSKillAppTasks( void )
{
    OSWORD  tskInd;
    OSDWORD tasksVector = OsAppTable[OSGetCurApp()].tasks;

#if defined(OSEXTPRIORS)
    OSDWORD tasksVector2 = OsAppTable[OSGetCurApp()].tasks2;
#endif    

#if defined(OSEXTPRIORS)
    while((tskInd = OSMask2Task(tasksVector, tasksVector2)) != OSSCHEDULERVECTORSIZE)
#else
    while((tskInd = OSMask2Task(tasksVector)) != OSSCHEDULERVECTORSIZE)
#endif /*defined(OSEXTPRIORS)*/
    {
        if( ( OsTaskTable[tskInd].status & OSTCBNOSUSPENDED ) != 0 )
        {
            OSKillTask(&OsTaskTable[tskInd]);
        }
#if defined(OSEXTPRIORS)
        if(tskInd >= OSSCHMAXBITNUM)
        {
            tasksVector2 &=  ~(OSDWORDMSB >> (tskInd - OSSCHMAXBITNUM));
        }
        else
#endif /*defined(OSEXTPRIORS)*/
        {
            tasksVector &= ~(OSDWORDMSB >> tskInd);
        }
    }
}
#endif/* defined(OSAPPLICATION) */


#if defined(OSTERMINATION) || defined(OSEXTSTATUS)

#if defined(OSRESOURCE) 
/******************************************************************************
 * Function:    OSReleaseTaskResource
 *
 * Description: Releases resources taken by the task
 *
 * Returns:     none
 *
 * Notes:       used for TerminateApplication service
 ******************************************************************************/

OSINLINE void OSReleaseTaskResource(const OSTSKCBPTR taskPtr)
{
    OSResType resPtr;

    while(taskPtr->resources != OSNULLRES)
    {
        resPtr = taskPtr->resources; 

#if defined(OSRESOURCEISR)
        if( resPtr->prio < 0 ) /* prio < 0 - ISR resource */
        {
            OsISRResourceCounter--;
            if( OsISRResourceCounter == 0 )         /* It is the first ISR resource */ 
            {
                OsIsrLevel &= ~OSISRRESOURCELEVEL;  /* unblock scheduler */
            }
        }
        else
#endif
        {
            OSGETTASK( resPtr->prio ) = resPtr->prio2task; 
#if (OSNXTSKS > 0)
            if( ( OSTASKSTATUS( resPtr->prio ) & ( OSTCBNOSUSPENDED | OSTCBWAIT ) ) != OSTCBNOSUSPENDED )
#else
            if( ( OSTASKSTATUS( resPtr->prio ) & OSTCBNOSUSPENDED) == 0 )
#endif
            {
                OSTask2Suspend( resPtr->prio );   /* clear bit in OsScheduleVector */
            }
        }

#if (OSORTIDEBUGLEVEL > 0) || defined(OSEXTSTATUS)
        resPtr->isUsed = 0;
#endif
        taskPtr->resources = resPtr->nextRes;
    }
}
#endif /* defined(OSRESOURCE) */

/***************************************************************************
 * Function:    OSKillRunningTask
 *
 * Description: kills running Task and performs appropriate cleanup 
 *
 * Notes:       shall be called with TP interrupts disabled 
 *              intended for use in the task dispatcher, shall not be
 *              used by protection handlers.
 *
 **************************************************************************/

void OSKillRunningTask( void )
{
    OSRUNNINGSTATUS &= ~(OSTCBNOSUSPENDED); /* clear flags */    
    OSRUNNINGSTATUS |= OSTCBFIRST;          /* set flag that task has no valid context  yet */  

#if defined(OSMEMPROTECTION)
#if (OSNTRUSTEDFUNCTIONS > 0)               /* restore appId in case it was changed */
    OsRunning->appId = OsTaskCfgTable[OsRunning->taskId].appId;
#endif
#endif

#if defined(OSRESOURCE)
    OSReleaseTaskResource(OsRunning);
#endif /* defined(OSRESOURCE) */

    OSResetInternalPrio2( );
    OSREMOVETASK(OsRunning);

#if defined(OSISRENTRYEXIT)
    OsIsrLevel = 0;         /* clear ISR level and context bits */
    OSTPKillIntLockTime();
    OsSuspendLevel = 0;
#else
    OSCLEARCNTX();          /* clear all context bits */
#endif
    OsSuspendLevelAll = 0;      
    OSSETTASKMSR();         /* set MSR for Task, EE = 1 */
}

#endif /* defined(OSTERMINATION) || defined(OSEXTSTATUS) */

#if defined(OSTERMINATION)
/******************************************************************************
 * Function:    OSKillTask
 *
 * Description: kills any task (running or ready) and performs appropriate cleanup 
 *
 * Returns:     n/a
 *
 * Notes:       called with OS and TP interrupts disabled
 *
 ******************************************************************************/

void OSKillTask( OSTSKCBPTR taskPtr )
{
    taskPtr->status &= ~(OSTCBNOSUSPENDED | OSTCBWAIT); /* clear flags */  
    taskPtr->status |= OSTCBFIRST;      /* set flag that task has no valid context yet */
#if defined(OSMEMPROTECTION)
#if (OSNTRUSTEDFUNCTIONS > 0)           /* restore appId in case it was changed */
    taskPtr->appId = OsTaskCfgTable[taskPtr->taskId].appId;
#endif
#endif
    if( taskPtr == OsRunning )
    {
#if defined(OSUSEISRLEVEL)
        if( OSISRLEVELMASKED == 0 )
        {                           /* we are on Task level */
            OsIsrLevel = 0;
#endif
            OSTPResetTaskBudget();

#if defined(OSISRENTRYEXIT)
            OSTPKillIntLockTime();
            OsSuspendLevel = 0;
#endif
            OsSuspendLevelAll = 0;      
            OSDI();
            OSSETTASKMSR();         /* set MSR for Task, EE = 1 */
            OSCLEARCNTX();          /* clear all context bits */

#if defined(OSUSEISRLEVEL)
        }
#endif
        OsKilled |= OSRUNTSKKILLED;
    }
#if (OSNTPTSKBGTS > 0) || (OSNTPTSKRESLOCKTIME > 0)
    else
    {
        OSTPResetReadyTask( taskPtr );
    }
#endif /* (OSNTPTSKBGTS > 0) || (OSNTPTSKRESLOCKTIME > 0) */

#if defined(OSRESOURCE)
    OSReleaseTaskResource( taskPtr );
#endif /* defined(OSRESOURCE) */

#if defined(OSRESOURCE) || defined(OSINRES)
    if( OSGETTASK(taskPtr->taskId) == taskPtr )
#endif
    {              /* if this Task static prio points to this Task   */
        OSTask2Suspend( taskPtr->taskId );
    }
#if defined(OSINRES)
#if defined(OSECC)
    if( ( OSTASKSTATUS( OSPRIO2TASKID( OSTASKRUNPRIO(taskPtr) ) )
        & (OSTCBNOSUSPENDED | OSTCBWAIT)) != OSTCBNOSUSPENDED )    
#else   
    if( ( OSTASKSTATUS( OSPRIO2TASKID( OSTASKRUNPRIO(taskPtr) ) ) & OSTCBNOSUSPENDED) == 0 )    
#endif  
    {               /* if there is no ready task of this prio.  */
        OSTask2Suspend( OSTASKRUNPRIO(taskPtr) );
    }
    if( (OsPrioLink[OSTASKRUNPRIO(taskPtr)] == taskPtr) && (OSTASKRUNPRIO(taskPtr) !=  taskPtr->taskId) )
    {               /* if this prio was occupied by this Task and it is not it's own prio   */
        OsPrioLink[OSTASKRUNPRIO(taskPtr)] = taskPtr->prio2Task;    /* RESETRUNPRIO */
    }
#endif /* defined(OSINRES) */
}
#endif /* defined(OSTERMINATION) */


