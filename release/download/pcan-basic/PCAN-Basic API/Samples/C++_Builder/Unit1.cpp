//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

/// <summary>
/// Convert a CAN DLC value into the actual data length of the CAN/CAN-FD frame.
/// </summary>
/// <param name="dlc">A value between 0 and 15 (CAN and FD DLC range)</param>
/// <param name="isSTD">A value indicating if the msg is a standard CAN (FD Flag not checked)</param>
/// <returns>The length represented by the DLC</returns>
static int GetLengthFromDLC(int dlc, bool isSTD)
{
	if (dlc <= 8)
		return dlc;

	if (isSTD)
		return 8;

	switch (dlc)
	{
		case 9: return 12;
		case 10: return 16;
		case 11: return 20;
		case 12: return 24;
		case 13: return 32;
		case 14: return 48;
		case 15: return 64;
		default: return dlc;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Critical Section class
//
clsCritical::clsCritical(CRITICAL_SECTION *cs, bool createUnlocked, bool lockRecursively)
{
	m_objpCS = cs;
	m_dwLocked = -1;
	m_bDoRecursive = lockRecursively;
	m_dwOwnerThread = GetCurrentThreadId();

	if(!createUnlocked)
		Enter();
}	

clsCritical::~clsCritical()
{
	int iFail = (int)0x80000000;

	while(m_dwLocked >= 0)
		if(Leave() == iFail) 
			break;
}

int clsCritical::Enter()
{
	if(m_dwOwnerThread != GetCurrentThreadId())
		throw "class clsCritical: Thread cross-over error. ";

	try
	{
		if(m_bDoRecursive || (m_dwLocked == -1))
		{
			EnterCriticalSection(m_objpCS);
			InterlockedIncrement(&m_dwLocked);
		}
		return m_dwLocked;
	}
	catch(...)
	{	
		return 0x80000000;
	}
}

int clsCritical::Leave()
{
	if(m_dwOwnerThread != GetCurrentThreadId())
		throw "class clsCritical: Thread cross-over error. ";

	try
	{
		if(m_dwLocked >= 0)
		{
			LeaveCriticalSection(m_objpCS);
			InterlockedDecrement(&m_dwLocked);
			return m_dwLocked;
		}
		return -1;
	}
	catch(...)
	{
		return 0x80000000;
	}
}

bool clsCritical::IsLocked()
{
	return (m_dwLocked > -1);
}

int clsCritical::GetRecursionCount()
{
	return m_dwLocked;
}

//////////////////////////////////////////////////////////////////////////////////////////////
// MessageStatus class
//
MessageStatus::MessageStatus(TPCANMsgFD canMsg, TPCANTimestampFD canTimestamp, int listIndex)
{
    m_Msg = canMsg;
    m_TimeStamp = canTimestamp;
    m_oldTimeStamp = canTimestamp;
    m_iIndex = listIndex;
	m_Count = 1;
	m_bShowPeriod = true;
	m_bWasChanged = false;
}

void MessageStatus::Update(TPCANMsgFD canMsg, TPCANTimestampFD canTimestamp)
{
	m_Msg = canMsg;
	m_oldTimeStamp = m_TimeStamp;
	m_TimeStamp = canTimestamp;
	m_bWasChanged = true;
	m_Count += 1;
}

AnsiString MessageStatus::GetTypeString()
{
	AnsiString strTemp;

	// Add the new ListView Item with the type of the message
	//
    if ((m_Msg.MSGTYPE & PCAN_MESSAGE_STATUS) != 0)
		return "STATUS";

	if ((m_Msg.MSGTYPE & PCAN_MESSAGE_ERRFRAME) != 0)
		return "ERROR";

	if((m_Msg.MSGTYPE & PCAN_MESSAGE_EXTENDED) != 0)
		strTemp = "EXT";
	else
		strTemp = "STD";

	if((m_Msg.MSGTYPE & PCAN_MESSAGE_RTR) == PCAN_MESSAGE_RTR)
		strTemp = (strTemp + "/RTR");
	else
		if(m_Msg.MSGTYPE > PCAN_MESSAGE_EXTENDED)
		{
			strTemp += (" [ ");
			if (m_Msg.MSGTYPE & PCAN_MESSAGE_FD)
				strTemp += (" FD");
			if (m_Msg.MSGTYPE & PCAN_MESSAGE_BRS)
				strTemp += (" BRS");
			if (m_Msg.MSGTYPE & PCAN_MESSAGE_ESI)
				strTemp += (" ESI");
			strTemp += (" ]");
		}

	return strTemp;
}

AnsiString MessageStatus::GetIdString()
{
	// We format the ID of the message and show it
	//
	if((m_Msg.MSGTYPE & PCAN_MESSAGE_EXTENDED) != 0)
		return IntToHex((int)m_Msg.ID,8) + "h";
	else
		return IntToHex((int)m_Msg.ID,3) + "h";
}

AnsiString MessageStatus::GetDataString()
{
	AnsiString strTemp, strTemp2;

	strTemp = "";
	strTemp2 = "";

	if((m_Msg.MSGTYPE & PCAN_MESSAGE_RTR) == PCAN_MESSAGE_RTR)
		return "Remote Request";
	else
		for(int i=0; i < GetLengthFromDLC(m_Msg.DLC, !(m_Msg.MSGTYPE & PCAN_MESSAGE_FD)); i++)
		{
			strTemp = AnsiString::Format("%s %02X", ARRAYOFCONST((strTemp2, m_Msg.DATA[i])));
			strTemp2 = strTemp;
		}

	return strTemp2;
}

AnsiString MessageStatus::GetTimeString()
{
	double fTime;

	fTime = (m_TimeStamp / 1000.0);
	if (m_bShowPeriod)
		fTime -= (m_oldTimeStamp / 1000.0);
	return AnsiString::Format("%.1f", ARRAYOFCONST((fTime)));
}

void MessageStatus::SetShowingPeriod(bool value)
{
    if (m_bShowPeriod ^ value)
    {
		m_bShowPeriod = value;
		m_bWasChanged = true;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	// Initialize all
	//
	InitializeControls();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	// Release Hardware if needed
	//
	if(btnRelease->Enabled)
		btnRelease->Click();

	// Close the event
	CloseHandle(m_hEvent);
			
	//Free Ressources
	//
	delete m_objPCANBasic;

	// (Protected environment)
	//
	{
		clsCritical locker(m_objpCS);
		
		while(m_LastMsgsList->Count)
		{
			delete m_LastMsgsList->First();
			m_LastMsgsList->Delete(0);
		}
		delete m_LastMsgsList;
	}

	// Uninitialize the Critical Section
	//
	FinalizeProtection();
}
//---------------------------------------------------------------------------

void TForm1::InitializeControls(void)
{
	// Initialize the Critical Section
	//
	InitializeProtection();

	// Creates an array with all possible PCAN-Channels
	//
	m_HandlesArray[0] = PCAN_ISABUS1;
	m_HandlesArray[1] = PCAN_ISABUS2;
	m_HandlesArray[2] = PCAN_ISABUS3;
	m_HandlesArray[3] = PCAN_ISABUS4;
	m_HandlesArray[4] = PCAN_ISABUS5;
	m_HandlesArray[5] = PCAN_ISABUS6;
	m_HandlesArray[6] = PCAN_ISABUS7;
	m_HandlesArray[7] = PCAN_ISABUS8;
	m_HandlesArray[8] = PCAN_DNGBUS1;
	m_HandlesArray[9] = PCAN_PCIBUS1;
	m_HandlesArray[10] = PCAN_PCIBUS2;
	m_HandlesArray[11] = PCAN_PCIBUS3;
	m_HandlesArray[12] = PCAN_PCIBUS4;
	m_HandlesArray[13] = PCAN_PCIBUS5;
	m_HandlesArray[14] = PCAN_PCIBUS6;
	m_HandlesArray[15] = PCAN_PCIBUS7;
	m_HandlesArray[16] = PCAN_PCIBUS8;
	m_HandlesArray[17] = PCAN_PCIBUS9;
	m_HandlesArray[18] = PCAN_PCIBUS10;
	m_HandlesArray[19] = PCAN_PCIBUS11;
	m_HandlesArray[20] = PCAN_PCIBUS12;
	m_HandlesArray[21] = PCAN_PCIBUS13;
	m_HandlesArray[22] = PCAN_PCIBUS14;
	m_HandlesArray[23] = PCAN_PCIBUS15;
	m_HandlesArray[24] = PCAN_PCIBUS16;
	m_HandlesArray[25] = PCAN_USBBUS1;
	m_HandlesArray[26] = PCAN_USBBUS2;
	m_HandlesArray[27] = PCAN_USBBUS3;
	m_HandlesArray[28] = PCAN_USBBUS4;
	m_HandlesArray[29] = PCAN_USBBUS5;
	m_HandlesArray[30] = PCAN_USBBUS6;
	m_HandlesArray[31] = PCAN_USBBUS7;
	m_HandlesArray[32] = PCAN_USBBUS8;
	m_HandlesArray[33] = PCAN_USBBUS9;
	m_HandlesArray[34] = PCAN_USBBUS10;
	m_HandlesArray[35] = PCAN_USBBUS11;
	m_HandlesArray[36] = PCAN_USBBUS12;
	m_HandlesArray[37] = PCAN_USBBUS13;
	m_HandlesArray[38] = PCAN_USBBUS14;
	m_HandlesArray[39] = PCAN_USBBUS15;
	m_HandlesArray[40] = PCAN_USBBUS16;
	m_HandlesArray[41] = PCAN_PCCBUS1;
	m_HandlesArray[42] = PCAN_PCCBUS2;
	m_HandlesArray[43] = PCAN_LANBUS1;
	m_HandlesArray[44] = PCAN_LANBUS2;
	m_HandlesArray[45] = PCAN_LANBUS3;
	m_HandlesArray[46] = PCAN_LANBUS4;
	m_HandlesArray[47] = PCAN_LANBUS5;
	m_HandlesArray[48] = PCAN_LANBUS6;
	m_HandlesArray[49] = PCAN_LANBUS7;
	m_HandlesArray[50] = PCAN_LANBUS8;
	m_HandlesArray[51] = PCAN_LANBUS9;
	m_HandlesArray[52] = PCAN_LANBUS10;
	m_HandlesArray[53] = PCAN_LANBUS11;
	m_HandlesArray[54] = PCAN_LANBUS12;
	m_HandlesArray[55] = PCAN_LANBUS13;
	m_HandlesArray[56] = PCAN_LANBUS14;
	m_HandlesArray[57] = PCAN_LANBUS15;
	m_HandlesArray[58] = PCAN_LANBUS16;

	// We set the variable for the current
	// PCAN Basic Class instance to use it
	//
	m_objPCANBasic = new PCANBasicClass();

	// As defautl, normal CAN hardware is used
	//
	m_IsFD = false;

	// Create a list to store the displayed messages
	//
	m_LastMsgsList = new TList();

	// Create Event to use Received-event
	//
	m_hEvent = CreateEvent(NULL, FALSE, FALSE, "");

	// Set the Read-thread variable to null
	//
	m_hThread = NULL;

	// We set the variable to know which reading mode is
	// currently selected (Timer by default)
	//
	m_ActiveReadingMode = 0;

	// Prepares the PCAN-Basic's debug-Log file
	//
	FillComboBoxData();

	// Init log parameters
	ConfigureLogFile();

	// Set default connection status
	//
	SetConnectionStatus(false);
}
//---------------------------------------------------------------------------
void TForm1::InitializeProtection()
{
	m_objpCS = new CRITICAL_SECTION();
	InitializeCriticalSection(m_objpCS);
}

//---------------------------------------------------------------------------
void TForm1::FinalizeProtection()
{
	try
	{
		DeleteCriticalSection(m_objpCS);
		delete m_objpCS;
		m_objpCS = NULL;
	}
	catch(...)
	{
		throw;
	}
}
//---------------------------------------------------------------------------

void TForm1::FillComboBoxData()
{
	// Channels will be check
	//
	btnHwRefresh->Click();

    // FD Bitrate: 
    //      Arbitration: 1 Mbit/sec 
    //      Data: 2 Mbit/sec
	//
	txtBitrate->Text =   "f_clock_mhz=20, nom_brp=5, nom_tseg1=2, nom_tseg2=1, nom_sjw=1, data_brp=2, data_tseg1=3, data_tseg2=1, data_sjw=1";
	
	// TPCANBaudrate
	//
	cbbBaudrates->ItemIndex =2; // 500 K
	cbbBaudratesChange(cbbBaudrates);

	// Hardware Type for no plugAndplay hardware
	//
	cbbHwType->ItemIndex = 0;
	cbbHwTypeChange(cbbHwType);

	// Interrupt for no plugAndplay hardware
	//
	cbbInterrupt->ItemIndex = 0;

	// IO Port for no plugAndplay hardware
	//
	cbbIO->ItemIndex = 0;

	// Parameters for GetValue and SetValue function calls
	//
	cbbParameter->ItemIndex = 0;
	cbbParameterChange(cbbParameter);
}
//---------------------------------------------------------------------------

AnsiString TForm1::FormatChannelName(TPCANHandle handle, bool isFD)
{
	AnsiString strName;
	BYTE byChannel;

	// Gets the owner device and channel for a
	// PCAN-Basic handle
	//
	if(handle < 0x100)
		byChannel = (BYTE)(handle) & 0xF;
	else
		byChannel = (BYTE)(handle) & 0xFF;

	// Constructs the PCAN-Basic Channel name and return it
	//
	return Format(isFD ? "%s:FD %d (%Xh)" : "%s %d (%Xh)", ARRAYOFCONST((GetTPCANHandleName(handle), byChannel, handle)));
}
//---------------------------------------------------------------------------

AnsiString TForm1::FormatChannelName(TPCANHandle handle)
{
	return FormatChannelName(handle, false);
}

//---------------------------------------------------------------------------
AnsiString TForm1::GetTPCANHandleName(TPCANHandle handle)
{
	AnsiString result = "PCAN_NONE";

	switch(handle)
	{
		case PCAN_ISABUS1:
		case PCAN_ISABUS2:
		case PCAN_ISABUS3:
		case PCAN_ISABUS4:
		case PCAN_ISABUS5:
		case PCAN_ISABUS6:
		case PCAN_ISABUS7:
		case PCAN_ISABUS8:
			result = "PCAN_ISA";
			break;

		case PCAN_DNGBUS1:
			result = "PCAN_DNG";
			break;

		case PCAN_PCIBUS1:
		case PCAN_PCIBUS2:
		case PCAN_PCIBUS3:
		case PCAN_PCIBUS4:
		case PCAN_PCIBUS5:
		case PCAN_PCIBUS6:
		case PCAN_PCIBUS7:
		case PCAN_PCIBUS8:
		case PCAN_PCIBUS9:
		case PCAN_PCIBUS10:
		case PCAN_PCIBUS11:
		case PCAN_PCIBUS12:
		case PCAN_PCIBUS13:
		case PCAN_PCIBUS14:
		case PCAN_PCIBUS15:
		case PCAN_PCIBUS16:
			result = "PCAN_PCI";
			break;

		case PCAN_USBBUS1:
		case PCAN_USBBUS2:
		case PCAN_USBBUS3:
		case PCAN_USBBUS4:
		case PCAN_USBBUS5:
		case PCAN_USBBUS6:
		case PCAN_USBBUS7:
		case PCAN_USBBUS8:
		case PCAN_USBBUS9:
		case PCAN_USBBUS10:
		case PCAN_USBBUS11:
		case PCAN_USBBUS12:
		case PCAN_USBBUS13:
		case PCAN_USBBUS14:
		case PCAN_USBBUS15:
		case PCAN_USBBUS16:
			result = "PCAN_USB";
			break;

		case PCAN_PCCBUS1:
		case PCAN_PCCBUS2:
			result = "PCAN_PCC";
			break;

		case PCAN_LANBUS1:
		case PCAN_LANBUS2:
		case PCAN_LANBUS3:
		case PCAN_LANBUS4:
		case PCAN_LANBUS5:
		case PCAN_LANBUS6:
		case PCAN_LANBUS7:
		case PCAN_LANBUS8:
		case PCAN_LANBUS9:
		case PCAN_LANBUS10:
		case PCAN_LANBUS11:
		case PCAN_LANBUS12:
		case PCAN_LANBUS13:
		case PCAN_LANBUS14:
		case PCAN_LANBUS15:
		case PCAN_LANBUS16:
			result = "PCAN_LAN";
			break; 
	}
	return result;
}
//---------------------------------------------------------------------------

void TForm1::ConfigureLogFile()
{
	int iBuffer;

	// Sets the mask to catch all events
	//
	iBuffer = LOG_FUNCTION_ALL;

	// Configures the log file.
	// NOTE: The Log capability is to be used with the NONEBUS Handle. Other handle than this will
	// cause the function fail.
	//
	m_objPCANBasic->SetValue(PCAN_NONEBUS, PCAN_LOG_CONFIGURE, (void*)&iBuffer, sizeof(iBuffer));
}
//---------------------------------------------------------------------------

void TForm1::ConfigureTraceFile()
{
	int iBuffer;
	TPCANStatus stsResult;

    // Configure the maximum size of a trace file to 5 megabytes
    //
	iBuffer = 5;
	stsResult = m_objPCANBasic->SetValue(m_PcanHandle, PCAN_TRACE_SIZE, (void*)&iBuffer, sizeof(iBuffer));
	if (stsResult != PCAN_ERROR_OK)
		IncludeTextMessage(GetFormatedError(stsResult));

    // Configure the way how trace files are created: 
    // * Standard name is used
    // * Existing file is ovewritten, 
    // * Only one file is created.
    // * Recording stopts when the file size reaches 5 megabytes.
    //
	iBuffer = TRACE_FILE_SINGLE | TRACE_FILE_OVERWRITE;
	stsResult = m_objPCANBasic->SetValue(m_PcanHandle, PCAN_TRACE_CONFIGURE, (void*)&iBuffer, sizeof(iBuffer));
	if (stsResult != PCAN_ERROR_OK)
		IncludeTextMessage(GetFormatedError(stsResult));
}
//---------------------------------------------------------------------------

void TForm1::SetConnectionStatus(bool bConnected)
{
	// Buttons
	//
	btnInit->Enabled = !bConnected;
	btnRead->Enabled = (bConnected && rdbManual->Checked);
	btnWrite->Enabled = bConnected;
	btnRelease->Enabled = bConnected;
	btnFilterApply->Enabled = bConnected;
	btnFilterQuery->Enabled = bConnected;
	btnGetVersions->Enabled = bConnected;
	btnHwRefresh->Enabled = !bConnected;
	btnStatus->Enabled = bConnected;
	btnReset->Enabled = bConnected;

	// ComboBoxs
	//
	cbbBaudrates->Enabled = !bConnected;
	cbbChannel->Enabled = !bConnected;
	cbbHwType->Enabled = !bConnected;
	cbbIO->Enabled = !bConnected;
	cbbInterrupt->Enabled = !bConnected;

	// Check-Buttons
    //
    chbCanFD->Enabled = !bConnected;	

	// Hardware configuration and read mode
	//
	if (!bConnected)
		cbbChannelChange(cbbChannel);
	else
		ReadingModeChanged();

	// Display messages in grid
	//
	tmrDisplay->Enabled = bConnected;
}
//---------------------------------------------------------------------------

AnsiString TForm1::GetFormatedError(TPCANStatus error)
{
	TPCANStatus status;
	char buffer[256];
	AnsiString result;

	memset(buffer,'\0',256);
	// Gets the text using the GetErrorText API function
	// If the function success, the translated error is returned. If it fails,
	// a text describing the current error is returned.
	//
	status = m_objPCANBasic->GetErrorText(error, 0, buffer);
	if(status != PCAN_ERROR_OK)
		result = Format("An error ocurred. Error-code's text (%Xh) couldn't be retrieved", ARRAYOFCONST((error)));
	else
		result = buffer;
	return result;
}
//---------------------------------------------------------------------------

void TForm1::IncludeTextMessage(AnsiString strMsg)
{
	// Inserts a message in the Info box and focuses it
	//
	lbxInfo->Items->Add(strMsg);
	lbxInfo->ItemIndex = lbxInfo->Items->Count-1;
}
//---------------------------------------------------------------------------

bool TForm1::GetFilterStatus(int* status)
{
	TPCANStatus stsResult;

	// Tries to get the status of the filter for the current connected hardware
	//
	stsResult = m_objPCANBasic->GetValue(m_PcanHandle, PCAN_MESSAGE_FILTER, (void*)status, sizeof(int));

	// If it fails, a error message is shown
	//
	if (stsResult != PCAN_ERROR_OK)
	{
		::MessageBox(NULL, GetFormatedError(stsResult).c_str(), "Error!",MB_ICONERROR);
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------

void TForm1::InsertMsgEntry(TPCANMsgFD NewMsg, TPCANTimestampFD timeStamp)
{
	MessageStatus *msgStsCurrentMsg;
	TListItem *CurrentItem;

	// (Protected environment)
	//
	{
		clsCritical locker(m_objpCS);

		// We add this status in the last message list
		//
		msgStsCurrentMsg = new MessageStatus(NewMsg, timeStamp, lstMessages->Items->Count);
		msgStsCurrentMsg->ShowingPeriod = chbShowPeriod->Checked;
		m_LastMsgsList->Add(msgStsCurrentMsg);

		// Add the new ListView Item with the Type of the message
		//
		CurrentItem = lstMessages->Items->Add();
		CurrentItem->Caption = msgStsCurrentMsg->TypeString;

		// We set the ID of the message
		//
		CurrentItem->SubItems->Add(msgStsCurrentMsg->IdString);
		// We set the length of the Message
		//
		CurrentItem->SubItems->Add(IntToStr(GetLengthFromDLC(NewMsg.DLC, !(NewMsg.MSGTYPE & PCAN_MESSAGE_FD))));
		// we set the message count message (this is the First, so count is 1)
		//
		CurrentItem->SubItems->Add(IntToStr(msgStsCurrentMsg->Count));
		// Add timestamp information
		//
		CurrentItem->SubItems->Add(msgStsCurrentMsg->TimeString);
		// We set the data of the message.
		//
		CurrentItem->SubItems->Add(msgStsCurrentMsg->DataString);		
	}
}
//---------------------------------------------------------------------------

void TForm1::DisplayMessages()
{
	TListItem *CurrentItem;
	MessageStatus *msgStatus;

    // We search if a message (Same ID and Type) is 
    // already received or if this is a new message
	// (in a protected environment)
	//
	{
		clsCritical locker(m_objpCS);
		for(int i=0; i < m_LastMsgsList->Count; i++)
		{
			msgStatus = (MessageStatus*)m_LastMsgsList->Items[i];

			if (msgStatus->MarkedAsUpdated)
			{
				msgStatus->MarkedAsUpdated = false;
				CurrentItem = lstMessages->Items->Item[msgStatus->Position];

				CurrentItem->SubItems->Strings[1] = IntToStr(GetLengthFromDLC(msgStatus->CANMsg.DLC, !(msgStatus->CANMsg.MSGTYPE & PCAN_MESSAGE_FD)));
				CurrentItem->SubItems->Strings[2] = IntToStr(msgStatus->Count);
				CurrentItem->SubItems->Strings[3] = msgStatus->TimeString;
				CurrentItem->SubItems->Strings[4] = msgStatus->DataString;
			}
		}
	}
}
//---------------------------------------------------------------------------

TPCANStatus TForm1::ReadMessageFD()
{
	TPCANMsgFD CANMsg;
	TPCANTimestampFD CANTimeStamp;
	TPCANStatus stsResult;

	// We execute the "Read" function of the PCANBasic
	//
	stsResult = m_objPCANBasic->ReadFD(m_PcanHandle, &CANMsg, &CANTimeStamp);
	if (stsResult != PCAN_ERROR_QRCVEMPTY)
		// We process the received message
		//
		ProcessMessage(CANMsg, CANTimeStamp);

	return stsResult;
}
//---------------------------------------------------------------------------

TPCANStatus TForm1::ReadMessage()
{
	TPCANMsg CANMsg;
	TPCANTimestamp CANTimeStamp;
	TPCANStatus stsResult;

	// We execute the "Read" function of the PCANBasic
	//
	stsResult = m_objPCANBasic->Read(m_PcanHandle, &CANMsg, &CANTimeStamp);
	if (stsResult != PCAN_ERROR_QRCVEMPTY)
		// We process the received message
		//
		ProcessMessage(CANMsg, CANTimeStamp);

	return stsResult;
}
//---------------------------------------------------------------------------

void TForm1::ReadMessages()
{
	TPCANStatus stsResult;

	// We read at least one time the queue looking for messages.
	// If a message is found, we look again trying to find more.
	// If the queue is empty or an error occurr, we get out from
	// the dowhile statement.
	//
	do
	{
		stsResult = m_IsFD ? ReadMessageFD() : ReadMessage();
		if (stsResult == PCAN_ERROR_ILLOPERATION)
			break;
	} while (btnRelease->Enabled && (!(stsResult & PCAN_ERROR_QRCVEMPTY)));
}
//---------------------------------------------------------------------------

void TForm1::ProcessMessage(TPCANMsgFD theMsg, TPCANTimestampFD itsTimeStamp)
{
	MessageStatus *msg;

	// We search if a message (Same ID and Type) is
	// already received or if this is a new message
	//
	{
		clsCritical locker(m_objpCS);
		for(int i=0; i < m_LastMsgsList->Count; i++)
		{
			msg = (MessageStatus*)m_LastMsgsList->Items[i];
			if((msg->CANMsg.ID == theMsg.ID) && (msg->CANMsg.MSGTYPE == theMsg.MSGTYPE))
			{
				// Modify the message and exit
				//
				msg->Update(theMsg, itsTimeStamp);
				return;
			}
		}
		// Message not found. It will created
		//
		InsertMsgEntry(theMsg, itsTimeStamp);
	}
}
//---------------------------------------------------------------------------

void TForm1::ProcessMessage(TPCANMsg theMsg, TPCANTimestamp itsTimeStamp)
{
	TPCANMsgFD newMsg;
	TPCANTimestampFD newTimestamp;

	newMsg = TPCANMsgFD();
	newMsg.ID = theMsg.ID;
	newMsg.DLC = theMsg.LEN;
	for (int i = 0; i < ((theMsg.LEN > 8) ? 8 : theMsg.LEN); i++)
		newMsg.DATA[i] = theMsg.DATA[i];
	newMsg.MSGTYPE = theMsg.MSGTYPE;

	newTimestamp = (itsTimeStamp.micros + 1000 * itsTimeStamp.millis + 0x100000000 * 1000 * itsTimeStamp.millis_overflow);
	ProcessMessage(newMsg, newTimestamp);
}
//---------------------------------------------------------------------------

void TForm1::ReadingModeChanged()
{
	if (!btnRelease->Enabled)
		return;

	switch(m_ActiveReadingMode)
	{
		case 0: 	// If active reading mode is By Timer
			// Terminate Read Thread if it exists
			//
			if(m_hThread != NULL)
			{
				TerminateThread(m_hThread, -1000);
				m_hThread = NULL;
			}
			// We start to read
			//
			tmrRead->Enabled = true;
			break;
		case 1: 	// If active reading mode is By Event
			// We stop to read from the CAN queue
			//
			tmrRead->Enabled = false;

			// Create Reading Thread ....
			//
			m_hThread = CreateThread(NULL, NULL, TForm1::CallCANReadThreadFunc, (LPVOID)this, NULL, NULL);

			if(m_hThread == NULL)
				::MessageBox(NULL,"Create CANRead-Thread failed","Error!",MB_ICONERROR);
			break;
		default:	// If active reading mode is Manual
			// Terminate Read Thread if it exists
			//
			if(m_hThread != NULL)
			{
				TerminateThread(m_hThread, -1000);
				m_hThread = NULL;
			}
			// We enable the button for read
			//
			tmrRead->Enabled = false;
			btnRead->Enabled = (btnRelease->Enabled && rdbManual->Checked);
			break;
	}
}
//---------------------------------------------------------------------------

DWORD WINAPI TForm1::CallCANReadThreadFunc(LPVOID lpParam)
{
	// Cast lpParam argument to PCANBasicExampleDlg*
	//
	TForm1* dialog = (TForm1*)lpParam;

	// Call TForm1 Thread member function
	//
	return dialog->CANReadThreadFunc();
}
//---------------------------------------------------------------------------

DWORD TForm1::CANReadThreadFunc()
{
	TPCANStatus stsResult;
	DWORD result, dwTemp;

	// Sets the handle of the Receive-Event.
	//
	stsResult = m_objPCANBasic->SetValue(m_PcanHandle, PCAN_RECEIVE_EVENT ,&m_hEvent, sizeof(m_hEvent));

	// If it fails, a error message is shown
	//
	if (stsResult != PCAN_ERROR_OK)
	{
		::MessageBox(NULL, GetFormatedError(stsResult).c_str(), "Error!",MB_ICONERROR);
		return 1;
	}

	// While this mode is selected
	//
	while(rdbEvent->Checked)
	{
		//Wait for CAN Data...
		result = WaitForSingleObject(m_hEvent, INFINITE);

		if (result == WAIT_OBJECT_0)
			ReadMessages();
	}

	// Resets the Event-handle configuration
	//
	dwTemp = 0;
	m_objPCANBasic->SetValue(m_PcanHandle, PCAN_RECEIVE_EVENT ,&dwTemp, sizeof(dwTemp));

	return 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tmrReadTimer(TObject *Sender)
{
	ReadMessages();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnHwRefreshClick(TObject *Sender)
{
	int iBuffer;
	TPCANStatus stsResult;
	bool isFD;

	// Clears the Channel combioBox and fill it againa with 
	// the PCAN-Basic handles for no-Plug&Play hardware and
	// the detected Plug&Play hardware
	//
	cbbChannel->Items->Clear();
	for (int i = 0; i < (int)(sizeof(m_HandlesArray) /sizeof(TPCANHandle)) ; i++)
	{
		// Includes all no-Plug&Play Handles
		//
		if (m_HandlesArray[i] <= PCAN_DNGBUS1)
			cbbChannel->Items->Add(FormatChannelName(m_HandlesArray[i]));
		else
		{
			// Checks for a Plug&Play Handle and, according with the return value, includes it
			// into the list of available hardware channels.
			//
			stsResult = m_objPCANBasic->GetValue((TPCANHandle)m_HandlesArray[i], PCAN_CHANNEL_CONDITION, (void*)&iBuffer, sizeof(iBuffer));
			if ((stsResult == PCAN_ERROR_OK) && ((iBuffer & PCAN_CHANNEL_AVAILABLE) == PCAN_CHANNEL_AVAILABLE))
			{
				stsResult = m_objPCANBasic->GetValue((TPCANHandle)m_HandlesArray[i], PCAN_CHANNEL_FEATURES, (void*)&iBuffer, sizeof(iBuffer));
				isFD = (stsResult == PCAN_ERROR_OK) && (iBuffer & FEATURE_FD_CAPABLE);
				cbbChannel->Items->Add(FormatChannelName(m_HandlesArray[i], isFD));
			}
		}
	}

	// Select Last One
	//
	cbbChannel->ItemIndex = cbbChannel->Items->Count - 1;
	cbbChannelChange(cbbChannel);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnInitClick(TObject *Sender)
{
	TPCANStatus stsResult;
	int selectedIO;
	int selectedInterrupt;

	// Parse IO and Interrupt
	//
	selectedIO = StrToInt("0x"+cbbIO->Text);
	selectedInterrupt = StrToInt("0x"+cbbInterrupt->Text);

	// Connects a selected PCAN-Basic channel
	//
	if(m_IsFD)
		stsResult = m_objPCANBasic->InitializeFD(m_PcanHandle, AnsiString(txtBitrate->Text).c_str());
	else
		stsResult = m_objPCANBasic->Initialize(m_PcanHandle, m_Baudrate, m_HwType, selectedIO, selectedInterrupt);

	if (stsResult != PCAN_ERROR_OK)
		if (stsResult != PCAN_ERROR_CAUTION)
			::MessageBox(NULL, GetFormatedError(stsResult).c_str(), "Error!",MB_ICONERROR);
		else
		{
			IncludeTextMessage("******************************************************");
			IncludeTextMessage("The bitrate being used is different than the given one");
			IncludeTextMessage("******************************************************");			
			stsResult = PCAN_ERROR_OK;
        }
	else
		// Prepares the PCAN-Basic's PCAN-Trace file
		//
		ConfigureTraceFile();

	// Sets the connection status of the main-form
	//
	SetConnectionStatus(stsResult == PCAN_ERROR_OK); 
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnReleaseClick(TObject *Sender)
{
	// Terminate Read Thread if it exists
	//
	if(m_hThread != NULL)
	{
		TerminateThread(m_hThread, 1000);
		m_hThread = NULL;
	}

	// We stop to read from the CAN queue
	//
	tmrRead->Enabled = false;

	// Releases a current connected PCAN-Basic channel
	//
	m_objPCANBasic->Uninitialize(m_PcanHandle);

	// Sets the connection status of the main-form
	//
	SetConnectionStatus(false);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnFilterApplyClick(TObject *Sender)
{
	int iBuffer;
	AnsiString info;
	TPCANStatus stsResult;

	// Gets the current status of the message filter
	//
	if (!GetFilterStatus(&iBuffer))
		return;

	// Configures the message filter for a custom range of messages
	//
	if (rdbFilterCustom->Checked)
	{
		// Sets the custom filter
		//
		stsResult = m_objPCANBasic->FilterMessages(m_PcanHandle, StrToInt("0x"+txtIdFrom->Text), StrToInt("0x"+txtIdTo->Text), chbFilterExt->Checked ? PCAN_MODE_EXTENDED : PCAN_MODE_STANDARD);
		// If success, an information message is written, if it is not, an error message is shown
		//
		if (stsResult == PCAN_ERROR_OK)
		{
			info = Format("The filter was customized. IDs from {0x%s} to {0x%s} will be received", ARRAYOFCONST((txtIdFrom->Text,txtIdTo->Text)));
			IncludeTextMessage(info);
		}
		else
			::MessageBox(NULL, GetFormatedError(stsResult).c_str(), "Error!",MB_ICONERROR);

		return;
	}

	// The filter will be full opened or complete closed
	//
	if (rdbFilterClose->Checked)
		iBuffer = PCAN_FILTER_CLOSE;
	else
		iBuffer = PCAN_FILTER_OPEN;

	// The filter is configured
	//
	stsResult = m_objPCANBasic->SetValue(m_PcanHandle, PCAN_MESSAGE_FILTER, (void*)&iBuffer, sizeof(int));

	// If success, an information message is written, if it is not, an error message is shown
	//
	if (stsResult == PCAN_ERROR_OK)
	{
		info = Format("The filter was successfully %s", ARRAYOFCONST((rdbFilterClose->Checked ? "closed." : "opened.")));
		IncludeTextMessage(info);
	}
	else
		::MessageBox(NULL, GetFormatedError(stsResult).c_str(), "Error!",MB_ICONERROR);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnFilterQueryClick(TObject *Sender)
{
	int iBuffer;

	// Queries the current status of the message filter
	//
	if (GetFilterStatus(&iBuffer))
	{
		switch(iBuffer)
		{
			// The filter is closed
			//
		case PCAN_FILTER_CLOSE:
			IncludeTextMessage("The Status of the filter is: closed.");
			break;
			// The filter is fully opened
			//
		case PCAN_FILTER_OPEN:
			IncludeTextMessage("The Status of the filter is: full opened.");
			break;
			// The filter is customized
			//
		case PCAN_FILTER_CUSTOM:
			IncludeTextMessage("The Status of the filter is: customized.");
			break;
			// The status of the filter is undefined. (Should never happen)
			//
		default:
			IncludeTextMessage("The Status of the filter is: Invalid.");
			break;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnParameterSetClick(TObject *Sender)
{
	TPCANStatus stsResult;
	unsigned int iBuffer;
	AnsiString info;
	TCHAR szDirectory[MAX_PATH] = "";
	bool bActivate;

	bActivate = rdbParamActive->Checked;

	// Sets a PCAN-Basic parameter value
	//
	switch (cbbParameter->ItemIndex)
	{
		// The Device-Number of an USB channel will be set
		//
	case 0:
		iBuffer = StrToInt(txtDeviceIdOrDelay->Text);
		stsResult = m_objPCANBasic->SetValue(m_PcanHandle, PCAN_DEVICE_NUMBER, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
			IncludeTextMessage("The desired Device-Number was successfully configured");
		break;

		// The 5 Volt Power feature of a PC-card or USB will be set
		//
	case 1:
		iBuffer = bActivate ? PCAN_PARAMETER_ON : PCAN_PARAMETER_OFF;
		stsResult = m_objPCANBasic->SetValue(m_PcanHandle, PCAN_5VOLTS_POWER, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The USB/PC-Card 5 power was successfully %s", ARRAYOFCONST((bActivate ? "activated" : "deactivated")));
			IncludeTextMessage(info);
		}
		break;

		// The feature for automatic reset on BUS-OFF will be set
		//
	case 2:
		iBuffer = bActivate ? PCAN_PARAMETER_ON : PCAN_PARAMETER_OFF;
		stsResult = m_objPCANBasic->SetValue(m_PcanHandle, PCAN_BUSOFF_AUTORESET, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The automatic-reset on BUS-OFF was successfully %s", ARRAYOFCONST((bActivate ? "activated" : "deactivated")));
			IncludeTextMessage(info);
		}
		break;

		// The CAN option "Listen Only" will be set
		//
	case 3:
		iBuffer = bActivate ? PCAN_PARAMETER_ON : PCAN_PARAMETER_OFF;
		stsResult = m_objPCANBasic->SetValue(m_PcanHandle, PCAN_LISTEN_ONLY, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The CAN option \"Listen Only\" was successfully %s", ARRAYOFCONST((bActivate ? "activated" : "deactivated")));
			IncludeTextMessage(info);
		}
		break;

		// The feature for logging debug-information will be set
		//
	case 4:
		iBuffer = bActivate ? PCAN_PARAMETER_ON : PCAN_PARAMETER_OFF;
		stsResult = m_objPCANBasic->SetValue(PCAN_NONEBUS, PCAN_LOG_STATUS, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The feature for logging debug information was successfully %s", ARRAYOFCONST((bActivate ? "activated" : "deactivated")));
			IncludeTextMessage(info);
			::GetCurrentDirectory(sizeof(szDirectory) - 1, szDirectory);
			info = Format("Log file folder: %s" , ARRAYOFCONST((szDirectory)));
			IncludeTextMessage(info);
		}
		break;

		// The channel option "Receive Status" will be set
		//
	case 5:
		iBuffer = bActivate ? PCAN_PARAMETER_ON : PCAN_PARAMETER_OFF;
		stsResult = m_objPCANBasic->SetValue(m_PcanHandle, PCAN_RECEIVE_STATUS, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The channel option \"Receive Status\" was set to %s", ARRAYOFCONST((bActivate ? "ON" : "OFF")));
			IncludeTextMessage(info);
		}
		break;

		// The feature for tracing will be set
		//
	case 7:
		iBuffer = bActivate ? PCAN_PARAMETER_ON : PCAN_PARAMETER_OFF;
		stsResult = m_objPCANBasic->SetValue(m_PcanHandle, PCAN_TRACE_STATUS, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The feature for tracing data was successfully %s", ARRAYOFCONST((bActivate ? "activated" : "deactivated")));
			IncludeTextMessage(info);
		}
		break;

		// The feature for identifying an USB Channel will be set
		//
	case 8:
		iBuffer = bActivate ? PCAN_PARAMETER_ON : PCAN_PARAMETER_OFF;
		stsResult = m_objPCANBasic->SetValue(m_PcanHandle, PCAN_CHANNEL_IDENTIFYING, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The procedure for channel identification was successfully %s", ARRAYOFCONST((bActivate ? "activated" : "deactivated")));
			IncludeTextMessage(info);
		}
		break;

		// The feature for using an already configured speed will be set
		//
	case 10:
		iBuffer = bActivate ? PCAN_PARAMETER_ON : PCAN_PARAMETER_OFF;
		stsResult = m_objPCANBasic->SetValue(m_PcanHandle, PCAN_BITRATE_ADAPTING, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The feature for bit rate adaptation was successfully %s", ARRAYOFCONST((bActivate ? "activated" : "deactivated")));
			IncludeTextMessage(info);
		}
		break;

		// The option "Allow Status Frames" will be set
		//
	case 17:
		iBuffer = bActivate ? PCAN_PARAMETER_ON : PCAN_PARAMETER_OFF;
		stsResult = m_objPCANBasic->SetValue(m_PcanHandle, PCAN_ALLOW_STATUS_FRAMES, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The reception of Status frames was successfully %s", ARRAYOFCONST((bActivate ? "enabled" : "disabled")));
			IncludeTextMessage(info);
		}
		break;

		// The option "Allow RTR Frames" will be set
		//
	case 18:
		iBuffer = bActivate ? PCAN_PARAMETER_ON : PCAN_PARAMETER_OFF;
		stsResult = m_objPCANBasic->SetValue(m_PcanHandle, PCAN_ALLOW_RTR_FRAMES, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The reception of RTR frames was successfully %s", ARRAYOFCONST((bActivate ? "enabled" : "disabled")));
			IncludeTextMessage(info);
		}
		break;

		// The option "Allow Error Frames" will be set
		//
	case 19:
		iBuffer = bActivate ? PCAN_PARAMETER_ON : PCAN_PARAMETER_OFF;
		stsResult = m_objPCANBasic->SetValue(m_PcanHandle, PCAN_ALLOW_ERROR_FRAMES, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The reception of Error frames was successfully %s", ARRAYOFCONST((bActivate ? "enabled" : "disabled")));
			IncludeTextMessage(info);
		}
		break;

		// The option "Interframes Delay" will be set
		//
	case 20:
		iBuffer = StrToInt(txtDeviceIdOrDelay->Text);
		stsResult = m_objPCANBasic->SetValue(m_PcanHandle, PCAN_INTERFRAME_DELAY, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
			IncludeTextMessage("The delay between transmitting frames was successfully set");
		break;
		// The current parameter is invalid
		//
	default:
		stsResult = PCAN_ERROR_UNKNOWN;
		::MessageBox(NULL, "Wrong parameter code.", "Error!",MB_ICONERROR);
		return;
	}

	// If the function fail, an error message is shown
	//
	if(stsResult != PCAN_ERROR_OK)
		::MessageBox(NULL, GetFormatedError(stsResult).c_str(), "Error!",MB_ICONERROR);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnParameterGetClick(TObject *Sender)
{
	TPCANStatus stsResult;
	unsigned int iBuffer;
	char strBuffer[256];
	AnsiString  info;

	// Sets a PCAN-Basic parameter value
	//
	switch (cbbParameter->ItemIndex)
	{
		// The Device-Number of an USB channel will be get
		//
	case 0:
		stsResult = m_objPCANBasic->GetValue(m_PcanHandle, PCAN_DEVICE_NUMBER, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The configured Device-Number is %d", ARRAYOFCONST((iBuffer)));
			IncludeTextMessage(info);
		}
		break;

		// The 5 Volt Power feature of a PC-card or USB will be get
		//
	case 1:
		stsResult = m_objPCANBasic->GetValue(m_PcanHandle, PCAN_5VOLTS_POWER, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The 5-Volt Power of the USB/PC-Card is %s", ARRAYOFCONST(((iBuffer == PCAN_PARAMETER_ON) ? "activated" : "deactivated")));
			IncludeTextMessage(info);
		}
		break;

		// The feature for automatic reset on BUS-OFF will be get
		//
	case 2:
		stsResult = m_objPCANBasic->GetValue(m_PcanHandle, PCAN_BUSOFF_AUTORESET, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The automatic-reset on BUS-OFF is %s", ARRAYOFCONST(((iBuffer == PCAN_PARAMETER_ON) ? "activated" : "deactivated")));
			IncludeTextMessage(info);
		}
		break;

		// The CAN option "Listen Only" will be get
		//
	case 3:
		stsResult = m_objPCANBasic->GetValue(m_PcanHandle, PCAN_LISTEN_ONLY, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The CAN option \"Listen Only\" is %s", ARRAYOFCONST(((iBuffer == PCAN_PARAMETER_ON) ? "activated" : "deactivated")));
			IncludeTextMessage(info);
		}
		break;

		// The feature for logging debug-information will be get
		//
	case 4:
		stsResult = m_objPCANBasic->GetValue(PCAN_NONEBUS, PCAN_LOG_STATUS, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The feature for logging debug information is %s", ARRAYOFCONST(((iBuffer == PCAN_PARAMETER_ON) ? "activated" : "deactivated")));
			IncludeTextMessage(info);
		}
		break;

		// The activation status of the channel option "Receive Status"  will be retrieved
		//
	case 5:
		stsResult = m_objPCANBasic->GetValue(m_PcanHandle, PCAN_RECEIVE_STATUS, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The channel option \"Receive Status\" is %s", ARRAYOFCONST(((iBuffer == PCAN_PARAMETER_ON) ? "ON" : "OFF")));
			IncludeTextMessage(info);
		}
		break;

		// The Number of the CAN-Controller used by a PCAN-Channel
		//
	case 6:
		stsResult = m_objPCANBasic->GetValue(m_PcanHandle, PCAN_CONTROLLER_NUMBER, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The CAN Controller number is %d", ARRAYOFCONST((iBuffer)));
			IncludeTextMessage(info);
		}
		break;

		// The activation status for the feature for tracing data will be retrieved
        //
	case 7:
		stsResult = m_objPCANBasic->GetValue(m_PcanHandle, PCAN_TRACE_STATUS, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The feature for tracing data is %s", ARRAYOFCONST(((iBuffer == PCAN_PARAMETER_ON) ? "ON" : "OFF")));
			IncludeTextMessage(info);
		}
		break;

		// The activation status of the Channel Identifying procedure will be retrieved
		//
	case 8:
		stsResult = m_objPCANBasic->GetValue(m_PcanHandle, PCAN_CHANNEL_IDENTIFYING, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The identification procedure of the selected channel is %s", ARRAYOFCONST(((iBuffer == PCAN_PARAMETER_ON) ? "ON" : "OFF")));
			IncludeTextMessage(info);
		}
		break;

		// The extra capabilities of a hardware will asked
		//
	case 9:
		stsResult = m_objPCANBasic->GetValue(m_PcanHandle, PCAN_CHANNEL_FEATURES, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The channel %s Flexible Data-Rate (CAN-FD)", ARRAYOFCONST(((iBuffer & FEATURE_FD_CAPABLE) ? "does support" : "DOESN'T SUPPORT")));
			IncludeTextMessage(info);
			info = Format("The channel %s an inter-frame delay for sending messages", ARRAYOFCONST(((iBuffer & FEATURE_DELAY_CAPABLE) ? "does support" : "DOESN'T SUPPORT")));
			IncludeTextMessage(info);
			info = Format("The channel %s using I/O pins", ARRAYOFCONST(((iBuffer & FEATURE_IO_CAPABLE) ? "does allow" : "DOESN'T ALLOW")));
			IncludeTextMessage(info);
		}
		break;

		// The status of the speed adapting feature will be retrieved 
		//
	case 10:
		stsResult = m_objPCANBasic->GetValue(m_PcanHandle, PCAN_BITRATE_ADAPTING, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The feature for bit rate adaptation is %s", ARRAYOFCONST(((iBuffer == PCAN_PARAMETER_ON) ? "ON" : "OFF")));
			IncludeTextMessage(info);
		}
		break;

		// The bitrate of the connected channel will be retrieved (BTR0-BTR1 value)
		//
	case 11:
		stsResult = m_objPCANBasic->GetValue(m_PcanHandle, PCAN_BITRATE_INFO, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The bit rate of the channel is %.4Xh", ARRAYOFCONST(((iBuffer))));
			IncludeTextMessage(info);
		}
		break;

		// The bitrate of the connected FD channel will be retrieved (String value)
		//
	case 12:
		stsResult = m_objPCANBasic->GetValue(m_PcanHandle, PCAN_BITRATE_INFO_FD, strBuffer, 256);
		if(stsResult == PCAN_ERROR_OK)
		{
			IncludeTextMessage("The bit rate FD of the channel is represented by the following values:");
			TStringList *strParts;
			strParts = new TStringList();
			strParts->Delimiter = ',';
			strParts->DelimitedText = strBuffer;
			for(int i=0 ; i < strParts->Count; i++)
				IncludeTextMessage(((AnsiString)"  * ") + strParts->Strings[i]);
			delete strParts;
		}
		break;

		// The nominal speed configured on the CAN bus
		//
	case 13:
		stsResult = m_objPCANBasic->GetValue(m_PcanHandle, PCAN_BUSSPEED_NOMINAL, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The nominal speed of the channel is %d bit/s", ARRAYOFCONST((iBuffer)));
			IncludeTextMessage(info);
		}
		break;

		// The data speed configured on the CAN bus
		//
	case 14:
		stsResult = m_objPCANBasic->GetValue(m_PcanHandle, PCAN_BUSSPEED_DATA, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The data speed of the channel is %d bit/s", ARRAYOFCONST((iBuffer)));
			IncludeTextMessage(info);
		}
		break;

		// The IP address of a LAN channel as string, in IPv4 format
		//
	case 15:
		stsResult = m_objPCANBasic->GetValue(m_PcanHandle, PCAN_IP_ADDRESS, strBuffer, 256);
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The IP address of the channel is %s", ARRAYOFCONST(((AnsiString)strBuffer)));
			IncludeTextMessage(info);
		}
		break;

		// The running status of the LAN Service
		//
	case 16:
		stsResult = m_objPCANBasic->GetValue(PCAN_NONEBUS, PCAN_LAN_SERVICE_STATUS, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The LAN service is %s", ARRAYOFCONST(((iBuffer == SERVICE_STATUS_RUNNING) ? "running" : "NOT running")));
			IncludeTextMessage(info);
		}
		break;

		// The reception of Status frames
		//
	case 17:
		stsResult = m_objPCANBasic->GetValue(m_PcanHandle, PCAN_ALLOW_STATUS_FRAMES, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The reception of Status frames is %s", ARRAYOFCONST(((iBuffer == PCAN_PARAMETER_ON) ? "enabled" : "disabled")));
			IncludeTextMessage(info);
		}
		break;

		// The reception of RTR frames
		//
	case 18:
		stsResult = m_objPCANBasic->GetValue(m_PcanHandle, PCAN_ALLOW_RTR_FRAMES, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The reception of RTR frames is %s", ARRAYOFCONST(((iBuffer == PCAN_PARAMETER_ON) ? "enabled" : "disabled")));
			IncludeTextMessage(info);
		}
		break;

		// The reception of Error frames
		//
	case 19:
		stsResult = m_objPCANBasic->GetValue(m_PcanHandle, PCAN_ALLOW_ERROR_FRAMES, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The reception of Error frames is %s", ARRAYOFCONST(((iBuffer == PCAN_PARAMETER_ON) ? "enabled" : "disabled")));
			IncludeTextMessage(info);
		}
		break;

		// The Interframe delay of an USB channel will be retrieved
		//
	case 20:
		stsResult = m_objPCANBasic->GetValue(m_PcanHandle, PCAN_INTERFRAME_DELAY, (void*)&iBuffer, sizeof(iBuffer));
		if(stsResult == PCAN_ERROR_OK)
		{
			info = Format("The configured interframe delay is %d ms", ARRAYOFCONST((iBuffer)));
			IncludeTextMessage(info);
		}
		break;

		// The current parameter is invalid
		//
	default:
		::MessageBox(NULL, "Wrong parameter code.", "Error!",MB_ICONERROR);
		return;
	}

	// If the function fail, an error message is shown
	//
	if(stsResult != PCAN_ERROR_OK)
		::MessageBox(NULL, GetFormatedError(stsResult).c_str(), "Error!",MB_ICONERROR);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnReadClick(TObject *Sender)
{
	TPCANStatus stsResult;

	// We execute the "Read" function of the PCANBasic
	//
	stsResult = m_IsFD ? ReadMessageFD() : ReadMessage();
	if (stsResult != PCAN_ERROR_OK)
		// If an error occurred, an information message is included
		//
		IncludeTextMessage(GetFormatedError(stsResult));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnMsgClearClick(TObject *Sender)
{
	// (Protected environment)
	//
	{
		clsCritical locker(m_objpCS);

		// Remove all messages
		//
		lstMessages->Items->Clear();
		while(m_LastMsgsList->Count)
		{
			delete m_LastMsgsList->First();
			m_LastMsgsList->Delete(0);
		}
	}
}
//---------------------------------------------------------------------------

TPCANStatus TForm1::WriteFrame()
{
	TPCANMsg CANMsg;
	TEdit *CurrentTextBox;

	// We configurate the Message.  The ID (max 0x1FF),
	// Length of the Data, Message Type (Standard in
	// this example) and die data
	//
	CANMsg = TPCANMsg();
	CANMsg.ID = StrToInt("0x"+txtID->Text);
	CANMsg.LEN = (BYTE)nudLength->Position;
	CANMsg.MSGTYPE = (chbExtended->Checked) ? PCAN_MESSAGE_EXTENDED : PCAN_MESSAGE_STANDARD;
	// If a remote frame will be sent, the data bytes are not important.
	//
	if (chbRemote->Checked)
		CANMsg.MSGTYPE |= PCAN_MESSAGE_RTR;
	else
	{
		// We get so much data as the Len of the message
		//
		for (int i = 0; i < GetLengthFromDLC(CANMsg.LEN, true); i++)
		{
			CurrentTextBox = (TEdit*)FindComponent("txtData"+IntToStr(i));
			CANMsg.DATA[i] = (BYTE)(StrToInt("0x" + CurrentTextBox->Text));
		}
	}

	// The message is sent to the configured hardware
	//
	return m_objPCANBasic->Write(m_PcanHandle, &CANMsg);
}
//---------------------------------------------------------------------------

TPCANStatus TForm1::WriteFrameFD()
{
	TPCANMsgFD CANMsg;
	TEdit *CurrentTextBox;
	int iLength;

	// We configurate the Message.  The ID (max 0x1FF),
	// Length of the Data, Message Type (Standard in
	// this example) and die data
	//
	CANMsg = TPCANMsgFD();
	CANMsg.ID = StrToInt("0x"+txtID->Text);
	CANMsg.DLC = (BYTE)nudLength->Position;
	CANMsg.MSGTYPE = (chbExtended->Checked) ? PCAN_MESSAGE_EXTENDED : PCAN_MESSAGE_STANDARD;
	CANMsg.MSGTYPE |= (chbFD->Checked) ?  PCAN_MESSAGE_FD : PCAN_MESSAGE_STANDARD;
	CANMsg.MSGTYPE |= (chbBRS->Checked) ?  PCAN_MESSAGE_BRS : PCAN_MESSAGE_STANDARD;

	// If a remote frame will be sent, the data bytes are not important.
	//
	if (chbRemote->Checked)
		CANMsg.MSGTYPE |= PCAN_MESSAGE_RTR;
	else
	{
		// We get so much data as the Len of the message
		//
		iLength = GetLengthFromDLC(CANMsg.DLC, !(CANMsg.MSGTYPE & PCAN_MESSAGE_FD));
		for (int i = 0; i < iLength; i++)
		{
			CurrentTextBox = (TEdit*)FindComponent("txtData"+IntToStr(i));
			CANMsg.DATA[i] = (BYTE)(StrToInt("0x" + CurrentTextBox->Text));
		}
	}

	// The message is sent to the configured hardware
	//
	return m_objPCANBasic->WriteFD(m_PcanHandle, &CANMsg);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnWriteClick(TObject *Sender)
{
	TPCANStatus stsResult;

	// Send the message
	//
	stsResult = m_IsFD ? WriteFrameFD() : WriteFrame();

	// The Hardware was successfully sent
	//
	if (stsResult == PCAN_ERROR_OK)
		IncludeTextMessage("Message was successfully SENT");
	// An error occurred.  We show the error.
	//
	else
		::MessageBox(NULL, GetFormatedError(stsResult).c_str(), "Error!",MB_ICONERROR);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnGetVersionsClick(TObject *Sender)
{
	TPCANStatus stsResult;
	char buffer[256];

	AnsiString info;
	int iPos;

	memset(buffer,'\0',256);

	// We get the vesion of the PCAN-Basic API
	//
	stsResult = m_objPCANBasic->GetValue(PCAN_NONEBUS, PCAN_API_VERSION, buffer, 256);
	if (stsResult == PCAN_ERROR_OK)
	{
		info = Format("API Version: %s", ARRAYOFCONST((buffer)));
		IncludeTextMessage(info);
		// We get the driver version of the channel being used
		//
		stsResult = m_objPCANBasic->GetValue(m_PcanHandle, PCAN_CHANNEL_VERSION, buffer, 256);

		if (stsResult == PCAN_ERROR_OK)
		{
			IncludeTextMessage("Channel/Driver Version: ");

			// Because this information contains line control characters (several lines)
			// we split this also in several entries in the Information List-Box
			//			
			info = (AnsiString)buffer;
			while(info != "")
			{
				iPos = info.Pos("\n");
				if(iPos == 0)
					iPos = info.Length();
				IncludeTextMessage("     * " + info.SubString(1, iPos));
				info.Delete(1,iPos);
			}
		}
	}

	// If the function fail, an error message is shown
	//
	if(stsResult != PCAN_ERROR_OK)
		::MessageBox(NULL, GetFormatedError(stsResult).c_str(), "Error!",MB_ICONERROR);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnInfoClearClick(TObject *Sender)
{
	lbxInfo->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnStatusClick(TObject *Sender)
{
	TPCANStatus status;
	AnsiString errorName;
	AnsiString info;

	// Gets the current BUS status of a PCAN Channel.
	//
	status = m_objPCANBasic->GetStatus(m_PcanHandle);

	// Switch On Error Name
	//
	switch(status)
	{
		case PCAN_ERROR_INITIALIZE:
			errorName = "PCAN_ERROR_INITIALIZE";
			break;

		case PCAN_ERROR_BUSLIGHT:
			errorName = "PCAN_ERROR_BUSLIGHT";
			break;

		case PCAN_ERROR_BUSHEAVY: // PCAN_ERROR_BUSWARNING
			errorName = m_IsFD ? "PCAN_ERROR_BUSWARNING" : "PCAN_ERROR_BUSHEAVY";
			break;

		case PCAN_ERROR_BUSPASSIVE:
			errorName = "PCAN_ERROR_BUSPASSIVE";
			break;

		case PCAN_ERROR_BUSOFF:
			errorName = "PCAN_ERROR_BUSOFF";
			break;

		case PCAN_ERROR_OK:
			errorName = "PCAN_ERROR_OK";
			break;

		default:
			errorName = "See Documentation";
			break;
	}

	// Display Message
	//
	info = Format("Status: %s (%Xh)", ARRAYOFCONST((errorName, status)));
	IncludeTextMessage(info);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnResetClick(TObject *Sender)
{
	TPCANStatus stsResult;

	// Resets the receive and transmit queues of a PCAN Channel.
	//
	stsResult = m_objPCANBasic->Reset(m_PcanHandle);

	// If it fails, a error message is shown
	//
	if (stsResult != PCAN_ERROR_OK)
		::MessageBox(NULL, GetFormatedError(stsResult).c_str(), "Error!",MB_ICONERROR);
	else
		IncludeTextMessage("Receive and transmit queues successfully reset");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::cbbChannelChange(TObject *Sender)
{
	bool bNonPnP;
	AnsiString strTemp;

	// Get the handle from the text being shown
	//
	strTemp = cbbChannel->Text;
	strTemp = strTemp.SubString(strTemp.Pos("(") + 1, 3);

	strTemp = StringReplace(strTemp, "h", " ", TReplaceFlags() << rfReplaceAll).Trim();

	// Determines if the handle belong to a No Plug&Play hardware
	//
	m_PcanHandle = (TPCANHandle)StrToInt("0x"+strTemp);
	bNonPnP = m_PcanHandle <= PCAN_DNGBUS1;

	// Activates/deactivates configuration controls according with the
	// kind of hardware
	//
	cbbIO->Enabled = bNonPnP;
	cbbInterrupt->Enabled = bNonPnP;
	cbbHwType->Enabled = bNonPnP;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::cbbBaudratesChange(TObject *Sender)
{
	// We save the corresponding Baudrate enumeration
	// type value for every selected Baudrate from the
	// list.
	//
	switch(cbbBaudrates->ItemIndex)
	{
	case 0:
		m_Baudrate = PCAN_BAUD_1M;
		break;
	case 1:
		m_Baudrate = PCAN_BAUD_800K;
		break;
	case 2:
		m_Baudrate = PCAN_BAUD_500K;
		break;
	case 3:
		m_Baudrate = PCAN_BAUD_250K;
		break;
	case 4:
		m_Baudrate = PCAN_BAUD_125K;
		break;
	case 5:
		m_Baudrate = PCAN_BAUD_100K;
		break;
	case 6:
		m_Baudrate = PCAN_BAUD_95K;
		break;
	case 7:
		m_Baudrate = PCAN_BAUD_83K;
		break;
	case 8:
		m_Baudrate = PCAN_BAUD_50K;
		break;
	case 9:
		m_Baudrate = PCAN_BAUD_47K;
		break;
	case 10:
		m_Baudrate = PCAN_BAUD_33K;
		break;
	case 11:
		m_Baudrate = PCAN_BAUD_20K;
		break;
	case 12:
		m_Baudrate = PCAN_BAUD_10K;
		break;
	case 13:
		m_Baudrate = PCAN_BAUD_5K;
		break;
	default:
		m_Baudrate = (TPCANBaudrate)0;
		break;
	}	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::cbbHwTypeChange(TObject *Sender)
{
	// Saves the current type for a no-Plug&Play hardware
	//
	switch (cbbHwType->ItemIndex)
	{
	case 0:
		m_HwType = PCAN_TYPE_ISA;
		break;
	case 1:
		m_HwType = PCAN_TYPE_ISA_SJA;
		break;
	case 2:
		m_HwType = PCAN_TYPE_ISA_PHYTEC;
		break;
	case 3:
		m_HwType = PCAN_TYPE_DNG;
		break;
	case 4:
		m_HwType = PCAN_TYPE_DNG_EPP;
		break;
	case 5:
		m_HwType = PCAN_TYPE_DNG_SJA;
		break;
	case 6:
		m_HwType = PCAN_TYPE_DNG_SJA_EPP;
		break;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::cbbParameterChange(TObject *Sender)
{
	// Activates/deactivates controls according with the selected
	// PCAN-Basic parameter 
	//
	rdbParamActive->Enabled = (cbbParameter->ItemIndex != 0) && (cbbParameter->ItemIndex != 20);
	rdbParamInactive->Enabled = rdbParamActive->Enabled;
	txtDeviceIdOrDelay->Enabled = (!rdbParamActive->Enabled);
	laDeviceOrDelay->Caption = (cbbParameter->ItemIndex == 20) ? "Delay (ms):" : "Device ID:";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::chbFilterExtClick(TObject *Sender)
{
	// Updates the from and To ID-text according with the Message type
	//
	txtIdFromExit(txtIdFrom);
	txtIdFromExit(txtIdTo);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::chbExtendedClick(TObject *Sender)
{
	// Updates the ID-text according with the Message type
	//
	txtIDExit(txtID);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::rdbTimerClick(TObject *Sender)
{
	TRadioButton *radioBtn;

	radioBtn = 	(TRadioButton*)Sender;
	if(radioBtn && !radioBtn->Checked)
		return;

	if(radioBtn->Name == "rdbTimer")
		m_ActiveReadingMode = 0;
	if(radioBtn->Name == "rdbEvent")
		m_ActiveReadingMode = 1;
	if(radioBtn->Name == "rdbManual")
		m_ActiveReadingMode = 2;

	ReadingModeChanged();
}
//---------------------------------------------------------------------------

void TForm1::EnableDisableDataFields(int length)
{
	TEdit *CurrentTextBox;

	CurrentTextBox = txtData0;
	for (int i = 0; i <= 64; i++)
	{
		CurrentTextBox->Enabled = i <= length;
		if (i < 64)
			CurrentTextBox = (TEdit*)FindComponent("txtData"+IntToStr(i));
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::nudLengthClick(TObject *Sender, TUDBtnType Button)
{
	int iLength;

	iLength = GetLengthFromDLC((int)nudLength->Position, !chbFD->Checked);
	EnableDisableDataFields(iLength);
	laLength->Caption = Format("%d B.", ARRAYOFCONST((iLength)));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::txtIdFromExit(TObject *Sender)
{
	unsigned int iTempMax, iTempValue;
	TEdit *IdBox;

	IdBox = (TEdit*)Sender;

	// Calculates the text length and Maximum ID value according
	// with the Frame Type
	//
	IdBox->MaxLength = (chbFilterExt->Checked) ? 8 : 3;
	iTempMax = (chbFilterExt->Checked) ? 0x1FFFFFFF : 0x7FF;

	// Adjusts the ID value to refresh
	//
	iTempValue = StrToInt("0x" + IdBox->Text);
	if(iTempValue < iTempMax)
		iTempMax = iTempValue;

	// Refreshes the ID value
	//
	IdBox->Text = IntToHex((int)iTempMax,IdBox->MaxLength);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::txtIdFromKeyPress(TObject *Sender, char &Key)
{
	// We convert the Character to its Upper case equivalent
	//
	Key = *(UpperCase((AnsiString)Key)).c_str();

	// The Key is the Delete (Backspace) Key
	//
	if(Key == 8)
		return;
	// The Key is a number between 0-9
	//
	if((Key > 47)&&(Key < 58))
		return;
	// The Key is a character between A-F
	//
	if((Key > 64)&&(Key < 71))
		return;

	// Is neither a number nor a character between A(a) and F(f)
	//
	Key = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::txtDeviceIdOrDelayKeyPress(TObject *Sender, char &Key)
{
	// We convert the Character to its Upper case equivalent
	//
	Key = *(UpperCase((AnsiString)Key)).c_str();

	// The Key is the Delete (Backspace) Key
	//
	if(Key == 8)
		return;
	// The Key is a number between 0-9
	//
	if((Key > 47)&&(Key < 58))
		return;

	// Is neither a number nor a character between A(a) and F(f)
	//
	Key = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::txtDeviceIdOrDelayExit(TObject *Sender)
{
	__int64 iTemp;

	// Checks the range of the given device ID
	//
	iTemp = StrToInt64(txtDeviceIdOrDelay->Text);
	if(iTemp > MAXUINT)
		txtDeviceIdOrDelay->Text = FloatToStr(MAXUINT);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::txtIDExit(TObject *Sender)
{
	unsigned int iTempMax, iTempValue;

	// Calculates the text length and Maximum ID value according
	// with the Frame Type
	//
	txtID->MaxLength = (chbExtended->Checked) ? 8 : 3;
	iTempMax = (chbExtended->Checked) ? 0x1FFFFFFF : 0x7FF;

	// Adjusts the ID value to refresh
	//
	iTempValue = StrToInt("0x" + txtID->Text);
	if(iTempValue < iTempMax)
		iTempMax = iTempValue;

	// Refreshes the ID value
	//
	txtID->Text = IntToHex((int)iTempMax,txtID->MaxLength);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::txtData0Exit(TObject *Sender)
{
	TEdit *CurrentEdit;

	// Checks the length of the given value
	//
	if(String(Sender->ClassName()) == "TEdit")
	{
		CurrentEdit = (TEdit*)Sender;
		while(CurrentEdit->Text.Length() != 2)
			CurrentEdit->Text = ("0" + CurrentEdit->Text);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::chbShowPeriodClick(TObject *Sender)
{
	MessageStatus *msg;

	// According with the check-value of this checkbox,
	// the recieved time of a messages will be interpreted as 
	// period (time between the two last messages) or as time-stamp
	// (the elapsed time since windows was started).
	// - (Protected environment)
	//
	{
		clsCritical locker(m_objpCS);

		for(int i=0; i < m_LastMsgsList->Count; i++)
		{
			msg = (MessageStatus*)m_LastMsgsList->Items[i];
			msg->ShowingPeriod =  chbShowPeriod->Checked;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tmrDisplayTimer(TObject *Sender)
{
	DisplayMessages();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::chbCanFDClick(TObject *Sender)
{
	m_IsFD = chbCanFD->Checked;

	cbbBaudrates->Visible = !m_IsFD;
	cbbHwType->Visible = !m_IsFD;
	cbbInterrupt->Visible = !m_IsFD;
	cbbIO->Visible = !m_IsFD;
	laBaudrate->Visible = !m_IsFD;
	laHwType->Visible = !m_IsFD;
	laIOPort->Visible = !m_IsFD;
	laInterrupt->Visible = !m_IsFD;

	txtBitrate->Visible = m_IsFD;
	laBitrate->Visible = m_IsFD;
	chbFD->Visible = m_IsFD;
	chbBRS->Visible = m_IsFD;

	if ((nudLength->Max > 8) && !m_IsFD)
		chbFD->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::chbFDClick(TObject *Sender)
{
	int iMax;

	chbRemote->Enabled = !chbFD->Checked;
	chbBRS->Enabled = chbFD->Checked;
	if (!chbBRS->Enabled)
		chbBRS->Checked = false;
	iMax = chbFD->Checked ? 15 : 8;
	nudLength->Max = iMax;
	txtLength->Text = IntToStr(nudLength->Position);
	EnableDisableDataFields(GetLengthFromDLC(nudLength->Position, chbFD->Checked));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::chbRemoteClick(TObject *Sender)
{
	// Show or Hide control according message is a RTR
	//
	EnableDisableDataFields(chbRemote->Checked ? 0 : nudLength->Position);
	chbFD->Enabled = !chbRemote->Checked;
}
//---------------------------------------------------------------------------

