#ifndef COM_AS_TOOL_LUA_CAN_LASCANLIB_H_
#define COM_AS_TOOL_LUA_CAN_LASCANLIB_H_
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
#if !defined(__AS_PY_CAN__) && !defined(__AS_CAN_BUS__)
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#endif
/* ============================ [ MACROS    ] ====================================================== */
#define CAN_DEVICE_NAME_SIZE 32
/* ============================ [ TYPES     ] ====================================================== */
typedef void (*can_device_rx_notification_t)(uint32_t busid,uint32_t canid,uint32_t dlc,uint8_t* data);
typedef boolean (*can_device_probe_t)(uint32_t busid,uint32_t port,uint32_t baudrate,can_device_rx_notification_t rx_notification);
typedef boolean (*can_device_write_t)(uint32_t port,uint32_t canid,uint32_t dlc,uint8_t* data);
typedef boolean (*can_device_reset_t)(uint32_t port);
typedef void (*can_device_close_t)(uint32_t port);

typedef struct
{
	char name[CAN_DEVICE_NAME_SIZE];
	can_device_probe_t probe;
	can_device_close_t close;
	can_device_write_t write;
	can_device_reset_t reset;
}Can_DeviceOpsType;

typedef struct
{
	uint32_t busid; /* busid of this driver */
	uint32_t port;  /* busid --> port of this device */
	const Can_DeviceOpsType* ops;
}Can_DeviceType;
/* ============================ [ DECLARES  ] ====================================================== */
extern const Can_DeviceOpsType can_rpmsg_ops;
extern const Can_DeviceOpsType can_serial_ops;
#ifdef __WINDOWS__
extern const Can_DeviceOpsType can_vxl_ops;
extern const Can_DeviceOpsType can_peak_ops;
extern const Can_DeviceOpsType can_zlg_ops;
#else
extern const Can_DeviceOpsType can_socket_ops;
#endif
extern const Can_DeviceOpsType can_socketwin_ops;
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#if !defined(__AS_PY_CAN__) && !defined(__AS_CAN_BUS__)
int luai_can_write (lua_State *L);
int luai_can_read  (lua_State *L);
int luai_can_open  (lua_State *L);
int luai_can_close (lua_State *L);
int luai_can_log   (lua_State *L);
void luai_canlib_open(void);
void luai_canlib_close(void);
#endif
#endif /* COM_AS_TOOL_LUA_CAN_LASCANLIB_H_ */
