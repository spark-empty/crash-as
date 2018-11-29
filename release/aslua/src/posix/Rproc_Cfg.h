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
#ifndef COM_AS_APPLICATION_COMMON_CONFIG_RPROC_CFG_H_
#define COM_AS_APPLICATION_COMMON_CONFIG_RPROC_CFG_H_
/* ============================ [ INCLUDES  ] ====================================================== */

/* ============================ [ MACROS    ] ====================================================== */
#define RPROC_RSC_NUM  1
#define RPROC_RPMSG_CFG_SIZE  16

#define RPROC_RPMSG_FEATURES (1 << 0)
/* ============================ [ TYPES     ] ====================================================== */
typedef struct
{
	uint32 version;
	uint32 num;
	uint32 reserved[2];
	uint32 offset[RPROC_RSC_NUM];  /* Should match 'num' in actual definition */
	Rproc_ResourceVdevType rpmsg_vdev;
#if RPROC_RPMSG_CFG_SIZE > 0 /* @config_len of Rproc_ResourceVdevType */
	uint8                 rpmsg_cfg[RPROC_RPMSG_CFG_SIZE];
#endif
}Rproc_ResourceTableType;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
extern VAR(Rproc_ResourceTableType, MEM_RPROC_RESOURCE_TABLE) Rproc_ResourceTable;
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */

#endif /* COM_AS_APPLICATION_COMMON_CONFIG_RPROC_CFG_H_ */
