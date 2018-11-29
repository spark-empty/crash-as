/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2018  AS <parai@foxmail.com>
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
.extern __bss_start
.extern __bss_end
.extern main

	.section .init
	.globl _start
;;
_start:

reset:
	ldr x30, =stack_top
	mov sp, x30
	b main
	b .

	.section .text
    .global Irq_Restore
    .type   Irq_Restore, %function
/* void Irq_Restore( imask_t intsts ); */
Irq_Restore:
	ret

    .global __Irq_Save
    .type   __Irq_Save, %function
/* imask_t __Irq_Save( void ); */
__Irq_Save:
	ret

/* void Irq_Disable(void)   */
    .global Irq_Disable
    .type   Irq_Disable, %function
Irq_Disable:
	ret
/* void Irq_Enable(void) */
    .global Irq_Enable
    .type   Irq_Enable, %function
Irq_Enable:
	ret
