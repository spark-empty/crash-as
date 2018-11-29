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
#ifndef PYCAN_H_
#define PYCAN_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include <stdio.h>
/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */

/* ============================ [ DECLARES  ] ====================================================== */
extern "C" {
void luai_canlib_open(void);
void luai_canlib_close(void);
int can_open(unsigned long busid,const char* device,unsigned long port, unsigned long baudrate);
int can_write(unsigned long busid,unsigned long canid,unsigned long dlc,unsigned char* data);
int can_read(unsigned long busid,unsigned long canid,unsigned long *p_canid,unsigned long *dlc,unsigned char** data);
int can_close(unsigned long busid);
int can_reset(unsigned long busid);
}
/* ============================ [ CLASS     ] ====================================================== */
class can
{
public:
	explicit can()
	{
		printf("can()\n");
		luai_canlib_open();
	}
	~can()
	{
		printf("~can()\n");
		luai_canlib_close();
	}

	int open(unsigned long busid,const char* device,unsigned long port, unsigned long baudrate)
	{
		return can_open(busid,device,port,baudrate);
	}
	int write(unsigned long busid,unsigned long canid,unsigned long dlc,unsigned char* data)
	{
		return can_write(busid,canid,dlc,data);
	}

	int read(unsigned long busid,unsigned long canid,unsigned long *p_canid, unsigned long *dlc,unsigned char** data)
	{
		return can_read(busid,canid,p_canid,dlc,data);
	}

	int close(unsigned long busid)
	{
		return can_close(busid);
	}

	int reset(unsigned long busid)
	{
		return can_reset(busid);
	}
};
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */

#endif /* PYCAN_H_ */
