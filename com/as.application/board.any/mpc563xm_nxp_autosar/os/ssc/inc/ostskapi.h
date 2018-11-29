#ifndef OSTSKAPI_H
#define OSTSKAPI_H
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
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/inc/ostskapi.h,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  API for OSEK OS task management         
*
* Notes:        
*
******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/*  Configuration Data  */

#if defined(OSUSETCB) 

extern const OSTSK OsTaskCfgTable[OSNTSKS];    /* TaskConfiguration table  */

#else   /* defined(OSUSETCB) */

extern const OSTASKENTRY OsTaskEntry[OSNTSKS];       /* Tasks' entries */      
extern const OSBYTE      OsTaskProperty[OSNTSKS];    /* Tasks' properties */
extern const OSBYTE      OsTaskRunPrio[OSNTSKS];     /* Tasks' runprio */

#if (OSNAPPMODES > 1)            
extern const OSBYTE      OsTaskAutostart[OSNTSKS];   
#endif

#endif  /* defined(OSUSETCB) */

/*  Constants */

#define RUNNING         ((TaskStateType)0)      /* Constant of data type TaskStateType for task state running.  */
#define WAITING         ((TaskStateType)1)      /* Constant of data type TaskStateType for task state waiting.  */
#define READY           ((TaskStateType)2)      /* Constant of data type TaskStateType for task state ready.    */
#define SUSPENDED       ((TaskStateType)3)      /* Constant of data type TaskStateType for task state suspended.    */

/* Task properties   */
#define OSTSKACTIVATE   ( (OSBYTE)0x08 )        /* Activate task during system start-up */
#define OSTSKNONPREEMPT ( (OSBYTE)0x40 )        /* Non-preemptive task  */
#define OSTSKEXTENDED   ( (OSBYTE)0x80 )        /* Extended task    */

/* Task status      */
/*#define OSTCBSCHEDULER  ( (OSBYTE)0x01 )*/        /* (0x01) Task has allocated (locked) the scheduler */
#define OSTCBFIRST      ( (OSBYTE)0x02 )        /* (0x02) First run of task (context must be built) */
#define OSTCBWAIT       ( (OSBYTE)0x04 )        /* (0x04) Task is waiting for event                 */
#define OSTCBNOSUSPENDED ( (OSBYTE)0x10 )       /* Task is not in suspended state, for Ext. Status  */
                        
#if defined(OSTIMINGPROTECTION) && (OSNTPTSKBGTS > 0) && (OSNXTSKS > 0) 
#define OSTPWAITEVT         ( (OSBYTE)0x20 )    /* Task is inside WaitEvent function    */
#define OSTPSetWAITEVT()    ( OsRunning->status |= OSTPWAITEVT )
#define OSTPClrWAITEVT()    ( OsRunning->status &= ~OSTPWAITEVT )
#else
#define OSTPSetWAITEVT()
#define OSTPClrWAITEVT()
#endif
    
#define OSTCBSTART      ((OSBYTE)(OSTCBFIRST | OSTCBNOSUSPENDED))
/*#define OSTCBNONPREEMPT OSTSKNONPREEMPT */        /* (0x40) Non-preemptive task                       */
#define OSTCBEXTENDED   OSTSKEXTENDED           /* (0x80) Extended task                             */

#if (OSORTIDEBUGLEVEL > 0) || defined(OSSTKCHECK) || defined(OSMEMPROTECTION)
#define OSSTKNOASSIGNED     0xFFFFu
#endif

extern OSDWORD OSSTACKTOP[];    /* _stack_addr for CW and __SP_INIT for DIAB */
extern OSDWORD OSSTACKBOTTOM[]; /* _stack_end for CW and  __SP_END for DIAB */

#if defined(OSUSETCB)
#define _OSNULLTASK  (OSNTSKS)
#define OSNULLTASKPTR ((OSTSKCBPTR)0)
#else   /* defined(OSUSETCB) */
#define _OSNULLTASK  (OSSCHWIDE*OSSCHMAXBITNUM)      /* Task Id when no activated tasks */
#endif  /* defined(OSUSETCB) */

#define OSNULLTASK  _OSNULLTASK     

#define INVALID_TASK  OS_MKOBJID(OBJECT_TASK,OSNULLTASK)    /* Invalid task (no active task)    */


/*  OSEK naming conventions */

#if defined(OSBCC)

#if defined(OSNOFASTTERMINATE) 
#define TASK( TaskName ) void Func##TaskName( void )
#else
#define TASK( TaskName ) OSTASKTYPE Func##TaskName( void )
#endif

#if defined(OSEXTPRIORS)
#define OSCHECKTASKSTATUS(taskId)  \
    ( (taskId < OSSCHMAXBITNUM) ? \
    ((OsSchedulerVector1 &  ( OSDWORDMSB >> taskId )) ? 1 : 0) : \
    ((OsSchedulerVector2 &  ( OSDWORDMSB >> ((OSTASKTYPE)taskId - OSSCHMAXBITNUM))) ? 1 : 0 ))
#else   /* defined(OSEXTPRIORS) */
#define OSCHECKTASKSTATUS(taskId) \
    (( OsSchedulerVector1 & ( OSDWORDMSB >> (taskId) )) ? 1 : 0 )
#endif  /* defined(OSEXTPRIORS) */

#endif  /* defined(OSBCC)  */

#if defined(OSECC)
#define TASK( TaskName ) void Func##TaskName( void )
#endif  /* defined(OSECC)  */

/*  Private OS Services */
#if defined(OSSYSSTKCHECK) && defined(OSUSETOS)
extern void OSCheckStack( void );
#else
#define OSCheckStack()
#endif

#if defined(OSTIMINGPROTECTION)
#if defined(OSSYSSTKCHECK)

#define OSCHECKSTACK_TP()                           \
    OSCheckStack();                                 \
    if( (OsKilled & OSRUNTSKKILLED) != 0 )          \
    {                                               \
        OsKilled &= ~OSRUNTSKKILLED;                \
    }                                               \
    else                                            \
    {                                               \
        OSTPStopTaskBudget();                       \
    }
#else
#define OSCHECKSTACK_TP() OSTPStopTaskBudget()
#endif 

#else  /* defined(OSTIMINGPROTECTION) */

#if defined(OSSYSSTKCHECK)
#define OSCHECKSTACK_TP()   OSCheckStack();  OsKilled &= ~OSRUNTSKKILLED
#else
#define OSCHECKSTACK_TP()
#endif 

#endif /* defined(OSTIMINGPROTECTION) */

#if defined(OSSC1)
#if defined(OSSYSSTKCHECK)
extern void OSCheckMainStack( void );
#else
#define OSCheckMainStack()
#endif
#endif /* defined(OSSC1) */

#if defined(OSSYSSTKCHECK) && defined(OSUSEISRSTACK)
extern void OSCheckIsrStack( void );
#else
#define OSCheckIsrStack()
#endif


#if (OSORTIDEBUGLEVEL > 0) || defined(OSSTKCHECK)
extern OSWORD OSGetUsedBytes( const OSDWORD* start, unsigned short num );

#if !defined(OSSTKCHECKPATTERN)
#define OSSTKCHECKPATTERN  0x55555555U          /* Pattern to fill the stack area */
#endif
#if !defined(OSORTISTACKPATTERN)
#define OSORTISTACKPATTERN  OSSTKCHECKPATTERN
#endif  /* !defined(OSORTISTACKPATTERN) */


/***************************************************************************
 * Macro:       OSSTKSETGUARD, OSSTKINVALID
 *
 * Description: initialize, check stack patterns 
 *
 * Notes:       pattern size may be 1 or 2 or 4 long words
 *
 **************************************************************************/

#if OSSTKCHECKPATTERNSIZE == 1
#define OSSTKINVALID(ptr) (*(ptr) != OSSTKCHECKPATTERN)
#define OSSTKSETGUARD(ptr) *(ptr) = OSSTKCHECKPATTERN
#elif OSSTKCHECKPATTERNSIZE == 2
#define OSSTKINVALID(ptr) (((ptr)[0] != OSSTKCHECKPATTERN) || ((ptr)[1] != OSSTKCHECKPATTERN))
#define OSSTKSETGUARD(ptr) (ptr)[0] = OSSTKCHECKPATTERN; (ptr)[1] = OSSTKCHECKPATTERN
#elif OSSTKCHECKPATTERNSIZE == 4
#define OSSTKINVALID(ptr) \
       ((((ptr)[0] != OSSTKCHECKPATTERN) || ((ptr)[1] != OSSTKCHECKPATTERN)) || \
        (((ptr)[2] != OSSTKCHECKPATTERN) || ((ptr)[3] != OSSTKCHECKPATTERN)))
#define OSSTKSETGUARD(ptr) \
        (ptr)[0] = OSSTKCHECKPATTERN; (ptr)[1] = OSSTKCHECKPATTERN; \
        (ptr)[2] = OSSTKCHECKPATTERN; (ptr)[3] = OSSTKCHECKPATTERN
#endif

#endif  /* (OSORTIDEBUGLEVEL > 0) || defined(OSSTKCHECK) */


/*  Public OS Services  */

#define DeclareTask(TaskID) extern OSBYTE osdummy

extern StatusType OS_ActivateTask( TaskType taskId );

#if defined(OSBCC) 
#if defined(OSNOFASTTERMINATE) 
extern StatusType OS_TerminateTask( void );
extern StatusType OS_ChainTask( TaskType taskId );
#else
#define TerminateTask() return( OSNULLTASK )
#define ChainTask( taskId )  return( (taskId) )
#endif
#endif  /* defined(OSBCC)  */

#if defined(OSECC) 
extern StatusType OS_TerminateTask( void );
extern StatusType OS_ChainTask( TaskType taskId );
#endif

extern StatusType OS_GetTaskID( TaskRefType taskIdRef );
extern StatusType OS_GetTaskState( TaskType taskId, TaskStateRefType stateRef );

#if defined(OSMEMPROTECTION)

OSINLINE  StatusType ActivateTask( TaskType taskId )
{
    return OSServiceCall1( StatusType, taskId, ActivateTask );
}

OSINLINE  StatusType TerminateTask( void )
{
    return OSServiceCall0( StatusType, TerminateTask );
}

OSINLINE StatusType ChainTask( TaskType taskId ) 
{
    return OSServiceCall1( StatusType, taskId, ChainTask );
}

OSINLINE StatusType GetTaskID( TaskRefType taskIdRef )
{
    return OSServiceCall1( StatusType, taskIdRef, GetTaskID );
}

OSINLINE StatusType GetTaskState( TaskType taskId, TaskStateRefType stateRef )
{
    return OSServiceCall2( StatusType, taskId, stateRef, GetTaskState );
}

#else /* OSMEMPROTECTION */

#define ActivateTask(taskId)           OS_ActivateTask(taskId)

#if defined(OSNOFASTTERMINATE)
#define TerminateTask()                OS_TerminateTask()
#define ChainTask(taskId)              OS_ChainTask(taskId)
#endif

#define GetTaskID(taskIdRef)           OS_GetTaskID(taskIdRef)
#define GetTaskState(taskId, stateRef) OS_GetTaskState(taskId, stateRef)

#endif /* OSMEMPROTECTION */



#if (OSORTIDEBUGLEVEL > 0) || defined(OSSTKCHECK)
extern OSWORD GetRunningStackUsage( void );
extern OSWORD GetStackUsage( TaskType taskId );
#endif

#if defined(OSTERMINATION)
extern void OSKillTask( OSTSKCBPTR taskPtr );
#endif

#if defined(OSTERMINATION) || defined(OSEXTSTATUS)
extern void OSKillRunningTask( void );
#endif

#if defined(OSAPPLICATION)
extern void OSKillAppTasks(void);
#endif

/******************************************************************************
 * inline function: OSResetInternalPrio
 * Description:     clears bit in scheduler vector if there is no OTHER ready 
 *                  task of running priority, resets Task prio to assigned
 * Returns:         none
 ******************************************************************************/
#if defined(OSINRES)
OSINLINE void OSResetInternalPrio( void )
{
    if( OSCLEARRUNPRIOBITISNECESSARY( ) )
    {                                                   /* if there is no ready task of this prio. */
        OSTask2Suspend( OSTASKRUNPRIO( OsRunning ));    /* then clear bit in OsScheduler           */
    }
    OSRESETRUNPRIO( );
}
#else
#define OSResetInternalPrio( )
#endif

/******************************************************************************
 * inline function: OSResetInternalPrio2
 * Description:     clears bit in scheduler vector if there is no ready task
 *                  of running priority, resets Task prio to assigned
 * Returns:         none
 ******************************************************************************/
#if defined(OSINRES)
#if defined(OSECC)
OSINLINE void OSResetInternalPrio2( void )
{
    if( (OSTASKSTATUS( OSPRIO2TASKID( OSTASKRUNPRIO( OsRunning ) ) ) 
        & (OSTCBNOSUSPENDED | OSTCBWAIT)) != OSTCBNOSUSPENDED )    
    {                                           /* if there is no ready task of this prio.  */
        OSTask2Suspend( OSTASKRUNPRIO( OsRunning ));    /* then clear bit in OsScheduler         */
    }
    OSRESETRUNPRIO();       
}
#else   /* defined(OSECC) */
OSINLINE void OSResetInternalPrio2( void )
{
    if( (OSTASKSTATUS( OSPRIO2TASKID( OSTASKRUNPRIO( OsRunning ) ) ) & OSTCBNOSUSPENDED) == 0 )    
    {                                           /* if there is no ready task of this prio.  */
        OSTask2Suspend( OSTASKRUNPRIO( OsRunning ));    /* then clear bit in OsScheduler         */
    }
    OSRESETRUNPRIO();       
}
#endif  /* defined(OSECC) */
#else
#define OSResetInternalPrio2( )
#endif


#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* OSTSKAPI_H */
