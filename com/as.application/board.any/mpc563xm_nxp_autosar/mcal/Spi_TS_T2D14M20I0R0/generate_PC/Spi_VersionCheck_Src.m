[!NOCODE!][!//
/**
  @file    Spi_VersionCheck_Src.m
  @version 2.0.0

  @brief   AUTOSAR Spi - version check macro.
  @details Version checks.
  
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
/*==================================================================================================
==================================================================================================*/

[!VAR "SPI_AR_MAJOR_VERSION_TEMPLATE"="3"!][!//
[!VAR "SPI_AR_MINOR_VERSION_TEMPLATE"="0"!][!//
[!VAR "SPI_AR_PATCH_VERSION_TEMPLATE"="0"!][!//
[!VAR "SPI_SW_MAJOR_VERSION_TEMPLATE"="2"!][!//
[!VAR "SPI_SW_MINOR_VERSION_TEMPLATE"="0"!][!//
[!ENDNOCODE!][!//
[!SELECT "CommonPublishedInformation"!][!//
[!/*
[!ASSERT "num:i(ArMajorVersion) = num:i($SPI_AR_MAJOR_VERSION_TEMPLATE)"!]
            **** AUTOSAR major version number of the Basic Software Module Description file (Spi.epd version [!"ArMajorVersion "!]) and the Code template files (Spi_Cfg.c version [!"num:i($SPI_AR_MAJOR_VERSION_TEMPLATE)"!]) are different ****
[!ENDASSERT!][!//
[!ASSERT "num:i(ArMinorVersion)  = num:i($SPI_AR_MINOR_VERSION_TEMPLATE)"!]
            **** AUTOSAR minor version number of the Basic Software Module Description file (Spi.epd version [!"ArMinorVersion"!]) and the Code template files ( Spi_Cfg.c version [!"num:i($SPI_AR_MINOR_VERSION_TEMPLATE)"!]) are different ****
[!ENDASSERT!][!//
[!ASSERT "num:i(ArPatchVersion)  = num:i($SPI_AR_PATCH_VERSION_TEMPLATE)"!]
            **** AUTOSAR patch version number of the Basic Software Module Description file (Spi.epd version [!"ArPatchVersion"!]) and the Code template files ( Spi_Cfg.c version [!"num:i($SPI_AR_PATCH_VERSION_TEMPLATE)"!]) are different ****
[!ENDASSERT!][!//
*/!]
[!ASSERT "num:i(SwMajorVersion) = num:i($SPI_SW_MAJOR_VERSION_TEMPLATE)"!]
            **** The software major number of the Basic Software Module Description file (Spi.epd version [!"SwMajorVersion"!]) and the Code template files (Spi_Cfg.c version [!"num:i($SPI_SW_MAJOR_VERSION_TEMPLATE)"!]) are different ****
[!ENDASSERT!][!//
[!ASSERT "num:i(SwMinorVersion) = num:i($SPI_SW_MINOR_VERSION_TEMPLATE)"!]
            **** The software minor number of the Basic Software Module Description file (Spi.epd version [!"SwMinorVersion"!]) and the Code template files ( Spi_Cfg.c version [!"num:i($SPI_SW_MINOR_VERSION_TEMPLATE)"!]) are different ****
[!ENDASSERT!][!//
[!ENDSELECT!][!//
[!NOCODE!][!//
[!ENDNOCODE!][!//
