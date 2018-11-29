#ifndef COM_AS_INFRASTRUCTURE_BOOT_COMMON_BOOTLOADER_H_
#define COM_AS_INFRASTRUCTURE_BOOT_COMMON_BOOTLOADER_H_
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
#include "Std_Types.h"
#include "Dcm.h"
#include "Dcm_Internal.h"
#ifdef USE_XCP
#include "Xcp.h"
#endif
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
#define AS_LOG_BL 1
#define AS_LOG_PBL 1

#define BL_SECURITY_LEVEL_EXTDS 1
#define BL_SECURITY_LEVEL_PRGS  2
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void BL_Init(void);
void BL_MainFunction(void);
void BL_StopAppTimer(void);
#endif /* COM_AS_INFRASTRUCTURE_BOOT_COMMON_BOOTLOADER_H_ */
