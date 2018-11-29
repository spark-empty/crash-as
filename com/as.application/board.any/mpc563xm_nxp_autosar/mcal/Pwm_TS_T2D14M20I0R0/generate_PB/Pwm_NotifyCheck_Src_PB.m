[!NOCODE!][!//

/**
  @file    Pwm_NotifyCheck_Src_PB.m
  @version 2.0.0

  @brief   AUTOSAR Pwm - Notify check.
  @details Notify check.
  
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
[!IF "not(var:defined('PWM_NOTIFY_CHECK_SRC_PB_M'))"!]
[!VAR "PWM_NOTIFY_CHECK_SRC_PB_M"="'true'"!]


[!NOCODE!][!//
[!MACRO "PwmNotifyCheck_PB"!][!//
[!VAR "OuterLoopCounter" = "0"!][!//
[!VAR "InnerLoopCounter" = "0"!] [!//
[!LOOP "PwmChannelConfigSet/*/PwmChannel/*"!][!//
    [!VAR "OuterLoopCounter" = "$OuterLoopCounter + 1"!][!//
    [!VAR "InnerLoopCounter" = "0"!][!//
        [!VAR "Matchcounter" = "0"!][!//
    [!VAR "Notification" = "PwmNotification"!][!//
    [!LOOP "../../../*/PwmChannel/*"!][!//
    [!IF "(PwmNotification != 'NULL_PTR') and (PwmNotification != '"NULL"') and (PwmNotification != 'NULL')"!][!//
    [!VAR "InnerLoopCounter" = "$InnerLoopCounter + 1"!]
    [!IF "$OuterLoopCounter >= $InnerLoopCounter"!][!//
        [!IF "($Notification = PwmNotification)"!][!//
          [!VAR "Matchcounter" = "$Matchcounter + 1"!]
    [!ENDIF!][!//
    [!ENDIF!][!//
    [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "$Matchcounter >= 1"!][!CODE!][!//
[!"PwmChannelConfigSet/*/PwmChannel/*"!][!//
extern void [!"PwmNotification"!](void);
[!ENDCODE!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDNOCODE!]


[!ENDIF!][!// avoid multiple inclusion ENDIF
