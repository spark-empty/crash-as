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
#ifndef PORTABLE_H_
#define PORTABLE_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#ifndef _MACRO_ONLY
#if  defined(CHIP_STM32F10X)
#include "stm32f10x.h"
#elif defined(CHIP_AT91SAM3S)
#include "SAM3S.h"
#include "board.h"
#elif defined(CHIP_LM3S6965)
#include "hw_ints.h"
#else
#error "CHIP is not known, please select the CHIP_STM32F10X or CHIP_AT91SAM3S"
#endif
#include <core_cm3.h>
#endif
/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifndef _MACRO_ONLY
extern void StartOsTick(void);
#endif
#endif /* PORTABLE_H_ */
