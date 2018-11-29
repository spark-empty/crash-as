/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2017  AS <parai@foxmail.com>
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
#ifdef USE_PCI
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Can.h"
#include "CanIf_Cbk.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#include "Os.h"
#include "pci_core.h"
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
#define AS_LOG_CAN 0
#define AS_LOG_CANRX 0
#define AS_LOG_CANTX 0

#ifndef CAN_DEV_NAME
#define CAN_DEV_NAME "socket"
#endif

#define GET_CONTROLLER_CONFIG(_controller)	\
		&Can_Global.config->CanConfigSet->CanController[(_controller)]

#define GET_CALLBACKS() \
		(Can_Global.config->CanConfigSet->CanCallbacks)

#define GET_PRIVATE_DATA(_controller) &CanUnit[_controller]

#define GET_CONTROLLER_CNT() (CAN_CONTROLLER_CNT)

#if ( CAN_DEV_ERROR_DETECT == STD_ON )
#define VALIDATE(_exp,_api,_err ) \
        if( !(_exp) ) { \
          Det_ReportError(MODULE_ID_CAN,0,_api,_err); \
          return CAN_NOT_OK; \
        }

#define VALIDATE_NO_RV(_exp,_api,_err ) \
        if( !(_exp) ) { \
          Det_ReportError(MODULE_ID_CAN,0,_api,_err); \
          return; \
        }

#define DET_REPORTERROR(_x,_y,_z,_q) Det_ReportError(_x, _y, _z, _q)
#else
#define VALIDATE(_exp,_api,_err )
#define VALIDATE_NO_RV(_exp,_api,_err )
#define DET_REPORTERROR(_x,_y,_z,_q)
#endif

#define CAN_EMPTY_MESSAGE_BOX 0xFFFF

enum {
	FLG_RX = 0x01,
	FLG_TX = 0x02,
};

enum{
	REG_BUS_NAME  = 0x00,
	REG_BUSID     = 0x04,
	REG_PORT      = 0x08,
	REG_CANID     = 0x0C,
	REG_CANDLC    = 0x10,
	REG_CANDATA   = 0x14,
	REG_CANSTATUS = 0x18,
	REG_CMD       = 0x1C,
};
/* ============================ [ TYPES     ] ====================================================== */
typedef enum
{
	CAN_UNINIT = 0,
	CAN_READY
} Can_DriverStateType;


typedef struct Can_Arc_ObjectHOHMapStruct
{
	CanControllerIdType CanControllerRef;
	const Can_HardwareObjectType* CanHOHRef;
} Can_Arc_ObjectHOHMapType;

/* Type for holding global information used by the driver */
typedef struct {
	Can_DriverStateType initRun;


	const Can_ConfigType *config;

	/* One bit for each channel that is configured.
	 * Used to determine if validity of a channel
	 * 1 - configured
	 * 0 - NOT configured
	 */
	uint32  configured;
	/* Maps the a channel id to a configured channel id */
	uint8   channelMap[CAN_CONTROLLER_CNT];

	/* This is a map that maps the HTH:s with the controller and Hoh. It is built
	 * during Can_Init and is used to make things faster during a transmit.
	 */
	Can_Arc_ObjectHOHMapType CanHTHMap[NUM_OF_HTHS];
} Can_GlobalType;

/* Type for holding information about each controller */
typedef struct {
	CanIf_ControllerModeType state;
	uint8		lock_cnt;

	/* Data stored for Txconfirmation callbacks to CanIf */
	PduIdType swPduHandle;
} Can_UnitType;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
static pci_dev *pdev = NULL;
static void* __iobase= NULL;

Can_UnitType CanUnit[CAN_CONTROLLER_CNT] =
{
	{
		.state = CANIF_CS_UNINIT,
	},
	{
		.state = CANIF_CS_UNINIT,
	},
	{
		.state = CANIF_CS_UNINIT,
	},
	{
		.state = CANIF_CS_UNINIT,
	},
	{
		.state = CANIF_CS_UNINIT,
	},
};
Can_GlobalType Can_Global =
{
	.initRun = CAN_UNINIT,
};
/* ============================ [ LOCALS    ] ====================================================== */
/**
 * Function that finds the Hoh( HardwareObjectHandle ) from a Hth
 * A HTH may connect to one or several HOH's. Just find the first one.
 *
 * @param hth The transmit handle
 * @returns Ptr to the Hoh
 */
static const Can_HardwareObjectType * Can_FindHoh( Can_Arc_HTHType hth , uint32* controller)
{
	const Can_HardwareObjectType *hohObj;
	const Can_Arc_ObjectHOHMapType *map;

	map = &Can_Global.CanHTHMap[hth];

	/* Verify that this is the correct map */
	if (map->CanHOHRef->CanObjectId != hth)
	{
	DET_REPORTERROR(MODULE_ID_CAN, 0, 0x6, CAN_E_PARAM_HANDLE);
	}
	hohObj = map->CanHOHRef;

	/* Verify that this is the correct Hoh type */
	if ( hohObj->CanObjectType == CAN_OBJECT_TYPE_TRANSMIT)
	{
		*controller = map->CanControllerRef;
		return hohObj;
	}

	DET_REPORTERROR(MODULE_ID_CAN, 0, 0x6, CAN_E_PARAM_HANDLE);

	return NULL;
}

static void can_isr(void)
{
	uint32 flag;
	Can_UnitType *canUnit;
	const Can_ControllerConfigType *canHwConfig;
	uint8 ctlrId;

	#ifdef USE_ASKAR
	imask_t imask;
	extern unsigned int CallLevel;
	unsigned int savedCallLevel;
	#endif

	if(Can_Global.initRun == CAN_READY)
	{
		#ifdef USE_ASKAR
		Irq_Save(imask);
		savedCallLevel = CallLevel;
		CallLevel = 2 /*TCL_ISR2 */;
		#endif

		flag = readl(__iobase+REG_CANSTATUS);

		for (int configId=0; configId < CAN_CTRL_CONFIG_CNT; configId++) {
			canHwConfig = GET_CONTROLLER_CONFIG(configId);
			ctlrId = canHwConfig->CanControllerId;

			canUnit = GET_PRIVATE_DATA(ctlrId);
			if(flag&(FLG_TX<<(4*ctlrId)))
			{
				if(CAN_EMPTY_MESSAGE_BOX != canUnit->swPduHandle)
				{
					PduIdType swPduHandle = canUnit->swPduHandle;
					canUnit->swPduHandle = CAN_EMPTY_MESSAGE_BOX;
					if(NULL != Can_Global.config->CanConfigSet->CanCallbacks->TxConfirmation)
					{
						Can_Global.config->CanConfigSet->CanCallbacks->TxConfirmation(swPduHandle);
					}
				}
			}

			if(flag&(FLG_RX<<(4*ctlrId)))
			{
				uint32_t canid, i;
				uint8_t dlc;
				uint16 Hrh;
				unsigned char data[64];
				const Can_HardwareObjectType  *hoh = Can_Global.config->CanConfigSet->CanController[configId].Can_Arc_Hoh;
				hoh --;
				do{
					hoh ++;
					if(CAN_OBJECT_TYPE_RECEIVE == hoh->CanObjectType)
					{
						Hrh = hoh->CanObjectId;
						break;
					}
				}while(FALSE == hoh->Can_Arc_EOL);
				asAssert(0xFFFF != Hrh);

				writel(__iobase+REG_BUSID,ctlrId);
				canid = readl(__iobase+REG_CANID);
				dlc   = readl(__iobase+REG_CANDLC);
				asAssert(dlc <= CAN_LL_DL);
				for(i=0; i<dlc; i++)
				{
					data[i] = readl(__iobase+REG_CANDATA);
				}

				asAssert(Can_Global.config->CanConfigSet->CanCallbacks->RxIndication);
				ASLOG(CANRX,"CAN%d ID=0x%08X LEN=%d DATA=[%02X %02X %02X %02X %02X %02X %02X %02X]\n",ctlrId,
						canid,dlc,data[0],data[1],data[2],data[3],
					data[4],data[5],data[6],data[7]);
				Can_Global.config->CanConfigSet->CanCallbacks->RxIndication(Hrh, canid, dlc, data);

			}
		}
		#ifdef USE_ASKAR
		CallLevel = savedCallLevel;
		Irq_Restore(imask);
		#endif
	}
}
/* ============================ [ FUNCTIONS ] ====================================================== */
void Can_Init( const Can_ConfigType *config )
{
	Can_UnitType *canUnit;
	const Can_ControllerConfigType *canHwConfig;
	uint8 ctlrId;

	VALIDATE_NO_RV( (Can_Global.initRun == CAN_UNINIT), 0x0, CAN_E_TRANSITION );
	VALIDATE_NO_RV( (config != NULL ), 0x0, CAN_E_PARAM_POINTER );

	pdev = find_pci_dev_from_id(0xcaac,0x0001);
	if(NULL != pdev)
	{
		__iobase = pci_get_memio(pdev, 1);

		enable_pci_resource(pdev);
		#ifdef __X86__
		pci_register_irq(pdev->irq_num,can_isr);
		#else
		pci_bus_write_config_byte(pdev,0x3c,0x43);
		pci_register_irq(32+30,can_isr);
		#endif
		enable_pci_interrupt(pdev);

		Can_Global.config = config;
		Can_Global.initRun = CAN_READY;

		for (int configId=0; configId < CAN_CTRL_CONFIG_CNT; configId++) {
			char* p;
			imask_t irq_state;
			canHwConfig = GET_CONTROLLER_CONFIG(configId);
			ctlrId = canHwConfig->CanControllerId;

			/* Assign the configuration channel used later.. */
			Can_Global.channelMap[canHwConfig->CanControllerId] = configId;
			Can_Global.configured |= (1<<ctlrId);

			canUnit = GET_PRIVATE_DATA(ctlrId);
			canUnit->state = CANIF_CS_STOPPED;

			canUnit->lock_cnt = 0;
			/* 0xFFFF marked as Empty and invalid */
			canUnit->swPduHandle = CAN_EMPTY_MESSAGE_BOX;

			Can_InitController(ctlrId, canHwConfig);

			Irq_Save(irq_state);
			writel(__iobase+REG_CMD, 0); /* CMD init, reset bus name */

			for(p=CAN_DEV_NAME; *p != '\0'; p++)
			{
				writel(__iobase+REG_BUS_NAME, *p);
			}

			writel(__iobase+REG_BUSID, ctlrId);
			writel(__iobase+REG_PORT,  ctlrId);

			writel(__iobase+REG_CMD, 1); /* CMD start open device */
			Irq_Restore(irq_state);

			/* Loop through all Hoh:s and map them into the HTHMap */
			const Can_HardwareObjectType* hoh;
			hoh = canHwConfig->Can_Arc_Hoh;
			hoh--;
			do
			{
				hoh++;

				if (hoh->CanObjectType == CAN_OBJECT_TYPE_TRANSMIT)
				{
					Can_Global.CanHTHMap[hoh->CanObjectId].CanControllerRef = canHwConfig->CanControllerId;
					Can_Global.CanHTHMap[hoh->CanObjectId].CanHOHRef = hoh;
				}
			} while (!hoh->Can_Arc_EOL);
		}
	}
	else
	{
		ASLOG(ERROR,"No pci-can device found, specify '-device pci-ascan' to qemu\n");
	}
}

void Can_InitController( uint8 controller, const Can_ControllerConfigType *config)
{
	Can_UnitType *canUnit;
	uint8 cId = controller;
	const Can_ControllerConfigType *canHwConfig;
	const Can_HardwareObjectType *hohObj;

	VALIDATE_NO_RV( (Can_Global.initRun == CAN_READY), 0x2, CAN_E_UNINIT );
	VALIDATE_NO_RV( (config != NULL ), 0x2,CAN_E_PARAM_POINTER);
	VALIDATE_NO_RV( (controller < GET_CONTROLLER_CNT()), 0x2, CAN_E_PARAM_CONTROLLER );

	canUnit = GET_PRIVATE_DATA(controller);

	VALIDATE_NO_RV( (canUnit->state==CANIF_CS_STOPPED), 0x2, CAN_E_TRANSITION );

	canHwConfig = GET_CONTROLLER_CONFIG(Can_Global.channelMap[cId]);

	canUnit->state = CANIF_CS_STOPPED;
	Can_EnableControllerInterrupts(cId);
}

Can_ReturnType Can_SetControllerMode( uint8 controller, Can_StateTransitionType transition )
{
	Can_ReturnType rv = CAN_OK;
	VALIDATE( (controller < GET_CONTROLLER_CNT()), 0x3, CAN_E_PARAM_CONTROLLER );

	Can_UnitType *canUnit = GET_PRIVATE_DATA(controller);

	VALIDATE( (canUnit->state!=CANIF_CS_UNINIT), 0x3, CAN_E_UNINIT );
	switch(transition )
	{
		case CAN_T_START:
			canUnit->state = CANIF_CS_STARTED;
			ASLOG(STDOUT,"can set on-line!\n");
			if (canUnit->lock_cnt == 0){
				Can_EnableControllerInterrupts(controller);
			}
		break;
		case CAN_T_WAKEUP:
			VALIDATE(canUnit->state == CANIF_CS_SLEEP, 0x3, CAN_E_TRANSITION);
			canUnit->state = CANIF_CS_STOPPED;
		break;
		case CAN_T_SLEEP:
			VALIDATE(canUnit->state == CANIF_CS_STOPPED, 0x3, CAN_E_TRANSITION);
			canUnit->state = CANIF_CS_SLEEP;
		break;
		case CAN_T_STOP:
			canUnit->state = CANIF_CS_STOPPED;
		break;
		default:
			VALIDATE(canUnit->state == CANIF_CS_STOPPED, 0x3, CAN_E_TRANSITION);
		break;
	}
	return rv;
}

Can_ReturnType Can_Write( Can_Arc_HTHType hth, Can_PduType *pduInfo )
{
	Can_ReturnType rv = CAN_OK;
	const Can_HardwareObjectType *hohObj;
	uint32 controller;
	imask_t irq_state;
	uint8_t busid;

	VALIDATE( (Can_Global.initRun == CAN_READY), 0x6, CAN_E_UNINIT );
	VALIDATE( (pduInfo != NULL), 0x6, CAN_E_PARAM_POINTER );
	VALIDATE( (pduInfo->length <= 64), 0x6, CAN_E_PARAM_DLC );
	VALIDATE( (hth < NUM_OF_HTHS ), 0x6, CAN_E_PARAM_HANDLE );

	hohObj = Can_FindHoh(hth, &controller);
	if (hohObj == NULL)
	{
		return CAN_NOT_OK;
	}

	Can_UnitType *canUnit = GET_PRIVATE_DATA(controller);

	for (busid=0; busid < CAN_CTRL_CONFIG_CNT; busid++)
	{
		if(controller==Can_Global.config->CanConfigSet->CanController->CanControllerId)
		{
			break;
		}
	}
	if(busid >= CAN_CTRL_CONFIG_CNT)
	{
		return CAN_NOT_OK;
	}
	if(CANIF_CS_STARTED == canUnit->state)
	{
		Irq_Save(irq_state);
		if(CAN_EMPTY_MESSAGE_BOX == canUnit->swPduHandle)	/* check for any free box */
		{
			uint32_t i;
			writel(__iobase+REG_BUSID, controller);
			writel(__iobase+REG_CANID, pduInfo->id);
			writel(__iobase+REG_CANDLC, pduInfo->length);
			for(i=0; i<pduInfo->length; i++)
			{
				writel(__iobase+REG_CANDATA, pduInfo->sdu[i]);
			}
			writel(__iobase+REG_CMD, 2);
			ASLOG(CANTX,"CAN%d ID=0x%08X LEN=%d DATA=[%02X %02X %02X %02X %02X %02X %02X %02X]\n",controller,
				pduInfo->id,pduInfo->length,pduInfo->sdu[0],pduInfo->sdu[1],pduInfo->sdu[2],pduInfo->sdu[3],
				pduInfo->sdu[4],pduInfo->sdu[5],pduInfo->sdu[6],pduInfo->sdu[7]);

			canUnit->swPduHandle = pduInfo->swPduHandle;
		}
		else
		{
			rv = CAN_BUSY;
		}
		Irq_Restore(irq_state);
	} else {
		rv = CAN_NOT_OK;
	}

	return rv;
}


void Can_DisableControllerInterrupts( uint8 controller )
{
	Can_UnitType *canUnit;

	VALIDATE_NO_RV( (controller < GET_CONTROLLER_CNT()), 0x4, CAN_E_PARAM_CONTROLLER );

	canUnit = GET_PRIVATE_DATA(controller);

	VALIDATE_NO_RV( (canUnit->state!=CANIF_CS_UNINIT), 0x4, CAN_E_UNINIT );

	if(canUnit->lock_cnt > 0 )
	{
		/* Interrupts already disabled */
		canUnit->lock_cnt++;
		return;
	}
	canUnit->lock_cnt++;
}

void Can_EnableControllerInterrupts( uint8 controller )
{
	Can_UnitType *canUnit;
	VALIDATE_NO_RV( (controller < GET_CONTROLLER_CNT()), 0x5, CAN_E_PARAM_CONTROLLER );

	canUnit = GET_PRIVATE_DATA(controller);

	VALIDATE_NO_RV( (canUnit->state!=CANIF_CS_UNINIT), 0x5, CAN_E_UNINIT );

	if( canUnit->lock_cnt > 1 )
	{
		/* IRQ should still be disabled so just decrement counter */
		canUnit->lock_cnt--;
		return;
	} else if (canUnit->lock_cnt == 1)
	{
		canUnit->lock_cnt = 0;
	}

	return;
}


// Hth - for Flexcan, the hardware message box number... .We don't care
void Can_Cbk_CheckWakeup( uint8 controller ){(void)controller;}

void Can_MainFunction_Write( void ) { can_isr();}
void Can_MainFunction_Read( void )  { can_isr();}
void Can_MainFunction_BusOff( void ){}
void Can_MainFunction_Wakeup( void ){}
void Can_MainFunction_Error ( void ){}

void Can_Arc_GetStatistics( uint8 controller, Can_Arc_StatisticsType * stat){(void)controller;(void)stat;}

#endif /* USE_PCI */
