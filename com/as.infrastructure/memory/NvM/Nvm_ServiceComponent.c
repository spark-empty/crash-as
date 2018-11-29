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

#include "NvM.h"

#if defined(CFG_NVM_USE_SERVICE_COMPONENT)

Std_ReturnType NvMService_GetErrorStatus(NvM_BlockIdType BlockId, NvM_RequestResultType* RequestResultPtr) {
	NvM_GetErrorStatus( BlockId, (uint8*)RequestResultPtr );
	return E_OK;
}

#if (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON )
Std_ReturnType NvMService_SetRamBlockStatus(NvM_BlockIdType BlockId, Boolean BlockChanged) {
	NvM_SetRamBlockStatus( BlockId, (boolean)BlockChanged );
	return E_OK;
}
#endif

#if (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1)

Std_ReturnType NvMService_SetDataIndex(NvM_BlockIdType BlockId, UInt8 DataIndex) {
	NvM_SetDataIndex( BlockId, (uint8)DataIndex );
	return E_OK;
}

Std_ReturnType NvMService_GetDataIndex(NvM_BlockIdType BlockId, UInt8* DataIndexPtr) {
	NvM_GetDataIndex( BlockId, (uint8*)DataIndexPtr );
	return E_OK;
}

Std_ReturnType NvMService_ReadBlock(NvM_BlockIdType BlockId, const DstPtrType DstPtr) {
	return NvM_ReadBlock(BlockId, (uint8*)DstPtr), E_OK;
}

Std_ReturnType NvMService_WriteBlock(NvM_BlockIdType BlockId, const DstPtrType SrcPtr) {
	return NvM_WriteBlock( BlockId, (uint8*)(SrcPtr) ), E_OK;
}

Std_ReturnType NvMService_RestoreBlockDefaults(NvM_BlockIdType BlockId, const DstPtrType DstPtr) {
	return NvM_RestoreBlockDefaults( BlockId, (uint8*)DstPtr ), E_OK;
}

#else

Std_ReturnType NvMService_SetDataIndex(NvM_BlockIdType BlockId, UInt8 DataIndex) {
	/* Dummy */
	return E_NOT_OK;
}

Std_ReturnType NvMService_GetDataIndex(NvM_BlockIdType BlockId, UInt8* DataIndexPtr) {
	/* Dummy */
	return E_NOT_OK;
}

Std_ReturnType NvMService_ReadBlock(NvM_BlockIdType BlockId, const DstPtrType DstPtr) {
	/* Dummy */
	return E_NOT_OK;
}

Std_ReturnType NvMService_WriteBlock(NvM_BlockIdType BlockId, const DstPtrType SrcPtr) {
	/* Dummy */
	return NvM_WriteBlock(BlockId, (const uint8*) SrcPtr);
}

Std_ReturnType NvMService_RestoreBlockDefaults(NvM_BlockIdType BlockId, const DstPtrType DstPtr) {
	/* Dummy */
	return E_NOT_OK;
}

#endif

#if (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_2)

Std_ReturnType NvMService_EraseBlock(NvM_BlockIdType BlockId) {
	/* NOT SUPPORTED */ /* return NvM_EraseNvBlock( BlockId ); */
	return E_NOT_OK;
}

Std_ReturnType NvMService_InvalidateNvBlock(NvM_BlockIdType BlockId) {
	return NvM_InvalidateNvBlock( BlockId );
}

Std_ReturnType NvMAdmin_SetBlockProtection(NvM_BlockIdType BlockId, Boolean ProtectionEnabled) {
	/* NOT SUPPORTED */ /* NvM_SetBlockProtection( BlockId, (boolean)(ProtectionEnabled); return E_OK; */
	return E_NOT_OK;
}

#else

Std_ReturnType NvMService_EraseBlock(NvM_BlockIdType BlockId) {
	/* Dummy */
	return E_NOT_OK;
}

Std_ReturnType NvMService_InvalidateNvBlock(NvM_BlockIdType BlockId) {
	/* Dummy */
	return E_NOT_OK;
}

Std_ReturnType NvMAdmin_SetBlockProtection(NvM_BlockIdType BlockId, Boolean ProtectionEnabled) {
	/* Dummy */
	return E_NOT_OK;
}

#endif

#endif /* CFG_NVM_USE_SERVICE_COMPONENT */
