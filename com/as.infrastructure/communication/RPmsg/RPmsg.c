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
#include "RPmsg.h"
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
#define AS_LOG_RPMSG 0
/* ============================ [ TYPES     ] ====================================================== */
typedef struct
{
	const RPmsg_ConfigType* config;
	boolean online;
	boolean initialized;
}rpmsg_t;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
static rpmsg_t rpmsg =
{
	.initialized = FALSE
};
/* ============================ [ LOCALS    ] ====================================================== */
static Std_ReturnType sendMessage(const RPmsg_ChannelConfigType* chlConfig, uint32 dstEndpt, uint32 srcEndpt, void* data, uint16 len)
{
	Std_ReturnType ercd;
	VirtQ_IdxType idx;
	RPmsg_HandlerType* msg;
	uint16 length;
	const RPmsg_PortConfigType* portConfig = chlConfig->portConfig;
	ASLOG(RPMSG,"RPmsg send(dst=%Xh,src=%Xh,data=%Xh,len=%d)\n",dstEndpt,srcEndpt,(uint32)data,len);
	ercd = VirtQ_GetAvailiableBuffer(portConfig->txChl,&idx,(void**)&msg,&length);
	if(E_OK == ercd)
	{
		asAssert(len <= (length-(sizeof(*msg)-sizeof(msg->data))));
		/* Copy the payload and set message header: */
		memcpy(msg->data, data, len);
		msg->len = len;
		msg->dst = dstEndpt;
		msg->src = srcEndpt;
		msg->flags = 0;
		msg->reserved = 0;

		VirtQ_AddUsedBuffer(portConfig->txChl, idx, length);
		VirtQ_Kick(portConfig->txChl);
	}
	else
	{
		ASLOG(RPMSG,"transmit message failed as buffer not availiable.\n");
	}
	return ercd;
}
static void sendNamseServiceMessage(const RPmsg_ChannelConfigType* chlConfig, RPmsg_NameServiceFlagType flags)
{
	RPmsg_NamseServiceMessageType nsMsg;
	Std_ReturnType ercd;
	const RPmsg_PortConfigType* portConfig = chlConfig->portConfig;
	strncpy(nsMsg.name, chlConfig->name, RPMSG_NAME_SIZE);
	nsMsg.addr = portConfig->port;
	nsMsg.flags = flags;

	ASLOG(RPMSG,"RPmsg create <%s> on port=0x%X\n",chlConfig->name,portConfig->port);
	ercd = sendMessage(chlConfig,RPMSG_NAME_SERVICE_PORT, portConfig->port, &nsMsg, sizeof(nsMsg));
	asAssert(E_OK == ercd);
}

static void NameSerivice_Create(const RPmsg_ChannelConfigType* chlConfig)
{
	sendNamseServiceMessage(chlConfig, RPMSG_NS_CREATE);
}
/* ============================ [ FUNCTIONS ] ====================================================== */
void RPmsg_Init(const RPmsg_ConfigType* config)
{
	if(FALSE == rpmsg.initialized)
	{
		rpmsg.initialized = TRUE;
		rpmsg.online = FALSE;
		rpmsg.config = config;
	}
	else
	{
		asAssert(0);
	}
}
void RPmsg_RxNotification(RPmsg_PortType port)
{
	VirtQ_IdxType idx;
	uint16_t length;
	RPmsg_HandlerType* msg;
	Std_ReturnType ercd;
	RPmsg_ChannelType chl;
	const RPmsg_PortConfigType* portConfig;
	asAssert(rpmsg.initialized);
	asAssert(port < RPMSG_PORT_NUM);

	portConfig = &(rpmsg.config->portConfig[port]);

	ercd = VirtQ_GetAvailiableBuffer(portConfig->rxChl,&idx,(void**)&msg,&length);
	if(E_OK == ercd)
	{
		ASLOG(RPMSG,"RPmsg rx(dst=%Xh,src=%Xh,data=%Xh,len=%d/%d)\n",msg->dst,msg->src,(uint32)msg->data,msg->len,length);
		for(chl=0;chl<RPMSG_CHL_NUM;chl++)
		{
			if( (portConfig==rpmsg.config->chlConfig[chl].portConfig) &&
				(portConfig->port == msg->dst) &&
				(msg->src==rpmsg.config->chlConfig[chl].dst) )
			{
				break;
			}
		}

		if(chl<RPMSG_CHL_NUM)
		{
			rpmsg.config->chlConfig[chl].rxNotification(chl,msg->data,msg->len);
		}
		else
		{
			/* ignore invalid message */
			ASWARNING("RPMSG: invalid message, ignore it\n");
		}

		VirtQ_AddUsedBuffer(portConfig->rxChl, idx, length);
		VirtQ_Kick(portConfig->rxChl);
	}
	else
	{
		/* asAssert(0); */
		ASLOG(RPMSG,"invalid RPmsg_RxNotification\n");
	}
}

boolean RPmsg_IsOnline(void)
{
	return rpmsg.online;
}
void RPmsg_TxConfirmation(RPmsg_PortType port)
{
	int chl;
	const RPmsg_PortConfigType* portConfig;
	const RPmsg_ChannelConfigType* chlConfig;
	asAssert(rpmsg.initialized);
	asAssert(port < RPMSG_PORT_NUM);

	portConfig = &(rpmsg.config->portConfig[port]);
	if(rpmsg.online)
	{
		// TODO:
		ASLOG(RPMSG,"RPmsg_TxConfirmation(%d)\n",port);
	}
	else
	{
		ASLOG(RPMSG,"RPmsg_TxConfirmation(offline-->online)\n");
		VirtQ_InitVq(portConfig->rxChl);
		VirtQ_InitVq(portConfig->txChl);
		for(chl = 0; chl < RPMSG_CHL_NUM; chl ++)
		{
			chlConfig=&(rpmsg.config->chlConfig[chl]);
			if(chlConfig->portConfig == portConfig)
			{
				NameSerivice_Create(chlConfig);
			}
		}
		rpmsg.online = TRUE;
	}
}

Std_ReturnType RPmsg_Send(RPmsg_ChannelType chl, void* data, uint16 len)
{
	Std_ReturnType ercd;
	const RPmsg_ChannelConfigType* chlConfig;
	asAssert(rpmsg.initialized);
	asAssert(chl<RPMSG_CHL_NUM);
	chlConfig=&(rpmsg.config->chlConfig[chl]);
	ercd = sendMessage(chlConfig,chlConfig->dst,chlConfig->portConfig->port,data,len);
	return ercd;
}
