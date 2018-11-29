#ifndef OSSETAPI_H
#define OSSETAPI_H
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
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/inc/ossetapi.h,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  API for OSEK OS Start-Up    
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

#define OSMODE     0            /* application mode */

/*  Constructional elements */

/*  OSEK naming conventions */

/*  Private OS Services */
/*  Public OS Services  */

/*  Startup/Shutdown    */

#define OSDEFAULTAPPMODE (AppModeType)0

extern void StartOS( AppModeType mode );
extern void OS_ShutdownOS( StatusType error );
extern void OSShutdownOS( StatusType error );

#if(OSNAPPMODES > 1)
#define OSCURAPPMODE OsCurAppMode
#else  
#define OSCURAPPMODE OSDEFAULTAPPMODE
#endif /* (OSNAPPMODES > 1) */

AppModeType OS_GetActiveApplicationMode( void );


#if defined(OSAPPLICATION)
void OSInitApplications( void ); /* making OsAppTable of OsCfgAppTable */
#endif

#if defined(OSMEMPROTECTION)

OSINLINE void ShutdownOS( StatusType error )
{
    OSServiceCall1( void, error, ShutdownOS );
}

OSINLINE AppModeType GetActiveApplicationMode( void )
{
    return OSServiceCall0( AppModeType, GetActiveApplicationMode );
}

extern const OS_AppType OsAppCfgTable[OSNAPPS];

#else /* OSMEMPROTECTION */ 

#define ShutdownOS( error ) OS_ShutdownOS( error )
#define OSCallShutdownHook(error) ShutdownHook(error)
#if defined(OSCHECKCONTEXT)
#define GetActiveApplicationMode() OS_GetActiveApplicationMode()
#else  /* defined(OSCHECKCONTEXT) */
#if defined(OSORTICURRENTSERVICEID)
#define GetActiveApplicationMode() (OSOrtiSetServiceWatch( OSServiceId_GetActiveApplicationMode ), \
                                    OSOrtiServiceWatchOnExit( OSServiceId_GetActiveApplicationMode ), \
                                    OSCURAPPMODE)
#else  /*OSORTICURRENTSERVICEID*/
#define GetActiveApplicationMode()  OSCURAPPMODE
#endif /*defined(OSORTICURRENTSERVICEID)*/
#endif /* defined(OSCHECKCONTEXT) */

# endif /* defined(OSMEMPROTECTION)*/

#if defined(OSHOOKSCHEDULER)    /* not configurable by OIL */
#define OSHOOK_START_SEC_CODE
#include "ossections.h"
void IdleLoopHook( void );
#define OSTEXT_START_SEC_CODE
#include "ossections.h"
#endif

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* OSSETAPI_H */
