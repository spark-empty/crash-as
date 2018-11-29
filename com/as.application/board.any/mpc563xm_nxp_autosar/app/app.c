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
#include <stdio.h>
#ifdef USE_DIO
#include "Dio.h"
#endif

#ifdef USE_ADC
#include "Adc.h"
#endif

#ifdef USE_ANYOS
#include "os.h"
#endif
/* ============================ [ MACROS    ] ====================================================== */
#define DIO_PIN_LED1 188
#define DIO_PIN_LED2 189
#define DIO_PIN_LED3 190
#define DIO_PIN_LED4 191

#define DIO_PIN_KEY1 179
#define DIO_PIN_KEY2 181
#define DIO_PIN_KEY3 183
#define DIO_PIN_KEY4 187
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
#ifdef USE_ADC
static Adc_ValueGroupType adcValueGroup[ADC_CFGSET1_GROUP_0_CHANNELS];
#endif

#ifdef USE_ANYOS
extern const TaskType TASK_ID_TaskCanIf = TaskCanIf;
extern const TaskType TASK_ID_SchM_BswService = SchM_BswService;
extern const TaskType TASK_ID_SchM_Startup = SchM_Startup;
extern const TaskType TASK_ID_TaskApp = TaskApp;
extern const TaskType TASK_ID_TaskShell = TaskShell;
extern const TaskType TASK_ID_TaskIdle = TaskIdle;

extern const AlarmType ALARM_ID_AlarmApp = AlarmApp;
extern const AlarmType ALARM_ID_Alarm_BswService = Alarm_BswService;
#endif
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void App_MainFunction(void)
{
#ifdef USE_DIO
	static int lcc_Delay_Num = 0;
	//关闭其他led灯
	Dio_WriteChannel(DIO_PIN_LED2, 1);	
	Dio_WriteChannel(DIO_PIN_LED3, 1);	
	Dio_WriteChannel(DIO_PIN_LED4, 1);	
	//闪烁小灯
	if(++lcc_Delay_Num == 100){
		lcc_Delay_Num = 0;
		Dio_WriteChannel(DIO_PIN_LED1, ~Dio_ReadChannel(DIO_PIN_LED1));	
	}
#endif
}


void App_PeriodFunction1s(void)
{
#ifdef USE_ADC
	/*Adc_SetupResultBuffer(AdcGroup_0, adcValueGroup);
	Adc_StartGroupConversion(AdcGroup_0);

	printf("Adc value is %d\n", adcValueGroup[0]);*/
#endif
}
