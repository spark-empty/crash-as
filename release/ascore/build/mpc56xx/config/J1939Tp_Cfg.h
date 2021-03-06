/*
* Configuration of module: J1939Tp
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
#ifndef J1939TP_CFG_H
#define J1939TP_CFG_H
/* ============================ [ INCLUDES  ] ====================================================== */
#include "SchM_cfg.h"
/* ============================ [ MACROS    ] ====================================================== */
#define J1939TP_VERSION_INFO_API        STD_ON
#define J1939TP_DEV_ERROR_DETECT        STD_ON
#define J1939TP_MAIN_FUNCTION_PERIOD MAIN_FUNCTION_PERIOD(J1939TP)
#define J1939TP_TX_CONF_TIMEOUT MIAN_FUNCTION_MS2TICKS(J1939TP,1000)
#define J1939TP_PACKETS_PER_BLOCK 8

#define J1939TP_CHL_J1939TP_RX_CHL 0
#define J1939TP_CHL_J1939TP_TX_CHL 1
#define J1939TP_TX_CHANNEL_COUNT 1
#define J1939TP_RX_CHANNEL_COUNT 1
#define J1939TP_CHANNEL_COUNT (J1939TP_TX_CHANNEL_COUNT+J1939TP_RX_CHANNEL_COUNT)

#define J1939TP_ID_RX_J1939TP_REVERSE_CM 0
#define J1939TP_ID_RX_J1939TP_CM 1
#define J1939TP_ID_RX_J1939TP_DT 2
#define J1939TP_ID_RX_J1939TP_DIRECT 3
#define J1939TP_ID_TX_J1939TP_CmNPdu 4
#define J1939TP_ID_TX_J1939TP_DtNPdu 5
#define J1939TP_ID_TX_J1939TP_FcNPdu 6
#define J1939TP_ID_TX_J1939TP_DirectNPdu 7
#define J1939TP_RX_PDU_COUNT 8

#define J1939TP_PGID_PG_RX 0
#define J1939TP_ID_J1939TP_RX 0
#define J1939TP_PGID_PG_TX 1
#define J1939TP_ID_J1939TP_TX 1
#define J1939TP_PG_COUNT 2

/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#endif /* J1939TP_CFG_H */
