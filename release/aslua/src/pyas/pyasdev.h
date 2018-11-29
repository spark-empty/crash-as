/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2017  AS <parai@foxmail.com>
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
#ifndef PYASDEV_H_
#define PYASDEV_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include <stdio.h>
/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */

/* ============================ [ DECLARES  ] ====================================================== */
extern "C" {
	void luai_asdevlib_open(void);
	void luai_asdevlib_close(void);
	int asdev_open(const char* device, const char* option);
	int asdev_write(int fd, unsigned char* data, unsigned long len);
	int asdev_read(int fd, unsigned char** data);
	int asdev_ioctl(int fd, int type, unsigned char* data,unsigned long len, unsigned char** rdata);
	int asdev_close(int fd);
}
/* ============================ [ CLASS     ] ====================================================== */
class asdev
{
public:
	explicit asdev()
	{
		printf("asdev()\n");
		luai_asdevlib_open();
	}
	~asdev()
	{
		printf("~asdev()\n");
		luai_asdevlib_close();
	}

	int open(const char* device, const char* option)
	{
		return asdev_open(device, option);
	}
	int write(int fd, unsigned char* data, unsigned long len)
	{
		return asdev_write(fd, data, len);
	}

	int read(int fd, unsigned char** data)
	{
		return asdev_read(fd, data);
	}

	int ioctl(int fd, int type, unsigned char* data,unsigned long len, unsigned char** rdata)
	{
		return asdev_ioctl(fd, type, data, len, rdata);
	}
	int close(int fd)
	{
		return asdev_close(fd);
	}
};
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */

#endif /* PYASDEV_H_ */
