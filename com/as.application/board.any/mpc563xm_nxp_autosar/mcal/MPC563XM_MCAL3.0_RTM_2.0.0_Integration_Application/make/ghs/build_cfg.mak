#===================================================================================================
#
#   @file        build_cfg.mak
#   @version     2.0.0
#
#   @brief       configuration file for GreenHills Multi toolchain
#   @details     This file contains the compiler, assembler, linker options for GreenHills Multi toolchain
#   
#   Project      : AUTOSAR 3.0 MCAL
#   Platform     : PA
#   Peripheral   : 
#   Dependencies : Base Det Dem Port Dio Mcu SchM Wdg WdgIf CanIf LinIf EcuM
#   
#   Autosar Version       : 1.9.0
#   Autosar Revision      : ASR_REL_1_9_REV_0003
#   Autosar Conf. Variant : 
#   Software Version      : 2.0.0
#   Build Version         : MPC563xMxM_MCAL_2_0_0_RTM_ASR_REL_1_9_REV_0003_20110214
#
#   (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
#   All Rights Reserved.
#
#===================================================================================================
##===================================================================================================
# Setup buid tools
# MISRA-C 2004 Rule checking.
VLETYPE = vle
PRJFLAG :=-DMPC$(DERIVATIVE)
MISRA_ALL = --misra_2004=all
# Allowed exceptions are to be documented in the source code. Exceptions are documented in Global_MSG_C-Coding_Guidelines.doc Appendix A
MISRA_ALLOWED = --misra_2004=all,-5.7,-11.3,-11.4,-14.7,-17.1,-17.2,-17.4,-20.3,-20.4
#MISRA = $(MISRA_ALLOWED)

CC 			:= $(call winpath, $(TOOLCHAIN_DIR)/ccppc.exe)
LD 			:= $(call winpath, $(TOOLCHAIN_DIR)/ccppc.exe)
AS 			:= $(call winpath, $(TOOLCHAIN_DIR)/asppc.exe)

CCOPT 		:= -cpu=ppc563xm  $(MISRA) $(PRJFLAG) -DGHS --incorrect_pragma_warnings \
               -$(VLETYPE) -DAUTOSAR_OS_NOT_USED -DMCAL_VERSION_CHECK -DEU_DISABLE_ANSILIB_CALLS -preprocess_assembly_files \
               --no_exceptions -dual_debug --prototype_errors -Wundef -ansi -Ospace -G -noslashcomment -Odebug\
               -Wimplicit-int -Wshadow -Wtrigraphs -noSPE -nostartfile -sda=0 --no_commons 



LDOPT 		:= -cpu=ppc563xm -$(VLETYPE) -nostartfiles -linker_warnings
ASOPT 		:= -cpu=ppc563xm
ifeq ($(findstring @LoadTo=ram, $(TEST_PARAMS)),)
    # if compiling/linking into flash
else
    #if compiling/linking into ram
    ASOPT       := $(ASOPT) -DSINTRAM    
	CCOPT       := $(CCOPT) -DSINTRAM 
endif

ifeq ($(CCOV_ENABLE),ON)
    #if code coverage is needed
    CCOPT:= $(CCOPT) -DCCOV_ENABLE
endif

ifeq ($(AUX_BUFFER_APP),ON)
	CCOPT       := $(CCOPT) -DENABLE_TIMERS 
endif

# Setup system libs, inlude dirs, and sourceinclude files
LIBS			:= 
#INCLUDE_DIRS	= 
#SRC_FILES		= 
# Extention of the linked executable file
EXE_EXT := elf

# Compiling and Linking macros
COMPILE_C_FILE = $(CC) $(CCOPT) -DFILE_BASENAME=$(basename $(notdir $<)) -c $(call winpath, $<) $(addprefix -I, $(INCLUDE_DIRS)) -o $(call winpath, $(OUT_DIR)/$@)
PREPROCESS_C_FILE = $(CC) $(CCOPT)  -DENABLE_DUMMY_SUITES -DPREPROCESS_ONLY_TEST -E $(call winpath, $<) $(addprefix -I, $(INCLUDE_DIRS)) -o $(call winpath, $(OUT_DIR)/$(notdir $@))
COMPILE_S_FILE = $(AS) $(ASOPT) $(call winpath, $<) -o $(call winpath, $(OUT_DIR)/$@)
LINK_O_FILES = $(LD) $(LDOPT) $(foreach LINKER_DEF, $(LINKER_DEFS), $(call winpath, $(LINKER_DEF))) $(addprefix $(call winpath, $(OUT_DIR)/), $(OUT_FILES)) $(call winpath, $(LIBS)) -o $(call winpath, $@)

COMPILER_VERSION_CMD = $(CC) -V a.c 2>&1 | grep $(COMPILER_REFERENCE_VERSION)
COMPILER_REFERENCE_VERSION := "C-POWERPC 5.1.7 RELEASE VERSION Copyright 1983-2005 Green Hills Software, Inc. All rights reserved."

#check toolchain version
ifeq ($(TOOLCHAIN_VERSION),)
    #export to environment - so that is checked only once during current make run
    export TOOLCHAIN_VERSION:= $(strip $(shell $(COMPILER_VERSION_CMD)))
endif
ifeq ($(strip $(TOOLCHAIN_VERSION)),)
    $(shell echo "**************************************************************************************" 1>&2) 
    $(shell echo Bad Compiler version 1>&2) 
    $(shell echo For $(PLATFORM)-$(DERIVATIVE) you must use: $(COMPILER_REFERENCE_VERSION) 1>&2) 
    $(shell echo "**************************************************************************************" 1>&2) 
    $(error Bad Compiler version)
endif
