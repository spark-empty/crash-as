<?xml version='1.0' encoding='utf-8'?>

<AUTOSAR>
<OS>
<General Comment="*" Conformance="ECC1" ErrorHook="ErrorHook" PTHREAD="0" PTHREAD_PRIORITY="32" PostTaskHook="PostTaskHook" PreTaskHook="PreTaskHook" ProtectionHook="NULL" ShutdownHook="ShutdownHook" StartupHook="StartupHook" Status="EXTENDED" />
<ApplicationModeList Max="TBD" />
<ApplicationList Max="TBD" />
<TaskList Max="TBD" />
<AlarmList Max="TBD" />
<CounterList Max="TBD" />
<ResourceList Max="TBD" />
<InternalResourceList Max="TBD" />
</OS>
<EcuC>
<PduList Max="TBD">
<Pdu Comment="*" Name="TxDiagP2P" Size="64" />
<Pdu Comment="*" Name="RxDiagP2P" Size="64" />
<Pdu Comment="*" Name="XCP_RX" Size="64" />
<Pdu Comment="*" Name="XCP_TX" Size="64" />
<Pdu Comment="*" Name="SOAD_RX" Size="64" />
<Pdu Comment="*" Name="SOAD_TX" Size="64" />
</PduList>
</EcuC>
<Can>
<General Comment="*" DevelopmentErrorDetection="ON" VersionInfoApi="ON" />
<ControllerList Max="TBD">
<Controller Baudrate="1000" Comment="*" Name="CAN_CTRL_0" Seg1="13" Seg2="2">
<HohList Max="TBD">
<Hoh Comment="*" HohType="BASIC" IdentifierType="STANDARD" Name="Can0Hrh" ObjectType="RECEIVE" />
<Hoh Comment="*" HohType="BASIC" IdentifierType="STANDARD" Name="Can0Hth" ObjectType="TRANSMIT" />
</HohList>
</Controller>
</ControllerList>
</Can>
<CanIf>
<General BusOffNotification="NULL" Comment="*" DataLengthCodeCheck="ON" DevelopmentErrorDetection="ON" ErrorNotification="NULL" RxFifoSize="32" TaskFifoMode="ON" TxFifoSize="32" VersionInfoApi="OFF" />
<ChannelList Max="TBD">
<Channel Comment="*" ControllerRef="CAN_CTRL_0" Name="CANIF_CHL_LS">
<HthList Max="TBD">
<Hth Comment="*" HthRef="Can0Hth" Name="LS_Hth" />
</HthList>
<TxPduList Max="TBD">
<Pdu Comment="*" DataLengthCode="8" EcuCPduRef="TxDiagP2P" HthRef="LS_Hth" Identifier="0x732" Name="P2P" TransmitNotifier="CanTp" UserNotification="CanIf_User" />
<Pdu Comment="*" DataLengthCode="8" EcuCPduRef="XCP_TX" HthRef="LS_Hth" Identifier="0x555" Name="XCP_TX" TransmitNotifier="Xcp" UserNotification="CanIf_User" />
</TxPduList>
<HrhList Max="TBD">
<Hrh Comment="*" HrhRef="Can0Hrh" Name="LS_Hrh" SoftwareFilterUsed="True" />
</HrhList>
<RxPduList Max="TBD">
<Pdu Comment="*" DataLengthCode="8" EcuCPduRef="RxDiagP2P" FilterMask="0x7FF" HrhRef="LS_Hrh" Identifier="0x731" Name="P2P" ReceivedNotifier="CanTp" UserNotification="CanIf_UserRxIndication" />
<Pdu Comment="*" DataLengthCode="1" EcuCPduRef="XCP_RX" FilterMask="0x7FF" HrhRef="LS_Hrh" Identifier="0x554" Name="XCP_RX" ReceivedNotifier="Xcp" UserNotification="CanIf_UserRxIndication" />
</RxPduList>
</Channel>
</ChannelList>
</CanIf>
<CanTp>
<General Comment="*" DevelopmentErrorDetection="ON" VersionInfoApi="OFF" />
<RxSduList Max="TBD">
<Sdu BS="8" Comment="*" CommunicationType="PHYSICAL" MaxBusyTransmission="10" Name="SduP2P" Nar="25" Nbr="25" Ncr="150" Padding="ON" RxPduRef="RxDiagP2P" STmin="1" TxFcPduRef="TxDiagP2P" ll_dl="64" />
</RxSduList>
<TxSduList Max="TBD">
<Sdu Comment="Generally for Nbs, it's 75ms, here as the qemu CAN simulation is not real time, so set it to a bigger value ." CommunicationType="PHYSICAL" Name="SduP2P" Nas="25" Nbs="250" Ncs="25" Padding="ON" RxFcPduRef="RxDiagP2P" TxPduRef="TxDiagP2P" ll_dl="64" />
</TxSduList>
</CanTp>
<PduR>
<General CanIfUsed="False" CanTpUsed="True" ComUsed="False" Comment="*" DcmUsed="True" DevelopmentErrorDetection="ON" J1939TpUsed="False" LinIfUsed="False" LinTpUsed="False" VersionInfoApi="OFF" ZeroCostIf="CanIf" ZeroCostOperationMode="OFF" ZeroCostTp="CanTp" />
<RoutineList Max="TBD">
<Source Comment="*" Module="Dcm" Name="DcmP2P" PduRef="TxDiagP2P">
<DestinationList Max="TBD">
<Destination Comment="*" Module="CanTp" Name="CanTpP2P" PduRef="TxDiagP2P" />
</DestinationList>
</Source>
<Source Comment="*" Module="CanTp" Name="CanTpP2P" PduRef="RxDiagP2P">
<DestinationList Max="TBD">
<Destination Comment="*" Module="Dcm" Name="DcmP2P" PduRef="RxDiagP2P" />
</DestinationList>
</Source>
<Source Comment="*" Module="Dcm" Name="DoIP_TX" PduRef="SOAD_TX">
<DestinationList Max="TBD">
<Destination Comment="*" Module="SoAdTp" Name="Destination1" PduRef="SOAD_TX" />
</DestinationList>
</Source>
<Source Comment="*" Module="SoAdTp" Name="DoIP_RX" PduRef="SOAD_RX">
<DestinationList Max="TBD">
<Destination Comment="*" Module="Dcm" Name="Destination1" PduRef="SOAD_RX" />
</DestinationList>
</Source>
</RoutineList>
</PduR>
<Com>
<General Comment="*" DevelopmentErrorDetection="ON" VersionInfoApi="OFF" />
<PduGroupList Max="TBD" />
<IPduList Max="TBD" />
</Com>
<Dcm>
<General Comment="*" DevelopmentErrorDetection="ON" MaxPeriodDIDNumber="8" PeriodicDIDFastModeTime="50" PeriodicDIDMediumModeTime="100" PeriodicDIDSlowModeTime="200" VersionInfoApi="OFF" />
<BufferList Max="TBD">
<Buffer Comment="rx buffer" Name="Buffer1" Size="4095" />
<Buffer Comment="tx buffer" Name="Buffer2" Size="4095" />
</BufferList>
<SessionList Max="TBD">
<Session Comment="*" Identifier="1" Name="DS" P2ServerMaxTimeMs="100" P2StartServerMaxTimeMs="100" />
<Session Comment="*" Identifier="2" Name="PRGS" P2ServerMaxTimeMs="100" P2StartServerMaxTimeMs="100" />
<Session Comment="*" Identifier="3" Name="EXTDS" P2ServerMaxTimeMs="100" P2StartServerMaxTimeMs="100" />
</SessionList>
<SecurityList Max="TBD">
<Security Comment="*" CompareKeyCallback="BL_CompareProgramSessionKey" GetSeedCallback="BL_GetProgramSessionSeed" Identifier="2" KeySize="4" Name="PRGS" SeedSize="4" />
<Security Comment="*" CompareKeyCallback="BL_CompareExtendedSessionKey" GetSeedCallback="BL_GetExtendedSessionSeed" Identifier="1" KeySize="4" Name="EXTDS" SeedSize="4" />
<Security Comment="Level 0, is the default for each session when enterred" CompareKeyCallback="NULL" GetSeedCallback="NULL" Identifier="0" KeySize="4" Name="Default" SeedSize="4" />
</SecurityList>
<DIDControlRecordList Max="TBD" />
<DIDInfoList Max="TBD" />
<DIDList Max="TBD" />
<RoutineInfoList Max="TBD">
<RoutineInfo Comment="*" Name="RoutineInfo_EraseFlash">
<SessionList Max="TBD">
<Session Comment="*" Name="PRGS" />
</SessionList>
<SecurityList Max="TBD">
<Security Comment="*" Name="PRGS" />
</SecurityList>
<Start Comment="4 byte address, 4 byte size, 1 byte identifier" RecordSizeOfRequest="9" RecordSizeOfResponse="0" />
</RoutineInfo>
<RoutineInfo Comment="*" Name="RoutineInfo_TestJumpToApplication">
<SessionList Max="TBD">
<Session Comment="*" Name="PRGS" />
</SessionList>
<SecurityList Max="TBD">
<Security Comment="*" Name="PRGS" />
</SecurityList>
<Start Comment="direct jump to application and no response" RecordSizeOfRequest="0" RecordSizeOfResponse="0" />
</RoutineInfo>
</RoutineInfoList>
<RoutineList Max="TBD">
<Routine Comment="*" Identifier="0xFF01" Name="EraseFlash" RoutineInfoRef="RoutineInfo_EraseFlash" RoutineResultCbk="NULL" StartRoutineCbk="BL_StartEraseFlash" StopRoutineCbk="NULL" />
<Routine Comment="*" Identifier="0xFF03" Name="TestJumpToApplication" RoutineInfoRef="RoutineInfo_TestJumpToApplication" RoutineResultCbk="NULL" StartRoutineCbk="BL_TestJumpToApplicatin" StopRoutineCbk="NULL" />
</RoutineList>
<MemoryList Max="TBD">
<Memory Comment="*" Identifier="0xFF" Name="Flash">
<MemoryReadInfoList Max="TBD">
<MemoryInfo AddressHigh="0x00010000" AddressLow="0x00000000" Comment="0~64K for bootloader for STM32F107VC" Name="Bootloader">
<SecurityList Max="TBD">
<Security Comment="*" Name="PRGS" />
</SecurityList>
</MemoryInfo>
<MemoryInfo AddressHigh="0x00040000" AddressLow="0x00010000" Comment="64K~256K for application for STM32F017VC" Name="Application">
<SecurityList Max="TBD">
<Security Comment="*" Name="PRGS" />
</SecurityList>
</MemoryInfo>
<MemoryInfo AddressHigh="0x08000000" AddressLow="0x00040000" Comment="*" Name="AppBcm2835">
<SecurityList Max="TBD">
<Security Comment="*" Name="PRGS" />
</SecurityList>
</MemoryInfo>
<MemoryInfo AddressHigh="0x00180000" AddressLow="0x00020000" Comment="*" Name="MPC56xx">
<SecurityList Max="TBD">
<Security Comment="*" Name="PRGS" />
</SecurityList>
</MemoryInfo>
</MemoryReadInfoList>
<MemoryWriteInfoList Max="TBD">
<MemoryInfo AddressHigh="0x00040000" AddressLow="0x00010000" Comment="*" Name="Application">
<SecurityList Max="TBD">
<Security Comment="*" Name="PRGS" />
</SecurityList>
</MemoryInfo>
<MemoryInfo AddressHigh="0x08000000" AddressLow="0x00040000" Comment="*" Name="AppBcm2835">
<SecurityList Max="TBD">
<Security Comment="*" Name="PRGS" />
</SecurityList>
</MemoryInfo>
<MemoryInfo AddressHigh="0x00180000" AddressLow="0x00020000" Comment="*" Name="MPC56xx">
<SecurityList Max="TBD">
<Security Comment="*" Name="PRGS" />
</SecurityList>
</MemoryInfo>
</MemoryWriteInfoList>
</Memory>
<Memory Comment="*" Identifier="0xEE" Name="Eeprom">
<MemoryReadInfoList Max="TBD">
<MemoryInfo AddressHigh="256" AddressLow="0" Comment="0~256 for bootloader information storage" Name="Bootloader">
<SecurityList Max="TBD">
<Security Comment="*" Name="PRGS" />
</SecurityList>
</MemoryInfo>
<MemoryInfo AddressHigh="4096" AddressLow="256" Comment="*" Name="Application">
<SecurityList Max="TBD">
<Security Comment="*" Name="PRGS" />
</SecurityList>
</MemoryInfo>
</MemoryReadInfoList>
<MemoryWriteInfoList Max="TBD">
<MemoryInfo AddressHigh="256" AddressLow="0" Comment="*" Name="Bootloader">
<SecurityList Max="TBD">
<Security Comment="*" Name="PRGS" />
</SecurityList>
</MemoryInfo>
<MemoryInfo AddressHigh="4096" AddressLow="256" Comment="*" Name="Application">
<SecurityList Max="TBD">
<Security Comment="*" Name="PRGS" />
</SecurityList>
</MemoryInfo>
</MemoryWriteInfoList>
</Memory>
<Memory Comment="*" Identifier="0xFD" Name="FlashDriver">
<MemoryReadInfoList Max="TBD">
<MemoryInfo AddressHigh="4096" AddressLow="0" Comment="*" Name="FlashDriver">
<SecurityList Max="TBD">
<Security Comment="*" Name="PRGS" />
</SecurityList>
</MemoryInfo>
</MemoryReadInfoList>
<MemoryWriteInfoList Max="TBD">
<MemoryInfo AddressHigh="4096" AddressLow="0" Comment="*" Name="FlashDriver">
<SecurityList Max="TBD">
<Security Comment="*" Name="PRGS" />
</SecurityList>
</MemoryInfo>
</MemoryWriteInfoList>
</Memory>
</MemoryList>
<ProtocolList Max="TBD">
<Protocol Comment="*" Name="P2P" ProtocolID="UDS_ON_CAN" RxBufferRef="Buffer1" ServiceTableRef="ServiceTable1" TimingLimitRef="Timing1" TransmissionType="TYPE_1" TxBufferRef="Buffer2">
<ConnectionList Max="TBD">
<Connection Comment="*" Name="Connection1">
<RxChannelList Max="TBD">
<RxChannel AddressingType="PHYSICAL" Comment="*" Name="RxChannel1" PduRef="RxDiagP2P" />
</RxChannelList>
<TxChannel Comment="*" Name="TxChannel2" PduRef="TxDiagP2P" />
</Connection>
</ConnectionList>
</Protocol>
<Protocol Comment="*" Name="DoIP" ProtocolID="UDS_ON_DOIP" RxBufferRef="Buffer1" ServiceTableRef="ServiceTable1" TimingLimitRef="Timing1" TransmissionType="TYPE_1" TxBufferRef="Buffer2">
<ConnectionList Max="TBD">
<Connection Comment="*" Name="Connection1">
<RxChannelList Max="TBD">
<RxChannel AddressingType="PHYSICAL" Comment="*" Name="RxChannel1" PduRef="SOAD_RX" />
</RxChannelList>
<TxChannel Comment="*" Name="TBD" PduRef="SOAD_TX" />
</Connection>
</ConnectionList>
</Protocol>
</ProtocolList>
<RequestServiceList Max="TBD">
<RequestService Comment="*" Name="RequestService1" ProtocolIndicationCbk="BL_ProtocolIndicationCbk" StartProtocolCbk="BL_StartProtocolCbk" StopProtocolCbk="BL_StopProtocolCbk" />
</RequestServiceList>
<ServiceTableList Max="TBD">
<ServiceTable Comment="*" Name="ServiceTable1">
<ServiceList Max="TBD">
<Service Comment="*" Name="DIAGNOSTIC_SESSION_CONTROL" SubFunctionSupported="True">
<SecurityList Max="TBD">
<Security Comment="*" Name="PRGS" />
<Security Comment="*" Name="EXTDS" />
<Security Comment="*" Name="Default" />
</SecurityList>
<SessionList Max="TBD">
<Session Comment="*" Name="DS" />
<Session Comment="*" Name="PRGS" />
<Session Comment="*" Name="EXTDS" />
</SessionList>
</Service>
<Service Comment="*" Name="SECURITY_ACCESS" SubFunctionSupported="True">
<SecurityList Max="TBD">
<Security Comment="*" Name="PRGS" />
<Security Comment="*" Name="EXTDS" />
<Security Comment="*" Name="Default" />
</SecurityList>
<SessionList Max="TBD">
<Session Comment="*" Name="PRGS" />
<Session Comment="*" Name="EXTDS" />
</SessionList>
</Service>
<Service Comment="*" Name="TESTER_PRESENT" SubFunctionSupported="True">
<SecurityList Max="TBD">
<Security Comment="*" Name="PRGS" />
<Security Comment="*" Name="EXTDS" />
</SecurityList>
<SessionList Max="TBD">
<Session Comment="*" Name="PRGS" />
<Session Comment="*" Name="EXTDS" />
</SessionList>
</Service>
<Service Comment="*" Name="ROUTINE_CONTROL" SubFunctionSupported="True">
<SecurityList Max="TBD">
<Security Comment="*" Name="PRGS" />
<Security Comment="*" Name="EXTDS" />
</SecurityList>
<SessionList Max="TBD">
<Session Comment="*" Name="PRGS" />
<Session Comment="*" Name="EXTDS" />
</SessionList>
</Service>
<Service Comment="*" Name="ECU_RESET" SubFunctionSupported="True">
<SecurityList Max="TBD">
<Security Comment="*" Name="PRGS" />
<Security Comment="*" Name="EXTDS" />
</SecurityList>
<SessionList Max="TBD">
<Session Comment="*" Name="PRGS" />
<Session Comment="*" Name="EXTDS" />
</SessionList>
</Service>
<Service Comment="*" Name="REQUEST_DOWNLOAD" SubFunctionSupported="False">
<SecurityList Max="TBD">
<Security Comment="*" Name="PRGS" />
</SecurityList>
<SessionList Max="TBD">
<Session Comment="*" Name="PRGS" />
</SessionList>
</Service>
<Service Comment="*" Name="REQUEST_UPLOAD" SubFunctionSupported="False">
<SecurityList Max="TBD">
<Security Comment="*" Name="PRGS" />
</SecurityList>
<SessionList Max="TBD">
<Session Comment="*" Name="PRGS" />
</SessionList>
</Service>
<Service Comment="*" Name="TRANSFER_DATA" SubFunctionSupported="False">
<SecurityList Max="TBD">
<Security Comment="*" Name="PRGS" />
</SecurityList>
<SessionList Max="TBD">
<Session Comment="*" Name="PRGS" />
</SessionList>
</Service>
<Service Comment="*" Name="REQUEST_TRANSFER_EXIT" SubFunctionSupported="False">
<SecurityList Max="TBD">
<Security Comment="*" Name="PRGS" />
</SecurityList>
<SessionList Max="TBD">
<Session Comment="*" Name="PRGS" />
</SessionList>
</Service>
</ServiceList>
</ServiceTable>
</ServiceTableList>
<SessionControlList Max="TBD">
<SessionControl Comment="*" GetSessionChangePermissionCbk="BL_GetSessionChangePermission" Name="SessionControl" />
</SessionControlList>
<TimingList Max="TBD">
<Timing Comment="*" Name="Timing1" P2ServerMaxTimeMs="100" P2ServerMinTimeMs="20" S3ServerTimeMs="5000" />
</TimingList>
</Dcm>
<Fls>
<General Comment="*" DevelopmentErrorDetection="OFF" FlashBaseAddress="0" MaxFastReadSize="512" MaxFastWriteSize="32" MaxNormalReadSize="32" MaxNormalWriteSize="8" VersionInfoApi="OFF" />
<SectorList Max="TBD" />
</Fls>
<Fee>
<General Comment="*" DevelopmentErrorDetection="OFF" NvmJobEndNotification="NULL" NvmJobErrorNotification="NULL" PollingMode="ON" VersionInfoApi="OFF" VirtualPageSize="8" />
<BlockList Max="TBD" />
</Fee>
<Ea>
<General Comment="*" DevelopmentErrorDetection="OFF" NvmJobEndNotification="NULL" NvmJobErrorNotification="NULL" SetModeApi="ON" VersionInfoApi="OFF" VirtualPageSize="8" />
<BlockList Max="TBD" />
</Ea>
<NvM>
<General Comment="*" ConfigClass="CLASS_2" DevelopmentErrorDetection="OFF" ImmediateJobQueueSize="8" MultiBlockCallback="NULL" PollingMode="ON" RamBlockStatusApi="ON" StandardJobQueueSize="8" VersionInfoApi="OFF" />
<BlockList Max="TBD" />
</NvM>
<Xcp>
<General Comment="*" DevelopmentErrorDetection="OFF" VersionInfoApi="OFF" XcpCounterRef="TBD" XcpDaqConfigType="DAQ_STATIC" XcpDaqCount="8" XcpFlashProgrammingEnabled="True" XcpIdentificationFieldType="ABSOLUTE" XcpMainFunctionPeriod="10" XcpMaxCto="8" XcpMaxDto="8" XcpMaxEventChannel="8" XcpMaxRxTxQueue="32" XcpMinDaq="0" XcpNvRamBlockIdRef="TBD" XcpOdtCount="56" XcpOdtEntriesCount="112" XcpOdtEntrySizeDaq="0" XcpOdtEntrySizeStim="0" XcpPrescalerSupported="True" XcpProtocal="CAN" XcpSuppressTxSupport="True" XcpTimestampTicks="1" XcpTimestampType="FOUR_BYTE" XcpTimestampUnit="1ms" />
<XcpStaticDaqList Max="TBD" />
<XcpEventChannelList Max="TBD" />
</Xcp>
<Rte>
<DataTypeList Max="TBD" />
<ConstantList Max="TBD" />
<SwcList Max="TBD" />
</Rte>
<Dem>
<General Comment="*" DEM_CLEAR_ALL_EVENTS="OFF" DEM_DTC_STATUS_AVAILABILITY_MASK="0xFF" DEM_MAX_NUMBER_FF_DATA_PRI_MEM="5" DEM_OBD_SUPPORT="OFF" DEM_PTO_SUPPORT="OFF" DEM_TYPE_OF_DTC_SUPPORTED="0x01" DEM_USE_NVM="ON" DevelopmentErrorDetection="OFF" NvMFreezeFrameBlock="TBD" NvMHealingBlock="TBD" VersionInfoApi="OFF" />
<ExtendedDataRecordClassList Max="TBD" />
<DTCClassList Max="TBD" />
<FFIdClassList Max="TBD" />
<FreezeFrameClassList Max="TBD" />
<EventClassList Max="TBD" />
<EventParameterList Max="TBD" />
</Dem>
<J1939Tp>
<General Comment="*" DevelopmentErrorDetection="OFF" PACKETS_PER_BLOCK="8" TX_CONF_TIMEOUT="1000" VersionInfoApi="OFF" />
<ChannelList Max="TBD" />
<ParameterGroupList Max="TBD" />
<PduInfoList Max="TBD" />
</J1939Tp>
</AUTOSAR>
