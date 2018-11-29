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

/* ============================ [ INCLUDES  ] ====================================================== */
#ifdef __WINDOWS__
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#ifdef __WINDOWS__
#ifndef MSG_DONTWAIT
#define MSG_DONTWAIT 0
#endif
/* Link with ws2_32.lib */
#ifndef __GNUC__
#pragma comment(lib, "Ws2_32.lib")
#else
/* -lwsock32 */
#endif
#else
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#endif
#include "asocket.h"
/* ============================ [ MACROS    ] ====================================================== */
#define WEBSOCK_CLIENT_MAX 32
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
/* ============================ [ TYPES     ] ====================================================== */

/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
int ask_create(int is_server,const char * uri,int port)
{
	int s,rv;
	struct sockaddr_in addr;
#ifdef __WINDOWS__
	{
		WSADATA wsaData;
		static int startup_flag = 0;
		if(0 == startup_flag)
		{
			WSAStartup(MAKEWORD(2, 2), &wsaData);
			startup_flag = 1;
		}
	}
#endif

	rv = TRUE;
	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(uri);
	addr.sin_port = htons(port);

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("websocket TCP open failed!\n");perror("::");
		rv = FALSE;
	}

	if( rv && !is_server )
	{
		/* Connect to server. */
		if(connect(s, (struct sockaddr*) & addr, sizeof (addr)) < 0)
		{
#ifdef __WINDOWS__
			printf("websocket TCP connect failed: %d\n", WSAGetLastError());
			closesocket(s);
#else
			printf("websocket TCP connect failed!\n");perror("::");
			close(s);
#endif
			rv = FALSE;
		}
	}
	else if( rv && is_server )
	{
		if(bind(s, (struct sockaddr *)&(addr), sizeof (struct sockaddr))<0)
		{
#ifdef __WINDOWS__
			printf("websocket TCP bind failed: %d\n", WSAGetLastError());
			closesocket(s);
#else
			printf("websocket TCP bind failed!\n");perror("::");
			close(s);
#endif
			rv = FALSE;
		}

		if(rv)
		{
			if (listen(s, WEBSOCK_CLIENT_MAX) < 0 )
			{
#ifdef __WINDOWS__
				printf("websocket TCP listen failed: %d\n", WSAGetLastError());
				closesocket(s);
#else
				printf("websocket TCP listen failed!\n");perror("::");
				close(s);
#endif
				return FALSE;
			}
		}
	}

	if( !rv )
	{
		s = -1;
	}
	else
	{
		#ifdef __WINDOWS__
		/* set to non blocking mode */
		u_long iMode = 1;
		ioctlsocket(s, FIONBIO, &iMode);
		#endif
	}

	return s;
}
int ask_accept(int s)
{
	int cs;

	cs = accept(s,0,0);

	return cs;
}

ssize_t ask_readv(int s,const struct iovec * iov, int iocnt)
{
	ssize_t len;
	int i,tmp;

	len = 0;
	i = 0;

	do {
		tmp = recv(s,iov[i].iov_base,iov[i].iov_len,MSG_DONTWAIT);
		if(tmp > 0)
		{
			len += tmp;
		}

		if(tmp < 0)
		{
#ifdef __WINDOWS__
			if(10035 != WSAGetLastError())
#else
			if(errno != EAGAIN)
#endif
			{
#ifdef __WINDOWS__
				printf("websocket TCP %d recv failed: %d\n", s, WSAGetLastError());
				closesocket(s);
				len = -1;
#else
				//TODO:how to determine a connection error other than socket buffer empty.
				//printf("websocket TCP %d recv failed!\n",s);perror("::");
				//close(s);
				//len = -1;
#endif
			}
			break;
		}

		if((size_t)tmp < iov[i].iov_len)
		{
			break;
		}
	} while((++i) <iocnt);

	return len;
}

ssize_t ask_writev(int s,const struct iovec * iov, int iocnt)
{
	ssize_t len;
	int i,tmp;

	len = 0;
	i = 0;

	do {
		tmp = send(s,iov[i].iov_base,iov[i].iov_len,0);
		if((size_t)tmp == iov[i].iov_len)
		{
			len += tmp;
		}
		else
		{
			len = -1;
			break;
		}
	} while((++i) <iocnt);

	return len;
}

void ask_close(int s)
{
#ifdef __WINDOWS__
	closesocket(s);
#else
	close(s);
#endif
}
