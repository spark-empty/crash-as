[!NOCODE!]
/**
  @file    Can_VersionCheck_Inc.m
  @version 2.0.0

  @brief   AUTOSAR Can - version check macro.
  @details Version checks.
  
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

    [!VAR "CAN_AR_MAJOR_VERSION_TEMPLATE"="3"!]
    [!VAR "CAN_AR_MINOR_VERSION_TEMPLATE"="0"!]
    [!VAR "CAN_AR_PATCH_VERSION_TEMPLATE"="0"!]
    [!VAR "CAN_SW_MAJOR_VERSION_TEMPLATE"="2"!]
    [!VAR "CAN_SW_MINOR_VERSION_TEMPLATE"="0"!]
[!ENDNOCODE!]

[!/* *** multiple inclusion protection *** */!]
[!IF "not(var:defined('CAN_VERSIONCHECK_INC_M'))"!]
[!VAR "CAN_VERSIONCHECK_INC_M"="'true'"!]


[!SELECT "CommonPublishedInformation"!]
[!/*
    [!ASSERT "ArMajorVersion = num:i($CAN_AR_MAJOR_VERSION_TEMPLATE)"!]
        **** AUTOSAR major version number of the Basic Software Module Description file (CAN.epd version [!"ArMajorVersion"!]) and the Code template file (CAN_Cfg.h  version [!"num:i($CAN_AR_MAJOR_VERSION_TEMPLATE)"!]) are different ****
    [!ENDASSERT!]

    [!ASSERT "ArMinorVersion  = num:i($CAN_AR_MINOR_VERSION_TEMPLATE)"!]
        **** AUTOSAR minor version number of the Basic Software Module Description file (CAN.epd version [!"ArMinorVersion"!]) and the Code template file (CAN_Cfg.h  version [!"num:i($CAN_AR_MINOR_VERSION_TEMPLATE)"!]) are different ****
    [!ENDASSERT!]

    [!ASSERT "ArPatchVersion  = num:i($CAN_AR_PATCH_VERSION_TEMPLATE)"!]
        **** AUTOSAR patch version number of the Basic Software Module Description file (CAN.epd version [!"ArPatchVersion"!]) and the Code template file (CAN_Cfg.h version [!"num:i($CAN_AR_PATCH_VERSION_TEMPLATE)"!]) are different ****
    [!ENDASSERT!]
*/!]
    [!ASSERT "SwMajorVersion = num:i($CAN_SW_MAJOR_VERSION_TEMPLATE)"!]
        **** The software major number of the Basic Software Module Description file (CAN.epd version [!"SwMajorVersion"!]) and the Code template file (CAN_Cfg.h version [!"num:i($CAN_SW_MAJOR_VERSION_TEMPLATE)"!]) are different ****
    [!ENDASSERT!]

    [!ASSERT "SwMinorVersion = num:i($CAN_SW_MINOR_VERSION_TEMPLATE)"!]
        **** The software minor number of the Basic Software Module Description file (CAN.epd version [!"SwMinorVersion"!]) and the Code template file (CAN_Cfg.h version [!"num:i($CAN_SW_MINOR_VERSION_TEMPLATE)"!]) are different ****
    [!ENDASSERT!]
[!ENDSELECT!]

[!NOCODE!]
    /* put here the CODE section */
[!ENDNOCODE!]

[!ENDIF!]
