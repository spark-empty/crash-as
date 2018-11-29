[!NOCODE!][!//
[!//====================================================================================================
[!//    @file    Spi_PBcfg.c
[!//    @version 2.0.0
[!//
[!//    @brief   AUTOSAR Spi - Post-Build(PB) configuration file code template.
[!//    @details Code template for Post-Build(PB) configuration file generation.
[!//
[!//    Project AUTOSAR 3.0 MCAL
[!//    Patform PA
[!//    Peripheral DSPI
[!//    Dependencies 
[!//
[!//    ARVersion 3.0.0
[!//    ARRevision ASR_REL_3_0_REV_0003
[!//    ARConfVariant
[!//    SWVersion 2.0.0
[!//    BuildVersion XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223
[!//
[!//    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
[!//    All Rights Reserved.
[!//
[!//[!//====================================================================================================

[!LOOP "SpiDriver/*"!]
    [!VAR "Current_ConfigSet"="@name"!]
    [!LOOP "SpiJob/*"!]
        [!LOOP "ChannelAssignment/*"!]
            [!IF "contains(.,$Current_ConfigSet)"!]
            [!ELSE!]
                [!ERROR!]
                            WRONG Reference is selected for ChannelAssignment in [!"../../@name"!]. Channels configured in [!"$Current_ConfigSet"!] should be referenced.
                [!ENDERROR!]
            [!ENDIF!]
        [!ENDLOOP!]

        [!IF "contains(DeviceAssignment,$Current_ConfigSet)"!]
        [!ELSE!]
            [!ERROR!]
                        WRONG Reference is selected for DeviceAssignment in [!"@name"!]. Devices configured in [!"$Current_ConfigSet"!] should be referenced.
            [!ENDERROR!]
        [!ENDIF!]
    [!ENDLOOP!]

    [!LOOP "SpiSequence/*"!]
        [!LOOP "JobAssignment/*"!]
            [!IF "contains(.,$Current_ConfigSet)"!]
            [!ELSE!]
                [!ERROR!]
                            WRONG Reference is selected for JobAssignment in [!"../../@name"!]. Jobs configured in [!"$Current_ConfigSet"!] should be referenced.
                [!ENDERROR!]
            [!ENDIF!]
        [!ENDLOOP!]
    [!ENDLOOP!]
[!ENDLOOP!]

[!MACRO "DetermineOptimalTimeSettings"!]
  [!VAR "OptimalAbsoluteTimeError" = "1000000"!]
  [!VAR "OptimalRelativeTimeError" = "0"!]
  [!VAR "OptimalTime" = "0"!]
  [!VAR "OptimalPrescaler" = "0"!]
  [!VAR "OptimalScaler" = "0"!]
  [!VAR "DesiredBaudrate" = "SpiBaudrate"!]
  [!// if $DesiredTime=0, initialized values are OK; no further calculations needed
  [!IF "$DesiredTime > 0.0"!]
    [!IF "node:exists(TSBModeEnable) and TSBModeEnable = 'true'"!]
            [!VAR "tmpTDT" = "($DesiredTime - 1.0)"!]
            [!VAR "tmpDT" = "bit:and($tmpTDT,15)"!]
            [!VAR "tmpPDT" = "((bit:shr((bit:and($tmpTDT,48)),4)))"!]
            [!VAR "OptimalPrescaler" = "($tmpPDT +1)+($tmpPDT)"!]
            [!VAR "OptimalScaler" = "(bit:shl(2,$tmpDT))"!]
            [!VAR "realTime" = "($DesiredTime * (1.0 div $DesiredBaudrate))"!]
        [!ELSE!]
    [!FOR "Prescaler_Count" = "0" TO "3"!]
      [!VAR "Prescaler" = "$Prescaler_Count*2 + 1"!]
      [!VAR "Scaler" = "2"!]
      [!FOR "Scaler_Count" = "0" TO "15"!]
      [!VAR "CalculatedTime" = "$Prescaler * $Scaler div $BusClock"!]
        [!VAR "RelativeTimeError" = "($CalculatedTime div $DesiredTime) - 1 "!]
        [!VAR "AbsoluteTimeError" = "$RelativeTimeError"!]
        [!IF "$AbsoluteTimeError < 0"!][!VAR "AbsoluteTimeError" = "$AbsoluteTimeError * (-1)"!][!ENDIF!]
        [!IF "$AbsoluteTimeError < $OptimalAbsoluteTimeError"!]
          [!VAR "OptimalAbsoluteTimeError" = "$AbsoluteTimeError"!]
          [!VAR "OptimalRelativeTimeError" = "$RelativeTimeError"!]
          [!VAR "OptimalTime" = "$CalculatedTime"!]
          [!VAR "OptimalPrescaler" = "$Prescaler"!]
          [!VAR "OptimalScaler" = "$Scaler"!]
        [!ENDIF!]
        [!VAR "Scaler" = "$Scaler*2"!]
      [!ENDFOR!]
    [!ENDFOR!]
      [!ENDIF!]
  [!ENDIF!][!//"$DesiredTime > 0.0"
[!ENDMACRO!]

[!MACRO "DetermineOptimalBaudrateSettings"!]
  [!VAR "OptimalAbsoluteBaudrateError" = "1000000"!]
  [!VAR "OptimalRelativeBaudrateError" = "0"!]
  [!VAR "OptimalBaudrate" = "0"!]
  [!VAR "OptimalDouble" = "0"!]
  [!VAR "OptimalPrescaler" = "0"!]
  [!VAR "OptimalScaler" = "0"!]
  [!FOR "Double" = "0" TO "1"!]
    [!FOR "Prescaler_Count" = "0" TO "3"!]
      [!VAR "Prescaler" = "$Prescaler_Count*2 + 1"!]
      [!IF "$Prescaler = 1"!][!VAR "Prescaler" = "2"!][!ENDIF!]
      [!VAR "Scaler" = "2"!]
      [!FOR "Scaler_Count" = "0" TO "15"!]
        [!VAR "CalculatedBaudrate" = "1000000 * $BusClock * (1+ $Double) div ($Prescaler * $Scaler)"!]
        [!// DesiredBaudrate is always positive
        [!VAR "RelativeBaudrateError" = "($CalculatedBaudrate div $DesiredBaudrate) - 1 "!]
        [!VAR "AbsoluteBaudrateError" = "$RelativeBaudrateError"!]
        [!IF "$AbsoluteBaudrateError < 0"!][!VAR "AbsoluteBaudrateError" = "$AbsoluteBaudrateError * (-1)"!][!ENDIF!]
        [!IF "$AbsoluteBaudrateError < $OptimalAbsoluteBaudrateError"!]
          [!VAR "OptimalAbsoluteBaudrateError" = "$AbsoluteBaudrateError"!]
          [!VAR "OptimalRelativeBaudrateError" = "$RelativeBaudrateError"!]
          [!VAR "OptimalBaudrate" = "$CalculatedBaudrate"!]
          [!VAR "OptimalDouble" = "$Double"!]
          [!VAR "OptimalPrescaler" = "$Prescaler"!]
          [!VAR "OptimalScaler" = "$Scaler"!]
        [!ENDIF!]
        [!IF "$Scaler = 4"!]
          [!VAR "Scaler" = "6"!]
        [!ELSEIF "$Scaler = 6"!]
          [!VAR "Scaler" = "8"!]
        [!ELSE!]
          [!VAR "Scaler" = "$Scaler*2"!]
        [!ENDIF!]
      [!ENDFOR!]
    [!ENDFOR!]
  [!ENDFOR!]
[!ENDMACRO!]

[!MACRO "GenerateExternalDeviceInfo"!]
[!NOCODE!][!//
  [!//
  [!VAR "BusClock" = "$BusClockNormal"!][!//
  [!VAR "DesiredTime" = "SpiTimeCs2Clk"!]
  [!CALL "DetermineOptimalTimeSettings"!]
  [!VAR "OptimalPCSCLK" = "$OptimalPrescaler"!]
  [!VAR "OptimalSCSCLK" = "$OptimalScaler"!]
  [!VAR "OptimalTimeCs2Clk" = "$OptimalTime"!]
  [!VAR "OptimalTimeCs2ClkError" = "$OptimalRelativeTimeError"!]
  [!//
  [!VAR "DesiredTime" = "SpiTimeClk2Cs"!]
  [!CALL "DetermineOptimalTimeSettings"!]
  [!VAR "OptimalPASC" = "$OptimalPrescaler"!]
  [!VAR "OptimalSASC" = "$OptimalScaler"!]
  [!VAR "OptimalTimeClk2Cs" = "$OptimalTime"!]
  [!VAR "OptimalTimeClk2CsError" = "$OptimalRelativeTimeError"!]
  [!//
  [!VAR "DesiredTime" = "SpiTimeCs2Cs"!]
  [!VAR "DesiredBaudrate" = "SpiBaudrate"!]
  [!CALL "DetermineOptimalTimeSettings"!]
  [!VAR "OptimalPDT" = "$OptimalPrescaler"!]
  [!VAR "OptimalSDT" = "$OptimalScaler"!]
  [!VAR "OptimalTimeCs2Cs" = "$OptimalTime"!]
  [!VAR "OptimalTimeCs2CsError" = "$OptimalRelativeTimeError"!]
  [!//
  [!VAR "DesiredBaudrate" = "SpiBaudrate"!]
  [!CALL "DetermineOptimalBaudrateSettings"!]
  [!VAR "OptimalPBR" = "$OptimalPrescaler"!]
  [!VAR "OptimalSBR" = "$OptimalScaler"!]
  [!VAR "OptimalDBR" = "$OptimalDouble"!]
  [!VAR "OptimalBaudrateNormal" = "$OptimalBaudrate"!]
  [!VAR "OptimalRelativeBaudrateErrorNormal" = "$OptimalRelativeBaudrateError"!]
  [!//
  [!IF "$DualClockEnabled = 'true'"!][!//
    [!VAR "BusClock" = "$BusClockAlternate"!][!//
    [!VAR "DesiredTime" = "SpiTimeCs2Clk"!]
    [!CALL "DetermineOptimalTimeSettings"!]
    [!VAR "OptimalPCSCLKAlternate" = "$OptimalPrescaler"!]
    [!VAR "OptimalSCSCLKAlternate" = "$OptimalScaler"!]
    [!VAR "OptimalTimeCs2ClkAlternate" = "$OptimalTime"!]
    [!VAR "OptimalTimeCs2ClkErrorAlternate" = "$OptimalRelativeTimeError"!]
    [!//
    [!VAR "DesiredTime" = "SpiTimeClk2Cs"!]
    [!CALL "DetermineOptimalTimeSettings"!]
    [!VAR "OptimalPASCAlternate" = "$OptimalPrescaler"!]
    [!VAR "OptimalSASCAlternate" = "$OptimalScaler"!]
    [!VAR "OptimalTimeClk2CsAlternate" = "$OptimalTime"!]
    [!VAR "OptimalTimeClk2CsErrorAlternate" = "$OptimalRelativeTimeError"!]
    [!//
    [!VAR "DesiredTime" = "SpiTimeCs2Cs"!]
    [!CALL "DetermineOptimalTimeSettings"!]
    [!VAR "OptimalPDTAlternate" = "$OptimalPrescaler"!]
    [!VAR "OptimalSDTAlternate" = "$OptimalScaler"!]
    [!VAR "OptimalTimeCs2CsAlternate" = "$OptimalTime"!]
    [!VAR "OptimalTimeCs2CsErrorAlternate" = "$OptimalRelativeTimeError"!]
    [!//
    [!VAR "DesiredBaudrate" = "SpiBaudrate"!]
    [!CALL "DetermineOptimalBaudrateSettings"!]
    [!VAR "OptimalPBRAlternate" = "$OptimalPrescaler"!]
    [!VAR "OptimalSBRAlternate" = "$OptimalScaler"!]
    [!VAR "OptimalDBRAlternate" = "$OptimalDouble"!]
    [!VAR "OptimalBaudrateAlternate" = "$OptimalBaudrate"!]
    [!VAR "OptimalRelativeBaudrateErrorAlternate" = "$OptimalRelativeBaudrateError"!]
  [!ENDIF!][!// "$DualClockEnabled = 'true'"
  [!//
[!ENDNOCODE!][!//
[!IF "$DualClockEnabled = 'true'"!][!//
          {
            /* Normal Mode */
[!ENDIF!][!//
        (uint32)([!IF "SpiShiftClockIdleLevel = 'LOW'"!]DSPI_CTAR_CPOL_LOW[!//
[!ELSEIF "SpiShiftClockIdleLevel = 'HIGH'"!]DSPI_CTAR_CPOL_HIGH[!//
[!ELSE!][!ERROR "Illegal value for SpiShiftClockIdleLevel"!][!//
[!ENDIF!] | /* Clock Polarity (Idle State) */
        [!IF "SpiDataShiftEdge = 'LEADING'"!][!WS "8"!]DSPI_CTAR_CPHA_LEADING[!//
[!ELSEIF "SpiDataShiftEdge = 'TRAILING'"!][!WS "8"!]DSPI_CTAR_CPHA_TRAILING[!//
[!ELSE!][!ERROR "Illegal value for SpiDataShiftEdge"!][!//
[!ENDIF!] | /* Clock Phase */
        DSPI_CTAR_PCSCLK_[!"num:i($OptimalPCSCLK)"!] | DSPI_CTAR_SCSCLK_[!"num:i($OptimalSCSCLK)"!] | /* TimeCs2Clk: Should=[!"SpiTimeCs2Clk"!], Is=[!"num:i($OptimalTimeCs2Clk)"!], Error=[!"round(10000*$OptimalTimeCs2ClkError) div 100"!]% */
        DSPI_CTAR_PASC_[!"num:i($OptimalPASC)"!] | DSPI_CTAR_SASC_[!"num:i($OptimalSASC)"!] | /* TimeClk2Cs: Should=[!"SpiTimeClk2Cs"!], Is=[!"num:i($OptimalTimeClk2Cs)"!], Error=[!"round(10000*$OptimalTimeClk2CsError) div 100"!]% */
        DSPI_CTAR_PDT_[!"num:i($OptimalPDT)"!] | DSPI_CTAR_SDT_[!"num:i($OptimalSDT)"!] | /* TimeCs2Cs: Should=[!"SpiTimeCs2Cs"!], Is=[!"num:i($OptimalTimeCs2Cs)"!], Error=[!"round(10000*$OptimalTimeCs2CsError) div 100"!]% */
        DSPI_CTAR_PBR_[!"num:i($OptimalPBR)"!] | DSPI_CTAR_SBR_[!"num:i($OptimalSBR)"!] | DSPI_CTAR_DBR_[!"num:i($OptimalDBR)"!]), /* Baudrate: Should=[!"SpiBaudrate"!], Is=[!"num:i($OptimalBaudrate)"!], Error=[!"round(10000*$OptimalRelativeBaudrateError) div 100"!]% */
[!IF "$DualClockEnabled = 'true'"!][!//
            /* Alternate Mode */
            (uint32)([!IF "SpiShiftClockIdleLevel = 'LOW'"!]DSPI_CTAR_CPOL_LOW[!//
[!ELSEIF "SpiShiftClockIdleLevel = 'HIGH'"!]DSPI_CTAR_CPOL_HIGH[!//
[!ELSE!][!ERROR "Illegal value for SpiShiftClockIdleLevel"!][!//
[!ENDIF!] | /* Clock Polarity (Idle State) */
            [!IF "SpiDataShiftEdge = 'LEADING'"!][!WS "8"!]    DSPI_CTAR_CPHA_LEADING[!//
[!ELSEIF "SpiDataShiftEdge = 'TRAILING'"!][!WS "8"!]    DSPI_CTAR_CPHA_TRAILING[!//
[!ELSE!][!ERROR "Illegal value for SpiDataShiftEdge"!][!//
[!ENDIF!] | /* Clock Phase */
            DSPI_CTAR_PCSCLK_[!"num:i($OptimalPCSCLKAlternate)"!] | DSPI_CTAR_SCSCLK_[!"num:i($OptimalSCSCLKAlternate)"!] | /* TimeCs2Clk: Should=[!"SpiTimeCs2Clk"!], Is=[!"num:i($OptimalTimeCs2ClkAlternate)"!], Error=[!"round(10000*$OptimalTimeCs2ClkErrorAlternate) div 100"!]% */
            DSPI_CTAR_PASC_[!"num:i($OptimalPASCAlternate)"!] | DSPI_CTAR_SASC_[!"num:i($OptimalSASCAlternate)"!] | /* TimeClk2Cs: Should=[!"SpiTimeClk2Cs"!], Is=[!"num:i($OptimalTimeClk2CsAlternate)"!], Error=[!"round(10000*$OptimalTimeClk2CsErrorAlternate) div 100"!]% */
            DSPI_CTAR_PDT_[!"num:i($OptimalPDTAlternate)"!] | DSPI_CTAR_SDT_[!"num:i($OptimalSDTAlternate)"!] | /* TimeCs2Cs: Should=[!"SpiTimeCs2Cs"!], Is=[!"num:i($OptimalTimeCs2CsAlternate)"!], Error=[!"round(10000*$OptimalTimeCs2CsErrorAlternate) div 100"!]% */
            DSPI_CTAR_PBR_[!"num:i($OptimalPBRAlternate)"!] | DSPI_CTAR_SBR_[!"num:i($OptimalSBRAlternate)"!] | DSPI_CTAR_DBR_[!"num:i($OptimalDBRAlternate)"!]) /* Baudrate: Should=[!"SpiBaudrate"!], Is=[!"num:i($OptimalBaudrateAlternate)"!], Error=[!"round(10000*$OptimalRelativeBaudrateErrorAlternate) div 100"!]% */
          },
[!ENDIF!][!//
[!IF "SpiEnableCs = 'true'"!]
        (uint32)(DSPI_CMD_[!"SpiCsIdentifier"!] | /* Chip Select Pin */
        [!IF "SpiCsContinous = 'false'"!][!WS "8"!]DSPI_CMD_CONTINOUS_FALSE[!//
[!ELSEIF "SpiCsContinous = 'true'"!][!WS "8"!]DSPI_CMD_CONTINOUS_TRUE[!//
[!ELSE!][!ERROR "Illegal value for SpiCsContinous"!][!//
[!ENDIF!]), /* Continous chip select */
[!ELSE!][!WS "8"!]0x00000000u,
[!ENDIF!]
        [!IF "SpiCsPolarity = 'HIGH'"!][!//
[!WS "8"!]DSPI_[!"SpiCsIdentifier"!]_IDLEHIGH[!//
[!ELSE!][!//
[!WS "8"!](uint32)0u[!//
[!ENDIF!][!WS "2"!]/* Chip select polarity */
[!ENDMACRO!]

[!MACRO "GenerateTSBExternalDeviceInfo"!]
[!NOCODE!][!//
  [!//
  [!VAR "BusClock" = "$BusClockNormal"!][!//
  [!VAR "DesiredTime" = "SpiTimeCs2Clk"!]
  [!CALL "DetermineOptimalTimeSettings"!]
  [!VAR "OptimalPCSCLK" = "$OptimalPrescaler"!]
  [!VAR "OptimalSCSCLK" = "$OptimalScaler"!]
  [!VAR "OptimalTimeCs2Clk" = "$OptimalTime"!]
  [!VAR "OptimalTimeCs2ClkError" = "$OptimalRelativeTimeError"!]
  [!//
  [!VAR "DesiredTime" = "SpiTimeClk2Cs"!]
  [!CALL "DetermineOptimalTimeSettings"!]
  [!VAR "OptimalPASC" = "$OptimalPrescaler"!]
  [!VAR "OptimalSASC" = "$OptimalScaler"!]
  [!VAR "OptimalTimeClk2Cs" = "$OptimalTime"!]
  [!VAR "OptimalTimeClk2CsError" = "$OptimalRelativeTimeError"!]
  [!//
  [!VAR "DesiredTime" = "SpiTimeCs2Cs"!]
  [!CALL "DetermineOptimalTimeSettings"!]
  [!VAR "OptimalPDT" = "$OptimalPrescaler"!]
  [!VAR "OptimalSDT" = "$OptimalScaler"!]
  [!VAR "OptimalTimeCs2Cs" = "$OptimalTime"!]
  [!VAR "OptimalTimeCs2CsError" = "$OptimalRelativeTimeError"!]
  [!//
  [!VAR "DesiredBaudrate" = "SpiBaudrate"!]
  [!CALL "DetermineOptimalBaudrateSettings"!]
  [!VAR "OptimalPBR" = "$OptimalPrescaler"!]
  [!VAR "OptimalSBR" = "$OptimalScaler"!]
  [!VAR "OptimalDBR" = "$OptimalDouble"!]
  [!VAR "OptimalBaudrateNormal" = "$OptimalBaudrate"!]
  [!VAR "OptimalRelativeBaudrateErrorNormal" = "$OptimalRelativeBaudrateError"!]
  [!//
  [!IF "$DualClockEnabled = 'true'"!][!//
    [!VAR "BusClock" = "$BusClockAlternate"!][!//
    [!VAR "DesiredTime" = "SpiTimeCs2Clk"!]
    [!CALL "DetermineOptimalTimeSettings"!]
    [!VAR "OptimalPCSCLKAlternate" = "$OptimalPrescaler"!]
    [!VAR "OptimalSCSCLKAlternate" = "$OptimalScaler"!]
    [!VAR "OptimalTimeCs2ClkAlternate" = "$OptimalTime"!]
    [!VAR "OptimalTimeCs2ClkErrorAlternate" = "$OptimalRelativeTimeError"!]
    [!//
    [!VAR "DesiredTime" = "SpiTimeClk2Cs"!]
    [!CALL "DetermineOptimalTimeSettings"!]
    [!VAR "OptimalPASCAlternate" = "$OptimalPrescaler"!]
    [!VAR "OptimalSASCAlternate" = "$OptimalScaler"!]
    [!VAR "OptimalTimeClk2CsAlternate" = "$OptimalTime"!]
    [!VAR "OptimalTimeClk2CsErrorAlternate" = "$OptimalRelativeTimeError"!]
    [!//
    [!VAR "DesiredTime" = "SpiTimeCs2Cs"!]
    [!CALL "DetermineOptimalTimeSettings"!]
    [!VAR "OptimalPDTAlternate" = "$OptimalPrescaler"!]
    [!VAR "OptimalSDTAlternate" = "$OptimalScaler"!]
    [!VAR "OptimalTimeCs2CsAlternate" = "$OptimalTime"!]
    [!VAR "OptimalTimeCs2CsErrorAlternate" = "$OptimalRelativeTimeError"!]
    [!//
    [!VAR "DesiredBaudrate" = "SpiBaudrate"!]
    [!CALL "DetermineOptimalBaudrateSettings"!]
    [!VAR "OptimalPBRAlternate" = "$OptimalPrescaler"!]
    [!VAR "OptimalSBRAlternate" = "$OptimalScaler"!]
    [!VAR "OptimalDBRAlternate" = "$OptimalDouble"!]
    [!VAR "OptimalBaudrateAlternate" = "$OptimalBaudrate"!]
    [!VAR "OptimalRelativeBaudrateErrorAlternate" = "$OptimalRelativeBaudrateError"!]
  [!ENDIF!][!// "$DualClockEnabled = 'true'"
  [!//
[!ENDNOCODE!][!//
[!IF "$DualClockEnabled = 'true'"!][!//
          {
            /* Normal Mode */
[!ENDIF!][!//
        (uint32)([!IF "SpiShiftClockIdleLevel = 'LOW'"!]DSPI_CTAR_CPOL_LOW[!//
[!ELSEIF "SpiShiftClockIdleLevel = 'HIGH'"!]DSPI_CTAR_CPOL_HIGH[!//
[!ELSE!][!ERROR "Illegal value for SpiShiftClockIdleLevel"!][!//
[!ENDIF!] | /* Clock Polarity (Idle State) */
        [!IF "SpiDataShiftEdge = 'LEADING'"!][!WS "8"!]DSPI_CTAR_CPHA_LEADING[!//
[!ELSEIF "SpiDataShiftEdge = 'TRAILING'"!][!WS "8"!]DSPI_CTAR_CPHA_TRAILING[!//
[!ELSE!][!ERROR "Illegal value for SpiDataShiftEdge"!][!//
[!ENDIF!] | /* Clock Phase */
        DSPI_CTAR_PCSCLK_[!"num:i($OptimalPCSCLK)"!] | DSPI_CTAR_SCSCLK_[!"num:i($OptimalSCSCLK)"!] | /* TimeCs2Clk: Should=[!"SpiTimeCs2Clk"!], Is=[!"num:i($OptimalTimeCs2Clk)"!], Error=[!"round(10000*$OptimalTimeCs2ClkError) div 100"!]% */
        DSPI_CTAR_PASC_[!"num:i($OptimalPASC)"!] | DSPI_CTAR_SASC_[!"num:i($OptimalSASC)"!] | /* TimeClk2Cs: Should=[!"SpiTimeClk2Cs"!], Is=[!"num:i($OptimalTimeClk2Cs)"!], Error=[!"round(10000*$OptimalTimeClk2CsError) div 100"!]% */
        DSPI_CTAR_PDT_[!"num:i($OptimalPDT)"!] | DSPI_CTAR_SDT_[!"num:i($OptimalSDT)"!] | /* TimeCs2Cs: Should=[!"SpiTimeCs2Cs"!], Is=[!"num:i($OptimalTimeCs2Cs)"!], Error=[!"round(10000*$OptimalTimeCs2CsError) div 100"!]% */
        DSPI_CTAR_PBR_[!"num:i($OptimalPBR)"!] | DSPI_CTAR_SBR_[!"num:i($OptimalSBR)"!] | DSPI_CTAR_DBR_[!"num:i($OptimalDBR)"!]|
       [!IF "$Dualreceiver = 0"!]DSPI_DUALRECEIVER_DISABLED[!ELSE!][!//
        DSPI_CMD_WIDTH_[!"$Dualreceiver"!][!ENDIF!])[!IF "$DualClockEnabled = 'true'"!],[!ENDIF!] /* Baudrate: Should=[!"SpiBaudrate"!], Is=[!"num:i($OptimalBaudrate)"!], Error=[!"round(10000*$OptimalRelativeBaudrateError) div 100"!]% */
[!IF "$DualClockEnabled = 'true'"!][!//
            /* Alternate Mode */
            (uint32)([!IF "SpiShiftClockIdleLevel = 'LOW'"!]DSPI_CTAR_CPOL_LOW[!//
[!ELSEIF "SpiShiftClockIdleLevel = 'HIGH'"!]DSPI_CTAR_CPOL_HIGH[!//
[!ELSE!][!ERROR "Illegal value for SpiShiftClockIdleLevel"!][!//
[!ENDIF!] | /* Clock Polarity (Idle State) */
            [!IF "SpiDataShiftEdge = 'LEADING'"!][!WS "8"!]    DSPI_CTAR_CPHA_LEADING[!//
[!ELSEIF "SpiDataShiftEdge = 'TRAILING'"!][!WS "8"!]    DSPI_CTAR_CPHA_TRAILING[!//
[!ELSE!][!ERROR "Illegal value for SpiDataShiftEdge"!][!//
[!ENDIF!] | /* Clock Phase */
            DSPI_CTAR_PCSCLK_[!"num:i($OptimalPCSCLKAlternate)"!] | DSPI_CTAR_SCSCLK_[!"num:i($OptimalSCSCLKAlternate)"!] | /* TimeCs2Clk: Should=[!"SpiTimeCs2Clk"!], Is=[!"num:i($OptimalTimeCs2ClkAlternate)"!], Error=[!"round(10000*$OptimalTimeCs2ClkErrorAlternate) div 100"!]% */
            DSPI_CTAR_PASC_[!"num:i($OptimalPASCAlternate)"!] | DSPI_CTAR_SASC_[!"num:i($OptimalSASCAlternate)"!] | /* TimeClk2Cs: Should=[!"SpiTimeClk2Cs"!], Is=[!"num:i($OptimalTimeClk2CsAlternate)"!], Error=[!"round(10000*$OptimalTimeClk2CsErrorAlternate) div 100"!]% */
            DSPI_CTAR_PDT_[!"num:i($OptimalPDTAlternate)"!] | DSPI_CTAR_SDT_[!"num:i($OptimalSDTAlternate)"!] | /* TimeCs2Cs: Should=[!"SpiTimeCs2Cs"!], Is=[!"num:i($OptimalTimeCs2CsAlternate)"!], Error=[!"round(10000*$OptimalTimeCs2CsErrorAlternate) div 100"!]% */
            DSPI_CTAR_PBR_[!"num:i($OptimalPBRAlternate)"!] | DSPI_CTAR_SBR_[!"num:i($OptimalSBRAlternate)"!] | DSPI_CTAR_DBR_[!"num:i($OptimalDBRAlternate)"!] |
            [!IF "$Dualreceiver = 0"!]DSPI_DUALRECEIVER_DISABLED[!ELSE!][!//
            DSPI_CMD_WIDTH_[!"$Dualreceiver"!][!ENDIF!]) /* Baudrate: Should=[!"SpiBaudrate"!], Is=[!"num:i($OptimalBaudrateAlternate)"!], Error=[!"round(10000*$OptimalRelativeBaudrateErrorAlternate) div 100"!]% */
          }
[!ENDIF!][!//
[!ENDMACRO!]



[!ENDNOCODE!][!//
[!//
[!//
[!//
[!CODE!][!//
/**
    @file    Spi_PBcfg.c
    @version 2.0.0

    @brief   AUTOSAR Spi - Post-Build(PB) configuration file.
    @details Generated Post-Build(PB) configuration file.

    Project AUTOSAR 3.0 MCAL
    Patform PA
    Peripheral DSPI
    Dependencies 

    ARVersion 3.0.0
    ARRevision ASR_REL_3_0_REV_0003
    ARConfVariant
    SWVersion 2.0.0
    BuildVersion XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223

    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
    All Rights Reserved.
*/

/**
@page misra_violations MISRA-C:2004 violations

@section Spi_Lcfg_c_REF_1
Violates MISRA 2004 Advisory Rule Rule 19.1, only preprocessor statements
and comments before '#include'. AUTOSAR imposes the specification of the
sections in which certain parts of the driver must be placed.
@section Spi_Lcfg_c_REF_2
Violates MISRA 2004 Rule 19.15, precautions shall be taken in order to prevent the content of a
header file to be included twice. The inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Spi.h"
#include "Reg_eSys_DSPI.h"
#include "Mcal.h"
#if (SPI_CONFIG_VARIANT == SPI_VARIANT_POSTBUILD)

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
/**
@brief Parameters that shall be published within the configuration source file and also in the
       module's description file
@remarks Covers BSW00374, BSW00318
@{
*/
#define SPI_MODULE_ID_PBCFG_C         83
#define SPI_VENDOR_ID_PBCFG_C         43
#define SPI_AR_MAJOR_VERSION_PBCFG_C  3
#define SPI_AR_MINOR_VERSION_PBCFG_C  0
#define SPI_AR_PATCH_VERSION_PBCFG_C  0
#define SPI_SW_MAJOR_VERSION_PBCFG_C  2
#define SPI_SW_MINOR_VERSION_PBCFG_C  0
#define SPI_SW_PATCH_VERSION_PBCFG_C  0
/**@}*/
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and SPI header file are of the module ID */
#if (SPI_MODULE_ID_PBCFG_C != SPI_MODULE_ID_CFG)
    #error "Spi_PBcfg.c and Spi_Cfg.h have different module ids"
#endif

/* Check if source file and SPI header file are of the same vendor */
#if (SPI_VENDOR_ID_PBCFG_C != SPI_VENDOR_ID_CFG)
    #error "Spi_PBcfg.c and Spi_Cfg.h have different vendor ids"
#endif

/* Check if source file and SPI header file are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
  #if ((SPI_AR_MAJOR_VERSION_PBCFG_C != SPI_AR_MAJOR_VERSION_CFG) || \
       (SPI_AR_MINOR_VERSION_PBCFG_C != SPI_AR_MINOR_VERSION_CFG) || \
       (SPI_AR_PATCH_VERSION_PBCFG_C != SPI_AR_PATCH_VERSION_CFG))
      #error "AutoSar Version Numbers of Spi_PBcfg.c and Spi_Cfg.h are different"
  #endif
#endif

/* Check if source file and SPI header file are of the same Software version */
#if ((SPI_SW_MAJOR_VERSION_PBCFG_C != SPI_SW_MAJOR_VERSION_CFG) || \
     (SPI_SW_MINOR_VERSION_PBCFG_C != SPI_SW_MINOR_VERSION_CFG))
    #error "Software Version Numbers of Spi_PBcfg.c and Spi_Cfg.h are different"
#endif

/* Check if source file and Dem header file are of the same version */
#ifdef CHECK_AUTOSAR_VERSION
  #if ((SPI_AR_MAJOR_VERSION_PBCFG_C != DEM_AR_MAJOR_VERSION) || \
       (SPI_AR_MINOR_VERSION_PBCFG_C != DEM_AR_MINOR_VERSION))
      #error "AutoSar Version Numbers of Spi_PBcfg.c and Dem.h are different"
  #endif
#endif

[!NOCODE!][!//

[!VAR "OuterLoopCounter" = "0"!][!//
[!VAR "InnerLoopCounter" = "0"!][!//
[!LOOP "SpiDriver/*/SpiJob/*"!][!//
[!VAR "OuterLoopCounter" = "$OuterLoopCounter + 1"!]
    [!VAR "InnerLoopCounter" = "0"!]
    [!VAR "Matchcounter" = "0"!]
    [!VAR "Name" = "node:name(.)"!]
    [!LOOP "../../../*/SpiJob/*"!]
    [!VAR "InnerLoopCounter" = "$InnerLoopCounter + 1"!]
    [!IF "$OuterLoopCounter >= $InnerLoopCounter"!]
      [!IF "($Name = node:name(.))"!]
          [!VAR "Matchcounter" = "$Matchcounter + 1"!]
       [!ENDIF!][!//
    [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "$Matchcounter = 1"!]
    [!ELSE!][!//
        [!ERROR!]SpiJob Symbolic name "[!"@name"!]" for the two or more SpiJobs is repeated.[!ENDERROR!]
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!VAR "OuterLoopCounter" = "0"!][!//
[!VAR "InnerLoopCounter" = "0"!][!//
[!LOOP "SpiDriver/*/SpiSequence/*"!][!//
[!VAR "OuterLoopCounter" = "$OuterLoopCounter + 1"!]
    [!VAR "InnerLoopCounter" = "0"!]
    [!VAR "Matchcounter" = "0"!]
    [!VAR "Name" = "node:name(.)"!]
    [!LOOP "../../../*/SpiSequence/*"!]
    [!VAR "InnerLoopCounter" = "$InnerLoopCounter + 1"!]
    [!IF "$OuterLoopCounter >= $InnerLoopCounter"!]
      [!IF "($Name = node:name(.))"!]
          [!VAR "Matchcounter" = "$Matchcounter + 1"!]
       [!ENDIF!][!//
    [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "$Matchcounter = 1"!]
    [!ELSE!][!//
        [!ERROR!]SpiSequences Symbolic name "[!"@name"!]" for the two or more SpiSequences is repeated.[!ENDERROR!]
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!VAR "OuterLoopCounter" = "0"!][!//
[!VAR "InnerLoopCounter" = "0"!][!//
[!LOOP "SpiDriver/*/SpiExternalDevice/*"!][!//
[!VAR "OuterLoopCounter" = "$OuterLoopCounter + 1"!]
    [!VAR "InnerLoopCounter" = "0"!]
    [!VAR "Matchcounter" = "0"!]
    [!VAR "Name" = "node:name(.)"!]
    [!LOOP "../../../*/SpiExternalDevice/*"!]
    [!VAR "InnerLoopCounter" = "$InnerLoopCounter + 1"!]
    [!IF "$OuterLoopCounter >= $InnerLoopCounter"!]
      [!IF "($Name = node:name(.))"!]
          [!VAR "Matchcounter" = "$Matchcounter + 1"!]
       [!ENDIF!][!//
    [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "$Matchcounter = 1"!]
    [!ELSE!][!//
        [!ERROR!]SpiExternalDevice Symbolic name "[!"@name"!]" for the two or more SpiExternalDevices is repeated.[!ENDERROR!]
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!]

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
#define SPI_START_SEC_CODE
/**
@file Spi_PBcfg.c
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_PBcfg_c_REF_1 & @ref Spi_PBcfg_c_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/


/* Job start Notifications */
[!LOOP "SpiDriver/*/SpiJob/*"!][!//
[!VAR "WhiteSpaceInstartJobNotification"="normalize-space(SpiJobStartNotification)"!]
[!IF "(string-length($WhiteSpaceInstartJobNotification)>0) and (SpiJobStartNotification!='NULL_PTR') and (SpiJobStartNotification!='NULL')"!][!//
extern void [!"SpiJobStartNotification"!](void); /* start job Notification for Job '[!"name(.)"!]' */
[!ENDIF!][!//
[!ENDLOOP!][!//
[!//
/* Job End Notifications */
[!LOOP "SpiDriver/*/SpiJob/*"!][!//
[!VAR "WhiteSpaceInJobEndNotification"="normalize-space(SpiJobEndNotification)"!]
[!IF "(string-length($WhiteSpaceInJobEndNotification)>0) and (SpiJobEndNotification!='NULL_PTR') and (SpiJobEndNotification!='NULL')"!][!//
extern void [!"SpiJobEndNotification"!](void); /* End Notification for Job '[!"name(.)"!]' */
[!ENDIF!][!//
[!ENDLOOP!][!//
[!//
/* Sequence End Notifications */
[!NOCODE!]
[!LOOP "SpiDriver/*/SpiSequence/*"!][!//
[!VAR "WhiteSpaceInSeqEndNotification"="normalize-space(SpiSeqEndNotification)"!]
[!IF "(string-length($WhiteSpaceInSeqEndNotification)>0)  and (SpiSeqEndNotification!='NULL_PTR') and (SpiSeqEndNotification!='NULL')"!][!//
[!CODE!]
extern void [!"SpiSeqEndNotification"!](void); /* End Notification for Sequence '[!"name(.)"!]' */
[!ENDCODE!]
[!ENDIF!]
[!ENDLOOP!][!//
[!ENDNOCODE!]

#define SPI_STOP_SEC_CODE
/**
@file Spi_PBcfg.c
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_PBcfg_c_REF_1 & @ref Spi_PBcfg_c_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/

#define SPI_START_SEC_VAR_UNSPECIFIED
/**
@file Spi_PBcfg.c
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_PBcfg_c_REF_1 & @ref Spi_PBcfg_c_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

[!VAR "spiPath" = "node:path(.)"!][!//
/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/
[!NOCODE!][!//
[!VAR "OuterLoopCounter" = "0"!][!//
[!VAR "InnerLoopCounter" = "0"!][!//
[!ENDNOCODE!][!//
[!LOOP "SpiDriver/*/SpiChannel/*"!][!//
[!NOCODE!][!//
[!VAR "OuterLoopCounter" = "$OuterLoopCounter + 1"!][!//
    [!VAR "InnerLoopCounter" = "0"!][!//
    [!VAR "Matchcounter" = "0"!][!//
    [!VAR "TempChannel_FirstSpiChannelId" = "0"!][!//
    [!VAR "TempChannel_FirstSpiChannelType" = "SpiChannelType"!][!//
    [!VAR "TempChannel_FirstSpiDataWidth" = "SpiDataWidth"!][!//
    [!VAR "TempChannel_FirstSpiDefaultData" = "SpiDefaultData"!][!//
    [!VAR "TempChannel_FirstSpiEbMaxLength" = "SpiEbMaxLength"!][!//
    [!VAR "TempChannel_FirstSpiIbNBuffers" = "SpiChannelType"!][!//
    [!VAR "TempChannel_FirstSpiTransferStart" = "SpiTransferStart"!][!//
    [!VAR "Name" = "node:name(.)"!][!//
    [!LOOP "../../../*/SpiChannel/*"!][!//
    [!VAR "InnerLoopCounter" = "$InnerLoopCounter + 1"!][!//
    [!IF "$OuterLoopCounter >= $InnerLoopCounter"!][!//
      [!IF "($Name = node:name(.))"!][!//
         [!VAR "Matchcounter" = "$Matchcounter + 1"!][!//
         [!IF "$Matchcounter = 1"!][!//
         [!VAR "TempChannel_FirstSpiChannelId" = "SpiChannelId"!][!//
         [!VAR "TempChannel_FirstSpiChannelType" = "SpiChannelType"!][!//
         [!VAR "TempChannel_FirstSpiDataWidth" = "SpiDataWidth"!][!//
         [!VAR "TempChannel_FirstSpiDefaultData" = "SpiDefaultData"!][!//
         [!VAR "TempChannel_FirstSpiEbMaxLength" = "SpiEbMaxLength"!][!//
         [!VAR "TempChannel_FirstSpiIbNBuffers" = "SpiIbNBuffers"!][!//
         [!VAR "TempChannel_FirstSpiTransferStart" = "SpiTransferStart"!][!//
         [!ENDIF!][!//
         [!IF "($Matchcounter > 1) and (SpiChannelType = 'IB')"!][!//
         [!IF "($TempChannel_FirstSpiChannelId != SpiChannelId) or ($TempChannel_FirstSpiChannelType != SpiChannelType) or
         ($TempChannel_FirstSpiDataWidth != SpiDataWidth) or ($TempChannel_FirstSpiDefaultData != SpiDefaultData) or
         ($TempChannel_FirstSpiIbNBuffers != SpiIbNBuffers) or($TempChannel_FirstSpiTransferStart != SpiTransferStart) "!][!//
         [!ERROR!]If the same symbolic channel name [!"node:name(.)"!] is used for more than one channel, all channel attributes shall be identical.[!ENDERROR!]
         [!ENDIF!][!//
         [!ENDIF!][!//
         [!IF "($Matchcounter > 1) and (SpiChannelType = 'EB')"!][!//
         [!IF "($TempChannel_FirstSpiChannelId != SpiChannelId) or ($TempChannel_FirstSpiChannelType != SpiChannelType) or
         ($TempChannel_FirstSpiDataWidth != SpiDataWidth) or ($TempChannel_FirstSpiDefaultData != SpiDefaultData) or
         ($TempChannel_FirstSpiEbMaxLength != SpiEbMaxLength) or ($TempChannel_FirstSpiTransferStart != SpiTransferStart) "!][!//
         [!ERROR!]If the same symbolic channel name [!"node:name(.)"!] is used for more than one channel, all channel attributes shall be identical.[!ENDERROR!]
         [!ENDIF!][!//
         [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDNOCODE!][!//
[!IF "$Matchcounter = 1"!]
[!IF "SpiChannelType = 'EB'"!][!//
/*  Buffers Descriptors for EB Channels (if any) */
[!IF "node:exists(../../../../SpiNonAUTOSAR/SpiForceDataType) and (node:value(../../../../SpiNonAUTOSAR/SpiForceDataType) = 'true')"!][!//
[!IF "num:i(SpiDataWidth) > 8"!][!//
VAR_ALIGN(static VAR(Spi_BufferDescriptor, SPI_VAR) Buffer_PB[!"name(.)"!], 2)
[!ELSE!][!//
static VAR(Spi_BufferDescriptor, SPI_VAR) Buffer_PB[!"name(.)"!];
[!ENDIF!][!//
[!ELSE!][!//
static VAR(Spi_BufferDescriptor, SPI_VAR) Buffer_PB[!"name(.)"!];
[!ENDIF!][!//
[!ELSEIF "SpiChannelType = 'IB'"!][!//
/* Allocate Buffers for IB Channels (if any) */
[!IF "node:exists(../../../../SpiNonAUTOSAR/SpiForceDataType) and (node:value(../../../../SpiNonAUTOSAR/SpiForceDataType) = 'true')"!][!//
[!IF "num:i(SpiDataWidth) > 8"!][!//
VAR_ALIGN(static VAR(Spi_DataType, SPI_VAR) BufferTX_PB[!"name(.)"!][[!"SpiIbNBuffers"!]], 2)
VAR_ALIGN(static VAR(Spi_DataType, SPI_VAR) BufferRX_PB[!"name(.)"!][[!"SpiIbNBuffers"!]], 2)
[!ELSE!][!//
static VAR(Spi_DataType, SPI_VAR) BufferTX_PB[!"name(.)"!][[!"SpiIbNBuffers"!]];
static VAR(Spi_DataType, SPI_VAR) BufferRX_PB[!"name(.)"!][[!"SpiIbNBuffers"!]];
[!ENDIF!][!//
[!ELSE!][!//
static VAR(Spi_DataType, SPI_VAR) BufferTX_PB[!"name(.)"!][[!"SpiIbNBuffers"!]];
static VAR(Spi_DataType, SPI_VAR) BufferRX_PB[!"name(.)"!][[!"SpiIbNBuffers"!]];
[!ENDIF!][!//
[!ELSE!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//

#define SPI_STOP_SEC_VAR_UNSPECIFIED
/**
@file Spi_PBcfg.c
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_PBcfg_c_REF_1 & @ref Spi_PBcfg_c_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/

#define SPI_START_CONFIG_DATA_UNSPECIFIED
/**
@file Spi_PBcfg.c
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_PBcfg_c_REF_1 & @ref Spi_PBcfg_c_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

/* POSTBUILD FLASH from here onward! */

/*  Buffers Descriptors for IB Channels (if any) */
[!NOCODE!][!//
[!VAR "OuterLoopCounter" = "0"!][!//
[!VAR "InnerLoopCounter" = "0"!][!//
[!ENDNOCODE!][!//
[!LOOP "SpiDriver/*/SpiChannel/*"!][!//
[!NOCODE!][!//
[!VAR "OuterLoopCounter" = "$OuterLoopCounter + 1"!][!//
    [!VAR "InnerLoopCounter" = "0"!][!//
    [!VAR "Matchcounter" = "0"!][!//
    [!VAR "TempChannel_FirstSpiChannelId" = "0"!][!//
    [!VAR "TempChannel_FirstSpiChannelType" = "SpiChannelType"!][!//
    [!VAR "TempChannel_FirstSpiDataWidth" = "SpiDataWidth"!][!//
    [!VAR "TempChannel_FirstSpiDefaultData" = "SpiDefaultData"!][!//
    [!VAR "TempChannel_FirstSpiEbMaxLength" = "SpiEbMaxLength"!][!//
    [!VAR "TempChannel_FirstSpiIbNBuffers" = "SpiChannelType"!][!//
    [!VAR "TempChannel_FirstSpiTransferStart" = "SpiTransferStart"!][!//
    [!VAR "Name" = "node:name(.)"!][!//
    [!LOOP "../../../*/SpiChannel/*"!][!//
    [!VAR "InnerLoopCounter" = "$InnerLoopCounter + 1"!][!//
    [!IF "$OuterLoopCounter >= $InnerLoopCounter"!][!//
      [!IF "($Name = node:name(.))"!][!//
         [!VAR "Matchcounter" = "$Matchcounter + 1"!][!//
         [!IF "$Matchcounter = 1"!][!//
         [!VAR "TempChannel_FirstSpiChannelId" = "SpiChannelId"!][!//
         [!VAR "TempChannel_FirstSpiChannelType" = "SpiChannelType"!][!//
         [!VAR "TempChannel_FirstSpiDataWidth" = "SpiDataWidth"!][!//
         [!VAR "TempChannel_FirstSpiDefaultData" = "SpiDefaultData"!][!//
         [!VAR "TempChannel_FirstSpiEbMaxLength" = "SpiEbMaxLength"!][!//
         [!VAR "TempChannel_FirstSpiIbNBuffers" = "SpiIbNBuffers"!][!//
         [!VAR "TempChannel_FirstSpiTransferStart" = "SpiTransferStart"!][!//
         [!ENDIF!][!//
         [!IF "($Matchcounter > 1) and (SpiChannelType = 'IB')"!][!//
         [!IF "($TempChannel_FirstSpiChannelId != SpiChannelId) or ($TempChannel_FirstSpiChannelType != SpiChannelType) or
         ($TempChannel_FirstSpiDataWidth != SpiDataWidth) or ($TempChannel_FirstSpiDefaultData != SpiDefaultData) or
         ($TempChannel_FirstSpiIbNBuffers != SpiIbNBuffers) or($TempChannel_FirstSpiTransferStart != SpiTransferStart) "!][!//
         [!ERROR!]If the same symbolic channel name [!"node:name(.)"!] is used for more than one channel, all channel attributes shall be identical.[!ENDERROR!]
         [!ENDIF!][!//
         [!ENDIF!][!//
         [!IF "($Matchcounter > 1) and (SpiChannelType = 'EB')"!][!//
         [!IF "($TempChannel_FirstSpiChannelId != SpiChannelId) or ($TempChannel_FirstSpiChannelType != SpiChannelType) or
         ($TempChannel_FirstSpiDataWidth != SpiDataWidth) or ($TempChannel_FirstSpiDefaultData != SpiDefaultData) or
         ($TempChannel_FirstSpiEbMaxLength != SpiEbMaxLength) or ($TempChannel_FirstSpiTransferStart != SpiTransferStart) "!][!//
         [!ERROR!]If the same symbolic channel name [!"node:name(.)"!] is used for more than one channel, all channel attributes shall be identical.[!ENDERROR!]
         [!ENDIF!][!//
         [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDNOCODE!][!//
[!IF "$Matchcounter = 1"!]
[!IF "SpiChannelType = 'IB'"!][!//
static CONST(Spi_BufferDescriptor, SPI_CONST) Buffer_PB[!"name(.)"!] =
{
    BufferTX_PB[!"name(.)"!],
    BufferRX_PB[!"name(.)"!]
};
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//

[!LOOP "SpiDriver/*"!][!//
[!VAR "idx" = "1"!][!//
[!VAR "LoopVar"="0"!][!//
[!VAR "count" = "count(SpiChannel/*)"!][!//
/* SpiChannelConfig_PB[!"@index"!] Channel Configuration of [!"name(.)"!]*/
static CONST(Spi_ChannelConfig, SPI_CONST) SpiChannelConfig_PB[!"@index"!][[!"num:i($count)"!]] =
{
[!FOR "x" = "0" TO "num:i(count(SpiChannel/*))"!][!//
[!LOOP "SpiChannel/*"!][!//
[!VAR "Loop"="num:i($LoopVar)"!][!//
[!IF "SpiChannelId = $Loop"!][!//
    {
        /* [!"name(.)"!]*/
        [!"SpiChannelType"!],
        [!"SpiDefaultData"!]U,
[!IF "SpiChannelType = 'IB'"!][!//
        [!"SpiIbNBuffers"!]U,
[!ENDIF!][!//
[!IF "SpiChannelType = 'EB'"!][!//
        [!"SpiEbMaxLength"!]U,
[!ENDIF!][!//
        &Buffer_PB[!"name(.)"!],
        &SpiChannelState[[!"SpiChannelId"!]]
    }[!IF "$idx!=$count"!],[!ENDIF!]
[!VAR "idx" = "$idx + 1"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!VAR "LoopVar"="$LoopVar + 1"!][!//
[!CR!][!ENDFOR!][!//
};
[!ENDLOOP!][!//

/* Channel to Job Assignment */
[!/* Retrieves all Channel assignments */!]
[!LOOP "SpiDriver/*/SpiJob/*"!][!//
static CONST(Spi_ChannelType, SPI_CONST) [!"name(.)"!]_ChannelAssignment_PB[[!"num:i(count(ChannelAssignment/*))"!]] = {[!//
[!LOOP "ChannelAssignment/*"!][!//
[!IF "@index > 0"!],[!ENDIF!][!//
[!"name(node:ref(.))"!][!//
[!ENDLOOP!]};
[!ENDLOOP!][!//

[!VAR "DualClockEnabled" = "node:exists(SpiNonAUTOSAR/SpiEnableDualClockMode) and (node:value(SpiNonAUTOSAR/SpiEnableDualClockMode) = 'true')"!][!//
[!SELECT "node:ref(SpiGeneral/SpiClockRef)"!][!//
[!VAR "SpiPeriphFrequency" = "McuClockReferencePointFrequency"!][!//
[!ENDSELECT!][!//
[!VAR "BusClockNormal" = "string($SpiPeriphFrequency div 1000000)"!][!//
[!IF "$DualClockEnabled = 'true'"!][!//
[!SELECT "node:ref(SpiNonAUTOSAR/SpiAlternateClockRef)"!][!//
[!VAR "SpiPeriphFrequency" = "McuClockReferencePointFrequency"!][!//
[!ENDSELECT!][!//
[!VAR "BusClockAlternate" = "string($SpiPeriphFrequency div 1000000)"!][!//
[!ENDIF!][!//
[!LOOP "SpiDriver/*"!][!//
[!VAR "idx" = "1"!][!//
[!VAR "LoopVar"="0"!][!//
[!VAR "count" = "count(SpiJob/*)"!][!//
/* SpiJobConfig_PB[!"@index"!] Job Configuration of [!"name(.)"!]*/
static CONST(Spi_JobConfig, SPI_CONST) SpiJobConfig_PB[!"@index"!][[!"num:i($count)"!]] =
{
[!FOR "x" = "0" TO "num:i(count(SpiJob/*))"!][!//
[!LOOP "SpiJob/*"!][!//
[!VAR "Loop"="num:i($LoopVar)"!][!//
[!IF "SpiJobId = $Loop"!][!//
    {
[!VAR "WhiteSpaceInJobEndNotification1"="normalize-space(SpiJobEndNotification)"!]
[!VAR "WhiteSpaceInstartJobNotification1"="normalize-space(SpiJobStartNotification)"!]
        /* [!"name(.)"!] */
        (Spi_ChannelType)[!"num:i(count(ChannelAssignment/*))"!]u,
        [!"name(.)"!]_ChannelAssignment_PB, /* List of Channels */
[!IF "(string-length($WhiteSpaceInJobEndNotification1)>0) and (SpiJobEndNotification!='NULL_PTR') and (SpiJobEndNotification!='NULL')"!][!//
        [!"SpiJobEndNotification"!][!//
[!ELSE!][!//
        NULL_PTR[!//
[!ENDIF!], /* End Notification */
[!IF "(string-length($WhiteSpaceInstartJobNotification1)>0) and (SpiJobStartNotification!='NULL_PTR') and (SpiJobStartNotification!='NULL')"!][!//
        [!"SpiJobStartNotification"!][!//
[!ELSE!][!//
        NULL_PTR[!//
[!ENDIF!], /* job start Notification */
        (sint8)[!"SpiJobPriority"!], /* Priority */
        &SpiJobState[[!"SpiJobId"!]], /* JobState instance */
        [!"SpiHwUnit"!], /* HWUnit index */
[!VAR "varSpiHwUnit"="string(substring-after(SpiHwUnit,'CSIB')+1)"!][!//
        [!"node:value(concat($spiPath,'/SpiGeneral/SpiPhyUnit/*[',$varSpiHwUnit,']/SpiPhyUnitMapping'))"!]_OFFSET, /* DSPI device HW unit offset */
        /* External Device Settings */
        [!SELECT "node:ref(DeviceAssignment)"!]
        [!WS "8"!][!"name(.)"!], /* External Device */
        {
        [!CALL "GenerateExternalDeviceInfo"!]
        }
        [!ENDSELECT!]
    }[!IF "$idx!=$count"!],[!ENDIF!]
[!VAR "idx" = "$idx + 1"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!VAR "LoopVar"="$LoopVar + 1"!][!//
[!CR!][!ENDFOR!][!//
};
[!ENDLOOP!][!//

/* Job to Sequence Assignment */
[!LOOP "SpiDriver/*/SpiSequence/*"!][!//
static CONST(Spi_JobType, SPI_CONST) [!"name(.)"!]_JobAssignment_PB[[!"num:i(count(JobAssignment/*))"!]] = {[!//
[!LOOP "JobAssignment/*"!][!//
[!/* Check if reference node has the name "Job". We need to avoid the name "Job" */!][!//
[!/* driver shall run into problems if a name "Job" is founded */!][!//
[!IF "name(node:ref(.)) = 'Job'"!][!//
Job_default[!//
[!ELSE!][!//
[!IF "@index > 0"!],[!ENDIF!][!//
[!"name(node:ref(.))"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
};
[!ENDLOOP!][!//

[!LOOP "SpiDriver/*"!][!//
[!VAR "idx" = "1"!][!//
[!VAR "LoopVar"="0"!][!//
[!VAR "count" = "count(SpiSequence/*)"!][!//
/* SpiSequenceConfig_PB[!"@index"!] Sequence Configuration of [!"name(.)"!]*/
static CONST(Spi_SequenceConfig, SPI_CONST) SpiSequenceConfig_PB[!"@index"!][[!"num:i($count)"!]] =
{
[!FOR "x" = "0" TO "num:i(count(SpiSequence/*))"!][!//
[!LOOP "SpiSequence/*"!][!//
[!VAR "Loop"="num:i($LoopVar)"!][!//
[!IF "SpiSequenceId = $Loop"!][!//
    {  /* [!"name(.)"!] */
[!VAR "WhiteSpaceInSeqEndNotification1"="normalize-space(SpiSeqEndNotification)"!]
        (Spi_JobType)[!"num:i(count(JobAssignment/*))"!]u,
        [!"name(.)"!]_JobAssignment_PB, /* List of Jobs */
[!IF "(string-length($WhiteSpaceInSeqEndNotification1)>0) and (SpiSeqEndNotification!='NULL_PTR') and (SpiSeqEndNotification!='NULL')"!][!//
        [!"SpiSeqEndNotification"!][!//
[!ELSE!][!//
        NULL_PTR[!//
[!ENDIF!], /* End Notification */
        [!WS "8"!][!IF "SpiInterruptibleSequence"!](uint8)TRUE[!ELSE!](uint8)FALSE[!ENDIF!] /* Interruptible */
    }[!IF "$idx!=$count"!],[!ENDIF!]
[!VAR "idx" = "$idx + 1"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!VAR "LoopVar"="$LoopVar + 1"!][!//
[!CR!][!ENDFOR!][!//
};
[!ENDLOOP!][!//

/*---------------------------------------------------------------------------
             SPI Driver Implementation Specific Configuration
-----------------------------------------------------------------------------*/
[!LOOP "SpiDriver/*"!][!//
[!VAR "idx" = "1"!][!//
[!VAR "LoopVar"="0"!][!//
[!VAR "count" = "count(SpiChannel/*)"!][!//
/* DspiChannelAttributesConfig_PB[!"@index"!] Channel Attribute Configuration of [!"name(.)"!]*/
static CONST(Spi_LLD_ChannelAttributesConfig, SPI_CONST) DspiChannelAttributesConfig_PB[!"@index"!][[!"num:i($count)"!]] =
{
[!FOR "x" = "0" TO "num:i(count(SpiChannel/*))"!][!//
[!LOOP "SpiChannel/*"!][!//
[!VAR "Loop"="num:i($LoopVar)"!][!//
[!IF "SpiChannelId = $Loop"!][!//
[!IF "node:exists(../../../../SpiNonAUTOSAR/SpiForceDataType) and (node:value(../../../../SpiNonAUTOSAR/SpiForceDataType) = 'true')"!][!//
[!IF "num:i(SpiDataWidth) > 8"!][!//
    {(uint32)(DSPI_CMD_[!"SpiTransferStart"!] | DSPI_CMD_WIDTH_[!"SpiDataWidth"!]),SPI_DATA_WIDTH_16}[!//
[!ELSE!][!//
    {(uint32)(DSPI_CMD_[!"SpiTransferStart"!] | DSPI_CMD_WIDTH_[!"SpiDataWidth"!]),SPI_DATA_WIDTH_8}[!//
[!ENDIF!][!//
[!ELSE!][!//
    {(uint32)(DSPI_CMD_[!"SpiTransferStart"!] | DSPI_CMD_WIDTH_[!"SpiDataWidth"!])}[!//
[!ENDIF!][!//
[!IF "$idx!=$count"!],[!ENDIF!]
[!VAR "idx" = "$idx + 1"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!VAR "LoopVar"="$LoopVar + 1"!][!//
[!CR!][!ENDFOR!][!//
};
[!ENDLOOP!][!//

[!LOOP "SpiDriver/*"!][!//
[!VAR "var"= "1"!][!VAR "deviceattribute"= "num:i(count(SpiExternalDevice/*))-1"!][!//

/* DspiDeviceAttributesConfig_PB[!"@index"!] Device Attribute Configuration of [!"name(.)"!]*/
static CONST(Spi_LLD_DeviceAttributesConfig, SPI_CONST) DspiDeviceAttributesConfig_PB[!"@index"!][[!"num:i(count(SpiExternalDevice/*))"!]] =
{
[!AUTOSPACING!][!LOOP "SpiExternalDevice/*"!][!//
    {  /* [!"name(.)"!] */
        [!CALL "GenerateExternalDeviceInfo"!]
    }[!IF "$deviceattribute>=$var"!],[!ENDIF!][!VAR "var"= "$var+1"!][!//
[!CR!][!ENDLOOP!][!//
};
[!ENDLOOP!][!//

[!LOOP "SpiDriver/*"!][!//

/* SpiAttributesConfig_PB[!"@index"!] Attribute Configuration of [!"@name"!] */
static CONST(Spi_AttributesConfig, SPI_CONST) SpiAttributesConfig_PB[!"@index"!] = {
    DspiChannelAttributesConfig_PB[!"@index"!],
    DspiDeviceAttributesConfig_PB[!"@index"!]
};
[!ENDLOOP!][!//

/* Array of DSPI Unit configurations */
static CONST(Spi_HWUnitConfig, SPI_CONST) HWUnitConfig_PB[SPI_MAX_HWUNIT] =
{
[!VAR "var"= "1"!][!VAR "numdevices"= "num:i(count(SpiGeneral/SpiPhyUnit/*))-1"!][!//
[!AUTOSPACING!][!LOOP "SpiGeneral/SpiPhyUnit/*"!][!//
    { [!"SpiPhyUnitMapping"!]_OFFSET, [!//
[!IF "SpiPhyUnitSync = 'true'"!][!//
SPI_PHYUNIT_SYNC[!//
[!ELSE!][!//
SPI_PHYUNIT_ASYNC[!//
[!IF "ecu:get('SpiDMAPresent') = 'TRUE' and node:exists(../../SpiGlobalDmaEnable) and ../../SpiGlobalDmaEnable = 'true'"!][!//
[!IF "node:exists(SpiPhyUnitAsyncMethod) and SpiPhyUnitAsyncMethod = 'DMA'"!][!//
, (uint16)TRUE, [!"SpiPhyTxDmaChannel"!]u, [!"SpiPhyTxDmaChannelAux"!]u, [!"SpiPhyRxDmaChannel"!]u[!//
[!ELSE!][!//
, (uint16)FALSE[!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
 }[!IF "$numdevices>=$var"!],[!ENDIF!][!VAR "var"= "$var+1"!][!//
[!CR!][!ENDLOOP!][!//
};

/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/

[!LOOP "SpiDriver/*"!][!//

/* [!"@name"!] Configuration */
CONST(Spi_ConfigType, SPI_CONST) [!"@name"!] =
{
    [!"num:i(count(SpiExternalDevice/*))"!]u,
    [!"num:i(count(SpiChannel/*))"!]u,
    [!"num:i(count(SpiJob/*))"!]u,
    [!"num:i(count(SpiSequence/*))"!]u,
    SpiChannelConfig_PB[!"@index"!],
    SpiJobConfig_PB[!"@index"!],
    SpiSequenceConfig_PB[!"@index"!],
    &SpiAttributesConfig_PB[!"@index"!],
    HWUnitConfig_PB
};
[!ENDLOOP!][!//

[!IF "node:exists(SpiNonAUTOSAR/SpiTSBModeSupport) and (node:value(SpiNonAUTOSAR/SpiTSBModeSupport) = 'true')"!][!//
[!LOOP "SpiDriver/*"!][!//
[!VAR "idx" = "1"!][!//
[!VAR "LoopVar"="0"!][!//
[!VAR "count" = "count(SpiJob/*)"!][!//
[!VAR "TSBJobCount"="0"!][!//
[!LOOP "SpiJob/*"!][!//
[!IF "node:exists(TSBModeEnable) and TSBModeEnable = 'true'"!][!//
   [!VAR "TSBJobCount" = "$TSBJobCount +1"!] [!ENDIF!][!//
[!ENDLOOP!][!//
[!IF "$TSBJobCount=0"!]
  [!ERROR!] Atlease one TSBJob should be configured as SpiTSBModeSupport is enabled [!ENDERROR!]
[!ENDIF!]
/* SpiJobConfig_PB[!"@index"!] Job Configuration of [!"name(.)"!]*/
CONST(Spi_TSBConfig, SPI_CONST) SpiJobTSBConfig[[!"num:i($TSBJobCount)"!]] =
{
[!VAR "Dualreceiver" = "0"!]
[!FOR "x" = "0" TO "num:i(count(SpiJob/*))"!][!//
[!LOOP "SpiJob/*"!][!//
[!IF "node:exists(TSBModeEnable) and TSBModeEnable = 'true'"!][!//
[!VAR "Loop"="num:i($LoopVar)"!][!//
[!IF "SpiJobId = $Loop"!][!//
   {
       (Spi_JobType)([!"SpiJobId"!]),  /*Normal Job Id*/
       /*DSICR attributes*/
       (uint32)(DSPI_DSICR_CS_[!"DsiCsIdentifier"!] | [!//
       [!IF "TransmitDataSource = 'DSISerializationRegister'"!]DSPI_DSICR_TXSS_CLEAR[!//
       [!ELSEIF "TransmitDataSource = 'DSIAltSerRegister'"!]DSPI_DSICR_TXSS_SET[!//
       [!ENDIF!] |[!//
       [!IF "node:exists(ChangeInDataTransfer) and ChangeInDataTransfer = 'true'"!]DSPI_DSICR_CID_SET[!//
       [!ELSEIF "node:exists(ChangeInDataTransfer) and ChangeInDataTransfer = 'false'"!]DSPI_DSICR_CID_CLEAR[!//
       [!ENDIF!] ),
       /*DSICR1 attributes*/
       (uint32)([!IF "DualReceiverSupport = 'true'"!]DSPI_DSICR1_CS_[!"SecondaryDsiCsIdentifier"!][!//
       [!ELSE!]DSPI_DUALRECEIVER_DISABLED[!//
       [!ENDIF!][!//
       | DSPI_DSICR1_TSBCNT_[!"TSBFrameSize"!]),
       [!NOCODE!]
       ([!IF "DualReceiverSupport = 'true'"!]
       [!VAR "Dualreceiver" = "SecondaryFrameSize"!][!//
       [!ELSE!]
       [!VAR "Dualreceiver" = "0"!][!//
       [!ENDIF!])
       [!ENDNOCODE!]
       /*CTAR2 attributes*/ /* External Device Settings */
       [!SELECT "node:ref(DeviceAssignment)"!]
       [!CALL "GenerateTSBExternalDeviceInfo"!][!//
       [!ENDSELECT!]
   }[!IF "$idx!=$count"!],[!ELSE!][!ENDIF!]
[!VAR "idx" = "$idx + 1"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!VAR "LoopVar"="$LoopVar + 1"!][!//
[!CR!][!ENDFOR!][!//
};
[!ENDLOOP!][!//
[!ENDIF!][!//

#define SPI_STOP_CONFIG_DATA_UNSPECIFIED
/**
@file Spi_PBcfg.c
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_PBcfg_c_REF_1 & @ref Spi_PBcfg_c_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

#endif /*(SPI_CONFIG_VARIANT == SPI_VARIANT_POSTBUILD)*/

#ifdef __cplusplus
}
#endif

[!ENDCODE!]
