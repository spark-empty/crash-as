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
#ifndef COM_AS_INFRASTRUCTURE_INCLUDE_OSEKNM_H_
#define COM_AS_INFRASTRUCTURE_INCLUDE_OSEKNM_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Os.h"
#include "ComStack_Types.h"
/* ============================ [ MACROS    ] ====================================================== */
/* Mask bit for ScalingParamType */
/* If 1 the function is supported, 0 not */
#define NM_BusSleepSupport             0x01
#define NM_StatusDeltaSupport          0x02
#define NM_NormalConfigDeltaSupport    0x04
#define NM_LimphomeConfigDeltaSupport  0x08
#define NM_RingdataSupport             0x10

// Macros for OpCode
#define NM_MaskAlive   	 0x01
#define NM_MaskRing   	 0x02
#define NM_MaskLimphome  0x04
#define NM_MaskSI        0x10   /* sleep ind */
#define NM_MaskSA        0x20   /* sleep ack */
/* ============================ [ TYPES     ] ====================================================== */
/* @ nm253.pdf 4.3 P89 */
typedef uint8 NodeIdType;
typedef uint8 NetIdType;
typedef void (*RoutineRefType)(NetIdType NetId);
/* import EventMaskType from OS */
typedef enum{
	SignalInvalid = 0,
	SignalActivation,
	SignalEvent
}SignallingMode;
/* import StatusType / TaskRefType / TickType from OS */
/* -- Private Types */
typedef enum
{
	NM_DIRECT = 0,
	NM_INDIRECT
}NMType;

typedef uint8 ScalingParamType; /* 8 bit is enough TODO: not used */

/* @ nm253.pdf 4.4.2 P92 */
typedef uint8* ConfigRefType;
typedef enum
{
	NM_ckNormal = 1,              /* supported by direct and indirect NM */
	NM_ckNormalExtended,          /* only supported by indirect NM */
	NM_ckLimphome                 /* only supported by direct NM */
}ConfigKindName;
typedef ConfigRefType ConfigHandleType;
typedef union
{
	uint32 w;
	struct{
		unsigned NMactive:1;
		unsigned bussleep:1;
		unsigned configurationstable:1;
	}W;
}NetworkStatusType;

typedef NetworkStatusType* StatusRefType;
/* @ nm253.pdf 4.4.3.1 P98 */
typedef enum
{
	NM_BusSleep = 1,
	NM_Awake
}NMModeName;
typedef enum
{
	NM_stOff = 0,
	NM_stInit,
	NM_stInitReset,
	NM_stNormal,
	NM_stNormalPrepSleep,
	NM_stTwbsNormal,
	NM_stBusSleep,
	NM_stLimphome,
	NM_stLimphomePrepSleep,
	NM_stTwbsLimphome,
	NM_stOn /* in fact if not Off then ON. */
	// ...  and so on
}NMStateType;
typedef StatusRefType StatusHandleType;

/* @ nm253.pdf 4.4.5.3.1 P103 */
typedef uint8 RingDataType[6];
typedef RingDataType* RingDataRefType;

typedef struct
{
	uint8 Source;
	uint8 Destination;
	union
	{
		uint8 b;
		struct {
			uint8 Alive     :1;
			uint8 Ring      :1;
			uint8 Limphome  :1;
			uint8 reserved1 :1;
			uint8 SleepInd  :1;
			uint8 SleepAck  :1;
			uint8 reserved2 :2;
		}B;
	}OpCode;
	RingDataType RingData ;
}NMPduType;

#include "OsekNm_Cfg.h"
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
/* @ nm253.pdf 4.4.1.1 P89 System Generation Support */
void InitNMType(NetIdType NetId,NMType nmType);
void InitNMScaling(NetIdType NetId,ScalingParamType ScalingParams);
void SelectHWRoutines(NetIdType NetId,RoutineRefType BusInit,RoutineRefType BusAwake,	\
				RoutineRefType BusSleep,RoutineRefType BusRestart,RoutineRefType BusShutdown);
void InitCMaskTable(NetIdType NetId,ConfigKindName ConfigKind,ConfigRefType CMask);
void InitTargetConfigTable(NetIdType NetId,ConfigKindName ConfigKind,ConfigRefType TargetConfig);
void InitIndDeltaConfig(NetIdType NetId,ConfigKindName ConfigKind,SignallingMode SMode,	\
				TaskType TaskId,EventMaskType EMask);
void InitSMaskTable(NetIdType NetId,StatusRefType SMask);
void InitTargetStatusTable(NetIdType NetId,StatusRefType TargetStatus);
void InitIndDeltaStatus(NetIdType NetId,SignallingMode SMode,TaskType TaskId,EventMaskType EMask);
/* @ nm253.pdf 4.4.2.3 P95 Services */
StatusType InitConfig(NetIdType NetId);
StatusType GetConfig(NetIdType NetId,ConfigRefType Config,ConfigKindName ConfigKind);
StatusType CmpConfig(NetIdType NetId,ConfigRefType TestConfig,ConfigRefType RefConfig,ConfigRefType CMask);
StatusType SelectDeltaConfig(NetIdType NetId,ConfigKindName ConfigKind,ConfigHandleType ConfigHandle,ConfigHandleType CMaskHandle);

StatusType StartNM(NetIdType NetId);
StatusType StopNM(NetIdType NetId);
StatusType GotoMode(NetIdType NetId,NMModeName NewMode);
StatusType GetStatus(NetIdType NetId,StatusRefType NetworkStatus);
StatusType CmpStatus(NetIdType NetId,StatusRefType TestStatus,StatusRefType RefStatus,StatusRefType SMask);
StatusType SelectDeltaStatus(NetIdType NetId,StatusHandleType StatusHandle,StatusHandleType SMaskHandle);

/* FOR DIRECT NM */
void InitDirectNMParams(NetIdType NetId,NodeIdType NodeId,TickType TimerTyp,TickType TimerMax, 	\
								TickType TimerError,TickType TimerWaitBusSleep,TickType TimerTx);
StatusType SilentNM(NetIdType);
StatusType TalkNM(NetIdType);
void InitIndRingData(NetIdType NetId,SignallingMode SMode,TaskType TaskId,EventMaskType EMask);
void ReadRingData(NetIdType NetId,RingDataRefType RingData);
void TransmitRingData(NetIdType NetId,RingDataRefType RingData);

/* FOR INDIRECT NM */
void InitIndirectNMParams(NetIdType NetId,NodeIdType NodeId,TickType TOB,TickType TimerError,TickType TimerWaitBusSleep);
void InitExtNodeMonitiring(NetIdType NetId,NodeIdType NodeId,uint8 DeltaInc,uint8 DeltaDec);


void NM_TxConformation(NetIdType NetId);
void NM_RxIndication(NetIdType NetId,NMPduType* NMPDU);
void NM_WakeupIndication(NetIdType NetId);
void NM_BusErrorIndication(NetIdType NetId);

void NM_MainFuntion(void);

void D_Init(NetIdType NetId,RoutineRefType InitRoutine);
void D_Offline(NetIdType NetId);
void D_Online(NetIdType NetId);
StatusType D_WindowDataReq(NetIdType NetId,NMPduType* NMPDU,uint8 DataLengthTx);


/* Function needed by DLL */
void BusInit(NetIdType NetId);
void BusSleep(NetIdType NetId);
void BusAwake(NetIdType NetId);
void BusRestart(NetIdType NetId);

#endif /* COM_AS_INFRASTRUCTURE_INCLUDE_OSEKNM_H_ */
