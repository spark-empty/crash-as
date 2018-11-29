#include "SystemConfig.h"

#ifdef __arch_raspi__
#include "uart.h"
#include "regs.h"
#include "timer.h"
#include "interrupts.h"
#endif

#ifdef __arch_9s12xep100__
#include <hidef.h>
#include <MC9S12XEP100.h>
#pragma LINK_INFO DERIVATIVE "MC9S12XEP100"
#endif

#if defined(__arch_dos__) || defined(__arch_posix__)
#include "pc.h"
#include "rs232.h"
#endif

OS_STK MainTask_Stk[MainTask_StkSize];
OS_STK App1Task_Stk[App1Task_StkSize];
OS_STK App2Task_Stk[App2Task_StkSize];

#ifdef __arch_9s12xep100__
#define  BUS_CLOCK   32000000
#define  OSC_CLOCK   16000000

void Sci_Init(){
	SCI0BD = BUS_CLOCK/16/115200;
	SCI0CR1 = 0x00;
	SCI0CR2 = 0x0c;
}

void TERMIO_PutChar(char ch)
{
	while(!(SCI0SR1&0x80)) ;
	SCI0DRL = ch;
}

void Initialize_PLL(void) 
{
    CRGINT = 0; /* disable interrupt */
    CLKSEL_PLLSEL = 0;
    
#if(BUS_CLOCK == 40000000) 
    SYNR = 4;
#elif(BUS_CLOCK == 32000000)
    SYNR = 3;     
#elif(BUS_CLOCK == 24000000)
    SYNR = 2;
#endif 

    REFDV = 1;
    PLLCTL_PLLON = 1;

    while (CRGFLG_LOCK == 0);
    CLKSEL_PLLSEL = 1;
}

void Initialize_RTI(void) 
{
	CRGINT_RTIE=1;
	RTICTL = 0x70;
	CRGINT = 1; /* enable interrupt */
}
#endif /* __arch_9s12xep100 */

int demo_main(void)
{
#ifdef __arch_raspi__
	uart_init();

	InitInterruptController();

	DisableInterrupts();

	timer_init();
#endif

#ifdef __arch_9s12xep100__
	Initialize_PLL();
	Sci_Init();
#endif

#if defined(__arch_dos__) || defined(__arch_posix__)
	PC_DispClrScr(DISP_FGND_WHITE + DISP_BGND_BLACK);      /* Clear the screen                         */
#endif

	OSInit();                                              /* Initialize uC/OS-II                      */

#if defined(__arch_dos__) || defined(__arch_posix__)
	PC_DOSSaveReturn();                                    /* Save environment to return to DOS        */
	PC_VectSet(uCOS, OSCtxSw);
#endif


	OSTaskCreate(MainTask, (void *)0, &MainTask_Stk[MainTask_StkSize-1], MainTask_Prio);
	OSStart();
	return 0;
}

void MainTask(void *p_arg)
{
#if defined(__arch_dos__) || defined(__arch_posix__)
#if      OS_CRITICAL_METHOD == 3
	OS_CPU_SR cpu_sr;
#endif
#endif
	p_arg = p_arg;

#ifdef __arch_9s12xep100__
	Initialize_RTI(); /* start the system tick timer */
#endif

#if defined(__arch_dos__) || defined(__arch_posix__)
    OS_ENTER_CRITICAL();
    PC_VectSet(0x08, OSTickISR);                           /* Install uC/OS-II's clock tick ISR        */
    PC_SetTickRate(OS_TICKS_PER_SEC);                      /* Reprogram tick rate                      */
    OS_EXIT_CRITICAL();
#endif

	OSStatInit();
	while(1)
	{

		OSTaskCreate(App1Task, (void *)0, &App1Task_Stk[App1Task_StkSize-1], App1Task_Prio);
		OSTaskCreate(App2Task, (void *)0, &App2Task_Stk[App2Task_StkSize-1], App2Task_Prio);
		printf("Hello,I am Main!\n");
		OSTimeDlyHMSM(0, 0, 5, 0);
		printf("Hello,Main End!\n");
        OSTaskDel(MainTask_Prio);
	}
}
/* App1Task */
void App1Task(void *p_arg)
{
	int i = 0;
	p_arg = p_arg;
	while(1)
	{
		printf("Hello,I am PC %d!\n",i++);
		OSTimeDlyHMSM(0, 0, 1, 0);
	}
}
/* App2Task */
void App2Task(void *p_arg)
{
	int i = 0;
	p_arg = p_arg;
	while(1)
	{
		printf("Hello,uCOS-II %d!\n",i++);
		OSTimeDlyHMSM(0, 0, 2, 0);
	}
}

void OSDebugInit()
{
}

int main(int argc,char* argv[])
{
#if defined(__arch_dos__) || defined(__arch_posix__)
	extern int  ex_main (void);
	if( (2 == argc) && (0 == strcmp(argv[1],"ex")))
	{
		return ex_main();
	}

	extern int tool_main(const char* comport);
	if( (3 == argc) && (0 == strcmp(argv[1],"-c")))
	{
		return tool_main(argv[2]);
	}
#endif

	return demo_main();
}


#if defined(__arch_dos__) || defined(__arch_posix__)
int tool_main(const char* comport)
{
	INT8U chr;
	int ret;
	INT8U r_cache[1024];
	size_t r_size = 0;
	int port = atoi(comport);
	INT8U x,y,c;
	INT16S key;

	if( 0 != RS232_OpenComport(port,115200,"8N1"))
	{
		return -1;
	}

	PC_DOSSaveReturn();
	PC_DispClrScr(DISP_FGND_WHITE + DISP_BGND_BLACK);      /* Clear the screen                         */

	while(1)
	{
		ret = RS232_PollComport(port,(unsigned char*)&chr,1);
		if( 1 == ret )
		{
			if(('\n' == chr) || ('\r' == chr))
			{ /* CMD: '$XYC...STRING...' */
				if((r_size > 4) && ('$' == r_cache[0]))
				{
					x = r_cache[1];
					y = r_cache[2];
					c = r_cache[3];
					r_cache[r_size] = '\0';
					PC_DispStr(x,y,&r_cache[4],c);
				}
				else if((3==r_size) && ('$' == r_cache[0]) && ('$' == r_cache[1]))
				{
					c = r_cache[2];
					PC_DispClrScr(c);
				}
				r_size = 0;
			}
			else
			{
				r_cache[r_size] = chr;
				r_size++; 
				if(r_size >= sizeof(r_cache))
				{
					r_size = 0; /* reset as some error */
				}
			}
		}

		if(PC_GetKey(&key))
		{
			ret = RS232_SendByte(port, key);
			if(0 != ret)
			{
				break; /* something wrong*/
			}
		}
	}

	return 0;
}
#endif

