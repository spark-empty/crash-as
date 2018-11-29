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
/* DOC:
 * https://networkupstools.org/protocols/eaton/XCP_Rev_C1_Public_021309.pdf
 * http://read.pudn.com/downloads192/doc/comm/903802/XCP%20-Part%203-%20Transport_layer_specification_xcp_on_can_1-0.pdf
 * https://vector.com/portal/medien/solutions_for/xcp/Vector_XCP_Basics_EN.pdf
 * https://www.etas.com/download-center-files/products_INCA_Software_Products/iLinkRT_XCP_Implementation_Description_PV1_3_-_DV1_4_released.pdf
 */
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Xcp.h"
#include "CanIf.h"
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
#define AS_LOG_XCP     0
#define AS_LOG_XCPE    1

#ifndef CAN_LL_DL
#define CAN_LL_DL 8
#endif

#ifndef XCP_MAX_CTO
#define XCP_MAX_CTO 8
#endif
#ifndef XCP_MAX_DTO
#define XCP_MAX_DTO 8
#endif

#ifdef __AS_BOOTLOADER__
#ifndef USE_XCP_RES_PGM
#define USE_XCP_RES_PGM
#endif
#ifndef USE_XCP_RES_CALPAG
#define USE_XCP_RES_CALPAG
#endif
#endif

/* XCP command codes */
/* CONNECT command code. */
#define XCP_CMD_CONNECT             (0xff)
/* DISCONNECT command code. */
#define XCP_CMD_DISCONNECT          (0xfe)
/* GET_STATUS command code. */
#define XCP_CMD_GET_STATUS          (0xfd)
/* SYNCH command code. */
#define XCP_CMD_SYNCH               (0xfc)
/* GET_ID command code. */
#define XCP_CMD_GET_ID              (0xfa)
/* GET_SEED command code. */
#define XCP_CMD_GET_SEED            (0xf8)
/* UNLOCK command code. */
#define XCP_CMD_UNLOCK              (0xf7)
/* SET_MTA command code. */
#define XCP_CMD_SET_MTA             (0xf6)
/* UPLOAD command code. */
#define XCP_CMD_UPLOAD              (0xf5)
/* SHORT_UPLOAD command code. */
#define XCP_CMD_SHORT_UPLOAD        (0xf4)
/* BUILD_CHECKSUM command code. */
#define XCP_CMD_BUILD_CHECKSUM      (0xf3)
/* DOWNLOAD command code. */
#define XCP_CMD_DOWNLOAD            (0xf0)
/* DOWNLOAD_MAX command code. */
#define XCP_CMD_DOWLOAD_MAX         (0xee)
/* SET_CALPAGE command code. */
#define XCP_CMD_SET_CAL_PAGE        (0xeb)
/* GET_CALPAGE command code. */
#define XCP_CMD_GET_CAL_PAGE        (0xea)
/* PROGRAM_START command code. */
#define XCP_CMD_PROGRAM_START       (0xd2)
/* PROGRAM_CLEAR command code. */
#define XCP_CMD_PROGRAM_CLEAR       (0xd1)
/* PROGRAM command code. */
#define XCP_CMD_PROGRAM             (0xd0)
/* PROGRAM_RESET command code. */
#define XCP_CMD_PROGRAM_RESET       (0xcf)
/* PROGRAM_PREPARE command code. */
#define XCP_CMD_PROGRAM_PREPARE     (0xcc)
/* PROGRAM_MAX command code. */
#define XCP_CMD_PROGRAM_MAX         (0xc9)

/* XCP packet identifiers */
/* Command response packet identifier. */
#define XCP_PID_RES                 (0xff)
/* Error packet identifier. */
#define XCP_PID_ERR                 (0xfe)

/* XCP error codes */
/* Cmd processor synchronization error code. */
#define XCP_ERR_CMD_SYNCH           (0x00)
/* Command was not executed error code. */
#define XCP_ERR_CMD_BUSY            (0x10)
/* Unknown or unsupported command error code. */
#define XCP_ERR_CMD_UNKNOWN         (0x20)
/* Parameter out of range error code. */
#define XCP_ERR_OUT_OF_RANGE        (0x22)
/* Protected error code. Seed/key required. */
#define XCP_ERR_ACCESS_LOCKED       (0x25)
/* Cal page not valid error code. */
#define XCP_ERR_PAGE_NOT_VALID      (0x26)
/* Sequence error code. */
#define XCP_ERR_SEQUENCE            (0x29)
/* Generic error code. */
#define XCP_ERR_GENERIC             (0x31)

/* xcp supported resources */
/** ProGraMming resource. */
#define XCP_RES_PGM            (0x10)
/*data STIMulation resource. */
#define XCP_RES_STIM           (0x08)
/* Data AcQuisition resource. */
#define XCP_RES_DAQ            (0x04)
/* CALibration and PAGing resource. */
#define XCP_RES_CALPAG         (0x01)

#define XCP_FLAG_RES_MASK   (XCP_RES_PGM|XCP_RES_STIM|XCP_RES_DAQ|XCP_RES_CALPAG)

#define XCP_FLAG_CALPAG_SEED_REQUESTED    (XCP_RES_CALPAG<<8)
#define XCP_FLAG_PGM_SEED_REQUESTED       (XCP_RES_PGM<<8)

#define XCP_FLAG_SEED_REQUESTED_MASK       (XCP_FLAG_RES_MASK<<8)

#define XCP_FLAG_CONNECTED             0x10000
#define XCP_FLAG_PGM_STARTED           0x20000

#define RWU16(a) (*(uint16*)(&(a)))
#define RWU32(a) (*(uint32*)(&(a)))

#define RWS16(a) (*(sint16*)(&(a)))
#define RWS32(a) (*(sint32*)(&(a)))


#define XCP_CHECK(e,msg)							\
	do {											\
		if(FALSE == (e)) {							\
			ASLOG(XCPE, "%s: %s", __func__, msg);	\
			XcpSendNRC(XCP_ERR_GENERIC);			\
			return;									\
		}											\
	} while(0)

/* ============================ [ TYPES     ] ====================================================== */
enum {
	XCP_ON_NONE = 0,
	XCP_ON_CAN,
	XCP_ON_ETH,
};

enum {
	XCP_BUFFER_IDLE = 0,
	XCP_BUFFER_FULL,
};

enum {
	XCP_MTA_RAM = 0,
	XCP_MTA_ROM, /* FLASH */
	XCP_MTA_NONE
};

typedef struct
{
	uint32        flags;
	uint32        mtaAddr;	/* memory address to be accessed */
	/* MUST BE 4 byte aligned */
	uint8         rxBuffer[XCP_MAX_CTO];
	uint8         txBuffer[XCP_MAX_DTO];

	PduLengthType LL_DL;	/* Low Level target maximum Data Length */
	PduLengthType rxLength;
	PduLengthType txLength;
	uint8         target;
	uint8         rxBufferState;
	uint8         txBufferState;
	uint8         counter;

	uint8         mtaExt;
} Xcp_RuntimeType; /* RTE */

/* ============================ [ DECLARES  ] ====================================================== */
extern uint8 Xcp_SeedFn(Xcp_ProtectType res, uint8* seed);
extern Std_ReturnType Xcp_UnlockFn(Xcp_ProtectType res, const uint8* seed,
        uint8 seed_len, const uint8* key, uint8 key_len);

Std_ReturnType Xcp_CanIfTransmit(const void* data, int len);

static void XcpHandleTransmit(void);
/* ============================ [ DATAS     ] ====================================================== */
static Xcp_RuntimeType XCP_RTE;

const Xcp_ConfigType XcpConfig;
/* ============================ [ LOCALS    ] ====================================================== */
static void XcpReset(void)
{
	memset(&XCP_RTE, 0 , sizeof(XCP_RTE));
	XCP_RTE.mtaExt = XCP_MTA_NONE;
}


static void XcpCmdServiceDone(void)
{
	XCP_RTE.counter = 0;
	XCP_RTE.rxBufferState = XCP_BUFFER_IDLE;
	XCP_RTE.txBufferState = XCP_BUFFER_IDLE;
	XCP_RTE.target = XCP_ON_NONE;
}

static void XcpSendPRC(PduLengthType len)
{
	if(XCP_BUFFER_IDLE == XCP_RTE.txBufferState)
	{
		XCP_RTE.txBuffer[0] = XCP_PID_RES;
		XCP_RTE.txLength = len+1;
		XCP_RTE.txBufferState = XCP_BUFFER_FULL;
		XCP_RTE.rxBufferState = XCP_BUFFER_IDLE;

		XcpHandleTransmit();
	}
}

static void XcpSendNRC(uint8 nrc)
{
	if(XCP_BUFFER_IDLE == XCP_RTE.txBufferState)
	{
		XCP_RTE.txBuffer[0] = XCP_PID_ERR;
		XCP_RTE.txBuffer[1] = nrc;
		XCP_RTE.txLength = 2;
		XCP_RTE.txBufferState = XCP_BUFFER_FULL;
		XCP_RTE.rxBufferState = XCP_BUFFER_IDLE;

		XcpHandleTransmit();
	}
}

static void XcpCmdConnect(void)
{
	uint8 endian;
	uint8 mode;
	uint32 endian_mask = 0xdeadbeef;

	XCP_CHECK(2 <= XCP_RTE.rxLength, "invalid message length!\n");

	mode = XCP_RTE.rxBuffer[1];

	XCP_CHECK(0 == mode, "invalid mode!\n");

	/* report available resources */
	XCP_RTE.txBuffer[1] = 0;
	#ifdef USE_XCP_RES_CALPAG
	XCP_RTE.txBuffer[1] |= XCP_RES_CALPAG;
	#endif

	#ifdef USE_XCP_RES_PGM
	XCP_RTE.txBuffer[1] |= XCP_RES_PGM;
	#endif

	#ifdef USE_XCP_RES_DAQ
	XCP_RTE.txBuffer[1] |= XCP_RES_DAQ;
	#endif

	#ifdef USE_XCP_RES_STIM
	XCP_RTE.txBuffer[1] |= XCP_RES_STIM;
	#endif

	/* report communication mode info. only byte granularity is supported */
	XCP_RTE.txBuffer[2] = 0;
	if(0xde == (*(uint8_t*)&endian_mask))
	{	/* big endian */
		XCP_RTE.txBuffer[2] |= 0x01;
	}
	/* report max cto data length */
	XCP_RTE.txBuffer[3] = XCP_MAX_CTO;
	RWU16(XCP_RTE.txBuffer[4]) = XCP_MAX_DTO;
	/* report msb of protocol layer version number */
	XCP_RTE.txBuffer[6] = 1;

	/* report msb of transport layer version number */
	XCP_RTE.txBuffer[7] = 1;
	XcpSendPRC(7);

	if(0 == (XCP_RTE.flags&XCP_FLAG_CONNECTED))
	{
		XCP_RTE.flags = XCP_FLAG_CONNECTED;
	}
}

static void XcpCmdUnlock(void)
{
	uint8 bOk = TRUE;
	Std_ReturnType ret;
	uint8 res;

	XCP_CHECK((XCP_RTE.rxBuffer[1]+2) <= XCP_RTE.rxLength, "invalid message length!\n");

#ifdef USE_XCP_RES_PGM
	if(XCP_RTE.flags&XCP_FLAG_PGM_SEED_REQUESTED)
	{
		res = XCP_RES_PGM;
	}
	else
#endif
#ifdef USE_XCP_RES_CALPAG
	if(XCP_RTE.flags&XCP_FLAG_CALPAG_SEED_REQUESTED)
	{
		res = XCP_RES_CALPAG;
	}
	else
#endif
	{
		bOk = FALSE;
	}

	if(bOk)
	{
		if(XCP_RTE.rxBuffer[1] <= (XCP_MAX_CTO-2))
		{	/* NOTE: seed&key size should be less or equal than XCP_MAX_CTO-2 */
			ret = Xcp_UnlockFn(res, &XCP_RTE.txBuffer[2], XCP_RTE.txBuffer[1],
						&XCP_RTE.rxBuffer[2], XCP_RTE.rxBuffer[1]);
			if(E_OK == ret)
			{
				XCP_RTE.flags &= ~XCP_FLAG_SEED_REQUESTED_MASK;
				XCP_RTE.flags |= res;
				/* report the current resource protection */
				XCP_RTE.txBuffer[1] = XCP_RTE.flags&XCP_FLAG_RES_MASK;
				XcpSendPRC(1);
			}
			else
			{
				XcpSendNRC(XCP_ERR_ACCESS_LOCKED);
			}
		}
		else
		{
			XcpSendNRC(XCP_ERR_GENERIC);
		}
	}
	else
	{
		XcpSendNRC(XCP_ERR_SEQUENCE);
	}
}

static void XcpCmdGetSeed(void)
{
	uint8 bOk = TRUE;
	uint8 res;

	res  = XCP_RTE.rxBuffer[2];

	XCP_CHECK(3 <= XCP_RTE.rxLength, "invalid message length!\n");
	XCP_CHECK(0 == XCP_RTE.rxBuffer[1], "invalid mode!\n");

#ifdef USE_XCP_RES_PGM
	if(XCP_RES_PGM == res)
	{	/* NOTE: seed&key size should be less or equal than XCP_MAX_CTO-2 */
		XCP_RTE.flags &= ~XCP_FLAG_SEED_REQUESTED_MASK;
		XCP_RTE.flags |= XCP_FLAG_PGM_SEED_REQUESTED;
	}
	else
#endif
#ifdef USE_XCP_RES_CALPAG
	if(XCP_RES_CALPAG == res)
	{	/* NOTE: seed&key size should be less or equal than XCP_MAX_CTO-2 */
		XCP_RTE.flags &= ~XCP_FLAG_SEED_REQUESTED_MASK;
		XCP_RTE.flags |= XCP_FLAG_CALPAG_SEED_REQUESTED;
	}
	else
#endif
	{
		bOk = FALSE;
	}

	if(bOk)
	{
		XCP_RTE.txBuffer[1] = Xcp_SeedFn(res, &XCP_RTE.txBuffer[2]);
		asAssert(XCP_RTE.txBuffer[1] < (XCP_MAX_CTO-2));
		XcpSendPRC(XCP_RTE.txBuffer[1]+1);
	}
	else
	{
		XcpSendNRC(XCP_ERR_OUT_OF_RANGE);
	}
}
#ifdef USE_XCP_RES_PGM
static void XcpCmdProgramStart(void)
{
	XCP_CHECK(1 <= XCP_RTE.rxLength, "invalid message length!\n");
	if(XCP_RTE.flags&XCP_RES_PGM)
	{
		/* initialize reserved parameter */
		XCP_RTE.txBuffer[1] = 0;
		/* no special communication mode supported during programming */
		XCP_RTE.txBuffer[2] = 0;

		/* cto packet length stays the same during programming */
		XCP_RTE.txBuffer[3] = XCP_MAX_CTO;

		/* no block size, st-min time, or queue size supported */
		XCP_RTE.txBuffer[4] = 0;
		XCP_RTE.txBuffer[5] = 0;
		XCP_RTE.txBuffer[6] = 0;

		XCP_RTE.flags |= XCP_FLAG_PGM_STARTED;
		XcpSendPRC(7);
	}
	else
	{
		XcpSendNRC(XCP_ERR_ACCESS_LOCKED);
	}
}

static void XcpCmdProgramClear(void)
{
	uint32 length;

	XCP_CHECK(8 <= XCP_RTE.rxLength, "invalid message length!\n");
	XCP_CHECK(0 == XCP_RTE.rxBuffer[1], "invalid access mode!\n");

	if(XCP_RTE.flags&XCP_RES_PGM)
	{
		if( (XCP_RTE.flags&XCP_FLAG_PGM_STARTED) &&
			(XCP_MTA_ROM == XCP_RTE.mtaExt) )
		{
			length = RWU32(XCP_RTE.rxBuffer[4]);

			if(E_OK == Xcp_FlashErase(XCP_RTE.mtaAddr, length))
			{
				XcpSendPRC(0);
			}
			else
			{
				XcpSendNRC(XCP_ERR_GENERIC);
			}
		}
		else
		{
			XcpSendNRC(XCP_ERR_SEQUENCE);
		}
	}
	else
	{
		XcpSendNRC(XCP_ERR_ACCESS_LOCKED);
	}
}

static void XcpCmdProgramReset(void)
{
	uint32 length;

	XCP_CHECK(1 <= XCP_RTE.rxLength, "invalid message length!\n");

	if(XCP_RTE.flags&XCP_RES_PGM)
	{
		if(XCP_RTE.flags&XCP_FLAG_PGM_STARTED)
		{
			if(E_OK == Xcp_ProgramReset(&XCP_RTE.txBuffer[1], XCP_RTE.rxLength-1))
			{
				XcpSendPRC(0);
			}
			else
			{
				XcpSendNRC(XCP_ERR_GENERIC);
			}
		}
		else
		{
			XcpSendNRC(XCP_ERR_SEQUENCE);
		}
	}
	else
	{
		XcpSendNRC(XCP_ERR_ACCESS_LOCKED);
	}
}
#endif


static void XcpSetMTA(void)
{
	uint8 ext;
	uint32 addr;
	XCP_CHECK(8 <= XCP_RTE.rxLength, "invalid message length!\n");

	ext = RWU16(XCP_RTE.rxBuffer[3]);
	addr = RWU32(XCP_RTE.rxBuffer[4]);

	switch(ext)
	{
		case XCP_MTA_RAM: /* intended no break */
		case XCP_MTA_ROM:
			XCP_RTE.mtaExt = ext;
			XCP_RTE.mtaAddr = addr;
			XcpSendPRC(0);
			break;
		default:
			XcpSendNRC(XCP_ERR_OUT_OF_RANGE);
			break;
	}
}

#ifdef USE_XCP_RES_CALPAG
static void XcpCmdDownload(void)
{
	uint8 doSz;

	XCP_CHECK(2 < XCP_RTE.rxLength, "invalid message length!\n");
	if(XCP_RTE.flags&XCP_RES_CALPAG)
	{
		doSz = XCP_RTE.rxBuffer[1];
		if(doSz <= (XCP_MAX_CTO-2))
		{
			switch(XCP_RTE.mtaExt)
			{
				case XCP_MTA_RAM:
					memcpy((void*)XCP_RTE.mtaAddr, &XCP_RTE.rxBuffer[2], doSz);
					XCP_RTE.mtaAddr += doSz;
					XcpSendPRC(0);
					break;
				case XCP_MTA_ROM:
					if(E_OK == Xcp_FlashWrite(XCP_RTE.mtaAddr, &XCP_RTE.rxBuffer[2], doSz))
					{
						if(0 == memcmp((void*)XCP_RTE.mtaAddr, &XCP_RTE.rxBuffer[2], doSz))
						{
							XCP_RTE.mtaAddr += doSz;
							XcpSendPRC(0);
						}
						else
						{
							XcpSendNRC(XCP_ERR_GENERIC);
						}
					}
					else
					{
						XcpSendNRC(XCP_ERR_SEQUENCE);
					}
					break;
				default:
					XcpSendNRC(XCP_ERR_SEQUENCE);
					break;
			}
		}
		else
		{
			XcpSendNRC(XCP_ERR_OUT_OF_RANGE);
		}
	}
	else
	{
		XcpSendNRC(XCP_ERR_ACCESS_LOCKED);
	}
}

static void XcpCmdUpload(void)
{
	uint8 doSz;

	XCP_CHECK(2 <= XCP_RTE.rxLength, "invalid message length!\n");
	if(XCP_RTE.flags&XCP_RES_CALPAG)
	{
		doSz = XCP_RTE.rxBuffer[1];
		if(doSz <= (XCP_MAX_CTO-1))
		{
			switch(XCP_RTE.mtaExt)
			{
				case XCP_MTA_RAM: /* intended no break */
				case XCP_MTA_ROM:
					memcpy(&XCP_RTE.txBuffer[1], (void*)XCP_RTE.mtaAddr, doSz);
					XCP_RTE.mtaAddr += doSz;
					XcpSendPRC(doSz);
					break;
				default:
					XcpSendNRC(XCP_ERR_SEQUENCE);
					break;
			}
		}
		else
		{
			XcpSendNRC(XCP_ERR_OUT_OF_RANGE);
		}
	}
	else
	{
		XcpSendNRC(XCP_ERR_ACCESS_LOCKED);
	}
}
#endif

static void XcpHandleRequest(void)
{
	uint8 cmd;

	cmd = XCP_RTE.rxBuffer[0];
	XCP_RTE.counter ++;

	ASLOG(XCP, "command %X\n", cmd);
	if(XCP_CMD_CONNECT == cmd)
	{
		XcpCmdConnect();
	}
	else if(XCP_RTE.flags&XCP_FLAG_CONNECTED)
	{
		switch(cmd)
		{
			#ifdef USE_XCP_RES_PGM
			case XCP_CMD_PROGRAM_RESET:
				XcpCmdProgramReset();
				break;
			case XCP_CMD_PROGRAM_CLEAR:
				XcpCmdProgramClear();
				break;
			case XCP_CMD_PROGRAM_START:
				XcpCmdProgramStart();
				break;
			#endif
			#ifdef USE_XCP_RES_CALPAG
			case XCP_CMD_DOWNLOAD:
				XcpCmdDownload();
				break;
			case XCP_CMD_UPLOAD:
				XcpCmdUpload();
				break;
			#endif
			case XCP_CMD_SET_MTA:
				XcpSetMTA();
				break;
			case XCP_CMD_UNLOCK:
				XcpCmdUnlock();
				break;
			case XCP_CMD_GET_SEED:
				XcpCmdGetSeed();
				break;
			default:
				XcpSendNRC(XCP_ERR_CMD_UNKNOWN);
				break;
		}
	}
	else
	{
		ASLOG(XCPE, "no connection!");
	}

	if(0xFF == XCP_RTE.counter)
	{
		XcpReset();
		ASLOG(XCPE, "fatal error as busy of repeat request, timeout!\n");
	}
}

static void XcpHandleTransmit(void)
{
	Std_ReturnType ret = E_OK;
	switch(XCP_RTE.target)
	{
		case XCP_ON_CAN:
			ret = Xcp_CanIfTransmit(XCP_RTE.txBuffer, XCP_RTE.txLength);
			break;
		default:
			ASLOG(XCPE, "fatal error as invalid target, RESET XCP\n");
			XcpReset();
			ret = E_NOT_OK;
			break;
	}

	if(E_OK == ret)
	{	/* yes, this Xcp_Mini will ignore the TX Confirmation */
		XcpCmdServiceDone();
	}
	else
	{
		/* do request transmit next time */
	}
}
/* ============================ [ FUNCTIONS ] ====================================================== */
void Xcp_Init(const Xcp_ConfigType* Xcp_ConfigPtr)
{
	asAssert( 0 == (((uint32)XCP_RTE.rxBuffer) & 0x03));
	asAssert( 0 == (((uint32)XCP_RTE.rxBuffer) & 0x03));
	XcpReset();
}

void Xcp_RxIndication(const uint8* data, PduLengthType len)
{
	if(len <= XCP_MAX_CTO)
	{
		if(XCP_BUFFER_IDLE == XCP_RTE.rxBufferState)
		{
			memcpy(XCP_RTE.rxBuffer, data, len);
			XCP_RTE.rxLength = len;
			XCP_RTE.rxBufferState = XCP_BUFFER_FULL;

			XcpHandleRequest();
		}
		else
		{
			ASLOG(XCPE, "rxBuffer busy!\n");
		}
	}
	else
	{
		ASLOG(XCPE, "rxBuffer overflow(%d < %d)!\n", XCP_MAX_CTO, len);
	}
}

void Xcp_MainFunction(void)
{
	if( (XCP_BUFFER_FULL == XCP_RTE.rxBufferState) &&
		(XCP_BUFFER_IDLE == XCP_RTE.txBufferState) )
	{
		XcpHandleRequest();
	}

	if(XCP_BUFFER_FULL == XCP_RTE.txBufferState)
	{
		XcpHandleTransmit();
	}
}

void Xcp_CanIfRxIndication(PduIdType    XcpRxPduId, PduInfoType* XcpRxPduPtr)
{
	if(XCP_ON_NONE == XCP_RTE.target)
	{
		XCP_RTE.target = XCP_ON_CAN;
		XCP_RTE.LL_DL = CAN_LL_DL;
		Xcp_RxIndication(XcpRxPduPtr->SduDataPtr, XcpRxPduPtr->SduLength);
	}
	else
	{
		ASLOG(XCPE, "busing service on target %d\n", XCP_RTE.target);
	}
}

void Xcp_CanIfTxConfirmation (PduIdType XcpTxPduId)
{
	asAssert(CANIF_ID_XCP_TX == XcpTxPduId);
}

Std_ReturnType Xcp_CanIfTransmit(const void* data, int len)
{
	PduInfoType pdu;
	pdu.SduDataPtr = (uint8*)data;
	pdu.SduLength  = len;
	return CanIf_Transmit(CANIF_ID_XCP_TX, &pdu);
}
