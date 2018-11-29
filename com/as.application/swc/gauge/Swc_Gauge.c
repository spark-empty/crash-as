/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2018  AS <parai@foxmail.com>
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
#include "Rte_Gauge.h"
#ifdef USE_STMO
#include "Stmo.h"
#endif

#ifdef USE_COM
#include "Com.h"
#endif
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
#ifdef USE_STMO
static void sample_pointer(void)
{
#ifdef COM_SID_VehicleSpeed
	uint16 VehicleSpeed = 0;
#endif
#ifdef COM_SID_TachoSpeed
	uint16 TachoSpeed = 0;
#endif

	static Stmo_DegreeType tacho = 0;
	static Stmo_DegreeType speed = 0;
	static Stmo_DegreeType temp = 0;
	static Stmo_DegreeType fuel = 0;
	static boolean tacho_up = TRUE;
	static boolean speed_up = TRUE;
	static boolean temp_up = TRUE;
	static boolean fuel_up = TRUE;

#ifdef COM_SID_TachoSpeed
	(void)Com_ReceiveSignal(COM_SID_TachoSpeed,&TachoSpeed);
	tacho = TachoSpeed;
#else
	if(tacho_up)
	{
		tacho += 50;
		if(tacho >=  24000)
		{
			tacho = 24000;
			tacho_up = FALSE;
		}
	}
	else
	{
		if(tacho > 100)
		{
			tacho -= 100;
		}
		else
		{
			tacho = 0;
			tacho_up = TRUE;
		}
	}
#endif

#ifdef COM_SID_VehicleSpeed
	(void)Com_ReceiveSignal(COM_SID_VehicleSpeed,&VehicleSpeed);
	speed = VehicleSpeed;
#else
	if(speed_up)
	{
		speed += 50;
		if(speed >=  24000)
		{
			speed = 24000;
			speed_up = FALSE;
		}
	}
	else
	{
		if(speed > 100)
		{
			speed -= 100;
		}
		else
		{
			speed = 0;
			speed_up = TRUE;
		}
	}
#endif
	if(temp_up)
	{
		temp += 50;
		if(temp >=  9700)
		{
			temp = 9700;
			temp_up = FALSE;
		}
	}
	else
	{
		if(temp > 50)
		{
			temp -= 50;
		}
		else
		{
			temp = 0;
			temp_up = TRUE;
		}
	}

	if(fuel_up)
	{
		fuel += 50;
		if(fuel >=  9700)
		{
			fuel = 9700;
			fuel_up = FALSE;
		}
	}
	else
	{
		if(fuel > 50)
		{
			fuel -= 50;
		}
		else
		{
			fuel = 0;
			fuel_up = TRUE;
		}
	}

	Stmo_SetPosDegree(STMO_ID_SPEED,speed);
	Stmo_SetPosDegree(STMO_ID_TACHO,tacho);
	Stmo_SetPosDegree(STMO_ID_TEMP,temp);
	Stmo_SetPosDegree(STMO_ID_FUEL,fuel);

}
#endif
/* ============================ [ FUNCTIONS ] ====================================================== */
void Gauge_Run(void)
{
#ifdef USE_STMO
	sample_pointer();
#endif
}
