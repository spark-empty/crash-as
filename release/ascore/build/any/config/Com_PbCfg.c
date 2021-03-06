/*
* Configuration of module: Com
*
* Created by:   parai
* Copyright:    (C)parai@foxmail.com  
*
* Configured for (MCU):    posix
*
* Module vendor:           ArcCore
* Generator version:       01.00
*
* Generated by easySAR Studio (https://github.com/parai/as)
*/

#ifdef USE_COM
#include "Com.h"
#include "Com_Internal.h"
#if defined(USE_PDUR)
#include "PduR.h"
#endif 

//Signal init values.
static const uint16 VehicleSpeed_InitValue = 0;
static const uint16 TachoSpeed_InitValue = 0;
static const uint8 Led1Sts_InitValue = 0;
static const uint8 Led2Sts_InitValue = 0;
static const uint8 Led3Sts_InitValue = 0;
static uint8 SystemTime_ShadowBuffer[8];
static const uint8 SystemTime_InitValue[8] = {0x07,0xDD,0x0C,0x0F,0x13,0x31,0x00,0x00,};
static const uint8 SystemTime_ShadowBufferMask[8]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,};
static const uint16 year_InitValue = 2013;
static const uint8 month_InitValue = 12;
static const uint8 day_InitValue = 15;
static const uint8 hour_InitValue = 19;
static const uint8 minute_InitValue = 49;
static const uint8 second_InitValue = 0;

static const ComGroupSignal_type ComGroupSignal[] = {
    
    {
        #if defined(USE_SHELL)
        .name = "year",
        #endif
        .ComBitPosition= 7,
        .ComBitSize= 16,
        .ComHandleId= COM_GSID_year,
        .ComSignalEndianess= COM_BIG_ENDIAN,
        .ComSignalInitValue= &year_InitValue,
        .ComSignalType= COM_SIGNAL_TYPE_UINT16,
        .Com_Arc_EOL= FALSE
    },
    
    {
        #if defined(USE_SHELL)
        .name = "month",
        #endif
        .ComBitPosition= 23,
        .ComBitSize= 8,
        .ComHandleId= COM_GSID_month,
        .ComSignalEndianess= COM_BIG_ENDIAN,
        .ComSignalInitValue= &month_InitValue,
        .ComSignalType= COM_SIGNAL_TYPE_UINT8,
        .Com_Arc_EOL= FALSE
    },
    
    {
        #if defined(USE_SHELL)
        .name = "day",
        #endif
        .ComBitPosition= 31,
        .ComBitSize= 8,
        .ComHandleId= COM_GSID_day,
        .ComSignalEndianess= COM_BIG_ENDIAN,
        .ComSignalInitValue= &day_InitValue,
        .ComSignalType= COM_SIGNAL_TYPE_UINT8,
        .Com_Arc_EOL= FALSE
    },
    
    {
        #if defined(USE_SHELL)
        .name = "hour",
        #endif
        .ComBitPosition= 39,
        .ComBitSize= 8,
        .ComHandleId= COM_GSID_hour,
        .ComSignalEndianess= COM_BIG_ENDIAN,
        .ComSignalInitValue= &hour_InitValue,
        .ComSignalType= COM_SIGNAL_TYPE_UINT8,
        .Com_Arc_EOL= FALSE
    },
    
    {
        #if defined(USE_SHELL)
        .name = "minute",
        #endif
        .ComBitPosition= 47,
        .ComBitSize= 8,
        .ComHandleId= COM_GSID_minute,
        .ComSignalEndianess= COM_BIG_ENDIAN,
        .ComSignalInitValue= &minute_InitValue,
        .ComSignalType= COM_SIGNAL_TYPE_UINT8,
        .Com_Arc_EOL= FALSE
    },
    
    {
        #if defined(USE_SHELL)
        .name = "second",
        #endif
        .ComBitPosition= 55,
        .ComBitSize= 8,
        .ComHandleId= COM_GSID_second,
        .ComSignalEndianess= COM_BIG_ENDIAN,
        .ComSignalInitValue= &second_InitValue,
        .ComSignalType= COM_SIGNAL_TYPE_UINT8,
        .Com_Arc_EOL= FALSE
    },

};
//SignalGroup GroupSignals lists.
static const ComGroupSignal_type * const SystemTime_GrpSignalRefs[] =
{
	&ComGroupSignal[ COM_GSID_year ],
	&ComGroupSignal[ COM_GSID_month ],
	&ComGroupSignal[ COM_GSID_day ],
	&ComGroupSignal[ COM_GSID_hour ],
	&ComGroupSignal[ COM_GSID_minute ],
	&ComGroupSignal[ COM_GSID_second ],
	NULL
};


//IPdu buffers and signal group buffers
static uint8 RxMsgAbsInfo_IPduBuffer[8];
static uint8 RxMsgAbsInfo_IPduDefferredBuffer[8];
static uint8 TxMsgTime_IPduBuffer[8];

//Signal definitions
static const ComSignal_type ComSignal[] = {

    {
        #if defined(USE_SHELL)
        .name = "VehicleSpeed",
        #endif
        .ComBitPosition = 7,
        .ComBitSize = 16,
        .ComErrorNotification = NULL,
        .ComFirstTimeoutFactor = (100+COM_MAIN_FUNCTION_RX_PERIOD-1)/COM_MAIN_FUNCTION_RX_PERIOD,
        .ComHandleId = COM_SID_VehicleSpeed,
        .ComNotification = NULL,
        .ComRxDataTimeoutAction = COM_TIMEOUT_DATA_ACTION_NONE,
        .ComSignalEndianess = COM_BIG_ENDIAN,
        .ComSignalInitValue = &VehicleSpeed_InitValue,
        .ComSignalType = COM_SIGNAL_TYPE_UINT16,
        .ComTimeoutFactor = (100+COM_MAIN_FUNCTION_RX_PERIOD-1)/COM_MAIN_FUNCTION_RX_PERIOD,
        .ComTimeoutNotification = NULL,
        .ComTransferProperty = COM_PENDING,
        .ComUpdateBitPosition = 0xDB,
        .ComSignalArcUseUpdateBit = FALSE,
        .Com_Arc_IsSignalGroup = FALSE,
        .ComGroupSignal = NULL,
        .Com_Arc_ShadowBuffer = NULL,
        .Com_Arc_ShadowBuffer_Mask = NULL,
        .ComIPduHandleId = COM_ID_RxMsgAbsInfo,
        .Com_Arc_EOL = FALSE
    },

    {
        #if defined(USE_SHELL)
        .name = "TachoSpeed",
        #endif
        .ComBitPosition = 23,
        .ComBitSize = 16,
        .ComErrorNotification = NULL,
        .ComFirstTimeoutFactor = (100+COM_MAIN_FUNCTION_RX_PERIOD-1)/COM_MAIN_FUNCTION_RX_PERIOD,
        .ComHandleId = COM_SID_TachoSpeed,
        .ComNotification = NULL,
        .ComRxDataTimeoutAction = COM_TIMEOUT_DATA_ACTION_NONE,
        .ComSignalEndianess = COM_BIG_ENDIAN,
        .ComSignalInitValue = &TachoSpeed_InitValue,
        .ComSignalType = COM_SIGNAL_TYPE_UINT16,
        .ComTimeoutFactor = (100+COM_MAIN_FUNCTION_RX_PERIOD-1)/COM_MAIN_FUNCTION_RX_PERIOD,
        .ComTimeoutNotification = NULL,
        .ComTransferProperty = COM_PENDING,
        .ComUpdateBitPosition = 0xDB,
        .ComSignalArcUseUpdateBit = FALSE,
        .Com_Arc_IsSignalGroup = FALSE,
        .ComGroupSignal = NULL,
        .Com_Arc_ShadowBuffer = NULL,
        .Com_Arc_ShadowBuffer_Mask = NULL,
        .ComIPduHandleId = COM_ID_RxMsgAbsInfo,
        .Com_Arc_EOL = FALSE
    },

    {
        #if defined(USE_SHELL)
        .name = "Led1Sts",
        #endif
        .ComBitPosition = 39,
        .ComBitSize = 2,
        .ComErrorNotification = NULL,
        .ComFirstTimeoutFactor = (500+COM_MAIN_FUNCTION_RX_PERIOD-1)/COM_MAIN_FUNCTION_RX_PERIOD,
        .ComHandleId = COM_SID_Led1Sts,
        .ComNotification = NULL,
        .ComRxDataTimeoutAction = COM_TIMEOUT_DATA_ACTION_NONE,
        .ComSignalEndianess = COM_BIG_ENDIAN,
        .ComSignalInitValue = &Led1Sts_InitValue,
        .ComSignalType = COM_SIGNAL_TYPE_UINT8,
        .ComTimeoutFactor = (500+COM_MAIN_FUNCTION_RX_PERIOD-1)/COM_MAIN_FUNCTION_RX_PERIOD,
        .ComTimeoutNotification = NULL,
        .ComTransferProperty = COM_PENDING,
        .ComUpdateBitPosition = 0xDB,
        .ComSignalArcUseUpdateBit = FALSE,
        .Com_Arc_IsSignalGroup = FALSE,
        .ComGroupSignal = NULL,
        .Com_Arc_ShadowBuffer = NULL,
        .Com_Arc_ShadowBuffer_Mask = NULL,
        .ComIPduHandleId = COM_ID_RxMsgAbsInfo,
        .Com_Arc_EOL = FALSE
    },

    {
        #if defined(USE_SHELL)
        .name = "Led2Sts",
        #endif
        .ComBitPosition = 37,
        .ComBitSize = 2,
        .ComErrorNotification = NULL,
        .ComFirstTimeoutFactor = (500+COM_MAIN_FUNCTION_RX_PERIOD-1)/COM_MAIN_FUNCTION_RX_PERIOD,
        .ComHandleId = COM_SID_Led2Sts,
        .ComNotification = NULL,
        .ComRxDataTimeoutAction = COM_TIMEOUT_DATA_ACTION_NONE,
        .ComSignalEndianess = COM_BIG_ENDIAN,
        .ComSignalInitValue = &Led2Sts_InitValue,
        .ComSignalType = COM_SIGNAL_TYPE_UINT8,
        .ComTimeoutFactor = (500+COM_MAIN_FUNCTION_RX_PERIOD-1)/COM_MAIN_FUNCTION_RX_PERIOD,
        .ComTimeoutNotification = NULL,
        .ComTransferProperty = COM_PENDING,
        .ComUpdateBitPosition = 0xDB,
        .ComSignalArcUseUpdateBit = FALSE,
        .Com_Arc_IsSignalGroup = FALSE,
        .ComGroupSignal = NULL,
        .Com_Arc_ShadowBuffer = NULL,
        .Com_Arc_ShadowBuffer_Mask = NULL,
        .ComIPduHandleId = COM_ID_RxMsgAbsInfo,
        .Com_Arc_EOL = FALSE
    },

    {
        #if defined(USE_SHELL)
        .name = "Led3Sts",
        #endif
        .ComBitPosition = 35,
        .ComBitSize = 2,
        .ComErrorNotification = NULL,
        .ComFirstTimeoutFactor = (500+COM_MAIN_FUNCTION_RX_PERIOD-1)/COM_MAIN_FUNCTION_RX_PERIOD,
        .ComHandleId = COM_SID_Led3Sts,
        .ComNotification = NULL,
        .ComRxDataTimeoutAction = COM_TIMEOUT_DATA_ACTION_NONE,
        .ComSignalEndianess = COM_BIG_ENDIAN,
        .ComSignalInitValue = &Led3Sts_InitValue,
        .ComSignalType = COM_SIGNAL_TYPE_UINT8,
        .ComTimeoutFactor = (500+COM_MAIN_FUNCTION_RX_PERIOD-1)/COM_MAIN_FUNCTION_RX_PERIOD,
        .ComTimeoutNotification = NULL,
        .ComTransferProperty = COM_PENDING,
        .ComUpdateBitPosition = 0xDB,
        .ComSignalArcUseUpdateBit = FALSE,
        .Com_Arc_IsSignalGroup = FALSE,
        .ComGroupSignal = NULL,
        .Com_Arc_ShadowBuffer = NULL,
        .Com_Arc_ShadowBuffer_Mask = NULL,
        .ComIPduHandleId = COM_ID_RxMsgAbsInfo,
        .Com_Arc_EOL = FALSE
    },

    {
        #if defined(USE_SHELL)
        .name = "SystemTime",
        #endif
        .ComBitPosition = 0,
        .ComBitSize = 56,
        .ComErrorNotification = NULL,
        .ComFirstTimeoutFactor = 0,
        .ComHandleId = COM_SID_SystemTime,
        .ComNotification = NULL,
        .ComRxDataTimeoutAction = COM_TIMEOUT_DATA_ACTION_NONE,
        .ComSignalEndianess = COM_OPAQUE,
        .ComSignalInitValue = SystemTime_InitValue,
        .ComSignalType = COM_SIGNAL_TYPE_UINT8_N,
        .ComTimeoutFactor = 0,
        .ComTimeoutNotification = NULL,
        .ComTransferProperty = COM_PENDING,
        .ComUpdateBitPosition = 0,
        .ComSignalArcUseUpdateBit = FALSE,
        .Com_Arc_IsSignalGroup = TRUE,
        .ComGroupSignal = SystemTime_GrpSignalRefs,
        .Com_Arc_ShadowBuffer = SystemTime_ShadowBuffer,
        .Com_Arc_ShadowBuffer_Mask = SystemTime_ShadowBufferMask,
        .ComIPduHandleId = COM_ID_TxMsgTime,
        .Com_Arc_EOL = FALSE
    },

    {
         .Com_Arc_EOL =  True,
    }
};

    
//I-PDU group definitions
static const ComIPduGroup_type ComIPduGroup[] = {

    {
        .ComIPduGroupHandleId =  COM_IPDU_GROUP_PduGroup1, 
        .Com_Arc_EOL =  FALSE
    },

};


//IPdu signal lists.
static const ComSignal_type * const RxMsgAbsInfo_SignalRefs[] = {
	&ComSignal[ COM_SID_VehicleSpeed ],
	&ComSignal[ COM_SID_TachoSpeed ],
	&ComSignal[ COM_SID_Led1Sts ],
	&ComSignal[ COM_SID_Led2Sts ],
	&ComSignal[ COM_SID_Led3Sts ],
	NULL
};
static const ComSignal_type * const TxMsgTime_SignalRefs[] = {
	&ComSignal[ COM_SID_SystemTime ],
	NULL
};
    
    
//I-PDU definitions
static const ComIPdu_type ComIPdu[] = {

    {
        #if defined(USE_SHELL)
        .name = "AbsInfo",
        #endif
        .ComIPduCallout =  NULL,
        .ArcIPduOutgoingId =  PDUR_ID_RxMsgAbsInfo,
        .ComIPduSignalProcessing =  COM_DEFERRED,
        .ComIPduSize =  8,
        .ComIPduDirection =  COM_RECEIVE,
        .ComIPduGroupRef =  COM_IPDU_GROUP_PduGroup1,
        .ComTxIPdu ={
            .ComTxIPduMinimumDelayFactor =  1,
            .ComTxIPduUnusedAreasDefault =  0x5A,
            .ComTxModeTrue ={
                .ComTxModeMode =   COM_PERIODIC,
                .ComTxModeNumberOfRepetitions =   0,
                .ComTxModeRepetitionPeriodFactor =   10,
                .ComTxModeTimeOffsetFactor =   (0+COM_MAIN_FUNCTION_TX_PERIOD-1)/COM_MAIN_FUNCTION_TX_PERIOD,
                .ComTxModeTimePeriodFactor =   (10+COM_MAIN_FUNCTION_TX_PERIOD-1)/COM_MAIN_FUNCTION_TX_PERIOD,
            },
        },
        .ComIPduDataPtr =  RxMsgAbsInfo_IPduBuffer,
        .ComIPduDeferredDataPtr =  RxMsgAbsInfo_IPduDefferredBuffer,
        .ComIPduSignalRef =  RxMsgAbsInfo_SignalRefs,
        .ComIPduDynSignalRef =  NULL,
        .Com_Arc_EOL =  FALSE,
    },

    {
        #if defined(USE_SHELL)
        .name = "MsgTime",
        #endif
        .ComIPduCallout =  NULL,
        .ArcIPduOutgoingId =  PDUR_ID_TxMsgTime,
        .ComIPduSignalProcessing =  COM_DEFERRED,
        .ComIPduSize =  8,
        .ComIPduDirection =  COM_SEND,
        .ComIPduGroupRef =  COM_IPDU_GROUP_PduGroup1,
        .ComTxIPdu ={
            .ComTxIPduMinimumDelayFactor =  1,
            .ComTxIPduUnusedAreasDefault =  0x5A,
            .ComTxModeTrue ={
                .ComTxModeMode =   COM_PERIODIC,
                .ComTxModeNumberOfRepetitions =   0,
                .ComTxModeRepetitionPeriodFactor =   10,
                .ComTxModeTimeOffsetFactor =   (0+COM_MAIN_FUNCTION_TX_PERIOD-1)/COM_MAIN_FUNCTION_TX_PERIOD,
                .ComTxModeTimePeriodFactor =   (100+COM_MAIN_FUNCTION_TX_PERIOD-1)/COM_MAIN_FUNCTION_TX_PERIOD,
            },
        },
        .ComIPduDataPtr =  TxMsgTime_IPduBuffer,
        .ComIPduDeferredDataPtr =  NULL,
        .ComIPduSignalRef =  TxMsgTime_SignalRefs,
        .ComIPduDynSignalRef =  NULL,
        .Com_Arc_EOL =  FALSE,
    },

    {
        .Com_Arc_EOL =  TRUE
    }
};

const Com_ConfigType ComConfiguration = {
    .ComConfigurationId =  1,
    .ComIPdu =  ComIPdu,
    .ComIPduGroup =  ComIPduGroup,
    .ComSignal =  ComSignal,
#if(COM_N_GROUP_SIGNALS > 0)
    .ComGroupSignal =  ComGroupSignal
#else
    .ComGroupSignal =  NULL
#endif
};

static Com_Arc_IPdu_type Com_Arc_IPdu[] = {

    { // RxMsgAbsInfo
        .Com_Arc_TxIPduTimers ={
            .ComTxIPduNumberOfRepetitionsLeft =  0,
            .ComTxModeRepetitionPeriodTimer =  0,
            .ComTxIPduMinimumDelayTimer =  0,
            .ComTxModeTimePeriodTimer =  0
        },
        .Com_Arc_IpduStarted =  0
    },

    { // TxMsgTime
        .Com_Arc_TxIPduTimers ={
            .ComTxIPduNumberOfRepetitionsLeft =  0,
            .ComTxModeRepetitionPeriodTimer =  0,
            .ComTxIPduMinimumDelayTimer =  0,
            .ComTxModeTimePeriodTimer =  0
        },
        .Com_Arc_IpduStarted =  0
    },
};

Com_Arc_Signal_type Com_Arc_Signal[] = {

    { // VehicleSpeed
        .Com_Arc_DeadlineCounter =  0,
        .ComSignalUpdated =  0,
    },

    { // TachoSpeed
        .Com_Arc_DeadlineCounter =  0,
        .ComSignalUpdated =  0,
    },

    { // Led1Sts
        .Com_Arc_DeadlineCounter =  0,
        .ComSignalUpdated =  0,
    },

    { // Led2Sts
        .Com_Arc_DeadlineCounter =  0,
        .ComSignalUpdated =  0,
    },

    { // Led3Sts
        .Com_Arc_DeadlineCounter =  0,
        .ComSignalUpdated =  0,
    },
};

   
#if(COM_N_GROUP_SIGNALS > 0)
static Com_Arc_GroupSignal_type Com_Arc_GroupSignal[COM_N_GROUP_SIGNALS];
#endif

const Com_Arc_Config_type Com_Arc_Config = {
    .ComIPdu =  Com_Arc_IPdu,
    .ComSignal =  Com_Arc_Signal,
#if(COM_N_GROUP_SIGNALS > 0)
    .ComGroupSignal =  Com_Arc_GroupSignal
#else
    .ComGroupSignal =  NULL
#endif
};
#endif /* USE_COM */
