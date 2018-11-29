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
    .syntax unified
    .cpu cortex-m3
    .fpu softvfp
    .thumb
#define _MACRO_ONLY
#include "portable.h"

    .extern p_runtsk, p_schedtsk, knl_taskindp
    .extern callevel_stat,,activate_r,knl_dispatch_started
    .extern knl_system_stack_top

    .section .text
    .global Irq_Restore
    .type   Irq_Restore, %function
/* void Irq_Restore( imask_t intsts ); */
Irq_Restore:
    mrs     r1, primask
    msr     primask, r0
    mov     r0, r1
    bx      lr

    .global __Irq_Save
    .type   __Irq_Save, %function
/* imask_t __Irq_Save( void ); */
__Irq_Save:
    mrs     r0, primask
    ldr     r1, = 0x1 /* TS_PMK_D */
    msr     primask, r1
    bx      lr

    .global knl_activate_r
    .type   knl_activate_r, %function
knl_activate_r:
    mov r3, #0x01000000 /* TS_PSR_T */
    ldr r2, =activate_r
    push {r2,r3}
    subs  sp,sp,#24
    bx lr

    .global  knl_dispatch_r
    .type   knl_dispatch_r, %function
knl_dispatch_r:
     /* start to restore task's context */
    pop     {r4-r11}
    cpsie   i
    dsb
    isb
    bx      lr

dispatch_task:
    ldr     r2,[r0,#40]  /* check TCB_PC_OFFSET */
    bx      r2

    .global knl_start_dispatch
    .type   knl_start_dispatch, %function
knl_dispatch_ret_int:
knl_start_dispatch:
    /* lr must be 0xFFFFFFF9, if compiler is gcc, I don't know why fisrt times it is 0xFFFFFFF1,
     * so that hard_fault.
     * I want to say shit, why IAR is OK with the same code
     */
    ldr lr, =0xFFFFFFF9 /* force it to process mode and use MSP */
    ldr     r0, =p_schedtsk
    ldr     r0, [r0]
    ldr     r1, =p_runtsk
    str     r0, [r1]

    ldr     sp, [r0, #36 ]  /* check TCB_SP_OFFSET */
    b       dispatch_task

    .global knl_dispatch_entry
    .type   knl_dispatch_entry, %function
knl_dispatch_entry:
    push    {r4-r11}

    ldr     r1, =p_runtsk
    ldr     r0, [r1]

    str     sp, [r0, #36]  /* check TCB_SP_OFFSET */

    ldr     r12, =knl_dispatch_r
    str     r12, [r0, #40]  /* check TCB_PC_OFFSET */

    b       knl_start_dispatch

    .global EnterISR
    .type   EnterISR, %function
EnterISR:
    ldr     r1, =knl_taskindp
    ldr     r2, [r1]

    cmp     r2, #0      /* knl_taskindp==0 */
    bne     l_nosave

    ldr     r3, = knl_dispatch_started
    ldr     r3, [r3]
    cmp     r3, #0
    beq     l_nosave    /* system not startd */

    /* save context on fisrt ISR enter */
    push    {r4-r11}

    ldr     r3, =p_runtsk
    ldr     r4, [r3]

    str     sp, [r4, #36]  /* check TCB_SP_OFFSET */

    ldr     r12, =knl_dispatch_r
    str     r12, [r4, #40]  /* check TCB_PC_OFFSET */
    /* and then load isr system stack */
    ldr     sp, =knl_system_stack_top  /* Set system stack */

l_nosave:
    push    {r0}    /* push {lr} */
    add     r3, r2, #1
    str     r3, [r1]
    push    {r1, r2}
    ldr     r1, = callevel_stat
    ldrh    r3, [r1]
    push    {r3}
    orr.w   r3, r3, #2    /* callevel = TCL_ISR2 */
    strh    r3,[r1]
    cpsie   i
    bx      lr


    .global ExitISR
    .type   ExitISR, %function
ExitISR:
    pop     {r3}
    ldr     r1, = callevel_stat
    strh    r3, [r1]
    pop     {r1,r2}
    str     r2, [r1]
    pop     {lr}
    cpsid   i

    ldr     r0, =knl_taskindp
    ldr     r0, [r0]
    cmp     r0, #0
    bne     l_nodispatch

    ldr     r0, = knl_dispatch_started
    ldr     r0, [r0]
    cmp     r0, #0
    beq     l_nodispatch

    b     knl_dispatch_ret_int                 /* To dispatch processing */

l_nodispatch:
    cpsie   i
    bx      lr

    .extern knl_system_tick_handler
    .global knl_system_tick
    .type   knl_system_tick, %function
knl_system_tick:
    mov r0,lr
    bl EnterISR
    bl knl_system_tick_handler
    b  ExitISR

    .global knl_isr_process
    .extern knl_isr_handler
    .type   knl_isr_process, %function
knl_isr_process:
    mov r0,lr
    bl EnterISR
    mrs     r0, ipsr                             /* r0 = dintno */
    bl knl_isr_handler
    b  ExitISR

