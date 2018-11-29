#===================================================================================================
#
#   @file        build_cfg.mak
#   @version     2.0.0
#
#   @brief       configuration file for WindRiver DIAB toolchain
#   @details     This file contains the compiler, assembler, linker options for WindRiver DIAB toolchain
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

VLETYPE := vle
PRJFLAG :=-DMPC$(DERIVATIVE)
DEBUG_FLAGS := -g -W:as:,-l


LIB_PATH		:= -Y P,$(call winpath, $(TOOLCHAIN_DIR))/PPCVLEEN/simple:$(call winpath, $(TOOLCHAIN_DIR))/PPCVLEEN:$(call winpath, $(TOOLCHAIN_DIR))/PPCVLEE/simple:$(call winpath, $(TOOLCHAIN_DIR))/PPCVLEE

CC 			:= $(call winpath, $(TOOLCHAIN_DIR)/WIN32/bin/dcc.exe)
LD 			:= $(call winpath, $(TOOLCHAIN_DIR)/WIN32/bin/dld.exe)
AS 			:= $(call winpath, $(TOOLCHAIN_DIR)/WIN32/bin/das.exe)
CCOPT     :=  -tPPCE200Z3VEG:simple $(PRJFLAG) $(DEBUG_FLAGS) -DDIAB -DAUTOSAR_OS_NOT_USED -DEU_DISABLE_ANSILIB_CALLS \
                -Xdialect-ansi  -XO -Xsize-opt -Xno-common  \
                 --ee1481  -Xsmall-data=0 \
                -Xforce-declarations -Xmacro-undefined-warn \
                -g -Xdebug-dwarf2 -Xdebug-local-all -Xdebug-local-cie -Xdebug-struct-all \
                -Xnested-interrupts -Wa,-Xisa-vle -W:as:,-l  -Xforce-prototypes -Xalign-functions=4 \
               -Xlint -ei1604 -Xaddr-sconst=0x11  -Xaddr-sdata=0x11                   


               # -Xdialect-ansi  -XO -Xsize-opt -Xno-common  \
               

LDOPT 			:= -tPPCE200Z3VEG:simple -Xelf -m6 -Xlibc-old -lc $(LIB_PATH)
#LDOPT 			:= -tPPCE200Z3VEG:simple -Xelf -m6 -li -lc $(LIB_PATH)
ASOPT 			:= -tPPCE200Z3VEG:simple -g -Xisa-vle -Xasm-debug-on -Xdebug-dwarf2

ifeq ($(findstring @LoadTo=ram, $(TEST_PARAMS)),)
	# if compiling/linking into flash
else
	#if compiling/linking into ram
	ASOPT       := $(ASOPT) -DSINTRAM
	CCOPT       := $(CCOPT) -DSINTRAM
endif

ifeq ($(AUX_BUFFER_APP),ON)
	CCOPT       := $(CCOPT) -DENABLE_TIMERS
endif


# Setup system libs, inlude dirs, and sourceinclude files
LIBS			:=
#INCLUDE_DIRS		 =
#SRC_FILES		 =
# Extention of the linked executable file
EXE_EXT 		:= elf

# Compiling and Linking macros
COMPILE_C_FILE = $(CC) $(CCOPT) -DFILE_BASENAME=$(basename $(notdir $<)) -c $(call winpath, $<) $(addprefix -I, $(INCLUDE_DIRS)) -o $(call winpath, $(OUT_DIR)/$@)
PREPROCESS_C_FILE = $(CC) $(CCOPT)  -DENABLE_DUMMY_SUITES -DPREPROCESS_ONLY_TEST -E $(call winpath, $<) $(addprefix -I, $(INCLUDE_DIRS)) -@O=$(call winpath, $@)
COMPILE_S_FILE = $(AS) $(ASOPT)  -o $(call winpath, $(OUT_DIR)/$@) $(call winpath, $<)
LINK_O_FILES = $(LD)  $(LDOPT) $(foreach LINKER_DEF, $(LINKER_DEFS),$(call winpath, $(LINKER_DEF))) \
$(addprefix $(call winpath, $(OUT_DIR)/), $(OUT_FILES)) $(addprefix   , $(call winpath, $(LIBS)))  \
-o $(call winpath, $@) -@O=$(basename $(call winpath, $@)).map

COMPILER_VERSION_CMD = $(CC) -V 2>&1 | grep $(COMPILER_REFERENCE_VERSION)
COMPILER_REFERENCE_VERSION := "Build label: DIAB_5_8_0_0-2_wind00198363_20100511_123238"

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
