#ifndef OSCTRAPI_H
#define OSCTRAPI_H
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
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/inc/osctrapi.h,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* Functions:    
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  API for OSEK OS counters    
*
* Notes:        
*
******************************************************************************/

#if defined(OSCOUNTER)
#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#define OSNSYSHWCTRS OSNHWCTRS

#if (OSNSYSTMRS > 0)
enum {
    OSTIMER1
#if defined(OSSECONDTIMER)
    ,
    OSTIMER2
#endif
};
#endif /* (OSNSYSTMRS > 0) */

#if OSNCTRS > OSNHWCTRS
#define OSSWCOUNTER             /* there are SW counters */
#endif

#if defined(OSSECONDTIMER)
#if (OSNHWCTRS  < 2)
#define OSSECONDSOFT            /* Second Timer is SW */
#endif
#endif


#if(OSNSYSTMRS > 0)

#include <ostimer.h>

#endif

#if defined(OSHWCOUNTER)

/* OS internal macros */
#if defined(OSSECONDTIMER) || defined(OS2SECONDTIMER)
#define OSHWCtrCancel( ctrId )      OSSysTimerCancel( ctrId )
#else
#define OSHWCtrCancel( ctrId )      OSSysTimerCancel()
#endif

#if OSNHWCTRS == 1

#define OSHWCtrArm( ctrId, value )  OSSysTimerArm( value )
void OSSysTimerArm( OSHWTickType ticks );

#elif OSNHWCTRS > 1

#define OSHWCtrArm( ctrId, value )  OSSysTimerArm( ctrId, value )
void OSSysTimerArm( OSWORD ctrInd, OSHWTickType ticks );

#endif  /* OSNHWCTRS == 1 */

#endif  /* defined(OSHWCOUNTER) */

/*  OSEK naming conventions */

/*  Private OS Services */

#if defined(OSSWCOUNTER)

#define OSSWCtrInit( ctrId, vl )    OsCounters[ctrId].value = vl
#define OSSWCtrValue( ctrId )       OsCounters[ctrId].value

#endif

#if defined(OSSYSTIMER) || defined(OS2SYSTIMER)

#if defined(OSSYSTIMER)
extern void OSISRSystemTimer( void );
#endif
#if defined(OS2SYSTIMER)
extern void OSISRSystemTimerCore1( void );
#endif

#if defined(OSSECONDTIMER) || defined(OS2SECONDTIMER)

#if defined(OSSECONDTIMER)
extern void OSISRSecondTimer( void );
#endif
#if defined(OS2SECONDTIMER)
extern void OSISRSecondTimerCore1( void );
#endif

void OSSysTimerCancel( OSWORD ctrInd );
#else
void OSSysTimerCancel( void );

#endif /* defined(OSSECONDTIMER) || defined(OS2SECONDTIMER) */
#endif /* defined(OSSYSTIMER) || defined(OS2SYSTIMER) */

#if defined(OSSWCOUNTER)

#define OSIncrementCounter( ctrId )                                     \
    if( OSSWCtrValue(ctrId) == OsCountersCfg[ctrId].maxallowedvalue )   \
    {                                                                   \
        OSSWCtrInit( ctrId, 0 );                                        \
    }                                                                   \
    else                                                                \
    {                                                                   \
        OSSWCtrValue(ctrId)++;                                          \
    }                                                                   \

#if OSNALMS > 0

#define OSCounterTrigger(ctrInd)                 \
    OSIncrementCounter(ctrInd)                   \
    OSCheckAlarms(ctrInd)

#if defined(OSALMINCCOUNTER)
extern void OSAlmCounterTrigger(OSWORD ctrInd);
#endif

#else   /* OSNALMS > 0 */

#define OSCounterTrigger(ctrInd)                \
    OSIncrementCounter(ctrInd)

#endif /* OSNALMS > 0 */

#endif /* defined(OSSWCOUNTER) */


/*  Public OS Services  */

#if OSNCTRS > 0

#define DeclareCounter(Counter)  extern OSBYTE osdummy

StatusType OS_InitCounter( CounterType ctrId, TickType value );
StatusType OS_GetCounterValue( CounterType ctrId, TickRefType tickRef );
StatusType OS_GetElapsedCounterValue( CounterType ctrId, TickRefType previousValue, TickRefType tickRef );
StatusType OS_IncrementCounter( CounterType ctrId );
StatusType OS_GetCounterInfo ( CounterType ctrId, CtrInfoRefType info );

#if defined(OSMEMPROTECTION)
OSINLINE StatusType InitCounter( CounterType ctrId, TickType value )
{
    return OSServiceCall2( StatusType, ctrId, value, InitCounter );
}
OSINLINE StatusType GetCounterValue( CounterType ctrId, TickRefType tickRef )
{
    return OSServiceCall2( StatusType, ctrId, tickRef, GetCounterValue );
}
OSINLINE StatusType GetElapsedCounterValue( CounterType ctrId, TickRefType previousValue, TickRefType tickRef )
{
    return OSServiceCall3( StatusType, ctrId, previousValue, tickRef, GetElapsedCounterValue );
}
OSINLINE StatusType IncrementCounter( CounterType ctrId )
{
    return OSServiceCall1( StatusType, ctrId, IncrementCounter );
}
OSINLINE StatusType GetCounterInfo ( CounterType ctrId, CtrInfoRefType info )
{
    return OSServiceCall2( StatusType, ctrId, info, GetCounterInfo );
}
#else
#define InitCounter(ctrId, value)                             OS_InitCounter(ctrId, value)
#define GetCounterValue(ctrId, tickRef)                       OS_GetCounterValue(ctrId, tickRef)
#define GetElapsedCounterValue(ctrId, previousValue, tickRef) OS_GetElapsedCounterValue(ctrId, previousValue, tickRef)
#define IncrementCounter(ctrId)                               OS_IncrementCounter(ctrId)
#define GetCounterInfo(ctrId, info)                           OS_GetCounterInfo(ctrId, info)
#endif

#endif  /* OSNCTRS > 0  */

#if defined(OSSYSTIMER) || defined(OS2SYSTIMER)

#if (OSORTIDEBUGLEVEL > 0)
#define GetTimeStamp() (OSWORD)(OSHWCtrValue(0))
#endif  /* (OSORTIDEBUGLEVEL > 0) */

void OSShutdownSystemTimer( void );
void OSInitializeSystemTimer( void );

#endif /* defined(OSSYSTIMER) || defined(OS2SYSTIMER) */

#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif  /* defined(OSCOUNTER) */
#endif  /* OSCTRAPI_H */
