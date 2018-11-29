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
#ifndef KSM_CFG_H
#define KSM_CFG_H

/* ============================ [ INCLUDES  ] ====================================================== */
#include "Os.h"
/* ============================ [ MACROS    ] ====================================================== */
#define KSM_ID_CANIdle                          0
#define KSM_NUM                                 1

#define KSM_CANIdle_Init                     0
#define KSM_CANIdle_Start                    1
#define KSM_CANIdle_Stop                     2
#define KSM_CANIdle_Running                  3
#define KSM_CANIdle_STATE_LIMIT              4

/* ============================ [ TYPES     ] ====================================================== */

typedef uint8 KSMState_Type;
typedef void (*KsmFunction_Type) (void);
typedef struct
{
    KSMState_Type KsLimit;
    const KsmFunction_Type* Ksm;
}KSM_Type;    /* Kernel State Machine */
/* ============================ [ DECLARES  ] ====================================================== */
extern const KSM_Type KSM_Config[KSM_NUM];
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#endif

