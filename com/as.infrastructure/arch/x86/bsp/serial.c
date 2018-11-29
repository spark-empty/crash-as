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
#ifdef USE_SHELL
#include "shell.h"
#endif
#include "kernel_internal.h"
/* ============================ [ MACROS    ] ====================================================== */
/*******************************************************************/
/* Serial Register */
/*******************************************************************/
/*Serial I/O code */
#define COM1				0x3F8
#define COMSTATUS			5
#define COMDATA				0x01
#define COMREAD				0
#define COMWRITE			0

/* Bits definition of the Line Status Register (LSR)*/
#define DR					0x01	/* Data Ready */
#define OE					0x02	/* Overrun Error */
#define PE					0x04	/* Parity Error */
#define FE					0x08	/* Framing Error */
#define BI					0x10	/* Break Interrupt */
#define THRE				0x20	/* Transmitter Holding Register Empty */
#define TEMT				0x40	/* Transmitter Empty */
#define ERFIFO				0x80	/* Error receive Fifo */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void serial_init(void)
{
	outb(COM1+3,0x80);	/* set DLAB of line control reg */
	outb(COM1,0x0c);	/* LS of divisor (48 -> 2400 bps */
	outb(COM1+1,0x00);	/* MS of divisor */
	outb(COM1+3,0x03);	/* reset DLAB */
	outb(COM1+4,0x0b);	/* set DTR,RTS, OUT_2 */
	outb(COM1+1,0x0d);	/* enable all intrs but writes */
	inb(COM1);			/* read data port to reset things (?) */
}

char serial_getc(void)
{

	while(!(inb(COM1+COMSTATUS) & COMDATA));

	return inb(COM1+COMREAD);

}

void serial_putc(const char c)
{
	int val;

	while(1)
	{
		if ((val = inb(COM1+COMSTATUS)) & THRE)
			break;
	}

	outb(COM1+COMWRITE, c&0xff);
}

void serial_isr(void)
{

	char c;

	EnterISR();

	while((inb(COM1+COMSTATUS) & COMDATA)) {
		c = inb(COM1+COMREAD);
		#ifdef USE_SHELL
		if(0x7f == c) c = '\b';
		if('\r' == c) c = '\n';
		SHELL_input(c);
		#endif
	}

	LeaveISR();
}
