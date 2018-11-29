::===================================================================================================
::
::    @file        launch.bat
::    @version     2.0.0
::
::    @brief       AUTOSAR - Sample_app - launches build.
::    @details     Launches the build of the sample application
::
::    Project      : AUTOSAR 3.0 MCAL
::    Patform      : PA
::    Peripheral   : 
::    Dependencies : Base Det Dem Port Dio Mcu SchM Wdg WdgIf CanIf LinIf EcuM
::
::    Autosar Version       : 1.9.0
::    Autosar Revision      : ASR_REL_1_9_REV_0003
::    Autosar Conf. Variant :
::    Software Version      : 2.0.0
::    Build Version         : MPC563xMxM_MCAL_2_0_0_RTM_ASR_REL_1_9_REV_0003_20110214
::
::    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
::    All Rights Reserved.
::
::===================================================================================================
::::===================================================================================================

@echo off

:: uncomment line below if you do not set TRESOS_DIR over environment
SET TRESOS_DIR=E:\EB\tresos_20100409-release2010a-sr4

::OS Path
SET SSC_ROOT=E:\Freescale\AUTOSAR\os_freescale_mpc56xxAM

::Compiler Path
SET CW_DIR=E:\TOOLS\cw\CW_2.8_b209
SET DIAB_DIR=E:\TOOLS\WindRiver\DIAB_5_8_0_0-2_wind00198363_20100511_123238\diab\5.8.0.0
SET GHS_DIR=E:\TOOLS\ghs\multi524


if not defined TRESOS_DIR GOTO missing_path_names_TRESOS_DIR
if not exist %TRESOS_DIR% GOTO missing_path_names_TRESOS_DIR

cmd /c "make.bat %1 %2 %3 %4 %5 %6"

GOTO end

:: The variable TRESOS_DIR was not specified
:missing_path_names_TRESOS_DIR
ECHO.
ECHO    The variable TRESOS_DIR was not set correctly.
ECHO    Please specify this variable manually, by editing
ECHO    the batch file 'launch.bat'.
ECHO.
pause
GOTO end

:end
