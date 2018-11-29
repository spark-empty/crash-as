#===================================================================================================
#
#    @file        files.mak
#    @version     2.0.0
#
#    @brief       AUTOSAR - files to be build for the current application.
#    @details     List of files to be built for the Leds Sample Application.
#
#    Project      : AUTOSAR 3.0 MCAL
#    Patform      : PA
#    Peripheral   : 
#    Dependencies : Base Det Dem Port Dio Mcu SchM Wdg WdgIf CanIf LinIf EcuM
#
#    Autosar Version       : 1.9.0
#    Autosar Revision      : ASR_REL_1_9_REV_0003
#    Autosar Conf. Variant :
#    Software Version      : 2.0.0
#    Build Version         : MPC563xMxM_MCAL_2_0_0_RTM_ASR_REL_1_9_REV_0003_20110214
#
#    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
#    All Rights Reserved.
#
#    You can use this example for any purpose on any computer system with the following restrictions:
#    1. This example is provided "as is", without warranty.
#    2. You do not remove this copyright notice from this example or any direct derivation thereof.
#
#
#===================================================================================================
##===================================================================================================

################################################################################
# Sample application name
################################################################################
SAMPLE_APP_NAME := sample_app_mcal

#

################################################################################
# List of all source directories (test, dependency, and generated .c files)
################################################################################
#
# specify modules which will be compiled and linked
include Modules
# paths for building installed plugins
SRC_DIRS	+=	$(GENERATE_DIR)/src \
                $(foreach mod,$(MODULE_LIST),$(PLUGINS_DIR)/$(mod)_$(AR_PKG_NAME)/src)
#
################################################################################
# List of source files
################################################################################
SRC_FILES   +=  $(DEV_DIR)/src/main.c \
                $(DEV_DIR)/src/sample_app_mcal_data_definition.c \
                $(DEV_DIR)/src/sample_app_mcal_initialization_task.c \
                $(DEV_DIR)/src/sample_app_mcal_task_1.c \
                $(DEV_DIR)/src/sample_app_mcal_task_2.c \
                $(DEV_DIR)/src/sample_app_mcal_task_3.c \
                $(DEV_DIR)/src/sample_app_mcal_spi_task.c \
                $(DEV_DIR)/src/sample_app_mcal_fee_task.c \
                $(DEV_DIR)/src/sample_app_mcal_adc_task.c \
                $(DEV_DIR)/src/sample_app_mcal_icu_task.c \
                $(DEV_DIR)/src/sample_app_mcal_pwm_task.c \
                $(DEV_DIR)/src/sample_app_mcal_lin_task.c \
                $(DEV_DIR)/src/sample_app_mcal_can_task.c \
                $(DEV_DIR)/src/sample_app_mcal_uart_console.c \
        $(DEV_DIR)/src/Fls_sectors_unlock.c

ifeq ($(modulelist),os)
  ifeq ($(TOOLCHAIN),cw)
    ASM_FILES_TO_BUILD		+= $(DEV_DIR)/toolchains/CW_Startup_vle_os.s
  else
    SRC_FILES		+= $(DEV_DIR)/toolchains/Startup_vle_os.c
  endif
else
ifeq ($(TOOLCHAIN),cw)
    SRC_FILES		+= $(DEV_DIR)/toolchains/CW_Startup_vle.s
else
    SRC_FILES		+= $(DEV_DIR)/toolchains/Startup_vle.c
endif
endif


################################################################################
# List of all include directories (test, dependency, and generated .h files)
################################################################################
#
INCLUDE_DIRS+= 		$(GENERATE_DIR)/include \
                    $(DEV_DIR)/include \
                    $(foreach mod,$(MODULE_LIST),$(PLUGINS_DIR)/$(mod)_$(AR_PKG_NAME)/include) \
                    $(PLUGINS_DIR)/CanIf_$(AR_PKG_NAME)/include
#
################################################################################
# Path to the linker definition file
################################################################################
LINKER_DEFS_GHS_FLASH   :=    $(DEV_DIR)/toolchains/autosar_flash.ld
LINKER_DEFS_GHS_RAM     :=    $(DEV_DIR)/toolchains/autosar_intram.ld
LINKER_DEFS_CW_FLASH    :=    $(DEV_DIR)/toolchains/autosar_flash.lcf
LINKER_DEFS_CW_RAM      :=    $(DEV_DIR)/toolchains/autosar_intram.lcf
LINKER_DEFS_DIAB_FLASH  :=    $(DEV_DIR)/toolchains/autosar_flash.dld
LINKER_DEFS_DIAB_RAM    :=    $(DEV_DIR)/toolchains/autosar_intram.dld

printout := $(shell echo .set FLASH, 0 > compiler_used.s );
printout := $(shell echo .set INTRAM, 1 >> compiler_used.s );


ifeq ($(TOOLCHAIN),ghs)
    ifeq ($(findstring @LoadTo=ram, $(TEST_PARAMS)),)
        # if linking into flash
        LINKER_DEFS      :=    $(LINKER_DEFS_GHS_FLASH)
    else
        #if linking into ram
        LINKER_DEFS      :=    $(LINKER_DEFS_GHS_RAM)
    endif
    printout := $(shell echo .set COMPILER_USED, COMPILER_GHS >> compiler_used.s );
else
ifeq ($(TOOLCHAIN),cw)
    ifeq ($(findstring @LoadTo=ram, $(TEST_PARAMS)),)
        # if linking into flash
        LINKER_DEFS      :=    $(LINKER_DEFS_CW_FLASH)
    else
        #if linking into ram
        LINKER_DEFS      :=    $(LINKER_DEFS_CW_RAM)
    endif
    printout := $(shell echo .set COMPILER_USED, COMPILER_CW  >> compiler_used.s );
    printout := $(shell echo .set LINKED_TO, FLASH >> compiler_used.s );
else
    ifeq ($(findstring @LoadTo=ram, $(TEST_PARAMS)),)
        # if linking into flash
        LINKER_DEFS      :=    $(LINKER_DEFS_DIAB_FLASH)
    else
        #if linking into ram
        LINKER_DEFS      :=    $(LINKER_DEFS_DIAB_RAM)
    endif
    printout := $(shell echo .set COMPILER_USED, COMPILER_DIAB >> compiler_used.s );
endif
endif

################################################################################
# Additional test specific C compiler options
################################################################################
CCOPT	+=

#
################################################################################
# Additional test specific linker options
################################################################################
LDOPT			+=

################################################################################
# Custom libraries
################################################################################
LIBS			+=


#