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
#ifndef STMO_CFG_H_
#define STMO_CFG_H_

#define STMO_MAX_DEGREE  (36000)
#define STMO_ONE_DEGREE  (100)

#define STMO_ONE_STEP    (250*2)  // Degree Change in 1 Stmo_MainFunction call

typedef uint32_t Stmo_DegreeType;

typedef enum
{
	STMO_ID_SPEED,
	STMO_ID_TACHO,
	STMO_ID_TEMP,
	STMO_ID_FUEL,
	STMO_CFG_NUM
}Stmo_IdType;

typedef enum
{
	STMO_DIR_CLOCKWISE,
	STMO_DIR_ANTICLOCKWISE
}Stmo_DirectionType;

typedef struct
{
	Stmo_DegreeType SoftwareZero;
	Stmo_DirectionType Direction;

}Stmo_ChannelType;

typedef struct
{
	const Stmo_ChannelType* Channels;
}Stmo_ConfigType;

extern const Stmo_ConfigType Stmo_ConfigData;

#endif /* STMO_CFG_H_ */
