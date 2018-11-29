[!NOCODE!][!//
/**
    @file    LIN_VersionCheck_Inc.m
    @version 2.0.0

    @brief   AUTOSAR Lin - Brief description.
    @details Version check variables vor Lin_Cfg.c
    
    Project AUTOSAR 3.0 MCAL
    Patform PA
    Peripheral ESCI
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

[!VAR "LIN_AR_MAJOR_VERSION_TEMPLATE"="3"!][!//
[!VAR "LIN_AR_MINOR_VERSION_TEMPLATE"="0"!][!//
[!VAR "LIN_AR_PATCH_VERSION_TEMPLATE"="0"!][!//
[!VAR "LIN_SW_MAJOR_VERSION_TEMPLATE"="2"!][!//
[!VAR "LIN_SW_MINOR_VERSION_TEMPLATE"="0"!][!//
[!ENDNOCODE!][!//
[!SELECT "CommonPublishedInformation"!][!//
[!/*
[!IF "num:i(ArMajorVersion) != num:i($LIN_AR_MAJOR_VERSION_TEMPLATE)"!]
[!ERROR!]
      **** AUTOSAR major version number of the Basic Software Module Description file (Lin.epd version [!"ArMajorVersion"!]) and the Code template file (Lin_Cfg.c version [!"num:i($LIN_AR_MAJOR_VERSION_TEMPLATE)"!]) are different ****
[!ENDERROR!]      
[!ENDIF!][!//
[!IF "num:i(ArMinorVersion)  != num:i($LIN_AR_MINOR_VERSION_TEMPLATE)"!]
[!ERROR!]
      **** AUTOSAR minor version number of the Basic Software Module Description file (Lin.epd version [!"ArMinorVersion"!]) and the Code template file (Lin_Cfg.c version [!"num:i($LIN_AR_MINOR_VERSION_TEMPLATE)"!]) are different ****
[!ENDERROR!]      
[!ENDIF!][!//
[!IF "num:i(ArPatchVersion)  != num:i($LIN_AR_PATCH_VERSION_TEMPLATE)"!]
[!ERROR!]
      **** AUTOSAR patch version number of the Basic Software Module Description file (Lin.epd version [!"ArPatchVersion"!]) and the Code template file (Lin_Cfg.c version [!"num:i($LIN_AR_PATCH_VERSION_TEMPLATE)"!]) are different ****
[!ENDERROR!]      
[!ENDIF!][!//
*/!]
[!IF "num:i(SwMajorVersion) != num:i($LIN_SW_MAJOR_VERSION_TEMPLATE)"!]
[!ERROR!]
      **** The software major number of the Basic Software Module Description file (Lin.epd version [!"SwMajorVersion"!]) and the Code template file (Lin_Cfg.c version [!"num:i($LIN_SW_MAJOR_VERSION_TEMPLATE)"!]) are different ****
[!ENDERROR!]      
[!ENDIF!][!//
[!IF "num:i(SwMinorVersion) != num:i($LIN_SW_MINOR_VERSION_TEMPLATE)"!]
[!ERROR!]
      **** The software minor number of the Basic Software Module Description file (Lin.epd version [!"SwMinorVersion"!]) and the Code template file (Lin_Cfg.c version [!"num:i($LIN_SW_MINOR_VERSION_TEMPLATE)"!]) are different ****
[!ENDERROR!]      
[!ENDIF!][!//
[!ENDSELECT!][!//
[!NOCODE!][!//
[!ENDNOCODE!][!//
