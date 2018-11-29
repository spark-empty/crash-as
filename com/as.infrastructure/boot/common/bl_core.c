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
#include "bootloader.h"
#include "Flash.h"
#include "Os.h"
#include "asdebug.h"
#include "CanIf.h"
#include "CanIf_Cbk.h"
/* ============================ [ MACROS    ] ====================================================== */
#define BL_FLASH_IDENTIFIER   0xFF
#define BL_EEPROM_IDENTIFIER  0xEE
#define BL_FLSDRV_IDENTIFIER  0xFD

#if defined(__LINUX__) || defined(__WINDOWS__)
#define FL_ERASE_PER_CYCLE 32
#else
#ifndef FL_ERASE_PER_CYCLE
#define FL_ERASE_PER_CYCLE 1
#endif
#endif
#define FL_WRITE_PER_CYCLE (4096/FLASH_WRITE_SIZE)
#define FL_READ_PER_CYCLE  (4096/FLASH_WRITE_SIZE)

#ifndef BL_STAY_TIME_MS
#define BL_STAY_TIME_MS 1000
#endif
/* ============================ [ TYPES     ] ====================================================== */
typedef struct
{
	uint32 addressLow;
	uint32 addressHigh;
	uint8  identifier;
	uint8  attr; /*attr: bit mask 0x04=READ 0x02=WRITE 0x01=EXECUTE */
} BL_MemoryInfoType;
/* ============================ [ DECLARES  ] ====================================================== */
extern void application_main(void); /* Symbol exposed in linker.lds */
extern uint32_t FlashDriverRam[];

extern void BL_SetAutoPRGS(void);
/* ============================ [ DATAS     ] ====================================================== */
static tFlashParam blFlashParam =
{
    .patchlevel  = FLASH_DRIVER_VERSION_PATCH,
    .minornumber = FLASH_DRIVER_VERSION_MINOR,
    .majornumber = FLASH_DRIVER_VERSION_MAJOR,
    .wdTriggerFct = NULL,
    .errorcode   = kFlashOk,
};
static uint8   blMemoryIdentifier;
static uint32  blMemoryAddress;
static uint32  blMemorySize;
static uint32* blMemoryData;
static TimerType appTimer;

static BL_MemoryInfoType blMemoryList[] = {
	/* STM32F017VC  */ { 0x00010000, 0x00040000, 0xFF, 0x04|0x02|0x01 },
	/* VERSATILEPB  */ { 0x00040000, 0x08000000, 0xFF, 0x04|0x02|0x01 },
	/* MPC56XX      */ { 0x00020000, 0x00180000, 0xFF, 0x04|0x02|0x01 },
	/* FLASH DRIVER */ { 0x00000000, 0x00001000, 0xFD, 0x04|0x02|0x01 },
};
/* ============================ [ LOCALS    ] ====================================================== */
static Dcm_ReturnEraseMemoryType eraseFlash(Dcm_OpStatusType OpStatus,uint32 MemoryAddress,uint32 MemorySize)
{
	Dcm_ReturnEraseMemoryType rv;
	uint32 length;
	switch(OpStatus)
	{
		case DCM_INITIAL:
			FLASH_DRIVER_INIT(FLASH_DRIVER_STARTADDRESS,&blFlashParam);
			if(kFlashOk == blFlashParam.errorcode)
			{
				blMemoryAddress = MemoryAddress;
				blMemorySize = MemorySize;
				rv = DCM_ERASE_PENDING;
			}
			else
			{
				rv = DCM_ERASE_FAILED;
			}
			/* no break here intentionally */
		case DCM_PENDING:
			if(blMemorySize > (FL_ERASE_PER_CYCLE*FLASH_ERASE_SIZE))
			{
				length  = FL_ERASE_PER_CYCLE*FLASH_ERASE_SIZE;
			}
			else
			{
				length = blMemorySize;
			}
			blFlashParam.address = blMemoryAddress;
			blFlashParam.length  = length;
			blFlashParam.data    = (tData*)blMemoryData;
			FLASH_DRIVER_ERASE(FLASH_DRIVER_STARTADDRESS,&blFlashParam);
			blMemoryAddress += length;
			blMemorySize    -= length;
			if(kFlashOk == blFlashParam.errorcode)
			{
				if( 0 == blMemorySize)
				{
					rv = DCM_ERASE_OK;
				}
				else
				{
					rv = DCM_ERASE_PENDING;
				}
			}
			else
			{
				ASLOG(BL,"erase faile: errorcode = %X(addr=%X,size=%X)\n",
						blFlashParam.errorcode,blFlashParam.address,blFlashParam.length);
				rv = DCM_ERASE_FAILED;
			}
			break;
		default:
			asAssert(0);
			rv = DCM_ERASE_FAILED;
			break;
	}

	return rv;
}

static Dcm_ReturnWriteMemoryType writeFlash(Dcm_OpStatusType OpStatus,uint32 MemoryAddress,uint32 MemorySize,
		uint8* MemoryData)
{
	Dcm_ReturnWriteMemoryType rv;
	uint32 length;
	switch(OpStatus)
	{
		case DCM_INITIAL:
			blMemoryAddress = MemoryAddress;
			blMemorySize 	= MemorySize;
			blMemoryData 	= (uint32*)MemoryData; /* should be uint32 aligned */
			/* no break here intentionally */
		case DCM_PENDING:
			if(blMemorySize > (FL_WRITE_PER_CYCLE*FLASH_WRITE_SIZE))
			{
				length  = FL_WRITE_PER_CYCLE*FLASH_WRITE_SIZE;
			}
			else
			{
				length = blMemorySize;
			}
			blFlashParam.address = blMemoryAddress;
			blFlashParam.length = length;
			blFlashParam.data    = (tData*)blMemoryData;
			FLASH_DRIVER_WRITE(FLASH_DRIVER_STARTADDRESS,&blFlashParam);
			blMemoryAddress += length;
			blMemorySize    -= length;
			blMemoryData    = &blMemoryData[length/sizeof(uint32)];
			if(kFlashOk == blFlashParam.errorcode)
			{
				if( 0 == blMemorySize)
				{
					rv = DCM_WRITE_OK;
				}
				else
				{
					rv = DCM_WRITE_PENDING;
				}
			}
			else
			{
				ASLOG(BL,"write faile: errorcode = %X(addr=%X,size=%X)\n",
						blFlashParam.errorcode,blFlashParam.address,blFlashParam.length);
				rv = DCM_WRITE_FAILED;
			}
			break;
		default:
			asAssert(0);
			rv = DCM_WRITE_FAILED;
			break;
	}

	return rv;
}

static Dcm_ReturnReadMemoryType readFlash(Dcm_OpStatusType OpStatus,uint32 MemoryAddress,uint32 MemorySize,
		uint8* MemoryData)
{
	Dcm_ReturnReadMemoryType rv;
	uint32 length;
	switch(OpStatus)
	{
		case DCM_INITIAL:
			blMemoryAddress = MemoryAddress;
			blMemorySize 	= MemorySize;
			blMemoryData 	= (uint32*)MemoryData; /* should be uint32 aligned */
			/* no break here intentionally */
		case DCM_PENDING:
			if(blMemorySize > (FL_READ_PER_CYCLE*FLASH_READ_SIZE))
			{
				length  = FL_READ_PER_CYCLE*FLASH_READ_SIZE;
			}
			else
			{
				length = blMemorySize;
			}
			blFlashParam.address = blMemoryAddress;
			blFlashParam.length = length;
			blFlashParam.data    = (tData*)blMemoryData;
			FLASH_DRIVER_READ(FLASH_DRIVER_STARTADDRESS,&blFlashParam);
			blMemoryAddress += length;
			blMemorySize    -= length;
			blMemoryData    = &blMemoryData[length/sizeof(uint32)];
			if(kFlashOk == blFlashParam.errorcode)
			{
				if( 0 == blMemorySize)
				{
					rv = DCM_READ_OK;
				}
				else
				{
					rv = DCM_READ_PENDING;
				}
			}
			else
			{
				ASLOG(BL,"read faile: errorcode = %X(addr=%X,size=%X)\n",
						blFlashParam.errorcode,blFlashParam.address,blFlashParam.length);
				rv = DCM_READ_FAILED;
			}
			break;
		default:
			asAssert(0);
			rv = DCM_READ_FAILED;
			break;
	}

	return rv;
}

static Dcm_ReturnWriteMemoryType writeFlashDriver(Dcm_OpStatusType OpStatus,uint32 MemoryAddress,uint32 MemorySize,
		uint8* MemoryData)
{
	memcpy((void*)&(FlashDriverRam[MemoryAddress/sizeof(uint32_t)]),(void*)MemoryData,MemorySize);
	return DCM_WRITE_OK;
}

static Dcm_ReturnReadMemoryType readFlashDriver(Dcm_OpStatusType OpStatus,uint32 MemoryAddress,uint32 MemorySize,
		uint8* MemoryData)
{
	memcpy((void*)MemoryData,(void*)&(FlashDriverRam[MemoryAddress/sizeof(uint32_t)]),MemorySize);
	return DCM_READ_OK;
}
/* ============================ [ FUNCTIONS ] ====================================================== */

Dcm_ReturnEraseMemoryType Dcm_EraseMemory(Dcm_OpStatusType OpStatus,
											   uint8 MemoryIdentifier,
											   uint32 MemoryAddress,
											   uint32 MemorySize)
{
	imask_t imask;
	Dcm_ReturnEraseMemoryType rv;

	ASLOG(BL,"Dcm_EraseMemory(%X,%X,%X,%X)\n",
			OpStatus,MemoryIdentifier,MemoryAddress,MemorySize);
	StopTimer(&appTimer);
	if(DCM_INITIAL == OpStatus)
	{
		blMemoryIdentifier = MemoryIdentifier;
	}
	Irq_Save(imask);
	switch(blMemoryIdentifier)
	{
		case BL_FLASH_IDENTIFIER:
			rv = eraseFlash(OpStatus,MemoryAddress,MemorySize);
			break;
		default:
			asAssert(0);
			rv = DCM_READ_FAILED;
			break;
	}
	Irq_Restore(imask);
	return rv;
}

Dcm_ReturnWriteMemoryType Dcm_WriteMemory(Dcm_OpStatusType OpStatus,
											   uint8 MemoryIdentifier,
											   uint32 MemoryAddress,
											   uint32 MemorySize,
											   uint8* MemoryData)
{
	imask_t imask;
	Dcm_ReturnEraseMemoryType rv;
	ASLOG(BL,"Dcm_WriteMemory(%X,%X,%X,%X)\n",
			OpStatus,MemoryIdentifier,MemoryAddress,MemorySize);
	StopTimer(&appTimer);
	if(DCM_INITIAL == OpStatus)
	{
		blMemoryIdentifier = MemoryIdentifier;
	}
	Irq_Save(imask);
	switch(blMemoryIdentifier)
	{
		case BL_FLASH_IDENTIFIER:
			rv = writeFlash(OpStatus,MemoryAddress,MemorySize,MemoryData);
			break;
		case BL_FLSDRV_IDENTIFIER:
			rv = writeFlashDriver(OpStatus,MemoryAddress,MemorySize,MemoryData);
			break;
		default:
			asAssert(0);
			rv = DCM_READ_FAILED;
			break;
	}
	Irq_Restore(imask);
	return rv;
}

/*@req Dcm495*/
Dcm_ReturnReadMemoryType Dcm_ReadMemory(Dcm_OpStatusType OpStatus,
											   uint8 MemoryIdentifier,
											   uint32 MemoryAddress,
											   uint32 MemorySize,
											   uint8* MemoryData)
{
	imask_t imask;
	Dcm_ReturnReadMemoryType rv;
	ASLOG(BL,"Dcm_ReadMemory(%X,%X,%X,%X)\n",
			OpStatus,MemoryIdentifier,MemoryAddress,MemorySize);
	if(DCM_INITIAL == OpStatus)
	{
		blMemoryIdentifier = MemoryIdentifier;
	}
	Irq_Save(imask);
	switch(blMemoryIdentifier)
	{
		case BL_FLASH_IDENTIFIER:
			rv = readFlash(OpStatus,MemoryAddress,MemorySize,MemoryData);
			break;
		case BL_FLSDRV_IDENTIFIER:
			rv = readFlashDriver(OpStatus,MemoryAddress,MemorySize,MemoryData);
			break;
		default:
			asAssert(0);
			rv = DCM_READ_FAILED;
			break;
	}
	Irq_Restore(imask);
	return rv;
}

boolean Dcm_CheckMemory(uint8 attr, uint8 memoryIdentifier, uint32 memoryAddress, uint32 length)
{
	boolean rv = FALSE;
	uint32 i;
	for(i=0; i<(sizeof(blMemoryList)/sizeof(BL_MemoryInfoType)); i++)
	{
		if( (memoryIdentifier == blMemoryList[i].identifier) &&
			((blMemoryList[i].attr&attr) == attr) &&
			(memoryAddress >= blMemoryList[i].addressLow) &&
			((memoryAddress+length) <= blMemoryList[i].addressHigh) )
		{
			rv = TRUE;
			break;
		}
	}
	return rv;
}

boolean Dcm_CheckDataFormatIdentifier(uint8 dataFormatIdentifier)
{
	boolean rv = FALSE;

	if(0x00u == dataFormatIdentifier)
	{
		rv = TRUE; /* no compressionMethod nor encryptingMethod is used */

	}
	else
	{
		rv = FALSE;
	}

	return rv;
}


Std_ReturnType BL_TestJumpToApplicatin(uint8 *inBuffer, uint8 *outBuffer, Dcm_NegativeResponseCodeType *errorCode)
{

	imask_t imask;

	Irq_Save(imask);

	application_main();

	Irq_Restore(imask);
	/* impossible return, failed */
	*errorCode = DCM_E_REQUEST_OUT_OF_RANGE;

	return E_NOT_OK;
}

void BL_Init(void)
{
	static const uint8 CanSduPtr[8] = {
		0x02,0x10,0x02,0x55,0x55,0x55,0x55,0x55
	};
	StartTimer(&appTimer);
	/* TODO: check previous update request from application */
	if(1)
	{	/* simulation call to enter program session */
		BL_SetAutoPRGS();
		CanIf_RxIndication(CANIF_CHL_LS,0x731,8,CanSduPtr);
	}
}

void BL_StopAppTimer(void)
{
	StopTimer(&appTimer);
}
void BL_MainFunction(void)
{
	if(GetTimer(&appTimer) > BL_STAY_TIME_MS)
	{
		imask_t imask;

		Irq_Save(imask);

		ASLOG(BL,"appTimer timeout, jump to application @%p 0x%X FLSDRV@%X!\n",
				application_main,
				*(uint32_t*)application_main,
				FLASH_DRIVER_STARTADDRESS);
		if( ((*(uint32_t*)application_main) != 0)
			&& ((*(uint32_t*)application_main) != 0xFFFFFFFF)
#ifdef STM32F10X_CL
			&& ((*(uint32_t*)application_main) == 0xBD02CF8)
#endif
		 )
		{
			application_main();
		}
		else
		{
			ASLOG(BL,"invalid application entry point, stay in bootloader.\n");
		}

		Irq_Restore(imask);
		/* impossible return, failed */

		StopTimer(&appTimer);
	}
}
