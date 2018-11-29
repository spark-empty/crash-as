#define OSMEM_C
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
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/src/osmem.c,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* Functions:    
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  Autosar memory protection           
*
* Notes:        
*
******************************************************************************/

#define OS_INTERNAL 1
#include    <os.h>
#undef OS_INTERNAL

#define OSTEXT_START_SEC_CODE
#include "ossections.h"
#define OS_START_SEC_VAR_UNSPECIFIED
#include "ossections.h"
#define OS_START_ONCE_SEC_VAR_FAST_UNSPECIFIED
#include "ossections.h"
#define OS_START_SEC_CONST_UNSPECIFIED
#include "ossections.h"

/**** linker defined symbols for ProtectionHandler ****/
extern char OS_BEGIN_DSADDR(ostext)[]; /* beginning of OS code section */
extern char OS_END_DSADDR(ostext)[]; /* end of OS code section */

/* local functions prototypes */
#if defined(OSMEMPROTECTION)
AccessType OSAppMemAccess( ApplicationType appId, OSDWORD start, OSDWORD end, OSDWORD bos, OSDWORD tos );

void OSTLBException( OSDWORD srr0, OSDWORD srr1 );
#endif
void OSProtectionHandler( StatusType ecode );
void OSExceptionError( OSDWORD srr0, OSDWORD srr1 );  /* for MISRA */

#if defined(OSMEMPROTECTION)

OSDWORD OsExceptionStack[OSEXCEPTIONSTACKSIZE];


extern char OS_BEGIN_DSADDR(osbegincode)[]; /* beginning of common code section */
extern char OS_END_DSADDR(osendcode)[];   /* end of common code section */


#define OSMPU_GRANULARITY       0x20ul  /* MPU granularity */

/**** linker defined symbols for ProtectionHandler ****/
extern char OS_BEGIN_DSADDR(osstack)[]; /* beginning of OS stack section */
extern char OS_END_DSADDR(osstack)[]; /* end of of OS stack section */

/* MPU region descriptor structure */
typedef struct {
    OSDWORD word0;
    OSDWORD word1;
    OSDWORD word2;
    OSDWORD word3;
    OSBYTE id;       
} OsMPU_RGD;

/* Constant MPU region descriptors */
const OsMPU_RGD OsMPU_ConstRGD[] = 
{
    /* Descriptor 0: 0 - <start of osstack - 1>, 
       M0 SM: "RWX", M0 UM: "---" , M4: "---", other masters depend on OSMPU_RGD_W2_M123() */
    {
        0ul, 
        (OSDWORD) OS_BEGIN_DSADDR( osstack ), 
        OSMPU_RGD_W2_M0( OSMPU_PE_OFF, OSMPU_SM_RWX, 0 ) | OSMPU_RGD_W2_M123(),
        OSMPU_RGD_W3_VLD, 
        OSMPU_RGD_DESC0
    },

    /* Descriptor 1: <start of osstack> - <end of osstack - 1>,
       M0 SU with PID=OS_PID_SUPERVISOR: "RW-", M0 with other PIDs and M0 UM: "---", M4: "---",other masters depend on OSMPU_RGD_W2_M123() */
    { 
        (OSDWORD) OS_BEGIN_DSADDR( osstack ),
        (OSDWORD) OS_END_DSADDR( osstack ),
        OSMPU_RGD_W2_M0( OSMPU_PE_ON, OSMPU_SM_RW, 0 ) | OSMPU_RGD_W2_M123(),
        ( OSMPU_RGD_W3_VLD | (OS_PID_OSSTK<<24) ),
        OSMPU_RGD_DESC1
    },

    /* Descriptor 2: <end of osstack> - (0x100000000-1), 
       M0 SM: "RWX", M0 UM and M4: "---", other masters depend on OSMPU_RGD_W2_M123() */
    { 
        (OSDWORD) OS_END_DSADDR( osstack ),
        0ul, /* Note: 0lu - 1lu = 0xfffffffflu */
        OSMPU_RGD_W2_M0( OSMPU_PE_OFF , OSMPU_SM_RWX, 0 ) | OSMPU_RGD_W2_M123(),
        OSMPU_RGD_W3_VLD,
        OSMPU_RGD_DESC2
    },
        
    /* Descriptor 3: <start of .text> - <end of .osrodata - 1>, 
       M0 UM/SM: "RWX", M4: "---", other masters depend on OSMPU_RGD_W2_M123() */
    { 
        (OSDWORD) OS_BEGIN_DSADDR( osbegincode ),
        (OSDWORD) OS_END_DSADDR( osendcode ),
        OSMPU_RGD_W2_M0( OSMPU_PE_OFF, 0, OSMPU_UM_R | OSMPU_UM_X ) | OSMPU_RGD_W2_M123(),
        OSMPU_RGD_W3_VLD,
        OSMPU_RGD_DESC3
    },

};

/* Memory region rights structure */
typedef struct {
    OSDWORD start;
    OSDWORD end;
    AccessType rights;       
} OSMEMRGN;

const OSMEMRGN OsMemRgn[] = 
{
#ifdef OSINTRAMSIZE
    {
        (OSDWORD)(OSINTRAMADDR),
        (OSDWORD)(OSINTRAMADDR + OSINTRAMSIZE - 1),
        (AccessType)(OSMP_S | OSMP_E | OSMP_R | OSMP_W)
    },
#endif
#ifdef OSEXTRAMSIZE
    {
        (OSDWORD)(OSEXTRAMADDR),
        (OSDWORD)(OSEXTRAMADDR + OSEXTRAMSIZE - 1),
        (AccessType)(OSMP_S | OSMP_E | OSMP_R | OSMP_W)
    },
#endif
#ifdef OSINTROMSIZE
    {
        (OSDWORD)(OSINTROMADDR),
        (OSDWORD)(OSINTROMADDR + OSINTROMSIZE - 1),
        (AccessType)(OSMP_E | OSMP_R | OSMP_W)
    },
#endif
#ifdef OSEXTROMSIZE
    {
        (OSDWORD)(OSEXTROMADDR),
        (OSDWORD)(OSEXTROMADDR + OSEXTROMSIZE - 1),
        (AccessType)(OSMP_E | OSMP_R | OSMP_W)
    },
#endif
#ifdef OSBRIDGE1SIZE
    {
        (OSDWORD)(OSBRIDGE1ADDR),
        (OSDWORD)(OSBRIDGE1ADDR + OSBRIDGE1SIZE - 1),
        (AccessType)(OSMP_R | OSMP_W)
    },
#endif
#ifdef OSBRIDGE2SIZE
    {
        (OSDWORD)(OSBRIDGE2ADDR),
        (OSDWORD)(OSBRIDGE2ADDR + OSBRIDGE2SIZE - 1),
        (AccessType)(OSMP_R | OSMP_W)
    },
#endif
#ifdef OSBRIDGE3SIZE
    {
        (OSDWORD)(OSBRIDGE3ADDR),
        (OSDWORD)(OSBRIDGE3ADDR + OSBRIDGE3SIZE - 1),
        (AccessType)(OSMP_R | OSMP_W)
    },
#endif
#ifdef OSBRIDGE4SIZE
    {
        (OSDWORD)(OSBRIDGE4ADDR),
        (OSDWORD)(OSBRIDGE4ADDR + OSBRIDGE4SIZE - 1),
        (AccessType)(OSMP_R | OSMP_W)
    },
#endif
#ifdef OSBRIDGE5SIZE
    {
        (OSDWORD)(OSBRIDGE5ADDR),
        (OSDWORD)(OSBRIDGE5ADDR + OSBRIDGE5SIZE - 1),
        (AccessType)(OSMP_R | OSMP_W)
    }
#endif
};

/*****************************************************************************
 * Function    : OSInitMemProtection
 *
 * Description : protects ALL memory against writing in user mode 
 *
 * Returns     : none
 *
 * Notes       : none
 *****************************************************************************/

void OSInitMemProtection( void )
{
    OSBYTE i;

    /* Put off MPU */
    OSMPU_CESR = 0; 

    /* Set constant MPU region descriptors. */
    for( i = 0; i < sizeof(OsMPU_ConstRGD)/sizeof(OsMPU_ConstRGD[0]); i++ )
    {
        OSDWORD word1;

        OSMPU_RGD(OsMPU_ConstRGD[i].id,OSMPU_RGD_WORD0) = OsMPU_ConstRGD[i].word0;
        word1 = OsMPU_ConstRGD[i].word1;
        if( (word1 & (OSMPU_GRANULARITY-1)) == 0 )      /* endaddress is aligned by MPU granularity */
        {
            word1--;
        }
        OSMPU_RGD(OsMPU_ConstRGD[i].id,OSMPU_RGD_WORD1) = word1;
        OSMPU_RGD(OsMPU_ConstRGD[i].id,OSMPU_RGD_WORD2) = OsMPU_ConstRGD[i].word2;
        OSMPU_RGD(OsMPU_ConstRGD[i].id,OSMPU_RGD_WORD3) = OsMPU_ConstRGD[i].word3;
    }
    
    /* Put off other descriptors */
    for( i = OSMPU_RGD_FIRST_UNUSED; i <= OSMPU_RGD_LAST; i++ )
    {
        OSMPU_RGD(i,OSMPU_RGD_WORD3) = 0;
    }    
    /* Set constant part of dynamic MPU region descriptors:
       - for nontrusted application data, UM/SM - RW 
       - for stack of runable, UM/SM - RW */
#if (OSNMEMDATA0 > 0) 
    OSMPU_RGD(OSMPU_RGD_DESC_DATA_0,OSMPU_RGD_WORD2)  = 
        (OSDWORD) OSMPU_RGD_W2_M0( OSMPU_PE_OFF, 0, OSMPU_UM_R | OSMPU_UM_W ) | OSMPU_RGD_W2_M123();
#endif
#if (OSNMEMDATA1 > 0) 
    OSMPU_RGD(OSMPU_RGD_DESC_DATA_1,OSMPU_RGD_WORD2)  = 
        (OSDWORD) OSMPU_RGD_W2_M0( OSMPU_PE_OFF, 0, OSMPU_UM_R | OSMPU_UM_W ) | OSMPU_RGD_W2_M123();
#endif
#if (OSNMEMDATA2 > 0) 
    OSMPU_RGD(OSMPU_RGD_DESC_DATA_2,OSMPU_RGD_WORD2)  = 
        (OSDWORD) OSMPU_RGD_W2_M0( OSMPU_PE_OFF, 0, OSMPU_UM_R | OSMPU_UM_W ) | OSMPU_RGD_W2_M123();
#endif
    
    OSMPU_RGD(OSMPU_RGD_DESC_STACK,OSMPU_RGD_WORD2) = 
        (OSDWORD) OSMPU_RGD_W2_M0( OSMPU_PE_ON, 0, OSMPU_UM_R | OSMPU_UM_W ) | OSMPU_RGD_W2_M123();


#if (OSNNOTTRUSTEDAPPS > 0)    
    /* Array of application data section adresses (in RAM) */
    for( i = 0; i < OSNNOTTRUSTEDAPPS; i++ )
    {
#if (OSNMEMDATA0 > 0)
        _OSMP_PREP_DESC(OsMPData, OsMPDataRAM, i);
#endif /* (OSNMEMDATA0 > 0) */      
#if (OSNMEMDATA1 > 0)
        _OSMP_PREP_DESC(OsMPData_1, OsMPDataRAM_1, i);
#endif /* (OSNMEMDATA1 > 0) */      
#if (OSNMEMDATA2 > 0)
        _OSMP_PREP_DESC(OsMPData_2, OsMPDataRAM_2, i);
#endif /* (OSNMEMDATA2 > 0) */      
    }

#if  (OSNNOTTRUSTEDAPPS > 1 ) 
    OSSetCurApp(INVALID_OSAPPLICATION);
    OsLastApp = INVALID_OSAPPLICATION;
#endif

#if (OSNNOTTRUSTEDAPPS == 1)
    OSSetCurApp(0);
    OSMP_DATA_DESC();    
#endif

#endif /* (OSNNOTTRUSTEDAPPS > 0) */    

    OSSetPID0(OS_PID_OSSTK);                   /* RW rigths for all osstack area */

    OSMPU_CESR = OSMPU_CESR_VLD;               /* put on MPU */
}


/*****************************************************************************
 * Function    : OSAppMemAccess
 *
 * Description : Determinate access type to memory area for application
 *
 * Returns     : AccessType
 *
 * Notes       : none
 *****************************************************************************/
AccessType OSAppMemAccess( ApplicationType appId,
                           OSDWORD start, OSDWORD end,
                           OSDWORD bos, OSDWORD tos )
{
    OSBYTE i;

    if( ( start >= bos ) && ( end < tos ) )
    {   /* given ISR or Task stack */        
        return( OSMP_S | OSMP_R | OSMP_W );
    }
#if (OSNNOTTRUSTEDAPPS > 0)
    if( OSMP_IS_NONTRUSTEDAPP( appId ) )
    {   /* Nontrusted application */
#if (OSNMEMDATA0 > 0) 
        if( ( start >= OsMPData[appId].startaddr ) &&
            ( end   <  OsMPData[appId].endaddr ) )
        {   /* given ISR or Task application data */
            return( OSMP_R | OSMP_W );
        }
#endif
#if (OSNMEMDATA1 > 0) 
        if( ( start >= OsMPData_1[appId].startaddr ) &&
            ( end   <  OsMPData_1[appId].endaddr ) )
        {   /* given ISR or Task application data */
            return( OSMP_R | OSMP_W );
        }
#endif
#if (OSNMEMDATA2 > 0) 
        if( ( start >= OsMPData_2[appId].startaddr ) &&
            ( end   <  OsMPData_2[appId].endaddr ) )
        {   /* given ISR or Task application data */
            return( OSMP_R | OSMP_W );
        }
#endif
        if( ( start >= (OSDWORD)OS_BEGIN_DSADDR(osbegincode) ) &&
            ( end   <  (OSDWORD)OS_END_DSADDR(osendcode) ) )
        {  /* code */
           return( OSMP_R | OSMP_E );
        }
    }
    else
#endif /* (OSNNOTTRUSTEDAPPS > 0) */
    {   /* Trusted application */
        if( ( start >= (OSDWORD)OS_BEGIN_DSADDR( osstack ) ) &&
            ( end   <  (OSDWORD)OS_END_DSADDR( osstack ) ) )
        {   /* another tasks and ISRs stacks */
            return( 0 ); /* no access */
        }
        for( i = 0; i < (sizeof(OsMemRgn)/sizeof(OSMEMRGN)); i++ )
        {
            if( (start >= OsMemRgn[i].start) && (end <= OsMemRgn[i].end) )
            {
                return( OsMemRgn[i].rights );
            }
        }
    }
    return( 0 ); /* no access */
}

/******************************************************************************
 * Function :   OSCheckWriteAccess
 *
 * Description: Checks the OS-Application write access to the data area.
 *
 * Returns:     OSTRUE - if write access is permitted (area is stack or application data),
 *              otherwise - OSFALSE.
 *            
 *****************************************************************************/
AccessType OSCheckWriteAccess( MemoryStartAddressType address, MemorySizeType size )
{
    register OSDWORD endAddr = (OSDWORD)address + size;
    OSDWORD bos, tos;
#if (OSNUSERISR > 0)
    OS_ISRTYPE* isrPtr; /* pointer to ISR descriptor */
#endif

#if defined(OSHOOKERROR) || defined(OSHOOKPROTECTION) || \
    defined(OSHOOKPRETASK) || defined(OSHOOKPOSTTASK)
    if( OsIsrLevel & ( OSISRLEVELHOOKERROR | OSISRLEVELHOOKPROTECTION |
                       OSISRLEVELHOOKTASK ) )
    {   /* hook */
#if defined(OSINTRAMSIZE)
        if( ( (OSDWORD)address >= OSINTRAMADDR ) &&
            ( endAddr <= ( OSINTRAMADDR + OSINTRAMSIZE ) ) )
        {   /* begin of internal RAM <= address, endAddr <= end of internal RAM */
            return OSTRUE;
        }
#endif
#if defined(OSEXTRAMSIZE)
        if( ( (OSDWORD)address >= OSEXTRAMADDR ) &&
            ( endAddr <= ( OSEXTRAMADDR + OSEXTRAMSIZE ) ) )
        {   /* begin of external RAM <= address, endAddr <= end of external RAM */
            return OSTRUE;
        }
#endif
        return OSFALSE;
    }
#endif /* defined(OSHOOKERROR) || defined(OSHOOKPROTECTION) || \
          defined(OSHOOKPRETASK) || defined(OSHOOKPOSTTASK) */

#if (OSNUSERISR > 0)
    if(OSISRLEVELMASKED != 0)
    {
        isrPtr = OsIsrArray[OSISRLEVELMASKED -1];
        bos = (OSDWORD)(isrPtr->isrBos);
        tos = (OSDWORD)(isrPtr->stackPtr);
    }
    else
    {
#endif
        bos = (OSDWORD)(OsRunning->bos);
        tos = (OSDWORD)(OsRunning->tos);
#if (OSNUSERISR > 0)
    }
#endif
    if( ( (OSDWORD)address >= bos ) && ( endAddr < tos ) )
    {   /* current runnable task, ISR, hook stack */
        return OSTRUE;
    }

#if (OSNNOTTRUSTEDAPPS > 0)
    if( OSMP_IS_TRUSTEDAPP( OSGetCurApp( ) ) )
    {   /* trusted application */
#endif
        if( ( (OSDWORD)address >= (OSDWORD)OS_BEGIN_DSADDR( osstack ) ) &&
            ( endAddr < (OSDWORD)OS_END_DSADDR( osstack ) ) )
        {   /* another tasks and ISRs stacks */
            return OSFALSE;
        }
#if defined(OSINTRAMSIZE)
        if( ( (OSDWORD)address >= OSINTRAMADDR ) &&
            ( endAddr <= ( OSINTRAMADDR + OSINTRAMSIZE ) ) )
        {   /* begin of internal RAM <= address, endAddr <= end of internal RAM */
            if( endAddr < (OSDWORD)OS_BEGIN_DSADDR( osstack ) )
            {   /* begin of internal RAM <= address, endAddr < begin of osstack */
                return OSTRUE;
            }
            if( (OSDWORD)address >= (OSDWORD)OS_END_DSADDR( osstack ) )
            {   /* end of osstack < address, endAddr <= end of internal RAM */
                return OSTRUE;
            }
        }
#endif
#if defined(OSEXTRAMSIZE)
        if( ( (OSDWORD)address >= OSEXTRAMADDR ) &&
            ( endAddr <= ( OSEXTRAMADDR + OSEXTRAMSIZE ) ) )
        {   /* begin of external RAM <= address, endAddr <= end of external RAM */
            if( endAddr < (OSDWORD)OS_BEGIN_DSADDR( osstack ) )
            {   /* begin of external RAM <= address, endAddr < begin of osstack */
                return OSTRUE; 
            }
            if( (OSDWORD)address >= (OSDWORD)OS_END_DSADDR( osstack ) )
            {   /* end of osstack < address, endAddr <= end of external RAM */
                return OSTRUE;
            }
        }
#endif
        return OSFALSE;
#if (OSNNOTTRUSTEDAPPS > 0)
    }
    else
    {   /* nontrusted application */
#if (OSNMEMDATA0 > 0) 
        if( ( (OSDWORD)address >= OsMPData[OSGetCurApp( )].startaddr ) &&
            (          endAddr <= OsMPData[OSGetCurApp( )].endaddr ) )
        {   /* current nontrusted application stack */
            return OSTRUE;
        }
#endif
#if (OSNMEMDATA1 > 0) 
        if( ( (OSDWORD)address >= OsMPData_1[OSGetCurApp( )].startaddr ) &&
            (          endAddr <= OsMPData_1[OSGetCurApp( )].endaddr ) )
        {   /* current nontrusted application stack */
            return OSTRUE;
        }
#endif
#if (OSNMEMDATA2 > 0) 
        if( ( (OSDWORD)address >= OsMPData_2[OSGetCurApp( )].startaddr ) &&
            (          endAddr <= OsMPData_2[OSGetCurApp( )].endaddr ) )
        {   /* current nontrusted application stack */
            return OSTRUE;
        }
#endif

        return OSFALSE;
    }
#endif /* (OSNNOTTRUSTEDAPPS > 0) */
}

#if !defined(OSNOISR2)
/*****************************************************************************
 * Function :   OS_CheckISRMemoryAccess
 *
 * Description: checks whether or not the private memory section of the ISR
 *              is within the memory section 
 *
 * Returns:     Set of access rights for the specified region of memory.
 *              0 - for no access.    
 *            
 ******************************************************************************/
AccessType OS_CheckISRMemoryAccess( ISRType isrId,
                                    MemoryStartAddressType address,
                                    MemorySizeType size )
{
    const OS_ISRTYPE* isr;
    AccessType access;

    OSOrtiSetServiceWatch( OSServiceId_CheckISRMemoryAccess );    

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK |
                         OSISRLEVELHOOKERROR | OSISRLEVELHOOKAPPERROR |
                         OSISRLEVELHOOKPROTECTION ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
#if defined(OSHOOKERROR_EXT)
            OSErrorHook( E_OS_DISABLEDINT, OSServiceId_CheckISRMemoryAccess, 0 );
#endif     
            OSOrtiServiceWatchOnExit( OSServiceId_CheckISRMemoryAccess );
            return( 0 );
        }
        else
#endif /* defined(OSEXTSTATUS) */
        {
#if defined(OSHOOKERROR_EXT)
            OSErrorHook( E_OS_CALLEVEL, OSServiceId_CheckISRMemoryAccess, 0 );
#endif     
            OSOrtiServiceWatchOnExit( OSServiceId_CheckISRMemoryAccess );
            return( 0 );
        }
    }
#endif /* defined(OSCHECKCONTEXT) */

#if defined(OSEXTSTATUS)
    if( OSISRIDISINVALID(isrId) )
    {
#if defined(OSHOOKERROR_EXT)
        OSErrorHook( E_OS_ID, OSServiceId_CheckISRMemoryAccess, isrId ); /* invalid ID */
#endif
        OSOrtiServiceWatchOnExit( OSServiceId_CheckISRMemoryAccess );
        return( 0 );
    }
#endif /*defined(OSEXTSTATUS)*/

    isr = &(OsIsrTable[OS_GETOBJIND( isrId )]);

#if defined(OSEXTSTATUS)
    if( isr->type > OSISR1 )    /* if it is a system interrupt */
    {
#if defined(OSHOOKERROR_EXT)
        OSErrorHook( E_OS_ID, OSServiceId_CheckISRMemoryAccess, isrId ); /* invalid ID */
#endif
        OSOrtiServiceWatchOnExit( OSServiceId_CheckISRMemoryAccess );
        return( 0 );
    }
#endif /*defined(OSEXTSTATUS)*/

    access = OSAppMemAccess( isr->appId,
                             (OSDWORD)address, (OSDWORD)address + size - 1,
                             (OSDWORD)isr->isrBos, (OSDWORD)isr->stackPtr );
    OSOrtiServiceWatchOnExit( OSServiceId_CheckISRMemoryAccess );
    return( access );
}
#endif /* !defined(OSNOISR2) */


/*****************************************************************************
 * Function :   OS_CheckTaskMemoryAccess
 *
 * Description: checks whether or not the private memory section of the task
 *              is within the memory section 
 *
 * Returns:     Set of access rights for the specified region of memory.
 *              0 - for no access.    
 *            
 ******************************************************************************/
AccessType OS_CheckTaskMemoryAccess( TaskType taskId,
                                     MemoryStartAddressType address,
                                     MemorySizeType size )
{
    const OSTSKCB* task;
    AccessType access;

    OSOrtiSetServiceWatch( OSServiceId_CheckTaskMemoryAccess );

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK |
                         OSISRLEVELHOOKERROR | OSISRLEVELHOOKAPPERROR |
                         OSISRLEVELHOOKPROTECTION ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
#if defined(OSHOOKERROR_EXT)
            OSErrorHook( E_OS_DISABLEDINT, OSServiceId_CheckTaskMemoryAccess, 0 );
#endif     
            OSOrtiServiceWatchOnExit( OSServiceId_CheckTaskMemoryAccess );
            return( 0 );
        }
        else
#endif /* defined(OSEXTSTATUS) */
        {
#if defined(OSHOOKERROR_EXT)
            OSErrorHook( E_OS_CALLEVEL, OSServiceId_CheckTaskMemoryAccess, 0 );
#endif     
            OSOrtiServiceWatchOnExit( OSServiceId_CheckTaskMemoryAccess );
            return( 0 );
        }
    }
#endif /* defined(OSCHECKCONTEXT) */

#if defined(OSEXTSTATUS)
   if( OSTASKIDISINVALID(taskId) )
   {
#if defined(OSHOOKERROR_EXT)
       OSErrorHook( E_OS_ID, OSServiceId_CheckTaskMemoryAccess, taskId ); /* invalid ID */
#endif
       OSOrtiServiceWatchOnExit( OSServiceId_CheckTaskMemoryAccess );
       return( 0 );
   }
#endif

    task = &(OsTaskTable[OS_GETOBJIND( taskId )]);
    access = OSAppMemAccess( task->appId,
                             (OSDWORD)address, (OSDWORD)address + size - 1,
                             (OSDWORD)task->bos, (OSDWORD)task->tos );
    OSOrtiServiceWatchOnExit( OSServiceId_CheckTaskMemoryAccess );
    return( access );
}

#endif /* defined(OSMEMPROTECTION) */


#if defined(OSAPPLICATION)

/******************************************************************************
* Function:    OS_CallTrustedFunction
*
* Description: calls a trusted function written by user 
*
* Returns:     E_OK
*              E_OS_SERVICE_ID
******************************************************************************/
#if OSNTRUSTEDFUNCTIONS > 0
StatusType OS_CallTrustedFunction( TrustedFunctionIndexType ix,
                                   TrustedFunctionParameterRefType ptr )
{
    OSBYTE tmpApp;
    OSIMSAVE                        /* OSINTMASKTYPE save; */

    OSOrtiSetServiceWatch( OSServiceId_CallTrustedFunction );

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK ) )
    {
#if defined(OSEXTSTATUS)

        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_CallTrustedFunction, 0 ); 
        }
        else  
#endif        
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_CallTrustedFunction, 0 ); 
        }
    }
#endif /* OSCHECKCONTEXT */

    if( ix > OSNTRUSTEDFUNCTIONS - 1 )
    {
        OSRETERROR( E_OS_SERVICEID, OSServiceId_CallTrustedFunction, 0 );
    }

    tmpApp  = OSGetCurApp();

    OSDIS(save);

    OSSetCurApp( OsTrustedFunctionsAppId[ ix ] );

#if !defined(OSNOISR2)
    if( OSISRLEVELMASKED == 0 )
    {               /* temporary assign this runable to the function OS-Application */
        OsRunning->appId = OSGetCurApp();
    }
    else
    {
        OsIsrArray[OSISRLEVELMASKED - 1]->appId = OSGetCurApp();
    }
#else  /* !defined(OSNOISR2) */
    OsRunning->appId = OSGetCurApp();
#endif /* !defined(OSNOISR2) */
    OSRI(save);
    OsTrustedFunctionsTable[ ix ]( ix, ptr );
    OSDIS(save);

#if !defined(OSNOISR2)
    if( OSISRLEVELMASKED == 0 )
    {
        OsRunning->appId = tmpApp;
    }
    else
    {
        OsIsrArray[OSISRLEVELMASKED - 1]->appId = tmpApp;
    }
#else  /* !defined(OSNOISR2) */
    OsRunning->appId = tmpApp;
#endif /* !defined(OSNOISR2) */

    OSSetCurApp(tmpApp);
    OSRI(save);

    OSOrtiServiceWatchOnExit( OSServiceId_CallTrustedFunction );
    return E_OK;
}
#endif  /* OSNTRUSTEDFUNCTIONS > 0*/


/******************************************************************************
 * Function :   CheckObjectAccess
 *
 * Description: returns ability of given application to access given object 
 *
 * Returns:     ACCESS     
 *              NOACCESS
 *            
 * Notes:
 *
 ******************************************************************************/

ObjectAccessType OS_CheckObjectAccess( ApplicationType appId,
                                       ObjectTypeType objectType,
                                       OSObjectType objectId )
{
    OSWORD  objIndex;
    OSDWORD appIdBit;
    OSDWORD appMask;

    OSOrtiSetServiceWatch( OSServiceId_CheckObjectAccess );
    
#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK |
                         OSISRLEVELHOOKERROR | OSISRLEVELHOOKAPPERROR |
                         OSISRLEVELHOOKPROTECTION) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
#if defined(OSHOOKERROR_EXT)
            OSErrorHook( E_OS_DISABLEDINT, OSServiceId_CheckObjectAccess, 0 );
#endif     
            OSOrtiServiceWatchOnExit( OSServiceId_CheckObjectAccess );
            return( NO_ACCESS );
        }
        else
#endif /* defined(OSEXTSTATUS) */
        {
#if defined(OSHOOKERROR_EXT)
            OSErrorHook( E_OS_CALLEVEL, OSServiceId_CheckObjectAccess, 0 );
#endif     
            OSOrtiServiceWatchOnExit( OSServiceId_CheckObjectAccess );
            return( NO_ACCESS );
        }
    }
#endif /* defined(OSCHECKCONTEXT) */

#if defined(OSEXTSTATUS)
    if( OSAPPIDISINVALID(appId) )
    {
#if defined(OSHOOKERROR_EXT)
        OSErrorHook( E_OS_ID, OSServiceId_CheckObjectAccess, appId ); /* invalid ID */
#endif
        OSOrtiServiceWatchOnExit( OSServiceId_CheckObjectAccess );
        return( NO_ACCESS);
    }
#endif /* defined(OSEXTSTATUS) */

    appIdBit = 1 << appId;

    if( objectType != OS_GETOBJTYP( objectId ))
    {
        OSOrtiServiceWatchOnExit( OSServiceId_CheckObjectAccess );
        return( NO_ACCESS);
    }
    
    objIndex = OS_GETOBJIND( objectId );
    switch( objectType )
    {
        case OBJECT_TASK:
            appMask = OsTaskTable[ objIndex ].appMask;
            break;

#if !defined(OSNOISR)
        case OBJECT_ISR:
            appMask = OsIsrTable[ objIndex ].appMask;
            break;
#endif

#if (OSNUSERALMS > 0)
        case OBJECT_ALARM:
            appMask = OSALMARRAY[ objIndex ].appMask;
            break;
#endif

#if defined(OSRESOURCE)
        case OBJECT_RESOURCE:
            appMask = OsResources[ objIndex ].appMask;
            break;
#endif

#if defined(OSCOUNTER)
        case OBJECT_COUNTER:
            appMask = OsCounters[ objIndex ].appMask;
            break;
#endif

#if defined(OSSCHEDULETABLES)
        case OBJECT_SCHEDULETABLE:
            appMask = OsScheduleTables[ objIndex ].appMask;
            break;
#endif

#if (OSNMSGS > 0)
        case OBJECT_MESSAGE:
            if( objIndex < OSNRCVMSGS )
            {
                appMask = OsMessages[ objIndex ].appMask;
            }
            else /* sending messages  */
            {
                appMask = OsSndMessages[ objIndex-OSNRCVMSGS ].appMask;
            }
            break;
#endif

        default:
            appMask = 0;
            break;
    }
    OSOrtiServiceWatchOnExit( OSServiceId_CheckObjectAccess );
    return ( appMask & appIdBit ) ? ( ACCESS ) : ( NO_ACCESS );
}

/***************************************************************************
 * function:   OS_TerminateApplication(RestartType RestartOption)
 *
 * Description: kills all tasks and ISRs which belong to current application 
 *
 * Returns: E_OS_CALLLEVEL if called from wrong context
 *          E_OS_ID if Restart option is not of RestartType
 *          no return otherwise
 * Notes:  
 **************************************************************************/
StatusType OS_TerminateApplication( RestartType RestartOption )
{
    OSOrtiSetServiceWatch( OSServiceId_TerminateApplication );

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK | OSISRLEVELHOOKAPPERROR ) )
    {
#if defined(OSEXTSTATUS)

        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
            OSRETERROR( E_OS_DISABLEDINT, OSServiceId_TerminateApplication, 0 ); 
        }
        else  
#endif        
        {
            OSRETERROR( E_OS_CALLEVEL, OSServiceId_TerminateApplication, 0 ); 
        }
    }
#endif /* OSCHECKCONTEXT */

    if( (OSDWORD)RestartOption > (OSDWORD)RESTART )
    {
        OSRETERROR( E_OS_VALUE, OSServiceId_TerminateApplication, 0 );
    }

    OSDI();
    OSDHI();

    OSOrtiSetOldServiceID( OSServiceId_TerminateApplication );

    (void)OSTerminateApplication(RestartOption);

    if( ( (OsKilled & OSRUNTSKKILLED) != 0 )
#if defined(OSISRENTRYEXIT)
        && ( OSISRLEVELMASKED == 0 )
#endif
    ) 
    {
        OSSETTASKMSR();             /* set MSR for Task, EE = 1 */
        OsKilled &= ~OSRUNTSKKILLED;
        OsRunning = OSGETMAXPRIOTASK;
        OSTaskInternalDispatch();
    }

#if (OSNIPLS > 0)
    /* otherwise running ISR is killed - no other option */

    OsIsrLevel--;
    OSLongJmp( OsISRbufs[OSISRLEVELMASKED] ); /* back to OSInterruptDispatcher */
#endif /* (OSNIPLS > 0) */

    return E_OK;  /* unreachable point */
}

/***************************************************************************
 * function:   OSTerminateApplication(RestartType RestartOption)
 *
 * Description: kills all tasks and ISRs which belong to current application 
 *
 * Returns:    OSTRUE on success,
 *             OSFALSE - otherwise 
 *
 * Notes:   
 **************************************************************************/

OSWORD OSTerminateApplication(RestartType RestartOption)
{
#if defined(OSHAS_RESTARTTASK)
    OSWORD restartTask;
#endif

    if(OSGetCurApp() == INVALID_OSAPPLICATION) 
    {                                   /* it might be in ErrorHook */
        return OSFALSE;
    }
#if (OSNTRUSTEDFUNCTIONS > 0)
                    /* restore current application in case of Trusted Function */
#if !defined(OSNOISR2)
    if( OSISRLEVELMASKED != 0 )
    {
        OSSetCurApp( OsIsrCfg[ OsIsrArray[OSISRLEVELMASKED-1]-&OsIsrTable[0] ].appId );
    }
    else
#endif
    {
        OSSetCurApp( OsTaskCfgTable[OsRunning->taskId].appId );
    }
#endif /* OSNTRUSTEDFUNCTIONS > 0 */

#if (OSNUSERALMS > 0)
    OSKillAppAlarms();
#endif
#if defined(OSSCHEDULETABLES)
    OSKillAppScheduleTables();
#endif

    OSKillAppTasks();                   /* kill all tasks of this application */

#if defined(OSHAS_RESTARTTASK)
    restartTask = OsAppTable[OSGetCurApp()].restartTask;

    if( (restartTask != OSNULLTASK) && (RESTART == RestartOption) )
    {                                   /* set Task ready as in ActivateTask   */
#if defined(OSECC)
#if (OSNXTSKS > 0)
        OsTaskTable[restartTask].set_event = OSNOEVENTS;
#endif
#endif /* defined(OSECC) */
        OSActivateTaskInAlm( restartTask );  /* here is the same case as when task is activated from alarm action */
    }
#endif /*defined(OSHAS_RESTARTTASK)*/

#if (OSNUSERISR > 0)
    OSKillAppISRs(); /* kill all ISRs of this application */
#endif /*!defined(OSNUSERISR)*/
    return OSTRUE;
}

/***************************************************************************
 * function:   OS_CheckObjectOwnership
 *
 * Description: finds the application that owns the object
 *
 * Returns: ID of the application that owns the object
 *          INVALID_OSAPPLICATION if no application owns the object
 *          or if the object is RES_SCHEDULER
 * Notes:  none
 **************************************************************************/

ApplicationType OS_CheckObjectOwnership( ObjectTypeType objectType,
                                         OSObjectType objectId )
{
    OSWORD index;

    OSOrtiSetServiceWatch( OSServiceId_CheckObjectOwnership );    

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK |
                         OSISRLEVELHOOKERROR | OSISRLEVELHOOKAPPERROR |
                         OSISRLEVELHOOKPROTECTION ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
#if defined(OSHOOKERROR_EXT)
            OSErrorHook( E_OS_DISABLEDINT, OSServiceId_CheckObjectOwnership, 0 );
#endif     
            OSOrtiServiceWatchOnExit( OSServiceId_CheckObjectOwnership );
            return( INVALID_OSAPPLICATION );
        }
        else
#endif /* defined(OSEXTSTATUS) */
        {
#if defined(OSHOOKERROR_EXT)
            OSErrorHook( E_OS_CALLEVEL, OSServiceId_CheckObjectOwnership, 0 );
#endif     
            OSOrtiServiceWatchOnExit( OSServiceId_CheckObjectOwnership );
            return( INVALID_OSAPPLICATION );
        }
    }
#endif /* OSCHECKCONTEXT */

#if defined(OSRES_SCHEDULER)
    if(objectId == (ResourceType)OS_MKOBJID(OBJECT_RESOURCE, (OSNALLRES-1)) )
    {
        OSOrtiServiceWatchOnExit( OSServiceId_CheckObjectOwnership );
        return( INVALID_OSAPPLICATION );
    }
#endif /* defined(OSRES_SCHEDULER) */

    index = OS_GETOBJIND(objectId);
    switch(objectType)
    {
    case OBJECT_TASK:
        OSOrtiServiceWatchOnExit( OSServiceId_CheckObjectOwnership );
        return index < OSNTSKS ? OsTaskTable[index].appId : INVALID_OSAPPLICATION;

#if !defined(OSNUSERISR)
    case OBJECT_ISR:
        OSOrtiServiceWatchOnExit( OSServiceId_CheckObjectOwnership );
        return index < OSNUSERISR ? OsIsrTable[index].appId : INVALID_OSAPPLICATION;
#endif /*!defined(OSNOISR)*/

#if (OSNUSERALMS > 0)
    case OBJECT_ALARM:
        OSOrtiServiceWatchOnExit( OSServiceId_CheckObjectOwnership );
        return index < OSNUSERALMS ? OSALMARRAY[index].appId : INVALID_OSAPPLICATION;
#endif

#if defined(OSCOUNTER)
    case OBJECT_COUNTER:
        OSOrtiServiceWatchOnExit( OSServiceId_CheckObjectOwnership );
        return index < OSNCTRS ? OsCounters[index].appId : INVALID_OSAPPLICATION;
#endif/*defined(OSCOUNTER)*/

#if defined(OSSCHEDULETABLES)
    case OBJECT_SCHEDULETABLE:
        OSOrtiServiceWatchOnExit( OSServiceId_CheckObjectOwnership );
        return index < OSNSCTS ? OsScheduleTables[index].appId : INVALID_OSAPPLICATION;
#endif/*defined(OSSCHEDULETABLES)*/

#if OSNMSGS > 0
    case OBJECT_MESSAGE: 
        if( index < OSNRCVMSGS ) /* Receiving messages */
        {
            OSOrtiServiceWatchOnExit( OSServiceId_CheckObjectOwnership );
            return OsMessages[index].appId;
        }
        else                     /* Sending messages */
        {
            index = index - OSNRCVMSGS;
            OSOrtiServiceWatchOnExit( OSServiceId_CheckObjectOwnership );
            return index < OSNSNDMSGS ? OsSndMessages[index].appId : INVALID_OSAPPLICATION;
        }
#endif/*OSNMSGS > 0*/

#if defined(OSRESOURCE) 
    case OBJECT_RESOURCE:
        OSOrtiServiceWatchOnExit( OSServiceId_CheckObjectOwnership );
        return (index < OSNALLRES) ? OsResources[index].appId : INVALID_OSAPPLICATION;
#endif/*defined(OSRESOURCE) */
    default:
        OSOrtiServiceWatchOnExit( OSServiceId_CheckObjectOwnership );
        return( INVALID_OSAPPLICATION );
    }

    /* It is unreachable point */
}

/******************************************************************************
 * Function:    OS_GetApplicationID
 *
 * Description: shows which applications task,ISR or hook is running
 *
 * Returns:     current application Id or INVALID_OSAPPLICATION.
 *
 ******************************************************************************/
 ApplicationType OS_GetApplicationID( void )
 {
     OSOrtiSetServiceWatch( OSServiceId_GetApplicationID );

#if defined(OSCHECKCONTEXT)
    if( OSIsrLevelCheck( OSISRLEVELTASKMASK |
                         OSISRLEVELHOOKERROR | OSISRLEVELHOOKAPPERROR |
                         OSISRLEVELHOOKPRETASK | OSISRLEVELHOOKPOSTTASK |
                         OSISRLEVELHOOKSTARTUP | OSISRLEVELHOOKSHUTDOWN |
                         OSISRLEVELHOOKPROTECTION ) )
    {
#if defined(OSEXTSTATUS)
        if( OsIsrLevel & OSISRLEVELDISABLEDINTERRUPTS )
        {
#if defined(OSHOOKERROR_EXT)
            OSErrorHook( E_OS_DISABLEDINT, OSServiceId_GetApplicationID, 0 );
#endif     
            OSOrtiServiceWatchOnExit( OSServiceId_GetApplicationID );
            return( INVALID_OSAPPLICATION );
        }
        else
#endif /* defined(OSEXTSTATUS) */
        {
#if defined(OSHOOKERROR_EXT)
            OSErrorHook( E_OS_CALLEVEL, OSServiceId_GetApplicationID, 0 );
#endif     
            OSOrtiServiceWatchOnExit( OSServiceId_GetApplicationID );
            return( INVALID_OSAPPLICATION );
        }
    }
#endif /* defined(OSCHECKCONTEXT) */

    OSOrtiServiceWatchOnExit( OSServiceId_GetApplicationID );
    return OSGetCurApp( );
 }

#endif /* defined(OSAPPLICATION) */


/***************************************************************************
 * Function:    OSExceptionError
 *
 * Description: it is called when Instruction Error occurs.
 *
 * Returns:     never
 *
 **************************************************************************/
void OSExceptionError( OSDWORD srr0, OSDWORD srr1 )
{
    StatusType ecode;

#if defined(OSMEMPROTECTION)
    OSDWORD sperr;
#endif
#if defined(OSE200Z4) || defined(OSE200Z7) || defined(OSMEMPROTECTION)
    OSDWORD mcsr;
    mcsr = OSGetMCSR();
#endif
#if defined(OSE200Z4) || defined(OSE200Z7)
    OSSetMCSR( mcsr );  /* clear Machine check asynchronous events */
#endif

#if defined(OSMEMPROTECTION)
    if( sperr != 0 )          /* MPU exeception ? */
    {
        ecode = E_OS_PROTECTION_MEMORY;
        OSMPU_CESR |= sperr;  /* the SPERR bits are 'write one to clear' */
    }
    else
    {
        if( mcsr )
        {
            if( ( mcsr & OSMCSR_EXCP_ERR ) != 0 )
            {
                OSShutdownOS( E_OS_SYS_FATAL );
            }

            if( ( mcsr & OSMCSR_BUS_ERROR ) != 0 )
            {
                ecode = E_OS_PROTECTION_MEMORY;
            }
            else
            {
                ecode = E_OS_PROTECTION_EXCEPTION;
            }
        }
        else
        {
            if( (OSGetESR() & OSESR_ST) != 0 )
            {
                ecode = E_OS_PROTECTION_MEMORY;
            }
            else
            {
                ecode = E_OS_PROTECTION_EXCEPTION;
            }
        }
    }

#else  /* defined(OSMEMPROTECTION) */
    ecode = E_OS_PROTECTION_EXCEPTION;
#endif /* defined(OSMEMPROTECTION) */

#if defined( OSHOOKPROTECTION ) && !defined(OSSC1)
    /* if exception occurs in OS code itself */ 
    if( ( (srr0 >= (OSDWORD)OS_BEGIN_DSADDR(ostext)) && (srr0 < (OSDWORD)OS_END_DSADDR(ostext)) && ((srr1 & OSMSR_PR) == 0) )
#if defined(OSHOOKERROR) || defined(OSCOMHOOKERROR)
    /* if exception occurs in error hooks */
        || ( OsIsrLevel & (OSISRLEVELHOOKERROR | OSISRLEVELHOOKCOM) )
#endif
#if !defined(OSNOISR1)
    /* if exception occurs in ISR of category 1 */
        || ( OSISRGetPrio( ) > OSHIGHISRPRIO )
#endif
        ) 
    {
        OSShutdownOS( ecode );
    }

    OSProtectionHandler( ecode );
#else
    OSShutdownOS( ecode );
#endif /* defined( OSHOOKPROTECTION ) && !defined(OSSC1) */
}

#if defined(OSMEMPROTECTION)
/***************************************************************************
 * Function:    OSTLBException
 *
 * Description: TLB exception (data or code) .
 *
 * Returns:     never
 *
 **************************************************************************/

void OSTLBException( OSDWORD srr0, OSDWORD srr1 )
{
#if defined( OSHOOKPROTECTION )
    /* if exception occurs in OS code itself */ 
    if( ( (srr0 >= (OSDWORD)OS_BEGIN_DSADDR(ostext)) && (srr0 < (OSDWORD)OS_END_DSADDR(ostext)) && ((srr1 & OSMSR_PR) == 0) )
#if defined(OSHOOKERROR) || defined(OSCOMHOOKERROR)
    /* if exception occurs in error hooks */
        || ( OsIsrLevel & (OSISRLEVELHOOKERROR | OSISRLEVELHOOKCOM) )
#endif
#if !defined(OSNOISR1)
    /* if exception occurs in ISR of category 1 */
        || ( OSISRGetPrio( ) > OSHIGHISRPRIO )
#endif
        ) 
    {
        OSShutdownOS( E_OS_PROTECTION_MEMORY );
    }

    OSProtectionHandler( E_OS_PROTECTION_MEMORY );
#else
    OSShutdownOS( E_OS_PROTECTION_MEMORY );
#endif /* defined(OSHOOKPROTECTION) */
}
#endif /* defined(OSMEMPROTECTION) */

#if defined(OSHOOKPROTECTION)
/****************************************************************************************
 * Function:    OSProtectionHandler
 *
 * Description: called from Memory and CPU exception handlers
 *
 * Returns:     never
 *
 ****************************************************************************************/

void OSProtectionHandler( StatusType ecode )
{
    ProtectionReturnType action;

#if defined(OSMEMPROTECTION)
    RestartType restart = RESTART;

    OsViolatorAppId = OSGetCurApp();
#endif

    OsViolatorTaskId = INVALID_TASK;

    OsViolatorISRId = INVALID_ISR;

#if !defined(OSNOISR2)
    if( OSISRLEVELMASKED != 0 )
    {
        OsViolatorISRId = OS_MKOBJID(OBJECT_ISR,OsIsrArray[OSISRLEVELMASKED-1]-&OsIsrTable[0]);
    }
    else
#endif
    {
        if( OSTSKIND(OsRunning) != OSNULLTASK )
        {
            OsViolatorTaskId = OS_MKOBJID(OBJECT_TASK, OSTSKIND(OsRunning));
        }
    }

    OSOrtiSetServiceWatch( OSServiceId_ProtectionHook );    /* set watch to this service */ 
    OSSETPROTCNXT();
    action = ProtectionHook( ecode );    
    OSCLRPROTCNTX();
    OSOrtiServiceWatchOnExit( OSServiceId_ProtectionHook ); /* clear service watch on hook leaving */ 

    switch( action ) 
    {
        case PRO_KILLTASKISR: 
#if (OSNUSERISR > 0)
            if( OSISRLEVELMASKED != 0 )
            {
                OSKillRunningISR();
            }
            else 
#endif /* OSNUSERISR > 0 */
            {
                if( OSTSKIND(OsRunning) != OSNULLTASK )
                {
                    OSKillTask(OsRunning); 
                }
#if defined(OSMEMPROTECTION)
                else if( OSTerminateApplication(NO_RESTART) )
                {                                       /* if no running Task or ISR found */
                    break; 
                }
#endif
                else
                {
                    OSShutdownOS( ecode );
                }
            }
            break;

        case PRO_KILLAPPL: 
#if defined(OSMEMPROTECTION)
            restart = NO_RESTART; /* no break */
#endif

        case PRO_KILLAPPL_RESTART:
#if defined(OSMEMPROTECTION)
            if( OSTerminateApplication(restart) )
            {
                break;
            }
             /* no break. OSShutdownOS() shall be called */
#endif
        case PRO_SHUTDOWN:
        default: 
            OSShutdownOS( ecode );
    }
    OSDI();

    if( ( (OsKilled & OSRUNTSKKILLED) != 0 )
#if defined(OSISRENTRYEXIT)
    && ( OSISRLEVELMASKED == 0 )
#endif
    ) 
    {                            
        OSSETTASKMSR();             /* set MSR for Task, EE = 1 */
        OsRunning = OSGETMAXPRIOTASK;
        OsKilled &= ~OSRUNTSKKILLED;
        OSTaskInternalDispatch();
        /* no return here */
    }
#if (OSNIPLS > 0)
    
    /* otherwise running ISR is killed - no other option */

    OsIsrLevel--;
    OSLongJmp( OsISRbufs[OSISRLEVELMASKED] ); /* back to OSInterruptDispatcher */
#endif    
}
#endif /* defined(OSHOOKPROTECTION) */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "ossections.h"
#define OS_START_ONCE_SEC_VAR_FAST_UNSPECIFIED
#include "ossections.h"
#define OS_START_SEC_VAR_UNSPECIFIED
#include "ossections.h"
#define OSTEXT_START_SEC_CODE
#include "ossections.h"
