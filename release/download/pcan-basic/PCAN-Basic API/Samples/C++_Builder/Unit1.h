//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "PCANBasicClass.h"

// Critical Section class for thread-safe menbers access
//
class clsCritical
{
	private:
		CRITICAL_SECTION *m_objpCS;
		ULONG volatile m_dwOwnerThread;
		LONG volatile m_dwLocked;
		bool volatile m_bDoRecursive;

	public:
		explicit clsCritical(CRITICAL_SECTION *cs, bool createUnlocked = false, bool lockRecursively = false);
        ~clsCritical();
		int GetRecursionCount();
		bool IsLocked();
		int Enter();
		int Leave();
};

/// Message Status structure used to show CAN Messages
/// in a ListView
//
class MessageStatus
{
	private:
		TPCANMsgFD m_Msg;
		TPCANTimestampFD m_TimeStamp;
		TPCANTimestampFD m_oldTimeStamp;
		int m_iIndex;
		int m_Count;
		bool m_bShowPeriod;
		bool m_bWasChanged;

		AnsiString GetTypeString();
		AnsiString GetIdString();
		AnsiString GetDataString();
		AnsiString GetTimeString();
		void SetShowingPeriod(bool value);

	public:
		MessageStatus(TPCANMsgFD canMsg,TPCANTimestampFD canTimestamp,int listIndex);
		void Update(TPCANMsgFD canMsg, TPCANTimestampFD canTimestamp);

		__property TPCANMsgFD CANMsg = {read = m_Msg};
		__property TPCANTimestampFD Timestamp = {read = m_TimeStamp};
		__property int Position = {read = m_iIndex};
		__property AnsiString TypeString = {read = GetTypeString};
		__property AnsiString IdString = {read = GetIdString};
		__property AnsiString DataString = {read = GetDataString};
		__property AnsiString TimeString = {read = GetTimeString};
		__property int Count = {read = m_Count};
		__property bool ShowingPeriod = {read = m_bShowPeriod, write = SetShowingPeriod};
		__property bool MarkedAsUpdated = {read = m_bWasChanged, write = m_bWasChanged};
};

typedef void (__closure *ProcMsgRead)();

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TGroupBox *GroupBox3;
	TGroupBox *GroupBox4;
	TGroupBox *GroupBox5;
	TGroupBox *GroupBox6;
	TLabel *Label1;
	TComboBox *cbbChannel;
	TButton *btnHwRefresh;
	TLabel *laBaudrate;
	TComboBox *cbbBaudrates;
	TLabel *laHwType;
	TComboBox *cbbHwType;
	TComboBox *cbbIO;
	TLabel *laIOPort;
	TLabel *laInterrupt;
	TComboBox *cbbInterrupt;
	TButton *btnInit;
	TButton *btnRelease;
	TCheckBox *chbFilterExt;
	TRadioButton *rdbFilterOpen;
	TRadioButton *rdbFilterClose;
	TRadioButton *rdbFilterCustom;
	TEdit *txtIdFrom;
	TEdit *txtIdTo;
	TLabel *Label6;
	TLabel *Label7;
	TButton *btnFilterApply;
	TButton *btnFilterQuery;
	TButton *btnParameterSet;
	TButton *btnParameterGet;
	TLabel *Label8;
	TComboBox *cbbParameter;
	TLabel *Label9;
	TRadioButton *rdbParamActive;
	TRadioButton *rdbParamInactive;
	TLabel *laDeviceOrDelay;
	TEdit *txtDeviceIdOrDelay;
	TRadioButton *rdbTimer;
	TRadioButton *rdbEvent;
	TRadioButton *rdbManual;
	TCheckBox *chbShowPeriod;
	TButton *btnRead;
	TButton *btnMsgClear;
	TListView *lstMessages;
	TTimer *tmrRead;
	TEdit *txtID;
	TLabel *Label11;
	TCheckBox *chbExtended;
	TEdit *txtLength;
	TUpDown *nudLength;
	TLabel *Label12;
	TCheckBox *chbRemote;
	TLabel *Label13;
	TEdit *txtData0;
	TEdit *txtData1;
	TEdit *txtData2;
	TEdit *txtData3;
	TEdit *txtData4;
	TEdit *txtData5;
	TEdit *txtData6;
	TEdit *txtData7;
	TButton *btnWrite;
	TListBox *lbxInfo;
	TButton *btnGetVersions;
	TButton *btnInfoClear;
	TButton *btnReset;
	TButton *btnStatus;
	TTimer *tmrDisplay;
	TEdit *txtData8;
	TEdit *txtData9;
	TEdit *txtData10;
	TEdit *txtData12;
	TEdit *txtData11;
	TEdit *txtData13;
	TEdit *txtData14;
	TEdit *txtData15;
	TEdit *txtData24;
	TEdit *txtData25;
	TEdit *txtData26;
	TEdit *txtData28;
	TEdit *txtData27;
	TEdit *txtData29;
	TEdit *txtData30;
	TEdit *txtData31;
	TEdit *txtData23;
	TEdit *txtData22;
	TEdit *txtData21;
	TEdit *txtData20;
	TEdit *txtData19;
	TEdit *txtData18;
	TEdit *txtData17;
	TEdit *txtData16;
	TEdit *txtData40;
	TEdit *txtData41;
	TEdit *txtData42;
	TEdit *txtData44;
	TEdit *txtData43;
	TEdit *txtData45;
	TEdit *txtData46;
	TEdit *txtData47;
	TEdit *txtData39;
	TEdit *txtData38;
	TEdit *txtData37;
	TEdit *txtData36;
	TEdit *txtData35;
	TEdit *txtData34;
	TEdit *txtData33;
	TEdit *txtData32;
	TEdit *txtData56;
	TEdit *txtData57;
	TEdit *txtData58;
	TEdit *txtData60;
	TEdit *txtData59;
	TEdit *txtData61;
	TEdit *txtData62;
	TEdit *txtData63;
	TEdit *txtData55;
	TEdit *txtData54;
	TEdit *txtData53;
	TEdit *txtData52;
	TEdit *txtData51;
	TEdit *txtData50;
	TEdit *txtData49;
	TEdit *txtData48;
	TLabel *Label2;
	TCheckBox *chbFD;
	TCheckBox *chbBRS;
	TLabel *laLength;
	TMemo *txtBitrate;
	TLabel *laBitrate;
	TCheckBox *chbCanFD;
	void __fastcall btnHwRefreshClick(TObject *Sender);
	void __fastcall cbbBaudratesChange(TObject *Sender);
	void __fastcall cbbHwTypeChange(TObject *Sender);
	void __fastcall cbbParameterChange(TObject *Sender);
	void __fastcall cbbChannelChange(TObject *Sender);
	void __fastcall txtIdFromExit(TObject *Sender);
	void __fastcall chbFilterExtClick(TObject *Sender);
	void __fastcall txtIdFromKeyPress(TObject *Sender, char &Key);
	void __fastcall txtIDExit(TObject *Sender);
	void __fastcall chbExtendedClick(TObject *Sender);
	void __fastcall txtData0Exit(TObject *Sender);
	void __fastcall nudLengthClick(TObject *Sender, TUDBtnType Button);
	void __fastcall btnInitClick(TObject *Sender);
	void __fastcall btnReleaseClick(TObject *Sender);
	void __fastcall rdbTimerClick(TObject *Sender);
	void __fastcall btnFilterApplyClick(TObject *Sender);
	void __fastcall txtDeviceIdOrDelayKeyPress(TObject *Sender, char &Key);
	void __fastcall txtDeviceIdOrDelayExit(TObject *Sender);
	void __fastcall btnParameterSetClick(TObject *Sender);
	void __fastcall btnParameterGetClick(TObject *Sender);
	void __fastcall btnReadClick(TObject *Sender);
	void __fastcall btnMsgClearClick(TObject *Sender);
	void __fastcall btnWriteClick(TObject *Sender);
	void __fastcall btnGetVersionsClick(TObject *Sender);
	void __fastcall btnInfoClearClick(TObject *Sender);
	void __fastcall btnStatusClick(TObject *Sender);
	void __fastcall btnResetClick(TObject *Sender);
	void __fastcall tmrReadTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btnFilterQueryClick(TObject *Sender);
	void __fastcall chbShowPeriodClick(TObject *Sender);
	void __fastcall tmrDisplayTimer(TObject *Sender);
	void __fastcall chbCanFDClick(TObject *Sender);
	void __fastcall chbFDClick(TObject *Sender);
	void __fastcall chbRemoteClick(TObject *Sender);

private:	// User declarations
	// Variables to store the current PCANBasic instance
	//
	PCANBasicClass *m_objPCANBasic;
    // Saves the desired connection mode
    //
    bool m_IsFD;	
	// Saves the handle of a PCAN hardware
	//
	TPCANHandle m_PcanHandle;

	// Saves the baudrate register for a conenction
	//
	TPCANBaudrate m_Baudrate;

	// Saves the type of a non-plug-and-play hardware
	//
	TPCANType m_HwType;

	// Variables to store the current reading mode
	// 0 : Timer Mode
	// 1 : Event Mode
	// 2 : Manual Mode
	//
	int m_ActiveReadingMode;

	// CAN messages array. Store the message status for its display
	//
	TList *m_LastMsgsList;

	// Handle to set Received-Event
	//
	HANDLE m_hEvent;

	// Handle to the thread to read using Received-Event method
	//
	HANDLE m_hThread;

	// Handles of the current available PCAN-Hardware
	//
	TPCANHandle m_HandlesArray[59];
	// Handle for a Critical Section 
	//
	CRITICAL_SECTION *m_objpCS;

	void EnableDisableDataFields(int length);
	AnsiString FormatChannelName(TPCANHandle handle);
	AnsiString FormatChannelName(TPCANHandle handle, bool isFD);
	AnsiString GetTPCANHandleName(TPCANHandle handle);
	void FillComboBoxData();
	void ConfigureLogFile();
	void ConfigureTraceFile();
	void SetConnectionStatus(bool bConnected);
	void ReadingModeChanged();

	TPCANStatus ReadMessageFD();
	TPCANStatus ReadMessage();
	void ReadMessages();

	TPCANStatus WriteFrame();
	TPCANStatus WriteFrameFD();	

	void ProcessMessage(TPCANMsgFD theMsg, TPCANTimestampFD itsTimeStamp);
	void ProcessMessage(TPCANMsg MyMsg, TPCANTimestamp itsTimeStamp);
	void InsertMsgEntry(TPCANMsgFD NewMsg, TPCANTimestampFD itsTimeStamp);
	void DisplayMessages();
	void IncludeTextMessage(AnsiString strMsg);
	bool GetFilterStatus(int* status);

	AnsiString GetFormatedError(TPCANStatus error);

	// Static Thread function to manage reading by event
	//
	static DWORD WINAPI CallCANReadThreadFunc(LPVOID lpParam);
	// Member Thread function to manage reading by event
	//
	DWORD CANReadThreadFunc();

	// Critical section Ini/deinit functions
	//
	void InitializeProtection();
	void FinalizeProtection();

public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	void InitializeControls(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
