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
#include "remoteproc.h"
#ifdef __WINDOWS__
#include <windows.h>
#endif
#ifdef __LINUX__
#include <pthread.h>
#include <unistd.h>
#endif

#include <virtio_can.h>
/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
struct rsc_fifo {
	u32 count;
	u32 size;	/* size of identifier in u32 */
	u32 r_pos;
	u32 w_pos;
	u32 identifier[0];
} __packed;

/* ============================ [ DECLARES  ] ====================================================== */
static int start(struct rproc *rproc);
static int stop(struct rproc *rproc);
static void kick(struct rproc *rproc, int vqid);
/* ============================ [ DATAS     ] ====================================================== */
static struct device rpdev = {
	.name = "remote processor AUTOSAR ECU",
	.address = NULL,
	.size    = 0
};
static struct rproc* rproc;
static const struct rproc_ops rproc_ops=
{
	.start = start,
	.stop  = stop,
	.kick  = kick
};

static struct rsc_fifo* r_fifo;
static struct rsc_fifo* w_fifo;
static void* virtio;
/* ============================ [ LOCALS    ] ====================================================== */
static bool fifo_write(u32 id)
{
	bool ercd;
#ifdef __WINDOWS__
	WaitForSingleObject(rpdev.w_lock,INFINITE);
#else
	(void)pthread_mutex_lock((pthread_mutex_t *)rpdev.w_lock);
#endif
	if(w_fifo->count < w_fifo->size)
	{
		w_fifo->identifier[w_fifo->w_pos] = id;
		w_fifo->w_pos = (w_fifo->w_pos + 1)%(w_fifo->size);
		w_fifo->count += 1;
		ASLOG(0,"fifo_write(%x) fifo=%x lock=%x event=%x\n",id, w_fifo, rpdev.w_lock, rpdev.w_event);
		ASLOG(AS_LOG_RPROC,"Transmit message: 0x%X\n",id);
		ercd = true;
	}
	else
	{
		asAssert(0);
		ercd = false;
	}
#ifdef __WINDOWS__
	ReleaseMutex(rpdev.w_lock);
	SetEvent( rpdev.w_event );
#else
	(void)pthread_mutex_unlock( (pthread_mutex_t *)rpdev.w_lock );
	(void)pthread_cond_signal ((pthread_cond_t *)rpdev.w_event);
#endif
	return ercd;
}
static bool fifo_read(u32* id)
{
    bool ercd;
    if(r_fifo->count > 0)
    {
        *id = r_fifo->identifier[r_fifo->r_pos];
        r_fifo->r_pos = (r_fifo->r_pos + 1)%(r_fifo->size);
        r_fifo->count -= 1;
        ASLOG(0,"fifo_read(%x) fifo=%x lock=%x event=%x\n",*id, r_fifo, rpdev.r_lock, rpdev.r_event);
        ASLOG(AS_LOG_RPROC,"Incoming message: 0x%X\n",*id);
        ercd = true;
    }
    else
    {
        ercd  = false;
    }
    return ercd;
}
static void virtio_add_devices(void)
{
	virtio_add_can(rproc);
}
#ifdef __WINDOWS__
static DWORD virtio_run(LPVOID lpParameter)
#else
static void* virtio_run(void* lpParameter)
#endif
{
#ifdef __WINDOWS__
	HANDLE pvObjectList[ 2 ];
#endif
	uint32 id;
	bool ercd;
#ifdef __WINDOWS__
	pvObjectList[ 0 ] = rpdev.r_lock;
	pvObjectList[ 1 ] = rpdev.r_event;
#endif
	ASLOG(0,"virtio_run daemon is on-line fifo=%x lock=%x event=%x\n",r_fifo, rpdev.r_lock, rpdev.r_event);
	virtio_add_devices();
	while(true)
	{
#ifdef __WINDOWS__
		WaitForMultipleObjects( sizeof( pvObjectList ) / sizeof( HANDLE ), pvObjectList, TRUE, INFINITE );
#else
		(void)pthread_cond_wait ((pthread_cond_t *)rpdev.r_event,(pthread_mutex_t *)rpdev.r_lock);
#endif
		do {
			ercd = fifo_read(&id);
			if(ercd)
			{

			}
			else
			{
				/* do nothing as empty */
			}
		}while(ercd);
#ifdef __WINDOWS__
		ReleaseMutex( rpdev.r_lock );
#else
		(void)pthread_mutex_unlock( (pthread_mutex_t *)rpdev.r_lock );
#endif
	}
	return 0;
}
static int start(struct rproc *rproc)
{
#ifdef __WINDOWS__
	virtio = CreateThread( NULL, 0, virtio_run, NULL, 0, NULL );
#else
	pthread_create((pthread_t*)&virtio,NULL,virtio_run,NULL);
	usleep(1);/*make sure virtio_run daemon run firstly */
#endif
	if( virtio != NULL )
	{
#ifdef __WINDOWS__
		SetThreadPriority( virtio, THREAD_PRIORITY_BELOW_NORMAL );
		SetThreadPriorityBoost( virtio, TRUE );
		SetThreadAffinityMask( virtio, 0x01 );
#endif
	}
	else
	{
		asAssert(0);
	}
	return 0;
}
static int stop(struct rproc *rproc)
{
	return 0;
}
static void kick(struct rproc *rproc, int vqid)
{

}
/* ============================ [ FUNCTIONS ] ====================================================== */
void InitOS(void)
{
	struct device* dev;
	if(NULL != rpdev.address)
	{
		dev = &rpdev;
		/* init FIFO */
		dev->size = dev->size - dev->sz_fifo*2*sizeof(u32);

		r_fifo = (struct rsc_fifo*)((unsigned long)dev->address + dev->size + 0*dev->sz_fifo*sizeof(u32));
		w_fifo = (struct rsc_fifo*)((unsigned long)dev->address + dev->size + 1*dev->sz_fifo*sizeof(u32));

		r_fifo->count = 0;
		r_fifo->size  = dev->sz_fifo - sizeof(struct rsc_fifo)/sizeof(u32);
		r_fifo->r_pos = 0;
		r_fifo->w_pos = 0;
		memset(r_fifo->identifier,0,r_fifo->size*sizeof(u32));

		w_fifo->count = 0;
		w_fifo->size  = dev->sz_fifo - sizeof(struct rsc_fifo)/sizeof(u32);
		w_fifo->r_pos = 0;
		w_fifo->w_pos = 0;
		memset(w_fifo->identifier,0,w_fifo->size*sizeof(u32));
		/* inti remote processor */
		rproc = rproc_alloc(&rpdev,"AsRproc",&rproc_ops,NULL,1024);
	}
	else
	{
		//asAssert(0);
	}
}

bool AsRproc_Init(void* address, size_t size,void* r_lock,void* w_lock,void* r_event, void* w_event, size_t sz_fifo)
{

	bool bOK = false;
	if(NULL == rpdev.address)
	{
		rpdev.address = address;
		rpdev.size    = size;
		rpdev.sz_fifo = sz_fifo;
		rpdev.r_lock  = r_lock;
		rpdev.w_lock  = w_lock;
		rpdev.r_event = r_event;
		rpdev.w_event = w_event;
		bOK = true;
	}
	return bOK;
}

