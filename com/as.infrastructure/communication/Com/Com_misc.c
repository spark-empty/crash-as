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
#include <string.h>

#include "Com_Arc_Types.h"
#include "Com.h"
#include "Com_Internal.h"
#include "Com_misc.h"
#include "asdebug.h"

/* sync from https://github.com/z2akhtar/PWC-Demonstrator/blob/master/AUTOSAR/core/communication/Com/Com_misc.c */
static void Com_Internal_ReadSignalDataFromPdu (
		const uint8 *comIPduDataPtr,
		Com_BitPositionType bitPosition,
		uint16 bitSize,
		ComSignalEndianess_type endian,
		Com_SignalType signalType,
		uint8 *SignalData) {
	imask_t state;
	Irq_Save(state);

	if (endian == COM_OPAQUE || signalType == COM_SIGNAL_TYPE_UINT8_N) {
		// Aligned opaque data -> straight copy
		/* @req COM472 */
		memcpy(SignalData, comIPduDataPtr + bitPosition/8, bitSize / 8);
		Irq_Restore(state);
	} else {
		// Unaligned data and/or endianness conversion
		uint32 pduData;
		if(endian == COM_BIG_ENDIAN) {
			uint32 lsbIndex = ((bitPosition ^ 0x7) + bitSize - 1) ^ 7; // calculate lsb bit index. This could be moved to generator
			const uint8 *pduDataPtr = comIPduDataPtr + lsbIndex / 8 - 3; // calculate big endian ptr to data
			uint8 bitShift = lsbIndex % 8;
			pduData = 0;
			for(uint32 i = 0; i < 4; i++) {
				pduData = (pduData << 8) | pduDataPtr[i];
			}
			pduData >>= bitShift;
			if(32 - bitShift < bitSize) {
				pduData |= pduDataPtr[-1] << (32 - bitShift);
			}
		} else if (endian == COM_LITTLE_ENDIAN) {
			uint32 lsbIndex = bitPosition;
			const uint8 *pduDataPtr = comIPduDataPtr + (bitPosition/8);
			uint8 bitShift = lsbIndex % 8;
			pduData = 0;
			for(sint32 i = 3; i >= 0; i--) {
				pduData = (pduData << 8) | pduDataPtr[i];
			}
			pduData >>= bitShift;
			if(32 - bitShift < bitSize) {
				pduData |= pduDataPtr[4] << (32 - bitShift);
			}
		} else {
			asAssert(0);
		}
		Irq_Restore(state);
		uint32 mask = 0xFFFFFFFFu >> (32 - bitSize); // calculate mask for SigVal
		pduData &= mask; // clear bit out of range
		uint32 signmask = ~(mask >> 1);
		switch(signalType) {
		case COM_SIGNAL_TYPE_SINT8:
			if(pduData & signmask) {
				pduData |= signmask; // add sign bits
			}
			// no break, sign extended data can be written as uint
		case COM_SIGNAL_TYPE_BOOLEAN:
		case COM_SIGNAL_TYPE_UINT8:
			*(uint8*)SignalData = pduData;
			break;
		case COM_SIGNAL_TYPE_SINT16:
			if(pduData & signmask) {
				pduData |= signmask; // add sign bits
			}
			// no break, sign extended data can be written as uint
		case COM_SIGNAL_TYPE_UINT16:
			*(uint16*)SignalData = pduData;
			break;
		case COM_SIGNAL_TYPE_SINT32:
			if(pduData & signmask) {
				pduData |= signmask; // add sign bits
			}
			// no break, sign extended data can be written as uint
		case COM_SIGNAL_TYPE_UINT32:
			*(uint32*)SignalData = pduData;
			break;
		case COM_SIGNAL_TYPE_UINT8_N:
		case COM_SIGNAL_TYPE_UINT8_DYN:
			asAssert(0);
		}
	}
}

static void Com_Internal_WriteSignalDataToPdu(
		const uint8 *SignalDataPtr,
		Com_SignalType signalType,
		uint8 *comIPduDataPtr,
		Com_BitPositionType bitPosition,
		uint16 bitSize,
		ComSignalEndianess_type endian,
		boolean *dataChanged) {
	imask_t irq_state;
	if (endian == COM_OPAQUE || signalType == COM_SIGNAL_TYPE_UINT8_N) {
		/* @req COM472 */
		uint8 *pduBufferBytes = (uint8 *)comIPduDataPtr + bitPosition / 8;
		uint16 signalLength = bitSize / 8;
		Irq_Save(irq_state);
		if(NULL != dataChanged) {
			*dataChanged = ( 0 != memcmp(pduBufferBytes, SignalDataPtr, signalLength) );
		}
		memcpy(pduBufferBytes, SignalDataPtr, signalLength);
	} else {
		uint32 sigVal = 0;
		switch(signalType) {
		case COM_SIGNAL_TYPE_BOOLEAN:
		case COM_SIGNAL_TYPE_UINT8:
		case COM_SIGNAL_TYPE_SINT8:
			sigVal = *((uint8*)SignalDataPtr);
			break;
		case COM_SIGNAL_TYPE_UINT16:
		case COM_SIGNAL_TYPE_SINT16:
			sigVal = *((uint16*)SignalDataPtr);
			break;
		case COM_SIGNAL_TYPE_UINT32:
		case COM_SIGNAL_TYPE_SINT32:
			sigVal = *((uint32*)SignalDataPtr);
			break;
		case COM_SIGNAL_TYPE_UINT8_N:
		case COM_SIGNAL_TYPE_UINT8_DYN:
			asAssert(0);
		}
		uint32 mask = 0xFFFFFFFFu >> (32 - bitSize); // calculate mask for SigVal
		sigVal &= mask; // mask sigVal;
		Irq_Save(irq_state);
		if(endian == COM_BIG_ENDIAN) {
			uint32 lsbIndex = ((bitPosition ^ 0x7) + bitSize - 1) ^ 7; // calculate lsb bit index. This could be moved to generator
			uint8 *pduDataPtr = (comIPduDataPtr + lsbIndex / 8 - 3); // calculate big endian ptr to data
			uint32 pduData = 0;
			for(uint32 i = 0; i < 4; i++) {
				pduData = (pduData << 8) | pduDataPtr[i];
			}
			uint8 bitShift = lsbIndex % 8;
			uint32 sigLo = sigVal << bitShift;
			uint32 maskLo = ~(mask  << bitShift);
			uint32 newPduData = (pduData & maskLo) | sigLo;
			if(NULL != dataChanged) {
				*dataChanged = (newPduData != pduData);
			}
			for(int i = 3; i >= 0; i--) {
				pduDataPtr[i] = (uint8)newPduData;
				newPduData >>= 8;
			}
			sint8 maxBitsWritten = 32 - bitShift;
			if(maxBitsWritten < bitSize) {
				pduDataPtr--;
				pduData = *pduDataPtr;
				uint32 maskHi = ~(mask  >> maxBitsWritten);
				uint32 sigHi = sigVal >> maxBitsWritten;
				newPduData = (pduData & maskHi) | sigHi;
				if(NULL != dataChanged) {
					*dataChanged |= (newPduData != pduData) ? TRUE : *dataChanged;
				}
				*pduDataPtr = newPduData;
			}
		} else if (endian == COM_LITTLE_ENDIAN) {
			uint32 lsbIndex = bitPosition; // calculate lsb bit index.
			uint8 *pduDataPtr = (comIPduDataPtr + lsbIndex / 8); // calculate big endian ptr to data
			uint32 pduData = 0;
			for(sint32 i = 3; i >= 0; i--) {
				pduData = (pduData << 8) | pduDataPtr[i];
			}
			uint8 bitShift = lsbIndex % 8;
			uint32 sigLo = sigVal << bitShift;
			uint32 maskLo = ~(mask  << bitShift);
			uint32 newPduData = (pduData & maskLo) | sigLo;
			if(NULL != dataChanged) {
				*dataChanged = (newPduData != pduData);
			}
			for(uint32 i = 0; i < 4; i++) {
				pduDataPtr[i] = (uint8)newPduData;
				newPduData >>= 8;
			}
			sint8 maxBitsWritten = 32 - bitShift;
			if(maxBitsWritten < bitSize) {
				pduDataPtr += 4;
				pduData = *pduDataPtr;
				uint32 maskHi = ~(mask >> maxBitsWritten);
				uint32 sigHi = sigVal >> maxBitsWritten;
				newPduData = (pduData & maskHi) | sigHi;
				if(NULL != dataChanged) {
					*dataChanged = (newPduData != pduData) ? TRUE : *dataChanged;
				}
				*pduDataPtr = newPduData;
			}
		} else {
			asAssert(0);
		}
	}
	Irq_Restore(irq_state);
}

void Com_CopySignalGroupDataFromShadowBufferToPdu(const Com_SignalIdType signalGroupId) {

	// Get PDU
	const ComSignal_type * Signal = GET_Signal(signalGroupId);
	const ComIPdu_type *IPdu = GET_IPdu(Signal->ComIPduHandleId);

	uint8 *pduDataPtr = 0;
	if (IPdu->ComIPduSignalProcessing == COM_DEFERRED && IPdu->ComIPduDirection == COM_RECEIVE) {
		pduDataPtr = IPdu->ComIPduDeferredDataPtr;
	} else {
		pduDataPtr = IPdu->ComIPduDataPtr;
	}

	// Aligned opaque data -> straight copy with signalgroup mask
	uint8 *buf = (uint8 *)Signal->Com_Arc_ShadowBuffer;
	for(int i= 0; i < IPdu->ComIPduSize; i++){
		*pduDataPtr = (~Signal->Com_Arc_ShadowBuffer_Mask[i] & *pduDataPtr) |
					  (Signal->Com_Arc_ShadowBuffer_Mask[i] & *buf);
		buf++;
		pduDataPtr++;
	}

}

void Com_CopySignalGroupDataFromPduToShadowBuffer(const Com_SignalIdType signalGroupId) {

	// Get PDU
	const ComSignal_type * Signal = GET_Signal(signalGroupId);
	const ComIPdu_type *IPdu = GET_IPdu(Signal->ComIPduHandleId);

	const uint8 *pduDataPtr = 0;
	if (IPdu->ComIPduSignalProcessing == COM_DEFERRED && IPdu->ComIPduDirection == COM_RECEIVE) {
		pduDataPtr = IPdu->ComIPduDeferredDataPtr;
	} else {
		pduDataPtr = IPdu->ComIPduDataPtr;
	}

	// Aligned opaque data -> straight copy with signalgroup mask
	uint8 *buf = (uint8 *)Signal->Com_Arc_ShadowBuffer;
	for(int i= 0; i < IPdu->ComIPduSize; i++){
		*buf++ = Signal->Com_Arc_ShadowBuffer_Mask[i] & *pduDataPtr++;
	}
}

void Com_ReadSignalDataFromPduBuffer(
		const uint16 signalId,
		const boolean isGroupSignal,
		void *signalData,
		const void *pduBuffer) {

	Com_SignalType signalType;
	ComSignalEndianess_type signalEndianess;
	Com_BitPositionType bitPosition;
	uint8 bitSize;

	if (!isGroupSignal) {
		const ComSignal_type * Signal =  GET_Signal(signalId);
		signalType = Signal->ComSignalType;
		signalEndianess = Signal->ComSignalEndianess;
		bitPosition = Signal->ComBitPosition;
		bitSize = Signal->ComBitSize;
	} else {
		/* Groupsignal, we actually read from shadowbuffer */
		const ComGroupSignal_type *GroupSignal = GET_GroupSignal(signalId);
		signalType = GroupSignal->ComSignalType;
		signalEndianess = GroupSignal->ComSignalEndianess;
		bitPosition = GroupSignal->ComBitPosition;
		bitSize = GroupSignal->ComBitSize;
	}

	Com_Internal_ReadSignalDataFromPdu((const uint8 *)pduBuffer, bitPosition, bitSize,
			signalEndianess, signalType, (uint8 *)signalData);
}


void Com_WriteSignalDataToPdu(
			const Com_SignalIdType signalId,
			const void *signalData) {

	// Get PDU
	const ComSignal_type *Signal     = GET_Signal(signalId);
	const ComIPdu_type   *IPdu       = GET_IPdu(Signal->ComIPduHandleId);

	// Get data
	Com_WriteSignalDataToPduBuffer(
			signalId,
			FALSE,
			signalData,
			IPdu->ComIPduDataPtr);
}

void Com_WriteSignalDataToPduBuffer(
			const uint16 signalId,
			const boolean isGroupSignal,
			const void *signalData,
			void *pduBuffer) {

	Com_SignalType signalType;
	Com_BitPositionType bitPosition;
	uint8 bitSize;
	ComSignalEndianess_type endian;

	if (!isGroupSignal) {
		const ComSignal_type * Signal =  GET_Signal(signalId);
		signalType = Signal->ComSignalType;
		bitPosition = Signal->ComBitPosition;
		bitSize = Signal->ComBitSize;
		endian = Signal->ComSignalEndianess;
	} else {
		const ComGroupSignal_type *GroupSignal = GET_GroupSignal(signalId);
		signalType = GroupSignal->ComSignalType;
		bitPosition = GroupSignal->ComBitPosition;
		bitSize = GroupSignal->ComBitSize;
		endian = GroupSignal->ComSignalEndianess;
	}

	Com_Internal_WriteSignalDataToPdu((const uint8 *)signalData, signalType,
			(uint8 *)pduBuffer, bitPosition, bitSize, endian, NULL);
}

void Com_RxProcessSignals(const ComIPdu_type *IPdu,Com_Arc_IPdu_type *Arc_IPdu) {
	const ComSignal_type *comSignal;
	for (uint8 i = 0; IPdu->ComIPduSignalRef[i] != NULL; i++) {
		comSignal = IPdu->ComIPduSignalRef[i];
		Com_Arc_Signal_type * Arc_Signal = GET_ArcSignal(comSignal->ComHandleId);

		// If this signal uses an update bit, then it is only considered if this bit is set.
		if ( (!comSignal->ComSignalArcUseUpdateBit) ||
			( (comSignal->ComSignalArcUseUpdateBit) && (TESTBIT(IPdu->ComIPduDataPtr, comSignal->ComUpdateBitPosition)) ) ) {

			if (comSignal->ComTimeoutFactor > 0) { // If reception deadline monitoring is used.
				// Reset the deadline monitoring timer.
				Arc_Signal->Com_Arc_DeadlineCounter = comSignal->ComTimeoutFactor;
			}

			// Check the signal processing mode.
			if (IPdu->ComIPduSignalProcessing == COM_IMMEDIATE) {
				// If signal processing mode is IMMEDIATE, notify the signal callback.
				if (IPdu->ComIPduSignalRef[i]->ComNotification != NULL) {
					IPdu->ComIPduSignalRef[i]->ComNotification();
				}

			} else {
				// Signal processing mode is COM_DEFERRED, mark the signal as updated.
				Arc_Signal->ComSignalUpdated = 1;
			}

		} else {
			DEBUG(DEBUG_LOW, "Com_RxIndication: Ignored signal %d of I-PD %d since its update bit was not set\n", comSignal->ComHandleId,0x000);
		}
	}
}
void UnlockTpBuffer(PduIdType PduId) {
	Com_BufferPduState[PduId].locked = false;
	Com_BufferPduState[PduId].currentPosition = 0;
}

boolean isPduBufferLocked(PduIdType id) {
	imask_t state;
	Irq_Save(state);
	boolean bufferLocked = Com_BufferPduState[id].locked;
	Irq_Restore(state);
	if (bufferLocked) {
		return true;
	} else {
		return false;
	}
}
PduIdType getPduId(const ComIPdu_type* IPdu) {
	return (PduIdType)(IPdu - (ComConfig->ComIPdu));
}
#endif /* USE_COM */

