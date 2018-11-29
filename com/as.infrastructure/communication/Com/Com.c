/* -------------------------------- Arctic Core ------------------------------
 * Arctic Core - the open source AUTOSAR platform http://arccore.com
 *
 * Copyright (C) 2009  ArcCore AB <contact@arccore.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * -------------------------------- Arctic Core ------------------------------*/


//lint -esym(960,8.7)	PC-Lint misunderstanding of Misra 8.7 for Com_SystenEndianness and endianess_test
#ifdef USE_COM

#include <stdlib.h>
//#include <stdio.h>
#include <string.h>
#include "Com.h"
#include "Com_Arc_Types.h"
#include "Com_Internal.h"
#include "Com_misc.h"
#include "asdebug.h"

#ifdef USE_SHELL
#include "shell.h"

static int cmdComLsSgFunc(int argc, char *argv[]);
static int cmdComWrSgFunc(int argc, char *argv[]);

static SHELL_CONST ShellCmdT cmdComLsSg  = {
		cmdComLsSgFunc,
		0,1,
		"lssg",
		"lssg",
		"list all the value of com signals\n",
		{NULL,NULL}
};
SHELL_CMD_EXPORT(cmdComLsSg)

static SHELL_CONST ShellCmdT cmdComWrSg  = {
		cmdComWrSgFunc,
		2,3,
		"wrsg",
		"wrsg sid value [gid]",
		"write signal, if sid is group signals, need the gid\n",
		{NULL,NULL}
};
SHELL_CMD_EXPORT(cmdComWrSg)

static void ListSignal(void) {
	union {
		uint32 u32V;
		uint16 u16V;
		uint8  u8V;
	} uV;
	for (uint16 pduId = 0; !ComConfig->ComIPdu[pduId].Com_Arc_EOL; pduId++) {
		const ComIPdu_type *IPdu = GET_IPdu(pduId);
		imask_t irq_state;
		Irq_Save(irq_state);
		for (uint16 i = 0; (IPdu->ComIPduSignalRef != NULL) && (IPdu->ComIPduSignalRef[i] != NULL); i++) {
			const ComSignal_type *signal = IPdu->ComIPduSignalRef[i];

			if(FALSE == signal->Com_Arc_IsSignalGroup)
			{
				switch(signal->ComSignalType)
				{
					case COM_SIGNAL_TYPE_UINT8:
					case COM_SIGNAL_TYPE_SINT8:
						(void)Com_ReceiveSignal(signal->ComHandleId, &uV.u8V);
						SHELL_printf("%s.%s(SID=%d): V = 0x%02X(%d)\n",
								IPdu->name, signal->name, signal->ComHandleId, uV.u8V, uV.u8V);
						break;
					case COM_SIGNAL_TYPE_UINT16:
					case COM_SIGNAL_TYPE_SINT16:
						(void)Com_ReceiveSignal(signal->ComHandleId, &uV.u16V);
						SHELL_printf("%s.%s(SID=%d): V = 0x%04X(%d)\n",
								IPdu->name, signal->name, signal->ComHandleId, uV.u16V, uV.u16V);
						break;
					case COM_SIGNAL_TYPE_UINT32:
					case COM_SIGNAL_TYPE_SINT32:
						(void)Com_ReceiveSignal(signal->ComHandleId, &uV.u32V);
						SHELL_printf("%s.%s(SID=%d): V = 0x%08X(%d)\n",
								IPdu->name, signal->name, signal->ComHandleId, uV.u32V, uV.u32V);
						break;
					default:
						SHELL_printf("%s.%s(SID=%d): unsupported type %d(%d)\n",
								IPdu->name, signal->name, signal->ComHandleId, signal->ComSignalType);
						break;
				}
			}
			else
			{
				for (uint16 j = 0; (signal->ComGroupSignal != NULL) && (signal->ComGroupSignal[j] != NULL); j++) {
					const ComGroupSignal_type *gsignal = signal->ComGroupSignal[j];
					(void)Com_ReceiveSignalGroup(signal->ComHandleId);
					switch(gsignal->ComSignalType)
					{
						case COM_SIGNAL_TYPE_UINT8:
						case COM_SIGNAL_TYPE_SINT8:
							(void)Com_ReceiveShadowSignal(gsignal->ComHandleId, &uV.u8V);
							SHELL_printf("%s.%s.%s(SID=%d,GID=%d): V = 0x%02X(%d)\n",
									IPdu->name, signal->name, gsignal->name,
									signal->ComHandleId, gsignal->ComHandleId,
									uV.u8V, uV.u8V);
							break;
						case COM_SIGNAL_TYPE_UINT16:
						case COM_SIGNAL_TYPE_SINT16:
							(void)Com_ReceiveShadowSignal(gsignal->ComHandleId, &uV.u16V);
							SHELL_printf("%s.%s.%s(SID=%d,GID=%d): V = 0x%04X(%d)\n",
									IPdu->name, signal->name, gsignal->name,
									signal->ComHandleId, gsignal->ComHandleId,
									uV.u16V, uV.u16V);
							break;
						case COM_SIGNAL_TYPE_UINT32:
						case COM_SIGNAL_TYPE_SINT32:
							(void)Com_ReceiveShadowSignal(gsignal->ComHandleId, &uV.u32V);
							SHELL_printf("%s.%s.%s(SID=%d,GID=%d): V = 0x%08X(%d)\n",
									IPdu->name, signal->name, gsignal->name,
									signal->ComHandleId, gsignal->ComHandleId,
									uV.u32V, uV.u32V);
							break;
						default:
							SHELL_printf("%s.%s.%s(SID=%d,GID=%d): unsupported type %d\n",
									IPdu->name, signal->name, gsignal->name,
									signal->ComHandleId, gsignal->ComHandleId,
									gsignal->ComSignalType);
							break;
					}
				}
			}
		}
		Irq_Restore(irq_state);
	}
}
static int cmdComLsSgFunc(int argc, char *argv[] ) {
	int rv = 0;
	ListSignal();
	return rv;
}

static int cmdComWrSgFunc(int argc, char *argv[])
{
	int rv = 0;
	uint16 sid,gid;
	uint32 u32V;
	union {
		uint32 u32V;
		uint16 u16V;
		uint8  u8V;
	} uV;
	const ComSignal_type * signal;
	const ComGroupSignal_type *gsignal;

	sid = strtoul(argv[1],NULL, 10);
	u32V = strtoul(argv[2],NULL, 16);
	signal = GET_Signal(sid);
	if(FALSE == signal->Com_Arc_IsSignalGroup)
	{
		switch(signal->ComSignalType)
		{
			case COM_SIGNAL_TYPE_UINT8:
			case COM_SIGNAL_TYPE_SINT8:
				uV.u8V = (uint8)u32V;
				(void)Com_SendSignal(signal->ComHandleId, &uV.u8V);
				break;
			case COM_SIGNAL_TYPE_UINT16:
			case COM_SIGNAL_TYPE_SINT16:
				uV.u16V = (uint16)u32V;
				(void)Com_SendSignal(signal->ComHandleId, &uV.u16V);
				break;
			case COM_SIGNAL_TYPE_UINT32:
			case COM_SIGNAL_TYPE_SINT32:
				uV.u32V = (uint32)u32V;
				(void)Com_SendSignal(signal->ComHandleId, &uV.u32V);
				break;
			default:
				break;
		}
	}
	else
	{
		gid = strtoul(argv[3],NULL, 10);
		gsignal = signal->ComGroupSignal[gid];
		switch(gsignal->ComSignalType)
		{
			case COM_SIGNAL_TYPE_UINT8:
			case COM_SIGNAL_TYPE_SINT8:
				uV.u8V = (uint8)u32V;
				(void)Com_UpdateShadowSignal(gsignal->ComHandleId, &uV.u8V);
				break;
			case COM_SIGNAL_TYPE_UINT16:
			case COM_SIGNAL_TYPE_SINT16:
				uV.u16V = (uint16)u32V;
				(void)Com_UpdateShadowSignal(gsignal->ComHandleId, &uV.u16V);
				break;
			case COM_SIGNAL_TYPE_UINT32:
			case COM_SIGNAL_TYPE_SINT32:
				uV.u32V = (uint32)u32V;
				(void)Com_UpdateShadowSignal(gsignal->ComHandleId, &uV.u32V);
				break;
			default:
				break;
		}
		Com_SendSignalGroup(signal->ComHandleId);
	}

	return 0;
}
#endif

/* TODO: Better way to get endianness across all compilers? */
static const uint32_t endianness_test = 0xdeadbeefU;
ComSignalEndianess_type Com_SystemEndianness;


const Com_ConfigType * ComConfig;


void Com_Init(const Com_ConfigType *config ) {
	uint32 firstTimeout;

	//lint --e(928)	PC-Lint exception Misra 11.4, Must be like this. /tojo
	uint8 endiannessByte = *(const uint8 *)&endianness_test;

#if !defined(USE_SHELL_SYMTAB) && defined(USE_SHELL)
	SHELL_AddCmd(&cmdComLsSg);
	SHELL_AddCmd(&cmdComWrSg);
#endif
	ComConfig = config;
	if      ( endiannessByte == 0xef ) { Com_SystemEndianness = COM_LITTLE_ENDIAN; }
	else if ( endiannessByte == 0xde ) { Com_SystemEndianness = COM_BIG_ENDIAN; }
	else {
		// No other endianness supported
		//lint --e(506)	PC-Lint exception Misra 13.7, 14.1, Allow boolean to always be false.
		asAssert(0);
	}

	// Initialize each IPdu
	//ComIPdu_type *IPdu;
	//Com_Arc_IPdu_type *Arc_IPdu;
	const ComSignal_type *Signal;
	const ComGroupSignal_type *GroupSignal;
	for (uint16 i = 0; !ComConfig->ComIPdu[i].Com_Arc_EOL; i++) {

		const ComIPdu_type *IPdu = GET_IPdu(i);
		Com_Arc_IPdu_type *Arc_IPdu = GET_ArcIPdu(i);
		Arc_IPdu->Com_Arc_DynSignalLength = 0;

		if (i >= COM_N_IPDUS) {
			DET_REPORTERROR(COM_MODULE_ID, COM_INSTANCE_ID, 0x01, COM_E_TOO_MANY_IPDU);
			break;
		}

		// If this is a TX and cyclic IPdu, configure the first deadline.
		if ( (IPdu->ComIPduDirection == COM_SEND) &&
				( (IPdu->ComTxIPdu.ComTxModeTrue.ComTxModeMode == COM_PERIODIC) || (IPdu->ComTxIPdu.ComTxModeTrue.ComTxModeMode == COM_MIXED) )) {
			//IPdu->Com_Arc_TxIPduTimers.ComTxModeTimePeriodTimer = IPdu->ComTxIPdu.ComTxModeTrue.ComTxModeTimeOffsetFactor;
			Arc_IPdu->Com_Arc_TxIPduTimers.ComTxModeTimePeriodTimer = IPdu->ComTxIPdu.ComTxModeTrue.ComTxModeTimeOffsetFactor;
		}


		// Reset firstTimeout.
		firstTimeout = 0xffffffffu;

		// Initialize the memory with the default value.
		if (IPdu->ComIPduDirection == COM_SEND) {
			memset((void *)IPdu->ComIPduDataPtr, IPdu->ComTxIPdu.ComTxIPduUnusedAreasDefault, IPdu->ComIPduSize);
		}

		// For each signal in this PDU.
		//Arc_IPdu->NComIPduSignalRef = 0;
		for (uint16 j = 0; (IPdu->ComIPduSignalRef != NULL) && (IPdu->ComIPduSignalRef[j] != NULL) ; j++) {
			Signal = IPdu->ComIPduSignalRef[j];
			Com_Arc_Signal_type * Arc_Signal = GET_ArcSignal(Signal->ComHandleId);

			// Configure signal deadline monitoring if used.
			if ((COM_RECEIVE == IPdu->ComIPduDirection) && (Signal->ComTimeoutFactor > 0)) {

				if (Signal->ComSignalArcUseUpdateBit) {
					// This signal uses an update bit, and hence has its own deadline monitoring.
					Arc_Signal->Com_Arc_DeadlineCounter = Signal->ComFirstTimeoutFactor; // Configure the deadline counter

				} else {
					// This signal does not use an update bit, and should therefore use per I-PDU deadline monitoring.
					if (firstTimeout > Signal->ComFirstTimeoutFactor) {
						firstTimeout = Signal->ComFirstTimeoutFactor;
					}
				}
			}

			// Clear update bits
			if (Signal->ComSignalArcUseUpdateBit) {
				CLEARBIT(IPdu->ComIPduDataPtr, Signal->ComUpdateBitPosition);
			}

			// If this signal is a signal group
			if (Signal->Com_Arc_IsSignalGroup) {

				// For each group signal of this signal group.
				for(uint8 h = 0; Signal->ComGroupSignal[h] != NULL; h++) {
					GroupSignal = Signal->ComGroupSignal[h];
					Com_Arc_GroupSignal_type *Arc_GroupSignal = GET_ArcGroupSignal(GroupSignal->ComHandleId);
					// Set pointer to shadow buffer
					Arc_GroupSignal->Com_Arc_ShadowBuffer = (void *)Signal->Com_Arc_ShadowBuffer;
					// Initialize shadowbuffer.
					Com_UpdateShadowSignal(GroupSignal->ComHandleId, GroupSignal->ComSignalInitValue);
				}
				// Initialize group signal data from shadowbuffer.
				Com_CopySignalGroupDataFromShadowBufferToPdu(Signal->ComHandleId);
			} else {
				// Initialize signal data.
				Com_WriteSignalDataToPdu(Signal->ComHandleId, Signal->ComSignalInitValue);
			}
		}
		if ((IPdu->ComIPduDirection == COM_RECEIVE) && (IPdu->ComIPduSignalProcessing == COM_DEFERRED)) {
			// Copy the initialized pdu to deferred buffer
			memcpy(IPdu->ComIPduDeferredDataPtr,IPdu->ComIPduDataPtr,IPdu->ComIPduSize);
		}
		// Configure per I-PDU based deadline monitoring.
		for (uint16 j = 0; (COM_RECEIVE == IPdu->ComIPduDirection) && (IPdu->ComIPduSignalRef != NULL) && (IPdu->ComIPduSignalRef[j] != NULL); j++) {
			Signal = IPdu->ComIPduSignalRef[j];
			Com_Arc_Signal_type * Arc_Signal = GET_ArcSignal(Signal->ComHandleId);

			if ( (Signal->ComTimeoutFactor > 0) && (!Signal->ComSignalArcUseUpdateBit) ) {
				Arc_Signal->Com_Arc_DeadlineCounter = firstTimeout;
			}
		}
	}
	for (uint16 i = 0; i < COM_N_IPDUS; i++) {
		Com_BufferPduState[i].currentPosition = 0;
		Com_BufferPduState[i].locked = false;
	}
}


void Com_DeInit( void ) {

}

void Com_IpduGroupStart(Com_PduGroupIdType IpduGroupId,boolean Initialize) {
	(void)Initialize; // Nothing to be done. This is just to avoid Lint warning.
	for (uint16 i = 0; !ComConfig->ComIPdu[i].Com_Arc_EOL; i++) {
		if (ComConfig->ComIPdu[i].ComIPduGroupRef == IpduGroupId) {
			Com_Arc_Config.ComIPdu[i].Com_Arc_IpduStarted = 1;
		}
	}
}

void Com_IpduGroupStop(Com_PduGroupIdType IpduGroupId) {
	for (uint16 i = 0; !ComConfig->ComIPdu[i].Com_Arc_EOL; i++) {
		if (ComConfig->ComIPdu[i].ComIPduGroupRef == IpduGroupId) {
			Com_Arc_Config.ComIPdu[i].Com_Arc_IpduStarted = 0;
		}
	}
}

/**
 *
 * @param PduId
 * @param PduInfoPtr
 * @param RetryInfoPtr not supported
 * @param TxDataCntPtr
 * @return
 */
BufReq_ReturnType Com_CopyTxData(PduIdType PduId, PduInfoType* PduInfoPtr, RetryInfoType* RetryInfoPtr, PduLengthType* TxDataCntPtr) {
	imask_t state;
	BufReq_ReturnType r = BUFREQ_OK;
	const ComIPdu_type *IPdu = GET_IPdu(PduId);
	boolean dirOk = ComConfig->ComIPdu[PduId].ComIPduDirection == COM_SEND;
	boolean sizeOk;
	(void)RetryInfoPtr; // get rid of compiler warning

	Irq_Save(state);
	sizeOk = IPdu->ComIPduSize >= Com_BufferPduState[PduId].currentPosition + PduInfoPtr->SduLength;
	Com_BufferPduState[PduId].locked = true;
	if (dirOk && sizeOk) {
		void* source = (void *)IPdu->ComIPduDataPtr;
		memcpy(PduInfoPtr->SduDataPtr,(uint8 *)source + Com_BufferPduState[PduId].currentPosition, PduInfoPtr->SduLength);
		Com_BufferPduState[PduId].currentPosition += PduInfoPtr->SduLength;
		*TxDataCntPtr = IPdu->ComIPduSize - Com_BufferPduState[PduId].currentPosition;
	} else {
		r = BUFREQ_NOT_OK;
	}
	Irq_Restore(state);
	return r;
}
BufReq_ReturnType Com_CopyRxData(PduIdType PduId, const PduInfoType* PduInfoPtr, PduLengthType* RxBufferSizePtr) {
	imask_t state;
	BufReq_ReturnType r = BUFREQ_OK;
	uint8 remainingBytes;
	boolean sizeOk;
	boolean dirOk;
	boolean lockOk;

	Irq_Save(state);

	remainingBytes = GET_IPdu(PduId)->ComIPduSize - Com_BufferPduState[PduId].currentPosition;
	sizeOk = remainingBytes >= PduInfoPtr->SduLength;
    dirOk = GET_IPdu(PduId)->ComIPduDirection == COM_RECEIVE;
	lockOk = isPduBufferLocked(PduId);
	if (dirOk && lockOk && sizeOk) {
		memcpy((void *)((uint8 *)GET_IPdu(PduId)->ComIPduDataPtr+Com_BufferPduState[PduId].currentPosition), PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
		Com_BufferPduState[PduId].currentPosition += PduInfoPtr->SduLength;
		*RxBufferSizePtr = GET_IPdu(PduId)->ComIPduSize - Com_BufferPduState[PduId].currentPosition;
	} else {
		r = BUFREQ_NOT_OK;
	}
	Irq_Restore(state);
	return r;
}

static void Com_SetDynSignalLength(PduIdType ComRxPduId,PduLengthType TpSduLength) {
	const ComIPdu_type *IPdu = GET_IPdu(ComRxPduId);
	if (IPdu->ComIPduDynSignalRef == 0) {
		return;
	}
	const ComSignal_type * const dynSignal = IPdu->ComIPduDynSignalRef;
	Com_Arc_IPdu_type *Arc_IPdu = GET_ArcIPdu(ComRxPduId);
	Arc_IPdu->Com_Arc_DynSignalLength = TpSduLength - (dynSignal->ComBitPosition/8);
	return;
}

BufReq_ReturnType Com_StartOfReception(PduIdType ComRxPduId, PduLengthType TpSduLength, PduLengthType* RxBufferSizePtr) {
	PduLengthType ComIPduSize;
	imask_t state;
	BufReq_ReturnType r = BUFREQ_OK;
	Com_Arc_IPdu_type *Arc_IPdu = GET_ArcIPdu(ComRxPduId);

	Irq_Save(state);
	if (Arc_IPdu->Com_Arc_IpduStarted) {
		if (GET_IPdu(ComRxPduId)->ComIPduDirection == COM_RECEIVE) {
			if (!Com_BufferPduState[ComRxPduId].locked) {
				ComIPduSize = GET_IPdu(ComRxPduId)->ComIPduSize;
				if (ComIPduSize >= TpSduLength) {
					Com_BufferPduState[ComRxPduId].locked = true;
					*RxBufferSizePtr = ComIPduSize;
					Com_SetDynSignalLength(ComRxPduId,TpSduLength);
				} else {
					r = BUFREQ_OVFL;
				}
			} else {
				r = BUFREQ_BUSY;
			}
		}
	} else {
		r = BUFREQ_NOT_OK;
	}
	Irq_Restore(state);
	return r;
}
#endif /* USE_COM */
