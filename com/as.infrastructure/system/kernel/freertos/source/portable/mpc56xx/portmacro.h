/*
    FreeRTOS V7.1.1 - Copyright (C) 2012 Real Time Engineers Ltd.
	

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS tutorial books are available in pdf and paperback.        *
     *    Complete, revised, and edited pdf reference manuals are also       *
     *    available.                                                         *
     *                                                                       *
     *    Purchasing FreeRTOS documentation will not only help you, by       *
     *    ensuring you get running as quickly as possible and with an        *
     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
     *    the FreeRTOS project to continue with its mission of providing     *
     *    professional grade, cross platform, de facto standard solutions    *
     *    for microcontrollers - completely free of charge!                  *
     *                                                                       *
     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
     *                                                                       *
     *    Thank you for using FreeRTOS, and thank you for your support!      *
     *                                                                       *
    ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    >>>NOTE<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!
    
    ***************************************************************************
     *                                                                       *
     *    Having a problem?  Start by reading the FAQ "My application does   *
     *    not run, what could be wrong?                                      *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************

    
    http://www.FreeRTOS.org - Documentation, training, latest information, 
    license and contact details.
    
    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool.

    Real Time Engineers ltd license FreeRTOS to High Integrity Systems, who sell 
    the code with commercial support, indemnification, and middleware, under 
    the OpenRTOS brand: http://www.OpenRTOS.com.  High Integrity Systems also
    provide a safety engineered and independently SIL3 certified version under 
    the SafeRTOS brand: http://www.SafeRTOS.com.
*/


#ifndef PORTMACRO_H
#define PORTMACRO_H

/*-----------------------------------------------------------
 * Port specific definitions.  
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions. */
#define portCHAR		char
#define portFLOAT		float
#define portDOUBLE		double
#define portLONG		long
#define portSHORT		short
#define portSTACK_TYPE	unsigned portLONG
#define portBASE_TYPE	portLONG

typedef unsigned long UBaseType_t;

#if( configUSE_16_BIT_TICKS == 1 )
	typedef unsigned portSHORT portTickType;
	#define portMAX_DELAY ( portTickType ) 0xffff
#else
	typedef unsigned portLONG portTickType;
	#define portMAX_DELAY ( portTickType ) 0xffffffff
#endif

typedef portSTACK_TYPE StackType_t;
typedef portBASE_TYPE BaseType_t;
typedef portTickType TickType_t; 
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#define portBYTE_ALIGNMENT			4
#define portSTACK_GROWTH			( -1 )
#define portYIELD()					__asm( "sc" );
#define portNOP()					__asm( "nop" );
/*-----------------------------------------------------------*/

/* Critical section handling. */
#define portENABLE_INTERRUPTS()			__asm("wrteei 1")
#define portDISABLE_INTERRUPTS()		__asm("wrteei 0")

/*
 * Disable interrupts before incrementing the count of critical section nesting.
 * The nesting count is maintained so we know when interrupts should be
 * re-enabled.  Once interrupts are disabled the nesting count can be accessed
 * directly.  Each task maintains its own nesting count.
 */
#define portENTER_CRITICAL()  									\
{																\
	extern volatile unsigned portBASE_TYPE uxCriticalNesting;	\
																\
	portDISABLE_INTERRUPTS();									\
	uxCriticalNesting++;										\
}

/*
 * Interrupts are disabled so we can access the nesting count directly.  If the
 * nesting is found to be 0 (no nesting) then we are leaving the critical 
 * section and interrupts can be re-enabled.
 */
#define  portEXIT_CRITICAL()									\
{																\
	extern volatile unsigned portBASE_TYPE uxCriticalNesting;	\
																\
	uxCriticalNesting--;										\
	if( uxCriticalNesting == 0 )								\
	{															\
		portENABLE_INTERRUPTS();								\
	}															\
}
/*-----------------------------------------------------------*/

/* Task utilities. */

/* 
 * These macros are very simple as the processor automatically saves and 
 * restores its registers as interrupts are entered and exited.  In
 * addition to the (automatically stacked) registers we also stack the 
 * critical nesting count.  Each task maintains its own critical nesting
 * count as it is legitimate for a task to yield from within a critical
 * section.  If the banked memory model is being used then the PPAGE
 * register is also stored as part of the tasks context.
 */
/*
 * Load the stack pointer for the task, then pull the critical nesting
 * count and PPAGE register from the stack.  The remains of the
 * context are restored by the RTI instruction.
 */

/***************************************************************************************************
		Regeister Map
***************************************************************************************************/
#define XR1     0
#define XBLK    XR1+4
#define XR2     XBLK+4
#define XR3     XR2+4    
#define XR4     XR3+4
#define XR5     XR4+4
#define XR6     XR5+4
#define XR7     XR6+4
#define XR8     XR7+4
#define XR9     XR8+4
#define XR10    XR9+4
#define XR11    XR10+4
#define XR12    XR11+4
#define XR13    XR12+4
#define XR14    XR13+4
#define XR15    XR14+4
#define XR16    XR15+4
#define XR17    XR16+4
#define XR18    XR17+4
#define XR19    XR18+4
#define XR20    XR19+4
#define XR21    XR20+4
#define XR22    XR21+4
#define XR23    XR22+4
#define XR24    XR23+4
#define XR25    XR24+4
#define XR26    XR25+4
#define XR27    XR26+4
#define XR28    XR27+4
#define XR29    XR28+4
#define XR30    XR29+4
#define XR31    XR30+4 
#define XR0     XR31+4
#define XSRR0   XR0+4
#define XSRR1   XSRR0+4
#define XUSPRG  XSRR1+4 
#define XCTR    XUSPRG+4    
#define XXER    XCTR+4
#define XCR     XXER+4
#define XLR     XCR+4
#define XSPEFSCR XLR+4
#define XPAD2   XSPEFSCR+4
#define XPAD3   XPAD2+4
#define XMSR    XPAD3+4

#define STACK_FRAME_SIZE   XMSR+4

#define portRESTORE_CONTEXT()	\
	wrteei 0; \
	/* Get the address of the TCB. */	\
	lis     r11, pxCurrentTCB@ha;	\
	lwz		r11, pxCurrentTCB@l(r11);	\
	/* Get the task stack pointer in the TCB. */	\
	lwz		r1, 0( r11 ); \
	/*restore R0,R2-R31*/	\
	lmw		r2,  XR2(r1);	\
	/*restore CR*/	\
    lwz     r0,  XCR(r1);	\
    mtcrf   0xff,r0;	\
	/*restore XER*/	\
	lwz     r0,  XXER(r1);	\
	mtxer   r0;	\
	/*restore CTR*/	\
	lwz     r0,  XCTR(r1);	\
	mtctr   r0;	\
	lwz     r0,  XLR(r1);	\
	mtlr    r0;	\
	/*restore SRR1*/	\
	lwz     r0,  XSRR1(r1);	\
	mtspr   SRR1,r0;	\
	/*restore SRR0*/	\
	lwz     r0,  XSRR0(r1);	\
	mtspr   SRR0,r0;	\
	/*restore USPRG*/	\
	lwz     r0,  XUSPRG(r1);	\
	mtspr   USPRG0,r0;	\
	/*restore SPEFSCR : for float point */ \
	lwz     r0,  XSPEFSCR(r1);	\
	mtspr   SPEFSCR,r0;	\
	/*restore rsp*/ \
	lwz     r0,  XR0(r1);	\
    addi    r1,  r1, STACK_FRAME_SIZE
    
/*
	lwz     r2,  XR2(r1);	\
	lwz     r3,  XR3(r1);	\
	lwz     r4,  XR4(r1);	\
	lwz     r5,  XR5(r1);	\
	lwz     r6,  XR6(r1);	\
	lwz     r7,  XR7(r1);	\
	lwz     r8,  XR8(r1);	\
	lwz     r9,  XR9(r1);	\
	lwz     r10, XR10(r1);	\
	lwz     r11, XR11(r1);	\
	lwz     r12, XR12(r1);	\
	lwz     r13, XR13(r1);	\
	lwz     r14, XR14(r1);	\
	lwz     r15, XR15(r1);	\
	lwz     r16, XR16(r1);	\
	lwz     r17, XR17(r1);	\
	lwz     r18, XR18(r1);	\
	lwz     r19, XR19(r1);	\
	lwz     r20, XR20(r1);	\
	lwz     r21, XR21(r1);	\
	lwz     r22, XR22(r1);	\
	lwz     r23, XR23(r1);	\
	lwz     r24, XR24(r1);	\
	lwz     r25, XR25(r1);	\
	lwz     r26, XR26(r1);	\
	lwz     r27, XR27(r1);	\
	lwz     r28, XR28(r1);	\
	lwz     r29, XR29(r1);	\
	lwz     r30, XR30(r1);	\
	lwz     r31, XR31(r1);	\
*/    
/*    
	stw     r2,  XR2(r1);	  \
	stw     r3,  XR3(r1); \
	stw     r4,  XR4(r1); \
	stw     r5,  XR5(r1); \
	stw     r6,  XR6(r1); \
	stw     r7,  XR7(r1); \
	stw     r8,  XR8(r1); \
	stw     r9,  XR9(r1); \
	stw     r10, XR10(r1); \
	stw     r11, XR11(r1); \
	stw     r12, XR12(r1); \
	stw     r13, XR13(r1); \
	stw     r14, XR14(r1); \
	stw     r15, XR15(r1); \
	stw     r16, XR16(r1); \
	stw     r17, XR17(r1); \
	stw     r18, XR18(r1); \
	stw     r19, XR19(r1); \
	stw     r20, XR20(r1); \
	stw     r21, XR21(r1); \
	stw     r22, XR22(r1); \
	stw     r23, XR23(r1); \
	stw     r24, XR24(r1); \
	stw     r25, XR25(r1); \
	stw     r26, XR26(r1); \
	stw     r27, XR27(r1); \
	stw     r28, XR28(r1); \
	stw     r29, XR29(r1); \
	stw     r30, XR30(r1); \
	stw     r31, XR31(r1); \
	*/
#define portSAVE_CONTEXT()	\
	/* Remain frame from stack */	\
	subi    r1, r1, -STACK_FRAME_SIZE; \
	/*Store R0,R2,R3-R31*/	\
	stw     r0,  XR0(r1);		\
	stmw	r2,  XR2(r1);	  \
	/*Store XMSR ang SPEFSCR  */ \
	mfmsr   r0; \
	stw     r0,  XMSR(r1); \
	mfspr   r0,  SPEFSCR; \
	stw     r0,  XSPEFSCR(r1); \
	/*Store LR(SRR0)*/	\
	mfspr   r0,  SRR0; \
	stw     r0,  XSRR0(r1); \
	/*Store MSR(SRR1)*/	\
	mfspr   r0,  SRR1; \
	stw     r0,  XSRR1(r1); \
	/*Store USPRG0*/	\
	mfspr   r0,  USPRG0; \
	stw     r0,  XUSPRG(r1); \
	/*Store LR*/  \
	mflr    r0; \
	stw     r0,  XLR(r1); \
	/*Store CTR*/	\
	mfctr   r0; \
	stw     r0,  XCTR(r1); \
	/*Store XER*/	\
	mfxer   r0; \
	stw     r0,  XXER(r1); \
	/*Store CR*/	\
	mfcr    r0; \
	stw     r0,  XCR(r1); \
	mfmsr   r0;	\
	/* Get the address of the TCB. */	\
	lis     r11, pxCurrentTCB@ha;	\
	lwz		r11, pxCurrentTCB@l(r11);	\
	/* Save the task stack pointer in the TCB. */	\
	stw		r1, 0( r11 )
/*
 * Utility macro to call macros above in correct order in order to perform a
 * task switch from within a standard ISR.  This macro can only be used if
 * the ISR does not use any local (stack) variables.  If the ISR uses stack
 * variables portYIELD() should be used in it's place.
 */
#define portTASK_SWITCH_FROM_ISR()								\
	portSAVE_CONTEXT();											\
	vTaskSwitchContext();										\
	portRESTORE_CONTEXT();


/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) void vFunction( void *pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters ) void vFunction( void *pvParameters )

#endif /* PORTMACRO_H */

