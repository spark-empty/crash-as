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
#include "bootloader.h"
#include "Os.h"
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
static uint32 bl_prgs_seed= 0xdeadbeef;
static uint32 bl_extds_seed= 0xbeafdada;
static boolean bl_auto_prgs = FALSE;
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
Std_ReturnType BL_GetProgramSessionSeed (uint8 *securityAccessDataRecord, uint8 *seed,
		Dcm_NegativeResponseCodeType *errorCode)
{
	uint32 u32Seed; /* intentional not initialized to use the stack random value */
	uint32 u32Time = GetOsTick();

	(void)securityAccessDataRecord;
	*errorCode = DCM_E_POSITIVE_RESPONSE;
	bl_prgs_seed = bl_prgs_seed ^ u32Seed ^ u32Time ^ 0xfeedbeef;

	ASLOG(BL,"%s(seed = %X)\n",__func__,bl_prgs_seed);

	seed[0] = (uint8)(bl_prgs_seed>>24);
	seed[1] = (uint8)(bl_prgs_seed>>16);
	seed[2] = (uint8)(bl_prgs_seed>>8);
	seed[3] = (uint8)(bl_prgs_seed);
	return E_OK;
}
Std_ReturnType BL_CompareProgramSessionKey (uint8 *key)
{
	Std_ReturnType ercd;
	uint32 u32Key = ((uint32)key[0]<<24) + ((uint32)key[1]<<16) + ((uint32)key[2]<<8) +((uint32)key[3]);
	uint32 u32KeyExpected = bl_prgs_seed ^ 0x94586792;

	ASLOG(BL,"%s(key = %X(%X))\n",__func__,u32Key,u32KeyExpected);

	if(u32KeyExpected == u32Key)
	{
		ercd = E_OK;
		BL_StopAppTimer();
	}
	else
	{
		ercd = E_NOT_OK;
	}
	return ercd;
}

Std_ReturnType BL_GetExtendedSessionSeed (uint8 *securityAccessDataRecord, uint8 *seed,
		Dcm_NegativeResponseCodeType *errorCode)
{
	uint32 u32Seed; /* intentional not initialized to use the stack random value */
	uint32 u32Time = GetOsTick();
	*errorCode = DCM_E_POSITIVE_RESPONSE;
	(void)securityAccessDataRecord;
	*errorCode = DCM_E_POSITIVE_RESPONSE;

	bl_extds_seed = bl_extds_seed ^ u32Seed ^ u32Time ^ 0x95774321;

	ASLOG(BL,"%s(seed = %X)\n",__func__,bl_extds_seed);

	seed[0] = (uint8)(bl_extds_seed>>24);
	seed[1] = (uint8)(bl_extds_seed>>16);
	seed[2] = (uint8)(bl_extds_seed>>8);
	seed[3] = (uint8)(bl_extds_seed);
	return E_OK;
}
Std_ReturnType BL_CompareExtendedSessionKey (uint8 *key)
{
	Std_ReturnType ercd;
	uint32 u32Key = ((uint32)key[0]<<24) + ((uint32)key[1]<<16) + ((uint32)key[2]<<8) +((uint32)key[3]);
	uint32 u32KeyExpected = bl_extds_seed ^ 0x78934673;

	ASLOG(BL,"%s(key = %X(%X))\n",__func__,u32Key,u32KeyExpected);

	if(u32KeyExpected == u32Key)
	{
		ercd = E_OK;
	}
	else
	{
		ercd = E_NOT_OK;
	}
	return ercd;
}
Std_ReturnType BL_StartProtocolCbk (Dcm_ProtocolType protocolID)
{
	ASLOG(BL,"%s(protocolID=%d)\n",__func__,protocolID);
	// TODO: check pre-condition such as battery...
	return E_OK;
}
Std_ReturnType BL_StopProtocolCbk (Dcm_ProtocolType protocolID)
{
	ASLOG(BL,"%s(protocolID=%d)\n",__func__,protocolID);
	return E_OK;
}
Std_ReturnType BL_ProtocolIndicationCbk(uint8 *requestData, uint16 dataSize)
{
	ASLOG(BL,"%s(dataSize=%d)\n",__func__,dataSize);
	return E_OK;
}

Std_ReturnType BL_GetSessionChangePermission(Dcm_SesCtrlType sesCtrlTypeActive, Dcm_SesCtrlType sesCtrlTypeNew)

{
	Std_ReturnType ercd = E_OK;
	ASLOG(BL,"%s(%d --> %d)\n",__func__,sesCtrlTypeActive,sesCtrlTypeNew);

	/* program session can only be entered through EXTDS session */
	if(( DCM_PROGRAMMING_SESSION == sesCtrlTypeNew) && (DCM_EXTENDED_DIAGNOSTIC_SESSION != sesCtrlTypeActive))
	{
		ercd = E_NOT_OK;
	}
	if(( DCM_PROGRAMMING_SESSION == sesCtrlTypeNew) && (DCM_EXTENDED_DIAGNOSTIC_SESSION == sesCtrlTypeActive))
	{
		Dcm_SecLevelType level = BL_SECURITY_LEVEL_EXTDS;
		(void)Dcm_GetSecurityLevel(&level);

		if(DCM_SEC_LEV_LOCKED == level)
		{
			ercd = E_NOT_OK;
		}
	}

	if(bl_auto_prgs==TRUE)
	{
		bl_auto_prgs = FALSE;
		ercd = E_OK;
	}
	return ercd;
}

void BL_SetAutoPRGS(void)
{
	bl_auto_prgs = TRUE;
}
