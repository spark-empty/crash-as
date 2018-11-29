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
#include "Os.h"
#include "kernel_impl.h"
#include "osap.h"
#include "counter.h"
#include "interrupt.h"
#include "scheduletable.h"
#include "task.h"
#include "alarm.h"
#include "ioc_impl.h"
#include "memory.h"
/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
TickType OsTickCounter;
static StackType knl_system_stack[1024];
StackType * const	_ostk = knl_system_stack;
const MemorySizeType	_ostksz = sizeof(knl_system_stack);
#ifdef TOPPERS_OSTKPT
StackType	_ostkpt[1024];
#endif /* TOPPERS_OSTKPT */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
imask_t __Irq_Save(void)
{
	return 0;
}
void Irq_Restore(imask_t irq_state)
{
	(void)irq_state;
}

void x_nested_lock_os_int(void){}
void x_nested_unlock_os_int(void){}
void x_lock_all_int(void){}
void x_unlock_all_int(void){}
void x_config_int(InterruptNumberType intno,AttributeType attr,PriorityType prio){}
boolean x_is_called_in_c1isr(void) {
	return FALSE;
}
void    x_set_ipm_c2isr_disable(void) {}
boolean target_is_int_controllable(InterruptNumberType intno) {
	return FALSE;
}
void    x_enable_int(InterruptNumberType intno) {}
void    x_disable_int(InterruptNumberType intno) {}

void target_initialize(void) {}
void target_exit(void)       {}
void target_tp_initialize(void) {}
void target_tp_terminate(void) {}
void target_tp_start_timer(TickType tick) {}
TickType target_tp_stop_timer(void) {
	return 0;
}
void target_clear_tp_fault_status(void){}
void target_clear_tp_timer_status(void) {}
TickType target_tp_get_remaining_ticks(void){
	return 0;
}
TickType target_tp_get_elapsed_ticks(void){
	return 1;
}
boolean  target_tp_sense_interrupt(void){
	return FALSE;
}

void x_set_ipm(PriorityType prio){}
PriorityType x_get_ipm(void){
	return 0;
}

void dispatch(void){}
void start_dispatch(void){}
void exit_and_dispatch(void){}
void exit_and_dispatch_nohook(void){}
void activate_force_term_osap_main(TCB* tcb){}
void activate_context(TCB* tcb) {}
StatusType trustedfunc_stack_check(MemorySizeType sz){
	return FALSE;
}
AccessType probe_trusted_osap_mem(MemoryStartAddressType sadr, MemoryStartAddressType eadr) {
	return AP_NoAccess;
}

