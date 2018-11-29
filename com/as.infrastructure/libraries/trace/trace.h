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

#ifndef _TRACE_H_
#define _TRACE_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include <stdint.h>
#include "trace_cfg.h"
/* ============================ [ MACROS    ] ====================================================== */
#define TRACE_TIMER_TYPE_DOWN 0
#define TRACE_TIMER_TYPE_UP   1
/* ============================ [ TYPES     ] ====================================================== */

typedef struct
{
	uint32_t sumH;
	uint32_t sumL;
	uint32_t max;
	uint32_t min;
	uint32_t times;
	uint32_t tmp;
} Trace_PerfRecordType;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void Trace_Init(void);
void Trace_PerfStart(uint32_t Id);
void Trace_PerfStop(uint32_t Id);
void Trace_PerfReset(void);
#endif /* _TRACE_H_ */
