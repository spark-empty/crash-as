[!NOCODE!][!//

/**
  @file    Pwm_Clock_Tree.m
  @version 2.0.0

  @brief   AUTOSAR Pwm - Clock Tree.
  @details Clock tree computations.
  
  Project AUTOSAR 3.0 MCAL
  Patform PA
  Peripheral eMIOS200
  Dependencies none
  
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
[!ENDNOCODE!][!// 


[!/* avoid multiple inclusion */!]
[!IF "not(var:defined('PWM_CLOCK_TREE_M'))"!]
[!VAR "PWM_CLOCK_TREE_M"="'true'"!]
 
  
[!NOCODE!][!//
[!IF "PwmGeneral/PwmClockFromMCU = 'true'"!]
[!/* Reference MCU plugin from PWM to obtain the clock frequency for eMIOS0 peripheral.
   The scope is to calculate the clock value for each eMIOS peripheral instance (in Hz). */!]
[!SELECT "node:ref(PwmGeneral/PwmCpuClockRef)"!][!/* Switch to MCU model to obtain clock source - MCU is referenced by PWM module! */!]
                                 
        [!/* eMIOS0 global prescaler */!]
        [!VAR "McuEMIOS0_Global_DIV"  = "McuEMIOSSettings/GlobalPrescaler"!]
        [!VAR "McuEMIOS0_Global_DIV"  = "$McuEMIOS0_Global_DIV+1"!]
        [!VAR "EMIOS0_ClockFrequency" = "McuClockReferencePointFrequency  div $McuEMIOS0_Global_DIV"!]
        [!VAR "McuClockReferencePointFrequency_Debug" = "McuClockReferencePointFrequency"!]
        [!VAR "EmiosA_LowPower"  = "McuEMIOSSettings/MdisBit"!]
        
        [!IF "$EmiosA_LowPower = 'true'"!]
        [!WARNING!]
MdisBit in McuEMIOSSettings_A is set, this puts EMIOS_A in low power mode.
The Pwm driver will not work if pwm channels are configured on EMIOS_A.
        [!ENDWARNING!]
[!CODE!]/* WARNING:
 * MdisBit in McuEMIOSSettings_A is set, this puts EMIOS_A in low power mode.
 * The Pwm driver will not work if pwm channels are configured on EMIOS_A.
 */[!ENDCODE!]
        [!ENDIF!]

[!ENDSELECT!]

[!ELSE!]
        [!/* EMIOS clock value entered in the PWM plugin and MCU reference not used. */!]

        [!VAR "McuEMIOS0_Global_DIV"  = "'false'"!]
        [!VAR "EMIOS0_ClockFrequency" = "PwmGeneral/PwmEmiosClockValue"!]
        [!VAR "McuClockReferencePointFrequency_Debug" = "'false'"!]
        [!VAR "EmiosA_LowPower"  = "'false'"!]

[!ENDIF!]


[!IF "PwmGeneral/PwmGenerateClockTreeDebugInfo = 'true'"!]
[!CODE!]
/*  --- EMIOS Clock Tree Debug information ---

[!IF "PwmGeneral/PwmClockFromMCU = 'true'"!]
Clock source: MCU
[!ELSE!]
Clock source: PWM debug
[!ENDIF!]

McuClockReferencePointFrequency  : [!"$McuClockReferencePointFrequency_Debug"!] Hz
EmiosA_LowPower : [!"$EmiosA_LowPower"!]
McuEMIOS0_Global_DIV : [!"$McuEMIOS0_Global_DIV"!]
EMIOS0_ClockFrequency : [!"$EMIOS0_ClockFrequency"!] Hz

*/
[!ENDCODE!]
[!ENDIF!]

[!ENDNOCODE!][!//

[!ENDIF!][!// avoid multiple inclusion ENDIF

