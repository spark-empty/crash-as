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

#ifndef _CONTIKI_CONF_H_
#define _CONTIKI_CONF_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include <stdint.h>
#include "sys/pt-sem.h"
#ifdef USE_UIP
#include "uip-conf.h"
#endif
/* ============================ [ MACROS    ] ====================================================== */
#define CCIF
#define CLIF

#define PROCESS_SEM_INIT(s, c) PT_SEM_INIT(s, c)
#define PROCESS_SEM_WAIT(s)    PT_SEM_WAIT(process_pt, s)
#define PROCESS_SEM_SIGNAL(s)  PT_SEM_SIGNAL(process_pt, s)

#if defined(__GNUC__)
#define PROTO_AUTOSTART_PROCESS_EXPORT(proc) \
	struct process * const __attribute__((section("ProtoSymTab"))) autostart_##proc = &proc
#define PROTO_AUTOSTART_PROCESS_END() \
	struct process * const __attribute__((section("ProtoSymTabEnd"))) autostart_end = NULL
#else
#define PROTO_AUTOSTART_PROCESS_EXPORT(proc)
#define PROTO_AUTOSTART_PROCESS_END()
#endif
/* ============================ [ TYPES     ] ====================================================== */
typedef unsigned long clock_time_t;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void StartContiki(void);
void ScheduleContiki(void);
#endif /* _CONTIKI_CONF_H_ */
