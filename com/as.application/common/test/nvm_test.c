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
#include "Std_Types.h"
#include "tester.h"
#if defined(USE_FEE)
#include "Fee.h"
#endif

#if defined(USE_EA)
#include "Ea.h"
#endif
#if defined(USE_NVM)
#include "NvM.h"
#endif
#if defined(USE_DEM)
#include "Dem.h"
#endif
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
typedef struct
{
	uint16 year;
	uint8  month;
	uint8  day;
	uint8  hour;
	uint8  minute;
	uint8  second;
}App_TimeType;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
static App_TimeType SystemTime =
{
	.year   = 2013,
	.month  = 12,
	.day    = 15,
	.hour   = 19,
	.minute = 49,
	.second = 0
};
/* ============================ [ LOCALS    ] ====================================================== */

#ifdef USE_FEE_TEST
static void Fee_Test(void)
{
	static uint8 stage = 0;
	static uint32 Flag;
	static uint32 Flag_Read;
	static App_TimeType SystemTime_Read;

	if(0 == stage)
	{
		Flag = 0xABCD55FF;
		Fee_Write(FEE_BLOCK_NUM_Config,(uint8*)&Flag);
	}
	else if(1 == stage)
	{
		printf("Year=%d,Month=%d,Day=%d,Hour=%d,Minute=%d,Second=%d\n",
				SystemTime_Read.year,SystemTime_Read.month,SystemTime_Read.day,
				SystemTime_Read.hour,SystemTime_Read.minute,SystemTime_Read.second);
		Fee_Read(FEE_BLOCK_NUM_Config,0,(uint8*)&Flag_Read,4);
	}
	else if(2 == stage)
	{
		Flag = 0xDEADBEEF;
		Fee_Write(FEE_BLOCK_NUM_FingerPrint,(uint8*)&Flag);
	}
	else if(3 == stage)
	{
		printf("Flag=0x%X\n",Flag_Read);
		Fee_Read(FEE_BLOCK_NUM_FingerPrint,0,(uint8*)&Flag_Read,4);
	}
	else if(4 == stage)
	{
		Fee_Write(FEE_BLOCK_NUM_Time,(uint8*)&SystemTime);
	}
	else if(5 == stage)
	{
		printf("Flag=0x%X\n",Flag_Read);
		Fee_Read(FEE_BLOCK_NUM_Time,0,(uint8*)&SystemTime_Read,sizeof(App_TimeType));
	}
	stage ++;
	if(stage > 5)
	{
		stage = 0;
	}
}
#endif

#ifdef USE_NVM_TEST
static void NvM_Test(void)
{
//	NvM_ReadBlock(NVM_BLOCK_ID_Time,(uint8*)&NvM_BlockTime_DataGroup_RAM);
//	printf("NvM>>> Year=%d,Month=%d,Day=%d,Hour=%d,Minute=%d,Second=%d\n",
//			NvM_BlockTime_DataGroup_RAM.Year,NvM_BlockTime_DataGroup_RAM.Month,NvM_BlockTime_DataGroup_RAM.Day,
//			NvM_BlockTime_DataGroup_RAM.Hour,NvM_BlockTime_DataGroup_RAM.Minute,NvM_BlockTime_DataGroup_RAM.Second);
#ifdef USE_FEE
	printf("NvM>>> Year=%d,Month=%d,Day=%d,Hour=%d,Minute=%d,Second=%d\n",
			Rte_NvMRead(Time,Year),Rte_NvMRead(Time,Month),Rte_NvMRead(Time,Day),
			Rte_NvMRead(Time,Hour),Rte_NvMRead(Time,Minute),Rte_NvMRead(Time,Second));
#endif
#ifdef USE_EA
	printf("NvM>> EaTest1 = [0x%X,0x%X,0x%X,0x%X]\n",
			Rte_NvMRead(EaTest1,Data0),Rte_NvMRead(EaTest1,Data1),
			Rte_NvMRead(EaTest1,Data2),Rte_NvMRead(EaTest1,Data3));

	printf("NvM>> EaTest2 = [0x%X,0x%X,0x%X,0x%X]\n",
			Rte_NvMRead(EaTest2,Data1),Rte_NvMRead(EaTest2,Data2),
			Rte_NvMRead(EaTest2,Data3),Rte_NvMRead(EaTest2,Data4));
#endif
#ifdef USE_FEE
	Rte_NvMWrite(Time,Year,SystemTime.year);
	Rte_NvMWrite(Time,Month,SystemTime.month);
	Rte_NvMWrite(Time,Day,SystemTime.day);
	Rte_NvMWrite(Time,Hour,SystemTime.hour);
	Rte_NvMWrite(Time,Minute,SystemTime.minute);
	Rte_NvMWrite(Time,Second,SystemTime.second);
#endif
#ifdef USE_EA
	Rte_NvMWrite(EaTest1,Data0,0xDEADBEEF);
	Rte_NvMWrite(EaTest1,Data1,0xAABBCCDD);
	Rte_NvMWrite(EaTest1,Data2,0xFFAA33BB);
	Rte_NvMWrite(EaTest1,Data3,0x12345678);

	Rte_NvMWrite(EaTest2,Data1,0xABCDEFA);
	Rte_NvMWrite(EaTest2,Data2,0x12345678);
	Rte_NvMWrite(EaTest2,Data3,0xBB994567);
	Rte_NvMWrite(EaTest2,Data4,0x12345678);
#endif
#ifdef USE_FEE
	if(SystemTime.second%3 == 0)
	{
		Rte_NvmWriteBlock(Time);
	}
	else if(SystemTime.second%5 == 0)
	{
		Rte_NvmWriteBlock(EaTest1);
	}
	else if(SystemTime.second%7 == 0)
	{
		Rte_NvmWriteBlock(EaTest2);
	}
	else
	{
		memcpy(Rte_NvMReadBuffer(FingerPrint),"Test by parai@foxmail.com\n",26);
		Rte_NvmWriteBlock(FingerPrint);
	}
#endif
}
#endif
#ifdef USE_EA_TEST
static void Ea_Test(void)
{
	static uint32 caller = 0;
	static uint8 buffer[512];
	caller ++;
	switch(caller)
	{
		case 5:
			for(int i=0;i<260;i++)
			{
				buffer[i] = i;
			}
			if(E_OK != Ea_Write(1,buffer))
			{
				printf("## Request Write failed\n");
			}
			break;
		case 6:
			memset(buffer,0,512);
			if(E_OK != Ea_Read(1,0,buffer,16))
			{
				printf("## Request Read failed\n");
			}
			break;
		case 7:
			printf("Buffer = [");
			for(int i=0;i<260;i++)
			{
				printf("%-2X,",buffer[i]);
			}
			printf("]\n");
			break;
		default:
			break;
	}
}
#endif
#ifdef USE_DEM_TEST
static void Dem_Test(void)
{
	uint8 status = -1;
	Dem_GetEventStatus(DEM_EVENT_ID_AIRBAG_FAILED,&status);
	Dem_SetOperationCycleState(DEM_IGNITION,DEM_CYCLE_STATE_START);
	printf("DEM airbag status is 0x%X\n",status);
	asmem("DTC", NvM_Block_DemFreezeFrame_DataGroup_RAM, sizeof(NvM_Block_DemFreezeFrame_DataGroup_RAM[0]));
	if(DEM_TEST_FAILED_THIS_OPERATION_CYCLE != status)
	{
		Dem_ReportErrorStatus(DEM_EVENT_ID_AIRBAG_FAILED,DEM_EVENT_STATUS_FAILED);
	}
	else
	{
		Dem_ReportErrorStatus(DEM_EVENT_ID_AIRBAG_FAILED,DEM_EVENT_STATUS_PASSED);
	}
}
#endif
/* ============================ [ FUNCTIONS ] ====================================================== */
void tester_time_1000ms_runnable(void)
{
	static boolean called = False;
	if(!called)
	{
#ifdef USE_NVM
#if 0
		SystemTime.year   = Rte_NvMRead(Time,Year,SystemTime.year);
		SystemTime.month  = Rte_NvMRead(Time,Month,SystemTime.month);
		SystemTime.day    = Rte_NvMRead(Time,Day,SystemTime.day);
		SystemTime.hour   = Rte_NvMRead(Time,Hour,SystemTime.hour);
		SystemTime.minute = Rte_NvMRead(Time,Minute,SystemTime.minute);
		SystemTime.second = Rte_NvMRead(Time,Second,SystemTime.second);
#else
		memcpy(&SystemTime,Rte_NvMReadBuffer(Time),sizeof(App_TimeType));
#endif
#endif
	}
	SystemTime.second ++;
	if(SystemTime.second > 59)
	{
		SystemTime.second = 0;
		SystemTime.minute ++;
		if(SystemTime.minute > 59)
		{
			SystemTime.minute = 0;
			SystemTime.hour ++;
			if(SystemTime.hour > 23)
			{
				SystemTime.hour = 0;
				SystemTime.day++;
				if(SystemTime.day > 30)	//be easy, I just give a example
				{
					SystemTime.day = 0;
					SystemTime.month ++;
					if(SystemTime.month > 12)
					{
						SystemTime.month = 0;
						SystemTime.year ++;
					}
				}
			}
		}
	}
}
void tester_nvm_1000ms_runnable(void)
{
	#ifdef USE_FEE_TEST
	Fee_Test();
	#endif
	#ifdef USE_EA_TEST
	Ea_Test();
	#endif
	#ifdef USE_NVM_TEST
	NvM_Test();
	#endif
	#ifdef USE_DEM_TEST
	Dem_Test();
	#endif
}
