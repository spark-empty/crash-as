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
/* ============================ [ INCLUDES  ] ====================================================== */
#define MACROS_ONLY
#include "Os_Cfg.h"
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
	.extern Irq_Enable
	.extern Irq_Disable
	.extern Os_PortIsrHandler
	.extern Sched_Preempt
/* ============================ [ DATAS     ] ====================================================== */
	.extern RunningVar
	.extern ReadyVar
	.extern CallLevel
	.extern ISR2Counter
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
	.section .text

Os_PortIdle:
	/* set RunningVar to NULL */

l_idle:


	.global Os_PortStartDispatch
	.type   Os_PortStartDispatch, %function
/* void Os_PortStartDispatch( void ); */
Os_PortStartDispatch:

Os_PortDispatchFormISR:


	.global Os_PortResume
	.type   Os_PortResume, %function
Os_PortResumePreHook:
	#ifdef OS_USE_PRETASK_HOOK

	#endif
Os_PortResume:


	.global Os_PortDispatch
	.type   Os_PortDispatch, %function
Os_PortDispatch:

	.global vector_irq
	.type   vector_irq, %function
vector_irq:
	/* Save working register to IRQ stack */

EnterISR:
	/* save context on fisrt ISR enter                                          */


l_nosave:

ExitISR:


	#ifdef OS_USE_PRETASK_HOOK

	#endif


l_nopreempt:


l_nodispatch:

