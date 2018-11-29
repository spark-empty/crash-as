#define OS_C
/******************************************************************************
*
*       Freescale(TM) and the Freescale logo are trademarks of Freescale Semiconductor, Inc. 
*       All other product or service names are the property of their respective owners. 
*       (C) Freescale Semiconductor, Inc. 2006-2010
*
*       THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
*       BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
*       Freescale Semiconductor, Inc.
*
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/src/os.c,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* Functions:    
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  Main module of the OSEK OS  
*
* Notes:        
*
******************************************************************************/

#define OS_INTERNAL 1
#include    <os.h>
#undef OS_INTERNAL 

#define OSTEXT_START_SEC_CODE
#include "ossections.h"

/* Stacks */

#define OSSTACK_START_SEC_VAR_UNSPECIFIED
#include "ossections.h"

#if defined(OSUSEISRSTACK)
OSDWORD  OsISRStack[OSISRSTACKSIZE];
#endif

#if (OSNXTSKS > 0) || !defined(OSSC1)
OSDWORD OsStacks[(OSSTKSIZE+OSSTACKPROTECTIONLAYER)/4];
#endif 

#define OSSTACK_STOP_SEC_VAR_UNSPECIFIED
#include "ossections.h"

/*  Global OS variables */

#define OS_START_SEC_VAR_UNSPECIFIED
#include "ossections.h"
#define OS_START_ONCE_SEC_VAR_FAST_UNSPECIFIED
#include "ossections.h"
#define OS_START_SEC_CONST_UNSPECIFIED
#include "ossections.h"

#define OS_START_SEC_VAR_FAST_UNSPECIFIED
#include "ossections.h"

#if defined(OSTERMINATION)
OSDECLAREVAR(OSNEAR OSBYTE, OsKilled_);  /* flags that Task or ISR was killed or some TP context */

#if defined(OSHOOKPROTECTION)
OSDECLAREVAR(OSNEAR TaskType, OsViolatorTaskId_);        /* Task Id of task which has violated */
OSDECLAREVAR(OSNEAR ISRType,  OsViolatorISRId_);         /* ISR2 Id of ISR2 which has violated */
#if defined(OSAPPLICATION)
OSDECLAREVAR(OSNEAR ApplicationType, OsViolatorAppId_);  /* Application Id of runable which has violated */
#endif
#endif /* defined(OSHOOKPROTECTION) */
#endif /* defined(OSTERMINATION) */

#if defined(OSORTICURRENTSERVICEID)
OSDECLAREVAR(OSNEAR volatile OSBYTE, OsOrtiRunningServiceId_);
OSDECLAREVAR(OSNEAR volatile OSBYTE, OsOrtiOldServiceId_);
#endif  /* defined(OSORTICURRENTSERVICEID) */

#if defined(OSCOUNTER)
#if defined(OSALMINCCOUNTER) 
OSDECLAREVAR(OSNEAR OSDWORD, OsCtrIncCounter_);
#endif  /* defined(OSALMCALLBACK) */
#endif /* defined(OSCOUNTER) */

#if defined(OSHWCOUNTER)
OSDECLAREVAR(OSNEAR OSHWTickType, OsTimVal_);
#endif

#if defined(OSGETSERVICEID) || defined(OSPARAMETERACCESS)
OSDECLAREVAR(OSNEAR OSServiceIdType, OsService_);          /* for OSErrorGetServiceId() from ErrorHook */
OSDECLAREVAR(OSNEAR OSDWORD,         OsObjId_);            /* for first parameter                      */
#endif /* defined(OSGETSERVICEID) || defined(OSPARAMETERACCESS) */

#if(OSORTIDEBUGLEVEL > 0)
OSDECLAREVAR(OSNEAR StatusType, OsLastError_);
#endif

#if defined(OSISRENTRYEXIT) && defined(OSORTIRUNNINGISRID)
/* ORTI support for tracing ISR */
OSDECLAREVAR(OSNEAR volatile OSWORD, OSISRId_);  /* the id of currently running ISR */
#endif

#if defined(OSISRENTRYEXIT)
OSDECLAREVAR(OSNEAR OSBYTE, OsSuspendLevel_);    /* level of the nested Suspend/Resume pairs */
#endif/* defined(OSISRENTRYEXIT) */
                                            
OSDECLAREVAR(OSNEAR OSDWORD, OsOldMsr_);         /* Saved MSR for EnableAll/DisableAllInterrupts */

OSDECLAREVAR(OSNEAR OSINTMASKTYPE, OsOldInterruptMask_); /* Saved interrupt mask for SuspendOS/ResumeOSInterrupts services */
                                                                /* and for Hooks */

OSDECLAREVAR(OSNEAR OSBYTE, OsSuspendLevelAll_);         /* level of the nested Suspend/ResumeAll pairs */

OSDECLAREVAR(OSNEAR OSINTMASKTYPE, OsOldIntMaskAll_);    /* SuspendAll/ResumeAllInterrupts services */

#if defined(OSISRENTRYEXIT) && defined (OSHOOKERROR_EXT)
OSDECLAREVAR(OSNEAR OSDWORD, OsIntCheck_);       /* check correct order of the nested Suspend/Resume pairs */
#endif

#if defined(OSUSEISRLEVEL)
OSDECLAREVAR(OSNEAR OSISRLEVELTYPE, OsIsrLevel_); /* num of active ISRs & context bits */
#if defined(OSISRENTRYEXIT) || !defined(OSSC1)
OSDECLAREVAR(OSNEAR OSDWORD, OsInitialMSR_);      /* saved initial MSR */
#endif
#endif /* defined(OSUSEISRLEVEL) */

#if defined(OSRESOURCEISR)   
OSDECLAREVAR(OSNEAR OSWORD, OsISRResourceCounter_);
#endif

OSDECLAREVAR(OSNEAR OSDWORD, OsSchedulerVector1_);  /* Mask of activated tasks(priorities) */
#if defined(OSEXTPRIORS)
OSDECLAREVAR(OSNEAR OSDWORD, OsSchedulerVector2_);   /* Mask of activated tasks(priorities) Extended vector */
#endif  /* defined(OSEXTPRIORS) */

#if defined(OSUSETCB)
OSDECLAREVAR(OSNEAR OSTSKCBPTR, OsRunning_);        /* running task (0, if no task is running) */
#else   /* defined(OSUSETCB) */
OSDECLAREVAR(OSNEAR OSTASKTYPE, OsRunning_);        /* running task (0, if no task is running) */
#endif  /* defined(OSUSETCB) */

#if(OSORTIDEBUGLEVEL > 0) || (OSNAPPMODES > 1)
OSDECLAREVAR(OSNEAR AppModeType, OsCurAppMode_);
#endif

#if (OSNMSGS > 0)
#if defined(OSCOMGETSERVICEID)
OSDECLAREVAR(OSNEAR OSDWORD, OsComObjId_);
OSDECLAREVAR(OSNEAR COMServiceIdType, OsComService_);
#endif
OSDECLAREVAR(OSNEAR COMApplicationModeType, OsCOMmode_);
#endif /* (OSNMSGS > 0) */
#if defined(OSTIMINGPROTECTION)

#if (OSNTPBGTS > 0) 
OSDECLAREVAR(OSNEAR OSObjectType, OsTPBudgetObject_);    /* TP object (TASK or ISR2) with current budget */
#endif
#if (OSNTPTSKINTLOCKTIME >0) || (OSNTPISRINTLOCKTIME > 0)
OSDECLAREVAR(OSNEAR OSObjectType, OsTPIntLockObject_);   /* TP object (TASK or ISR2) with current interrupt locking time */
#endif
#if (OSNTPTSKRESLOCKTIME >0) || (OSNTPISRRESLOCKTIME > 0)
OSDECLAREVAR(OSNEAR OSObjectType, OsTPResLockObject_);   /* TP object (TASK or ISR2) with current resource locking time */
#endif
OSDECLAREVAR(OSNEAR OSBYTE, OsTPForceReason_);           /* reason of TP forced interrupt */ 
OSDECLAREVAR(OSNEAR OSTPTICKTYPE, OsTPTimVal_);          /* current STM count value */ 
#if (OSNTPISRARRIV > 0) || (OSNTPTSKARRIV > 0)
OSDECLAREVAR(OSNEAR OSDWORD, OsTPOverflowCnt_);          /* TP overflow counter */
#endif
#if defined(OSHOOKPROTECTION)
OSDECLAREVAR(OSNEAR ProtectionReturnType, OsTPHookAction_);     /* Protection hook action desired by user when
                                                                   inter-arrival rate violation occurs */
#endif
#endif /* defined(OSTIMINGPROTECTION) */

#if defined(OSMEMPROTECTION)
#if (OSNNOTTRUSTEDAPPS > 1)
OSDECLAREVAR(OSNEAR ApplicationType, OsLastApp_); /* Last nontrusted application ID */
#endif
#endif /* defined(OSMEMPROTECTION) */

#define OS_STOP_SEC_VAR_FAST_UNSPECIFIED
#include "ossections.h"

#if defined(OSUSETCB) 
OSTSKCB OsTaskTable[OSNTSKS+1];
#else   /* defined(OSUSETCB) */
OSBYTE  OsTaskStatus[OSNTSKS];          /* Tasks status*/
#if defined(OSINRES)
TaskType OsPrio2Task[OSNTSKS];          /* references from priority to task */ 
#endif  /* defined(OSINRES) */
#endif  /* defined(OSUSETCB) */

#if defined(OSRESOURCE)
OSRESCB OsResources[OSNALLRES];
#endif

#if defined(OSCOUNTER)
/*  Global OS variables */
OSCTRCB   OsCounters[OSNCTRS];              /* Counters table           */

#if defined(OSALMINCCOUNTER) 
OSWORD    OsCtrIncValue[OSNCTRS-OSNHWCTRS]; /* the counter increment value inspired by corresponding alarm action 
                                               (only for SW counters) */
#endif /* defined(OSALMINCCOUNTER) */
#endif /* defined(OSCOUNTER) */

#if (OSNALMS > 0)
#if (OSNUSERALMS > 0) && (OSNSCTALMS > 0)
OSALLALARMS OsAllAlarms;
#elif (OSNUSERALMS == 0)
OSSCTALMCB  OsSCTAlarms[OSNSCTALMS];
#else
OSALMCB  OsAlarms[OSNUSERALMS];
#endif /* (OSNUSERALMS > 0) && (OSNSCTALMS > 0) */
#endif /* (OSNALMS > 0) */

#if defined(OSSCHEDULETABLES)
OSSCTCB  OsScheduleTables[OSNSCTS];
#endif

#if OSNISR > 0

#if OSNIPLSP > 0
OS_ISRTYPE* OsIsrArray[OSNIPLSP];           /* its index is OsIsrLevel */
#endif

OS_ISRTYPE OsIsrTable[OSNISR+1]; 

#endif /* OSNISR > 0 */
#if defined(OSTIMINGPROTECTION)
/* TP control blocks of resource locking time for tasks and ISR2s */
#if (OSNTPTSKRESLOCKTIME > 0) 
OSTPRESLOCK OsTPTskResLockTime[OSNTPTSKRESLOCKS];
#endif
#if (OSNTPISRRESLOCKTIME > 0)
OSTPRESLOCK OsTPISRResLockTime[OSNTPISRRESLOCKS];
#endif
#endif /* defined(OSTIMINGPROTECTION) */

#if defined(OSAPPLICATION)

OS_AppType OsAppTable[OSNAPPS];
#endif /* defined(OSAPPLICATION) */

#if defined(OSMEMPROTECTION)
#define OSSRVENTRY( ServiceName ) (OSSRV) OS_##ServiceName
const OSSRV OsServices[] = 
{
#include <ossrvlist.h>
};
#undef OSSRVENTRY

const OSBYTE OsLastServiceId = sizeof(OsServices) / sizeof(OSSRV);

#if (OSNMEMDATA0 > 0) 
/* Array of application data section adresses (in RAM) */
OSMP_DSADDR   OsMPDataRAM[OSNNOTTRUSTEDAPPS];
#endif

#if (OSNMEMDATA1 > 0) 
/* Array of application data section adresses (in RAM) */
OSMP_DSADDR   OsMPDataRAM_1[OSNNOTTRUSTEDAPPS];
#endif

#if (OSNMEMDATA2 > 0) 
/* Array of application data section adresses (in RAM) */
OSMP_DSADDR   OsMPDataRAM_2[OSNNOTTRUSTEDAPPS];
#endif
#endif /* OSMEMPROTECTION */

#if (OSORTIDEBUGLEVEL > 0 )

#if defined(OSCWPPC)

const OSDWORD _OsOrtiStart      = (OSDWORD)_stack_addr;
const OSDWORD _OsOrtiStackStart = (OSDWORD)_stack_end;

#else   /* defined(OSCWPPC) */

extern OSDWORD _OsOrtiStart[];
extern OSDWORD _OsOrtiStackStart[];

#endif  /* defined(OSCWPPC) */

OSBYTE OsOrtiRunning;                    /* running task for ORTI */

#endif  /* (OSORTIDEBUGLEVEL > 0 ) */


#if (OSNMSGS > 0)

OSMSGCBtype* OsRcvPtr[OSNSNDMSGS];          /* sending messages pointer to (1st) receiving */

OSMSGCBtype OsMessages[OSNRCVMSGS];         /* control blocks for receiving messages ( initalized in StartOS ) */

#if defined(OSAPPLICATION)
OSSNDMSGCBtype OsSndMessages[OSNSNDMSGS];   /* control blocks for sending messages ( initalized in StartOS ) */
#endif

#endif /* OSNMSGS > 0  */

#if defined(OSTERMINATION) && (OSNIPLSP > 0)
OSJMP_BUF OsISRbufs[OSNIPLSP];              /* jump buffers for skipping killed ISRs */
#endif

#if defined(OSAPPLICATION) 
#if defined(OSAPPHOOKERROR)
/***************************************************************************
 * inline function  : OSGetAppErrorHook
 *
 * Description: 
 *
 * Returns: application specific error hook address
 *
 * Notes: none
 **************************************************************************/
OSINLINE OSHKERROR OSGetAppErrorHook(OS_AppType *app)
{
    return app->error;
}

/******************************************************************************
 * function:       OSCallAppErrorHook
 *
 * Description: calls user defined application specific hook (if any) 
 *
 * Returns: none
 *
 * Notes:  
 ******************************************************************************/
OSINLINE void OSCallAppErrorHook( StatusType error )
{
    OSHKERROR appErrorHook;
    OS_AppType *app;
  
    if( OSGetCurApp() == INVALID_OSAPPLICATION )
    {
        return;
    }

    app = &OsAppTable[OSGetCurApp()];

    appErrorHook = OSGetAppErrorHook(app);

    if( appErrorHook != 0 )
    {

#if (OSNNOTTRUSTEDAPPS > 0)
        if( OSMP_IS_NONTRUSTEDAPP(OSGetCurApp()) )
        {
            OSMP_APP_OPEN_DATA();
            OS2UserMode( );
            appErrorHook( error );           /* call application specific error hook */
            OSSystemCall0( OsIdOS2SysMode ); /* to supervisor mode */
        }
        else
#endif /* (OSNNOTTRUSTEDAPPS > 0) */
        {
            appErrorHook( error );           /* call application specific error hook */
        }
    }
}

#endif /* defined(OSAPPHOOKERROR) */
#endif /* defined(OSAPPLICATION) */

#if defined(OSHOOKERROR) || defined(OSAPPHOOKERROR)

#if defined(OSGETSERVICEID) || defined(OSPARAMETERACCESS)

/******************************************************************************
 * Function:    OSErrorHook
 * Description: calls user defined hook if not nested
 * Returns:
 * Notes:       2 variants - differs in number of arguments
 ******************************************************************************/
void OSErrorHook( StatusType error, OSServiceIdType ID, OSObjectType param )
{
#if defined(OSHOOKERROR) || defined(OSAPPHOOKERROR)
    OSISRLEVELTYPE OsOldIsrLevel;
#endif
    OSPUTERROR( error );
    if( (OsIsrLevel & (OSISRLEVELHOOKERROR | OSISRLEVELHOOKAPPERROR)) == 0 ) /* if not nested call */
    {
#if defined(OSISRENTRYEXIT)
        if( (OsSuspendLevel == 0) && 
            (OsIsrLevel & ( OSISRLEVELHOOKPRETASK | OSISRLEVELHOOKPOSTTASK )) == 0 ) 
        {                                                        /* if called not from Pre/PostTaskHook */
            OSSuspendInterrupts( );                              /* disable OS interrupts  to avoid enabling interrupt in OSRI point */
        }
        else
        {
            OsSuspendLevel++; /* increase counter of nested Suspend/Resume pairs */
        }
#endif
        OSPUTPARAM( ID, param );
#if defined(OSHOOKERROR)
        OsOldIsrLevel = OsIsrLevel;                              /* save old value, then clear context flags */
        OsIsrLevel = (OsIsrLevel & OSISRLEVELMASK) | OSISRLEVELHOOKERROR;          /* and set ErrorHook flag */                      
        OSOrtiSetServiceWatch( OSServiceId_ErrorHook );          /* set watch to this service */
        ErrorHook( error );
        OSOrtiServiceWatchOnExit( OSServiceId_ErrorHook );       /* clean service watch on hook leaving */
        OsIsrLevel = OsOldIsrLevel;                              /* restore ISR level */
#endif
#if defined(OSAPPHOOKERROR)
        OsOldIsrLevel = OsIsrLevel;
        OsIsrLevel = (OsIsrLevel & OSISRLEVELMASK) | OSISRLEVELHOOKAPPERROR; /* set flag for context checking */
        OSCallAppErrorHook( error );
        OsIsrLevel = OsOldIsrLevel;                              /* restore ISR level */
#endif
        OSCLEARPARAM( );
#if defined(OSISRENTRYEXIT)
        if( (OsSuspendLevel == 1) && 
            (OsIsrLevel & ( OSISRLEVELHOOKPRETASK | OSISRLEVELHOOKPOSTTASK )) == 0 ) 
        {                                                        /* if called not from Pre/PostTaskHook */
            OSResumeInterrupts( );                               /* restore OS interrupts state */
        }
        else
        {
            OsSuspendLevel--; /* decrease counter of nested Suspend/Resume pairs */
        }
#endif
    }
}

#else /* defined(OSGETSERVICEID) || defined(OSPARAMETERACCESS) */

void OSErrorHook_1( StatusType error )
{
#if defined(OSHOOKERROR) || defined(OSAPPHOOKERROR)
    OSISRLEVELTYPE OsOldIsrLevel;
#endif
    OSPUTERROR( error );
    if( (OsIsrLevel & OSISRLEVELHOOKERROR) == 0 )                /* if not nested call */
    {
#if defined(OSISRENTRYEXIT)
        if( (OsSuspendLevel == 0) && 
            (OsIsrLevel & ( OSISRLEVELHOOKPRETASK | OSISRLEVELHOOKPOSTTASK )) == 0 ) 
        {                                                        /* if called not from Pre/PostTaskHook */
            OSSuspendInterrupts( );                              /* disable OS interrupts to avoid enabling interrupt in OSRI point */
        }
        else
        {
            OsSuspendLevel++; /* increase counter of nested Suspend/Resume pairs */
        }
#endif
#if defined(OSHOOKERROR)
        OsOldIsrLevel = OsIsrLevel;                              /* save old value, then clear context flags */
        OsIsrLevel = (OsIsrLevel & OSISRLEVELMASK) | OSISRLEVELHOOKERROR;          /* and set ErrorHook flag */                      
        OSOrtiSetServiceWatch( OSServiceId_ErrorHook );          /* set watch to this service */
        ErrorHook( error );
        OSOrtiServiceWatchOnExit( OSServiceId_ErrorHook );       /* clean service watch on hook leaving */
        OsIsrLevel = OsOldIsrLevel;                              /* restore ISR level */
#endif
#if defined(OSAPPHOOKERROR)
        OsOldIsrLevel = OsIsrLevel;
        OsIsrLevel = (OsIsrLevel & OSISRLEVELMASK) | OSISRLEVELHOOKAPPERROR; /* set flag for context checking */
        OSCallAppErrorHook( error );
        OsIsrLevel = OsOldIsrLevel;                              /* restore ISR level */
#endif
#if defined(OSISRENTRYEXIT)
        if( (OsSuspendLevel == 1) && 
            (OsIsrLevel & ( OSISRLEVELHOOKPRETASK | OSISRLEVELHOOKPOSTTASK )) == 0 ) 
        {                                                        /* if called not from Pre/PostTaskHook */
            OSResumeInterrupts( );                               /* return OS interrupts state */
        }
        else
        {
            OsSuspendLevel--; /* decrease counter of nested Suspend/Resume pairs */
        }
#endif
    }
}

#endif /* defined(OSGETSERVICEID) || defined(OSPARAMETERACCESS) */

/******************************************************************************
 * Function:    OSErrorHook_noPar
 * Description: calls user defined hook if not nested
 * Returns:
 * Notes:       called from internal OS functions with interrupts disabled
 ******************************************************************************/

void OSErrorHook_noPar( StatusType error )
{
#if defined(OSHOOKERROR) || defined(OSAPPHOOKERROR)
    OSISRLEVELTYPE OsOldIsrLevel;
#endif
    OSPUTERROR( error );
    if( (OsIsrLevel & (OSISRLEVELHOOKERROR | OSISRLEVELHOOKAPPERROR)) == 0 ) /* if not nested call */
    {
#if defined(OSHOOKERROR)
        OsOldIsrLevel = OsIsrLevel;                              /* save old value, then clear context flags */
        OsIsrLevel = (OsIsrLevel & OSISRLEVELMASK) | OSISRLEVELHOOKERROR;          /* and set ErrorHook flag */                      
        OSOrtiSetServiceWatch( OSServiceId_ErrorHook );          /* set watch to this service */
        ErrorHook( error );
        OSOrtiServiceWatchOnExit( OSServiceId_ErrorHook );       /* clean service watch on hook leaving */
        OsIsrLevel = OsOldIsrLevel;                              /* restore ISR level */
#endif
#if defined(OSAPPHOOKERROR)
        OsOldIsrLevel = OsIsrLevel;
        OsIsrLevel = (OsIsrLevel & OSISRLEVELMASK) | OSISRLEVELHOOKAPPERROR; /* set flag for context checking */
        OSCallAppErrorHook( error );
        OsIsrLevel = OsOldIsrLevel;                              /* restore ISR level */
#endif
    }
}

#endif /* defined(OSHOOKERROR) || defined(OSAPPHOOKERROR) */
