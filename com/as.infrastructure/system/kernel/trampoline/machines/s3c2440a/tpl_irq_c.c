/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2017  AS <parai@foxmail.com>
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
#include "s3c2440.h"
#include "asdebug.h"
#include "tpl_os_os_kernel.h"
#include "Mcu.h"
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
extern const tpl_callback_func tisr_pc[ ISR_NUM ];

extern FUNC(tpl_bool, OS_CODE) tpl_call_counter_tick(void);
/* ============================ [ DATAS     ] ====================================================== */

/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void    x_enable_int(uint32_t intno) {
	if(intno < 32)
	{
		INTMSK &= ~(1<<intno);
	}
	else if(intno < 46)
	{
		INTSUBMSK &= ~(1<<(intno-32));
	}
	else
	{
		asAssert(0);
	}
}

void tpl_init_machine(void) {
	/* timer4, pre = 15+1 */
	TCFG0 &= 0xffff00ff;
	TCFG0 |= 15 << 8;
	/* all are interrupt mode,set Timer 4 MUX 1/4 */
	TCFG1  &= 0xfff0ffff;
	TCFG1  |= 0x00010000;

	TCNTB4 = (uint32_t)(McuE_GetSystemClock() / (4 *16* 1000)) - 1;	/* 1000 ticks per second */
	/* manual update */
	TCON = TCON & (~(0x0f<<20)) | (0x02<<20);

	/* enable interrupt */
	INTMSK &= ~BIT_TIMER4;

    /* start timer4, reload */
	TCON = TCON & (~(0x0f<<20)) | (0x05<<20);
}

void    x_disable_int(uint32_t intno) {
	if(intno < 32)
	{
		INTMSK |= (1<<intno);
	}
	else if(intno < 46)
	{
		INTSUBMSK |= (1<<(intno-32));
	}
	else
	{
		asAssert(0);
	}
}

void x_clear_int(uint32_t intno)
{
	if(intno < 32)
	{
		SRCPND |= (1<<intno);
		INTPND = INTPND;
	}
	else if(intno < 46)
	{
		SUBSRCPND |= (1<<(intno-32));
	}
	else
	{
		asAssert(0);
	}
}

void tpl_shutdown(void)
{
	while(1);
}

void tpl_arm_subarch_irq_handler(void)
{
	uint32_t intno;

	intno = INTOFFSET;
	if(intno < ISR_NUM)
	{
		if(tisr_pc[intno] != NULL)
		{
			x_disable_int(intno);
			tisr_pc[intno]();
			x_enable_int(intno);
		}
		else
		{
			tpl_shutdown_os_service(0xFF);
		}

		x_clear_int(intno);
	}
	else
	{
		tpl_shutdown_os_service(0xFF);
	}
}

void knl_isr_handler(void)
{
	tpl_arm_subarch_irq_handler();
}

ISR(TIMER4)
{
	tpl_call_counter_tick();
}
