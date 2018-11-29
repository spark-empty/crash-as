#ifdef USE_FLASH_CMD
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
#include "Std_Types.h"
#include "shell.h"
#include "Flash.h"
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
#ifndef FLASH_CMD_MAX_DATA
#define FLASH_CMD_MAX_DATA 32
#endif

#define AS_LOG_FLASH 0
/* ============================ [ DECLARES  ] ====================================================== */
static int shellFlashLoadDriver(int argc, char *argv[]);
static int shellFlashErase(int argc, char *argv[]);
static int shellFlashWrite(int argc, char *argv[]);
/* ============================ [ DATAS     ] ====================================================== */
SHELL_CONST ShellCmdT cmdFlashLoadDriver  = {
		shellFlashLoadDriver,
		2,2,
		"load",
		"load addr data",
		"",
		{NULL,NULL}
};
SHELL_CMD_EXPORT(cmdFlashLoadDriver)

SHELL_CONST ShellCmdT cmdFlashErase  = {
		shellFlashErase,
		2,2,
		"erase",
		"erase addr size",
		"",
		{NULL,NULL}
};
SHELL_CMD_EXPORT(cmdFlashErase)

SHELL_CONST ShellCmdT cmdFlashWrite  = {
		shellFlashWrite,
		2,2,
		"write",
		"write addr data",
		"",
		{NULL,NULL}
};
SHELL_CMD_EXPORT(cmdFlashWrite)


static tFlashParam cmdFlashParam =
{
    .patchlevel  = FLASH_DRIVER_VERSION_PATCH,
    .minornumber = FLASH_DRIVER_VERSION_MINOR,
    .majornumber = FLASH_DRIVER_VERSION_MAJOR,
    .wdTriggerFct = NULL,
    .errorcode   = 0xFF,
};

static uint32 working_buffer[FLASH_CMD_MAX_DATA/sizeof(uint32)];
/* ============================ [ LOCALS    ] ====================================================== */
static int parse_data(char* pStr)
{
	char tmp[3];
	uint8* pData;
	int len;

	len = strlen(pStr);
	if((len <= (sizeof(working_buffer)*2)) && (0==(len&0x01)))
	{
		memset(working_buffer, 0xFF, sizeof(working_buffer));
		pData = (uint8*)working_buffer;
		tmp[2] = '\0';
		while(*pStr != '\0')
		{
			tmp[0] = pStr[0];
			tmp[1] = pStr[1];
			*pData = strtoul(tmp, NULL, 16);
			pStr += 2;
			pData ++;
		}

		len = len/2;
	}
	else
	{
		len = 0;
	}

	return len;
}
static int shellFlashLoadDriver(int argc, char *argv[])
{
	int rv = 0;
	int len;
	uint32 addr;
	(void)argc;

	addr  = strtoul(argv[1], NULL, 16);
	len = parse_data(argv[2]);
	if(len > 0)
	{
		memcpy((void*)addr, working_buffer, len);
		cmdFlashParam.errorcode = 0xFF;
	}
	else
	{
		rv = -11;
	}

	return rv;
}
static int shellFlashErase(int argc, char *argv[] ) {
	int rv = 0;
	imask_t imask;

	(void)argc;

	if(0xFF == cmdFlashParam.errorcode)
	{
		FLASH_DRIVER_INIT(FLASH_DRIVER_STARTADDRESS,&cmdFlashParam);
		rv = cmdFlashParam.errorcode;
	}

	if(0 == rv)
	{
		cmdFlashParam.address  = strtoul(argv[1], NULL, 16);
		cmdFlashParam.length = strtoul(argv[2], NULL, 16);
		ASLOG(FLASH, "erase %08X %08X\n", cmdFlashParam.address, cmdFlashParam.length);
		Irq_Save(imask);
		FLASH_DRIVER_ERASE(FLASH_DRIVER_STARTADDRESS,&cmdFlashParam);
		Irq_Restore(imask);
		rv = cmdFlashParam.errorcode;
	}

	return rv;
}

static int shellFlashWrite(int argc, char *argv[] ) {
	int rv = 0;
	imask_t imask;
	(void)argc;

	rv = cmdFlashParam.errorcode;

	if(0 == rv)
	{
		cmdFlashParam.address  = strtoul(argv[1], NULL, 16);
		cmdFlashParam.data  = working_buffer;
		cmdFlashParam.length = parse_data(argv[2]);
		if(cmdFlashParam.length > 0)
		{
			ASLOG(FLASH, "write %08X (len=%d) %08X%08X...\n",
					cmdFlashParam.address, cmdFlashParam.length,
					cmdFlashParam.data[0],cmdFlashParam.data[1]);

			Irq_Save(imask);
			FLASH_DRIVER_WRITE(FLASH_DRIVER_STARTADDRESS,&cmdFlashParam);
			Irq_Restore(imask);
			rv = cmdFlashParam.errorcode;
		}
		else
		{
			rv = -11;
		}
	}

	return rv;
}
/* ============================ [ FUNCTIONS ] ====================================================== */

#endif /* USE_FLASH_CMD */
