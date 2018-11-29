/*
* Configuration of module: XCP
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
#ifndef XCP_CFG_H
#define XCP_CFG_H

/* ============================ [ INCLUDES  ] ====================================================== */
#include "Xcp_ConfigTypes.h"
#include "CanIf.h"
/* ============================ [ MACROS    ] ====================================================== */
#define XCP_DEV_ERROR_DETECT STD_OFF
#define XCP_VERSION_INFO_API STD_OFF
#define XCP_FEATURE_GET_SLAVE_ID STD_ON

#define DAQ_DYNAMIC 0
#define DAQ_STATIC 1
#define XCP_DAQ_CONFIG_TYPE DAQ_STATIC
#define XCP_IDENTIFICATION XCP_IDENTIFICATION_ABSOLUTE
#define XCP_DAQ_COUNT  8
#define XCP_ODT_COUNT  56
#define XCP_ODT_ENTRIES_COUNT 112
#define XCP_MAX_CTO 8
#define XCP_MAX_DTO 8
#define XCP_MAX_RXTX_QUEUE 32
#define XCP_PROTOCOL XCP_PROTOCOL_CAN
#define XCP_PDU_ID_TX CANIF_ID_XCP_TX
#define XCP_PDU_ID_RX 0
#define XCP_CAN_ID_RX 0
#define XCP_PDU_ID_BROADCAST 0
#define XCP_ID_XCP_RX XCP_PDU_ID_RX
#define XCP_ID_XCP_TX XCP_PDU_ID_TX

#define XCP_FEATURE_PROTECTION STD_ON
#define XCP_FEATURE_PGM STD_ON
#define XCP_FEATURE_BLOCKMODE STD_ON
#define XCP_FEATURE_CALPAG STD_ON


#define XCP_STATIC_DAQ_COUNT 0
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
extern const Xcp_ConfigType XcpConfig;
extern uint8_t xcpSimMTAMemory[];
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#endif