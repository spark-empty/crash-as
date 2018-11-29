#define OSISR_C

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
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/src/osisr.c,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* Functions:    
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:    AUTOSAR OS ISR management    
*
* Notes:        
*
******************************************************************************/

#define OS_INTERNAL 1
#include    <os.h>
#undef OS_INTERNAL

#define OSTEXT_START_SEC_CODE
#include "ossections.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "ossections.h"



/* Prototypes */
void OSInterruptDispatcher1( void );

#if defined(OSE200Z6) || defined(OSE200Z3) || defined(OSE200Z4) || defined(OSE200Z7)
#if defined(OSCWPPC)
OSASM void OSInitIVORS( void );
#endif
#endif

/*    Private OS Services    */

/***************************************************************************
 * Function :   OSISRException
 *
 * Description: ISR for catching unregistered interrupts
 *
 * Notes:       called only if unregistered interrupt occured 
 *
 **************************************************************************/

void OSISRException( void )          
{
    OSShutdownOS( E_OS_SYS_FATAL );
}

#if !defined(OSNOISR2)
#if !defined(OSSC1)
/******************************************************************************
 * function:      OSKillRunningISR(void)
 *
 * Description: kills ISR2 that caused ProtectionHook 
 *
 * Returns: none 
 *
 * Notes:   it is called from protection handler only
 ******************************************************************************/
void OSKillRunningISR(void) 
{
    OSTPKillISRBudget();

#if defined(OSRESOURCEISR)
    OSReleaseISRResources( &(OsIsrArray[OSISRLEVELMASKED - 1]->resources) );
#endif /* defined(OSRESOURCEISR) */

    OsIsrArray[OSISRLEVELMASKED-1]->isKilled = OSTRUE;

    OSTPKillIntLockTime();
    OsSuspendLevel = 0;
    OsSuspendLevelAll = 0;      
    OSCLEARCNTX();          /* clear all context bits */
}
#endif /* !defined(OSSC1) */

#if defined(OSTERMINATION)
/******************************************************************************
 * Function:      OSKillISR
 *
 * Description: kills given ISR2  
 *
 * Returns: none 
 *
 * Notes:       OsIsrLevel is not changed
 ******************************************************************************/
void OSKillISR( OS_ISRTYPE* isr )
{
#if defined(OSAPPLICATION)
#if (OSNTRUSTEDFUNCTIONS > 0)           /* restore appId in case it was changed */
    isr->appId = OsIsrCfg[OsIsr[isr->index]].appId;
#endif
#endif
    if( isr == OsIsrArray[OSISRLEVELMASKED-1] )   /* running ISR */
    {
        OSTPKillISRBudget();
        OSTPKillIntLockTime();
        OsSuspendLevel = 0;
        OsSuspendLevelAll = 0;      
        OSCLEARCNTX();          /* clear all context bits */
    }

#if defined(OSRESOURCEISR)
    OSReleaseISRResources(&(isr->resources)); 
#endif /* defined(OSRESOURCEISR) */
    isr->isKilled = OSTRUE;
}

#endif /* defined(OSTERMINATION) */

#endif /* !defined(OSNOISR2) */


#if defined(OSE200Z6) || defined(OSE200Z3) || defined(OSE200Z4) || defined(OSE200Z7)
/***************************************************************************
 * Function : OSInitIVORS
 *
 * Description: initializes all IVORS to point to vector table
 *
 * Returns: none
 *
 **************************************************************************/

#if defined(OSCWPPC)
OSASM void OSInitIVORS( void )
{
    extern char VTABLE[];
    nofralloc
        
#endif

#if defined(OSGHSPPC) || defined(OSDIABPPC)
OSASM void OSInitIVORS( void )
{
#endif 

    e_lis       r0, VTABLE@ha   
    e_add16i    r0, r0, VTABLE@l
    e_rlwinm    r0, r0, 0, 16, 27
    mtspr       IVOR0, r0  /* IVOR0 400 Critical input                                           */
    e_add16i    r3, r0, 0x010
    mtspr       IVOR1, r3  /* IVOR1 401 Machine check                                            */
    e_add16i    r3, r0, 0x020
    mtspr       IVOR2, r3  /* IVOR2 402 Data storage                                             */
    e_add16i    r3, r0, 0x030
    mtspr       IVOR3, r3  /* IVOR3 403 Instruction storage                                      */
    e_add16i    r3, r0, 0x040
    mtspr       IVOR4, r3  /* IVOR4 404 External input                                           */
    e_add16i    r3, r0, 0x050
    mtspr       IVOR5, r3  /* IVOR5 405 Alignment                                                */
    e_add16i    r3, r0, 0x060
    mtspr       IVOR6, r3  /* IVOR7 406 Program                                                  */
    e_add16i    r3, r0, 0x070
    mtspr       IVOR7, r3  /* IVOR7 407 Floating-point unavailable                               */
    e_add16i    r3, r0, 0x080
    mtspr       IVOR8, r3  /* IVOR8 408 System call                                              */
    e_add16i    r3, r0, 0x090
    mtspr       IVOR9, r3  /* IVOR9 409 Auxiliary processor unavailable. Not used by the e200z6. */
    e_add16i    r3, r0, 0x0A0
    mtspr       IVOR10, r3 /* IVOR10 410 Decrementer                                             */
    e_add16i    r3, r0, 0x0B0
    mtspr       IVOR11, r3 /* IVOR11 411 Fixed-interval timer interrupt                          */
    e_add16i    r3, r0, 0x0C0
    mtspr       IVOR12, r3 /* IVOR12 412 Watchdog timer interrupt                                */
    e_add16i    r3, r0, 0x0D0
    mtspr       IVOR13, r3 /* IVOR13 413 Data TLB error                                          */
    e_add16i    r3, r0, 0x0E0
    mtspr       IVOR14, r3 /* IVOR14 414 Instruction TLB error                                   */
    e_add16i    r3, r0, 0x0F0
    mtspr       IVOR15, r3 /* IVOR15 415 Debug                                                   */

                           /* IVOR16-IVOR31 - Reserved for future architectural use              */

    e_add16i    r3, r0, 0x100
    mtspr       IVOR32, r3 /* IVOR32 528 SPE APU unavailable                                     */
    e_add16i    r3, r0, 0x110
    mtspr       IVOR33, r3 /* IVOR33 529 SPE floating-point data exception                       */
    e_add16i    r3, r0, 0x120
    mtspr       IVOR34, r3 /* IVOR34 530 SPE floating-point round exception                      */
#if defined(OSCWPPC) 
    se_blr
#endif

}

#endif /* defined(OSE200Z6) || defined(OSE200Z3) || defined(OSE200Z4) || defined(OSE200Z7) */

/******************************************************************************
 * Function:    OSInitializeISR
 *
 * Description: Initializes ISRs
 *
 * Returns:     none
 *
 * Notes: 
 ******************************************************************************/
void OSInitializeISR(void)
{
    extern char VTABLE[];

    OSDWORD                 i;

#if OSNISR > 0
    const OSISRCFGTYPE      *isrCfgPtr;
    OS_ISRTYPE              *isrTablePtr;

    isrCfgPtr = &(OsIsrCfg[0]);
    isrTablePtr = &(OsIsrTable[0]);

    for(i = 0; i < OSNISR+1; ++i, ++isrCfgPtr, ++isrTablePtr)
    {

#if defined(OSAPPLICATION)
        isrTablePtr->appMask = isrCfgPtr->appMask;
        isrTablePtr->appId = isrCfgPtr->appId;
#endif
#if defined(OSMEMPROTECTION)
        isrTablePtr->stackPtr = isrCfgPtr->stackPtr - OSSTKADDS;
        isrTablePtr->isrBos = isrCfgPtr->isrBos;   
#endif /* defined(OSMEMPROTECTION) */
#if defined(OSTERMINATION)
        isrTablePtr->isKilled = OSFALSE;
#endif
#if defined(OSUSERESLINK)
        isrTablePtr->resources = OSNULLRES;
#endif
        isrTablePtr->userISR = isrCfgPtr->userISR;
        isrTablePtr->type = isrCfgPtr->type;
        isrTablePtr->index = isrCfgPtr->index;
        isrTablePtr->prio = isrCfgPtr->prio & ((OSBYTE)0xf);  /* 0xf mask clears PRC_SEL bits */
    }

#endif /*OSNISR > 0 */
    
#if defined(OSRESOURCEISR)

    OsISRResourceCounter = 0;       /* clear ISR resource counter      */

#endif

#if defined(OSUSEISRLEVEL)
    OsIsrLevel = 0;                 /* no ISR/critical section running */
#endif

#if defined(OSISRENTRYEXIT)
    OsSuspendLevel = 0;             /* level of the nested Suspend/Resume pairs */
#endif

#if defined(OSE200Z6) || defined(OSE200Z3) || defined(OSE200Z4) || defined(OSE200Z7)
    OsSetIVPR((OSDWORD)VTABLE & 0xFFFF0000ul); /* Set Interrupt vector prefix */
    OSInitIVORS();
#else
    OsSetIVPR((OSDWORD)VTABLE);                /* Set Interrupt vector prefix, VTABLE address must be aligned
                                                  for Z1, Z0 cores to a 4-Kbyte boundary */
#endif

    /* Machine check enable (ME=1) */
    OSSETMSR(OSGETMSR()|OSMSR_ME);  /* MPU violation events and another 'bus errors' will be handled as exceptions (not CPU reset) */

    for( i=0; i<OSNINTC; i++ )
    {
        OSCLEAR_INT_PSRX( i );
#if (OSNISR > 0)
        if( OsIsr[i] != OSNISR )
        {
            OSSET_INT_PSRX( i, OsIsrTable[OsIsr[i]].prio );
        }
#endif
    }

    OSINTC_MCR &= ~OSINTC_MCR_HVEN;      /* Software vector mode            */
    OSINTC_MCR &= ~OSINTC_MCR_VTES;      /* Vector Table Entry Size = 4     */

    OSINTC_IACKR = 0;

    OSOrtiSetISRId( OSINVALID_ISR );     /* no running ISR                  */

    OSISRALLON();                        /* Enable all Interrupts (IPL = 0) */ 
}

#if defined(OSISRENTRYEXIT)

#if defined(OSSC1)
#if defined(OSBCC)
#if !defined(OSNOFASTTERMINATE)
/***************************************************************************
 * Function:    OSLeaveISR
 *
 * Description: Leave ISR and switch tasks' context, if needed
 *
 * Returns:     none
 *
 * Notes: 
 *
 **************************************************************************/
void OSLeaveISR( void )
{
#if defined(OSRESOURCE)
    OSTSKCBPTR            osOldRunning;         /* currently running task    */
#else   /* defined(OSRESOURCE */
    OSTASKTYPE            osOldRunning;         /* currently running task    */
#endif  /* defined(OSRESOURCE) */

    OSTASKTYPE            osChainTask;          /* task to be chain    (if any)    */

/* Check condition of dispatching, if dispatching is not needed then return, else dispatch  */
#if defined(OSMIXPREEMPT)
    if( OSHASRUNNINGTASK )               /* if interrupted task is not idle loop */
    {
        if( (OSRUNNINGSTATUS & OSTSKNONPREEMPT ) != 0 )
        {
            return;                             /* if non-preemptive task was interrupted, then no launch    */
        }
    }
#elif defined(OSNOPREEMPT)
    if( OSHASRUNNINGTASK )    
    {
        return;                                 /* for non-preemptive system no Task switch    */
    }                                           /* if interrupt occured while any task was running    */ 
#elif defined(OSFULLPREEMPT)
    /* nothing here */
#endif  /* defined(OSMIXPREEMPT) */

    OSEHI();
    osOldRunning = OsRunning;                   /* save running task (if any)    */

#if defined(OSHOOKPOSTTASK)
    if( OSHASRUNNINGTASK )    
    {
        OSPostTaskHook();       /* user hook or empty macro */
    }
#endif  /* defined(OSHOOKPOSTTASK) */

    while( ( OsRunning = OSGETMAXPRIOTASK) != osOldRunning ) /* cycle to launch all preempting tasks    */
    {
        OSOrtiSetRunningId();
        OSSETRUNPRIO();        /* set internal resource priotity, if any       */
        OSOrtiResetIdOnExit( );                 /* set that the caller service is finished */
        OSCallPreTaskHook();
        OSSETTASKMSR();                         /* set MSR for Task, EE = 1 */
        OSEI(); 
        osChainTask = OSCallTask();             /* execute the task, and get the ID of chained task */
        OSDI();
        OSCheckMainStack();                     /* check main stack overflow */
        OSResetInternalPrio2( ); 

#if defined(OSRESOURCE) || defined(OSINRES)
        OSRUNNINGSTATUS &= (~OSTCBNOSUSPENDED); /* clear "nonsuspended" flag */
#endif  /* defined(OSRESOURCE) || defined(OSINRES) */

        OSREMOVETASK(OsRunning);

        if( osChainTask != OSNULLTASK )         /* if some task needs to be chained    */
        {
            OSTask2Ready( osChainTask );        /* then readies chained task    */        
        }

        OSPostTaskHook();                       /* user hook or empty macro */
    }
    OSOrtiSetRunningId();
    OSSETBITRUNPRIO();      /* Restore runprio bit */
    
    OSOrtiResetIdOnExit( );                     /* set that the caller service is finished */
    OSPreTaskHook();        /* call user hook           */
    OSDHI();
    return;
}
#else  /* !defined(OSNOFASTTERMINATE) */
/***************************************************************************
 * Function:    OSLeaveISR
 *
 * Description: Leave ISR and switch tasks' context, if needed
 *
 * Returns:     none
 *
 * Notes:       for SC1, BCC1, NOFASTTERMINATE
 *
 **************************************************************************/
void OSLeaveISR( void )
{
    OSTSKCBPTR osOldRunning;            /* currently running task    */

/* Check condition of dispatching, if dispatching is not needed then return, else dispatch  */
#if defined(OSMIXPREEMPT)
    if( OSHASRUNNINGTASK )     /* if interrupted task is not idle loop */
    {
        if( (OSRUNNINGSTATUS & OSTSKNONPREEMPT ) != 0 )
        {
            return;                             /* if non-preemptive task was interrupted, then no launch    */
        }
    }
#elif defined(OSNOPREEMPT)    
    if( OSHASRUNNINGTASK )    
    {
        return;                                 /* for non-preemptive system nothing launch,    */
    }                                           /*  if interrupt occured while any task was running    */ 
#elif defined(OSFULLPREEMPT)
        /*  nothing here */
#endif  /* defined(OSMIXPREEMPT) */

    OSSETTASKMSR();                             /* set MSR for Task, EE = 1 */
    osOldRunning = OsRunning;                   /* save running task (if any)    */

#if defined(OSHOOKPOSTTASK)
    if( OSHASRUNNINGTASK )    
    {
        OSPostTaskHook();       /* user hook or empty macro */
    }
#endif  /* defined(OSHOOKPOSTTASK) */

    OsRunning = OSGETMAXPRIOTASK;
    OSOrtiSetRunningId();

    if( OSSetJmp( osOldRunning->context ) )
    {
        OSSETBITRUNPRIO();              /* Restore runprio bit */
        OSOrtiResetIdOnExit( );                 /* set that the caller service is finished */
        OSPreTaskHook();
        OSDHI();
        return;
    }

    if( (OSRUNNINGSTATUS & OSTCBFIRST) != 0 )       /* if task not running yet */
    {
        OSRUNNINGSTATUS &= (OSBYTE)(~OSTCBFIRST);   /* set that task is running */

        OSSAVECONTEXTADDR(osOldRunning->context);

        OSSETRUNPRIO();        /* set internal resource priotity, if any       */

        OSOrtiResetIdOnExit( );                 /* set that the caller service is finished */
        OSCallPreTaskHook();
        OSEI(); 
        OSCallTask();                               /* start task (via conventional call or jump) */
        /* Task returned w/o TerminateTask  */            
        OSDispatchOnError();                        /* ShutdownOS in STANDARD status */
    }
    OSLOADCONTEXTADDR(OsRunning->context);
    OSLongJmp( OsRunning->context );          /* jump directly to the context of preempted task   */
        /* never return at this point */
    return;
}

#endif  /* !defined(OSNOFASTTERMINATE) */
#endif  /* OSBCC */

#if defined(OSECC)
/***************************************************************************
 * Function:    OSLeaveISR
 *
 * Description: Leave ISR and switch tasks' context, if needed
 *
 * Returns:     none
 *
 * Notes:       for SC1, ECC1
 *
 **************************************************************************/
void OSLeaveISR( void )
{
    OSTSKCBPTR osOldRunning;        /* currently running task    */

#if defined(OSMIXPREEMPT)
    if( (OsRunning->status & OSTSKNONPREEMPT) != 0 )
    {
        return;                     /* if non-preemptive task was interrupted, */
                                    /* or running task take scheduler then no launch */
    }
#elif defined(OSFULLPREEMPT)

#else   /* OSNOPREEMPT */    
    if( OSHASRUNNINGTASK )    
    {
        return;                     /* for non-preemptive system nothing launch,    */
    }                               /* if interrupt occured while any task was running */ 
#endif  /* defined(OSMIXPREEMPT) */

    OSSETTASKMSR();                 /* set MSR for Task, EE = 1 */
    osOldRunning = OsRunning;       /* save running task (if any)    */

#if defined(OSHOOKPOSTTASK)
    if( OSTSKIND(osOldRunning) != OSNULLTASK )    
    {
        OSPostTaskHook();            /* call user hook               */
    }
#endif  /* defined(OSHOOKPOSTTASK) */

    OsRunning = OSGETMAXPRIOTASK;
    OSOrtiSetRunningId();

    if( OSSetJmp( osOldRunning->context ) )   /* save context of preempted task    */
    { 
        /* return point from dispatched tasks */
        OSSETBITRUNPRIO();              /* Restore runprio bit */
        OSOrtiResetIdOnExit( );                 /* set that the caller service is finished */
        OSPreTaskHook();
        OSDHI();
        return;                            
    }

#if (OSNXTSKS > 0) 
    if( (osOldRunning->status & OSTCBEXTENDED) == 0 )
#endif  /* OSNXTSKS > 0  */
    {
        OSSAVECONTEXTADDR(osOldRunning->context);
    }    

    if( (OsRunning->status & OSTCBFIRST) != 0 )     /* if task not running yet */
    {
                                                    /* start-up the task    */
        OsRunning->status &= (OSBYTE)(~OSTCBFIRST); /* task already running */

#if (OSNXTSKS > 0)
        if( (OsRunning->status & OSTCBEXTENDED) != 0 )
        {
            OSLOADSP( OsRunning->tos );
        }
        else
        {
            if( (osOldRunning->status & OSTCBEXTENDED) != 0 ) /* if preempted task is BASIC */
            {
                OSLOADBASICSP();
            }
        }
#endif  /* OSNXTSKS > 0    */

        OSSETRUNPRIO();                             /* set internal resource priotity, if any       */

        OSOrtiResetIdOnExit( );                     /* set that the caller service is finished */
        OSCallPreTaskHook();
        OSEI();
        OSCallTask();                               /* start task via conventional call  */
        /* Task returned w/o TerminateTask  */            
        OSDispatchOnError();                        /* ShutdownOS in STANDARD status */
    }
#if (OSNXTSKS > 0)
    if( (OsRunning->status & OSTCBEXTENDED) == 0 )
#endif  /* OSNXTSKS > 0  */
    {
        OSLOADCONTEXTADDR(OsRunning->context);
    }
    OSLongJmp( OsRunning->context );          /* jump directly to the context of preempted task */
    /* never return at this point */
    return;
    OSWARNSUPPRESS                  /* For extra CW warning suppress */
}
#endif  /* defined(OSECC) */
#else   /* defined(OSSC1) */

/***************************************************************************
 * Function :   OSLeaveISR
 *
 * Description: Leave ISR and switch tasks' context, if needed
 *
 * Returns:     none
 *
 * Notes:       for SC2,3,4 all Tasks and ISRs has own stacks
 *
 **************************************************************************/
void OSLeaveISR( void )
{
    OSTSKCBPTR osOldRunning;        /* currently running task   */

#if !defined(OSFULLPREEMPT)
    if( ((OsKilled & OSRUNTSKKILLED) == 0) && OSHASRUNNINGTASK )
    {
#if !defined(OSNOPREEMPT)
        if( !OSDISPALLOWED )        /* no check for Non-preemptive system  */
#endif  /* Scheduling policy    */
        {
            OSTPResumeTaskBudget();
#if defined(OSMEMPROTECTION)
            OSMP_TASK_OPEN_STACK(); /* Prepare MPU for TASK stack */
#endif
            return;  /* there are some non-preemptive conditions for running task */
        }
    }
#endif /* !defined(OSFULLPREEMPT) */

    OSSETTASKMSR();                 /* set MSR for Task, EE = 1 */
    osOldRunning = OsRunning;       /* save running task (if any)    */

#if defined(OSHOOKPOSTTASK)
    if( OSTSKIND(osOldRunning) != OSNULLTASK )
    {
        if( (OsKilled & OSRUNTSKKILLED) == 0 )
        {
            OSSetCurApp(OsRunning->appId);
            OSPostTaskHook();       /* call user hook               */
        }
    }
#endif  /* defined(OSHOOKPOSTTASK) */

    OsRunning = OSGETMAXPRIOTASK;

    if( OSSetJmp( osOldRunning->context ) )   /* save context of preempted task    */
    {   /* returns here from dispatched tasks */
#if defined(OSMEMPROTECTION)
        OSEHI();
#endif
        OSSETBITRUNPRIO();          /* Restore runprio bit */
        OSOrtiResetIdOnExit( );     /* set that the caller service is finished */
        OSPreTaskHook();
        OSDHI();
        return;
    }
    OsKilled &= ~OSRUNTSKKILLED;    /* if some Task was killed */

    OSTaskInternalDispatch();
    /* unreachable point */
}

#endif  /* defined(OSSC1) */
#endif  /* defined(OSISRENTRYEXIT) */


#if defined(OSTIMINGPROTECTION)
/***************************************************************************
 * Function:    OSTPLeaveISR
 *
 * Description: performs dispatch before return from TP ISR if needed
 *
 * Notes:       called only if ISR and/or Task was killed, under OSDHI()
 *
 **************************************************************************/

void  OSTPLeaveISR( void )
{
#if defined(OSISRENTRYEXIT)
    if( OSISRLEVELMASKED == 0 )
#endif
    {
        if( (OsKilled & OSRUNTSKKILLED) != 0 )
        {                            
            OsRunning = OSGETMAXPRIOTASK;
            OsKilled &= ~OSRUNTSKKILLED;
            OSSETTASKMSR();             /* set MSR for Task, EE = 1 */
            OSTaskInternalDispatch();
        }
        /* return to running Task */
    }
#if defined(OSISRENTRYEXIT)
#if !defined(OSNOISR2)
    else if( OsIsrArray[OSISRLEVELMASKED - 1]->isKilled != OSFALSE )
    {
        OsIsrLevel--;
        OSLongJmp( OsISRbufs[OSISRLEVELMASKED] );   /* back to OSInterruptDispatcher */
    }
#endif    
#endif /* defined(OSISRENTRYEXIT) */
}
#endif /* defined(OSTIMINGPROTECTION) */


#if !defined(OSNOISR2) 
#if defined(OSMEMPROTECTION)
#if (OSNNONTRUSTEDISR > 0)
/******************************************************************************
 * Function:    OSNonTrustedISR2
 *
 * Description: this is the wrapper to call a user's non trusted ISR of category 2
 *
 * Returns:     none
 *
 ******************************************************************************/

OSINLINE void OSNonTrustedISR2(OSVOIDFUNCVOID userISR)
{
    OS2UserModeEHI();                   /* to user mode */
    userISR();                          /* it's important that userISR is calculated before of transfer to user mode */
    OSSystemCall0(OsIdOS2SysMode);      /* to supervisor mode */
    OSDI();
    OSDHI( );
}
#endif /* (OSNNONTRUSTEDISR > 0) */
#endif /* defined(OSMEMPROTECTION) */

/******************************************************************************
 * Function:    OSTrustedISR2
 *
 * Description: this is the wrapper to call a user's trusted ISR of category 2
 *              or ISR of category 2 for SC1 or SC2 configuration
 *
 * Returns:     none
 *
 ******************************************************************************/

OSINLINE void OSTrustedISR2( OS_ISRTYPE* ptr )
{
#if defined(OSUSEISRSTACK) || defined(OSSC1)
    if( OSISRLEVELMASKED == 0 )
    {
        OSSWITCH2STACK_ISR;
    }
#endif
    OsIsrLevel++;
    OSPreIsrHook( );
    OSTPStartISRBudget( ptr );

    OSEHI();
    ptr->userISR();             /* call User ISR */
    OSDI();
    OSDHI();

    OSTPResetISRBudget();

    OSPostIsrHook( );
    OsIsrLevel--;
#if defined(OSUSEISRSTACK)
    if( OSISRLEVELMASKED == 0 )
    {
        OSSWITCH2STACK_TASK;
    }
#endif
}
#endif /* !defined(OSNOISR2) */


/******************************************************************************
 * Function :    OSInterruptDispatcher
 *
 * Description:  This is a Dispatcher for External Interrupts 
 *
 * Note:    
 ******************************************************************************/
void OSInterruptDispatcher1( void )
{
#if( OSNISR > 0 )
    OS_ISRTYPE* isrPtr;     /* pointer to ISR descriptor */
#if defined(OSUSEISRLEVEL)
    OSDWORD     oldPri;     /* saved current ISR priority */
#endif
#if defined(OSAPPLICATION) 
#if defined(OSISRENTRYEXIT)
    ApplicationType curApp;
#endif 
#endif 

    OSCopyMode(OSMODESUPERVISOR);

#if defined(OSUSEISRLEVEL)
    oldPri = OSISRGetPrio();                        /* get the previous IPL (before reading IACKR) */
#endif
    isrPtr = &(OsIsrTable[OsIsr[OSINTC_IACKR >> 2]]);

#if !defined(OSNOISR1)
    if( isrPtr->type == OSISR1 )    
    {
#if defined(OSCHECKCONTEXT)
        oldPri = OsIsrLevel;                        /* oldPri is used differently than in ISRs cat.2 */
        OsIsrLevel |= OSISRLEVELISR1;               /* set flag for context check */
#endif /*defined(OSCHECKCONTEXT)*/
        OSEHI();
        isrPtr->userISR();                          /* call User ISR */
        OSDHI();
#if defined(OSCHECKCONTEXT)      
        OsIsrLevel = oldPri;                        /* restore previous context (ISR1) */
#endif /* defined(OSCHECKCONTEXT) */

        OSEOIR();                                   /* restore IPL */
        OSCopyMode(mode);
        return;
    }
#endif /* !defined(OSNOISR1) */

#if defined(OSUSEISRLEVEL)
    if( oldPri >= OSISRGetPrio() )                  /* Temporary ignore disabled ISR because of well-known INTC bug*/
    {
        OSEOIR();                                   /* restore IPL */
        OSCopyMode(mode);
        return;
    }
#endif
#if (OSNTPTSKBGTS > 0) || (OSNTPISRARRIV > 0)
    if( isrPtr->type == OSTPISR1 )    
    {
        isrPtr->userISR();                          /* call TP interrupt handler */
        OSEOIR();                                   /* restore IPL */
        return;         
    }
#endif

#if defined(OSAPPLICATION) 
#if defined(OSISRENTRYEXIT)
    curApp = OSGetCurApp();
#endif 
#endif 

#if defined(OSISRENTRYEXIT) || defined(OSTIMINGPROTECTION)

    OsIsrArray[OSISRLEVELMASKED] = isrPtr;

#if defined(OSSYSSTKCHECK)
    if( OSISRLEVELMASKED == 0 )
    {                           /* check stack of interrupted Task  */
        OSCheckStack();
    }
#endif /* defined(OSSYSSTKCHECK) */

    if( isrPtr->type == OSSYSINTERRUPT )
    {
#if defined(OSMEMPROTECTION)
        OSSetPID0(OS_PID_OSSTK);
        OSLoadISRSP( isrPtr->stackPtr );
#else
#if defined(OSUSEISRSTACK)          
        if( OSISRLEVELMASKED == 0 )
        {                           /* common ISR stack is used in SC1, SC2 */
            OSSWITCH2STACK_ISR;
        }
#endif
#endif /* defined(OSMEMPROTECTION) */
        OSOrtiSetISRId( OsIsr[isrPtr->index] ); 
        isrPtr->userISR();
#if defined(OSMEMPROTECTION)
        OSRestoreSP( );
#else
#if defined(OSUSEISRSTACK)
        OSCHECKISRSTACK( );
        if( 0 == OSISRLEVELMASKED )
        {
            OSSWITCH2STACK_TASK;
        }
#endif
#endif /* defined(OSMEMPROTECTION) */
    }
    else
    {
#if defined(OSTERMINATION)
        if( 0 == OSSetJmp(OsISRbufs[OSISRLEVELMASKED]) ) /* for killing ISR */
#endif
        {
#if !defined(OSNOISR2)

            OSSetCurApp( isrPtr->appId ); 

            /* Check inter-arrival rate for ISR2 */
#if (OSNTPISRARRIV > 0) && defined(OSHOOKPROTECTION)
            if( OSTPISRArrivalRate( isrPtr ) != OSTRUE )
            {
                OSSetCurApp(curApp);                    /* restore application */
                OSCopyMode(mode);
                OSEOIR();                               /* restore IPL */
                return;
            }
#else
            OSTPISRArrivalRate( isrPtr );
#endif

#if defined(OSMEMPROTECTION)
            /* Prepare MPU for ISR2 stack */
            OSMP_ISR2_OPEN_STACK( isrPtr );
            OSLOADSP( isrPtr->stackPtr );
#endif

            OSOrtiSetISRId( OsIsr[isrPtr->index] ); 

#if defined(OSMEMPROTECTION)
#if (OSNNONTRUSTEDISR > 0)
            if( isrPtr->type == OSNONTRUSTEDISR2 ) 
            {
                OSMP_APP_OPEN_DATA();
                OsIsrLevel++;
                OSPreIsrHook( );
                OSTPStartISRBudget( isrPtr );
                OSNonTrustedISR2( isrPtr->userISR );  /* the function call is used to ensure that userISR is in the register */
                OSTPResetISRBudget();
                OSPostIsrHook( );
                OsIsrLevel--;
                OSLOADSP((OSDWORD*)OsISRbufs[OSISRLEVELMASKED][0]);     /* restore stack */
            }
            else
#endif /* (OSNNONTRUSTEDISR > 0) */
#endif /* defined(OSMEMPROTECTION) */
            {
                OSTrustedISR2(isrPtr);      /* for SC2..4 never returns, ends with OSLongJmp */ 
#if defined(OSMEMPROTECTION)
                OSLOADSP((OSDWORD*)OsISRbufs[OSISRLEVELMASKED][0]);     /* restore stack */
#endif
            }
#endif /* !defined(OSNOISR2) */
        }
#if defined(OSMEMPROTECTION)
        OSSetPID0(OS_PID_OSSTK);
#endif

    }
    /* OS returns here under OSDHI() and OSDI() */

#if !defined(OSNOISR2)
    if( isrPtr->type != OSSYSINTERRUPT )
    {           /* check only for user ISR2  (ISR1 returns before)  */

#if defined(OSSYSSTKCHECK)
#if !defined(OSMEMPROTECTION)
        OSCHECKISRSTACK( );
#else  /* defined(OSMEMPROTECTION) */       
        if( (isrPtr->isKilled == OSFALSE) && OSSTKINVALID(isrPtr->isrBos) )
        {
#if defined(OSHOOKPROTECTION)
            ProtectionReturnType action;

            /* set violator Id */
            OsViolatorTaskId = INVALID_TASK;
            OsViolatorAppId = OSGetCurApp();
            OsViolatorISRId = OS_MKOBJID(OBJECT_ISR,OsIsr[isrPtr->index]);

            OSOrtiSetServiceWatch( OSServiceId_ProtectionHook );    /* set watch to this service */ 
            OSSETPROTCNXT();
            action = ProtectionHook( E_OS_STACKFAULT );    
            OSCLRPROTCNTX();
            OSOrtiServiceWatchOnExit( OSServiceId_ProtectionHook ); /* clear service watch on hook leaving */ 

            switch( action )
            {
                case PRO_KILLTASKISR:
                    break; /* nothing todo - it is finished */
                case PRO_KILLAPPL: 
                    if( OSTerminateApplication(NO_RESTART) )
                    {
                        break;
                    }
                    OSShutdownOS( E_OS_STACKFAULT );
                    /* unreachable point */
                case PRO_KILLAPPL_RESTART:
                    if( OSTerminateApplication(RESTART) )
                    {
                        break;
                    }
                    /* no break - OSShutdownOS() shall be called */
                case PRO_SHUTDOWN:
                default: 
                    OSShutdownOS( E_OS_STACKFAULT );
            }
            OSSTKSETGUARD( isrPtr->isrBos );        /* restore corrupted stack pad  */
#else
            OSShutdownOS( E_OS_STACKFAULT );
#endif
        }
#endif /* defined(OSMEMPROTECTION) */
#endif /* defined(OSSYSSTKCHECK) */

#if defined(OSTERMINATION)
        isrPtr->isKilled = OSFALSE;
#endif
        if( (OsSuspendLevelAll != 0) || (OsSuspendLevel != 0) ) /* check Suspend/Resume pairing */
        {
            OSErrorHook_noPar( E_OS_MISSINGEND );
            OsSuspendLevelAll = 0;
            OSTPKillIntLockTime();
            OsSuspendLevel = 0;
            OsIsrLevel &= ~OSISRLEVELDISABLEDINTERRUPTS;
        }

#if defined(OSRESOURCEISR)
        if( isrPtr->resources != OSNULLRES )
        {
            OSErrorHook_noPar( E_OS_MISSINGEND );
            OSReleaseISRResources( &(isrPtr->resources) );
        }
#endif /* defined(OSRESOURCEISR) */
    }

#if defined(OSTERMINATION)
    if( (OSISRLEVELMASKED != 0) && (OSTRUE == OsIsrArray[OSISRLEVELMASKED-1]->isKilled) )
    {                                           /* if preempted ISR was killed */
        OsIsrLevel--;
        OSLongJmp(OsISRbufs[OSISRLEVELMASKED]); /* restore context and go back */
    }
#endif /* defined(OSTERMINATION) */
#endif /* defined(OSNOISR2) */

#if defined(OSISRENTRYEXIT)
#if defined(OSORTIRUNNINGISRID)
    if( OSISRLEVEL == 0 )
    {                           /* return to task level */
        OSOrtiSetISRId( OSINVALID_ISR );
    }    
    else
    {                           /* return to preempted ISR */
        OSOrtiSetISRId( OsIsr[OsIsrArray[OSISRLEVELMASKED-1]->index] ); 
    }
#endif
#if defined(OSAPPLICATION)
    if( ( OsIsrLevel == 0 ) && ( ( OsRunning != OSGETMAXPRIOTASK ) || ( (OsKilled & OSRUNTSKKILLED) != 0 ) ) ) 
#else
    if( ( OsIsrLevel == 0 ) && ( OsRunning != OSGETMAXPRIOTASK ) ) 
#endif
    {                   
#if defined(OSTIMINGPROTECTION) && defined(OSAPPLICATION)
        if( (OsKilled & OSRUNTSKKILLED) != 0 )
        {                       /* if a task was killed via TerminateApplication() in SC2/4  - unconditional dispatch */
            OSEHI();
            OsRunning = OSGETMAXPRIOTASK;
            OsKilled &= ~OSRUNTSKKILLED;
            OSSETTASKMSR();             /* set MSR for Task, EE = 1 */
            OSTaskInternalDispatch();
            /* no return here */
        }
#endif
        OSLeaveISR( ); 
        OSMSYNC();
        OSISRSetPrio(oldPri);   /* instead of OSEOIR()  */
    }
    else
    {
#if defined(OSMEMPROTECTION) || defined(OSTIMINGPROTECTION)

        if( OSISRLEVELMASKED == 0 )
        {   /* we are returning from ISR cat.2 to the same Task */
#if defined(OSTIMINGPROTECTION)
            if( isrPtr->prio != OSHIGHTPISRPRIO )
            {                                           /* not executed after TP Timer ISR */
                OSTPResumeTaskBudget();
            }
#endif
#if defined(OSMEMPROTECTION)
            /* Prepare MPU for TASK stack */
            OSMP_TASK_OPEN_STACK();
#endif
        }
#if !defined(OSNOISR2)
        else
        {
#if defined(OSTIMINGPROTECTION)
            register OSBYTE tmpPrio;

            tmpPrio = isrPtr->prio;                     /* priority of current ISR  */
#endif
            isrPtr = OsIsrArray[OSISRLEVELMASKED - 1];
            if( isrPtr->type <= OSTRUSTEDISR2 )         /* if it is ISR category 2  */
            {
#if defined(OSTIMINGPROTECTION)
                if( tmpPrio != OSHIGHTPISRPRIO )
                {                                       /* not executed after TP Timer ISR */
                    OSTPResumeISRBudget( isrPtr );
                }
#endif
#if defined(OSMEMPROTECTION) 
                /* Prepare MPU for ISR2 stack */
                OSMP_ISR2_OPEN_STACK(isrPtr);
#endif
            }
        }
#endif  /* !defined(OSNOISR2) */
#endif  /* defined(OSMEMPROTECTION) || defined(OSTIMINGPROTECTION) */

        OSMSYNC();
        OSISRSetPrio(oldPri);   /* instead of OSEOIR() */
    }
    
    OSSetCurApp(curApp);                        /* restore application */
#if defined(OSMEMPROTECTION)
    /* Prepare MPU/MMU for data of current OS-application if the OS-application is nontrusted */
    OSMP_NONTRUSTEDAPP_OPEN_DATA();
#endif

#else
#if defined(OSUSEISRLEVEL)
    OSISRSetPrio(oldPri);   /* instead of OSEOIR() */
#endif
#endif /* defined(OSISRENTRYEXIT)  */ 

    OSCopyMode(mode);

#else 
    OSISRException();
#endif /* defined(OSISRENTRYEXIT) || defined(OSTIMINGPROTECTION) */

#else
    OSISRException();
#endif /* OSNISR > 0 */ 

    OSWARNSUPPRESS      /* For extra CW warning suppress (OS manipulates SP) */
}

#if defined(OSE200Z6) || defined(OSE200Z7)
void OSINTERRUPTNEST OSInterruptDispatcher( void )
{
    OSInterruptDispatcher1();
}
#endif


/*************************    Public OS Services    ***************************/

#if defined(OSEXTSTATUS)
/******************************************************************************
* Function:    DisableAllInterrupts
*
* Description: OSEK Service
*
* Returns:     none
******************************************************************************/
void OS_DisableAllInterrupts( void )
{
    OSOrtiSetServiceWatch( OSServiceId_DisableAllInterrupts );

    if( ( OsIsrLevel & OSISRLEVELDISABLEDINT ) == 0 )
    {
        OsOldMsr = OSGetMsrDI( );     
        OsIsrLevel |= OSISRLEVELDISABLEDINT;       
        OsSuspendLevelAll++;    /* it is checked in OSInterruptDispatcher for pairing */
    }
#if defined(OSHOOKERROR_EXT)
    else
    {
        OSErrorHook( E_OS_DISABLEDINT, OSServiceId_DisableAllInterrupts, 0 );
    }
#endif

    OSOrtiServiceWatchOnExit( OSServiceId_DisableAllInterrupts );
} 

/******************************************************************************
 * Function:    EnableAllInterrupts
 *
 * Description: OSEK Service
 *
 * Returns:     none
 *
 * Notes:       shall be called only after DisableAllInterrupts
 ******************************************************************************/
void OS_EnableAllInterrupts( void )
{
    OSOrtiSetServiceWatch( OSServiceId_EnableAllInterrupts );

    if( OsIsrLevel & OSISRLEVELDISABLEDINT )
    {
        OsSuspendLevelAll--;    /* decrease counter of nested Suspend/Resume pairs */
        OsIsrLevel &= ~OSISRLEVELDISABLEDINT;    
        OSMSYNC();
        OSSETMSR( OsOldMsr );
    }
#if defined(OSHOOKERROR_EXT)
    else
    {
        OSErrorHook( E_OS_SYS_ORDER, OSServiceId_EnableAllInterrupts, 0 );
    }
#endif

    OSOrtiServiceWatchOnExit( OSServiceId_EnableAllInterrupts );
}
#endif /* defined(OSEXTSTATUS) */

/******************************************************************************
 * Function:    SuspendAllInterrupts
 *
 * Description: Save interrupt state and disable all interrupts
 *
 * Returns: 
 *
 * Notes:       1.  This function is MD.
 ******************************************************************************/
void OS_SuspendAllInterrupts( void )
{
    OSOrtiSetServiceWatch( OSServiceId_SuspendAllInterrupts );
  
#if defined(OSEXTSTATUS)
    if( ( OsIsrLevel & OSISRLEVELDISABLEDINT ) == 0 )
    {
#endif
        if( OsSuspendLevelAll == 0 )
        {   /* if it is the first call to SuspendAllInterrupts, then disable */
            OsOldIntMaskAll = OSGetMsrDI( ); /* disable all ext.interrupts */  
#if defined(OSEXTSTATUS)
            OsIsrLevel |= OSISRLEVELDISABLEDINTALL;
#endif     
        }
#if defined(OSHOOKERROR_EXT) && defined(OSISRENTRYEXIT) 
        /* it is limited to nesting level of 32 */
        OsIntCheck |=  0x1 << ( OsSuspendLevel + OsSuspendLevelAll );
#endif
        OsSuspendLevelAll++; /* increase counter of nested Suspend/Resume pairs */
#if defined(OSEXTSTATUS)
    }
#if defined(OSHOOKERROR_EXT)
    else
    {
        OSErrorHook( E_OS_DISABLEDINT, OSServiceId_SuspendAllInterrupts, 0 );
    }
#endif
#endif /* defined(OSEXTSTATUS) */

    OSOrtiServiceWatchOnExit( OSServiceId_SuspendAllInterrupts );
}

/******************************************************************************
 * Function:    ResumeAllInterrupts
 *
 * Description: Restore interrupt state saved by SuspendAllInterrupts service
 *
 * Returns: 
 *
 * Notes:       1.  This function is MD.
 ******************************************************************************/

void OS_ResumeAllInterrupts( void )
{
    OSOrtiSetServiceWatch( OSServiceId_ResumeAllInterrupts );
   
#if defined(OSEXTSTATUS)
    if( ( OsIsrLevel & OSISRLEVELDISABLEDINT ) == 0 )
    {
#endif
        if( OsSuspendLevelAll == 0 )
        {
#if defined(OSHOOKERROR_EXT)
            OSErrorHook( E_OS_SYS_ORDER, OSServiceId_ResumeAllInterrupts, 0 );
#endif
            OSOrtiServiceWatchOnExit( OSServiceId_ResumeAllInterrupts );
            return;
        }
#if defined(OSHOOKERROR_EXT) && defined(OSISRENTRYEXIT) 
        /* it is limited to nesting level of 32 */
        if( ( OsIntCheck & ( 0x1 << ( OsSuspendLevel + OsSuspendLevelAll - 1 ) ) ) == 0 )
        {
            OSErrorHook( E_OS_SYS_ORDER, OSServiceId_ResumeAllInterrupts, 0 );
        }
#endif

        OsSuspendLevelAll--;         /* decrease counter of nested Suspend/Resume pairs */
                                                
        if( OsSuspendLevelAll == 0 ) /* if at outmost level of Suspend/Resume pair, restore interrupt level */
        {   
#if defined(OSEXTSTATUS)
            OsIsrLevel &= ~OSISRLEVELDISABLEDINTALL;
#endif     
            OSMSYNC();
            OSSETMSR( OsOldIntMaskAll );
            OSOrtiServiceWatchOnExit( OSServiceId_ResumeAllInterrupts );
            return;
        } /* otherwise nothing to do  */
#if defined(OSEXTSTATUS)
    }
#if defined(OSHOOKERROR_EXT)
    else
    {
        OSErrorHook( E_OS_DISABLEDINT, OSServiceId_ResumeAllInterrupts, 0 );
    }
#endif
#endif /* defined(OSEXTSTATUS) */

    OSOrtiServiceWatchOnExit( OSServiceId_ResumeAllInterrupts );
}

#if defined(OSISRENTRYEXIT)
/******************************************************************************
 * Function:    SuspendOSInterrupts
 *
 * Description: Save interrupt state and disable all OS interrupts
 *
 * Returns:     E_OK
 *
 * Notes:     
 ******************************************************************************/
void OS_SuspendOSInterrupts( void )
{
    OSOrtiSetServiceWatch( OSServiceId_SuspendOSInterrupts );

#if defined(OSEXTSTATUS)
    if( ( OsIsrLevel & OSISRLEVELDISABLEDINT ) == 0 )
    {
#endif
#if !defined(OSNOISR1) || defined(OSTIMINGPROTECTION)
        if( OSISRGetPrio( ) > OSHIGHISRPRIO )
        {   /* nothing to do in ISR1 */
            OSOrtiServiceWatchOnExit( OSServiceId_SuspendOSInterrupts );
            return;     
        }    
#endif
                                              
        if( OsSuspendLevel == 0 ) /* if first call of Suspend Interrupts, then disable them */
        {
            OSINTMASKTYPE oldMask;

            oldMask = OSISRGetPrio();
            OSISRSetPrio(OSHIGHISRPRIO); 
            OSMSYNC();
            OsSuspendLevel++;
            OsOldInterruptMask = oldMask;
            OSTPStartIntLockTime();
#if defined(OSEXTSTATUS)
            OsIsrLevel |= OSISRLEVELDISABLEDINTOS;
#endif     
        }
        else
        {                            
            OsSuspendLevel++; /* increase counter of nested Suspend/Resume pairs */
        }

#if defined(OSHOOKERROR_EXT)
        /* it is limited to nesting level of 32 */
        OsIntCheck &= ~( 0x1 << ( OsSuspendLevel + OsSuspendLevelAll - 1 ) );
#endif
#if defined(OSEXTSTATUS)
    }
#if defined(OSHOOKERROR_EXT)
    else
    {
        OSErrorHook( E_OS_DISABLEDINT, OSServiceId_SuspendOSInterrupts, 0 );
    }
#endif
#endif /* defined(OSEXTSTATUS) */

    OSOrtiServiceWatchOnExit( OSServiceId_SuspendOSInterrupts );
}

/******************************************************************************
 * Function:    ResumeOSInterrupts
 *
 * Description: Restore interrupt state saved by SuspendOSInterrupts service
 *
 * Returns:     none
 *
 * Notes:       allows nesting
 ******************************************************************************/
void OS_ResumeOSInterrupts( void )
{
    OSOrtiSetServiceWatch( OSServiceId_ResumeOSInterrupts );

#if defined(OSEXTSTATUS)
    if( ( OsIsrLevel & OSISRLEVELDISABLEDINT ) == 0 )
    {
#endif
#if !defined(OSNOISR1) || defined(OSTIMINGPROTECTION)
        if( OSISRGetPrio( ) > OSHIGHISRPRIO )
        {   /* nothing to do in ISR1 */       
            OSOrtiServiceWatchOnExit( OSServiceId_ResumeOSInterrupts );
            return;     
        }    
#endif
   
        if( OsSuspendLevel == 0 )
        {
#if defined(OSHOOKERROR_EXT)
            OSErrorHook( E_OS_SYS_ORDER, OSServiceId_ResumeOSInterrupts, 0 );
#endif
            OSOrtiServiceWatchOnExit( OSServiceId_ResumeOSInterrupts );
            return;
        }

#if defined(OSHOOKERROR_EXT)
        /* it is limited to nesting level of 32 */
        if( ( OsIntCheck & ( 0x1 << ( OsSuspendLevel + OsSuspendLevelAll - 1 ) ) ) != 0 )
        {
            OSErrorHook( E_OS_SYS_ORDER, OSServiceId_ResumeOSInterrupts, 0 );
        }
#endif

        if( OsSuspendLevel == 1 )
        {   /* if outmost level of Suspend/Resume pair, then restore interrupt state */
#if defined(OSEXTSTATUS)
            OsIsrLevel &= ~OSISRLEVELDISABLEDINTOS;
#endif     
            OSTPKillIntLockTime();
            OSResumeInterrupts( ); /* resume OS interrupts macro */
        }
        else
        {
            OsSuspendLevel--;
        }
#if defined(OSEXTSTATUS)
    }
#if defined(OSHOOKERROR_EXT)
    else
    {
        OSErrorHook( E_OS_DISABLEDINT, OSServiceId_ResumeOSInterrupts, 0 );
    }
#endif
#endif /* defined(OSEXTSTATUS) */

    OSOrtiServiceWatchOnExit( OSServiceId_ResumeOSInterrupts );
}

/******************************************************************************
 * Function:    OS_GetISRID
 *
 * Description: shows which ISR is running
 *
 * Returns:     current ISR Id or INVALID_ISR.
 *
 ******************************************************************************/

ISRType OS_GetISRID( void )
{
    OSWORD index;
    OSOrtiSetServiceWatch( OSServiceId_GetISRID );

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK |
                         OSISRLEVELHOOKERROR | OSISRLEVELHOOKAPPERROR |
                         OSISRLEVELHOOKPROTECTION ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
#if defined(OSHOOKERROR_EXT)
            OSErrorHook( E_OS_DISABLEDINT, OSServiceId_GetISRID, 0 );
#endif
            OSOrtiServiceWatchOnExit( OSServiceId_GetISRID );
            return( INVALID_ISR );
        }
        else
#endif        
        {
#if defined(OSHOOKERROR_EXT)
            OSErrorHook( E_OS_CALLEVEL, OSServiceId_GetISRID, 0 );
#endif
            OSOrtiServiceWatchOnExit( OSServiceId_GetISRID );
            return( INVALID_ISR );
        }
    }
#endif /* OSCHECKCONTEXT */

    if( OSISRLEVELMASKED == 0 )
    {
        OSOrtiServiceWatchOnExit( OSServiceId_GetISRID );
        return( INVALID_ISR );
    }
    index = OsIsrArray[OSISRLEVELMASKED - 1]->index; 

    OSOrtiServiceWatchOnExit( OSServiceId_GetISRID );
    return(OSWORD)( OS_MKOBJID( OBJECT_ISR, OsIsr[index] ) );
}

#endif /* defined(OSISRENTRYEXIT) */


#if OSNISR > 0

#if !defined(OSSC1) || defined(OSAPPLICATION)
/******************************************************************************
 * function:    DisableInterruptSource
 *
 * Description: disables interrupt source in INTC
 *
 * Returns:     E_OK, E_OS_ID
 *
 * Note:
 *
 ******************************************************************************/

StatusType OS_DisableInterruptSource( ISRType isrId )
{
    OSBYTE isrIndex = OS_GETOBJIND(isrId);
    OSIMSAVE                                     /* OSINTMASKTYPE save;       */
    OS_ISRTYPE* Isr;

    OSOrtiSetServiceWatch( OSServiceId_DisableInterruptSource );

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_DisableInterruptSource, isrId ); 
        }
        else
#endif        
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_DisableInterruptSource, isrId ); 
        }
    }
#endif /* OSCHECKCONTEXT */

#if defined(OSEXTSTATUS) 
    if( OSISRIDISINVALID(isrId) ) 
    {
        OSRETERROR( E_OS_ID, OSServiceId_DisableInterruptSource, isrId );   /* invalid ID */
    }
#endif /*defined(OSEXTSTATUS)*/

    Isr = &OsIsrTable[isrIndex];

#if defined(OSEXTSTATUS) 
    if( Isr->type > OSISR1 )    /* if it is not a User defined ISR */
    {
        OSRETERROR( E_OS_ID, OSServiceId_DisableInterruptSource, isrId );   /* invalid ID */
    }
#endif /*defined(OSEXTSTATUS)*/

    OSCHECKACCESSRIGHTS( OsIsrTable[isrIndex].appMask, OSServiceId_DisableInterruptSource, isrId );

    OSDIS(save);
    OSDisableISRSource( Isr );      /* disable ISR's source immediately */        
    OSRI(save);

    OSOrtiServiceWatchOnExit( OSServiceId_DisableInterruptSource );

    return E_OK;
}

/******************************************************************************
 * Function:    EnableInterruptSource
 *
 * Description: enables interrupt source in INTC
 *
 * Returns:     E_OK, E_OS_ID, E_OS_NOFUNC
 *
 * Note:
 *
 ******************************************************************************/

StatusType OS_EnableInterruptSource( ISRType isrId )
{
    OSBYTE isrIndex = OS_GETOBJIND(isrId);
    OS_ISRTYPE* Isr;
    OSIMSAVE                                    /* OSINTMASKTYPE save;       */

    OSOrtiSetServiceWatch( OSServiceId_EnableInterruptSource );

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_EnableInterruptSource, isrId ); 
        }
        else
#endif        
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_EnableInterruptSource, isrId ); 
        }
    }
#endif /* OSCHECKCONTEXT */

#if defined(OSEXTSTATUS)
    if( OSISRIDISINVALID(isrId) )
    {
        OSRETERROR( E_OS_ID, OSServiceId_EnableInterruptSource, isrId );   /* invalid ID */
    }
#endif /*defined(OSEXTSTATUS)*/

    Isr = &OsIsrTable[isrIndex];

#if defined(OSEXTSTATUS) 
    if( Isr->type == OSSYSINTERRUPT ) 
    {
        OSRETERROR( E_OS_ID, OSServiceId_EnableInterruptSource, isrId );   /* invalid ID */
    }
#endif /*defined(OSEXTSTATUS)*/

    OSCHECKACCESSRIGHTS( OsIsrTable[isrIndex].appMask, OSServiceId_EnableInterruptSource, isrId );

    OSDIS(save);
    OSEnableISRSource( &OsIsrCfg[isrIndex] );           /* enable ISR's source immediately */
    OSRI(save);
    OSOrtiServiceWatchOnExit( OSServiceId_EnableInterruptSource );
    return E_OK;
}
#endif /* !defined(OSSC1) || defined(OSAPPLICATION) */


#if defined(OSAPPLICATION)
/***************************************************************************
 * Function:    OSKillAppISRs
 *
 * Description: kills all the ISRs belonging to given application
 *
 * Returns:     none
 *
 * Notes:    
 ***************************************************************************/
void OSKillAppISRs(void)
{
    OSWORD i;

    for( i = 0; i < OSNISR+1; i++ )
    {
        if( OSGetCurApp() == OsIsrCfg[i].appId )
        {
#if OSNTRUSTEDFUNCTIONS > 0 
            OsIsrTable[i].appId = OsIsrCfg[i].appId;        /* restore appId for killed ISR */
#endif
            OSDisableISRSource( &OsIsrTable[i] );           /* disable ISR's source */ 
        }
    }

#if !defined(OSNOISR2)
    for( i = 0; i < OSISRLEVELMASKED; i++ )
    {
        if( OSGetCurApp() == OsIsrArray[i]->appId )
        {
            OSKillISR( OsIsrArray[i] );
        } 
    }
#endif
}
#endif /* defined(OSAPPLICATION) */

#endif /* OSNISR > 0 */

