/******************************************************************************
*
*       Freescale(TM) and the Freescale logo are trademarks of Freescale Semiconductor, Inc.
*       All other product or service names are the property of their respective owners.
*       (C) Freescale Semiconductor, Inc. 2007-2009
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

#endif /* defined(APP_START_SEC_CODE) */

#if defined(__CLASS_SC1) || defined(__CLASS_SC2)

#if defined(TrustedApplication_START_SEC_VAR_UNSPECIFIED)
#undef TrustedApplication_START_SEC_VAR_UNSPECIFIED
#undef MEMMAP_ERROR
#if defined(OSCWPPC)
#pragma section data_type ".app0_vU" ".app0_vU"
#elif defined(OSDIABPPC)
#pragma section DATA ".app0_vU" ".app0_vU"
#elif defined(OSGHSPPC)
#pragma ghs section data=".app0_vU_data"
#pragma ghs section bss=".app0_vU_bss"
#else
#error Unknown compiler
#endif /* OSCWPPC */
#endif

#if defined(TrustedApplication_STOP_SEC_VAR_UNSPECIFIED)
#undef TrustedApplication_STOP_SEC_VAR_UNSPECIFIED
#undef MEMMAP_ERROR
#if defined(OSCWPPC)
#pragma section data_type 
#elif defined(OSDIABPPC)
#pragma section DATA 
#elif defined(OSGHSPPC)
#pragma ghs section bss=default
#pragma ghs section data=default
#else
#error Unknown compiler
#endif /* OSCWPPC */
#endif

#if defined(TrustedApplication_START_SEC_VAR_FAST_UNSPECIFIED)
#undef TrustedApplication_START_SEC_VAR_FAST_UNSPECIFIED
#undef MEMMAP_ERROR
#if defined(OSCWPPC)
#pragma section sdata_type ".sapp_vU_data" ".sapp_vU_bss"
#elif defined(OSDIABPPC)
#pragma option -Xsmall-data=8
#pragma section SDATA ".sapp_vU_data" ".sapp_vU_bss"
#elif defined(OSGHSPPC)
#pragma ghs section sdata=".sapp_vU_data"
#pragma ghs section sbss=".sapp_vU_bss"
#pragma ghs startsda
#else
#error Unknown compiler
#endif /* OSCWPPC */
#endif

#if defined(TrustedApplication_STOP_SEC_VAR_FAST_UNSPECIFIED)
#undef TrustedApplication_STOP_SEC_VAR_FAST_UNSPECIFIED
#undef MEMMAP_ERROR
#if defined(OSCWPPC)
#pragma section sdata_type 
#elif defined(OSDIABPPC)
#pragma section SDATA 
#pragma option -Xsmall-data=0
#elif defined(OSGHSPPC)
#pragma ghs endsda
#pragma ghs section sbss=default
#pragma ghs section sdata=default
#else
#error Unknown compiler
#endif /* OSCWPPC */
#endif

#endif /* defined(__CLASS_SC1) || defined(__CLASS_SC2) */

/* Types generated by OS Sysgen: VAR_*, VAR_FAST_*, CONST_* and CONST_FAST_* */
#include <osmemmap.h>

#ifdef MEMMAP_ERROR                       

#ifdef OSMEMMAP_ERROR                       
#error "MemMap.h, wrong pragma command"
#endif /* OSMEMMAP_ERROR */

#endif /* MEMMAP_ERROR */
