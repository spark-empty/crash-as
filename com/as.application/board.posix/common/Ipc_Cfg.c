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
#include "Ipc.h"
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
#define AS_LOG_IPC 0
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */

/* ============================ [ DATAS     ] ====================================================== */
static Ipc_FifoType r_fifo;
static Ipc_FifoType w_fifo;
static const Ipc_Idx2VirtQChannleMappingType mapping[2] =
{
	{ .vring = &(Rproc_ResourceTable.rpmsg_vdev.vring[1]), .chl= VIRTQ_CHL_RPMSG_RX },
	{ .vring = &(Rproc_ResourceTable.rpmsg_vdev.vring[0]), .chl= VIRTQ_CHL_RPMSG_TX },
};
static Ipc_ChannelConfigType Ipc_ChlConfig[IPC_CHL_NUM] =
{
	{
		.r_fifo = &r_fifo,
		.w_fifo = &w_fifo,

		.mapping = mapping,
		.map_size = sizeof(mapping)/sizeof(Ipc_Idx2VirtQChannleMappingType),

		.rxNotification = VirtQ_RxNotificatin,
		.txConfirmation = VirtQ_TxConfirmation,

		.r_lock = NULL

	}
};
const Ipc_ConfigType Ipc_Config =
{
	.channelConfig = Ipc_ChlConfig
};
unsigned long Ipc_BaseAddress = 0;
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void Qt_SetIpcParam(/*Ipc_ChannelType*/int chl, void* r_lock, void* r_event, void* w_lock, void* w_event)
{
	asAssert(chl < IPC_CHL_NUM);
	Ipc_ChlConfig[chl].r_lock = w_lock;
	Ipc_ChlConfig[chl].w_lock = r_lock;
	Ipc_ChlConfig[chl].r_event = w_event;
	Ipc_ChlConfig[chl].w_event = r_event;
}
void Qt_GetIpcFifo(/*Ipc_ChannelType*/int chl, Ipc_FifoType** r_fifo, Ipc_FifoType** w_fifo)
{
	asAssert(chl < IPC_CHL_NUM);
	*r_fifo = Ipc_ChlConfig[chl].w_fifo;
	*w_fifo = Ipc_ChlConfig[chl].r_fifo;
}

void Qt_SetIpcBaseAddress(unsigned long base)
{
	if(0==Ipc_BaseAddress)
	{
		Ipc_BaseAddress = base;
		ASLOG(IPC,"Virtual Address Base = %X00000000h\n",(uint32_t)(base>>32));
	}
	else
	{
		asAssert(Ipc_BaseAddress == base);
	}
}
#ifndef CONFIG_ARCH_VEXPRESS
unsigned long as_phys_to_virt(unsigned long addr)
{
	return (Ipc_BaseAddress+addr);
}
#endif
