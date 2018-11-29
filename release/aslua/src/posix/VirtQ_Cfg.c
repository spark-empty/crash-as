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
#include "VirtQ.h"
#include "Rproc.h"
#include "Ipc.h"
#include "RPmsg.h"
/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */

/* ============================ [ DATAS     ] ====================================================== */
static const VirtQ_QueueConfigType queueConfig[VIRTQ_CHL_NUM] =
{
	{
		.chl = IPC_CHL_0,
		.handler = RPMSG_PORT_DEFAULT,
		.rxNotification = RPmsg_RxNotification ,
		.vring = &(Rproc_ResourceTable.rpmsg_vdev.vring[1])
	},
	{
		.chl = IPC_CHL_0,
		.handler = RPMSG_PORT_DEFAULT,
		.rxNotification = RPmsg_TxConfirmation ,
		.vring = &(Rproc_ResourceTable.rpmsg_vdev.vring[0])
	}
};

const VirtQ_ConfigType VirtQ_Config =
{
	.queueConfig = queueConfig
};
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
