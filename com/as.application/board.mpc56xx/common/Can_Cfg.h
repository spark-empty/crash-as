/*
* Configuration of module: Can (Can_Cfg.h)
*
* Created by:  parai
* Copyright:
*
* Configured for (MCU):    MPC56XX
*
* Module vendor:           ArcCore
*
*/


#if !(((CAN_SW_MAJOR_VERSION == 1) && (CAN_SW_MINOR_VERSION == 0)) )
#error Can: Configuration file expected BSW module version to be 1.0.*
#endif

	

#ifndef CAN_CFG_H_
#define CAN_CFG_H_

// Number of controller configs
#define CAN_ARC_CTRL_CONFIG_CNT		1

#define CAN_DEV_ERROR_DETECT			STD_OFF
#define CAN_VERSION_INFO_API			STD_OFF
#define CAN_MULTIPLEXED_TRANSMISSION	STD_OFF  // Not supported
#define CAN_WAKEUP_SUPPORT				STD_OFF  // Not supported
#define CAN_HW_TRANSMIT_CANCELLATION	STD_OFF  // Not supported

#define INDEX_OF_CAN_CTRL_0 0

#define CAN_CTRL_A CAN_CTRL_0
#define CAN_CTRL_C CAN_CTRL_1

#define FLEXCAN_A CAN_CTRL_A
typedef enum {
	CAN_CTRL_0 = 0,
	CAN_CTRL_1 = 1,
	CAN_CONTROLLER_CNT = 2
}CanControllerIdType;


typedef enum {
	CAN_ID_TYPE_EXTENDED,
	CAN_ID_TYPE_MIXED,
	CAN_ID_TYPE_STANDARD
} Can_IdTypeType;

typedef enum {
	CAN_OBJECT_TYPE_RECEIVE,
	CAN_OBJECT_TYPE_TRANSMIT
} Can_ObjectTypeType;


typedef enum {
	CAN_ARC_HANDLE_TYPE_BASIC,
	CAN_ARC_HANDLE_TYPE_FULL
} Can_Arc_HohType;

#define Can0Hth CanAHth
typedef enum {
	CanAHth,
	NUM_OF_HTHS
} Can_Arc_HTHType;

#define Can0Hrh CanAHrh
typedef enum {
	CanAHrh,
	NUM_OF_HRHS
} Can_Arc_HRHType;


/* check page 395 of MPC563XMRM.pdf*/
enum {
	FLEXCAN_A_ESR_BOFF_INT = 152,
	FLEXCAN_A_ESR_ERR_INT,
	FLEXCAN_A_WAKEUP_INT,
	FLEXCAN_A_IFLAG1_BUF0I,
	FLEXCAN_A_IFLAG1_BUF1I,
	FLEXCAN_A_IFLAG1_BUF2I,
	FLEXCAN_A_IFLAG1_BUF3I,
	FLEXCAN_A_IFLAG1_BUF4I,
	FLEXCAN_A_IFLAG1_BUF5I,
	FLEXCAN_A_IFLAG1_BUF6I,
	FLEXCAN_A_IFLAG1_BUF7I,
	FLEXCAN_A_IFLAG1_BUF8I,
	FLEXCAN_A_IFLAG1_BUF9I,
	FLEXCAN_A_IFLAG1_BUF10I,
	FLEXCAN_A_IFLAG1_BUF11I,
	FLEXCAN_A_IFLAG1_BUF12I,
	FLEXCAN_A_IFLAG1_BUF13I,
	FLEXCAN_A_IFLAG1_BUF14I,
	FLEXCAN_A_IFLAG1_BUF15I,
	FLEXCAN_A_IFLAG1_BUF31_16I,
	FLEXCAN_A_IFLAG1_BUF63_32I,

	FLEXCAN_C_ESR_BOFF_INT,
	FLEXCAN_C_ESR_ERR_INT,
	FLEXCAN_C_WAKEUP_INT,
	FLEXCAN_C_IFLAG1_BUF0I,
	FLEXCAN_C_IFLAG1_BUF1I,
	FLEXCAN_C_IFLAG1_BUF2I,
	FLEXCAN_C_IFLAG1_BUF3I,
	FLEXCAN_C_IFLAG1_BUF4I,
	FLEXCAN_C_IFLAG1_BUF5I,
	FLEXCAN_C_IFLAG1_BUF6I,
	FLEXCAN_C_IFLAG1_BUF7I,
	FLEXCAN_C_IFLAG1_BUF8I,
	FLEXCAN_C_IFLAG1_BUF9I,
	FLEXCAN_C_IFLAG1_BUF10I,
	FLEXCAN_C_IFLAG1_BUF11I,
	FLEXCAN_C_IFLAG1_BUF12I,
	FLEXCAN_C_IFLAG1_BUF13I,
	FLEXCAN_C_IFLAG1_BUF14I,
	FLEXCAN_C_IFLAG1_BUF15I,
	FLEXCAN_C_IFLAG1_BUF31_16I,
	FLEXCAN_C_IFLAG1_BUF63_32I,
};

typedef struct {
	void (*CancelTxConfirmation)( const Can_PduType *);
	void (*RxIndication)( uint16 ,Can_IdType ,uint8 , const uint8 * );
	void (*ControllerBusOff)(uint8);
	void (*TxConfirmation)(PduIdType);
	void (*ControllerWakeup)(uint8);
	void (*Arc_Error)(uint8,Can_Arc_ErrorType);
} Can_CallbackType;

typedef uint32 Can_FilterMaskType;

typedef struct Can_HardwareObjectStruct {
	// Specifies the type (Full-CAN or Basic-CAN) of a hardware object.
	Can_Arc_HohType CanHandleType;

	// Specifies whether the IdValue is of type - standard identifier - extended
	// identifier - mixed mode ImplementationType: Can_IdType
	Can_IdTypeType CanIdType;

	//	Specifies (together with the filter mask) the identifiers range that passes
	//	the hardware filter.
	uint32 CanIdValue;

	//	Holds the handle ID of HRH or HTH. The value of this parameter is unique
	//	in a given CAN Driver, and it should start with 0 and continue without any
	//	gaps. The HRH and HTH Ids are defined under two different name-spaces.
	//	Example: HRH0-0, HRH1-1, HTH0-2, HTH1-3
	uint32 CanObjectId;

	// Specifies if the HardwareObject is used as Transmit or as Receive object
	Can_ObjectTypeType CanObjectType;

	// Reference to the filter mask that is used for hardware filtering togerther
	// with the CAN_ID_VALUE
	Can_FilterMaskType CanFilterMaskRef;

	// A "1" in this mask tells the driver that that HW Message Box should be
	// occupied by this Hoh. A "1" in bit 31(ppc) occupies Mb 0 in HW.
	uint64 ArcMailboxMask;
	
} Can_HardwareObjectType;


#define CAN_CTRL_BUSOFF_PROCESSING_INTERRUPT 0x01
#define CAN_CTRL_RX_PROCESSING_INTERRUPT     0x02
#define CAN_CTRL_TX_PROCESSING_INTERRUPT     0x04
#define CAN_CTRL_ERROR_PROCESSING_INTERRUPT  0x08
#define CAN_CTRL_LOOPBACK                    0x10
#define CAN_CTRL_FIFO                        0x20

typedef struct {
	// Specifies the buadrate of the controller in kbps.
	uint32 CanControllerBaudRate;

	//	This parameter provides the controller ID which is unique in a given CAN
	//	Driver. The value for this parameter starts with 0 and continue without any
	//	gaps.
	CanControllerIdType CanControllerId;

	// Specifies propagation delay in time quantas.
	uint32 CanControllerPropSeg;

	// Specifies phase segment 1 in time quantas.
	uint32 CanControllerSeg1;

	// Specifies phase segment 2 in time quantas.
	uint32 CanControllerSeg2;

	uint32 CanControllerRJW;

	//	Reference to the CPU clock configuration, which is set in the MCU driver
	//	configuration
	uint32 CanCpuClockRef;

	uint64 Can_Arc_RxMailBoxMask;
	uint64 Can_Arc_TxMailBoxMask;

	// List of Hoh id's that belong to this controller
	const Can_HardwareObjectType  *Can_Arc_Hoh;
	const uint8 *Can_Arc_MailBoxToHrh;
	PduIdType * Can_Arc_TxPduHandles;
	uint8 Can_Arc_TxMailboxStart;

	uint8 Can_Arc_Flags;

	uint8 Can_Arc_HohCnt;
	uint8 Can_Arc_HohFifoCnt;
	uint8 Can_Arc_MailboxMax;

} Can_ControllerConfigType;


typedef struct {
	const Can_ControllerConfigType *CanController;
	
	// Callbacks( Extension )
	const Can_CallbackType *CanCallbacks;

	const uint8 *ArcHthToUnit;
	const uint8 *ArcHthToHoh;
	const uint8 *ArcCtrlToUnit;
} Can_ConfigSetType;


typedef struct {
	// This is the multiple configuration set container for CAN Driver
	// Multiplicity 1..*
	const Can_ConfigSetType	 *CanConfigSet;
} Can_ConfigType;


extern const Can_ConfigType Can_ConfigData;
extern const Can_ControllerConfigType Can_ControllerCfgData[];
extern const Can_ConfigSetType Can_ConfigSet;

#endif /*CAN_CFG_H_*/
