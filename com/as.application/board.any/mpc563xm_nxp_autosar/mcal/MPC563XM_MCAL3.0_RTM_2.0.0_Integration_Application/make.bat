::===================================================================================================
::
::    @file        make.bat
::    @version     2.0.0
::
::    @brief       AUTOSAR - Sample_app - launches the make command.
::    @details     launches the make command. A user makefile and optional parameter can be specified
::                 USAGE:
::                      make.bat [-f makefilename] [make_options] [target]
::                              -f          this parameter is optional. If -f is
::                                          missing, a default makefile.mak is used
::                              make_options options of make.exe
::                              target      one of the make targets
::                                          (listed when calling launch.bat)
::                      make.bat help      print information on usage
::                      make.bat -h
::                      make.bat --h
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


@ECHO OFF


:: a help message is wanted
IF "%1"=="-h" GOTO need_help
IF "%1"=="--help" GOTO need_help
IF "%1"=="help" GOTO need_help
:: a user makefile is specified
IF "%1"=="-f" GOTO user_makefile
:: no user makefile is specified, use default file
IF "%1"=="clean" GOTO default_make_clean
IF "%1"=="TOOLCHAIN" GOTO default_make_toolchain
IF "%1"=="OS" GOTO default_make_os
GOTO default_make

:: output a help message on usage of make.bat
:need_help
ECHO.
ECHO.
ECHO    launch.bat [-f makefilename] [make_options] [TOOLCHAIN=(ghs|diab|cw)]
ECHO          -f            this parameter is optional. If -f is
ECHO                        missing, a default makefile.mak is used
ECHO          make_options  options of make.exe
ECHO          TOOLCHAIN=ghs Select the ghs toolchain.
ECHO                        Default toolchai is ghs
ECHO.
ECHO    launch.bat help      print this message
ECHO    launch.bat -h
ECHO    launch.bat --help
ECHO.
ECHO.
GOTO end

:: a user makefile is specified
:user_makefile
set USER_MAKE_FILE=%2
CALL %TRESOS_DIR%/bin/make.exe -f %2 %3 %4 %5 %6 %7 %8 %9
GOTO end

:: clean target received in command line
:default_make_clean
set USER_MAKE_FILE=makefile
CALL %TRESOS_DIR%/bin/make.exe -f makefile %1
GOTO end

:: toolchain parameter received in command line
:default_make_toolchain
set USER_MAKE_FILE=makefile
IF "%3"=="OS" SET USER_MAKE_FILE=makefile_os
ECHO %TRESOS_DIR%/bin/make.exe -f %USER_MAKE_FILE% %1=%2 %4 %5 %6 %7 %8 %9
CALL %TRESOS_DIR%/bin/make.exe -f %USER_MAKE_FILE% %1=%2 %4 %5 %6 %7 %8 %9
GOTO end

:default_make_os
set TOOL=%2 %3
IF "%2"=="TOOLCHAIN" set TOOL=%2=%3
ECHO %TRESOS_DIR%/bin/make.exe -f makefile_os %TOOL% %4 %5 %6 %7 %8 %9
CALL %TRESOS_DIR%/bin/make.exe -f makefile_os %TOOL% %4 %5 %6 %7 %8 %9
GOTO end

:: no user makefile is specified, take default
:default_make
set USER_MAKE_FILE=makefile
CALL %TRESOS_DIR%/bin/make.exe -f makefile %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO end

:end
:: End of make.bat
exit