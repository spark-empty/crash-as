/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2018  AS <parai@foxmail.com>
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
#ifndef _STDIO_CFG_H_
#define _STDIO_CFG_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Os.h"
#include "ringbuffer.h"
/* ============================ [ MACROS    ] ====================================================== */
/* #define NO_STDIO_RINGBUFFER */

#ifndef NO_STDIO_RINGBUFFER
#define FLUSH_STDIO_IF(e)		\
	do {						\
		if(e) {					\
			flush_stdio();		\
		}						\
	} while(0)
#else
#define FLUSH_STDIO_IF(e)
#endif

#ifndef STDIO_RINGBUFFER_SIZE
#define STDIO_RINGBUFFER_SIZE 512
#endif
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
#ifdef USE_USB_SERIAL
extern void USB_SerialPutChar(char ch);
#endif

extern void Stdio_PutChar(char ch);
/* ============================ [ DATAS     ] ====================================================== */
RB_DECLARE(stdio, char, STDIO_RINGBUFFER_SIZE);
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifndef NO_STDIO_RINGBUFFER
void flush_stdio(void)
{
	char ch0;
	rb_size_t r0;
	imask_t imask;

	Irq_Save(imask);
	r0 = RB_Pop(&rb_stdio, &ch0, 1);
	Irq_Restore(imask);

	if(1 == r0)
	{
		Stdio_PutChar(ch0);
	}
}
#endif

void __putchar(char ch)
{
#ifndef NO_STDIO_RINGBUFFER
	rb_size_t r;
	imask_t imask;
	do {
		Irq_Save(imask);
		r = RB_Push(&rb_stdio, &ch, 1);
		Irq_Restore(imask);
		if(0 == r)
		{
			flush_stdio();
		}
	} while(r != 1);
#else
	Stdio_PutChar(ch);
#endif

#ifdef USE_USB_SERIAL
	USB_SerialPutChar(ch);
#endif

}

#ifndef __GNUC__
int putchar( int ch )	/* for printf */
{
	__putchar(ch);
	return ch;
}
#endif
#endif /* _STDIO_CFG_H_ */
