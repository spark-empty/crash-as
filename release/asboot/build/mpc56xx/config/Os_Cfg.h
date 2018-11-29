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
#ifndef OS_CFG_H
#define OS_CFG_H

/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
#include "os_i.h"
/* ============================ [ MACROS    ] ====================================================== */
#define __TINY_OS__

#define OS_TICKS2MS(a) (a)

#define TASK_ID_TaskIdle                         0   /* priority = 0 */
#define TASK_ID_TaskShell                        1   /* priority = 1 */
#define TASK_ID_SchM_Startup                     2   /* priority = 7 */
#define TASK_ID_SchM_BswService                  3   /* priority = 8 */
#define TASK_ID_TaskCanIf                        4   /* priority = 9 */
#define TASK_NUM                                 5

#define EVENT_MASK_TaskShell_EventShellInput                0x00000001

#define RES_NUMBER 1

#define ALARM_ID_Alarm_BswService                 0
#define ALARM_NUM                                 1

#define ISR_NUM  0



/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
extern CONST(task_declare_t,AUTOMATIC)  TaskList[TASK_NUM];
extern CONST(alarm_declare_t,AUTOMATIC) AlarmList[ALARM_NUM];
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
extern TASK(TaskIdle);
extern TASK(TaskShell);
extern TASK(SchM_Startup);
extern TASK(SchM_BswService);
extern TASK(TaskCanIf);


extern ALARM(Alarm_BswService);


#endif /* OS_CFG_H */

