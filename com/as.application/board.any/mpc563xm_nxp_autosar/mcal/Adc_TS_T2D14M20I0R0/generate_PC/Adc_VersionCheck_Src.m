[!NOCODE!][!//
/**
  @file    Adc_VersionCheck_Src.m
  @version 2.0.0

  @brief   AUTOSAR Adc - version check macro.
  @details Version checks.

  Project AUTOSAR 3.0 MCAL
  Patform PA
  Peripheral ADC_10B
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

[!VAR "ADC_AR_MAJOR_VERSION_TEMPLATE"="3"!][!//
[!VAR "ADC_AR_MINOR_VERSION_TEMPLATE"="0"!][!//
[!VAR "ADC_AR_PATCH_VERSION_TEMPLATE"="0"!][!//
[!VAR "ADC_SW_MAJOR_VERSION_TEMPLATE"="2"!][!//
[!VAR "ADC_SW_MINOR_VERSION_TEMPLATE"="0"!][!//
[!ENDNOCODE!][!//
[!SELECT "CommonPublishedInformation"!][!//
[!/*
[!ASSERT "ArMajorVersion = num:i($ADC_AR_MAJOR_VERSION_TEMPLATE)"!]
        **** AUTOSAR major version number of the Basic Software Module Description file (Adc.epd version [!"ArMajorVersion"!]) and the Code template file (Adc_Cfg.c version [!"num:i($ADC_AR_MAJOR_VERSION_TEMPLATE)"!]) are different ****
[!ENDASSERT!][!//
[!ASSERT "ArMinorVersion  = num:i($ADC_AR_MINOR_VERSION_TEMPLATE)"!]
        **** AUTOSAR minor version number of the Basic Software Module Description file (Adc.epd version [!"ArMinorVersion"!]) and the Code template file (Adc_Cfg.c version [!"num:i($ADC_AR_MINOR_VERSION_TEMPLATE)"!]) are different ****
[!ENDASSERT!][!//
[!ASSERT "ArPatchVersion  = num:i($ADC_AR_PATCH_VERSION_TEMPLATE)"!]
        **** AUTOSAR patch version number of the Basic Software Module Description file (Adc.epd version [!"ArPatchVersion"!]) and the Code template file (Adc_Cfg.c version [!"num:i($ADC_AR_PATCH_VERSION_TEMPLATE)"!]) are different ****
[!ENDASSERT!][!//
*/!]
[!ASSERT "SwMajorVersion = num:i($ADC_SW_MAJOR_VERSION_TEMPLATE)"!]
        **** The software major number of the Basic Software Module Description file (Adc.epd version [!"SwMajorVersion"!]) and the Code template file (Adc_Cfg.c version [!"num:i($ADC_SW_MAJOR_VERSION_TEMPLATE)"!]) are different ****
[!ENDASSERT!][!//
[!ASSERT "SwMinorVersion = num:i($ADC_SW_MINOR_VERSION_TEMPLATE)"!]
        **** The software minor number of the Basic Software Module Description file (Adc.epd version [!"SwMinorVersion"!]) and the Code template file (Adc_Cfg.c version [!"num:i($ADC_SW_MINOR_VERSION_TEMPLATE)"!]) are different ****
[!ENDASSERT!][!//
[!ENDSELECT!][!//
[!NOCODE!][!//
[!ENDNOCODE!][!//
