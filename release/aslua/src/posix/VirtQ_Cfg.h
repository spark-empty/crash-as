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
#ifndef COM_AS_APPLICATION_COMMON_CONFIG_VIRQ_CFG_H_
#define COM_AS_APPLICATION_COMMON_CONFIG_VIRQ_CFG_H_
/* ============================ [ INCLUDES  ] ====================================================== */

/* ============================ [ MACROS    ] ====================================================== */
#define VIRTQ_CHL_RPMSG_RX  ((VirtQ_ChannerlType)0)
#define VIRTQ_CHL_RPMSG_TX  ((VirtQ_ChannerlType)1)
#define VIRTQ_CHL_NUM		((VirtQ_ChannerlType)2)
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
extern const VirtQ_ConfigType VirtQ_Config;
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */

#endif /* COM_AS_APPLICATION_COMMON_CONFIG_VIRQ_CFG_H_ */
