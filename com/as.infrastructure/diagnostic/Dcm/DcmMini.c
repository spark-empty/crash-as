/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2018  AS <parai@foxmail.com>
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

/* design according to ISR 14229 (2006).pdf */
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Dcm.h"
#include "Dcm_Internal.h"
#include "CanTp.h"
#include "Os.h"
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
#define AS_LOG_DCM  0
#define AS_LOG_DCME 1

#ifndef DCM_INSTANCE_NUM
#define DCM_INSTANCE_NUM 1
#endif

#ifndef DCM_DEFAULT_RXBUF_SIZE
#define DCM_DEFAULT_RXBUF_SIZE 4095
#endif
#ifndef DCM_DEFAULT_TXBUF_SIZE
#define DCM_DEFAULT_TXBUF_SIZE 4095
#endif

#if defined(USE_ANYOS) && defined(__AS_BOOTLOADER__)
#ifndef DCM_MAIN_FUNCTION_PERIOD
#define DCM_MAIN_FUNCTION_PERIOD 1
#endif
#endif

#ifndef DCM_MAIN_FUNCTION_PERIOD
#define DCM_MAIN_FUNCTION_PERIOD 10
#endif
#define msToDcmTick(__ms) (((__ms)+DCM_MAIN_FUNCTION_PERIOD-1)/DCM_MAIN_FUNCTION_PERIOD)

#define dcmSetAlarm(Alarm,timeMs)						\
do{												\
	DCM_RTE.timer##Alarm = msToDcmTick(timeMs)+1;	\
}while(0)

#define dcmSignalAlarm(Alarm)					\
do{										\
	if(DCM_RTE.timer##Alarm > 1)				\
	{									\
		DCM_RTE.timer##Alarm --;				\
	}									\
}while(0)
#define dcmCancelAlarm(Alarm) { DCM_RTE.timer##Alarm = 0;}
#define dcmIsAlarmTimeout(Alarm) ( 1u == DCM_RTE.timer##Alarm )
#define dcmIsAlarmStarted(Alarm) ( 0u != DCM_RTE.timer##Alarm )

#define DCM_RTE dcmRTE[Instance]

#define DCM_EOL	(-1)

#ifdef __AS_BOOTLOADER__
#define DCM_GET_SESSION_CHANGE_PERMISSION_FNC BL_GetSessionChangePermission
#else
#define DCM_GET_SESSION_CHANGE_PERMISSION_FNC Dcm_GetSessionChangePermission
#endif

#define DCM_RXSDU   ((const PduInfoType *)DCM_RTE.parameter[0])
#define DCM_RXSDU_SIZE (((const PduInfoType *)DCM_RTE.parameter[0])->SduLength)
#define DCM_RXSDU_DATA (((const PduInfoType *)DCM_RTE.parameter[0])->SduDataPtr)
#define DCM_TXSDU ((const PduInfoType *)DCM_RTE.parameter[1])
#define DCM_TXSDU_SIZE (((const PduInfoType *)DCM_RTE.parameter[1])->SduLength)
#define DCM_TXSDU_DATA (((const PduInfoType *)DCM_RTE.parameter[1])->SduDataPtr)
#define DCM_SESSION_LIST ((const uint8 *)DCM_RTE.parameter[2])
#define DCM_GET_SESSION_CHANGE_PERMISSION ((const Dcm_CallbackGetSesChgPermissionFncType)DCM_RTE.parameter[3])
#define DCM_SECURITY_LEVEL_LIST ((const uint8 *)DCM_RTE.parameter[4])
#define DCM_SECURITY_SEED_SIZE_LIST ((const uint8 *)DCM_RTE.parameter[5])
#define DCM_SECURITY_KEY_SIZE_LIST ((const uint8 *)DCM_RTE.parameter[6])
#define DCM_SECURITY_GET_SEED_FNC_LIST ((const Dcm_CallbackGetSeedFncType*)DCM_RTE.parameter[7])
#define DCM_SECURITY_COMPARE_KEY_FNC_LIST ((const Dcm_CallbackCompareKeyFncType*)DCM_RTE.parameter[8])

#define DCM_S3SERVER_TIMEOUT_MS ((uint32)DCM_RTE.parameter[9])
#define DCM_P2SERVER_TIMEOUT_MS ((uint32)DCM_RTE.parameter[10])

#define DCM_SERVICE_LIST_IN_SESSION ((uint8**)DCM_RTE.parameter[11])
#define DCM_SERVICE_LIST_IN_LEVEL   ((uint8**)DCM_RTE.parameter[12])

#ifdef USE_USB_CAN
#define DCM_S3SERVER_CFG_TIMEOUT_MS 10000
#else
#define DCM_S3SERVER_CFG_TIMEOUT_MS 5000
#endif
#define DCM_INSTANCE_DEFAULT_PARAMETER	\
	{ (Dcm_ParameterType)&rxPduInfo, (Dcm_ParameterType)&txPduInfo, \
	  (Dcm_ParameterType)sesList, (Dcm_ParameterType)DCM_GET_SESSION_CHANGE_PERMISSION_FNC, \
	  (Dcm_ParameterType)secList, (Dcm_ParameterType)secSeedKeySizeList,  (Dcm_ParameterType)secSeedKeySizeList, \
	  (Dcm_ParameterType)getSeedList, (Dcm_ParameterType)compareKeyList, \
	  (Dcm_ParameterType)DCM_S3SERVER_CFG_TIMEOUT_MS, (Dcm_ParameterType)100, \
	  (Dcm_ParameterType)sesServiseList, (Dcm_ParameterType)secServiseList, \
	}
/* ============================ [ TYPES     ] ====================================================== */
enum {
	DCM_BUFFER_IDLE = 0,
	DCM_BUFFER_PROVIDED,
	DCM_BUFFER_FULL,
};

/* UDT = Upload Download Transfer */
typedef enum
{
	DCM_UDT_IDLE_STATE = 0,
	DCM_UDT_UPLOAD_STATE,
	DCM_UDT_DOWNLOAD_STATE
}Dcm_UDTStateType;

typedef struct
{
	Dcm_UDTStateType  state;
	uint32 memoryAddress;
	uint32 memorySize;
	uint8  blockSequenceCounter;
	uint8  dataFormatIdentifier;
	uint8  memoryIdentifier;
}Dcm_UDTType;

typedef struct
{
	TimerType timerS3Server;
	TimerType timerP2Server;
	const Dcm_ParameterType* parameter;
	PduLengthType rxPduLength;
	PduLengthType txPduLength;
	uint8 currentSID;
	uint8 currentSession;
	uint8 currentLevel;
	uint8 supressPositiveResponse;
	uint8 rxPduState;
	uint8 txPduState;
	uint8 seedRequested;
	uint8 counter;
#if defined(DCM_USE_SERVICE_REQUEST_DOWNLOAD) || defined(DCM_USE_SERVICE_REQUEST_UPLOAD)
	Dcm_UDTType UDTData;
#endif
} Dcm_RuntimeType; /* RTE */
/* ============================ [ DECLARES  ] ====================================================== */
static void SendNRC(PduIdType Instance, uint8 nrc);
static void SendPRC(PduIdType Instance);

#ifdef __AS_BOOTLOADER__
Std_ReturnType BL_GetSessionChangePermission(Dcm_SesCtrlType sesCtrlTypeActive, Dcm_SesCtrlType sesCtrlTypeNew);
Std_ReturnType BL_GetProgramSessionSeed (uint8 *securityAccessDataRecord, uint8 *seed,
		Dcm_NegativeResponseCodeType *errorCode);
Std_ReturnType BL_CompareProgramSessionKey (uint8 *key);
Std_ReturnType BL_GetExtendedSessionSeed (uint8 *securityAccessDataRecord, uint8 *seed,
		Dcm_NegativeResponseCodeType *errorCode);
Std_ReturnType BL_CompareExtendedSessionKey (uint8 *key);
#endif

Std_ReturnType Dcm_GetSessionChangePermission(Dcm_SesCtrlType sesCtrlTypeActive, Dcm_SesCtrlType sesCtrlTypeNew);
Std_ReturnType Dcm_GetSeed(uint8 *securityAccessDataRecord, uint8 *seed, Dcm_NegativeResponseCodeType *errorCode);
Std_ReturnType Dcm_CompareKey(uint8 *key);
/* ============================ [ DATAS     ] ====================================================== */
static Dcm_RuntimeType dcmRTE[DCM_INSTANCE_NUM];
/* uint64 for 8 byte alignment */
static uint64 rxBuffer[(DCM_DEFAULT_RXBUF_SIZE+sizeof(uint64)-1)/sizeof(uint64)];
static uint64 txBuffer[(DCM_DEFAULT_TXBUF_SIZE+sizeof(uint64)-1)/sizeof(uint64)];
/* 0xFFF=4095 is the maximum ability */
static const PduInfoType rxPduInfo =
{
	(uint8*)rxBuffer, sizeof(rxBuffer)
};

static const PduInfoType txPduInfo =
{
	(uint8*)txBuffer, sizeof(txBuffer)
};
static const uint8  sesList[] = { DCM_DEFAULT_SESSION, DCM_PROGRAMMING_SESSION, DCM_EXTENDED_DIAGNOSTIC_SESSION, DCM_EOL };
static const uint8  servicesInDFTS[] =  { SID_DIAGNOSTIC_SESSION_CONTROL, DCM_EOL };
static const uint8  servicesInPRGS[] =  { SID_DIAGNOSTIC_SESSION_CONTROL, SID_SECURITY_ACCESS,
		SID_REQUEST_DOWNLOAD, SID_REQUEST_UPLOAD, SID_TRANSFER_DATA, SID_REQUEST_TRANSFER_EXIT,
		SID_ECU_RESET, SID_ROUTINE_CONTROL, DCM_EOL };
static const uint8  servicesInEXTDS[] = { SID_DIAGNOSTIC_SESSION_CONTROL, SID_SECURITY_ACCESS, DCM_EOL };
static const uint8* sesServiseList[] = { servicesInDFTS, servicesInPRGS, servicesInEXTDS };
static const uint8 secList[] = { 1 /* EXTDS */, 2 /* PRGS */, DCM_EOL };
static const uint8  servicesInLevel1[] = { DCM_EOL };
static const uint8  servicesInLevel2[] = { SID_REQUEST_DOWNLOAD, SID_REQUEST_UPLOAD, SID_TRANSFER_DATA,
		SID_REQUEST_TRANSFER_EXIT, SID_ECU_RESET, SID_ROUTINE_CONTROL, DCM_EOL };
static const uint8* secServiseList[] = { servicesInLevel1, servicesInLevel2 };
static const uint8 secSeedKeySizeList[] = { 4 /* EXTDS */, 4 /* PRGS */ };
#ifdef __AS_BOOTLOADER__
static const Dcm_CallbackGetSeedFncType getSeedList[] = { BL_GetExtendedSessionSeed, BL_GetProgramSessionSeed };
static const Dcm_CallbackCompareKeyFncType compareKeyList[] = { BL_CompareExtendedSessionKey, BL_CompareProgramSessionKey };
#else
static const Dcm_CallbackGetSeedFncType getSeedList[] = { Dcm_GetSeed, Dcm_GetSeed };
static const Dcm_CallbackCompareKeyFncType compareKeyList[] = { Dcm_CompareKey, Dcm_CompareKey };
#endif
static const uint32 dcmInstanceDefaultParameter[] = DCM_INSTANCE_DEFAULT_PARAMETER;

/* ============================ [ LOCALS    ] ====================================================== */
Std_ReturnType __weak Dcm_GetSessionChangePermission(Dcm_SesCtrlType sesCtrlTypeActive, Dcm_SesCtrlType sesCtrlTypeNew)
{
	Std_ReturnType ercd = E_OK;
	return ercd;
}

Std_ReturnType __weak Dcm_GetSeed(uint8 *securityAccessDataRecord, uint8 *seed, Dcm_NegativeResponseCodeType *errorCode)
{
	Std_ReturnType ercd = E_OK;
	*errorCode = DCM_E_POSITIVE_RESPONSE;
	return ercd;
}
Std_ReturnType __weak Dcm_CompareKey(uint8 *key)
{
	Std_ReturnType ercd = E_OK;
	return ercd;
}

#if defined(DCM_USE_SERVICE_REQUEST_DOWNLOAD) \
	|| defined(DCM_USE_SERVICE_REQUEST_UPLOAD)
boolean __weak Dcm_CheckMemory(uint8 attr, uint8 memoryIdentifier, uint32 memoryAddress, uint32 length)
{	/*attr: bit mask 0x04=READ 0x02=WRITE 0x01=EXECUTE */
	return TRUE;
}

boolean __weak Dcm_CheckDataFormatIdentifier(uint8 dataFormatIdentifier)
{
	return TRUE;
}
#endif


static void HandleSubFunction(PduIdType Instance)
{
	if(DCM_RXSDU_DATA[1]&0x80)
	{
		DCM_RXSDU_DATA[1] &= 0x7F;
		DCM_RTE.supressPositiveResponse = TRUE;
	}
}

static uint8 u8IndexOfList(uint8 val, const uint8* pList)
{
	uint8 index = DCM_EOL;
	const uint8* pVar = pList;
	while((uint8)DCM_EOL != *pVar)
	{
		if(*pVar == val)
		{
			index = pVar - pList;
			break;
		}
		pVar++;
	}

	return index;
}

static void HandleSessionControl(PduIdType Instance)
{
	uint8 session;
	uint8 index;
	Std_ReturnType ercd;
	if(2 == DCM_RTE.rxPduLength)
	{
		HandleSubFunction(Instance);

		session = DCM_RXSDU_DATA[1];
		index = u8IndexOfList(session, DCM_SESSION_LIST);
		if(index != (uint8)DCM_EOL)
		{
			ercd = DCM_GET_SESSION_CHANGE_PERMISSION(DCM_RTE.currentSession, session);

			if(E_OK == ercd)
			{
				DCM_RTE.currentSession = session;
				Dcm_AppendTX(Instance, session);
				Dcm_AppendTX(Instance, (DCM_P2SERVER_TIMEOUT_MS>>8)&0xFF);
				Dcm_AppendTX(Instance, (DCM_P2SERVER_TIMEOUT_MS)&0xFF);
				Dcm_AppendTX(Instance, 0x00);
				Dcm_AppendTX(Instance, 0x0A);
				SendPRC(Instance);
			}
			else
			{
				SendNRC(Instance, DCM_E_CONDITIONS_NOT_CORRECT);
			}
		}
		else
		{
			SendNRC(Instance, DCM_E_SUB_FUNCTION_NOT_SUPPORTED);
		}
	}
	else
	{
		SendNRC(Instance, DCM_E_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
	}
}

static void HandleSecurityAccess(PduIdType Instance)
{
	uint8 level;
	uint8 index;
	Std_ReturnType ercd;
	Dcm_NegativeResponseCodeType errorCode = DCM_E_REQUEST_OUT_OF_RANGE;
	if(DCM_RTE.rxPduLength >= 2)
	{
		HandleSubFunction(Instance);
		level = (DCM_RXSDU_DATA[1] + 1) >> 1;
		index = u8IndexOfList(level, DCM_SECURITY_LEVEL_LIST);
		if(index != (uint8)DCM_EOL)
		{
			if(DCM_RXSDU_DATA[1]&0x01)
			{	/* requestSeed */
				if(2 != DCM_RTE.rxPduLength)
				{
					SendNRC(Instance, DCM_E_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
				}
				else
				{
					if(level == DCM_RTE.currentLevel)
					{	/* already unlocked */
						DCM_TXSDU_DATA[1] = DCM_RXSDU_DATA[1];
						memset(&DCM_TXSDU_DATA[2], 0, DCM_SECURITY_SEED_SIZE_LIST[index]);
						DCM_RTE.txPduLength = DCM_SECURITY_SEED_SIZE_LIST[index]+1;
						SendPRC(Instance);
					}
					else
					{
						ercd = DCM_SECURITY_GET_SEED_FNC_LIST[index](NULL, &DCM_TXSDU_DATA[2], &errorCode);
						if(E_OK == ercd)
						{
							DCM_TXSDU_DATA[1] = DCM_RXSDU_DATA[1];
							DCM_RTE.txPduLength = DCM_SECURITY_SEED_SIZE_LIST[index]+1;
							SendPRC(Instance);

							DCM_RTE.seedRequested = TRUE;
						}
						else
						{
							SendNRC(Instance, errorCode);
						}
					}
				}
			}
			else
			{	/* sendKey */
				if((DCM_SECURITY_KEY_SIZE_LIST[index]+2) != DCM_RTE.rxPduLength)
				{
					SendNRC(Instance, DCM_E_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
				}
				else if(FALSE == DCM_RTE.seedRequested)
				{
					SendNRC(Instance, DCM_E_REQUEST_SEQUENCE_ERROR);
				}
				else
				{
					ercd = DCM_SECURITY_COMPARE_KEY_FNC_LIST[index](&DCM_RXSDU_DATA[2]);
					if(E_OK == ercd)
					{
						DCM_TXSDU_DATA[1] = DCM_RXSDU_DATA[1];
						DCM_RTE.txPduLength = 1;
						SendPRC(Instance);

						DCM_RTE.seedRequested = FALSE;
						DCM_RTE.currentLevel = level;
					}
					else
					{
						SendNRC(Instance, DCM_E_INVALID_KEY);
					}
				}
			}
		}
		else
		{
			SendNRC(Instance, DCM_E_SUB_FUNCTION_NOT_SUPPORTED);
		}
	}
	else
	{
		SendNRC(Instance, DCM_E_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
	}
}

#if defined(DCM_USE_SERVICE_ROUTINE_CONTROL)
#ifdef __AS_BOOTLOADER__
static void BL_StartEraseFlash(PduIdType Instance)
{
	uint32 memoryAddress;
	uint32 length;
	uint8  memoryIdentifier;
	Dcm_ReturnEraseMemoryType eraseRet;
	if(13 == DCM_RTE.rxPduLength)
	{
		if(DCM_RTE.currentSession != DCM_PROGRAMMING_SESSION)
		{
			SendNRC(Instance, DCM_E_SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION);
		}
		else if(DCM_RTE.currentLevel != 2 /* PRGS */)
		{
			SendNRC(Instance, DCM_E_SECUTITY_ACCESS_DENIED);
		}
		else
		{
			memoryAddress = ((uint32)DCM_RXSDU_DATA[4]<<24) + ((uint32)DCM_RXSDU_DATA[5]<<16)
					+ ((uint32)DCM_RXSDU_DATA[6]<<8) +((uint32)DCM_RXSDU_DATA[7]);
			length  = ((uint32)DCM_RXSDU_DATA[8]<<24) + ((uint32)DCM_RXSDU_DATA[9]<<16)
					+ ((uint32)DCM_RXSDU_DATA[10]<<8) +((uint32)DCM_RXSDU_DATA[11]);
			memoryIdentifier = DCM_RXSDU_DATA[12];

			eraseRet = Dcm_EraseMemory( (1==DCM_RTE.counter)?DCM_INITIAL:DCM_PENDING,
										memoryIdentifier,
										memoryAddress,
										length);
			if(DCM_ERASE_OK == eraseRet)
			{
				DCM_TXSDU_DATA[1] = DCM_RXSDU_DATA[1];
				DCM_TXSDU_DATA[2] = DCM_RXSDU_DATA[2];
				DCM_TXSDU_DATA[3] = DCM_RXSDU_DATA[3];
				DCM_RTE.txPduLength = 3;
				SendPRC(Instance);
			}
			else if(DCM_ERASE_PENDING == eraseRet)
			{
				/* nothing */
			}
			else
			{
				SendNRC(Instance, DCM_E_GENERAL_PROGRAMMING_FAILURE);
			}
		}
	}
	else
	{
		SendNRC(Instance, DCM_E_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
	}
}

Std_ReturnType BL_TestJumpToApplicatin(uint8 *inBuffer, uint8 *outBuffer, Dcm_NegativeResponseCodeType *errorCode);
static void BL_StartApplication(PduIdType Instance)
{
	Dcm_NegativeResponseCodeType errorCode;
	(void) BL_TestJumpToApplicatin(&DCM_RXSDU_DATA[4], &DCM_TXSDU_DATA[4], &errorCode);
	SendNRC(Instance, DCM_E_REQUEST_OUT_OF_RANGE);
}
#endif
static void HandleRoutineControlStart(PduIdType Instance)
{
#ifdef __AS_BOOTLOADER__
	uint16 rcId = (uint16)((uint16)DCM_RXSDU_DATA[2] << 8) + DCM_RXSDU_DATA[3];
	switch(rcId)
	{
		case 0xFF01:
			BL_StartEraseFlash(Instance);
			break;
		case 0xFF03:
			BL_StartApplication(Instance);
			break;
		default:
			SendNRC(Instance, DCM_E_REQUEST_OUT_OF_RANGE);
			break;
	}
#else
	SendNRC(Instance, DCM_E_SUB_FUNCTION_NOT_SUPPORTED);
#endif
}

static void HandleRoutineControlStop(PduIdType Instance)
{
	SendNRC(Instance, DCM_E_SUB_FUNCTION_NOT_SUPPORTED);
}

static void HandleRoutineControlResult(PduIdType Instance)
{
	SendNRC(Instance, DCM_E_SUB_FUNCTION_NOT_SUPPORTED);
}

static void HandleRoutineControl(PduIdType Instance)
{
	if(DCM_RTE.rxPduLength >= 4)
	{
		HandleSubFunction(Instance);

		switch(DCM_RXSDU_DATA[1])
		{
			case 0x01: /* start */
				HandleRoutineControlStart(Instance);
				break;
			case 0x02: /* stop */
				HandleRoutineControlStop(Instance);
				break;
			case 0x03: /* request result */
				HandleRoutineControlResult(Instance);
				break;
			default:
				SendNRC(Instance, DCM_E_SUB_FUNCTION_NOT_SUPPORTED);
				break;
		}
	}
	else
	{
		SendNRC(Instance, DCM_E_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
	}

}

#endif /* DCM_USE_SERVICE_ROUTINE_CONTROL */
#if defined(DCM_USE_SERVICE_REQUEST_DOWNLOAD) || defined(DCM_USE_SERVICE_REQUEST_UPLOAD)
static void HandleRequestDownloadOrUpload(PduIdType Instance, Dcm_UDTStateType state)
{
	Std_ReturnType ercd;
	uint8 dataFormatIdentifier;
	uint8 addressFormat;
	uint8 lengthFormat;
	uint8 memoryIdentifier;
	if(DCM_RTE.rxPduLength >= 5)
	{
		dataFormatIdentifier = DCM_RXSDU_DATA[1];
		addressFormat = (uint8)((DCM_RXSDU_DATA[2]>>0u)&0x0Fu);
		lengthFormat  = (uint8)((DCM_RXSDU_DATA[2]>>4u)&0x0Fu);
		memoryIdentifier = DCM_RXSDU_DATA[3+addressFormat+lengthFormat];
		if((addressFormat+lengthFormat+4u) == DCM_RTE.rxPduLength)
		{
			if( (addressFormat<=4) && (lengthFormat<=4) && 	\
				(Dcm_CheckDataFormatIdentifier(dataFormatIdentifier)))
			{
				uint32 memoryAddress=0u,memorySize=0u;
				for(int i=0;i<addressFormat;i++)
				{
					memoryAddress = (memoryAddress<<8) + DCM_RXSDU_DATA[3+i];
				}
				for(int i=0;i<lengthFormat;i++)
				{
					memorySize = (memorySize<<8) + DCM_RXSDU_DATA[3+addressFormat+i];
				}

				if(Dcm_CheckMemory((DCM_UDT_DOWNLOAD_STATE==state)?0x02:0x04,
						memoryIdentifier, memoryAddress, memorySize))
				{
					DCM_RTE.UDTData.state   = state;
					DCM_RTE.UDTData.memoryAddress = memoryAddress;
					DCM_RTE.UDTData.memorySize    = memorySize;
					DCM_RTE.UDTData.dataFormatIdentifier = dataFormatIdentifier;
					DCM_RTE.UDTData.memoryIdentifier = memoryIdentifier;
					DCM_RTE.UDTData.blockSequenceCounter = 1u;

					ASLOG(DCM,"request %s addr(%X) size(%X),memory=%X\n",
							(DCM_UDT_DOWNLOAD_STATE==state)?"download":"upload",
							memoryAddress, memorySize, memoryIdentifier);
					/* create positive response code */
					DCM_TXSDU_DATA[1] = 0x20;  /* lengthFormatIdentifier = 2 Bytes */

					DCM_TXSDU_DATA[2] = (DCM_TXSDU_SIZE >> 8) & 0xFF;
					DCM_TXSDU_DATA[3] = (DCM_TXSDU_SIZE >> 0) & 0xFF;
					DCM_RTE.txPduLength = 3;
					SendPRC(Instance);
				}
				else
				{
					SendNRC(Instance, DCM_E_REQUEST_OUT_OF_RANGE);
				}
			}
			else
			{
				SendNRC(Instance, DCM_E_REQUEST_OUT_OF_RANGE);
			}
		}
		else
		{
			SendNRC(Instance, DCM_E_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
		}
	}
	else
	{
		SendNRC(Instance, DCM_E_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
	}
}
#endif

#if defined(DCM_USE_SERVICE_REQUEST_DOWNLOAD)
static void HandleTransferDownload(PduIdType Instance)
{
	uint32 memoryAddress;
	uint32 length;
	uint8   memoryIdentifier;
	Dcm_ReturnWriteMemoryType writeRet;

	if(DCM_RTE.UDTData.memorySize>0)
	{
		if(DCM_RTE.rxPduLength < 4)
		{
			SendNRC(Instance, DCM_E_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
		}
		else if(DCM_RTE.UDTData.blockSequenceCounter != DCM_RXSDU_DATA[1])
		{
			SendNRC(Instance, DCM_E_WRONG_BLOCK_SEQUENCE_COUNTER);
		}
		else
		{
			memoryAddress = DCM_RTE.UDTData.memoryAddress;
			length = DCM_RTE.rxPduLength-4;
			memoryIdentifier = DCM_RXSDU_DATA[3];
			if(DCM_RTE.UDTData.memorySize < length)
			{
				length = DCM_RTE.UDTData.memorySize;
			}

			if(DCM_RTE.UDTData.memoryIdentifier != memoryIdentifier)
			{
				SendNRC(Instance, DCM_E_REQUEST_OUT_OF_RANGE);
			}
			else
			{
				writeRet = Dcm_WriteMemory((1==DCM_RTE.counter)?DCM_INITIAL:DCM_PENDING,
											memoryIdentifier,
											memoryAddress,
											length,
											&DCM_RXSDU_DATA[4]);
				if(DCM_WRITE_OK == writeRet)
				{
					DCM_RTE.UDTData.memoryAddress += length;
					DCM_RTE.UDTData.memorySize    -= length;
					DCM_RTE.UDTData.blockSequenceCounter ++; /* may roll-over from 0xFF to 0x00 */

					/* create positive response code */
					DCM_TXSDU_DATA[1] = DCM_RXSDU_DATA[1];
					DCM_RTE.txPduLength = 1;
					SendPRC(Instance);
				}
				else if(DCM_WRITE_PENDING == writeRet)
				{	/* switch op status to pending and no response,
					 * so this HandleTransferDownload will be called again */
				}
				else
				{
					SendNRC(Instance, DCM_E_GENERAL_PROGRAMMING_FAILURE);
				}
			}
		}
	}
	else
	{
		SendNRC(Instance, DCM_E_CONDITIONS_NOT_CORRECT);
	}
}
#endif

#if defined(DCM_USE_SERVICE_REQUEST_UPLOAD)
static void HandleTransferUpload(PduIdType Instance)
{
	uint32 memoryAddress;
	uint32 length;
	uint8   memoryIdentifier;
	Dcm_ReturnReadMemoryType readRet;

	if(DCM_RTE.UDTData.memorySize>0)
	{
		if(DCM_RTE.rxPduLength != 4)
		{
			SendNRC(Instance, DCM_E_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
		}
		else if(DCM_RTE.UDTData.blockSequenceCounter != DCM_RXSDU_DATA[1])
		{
			SendNRC(Instance, DCM_E_WRONG_BLOCK_SEQUENCE_COUNTER);
		}
		else
		{
			memoryAddress = DCM_RTE.UDTData.memoryAddress;
			length = (DCM_TXSDU_SIZE-2)&0xFFFC; /* ability 4 align */
			memoryIdentifier = DCM_RXSDU_DATA[3];
			if(DCM_RTE.UDTData.memorySize < length)
			{
				length = DCM_RTE.UDTData.memorySize;
			}

			if(DCM_RTE.UDTData.memoryIdentifier != memoryIdentifier)
			{
				SendNRC(Instance, DCM_E_REQUEST_OUT_OF_RANGE);
			}
			else
			{
				readRet = Dcm_ReadMemory((1==DCM_RTE.counter)?DCM_INITIAL:DCM_PENDING,
												memoryIdentifier,
												memoryAddress,
												length,
												&DCM_TXSDU_DATA[2]);
				if(DCM_READ_OK == readRet)
				{
					DCM_RTE.UDTData.memoryAddress += length;
					DCM_RTE.UDTData.memorySize    -= length;
					DCM_RTE.UDTData.blockSequenceCounter ++; /* may roll-over from 0xFF to 0x00 */

					/* create positive response code */
					DCM_TXSDU_DATA[1] = DCM_RXSDU_DATA[1];
					DCM_RTE.txPduLength = 1+length;
					SendPRC(Instance);
				}
				else if(DCM_READ_PENDING == readRet)
				{	/* switch op status to pending and no response,
					 * so this HandleTransferUpload will be called again */
				}
				else
				{
					SendNRC(Instance, DCM_E_GENERAL_PROGRAMMING_FAILURE);
				}
			}
		}
	}
	else
	{
		SendNRC(Instance, DCM_E_CONDITIONS_NOT_CORRECT);
	}
}
#endif
#if defined(DCM_USE_SERVICE_TRANSFER_DATA)
static void HandleTransferData(PduIdType Instance)
{
	switch(DCM_RTE.UDTData.state)
	{
		#if defined(DCM_USE_SERVICE_REQUEST_UPLOAD)
		case DCM_UDT_UPLOAD_STATE:
			HandleTransferUpload(Instance);
			break;
		#endif
		#if defined(DCM_USE_SERVICE_REQUEST_DOWNLOAD)
		case DCM_UDT_DOWNLOAD_STATE:
			HandleTransferDownload(Instance);
			break;
		#endif
		default:
			SendNRC(Instance, DCM_E_REQUEST_SEQUENCE_ERROR);
			break;
	}
}
#endif

#if defined(DCM_USE_SERVICE_REQUEST_TRANSFER_EXIT)
static void HandleRequestTransferExit(PduIdType Instance)
{
	Dcm_NegativeResponseCodeType responseCode = DCM_E_POSITIVE_RESPONSE;
	if(1 == DCM_RTE.rxPduLength)
	{
		if( (DCM_UDT_IDLE_STATE != DCM_RTE.UDTData.state)
			/* && (0u == DCM_RTE.UDTData.memorySize) */)
		{
			memset(&DCM_RTE.UDTData,0u,sizeof(DCM_RTE.UDTData)); /* Exit */
			SendPRC(Instance);
		}
		else
		{
			SendNRC(Instance, DCM_E_REQUEST_SEQUENCE_ERROR);
		}
	}
	else
	{
		SendNRC(Instance, DCM_E_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
	}
}
#endif

static boolean CheckSessionSecurity(PduIdType Instance)
{
	uint8 index;
	uint8 index2;
	boolean bPassCheck = TRUE;

	index = u8IndexOfList(DCM_RTE.currentSession, DCM_SESSION_LIST);
	if((uint8)DCM_EOL == index)
	{ /* FATAL ERROR */
		SendNRC(Instance, DCM_E_CONDITIONS_NOT_CORRECT);
		bPassCheck = FALSE;
	}
	else
	{
		index = u8IndexOfList(DCM_RTE.currentSID, DCM_SERVICE_LIST_IN_SESSION[index]);
		if((uint8)DCM_EOL == index)
		{
			SendNRC(Instance, DCM_E_SERVICE_NOT_SUPPORTED);
			bPassCheck = FALSE;
		}
		else
		{
			bPassCheck = FALSE;	/* by default, assume this currentSID can run in any security level */
			for(index=0; (DCM_SECURITY_LEVEL_LIST[index] != (uint8)DCM_EOL); index++)
			{
				index2 = u8IndexOfList(DCM_RTE.currentSID, DCM_SERVICE_LIST_IN_LEVEL[index]);
				if((uint8)DCM_EOL != index2)
				{	/* This currentSID hit in one of the level List, need security check */
					bPassCheck = TRUE;
					break;
				}
			}

			if(bPassCheck)
			{	/* Need security check */
				index = u8IndexOfList(DCM_RTE.currentLevel, DCM_SECURITY_LEVEL_LIST);
				if((uint8)DCM_EOL == index)
				{
					SendNRC(Instance, DCM_E_SECUTITY_ACCESS_DENIED);
					bPassCheck = FALSE;
				}
				else
				{
					index = u8IndexOfList(DCM_RTE.currentSID, DCM_SERVICE_LIST_IN_LEVEL[index]);
					if((uint8)DCM_EOL == index)
					{
						SendNRC(Instance, DCM_E_SECUTITY_ACCESS_DENIED);
						bPassCheck = FALSE;
					}
				}
			}
			else
			{
				bPassCheck = TRUE;	/* service can run any level */
			}
		}
	}

	return bPassCheck;
}

static void HandleRequest(PduIdType Instance)
{
	boolean bPassCheck = TRUE;
	DCM_RTE.currentSID = DCM_RXSDU_DATA[0];

	ASLOG(DCM, "Service %02X, L=%d\n", DCM_RTE.currentSID, DCM_RTE.rxPduLength);

	DCM_RTE.counter ++;
	DCM_RTE.txPduLength = 0;
	DCM_RTE.supressPositiveResponse = FALSE;
	dcmSetAlarm(S3Server,DCM_S3SERVER_TIMEOUT_MS);
	dcmSetAlarm(P2Server,DCM_P2SERVER_TIMEOUT_MS);

	bPassCheck = CheckSessionSecurity(Instance);

	if(bPassCheck)
	{
		switch(DCM_RTE.currentSID)
		{
			case SID_DIAGNOSTIC_SESSION_CONTROL:
				HandleSessionControl(Instance);
				break;
			case SID_SECURITY_ACCESS:
				HandleSecurityAccess(Instance);
				break;
			#if defined(DCM_USE_SERVICE_ROUTINE_CONTROL)
			case SID_ROUTINE_CONTROL:
				HandleRoutineControl(Instance);
				break;
			#endif
			#if defined(DCM_USE_SERVICE_REQUEST_DOWNLOAD)
			case SID_REQUEST_DOWNLOAD:
				HandleRequestDownloadOrUpload(Instance, DCM_UDT_DOWNLOAD_STATE);
				break;
			#endif
			#if defined(DCM_USE_SERVICE_REQUEST_UPLOAD)
			case SID_REQUEST_UPLOAD:
				HandleRequestDownloadOrUpload(Instance, DCM_UDT_UPLOAD_STATE);
				break;
			#endif
			#if defined(DCM_USE_SERVICE_TRANSFER_DATA)
			case SID_TRANSFER_DATA:
				HandleTransferData(Instance);
				break;
			#endif
			#if defined(DCM_USE_SERVICE_REQUEST_TRANSFER_EXIT)
			case SID_REQUEST_TRANSFER_EXIT:
				HandleRequestTransferExit(Instance);
				break;
			#endif
			default:
				SendNRC(Instance, DCM_E_SERVICE_NOT_SUPPORTED);
				break;
		}
	}
}

static void HandleTransmit(PduIdType Instance)
{
	Std_ReturnType ercd;
	PduInfoType pdu;

	pdu.SduLength = DCM_RTE.txPduLength;
	pdu.SduDataPtr = DCM_TXSDU_DATA;
	ercd = CanTp_Transmit(Instance+DCM_INSTANCE_NUM, &pdu);

	if(E_OK == ercd)
	{
		/* nothing */
	}
}

static void SendNRC(PduIdType Instance, uint8 nrc) /* send Negative Response Code */
{
	if(DCM_BUFFER_IDLE == DCM_RTE.txPduState)
	{
		DCM_RTE.rxPduState = DCM_BUFFER_IDLE;

		DCM_TXSDU_DATA[0] = SID_NEGATIVE_RESPONSE;
		DCM_TXSDU_DATA[1] = DCM_RTE.currentSID;
		DCM_TXSDU_DATA[2] = nrc;
		DCM_RTE.txPduLength = 3;
		DCM_RTE.txPduState = DCM_BUFFER_FULL;


		HandleTransmit(Instance);

		if(DCM_E_RESPONSE_PENDING != nrc)
		{
			dcmCancelAlarm(P2Server);
			DCM_RTE.counter = 0;
		}
		else
		{
			dcmSetAlarm(P2Server,DCM_P2SERVER_TIMEOUT_MS);
		}
	}
}

static void SendPRC(PduIdType Instance)
{ /* send Positive Response Code */
	if(DCM_BUFFER_IDLE == DCM_RTE.txPduState)
	{
		DCM_RTE.rxPduState = DCM_BUFFER_IDLE;
		DCM_RTE.counter = 0;
		if(FALSE == DCM_RTE.supressPositiveResponse)
		{
			DCM_TXSDU_DATA[0] = DCM_RTE.currentSID | SID_RESPONSE_BIT;
			DCM_RTE.txPduLength += 1;
			DCM_RTE.txPduState = DCM_BUFFER_FULL;
		}

		HandleTransmit(Instance);

		dcmCancelAlarm(P2Server);
	}
}
/* ============================ [ FUNCTIONS ] ====================================================== */
void Dcm_Init(void)
{
	PduIdType Instance;
	for(Instance=0; Instance<DCM_INSTANCE_NUM; Instance++)
	{
		memset(&DCM_RTE, 0, sizeof(DCM_RTE));
		DCM_RTE.parameter = dcmInstanceDefaultParameter;
		DCM_RTE.currentSession = DCM_DEFAULT_SESSION;
	}
}

void Dcm_SetParameter(PduIdType Instance, const Dcm_ParameterType* parameter)
{
	asAssert(Instance < DCM_INSTANCE_NUM);
	DCM_RTE.parameter = parameter;
}

void Dcm_AppendTX(PduIdType Instance, uint8 v)
{
	DCM_TXSDU_DATA[1+DCM_RTE.txPduLength] = v;
	DCM_RTE.txPduLength ++;
}

void Dcm_RxIndication(PduIdType Instance, NotifResultType result)
{
	asAssert(Instance < DCM_INSTANCE_NUM);

	if(result == NTFRSLT_OK)
	{
		DCM_RTE.rxPduState = DCM_BUFFER_FULL;
	}
	else
	{
		DCM_RTE.rxPduState = DCM_BUFFER_IDLE;
	}
}

void Dcm_TxConfirmation(PduIdType Instance, NotifResultType result)
{
	asAssert(Instance < DCM_INSTANCE_NUM);

	if(result == NTFRSLT_OK)
	{

	}
	else
	{

	}

	DCM_RTE.txPduState = DCM_BUFFER_IDLE;
}

BufReq_ReturnType Dcm_ProvideRxBuffer(PduIdType Instance, PduLengthType tpSduLength, PduInfoType **pduInfoPtr)
{
	BufReq_ReturnType ret = BUFREQ_OK;

	asAssert(Instance < DCM_INSTANCE_NUM);

	if(DCM_BUFFER_IDLE != DCM_RTE.rxPduState)
	{
		ret = BUFREQ_E_BUSY;
	}
	else if(NULL == pduInfoPtr)
	{
		ret = BUFREQ_E_NOT_OK;
	}
	else if((tpSduLength > DCM_RXSDU_SIZE) || (0 == tpSduLength))
	{
		ret = BUFREQ_E_OVFL;
	}
	else
	{
		*pduInfoPtr = (PduInfoType *)DCM_RXSDU;
		DCM_RTE.rxPduLength = tpSduLength;
		DCM_RTE.rxPduState = DCM_BUFFER_PROVIDED;
	}

	return ret;
}

BufReq_ReturnType Dcm_ProvideTxBuffer(PduIdType Instance, PduInfoType **pduInfoPtr, PduLengthType length)
{
	BufReq_ReturnType ret = BUFREQ_OK;

	asAssert(Instance < DCM_INSTANCE_NUM);

	if(DCM_BUFFER_FULL != DCM_RTE.txPduState)
	{
		ret = BUFREQ_E_BUSY;
	}
	else if(NULL == pduInfoPtr)
	{
		ret = BUFREQ_E_NOT_OK;
	}
	else if((length > DCM_TXSDU_SIZE) || (0 == length))
	{
		ret = BUFREQ_E_OVFL;
	}
	else
	{
		*pduInfoPtr = (PduInfoType *)DCM_TXSDU;
		DCM_RTE.txPduState = DCM_BUFFER_PROVIDED;
	}
	return ret;
}

void Dcm_MainFunction(void)
{
	PduIdType Instance;
	const Dcm_ParameterType* parameter;
	for(Instance=0; Instance<DCM_INSTANCE_NUM; Instance++)
	{
		if( (DCM_BUFFER_FULL == DCM_RTE.rxPduState) &&
			(DCM_BUFFER_IDLE == DCM_RTE.txPduState))
		{
			HandleRequest(Instance);
		}

		if(DCM_BUFFER_FULL == DCM_RTE.txPduState)
		{
			HandleTransmit(Instance);
		}

		if(dcmIsAlarmStarted(P2Server))
		{
			dcmSignalAlarm(P2Server);
			if(dcmIsAlarmTimeout(P2Server))
			{
				SendNRC(Instance, DCM_E_RESPONSE_PENDING);
			}
		}

		if(dcmIsAlarmStarted(S3Server))
		{
			dcmSignalAlarm(S3Server);
			if(dcmIsAlarmTimeout(S3Server))
			{
				parameter = DCM_RTE.parameter;
				memset(&DCM_RTE, 0, sizeof(DCM_RTE));
				DCM_RTE.parameter = parameter;
				DCM_RTE.currentSession = DCM_DEFAULT_SESSION;
				ASLOG(STDOUT,"S3Server Timeout!\n");
			}
		}
	}
}

Std_ReturnType Dcm_GetSecurityLevel(Dcm_SecLevelType *secLevel)
{
	Std_ReturnType ercd = E_NOT_OK;
	PduIdType Instance;

	*secLevel = 0;
	for(Instance=0; Instance<DCM_INSTANCE_NUM; Instance++)
	{
		if(DCM_BUFFER_FULL == DCM_RTE.rxPduState)
		{	/* This is active instance */
			*secLevel = DCM_RTE.currentLevel;
			ercd = E_OK;
			break;
		}
	}

	return ercd;
}
