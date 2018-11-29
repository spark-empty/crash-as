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
#ifdef __WINDOWS__
#include <windows.h>
#include "Std_Types.h"
#include "lascanlib.h"
#ifdef SLIST_ENTRY
#undef SLIST_ENTRY
#endif
#include <sys/queue.h>
#include <pthread.h>
#include "PCANBasic.h"
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
#define Kbps *1000
/* ============================ [ TYPES     ] ====================================================== */
struct Can_PeakHandle_s
{
	uint32_t busid;
	uint32_t port;
	uint32_t channel;
	uint32_t baudrate;
	can_device_rx_notification_t rx_notification;
	STAILQ_ENTRY(Can_PeakHandle_s) entry;
};
struct Can_PeakHandleList_s
{
	pthread_t rx_thread;
	volatile boolean   terminated;
	STAILQ_HEAD(,Can_PeakHandle_s) head;
};
/* ============================ [ DECLARES  ] ====================================================== */
static boolean peak_probe(uint32_t busid,uint32_t port,uint32_t baudrate,can_device_rx_notification_t rx_notification);
static boolean peak_write(uint32_t port,uint32_t canid,uint32_t dlc,uint8_t* data);
static void peak_close(uint32_t port);
static void * rx_daemon(void *);
/* ============================ [ DATAS     ] ====================================================== */
const Can_DeviceOpsType can_peak_ops =
{
	.name = "peak",
	.probe = peak_probe,
	.close = peak_close,
	.write = peak_write,
};
static struct Can_PeakHandleList_s* peakH = NULL;
static uint32_t peak_ports[] = {
	PCAN_USBBUS1,PCAN_USBBUS2,PCAN_USBBUS3,PCAN_USBBUS4,
	PCAN_USBBUS5,PCAN_USBBUS6,PCAN_USBBUS7,PCAN_USBBUS8,
};
static uint32_t peak_bauds[][2] = {
	{1000 Kbps,PCAN_BAUD_1M		},
	{800  Kbps,PCAN_BAUD_800K	},
	{500  Kbps,PCAN_BAUD_500K	},
	{250  Kbps,PCAN_BAUD_250K	},
	{100  Kbps,PCAN_BAUD_100K	},
	{95   Kbps,PCAN_BAUD_95K	},
	{83   Kbps,PCAN_BAUD_83K	},
	{50   Kbps,PCAN_BAUD_50K	},
	{47   Kbps,PCAN_BAUD_47K	},
	{33   Kbps,PCAN_BAUD_33K	},
	{20   Kbps,PCAN_BAUD_20K	},
	{10   Kbps,PCAN_BAUD_10K	},
	{5    Kbps,PCAN_BAUD_5K		}
};
/* ============================ [ LOCALS    ] ====================================================== */
static struct Can_PeakHandle_s* getHandle(uint32_t port)
{
	struct Can_PeakHandle_s *handle,*h;
	handle = NULL;
	if(NULL != peakH)
	{
		STAILQ_FOREACH(h,&peakH->head,entry)
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
/*
 * InOut: port, baudrate
 */
static boolean get_peak_param(uint32_t *port,uint32_t* baudrate)
{
	uint32_t i;
	boolean rv = TRUE;

	if(*port < SIZE_OF_ARRAY(peak_ports))
	{
		*port = peak_ports[*port];
	}
	else
	{
		rv = FALSE;
	}

	for(i=0;i<SIZE_OF_ARRAY(peak_bauds);i++)
	{
		if(*baudrate == peak_bauds[i][0])
		{
			*baudrate = peak_bauds[i][1];
			break;
		}
	}

	if(i >= SIZE_OF_ARRAY(peak_bauds))
	{
		rv = FALSE;
	}

	return rv;
}

static boolean peak_probe(uint32_t busid,uint32_t port,uint32_t baudrate,can_device_rx_notification_t rx_notification)
{
	boolean rv = TRUE;;
	struct Can_PeakHandle_s* handle;
	if(NULL == peakH)
	{
		peakH = malloc(sizeof(struct Can_PeakHandleList_s));
		asAssert(peakH);
		STAILQ_INIT(&peakH->head);

		peakH->terminated = TRUE;
	}

	handle = getHandle(port);

	if(handle)
	{
		ASWARNING("CAN PEAK port=%d is already on-line, no need to probe it again!\n",port);
		rv = FALSE;
	}
	else
	{
		uint32_t peak_baud = baudrate;
		uint32_t peak_port = port;
		boolean rv = get_peak_param(&peak_port,&peak_baud);
		if( rv )
		{
			TPCANStatus status = CAN_Initialize(peak_port,peak_baud,0,0,0);

			if(PCAN_ERROR_OK == status)
			{
				rv = TRUE;
			}
			else
			{
				ASWARNING("CAN PEAK port=%d is not able to be opened,error=%X!\n",port,status);
				rv = FALSE;
			}
		}
		if( rv )
		{	/* open port OK */
			handle = malloc(sizeof(struct Can_PeakHandle_s));
			asAssert(handle);
			handle->busid = busid;
			handle->port = port;
			handle->channel = peak_port;
			handle->baudrate = baudrate;
			handle->rx_notification = rx_notification;
			STAILQ_INSERT_TAIL(&peakH->head,handle,entry);
		}
		else
		{
			rv = FALSE;
		}
	}

	if( (TRUE == peakH->terminated) &&
		(FALSE == STAILQ_EMPTY(&peakH->head)) )
	{
		if( 0 == pthread_create(&(peakH->rx_thread),NULL,rx_daemon,NULL))
		{
			peakH->terminated = FALSE;
		}
		else
		{
			asAssert(0);
		}
	}

	return rv;
}
static boolean peak_write(uint32_t port,uint32_t canid,uint32_t dlc,uint8_t* data)
{
	boolean rv = TRUE;
	struct Can_PeakHandle_s* handle = getHandle(port);
	if(handle != NULL)
	{
		TPCANMsg msg;
		msg.ID = canid;
		msg.LEN = dlc;
		if(0 != (canid&0x80000000))
		{
			msg.MSGTYPE = PCAN_MESSAGE_STANDARD;
		}
		else
		{
			msg.MSGTYPE = PCAN_MESSAGE_EXTENDED;
		}

		memcpy(msg.DATA,data,dlc);

		TPCANStatus status = CAN_Write(handle->channel,&msg);
		if( PCAN_ERROR_OK == status)
		{
			/* send OK */
		}
		else
		{
			rv = FALSE;
			ASWARNING("CAN PEAK port=%d send message failed: error = %X!\n",port,status);
		}
	}
	else
	{
		rv = FALSE;
		ASWARNING("CAN Peak port=%d is not on-line, not able to send message!\n",port);
	}

	return rv;
}
static void peak_close(uint32_t port)
{
	struct Can_PeakHandle_s* handle = getHandle(port);
	if(NULL != handle)
	{
		STAILQ_REMOVE(&peakH->head,handle,Can_PeakHandle_s,entry);

		free(handle);

		if(TRUE == STAILQ_EMPTY(&peakH->head))
		{
			peakH->terminated = TRUE;
		}
	}
}

static void rx_notifiy(struct Can_PeakHandle_s* handle)
{
	TPCANMsg msg;
	TPCANStatus status = CAN_Read(handle->channel,&msg,NULL);

	if(PCAN_ERROR_OK == status)
	{
		handle->rx_notification(handle->busid,msg.ID,msg.LEN,msg.DATA);
	}
	else if (PCAN_ERROR_QRCVEMPTY == status)
	{

	}
	else
	{
		ASWARNING("CAN PEAK port=%d read message failed: error = %X!\n",handle->port,status);
	}

}
static void * rx_daemon(void * param)
{
	(void)param;
	struct Can_PeakHandle_s* handle;
	while(FALSE == peakH->terminated)
	{
		STAILQ_FOREACH(handle,&peakH->head,entry)
		{
			rx_notifiy(handle);
		}
	}

	return NULL;
}

/* ============================ [ FUNCTIONS ] ====================================================== */
#endif /* __WINDOWS__ */

