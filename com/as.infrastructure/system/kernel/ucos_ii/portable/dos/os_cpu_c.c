/*
*********************************************************************************************************
*                                               uC/OS-II
*                                         The Real-Time Kernel
*
*                         (c) Copyright 1992-2001, Jean J. Labrosse, Weston, FL
*                                          All Rights Reserved
*
*
*                                       80x86/80x88 Specific code
*                                          PROTECTED MEMORY MODEL
*
*
* File         : OS_CPU_C.C
* By           : Jean J. Labrosse, updated by parai wang @ 2017/5/11
*********************************************************************************************************
*/

#include "ucos_ii.h"

static HANDLE  mainhandle;
static CONTEXT Context;
OS_CPU_SR FlagEn = 1;

void VCInit(void)
{
	HANDLE cp,ct;
	Context.ContextFlags = CONTEXT_CONTROL;
	cp = GetCurrentProcess();
	ct = GetCurrentThread();
	DuplicateHandle(cp, ct, cp, &mainhandle, 0, TRUE, 2);
}

#if OS_CRITICAL_METHOD == 3
OS_CPU_SR  OSCPUSaveSR(void)
{
	OS_CPU_SR old = FlagEn;

	FlagEn = 0;

	return old;
}
void       OSCPURestoreSR(OS_CPU_SR cpu_sr)
{
	FlagEn = cpu_sr;
}
#endif
/*
*********************************************************************************************************
*                                        INITIALIZE A TASK'S STACK
*
* Description: This function is called by either OSTaskCreate() or OSTaskCreateExt() to initialize the
*              stack frame of the task being created.  This function is highly processor specific.
*				
* Arguments  : task          is a pointer to the task code
*
*              pdata         is a pointer to a user supplied data area that will be passed to the task
*                            when the task first executes.
*
*              ptos          is a pointer to the top of stack.  It is assumed that 'ptos' points to
*                            a 'free' entry on the task stack.  If OS_STK_GROWTH is set to 1 then 
*                            'ptos' will contain the HIGHEST valid address of the stack.  Similarly, if
*                            OS_STK_GROWTH is set to 0, the 'ptos' will contains the LOWEST valid address
*                            of the stack.
*
*              opt           specifies options that can be used to alter the behavior of OSTaskStkInit().
*                            (see uCOS_II.H for OS_TASK_OPT_???).
*
* Returns    : Always returns the location of the new top-of-stack' once the processor registers have
*              been placed on the stack in the proper order.
*
* Note(s)    : Interrupts are enabled when your task starts executing. You can change this by setting the
*              PSW to 0x0002 instead.  In this case, interrupts would be disabled upon task startup.  The
*              application code would be responsible for enabling interrupts at the beginning of the task
*              code.  You will need to modify OSTaskIdle() and OSTaskStat() so that they enable 
*              interrupts.  Failure to do this will make your system crash!
*********************************************************************************************************
*/

OS_STK *OSTaskStkInit (void (*task)(void *pd), void *pdata, OS_STK *ptos, INT16U opt)
{
    INT32U *stk;


    opt    = opt;                           /* 'opt' is not used, prevent warning                      */
    stk    = (INT32U *)ptos;                /* Load stack pointer                                      */
    *--stk = (INT32U)pdata;         		/* Simulate call to function with argument                 */
	*--stk = (INT32U)0x00000000;			/* sub-routine get passed parameter from esp+4, so reserved 4 bytes */
	*--stk = (INT32U)task;          			/* Put pointer to task   on top of stack                   */
    *--stk = (INT32U)0x00000202;				/* EFL = 0X00000202												*/
	*--stk = (INT32U)0xAAAAAAAA;                /* EAX = 0xAAAAAAAA                                              */
    *--stk = (INT32U)0xCCCCCCCC;                /* ECX = 0xCCCCCCCC                                             */
    *--stk = (INT32U)0xDDDDDDDD;                /* EDX = 0xDDDDDDDD                                             */
    *--stk = (INT32U)0xBBBBBBBB;                /* EBX = 0xBBBBBBBB                                             */
    *--stk = (INT32U)0x00000000;                /* ESP = 0x00000000  esp can be any value                       */
    *--stk = (INT32U)0x11111111;                /* EBP = 0x11111111                                             */
    *--stk = (INT32U)0x22222222;                /* ESI = 0x22222222                                             */
    *--stk = (INT32U)0x33333333;                /* EDI = 0x33333333                                             */
    //*--stk = (INT32U)1;                			/* ISR Flag: enabled                                            */
                             
    return ((OS_STK *)stk);
}



/**********************************************************************************************************
;                                          START MULTITASKING
;                                       void OSStartHighRdy(void)
;
; The stack frame is assumed to look as follows:
;
; OSTCBHighRdy->OSTCBStkPtr --> EDI                               (Low memory)                           
;                               ESI
;                               EBP
;                               ESP
;                               EBX
;                               EDX
;                               ECX
;                               EAX
;                               Flags to load in PSW
;                               OFFSET  of task code address
;								4 empty byte
;                               OFFSET  of 'pdata'					(High memory)
;                                              
;
; Note : OSStartHighRdy() MUST:
;           a) Call OSTaskSwHook() then,
;           b) Set OSRunning to TRUE,
;           c) Switch to the highest priority task.
;*********************************************************************************************************/

void OSStartHighRdy(void)
{
	OSTaskSwHook();
	OSRunning = 1;
#ifdef __GNUC__
	/* https://www.ibm.com/developerworks/library/l-ia/
	 * http://www.cnblogs.com/zhuyp1015/archive/2012/05/01/2478099.html*/
	asm (
		 "mov  (%0), %%esp \n" /* restore contex */
		 "popal		        \n"   /* restore all general registers, in sum 8 */
		 "popfl		        \n"   /* restore the flag register */
		 "ret		        \n"   /* ret  = pop eip, in protection mode, not allowed to use eip */
			:: "a"(OSTCBCur) :
		);
#else
	_asm{
		mov ebx, [OSTCBCur]
		mov esp, [ebx]

		popad
		popfd
		ret
	}
#endif
	/* never reach here */
}

 /*$PAGE*/
/*********************************************************************************************************
;                                PERFORM A CONTEXT SWITCH (From task level)
;                                           void OSCtxSw(void)
;
; Note(s): 1) switch task
;
;          2) The stack frame of the task to suspend looks as follows:
;
;                 SP -> OFFSET  of task to suspend    (Low memory)
;                       PSW     of task to suspend    (High memory)
;
;          3) The stack frame of the task to resume looks as follows:
;
; OSTCBHighRdy->OSTCBStkPtr --> EDI                               (Low memory)                           
;                               ESI
;                               EBP
;                               ESP
;                               EBX
;                               EDX
;                               ECX
;                               EAX
;                               Flags to load in PSW
;                               OFFSET  of task code address				(High memory)
;                                    
;*********************************************************************************************************/

void OSCtxSw(void)
{
#ifdef __GNUC__
	unsigned long addr = (unsigned long)&&nextstart;
	asm (
		"push %1             \n"/* start from nextstart when the task switch back */
		"pushfl				 \n" /* flag register */
		"pushal				 \n" /* store EAX -- EDI */
		"mov %%esp, %0	     \n" /* store current stack esp to OSTCBCur */
		: "=a"(OSTCBCur->OSTCBStkPtr) : "a"(addr):
	);
#else
	_asm{
		lea	 eax, nextstart
		push eax
		pushfd
		pushad
		mov ebx, [OSTCBCur]
		mov [ebx], esp
	}
#endif
	OSTaskSwHook();
	OSTCBCur = OSTCBHighRdy;	
	OSPrioCur = OSPrioHighRdy;
#ifdef __GNUC__
	asm (
		 "mov  (%0), %%esp \n" /* restore contex */
		 "popal		        \n"   /* restore all general registers, in sum 8 */
		 "popfl		        \n"   /* restore the flag register */
		 "ret		        \n"   /* ret  = pop eip, in protection mode, not allowed to use eip */
			:: "a"(OSTCBCur) :
	);
#else
	_asm{
		mov ebx, [OSTCBCur]
		mov esp, [ebx]

		popad
		popfd
		ret
	}
#endif
nextstart:			/* the task switch back */
		return;
}

/*********************************************************************************************************
;                                PERFORM A CONTEXT SWITCH (From an ISR)
;                                        void OSIntCtxSw(void)
;
; Note(s): 1)
;
; OSTCBHighRdy->OSTCBStkPtr --> EDI                               (Low memory)                           
;                               ESI
;                               EBP
;                               ESP
;                               EBX
;                               EDX
;                               ECX
;                               EAX
;                               Flags to load in PSW
;                               OFFSET  of task code address				(High memory)
;*********************************************************************************************************/

void OSIntCtxSw(void)
{
	OS_STK *sp;
	OSTaskSwHook();

	
	sp = (OS_STK *)Context.Esp;	/* get the main thread stack pointer */
	/* save all the registers to stack */
	*--sp = Context.Eip;
	*--sp = Context.EFlags;
	*--sp = Context.Eax;
	*--sp = Context.Ecx;
	*--sp = Context.Edx;
	*--sp = Context.Ebx;
	*--sp = Context.Esp;	/* this is a wrong esp value£¬but the OSTCBCur is the right one */
	*--sp = Context.Ebp;
	*--sp = Context.Esi;
	*--sp = Context.Edi;
	OSTCBCur->OSTCBStkPtr = (OS_STK *)sp;	/* here save the esp, this is the right one */
	
	OSTCBCur = OSTCBHighRdy;
	OSPrioCur = OSPrioHighRdy;
	sp = OSTCBHighRdy->OSTCBStkPtr;
	
	
	//restore all registers
	Context.Edi = *sp++;
	Context.Esi = *sp++;
	Context.Ebp = *sp++;
	Context.Esp = *sp++;		/* this is not the right one */
	Context.Ebx = *sp++;
	Context.Edx = *sp++;
	Context.Ecx = *sp++;
	Context.Eax = *sp++;
	Context.EFlags = *sp++; 
	Context.Eip = *sp++;
	
	Context.Esp = (unsigned long)sp;		/* get the right esp */
	
	SetThreadContext(mainhandle, &Context);	/* save main thread contex */
}

/*********************************************************************************************************
;                                            HANDLE TICK ISR
;
; Description:  enabled by timeSetEvent, this is a simulated ISR
;
; Arguments  : none
;
; Returns    : none
;
; Note(s)    :
;*********************************************************************************************************/

void CALLBACK OSTickISR(unsigned int a,unsigned int b,unsigned long c,unsigned long d,unsigned long e)
{
	if(!FlagEn)
		return;

	SuspendThread(mainhandle);
	GetThreadContext(mainhandle, &Context);

	OSIntNesting++;
	if (OSIntNesting == 1) {
		OSTCBCur->OSTCBStkPtr = (OS_STK *)Context.Esp;
	}	
	OSTimeTick();
	OSIntExit();

	ResumeThread(mainhandle);

}
/*$PAGE*/
#if OS_CPU_HOOKS_EN
/*
*********************************************************************************************************
*                                       OS INITIALIZATION HOOK
*                                            (BEGINNING)
*
* Description: This function is called by OSInit() at the beginning of OSInit().
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts should be disabled during this call.
*********************************************************************************************************
*/
#if OS_VERSION > 203
void OSInitHookBegin (void)
{
}
#endif

/*
*********************************************************************************************************
*                                       OS INITIALIZATION HOOK
*                                               (END)
*
* Description: This function is called by OSInit() at the end of OSInit().
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts should be disabled during this call.
*********************************************************************************************************
*/
#if OS_VERSION > 203
void OSInitHookEnd (void)
{
}
#endif


/*
*********************************************************************************************************
*                                          TASK CREATION HOOK
*
* Description: This function is called when a task is created.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being created.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/
void OSTaskCreateHook (OS_TCB *ptcb)
{
    ptcb = ptcb;                       /* Prevent compiler warning                                     */
}


/*
*********************************************************************************************************
*                                           TASK DELETION HOOK
*
* Description: This function is called when a task is deleted.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being deleted.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/
void OSTaskDelHook (OS_TCB *ptcb)
{
    ptcb = ptcb;                       /* Prevent compiler warning                                     */
}

/*
*********************************************************************************************************
*                                           TASK SWITCH HOOK
*
* Description: This function is called when a task switch is performed.  This allows you to perform other
*              operations during a context switch.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are disabled during this call.
*              2) It is assumed that the global pointer 'OSTCBHighRdy' points to the TCB of the task that
*                 will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCur' points to the 
*                 task being switched out (i.e. the preempted task).
*********************************************************************************************************
*/
#ifndef NO_OS_TASK_SWITCH_HOOK
void OSTaskSwHook (void)
{
}
#endif

/*
*********************************************************************************************************
*                                           STATISTIC TASK HOOK
*
* Description: This function is called every second by uC/OS-II's statistics task.  This allows your 
*              application to add functionality to the statistics task.
*
* Arguments  : none
*********************************************************************************************************
*/
#ifndef NO_TASK_STAT_HOOK
void OSTaskStatHook (void)
{
}
#endif
/*
*********************************************************************************************************
*                                           OSTCBInit() HOOK
*
* Description: This function is called by OSTCBInit() after setting up most of the TCB.
*
* Arguments  : ptcb    is a pointer to the TCB of the task being created.
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/
#if OS_VERSION > 203
void OSTCBInitHook (OS_TCB *ptcb)
{
    ptcb = ptcb;                                           /* Prevent Compiler warning                 */
}
#endif


/*
*********************************************************************************************************
*                                               TICK HOOK
*
* Description: This function is called every tick.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/
void OSTimeTickHook (void)
{
#if OS_TMR_EN > 0u
	OSTmrSignal();
#endif
}


/*
*********************************************************************************************************
*                                             IDLE TASK HOOK
*
* Description: This function is called by the idle task.  This hook has been added to allow you to do  
*              such things as STOP the CPU to conserve power.changed by ÎÄ¼Ñ Email£ºganganwen@163.com
*
* Arguments  : none 
*
* Note(s)    : 1) Interrupts are enabled during this call.
*********************************************************************************************************
*/
#if OS_VERSION >= 251
void OSTaskIdleHook (void)
{
#ifdef __GNUC__
#else
	Sleep(1);
#endif
}
#endif

void OSTaskReturnHook(OS_TCB *ptcb)
{

}
#endif
