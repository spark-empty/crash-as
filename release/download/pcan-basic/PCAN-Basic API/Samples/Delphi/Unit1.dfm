object Form1: TForm1
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = 'PCAN-Basic Example'
  ClientHeight = 575
  ClientWidth = 760
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 0
    Width = 744
    Height = 65
    Caption = ' Connection '
    TabOrder = 0
    object Label1: TLabel
      Left = 11
      Top = 16
      Width = 51
      Height = 13
      Caption = 'Hardware:'
    end
    object laBaudrate: TLabel
      Left = 221
      Top = 16
      Width = 48
      Height = 13
      Caption = 'Baudrate:'
    end
    object laHwType: TLabel
      Left = 346
      Top = 16
      Width = 78
      Height = 13
      Caption = 'Hardware Type:'
    end
    object laIOPort: TLabel
      Left = 475
      Top = 16
      Width = 43
      Height = 13
      Caption = 'I/O Port:'
    end
    object laInterrupt: TLabel
      Left = 539
      Top = 16
      Width = 48
      Height = 13
      Caption = 'Interrupt:'
    end
    object laBitrate: TLabel
      Left = 221
      Top = 9
      Width = 39
      Height = 13
      Caption = 'Bit rate:'
      Visible = False
    end
    object txtBitrate: TMemo
      Left = 221
      Top = 25
      Width = 374
      Height = 35
      Lines.Strings = (
        'txtBitrate')
      ScrollBars = ssVertical
      TabOrder = 8
      Visible = False
    end
    object cbbChannel: TComboBox
      Left = 11
      Top = 35
      Width = 143
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 0
      OnChange = cbbChannelChange
      Items.Strings = (
        'None'
        'DNG-Channel 1'
        'ISA-Channel 1'
        'ISA-Channel 2'
        'ISA-Channel 3'
        'ISA-Channel 4'
        'ISA-Channel 5'
        'ISA-Channel 6'
        'ISA-Channel 7'
        'ISA-Channel 8'
        'PCC-Channel 1'
        'PCC-Channel 2'
        'PCI-Channel 1'
        'PCI-Channel 2'
        'PCI-Channel 3'
        'PCI-Channel 4'
        'PCI-Channel 5'
        'PCI-Channel 6'
        'PCI-Channel 7'
        'PCI-Channel 8'
        'USB-Channel 1'
        'USB-Channel 2'
        'USB-Channel 3'
        'USB-Channel 4'
        'USB-Channel 5'
        'USB-Channel 6'
        'USB-Channel 7'
        'USB-Channel 8')
    end
    object btnHwRefresh: TButton
      Left = 160
      Top = 33
      Width = 55
      Height = 25
      Caption = 'Refresh'
      TabOrder = 1
      OnClick = btnHwRefreshClick
    end
    object cbbBaudrates: TComboBox
      Left = 221
      Top = 35
      Width = 116
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 2
      OnChange = cbbBaudratesChange
      Items.Strings = (
        '1 MBit/sec'
        '800 kBit/sec'
        '500 kBit/sec'
        '250 kBit/sec'
        '125 kBit/sec'
        '100 kBit/sec'
        '95,238 kBit/s'
        '83,333 kBit/sec'
        '50 kBit/sec'
        '47,619 kBit/se'
        '33,333 kBit/se'
        '20 kBit/sec'
        '10 kBit/sec'
        '5 kBit/sec')
    end
    object cbbHwType: TComboBox
      Left = 346
      Top = 35
      Width = 120
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 3
      OnChange = cbbHwTypeChange
      Items.Strings = (
        'ISA-82C200'
        'ISA-SJA1000'
        'ISA-PHYTEC'
        'DNG-82C200'
        'DNG-82C200 EPP'
        'DNG-SJA1000'
        'DNG-SJA1000 EPP')
    end
    object cbbIO: TComboBox
      Left = 475
      Top = 35
      Width = 55
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 4
      Items.Strings = (
        '0100'
        '0120'
        '0140'
        '0200'
        '0220'
        '0240'
        '0260'
        '0278'
        '0280'
        '02A0'
        '02C0'
        '02E0'
        '02E8'
        '02F8'
        '0300'
        '0320'
        '0340'
        '0360'
        '0378'
        '0380'
        '03BC'
        '03E0'
        '03E8'
        '03F8')
    end
    object cbbInterrupt: TComboBox
      Left = 539
      Top = 35
      Width = 55
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 5
      Items.Strings = (
        '3'
        '4'
        '5'
        '7'
        '9'
        '10'
        '11'
        '12'
        '15')
    end
    object btnInit: TButton
      Left = 672
      Top = 11
      Width = 65
      Height = 25
      Caption = 'Initialize'
      TabOrder = 6
      OnClick = btnInitClick
    end
    object btnRelease: TButton
      Left = 672
      Top = 37
      Width = 65
      Height = 25
      Caption = 'Release'
      Enabled = False
      TabOrder = 7
      OnClick = btnReleaseClick
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 71
    Width = 744
    Height = 58
    Caption = ' Message Filtering '
    TabOrder = 1
    object Label6: TLabel
      Left = 367
      Top = 11
      Width = 58
      Height = 13
      Caption = 'From (Hex):'
    end
    object Label7: TLabel
      Left = 443
      Top = 11
      Width = 46
      Height = 13
      Caption = 'To (Hex):'
    end
    object chbFilterExt: TCheckBox
      Left = 11
      Top = 32
      Width = 97
      Height = 17
      Caption = 'Extended Frame'
      TabOrder = 0
      OnClick = chbFilterExtClick
    end
    object rdbFilterOpen: TRadioButton
      Left = 122
      Top = 32
      Width = 49
      Height = 17
      Caption = 'Open'
      Checked = True
      TabOrder = 1
      TabStop = True
    end
    object rdbFilterClose: TRadioButton
      Left = 177
      Top = 32
      Width = 57
      Height = 17
      Caption = 'Close'
      TabOrder = 2
    end
    object rdbFilterCustom: TRadioButton
      Left = 240
      Top = 32
      Width = 107
      Height = 17
      Caption = 'Custom (expand)'
      TabOrder = 3
    end
    object txtIdFrom: TEdit
      Left = 368
      Top = 30
      Width = 69
      Height = 21
      MaxLength = 3
      TabOrder = 4
      Text = '0'
      OnExit = txtIdFromExit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtIdTo: TEdit
      Left = 443
      Top = 30
      Width = 69
      Height = 21
      MaxLength = 3
      TabOrder = 5
      Text = '0'
      OnExit = txtIdFromExit
      OnKeyPress = txtIdFromKeyPress
    end
    object btnFilterApply: TButton
      Left = 601
      Top = 25
      Width = 65
      Height = 25
      Caption = 'Apply'
      Enabled = False
      TabOrder = 6
      OnClick = btnFilterApplyClick
    end
    object btnFilterQuery: TButton
      Left = 672
      Top = 25
      Width = 65
      Height = 25
      Caption = 'Query'
      Enabled = False
      TabOrder = 7
      OnClick = btnFilterQueryClick
    end
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 135
    Width = 744
    Height = 58
    Caption = ' Configuration Parameters '
    TabOrder = 2
    object Label8: TLabel
      Left = 11
      Top = 13
      Width = 54
      Height = 13
      Caption = 'Parameter:'
    end
    object Label9: TLabel
      Left = 240
      Top = 13
      Width = 52
      Height = 13
      Caption = 'Activation:'
    end
    object laDeviceOrDelay: TLabel
      Left = 409
      Top = 11
      Width = 50
      Height = 13
      Caption = 'Device ID:'
    end
    object btnParameterSet: TButton
      Left = 601
      Top = 25
      Width = 65
      Height = 25
      Caption = 'Set'
      TabOrder = 0
      OnClick = btnParameterSetClick
    end
    object btnParameterGet: TButton
      Left = 672
      Top = 25
      Width = 65
      Height = 25
      Caption = 'Get'
      TabOrder = 1
      OnClick = btnParameterGetClick
    end
    object cbbParameter: TComboBox
      Left = 11
      Top = 29
      Width = 217
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 2
      OnChange = cbbParameterChange
      Items.Strings = (
        'USB'#39's Device Number'
        'USB/PC-Card'#39's 5V Power'
        'Auto-reset on BUS-OFF'
        'CAN Listen-Only'
        'Debug'#39's Log'
        'Receive Status'
        'CAN Controller Number'
        'Trace File'
        'Channel Identification (USB)'
        'Channel Capabilities'
        'Bit rate Adaptation'
        'Get Bit rate Information'
        'Get Bit rate FD Information'
        'Get CAN Nominal Speed in Bit/s'
        'Get CAN Data Speed in Bit/s'
        'Get IP Address'
        'Get LAN Service Status'
        'Reception of Status Frames'
        'Reception of RTR Frames'
        'Reception of Error Frames'
        'Interframe Transmit Delay')
    end
    object rdbParamActive: TRadioButton
      Left = 234
      Top = 32
      Width = 49
      Height = 17
      Caption = 'Active'
      Checked = True
      TabOrder = 3
      TabStop = True
    end
    object rdbParamInactive: TRadioButton
      Left = 298
      Top = 32
      Width = 71
      Height = 17
      Caption = 'Inactive'
      TabOrder = 4
    end
    object txtDeviceIdOrDelay: TEdit
      Left = 408
      Top = 30
      Width = 104
      Height = 21
      MaxLength = 10
      TabOrder = 5
      Text = '0'
      OnExit = txtDeviceIdOrDelayExit
      OnKeyPress = txtDeviceIdOrDelayKeyPress
    end
  end
  object GroupBox4: TGroupBox
    Left = 8
    Top = 199
    Width = 744
    Height = 140
    Caption = ' Message Reading '
    TabOrder = 3
    object rdbTimer: TRadioButton
      Left = 11
      Top = 16
      Width = 133
      Height = 17
      Caption = 'Reading using a Timer'
      Checked = True
      TabOrder = 0
      TabStop = True
      OnClick = rdbTimerClick
    end
    object rdbEvent: TRadioButton
      Left = 150
      Top = 16
      Width = 133
      Height = 17
      Caption = 'Reading using an Event'
      TabOrder = 1
      OnClick = rdbTimerClick
    end
    object rdbManual: TRadioButton
      Left = 289
      Top = 16
      Width = 88
      Height = 17
      Caption = 'Manual Read'
      TabOrder = 2
      OnClick = rdbTimerClick
    end
    object chbShowPeriod: TCheckBox
      Left = 383
      Top = 16
      Width = 127
      Height = 17
      Caption = 'Timestamp as period'
      Checked = True
      State = cbChecked
      TabOrder = 3
      OnClick = chbShowPeriodClick
    end
    object btnRead: TButton
      Left = 601
      Top = 37
      Width = 65
      Height = 25
      Caption = 'Read'
      Enabled = False
      TabOrder = 4
      OnClick = btnReadClick
    end
    object btnMsgClear: TButton
      Left = 672
      Top = 37
      Width = 65
      Height = 25
      Caption = 'Clear'
      TabOrder = 5
      OnClick = btnMsgClearClick
    end
    object lstMessages: TListView
      Left = 11
      Top = 37
      Width = 584
      Height = 96
      Columns = <
        item
          Caption = 'Type'
          Width = 110
        end
        item
          Caption = 'ID'
          Width = 90
        end
        item
          Caption = 'Length'
        end
        item
          Caption = 'Count'
        end
        item
          Caption = 'Rcv Time'
          Width = 70
        end
        item
          Caption = 'Data'
          Width = 190
        end>
      RowSelect = True
      TabOrder = 6
      ViewStyle = vsReport
      OnDblClick = btnMsgClearClick
    end
  end
  object GroupBox6: TGroupBox
    Left = 8
    Top = 488
    Width = 744
    Height = 87
    Caption = ' Message Reading '
    TabOrder = 4
    object lbxInfo: TListBox
      Left = 11
      Top = 19
      Width = 584
      Height = 56
      ItemHeight = 13
      Items.Strings = (
        
          'Select a Hardware and a configuration for it. Then click "Initia' +
          'lize" button'
        
          'When activated, the Debug-Log file will be found in the same dir' +
          'ectory as this application'
        
          'When activated, the PCAN-Trace file will be found in the same di' +
          'rectory as this application')
      TabOrder = 0
      OnDblClick = btnInfoClearClick
    end
    object btnGetVersions: TButton
      Left = 601
      Top = 19
      Width = 65
      Height = 25
      Caption = 'Versions'
      Enabled = False
      TabOrder = 1
      OnClick = btnGetVersionsClick
    end
    object btnInfoClear: TButton
      Left = 672
      Top = 19
      Width = 65
      Height = 25
      Caption = 'Clear'
      TabOrder = 2
      OnClick = btnInfoClearClick
    end
    object btnReset: TButton
      Left = 672
      Top = 50
      Width = 65
      Height = 25
      Caption = 'Reset'
      Enabled = False
      TabOrder = 3
      OnClick = btnResetClick
    end
    object btnStatus: TButton
      Left = 602
      Top = 50
      Width = 65
      Height = 25
      Caption = 'Status'
      Enabled = False
      TabOrder = 4
      OnClick = btnStatusClick
    end
  end
  object chbCanFD: TCheckBox
    Left = 610
    Top = 37
    Width = 63
    Height = 17
    Caption = 'CAN-FD'
    TabOrder = 5
    OnClick = chbCanFDClick
  end
  object GroupBox5: TGroupBox
    Left = 8
    Top = 342
    Width = 744
    Height = 144
    Caption = ' Message Writing '
    TabOrder = 6
    object Label11: TLabel
      Left = 11
      Top = 13
      Width = 45
      Height = 13
      Caption = 'ID (Hex):'
    end
    object Label12: TLabel
      Left = 631
      Top = 13
      Width = 23
      Height = 13
      Caption = 'DLC:'
    end
    object Label13: TLabel
      Left = 696
      Top = 13
      Width = 37
      Height = 13
      Caption = 'Length:'
    end
    object Label14: TLabel
      Left = 507
      Top = 13
      Width = 45
      Height = 13
      Caption = 'ID (Hex):'
    end
    object laLength: TLabel
      Left = 700
      Top = 35
      Width = 19
      Height = 13
      Caption = '8 B.'
    end
    object txtID: TEdit
      Left = 507
      Top = 32
      Width = 118
      Height = 21
      MaxLength = 3
      TabOrder = 0
      Text = '0'
      OnExit = txtIDExit
      OnKeyPress = txtIdFromKeyPress
    end
    object chbExtended: TCheckBox
      Left = 507
      Top = 67
      Width = 64
      Height = 17
      Caption = 'Extended'
      TabOrder = 3
      OnClick = chbExtendedClick
    end
    object txtLength: TEdit
      Left = 631
      Top = 32
      Width = 34
      Height = 21
      ReadOnly = True
      TabOrder = 1
      Text = '8'
    end
    object nudLength: TUpDown
      Left = 665
      Top = 32
      Width = 16
      Height = 21
      Associate = txtLength
      Max = 8
      Position = 8
      TabOrder = 2
      Thousands = False
      OnClick = nudLengthClick
    end
    object chbRemote: TCheckBox
      Left = 585
      Top = 67
      Width = 40
      Height = 17
      Caption = 'RTR'
      TabOrder = 4
      OnClick = chbRemoteClick
    end
    object txtData0: TEdit
      Left = 11
      Top = 32
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 2
      TabOrder = 7
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData1: TEdit
      Left = 41
      Top = 32
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 2
      TabOrder = 8
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData2: TEdit
      Left = 71
      Top = 32
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 2
      TabOrder = 9
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData3: TEdit
      Left = 101
      Top = 32
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 2
      TabOrder = 10
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData4: TEdit
      Left = 131
      Top = 32
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 2
      TabOrder = 11
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData5: TEdit
      Left = 161
      Top = 32
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 2
      TabOrder = 12
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData6: TEdit
      Left = 191
      Top = 32
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 2
      TabOrder = 13
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData7: TEdit
      Left = 221
      Top = 32
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 2
      TabOrder = 14
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object btnWrite: TButton
      Left = 668
      Top = 84
      Width = 65
      Height = 25
      Caption = 'Write'
      Enabled = False
      TabOrder = 71
      OnClick = btnWriteClick
    end
    object txtData8: TEdit
      Left = 251
      Top = 32
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 15
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData9: TEdit
      Left = 281
      Top = 32
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 16
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData10: TEdit
      Left = 311
      Top = 32
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 17
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData12: TEdit
      Left = 371
      Top = 32
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 19
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData11: TEdit
      Left = 341
      Top = 32
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 18
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData13: TEdit
      Left = 401
      Top = 32
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 20
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData14: TEdit
      Left = 431
      Top = 32
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 21
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData15: TEdit
      Left = 461
      Top = 32
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 22
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData24: TEdit
      Left = 251
      Top = 59
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 31
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData25: TEdit
      Left = 281
      Top = 59
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 32
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData26: TEdit
      Left = 311
      Top = 59
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 33
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData28: TEdit
      Left = 371
      Top = 59
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 35
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData27: TEdit
      Left = 341
      Top = 59
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 34
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData29: TEdit
      Left = 401
      Top = 59
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 36
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData30: TEdit
      Left = 431
      Top = 59
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 37
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData31: TEdit
      Left = 461
      Top = 59
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 38
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData23: TEdit
      Left = 221
      Top = 59
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 30
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData22: TEdit
      Left = 191
      Top = 59
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 29
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData21: TEdit
      Left = 161
      Top = 59
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 28
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData20: TEdit
      Left = 131
      Top = 59
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 27
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData19: TEdit
      Left = 101
      Top = 59
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 26
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData18: TEdit
      Left = 71
      Top = 59
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 25
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData17: TEdit
      Left = 41
      Top = 59
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 24
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData16: TEdit
      Left = 11
      Top = 59
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 23
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData40: TEdit
      Left = 251
      Top = 86
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 47
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData41: TEdit
      Left = 281
      Top = 86
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 48
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData42: TEdit
      Left = 311
      Top = 86
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 49
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData44: TEdit
      Left = 371
      Top = 86
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 51
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData43: TEdit
      Left = 341
      Top = 86
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 50
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData45: TEdit
      Left = 401
      Top = 86
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 52
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData46: TEdit
      Left = 431
      Top = 86
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 53
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData47: TEdit
      Left = 461
      Top = 86
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 54
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData39: TEdit
      Left = 221
      Top = 86
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 46
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData38: TEdit
      Left = 191
      Top = 86
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 45
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData37: TEdit
      Left = 161
      Top = 86
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 44
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData36: TEdit
      Left = 131
      Top = 86
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 43
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData35: TEdit
      Left = 101
      Top = 86
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 42
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData34: TEdit
      Left = 71
      Top = 86
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 41
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData33: TEdit
      Left = 41
      Top = 86
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 40
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData32: TEdit
      Left = 11
      Top = 86
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 39
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData56: TEdit
      Left = 251
      Top = 113
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 63
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData57: TEdit
      Left = 281
      Top = 113
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 64
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData58: TEdit
      Left = 311
      Top = 113
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 65
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData60: TEdit
      Left = 371
      Top = 113
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 67
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData59: TEdit
      Left = 341
      Top = 113
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 66
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData61: TEdit
      Left = 401
      Top = 113
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 68
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData62: TEdit
      Left = 431
      Top = 113
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 69
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData63: TEdit
      Left = 461
      Top = 113
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 70
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData55: TEdit
      Left = 221
      Top = 113
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 62
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData54: TEdit
      Left = 191
      Top = 113
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 61
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData53: TEdit
      Left = 161
      Top = 113
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 60
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData52: TEdit
      Left = 131
      Top = 113
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 59
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData51: TEdit
      Left = 101
      Top = 113
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 58
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData50: TEdit
      Left = 71
      Top = 113
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 57
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData49: TEdit
      Left = 41
      Top = 113
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 56
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object txtData48: TEdit
      Left = 11
      Top = 113
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 2
      TabOrder = 55
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIdFromKeyPress
    end
    object chbFD: TCheckBox
      Left = 507
      Top = 90
      Width = 64
      Height = 17
      Caption = 'FD'
      TabOrder = 5
      Visible = False
      OnClick = chbFDClick
    end
    object chbBRS: TCheckBox
      Left = 585
      Top = 90
      Width = 64
      Height = 17
      Caption = 'BRS'
      TabOrder = 6
      Visible = False
      OnClick = chbExtendedClick
    end
  end
  object tmrRead: TTimer
    Enabled = False
    Interval = 50
    OnTimer = tmrReadTimer
    Left = 712
    Top = 272
  end
  object tmrDisplay: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tmrDisplayTimer
    Left = 680
    Top = 272
  end
end
