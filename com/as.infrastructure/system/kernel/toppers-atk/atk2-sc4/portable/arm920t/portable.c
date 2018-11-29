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
#include "s3c2440.h"
#include "Mcu.h"
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
extern void knl_start_dispatch(void);
extern void knl_activate_r(void);
extern void knl_dispatch_entry(void);
#if (ISR_NUM > 0)
extern const FunctionRefType tisr_pc[ISR_NUM];
#endif
extern uint32_t knl_system_stack;
#ifdef TOPPERS_OSTKPT
extern uint32_t knl_system_stack_top;
#endif
extern const uint32_t  knl_system_stack_size;
/* ============================ [ DATAS     ] ====================================================== */
TickType OsTickCounter;
uint32 knl_taskindp;
StackType * const	_ostk = (StackType *)&knl_system_stack;
const MemorySizeType	_ostksz = (MemorySizeType)&knl_system_stack_size;
#ifdef TOPPERS_OSTKPT
StackType * const	_ostkpt[1024] = (StackType *)&knl_system_stack_top;
#endif /* TOPPERS_OSTKPT */
uint32 knl_dispatch_started;
static uint32 nested_lock = 0;
static imask_t nested_imask;
/* ============================ [ LOCALS    ] ====================================================== */

/* ============================ [ FUNCTIONS ] ====================================================== */

void x_nested_lock_os_int(void)
{
	nested_lock ++;
	if(1 == nested_lock)
		Irq_Save(nested_imask);
}
void x_nested_unlock_os_int(void)
{
	asAssert(nested_lock>0);
	nested_lock--;
	if(0 == nested_lock)
		Irq_Restore(nested_imask);
}

void x_config_int(InterruptNumberType intno,AttributeType attr,PriorityType prio){

}
boolean x_is_called_in_c1isr(void) {
	return FALSE;
}
void    x_set_ipm_c2isr_disable(void) {}
boolean target_is_int_controllable(InterruptNumberType intno) {
	return FALSE;
}
void    x_enable_int(InterruptNumberType intno) {
	if(intno < 32)
	{
		INTMSK &= ~(1<<intno);
	}
	else if(intno < 46)
	{
		INTSUBMSK &= ~(1<<(intno-32));
	}
	else
	{
		asAssert(0);
	}
}

void    x_disable_int(InterruptNumberType intno) {
	if(intno < 32)
	{
		INTMSK |= (1<<intno);
	}
	else if(intno < 46)
	{
		INTSUBMSK |= (1<<(intno-32));
	}
	else
	{
		asAssert(0);
	}
}

void x_clear_int(InterruptNumberType intno)
{
	if(intno < 32)
	{
		SRCPND |= (1<<intno);
		INTPND = INTPND;
	}
	else if(intno < 46)
	{
		SUBSRCPND |= (1<<(intno-32));
	}
	else
	{
		asAssert(0);
	}
}

void target_initialize(void) {
	OsTickCounter = 1;
	knl_taskindp = 0;
	knl_dispatch_started = FALSE;
	nested_lock = 0;
	/* timer4, pre = 15+1 */
	TCFG0 &= 0xffff00ff;
	TCFG0 |= 15 << 8;
	/* all are interrupt mode,set Timer 4 MUX 1/4 */
	TCFG1  &= 0xfff0ffff;
	TCFG1  |= 0x00010000;

	TCNTB4 = (uint32_t)(McuE_GetSystemClock() / (4 *16* 1000)) - 1;	/* 1000 ticks per second */
	/* manual update */
	TCON = TCON & (~(0x0f<<20)) | (0x02<<20);

	/* enable interrupt */
	INTMSK &= ~BIT_TIMER4;

    /* start timer4, reload */
	TCON = TCON & (~(0x0f<<20)) | (0x05<<20);
}
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
void dispatch(void){
	knl_dispatch_entry();
}
void start_dispatch(void){
	knl_dispatch_started = TRUE;
	knl_start_dispatch();
}
void exit_and_dispatch(void){
	#ifdef CFG_USE_POSTTASKHOOK
	call_posttaskhook();
	#endif
	start_dispatch();
}
void exit_and_dispatch_nohook(void){
	start_dispatch();
}
void activate_force_term_osap_main(TCB* tcb){
	(void)tcb;
}
void activate_r(void)
{
    p_runtsk->curpri = p_runtsk->p_tinib->exepri;
	#ifdef CFG_USE_PRETASKHOOK
	call_pretaskhook();
	#endif
	ENTER_CALLEVEL(TCL_TASK);
    x_unlock_all_int();
    p_runtsk->p_tinib->task();
}
void activate_context(TCB* tcb) {
	tcb->tskctxb.pc = activate_r;
	tcb->tskctxb.sp = (void*)(((uint32_t)tcb->p_tinib->sstk) + ((uint32_t)tcb->p_tinib->sstksz));
}
StatusType trustedfunc_stack_check(MemorySizeType sz){
	return FALSE;
}
AccessType probe_trusted_osap_mem(MemoryStartAddressType sadr, MemoryStartAddressType eadr) {
	return AP_NoAccess;
}

ISR(TIMER4)
{
	OsTickCounter ++;
	if(0 == OsTickCounter)
	{
		OsTickCounter = 1;
	}
	if(knl_dispatch_started)
	{
		IncrementCounter(0);
	}
}

void knl_isr_handler(void)
{
	uint32_t intno;

	intno = INTOFFSET;
	if(intno < ISR_NUM)
	{
		if(tisr_pc[intno] != NULL)
		{
			x_disable_int(intno);
			tisr_pc[intno]();
			x_enable_int(intno);
		}
		else
		{
			internal_shutdownos(0xFF);
		}

		x_clear_int(intno);
	}
	else
	{
		internal_shutdownos(0xFF);
	}
}

void __ffssi2(void)
{
	return;
}
