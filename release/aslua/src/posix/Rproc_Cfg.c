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
#include "VirtQ.h"
#include "Rproc.h"

/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/*
 * only 1 instance of resource table was configured, if 2, configured another 1 as:
 * VAR(Rproc_ResourceTable2Type, MEM_RPROC_RESOURCE_TABLE) Rproc_ResourceTable2.
 * and configure 2 IPC channels
 */
VAR(Rproc_ResourceTableType, MEM_RPROC_RESOURCE_TABLE) Rproc_ResourceTable = {
	.version = 1,
	.num     = RPROC_RSC_NUM,
	.reserved = { 0, 0 },
	.offset = {
		[0]=offsetof(Rproc_ResourceTableType, rpmsg_vdev),
	},
	.rpmsg_vdev =  {
		.type = RSC_VDEV,
		.id = VIRTIO_ID_RPMSG,
		.notifyid = 0,	/* This is not supported, as feature will never dynamic changed */
		.dfeatures = RPROC_RPMSG_FEATURES,
		.gfeatures = 0,
		.config_len = RPROC_RPMSG_CFG_SIZE,
		.status  = 0,
		.num_of_vrings = RPROC_NUM_OF_VRINGS,
		.reserved = {0,0},
		.vring[0] = {
			.da = 0,
			.align = 4096,
			.num   = 256,
			.notifyid = 0xdeadbeef,	/* will filled up by kernel */
			.reserved = 0
		},
		.vring[1] = {
			.da = 0,
			.align = 4096,
			.num   = 256,
			.notifyid = 0xdeadbeef,	/* will filled up by kernel */
			.reserved = 0
		},
	},
#if RPROC_RPMSG_CFG_SIZE > 0
	.rpmsg_cfg = { 0, }
#endif
};
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
Rproc_ResourceTableType* Qt_GetRprocResourceTable(void)
{
	return &Rproc_ResourceTable;
}

unsigned int Qt_GetRprocResourceTableSize(void)
{
	return sizeof(Rproc_ResourceTable);
}
