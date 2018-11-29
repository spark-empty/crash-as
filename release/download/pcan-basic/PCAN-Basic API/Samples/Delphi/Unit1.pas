unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ComCtrls, PCANBasic, ExtCtrls, SyncObjs;

type
    MessageStatus = class(TObject)
        private
            m_Msg : TPCANMsgFD;
            m_TimeStamp : TPCANTimestampFD;
            m_oldTimeStamp : TPCANTimestampFD;
            m_iIndex : integer;
            m_Count : integer;
            m_bShowPeriod : boolean;
            m_bWasChanged : boolean;

            function GetMsgTypeString : AnsiString;
            function GetIdString : AnsiString;
            function GetDataString : AnsiString;
            function GetTimeString : AnsiString;

            procedure SetShowingPeriod(value : boolean);

        public
            constructor Create(canMsg : TPCANMsgFD; canTimestamp : TPCANTimestampFD; listIndex : Integer);
            procedure Update(canMsg : TPCANMsgFD; canTimestamp : TPCANTimestampFD);

            property CANMsg : TPCANMsgFD read  m_Msg;
            property Timestamp : TPCANTimestampFD read m_TimeStamp;
            property Position : Integer read m_iIndex;
            property TypeString : AnsiString read GetMsgTypeString;
            property IdString : AnsiString read GetIdString;
            property DataString : AnsiString read GetDataString;
            property Count : Integer read m_Count;
            property ShowingPeriod : boolean read m_bShowPeriod write SetShowingPeriod;
            property MarkedAsUpdated : boolean read m_bWasChanged write m_bWasChanged;
            property TimeString : AnsiString read GetTimeString;
    end;

  TForm1 = class(TForm)
    GroupBox1: TGroupBox;
    Label1: TLabel;
    laBaudrate: TLabel;
    laHwType: TLabel;
    laIOPort: TLabel;
    laInterrupt: TLabel;
    cbbChannel: TComboBox;
    btnHwRefresh: TButton;
    cbbBaudrates: TComboBox;
    cbbHwType: TComboBox;
    cbbIO: TComboBox;
    cbbInterrupt: TComboBox;
    btnInit: TButton;
    btnRelease: TButton;
    GroupBox2: TGroupBox;
    Label6: TLabel;
    Label7: TLabel;
    chbFilterExt: TCheckBox;
    rdbFilterOpen: TRadioButton;
    rdbFilterClose: TRadioButton;
    rdbFilterCustom: TRadioButton;
    txtIdFrom: TEdit;
    txtIdTo: TEdit;
    btnFilterApply: TButton;
    btnFilterQuery: TButton;
    GroupBox3: TGroupBox;
    Label8: TLabel;
    Label9: TLabel;
    laDeviceOrDelay: TLabel;
    btnParameterSet: TButton;
    btnParameterGet: TButton;
    cbbParameter: TComboBox;
    rdbParamActive: TRadioButton;
    rdbParamInactive: TRadioButton;
    txtDeviceIdOrDelay: TEdit;
    GroupBox4: TGroupBox;
    rdbTimer: TRadioButton;
    rdbEvent: TRadioButton;
    rdbManual: TRadioButton;
    chbShowPeriod: TCheckBox;
    btnRead: TButton;
    btnMsgClear: TButton;
    GroupBox6: TGroupBox;
    lbxInfo: TListBox;
    btnGetVersions: TButton;
    btnInfoClear: TButton;
    btnReset: TButton;
    btnStatus: TButton;
    tmrRead: TTimer;
    tmrDisplay: TTimer;
    laBitrate: TLabel;
    txtBitrate: TMemo;
    chbCanFD: TCheckBox;
    GroupBox5: TGroupBox;
    Label11: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    laLength: TLabel;
    txtID: TEdit;
    chbExtended: TCheckBox;
    txtLength: TEdit;
    nudLength: TUpDown;
    chbRemote: TCheckBox;
    txtData0: TEdit;
    txtData1: TEdit;
    txtData2: TEdit;
    txtData3: TEdit;
    txtData4: TEdit;
    txtData5: TEdit;
    txtData6: TEdit;
    txtData7: TEdit;
    btnWrite: TButton;
    txtData8: TEdit;
    txtData9: TEdit;
    txtData10: TEdit;
    txtData12: TEdit;
    txtData11: TEdit;
    txtData13: TEdit;
    txtData14: TEdit;
    txtData15: TEdit;
    txtData24: TEdit;
    txtData25: TEdit;
    txtData26: TEdit;
    txtData28: TEdit;
    txtData27: TEdit;
    txtData29: TEdit;
    txtData30: TEdit;
    txtData31: TEdit;
    txtData23: TEdit;
    txtData22: TEdit;
    txtData21: TEdit;
    txtData20: TEdit;
    txtData19: TEdit;
    txtData18: TEdit;
    txtData17: TEdit;
    txtData16: TEdit;
    txtData40: TEdit;
    txtData41: TEdit;
    txtData42: TEdit;
    txtData44: TEdit;
    txtData43: TEdit;
    txtData45: TEdit;
    txtData46: TEdit;
    txtData47: TEdit;
    txtData39: TEdit;
    txtData38: TEdit;
    txtData37: TEdit;
    txtData36: TEdit;
    txtData35: TEdit;
    txtData34: TEdit;
    txtData33: TEdit;
    txtData32: TEdit;
    txtData56: TEdit;
    txtData57: TEdit;
    txtData58: TEdit;
    txtData60: TEdit;
    txtData59: TEdit;
    txtData61: TEdit;
    txtData62: TEdit;
    txtData63: TEdit;
    txtData55: TEdit;
    txtData54: TEdit;
    txtData53: TEdit;
    txtData52: TEdit;
    txtData51: TEdit;
    txtData50: TEdit;
    txtData49: TEdit;
    txtData48: TEdit;
    chbFD: TCheckBox;
    chbBRS: TCheckBox;
    lstMessages: TListView;
    procedure FormCreate(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure cbbChannelChange(Sender: TObject);
    procedure cbbBaudratesChange(Sender: TObject);
    procedure cbbHwTypeChange(Sender: TObject);
    procedure cbbParameterChange(Sender: TObject);
    procedure btnHwRefreshClick(Sender: TObject);
    procedure btnInitClick(Sender: TObject);
    procedure btnReleaseClick(Sender: TObject);
    procedure btnFilterApplyClick(Sender: TObject);
    procedure btnFilterQueryClick(Sender: TObject);
    procedure btnParameterSetClick(Sender: TObject);
    procedure btnParameterGetClick(Sender: TObject);
    procedure btnReadClick(Sender: TObject);
    procedure btnMsgClearClick(Sender: TObject);
    procedure btnWriteClick(Sender: TObject);
    procedure btnGetVersionsClick(Sender: TObject);
    procedure btnInfoClearClick(Sender: TObject);
    procedure btnStatusClick(Sender: TObject);
    procedure btnResetClick(Sender: TObject);
    procedure chbFilterExtClick(Sender: TObject);
    procedure chbExtendedClick(Sender: TObject);
    procedure tmrReadTimer(Sender: TObject);
    procedure rdbTimerClick(Sender: TObject);
    procedure nudLengthClick(Sender: TObject; Button: TUDBtnType);
    procedure txtIDExit(Sender: TObject);
    procedure txtIdFromExit(Sender: TObject);
    procedure txtIdFromKeyPress(Sender: TObject; var Key: Char);
    procedure txtDeviceIdOrDelayKeyPress(Sender: TObject; var Key: Char);
    procedure txtDeviceIdOrDelayExit(Sender: TObject);
    procedure txtData0Exit(Sender: TObject);
    procedure chbShowPeriodClick(Sender: TObject);
    procedure tmrDisplayTimer(Sender: TObject);
    procedure chbCanFDClick(Sender: TObject);
    procedure chbFDClick(Sender: TObject);
    procedure chbRemoteClick(Sender: TObject);

  private
    //
    m_PcanHandle : TPCANHandle;
    m_IsFD : Boolean;    
    m_Baudrate : TPCANBaudrate;
    m_HwType : TPCANType;
    m_ActiveReadingMode : Integer;
    m_LastMsgsList : TList;
    m_hEvent : THandle;
    m_hThread : THandle;
    m_objpCS: TCriticalSection;

    m_HandlesArray : array[0..58] of TPCANHandle;
    procedure InitializeProtection();
    procedure FinalizeProtection();

  public
    procedure InitializeControls();
    procedure FillComboBoxData();
    procedure ConfigureLogFile();
    procedure ConfigureTraceFile();
    procedure SetConnectionStatus(bConnected : boolean);
    procedure IncludeTextMessage(strMsg: AnsiString);

    procedure InsertMsgEntry(NewMsg : TPCANMsgFD; timeStamp: TPCANTimestampFD);
    procedure DisplayMessages();
    function WriteFrame() : TPCANStatus;
    function WriteFrameFD() : TPCANStatus;    
    function ReadMessageFD() : TPCANStatus;
    function ReadMessage() : TPCANStatus;
    procedure ReadMessages();
    procedure ProcessMessage(theMsg : TPCANMsg; itsTimeStamp : TPCANTimestamp); overload;
    procedure ProcessMessage(theMsg : TPCANMsgFD; itsTimeStamp : TPCANTimestampFD); overload;
    procedure ReadingModeChanged();

    function CANReadThreadFunc() : LongWord;

    procedure EnableDisableDataFields(length: integer);
    function FormatChannelName(handle : TPCANHandle; isFD: boolean) : AnsiString; overload;
    function FormatChannelName(handle : TPCANHandle) : AnsiString; overload;
    function GetTPCANHandleName(handle : TPCANHandle) : AnsiString;
    function GetFormatedError(error: TPCANStatus) : AnsiString;
    function GetFilterStatus(var status: Integer) : boolean;

  end;

var
  Form1: TForm1;

implementation

function GetLengthFromDLC(dlc: integer; isSTD: boolean) : integer;
begin
    if (dlc <= 8) then
        Result := dlc
    else
        if (isSTD) then
            Result := 8
        else
            case dlc of
            9: Result := 12;
            10: Result := 16;
            11: Result := 20;
            12: Result := 24;
            13: Result := 32;
            14: Result := 48;
            15: Result := 64;
            else
            Result := DLC;
            end;

end;

{ MessageStatus }

constructor MessageStatus.Create(canMsg: TPCANMsgFD; canTimestamp: TPCANTimestampFD;
  listIndex: Integer);
begin
    m_Msg := canMsg;
    m_TimeStamp := canTimestamp;
    m_oldTimeStamp := canTimestamp;
    m_iIndex := listIndex;
    m_Count := 1;
    m_bShowPeriod := true;
    m_bWasChanged := false;
end;

procedure MessageStatus.Update(canMsg: TPCANMsgFD; canTimestamp: TPCANTimestampFD);
begin
    m_Msg := canMsg;
    m_oldTimeStamp := m_TimeStamp;
    m_TimeStamp := canTimestamp;
    m_bWasChanged := true;
    m_Count := m_Count + 1;
end;

function MessageStatus.GetDataString: AnsiString;
var
    strTemp : AnsiString;
    I : integer;
begin
    strTemp := '';

    // We format the data of the message. Each data is one
    // byte of Hexadecimal data
    //
    if((Byte(m_Msg.MSGTYPE) AND Byte(PCAN_MESSAGE_RTR)) = Byte(PCAN_MESSAGE_RTR))then
        Result := 'Remote Request'
    else
    begin

        for I:=0 To (GetLengthFromDLC(m_Msg.DLC, (Byte(m_Msg.MSGTYPE) AND Byte(PCAN_MESSAGE_FD)) = 0)-1) do
            strTemp := (strTemp + IntToHex(m_Msg.DATA[I],2) + ' ');
        Result := strTemp;
    end;
end;

function MessageStatus.GetIdString: AnsiString;
begin
    // We format the ID of the message and show it
    //
    if((Byte(m_Msg.MSGTYPE) AND Byte(PCAN_MESSAGE_EXTENDED)) <> 0)then
        Result := IntToHex(m_Msg.ID,8) + 'h'
    else
        Result := IntToHex(m_Msg.ID,3) + 'h';
end;

function MessageStatus.GetMsgTypeString: AnsiString;
var
    strTemp : AnsiString;
begin

    strTemp := '';

    // Add the new ListView Item with the Type of the message
    //
    if((Byte(m_Msg.MSGTYPE) AND Byte(PCAN_MESSAGE_STATUS)) <> 0)then
        strTemp := 'STATUS'
    else
        if((Byte(m_Msg.MSGTYPE) AND Byte(PCAN_MESSAGE_ERRFRAME)) <> 0)then
            strTemp := 'ERROR'
        else
        begin
            if((Byte(m_Msg.MSGTYPE) AND Byte(PCAN_MESSAGE_EXTENDED)) <> 0)then
                strTemp := 'EXT'
            else
                strTemp := 'STD';

            if((Byte(m_Msg.MSGTYPE) AND Byte(PCAN_MESSAGE_RTR)) = Byte(PCAN_MESSAGE_RTR))then
                strTemp := (strTemp + '/RTR')
            else
            begin
                if(Byte(m_Msg.MSGTYPE) > Byte(PCAN_MESSAGE_EXTENDED)) then
                begin
                     strTemp := strTemp + (' [ ');
                     if((Byte(m_Msg.MSGTYPE) AND Byte(PCAN_MESSAGE_FD)) = Byte(PCAN_MESSAGE_FD))then
                         strTemp := strTemp + (' FD');
                     if((Byte(m_Msg.MSGTYPE) AND Byte(PCAN_MESSAGE_BRS)) = Byte(PCAN_MESSAGE_BRS))then
                         strTemp := strTemp + (' BRS');
                     if((Byte(m_Msg.MSGTYPE) AND Byte(PCAN_MESSAGE_ESI)) = Byte(PCAN_MESSAGE_ESI))then
                         strTemp := strTemp + (' ESI');
                     strTemp := strTemp + (' ]');
                end;
            end;
        end;

    result := strTemp;
end;

function MessageStatus.GetTimeString: AnsiString;
var
    fTime : double;
begin
    fTime := (m_TimeStamp / 1000.0);
    if m_bShowPeriod then
        fTime := fTime - (m_oldTimeStamp / 1000.0);
    Result := Format('%.1f',[fTime]);
end;

procedure MessageStatus.SetShowingPeriod(value: boolean);
begin
    if m_bShowPeriod xor value then
    begin
        m_bShowPeriod := value;
        m_bWasChanged := true;
    end;
end;

{$R *.dfm}

procedure TForm1.FormCreate(Sender: TObject);
begin
	// Initialize all
	//
	InitializeControls();
end;

procedure TForm1.FormClose(Sender: TObject; var Action: TCloseAction);
begin
	// Release Hardware if needed
	//
	if(btnRelease.Enabled) then
		btnRelease.Click;

	// Close the event
    //
	CloseHandle(m_hEvent);

    try
        m_objpCS.Enter;

        while(m_LastMsgsList.Count > 0) do
        begin
            MessageStatus(m_LastMsgsList.First()).Free;
            m_LastMsgsList.Delete(0);
        end;
        m_LastMsgsList.Free;
    finally
        m_objpCS.Leave;
    end;

    FinalizeProtection();
end;

procedure TForm1.InitializeControls;
begin
	// Initialize the Critical Section
	//
    InitializeProtection();

	// Creates an array with all possible PCAN-Channels
	//
	m_HandlesArray[0] := TPCANBAsic.PCAN_ISABUS1;
	m_HandlesArray[1] := TPCANBAsic.PCAN_ISABUS2;
	m_HandlesArray[2] := TPCANBAsic.PCAN_ISABUS3;
	m_HandlesArray[3] := TPCANBAsic.PCAN_ISABUS4;
	m_HandlesArray[4] := TPCANBAsic.PCAN_ISABUS5;
	m_HandlesArray[5] := TPCANBAsic.PCAN_ISABUS6;
	m_HandlesArray[6] := TPCANBAsic.PCAN_ISABUS7;
	m_HandlesArray[7] := TPCANBAsic.PCAN_ISABUS8;
	m_HandlesArray[8] := TPCANBAsic.PCAN_DNGBUS1;
	m_HandlesArray[9] := TPCANBAsic.PCAN_PCIBUS1;
	m_HandlesArray[10] := TPCANBAsic.PCAN_PCIBUS2;
	m_HandlesArray[11] := TPCANBAsic.PCAN_PCIBUS3;
	m_HandlesArray[12] := TPCANBAsic.PCAN_PCIBUS4;
	m_HandlesArray[13] := TPCANBAsic.PCAN_PCIBUS5;
	m_HandlesArray[14] := TPCANBAsic.PCAN_PCIBUS6;
	m_HandlesArray[15] := TPCANBAsic.PCAN_PCIBUS7;
	m_HandlesArray[16] := TPCANBAsic.PCAN_PCIBUS8;
	m_HandlesArray[17] := TPCANBAsic.PCAN_PCIBUS9;
	m_HandlesArray[18] := TPCANBAsic.PCAN_PCIBUS10;
	m_HandlesArray[19] := TPCANBAsic.PCAN_PCIBUS11;
	m_HandlesArray[20] := TPCANBAsic.PCAN_PCIBUS12;
	m_HandlesArray[21] := TPCANBAsic.PCAN_PCIBUS13;
	m_HandlesArray[22] := TPCANBAsic.PCAN_PCIBUS14;
	m_HandlesArray[23] := TPCANBAsic.PCAN_PCIBUS15;
	m_HandlesArray[24] := TPCANBAsic.PCAN_PCIBUS16;
	m_HandlesArray[25] := TPCANBAsic.PCAN_USBBUS1;
	m_HandlesArray[26] := TPCANBAsic.PCAN_USBBUS2;
	m_HandlesArray[27] := TPCANBAsic.PCAN_USBBUS3;
	m_HandlesArray[28] := TPCANBAsic.PCAN_USBBUS4;
	m_HandlesArray[29] := TPCANBAsic.PCAN_USBBUS5;
	m_HandlesArray[30] := TPCANBAsic.PCAN_USBBUS6;
	m_HandlesArray[31] := TPCANBAsic.PCAN_USBBUS7;
	m_HandlesArray[32] := TPCANBAsic.PCAN_USBBUS8;
  m_HandlesArray[33] := TPCANBAsic.PCAN_USBBUS9;
	m_HandlesArray[34] := TPCANBAsic.PCAN_USBBUS10;
	m_HandlesArray[35] := TPCANBAsic.PCAN_USBBUS11;
	m_HandlesArray[36] := TPCANBAsic.PCAN_USBBUS12;
	m_HandlesArray[37] := TPCANBAsic.PCAN_USBBUS13;
	m_HandlesArray[38] := TPCANBAsic.PCAN_USBBUS14;
	m_HandlesArray[39] := TPCANBAsic.PCAN_USBBUS15;
	m_HandlesArray[40] := TPCANBAsic.PCAN_USBBUS16;
	m_HandlesArray[41] := TPCANBAsic.PCAN_PCCBUS1;
	m_HandlesArray[42] := TPCANBAsic.PCAN_PCCBUS2;
	m_HandlesArray[43] := TPCANBAsic.PCAN_LANBUS1;
	m_HandlesArray[44] := TPCANBAsic.PCAN_LANBUS2;
	m_HandlesArray[45] := TPCANBAsic.PCAN_LANBUS3;
	m_HandlesArray[46] := TPCANBAsic.PCAN_LANBUS4;
	m_HandlesArray[47] := TPCANBAsic.PCAN_LANBUS5;
	m_HandlesArray[48] := TPCANBAsic.PCAN_LANBUS6;
	m_HandlesArray[49] := TPCANBAsic.PCAN_LANBUS7;
	m_HandlesArray[50] := TPCANBAsic.PCAN_LANBUS8;
	m_HandlesArray[51] := TPCANBAsic.PCAN_LANBUS9;
	m_HandlesArray[52] := TPCANBAsic.PCAN_LANBUS10;
	m_HandlesArray[53] := TPCANBAsic.PCAN_LANBUS11;
	m_HandlesArray[54] := TPCANBAsic.PCAN_LANBUS12;
	m_HandlesArray[55] := TPCANBAsic.PCAN_LANBUS13;
	m_HandlesArray[56] := TPCANBAsic.PCAN_LANBUS14;
	m_HandlesArray[57] := TPCANBAsic.PCAN_LANBUS15;
	m_HandlesArray[58] := TPCANBAsic.PCAN_LANBUS16;

	// As defautl, normal CAN hardware is used
	//
	m_IsFD := false;

	// Create a list to store the displayed messages
	//
	m_LastMsgsList := TList.Create;

	// Create Event to use Received-event
	//
	m_hEvent := CreateEvent(nil, False, False, '');

	// Set the Read-thread variable to null
	//
	m_hThread := 0;

	// We set the variable to know which reading mode is
	// currently selected (Timer by default)
	//
	m_ActiveReadingMode := 0;

	// Prepares the PCAN-Basic's debug-Log file
	//
	FillComboBoxData();

	// Init log parameters
	ConfigureLogFile();

	// Set default connection status
	//
	SetConnectionStatus(false);
end;

procedure TForm1.InitializeProtection();
begin
    m_objpCS := TCriticalSection.Create;
end;

procedure TForm1.FinalizeProtection();
begin
    try
        m_objpCS.Free;
        m_objpCS := nil;
    except

    end;
end;

procedure TForm1.FillComboBoxData;
begin
	// Channels will be check
	//
	btnHwRefresh.Click();

  // FD Bitrate:
  //      Arbitration: 1 Mbit/sec
  //      Data: 2 Mbit/sec
	//
	txtBitrate.Text := 'f_clock_mhz=20, nom_brp=5, nom_tseg1=2, nom_tseg2=1, nom_sjw=1, data_brp=2, data_tseg1=3, data_tseg2=1, data_sjw=1';

	// TPCANBaudrate
	//
	cbbBaudrates.ItemIndex := 2; // 500 K
	cbbBaudratesChange(cbbBaudrates);

	// Hardware Type for no plugAndplay hardware
	//
	cbbHwType.ItemIndex := 0;
	cbbHwTypeChange(cbbHwType);

	// Interrupt for no plugAndplay hardware
	//
	cbbInterrupt.ItemIndex := 0;

	// IO Port for no plugAndplay hardware
	//
	cbbIO.ItemIndex := 0;

	// Parameters for GetValue and SetValue function calls
	//
	cbbParameter.ItemIndex := 0;
	cbbParameterChange(cbbParameter);
end;

procedure TForm1.ConfigureLogFile();
var
    iBuffer : Integer;
begin
	// Sets the mask to catch all events
	//
	iBuffer := TPCANBasic.LOG_FUNCTION_ALL;

	// Configures the log file.
	// NOTE: The Log capability is to be used with the NONEBUS Handle. Other handle than this will
	// cause the function fail.
	//
	TPCANBasic.SetValue(TPCANBasic.PCAN_NONEBUS, PCAN_LOG_CONFIGURE, PLongWord(@iBuffer), sizeof(iBuffer));
end;

procedure TForm1.ConfigureTraceFile();
var
    iBuffer : Integer;
    stsResult : TPCANStatus;
begin
	// Configure the maximum size of a trace file to 5 megabytes
	//
	iBuffer := 5;
    stsResult := TPCANBasic.SetValue(m_PcanHandle, PCAN_TRACE_SIZE, PLongWord(@iBuffer), sizeof(iBuffer));
    if (stsResult <> PCAN_ERROR_OK) then
	    IncludeTextMessage(GetFormatedError(stsResult));

    // Configure the way how trace files are created:
    // * Standard name is used
    // * Existing file is ovewritten,
    // * Only one file is created.
    // * Recording stopts when the file size reaches 5 megabytes.
    //
    iBuffer := TPCANBasic.TRACE_FILE_SINGLE Or TPCANBasic.TRACE_FILE_OVERWRITE;
	stsResult := TPCANBasic.SetValue(m_PcanHandle, PCAN_TRACE_CONFIGURE, PLongWord(@iBuffer), sizeof(iBuffer));
    if (stsResult <> PCAN_ERROR_OK) then
	    IncludeTextMessage(GetFormatedError(stsResult));    
end;

procedure TForm1.SetConnectionStatus(bConnected : boolean);
begin
	// Buttons
	//
	btnInit.Enabled := NOT bConnected;
	btnRead.Enabled := (bConnected AND rdbManual.Checked);
	btnWrite.Enabled := bConnected;
	btnRelease.Enabled := bConnected;
	btnFilterApply.Enabled := bConnected;
	btnFilterQuery.Enabled := bConnected;
	btnGetVersions.Enabled := bConnected;
	btnHwRefresh.Enabled := NOT bConnected;
	btnStatus.Enabled := bConnected;
	btnReset.Enabled := bConnected;

	// ComboBoxs
	//
	cbbBaudrates.Enabled := NOT bConnected;
	cbbChannel.Enabled := NOT bConnected;
	cbbHwType.Enabled := NOT bConnected;
	cbbIO.Enabled := NOT bConnected;
	cbbInterrupt.Enabled := NOT bConnected;

	// Check-Buttons
  //
  chbCanFD.Enabled := NOT bConnected;

	// Hardware configuration and read mode
	//
	if (NOT bConnected) then
		cbbChannelChange(cbbChannel)
	else
		ReadingModeChanged();

    // Display messages in grid
    //
    tmrDisplay.Enabled := bConnected;
end;

procedure TForm1.IncludeTextMessage(strMsg: AnsiString);
begin
	// Inserts a message in the Info box and focuses it
	//
	lbxInfo.Items.Add(strMsg);
	lbxInfo.ItemIndex := lbxInfo.Items.Count-1;
end;

procedure TForm1.InsertMsgEntry(NewMsg : TPCANMsgFD; timeStamp: TPCANTimestampFD);
var
  msgStsCurrentMsg : MessageStatus;
	CurrentItem : TListItem;
begin
	// (Protected environment)
	//
    try
        m_objpCS.Enter;

		// We add this status in the last message list
		//
		msgStsCurrentMsg := MessageStatus.Create(NewMsg, timeStamp, lstMessages.Items.Count);
    msgStsCurrentMsg.ShowingPeriod := chbShowPeriod.Checked;
		m_LastMsgsList.Add(msgStsCurrentMsg);

		// Add the new ListView Item with the Type of the message
		//
		CurrentItem := lstMessages.Items.Add();
		CurrentItem.Caption := msgStsCurrentMsg.TypeString;

		// We set the ID of the message
		//
		CurrentItem.SubItems.Add(msgStsCurrentMsg.IdString);
		// We set the length of the Message
		//
		CurrentItem.SubItems.Add(IntToStr(GetLengthFromDLC(NewMsg.DLC, NOT ((Byte(NewMsg.MSGTYPE) AND Byte(PCAN_MESSAGE_FD)) <>0))));
		// we set the message count message (this is the First, so count is 1)
		//
		CurrentItem.SubItems.Add(IntToStr(msgStsCurrentMsg.Count));
		// Add timestamp information
		//
		CurrentItem.SubItems.Add(msgStsCurrentMsg.TimeString);
		// We set the data of the message.
		//
		CurrentItem.SubItems.Add(msgStsCurrentMsg.DataString);    
    finally
        m_objpCS.Leave;
    end;
end;

procedure TForm1.DisplayMessages();
var
    msgStatus : MessageStatus;
    CurrentItem : TListItem;
    I : integer;
begin
    // We search if a message (Same ID and Type) is
    // already received or if this is a new message
  	// (in a protected environment)
	  //
    try
        m_objpCS.Enter;

        for I := 0 to m_LastMsgsList.Count - 1 do
        begin
            msgStatus := MessageStatus(m_LastMsgsList.Items[I]);
            if msgStatus.MarkedAsUpdated then
            begin
                msgStatus.MarkedAsUpdated := false;
                CurrentItem := lstMessages.Items[msgStatus.Position];
                CurrentItem.SubItems.Strings[1] := IntToStr(GetLengthFromDLC(msgStatus.CANMsg.DLC, NOT ((Byte(msgStatus.CANMsg.MSGTYPE) AND Byte(PCAN_MESSAGE_FD)) <>0)));
                CurrentItem.SubItems.Strings[2] := IntToStr(msgStatus.Count);
                CurrentItem.SubItems.Strings[3] := msgStatus.TimeString;
                CurrentItem.SubItems.Strings[4] := msgStatus.DataString;
            end;
        end;
    finally
        m_objpCS.Leave;
    end;
end;

function TForm1.WriteFrame() : TPCANStatus;
var
	CANMsg : TPCANMsg;
  CurrentTextBox: TEdit;
  I : integer;
begin
	// We configurate the Message.  The ID (max 0x1FF),
	// Length of the Data, Message Type (Standard in
	// this example) and die data
	//
  ZeroMemory(@CANMsg, SizeOf(CANMsg));
	CANMsg.ID := StrToInt('0x'+txtID.Text);
	CANMsg.LEN := nudLength.Position;
  if(chbExtended.Checked) then
    CANMsg.MSGTYPE := PCAN_MESSAGE_EXTENDED
   else
      CANMsg.MSGTYPE := PCAN_MESSAGE_STANDARD;

	// If a remote frame will be sent, the data bytes are not important.
	//
	if (chbRemote.Checked) then
		CANMsg.MSGTYPE := TPCANMessageType(Byte(CANMsg.MSGTYPE) OR Byte(PCAN_MESSAGE_RTR))
	else
	begin
		// We get so much data as the Len of the message
		//
    for I := 0 to (GetLengthFromDLC(CANMsg.LEN, true) - 1) do
    begin
      CurrentTextBox := TEdit(FindComponent('txtData'+IntToStr(i)));
      CANMsg.DATA[i] := StrToInt('0x' + CurrentTextBox.Text);
    end;
  end;

  Result := TPCANBasic.Write(m_PcanHandle, CANMsg);
end;

function TForm1.WriteFrameFD() : TPCANStatus;
var
	CANMsg : TPCANMsgFD;
  CurrentTextBox: TEdit;
  I : integer;
  iLength : integer;
begin
	// We configurate the Message.  The ID (max 0x1FF),
	// Length of the Data, Message Type (Standard in
	// this example) and die data
	//
  ZeroMemory(@CANMsg, SizeOf(CANMsg));
	CANMsg.ID := StrToInt('0x'+txtID.Text);
	CANMsg.DLC := nudLength.Position;
  if(chbExtended.Checked) then
    CANMsg.MSGTYPE := PCAN_MESSAGE_EXTENDED
   else
      CANMsg.MSGTYPE := PCAN_MESSAGE_STANDARD;

  if chbFD.Checked then
    CANMsg.MSGTYPE := TPCANMessageType(Byte(CANMsg.MSGTYPE) OR Byte(PCAN_MESSAGE_FD));
  if chbBRS.Checked then
    CANMsg.MSGTYPE := TPCANMessageType(Byte(CANMsg.MSGTYPE) OR Byte(PCAN_MESSAGE_BRS));

	// If a remote frame will be sent, the data bytes are not important.
	//
	if (chbRemote.Checked) then
		CANMsg.MSGTYPE := TPCANMessageType(Byte(CANMsg.MSGTYPE) OR Byte(PCAN_MESSAGE_RTR))
	else
	begin
		// We get so much data as the Len of the message
		//
    iLength := GetLengthFromDLC(CANMsg.DLC, ((Byte(CANMsg.MSGTYPE) And Byte(PCAN_MESSAGE_FD)) = 0));
    for I := 0 to (iLength - 1) do
    begin
      CurrentTextBox := TEdit(FindComponent('txtData'+IntToStr(i)));
      CANMsg.DATA[i] := StrToInt('0x' + CurrentTextBox.Text);
    end;
  end;

  Result := TPCANBasic.WriteFD(m_PcanHandle, CANMsg);
end;

function TForm1.ReadMessageFD() : TPCANStatus;
var
	CANMsg : TPCANMsgFD;
	CANTimeStamp : TPCANTimestampFD;
	stsResult : TPCANStatus;
begin
		// We execute the "Read" function of the PCANBasic
		//
  	stsResult := TPCANBasic.ReadFD(m_PcanHandle, CANMsg, CANTimeStamp);
    if (stsResult <> PCAN_ERROR_QRCVEMPTY) then
		    // We process the received message
    		//
        ProcessMessage(CANMsg, CANTimeStamp);
    Result := stsResult;
end;

function TForm1.ReadMessage() : TPCANStatus;
var
	CANMsg : TPCANMsg;
	CANTimeStamp : TPCANTimestamp;
	stsResult : TPCANStatus;
begin
		// We execute the "Read" function of the PCANBasic
		//
    stsResult := TPCANBasic.Read(m_PcanHandle, CANMsg, CANTimeStamp);
		// We process the message(s)
		//
		if (stsResult <> PCAN_ERROR_QRCVEMPTY) then
			ProcessMessage(CANMsg, CANTimeStamp);
    Result := stsResult;
end;

procedure TForm1.ReadMessages();
var
	stsResult : TPCANStatus;
begin
  // We read at least one time the queue looking for messages.
  // If a message is found, we look again trying to find more.
  // If the queue is empty or an error occurr, we get out from
  // the dowhile statement.
  //
  repeat
		// We execute the "Read" function of the PCANBasic
		//
    if m_IsFD then
      stsResult := ReadMessageFD()
    Else
		  stsResult := ReadMEssage();

		if (stsResult = PCAN_ERROR_ILLOPERATION) then
      Break;
	until (NOT btnRelease.Enabled OR ((LongWord(stsResult) AND LongWord(PCAN_ERROR_QRCVEMPTY)) <> 0));
end;

procedure TForm1.ProcessMessage(theMsg : TPCANMsgFD; itsTimeStamp : TPCANTimestampFD);
var
	msg : MessageStatus;
    I : integer;
begin
    // We search if a message (Same ID and Type) is
    // already received or if this is a new message
	// (in a protected environment)
	//
    try
        m_objpCS.Enter;

        for I := 0 to m_LastMsgsList.Count - 1 do
        begin
            msg := MessageStatus(m_LastMsgsList.Items[I]);
            if (msg.CANMsg.ID = theMsg.ID) And (msg.CANMsg.MSGTYPE = theMsg.MSGTYPE) then
             begin
                // Modify the message and exit
                //
                msg.Update(theMsg, itsTimeStamp);
                exit;
             end;
        end;

        // Message not found. It will created
        //
        InsertMsgEntry(theMsg, itsTimeStamp);
    finally
        m_objpCS.Leave;
    end;
end;

procedure TForm1.ProcessMessage(theMsg : TPCANMsg; itsTimeStamp : TPCANTimestamp);
var
  newMsg: TPCANMsgFD;
  newTimestamp: TPCANTimestampFD;
  I : integer;
  iLength : integer;
begin
  ZeroMemory(@newMsg, SizeOf(newMsg));
  newMsg.ID := theMsg.ID;
  newMsg.DLC := theMsg.LEN;

  if theMsg.LEN > 8 then
    iLength := 8
  else
    iLength := theMsg.LEN;

  for I := 0 to iLength - 1 do
    newMsg.DATA[i] := theMsg.DATA[i];

  newTimestamp := (itsTimeStamp.micros + 1000 * itsTimeStamp.millis + $100000000 * 1000 * itsTimeStamp.millis_overflow);
  ProcessMessage(newMsg, newTimestamp);
end;

function CallCANReadThreadFunc(lpParam : Pointer) : LongWord; stdcall;
begin

	// Call TForm1 Thread member function
	//
	result := Form1.CANReadThreadFunc();
end;

procedure TForm1.ReadingModeChanged();
var
    dwTemp : LongWord;
begin
	if (NOT btnRelease.Enabled) then
		exit;

	case m_ActiveReadingMode of
	    0:
        begin
         	// If active reading mode is By Timer
		    // Terminate Read Thread if it exists
			//
			if(m_hThread <> 0) then
			begin
				TerminateThread(m_hThread, 1000);
				m_hThread := 0;
			end;
			// We start to read
			//
			tmrRead.Enabled := true;
        end;
        1:
        begin
            // If active reading mode is By Event
			// We stop to read from the CAN queue
			//
			tmrRead.Enabled := false;

			// Create Reading Thread ....
			//
			m_hThread := CreateThread(nil, 0, @CallCANReadThreadFunc, self , 0, dwTemp);

			if(m_hThread = 0) then
				MessageBox(0,'Create CANRead-Thread failed','Error!',MB_ICONERROR)
        end
        else
        begin
            // If active reading mode is Manual
			// Terminate Read Thread if it exists
			//
			if(m_hThread <> 0) then
			begin
				TerminateThread(m_hThread, 1000);
				m_hThread := 0;
			end;
			// We enable the button for read
			//
			tmrRead.Enabled := false;
			btnRead.Enabled := (btnRelease.Enabled AND rdbManual.Checked);
        end;
    end;
end;

function TForm1.CANReadThreadFunc() : LongWord;
var
	stsResult : TPCANStatus;
	dwTemp : LongWord;
begin
	// Sets the handle of the Receive-Event.
	//
	stsResult := TPCANBasic.SetValue(m_PcanHandle, PCAN_RECEIVE_EVENT ,PLongWord(@m_hEvent), sizeof(m_hEvent));

	// If it fails, a error message is shown
	//
	if (stsResult <> PCAN_ERROR_OK) then
	begin
		MessageBox(0, PChar(string(GetFormatedError(stsResult))), 'Error!',MB_ICONERROR);
		result := 1;
        exit;
	end;

	// While this mode is selected
	//
	while(rdbEvent.Checked) do
	begin
		//Wait for CAN Data...
		if (WaitForSingleObject(m_hEvent, INFINITE) = WAIT_OBJECT_0) then
			ReadMessages();
	end;

	// Resets the Event-handle configuration
	//
	dwTemp := 0;
	TPCANBasic.SetValue(m_PcanHandle, PCAN_RECEIVE_EVENT ,PLongWord(@dwTemp), sizeof(dwTemp));

	result := 0;
end;

procedure TForm1.EnableDisableDataFields(length: integer);
var
  CurrentTextBox: TEdit;
  I: integer;
begin
  CurrentTextBox := txtData0;
  for I := 0 to 64 do
  begin
    CurrentTextBox.Enabled := i <= length;
    if (i < 64) then
      CurrentTextBox := TEdit(FindComponent('txtData' + IntToStr(i)));
  end;
end;
  
function TForm1.FormatChannelName(handle : TPCANHandle; isFD: boolean) : AnsiString;
var
	strName : AnsiString;
    byChannel : byte;
begin
	// Gets the owner device and channel for a
	// PCAN-Basic handle
	//
  if handle < $100 then
    byChannel := handle AND $F
  else
  	byChannel := handle AND $FF;

	// Constructs the PCAN-Basic Channel name and return it
	//
	strName := GetTPCANHandleName(handle);
  if isFD then
  	result := Format('%s:FD %d (%Xh)', [strName, byChannel, handle])
  else
    result := Format('%s %d (%Xh)', [strName, byChannel, handle])
end;

function TForm1.FormatChannelName(handle : TPCANHandle) : AnsiString;
begin
	result := FormatChannelName(handle, false);
end;

function TForm1.GetTPCANHandleName(handle : TPCANHandle) : AnsiString;
begin
    if((handle >= TPCANBasic.PCAN_ISABUS1) AND (handle <= TPCANBasic.PCAN_ISABUS8)) then
        result := 'PCAN_ISA'
    else if(handle = TPCANBasic.PCAN_DNGBUS1) then
        result := 'PCAN_DNG'
    else if((handle >= TPCANBasic.PCAN_PCIBUS1) AND (handle <= TPCANBasic.PCAN_PCIBUS8)) then
        result := 'PCAN_PCI'
    else if((handle >= TPCANBasic.PCAN_USBBUS1) AND (handle <= TPCANBasic.PCAN_USBBUS8)) then
        result := 'PCAN_USB'
    else if((handle >= TPCANBasic.PCAN_PCCBUS1) AND (handle <= TPCANBasic.PCAN_PCCBUS2)) then
        result := 'PCAN_PCC'
    else if((handle >= TPCANBasic.PCAN_LANBUS1) AND (handle <= TPCANBasic.PCAN_LANBUS8)) then
        result := 'PCAN_LAN'
    else
        result := 'PCAN_NONE';
end;

function TForm1.GetFormatedError(error: TPCANStatus) : AnsiString;
var
	status : TPCANStatus;
	buffer : array[0..255] of Ansichar;
begin
	// Gets the text using the GetErrorText API function
	// If the function success, the translated error is returned. If it fails,
	// a text describing the current error is returned.
	//
	status := TPCANBasic.GetErrorText(error, 0, buffer);
	if(status <> PCAN_ERROR_OK) then
		result := Format('An error ocurred. Error-code''s text (%Xh) couldn''t be retrieved', [Integer(error)])
	else
		result := buffer;
end;

function TForm1.GetFilterStatus(var status: Integer) : boolean;
var
	stsResult : TPCANStatus;
begin
	// Tries to get the status of the filter for the current connected hardware
	//
	stsResult := TPCANBasic.GetValue(m_PcanHandle, PCAN_MESSAGE_FILTER, PLongWord(@status), sizeof(status));

	// If it fails, a error message is shown
	//
	if (stsResult <> PCAN_ERROR_OK) then
	begin
		MessageBox(0, PChar(string(GetFormatedError(stsResult))), 'Error!',MB_ICONERROR);
		result := false;
	end
    else
    	result := true;
end;

procedure TForm1.tmrDisplayTimer(Sender: TObject);
begin
    DisplayMessages();
end;

procedure TForm1.tmrReadTimer(Sender: TObject);
begin
	ReadMessages();
end;

procedure TForm1.btnHwRefreshClick(Sender: TObject);
var
	iBuffer : Integer;
	stsResult : TPCANStatus;
  I: Integer;
  iCount :Integer;
  isFD: Boolean;
begin
	// Clears the Channel combioBox and fill it againa with
	// the PCAN-Basic handles for no-Plug&Play hardware and
	// the detected Plug&Play hardware
	//
	cbbChannel.Items.Clear();

  iCount := Trunc((sizeof(m_HandlesArray) /sizeof(TPCANHandle)))-1;

	for i:= 0 To iCount do
	begin
		// Includes all no-Plug&Play Handles
		//
		if (m_HandlesArray[i] <= TPCANBasic.PCAN_DNGBUS1) then
			cbbChannel.Items.Add(FormatChannelName(m_HandlesArray[i]))
		else
		begin
			// Checks for a Plug&Play Handle and, according with the return value, includes it
			// into the list of available hardware channels.
			//
			stsResult := TPCANBasic.GetValue(m_HandlesArray[i], PCAN_CHANNEL_CONDITION, PlongWord(@iBuffer), sizeof(iBuffer));
			if ((stsResult = PCAN_ERROR_OK) AND ((iBuffer AND TPCANBAsic.PCAN_CHANNEL_AVAILABLE) = TPCANBAsic.PCAN_CHANNEL_AVAILABLE)) then
      begin
        stsResult := TPCANBasic.GetValue(m_HandlesArray[i], PCAN_CHANNEL_FEATURES, PlongWord(@iBuffer), sizeof(iBuffer));
        isFD := (stsResult = PCAN_ERROR_OK) AND (iBuffer And Byte(TPCANBAsic.FEATURE_FD_CAPABLE) <> 0);
				cbbChannel.Items.Add(FormatChannelName(m_HandlesArray[i], isFD));
      end;
		end;
	end;

	// Select Last One
	//
	cbbChannel.ItemIndex := cbbChannel.Items.Count - 1;
	cbbChannelChange(cbbChannel);
end;

procedure TForm1.btnInitClick(Sender: TObject);
var
	stsResult : TPCANStatus;
	selectedIO : Integer;
	selectedInterrupt : Integer;
begin
	// Parse IO and Interrupt
	//
	selectedIO := StrToInt('0x'+cbbIO.Text);
	selectedInterrupt := StrToInt('0x'+cbbInterrupt.Text);

	// Connects a selected PCAN-Basic channel
	//
  if m_IsFD then
    stsResult := TPCANBasic.InitializeFD(m_PcanHandle, TPCANBitrateFD(txtBitrate.Text))
  Else
	  stsResult := TPCANBasic.Initialize(m_PcanHandle, m_Baudrate, m_HwType, selectedIO, selectedInterrupt);

	if (stsResult <> PCAN_ERROR_OK) then
    if (stsResult <> PCAN_ERROR_CAUTION) then
  		MessageBox(0, PChar(string(GetFormatedError(stsResult))), 'Error!',MB_ICONERROR)
    else
    begin
      IncludeTextMessage('******************************************************');
      IncludeTextMessage('The bitrate being used is different than the given one');
      IncludeTextMessage('******************************************************');
      stsResult := PCAN_ERROR_OK;
    end
  else
        // Prepares the PCAN-Basic's PCAN-Trace file
        //
        ConfigureTraceFile();

	// Sets the connection status of the main-form
	//
	SetConnectionStatus(stsResult = PCAN_ERROR_OK);
end;

procedure TForm1.btnReleaseClick(Sender: TObject);
begin
	// Terminate Read Thread if it exists
	//
	if(m_hThread <> 0) then
	begin
		TerminateThread(m_hThread, 1000);
		m_hThread := 0;
	end;

	// We stop to read from the CAN queue
	//
	tmrRead.Enabled := false;

	// Releases a current connected PCAN-Basic channel
	//
	TPCANBasic.Uninitialize(m_PcanHandle);

	// Sets the connection status of the main-form
	//
	SetConnectionStatus(false);
end;

procedure TForm1.btnFilterApplyClick(Sender: TObject);
var
	iBuffer : Integer;
	info : AnsiString;
	stsResult : TPCANStatus;
begin
	// Gets the current status of the message filter
	//
	if (Not GetFilterStatus(iBuffer)) then
		exit;

	// Configures the message filter for a custom range of messages
	//
	if (rdbFilterCustom.Checked) then
	begin
        // Sets the custom filter
        //
        if(chbFilterExt.Checked) then
            stsResult := TPCANBasic.FilterMessages(m_PcanHandle, StrToInt('0x'+txtIdFrom.Text), StrToInt('0x'+txtIdTo.Text), PCAN_MODE_EXTENDED)
        else
            stsResult := TPCANBasic.FilterMessages(m_PcanHandle, StrToInt('0x'+txtIdFrom.Text), StrToInt('0x'+txtIdTo.Text), PCAN_MODE_STANDARD);
        // If success, an information message is written, if it is not, an error message is shown
        //
        if (stsResult = PCAN_ERROR_OK) then
        begin
            info := Format('The filter was customized. IDs from {0x%s} to {0x%s} will be received', [txtIdFrom.Text,txtIdTo.Text]);
            IncludeTextMessage(info);
        end
        else
            MessageBox(0, PChar(string(GetFormatedError(stsResult))), 'Error!',MB_ICONERROR);

		exit;
	end;

	// The filter will be full opened or complete closed
	//
	if (rdbFilterClose.Checked) then
		iBuffer := TPCANBasic.PCAN_FILTER_CLOSE
	else
		iBuffer := TPCANBasic.PCAN_FILTER_OPEN;

	// The filter is configured
	//
	stsResult := TPCANBasic.SetValue(m_PcanHandle, PCAN_MESSAGE_FILTER, PLongWord(@iBuffer), sizeof(iBuffer));

	// If success, an information message is written, if it is not, an error message is shown
	//
	if (stsResult = PCAN_ERROR_OK) then
	begin

        if(rdbFilterClose.Checked) then
    		IncludeTextMessage('The filter was successfully closed.')
        else
    		IncludeTextMessage('The filter was successfully opened.');
	end
	else
		MessageBox(0, PChar(string(GetFormatedError(stsResult))), 'Error!',MB_ICONERROR);
end;

procedure TForm1.btnFilterQueryClick(Sender: TObject);
var
	iBuffer : Integer;
begin
	// Queries the current status of the message filter
	//
	if (GetFilterStatus(iBuffer)) then
        // The filter is closed
        //
        if (iBuffer = TPCANBasic.PCAN_FILTER_CLOSE) then
            IncludeTextMessage('The Status of the filter is: closed.')
        // The filter is fully opened
        //
        else if (iBuffer = TPCANBasic.PCAN_FILTER_OPEN) then
            IncludeTextMessage('The Status of the filter is: full opened.')
        // The filter is customized
        //
        else if (iBuffer = TPCANBasic.PCAN_FILTER_CUSTOM) then
            IncludeTextMessage('The Status of the filter is: customized.')
        // The status of the filter is undefined. (Should never happen)
        //
        else
            IncludeTextMessage('The Status of the filter is: Invalid.');
end;

procedure TForm1.btnParameterSetClick(Sender: TObject);
var
	stsResult : TPCANStatus;
	iBuffer : Integer;
	info : AnsiString;
	szDirectory : array[0..MAX_PATH] of char;
begin
	// Sets a PCAN-Basic parameter value
	//
	case cbbParameter.ItemIndex of
		// The Device-Number of an USB channel will be set
		//
	    0:
        begin
    		iBuffer := StrToInt(txtDeviceIdOrDelay.Text);
	    	stsResult := TPCANBasic.SetValue(m_PcanHandle, PCAN_DEVICE_NUMBER, PLongWord(@iBuffer), sizeof(iBuffer));
		    if(stsResult = PCAN_ERROR_OK) then
			    IncludeTextMessage('The desired Device-Number was successfully configured');
		end;

		// The 5 Volt Power feature of a PC-card or USB will be set
		//
	    1:
        begin
            if(rdbParamActive.Checked) then
                iBuffer := TPCANBasic.PCAN_PARAMETER_ON
            else
                iBuffer := TPCANBasic.PCAN_PARAMETER_OFF;

            stsResult := TPCANBasic.SetValue(m_PcanHandle, PCAN_5VOLTS_POWER, PLongWord(@iBuffer), sizeof(iBuffer));
            if(stsResult = PCAN_ERROR_OK) then
            begin
                if(iBuffer = TPCANBasic.PCAN_PARAMETER_ON) then
                    IncludeTextMessage('The USB/PC-Card 5 power was successfully activated')
                else
                    IncludeTextMessage('The USB/PC-Card 5 power was successfully deactivated');
            end;
        end;

		// The feature for automatic reset on BUS-OFF will be set
		//
	    2:
        begin
            if(rdbParamActive.Checked) then
                iBuffer := TPCANBasic.PCAN_PARAMETER_ON
            else
                iBuffer := TPCANBasic.PCAN_PARAMETER_OFF;
            stsResult := TPCANBasic.SetValue(m_PcanHandle, PCAN_BUSOFF_AUTORESET, PLongWord(@iBuffer), sizeof(iBuffer));
            if(stsResult = PCAN_ERROR_OK) then
            begin
                if(iBuffer = TPCANBasic.PCAN_PARAMETER_ON) then
                    IncludeTextMessage('The automatic-reset on BUS-OFF was successfully activated')
                else
                    IncludeTextMessage('The automatic-reset on BUS-OFF was successfully deactivated')
            end;
		end;

		// The CAN option "Listen Only" will be set
		//
	    3:
        begin
            if(rdbParamActive.Checked) then
                iBuffer := TPCANBasic.PCAN_PARAMETER_ON
            else
                iBuffer := TPCANBasic.PCAN_PARAMETER_OFF;
            stsResult := TPCANBasic.SetValue(m_PcanHandle, PCAN_LISTEN_ONLY, PLongWord(@iBuffer), sizeof(iBuffer));
            if(stsResult = PCAN_ERROR_OK) then
            begin
                if(iBuffer = TPCANBasic.PCAN_PARAMETER_ON) then
                    IncludeTextMessage('The CAN option "Listen Only" was successfully activated')
                else
                    IncludeTextMessage('The CAN option "Listen Only" was successfully deactivated');
            end;
		end;

		// The feature for logging debug-information will be set
		//
	    4:
        begin
            if(rdbParamActive.Checked) then
                iBuffer :=  TPCANBasic.PCAN_PARAMETER_ON
            else
                iBuffer :=  TPCANBasic.PCAN_PARAMETER_OFF;
            stsResult := TPCANBasic.SetValue(TPCANbasic.PCAN_NONEBUS, PCAN_LOG_STATUS, PLongWord(@iBuffer), sizeof(iBuffer));
            if(stsResult = PCAN_ERROR_OK) then
            begin
                if(iBuffer = TPCANBasic.PCAN_PARAMETER_ON) then
                    IncludeTextMessage('The feature for logging debug information was successfully activated')
                else
                    IncludeTextMessage('The feature for logging debug information was successfully deactivated');
                GetCurrentDirectory(sizeof(szDirectory) - 1, szDirectory);
                info := Format('Log file folder: %s', [szDirectory]);
                IncludeTextMessage(info);
            end;
		end;

		// The channel option "Receive Status" will be set
		//
	    5:
        begin
            if(rdbParamActive.Checked) then
                iBuffer := TPCANBasic.PCAN_PARAMETER_ON
            else
                iBuffer := TPCANBasic.PCAN_PARAMETER_OFF;
            stsResult := TPCANBasic.SetValue(m_PcanHandle, PCAN_RECEIVE_STATUS, PLongWord(@iBuffer), sizeof(iBuffer));
            if(stsResult = PCAN_ERROR_OK) then
            begin
                if(iBuffer = TPCANBasic.PCAN_PARAMETER_ON) then
                    IncludeTextMessage('The channel option "Receive Status" was set to ON')
                else
                    IncludeTextMessage('The channel option "Receive Status" was set to OFF');
            end;
		end;

		// The feature for tracing will be set
		//
	    7:
        begin
            if(rdbParamActive.Checked) then
                iBuffer := TPCANBasic.PCAN_PARAMETER_ON
            else
                iBuffer := TPCANBasic.PCAN_PARAMETER_OFF;
            stsResult := TPCANBasic.SetValue(m_PcanHandle, PCAN_TRACE_STATUS, PLongWord(@iBuffer), sizeof(iBuffer));
            if(stsResult = PCAN_ERROR_OK) then
            begin
                if(iBuffer = TPCANBasic.PCAN_PARAMETER_ON) then
                    IncludeTextMessage('The feature for tracing data was successfully activated')
                else
                    IncludeTextMessage('The feature for tracing data was successfully deactivated');
            end;
		end;

		// The feature for identifying an USB Channel will be set
		//
	    8:
        begin
            if(rdbParamActive.Checked) then
                iBuffer := TPCANBasic.PCAN_PARAMETER_ON
            else
                iBuffer := TPCANBasic.PCAN_PARAMETER_OFF;
            stsResult := TPCANBasic.SetValue(m_PcanHandle, PCAN_CHANNEL_IDENTIFYING, PLongWord(@iBuffer), sizeof(iBuffer));
            if(stsResult = PCAN_ERROR_OK) then
            begin
                if(iBuffer = TPCANBasic.PCAN_PARAMETER_ON) then
                    IncludeTextMessage('The procedure for channel identification was successfully activated')
                else
                    IncludeTextMessage('The procedure for channel identification was successfully deactivated');
            end;
        end;
		// The feature for using an already configured speed will be set
		//
	    10:
        begin
            if(rdbParamActive.Checked) then
                iBuffer := TPCANBasic.PCAN_PARAMETER_ON
            else
                iBuffer := TPCANBasic.PCAN_PARAMETER_OFF;
            stsResult := TPCANBasic.SetValue(m_PcanHandle, PCAN_BITRATE_ADAPTING, PLongWord(@iBuffer), sizeof(iBuffer));
            if(stsResult = PCAN_ERROR_OK) then
            begin
                if(iBuffer = TPCANBasic.PCAN_PARAMETER_ON) then
                    IncludeTextMessage('The feature for bit rate adaptation was successfully activated')
                else
                    IncludeTextMessage('The feature for bit rate adaptation was successfully deactivated');
            end;
    		end;
		// The option "Allow Status Frames" will be set
		//
        17:
          begin
            if(rdbParamActive.Checked) then
                iBuffer := TPCANBasic.PCAN_PARAMETER_ON
            else
                iBuffer := TPCANBasic.PCAN_PARAMETER_OFF;
            stsResult := TPCANBasic.SetValue(m_PcanHandle, PCAN_ALLOW_STATUS_FRAMES, PLongWord(@iBuffer), sizeof(iBuffer));
            if(stsResult = PCAN_ERROR_OK) then
            begin
                if(iBuffer = TPCANBasic.PCAN_PARAMETER_ON) then
                    IncludeTextMessage('The reception of Status frames was successfully enabled')
                else
                    IncludeTextMessage('The reception of Status frames was successfully disabled');
            end;
          end;
		// The option "Allow RTR Frames" will be set
		//
        18:
          begin
            if(rdbParamActive.Checked) then
                iBuffer := TPCANBasic.PCAN_PARAMETER_ON
            else
                iBuffer := TPCANBasic.PCAN_PARAMETER_OFF;
            stsResult := TPCANBasic.SetValue(m_PcanHandle, PCAN_ALLOW_RTR_FRAMES, PLongWord(@iBuffer), sizeof(iBuffer));
            if(stsResult = PCAN_ERROR_OK) then
            begin
                if(iBuffer = TPCANBasic.PCAN_PARAMETER_ON) then
                    IncludeTextMessage('The reception of RTR frames was successfully enabled')
                else
                    IncludeTextMessage('The reception of RTR frames was successfully disabled');
            end;
          end;
		// The option "Allow Error Frames" will be set
		//
        19:
          begin
            if(rdbParamActive.Checked) then
                iBuffer := TPCANBasic.PCAN_PARAMETER_ON
            else
                iBuffer := TPCANBasic.PCAN_PARAMETER_OFF;
            stsResult := TPCANBasic.SetValue(m_PcanHandle, PCAN_ALLOW_ERROR_FRAMES, PLongWord(@iBuffer), sizeof(iBuffer));
            if(stsResult = PCAN_ERROR_OK) then
            begin
                if(iBuffer = TPCANBasic.PCAN_PARAMETER_ON) then
                    IncludeTextMessage('The reception of Error frames was successfully enabled')
                else
                    IncludeTextMessage('The reception of Error frames was successfully disabled');
            end;
          end;

		// The option "Interframes Delay" will be set
		//
	    20:
        begin
    		iBuffer := StrToInt(txtDeviceIdOrDelay.Text);
	    	stsResult := TPCANBasic.SetValue(m_PcanHandle, PCAN_INTERFRAME_DELAY, PLongWord(@iBuffer), sizeof(iBuffer));
		    if(stsResult = PCAN_ERROR_OK) then
        begin
	    		IncludeTextMessage('The delay between transmitting frames was successfully set');
        end;
        end;

		// The current parameter is invalid
		//
	    else
        begin
	    	MessageBox(0, 'Wrong parameter code.', 'Error!',MB_ICONERROR);
		    exit;
        end;
	end;

	// If the function fail, an error message is shown
	//
	if(stsResult <> PCAN_ERROR_OK) then
		MessageBox(0, PChar(string(GetFormatedError(stsResult))), 'Error!',MB_ICONERROR);
end;

procedure TForm1.btnParameterGetClick(Sender: TObject);
var
	stsResult : TPCANStatus;
	iBuffer   : Integer;
  strBuffer :array[0..255] of AnsiChar;
	info      : AnsiString;
  strParts  : TStringList;
  I         : Integer;
begin
	// Sets a PCAN-Basic parameter value
	//
	case cbbParameter.ItemIndex of
		// The Device-Number of an USB channel will be get
		//
	    0:
        begin
		    stsResult := TPCANBasic.GetValue(m_PcanHandle, PCAN_DEVICE_NUMBER, PLongWord(@iBuffer), sizeof(iBuffer));
    		if(stsResult = PCAN_ERROR_OK) then
    		begin
    			info := Format('The configured Device-Number is %d', [iBuffer]);
	    		IncludeTextMessage(info);
		    end;
		end;

		// The 5 Volt Power feature of a PC-card or USB will be get
		//
	    1:
        begin
            stsResult := TPCANBasic.GetValue(m_PcanHandle, PCAN_5VOLTS_POWER, PLongWord(@iBuffer), sizeof(iBuffer));
            if(stsResult = PCAN_ERROR_OK) then
            begin
                if(iBuffer = TPCANBasic.PCAN_PARAMETER_ON) then
                    info := 'The 5-Volt Power of the USB/PC-Card is activated'
                else
                    info := 'The 5-Volt Power of the USB/PC-Card is deactivated';
                IncludeTextMessage(info);
            end;
		end;

		// The feature for automatic reset on BUS-OFF will be get
		//
	    2:
        begin
            stsResult := TPCANBasic.GetValue(m_PcanHandle, PCAN_BUSOFF_AUTORESET, PLongWord(@iBuffer), sizeof(iBuffer));
            if(stsResult = PCAN_ERROR_OK) then
            begin
                if(iBuffer = TPCANBasic.PCAN_PARAMETER_ON) then
                    info := 'The automatic-reset on BUS-OFF is activated'
                else
                    info := 'The automatic-reset on BUS-OFF is deactivated';
                IncludeTextMessage(info);
            end;
        end;

		// The CAN option "Listen Only" will be get
		//
	    3:
        begin
            stsResult := TPCANBasic.GetValue(m_PcanHandle, PCAN_LISTEN_ONLY, PLongWord(@iBuffer), sizeof(iBuffer));
            if(stsResult = PCAN_ERROR_OK) then
            begin
                if (iBuffer = TPCANBasic.PCAN_PARAMETER_ON) then
                    info := 'The CAN-option Listen-Only is activated'
                else
                    info := 'The CAN-option Listen-Only is deactivated';
                IncludeTextMessage(info);
            end;
		end;

		// The feature for logging debug-information will be get
		//
	    4:
        begin
            stsResult := TPCANBasic.GetValue(TPCANBasic.PCAN_NONEBUS, PCAN_LOG_STATUS, PLongWord(@iBuffer), sizeof(iBuffer));
            if(stsResult = PCAN_ERROR_OK) then
            begin
                if(iBuffer = TPCANBasic.PCAN_PARAMETER_ON) then
                    info := 'The feature for logging debug information is activated'
                else
                    info := 'The feature for logging debug information is deactivated';
                IncludeTextMessage(info);
            end;
		end;

		// The activation status of the channel option "Receive Status"  will be retrieved
		//
	    5:
        begin
            stsResult := TPCANBasic.GetValue(m_PcanHandle, PCAN_RECEIVE_STATUS, PLongWord(@iBuffer), sizeof(iBuffer));
            if(stsResult = PCAN_ERROR_OK) then
            begin
                if (iBuffer = TPCANBasic.PCAN_PARAMETER_ON) then
                    info := 'The channel option "Receive Status" is ON'
                else
                    info := 'The channel option "Receive Status" is OFF';
                IncludeTextMessage(info);
            end;
		end;

		// The Number of the CAN-Controller used by a PCAN-Channel
		//
	    6:
        begin                                              
		    stsResult := TPCANBasic.GetValue(m_PcanHandle, PCAN_CONTROLLER_NUMBER, PLongWord(@iBuffer), sizeof(iBuffer));
    		if(stsResult = PCAN_ERROR_OK) then
    		begin
    			info := Format('The CAN Controller number is %d', [iBuffer]);
	    		IncludeTextMessage(info);
		    end;
		end;

		// The activation status for the feature for tracing data will be retrieved
		//
	    7:
        begin
            stsResult := TPCANBasic.GetValue(m_PcanHandle, PCAN_TRACE_STATUS, PLongWord(@iBuffer), sizeof(iBuffer));
            if(stsResult = PCAN_ERROR_OK) then
            begin
                if (iBuffer = TPCANBasic.PCAN_PARAMETER_ON) then
                    info := 'The feature for tracing data is is ON'
                else
                    info := 'The feature for tracing data is is OFF';
                IncludeTextMessage(info);
            end;
		end;

		// The activation status of the Channel Identifying procedure will be retrieved
		//
	    8:
        begin
            stsResult := TPCANBasic.GetValue(m_PcanHandle, PCAN_CHANNEL_IDENTIFYING, PLongWord(@iBuffer), sizeof(iBuffer));
            if(stsResult = PCAN_ERROR_OK) then
            begin
                if (iBuffer = TPCANBasic.PCAN_PARAMETER_ON) then
                    info := 'The identification procedure of the selected channel is ON'
                else
                    info := 'The identification procedure of the selected channel is OFF';
                IncludeTextMessage(info);
            end;
    end;

		// The extra capabilities of a hardware will asked
		//
	    9:
        begin
            stsResult := TPCANBasic.GetValue(m_PcanHandle, PCAN_CHANNEL_FEATURES, PLongWord(@iBuffer), sizeof(iBuffer));
            if(stsResult = PCAN_ERROR_OK) then
            begin
                if (Byte(iBuffer) And Byte(TPCANBasic.FEATURE_FD_CAPABLE) <> 0) then
                    info := 'The channel does support Flexible Data-Rate (CAN-FD)'
                else
                    info := 'The channel DOESN''T SUPPORT Flexible Data-Rate (CAN-FD)';
                IncludeTextMessage(info);
                if (Byte(iBuffer) And Byte(TPCANBasic.FEATURE_DELAY_CAPABLE) <> 0) then
                    info := 'The channel does support an inter-frame delay for sending messages'
                else
                    info := 'The channel DOESN''T SUPPORT an inter-frame delay for sending messages';
                IncludeTextMessage(info);
                if (Byte(iBuffer) And Byte(TPCANBasic.FEATURE_IO_CAPABLE) <> 0) then
                    info := 'The channel does allow using I/O pins'
                else
                    info := 'The channel DOESN''T ALLOW using I/O pins';
                IncludeTextMessage(info);
            end;
         end;

		// The status of the bit rate adapting feature will be retrieved
		//
	    10:
        begin
            stsResult := TPCANBasic.GetValue(m_PcanHandle, PCAN_BITRATE_ADAPTING, PLongWord(@iBuffer), sizeof(iBuffer));
            if(stsResult = PCAN_ERROR_OK) then
            begin
                if (iBuffer = TPCANBasic.PCAN_PARAMETER_ON) then
                    info := 'The feature for bit rate adaptation is ON'
                else
                    info := 'The feature for bit rate adaptation is OFF';
                IncludeTextMessage(info);
            end;
        end;
        
		// The bitrate of the connected channel will be retrieved (BTR0-BTR1 value)
		//
	    11:
        begin
            stsResult := TPCANBasic.GetValue(m_PcanHandle, PCAN_BITRATE_INFO, PLongWord(@iBuffer), sizeof(iBuffer));
            if(stsResult = PCAN_ERROR_OK) then
            begin
                info := Format('The bit rate of the channel is %.4Xh', [iBuffer]);
                IncludeTextMessage(info);
            end;
        end;

		// The bitrate of the connected FD channel will be retrieved (String value)
		//
	    12:
        begin
            stsResult := TPCANBasic.GetValue(m_PcanHandle, PCAN_BITRATE_INFO_FD, strBuffer, 256);
            if(stsResult = PCAN_ERROR_OK) then
            begin
                IncludeTextMessage('The bit rate FD of the channel is represented by the following values:');
                strParts := TStringList.Create;
                strParts.Delimiter := ',';
                strParts.DelimitedText := strBuffer;
                for I := 0 to strParts.Count - 1 do
                    IncludeTextMessage('  * ' + strParts.Strings[i]);
                strParts.Free;
            end;
        end;

		// The nominal speed configured on the CAN bus
		//
	    13:
        begin
            stsResult := TPCANBasic.GetValue(m_PcanHandle, PCAN_BUSSPEED_NOMINAL, PLongWord(@iBuffer), sizeof(iBuffer));
            if(stsResult = PCAN_ERROR_OK) then
            begin
                info := Format('The nominal speed of the channel is %d bit/s', [iBuffer]);
                IncludeTextMessage(info);
            end;
        end;

		// The data speed configured on the CAN bus
		//
	    14:
        begin
            stsResult := TPCANBasic.GetValue(m_PcanHandle, PCAN_BUSSPEED_DATA, PLongWord(@iBuffer), sizeof(iBuffer));
            if(stsResult = PCAN_ERROR_OK) then
            begin
                info := Format('The data speed of the channel is %d bit/s', [iBuffer]);
                IncludeTextMessage(info);
            end;
        end;

		// The IP address of a LAN channel as string, in IPv4 format
		//
	    15:
        begin
            stsResult := TPCANBasic.GetValue(m_PcanHandle, PCAN_IP_ADDRESS, strBuffer, 256);
            if(stsResult = PCAN_ERROR_OK) then
            begin
                info := Format('The IP address of the channel is %s', [strBuffer]);
                IncludeTextMessage(info);
            end;
        end;

		// The running status of the LAN Service
		//
	    16:
        begin
            stsResult := TPCANBasic.GetValue(TPCANBasic.PCAN_NONEBUS, PCAN_LAN_SERVICE_STATUS, PLongWord(@iBuffer), sizeof(iBuffer));
            if(stsResult = PCAN_ERROR_OK) then
            begin
                if (iBuffer = TPCANBasic.SERVICE_STATUS_RUNNING) then
                    info := 'The LAN service is running'
                else
                    info := 'The service is NOT running';
                IncludeTextMessage(info);
            end;
        end;

		// The reception of Status frames
		//
	    17:
        begin
            stsResult := TPCANBasic.GetValue(m_PcanHandle, PCAN_ALLOW_STATUS_FRAMES, PLongWord(@iBuffer), sizeof(iBuffer));
            if(stsResult = PCAN_ERROR_OK) then
            begin
                if (iBuffer = TPCANBasic.PCAN_PARAMETER_ON) then
                    info := 'The reception of Status frames is enabled'
                else
                    info := 'The reception of Status frames is disabled';
                IncludeTextMessage(info);
            end;
        end;

		// The reception of RTR frames
		//
	    18:
        begin
            stsResult := TPCANBasic.GetValue(m_PcanHandle, PCAN_ALLOW_RTR_FRAMES, PLongWord(@iBuffer), sizeof(iBuffer));
            if(stsResult = PCAN_ERROR_OK) then
            begin
                if (iBuffer = TPCANBasic.PCAN_PARAMETER_ON) then
                    info := 'The reception of RTR frames is enabled'
                else
                    info := 'The reception of RTR frames is disabled';
                IncludeTextMessage(info);
            end;
        end;

		// The reception of Error frames
		//
	    19:
        begin
            stsResult := TPCANBasic.GetValue(m_PcanHandle, PCAN_ALLOW_ERROR_FRAMES, PLongWord(@iBuffer), sizeof(iBuffer));
            if(stsResult = PCAN_ERROR_OK) then
            begin
                if (iBuffer = TPCANBasic.PCAN_PARAMETER_ON) then
                    info := 'The reception of Error frames is enabled'
                else
                    info := 'The reception of Error frames is disabled';
                IncludeTextMessage(info);
            end;
        end;

		// The Interframe delay of an USB channel will be retrieved
		//
	    20:
        begin
		    stsResult := TPCANBasic.GetValue(m_PcanHandle, PCAN_INTERFRAME_DELAY, PLongWord(@iBuffer), sizeof(iBuffer));
    		if(stsResult = PCAN_ERROR_OK) then
    		begin
    			info := Format('The configured interframe delay is %d ms', [iBuffer]);
	    		IncludeTextMessage(info);
		    end;
		end;

		// The current parameter is invalid
		//
    else
        begin
            MessageBox(0, 'Wrong parameter code.', 'Error!',MB_ICONERROR);
		    exit;
        end;
	end;

	// If the function fail, an error message is shown
	//
	if(stsResult <> PCAN_ERROR_OK) then
		MessageBox(0, PChar(string(GetFormatedError(stsResult))), 'Error!',MB_ICONERROR);
end;

procedure TForm1.btnReadClick(Sender: TObject);
var
	stsResult : TPCANStatus;
begin
	// We execute the "Read" function of the PCANBasic
	//
  if m_IsFD then
    stsResult := ReadMessageFD()
  Else
	  stsResult := ReadMessage();

	if (stsResult <> PCAN_ERROR_OK) then
		// If an error occurred, an information message is included
		//
		IncludeTextMessage(GetFormatedError(stsResult));
end;

procedure TForm1.btnMsgClearClick(Sender: TObject);
begin
	// Clear Messages
	//
    try
        m_objpCS.Enter;

        lstMessages.Items.Clear();
        while(m_LastMsgsList.Count > 0) do
        begin
            MessageStatus(m_LastMsgsList.First()).Free;
            m_LastMsgsList.Delete(0);
        end;
    finally
        m_objpCS.Leave;
    end;
end;

procedure TForm1.btnWriteClick(Sender: TObject);
var
	stsResult : TPCANStatus;
begin
  // Send the message
  //
  if m_IsFD then  
    stsResult := WriteFrameFD()
  else
    stsResult := WriteFrame();

	// The Hardware was successfully sent
	//
	if (stsResult = PCAN_ERROR_OK) then
		IncludeTextMessage('Message was successfully SENT')
	// An error occurred.  We show the error.
	//
	else
		MessageBox(0, PChar(string(GetFormatedError(stsResult))), 'Error!',MB_ICONERROR);
end;

procedure TForm1.btnGetVersionsClick(Sender: TObject);
var
	stsResult : TPCANStatus;
	buffer : array[0..255] of AnsiChar;
	info : AnsiString;
	iPos : Integer;
begin
	// We get the vesion of the PCAN-Basic API
	//
	stsResult := TPCANBasic.GetValue(TPCANBAsic.PCAN_NONEBUS, PCAN_API_VERSION, buffer, 256);
	if (stsResult = PCAN_ERROR_OK) then
	begin
		info := Format('API Version: %s', [buffer]);
		IncludeTextMessage(info);
		// We get the driver version of the channel being used
		//
		stsResult := TPCANBasic.GetValue(m_PcanHandle, PCAN_CHANNEL_VERSION, buffer, 256);

		if (stsResult = PCAN_ERROR_OK) then
		begin
			IncludeTextMessage('Channel/Driver Version: ');

			// Because this information contains line control characters (several lines)
			// we split this also in several entries in the Information List-Box
			//
			info := buffer;
			while(info <> '') do
			begin
				iPos := Pos(#$A,info);
				if(iPos = 0) then
					iPos := Length(info);
				IncludeTextMessage('     * ' + Copy(info, 1, iPos));
				Delete(info, 1,iPos);
			end;
		end;
	end;

	// If the function fail, an error message is shown
	//
	if(stsResult <> PCAN_ERROR_OK) then
		MessageBox(0, PChar(string(GetFormatedError(stsResult))), 'Error!',MB_ICONERROR);
end;

procedure TForm1.btnInfoClearClick(Sender: TObject);
begin
	lbxInfo.Clear();
end;

procedure TForm1.btnStatusClick(Sender: TObject);
var
	status : TPCANStatus;
	errorName : AnsiString;
	info : AnsiString;
begin
	// Gets the current BUS status of a PCAN Channel.
	//
	status := TPCANBasic.GetStatus(m_PcanHandle);

	// Switch On Error Name
	//
	case status of
		PCAN_ERROR_INITIALIZE:
			errorName := 'PCAN_ERROR_INITIALIZE';

		PCAN_ERROR_BUSLIGHT:
			errorName := 'PCAN_ERROR_BUSLIGHT';

		PCAN_ERROR_BUSHEAVY: // PCAN_ERROR_BUSWARNING:
      if m_IsFD then
  			errorName := 'PCAN_ERROR_WARNING'
      else
    			errorName := 'PCAN_ERROR_BUSHEAVY';

		PCAN_ERROR_BUSPASSIVE:
			errorName := 'PCAN_ERROR_PASSIVE';

		PCAN_ERROR_BUSOFF:
			errorName := 'PCAN_ERROR_BUSOFF';

		PCAN_ERROR_OK:
			errorName := 'PCAN_ERROR_OK';

		else
			errorName := 'See Documentation';
    end;

	// Display Message
	//
	info := Format('Status: %s (%Xh)', [errorName, Integer(status)]);
	IncludeTextMessage(info);
end;

procedure TForm1.btnResetClick(Sender: TObject);
var
	stsResult : TPCANStatus;
begin
	// Resets the receive and transmit queues of a PCAN Channel.
	//
	stsResult := TPCANBasic.Reset(m_PcanHandle);

	// If it fails, a error message is shown
	//
	if (stsResult <> PCAN_ERROR_OK) then
		MessageBox(0, PChar(string(GetFormatedError(stsResult))), 'Error!',MB_ICONERROR)
	else
		IncludeTextMessage('Receive and transmit queues successfully reset');
end;

procedure TForm1.cbbBaudratesChange(Sender: TObject);
begin
    // We save the corresponding Baudrate enumeration
    // type value for every selected Baudrate from the
    // list.
    //
    Case cbbBaudrates.ItemIndex Of
        0:
            m_Baudrate:= PCAN_BAUD_1M;
        1:
            m_Baudrate:= PCAN_BAUD_800K;
        2:
            m_Baudrate:= PCAN_BAUD_500K;
        3:
            m_Baudrate:= PCAN_BAUD_250K;
        4:
            m_Baudrate:= PCAN_BAUD_125K;
        5:
            m_Baudrate:= PCAN_BAUD_100K;
        6:
            m_Baudrate:= PCAN_BAUD_95K;
        7:
            m_Baudrate:= PCAN_BAUD_83K;
        8:
            m_Baudrate:= PCAN_BAUD_50K;
        9:
            m_Baudrate:= PCAN_BAUD_47K;
        10:
            m_Baudrate:= PCAN_BAUD_33K;
        11:
            m_Baudrate:= PCAN_BAUD_20K;
        12:
            m_Baudrate:= PCAN_BAUD_10K;
        13:
            m_Baudrate:= PCAN_BAUD_5K;
        else
            m_Baudrate:= TPCANBaudrate(0);
    end;
end;

procedure TForm1.cbbChannelChange(Sender: TObject);
var
	bNonPnP : boolean;
	strTemp : AnsiString;
begin
	// Get the handle from the text being shown
	//
	strTemp := cbbChannel.Text;

	strTemp := Copy(strTemp, Pos('(',strTemp) + 1, 3);
  strTemp := StringReplace(strTemp, 'h',' ', [rfReplaceAll, rfIgnoreCase]);
  strTemp := Trim(strTemp);
	// Determines if the handle belong to a No Plug&Play hardware
	//
	m_PcanHandle := TPCANHandle(StrToInt('$'+strTemp));
	bNonPnP := m_PcanHandle <= TPCANBasic.PCAN_DNGBUS1;

	// Activates/deactivates configuration controls according with the
	// kind of hardware
	//
	cbbIO.Enabled := bNonPnP;
	cbbInterrupt.Enabled := bNonPnP;
	cbbHwType.Enabled := bNonPnP;
end;

procedure TForm1.cbbHwTypeChange(Sender: TObject);
begin
	Case cbbHwType.ItemIndex of
        0:
		    m_HwType := PCAN_TYPE_ISA;
	    1:
    		m_HwType := PCAN_TYPE_ISA_SJA;
	    2:
	    	m_HwType := PCAN_TYPE_ISA_PHYTEC;
	    3:
    		m_HwType := PCAN_TYPE_DNG;
	    4:
    		m_HwType := PCAN_TYPE_DNG_EPP;
	    5:
    		m_HwType := PCAN_TYPE_DNG_SJA;
	    6:
    		m_HwType := PCAN_TYPE_DNG_SJA_EPP;
    end;
end;

procedure TForm1.cbbParameterChange(Sender: TObject);
begin
	// Activates/deactivates controls according with the selected
	// PCAN-Basic parameter
	//
	rdbParamActive.Enabled := (cbbParameter.ItemIndex <> 0) AND (cbbParameter.ItemIndex <> 20);
	rdbParamInactive.Enabled := rdbParamActive.Enabled;
	txtDeviceIdOrDelay.Enabled := (NOT rdbParamActive.Enabled);
  if (cbbParameter.ItemIndex = 20) then
    laDeviceOrDelay.Caption := 'Delay (ms):'
  Else
    ladeviceOrDelay.Caption := 'Device ID:';
end;

procedure TForm1.chbFDClick(Sender: TObject);
var
	iMax : integer;
begin
	chbRemote.Enabled := NOT chbFD.Checked;
	chbBRS.Enabled := chbFD.Checked;
	if (NOT chbBRS.Enabled) then
		chbBRS.Checked := false;
  if chbFD.Checked then
  	iMax := 15
  Else
  	iMax := 8;
    
	nudLength.Max := iMax;
	txtLength.Text := IntToStr(nudLength.Position);
	EnableDisableDataFields(GetLengthFromDLC(nudLength.Position, chbFD.Checked));
end;

procedure TForm1.chbFilterExtClick(Sender: TObject);
begin
	// Updates the from and To ID-text according with the Message type
	//
	txtIdFromExit(txtIdFrom);
	txtIdFromExit(txtIdTo);
end;

procedure TForm1.chbRemoteClick(Sender: TObject);
begin
	// Show or Hide control according message is a RTR
	//
  if chbRemote.Checked then  
  	EnableDisableDataFields(0)
  Else
     EnableDisableDataFields(nudLength.Position);
     
	chbFD.Enabled := NOT chbRemote.Checked;
end;

procedure TForm1.chbShowPeriodClick(Sender: TObject);
var
    I : Integer;
    msgStsCurrentMessage : MessageStatus;
begin
    try
        m_objpCS.Enter;

        for I:=0 To m_LastMsgsList.Count-1 do
        begin
            msgStsCurrentMessage := MessageStatus(m_LastMsgsList.Items[I]);
            msgStsCurrentMessage.ShowingPeriod := chbShowPeriod.Checked;
        end;
    finally
        m_objpCS.Leave;
    end;
end;

procedure TForm1.chbCanFDClick(Sender: TObject);
begin
	m_IsFD := chbCanFD.Checked;

	cbbBaudrates.Visible := NOT m_IsFD;
	cbbHwType.Visible := NOT m_IsFD;
	cbbInterrupt.Visible := NOT m_IsFD;
	cbbIO.Visible := NOT m_IsFD;
	laBaudrate.Visible := NOT m_IsFD;
	laHwType.Visible := NOT m_IsFD;
	laIOPort.Visible := NOT m_IsFD;
	laInterrupt.Visible := NOT m_IsFD;

	txtBitrate.Visible := m_IsFD;
	laBitrate.Visible := m_IsFD;
	chbFD.Visible := m_IsFD;
	chbBRS.Visible := m_IsFD;

	if ((nudLength.Max > 8) AND NOT m_IsFD) then
		chbFD.Checked := false;
end;

procedure TForm1.chbExtendedClick(Sender: TObject);
begin
	// Updates the ID-text according with the Message type
	//
	txtIDExit(txtID);
end;

procedure TForm1.rdbTimerClick(Sender: TObject);
var
	radioBtn : TRadioButton;
begin

	radioBtn := Sender as TRadioButton;
	if((radioBtn <> nil) AND Not (radioBtn.Checked)) then
		exit;

	if(radioBtn.Name = 'rdbTimer') then
		m_ActiveReadingMode := 0;
	if(radioBtn.Name = 'rdbEvent') then
		m_ActiveReadingMode := 1;
	if(radioBtn.Name = 'rdbManual') then
		m_ActiveReadingMode := 2;

	ReadingModeChanged();
end;

procedure TForm1.nudLengthClick(Sender: TObject; Button: TUDBtnType);
var
    iLength: integer;
begin
	  // We enable so much TextBox Data fields as the length of the
    // message will be, that is the value of the UpDown control
    //
    iLength := GetLengthFromDLC(nudLength.Position, NOT chbFD.Checked);
    EnableDisableDataFields(iLength);
    laLength.Caption := Format('%d B.', [iLength]);
end;

procedure TForm1.txtIdFromExit(Sender: TObject);
var
	iTempMax, iTempValue : LongWord;
	IdBox : TEdit;
begin
	IdBox := Sender as TEdit;

	// Calculates the text length and Maximum ID value according
	// with the Frame Type
	//
    if(chbFilterExt.Checked) then
    	IdBox.MaxLength := 8
    else
        IdBox.MaxLength := 3;

    if(chbFilterExt.Checked) then
    	iTempMax := $1FFFFFFF
    else
        iTempMax := $7FF;

	// Adjusts the ID value to refresh
	//
	iTempValue := StrToInt('0x' + IdBox.Text);
	if(iTempValue < iTempMax) then
		iTempMax := iTempValue;

	// Refreshes the ID value
	//
	IdBox.Text := IntToHex(Integer(iTempMax),IdBox.MaxLength);
end;

procedure TForm1.txtIdFromKeyPress(Sender: TObject; var Key: Char);
begin
    // We convert the Character to its Upper case equivalent
    //
    Key := (UpperCase(Key))[1];

    // The Key is the Delete (Backspace) Key
    //
    if(Ord(Key) = 8)then
        exit;
    // The Key is a number between 0-9
    //
    if((Ord(Key) > 47)AND(Ord(Key) < 58))then
        exit;
    // The Key is a character between A-F
    //
    if((Ord(Key) > 64)AND(Ord(Key) < 71))then
        exit;

    // Is neither a number nor a character between A(a) and F(f)
    //
    Key := #0;
end;

procedure TForm1.txtDeviceIdOrDelayExit(Sender: TObject);
var
	iTemp : Int64;
begin

	// Checks the range of the given device ID
	//
	iTemp := StrToInt64(txtDeviceIdOrDelay.Text);
	if(iTemp > 4294967295) then
		txtDeviceIdOrDelay.Text := FloatToStr(4294967295);
end;

procedure TForm1.txtDeviceIdOrDelayKeyPress(Sender: TObject; var Key: Char);
begin
    // We convert the Character to its Upper case equivalent
    //
    Key := (UpperCase(Key))[1];

    // The Key is the Delete (Backspace) Key
    //
    if(Ord(Key) = 8)then
        exit;
    // The Key is a number between 0-9
    //
    if((Ord(Key) > 47)AND(Ord(Key) < 58))then
        exit;

    // Is neither a number nor a character between A(a) and F(f)
    //
    Key := #0;
end;

procedure TForm1.txtIDExit(Sender: TObject);
var
	iTempMax, iTempValue : LongWord;
begin
	// Calculates the text length and Maximum ID value according
	// with the Frame Type
	//
    if(chbExtended.Checked) then
    	txtID.MaxLength := 8
    else
        txtID.MaxLength := 3;

    if(chbExtended.Checked) then
    	iTempMax := $1FFFFFFF
    else
        iTempMax := $7FF;

	// Adjusts the ID value to refresh
	//
	iTempValue := StrToInt('0x' + txtID.Text);
	if(iTempValue < iTempMax) then
		iTempMax := iTempValue;

	// Refreshes the ID value
	//
	txtID.Text := IntToHex(Integer(iTempMax),txtID.MaxLength);
end;

procedure TForm1.txtData0Exit(Sender: TObject);
var
  CurrentEdit : TEdit;
begin
    if(AnsiString(Sender.ClassName) = 'TEdit')then
    begin
        CurrentEdit := TEdit(Sender);
        while(Length(CurrentEdit.Text) <> 2)do
            CurrentEdit.Text := ('0' + CurrentEdit.Text);
    end;
end;

end.
