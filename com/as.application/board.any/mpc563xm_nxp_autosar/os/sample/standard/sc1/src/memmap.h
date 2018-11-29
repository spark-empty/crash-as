/******************************************************************************
*
*       Freescale(TM) and the Freescale logo are trademarks of Freescale Semiconductor, Inc.
*       All other product or service names are the property of their respective owners.
*       (C) Freescale Semiconductor, Inc. 2009
*
*       THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
*       BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
*       Freescale Semiconductor, Inc.
*
* Description: Memory map file
*
********************************************************************************/

#define MEMMAP_ERROR

/* Here you may define your types yourselves except following types: VAR_*, VAR_FAST_*, CONST_* and CONST_FAST_* */
/* ... */
#if defined(APP_START_SEC_CODE)

#undef APP_START_SEC_CODE
#undef MEMMAP_ERROR

#if defined(OSCWPPC)
#pragma section code_type ".appcode"
#elif defined(OSDIABPPC)
#pragma section CODE ".appcode"
#elif defined(OSGHSPPC)
#pragma ghs section text=".appcode"
#else
#error Unknown compiler
#endif /* OSCWPPC */

#elif defined(APP_STOP_SEC_CODE)

#undef APP_STOP_SEC_CODE
#undef MEMMAP_ERROR

#if defined(OSCWPPC)
#pragma section code_type
#elif defined(OSDIABPPC)
#pragma section CODE
#elif defined(OSGHSPPC)
#pragma ghs section text=default
#else
#error Unknown compiler
#endif /* OSCWPPC */

#elif defined(RCHW_START_SEC_DATA)

#undef RCHW_START_SEC_DATA
#undef MEMMAP_ERROR

#if defined(OSCWPPC)
#pragma section const_type ".rchwdata" ".rchwdata"
#elif defined(OSDIABPPC)
#pragma section CONST ".rchwdata"
#elif defined(OSGHSPPC)
#pragma ghs section const=".rchwdata"
#else
#error Unknown compiler
#endif /* OSCWPPC */

#elif defined(RCHW_STOP_SEC_DATA)

#undef RCHW_STOP_SEC_DATA
#undef MEMMAP_ERROR

#if defined(OSCWPPC)
#pragma section const_type
#elif defined(OSDIABPPC)
#pragma section CONST
#elif defined(OSGHSPPC)
#pragma ghs section const=default
#else
#error Unknown compiler
#endif /* OSCWPPC */

#endif

/* Types generated by OS Sysgen: VAR_*, VAR_FAST_*, CONST_* and CONST_FAST_* */
#include "osmemmap.h"

#ifdef MEMMAP_ERROR                       

#ifdef OSMEMMAP_ERROR                       
#error "MemMap.h, wrong pragma command"
#endif /* OSMEMMAP_ERROR */

#endif /* MEMMAP_ERROR */