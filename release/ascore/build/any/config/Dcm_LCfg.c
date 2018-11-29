/*
* Configuration of module: Dcm
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
#if defined(USE_DCM) && !defined(USE_DCM_MINI)
#include "Std_Types.h"
#include "Dcm.h"
#include "Dcm_Internal.h"
#if defined(USE_PDUR)
#include "PduR.h"
#endif

#define INDEX_OF_SECURITY_PRGS                             0
#define INDEX_OF_SECURITY_EXTDS                            1
#define INDEX_OF_SECURITY_DS                               2
#define DCM_SECURITY_EOL_INDEX 3

#define INDEX_OF_SESSION_DS                               0
#define INDEX_OF_SESSION_PRGS                             1
#define INDEX_OF_SESSION_EXTDS                            2
#define DCM_SESSION_EOL_INDEX 3

#define DCM_DID_LIST_EOL_INDEX 0


#define INDEX_OF_BUF_Buffer1                          0
#define INDEX_OF_BUF_Buffer2                          1
#define INDEX_OF_BUF_Buffer3                          2
#define INDEX_OF_BUF_Buffer4                          3

#define INDEX_OF_TL_Timing1                          0

#define INDEX_OF_ST_ServiceTableP2P                  0
#define INDEX_OF_ST_ServiceTableP2A                  1

/* --------------------------------------------------------- */

extern Std_ReturnType Diag_GetSeedEXTDS (uint8 *securityAccessDataRecord, uint8 *seed, Dcm_NegativeResponseCodeType *errorCode);
extern Std_ReturnType Diag_CompareKeyEXTDS (uint8 *key);
extern Std_ReturnType Diag_StartProtocolCbk (Dcm_ProtocolType protocolID);
extern Std_ReturnType Diag_StopProtocolCbk (Dcm_ProtocolType protocolID);
extern Std_ReturnType Diag_ProtocolIndicationCbk(uint8 *requestData, uint16 dataSize);

extern Std_ReturnType Diag_GetSesChgPer(Dcm_SesCtrlType sesCtrlTypeActive, Dcm_SesCtrlType sesCtrlTypeNew);
static const Dcm_DspSecurityRowType DspSecurityList[] = {
	{ // PRGS
		.DspSecurityLevel =  6,
		.DspSecurityDelayTimeOnBoot =  0,/* Value is not configurable */
		.DspSecurityNumAttDelay =  0,     /* Value is not configurable */
		.DspSecurityDelayTime =  0,     /* Value is not configurable */
		.DspSecurityNumAttLock =  0,     /* Value is not configurable */
		.DspSecurityADRSize =  0, // TODO:
		.DspSecuritySeedSize =  4,
		.DspSecurityKeySize =  4,
		.GetSeed =  NULL,
		.CompareKey =  NULL,
		.Arc_EOL =  FALSE
	},
	{ // EXTDS
		.DspSecurityLevel =  1,
		.DspSecurityDelayTimeOnBoot =  0,/* Value is not configurable */
		.DspSecurityNumAttDelay =  0,     /* Value is not configurable */
		.DspSecurityDelayTime =  0,     /* Value is not configurable */
		.DspSecurityNumAttLock =  0,     /* Value is not configurable */
		.DspSecurityADRSize =  0, // TODO:
		.DspSecuritySeedSize =  4,
		.DspSecurityKeySize =  4,
		.GetSeed =  Diag_GetSeedEXTDS,
		.CompareKey =  Diag_CompareKeyEXTDS,
		.Arc_EOL =  FALSE
	},
	{ // DS
		.DspSecurityLevel =  0,
		.DspSecurityDelayTimeOnBoot =  0,/* Value is not configurable */
		.DspSecurityNumAttDelay =  0,     /* Value is not configurable */
		.DspSecurityDelayTime =  0,     /* Value is not configurable */
		.DspSecurityNumAttLock =  0,     /* Value is not configurable */
		.DspSecurityADRSize =  0, // TODO:
		.DspSecuritySeedSize =  4,
		.DspSecurityKeySize =  4,
		.GetSeed =  NULL,
		.CompareKey =  NULL,
		.Arc_EOL =  FALSE
	},
	{ 
		.Arc_EOL = TRUE
	}
};

static const Dcm_DspSecurityType DspSecurity = {
    .DspSecurityRow = DspSecurityList
};

static const Dcm_DspSessionRowType DspSessionList[] = {
	{ //DS
		.DspSessionLevel = 1,
		.DspSessionP2ServerMax = 5000,
		.DspSessionP2StarServerMax =  500,
		.Arc_EOL =  FALSE
	},
	{ //PRGS
		.DspSessionLevel = 2,
		.DspSessionP2ServerMax = 5000,
		.DspSessionP2StarServerMax =  500,
		.Arc_EOL =  FALSE
	},
	{ //EXTDS
		.DspSessionLevel = 3,
		.DspSessionP2ServerMax = 5000,
		.DspSessionP2StarServerMax =  500,
		.Arc_EOL =  FALSE
	},
	{ 
		.Arc_EOL = TRUE
	},
};

static const Dcm_DspSessionType DspSession = {
    .DspSessionRow = DspSessionList,
};

const Dcm_DspSecurityRowType *SecurityList_DS_EXTDS_PRGS[] = {
	&DspSecurityList[INDEX_OF_SECURITY_DS],
	&DspSecurityList[INDEX_OF_SECURITY_EXTDS],
	&DspSecurityList[INDEX_OF_SECURITY_PRGS],
	&DspSecurityList[DCM_SECURITY_EOL_INDEX]
};
const Dcm_DspSecurityRowType *SecurityList_EXTDS[] = {
	&DspSecurityList[INDEX_OF_SECURITY_EXTDS],
	&DspSecurityList[DCM_SECURITY_EOL_INDEX]
};
const Dcm_DspSecurityRowType *SecurityList_EXTDS_PRGS[] = {
	&DspSecurityList[INDEX_OF_SECURITY_EXTDS],
	&DspSecurityList[INDEX_OF_SECURITY_PRGS],
	&DspSecurityList[DCM_SECURITY_EOL_INDEX]
};
const Dcm_DspSecurityRowType *SecurityList_DS_EXTDS[] = {
	&DspSecurityList[INDEX_OF_SECURITY_DS],
	&DspSecurityList[INDEX_OF_SECURITY_EXTDS],
	&DspSecurityList[DCM_SECURITY_EOL_INDEX]
};
static const Dcm_DspSessionRowType *SessionList_DS_EXTDS_PRGS[] = {
	&DspSessionList[INDEX_OF_SESSION_DS],
	&DspSessionList[INDEX_OF_SESSION_EXTDS],
	&DspSessionList[INDEX_OF_SESSION_PRGS],
	&DspSessionList[DCM_SECURITY_EOL_INDEX]
};
static const Dcm_DspSessionRowType *SessionList_EXTDS[] = {
	&DspSessionList[INDEX_OF_SESSION_EXTDS],
	&DspSessionList[DCM_SECURITY_EOL_INDEX]
};
static const Dcm_DspSessionRowType *SessionList_EXTDS_PRGS[] = {
	&DspSessionList[INDEX_OF_SESSION_EXTDS],
	&DspSessionList[INDEX_OF_SESSION_PRGS],
	&DspSessionList[DCM_SECURITY_EOL_INDEX]
};
static const Dcm_DspSessionRowType *SessionList_DS_EXTDS[] = {
	&DspSessionList[INDEX_OF_SESSION_DS],
	&DspSessionList[INDEX_OF_SESSION_EXTDS],
	&DspSessionList[DCM_SECURITY_EOL_INDEX]
};

static const Dcm_DspDidInfoType DspDidInfoList[] = {
};

extern const Dcm_DspDidType DspDidList[];
const Dcm_DspDidType DspDidList[] = { 
	{ 		.Arc_EOL =  TRUE
	}
};

/************************************************************************
*                            Routine control                                *
************************************************************************/

static const Dcm_DspRoutineInfoType DspRoutineInfoList[] = {
};

static const Dcm_DspRoutineType  DspRoutineList[] = {
	{
		.Arc_EOL = TRUE
	}
};

/************************************************************************
*                            Memory Info                                 *
************************************************************************/

static const Dcm_DspType Dsp = {
    .DspMaxDidToRead =  0xDB, // TODO
    .DspDid =  DspDidList,
    .DspDidInfo = DspDidInfoList,
    .DspEcuReset = NULL,
    .DspPid =  NULL,
    .DspReadDTC =  NULL,
    .DspRequestControl =  NULL,
    .DspRoutine = DspRoutineList,
    .DspRoutineInfo = DspRoutineInfoList,
    .DspSecurity =  &DspSecurity,
    .DspSession =  &DspSession,
    .DspTestResultByObdmid =  NULL,
    .DspVehInfo = NULL,
    .DspMemory = NULL
};

/************************************************************************
*                                    DSD                                    *
************************************************************************/

static const Dcm_DsdServiceType ServiceTableP2P_serviceList[] = {
	{ 
		.DsdSidTabServiceId = SID_DIAGNOSTIC_SESSION_CONTROL,
		.DsdSidTabSubfuncAvail = TRUE,
		.DsdSidTabSecurityLevelRef = SecurityList_DS_EXTDS_PRGS,
		.DsdSidTabSessionLevelRef = SessionList_DS_EXTDS_PRGS,
		.Arc_EOL = FALSE
	},
	{ 
		.DsdSidTabServiceId = SID_SECURITY_ACCESS,
		.DsdSidTabSubfuncAvail = TRUE,
		.DsdSidTabSecurityLevelRef = SecurityList_DS_EXTDS_PRGS,
		.DsdSidTabSessionLevelRef = SessionList_EXTDS,
		.Arc_EOL = FALSE
	},
	{ 
		.DsdSidTabServiceId = SID_TESTER_PRESENT,
		.DsdSidTabSubfuncAvail = TRUE,
		.DsdSidTabSecurityLevelRef = SecurityList_DS_EXTDS_PRGS,
		.DsdSidTabSessionLevelRef = SessionList_EXTDS,
		.Arc_EOL = FALSE
	},
	{ 
		.DsdSidTabServiceId = SID_ECU_RESET,
		.DsdSidTabSubfuncAvail = TRUE,
		.DsdSidTabSecurityLevelRef = SecurityList_EXTDS,
		.DsdSidTabSessionLevelRef = SessionList_EXTDS,
		.Arc_EOL = FALSE
	},
	{ 
		.DsdSidTabServiceId = SID_READ_DATA_BY_IDENTIFIER,
		.DsdSidTabSubfuncAvail = FALSE,
		.DsdSidTabSecurityLevelRef = SecurityList_EXTDS_PRGS,
		.DsdSidTabSessionLevelRef = SessionList_EXTDS_PRGS,
		.Arc_EOL = FALSE
	},
	{ 
		.DsdSidTabServiceId = SID_READ_DTC_INFORMATION,
		.DsdSidTabSubfuncAvail = TRUE,
		.DsdSidTabSecurityLevelRef = SecurityList_EXTDS,
		.DsdSidTabSessionLevelRef = SessionList_EXTDS,
		.Arc_EOL = FALSE
	},
	{ 
		.DsdSidTabServiceId = SID_CLEAR_DIAGNOSTIC_INFORMATION,
		.DsdSidTabSubfuncAvail = FALSE,
		.DsdSidTabSecurityLevelRef = SecurityList_EXTDS,
		.DsdSidTabSessionLevelRef = SessionList_EXTDS,
		.Arc_EOL = FALSE
	},
	{ 
		.Arc_EOL = TRUE
	}
};

static const Dcm_DsdServiceType ServiceTableP2A_serviceList[] = {
	{ 
		.DsdSidTabServiceId = SID_DIAGNOSTIC_SESSION_CONTROL,
		.DsdSidTabSubfuncAvail = FALSE,
		.DsdSidTabSecurityLevelRef = SecurityList_DS_EXTDS,
		.DsdSidTabSessionLevelRef = SessionList_DS_EXTDS,
		.Arc_EOL = FALSE
	},
	{ 
		.DsdSidTabServiceId = SID_TESTER_PRESENT,
		.DsdSidTabSubfuncAvail = FALSE,
		.DsdSidTabSecurityLevelRef = SecurityList_DS_EXTDS,
		.DsdSidTabSessionLevelRef = SessionList_DS_EXTDS,
		.Arc_EOL = FALSE
	},
	{ 
		.Arc_EOL = TRUE
	}
};

static const Dcm_DsdServiceTableType DsdServiceTable[] = {    
	{ // ServiceTableP2P
		.DsdSidTabId = 0,
		.DsdService = ServiceTableP2P_serviceList,
		.Arc_EOL = FALSE
	},
	{ // ServiceTableP2A
		.DsdSidTabId = 1,
		.DsdService = ServiceTableP2A_serviceList,
		.Arc_EOL = FALSE
	},
	{ 
		.Arc_EOL = TRUE
	}
};

static const Dcm_DsdType Dsd = {
    .DsdServiceTable = DsdServiceTable
};

/************************************************************************
*                                    DSL                                    *
************************************************************************/

static uint8 Buffer1[512];
Dcm_DslBufferRuntimeType rxBufferParams_Buffer1 =
{
    .status =  NOT_IN_USE
};
static uint8 Buffer2[512];
Dcm_DslBufferRuntimeType rxBufferParams_Buffer2 =
{
    .status =  NOT_IN_USE
};
static uint8 Buffer3[512];
Dcm_DslBufferRuntimeType rxBufferParams_Buffer3 =
{
    .status =  NOT_IN_USE
};
static uint8 Buffer4[512];
Dcm_DslBufferRuntimeType rxBufferParams_Buffer4 =
{
    .status =  NOT_IN_USE
};
static const Dcm_DslBufferType DcmDslBufferList[DCM_DSL_BUFFER_LIST_LENGTH] = {
	{
		.DslBufferID =  0,// TODO
		.DslBufferSize = 512,/* ?Value is not configurable */
		.pduInfo={
			.SduDataPtr = Buffer1,
			.SduLength =  512,
		},
		.externalBufferRuntimeData = &rxBufferParams_Buffer1
	},
	{
		.DslBufferID =  1,// TODO
		.DslBufferSize = 512,/* ?Value is not configurable */
		.pduInfo={
			.SduDataPtr = Buffer2,
			.SduLength =  512,
		},
		.externalBufferRuntimeData = &rxBufferParams_Buffer2
	},
	{
		.DslBufferID =  2,// TODO
		.DslBufferSize = 512,/* ?Value is not configurable */
		.pduInfo={
			.SduDataPtr = Buffer3,
			.SduLength =  512,
		},
		.externalBufferRuntimeData = &rxBufferParams_Buffer3
	},
	{
		.DslBufferID =  3,// TODO
		.DslBufferSize = 512,/* ?Value is not configurable */
		.pduInfo={
			.SduDataPtr = Buffer4,
			.SduLength =  512,
		},
		.externalBufferRuntimeData = &rxBufferParams_Buffer4
	},
};

static const Dcm_DslCallbackDCMRequestServiceType DCMRequestServiceList[] = {
	{ // RequestService1
		.StartProtocol = Diag_StartProtocolCbk,
		.StopProtocol = Diag_StopProtocolCbk,
		.Arc_EOL = FALSE
	},
	{
		.Arc_EOL = TRUE
	}
};

static const Dcm_DslServiceRequestIndicationType DCMServiceRequestIndicationList[] = {
	{ // RequestService1
		.Indication =  Diag_ProtocolIndicationCbk,
		.Arc_EOL =  FALSE
	},
	{ 
		.Arc_EOL = TRUE
	}
};

extern const Dcm_DslMainConnectionType DslMainConnectionList[];

static const Dcm_DslProtocolRxType DcmDslProtocolRxList[] = {
	{// P2P->Connection1->RxChannel1
		.DslMainConnectionParent =  &DslMainConnectionList[0],
		.DslProtocolAddrType = DCM_PROTOCOL_PHYSICAL_ADDR_TYPE,
		.DcmDslProtocolRxPduId = PDUR_ID_RxDiagP2P,
		.DcmDslProtocolRxTesterSourceAddr_v4 =  0,       /* Value is not configurable */
		.DcmDslProtocolRxChannelId_v4 =  0,                /* Value is not configurable */
		.Arc_EOL =  FALSE
	},
	{// P2A->Connection1->RxChannel1
		.DslMainConnectionParent =  &DslMainConnectionList[1],
		.DslProtocolAddrType = DCM_PROTOCOL_PHYSICAL_ADDR_TYPE,
		.DcmDslProtocolRxPduId = PDUR_ID_RxDiagP2A,
		.DcmDslProtocolRxTesterSourceAddr_v4 =  0,       /* Value is not configurable */
		.DcmDslProtocolRxChannelId_v4 =  0,                /* Value is not configurable */
		.Arc_EOL =  FALSE
	},
	{
		.Arc_EOL = TRUE
	}
};

static const Dcm_DslProtocolTxType DcmDslProtocolTxList[] = {
	{// P2P->Connection1->TxChannel2
		.DslMainConnectionParent =  &DslMainConnectionList[0],
		.DcmDslProtocolTxPduId =  PDUR_ID_TxDiagP2P,
		.DcmDslProtocolDcmTxPduId =  DCM_ID_TxDiagP2P,
		.Arc_EOL =  FALSE
	},
	{// P2A->Connection1->TxChannel2
		.DslMainConnectionParent =  &DslMainConnectionList[1],
		.DcmDslProtocolTxPduId =  PDUR_ID_TxDiagP2A,
		.DcmDslProtocolDcmTxPduId =  DCM_ID_TxDiagP2A,
		.Arc_EOL =  FALSE
	},
	{
		.Arc_EOL = TRUE
	}
};

extern const Dcm_DslConnectionType DslConnectionList[];

const Dcm_DslMainConnectionType DslMainConnectionList[] = {
	{//P2P->Connection1
		.DslConnectionParent =  &DslConnectionList[0],
		.DslPeriodicTransmissionConRef =  NULL,        /* Value is not configurable */
		.DslROEConnectionRef =  NULL,                /* Value is not configurable */
		.DslProtocolRx =  NULL,                        /* Value is not configurable */
		.DslProtocolTx =  &DcmDslProtocolTxList[0],
	},
	{//P2A->Connection1
		.DslConnectionParent =  &DslConnectionList[1],
		.DslPeriodicTransmissionConRef =  NULL,        /* Value is not configurable */
		.DslROEConnectionRef =  NULL,                /* Value is not configurable */
		.DslProtocolRx =  NULL,                        /* Value is not configurable */
		.DslProtocolTx =  &DcmDslProtocolTxList[1],
	},
};

extern const Dcm_DslProtocolRowType DslProtocolRowList[];

const Dcm_DslConnectionType DslConnectionList[] = {
	{//P2P->Connection1
		.DslProtocolRow = &DslProtocolRowList[0],
		.DslMainConnection = &DslMainConnectionList[0],
		.DslPeriodicTransmission = NULL,    /* Value is not configurable */
		.DslResponseOnEvent = NULL,    /* Value is not configurable */
		.Arc_EOL =  FALSE
	},
	{//P2A->Connection1
		.DslProtocolRow = &DslProtocolRowList[1],
		.DslMainConnection = &DslMainConnectionList[1],
		.DslPeriodicTransmission = NULL,    /* Value is not configurable */
		.DslResponseOnEvent = NULL,    /* Value is not configurable */
		.Arc_EOL =  FALSE
	},
	{
		.Arc_EOL = TRUE
	}
};

extern const Dcm_DslProtocolTimingRowType ProtocolTimingList[];

static Dcm_DslRunTimeProtocolParametersType dcmDslRuntimeVariables[2];
const Dcm_DslProtocolRowType DslProtocolRowList[]= {
	{//P2P
		.DslProtocolID = DCM_UDS_ON_CAN,
		.DslProtocolIsParallelExecutab = FALSE, // not supported
		.DslProtocolPreemptTimeout = 0,    // not supported
		.DslProtocolPriority = 0,    // not supported
		.DslProtocolTransType = DCM_PROTOCOL_TRANS_TYPE_1,
		.DslProtocolRxBufferID = &DcmDslBufferList[INDEX_OF_BUF_Buffer1],
		.DslProtocolTxBufferID = &DcmDslBufferList[INDEX_OF_BUF_Buffer2],
		.DslProtocolSIDTable = &DsdServiceTable[INDEX_OF_ST_ServiceTableP2P],
		.DslProtocolTimeLimit = &ProtocolTimingList[INDEX_OF_TL_Timing1],
		.DslConnection =  DslConnectionList,
		.DslRunTimeProtocolParameters = &dcmDslRuntimeVariables[0],
		.Arc_EOL = FALSE
	},
	{//P2A
		.DslProtocolID = DCM_UDS_ON_CAN,
		.DslProtocolIsParallelExecutab = FALSE, // not supported
		.DslProtocolPreemptTimeout = 0,    // not supported
		.DslProtocolPriority = 0,    // not supported
		.DslProtocolTransType = DCM_PROTOCOL_TRANS_TYPE_1,
		.DslProtocolRxBufferID = &DcmDslBufferList[INDEX_OF_BUF_Buffer3],
		.DslProtocolTxBufferID = &DcmDslBufferList[INDEX_OF_BUF_Buffer4],
		.DslProtocolSIDTable = &DsdServiceTable[INDEX_OF_ST_ServiceTableP2A],
		.DslProtocolTimeLimit = &ProtocolTimingList[INDEX_OF_TL_Timing1],
		.DslConnection =  DslConnectionList,
		.DslRunTimeProtocolParameters = &dcmDslRuntimeVariables[1],
		.Arc_EOL = FALSE
	},
	{
		.Arc_EOL = TRUE
	}
};

static const Dcm_DslProtocolType DslProtocol = {
    .DslProtocolRxGlobalList = DcmDslProtocolRxList,
    .DslProtocolTxGlobalList = DcmDslProtocolTxList,
    .DslProtocolRowList = DslProtocolRowList
};

const Dcm_DslProtocolTimingRowType ProtocolTimingList[] = {
	{//Timing1
		.TimStrP2ServerMax = 5000,
		.TimStrP2ServerMin = 3000,
		.TimStrP2StarServerMax = 0,        /* Value is not configurable */
		.TimStrP2StarServerMin = 0,        /* Value is not configurable */
		.TimStrS3Server = 10000,
		.Arc_EOL = FALSE
	},
	{
		.Arc_EOL =  TRUE
	},
};

static const Dcm_DslProtocolTimingType ProtocolTiming = {
    .DslProtocolTimingRow = ProtocolTimingList
};

static const Dcm_DslSessionControlType SessionControlList[] = {
	{//SessionControl1
		.GetSesChgPermission = Diag_GetSesChgPer,
		.ChangeIndication = NULL,
		.ConfirmationRespPend = NULL,
		.Arc_EOL = FALSE
	},
	{
		.Arc_EOL = TRUE
	}
};

static const Dcm_DslDiagRespType DiagResp = {
    .DslDiagRespForceRespPendEn = TRUE,
    .DslDiagRespMaxNumRespPend =  100  /* if P2Server=100ms, so 10s totally */
};

static const Dcm_DslType Dsl = {
    .DslBuffer =  DcmDslBufferList,
    .DslCallbackDCMRequestService = DCMRequestServiceList,
    .DslDiagResp = &DiagResp,
    .DslProtocol =  &DslProtocol,
    .DslProtocolTiming = &ProtocolTiming,
    .DslServiceRequestIndication = DCMServiceRequestIndicationList,
    .DslSessionControl = SessionControlList
};

const Dcm_ConfigType DCM_Config = {
    .Dsp = &Dsp,
    .Dsd = &Dsd,
    .Dsl = &Dsl
};
#endif /* USE_DCM */
