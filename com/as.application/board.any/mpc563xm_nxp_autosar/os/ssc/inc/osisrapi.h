#ifndef OSISRAPI_H 
#define OSISRAPI_H
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
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/inc/osisrapi.h,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* Functions:    
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  API for AUTOSAR ISR handling    
*
*
* Notes:        
*
******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */


/* FIT and DEC interrupts are redirected to Software setable interrupts 6 and 7 */
#define OSSIFIT 6u
#define OSSIDEC 7u
#define OSFITSOFTINVOKE 0x0200u
#define OSDECSOFTINVOKE 0x2u 

#if defined(OSISRENTRYEXIT) && defined(OSORTIRUNNINGISRID)
/* ORTI support for tracing ISR */

/* macro for setting ISR Id for ORTI */
#define OSOrtiSetISRId(ISRId)(OSISRId = (OSWORD)(ISRId))

#else   /* defined(OSISRENTRYEXIT) && defined(OSORTIRUNNINGISRID) */
#define OSOrtiSetISRId(ISRId)
#endif  /* defined(OSISRENTRYEXIT) && defined(OSORTIRUNNINGISRID) */

#if defined(OSISRENTRYEXIT)
/* internal service for User ISRs category 2 and SysTimer ISR */
void OSLeaveISR(void);

#endif /*defined(OSISRENTRYEXIT)*/


/******************************* Constants ********************************/

#define OSISRLEVELMASK               ((OSISRLEVELTYPE)0x0000001F)

#if defined(OSUSEISRLEVEL)

#define OSISRLEVELTASK               ((OSISRLEVELTYPE)0x80000000)  /* ISR resource bit allowed for Task */
#define OSISRLEVELDISABLEDINT        ((OSISRLEVELTYPE)0x40000000)
#define OSISRLEVELDISABLEDINTOS      ((OSISRLEVELTYPE)0x20000000)
#define OSISRLEVELDISABLEDINTALL     ((OSISRLEVELTYPE)0x10000000)
#define OSISRLEVELDISABLEDINTERRUPTS ((OSISRLEVELTYPE)0x70000000)
#define OSISRLEVELHOOKSTARTUP        ((OSISRLEVELTYPE)0x04000000)
#define OSISRLEVELHOOKSHUTDOWN       ((OSISRLEVELTYPE)0x02000000)
#define OSISRLEVELHOOKPRETASK        ((OSISRLEVELTYPE)0x01000000)
#define OSISRLEVELHOOKPOSTTASK       ((OSISRLEVELTYPE)0x00800000)
#define OSISRLEVELHOOKTASK           ((OSISRLEVELTYPE)0x01800000)
#define OSISRLEVELHOOKERROR          ((OSISRLEVELTYPE)0x00400000)
#define OSISRLEVELHOOKPROTECTION     ((OSISRLEVELTYPE)0x00200000)
#define OSISRLEVELHOOKCOM            ((OSISRLEVELTYPE)0x00100000)
#define OSISRLEVELCALLBACK           ((OSISRLEVELTYPE)0x00080000)
#define OSISRLEVELHOOKAPPERROR       ((OSISRLEVELTYPE)0x00040000)
#define OSISRLEVELISR1               ((OSISRLEVELTYPE)0x00020000)
#define OSISRLEVELTASKMASK           ((OSISRLEVELTYPE)0x8000001F)

#define OSIsrLevelCheck(mask) ((OsIsrLevel & (~(mask))) != 0)
#define OSCLEARCNTX() OsIsrLevel &= OSISRLEVELTASKMASK

#else  /* defined(OSUSEISRLEVEL) */

#define OSCLEARCNTX() 

#endif /* defined(OSUSEISRLEVEL) */

/***************************** internal macros ****************************/

#if defined(OSISRENTRYEXIT)


/* OSSuspend/OSResumeInterrupts macros are used in OSErrorHooks only  */

/***************************************************************************
 * Macro:       OSSuspendInterrupts
 * Description: save interrupt mask and disable ISRs cat.2
 * Returns:     none
 * Notes:       called only if OsSuspendLevel == 0
 **************************************************************************/

OSINLINE void OSSuspendInterrupts( void )
{
    OSINTMASKTYPE oldMask;
    oldMask = OSISRGetPrio();
#if (OSHIGHISRPRIO > 0)
    if( oldMask < OSHIGHISRPRIO )
    {                                   /* change level only if it is not higher    */
        OSISRSetPrio(OSHIGHISRPRIO); 
        OSMSYNC();
    }
#endif
    OsSuspendLevel++;
    OsOldInterruptMask = oldMask;
}
/***************************************************************************
 * Macro:       OSResumeInterrupts
 * Description: Restore interrupt mask from the global variable
 * Returns:     none
 * Notes:       called only if OsSuspendLevel == 1
 **************************************************************************/

#define OSResumeInterrupts()            \
    OsSuspendLevel--;                   \
    OSMSYNC();                          \
    OSISRSetPrio(OsOldInterruptMask)

#endif /* defined(OSISRENTRYEXIT) */


/***************************************************************************
 * Macro  : OsSetIVPR()
 * Description: Sets Interrupt Vector Prefix Register (IVPR)
 * Returns: none
 * Notes: It is used in OSInitializeISR
 **************************************************************************/
#if defined(OSDIABPPC)
OSASM void OsSetIVPR( OSDWORD value )
{
%reg value
        mtspr   63, value
}
#endif /* defined(OSDIABPPC) */

#if defined(OSGHSPPC)
#define OsSetIVPR( value ) OSMTSPR( 63, value )
#endif

#if defined(OSCWPPC)
OSINLINE void OsSetIVPR( register OSDWORD value )
{
    OSASM { mtspr   63, value };
}
#endif  /* defined(OSCWPPC) */


#if defined(OSRESOURCEISR)
#define OSNEEDDISPINISR ((OsIsrLevel == 0) && (OsRunning != OSGETMAXPRIOTASK))
#else
#define OSNEEDDISPINISR (OsRunning != OSGETMAXPRIOTASK)
#endif 

#if !defined(OSUSEISRLEVEL)
#if defined(OSTIMINGPROTECTION)
#define OSISRLEVELMASKED 0
#endif /* defined(OSTIMINGPROTECTION) */
#endif/*defined(OSUSEISRLEVEL)*/

#define OSINVALID_ISR  OSOBJMASK
#define INVALID_ISR OS_MKOBJID(OBJECT_ISR, OSINVALID_ISR)

#if !defined(OSNOISR)

#if defined(OSDIABPPC)
OSASM OSDWORD* OsGetSP( void )
{
    mr  r3, r1
}
#endif /* defined(OSDIABPPC) */

#if defined(OSCWPPC)
OSINLINE OSDWORD* OsGetSP( void )
{
    register OSDWORD* x;

    OSASM { mr  x, r1; }

    return x;
}
#endif  /* defined(OSCWPPC) */

#if defined(OSGHSPPC)
OSASM OSDWORD* OsGetSP()
{
    mr  r3, r1;
}
#endif /* defined(OSGHSPPC) */

/* Special ISR level to be used in hooks to avoid changing interrupt status */
#define OSISRRESOURCELEVEL           ((OSISRLEVELTYPE)0x80000000) /* ISR level for task, which got resource with ISR priority */

/* ISR level used for check in services */
#define OSISRLEVEL (OsIsrLevel & ~OSISRRESOURCELEVEL)
#else
#define OSISRLEVEL  OsIsrLevel
#endif /* defined(OSRESOURCEISR) */

#if defined(OSRESOURCEISR) || defined(OSCOMHOOKERROR)   || \
    defined(OSHOOKSTARTUP) || defined(OSHOOKSHUTDOWN)   || \
    defined(OSHOOKPRETASK) || defined(OSHOOKPOSTTASK)   || \
    defined(OSHOOKERROR)   || defined(OSHOOKPROTECTION) || defined(OSALMCALLBACK) || \
    defined(OSEXTSTATUS)
/* ISR level used for ISR nesting control */
#define OSISRLEVELMASKED (OsIsrLevel & OSISRLEVELMASK)
#else
#if defined(OSUSEISRLEVEL)
#define OSISRLEVELMASKED  OsIsrLevel
#endif
#endif

#if defined(OSRESOURCEISR)
void OSReleaseISRResource(OS_ISRTYPE* isrPtr);
#endif 

/********************************** ISR data **********************************/

/* Interrupt table length */
#if defined(OSMPC5634M)
#define OSNINTC 364u
#endif
#if defined(OSMPC5644A)
#define OSNINTC 476u
#endif
#if defined(OSMPC5674F)
#define OSNINTC 480u
#endif

extern const OSSHORT OsIsr[OSNINTC];

#if (OSNISR > 0)

#if !defined(OSNOISR2) 
#if defined(OSTERMINATION)
extern void OSKillISR(OS_ISRTYPE* isrToKill);
#endif
#if !defined(OSSC1)
extern void OSKillRunningISR(void);
#endif
#endif /*!defined(OSNOISR2)*/

/* Interrupts config table */
extern const OSISRCFGTYPE OsIsrCfg[OSNISR+1];

#endif /* OSNISR > 0 */

#if defined(OSUSEISRSTACK)

#define OSSTACK_START_SEC_VAR_UNSPECIFIED
#include "ossections.h"

extern  OSDWORD                 OsISRStack[OSISRSTACKSIZE];
#define OSISRSTKEND             OsISRStack
#define OSISRTOS                ((OSDWORD*)(OSISRSTKEND + OSISRSTACKSIZE))

#define OS_START_SEC_VAR_UNSPECIFIED
#include "ossections.h"


#endif /* defined(OSUSEISRSTACK) */


/*  ISRs definitions        */

#if !defined(OSNOISR)
#define OSEOIR()        OSINTC_EOIR = 0 /* End Of Interrupt, restore IPL */
#endif

#define ISR(IsrName)        void OS_isr_##IsrName()


/*************************  Private OS Services ******************************/

#if defined(OSUSEISRSTACK) || defined(OSSYSTIMER) || defined(OS2SYSTIMER) || \
    defined(OSTIMINGPROTECTION) || defined(OSMEMPROTECTION)

#if defined(OSDIABPPC)
OSASM void OSLoadISRSP( OSDWORD* isrsp )
{
%reg isrsp
    e_stwu      r1, -4(isrsp) /*  store stack pointer into environment buffer */
    e_add16i    r1, isrsp, -8
}
#endif /* defined(OSDIABPPC) */

#if defined(OSGHSPPC)
OSASM void OSLoadISRSP( OSDWORD* isrsp )
{
%treg isrsp
    e_stwu      r1, -4(isrsp) /*  store stack pointer into environment buffer */
    e_add16i    r1, isrsp, -8
}
#endif /* defined(OSGHSPPC) */

#if defined(OSCWPPC)
OSINLINE void OSLoadISRSP( register OSDWORD* isrsp )
{
    OSASM { e_stwu      r1, -4(isrsp); }
    OSASM { e_add16i    r1, isrsp, -8; }
}
#endif  /* defined(OSCWPPC) */

#if defined(OSDIABPPC)
OSASM void OSRestoreSP( void )
{
    se_lwz      r1, 8(r1)
}
#endif /* defined(OSDIABPPC) */

#if defined(OSGHSPPC)
OSASM void OSRestoreSP()
{
    se_lwz      r1, 8(r1)
}
#endif /* defined(OSGHSPPC) */

#if defined(OSCWPPC)
OSINLINE void OSRestoreSP( void )
{
    OSASM { se_lwz      r1, 8(r1); }
}
#endif  /* defined(OSCWPPC) */

#else
#define OSRestoreSP()
#endif  /* defined(OSUSEISRSTACK) || defined(OSSYSTIMER) || defined(OS2SYSTIMER) || \
           defined(OSTIMINGPROTECTION) || defined(OSMEMPROTECTION) */

#if (OSNISR > 0)

#if defined(OSUSEISRSTACK)

#define OSSWITCH2STACK_TASK     OSRestoreSP()
#define OSCHECKISRSTACK()       OSCheckIsrStack()

#if defined(OSSC1)
#define OSSWITCH2STACK_ISR     OSCheckMainStack();  OSLoadISRSP(OSISRTOS)
#else
#define OSSWITCH2STACK_ISR     OSLoadISRSP(OSISRTOS)
#endif

#endif  /* defined(OSUSEISRSTACK) */


#if defined(OSISRENTRYEXIT)

#if defined(OSSC1)
#if defined(OSBCC)
#define OSSWITCH2STACK_ISR      OSCheckMainStack();    /* check main stack overflow */
#define OSSWITCH2STACK_TASK     OSCheckMainStack();
#define OSCHECKISRSTACK()       OSCheckMainStack()
#endif  /* defined(OSBCC) */
#endif /* defined(OSSC1) */

/***************************************************************************
 * Macro:       OSSystemEnterISR2
 *
 * Description: switch stack if needed, enable interrupts
 *
 * Notes:       for SC1..4
 *
 **************************************************************************/

#define OSSystemEnterISR2()     \
    OSTPStopBudget();           \
    OsIsrLevel++;               \
    OSPreIsrHook( );            \
    OSEHI()

/***************************************************************************
 * Macro:       OSSystemLeaveISR2
 *
 * Description: Leave ISR - switch stack if required
 *
 * Notes:       for SC1..4
 *
 **************************************************************************/

#define OSSystemLeaveISR2( )\
    OSDHI( );               \
    OSPostIsrHook( );       \
    OsIsrLevel--

#endif /* defined(OSISRENTRYEXIT) */

#endif /* (OSNISR > 0) */


#if defined(OSISRENTRYEXIT)

/************************** Public OS Services  *******************************/

/*  Internal OS Services  */

extern void OS_ResumeOSInterrupts( void );
extern void OS_SuspendOSInterrupts( void );
extern ISRType OS_GetISRID( void );

/*  Public OS Services  */
#if defined(OSMEMPROTECTION)
OSINLINE void ResumeOSInterrupts( void )
{
    OSServiceCall0( void, ResumeOSInterrupts );
}
OSINLINE void SuspendOSInterrupts( void )
{
    OSServiceCall0( void, SuspendOSInterrupts );
}
OSINLINE ISRType GetISRID( void )
{
    return OSServiceCall0( ISRType, GetISRID );
}
#else /* defined(OSMEMPROTECTION) */
#define ResumeOSInterrupts( )  OS_ResumeOSInterrupts( )
#define SuspendOSInterrupts( ) OS_SuspendOSInterrupts( )
#define GetISRID( )            OS_GetISRID( )
#endif /* defined(OSMEMPROTECTION) */

#else  /* defined(OSISRENTRYEXIT) */

#define ResumeOSInterrupts( )
#define SuspendOSInterrupts( )
#define GetISRID( )            INVALID_ISR

#endif /* defined(OSISRENTRYEXIT) */

#if OSNISR > 0    

/*  Internal OS Services  */
#if !defined(OSSC1) || defined(OSAPPLICATION)
#if OSNISR > 0
StatusType OS_DisableInterruptSource( ISRType disableIsr );
StatusType OS_EnableInterruptSource( ISRType enableIsr );
#endif
#define  OSDisableISRSource(isrPtr) OSCLEAR_INT_PSRX((isrPtr)->index)
#define  OSEnableISRSource(isrPtr)  OSSET_INT_PSRX((isrPtr)->index, (isrPtr)->prio)
#endif /* !defined(OSSC1)  || defined(OSAPPLICATION) */

/*  Public OS Services  */

#define DeclareISR(ISR)  extern OSBYTE osdummy

#if !defined(OSSC1)
#if defined(OSMEMPROTECTION)
OSINLINE StatusType EnableInterruptSource( ISRType enableISR )
{
    return OSServiceCall1( StatusType, enableISR, EnableInterruptSource );
}

OSINLINE StatusType DisableInterruptSource( ISRType disableISR )
{
    return OSServiceCall1( StatusType, disableISR, DisableInterruptSource );
}

#else 
#define EnableInterruptSource(enableISR ) OS_EnableInterruptSource(enableISR ) 
#define DisableInterruptSource(enableISR ) OS_DisableInterruptSource(enableISR ) 
#endif
#endif /* !defined(OSSC1) */ 

#endif /* OSNISR > 0 */


extern void OS_SuspendAllInterrupts( void );
extern void OS_ResumeAllInterrupts( void );

#if defined(OSMEMPROTECTION)
OSINLINE void SuspendAllInterrupts( void )
{
    OSServiceCall0( void, SuspendAllInterrupts );
}
OSINLINE void ResumeAllInterrupts( void )
{
    OSServiceCall0( void, ResumeAllInterrupts );
}
#else /* defined(OSMEMPROTECTION) */
#define SuspendAllInterrupts( ) OS_SuspendAllInterrupts( )
#define ResumeAllInterrupts( )  OS_ResumeAllInterrupts( )
#endif /* defined(OSMEMPROTECTION) */

/*  "All" interrupt management    */
OSINLINE OSDWORD OSGetMsrDI(void)
{
    register OSDWORD msr;
    msr = OSGETMSR();
    OSSETMSR(msr & ~(OSMSR_EE | OSMSR_CE));
    return msr;
}

#if !defined (OSEXTSTATUS) 

/******************************************************************************
 * Macro:       DisableAllInterrupts
 * Description: OSEK Service
 * Returns:     none
 ******************************************************************************/

#define DisableAllInterrupts()                                          \
    {                                                                   \
        OSGETCOREID                                                     \
        OSOrtiSetServiceWatch(OSServiceId_DisableAllInterrupts);        \
        OsOldMsr = OSGetMsrDI();                                        \
        OSOrtiServiceWatchOnExit(OSServiceId_DisableAllInterrupts);     \
    } 

/******************************************************************************
 * Macro:      EnableAllInterrupts
 * Description: OSEK Service
 * Returns: none
 * Notes:       shall be called only after DisableAllInterrupts
 ******************************************************************************/

#define EnableAllInterrupts()                                           \
    {                                                                   \
        OSGETCOREID                                                     \
        OSOrtiSetServiceWatch(OSServiceId_EnableAllInterrupts);         \
        OSMSYNC();                                                      \
        OSSETMSR(OsOldMsr);                                             \
        OSOrtiServiceWatchOnExit(OSServiceId_EnableAllInterrupts);      \
    }

#else  /* !defined (OSEXTSTATUS) */

extern void OS_DisableAllInterrupts( void );
extern void OS_EnableAllInterrupts( void );

#if defined(OSMEMPROTECTION)
OSINLINE void EnableAllInterrupts( void )
{
    OSServiceCall0( void, EnableAllInterrupts );
}
OSINLINE void DisableAllInterrupts( void )
{
    OSServiceCall0( void, DisableAllInterrupts );
}
#else  /* defined(OSMEMPROTECTION) */
#define DisableAllInterrupts( ) OS_DisableAllInterrupts( )
#define EnableAllInterrupts( )  OS_EnableAllInterrupts( )
#endif /* defined(OSMEMPROTECTION) */

#endif /* !defined (OSEXTSTATUS) */

#if defined(OSISRHOOKS)
extern void PreIsrHook( void );
extern void PostIsrHook( void );
#define OSPreIsrHook( )   PreIsrHook()
#define OSPostIsrHook( )  PostIsrHook()
#else
#define OSPreIsrHook( )
#define OSPostIsrHook( )
#endif

#define OSISREXCEPTIONIDX  OSNINTC /* reserved vector number of INTC  */
#define OSISREXCEPTIONPRIO 1

/* OS internal functions */
extern void OSInitializeISR(void);
extern void OSISRException( void );
#if defined(OSAPPLICATION)
#if (OSNISR > 0)
extern void OSKillAppISRs(void);
#endif
#endif
#if defined(OSTIMINGPROTECTION)
extern  void  OSTPLeaveISR( void );
#endif /* defined(OSTIMINGPROTECTION) */

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* OSISRAPI_H */
