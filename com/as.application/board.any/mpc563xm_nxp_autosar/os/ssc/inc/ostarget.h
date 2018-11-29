#ifndef OSTARGET_H
#define OSTARGET_H
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
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/inc/ostarget.h,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  Target-specific definitions
*
* Notes:        
*
******************************************************************************/

#if defined(OSCWPPC)
#pragma unsafe_global_reg_vars off
#endif

/* Disable/Enable Hardware Interrupts */
#if defined(OSDIABPPC)
#define OSDHI()             OSASM(" wrteei 0"); OSASM(" msync ")
#define OSEHI()             OSASM(" msync "); OSASM(" wrteei 1 ")
#define OSMSYNC()           OSASM(" msync ")
#endif /* defined(OSDIABPPC) */

#if defined(OSCWPPC)
#define OSDHI()             OSASM{ wrteei 0 }; OSASM{ msync }
#define OSEHI()             OSASM{ msync };  OSASM{ wrteei 1 }
#define OSMSYNC()           OSASM{ msync }
#endif /* defined(OSCWPPC) */

#if defined(OSGHSPPC)
#define OSDHI()             __DI( ); __MSYNC( )
#define OSEHI()             __MSYNC( ); __EI( )
#define OSMSYNC()           __MSYNC( )
#endif  /* defined(OSGHSPPC) */

#if defined(OSSC1) && !defined(OSISRENTRYEXIT)
#define OSSETTASKMSR()  OSEHI()
#else
#define OSSETTASKMSR()  OSMSYNC(); OSSETMSR(OsInitialMSR)   /* set MSR for Task */
#endif

/* Set the SP register new value */
#if defined(OSDIABPPC)
OSASM void OSLOADSP(OSDWORD * loadsp)
{
%reg loadsp
    mr r1, loadsp
}
#endif

#if defined(OSCWPPC)
OSINLINE void OSLOADSP(register OSDWORD *loadsp )
{
    OSASM volatile 
    {
        mr r1, loadsp;
    }
}
#endif

#if defined(OSGHSPPC)
OSASM void OSLOADSP(OSDWORD* loadsp)
{
%reg loadsp
    mr r1, loadsp
}
#endif

/* Get the SP register value */
#if defined(OSDIABPPC)
OSASM OSDWORD OSGETSTACKPOINTER()
{
    mr r3, r1
}
#endif

#if defined(OSCWPPC)
OSINLINE OSDWORD OSGETSTACKPOINTER( void )
{
    register OSDWORD result;
    OSASM { mr  result, r1; }
    return result;
}
#endif

#if defined(OSGHSPPC)
OSASM OSDWORD OSGETSTACKPOINTER()
{
    mr r3, r1
}
#endif

/* Get the MSR register value */
#if defined(OSDIABPPC)
OSASM OSDWORD OSGETMSR( void )
{
    mfmsr  r3
}
#endif

#if defined(OSGHSPPC)
#define OSGETMSR( ) __GETSR( )
#endif

#if defined(OSCWPPC)
OSINLINE OSDWORD OSGETMSR( void )
{
    register OSDWORD result;
    OSASM { mfmsr result; }
    return result;
}
#endif

/* Set the MSR register new value */
#if defined(OSDIABPPC)
OSASM void OSSETMSR(OSDWORD osmsr)
{
%reg osmsr
    mtmsr  osmsr
}
#endif

#if defined(OSGHSPPC)
#define OSSETMSR( value) __SETSR( value )
#endif

#if defined(OSCWPPC) 
OSINLINE void OSSETMSR(register OSDWORD osmsr)
{
    OSASM { mtmsr   osmsr; }
}
#endif

/* Get the PIR register value */
#if defined(OSDIABPPC)
OSASM OSWORD OSGetCoreID( void )
{
    mfspr r3, 286
}
#endif

#if defined(OSGHSPPC)
#define OSGetCoreID() ((OSWORD) OSMFSPR(286))
#endif

#if defined(OSCWPPC)
OSINLINE OSWORD OSGetCoreID( void )
{
    register OSWORD result;
    OSASM { mfspr result, 286; }
    return result;
}
#endif

/* Get the HID0 register value */
#if defined(OSDIABPPC)
OSASM OSDWORD OSGETHID0( void )
{
    mfspr  r3, 1008
}
#endif

#if defined(OSGHSPPC)
#define OSGETHID0( ) OSMFSPR( 1008 )
#endif

#if defined(OSCWPPC) 
OSINLINE OSDWORD OSGETHID0( void )
{
    register OSDWORD result;
    OSASM { mfspr result, 1008; }     /* read HID0 */
    return result;
}
#endif

/* Set the HID0 register new value */
#if defined(OSDIABPPC)
OSASM void OSSETHID0(OSDWORD oshid0)
{
%reg oshid0
    mtspr  1008, oshid0
    msync
}
#endif

#if defined(OSGHSPPC)
#define OSSETHID0( value ) OSMTSPR( 1008, value ); OSMSYNC( )
#endif

#if defined(OSCWPPC)
OSINLINE volatile void OSSETHID0(register OSDWORD oshid0)
{
    OSASM { mtspr   1008, oshid0; }
    OSASM { msync; }
}
#endif

/* Time base reading macros */
#if defined(OSDIABPPC)
OSASM OSDWORD OSGETTB()
{
    mfspr   r3, 268                /* read timebase via UTBL */
}
OSASM OSDWORD OSGETTBU(register OSDWORD tbu)
{
%reg tbu
    mfspr   tbu, 269               /* read timebase via UTBU */
}
OSASM OSDWORD OSGETTBL(register OSDWORD tbl)
{
%reg tbl
    mfspr   tbl, 268               /* read timebase via UTBL */
}
#endif /* defined(OSDIABPPC) */

#if defined(OSGHSPPC) 
#define OSGETTB( ) OSMFSPR( 268 )
#define OSGETTBU( tbu ) tbu = OSMFSPR( 269 )
#define OSGETTBL( tbl ) tbl = OSMFSPR( 268 )
#endif

#if defined(OSCWPPC)
OSINLINE OSDWORD OSGETTB( void )
{
    register OSDWORD result;
    OSASM { mfspr   result, 268; } /* read timebase via UTBL */
    return result;
}
#define OSGETTBU(tbu)  OSASM { mfspr tbu, 269; }
#define OSGETTBL(tbl)  OSASM { mfspr tbl, 268; }
#endif /* defined(OSCWPPC) */

#define OSGETTB64(tb)                       \
{                                           \
    register OSDWORD low, up1, up2;         \
                                            \
    OSGETTBU(up1);                          \
    OSGETTBL(low);                          \
    OSGETTBU(up2);                          \
                                            \
    if( up1 != up2 )                        \
    {                                       \
        OSGETTBL(low);                      \
    }                                       \
                                            \
    (tb) = ( (OSQWORD)up2 << 32ull ) + low; \
}

/* Time base writing macros, ticks must be more then zero */ 
#if defined(OSDIABPPC)
OSASM void OSSETTBL(OSSIGNEDDWORD ticks)
{
%reg ticks
    mttbl   ticks
}
OSASM void OSSETTBU(OSSIGNEDDWORD ticks)
{
%reg ticks
    mttbu   ticks
}
#endif /* defined(OSDIABPPC) */

#if defined(OSGHSPPC)
#define OSSETTBL( value ) OSMTSPR( 284, value )
#define OSSETTBU( value ) OSMTSPR( 285, value )
#endif

#if defined(OSCWPPC)
OSINLINE void OSSETTBL( register OSSIGNEDDWORD ticks )
{
    OSASM { mtspr 284, ticks; }
}
OSINLINE void OSSETTBU( register OSSIGNEDDWORD ticks )
{
    OSASM { mtspr 285, ticks; }
}
#endif  /* defined(OSCWPPC) */

/* Get the TCR register value */
#if defined(OSDIABPPC)
OSASM OSDWORD OsGetTCR()
{
    mfspr r3, 340
}
#endif

#if defined(OSGHSPPC)
#define OsGetTCR( ) OSMFSPR( 340 )
#endif

#if defined(OSCWPPC)
OSINLINE OSDWORD OsGetTCR( void )
{
    register OSDWORD result;
    OSASM { mfspr result, 340; }
    return result;
}
#endif

/* Set the TCR register new value */
#if defined(OSDIABPPC)
OSASM void OsSetTCR(OSDWORD value)
{
%reg value
    mtspr 340, value
}
#endif

#if defined(OSGHSPPC)
#define OsSetTCR( value ) OSMTSPR( 340, value )
#endif

#if defined(OSCWPPC)
OSINLINE void OsSetTCR(register OSDWORD value)
{
    OSASM{    mtspr   340, value};
}
#endif

/* Get the TSR register value */
#if defined(OSDIABPPC)
OSASM OSDWORD OsGetTSR()
{
    mfspr r3, 336
}
#endif

#if defined(OSGHSPPC)
#define OsGetTSR( ) OSMFSPR( 336 )
#endif

#if defined(OSCWPPC)
OSINLINE OSDWORD OsGetTSR( void )
{
    register OSDWORD result;
    OSASM { mfspr result, 336; }
    return result;
}
#endif

/* Set the TSR register new value */
#if defined(OSDIABPPC)
OSASM void OsSetTSR(OSDWORD value)
{
%reg value
    mtspr       336, value /*  */
}
#endif

#if defined(OSGHSPPC)
#define OsSetTSR( value ) OSMTSPR( 336, value )
#endif

#if defined(OSCWPPC)
OSINLINE void OsSetTSR(register OSDWORD value)
{
    OSASM { mtspr       336, value };
}
#endif

/* Get the DEC register value */
#if defined(OSDIABPPC)
OSASM OSDWORD OSGETDEC()
{
    mfdec r3
}
#endif

#if defined(OSGHSPPC)
#define OSGETDEC( ) OSMFSPR( 22 )
#endif

#if defined(OSCWPPC)
OSINLINE OSDWORD OSGETDEC( void )
{
    register OSDWORD result;
    OSASM { mfdec result; }
    return result;
}
#endif

/* Set the DEC register new value */
/* It is not necessary to adjust delta for decrementer because a decrementer */
/* event occurs when its value is 0x0000_0001 */
#if defined(OSDIABPPC)
OSASM void OSDecTimerSet(OSDWORD ticks)
{
%reg ticks
    mtdec       ticks
}
#endif

#if defined(OSGHSPPC)
#define OSDecTimerSet( value ) OSMTSPR( 22, value )
#endif

#if defined(OSCWPPC)
OSINLINE void OSDecTimerSet( register OSDWORD ticks )
{
    OSASM { mtdec ticks; }
}
#endif

/* Set the DECAR register new value */
#if defined(OSDIABPPC)
OSASM void OsSetDECAR(OSDWORD value)
{
%reg value
    mtspr   54, value
}
#endif

#if defined(OSGHSPPC)
#define OsSetDECAR( value ) OSMTSPR( 54, value )
#endif

#if defined(OSCWPPC)
OSINLINE void OsSetDECAR(register OSDWORD value)
{
    OSASM { mtspr   54, value };
}
#endif


/* Macros for INTC IPL manipulations, to be called with all interrupts disabled */
#define OSISRSetPrio(prio) OSINTC_CPR = (prio) /* Set current ISR prio to the highest OS ISR prio */    
#define OSISRGetPrio()     OSINTC_CPR          /* Get current ISR prio */

/* Unmasks all interrupts */
#define OSISRALLON() OSMSYNC(); OSISRSetPrio(0)

#if !defined(OSISRENTRYEXIT) && !defined(OSTIMINGPROTECTION)
/* If there are no ISR configured Disable/Enable interrupts macros are empty */
#define OSIMSAVE
#define OSDIS( save )
#define OSRI( save )
#define OSDI()
#define OSEI()

#else   /* !defined(OSISRENTRYEXIT) && !defined(OSTIMINGPROTECTION) */

/* defines the "save" local variables for current interrupts state saving */
/* `;' shall be in the definition to avoid it inside local variables declaration */
#define OSIMSAVE  OSINTMASKTYPE save;

/* Enable all interrupts in INTC */
#define OSEI()    OSISRALLON()

/* Disable all interrupts (for Multilevel interrupts - all */
/*             interrupts of cat.2 and interrupt of TP Timer) */
/* Notes: State of interrupts is saved into the "save" local variables */
#define OSDI()  OSISRSetPrio(OSHIGHINTPRIO); OSMSYNC()

/* OSDIS saves current SIMASK in the local variable and */
/* disables all interrupts of the category 2 and Timers interrupts */
#define OSDIS( save )                   \
    save = OSISRGetPrio();              \
    if( save < OSHIGHINTPRIO )          \
    {                                   \
        OSDI();                         \
    }

/* Restore interrupts state from the "save" local variables */
/* Notes: enables external interrupts */
#define OSRI( save )    OSMSYNC(); OSISRSetPrio(save)

#endif  /* !defined(OSISRENTRYEXIT) && !defined(OSTIMINGPROTECTION) */

#if defined(OSAPPLICATION)
/* Get the SPRG4 register value */
#if defined(OSDIABPPC)
OSASM OSDWORD OSGetSPRG4( void )
{
    mfspr   r3, 260 
}
#endif

#if defined(OSGHSPPC)
#define OSGetSPRG4( ) OSMFSPR( 260 )
#endif

#if defined(OSCWPPC)
OSINLINE OSDWORD OSGetSPRG4( void )
{
    register OSDWORD x;

    OSASM { mfspr    x, 260; }
    return x;
}
#endif

/* Set the SPRG4 register new value */
#if defined(OSDIABPPC)
OSASM void OSSetSPRG4( OSDWORD x )
{
%reg x
        mtsprg4  x
}
#endif

#if defined(OSGHSPPC)
#define OSSetSPRG4( value ) OSMTSPR( 276, value )
#endif

#if defined(OSCWPPC)
OSINLINE void OSSetSPRG4( register OSDWORD x )
{
    OSASM { mtsprg4 x;  }
}
#endif
#endif /* defined(OSAPPLICATION) */

#if defined(OSMEMPROTECTION)
/* Get the PID0 register value */ 
#if defined(OSDIABPPC)
OSASM OSDWORD OSGetPID0( void )
{
    mfspr       r3, 48
}
#endif

#if defined(OSGHSPPC)
#define OSGetPID0( ) OSMFSPR( 48 )
#endif

#if defined(OSCWPPC)
OSINLINE OSDWORD OSGetPID0( void )
{
    register OSDWORD x;

    OSASM { mfpid   x; }
    return x;
}
#endif
#endif /* defined(OSMEMPROTECTION) */

/* Sets the PID0 register value */
/* Notes: in SC3 and SC4 it is used to control access to stacks,
 *        in SC1, SC2 it is used to generate OTM on Task switch */
#if defined(OSDIABPPC)
OSASM void OSSetPID0( OSDWORD x )
{
%reg x
    mtspr    48, x
}
#endif

#if defined(OSGHSPPC)
#define OSSetPID0( value ) OSMTSPR( 48, value )
#endif

#if defined(OSCWPPC)
OSINLINE void OSSetPID0( register OSDWORD x )
{
    OSASM { mtspr  48, x; }
}
#endif


#define OSMSR_RI    0x00000002ul /* Recoverable exception bit */
#define OSMSR_ME    0x00001000ul /* Machine check enable bit */
#define OSMSR_PR    0x00004000ul /* Problem state: 0 - supervisor mode, 1 - user mode */
#define OSMSR_EE    0x00008000ul /* External interrupt enable bit */
#define OSMSR_CE    0x00020000ul /* Critical interrupt enable bit */
#define OSMSR_POW   0x00040000ul /*  MSR/POW: power management enable bit (WE bit in ESYS)  */
#define OSMSR_ISDS  0x00000000ul /*  IS and DS bits aren't used for memory protection on MPU */

/* Bits in MCESR register */
#define OSMCSR_BUS_ERROR    0x0000001Cul /* BUS_IERROR | BUS_DRERR | BUS_WRERR */
#define OSMCSR_EXCP_ERR     0x08000000ul /* ISI, ITLB, or Bus Error on first instruction fetch for an exception handler */

/* Bits in ESR register */
#define OSESR_ST            0x00800000ul /* bit 'Store operation' */
          
/* HID0 register bits description */
#define OSHID0_DOZE         0x00800000ul /* Doze mode enable */
#define OSHID0_NAP          0x00400000ul /* Nap mode enable */
#define OSHID0_SLEEP        0x00200000ul /* Sleep mode enable */
#define OSHID0_DPM          0x00100000ul /* Dynamic power management enable */

#define OSMPC_DCI()         OSSETMSR(( OSGETMSR() ) & ~((OSMSR_EE) | (OSMSR_CE)) )

#if defined(OSTIMPRESCALER) || defined(OSTIM2PRESCALER)
/* Prescaler/SIU registers formats conversion */
/* Shift bit fields to register position */
#define OSTPSFIELD(field)   OSTPS_##field

#if defined(OSTIMPRESCALER)
#define OSTPS2REG(field)    ( ( OSTIMPRESCALER & OSTPSFIELD(field) ) << (OSTPSFIELD(field)##_REG ) )
                                                /* Shift bit field to value position  */
#endif  /* defined(OSTIMPRESCALER) */

#if defined(OSTIM2PRESCALER)
#define OSTPS2REG2(field)    ( ( OSTIM2PRESCALER & OSTPSFIELD(field) ) << (OSTPSFIELD(field)##_REG ) )
#endif  /* defined(OSTIM2PRESCALER) */
#endif  /* defined(OSTIMPRESCALER) || defined(OSTIM2PRESCALER) */

/*  Miscellaneous definitions for MPC */
                                                /*  define USIU DWORD register */
#define OSSIUREG( address )     ( *(volatile OSDWORD*)( (address) ) )
                                                /*  define USIU WORD register */
#define OSSIUWORDREG( address ) ( *(volatile OSWORD *)( (address) ) )
                                                /*  define USIU BYTE register */
#define OSSIUBYTEREG( address ) ( *(volatile OSBYTE *)( (address) ) )

/*  Base addresses */
#define OSFLASH_BASE_ADDR     0x00000000ul
#define OSFLASH_SIZE          0x00200000ul

#define OSSRAM_BASE_ADDR      0x40000000ul
#define OSSRAM_SIZE           0x00010000ul

#define OSEXTMEM1_BASE_ADDR   0x20000000ul
#define OSEXTMEM1_SIZE        0x00080000ul

#define OSEXTMEM2_BASE_ADDR   0x3ff80000ul
#define OSEXTMEM2_SIZE        0x00080000ul

#define OSEXTBUSINT_BASE_ADDR 0xffff4000ul

#define OSINTC_BASE_ADDR      0xfff48000ul

#define OSETPU_BASE_ADDR      0xC3FC0000ul

#define OSCRP_BASE_ADDR       0xFFFEC000ul

#define OSBAM_BASE_ADDR       0xfffff000ul
#define OSBAM_SIZE            0x00001000ul

/****************** Interrupt Controller Addresses ******************/

#define OSINTC_MCR        OSSIUREG(OSINTC_BASE_ADDR)        /* Module Configuration Register */
#define OSINTC_TST        OSSIUREG(OSINTC_BASE_ADDR + 0x04u)/* Test Register */

#define OSINTC_OFFSET 0u

#define OSINTC_CPR        OSSIUREG(OSINTC_BASE_ADDR + 0x08u + OSINTC_OFFSET) /* Current Priority Register */
#define OSINTC_IACKR      OSSIUREG(OSINTC_BASE_ADDR + 0x10u + OSINTC_OFFSET) /* Interrupt Acknowledge Register */
#define OSINTC_EOIR       OSSIUREG(OSINTC_BASE_ADDR + 0x18u + OSINTC_OFFSET) /* End of Interrupt Register */

#define OSINTC_SSCIR0_3   OSSIUREG(OSINTC_BASE_ADDR + 0x20u) /* Software Set/Clear Interrupt Register 0-3 */
#define OSINTC_SSCIR4_7   OSSIUREG(OSINTC_BASE_ADDR + 0x24u) /* Software Set/Clear Interrupt Register 4-7 */

#define OSINT_PSR         (OSINTC_BASE_ADDR + 0x40u)         /* Priority Select Registers Base Address */
#define OSINT_PSRX(arg1)  OSSIUREG(OSINT_PSR + (arg1 >> 2u)*4u) /* Byte address of INT_PSR x */

#define OSSET_INT_PSRX(sint, prio) OSINT_PSRX(sint) |= (prio << ((3u - (sint - (sint >> 2u)*4u))*8u))
/* Clear current prio for sint input */
#define OSCLEAR_INT_PSRX(sint)     OSINT_PSRX(sint) &= ~(0xfu << ((3u - (sint - (sint >> 2u)*4u))*8u))

#define OSINTC_MCR_HVEN            0x00000001ul /* Hardware vector mode */
#define OSINTC_MCR_VTES            0x00000020ul /* Vector Table Entry Size = 8 */
#define OS2INTC_MCR_HVEN           0x00000100ul /* Hardware vector mode for processor 1 (second core) */
#define OS2INTC_MCR_VTES           0x00000200ul /* Vector Table Entry Size for processor 1 (second core) */

#if defined(OSMPC5644A) || defined(OSMPC5674F)
#define OSMPU_BASE 0xFFF10000ul
#endif

/* MPU_CESR register */
#define OSMPU_CESR              OSSIUREG(OSMPU_BASE)         /* MPU control/error status register */

/* MPU_CESR register bit masks */
#define OSMPU_CESR_VLD          0x1ul                        /* This bit provides a global enable/disable for the MPU */
#define OSMPU_CESR_SPERR        0xff000000ul                 /* mask for the SPERR bits */

#define OSMPU_CESR_SPERR_S0     0x80000000ul
#define OSMPU_CESR_SPERR_S1     0x40000000ul
#define OSMPU_CESR_SPERR_S2     0x20000000ul 

/* MPU_EARn/MPU_EDRn registers */
#define OSMPU_EAR0              OSSIUREG(OSMPU_BASE + 0x10ul)  /* MPU Error Address Register, Slave Port 0 */
#define OSMPU_EDR0              OSSIUREG(OSMPU_BASE + 0x14ul)  /* MPU Error Detail Register, Slave Port 0 */
#define OSMPU_EAR1              OSSIUREG(OSMPU_BASE + 0x18ul)  /* MPU Error Address Register, Slave Port 1 */
#define OSMPU_EDR1              OSSIUREG(OSMPU_BASE + 0x1cul)  /* MPU Error Detail Register, Slave Port 1 */
#define OSMPU_EAR2              OSSIUREG(OSMPU_BASE + 0x20ul)  /* MPU Error Address Register, Slave Port 2 */
#define OSMPU_EDR2              OSSIUREG(OSMPU_BASE + 0x24ul)  /* MPU Error Detail Register, Slave Port 2 */

/* MPU_EDRn bit masks */
#define OSMPU_EDR_ERW           0x1ul                        /* Error Read/Write. 0 - read access, 1 - write access */
#define OSMPU_EDR_EACD          0xffff0000ul                 /* Error Access Control Detail. */
#define OSMPU_EDR_EATTR         0xeul                        /* Error Attributes. This 3-bit read-only field records attribute information 
                                                                about the faulting reference. The supported encodings are defined as:
                                                                000 User mode, instruction access
                                                                001 User mode, data access
                                                                010 Supervisor mode, instruction access
                                                                011 Supervisor mode, data access */

/* MPU Region Descriptor num (0..15), word (0..3) */
#define OSMPU_RGD(num,word)     OSSIUREG(OSMPU_BASE + 0x400ul + (num)*0x10ul + (word)*4ul)

/* MPU Region Descriptor word 3: This bit signals the region descriptor is valid. */
#define OSMPU_RGD_W3_VLD          0x1ul                       

/* Master Supervisor mode (sm) access bit field */
#define OSMPU_SM_RWX 0x0ul  
#define OSMPU_SM_RX  0x1ul  
#define OSMPU_SM_RW  0x2ul  
#define OSMPU_SM_UM  0x3ul  

/* Master User mode (um) access bits */
#define OSMPU_UM_R   0x4ul  
#define OSMPU_UM_W   0x2ul  
#define OSMPU_UM_X   0x1ul  
#define OSMPU_UM_RWX (OSMPU_UM_R | OSMPU_UM_W | OSMPU_UM_X)
#define OSMPU_UM_RW  (OSMPU_UM_R | OSMPU_UM_W)
#define OSMPU_UM_RX  (OSMPU_UM_R | OSMPU_UM_X)

/* Master PID Enable */
#define OSMPU_PE_ON  0x1ul
#define OSMPU_PE_OFF 0x0ul

/* Mask for Master ID 0..3 rights */
#define OSMPU_RGD_W2_M0(mpe,sm,um)  (((mpe)<<5ul)|((sm)<<3ul)|(um))              /* Word 2: Bus Master ID 0 rights */
#define OSMPU_RGD_W2_M1(mpe,sm,um)  (((mpe)<<11ul)|((sm)<<9ul)|((um)<<6ul))      /* Word 2: Bus Master ID 1 rights */
#define OSMPU_RGD_W2_M2(mpe,sm,um)  (((mpe)<<17ul)|((sm)<<15ul)|((um)<<12ul))    /* Word 2: Bus Master ID 2 rights */
#define OSMPU_RGD_W2_M3(mpe,sm,um)  (((mpe)<<23ul)|((sm)<<21ul)|((um)<<18ul))    /* Word 2: Bus Master ID 3 rights */

/* Master M4 rights */
#define OSMPU_RGD_W2_M4E_R   0x2ul
#define OSMPU_RGD_W2_M4E_W   0x1ul
#define OSMPU_RGD_W2_M4(m4)  ((m4)<<24ul)  /* Word 2: Bus Master ID 4 rigths */

#if defined(OSMPU_NO_OTHERMASTERS)
/* Make masters 1,2 and 3 without any rights */
#define OSMPU_RGD_W2_M123()                                     \
    (OSMPU_RGD_W2_M1( OSMPU_PE_OFF, OSMPU_SM_UM, 0 ) |          \
     OSMPU_RGD_W2_M2( OSMPU_PE_OFF, OSMPU_SM_UM, 0 ) |          \
     OSMPU_RGD_W2_M3( OSMPU_PE_OFF, OSMPU_SM_UM, 0 ))

#else
/* Make masters 1,2 and 3 with RWX rights in system mode 
   Note: practically this macro returns 0 */
#define OSMPU_RGD_W2_M123()                           \
    (OSMPU_RGD_W2_M1( OSMPU_PE_OFF, 0, 0 ) |          \
     OSMPU_RGD_W2_M2( OSMPU_PE_OFF, 0, 0 ) |          \
     OSMPU_RGD_W2_M3( OSMPU_PE_OFF, 0, 0 ))
#endif

/* MPU Region Descriptor Alternate Access Control num (0..15) */
#define OSMPU_RGDAAC(num)       OSSIUREG(OSMPU_BASE + 0x800ul + (num)*4ul)

/* MPU region descriptor words */
#define OSMPU_RGD_WORD0 0u
#define OSMPU_RGD_WORD1 1u
#define OSMPU_RGD_WORD2 2u
#define OSMPU_RGD_WORD3 3u
/*********************** Specific definitions for timers ***********************/

#if defined(OSHWCOUNTER)
#if defined(OSMPC5634M) || defined(OSMPC5644A) ||  defined(OSMPC5674F)
typedef OSDWORD OSHWTickType;   /* eMIOS 24bits and STM */
#endif
#endif /* defined(OSHWCOUNTER) */

#if defined(OSMPC5644A) || defined(OSMPC5634M) || defined(OSMPC5674F)
#if OSNHWCTRS == 2
#if defined(OSTIMSTM) && defined(OSTIM2STM)
#define OSCTRBITS(num) (num)
#else
#if defined(OSTIMSTM)
#define OSCTRBITS(num) ((ctrInd != 0) ? (OSDWORD)(0x00FFFFFFul & (num)) : (num))/* 24 bit eMIOS counter or */
#elif defined(OSTIM2STM)                                                        /* 32 bit STM counter */
#define OSCTRBITS(num) ((ctrInd == 0) ? (OSDWORD)(0x00FFFFFFul & (num)) : (num))
#else
#define OSCTRBITS(num) (OSDWORD)(0x00FFFFFFul & (num))      /* 24 bit eMIOS counter */
#endif /* defined(OSTIMSTM) */
#endif /* defined(OSTIMSTM) && defined(OSTIM2STM) */
#elif OSNHWCTRS == 1
#if defined(OSTIMeMIOS) || defined(OSTIMeMIOS1)
#define OSCTRBITS(num) (OSDWORD)(0x00FFFFFFul & (num))      /* 24 bit eMIOS counter */
#else
#define OSCTRBITS(num) (num)                                /* 32 bit STM counter */
#endif /* defined(OSTIMeMIOS) || defined(OSTIM2eMIOS) */
#endif /* OSNHWCTRS == 2 */
#endif /* defined(OSMPC5644A) || defined(OSMPC5634M) || defined(OSMPC5674F) */

#if defined(OSMPC5634M)
#define OSTIMERDEC
#define OSTIMERFIT
#define OSTIMEReMIOS
#define OSTIMERPIT
#define OSTIMERPIT_RTI
#define OSTIMERSTM
#define OSTIMPIT_TYPE2
#define OSTIMPIT_RTI_TYPE2
#define OSeMIOSBASE     0xC3FA0000ul                 /* eMIOS base address */
#define OSPITBASE       0xC3FF0000ul                 /* PIT_RTI base address */
#define OSPITRTIBASE    0xC3FF0000ul                 /* PIT_RTI base address */
#define OSSTMBASE       0xFFF3C000ul                 /* STM base address */
#endif
#if defined(OSMPC5644A)
#define OSTIMERDEC
#define OSTIMERFIT
#define OSTIMEReMIOS
#define OSTIMERPIT
#define OSTIMERPIT_RTI
#define OSTIMERSTM
#define OSTIMPIT_TYPE2
#define OSTIMPIT_RTI_TYPE2
#define OSeMIOSBASE     0xC3FA0000ul                 /* eMIOS base address */
#define OSPITBASE       0xC3FF0000ul                 /* PIT base address */
#define OSPITRTIBASE    0xC3FF0000ul                 /* PIT_RTI base address */
#define OSSTMBASE       0xFFF3C000ul                 /* STM base address */
#endif
#if defined(OSMPC5674F)
#define OSTIMERDEC
#define OSTIMERFIT
#define OSTIMEReMIOS
#define OSTIMERPIT
#define OSTIMERPIT_RTI
#define OSTIMERSTM
#define OSTIMPIT_TYPE2
#define OSTIMPIT_RTI_TYPE2
#define OSeMIOSBASE     0xC3FA0000ul                 /* eMIOS base address */
#define OSPITBASE       0xC3FF0000ul                 /* PIT base address */
#define OSPITRTIBASE    0xC3FF0000ul                 /* PIT_RTI base address */
#define OSSTMBASE       0xFFF3C000ul                 /* STM base address */
#endif

#define OSTIMeMIOSSAOC  0x03u                       /* SAOC Mode */
#define OSTIMeMIOSMC    0x10u                       /* MC Mode */
#define OSTIMeMIOSMCB   0x50u                       /* MCB Mode(use when MC is absent) */
#define OSeMIOSHWMODE   OSTIMeMIOSSAOC              /* SAOC mode is used for all HW eMIOS system timers */

#if defined(OSMPC5644A)
#define OSeMIOSSWMODE   OSTIMeMIOSMCB
#endif
#if defined(OSMPC5634M)
#define OSeMIOSSWMODE   OSTIMeMIOSMCB
#endif
#if defined(OSMPC5674F)
#define OSeMIOSSWMODE   OSTIMeMIOSMC
#endif


/* Peripheral memory regions data */


#if defined(OSMPC5634M)
#define OSBRIDGE1ADDR 0xC3F00000ul
#define OSBRIDGE1SIZE 0x000E0000ul
#define OSBRIDGE2ADDR 0xFFF00000ul
#define OSBRIDGE2SIZE 0x00100000ul
#endif
#if defined(OSMPC5644A)
#define OSBRIDGE1ADDR 0xC0000000ul
#define OSBRIDGE1SIZE 0x40000000ul
#endif
#if defined(OSMPC5674F)
#define OSBRIDGE1ADDR 0xC3F00000ul
#define OSBRIDGE1SIZE 0x00100000ul
#define OSBRIDGE2ADDR 0xFFF00000ul
#define OSBRIDGE2SIZE 0x00100000ul
#endif


#endif /* OSTARGET_H */
