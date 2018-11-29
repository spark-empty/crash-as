/* -------------------------------- Arctic Core ------------------------------
 * Arctic Core - the open source AUTOSAR platform http://arccore.com
 *
 * Copyright (C) 2009  ArcCore AB <contact@arccore.com>
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
 * -------------------------------- Arctic Core ------------------------------*/


#include "PduR.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#include "asdebug.h"

#if (PDUR_ZERO_COST_OPERATION == STD_OFF) && (PDUR_J1939TP_SUPPORT == STD_ON)

#if (PDUR_DCM_SUPPORT == STD_ON)
#ifndef J1939TP_DCM_BUFFER_NUM
#define J1939TP_DCM_BUFFER_NUM 2
#endif
typedef struct {
	PduInfoType *pduInfoPtr;
	PduIdType pduId;
	PduLengthType pos;
} J1939Tp_DcmBufferControlType;
static J1939Tp_DcmBufferControlType J1939Tp_DcmBufferControl[J1939TP_DCM_BUFFER_NUM];
static J1939Tp_DcmBufferControlType* J1939Tp_MallocDBC(void)
{
	int i;
	J1939Tp_DcmBufferControlType* pDBC = NULL;

	for(i=0; i<J1939TP_DCM_BUFFER_NUM; i++)
	{
		if(NULL == J1939Tp_DcmBufferControl[i].pduInfoPtr)
		{
			pDBC = &J1939Tp_DcmBufferControl[i];
			pDBC->pduInfoPtr = (void*)-1; /* reserved it as used */
			pDBC->pos = 0;
			break;
		}
	}

	return pDBC;
}

static void J1939Tp_FreeDBC(J1939Tp_DcmBufferControlType* pDBC)
{
	pDBC->pduInfoPtr = NULL;
}

static J1939Tp_DcmBufferControlType* J1939Tp_FindDBC(PduIdType id)
{
	int i;
	J1939Tp_DcmBufferControlType* pDBC = NULL;

	for(i=0; i<J1939TP_DCM_BUFFER_NUM; i++)
	{
		if(id == J1939Tp_DcmBufferControl[i].pduId)
		{
			pDBC = &J1939Tp_DcmBufferControl[i];
			break;
		}
	}

	return pDBC;
}
#endif

void PduR_J1939TpRxIndication(PduIdType id, NotifResultType Result) {
	const PduRRoutingPath_type *route = PduRConfig->RoutingPaths[id];

	// Limitation, Just sends to the first destination
	switch(route->PduRDestPdus[0]->DestModule)
	{
	#if (PDUR_COM_SUPPORT == STD_ON)
	case ARC_PDUR_COM:
		Com_TpRxIndication(route->PduRDestPdus[0]->DestPduId, Result);
		break;
	#endif
	#if (PDUR_DCM_SUPPORT == STD_ON)
	case ARC_PDUR_DCM:
	{
		J1939Tp_DcmBufferControlType* pDBC;
		pDBC = J1939Tp_FindDBC(id);
		if(NULL != pDBC)
		{
			J1939Tp_FreeDBC(pDBC);
		}
		Dcm_RxIndication(route->PduRDestPdus[0]->DestPduId, Result);
		break;
	}
	#endif
	default:
		break;
	}
}

void PduR_J1939TpTxConfirmation(PduIdType J1939TpTxId, NotifResultType Result) {
	const PduRRoutingPath_type *route = PduRConfig->RoutingPaths[J1939TpTxId];

	// Limitation, Just sends to the first destination
	switch(route->SrcModule)
	{
	#if (PDUR_COM_SUPPORT == STD_ON)
	case ARC_PDUR_COM:
		Com_TpTxConfirmation(route->SrcPduId, Result);
		break;
	#endif
	#if (PDUR_DCM_SUPPORT == STD_ON)
	case ARC_PDUR_DCM:
	{
		J1939Tp_DcmBufferControlType* pDBC;
		pDBC = J1939Tp_FindDBC(J1939TpTxId);
		if(NULL != pDBC)
		{
			J1939Tp_FreeDBC(pDBC);
		}
		Dcm_TxConfirmation(route->SrcPduId, Result);
		break;
	}
	#endif
	default:
		break;
	}
}

/* autosar 4 api */
BufReq_ReturnType PduR_J1939TpCopyTxData(PduIdType id, PduInfoType* info, RetryInfoType* retry, PduLengthType* availableDataPtr) {
	BufReq_ReturnType ercd = BUFREQ_NOT_OK;
	const PduRRoutingPath_type *route = PduRConfig->RoutingPaths[id];

	// Limitation, Just sends to the first destination
	switch(route->SrcModule)
	{
	#if (PDUR_COM_SUPPORT == STD_ON)
	case ARC_PDUR_COM:
		ercd = Com_CopyTxData(route->SrcPduId, info,0 ,availableDataPtr);
		break;
	#endif
	#if (PDUR_DCM_SUPPORT == STD_ON)
	case ARC_PDUR_DCM:
	{
		J1939Tp_DcmBufferControlType* pDBC;
		pDBC = J1939Tp_FindDBC(id);
		if(NULL == pDBC)
		{
			pDBC = J1939Tp_MallocDBC();
			if(NULL != pDBC)
			{
				ercd = Dcm_ProvideTxBuffer(route->SrcPduId, &(pDBC->pduInfoPtr), 0);
				if(BUFREQ_OK != ercd)
				{
					J1939Tp_FreeDBC(pDBC);
					pDBC = NULL;
				}
				else
				{
					pDBC->pduId = id;
					*availableDataPtr = pDBC->pduInfoPtr->SduLength;
				}
			}
		}

		if(NULL != pDBC)
		{
			if( (NULL != pDBC->pduInfoPtr->SduDataPtr) &&
				((pDBC->pos+info->SduLength) <= pDBC->pduInfoPtr->SduLength) )
			{
				memcpy(info->SduDataPtr, &pDBC->pduInfoPtr->SduDataPtr[pDBC->pos], info->SduLength);
				pDBC->pos += info->SduLength;
				*availableDataPtr = pDBC->pduInfoPtr->SduLength - pDBC->pos;
				ercd = BUFREQ_OK;
			}
		}
		break;
	}
	#endif
	default:
		break;
	}

	return ercd;
}
BufReq_ReturnType PduR_J1939TpCopyRxData(PduIdType id, PduInfoType* info, PduLengthType* bufferSizePtr) {
	BufReq_ReturnType ercd = BUFREQ_NOT_OK;
	const PduRRoutingPath_type *route = PduRConfig->RoutingPaths[id];

	// Limitation, Just sends to the first destination
	switch(route->PduRDestPdus[0]->DestModule)
	{
	#if (PDUR_COM_SUPPORT == STD_ON)
	case ARC_PDUR_COM:
		ercd = Com_CopyRxData(route->PduRDestPdus[0]->DestPduId, info,bufferSizePtr);
		break;
	#endif
	#if (PDUR_DCM_SUPPORT == STD_ON)
	case ARC_PDUR_DCM:
	{
		J1939Tp_DcmBufferControlType* pDBC;
		pDBC = J1939Tp_FindDBC(id);
		if(NULL != pDBC)
		{
			if( (NULL != pDBC->pduInfoPtr->SduDataPtr) &&
				((pDBC->pos+info->SduLength) <= pDBC->pduInfoPtr->SduLength) )
			{
				memcpy(&pDBC->pduInfoPtr->SduDataPtr[pDBC->pos], info->SduDataPtr, info->SduLength);
				pDBC->pos += info->SduLength;
				*bufferSizePtr = pDBC->pduInfoPtr->SduLength - pDBC->pos;
				ercd = BUFREQ_OK;
			}
		}
		break;
	}
	#endif
	default:
		break;
	}

	return ercd;
}

BufReq_ReturnType PduR_J1939TpStartOfReception(PduIdType id, PduLengthType TpSduLength, PduLengthType* bufferSizePtr) {
	BufReq_ReturnType ercd = BUFREQ_NOT_OK;
	const PduRRoutingPath_type *route = PduRConfig->RoutingPaths[id];
	// Limitation, Just sends to the first destination
	switch(route->PduRDestPdus[0]->DestModule)
	{
	#if (PDUR_COM_SUPPORT == STD_ON)
	case ARC_PDUR_COM:
		ercd = Com_StartOfReception(route->PduRDestPdus[0]->DestPduId, TpSduLength, bufferSizePtr);
		break;
	#endif
	#if (PDUR_DCM_SUPPORT == STD_ON)
	case ARC_PDUR_DCM:
	{
		J1939Tp_DcmBufferControlType* pDBC;
		pDBC = J1939Tp_MallocDBC();
		if(NULL != pDBC)
		{
			ercd = Dcm_ProvideRxBuffer(route->PduRDestPdus[0]->DestPduId, TpSduLength, &(pDBC->pduInfoPtr));
			if(BUFREQ_OK != ercd)
			{
				J1939Tp_FreeDBC(pDBC);
			}
			else
			{
				pDBC->pduId = id;
				*bufferSizePtr = pDBC->pduInfoPtr->SduLength;
			}
		}
		break;
	}
	#endif
	default:
		break;
	}

	return ercd;
}

#endif
