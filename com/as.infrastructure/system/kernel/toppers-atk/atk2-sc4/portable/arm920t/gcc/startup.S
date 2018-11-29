/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2015  AS <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#define S_FRAME_SIZE        72

#define S_OLD_R0            68
#define S_PSR               64
#define S_PC                60
#define S_LR                56
#define S_SP                52

#define S_IP                48
#define S_FP                44
#define S_R10               40
#define S_R9                36
#define S_R8                32
#define S_R7                28
#define S_R6                24
#define S_R5                20
#define S_R4                16
#define S_R3                12
#define S_R2                8
#define S_R1                4
#define S_R0                0

.equ    USERMODE,           0x10
.equ    FIQMODE,            0x11
.equ    IRQMODE,            0x12
.equ    SVCMODE,            0x13
.equ    ABORTMODE,          0x17
.equ    UNDEFMODE,          0x1b
.equ    MODEMASK,           0x1f
.equ    NOINT,              0xc0

.equ    RAM_BASE,           0x00000000  /*Start address of RAM      */
.equ    ROM_BASE,           0x30000000  /*Start address of Flash    */

.equ    MPLLCON,            0x4c000004  /*Mpll control register     */
.equ    M_MDIV,             0x20
.equ    M_PDIV,             0x4
.equ    M_SDIV,             0x2

.equ    INTMSK,             0x4a000008
.equ    INTSUBMSK,          0x4a00001c
.equ    WTCON,              0x53000000
.equ    LOCKTIME,           0x4c000000
.equ    CLKDIVN,            0x4c000014  /*Clock divider control     */
.equ    GPHCON,             0x56000070  /*Port H control            */
.equ    GPHUP,              0x56000078  /*Pull-up control H         */
.equ    BWSCON,             0x48000000  /*Bus width & wait status   */
.equ    BANKCON0,           0x48000004  /*Boot ROM control          */
.equ    BANKCON1,           0x48000008  /*BANK1 control             */
.equ    BANKCON2,           0x4800000c  /*BANK2 cControl            */
.equ    BANKCON3,           0x48000010  /*BANK3 control             */
.equ    BANKCON4,           0x48000014  /*BANK4 control             */
.equ    BANKCON5,           0x48000018  /*BANK5 control             */
.equ    BANKCON6,           0x4800001c  /*BANK6 control             */
.equ    BANKCON7,           0x48000020  /*BANK7 control             */
.equ    REFRESH,            0x48000024  /*DRAM/SDRAM efresh         */
.equ    BANKSIZE,           0x48000028  /*Flexible Bank Size        */
.equ    MRSRB6,             0x4800002c  /*Mode egister set for SDRAM*/
.equ    MRSRB7,             0x48000030  /*Mode egister set for SDRAM*/

/*
 *************************************************************************
 *
 * Jump vector table
 *
 *************************************************************************
 */

.section .startup, "ax"
.code 32

.globl _start
_start:
    b       reset_handler
    ldr     pc, _vector_undef
    ldr     pc, _vector_swi
    ldr     pc, _vector_pabt
    ldr     pc, _vector_dabt
    ldr     pc, _vector_resv
    ldr     pc, _vector_irq
    ldr     pc, _vector_fiq

_vector_undef:  .word vector_undef
_vector_swi:    .word vector_swi
_vector_pabt:   .word vector_pabt
_vector_dabt:   .word vector_dabt
_vector_resv:   .word vector_resv
_vector_irq:    .word vector_irq
_vector_fiq:    .word vector_fiq

.balignl    16,0xdeadbeef

/*
 *************************************************************************
 *
 * Startup Code (reset vector)
 * relocate armboot to ram
 * setup stack
 * jump to second stage
 *
 *************************************************************************
 */

_TEXT_BASE:
    .word   TEXT_BASE

/*
 * rtthread bss start and end which are defined in linker script
 */
.globl _bss_start
_bss_start:
    .word __bss_start__

.globl _bss_end
_bss_end:
    .word __bss_end__

/* IRQ stack memory (calculated at run-time)                        */
.globl IRQ_STACK_START
IRQ_STACK_START:
    .word knl_irq_stack_top

.globl FIQ_STACK_START
FIQ_STACK_START:
    .word knl_fiq_stack_top

.globl UNDEFINED_STACK_START
UNDEFINED_STACK_START:
    .word knl_undefined_stack_top

.globl ABORT_STACK_START
ABORT_STACK_START:
    .word knl_aboknl_stack_top

.globl _STACK_START
_STACK_START:
    .word knl_system_stack_top

/* ----------------------------------entry------------------------------*/
.globl reset_handler
reset_handler:

    /* set the cpu to SVC32 mode    */
    mrs     r0,cpsr
    bic     r0,r0,#MODEMASK
    orr     r0,r0,#SVCMODE
    msr     cpsr,r0

    /* watch dog disable            */
    ldr     r0,=WTCON
    ldr     r1,=0x0
    str     r1,[r0]

    /* mask all IRQs by clearing all bits in the INTMRs                 */
    ldr     r1, =INTMSK
    ldr     r0, =0xffffffff
    str     r0, [r1]
    ldr     r1, =INTSUBMSK
    ldr     r0, =0x7fff             /*all sub interrupt disable         */
    str     r0, [r1]

    /* set interrupt vector         */
    ldr     r0, _load_address
    mov     r1, #0x0                /* target address                   */
    add     r2, r0, #0x20           /* size, 32bytes                    */

copy_loop:
    ldmia   r0!, {r3-r10}           /* copy from source address [r0]    */
    stmia   r1!, {r3-r10}           /* copy to   target address [r1]    */
    cmp     r0, r2                  /* until source end addreee [r2]    */
    ble     copy_loop

    /* setup stack */
    bl      stack_setup

     /* Copy the data segment initializers from flash to SRAM */
    ldr r0, =__data_start__  /* r0 holds start of data in ram */
    ldr r3, =__data_end__    /* r3 holds end of data in ram */
    ldr r5, =__etext         /* r5 start of data in flash */
    movs    r1, #0
    b   LoopCopyDataInit

CopyDataInit:
    ldr r4, [r5, r1]          /* read current position in flash */
    str r4, [r0, r1]          /* store current position in ram */
    adds    r1, r1, #4        /* increment counter */

LoopCopyDataInit:
    adds    r2, r0, r1        /* are we at the final position? */
    cmp r2, r3                /* ... */
    bcc CopyDataInit          /* nope, continue */
    ldr r2, =__bss_start__
    b   LoopFillZerobss

LoopFillZerobss:
    /* clear .bss */
    mov     r0,#0                    /* get a zero                       */
    ldr     r1,=__bss_start__        /* bss start                        */
    ldr     r2,=__bss_end__           /* bss end                          */

bss_loop:
    cmp     r1,r2                   /* check if data to clear           */
    strlo   r0,[r1],#4              /* clear 4 bytes                    */
    blo     bss_loop                /* loop until done                  */

    /* call C++ constructors of global objects                          */
    ldr     r0, =__ctors_start__
    ldr     r1, =__ctors_end__

ctor_loop:
    cmp     r0, r1
    beq     ctor_end
    ldr     r2, [r0], #4
    stmfd   sp!, {r0-r1}
    mov     lr, pc
    bx      r2
    ldmfd   sp!, {r0-r1}
    b       ctor_loop

ctor_end:

    /* call c_entry       */
    ldr     pc, _main

_main:
    .word main
#ifdef __FLASH_BUILD__
_load_address:
    .word ROM_BASE + _TEXT_BASE
#else
_load_address:
    .word RAM_BASE + _TEXT_BASE
#endif

/*
 *************************************************************************
 *
 * Interrupt handling
 *
 *************************************************************************
 */

/* exception handlers               */
    .align  5
vector_undef:
    b vector_undef

    .align  5
    .weak vector_swi
vector_swi:
    b vector_swi

    .align  5
vector_pabt:
    b vector_pabt

    .align  5
vector_dabt:
    b vector_dabt

    .align  5
vector_resv:
    b vector_resv

    .align  5
vector_fiq:
   b vector_fiq

stack_setup:
    mrs     r0, cpsr
    bic     r0, r0, #MODEMASK
    orr     r1, r0, #UNDEFMODE|NOINT
    msr     cpsr_cxsf, r1           /* undef mode                       */
    ldr     sp, UNDEFINED_STACK_START

    orr     r1,r0,#ABORTMODE|NOINT
    msr     cpsr_cxsf,r1            /* abort mode                       */
    ldr     sp, ABORT_STACK_START

    orr     r1,r0,#IRQMODE|NOINT
    msr     cpsr_cxsf,r1            /* IRQ mode                         */
    ldr     sp, IRQ_STACK_START

    orr     r1,r0,#FIQMODE|NOINT
    msr     cpsr_cxsf,r1            /* FIQ mode                         */
    ldr     sp, FIQ_STACK_START

    bic     r0,r0,#MODEMASK
    orr     r1,r0,#SVCMODE|NOINT
    msr     cpsr_cxsf,r1            /* SVC mode                         */

    ldr     sp, _STACK_START

    /* USER mode is not initialized. */
    mov     pc,lr                   /* The LR register may be not valid for the mode changes.*/

/*/*}*/
	.section .text
    .global Irq_Restore
    .type   Irq_Restore, %function
/* void Irq_Restore( imask_t intsts ); */
Irq_Restore:
    msr cpsr, r0
    mov pc, lr

    .global __Irq_Save
    .type   __Irq_Save, %function
/* imask_t __Irq_Save( void ); */
__Irq_Save:
    mrs r0, cpsr
    orr r1, r0, #NOINT
    msr cpsr_c, r1
    mov pc, lr

/* void x_lock_all_int(void)   */
    .global tpl_disable_os_interrupts
    .type   tpl_disable_os_interrupts, %function
    .global x_lock_all_int
    .type   x_lock_all_int, %function
    .global Irq_Disable
    .type   Irq_Disable, %function
tpl_disable_os_interrupts:
x_lock_all_int:
Irq_Disable:
    mrs r0, cpsr
    orr r0, r0, #NOINT
    msr cpsr_c, r0
    mov pc, lr

/* void x_unlock_all_int(void) */
	.global tpl_enable_os_interrupts
	.type   tpl_enable_os_interrupts, %function
    .global x_unlock_all_int
    .type   x_unlock_all_int, %function
    .global Irq_Enable
    .type   Irq_Enable, %function
tpl_enable_os_interrupts:
x_unlock_all_int:
Irq_Enable:
    mrs r0, cpsr
    bic r0, r0, #NOINT
    msr cpsr_c, r0
    mov pc, lr

	.global vector_irq
	.weak   vector_irq
	.type   vector_irq, %function
	.extern knl_isr_handler
vector_irq:
    /* store caller-saved registers */
    stmfd sp!, {r0-r3,r9,r11,ip,lr}

	bl Irq_Disable

    bl knl_isr_handler

	bl Irq_Enable
 	/* restore caller-saved registers */
    ldmfd sp!, {r0-r3,r9,r11,ip,lr}

    /* return to interrupted task */
    subs pc,lr,#4
