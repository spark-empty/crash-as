<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form remplace la méthode Dispose pour nettoyer la liste des composants.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Requise par le Concepteur Windows Form
    Private components As System.ComponentModel.IContainer

    'REMARQUE : la procédure suivante est requise par le Concepteur Windows Form
    'Elle peut être modifiée à l'aide du Concepteur Windows Form.  
    'Ne la modifiez pas à l'aide de l'éditeur de code.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container
        Me.chbShowPeriod = New System.Windows.Forms.CheckBox
        Me.rdbManual = New System.Windows.Forms.RadioButton
        Me.rdbEvent = New System.Windows.Forms.RadioButton
        Me.lstMessages = New System.Windows.Forms.ListView
        Me.clhType = New System.Windows.Forms.ColumnHeader
        Me.clhID = New System.Windows.Forms.ColumnHeader
        Me.clhLength = New System.Windows.Forms.ColumnHeader
        Me.clhCount = New System.Windows.Forms.ColumnHeader
        Me.clhRcvTime = New System.Windows.Forms.ColumnHeader
        Me.clhData = New System.Windows.Forms.ColumnHeader
        Me.btnMsgClear = New System.Windows.Forms.Button
        Me.groupBox5 = New System.Windows.Forms.GroupBox
        Me.rdbTimer = New System.Windows.Forms.RadioButton
        Me.btnRead = New System.Windows.Forms.Button
        Me.label11 = New System.Windows.Forms.Label
        Me.btnWrite = New System.Windows.Forms.Button
        Me.groupBox6 = New System.Windows.Forms.GroupBox
        Me.Label12 = New System.Windows.Forms.Label
        Me.laLength = New System.Windows.Forms.Label
        Me.chbBRS = New System.Windows.Forms.CheckBox
        Me.chbFD = New System.Windows.Forms.CheckBox
        Me.chbRemote = New System.Windows.Forms.CheckBox
        Me.chbExtended = New System.Windows.Forms.CheckBox
        Me.Label13 = New System.Windows.Forms.Label
        Me.Label14 = New System.Windows.Forms.Label
        Me.txtID = New System.Windows.Forms.TextBox
        Me.nudLength = New System.Windows.Forms.NumericUpDown
        Me.txtData60 = New System.Windows.Forms.TextBox
        Me.txtData62 = New System.Windows.Forms.TextBox
        Me.txtData47 = New System.Windows.Forms.TextBox
        Me.txtData58 = New System.Windows.Forms.TextBox
        Me.txtData57 = New System.Windows.Forms.TextBox
        Me.txtData56 = New System.Windows.Forms.TextBox
        Me.txtData55 = New System.Windows.Forms.TextBox
        Me.txtData54 = New System.Windows.Forms.TextBox
        Me.txtData61 = New System.Windows.Forms.TextBox
        Me.txtData63 = New System.Windows.Forms.TextBox
        Me.txtData48 = New System.Windows.Forms.TextBox
        Me.txtData53 = New System.Windows.Forms.TextBox
        Me.txtData52 = New System.Windows.Forms.TextBox
        Me.txtData51 = New System.Windows.Forms.TextBox
        Me.txtData50 = New System.Windows.Forms.TextBox
        Me.txtData49 = New System.Windows.Forms.TextBox
        Me.txtData59 = New System.Windows.Forms.TextBox
        Me.txtData46 = New System.Windows.Forms.TextBox
        Me.txtData45 = New System.Windows.Forms.TextBox
        Me.txtData44 = New System.Windows.Forms.TextBox
        Me.txtData43 = New System.Windows.Forms.TextBox
        Me.txtData42 = New System.Windows.Forms.TextBox
        Me.txtData41 = New System.Windows.Forms.TextBox
        Me.txtData40 = New System.Windows.Forms.TextBox
        Me.txtData39 = New System.Windows.Forms.TextBox
        Me.txtData38 = New System.Windows.Forms.TextBox
        Me.txtData37 = New System.Windows.Forms.TextBox
        Me.txtData36 = New System.Windows.Forms.TextBox
        Me.txtData35 = New System.Windows.Forms.TextBox
        Me.txtData34 = New System.Windows.Forms.TextBox
        Me.txtData33 = New System.Windows.Forms.TextBox
        Me.txtData32 = New System.Windows.Forms.TextBox
        Me.txtData31 = New System.Windows.Forms.TextBox
        Me.txtData30 = New System.Windows.Forms.TextBox
        Me.txtData29 = New System.Windows.Forms.TextBox
        Me.txtData28 = New System.Windows.Forms.TextBox
        Me.txtData27 = New System.Windows.Forms.TextBox
        Me.txtData26 = New System.Windows.Forms.TextBox
        Me.txtData25 = New System.Windows.Forms.TextBox
        Me.txtData24 = New System.Windows.Forms.TextBox
        Me.txtData23 = New System.Windows.Forms.TextBox
        Me.txtData22 = New System.Windows.Forms.TextBox
        Me.txtData21 = New System.Windows.Forms.TextBox
        Me.txtData20 = New System.Windows.Forms.TextBox
        Me.txtData19 = New System.Windows.Forms.TextBox
        Me.txtData18 = New System.Windows.Forms.TextBox
        Me.txtData17 = New System.Windows.Forms.TextBox
        Me.txtData16 = New System.Windows.Forms.TextBox
        Me.txtData15 = New System.Windows.Forms.TextBox
        Me.txtData14 = New System.Windows.Forms.TextBox
        Me.txtData13 = New System.Windows.Forms.TextBox
        Me.txtData12 = New System.Windows.Forms.TextBox
        Me.txtData11 = New System.Windows.Forms.TextBox
        Me.txtData10 = New System.Windows.Forms.TextBox
        Me.txtData9 = New System.Windows.Forms.TextBox
        Me.txtData8 = New System.Windows.Forms.TextBox
        Me.txtData7 = New System.Windows.Forms.TextBox
        Me.txtData6 = New System.Windows.Forms.TextBox
        Me.txtData5 = New System.Windows.Forms.TextBox
        Me.txtData4 = New System.Windows.Forms.TextBox
        Me.txtData3 = New System.Windows.Forms.TextBox
        Me.txtData2 = New System.Windows.Forms.TextBox
        Me.txtData1 = New System.Windows.Forms.TextBox
        Me.txtData0 = New System.Windows.Forms.TextBox
        Me.groupBox4 = New System.Windows.Forms.GroupBox
        Me.btnReset = New System.Windows.Forms.Button
        Me.btnStatus = New System.Windows.Forms.Button
        Me.btnGetVersions = New System.Windows.Forms.Button
        Me.lbxInfo = New System.Windows.Forms.ListBox
        Me.btnInfoClear = New System.Windows.Forms.Button
        Me.cbbChannel = New System.Windows.Forms.ComboBox
        Me.rdbParamInactive = New System.Windows.Forms.RadioButton
        Me.btnHwRefresh = New System.Windows.Forms.Button
        Me.cbbHwType = New System.Windows.Forms.ComboBox
        Me.cbbInterrupt = New System.Windows.Forms.ComboBox
        Me.btnFilterQuery = New System.Windows.Forms.Button
        Me.laInterrupt = New System.Windows.Forms.Label
        Me.groupBox3 = New System.Windows.Forms.GroupBox
        Me.chbFilterExt = New System.Windows.Forms.CheckBox
        Me.nudIdTo = New System.Windows.Forms.NumericUpDown
        Me.nudIdFrom = New System.Windows.Forms.NumericUpDown
        Me.label8 = New System.Windows.Forms.Label
        Me.label7 = New System.Windows.Forms.Label
        Me.rdbFilterOpen = New System.Windows.Forms.RadioButton
        Me.rdbFilterCustom = New System.Windows.Forms.RadioButton
        Me.rdbFilterClose = New System.Windows.Forms.RadioButton
        Me.btnFilterApply = New System.Windows.Forms.Button
        Me.cbbIO = New System.Windows.Forms.ComboBox
        Me.tmrRead = New System.Windows.Forms.Timer(Me.components)
        Me.laIOPort = New System.Windows.Forms.Label
        Me.laHwType = New System.Windows.Forms.Label
        Me.cbbBaudrates = New System.Windows.Forms.ComboBox
        Me.laBaudrate = New System.Windows.Forms.Label
        Me.label1 = New System.Windows.Forms.Label
        Me.btnInit = New System.Windows.Forms.Button
        Me.btnRelease = New System.Windows.Forms.Button
        Me.btnParameterGet = New System.Windows.Forms.Button
        Me.label10 = New System.Windows.Forms.Label
        Me.nudDeviceIdOrDelay = New System.Windows.Forms.NumericUpDown
        Me.laDeviceOrDelay = New System.Windows.Forms.Label
        Me.cbbParameter = New System.Windows.Forms.ComboBox
        Me.groupBox2 = New System.Windows.Forms.GroupBox
        Me.label6 = New System.Windows.Forms.Label
        Me.rdbParamActive = New System.Windows.Forms.RadioButton
        Me.btnParameterSet = New System.Windows.Forms.Button
        Me.groupBox1 = New System.Windows.Forms.GroupBox
        Me.chbCanFD = New System.Windows.Forms.CheckBox
        Me.txtBitrate = New System.Windows.Forms.TextBox
        Me.laBitrate = New System.Windows.Forms.Label
        Me.tmrDisplay = New System.Windows.Forms.Timer(Me.components)
        Me.groupBox5.SuspendLayout()
        Me.groupBox6.SuspendLayout()
        CType(Me.nudLength, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.groupBox4.SuspendLayout()
        Me.groupBox3.SuspendLayout()
        CType(Me.nudIdTo, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.nudIdFrom, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.nudDeviceIdOrDelay, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.groupBox2.SuspendLayout()
        Me.groupBox1.SuspendLayout()
        Me.SuspendLayout()
        '
        'chbShowPeriod
        '
        Me.chbShowPeriod.AutoSize = True
        Me.chbShowPeriod.Location = New System.Drawing.Point(374, 15)
        Me.chbShowPeriod.Name = "chbShowPeriod"
        Me.chbShowPeriod.Size = New System.Drawing.Size(123, 17)
        Me.chbShowPeriod.TabIndex = 75
        Me.chbShowPeriod.Text = "Timestamp as period"
        Me.chbShowPeriod.UseVisualStyleBackColor = True
        '
        'rdbManual
        '
        Me.rdbManual.AutoSize = True
        Me.rdbManual.Location = New System.Drawing.Point(276, 14)
        Me.rdbManual.Name = "rdbManual"
        Me.rdbManual.Size = New System.Drawing.Size(89, 17)
        Me.rdbManual.TabIndex = 74
        Me.rdbManual.Text = "Manual Read"
        Me.rdbManual.UseVisualStyleBackColor = True
        '
        'rdbEvent
        '
        Me.rdbEvent.AutoSize = True
        Me.rdbEvent.Location = New System.Drawing.Point(131, 14)
        Me.rdbEvent.Name = "rdbEvent"
        Me.rdbEvent.Size = New System.Drawing.Size(139, 17)
        Me.rdbEvent.TabIndex = 73
        Me.rdbEvent.Text = "Reading using an Event"
        Me.rdbEvent.UseVisualStyleBackColor = True
        '
        'lstMessages
        '
        Me.lstMessages.Columns.AddRange(New System.Windows.Forms.ColumnHeader() {Me.clhType, Me.clhID, Me.clhLength, Me.clhCount, Me.clhRcvTime, Me.clhData})
        Me.lstMessages.FullRowSelect = True
        Me.lstMessages.Location = New System.Drawing.Point(8, 37)
        Me.lstMessages.MultiSelect = False
        Me.lstMessages.Name = "lstMessages"
        Me.lstMessages.Size = New System.Drawing.Size(560, 96)
        Me.lstMessages.TabIndex = 28
        Me.lstMessages.UseCompatibleStateImageBehavior = False
        Me.lstMessages.View = System.Windows.Forms.View.Details
        '
        'clhType
        '
        Me.clhType.Text = "Type"
        Me.clhType.Width = 110
        '
        'clhID
        '
        Me.clhID.Text = "ID"
        Me.clhID.Width = 90
        '
        'clhLength
        '
        Me.clhLength.Text = "Length"
        Me.clhLength.Width = 50
        '
        'clhCount
        '
        Me.clhCount.Text = "Count"
        Me.clhCount.Width = 49
        '
        'clhRcvTime
        '
        Me.clhRcvTime.Text = "Rcv Time"
        Me.clhRcvTime.Width = 70
        '
        'clhData
        '
        Me.clhData.Text = "Data"
        Me.clhData.Width = 170
        '
        'btnMsgClear
        '
        Me.btnMsgClear.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.btnMsgClear.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnMsgClear.Location = New System.Drawing.Point(643, 37)
        Me.btnMsgClear.Name = "btnMsgClear"
        Me.btnMsgClear.Size = New System.Drawing.Size(65, 23)
        Me.btnMsgClear.TabIndex = 50
        Me.btnMsgClear.Text = "Clear"
        Me.btnMsgClear.UseVisualStyleBackColor = True
        '
        'groupBox5
        '
        Me.groupBox5.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
                    Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.groupBox5.Controls.Add(Me.chbShowPeriod)
        Me.groupBox5.Controls.Add(Me.rdbManual)
        Me.groupBox5.Controls.Add(Me.rdbEvent)
        Me.groupBox5.Controls.Add(Me.lstMessages)
        Me.groupBox5.Controls.Add(Me.btnMsgClear)
        Me.groupBox5.Controls.Add(Me.rdbTimer)
        Me.groupBox5.Controls.Add(Me.btnRead)
        Me.groupBox5.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.groupBox5.Location = New System.Drawing.Point(5, 204)
        Me.groupBox5.Name = "groupBox5"
        Me.groupBox5.Size = New System.Drawing.Size(714, 140)
        Me.groupBox5.TabIndex = 56
        Me.groupBox5.TabStop = False
        Me.groupBox5.Text = " Messages Reading "
        '
        'rdbTimer
        '
        Me.rdbTimer.AutoSize = True
        Me.rdbTimer.Location = New System.Drawing.Point(8, 14)
        Me.rdbTimer.Name = "rdbTimer"
        Me.rdbTimer.Size = New System.Drawing.Size(117, 17)
        Me.rdbTimer.TabIndex = 72
        Me.rdbTimer.Text = "Read using a Timer"
        Me.rdbTimer.UseVisualStyleBackColor = True
        '
        'btnRead
        '
        Me.btnRead.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.btnRead.Enabled = False
        Me.btnRead.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnRead.Location = New System.Drawing.Point(572, 37)
        Me.btnRead.Name = "btnRead"
        Me.btnRead.Size = New System.Drawing.Size(65, 23)
        Me.btnRead.TabIndex = 49
        Me.btnRead.Text = "Read"
        Me.btnRead.UseVisualStyleBackColor = True
        '
        'label11
        '
        Me.label11.AutoSize = True
        Me.label11.Location = New System.Drawing.Point(7, 16)
        Me.label11.Name = "label11"
        Me.label11.Size = New System.Drawing.Size(61, 13)
        Me.label11.TabIndex = 32
        Me.label11.Text = "Data (Hex):"
        '
        'btnWrite
        '
        Me.btnWrite.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.btnWrite.Cursor = System.Windows.Forms.Cursors.Default
        Me.btnWrite.Enabled = False
        Me.btnWrite.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnWrite.Location = New System.Drawing.Point(639, 86)
        Me.btnWrite.Name = "btnWrite"
        Me.btnWrite.Size = New System.Drawing.Size(65, 23)
        Me.btnWrite.TabIndex = 36
        Me.btnWrite.Text = "Write"
        '
        'groupBox6
        '
        Me.groupBox6.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
                    Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.groupBox6.Controls.Add(Me.Label12)
        Me.groupBox6.Controls.Add(Me.laLength)
        Me.groupBox6.Controls.Add(Me.chbBRS)
        Me.groupBox6.Controls.Add(Me.chbFD)
        Me.groupBox6.Controls.Add(Me.chbRemote)
        Me.groupBox6.Controls.Add(Me.chbExtended)
        Me.groupBox6.Controls.Add(Me.Label13)
        Me.groupBox6.Controls.Add(Me.Label14)
        Me.groupBox6.Controls.Add(Me.txtID)
        Me.groupBox6.Controls.Add(Me.nudLength)
        Me.groupBox6.Controls.Add(Me.txtData60)
        Me.groupBox6.Controls.Add(Me.txtData62)
        Me.groupBox6.Controls.Add(Me.txtData47)
        Me.groupBox6.Controls.Add(Me.txtData58)
        Me.groupBox6.Controls.Add(Me.txtData57)
        Me.groupBox6.Controls.Add(Me.txtData56)
        Me.groupBox6.Controls.Add(Me.txtData55)
        Me.groupBox6.Controls.Add(Me.txtData54)
        Me.groupBox6.Controls.Add(Me.txtData61)
        Me.groupBox6.Controls.Add(Me.txtData63)
        Me.groupBox6.Controls.Add(Me.txtData48)
        Me.groupBox6.Controls.Add(Me.txtData53)
        Me.groupBox6.Controls.Add(Me.txtData52)
        Me.groupBox6.Controls.Add(Me.txtData51)
        Me.groupBox6.Controls.Add(Me.txtData50)
        Me.groupBox6.Controls.Add(Me.txtData49)
        Me.groupBox6.Controls.Add(Me.txtData59)
        Me.groupBox6.Controls.Add(Me.txtData46)
        Me.groupBox6.Controls.Add(Me.txtData45)
        Me.groupBox6.Controls.Add(Me.txtData44)
        Me.groupBox6.Controls.Add(Me.txtData43)
        Me.groupBox6.Controls.Add(Me.txtData42)
        Me.groupBox6.Controls.Add(Me.txtData41)
        Me.groupBox6.Controls.Add(Me.txtData40)
        Me.groupBox6.Controls.Add(Me.txtData39)
        Me.groupBox6.Controls.Add(Me.txtData38)
        Me.groupBox6.Controls.Add(Me.txtData37)
        Me.groupBox6.Controls.Add(Me.txtData36)
        Me.groupBox6.Controls.Add(Me.txtData35)
        Me.groupBox6.Controls.Add(Me.txtData34)
        Me.groupBox6.Controls.Add(Me.txtData33)
        Me.groupBox6.Controls.Add(Me.txtData32)
        Me.groupBox6.Controls.Add(Me.txtData31)
        Me.groupBox6.Controls.Add(Me.txtData30)
        Me.groupBox6.Controls.Add(Me.txtData29)
        Me.groupBox6.Controls.Add(Me.txtData28)
        Me.groupBox6.Controls.Add(Me.txtData27)
        Me.groupBox6.Controls.Add(Me.txtData26)
        Me.groupBox6.Controls.Add(Me.txtData25)
        Me.groupBox6.Controls.Add(Me.txtData24)
        Me.groupBox6.Controls.Add(Me.txtData23)
        Me.groupBox6.Controls.Add(Me.txtData22)
        Me.groupBox6.Controls.Add(Me.txtData21)
        Me.groupBox6.Controls.Add(Me.txtData20)
        Me.groupBox6.Controls.Add(Me.txtData19)
        Me.groupBox6.Controls.Add(Me.txtData18)
        Me.groupBox6.Controls.Add(Me.txtData17)
        Me.groupBox6.Controls.Add(Me.txtData16)
        Me.groupBox6.Controls.Add(Me.txtData15)
        Me.groupBox6.Controls.Add(Me.txtData14)
        Me.groupBox6.Controls.Add(Me.txtData13)
        Me.groupBox6.Controls.Add(Me.txtData12)
        Me.groupBox6.Controls.Add(Me.txtData11)
        Me.groupBox6.Controls.Add(Me.txtData10)
        Me.groupBox6.Controls.Add(Me.txtData9)
        Me.groupBox6.Controls.Add(Me.txtData8)
        Me.groupBox6.Controls.Add(Me.txtData7)
        Me.groupBox6.Controls.Add(Me.txtData6)
        Me.groupBox6.Controls.Add(Me.txtData5)
        Me.groupBox6.Controls.Add(Me.txtData4)
        Me.groupBox6.Controls.Add(Me.txtData3)
        Me.groupBox6.Controls.Add(Me.txtData2)
        Me.groupBox6.Controls.Add(Me.txtData1)
        Me.groupBox6.Controls.Add(Me.txtData0)
        Me.groupBox6.Controls.Add(Me.label11)
        Me.groupBox6.Controls.Add(Me.btnWrite)
        Me.groupBox6.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.groupBox6.Location = New System.Drawing.Point(5, 350)
        Me.groupBox6.Name = "groupBox6"
        Me.groupBox6.Size = New System.Drawing.Size(714, 150)
        Me.groupBox6.TabIndex = 57
        Me.groupBox6.TabStop = False
        Me.groupBox6.Text = "Write Messages"
        '
        'Label12
        '
        Me.Label12.AutoSize = True
        Me.Label12.Location = New System.Drawing.Point(665, 16)
        Me.Label12.Name = "Label12"
        Me.Label12.Size = New System.Drawing.Size(43, 13)
        Me.Label12.TabIndex = 143
        Me.Label12.Text = "Length:"
        '
        'laLength
        '
        Me.laLength.AutoSize = True
        Me.laLength.Location = New System.Drawing.Point(672, 41)
        Me.laLength.Name = "laLength"
        Me.laLength.Size = New System.Drawing.Size(26, 13)
        Me.laLength.TabIndex = 142
        Me.laLength.Text = "8 B."
        '
        'chbBRS
        '
        Me.chbBRS.Cursor = System.Windows.Forms.Cursors.Default
        Me.chbBRS.Enabled = False
        Me.chbBRS.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.chbBRS.Location = New System.Drawing.Point(568, 86)
        Me.chbBRS.Name = "chbBRS"
        Me.chbBRS.Size = New System.Drawing.Size(40, 24)
        Me.chbBRS.TabIndex = 139
        Me.chbBRS.Text = "BRS"
        Me.chbBRS.Visible = False
        '
        'chbFD
        '
        Me.chbFD.Cursor = System.Windows.Forms.Cursors.Default
        Me.chbFD.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.chbFD.Location = New System.Drawing.Point(500, 86)
        Me.chbFD.Name = "chbFD"
        Me.chbFD.Size = New System.Drawing.Size(37, 24)
        Me.chbFD.TabIndex = 138
        Me.chbFD.Text = "FD"
        Me.chbFD.Visible = False
        '
        'chbRemote
        '
        Me.chbRemote.Cursor = System.Windows.Forms.Cursors.Default
        Me.chbRemote.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.chbRemote.Location = New System.Drawing.Point(568, 64)
        Me.chbRemote.Name = "chbRemote"
        Me.chbRemote.Size = New System.Drawing.Size(44, 24)
        Me.chbRemote.TabIndex = 137
        Me.chbRemote.Text = "RTR"
        '
        'chbExtended
        '
        Me.chbExtended.Cursor = System.Windows.Forms.Cursors.Default
        Me.chbExtended.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.chbExtended.Location = New System.Drawing.Point(500, 64)
        Me.chbExtended.Name = "chbExtended"
        Me.chbExtended.Size = New System.Drawing.Size(62, 24)
        Me.chbExtended.TabIndex = 136
        Me.chbExtended.Text = "Extended"
        '
        'Label13
        '
        Me.Label13.AutoSize = True
        Me.Label13.Location = New System.Drawing.Point(615, 16)
        Me.Label13.Name = "Label13"
        Me.Label13.Size = New System.Drawing.Size(31, 13)
        Me.Label13.TabIndex = 141
        Me.Label13.Text = "DLC:"
        '
        'Label14
        '
        Me.Label14.AutoSize = True
        Me.Label14.Location = New System.Drawing.Point(497, 16)
        Me.Label14.Name = "Label14"
        Me.Label14.Size = New System.Drawing.Size(49, 13)
        Me.Label14.TabIndex = 140
        Me.Label14.Text = "ID (Hex):"
        '
        'txtID
        '
        Me.txtID.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtID.Location = New System.Drawing.Point(500, 38)
        Me.txtID.MaxLength = 3
        Me.txtID.Name = "txtID"
        Me.txtID.Size = New System.Drawing.Size(112, 20)
        Me.txtID.TabIndex = 134
        Me.txtID.Text = "0"
        '
        'nudLength
        '
        Me.nudLength.BackColor = System.Drawing.Color.White
        Me.nudLength.Location = New System.Drawing.Point(618, 38)
        Me.nudLength.Maximum = New Decimal(New Integer() {8, 0, 0, 0})
        Me.nudLength.Name = "nudLength"
        Me.nudLength.ReadOnly = True
        Me.nudLength.Size = New System.Drawing.Size(41, 20)
        Me.nudLength.TabIndex = 135
        '
        'txtData60
        '
        Me.txtData60.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData60.Enabled = False
        Me.txtData60.Location = New System.Drawing.Point(370, 116)
        Me.txtData60.MaxLength = 2
        Me.txtData60.Name = "txtData60"
        Me.txtData60.Size = New System.Drawing.Size(24, 20)
        Me.txtData60.TabIndex = 130
        Me.txtData60.Text = "00"
        Me.txtData60.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData62
        '
        Me.txtData62.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData62.Enabled = False
        Me.txtData62.Location = New System.Drawing.Point(430, 116)
        Me.txtData62.MaxLength = 2
        Me.txtData62.Name = "txtData62"
        Me.txtData62.Size = New System.Drawing.Size(24, 20)
        Me.txtData62.TabIndex = 132
        Me.txtData62.Text = "00"
        Me.txtData62.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData47
        '
        Me.txtData47.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData47.Enabled = False
        Me.txtData47.Location = New System.Drawing.Point(460, 90)
        Me.txtData47.MaxLength = 2
        Me.txtData47.Name = "txtData47"
        Me.txtData47.Size = New System.Drawing.Size(24, 20)
        Me.txtData47.TabIndex = 117
        Me.txtData47.Text = "00"
        Me.txtData47.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData58
        '
        Me.txtData58.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData58.Enabled = False
        Me.txtData58.Location = New System.Drawing.Point(310, 116)
        Me.txtData58.MaxLength = 2
        Me.txtData58.Name = "txtData58"
        Me.txtData58.Size = New System.Drawing.Size(24, 20)
        Me.txtData58.TabIndex = 128
        Me.txtData58.Text = "00"
        Me.txtData58.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData57
        '
        Me.txtData57.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData57.Enabled = False
        Me.txtData57.Location = New System.Drawing.Point(280, 116)
        Me.txtData57.MaxLength = 2
        Me.txtData57.Name = "txtData57"
        Me.txtData57.Size = New System.Drawing.Size(24, 20)
        Me.txtData57.TabIndex = 127
        Me.txtData57.Text = "00"
        Me.txtData57.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData56
        '
        Me.txtData56.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData56.Enabled = False
        Me.txtData56.Location = New System.Drawing.Point(250, 116)
        Me.txtData56.MaxLength = 2
        Me.txtData56.Name = "txtData56"
        Me.txtData56.Size = New System.Drawing.Size(24, 20)
        Me.txtData56.TabIndex = 126
        Me.txtData56.Text = "00"
        Me.txtData56.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData55
        '
        Me.txtData55.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData55.Enabled = False
        Me.txtData55.Location = New System.Drawing.Point(220, 116)
        Me.txtData55.MaxLength = 2
        Me.txtData55.Name = "txtData55"
        Me.txtData55.Size = New System.Drawing.Size(24, 20)
        Me.txtData55.TabIndex = 125
        Me.txtData55.Text = "00"
        Me.txtData55.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData54
        '
        Me.txtData54.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData54.Enabled = False
        Me.txtData54.Location = New System.Drawing.Point(190, 116)
        Me.txtData54.MaxLength = 2
        Me.txtData54.Name = "txtData54"
        Me.txtData54.Size = New System.Drawing.Size(24, 20)
        Me.txtData54.TabIndex = 124
        Me.txtData54.Text = "00"
        Me.txtData54.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData61
        '
        Me.txtData61.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData61.Enabled = False
        Me.txtData61.Location = New System.Drawing.Point(400, 116)
        Me.txtData61.MaxLength = 2
        Me.txtData61.Name = "txtData61"
        Me.txtData61.Size = New System.Drawing.Size(24, 20)
        Me.txtData61.TabIndex = 131
        Me.txtData61.Text = "00"
        Me.txtData61.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData63
        '
        Me.txtData63.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData63.Enabled = False
        Me.txtData63.Location = New System.Drawing.Point(460, 116)
        Me.txtData63.MaxLength = 2
        Me.txtData63.Name = "txtData63"
        Me.txtData63.Size = New System.Drawing.Size(24, 20)
        Me.txtData63.TabIndex = 133
        Me.txtData63.Text = "00"
        Me.txtData63.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData48
        '
        Me.txtData48.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData48.Enabled = False
        Me.txtData48.Location = New System.Drawing.Point(10, 116)
        Me.txtData48.MaxLength = 2
        Me.txtData48.Name = "txtData48"
        Me.txtData48.Size = New System.Drawing.Size(24, 20)
        Me.txtData48.TabIndex = 118
        Me.txtData48.Text = "00"
        Me.txtData48.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData53
        '
        Me.txtData53.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData53.Enabled = False
        Me.txtData53.Location = New System.Drawing.Point(160, 116)
        Me.txtData53.MaxLength = 2
        Me.txtData53.Name = "txtData53"
        Me.txtData53.Size = New System.Drawing.Size(24, 20)
        Me.txtData53.TabIndex = 123
        Me.txtData53.Text = "00"
        Me.txtData53.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData52
        '
        Me.txtData52.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData52.Enabled = False
        Me.txtData52.Location = New System.Drawing.Point(130, 116)
        Me.txtData52.MaxLength = 2
        Me.txtData52.Name = "txtData52"
        Me.txtData52.Size = New System.Drawing.Size(24, 20)
        Me.txtData52.TabIndex = 122
        Me.txtData52.Text = "00"
        Me.txtData52.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData51
        '
        Me.txtData51.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData51.Enabled = False
        Me.txtData51.Location = New System.Drawing.Point(100, 116)
        Me.txtData51.MaxLength = 2
        Me.txtData51.Name = "txtData51"
        Me.txtData51.Size = New System.Drawing.Size(24, 20)
        Me.txtData51.TabIndex = 121
        Me.txtData51.Text = "00"
        Me.txtData51.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData50
        '
        Me.txtData50.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData50.Enabled = False
        Me.txtData50.Location = New System.Drawing.Point(70, 116)
        Me.txtData50.MaxLength = 2
        Me.txtData50.Name = "txtData50"
        Me.txtData50.Size = New System.Drawing.Size(24, 20)
        Me.txtData50.TabIndex = 120
        Me.txtData50.Text = "00"
        Me.txtData50.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData49
        '
        Me.txtData49.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData49.Enabled = False
        Me.txtData49.Location = New System.Drawing.Point(40, 116)
        Me.txtData49.MaxLength = 2
        Me.txtData49.Name = "txtData49"
        Me.txtData49.Size = New System.Drawing.Size(24, 20)
        Me.txtData49.TabIndex = 119
        Me.txtData49.Text = "00"
        Me.txtData49.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData59
        '
        Me.txtData59.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData59.Enabled = False
        Me.txtData59.Location = New System.Drawing.Point(340, 116)
        Me.txtData59.MaxLength = 2
        Me.txtData59.Name = "txtData59"
        Me.txtData59.Size = New System.Drawing.Size(24, 20)
        Me.txtData59.TabIndex = 129
        Me.txtData59.Text = "00"
        Me.txtData59.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData46
        '
        Me.txtData46.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData46.Enabled = False
        Me.txtData46.Location = New System.Drawing.Point(430, 90)
        Me.txtData46.MaxLength = 2
        Me.txtData46.Name = "txtData46"
        Me.txtData46.Size = New System.Drawing.Size(24, 20)
        Me.txtData46.TabIndex = 116
        Me.txtData46.Text = "00"
        Me.txtData46.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData45
        '
        Me.txtData45.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData45.Enabled = False
        Me.txtData45.Location = New System.Drawing.Point(400, 90)
        Me.txtData45.MaxLength = 2
        Me.txtData45.Name = "txtData45"
        Me.txtData45.Size = New System.Drawing.Size(24, 20)
        Me.txtData45.TabIndex = 115
        Me.txtData45.Text = "00"
        Me.txtData45.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData44
        '
        Me.txtData44.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData44.Enabled = False
        Me.txtData44.Location = New System.Drawing.Point(370, 90)
        Me.txtData44.MaxLength = 2
        Me.txtData44.Name = "txtData44"
        Me.txtData44.Size = New System.Drawing.Size(24, 20)
        Me.txtData44.TabIndex = 114
        Me.txtData44.Text = "00"
        Me.txtData44.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData43
        '
        Me.txtData43.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData43.Enabled = False
        Me.txtData43.Location = New System.Drawing.Point(340, 90)
        Me.txtData43.MaxLength = 2
        Me.txtData43.Name = "txtData43"
        Me.txtData43.Size = New System.Drawing.Size(24, 20)
        Me.txtData43.TabIndex = 113
        Me.txtData43.Text = "00"
        Me.txtData43.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData42
        '
        Me.txtData42.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData42.Enabled = False
        Me.txtData42.Location = New System.Drawing.Point(310, 90)
        Me.txtData42.MaxLength = 2
        Me.txtData42.Name = "txtData42"
        Me.txtData42.Size = New System.Drawing.Size(24, 20)
        Me.txtData42.TabIndex = 112
        Me.txtData42.Text = "00"
        Me.txtData42.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData41
        '
        Me.txtData41.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData41.Enabled = False
        Me.txtData41.Location = New System.Drawing.Point(280, 90)
        Me.txtData41.MaxLength = 2
        Me.txtData41.Name = "txtData41"
        Me.txtData41.Size = New System.Drawing.Size(24, 20)
        Me.txtData41.TabIndex = 111
        Me.txtData41.Text = "00"
        Me.txtData41.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData40
        '
        Me.txtData40.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData40.Enabled = False
        Me.txtData40.Location = New System.Drawing.Point(250, 90)
        Me.txtData40.MaxLength = 2
        Me.txtData40.Name = "txtData40"
        Me.txtData40.Size = New System.Drawing.Size(24, 20)
        Me.txtData40.TabIndex = 110
        Me.txtData40.Text = "00"
        Me.txtData40.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData39
        '
        Me.txtData39.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData39.Enabled = False
        Me.txtData39.Location = New System.Drawing.Point(220, 90)
        Me.txtData39.MaxLength = 2
        Me.txtData39.Name = "txtData39"
        Me.txtData39.Size = New System.Drawing.Size(24, 20)
        Me.txtData39.TabIndex = 109
        Me.txtData39.Text = "00"
        Me.txtData39.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData38
        '
        Me.txtData38.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData38.Enabled = False
        Me.txtData38.Location = New System.Drawing.Point(190, 90)
        Me.txtData38.MaxLength = 2
        Me.txtData38.Name = "txtData38"
        Me.txtData38.Size = New System.Drawing.Size(24, 20)
        Me.txtData38.TabIndex = 108
        Me.txtData38.Text = "00"
        Me.txtData38.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData37
        '
        Me.txtData37.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData37.Enabled = False
        Me.txtData37.Location = New System.Drawing.Point(160, 90)
        Me.txtData37.MaxLength = 2
        Me.txtData37.Name = "txtData37"
        Me.txtData37.Size = New System.Drawing.Size(24, 20)
        Me.txtData37.TabIndex = 107
        Me.txtData37.Text = "00"
        Me.txtData37.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData36
        '
        Me.txtData36.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData36.Enabled = False
        Me.txtData36.Location = New System.Drawing.Point(130, 90)
        Me.txtData36.MaxLength = 2
        Me.txtData36.Name = "txtData36"
        Me.txtData36.Size = New System.Drawing.Size(24, 20)
        Me.txtData36.TabIndex = 106
        Me.txtData36.Text = "00"
        Me.txtData36.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData35
        '
        Me.txtData35.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData35.Enabled = False
        Me.txtData35.Location = New System.Drawing.Point(100, 90)
        Me.txtData35.MaxLength = 2
        Me.txtData35.Name = "txtData35"
        Me.txtData35.Size = New System.Drawing.Size(24, 20)
        Me.txtData35.TabIndex = 105
        Me.txtData35.Text = "00"
        Me.txtData35.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData34
        '
        Me.txtData34.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData34.Enabled = False
        Me.txtData34.Location = New System.Drawing.Point(70, 90)
        Me.txtData34.MaxLength = 2
        Me.txtData34.Name = "txtData34"
        Me.txtData34.Size = New System.Drawing.Size(24, 20)
        Me.txtData34.TabIndex = 104
        Me.txtData34.Text = "00"
        Me.txtData34.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData33
        '
        Me.txtData33.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData33.Enabled = False
        Me.txtData33.Location = New System.Drawing.Point(40, 90)
        Me.txtData33.MaxLength = 2
        Me.txtData33.Name = "txtData33"
        Me.txtData33.Size = New System.Drawing.Size(24, 20)
        Me.txtData33.TabIndex = 103
        Me.txtData33.Text = "00"
        Me.txtData33.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData32
        '
        Me.txtData32.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData32.Enabled = False
        Me.txtData32.Location = New System.Drawing.Point(10, 90)
        Me.txtData32.MaxLength = 2
        Me.txtData32.Name = "txtData32"
        Me.txtData32.Size = New System.Drawing.Size(24, 20)
        Me.txtData32.TabIndex = 102
        Me.txtData32.Text = "00"
        Me.txtData32.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData31
        '
        Me.txtData31.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData31.Enabled = False
        Me.txtData31.Location = New System.Drawing.Point(460, 64)
        Me.txtData31.MaxLength = 2
        Me.txtData31.Name = "txtData31"
        Me.txtData31.Size = New System.Drawing.Size(24, 20)
        Me.txtData31.TabIndex = 101
        Me.txtData31.Text = "00"
        Me.txtData31.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData30
        '
        Me.txtData30.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData30.Enabled = False
        Me.txtData30.Location = New System.Drawing.Point(430, 64)
        Me.txtData30.MaxLength = 2
        Me.txtData30.Name = "txtData30"
        Me.txtData30.Size = New System.Drawing.Size(24, 20)
        Me.txtData30.TabIndex = 100
        Me.txtData30.Text = "00"
        Me.txtData30.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData29
        '
        Me.txtData29.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData29.Enabled = False
        Me.txtData29.Location = New System.Drawing.Point(400, 64)
        Me.txtData29.MaxLength = 2
        Me.txtData29.Name = "txtData29"
        Me.txtData29.Size = New System.Drawing.Size(24, 20)
        Me.txtData29.TabIndex = 99
        Me.txtData29.Text = "00"
        Me.txtData29.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData28
        '
        Me.txtData28.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData28.Enabled = False
        Me.txtData28.Location = New System.Drawing.Point(370, 64)
        Me.txtData28.MaxLength = 2
        Me.txtData28.Name = "txtData28"
        Me.txtData28.Size = New System.Drawing.Size(24, 20)
        Me.txtData28.TabIndex = 98
        Me.txtData28.Text = "00"
        Me.txtData28.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData27
        '
        Me.txtData27.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData27.Enabled = False
        Me.txtData27.Location = New System.Drawing.Point(340, 64)
        Me.txtData27.MaxLength = 2
        Me.txtData27.Name = "txtData27"
        Me.txtData27.Size = New System.Drawing.Size(24, 20)
        Me.txtData27.TabIndex = 97
        Me.txtData27.Text = "00"
        Me.txtData27.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData26
        '
        Me.txtData26.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData26.Enabled = False
        Me.txtData26.Location = New System.Drawing.Point(310, 64)
        Me.txtData26.MaxLength = 2
        Me.txtData26.Name = "txtData26"
        Me.txtData26.Size = New System.Drawing.Size(24, 20)
        Me.txtData26.TabIndex = 96
        Me.txtData26.Text = "00"
        Me.txtData26.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData25
        '
        Me.txtData25.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData25.Enabled = False
        Me.txtData25.Location = New System.Drawing.Point(280, 64)
        Me.txtData25.MaxLength = 2
        Me.txtData25.Name = "txtData25"
        Me.txtData25.Size = New System.Drawing.Size(24, 20)
        Me.txtData25.TabIndex = 95
        Me.txtData25.Text = "00"
        Me.txtData25.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData24
        '
        Me.txtData24.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData24.Enabled = False
        Me.txtData24.Location = New System.Drawing.Point(250, 64)
        Me.txtData24.MaxLength = 2
        Me.txtData24.Name = "txtData24"
        Me.txtData24.Size = New System.Drawing.Size(24, 20)
        Me.txtData24.TabIndex = 94
        Me.txtData24.Text = "00"
        Me.txtData24.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData23
        '
        Me.txtData23.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData23.Enabled = False
        Me.txtData23.Location = New System.Drawing.Point(220, 64)
        Me.txtData23.MaxLength = 2
        Me.txtData23.Name = "txtData23"
        Me.txtData23.Size = New System.Drawing.Size(24, 20)
        Me.txtData23.TabIndex = 93
        Me.txtData23.Text = "00"
        Me.txtData23.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData22
        '
        Me.txtData22.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData22.Enabled = False
        Me.txtData22.Location = New System.Drawing.Point(190, 64)
        Me.txtData22.MaxLength = 2
        Me.txtData22.Name = "txtData22"
        Me.txtData22.Size = New System.Drawing.Size(24, 20)
        Me.txtData22.TabIndex = 92
        Me.txtData22.Text = "00"
        Me.txtData22.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData21
        '
        Me.txtData21.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData21.Enabled = False
        Me.txtData21.Location = New System.Drawing.Point(160, 64)
        Me.txtData21.MaxLength = 2
        Me.txtData21.Name = "txtData21"
        Me.txtData21.Size = New System.Drawing.Size(24, 20)
        Me.txtData21.TabIndex = 91
        Me.txtData21.Text = "00"
        Me.txtData21.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData20
        '
        Me.txtData20.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData20.Enabled = False
        Me.txtData20.Location = New System.Drawing.Point(130, 64)
        Me.txtData20.MaxLength = 2
        Me.txtData20.Name = "txtData20"
        Me.txtData20.Size = New System.Drawing.Size(24, 20)
        Me.txtData20.TabIndex = 90
        Me.txtData20.Text = "00"
        Me.txtData20.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData19
        '
        Me.txtData19.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData19.Enabled = False
        Me.txtData19.Location = New System.Drawing.Point(100, 64)
        Me.txtData19.MaxLength = 2
        Me.txtData19.Name = "txtData19"
        Me.txtData19.Size = New System.Drawing.Size(24, 20)
        Me.txtData19.TabIndex = 89
        Me.txtData19.Text = "00"
        Me.txtData19.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData18
        '
        Me.txtData18.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData18.Enabled = False
        Me.txtData18.Location = New System.Drawing.Point(71, 64)
        Me.txtData18.MaxLength = 2
        Me.txtData18.Name = "txtData18"
        Me.txtData18.Size = New System.Drawing.Size(24, 20)
        Me.txtData18.TabIndex = 88
        Me.txtData18.Text = "00"
        Me.txtData18.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData17
        '
        Me.txtData17.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData17.Enabled = False
        Me.txtData17.Location = New System.Drawing.Point(41, 64)
        Me.txtData17.MaxLength = 2
        Me.txtData17.Name = "txtData17"
        Me.txtData17.Size = New System.Drawing.Size(24, 20)
        Me.txtData17.TabIndex = 87
        Me.txtData17.Text = "00"
        Me.txtData17.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData16
        '
        Me.txtData16.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData16.Enabled = False
        Me.txtData16.Location = New System.Drawing.Point(10, 64)
        Me.txtData16.MaxLength = 2
        Me.txtData16.Name = "txtData16"
        Me.txtData16.Size = New System.Drawing.Size(24, 20)
        Me.txtData16.TabIndex = 86
        Me.txtData16.Text = "00"
        Me.txtData16.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData15
        '
        Me.txtData15.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData15.Enabled = False
        Me.txtData15.Location = New System.Drawing.Point(460, 38)
        Me.txtData15.MaxLength = 2
        Me.txtData15.Name = "txtData15"
        Me.txtData15.Size = New System.Drawing.Size(24, 20)
        Me.txtData15.TabIndex = 85
        Me.txtData15.Text = "00"
        Me.txtData15.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData14
        '
        Me.txtData14.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData14.Enabled = False
        Me.txtData14.Location = New System.Drawing.Point(430, 38)
        Me.txtData14.MaxLength = 2
        Me.txtData14.Name = "txtData14"
        Me.txtData14.Size = New System.Drawing.Size(24, 20)
        Me.txtData14.TabIndex = 84
        Me.txtData14.Text = "00"
        Me.txtData14.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData13
        '
        Me.txtData13.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData13.Enabled = False
        Me.txtData13.Location = New System.Drawing.Point(400, 38)
        Me.txtData13.MaxLength = 2
        Me.txtData13.Name = "txtData13"
        Me.txtData13.Size = New System.Drawing.Size(24, 20)
        Me.txtData13.TabIndex = 83
        Me.txtData13.Text = "00"
        Me.txtData13.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData12
        '
        Me.txtData12.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData12.Enabled = False
        Me.txtData12.Location = New System.Drawing.Point(370, 38)
        Me.txtData12.MaxLength = 2
        Me.txtData12.Name = "txtData12"
        Me.txtData12.Size = New System.Drawing.Size(24, 20)
        Me.txtData12.TabIndex = 82
        Me.txtData12.Text = "00"
        Me.txtData12.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData11
        '
        Me.txtData11.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData11.Enabled = False
        Me.txtData11.Location = New System.Drawing.Point(340, 38)
        Me.txtData11.MaxLength = 2
        Me.txtData11.Name = "txtData11"
        Me.txtData11.Size = New System.Drawing.Size(24, 20)
        Me.txtData11.TabIndex = 81
        Me.txtData11.Text = "00"
        Me.txtData11.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData10
        '
        Me.txtData10.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData10.Enabled = False
        Me.txtData10.Location = New System.Drawing.Point(310, 38)
        Me.txtData10.MaxLength = 2
        Me.txtData10.Name = "txtData10"
        Me.txtData10.Size = New System.Drawing.Size(24, 20)
        Me.txtData10.TabIndex = 80
        Me.txtData10.Text = "00"
        Me.txtData10.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData9
        '
        Me.txtData9.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData9.Enabled = False
        Me.txtData9.Location = New System.Drawing.Point(280, 38)
        Me.txtData9.MaxLength = 2
        Me.txtData9.Name = "txtData9"
        Me.txtData9.Size = New System.Drawing.Size(24, 20)
        Me.txtData9.TabIndex = 79
        Me.txtData9.Text = "00"
        Me.txtData9.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData8
        '
        Me.txtData8.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData8.Enabled = False
        Me.txtData8.Location = New System.Drawing.Point(250, 38)
        Me.txtData8.MaxLength = 2
        Me.txtData8.Name = "txtData8"
        Me.txtData8.Size = New System.Drawing.Size(24, 20)
        Me.txtData8.TabIndex = 78
        Me.txtData8.Text = "00"
        Me.txtData8.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData7
        '
        Me.txtData7.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData7.Location = New System.Drawing.Point(220, 38)
        Me.txtData7.MaxLength = 2
        Me.txtData7.Name = "txtData7"
        Me.txtData7.Size = New System.Drawing.Size(24, 20)
        Me.txtData7.TabIndex = 77
        Me.txtData7.Text = "00"
        Me.txtData7.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData6
        '
        Me.txtData6.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData6.Location = New System.Drawing.Point(190, 38)
        Me.txtData6.MaxLength = 2
        Me.txtData6.Name = "txtData6"
        Me.txtData6.Size = New System.Drawing.Size(24, 20)
        Me.txtData6.TabIndex = 76
        Me.txtData6.Text = "00"
        Me.txtData6.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData5
        '
        Me.txtData5.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData5.Location = New System.Drawing.Point(160, 38)
        Me.txtData5.MaxLength = 2
        Me.txtData5.Name = "txtData5"
        Me.txtData5.Size = New System.Drawing.Size(24, 20)
        Me.txtData5.TabIndex = 75
        Me.txtData5.Text = "00"
        Me.txtData5.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData4
        '
        Me.txtData4.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData4.Location = New System.Drawing.Point(130, 38)
        Me.txtData4.MaxLength = 2
        Me.txtData4.Name = "txtData4"
        Me.txtData4.Size = New System.Drawing.Size(24, 20)
        Me.txtData4.TabIndex = 74
        Me.txtData4.Text = "00"
        Me.txtData4.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData3
        '
        Me.txtData3.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData3.Location = New System.Drawing.Point(100, 38)
        Me.txtData3.MaxLength = 2
        Me.txtData3.Name = "txtData3"
        Me.txtData3.Size = New System.Drawing.Size(24, 20)
        Me.txtData3.TabIndex = 73
        Me.txtData3.Text = "00"
        Me.txtData3.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData2
        '
        Me.txtData2.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData2.Location = New System.Drawing.Point(71, 38)
        Me.txtData2.MaxLength = 2
        Me.txtData2.Name = "txtData2"
        Me.txtData2.Size = New System.Drawing.Size(24, 20)
        Me.txtData2.TabIndex = 72
        Me.txtData2.Text = "00"
        Me.txtData2.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData1
        '
        Me.txtData1.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData1.Location = New System.Drawing.Point(41, 38)
        Me.txtData1.MaxLength = 2
        Me.txtData1.Name = "txtData1"
        Me.txtData1.Size = New System.Drawing.Size(24, 20)
        Me.txtData1.TabIndex = 71
        Me.txtData1.Text = "00"
        Me.txtData1.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData0
        '
        Me.txtData0.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData0.Location = New System.Drawing.Point(10, 38)
        Me.txtData0.MaxLength = 2
        Me.txtData0.Name = "txtData0"
        Me.txtData0.Size = New System.Drawing.Size(24, 20)
        Me.txtData0.TabIndex = 70
        Me.txtData0.Text = "00"
        Me.txtData0.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'groupBox4
        '
        Me.groupBox4.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
                    Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.groupBox4.Controls.Add(Me.btnReset)
        Me.groupBox4.Controls.Add(Me.btnStatus)
        Me.groupBox4.Controls.Add(Me.btnGetVersions)
        Me.groupBox4.Controls.Add(Me.lbxInfo)
        Me.groupBox4.Controls.Add(Me.btnInfoClear)
        Me.groupBox4.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.groupBox4.Location = New System.Drawing.Point(5, 506)
        Me.groupBox4.Name = "groupBox4"
        Me.groupBox4.Size = New System.Drawing.Size(714, 77)
        Me.groupBox4.TabIndex = 55
        Me.groupBox4.TabStop = False
        Me.groupBox4.Text = "Information"
        '
        'btnReset
        '
        Me.btnReset.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.btnReset.Enabled = False
        Me.btnReset.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnReset.Location = New System.Drawing.Point(641, 44)
        Me.btnReset.Name = "btnReset"
        Me.btnReset.Size = New System.Drawing.Size(65, 23)
        Me.btnReset.TabIndex = 63
        Me.btnReset.Text = "Reset"
        Me.btnReset.UseVisualStyleBackColor = True
        '
        'btnStatus
        '
        Me.btnStatus.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.btnStatus.Enabled = False
        Me.btnStatus.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnStatus.Location = New System.Drawing.Point(570, 44)
        Me.btnStatus.Name = "btnStatus"
        Me.btnStatus.Size = New System.Drawing.Size(65, 23)
        Me.btnStatus.TabIndex = 62
        Me.btnStatus.Text = "Status"
        Me.btnStatus.UseVisualStyleBackColor = True
        '
        'btnGetVersions
        '
        Me.btnGetVersions.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.btnGetVersions.Enabled = False
        Me.btnGetVersions.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnGetVersions.Location = New System.Drawing.Point(570, 15)
        Me.btnGetVersions.Name = "btnGetVersions"
        Me.btnGetVersions.Size = New System.Drawing.Size(65, 23)
        Me.btnGetVersions.TabIndex = 60
        Me.btnGetVersions.Text = "Versions"
        Me.btnGetVersions.UseVisualStyleBackColor = True
        '
        'lbxInfo
        '
        Me.lbxInfo.FormattingEnabled = True
        Me.lbxInfo.Items.AddRange(New Object() {"Select a Hardware and a configuration for it. Then click ""Initialize"" button", "When activated, the Debug-Log file will be found in the same directory as this ap" & _
                        "plication", "When activated, the PCAN-Trace file will be found in the same directory as this a" & _
                        "pplication"})
        Me.lbxInfo.Location = New System.Drawing.Point(8, 15)
        Me.lbxInfo.Name = "lbxInfo"
        Me.lbxInfo.ScrollAlwaysVisible = True
        Me.lbxInfo.Size = New System.Drawing.Size(558, 56)
        Me.lbxInfo.TabIndex = 61
        '
        'btnInfoClear
        '
        Me.btnInfoClear.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.btnInfoClear.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnInfoClear.Location = New System.Drawing.Point(641, 15)
        Me.btnInfoClear.Name = "btnInfoClear"
        Me.btnInfoClear.Size = New System.Drawing.Size(65, 23)
        Me.btnInfoClear.TabIndex = 59
        Me.btnInfoClear.Text = "Clear"
        Me.btnInfoClear.UseVisualStyleBackColor = True
        '
        'cbbChannel
        '
        Me.cbbChannel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cbbChannel.Font = New System.Drawing.Font("Consolas", 8.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cbbChannel.Items.AddRange(New Object() {"None", "DNG-Channel 1", "ISA-Channel 1", "ISA-Channel 2", "ISA-Channel 3", "ISA-Channel 4", "ISA-Channel 5", "ISA-Channel 6", "ISA-Channel 7", "ISA-Channel 8", "PCC-Channel 1", "PCC-Channel 2", "PCI-Channel 1", "PCI-Channel 2", "PCI-Channel 3", "PCI-Channel 4", "PCI-Channel 5", "PCI-Channel 6", "PCI-Channel 7", "PCI-Channel 8", "USB-Channel 1", "USB-Channel 2", "USB-Channel 3", "USB-Channel 4", "USB-Channel 5", "USB-Channel 6", "USB-Channel 7", "USB-Channel 8"})
        Me.cbbChannel.Location = New System.Drawing.Point(8, 31)
        Me.cbbChannel.Name = "cbbChannel"
        Me.cbbChannel.Size = New System.Drawing.Size(125, 21)
        Me.cbbChannel.TabIndex = 32
        '
        'rdbParamInactive
        '
        Me.rdbParamInactive.Location = New System.Drawing.Point(300, 32)
        Me.rdbParamInactive.Name = "rdbParamInactive"
        Me.rdbParamInactive.Size = New System.Drawing.Size(67, 17)
        Me.rdbParamInactive.TabIndex = 0
        Me.rdbParamInactive.Text = "Inactive"
        Me.rdbParamInactive.UseVisualStyleBackColor = True
        '
        'btnHwRefresh
        '
        Me.btnHwRefresh.Cursor = System.Windows.Forms.Cursors.Default
        Me.btnHwRefresh.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnHwRefresh.Location = New System.Drawing.Point(139, 30)
        Me.btnHwRefresh.Name = "btnHwRefresh"
        Me.btnHwRefresh.Size = New System.Drawing.Size(59, 23)
        Me.btnHwRefresh.TabIndex = 45
        Me.btnHwRefresh.Text = "Refresh"
        '
        'cbbHwType
        '
        Me.cbbHwType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cbbHwType.Items.AddRange(New Object() {"ISA-82C200", "ISA-SJA1000", "ISA-PHYTEC", "DNG-82C200", "DNG-82C200 EPP", "DNG-SJA1000", "DNG-SJA1000 EPP"})
        Me.cbbHwType.Location = New System.Drawing.Point(326, 31)
        Me.cbbHwType.Name = "cbbHwType"
        Me.cbbHwType.Size = New System.Drawing.Size(120, 21)
        Me.cbbHwType.TabIndex = 37
        '
        'cbbInterrupt
        '
        Me.cbbInterrupt.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cbbInterrupt.Items.AddRange(New Object() {"3", "4", "5", "7", "9", "10", "11", "12", "15"})
        Me.cbbInterrupt.Location = New System.Drawing.Point(513, 31)
        Me.cbbInterrupt.Name = "cbbInterrupt"
        Me.cbbInterrupt.Size = New System.Drawing.Size(55, 21)
        Me.cbbInterrupt.TabIndex = 39
        '
        'btnFilterQuery
        '
        Me.btnFilterQuery.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.btnFilterQuery.Enabled = False
        Me.btnFilterQuery.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnFilterQuery.Location = New System.Drawing.Point(643, 26)
        Me.btnFilterQuery.Name = "btnFilterQuery"
        Me.btnFilterQuery.Size = New System.Drawing.Size(65, 23)
        Me.btnFilterQuery.TabIndex = 55
        Me.btnFilterQuery.Text = "Query"
        Me.btnFilterQuery.UseVisualStyleBackColor = True
        '
        'laInterrupt
        '
        Me.laInterrupt.Location = New System.Drawing.Point(515, 15)
        Me.laInterrupt.Name = "laInterrupt"
        Me.laInterrupt.Size = New System.Drawing.Size(53, 23)
        Me.laInterrupt.TabIndex = 44
        Me.laInterrupt.Text = "Interrupt:"
        '
        'groupBox3
        '
        Me.groupBox3.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
                    Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.groupBox3.Controls.Add(Me.btnFilterQuery)
        Me.groupBox3.Controls.Add(Me.chbFilterExt)
        Me.groupBox3.Controls.Add(Me.nudIdTo)
        Me.groupBox3.Controls.Add(Me.nudIdFrom)
        Me.groupBox3.Controls.Add(Me.label8)
        Me.groupBox3.Controls.Add(Me.label7)
        Me.groupBox3.Controls.Add(Me.rdbFilterOpen)
        Me.groupBox3.Controls.Add(Me.rdbFilterCustom)
        Me.groupBox3.Controls.Add(Me.rdbFilterClose)
        Me.groupBox3.Controls.Add(Me.btnFilterApply)
        Me.groupBox3.Location = New System.Drawing.Point(5, 76)
        Me.groupBox3.Name = "groupBox3"
        Me.groupBox3.Size = New System.Drawing.Size(714, 58)
        Me.groupBox3.TabIndex = 53
        Me.groupBox3.TabStop = False
        Me.groupBox3.Text = " Message Filtering "
        '
        'chbFilterExt
        '
        Me.chbFilterExt.AutoSize = True
        Me.chbFilterExt.Location = New System.Drawing.Point(10, 33)
        Me.chbFilterExt.Name = "chbFilterExt"
        Me.chbFilterExt.Size = New System.Drawing.Size(103, 17)
        Me.chbFilterExt.TabIndex = 44
        Me.chbFilterExt.Text = "Extended Frame"
        Me.chbFilterExt.UseVisualStyleBackColor = True
        '
        'nudIdTo
        '
        Me.nudIdTo.Hexadecimal = True
        Me.nudIdTo.Location = New System.Drawing.Point(438, 29)
        Me.nudIdTo.Maximum = New Decimal(New Integer() {2047, 0, 0, 0})
        Me.nudIdTo.Name = "nudIdTo"
        Me.nudIdTo.Size = New System.Drawing.Size(69, 20)
        Me.nudIdTo.TabIndex = 6
        Me.nudIdTo.Value = New Decimal(New Integer() {2047, 0, 0, 0})
        '
        'nudIdFrom
        '
        Me.nudIdFrom.Hexadecimal = True
        Me.nudIdFrom.Location = New System.Drawing.Point(363, 29)
        Me.nudIdFrom.Maximum = New Decimal(New Integer() {536870911, 0, 0, 0})
        Me.nudIdFrom.Name = "nudIdFrom"
        Me.nudIdFrom.Size = New System.Drawing.Size(69, 20)
        Me.nudIdFrom.TabIndex = 5
        '
        'label8
        '
        Me.label8.Location = New System.Drawing.Point(436, 10)
        Me.label8.Name = "label8"
        Me.label8.Size = New System.Drawing.Size(28, 23)
        Me.label8.TabIndex = 43
        Me.label8.Text = "To:"
        '
        'label7
        '
        Me.label7.Location = New System.Drawing.Point(361, 12)
        Me.label7.Name = "label7"
        Me.label7.Size = New System.Drawing.Size(38, 23)
        Me.label7.TabIndex = 42
        Me.label7.Text = "From:"
        '
        'rdbFilterOpen
        '
        Me.rdbFilterOpen.Location = New System.Drawing.Point(120, 32)
        Me.rdbFilterOpen.Name = "rdbFilterOpen"
        Me.rdbFilterOpen.Size = New System.Drawing.Size(53, 17)
        Me.rdbFilterOpen.TabIndex = 2
        Me.rdbFilterOpen.Text = "Open"
        Me.rdbFilterOpen.UseVisualStyleBackColor = True
        '
        'rdbFilterCustom
        '
        Me.rdbFilterCustom.Location = New System.Drawing.Point(238, 32)
        Me.rdbFilterCustom.Name = "rdbFilterCustom"
        Me.rdbFilterCustom.Size = New System.Drawing.Size(104, 17)
        Me.rdbFilterCustom.TabIndex = 1
        Me.rdbFilterCustom.Text = "Custom (expand)"
        Me.rdbFilterCustom.UseVisualStyleBackColor = True
        '
        'rdbFilterClose
        '
        Me.rdbFilterClose.Location = New System.Drawing.Point(177, 32)
        Me.rdbFilterClose.Name = "rdbFilterClose"
        Me.rdbFilterClose.Size = New System.Drawing.Size(58, 17)
        Me.rdbFilterClose.TabIndex = 0
        Me.rdbFilterClose.Text = "Close"
        Me.rdbFilterClose.UseVisualStyleBackColor = True
        '
        'btnFilterApply
        '
        Me.btnFilterApply.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.btnFilterApply.Enabled = False
        Me.btnFilterApply.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnFilterApply.Location = New System.Drawing.Point(572, 26)
        Me.btnFilterApply.Name = "btnFilterApply"
        Me.btnFilterApply.Size = New System.Drawing.Size(65, 23)
        Me.btnFilterApply.TabIndex = 44
        Me.btnFilterApply.Text = "Apply"
        Me.btnFilterApply.UseVisualStyleBackColor = True
        '
        'cbbIO
        '
        Me.cbbIO.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cbbIO.Items.AddRange(New Object() {"0100", "0120", "0140", "0200", "0220", "0240", "0260", "0278", "0280", "02A0", "02C0", "02E0", "02E8", "02F8", "0300", "0320", "0340", "0360", "0378", "0380", "03BC", "03E0", "03E8", "03F8"})
        Me.cbbIO.Location = New System.Drawing.Point(452, 31)
        Me.cbbIO.Name = "cbbIO"
        Me.cbbIO.Size = New System.Drawing.Size(55, 21)
        Me.cbbIO.TabIndex = 38
        '
        'tmrRead
        '
        Me.tmrRead.Interval = 50
        '
        'laIOPort
        '
        Me.laIOPort.Location = New System.Drawing.Point(452, 15)
        Me.laIOPort.Name = "laIOPort"
        Me.laIOPort.Size = New System.Drawing.Size(55, 23)
        Me.laIOPort.TabIndex = 43
        Me.laIOPort.Text = "I/O Port:"
        '
        'laHwType
        '
        Me.laHwType.Location = New System.Drawing.Point(327, 15)
        Me.laHwType.Name = "laHwType"
        Me.laHwType.Size = New System.Drawing.Size(90, 23)
        Me.laHwType.TabIndex = 42
        Me.laHwType.Text = "Hardware Type:"
        '
        'cbbBaudrates
        '
        Me.cbbBaudrates.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cbbBaudrates.Items.AddRange(New Object() {"1 MBit/sec", "800 kBit/sec", "500 kBit/sec", "250 kBit/sec", "125 kKBit/sec", "100 kBit/sec", "95,238 kBit/sec", "83,333 kBit/sec", "50 kBit/sec", "47,619 kBit/sec", "33,333 kBit/sec", "20 kBit/sec", "10 kBit/sec", "5 kBit/sec"})
        Me.cbbBaudrates.Location = New System.Drawing.Point(204, 31)
        Me.cbbBaudrates.Name = "cbbBaudrates"
        Me.cbbBaudrates.Size = New System.Drawing.Size(116, 21)
        Me.cbbBaudrates.TabIndex = 36
        '
        'laBaudrate
        '
        Me.laBaudrate.Location = New System.Drawing.Point(204, 15)
        Me.laBaudrate.Name = "laBaudrate"
        Me.laBaudrate.Size = New System.Drawing.Size(56, 23)
        Me.laBaudrate.TabIndex = 41
        Me.laBaudrate.Text = "Baudrate:"
        '
        'label1
        '
        Me.label1.Location = New System.Drawing.Point(7, 16)
        Me.label1.Name = "label1"
        Me.label1.Size = New System.Drawing.Size(56, 23)
        Me.label1.TabIndex = 40
        Me.label1.Text = "Hardware:"
        '
        'btnInit
        '
        Me.btnInit.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.btnInit.Cursor = System.Windows.Forms.Cursors.Default
        Me.btnInit.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnInit.Location = New System.Drawing.Point(643, 11)
        Me.btnInit.Name = "btnInit"
        Me.btnInit.Size = New System.Drawing.Size(65, 23)
        Me.btnInit.TabIndex = 34
        Me.btnInit.Text = "Initialize"
        '
        'btnRelease
        '
        Me.btnRelease.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.btnRelease.Cursor = System.Windows.Forms.Cursors.Default
        Me.btnRelease.Enabled = False
        Me.btnRelease.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnRelease.Location = New System.Drawing.Point(643, 36)
        Me.btnRelease.Name = "btnRelease"
        Me.btnRelease.Size = New System.Drawing.Size(65, 23)
        Me.btnRelease.TabIndex = 35
        Me.btnRelease.Text = "Release"
        '
        'btnParameterGet
        '
        Me.btnParameterGet.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.btnParameterGet.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnParameterGet.Location = New System.Drawing.Point(643, 26)
        Me.btnParameterGet.Name = "btnParameterGet"
        Me.btnParameterGet.Size = New System.Drawing.Size(65, 23)
        Me.btnParameterGet.TabIndex = 54
        Me.btnParameterGet.Text = "Get"
        Me.btnParameterGet.UseVisualStyleBackColor = True
        '
        'label10
        '
        Me.label10.Location = New System.Drawing.Point(241, 11)
        Me.label10.Name = "label10"
        Me.label10.Size = New System.Drawing.Size(59, 23)
        Me.label10.TabIndex = 46
        Me.label10.Text = "Activation:"
        '
        'nudDeviceIdOrDelay
        '
        Me.nudDeviceIdOrDelay.Enabled = False
        Me.nudDeviceIdOrDelay.Location = New System.Drawing.Point(408, 29)
        Me.nudDeviceIdOrDelay.Maximum = New Decimal(New Integer() {-1, 0, 0, 0})
        Me.nudDeviceIdOrDelay.Name = "nudDeviceIdOrDelay"
        Me.nudDeviceIdOrDelay.Size = New System.Drawing.Size(99, 20)
        Me.nudDeviceIdOrDelay.TabIndex = 6
        '
        'laDeviceOrDelay
        '
        Me.laDeviceOrDelay.Location = New System.Drawing.Point(405, 12)
        Me.laDeviceOrDelay.Name = "laDeviceOrDelay"
        Me.laDeviceOrDelay.Size = New System.Drawing.Size(59, 23)
        Me.laDeviceOrDelay.TabIndex = 45
        Me.laDeviceOrDelay.Text = "Device ID:"
        '
        'cbbParameter
        '
        Me.cbbParameter.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cbbParameter.FormattingEnabled = True
        Me.cbbParameter.Items.AddRange(New Object() {"USB's Device Number", "USB/PC-Card's 5V Power", "Auto-reset on BUS-OFF", "CAN Listen-Only", "Debug's Log", "Receive Status", "CAN Controller Number", "Trace File", "Channel Identification (USB)", "Channel Capabilities", "Bit rate Adaptation", "Get Bit rate Information", "Get Bit rate FD Information", "Get CAN Nominal Speed Bit/s", "Get CAN Data Speed Bit/s", "Get IP Address", "Get LAN Service Status", "Reception of Status Frames", "Reception of RTR Frames", "Reception of Error Frames", "Interframe Transmit Delay"})
        Me.cbbParameter.Location = New System.Drawing.Point(10, 31)
        Me.cbbParameter.Name = "cbbParameter"
        Me.cbbParameter.Size = New System.Drawing.Size(217, 21)
        Me.cbbParameter.TabIndex = 44
        '
        'groupBox2
        '
        Me.groupBox2.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
                    Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.groupBox2.Controls.Add(Me.btnParameterGet)
        Me.groupBox2.Controls.Add(Me.label10)
        Me.groupBox2.Controls.Add(Me.nudDeviceIdOrDelay)
        Me.groupBox2.Controls.Add(Me.laDeviceOrDelay)
        Me.groupBox2.Controls.Add(Me.cbbParameter)
        Me.groupBox2.Controls.Add(Me.label6)
        Me.groupBox2.Controls.Add(Me.rdbParamActive)
        Me.groupBox2.Controls.Add(Me.rdbParamInactive)
        Me.groupBox2.Controls.Add(Me.btnParameterSet)
        Me.groupBox2.Location = New System.Drawing.Point(5, 140)
        Me.groupBox2.Name = "groupBox2"
        Me.groupBox2.Size = New System.Drawing.Size(714, 58)
        Me.groupBox2.TabIndex = 54
        Me.groupBox2.TabStop = False
        Me.groupBox2.Text = " Configuration Parameters "
        '
        'label6
        '
        Me.label6.Location = New System.Drawing.Point(7, 14)
        Me.label6.Name = "label6"
        Me.label6.Size = New System.Drawing.Size(64, 23)
        Me.label6.TabIndex = 43
        Me.label6.Text = "Parameter:"
        '
        'rdbParamActive
        '
        Me.rdbParamActive.Location = New System.Drawing.Point(238, 32)
        Me.rdbParamActive.Name = "rdbParamActive"
        Me.rdbParamActive.Size = New System.Drawing.Size(56, 17)
        Me.rdbParamActive.TabIndex = 2
        Me.rdbParamActive.Text = "Active"
        Me.rdbParamActive.UseVisualStyleBackColor = True
        '
        'btnParameterSet
        '
        Me.btnParameterSet.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.btnParameterSet.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnParameterSet.Location = New System.Drawing.Point(572, 26)
        Me.btnParameterSet.Name = "btnParameterSet"
        Me.btnParameterSet.Size = New System.Drawing.Size(65, 23)
        Me.btnParameterSet.TabIndex = 46
        Me.btnParameterSet.Text = "Set"
        Me.btnParameterSet.UseVisualStyleBackColor = True
        '
        'groupBox1
        '
        Me.groupBox1.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
                    Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.groupBox1.Controls.Add(Me.chbCanFD)
        Me.groupBox1.Controls.Add(Me.btnHwRefresh)
        Me.groupBox1.Controls.Add(Me.cbbChannel)
        Me.groupBox1.Controls.Add(Me.cbbHwType)
        Me.groupBox1.Controls.Add(Me.cbbInterrupt)
        Me.groupBox1.Controls.Add(Me.laInterrupt)
        Me.groupBox1.Controls.Add(Me.cbbIO)
        Me.groupBox1.Controls.Add(Me.laIOPort)
        Me.groupBox1.Controls.Add(Me.laHwType)
        Me.groupBox1.Controls.Add(Me.cbbBaudrates)
        Me.groupBox1.Controls.Add(Me.laBaudrate)
        Me.groupBox1.Controls.Add(Me.label1)
        Me.groupBox1.Controls.Add(Me.btnInit)
        Me.groupBox1.Controls.Add(Me.btnRelease)
        Me.groupBox1.Controls.Add(Me.txtBitrate)
        Me.groupBox1.Controls.Add(Me.laBitrate)
        Me.groupBox1.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.groupBox1.Location = New System.Drawing.Point(5, 5)
        Me.groupBox1.Name = "groupBox1"
        Me.groupBox1.Size = New System.Drawing.Size(714, 65)
        Me.groupBox1.TabIndex = 52
        Me.groupBox1.TabStop = False
        Me.groupBox1.Text = " Connection "
        '
        'chbCanFD
        '
        Me.chbCanFD.AutoSize = True
        Me.chbCanFD.Location = New System.Drawing.Point(577, 34)
        Me.chbCanFD.Name = "chbCanFD"
        Me.chbCanFD.Size = New System.Drawing.Size(65, 17)
        Me.chbCanFD.TabIndex = 60
        Me.chbCanFD.Text = "CAN-FD"
        Me.chbCanFD.UseVisualStyleBackColor = True
        '
        'txtBitrate
        '
        Me.txtBitrate.Location = New System.Drawing.Point(207, 24)
        Me.txtBitrate.Multiline = True
        Me.txtBitrate.Name = "txtBitrate"
        Me.txtBitrate.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
        Me.txtBitrate.Size = New System.Drawing.Size(364, 34)
        Me.txtBitrate.TabIndex = 60
        Me.txtBitrate.Visible = False
        '
        'laBitrate
        '
        Me.laBitrate.AutoSize = True
        Me.laBitrate.Location = New System.Drawing.Point(204, 7)
        Me.laBitrate.Name = "laBitrate"
        Me.laBitrate.Size = New System.Drawing.Size(43, 13)
        Me.laBitrate.TabIndex = 59
        Me.laBitrate.Text = "Bit rate:"
        Me.laBitrate.Visible = False
        '
        'tmrDisplay
        '
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(724, 595)
        Me.Controls.Add(Me.groupBox5)
        Me.Controls.Add(Me.groupBox6)
        Me.Controls.Add(Me.groupBox4)
        Me.Controls.Add(Me.groupBox3)
        Me.Controls.Add(Me.groupBox2)
        Me.Controls.Add(Me.groupBox1)
        Me.MaximizeBox = False
        Me.Name = "Form1"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "PCAN-Basic Sample"
        Me.groupBox5.ResumeLayout(False)
        Me.groupBox5.PerformLayout()
        Me.groupBox6.ResumeLayout(False)
        Me.groupBox6.PerformLayout()
        CType(Me.nudLength, System.ComponentModel.ISupportInitialize).EndInit()
        Me.groupBox4.ResumeLayout(False)
        Me.groupBox3.ResumeLayout(False)
        Me.groupBox3.PerformLayout()
        CType(Me.nudIdTo, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.nudIdFrom, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.nudDeviceIdOrDelay, System.ComponentModel.ISupportInitialize).EndInit()
        Me.groupBox2.ResumeLayout(False)
        Me.groupBox1.ResumeLayout(False)
        Me.groupBox1.PerformLayout()
        Me.ResumeLayout(False)

    End Sub
    Private WithEvents chbShowPeriod As System.Windows.Forms.CheckBox
    Private WithEvents rdbManual As System.Windows.Forms.RadioButton
    Private WithEvents rdbEvent As System.Windows.Forms.RadioButton
    Private WithEvents lstMessages As System.Windows.Forms.ListView
    Private WithEvents clhType As System.Windows.Forms.ColumnHeader
    Private WithEvents clhID As System.Windows.Forms.ColumnHeader
    Private WithEvents clhLength As System.Windows.Forms.ColumnHeader
    Private WithEvents clhData As System.Windows.Forms.ColumnHeader
    Private WithEvents clhCount As System.Windows.Forms.ColumnHeader
    Private WithEvents clhRcvTime As System.Windows.Forms.ColumnHeader
    Private WithEvents btnMsgClear As System.Windows.Forms.Button
    Private WithEvents groupBox5 As System.Windows.Forms.GroupBox
    Private WithEvents rdbTimer As System.Windows.Forms.RadioButton
    Private WithEvents btnRead As System.Windows.Forms.Button
    Private WithEvents label11 As System.Windows.Forms.Label
    Private WithEvents btnWrite As System.Windows.Forms.Button
    Private WithEvents groupBox6 As System.Windows.Forms.GroupBox
    Private WithEvents groupBox4 As System.Windows.Forms.GroupBox
    Private WithEvents cbbChannel As System.Windows.Forms.ComboBox
    Private WithEvents rdbParamInactive As System.Windows.Forms.RadioButton
    Private WithEvents btnHwRefresh As System.Windows.Forms.Button
    Private WithEvents cbbHwType As System.Windows.Forms.ComboBox
    Private WithEvents cbbInterrupt As System.Windows.Forms.ComboBox
    Private WithEvents btnFilterQuery As System.Windows.Forms.Button
    Private WithEvents laInterrupt As System.Windows.Forms.Label
    Private WithEvents groupBox3 As System.Windows.Forms.GroupBox
    Private WithEvents chbFilterExt As System.Windows.Forms.CheckBox
    Private WithEvents nudIdTo As System.Windows.Forms.NumericUpDown
    Private WithEvents nudIdFrom As System.Windows.Forms.NumericUpDown
    Private WithEvents label8 As System.Windows.Forms.Label
    Private WithEvents label7 As System.Windows.Forms.Label
    Private WithEvents rdbFilterOpen As System.Windows.Forms.RadioButton
    Private WithEvents rdbFilterCustom As System.Windows.Forms.RadioButton
    Private WithEvents rdbFilterClose As System.Windows.Forms.RadioButton
    Private WithEvents btnFilterApply As System.Windows.Forms.Button
    Private WithEvents cbbIO As System.Windows.Forms.ComboBox
    Private WithEvents laIOPort As System.Windows.Forms.Label
    Private WithEvents laHwType As System.Windows.Forms.Label
    Private WithEvents cbbBaudrates As System.Windows.Forms.ComboBox
    Private WithEvents laBaudrate As System.Windows.Forms.Label
    Private WithEvents label1 As System.Windows.Forms.Label
    Private WithEvents btnInit As System.Windows.Forms.Button
    Private WithEvents btnRelease As System.Windows.Forms.Button
    Private WithEvents btnParameterGet As System.Windows.Forms.Button
    Private WithEvents label10 As System.Windows.Forms.Label
    Private WithEvents nudDeviceIdOrDelay As System.Windows.Forms.NumericUpDown
    Private WithEvents laDeviceOrDelay As System.Windows.Forms.Label
    Private WithEvents cbbParameter As System.Windows.Forms.ComboBox
    Private WithEvents groupBox2 As System.Windows.Forms.GroupBox
    Private WithEvents label6 As System.Windows.Forms.Label
    Private WithEvents rdbParamActive As System.Windows.Forms.RadioButton
    Private WithEvents btnParameterSet As System.Windows.Forms.Button
    Private WithEvents groupBox1 As System.Windows.Forms.GroupBox
    Private WithEvents tmrRead As System.Windows.Forms.Timer
    Private WithEvents tmrDisplay As System.Windows.Forms.Timer
    Private WithEvents txtBitrate As System.Windows.Forms.TextBox
    Private WithEvents laBitrate As System.Windows.Forms.Label
    Private WithEvents txtData60 As System.Windows.Forms.TextBox
    Private WithEvents txtData62 As System.Windows.Forms.TextBox
    Private WithEvents txtData47 As System.Windows.Forms.TextBox
    Private WithEvents txtData58 As System.Windows.Forms.TextBox
    Private WithEvents txtData57 As System.Windows.Forms.TextBox
    Private WithEvents txtData56 As System.Windows.Forms.TextBox
    Private WithEvents txtData55 As System.Windows.Forms.TextBox
    Private WithEvents txtData54 As System.Windows.Forms.TextBox
    Private WithEvents txtData61 As System.Windows.Forms.TextBox
    Private WithEvents txtData63 As System.Windows.Forms.TextBox
    Private WithEvents txtData48 As System.Windows.Forms.TextBox
    Private WithEvents txtData53 As System.Windows.Forms.TextBox
    Private WithEvents txtData52 As System.Windows.Forms.TextBox
    Private WithEvents txtData51 As System.Windows.Forms.TextBox
    Private WithEvents txtData50 As System.Windows.Forms.TextBox
    Private WithEvents txtData49 As System.Windows.Forms.TextBox
    Private WithEvents txtData59 As System.Windows.Forms.TextBox
    Private WithEvents txtData46 As System.Windows.Forms.TextBox
    Private WithEvents txtData45 As System.Windows.Forms.TextBox
    Private WithEvents txtData44 As System.Windows.Forms.TextBox
    Private WithEvents txtData43 As System.Windows.Forms.TextBox
    Private WithEvents txtData42 As System.Windows.Forms.TextBox
    Private WithEvents txtData41 As System.Windows.Forms.TextBox
    Private WithEvents txtData40 As System.Windows.Forms.TextBox
    Private WithEvents txtData39 As System.Windows.Forms.TextBox
    Private WithEvents txtData38 As System.Windows.Forms.TextBox
    Private WithEvents txtData37 As System.Windows.Forms.TextBox
    Private WithEvents txtData36 As System.Windows.Forms.TextBox
    Private WithEvents txtData35 As System.Windows.Forms.TextBox
    Private WithEvents txtData34 As System.Windows.Forms.TextBox
    Private WithEvents txtData33 As System.Windows.Forms.TextBox
    Private WithEvents txtData32 As System.Windows.Forms.TextBox
    Private WithEvents txtData31 As System.Windows.Forms.TextBox
    Private WithEvents txtData30 As System.Windows.Forms.TextBox
    Private WithEvents txtData29 As System.Windows.Forms.TextBox
    Private WithEvents txtData28 As System.Windows.Forms.TextBox
    Private WithEvents txtData27 As System.Windows.Forms.TextBox
    Private WithEvents txtData26 As System.Windows.Forms.TextBox
    Private WithEvents txtData25 As System.Windows.Forms.TextBox
    Private WithEvents txtData24 As System.Windows.Forms.TextBox
    Private WithEvents txtData23 As System.Windows.Forms.TextBox
    Private WithEvents txtData22 As System.Windows.Forms.TextBox
    Private WithEvents txtData21 As System.Windows.Forms.TextBox
    Private WithEvents txtData20 As System.Windows.Forms.TextBox
    Private WithEvents txtData19 As System.Windows.Forms.TextBox
    Private WithEvents txtData18 As System.Windows.Forms.TextBox
    Private WithEvents txtData17 As System.Windows.Forms.TextBox
    Private WithEvents txtData16 As System.Windows.Forms.TextBox
    Private WithEvents txtData15 As System.Windows.Forms.TextBox
    Private WithEvents txtData14 As System.Windows.Forms.TextBox
    Private WithEvents txtData13 As System.Windows.Forms.TextBox
    Private WithEvents txtData12 As System.Windows.Forms.TextBox
    Private WithEvents txtData11 As System.Windows.Forms.TextBox
    Private WithEvents txtData10 As System.Windows.Forms.TextBox
    Private WithEvents txtData9 As System.Windows.Forms.TextBox
    Private WithEvents txtData8 As System.Windows.Forms.TextBox
    Private WithEvents txtData7 As System.Windows.Forms.TextBox
    Private WithEvents txtData6 As System.Windows.Forms.TextBox
    Private WithEvents txtData5 As System.Windows.Forms.TextBox
    Private WithEvents txtData4 As System.Windows.Forms.TextBox
    Private WithEvents txtData3 As System.Windows.Forms.TextBox
    Private WithEvents txtData2 As System.Windows.Forms.TextBox
    Private WithEvents txtData1 As System.Windows.Forms.TextBox
    Private WithEvents txtData0 As System.Windows.Forms.TextBox
    Private WithEvents Label12 As System.Windows.Forms.Label
    Private WithEvents laLength As System.Windows.Forms.Label
    Private WithEvents chbBRS As System.Windows.Forms.CheckBox
    Private WithEvents chbFD As System.Windows.Forms.CheckBox
    Private WithEvents chbRemote As System.Windows.Forms.CheckBox
    Private WithEvents chbExtended As System.Windows.Forms.CheckBox
    Private WithEvents Label13 As System.Windows.Forms.Label
    Private WithEvents Label14 As System.Windows.Forms.Label
    Private WithEvents txtID As System.Windows.Forms.TextBox
    Private WithEvents nudLength As System.Windows.Forms.NumericUpDown
    Private WithEvents btnReset As System.Windows.Forms.Button
    Private WithEvents btnStatus As System.Windows.Forms.Button
    Private WithEvents btnGetVersions As System.Windows.Forms.Button
    Private WithEvents lbxInfo As System.Windows.Forms.ListBox
    Private WithEvents btnInfoClear As System.Windows.Forms.Button
    Private WithEvents chbCanFD As System.Windows.Forms.CheckBox

End Class
