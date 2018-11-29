/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2017  AS <parai@foxmail.com>
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
#ifdef __WINDOWS__
#include <windows.h>
#include "Std_Types.h"
#include "lascanlib.h"
#ifdef SLIST_ENTRY
#undef SLIST_ENTRY
#endif
#include <sys/queue.h>
#include <pthread.h>
#include "ControlCAN.h"
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
#define Kbps *1000

#define AS_LOG_ZLG 1
/* ============================ [ TYPES     ] ====================================================== */
struct Can_ZLGHandle_s
{
	uint32_t busid;
	uint32_t port;
	uint32_t DeviceType;
	uint32_t CANInd;
	uint32_t baudrate;
	can_device_rx_notification_t rx_notification;
	STAILQ_ENTRY(Can_ZLGHandle_s) entry;
};
struct Can_ZLGHandleList_s
{
	pthread_t rx_thread;
	volatile boolean   terminated;
	STAILQ_HEAD(,Can_ZLGHandle_s) head;
};
/* ============================ [ DECLARES  ] ====================================================== */
static boolean zlg_probe(uint32_t busid,uint32_t port,uint32_t baudrate,can_device_rx_notification_t rx_notification);
static boolean zlg_write(uint32_t port,uint32_t canid,uint32_t dlc,uint8_t* data);
static void zlg_close(uint32_t port);
static void * rx_daemon(void *);
/* ============================ [ DATAS     ] ====================================================== */
const Can_DeviceOpsType can_zlg_ops =
{
	.name = "zlg",
	.probe = zlg_probe,
	.close = zlg_close,
	.write = zlg_write,
};
static struct Can_ZLGHandleList_s* zlgH = NULL;
static uint32_t zlg_bauds[][2] = {
	{1000 Kbps,0x0014	},
	{800  Kbps,0x0016	},
	{500  Kbps,0x001C	},
	{250  Kbps,0x011C	},
	{125  Kbps,0x031C	},
	{100  Kbps,0x041C	},
	{50   Kbps,0x091C	},
	{20   Kbps,0x181C	},
	{10   Kbps,0x311C	},
	{5    Kbps,0xBFFF	}
};
/* ============================ [ LOCALS    ] ====================================================== */
static struct Can_ZLGHandle_s* getHandle(uint32_t port)
{
	struct Can_ZLGHandle_s *handle,*h;
	handle = NULL;
	if(NULL != zlgH)
	{
		STAILQ_FOREACH(h,&zlgH->head,entry)
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

static boolean get_zlg_param(uint32_t port,uint32_t* DeviceType,uint32_t* CANInd,uint32_t* baudrate)
{
	uint32_t i;
	boolean rv = TRUE;

	char* pVCI_USBCAN = getenv("VCI_USBCAN");

	if(NULL != pVCI_USBCAN)
	{
		*DeviceType = strtoul(pVCI_USBCAN, NULL, 10);
		*CANInd  = port;
		ASLOG(ZLG, "open VCI_USBCAN %d port %d\n", *DeviceType, *CANInd);
	}
	else
	{
		ASWARNING("please set env VCI_USBCAN according to the device type value specified in ConttrolCAN.h!\n"
				"  set VCI_USBCAN=4 REM for VCI_USBCAN2\n"
				"  set VCI_USBCAN=21 REM for VCI_USBCAN_2E_U\n"
				);
		rv = FALSE;
	}

	for(i=0;i<SIZE_OF_ARRAY(zlg_bauds);i++)
	{
		if(*baudrate == zlg_bauds[i][0])
		{
			*baudrate = zlg_bauds[i][1];
			break;
		}
	}

	if(i >= SIZE_OF_ARRAY(zlg_bauds))
	{
		rv = FALSE;
	}

	return rv;
}

static boolean zlg_probe(uint32_t busid,uint32_t port,uint32_t baudrate,can_device_rx_notification_t rx_notification)
{
	boolean rv = TRUE;;
	struct Can_ZLGHandle_s* handle;
	if(NULL == zlgH)
	{
		zlgH = malloc(sizeof(struct Can_ZLGHandleList_s));
		asAssert(zlgH);
		STAILQ_INIT(&zlgH->head);

		zlgH->terminated = TRUE;
	}

	handle = getHandle(port);

	if(handle)
	{
		ASWARNING("CAN ZLG port=%d is already on-line, no need to probe it again!\n",port);
		rv = FALSE;
	}
	else
	{
		uint32_t DeviceType;
		uint32_t CANInd;
		uint32_t baud = baudrate;
		VCI_INIT_CONFIG init_config;
		uint32_t status;

		rv = get_zlg_param(port, &DeviceType, &CANInd,&baud);

		if(rv)
		{
			status = VCI_OpenDevice(DeviceType,0,0);

			if(STATUS_OK != status)
			{
				ASWARNING("CAN ZLG port=%d is not able to be opened,error=%X!\n",port,status);
				ASWARNING("maybe you forgot about the ControlCAN\\64\\kerneldlls to be copied to local directory!\n");
				rv = FALSE;
			}
		}

		if(rv)
		{
			init_config.AccCode=0x00000000;
			init_config.AccMask=0xFFFFFFFF;
			init_config.Filter=0;
			init_config.Mode=0;  /* normal mode */
			init_config.Timing0=(UCHAR)(baud>>8)&0xFF;
			init_config.Timing1=(UCHAR)baud&0xFF;

			status = VCI_InitCAN(DeviceType,0,CANInd,&init_config);
			if(STATUS_OK != status)
			{
				ASWARNING("CAN ZLG port=%d is not able to be initialized,error=%X!\n",port,status);
				rv = FALSE;
			}
		}

		if(rv)
		{
			status = VCI_StartCAN(DeviceType,0,CANInd);
			if(STATUS_OK != status)
			{
				ASWARNING("CAN ZLG port=%d is not able to be started,error=%X!\n",port,status);
				rv = FALSE;
			}
		}

		if( rv )
		{	/* open port OK */
			handle = malloc(sizeof(struct Can_ZLGHandle_s));
			asAssert(handle);
			handle->busid = busid;
			handle->port = port;
			handle->DeviceType = DeviceType;
			handle->CANInd = CANInd;
			handle->baudrate = baudrate;
			handle->rx_notification = rx_notification;
			STAILQ_INSERT_TAIL(&zlgH->head,handle,entry);
		}
		else
		{
			rv = FALSE;
		}
	}

	if( (TRUE == zlgH->terminated) &&
		(FALSE == STAILQ_EMPTY(&zlgH->head)) )
	{
		if( 0 == pthread_create(&(zlgH->rx_thread),NULL,rx_daemon,NULL))
		{
			zlgH->terminated = FALSE;
		}
		else
		{
			asAssert(0);
		}
	}

	return rv;
}
static boolean zlg_write(uint32_t port,uint32_t canid,uint32_t dlc,uint8_t* data)
{
	boolean rv = TRUE;
	uint32_t status;
	struct Can_ZLGHandle_s* handle = getHandle(port);
	if(handle != NULL)
	{
		VCI_CAN_OBJ msg;
		msg.ID = canid&0x7FFFFFFFUL;
		msg.DataLen = dlc;
		if(canid & 0x8000000UL)
		{
			msg.ExternFlag = 1;
		}
		else
		{
			msg.ExternFlag = 0;
		}
		msg.RemoteFlag = 0;

		memcpy(msg.Data,data,dlc);

		status = VCI_Transmit(handle->DeviceType,0,handle->CANInd,&msg,1);
		if( STATUS_OK == status)
		{
			/* send OK */
		}
		else
		{
			rv = FALSE;
			ASWARNING("CAN ZLG port=%d send message failed: error = %X!\n",port,status);
		}
	}
	else
	{
		rv = FALSE;
		ASWARNING("CAN ZLG port=%d is not on-line, not able to send message!\n",port);
	}

	return rv;
}
static void zlg_close(uint32_t port)
{
	struct Can_ZLGHandle_s* handle = getHandle(port);
	if(NULL != handle)
	{
		STAILQ_REMOVE(&zlgH->head,handle,Can_ZLGHandle_s,entry);

		if(TRUE == STAILQ_EMPTY(&zlgH->head))
		{
			VCI_CloseDevice(handle->DeviceType, 0);
			zlgH->terminated = TRUE;
		}
		free(handle);
	}
}

static void rx_notifiy(struct Can_ZLGHandle_s* handle)
{
	VCI_CAN_OBJ msg;
	uint32 dwRel;
	uint32_t status;

	dwRel = VCI_GetReceiveNum(handle->DeviceType,0,handle->CANInd);

	if(dwRel > 0)
	{
		status = VCI_Receive(handle->DeviceType,0,handle->CANInd,&msg,1,0);

		if(STATUS_OK == status)
		{
			handle->rx_notification(handle->busid,msg.ID,msg.DataLen,msg.Data);
		}
		else
		{
			ASWARNING("CAN ZLG port=%d read message failed: error = %X!\n",handle->port,status);
		}
	}

}
static void * rx_daemon(void * param)
{
	(void)param;
	struct Can_ZLGHandle_s* handle;
	while(FALSE == zlgH->terminated)
	{
		STAILQ_FOREACH(handle,&zlgH->head,entry)
		{
			rx_notifiy(handle);
		}
	}

	return NULL;
}

/* ============================ [ FUNCTIONS ] ====================================================== */
#endif /* __WINDOWS__ */

