[!/*
    @file     Lin_BaudRate_com.m_Inc.m
    @version  2.0.0
    
    @brief    AUTOSAR Lin - Brief description.
    @details  Baud rate computation for Lin_Cfg.c, Lin_PBcfg.c
    
    Project        AUTOSAR 3.0 MCAL
    Platform       PA
    Peripheral     ESCI
    Dependencies   
    
    ARVersion      3.0.0
    ARRevision     ASR_REL_3_0_REV_0003
    ARConfVariant  
    SWVersion      2.0.0
    BuildVersion   XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223
    
    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
    All Rights Reserved.
*/!]
[!/*================================================================================================
====================================================================================================
*/!]
[!VAR "ClockFrequencyFromMcu" = "McuClockReferencePointFrequency"!]
    [!VAR "SBR" = "($ClockFrequencyFromMcu div ($linBaudrate * 16))"!][//
    [!VAR "temp1" = "num:i($SBR)"!][!//
    [!VAR "ESCISBR" = "num:inttohex($temp1,4)"!][!//
    [!VAR "temp2" = "($linBaudrate - $temp1) div $linBaudrate"!][!//
