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
#include "osek_kernel.h"
#include "task.h"
#include "Mcu.h"
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
extern void knl_activate_r(void);
/* ============================ [ DATAS     ] ====================================================== */
uint32 knl_taskindp;
#ifndef __GNUC__
uint32 knl_system_stack[SYSTEM_STACK_SIZE/sizeof(uint32)];
#endif
VP tcxb_sp[TASK_NUM];
FP tcxb_pc[TASK_NUM];
#if (ISR_NUM > 0)
extern const FP tisr_pc[ISR_NUM];
#endif

extern const uint32 __vector_table[];
uint32 knl_dispatch_started;
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifdef __GNUC__
void Irq_Enable(void)
{
	enable_int();
}
void Irq_Disable(void)
{
	disable_int();
}
#endif
void set_ipl(IPL ipl)
{
	if(ipl > 0)
	{
		disable_int();
	}
}
IPL  current_ipl(void)
{
	return 0;
}
void activate_r(void)
{
    tcb_curpri[runtsk] = tinib_exepri[runtsk];
    callevel = TCL_PREPOST;
    PreTaskHook();
    callevel = TCL_TASK;
    enable_int();
    tinib_task[runtsk]();
}
void activate_context(TaskType TaskID)
{
    tcxb_pc[TaskID] = (FP)knl_activate_r;

	tcxb_sp[TaskID] = (VP)( (UINT32)tinib_stk[TaskID] + (UINT32)tinib_stksz[TaskID]);
}
void cpu_terminate(void)
{

}
void sys_exit(void)
{

}

void cpu_initialize(void)
{
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

	knl_taskindp = 0;
	knl_dispatch_started = FALSE;

	if (SysTick_Config(McuE_GetSystemClock() / 1000)) { /* Capture error */ while (1); }

}

void knl_system_tick_handler(void)
{
	if(knl_dispatch_started == TRUE)
	{
		SignalCounter(0);
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

void sys_initialize(void)
{

}
void tool_initialize(void)
{

}

#if 0 /* __GNUC__ */
void __naked Irq_Restore( imask_t intsts )
{
	(void)intsts;
	__asm__ volatile("mrs     r1, primask	");
	__asm__ volatile("msr     primask, r0	");
	__asm__ volatile("mov     r0, r1		");
	__asm__ volatile("bx      lr			");
}

imask_t __naked __Irq_Save( void )
{
	__asm__ volatile("mrs     r0, primask	");
	__asm__ volatile("ldr     r1, =0x01  	");	/* =TS_PMK_D*/
	__asm__ volatile("msr     primask, r1	");
	__asm__ volatile("bx      lr			");
	return 0;
}

void __naked knl_activate_r(void)
{
	__asm__ volatile("mov 	r3, #0x01000000	"); /* TS_PSR_T */
	__asm__ volatile("ldr 	r2, =activate_r ");
	__asm__ volatile("push 	{r2,r3}			");
	__asm__ volatile("subs  sp,sp,#0x18		"); /* sp = sp - 6*4 */
	__asm__ volatile("bx 	lr				");
}

void __naked __balign(4) knl_dispatch_r(void)
{
     /* start to restore task's context */
	__asm__ volatile("pop     {r4-r11}	");
	__asm__ volatile("cpsie   i			");
	__asm__ volatile("bx      lr		");
}

void __naked dispatch_task(void)
{
	__asm__ volatile("ldr     r2, =tcxb_pc		");
	__asm__ volatile("ldr     r3,[r2,r0,LSL #2]	");
	__asm__ volatile("bx      r3				");
}
#define knl_dispatch_ret_int knl_start_dispatch
void __naked knl_start_dispatch(void)
{
	__asm__ volatile("ldr     r0, =schedtsk			");
	__asm__ volatile("ldrb    r0, [r0]				");
	__asm__ volatile("ldr     r1, =runtsk			");
	__asm__ volatile("strb    r0, [r1]				");

	__asm__ volatile("ldr     r2, =tcxb_sp			");
	__asm__ volatile("ldr     sp, [r2,r0, LSL #2]	");
	__asm__ volatile("b       dispatch_task			");
}

void __naked knl_dispatch_entry(void)
{
	__asm__ volatile("push    {r4-r11}				");

	__asm__ volatile("ldr     r1, =runtsk			");
	__asm__ volatile("ldrb    r0, [r1]				");

	__asm__ volatile("ldr     r2, =tcxb_sp			");
	__asm__ volatile("str     sp, [r2,r0, LSL #2]	");

	__asm__ volatile("ldr     r2, =tcxb_pc			");

	__asm__ volatile("ldr     r12, =knl_dispatch_r	");
	__asm__ volatile("str     r12, [r2,r0, LSL #2]	");

	__asm__ volatile("b       knl_start_dispatch	");
}

void __naked EnterISR(void)
{
	__asm__ volatile("ldr     r1, =knl_taskindp		");
	__asm__ volatile("ldr     r2, [r1]				");

	__asm__ volatile("cmp     r2, #0				");      /* knl_taskindp==0 */
	__asm__ volatile("bne     l_nosave				");

	__asm__ volatile("ldr     r3, = knl_dispatch_started ");
	__asm__ volatile("ldr     r3, [r3]				");
	__asm__ volatile("cmp     r3, #0				");
	__asm__ volatile("beq     l_nosave				");    /* system not startd */

    /* save context on fisrt ISR enter */
	__asm__ volatile("push    {r4-r11}				");

	__asm__ volatile("ldr     r3, =runtsk			");
	__asm__ volatile("ldrb    r4, [r3]				");

	__asm__ volatile("ldr     r3, =tcxb_sp			");
	__asm__ volatile("str     sp, [r3,r4, LSL #2]	");

	__asm__ volatile("ldr     r3, =tcxb_pc			");

	__asm__ volatile("ldr     r12, =knl_dispatch_r	");
	__asm__ volatile("str     r12, [r3,r4, LSL #2]	");
    /* and then load isr system stack */
	__asm__ volatile("ldr     sp, =knl_system_stack_top ");  /* Set system stack*/

	__asm__ volatile("l_nosave: 					");
	__asm__ volatile("push    {r0}					");    /* push {lr} */
	__asm__ volatile("add     r3, r2, #1			");
	__asm__ volatile("str     r3, [r1]				");
	__asm__ volatile("push    {r1, r2}				");
	__asm__ volatile("ldr     r1, = callevel		");
	__asm__ volatile("ldrb    r3, [r1]				");
	__asm__ volatile("push    {r3}					");
	__asm__ volatile("mov     r3, #2				");    /* callevel = TCL_ISR2 */
	__asm__ volatile("strb    r3,[r1]				");
	__asm__ volatile("cpsie   i						");
	__asm__ volatile("bx      lr					");
}


void __naked ExitISR(void)
{
	__asm__ volatile("pop     {r3}						");
	__asm__ volatile("ldr     r1, = callevel			");
	__asm__ volatile("strb    r3, [r1]					");
	__asm__ volatile("pop     {r1,r2}					");
	__asm__ volatile("str     r2, [r1]					");
	__asm__ volatile("pop     {lr}						");
	__asm__ volatile("cpsid   i							");

	__asm__ volatile("ldr     r0, =knl_taskindp			");
	__asm__ volatile("ldr     r0, [r0]					");
	__asm__ volatile("cmp     r0, #0					");
	__asm__ volatile("bne     l_nodispatch				");

	__asm__ volatile("ldr     r0, = knl_dispatch_started");
	__asm__ volatile("ldr     r0, [r0]					");
	__asm__ volatile("cmp     r0, #0					");
	__asm__ volatile("beq     l_nodispatch				");

	__asm__ volatile("b      knl_dispatch_entry 		");  /* To dispatch processing  knl_dispatch_ret_int*/

	__asm__ volatile("l_nodispatch:						");
	__asm__ volatile("cpsie   i							");
	__asm__ volatile("bx      lr						");
}

void __naked knl_system_tick(void)
{
	__asm__ volatile("mov r0,lr						");
	__asm__ volatile("bl EnterISR					");
	__asm__ volatile("bl knl_system_tick_handler	");
	__asm__ volatile("b  ExitISR					");
}

void __naked knl_isr_process(void)
{
	__asm__ volatile("mov r0,lr					");
	__asm__ volatile("bl EnterISR				");
	__asm__ volatile("mrs     r0, ipsr 			");   /* r0 = dintno */
	__asm__ volatile("bl knl_isr_handler		");
	__asm__ volatile("b  ExitISR				");
}
#endif /* __GNUC__ */


void nmi_handler(void) 			{ printf("nmi_handler\n");while(1);}
void hard_fault_handler(void)	{ printf("hard_fault_handler\n");while(1);}
void mpu_fault_handler(void)	{ printf("mpu_fault_handler\n");while(1);}
void bus_fault_handler(void)	{ printf("bus_fault_handler\n");while(1);}
void usage_fault_handler(void)	{ printf("usage_fault_handler\n");while(1);}
void debug_monitor_handler(void){ printf("debug_monitor_handler\n");while(1);}
