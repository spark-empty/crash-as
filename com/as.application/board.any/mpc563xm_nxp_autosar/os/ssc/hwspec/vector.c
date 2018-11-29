#define VECTOR_C
/******************************************************************************
*
*   Freescale(TM) and the Freescale logo are trademarks of Freescale Semiconductor, Inc. 
*   All other product or service names are the property of their respective owners. 
*   (C) Freescale Semiconductor, Inc. 2006-2010
*
*   You can use this example for any purpose on any computer system with the
*   following restrictions:
*
*   1. This example is provided  as is , without warranty.
*
*   2. You don't remove this copyright notice from this example or any direct
*      derivation thereof.
*
* Description:    Vector table for OS/MPC56xxAMv3
*
* Notes:
*
******************************************************************************/

#include    <os.h>

#define OSVECTORS_START_SEC_CODE
#include <ossections.h>

#if defined(OSDIABPPC)
#define OSALIGN   asm volatile (" .skip 0x0C ")
#endif
#if defined(OSGHSPPC)
#define OSALIGN   asm (" .skip 0x0C ")
#endif	

#if defined(OSDIABPPC) || defined(OSGHSPPC)
    OSASMF(   .globl VTABLE                   );
    OSASMF(VTABLE:                            ); /* Vector table start address */

#elif defined(OSCWPPC)  /* defined(OSDIABPPC) || defined(OSGHSPPC) */

#if defined(OSE200Z4) || defined(OSE200Z7)
extern void OSMachineCheckException( void );
#endif
extern void OSCriticalException( void );
extern void OSMachineCheckException( void );
extern void OSNonCriticalException( void );
extern void OSInterruptDispatcher( void );
extern void OSServiceDispatcher( void );
extern void OSDECisr( void );
extern void OSFITisr( void );
extern void OSTLBErrorException( void );
extern void OSDebugException( void );
extern void VTABLE( void );
#define SIXTEEN_BYTES 16
#pragma force_active on
#pragma function_align 16

#define OSALIGN  .align SIXTEEN_BYTES

asm void VTABLE( void )
{
    nofralloc
#endif

    OSASMF(    e_b   OSCriticalException        ); /* Critical input */

    OSALIGN;

#if defined(OSE200Z4) || defined(OSE200Z7)
    OSASMF(    e_b   OSMachineCheckException    ); /* Machine check */
#else
    OSASMF(    e_b   OSCriticalException        ); /* Machine check */
#endif

    OSALIGN;
    OSASMF(    e_b   OSNonCriticalException     ); /* Data storage */

    OSALIGN;
    OSASMF(    e_b   OSNonCriticalException     ); /* Instruction storage */

    OSALIGN;
    OSASMF(    e_b   OSInterruptDispatcher      ); /* External input */

    OSALIGN;
    OSASMF(    e_b   OSNonCriticalException     ); /* Alignment */

    OSALIGN;
    OSASMF(    e_b   OSNonCriticalException     ); /* Program */

    OSALIGN;
    OSASMF(    e_b   OSNonCriticalException     ); /* Floating-point unavailable */

    OSALIGN;
#if defined(OSSC3) || defined(OSSC4)              /* System call */
    OSASMF(    e_b   OSServiceDispatcher        );
#else
    OSASMF(    e_b   OSNonCriticalException     );
#endif

    OSALIGN;
    OSASMF(    e_b   OSNonCriticalException     );

    OSALIGN;
#if defined(OSDECISR) || defined(OSTIMDEC) || defined(OSTIM2DEC) || defined(OSTPTIMDEC)
    OSASMF(    e_b   OSDECisr                   ); /* Decrementer */
#else
    OSASMF(    e_b   OSNonCriticalException     );
#endif

    OSALIGN;
#if defined(OSFITISR)  || defined(OSTIMFIT) || defined(OSTIM2FIT)
    OSASMF(    e_b   OSFITisr                   ); /* Fixed Interval Timer */
#else
    OSASMF(    e_b   OSNonCriticalException     );
#endif

    OSALIGN;
    OSASMF(    e_b   OSCriticalException        ); /* Watchdog Timer */

    OSALIGN;
#if defined(OSSC3)  || defined(OSSC4)
    OSASMF(    e_b   OSTLBErrorException        ); /* Data TLB Error */
#else
    OSASMF(    e_b   OSNonCriticalException     );
#endif

    OSALIGN;
#if defined(OSSC3)  || defined(OSSC4)
    OSASMF(    e_b   OSTLBErrorException        ); /* Instruction TLB Error */
#else
    OSASMF(    e_b   OSNonCriticalException     );
#endif

    OSALIGN;
    OSASMF(    e_b   OSDebugException           ); /* Debug */

    OSALIGN;
    OSASMF(    e_b   OSNonCriticalException     ); /* SPE Unavailable */

    OSALIGN;
    OSASMF(    e_b   OSNonCriticalException     ); /* EFP Data */

    OSALIGN;
    OSASMF(    e_b   OSNonCriticalException     ); /* EFP Round */

#if defined(OSCWPPC)
}
#endif

#define OSVECTORS_STOP_SEC_CODE
#include <ossections.h>

#if defined(FLASH_START)

#define SRAM_BASE_ADDR 0x40000000

#if defined(OSMPC5644A)
#define OSLOOP_SIZE (192*1024)>>7
#elif defined(OSMPC5634M)
#define OSLOOP_SIZE (94*1024)>>7
#elif defined(OSMPC5674F)
#define OSLOOP_SIZE (256*1024)>>7
#else
#error  MCU type is not specified 
#endif

/* Code to intialize all internal RAM.
   This must be executed before using RAM to avoid ECC errors. */
#if defined(OSDIABPPC) || defined(OSGHSPPC)

    OSASMF2( .set BASE_SRAM_ADDRESS, SRAM_BASE_ADDR );
    OSASMF2( .set OS_LOOP_SIZE, OSLOOP_SIZE         );
   
#if defined(OSGHSPPC)
    OSASMF(     .globl __ghs_board_memory_init      );

    OSASMF( __ghsautoimport_ghs_board_memory_init:  );
    OSASMF( __ghs_board_memory_init:                );
#else
    OSASMF(    .globl          usr_init             );

    OSASMF( usr_init:                               );
#endif

    OSASMF2(    e_lis r11,%hi(BASE_SRAM_ADDRESS)    );

#elif defined(OSCWPPC)
void usr_init( void );    
asm void usr_init( void )
{
    nofralloc

    OSASMF2(    e_lis r11,SRAM_BASE_ADDR@h          );    /* Base address of the L2SRAM, 64-bit word aligned */
#endif
    
    OSASMF2(    e_li r12,OSLOOP_SIZE                );/* Loop counter to get all of L2SRAM; SIZE/4 bytes/32 GPRs */
    OSASMF(     mtctr r12                           );

    OSASMF( init_l2sram_loop:                       );
    OSASMF2(    e_stmw r0,0(r11)                    );/* Write all 32 GPRs to L2SRAM */
    OSASMF3(    e_addi r11,r11,128                  );/* Inc the ram ptr; 32 GPRs * 4 bytes = 128 */
    OSASMF(     e_bdnz init_l2sram_loop             );/* Branch OSLOOP_SIZE-1 times */
    OSASMF(     se_blr                              );

#if defined(OSCWPPC)
}
#endif

#endif /* if defined(FLASH_START) */
