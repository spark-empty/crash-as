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
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
extern void KsmCANIdle_Init                    (void);
extern void KsmCANIdle_Start                   (void);
extern void KsmCANIdle_Stop                    (void);
extern void KsmCANIdle_Running                 (void);
/* ============================ [ DATAS     ] ====================================================== */
static const KsmFunction_Type KsmCANIdle_FunctionList[4] = 
{
	KsmCANIdle_Init                    ,
	KsmCANIdle_Start                   ,
	KsmCANIdle_Stop                    ,
	KsmCANIdle_Running                 ,
};
const KSM_Type KSM_Config[KSM_NUM] = 
{
	{ /* CANIdle */
		4,
		KsmCANIdle_FunctionList
	},
};

/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
