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
 *
 * Refereed to Linux virtio and SYSBIOS-RPMSG source code
 * http://git.omapzoom.org/?p=repo/sysbios-rpmsg.git;a=summary
 */
#ifndef COM_AS_INFRASTRUCTURE_COMMUNICATION_RPMSG_VIRTQ_H_
#define COM_AS_INFRASTRUCTURE_COMMUNICATION_RPMSG_VIRTQ_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "virtio_ring.h"
#include "Rproc.h"
/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
typedef uint8 Ipc_ChannelType;
typedef uint8 VirtQ_ChannerlType;
typedef void (*VirtQ_NotificationType)(VirtQ_ChannerlType channel);
typedef uint32 VirtQ_IdxType;
typedef uint32 VirtQ_IdxSizeType;
typedef struct virtqueue
{
    /* Shared state */
    Vring_Type            		vring;

    /* Last available index */
    VirtQ_IdxType           last_avail_idx;

}VirtQ_QueueType;

typedef struct
{
	Ipc_ChannelType             chl;
	uint8                       handler;	/* upper layer handler */

    /* The function to call when buffers are consumed (can be NULL) */
	VirtQ_NotificationType      rxNotification;

	Rproc_ReseouceVdevVringType* vring;

}VirtQ_QueueConfigType;

typedef struct
{
	const VirtQ_QueueConfigType* queueConfig;
}VirtQ_ConfigType;

#include "VirtQ_Cfg.h"
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void VirtQ_Init(const VirtQ_ConfigType *config);
void VirtQ_RxNotificatin(VirtQ_ChannerlType chl);
void VirtQ_TxConfirmation(VirtQ_ChannerlType chl);
void VirtQ_InitVq(VirtQ_ChannerlType chl);
Std_ReturnType VirtQ_GetAvailiableBuffer(VirtQ_ChannerlType chl,VirtQ_IdxType* idx,void** buf,uint16* len);
void VirtQ_AddUsedBuffer(VirtQ_ChannerlType chl,VirtQ_IdxType idx,uint16 len);
void VirtQ_Kick(VirtQ_ChannerlType chl);
#endif /* COM_AS_INFRASTRUCTURE_COMMUNICATION_RPMSG_VIRTQ_H_ */
