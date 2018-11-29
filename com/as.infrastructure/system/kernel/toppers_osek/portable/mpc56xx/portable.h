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
#ifndef _PORTABLE_H_
#define _PORTABLE_H_
/* ============================ [ INCLUDES  ] ====================================================== */

/* ============================ [ MACROS    ] ====================================================== */
#define disable_int()		__asm("wrteei 0")
#define enable_int()		__asm("wrteei 1")
#define dispatch()			__asm("sc")
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
extern void start_dispatch(void);
extern void exit_and_dispatch(void);

extern void set_ipl(IPL ipl);
extern IPL  current_ipl(void);
extern void activate_context(TaskType TaskID);

extern void cpu_terminate(void);
extern void sys_exit(void);

extern void cpu_initialize(void);
extern void sys_initialize(void);
extern void tool_initialize(void);
#endif /* _PORTABLE_H_ */
