/*
* Configuration of module: PduR
*
* Created by:   parai
* Copyright:    (C)parai@foxmail.com  
*
* Configured for (MCU):    posix
*
* Module vendor:           ArcCore
* Generator version:       01.00
*
* Generated by easySAR Studio (https://github.com/parai/as)
*/
#ifdef USE_PDUR


#include "PduR.h"

#if PDUR_CANIF_SUPPORT == STD_ON
#include "CanIf.h"
#endif
#if PDUR_CANTP_SUPPORT == STD_ON
#include "CanTp.h"
#endif
#if PDUR_LINIF_SUPPORT == STD_ON
#include "LinIf.h"
#endif
#if PDUR_COM_SUPPORT == STD_ON
#include "Com.h"
#endif
#if PDUR_DCM_SUPPORT == STD_ON
#include "Dcm.h"
#endif
#if PDUR_J1939TP_SUPPORT == STD_ON
#include "J1939Tp.h"
#endif
#ifdef USE_SOAD
#include "SoAd.h"
#endif

#if(PDUR_ZERO_COST_OPERATION == STD_OFF)
const PduRDestPdu_type PduR_PduRDestination[] = {

    {
        .DataProvision =  PDUR_NO_PROVISION,
        .DestPduId =  CANTP_ID_TxDiagP2P,
        .TxBufferRef =  NULL,
        .DestModule =  ARC_PDUR_CANTP
    },

    {
        .DataProvision =  PDUR_NO_PROVISION,
        .DestPduId =  DCM_ID_RxDiagP2P,
        .TxBufferRef =  NULL,
        .DestModule =  ARC_PDUR_DCM
    },

    {
        .DataProvision =  PDUR_NO_PROVISION,
        .DestPduId =  CANTP_ID_TxDiagP2A,
        .TxBufferRef =  NULL,
        .DestModule =  ARC_PDUR_CANTP
    },

    {
        .DataProvision =  PDUR_NO_PROVISION,
        .DestPduId =  DCM_ID_RxDiagP2A,
        .TxBufferRef =  NULL,
        .DestModule =  ARC_PDUR_DCM
    },

    {
        .DataProvision =  PDUR_NO_PROVISION,
        .DestPduId =  CANIF_ID_TxMsgTime,
        .TxBufferRef =  NULL,
        .DestModule =  ARC_PDUR_CANIF
    },

    {
        .DataProvision =  PDUR_NO_PROVISION,
        .DestPduId =  COM_ID_RxMsgAbsInfo,
        .TxBufferRef =  NULL,
        .DestModule =  ARC_PDUR_COM
    },

};
    const PduRDestPdu_type * const TxDiagP2P_PduRDestinations[] = 
{
	&PduR_PduRDestination[0],
	NULL,
};
const PduRDestPdu_type * const RxDiagP2P_PduRDestinations[] = 
{
	&PduR_PduRDestination[1],
	NULL,
};
const PduRDestPdu_type * const TxDiagP2A_PduRDestinations[] = 
{
	&PduR_PduRDestination[2],
	NULL,
};
const PduRDestPdu_type * const RxDiagP2A_PduRDestinations[] = 
{
	&PduR_PduRDestination[3],
	NULL,
};
const PduRDestPdu_type * const TxMsgTime_PduRDestinations[] = 
{
	&PduR_PduRDestination[4],
	NULL,
};
const PduRDestPdu_type * const RxMsgAbsInfo_PduRDestinations[] = 
{
	&PduR_PduRDestination[5],
	NULL,
};

const PduRRoutingPath_type TxDiagP2P_PduRRoutingPath = {
    .SduLength =  8,
    .SrcPduId =  DCM_ID_TxDiagP2P,
    .SrcModule =  ARC_PDUR_DCM,
    .PduRDestPdus =  TxDiagP2P_PduRDestinations
};

const PduRRoutingPath_type RxDiagP2P_PduRRoutingPath = {
    .SduLength =  8,
    .SrcPduId =  CANTP_ID_RxDiagP2P,
    .SrcModule =  ARC_PDUR_CANTP,
    .PduRDestPdus =  RxDiagP2P_PduRDestinations
};

const PduRRoutingPath_type TxDiagP2A_PduRRoutingPath = {
    .SduLength =  8,
    .SrcPduId =  DCM_ID_TxDiagP2A,
    .SrcModule =  ARC_PDUR_DCM,
    .PduRDestPdus =  TxDiagP2A_PduRDestinations
};

const PduRRoutingPath_type RxDiagP2A_PduRRoutingPath = {
    .SduLength =  8,
    .SrcPduId =  CANTP_ID_RxDiagP2A,
    .SrcModule =  ARC_PDUR_CANTP,
    .PduRDestPdus =  RxDiagP2A_PduRDestinations
};

const PduRRoutingPath_type TxMsgTime_PduRRoutingPath = {
    .SduLength =  8,
    .SrcPduId =  COM_ID_TxMsgTime,
    .SrcModule =  ARC_PDUR_COM,
    .PduRDestPdus =  TxMsgTime_PduRDestinations
};

const PduRRoutingPath_type RxMsgAbsInfo_PduRRoutingPath = {
    .SduLength =  8,
    .SrcPduId =  CANIF_ID_RxMsgAbsInfo,
    .SrcModule =  ARC_PDUR_CANIF,
    .PduRDestPdus =  RxMsgAbsInfo_PduRDestinations
};

const PduRRoutingPath_type * const PduRRoutingPaths[] = { 
	&TxDiagP2P_PduRRoutingPath,
	&RxDiagP2P_PduRRoutingPath,
	&TxDiagP2A_PduRRoutingPath,
	&RxDiagP2A_PduRRoutingPath,
	&TxMsgTime_PduRRoutingPath,
	&RxMsgAbsInfo_PduRRoutingPath,

    NULL
};  

const PduR_PBConfigType PduR_Config = {
    .PduRConfigurationId =  0,
    .NRoutingPaths =  6,       
    .RoutingPaths =  PduRRoutingPaths,
    .TpBuffers =  NULL,
    .TpRouteBuffers =  NULL
};

#endif //(PDUR_ZERO_COST_OPERATION == STD_OFF)  
    
#endif /* USE_PDUR */
