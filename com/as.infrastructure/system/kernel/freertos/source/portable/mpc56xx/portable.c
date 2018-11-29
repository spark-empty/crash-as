#include "FreeRTOS.h"
#include "task.h"
#include "mpc56xx.h"

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the HCS12 port.
 *----------------------------------------------------------*/


/*
 * Configure a timer to generate the RTOS tick at the frequency specified 
 * within FreeRTOSConfig.h.
 */
static void prvSetupTimerInterrupt( void );

/* Interrupt service routines have to be in non-banked memory - as does the
scheduler startup function. */

/* Manual context switch function.  This is the SWI ISR. */
void vPortYield( void );

/* Tick context switch function.  This is the timer ISR. */
void vPortTickInterrupt( void );

/* Simply called by xPortStartScheduler().  xPortStartScheduler() does not
start the scheduler directly because the header file containing the 
xPortStartScheduler() prototype is part of the common kernel code, and 
therefore cannot use the CODE_SEG pragma. */
static portBASE_TYPE xStartFirstTask( void );
void vPortEndScheduler( void );


/* Calls to portENTER_CRITICAL() can be nested.  When they are nested the 
critical section should not be left (i.e. interrupts should not be re-enabled)
until the nesting depth reaches 0.  This variable simply tracks the nesting 
depth.  Each task maintains it's own critical nesting depth variable so 
uxCriticalNesting is saved and restored from the task stack during a context
switch. */
volatile unsigned portBASE_TYPE uxCriticalNesting = 0xff;

extern const unsigned _SDA_BASE_;
extern const unsigned _SDA2_BASE_;
/* Definitions to set the initial MSR of each task. */
#define portCRITICAL_INTERRUPT_ENABLE	( 1UL << 17UL )
#define portEXTERNAL_INTERRUPT_ENABLE	( 1UL << 15UL )
#define portMACHINE_CHECK_ENABLE		( 1UL << 12UL )

#if configUSE_FPU == 1
	#define portAPU_PRESENT				( 1UL << 25UL )
	#define portFCM_FPU_PRESENT			( 1UL << 13UL )
#else
	#define portAPU_PRESENT				( 0UL )
	#define portFCM_FPU_PRESENT			( 0UL )
#endif

#define portINITIAL_MSR		( portCRITICAL_INTERRUPT_ENABLE | portEXTERNAL_INTERRUPT_ENABLE | \
			portMACHINE_CHECK_ENABLE | portAPU_PRESENT | portFCM_FPU_PRESENT )
			
asm portLONG OS_MSR_Rd(void){
nofralloc
	mfmsr   r3
	blr
 }			
portSTACK_TYPE *pxPortInitialiseStack( portSTACK_TYPE *pxTopOfStack, pdTASK_CODE pxCode, void *pvParameters )
{
/* Place a known value at the bottom of the stack for debugging. */
	portLONG   msr;													/* Local: Initial MSR									   */
	portLONG   srr1;												   /* Local: Initial SRR1									  */

	msr	 =  OS_MSR_Rd();											 /* get the MSB reg value									*/
	srr1	= portINITIAL_MSR;
											   /* set MSR[EE] bit to enable interrupts					 */
	*pxTopOfStack = 0xDEADBEEF;
	pxTopOfStack--;
	pxTopOfStack	= (portSTACK_TYPE *)((portLONG) pxTopOfStack & (portLONG) 0xFFFFFFF0);		  /* 16-byte align task's stack pointer (EABI)				*/

																		/* Leave buffer area for locals "above the stack" in ...	*/
	pxTopOfStack   -=  10;										/* case the compiler prolog puts variables above the stack  */

																		/* Stack Frame Initialization							   */
	*--pxTopOfStack = (portLONG)msr;											  /* MSR													  */
	*--pxTopOfStack = 0;														/* EABI padding											 */
	*--pxTopOfStack = 0;														/* EABI padding											 */
	*--pxTopOfStack = 0;														/* SPEFSCR												  */
	*--pxTopOfStack = (portLONG)vPortEndScheduler;											 /* LR													   */
	*--pxTopOfStack = 0;														/* CR													   */
	*--pxTopOfStack = 0;														/* XER													  */
	*--pxTopOfStack = 0;														/* CTR													  */
	*--pxTopOfStack = 0;														/* USPRG0												   */
	*--pxTopOfStack = (portLONG)srr1;											 /* SRR1													 */
	*--pxTopOfStack = (portLONG)pxCode;											 /* SRR0													 */
	*--pxTopOfStack = 0;														/* R0													   */
	*--pxTopOfStack = 0x31L;													/* r31													  */
	*--pxTopOfStack = 0x30L;													/* r30													  */
	*--pxTopOfStack = 0x29L;													/* r29													  */
	*--pxTopOfStack = 0x28L;													/* r28													  */
	*--pxTopOfStack = 0x27L;													/* r27													  */
	*--pxTopOfStack = 0x26L;													/* r26													  */
	*--pxTopOfStack = 0x25L;													/* r25													  */
	*--pxTopOfStack = 0x24L;													/* r24													  */
	*--pxTopOfStack = 0x23L;													/* r23													  */
	*--pxTopOfStack = 0x22L;													/* r22													  */
	*--pxTopOfStack = 0x21L;													/* r21													  */
	*--pxTopOfStack = 0x20L;													/* r20													  */
	*--pxTopOfStack = 0x19L;													/* r19													  */
	*--pxTopOfStack = 0x18L;													/* r18													  */
	*--pxTopOfStack = 0x17L;													/* r17													  */
	*--pxTopOfStack = 0x16L;													/* r16													  */
	*--pxTopOfStack = 0x15L;													/* r15													  */
	*--pxTopOfStack = 0x14L;													/* r14													  */
	*--pxTopOfStack = (portLONG)&_SDA_BASE_;									  /* r13													  */
	*--pxTopOfStack = 0x12L;													/* r12													  */
	*--pxTopOfStack = 0x11L;													/* r11													  */
	*--pxTopOfStack = 0x10L;													/* r10													  */
	*--pxTopOfStack = 0x9L;													 /* r09													  */
	*--pxTopOfStack = 0x8L;													 /* r08													  */
	*--pxTopOfStack = 0x7L;													 /* r07													  */
	*--pxTopOfStack = 0x6L;													 /* r06													  */
	*--pxTopOfStack = 0x5L;													 /* r05													  */
	*--pxTopOfStack = 0x4L;													 /* r04													  */
	*--pxTopOfStack = (portLONG)pvParameters;											/* r03													  */
	*--pxTopOfStack = (portLONG)&_SDA2_BASE_;									 /* r02													  */
	*--pxTopOfStack = 0;														/* BLANK for 0xA0 size									  */
	*--pxTopOfStack = (portLONG)pxTopOfStack;											 /* Stack Ptr												*/
	return(pxTopOfStack);
}
/*-----------------------------------------------------------*/

void vPortEndScheduler( void )
{
	/* It is unlikely that the HCS12 port will get stopped. */
	for(;;);
}
/*-----------------------------------------------------------*/
#if (configTickSrc==configRTI)
#include "IntcInterrupts.h"
#endif
static void prvSetupTimerInterrupt( void )
{
	TickTimer_SetFreqHz( configTICK_RATE_HZ );
	INTC.CPR.B.PRI = 0;/* Lower INTC's current priority */
}
/*-----------------------------------------------------------*/

portBASE_TYPE xPortStartScheduler( void )
{
	return xStartFirstTask();
}
/*-----------------------------------------------------------*/

extern volatile void * pxCurrentTCB;
extern volatile unsigned portBASE_TYPE uxCriticalNesting;
static asm void prvStartFirstTask( void )
{
nofralloc
	portRESTORE_CONTEXT();

	/* Simulate the end of an interrupt to start the scheduler off. */
	rfi
}
static portBASE_TYPE xStartFirstTask( void )
{
	/* Configure the timer that will generate the RTOS tick.  Interrupts are
	disabled when this function is called. */
	prvSetupTimerInterrupt();

	prvStartFirstTask();

	/* Should not get here! */
	return pdFALSE;
}
/*-----------------------------------------------------------*/

#pragma section RX ".__exception_handlers"
#pragma push /* Save the current state */
__declspec (section ".__exception_handlers") extern long EXCEPTION_HANDLERS;  
#pragma force_active on
#pragma function_align 16 /* We use 16 bytes alignment for Exception handlers */
__declspec(interrupt)
__declspec (section ".__exception_handlers")
asm void vPortYield( void )
{
nofralloc
prolog:
	portSAVE_CONTEXT();
	
	/*invoke vTaskSwitchContext()*/
	lis r3,vTaskSwitchContext@h
	ori r3,r3,vTaskSwitchContext@l
	mtlr r3
	blrl
	
epilog:
	portRESTORE_CONTEXT();
	/* End of Interrupt */
	rfi
}

/*-----------------------------------------------------------*/

/*
 * RTOS tick interrupt service routine.  If the cooperative scheduler is 
 * being used then this simply increments the tick count.  If the 
 * preemptive scheduler is being used a context switch can occur.
 */

void asm vPortTickInterrupt( void )
{
nofralloc
	#if configUSE_PREEMPTION == 1
prolog:
	portSAVE_CONTEXT();
	
	/* Increment the tick ... */
	lis r3,xTaskIncrementTick@h
	ori r3,r3,xTaskIncrementTick@l
	mtlr r3
	blrl
	
	/* ... then see if the new tick value has necessitated a
	context switch. */
	lis r3,vTaskSwitchContext@h
	ori r3,r3,vTaskSwitchContext@l
	mtlr r3
	blrl
	
epilog:
	/*Clear TSR[DIS]*/
	lis r3,0x0800;
	mtspr TSR,r3;
	portRESTORE_CONTEXT();
	/* End of Interrupt */	
	rfi
	#else
	/*invoke vTaskIncrementTick()*/
	lis r3,vTaskIncrementTick@h
	ori r3,r3,vTaskIncrementTick@l
	mtlr r3
	blrl
	#endif
}
#pragma force_active off
#pragma pop


