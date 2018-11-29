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
#include "Std_Types.h"
#include "Port.h" /** @req PORT131 */

#if defined(USE_DET)
#include "Det.h"
#endif
#include <string.h>

/* SHORT ON HW
 *  Have a bunch of ports:
 *  - PA, PB, PE, PK  is CPU registers (used as address bus if external RAM is used)
 *  - PH, PJ, PM, PP, PS, PT is peripheral registers
 */

typedef enum
{
    PORT_UNINITIALIZED = 0, PORT_INITIALIZED,
} Port_StateType;

static Port_StateType _portState = PORT_UNINITIALIZED;
static const Port_ConfigType * _configPtr = NULL;

/** @req PORT107 */
#if (PORT_DEV_ERROR_DETECT == STD_ON)
#define VALIDATE_PARAM_CONFIG(_ptr,_api) \
	if( (_ptr)==((void *)0) ) { \
		Det_ReportError(MODULE_ID_PORT, 0, _api, PORT_E_PARAM_CONFIG ); \
		return; \
	}

#define VALIDATE_STATE_INIT(_api)\
	if(PORT_INITIALIZED!=_portState){\
		Det_ReportError(MODULE_ID_PORT, 0, _api, PORT_E_UNINIT ); \
		return; \
	}

#else
#define VALIDATE_PARAM_CONFIG(_ptr,_api)
#define VALIDATE_STATE_INIT(_api)
#define VALIDATE_PARAM_PIN(_api)
#endif

#if PORT_VERSION_INFO_API == STD_ON
static Std_VersionInfoType _Port_VersionInfo =
{
		.vendorID = (uint16)1,
		.moduleID = (uint16) MODULE_ID_PORT,
        .instanceID = (uint8)1,
        .sw_major_version = (uint8)PORT_SW_MAJOR_VERSION,
        .sw_minor_version = (uint8)PORT_SW_MINOR_VERSION,
        .sw_patch_version = (uint8)PORT_SW_PATCH_VERSION,
        .ar_major_version = (uint8)PORT_AR_MAJOR_VERSION,
        .ar_minor_version = (uint8)PORT_AR_MINOR_VERSION,
        .ar_patch_version = (uint8)PORT_AR_PATCH_VERSION, };
#endif

extern void exDio_SetPinDirection(uint32_t channelId,Port_PinDirectionType Direction);
/** @req PORT140 */
/** @req PORT041 Comment: To reduce flash usage the configuration tool can disable configuration of some ports  */
/** @req PORT078 See environment i.e Ecu State Manager */
/** @req PORT042 */
/** @req PORT113 Number 2 in list is applicable for all pins. */
/** @req PORT043 Comment: Output value is set before direction */
/** @req PORT071 See environment i.e Ecu State Manager */
/** @req PORT002 The _portState varialble is initialised. */
/** @req PORT003 See environment i.e Ecu State Manager */
/** @req PORT055 Comment: Output value is set before direction */
/** @req PORT121 */
void Port_Init(const Port_ConfigType *configType)
{
    VALIDATE_PARAM_CONFIG(configType, PORT_INIT_ID); /** @req PORT105 */
    uint32_t i;
    // Setup pin drives and pullups


    // CAN and SPI routing of pins

    // Setup ports
    for(i=0;i<Port_PIN_NUM;i++)
	{
		exDio_SetPinDirection(i,configType->padConfig[i]);
	}

    _portState = PORT_INITIALIZED;
    _configPtr = configType;

    return;
}

/** @req PORT141 */
/** @req PORT063 */
/** @req PORT054 */
/** @req PORT086 */
#if ( PORT_SET_PIN_DIRECTION_API == STD_ON )
void Port_SetPinDirection( Port_PinType pin, Port_PinDirectionType direction )
{
    VALIDATE_STATE_INIT(PORT_SET_PIN_DIRECTION_ID);

    if(pin < Port_PIN_NUM)
    {
    	exDio_SetPinDirection(pin,direction);
    }
    else
    {
#if (PORT_DEV_ERROR_DETECT == STD_ON)
        Det_ReportError(MODULE_ID_PORT, 0, PORT_SET_PIN_DIRECTION_ID, PORT_E_PARAM_PIN );
#endif
    }

    return;
}
#endif

/** @req PORT066 */
/** @req PORT142 */
/** @req PORT060 */
/** @req PORT061 */
void Port_RefreshPortDirection(void)
{
    uint32_t i;
    VALIDATE_STATE_INIT(PORT_REFRESH_PORT_DIRECTION_ID);
    for(i=0;i<Port_PIN_NUM;i++)
    {
    	exDio_SetPinDirection(i,_configPtr->padConfig[i]);
    }
    return;
}

/** req PORT143 */
/** req PORT102 */
/** req PORT103 */
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType* versionInfo)
{
    VALIDATE_STATE_INIT(PORT_GET_VERSION_INFO_ID);
    memcpy(versionInfo, &_Port_VersionInfo, sizeof(Std_VersionInfoType));
    return;
}
#endif

/** req PORT145 */
/** req PORT125 */
/** req PORT128 */
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
    VALIDATE_STATE_INIT(PORT_SET_PIN_MODE_ID);

    // Mode of pins not changeable on this CPU
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    Det_ReportError(MODULE_ID_PORT, 0, PORT_SET_PIN_MODE_ID, PORT_E_MODE_UNCHANGEABLE );
#endif

    return;
}
#endif
