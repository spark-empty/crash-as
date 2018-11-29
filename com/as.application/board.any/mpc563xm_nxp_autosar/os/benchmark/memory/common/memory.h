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
/* #define USEPORT */       /* uncomment it to enable pin manipulations */
#define USETIMER       /* comment it to disable timer capture     */
//#define TICKDURATION 781 /* = 7.81ns */

/*********************************** eMIOS **********************************/
#define MTSCMP(Channel) OSSIUREG(OSeMIOSBASE + 32*Channel + 32)  /* "A"     */
#define MTSCNT(Channel) OSSIUREG(OSeMIOSBASE + 32*Channel + 40)  /* Counter */
#define MTSC(Channel)   OSSIUREG(OSeMIOSBASE + 32*Channel + 44)  /* Control */
#define MTSS(Channel)   OSSIUREG(OSeMIOSBASE + 32*Channel + 48)  /* Status  */

#define CMPBIT 0x0100                                      /* channel 8 bit  */

#define ClearCMP(Channel)   MTSS(Channel) = 1 /* clear interrupt request flag */
#define CMPSetHW(Channel)   MTSC(Channel) = 0; \
                            OSMTSOUDIS &= ~(1 << Chanel); \
                            MTSC(Channel) = OSCHFREEZE | 0x02000603

#define EnableCMP(Channel)  MTSC(Channel) |=  0x00020000 /* enable CMP interrupts  */
#define DisableCMP(Channel) MTSC(Channel) &= ~0x00020000 /* disable CMP interrupts */

/*********************************** STM timer *********************************/
#define StartTime()  OSSTM_CR |= 0x00000001;
#define GetTime()    OSSTM_CNT
#define ClearTime()  OSSTM_CNT = 0
#define InitTime()

/*********************************** RTC timer *********************************/
//#define StartTime()  (*((volatile OSDWORD *)0xC3FEC004)) = 0x80000000
//#define GetTime()    (*((volatile OSDWORD *)0xFFF3C00C))
//#define ClearTime()  (*((volatile OSDWORD *)0xFFF3C00C)) = 0
//#define InitTime()   (*((volatile OSDWORD *)0xC3FEC000)) = 0

#define TrustedApplication_START_SEC_VAR_FAST_UNSPECIFIED
#include "MemMap.h"
extern OSDWORD APPNEAR volatile sysCnt;             /* counter for "useful" work */
extern OSDWORD APPNEAR volatile nosys;              /* counter for "useful" work w/o system overhead */
extern OSWORD  APPNEAR procent;                     /* result goes here */
#define TrustedApplication_STOP_SEC_VAR_FAST_UNSPECIFIED
#include "MemMap.h"

#define SYNCHRON 0x02000000             /* time for synchronization     */
#define MEASURE  0x04000000             /* time of measurement = 98 ms  */
#define MEASURE1 SYNCHRON + MEASURE
#define MEASURE2 SYNCHRON + 2*MEASURE


/*** definitions for measuring stack usage ***/

/*** stack symbols ***/
#define SP_TOP    ((OSBYTE *)(&OSSTACKTOP[0]))
#define SP_BOTTOM ((OSBYTE *)(&OSSTACKBOTTOM[0]))

#define STACKPATTERN 0xA5A5A5A5                 /* pattern to fill stack    */

/*** stack functions prototypes   ***/
OSDWORD GetUsedBytes( OSBYTE* start, OSDWORD num );
void IniStack( OSBYTE* start, OSDWORD num  );

#endif /* BCC1_M_H */

