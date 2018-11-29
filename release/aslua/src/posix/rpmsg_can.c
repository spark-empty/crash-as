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
#ifdef USE_RPMSG
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
#include "RPmsg.h"
#include "lascanlib.h"
#include <sys/queue.h>
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
#define AS_LOG_LUA 0
/* ============================ [ TYPES     ] ====================================================== */
struct Can_RPmsgHandle_s
{
	uint32_t busid;
	uint32_t port;
	uint32_t baudrate;
	can_device_rx_notification_t rx_notification;
	STAILQ_ENTRY(Can_RPmsgHandle_s) entry;
};
struct Can_RPmsgHandleList_s
{
	STAILQ_HEAD(,Can_RPmsgHandle_s) head;
};
/* ============================ [ DECLARES  ] ====================================================== */
static boolean rpmsg_probe(uint32_t busid,uint32_t port,uint32_t baudrate,can_device_rx_notification_t rx_notification);
static boolean rpmsg_write(uint32_t port,uint32_t canid,uint32_t dlc,uint8_t* data);
static void rpmsg_close(uint32_t port);
/* ============================ [ DATAS     ] ====================================================== */
const Can_DeviceOpsType can_rpmsg_ops =
{
	.name = "rpmsg",
	.probe = rpmsg_probe,
	.close = rpmsg_close,
	.write = rpmsg_write,
};
static struct Can_RPmsgHandleList_s* rpmsgH = NULL;
/* ============================ [ LOCALS    ] ====================================================== */
static struct Can_RPmsgHandle_s* getHandle(uint32_t port)
{
	struct Can_RPmsgHandle_s *handle,*h;
	handle = NULL;
	if(NULL != rpmsgH)
	{
		STAILQ_FOREACH(h,&rpmsgH->head,entry)
		{
			if(h->port == port)
			{
				handle = h;
				break;
			}
		}
	}
	return handle;
}
static boolean rpmsg_probe(uint32_t busid,uint32_t port,uint32_t baudrate,can_device_rx_notification_t rx_notification)
{
	boolean rv;
	struct Can_RPmsgHandle_s* handle;
	if(NULL == rpmsgH)
	{
		rpmsgH = malloc(sizeof(struct Can_RPmsgHandleList_s));
		asAssert(rpmsgH);
		STAILQ_INIT(&rpmsgH->head);
	}
	handle = getHandle(port);

	if(handle)
	{
		ASWARNING("CAN RPMSG port=%d is already on-line, no need to probe it again!\n",port);
		rv = FALSE;
	}
	else
	{
		handle = malloc(sizeof(struct Can_RPmsgHandle_s));
		STAILQ_INSERT_TAIL(&rpmsgH->head,handle,entry);
		handle->busid = busid;
		handle->port = port;
		handle->baudrate = baudrate;
		handle->rx_notification = rx_notification;
		rv = TRUE;
	}

	return rv;
}
static boolean rpmsg_write(uint32_t port,uint32_t canid,uint32_t dlc,uint8_t* data)
{
	boolean rv = TRUE;

	if(RPmsg_IsOnline())
	{
		Can_RPmsgPduType pduInfo;
		Std_ReturnType ercd;
		pduInfo.bus = port;
		pduInfo.id = canid;
		pduInfo.length = dlc;
		memcpy(pduInfo.sdu,data,dlc);
		ASLOG(LUA,"LUA TX CAN ID=0x%08X LEN=%d DATA=[%02X %02X %02X %02X %02X %02X %02X %02X]\n",
			  pduInfo.id,pduInfo.length,pduInfo.sdu[0],pduInfo.sdu[1],pduInfo.sdu[2],pduInfo.sdu[3],
			  pduInfo.sdu[4],pduInfo.sdu[5],pduInfo.sdu[6],pduInfo.sdu[7]);

		do {
			ercd = RPmsg_Send(RPMSG_CHL_CAN,&pduInfo,sizeof(pduInfo));
		} while(ercd != E_OK);
	}
	else
	{
		rv = FALSE;
		ASWARNING("CAN RPMSG port=%d is not on-line, not able to send message!\n",port);
	}

	return rv;
}
static void rpmsg_close(uint32_t port)
{
	struct Can_RPmsgHandle_s* handle = getHandle(port);
	if(NULL != handle)
	{
		STAILQ_REMOVE(&rpmsgH->head,handle,Can_RPmsgHandle_s,entry);
		free(handle);
	}
}
/* ============================ [ FUNCTIONS ] ====================================================== */
void Can_RPmsg_RxNotitication(RPmsg_ChannelType chl,void* data, uint16 len)
{
	Can_RPmsgPduType* pduInfo = (Can_RPmsgPduType*)data;
	asAssert(len==sizeof(Can_RPmsgPduType));
	asAssert(chl == RPMSG_CHL_CAN);
	struct Can_RPmsgHandle_s* handle = getHandle(pduInfo->bus);

	if(NULL != handle)
	{
		if(NULL != handle->rx_notification)
		{
			handle->rx_notification(handle->busid,pduInfo->id,pduInfo->length,pduInfo->sdu);
		}
		else
		{
			ASWARNING("RPMSG CAN RX notification of bus <%d> is NULL\n",pduInfo->bus);
		}
	}
	else
	{
		ASWARNING("RPMSG CAN RX bus <%d> out of range\n",pduInfo->bus);
	}

    ASLOG(LUA,"RPMAG RX CAN ID=0x%08X LEN=%d DATA=[%02X %02X %02X %02X %02X %02X %02X %02X]\n",
		  pduInfo->id,pduInfo->length,pduInfo->sdu[0],pduInfo->sdu[1],pduInfo->sdu[2],pduInfo->sdu[3],
		  pduInfo->sdu[4],pduInfo->sdu[5],pduInfo->sdu[6],pduInfo->sdu[7]);
}
void Can_RPmsg_TxConfirmation(RPmsg_ChannelType chl)
{
	asAssert(chl == RPMSG_CHL_CAN);
}
#endif /* USE_RPMSG */
