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
#ifdef FLASH_DRIVER_DYNAMIC_DOWNLOAD
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
#include "Flash.h"
#include "stm32f10x_flash.h"
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
const tFlashHeader FlashHeader =
{
	.Info.w    = 0x01004512,
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
		/* Unlock the Flash Program Erase controller */
		FLASH_Unlock();
		/* Clear All pending flags */
		FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);

		FlashParam->errorcode = kFlashOk;
	}
	else
	{
		FlashParam->errorcode = kFlashFailed;
	}
}

void FlashDeinit(tFlashParam* FlashParam)
{
	FLASH_Lock();
	FlashParam->errorcode = kFlashOk;
}
/* 1 sector size is 2K */
void FlashErase(tFlashParam* FlashParam)
{
	tAddress address;
	tLength  length;
	if ( (FLASH_DRIVER_VERSION_PATCH == FlashParam->patchlevel) ||
		 (FLASH_DRIVER_VERSION_MINOR == FlashParam->minornumber) ||
		 (FLASH_DRIVER_VERSION_MAJOR == FlashParam->majornumber) )
	{
		length = FlashParam->length;
		address = FlashParam->address + 0x08000000;
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
			/* Erase the sector... */
			while(length > 0)
			{
				volatile FLASH_Status status = FLASH_BUSY;
				while(status != FLASH_COMPLETE){
					status = FLASH_ErasePage((uint32_t)address);
				}

				length  -= FLASH_ERASE_SIZE;
				address += FLASH_ERASE_SIZE;
			}
			FlashParam->errorcode = kFlashOk;
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
	uint32_t  i;
	if ( (FLASH_DRIVER_VERSION_PATCH == FlashParam->patchlevel) ||
		 (FLASH_DRIVER_VERSION_MINOR == FlashParam->minornumber) ||
		 (FLASH_DRIVER_VERSION_MAJOR == FlashParam->majornumber) )
	{
		length = FlashParam->length;
		address = FlashParam->address + 0x08000000;
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
			while(length > 0)
			{
				for(i=0;i<(FLASH_WRITE_SIZE/sizeof(tData));i++)
				{
					#if 0
					volatile FLASH_Status status = FLASH_BUSY;
					while(status != FLASH_COMPLETE){
						status = FLASH_ProgramWord((address+i*sizeof(tData)), data[i]);
					}
					#else
					FLASH_ProgramWord((address+i*sizeof(tData)), data[i]);
					#endif
				}
				length  -= FLASH_WRITE_SIZE;
				address += FLASH_WRITE_SIZE;
				data    += (FLASH_WRITE_SIZE/sizeof(tData));
			}
			FlashParam->errorcode = kFlashOk;
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
		address = FlashParam->address + 0x08000000;
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
			tLength i;
			const char* src = (const char*) address;

			for(i=0;i<length;i++)
			{
				data[i] = src[i];
			}
		}
	}
	else
	{
		FlashParam->errorcode = kFlashFailed;
	}
}
#endif /* FLASH_DRIVER_DYNAMIC_DOWNLOAD */

