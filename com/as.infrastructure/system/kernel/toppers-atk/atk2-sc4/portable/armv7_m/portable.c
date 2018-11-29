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
#include "Mcu.h"
/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
extern void knl_activate_r(void);
#if (ISR_NUM > 0)
extern const FunctionRefType tisr_pc[ISR_NUM];
#endif
extern const uint32 __vector_table[];
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
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void x_nested_lock_os_int(void){}
void x_nested_unlock_os_int(void){}
void x_lock_all_int(void)  { __asm("cpsid   i"); }
void x_unlock_all_int(void){ __asm("cpsie   i"); }
void Irq_Enable(void)
{
	x_unlock_all_int();
}
void Irq_Disable(void)
{
	x_lock_all_int();
}
void x_config_int(InterruptNumberType intno,AttributeType attr,PriorityType prio){
	(void)attr;
	NVIC_SetPriority(intno,prio);
}
boolean x_is_called_in_c1isr(void) {
	return FALSE;
}
void    x_set_ipm_c2isr_disable(void) {

}
boolean target_is_int_controllable(InterruptNumberType intno) {
	(void)intno;
	return FALSE;
}
void    x_enable_int(InterruptNumberType intno) {
	NVIC_EnableIRQ(intno);
}
void    x_disable_int(InterruptNumberType intno) {
	NVIC_DisableIRQ(intno);
}

void target_initialize(void) {
	const uint32_t* pSrc;

	pSrc = __vector_table ;

#if defined(CHIP_AT91SAM3S)
	SCB->VTOR = ( (uint32_t)pSrc & SCB_VTOR_TBLOFF_Msk ) ;
	if ( ((uint32_t)pSrc >= IRAM_ADDR) && ((uint32_t)pSrc < IRAM_ADDR+IRAM_SIZE) )
	{
		SCB->VTOR |= 1 << SCB_VTOR_TBLBASE_Pos ;
	}

	WDT_Disable(WDT);
	/* Low level Initialize */
	LowLevelInit() ;
#else
	SCB->VTOR = (uint32_t)pSrc;
#endif

	OsTickCounter = 1;
	knl_taskindp = 0;
	knl_dispatch_started = FALSE;

	if (SysTick_Config(McuE_GetSystemClock() / 1000)) { /* Capture error */ while (1); }
}
void target_exit(void)       {}
void target_tp_initialize(void) {}
void target_tp_terminate(void) {}
void target_tp_start_timer(TickType tick) {
	(void)tick;
}
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

void x_set_ipm(PriorityType prio){
	(void)prio;
}
PriorityType x_get_ipm(void){
	return 0;
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

void dispatch(void){
	__asm("cpsie   i");
	SCB->ICSR = SCB_ICSR_PENDSVSET_Msk;
}
void start_dispatch(void){
	knl_dispatch_started=TRUE;
	__asm("cpsie   i");
	__asm("svc 0");
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
void activate_context(TCB* tcb) {
	tcb->tskctxb.pc = knl_activate_r;
	tcb->tskctxb.sp = (void*)(((uint32_t)tcb->p_tinib->sstk) + ((uint32_t)tcb->p_tinib->sstksz));
}
StatusType trustedfunc_stack_check(MemorySizeType sz){
	(void)sz;
	return FALSE;
}
AccessType probe_trusted_osap_mem(MemoryStartAddressType sadr, MemoryStartAddressType eadr) {
	(void)sadr;(void)eadr;
	return AP_NoAccess;
}

void knl_system_tick_handler(void)
{

	OsTickCounter ++;

	if(0 == OsTickCounter)
	{
		OsTickCounter = 1;
	}

	if(knl_dispatch_started == TRUE)
	{
		IncrementCounter(0);
	}
#if defined(CHIP_AT91SAM3S)
	TimeTick_Increment();
#endif
}
void knl_isr_handler(uint32 intno)
{
#if (ISR_NUM > 0)
	if( (intno>15) &&  (intno<(16+ISR_NUM)) && (tisr_pc[intno-16]!=NULL))
	{
		tisr_pc[intno-16]();
	}
	else
#endif
	{
		ShutdownOS(0xFF);
	}
}

void nmi_handler(void) 			{ printf("nmi_handler\n");while(1);}
void hard_fault_handler(void)	{ printf("hard_fault_handler\n");while(1);}
void mpu_fault_handler(void)	{ printf("mpu_fault_handler\n");while(1);}
void bus_fault_handler(void)	{ printf("bus_fault_handler\n");while(1);}
void usage_fault_handler(void)	{ printf("usage_fault_handler\n");while(1);}
void debug_monitor_handler(void){ printf("debug_monitor_handler\n");while(1);}
