#/**
#    @file        Vector_vle_core.s
#    @version     2.0.0
#
#    @brief       AUTOSAR Sample_app - Core Vector Table.
#    @details     Core Vector Table.
#
#    Project      : AUTOSAR 3.0 MCAL
#    Platform     : PA
#    Peripheral   : 
#    Dependencies : Base Det Dem Port Dio Mcu SchM Wdg WdgIf CanIf LinIf EcuM
#
#    Autosar Version       : 1.9.0
#    Autosar Revision      : ASR_REL_1_9_REV_0003
#    Autosar Conf. Variant :
#    Software Version      : 2.0.0
#    Build Version         : MPC563xMxM_MCAL_2_0_0_RTM_ASR_REL_1_9_REV_0003_20110214
#
#    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
#    All Rights Reserved.
#*/
#/*==================================================================================================
##==================================================================================================*/
# Note: The user interrupt service routines must create entry and exit code
# (either with assembly code or with __interrupt keyword). If not the code
# will not exit interrupts properly.

#===============================================================
# Set the compiler using generated file by BEART
#===============================================================
    .set COMPILER_GHS,  0
    .set COMPILER_DIAB, 1
    .set COMPILER_CW,   2

    .include "compiler_used.s"

#===============================================================
# Compiler selection
#===============================================================
    .if COMPILER_USED == COMPILER_GHS
        .set C_GHS,  1         # 0/1 - off/on
        .set C_DIAB, 0         # 0/1 - off/on
        .set C_CW,   0         # 0/1 - off/on
        .set ALIGN_SIZE,   4
    .else
    .if COMPILER_USED == COMPILER_DIAB
        .set C_GHS,  0         # 0/1 - off/on
        .set C_DIAB, 1         # 0/1 - off/on
        .set C_CW,   0         # 0/1 - off/on
        .set ALIGN_SIZE,   4
    .else
    .if COMPILER_USED == COMPILER_CW
        .set C_GHS,  0         # 0/1 - off/on
        .set C_DIAB, 0         # 0/1 - off/on
        .set C_CW,   1         # 0/1 - off/on
        .set ALIGN_SIZE,   16
    .endif
    .endif
    .endif

#===============================================================
# Compiler selection
#===============================================================
    .set    RCW, 0x015a0000

#===============================================================
# put reset configuration halfword and application start address
# into .rcw section
#===============================================================
    .if C_CW == 1
         .extern __start
         .section .rcw,text
         .long RCW, __start
    .else
         .extern _start
         .section ".rcw","ax"
         .long RCW, _start
    .endif

#===============================================================
# put remaining code in this file into .isrvectbl_core section
#===============================================================
    .if C_GHS == 1
       .vle
       .section ".isrvectbl_core","avx"
    .endif

    .if C_DIAB == 1
       .section ".isrvectbl_core","ax"
    .endif

    .if C_CW == 1
       .section .isrvectbl_cw_core, text_vle
    .endif

#===============================================================
# define symbols as global to allow easier debugging
#===============================================================
    .globl IVOR0_Handler
	.globl IVOR1_Handler
	.globl IVOR2_Handler
	.globl IVOR3_Handler
	.globl IVOR4_Handler
	.globl IVOR5_Handler
	.globl IVOR6_Handler
	.globl IVOR7_Handler
	.globl IVOR8_Handler
	.globl IVOR9_Handler
	.globl IVOR10_Handler
	.globl IVOR11_Handler
	.globl IVOR12_Handler
	.globl IVOR13_Handler
	.globl IVOR14_Handler
	.globl IVOR15_Handler
	.globl IVOR32_Handler
	.globl IVOR33_Handler
	.globl IVOR34_Handler
	.globl Wdg_Isr

    .globl CoreVectorTable

#===============================================================
#               Core vector TABLE
#===============================================================
CoreVectorTable:
    .align ALIGN_SIZE
IVOR0_Handler:
    e_b Wdg_Isr   # IVOR0 - 0x1000 - Critical Input (SPR 400)
    .align ALIGN_SIZE
IVOR1_Handler:
    e_b .         # IVOR1 - 0x1010 - Machine Check Interrupt (SPR 401)
    .align ALIGN_SIZE
IVOR2_Handler:
    e_b .         # IVOR2 - 0x1020 - Data Storage Interrupt (SPR 402)
    .align ALIGN_SIZE
IVOR3_Handler:
    e_b .         # IVOR3 - 0x1030 - Instruction Storage Interrupt (SPR 403)
    .align ALIGN_SIZE
IVOR4_Handler:
    e_b .         # IVOR4 - 0x1040 - External Input Interrupt (SPR 404)
    .align ALIGN_SIZE
IVOR5_Handler:
    e_b .         # IVOR5 - 0x1050 - Alignment Interrupt (SPR 405)
    .align ALIGN_SIZE
IVOR6_Handler:
    e_b .         # IVOR6 - 0x1060 - Program Interrupt (SPR 406)
    .align ALIGN_SIZE
IVOR7_Handler:
    e_b .         # IVOR7 - 0x1070 - Floating Point Interrupt (SPR 407)
    .align ALIGN_SIZE
IVOR8_Handler:
    e_b .         # IVOR8 - 0x1080 - System Call Interrupt (SPR 408)
    .align ALIGN_SIZE
IVOR9_Handler:
    e_b .         # IVOR9 - 0x1090 - Auxilary Processor (SPR 409)
    .align ALIGN_SIZE
IVOR10_Handler:
    e_b .         # IVOR10 - 0x10A0 - Decrementer interrupt (SPR 410)
    .align ALIGN_SIZE
IVOR11_Handler:
    e_b .         # IVOR11 - 0x10B0 - Fixed interval timer interrupt (SPR 411)
    .align ALIGN_SIZE
IVOR12_Handler:
    e_b .         # IVOR12 - 0x10C0 - Watchdog Timer Interrupt (SPR 412)
    .align ALIGN_SIZE
IVOR13_Handler:
    e_b .         # IVOR13 - 0x10D0 - Data TLB Error interrupt (SPR 413)
    .align ALIGN_SIZE
IVOR14_Handler:
    e_b .         # IVOR14 - 0x10E0 - Instruction TLB Error interrupt (SPR 414)
    .align ALIGN_SIZE
IVOR15_Handler:
    e_b .         # IVOR15 - 0x10F0 - Debug (SPR 415)
    .align ALIGN_SIZE
IVOR32_Handler:
    e_b .         # IVOR32 - 0x1100 - SPE APU unavailable (SPR 528)
    .align ALIGN_SIZE
IVOR33_Handler:
    e_b .         # IVOR33 - 0x1110 - SPE floating point data exception (SPR 529)
    .align ALIGN_SIZE
IVOR34_Handler:
    e_b .         # IVOR34 - 0x1120 - SPE floating point round exception (SPR 530)
