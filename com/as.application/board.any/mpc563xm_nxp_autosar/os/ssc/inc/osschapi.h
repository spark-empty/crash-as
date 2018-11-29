#ifndef OSSCHAPI_H
#define OSSCHAPI_H
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
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/inc/osschapi.h,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  API for OSEK OS scheduler   
*
* Notes:        
*
******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/*  Configuration Data  */

/*  Constants */

/*  Global OS variables */

#define OSPRIO2TASKID(prio) prio

#if defined(OSUSETCB)

#if defined(OSRESOURCE) || defined(OSINRES)

#define OSNPRIORS (OSNTSKS+1)
extern OSTSKCBPTR OsPrioLink[OSNPRIORS];   /* Priority Link table */

#endif  /* defined(OSRESOURCE) || defined(OSINRES) */

#endif  /* defined(OSUSETCB) */

/*  Private OS Services */

#if defined(OSEXTPRIORS)
/* OSGetReadyTask returns the priority of ready task. Note the priority equals to task Id when single core is used */
#define OSGetReadyTask()    (OSMask2Task(OsSchedulerVector1, OsSchedulerVector2))

#define OSSETBITNUM2MASK(taskprio) \
    ( (taskprio < OSSCHMAXBITNUM) ? \
    (OsSchedulerVector1 |=  ( OSDWORDMSB >> (taskprio) )) : \
    (OsSchedulerVector2 |=  ( OSDWORDMSB >> \
    ((OSTASKTYPE)taskprio - OSSCHMAXBITNUM)) ) \
    )

#define OSTask2Suspend(taskprio)  ( (taskprio < OSSCHMAXBITNUM) ? \
    (OsSchedulerVector1 &= ~( OSDWORDMSB >> (taskprio) )) : \
    (OsSchedulerVector2 &= ~( OSDWORDMSB >> \
    ((OSTASKTYPE)taskprio - OSSCHMAXBITNUM)) ) \
    )

#else   /* defined(OSEXTPRIORS) */

#define OSGetReadyTask()            (OSMask2Task(OsSchedulerVector1))
#define OSSETBITNUM2MASK(taskprio)    ( OsSchedulerVector1 |=  ( OSDWORDMSB >> (taskprio) )  )
#define OSTask2Suspend(taskprio)  ( OsSchedulerVector1 &= ~( OSDWORDMSB >> (taskprio) )  )

#endif  /* defined(OSEXTPRIORS) */

#define OSTask2Ready( taskId )      OSSETBITNUM2MASK( taskId )
#define OSSetPrioBit( taskId )      OSSETBITNUM2MASK( taskId )



#if defined(OSHOOKPROTECTION) && (OSNTPTSKARRIV > 0)
/* Macros are intended for 'task activation' */
#define OSActivateTaskInAlm( taskId )                   \
    if( OSTPStartTaskFrameInAlm( taskId ) == OSTRUE )   \
    {                                                   \
        OSTASKSTATUS( taskId ) |= OSTCBSTART;           \
        OSTask2Ready( taskId );                         \
    } 

#define OSActivateTask( taskId )                        \
    if( OSTPStartTaskFrame( taskId ) == OSTRUE )        \
    {                                                   \
        OSTASKSTATUS( taskId ) |= OSTCBSTART;           \
        OSTask2Ready( taskId );                         \
    }

/* Macros are used where an event is set. */
#if defined(OSECC) && (OSNXTSKS > 0)

#define OSReleaseTaskInAlm( taskId, mask )                              \
    if( OSTPStartTaskFrameInAlm( taskId ) == OSTRUE )                   \
    {                                                                   \
        OSTASKSTATUS( taskId ) &= (OSBYTE)(~OSTCBWAIT);                 \
        OSTask2Ready( taskId );                                         \
    }                                                                   \
    else                                                                \
    {                                                                   \
        OsTaskTable[taskId].set_event &= (EventMaskType)~(OsTaskTable[taskId].wait_event & mask); \
    }

#define OSReleaseTask( taskId, mask )                                   \
    if( OSTPStartTaskFrame( taskId ) == OSTRUE )                        \
    {                                                                   \
        OSTASKSTATUS( taskId ) &= (OSBYTE)(~OSTCBWAIT);                 \
        OSTask2Ready( taskId );                                         \
    }                                                                   \
    else                                                                \
    {                                                                   \
        OsTaskTable[taskId].set_event &= (EventMaskType)~(OsTaskTable[taskId].wait_event & mask); \
    }

#endif

#else  /* defined(OSHOOKPROTECTION) && (OSNTPTSKARRIV > 0) */


/* Macro is intended for 'task activation' */
#define OSActivateTaskInAlm( taskId )                   \
    OSTPStartTaskFrameInAlm( taskId );                  \
    OSTASKSTATUS( taskId ) |= OSTCBSTART;               \
    OSTask2Ready( taskId )

#define OSActivateTask( taskId )   OSActivateTaskInAlm( taskId )

#if defined(OSECC) && (OSNXTSKS > 0)
/* Macro is intended for use in 'set event'.  */
#define OSReleaseTaskInAlm( taskId, mask )              \
    OSTPStartTaskFrameInAlm( taskId );                  \
    OSTASKSTATUS( taskId ) &= (OSBYTE)(~OSTCBWAIT);     \
    OSTask2Ready( taskId )

#define OSReleaseTask( taskId, mask )    OSReleaseTaskInAlm( taskId, mask )
#endif

#endif /* defined(OSHOOKPROTECTION) && (OSNTPTSKARRIV > 0) */



#if !defined(OSEXTPRIORS)  
#define OSMask2Task( scheduler_vector )  ( (OSTASKTYPE) ( OSCNTLZW( scheduler_vector ) ) )
#else   /* !defined(OSEXTPRIORS) */
OSINLINE OSTASKTYPE OSMask2Task( register OSDWORD scheduler_vector, register OSDWORD scheduler_vector2 )
{
    register OSDWORD result;
    register OSDWORD tmp;

    result = OSCNTLZW( scheduler_vector ); /* calculate number of leading 'zeros' till first 'one' from left   */

    if ( result >= OSSCHMAXBITNUM )
    {
        tmp = OSCNTLZW( scheduler_vector2 ); /* calculate number of leading 'zeros' till first 'one' from left   */
        result += tmp;
    }

    return result;
}
#endif  /* !defined(OSEXTPRIORS) */


#if defined(OSSC1)
#if defined(OSNOFASTTERMINATE)
#if defined(OSDIABPPC)

#define OSLOADBASICSP() \
    OSASM("    mfspr    r4, 273   "); \
    OSASM("    e_lwz    r1, 0(r4) ");

/***************************************************************************
 * Macro  : OSSAVECONTEXTADDR
 * Description: Saves the current content of the SPRG1
 *              into Task context, 
 *              sets the new SPRG1 value as Task context address
 * Returns: none
 * Notes:   
 **************************************************************************/
OSASM void OSSAVECONTEXTADDR( OSJMP_BUF jmpbuf_ptr )
{
%reg jmpbuf_ptr
    mfspr       r4, 273         /* SPRG1 */
    e_stw       r4, OSSSP*4(jmpbuf_ptr)
    mtspr       273, jmpbuf_ptr /* SPRG1 */
}

/***************************************************************************
 * Macro:    OSLOADCONTEXTADDR
 *
 * Description: Loads the content of the SPRG1 from Task context.
 *
 **************************************************************************/
OSASM void OSLOADCONTEXTADDR( OSJMP_BUF jmpbuf_ptr )
{
%reg jmpbuf_ptr
    e_lwz       r4, OSSSP*4(jmpbuf_ptr)
    mtspr       273, r4 /* SPRG1 */
}

#endif  /* defined(OSDIABPPC) */

#if defined(OSGHSPPC)

#define OSLOADBASICSP() \
    OSASM("    mfsprg1  r4        "); \
    OSASM("    e_lwz    r1, 0(r4) ");

/***************************************************************************
 * Macro  : OSSAVECONTEXTADDR
 * Description: Saves the current content of the SPRG1 into Task context, 
 *              sets the new SPRG1 value as Task context address
 * Returns: none
 * Notes:   
 **************************************************************************/
#define OSSAVECONTEXTADDR( jmpbuf_ptr ) jmpbuf_ptr[ OSSSP ] = OSMFSPR( 273 ); \
                                        OSMTSPR( 273, (OSDWORD)jmpbuf_ptr )

/***************************************************************************
 * Macro:    OSLOADCONTEXTADDR
 * Description: Loads the content of the SPRG1 from Task context.
 **************************************************************************/
#define OSLOADCONTEXTADDR( jmpbuf_ptr ) OSMTSPR( 273, jmpbuf_ptr[ OSSSP ] )

#endif  /* defined(OSGHSPPC) */

#if defined(OSCWPPC)

OSINLINE void OSLOADBASICSP( void )
{
    OSASM {
        mfsprg1     r4
        se_lwz      r1, 0(r4)
    }
}
                                    
OSINLINE void OSSAVECONTEXTADDR( register OSJMP_BUF jmpbuf_ptr )
{
    register OSDWORD tmp;
    OSASM {
        mfsprg1     tmp        /* SPRG1 */
        e_stw       tmp, OSSSP*4(jmpbuf_ptr)
        mtsprg1     jmpbuf_ptr /* SPRG1 */
    }
}

OSINLINE void OSLOADCONTEXTADDR( register OSJMP_BUF jmpbuf_ptr )
{
    register OSDWORD tmp;
    OSASM {
        e_lwz       tmp, OSSSP*4(jmpbuf_ptr)
        mtsprg1     tmp /* SPRG1 */
    }
}
#endif  /* defined(OSCWPPC) */

#endif /* defined(OSNOFASTTERMINATE) */
#endif /* defined(OSSC1) */


extern void OSTaskForceDispatch( void );

#if defined(OSNOFASTTERMINATE)
void OSTaskTerminateDispatch( void );

#if defined(OSUSETCB) 
extern OSSIGNEDDWORD OSSetJmp( OSJMP_BUF );
extern OSSIGNEDDWORD OSLongJmp( OSJMP_BUF );
#else  /* OSUSETCB */
extern OSSIGNEDDWORD OSSetJmp( OSWORD );
extern OSSIGNEDDWORD OSLongJmp( OSWORD );
#endif /* OSUSETCB */

#endif /* OSNOFASTTERMINATE */

#if defined(OSSC1)
#if defined(OSEXTSTATUS) 
void OSDispatchOnError( void );
#else
#define OSDispatchOnError()  OSShutdownOS(E_OS_MISSINGEND)
#endif
#endif /* defined(OSSC1) */

/* OSDISPATCH() definition , check current task on preeptive condition and call dispatcher if necessary */
/* Must be called with disabled all/system interrupts */
#if defined(OSMIXPREEMPT)

#define OSDISPALLOWED ((OSRUNNINGSTATUS & OSTSKNONPREEMPT) == 0)

#define OSDISPATCH() \
    if( OSDISPALLOWED ) \
    { \
        OSTaskForceDispatch(); \
    }

#elif defined(OSFULLPREEMPT)

#define OSDISPATCH()   OSTaskForceDispatch()

#else   /* OSNOPREEMPT  */  
/* no call to dispatcher at all */
#define OSDISPATCH()    
#endif  /* Scheduling policy */

/*  Public OS Services  */

StatusType OS_Schedule( void );

#if defined(OSMEMPROTECTION)

extern void OS_ExceptionDispatch(void);

OSINLINE StatusType Schedule( void )
{
    return( OSServiceCall0( StatusType, Schedule ) );
}

#else  /* defined(OSMEMPROTECTION) */

#define Schedule( ) OS_Schedule( )

#endif /* defined(OSMEMPROTECTION) */

#if !defined(OSSC1)
extern void OSTaskInternalDispatch(void);
#endif

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* OSSCHAPI_H */
