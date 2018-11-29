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
#include "Flash.h"
#include <stdio.h>
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
#define FLASH_IMG "Flash.img"
#define FLS_TOTAL_SIZE  1024*1024

#define IS_FLASH_ADDRESS(a) ((a) <= FLS_TOTAL_SIZE)
#define AS_LOG_FLS 1
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
const tFlashHeader FlashHeader =
{
	.Info.W.MCU     = 1,
	.Info.W.mask    = 2,
	.Info.W.version = 169,
	.Init      = FlashInit,
	.Deinit    = FlashDeinit,
	.Erase     = FlashErase,
	.Write     = FlashWrite,
	.Read      = FlashRead
};
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void FlashInit(tFlashParam* FlashParam)
{
	if ( (FLASH_DRIVER_VERSION_PATCH == FlashParam->patchlevel) ||
		 (FLASH_DRIVER_VERSION_MINOR == FlashParam->minornumber) ||
		 (FLASH_DRIVER_VERSION_MAJOR == FlashParam->majornumber) )
	{
		FILE* fp = fopen(FLASH_IMG,"rb");
		if(NULL == fp)
		{
			fp = fopen(FLASH_IMG,"wb+");
			asAssert(fp);
			for(int i=0;i<FLS_TOTAL_SIZE;i++)
			{
				uint8_t data = 0xFF;
				fwrite(&data,1,1,fp);
			}
			fclose(fp);

			ASLOG(FLS,"simulation on new created image %s(%dKb)\n",FLASH_IMG,FLS_TOTAL_SIZE/1024);
		}
		else
		{
			ASLOG(FLS,"simulation on old existed image %s(%dKb)\n",FLASH_IMG,FLS_TOTAL_SIZE/1024);
			fclose(fp);
		}
		FlashParam->errorcode = kFlashOk;
	}
	else
	{
		FlashParam->errorcode = kFlashFailed;
	}
}

void FlashDeinit(tFlashParam* FlashParam)
{
	/*  TODO: Deinit Flash Controllor */
	FlashParam->errorcode = kFlashOk;
}

void FlashErase(tFlashParam* FlashParam)
{
	tAddress address;
	tLength  length;
	if ( (FLASH_DRIVER_VERSION_PATCH == FlashParam->patchlevel) ||
		 (FLASH_DRIVER_VERSION_MINOR == FlashParam->minornumber) ||
		 (FLASH_DRIVER_VERSION_MAJOR == FlashParam->majornumber) )
	{
		length = FlashParam->length;
		address = FlashParam->address;
		if ( (FALSE == FLASH_IS_ERASE_ADDRESS_ALIGNED(address)) ||
			 (FALSE == IS_FLASH_ADDRESS(address)) )
		{
			FlashParam->errorcode = kFlashInvalidAddress;
		}
		else if( (FALSE == IS_FLASH_ADDRESS(address+length)) ||
				 (FALSE == FLASH_IS_ERASE_ADDRESS_ALIGNED(length)) )
		{
			FlashParam->errorcode = kFlashInvalidSize;
		}
		else
		{
			FILE* fp = NULL;
			static unsigned char EraseMask[4] = {0xFF,0xFF,0xFF,0xFF};
			fp = fopen(FLASH_IMG,"rb+");
			if(NULL == fp)
			{
				FlashParam->errorcode = kFlashFailed;
			}
			else
			{
				fseek(fp,FlashParam->address,SEEK_SET);
				for(int i=0;i<(FlashParam->length);i++)
				{
					fwrite(EraseMask,1,1,fp);
				}
				fclose(fp);
				FlashParam->errorcode = kFlashOk;
			}
		}
	}
	else
	{
		FlashParam->errorcode = kFlashFailed;
	}
}

void FlashWrite(tFlashParam* FlashParam)
{
	tAddress address;
	tLength  length;
	tData*    data;
	if ( (FLASH_DRIVER_VERSION_PATCH == FlashParam->patchlevel) ||
		 (FLASH_DRIVER_VERSION_MINOR == FlashParam->minornumber) ||
		 (FLASH_DRIVER_VERSION_MAJOR == FlashParam->majornumber) )
	{
		length = FlashParam->length;
		address = FlashParam->address;
		data = FlashParam->data;
		if ( (FALSE == FLASH_IS_WRITE_ADDRESS_ALIGNED(address)) ||
			 (FALSE == IS_FLASH_ADDRESS(address)) )
		{
			FlashParam->errorcode = kFlashInvalidAddress;
		}
		else if( (FALSE == IS_FLASH_ADDRESS(address+length)) ||
				 (FALSE == FLASH_IS_WRITE_ADDRESS_ALIGNED(length)) )
		{
			FlashParam->errorcode = kFlashInvalidSize;
		}
		else if( NULL == data )
		{
			FlashParam->errorcode = kFlashInvalidData;
		}
		else
		{
			FILE* fp = NULL;
			fp = fopen(FLASH_IMG,"rb+");
			if(NULL == fp)
			{
				FlashParam->errorcode = kFlashFailed;
			}
			else
			{
				fseek(fp,address,SEEK_SET);
				fwrite(data,length,1,fp);
				fclose(fp);
				FlashParam->errorcode = kFlashOk;
			}
		}
	}
	else
	{
		FlashParam->errorcode = kFlashFailed;
	}
}

void FlashRead(tFlashParam* FlashParam)
{
	tAddress address;
	tLength  length;
	tData*    data;
	if ( (FLASH_DRIVER_VERSION_PATCH == FlashParam->patchlevel) ||
		 (FLASH_DRIVER_VERSION_MINOR == FlashParam->minornumber) ||
		 (FLASH_DRIVER_VERSION_MAJOR == FlashParam->majornumber) )
	{
		length = FlashParam->length;
		address = FlashParam->address;
		data = FlashParam->data;
		if ( (FALSE == FLASH_IS_READ_ADDRESS_ALIGNED(address)) ||
			 (FALSE == IS_FLASH_ADDRESS(address)) )
		{
			FlashParam->errorcode = kFlashInvalidAddress;
		}
		else if( (FALSE == IS_FLASH_ADDRESS(address+length)) ||
				 (FALSE == FLASH_IS_READ_ADDRESS_ALIGNED(length)) )
		{
			FlashParam->errorcode = kFlashInvalidSize;
		}
		else if( NULL == data )
		{
			FlashParam->errorcode = kFlashInvalidData;
		}
		else
		{
			FILE* fp = NULL;
			fp = fopen(FLASH_IMG,"rb+");
			if(NULL == fp)
			{
				FlashParam->errorcode = kFlashFailed;
			}
			else
			{
				fseek(fp,address,SEEK_SET);
				fread(data,length,1,fp);
				fclose(fp);
				FlashParam->errorcode = kFlashOk;
			}
		}
	}
	else
	{
		FlashParam->errorcode = kFlashFailed;
	}
}
