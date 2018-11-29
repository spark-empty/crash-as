using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

/// <summary>
/// Inclusion of PEAK PCAN-Basic namespace
/// </summary>
using Peak.Can.Basic;
using TPCANHandle = System.UInt16;
using TPCANBitrateFD = System.String;
using TPCANTimestampFD = System.UInt64;

namespace ICDIBasic
{
    public partial class Form1 : Form
    {
        #region Structures
        /// <summary>
        /// Message Status structure used to show CAN Messages
        /// in a ListView
        /// </summary>
        private class MessageStatus
        {
            private TPCANMsgFD m_Msg;
            private TPCANTimestampFD m_TimeStamp;
            private TPCANTimestampFD m_oldTimeStamp;
            private int m_iIndex;
            private int m_Count;
            private bool m_bShowPeriod;
            private bool m_bWasChanged;

            public MessageStatus(TPCANMsgFD canMsg, TPCANTimestampFD canTimestamp, int listIndex)
            {
                m_Msg = canMsg;
                m_TimeStamp = canTimestamp;
                m_oldTimeStamp = canTimestamp;
                m_iIndex = listIndex;
                m_Count = 1;
                m_bShowPeriod = true;
                m_bWasChanged = false;
            }

            public void Update(TPCANMsgFD canMsg, TPCANTimestampFD canTimestamp)
            {
                m_Msg = canMsg;
                m_oldTimeStamp = m_TimeStamp;
                m_TimeStamp = canTimestamp;
                m_bWasChanged = true;
                m_Count += 1;
            }

            public TPCANMsgFD CANMsg
            {
                get { return m_Msg; }
            }

            public TPCANTimestampFD Timestamp
            {
                get { return m_TimeStamp; }
            }

            public int Position
            {
                get { return m_iIndex; }
            }

            public string TypeString
            {
                get { return GetMsgTypeString(); }
            }

            public string IdString
            {
                get { return GetIdString(); }
            }

            public string DataString
            {
                get { return GetDataString(); }
            }

            public int Count
            {
                get { return m_Count; }
            }

            public bool ShowingPeriod
            {
                get { return m_bShowPeriod; }
                set
                {
                    if (m_bShowPeriod ^ value)
                    {
                        m_bShowPeriod = value;
                        m_bWasChanged = true;
                    }
                }
            }

            public bool MarkedAsUpdated
            {
                get { return m_bWasChanged; }
                set { m_bWasChanged = value; }
            }

            public string TimeString
            {
                get { return GetTimeString(); }
            }

            private string GetTimeString()
            {
                double fTime;

                fTime = (m_TimeStamp / 1000.0);
                if (m_bShowPeriod)
                    fTime -= (m_oldTimeStamp / 1000.0);
                return fTime.ToString("F1");
            }

            private string GetDataString()
            {
                string strTemp;

                strTemp = "";

                if ((m_Msg.MSGTYPE & TPCANMessageType.PCAN_MESSAGE_RTR) == TPCANMessageType.PCAN_MESSAGE_RTR)
                    return "Remote Request";
                else
                    for (int i = 0; i < Form1.GetLengthFromDLC(m_Msg.DLC, (m_Msg.MSGTYPE & TPCANMessageType.PCAN_MESSAGE_FD) == 0); i++)
                        strTemp += string.Format("{0:X2} ", m_Msg.DATA[i]);

                return strTemp;
            }

            private string GetIdString()
            {
                // We format the ID of the message and show it
                //
                if ((m_Msg.MSGTYPE & TPCANMessageType.PCAN_MESSAGE_EXTENDED) == TPCANMessageType.PCAN_MESSAGE_EXTENDED)
                    return string.Format("{0:X8}h", m_Msg.ID);
                else
                    return string.Format("{0:X3}h", m_Msg.ID);
            }

            private string GetMsgTypeString()
            {
                string strTemp;

                if ((m_Msg.MSGTYPE & TPCANMessageType.PCAN_MESSAGE_STATUS) == TPCANMessageType.PCAN_MESSAGE_STATUS)
                    return "STATUS";

                if ((m_Msg.MSGTYPE & TPCANMessageType.PCAN_MESSAGE_ERRFRAME) == TPCANMessageType.PCAN_MESSAGE_ERRFRAME)
                    return "ERROR";

                if ((m_Msg.MSGTYPE & TPCANMessageType.PCAN_MESSAGE_EXTENDED) == TPCANMessageType.PCAN_MESSAGE_EXTENDED)
                    strTemp = "EXT";
                else
                    strTemp = "STD";

                if ((m_Msg.MSGTYPE & TPCANMessageType.PCAN_MESSAGE_RTR) == TPCANMessageType.PCAN_MESSAGE_RTR)
                    strTemp += "/RTR";
                else
                    if ((int)m_Msg.MSGTYPE > (int)TPCANMessageType.PCAN_MESSAGE_EXTENDED)
                    {
                        strTemp += " [ ";
                        if ((m_Msg.MSGTYPE & TPCANMessageType.PCAN_MESSAGE_FD) == TPCANMessageType.PCAN_MESSAGE_FD)
                            strTemp += " FD";
                        if ((m_Msg.MSGTYPE & TPCANMessageType.PCAN_MESSAGE_BRS) == TPCANMessageType.PCAN_MESSAGE_BRS)
                            strTemp += " BRS";
                        if ((m_Msg.MSGTYPE & TPCANMessageType.PCAN_MESSAGE_ESI) == TPCANMessageType.PCAN_MESSAGE_ESI)
                            strTemp += " ESI";
                        strTemp += " ]";
                    }

                return strTemp;
            }

        }
        #endregion

        #region Delegates
        /// <summary>
        /// Read-Delegate Handler
        /// </summary>
        private delegate void ReadDelegateHandler();
        #endregion

        #region Members
        /// <summary>
        /// Saves the desired connection mode
        /// </summary>
        private bool m_IsFD;
        /// <summary>
        /// Saves the handle of a PCAN hardware
        /// </summary>
        private TPCANHandle m_PcanHandle;
        /// <summary>
        /// Saves the baudrate register for a conenction
        /// </summary>
        private TPCANBaudrate m_Baudrate;
        /// <summary>
        /// Saves the type of a non-plug-and-play hardware
        /// </summary>
        private TPCANType m_HwType;
        /// <summary>
        /// Stores the status of received messages for its display
        /// </summary>
        private System.Collections.ArrayList m_LastMsgsList;
        /// <summary>
        /// Read Delegate for calling the function "ReadMessages"
        /// </summary>
        private ReadDelegateHandler m_ReadDelegate;
        /// <summary>
        /// Receive-Event
        /// </summary>
        private System.Threading.AutoResetEvent m_ReceiveEvent;
        /// <summary>
        /// Thread for message reading (using events)
        /// </summary>
        private System.Threading.Thread m_ReadThread;
        /// <summary>
        /// Handles of the current available PCAN-Hardware
        /// </summary>
        private TPCANHandle[] m_HandlesArray;
        #endregion

        #region Methods
        #region Help functions
        /// <summary>
        /// Convert a CAN DLC value into the actual data length of the CAN/CAN-FD frame.
        /// </summary>
        /// <param name="dlc">A value between 0 and 15 (CAN and FD DLC range)</param>
        /// <param name="isSTD">A value indicating if the msg is a standard CAN (FD Flag not checked)</param>
        /// <returns>The length represented by the DLC</returns>
        public static int GetLengthFromDLC(int dlc, bool isSTD)
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

        /// <summary>
        /// Initialization of PCAN-Basic components
        /// </summary>
        private void InitializeBasicComponents()
        {
            // Creates the list for received messages
            //
            m_LastMsgsList = new System.Collections.ArrayList();
            // Creates the delegate used for message reading
            //
            m_ReadDelegate = new ReadDelegateHandler(ReadMessages);
            // Creates the event used for signalize incomming messages 
            //
            m_ReceiveEvent = new System.Threading.AutoResetEvent(false);
            // Creates an array with all possible PCAN-Channels
            //
            m_HandlesArray = new TPCANHandle[] 
            { 
                PCANBasic.PCAN_ISABUS1,
                PCANBasic.PCAN_ISABUS2,
                PCANBasic.PCAN_ISABUS3,
                PCANBasic.PCAN_ISABUS4,
                PCANBasic.PCAN_ISABUS5,
                PCANBasic.PCAN_ISABUS6,
                PCANBasic.PCAN_ISABUS7,
                PCANBasic.PCAN_ISABUS8,
                PCANBasic.PCAN_DNGBUS1,
                PCANBasic.PCAN_PCIBUS1,
                PCANBasic.PCAN_PCIBUS2,
                PCANBasic.PCAN_PCIBUS3,
                PCANBasic.PCAN_PCIBUS4,
                PCANBasic.PCAN_PCIBUS5,
                PCANBasic.PCAN_PCIBUS6,
                PCANBasic.PCAN_PCIBUS7,
                PCANBasic.PCAN_PCIBUS8,
                PCANBasic.PCAN_PCIBUS9,
                PCANBasic.PCAN_PCIBUS10,
                PCANBasic.PCAN_PCIBUS11,
                PCANBasic.PCAN_PCIBUS12,
                PCANBasic.PCAN_PCIBUS13,
                PCANBasic.PCAN_PCIBUS14,
                PCANBasic.PCAN_PCIBUS15,
                PCANBasic.PCAN_PCIBUS16,
                PCANBasic.PCAN_USBBUS1,
                PCANBasic.PCAN_USBBUS2,
                PCANBasic.PCAN_USBBUS3,
                PCANBasic.PCAN_USBBUS4,
                PCANBasic.PCAN_USBBUS5,
                PCANBasic.PCAN_USBBUS6,
                PCANBasic.PCAN_USBBUS7,
                PCANBasic.PCAN_USBBUS8,
                PCANBasic.PCAN_USBBUS9,
                PCANBasic.PCAN_USBBUS10,
                PCANBasic.PCAN_USBBUS11,
                PCANBasic.PCAN_USBBUS12,
                PCANBasic.PCAN_USBBUS13,
                PCANBasic.PCAN_USBBUS14,
                PCANBasic.PCAN_USBBUS15,
                PCANBasic.PCAN_USBBUS16,
                PCANBasic.PCAN_PCCBUS1,
                PCANBasic.PCAN_PCCBUS2,
                PCANBasic.PCAN_LANBUS1,
                PCANBasic.PCAN_LANBUS2,
                PCANBasic.PCAN_LANBUS3,
                PCANBasic.PCAN_LANBUS4,
                PCANBasic.PCAN_LANBUS5,
                PCANBasic.PCAN_LANBUS6,
                PCANBasic.PCAN_LANBUS7,
                PCANBasic.PCAN_LANBUS8,
                PCANBasic.PCAN_LANBUS9,
                PCANBasic.PCAN_LANBUS10,
                PCANBasic.PCAN_LANBUS11,
                PCANBasic.PCAN_LANBUS12,
                PCANBasic.PCAN_LANBUS13,
                PCANBasic.PCAN_LANBUS14,
                PCANBasic.PCAN_LANBUS15,
                PCANBasic.PCAN_LANBUS16,
            };

            // Fills and configures the Data of several comboBox components
            //
            FillComboBoxData();

            // Prepares the PCAN-Basic's debug-Log file
            //
            ConfigureLogFile();
        }

        /// <summary>
        /// Configures the Debug-Log file of PCAN-Basic
        /// </summary>
        private void ConfigureLogFile()
        {
            UInt32 iBuffer;

            // Sets the mask to catch all events
            //
            iBuffer = PCANBasic.LOG_FUNCTION_ALL;

            // Configures the log file. 
            // NOTE: The Log capability is to be used with the NONEBUS Handle. Other handle than this will 
            // cause the function fail.
            //
            PCANBasic.SetValue(PCANBasic.PCAN_NONEBUS, TPCANParameter.PCAN_LOG_CONFIGURE, ref iBuffer, sizeof(UInt32));
        }

        /// <summary>
        /// Configures the PCAN-Trace file for a PCAN-Basic Channel
        /// </summary>
        private void ConfigureTraceFile()
        {
            UInt32 iBuffer;
            TPCANStatus stsResult;

            // Configure the maximum size of a trace file to 5 megabytes
            //
            iBuffer = 5;
            stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_TRACE_SIZE, ref iBuffer, sizeof(UInt32));
            if (stsResult != TPCANStatus.PCAN_ERROR_OK)
                IncludeTextMessage(GetFormatedError(stsResult));

            // Configure the way how trace files are created: 
            // * Standard name is used
            // * Existing file is ovewritten, 
            // * Only one file is created.
            // * Recording stopts when the file size reaches 5 megabytes.
            //
            iBuffer = PCANBasic.TRACE_FILE_SINGLE | PCANBasic.TRACE_FILE_OVERWRITE;
            stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_TRACE_CONFIGURE, ref iBuffer, sizeof(UInt32));
            if (stsResult != TPCANStatus.PCAN_ERROR_OK)
                IncludeTextMessage(GetFormatedError(stsResult));
        }

        /// <summary>
        /// Help Function used to get an error as text
        /// </summary>
        /// <param name="error">Error code to be translated</param>
        /// <returns>A text with the translated error</returns>
        private string GetFormatedError(TPCANStatus error)
        {
            StringBuilder strTemp;

            // Creates a buffer big enough for a error-text
            //
            strTemp = new StringBuilder(256);
            // Gets the text using the GetErrorText API function
            // If the function success, the translated error is returned. If it fails,
            // a text describing the current error is returned.
            //
            if (PCANBasic.GetErrorText(error, 0, strTemp) != TPCANStatus.PCAN_ERROR_OK)
                return string.Format("An error occurred. Error-code's text ({0:X}) couldn't be retrieved", error);
            else
                return strTemp.ToString();
        }

        /// <summary>
        /// Includes a new line of text into the information Listview
        /// </summary>
        /// <param name="strMsg">Text to be included</param>
        private void IncludeTextMessage(string strMsg)
        {
            lbxInfo.Items.Add(strMsg);
            lbxInfo.SelectedIndex = lbxInfo.Items.Count - 1;
        }

        /// <summary>
        /// Gets the current status of the PCAN-Basic message filter
        /// </summary>
        /// <param name="status">Buffer to retrieve the filter status</param>
        /// <returns>If calling the function was successfull or not</returns>
        private bool GetFilterStatus(out uint status)
        {
            TPCANStatus stsResult;

            // Tries to get the sttaus of the filter for the current connected hardware
            //
            stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_MESSAGE_FILTER, out status, sizeof(UInt32));

            // If it fails, a error message is shown
            //
            if (stsResult != TPCANStatus.PCAN_ERROR_OK)
            {
                MessageBox.Show(GetFormatedError(stsResult));
                return false;
            }
            return true;
        }

        /// <summary>
        /// Configures the data of all ComboBox components of the main-form
        /// </summary>
        private void FillComboBoxData()
        {
            // Channels will be check
            //
            btnHwRefresh_Click(this, new EventArgs());

            // FD Bitrate: 
            //      Arbitration: 1 Mbit/sec 
            //      Data: 2 Mbit/sec
            //
            txtBitrate.Text = "f_clock_mhz=20, nom_brp=5, nom_tseg1=2, nom_tseg2=1, nom_sjw=1, data_brp=2, data_tseg1=3, data_tseg2=1, data_sjw=1";

            // Baudrates 
            //
            cbbBaudrates.SelectedIndex = 2; // 500 K

            // Hardware Type for no plugAndplay hardware
            //
            cbbHwType.SelectedIndex = 0;

            // Interrupt for no plugAndplay hardware
            //
            cbbInterrupt.SelectedIndex = 0;

            // IO Port for no plugAndplay hardware
            //
            cbbIO.SelectedIndex = 0;

            // Parameters for GetValue and SetValue function calls
            //
            cbbParameter.SelectedIndex = 0;
        }

        /// <summary>
        /// Activates/deaactivates the different controls of the main-form according
        /// with the current connection status
        /// </summary>
        /// <param name="bConnected">Current status. True if connected, false otherwise</param>
        private void SetConnectionStatus(bool bConnected)
        {
            // Buttons
            //
            btnInit.Enabled = !bConnected;
            btnRead.Enabled = bConnected && rdbManual.Checked;
            btnWrite.Enabled = bConnected;
            btnRelease.Enabled = bConnected;
            btnFilterApply.Enabled = bConnected;
            btnFilterQuery.Enabled = bConnected;
            btnGetVersions.Enabled = bConnected;
            btnHwRefresh.Enabled = !bConnected;
            btnStatus.Enabled = bConnected;
            btnReset.Enabled = bConnected;

            // ComboBoxs
            //
            cbbChannel.Enabled = !bConnected;
            cbbBaudrates.Enabled = !bConnected;
            cbbHwType.Enabled = !bConnected;
            cbbIO.Enabled = !bConnected;
            cbbInterrupt.Enabled = !bConnected;

            // Check-Buttons
            //
            chbCanFD.Enabled = !bConnected;

            // Hardware configuration and read mode
            //
            if (!bConnected)
                cbbChannel_SelectedIndexChanged(this, new EventArgs());
            else
                rdbTimer_CheckedChanged(this, new EventArgs());

            // Display messages in grid
            //
            tmrDisplay.Enabled = bConnected;
        }

        /// <summary>
        /// Gets the formated text for a PCAN-Basic channel handle
        /// </summary>
        /// <param name="handle">PCAN-Basic Handle to format</param>
        /// <param name="isFD">If the channel is FD capable</param>
        /// <returns>The formatted text for a channel</returns>
        private string FormatChannelName(TPCANHandle handle, bool isFD)
        {
            TPCANDevice devDevice;
            byte byChannel;

            // Gets the owner device and channel for a 
            // PCAN-Basic handle
            //
            if (handle < 0x100)
            {
                devDevice = (TPCANDevice)(handle >> 4);
                byChannel = (byte)(handle & 0xF);
            }
            else
            {
                devDevice = (TPCANDevice)(handle >> 8);
                byChannel = (byte)(handle & 0xFF);
            }

            // Constructs the PCAN-Basic Channel name and return it
            //
            if (isFD)
                return string.Format("{0}:FD {1} ({2:X2}h)", devDevice, byChannel, handle);
            else
                return string.Format("{0} {1} ({2:X2}h)", devDevice, byChannel, handle);
        }

        /// <summary>
        /// Gets the formated text for a PCAN-Basic channel handle
        /// </summary>
        /// <param name="handle">PCAN-Basic Handle to format</param>
        /// <returns>The formatted text for a channel</returns>
        private string FormatChannelName(TPCANHandle handle)
        {
            return FormatChannelName(handle, false);
        }
        #endregion

        #region Message-proccessing functions
        /// <summary>
        /// Display CAN messages in the Message-ListView
        /// </summary>
        private void DisplayMessages()
        {
            ListViewItem lviCurrentItem;

            lock (m_LastMsgsList.SyncRoot)
            {
                foreach (MessageStatus msgStatus in m_LastMsgsList)
                {
                    // Get the data to actualize
                    //
                    if (msgStatus.MarkedAsUpdated)
                    {
                        msgStatus.MarkedAsUpdated = false;
                        lviCurrentItem = lstMessages.Items[msgStatus.Position];

                        lviCurrentItem.SubItems[2].Text = GetLengthFromDLC(msgStatus.CANMsg.DLC, (msgStatus.CANMsg.MSGTYPE & TPCANMessageType.PCAN_MESSAGE_FD) == 0).ToString();
                        lviCurrentItem.SubItems[3].Text = msgStatus.Count.ToString();
                        lviCurrentItem.SubItems[4].Text = msgStatus.TimeString;
                        lviCurrentItem.SubItems[5].Text = msgStatus.DataString;
                    }
                }
            }
        }

        /// <summary>
        /// Inserts a new entry for a new message in the Message-ListView
        /// </summary>
        /// <param name="newMsg">The messasge to be inserted</param>
        /// <param name="timeStamp">The Timesamp of the new message</param>
        private void InsertMsgEntry(TPCANMsgFD newMsg, TPCANTimestampFD timeStamp)
        {
            MessageStatus msgStsCurrentMsg;
            ListViewItem lviCurrentItem;

            lock (m_LastMsgsList.SyncRoot)
            {
                // We add this status in the last message list
                //
                msgStsCurrentMsg = new MessageStatus(newMsg, timeStamp, lstMessages.Items.Count);
                msgStsCurrentMsg.ShowingPeriod = chbShowPeriod.Checked;
                m_LastMsgsList.Add(msgStsCurrentMsg);

                // Add the new ListView Item with the Type of the message
                //	
                lviCurrentItem = lstMessages.Items.Add(msgStsCurrentMsg.TypeString);
                // We set the ID of the message
                //
                lviCurrentItem.SubItems.Add(msgStsCurrentMsg.IdString);
                // We set the length of the Message
                //
                lviCurrentItem.SubItems.Add(GetLengthFromDLC(newMsg.DLC, (newMsg.MSGTYPE & TPCANMessageType.PCAN_MESSAGE_FD) == 0).ToString());
                // we set the message count message (this is the First, so count is 1)            
                //
                lviCurrentItem.SubItems.Add(msgStsCurrentMsg.Count.ToString());
                // Add time stamp information if needed
                //
                lviCurrentItem.SubItems.Add(msgStsCurrentMsg.TimeString);
                // We set the data of the message. 	
                //
                lviCurrentItem.SubItems.Add(msgStsCurrentMsg.DataString);
            }
        }

        /// <summary>
        /// Processes a received message, in order to show it in the Message-ListView
        /// </summary>
        /// <param name="theMsg">The received PCAN-Basic message</param>
        /// <returns>True if the message must be created, false if it must be modified</returns>
        private void ProcessMessage(TPCANMsgFD theMsg, TPCANTimestampFD itsTimeStamp)
        {
            // We search if a message (Same ID and Type) is 
            // already received or if this is a new message
            //
            lock (m_LastMsgsList.SyncRoot)
            {
                foreach (MessageStatus msg in m_LastMsgsList)
                {
                    if ((msg.CANMsg.ID == theMsg.ID) && (msg.CANMsg.MSGTYPE == theMsg.MSGTYPE))
                    {
                        // Modify the message and exit
                        //
                        msg.Update(theMsg, itsTimeStamp);
                        return;
                    }
                }
                // Message not found. It will created
                //
                InsertMsgEntry(theMsg, itsTimeStamp);
            }
        }

        /// <summary>
        /// Processes a received message, in order to show it in the Message-ListView
        /// </summary>
        /// <param name="theMsg">The received PCAN-Basic message</param>
        /// <returns>True if the message must be created, false if it must be modified</returns>
        private void ProcessMessage(TPCANMsg theMsg, TPCANTimestamp itsTimeStamp)
        {
            TPCANMsgFD newMsg;
            TPCANTimestampFD newTimestamp;

            newMsg = new TPCANMsgFD();
            newMsg.DATA = new byte[64];
            newMsg.ID = theMsg.ID;
            newMsg.DLC = theMsg.LEN;
            for (int i = 0; i < ((theMsg.LEN > 8) ? 8 : theMsg.LEN); i++)
                newMsg.DATA[i] = theMsg.DATA[i];
            newMsg.MSGTYPE = theMsg.MSGTYPE;

            newTimestamp = Convert.ToUInt64(itsTimeStamp.micros + 1000 * itsTimeStamp.millis + 0x100000000 * 1000 * itsTimeStamp.millis_overflow);
            ProcessMessage(newMsg, newTimestamp);
        }

        /// <summary>
        /// Thread-Function used for reading PCAN-Basic messages
        /// </summary>
        private void CANReadThreadFunc()
        {
            UInt32 iBuffer;
            TPCANStatus stsResult;

            iBuffer = Convert.ToUInt32(m_ReceiveEvent.SafeWaitHandle.DangerousGetHandle().ToInt32());
            // Sets the handle of the Receive-Event.
            //
            stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_RECEIVE_EVENT, ref iBuffer, sizeof(UInt32));

            if (stsResult != TPCANStatus.PCAN_ERROR_OK)
            {
                MessageBox.Show(GetFormatedError(stsResult), "Error!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            // While this mode is selected
            while (rdbEvent.Checked)
            {
                // Waiting for Receive-Event
                // 
                if (m_ReceiveEvent.WaitOne(50))
                    // Process Receive-Event using .NET Invoke function
                    // in order to interact with Winforms UI (calling the 
                    // function ReadMessages)
                    // 
                    this.Invoke(m_ReadDelegate);
            }
        }

        /// <summary>
        /// Function for reading messages on FD devices
        /// </summary>
        /// <returns>A TPCANStatus error code</returns>
        private TPCANStatus ReadMessageFD()
        {
            TPCANMsgFD CANMsg;
            TPCANTimestampFD CANTimeStamp;
            TPCANStatus stsResult;

            // We execute the "Read" function of the PCANBasic                
            //
            stsResult = PCANBasic.ReadFD(m_PcanHandle, out CANMsg, out CANTimeStamp);
            if (stsResult != TPCANStatus.PCAN_ERROR_QRCVEMPTY)
                // We process the received message
                //
                ProcessMessage(CANMsg, CANTimeStamp);

            return stsResult;
        }

        /// <summary>
        /// Function for reading CAN messages on normal CAN devices
        /// </summary>
        /// <returns>A TPCANStatus error code</returns>
        private TPCANStatus ReadMessage()
        {
            TPCANMsg CANMsg;
            TPCANTimestamp CANTimeStamp;
            TPCANStatus stsResult;

            // We execute the "Read" function of the PCANBasic                
            //
            stsResult = PCANBasic.Read(m_PcanHandle, out CANMsg, out CANTimeStamp);
            if (stsResult != TPCANStatus.PCAN_ERROR_QRCVEMPTY)
                // We process the received message
                //
                ProcessMessage(CANMsg, CANTimeStamp);

            return stsResult;
        }

        /// <summary>
        /// Function for reading PCAN-Basic messages
        /// </summary>
        private void ReadMessages()
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
                if (stsResult == TPCANStatus.PCAN_ERROR_ILLOPERATION)
                    break;
            } while (btnRelease.Enabled && (!Convert.ToBoolean(stsResult & TPCANStatus.PCAN_ERROR_QRCVEMPTY)));
        }
        #endregion

        #region Event Handlers
        #region Form event-handlers
        /// <summary>
        /// Consturctor
        /// </summary>
        public Form1()
        {
            // Initializes Form's component
            //
            InitializeComponent();
            // Initializes specific components
            //
            InitializeBasicComponents();
        }

        /// <summary>
        /// Form-Closing Function / Finish function
        /// </summary>
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            // Releases the used PCAN-Basic channel
            //
            if (btnRelease.Enabled)
                btnRelease_Click(this, new EventArgs());
        }
        #endregion

        #region ComboBox event-handlers
        private void cbbChannel_SelectedIndexChanged(object sender, EventArgs e)
        {
            bool bNonPnP;
            string strTemp;

            // Get the handle fromt he text being shown
            //
            strTemp = cbbChannel.Text;
            strTemp = strTemp.Substring(strTemp.IndexOf('(') + 1, 3);

            strTemp = strTemp.Replace('h', ' ').Trim(' ');

            // Determines if the handle belong to a No Plug&Play hardware 
            //
            m_PcanHandle = Convert.ToUInt16(strTemp, 16);
            bNonPnP = m_PcanHandle <= PCANBasic.PCAN_DNGBUS1;
            // Activates/deactivates configuration controls according with the 
            // kind of hardware
            //
            cbbHwType.Enabled = bNonPnP;
            cbbIO.Enabled = bNonPnP;
            cbbInterrupt.Enabled = bNonPnP;
        }

        private void cbbBaudrates_SelectedIndexChanged(object sender, EventArgs e)
        {
            // Saves the current selected baudrate register code
            //
            switch (cbbBaudrates.SelectedIndex)
            {
                case 0:
                    m_Baudrate = TPCANBaudrate.PCAN_BAUD_1M;
                    break;
                case 1:
                    m_Baudrate = TPCANBaudrate.PCAN_BAUD_800K;
                    break;
                case 2:
                    m_Baudrate = TPCANBaudrate.PCAN_BAUD_500K;
                    break;
                case 3:
                    m_Baudrate = TPCANBaudrate.PCAN_BAUD_250K;
                    break;
                case 4:
                    m_Baudrate = TPCANBaudrate.PCAN_BAUD_125K;
                    break;
                case 5:
                    m_Baudrate = TPCANBaudrate.PCAN_BAUD_100K;
                    break;
                case 6:
                    m_Baudrate = TPCANBaudrate.PCAN_BAUD_95K;
                    break;
                case 7:
                    m_Baudrate = TPCANBaudrate.PCAN_BAUD_83K;
                    break;
                case 8:
                    m_Baudrate = TPCANBaudrate.PCAN_BAUD_50K;
                    break;
                case 9:
                    m_Baudrate = TPCANBaudrate.PCAN_BAUD_47K;
                    break;
                case 10:
                    m_Baudrate = TPCANBaudrate.PCAN_BAUD_33K;
                    break;
                case 11:
                    m_Baudrate = TPCANBaudrate.PCAN_BAUD_20K;
                    break;
                case 12:
                    m_Baudrate = TPCANBaudrate.PCAN_BAUD_10K;
                    break;
                case 13:
                    m_Baudrate = TPCANBaudrate.PCAN_BAUD_5K;
                    break;
            }
        }

        private void cbbHwType_SelectedIndexChanged(object sender, EventArgs e)
        {
            // Saves the current type for a no-Plug&Play hardware
            //
            switch (cbbHwType.SelectedIndex)
            {
                case 0:
                    m_HwType = TPCANType.PCAN_TYPE_ISA;
                    break;
                case 1:
                    m_HwType = TPCANType.PCAN_TYPE_ISA_SJA;
                    break;
                case 2:
                    m_HwType = TPCANType.PCAN_TYPE_ISA_PHYTEC;
                    break;
                case 3:
                    m_HwType = TPCANType.PCAN_TYPE_DNG;
                    break;
                case 4:
                    m_HwType = TPCANType.PCAN_TYPE_DNG_EPP;
                    break;
                case 5:
                    m_HwType = TPCANType.PCAN_TYPE_DNG_SJA;
                    break;
                case 6:
                    m_HwType = TPCANType.PCAN_TYPE_DNG_SJA_EPP;
                    break;
            }
        }

        private void cbbParameter_SelectedIndexChanged(object sender, EventArgs e)
        {
            // Activates/deactivates controls according with the selected 
            // PCAN-Basic parameter 
            //
            rdbParamActive.Enabled = (cbbParameter.SelectedIndex != 0) && (cbbParameter.SelectedIndex != 20);
            rdbParamInactive.Enabled = rdbParamActive.Enabled;
            nudDeviceIdOrDelay.Enabled = !rdbParamActive.Enabled;
            laDeviceOrDelay.Text = (cbbParameter.SelectedIndex == 20) ? "Delay (μs):" : "Device ID:";
        }
        #endregion

        #region Button event-handlers
        private void btnHwRefresh_Click(object sender, EventArgs e)
        {
            UInt32 iBuffer;
            TPCANStatus stsResult;
            bool isFD;

            // Clears the Channel combioBox and fill it again with 
            // the PCAN-Basic handles for no-Plug&Play hardware and
            // the detected Plug&Play hardware
            //
            cbbChannel.Items.Clear();
            try
            {
                for (int i = 0; i < m_HandlesArray.Length; i++)
                {
                    // Includes all no-Plug&Play Handles
                    if (m_HandlesArray[i] <= PCANBasic.PCAN_DNGBUS1)
                        cbbChannel.Items.Add(FormatChannelName(m_HandlesArray[i]));
                    else
                    {
                        // Checks for a Plug&Play Handle and, according with the return value, includes it
                        // into the list of available hardware channels.
                        //
                        stsResult = PCANBasic.GetValue(m_HandlesArray[i], TPCANParameter.PCAN_CHANNEL_CONDITION, out iBuffer, sizeof(UInt32));
                        if ((stsResult == TPCANStatus.PCAN_ERROR_OK) && ((iBuffer & PCANBasic.PCAN_CHANNEL_AVAILABLE) == PCANBasic.PCAN_CHANNEL_AVAILABLE))
                        {
                            stsResult = PCANBasic.GetValue(m_HandlesArray[i], TPCANParameter.PCAN_CHANNEL_FEATURES, out iBuffer, sizeof(UInt32));
                            isFD = (stsResult == TPCANStatus.PCAN_ERROR_OK) && ((iBuffer & PCANBasic.FEATURE_FD_CAPABLE) == PCANBasic.FEATURE_FD_CAPABLE);
                            cbbChannel.Items.Add(FormatChannelName(m_HandlesArray[i], isFD));
                        }
                    }
                }
                cbbChannel.SelectedIndex = cbbChannel.Items.Count - 1;
                btnInit.Enabled = cbbChannel.Items.Count > 0;
            }
            catch (DllNotFoundException)
            {
                MessageBox.Show("Unable to find the library: PCANBasic.dll !", "Error!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                Environment.Exit(-1);
            }
        }

        private void btnInit_Click(object sender, EventArgs e)
        {
            TPCANStatus stsResult;

            // Connects a selected PCAN-Basic channel
            //
            if (m_IsFD)
                stsResult = PCANBasic.InitializeFD(
                    m_PcanHandle,
                    txtBitrate.Text);
            else
                stsResult = PCANBasic.Initialize(
                    m_PcanHandle,
                    m_Baudrate,
                    m_HwType,
                    Convert.ToUInt32(cbbIO.Text, 16),
                    Convert.ToUInt16(cbbInterrupt.Text));

            if (stsResult != TPCANStatus.PCAN_ERROR_OK)
                if (stsResult != TPCANStatus.PCAN_ERROR_CAUTION)
                    MessageBox.Show(GetFormatedError(stsResult));
                else
                {
                    IncludeTextMessage("******************************************************");
                    IncludeTextMessage("The bitrate being used is different than the given one");
                    IncludeTextMessage("******************************************************");
                    stsResult = TPCANStatus.PCAN_ERROR_OK;
                }
            else
                // Prepares the PCAN-Basic's PCAN-Trace file
                //
                ConfigureTraceFile();

            // Sets the connection status of the main-form
            //
            SetConnectionStatus(stsResult == TPCANStatus.PCAN_ERROR_OK);
        }

        private void btnRelease_Click(object sender, EventArgs e)
        {
            // Releases a current connected PCAN-Basic channel
            //
            PCANBasic.Uninitialize(m_PcanHandle);
            tmrRead.Enabled = false;
            if (m_ReadThread != null)
            {
                m_ReadThread.Abort();
                m_ReadThread.Join();
                m_ReadThread = null;
            }

            // Sets the connection status of the main-form
            //
            SetConnectionStatus(false);
        }

        private void btnFilterApply_Click(object sender, EventArgs e)
        {
            UInt32 iBuffer;
            TPCANStatus stsResult;

            // Gets the current status of the message filter
            //
            if (!GetFilterStatus(out iBuffer))
                return;

            // Configures the message filter for a custom range of messages
            //
            if (rdbFilterCustom.Checked)
            {
                // Sets the custom filter
                //
                stsResult = PCANBasic.FilterMessages(
                m_PcanHandle,
                Convert.ToUInt32(nudIdFrom.Value),
                Convert.ToUInt32(nudIdTo.Value),
                chbFilterExt.Checked ? TPCANMode.PCAN_MODE_EXTENDED : TPCANMode.PCAN_MODE_STANDARD);
                // If success, an information message is written, if it is not, an error message is shown
                //
                if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                    IncludeTextMessage(string.Format("The filter was customized. IDs from {0:X} to {1:X} will be received", nudIdFrom.Text, nudIdTo.Text));
                else
                    MessageBox.Show(GetFormatedError(stsResult));

                return;
            }

            // The filter will be full opened or complete closed
            //
            if (rdbFilterClose.Checked)
                iBuffer = PCANBasic.PCAN_FILTER_CLOSE;
            else
                iBuffer = PCANBasic.PCAN_FILTER_OPEN;

            // The filter is configured
            //
            stsResult = PCANBasic.SetValue(
                m_PcanHandle,
                TPCANParameter.PCAN_MESSAGE_FILTER,
                ref iBuffer,
                sizeof(UInt32));

            // If success, an information message is written, if it is not, an error message is shown
            //
            if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                IncludeTextMessage(string.Format("The filter was successfully {0}", rdbFilterClose.Checked ? "closed." : "opened."));
            else
                MessageBox.Show(GetFormatedError(stsResult));
        }

        private void btnFilterQuery_Click(object sender, EventArgs e)
        {
            UInt32 iBuffer;

            // Queries the current status of the message filter
            //
            if (GetFilterStatus(out iBuffer))
            {
                switch (iBuffer)
                {
                    // The filter is closed
                    //
                    case PCANBasic.PCAN_FILTER_CLOSE:
                        IncludeTextMessage("The Status of the filter is: closed.");
                        break;
                    // The filter is fully opened
                    //
                    case PCANBasic.PCAN_FILTER_OPEN:
                        IncludeTextMessage("The Status of the filter is: full opened.");
                        break;
                    // The filter is customized
                    //
                    case PCANBasic.PCAN_FILTER_CUSTOM:
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

        private void btnParameterSet_Click(object sender, EventArgs e)
        {
            TPCANStatus stsResult;
            UInt32 iBuffer;
            bool bActivate;

            bActivate = rdbParamActive.Checked;

            // Sets a PCAN-Basic parameter value
            //
            switch (cbbParameter.SelectedIndex)
            {
                // The Device-Number of an USB channel will be set
                //
                case 0:
                    iBuffer = Convert.ToUInt32(nudDeviceIdOrDelay.Value);
                    stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_DEVICE_NUMBER, ref iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage("The desired Device-Number was successfully configured");
                    break;
                // The 5 Volt Power feature of a PC-card or USB will be set
                //
                case 1:
                    iBuffer = (uint)(bActivate ? PCANBasic.PCAN_PARAMETER_ON : PCANBasic.PCAN_PARAMETER_OFF);
                    stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_5VOLTS_POWER, ref iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The USB/PC-Card 5 power was successfully {0}", bActivate ? "activated" : "deactivated"));
                    break;
                // The feature for automatic reset on BUS-OFF will be set
                //
                case 2:
                    iBuffer = (uint)(bActivate ? PCANBasic.PCAN_PARAMETER_ON : PCANBasic.PCAN_PARAMETER_OFF);
                    stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_BUSOFF_AUTORESET, ref iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The automatic-reset on BUS-OFF was successfully {0}", bActivate ? "activated" : "deactivated"));
                    break;
                // The CAN option "Listen Only" will be set
                //
                case 3:
                    iBuffer = (uint)(bActivate ? PCANBasic.PCAN_PARAMETER_ON : PCANBasic.PCAN_PARAMETER_OFF);
                    stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_LISTEN_ONLY, ref iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The CAN option \"Listen Only\" was successfully {0}", bActivate ? "activated" : "deactivated"));
                    break;
                // The feature for logging debug-information will be set
                //
                case 4:
                    iBuffer = (uint)(bActivate ? PCANBasic.PCAN_PARAMETER_ON : PCANBasic.PCAN_PARAMETER_OFF);
                    stsResult = PCANBasic.SetValue(PCANBasic.PCAN_NONEBUS, TPCANParameter.PCAN_LOG_STATUS, ref iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The feature for logging debug information was successfully {0}", bActivate ? "activated" : "deactivated"));
                    break;
                // The channel option "Receive Status" will be set
                //
                case 5:
                    iBuffer = (uint)(bActivate ? PCANBasic.PCAN_PARAMETER_ON : PCANBasic.PCAN_PARAMETER_OFF);
                    stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_RECEIVE_STATUS, ref iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The channel option \"Receive Status\" was set to {0}", bActivate ? "ON" : "OFF"));
                    break;
                // The feature for tracing will be set
                //
                case 7:
                    iBuffer = (uint)(bActivate ? PCANBasic.PCAN_PARAMETER_ON : PCANBasic.PCAN_PARAMETER_OFF);
                    stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_TRACE_STATUS, ref iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The feature for tracing data was successfully {0}", bActivate ? "activated" : "deactivated"));
                    break;

                // The feature for identifying an USB Channel will be set
                //
                case 8:
                    iBuffer = (uint)(bActivate ? PCANBasic.PCAN_PARAMETER_ON : PCANBasic.PCAN_PARAMETER_OFF);
                    stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_CHANNEL_IDENTIFYING, ref iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The procedure for channel identification was successfully {0}", bActivate ? "activated" : "deactivated"));
                    break;

                // The feature for using an already configured speed will be set
                //
                case 10:
                    iBuffer = (uint)(bActivate ? PCANBasic.PCAN_PARAMETER_ON : PCANBasic.PCAN_PARAMETER_OFF);
                    stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_BITRATE_ADAPTING, ref iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The feature for bit rate adaptation was successfully {0}", bActivate ? "activated" : "deactivated"));
                    break;
                
                // The option "Allow Status Frames" will be set
                //
                case 17:
                    iBuffer = (uint)(bActivate ? PCANBasic.PCAN_PARAMETER_ON : PCANBasic.PCAN_PARAMETER_OFF);
                    stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_ALLOW_STATUS_FRAMES, ref iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The reception of Status frames was successfully {0}", bActivate ? "enabled" : "disabled"));
                    break;

                // The option "Allow RTR Frames" will be set
                //
                case 18:
                    iBuffer = (uint)(bActivate ? PCANBasic.PCAN_PARAMETER_ON : PCANBasic.PCAN_PARAMETER_OFF);
                    stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_ALLOW_RTR_FRAMES, ref iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The reception of RTR frames was successfully {0}", bActivate ? "enabled" : "disabled"));
                    break;

                // The option "Allow Error Frames" will be set
                //
                case 19:
                    iBuffer = (uint)(bActivate ? PCANBasic.PCAN_PARAMETER_ON : PCANBasic.PCAN_PARAMETER_OFF);
                    stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_ALLOW_ERROR_FRAMES, ref iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The reception of Error frames was successfully {0}", bActivate ? "enabled" : "disabled"));
                    break;

                // The option "Interframes Delay" will be set
                //
                case 20:
                    iBuffer = Convert.ToUInt32(nudDeviceIdOrDelay.Value);
                    stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_INTERFRAME_DELAY, ref iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage("The delay between transmitting frames was successfully set");
                    break;

                // The current parameter is invalid
                //
                default:
                    stsResult = TPCANStatus.PCAN_ERROR_UNKNOWN;
                    MessageBox.Show("Wrong parameter code.");
                    return;
            }

            // If the function fail, an error message is shown
            //
            if (stsResult != TPCANStatus.PCAN_ERROR_OK)
                MessageBox.Show(GetFormatedError(stsResult));
        }

        private void btnParameterGet_Click(object sender, EventArgs e)
        {
            TPCANStatus stsResult;
            UInt32 iBuffer;
            StringBuilder strBuffer;

            strBuffer = new StringBuilder(255);

            // Gets a PCAN-Basic parameter value
            //
            switch (cbbParameter.SelectedIndex)
            {
                // The Device-Number of an USB channel will be retrieved
                //
                case 0:
                    stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_DEVICE_NUMBER, out iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The configured Device-Number is {0:X}h", iBuffer));
                    break;
                // The activation status of the 5 Volt Power feature of a PC-card or USB will be retrieved
                //
                case 1:
                    stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_5VOLTS_POWER, out iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The 5-Volt Power of the USB/PC-Card is {0}", (iBuffer == PCANBasic.PCAN_PARAMETER_ON) ? "ON" : "OFF"));
                    break;
                // The activation status of the feature for automatic reset on BUS-OFF will be retrieved
                //
                case 2:
                    stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_BUSOFF_AUTORESET, out iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The automatic-reset on BUS-OFF is {0}", (iBuffer == PCANBasic.PCAN_PARAMETER_ON) ? "ON" : "OFF"));
                    break;
                // The activation status of the CAN option "Listen Only" will be retrieved
                //
                case 3:
                    stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_LISTEN_ONLY, out iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The CAN option \"Listen Only\" is {0}", (iBuffer == PCANBasic.PCAN_PARAMETER_ON) ? "ON" : "OFF"));
                    break;
                // The activation status for the feature for logging debug-information will be retrieved
                case 4:
                    stsResult = PCANBasic.GetValue(PCANBasic.PCAN_NONEBUS, TPCANParameter.PCAN_LOG_STATUS, out iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The feature for logging debug information is {0}", (iBuffer == PCANBasic.PCAN_PARAMETER_ON) ? "ON" : "OFF"));
                    break;
                // The activation status of the channel option "Receive Status"  will be retrieved
                //
                case 5:
                    stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_RECEIVE_STATUS, out iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The channel option \"Receive Status\" is {0}", (iBuffer == PCANBasic.PCAN_PARAMETER_ON) ? "ON" : "OFF"));
                    break;
                // The Number of the CAN-Controller used by a PCAN-Channel
                // 
                case 6:
                    stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_CONTROLLER_NUMBER, out iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The CAN Controller number is {0}", iBuffer));
                    break;
                // The activation status for the feature for tracing data will be retrieved
                //
                case 7:
                    stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_TRACE_STATUS, out iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The feature for tracing data is {0}", (iBuffer == PCANBasic.PCAN_PARAMETER_ON) ? "ON" : "OFF"));
                    break;
                // The activation status of the Channel Identifying procedure will be retrieved
                //
                case 8:
                    stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_CHANNEL_IDENTIFYING, out iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The identification procedure of the selected channel is {0}", (iBuffer == PCANBasic.PCAN_PARAMETER_ON) ? "ON" : "OFF"));
                    break;
                // The extra capabilities of a hardware will asked
                //
                case 9:
                    stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_CHANNEL_FEATURES, out iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                    {
                        IncludeTextMessage(string.Format("The channel {0} Flexible Data-Rate (CAN-FD)", ((iBuffer & PCANBasic.FEATURE_FD_CAPABLE) == PCANBasic.FEATURE_FD_CAPABLE) ? "does support" : "DOESN'T SUPPORT"));
                        IncludeTextMessage(string.Format("The channel {0} an inter-frame delay for sending messages", ((iBuffer & PCANBasic.FEATURE_DELAY_CAPABLE) == PCANBasic.FEATURE_DELAY_CAPABLE) ? "does support" : "DOESN'T SUPPORT"));
                        IncludeTextMessage(string.Format("The channel {0} using I/O pins", ((iBuffer & PCANBasic.FEATURE_IO_CAPABLE) == PCANBasic.FEATURE_IO_CAPABLE) ? "does allow" : "DOESN'T ALLOW"));
                    }
                    break;
                // The status of the speed adapting feature will be retrieved
                //
                case 10:
                    stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_BITRATE_ADAPTING, out iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The feature for bit rate adaptation is {0}", (iBuffer == PCANBasic.PCAN_PARAMETER_ON) ? "ON" : "OFF"));
                    break;
                // The bitrate of the connected channel will be retrieved (BTR0-BTR1 value)
                //
                case 11:
                    stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_BITRATE_INFO, out iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The bit rate of the channel is {0:X4}h", iBuffer));
                    break;
                // The bitrate of the connected FD channel will be retrieved (String value)
                //
                case 12:
                    stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_BITRATE_INFO_FD, strBuffer, 255);
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                    {
                        IncludeTextMessage("The bit rate FD of the channel is represented by the following values:");
                        foreach(string strPart in strBuffer.ToString().Split(','))
                            IncludeTextMessage("   * " + strPart);
                    }
                    break;
                // The nominal speed configured on the CAN bus
                //
                case 13:
                    stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_BUSSPEED_NOMINAL, out iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The nominal speed of the channel is {0} bit/s", iBuffer));
                    break;
                // The data speed configured on the CAN bus
                //
                case 14:
                    stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_BUSSPEED_DATA, out iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The data speed of the channel is {0} bit/s", iBuffer));
                    break;
                // The IP address of a LAN channel as string, in IPv4 format
                //
                case 15:
                    stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_IP_ADDRESS, strBuffer, 255);
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The IP address of the channel is {0}", strBuffer.ToString()));
                    break;
                // The running status of the LAN Service
                //
                case 16:
                    stsResult = PCANBasic.GetValue(PCANBasic.PCAN_NONEBUS, TPCANParameter.PCAN_LAN_SERVICE_STATUS, out iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The LAN service is {0}", (iBuffer == PCANBasic.SERVICE_STATUS_RUNNING) ? "running" : "NOT running"));
                    break;
                // The reception of Status frames
                //
                case 17:
                    stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_ALLOW_STATUS_FRAMES, out iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The reception of Status frames is {0}", (iBuffer == PCANBasic.PCAN_PARAMETER_ON) ? "enabled" : "disabled"));
                    break;
                // The reception of RTR frames
                //
                case 18:
                    stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_ALLOW_RTR_FRAMES, out iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The reception of RTR frames is {0}", (iBuffer == PCANBasic.PCAN_PARAMETER_ON) ? "enabled" : "disabled"));
                    break;
                // The reception of Error frames
                //
                case 19:
                    stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_ALLOW_ERROR_FRAMES, out iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The reception of Error frames is {0}", (iBuffer == PCANBasic.PCAN_PARAMETER_ON) ? "enabled" : "disabled"));
                    break;
                // The Interframe delay of an USB channel will be retrieved
                //
                case 20:
                    stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_INTERFRAME_DELAY, out iBuffer, sizeof(UInt32));
                    if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                        IncludeTextMessage(string.Format("The configured interframe delay is {0} μs", iBuffer));
                    break;
                // The current parameter is invalid
                //
                default:
                    stsResult = TPCANStatus.PCAN_ERROR_UNKNOWN;
                    MessageBox.Show("Wrong parameter code.");
                    return;
            }

            // If the function fail, an error message is shown
            //
            if (stsResult != TPCANStatus.PCAN_ERROR_OK)
                MessageBox.Show(GetFormatedError(stsResult));
        }

        private void btnRead_Click(object sender, EventArgs e)
        {
            TPCANStatus stsResult;

            // We execute the "Read" function of the PCANBasic                
            //
            stsResult = m_IsFD ? ReadMessageFD() : ReadMessage();
            if (stsResult != TPCANStatus.PCAN_ERROR_OK)
                // If an error occurred, an information message is included
                //
                IncludeTextMessage(GetFormatedError(stsResult));
        }

        private void btnGetVersions_Click(object sender, EventArgs e)
        {
            TPCANStatus stsResult;
            StringBuilder strTemp;
            string[] strArrayVersion;

            strTemp = new StringBuilder(256);

            // We get the vesion of the PCAN-Basic API
            //
            stsResult = PCANBasic.GetValue(PCANBasic.PCAN_NONEBUS, TPCANParameter.PCAN_API_VERSION, strTemp, 256);
            if (stsResult == TPCANStatus.PCAN_ERROR_OK)
            {
                IncludeTextMessage("API Version: " + strTemp.ToString());
                // We get the driver version of the channel being used
                //
                stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_CHANNEL_VERSION, strTemp, 256);
                if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                {
                    // Because this information contains line control characters (several lines)
                    // we split this also in several entries in the Information List-Box
                    //
                    strArrayVersion = strTemp.ToString().Split(new char[] { '\n' });
                    IncludeTextMessage("Channel/Driver Version: ");
                    for (int i = 0; i < strArrayVersion.Length; i++)
                        IncludeTextMessage("     * " + strArrayVersion[i]);
                }
            }

            // If an error ccurred, a message is shown
            //
            if (stsResult != TPCANStatus.PCAN_ERROR_OK)
                MessageBox.Show(GetFormatedError(stsResult));
        }

        private void btnMsgClear_Click(object sender, EventArgs e)
        {
            // The information contained in the messages List-View
            // is cleared
            //
            lock (m_LastMsgsList.SyncRoot)
            {
                m_LastMsgsList.Clear();
                lstMessages.Items.Clear();
            }
        }

        private void btnInfoClear_Click(object sender, EventArgs e)
        {
            // The information contained in the Information List-Box 
            // is cleared
            //
            lbxInfo.Items.Clear();
        }

        private TPCANStatus WriteFrame()
        {
            TPCANMsg CANMsg;
            TextBox txtbCurrentTextBox;

            // We create a TPCANMsg message structure 
            //
            CANMsg = new TPCANMsg();
            CANMsg.DATA = new byte[8];

            // We configurate the Message.  The ID,
            // Length of the Data, Message Type
            // and the data
            //
            CANMsg.ID = Convert.ToUInt32(txtID.Text, 16);
            CANMsg.LEN = Convert.ToByte(nudLength.Value);
            CANMsg.MSGTYPE = (chbExtended.Checked) ? TPCANMessageType.PCAN_MESSAGE_EXTENDED : TPCANMessageType.PCAN_MESSAGE_STANDARD;
            // If a remote frame will be sent, the data bytes are not important.
            //
            if (chbRemote.Checked)
                CANMsg.MSGTYPE |= TPCANMessageType.PCAN_MESSAGE_RTR;
            else
            {
                // We get so much data as the Len of the message
                //
                for (int i = 0; i < GetLengthFromDLC(CANMsg.LEN, true); i++)
                {
                    txtbCurrentTextBox = (TextBox)this.Controls.Find("txtData" + i.ToString(), true)[0];
                    CANMsg.DATA[i] = Convert.ToByte(txtbCurrentTextBox.Text, 16);
                }
            }

            // The message is sent to the configured hardware
            //
            return PCANBasic.Write(m_PcanHandle, ref CANMsg);
        }

        private TPCANStatus WriteFrameFD()
        {
            TPCANMsgFD CANMsg;
            TextBox txtbCurrentTextBox;
            int iLength;

            // We create a TPCANMsgFD message structure 
            //
            CANMsg = new TPCANMsgFD();
            CANMsg.DATA = new byte[64];

            // We configurate the Message.  The ID,
            // Length of the Data, Message Type 
            // and the data
            //
            CANMsg.ID = Convert.ToUInt32(txtID.Text, 16);
            CANMsg.DLC = Convert.ToByte(nudLength.Value);
            CANMsg.MSGTYPE = (chbExtended.Checked) ? TPCANMessageType.PCAN_MESSAGE_EXTENDED : TPCANMessageType.PCAN_MESSAGE_STANDARD;
            CANMsg.MSGTYPE |= (chbFD.Checked) ? TPCANMessageType.PCAN_MESSAGE_FD : TPCANMessageType.PCAN_MESSAGE_STANDARD;
            CANMsg.MSGTYPE |= (chbBRS.Checked) ? TPCANMessageType.PCAN_MESSAGE_BRS : TPCANMessageType.PCAN_MESSAGE_STANDARD;

            // If a remote frame will be sent, the data bytes are not important.
            //
            if (chbRemote.Checked)
                CANMsg.MSGTYPE |= TPCANMessageType.PCAN_MESSAGE_RTR;
            else
            {
                // We get so much data as the Len of the message
                //
                iLength = GetLengthFromDLC(CANMsg.DLC, (CANMsg.MSGTYPE & TPCANMessageType.PCAN_MESSAGE_FD) == 0);
                for (int i = 0; i < iLength; i++)
                {
                    txtbCurrentTextBox = (TextBox)this.Controls.Find("txtData" + i.ToString(), true)[0];
                    CANMsg.DATA[i] = Convert.ToByte(txtbCurrentTextBox.Text, 16);
                }
            }

            // The message is sent to the configured hardware
            //
            return PCANBasic.WriteFD(m_PcanHandle, ref CANMsg);
        }

        private void btnWrite_Click(object sender, EventArgs e)
        {
            TPCANStatus stsResult;

            // Send the message
            //
            stsResult = m_IsFD ? WriteFrameFD() : WriteFrame();

            // The message was successfully sent
            //
            if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                IncludeTextMessage("Message was successfully SENT");
            // An error occurred.  We show the error.
            //			
            else
                MessageBox.Show(GetFormatedError(stsResult));
        }

        private void btnReset_Click(object sender, EventArgs e)
        {
            TPCANStatus stsResult;

            // Resets the receive and transmit queues of a PCAN Channel.
            //
            stsResult = PCANBasic.Reset(m_PcanHandle);

            // If it fails, a error message is shown
            //
            if (stsResult != TPCANStatus.PCAN_ERROR_OK)
                MessageBox.Show(GetFormatedError(stsResult));
            else
                IncludeTextMessage("Receive and transmit queues successfully reset");
        }

        private void btnStatus_Click(object sender, EventArgs e)
        {
            TPCANStatus stsResult;
            String errorName;

            // Gets the current BUS status of a PCAN Channel.
            //
            stsResult = PCANBasic.GetStatus(m_PcanHandle);

            // Switch On Error Name
            //
            switch (stsResult)
            {
                case TPCANStatus.PCAN_ERROR_INITIALIZE:
                    errorName = "PCAN_ERROR_INITIALIZE";
                    break;

                case TPCANStatus.PCAN_ERROR_BUSLIGHT:
                    errorName = "PCAN_ERROR_BUSLIGHT";
                    break;

                case TPCANStatus.PCAN_ERROR_BUSHEAVY: // TPCANStatus.PCAN_ERROR_BUSWARNING
                    errorName = m_IsFD ? "PCAN_ERROR_BUSWARNING" : "PCAN_ERROR_BUSHEAVY";
                    break;

                case TPCANStatus.PCAN_ERROR_BUSPASSIVE: 
                    errorName = "PCAN_ERROR_BUSPASSIVE";
                    break;
                
                case TPCANStatus.PCAN_ERROR_BUSOFF:
                    errorName = "PCAN_ERROR_BUSOFF";
                    break;

                case TPCANStatus.PCAN_ERROR_OK:
                    errorName = "PCAN_ERROR_OK";
                    break;

                default:
                    errorName = "See Documentation";
                    break;
            }

            // Display Message
            //
            IncludeTextMessage(String.Format("Status: {0} ({1:X}h)", errorName, stsResult));
        }
        #endregion

        #region Timer event-handler
        private void tmrRead_Tick(object sender, EventArgs e)
        { 
            // Checks if in the receive-queue are currently messages for read
            // 
            ReadMessages();
        }

        private void tmrDisplay_Tick(object sender, EventArgs e)
        {
            DisplayMessages();
        }
        #endregion

        #region Message List-View event-handler
        private void lstMessages_DoubleClick(object sender, EventArgs e)
        {
            // Clears the content of the Message List-View
            //
            btnMsgClear_Click(this, new EventArgs());
        }
        #endregion

        #region Information List-Box event-handler
        private void lbxInfo_DoubleClick(object sender, EventArgs e)
        {
            // Clears the content of the Information List-Box
            //
            btnInfoClear_Click(this, new EventArgs());
        }
        #endregion

        #region Textbox event handlers
        private void txtID_Leave(object sender, EventArgs e)
        {
            int iTextLength;
            uint uiMaxValue;

            // Calculates the text length and Maximum ID value according
            // with the Message Type
            //
            iTextLength = (chbExtended.Checked) ? 8 : 3;
            uiMaxValue = (chbExtended.Checked) ? (uint)0x1FFFFFFF : (uint)0x7FF;

            // The Textbox for the ID is represented with 3 characters for 
            // Standard and 8 characters for extended messages.
            // Therefore if the Length of the text is smaller than TextLength,  
            // we add "0"
            //
            while (txtID.Text.Length != iTextLength)
                txtID.Text = ("0" + txtID.Text);

            // We check that the ID is not bigger than current maximum value
            //
            if (Convert.ToUInt32(txtID.Text, 16) > uiMaxValue)
                txtID.Text = string.Format("{0:X" + iTextLength.ToString() + "}", uiMaxValue);
        }

        private void txtID_KeyPress(object sender, KeyPressEventArgs e)
        {
            char chCheck;

            // We convert the Character to its Upper case equivalent
            //
            chCheck = char.ToUpper(e.KeyChar);

            // The Key is the Delete (Backspace) Key
            //
            if (chCheck == 8)
                return;
            // The Key is a number between 0-9
            //
            if ((chCheck > 47) && (chCheck < 58))
                return;
            // The Key is a character between A-F
            //
            if ((chCheck > 64) && (chCheck < 71))
                return;

            // Is neither a number nor a character between A(a) and F(f)
            //
            e.Handled = true;
        }

        private void txtData0_Leave(object sender, EventArgs e)
        {
            TextBox txtbCurrentTextbox;

            // all the Textbox Data fields are represented with 2 characters.
            // Therefore if the Length of the text is smaller than 2, we add
            // a "0"
            //
            if (sender.GetType().Name == "TextBox")
            {
                txtbCurrentTextbox = (TextBox)sender;
                while (txtbCurrentTextbox.Text.Length != 2)
                    txtbCurrentTextbox.Text = ("0" + txtbCurrentTextbox.Text);
            }
        }
        #endregion

        #region Radio- and Check- Buttons event-handlers
        private void chbShowPeriod_CheckedChanged(object sender, EventArgs e)
        {
            // According with the check-value of this checkbox,
            // the recieved time of a messages will be interpreted as 
            // period (time between the two last messages) or as time-stamp
            // (the elapsed time since windows was started)
            //
            lock (m_LastMsgsList.SyncRoot)
            {
                foreach (MessageStatus msg in m_LastMsgsList)
                    msg.ShowingPeriod = chbShowPeriod.Checked;
            }
        }

        private void chbExtended_CheckedChanged(object sender, EventArgs e)
        {
            uint uiTemp;

            txtID.MaxLength = (chbExtended.Checked) ? 8 : 3;

            // the only way that the text length can be bigger als MaxLength
            // is when the change is from Extended to Standard message Type.
            // We have to handle this and set an ID not bigger than the Maximum
            // ID value for a Standard Message (0x7FF)
            //
            if (txtID.Text.Length > txtID.MaxLength)
            {
                uiTemp = Convert.ToUInt32(txtID.Text, 16);
                txtID.Text = (uiTemp < 0x7FF) ? string.Format("{0:X3}", uiTemp) : "7FF";
            }

            txtID_Leave(this, new EventArgs());
        }

        private void chbRemote_CheckedChanged(object sender, EventArgs e)
        {
            TextBox txtbCurrentTextBox;

            txtbCurrentTextBox = txtData0;

            chbFD.Enabled = !chbRemote.Checked;

            // If the message is a RTR, no data is sent. The textboxes for data 
            // will be disabled
            // 
            for (int i = 0; i <= nudLength.Value; i++)
            {
                txtbCurrentTextBox.Enabled = !chbRemote.Checked;
                if (i < nudLength.Value)
                    txtbCurrentTextBox = (TextBox)this.Controls.Find("txtData" + i.ToString(), true)[0];
            }
        }

        private void chbFilterExt_CheckedChanged(object sender, EventArgs e)
        {
            int iMaxValue;

            iMaxValue = (chbFilterExt.Checked) ? 0x1FFFFFFF : 0x7FF;

            // We check that the maximum value for a selected filter 
            // mode is used
            //
            if (nudIdTo.Value > iMaxValue)
                nudIdTo.Value = iMaxValue;
            nudIdTo.Maximum = iMaxValue;

            if (nudIdFrom.Value > iMaxValue)
                nudIdFrom.Value = iMaxValue;
            nudIdFrom.Maximum = iMaxValue;
        }

        private void chbFD_CheckedChanged(object sender, EventArgs e)
        {
            chbRemote.Enabled = !chbFD.Checked;
            chbBRS.Enabled = chbFD.Checked;
            if (!chbBRS.Enabled)
                chbBRS.Checked = false;
            nudLength.Maximum = chbFD.Checked ? 15 : 8;
        }

        private void rdbTimer_CheckedChanged(object sender, EventArgs e)
        {
            if (!btnRelease.Enabled)
                return;

            // According with the kind of reading, a timer, a thread or a button will be enabled
            //
            if (rdbTimer.Checked)
            {
                // Abort Read Thread if it exists
                //
                if (m_ReadThread != null)
                {
                    m_ReadThread.Abort();
                    m_ReadThread.Join();
                    m_ReadThread = null;
                }

                // Enable Timer
                //
                tmrRead.Enabled = btnRelease.Enabled;
            }
            if (rdbEvent.Checked)
            {
                // Disable Timer
                //
                tmrRead.Enabled = false;
                // Create and start the tread to read CAN Message using SetRcvEvent()
                //
                System.Threading.ThreadStart threadDelegate = new System.Threading.ThreadStart(this.CANReadThreadFunc);
                m_ReadThread = new System.Threading.Thread(threadDelegate);
                m_ReadThread.IsBackground = true;
                m_ReadThread.Start();
            }
            if (rdbManual.Checked)
            {
                // Abort Read Thread if it exists
                //
                if (m_ReadThread != null)
                {
                    m_ReadThread.Abort();
                    m_ReadThread.Join();
                    m_ReadThread = null;
                }
                // Disable Timer
                //
                tmrRead.Enabled = false;
            }
            btnRead.Enabled = btnRelease.Enabled && rdbManual.Checked;
        }

        private void chbCanFD_CheckedChanged(object sender, EventArgs e)
        {
            m_IsFD = chbCanFD.Checked;

            cbbBaudrates.Visible = !m_IsFD;
            cbbHwType.Visible = !m_IsFD;
            cbbInterrupt.Visible = !m_IsFD;
            cbbIO.Visible = !m_IsFD;
            laBaudrate.Visible = !m_IsFD;
            laHwType.Visible = !m_IsFD;
            laIOPort.Visible = !m_IsFD;
            laInterrupt.Visible = !m_IsFD;

            txtBitrate.Visible = m_IsFD;
            laBitrate.Visible = m_IsFD;
            chbFD.Visible = m_IsFD;
            chbBRS.Visible = m_IsFD;

            if ((nudLength.Maximum > 8) && !m_IsFD)
                chbFD.Checked = false;
        }

        private void nudLength_ValueChanged(object sender, EventArgs e)
        {
            TextBox txtbCurrentTextBox;
            int iLength;

            txtbCurrentTextBox = txtData0;
            iLength = GetLengthFromDLC((int)nudLength.Value, !chbFD.Checked);
            laLength.Text = string.Format("{0} B.", iLength);

            for (int i = 0; i <= 64; i++)
            {
                txtbCurrentTextBox.Enabled = i <= iLength;
                if (i < 64)
                    txtbCurrentTextBox = (TextBox)this.Controls.Find("txtData" + i.ToString(), true)[0];
            }
        }
        #endregion        
        #endregion        
        #endregion        
    }
}
