#ifndef OSTIMER_H
#define OSTIMER_H
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
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/inc/ostimer.h,v $
* Author:       $Author: b00355 $
* Locker:       $Locker:  $
* State:        $State: Exp $
* Revision:     $Revision: 1.5 $
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  Timer hardware registers definitions
*               and macros to handle timer's interrupts
*
* Notes:        included only if OSSYSTIMER(OS2SYSTIMER) or OSTPTIMSTM is defined
*
******************************************************************************/

/************************* Timer HW definitions ******************************/
/*********************************************  eMIOS(eMIOS0) registers and bits   *****/
#define OSGTBE        0x10000000ul      /* global time base enable bit */
#define OSGPREN       0x04000000ul      /* global prescaler enable bit */
#define OSUCPREN      0x02000000ul      /* prescaler enable bit */
#define OSFEN         0x00020000ul      /* FLAG enable bit */
#define OSBSL         0x00000600ul      /* bus select bits: internal counter */
#define OSPREMASK     0x0C000000ul      /* channel prescaler mask */
#define OSGPREMASK    0x0000FF00ul      /* global prescaler mask */
#define OSFLAG        0x01u             /* FLAG bit */

#define OSMTSMCR      OSSIUREG(OSeMIOSBASE)                         /* Module Configuration register     */
#define OSMTSOUDIS    OSSIUREG(OSeMIOSBASE + 0x08u)                 /* Output Update Disable register    */
#define OSMTSA(n)     OSSIUREG(OSeMIOSBASE + (32u*(n)) + 32u)       /* "A" */
#define OSMTSB(n)     OSSIUREG(OSeMIOSBASE + (32u*(n)) + 36u)       /* "B" */
#define OSMTSCNT(n)   OSSIUREG(OSeMIOSBASE + (32u*(n)) + 40u)       /* Counter */
#define OSMTSC(n)     OSSIUREG(OSeMIOSBASE + (32u*(n)) + 44u)       /* Control */
#define OSMTSS(n)     OSSIUREG(OSeMIOSBASE + (32u*(n)) + 48u)       /* Status  */

#ifdef OSTIMEReMIOS1
/**********************************************  eMIOS1 registers    *****/
#define OSMTSMCR1     OSSIUREG(OSeMIOSBASE1)                        /* Module Configuration register   */
#define OSMTSOUDIS1   OSSIUREG(OSeMIOSBASE1 + 0x08u)                /* Output Update Disable register  */
#define OSMTSA1(n)    OSSIUREG(OSeMIOSBASE1 + (32u*(n)) + 32u)      /* "A" */
#define OSMTSB1(n)    OSSIUREG(OSeMIOSBASE1 + (32u*(n)) + 36u)      /* "B" */
#define OSMTSCNT1(n)  OSSIUREG(OSeMIOSBASE1 + (32u*(n)) + 40u)      /* Counter */
#define OSMTSC1(n)    OSSIUREG(OSeMIOSBASE1 + (32u*(n)) + 44u)      /* Control */
#define OSMTSS1(n)    OSSIUREG(OSeMIOSBASE1 + (32u*(n)) + 48u)      /* Status  */
#endif
#if defined(OSTIMPIT_TYPE1)
/**********************************************  PIT type1 registers    *****/
#define OSPITFLG       OSSIUREG(OSPITRTIBASE + 0x100u)                  /* PIT_RTI Interrupt Flags register */
#define OSPITINTEN     OSSIUREG(OSPITRTIBASE + 0x104u)                  /* PIT_RTI Interrupt Enable register */ 
#define OSPITINTSEL    OSSIUREG(OSPITRTIBASE + 0x108u)                  /* PIT Interrupt/DMA Select register */
#define OSPITEN        OSSIUREG(OSPITRTIBASE + 0x10Cu)                  /* PIT_RTI Timer Enable register */
#define OSPITCTRL      OSSIUREG(OSPITRTIBASE + 0x110u)                  /* PIT Control register */
#define OSTLVAL(n)     OSSIUREG(OSPITRTIBASE + 4u*(n))                  /* PIT Timer Load Value register */   
#define OSTVAL(n)      OSSIUREG(OSPITRTIBASE + 0x80u + 4u*(n))          /* PIT Current Timer Value register */
#endif
#if defined(OSTIMPIT_TYPE2) || defined(OSTIMPIT_TYPE3)
/**********************************************  PIT type2,3 registers  *****/
#define OSPITMCR       OSSIUREG(OSPITBASE)                              /* PIT Module Control Register */
#define OSLDVAL(n)     OSSIUREG(OSPITBASE + 0x100u + (16u*(n)) )        /* Timer Load Value Register */
#define OSCVAL(n)      OSSIUREG(OSPITBASE + 0x104u + (16u*(n)) )        /* Current Timer Value Register */
#define OSTCTRL(n)     OSSIUREG(OSPITBASE + 0x108u + (16u*(n)) )        /* Timer Control Register */
#define OSETFLG(n)     OSSIUREG(OSPITBASE + 0x10Cu + (16u*(n)) )        /* Timer Flag Register */
#endif
#if defined(OSTIMPIT_TYPE4)
/**********************************************  PIT type4 registers,the first channel number is 1 *****/
#define OSPITMCR       OSSIUREG(OSPITBASE)                              /* PIT Module Control Register */
#define OSLDVAL(n)     OSSIUREG(OSPITBASE + 0x100u + (16u*(n-1)) )      /* Timer Load Value Register */
#define OSCVAL(n)      OSSIUREG(OSPITBASE + 0x104u + (16u*(n-1)) )      /* Current Timer Value Register */
#define OSTCTRL(n)     OSSIUREG(OSPITBASE + 0x108u + (16u*(n-1)) )      /* Timer Control Register */
#define OSETFLG(n)     OSSIUREG(OSPITBASE + 0x10Cu + (16u*(n-1)) )      /* Timer Flag Register */
#endif
#if defined(OSTIMPIT_RTI_TYPE1)
/***********************************************  RTI1 registers         *****/
#define OSPITFLG_RTI    OSSIUREG(OSPITRTIBASE + 0x100u)                 /* PIT_RTI Interrupt Flags register */
#define OSPITINTEN_RTI  OSSIUREG(OSPITRTIBASE + 0x104u)                 /* PIT_RTI Interrupt Enable register */ 
#define OSPITEN_RTI     OSSIUREG(OSPITRTIBASE + 0x10Cu)                 /* PIT_RTI Timer Enable register */
#define OSTLVAL_RTI     OSSIUREG(OSPITRTIBASE)                          /* RTI Timer Load Value register */   
#define OSTVAL_RTI      OSSIUREG(OSPITRTIBASE + 0x80u)                  /* RTI Current Timer Value register */
#endif
#if defined(OSTIMPIT_RTI_TYPE2)
/***********************************************  RTI2 registers         *****/
#define OSPITMCR_RTI    OSSIUREG(OSPITRTIBASE)                          /* RTI Module Control Register */
#define OSLDVAL_RTI     OSSIUREG(OSPITRTIBASE + 0xF0u)                  /* Timer Load Value Register */
#define OSCVAL_RTI      OSSIUREG(OSPITRTIBASE + 0xF4u)                  /* Current Timer Value Register */
#define OSTCTRL_RTI     OSSIUREG(OSPITRTIBASE + 0xF8u)                  /* Timer Control Register */
#define OSETFLG_RTI     OSSIUREG(OSPITRTIBASE + 0xFCu)                  /* Timer Flag Register */
#endif
/************************************************  STM registers         *****/
#define OSSTM_CR        OSSIUREG(OSSTMBASE)                             /* STM Control Register */
#define OSSTM_CNT       OSSIUREG(OSSTMBASE + 0x04u)                     /* STM Counter Value */
#define OSSTM_CCR(n)    OSSIUREG(OSSTMBASE + 0x10u + 16u*(n))           /* STM Channel n Control Register */
#define OSSTM_CIR(n)    OSSIUREG(OSSTMBASE + 0x14u + 16u*(n))           /* STM Channel n Interrupt Register */
#define OSSTM_CMP(n)    OSSIUREG(OSSTMBASE + 0x18u + 16u*(n))           /* STM Channel n Compare Register */
#define OSSTMTENBIT     0x01u                                           /* timer enable bit */
#define OSSTMFLBIT      0x01u                                           /* channel interrupt flag */
#define OSSTMCENBIT     0x01u                                           /* channel enable bit */
#define OSSTMFREEZEBIT  0x02u                                           /* STM freeze bit */
/************************************************  DEC definitions         *****/
#define OSDECHID0_TBEN  0x00004000ul                /* Time base enable bit*/
#define OSTCR_DIE       0x04000000ul                /* Decrementer interrupt enable bit*/
#define OSTCR_ARE       0x00400000ul                /* Auto-reload enable bit*/
#define OSTSR_DIS       0x08000000ul                /* Decrementer interrupt status bit*/
#if defined(OSTIMDEC)
/*********************************************************  System DEC timer  *****/
/* DEC numbers of the Software setable interrupt for the System timer */
/* INT number = 7 */
#define OSSYSSOFTINVOKE 0x2u
#define OSSYSSOFTCLEAR  0x1u

#define OSSysTimRun()         OSSETHID0( OSGETHID0() | OSDECHID0_TBEN);         /* Time base Enable */
#define OSSysTimClearFlag()   OSINTC_SSCIR4_7 = OSSYSSOFTCLEAR
#define OSSysTimDisableInt()    OsSetTCR(OsGetTCR() & ~( OSTCR_DIE ))
#define OSSysTimEnableInt()     OsSetTCR(OsGetTCR() | (OSTCR_DIE | OSTCR_ARE )) /* Enable DEC Interrupt and Auto-reload */
#define OSSysTimStop();
#endif
/********************************************************   System FIT timer  *****/
#define OSFITHID0_TBEN  0x00004000ul                /* Time base enable bit*/
#define OSTCR_FP        0x03000000ul                /* Fixed interval timer period mask*/
#define OSTCR_FIE       0x00800000ul                /* Fixed interval interrupt enable bit*/
#define OSTCR_FPEXT     0x0001E000ul                /* Fixed-interval timer period extension mask*/
#define OSTSR_FIS       0x04000000ul                /* Fixed-interval interrupt status bit*/
#define OSTBMAXVALUE    0xFFFFFFFFul                /* Max value for Time Base used in the system */

#if defined(OSTIMFIT)
/* FIT number of the Software setable interrupt for the System timer */
/* INT number = 6 */
#define OSSYSSOFTINVOKE 0x0200u
#define OSSYSSOFTCLEAR  0x0100u

#define OSSysTimRun()         OSSETHID0(OSGETHID0() | OSFITHID0_TBEN);  /* Time base Enable */
#define OSSysTimClearFlag()   OSINTC_SSCIR4_7 = OSSYSSOFTCLEAR
#define OSSysTimDisableInt()  OsSetTCR(OsGetTCR() & ~( OSTCR_FIE ))
#define OSSysTimEnableInt()   OsSetTCR(OsGetTCR() | (OSTCR_FIE ))      /* Enable FIT Interrupt */
#define OSSysTimStop();
#endif
/************* System Timer **************/

#if defined(OSTIMeMIOS) || defined(OSTIMeMIOS1) || defined(OS2TIMeMIOS)
/*********************************************************  System eMIOS timer  *****/
#if defined(OSSYSTIMFREEZE) || defined(OS2SYSTIMFREEZE)
#define OSCHFREEZE      0x80000000u                     /* Doze Enable bit */
#define OSFRZ           0x20000000u                     /* Freeze bit */
#else
#define OSCHFREEZE      0u
#define OSFRZ           0u
#endif

#define OSTIMCHBIT      (1u << OSTIMCHAN)               /* channel bit */

#if defined(OSTIMeMIOS)        
#define OSTIMTCNT       OSMTSCNT( OSTIMCHAN )           /* counter */
#define OSTIMCHOC       OSMTSA( OSTIMCHAN )             /* base of the UC */
#define OSSTREG         OSMTSS( OSTIMCHAN )             /* status register */
#define OSMTSCREG       OSMTSC( OSTIMCHAN )             /* control register */
#define OSMTSSREG       OSMTSS( OSTIMCHAN )             /* status register */
#define OSMTSMCRREG     OSMTSMCR                        /* module conf.register */
#define OSMTSOUDISREG   OSMTSOUDIS                      /* output update disable register  */
#if defined(OSeMIOSGLOBALPRESCALER)
#define OSeMIOSGLBL     OSeMIOSGLOBALPRESCALER          /* global prescaler value */
#endif
#elif defined(OSTIMeMIOS1)
#define OSTIMTCNT       OSMTSCNT1( OSTIMCHAN )          /* counter */
#define OSTIMCHOC       OSMTSA1( OSTIMCHAN )            /* base of the UC */
#define OSSTREG         OSMTSS1( OSTIMCHAN )            /* status register */
#define OSMTSCREG       OSMTSC1( OSTIMCHAN )            /* control register */
#define OSMTSSREG       OSMTSS1( OSTIMCHAN )            /* status register */
#define OSMTSMCRREG     OSMTSMCR1                       /* module conf.register */
#define OSMTSOUDISREG   OSMTSOUDIS1                     /* output update disable register  */
#if defined(OSeMIOS1GLOBALPRESCALER)
#define OSeMIOSGLBL     OSeMIOS1GLOBALPRESCALER         /* global prescaler value */
#endif
#endif /* defined(OSTIMeMIOS1) */

#define OSTimeMIOSHW (OSFRZ | OSGTBE)               /* global freeze,timebase and bus select */

#if defined(OSeMIOSGLOBALPRESCALER) || defined(OSeMIOS1GLOBALPRESCALER)
#define OSTimGlobalPSR()  OSMTSMCRREG &= ~OSGPREMASK; OSMTSMCRREG |= (OSeMIOSGLBL << 8); OSMTSMCRREG |= OSGPREN
#else
#define OSTimGlobalPSR()  /* nothing to do */
#endif
#if defined(OSTIMPRESCALER)                         /* global prescaler,presettings and update enable  */
#if defined(OSeMIOSGLOBALPRESCALER) || defined(OSeMIOS1GLOBALPRESCALER)
#define OSTimHWprepare()  OSTimGlobalPSR(); OSMTSMCRREG |= OSTimeMIOSHW; OSMTSOUDISREG &= ~OSTIMCHBIT
#else
#define OSTimHWprepare()  OSMTSMCRREG = OSTimeMIOSHW; OSMTSOUDISREG &= ~OSTIMCHBIT
#endif
#else
#define OSTimHWprepare() OSTimGlobalPSR()
#endif  /* defined(OSTIMPRESCALER) */

#define OSSysTimRun()   OSMTSCREG |= OSUCPREN       /* set UCPREN (presc.enable) */
#define OSSysTimStop()  OSMTSCREG &= ~OSUCPREN      /* disable timer channel        */
#define OSSysTimClearFlag()  OSSTREG = OSFLAG       /* clear interrupt request flag */
#define OSSysTimEnableInt()  OSMTSCREG |= OSFEN     /* enable timer interrupts (FEN = 1) */
#define OSSysTimDisableInt() OSMTSCREG &= ~OSFEN    /* disable timer interrupts (FEN = 0)*/
#endif /* defined(OSTIMeMIOS) || defined(OSTIMeMIOS1) */

#if defined(OSTIMPIT) || defined(OS2TIMPIT)
/*********************************************************  System PIT timer  *****/
#if defined(OSTIMPIT_TYPE1)                     /* PIT module type 1 */

#define OSTIMTCNT       OSTVAL( OSTIMCHAN )     /* counter value */
#define OSTIMCHOC       OSTLVAL( OSTIMCHAN )    /* timer load value */

#define OSTIMCHBIT      ( 1u << OSTIMCHAN )     /* channel bit */
 
#define OSTimHWprepare()    OSPITCTRL = 0u; OSPITINTSEL |= OSTIMCHBIT

#define OSSysTimRun()       OSPITEN |= OSTIMCHBIT       /* active timer ( PENn = 1) */
#define OSSysTimStop()      OSPITEN &= ~OSTIMCHBIT      /* disable timer ( PENn = 0) */
#define OSSysTimClearFlag()  OSPITFLG = OSTIMCHBIT      /* clear interrupt flag (TIFn = 1) */
#define OSSysTimEnableInt()  OSPITINTEN |= OSTIMCHBIT   /* enable timer interrupts (TIEn = 1) */
#define OSSysTimDisableInt() OSPITINTEN &= ~OSTIMCHBIT  /* disable timer interrupts (TIEn = 0) */
#endif

#if defined(OSTIMPIT_TYPE2)                 /* PIT module type 2 */

#if defined(OSSYSTIMFREEZE)
#define OSTIMFRZBIT     0x01u               /* freeze bit */
#else
#define OSTIMFRZBIT     0x00u
#endif
#define OSTIMTENBIT     0x01u               /* timer enable bit */
#define OSTIMTIFBIT     0x01u               /* time interrupt flag bit */
#define OSTIMTIEBIT     0x02u               /* timer interrupt enable bit */
#define OSTIMMDIS_RTI   0x04u               /* RTI disable clock bit */
                                            
#define OSTIMTCNT   OSCVAL( OSTIMCHAN )     /* counter value */
#define OSTIMCHOC   OSLDVAL( OSTIMCHAN )    /* timer load value */

#define OSTimHWprepare()    OSPITMCR = OSTIMMDIS_RTI | OSTIMFRZBIT

#endif /* defined(OSTIMPIT_TYPE2) */

#if defined(OSTIMPIT_TYPE3) || defined(OSTIMPIT_TYPE4)  /* PIT module type3,4 */

#if defined(OSSYSTIMFREEZE)
#define OSTIMFRZBIT     0x01u               /* freeze bit */
#else
#define OSTIMFRZBIT     0x00u
#endif
#define OSTIMTENBIT     0x01u               /* timer enable bit */
#define OSTIMTIFBIT     0x01u               /* time interrupt flag bit */
#define OSTIMTIEBIT     0x02u               /* timer interrupt enable bit */

#define OSTIMTCNT   OSCVAL( OSTIMCHAN )     /* counter value */
#define OSTIMCHOC   OSLDVAL( OSTIMCHAN )    /* timer load value */

#if defined(OSSYSTIMFREEZE)
#define OSTimHWprepare()    OSPITMCR = OSTIMFRZBIT
#else
#define OSTimHWprepare()    OSPITMCR = 0u
#endif
#endif /* defined(OSTIMPIT_TYPE3) || defined(OSTIMPIT_TYPE4) */

#if defined(OSTIMPIT_TYPE2) || defined(OSTIMPIT_TYPE3) || defined(OSTIMPIT_TYPE4)
#define OSSysTimRun()       OSTCTRL( OSTIMCHAN ) = OSTIMTENBIT       /* timer enable ( TENn = 1) */
#define OSSysTimStop()      OSTCTRL( OSTIMCHAN ) &= ~OSTIMTENBIT     /* timer disable ( TENn = 0) */
#define OSSysTimClearFlag()  OSETFLG( OSTIMCHAN ) = OSTIMTIFBIT      /* clear interrupt flag (TIFn = 1) */
#define OSSysTimEnableInt()  OSTCTRL( OSTIMCHAN ) |= OSTIMTIEBIT     /* enable timer interrupts (TIEn = 1) */
#define OSSysTimDisableInt() OSTCTRL( OSTIMCHAN ) &= ~OSTIMTIEBIT    /* disable timer interrupts (TIEn = 0) */
#endif
#endif /* defined(OSTIMPIT) || defined(OS2TIMPIT) */

#if defined(OSTIMPIT_RTI)
/*********************************************************  System RTI timer  *****/
#define OSTIMTENBIT     0x01u           /* timer enable bit */
#define OSTIMTIFBIT     0x01u           /* time interrupt flag bit */

#if defined(OSTIMPIT_RTI_TYPE1)         /* PIT_RTI type 1 */

#define OSTIMTCNT       OSTVAL_RTI      /* counter value */
#define OSTIMCHOC       OSTLVAL_RTI     /* timer load value */

#define OSTIMTIEBIT     0x01u           /* timer interrupt enable bit */

#define OSTimHWprepare()

#define OSSysTimRun()    OSPITEN_RTI |= OSTIMTENBIT             /* timer enable ( PEN0 = 1) */
#define OSSysTimClearFlag()  OSPITFLG_RTI = OSTIMTIFBIT         /* clear interrupt flag (TIF0 = 1) */
#define OSSysTimEnableInt()  OSPITINTEN_RTI |= OSTIMTIEBIT      /* enable timer interrupts (TIE0 = 1) */
#define OSSysTimDisableInt() OSPITINTEN_RTI &= ~OSTIMTIEBIT     /* disable timer interrupts (TIE0 = 0) */
#endif

#if defined(OSTIMPIT_RTI_TYPE2)             /* PIT_RTI type 2 */

#if defined(OSSYSTIMFREEZE)
#define OSTIMFRZBIT     0x01u               /* freeze bit */
#else
#define OSTIMFRZBIT     0x00u
#endif

#define OSTIMTIEBIT     0x02u               /* timer interrupt enable bit */
#define OSTIMMDIS       0x02u               /* PIT disable clock bit */

#define OSTIMTCNT       OSCVAL_RTI          /* counter value */
#define OSTIMCHOC       OSLDVAL_RTI         /* timer load value */

#define OSTimHWprepare()    OSPITMCR_RTI = OSTIMMDIS | OSTIMFRZBIT

#define OSSysTimRun()       OSTCTRL_RTI = OSTIMTENBIT       /* timer enable ( TENn = 1) */
#define OSSysTimStop()      OSTCTRL_RTI &= ~OSTIMTENBIT     /* timer disable ( TENn = 0) */
#define OSSysTimClearFlag()  OSETFLG_RTI = OSTIMTIFBIT      /* clear interrupt flag (TIFn = 1) */
#define OSSysTimEnableInt()  OSTCTRL_RTI |= OSTIMTIEBIT     /* enable timer interrupts (TIEn = 1) */
#define OSSysTimDisableInt() OSTCTRL_RTI &= ~OSTIMTIEBIT    /* disable timer interrupts (TIEn = 0) */
#endif /* defined(OSTIMPIT_RTI_TYPE2) */
#endif /* defined(OSTIMPIT_RTI) */

#if defined(OSTIMSTM) || defined(OS2TIMSTM)
/*********************************************************  System STM timer  *****/
#define OSTIMTENBIT     OSSTMTENBIT             /* timer enable bit */     
#define OSTIMFLBIT      OSSTMFLBIT              /* channel interrupt flag */     
#define OSTIMCENBIT     OSSTMCENBIT             /* channel enable bit */

#if defined(OSTIMSTM)
#define OSTIMTCNT       OSSTM_CNT               /* counter value */
#define OSTIMCHOC       OSSTM_CMP(OSTIMCHAN)    /* timer compare value */
#define OSSTREG         OSSTM_CIR(OSTIMCHAN)    /* status register */
#define OSSTARTVAL      0u                      /* start counter value */ 
#endif
#if defined(OSSYSTIMFREEZE) || defined(OS2SYSTIMFREEZE)
#define OSTIMFRZBIT     OSSTMFREEZEBIT
#else
#define OSTIMFRZBIT     0u
#endif

#if defined(OSTIMPRESCALER)
                            /* set prescaler,"stopped in debug mode" and timer enable bit */
#define OSTimHWprepare()     OSSTM_CR = (OSTIMPRESCALER << 8) | OSTIMFRZBIT | OSTIMTENBIT
#else
#define OSTimHWprepare()    /* nothing to do */
#endif
#define OSSysTimRun()                                              /* running by OSSysTimEnableInt() */
#define OSSysTimStop()       OSSTM_CCR(OSTIMCHAN) = 0u             /* the channel is disabled (CENn = 0) */
#define OSSysTimClearFlag()  OSSTM_CIR(OSTIMCHAN) = OSTIMFLBIT     /* clear interrupt flag (CIFn = 1) */
#define OSSysTimEnableInt()  OSSTM_CCR(OSTIMCHAN) = OSTIMCENBIT    /* enable timer interrupts (CENn = 1) */
#define OSSysTimDisableInt() OSSTM_CCR(OSTIMCHAN) = 0u             /* disable timer interrupts (CENn = 0) */
#endif /* defined(OSTIMSTM) || defined(OS2TIMSTM) */

/***************************************************************************
 * Macro:    OSSysTimSetHW
 *
 * Description: System timer's HW initialization;
 *              mode,control bits and prescaler are set here;
 *
 * Notes:
 *          for DEC:
 *              set MODULO value;      
 *              time base enable;
 *          for FIT:
 *              set FIT interval period;
 *              time base enable;
 *          for eMIOS:
 *              set GPIO mode to get CNT = 0(optional) and mode;
 *              set output enable bit;
 *              BSL  = b11 - int.counter;
 *              MODE = 0x10(0x050) - MC(MCB) mode for SW counters,MODULO value,
 *              MODE = 0x03(0x06) - SAOC mode for HW counters;
 *              prescaler control bits and value;
 *              FREEZE bits if it needs;
 *
 *          for eTimer:
 *              set Count mode(CNTMODE = 1 );
 *              prescaler control bits and value;
 *              set re-initialize mode and load(MODULO) value for SW counters;
 *              clear counter register;
 *
 *          for STM:
 *              MODULO value;
 *              FREEZE bits if it needs;
 *              clear counter register;
 *
 *          for other timers:
 *              MODULO value only;
 *              FREEZE bits if it needs;
 *
 **************************************************************************/
#if defined(OSTIMDEC)
OSINLINE void OSSysTimSetHW(void)
{
    OSSETHID0( OSGETHID0() & ~(OSDECHID0_TBEN));    /* Time base disable */
    OsSetDECAR(OSTIMMODULO);                        /* Write modulo value into the DEC Auto-reload register */
    OSDecTimerSet(OSTIMMODULO);
    OSSysTimRun();                                  /* start system timer  */
}
#endif 

#if defined(OSTIMFIT)
OSINLINE void OSSysTimSetHW(void)
{
    OSSETHID0( OSGETHID0() & ~(OSFITHID0_TBEN));    /* Time base disable */
    OsSetTCR(OsGetTCR() & ~(OSTCR_FIE | OSTCR_FP | OSTCR_FPEXT) );  /* Clear all FIT bits */

#if defined(OSTIMMODULO)
    OsSetTCR(OsGetTCR() | ((OSFITP << 24) | (OSFITPEXT << 13)) );   /* Set Fixed interval timer period */
#endif
    OSSysTimRun();                  /* start system timer  */
}
#endif /* defined(OSTIMFIT) */

#if defined(OSTIMeMIOS) || defined(OSTIMeMIOS1)
OSINLINE void OSSysTimSetHW(void)
{
    OSTimHWprepare();                   /* eMIOS general settings */

#if defined(OSTIMMODULO)                /* eMIOS channel settings: */
    OSTIMCHOC = OSTIMMODULO;            /* set matching value */
#endif

#if defined(OSTIMPRESCALER)
    OSMTSCREG = OSCHFREEZE | OSBSL | (OSTIMPRESCALER << 26); /* set freeze and counter source and presc.value */

#if (OSNSYSHWCTRS > 0)
    OSMTSCREG |= OSeMIOSHWMODE;         /* set HW timer mode */
#else
    OSMTSCREG |= OSeMIOSSWMODE;         /* set SW timer mode */
#endif
#endif /* defined(OSTIMPRESCALER) */

#if defined(OSTIMPRESCALER)
    OSSysTimRun();                      /* start system timer  */
#endif
}
#endif /* defined(OSTIMeMIOS) || defined(OSTIMeMIOS1) */

#if defined(OSTIMPIT)
OSINLINE void OSSysTimSetHW(void)
{
#if defined(OSTIMMODULO)
    OSTIMCHOC = OSTIMMODULO;
#endif
    OSTimHWprepare();                   /* PIT settings */

    OSSysTimRun();                      /* start system timer  */
}
#endif /* OSTIMPIT */

#if defined(OSTIMPIT_RTI)
OSINLINE void OSSysTimSetHW(void)
{
#if defined(OSTIMMODULO)
    OSTIMCHOC = OSTIMMODULO;
#endif
    OSTimHWprepare();                   /* RTI settings */

    OSSysTimRun();                      /* start system timer  */
}
#endif /* OSTIMPIT_RTI */

#if defined(OSTIMSTM)
OSINLINE void OSSysTimSetHW(void)
{
#if defined(OSTIMPRESCALER)
    OSTIMTCNT = OSSTARTVAL;             /* clear counter register */
#endif
#if defined(OSTIMMODULO)
    OSTIMCHOC = OSTIMMODULO;
#endif
    OSTimHWprepare();                   /* STM settings */

    OSSysTimRun();                      /* start system timer  */
}
#endif /* OSTIMSTM */


/************* Second Timer **************/

#if defined(OSSECONDTIMER) || defined(OS2SECONDTIMER)

#if defined(OSTIM2DEC)
/*********************************************************  Second DEC timer  *****/
/* DEC numbers of the Software setable interrupt for the Second timer */
/* INT number = 7 */
#define OSSECSOFTINVOKE 0x2u
#define OSSECSOFTCLEAR  0x1u

#define OSSecondRun()        OSSETHID0( OSGETHID0() | OSDECHID0_TBEN);      /* Time base Enable */
#define OSSecondClearFlag()  OSINTC_SSCIR4_7 = OSSECSOFTCLEAR
#define OSSecondDisableInt()    OsSetTCR(OsGetTCR() & ~( OSTCR_DIE ))
#define OSSecondEnableInt()     OsSetTCR(OsGetTCR() | (OSTCR_DIE | OSTCR_ARE))  /* Enable DEC Interrupt and Auto-reload */
#define OSSecondStop()
#endif

#if defined(OSTIM2FIT)
/*********************************************************  Second FIT timer  *****/
/* FIT numbers of the Software setable interrupt for the Second timer */
/* INT number = 6 */
#define OSSECSOFTINVOKE 0x0200u
#define OSSECSOFTCLEAR  0x0100u

#define OSSecondRun()        OSSETHID0( OSGETHID0() | OSFITHID0_TBEN);   /* Time base Enable */
#define OSSecondClearFlag()  OSINTC_SSCIR4_7 = OSSECSOFTCLEAR
#define OSSecondDisableInt()    OsSetTCR(OsGetTCR() & ~( OSTCR_FIE ))
#define OSSecondEnableInt()     OsSetTCR(OsGetTCR() | (OSTCR_FIE ))      /* Enable FIT Interrupt */
#define OSSecondStop()
#endif

#if defined(OSTIM2eMIOS) || defined(OSTIM2eMIOS1) || defined(OS2TIM2eMIOS)
/*********************************************************  Second eMIOS timer  *****/
#if defined(OSSECONDFREEZE) || defined(OS2SECONDFREEZE) 
#define OSCH2FREEZE   0x80000000ul                  /* Doze Enable bit */  
#define OSFRZ2        0x20000000ul                  /* Freeze bit */
#else
#define OSCH2FREEZE   0u
#define OSFRZ2        0u
#endif

#define OSTIM2CHBIT     (1u << OSTIM2CHAN)          /* channel bit */

#if defined(OSTIM2eMIOS)
#define OSTIM2TCNT      OSMTSCNT( OSTIM2CHAN )      /* counter */
#define OSTIM2CHOC      OSMTSA( OSTIM2CHAN )        /* base of the UC */
#define OSSTREG2        OSMTSS( OSTIM2CHAN )        /* status register */
#define OSMTSCREG2      OSMTSC( OSTIM2CHAN )        /* control register */
#define OSMTSSREG2      OSMTSS( OSTIM2CHAN )        /* status register */
#define OSMTSMCRREG2    OSMTSMCR                    /* module conf.register */
#define OSMTSOUDISREG2  OSMTSOUDIS                  /* output update disable register  */
#if defined(OSeMIOSGLOBALPRESCALER)
#define OSeMIOSGLBL2    OSeMIOSGLOBALPRESCALER      /* global prescaler value */
#endif
#elif defined(OSTIM2eMIOS1)
#define OSTIM2TCNT      OSMTSCNT1( OSTIM2CHAN )     /* counter */
#define OSTIM2CHOC      OSMTSA1( OSTIM2CHAN )       /* base of the UC */
#define OSSTREG2        OSMTSS1( OSTIM2CHAN )       /* status register */
#define OSMTSCREG2      OSMTSC1( OSTIM2CHAN )       /* control register */
#define OSMTSSREG2      OSMTSS1( OSTIM2CHAN )       /* status register */
#define OSMTSMCRREG2    OSMTSMCR1                   /* module conf.register */
#define OSMTSOUDISREG2  OSMTSOUDIS1                 /* output update disable register  */
#if defined(OSeMIOS1GLOBALPRESCALER)
#define OSeMIOSGLBL2    OSeMIOS1GLOBALPRESCALER     /* global prescaler value */
#endif
#endif /* defined(OSTIM2eMIOS1) */

#if( defined(OSTIMeMIOS1) && defined(OSTIM2eMIOS1) ) || ( defined(OSTIMeMIOS) && defined(OSTIM2eMIOS) ) || \
   ( defined(OS2TIMeMIOS) && defined(OS2TIM2eMIOS) )
/* if the 1st timer and the 2nd uses the same eMIOS HW block */

#if defined(OSTIM2eMIOS) || defined(OSTIM2eMIOS1)
#define OSTim2HWprepare()   /* nothing to do, done in System Timer         */
#endif

#else                       /* need to do full initialization of eMIOS HW   */

#if defined(OSTIM2eMIOS) || defined(OSTIM2eMIOS1)

#define OSTim2eMIOSHW (OSFRZ2 | OSGTBE) 

#if defined(OSeMIOSGLOBALPRESCALER) || defined(OSeMIOS1GLOBALPRESCALER)
#define OSTim2GlobalPSR()  OSMTSMCRREG2 &= ~OSGPREMASK; OSMTSMCRREG2 |= (OSeMIOSGLBL2 << 8); OSMTSMCRREG2 |= OSGPREN
#else
#define OSTim2GlobalPSR()       /* nothing to do */
#endif
#if defined(OSTIM2PRESCALER)                         /* global prescaler,presettings and update enable  */
#if defined(OSeMIOSGLOBALPRESCALER) || defined(OSeMIOS1GLOBALPRESCALER)
#define OSTim2HWprepare()  OSTim2GlobalPSR(); OSMTSMCRREG2 |= OSTim2eMIOSHW; OSMTSOUDISREG2 &= ~OSTIM2CHBIT
#else
#define OSTim2HWprepare()  OSMTSMCRREG2 = OSTim2eMIOSHW; OSMTSOUDISREG2 &= ~OSTIM2CHBIT
#endif
#else /* defined(OSTIMPRESCALER) */
#define OSTim2HWprepare() OSTim2GlobalPSR()
#endif /* defined(OSTIM2PRESCALER) */
#endif /* defined(OSTIM2eMIOS) || defined(OSTIM2eMIOS1) */
#endif /* ( defined(OSTIMeMIOS1) && defined(OSTIM2eMIOS1) ) || ( defined(OSTIMeMIOS) && defined(OSTIM2eMIOS) ) 
          ( defined(OS2TIMeMIOS) && defined(OS2TIM2eMIOS) ) */

#if defined(OSTIM2eMIOS) || defined(OSTIM2eMIOS1)
#define OSSecondRun()       OSMTSCREG2 |= OSUCPREN        /* set UCPREN (presc.enable)    */
#define OSSecondStop()      OSMTSCREG2 &= ~OSUCPREN       /* disable timer channel        */
#define OSSecondClearFlag()  OSSTREG2 = OSFLAG            /* clear interrupt request flag */
#define OSSecondEnableInt()  OSMTSCREG2 |= OSFEN          /* enable timer interrupts      */
#define OSSecondDisableInt() OSMTSCREG2 &= ~OSFEN         /* disable timer interrupts     */
#endif
#endif /* defined(OSTIM2eMIOS) || defined(OSTIM2eMIOS1) || || defined(OS2TIM2eMIOS) */

#if defined(OSTIM2PIT) || defined(OS2TIM2PIT)
/*********************************************************  Second PIT timer  *****/
#if defined(OSTIMPIT_TYPE1)                     /* PIT module type 1 */

#define OSTIM2TCNT    OSTVAL( OSTIM2CHAN )      /* counter value */
#define OSTIM2CHOC    OSTLVAL( OSTIM2CHAN )     /* timer load value */
#define OSTIM2CHBIT   (1 << OSTIM2CHAN)         /* channel bit */
 
#define OSTim2HWprepare()   OSPITCTRL = 0u; OSPITINTSEL |= OSTIM2CHBIT

#define OSSecondRun()       OSPITEN |= OSTIM2CHBIT       /* active timer ( PENn = 1) */
#define OSSecondClearFlag()  OSPITFLG = OSTIM2CHBIT      /* clear interrupt flag (TIFn = 1) */
#define OSSecondStop()      OSPITEN &= ~OSTIM2CHBIT      /* disable timer ( PENn = 0) */
#define OSSecondEnableInt()  OSPITINTEN |= OSTIM2CHBIT   /* enable timer interrupts (TIEn = 1) */
#define OSSecondDisableInt() OSPITINTEN &= ~OSTIM2CHBIT  /* disable timer interrupts (TIEn = 0) */
#endif

#if defined(OSTIMPIT_TYPE2)                 /* PIT module type 2 */

#define OSTIM2TENBIT     0x01u              /* timer enable bit */
#define OSTIM2TIFBIT     0x01u              /* time interrupt flag bit */
#define OSTIM2TIEBIT     0x02u              /* timer interrupt enable bit */
#define OSTIM2MDIS       0x02u              /* PIT enable clock bit */

#define OSTIM2TCNT    OSCVAL( OSTIM2CHAN )  /* counter value */
#define OSTIM2CHOC    OSLDVAL( OSTIM2CHAN ) /* timer load value */


#if defined(OSTIM2PIT)
#if defined(OSSECONDFREEZE)
#define OSTIM2FRZBIT     0x01u              /* freeze bit */
#else
#define OSTIM2FRZBIT     0x00u
#endif
#endif /* defined(OSTIM2PIT) */

#if !defined(OSTIMPIT_RTI)
#define OSTIM2MDIS_RTI   0x04u              /* RTI disable clock bit */
#else
#define OSTIM2MDIS_RTI   0x00u
#endif

#define OSTim2HWprepare()   OSPITMCR |= OSTIM2FRZBIT | OSTIM2MDIS_RTI; OSPITMCR &= ~OSTIM2MDIS

#define OSSecondClearFlag()  OSETFLG( OSTIM2CHAN ) |= OSTIM2TIFBIT   /* clear interrupt flag (TIFn = 1) */
#endif /* defined(OSTIMPIT_TYPE2) */

#if defined(OSTIMPIT_TYPE3) || defined(OSTIMPIT_TYPE4)  /* PIT module type 3,4 */

#define OSTIM2TENBIT     0x01u              /* timer enable bit */
#define OSTIM2TIFBIT     0x01u              /* time interrupt flag bit */
#define OSTIM2TIEBIT     0x02u              /* timer interrupt enable bit */

#define OSTIM2TCNT    OSCVAL( OSTIM2CHAN )  /* counter value */
#define OSTIM2CHOC    OSLDVAL( OSTIM2CHAN ) /* timer load value */

#if defined(OSSECONDFREEZE)
#define OSTIM2FRZBIT     0x01u              /* freeze bit */
#else
#define OSTIM2FRZBIT     0x00u
#endif

#define OSTim2HWprepare()    OSPITMCR = OSTIM2FRZBIT

#define OSSecondClearFlag()  OSETFLG( OSTIM2CHAN ) = OSTIM2TIFBIT      /* clear interrupt flag (TIFn = 1) */
#endif /* defined(OSTIMPIT_TYPE3) || defined(OSTIMPIT_TYPE4) */

#if defined(OSTIMPIT_TYPE2) || defined(OSTIMPIT_TYPE3)|| defined(OSTIMPIT_TYPE4)
#define OSSecondRun()       OSTCTRL( OSTIM2CHAN ) = OSTIM2TENBIT     /* timer enable ( TENn = 1) */
#define OSSecondStop()      OSTCTRL( OSTIM2CHAN ) &= ~OSTIM2TENBIT   /* timer disable ( TENn = 0) */
#define OSSecondEnableInt()  OSTCTRL( OSTIM2CHAN ) |= OSTIM2TIEBIT   /* enable timer interrupts (TIEn = 1) */
#define OSSecondDisableInt() OSTCTRL( OSTIM2CHAN ) &= ~OSTIM2TIEBIT  /* disable timer interrupts (TIEn = 0) */
#endif
#endif /* defined(OSTIM2PIT) || defined(OS2TIM2PIT) */

#if defined(OSTIM2PIT_RTI)
/*********************************************************  Second RTI timer  *****/
#define OSTIM2TENBIT     0x01u          /* timer enable bit */
#define OSTIM2TIFBIT     0x01u          /* time interrupt flag bit */

#if defined(OSTIMPIT_RTI_TYPE1)         /* PIT_RTI type 1 */

#define OSTIM2TCNT       OSTVAL_RTI     /* counter value */
#define OSTIM2CHOC       OSTLVAL_RTI    /* timer load value */

#define OSTIM2TIEBIT     0x01u          /* timer interrupt enable bit */

#define OSTim2HWprepare()

#define OSSecondRun()   OSPITEN_RTI |= OSTIM2TENBIT             /* timer enable ( PEN0 = 1) */
#define OSSecondStop()   OSPITEN_RTI &= ~OSTIM2TENBIT           /* timer enable ( PEN0 = 0) */
#define OSSecondClearFlag()  OSPITFLG_RTI = OSTIM2TIFBIT        /* clear interrupt flag (TIF0 = 1) */
#define OSSecondEnableInt()  OSPITINTEN_RTI |= OSTIM2TIEBIT     /* enable timer interrupts (TIE0 = 1) */
#define OSSecondDisableInt() OSPITINTEN_RTI &= ~OSTIM2TIEBIT    /* disable timer interrupts (TIE0 = 0) */
#endif

#if defined(OSTIMPIT_RTI_TYPE2)              /* PIT_RTI type 2 */

#define OSTIM2TENBIT     0x01u               /* timer enable bit */
#define OSTIM2TIFBIT     0x01u               /* time interrupt flag bit */
#define OSTIM2TIEBIT     0x02u               /* timer interrupt enable bit */
#define OSTIM2MDIS_RTI   0x04u               /* RTI enable clock bit */

#define OSTIM2TCNT       OSCVAL_RTI          /* counter value */
#define OSTIM2CHOC       OSLDVAL_RTI         /* timer load value */

#if defined(OSSECONDFREEZE)
#define OSTIM2FRZBIT     0x01u               /* freeze bit */
#else
#define OSTIM2FRZBIT     0x00u
#endif

#if !defined(OSTIMPIT)
#define OSTIM2MDIS       0x02u               /* PIT disable clock bit */
#else
#define OSTIM2MDIS       0x00u
#endif

#define OSTim2HWprepare()   OSPITMCR_RTI |= OSTIM2FRZBIT | OSTIM2MDIS; OSPITMCR_RTI &= ~OSTIM2MDIS_RTI

#define OSSecondRun()       OSTCTRL_RTI = OSTIM2TENBIT       /* timer enable ( TENn = 1) */
#define OSSecondStop()      OSTCTRL_RTI &= ~OSTIM2TENBIT     /* timer disable ( TENn = 0) */
#define OSSecondClearFlag()  OSETFLG_RTI = OSTIM2TIFBIT      /* clear interrupt flag (TIFn = 1) */
#define OSSecondEnableInt()  OSTCTRL_RTI |= OSTIM2TIEBIT     /* enable timer interrupts (TIEn = 1) */
#define OSSecondDisableInt() OSTCTRL_RTI &= ~OSTIM2TIEBIT    /* disable timer interrupts (TIEn = 0) */
#endif /* defined(OSTIMPIT_RTI_TYPE2) */
#endif /* defined(OSTIM2PIT_RTI) */

#if defined(OSTIM2STM) || defined(OS2TIM2STM)
/*********************************************************  System STM timer  *****/
#if defined(OSTIM2STM)
#define OSTIM2TCNT      OSSTM_CNT               /* counter value */
#define OSTIM2CHOC      OSSTM_CMP(OSTIM2CHAN)   /* timer compare value */
#define OSSTREG2        OSSTM_CIR(OSTIM2CHAN)   /* status register */
#define OSSTARTVAL2     0u                      /* start counter value */ 
#endif
#define OSTIM2TENBIT    0x01u                   /* timer enable bit */
#define OSTIM2FLBIT     0x01u                   /* channel interrupt flag */
#define OSTIM2CENBIT    0x01u                   /* channel enable bit */

#if defined(OSTIM2STM)
#if defined(OSSECONDFREEZE)
#define OSTIM2FRZBIT    0x02u
#else
#define OSTIM2FRZBIT    0x00u
#endif
#endif
#if defined(OSTIM2STM)
#if defined(OSTIM2PRESCALER)
                             /* set prescaler,"stopped in debug mode" and timer enable bit */
#define OSTim2HWprepare()    OSSTM_CR = (OSTIM2PRESCALER << 8) | OSTIM2FRZBIT | OSTIM2TENBIT
#else
#define OSTim2HWprepare()    /* nothing to do */
#endif
#define OSSecondRun()                                               /* running by OSSecondEnableInt() */
#define OSSecondStop()       OSSTM_CCR(OSTIM2CHAN) = 0u             /* the channel is disabled (CENn = 0) */
#define OSSecondClearFlag()  OSSTM_CIR(OSTIM2CHAN) = OSTIM2FLBIT    /* clear interrupt flag (CIFn = 1) */
#define OSSecondEnableInt()  OSSTM_CCR(OSTIM2CHAN) = OSTIM2CENBIT   /* the channel is enabled (CENn = 1) */
#define OSSecondDisableInt() OSSTM_CCR(OSTIM2CHAN) = 0u             /* the channel is disabled (CENn = 0) */
#endif /* defined(OSTIM2STM) */

#endif /* defined(OSTIM2STM) || defined(OS2TIM2STM) */

/***************************************************************************
 * Macro:    OSSecondTimSetHW
 *
 * Description: Second timer's HW initialization;
 *              mode,control bits and prescaler are set here;
 *
 * Notes:       actions are similar to OSSystemTimSetHW
 *
 **************************************************************************/
#if defined(OSTIM2DEC)
OSINLINE void OSSecondSetHW(void)
{
    OSSETHID0( OSGETHID0() & ~(OSDECHID0_TBEN));/* Time base disable */
    OsSetDECAR(OSTIM2MODULO);                   /* Write modulo value into the DEC Auto-reload register */
    OSDecTimerSet(OSTIM2MODULO);
    OSSecondRun();                              /* start second timer  */
}
#endif

#if defined(OSTIM2FIT)
OSINLINE void OSSecondSetHW(void)
{
    OSSETHID0( OSGETHID0() & ~(OSFITHID0_TBEN));    /* Time base disable */
    OsSetTCR(OsGetTCR() & ~(OSTCR_FIE | OSTCR_FP | OSTCR_FPEXT) );   /* Clear all FIT bits */

#if defined(OSTIM2MODULO)
    OsSetTCR(OsGetTCR() | ((OSFITP << 24) | (OSFITPEXT << 13)) );   /* Set Fixed interval timer period */
#endif
    OSSecondRun();                              /* start second timer  */
}
#endif /* defined(OSTIM2FIT) */

#if defined(OSTIM2eMIOS) || defined(OSTIM2eMIOS1)
OSINLINE void OSSecondSetHW(void)
{
    OSTim2HWprepare();                      /* eMIOS general settings */

#if defined(OSTIM2MODULO)                   /* eMIOS chennal settings: */
    OSTIM2CHOC = OSTIM2MODULO;              /* set matching value */
#endif

#if defined(OSTIM2PRESCALER)
    OSMTSCREG2 = OSCH2FREEZE | OSBSL | (OSTIM2PRESCALER << 26); /* set freeze and counter source and presc.value */

#if (OSNSYSHWCTRS == 2)
    OSMTSCREG2 |= OSeMIOSHWMODE;            /* set HW timer mode */
#else
    OSMTSCREG2 |= OSeMIOSSWMODE;            /* set SW timer mode */
#endif
#endif /* defined(OSTIM2PRESCALER) */

#if defined(OSTIM2PRESCALER)
    OSSecondRun();                          /* start second timer  */
#endif
}
#endif /* defined(OSSECONDTIMER) */

#if defined(OSTIM2PIT)
OSINLINE void OSSecondSetHW(void)
{
#if defined(OSTIM2MODULO)
    OSTIM2CHOC = OSTIM2MODULO;
#endif
    OSTim2HWprepare();                  /* PIT settings */

    OSSecondRun();                      /* start second timer  */
}
#endif /* defined(OSTIM2PIT) */

#if defined(OSTIM2PIT_RTI)
OSINLINE void OSSecondSetHW(void)
{
#if defined(OSTIM2MODULO)
    OSTIM2CHOC = OSTIM2MODULO;
#endif
    OSTim2HWprepare();                  /* RTI settings */

    OSSecondRun();                      /* start second timer  */
}
#endif /* defined(OSTIM2PIT_RTI) */

#if defined(OSTIM2STM)
OSINLINE void OSSecondSetHW(void)
{
#if defined(OSTIM2PRESCALER)
    OSTIM2TCNT = OSSTARTVAL2;           /* clear counter register */
#endif
#if defined(OSTIM2MODULO)
    OSTIM2CHOC = OSTIM2MODULO;
#endif
    OSTim2HWprepare();                  /* STM settings */
}
#endif /* defined(OSTIM2STM) */

#endif /* defined(OSSECONDTIMER) || defined(OS2SECONDTIMER) */

#if defined(OSHWCOUNTER)    

#if (OSNHWCTRS == 1)
#define OSInterruptRaised( ctrId )  (OSSTREG & 1u)
#define OSHWCtrValue( ctrId )       (OSTIMTCNT)
#define OSHWCtrGetOC( ctrId )       (OSTIMCHOC)
#if defined(OSTIMeMIOS) || defined(OSTIMeMIOS1)
#define OSHWCtrInit( ctrId, value ) \
        OSMTSCREG &= ~OSeMIOSHWMODE;   /* enter to GPIO mode for CNT changing */ \
        OSTIMTCNT = value; \
        OSMTSCREG |= OSeMIOSHWMODE;    /* restore to SAOC mode */ \
        OSSysTimClearFlag()
#endif /* defined(OSTIMeMIOS) || defined(OSTIMeMIOS1) */
#if defined(OSTIMSTM)
#define OSHWCtrInit( ctrId, value )   OSTIMTCNT = value
#endif
#else /* (OSNHWCTRS == 1) */
#define OSInterruptRaised( ctrId )  ( ctrId ? (OSSTREG2 & 1u) : (OSSTREG & 1u) )
#define OSHWCtrValue( ctrId )       ( ctrId ? (OSTIM2TCNT) : (OSTIMTCNT) )
#define OSHWCtrGetOC( ctrId )       ( ctrId ? (OSTIM2CHOC) : (OSTIMCHOC) )
#if defined(OSTIM2eMIOS) || defined(OSTIM2eMIOS1)
#if defined(OSTIMeMIOS) || defined(OSTIMeMIOS1)
#define OSHWSysModeDown()  (OSMTSCREG &= ~OSeMIOSHWMODE) /* enter to GPIO mode for CNT changing */
#define OSHWSysModeUp()  (OSMTSCREG |= OSeMIOSHWMODE)    /* restore to SAOC mode */
#define OSHWSecModeDown()  (OSMTSCREG2 &= ~OSeMIOSHWMODE)
#define OSHWSecModeUp()  (OSMTSCREG2 |= OSeMIOSHWMODE)
#else
#define OSHWSysModeDown()
#define OSHWSysModeUp()
#define OSHWSecModeDown()  (OSMTSCREG2 &= ~OSeMIOSHWMODE)
#define OSHWSecModeUp()  (OSMTSCREG2 |= OSeMIOSHWMODE)
#endif /*  defined(OSTIMeMIOS) || defined(OSTIMeMIOS1) */
#else /* defined(OSTIM2eMIOS) || defined(OSTIM2eMIOS1) */
#if defined(OSTIMeMIOS) || defined(OSTIMeMIOS1)
#define OSHWSysModeDown()  (OSMTSCREG &= ~OSeMIOSHWMODE)
#define OSHWSysModeUp()  (OSMTSCREG |= OSeMIOSHWMODE)
#define OSHWSecModeDown()
#define OSHWSecModeUp()
#else
#define OSHWSysModeDown()
#define OSHWSysModeUp()
#define OSHWSecModeDown()
#define OSHWSecModeUp()
#endif
#endif /* defined(OSTIM2eMIOS) || defined(OSTIM2eMIOS1) */
#define OSHWCtrInit( ctrId, value )         \
        if( ctrId == 0 )                    \
        {                                   \
            OSHWSysModeDown();              \
            OSTIMTCNT = (value);            \
            OSHWSysModeUp();                \
            OSSysTimClearFlag();            \
        }                                   \
        else                                \
        {                                   \
            OSHWSecModeDown();              \
            OSTIM2TCNT = (value);           \
            OSHWSecModeUp();                \
            OSSecondClearFlag();            \
        }
#endif /* OSNHWCTRS == 1 */

#endif /* defined(OSHWCOUNTER) */

#endif  /* OSTIMER_H */
