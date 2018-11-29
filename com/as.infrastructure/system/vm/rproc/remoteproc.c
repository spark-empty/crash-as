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

/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */

/* ============================ [ DATAS     ] ====================================================== */

/* ============================ [ LOCALS    ] ====================================================== */

/* ============================ [ FUNCTIONS ] ====================================================== */
/**
 * rproc_alloc() - allocate a remote processor handle
 * @dev: the underlying device
 * @name: name of this remote processor
 * @ops: platform-specific handlers (mainly start/stop)
 * @firmware: name of firmware file to load, can be NULL
 * @len: length of private data needed by the rproc driver (in bytes)
 *
 * Allocates a new remote processor handle, but does not register
 * it yet. if @firmware is NULL, a default name is used.
 *
 * This function should be used by rproc implementations during initialization
 * of the remote processor.
 *
 * After creating an rproc handle using this function, and when ready,
 * implementations should then call rproc_add() to complete
 * the registration of the remote processor.
 *
 * On success the new rproc is returned, and on failure, NULL.
 *
 * Note: _never_ directly deallocate @rproc, even if it was not registered
 * yet. Instead, when you need to unroll rproc_alloc(), use rproc_put().
 */
struct rproc *rproc_alloc(struct device* dev, const char *name,
				const struct rproc_ops *ops,
				const char *firmware, int len)
{
	struct rproc *rproc = NULL;
	struct fw_rsc_hdr* rsc_hdr;
	int i;

	size_t rsc_entry_size = 0;

	if (!dev || !name || !ops)
	{
		return NULL;
	}

	rproc = kzalloc(sizeof(struct rproc) + len, GFP_KERNEL);
	if (!rproc) {
		return NULL;
	}
	/* RSC_CARVEOUT */
	if(rsc_entry_size < (sizeof(struct fw_rsc_carveout)))
	{
		rsc_entry_size = sizeof(struct fw_rsc_carveout);
	}
	/* RSC_DEVMEM */
	if(rsc_entry_size < (sizeof(struct fw_rsc_devmem)))
	{
		rsc_entry_size = sizeof(struct fw_rsc_devmem);
	}
	/* RSC_TRACE */
	if(rsc_entry_size < (sizeof(struct fw_rsc_trace)))
	{
		rsc_entry_size = sizeof(struct fw_rsc_trace);
	}
	/* RSC_VDEV */
	if(rsc_entry_size < (sizeof(struct fw_rsc_vdev) + RVDEV_NUM_VRINGS*sizeof(struct fw_rsc_vdev_vring)))
	{
		rsc_entry_size = sizeof(struct fw_rsc_vdev) + RVDEV_NUM_VRINGS*sizeof(struct fw_rsc_vdev_vring);
	}

	rproc->dev = dev;

	rproc->max_rsc_entry = dev->size/rsc_entry_size;
	rproc->max_rsc_entry = rproc->max_rsc_entry - (rproc->max_rsc_entry*4+rsc_entry_size-1)/rsc_entry_size;

	rproc->name = name;
	rproc->ops = ops;
	rproc->priv = &rproc[1];

	rproc->state = RPROC_OFFLINE;

	rproc->table_ptr = (struct resource_table*)dev->address;
	rproc->table_ptr->ver = 0x00000001;/* 00.01 */
	rproc->table_ptr->num = 0;
	rproc->table_ptr->reserved[0] = 0;
	rproc->table_ptr->reserved[1] = 0;

	for(i=0;i<rproc->max_rsc_entry;i++)
	{
		rproc->table_ptr->offset[i] = ((unsigned long)&(rproc->table_ptr->offset[rproc->max_rsc_entry]))+i*rsc_entry_size	-
				(unsigned long)rproc->table_ptr;
		rsc_hdr = (struct fw_rsc_hdr*) ((unsigned long)rproc->table_ptr + rproc->table_ptr->offset[i]);
		rsc_hdr->type = RSC_LAST;
	}

	rproc->ops->start(rproc);
	return rproc;
}

