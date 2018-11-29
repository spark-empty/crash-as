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
 *
 * This file content is copied form linux source code and then modified
 */
#ifndef COM_AS_INFRASTRUCTURE_COMMUNICATION_RPMSG_VIRTIO_RING_H_
#define COM_AS_INFRASTRUCTURE_COMMUNICATION_RPMSG_VIRTIO_RING_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
/* ============================ [ MACROS    ] ====================================================== */
/* This marks a buffer as continuing via the next field. */
#define VRING_DESC_F_NEXT	1
/* This marks a buffer as write-only (otherwise read-only). */
#define VRING_DESC_F_WRITE	2
/* This means the buffer contains a list of buffer descriptors. */
#define VRING_DESC_F_INDIRECT	4

/* The Host uses this in used->flags to advise the Guest: don't kick me when
 * you add a buffer.  It's unreliable, so it's simply an optimization.  Guest
 * will still kick if it's out of buffers. */
#define VRING_USED_F_NO_NOTIFY	1
/* The Guest uses this in avail->flags to advise the Host: don't interrupt me
 * when you consume a buffer.  It's unreliable, so it's simply an
 * optimization.  */
#define VRING_AVAIL_F_NO_INTERRUPT	1

/* We support indirect buffer descriptors */
#define VIRTIO_RING_F_INDIRECT_DESC	28

/* The Guest publishes the used index for which it expects an interrupt
 * at the end of the avail ring. Host should ignore the avail->flags field. */
/* The Host publishes the avail index for which it expects a kick
 * at the end of the used ring. Guest should ignore the used->flags field. */
#define VIRTIO_RING_F_EVENT_IDX		29

/* Alignment requirements for vring elements.
 * When using pre-virtio 1.0 layout, these fall out naturally.
 */
#define VRING_AVAIL_ALIGN_SIZE 2
#define VRING_USED_ALIGN_SIZE 4
#define VRING_DESC_ALIGN_SIZE 16
/* ============================ [ TYPES     ] ====================================================== */

/* Virtio ring descriptors: 16 bytes.  These can chain together via "next". */
typedef struct {
	/* Address (guest-physical). */
	uint64 addr;
	/* Length. */
	uint32 len;
	/* The flags as indicated above. */
	uint16 flags;
	/* We chain unused descriptors via this, too */
	uint16 next;
}Vring_DescType;

typedef struct {
	uint16 flags;
	uint16 idx;
	uint16 ring[];
}Vring_AvailType;

/* u32 is used here for ids for padding reasons. */
typedef struct {
	/* Index of start of used descriptor chain. */
	uint32 id;
	/* Total length of the descriptor chain which was used (written to) */
	uint32 len;
}Vring_UsedElemType;

typedef struct {
	uint16 flags;
	uint16 idx;
	Vring_UsedElemType ring[];
}Vring_UsedType;

typedef struct {
	uint32 num;	/* must be 2^n */

	Vring_DescType *desc;

	Vring_AvailType *avail;

	Vring_UsedType *used;
}Vring_Type;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
static inline void vring_init(Vring_Type *vr, uint32 num, void *p,
			      uint32 align)
{
	vr->num = num;
	vr->desc = p;
	vr->avail = p + num*sizeof(Vring_DescType);
	vr->used = (void *)(((unsigned long)(&vr->avail->ring[num]) + sizeof(uint16)
		+ align-1) & ~((unsigned long)align - 1));
}

static inline uint32 vring_size(uint32 num, uint32 align)
{
	return ((sizeof(Vring_DescType) * num + sizeof(uint16) * (3 + num)
		 + align - 1) & ~(align - 1))
		+ sizeof(uint16) * 3 + sizeof(Vring_UsedElemType) * num;
}
/* ============================ [ FUNCTIONS ] ====================================================== */

#endif /* COM_AS_INFRASTRUCTURE_COMMUNICATION_RPMSG_VIRTIO_RING_H_ */
