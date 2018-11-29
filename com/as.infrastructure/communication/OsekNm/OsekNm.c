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
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
#define rx_limit 4
#define tx_limit 8

/* Alarm Management */
#define nmSetAlarm(Timer)				\
do										\
{										\
	NM_ControlBlock[NetId].Alarm._##Timer = 1+NM_ControlBlock[NetId].nmDirectNMParams._##Timer;	\
}while(0)

/* signal the alarm to process one step/tick forward */
#define nmSingalAlarm(Timer)								\
do															\
{															\
	 if(NM_ControlBlock[NetId].Alarm._##Timer > 1)			\
	 {														\
		(NM_ControlBlock[NetId].Alarm._##Timer)--;			\
	 }														\
}while(0)

#define nmIsAlarmTimeout(Timer)  (1 == NM_ControlBlock[NetId].Alarm._##Timer)

#define nmIsAlarmStarted(Timer)	 (0 != NM_ControlBlock[NetId].Alarm._##Timer)

#define nmCancelAlarm(Timer)					\
do												\
{												\
	NM_ControlBlock[NetId].Alarm._##Timer = 0;	\
}while(0)

#define nmSendMessage()					\
do{										\
	StatusType ercd;					\
	ercd = D_WindowDataReq(NetId,&(NM_ControlBlock[NetId].nmTxPdu),8);		\
	if(ercd != E_OK)					\
	{									\
		nmSetAlarm(TTx); /* re-Transmit after TTx */						\
	}									\
}while(0)

#define AS_LOG_OSEK_NM 1
#define nmDebug(str) ASLOG(OSEK_NM,str)
/* ============================ [ TYPES     ] ====================================================== */
/* OK we could see terrible thing here, too big the struct is. */
typedef struct
{
	NMType nmType;
	ScalingParamType nmScalingParams; /* not used */
	struct
	{
		uint8 normal[32];
		uint8 normalExtended[32];
		uint8 limphome[32];
	}nmConfig;
	struct
	{
		uint8 normal[32];
		uint8 normalExtended[32];
		uint8 limphome[32];
	}nmCMask;
	struct
	{
		struct{
			SignallingMode SMode;
			TaskType TaskId;
			EventMaskType EMask;
		}normal;
		struct{
			SignallingMode SMode;
			TaskType TaskId;
			EventMaskType EMask;
		}normalExtended;
		struct{
			SignallingMode SMode;
			TaskType TaskId;
			EventMaskType EMask;
		}limphome;
	}nmIndDeltaConfig;
	struct{
		NetworkStatusType SMask;
		NetworkStatusType NetworkStatus;
		SignallingMode SMode;
		TaskType TaskId;
		EventMaskType EMask;
	}nmStatus;
	struct{
		SignallingMode SMode;
		TaskType TaskId;
		EventMaskType EMask;
	}nmRingDataInd;
	union
	{
		uint32 w;
		struct
		{
			unsigned stable : 1;
			unsigned limphome : 1;
		}W;
	}nmMerker; /* TODO: what's the meaning? */
	NMStateType nmState;
	struct
	{
		NodeIdType NodeId;
		TickType _TTx;
		TickType _TTyp;
		TickType _TMax;
		TickType _TError;
		TickType _TWbs;
	}nmDirectNMParams;
	uint8 nmRxCount;
	uint8 nmTxCount;
	struct{
		TickType _TTx;
		TickType _TTyp;
		TickType _TMax;
		TickType _TError;
		TickType _TWbs;
	}Alarm;
	NMPduType nmTxPdu;
}NM_ControlBlockType;
/* ============================ [ DECLARES  ] ====================================================== */
void NMInit(NetIdType NetId);
static void nmInit3(NetIdType NetId);
static void nmAddtoPresent(NetIdType NetId,NodeIdType NodeId);
static void nmAddtoLimphome(NetIdType NetId,NodeIdType NodeId);
static void nmInitReset5(NetIdType NetId);
static void nmInitReset6(NetIdType NetId);
static void nmAddToConfig(NetIdType NetId,ConfigKindName ConfigKind,NodeIdType NodeId);
static void nmRemoveFromConfig(NetIdType NetId,ConfigKindName ConfigKind,NodeIdType NodeId);
static void nmNormalStandard(NetIdType NetId,NMPduType* NMPDU);
static NodeIdType nmDetermineLS(NodeIdType S,NodeIdType R,NodeIdType L);
static boolean nmIsMeSkipped(NodeIdType S,NodeIdType R,NodeIdType D);
static void nmBusSleep(NetIdType NetId);
static void nmNormalTwbsMain(NetIdType NetId);
static void nmNormalPrepSleepMain(NetIdType NetId);
static void nmLimphomeMain(NetIdType NetId);
static void nmLimphomePrepSleepMain(NetIdType NetId);
static void nmNormalMain(NetIdType NetId);
static void nmTwbsLimphomeMain(NetIdType NetId);
/* ============================ [ DATAS     ] ====================================================== */
NM_ControlBlockType NM_ControlBlock[OSEKNM_NET_NUM];
/* ============================ [ LOCALS    ] ====================================================== */
/* nmInit3 is special doesn't mean all the operation of "Leave NMBusSleep" */
static void nmInit3(NetIdType NetId)
{
	/* step 3: config.limphome  := 0 */
	memset(NM_ControlBlock[NetId].nmConfig.limphome,0,32);
	/* step 4: */
	NM_ControlBlock[NetId].nmRxCount = 0;
	NM_ControlBlock[NetId].nmTxCount = 0;
	D_Online(NetId);
	nmInitReset6(NetId);
}
static void nmAddtoPresent(NetIdType NetId,NodeIdType NodeId)
{
	uint8 RefConfig[32]; /* old config */
	if(NM_ControlBlock[NetId].nmIndDeltaConfig.normal.SMode != SignalInvalid)
	{
		/* memcpy(RefConfig,NM_ControlBlock[NetId].nmConfig.normal,32);
		 * arm-none-eabi-gcc seems has a bug here for API call memcpy, in fact the asm code is
		 * not a memcpy call, seems to be a code opmization with builtin memcpy but which has issues */
		for(int i=0; i< 32; i++)
		{
			RefConfig[i] =NM_ControlBlock[NetId].nmConfig.normal[1];
		}
	}
	nmAddToConfig(NetId,NM_ckNormal,NodeId);
	nmRemoveFromConfig(NetId,NM_ckLimphome,NodeId);
	/* If enable do Indication */
	if(NM_ControlBlock[NetId].nmIndDeltaConfig.normal.SMode != SignalInvalid)
	{
		StatusType ercd;
		ercd = CmpConfig(NetId,NM_ControlBlock[NetId].nmConfig.normal,RefConfig,NM_ControlBlock[NetId].nmCMask.normal);
		if(ercd != E_OK)
		{ /* do ind */
			if(NM_ControlBlock[NetId].nmIndDeltaConfig.normal.SMode == SignalActivation)
			{
				#ifdef __TINY_OS__
				#ifdef __WINDOWS__
				(void)SetEvent2(NM_ControlBlock[NetId].nmIndDeltaConfig.normal.TaskId,NM_ControlBlock[NetId].nmIndDeltaConfig.normal.EMask);
				#else
				(void)SetEvent(NM_ControlBlock[NetId].nmIndDeltaConfig.normal.TaskId,NM_ControlBlock[NetId].nmIndDeltaConfig.normal.EMask);
				#endif
				#endif
				(void)ActivateTask(NM_ControlBlock[NetId].nmIndDeltaConfig.normal.TaskId);
			}
			else
			{
#ifdef __WINDOWS__
				(void)SetEvent2(NM_ControlBlock[NetId].nmIndDeltaConfig.normal.TaskId,NM_ControlBlock[NetId].nmIndDeltaConfig.normal.EMask);
#else
				(void)SetEvent(NM_ControlBlock[NetId].nmIndDeltaConfig.normal.TaskId,NM_ControlBlock[NetId].nmIndDeltaConfig.normal.EMask);
#endif
			}
		}
	}
}
static void nmAddtoLimphome(NetIdType NetId,NodeIdType NodeId)
{
	uint8 RefConfig[32]; /* old config */
	if(NM_ControlBlock[NetId].nmIndDeltaConfig.limphome.SMode != SignalInvalid)
	{
		memcpy(RefConfig,NM_ControlBlock[NetId].nmConfig.limphome,32);
	}
	nmAddToConfig(NetId,NM_ckLimphome,NodeId);
	/* If enable do Indication */
	if(NM_ControlBlock[NetId].nmIndDeltaConfig.limphome.SMode != SignalInvalid)
	{
		StatusType ercd;
		ercd = CmpConfig(NetId,NM_ControlBlock[NetId].nmConfig.limphome,RefConfig,NM_ControlBlock[NetId].nmCMask.limphome);
		if(ercd != E_OK)
		{ /* do ind */
			if(NM_ControlBlock[NetId].nmIndDeltaConfig.limphome.SMode == SignalActivation)
			{
				#ifdef __TINY_OS__
				#ifdef __WINDOWS__
				(void)SetEvent2(NM_ControlBlock[NetId].nmIndDeltaConfig.limphome.TaskId,NM_ControlBlock[NetId].nmIndDeltaConfig.limphome.EMask);
				#else
				(void)SetEvent(NM_ControlBlock[NetId].nmIndDeltaConfig.limphome.TaskId,NM_ControlBlock[NetId].nmIndDeltaConfig.limphome.EMask);
				#endif
				#endif
				(void)ActivateTask(NM_ControlBlock[NetId].nmIndDeltaConfig.limphome.TaskId);
			}
			else
			{
#ifdef __WINDOWS__
				(void)SetEvent2(NM_ControlBlock[NetId].nmIndDeltaConfig.limphome.TaskId,NM_ControlBlock[NetId].nmIndDeltaConfig.limphome.EMask);
#else
				(void)SetEvent(NM_ControlBlock[NetId].nmIndDeltaConfig.limphome.TaskId,NM_ControlBlock[NetId].nmIndDeltaConfig.limphome.EMask);
#endif
			}
		}
	}
}
static void nmInitReset5(NetIdType NetId)
{
	nmCancelAlarm(TError);
	NM_ControlBlock[NetId].nmMerker.W.limphome = 0;

	NM_ControlBlock[NetId].nmRxCount = 0;
	NM_ControlBlock[NetId].nmTxCount = 0;
	D_Online(NetId);
	nmInitReset6(NetId);
}
static void nmInitReset6(NetIdType NetId)
{
	NM_ControlBlock[NetId].nmState= NM_stInitReset;
	/* config.present = own station */
	memset(NM_ControlBlock[NetId].nmConfig.normal,0,32);
	nmAddtoPresent(NetId,NM_ControlBlock[NetId].nmDirectNMParams.NodeId);
	/* logical successor := own station */
	NM_ControlBlock[NetId].nmTxPdu.Destination = NM_ControlBlock[NetId].nmDirectNMParams.NodeId;
	NM_ControlBlock[NetId].nmRxCount += 1;
	/* Initialise the NMPDU(Data,OpCode) */
	NM_ControlBlock[NetId].nmTxPdu.OpCode.b = 0;
	memset(NM_ControlBlock[NetId].nmTxPdu.RingData,0,sizeof(RingDataType));
	/* Cancel all Alarm */
	nmCancelAlarm(TTx);
	nmCancelAlarm(TTyp);
	nmCancelAlarm(TMax);
	nmCancelAlarm(TWbs);
	nmCancelAlarm(TError);
	if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.NMactive)
	{
		NM_ControlBlock[NetId].nmTxCount += 1;
		/* Send A alive message */
		NM_ControlBlock[NetId].nmTxPdu.OpCode.b = NM_MaskAlive;
		nmSendMessage();
		nmDebug("nmInitReset6:Send Alive,");
	}
	if((NM_ControlBlock[NetId].nmTxCount <= tx_limit)	&&
		(NM_ControlBlock[NetId].nmRxCount <= rx_limit))
	{
		nmSetAlarm(TTyp);
		NM_ControlBlock[NetId].nmState = NM_stNormal;
		nmDebug("Set TTyp, enter Normal state.\n");
	}
	else
	{
		nmSetAlarm(TError);
		NM_ControlBlock[NetId].nmState = NM_stLimphome;
		nmDebug("Set TError, Enter Limphome state.\n");
	}
}
static void nmNormalStandard(NetIdType NetId,NMPduType* NMPDU)
{
	NM_ControlBlock[NetId].nmRxCount = 0;
	if(NMPDU->OpCode.B.Limphome)
	{
		/* add sender to config.limphome */
		nmAddtoLimphome(NetId,NMPDU->Source);
	}
	else
	{
		/* add sender to config.present */
		nmAddtoPresent(NetId,NMPDU->Source);
		/* determine logical successor */
		NM_ControlBlock[NetId].nmTxPdu.Destination = nmDetermineLS(NMPDU->Source,	\
									NM_ControlBlock[NetId].nmDirectNMParams.NodeId,	\
										NM_ControlBlock[NetId].nmTxPdu.Destination);
		if(NMPDU->OpCode.B.Ring)
		{
			nmCancelAlarm(TTyp);
			nmCancelAlarm(TMax);
			/* see nm253 Figure 4 Mechanism to transfer application data via the logical ring */
			memcpy(NM_ControlBlock[NetId].nmTxPdu.RingData,NMPDU->RingData,sizeof(RingDataType));
			if((NMPDU->Destination == NM_ControlBlock[NetId].nmDirectNMParams.NodeId) /* to me */
				|| (NMPDU->Destination == NMPDU->Source)) /* or D = S */
			{
				nmSetAlarm(TTyp);
				/* Do Ring Data indication */
				if(NM_ControlBlock[NetId].nmRingDataInd.SMode == SignalEvent)
				{
#ifdef __WINDOWS__
					(void)SetEvent2(NM_ControlBlock[NetId].nmRingDataInd.TaskId,NM_ControlBlock[NetId].nmRingDataInd.EMask);
#else
					(void)SetEvent(NM_ControlBlock[NetId].nmRingDataInd.TaskId,NM_ControlBlock[NetId].nmRingDataInd.EMask);
#endif
				}
				else if(NM_ControlBlock[NetId].nmRingDataInd.SMode == SignalActivation)
				{
					#ifdef __TINY_OS__
					#ifdef __WINDOWS__
					(void)SetEvent2(NM_ControlBlock[NetId].nmRingDataInd.TaskId,NM_ControlBlock[NetId].nmRingDataInd.EMask);
					#else
					(void)SetEvent(NM_ControlBlock[NetId].nmRingDataInd.TaskId,NM_ControlBlock[NetId].nmRingDataInd.EMask);
					#endif
					#endif
					(void)ActivateTask(NM_ControlBlock[NetId].nmRingDataInd.TaskId);
				}
				else
				{
					/* invalid as InitIndRingData hasn't been called before. */
				}

			}
			else
			{
				nmSetAlarm(TMax);
				if(nmIsMeSkipped(NMPDU->Source,NM_ControlBlock[NetId].nmDirectNMParams.NodeId,NMPDU->Destination))
				{
					if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.NMactive)
					{
						NM_ControlBlock[NetId].nmTxPdu.OpCode.b= NM_MaskAlive;
						NM_ControlBlock[NetId].nmTxPdu.Destination= NM_ControlBlock[NetId].nmDirectNMParams.NodeId;
						if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.bussleep)
						{
							NM_ControlBlock[NetId].nmTxPdu.OpCode.B.SleepInd = 1;
						}
						nmSendMessage();
					}
				}
			}
		}
	}
}
static NodeIdType nmDetermineLS(NodeIdType S,NodeIdType R,NodeIdType L)
{
	NodeIdType newL = L;
	if(L==R)
	{
		newL = S;
	}
	else
	{
		if(L<R)
		{
			if(S<L)
			{
				newL = S; /* SLR */
			}
			else
			{
				if(S<R)
				{
					/* LSR */
				}
				else
				{
					newL = S; /* LRS */
				}
			}
		}
		else
		{
			if(S<L)
			{
				if(S<R)
				{
					/* SRL */
				}
				else
				{
					newL = S; /* RSL */
				}
			}
			else
			{
				/* RLS */
			}
		}
	}
	return newL;
}
static boolean nmIsMeSkipped(NodeIdType S,NodeIdType R,NodeIdType D)
{
	boolean isSkipped = FALSE;
	if(D<R)
	{
		if(S<D)
		{
			/* not skipped SDR */
		}
		else
		{
			if(S<R)
			{
				isSkipped = TRUE; /* DRS */
			}
			else
			{
				/* not skipped DSR */
			}
		}
	}
	else
	{
		if(S<D)
		{
			if(S<R)
			{
				isSkipped = TRUE; /* SRD */
			}
			else
			{
				/* RSD */
			}
		}
		else
		{
			isSkipped = TRUE; /* RDS */
		}
	}
	return isSkipped;
}
static void nmAddToConfig(NetIdType NetId,ConfigKindName ConfigKind,NodeIdType NodeId)
{
	ConfigRefType Config = NULL;
	switch(ConfigKind)
	{
		case NM_ckNormal:
			Config = NM_ControlBlock[NetId].nmConfig.normal;
			break;
		case NM_ckNormalExtended:
			Config = NM_ControlBlock[NetId].nmConfig.normalExtended;
			break;
		case NM_ckLimphome:
			Config = NM_ControlBlock[NetId].nmConfig.limphome;
			break;
		default:
			break;
	}
	if(NULL != Config)
	{
		uint8 byte    = NodeId/8;
		uint8 bit     = NodeId%8;
		Config[byte] |= (1u<<bit);
	}
}

static void nmRemoveFromConfig(NetIdType NetId,ConfigKindName ConfigKind,NodeIdType NodeId)
{
	ConfigRefType Config = NULL;
	switch(ConfigKind)
	{
		case NM_ckNormal:
			Config = NM_ControlBlock[NetId].nmConfig.normal;
			break;
		case NM_ckNormalExtended:
			Config = NM_ControlBlock[NetId].nmConfig.normalExtended;
			break;
		case NM_ckLimphome:
			Config = NM_ControlBlock[NetId].nmConfig.limphome;
			break;
		default:
			break;
	}
	if(NULL != Config)
	{
		uint8 byte    = NodeId/8;
		uint8 bit     = NodeId%8;
		Config[byte] &= (~(1u<<bit));
	}
}
static void nmNormalMain(NetIdType NetId)
{
	if(nmIsAlarmStarted(TTyp))
	{
		nmSingalAlarm(TTyp);
		if(nmIsAlarmTimeout(TTyp))
		{
			nmCancelAlarm(TTyp);
			nmCancelAlarm(TMax);
			nmSetAlarm(TMax);
			if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.NMactive)
			{
				NM_ControlBlock[NetId].nmTxPdu.OpCode.b = NM_MaskRing;
				if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.bussleep)
				{
					NM_ControlBlock[NetId].nmTxPdu.OpCode.B.SleepInd = 1;
				}
				NM_ControlBlock[NetId].nmTxCount ++;
				nmSendMessage();
			}
			else
			{
			}
			if(NM_ControlBlock[NetId].nmTxCount > tx_limit)
			{
				NM_ControlBlock[NetId].nmState = NM_stLimphome;
				nmSetAlarm(TError);
			}
			else
			{
				if(NM_ControlBlock[NetId].nmMerker.W.stable)
				{
					NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.configurationstable = 1;
				}
				else
				{
					NM_ControlBlock[NetId].nmMerker.W.stable = 1;
				}
			}
		}
	}

	if(nmIsAlarmStarted(TMax))
	{
		nmSingalAlarm(TMax);
		if(nmIsAlarmTimeout(TMax))
		{
			nmCancelAlarm(TMax);
			nmInitReset6(NetId);
		}
	}
}
static void nmLimphomeMain(NetIdType NetId)
{
	if(nmIsAlarmStarted(TError))
	{
		nmSingalAlarm(TError);
		if(nmIsAlarmTimeout(TError))
		{
			nmCancelAlarm(TError);
			D_Online(NetId);
			NM_ControlBlock[NetId].nmTxPdu.OpCode.b = NM_MaskLimphome;
			if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.bussleep)
			{
				nmSetAlarm(TMax);
				NM_ControlBlock[NetId].nmTxPdu.OpCode.B.SleepInd =1;
				NM_ControlBlock[NetId].nmState = NM_stLimphomePrepSleep;
			}
			else
			{
				nmSetAlarm(TError);
			}
			if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.NMactive)
			{
				/* NM_ControlBlock[NetId].nmTxPdu.Destination = NM_ControlBlock[NetId].nmDirectNMParams.NodeId; */
				nmSendMessage();
			}
		}
	}
}
static void nmNormalPrepSleepMain(NetIdType NetId)
{
	if(nmIsAlarmStarted(TTyp))
	{
		nmSingalAlarm(TTyp);
		if(nmIsAlarmTimeout(TTyp))
		{
			nmCancelAlarm(TTyp);
			if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.NMactive)
			{
				/* Send ring message with set sleep.ack bit */
				NM_ControlBlock[NetId].nmTxPdu.OpCode.b = NM_MaskRing|NM_MaskSI|NM_MaskSA;
				nmSendMessage();
			}
		}
	}
}
static void nmBusSleep(NetIdType NetId)
{
	D_Init(NetId,BusSleep);
	NM_ControlBlock[NetId].nmState = NM_stBusSleep;
}
static void nmNormalTwbsMain(NetIdType NetId)
{
	if(nmIsAlarmStarted(TWbs))
	{
		nmSingalAlarm(TWbs);
		if(nmIsAlarmTimeout(TWbs))
		{
			nmCancelAlarm(TWbs);
			nmBusSleep(NetId);
		}
	}
}
static void nmLimphomePrepSleepMain(NetIdType NetId)
{
	if(nmIsAlarmStarted(TMax))
	{
		nmSingalAlarm(TMax);
		if(nmIsAlarmTimeout(TMax))
		{
			nmCancelAlarm(TMax);
			/* 7 NMInitBusSleep */
			D_Offline(NetId);
			nmSetAlarm(TWbs);
			NM_ControlBlock[NetId].nmState = NM_stTwbsLimphome;
		}
	}
}
static void nmTwbsLimphomeMain(NetIdType NetId)
{
	if(nmIsAlarmStarted(TWbs))
	{
		nmSingalAlarm(TWbs);
		if(nmIsAlarmTimeout(TWbs))
		{
			nmCancelAlarm(TWbs);
			nmBusSleep(NetId);
		}
	}
}
/* ============================ [ FUNCTIONS ] ====================================================== */
void InitNMType(NetIdType NetId,NMType nmType)
{
	NM_ControlBlock[NetId].nmType = nmType;
}

void InitNMScaling(NetIdType NetId,ScalingParamType ScalingParams)
{
	NM_ControlBlock[NetId].nmScalingParams = ScalingParams;
}
void InitCMaskTable(NetIdType NetId,ConfigKindName ConfigKind,ConfigRefType CMask)
{
	switch(ConfigKind)
	{
		case NM_ckNormal:
			(void)memcpy(NM_ControlBlock[NetId].nmCMask.normal,CMask,32);
			break;
		case NM_ckNormalExtended:
			(void)memcpy(NM_ControlBlock[NetId].nmCMask.normalExtended,CMask,32);
			break;
		case NM_ckLimphome:
			(void)memcpy(NM_ControlBlock[NetId].nmCMask.limphome,CMask,32);
			break;
		default:
			break;
	}
}

void InitTargetConfigTable(NetIdType NetId,ConfigKindName ConfigKind,ConfigRefType TargetConfig)
{
	switch(ConfigKind)
	{
		case NM_ckNormal:
			(void)memcpy(NM_ControlBlock[NetId].nmConfig.normal,TargetConfig,32);
			break;
		case NM_ckNormalExtended:
			(void)memcpy(NM_ControlBlock[NetId].nmConfig.normalExtended,TargetConfig,32);
			break;
		case NM_ckLimphome:
			(void)memcpy(NM_ControlBlock[NetId].nmConfig.limphome,TargetConfig,32);
			break;
		default:
			break;
	}
}

void InitIndDeltaConfig(NetIdType NetId,ConfigKindName ConfigKind,SignallingMode SMode,	\
				TaskType TaskId,EventMaskType EMask)
{
	switch(ConfigKind)
	{
		case NM_ckNormal:
			NM_ControlBlock[NetId].nmIndDeltaConfig.normal.SMode = SMode;
			NM_ControlBlock[NetId].nmIndDeltaConfig.normal.TaskId = TaskId;
			NM_ControlBlock[NetId].nmIndDeltaConfig.normal.EMask = EMask;
			break;
		case NM_ckNormalExtended:
			NM_ControlBlock[NetId].nmIndDeltaConfig.normalExtended.SMode = SMode;
			NM_ControlBlock[NetId].nmIndDeltaConfig.normalExtended.TaskId = TaskId;
			NM_ControlBlock[NetId].nmIndDeltaConfig.normalExtended.EMask = EMask;
			break;
		case NM_ckLimphome:
			NM_ControlBlock[NetId].nmIndDeltaConfig.limphome.SMode = SMode;
			NM_ControlBlock[NetId].nmIndDeltaConfig.limphome.TaskId = TaskId;
			NM_ControlBlock[NetId].nmIndDeltaConfig.limphome.EMask = EMask;
			break;
		default:
			break;
	}
}

void InitSMaskTable(NetIdType NetId,StatusRefType SMask)
{
	NM_ControlBlock[NetId].nmStatus.SMask = *SMask;
}
void InitTargetStatusTable(NetIdType NetId,StatusRefType TargetStatus)
{
	NM_ControlBlock[NetId].nmMerker.w = 0;
	NM_ControlBlock[NetId].nmStatus.NetworkStatus = *TargetStatus;
}
void InitIndDeltaStatus(NetIdType NetId,SignallingMode SMode,TaskType TaskId,EventMaskType EMask)
{
	NM_ControlBlock[NetId].nmStatus.SMode = SMode;
	NM_ControlBlock[NetId].nmStatus.TaskId = TaskId;
	NM_ControlBlock[NetId].nmStatus.EMask = EMask;
}

StatusType InitConfig(NetIdType NetId)
{

	return E_OK;
}
StatusType GetConfig(NetIdType NetId,ConfigRefType Config,ConfigKindName ConfigKind)
{
	switch(ConfigKind)
	{
		case NM_ckNormal:
			(void)memcpy(Config,NM_ControlBlock[NetId].nmConfig.normal,32);
			break;
		case NM_ckNormalExtended:
			(void)memcpy(Config,NM_ControlBlock[NetId].nmConfig.normalExtended,32);
			break;
		case NM_ckLimphome:
			(void)memcpy(Config,NM_ControlBlock[NetId].nmConfig.limphome,32);
			break;
		default:
			break;
	}
	return E_OK;
}

StatusType CmpConfig(NetIdType NetId,ConfigRefType TestConfig,ConfigRefType RefConfig,ConfigRefType CMask)
{
	StatusType ercd = E_OK;
	uint8 i;
	uint8 result;
	for(i=0;i<32;i++)
	{
		result = TestConfig[i]^RefConfig[i];
		result &= CMask[i];
		result = ~result;
		if(result != 0xFFU)
		{
			ercd = E_NOT_OK; /* TestConfig != RefConfig, */
			break;
		}
	}
	return ercd;
}

void InitDirectNMParams(NetIdType NetId,NodeIdType NodeId,TickType TimerTyp,TickType TimerMax, 	\
								TickType TimerError,TickType TimerWaitBusSleep,TickType TimerTx)
{
	NM_ControlBlock[NetId].nmDirectNMParams.NodeId = NodeId;
	NM_ControlBlock[NetId].nmDirectNMParams._TTyp = TimerTyp;
	NM_ControlBlock[NetId].nmDirectNMParams._TMax = TimerMax;
	NM_ControlBlock[NetId].nmDirectNMParams._TError = TimerError;
	NM_ControlBlock[NetId].nmDirectNMParams._TWbs = TimerWaitBusSleep;
	NM_ControlBlock[NetId].nmDirectNMParams._TTx = TimerTx;
	NM_ControlBlock[NetId].nmTxPdu.Source = NodeId;
}

/* see nm253.pdf Figure 30 Start-up of the network */
StatusType StartNM(NetIdType NetId)
{
	StatusType ercd = E_OK;
	/* Reset Control block, value 0 = invalid or initialize value */
	memset(&NM_ControlBlock[NetId],0,sizeof(NM_ControlBlockType));
	/* step 1: */
	NM_ControlBlock[NetId].nmTxPdu.OpCode.B.SleepInd = 0;
	NM_ControlBlock[NetId].nmTxPdu.OpCode.B.SleepAck = 0;
	/* step 2: enter NMInit */
	NM_ControlBlock[NetId].nmState= NM_stInit;
	NMInit(NetId);
	D_Init(NetId,BusInit);
	nmInit3(NetId);
	return ercd;
}

StatusType StopNM(NetIdType NetId)
{
	NM_ControlBlock[NetId].nmState= NM_stOff;
	return E_OK;
}

void InitIndRingData(NetIdType NetId,SignallingMode SMode,TaskType TaskId,EventMaskType EMask)
{
	NM_ControlBlock[NetId].nmRingDataInd.SMode = SMode;
	NM_ControlBlock[NetId].nmRingDataInd.TaskId = TaskId;
	NM_ControlBlock[NetId].nmRingDataInd.EMask = EMask;
}

void ReadRingData(NetIdType NetId,RingDataRefType RingData)
{
	memcpy(RingData,NM_ControlBlock[NetId].nmTxPdu.RingData,sizeof(RingDataType));
}
void TransmitRingData(NetIdType NetId,RingDataRefType RingData)
{
	memcpy(NM_ControlBlock[NetId].nmTxPdu.RingData,RingData,sizeof(RingDataType));
}
StatusType GotoMode(NetIdType NetId,NMModeName NewMode)
{
	if(NewMode == NM_BusSleep)
	{
		NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.bussleep = 1;
		switch(NM_ControlBlock[NetId].nmState)
		{
			case NM_stNormal:
			{
				if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.NMactive)
				{
					/* NMNormal */
				}
				else
				{
					nmDebug("GotoMode_BusSleep,Enter NormalPrepSleep.\n");
					NM_ControlBlock[NetId].nmState = NM_stNormalPrepSleep;
				}
				break;
			}
			default:
				break;
		}
	}
	else if(NewMode == NM_Awake)
	{
		NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.bussleep = 0;
		switch(NM_ControlBlock[NetId].nmState)
		{
			case NM_stNormalPrepSleep:
			{
				NM_ControlBlock[NetId].nmState = NM_stNormal;
				break;
			}
			case NM_stTwbsNormal:
			{
				nmCancelAlarm(TWbs);
				nmInitReset6(NetId);
				break;
			}
			case NM_stBusSleep:
			{
				D_Init(NetId,BusAwake);
				nmInit3(NetId);
				break;
			}
			case NM_stLimphomePrepSleep:
			{
				NM_ControlBlock[NetId].nmState = NM_stLimphome;
				nmSetAlarm(TError);
				break;
			}
			case NM_stTwbsLimphome:
			{
				nmCancelAlarm(TWbs);
				NM_ControlBlock[NetId].nmState = NM_stLimphome;
				nmSetAlarm(TError);
				break;
			}
			default:
				break;
		}
	}

	return E_OK;
}
StatusType SilentNM(NetIdType NetId)
{
	NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.NMactive = 0;
	return E_OK;
}
StatusType TalkNM(NetIdType NetId)
{
	NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.NMactive = 1;
	return E_OK;
}
void NM_BusErrorIndication(NetIdType NetId)
{
	D_Offline(NetId);
	D_Init(NetId,BusRestart);
	nmSetAlarm(TError);
	NM_ControlBlock[NetId].nmState = NM_stLimphome;
}
void NM_TxConformation(NetIdType NetId)
{
	NM_ControlBlock[NetId].nmTxCount = 0;
	switch(NM_ControlBlock[NetId].nmState)
	{
		case NM_stNormal:
		{
			if(NM_ControlBlock[NetId].nmTxPdu.OpCode.B.Ring)
			{
				nmCancelAlarm(TTyp);
				nmCancelAlarm(TMax);
				nmSetAlarm(TMax);
				if(NM_ControlBlock[NetId].nmTxPdu.OpCode.B.SleepInd)
				{
					if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.bussleep)
					{
						NM_ControlBlock[NetId].nmTxPdu.OpCode.B.SleepAck = 1;
						NM_ControlBlock[NetId].nmState = NM_stNormalPrepSleep;
					}
				}
			}
			break;
		}
		case NM_stNormalPrepSleep:
		{	/* 2 NMInitBusSleep */
			if(NM_ControlBlock[NetId].nmTxPdu.OpCode.B.Ring)
			{
				D_Offline(NetId);
				nmSetAlarm(TWbs);
				NM_ControlBlock[NetId].nmState = NM_stTwbsNormal;
			}
			break;
		}
		case NM_stLimphome:
		{
			if(NM_ControlBlock[NetId].nmTxPdu.OpCode.B.Limphome)
			{
				NM_ControlBlock[NetId].nmMerker.W.limphome = 1;
			}
			break;
		}
		default:
			break;
	}
}
void NM_RxIndication(NetIdType NetId,NMPduType* NMPDU)
{
	switch(NM_ControlBlock[NetId].nmState)
	{
		case NM_stNormal:
		case NM_stNormalPrepSleep:
		{
			nmNormalStandard(NetId,NMPDU);
			if(NMPDU->OpCode.B.SleepAck)
			{
				if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.bussleep)
				{ /* 2 NMInitBusSleep */
					D_Offline(NetId);
					nmSetAlarm(TWbs);
					NM_ControlBlock[NetId].nmState = NM_stTwbsNormal;
				}
			}
			/* Special process for NM_stNormalPrepSleep only */
			if(NM_stNormalPrepSleep == NM_ControlBlock[NetId].nmState)
			{
				if(NMPDU->OpCode.B.SleepInd)
				{
				}
				else
				{
					NM_ControlBlock[NetId].nmState = NM_stNormal;
				}
			}
			break;
		}
		case NM_stTwbsNormal:
		{
			if(NMPDU->OpCode.B.SleepInd)
			{  	/* = 1 */
			}
			else
			{	/* = 0 */
				nmCancelAlarm(TWbs);
				nmInitReset6(NetId);
			}
			break;
		}
		case NM_stLimphome:
		{
			if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.NMactive)
			{
				if(NM_ControlBlock[NetId].nmMerker.W.limphome)
				{
					if( (NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.bussleep) && (NMPDU->OpCode.B.SleepAck))
					{
						D_Offline(NetId);
						nmSetAlarm(TWbs);
						NM_ControlBlock[NetId].nmState = NM_stTwbsLimphome;
					}
					else
					{
						nmInitReset5(NetId);
					}
				}
				else
				{
					if(NMPDU->OpCode.B.SleepAck)
					{
						D_Offline(NetId);
						nmSetAlarm(TWbs);
						NM_ControlBlock[NetId].nmState = NM_stTwbsLimphome;
					}
					else
					{
						nmInitReset5(NetId);
					}
				}
			}
			else
			{
				if(NM_ControlBlock[NetId].nmMerker.W.limphome)
				{
					if( (NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.bussleep) && (NMPDU->OpCode.B.SleepAck))
					{
						D_Offline(NetId);
						nmSetAlarm(TWbs);
						NM_ControlBlock[NetId].nmState = NM_stTwbsLimphome;
					}
					else
					{
						nmInitReset5(NetId);
					}
				}
				else
				{
					if(NMPDU->OpCode.B.SleepAck)
					{
						D_Offline(NetId);
						nmSetAlarm(TWbs);
						NM_ControlBlock[NetId].nmState = NM_stTwbsLimphome;
					}
					else
					{
						nmInitReset5(NetId);
					}
				}
			}
			break;
		}
		case NM_stLimphomePrepSleep:
		{
			if(0 == NMPDU->OpCode.B.SleepInd)
			{
			}
			else
			{
				NM_ControlBlock[NetId].nmState = NM_stLimphome;
			}
			break;
		}
		case NM_stTwbsLimphome:
		{
			if(0 == NMPDU->OpCode.B.SleepInd)
			{
				nmCancelAlarm(TWbs);
				NM_ControlBlock[NetId].nmState = NM_stLimphome;
			}
			else
			{
			}
			break;
		}
		default:
			break;
	}
}
void NM_WakeupIndication(NetIdType NetId)
{
	if(NM_stBusSleep == NM_ControlBlock[NetId].nmState)
	{	/* 3 NMInit */
		/* OK Wakeup */
		D_Init(NetId,BusAwake);
		nmInit3(NetId);
	}
}

void NM_MainFuntion(void)
{
	NetIdType NetId;
	for(NetId= 0; NetId < OSEKNM_NET_NUM; NetId ++)
	{
		if(nmIsAlarmStarted(TTx))
		{
			nmSingalAlarm(TTx);
			if(nmIsAlarmTimeout(TTx))
			{
				nmCancelAlarm(TTx);
				nmSendMessage();
				continue; /* skip the process of state */
			}
		}
		switch(NM_ControlBlock[NetId].nmState)
		{
			case NM_stNormal:
				nmNormalMain(NetId);
				break;
			case NM_stLimphome:
				nmLimphomeMain(NetId);
				break;
			case NM_stNormalPrepSleep:
				nmNormalPrepSleepMain(NetId);
				break;
			case NM_stTwbsNormal:
				nmNormalTwbsMain(NetId);
				break;
			case NM_stLimphomePrepSleep:
				nmLimphomePrepSleepMain(NetId);
				break;
			case NM_stTwbsLimphome:
				nmTwbsLimphomeMain(NetId);
				break;
			default:
				break;
		}
	}
}
#endif /* USE_OSEKNM */
