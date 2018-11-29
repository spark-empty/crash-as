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
/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* for simple test purpose, echo the message back */
void __weak Can_RPmsg_RxNotitication(RPmsg_ChannelType chl,void* data, uint16 len){
	/* RPmsg_Send(chl,data,len); */
	(void)chl;
	(void)data;
	(void)len;
}
void __weak Can_RPmsg_TxConfirmation(RPmsg_ChannelType chl) {(void)chl;}
void __weak RPmsg_Client_RxNotitication(RPmsg_ChannelType chl,void* data, uint16 len)
{
	/* RPmsg_Send(chl,data,len); */
	(void)chl;
	(void)data;
	(void)len;
}
void __weak RPmsg_Client_TxConfirmation(RPmsg_ChannelType chl){(void)chl;};
/* ============================ [ DATAS     ] ====================================================== */

static const RPmsg_PortConfigType portConfig[RPMSG_PORT_NUM] =
{
	{
		.port = 0x257,
		.rxChl = VIRTQ_CHL_RPMSG_RX,
		.txChl = VIRTQ_CHL_RPMSG_TX,
	}
};
static const RPmsg_ChannelConfigType chlConfig[RPMSG_CHL_NUM] =
{
	{
		.name = "rpmsg-can-sample",
		.dst = 0x400,
		.rxNotification = Can_RPmsg_RxNotitication,
		.txConfirmation = Can_RPmsg_TxConfirmation,
		.portConfig = &portConfig[RPMSG_PORT_DEFAULT]
	},
	{
		.name = "rpmsg-client-sample",
		.dst = 0x401,
		.rxNotification = RPmsg_Client_RxNotitication,
		.txConfirmation = RPmsg_Client_TxConfirmation,
		.portConfig = &portConfig[RPMSG_PORT_DEFAULT]
	}
};
const RPmsg_ConfigType RPmsg_Config =
{
	.portConfig = portConfig,
	.chlConfig = chlConfig
};
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
