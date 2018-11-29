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
#include "Mcu.h"
#include "portable.h"
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
#define AS_LOG_OS  5
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
extern const uint32 __vector_table[];
#if (ISR_NUM > 0)
extern const FP tisr_pc[ISR_NUM];
#endif
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */

void systick_handler(void)
{
	OsTick();
}

void StartOsTick(void)
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

	if (SysTick_Config(McuE_GetSystemClock() / 1000)) { /* Capture error */ while (1); }
}


void knl_isr_handler(uint32_t intno)
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
void svcall_handler(void)		{ printf("svcall_handler\n");while(1);}
void pendsv_handler(void)		{ printf("pendsv_handler\n");while(1);}
