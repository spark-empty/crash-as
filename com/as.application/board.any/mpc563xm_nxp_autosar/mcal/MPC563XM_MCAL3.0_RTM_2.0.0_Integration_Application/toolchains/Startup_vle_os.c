/**
    @file        Startup_vle.c
    @version     2.0.0

    @brief       AUTOSAR Sample_app - Startup file for PowerPC VLE.
    @details     Startup file for PowerPC VLE.

    Project      : AUTOSAR 3.0 MCAL
    Platform     : PA
    Peripheral   : 
    Dependencies : Base Det Dem Port Dio Mcu SchM Wdg WdgIf CanIf LinIf EcuM

    Autosar Version       : 1.9.0
    Autosar Revision      : ASR_REL_1_9_REV_0003
    Autosar Conf. Variant :
    Software Version      : 2.0.0
    Build Version         : MPC563xMxM_MCAL_2_0_0_RTM_ASR_REL_1_9_REV_0003_20110214

    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
    All Rights Reserved.
*/
/*==================================================================================================
==================================================================================================*/

/************************************************************************/
/* Autosar synopsis of startup code (See MCU Specification):            */
/*                                                                      */
/*   Before the MCU driver can be initialized, a basic initialization   */
/*   of the MCU has to be executed. This MCU specific initialization is */
/*   typically executed in a start-up code. The start-up code of the    */
/*   MCU shall be executed after power up and any kind of micro-        */
/*   controller reset. It shall perform very basic and microcontroller  */
/*   specific start-up initialization and shall be kept short, because  */
/*   the MCU clock and PLL is not yet initialized. The start-up code    */
/*   shall cover MCU specific initialization, which is not part of      */
/*   other MCU services or other MCAL drivers. The following steps      */
/*   summarizes basic functionality which shall be included in the      */
/*   start-up code. They are listed for guidance, because some          */
/*   functionality might not be supported. No code will be found in     */
/*   case.                                                              */
/************************************************************************/


#include "Mcal.h"
#include "Platform_Types.h"

/* Function Definitions */
extern int main(void);
extern void _start(void);

#define RCW 0x015A0000UL

#if defined(DIAB)
#pragma section CONST ".rchwdata"
#elif defined(GHS)
#pragma ghs section const=".rchwdata"
#else
#error Unknown compiler
#endif /* DIAB */

#if defined(DIAB)
#pragma option -Xsmall-const=0 /* to ensure placement of RCHW1,2 variables in the section .rchwdata */
#endif

const uint32 RCHW1=RCW;
const uint32 RCHW2=(uint32)_start;

#if defined(DIAB)
#pragma section CONST
#elif defined(GHS)
#pragma ghs section const=default
#else
#error Unknown compiler
#endif /* DIAB */



void StartupCode(void)

{
/*****************************************************/
/* Skip normal entry point as nothing is initialized */
/*****************************************************/
    ASM_KEYWORD(".align 4");
    ASM_KEYWORD(" .globl _start");
    ASM_KEYWORD(" .globl __start");
    ASM_KEYWORD("_start:");
    ASM_KEYWORD("__start:");

    ASM_KEYWORD(" xor  r0, r0, r0");
    ASM_KEYWORD(" xor  r1, r1, r1");
    ASM_KEYWORD(" xor  r2, r2, r2");
    ASM_KEYWORD(" xor  r3, r3, r3");
    ASM_KEYWORD(" xor  r4, r4, r4");
    ASM_KEYWORD(" xor  r5, r5, r5");
    ASM_KEYWORD(" xor  r6, r6, r6");
    ASM_KEYWORD(" xor  r7, r7, r7");
    ASM_KEYWORD(" xor  r8, r8, r8");
    ASM_KEYWORD(" xor  r9, r9, r9");
    ASM_KEYWORD(" xor  r10, r10, r10");
    ASM_KEYWORD(" xor  r11, r11, r11");
    ASM_KEYWORD(" xor  r12, r12, r12");
    ASM_KEYWORD(" xor  r13, r13, r13");
    ASM_KEYWORD(" xor  r14, r14, r14");
    ASM_KEYWORD(" xor  r15, r15, r15");
    ASM_KEYWORD(" xor  r16, r16, r16");
    ASM_KEYWORD(" xor  r17, r17, r17");
    ASM_KEYWORD(" xor  r18, r18, r18");
    ASM_KEYWORD(" xor  r19, r19, r19");
    ASM_KEYWORD(" xor  r20, r20, r20");
    ASM_KEYWORD(" xor  r21, r21, r21");
    ASM_KEYWORD(" xor  r22, r22, r22");
    ASM_KEYWORD(" xor  r23, r23, r23");
    ASM_KEYWORD(" xor  r24, r24, r24");
    ASM_KEYWORD(" xor  r25, r25, r25");
    ASM_KEYWORD(" xor  r26, r26, r26");
    ASM_KEYWORD(" xor  r27, r27, r27");
    ASM_KEYWORD(" xor  r28, r28, r28");
    ASM_KEYWORD(" xor  r29, r29, r29");
    ASM_KEYWORD(" xor  r30, r30, r30");
    ASM_KEYWORD(" xor  r31, r31, r31");

/*******************************************************************/
/* Freescale Guidance 1 - Init registers to avoid lock-step issues */
/* N/A                                                             */
/*******************************************************************/

/***************************************************/
/* Freescale Guidance 2 - MMU BAM Basic Initialization */
/* MPC5606S - not needed, MMU already configured by BAM */
/***************************************************/

/******************************************************************/
/* Autosar Guidance 1 - The start-up code shall initialize the    */
/* base addresses for interrupt and trap vector tables. These base*/
/* addresses are provided as configuration parameters or          */
/* linker/locator setting.                                        */
/******************************************************************/
    /* Initialize IVPR register to address of Interrupt Vector Table */
/******************************************************************/
/* Autosar Guidance 2 - The start-up code shall initialize the    */
/* interrupt stack pointer, if an interrupt stack is              */
/* supported by the MCU. The interrupt stack pointer base address */
/* and the stack size are provided as configuration parameter or  */
/* linker/locator setting.                                        */
/*                                                                */
/******************************************************************/

/******************************************************************/
/* Autosar Guidance 3 - The start-up code shall initialize the    */
/* user stack pointer. The user stack pointer base address and    */
/* the stack size are provided as configuration parameter or      */
/* linker/locator setting.                                        */
/******************************************************************/
    ASM_KEYWORD(" e_lis   r1, __SP_INIT@h");
    ASM_KEYWORD(" e_or2i    r1, __SP_INIT@l");

/******************************************************************/
/* Autosar Guidance 4 - If the MCU supports context save          */
/* operation, the start-up code shall initialize the memory which */
/* is used for context save operation. The maximum amount of      */
/* consecutive context save operations is provided as             */
/* configuration parameter or linker/locator setting.             */
/*                                                                */
/******************************************************************/

/******************************************************************/
/* Autosar Guidance 5 - The start-up code shall ensure that the   */
/* MCU internal watchdog shall not be serviced until the watchdog */
/* is initialized from the MCAL watchdog driver. This can be      */
/* done for example by increasing the watchdog service time.      */
/*                                                                */
/******************************************************************/
    ASM_KEYWORD(" e_lis     r6,0xfff3 ");
    ASM_KEYWORD(" e_or2i    r6,0x8010 ");
    ASM_KEYWORD(" e_li      r7,0xC520 ");
    ASM_KEYWORD(" se_stw    r7,0x0(r6)");
    ASM_KEYWORD(" e_li      r7,0xD928 ");
    ASM_KEYWORD(" se_stw    r7,0x0(r6) "); /* # Disengage soft-lock */

    ASM_KEYWORD(" e_lis     r6,0xfff3 ");
    ASM_KEYWORD(" e_or2i    r6,0x8000 ");
    ASM_KEYWORD(" e_lis     r7,0xff00 ");
    ASM_KEYWORD(" e_or2i    r7,0x010A ");
    ASM_KEYWORD(" se_stw    r7,0x0(r6) "); /* # WEN = 0 */

/******************************************************************/
/* Autosar Guidance 6 - If the MCU supports cache memory for data */
/* and/or code, it shall be initialized and enabled in the        */
/* start-up code.                                                 */
/*                                                                */
/******************************************************************/

/******************************************************************/
/* Autosar Guidance 7 - The start-up code shall initialize MCU    */
/* specific features of internal memory like memory protection.   */
/*                                                                */
/******************************************************************/

/******************************************************************/
/* Autosar Guidance 8 - If external memory is used, the memory    */
/* shall be initialized in the start-up code. The start-up code   */
/* shall be prepared to support different memory configurations   */
/* depending on code location. Different configuration options    */
/* shall be taken into account for code execution from            */
/* external/internal memory.                                      */
/* N/A - external memory is not used                              */
/******************************************************************/

/******************************************************************/
/* Autosar Guidance 9 - The settings of the different memories    */
/* shall be provided to the start-up code as configuration        */
/* parameters.                                                    */
/* N/A - all memories are already configured                      */
/******************************************************************/

/******************************************************************/
/* Autosar Guidance 10 - In the start-up code a default           */
/* initialization of the MCU clock system shall be performed      */
/* including global clock prescalers.                             */
/******************************************************************/

/******************************************************************/
/* Autosar Guidance 11 - The start-up code shall enable           */
/* protection mechanisms for special function registers(SFR’s),   */
/* if supported by the MCU.                                       */
/* N/A - will be handled by Autosar OS                            */
/******************************************************************/

/******************************************************************/
/* Autosar Guidance 12 - The start-up code shall initialize all   */
/* necessary write once registers or registers common to several  */
/* drivers where one write, rather than repeated writes, to the   */
/* register is required or highly desirable.                      */
/******************************************************************/
/* TBD - MSR */

/******************************************************************/
/* Autosar Guidance 13 - The start-up code shall initialize a     */
/* minimum amount of RAM in order to allow proper execution of    */
/* the MCU driver services and the caller of these services.      */
/******************************************************************/
/* MPC55xx - internal ram must be initialized for error correction*/
/******************************************************************/
#ifndef SINTRAM  /* SINTRAM defined by compiler option -DSINTRAM only for INTRAM build */
     ASM_KEYWORD(" e_lis   r5, INT_SRAM_SIZE@h");     /* Number of 4 byte segments */
     ASM_KEYWORD(" e_or2i    r5, INT_SRAM_SIZE@l"); /* Number of 4 byte segments */
     ASM_KEYWORD(" se_mtctr r5");                       /* configure control register for use with e_bdnz */

/* start address of the internal SRAM */
     ASM_KEYWORD(" e_lis   r5,INT_SRAM_START@h");
     ASM_KEYWORD(" e_or2i    r5, INT_SRAM_START@l");

/* Repeat */
     ASM_KEYWORD("sram_loop:");
     ASM_KEYWORD("e_stmw  r16,0(r5)");   /* write 0 to to L2RAM and update r5 address */
     ASM_KEYWORD("e_addi r5,r5,64 ");
     ASM_KEYWORD(" e_bdnz   sram_loop"); /* loop for 64k of L2RAM */
#endif
/************************/
/* Erase ".sbss Section" */
/************************/
     ASM_KEYWORD(" xor   r0, r0, r0 ");
     ASM_KEYWORD(" e_lis  r5, SBSS_SRAM_SIZE@h");       /* Number of words */
     ASM_KEYWORD(" e_or2i   r5, SBSS_SRAM_SIZE@l");     /* Number of words */
     ASM_KEYWORD(" or.  r5, r5, r5");                   /* Number of words */
     ASM_KEYWORD(" e_beq    sram_erase1");
     ASM_KEYWORD(" se_mtctr r5");                       /* configure control register for use with e_bdnz */

/* start address of the sbss section */
     ASM_KEYWORD(" e_lis   r5,SBSS_SRAM_START@h");
     ASM_KEYWORD(" e_or2i    r5, SBSS_SRAM_START@l");
     ASM_KEYWORD(" xor   r0, r0, r0 ");
     ASM_KEYWORD(" e_subi  r5,r5,4");                   /* decrement by 4 to prepare for e_stwu in loop */

/* Repeat */
     ASM_KEYWORD("sram_loop1:");
     ASM_KEYWORD(" e_stwu   r0,4(r5)");                 /* write 0 to RAM and update r5 address */
     ASM_KEYWORD(" e_bdnz   sram_loop1");
     ASM_KEYWORD("sram_erase1:");

/************************/
/* Erase ".bss Section" */
/************************/
     ASM_KEYWORD(" e_lis   r5, BSS_SRAM_SIZE@h");       /* Number of words */
     ASM_KEYWORD(" e_or2i    r5, BSS_SRAM_SIZE@l");     /* Number of words */
     ASM_KEYWORD(" or.   r5, r5, r5");                  /* Number of words */
     ASM_KEYWORD(" e_beq   sram_erase2");
     ASM_KEYWORD(" se_mtctr r5");                       /* configure control register for use with e_bdnz */

/* start address of the bss section */
     ASM_KEYWORD(" e_lis   r5, BSS_SRAM_START@h");
     ASM_KEYWORD(" e_or2i    r5, BSS_SRAM_START@l");
     ASM_KEYWORD(" e_subi  r5,r5,4");                   /* decrement by 4 to prepare for e_stwu in loop */

/* Repeat */
     ASM_KEYWORD("sram_loop2:");
     ASM_KEYWORD(" e_stwu r0,4(r5)");                  /* write 0 to RAM and update r5 address, r0 must be zero */
     ASM_KEYWORD(" e_bdnz   sram_loop2");
     ASM_KEYWORD("sram_erase2:");

/******************************************************************/
/* Copy  initialized data from Flash to SRAM                      */
/******************************************************************/
/*******************/
/* .PPC.EMB.sdata0 */
/*******************/
     ASM_KEYWORD(" e_lis   r5, RC_PPC_SDATA2_SIZE@h");      /* Number of words */
     ASM_KEYWORD(" e_or2i    r5, RC_PPC_SDATA2_SIZE@l");    /* Number of words */
     ASM_KEYWORD(" or.   r5, r5, r5");                      /* Number of words */
     ASM_KEYWORD(" e_beq   data_copy1");
     ASM_KEYWORD(" se_mtctr r5");                       /* configure control register for use with e_bdnz */

/* source address of the section */
     ASM_KEYWORD(" e_lis   r8, RC_PPC_SDATA2_SRC@h");
     ASM_KEYWORD(" e_or2i    r8, RC_PPC_SDATA2_SRC@l");
     ASM_KEYWORD(" e_subi  r8,r8,4");                   /* decrement by 4 to prepare for e_stwu in loop */

/* Destination address of the section */
     ASM_KEYWORD(" e_lis   r9, RC_PPC_SDATA2_DEST@h");
     ASM_KEYWORD(" e_or2i    r9, RC_PPC_SDATA2_DEST@l");
     ASM_KEYWORD(" e_subi  r9,r9,4");                   /* decrement by 4 to prepare for e_stwu in loop */

/* Repeat */
     ASM_KEYWORD("data_copy_loop1:");
     ASM_KEYWORD(" e_lwzu  r10,4(r8)");
     ASM_KEYWORD(" e_stwu  r10,4(r9)");
     ASM_KEYWORD(" e_bdnz  data_copy_loop1");
    ASM_KEYWORD("data_copy1:");
/**********/
/* .sdata */
/**********/
     ASM_KEYWORD(" e_lis   r5, RC_SDATA_SIZE@h");       /* Number of words */
     ASM_KEYWORD(" e_or2i    r5, RC_SDATA_SIZE@l");     /* Number of words */
     ASM_KEYWORD(" or.   r5, r5, r5");                  /* Number of words */
     ASM_KEYWORD(" e_beq   data_copy2");
     ASM_KEYWORD(" se_mtctr r5");                       /* configure control register for use with e_bdnz */

/* source address of the section */
     ASM_KEYWORD(" e_lis   r8, RC_SDATA_SRC@h");
     ASM_KEYWORD(" e_or2i    r8, RC_SDATA_SRC@l");
     ASM_KEYWORD(" e_subi  r8,r8,4");                   /* decrement by 4 to prepare for e_stwu in loop */

/* Destination address of the section */
     ASM_KEYWORD(" e_lis   r9, RC_SDATA_DEST@h");
     ASM_KEYWORD(" e_or2i    r9, RC_SDATA_DEST@l");
     ASM_KEYWORD(" e_subi  r9,r9,4");                   /* decrement by 4 to prepare for e_stwu in loop */

/* Repeat */
     ASM_KEYWORD("data_copy_loop2:");
     ASM_KEYWORD(" e_lwzu  r10,4(r8)");
     ASM_KEYWORD(" e_stwu  r10,4(r9)");
     ASM_KEYWORD(" e_bdnz  data_copy_loop2");
     ASM_KEYWORD("data_copy2:");
/**********/
/* .data */
/**********/
     ASM_KEYWORD(" e_lis   r5, RC_DATA_SIZE@h");        /* Number of words */
     ASM_KEYWORD(" e_or2i    r5, RC_DATA_SIZE@l");      /* Number of words */
     ASM_KEYWORD(" or.   r5, r5, r5");                  /* Number of words */
     ASM_KEYWORD(" e_beq   data_copy3");
     ASM_KEYWORD(" se_mtctr r5");                       /* configure control register for use with e_bdnz */

/* source address of the section */
     ASM_KEYWORD(" e_lis   r8, RC_DATA_SRC@h");
     ASM_KEYWORD(" e_or2i    r8, RC_DATA_SRC@l");
     ASM_KEYWORD(" e_subi  r8,r8,4");                   /* decrement by 4 to prepare for e_stwu in loop */

/* Destination address of the section */
     ASM_KEYWORD(" e_lis   r9, RC_DATA_DEST@h");
     ASM_KEYWORD(" e_or2i    r9, RC_DATA_DEST@l");
     ASM_KEYWORD(" e_subi  r9,r9,4");                   /* decrement by 4 to prepare for e_stwu in loop */

/* Repeat */
     ASM_KEYWORD("data_copy_loop3:");
     ASM_KEYWORD(" e_lwzu  r10,4(r8)");
     ASM_KEYWORD(" e_stwu  r10,4(r9)");
     ASM_KEYWORD(" e_bdnz  data_copy_loop3");
     ASM_KEYWORD("data_copy3:");



/************/
/* .ramcode */
/************/
     ASM_KEYWORD(" e_lis   r5, RC_RAMCODE_SIZE@h");      /* Number of words */
     ASM_KEYWORD(" e_or2i    r5, RC_RAMCODE_SIZE@l");      /* Number of words */
     ASM_KEYWORD(" or.   r5, r5, r5");                     /* Number of words */
     ASM_KEYWORD(" e_beq   data_copy4");
     ASM_KEYWORD(" se_mtctr r5");                       /* configure control register for use with e_bdnz */

/* source address of the section */
     ASM_KEYWORD(" e_lis   r8, RC_RAMCODE_SRC@h");
     ASM_KEYWORD(" e_or2i    r8, RC_RAMCODE_SRC@l");
     ASM_KEYWORD(" e_subi  r8,r8,4");                   /* decrement by 4 to prepare for e_stwu in loop */

/* Destination address of the section */
     ASM_KEYWORD(" e_lis   r9, RC_RAMCODE_DEST@h");
     ASM_KEYWORD(" e_or2i    r9, RC_RAMCODE_DEST@l");
     ASM_KEYWORD(" e_subi  r9,r9,4");                   /* decrement by 4 to prepare for e_stwu in loop */

/* Repeat */
     ASM_KEYWORD("data_copy_loop4:");
     ASM_KEYWORD(" e_lwzu  r10,4(r8)");
     ASM_KEYWORD(" e_stwu  r10,4(r9)");
     ASM_KEYWORD(" e_bdnz  data_copy_loop4");
     ASM_KEYWORD("data_copy4:");



/*********************************/
/* Set the small ro data pointer */
/*********************************/
     ASM_KEYWORD(" e_lis   r2, _SDA2_BASE_@h");
     ASM_KEYWORD(" e_or2i    r2, _SDA2_BASE_@l");

/*********************************/
/* Set the small rw data pointer */
/*********************************/
     ASM_KEYWORD(" e_lis   r13, _SDA_BASE_@h");
     ASM_KEYWORD(" e_or2i    r13, _SDA_BASE_@l");

/******************************************************************/
/* Freescale Guidance 4 - Set up INTC                             */
/******************************************************************/
/******************************************************************/
/* Call Main Routine                                              */
/******************************************************************/
    /* Prepare a terminating stack record. */
    ASM_KEYWORD (" e_li r0, -1");
    ASM_KEYWORD (" e_stwu r1, -8(r1)"); /* Decrement stack by 8 bytes, (write word) */
    ASM_KEYWORD (" e_stw  r0, 4(r1)");  /* Make an illegal return address of 0xFFFFFFFF */
    ASM_KEYWORD (" e_stw  r0, 0(r1)");  /* Make an illegal back chain address of 0xFFFFFFFF */

    main();

    ASM_KEYWORD ("se_illegal"); /* SW breakpoint to stop debugging */

    while (1)
    {
    }
}
