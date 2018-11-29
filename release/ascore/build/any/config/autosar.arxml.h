<?xml version='1.0' encoding='utf-8'?>

<AUTOSAR>
<OS>
<General Comment="Not Used" Conformance="ECC1" ErrorHook="ErrorHook" PTHREAD="32" PTHREAD_PRIORITY="32" PostTaskHook="PostTaskHook" PreTaskHook="PreTaskHook" ProtectionHook="NULL" ShutdownHook="ShutdownHook" StartupHook="StartupHook" Status="EXTENDED" />
<ApplicationModeList Max="TBD">
<ApplicationMode Comment="*" Name="OSDEFAULTAPPMODE" />
</ApplicationModeList>
<ApplicationList Max="TBD">
<Application Comment="*" Name="OsDefaultApp" RestartTask="SchM_Startup" Trusted="True" UseRestartTask="True" />
</ApplicationList>
<TaskList Max="TBD">
<Task Activation="1" Application="OsDefaultApp" Autostart="True" Comment="*" Name="SchM_Startup" Priority="7" Schedule="FULL" StackSize="2048">
<ApplicationModeList Max="TBD">
<ApplicationMode Comment="*" Name="OSDEFAULTAPPMODE" />
</ApplicationModeList>
</Task>
<Task Activation="1" Application="OsDefaultApp" Autostart="False" Comment="*" Name="SchM_BswService" Priority="8" Schedule="FULL" StackSize="2048" />
<Task Activation="1" Application="OsDefaultApp" Autostart="False" Comment="Send" Name="Task2" Priority="8" Schedule="FULL" StackSize="2048">
<ApplicationModeList Max="TBD">
<ApplicationMode Comment="*" Name="OSDEFAULTAPPMODE" />
</ApplicationModeList>
</Task>
<Task Activation="1" Application="OsDefaultApp" Autostart="False" Comment="Receive" Name="Task1" Priority="8" Schedule="FULL" StackSize="2048">
<ApplicationModeList Max="TBD">
<ApplicationMode Comment="*" Name="OSDEFAULTAPPMODE" />
</ApplicationModeList>
</Task>
</TaskList>
<AlarmList Max="TBD">
<Alarm Action="ActivateTask" Application="OsDefaultApp" Autostart="False" Callback="TBD" Comment="*" Counter="OsClock" Event="TBD" Name="Alarm_BswService" Period="100" StartTime="0" Task="SchM_BswService" />
<Alarm Action="ActivateTask" Application="OsDefaultApp" Autostart="Absolute" Callback="TBD" Comment="Send" Counter="OsClock" Event="TBD" Name="SendData" Period="1000" StartTime="10" Task="Task2">
<ApplicationModeList Max="TBD">
<ApplicationMode Comment="*" Name="OSDEFAULTAPPMODE" />
</ApplicationModeList>
</Alarm>
<Alarm Action="ActivateTask" Application="OsDefaultApp" Autostart="Absolute" Callback="TBD" Comment="Receive" Counter="OsClock" Event="TBD" Name="ReceiveData" Period="1000" StartTime="20" Task="Task1">
<ApplicationModeList Max="TBD">
<ApplicationMode Comment="*" Name="OSDEFAULTAPPMODE" />
</ApplicationModeList>
</Alarm>
</AlarmList>
<CounterList Max="TBD">
<Counter Application="OsDefaultApp" Comment="*" MaxAllowed="0xFFFF" MinCycle="1" Name="OsClock" TicksPerBase="1" />
</CounterList>
<ResourceList Max="TBD">
<Resource Application="TBD" Comment="*" Name="RES_SCHEDULER" Priority="15" />
</ResourceList>
<InternalResourceList Max="TBD" />
</OS>
<EcuC>
<PduList Max="TBD">
<Pdu Comment="*" Name="TxDiagP2P" Size="64" />
<Pdu Comment="*" Name="RxDiagP2P" Size="64" />
<Pdu Comment="*" Name="TxDiagP2A" Size="64" />
<Pdu Comment="*" Name="RxDiagP2A" Size="64" />
<Pdu Comment="*" Name="TxMsgTime" Size="64" />
<Pdu Comment="*" Name="RxMsgAbsInfo" Size="64" />
<Pdu Comment="*" Name="LS_NM_TX" Size="64" />
<Pdu Comment="*" Name="OSEK_NM_TX" Size="64" />
<Pdu Comment="*" Name="OSEK_NM_RX" Size="64" />
<Pdu Comment="*" Name="XCP_RX" Size="64" />
<Pdu Comment="*" Name="XCP_TX" Size="64" />
<Pdu Comment="*" Name="SOAD_RX" Size="64" />
<Pdu Comment="*" Name="SOAD_TX" Size="64" />
<Pdu Comment="*" Name="STDIN" Size="64" />
<Pdu Comment="*" Name="STDOUT" Size="64" />
<Pdu Comment="*" Name="RX_J1939TP_REVERSE_CM" Size="64" />
<Pdu Comment="*" Name="RX_J1939TP_DT" Size="64" />
<Pdu Comment="*" Name="RX_J1939TP_CM" Size="64" />
<Pdu Comment="*" Name="RX_J1939TP_DIRECT" Size="64" />
<Pdu Comment="*" Name="TX_J1939TP_CmNPdu" Size="64" />
<Pdu Comment="*" Name="TX_J1939TP_DtNPdu" Size="64" />
<Pdu Comment="*" Name="TX_J1939TP_FcNPdu" Size="64" />
<Pdu Comment="*" Name="TX_J1939TP_DirectNPdu" Size="64" />
<Pdu Comment="*" Name="J1939TP_RX" Size="64" />
<Pdu Comment="*" Name="J1939TP_TX" Size="64" />
<Pdu Comment="*" Name="RxMsgLedInfo" Size="64" />
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
<Pdu Comment="*" DataLengthCode="8" EcuCPduRef="TxDiagP2A" HthRef="LS_Hth" Identifier="0x744" Name="P2A" TransmitNotifier="CanTp" UserNotification="CanIf_User" />
<Pdu Comment="*" DataLengthCode="8" EcuCPduRef="LS_NM_TX" HthRef="LS_Hth" Identifier="0x502" Name="LS_NM" TransmitNotifier="CanNm" UserNotification="CanIf_User" />
<Pdu Comment="*" DataLengthCode="8" EcuCPduRef="TxMsgTime" HthRef="LS_Hth" Identifier="0x101" Name="Time" TransmitNotifier="PduR" UserNotification="CanIf_User" />
<Pdu Comment="*" DataLengthCode="8" EcuCPduRef="OSEK_NM_TX" HthRef="LS_Hth" Identifier="0x401" Name="OSEK_NM_TX" TransmitNotifier="User" UserNotification="CanIf_OsekNmUser" />
<Pdu Comment="*" DataLengthCode="8" EcuCPduRef="XCP_TX" HthRef="LS_Hth" Identifier="0x555" Name="XCP_TX" TransmitNotifier="Xcp" UserNotification="CanIf_User" />
<Pdu Comment="*" DataLengthCode="8" EcuCPduRef="STDOUT" HthRef="LS_Hth" Identifier="0x702" Name="STDOUT" TransmitNotifier="User" UserNotification="CanIf_Stdio" />
<Pdu Comment="*" DataLengthCode="8" EcuCPduRef="TX_J1939TP_CmNPdu" HthRef="LS_Hth" Identifier="0x761" Name="TX_J1939TP_CmNPdu" TransmitNotifier="J1939Tp" UserNotification="CanIf_User" />
<Pdu Comment="*" DataLengthCode="8" EcuCPduRef="TX_J1939TP_DtNPdu" HthRef="LS_Hth" Identifier="0x762" Name="TX_J1939TP_DtNPdu" TransmitNotifier="J1939Tp" UserNotification="CanIf_User" />
<Pdu Comment="*" DataLengthCode="8" EcuCPduRef="TX_J1939TP_FcNPdu" HthRef="LS_Hth" Identifier="0x763" Name="TX_J1939TP_FcNPdu" TransmitNotifier="J1939Tp" UserNotification="CanIf_User" />
<Pdu Comment="*" DataLengthCode="8" EcuCPduRef="TX_J1939TP_DirectNPdu" HthRef="LS_Hth" Identifier="0x764" Name="TX_J1939TP_DirectNPdu" TransmitNotifier="J1939Tp" UserNotification="CanIf_User" />
</TxPduList>
<HrhList Max="TBD">
<Hrh Comment="*" HrhRef="Can0Hrh" Name="LS_Hrh" SoftwareFilterUsed="True" />
</HrhList>
<RxPduList Max="TBD">
<Pdu Comment="*" DataLengthCode="8" EcuCPduRef="RxDiagP2P" FilterMask="0x7FF" HrhRef="LS_Hrh" Identifier="0x731" Name="P2P" ReceivedNotifier="CanTp" UserNotification="CanIf_UserRxIndication" />
<Pdu Comment="*" DataLengthCode="8" EcuCPduRef="RxDiagP2A" FilterMask="0x7FF" HrhRef="LS_Hrh" Identifier="0x743" Name="P2A" ReceivedNotifier="CanTp" UserNotification="CanIf_UserRxIndication" />
<Pdu Comment="*" DataLengthCode="8" EcuCPduRef="RxMsgAbsInfo" FilterMask="0x7FF" HrhRef="LS_Hrh" Identifier="0x102" Name="AbsInfo" ReceivedNotifier="PduR" UserNotification="CanIf_UserRxIndication" />
<Pdu Comment="*" DataLengthCode="8" EcuCPduRef="OSEK_NM_RX" FilterMask="0x7FF" HrhRef="LS_Hrh" Identifier="0x400" Name="OSEK_NM_RX" ReceivedNotifier="User" UserNotification="CanIf_OsekNmUser" />
<Pdu Comment="*" DataLengthCode="1" EcuCPduRef="XCP_RX" FilterMask="0x7FF" HrhRef="LS_Hrh" Identifier="0x554" Name="XCP_RX" ReceivedNotifier="Xcp" UserNotification="CanIf_UserRxIndication" />
<Pdu Comment="*" DataLengthCode="1" EcuCPduRef="STDIN" FilterMask="0x7FF" HrhRef="LS_Hrh" Identifier="0x701" Name="STDIN" ReceivedNotifier="User" UserNotification="CanIf_Stdio" />
<Pdu Comment="*" DataLengthCode="1" EcuCPduRef="RX_J1939TP_REVERSE_CM" FilterMask="0x7FF" HrhRef="LS_Hrh" Identifier="0x751" Name="RX_J1939TP_REVERSE_CM" ReceivedNotifier="J1939Tp" UserNotification="CanIf_UserRxIndication" />
<Pdu Comment="*" DataLengthCode="1" EcuCPduRef="RX_J1939TP_DT" FilterMask="0x7FF" HrhRef="LS_Hrh" Identifier="0x752" Name="RX_J1939TP_DT" ReceivedNotifier="J1939Tp" UserNotification="CanIf_UserRxIndication" />
<Pdu Comment="*" DataLengthCode="1" EcuCPduRef="RX_J1939TP_CM" FilterMask="0x7FF" HrhRef="LS_Hrh" Identifier="0x753" Name="RX_J1939TP_CM" ReceivedNotifier="J1939Tp" UserNotification="CanIf_UserRxIndication" />
<Pdu Comment="*" DataLengthCode="1" EcuCPduRef="RX_J1939TP_DIRECT" FilterMask="0x7FF" HrhRef="LS_Hrh" Identifier="0x754" Name="RX_J1939TP_DIRECT" ReceivedNotifier="J1939Tp" UserNotification="CanIf_UserRxIndication" />
<Pdu Comment="*" DataLengthCode="8" EcuCPduRef="RxMsgLedInfo" FilterMask="0x7FF" HrhRef="LS_Hrh" Identifier="0x106" Name="LedInfo" ReceivedNotifier="PduR" UserNotification="CanIf_UserRxIndication" />
</RxPduList>
</Channel>
</ChannelList>
</CanIf>
<CanTp>
<General Comment="*" DevelopmentErrorDetection="ON" VersionInfoApi="OFF" />
<RxSduList Max="TBD">
<Sdu BS="8" Comment="*" CommunicationType="PHYSICAL" MaxBusyTransmission="10" Name="SduP2P" Nar="100" Nbr="100" Ncr="100" Padding="ON" RxPduRef="RxDiagP2P" STmin="1" TxFcPduRef="TxDiagP2P" ll_dl="64" />
<Sdu BS="8" Comment="*" CommunicationType="PHYSICAL" MaxBusyTransmission="10" Name="SduP2A" Nar="100" Nbr="100" Ncr="100" Padding="ON" RxPduRef="RxDiagP2A" STmin="1" TxFcPduRef="TxDiagP2A" ll_dl="64" />
</RxSduList>
<TxSduList Max="TBD">
<Sdu Comment="*" CommunicationType="PHYSICAL" Name="SduP2P" Nas="100" Nbs="100" Ncs="100" Padding="ON" RxFcPduRef="RxDiagP2P" TxPduRef="TxDiagP2P" ll_dl="64" />
<Sdu Comment="*" CommunicationType="PHYSICAL" Name="SduP2A" Nas="100" Nbs="100" Ncs="100" Padding="ON" RxFcPduRef="RxDiagP2A" TxPduRef="TxDiagP2A" ll_dl="64" />
</TxSduList>
</CanTp>
<PduR>
<General CanIfUsed="True" CanTpUsed="True" ComUsed="True" Comment="*" DcmUsed="True" DevelopmentErrorDetection="ON" J1939TpUsed="True" LinIfUsed="False" LinTpUsed="False" VersionInfoApi="OFF" ZeroCostIf="CanIf" ZeroCostOperationMode="OFF" ZeroCostTp="CanTp" />
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
<Source Comment="*" Module="Dcm" Name="DcmP2A" PduRef="TxDiagP2A">
<DestinationList Max="TBD">
<Destination Comment="*" Module="CanTp" Name="CanTpP2A" PduRef="TxDiagP2A" />
</DestinationList>
</Source>
<Source Comment="*" Module="CanTp" Name="CanTpP2A" PduRef="RxDiagP2A">
<DestinationList Max="TBD">
<Destination Comment="*" Module="Dcm" Name="DcmP2A" PduRef="RxDiagP2A" />
</DestinationList>
</Source>
<Source Comment="*" Module="Com" Name="ComMsgTime" PduRef="TxMsgTime">
<DestinationList Max="TBD">
<Destination Comment="*" Module="CanIf" Name="CanIfMsgTime" PduRef="TxMsgTime" />
</DestinationList>
</Source>
<Source Comment="*" Module="CanIf" Name="CanIfMsgAbs" PduRef="RxMsgAbsInfo">
<DestinationList Max="TBD">
<Destination Comment="*" Module="Com" Name="ComMsgAbs" PduRef="RxMsgAbsInfo" />
</DestinationList>
</Source>
<Source Comment="*" Module="SoAdTp" Name="SOAD_RX" PduRef="SOAD_RX">
<DestinationList Max="TBD">
<Destination Comment="*" Module="Dcm" Name="DCM_SOAD_RX" PduRef="SOAD_RX" />
</DestinationList>
</Source>
<Source Comment="*" Module="Dcm" Name="SOAD_TX" PduRef="SOAD_TX">
<DestinationList Max="TBD">
<Destination Comment="*" Module="SoAdTp" Name="DCM_SOAD_TX" PduRef="SOAD_TX" />
</DestinationList>
</Source>
<Source Comment="*" Module="Dcm" Name="DcmTxOnJ1939" PduRef="J1939TP_TX">
<DestinationList Max="TBD">
<Destination Comment="*" Module="J1939Tp" Name="DcmTxOnJ1939" PduRef="J1939TP_TX" />
</DestinationList>
</Source>
<Source Comment="*" Module="J1939Tp" Name="DcmRxOnJ1939" PduRef="J1939TP_RX">
<DestinationList Max="TBD">
<Destination Comment="*" Module="Dcm" Name="Destination1" PduRef="J1939TP_RX" />
</DestinationList>
</Source>
<Source Comment="*" Module="CanIf" Name="CanIfMsgLed" PduRef="RxMsgLedInfo">
<DestinationList Max="TBD">
<Destination Comment="*" Module="Com" Name="ComMsgLed" PduRef="RxMsgLedInfo" />
</DestinationList>
</Source>
</RoutineList>
</PduR>
<Com>
<General Comment="*" DevelopmentErrorDetection="ON" VersionInfoApi="OFF" />
<PduGroupList Max="TBD">
<PduGroup Comment="*" Name="PduGroup1" />
</PduGroupList>
<IPduList Max="TBD">
<IPdu Callout="NULL" Comment="*" DefaultValueForUnusedArea="0x5A" Direction="SEND" Name="MsgTime" NumberOfRepetions="0" PduGroupRef="PduGroup1" PduRef="TxMsgTime" RepetionsPeriodFactor="10" RxSignalProcessing="DEFERRED" TimeOffsetFactor="0" TimePeriodFactor="100" TxMinimumDelayFactor="1" TxMode="PERIODIC">
<GroupSignalList Max="TBD">
<GroupSignal Comment="*" Endianess="OPAQUE" FirstTimeoutFactor="TBD" Name="SystemTime" ReceivedNotification="NULL" Size="56" StartBit="0" TimeoutAction="REPLACE" TimeoutFactor="TBD" TimeoutNotification="NULL" TransferProperty="PENDING" UpdateBitPosition="0" UpdateBitUsed="False">
<SignalList Max="TBD">
<Signal Comment="*" Endianess="BIG_ENDIAN" InitialValue="2013" Name="year" Size="16" StartBit="7" Type="uint16" UpdateBitPosition="TBD" UpdateBitUsed="False" />
<Signal Comment="*" Endianess="BIG_ENDIAN" InitialValue="12" Name="month" Size="8" StartBit="23" Type="uint8" UpdateBitPosition="TBD" UpdateBitUsed="False" />
<Signal Comment="*" Endianess="BIG_ENDIAN" InitialValue="15" Name="day" Size="8" StartBit="31" Type="uint8" UpdateBitPosition="TBD" UpdateBitUsed="False" />
<Signal Comment="*" Endianess="BIG_ENDIAN" InitialValue="19" Name="hour" Size="8" StartBit="39" Type="uint8" UpdateBitPosition="TBD" UpdateBitUsed="False" />
<Signal Comment="*" Endianess="BIG_ENDIAN" InitialValue="49" Name="minute" Size="8" StartBit="47" Type="uint8" UpdateBitPosition="TBD" UpdateBitUsed="False" />
<Signal Comment="*" Endianess="BIG_ENDIAN" InitialValue="0" Name="second" Size="8" StartBit="55" Type="uint8" UpdateBitPosition="TBD" UpdateBitUsed="False" />
</SignalList>
</GroupSignal>
</GroupSignalList>
</IPdu>
<IPdu Callout="NULL" Comment="*" DefaultValueForUnusedArea="0x5A" Direction="RECEIVE" Name="AbsInfo" NumberOfRepetions="0" PduGroupRef="PduGroup1" PduRef="RxMsgAbsInfo" RepetionsPeriodFactor="10" RxSignalProcessing="DEFERRED" TimeOffsetFactor="0" TimePeriodFactor="10" TxMinimumDelayFactor="1" TxMode="PERIODIC">
<SignalList Max="TBD">
<Signal Comment="*" Endianess="BIG_ENDIAN" FirstTimeoutFactor="100" InitialValue="0" Name="VehicleSpeed" ReceivedNotification="NULL" Size="16" StartBit="7" TimeoutAction="NONE" TimeoutFactor="100" TimeoutNotification="NULL" TransferProperty="PENDING" Type="uint16" UpdateBitPosition="TBD" UpdateBitUsed="False" />
<Signal Comment="*" Endianess="BIG_ENDIAN" FirstTimeoutFactor="100" InitialValue="0" Name="TachoSpeed" ReceivedNotification="NULL" Size="16" StartBit="23" TimeoutAction="NONE" TimeoutFactor="100" TimeoutNotification="NULL" TransferProperty="PENDING" Type="uint16" UpdateBitPosition="TBD" UpdateBitUsed="False" />
<Signal Comment="*" Endianess="BIG_ENDIAN" FirstTimeoutFactor="500" InitialValue="0" Name="Led1Sts" ReceivedNotification="NULL" Size="2" StartBit="39" TimeoutAction="NONE" TimeoutFactor="500" TimeoutNotification="NULL" TransferProperty="PENDING" Type="uint8" UpdateBitPosition="TBD" UpdateBitUsed="False" />
<Signal Comment="*" Endianess="BIG_ENDIAN" FirstTimeoutFactor="500" InitialValue="0" Name="Led2Sts" ReceivedNotification="NULL" Size="2" StartBit="37" TimeoutAction="NONE" TimeoutFactor="500" TimeoutNotification="NULL" TransferProperty="PENDING" Type="uint8" UpdateBitPosition="TBD" UpdateBitUsed="False" />
<Signal Comment="*" Endianess="BIG_ENDIAN" FirstTimeoutFactor="500" InitialValue="0" Name="Led3Sts" ReceivedNotification="NULL" Size="2" StartBit="35" TimeoutAction="NONE" TimeoutFactor="500" TimeoutNotification="NULL" TransferProperty="PENDING" Type="uint8" UpdateBitPosition="TBD" UpdateBitUsed="False" />
<Signal Comment="*" Endianess="BIG_ENDIAN" FirstTimeoutFactor="500" InitialValue="0" Name="Led4Sts" ReceivedNotification="NULL" Size="2" StartBit="33" TimeoutAction="NONE" TimeoutFactor="200" TimeoutNotification="NULL" TransferProperty="PENDING" Type="uint8" UpdateBitPosition="TBD" UpdateBitUsed="False" />
</SignalList>
</IPdu>
<IPdu Callout="NULL" Comment="*" DefaultValueForUnusedArea="0x5A" Direction="RECEIVE" Name="LedInfoIpdu" NumberOfRepetions="0" PduGroupRef="PduGroup1" PduRef="RxMsgLedInfo" RepetionsPeriodFactor="10" RxSignalProcessing="DEFERRED" TimeOffsetFactor="0" TimePeriodFactor="10" TxMinimumDelayFactor="1" TxMode="PERIODIC">
<SignalList Max="TBD">
<Signal Comment="*" Endianess="BIG_ENDIAN" FirstTimeoutFactor="500" InitialValue="0" Name="LED2" ReceivedNotification="NULL" Size="8" StartBit="0" TimeoutAction="REPLACE" TimeoutFactor="200" TimeoutNotification="NULL" TransferProperty="PENDING" Type="uint8" UpdateBitPosition="TBD" UpdateBitUsed="False" />
</SignalList>
</IPdu>
</IPduList>
</Com>
<Dcm>
<General Comment="*" DevelopmentErrorDetection="ON" MaxPeriodDIDNumber="8" PeriodicDIDFastModeTime="50" PeriodicDIDMediumModeTime="100" PeriodicDIDSlowModeTime="200" VersionInfoApi="OFF" />
<BufferList Max="TBD">
<Buffer Comment="*" Name="Buffer1" Size="512" />
<Buffer Comment="*" Name="Buffer2" Size="512" />
<Buffer Comment="*" Name="Buffer3" Size="512" />
<Buffer Comment="*" Name="Buffer4" Size="512" />
<Buffer Comment="*" Name="Buffer5" Size="512" />
<Buffer Comment="*" Name="Buffer6" Size="512" />
<Buffer Comment="*" Name="Buffer7" Size="512" />
<Buffer Comment="*" Name="Buffer8" Size="512" />
</BufferList>
<SessionList Max="TBD">
<Session Comment="*" Identifier="1" Name="DS" P2ServerMaxTimeMs="5000" P2StartServerMaxTimeMs="500" />
<Session Comment="*" Identifier="2" Name="PRGS" P2ServerMaxTimeMs="5000" P2StartServerMaxTimeMs="500" />
<Session Comment="*" Identifier="3" Name="EXTDS" P2ServerMaxTimeMs="5000" P2StartServerMaxTimeMs="500" />
</SessionList>
<SecurityList Max="TBD">
<Security Comment="*" CompareKeyCallback="NULL" GetSeedCallback="NULL" Identifier="6" KeySize="4" Name="PRGS" SeedSize="4" />
<Security Comment="*" CompareKeyCallback="Diag_CompareKeyEXTDS" GetSeedCallback="Diag_GetSeedEXTDS" Identifier="1" KeySize="4" Name="EXTDS" SeedSize="4" />
<Security Comment="Level 0, is the default for each session when enterred" CompareKeyCallback="NULL" GetSeedCallback="NULL" Identifier="0" KeySize="4" Name="DS" SeedSize="4" />
</SecurityList>
<DIDControlRecordList Max="TBD" />
<DIDInfoList Max="TBD" />
<DIDList Max="TBD" />
<RoutineInfoList Max="TBD" />
<RoutineList Max="TBD" />
<MemoryList Max="TBD" />
<ProtocolList Max="TBD">
<Protocol Comment="*" Name="P2P" ProtocolID="UDS_ON_CAN" RxBufferRef="Buffer1" ServiceTableRef="ServiceTableP2P" TimingLimitRef="Timing1" TransmissionType="TYPE_1" TxBufferRef="Buffer2">
<ConnectionList Max="TBD">
<Connection Comment="*" Name="Connection1">
<RxChannelList Max="TBD">
<RxChannel AddressingType="PHYSICAL" Comment="*" Name="RxChannel1" PduRef="RxDiagP2P" />
</RxChannelList>
<TxChannel Comment="*" Name="TxChannel2" PduRef="TxDiagP2P" />
</Connection>
</ConnectionList>
</Protocol>
<Protocol Comment="*" Name="P2A" ProtocolID="UDS_ON_CAN" RxBufferRef="Buffer3" ServiceTableRef="ServiceTableP2A" TimingLimitRef="Timing1" TransmissionType="TYPE_1" TxBufferRef="Buffer4">
<ConnectionList Max="TBD">
<Connection Comment="*" Name="Connection1">
<RxChannelList Max="TBD">
<RxChannel AddressingType="PHYSICAL" Comment="*" Name="RxChannel1" PduRef="RxDiagP2A" />
</RxChannelList>
<TxChannel Comment="*" Name="TxChannel2" PduRef="TxDiagP2A" />
</Connection>
</ConnectionList>
</Protocol>
<Protocol Comment="*" Name="DoIP" ProtocolID="UDS_ON_DOIP" RxBufferRef="Buffer5" ServiceTableRef="ServiceTableP2P" TimingLimitRef="Timing1" TransmissionType="TYPE_1" TxBufferRef="Buffer6">
<ConnectionList Max="TBD">
<Connection Comment="*" Name="Connection1">
<RxChannelList Max="TBD">
<RxChannel AddressingType="PHYSICAL" Comment="*" Name="RxChannel1" PduRef="SOAD_RX" />
</RxChannelList>
<TxChannel Comment="*" Name="TxChannel2" PduRef="SOAD_TX" />
</Connection>
</ConnectionList>
</Protocol>
<Protocol Comment="*" Name="J1939" ProtocolID="UDS_ON_CAN" RxBufferRef="Buffer7" ServiceTableRef="ServiceTableP2P" TimingLimitRef="Timing1" TransmissionType="TYPE_1" TxBufferRef="Buffer8">
<ConnectionList Max="TBD">
<Connection Comment="*" Name="Connection1">
<RxChannelList Max="TBD">
<RxChannel AddressingType="PHYSICAL" Comment="*" Name="RxChannel1" PduRef="J1939TP_RX" />
</RxChannelList>
<TxChannel Comment="*" Name="TBD" PduRef="J1939TP_TX" />
</Connection>
</ConnectionList>
</Protocol>
</ProtocolList>
<RequestServiceList Max="TBD">
<RequestService Comment="*" Name="RequestService1" ProtocolIndicationCbk="Diag_ProtocolIndicationCbk" StartProtocolCbk="Diag_StartProtocolCbk" StopProtocolCbk="Diag_StopProtocolCbk" />
</RequestServiceList>
<ServiceTableList Max="TBD">
<ServiceTable Comment="*" Name="ServiceTableP2P">
<ServiceList Max="TBD">
<Service Comment="*" Name="DIAGNOSTIC_SESSION_CONTROL" SubFunctionSupported="True">
<SecurityList Max="TBD">
<Security Comment="*" Name="DS" />
<Security Comment="*" Name="PRGS" />
<Security Comment="*" Name="EXTDS" />
</SecurityList>
<SessionList Max="TBD">
<Session Comment="*" Name="DS" />
<Session Comment="*" Name="PRGS" />
<Session Comment="*" Name="EXTDS" />
</SessionList>
</Service>
<Service Comment="*" Name="SECURITY_ACCESS" SubFunctionSupported="True">
<SecurityList Max="TBD">
<Security Comment="*" Name="DS" />
<Security Comment="*" Name="PRGS" />
<Security Comment="*" Name="EXTDS" />
</SecurityList>
<SessionList Max="TBD">
<Session Comment="*" Name="EXTDS" />
</SessionList>
</Service>
<Service Comment="*" Name="TESTER_PRESENT" SubFunctionSupported="True">
<SecurityList Max="TBD">
<Security Comment="*" Name="DS" />
<Security Comment="*" Name="PRGS" />
<Security Comment="*" Name="EXTDS" />
</SecurityList>
<SessionList Max="TBD">
<Session Comment="*" Name="EXTDS" />
</SessionList>
</Service>
<Service Comment="*" Name="ECU_RESET" SubFunctionSupported="True">
<SecurityList Max="TBD">
<Security Comment="*" Name="EXTDS" />
</SecurityList>
<SessionList Max="TBD">
<Session Comment="*" Name="EXTDS" />
</SessionList>
</Service>
<Service Comment="*" Name="READ_DATA_BY_IDENTIFIER" SubFunctionSupported="False">
<SecurityList Max="TBD">
<Security Comment="*" Name="EXTDS" />
<Security Comment="*" Name="PRGS" />
</SecurityList>
<SessionList Max="TBD">
<Session Comment="*" Name="EXTDS" />
<Session Comment="*" Name="PRGS" />
</SessionList>
</Service>
<Service Comment="*" Name="READ_DTC_INFORMATION" SubFunctionSupported="True">
<SecurityList Max="TBD">
<Security Comment="*" Name="EXTDS" />
</SecurityList>
<SessionList Max="TBD">
<Session Comment="*" Name="EXTDS" />
</SessionList>
</Service>
<Service Comment="*" Name="CLEAR_DIAGNOSTIC_INFORMATION" SubFunctionSupported="False">
<SecurityList Max="TBD">
<Security Comment="*" Name="EXTDS" />
</SecurityList>
<SessionList Max="TBD">
<Session Comment="*" Name="EXTDS" />
</SessionList>
</Service>
</ServiceList>
</ServiceTable>
<ServiceTable Comment="*" Name="ServiceTableP2A">
<ServiceList Max="TBD">
<Service Comment="*" Name="DIAGNOSTIC_SESSION_CONTROL" SubFunctionSupported="False">
<SecurityList Max="TBD">
<Security Comment="*" Name="EXTDS" />
<Security Comment="*" Name="DS" />
</SecurityList>
<SessionList Max="TBD">
<Session Comment="*" Name="EXTDS" />
<Session Comment="*" Name="DS" />
</SessionList>
</Service>
<Service Comment="*" Name="TESTER_PRESENT" SubFunctionSupported="False">
<SecurityList Max="TBD">
<Security Comment="*" Name="EXTDS" />
<Security Comment="*" Name="DS" />
</SecurityList>
<SessionList Max="TBD">
<Session Comment="*" Name="DS" />
<Session Comment="*" Name="EXTDS" />
</SessionList>
</Service>
</ServiceList>
</ServiceTable>
</ServiceTableList>
<SessionControlList Max="TBD">
<SessionControl Comment="*" GetSessionChangePermissionCbk="Diag_GetSesChgPer" Name="SessionControl1" />
</SessionControlList>
<TimingList Max="TBD">
<Timing Comment="*" Name="Timing1" P2ServerMaxTimeMs="5000" P2ServerMinTimeMs="3000" S3ServerTimeMs="10000" />
</TimingList>
</Dcm>
<Fls>
<General Comment="*" DevelopmentErrorDetection="ON" FlashBaseAddress="0" MaxFastReadSize="512" MaxFastWriteSize="32" MaxNormalReadSize="32" MaxNormalWriteSize="8" VersionInfoApi="OFF" />
<SectorList Max="TBD">
<Sector Comment="*" Name="NVM" NumberOfSectors="2048" PageSize="8" SectorSize="512" StartAddress="0" />
</SectorList>
</Fls>
<Fee>
<General Comment="*" DevelopmentErrorDetection="ON" NvmJobEndNotification="NULL" NvmJobErrorNotification="NULL" PollingMode="ON" VersionInfoApi="OFF" VirtualPageSize="8" />
<BlockList Max="TBD">
<Block ArraySize="2" BlockSize="16" Comment="*" ImmediateData="False" IsArray="False" Name="Time" NumberOfWriteCycles="0xFFFFFFFF" />
<Block ArraySize="2" BlockSize="264" Comment="*" ImmediateData="False" IsArray="False" Name="Config" NumberOfWriteCycles="0xFFFFFFFF" />
<Block ArraySize="2" BlockSize="36" Comment="*" ImmediateData="False" IsArray="False" Name="Finger_Print" NumberOfWriteCycles="0xFFFFFFFF" />
<Block ArraySize="2" BlockSize="68" Comment="*" ImmediateData="False" IsArray="False" Name="DemHealing" NumberOfWriteCycles="0xFFFFFFFF" />
<Block ArraySize="5" BlockSize="28" Comment="ArraySize must be the size value of DemFreezeFrame" ImmediateData="False" IsArray="True" Name="Dem_DemFreezeFrame" NumberOfWriteCycles="0xFFFFFFFF" />
</BlockList>
</Fee>
<Ea>
<General Comment="*" DevelopmentErrorDetection="ON" NvmJobEndNotification="NULL" NvmJobErrorNotification="NULL" SetModeApi="ON" VersionInfoApi="OFF" VirtualPageSize="8" />
<BlockList Max="TBD">
<Block ArraySize="2" BlockSize="32" Comment="*" ImmediateData="False" IsArray="False" Name="EaTest1" NumberOfWriteCycles="0xFFFFFFFF" />
<Block ArraySize="2" BlockSize="32" Comment="*" ImmediateData="False" IsArray="False" Name="EaTest2" NumberOfWriteCycles="0xFFFFFFFF" />
</BlockList>
</Ea>
<NvM>
<General Comment="*" ConfigClass="CLASS_2" DevelopmentErrorDetection="ON" ImmediateJobQueueSize="8" MultiBlockCallback="NULL" PollingMode="OFF" RamBlockStatusApi="OFF" StandardJobQueueSize="8" VersionInfoApi="OFF" />
<BlockList Max="TBD">
<Block ArraySize="2" BlockCRCType="Crc16" BlockManagementType="NATIVE" BlockNumRef0="Time" BlockNumRef1="TBD" BlockUseCrc="True" Comment="*" InitBlockCallback="NULL" IsArray="False" Name="Time" NvramDeviceId="Fee" SelectBlockForReadall="True">
<DataList Max="TBD">
<Data ArraySize="2" Comment="*" DefaultValue="2015" IsArray="False" Name="Year" Type="uint16" />
<Data ArraySize="2" Comment="*" DefaultValue="12" IsArray="False" Name="Month" Type="uint8" />
<Data ArraySize="2" Comment="*" DefaultValue="3" IsArray="False" Name="Day" Type="uint8" />
<Data ArraySize="2" Comment="*" DefaultValue="21" IsArray="False" Name="Hour" Type="uint8" />
<Data ArraySize="2" Comment="*" DefaultValue="49" IsArray="False" Name="Minute" Type="uint8" />
<Data ArraySize="2" Comment="*" DefaultValue="7" IsArray="False" Name="Second" Type="uint8" />
</DataList>
</Block>
<Block ArraySize="2" BlockCRCType="Crc16" BlockManagementType="NATIVE" BlockNumRef0="Finger_Print" BlockNumRef1="TBD" BlockUseCrc="True" Comment="*" InitBlockCallback="NULL" IsArray="False" Name="FingerPrint" NvramDeviceId="Fee" SelectBlockForReadall="True">
<DataList Max="TBD">
<Data ArraySize="32" Comment="*" DefaultValue="{0,}" IsArray="True" Name="bytes" Type="uint8" />
</DataList>
</Block>
<Block ArraySize="2" BlockCRCType="Crc16" BlockManagementType="NATIVE" BlockNumRef0="Config" BlockNumRef1="TBD" BlockUseCrc="True" Comment="*" InitBlockCallback="NULL" IsArray="False" Name="Config" NvramDeviceId="Fee" SelectBlockForReadall="True">
<DataList Max="TBD">
<Data ArraySize="260" Comment="*" DefaultValue="{0,}" IsArray="True" Name="bytes" Type="uint8" />
</DataList>
</Block>
<Block ArraySize="2" BlockCRCType="Crc16" BlockManagementType="NATIVE" BlockNumRef0="TBD" BlockNumRef1="EaTest1" BlockUseCrc="True" Comment="*" InitBlockCallback="NULL" IsArray="False" Name="EaTest1" NvramDeviceId="Ea" SelectBlockForReadall="True">
<DataList Max="TBD">
<Data ArraySize="2" Comment="*" DefaultValue="0" IsArray="False" Name="Data0" Type="uint32" />
<Data ArraySize="2" Comment="*" DefaultValue="0" IsArray="False" Name="Data1" Type="uint32" />
<Data ArraySize="2" Comment="*" DefaultValue="0" IsArray="False" Name="Data2" Type="uint32" />
<Data ArraySize="2" Comment="*" DefaultValue="0" IsArray="False" Name="Data3" Type="uint32" />
</DataList>
</Block>
<Block ArraySize="2" BlockCRCType="Crc16" BlockManagementType="NATIVE" BlockNumRef0="TBD" BlockNumRef1="EaTest2" BlockUseCrc="True" Comment="*" InitBlockCallback="NULL" IsArray="False" Name="EaTest2" NvramDeviceId="Ea" SelectBlockForReadall="True">
<DataList Max="TBD">
<Data ArraySize="2" Comment="*" DefaultValue="1" IsArray="False" Name="Data1" Type="uint32" />
<Data ArraySize="2" Comment="*" DefaultValue="2" IsArray="False" Name="Data2" Type="uint32" />
<Data ArraySize="2" Comment="*" DefaultValue="3" IsArray="False" Name="Data3" Type="uint32" />
<Data ArraySize="2" Comment="*" DefaultValue="4" IsArray="False" Name="Data4" Type="uint32" />
</DataList>
</Block>
<Block ArraySize="2" BlockCRCType="Crc16" BlockManagementType="NATIVE" BlockNumRef0="DemHealing" BlockNumRef1="TBD" BlockUseCrc="True" Comment="*" InitBlockCallback="NULL" IsArray="False" Name="DemHealing" NvramDeviceId="Fee" SelectBlockForReadall="True">
<DataList Max="TBD">
<Struct ArraySize="8" Comment="*" IsArray="True" Name="HealingRec">
<DataList Max="TBD">
<Data ArraySize="2" Comment="*" DefaultValue="0" IsArray="False" Name="eventId" Type="uint16" />
<Data ArraySize="2" Comment="*" DefaultValue="0" IsArray="False" Name="agingCounter" Type="uint8" />
<Data ArraySize="2" Comment="*" DefaultValue="0" IsArray="False" Name="checksum" Type="uint16" />
</DataList>
</Struct>
</DataList>
</Block>
<Block ArraySize="5" BlockCRCType="Crc16" BlockManagementType="NATIVE" BlockNumRef0="Dem_DemFreezeFrame" BlockNumRef1="TBD" BlockUseCrc="True" Comment="*" InitBlockCallback="NULL" IsArray="True" Name="DemFreezeFrame" NvramDeviceId="Fee" SelectBlockForReadall="True">
<DataList Max="TBD">
<Struct ArraySize="2" Comment="*" IsArray="False" Name="FreezeFrameRec">
<DataList Max="TBD">
<Data ArraySize="2" Comment="*" DefaultValue="0" IsArray="False" Name="eventId" Type="uint16" />
<Data ArraySize="2" Comment="*" DefaultValue="0" IsArray="False" Name="kind" Type="uint8" />
<Data ArraySize="2" Comment="*" DefaultValue="0" IsArray="False" Name="occurrence" Type="uint16" />
<Data ArraySize="2" Comment="*" DefaultValue="0" IsArray="False" Name="dataSize" Type="uint16" />
<Data ArraySize="2" Comment="*" DefaultValue="0" IsArray="False" Name="recordNumber" Type="uint8" />
<Data ArraySize="2" Comment="*" DefaultValue="0" IsArray="False" Name="timeStamp" Type="uint32" />
<Data ArraySize="10" Comment="DEM_MAX_SIZE_FF_DATA" DefaultValue="0" IsArray="True" Name="data" Type="uint8" />
<Data ArraySize="2" Comment="*" DefaultValue="0" IsArray="False" Name="checksum" Type="uint16" />
</DataList>
</Struct>
</DataList>
</Block>
</BlockList>
</NvM>
<Xcp>
<General Comment="*" DevelopmentErrorDetection="ON" VersionInfoApi="ON" XcpCounterRef="TBD" XcpDaqConfigType="DAQ_DYNAMIC" XcpDaqCount="8" XcpFlashProgrammingEnabled="True" XcpIdentificationFieldType="ABSOLUTE" XcpMainFunctionPeriod="10" XcpMaxCto="8" XcpMaxDto="8" XcpMaxEventChannel="8" XcpMaxRxTxQueue="8" XcpMinDaq="0" XcpNvRamBlockIdRef="TBD" XcpOdtCount="8" XcpOdtEntriesCount="8" XcpOdtEntrySizeDaq="0" XcpOdtEntrySizeStim="0" XcpPrescalerSupported="True" XcpProtocal="CAN" XcpSuppressTxSupport="True" XcpTimestampTicks="1" XcpTimestampType="FOUR_BYTE" XcpTimestampUnit="1ms" />
<XcpStaticDaqList Max="TBD">
<XcpDaq Comment="*" Name="XcpDaq1" XcpMaxOdt="8" XcpOdtCount="8">
<XcpOdtList Max="TBD">
<XcpOdt Comment="*" Name="XcpOdt1">
<XcpOdtEntryList Max="TBD">
<XcpEntry Address="&amp;xcpSimMTAMemory[0]" Comment="*" Extension="MEMORY" Length="1" Name="XcpEntry1" />
<XcpEntry Address="&amp;xcpSimMTAMemory[1]" Comment="*" Extension="MEMORY" Length="2" Name="XcpEntry2" />
<XcpEntry Address="&amp;xcpSimMTAMemory[3]" Comment="*" Extension="MEMORY" Length="3" Name="XcpEntry3" />
</XcpOdtEntryList>
</XcpOdt>
<XcpOdt Comment="*" Name="XcpOdt2">
<XcpOdtEntryList Max="TBD">
<XcpEntry Address="&amp;xcpSimMTAMemory[6]" Comment="*" Extension="MEMORY" Length="1" Name="XcpEntry1" />
<XcpEntry Address="&amp;xcpSimMTAMemory[7]" Comment="*" Extension="MEMORY" Length="2" Name="XcpEntry2" />
<XcpEntry Address="&amp;xcpSimMTAMemory[9]" Comment="*" Extension="MEMORY" Length="3" Name="XcpEntry3" />
</XcpOdtEntryList>
</XcpOdt>
</XcpOdtList>
</XcpDaq>
</XcpStaticDaqList>
<XcpEventChannelList Max="TBD">
<XcpEventChannel Comment="*" DAQListRefSize="8" Name="1000ms">
<XcpStaticDaqList Max="TBD">
<XcpDaq Comment="*" Name="XcpDaq1" />
</XcpStaticDaqList>
</XcpEventChannel>
</XcpEventChannelList>
</Xcp>
<Rte>
<DataTypeList Max="TBD">
<DataType Comment="*" Maximum="TBD" Minimum="TBD" Name="InactiveActive_T" Type="Integer" ValueTable="InactiveActive_Inactive, InactiveActive_Active, InactiveActive_Error, InactiveActive_NotAvailable" />
<DataType Comment="*" Maximum="TBD" Minimum="TBD" Name="OnOff_T" Type="Integer" ValueTable="OnOff_Off, OnOff_On, OnOff_1Hz, OnOff_2Hz, OnOff_3Hz" />
</DataTypeList>
<ConstantList Max="TBD">
<Constant Comment="*" Name="C_TELLTALE_OFF_IV" Type="OnOff_T" Value="0" />
</ConstantList>
<SwcList Max="TBD">
<Swc Comment="*" Name="Telltale" Runnable="Telltale_run">
<PortList Max="TBD">
<Port Comment="*" DataTypeRef="OnOff_T" InitValueRef="C_TELLTALE_OFF_IV" Name="TelltaleTPMSStatus" Type="Provide" />
<Port Comment="*" DataTypeRef="OnOff_T" InitValueRef="C_TELLTALE_OFF_IV" Name="TelltaleAutoCruiseStatus" Type="Provide" />
<Port Comment="*" DataTypeRef="OnOff_T" InitValueRef="C_TELLTALE_OFF_IV" Name="TelltaleHighBeamStatus" Type="Provide" />
</PortList>
</Swc>
</SwcList>
</Rte>
<Dem>
<General Comment="DEM_MAX_NUMBER_FF_DATA_PRI_MEM must be the size value of DemFreezeFrame" DEM_CLEAR_ALL_EVENTS="OFF" DEM_DTC_STATUS_AVAILABILITY_MASK="0xFF" DEM_MAX_NUMBER_FF_DATA_PRI_MEM="5" DEM_OBD_SUPPORT="OFF" DEM_PTO_SUPPORT="OFF" DEM_TYPE_OF_DTC_SUPPORTED="0x01" DEM_USE_NVM="ON" DevelopmentErrorDetection="ON" NvMFreezeFrameBlock="DemFreezeFrame" NvMHealingBlock="DemHealing" VersionInfoApi="ON" />
<ExtendedDataRecordClassList Max="TBD">
<ExtendedDataRecordClass CallbackGetExtDataRecord="USED" Comment="*" DataSize="4" InternalDataElement="NO_ELEMENT" Name="ExtendedDataRecordClass_Odometer" RecordNumber="1" UpdateRule="VOLATILE" />
</ExtendedDataRecordClassList>
<DTCClassList Max="TBD">
<DTCClass Comment="*" DTC="0x180001" DTCFunctionalUnit="0" DTCKind="ALL_DTCS" Name="DTCAirbag" />
</DTCClassList>
<FFIdClassList Max="TBD">
<FFIdClass Comment="*" DidConditionCheckReadFnc="USED" DidIdentifier="0xFFFF" DidReadDataLengthFnc="USED" DidReadFnc="USED" Name="AirbagFFIdClass" PidIndentifier="1" PidOrDidSize="1" PidReadFnc="USED" />
</FFIdClassList>
<FreezeFrameClassList Max="TBD">
<FreezeFrameClass Comment="*" FFKind="NON_OBD" FFRecordNumber="1" FFStorageCondition="FAILED" Name="AirbagFreezeFrameClass">
<FFIdClassRefList Max="TBD">
<FFIdClassRef Comment="*" Name="AirbagFFIdClass" />
</FFIdClassRefList>
</FreezeFrameClass>
</FreezeFrameClassList>
<EventClassList Max="TBD">
<EventClass Comment="*" ConfirmationCycleCounterThreshold="8" ConsiderPtoStatus="False" EventPriority="1" FFPrestorageSupported="False" HealingAllowed="False" HealingCycleCounter="8" HealingCycleRef="IGNITION" Name="BSWEventClass" OperationCycleRef="IGNITION" />
<EventClass Comment="*" ConfirmationCycleCounterThreshold="8" ConsiderPtoStatus="False" EventPriority="1" FFPrestorageSupported="False" HealingAllowed="False" HealingCycleCounter="8" HealingCycleRef="IGNITION" Name="SWCEventClass" OperationCycleRef="IGNITION" />
</EventClassList>
<EventParameterList Max="TBD">
<EventParameter CallbackInitMForEFnc="NULL" Comment="*" DTCClassRef="NULL" EventClassRef="BSWEventClass" EventKind="BSW" Name="EEP_E_WRITE_FAILED" />
<EventParameter CallbackInitMForEFnc="NULL" Comment="*" DTCClassRef="NULL" EventClassRef="BSWEventClass" EventKind="BSW" Name="EEP_E_READ_FAILED" />
<EventParameter CallbackInitMForEFnc="NULL" Comment="*" DTCClassRef="NULL" EventClassRef="BSWEventClass" EventKind="BSW" Name="FLS_E_ERASE_FAILED" />
<EventParameter CallbackInitMForEFnc="NULL" Comment="*" DTCClassRef="NULL" EventClassRef="BSWEventClass" EventKind="BSW" Name="FLS_E_WRITE_FAILED" />
<EventParameter CallbackInitMForEFnc="NULL" Comment="*" DTCClassRef="NULL" EventClassRef="BSWEventClass" EventKind="BSW" Name="FLS_E_READ_FAILED" />
<EventParameter CallbackInitMForEFnc="NULL" Comment="*" DTCClassRef="NULL" EventClassRef="BSWEventClass" EventKind="BSW" Name="CANNM_E_NETWORK_TIMEOUT" />
<EventParameter CallbackInitMForEFnc="NULL" Comment="*" DTCClassRef="NULL" EventClassRef="BSWEventClass" EventKind="BSW" Name="PDUR_E_PDU_INSTANCE_LOST" />
<EventParameter CallbackInitMForEFnc="NULL" Comment="*" DTCClassRef="NULL" EventClassRef="BSWEventClass" EventKind="BSW" Name="NVM_E_INTEGRITY_FAILED" />
<EventParameter CallbackInitMForEFnc="NULL" Comment="*" DTCClassRef="NULL" EventClassRef="BSWEventClass" EventKind="BSW" Name="NVM_E_REQ_FAILED" />
<EventParameter CallbackInitMForEFnc="NULL" Comment="*" DTCClassRef="NULL" EventClassRef="BSWEventClass" EventKind="BSW" Name="ECUM_E_ALL_RUN_REQUESTS_KILLED" />
<EventParameter CallbackInitMForEFnc="NULL" Comment="*" DTCClassRef="NULL" EventClassRef="BSWEventClass" EventKind="BSW" Name="ECUM_E_RAM_CHECK_FAILED" />
<EventParameter CallbackInitMForEFnc="USED" Comment="*" DTCClassRef="DTCAirbag" EventClassRef="SWCEventClass" EventKind="SWC" Name="AIRBAG_FAILED">
<FreezeFrameClassRefList Max="TBD">
<FreezeFrameClassRef Comment="*" Name="AirbagFreezeFrameClass" />
</FreezeFrameClassRefList>
<ExtendedDataClassRefList>
<ExtendedDataClassRef Comment="*" Name="ExtendedDataRecordClass_Odometer" />
</ExtendedDataClassRefList>
</EventParameter>
</EventParameterList>
</Dem>
<J1939Tp>
<General Comment="*" DevelopmentErrorDetection="ON" PACKETS_PER_BLOCK="8" TX_CONF_TIMEOUT="1000" VersionInfoApi="ON" />
<ChannelList Max="TBD">
<Channel CmNPdu="TX_J1939TP_CmNPdu" Comment="*" Direction="RX" DtNPdu="TX_J1939TP_DtNPdu" FcNPdu="TX_J1939TP_FcNPdu" Name="J1939TP_RX_CHL" Protocol="CMDT" />
<Channel CmNPdu="TX_J1939TP_CmNPdu" Comment="*" Direction="TX" DtNPdu="TX_J1939TP_DtNPdu" FcNPdu="TX_J1939TP_FcNPdu" Name="J1939TP_TX_CHL" Protocol="CMDT" />
</ChannelList>
<ParameterGroupList Max="TBD">
<ParameterGroup Channel="J1939TP_RX_CHL" Comment="*" DirectNPdu="TX_J1939TP_DirectNPdu" DynLength="True" NSdu="J1939TP_RX" Name="PG_RX" PgnType="0" />
<ParameterGroup Channel="J1939TP_TX_CHL" Comment="*" DirectNPdu="TX_J1939TP_DirectNPdu" DynLength="True" NSdu="J1939TP_TX" Name="PG_TX" PgnType="1" />
</ParameterGroupList>
<PduInfoList Max="TBD">
<PduInfo Channel="J1939TP_TX_CHL" Comment="*" Name="RX_J1939TP_REVERSE_CM" PacketType="REVERSE_CM" ParameterGroup="PG_TX" />
<PduInfo Channel="J1939TP_RX_CHL" Comment="*" Name="RX_J1939TP_CM" PacketType="CM" ParameterGroup="PG_RX" />
<PduInfo Channel="J1939TP_RX_CHL" Comment="*" Name="RX_J1939TP_DT" PacketType="DT" ParameterGroup="PG_RX" />
<PduInfo Channel="J1939TP_RX_CHL" Comment="*" Name="RX_J1939TP_DIRECT" PacketType="DIRECT" ParameterGroup="PG_RX" />
<PduInfo Channel="J1939TP_TX_CHL" Comment="*" Name="TX_J1939TP_CmNPdu" PacketType="CM" ParameterGroup="PG_TX" />
<PduInfo Channel="J1939TP_TX_CHL" Comment="*" Name="TX_J1939TP_DtNPdu" PacketType="DT" ParameterGroup="PG_TX" />
<PduInfo Channel="J1939TP_RX_CHL" Comment="*" Name="TX_J1939TP_FcNPdu" PacketType="REVERSE_CM" ParameterGroup="PG_RX" />
<PduInfo Channel="J1939TP_TX_CHL" Comment="*" Name="TX_J1939TP_DirectNPdu" PacketType="DIRECT" ParameterGroup="PG_TX" />
</PduInfoList>
</J1939Tp>
</AUTOSAR>
