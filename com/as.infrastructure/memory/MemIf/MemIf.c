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

/*
 * Note!
 *
 * This file is controlled by config CFG_MEMIF_NO_MACRO and MEMIF_NUMBER_OF_DEVICES .
 */

#include "MemIf.h"
#include "asdebug.h"

#if (MEMIF_NUMBER_OF_DEVICES > 1) || defined(CFG_MEMIF_NO_MACRO)

void MemIf_SetMode(MemIf_ModeType Mode) {
	//return _MemIf_SetMode(Mode);
	asAssert(0);
}

Std_ReturnType MemIf_Read(uint8 DeviceIndex, uint16 BlockNumber, uint16 BlockOffset, uint8 *DataBufferPtr, uint16 Length) {
	//return _MemIf_Read(DeviceIndex, BlockNumber , BlockOffset, DataBufferPtr, Length );
#ifdef USE_FEE
	if(FEE_INDEX == DeviceIndex)
	{
		return Fee_Read(BlockNumber , BlockOffset, DataBufferPtr, Length );
	}
	else
#endif
#ifdef USE_EA
	if(EA_INDEX == DeviceIndex)
	{
		return Ea_Read(BlockNumber , BlockOffset, DataBufferPtr, Length );
	}
	else
#endif
	{
		return E_NOT_OK;
	}
}

Std_ReturnType MemIf_Write(uint8 DeviceIndex, uint16 BlockNumber, uint8 *DataBufferPtr) {
	//return _MemIf_Write(DeviceIndex, BlockNumber, DataBufferPtr );
#ifdef USE_FEE
	if(FEE_INDEX == DeviceIndex)
	{
		return Fee_Write(BlockNumber , DataBufferPtr);
	}
	else
#endif
#ifdef USE_EA
	if(EA_INDEX == DeviceIndex)
	{
		return Ea_Write(BlockNumber , DataBufferPtr);
	}
	else
#endif
	{
		return E_NOT_OK;
	}
}

void MemIf_Cancel(uint8 DeviceIndex) {
#ifdef USE_FEE
	//return _MemIf_Cancel(DeviceIndex);
	if(FEE_INDEX == DeviceIndex)
	{
		Fee_Cancel();
	}
	else
#endif
#ifdef USE_EA
	if(EA_INDEX == DeviceIndex)
	{
		Ea_Cancel();
	}
	else
#endif
	{

	}
}
MemIf_StatusType MemIf_GetStatus(uint8 DeviceIndex) {
	//return _MemIf_GetStatus(DeviceIndex);
#ifdef USE_FEE
	if(FEE_INDEX == DeviceIndex)
	{
		return Fee_GetStatus();
	}
	else
#endif
#ifdef USE_EA
	if(EA_INDEX == DeviceIndex)
	{
		return Ea_GetStatus();
	}
	else
#endif
	{
		return MEMIF_IDLE;
	}
}
MemIf_JobResultType MemIf_GetJobResult(uint8 DeviceIndex) {
	//eturn _MemIf_GetJobResult(DeviceIndex);
#ifdef USE_FEE
	if(FEE_INDEX == DeviceIndex)
	{
		return Fee_GetJobResult();
	}
	else
#endif
#ifdef USE_EA
	if(EA_INDEX == DeviceIndex)
	{
		return Ea_GetJobResult();
	}
	else
#endif
	{
		return MEMIF_JOB_FAILED;
	}
}
Std_ReturnType MemIf_InvalidateBlock(uint8 DeviceIndex, uint16 BlockNumber) {

	//return _MemIf_InvalidateBlock(DeviceIndex,BlockNumber);
#ifdef USE_FEE
	if(FEE_INDEX == DeviceIndex)
	{
		return Fee_InvalidateBlock(BlockNumber);
	}
	else
#endif
#ifdef USE_EA
	if(EA_INDEX == DeviceIndex)
	{
		return Ea_InvalidateBlock(BlockNumber);
	}
	else
#endif
	{
		return E_NOT_OK;
	}
}
Std_ReturnType MemIf_EraseImmediateBlock(uint8 DeviceIndex, uint16 BlockNumber) {
	//return _MemIf_EraseImmediateBlock( DeviceIndex, BlockNumber );
#ifdef USE_FEE
	if(FEE_INDEX == DeviceIndex)
	{
		return Fee_EraseImmediateBlock(BlockNumber);
	}
	else
#endif
#ifdef USE_EA
	if(EA_INDEX == DeviceIndex)
	{
		return Ea_EraseImmediateBlock(BlockNumber);
	}
	else
#endif
	{
		return E_NOT_OK;
	}
}
#endif

