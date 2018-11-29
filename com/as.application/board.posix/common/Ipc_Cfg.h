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
#ifndef COM_AS_APPLICATION_BOARD_POSIX_COMMON_IPC_CFG_H_
#define COM_AS_APPLICATION_BOARD_POSIX_COMMON_IPC_CFG_H_
/* ============================ [ INCLUDES  ] ====================================================== */

/* ============================ [ MACROS    ] ====================================================== */
#define IPC_CHL_0     ((Ipc_ChannelType)0)
#define IPC_CHL_NUM   ((Ipc_ChannelType)1)

#define IPC_FIFO_SIZE 1024

#define IPC_MAP_PA_TO_VA(addr) as_phys_to_virt(addr)
/* ============================ [ TYPES     ] ====================================================== */
typedef void (*Ipc_RxNotificationType)(VirtQ_ChannerlType chl);
typedef void (*Ipc_TxConfirmationType)(VirtQ_ChannerlType chl);
typedef struct
{
	VirtQ_IdxSizeType count;
	VirtQ_IdxType     idx[IPC_FIFO_SIZE];
}Ipc_FifoType;
typedef struct
{
	Rproc_ReseouceVdevVringType* vring;
	VirtQ_ChannerlType 	chl;
}Ipc_Idx2VirtQChannleMappingType;
typedef struct
{
	void* r_lock;
	void* r_event;
	void* w_lock;
	void* w_event;

	Ipc_FifoType* r_fifo;
	Ipc_FifoType* w_fifo;

	const Ipc_Idx2VirtQChannleMappingType* mapping;
	uint32 map_size;

	Ipc_RxNotificationType rxNotification;
	Ipc_TxConfirmationType txConfirmation;

}Ipc_ChannelConfigType;

typedef struct
{
	Ipc_ChannelConfigType* channelConfig;
}Ipc_ConfigType;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
extern const Ipc_ConfigType Ipc_Config;
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
unsigned long as_phys_to_virt(unsigned long addr);
#endif /* COM_AS_APPLICATION_BOARD_POSIX_COMMON_IPC_CFG_H_ */
