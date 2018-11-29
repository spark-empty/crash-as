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
#ifdef USE_PCI
/* ============================ [ INCLUDES  ] ====================================================== */
#include "virtio_net.h"
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
#define AS_LOG_VNET 1

#define FRAME_SIZE 1526 /* including the net_header */
/* ============================ [ TYPES     ] ====================================================== */
typedef struct
{
	u8* buffer;
	u64 size;
	u8 flags;

	// If the user wants to keep same buffer as passed in this struct, use "true".
	// otherwise, the supplied buffer will be copied in the queues' buffer
	u8 copy;
} buffer_info;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
static pci_dev *pdev = NULL;
/* ============================ [ LOCALS    ] ====================================================== */
static void handler(void)
{
	ASLOG(VNET,"virtio net isr happened\n");
}
/* ============================ [ FUNCTIONS ] ====================================================== */
void virtio_net_init(void)
{
	int i = 0;
	uint16 iobase=0;
	uint32 features,val;
	pdev = find_pci_dev_from_id(0x1af4, 0x1000);
	if(NULL == pdev) return;
	enable_pci_resource(pdev);
	iobase = pdev->io_addr[0];

	/* ref http://wiki.osdev.org/Virtio */
	ASLOG(VNET,"virtio net MAC=%02X:%02X:%02X:%02X:%02X:%02X\n",
			inb(iobase+0x14),inb(iobase+0x15),inb(iobase+0x16),
			inb(iobase+0x17),inb(iobase+0x18),inb(iobase+0x19));

	/* Virtual I/O Device (VIRTIO) Version 1.0, Spec 4, section 3.1.1:  Device Initialization */
	outb(iobase+0x12,VIRTIO_ACKNOWLEDGE);
	outb(iobase+0x12,VIRTIO_ACKNOWLEDGE | VIRTIO_DRIVER);

	features = inl(iobase+0x00);
	ASLOG(VNET,"virtio net supported features %08X\n", features);
	/* disable some features
	 * ref http://www.dumais.io/attachment-mongo.php?art=aca38a9a2b065b24dfa1dee728062a12&a=virtnet.c*/
	features &= ~((1<<VIRTIO_GUEST_TSO4) |
				  (1<<VIRTIO_GUEST_TSO6) |
				  (1<<VIRTIO_GUEST_UFO)  |
				  (1<<VIRTIO_EVENT_IDX)  |
				  (1<<VIRTIO_MRG_RXBUF) );
	/* enable some features */
	features |= 1<<VIRTIO_CSUM;
	outl(iobase+0x04,features);

	outb(iobase+0x12, VIRTIO_ACKNOWLEDGE | VIRTIO_DRIVER | VIRTIO_FEATURES_OK);

	val = inb(iobase+0x12);
	if(0 == (val&VIRTIO_FEATURES_OK))
	{
		ASLOG(ERROR," virtio net features NOK\n");
		return;
	}
	else
	{
		ASLOG(VNET, "features okay\n");
	}

	/* setup queues */
	virtio_pci_setup_vqs(pdev);

	pci_register_irq(pdev->irq_num, handler);
	enable_pci_interrupt(pdev);

	outb(iobase+0x12, VIRTIO_ACKNOWLEDGE | VIRTIO_DRIVER | VIRTIO_FEATURES_OK | VIRTIO_DRIVER_OK);
}

void virtio_net_start(void)
{
	VirtPci_DeviveType* dev;
	VirtQ_QueueType *rvq,*tvq;
	void* p;
	uint32 i;
	if(NULL == pdev) return;

	dev = pdev->priv;

	rvq = &(dev->vq[0]);
	tvq = &(dev->vq[1]);

	/* setup receive queue */
	for(i=0;i<rvq->vring.num;i++)
	{
		p = kzmalloc(FRAME_SIZE);
		asAssert(p);

		virtio_add_buffer(rvq, p, FRAME_SIZE);
	}



}

#endif /* USE_PCI */
