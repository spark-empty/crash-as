#ifndef BCC1_M_H
#define BCC1_M_H
/**************************************************************************************
* 
*   Freescale(TM) and the Freescale logo are trademarks of Freescale Semiconductor, Inc. 
*   All other product or service names are the property of their respective owners. 
*   (C) Freescale Semiconductor, Inc. 2008 - 2010
* 
*   You can use this example for any purpose on any computer system with the
*   following restrictions:
*
*   1. This example is provided "as is", without warranty.
*
*   2. You don't remove this copyright notice from this example or any direct derivation 
*      thereof.
*
*   Description:  hardware specific definitions for benchmark
*
**************************************************************************************/

#if defined(OSDIABPPC)
#define APPNEAR __attribute__(( section(".sapp_vU_data") ))
#endif
#if defined(OSCWPPC)
#define APPNEAR __declspec(section ".sapp_vU_data")
#endif
#if defined(OSGHSPPC)
#define APPNEAR
#endif

/* ST_DELAY tuning */
#if defined(OSSC1)
	#if defined(OSBCC)
	#define ST_DELAY 62000
	#elif defined(OSECC)
	#define ST_DELAY 55000
	#endif
#elif defined(OSSC2)
	#if defined(OSBCC)
	#define ST_DELAY 66000
	#elif defined(OSECC)
	#define ST_DELAY 60000
	#endif
#elif defined(OSSC3)
	#if defined(OSBCC)
	#define ST_DELAY 64000
	#elif defined(OSECC)
	#define ST_DELAY 56000
	#endif
#elif defined(OSSC4)
	#if defined(OSBCC)
	#define ST_DELAY 67000
	#elif defined(OSECC)
	#define ST_DELAY 61000
	#endif
#else
	#define ST_DELAY 67000
#endif

/* Branch Unit Control and Status Register (BUCSR) */
#if defined(OSGHSPPC)
#define SetBUCSR(bits)  __MTSPR(1013,(bits))
#elif defined(OSCWPPC)
extern void SetBUCSR(register OSDWORD bits);
OSINLINE void SetBUCSR(register OSDWORD bits)
{
    asm{    mtspr   1013, bits   };
}
#elif defined(OSDIABPPC) 
void SetBUCSR( OSDWORD bits);
OSASM void SetBUCSR( OSDWORD bits)
{
%reg bits
    mtspr   1013, bits
}
#else
#error SetBUCSR() is not defined
#endif

/* Branch target buffer enable */
#define BUCSR_BPEN      0x1ul           
#define EnableBTB()     SetBUCSR(BUCSR_BPEN)

/*  Conditional compilation for this application    */
/* #define USEPORT  */        /* uncomment it to enable pin manipulations */
#define USETIMER         /* comment it to disable timer capture      */

#if defined(USEPORT)

#define OSSIU_BASE_ADDR 0xC3F90000
#define GPIOPCR01  OSSIUREG(OSSIU_BASE_ADDR+0x40+114*2) /* PCR 114-115 ETPUA0-1 PJ9.0-1*/
#define GPIOPCR23  OSSIUREG(OSSIU_BASE_ADDR+0x40+116*2) /* PCR 116-117 ETPUA2-3 PJ9.2-3*/
#define GPIOPCR45  OSSIUREG(OSSIU_BASE_ADDR+0x40+118*2) /* PCR 118-119 ETPUA4-5 PJ9.4-5*/
#define GPIOPCR67  OSSIUREG(OSSIU_BASE_ADDR+0x40+120*2) /* PCR 120-121 ETPUA6-7 PJ9.6-7*/

#define PCR        0x02000200                          /* PA = 0 - GRIO OBE = 1 - enable the pad  group as outputs
                                                         IBE = 0 - disable the pad  group as inputs */
#define GPIOODO0  OSSIUBYTEREG(OSSIU_BASE_ADDR+0x600+114) /* Output-Only Data Value Out ETPUA0 PJ9.0*/
#define GPIOODO1  OSSIUBYTEREG(OSSIU_BASE_ADDR+0x600+115) /* Output-Only Data Value Out ETPUA1 PJ9.1*/
#define GPIOODO2  OSSIUBYTEREG(OSSIU_BASE_ADDR+0x600+116) /* Output-Only Data Value Out ETPUA2 PJ9.2*/
#define GPIOODO3  OSSIUBYTEREG(OSSIU_BASE_ADDR+0x600+117) /* Output-Only Data Value Out ETPUA3 PJ9.3*/
#define GPIOODO4  OSSIUBYTEREG(OSSIU_BASE_ADDR+0x600+118) /* Output-Only Data Value Out ETPUA4 PJ9.4*/
#define GPIOODO5  OSSIUBYTEREG(OSSIU_BASE_ADDR+0x600+119) /* Output-Only Data Value Out ETPUA5 PJ9.5*/
#define GPIOODO6  OSSIUBYTEREG(OSSIU_BASE_ADDR+0x600+120) /* Output-Only Data Value Out ETPUA6 PJ9.6*/
#define GPIOODO7  OSSIUBYTEREG(OSSIU_BASE_ADDR+0x600+121) /* Output-Only Data Value Out ETPUA7 PJ9.7*/

#define ClrGPIOODO 0x0
#define SetGPIOODO 0x1

#define IniPort()   \
        GPIOPCR01 = PCR; \
        GPIOPCR23 = PCR; \
        GPIOPCR45 = PCR; \
        GPIOPCR67 = PCR; \
        ClrPort();


#define SetPort(nn)   \
        ClrPort()\
        nn = SetGPIOODO;       /* set pin                   */

#define ClrPort()   \
        GPIOODO0 = ClrGPIOODO;\
        GPIOODO1 = ClrGPIOODO;\
        GPIOODO2 = ClrGPIOODO;\
        GPIOODO3 = ClrGPIOODO;\
        GPIOODO4 = ClrGPIOODO;\
        GPIOODO5 = ClrGPIOODO;\
        GPIOODO6 = ClrGPIOODO;\
        GPIOODO7 = ClrGPIOODO;
              /* reset  pin                  */

#define PIN0 GPIOODO0
#define PIN1 GPIOODO1
#define PIN2 GPIOODO2
#define PIN3 GPIOODO3
#define PIN4 GPIOODO4
#define PIN5 GPIOODO5
#define PIN6 GPIOODO6
#define PIN7 GPIOODO7

#else /* defined(USEPORT) */

#define ClrPort()
#define SetPort(nn)
#define IniPort()

#endif /* defined(USEPORT) */

#define StartTime( ) (*((volatile OSDWORD *)0xFFF3C000)) |= 0x00000003
#define GetTime( )   (*((volatile OSDWORD *)0xFFF3C004))
#define ClearTime( ) (*((volatile OSDWORD *)0xFFF3C004)) = 0

#ifdef USETIMER
#define SetStartTime( )     inTime = GetTime( )
#define CalcTime( VarName ) VarName = GetTime( ); VarName -= ( inTime + pfm1 )
#else
#define SetStartTime( )                
#define CalcTime( VarName )
#endif /* USETIMER */

/*********************************** eMIOS **********************************/
#define MTSCMP(Channel) OSSIUREG(OSeMIOSBASE + 32*Channel + 32)  /* "A"     */
#define MTSCNT(Channel) OSSIUREG(OSeMIOSBASE + 32*Channel + 40)  /* Counter */
#define MTSC(Channel)   OSSIUREG(OSeMIOSBASE + 32*Channel + 44)  /* Control */
#define MTSS(Channel)   OSSIUREG(OSeMIOSBASE + 32*Channel + 48)  /* Status  */

//#define CMPBIT 0x100                             /* channel 8 bit  */

#define ClearCMP(Channel)   MTSS(Channel) = 1 /* clear interrupt request flag */
#define CMPSetHW(Channel)   MTSC(Channel) = 0; \
                            OSMTSOUDIS &= ~(1 << Channel); \
                            MTSC(Channel) = OSCHFREEZE | 0x02000603

#define EnableCMP(Channel)  MTSC(Channel) |=  0x00020000 /* enable CMP interrupts  */
#define DisableCMP(Channel) MTSC(Channel) &= ~0x00020000 /* disable CMP interrupts */

#define T2MODULO   8192
#define ISR1DELAY  (T2MODULO / 2)    /* 0.5 ms delay for OneTimeISR          */

/************************************* PIT ***********************************/
#define PIT_MCR            OSSIUREG(OSPITBASE)                               /* PIT Module Control Register */
#define PIT_LDVAL(Channel) OSSIUREG(OSPITBASE + 0x100 + (16*Channel) + 0x00) /* Timer Load Value Register */
#define PIT_CVAL(Channel)  OSSIUREG(OSPITBASE + 0x100 + (16*Channel) + 0x04) /* Current Timer Value Register */
#define PIT_TCTRL(Channel) OSSIUREG(OSPITBASE + 0x100 + (16*Channel) + 0x08) /* Timer Control Register */
#define PIT_TFLG(Channel)  OSSIUREG(OSPITBASE + 0x100 + (16*Channel) + 0x0C) /* Timer Flag Register */

#endif /* BCC1_M_H */
