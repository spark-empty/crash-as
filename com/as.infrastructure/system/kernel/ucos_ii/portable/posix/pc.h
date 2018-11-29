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
#ifndef _PC_H_
#define _PC_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include <ncurses.h>
#include <stdlib.h>
#include "ucos_ii.h"
/* ============================ [ MACROS    ] ====================================================== */
#ifndef COLOR_GRAY
#define COLOR_GRAY COLOR_MAGENTA
#endif

/* check curses.h, color value is from 0 to 7*/
#define DISP_FGND_BLACK           COLOR_BLACK
#define DISP_FGND_BLUE            COLOR_BLUE
#define DISP_FGND_GREEN           COLOR_GREEN
#define DISP_FGND_RED             COLOR_RED
#define DISP_FGND_CYAN            COLOR_CYAN
#define DISP_FGND_YELLOW          COLOR_YELLOW
#define DISP_FGND_WHITE           COLOR_WHITE
#define DISP_FGND_GRAY            COLOR_GRAY

#define DISP_BGND_BLACK           (COLOR_BLACK<<4)
#define DISP_BGND_BLUE            (COLOR_BLUE<<4)
#define DISP_BGND_GREEN           (COLOR_GREEN<<4)
#define DISP_BGND_RED             (COLOR_RED<<4)
#define DISP_BGND_CYAN            (COLOR_CYAN<<4)
#define DISP_BGND_YELLOW          (COLOR_YELLOW<<4)
#define DISP_BGND_WHITE           (COLOR_WHITE<<4)
#define DISP_BGND_GRAY            (COLOR_GRAY<<4)
#define DISP_BGND_LIGHT_GRAY      (COLOR_GRAY<<4)

#define DISP_BLINK                (A_BLINK<<8)

#define PC_VectSet(irq, isr)
#define PC_VectGet(irq) NULL


/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void PC_DispChar(INT8U x, INT8U y, INT8U c, INT32U color);
void PC_DispClrScr(INT32U bgnd_color);
void PC_DispStr(INT8U x, INT8U y, INT8U * s, INT32U color);

void PC_ElapsedInit(void);
void PC_ElapsedStart(INT8U n);
INT32U PC_ElapsedStop(INT8U n);

void PC_GetDateTime(char *s);
BOOLEAN PC_GetKey(INT16S * c);

void PC_DOSSaveReturn(void);
void PC_DOSReturn(void);
void PC_SetTickRate(INT16U freq);

#endif /* _PC_H_ */
