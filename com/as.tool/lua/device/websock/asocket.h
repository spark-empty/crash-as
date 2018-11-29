/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2017 AS <parai@foxmail.com>
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
#ifndef _ASOCKET_H_
#define _ASOCKET_H_

/* ============================ [ INCLUDES  ] ====================================================== */
#include <sys/types.h>
/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
#ifdef __WINDOWS__
struct iovec
{
	char* iov_base;
	size_t iov_len;
};
#else
struct iovec;
#endif
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
extern int ask_create(int is_server,const char * uri,int port);
extern int ask_accept(int s);
extern ssize_t ask_readv(int s,const struct iovec * iov, int iocnt);
extern ssize_t ask_writev(int s,const struct iovec * iov, int iocnt);
extern void ask_close(int s);
#endif /* _ASOCKET_H_ */
