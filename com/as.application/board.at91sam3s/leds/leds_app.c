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
#include "board.h"

/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
static TimerType ledTimer;
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
KSM(LEDsAPP,Init)
{
	LED_Configure(LED_BLUE);
	LED_Configure(LED_RED);
	LED_Configure(LED_GREEN);
	LED_Set(LED_RED);

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
		//LED_Toggle(LED_BLUE);
		//LED_Toggle(LED_RED);
		LED_Toggle(LED_GREEN);
		StartTimer(&ledTimer);
	}
}
