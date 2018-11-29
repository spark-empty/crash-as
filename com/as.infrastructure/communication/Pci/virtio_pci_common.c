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
#ifdef USE_PCI
/* http://wiki.osdev.org/Virtio
 * https://github.com/pdumais/OperatingSystem */
/* ============================ [ INCLUDES  ] ====================================================== */
#include "virtio_pci_common.h"
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
#define AS_LOG_PCI 1
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */

/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void virtio_pci_setup_vqs(pci_dev* pdev)
{
	uint16 iobase = pdev->io_addr[0];
	u32 i, val, size;
	VirtPci_DeviveType* dev = kzmalloc(sizeof(VirtPci_DeviveType));
	asAssert(dev);

	dev->pdev = pdev;

	for(i=0;i<16;i++)
	{
		outl(iobase+0x0e,i);
		val = inl(iobase+0x0c);

		if(0 == val) break;
	}

	dev->number = i;
	dev->vq = kzmalloc(sizeof(VirtQ_QueueType)*dev->number);
	asAssert(dev->vq);

	for(i=0;i<dev->number;i++)
	{
		void* p;
		u32 j;
		outl(iobase+0x0e,i);
		val = inl(iobase+0x0c);
		size = vring_size(val,PAGE_SIZE);
		p = palloc(size);
		asAssert(p);
		vring_init(&(dev->vq[i].vring),val,p,PAGE_SIZE);
		ASLOG(PCI, "pci %04X:%04X vq[%d] number is %d, sum is %d bytes @ %p\n",
				pdev->vendor_id, pdev->device_id, i, val, size, p);

		for(j=0;j<(val-1);j++)
		{
			dev->vq[i].vring.desc[j].next = j+1;
		}

		dev->vq[i].num_added=0;
		dev->vq[i].free_head=0;
		dev->vq[i].last_used_index=0;
		dev->vq[i].last_avail_idx=0;
		dev->vq[i].idx = i;
		dev->vq[i].iobase = iobase;
		outl(iobase+0x08,((u32)p)/PAGE_SIZE);

		dev->vq[i].vring.avail->flags=0;
	}

	pdev->priv = (void*)dev;
}

void virtio_enable_interrupts(VirtQ_QueueType* vq)
{
	vq->vring.used->flags = 0;
}

void virtio_disable_interrupts(VirtQ_QueueType* vq)
{
	vq->vring.used->flags = 1;
}

void virtio_kick(VirtQ_QueueType* vq)
{
	outl(vq->iobase+0x10, vq->idx);
}

void virtio_add_buffer(VirtQ_QueueType* vq, void* buf, uint32 len)
{
	if(vq->num_added<vq->vring.num)
	{
		vq->vring.desc[vq->free_head].addr = (uint32) buf;
		vq->vring.desc[vq->free_head].len  = len;
		vq->vring.desc[vq->free_head].flags = VRING_DESC_F_NEXT;
		vq->free_head = vq->vring.desc[vq->free_head].next;
		vq->vring.avail->idx ++;
		vq->vring.avail->ring[vq->free_head] = vq->free_head;
		vq->num_added ++;

		virtio_kick(vq);
	}
	else
	{
		asAssert(0);
	}
}
#endif /* USE_PCI */
