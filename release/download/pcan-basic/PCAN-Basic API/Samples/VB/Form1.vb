Imports System.Text

' Inclusion of PEAK PCAN-Basic namespace
'
Imports Peak.Can.Basic
Imports TPCANHandle = System.UInt16
Imports TPCANBitrateFD = System.String
Imports TPCANTimestampFD = System.UInt64

Public Class Form1

    Public Sub New()
        ' Initializes Form's component
        '
        InitializeComponent()
        ' Initializes specific components
        '
        InitializeBasicComponents()
    End Sub

#Region "Structures"
    ''' <summary>
    ''' Message Status structure used to show CAN Messages
    ''' in a ListView
    ''' </summary>
    Private Class MessageStatus
        Private m_Msg As TPCANMsgFD
        Private m_TimeStamp As TPCANTimestampFD
        Private m_oldTimeStamp As TPCANTimestampFD
        Private m_iIndex As Integer
        Private m_Count As Integer
        Private m_bShowPeriod As Boolean
        Private m_bWasChanged As Boolean

        Public Sub New(ByVal canMsg As TPCANMsgFD, ByVal canTimestamp As TPCANTimestampFD, ByVal listIndex As Integer)
            m_Msg = canMsg
            m_TimeStamp = canTimestamp
            m_oldTimeStamp = canTimestamp
            m_iIndex = listIndex
            m_Count = 1
            m_bShowPeriod = True
            m_bWasChanged = False
        End Sub

        Public Sub Update(ByVal canMsg As TPCANMsgFD, ByVal canTimestamp As TPCANTimestampFD)
            m_Msg = canMsg
            m_oldTimeStamp = m_TimeStamp
            m_TimeStamp = canTimestamp
            m_bWasChanged = True
            m_Count += 1
        End Sub

        Private Function GetMsgTypeString() As String
            Dim strTemp As String

            If (m_Msg.MSGTYPE And TPCANMessageType.PCAN_MESSAGE_STATUS) = TPCANMessageType.PCAN_MESSAGE_STATUS Then
                Return "STATUS"
            End If

            If (m_Msg.MSGTYPE And TPCANMessageType.PCAN_MESSAGE_ERRFRAME) = TPCANMessageType.PCAN_MESSAGE_ERRFRAME Then
                Return "ERROR"
            End If

            If (m_Msg.MSGTYPE And TPCANMessageType.PCAN_MESSAGE_EXTENDED) = TPCANMessageType.PCAN_MESSAGE_EXTENDED Then
                strTemp = "EXT"
            Else
                strTemp = "STD"
            End If

            If (m_Msg.MSGTYPE And TPCANMessageType.PCAN_MESSAGE_RTR) = TPCANMessageType.PCAN_MESSAGE_RTR Then
                strTemp += "/RTR"
            Else
                If (m_Msg.MSGTYPE > TPCANMessageType.PCAN_MESSAGE_EXTENDED) Then
                    strTemp += " [ "
                    If ((m_Msg.MSGTYPE And TPCANMessageType.PCAN_MESSAGE_FD) = TPCANMessageType.PCAN_MESSAGE_FD) Then
                        strTemp += " FD"
                    End If
                    If ((m_Msg.MSGTYPE And TPCANMessageType.PCAN_MESSAGE_BRS) = TPCANMessageType.PCAN_MESSAGE_BRS) Then
                        strTemp += " BRS"
                    End If
                    If ((m_Msg.MSGTYPE And TPCANMessageType.PCAN_MESSAGE_ESI) = TPCANMessageType.PCAN_MESSAGE_ESI) Then
                        strTemp += " ESI"
                    End If
                    strTemp += " ]"
                End If
            End If

            Return strTemp
        End Function

        Private Function GetIdString() As String
            If (m_Msg.MSGTYPE And TPCANMessageType.PCAN_MESSAGE_EXTENDED) = TPCANMessageType.PCAN_MESSAGE_EXTENDED Then
                Return String.Format("{0:X8}h", m_Msg.ID)
            Else
                Return String.Format("{0:X3}h", m_Msg.ID)
            End If
        End Function

        Private Function GetDataString() As String
            Dim strTemp As String

            strTemp = ""

            If (m_Msg.MSGTYPE And TPCANMessageType.PCAN_MESSAGE_RTR) = TPCANMessageType.PCAN_MESSAGE_RTR Then
                strTemp = "Remote Request"
            Else
                For i As Integer = 0 To Form1.GetLengthFromDLC(m_Msg.DLC, (m_Msg.MSGTYPE And TPCANMessageType.PCAN_MESSAGE_FD) = 0) - 1
                    strTemp += String.Format("{0:X2} ", m_Msg.DATA(i))
                Next
            End If

            Return strTemp
        End Function

        Private Function GetTimeString() As String
            Dim fTime As Double

            fTime = (m_TimeStamp / 1000.0R)
            If m_bShowPeriod Then
                fTime -= (m_oldTimeStamp / 1000.0R)
            End If

            Return fTime.ToString("F1")
        End Function

        Public ReadOnly Property CANMsg() As TPCANMsgFD
            Get
                Return m_Msg
            End Get
        End Property

        Public ReadOnly Property Timestamp() As TPCANTimestampFD
            Get
                Return m_TimeStamp
            End Get
        End Property

        Public ReadOnly Property Position() As Integer
            Get
                Return m_iIndex
            End Get
        End Property

        Public ReadOnly Property TypeString() As String
            Get
                Return GetMsgTypeString()
            End Get
        End Property

        Public ReadOnly Property IdString() As String
            Get
                Return GetIdString()
            End Get
        End Property

        Public ReadOnly Property DataString() As String
            Get
                Return GetDataString()
            End Get
        End Property

        Public ReadOnly Property Count() As Integer
            Get
                Return m_Count
            End Get
        End Property

        Public Property ShowingPeriod() As Boolean
            Get
                Return m_bShowPeriod
            End Get
            Set(ByVal value As Boolean)
                If m_bShowPeriod Xor value Then
                    m_bShowPeriod = value
                    m_bWasChanged = True
                End If
            End Set
        End Property

        Public Property MarkedAsUpdated() As Boolean
            Get
                Return m_bWasChanged
            End Get
            Set(ByVal value As Boolean)
                m_bWasChanged = value
            End Set
        End Property

        Public ReadOnly Property TimeString() As String
            Get
                Return GetTimeString()
            End Get
        End Property
    End Class
#End Region

#Region "Delegates"
    ''' <summary>
    ''' Read-Delegate Handler
    ''' </summary>
    Private Delegate Sub ReadDelegateHandler()
#End Region

#Region "Members"
    ''' <summary>
    ''' Saves the desired connection mode
    ''' </summary>
    Private m_IsFD As Boolean
    ''' <summary>
    ''' Saves the handle of a PCAN hardware
    ''' </summary>
    Private m_PcanHandle As TPCANHandle
    ''' <summary>
    ''' Saves the baudrate register for a conenction
    ''' </summary>
    Private m_Baudrate As TPCANBaudrate
    ''' <summary>
    ''' Saves the type of a non-plug-and-play hardware
    ''' </summary>
    Private m_HwType As TPCANType
    ''' <summary>
    ''' Stores the status of received messages for its display
    ''' </summary>
    Private m_LastMsgsList As System.Collections.ArrayList
    ''' <summary>
    ''' Read Delegate for calling the function "ReadMessages"
    ''' </summary>
    Private m_ReadDelegate As ReadDelegateHandler
    ''' <summary>
    ''' Receive-Event
    ''' </summary>
    Private m_ReceiveEvent As System.Threading.AutoResetEvent
    ''' <summary>
    ''' Thread for message reading (using events)
    ''' </summary>
    Private m_ReadThread As System.Threading.Thread
    ''' <summary>
    ''' Handles of the current available PCAN-Hardware
    ''' </summary>
    Private m_HandlesArray As TPCANHandle()
#End Region

#Region "Methods"

#Region "UI Handler"

    Private Sub btnInit_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnInit.Click
        Dim stsResult As TPCANStatus

        ' Connects a selected PCAN-Basic channel
        '
        If (m_IsFD) Then
            stsResult = PCANBasic.InitializeFD(m_PcanHandle, txtBitrate.Text)
        Else
            stsResult = PCANBasic.Initialize(m_PcanHandle, m_Baudrate, m_HwType, Convert.ToUInt32(cbbIO.Text, 16), Convert.ToUInt16(cbbInterrupt.Text))
        End If

        If stsResult <> TPCANStatus.PCAN_ERROR_OK Then
            If stsResult <> TPCANStatus.PCAN_ERROR_CAUTION Then
                MessageBox.Show(GetFormatedError(stsResult))
            Else
                IncludeTextMessage("******************************************************")
                IncludeTextMessage("The bitrate being used is different than the given one")
                IncludeTextMessage("******************************************************")
                stsResult = TPCANStatus.PCAN_ERROR_OK
            End If

        Else
            ' Prepares the PCAN-Basic's PCAN-Trace file
            '
            ConfigureTraceFile()
        End If

        ' Sets the connection status of the main-form
        '
        SetConnectionStatus(stsResult = TPCANStatus.PCAN_ERROR_OK)
    End Sub

    Private Sub cbbChannel_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cbbChannel.SelectedIndexChanged
        Dim bNonPnP As Boolean
        Dim strTemp As String

        ' Get the handle fromt he text being shown
        strTemp = cbbChannel.Text
        strTemp = strTemp.Substring(strTemp.IndexOf("("c) + 1, 3)

        strTemp = strTemp.Replace("h", " ").Trim(" ")

        ' Determines if the handle belong to a No Plug&Play hardware 
        '
        m_PcanHandle = Convert.ToUInt16(strTemp, 16)
        bNonPnP = m_PcanHandle <= PCANBasic.PCAN_DNGBUS1

        ' Activates/deactivates configuration controls according with the 
        ' kind of hardware
        '
        cbbHwType.Enabled = bNonPnP
        cbbIO.Enabled = bNonPnP
        cbbInterrupt.Enabled = bNonPnP

    End Sub

    Private Sub btnHwRefresh_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnHwRefresh.Click
        Dim iBuffer As UInt32
        Dim stsResult As TPCANStatus
        Dim isFD As Boolean

        ' Clears the Channel combioBox and fill it againa with 
        ' the PCAN-Basic handles for no-Plug&Play hardware and
        ' the detected Plug&Play hardware
        '
        cbbChannel.Items.Clear()
        Try
            For i As Integer = 0 To m_HandlesArray.Length - 1
                ' Includes all no-Plug&Play Handles
                If m_HandlesArray(i) <= PCANBasic.PCAN_DNGBUS1 Then
                    cbbChannel.Items.Add(FormatChannelName(m_HandlesArray(i)))
                Else
                    ' Checks for a Plug&Play Handle and, according with the return value, includes it
                    ' into the list of available hardware channels.
                    '
                    stsResult = PCANBasic.GetValue(m_HandlesArray(i), TPCANParameter.PCAN_CHANNEL_CONDITION, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                    If (stsResult = TPCANStatus.PCAN_ERROR_OK) AndAlso ((iBuffer And PCANBasic.PCAN_CHANNEL_AVAILABLE) = PCANBasic.PCAN_CHANNEL_AVAILABLE) Then
                        stsResult = PCANBasic.GetValue(m_HandlesArray(i), TPCANParameter.PCAN_CHANNEL_FEATURES, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                        isFD = (stsResult = TPCANStatus.PCAN_ERROR_OK) And ((iBuffer And PCANBasic.FEATURE_FD_CAPABLE) = PCANBasic.FEATURE_FD_CAPABLE)
                        cbbChannel.Items.Add(FormatChannelName(m_HandlesArray(i), isFD))
                    End If
                End If
            Next
            cbbChannel.SelectedIndex = cbbChannel.Items.Count - 1
        Catch ex As DllNotFoundException
            MessageBox.Show("Unable to find the library: PCANBasic.dll !", "Error!", MessageBoxButtons.OK, MessageBoxIcon.Error)
            Environment.Exit(-1)
        End Try

    End Sub

    Private Sub cbbBaudrates_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cbbBaudrates.SelectedIndexChanged
        ' Saves the current selected baudrate register code
        '
        Select Case cbbBaudrates.SelectedIndex
            Case 0
                m_Baudrate = TPCANBaudrate.PCAN_BAUD_1M
                Exit Select
            Case 1
                m_Baudrate = TPCANBaudrate.PCAN_BAUD_800K
                Exit Select
            Case 2
                m_Baudrate = TPCANBaudrate.PCAN_BAUD_500K
                Exit Select
            Case 3
                m_Baudrate = TPCANBaudrate.PCAN_BAUD_250K
                Exit Select
            Case 4
                m_Baudrate = TPCANBaudrate.PCAN_BAUD_125K
                Exit Select
            Case 5
                m_Baudrate = TPCANBaudrate.PCAN_BAUD_100K
                Exit Select
            Case 6
                m_Baudrate = TPCANBaudrate.PCAN_BAUD_95K
                Exit Select
            Case 7
                m_Baudrate = TPCANBaudrate.PCAN_BAUD_83K
                Exit Select
            Case 8
                m_Baudrate = TPCANBaudrate.PCAN_BAUD_50K
                Exit Select
            Case 9
                m_Baudrate = TPCANBaudrate.PCAN_BAUD_47K
                Exit Select
            Case 10
                m_Baudrate = TPCANBaudrate.PCAN_BAUD_33K
                Exit Select
            Case 11
                m_Baudrate = TPCANBaudrate.PCAN_BAUD_20K
                Exit Select
            Case 12
                m_Baudrate = TPCANBaudrate.PCAN_BAUD_10K
                Exit Select
            Case 13
                m_Baudrate = TPCANBaudrate.PCAN_BAUD_5K
                Exit Select
        End Select
    End Sub

    Private Sub cbbHwType_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cbbHwType.SelectedIndexChanged
        ' Saves the current type for a no-Plug&Play hardware
        '
        Select Case cbbHwType.SelectedIndex
            Case 0
                m_HwType = TPCANType.PCAN_TYPE_ISA
                Exit Select
            Case 1
                m_HwType = TPCANType.PCAN_TYPE_ISA_SJA
                Exit Select
            Case 2
                m_HwType = TPCANType.PCAN_TYPE_ISA_PHYTEC
                Exit Select
            Case 3
                m_HwType = TPCANType.PCAN_TYPE_DNG
                Exit Select
            Case 4
                m_HwType = TPCANType.PCAN_TYPE_DNG_EPP
                Exit Select
            Case 5
                m_HwType = TPCANType.PCAN_TYPE_DNG_SJA
                Exit Select
            Case 6
                m_HwType = TPCANType.PCAN_TYPE_DNG_SJA_EPP
                Exit Select
        End Select
    End Sub

    Private Sub btnRelease_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnRelease.Click
        ' Releases a current connected PCAN-Basic channel
        '
        PCANBasic.Uninitialize(m_PcanHandle)
        tmrRead.Enabled = False
        If m_ReadThread IsNot Nothing Then
            m_ReadThread.Abort()
            m_ReadThread.Join()
            m_ReadThread = Nothing
        End If

        ' Sets the connection status of the main-form
        '
        SetConnectionStatus(False)

    End Sub

    Private Sub chbFilterExt_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles chbFilterExt.CheckedChanged
        Dim iMaxValue As Integer

        iMaxValue = If((chbFilterExt.Checked), &H1FFFFFFF, &H7FF)

        ' We check that the maximum value for a selected filter 
        ' mode is used
        '
        If nudIdTo.Value > iMaxValue Then
            nudIdTo.Value = iMaxValue
        End If
        nudIdTo.Maximum = iMaxValue

        If (nudIdFrom.Value > iMaxValue) Then
            nudIdFrom.Value = iMaxValue
        End If
        nudIdFrom.Maximum = iMaxValue
    End Sub

    Private Sub btnFilterApply_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnFilterApply.Click
        Dim iBuffer As UInt32
        Dim stsResult As TPCANStatus

        ' Gets the current status of the message filter
        '
        If Not GetFilterStatus(iBuffer) Then
            Return
        End If

        ' Configures the message filter for a custom range of messages
        '
        If rdbFilterCustom.Checked Then
            ' Sets the custom filter
            '
            stsResult = PCANBasic.FilterMessages(m_PcanHandle, Convert.ToUInt32(nudIdFrom.Value), Convert.ToUInt32(nudIdTo.Value), If(chbFilterExt.Checked, TPCANMode.PCAN_MODE_EXTENDED, TPCANMode.PCAN_MODE_STANDARD))
            ' If success, an information message is written, if it is not, an error message is shown
            '
            If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                IncludeTextMessage(String.Format("The filter was customized. IDs from {0:X} to {1:X} will be received", nudIdFrom.Text, nudIdTo.Text))
            Else
                MessageBox.Show(GetFormatedError(stsResult))
            End If

            Return
        End If

        ' The filter will be full opened or complete closed
        '
        If rdbFilterClose.Checked Then
            iBuffer = PCANBasic.PCAN_FILTER_CLOSE
        Else
            iBuffer = PCANBasic.PCAN_FILTER_OPEN
        End If

        ' The filter is configured
        '
        stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_MESSAGE_FILTER, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))

        ' If success, an information message is written, if it is not, an error message is shown
        '
        If stsResult = TPCANStatus.PCAN_ERROR_OK Then
            IncludeTextMessage(String.Format("The filter was successfully {0}", If(rdbFilterClose.Checked, "closed.", "opened.")))
        Else
            MessageBox.Show(GetFormatedError(stsResult))
        End If
    End Sub

    Private Sub btnFilterQuery_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnFilterQuery.Click
        Dim iBuffer As UInt32

        ' Queries the current status of the message filter
        '
        If GetFilterStatus(iBuffer) Then
            Select Case iBuffer
                ' The filter is closed
                '
                Case PCANBasic.PCAN_FILTER_CLOSE
                    IncludeTextMessage("The Status of the filter is: closed.")
                    Exit Select
                    ' The filter is fully opened
                    '
                Case PCANBasic.PCAN_FILTER_OPEN
                    IncludeTextMessage("The Status of the filter is: full opened.")
                    Exit Select
                    ' The filter is customized
                    '
                Case PCANBasic.PCAN_FILTER_CUSTOM
                    IncludeTextMessage("The Status of the filter is: customized.")
                    Exit Select
                Case Else
                    ' The status of the filter is undefined. (Should never happen)
                    '
                    IncludeTextMessage("The Status of the filter is: Invalid.")
                    Exit Select
            End Select
        End If
    End Sub

    Private Sub cbbParameter_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cbbParameter.SelectedIndexChanged
        ' Activates/deactivates controls according with the selected 
        ' PCAN-Basic parameter 
        '
        rdbParamActive.Enabled = (TryCast(sender, ComboBox).SelectedIndex <> 0) And (TryCast(sender, ComboBox).SelectedIndex <> 20)
        rdbParamInactive.Enabled = rdbParamActive.Enabled
        nudDeviceIdOrDelay.Enabled = Not rdbParamActive.Enabled
        laDeviceOrDelay.Text = If((cbbParameter.SelectedIndex = 20), "Delay (μs):", "Device ID:")
    End Sub

    Private Sub btnParameterSet_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnParameterSet.Click
        Dim stsResult As TPCANStatus
        Dim iBuffer As UInt32
        Dim bActivate As Boolean

        bActivate = rdbParamActive.Checked

        ' Sets a PCAN-Basic parameter value
        '
        Select Case cbbParameter.SelectedIndex
            ' The Device-Number of an USB channel will be set
            '
            Case 0
                iBuffer = Convert.ToUInt32(nudDeviceIdOrDelay.Value)
                stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_DEVICE_NUMBER, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage("The desired Device-Number was successfully configured")
                End If
                Exit Select
                ' The 5 Volt Power feature of a PC-card or USB will be set
                '
            Case 1
                iBuffer = CUInt((If(bActivate, PCANBasic.PCAN_PARAMETER_ON, PCANBasic.PCAN_PARAMETER_OFF)))
                stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_5VOLTS_POWER, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The USB/PC-Card 5 power was successfully {0}", If(bActivate, "activated", "deactivated")))
                End If
                Exit Select
                ' The feature for automatic reset on BUS-OFF will be set
                '
            Case 2
                iBuffer = CUInt((If(bActivate, PCANBasic.PCAN_PARAMETER_ON, PCANBasic.PCAN_PARAMETER_OFF)))
                stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_BUSOFF_AUTORESET, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The automatic-reset on BUS-OFF was successfully {0}", If(bActivate, "activated", "deactivated")))
                End If
                Exit Select
                ' The CAN option "Listen Only" will be set
                '
            Case 3
                iBuffer = CUInt((If(bActivate, PCANBasic.PCAN_PARAMETER_ON, PCANBasic.PCAN_PARAMETER_OFF)))
                stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_LISTEN_ONLY, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The CAN option ""Listen Only"" was successfully {0}", If(bActivate, "activated", "deactivated")))
                End If
                Exit Select
                ' The feature for logging debug-information will be set
                '
            Case 4
                iBuffer = CUInt((If(bActivate, PCANBasic.PCAN_PARAMETER_ON, PCANBasic.PCAN_PARAMETER_OFF)))
                stsResult = PCANBasic.SetValue(PCANBasic.PCAN_NONEBUS, TPCANParameter.PCAN_LOG_STATUS, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The feature for logging debug information was successfully {0}", If(bActivate, "activated", "deactivated")))
                End If
                Exit Select
                ' The channel option "Receive Status" will be set
                '
            Case 5
                iBuffer = CUInt((If(bActivate, PCANBasic.PCAN_PARAMETER_ON, PCANBasic.PCAN_PARAMETER_OFF)))
                stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_RECEIVE_STATUS, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The channel option ""Receive Status"" was set to {0}", If(bActivate, "ON", "OFF")))
                End If
                Exit Select
                ' The feature for tracing will be set
                '
            Case 7
                iBuffer = CUInt((If(bActivate, PCANBasic.PCAN_PARAMETER_ON, PCANBasic.PCAN_PARAMETER_OFF)))
                stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_TRACE_STATUS, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The feature for tracing data was successfully {0}", If(bActivate, "activated", "deactivated")))
                End If
                Exit Select
                ' The feature for identifying an USB Channel will be set
                '
            Case 8
                iBuffer = CUInt((If(bActivate, PCANBasic.PCAN_PARAMETER_ON, PCANBasic.PCAN_PARAMETER_OFF)))
                stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_CHANNEL_IDENTIFYING, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The procedure for channel identification was successfully {0}", If(bActivate, "activated", "deactivated")))
                End If
                Exit Select
                ' The feature for using an already configured speed will be set
                '
            Case 10
                iBuffer = CUInt((If(bActivate, PCANBasic.PCAN_PARAMETER_ON, PCANBasic.PCAN_PARAMETER_OFF)))
                stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_BITRATE_ADAPTING, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The feature for bit rate adaptation was successfully {0}", If(bActivate, "activated", "deactivated")))
                End If
                Exit Select
                ' The option "Allow Status Frames" will be set
                '
            Case 17
                iBuffer = CUInt((If(bActivate, PCANBasic.PCAN_PARAMETER_ON, PCANBasic.PCAN_PARAMETER_OFF)))
                stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_ALLOW_STATUS_FRAMES, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The reception of Status frames was successfully {0}", If(bActivate, "enabled", "disabled")))
                End If
                Exit Select
                ' The option "Allow RTR Frames" will be set
                '
            Case 18
                iBuffer = CUInt((If(bActivate, PCANBasic.PCAN_PARAMETER_ON, PCANBasic.PCAN_PARAMETER_OFF)))
                stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_ALLOW_RTR_FRAMES, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The reception of RTR frames was successfully {0}", If(bActivate, "enabled", "disabled")))
                End If
                Exit Select

                ' The option "Allow Error Frames" will be set
                '
            Case 19
                iBuffer = CUInt((If(bActivate, PCANBasic.PCAN_PARAMETER_ON, PCANBasic.PCAN_PARAMETER_OFF)))
                stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_ALLOW_ERROR_FRAMES, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The reception of Error frames was successfully {0}", If(bActivate, "enabled", "disabled")))
                End If
                Exit Select

                ' The option "Interframes Delay" will be set
                '
            Case 20
                iBuffer = Convert.ToUInt32(nudDeviceIdOrDelay.Value)
                stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_INTERFRAME_DELAY, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage("The delay between transmitting frames was successfully set")
                End If
                Exit Select

            Case Else
                ' The current parameter is invalid
                '
                stsResult = TPCANStatus.PCAN_ERROR_UNKNOWN
                MessageBox.Show("Wrong parameter code.")
                Return
        End Select

        ' If the function fail, an error message is shown
        '
        If stsResult <> TPCANStatus.PCAN_ERROR_OK Then
            MessageBox.Show(GetFormatedError(stsResult))
        End If

    End Sub

    Private Sub btnParameterGet_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnParameterGet.Click
        Dim stsResult As TPCANStatus
        Dim iBuffer As UInt32
        Dim strBuffer As StringBuilder

        strBuffer = New StringBuilder(256)

        ' Gets a PCAN-Basic parameter value
        '
        Select Case cbbParameter.SelectedIndex
            ' The Device-Number of an USB channel will be retrieved
            '
            Case 0
                stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_DEVICE_NUMBER, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The configured Device-Number is {0:X}", iBuffer))
                End If
                Exit Select
                ' The activation status of the 5 Volt Power feature of a PC-card or USB will be retrieved
                '
            Case 1
                stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_5VOLTS_POWER, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The 5-Volt Power of the USB/PC-Card is {0:X}", If((iBuffer = PCANBasic.PCAN_PARAMETER_ON), "ON", "OFF")))
                End If
                Exit Select
                ' The activation status of the feature for automatic reset on BUS-OFF will be retrieved
                '
            Case 2
                stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_BUSOFF_AUTORESET, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The automatic-reset on BUS-OFF is {0:X}", If((iBuffer = PCANBasic.PCAN_PARAMETER_ON), "ON", "OFF")))
                End If
                Exit Select
                ' The activation status of the CAN option "Listen Only" will be retrieved
                '
            Case 3
                stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_LISTEN_ONLY, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The CAN option ""Listen Only"" is {0:X}", If((iBuffer = PCANBasic.PCAN_PARAMETER_ON), "ON", "OFF")))
                End If
                Exit Select
                ' The activation status for the feature for logging debug-information will be retrieved
            Case 4
                stsResult = PCANBasic.GetValue(PCANBasic.PCAN_NONEBUS, TPCANParameter.PCAN_LOG_STATUS, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The feature for logging debug information is {0:X}", If((iBuffer = PCANBasic.PCAN_PARAMETER_ON), "ON", "OFF")))
                End If
                Exit Select
                ' The activation status of the channel option "Receive Status"  will be retrieved
                '
            Case 5
                stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_RECEIVE_STATUS, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The channel option ""Receive Status"" is {0}", If((iBuffer = PCANBasic.PCAN_PARAMETER_ON), "ON", "OFF")))
                End If
                Exit Select
                ' The Number of the CAN-Controller used by a PCAN-Channel
                '
            Case 6
                stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_CONTROLLER_NUMBER, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The CAN Controller number is {0}", iBuffer))
                End If
                Exit Select
                ' The activation status for the feature for tracing data will be retrieved
                '
            Case 7
                stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_TRACE_STATUS, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The feature for tracing data is {0}", If((iBuffer = PCANBasic.PCAN_PARAMETER_ON), "ON", "OFF")))
                End If
                Exit Select
                ' The activation status of the Channel Identifying procedure will be retrieved
                '
            Case 8
                stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_CHANNEL_IDENTIFYING, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The identification procedure of the selected channel is {0}", If((iBuffer = PCANBasic.PCAN_PARAMETER_ON), "ON", "OFF")))
                End If
                Exit Select
            Case 9
                stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_CHANNEL_FEATURES, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The channel {0} Flexible Data-Rate (CAN-FD)", If(((iBuffer And PCANBasic.FEATURE_FD_CAPABLE) = PCANBasic.FEATURE_FD_CAPABLE), "does support", "DOESN'T SUPPORT")))
                    IncludeTextMessage(String.Format("The channel {0} an inter-frame delay for sending messages", If(((iBuffer And PCANBasic.FEATURE_DELAY_CAPABLE) = PCANBasic.FEATURE_DELAY_CAPABLE), "does support", "DOESN'T SUPPORT")))
                    IncludeTextMessage(String.Format("The channel {0} using I/O pins", If(((iBuffer And PCANBasic.FEATURE_IO_CAPABLE) = PCANBasic.FEATURE_IO_CAPABLE), "does allow", "DOESN'T ALLOW")))
                End If
                Exit Select
                ' The status of the speed adapting feature will be retrieved
                '
            Case 10
                stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_BITRATE_ADAPTING, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The feature for bit rate adaptation is {0}", If(((iBuffer And PCANBasic.FEATURE_FD_CAPABLE) = PCANBasic.FEATURE_FD_CAPABLE), "ON", "OFF")))
                End If
                Exit Select
                ' The bitrate of the connected channel will be retrieved (BTR0-BTR1 value)
                '
            Case 11
                stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_BITRATE_INFO, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The bit rate of the channel is {0:X4}h", iBuffer))
                End If
                Exit Select
                ' The bitrate of the connected FD channel will be retrieved (String value)
                '
            Case 12
                stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_BITRATE_INFO_FD, strBuffer, 255)
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage("The bit rate FD of the channel is represented by the following values:")
                    For Each strPart As String In strBuffer.ToString().Split(",")
                        IncludeTextMessage("   * " + strPart)
                    Next
                End If
                Exit Select
                ' The nominal speed configured on the CAN bus
                '
            Case 13
                stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_BUSSPEED_NOMINAL, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The nominal speed of the channel is {0} bit/s", iBuffer))
                End If
                Exit Select
                ' The data speed configured on the CAN bus
                '
            Case 14
                stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_BUSSPEED_DATA, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The data speed of the channel is {0} bit/s", iBuffer))
                End If
                Exit Select
                ' The IP address of a LAN channel as string, in IPv4 format
                '
            Case 15
                stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_IP_ADDRESS, strBuffer, 255)
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The IP address of the channel is {0}", strBuffer.ToString()))
                End If
                Exit Select
                ' The running status of the LAN service
                '
            Case 16
                stsResult = PCANBasic.GetValue(PCANBasic.PCAN_NONEBUS, TPCANParameter.PCAN_LAN_SERVICE_STATUS, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The LAN service is {0}", If((iBuffer = PCANBasic.SERVICE_STATUS_RUNNING), "running", "NOT running")))
                End If
                Exit Select
                ' The reception of Status frames
                '
            Case 17
                stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_ALLOW_STATUS_FRAMES, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The reception of Status frames is {0}", If((iBuffer = PCANBasic.PCAN_PARAMETER_ON), "enabled", "disabled")))
                End If
                Exit Select
                ' The reception of RTR frames
                '
            Case 18
                stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_ALLOW_RTR_FRAMES, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The reception of RTR frames is {0}", If((iBuffer = PCANBasic.PCAN_PARAMETER_ON), "enabled", "disabled")))
                End If
                Exit Select
                ' The reception of Error frames
                '
            Case 19
                stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_ALLOW_ERROR_FRAMES, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The reception of Error frames is {0}", If((iBuffer = PCANBasic.PCAN_PARAMETER_ON), "enabled", "disabled")))
                End If
                Exit Select
                ' The Interframe delay of an USB channel will be retrieved
                '
            Case 20
                stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_INTERFRAME_DELAY, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
                If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                    IncludeTextMessage(String.Format("The configured interframe delay is {0} μs", iBuffer))
                End If
                Exit Select
            Case Else
                ' The current parameter is invalid
                '
                stsResult = TPCANStatus.PCAN_ERROR_UNKNOWN
                MessageBox.Show("Wrong parameter code.")
                Return
        End Select

        ' If the function fail, an error message is shown
        '
        If stsResult <> TPCANStatus.PCAN_ERROR_OK Then
            MessageBox.Show(GetFormatedError(stsResult))
        End If
    End Sub

    Private Sub rdbTimer_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles rdbTimer.CheckedChanged, rdbManual.CheckedChanged, rdbEvent.CheckedChanged
        ''Checks Form Initialization is complete 
        '      If Not isFormInitCompleted Then
        '           Return
        '        End If

        If Not btnRelease.Enabled Then
            Return
        End If

        ' According with the kind of reading, a timer, a thread or a button will be enabled
        '
        If rdbTimer.Checked Then
            ' Abort Read Thread if it exists
            '
            If m_ReadThread IsNot Nothing Then
                m_ReadThread.Abort()
                m_ReadThread.Join()
                m_ReadThread = Nothing
            End If

            ' Enable Timer
            '
            tmrRead.Enabled = btnRelease.Enabled
        End If
        If rdbEvent.Checked Then
            ' Disable Timer
            '
            tmrRead.Enabled = False
            ' Create and start the tread to read CAN Message using SetRcvEvent()
            '
            Dim threadDelegate As New System.Threading.ThreadStart(AddressOf Me.CANReadThreadFunc)
            m_ReadThread = New System.Threading.Thread(threadDelegate)
            m_ReadThread.IsBackground = True
            m_ReadThread.Start()
        End If
        If rdbManual.Checked Then
            ' Abort Read Thread if it exists
            '
            If m_ReadThread IsNot Nothing Then
                m_ReadThread.Abort()
                m_ReadThread.Join()
                m_ReadThread = Nothing
            End If
            ' Disable Timer
            '
            tmrRead.Enabled = False
            btnRead.Enabled = btnRelease.Enabled AndAlso rdbManual.Checked
        End If
    End Sub

    Private Sub chbShowPeriod_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles chbShowPeriod.CheckedChanged
        ' According with the check-value of this checkbox,
        ' the recieved time of a messages will be interpreted as 
        ' period (time between the two last messages) or as time-stamp
        ' (the elapsed time since windows was started)
        '
        SyncLock m_LastMsgsList.SyncRoot
            For Each msg As MessageStatus In m_LastMsgsList
                msg.ShowingPeriod = chbShowPeriod.Checked
            Next
        End SyncLock
    End Sub

    Private Sub btnRead_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnRead.Click
        Dim stsResult As TPCANStatus

        ' We execute the "Read" function of the PCANBasic                
        '
        stsResult = If(m_IsFD, ReadMessageFD(), ReadMessage())
        If stsResult = TPCANStatus.PCAN_ERROR_OK Then
            ' If an error occurred, an information message is included
            '
            IncludeTextMessage(GetFormatedError(stsResult))
        End If
    End Sub

    Private Sub btnMsgClear_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnMsgClear.Click
        ' The information contained in the messages List-View
        ' is cleared
        '
        SyncLock m_LastMsgsList.SyncRoot
            lstMessages.Items.Clear()
            m_LastMsgsList.Clear()
        End SyncLock
    End Sub

    Private Sub txtID_KeyPress(ByVal sender As System.Object, ByVal e As System.Windows.Forms.KeyPressEventArgs) Handles txtID.KeyPress, txtData9.KeyPress, txtData8.KeyPress, txtData7.KeyPress, txtData63.KeyPress, txtData62.KeyPress, txtData61.KeyPress, txtData60.KeyPress, txtData6.KeyPress, txtData59.KeyPress, txtData58.KeyPress, txtData57.KeyPress, txtData56.KeyPress, txtData55.KeyPress, txtData54.KeyPress, txtData53.KeyPress, txtData52.KeyPress, txtData51.KeyPress, txtData50.KeyPress, txtData5.KeyPress, txtData49.KeyPress, txtData48.KeyPress, txtData47.KeyPress, txtData46.KeyPress, txtData45.KeyPress, txtData44.KeyPress, txtData43.KeyPress, txtData42.KeyPress, txtData41.KeyPress, txtData40.KeyPress, txtData4.KeyPress, txtData39.KeyPress, txtData38.KeyPress, txtData37.KeyPress, txtData36.KeyPress, txtData35.KeyPress, txtData34.KeyPress, txtData33.KeyPress, txtData32.KeyPress, txtData31.KeyPress, txtData30.KeyPress, txtData3.KeyPress, txtData29.KeyPress, txtData28.KeyPress, txtData27.KeyPress, txtData26.KeyPress, txtData25.KeyPress, txtData24.KeyPress, txtData23.KeyPress, txtData22.KeyPress, txtData21.KeyPress, txtData20.KeyPress, txtData2.KeyPress, txtData19.KeyPress, txtData18.KeyPress, txtData17.KeyPress, txtData16.KeyPress, txtData15.KeyPress, txtData14.KeyPress, txtData13.KeyPress, txtData12.KeyPress, txtData11.KeyPress, txtData10.KeyPress, txtData1.KeyPress, txtData0.KeyPress
        Dim chCheck As Int16

        ' We convert the Character to its Upper case equivalent
        '
        chCheck = Microsoft.VisualBasic.Asc(e.KeyChar.ToString().ToUpper())

        ' The Key is the Delete (Backspace) Key
        '
        If chCheck = 8 Then
            Return
        End If
        ' The Key is a number between 0-9
        '
        If (chCheck > 47) AndAlso (chCheck < 58) Then
            Return
        End If
        ' The Key is a character between A-F
        '
        If (chCheck > 64) AndAlso (chCheck < 71) Then
            Return
        End If

        ' Is neither a number nor a character between A(a) and F(f)
        '
        e.Handled = True

    End Sub

    Private Sub txtID_Leave(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtID.Leave
        Dim iTextLength As Integer
        Dim uiMaxValue As UInteger

        ' Calculates the text length and Maximum ID value according
        ' with the Message Type
        '
        iTextLength = If((chbExtended.Checked), 8, 3)
        uiMaxValue = If((chbExtended.Checked), CUInt(&H1FFFFFFF), CUInt(&H7FF))

        ' The Textbox for the ID is represented with 3 characters for 
        ' Standard and 8 characters for extended messages.
        ' Therefore if the Length of the text is smaller than TextLength,  
        ' we add "0"
        '
        While txtID.Text.Length <> iTextLength
            txtID.Text = ("0" & txtID.Text)
        End While

        ' We check that the ID is not bigger than current maximum value
        '
        If Convert.ToUInt32(txtID.Text, 16) > uiMaxValue Then
            txtID.Text = String.Format("{0:X" & iTextLength.ToString() & "}", uiMaxValue)
        End If
    End Sub

    Private Sub chbExtended_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles chbExtended.CheckedChanged
        Dim uiTemp As UInteger

        txtID.MaxLength = If((chbExtended.Checked), 8, 3)

        ' the only way that the text length can be bigger als MaxLength
        ' is when the change is from Extended to Standard message Type.
        ' We have to handle this and set an ID not bigger than the Maximum
        ' ID value for a Standard Message (0x7FF)
        '
        If txtID.Text.Length > txtID.MaxLength Then
            uiTemp = Convert.ToUInt32(txtID.Text, 16)
            txtID.Text = If((uiTemp < &H7FF), String.Format("{0:X3}", uiTemp), "7FF")
        End If

        txtID_Leave(Me, New EventArgs())
    End Sub

    Private Sub chbRemote_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles chbRemote.CheckedChanged
        Dim txtbCurrentTextBox As TextBox

        txtbCurrentTextBox = txtData0

        chbFD.Enabled = Not chbRemote.Checked
        If (chbRemote.Checked) Then
            chbBRS.Checked = False
        End If

        ' If the message is a RTR, no data is sent. The textboxes for data 
        ' will be disabled
        ' 
        For i As Integer = 0 To nudLength.Value
            txtbCurrentTextBox.Enabled = Not chbRemote.Checked
            If i < nudLength.Value Then
                txtbCurrentTextBox = DirectCast(Me.GetNextControl(txtbCurrentTextBox, True), TextBox)
            End If
        Next
    End Sub

    Private Sub txtData0_Leave(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtData9.Leave, txtData8.Leave, txtData7.Leave, txtData63.Leave, txtData62.Leave, txtData61.Leave, txtData60.Leave, txtData6.Leave, txtData59.Leave, txtData58.Leave, txtData57.Leave, txtData56.Leave, txtData55.Leave, txtData54.Leave, txtData53.Leave, txtData52.Leave, txtData51.Leave, txtData50.Leave, txtData5.Leave, txtData49.Leave, txtData48.Leave, txtData47.Leave, txtData46.Leave, txtData45.Leave, txtData44.Leave, txtData43.Leave, txtData42.Leave, txtData41.Leave, txtData40.Leave, txtData4.Leave, txtData39.Leave, txtData38.Leave, txtData37.Leave, txtData36.Leave, txtData35.Leave, txtData34.Leave, txtData33.Leave, txtData32.Leave, txtData31.Leave, txtData30.Leave, txtData3.Leave, txtData29.Leave, txtData28.Leave, txtData27.Leave, txtData26.Leave, txtData25.Leave, txtData24.Leave, txtData23.Leave, txtData22.Leave, txtData21.Leave, txtData20.Leave, txtData2.Leave, txtData19.Leave, txtData18.Leave, txtData17.Leave, txtData16.Leave, txtData15.Leave, txtData14.Leave, txtData13.Leave, txtData12.Leave, txtData11.Leave, txtData10.Leave, txtData1.Leave, txtData0.Leave
        Dim txtbCurrentTextbox As TextBox

        ' all the Textbox Data fields are represented with 2 characters.
        ' Therefore if the Length of the text is smaller than 2, we add
        ' a "0"
        '
        If sender.[GetType]().Name = "TextBox" Then
            txtbCurrentTextbox = DirectCast(sender, TextBox)
            While txtbCurrentTextbox.Text.Length <> 2
                txtbCurrentTextbox.Text = ("0" & txtbCurrentTextbox.Text)
            End While
        End If
    End Sub

    Private Function WriteFrame()
        Dim CANMsg As TPCANMsg
        Dim txtbCurrentTextBox As TextBox

        ' We create a TPCANMsg message structure 
        '
        CANMsg = New TPCANMsg()
        CANMsg.DATA = CType(Array.CreateInstance(GetType(Byte), 8), Byte())

        ' We configurate the Message.  The ID,
        ' Length of the Data, Message Type
        ' and die data
        '
        CANMsg.ID = Convert.ToInt32(txtID.Text, 16)
        CANMsg.LEN = Convert.ToByte(nudLength.Value)
        CANMsg.MSGTYPE = If(chbExtended.Checked, TPCANMessageType.PCAN_MESSAGE_EXTENDED, TPCANMessageType.PCAN_MESSAGE_STANDARD)
        ' If a remote frame will be sent, the data bytes are not important.
        '
        If (chbRemote.Checked) Then
            CANMsg.MSGTYPE = CANMsg.MSGTYPE Or TPCANMessageType.PCAN_MESSAGE_RTR
        Else
            ' We get so much data as the Len of the message
            '
            For I As Integer = 0 To GetLengthFromDLC(CANMsg.LEN, True) - 1
                txtbCurrentTextBox = DirectCast(Me.Controls.Find("txtData" + I.ToString(), True)(0), TextBox)
                CANMsg.DATA(I) = Convert.ToByte(txtbCurrentTextBox.Text, 16)
            Next

        End If

        ' The message is sent to the configured hardware
        '
        Return PCANBasic.Write(m_PcanHandle, CANMsg)
    End Function

    Private Function WriteFrameFD()
        Dim CANMsg As TPCANMsgFD
        Dim txtbCurrentTextBox As TextBox
        Dim iLength As Integer

        ' We create a TPCANMsg message structure 
        '
        CANMsg = New TPCANMsgFD()
        CANMsg.DATA = CType(Array.CreateInstance(GetType(Byte), 64), Byte())

        ' We configurate the Message.  The ID,
        ' Length of the Data, Message Type
        ' and die data
        '
        CANMsg.ID = Convert.ToInt32(txtID.Text, 16)
        CANMsg.DLC = Convert.ToByte(nudLength.Value)
        CANMsg.MSGTYPE = If(chbExtended.Checked, TPCANMessageType.PCAN_MESSAGE_EXTENDED, TPCANMessageType.PCAN_MESSAGE_STANDARD)
        CANMsg.MSGTYPE = CANMsg.MSGTYPE Or If(chbFD.Checked, TPCANMessageType.PCAN_MESSAGE_FD, TPCANMessageType.PCAN_MESSAGE_STANDARD)
        CANMsg.MSGTYPE = CANMsg.MSGTYPE Or If(chbBRS.Checked, TPCANMessageType.PCAN_MESSAGE_BRS, TPCANMessageType.PCAN_MESSAGE_STANDARD)

        ' If a remote frame will be sent, the data bytes are not important.
        '
        If (chbRemote.Checked) Then
            CANMsg.MSGTYPE = CANMsg.MSGTYPE Or TPCANMessageType.PCAN_MESSAGE_RTR
        Else
            ' We get so much data as the Len of the message
            '
            iLength = GetLengthFromDLC(CANMsg.DLC, (CANMsg.MSGTYPE And TPCANMessageType.PCAN_MESSAGE_FD) = 0)
            For I As Integer = 0 To iLength - 1
                txtbCurrentTextBox = DirectCast(Me.Controls.Find("txtData" + I.ToString(), True)(0),TextBox)
                CANMsg.DATA(I) = Convert.ToByte(txtbCurrentTextBox.Text, 16)
            Next

        End If

        ' The message is sent to the configured hardware
        '
        Return PCANBasic.WriteFD(m_PcanHandle, CANMsg)
    End Function

    Private Sub btnWrite_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnWrite.Click
        Dim stsResult As TPCANStatus

        ' Send the message
        '
        stsResult = If(m_IsFD, WriteFrameFD(), WriteFrame())

        ' The message was successfully sent
        '
        If (stsResult = TPCANStatus.PCAN_ERROR_OK) Then
            IncludeTextMessage("Message was successfully SENT")
        Else
            ' An error occurred.  We show the error.
            '
            MessageBox.Show(GetFormatedError(stsResult))
        End If
    End Sub

    Private Sub btnGetVersions_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnGetVersions.Click
        Dim stsResult As TPCANStatus
        Dim strTemp As StringBuilder
        Dim strArrayVersion As String()

        strTemp = New StringBuilder(256)

        ' We get the vesion of the PCAN-Basic API
        '
        stsResult = PCANBasic.GetValue(PCANBasic.PCAN_NONEBUS, TPCANParameter.PCAN_API_VERSION, strTemp, 256)
        If stsResult = TPCANStatus.PCAN_ERROR_OK Then
            IncludeTextMessage("API Version: " & strTemp.ToString())
            ' We get the driver version of the channel being used
            '
            stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_CHANNEL_VERSION, strTemp, 256)
            If stsResult = TPCANStatus.PCAN_ERROR_OK Then
                ' Because this information contains line control characters (several lines)
                ' we split this also in several entries in the Information List-Box
                '
                strArrayVersion = strTemp.ToString().Split(New Char() {ControlChars.Lf})
                IncludeTextMessage("Channel/Driver Version: ")
                For i As Integer = 0 To strArrayVersion.Length - 1
                    IncludeTextMessage("     * " & strArrayVersion(i))
                Next
            End If
        End If

        ' If an error ccurred, a message is shown
        '
        If stsResult <> TPCANStatus.PCAN_ERROR_OK Then
            MessageBox.Show(GetFormatedError(stsResult))
        End If
    End Sub

    Private Sub btnInfoClear_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnInfoClear.Click
        ' The information contained in the Information List-Box 
        ' is cleared
        lbxInfo.Items.Clear()
    End Sub

    Private Sub Form_FormClosing(ByVal sender As System.Object, ByVal e As System.Windows.Forms.FormClosingEventArgs) Handles MyBase.FormClosing
        ' Releases the used PCAN-Basic channel
        '
        If (btnRelease.Enabled) Then
            btnRelease_Click(Me, New EventArgs())
        End If
    End Sub

    Private Sub tmrRead_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles tmrRead.Tick
        '' Checks if in the receive-queue are currently messages for read
        ReadMessages()
    End Sub

    Private Sub tmrDisplay_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles tmrDisplay.Tick
        DisplayMessages()
    End Sub

    Private Sub Form_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        nudLength.Value = 8
        chbShowPeriod.Checked = True
        rdbParamActive.Checked = True
        rdbTimer.Checked = True
        rdbFilterOpen.Checked = True
    End Sub

    Private Sub lstMessages_DoubleClick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles lstMessages.DoubleClick
        ' Clears the content of the Message List-View
        '
        btnMsgClear_Click(Me, New EventArgs())
    End Sub

    Private Sub lbxInfo_DoubleClick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles lbxInfo.Click
        ' Clears the content of the Information List-Box
        '
        btnInfoClear_Click(Me, New EventArgs())
    End Sub

    Private Sub btnReset_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnReset.Click
        Dim stsResult As TPCANStatus

        ' Resets the receive and transmit queues of a PCAN Channel.
        '
        stsResult = PCANBasic.Reset(m_PcanHandle)

        ' If it fails, a error message is shown
        '
        If (stsResult <> TPCANStatus.PCAN_ERROR_OK) Then
            MessageBox.Show(GetFormatedError(stsResult))
        Else
            IncludeTextMessage("Receive and transmit queues successfully reset")
        End If

    End Sub

    Private Sub btnStatus_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnStatus.Click
        Dim stsResult As TPCANStatus
        Dim errorName As String

        ' Gets the current BUS status of a PCAN Channel.
        '
        stsResult = PCANBasic.GetStatus(m_PcanHandle)

        ' Switch On Error Name
        '
        Select Case stsResult
            Case TPCANStatus.PCAN_ERROR_INITIALIZE
                errorName = "PCAN_ERROR_INITIALIZE"
                Exit Select

            Case TPCANStatus.PCAN_ERROR_BUSLIGHT
                errorName = "PCAN_ERROR_BUSLIGHT"
                Exit Select

            Case TPCANStatus.PCAN_ERROR_BUSHEAVY ' TPCANStatus.PCAN_ERROR_BUSWARNING
                errorName = If(m_IsFD, "PCAN_ERROR_BUSWARNING", "PCAN_ERROR_BUSHEAVY")
                Exit Select

            Case TPCANStatus.PCAN_ERROR_BUSPASSIVE
                errorName = "PCAN_ERROR_BUSPASSIVE"
                Exit Select

            Case TPCANStatus.PCAN_ERROR_BUSOFF
                errorName = "PCAN_ERROR_BUSOFF"
                Exit Select

            Case TPCANStatus.PCAN_ERROR_OK
                errorName = "PCAN_ERROR_OK"
                Exit Select
            Case Else
                errorName = "See Documentation"
                Exit Select
        End Select

        ' Display Message
        '
        IncludeTextMessage(String.Format("Status: {0} ({1:X}h)", errorName, stsResult))
    End Sub

    Private Sub nudLength_ValueChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles nudLength.ValueChanged
        Dim txtbCurrentTextBox As TextBox
        Dim iLength As Integer

        txtbCurrentTextBox = txtData0
        iLength = GetLengthFromDLC(nudLength.Value, Not chbFD.Checked)
        laLength.Text = String.Format("{0} B.", iLength)

        For i As Integer = 0 To 64
            txtbCurrentTextBox.Enabled = i <= iLength
            If (i < 64) Then
                txtbCurrentTextBox = DirectCast(Me.Controls.Find("txtData" + i.ToString(), True)(0), TextBox)
            End If
        Next
    End Sub

    Private Sub chbFD_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles chbFD.CheckedChanged
        chbRemote.Enabled = Not chbFD.Checked
        chbBRS.Enabled = chbFD.Checked
        If (Not chbBRS.Enabled) Then
            chbBRS.Checked = False
        End If
        nudLength.Maximum = If(chbFD.Checked, 15, 8)
    End Sub

    Private Sub rdbCAN_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles chbCanFD.CheckedChanged
        m_IsFD = chbCanFD.Checked

        cbbBaudrates.Visible = Not m_IsFD
        cbbHwType.Visible = Not m_IsFD
        cbbInterrupt.Visible = Not m_IsFD
        cbbIO.Visible = Not m_IsFD
        laBaudrate.Visible = Not m_IsFD
        laHwType.Visible = Not m_IsFD
        laIOPort.Visible = Not m_IsFD
        laInterrupt.Visible = Not m_IsFD

        txtBitrate.Visible = m_IsFD
        laBitrate.Visible = m_IsFD
        chbFD.Visible = m_IsFD
        chbBRS.Visible = m_IsFD

        If ((nudLength.Maximum > 8) And (Not m_IsFD)) Then
            chbFD.Checked = False
        End If
    End Sub

#End Region

#Region "Help functions"
    ''' <summary>
    ''' Convert a CAN DLC value into the actual data length of the CAN/CAN-FD frame.
    ''' </summary>
    ''' <param name="dlc">A value between 0 and 15 (CAN and FD DLC range)</param>
    ''' <param name="isSTD">A value indicating if the msg is a standard CAN (FD Flag not checked)</param>
    ''' <returns>The length represented by the DLC</returns>
    Public Shared Function GetLengthFromDLC(ByVal dlc As Integer, ByVal isSTD As Boolean)
        If dlc <= 8 Then
            Return dlc
        End If

        If (isSTD) Then
            Return 8
        End If

        Select Case dlc
            Case 9
                Return 12
            Case 10
                Return 16
            Case 11
                Return 20
            Case 12
                Return 24
            Case 13
                Return 32
            Case 14
                Return 48
            Case 15
                Return 64
            Case Else
                Return dlc
        End Select
    End Function

    ''' <summary>
    ''' Initialization of PCAN-Basic components
    ''' </summary>
    Private Sub InitializeBasicComponents()
        ' Creates the list for received messages
        '
        m_LastMsgsList = New System.Collections.ArrayList()
        ' Creates the delegate used for message reading
        '
        m_ReadDelegate = New ReadDelegateHandler(AddressOf ReadMessages)
        ' Creates the event used for signalize incomming messages 
        '
        m_ReceiveEvent = New System.Threading.AutoResetEvent(False)
        ' Creates an array with all possible PCAN-Channels
        '
        m_HandlesArray = New TPCANHandle() {PCANBasic.PCAN_ISABUS1, PCANBasic.PCAN_ISABUS2, PCANBasic.PCAN_ISABUS3, PCANBasic.PCAN_ISABUS4, PCANBasic.PCAN_ISABUS5, PCANBasic.PCAN_ISABUS6, _
         PCANBasic.PCAN_ISABUS7, PCANBasic.PCAN_ISABUS8, PCANBasic.PCAN_DNGBUS1, PCANBasic.PCAN_PCIBUS1, PCANBasic.PCAN_PCIBUS2, PCANBasic.PCAN_PCIBUS3, _
         PCANBasic.PCAN_PCIBUS4, PCANBasic.PCAN_PCIBUS5, PCANBasic.PCAN_PCIBUS6, PCANBasic.PCAN_PCIBUS7, PCANBasic.PCAN_PCIBUS8, PCANBasic.PCAN_PCIBUS9, _
         PCANBasic.PCAN_PCIBUS10, PCANBasic.PCAN_PCIBUS11, PCANBasic.PCAN_PCIBUS12, PCANBasic.PCAN_PCIBUS13, PCANBasic.PCAN_PCIBUS14, PCANBasic.PCAN_PCIBUS15, _
         PCANBasic.PCAN_USBBUS1, PCANBasic.PCAN_USBBUS2, PCANBasic.PCAN_USBBUS3, PCANBasic.PCAN_USBBUS4, PCANBasic.PCAN_USBBUS5, PCANBasic.PCAN_USBBUS6, _
         PCANBasic.PCAN_USBBUS7, PCANBasic.PCAN_USBBUS8, PCANBasic.PCAN_USBBUS9, PCANBasic.PCAN_USBBUS10, PCANBasic.PCAN_USBBUS11, PCANBasic.PCAN_USBBUS12, _
         PCANBasic.PCAN_USBBUS13, PCANBasic.PCAN_USBBUS14, PCANBasic.PCAN_USBBUS15, PCANBasic.PCAN_USBBUS16, PCANBasic.PCAN_PCCBUS1, PCANBasic.PCAN_PCCBUS2, _
         PCANBasic.PCAN_LANBUS1, PCANBasic.PCAN_LANBUS2, PCANBasic.PCAN_LANBUS3, PCANBasic.PCAN_LANBUS4, PCANBasic.PCAN_LANBUS5, PCANBasic.PCAN_LANBUS6, _
         PCANBasic.PCAN_LANBUS7, PCANBasic.PCAN_LANBUS8, PCANBasic.PCAN_LANBUS9, PCANBasic.PCAN_LANBUS10, PCANBasic.PCAN_LANBUS11, PCANBasic.PCAN_LANBUS12, _
         PCANBasic.PCAN_LANBUS13, PCANBasic.PCAN_LANBUS14, PCANBasic.PCAN_LANBUS15, PCANBasic.PCAN_LANBUS16}

        ' Fills and configures the Data of several comboBox components
        '
        FillComboBoxData()

        ' Prepares the PCAN-Basic's debug-Log file
        '
        ConfigureLogFile()
    End Sub

    ''' <summary>
    ''' Configures the Debug-Log file of PCAN-Basic
    ''' </summary>
    Private Sub ConfigureLogFile()
        Dim iBuffer As UInt32

        ' Sets the mask to catch all events
        '
        iBuffer = PCANBasic.LOG_FUNCTION_ALL

        ' Configures the log file. 
        ' NOTE: The Log capability is to be used with the NONEBUS Handle. Other handle than this will 
        ' cause the function fail.
        '
        PCANBasic.SetValue(PCANBasic.PCAN_NONEBUS, TPCANParameter.PCAN_LOG_CONFIGURE, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
    End Sub

    ''' <summary>
    ''' Configures the Debug-Log file of PCAN-Basic
    ''' </summary>
    Private Sub ConfigureTraceFile()
        Dim iBuffer As UInt32
        Dim stsResult As TPCANStatus

        ' Configure the maximum size of a trace file to 5 megabytes
        '
        iBuffer = 5
        stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_TRACE_SIZE, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
        If stsResult <> TPCANStatus.PCAN_ERROR_OK Then
            IncludeTextMessage(GetFormatedError(stsResult))
        End If

        ' Configure the way how trace files are created: 
        ' * Standard name is used
        ' * Existing file is ovewritten,
        ' * Only one file is created.
        ' * Recording stopts when the file size reaches 5 megabytes.
        '
        iBuffer = PCANBasic.TRACE_FILE_SINGLE Or PCANBasic.TRACE_FILE_OVERWRITE
        stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_TRACE_CONFIGURE, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))
        If stsResult <> TPCANStatus.PCAN_ERROR_OK Then
            IncludeTextMessage(GetFormatedError(stsResult))
        End If
    End Sub

    ''' <summary>
    ''' Help Function used to get an error as text
    ''' </summary>
    ''' <param name="error">Error code to be translated</param>
    ''' <returns>A text with the translated error</returns>
    Private Function GetFormatedError(ByVal [error] As TPCANStatus) As String
        Dim strTemp As StringBuilder

        ' Creates a buffer big enough for a error-text
        '
        strTemp = New StringBuilder(256)
        ' Gets the text using the GetErrorText API function
        ' If the function success, the translated error is returned. If it fails,
        ' a text describing the current error is returned.
        '
        If PCANBasic.GetErrorText([error], 0, strTemp) <> TPCANStatus.PCAN_ERROR_OK Then
            Return String.Format("An error occurred. Error-code's text ({0:X}) couldn't be retrieved", [error])
        Else
            Return strTemp.ToString()
        End If
    End Function

    ''' <summary>
    ''' Includes a new line of text into the information Listview
    ''' </summary>
    ''' <param name="strMsg">Text to be included</param>
    Private Sub IncludeTextMessage(ByVal strMsg As String)
        lbxInfo.Items.Add(strMsg)
        lbxInfo.SelectedIndex = lbxInfo.Items.Count - 1
    End Sub

    ''' <summary>
    ''' Gets the current status of the PCAN-Basic message filter
    ''' </summary>
    ''' <param name="status">Buffer to retrieve the filter status</param>
    ''' <returns>If calling the function was successfull or not</returns>
    Private Function GetFilterStatus(ByRef status As UInteger) As Boolean
        Dim stsResult As TPCANStatus

        ' Tries to get the sttaus of the filter for the current connected hardware
        '
        stsResult = PCANBasic.GetValue(m_PcanHandle, TPCANParameter.PCAN_MESSAGE_FILTER, status, CType(System.Runtime.InteropServices.Marshal.SizeOf(status), UInteger))

        ' If it fails, a error message is shown
        '
        If stsResult <> TPCANStatus.PCAN_ERROR_OK Then
            MessageBox.Show(GetFormatedError(stsResult))
            Return False
        End If
        Return True
    End Function

    ''' <summary>
    ''' Configures the data of all ComboBox components of the main-form
    ''' </summary>
    Private Sub FillComboBoxData()
        ' Channels will be check
        '
        btnHwRefresh_Click(Me, New EventArgs())

        ' FD Bitrate: 
        '      Arbitration: 1 Mbit/sec 
        '      Data: 2 Mbit/sec
        '
        txtBitrate.Text = "f_clock_mhz=20, nom_brp=5, nom_tseg1=2, nom_tseg2=1, nom_sjw=1, data_brp=2, data_tseg1=3, data_tseg2=1, data_sjw=1"

        ' Baudrates 
        '
        cbbBaudrates.SelectedIndex = 2 ' 500 K
        ' Hardware Type for no plugAndplay hardware
        '
        cbbHwType.SelectedIndex = 0

        ' Interrupt for no plugAndplay hardware
        '
        cbbInterrupt.SelectedIndex = 0

        ' IO Port for no plugAndplay hardware
        '
        cbbIO.SelectedIndex = 0

        ' Parameters for GetValue and SetValue function calls
        '
        cbbParameter.SelectedIndex = 0
    End Sub

    ''' <summary>
    ''' Activates/deaactivates the different controls of the main-form according
    ''' with the current connection status
    ''' </summary>
    ''' <param name="bConnected">Current status. True if connected, false otherwise</param>
    Private Sub SetConnectionStatus(ByVal bConnected As Boolean)
        ' Buttons
        '
        btnInit.Enabled = Not bConnected
        btnRead.Enabled = bConnected AndAlso rdbManual.Checked
        btnWrite.Enabled = bConnected
        btnRelease.Enabled = bConnected
        btnFilterApply.Enabled = bConnected
        btnFilterQuery.Enabled = bConnected
        btnGetVersions.Enabled = bConnected
        btnHwRefresh.Enabled = Not bConnected
        btnStatus.Enabled = bConnected
        btnReset.Enabled = bConnected

        ' ComboBoxs
        '
        cbbBaudrates.Enabled = Not bConnected
        cbbChannel.Enabled = Not bConnected
        cbbHwType.Enabled = Not bConnected
        cbbIO.Enabled = Not bConnected
        cbbInterrupt.Enabled = Not bConnected

        ' Check-Buttons
        '
        chbCanFD.Enabled = Not bConnected

        ' Hardware configuration and read mode
        '
        If Not bConnected Then
            cbbChannel_SelectedIndexChanged(Me, New EventArgs())
        Else
            rdbTimer_CheckedChanged(Me, New EventArgs())
        End If

        ' Display messages in grid
        '
        tmrDisplay.Enabled = bConnected
    End Sub

    ''' <summary>
    ''' Gets the formated text for a CPAN-Basic channel handle
    ''' </summary>
    ''' <param name="handle">PCAN-Basic Handle to format</param>
    ''' <param name="isFD">If the channel is FD capable</param>
    ''' <returns>The formatted text for a channel</returns>
    Private Function FormatChannelName(ByVal handle As TPCANHandle, ByVal isFD As Boolean) As String
        Dim devDevice As TPCANDevice
        Dim byChannel As Byte

        ' Gets the owner device and channel for a 
        ' PCAN-Basic handle
        '
        If CType(handle, UShort) < &H100 Then
            devDevice = DirectCast(CType(handle >> 4, Byte), TPCANDevice)
            byChannel = CByte((handle And &HF))
        Else
            devDevice = DirectCast(CType(handle >> 8, Byte), TPCANDevice)
            byChannel = CByte((handle And &HFF))
        End If

        ' Constructs the PCAN-Basic Channel name and return it
        '
        If (isFD) Then
            Return String.Format("{0}:FD {1} ({2:X2}h)", devDevice, byChannel, handle)
        Else
            Return String.Format("{0} {1} ({2:X2}h)", devDevice, byChannel, handle)
        End If
    End Function

    ''' <summary>
    ''' Gets the formated text for a CPAN-Basic channel handle
    ''' </summary>
    ''' <param name="handle">PCAN-Basic Handle to format</param>
    ''' <returns>The formatted text for a channel</returns>
    Private Function FormatChannelName(ByVal handle As TPCANHandle) As String
        Return FormatChannelName(handle, False)
    End Function
#End Region

#Region "Message-proccessing functions"
    ''' <summary>
    ''' Display CAN messages in the Message-ListView
    ''' </summary>
    Private Sub DisplayMessages()
        Dim lviCurrentItem As ListViewItem

        SyncLock m_LastMsgsList.SyncRoot
            For Each msgStatus As MessageStatus In m_LastMsgsList
                ' Get the data to actualize
                '
                If msgStatus.MarkedAsUpdated Then
                    msgStatus.MarkedAsUpdated = False
                    lviCurrentItem = lstMessages.Items(msgStatus.Position)

                    lviCurrentItem.SubItems(2).Text = GetLengthFromDLC(msgStatus.CANMsg.DLC, (msgStatus.CANMsg.MSGTYPE And TPCANMessageType.PCAN_MESSAGE_FD) = 0).ToString()
                    lviCurrentItem.SubItems(3).Text = msgStatus.Count.ToString()
                    lviCurrentItem.SubItems(4).Text = msgStatus.TimeString
                    lviCurrentItem.SubItems(5).Text = msgStatus.DataString
                End If
            Next
        End SyncLock
    End Sub

    ''' <summary>
    ''' Inserts a new entry for a new message in the Message-ListView
    ''' </summary>
    ''' <param name="newMsg">The messasge to be inserted</param>
    ''' <param name="timeStamp">The Timesamp of the new message</param>
    Private Sub InsertMsgEntry(ByVal newMsg As TPCANMsgFD, ByVal timeStamp As TPCANTimestampFD)
        Dim lviCurrentItem As ListViewItem
        Dim msgStsCurrentMsg As MessageStatus

        SyncLock m_LastMsgsList.SyncRoot
            ' We add this status in the last message list
            '
            msgStsCurrentMsg = New MessageStatus(newMsg, timeStamp, lstMessages.Items.Count)
            msgStsCurrentMsg.ShowingPeriod = chbShowPeriod.Checked
            m_LastMsgsList.Add(msgStsCurrentMsg)

            ' Add the new ListView Item with the Type of the message
            '	
            lviCurrentItem = lstMessages.Items.Add(msgStsCurrentMsg.TypeString)
            ' We set the ID of the message
            '
            lviCurrentItem.SubItems.Add(msgStsCurrentMsg.IdString)
            ' We set the length of the Message
            '
            lviCurrentItem.SubItems.Add(GetLengthFromDLC(newMsg.DLC, (newMsg.MSGTYPE And TPCANMessageType.PCAN_MESSAGE_FD) = 0).ToString())
            ' we set the message count message (this is the First, so count is 1)            
            '
            lviCurrentItem.SubItems.Add(msgStsCurrentMsg.Count.ToString())
            ' Add time stamp information if needed
            '
            lviCurrentItem.SubItems.Add(msgStsCurrentMsg.TimeString)
            ' We set the data of the message. 	
            '
            lviCurrentItem.SubItems.Add(msgStsCurrentMsg.DataString)
        End SyncLock
    End Sub

    ''' <summary>
    ''' Processes a received message, in order to show it in the Message-ListView
    ''' </summary>
    ''' <param name="theMsg">The received PCAN-Basic message</param>
    ''' <param name="itsTimeStamp">The Timestamp of the received message</param>
    Private Sub ProcessMessage(ByVal theMsg As TPCANMsgFD, ByVal itsTimeStamp As TPCANTimestampFD)
        ' We search if a message (Same ID and Type) is 
        ' already received or if this is a new message
        '
        SyncLock m_LastMsgsList.SyncRoot
            For Each msg As MessageStatus In m_LastMsgsList
                If (msg.CANMsg.ID = theMsg.ID) And (msg.CANMsg.MSGTYPE = theMsg.MSGTYPE) Then
                    ' Messages of this kind are already received; we do an update
                    '
                    msg.Update(theMsg, itsTimeStamp)
                    Exit Sub
                End If
            Next

            ' Message not found. It will created
            '
            InsertMsgEntry(theMsg, itsTimeStamp)
        End SyncLock
    End Sub

    ''' <summary>
    ''' Processes a received message, in order to show it in the Message-ListView
    ''' </summary>
    ''' <param name="theMsg">The received PCAN-Basic message</param>
    ''' <param name="itsTimeStamp">The Timestamp of the received message</param>
    Private Sub ProcessMessage(ByVal theMsg As TPCANMsg, ByVal itsTimeStamp As TPCANTimestamp)
        Dim newMsg As TPCANMsgFD
        Dim newTimestamp As TPCANTimestampFD

        newMsg = New TPCANMsgFD()
        newMsg.DATA = CType(Array.CreateInstance(GetType(Byte), 64), Byte())
        newMsg.ID = theMsg.ID
        newMsg.DLC = theMsg.LEN
        For i As Integer = 0 To If(theMsg.LEN > 8, 7, theMsg.LEN - 1)
            newMsg.DATA(i) = theMsg.DATA(i)
        Next
        newMsg.MSGTYPE = theMsg.MSGTYPE

        newTimestamp = Convert.ToUInt64(itsTimeStamp.micros + 1000 * itsTimeStamp.millis + &H100000000 * 1000 * itsTimeStamp.millis_overflow)
        ProcessMessage(newMsg, newTimestamp)
    End Sub

    ''' <summary>
    ''' Thread-Function used for reading PCAN-Basic messages
    ''' </summary>
    Private Sub CANReadThreadFunc()
        Dim iBuffer As UInt32
        Dim stsResult As TPCANStatus

        iBuffer = Convert.ToUInt32(m_ReceiveEvent.SafeWaitHandle.DangerousGetHandle().ToInt32())
        ' Sets the handle of the Receive-Event.
        '
        stsResult = PCANBasic.SetValue(m_PcanHandle, TPCANParameter.PCAN_RECEIVE_EVENT, iBuffer, CType(System.Runtime.InteropServices.Marshal.SizeOf(iBuffer), UInteger))

        If stsResult <> TPCANStatus.PCAN_ERROR_OK Then
            MessageBox.Show(GetFormatedError(stsResult), "Error!", MessageBoxButtons.OK, MessageBoxIcon.Error)
            Return
        End If

        ' While this mode is selected
        While rdbEvent.Checked
            ' Waiting for Receive-Event
            ' 
            If m_ReceiveEvent.WaitOne(50) Then
                ' Process Receive-Event using .NET Invoke function
                ' in order to interact with Winforms UI (calling the 
                ' function ReadMessages)
                ' 
                Me.Invoke(m_ReadDelegate)
            End If
        End While
    End Sub

    ''' <summary>
    ''' Function for reading messages on FD devices
    ''' </summary>
    ''' <returns>A TPCANStatus error code</returns>
    Private Function ReadMessageFD() As TPCANStatus
        Dim CANMsg As TPCANMsgFD = Nothing
        Dim CANTimeStamp As TPCANTimestampFD
        Dim stsResult As TPCANStatus

        ' We execute the "Read" function of the PCANBasic 
        '
        stsResult = PCANBasic.ReadFD(m_PcanHandle, CANMsg, CANTimeStamp)
        If (stsResult <> TPCANStatus.PCAN_ERROR_QRCVEMPTY) Then
            ' We process the received message
            '
            ProcessMessage(CANMsg, CANTimeStamp)
        End If

        Return stsResult
    End Function

    ''' <summary>
    ''' Function for reading CAN messages on normal CAN devices
    ''' </summary>
    ''' <returns>A TPCANStatus error code</returns>
    Private Function ReadMessage() As TPCANStatus
        Dim CANMsg As TPCANMsg = Nothing
        Dim CANTimeStamp As TPCANTimestamp
        Dim stsResult As TPCANStatus

        ' We execute the "Read" function of the PCANBasic 
        '
        stsResult = PCANBasic.Read(m_PcanHandle, CANMsg, CANTimeStamp)
        If (stsResult <> TPCANStatus.PCAN_ERROR_QRCVEMPTY) Then
            ' We process the received message
            '
            ProcessMessage(CANMsg, CANTimeStamp)
        End If

        Return stsResult
    End Function

    ''' <summary>
    ''' Function for reading PCAN-Basic messages
    ''' </summary>
    Private Sub ReadMessages()
        Dim stsResult As TPCANStatus

        ' We read at least one time the queue looking for messages.
        ' If a message is found, we look again trying to find more.
        ' If the queue is empty or an error occurr, we get out from
        ' the dowhile statement.
        '			
        Do
            ' We execute the "Read" or "ReadFD" function of the PCANBasic
            '
            stsResult = If(m_IsFD, ReadMessageFD(), ReadMessage())
            If (stsResult = TPCANStatus.PCAN_ERROR_ILLOPERATION) Then
                Exit Do
            End If
        Loop While btnRelease.Enabled AndAlso (Not Convert.ToBoolean(stsResult And TPCANStatus.PCAN_ERROR_QRCVEMPTY))
    End Sub
#End Region

#End Region
End Class
