#ifndef OSTPAPI_H
#define OSTPAPI_H
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
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/inc/ostpapi.h,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  API for the time protection (AUTOSAR spec. v3)
*
* Notes:        
*
******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#if defined (OSTIMINGPROTECTION)

#include <ostimer.h>

#if defined(OSTIMSTM) || defined(OSTIM2STM)
#error  Error of the OS Configuration: the STM timer should be used only for TP in SC2/4
#endif 

/* TP force interrupt  redirected to Software setable interrupt 5 */
#define OSTPSOFTINT    5u
#define OSTPSOFTINVOKE ((OSDWORD)0x20000)
#define OSTPSOFTCLEAR  ((OSDWORD)0x10000)

/* 
 *  Assignment of STM channels:  
 *  0: Overflow counter (OVF)
 *  1: Interrupt locking time
 *  2: Task/ISR budget
 *  3: Resource locking time
 */
#define OSTPCH_OVF        0u
#define OSTPCH_INTLOCK    1u
#define OSTPCH_BUDGET     2u
#define OSTPCH_RESLOCK    3u

/* Return low part of TP time */
#define OSTPGetTimVal() ( OSSTM_CNT )

#define OSTPTimerClearFlag(ch)  OSSTM_CIR(ch) = OSSTMFLBIT      /* clear flag for the STM channel */
#define OSTPTimerEnable(ch)     OSSTM_CCR(ch) = OSSTMCENBIT     /* enable interrupt from the STM channel */

/* Disable STM channel */
#define OSTPTimerDisable(ch)                    \
    OSSTM_CCR(ch) = 0;                          \
    OSTPTimerClearFlag(ch)

/* Arm STM channel */
#define OSTPTimerArm(ticks,ch)                  \
    OSSTM_CMP(ch)=(ticks);                      \
    OSTPTimerClearFlag(ch);                     \
    OSTPTimerEnable(ch) 

/* Check the STM channel interrupt request */
#define OSTPTimerInterruptRaised(ch) ((OSSTM_CIR(ch) & OSSTMFLBIT) != 0)

/* Force TP interrupt: clear and invoke */
#define OSTPTimerForceClearFlag()    (OSINTC_SSCIR4_7 = OSTPSOFTCLEAR)
#define OSTPTimerInterruptForce(r)              \
    OsTPForceReason |= (r);                     \
    (OSINTC_SSCIR4_7 = OSTPSOFTINVOKE)

/* Reason of TP forced interrupt */
#define OSTPFORCEBUDGET      ((OSBYTE)0x01)
#define OSTPFORCEINTLOCK     ((OSBYTE)0x02)
#define OSTPFORCERESLOCK     ((OSBYTE)0x04)
#define OSTPFORCETSKARRIVAL  ((OSBYTE)0x10)
#define OSTPFORCEISRARRIVAL  ((OSBYTE)0x20)

/* STM freeze mode */
#if defined(OSTPTIMFREEZE)
#define OSTPTIMFRZBIT  OSSTMFREEZEBIT
#else
#define OSTPTIMFRZBIT  0x00
#endif

/* STM control register bits */
#if defined(OSTPTIMPRESCALER)
#define OSTPSTMCR  ((OSTPTIMPRESCALER << 8) | OSTPTIMFRZBIT | OSSTMCENBIT)
#else
#define OSTPSTMCR  (OSTPTIMFRZBIT | OSSTMCENBIT)
#endif


/* Prototypes of TP interrupt handlers */

extern void OSISRTPForced( void );

#if (OSNTPISRARRIV > 0) || (OSNTPTSKARRIV > 0)  /* there is inter-arrival time protection */
/* Interrupt handler for 'overflow' STM channel */
extern void OSISRTPTimerOVF( void );        
#define OSTPStartOVFCh() OSTPTimerArm(0,OSTPCH_OVF)
#else
#define OSTPStartOVFCh()
#endif

#if defined(OSMPC5674F)
/* The STM has feature: three channels (1,2,3) sharing the same interrupt node */
#define OSTPSTM123
#endif

#if !defined(OSTPSTM123)
#if (OSNTPBGTS > 0)
/* Interrupt handler for 'budget' STM channel */
extern void OSISRTPTimerBudget( void );
#endif /* (OSNTPBGTS > 0) */

#if (OSNTPTSKINTLOCKTIME > 0) || (OSNTPISRINTLOCKTIME > 0)
/* Interrupt handler for 'interrupt locking time' STM channel */
extern void OSISRTPTimerIntLock( void );
#endif /* (OSNTPTSKINTLOCKTIME > 0) || (OSNTPISRINTLOCKTIME > 0) */

#if (OSNTPTSKRESLOCKTIME > 0) || (OSNTPISRRESLOCKTIME > 0) 
/* Interrupt handler for 'resource locking time' STM channel */
extern void OSISRTPTimerResLock( void );
#endif /* (OSNTPTSKRESLOCKTIME > 0) || (OSNTPISRRESLOCKTIME > 0) */
#endif /* !defined(OSTPSTM123) */

#if defined(OSTPSTM123)
#if (OSNTPBGTS > 0) || (OSNTPTSKINTLOCKTIME > 0) || (OSNTPISRINTLOCKTIME > 0) || \
    (OSNTPTSKRESLOCKTIME > 0) || (OSNTPISRRESLOCKTIME > 0)
extern void OSISRTPViolation( void );
#endif
#endif /* defined(OSSTM123) */

/* STM shutdown */
#define OSTPTimerShutdown()                     \
    OSSTM_CR = 0;                               \
    OSSTM_CCR(0) = 0;                           \
    OSSTM_CCR(1) = 0;                           \
    OSSTM_CCR(2) = 0;                           \
    OSSTM_CCR(3) = 0;                           \
    OSSTM_CIR(0) = OSSTMFLBIT;                  \
    OSSTM_CIR(1) = OSSTMFLBIT;                  \
    OSSTM_CIR(2) = OSSTMFLBIT;                  \
    OSSTM_CIR(3) = OSSTMFLBIT;                  \
    OSTPTimerForceClearFlag()

/* STM initialization */
#define OSTPTimerInit()                         \
    OSTPTimerShutdown();                        \
    OSSTM_CNT = 1;              /* we prevent OVF interrupt directly after StartOS() */ \
    OSSTM_CR = OSTPSTMCR;                       \
    OSTPStartOVFCh()



/* Nils */
#define OSTPOBJECT0     ((OSObjectType)0)
#define OSTPRESLOCK0    ((OSTPRESLOCK *)0)
#define OSTPLOCK0       OSTPRESLOCK0


/* --- Data --- */

/* Note. In some cases TP uses forced software interrupt invoked with
         MSR(EE)=0. But when MSR(EE) will be 1 a low priority
         interrupt may be ocurred before TP interrupt because of known
         bug in interrupt controller. As a result TP handler cannot
         use OSISRLEVELMASKED to define current TP violator. And so
         some special TP object variables are introduced. */


#if (OSNTPTSKRESLOCKTIME > 0) 
/* RAM memory for TASK/ISR2 resource locking time configurations. */
extern OSTPRESLOCK      OsTPTskResLockTime[OSNTPTSKRESLOCKS];
#endif
#if (OSNTPISRRESLOCKTIME > 0)
/* RAM memory for TASK/ISR2 resource locking time configurations. */
extern OSTPRESLOCK      OsTPISRResLockTime[OSNTPISRRESLOCKS];
#endif


/* --- TP interface macros and functions --- */

#if(OSNAPPMODES > 1)
extern void OSInitializeTP( AppModeType mode );
#else
extern void OSInitializeTP( void );
#endif

/***************************************************************************
 * Fuction: OSTPTimerRemained
 *
 * Description:  return the remained time until the compare event
 *
 * Notes:       OsTPTimVal shall be updated before 
 *
 **************************************************************************/
OSINLINE OSTPTICKTYPE OSTPTimerRemained( int ch )
{                       
    register OSTPTICKTYPE value;

    value = OSSTM_CMP(ch) - OsTPTimVal;

    if( ((OSSTM_CIR(ch)) & OSSTMFLBIT) != 0 )
    {
        value = 0;
    }

    return value;
}

/***************************************************************************
 * Macro: OSTPGetTime64
 *
 * Description:  return full TP time (in 'timval64' variable)
 *
 * Notes:   1. the same macro interface as for DEC timer
 *          2. OsTPTimVal shall be updated before 
 *
 **************************************************************************/
#define OSTPGetTime64(timval64)                                 \
    {                                                           \
        register OSDWORD up;                                    \
                                                                \
        up = OsTPOverflowCnt;                                   \
                                                                \
        if( ((OSSTM_CIR(OSTPCH_OVF)) & OSSTMFLBIT) != 0 )       \
        {                                                       \
            OsTPTimVal = OSSTM_CNT;                             \
            up++;                                               \
        }                                                       \
                                                                \
        (timval64) = ( (OSQWORD)up << 32u ) + OsTPTimVal;       \
    }

#define OSTPGetRemained()     OSTPTimerRemained(OSTPCH_BUDGET)  /* get the remained time on the budget */
#define OSTPResLockRemained() OSTPTimerRemained(OSTPCH_RESLOCK) /* get the remained time on the resource locking time */


#define OSTPTASKOBJECT(task)    OSTP_MKOBJID(OBJECT_TASK, task->taskId)
#define OSTPISROBJECT(isr)      OSTP_MKOBJID(OBJECT_ISR, (isr - &OsIsrTable[0]))

#if (OSNTPTSKRESLOCKTIME > 0) || (OSNTPISRRESLOCKTIME > 0)

/* Start interrupt locking time */
#define OSTPStartResLock(val, obj)                                      \
    OSTPTimerArm((val) + OsTPTimVal, OSTPCH_RESLOCK);                   \
    if( ( OSSTM_CNT - OsTPTimVal ) >= ( OSSTM_CMP(OSTPCH_RESLOCK) - (OsTPTimVal) ) ) \
    {                                                                   \
        OSTPTimerDisable(OSTPCH_RESLOCK);                               \
        OSTPTimerInterruptForce(OSTPFORCERESLOCK);                      \
    }                                                                   \
    OsTPResLockObject = (obj)

/* Reset interrupt locking time */
#define OSTPResetResLock()                      \
    OSTPTimerDisable(OSTPCH_RESLOCK);           \
    OsTPResLockObject = OSTPOBJECT0

#endif /* (OSNTPTSKRESLOCKTIME > 0) || (OSNTPISRRESLOCKTIME > 0) */

#if (OSNTPBGTS > 0) 

/* Reset timing protection execution budget */
#define OSTPResetBudget()                       \
    OSTPTimerDisable(OSTPCH_BUDGET);            \
    OsTPBudgetObject = OSTPOBJECT0

/* Start timing protection execution budget */
#define OSTPStartBudget(val, obj)                                       \
    OSTPTimerArm((val) + OsTPTimVal, OSTPCH_BUDGET);                    \
    if( ( OSSTM_CNT - OsTPTimVal ) >= ( OSSTM_CMP(OSTPCH_BUDGET) - (OsTPTimVal) ) ) \
    {                                                                   \
        OSTPTimerDisable(OSTPCH_BUDGET);                                \
        OSTPTimerInterruptForce(OSTPFORCEBUDGET);                       \
    }                                                                   \
    OsTPBudgetObject = (obj)

#endif /* (OSNTPBGTS > 0) */

#if (OSNTPBGTS > 0) || (OSNTPTSKRESLOCKTIME > 0) || (OSNTPISRRESLOCKTIME > 0)
extern void OSTPStopBudget( void );
#else
#define OSTPStopBudget()
#endif

#if (OSNTPTSKARRIV > 0)
#if defined(OSHOOKPROTECTION)
extern OSBYTE OSTPStartTaskFrame( OSWORD taskId );
extern OSBYTE OSTPStartTaskFrameInAlm( OSWORD taskId );
#else
extern void OSTPStartTaskFrameInAlm( OSWORD taskId );
#define OSTPStartTaskFrame(taskId) OSTPStartTaskFrameInAlm( taskId )
#endif
#else  /* (OSNTPTSKARRIV > 0) */
#define OSTPStartTaskFrame( arg )
#define OSTPStartTaskFrameInAlm( arg )
#endif /* (OSNTPTSKARRIV > 0) */

#if (OSNTPTSKBGTS > 0) || (OSNTPTSKRESLOCKTIME > 0)
/***************************************************************************
 * Function: OSTPResumeTaskBudget
 *
 * Description: Resume timing protection execution budget and resource
 *              locking time when a task is started after preempting
 *
 * Returns: 
 *
 * Notes:
 *
 **************************************************************************/

OSINLINE void OSTPResumeTaskBudget( void )
{
    OsTPTimVal = OSTPGetTimVal();

#if (OSNTPTSKBGTS > 0)
    if( OsRunning->tpExecBudget > 0 )     /* TP budget is applied for this task */
    {
        OSTPStartBudget(OsRunning->tpRemained, OSTPTASKOBJECT(OsRunning));
    }
#endif
#if (OSNTPTSKRESLOCKTIME > 0)
    if( OsRunning->tpResources )  /* there is a resource with started TP */
    {
        OSTPStartResLock( OsRunning->tpResources->tpRemained, OSTPTASKOBJECT(OsRunning) );
    }
#endif
}


/***************************************************************************
 * Function: OSTPStopTaskBudget
 *
 * Description: Stop task timing protection (the budget and/or the resource 
 *              locking time) when a task is preempted
 *
 * Returns: 
 *
 * Notes:
 *
 **************************************************************************/

OSINLINE void OSTPStopTaskBudget( void )
{
#if (OSNTPTSKBGTS > 0) && (OSNXTSKS > 0)
    if( ( OsRunning->status & OSTPWAITEVT ) != OSTPWAITEVT )
    {
#endif
        OsTPTimVal = OSTPGetTimVal();
#if (OSNTPTSKBGTS > 0)
        if( OsRunning->tpExecBudget > 0 )       /* TP budget is applied for this task */
        {
            OsRunning->tpRemained = OSTPTimerRemained( OSTPCH_BUDGET );
            OSTPResetBudget();
        }
#endif
#if (OSNTPTSKRESLOCKTIME > 0)
        if( OsRunning->tpResources )            /* there is a resource with started TP */
        {
            OsRunning->tpResources->tpRemained = OSTPTimerRemained( OSTPCH_RESLOCK );
            OSTPResetResLock();
        }
#endif
#if (OSNTPTSKBGTS > 0) && (OSNXTSKS > 0)
    }
    else   /* the task goes in wait state */
    {
        OsRunning->tpRemained = OsRunning->tpExecBudget;  /* reset task budget */
        OSTPResetBudget();
        /* Note that the queue tpResource must be empty here 
           because of all resources must be released before WaitEvent() */
    }
#endif
}


#if (OSNXTSKS > 0) && (OSNTPTSKBGTS > 0)
/***************************************************************************
 * Function: OSTPRestartTaskBudget
 *
 * Description: Restart task budget for extended tasks 
 *
 * Returns: 
 *
 * Notes:
 *
 **************************************************************************/

OSINLINE void OSTPRestartTaskBudget( void )
{
    if( OsRunning->tpExecBudget > 0 )      /* TP budget is applied for this task */
    {
        OsTPTimVal = OSTPGetTimVal();
        OsRunning->tpRemained  = OsRunning->tpExecBudget;
        OSTPStartBudget(OsRunning->tpRemained, OSTPTASKOBJECT(OsRunning));
    }
}
#else
#define OSTPRestartTaskBudget()
#endif  /* (OSNXTSKS > 0) && (OSNTPTSKBGTS > 0) */

/***************************************************************************
 * Function: OSTPResetTaskBudget
 *
 * Description: Reset task timing protection (the budget and/or the resource 
 *              locking time)
 *
 * Returns: 
 *
 * Notes:
 *
 **************************************************************************/

OSINLINE void OSTPResetTaskBudget( void )
{
#if (OSNTPTSKBGTS > 0)
    OsRunning->tpRemained = OsRunning->tpExecBudget;
    OSTPResetBudget();
#endif

#if (OSNTPTSKRESLOCKTIME > 0)
    OsRunning->tpResources = OSNULLRES;
    OSTPResetResLock();
#endif
}


/***************************************************************************
 * Function: OSTPResetReadyTask
 *
 * Description: Reset task timing protection (the budget and/or the
 *              resource locking time) for task in ready state (not running)
 *              
 * Returns: 
 *
 * Notes:       It used to reset TP fields for the task when the task is not
 *              running and the task is killed
 *
 **************************************************************************/
OSINLINE void OSTPResetReadyTask( OSTSKCBPTR task )
{
#if (OSNTPTSKBGTS > 0)
    task->tpRemained = task->tpExecBudget;      /* reset task budget */
#endif
#if  (OSNTPTSKRESLOCKTIME > 0)
    task->tpResources = OSNULLRES;              /* reset TP resource lock' queue */
#endif
}

#else

#define OSTPStopTaskBudget()
#define OSTPResumeTaskBudget()
#define OSTPResetTaskBudget()
#define OSTPRestartTaskBudget()

#endif /* (OSNTPTSKBGTS > 0) || (OSNTPTSKRESLOCKTIME > 0) */

#if (OSNTPISRARRIV > 0) 
#if defined(OSHOOKPROTECTION)
extern OSBYTE OSTPISRArrivalRate( OS_ISRTYPE *isr );
#else
extern void OSTPISRArrivalRate( OS_ISRTYPE *isr );
#endif
#else
#define OSTPISRArrivalRate( arg ) 
#endif  /* (OSNTPISRARRIV > 0) */

#if ((OSNTPBGTS > 0) || (OSNTPTSKRESLOCKTIME > 0) || (OSNTPISRRESLOCKTIME > 0) ) && !defined(OSNOISR2) 
/***************************************************************************
 * Function: OSTPStartISRBudget
 *
 * Description: Start timing protection for ISR:
 *             - the execution budget
 *             - resource locking time
 *
 * Returns: 
 *
 * Notes:
 *
 **************************************************************************/

OSINLINE void OSTPStartISRBudget( OS_ISRTYPE *isr )
{
    OSTPStopBudget();                   /* stop TP for preempted task or ISR2 */

#if (OSNTPISRBGTS > 0)
    if( isr->tpExecBudget > 0 )         /* TP budget is applied for this ISR2 */
    {
        OsTPTimVal = OSTPGetTimVal();
        OSTPStartBudget( isr->tpExecBudget, OSTPISROBJECT(isr) );
    }
#endif

#if (OSNTPISRRESLOCKTIME > 0)
    isr->tpResources = OSNULLRES;
#endif
}
#else
#define OSTPStartISRBudget( arg )
#endif /* ((OSNTPBGTS > 0) || (OSNTPTSKRESLOCKTIME > 0) || (OSNTPISRRESLOCKTIME > 0) ) && !defined(OSNOISR2) */ 


#if (OSNTPISRBGTS > 0) || (OSNTPISRRESLOCKTIME > 0)
/***************************************************************************
 * Function: OSTPResetISRBudget
 *
 * Description: Reset the ISR2 budget
 *
 * Returns: 
 *
 * Notes:
 *
 **************************************************************************/

OSINLINE void OSTPResetISRBudget( void )
{
#if (OSNTPISRBGTS > 0)
    OSTPResetBudget();
#endif

#if (OSNTPISRRESLOCKTIME > 0)
    OSTPResetResLock();
#endif
}

#define OSTPKillISRBudget()  OSTPResetISRBudget()

/***************************************************************************
 * Function: OSTPResumeISRBudget
 *
 * Description: Resume the ISR2 budget and/or the resource locking time
 *
 * Returns: 
 *
 * Notes:
 *
 **************************************************************************/

OSINLINE void OSTPResumeISRBudget( OS_ISRTYPE* isr )
{
    OsTPTimVal = OSTPGetTimVal();

#if (OSNTPISRBGTS > 0)
    if( isr->tpExecBudget > 0 ) /* TP budget is applied for this ISR2 */
    {
        OSTPStartBudget( isr->tpRemained, OSTPISROBJECT(isr) );
    }
#endif
#if (OSNTPISRRESLOCKTIME > 0)
    if( isr->tpResources )  /* there is a resource with started TP */
    {
        OSTPStartResLock( isr->tpResources->tpRemained, OSTPISROBJECT(isr) );
    }
#endif
}
#else

#define OSTPResumeISRBudget( arg )
#define OSTPResetISRBudget()
#define OSTPKillISRBudget()

#endif /* (OSNTPISRBGTS > 0) || (OSNTPISRRESLOCKTIME >0) */


#if (OSNTPTSKINTLOCKTIME > 0) || (OSNTPISRINTLOCKTIME > 0)

/* Start interrupt locking time */
#define OSTPStartIntLock(val, obj)                                      \
    OSTPTimerArm((val) + OsTPTimVal, OSTPCH_INTLOCK);                   \
    if( ( OSSTM_CNT - OsTPTimVal ) >= ( OSSTM_CMP(OSTPCH_INTLOCK) - (OsTPTimVal) ) ) \
    {                                                                   \
        OSTPTimerDisable(OSTPCH_INTLOCK);                               \
        OSTPTimerInterruptForce(OSTPFORCEINTLOCK);                      \
    }                                                                   \
    OsTPIntLockObject = (obj)



/***************************************************************************
 * Function: OSTPStartIntLockTime
 *
 * Description: Start timing protection for OS interrupt locking time
 *
 * Returns: 
 *
 * Notes:
 *
 **************************************************************************/

OSINLINE void OSTPStartIntLockTime( void )
{
    OsTPTimVal = OSTPGetTimVal();

    if( OSISRLEVELMASKED == 0 )
    {
#if (OSNTPTSKINTLOCKTIME > 0)
        if( OsRunning->tpIntLockTime > 0 )
        {
            OSTPStartIntLock( OsRunning->tpIntLockTime, OSTPTASKOBJECT(OsRunning) );
        }
#endif
    }
    else 
    {
#if (OSNTPISRINTLOCKTIME > 0)
        OSTPTICKTYPE locktime;
        OS_ISRTYPE *isr =  OsIsrArray[OSISRLEVELMASKED - 1];
        locktime = isr->tpIntLockTime;
        if( locktime > 0 )
        {
            OSTPStartIntLock( locktime, OSTPISROBJECT(isr) );
        }
#endif
    }
}

/***************************************************************************
 * Macro: OSTPKillIntLockTime
 *
 * Description: Reset timing protection for OS interrupt lock time
 *
 * Returns: 
 *
 * Notes:
 *
 **************************************************************************/
#define OSTPKillIntLockTime()                   \
    OSTPTimerDisable(OSTPCH_INTLOCK);           \
    OsTPIntLockObject = OSTPOBJECT0

#else

#define OSTPStartIntLockTime()
#define OSTPKillIntLockTime()

#endif /* (OSNTPTSKINTLOCKTIME > 0) || (OSNTPISRINTLOCKTIME > 0) */

#if (OSNTPTSKRESLOCKTIME > 0) || (OSNTPISRRESLOCKTIME > 0)

#if (OSNTPTSKRESLOCKTIME > 0)
extern void OSTPStartTaskResLockTime( OSWORD resInd );
extern void OSTPResetTaskResLockTime( OSResType resRef );
#endif
#if (OSNTPISRRESLOCKTIME > 0)
extern void OSTPStartISRResLockTime( OSWORD resInd );
extern void OSTPResetISRResLockTime( OSResType resRef );
#endif

/***************************************************************************
 * Function: OSTPStartResLockTime
 *
 * Description: Start resource locking time in a task or ISR2
 *
 * Returns: 
 *
 * Notes:
 *
 **************************************************************************/
OSINLINE void OSTPStartResLockTime( OSWORD resInd )
{
#if defined(OSISRENTRYEXIT)
    if( OSISRLEVELMASKED == 0 )
    {
#endif
#if (OSNTPTSKRESLOCKTIME > 0)
        OSTPStartTaskResLockTime( resInd );
#endif
#if defined(OSISRENTRYEXIT)
    }
    else 
    {
#if (OSNTPISRRESLOCKTIME > 0)
        OSTPStartISRResLockTime( resInd );
#endif
    }
#endif
}

/***************************************************************************
 * Function: OSTPResetResLockTime
 *
 * Description: Reset resource locking time in a task or ISR2
 *
 * Returns: 
 *
 * Notes:
 *
 **************************************************************************/
OSINLINE void OSTPResetResLockTime( OSResType resRef )
{
#if defined(OSISRENTRYEXIT)
    if( OSISRLEVELMASKED == 0 )
    {
#endif
#if (OSNTPTSKRESLOCKTIME > 0)
        OSTPResetTaskResLockTime( resRef );
#endif
#if defined(OSISRENTRYEXIT)
    }
    else 
    {
#if (OSNTPISRRESLOCKTIME > 0)
        OSTPResetISRResLockTime( resRef );
#endif
    }
#endif
}
#else
#define OSTPStartResLockTime( arg )
#define OSTPResetResLockTime( arg )
#endif /* (OSNTPTSKRESLOCKTIME > 0) || (OSNTPISRRESLOCKTIME > 0) */

#else

/* Empty TP interface macros */
#define OSTPStartTaskFrame( arg )
#define OSTPStartTaskFrameInAlm( arg )
#define OSTPResumeTaskBudget()
#define OSTPResetTaskBudget()
#define OSTPStopTaskBudget()
#define OSTPRestartTaskBudget()
#define OSTPStartISRBudget( arg )
#define OSTPResetISRBudget()
#define OSTPKillISRBudget()
#define OSTPResumeISRBudget( arg )
#define OSTPStopBudget()
#define OSTPStartIntLockTime()
#define OSTPKillIntLockTime()
#define OSTPStartResLockTime( arg )
#define OSTPResetResLockTime( arg )
#define OSTPISRArrivalRate( arg ) 

#endif /* defined (OSTIMINGPROTECTION) */

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* OSTPAPI_H */
