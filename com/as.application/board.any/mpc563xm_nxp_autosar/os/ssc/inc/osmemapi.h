#ifndef OSMEMAPI_H
#define OSMEMAPI_H

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
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/inc/osmemapi.h,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.6 $
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  OS memory protection definitions 
*
* Notes:        
*
******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#if defined(OSAPPLICATION)
#define OSCHECKACCESSRIGHTS( mask, ID, param ) \
    if( ( OSCURRENTAPPMASK & mask) == 0 ) \
    { \
        OSRETERROR( E_OS_ACCESS, ID, param ); \
    }
#else  /* defined(OSAPPLICATION) */
#define OSCHECKACCESSRIGHTS( mask, ID, param )
#endif /* defined(OSAPPLICATION) */

#if defined(OSMEMPROTECTION)

/* Application data section adresses for various compilers (sysgen uses these macros too) */
#if defined(OSCWPPC)
#define OSMP_BEGIN_DSAPPL(DSNAME) _f_##DSNAME
#define OSMP_END_DSAPPL(DSNAME)   _e_##DSNAME
#endif

#if defined(OSGHSPPC)
#define OSMP_BEGIN_DSAPPL(DSNAME) __ghsbegin_##DSNAME##_data
#define OSMP_END_DSAPPL(DSNAME)   __ghsend_##DSNAME##_bss
#endif

#if defined(OSDIABPPC)
#define OSMP_BEGIN_DSAPPL(DSNAME) _f_##DSNAME
#define OSMP_END_DSAPPL(DSNAME)   _e_##DSNAME
#endif

/* Descriptor numbers */
#define OSMPU_RGD_DESC0   0u   /* 0 - <start of osstack - 1>, M0 SM - RWX, M0 UM and other masters without rights */
#define OSMPU_RGD_DESC1   1u   /* osstack area, M0 SM with PID=OS_PID_OSSTK - RW, others without rights */
#define OSMPU_RGD_DESC2   2u   /* <end of osstack> - 0xFFFF_FFFF, M0 SM - RWX, others without rights */
#define OSMPU_RGD_DESC3   3u   /* code and constants area, M0 UM/SM - RX, others without rights */
#define OSMPU_RGD_DESC4   4u   /* nontrusted application data area (MemData0), M0 UM/SM - RW, others without rights */
#define OSMPU_RGD_DESC5   5u   /* runable stack area, M0 UM/SM - RW, others without rights */
#define OSMPU_RGD_DESC6   6u   /* shared OS data (for OsCurApp) (for 5600)*/
#define OSMPU_RGD_DESC7   7u   /* Used for other masters */

#define OSMPU_RGD_DESC8   8u   /* nontrusted application data area (MemData1), M0 UM/SM - RW, others without rights */
#define OSMPU_RGD_DESC9   9u   /* nontrusted application data area (MemData2), M0 UM/SM - RW, others without rights */
#define OSMPU_RGD_DESC10 10u   /* free */
#define OSMPU_RGD_DESC11 11u   /* free */
#define OSMPU_RGD_DESC12 12u   /* free */
#define OSMPU_RGD_DESC13 13u   /* free */
#define OSMPU_RGD_DESC14 14u   /* free */
#define OSMPU_RGD_DESC15 15u   /* free */

#if !defined(OSMPU_RGD_LAST)   /* it may be defined across -DOSMPU_RGD_LAST=OSMPU_RGD_DESC<N> 
                                  (only for internal use by OS testers) */
#if defined(OSMPC5644A) || defined(OSMPC5674F)
#define OSMPU_RGD_LAST OSMPU_RGD_DESC15
#endif
#endif /* !defined(OSMPU_RGD_LAST) */

#define OSMPU_RGD_DESC_DATA_0  OSMPU_RGD_DESC4
#define OSMPU_RGD_DESC_DATA_1  OSMPU_RGD_DESC8
#define OSMPU_RGD_DESC_DATA_2  OSMPU_RGD_DESC9
#define OSMPU_RGD_DESC_STACK   OSMPU_RGD_DESC5
#define OSMPU_RGD_FIRST_UNUSED OSMPU_RGD_DESC6

#if (OSNNOTTRUSTEDAPPS > 0)

#if (OSNMEMDATA0 > 0) 
/* Array of application data section adresses (in ROM) */
extern const OSMP_DSADDR OsMPData[OSNNOTTRUSTEDAPPS];
#endif

#if (OSNMEMDATA1 > 0) 
extern const OSMP_DSADDR OsMPData_1[OSNNOTTRUSTEDAPPS];
#endif

#if (OSNMEMDATA2 > 0) 
extern const OSMP_DSADDR OsMPData_2[OSNNOTTRUSTEDAPPS];
#endif

/*****************************************************************************
 * Function :   OSMP_DATA_DESC
 * Description: Set current application data MPU descriptor (desc N4, 8, 9)  
 * Returns:     none
 *****************************************************************************/
#define OSMP_DATA_DESC()                                                \
    {                                                                   \
        OSMP_DATA_0_DESC();                                             \
        OSMP_DATA_1_DESC();                                             \
        OSMP_DATA_2_DESC();                                             \
    }

/* Copy prepared MPU descriptor fields to HW */
#define _OSMP_DATA_DESC(mpdataram, descnum)                             \
    {                                                                   \
        OSMP_DSADDR *dsram = &(mpdataram)[ OSGetCurApp() ];             \
        /* Writes to either following words clears descriptor's valid bit */ \
        OSMPU_RGD((descnum),OSMPU_RGD_WORD0) = dsram->startaddr;        \
        OSMPU_RGD((descnum),OSMPU_RGD_WORD1) = dsram->endaddr;          \
        /* Restore descriptor's valid bit */                            \
        OSMPU_RGD((descnum),OSMPU_RGD_WORD3) = dsram->valid;            \
    }
    
/* Prepare MPU descriptor fields */
#define _OSMP_PREP_DESC(mpdata, mpdataram, appId)                       \
    {                                                                   \
        OSMP_DSADDR const *ds;                                          \
        OSMP_DSADDR *dsram;                                             \
                                                                        \
        ds = & (mpdata) [appId];                                        \
        dsram = & (mpdataram) [appId];                                  \
                                                                        \
        if( ds->startaddr < ds->endaddr )       /* data section is not empty */ \
        {                                                               \
            dsram->startaddr = ds->startaddr;                           \
            dsram->endaddr = ds->endaddr;                               \
            if( (dsram->endaddr & (OSMPU_GRANULARITY-1) ) == 0 )        /* endaddress is aligned by MPU granularity */ \
            {                                                           \
                dsram->endaddr--;                                       \
            }                                                           \
            dsram->valid = OSMPU_RGD_W3_VLD;                            \
        }                                                               \
        else                                                            \
        {                                                               \
            dsram->valid = 0;                                           \
        }                                                               \
    }

#if (OSNMEMDATA0 > 0)
#define OSMP_DATA_0_DESC() _OSMP_DATA_DESC(OsMPDataRAM,OSMPU_RGD_DESC_DATA_0)
#else /* OSNMEMDATA0 > 0 */
#define OSMP_DATA_0_DESC()
#endif /* OSNMEMDATA0 > 0 */

#if (OSNMEMDATA1 > 0)
#define OSMP_DATA_1_DESC() _OSMP_DATA_DESC(OsMPDataRAM_1,OSMPU_RGD_DESC_DATA_1)
#else /* OSNMEMDATA1 > 0 */
#define OSMP_DATA_1_DESC()
#endif /* OSNMEMDATA1 > 0 */

#if (OSNMEMDATA2 > 0)
#define OSMP_DATA_2_DESC() _OSMP_DATA_DESC(OsMPDataRAM_2,OSMPU_RGD_DESC_DATA_2)
#else /* OSNMEMDATA2 > 0 */
#define OSMP_DATA_2_DESC()
#endif /* OSNMEMDATA2 > 0 */

#else /* (OSNNOTTRUSTEDAPPS > 0) */

#define OSMP_DATA_DESC()

#endif /* (OSNNOTTRUSTEDAPPS > 0) */


/* Set current runable stack MPU descriptor (desc N5) */
#define OSMP_STACK_DESC(stackbos, stacktos)                             \
{                                                                       \
    /* Writes to either of the following words clears descriptor's valid bit */ \
    OSMPU_RGD(OSMPU_RGD_DESC_STACK,OSMPU_RGD_WORD0) = stackbos;         \
    OSMPU_RGD(OSMPU_RGD_DESC_STACK,OSMPU_RGD_WORD1) = stacktos; /* NB! stacktos = cfg->stacktos - OSSTKADDS, */ \
                                                                /*     -> -1 it's not necessary */ \
    /* Restore descriptor's valid bit */                                \
    /* VLD = 1, PID=OS_PID_APPSTK -> descriptor on */                   \
    OSMPU_RGD(OSMPU_RGD_DESC_STACK,OSMPU_RGD_WORD3) = (OS_PID_APPSTK<<24) | OSMPU_RGD_W3_VLD; \
    OSSetPID0(OS_PID_APPSTK);                                           \
}

#if (OSNNOTTRUSTEDAPPS > 1)  /* There is more than one nontrusted OS-application */

/* Prepare MPU for OS-application under OSDHI()  */
#define OSMP_APP_OPEN_DATA_DHI()                                        \
    if( OsLastApp != OSGetCurApp() )                                    \
    {                                                                   \
        OsLastApp = OSGetCurApp();                                      \
        OSDHI();                                                        \
        OSMP_DATA_DESC();   /* Turn on MPU descripror for OS-application data */ \
        OSEHI();                                                        \
    }                                                                   \

/* Prepare MPU for OS-application */
#define OSMP_APP_OPEN_DATA()                                            \
    if( OsLastApp != OSGetCurApp() )                                    \
    {                                                                   \
        OsLastApp = OSGetCurApp();                                      \
        OSMP_DATA_DESC();   /* Turn on MPU descripror for OS-application data */ \
    }                                                                   \

/* Prepare MPU for nontrusted OS-application under OSDHI() */
#define OSMP_NONTRUSTEDAPP_OPEN_DATA_DHI()                              \
    if( OSMP_IS_NONTRUSTEDAPP(OSGetCurApp()) )  /* OS-application is non-trusted */ \
    {                                                                   \
        OSMP_APP_OPEN_DATA_DHI();                                       \
    }

/* Prepare MPU for nontrusted OS-application */
#define OSMP_NONTRUSTEDAPP_OPEN_DATA()                                  \
    if( OSMP_IS_NONTRUSTEDAPP(OSGetCurApp()) )  /* OS-application is non-trusted */ \
    {                                                                   \
        OSMP_APP_OPEN_DATA();                                           \
    }

#else
#define OSMP_APP_OPEN_DATA()
#define OSMP_APP_OPEN_DATA_DHI()
#define OSMP_NONTRUSTEDAPP_OPEN_DATA()
#define OSMP_NONTRUSTEDAPP_OPEN_DATA_DHI()
#endif /* (OSNNOTTRUSTEDAPPS > 1) */

/* Prepare MPU for TASK stack */
#define OSMP_TASK_OPEN_STACK()                                          \
    OSMP_STACK_DESC((OSDWORD)OsRunning->bos, (OSDWORD)OsRunning->tos)

#if !defined(OSNOISR2) 
/* Prepare MPU for ISR2 stack */
#define OSMP_ISR2_OPEN_STACK(isr)                                       \
    OSMP_STACK_DESC((OSDWORD)isr->isrBos, (OSDWORD)isr->stackPtr)
#endif



#if !defined(OSEXCEPTIONSTACKSIZE)
#define OSEXCEPTIONSTACKSIZE 128  /* 128 * 4 bytes */
#endif

extern OSDWORD OsExceptionStack[OSEXCEPTIONSTACKSIZE];


extern void OSInitMemProtection(void);
extern OSWORD OSTerminateApplication(RestartType RestartOption);

#if OSNTRUSTEDFUNCTIONS > 0
extern const OS_TRUSTED_FUNCTION OsTrustedFunctionsTable[];
extern const OSBYTE OsTrustedFunctionsAppId[OSNTRUSTEDFUNCTIONS];
#endif /* OSNTRUSTEDFUNCTIONS > 0 */

extern AccessType OSCheckWriteAccess( MemoryStartAddressType address, MemorySizeType size );
#define OSCHECKWRITEACCESS( address, size, ID, param ) \
    if( !OSCheckWriteAccess( (MemoryStartAddressType)address, size ) ) \
    { \
        OSRETERROR( E_OS_ILLEGAL_ADDRESS, ID, param ); \
    }
#define OSCHECKWRITEACCESS2( address, size, ID, param ) OSCHECKWRITEACCESS( address, size, ID, param )


#if (OSNNOTTRUSTEDAPPS > 0)

extern void OS_OS2SysMode(void);

#define OSCopyMode( arg )

#define OS2UserMode() OSCopyMode(OSMODEUSER); OSSETMSR(OSGETMSR() | OSMSR_PR | OSMSR_ISDS)

#if defined(OSISRENTRYEXIT)
#define OS2UserModeEHI() OSCopyMode(OSMODEUSER); OSMSYNC(); OSSETMSR(OsInitialMSR | OSMSR_PR | OSMSR_ISDS)
#else
/* Switch to user mode with interrupts enabled (set PR & EE bits) */
#define OS2UserModeEHI() OSCopyMode(OSMODEUSER); OSMSYNC(); OSSETMSR(OSGETMSR() | OSMSR_EE | OSMSR_PR | OSMSR_ISDS)
#endif

#else  /* (OSNNOTTRUSTEDAPPS > 0) */

#define OSCopyMode( arg )
#define OS2UserModeEHI( arg )

#endif /* (OSNNOTTRUSTEDAPPS > 0) */

#else  /* OSMEMPROTECTION */

#define OSCHECKWRITEACCESS( address, size, ID, param )
#define OSCHECKWRITEACCESS2( address, size, ID, param )
#define OSCopyMode( arg )
#define OS2UserModeEHI( arg )

#endif /* OSMEMPROTECTION */

/*****************************************************************************
 * inline function: OSGetESR
 * Description:     get the value of Exception syndrome register
 * Returns:         the value of ESR
 *****************************************************************************/
#if defined(OSDIABPPC)
OSASM OSDWORD OSGetESR( void )
{
    mfspr       r3, 62
}
#endif  /* defined(OSDIABPPC) */

#if defined(OSCWPPC)
OSINLINE OSDWORD OSGetESR( void )
{
    register OSDWORD x;

    OSASM { mfspr   x, 62; }
    return x;
}
#endif  /* defined(OSCWPPC) */

#if defined(OSGHSPPC)
#define OSGetESR( ) OSMFSPR( 62 )
#endif

/*****************************************************************************
 * inline function: OSGetMCSR
 * Description:     get the value of Machine Check Sindrom Register 
 * Returns:         the value of MCSR
  ****************************************************************************/
#if defined(OSDIABPPC)
OSASM OSDWORD OSGetMCSR( void )
{
    mfspr       r3, 572
}
#endif  /* defined(OSDIABPPC) */

#if defined(OSCWPPC)
OSINLINE OSDWORD OSGetMCSR( void )
{
    register OSDWORD x;

    OSASM { mfspr   x, 572; }
    return x;
}
#endif  /* defined(OSCWPPC) */

#if defined(OSGHSPPC)
#define OSGetMCSR( ) OSMFSPR( 572 )
#endif


/*****************************************************************************
 * inline function: OSSetMCSR
 * Description:     set Machine Check Sindrom Register 
 * Returns:         none
  ****************************************************************************/
#if defined(OSDIABPPC)
OSASM void OSSetMCSR( OSDWORD mcsr )
{
%reg mcsr
    mtspr  572, mcsr
}
#endif  /* defined(OSDIABPPC) */

#if defined(OSCWPPC)
OSINLINE void OSSetMCSR( register OSDWORD _mcsr )
{
    OSASM { mtspr  572, _mcsr; }
}
#endif  /* defined(OSCWPPC) */

#if defined(OSGHSPPC)
#define OSSetMCSR( mcsr ) OSMTSPR( 572, mcsr )
#endif

#if defined(OSMEMPROTECTION)

/* OS services prototypes */
#if OSNTRUSTEDFUNCTIONS > 0
extern StatusType OS_CallTrustedFunction( TrustedFunctionIndexType ix, TrustedFunctionParameterRefType ptr );
#endif
#if !defined(OSNOISR2)
extern AccessType OS_CheckISRMemoryAccess( ISRType isrId, MemoryStartAddressType address, MemorySizeType size );
#endif
extern AccessType OS_CheckTaskMemoryAccess( TaskType isrId, MemoryStartAddressType address, MemorySizeType size );
extern ObjectAccessType OS_CheckObjectAccess( ApplicationType appId, ObjectTypeType objectType, OSObjectType objectId );
extern ApplicationType OS_CheckObjectOwnership( ObjectTypeType objectType, OSObjectType objectId );
extern ApplicationType OS_GetApplicationID( void );
extern StatusType OS_TerminateApplication( RestartType RestartOption );

/*****************************************************************************
 * Function:    
 * Description: wrappers for OS services
 * Returns:     return values of given OS services
 *****************************************************************************/
#if OSNTRUSTEDFUNCTIONS > 0
OSINLINE StatusType CallTrustedFunction( TrustedFunctionIndexType ix, TrustedFunctionParameterRefType ptr )
{
    return OSServiceCall2( StatusType, ix, ptr, CallTrustedFunction );
}
#endif

#if !defined(OSNOISR2)
OSINLINE AccessType CheckISRMemoryAccess( ISRType isrId, MemoryStartAddressType address, MemorySizeType size )
{
    return OSServiceCall3( AccessType, isrId, address, size, CheckISRMemoryAccess );
}
#endif

OSINLINE AccessType CheckTaskMemoryAccess( TaskType taskId, MemoryStartAddressType address, MemorySizeType size )
{
    return OSServiceCall3( AccessType, taskId, address, size, CheckTaskMemoryAccess );
}

OSINLINE ObjectAccessType CheckObjectAccess( ApplicationType appId, ObjectTypeType objectType, OSObjectType objectId )
{
    return OSServiceCall3( ObjectAccessType, appId, objectType, objectId, CheckObjectAccess );
}

OSINLINE  ApplicationType CheckObjectOwnership( ObjectTypeType objectType, OSObjectType objectId )
{
    return OSServiceCall2( ApplicationType, objectType, objectId, CheckObjectOwnership );
}

OSINLINE ApplicationType GetApplicationID( void )
{
    return OSServiceCall0( ApplicationType, GetApplicationID );
}

OSINLINE StatusType TerminateApplication( RestartType RestartOption ) 
{
    return OSServiceCall1( StatusType, RestartOption, TerminateApplication );
}

#endif /* defined(OSMEMPROTECTION) */

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* OSMEMAPI_H */
