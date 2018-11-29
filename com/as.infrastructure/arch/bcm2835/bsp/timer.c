#include <stdio.h>
#include "regs.h"
#include "interrupts.h"
#ifdef USE_UCOSII
#include "ucos_ii.h"
#else
#define OS_TICKS_PER_SEC 1000
#endif
extern INTERRUPT_VECTOR g_VectorTable[BCM2835_INTC_TOTAL_IRQ];

static void tickISR()
{
	#ifdef USE_UCOSII
	OSTimeTick();
    #elif defined(__AS_BOOTLOADER__)
	extern void OsTick(void);
	OsTick();
    #else
	extern void tpl_call_counter_tick();
	tpl_call_counter_tick();	
    #endif
	timerRegs->CLI = 0;
}


void timer_init( void )
{

	DisableInterrupt(64);

	g_VectorTable[64].pfnHandler=tickISR;

	timerRegs->CTL = 0x003E0000;
	timerRegs->LOD = 1000000/OS_TICKS_PER_SEC - 1;
	timerRegs->RLD = 1000000/OS_TICKS_PER_SEC - 1;
	timerRegs->DIV = 0xF9;
	timerRegs->CLI = 0;
	timerRegs->CTL = 0x003E00A2;

	EnableInterrupt(64);
}

void tpl_disable_os_interrupts(void)
{
	DisableInterrupt(64);
}

void tpl_enable_os_interrupts(void)
{
	EnableInterrupt(64);
}

void tpl_init_machine(void)
{

}

void tpl_shutdown(void)
{
    /* FIXME: this is does not conform to AUTOSAR OS specifications,
     * should return to main with initial context */
    DisableInterrupts ();

    /* TODO : fall into very low consumption mode : all
     * internal CPU clocks are disabled.
     */

    while (1);
}

