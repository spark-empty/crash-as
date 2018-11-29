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
/* LUA version is 5.3.1 */
/* ============================ [ INCLUDES  ] ====================================================== */
#include "lascanlib.h"
#include "lasdevlib.h"
#include <sys/time.h>
/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
typedef void (*luaL_open_t)(void);
typedef void (*luaL_close_t)(void);
/* ============================ [ DECLARES  ] ====================================================== */
static int luai_as_time (lua_State *L);
/* ============================ [ DATAS     ] ====================================================== */
static const luaL_Reg aslib[] = {
		{"can_write",luai_can_write},
		{"can_read", luai_can_read},
		{"can_open", luai_can_open},
		{"can_log",  luai_can_log},
		{"time",     luai_as_time},
		{"open",     luai_as_open},
		{"read",     luai_as_read},
		{"write",     luai_as_write},
		{"ioctl",     luai_as_ioctl},
		{"close",     luai_as_close},
		{NULL,NULL}
};
static const luaL_open_t open_ops[] =
{
	luai_canlib_open,
	luai_asdevlib_open,
	NULL
};
static const luaL_open_t close_ops[] =
{
	luai_canlib_close,
	luai_asdevlib_close,
	NULL
};
static struct timeval m0;

/* ============================ [ LOCALS    ] ====================================================== */
static int luai_as_time (lua_State *L) {
	struct timeval m1;

	gettimeofday(&m1,NULL);
	lua_Number rtim = m1.tv_sec-m0.tv_sec;

	if(m1.tv_usec > m0.tv_usec)
	{
		rtim += (lua_Number)(m1.tv_usec-m0.tv_usec)/1000000.0;
	}
	else
	{
		rtim = rtim - 1 + (lua_Number)(1000000.0+m1.tv_usec-m0.tv_usec)/1000000.0;
	}
    lua_pushnumber(L, rtim);
    return 1;
}
/* ============================ [ FUNCTIONS ] ====================================================== */
LUAMOD_API int luaopen_as (lua_State *L)
{
	const luaL_open_t* libopen = open_ops;
	while((*libopen) != NULL)
	{
		(*libopen)();
		libopen ++;
	}
	luaL_newlib(L, aslib);

	gettimeofday(&m0,NULL);

	return 1;
}

void luaclose_as(void)
{
	const luaL_close_t* libclose = close_ops;
	while((*libclose) != NULL)
	{
		(*libclose)();
		libclose ++;
	}
}
