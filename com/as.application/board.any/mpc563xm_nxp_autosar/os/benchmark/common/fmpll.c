/**************************************************************************************
* 
*   Freescale(TM) and the Freescale logo are trademarks of Freescale Semiconductor, Inc. 
*   All other product or service names are the property of their respective owners. 
*   (C) Freescale Semiconductor, Inc. 2009 - 2010
* 
*   You can use this example for any purpose on any computer system with the
*   following restrictions:
*
*   1. This example is provided "as is", without warranty.
*
*   2. You don't remove this copyright notice from this example or any direct derivation 
*      thereof.
*
*   Description:  Setup PLL
*
**************************************************************************************/

#include <os.h>

#define PCR_BASE   0xC3F90040ul

#define CUR100MS  6400000
#define ESYNCHR1  ((volatile OSDWORD *)0xC3F80008)
#define ESYNCHR2  ((volatile OSDWORD *)0xC3F8000C)
#define SYNSR     ((volatile OSDWORD *)0xC3F80004)
#define LOLRE     0x00400000
#define LOCRE     0x00200000
#define LOCK      0x00000008
#define EMODE     0x80000000
#define CLKCFG0   0x40000000
#define CLKCFG1   0x20000000
#define CLKCFG2   0x10000000

#define APP_START_SEC_CODE
#include "MemMap.h"

void SetPLL( void );

void SetPLL( void )
{
/************************************************

Fsys = Fref * EMFD / ((EPREDIV + 1) * 2^(ERFD + 1))

For Fref=40MHz, EMFD=64, EPREDIV=4 and ERFD=2
Fsys = 40MHz * 64 / 40 = 64MHz
100mS = 6400000 tick/S

*************************************************/
	volatile register OSDWORD i, ES1, ES2;
    
    ES1     = *ESYNCHR1; 
    ES2     = *ESYNCHR2; 
    /**** clear LOLRE and LOCRE ****/
    ES2 &= ~(LOLRE | LOCRE);
    *ESYNCHR2 = ES2; 
    OSMSYNC(); 
    /**** Bypass mode with crystal reference and PLL running ****/ 
    ES1 &= ~CLKCFG0;    
    ES1 |= (EMODE | CLKCFG1 | CLKCFG2); 
 
    /**** EPREDIV = 4, EMFD = 64 ****/         
    ES1 &= 0xFFF0FF00; 
    ES1 |= 0x00040040;     
    
    *ESYNCHR1 = ES1; 
    OSMSYNC(); 

    /**** ERFD = 2 ****/
    ES2 &= 0xFFFFFF00;        
    ES2 |= 0x00000002; 
    *ESYNCHR2 = ES2; 

    do 
    { 
        OSMSYNC(); 
        i = *SYNSR; 
    } while ( (i & LOCK) == 0 ); 
    
    ES1 |= CLKCFG0;    
    *ESYNCHR1 = ES1; 
    OSMSYNC();    
}

#define APP_STOP_SEC_CODE
#include "MemMap.h"