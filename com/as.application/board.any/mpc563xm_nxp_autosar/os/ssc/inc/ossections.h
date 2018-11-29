/******************************************************************************
*
*    Freescale(TM) and the Freescale logo are trademarks of Freescale Semiconductor, Inc. 
*    All other product or service names are the property of their respective owners. 
*    (C) Freescale Semiconductor, Inc. 2006-2010
*
*    THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
*    BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
*    Freescale Semiconductor, Inc.
*
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/inc/ossections.h,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  OS internal memory mapping 
*
* Usage notes: there is some differences in usage of *_VAR_FAST_* 
*              types for different compilers. DIAB behavior is very
*              different from CW/GHS compilers.
*              -  For DIAB and CW it is possible declare FAST data implicitly
*                 using once declaration in os.h:
*                 #define OS_START_ONCE_SEC_VAR_FAST_UNSPECIFIED
*                 #include "ossections.h"
*                 DIAB and CW will put data with size < 'small data threshold'
*                 to small data section .ossbss, others to .osbss.
*                 CW will put there also data with OSNEAR (__declspec(.ossbss)) attribute.
*              -  For GHS it is necessary to use explicit declaration
*                 #define OS_START_SEC_VAR_FAST_UNSPECIFIED
*                 #include "ossections.h"
*                 before each OSNEAR data declaration.
******************************************************************************/

#define OSMEMMAP_ERROR

#if defined(OSTEXT_START_SEC_CODE)

#undef OSTEXT_START_SEC_CODE
#undef OSMEMMAP_ERROR

#if defined(OSCWPPC)
#pragma section code_type ".ostext"
#elif defined(OSDIABPPC)
#pragma section CODE ".ostext"
#elif defined(OSGHSPPC)
#pragma ghs section text=".ostext"
#else
#error Unknown compiler
#endif /* OSCWPPC */

#elif defined(OSTEXT_STOP_SEC_CODE)
#undef OSTEXT_STOP_SEC_CODE
#undef OSMEMMAP_ERROR

#if defined(OSCWPPC)
#pragma section code_type
#elif defined(OSDIABPPC)
#pragma section CODE
#elif defined(OSGHSPPC)
#pragma ghs section text=default
#else
#error Unknown compiler
#endif /* OSCWPPC */

#elif defined(OSVECTORS_START_SEC_CODE)
#undef OSVECTORS_START_SEC_CODE
#undef OSMEMMAP_ERROR

#if defined(OSCWPPC)
#pragma section code_type ".vects"
#elif defined(OSDIABPPC)
#pragma section CODE ".vects"
#elif defined(OSGHSPPC)
    OSASM("   .section  \".vects\", \"vax\"   ");
    OSASM("   .vle ");
#else
#error Unknown compiler
#endif /* OSCWPPC */

#elif defined(OSVECTORS_STOP_SEC_CODE)
#undef OSVECTORS_STOP_SEC_CODE
#undef OSMEMMAP_ERROR

#if defined(OSCWPPC)
#pragma section code_type
#elif defined(OSDIABPPC)
#pragma section CODE
#elif defined(OSGHSPPC)
    OSASM("   .section  \".vletext\", \"vax\"   ");
    OSASM("   .vle ");
#else
#error Unknown compiler
#endif /* OSCWPPC */

#elif defined(OSVECTORS2_START_SEC_CODE)
#undef OSVECTORS2_START_SEC_CODE
#undef OSMEMMAP_ERROR

#if defined(OSCWPPC)
#pragma section code_type ".vects2"
#elif defined(OSDIABPPC)
#pragma section CODE ".vects2"
#elif defined(OSGHSPPC)
    OSASM("   .section  \".vects2\", \"vax\"   ");
    OSASM("   .vle ");
#else
#error Unknown compiler
#endif /* OSCWPPC */

#elif defined(OSVECTORS2_STOP_SEC_CODE)
#undef OSVECTORS2_STOP_SEC_CODE
#undef OSMEMMAP_ERROR

#if defined(OSCWPPC)
#pragma section code_type
#elif defined(OSDIABPPC)
#pragma section CODE
#elif defined(OSGHSPPC)
    OSASM("   .section  \".vletext\", \"vax\"   ");
    OSASM("   .vle ");
#else
#error Unknown compiler
#endif /* OSCWPPC */

#elif defined(OSHOOK_START_SEC_CODE)
#undef OSHOOK_START_SEC_CODE
#undef OSMEMMAP_ERROR

#if defined(OSCWPPC)
#pragma section code_type ".oshook"
#elif defined(OSDIABPPC)
#pragma section CODE ".oshook"
#elif defined(OSGHSPPC)
#pragma ghs section text=".oshook"
#else
#error Unknown compiler
#endif /* OSCWPPC */

#elif defined(OSHOOK_STOP_SEC_CODE)
#undef OSHOOK_STOP_SEC_CODE
#undef OSMEMMAP_ERROR

#if defined(OSCWPPC)
#pragma section code_type
#elif defined(OSDIABPPC)
#pragma section CODE
#elif defined(OSGHSPPC)
#pragma ghs section text=default
#else
#error Unknown compiler
#endif /* OSCWPPC */

#elif defined(OS_START_SEC_VAR_UNSPECIFIED)
#undef OS_START_SEC_VAR_UNSPECIFIED
#undef OSMEMMAP_ERROR

#if defined(OSCWPPC)
#pragma section data_type ".osdata" ".osbss"
#elif defined(OSDIABPPC)
#pragma section DATA ".osdata" ".osbss"
#elif defined(OSGHSPPC)
#pragma ghs section bss=".osbss"
#else
#error Unknown compiler
#endif /* OSCWPPC */

#elif defined(OS_STOP_SEC_VAR_UNSPECIFIED)
#undef OS_STOP_SEC_VAR_UNSPECIFIED
#undef OSMEMMAP_ERROR

#if defined(OSCWPPC)
#pragma section data_type
#elif defined(OSDIABPPC)
#pragma section DATA
#elif defined(OSGHSPPC)
#pragma ghs section bss=default
#else
#error Unknown compiler
#endif /* OSCWPPC */

#elif defined(OS_START_SEC_VAR_FAST_UNSPECIFIED)
#undef OS_START_SEC_VAR_FAST_UNSPECIFIED
#undef OSMEMMAP_ERROR

#if defined(OSCWPPC)
/* see OS_START_ONCE_SEC_VAR_FAST_UNSPECIFIED */
#elif defined(OSGHSPPC)
#pragma ghs section sbss=".ossbss"
#pragma ghs startsda
#elif defined(OSDIABPPC)
/* see OS_START_ONCE_SEC_VAR_FAST_UNSPECIFIED */
#else
#error Unknown compiler
#endif /* OSCWPPC */

#elif defined(OS_STOP_SEC_VAR_FAST_UNSPECIFIED)
#undef OS_STOP_SEC_VAR_FAST_UNSPECIFIED
#undef OSMEMMAP_ERROR

#if defined(OSCWPPC)
/* see OS_STOP_ONCE_SEC_VAR_FAST_UNSPECIFIED */
#elif defined(OSDIABPPC)
/* see OS_STOP_ONCE_SEC_VAR_FAST_UNSPECIFIED */
#elif defined(OSGHSPPC)
#pragma ghs endsda
#pragma ghs section sbss=default
#else
#error Unknown compiler
#endif /* OSCWPPC */

#elif defined(OS_START_ONCE_SEC_VAR_FAST_UNSPECIFIED)
#undef OS_START_ONCE_SEC_VAR_FAST_UNSPECIFIED
#undef OSMEMMAP_ERROR

#if defined(OSCWPPC)
#pragma section sdata_type ".ossdata" ".ossbss"
/* Note: it is necessary also use __declspec(section ".ossdata") before each data declaration (see OSNEAR macro) */
#elif defined(OSGHSPPC)
/* see OS_START_SEC_VAR_FAST_UNSPECIFIED */
#elif defined(OSDIABPPC)
#if defined(OSMEMPROTECTION)
#pragma option -Xsmall-data=8
#endif
#pragma section SDATA ".ossdata" ".ossbss"
#else
#error Unknown compiler
#endif /* OSCWPPC */

#elif defined(OS_STOP_ONCE_SEC_VAR_FAST_UNSPECIFIED)
#undef OS_STOP_ONCE_SEC_VAR_FAST_UNSPECIFIED
#undef OSMEMMAP_ERROR

#if defined(OSCWPPC)
#pragma section sdata_type
#elif defined(OSDIABPPC)
#pragma section SDATA
#if defined(OSMEMPROTECTION)
#pragma option -Xsmall-data=0
#endif
#elif defined(OSGHSPPC)
/* see OS_STOP_SEC_VAR_FAST_UNSPECIFIED */
#else
#error Unknown compiler
#endif /* OSCWPPC */

#elif defined(OS_START_SEC_VAR_SHARED)  /* it is intended only for  SC3/4 */

#if defined(OSMEMPROTECTION)

#undef OS_START_SEC_VAR_SHARED
#undef OSMEMMAP_ERROR

#if defined(OSCWPPC)
#pragma section data_type ".osdatashared" ".osbssshared"
#elif defined(OSGHSPPC)
#pragma ghs section bss=".osbssshared"
#elif defined(OSDIABPPC)
#pragma option -Xsmall-data=0
#pragma section DATA ".osdatashared" ".osbssshared"
#else
#error Unknown compiler
#endif /* OSCWPPC */

#endif /* OSMEMPROTECTION */

#elif defined(OS_STOP_SEC_VAR_SHARED)

#if defined(OSMEMPROTECTION)

#undef OS_STOP_SEC_VAR_SHARED
#undef OSMEMMAP_ERROR

#if defined(OSCWPPC)
#pragma section data_type
#elif defined(OSDIABPPC)
#pragma section DATA
#pragma option -Xsmall-data=8
#elif defined(OSGHSPPC)
#pragma ghs section bss=default
#else
#error Unknown compiler
#endif /* OSCWPPC */

#endif /* OSMEMPROTECTION */

#elif defined(OSSTACK_START_SEC_VAR_UNSPECIFIED)
#undef OSSTACK_START_SEC_VAR_UNSPECIFIED
#undef OSMEMMAP_ERROR

#if defined(OSCWPPC)
#pragma section data_type ".osstack" ".osstack"
#elif defined(OSDIABPPC)
#pragma section DATA ".osstack" ".osstack"
#elif defined(OSGHSPPC)
#pragma ghs section bss=".osstack"
#else
#error Unknown compiler
#endif /* OSCWPPC */

#elif defined(OSSTACK_STOP_SEC_VAR_UNSPECIFIED)
#undef OSSTACK_STOP_SEC_VAR_UNSPECIFIED
#undef OSMEMMAP_ERROR

#if defined(OSCWPPC)
#pragma section data_type
#elif defined(OSDIABPPC)
#pragma section DATA
#elif defined(OSGHSPPC)
#pragma ghs section bss=default
#else
#error Unknown compiler
#endif /* OSCWPPC */

#elif defined(OS_START_SEC_CONST_UNSPECIFIED)

#undef OS_START_SEC_CONST_UNSPECIFIED
#undef OSMEMMAP_ERROR

#if defined(OSCWPPC)
#pragma section const_type ".osrodata" ".osrodata"
#elif defined(OSDIABPPC)
#pragma section CONST ".osrodata" ".osrodata"
#pragma option -Xsmall-const=0
#elif defined(OSGHSPPC)
#pragma ghs section rodata=".osrodata"
#else
#error Unknown compiler
#endif /* OSCWPPC */

#elif defined(OS_STOP_SEC_CONST_UNSPECIFIED)
#undef OS_STOP_SEC_CONST_UNSPECIFIED
#undef OSMEMMAP_ERROR

#if defined(OSCWPPC)
#pragma section const_type
#elif defined(OSDIABPPC)
#pragma option -Xsmall-const=8          /* restore to default threshold */
#pragma section CONST
#elif defined(OSGHSPPC)
#pragma ghs section const=default
#else
#error Unknown compiler
#endif /* OSCWPPC */

#elif defined(OS_START_SEC_CONST_FAST_UNSPECIFIED)   
#undef OS_START_SEC_CONST_FAST_UNSPECIFIED
#undef OSMEMMAP_ERROR

#if defined(OSCWPPC)
#pragma section const_type ".ossrodata" ".ossrodata"
/* Note: it is necessary also use __declspec(".ossrodata") before 'const' in constant declarations */
#elif defined(OSDIABPPC)
#if defined(OSMEMPROTECTION)
#pragma option -Xsmall-const=8
#endif
#pragma section CONST ".ossrodata" ".ossrodata"
#elif defined(OSGHSPPC)
#pragma ghs section const=".ossrodata"
#else
#error Unknown compiler
#endif /* OSCWPPC */

#elif defined(OS_STOP_SEC_CONST_FAST_UNSPECIFIED)
#undef OS_STOP_SEC_CONST_FAST_UNSPECIFIED
#undef OSMEMMAP_ERROR

#if defined(OSCWPPC)
#pragma section const_type
#elif defined(OSDIABPPC)
#if defined(OSMEMPROTECTION)
#pragma option -Xsmall-const=0
#endif
#pragma section CONST
#elif defined(OSGHSPPC)
#pragma ghs section const=default
#else
#error Unknown compiler
#endif /* OSCWPPC */

#elif defined(APP_START_SEC_CODE)
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

#endif
