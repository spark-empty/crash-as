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
#ifndef COM_AS_INFRASTRUCTURE_COMMUNICATION_RPMSG_RPMSG_H_
#define COM_AS_INFRASTRUCTURE_COMMUNICATION_RPMSG_RPMSG_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "VirtQ.h"
/* ============================ [ MACROS    ] ====================================================== */
#define RPMSG_ADDR_ANY		0xFFFFFFFF

/* The feature bitmap for virtio rpmsg */
#define VIRTIO_RPMSG_F_NS	0 /* RP supports name service notifications */

#define RPMSG_NAME_SERVICE_PORT 53

#define RPMSG_NAME_SIZE			32
#define RPMSG_DATA_SIZE         512	/* FIXME: can be changed to an other proper value  */
/* ============================ [ TYPES     ] ====================================================== */

/**
 * struct rpmsg_hdr - common header for all rpmsg messages
 * @src: source address
 * @dst: destination address
 * @reserved: reserved for future use
 * @len: length of payload (in bytes)
 * @flags: message flags
 * @data: @len bytes of message payload data
 *
 * Every message sent(/received) on the rpmsg bus begins with this header.
 */
typedef struct {
	uint32_t src;
	uint32_t dst;
	uint32_t reserved;
	uint16_t len;
	uint16_t flags;
	uint8_t data[RPMSG_DATA_SIZE];
} RPmsg_HandlerType;

/**
 * struct rpmsg_ns_msg - dynamic name service announcement message
 * @name: name of remote service that is published
 * @addr: address of remote service that is published
 * @flags: indicates whether service is created or destroyed
 *
 * This message is sent across to publish a new service, or announce
 * about its removal. When we receive these messages, an appropriate
 * rpmsg channel (i.e device) is created/destroyed. In turn, the ->probe()
 * or ->remove() handler of the appropriate rpmsg driver will be invoked
 * (if/as-soon-as one is registered).
 */
typedef struct {
	char name[RPMSG_NAME_SIZE];
	uint32_t addr;
	uint32_t flags;
} RPmsg_NamseServiceMessageType;

/**
 * enum rpmsg_ns_flags - dynamic name service announcement flags
 *
 * @RPMSG_NS_CREATE: a new remote service was just created
 * @RPMSG_NS_DESTROY: a known remote service was just destroyed
 */
typedef enum{
	RPMSG_NS_CREATE		= 0,
	RPMSG_NS_DESTROY	= 1,
} RPmsg_NameServiceFlagType;

typedef uint8 RPmsg_PortType;
typedef uint8 RPmsg_ChannelType;
typedef void (*RPmsg_RxNotiticationType)(RPmsg_ChannelType chl,void* data, uint16 len);
typedef void (*RPmsg_TxConfirmationType)(RPmsg_ChannelType chl);

typedef struct
{
	uint32 port;	/* src for each dst end point */
	VirtQ_ChannerlType rxChl;
	VirtQ_ChannerlType txChl;
}RPmsg_PortConfigType;

typedef struct
{
	char*  name;
	uint32_t dst;
	uint16_t flags;
	RPmsg_RxNotiticationType rxNotification;
	RPmsg_TxConfirmationType txConfirmation;
	const RPmsg_PortConfigType* portConfig;
}RPmsg_ChannelConfigType;


typedef struct
{
	const RPmsg_PortConfigType* portConfig;
	const RPmsg_ChannelConfigType* chlConfig;
}RPmsg_ConfigType;

#include "RPmsg_Cfg.h"
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void RPmsg_Init(const RPmsg_ConfigType* config);
void RPmsg_RxNotification(RPmsg_ChannelType channel);
void RPmsg_TxConfirmation(RPmsg_ChannelType channel);
boolean RPmsg_IsOnline(void);
Std_ReturnType RPmsg_Send(RPmsg_ChannelType chl, void* data, uint16 len);
#endif /* COM_AS_INFRASTRUCTURE_COMMUNICATION_RPMSG_RPMSG_H_ */
