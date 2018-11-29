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
#ifndef COM_AS_INFRASTRUCTURE_SYSTEM_KERNEL_TOPPERS_OSEK_PORTABLE_POSIX_PORTABLE_H_
#define COM_AS_INFRASTRUCTURE_SYSTEM_KERNEL_TOPPERS_OSEK_PORTABLE_POSIX_PORTABLE_H_
/* ============================ [ INCLUDES  ] ====================================================== */

/* ============================ [ MACROS    ] ====================================================== */
#define Inline static __inline__

/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
extern void disable_int(void);
extern void enable_int(void);

extern void dispatch(void);
extern void set_ipl(IPL ipl);
extern IPL  current_ipl(void);
extern void start_dispatch(void);
extern void exit_and_dispatch(void);
extern void activate_context(TaskType TaskID);

extern void cpu_terminate(void);
extern void sys_exit(void);

extern void cpu_initialize(void);
extern void sys_initialize(void);
extern void tool_initialize(void);

#endif /* COM_AS_INFRASTRUCTURE_SYSTEM_KERNEL_TOPPERS_OSEK_PORTABLE_POSIX_PORTABLE_H_ */
