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
#ifdef USE_STMO
#include "Stmo.h"

static const Stmo_ChannelType StmoChannels[] =
{
	{ /* Speed */
		.SoftwareZero = 15100,
		.Direction = STMO_DIR_CLOCKWISE
	},
	{ /* Tacho */
		.SoftwareZero = 15100,
		.Direction = STMO_DIR_CLOCKWISE
	},
	{ /* Temperature */
		.SoftwareZero = 13100,
		.Direction = STMO_DIR_CLOCKWISE
	},
	{ /* Fuel */
		.SoftwareZero = 4800,
		.Direction = STMO_DIR_ANTICLOCKWISE
	}

};

const Stmo_ConfigType Stmo_ConfigData =
{
	.Channels = StmoChannels
};
#endif
