/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            i8259.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


#include "Std_Types.h"
#include "mmu.h"
#include "Os.h"
#ifdef USE_STDRT
#include "rthw.h"
#endif
/* 8259A interrupt controller ports. */
#define	INT_M_CTL	0x20	/* I/O port for interrupt controller         <Master> */
#define	INT_M_CTLMASK	0x21	/* setting bits in this port disables ints   <Master> */
#define	INT_S_CTL	0xA0	/* I/O port for second interrupt controller  <Slave>  */
#define	INT_S_CTLMASK	0xA1	/* setting bits in this port disables ints   <Slave>  */

/* Hardware interrupts */
#define	NR_IRQ		16	/* Number of IRQs */
#define	CLOCK_IRQ	0
#define	KEYBOARD_IRQ	1
#define	CASCADE_IRQ	2	/* cascade enable for 2nd AT controller */
#define	ETHER_IRQ	3	/* default ethernet interrupt vector */
#define	SECONDARY_IRQ	3	/* RS232 interrupt vector for port 2 */
#define	RS232_IRQ	4	/* RS232 interrupt vector for port 1 */
#define	XT_WINI_IRQ	5	/* xt winchester */
#define	FLOPPY_IRQ	6	/* floppy disk */
#define	PRINTER_IRQ	7
#define	AT_WINI_IRQ	14	/* at winchester */

/* 8253/8254 PIT (Programmable Interval Timer) */
#define TIMER0          0x40	/* I/O port for timer channel 0 */
#define TIMER_MODE      0x43	/* I/O port for timer mode control */
#define RATE_GENERATOR	0x34	/* 00-11-010-0 : Counter0 - LSB then MSB - rate generator - binary */
#define TIMER_FREQ	1193182L/* clock frequency for timer in PC and AT */
#define HZ	1000	/* clock freq (software settable on IBM-PC) */

typedef	void	(*t_pf_irq_handler)	(int irq);

t_pf_irq_handler	irq_table[NR_IRQ];

void out_byte(unsigned int port, unsigned char value);
void spurious_irq(int irq);
extern void Os_PortSysTick(void);
extern void enable_irq(unsigned int irq);
extern void disable_irq(unsigned int irq);
/*======================================================================*
                            init_8259A
 *======================================================================*/
void init_8259A()
{
	out_byte(INT_M_CTL,	0x11);			// Master 8259, ICW1.
	out_byte(INT_S_CTL,	0x11);			// Slave  8259, ICW1.
	out_byte(INT_M_CTLMASK,	INT_VECTOR_IRQ0);	// Master 8259, ICW2. 设置 '主8259' 的中断入口地址为 0x20.
	out_byte(INT_S_CTLMASK,	INT_VECTOR_IRQ8);	// Slave  8259, ICW2. 设置 '从8259' 的中断入口地址为 0x28
	out_byte(INT_M_CTLMASK,	0x4);			// Master 8259, ICW3. IR2 对应 '从8259'.
	out_byte(INT_S_CTLMASK,	0x2);			// Slave  8259, ICW3. 对应 '主8259' 的 IR2.
	out_byte(INT_M_CTLMASK,	0x1);			// Master 8259, ICW4.
	out_byte(INT_S_CTLMASK,	0x1);			// Slave  8259, ICW4.

	out_byte(INT_M_CTLMASK,	0xFF);	// Master 8259, OCW1.
	out_byte(INT_S_CTLMASK,	0xFF);	// Slave  8259, OCW1.

	int i;
	for(i=0;i<NR_IRQ;i++){
		irq_table[i]	= spurious_irq;
	}
}

/*======================================================================*
                            put_irq_handler
 *======================================================================*/
void put_irq_handler(int irq, t_pf_irq_handler handler)
{
	disable_irq(irq);
	irq_table[irq] = handler;
}

/*======================================================================*
                           spurious_irq
 *======================================================================*/
void spurious_irq(int irq)
{
	printf("spurious_irq: %d\n",irq);
}

extern void serial_isr(void);

void serial_enable_rx(void)
{
	put_irq_handler(RS232_IRQ, (t_pf_irq_handler)serial_isr);
	enable_irq(RS232_IRQ);
}
#ifdef USE_STDRT
static void rt_timer_handler(int vector, void* param)
{
	rt_tick_increase();
}
#endif

void init_clock(void)
{
	/* 初始化 8253 PIT */
	out_byte(TIMER_MODE, RATE_GENERATOR);
	out_byte(TIMER0, (uint8_t) (TIMER_FREQ/HZ) );
	out_byte(TIMER0, (uint8_t) ((TIMER_FREQ/HZ) >> 8));
#ifndef USE_STDRT
	put_irq_handler(CLOCK_IRQ, (t_pf_irq_handler)Os_PortSysTick);	/* 设定时钟中断处理程序 */
	enable_irq(CLOCK_IRQ);				/* 让8259A可以接收时钟中断 */

	serial_enable_rx();
#else
	/* install interrupt handler */
	rt_hw_interrupt_install(CLOCK_IRQ, rt_timer_handler, RT_NULL, "tick");
	rt_hw_interrupt_umask(CLOCK_IRQ);
#endif
}

void rt_hw_timer_init(void)
{
	init_clock();
}



