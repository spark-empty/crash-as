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
/* ============================ [ INCLUDES  ] ====================================================== */

#include "portoffset.h"

    .extern p_runtsk, p_schedtsk, knl_taskindp
    .extern callevel_stat,,activate_r,knl_dispatch_started
    .extern knl_system_stack_top

.equ    USERMODE,           0x10
.equ    FIQMODE,            0x11
.equ    IRQMODE,            0x12
.equ    SVCMODE,            0x13
.equ    ABORTMODE,          0x17
.equ    UNDEFMODE,          0x1b
.equ    MODEMASK,           0x1f
.equ    NOINT,              0xc0

    .section .text

    .global  knl_dispatch_r
    .type   knl_dispatch_r, %function
knl_dispatch_r:
    ldmfd   sp!, {r0}
    msr     spsr, r0
    ldmfd   sp!, {r0-r12, lr, pc}^

dispatch_task:
    ldr     r2,[r0,TCB_PC_OFFSET]
    mov     pc,r2

    .global knl_start_dispatch
    .type   knl_start_dispatch, %function
knl_dispatch_ret_int:
knl_start_dispatch:
    ldr     r0, =p_schedtsk
    ldr     r0, [r0]
    ldr     r1, =p_runtsk
    str     r0, [r1]

    ldr     sp, [r0, TCB_SP_OFFSET ]
    b       dispatch_task

    .global knl_dispatch_entry
    .type   knl_dispatch_entry, %function
knl_dispatch_entry:
	stmfd   sp, {r0-r2}
	sub     r0, sp, #12
	sub     r1, lr, #0              /* Adjust PC for return address to task */
	mrs     r2, cpsr
	stmfd   sp!, {r1}               /* Push task''s PC */
	stmfd   sp!, {r3-r12, lr}       /* Push task''s LR,R12-R4 */
	ldmfd   r0!, {r3-r5}            /* Load Task''s R0-R2 from stack */
	stmfd   sp!, {r3-r5}            /* Push Task''s R0-R2 to SVC stack */
	stmfd   sp!, {r2}               /* Push task''s SPSR */

    ldr     r3, =p_runtsk
    ldr     r4, [r3]

    str     sp, [r4, TCB_SP_OFFSET]

    ldr     r12, =knl_dispatch_r
    str     r12, [r4, TCB_PC_OFFSET]

    b knl_start_dispatch

    .global vector_irq
    .extern knl_isr_handler
    .type   vector_irq, %function
vector_irq:
    /* Save Context To task SVC stack */
    stmfd   sp, {r0-r2}
EnterISR:
    ldr     r0, = knl_dispatch_started
    ldr     r0, [r0]
    cmp     r0, #0
    beq     l_nosave    /* system not startd */

    ldr     r0, =knl_taskindp
    ldr     r2, [r0]
    add     r2, r2, #1  /* knl_taskindp++ */
    str     r2, [r0]

    cmp     r2, #1      /* previous knl_taskindp==0 */
    bne     l_nosave

    /* save context on fisrt ISR enter                                          */
    /* now R0 R1 R2 have all saved to IRQ's stack before,but no adjust to SP    */
    /*------------------------------------------------------------------------  */
    /*   R0--SP                                                                 */
    /*   R1--PC                                                                 */
    /*   R2--SPSR                                                               */
    /*------------------------------------------------------------------------  */

    sub     r0, sp, #12
    sub     r1, lr, #4              /* Adjust PC for return address to task */
    mrs     r2, spsr                /* Copy SPSR (Task CPSR) */
    msr     cpsr_c, #SVCMODE|NOINT /* Change to SVC mode,that is task's mode */
                                    /* SAVE TASK''S CONTEXT ONTO OLD TASK''S STACK */
    stmfd   sp!, {r1}               /* Push task''s PC */
    stmfd   sp!, {r3-r12, lr}       /* Push task''s LR,R12-R4 */
    ldmfd   r0!, {r3-r5}            /* Load Task''s R0-R2 from IRQ stack */
    stmfd   sp!, {r3-r5}            /* Push Task''s R0-R2 to SVC stack */
    stmfd   sp!, {r2}               /* Push task''s SPSR */

    ldr     r3, =p_runtsk
    ldr     r4, [r3]

    str     sp, [r4, TCB_SP_OFFSET]

    ldr     r12, =knl_dispatch_r
    str     r12, [r4, TCB_PC_OFFSET]

l_nosave:
    stmfd   sp!, {lr}     /* push {lr} */
    ldr     r1, = callevel_stat
    ldrh    r3, [r1]
    stmfd   sp!, {r3}
    mov     r3, #2   /* callevel = TCL_ISR2 */
    strh    r3,[r1]

    //mrs r0, cpsr
    //bic r0, r0, #NOINT  /* interrupt enable */
    //msr cpsr_c, r0

    bl knl_isr_handler

ExitISR:
    ldmfd   sp!, {r3}
    ldr     r1, = callevel_stat
    strh    r3, [r1]

    ldmfd   sp!, {lr}

    //mrs r0, cpsr
    //orr r0, r0, #NOINT  /* interrupt disable */
    //msr cpsr_c, r0

    ldr     r0, = knl_dispatch_started
    ldr     r0, [r0]
    cmp     r0, #0
    beq     l_nodispatch

    ldr     r0, =knl_taskindp
    ldr     r1, [r0]
    sub     r1, r1, #1
    str     r1, [r0]
    cmp     r1, #0
    bne     l_nodispatch

    b     knl_dispatch_ret_int                 /* To dispatch processing */

l_nodispatch:
    subs pc, lr, #4
