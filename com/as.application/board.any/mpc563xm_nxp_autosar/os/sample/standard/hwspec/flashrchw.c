#define FLASHRCHW_C
/******************************************************************************
*
*   Freescale(TM) and the Freescale logo are trademarks of Freescale Semiconductor, Inc. 
*   All other product or service names are the property of their respective owners. 
*   (C) Freescale Semiconductor, Inc. 2006-2009
*
*   You can use this example for any purpose on any computer system with the
*   following restrictions:
*
*   1. This example is provided "as is", without warranty.
*
*   2. You don't remove this copyright notice from this example or any direct
*      derivation thereof.
*
* Description:    BAM RCHW block for OS/MPC56xxAMv3
*
* Notes:
*
******************************************************************************/

#if defined(FLASH_START)

#include    <os.h>

#define VLE_DISABLE   0x00000000  /* VLE is default disabled              */
#define VLE_ENABLE    0x01000000  /* VLE is enabled                       */
#define CS0_32BIT     0x00000000  /* CS0 external data bus is 32-bits     */
#define CS0_16BIT     0x02000000  /* CS0 external data bus is 16-bits     */
#define WTE_DISABLE   0x00000000  /* Disable core software watchdog timer */
#define WTE_ENABLE    0x04000000  /* Software watchdog timer enabled      */
#define SWT_DISABLE   0x00000000  /* Disable software watchdog timer      */
#define SWT_ENABLE    0x08000000  /* Software watchdog timer enabled      */
#define MPC56xxAM_ID  0x005A0000  /* RCHW boot ID for MPC56xxAM devices   */
#define RCHW_VAL (SWT_DISABLE | WTE_DISABLE | CS0_32BIT | VLE_ENABLE | MPC56xxAM_ID)

#if defined(OSCWPPC)
extern void __start(void);
#else
extern void _start(void);
#endif

#define RCHW_START_SEC_DATA
#include "MemMap.h"

#if defined(OSDIABPPC)
#pragma option -Xsmall-const=0 /* to ensure placement of RCHW1,2 variables in the section .rchwdata */
#endif

#if defined(OSCWPPC)
#define RCHWDATA __declspec(section ".rchwdata") 
#define ENTRY_POINT __start
#else
#define RCHWDATA
#define ENTRY_POINT  _start
#endif

RCHWDATA const OSDWORD RCHW1=RCHW_VAL;
RCHWDATA const OSDWORD RCHW2=(OSDWORD)ENTRY_POINT;

#define RCHW_STOP_SEC_DATA
#include "MemMap.h"

#endif /* defined(FLASH_START) */
