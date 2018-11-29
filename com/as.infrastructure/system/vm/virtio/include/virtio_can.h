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
#ifndef COM_AS_INFRASTRUCTURE_SYSTEM_VM_VIRTIO_INCLUDE_VIRTIO_CAN_H_
#define COM_AS_INFRASTRUCTURE_SYSTEM_VM_VIRTIO_INCLUDE_VIRTIO_CAN_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "remoteproc.h"
/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
struct virtio_can
{
	struct rproc_vdev vdev;
};
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
extern void virtio_add_can(struct rproc* rproc);
#endif /* COM_AS_INFRASTRUCTURE_SYSTEM_VM_VIRTIO_INCLUDE_VIRTIO_CAN_H_ */
