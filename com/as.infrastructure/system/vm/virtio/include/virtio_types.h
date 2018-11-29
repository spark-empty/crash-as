#ifndef _UAPI_LINUX_VIRTIO_TYPES_H
#define _UAPI_LINUX_VIRTIO_TYPES_H
/* Type definitions for virtio implementations.
 *
 * This header is BSD licensed so anyone can use the definitions to implement
 * compatible drivers/servers.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of IBM nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL IBM OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * Copyright (C) 2014 Red Hat, Inc.
 * Author: Michael S. Tsirkin <mst@redhat.com>
 */
#include "Std_Types.h"
#include <stdlib.h>
#include <errno.h>

#define __bitwise__
#define __bitwise
#define __user
#define __force

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#ifndef __packed
# define __packed		__attribute__((__packed__))
#endif

#define VIRTIO_ID_NET		1 /* virtio net */
#define VIRTIO_ID_BLOCK		2 /* virtio block */
#define VIRTIO_ID_CONSOLE	3 /* virtio console */
#define VIRTIO_ID_RNG		4 /* virtio rng */
#define VIRTIO_ID_BALLOON	5 /* virtio balloon */
#define VIRTIO_ID_RPMSG		7 /* virtio remote processor messaging */
#define VIRTIO_ID_SCSI		8 /* virtio scsi */
#define VIRTIO_ID_9P		9 /* 9p virtio console */
#define VIRTIO_ID_RPROC_SERIAL 11 /* virtio remoteproc serial link */
#define VIRTIO_ID_CAIF	       12 /* Virtio caif */
#define VIRTIO_ID_INPUT        18 /* virtio input */

#define kfree(ptr)   free(ptr)
#define kmalloc(size,flag) malloc(size)
#define kzalloc(size,flag) kzmalloc(size)

typedef uint8  __u8;
typedef uint16 __u16;
typedef uint32 __u32;
typedef uint64 __u64;

typedef __u16 __bitwise __le16;
typedef __u16 __bitwise __be16;
typedef __u32 __bitwise __le32;
typedef __u32 __bitwise __be32;
typedef __u64 __bitwise __le64;
typedef __u64 __bitwise __be64;

typedef uint8  u8;
typedef uint16 u16;
typedef uint32 u32;
typedef uint64 u64;
/*
 * A dma_addr_t can hold any valid DMA address, i.e., any address returned
 * by the DMA API.
 *
 * If the DMA API only uses 32-bit addresses, dma_addr_t need only be 32
 * bits wide.  Bus addresses, e.g., PCI BARs, may be wider than 32 bits,
 * but drivers do memory-mapped I/O to ioremapped kernel virtual addresses,
 * so they don't care about the size of the actual bus addresses.
 */
#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
typedef u64 dma_addr_t;
#else
typedef u32 dma_addr_t;
#endif

struct device
{
	char* name;
	void* address;	/* address of the hardware device */
	size_t size;	/* size limit of the hardware device in byte */
	size_t sz_fifo; /* size of the fifo for communication in u32 */
	void* r_lock;	/* read access lock */
	void* w_lock;	/* write access lock */
	void* r_event;  /* data in-coming event */
	void* w_event;  /* data out-going event */
};
typedef unsigned __bitwise__ gfp_t;
/*
 * __virtio{16,32,64} have the following meaning:
 * - __u{16,32,64} for virtio devices in legacy mode, accessed in native endian
 * - __le{16,32,64} for standard-compliant virtio devices
 */

typedef __u16 __bitwise__ __virtio16;
typedef __u32 __bitwise__ __virtio32;
typedef __u64 __bitwise__ __virtio64;

/**
 * kzalloc - allocate memory. The memory is set to zero.
 * @size: how many bytes of memory are required.
 * @flags: the type of memory to allocate (see kmalloc).
 */
static inline void *kzmalloc(size_t size/*, gfp_t flags*/)
{
	void * p_mem = kmalloc(size, flags | __GFP_ZERO);
	if(NULL != p_mem)
	{
		memset(p_mem,0,size);
	}
	return p_mem;
}

#endif /* _UAPI_LINUX_VIRTIO_TYPES_H */
