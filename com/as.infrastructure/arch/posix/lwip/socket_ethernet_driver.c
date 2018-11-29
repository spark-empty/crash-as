/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2016  AS <parai@foxmail.com>
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
#ifdef SOCKET_ETHERNET_DRIVER
/* ============================ [ INCLUDES  ] ====================================================== */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/queue.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <asm-generic/ioctls.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
/* ============================ [ MACROS    ] ====================================================== */
#define ETH_BUS_NODE_MAX 32
/* ============================ [ TYPES     ] ====================================================== */
struct Eth_SocketHandle_s
{
	int s; /* ETH raw socket: accept */
	STAILQ_ENTRY(Eth_SocketHandle_s) entry;
};
struct Eth_SocketHandleList_s
{
	pthread_t rx_thread;
	int s; /* ETH raw socket: listen */
	STAILQ_HEAD(,Eth_SocketHandle_s) head;
};
static struct timeval m0;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
static struct Eth_SocketHandleList_s* socketH = NULL;
static pthread_mutex_t socketLock = PTHREAD_MUTEX_INITIALIZER;
/* ============================ [ LOCALS    ] ====================================================== */
static int init_socket(void)
{
	int ercd;
	int s;
	struct sockaddr_in service;

	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s < 0 ) {
		perror("socket");
		return false;;
	}

	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = (u_short)htons(8000);
	ercd = bind(s, (struct sockaddr *)&(service), sizeof (struct sockaddr));
	if (ercd < 0) {
		perror("bind");
		return false;
	}

	if (listen(s, ETH_BUS_NODE_MAX) < 0 ) {
		perror("listen");
		return false;
	}

	printf("eth socket driver on-line!\n");

	socketH = malloc(sizeof(struct Eth_SocketHandleList_s));
	assert(socketH);
	STAILQ_INIT(&socketH->head);
	socketH->s = s;

	return true;
}
static void try_accept(void)
{
	struct Eth_SocketHandle_s* handle;
	int s = accept(socketH->s, NULL, NULL);

	if(s >= 0)
	{

		handle = malloc(sizeof(struct Eth_SocketHandle_s));
		assert(handle);
		handle->s = s;
		pthread_mutex_lock(&socketLock);
		STAILQ_INSERT_TAIL(&socketH->head,handle,entry);
		pthread_mutex_unlock(&socketLock);
		printf("  >> ETH socket %X on-line! <<\n",s);
	}
	else
	{

	}
}

static void remove_socket(struct Eth_SocketHandle_s* h)
{
	printf("  >> ETH socket %X off-line! <<\n",h->s);
	STAILQ_REMOVE(&socketH->head,h,Eth_SocketHandle_s,entry);
	close(h->s);
	free(h);
}
static void log_msg(unsigned char* frame,size_t len,float rtim, int s)
{
	size_t i,j;
	printf("\nETH%05d :: 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F  length=%d @%f s\n",s,(int)len,rtim);
	for(i=0; i<(len+15)/16; i++)
	{

		printf("%08X ::",(uint32_t)i*16);

		fflush(stdout);
		for(j=0;j<16;j++)
		{
			if((i*16+j)<len)
			{
				printf(" %02X",frame[i*16+j]);
			}
			else
			{
				printf("   ");
			}
		}
		printf("\t");
		for(j=0;j<16;j++)
		{
			if(((i*16+j)<len) && isprint(frame[i*16+j]))
			{
				printf("%c",frame[i*16+j]);
			}
			else
			{
				printf(".");
			}
		}
		printf("\n");
	}

	fflush(stdout);
}
static void try_recv_forward(void)
{
	int len;
	unsigned char frame[2018];
	struct Eth_SocketHandle_s* h;
	struct Eth_SocketHandle_s* h2;

	pthread_mutex_lock(&socketLock);
	STAILQ_FOREACH(h,&socketH->head,entry)
	{
		len = recv(h->s, (void*)&frame, sizeof(frame), MSG_DONTWAIT);
		if(len > 0)
		{
			struct timeval m1;

			gettimeofday(&m1,NULL);
			float rtim = m1.tv_sec-m0.tv_sec;

			if(m1.tv_usec > m0.tv_usec)
			{
				rtim += (float)(m1.tv_usec-m0.tv_usec)/1000000.0;
			}
			else
			{
				rtim = rtim - 1 + (float)(1000000.0+m1.tv_usec-m0.tv_usec)/1000000.0;
			}

			log_msg(frame,(size_t)len,rtim,h->s);

			STAILQ_FOREACH(h2,&socketH->head,entry)
			{
				if(h != h2)
				{
					if (send(h2->s, (const char*)&frame, len,0) != len) {
						printf("send failed with error, remove this node %X!\n",h2->s);
						perror("send");
						remove_socket(h2);
						break;
					}
				}
			}
		}
		else if(-1 == len)
		{

		}
		else
		{
			printf("timeout recv... len=%d\n",len);
			remove_socket(h);
		}
	}
	pthread_mutex_unlock(&socketLock);
}
static void * rx_daemon(void * param)
{
	(void)param;
	while(true)
	{
		try_accept();
	}

	return NULL;
}
static void schedule(void)
{
	try_recv_forward();
}
/* ============================ [ FUNCTIONS ] ====================================================== */
int main(int argc,char* argv[])
{
	gettimeofday(&m0,NULL);
	if(false==init_socket())
	{
		return -1;
	}

	if( 0 == pthread_create(&(socketH->rx_thread),NULL,rx_daemon,NULL))
	{
	}
	else
	{
		return -1;
	}

	for(;;)
	{
		schedule();
	}

	return 0;
}
#endif /* SOCKET_ETHERNET_DRIVER */
