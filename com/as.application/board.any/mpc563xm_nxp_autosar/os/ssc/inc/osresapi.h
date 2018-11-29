#ifndef OSRESAPI_H
#define OSRESAPI_H
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
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/inc/osresapi.h,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  API for OSEK OS resource management
*
* Notes:        
*
******************************************************************************/

#if defined(OSRESOURCE)

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */


/*  Private OS Services */

#if defined(OSRESOURCEISR)   

#if defined(OSUSERESLINK)
void OSReleaseISRResources(OSRESCB** resources);
#endif
#endif /* defined(OSRESOURCEISR) */    

StatusType OS_GetResource( ResourceType resId );
StatusType OS_ReleaseResource( ResourceType resId );

#if defined(OSUSETCB)
#define OSNULLPRIOLINK (OSTSKCBPTR)0
#endif

#define OSNULLRES  (OSResType)0

/* Configuration Data   */
#if defined(OSAPPLICATION)
extern const OSRESCFG OsResCfg[OSNRESS + OSNISRRESS];
#else
extern const OSPRIOTYPE OsResPrioTbl[OSNRESS + OSNISRRESS];
#endif /* defined(OSAPPLICATION) */


/*  Public OS Services  */

#define DeclareResource(ResID) extern OSBYTE osdummy

#if defined(OSMEMPROTECTION)

OSINLINE StatusType GetResource( ResourceType resId )
{
    return OSServiceCall1( StatusType, resId, GetResource );
}

OSINLINE StatusType ReleaseResource( ResourceType resId )
{
    return OSServiceCall1( StatusType, resId, ReleaseResource );
}

#else
#define GetResource(resId)     OS_GetResource(resId)
#define ReleaseResource(resId) OS_ReleaseResource(resId)
#endif


#ifdef __cplusplus
}
#endif  /* __cplusplus */

#else   /* defined(OSRESOURCE) */

#if defined(OSINRES)                /* if there are internal Resources  */
#define DeclareResource(ResID) extern OSBYTE osdummy
#endif

#endif  /* defined(OSRESOURCE) */

#endif  /* OSRESAPI_H */


