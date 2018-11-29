#ifndef OSAPI_H 
#define OSAPI_H
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
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/inc/os.h,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  API for OSEK OS
*
* Notes:        1.  Property file must be included before this file.
*
******************************************************************************/

#if !defined(OSPROPH)   
#include    "osprop.h"                          /* OS Properties */
#else   /* !defined(OSPROPH)    */
#include    OSPROPH                             /* OS Properties */
#endif  /* !defined(OSPROPH)    */

#if !defined(OSCWPPC)
#if defined(__MWERKS__)
#define OSCWPPC
#endif  /* defined(__MWERKS__) */
#endif

#if defined(OSGHSPPC)
#include <ppc_ghs.h>    /* for intrinsic functions only */
#endif

#if !defined(OSCWPPC) && !defined(OSDIABPPC) && !defined(OSGHSPPC)
#error Compiler is not defined
#endif

#include "osversion.h"                          /* OS version info */

#define OSVLE                       /* OS is to be compiled in VLE mode only */

#if defined(OSBCC1)
#define OSBCC
#endif

#if defined(OSECC1)
#define OSECC
#endif

#if defined(OSSC2) || defined(OSSC4)
/* Time protection */
#define OSTIMINGPROTECTION   
#endif  /* defined(OSSC2) || defined(OSSC4) */

#if defined(OSSC3) || defined(OSSC4)
/* Memory protection */
#define OSMEMPROTECTION   
#endif

#if (OSNAPPS > 0)
#define OSAPPLICATION   /* Os-Applications are configured */
#endif

#if defined(OSAPPLICATION) || !defined(OSSC1)
#define OSTERMINATION   /* OS feature to terminate runables via TerminateApplication()
                           or killing because of a protection violation */
#endif

#if defined(OSMPC5634M)
/* Note that OSE200Z3 means e200z335 */
#define OSE200Z3
#endif
#if defined(OSMPC5644A)
#define OSE200Z4
#endif
#if defined(OSMPC5674F)
#define OSE200Z7
#endif
#define OSNCORES 1

#if defined(OSMEMPROTECTION) 
#if !defined(OSEXTSTATUS)
#define OSEXTSTATUS
#endif
#if !defined(OSCOMEXTSTATUS)
#define OSCOMEXTSTATUS
#endif
#endif /* defined(OSMEMPROTECTION) */

#if defined(OSTIMINGPROTECTION) && !defined(OSISRENTRYEXIT)
#define OSISRENTRYEXIT
#endif

#if defined(OSSC2) || ( defined(OSSC1) && ( ( defined(OSISRENTRYEXIT) && defined(OSECC) ) || defined(OSAPPLICATION) ) )
/* if there are ISR2 or systimer then common ISR stack is used in SC2 and SC1, ECC1 */
#define OSUSEISRSTACK                          
#endif

#if defined(OSNOISR1) && !defined(OSISRENTRYEXIT) && !defined(OSTIMINGPROTECTION) && (OSNCORES < 2)
/* same as `#if OSNISR == 0' */
#define OSNOISR
#endif

#if defined(OSEXTSTATUS)
#define OSCHECKDISABLEDINT
#endif

#if defined(OSSTKCHECK)
#define OSSYSSTKCHECK           /* OS checks stacks (no User check functions) */
#endif

#if !defined(OSSC1) || defined(OSECC)
#define OSUSETOS        /* top of stack defined in TagOSTSK  */
#if defined(OSSTKCHECK) || (OSORTIDEBUGLEVEL > 0) || defined(OSMEMPROTECTION)
#define OSUSEBOS        /* bottom of stack defined in TagOSTSK  */
#endif
#endif

#if defined(OSISRENTRYEXIT) || defined(OSHOOKSTARTUP) || defined(OSHOOKSHUTDOWN) || \
    defined(OSHOOKPRETASK) || defined(OSHOOKPOSTTASK) || defined(OSHOOKERROR) || \
    defined(OSHOOKPROTECTION) || defined(OSALMCALLBACK) || defined(OSCOMHOOKERROR) || defined(OSEXTSTATUS)
/* OsIsrLevel is used for context check, including hooks */
#define OSUSEISRLEVEL
#if defined(OSEXTSTATUS)
#define OSCHECKCONTEXT
#endif
#endif

#if defined(OSUSETOS) || defined(OSEXTSTATUS)
#if !defined(OSNOFASTTERMINATE)
#define OSNOFASTTERMINATE   /* FastTerminate may be used only in SC1, BCC1  */
#endif
#endif

#if defined(OSNOFASTTERMINATE) || defined(OSRESOURCE)
#define OSUSETCB            /* OS uses Task Control Block */
#endif

#if defined(OSRESOURCE)
#define OSUSERESLINK
#endif

#if defined(OSNAUTOALMS)
#if OSNAUTOALMS > 0
#define OSAUTOALARMS
#endif  /* OSNAUTOALMS > 0 */
#endif  /* defined(OSNAUTOALMS) */


#define OSORTIDEBUGLEVELNOORTI  0               /* no ORTI support */
#define OSORTIDEBUGLEVELSTATIC  1               /* static ORTI support */
#define OSORTIDEBUGLEVELRUNTIME 2               /* run time and static ORTI support */
#define OSORTIDEBUGLEVELISR     3               /* runtime w/o service trace */

#if !defined(OSORTIDEBUGLEVEL)
#define OSORTIDEBUGLEVEL    OSORTIDEBUGLEVELNOORTI
#endif  /* !defined(OSORTIDEBUGLEVEL) */


#if (OSORTIDEBUGLEVEL == OSORTIDEBUGLEVELISR)
                                                /* level 3 */
#define OSORTIRUNNINGISRID                      /* introducing run-time variable containing */
                                                /* the identifier of currently running ISR */
#else  /* (OSORTIDEBUGLEVEL >= OSORTIDEBUGLEVELISR) */

#if (OSORTIDEBUGLEVEL >= OSORTIDEBUGLEVELRUNTIME)
                                                /* level 2 or 4 */
#define OSORTICURRENTSERVICEID                  /* introducing run-time variable containing */
                                                /* the identifier of currently running OSEK OS service */
#define OSORTIRUNNINGISRID                      /* introducing run-time variable containing */
                                                /* the identifier of currently running ISR */
#endif  /* (OSORTIDEBUGLEVEL >= OSORTIDEBUGLEVELRUNTIME) */
#endif  /* (OSORTIDEBUGLEVEL == OSORTIDEBUGLEVELISR) */

/* OS memory sections */

#define OSTEXT_START_SEC_CODE
#include "ossections.h"
#define OS_START_SEC_VAR_UNSPECIFIED
#include "ossections.h"
#define OS_START_ONCE_SEC_VAR_FAST_UNSPECIFIED
#include "ossections.h"
#define OS_START_SEC_CONST_UNSPECIFIED
#include "ossections.h"

#include    <osbasapi.h>                        /* Basic types and constants, etc.  */
#include    <ostarget.h>                        /* Target-specific definitions      */
#include    <oserrapi.h>
#include    <osdata.h>
#include    <osctrapi.h>
#include    <osalmapi.h>
#include    <osschapi.h>
#include    <osresapi.h>
#include    <osevtapi.h>
#include    <osmemapi.h>
#include    <ossetapi.h>
#include    <ostskapi.h>
#include    <osisrapi.h>
#include    <osmsgapi.h>
#include    <ostpapi.h>

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "ossections.h"
#define OS_STOP_ONCE_SEC_VAR_FAST_UNSPECIFIED
#include "ossections.h"
#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "ossections.h"
#define OSTEXT_STOP_SEC_CODE
#include "ossections.h"

#if !defined(OS_INTERNAL)

#if defined(APPTYPESH)   
#include    APPTYPESH                          /* User types and definitions */
#endif  /* !defined(APPTYPESH)    */

#if !defined(OSCFGH)   
#include    "os_cfg.h"                            /* OS Properties */
#else   /* !defined(OSCFGH)    */
#include    OSCFGH                             /* OS Configuration (generated by SysGen) */
#endif  /* !defined(OSCFGH)    */

#endif  /* !defined(OS_INTERNAL) */

#endif  /* OSAPI_H */
