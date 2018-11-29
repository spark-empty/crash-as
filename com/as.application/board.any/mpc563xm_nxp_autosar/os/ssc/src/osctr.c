#define OSCTR_C
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
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/src/osctr.c,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* Functions:    
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  Function code to support OSEK OS counters       
*
* Notes:        
*
******************************************************************************/

#define OS_INTERNAL 1
#include    <os.h>
#undef OS_INTERNAL

#define OSTEXT_START_SEC_CODE
#include "ossections.h"

#if defined(OSCOUNTER)
/*  Private OS Services */
#if !defined(OSEXTSTATUS)
#define ctrInd ctrId
#endif

#define OSCTRIDISINVALID(ctrId) ((OS_GETOBJTYP(ctrId) != OBJECT_COUNTER) || (ctrId >= OS_MKOBJID(OBJECT_COUNTER,OSNCTRS)))

#if defined(OSSYSTIMER) || defined(OS2SYSTIMER)
/***************************************************************************
 * Function :   OSSysTimerCancel
 *
 * Description: disable interrupts from output compare channel
 *
 * Returns: 
 *
 * Notes:       for HW counters
 *
 **************************************************************************/
#if defined(OSSECONDTIMER) || defined(OS2SECONDTIMER)

void OSSysTimerCancel( OSWORD ctrInd )
{
#if defined(OSSECONDTIMER)
    {
        if( ctrInd == OSTIMER1 )                /* SysTimer ID */
        {
            OSSysTimDisableInt( );              /* disable output compare interrupt     */
            OSSysTimClearFlag( );               /* clear output compare interrupt flag  */
        }
        else                                    /* SecondTimer ID */
        {
            OSSecondDisableInt( );              /* disable output compare interrupt     */
            OSSecondClearFlag( );               /* clear output compare interrupt flag  */
        }
    }
#endif /* defined(OSSECONDTIMER) */

    OSMSYNC( );
}
#else   /* defined(OSSECONDTIMER) || defined(OS2SECONDTIMER) */

void OSSysTimerCancel( void )
{
#if defined(OSSYSTIMER)
    {
        OSSysTimDisableInt( );                  /* disable output compare interrupt     */
        OSSysTimClearFlag( );                   /* clear output compare interrupt flag  */
    }    
#endif /* defined(OSSYSTIMER) */

    OSMSYNC( );
}
#endif  /* defined(OSSECONDTIMER) || defined(OS2SECONDTIMER) */
#endif  /* defined(OSSYSTIMER) || defined(OS2SYSTIMER) */

#if defined(OSHWCOUNTER)
/***************************************************************************
 * Function :   OSSysTimerArm
 *
 * Description: set interruption point and enable interrupts
 *
 * Returns: 
 *
 * Notes:
 *
 **************************************************************************/
#if OSNHWCTRS == 1
void OSSysTimerArm( OSHWTickType ticks )
#elif OSNHWCTRS > 1
void OSSysTimerArm( OSWORD ctrInd, OSHWTickType ticks )
#endif  /* OSNHWCTRS == 1 */
{
#if (OSNSYSHWCTRS > 0)
    {    
#if (OSNSYSHWCTRS == 2)
        if( ctrInd == OSTIMER1 )                /* (CORE0)SysTimer ID */
        {                                                
#endif
            OSTIMCHOC = ticks;                  /* set next point to OC register */
            OSSysTimClearFlag();                /* clear output compare interrupt flag  */
            OSSysTimEnableInt();                /* enable interrupts on channel */
#if (OSNSYSHWCTRS == 2)
        }
        else                                    /* SecondTimer ID */
        {                                       /* this is for Second Timer */
            OSTIM2CHOC = ticks;                 /* set next point to OC register */
            OSSecondClearFlag();                /* clear output compare interrupt flag  */
            OSSecondEnableInt();                /* enable interrupts on channel */
        }
#endif
    }
#endif  /* (OSNSYSHWCTRS > 0) */
}
#endif /* defined(OSHWCOUNTER) */

#if (OSNSYSHWCTRS > 0)
/***************************************************************************
 * Function :   OSISRSystemTimer
 *
 * Description: ISR for system timer
 *
 * Notes:       called only if timer is armed (HW counter used)
 *
 **************************************************************************/
void OSISRSystemTimer( void )
{

    if( OSInterruptRaised( OSTIMER1 ) )     /* spurious interrupt might occur due to old INTC bug */
    {
        OSSetCurApp(INVALID_OSAPPLICATION); /* OS ISR does not belongs to any OS-Application */
        OSSystemEnterISR2();
        OSSysTimClearFlag();
        OSDI();
#if (OSNALMS > 0)
        OSCounterNotify( OSTIMER1 );
#endif
        OSSystemLeaveISR2();
    }
    OSWARNSUPPRESS 
}

#if OSNSYSHWCTRS == 2
/***************************************************************************
 * Function :   OSISRSecondTimer
 *
 * Description: ISR for second timer
 *
 * Returns:
 *
 * Notes:       called only if timer is armed (HW counter used)
 *
 **************************************************************************/
void OSISRSecondTimer( void )               /* timer ISR (category 2)   */
{
    if( OSInterruptRaised( OSTIMER2 ) )     /* spurious interrupt might occur due to old INTC bug */
    {
        OSSetCurApp(INVALID_OSAPPLICATION); /* OS ISR does not belongs to any OS-Application */
        OSSystemEnterISR2();
        OSSecondClearFlag();
        OSDI();
#if (OSNALMS > 0)
        OSCounterNotify( OSTIMER2 );
#endif
        OSSystemLeaveISR2();
    }
        OSWARNSUPPRESS 
}
#endif  /* OSNSYSHWCTRS == 2 */

#else   /* (OSNSYSHWCTRS > 0) */

#if defined(OSSYSTIMER)      /* 1st system timer is SW */
/***************************************************************************
 * Function :   OSISRSystemTimer
 *
 * Description: ISR for system timer
 *
 * Returns: 
 *
 * Notes:       SW counter used
 *
 **************************************************************************/
void OSISRSystemTimer( void )               /* timer ISR (category 2)   */
{
#if defined(OSTIMSTM)
    TickType Tcnt;
#endif  /* defined(OSTIMSTM) */

    OSSetCurApp(INVALID_OSAPPLICATION);     /* OS ISR does not belongs to any OS-Application */
    OSSystemEnterISR2();
    OSSysTimClearFlag();
    OSDI();    

#if defined(OSTIMSTM)
#if (OSTIMMODULO < 0x80000000U)
again:
#endif  /* (OSTIMMODULO < 0x80000000) */

    Tcnt = OSTIMCHOC + OSTIMMODULO;         /* set new value of the STM counter register for next interrupt */
    OSTIMCHOC = Tcnt;                       /* set next value for interrupt */

#endif  /* defined(OSTIMSTM) */

#if !defined(OSALMINCCOUNTER)
    OSCounterTrigger(OSTIMER1);
#else
    OSAlmCounterTrigger(OSTIMER1);
#endif /* !defined(OSALMINCCOUNTER) */

#if defined(OSTIMSTM)
#if defined(OSTIMMODULO)
#if (OSTIMMODULO < 0x80000000U)
    Tcnt -= OSTIMMODULO;
    if( (TickType)(OSTIMTCNT - Tcnt) > OSTIMMODULO )
    {
        OSSysTimClearFlag();
        goto again;
    }
#endif  /* (OSTIMMODULO < 0x80000000) */

#endif  /* defined(OSTIMMODULO) */
#endif  /* defined(OSTIMSTM) */

    OSSystemLeaveISR2();
    OSWARNSUPPRESS
}

#endif  /* defined(OSSYSTIMER)  */
#endif  /* (OSNSYSHWCTRS == 1) */

#if defined(OSSECONDSOFT)
/***************************************************************************
 * Function :   OSISRSecondTimer
 *
 * Description: ISR for 2nd system timer
 *
 * Returns: 
 *
 * Notes:       SW couner used
 *
 **************************************************************************/
void OSISRSecondTimer( void )               /* timer ISR (category 2)   */
{
#if defined(OSTIM2STM)
    TickType Tcnt;
#endif  /* defined(OSTIM2STM) */

    OSSetCurApp(INVALID_OSAPPLICATION);     /* OS ISR does not belongs to any OS-Application */
    OSSystemEnterISR2();
    OSSecondClearFlag();
    OSDI();

#if defined(OSTIM2STM)
#if (OSTIM2MODULO < 0x80000000U)
again:
#endif  /* (OSTIM2MODULO < 0x80000000) */

    Tcnt = OSTIM2CHOC + OSTIM2MODULO;       /* set new value of the STM counter register for next interrupt */
    OSTIM2CHOC = Tcnt;                      /* set next value for interrupt */

#endif  /* defined(OSTIM2STM) */

#if !defined(OSALMINCCOUNTER)
    OSCounterTrigger(OSTIMER2);
#else
    OSAlmCounterTrigger(OSTIMER2);
#endif /* !defined(OSALMINCCOUNTER) */

#if defined(OSTIM2STM)
#if defined(OSTIM2MODULO)
#if (OSTIM2MODULO < 0x80000000U)
    Tcnt -= OSTIM2MODULO;
    if( (TickType)(OSTIM2TCNT - Tcnt) > OSTIM2MODULO )
    {
        OSSecondClearFlag();
        goto again;
    }
#endif  /* (OSTIM2MODULO < 0x80000000) */

#endif  /* defined(OSTIM2MODULO) */
#endif  /* defined(OSTIM2STM) */

    OSSystemLeaveISR2();
    OSWARNSUPPRESS
}

#endif  /* defined(OSSECONDSOFT) */


#if defined(OSSYSTIMER) || defined(OS2SYSTIMER)
/***************************************************************************
 * Function :   OSShutdownSystemTimer
 *
 * Description: disable all timer(s)
 *
 * Returns: 
 *
 * Notes:       only interrupts are disabled, timers are not stopped
 *
 **************************************************************************/
void OSShutdownSystemTimer( void )
{
#if defined(OSSYSTIMER)
#if defined(OSSECONDTIMER)
    OSSysTimerCancel( OSTIMER1 );
    OSSysTimStop();
    OSSysTimerCancel( OSTIMER2 );
    OSSecondStop();
#else
    OSSysTimerCancel();
    OSSysTimStop();
#endif
#endif /* defined(OSSYSTIMER) */
#if defined(OS2SYSTIMER) 
#endif /* OSMC */
}

/***************************************************************************
 * Function :   OSInitializeSystemTimer
 *
 * Description: initialize HW and start timer(s)
 *
 * Notes:       1. MPC55xx/56xx HW specific,
 *              2. called with interrupts disabled 
 *
 **************************************************************************/
void OSInitializeSystemTimer( void )
{
    /* System Timer initialization */
#if defined(OSSYSTIMER)
    {
        OSSysTimSetHW();                /*(CORE0) System Timer HW initialization */
        OSSysTimClearFlag();            /* clear interrupt flag  */
#if (OSNSYSHWCTRS == 0)
        OSSysTimEnableInt();            /* enable interrupt for SW system timer */
#endif
    }
#endif
    /* Second Timer initialization */
#if defined(OSSECONDTIMER) || defined(OS2SECONDTIMER)
#if defined(OSSECONDTIMER)
    {
        OSSecondSetHW();                /* second timer HW initialization */
        OSSecondClearFlag();            /* clear interrupt flag  */
#if (OSNSYSHWCTRS < 2)
        OSSecondEnableInt();            /* enable interrupt for SW second timer */
#endif
    }
#endif
#endif /* defined(OSSECONDTIMER) || defined(OS2SECONDTIMER) */ 
}
#endif  /* defined(OSSYSTIMER) || defined(OS2SYSTIMER) */

/* Public services */

/******************************************************************************
 * Function:    InitCounter
 *
 * Description: Set initial counter value
 *
 * Returns:     E_OK, E_ID, E_VALUE, E_CALLEVEL
 *
 * Notes:       1. If alarms are linked to this counter, then its state unchanged.
 *
 ******************************************************************************/
StatusType OS_InitCounter( CounterType ctrId, TickType value )
{
#if defined(OSEXTSTATUS)
    OSWORD  ctrInd;              /* index in Counters table */
#endif

    OSOrtiSetServiceWatch( OSServiceId_InitCounter ); /* set watch to this service */ 

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        { 
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_InitCounter, ctrId ); 
        }
        else
#endif        
        {
            OSRETERROR(E_OS_CALLEVEL, OSServiceId_InitCounter, ctrId); 
        }
    }
#endif /* OSCHECKCONTEXT */

#if defined(OSEXTSTATUS)
    ctrInd = (OSWORD)OS_GETOBJIND(ctrId);

    if( OSCTRIDISINVALID(ctrId) )
    {                                           /* invalid ID */
        OSRETERROR( E_OS_ID, OSServiceId_InitCounter, ctrId );                  
    }
    if( value > OsCountersCfg[ctrInd].maxallowedvalue )
    {                                           /* value is outside of admissible limit */
        OSRETERROR( E_OS_VALUE, OSServiceId_InitCounter, ctrId );               
    }
#endif  /* defined(OSEXTSTATUS) */

    OSCHECKACCESSRIGHTS( OsCounters[ ctrInd ].appMask, OSServiceId_InitCounter, ctrId );

#if defined(OSSWCOUNTER)
#if defined(OSHWCOUNTER)
    if( ctrInd >= OSNHWCTRS )
#endif
    {
        OSSWCtrInit( ctrInd, value);
    }
#endif  /* defined(OSSWCOUNTER) */

#if defined(OSHWCOUNTER)
#if defined(OSSWCOUNTER)
    else
#endif  /* defined(OSSWCOUNTER) */
    {
        OSHWCtrInit( ctrInd, value);
    }
#endif  /* defined(OSHWCOUNTER) */

    OSOrtiServiceWatchOnExit( OSServiceId_InitCounter );
    return E_OK;
}

/******************************************************************************
 * Function:    GetCounterValue
 *
 * Description: Return counter value
 *
 * Returns:     E_OK, E_OS_ID, E_OS_DISABLEDINT
 *
 * Notes:
 *
 ******************************************************************************/
StatusType OS_GetCounterValue( CounterType ctrId, TickRefType tickRef )
{
#if defined(OSEXTSTATUS)
    OSWORD  ctrInd;              /* index in Counters table */
#endif

    OSOrtiSetServiceWatch( OSServiceId_GetCounterValue ); /* set watch to this service */ 

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        { 
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_GetCounterValue, ctrId ); 
        }
        else
#endif        
        {
            OSRETERROR(E_OS_CALLEVEL, OSServiceId_GetCounterValue, ctrId); 
        }
    }
#endif /* OSCHECKCONTEXT */

#if defined(OSEXTSTATUS)
    ctrInd = (OSWORD)OS_GETOBJIND(ctrId);

    if( OSCTRIDISINVALID(ctrId) )
    {                                           /* invalid ID */
        OSRETERROR( E_OS_ID, OSServiceId_GetCounterValue, ctrId );                  
    }
#endif  /* defined(OSEXTSTATUS) */

    OSCHECKACCESSRIGHTS( OsCounters[ ctrInd ].appMask, OSServiceId_GetCounterValue, ctrId );
    OSCHECKWRITEACCESS( tickRef, sizeof(TickType), OSServiceId_GetCounterValue, ctrId );

#if defined(OSSWCOUNTER)
#if defined(OSHWCOUNTER)
    if( ctrInd >= OSNHWCTRS )
#endif
    {
        *tickRef = OSSWCtrValue(ctrInd);
    }
#endif  /* defined(OSSWCOUNTER) */

#if defined(OSHWCOUNTER)
#if defined(OSSWCOUNTER)
    else
#endif  /* defined(OSSWCOUNTER) */
    {
        *tickRef = OSHWCtrValue(ctrInd);
    }
#endif  /* defined(OSHWCOUNTER) */
    OSOrtiServiceWatchOnExit( OSServiceId_GetCounterValue );
    return E_OK;
}

/******************************************************************************
 * Function:    GetElapsedCounterValue
 *
 * Description: Return counter value
 *
 * Returns:     E_OK, E_OS_ID, E_OS_DISABLEDINT
 *
 * Notes:
 *
 ******************************************************************************/
StatusType OS_GetElapsedCounterValue( CounterType ctrId,
                                     TickRefType valueRef,
                                     TickRefType tickRef )
{
    TickType currentValue;
#if defined(OSEXTSTATUS)
    OSWORD  ctrInd;              /* index in Counters table */
#endif

    OSOrtiSetServiceWatch( OSServiceId_GetElapsedCounterValue ); /* set watch to this service */ 

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        { 
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_GetElapsedCounterValue, ctrId ); 
        }
        else
#endif        
        {
            OSRETERROR(E_OS_CALLEVEL, OSServiceId_GetElapsedCounterValue, ctrId); 
        }
    }
#endif /* OSCHECKCONTEXT */

#if defined(OSEXTSTATUS)
    ctrInd = (OSWORD)OS_GETOBJIND(ctrId);

    if( OSCTRIDISINVALID(ctrId) )
    {                                           /* invalid ID */
        OSRETERROR( E_OS_ID, OSServiceId_GetElapsedCounterValue, ctrId );                  
    }
    if( OsCountersCfg[ctrInd].maxallowedvalue < (*valueRef) )
    {
        OSRETERROR( E_OS_VALUE, OSServiceId_GetElapsedCounterValue, ctrId );
    }
#endif  /* defined(OSEXTSTATUS) */

    OSCHECKACCESSRIGHTS( OsCounters[ ctrInd ].appMask, OSServiceId_GetElapsedCounterValue, ctrId );
    OSCHECKWRITEACCESS( tickRef, sizeof(TickRefType), OSServiceId_GetElapsedCounterValue, ctrId );
    OSCHECKWRITEACCESS( valueRef, sizeof(TickRefType), OSServiceId_GetElapsedCounterValue, ctrId );

#if defined(OSSWCOUNTER)
#if defined(OSHWCOUNTER)
    if( ctrInd >= OSNHWCTRS )
#endif
    {
        currentValue = (TickType)OSSWCtrValue(ctrInd);
    }
#endif  /* defined(OSSWCOUNTER) */
#if defined(OSHWCOUNTER)
#if defined(OSSWCOUNTER)
    else
#endif  /* defined(OSSWCOUNTER) */
    {
        currentValue = (TickType)OSHWCtrValue(ctrInd);
    }
#endif  /* defined(OSHWCOUNTER) */

    if( currentValue >= (*valueRef) )
    {
        *tickRef = currentValue - (*valueRef);
    }
    else
    {
        *tickRef = (OsCountersCfg[ctrInd].maxallowedvalue + 1) - ((*valueRef) - currentValue);
    }
    *valueRef = currentValue;
    OSOrtiServiceWatchOnExit( OSServiceId_GetElapsedCounterValue );
    return E_OK;
}

#if defined(OSALMINCCOUNTER)
/******************************************************************************
 * Function:    OSAlmCounterTrigger
 *
 * Description: Increment counter value and another counters values if expired
 *              alarm(s) has "increment counter" action.
 *
 * Returns: 
 *
 * Notes:
 *
 ******************************************************************************/
void OSAlmCounterTrigger(OSWORD ctrInd)
{
    OSWORD index;

    OsCtrIncCounter = 0;

    OSCounterTrigger(ctrInd);

    while ( OsCtrIncCounter != 0 )
    {
        /* Check for all SW counters */
        for( index = OSNHWCTRS; index < OSNCTRS; index++ )
        {
            if( OsCtrIncValue[index-OSNHWCTRS] > 0 )
            {
                OsCtrIncValue[index-OSNHWCTRS]--;
                OsCtrIncCounter--;
                OSCounterTrigger(index);
            }
        }
    }
}
#endif

/******************************************************************************
 * Function:    IncrementCounter
 *
 * Description: Increment counter value and check attached alarms
 *
 * Returns:     E_OK, E_OS_ID, E_OS_DISABLEDINT, E_OS_CALLEVEL
 *
 ******************************************************************************/
StatusType OS_IncrementCounter( CounterType ctrId )
{
#if defined(OSEXTSTATUS)
    OSWORD  ctrInd;              /* index in Counters table */
#endif

    OSIMSAVE               /* OSINTMASKTYPE save;       */

    OSOrtiSetServiceWatch( OSServiceId_IncrementCounter ); /* set watch to this service */ 

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        { 
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_IncrementCounter, ctrId ); 
        }
        else
#endif        
        {
            OSRETERROR(E_OS_CALLEVEL, OSServiceId_IncrementCounter, ctrId); 
        }
    }
#endif /* OSCHECKCONTEXT */

#if defined(OSEXTSTATUS)
    ctrInd = (OSWORD)OS_GETOBJIND(ctrId);

    if( ( OSCTRIDISINVALID(ctrId) )
#if defined(OSHWCOUNTER)
        || ( ctrInd < OSNHWCTRS ) 
#endif
      ) /* invalid ID */
    {                                           
        OSRETERROR( E_OS_ID, OSServiceId_IncrementCounter, ctrId ); 
    }
#endif /* OSEXTSTATUS */

    OSCHECKACCESSRIGHTS( OsCounters[ ctrInd ].appMask, OSServiceId_IncrementCounter, ctrId );

#if defined(OSSWCOUNTER)

    OSDIS( save );
    OSOrtiSetOldServiceID( OSServiceId_IncrementCounter );

#if (OSNALMS > 0)
    OSPUTPARAM( OSServiceId_IncrementCounter, ctrId );
#endif

#if !defined(OSALMINCCOUNTER)
    OSCounterTrigger(ctrInd);
#else
    OSAlmCounterTrigger(ctrInd);
#endif /* !defined(OSALMINCCOUNTER) */

#if (OSNALMS > 0)
    OSCLEARPARAM( );

    if( ( OsRunning != OSGETMAXPRIOTASK )
#if defined(OSISRENTRYEXIT)
        && (OsIsrLevel == 0 )
#endif
      )
    {
        OSDISPATCH( );
    }

#endif /* (OSNALMS > 0) */

    OSOrtiResetIdOnExit( );
    OSRI( save );

#endif /* defined(OSSWCOUNTER) */

    return( E_OK );
}

/******************************************************************************
 * Function:    GetCounterInfo
 *
 * Description: Fill counter info structure
 *
 * Returns:     E_OK, E_OS_ID, E_DISABLEDINT
 *
 * Notes:
 *
 ******************************************************************************/
StatusType OS_GetCounterInfo( CounterType ctrId, CtrInfoRefType info )
{
    OSOrtiSetServiceWatch( OSServiceId_GetCounterInfo ); /* set watch to this service */

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        { 
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_GetCounterInfo, ctrId ); 
        }
        else
#endif        
        {
            OSRETERROR(E_OS_CALLEVEL, OSServiceId_GetCounterInfo, ctrId); 
        }
    }
#endif /* OSCHECKCONTEXT */

#if defined(OSEXTSTATUS)
    if( OSCTRIDISINVALID(ctrId) )
    {                                           /* invalid ID */
        OSRETERROR( E_OS_ID, OSServiceId_GetCounterInfo, ctrId );
    }
#endif /* defined(OSEXTSTATUS) */

    OSCHECKACCESSRIGHTS( OsCounters[ OS_GETOBJIND( ctrId ) ].appMask, OSServiceId_GetCounterInfo, ctrId );
    OSCHECKWRITEACCESS( info, sizeof(CtrInfoType), OSServiceId_GetCounterInfo, ctrId );

    /* Fill counter info structure */
    *info = OsCountersCfg[OS_GETOBJIND(ctrId)];

    OSOrtiServiceWatchOnExit( OSServiceId_GetCounterInfo );
    return( E_OK );
}

#endif  /* defined(OSCOUNTER) */
