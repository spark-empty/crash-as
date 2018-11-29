#ifndef _PORTABLE_H_
#define _PORTABLE_H_
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
#include "Std_Types.h"

/* ============================ [ MACROS    ] ====================================================== */
#define OMIT_STKMPUINFOB
#define OMIT_OSAPMPUINFOB

#define TOPPERS_SVC_FUNCCALL
#define TARGET_SVC_NUM 0
#define TARGET_SVC_TABLE

#define SIL_PRE_LOC
#define SIL_LOC_INT()
#define SIL_UNL_INT()
/* ============================ [ TYPES     ] ====================================================== */
typedef uint32   uintptr;
typedef sint32   sintptr;
typedef char     char8;

typedef struct{
	void* sp;
	void  (*pc)(void);
}TSKCTXB;
/* ============================ [ DECLARES  ] ====================================================== */
#define TP_TIMER_MAX_TICK ((TickType)0xFFFFFFFF)
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
extern void target_initialize(void);
extern void target_exit(void);

extern void dispatch(void);
extern void start_dispatch(void);
extern void exit_and_dispatch(void);
extern void exit_and_dispatch_nohook(void);
#endif /* _PORTABLE_H_ */
