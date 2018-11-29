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
#ifdef __WINDOWS__
/* ============================ [ INCLUDES  ] ====================================================== */
#include <windows.h>
#include "vxlapi.h"
#ifdef SLIST_ENTRY
#undef SLIST_ENTRY
#endif
#include "Std_Types.h"
#include "lascanlib.h"
#include <sys/queue.h>
#include <pthread.h>
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
struct Can_VxlHandle_s
{
	XLportHandle xlHandle;
	XLaccess     xlAccess;
	XLdriverConfig  xlDrvConfig;
	uint32_t busid;
	uint32_t port;
	uint32_t baudrate;
	can_device_rx_notification_t rx_notification;
	STAILQ_ENTRY(Can_VxlHandle_s) entry;
};
struct Can_VxlHandleList_s
{
	pthread_t rx_thread;
	volatile boolean   terminated;
	STAILQ_HEAD(,Can_VxlHandle_s) head;
};
/* ============================ [ DECLARES  ] ====================================================== */
#ifndef MINGW_HAS_SECURE_API
extern char* strncpy_s(char* __to, size_t dsize, const char* __from, size_t doSz);
#endif
static boolean vxl_probe(uint32_t busid,uint32_t port,uint32_t baudrate,can_device_rx_notification_t rx_notification);
static boolean vxl_write(uint32_t port,uint32_t canid,uint32_t dlc,uint8_t* data);
static void vxl_close(uint32_t port);
static void * rx_daemon(void *);
/* ============================ [ DATAS     ] ====================================================== */
const Can_DeviceOpsType can_vxl_ops =
{
	.name = "vxl",
	.probe = vxl_probe,
	.close = vxl_close,
	.write = vxl_write,
};
static struct Can_VxlHandleList_s* vxlH = NULL;
/* ============================ [ LOCALS    ] ====================================================== */
static struct Can_VxlHandle_s* getHandle(uint32_t port)
{
	struct Can_VxlHandle_s *handle,*h;
	handle = NULL;
	if(NULL != vxlH)
	{
		STAILQ_FOREACH(h,&vxlH->head,entry)
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

static void vxlPrintConfig(XLdriverConfig *xlDrvConfig)
{

	unsigned int i;
	char         str[100];

	printf("----------------------------------------------------------\n");
	printf("- %02d channels       Hardware Configuration               -\n", xlDrvConfig->channelCount);
	printf("----------------------------------------------------------\n");

	for (i=0; i < xlDrvConfig->channelCount; i++)
	{

		printf("- Ch:%02d, CM:0x%03I64x,",
				xlDrvConfig->channel[i].channelIndex, xlDrvConfig->channel[i].channelMask);

		strncpy_s(str, 100, xlDrvConfig->channel[i].name, 23);
		printf(" %23s,", str);

		memset(str, 0, sizeof(str));

		if (xlDrvConfig->channel[i].transceiverType != XL_TRANSCEIVER_TYPE_NONE)
		{
			strncpy_s( str, 100, xlDrvConfig->channel[i].transceiverName, 13);
			printf("%13s -\n", str);
		}
		else
		{
			printf("    no Cab!   -\n");
		}
	}

	printf("----------------------------------------------------------\n\n");

}

static boolean open_vxl(struct Can_VxlHandle_s *handle)
{
	char userName[32];
	XLstatus status;
	XLaccess accessMask;

	status = xlGetDriverConfig(&handle->xlDrvConfig);

	if(XL_SUCCESS == status)
	{
		vxlPrintConfig(&handle->xlDrvConfig);
	}
	else
	{
		ASWARNING("CAN VXL get driver config error<%d>: %s\n",status, xlGetErrorString(status));
		return FALSE;
	}

	sprintf(userName,"port%d",(int)handle->port);
	accessMask = 1<<handle->port;
	handle->xlAccess = accessMask;
	status= xlOpenPort(&handle->xlHandle,userName,accessMask,&handle->xlAccess,512,XL_INTERFACE_VERSION,XL_BUS_TYPE_CAN);
	if(XL_SUCCESS != status)
	{
		ASWARNING("CAN VXL open port error<%d>: %s\n",status, xlGetErrorString(status));
		return FALSE;
	}

	status = xlCanSetChannelBitrate(handle->xlHandle,handle->xlAccess,handle->baudrate);
	if(XL_SUCCESS != status)
	{
		ASWARNING("CAN VXL open error<%d>: %s\n",status, xlGetErrorString(status));
		return FALSE;
	}


	status = xlActivateChannel(handle->xlHandle,handle->xlAccess,XL_BUS_TYPE_CAN,XL_ACTIVATE_RESET_CLOCK);
	if(XL_SUCCESS != status)
	{
		ASWARNING("CAN VXL open error<%d>: %s\n",status, xlGetErrorString(status));
		return FALSE;
	}

	return TRUE;
}
static boolean vxl_probe(uint32_t busid,uint32_t port,uint32_t baudrate,can_device_rx_notification_t rx_notification)
{
	boolean rv = TRUE;;
	struct Can_VxlHandle_s* handle;
	if(NULL == vxlH)
	{
		XLstatus status = xlOpenDriver();

		if(XL_SUCCESS != status)
		{
			ASWARNING("CAN VXL open error<%d>: %s\n",status, xlGetErrorString(status));
			return FALSE;
		}

		vxlH = malloc(sizeof(struct Can_VxlHandleList_s));
		asAssert(vxlH);
		STAILQ_INIT(&vxlH->head);

		vxlH->terminated = TRUE;
	}

	handle = getHandle(port);

	if(handle)
	{
		ASWARNING("CAN VXL port=%d is already on-line, no need to probe it again!\n",port);
		rv = FALSE;
	}
	else
	{
		handle = malloc(sizeof(struct Can_VxlHandle_s));
		asAssert(handle);
		handle->busid = busid;
		handle->port = port;
		handle->baudrate = baudrate;
		handle->rx_notification = rx_notification;
		if( open_vxl(handle) )
		{	/* open port OK */

			STAILQ_INSERT_TAIL(&vxlH->head,handle,entry);
		}
		else
		{
			free(handle);
			ASWARNING("CAN VXL port=%d is is not able to be opened!\n",port);
			rv = FALSE;
		}
	}

	if( (TRUE == vxlH->terminated) &&
		(FALSE == STAILQ_EMPTY(&vxlH->head)) )
	{
		if( 0 == pthread_create(&(vxlH->rx_thread),NULL,rx_daemon,NULL))
		{
			vxlH->terminated = FALSE;
		}
		else
		{
			asAssert(0);
		}
	}

	return rv;
}
static boolean vxl_write(uint32_t port,uint32_t canid,uint32_t dlc,uint8_t* data)
{
	boolean rv = TRUE;
	struct Can_VxlHandle_s* handle = getHandle(port);
	if(handle != NULL)
	{
		XLstatus status;
		XLevent Event;
		unsigned int EventCount = 1;
		Event.tag=XL_TRANSMIT_MSG;
		Event.tagData.msg.id=canid;
		Event.tagData.msg.flags=0;
		memcpy(Event.tagData.msg.data,data,dlc);
		Event.tagData.msg.dlc=dlc;
		status = xlCanTransmit(handle->xlHandle,handle->xlAccess, &EventCount, &Event);
		if(XL_SUCCESS != status)
		{
			rv = FALSE;
			ASWARNING("CAN VXL port=%d send message failed: %s!\n",port,xlGetErrorString(status));
		}
	}
	else
	{
		rv = FALSE;
		ASWARNING("CAN Vxl port=%d is not on-line, not able to send message!\n",port);
	}

	return rv;
}
static void vxl_close(uint32_t port)
{
	struct Can_VxlHandle_s* handle = getHandle(port);
	if(NULL != handle)
	{
		STAILQ_REMOVE(&vxlH->head,handle,Can_VxlHandle_s,entry);

		free(handle);

		if(TRUE == STAILQ_EMPTY(&vxlH->head))
		{
			vxlH->terminated = TRUE;
		}
	}
}

static void rx_notifiy(struct Can_VxlHandle_s* handle)
{
	char* string;
	XLstatus status;
	unsigned int EventCount = 1;
	uint32_t i;
	XLevent Event;
	uint32_t port,time,canid,dlc,tid,u32V;
	uint8_t data[8];
	char sdata[32];
	status = xlReceive(handle->xlHandle,&EventCount,&Event);
	if(XL_ERR_QUEUE_IS_EMPTY == status)
	{
		return;
	}

	if(XL_SUCCESS != status)
	{
		ASWARNING("CAN VXL port=%d receive message failed: %s!\n",handle->port,xlGetErrorString(status));
		return;
	}
	string = xlGetEventString(&Event);
	if(NULL != strstr(string,"ERROR_FRAME"))
	{
		ASWARNING("%s!\n",string);
	}
	/* RX_MSG c=0, t=222, id=0510 l=8, 0000000000000000 tid=00 */
	else if(NULL != strstr(string,"RX_MSG"))
	{
		sscanf(string,"RX_MSG c=%d, t=%d, id=%X l=%d, %s tid=%d",&port,&time,&canid,&dlc,sdata,&tid);
		asAssert((dlc*2)<=strlen(sdata));
		for(i=0;i<dlc;i++)
		{
			sscanf(&sdata[2*i],"%2x",&u32V);
			data[i] = (uint8_t)u32V;
		}
		handle->rx_notification(handle->busid,canid,dlc,data);
	}
	else
	{
		ASWARNING("CAN VXL port=%d receive unknown message: '%s'!\n",handle->port,string);
	}
}
static void * rx_daemon(void * param)
{
	(void)param;
	struct Can_VxlHandle_s* handle;

	while(FALSE == vxlH->terminated)
	{
		STAILQ_FOREACH(handle,&vxlH->head,entry)
		{
			rx_notifiy(handle);
		}
	}

	xlCloseDriver();
	return NULL;
}

/* ============================ [ FUNCTIONS ] ====================================================== */
#endif /* __WINDOWS__ */

