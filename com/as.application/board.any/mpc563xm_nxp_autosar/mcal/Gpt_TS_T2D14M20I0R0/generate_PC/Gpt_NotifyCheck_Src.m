[!NOCODE!][!//

/**
  @file    Gpt_NotifyCheck_Src.m
  @version 2.0.0

  @brief   AUTOSAR Gpt - notify check macro.
  @details notify checks.
  
  Project AUTOSAR 3.0 MCAL
  Patform PA
  Peripheral eMIOS200_Stm_PitRti
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

[!ENDNOCODE!]

[!CODE!][!//
/*==================================================================================================
                                        LOCAL MACROS (.m file)
==================================================================================================*/
/* The integration of incompatible files shall be avoided. */
#define NTFCCK_AR_MAJOR_VERSION_M    3
#define NTFCCK_AR_MINOR_VERSION_M    0
#define NTFCCK_AR_PATCH_VERSION_M    0
#define NTFCCK_SW_MAJOR_VERSION_M    2
#define NTFCCK_SW_MINOR_VERSION_M    0
#define NTFCCK_SW_PATCH_VERSION_M    0
/*================================================================================================*/
[!ENDCODE!]

[!NOCODE!][!//
[!MACRO "GptNotifyCheck1"!][!//
[!VAR "OuterLoopCounter" = "0"!][!//
[!VAR "InnerLoopCounter" = "0"!] [!//
[!LOOP "GptChannelConfigSet/*[1]/GptChannelConfiguration/*"!][!//
    [!VAR "OuterLoopCounter" = "$OuterLoopCounter + 1"!][!//
    [!VAR "InnerLoopCounter" = "0"!][!//
        [!VAR "Matchcounter" = "0"!][!//
    [!VAR "Notification" = "GptNotification"!][!//
    [!LOOP "../../../*[1]/GptChannelConfiguration/*"!][!//
    [!IF "(GptNotification != 'NULL_PTR') and (GptNotification != 'NULL')"!][!//
    [!VAR "InnerLoopCounter" = "$InnerLoopCounter + 1"!]
    [!IF "$OuterLoopCounter >= $InnerLoopCounter"!][!//
        [!IF "($Notification = GptNotification)"!][!//
          [!VAR "Matchcounter" = "$Matchcounter + 1"!]
                [!ENDIF!][!//
    [!ENDIF!][!//
    [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "$Matchcounter = 1"!][!CODE!][!//
[!"GptChannelConfigSet/*[1]/GptChannelConfiguration/*"!][!//
extern void [!"GptNotification"!](void);
[!ENDCODE!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDNOCODE!]
