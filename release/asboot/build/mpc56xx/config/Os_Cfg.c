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
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
CONST(task_declare_t,AUTOMATIC)  TaskList[TASK_NUM] = 
{
	DeclareTask(TaskIdle                        , FALSE, OSDEFAULTAPPMODE    ),
	DeclareTask(TaskShell                       , TRUE , OSDEFAULTAPPMODE    ),
	DeclareTask(SchM_Startup                    , TRUE , OSDEFAULTAPPMODE    ),
	DeclareTask(SchM_BswService                 , FALSE, OSDEFAULTAPPMODE    ),
	DeclareTask(TaskCanIf                       , TRUE , OSDEFAULTAPPMODE    ),
};

CONST(alarm_declare_t,AUTOMATIC) AlarmList[ALARM_NUM] = 
{
	DeclareAlarm(Alarm_BswService),
};



