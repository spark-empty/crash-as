#===================================================================================================
#
#   @file        build_cfg.mak
#   @version     2.0.0
#
#   @brief       configuration file for CodeWarrior toolchain
#   @details     This file contains the compiler, assembler, linker options for CodeWarrior toolchain
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

VLETYPE := -vle
PRJFLAG :=-DMPC$(DERIVATIVE)
PPCLIB := $(TOOLCHAIN_DIR)/PowerPC_EABI_Support/Runtime/Lib/Runtime.PPCEABI.VS.UC.a
MSLLIB := $(TOOLCHAIN_DIR)/PowerPC_EABI_Support/MSL/MSL_C/PPC_EABI/Lib/MSL_C.PPCEABI.bare.VS.UC.a

#-char unsigned
CC 			:= $(call winpath, $(TOOLCHAIN_DIR)/PowerPC_EABI_Tools/Command_Line_Tools/mwcceppc.exe)
LD 			:= $(call winpath, $(TOOLCHAIN_DIR)/PowerPC_EABI_Tools/Command_Line_Tools/mwldeppc.exe)
AS 			:= $(call winpath, $(TOOLCHAIN_DIR)/PowerPC_EABI_Tools/Command_Line_Tools/mwasmeppc.exe)
CCOPT 		:=  -proc Zen $(PRJFLAG) -DMWERKS -nosyspath -common off -w on \
                 -char unsigned -sdatathreshold 0 -sdata2threshold 0 -Cpp_exceptions off -use_lmw_stmw on \
                -r -DAUTOSAR_OS_NOT_USED -DMCAL_VERSION_CHECK -sym dwarf-2,full $(VLETYPE) -gdwarf-2 \
                -DEU_DISABLE_ANSILIB_CALLS -lang c -fp none -opt all -func_align 4 -w undefmacro \
                -ir $(call winpath, $(TOOLCHAIN_DIR))/PowerPC_EABI_Support/MSL/MSL_C \
                -ppc_asm_to_vle

LDOPT 		:= -proc Zen -code_merging all -far_near_addressing -vle_enhance_merging \
               -sym dwarf-2,full -listdwarf  -char unsigned
			 
ASOPT 		:= -c -proc Zen $(PRJFLAG) -DMWERKS $(VLETYPE) -sym dwarf-2,full -gdwarf-2

ifeq ($(findstring @LoadTo=ram, $(TEST_PARAMS)),)
    # if linking into flash
	LDOPT       := $(LDOPT) -romaddr 0x00000000 -rambuffer 0x00000000  
else
    #if linking into ram
    ASOPT       := $(ASOPT) -DSINTRAM    
endif

ifeq ($(AUX_BUFFER_APP),ON)
	CCOPT       := $(CCOPT) -DENABLE_TIMERS 
endif

# Setup system libs, inlude dirs, and sourceinclude files
LIBS			:= $(PPCLIB) $(MSLLIB) 

#INCLUDE_DIRS		 =
#SRC_FILES		 =
# Extention of the linked executable file
EXE_EXT 		:= elf

# Compiling and Linking macros
COMPILE_C_FILE = $(CC) $(CCOPT) -DFILE_BASENAME=$(basename $(notdir $<)) -c $(call winpath, $<) $(addprefix -I, $(INCLUDE_DIRS)) -o $(call winpath, $(OUT_DIR)/$@)
PREPROCESS_C_FILE = $(CC) $(CCOPT)  -DENABLE_DUMMY_SUITES -DPREPROCESS_ONLY_TEST -E $(call winpath, $<) $(addprefix -I, $(INCLUDE_DIRS)) -o $(call winpath, $@)
COMPILE_S_FILE = $(AS) $(ASOPT) $(call winpath, $<) -o $(call winpath, $(OUT_DIR)/$@)
LINK_O_FILES = $(LD) $(LDOPT) $(foreach LINKER_DEF, $(LINKER_DEFS),-lcf $(call winpath, $(LINKER_DEF))) $(addprefix $(call winpath, $(OUT_DIR)/), $(OUT_FILES)) \
$(call winpath, $(LIBS)) -o $(call winpath, $@) -map $(basename $(call winpath, $@)).map

COMPILER_VERSION_CMD = $(CC) -version 2>&1 | grep $(COMPILER_REFERENCE_VERSION)
COMPILER_REFERENCE_VERSION := "Version 4.3 build 182"

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
