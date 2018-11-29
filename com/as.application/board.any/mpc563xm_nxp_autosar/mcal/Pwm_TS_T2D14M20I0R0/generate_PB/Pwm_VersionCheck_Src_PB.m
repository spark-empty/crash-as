[!NOCODE!][!//

/**
  @file    Pwm_VersionCheck_Src_PB.m
  @version 2.0.0

  @brief   AUTOSAR Pwm - version checks.
  @details Version check.
  
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
[!IF "not(var:defined('PWM_VERSION_CHECK_SRC_PB_M'))"!]
[!VAR "PWM_VERSION_CHECK_SRC_PB_M"="'true'"!]


[!VAR "PWM_AR_MAJOR_VERSION_TEMPLATE"="3"!][!//
[!VAR "PWM_AR_MINOR_VERSION_TEMPLATE"="0"!][!//
[!VAR "PWM_AR_PATCH_VERSION_TEMPLATE"="0"!][!//
[!VAR "PWM_SW_MAJOR_VERSION_TEMPLATE"="2"!][!//
[!VAR "PWM_SW_MINOR_VERSION_TEMPLATE"="0"!][!//
[!VAR "PWM_SW_PATCH_VERSION_TEMPLATE"="0"!][!//

[!SELECT "CommonPublishedInformation"!][!//
[!/*
[!IF "ArMajorVersion != num:i($PWM_AR_MAJOR_VERSION_TEMPLATE)"!]
                [!ERROR!]
                **** AUTOSAR major version number of the Basic Software Module Description file (Pwm.epd version [!"ArMajorVersion "!]) and the Code template files (Pwm_PBcfg.c  version [!"num:i($PWM_AR_MAJOR_VERSION_TEMPLATE)"!]) are different ****
                [!ENDERROR!]
[!ENDIF!]
[!IF "ArMinorVersion != num:i($PWM_AR_MINOR_VERSION_TEMPLATE)"!]
                [!ERROR!]
                **** AUTOSAR minor version number of the Basic Software Module Description file (Pwm.epd version [!"ArMinorVersion"!]) and the Code template files (Pwm_PBcfg.c version [!"num:i($PWM_AR_MINOR_VERSION_TEMPLATE)"!]) are different ****
                [!ENDERROR!]
                [!ENDIF!]
[!IF "ArPatchVersion != num:i($PWM_AR_PATCH_VERSION_TEMPLATE)"!]
                [!ERROR!]
                **** AUTOSAR patch version number of the Basic Software Module Description file (Pwm.epd version [!"ArPatchVersion"!]) and the Code template files (Pwm_PBcfg.c  version [!"num:i($PWM_AR_PATCH_VERSION_TEMPLATE)"!]) are different ****
                [!ENDERROR!]
[!ENDIF!]
*/!]
[!IF "SwMajorVersion != num:i($PWM_SW_MAJOR_VERSION_TEMPLATE)"!]
                [!ERROR!]
                **** The software major number of the Basic Software Module Description file (Pwm.epd version [!"SwMajorVersion"!]) and the Code template files (Pwm_PBcfg.c  version [!"num:i($PWM_SW_MAJOR_VERSION_TEMPLATE)"!]) are different ****
                [!ENDERROR!]
[!ENDIF!]
[!IF "SwMinorVersion != num:i($PWM_SW_MINOR_VERSION_TEMPLATE)"!]
                [!ERROR!]
                **** The software minor number of the Basic Software Module Description file (Pwm.epd version [!"SwMinorVersion"!]) and the Code template files (Pwm_PBcfg.c  version [!"num:i($PWM_SW_MINOR_VERSION_TEMPLATE)"!]) are different ****
                [!ENDERROR!]
[!ENDIF!]
[!IF "SwPatchVersion != num:i($PWM_SW_PATCH_VERSION_TEMPLATE)"!]
                [!ERROR!]
                **** The software patch number of the Basic Software Module Description file (Pwm.epd version [!"SwPatchVersion"!]) and the Code template files (Pwm_PBcfg.c version [!"num:i($PWM_SW_PATCH_VERSION_TEMPLATE)"!]) are different ****
                [!ENDERROR!]
[!ENDIF!]
[!ENDSELECT!][!//
[!NOCODE!][!//
[!ENDNOCODE!][!//


[!ENDIF!][!// avoid multiple inclusion ENDIF

