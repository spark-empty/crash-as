#define OSRES_C
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
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/src/osres.c,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* Functions:    
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  Function code to support OSEK OS resources  
*
* Notes:        
*
******************************************************************************/

#define OS_INTERNAL 1
#include    <os.h>
#undef OS_INTERNAL

#define OSTEXT_START_SEC_CODE
#include "ossections.h"

                                                /*  Conditional compilation */
/*  Resource management */

/*  Private OS Services */

#if defined(OSRESOURCE)
#define OSRESIDISINVALID(resId) ((OS_GETOBJTYP(resId) != OBJECT_RESOURCE) || (resId >= OS_MKOBJID(OBJECT_RESOURCE,OSNALLRES)))

/******************************************************************************
 * Function:    GetResource
 *
 * Description: Occupies resource
 *
 * inp:         resId - resource identifer
 *
 * Returns:     E_OK, E_OS_ID, E_OS_ACCESS
 *
 ******************************************************************************/

StatusType OS_GetResource( ResourceType resId )
{
    volatile OSINTMASKTYPE msr;
    volatile OSIMSAVE                   /* volatile OSINTMASKTYPE save; */
    OSResType resRef;
#if defined(OSRESOURCEISR) && defined(OSUSERESLINK)
    OSResType* curResRef;

    if(OSISRLEVELMASKED > 0)
    {
        curResRef = &(OsIsrArray[OSISRLEVELMASKED - 1]->resources);
    }
    else
    {
        curResRef = &(OsRunning->resources);
    }
#endif /* defined(OSRESOURCEISR) && defined(OSUSERESLINK) */

    OSOrtiSetServiceWatch( OSServiceId_GetResource );

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_GetResource, resId ); 
        }
        else
#endif        
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_GetResource, resId ); 
        }
    }
#endif /* OSCHECKCONTEXT */    

#if defined(OSEXTSTATUS)
    if( OSRESIDISINVALID(resId) ) /* invalid ID */
    {                                           
        OSRETERROR( E_OS_ID, OSServiceId_GetResource, resId );
    }
#endif /* OSEXTSTATUS */

    resRef = &OsResources[OS_GETOBJIND(resId)];

#if defined(OSEXTSTATUS)
    if( resRef->isUsed ) /* attempt to access occupied resource  */
    {                         
        OSRETERROR( E_OS_ACCESS, OSServiceId_GetResource, resId );
    }                                   
#if defined(OSISRENTRYEXIT)
    if( OSISRLEVEL != 0 ) /* Check call level */
    {                                 
#if defined(OSRESOURCEISR)
        if( resRef->prio < 0 ) /* prio < 0 - ISR resource */
        {
           if( OsIsrArray[OSISRLEVELMASKED-1]->prio > ( -(resRef->prio) ) ) /* resource priority is lower than assigned ISR priority */
           {       
               OSRETERROR( E_OS_ACCESS, OSServiceId_GetResource, resId );
           }
        }
        else                             /* resource is not for ISR */
#endif
        {
            OSRETERROR( E_OS_ACCESS, OSServiceId_GetResource, resId );
        }
    }
#endif /* OSISRENTRYEXIT */
#if defined(OSRESOURCEISR)
    if( resRef->prio >= 0 ) /* prio >= 0 - TASK resource */
#endif
    {
        if( OSTSKPRIO(OsRunning) < resRef->prio ) /* or resource with lower priority      */
        {                         
            OSRETERROR( E_OS_ACCESS, OSServiceId_GetResource, resId );  
        }
    }                                   
#endif /* OSEXTSTATUS */

    OSCHECKACCESSRIGHTS( OsResources[OS_GETOBJIND(resId)].appMask, OSServiceId_GetResource, resId );

    OSDIS( save );
    OSTPStartResLockTime( OS_GETOBJIND(resId) ); 

#if defined(OSEXTSTATUS) || (OSORTIDEBUGLEVEL > 0)
    resRef->isUsed = 1;
#endif
#if defined(OSRESOURCEISR)
    if( resRef->prio < 0 ) /* prio < 0 - ISR resource */
    {
        OsIsrLevel |= OSISRRESOURCELEVEL;   /* block scheduler */

        resRef->savedIsrMask = save; 
        save = -(resRef->prio);
        
        if( save < resRef->savedIsrMask )
        {
            save = resRef->savedIsrMask;
        }
#if defined(OSUSERESLINK)
        resRef->nextRes = *curResRef;
        *curResRef = resRef;
#endif
    }
    else                                /* Task level resource */
#endif /* defined(OSRESOURCEISR) */
    {
        resRef->prio2task = OSGETTASK(resRef->prio);
        OSGETTASK( resRef->prio ) = OsRunning;

        OSSetPrioBit( resRef->prio );

        resRef->nextRes = OsRunning->resources;
        OsRunning->resources = resRef;
    }  
     
#if(OSORTIDEBUGLEVEL > 0)
    resRef->curPrio = OsRunning->curPrio; /* save the current task prio value */

    if( OsRunning->curPrio > resRef->prio )     /* internal prio are in reversed order */
    {
        OsRunning->curPrio = resRef->prio;
    }
#endif /* (OSORTIDEBUGLEVEL > 0) */

    OSRI( save );
    OSOrtiServiceWatchOnExit( OSServiceId_GetResource );
    
#if defined(OSRESOURCEISR)
    if( resRef->prio < 0 ) /* prio < 0 - ISR resource */
    {
        OsISRResourceCounter++;
    }
#endif /* defined(OSRESOURCEISR) */
    return( E_OK );
}

#if defined(OSRESOURCEISR) && defined(OSUSERESLINK) 
/******************************************************************************
 * Function:    OSReleaseISRResources
 *
 * Description: Releases resources of the ISR without any checking
 *
 * Returns:     none 
 *
 * Notes:       intended for "kill" functions
 ******************************************************************************/
void OSReleaseISRResources(OSRESCB** resources)
{
    OSRESCB* resRef;
    volatile OSINTMASKTYPE msr;

    while(*resources != OSNULLRES)
    {
        resRef =  *resources;

#if (OSORTIDEBUGLEVEL > 0) || defined(OSEXTSTATUS)
        resRef->isUsed = 0;
#endif
        *resources = resRef->nextRes;

        OsISRResourceCounter--;
        if( OsISRResourceCounter == 0 )         /* It is the first ISR resource */ 
        {
            OsIsrLevel &= ~OSISRRESOURCELEVEL;  /* unblock scheduler */
        }
    }
}
#endif /* defined(OSRESOURCEISR) && defined(OSUSERESLINK) */

/******************************************************************************
 * Function:    ReleaseResource
 *
 * Description: releases resource, rescheduling may occur
 *
 * inp:     resID - resource identifer
 *
 * Returns: E_OK, E_OS_ID, E_OS_ACCESS, E_OS_NOFUNC
 *
 ******************************************************************************/

StatusType OS_ReleaseResource( ResourceType resId )
{
    volatile OSINTMASKTYPE msr;
    volatile OSIMSAVE                   /* volatile OSINTMASKTYPE save; */
    OSResType resRef;
#if defined(OSRESOURCEISR) && defined(OSUSERESLINK)
    OSResType* curResRef;       /* reference to ISR or Task resource field */

    OSOrtiSetServiceWatch( OSServiceId_ReleaseResource );

    if(OSISRLEVELMASKED > 0)
    {
        curResRef = &(OsIsrArray[OSISRLEVELMASKED - 1]->resources);
    }
    else
    {
        curResRef = &(OsRunning->resources);
    }
#else 
    OSOrtiSetServiceWatch( OSServiceId_ReleaseResource );
#endif /* defined(OSRESOURCEISR) && defined(OSUSERESLINK) */

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_ReleaseResource, resId ); 
        }
        else
#endif        
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_ReleaseResource, resId ); 
        }
    }
#endif /* OSCHECKCONTEXT */    

#if defined(OSEXTSTATUS)
    if( OSRESIDISINVALID(resId) ) /* invalid ID */
    {
        OSRETERROR( E_OS_ID, OSServiceId_ReleaseResource, resId );
    }
#endif /* OSEXTSTATUS */

    resRef = &OsResources[OS_GETOBJIND(resId)];

#if defined(OSEXTSTATUS)
    if( !( resRef->isUsed ) )        /* attempt to access not occupied resource */
    {                         
        OSRETERROR( E_OS_NOFUNC, OSServiceId_ReleaseResource, resId ); 
    }                      
#if defined(OSRESOURCEISR) 
    if( resRef->prio < 0 )           /* ISR resource */
    {
        if( *curResRef != resRef) /* another resource has to be released before */
        {
            OSRETERROR( E_OS_NOFUNC, OSServiceId_ReleaseResource, resId ); 
        }                                
#if defined(OSISRENTRYEXIT)
        if( OSISRLEVEL != 0 )       /* Check call level */
        {
            if( OsIsrArray[OSISRLEVELMASKED-1]->prio > ( -(resRef->prio) ) ) /* resource priority is lower than assigned ISR priority */
            {       
                OSRETERROR( E_OS_ACCESS, OSServiceId_ReleaseResource, resId );
            }
        }
#endif/*defined(OSISRENTRYEXIT)*/
    }
    else                 /* TASK resource */
#endif /* defined(OSRESOURCEISR) */
    {
        if( OsRunning->resources != resRef ) /* another resource has to be released before */
        {
            OSRETERROR( E_OS_NOFUNC, OSServiceId_ReleaseResource, resId );
        }
#if defined(OSISRENTRYEXIT)
        if( OSISRLEVELMASKED != 0 ) /* Check call level */
        {
            OSRETERROR( E_OS_ACCESS, OSServiceId_ReleaseResource, resId ); /* resource is not for ISR */
        }
#endif
        if( OSTSKPRIO(OsRunning) < resRef->prio ) /* or resource with lower priority */
        {
            OSRETERROR( E_OS_ACCESS, OSServiceId_ReleaseResource, resId); 
        }
    }
#endif /* OSEXTSTATUS */

    OSCHECKACCESSRIGHTS( OsResources[OS_GETOBJIND(resId)].appMask, OSServiceId_ReleaseResource, resId );

    OSDIS( save );
    OSOrtiSetOldServiceID( OSServiceId_ReleaseResource );

    OSTPResetResLockTime(resRef);
    
#if defined(OSRESOURCEISR)
    if( resRef->prio < 0 ) /* prio < 0 - ISR resource */
    {
#if (OSORTIDEBUGLEVEL > 0) || defined(OSEXTSTATUS)
        resRef->isUsed = 0;
#endif
#if defined(OSUSERESLINK)
        *curResRef = resRef->nextRes;
#endif
        save = resRef->savedIsrMask; 

        OsISRResourceCounter--;
        if( OsISRResourceCounter == 0 )         /* It is the first ISR resource */ 
        {
            OsIsrLevel &= ~OSISRRESOURCELEVEL;  /* unblock scheduler */
        }
    }
    else
#endif /* OSRESOURCEISR */
    {
        OSGETTASK( resRef->prio ) = resRef->prio2task;

#if defined(OSECC)
        if( (OSTASKSTATUS(OSGETTASK(resRef->prio)->taskId) & ( OSTCBNOSUSPENDED | OSTCBWAIT )) != OSTCBNOSUSPENDED )
#else
        if( (OSTASKSTATUS(OSGETTASK(resRef->prio)->taskId) & OSTCBNOSUSPENDED) == 0 )
#endif
        {
            OSTask2Suspend( resRef->prio ); 
        }
#if (OSORTIDEBUGLEVEL > 0) || defined(OSEXTSTATUS)
        resRef->isUsed = 0;
#endif

#if defined(OSUSERESLINK)
        OsRunning->resources = resRef->nextRes;
#endif
    }
    
#if(OSORTIDEBUGLEVEL > 0)
    if( OsRunning->curPrio < resRef->curPrio )
    {
        OsRunning->curPrio = resRef->curPrio;
    }
#endif

    if( ( OsRunning != OSGETMAXPRIOTASK )
#if defined(OSISRENTRYEXIT)
        && ( OsIsrLevel == 0 )
#endif
        )
    {
        OSDISPATCH( );
    }
    
    OSOrtiResetIdOnExit( );
    OSRI( save );
    return( E_OK );
}
#endif /* OSRESOURCE */
