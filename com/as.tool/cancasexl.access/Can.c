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
#include "Can.h"
#include <windows.h>
#include "vxlapi.h"
/* ============================ [ MACROS    ] ====================================================== */
#define CAN_REPORT_ERROR_AND_EXIT(error)													\
	do	{																					\
		if(XL_SUCCESS != error)																\
		{																					\
			printf("CAN ERROR In %s line %d: %s\n",__FUNCTION__,__LINE__,					\
							xlGetErrorString(error));										\
			return E_NOT_OK;																\
		}																					\
	}while(0)
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
static boolean 		IsXLReady = FALSE;
static XLportHandle xlPortHandle[32];
static XLaccess     xlAccess[32];
static uint64       xlPortInUseMask=0;
/* ============================ [ FUNCTIONS ] ====================================================== */
Std_ReturnType Can_Init(uint32 port,uint32 baudrate)
{
	char userName[32];
	XLstatus status;
	XLaccess accessMask;
	if(FALSE == IsXLReady)
	{
		status = xlOpenDriver();

		CAN_REPORT_ERROR_AND_EXIT(status);

		IsXLReady = TRUE;
	}


	sprintf(userName,"port%d",(int)port);
	accessMask = 1<<port;
	status= xlOpenPort(&xlPortHandle[port],userName,accessMask,&xlAccess[port],512,XL_INTERFACE_VERSION,XL_BUS_TYPE_CAN);
	CAN_REPORT_ERROR_AND_EXIT(status);

	xlPortInUseMask |= accessMask;

	status = xlCanSetChannelBitrate(xlPortHandle[port],xlAccess[port],baudrate);
	CAN_REPORT_ERROR_AND_EXIT(status);


	status = xlActivateChannel(xlPortHandle[port],xlAccess[port],XL_BUS_TYPE_CAN,XL_ACTIVATE_RESET_CLOCK);
	CAN_REPORT_ERROR_AND_EXIT(status);

	return E_OK;
}

Std_ReturnType Can_Receive(uint32 port,char** message)
{
	XLstatus status;
	XLaccess accessMask;
	accessMask = 1<<port;

	if(xlPortInUseMask&accessMask)
	{
		unsigned int EventCount = 1;
		XLevent Event;
		status = xlReceive(xlPortHandle[port],&EventCount,&Event);
		CAN_REPORT_ERROR_AND_EXIT(status);
		*message = xlGetEventString(&Event);
		CAN_REPORT_ERROR_AND_EXIT(status);
	}
	else
	{
		*message = "CAN ERROR: this port is not in active status\n";
		return E_NOT_OK;
	}

	return E_OK;
}

Std_ReturnType Can_Write(uint32  port, Can_PduType *pduInfo )
{
	XLstatus status;
	XLaccess accessMask;
	accessMask = 1<<port;

	if(xlPortInUseMask&accessMask)
	{
		XLevent Event;
		unsigned int EventCount = 1;
		Event.tag=XL_TRANSMIT_MSG;
		Event.tagData.msg.id=pduInfo->id;
		Event.tagData.msg.flags=0;
		assert(pduInfo->length<=8);
		memcpy(Event.tagData.msg.data,pduInfo->sdu,pduInfo->length);
		Event.tagData.msg.dlc=pduInfo->length;
		status = xlCanTransmit(xlPortHandle[port],xlAccess[port], &EventCount, &Event);
		CAN_REPORT_ERROR_AND_EXIT(status);
	}
	else
	{
		return E_NOT_OK;
	}

	return E_OK;
}

Std_ReturnType Can_DeInit(uint32 port)
{
	XLstatus status;
	XLaccess accessMask;
	accessMask = 1<<port;

	if(xlPortInUseMask&accessMask)
	{
		status = xlClosePort(xlPortHandle[port]);
		CAN_REPORT_ERROR_AND_EXIT(status);
		xlPortInUseMask &= ~accessMask;
	}

	if(0==xlPortInUseMask)
	{
		status = xlCloseDriver();
		CAN_REPORT_ERROR_AND_EXIT(status);
	}

	return E_OK;
}
