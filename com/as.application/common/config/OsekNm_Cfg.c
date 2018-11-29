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
#ifdef USE_OSEKNM
/* ============================ [ INCLUDES  ] ====================================================== */
#include "OsekNm.h"
#include "Can.h"
#include "CanIf.h"
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
// NM Main Task Tick = 10 ms
#define tTyp 10
#define tMax 26
#define tError 100
#define tWBS   500
#define tTx    2

#define EventNmNormal   EVENT_MASK_TaskNmInd_EventNmNormal
#define EventNmLimphome EVENT_MASK_TaskNmInd_EventNmLimphome
#define EventNmStatus   EVENT_MASK_TaskNmInd_EventNmStatus
#define EventRingData   EVENT_MASK_TaskNmInd_EventRingData

#if defined(__LINUX__) || defined(__WINDOWS__)
#define ASENV_OSEKNM_NODE_ID()  atoi(ASENV(1))
#else
#define ASENV_OSEKNM_NODE_ID()  1
#endif
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
#if defined(__WINDOWS__) || defined(__LINUX__)
extern CanIf_TxPduConfigType CanIfTxPduConfigData[];
#endif
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void D_Init(NetIdType NetId,RoutineRefType InitRoutine)
{

}
void D_Offline(NetIdType NetId)
{

}
void D_Online(NetIdType NetId)
{

}
StatusType D_WindowDataReq(NetIdType NetId,NMPduType* NMPDU,uint8 DataLengthTx)
{
	PduInfoType pdu;
	uint8 data[8];
	pdu.SduLength = DataLengthTx;
	pdu.SduDataPtr = data;
	asAssert(DataLengthTx > 2);
	data[0] = NMPDU->Destination;
	data[1] = NMPDU->OpCode.b;
	memcpy(&data[2],NMPDU->RingData,DataLengthTx-2);
	return CanIf_Transmit(CANIF_ID_OSEK_NM_TX,&pdu);
}


/* Function needed by DLL */
void BusInit(NetIdType NetId)
{

}
void BusSleep(NetIdType NetId)
{

}
void BusAwake(NetIdType NetId)
{

}
void BusRestart(NetIdType NetId)
{

}

TASK(TaskNmInd)
{
	StatusType ercd;
	EventMaskType mask;
	OS_TASK_BEGIN();
	ercd = WaitEvent(EventNmNormal|EventNmLimphome|EventNmStatus|EventRingData);
	if(E_OK == ercd)
	{
		GetEvent(TASK_ID_TaskNmInd,&mask);
		if((mask&EventNmNormal) != 0)
		{
			printf("In NM normal state,config changed.\n");
		}
		if((mask&EventNmLimphome) != 0)
		{
			printf("In NM limphome state,config changed.\n");
		}
		if((mask&EventNmStatus) != 0)
		{
			printf("NM network status changed.\n");
		}
		if((mask&EventRingData) != 0)
		{
			printf("NM Ring Data ind.\n");
		}
		ClearEvent(EventNmNormal|EventNmLimphome|EventNmStatus|EventRingData);
	}
	OsTerminateTask(TaskNmInd);
	OS_TASK_END();
}

/* This is an example of how to write NMInit() */
void NMInit(NetIdType NetId)
{
	uint8 config[32];
	NetworkStatusType status;
	(void)memset(config,0x01,32); /*care node :0,8,16,24,32,... */
	#if defined(__LINUX__) || defined(__WINDOWS__)
	CanIfTxPduConfigData[CANIF_ID_OSEK_NM_TX].CanIfCanTxPduIdCanId = 0x400+ASENV_OSEKNM_NODE_ID();
	#endif
	if(NetId == 0)
	{
		InitNMType(NetId,NM_DIRECT);
		InitNMScaling(NetId,0xFF); /* TODO: not used */
		InitCMaskTable(NetId,NM_ckNormal,config);
		InitCMaskTable(NetId,NM_ckLimphome,config);
		InitIndDeltaConfig(NetId,NM_ckNormal,SignalActivation,TASK_ID_TaskNmInd,EventNmNormal);
		InitIndDeltaConfig(NetId,NM_ckLimphome,SignalActivation,TASK_ID_TaskNmInd,EventNmLimphome);
		memset(&status,0,sizeof(NetworkStatusType));
		status.W.NMactive = 1;
		InitSMaskTable(NetId,&status); /* TODO : not implemented for indication */
		InitTargetStatusTable(NetId,&status);
		InitIndDeltaStatus(NetId,SignalActivation,TASK_ID_TaskNmInd,EventNmStatus);
		InitDirectNMParams(NetId,ASENV_OSEKNM_NODE_ID(),tTyp,tMax,tError,tWBS,tTx);
		InitIndRingData(NetId,SignalActivation,TASK_ID_TaskNmInd,EventRingData);
	}
}


void CanIf_OsekNmUserTxConfirmation(PduIdType pduId)
{
	NM_TxConformation((NetIdType)pduId);
}

void CanIf_OsekNmUserRxIndication(uint8 channel, PduIdType pduId, const uint8 *sduPtr, uint8 dlc, Can_IdType canId)
{
	NMPduType pdu;
	pdu.Source = canId&0xFF;

	asAssert(dlc >= 2);
	pdu.Destination = sduPtr[0];
	pdu.OpCode.b=sduPtr[1];

	memset(pdu.RingData,0,6);
	memcpy(pdu.RingData,&sduPtr[2],dlc-2);

	NM_RxIndication(channel,&pdu);

}
#else
#include "Os.h"
TASK(TaskNmInd)
{
	OsTerminateTask(TaskNmInd);
}
#endif /* USE_OSEKNM */
