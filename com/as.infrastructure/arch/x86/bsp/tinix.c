/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2016  AS <parai@foxmail.com>
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
#include "mmu.h"
#include "x86.h"
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
#define AS_LOG_TINIX 1

/* GDT */
/* 描述符索引 */
#define	INDEX_DUMMY			0	// ┓
#define	INDEX_FLAT_C		1	// ┣ LOADER 里面已经确定了的.
#define	INDEX_FLAT_RW		2	// ┃
#define	INDEX_VIDEO			3	// ┛
#define	INDEX_TSS			4
#define	INDEX_LDT_FIRST		5
/* 选择子 */
#define	SELECTOR_DUMMY		   0		// ┓
#define	SELECTOR_FLAT_C		0x08		// ┣ LOADER 里面已经确定了的.
#define	SELECTOR_FLAT_RW	0x10		// ┃
#define	SELECTOR_VIDEO		(0x18+3)	// ┛<-- RPL=3
#define	SELECTOR_TSS		0x20		// TSS. 从外层跳到内存时 SS 和 ESP 的值从里面获得.
#define SELECTOR_LDT_FIRST	0x28

#define	SELECTOR_KERNEL_CS	SELECTOR_FLAT_C
#define	SELECTOR_KERNEL_DS	SELECTOR_FLAT_RW
#define	SELECTOR_KERNEL_GS	SELECTOR_VIDEO
#define LDT_SIZE		2

#define NR_SYS_CALL 2
/* ============================ [ TYPES     ] ====================================================== */
typedef struct s_proc {
	cpu_context_t			regs;			/* process' registers saved in stack frame */

	uint16_t			ldt_sel;		/* selector in gdt giving ldt base and limit*/
	mmu_descriptor_t	ldts[LDT_SIZE];		/* local descriptors for code and data */
											/* 2 is LDT_SIZE - avoid include protect.h */
	int				ticks;			/* remained ticks */
	int				priority;
	uint32_t				pid;			/* process id passed in from MM */
	char				name[16];		/* name of the process */

	int				nr_tty;
}PROCESS;

typedef	void*	t_sys_call;
/* ============================ [ DECLARES  ] ====================================================== */
void init_prot(void);
int sys_get_ticks (void);
int sys_write	(char* buf, int len, PROCESS* p_proc);
void init_descriptor(mmu_descriptor_t * p_desc, uint32_t base, uint32_t limit, uint16_t attribute);
uint32_t seg2phys(uint16_t seg);
void restart(void);
void task_entry(void);
extern void init_clock(void);
/* ============================ [ DATAS     ] ====================================================== */
uint8_t         gdt_ptr[6]; /* 0~15:Limit  16~47:Base */
mmu_descriptor_t    gdt[GDT_SIZE];
uint8_t idt_ptr[6]; /* 0~15:Limit  16~47:Base */
mmu_gate_t idt[IDT_SIZE];

uint32_t disp_pos;
uint32_t k_reenter;

tss_t tss;

PROCESS*	p_proc_ready;

PROCESS		proc_table[TASK_NUM];

t_sys_call sys_call_table[NR_SYS_CALL] = {sys_get_ticks, sys_write};

TickType				OsTickCounter;
/* ============================ [ LOCALS    ] ====================================================== */
static void init_ldt(void)
{
	/* 填充 GDT 中每个进程的 LDT 的描述符 */
	int i;
	PROCESS* p_proc	= proc_table;
	uint16_t selector_ldt = INDEX_LDT_FIRST << 3;
	for(i=0;i<TASK_NUM;i++){
		init_descriptor(&gdt[selector_ldt>>3],
				vir2phys(seg2phys(SELECTOR_KERNEL_DS), proc_table[i].ldts),
				LDT_SIZE * sizeof(mmu_descriptor_t) - 1,
				DA_LDT);
		p_proc++;
		selector_ldt += 1 << 3;
	}
}
/* ============================ [ FUNCTIONS ] ====================================================== */
void TaskProcess(uint32_t tskid)
{
	const task_declare_t* td;
	td = &TaskList[tskid];
	TimerType timer = 0;
	uint32_t counter = 0;

	ASLOG(TINIX,"%s is ready!\n",td->name);

	StartTimer(&timer);
	while(1)
	{
		if(GetTimer(&timer) > 1000)
		{
			counter ++;
			ASLOG(TINIX,"%s loop %d times!\n",td->name,counter);
			StartTimer(&timer);

			if(tskid == (TASK_NUM-1))
			{
				disp_pos = 0;
			}

			//td->main();
		}
	}
}

void cstart(void)
{
	disp_pos = 0;
	ASLOG(TINIX,"cstart begins\n");

	/* copy the GDT of LOADER to the new GDT */
	memcpy(&gdt,    /* New GDT */
		   (void*)(*((uint32_t*)(&gdt_ptr[2]))),   /* Base  of Old GDT */
		   *((uint16_t*)(&gdt_ptr[0])) + 1    /* Limit of Old GDT */
		);
	/* gdt_ptr[6] has 6 bytes : 0~15:Limit  16~47:Base, acting as parameter of instruction sgdt & lgdt */
	uint16_t* p_gdt_limit = (uint16_t*)(&gdt_ptr[0]);
	uint32_t* p_gdt_base  = (uint32_t*)(&gdt_ptr[2]);
	*p_gdt_limit = GDT_SIZE * sizeof(mmu_descriptor_t) - 1;
	*p_gdt_base  = (uint32_t)&gdt;

	/* idt_ptr[6] 共 6 个字节：0~15:Limit  16~47:Base。用作 sidt 以及 lidt 的参数。*/
	uint16_t* p_idt_limit = (uint16_t*)(&idt_ptr[0]);
	uint32_t* p_idt_base  = (uint32_t*)(&idt_ptr[2]);
	*p_idt_limit = IDT_SIZE * sizeof(mmu_gate_t) - 1;
	*p_idt_base = (uint32_t)&idt;

	init_prot();

	/* 填充 GDT 中 TSS 这个描述符 */
	memset(&tss, 0, sizeof(tss));
	tss.ss0		= SELECTOR_KERNEL_DS;
	init_descriptor(&gdt[INDEX_TSS],
			vir2phys(seg2phys(SELECTOR_KERNEL_DS), &tss),
			sizeof(tss) - 1,
			DA_386TSS);
	tss.iobase	= sizeof(tss);	/* 没有I/O许可位图 */

	ASLOG(TINIX,"cstart finished\n");
}

FUNC(StatusType,MEM_ACTIVATE_TASK) 	 ActivateTask    ( TaskType TaskId)
{
	StatusType ercd = E_OK;
	return ercd;
}

FUNC(StatusType,MEM_ACTIVATE_TASK) 	 TerminateTask   ( void )
{
	StatusType ercd = E_OK;
	return ercd;
}

FUNC(void,MEM_OsTick)         OsTick       ( void )
{
	OsTickCounter ++;

	if(0u == OsTickCounter)
	{
		OsTickCounter = 1;
	}
	/* each task one tick slot */
	p_proc_ready = &proc_table[(p_proc_ready->pid+1)<TASK_NUM?(p_proc_ready->pid+1):0];
}

FUNC(TickType,MEM_GetOsTick)         GetOsTick       ( void )
{
	return OsTickCounter;
}

FUNC(StatusType,MEM_SetEvent)        SetEvent        ( TaskType tskid , EventMaskType mask )
{
	StatusType ercd = E_OK;
	return ercd;
}
FUNC(StatusType,MEM_ClearEvent)      ClearEvent      ( EventMaskType mask )
{
	StatusType ercd = E_OK;
	return ercd;
}
FUNC(StatusType,MEM_GetEvent)        GetEvent        ( TaskType tskid , EventMaskRefType p_mask )
{
	StatusType ercd = E_OK;
	return ercd;
}
FUNC(StatusType,MEM_WaitEvent)       WaitEvent       ( EventMaskType mask )
{
	StatusType ercd = E_OK;
	return ercd;
}

FUNC(StatusType,MEM_SetRelAlarm) 	 SetRelAlarm     ( AlarmType AlarmId, TickType Increment, TickType Cycle )
{
	StatusType ercd = E_OK;
	return ercd;
}
FUNC(StatusType,MEM_SetAbsAlarm) 	 SetAbsAlarm     ( AlarmType AlarmId, TickType Increment, TickType Cycle )
{
	StatusType ercd = E_OK;
	return ercd;
}
FUNC(StatusType,MEM_CancelAlarm)     CancelAlarm     ( AlarmType AlarmId )
{
	StatusType ercd = E_OK;
	return ercd;
}

FUNC(StatusType,MEM_GetResource)     GetResource     ( ResourceType ResID )
{
	StatusType ercd = E_OK;
	return ercd;
}
FUNC(StatusType,MEM_ReleaseResource) ReleaseResource ( ResourceType ResID )
{
	StatusType ercd = E_OK;
	return ercd;
}

FUNC(void,MEM_ShutdownOS)  ShutdownOS ( StatusType ercd )
{
	(void)ercd;
	while(1);
}
void StartOS(AppModeType app_mode)
{
	uint32 i;
	const task_declare_t* td;
	uint16_t selector_ldt	= SELECTOR_LDT_FIRST;
	uint8_t privilege;
	uint8_t rpl;
	int	eflags;
	PROCESS* p_proc = proc_table;

	ASLOG(TINIX,"StartOS(%d)\n",app_mode);
	init_ldt();
	for(i=0;i<TASK_NUM;i++)
	{
		td = &TaskList[i];
		privilege	= PRIVILEGE_TASK;
		rpl		= RPL_TASK;
		eflags = 0x1202; /* IF=1, IOPL=1, bit 2 is always 1 */
		strcpy(p_proc->name, td->name);	/* name of the process */
		p_proc->pid	= i;			/* pid */

		p_proc->ldt_sel	= selector_ldt;
		memcpy(&p_proc->ldts[0], &gdt[SELECTOR_KERNEL_CS >> 3], sizeof(mmu_descriptor_t));
		p_proc->ldts[0].attr1 = DA_C | privilege << 5;	/* change the DPL */
		memcpy(&p_proc->ldts[1], &gdt[SELECTOR_KERNEL_DS >> 3], sizeof(mmu_descriptor_t));
		p_proc->ldts[1].attr1 = DA_DRW | privilege << 5;/* change the DPL */
		p_proc->regs.cs		= ((8 * 0) & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
		p_proc->regs.ds		= ((8 * 1) & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
		p_proc->regs.es		= ((8 * 1) & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
		p_proc->regs.fs		= ((8 * 1) & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
		p_proc->regs.ss		= ((8 * 1) & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
		p_proc->regs.gs		= (SELECTOR_KERNEL_GS & SA_RPL_MASK) | rpl;
		p_proc->regs.eip	= (uint32_t)task_entry;
		p_proc->regs.esp	= (uint32_t)&(td->pstk[td->stk_size]);
		p_proc->regs.eflags	= eflags;

		p_proc->regs.eax = i;

		p_proc->nr_tty		= 0;

		p_proc++;
		selector_ldt += 1 << 3;
	}

	p_proc_ready = proc_table;

	init_clock();

	restart();
}

int sys_get_ticks (void)
{
	return OsTickCounter;
}

int sys_write	(char* buf, int len, PROCESS* p_proc)
{
	return printf("%s",buf);
}
