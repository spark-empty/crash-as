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
 * SgDraw: static GUI basic draw function
 */
#ifndef COM_CLANG_INCLUDE_SGDRAW_H_
#define COM_CLANG_INCLUDE_SGDRAW_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"

/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */

/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void Sg_DrawPixel(int x,int y,uint32 color);
void Sg_DrawLine(int x0,int y0,int x1,int y1,uint32 color);
void Sg_FillArea(int x, int y, int cx, int cy, uint32 color);
void Sg_DrawCircle(int x, int y, int radius, uint32 color);
void Sg_FillCircle(int x, int y, int radius, uint32 color);
void Sg_DrawEllipse(int x, int y, int a, int b, uint32 color);
void Sg_FillEllipse(int x, int y, int a, int b, uint32 color);

void Sg_Update(void);
#endif /* COM_CLANG_INCLUDE_SGDRAW_H_ */
