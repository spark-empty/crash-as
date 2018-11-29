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

#include <assert.h>
#include <string.h>
#include "Std_Types.h"
#include "Mcu.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#if defined(USE_DEM)
#include "Dem.h"
#endif
#if defined(USE_DIO)
#include "Dio.h"
#endif
//#include "Cpu.h"
//#include "Ramlog.h"
#include "Os.h"
//#include "isr.h"

//#define USE_LDEBUG_PRINTF 1
#include "asdebug.h"

#include "mpc56xx.h"

#if(CPU_FREQUENCY==8)
#define SYNCR_V 0x36100000
#endif
#if(CPU_FREQUENCY==16)
#define SYNCR_V 0x16100000
#endif
#if(CPU_FREQUENCY==20)
#define SYNCR_V 0x18100000
#endif
#if(CPU_FREQUENCY==32)
#define SYNCR_V 0x16080000
#endif
#if(CPU_FREQUENCY==40)
#define SYNCR_V 0x18080000
#endif
#if(CPU_FREQUENCY==50)
#define SYNCR_V 0x1A880000
#endif
#if(CPU_FREQUENCY==60)
#define SYNCR_V 0x15800000
#endif
#if(CPU_FREQUENCY==64)
#define SYNCR_V 0x16000000	/**PREFDIV=1,MFD=12,RFD=0,->Fsys=64MHZ*/
#endif
#if(CPU_FREQUENCY==80) /**PREFDIV=1,MFD=16,RFD=0,->Fsys=80MHZ*/
#define SYNCR_V 0x18000000
#endif



void InitializeUART(void) {
	ESCI_A.CR2.R = 0x2000;
	ESCI_A.CR1.R =(((CPU_FREQUENCY*1000000/(16*115200))<<16)|0x0000000c);
	SIU.PCR[89].R = 0x400;
	SIU.PCR[90].R = 0x400;
}
char ReadUARTN(void) {
	while (ESCI_A.SR.B.RDRF == 0) {}    /* Wait for receive data reg full = 1 */
	ESCI_A.SR.R = 0x20000000;           /* Clear RDRF flag */
	return ESCI_A.DR.B.D;               /* Read byte of Data*/
}

void WriteUARTN(char ch) {
	while (ESCI_A.SR.B.TDRE == 0) {}
	ESCI_A.SR.R = 0x80000000;
	ESCI_A.DR.B.D = ch;
}

void __putchar (char data) {
	WriteUARTN(data);
}

void Mcu_Init(const Mcu_ConfigType *configPtr)
{
	(void)configPtr;
}

void Mcu_SetMode( Mcu_ModeType McuMode ) {
	(void)McuMode;
}

/**
 * Get the system clock in Hz. It calculates the clock from the
 * different register settings in HW.
 */
uint32_t McuE_GetSystemClock(void)
{
  return CPU_FREQUENCY*1000000;
}

uint32_t McuE_GetPeripheralClock(McuE_PeriperalClock_t type)
{
	uint32_t clk = 0;

	switch(type)
	{
		case 0: /* CAN */
			clk = CPU_FREQUENCY*1000000;
			break;
	}
	return clk;
}

uint32_t McuE_GetClockReferencePointFrequency(void)
{
	return 0;
}

Std_ReturnType Mcu_InitClock( const Mcu_ClockType ClockSetting ) {
	/**
	 * Fref=8MHZ(CRYSTAL OSCILLATOR CLOCK)
	 * In legacy mode:Fsys=Fref*(MFD+4)/(PREFDIV+1)/(2^RFD)
	 * In enhanced mode:Fsys=Fref*(EMFD)/(EPREFDIV+1)/(2^(ERFD+1))
	 */
	(void) ClockSetting;
	FMPLL.ESYNCR1.B.CLKCFG = 0X7;
	FMPLL.SYNCR.R = 0x16080000;/**PREFDIV=1,MFD=12,RFD=1,->Fsys=32MHZ*/
	while (FMPLL.SYNSR.B.LOCK != 1) {};
	FMPLL.SYNCR.R = SYNCR_V;
	return E_OK;
}

void Mcu_PerformReset( void ) {
	SIU.SRCR.B.SSR = 1;
}

Mcu_PllStatusType Mcu_GetPllStatus( void ) {
	return MCU_PLL_LOCKED;
}


Mcu_ResetType Mcu_GetResetReason(void)
{
	Mcu_ResetType rv;

	if( SIU.RSR.B.SSRS ) {
		rv = MCU_SW_RESET;
	} else if( SIU.RSR.B.WDRS ) {
		rv = MCU_WATCHDOG_RESET;
	} else if( SIU.RSR.B.PORS || SIU.RSR.B.ERS ) {
		rv = MCU_POWER_ON_RESET;
	} else {
		rv = MCU_RESET_UNDEFINED;
	}

	return rv;
}

void TickTimer_SetFreqHz(int Freq)
{
/* use Decrementer as the System Tick*/
	int  decr=CPU_FREQUENCY*1000000/Freq;
	__asm{
		li		r0, 0x0000
		mthid0	r0
/*Set the gap time between tick and tick*/
		lwz     r0,decr
		mtdec	r0
		mtdecar	r0
/*Set TCR[DIE]=1,TCR[ARE]=1,that is to enable DEC interrupt and enable auto-reload*/
		lis		r0, 0x0440
		mftcr   r3
		or      r0,r0,r3
		mttcr	r0
/*Set HID0[TBEN]=1,Time base enable*/
		li		r0, 0x4000
		mthid0	r0
	}
}

void RTI_TickHandler(void)
{
#ifdef USE_TINYOS
	OsTick();
#endif
	PIT.RTI.TFLG.B.TIF=1;
}

#define POLLING_RTI

void RTI_SetFreqHz(int Freq)
{
	PIT.PITMCR.B.MDIS_RTI=0;/*turn on PIT just for RTI*/
	PIT.RTI.LDVAL.R=CPU_FREQUENCY*1000000/Freq-1;
#if !defined(USE_TINYOS) && defined(POLLING_RTI)
	PIT.RTI.TCTRL.B.TIE=1;	/*enable interrupt*/
#endif
	PIT.RTI.TCTRL.B.TEN=1;/*turn on RTI*/
	INTC_InstallINTCInterruptHandler(RTI_TickHandler,305,1);
}

#if defined(USE_TINYOS) && defined(POLLING_RTI)
void CheckOsTick(void)
{
	if(PIT.RTI.TFLG.B.TIF)
	{
		RTI_TickHandler();
	}
}
#endif

void TaskIdleHook(void)
{
#if defined(USE_TINYOS) && defined(POLLING_RTI)
	CheckOsTick();
#endif
#ifdef USE_SHELL
	extern void SHELL_input(char c);
	while(ESCI_A.SR.B.RDRF)
	{
		char ch = ReadUARTN();
		if('\r' == ch) ch = '\n';
		SHELL_input(ch);
	}
#endif
#if defined(USE_DIO)
	Dio_WriteChannel(DIO_PIN_LED1, Dio_ReadChannel(DIO_PIN_KEY1));
	Dio_WriteChannel(DIO_PIN_LED2, Dio_ReadChannel(DIO_PIN_KEY2));
	Dio_WriteChannel(DIO_PIN_LED3, Dio_ReadChannel(DIO_PIN_KEY3));
	Dio_WriteChannel(DIO_PIN_LED4, Dio_ReadChannel(DIO_PIN_KEY4));
#endif
}

void Mcu_DistributePllClock( void )
{
	InitializeUART();

#ifndef USE_TINYOS
	TickTimer_SetFreqHz(OS_TICKS_PER_SECOND);
	EXCEP_InitExceptionHandlers();
	INTC_InitINTCInterrupts();
	RTI_SetFreqHz(100);
#endif

	printf("reset reason is %d(0x%X)\n", Mcu_GetResetReason(), SIU.RSR.R);
}

void Irq_Enable(void)
{
	__asm("wrteei 1");
}

void Irq_Disable(void)
{
	__asm("wrteei 0");
}

asm imask_t __Irq_Save(void)
{
nofralloc
	mfmsr   r3
	wrteei  0
	blr
}

asm void Irq_Restore(imask_t mask)
{
nofralloc
	mtmsr   r3;
	blr
}

#ifdef USE_TINYOS
void StartOsTick(void)
{
	EXCEP_InitExceptionHandlers();
	INTC_InitINTCInterrupts();
	RTI_SetFreqHz(OS_TICKS_PER_SECOND);
	INTC.CPR.B.PRI = 0;
}
#endif

#ifdef __AS_BOOTLOADER__
void application_main(void)
{
	const struct appbam_s {
		uint32_t bam;
		void (*entry)(void);
	} *appbam = (struct appbam_s*)0x40000;
	printf("application bam is 0x%X, entry is 0x%X\n", appbam->bam, appbam->entry);
	if((0x015A015A == appbam->bam) && (NULL != appbam->entry))
	{
		appbam->entry();
	}
}
#endif

