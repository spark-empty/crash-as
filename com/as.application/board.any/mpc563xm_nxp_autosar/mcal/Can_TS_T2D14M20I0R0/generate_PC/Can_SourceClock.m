[!NOCODE!]
/**
  @file    Can_SourceClock.m
  @version 2.0.0

  @brief   AUTOSAR Can - version check macro.
  @details Extract source clock from MCU plugin.
  
  Project AUTOSAR 3.0 MCAL
  Platform PA
  Peripheral FLEXCAN
  Dependencies 

  ARVersion 3.0.0
  ARRevision ASR_REL_3_0_REV_0003
  ARConfVariant
  SWVersion 2.0.0
  BuildVersion XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223

  (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
  All Rights Reserved.
*/
/*==================================================================================================
==================================================================================================*/
[!ENDNOCODE!]

[!/* *** multiple inclusion protection *** */!]
[!IF "not(var:defined('CAN_SOURCECLOCK_M'))"!]
[!VAR "CAN_SOURCECLOCK_M"="'true'"!]
[!MACRO "CanClockFrequency_M"!]
    [!/* Use the Reference of MCU from CAN module and calculate CAN clock Frequency for any late useless. 
         The scope is to calculate the <<CANClockFrequencyFromMcu>> valiable from below (in Hz). */!]
    [!SELECT "node:ref(CanCpuClockRef)"!][!/* Switch to MCU model to obtain clock source - MCU is refered by CAN module! */!]

        [!VAR "CANClockFrequencyFromMcu" = "McuClockReferencePointFrequency"!]

    [!ENDSELECT!]

    [!IF "node:exists(./../../../../CanGeneral/CanEnableDualClockMode)"!][!IF "./../../../../CanGeneral/CanEnableDualClockMode = 'true'"!]
        [!SELECT "node:ref(CanCpuClockRef_Alternate)"!][!/* Switch to MCU model to obtain clock source - MCU is refered by CAN module! */!]
            [!VAR "CANClockFrequencyFromMcu_Alternate" = "McuClockReferencePointFrequency"!]
    [!ENDSELECT!]
    [!ENDIF!][!ENDIF!]
[!ENDMACRO!]

[!MACRO "CanOscillatorFrequency_M"!]
    [!SELECT "node:ref(./../../../../CanGeneral/CanOscillatorClockRef)"!][!/* Switch to MCU model to obtain Oscillator frequency- MCU is refered by CAN module! */!]
        [!VAR "CanCrystalFrequency" = "CrystalFrequencyHz"!][!/* Frequency provided by user */!]
    [!ENDSELECT!]
[!ENDMACRO!]
[!ENDIF!]
    
