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
#include "pc.h"
#include <assert.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
/* ============================ [ MACROS    ] ====================================================== */
#define NTIMERS 8
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
static void (*interruptTable[512])();
static BOOLEAN lock=FALSE;
static struct timeval  prev_timeval[NTIMERS];
/* ============================ [ FUNCTIONS ] ====================================================== */

BOOLEAN PC_GetKey(INT16S *c)
{   
	return FALSE;
}

void PC_DispStr(INT8U x, INT8U y, INT8U * s, INT32U color)
{   
	int mx,my;
	
	if (lock) { return; } else { lock = TRUE; }

	getmaxyx(stdscr, my, mx);
    if ((x>mx) || (y>my))					
    {
		assert(0);
	}

	init_pair(1, color&0xF, (color>>4)&0xF);

	move(y, x);

    printw("%s", s);

	mvchgat(y, x, strlen(s), color>>8, 1, NULL);

	refresh();

	lock = FALSE;
}

void PC_DispChar(INT8U x, INT8U y, INT8U c, INT32U color)
{
	int mx,my;

	if (lock) { return; } else { lock = TRUE; }

	getmaxyx(stdscr, my, mx);
    if ((x>mx) || (y>my))					
    {
		assert(0);
	}

	init_pair(1, color&0xF, (color>>4)&0xF);

	move(y, x);

    printw("%c", c);

	mvchgat(y, x, 1, color>>8, 1, NULL);
	
	refresh();

	lock = FALSE;
}

void PC_DispClrScr(INT32U color)
{
	if (lock) { return; } else { lock = TRUE; }

	clear();
	refresh();

	lock = FALSE;
}

void PC_ElapsedInit(void)
{
}

void PC_ElapsedStart(INT8U n)
{
	assert(n < NTIMERS);

	gettimeofday(&prev_timeval[n],NULL);
}

INT32U PC_ElapsedStop(INT8U n)
{
	float rv;
	struct timeval m1;
	struct timeval* m0;
	assert(n < NTIMERS);
	
	gettimeofday(&m1,NULL);

	m0 = &prev_timeval[n];

	rv = m1.tv_sec-m0->tv_sec;

	if(m1.tv_usec > m0->tv_usec)
	{
		rv += (float)(m1.tv_usec-m0->tv_usec)/1000000.0;
	}
	else
	{
		rv = rv - 1 + (float)(1000000.0+m1.tv_usec-m0->tv_usec)/1000000.0;
	}

	return (INT32U)(rv*1000000);
}

void PC_GetDateTime(char *s)
{
	time_t t = time(0);
	struct tm* lt = localtime(&t);
    sprintf(s, "%04d-%02d-%02d  %02d:%02d:%02d",
            lt->tm_year+1900,
            lt->tm_mon,
            lt->tm_mday,
            lt->tm_hour,
            lt->tm_min,
            lt->tm_sec);
}

void PC_DOSSaveReturn(void)
{
	initscr();

	start_color();

}

void    PC_SetTickRate(INT16U freq)
{

}

void PC_DOSReturn(void)
{
	exit(0);
}

