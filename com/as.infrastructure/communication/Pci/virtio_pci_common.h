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
#ifndef _VIRTIO_PCI_COMMON_H_
#define _VIRTIO_PCI_COMMON_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "pci_core.h"
#include "virtio_ring.h"
/* ============================ [ MACROS    ] ====================================================== */
/* Documentation:
 * http://ozlabs.org/~rusty/virtio-spec/virtio-0.9.5.pdf, appendix C
 * http://docs.oasis-open.org/virtio/virtio/v1.0/cs04/virtio-v1.0-cs04.html
 */

/*Virtual I/O Device (VIRTIO) Version 1.0, Spec 4, section 5.1.3:  Feature bits */
#define VIRTIO_CSUM                 0
#define VIRTIO_GUEST_CSUM           1
#define VIRTIO_CTRL_GUEST_OFFLOADS  2
#define VIRTIO_MAC                  5
#define VIRTIO_GUEST_TSO4           7
#define VIRTIO_GUEST_TSO6           8
#define VIRTIO_GUEST_ECN            9
#define VIRTIO_GUEST_UFO            10
#define VIRTIO_HOST_TSO4            11
#define VIRTIO_HOST_TSO6            12
#define VIRTIO_HOST_ECN             13
#define VIRTIO_HOST_UFO             14
#define VIRTIO_MRG_RXBUF            15
#define VIRTIO_STATUS               16
#define VIRTIO_CTRL_VQ              17
#define VIRTIO_CTRL_RX              18
#define VIRTIO_CTRL_VLAN            19
#define VIRTIO_CTRL_RX_EXTRA        20
#define VIRTIO_GUEST_ANNOUNCE       21
#define VIRTIO_MQ                   22
#define VIRTIO_CTRL_MAC_ADDR        23
#define VIRTIO_EVENT_IDX            29

#define VIRTIO_ACKNOWLEDGE 1
#define VIRTIO_DRIVER 2
#define VIRTIO_FAILED 128
#define VIRTIO_FEATURES_OK 8
#define VIRTIO_DRIVER_OK 4
#define VIRTIO_DEVICE_NEEDS_RESET 64

#define VIRTIO_DESC_FLAG_NEXT           1
#define VIRTIO_DESC_FLAG_WRITE_ONLY     2
#define VIRTIO_DESC_FLAG_INDIRECT       4

#define VIRTIO_NET_HDR_F_NEEDS_CSUM    1
#define VIRTIO_NET_HDR_GSO_NONE        0
#define VIRTIO_NET_HDR_GSO_TCPV4       1
#define VIRTIO_NET_HDR_GSO_UDP         3
#define VIRTIO_NET_HDR_GSO_TCPV6       4
#define VIRTIO_NET_HDR_GSO_ECN         0x80
/* ============================ [ TYPES     ] ====================================================== */
typedef struct virtqueue
{
	/* Shared state */
	Vring_Type vring;

	uint32 last_used_index;
	uint32 last_avail_idx;
	uint32 free_head;
	uint32 num_added;

	uint32 idx;
	uint16 iobase;

}VirtQ_QueueType;

typedef struct
{
	uint32 number;
	VirtQ_QueueType* vq;
	pci_dev* pdev;
}VirtPci_DeviveType;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void virtio_pci_setup_vqs(pci_dev* pdev);
void virtio_enable_interrupts(VirtQ_QueueType* vq);
void virtio_disable_interrupts(VirtQ_QueueType* vq);
void virtio_add_buffer(VirtQ_QueueType* vq, void* buf, uint32 len);
void virtio_kick(VirtQ_QueueType* vq);
#endif /* _VIRTIO_PCI_COMMON_H_ */
