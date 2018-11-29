[!NOCODE!][!//
/**
  @file    Wdg_VersionCheck_Src_LT.m
  @version 2.0.0

  @brief   AUTOSAR Wdg - version check macro.
  @details Version checks.
  
  Project AUTOSAR 3.0 MCAL
  Platform PA
  Peripheral Swt
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

[!VAR "WDG_AR_MAJOR_VERSION_TEMPLATE"="3"!][!//
[!VAR "WDG_AR_MINOR_VERSION_TEMPLATE"="0"!][!//
[!VAR "WDG_AR_PATCH_VERSION_TEMPLATE"="0"!][!//
[!VAR "WDG_SW_MAJOR_VERSION_TEMPLATE"="2"!][!//     
[!VAR "WDG_SW_MINOR_VERSION_TEMPLATE"="0"!][!//  
[!VAR "WDG_SW_PATCH_VERSION_TEMPLATE"="0"!][!//

[!ENDNOCODE!][!//
[!//
[!/* *** multiple inclusion protection *** */!][!//
[!IF "not(var:defined('WDG_VS_CHECKS_SRC_LT_M'))"!][!//
[!VAR "WDG_VS_CHECKS_SRC_LT_M"="'true'"!][!//
[!//
[!SELECT "CommonPublishedInformation"!][!//
[!/*
[!IF "not(num:i(ArMajorVersion) = num:i($WDG_AR_MAJOR_VERSION_TEMPLATE))"!]
       [!ERROR!]
        "AUTOSAR major version number of the Basic Software Module Description file (Wdg.epd version [!"ArMajorVersion"!]) and the Code template file (Wdg_LCfg.c version [!"num:i($WDG_AR_MAJOR_VERSION_TEMPLATE)"!]) are different "
        [!ENDERROR!]
[!ENDIF!][!//
[!IF "not(num:i(ArMinorVersion)  = num:i($WDG_AR_MINOR_VERSION_TEMPLATE))"!]
       [!ERROR!]
        "AUTOSAR minor version number of the Basic Software Module Description file (Wdg.epd version [!"ArMinorVersion"!]) and the Code template file (Wdg_LCfg.c version [!"num:i($WDG_AR_MINOR_VERSION_TEMPLATE)"!]) are different "
      [!ENDERROR!] 
[!ENDIF!][!//
[!IF "not(num:i(ArPatchVersion)  = num:i($WDG_AR_PATCH_VERSION_TEMPLATE))"!]
       [!ERROR!]
        "AUTOSAR patch version number of the Basic Software Module Description file (Wdg.epd version [!"ArPatchVersion"!]) and the Code template file (Wdg_LCfg.c version [!"num:i($WDG_AR_PATCH_VERSION_TEMPLATE)"!]) are different "
      [!ENDERROR!]     
[!ENDIF!][!//
*/!]

[!IF "not(num:i(SwMajorVersion) = num:i($WDG_SW_MAJOR_VERSION_TEMPLATE))"!][!//
    [!ERROR!][!//
        "The software major number of the Basic Software Module Description file (Wdg.epd version [!"SwMajorVersion"!]) and the Code template file (Wdg_LCfg.c version [!"num:i($WDG_SW_MAJOR_VERSION_TEMPLATE)"!]) are different "[!//
    [!ENDERROR!][!//
[!ENDIF!][!//
[!IF "not(num:i(SwMinorVersion) = num:i($WDG_SW_MINOR_VERSION_TEMPLATE))"!][!//
      [!ERROR !][!//
        "The software minor number of the Basic Software Module Description file (Wdg.epd version [!"SwMinorVersion"!]) and the Code template file (Wdg_LCfg.c version [!"num:i($WDG_SW_MINOR_VERSION_TEMPLATE)"!]) are different "[!//
      [!ENDERROR!][!//
[!ENDIF!][!//
[!IF "not(num:i(SwPatchVersion) = num:i($WDG_SW_PATCH_VERSION_TEMPLATE))"!][!//
      [!ERROR !][!//
        "The software minor number of the Basic Software Module Description file (Wdg.epd version [!"SwMinorVersion"!]) and the Code template file (Wdg_Cfg.h version [!"num:i($WDG_SW_MINOR_VERSION_TEMPLATE)"!]) are different "[!//
      [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!NOCODE!][!//
[!//
[!ENDNOCODE!][!//
[!ENDIF!][!//