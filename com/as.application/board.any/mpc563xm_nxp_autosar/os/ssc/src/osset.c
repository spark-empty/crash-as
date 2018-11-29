#define OSSET_C

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
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/src/osset.c,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* Functions:    
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  OSEK OS set-up  
*
* Notes:        
*
******************************************************************************/
#include    <string.h>                          /* memcpy()    */

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


#if defined(OSAPPLICATION)
/***************************************************************************
 * inline function  : OSGetAppStartupHook
 *
 * Description: 
 *
 * Returns: application specific startup hook address
 *
 * Notes: none
 **************************************************************************/
#if defined(OSAPPHOOKSTARTUP)
OSINLINE OSHKSTARTUP OSGetAppStartupHook(OS_AppType* app)
{
    return app->startup;
}
#endif

/***************************************************************************
 * inline function  : OSGetAppShutdownHook
 *
 * Description: 
 *
 * Returns: application specific shutdown hook address
 *
 * Notes: none
 **************************************************************************/
#if defined(OSAPPHOOKSHUTDOWN)
OSINLINE OSHKSHUTDOWN OSGetAppShutdownHook(OS_AppType* app)
{
    return app->shutdown;
}
#endif
#endif /* defined(OSAPPLICATION) */

/*****************************************************************************
 * inline function  : OSFillStacks
 *
 * Description: 
 *
 * Returns:
 *
 * Notes: none
 *****************************************************************************/
#if defined(OSSTKCHECK) || (OSORTIDEBUGLEVEL > 0)

#if defined(OSSC1) && defined(OSBCC1)

#define OSFillStacks( ) OSSTKSETGUARD( OSSTACKBOTTOM )

#else /* defined(OSSC1) && defined(OSBCC1) */

OSINLINE void OSFillStacks( void )
{
    OSDWORD* pstk;

#if defined(OSSC1)
    OSSTKSETGUARD( OSSTACKBOTTOM ); /* Common stack initialization in SC1,ECC1 */
#endif

#if (OSNXTSKS > 0) || !defined(OSSC1) /* SC1,ECC1 with extended tasks or SC2-SC4 */
    for( pstk = OSRUNNABLESTKBEG;
         pstk < &OsStacks[(OSSTKSIZE+OSSTACKPROTECTIONLAYER)/4];
         pstk++ )
    {
        *pstk = OSORTISTACKPATTERN;
    }
#endif

#if defined(OSUSEISRSTACK) /* SC1,ECC1 with ISRs category 2 or SC2 */
    for( pstk = &OsISRStack[0];
         pstk < &OsISRStack[OSISRSTACKSIZE];
         pstk++ )
    {
        *pstk = OSORTISTACKPATTERN;
    }
#endif /* defined(OSUSEISRSTACK) */
}
#endif /* defined(OSSC1) && defined(OSBCC1) */

#else  /* defined(OSSTKCHECK) || (OSORTIDEBUGLEVEL > 0) */

#define OSFillStacks( )

#endif /* defined(OSSTKCHECK) || (OSORTIDEBUGLEVEL > 0) */

/*  Public OS Services  */

/******************************************************************************
 * Function:    StartOS
 *
 * Description: OS data initialization from configuration tables
 *
 * Returns:     none
 *
 * Notes:
 *
 ******************************************************************************/

void StartOS( AppModeType mode )
{
    OSCARDINAL  i;
#if defined(OSUSETCB) 
    OSTSKCBPTR          task_cb;
    const   OSTSK*      task_cfg;
#endif

    OSDHI();

    OSOrtiSetServiceWatch( OSServiceId_StartOS );          /* set watch to this service */
    OSOrtiSetOldServiceID( OSServiceId_StartOS );

#if defined(OSEXTSTATUS)
    if( mode >= OSNAPPMODES )
    {
#if defined(OSHOOKERROR_EXT)
        OSOrtiSetServiceWatch( OSServiceId_ErrorHook );    /* set watch to this service */
        ErrorHook( E_OS_VALUE );
        OSOrtiServiceWatchOnExit( OSServiceId_ErrorHook ); /* clean service watch on hook leaving */
#endif
        OSOrtiServiceWatchOnExit( OSServiceId_StartOS );
        return;
    }
#endif        

    OSCLEARPARAM();                                     /* clear parameters for ErrorHook */

#if defined(OSMEMPROTECTION)
    OSInitMemProtection();      /* setting all used data sections for system PID, code sections for usre PID */
#endif

#if defined(OSAPPLICATION)
    OSInitApplications();       /* making OsAppTable of OsConstAppTable */
#endif

#if defined(OSTERMINATION)
    OsKilled = 0;
#endif

#if(OSORTIDEBUGLEVEL > 0) || (OSNAPPMODES > 1)    
    OsCurAppMode = mode;
#endif /* (OSORTIDEBUGLEVEL > 0)  || (OSNAPPMODES > 1) */

#if(OSORTIDEBUGLEVEL > 0)
    OsLastError = E_OK;
#endif /* (OSORTIDEBUGLEVEL > 0 ) */
    OsSuspendLevelAll = 0;

    /* ISR initialization   */
    OSInitializeISR( );

    /* Scheduler initialization */
    OsSchedulerVector1 = 0;
#if defined(OSEXTPRIORS)
    OsSchedulerVector2 = 0;
#endif  /* defined(OSEXTPRIORS) */

    /* Tasks initialization */
    /* Init task's control blocks */
#if defined(OSUSETCB) 
#if defined(OSRESOURCE)
    for( i = 0; i < OSNPRIORS; i++ )
    {
        OsPrioLink[i] = OSNULLPRIOLINK;         /* Priority Link table  */
    }
#endif

    for( i = 0; i < OSNTSKS; i++ )
    {
        task_cb  = &(OsTaskTable[i]);
        task_cfg = &(OsTaskCfgTable[i]);


#if defined(OSMEMPROTECTION)
        task_cb->appMask = task_cfg->appMask;   /* copy application identification mask value */ 
        task_cb->appId   = task_cfg->appId;     /* copy application identification value */ 
#endif
        task_cb->entry  = task_cfg->entry;      /* entry point of task */
        task_cb->taskId = task_cfg->taskId;
#if defined(OSMEMPROTECTION)
        task_cb->appId = task_cfg->appId;
#endif
#if defined(OSINRES)
        task_cb->runprio = task_cfg->runprio;
#endif

#if defined(OSRESOURCE) || defined(OSINRES)
        OsPrioLink[task_cfg->taskId] = task_cb;     
#endif
        task_cb->status = (OSBYTE)( OSTCBFIRST | (task_cfg->property) );

#if defined(OSSC1)
#if defined(OSECC)
        if( ( task_cfg->property & OSTSKEXTENDED ) != 0 )
        {
            task_cb->tos = task_cfg->tos - OSSTKADDS; /* -8 bytes because it is necessary to reserve space for backchain */
#if defined(OSUSEBOS)
            task_cb->bos = task_cfg->bos;             /* bottom of task stack */
#endif
        }
        else
        {                           /* for Basic tasks */
            task_cb->tos = 0;            
#if defined(OSSTKCHECK) || (OSORTIDEBUGLEVEL > 0)            
            task_cb->bos = 0;        
#endif
        }

#endif /* defined(OSECC) */
#else  /* defined(OSSC1) */

        task_cb->tos = task_cfg->tos - OSSTKADDS; /* -8 because it is necessary to reserve space for backchain */
#if defined(OSUSEBOS)
        task_cb->bos = task_cfg->bos;             /* bottom of task stack */
#endif

#endif /* defined(OSSC1) */

#if (OSNXTSKS > 0)
        task_cb->set_event = OSNOEVENTS;          /* clear set_event field */
#endif /* OSNXTSKS > 0 */

#if defined(OSRESOURCE)
#if defined(OSUSERESLINK)
        task_cb->resources = OSNULLRES;
#endif
#if(OSORTIDEBUGLEVEL > 0)
        task_cb->curPrio = (OSPRIOTYPE)(task_cb->taskId);
#endif
#endif /* OSRESOURCE */        

        /* Initialize task TP fields */

        /* Activate auto-startup tasks  */
#if(OSNAPPMODES > 1)
        if( ( task_cfg->autostart & ( 1 << mode ) ) != 0 )
#else
        if( ( task_cfg->property & OSTSKACTIVATE ) != 0 ) 
#endif
        {
            task_cb->status |= OSTCBSTART;   
            OSTask2Ready( task_cfg->taskId );
        }
    }

/*** NULLTASK CB initialization ***/

    task_cb  = &(OsTaskTable[OSNULLTASK]);

#if defined(OSMEMPROTECTION)
    task_cb->appMask = 0; 
    task_cb->appId = OSNAPPS;
#endif
    task_cb->entry  = 0;      /* entry point of task */
    task_cb->taskId = OSNULLTASK;
#if defined(OSINRES)
    task_cb->runprio = OSNTSKS;
#endif

#if defined(OSRESOURCE) || defined(OSINRES)
    OsPrioLink[OSNPRIORS-1] = task_cb;     /* Init priorities link table */
#endif
    task_cb->status = OSTCBNOSUSPENDED;
    OSTask2Ready( OSNULLTASK );

#if defined(OSECC) || !defined(OSSC1)
    task_cb->tos = 0;            
#if defined(OSSTKCHECK) || (OSORTIDEBUGLEVEL > 0)
    task_cb->bos = 0;        
#endif

#if (OSNXTSKS > 0)
    task_cb->set_event = OSNOEVENTS;
#endif /* OSNXTSKS > 0 */
#endif  /* defined(OSECC) || !defined(OSSC1) */

#if defined(OSRESOURCE)
#if defined(OSUSERESLINK)
    task_cb->resources = OSNULLRES;
#endif
#if(OSORTIDEBUGLEVEL > 0)
    task_cb->curPrio = (OSPRIOTYPE)(OSNULLTASK);
#endif
#endif /* OSRESOURCE */

/* end of NULLTASK CB initialization */

    task_cb->status &= (OSBYTE)(~OSTCBFIRST);           /* Background task(os, nulltask) already running */

    OsRunning = task_cb;                                /* no running task yet  */

#else  /* defined(OSUSETCB) */

    for( i = 0; i < OSNTSKS; i++ )
    {
        OsTaskStatus[i] = OsTaskProperty[i];
#if(OSNAPPMODES > 1)            
        if( ( OsTaskAutostart[i] & ( 1 << mode ) ) != 0 )
#else
        if( ( OsTaskStatus[i] & OSTSKACTIVATE ) != 0 )
#endif
        {
            OsTaskStatus[i] |= OSTCBSTART;       
            OSTask2Ready( i );
        }
#if defined(OSINRES)
        OsPrio2Task[i] = i;
#endif
        /* note that 'fast terminate' mode is not used in multicore environment */
    }
    
    OsRunning = OSNULLTASK;                     /* no running task yet  */
#endif  /* defined(OSUSETCB) */

    OSFillStacks( );

#if defined(OSRESOURCE)
    /* resources initialization */
    for( i = 0; i < OSNALLRES; i++ )
    {

#if defined(OSMEMPROTECTION)
        OsResources[i].appMask   = OsResCfg[i].appMask; 
        OsResources[i].prio      = OsResCfg[i].prio;
        OsResources[i].appId     = OsResCfg[i].appId; 
#else
        OsResources[i].prio      = OsResPrioTbl[i]; 
#endif
        OsResources[i].prio2task = OSNULLPRIOLINK;
#if defined(OSEXTSTATUS) || (OSORTIDEBUGLEVEL > 0)
        OsResources[i].isUsed    = 0;
#endif
#if defined(OSUSERESLINK)
        OsResources[i].nextRes   = OSNULLRES;
#endif
#if(OSORTIDEBUGLEVEL > 0)
        OsResources[i].curPrio   = 0;
#endif
#if (OSNTPTSKRESLOCKTIME > 0) || (OSNTPISRRESLOCKTIME > 0)
        OsResources[i].tpRemained = 0;
        OsResources[i].tpNextRes = OSNULLRES;
#endif

    }
#endif /* OSRESOURCE */


/* Counters initialization */
#if defined(OSCOUNTER)
    for( i = 0; i < OSNCTRS; i++ )
    {
#if defined(OSMEMPROTECTION)
        OsCounters[i].appMask = OsCountersCfg[i].appMask; /* copy application identification mask value */
        OsCounters[i].appId   = OsCountersCfg[i].appId;   /* copy application identification value */ 
#endif
#if (OSNALMS > 0)
        /*  Configuration Data  */
        OsCounters[i].alarm = OSALM0;                    /* pointer to assigned running alarms  */
#endif
        OsCounters[i].value = 0;
    }

#if defined(OSALMINCCOUNTER) 
    for( i = OSNHWCTRS; i < OSNCTRS; i++ )
    {
        OsCtrIncValue[i - OSNHWCTRS] = 0;
    }
    OsCtrIncCounter = 0;
#endif  /* defined(OSALMINCCOUNTER) */

#endif /* OSCOUNTER */

/* Alarms initialization */
#if (OSNUSERALMS > 0)
    for( i = 0; i < OSNUSERALMS; i++ )
    {

#if defined(OSMEMPROTECTION)
        OSALMARRAY[i].appMask = OsAlarmsCfg[i].appMask;         /* copy application identification mask value */
        OSALMARRAY[i].appId   = OsAlarmsCfg[i].appId;           /* copy application identification value */ 
#endif /* defined(OSMEMPROTECTION) */
        OSALMARRAY[i].action.taskIndex  = OsAlarmsCfg[i].taskIndex;
                                                                /* for BCC1 events are not supported, action is only activate task */
#if defined(OSALMSETEVENT)                                      /* events are supported if necessary */
        OSALMARRAY[i].action.event = OsAlarmsCfg[i].event;      /* if event==0 then alarm activates task 
                                                                   else it set event for this task */
#elif defined(OSSCTSETEVENT)
        OSALMARRAY[i].action.event = 0;                         /* alarm event field is not used in this configuration */
#endif  /*  defined(OSECC) && defined(OSALMSETEVENT) && (OSNXTSKS>0) */
        OSALMARRAY[i].ctrIndex  = OsAlarmsCfg[i].ctrIndex;      /* attached Counter ID  */
        OSALMARRAY[i].prev  = OSALMCBPTR0;
        OSALMARRAY[i].next  = OSALMCBPTR0;
#if defined(OSALMCALLBACK)
        OSALMARRAY[i].callBack = OsAlarmsCfg[i].callBack;
#endif
#if defined(OSALMINCCOUNTER) 
        OSALMARRAY[i].ctrIndexInc = OsAlarmsCfg[i].ctrIndexInc;
#endif  /* defined(OSALMCALLBACK) */
    }
#endif /* (OSNUSERALMS > 0) */

/* Schedule tables initialization */
#if defined(OSSCHEDULETABLES)
    for( i = 0; i < OSNSCTS; i++ )      /* Note that OSNSCTS is equal to OSNSCTALMS */
    {
        OSALMSCTARRAY[i].ctrIndex  = OsScheduleTablesCfg[i].ctrIndex;   /* attached Counter ID  */
        OSALMSCTARRAY[i].prev  = OSALMCBPTR0;
        OSALMSCTARRAY[i].next  = OSALMCBPTR0;

        OsScheduleTables[i].nextId = OSSCT0;
        OsScheduleTables[i].almId  = &OSALMSCTARRAY[i];

#if defined(OSSCTSYNCEXPLICIT)
        OsScheduleTables[i].deviation = 0;
        OsScheduleTables[i].precision = OsScheduleTablesCfg[i].precision;
        OsScheduleTables[i].syncOffset = 0;
#endif /* defined(OSSCTSYNCEXPLICIT) */
        OsScheduleTables[i].length = OsScheduleTablesCfg[i].length;
        OsScheduleTables[i].ctrIndex = OsScheduleTablesCfg[i].ctrIndex;

        OsScheduleTables[i].initialOffset = OsScheduleTablesCfg[i].initialOffset;
        OsScheduleTables[i].firstEP = OsScheduleTablesCfg[i].firstEP;
        OsScheduleTables[i].state = ( ( (OSWORD)OsScheduleTablesCfg[i].opts ) << 8 ) | SCHEDULETABLE_STOPPED;
#if defined(OSMEMPROTECTION)
        OsScheduleTables[i].appMask = OsScheduleTablesCfg[i].appMask;
        OsScheduleTables[i].appId = OsScheduleTablesCfg[i].appId;
#endif
    }
#endif /* defined(OSSCHEDULETABLES) */


/* Messages inititalization */
#if(OSNMSGS > 0)
    OSMsgInit( );  /* init messages data, even user must do it himself */
#endif  /* OSNMSGS > 0 */

#if defined(OSHOOKSTARTUP)
#endif /* defined(OSHOOKSTARTUP) */

#if defined(OSHOOKSTARTUP) || defined(OSAPPHOOKSTARTUP)
#if defined(OSCHECKCONTEXT)
    OsIsrLevel |= OSISRLEVELHOOKSTARTUP;                 /* to block scheduler during StartupHook  */
#endif
    OSOrtiSetServiceWatch( OSServiceId_StartupHook );    /* set watch to this service              */
#if defined(OSHOOKSTARTUP)
    StartupHook( );                                      /* user hook or empty macro               */
#endif
#if defined(OSAPPLICATION)
#if defined(OSAPPHOOKSTARTUP)
    for( i = 0; i < OSNAPPS; i++ )
    {
        OS_AppType* app;
        OSHKSTARTUP startup;

        OSSetCurApp(i);
        app = &(OsAppTable[i]);
                
        /* OS data including OS application structure ('app' points to it) is not avaliable in user mode
           therefore startup() address is calculated before jump to user mode  */
        startup = OSGetAppStartupHook(app);

        if( startup != 0 )
        {
            void* stackStore = (void*)OSGETSTACKPOINTER();
            OSDWORD *tos = app->hookStack - OSSTKADDS;

#if defined(OSMEMPROTECTION)
            OSMP_STACK_DESC((OSDWORD)app->hookStackBos, (OSDWORD)tos);
#endif
            OSLOADSP(tos);

#if defined(OSMEMPROTECTION)
#if (OSNNOTTRUSTEDAPPS > 0)
            if( OSMP_IS_NONTRUSTEDAPP(i) )
            {
                OSMP_APP_OPEN_DATA();
                OS2UserMode();
                startup();
                OSSystemCall0(OsIdOS2SysMode);       /* to supervisor mode */
            }
            else
#endif /* (OSNNOTTRUSTEDAPPS > 0) */
#endif
            {
                startup();
            }
#if defined(OSMEMPROTECTION)
            OSSetPID0(OS_PID_OSSTK);  /* restore OS rights for osstack area */
#endif
            OSLOADSP(stackStore);
        }
    }

    OSSetCurApp(i);   /* set INVALID_OSAPPLICATION */

#endif /* defined(OSAPPHOOKSTARTUP) */
#endif /* defined(OSAPPLICATION) */
    OSOrtiServiceWatchOnExit( OSServiceId_StartupHook ); /* clean service watch on hook leaving    */
#if defined(OSCHECKCONTEXT)
    OsIsrLevel &= (OSISRLEVELTYPE)(~OSISRLEVELHOOKSTARTUP);
#endif /* OSCHECKCONTEXT */
#endif /* OSHOOKSTARTUP ||  OSAPPHOOKSTARTUP*/

    /* Init systimer. It shall be after StartupHook call for compatibility with OS 2.1 */
#if defined(OSSYSTIMER) || defined(OS2SYSTIMER)
    {
        OSInitializeSystemTimer();
    }
#endif /* defined(OSSYSTIMER) || defined(OS2SYSTIMER) */
#if defined(OSTIMINGPROTECTION)
#if(OSNAPPMODES > 1)
    OSInitializeTP( mode );
#else
    OSInitializeTP();
#endif
#endif /* defined(OSTIMINGPROTECTION) */

#if defined(OSAUTOALARMS)
#if(OSNAPPMODES > 1)            
    OSInitAutoAlarms( mode ); 
#else
    OSInitAutoAlarms();
#endif
#endif /* OSAUTOALARMS */

#if defined(OSAUTOSCHEDULETABLES)
#if(OSNAPPMODES > 1)            
    OSInitAutoScheduleTables( mode ); 
#else
    OSInitAutoScheduleTables();
#endif
#endif /* OSAUTOSCHEDULETABLES */

    /*  Start scheduler */
#if defined(OSISRENTRYEXIT) || !defined(OSSC1)
    OsInitialMSR = OSGETMSR() | OSMSR_EE;      /* save initial MSR, used for Tasks start */
#endif


    OSEHI();
#if defined(OSISRENTRYEXIT)
    OSDI();
#endif
    
    if( OSPRIO2TASKID(OSGetReadyTask()) != OSNULLTASK )
    {
        OSTaskForceDispatch( );     /* start autostarted Tasks  */
    }
    OSEI( );            /* end of initialization if there were no autostarted Tasks */

    for( ; ; )
    {                                                         /* scheduler idle loop  */
#if defined(OSHOOKSCHEDULER)        /* not configurable by OIL */
        OSOrtiSetServiceWatch( OSServiceId_IdleLoopHook );    /* set watch to this service */ 
        IdleLoopHook( ); 
        OSOrtiServiceWatchOnExit( OSServiceId_IdleLoopHook ); /* clean service watch on hook leaving */ 
#endif
    }

    OSWARNSUPPRESS
}

#include <osbasapi.h>
/******************************************************************************
 * Function :   OSShutdownOS
 *
 * Description: Calls shutdown hook, disables interrupts from system timers,
 *              Sets Power-down mode
 *
 * Returns:     never
 *
 ******************************************************************************/

void OSShutdownOS( StatusType error )
{
#if defined(OSAPPLICATION)
#if defined(OSAPPHOOKSHUTDOWN)
    OSCARDINAL  i;
#endif
#endif

    OSMPC_DCI( );                                    /* disable ALL interrupts    */
    OSMSYNC();

#if defined(OSMEMPROTECTION)
   OSSetPID0(OS_PID_OSSTK);                         /* restore OS rights for osstack area */
#endif

    OSOrtiSetServiceWatch( OSServiceId_ShutdownOS ); /* set watch to this service */

#if defined(OSTIMINGPROTECTION)
    OSTPTimerShutdown();                            /* shutdown timing protection timer (hardware) */
#endif

#if defined(OSSYSTIMER) || defined(OS2SYSTIMER)
    OSShutdownSystemTimer( );                               /* shutdown system timer (hardware)        */
#endif

#if defined(OSHOOKSHUTDOWN) || defined(OSAPPHOOKSHUTDOWN)

#if defined(OSCHECKCONTEXT)
    OsIsrLevel |= OSISRLEVELHOOKSHUTDOWN;
#endif
    OSOrtiSetServiceWatch( OSServiceId_ShutdownHook );      /* set watch to this service               */

#if defined(OSAPPLICATION)
#if defined(OSAPPHOOKSHUTDOWN)
    for( i = 0; i < OSNAPPS; i++ )
    {
        OS_AppType* app;
        OSHKSHUTDOWN shutdown;

        OSSetCurApp(i);
        app = &(OsAppTable[i]);

        /* OS data including OS application structure ('app' points to it) is not avaliable in user mode
           therefore shutdown() address is calculated before jump to user mode  */
        shutdown = OSGetAppShutdownHook(app);

        if( shutdown != 0 )
        {
            OSDWORD *tos = app->hookStack - OSSTKADDS;

#if defined(OSMEMPROTECTION)
            OSMP_STACK_DESC((OSDWORD)app->hookStackBos, (OSDWORD)tos);
#endif
            OSLOADSP(tos);

#if defined(OSMEMPROTECTION)
#if (OSNNOTTRUSTEDAPPS > 0)
            if( OSMP_IS_NONTRUSTEDAPP(i) )
            {
                OSMP_APP_OPEN_DATA();
                OS2UserMode();
                shutdown( error );
                OSSystemCall0(OsIdOS2SysMode);
            }
            else
#endif
#endif
            {
                shutdown( error );
            }
#if defined(OSMEMPROTECTION)
            OSSetPID0(OS_PID_OSSTK);  /* restore OS rights for osstack area */
#endif
            /* no stack restoration here as it is indifferent which one is used farther */
        }
    }

    OSSetCurApp(i);   /* set INVALID_OSAPPLICATION */
#endif /* defined(OSAPPHOOKSHUTDOWN) */
#endif /* defined(OSAPPLICATION) */


#if defined(OSHOOKSHUTDOWN)
    ShutdownHook( error ); 
#endif
    OSOrtiServiceWatchOnExit( OSServiceId_ShutdownHook );       /* clean service watch on hook leaving     */ 
#if defined(OSCHECKCONTEXT)
    OsIsrLevel &= (OSISRLEVELTYPE)(~OSISRLEVELHOOKSHUTDOWN);
#endif
#endif /* defined(OSHOOKSHUTDOWN) || defined(OSAPPHOOKSHUTDOWN) */

    /* Set Power-down mode */
    OSOrtiServiceWatchOnExit( OSServiceId_ShutdownOS );         /* clean service watch on leaving service  */

    OSSETHID0( ( OSGETHID0( ) & 0xFF1FFFFFul ) | OSHID0_SLEEP );/* Enable SLEEP mode                       */
    OSSETMSR( OSGETMSR( ) | OSMSR_POW );                        /* set POW bit in MSR                      */

    for( ; ; )
    { }                                                         /* wait forever */

    OSWARNSUPPRESS
}

/******************************************************************************
 * Function:    OS_ShutdownOS
 *
 * Description: Shutdown OS
 *
 * Returns:     only if the call is not allowed
 *
 * Notes:       disables all interrupts and stops CPU
 *
 ******************************************************************************/

void OS_ShutdownOS( StatusType error )
{
    OSOrtiSetServiceWatch( OSServiceId_ShutdownOS ); /* set watch to this service */

#if defined(OSMEMPROTECTION)
#if (OSNNOTTRUSTEDAPPS > 0)
    if( ( OSGetCurApp() < OSNNOTTRUSTEDAPPS ) &&
       ( (OsIsrLevel & (OSISRLEVELHOOKERROR | OSISRLEVELHOOKAPPERROR)) == 0 ) )
    {   /* if current app is non-trusted, and call is not from ErrorHook, AppErrorHook */
        OSOrtiServiceWatchOnExit(OSServiceId_ShutdownOS);
        return;
    }
#endif
#endif
#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK |
                         OSISRLEVELHOOKERROR | OSISRLEVELHOOKAPPERROR | OSISRLEVELHOOKSTARTUP ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
#if defined(OSHOOKERROR_EXT)
           OSErrorHook( E_OS_DISABLEDINT, OSServiceId_ShutdownOS, 0 );
#endif     
           OSOrtiServiceWatchOnExit(OSServiceId_ShutdownOS);
           return;
        }
        else
#endif /* OSEXTSTATUS */
        {
#if defined(OSHOOKERROR_EXT)
            OSErrorHook( E_OS_CALLEVEL, OSServiceId_ShutdownOS, 0 );
#endif     
            OSOrtiServiceWatchOnExit( OSServiceId_ShutdownOS );
            return;
        }
    }
#endif /* OSCHECKCONTEXT */

    OSShutdownOS( error );
    /* never return here */
}

#if defined(OSCHECKCONTEXT) 
/******************************************************************************
 * Function :   GetActiveApplicationMode
 *
 * Description: 
 *
 * Returns:     AppModeType
 *
 ******************************************************************************/
AppModeType OS_GetActiveApplicationMode( void )
{
    OSOrtiSetServiceWatch( OSServiceId_GetActiveApplicationMode );

#if defined(OSHOOKERROR_EXT)
#if defined(OSEXTSTATUS)
    if( OSIsrLevelCheck( OSISRLEVELDISABLEDINTERRUPTS | OSISRLEVELTASKMASK |
                         OSISRLEVELHOOKERROR | OSISRLEVELHOOKAPPERROR | OSISRLEVELHOOKTASK |
                         OSISRLEVELHOOKSTARTUP | OSISRLEVELHOOKSHUTDOWN ) )
    {
        if( OSIsrLevelCheck( OSISRLEVELDISABLEDINTERRUPTS ) )
        {
           OSErrorHook( E_OS_DISABLEDINT, OSServiceId_GetActiveApplicationMode, 0 );
        }
#else    
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK | OSISRLEVELHOOKERROR | OSISRLEVELHOOKAPPERROR | OSISRLEVELHOOKTASK |
                         OSISRLEVELHOOKSTARTUP | OSISRLEVELHOOKSHUTDOWN ) )
    {        
#endif
        OSErrorHook( E_OS_CALLEVEL, OSServiceId_GetActiveApplicationMode, 0 );
    }
#endif /* defined(OSHOOKERROR_EXT) */       
    
    OSOrtiServiceWatchOnExit( OSServiceId_GetActiveApplicationMode );
  
    return( OSCURAPPMODE );
}
#endif /* defined(OSCHECKCONTEXT) */

#if defined(OSAPPLICATION)
/******************************************************************************
 * Function :   OsInitApplications
 *
 * Description: makes OsAppTable of OsAppCfgTable
 *
 * Returns:     none
 *
 ******************************************************************************/
void OSInitApplications( void )
{
    memcpy( &OsAppTable, &OsAppCfgTable, sizeof(OsAppCfgTable) );

    OSSetCurApp(INVALID_OSAPPLICATION);
}
#endif /* defined(OSAPPLICATION) */
