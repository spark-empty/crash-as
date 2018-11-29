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
#ifdef USE_ECUM
#include "EcuM.h"
#endif
#include "Os.h"
#ifdef USE_MCU
#include "Mcu.h"
#endif
#ifdef USE_CAN
#include "Can.h"
#endif
#ifdef USE_CANTP
#include "CanTp.h"
#include "CanTp_Cbk.h"
#endif
#ifdef USE_DCM
#include "Dcm.h"
#endif
#ifdef USE_XCP
#include "Xcp.h"
#endif

#include "bootloader.h"

#include "CanIf.h"
#include "CanIf_Cbk.h"

#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
extern void StartOsTick(void);
/* ============================ [ DATAS     ] ====================================================== */
#ifdef USE_ANYOS
TickType				OsTickCounter = 1;
#endif

#ifdef USE_CAN
extern const Can_ControllerConfigType  Can_ControllerCfgData[];
#endif
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void StartupHook(void)
{
	printf(" start bootloaster BUILD @ %s %s\n",__DATE__,__TIME__);
}

void SchM_StartupHook(void)
{

}

#if !defined(USE_CANIF)
void CanIf_TxConfirmation( PduIdType canTxPduId )
{
#ifdef USE_CANTP
	if(CANIF_ID_TxDiagP2P == canTxPduId)
	{
		CanTp_TxConfirmation(CANTP_ID_TxDiagP2P);
	}
#endif
#ifdef USE_XCP
	if(CANIF_ID_XCP_TX == canTxPduId)
	{
		Xcp_CanIfTxConfirmation(CANIF_ID_XCP_TX);
	}
#endif
}
void CanIf_RxIndication( uint16 Hrh, Can_IdType CanId, uint8 CanDlc, const uint8 *CanSduPtr )
{
	PduInfoType pdu;

	pdu.SduDataPtr = (uint8*)CanSduPtr;
	pdu.SduLength = CanDlc;
#ifdef USE_CANTP
	if(0x731 == CanId)
	{
		CanTp_RxIndication(0, &pdu);
	}
#endif
#ifdef USE_XCP
	if(0x554 == CanId)
	{
		Xcp_CanIfRxIndication(0, &pdu);
	}
#endif
}

Std_ReturnType CanIf_Transmit(PduIdType CanTxPduId,
    const PduInfoType *PduInfoPtr)
{
	Can_PduType canPdu;
	Can_ReturnType rVal;
	Std_ReturnType ret = E_OK;
#ifdef USE_CANTP
	if(CANIF_ID_TxDiagP2P == CanTxPduId)
	{
		canPdu.id = 0x732;

		canPdu.length = PduInfoPtr->SduLength;
		canPdu.sdu = PduInfoPtr->SduDataPtr;
		canPdu.swPduHandle = CanTxPduId;
		rVal = Can_Write(Can0Hth, &canPdu);

		if (rVal == CAN_NOT_OK){
			ret = E_NOT_OK;
		}
	}
	else
#endif
#ifdef USE_CANTP
	if(CANIF_ID_XCP_TX == CanTxPduId)
	{
		canPdu.id = 0x555;

		canPdu.length = PduInfoPtr->SduLength;
		canPdu.sdu = PduInfoPtr->SduDataPtr;
		canPdu.swPduHandle = CanTxPduId;
		rVal = Can_Write(Can0Hth, &canPdu);

		if (rVal == CAN_NOT_OK){
			ret = E_NOT_OK;
		}
	}
	else
#endif
	{
		ret = E_NOT_OK;
	}

	return ret;
}
#endif

#ifdef USE_ANYOS
void __weak BL_HwMonitor(void)
{
	/* this weak function need to be re-implemented for each board
	 * to do hardware monitoring, for example, call OsTick
	 * each 1ms */
}

void OsTick(void)
{
	OsTickCounter ++;

	if(0u == OsTickCounter)
	{
		OsTickCounter = 1;
	}
}

void StartOS( AppModeType mode )
{
	(void) mode;
	static TickType preTick = 1;
	StartupHook();
	OsTickCounter = 1;
	StartOsTick();
	for(;;)
	{
		Irq_Enable();
		BL_HwMonitor();
#ifdef USE_CAN
		Can_MainFunction_Read();
		Can_MainFunction_Write();
#endif

		if(preTick != OsTickCounter)
		{
			#ifdef USE_CANTP
			CanTp_MainFunction();
			#endif
			#ifdef USE_DCM
			Dcm_MainFunction();
			#endif
			#ifdef USE_XCP
			Xcp_MainFunction();
			#endif
			BL_MainFunction();
			preTick = OsTickCounter;
		}
	}
}
#endif

#ifndef USE_ECUM
void __weak BL_HwInit(void)
{
	/* this weak function need to be re-implemented for each board
	 * to do hardware initialization */
}
void EcuM_Init(void)
{
#ifdef USE_MCU
	Mcu_Init(McuConfigData);
	while(MCU_PLL_LOCKED != Mcu_GetPllStatus());
	Mcu_DistributePllClock();
#endif

	BL_HwInit();

#ifdef USE_CAN
	Can_Init(&Can_ConfigData);
	Can_InitController(0, Can_ControllerCfgData);
	Can_SetControllerMode(0, CAN_T_START);
#endif

	/* No CANIF */

#ifdef USE_CANTP
	CanTp_Init();
#endif

#ifdef USE_DCM
	Dcm_Init();
#endif

#ifdef USE_XCP
	Xcp_Init(&XcpConfig);
#endif

	BL_Init();

	StartOS(OSDEFAULTAPPMODE);
}
#endif

int main(int argc,char* argv[])
{
	EcuM_Init();
	while(1);

	return 0;
}
