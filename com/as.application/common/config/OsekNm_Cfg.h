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
#ifndef COM_AS_APPLICATION_COMMON_CONFIG_OSEKNM_CFG_H_
#define COM_AS_APPLICATION_COMMON_CONFIG_OSEKNM_CFG_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Can.h"
/* ============================ [ MACROS    ] ====================================================== */
#define OSEKNM_NET_NUM 1

#define PDUR_ID_OSEK_NM_RX   0
#define PDUR_ID2_OSEK_NM_TX  0
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void CanIf_OsekNmUserTxConfirmation(PduIdType pduId);
void CanIf_OsekNmUserRxIndication(uint8 channel, PduIdType pduId, const uint8 *sduPtr, uint8 dlc, Can_IdType canId);
#endif /* COM_AS_APPLICATION_COMMON_CONFIG_OSEKNM_CFG_H_ */
