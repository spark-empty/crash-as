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
#include "Os.h"
#include "stm32f10x.h"
#include "Dio.h"
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
static TimerType ledTimer;
static Dio_LevelType ioStsLed1;
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
KSM(LEDsAPP,Init)
{
	ioStsLed1 = STD_HIGH;

	/* turn off led2 and led3 */
	Dio_WriteChannel(DIO_CHL_LED2,STD_LOW);
	Dio_WriteChannel(DIO_CHL_LED3,STD_LOW);

	KGS(LEDsAPP,Start);
}
KSM(LEDsAPP,Start)
{
	StartTimer(&ledTimer);
	KGS(LEDsAPP,Running);
}
KSM(LEDsAPP,Stop)
{

}
KSM(LEDsAPP,Running)
{
	if(GetTimer(&ledTimer) > 500)
	{
		/* indicate the CPU is working */
		Dio_WriteChannel(DIO_CHL_LED1,ioStsLed1);
		ioStsLed1 = (STD_HIGH == ioStsLed1)? STD_LOW: STD_HIGH;
		StartTimer(&ledTimer);
	}
}
