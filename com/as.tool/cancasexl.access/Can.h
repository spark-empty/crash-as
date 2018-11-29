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
#ifndef CAN_H_
#define CAN_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"

/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
typedef struct CanPduType {
    /* the CAN ID, 29 or 11-bit */
	uint32   	id;
	uint8		length;
	uint8 		sdu[8];
} Can_PduType;
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
Std_ReturnType Can_Init(uint32 port,uint32 baudrate);
Std_ReturnType Can_DeInit(uint32 port);
/*
 * This API is special for VXLAPI
 *
 * message example:
 * "RX_MSG c=0, t=222, id=0510 l=8, 0000000000000000 tid=00"
 * So access it in python by re
 * [ port, time, id, length, data ]
 * reMsg = re.compile(r'RX_MSG c=(\d+), t=(\d+), id=(\w+) l=(\d+), (\w+)')
 */
Std_ReturnType Can_Receive(uint32 port,char** message);
Std_ReturnType Can_Write(uint32  port, Can_PduType *pduInfo );
#endif /* CAN_H_ */
