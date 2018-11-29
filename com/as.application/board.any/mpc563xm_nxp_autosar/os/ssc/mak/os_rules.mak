################################################################
#
#  Freescale(TM) and the Freescale logo are trademarks of Freescale Semiconductor, Inc. 
#  All other product or service names are the property of their respective owners. 
#  (C) Freescale Semiconductor, Inc. 2006-2010 
# 
#  1. This example is provided "as is", without warranty.
#
#  2. You don't remove this copyright notice from this example or any direct derivation 
#     thereof.
#
#  Description:  AUTOSAR OS rules makefile      
#
#  Notes:        
#
#################################################################

#################################################################
# REQUIRE:
# 
# PROJECT_ROOT - path to the project root given by the project makefile (in base_make)
# SSC_ROOT     - path to the ssc root given by the base_makefile (in base_make)
#
# OS_SRC_PATH, OS_INC_PATH, OS_HWSPEC_PATH (in os_defs.mak)
# OS_OIL_NAME  - full name of project specific configuration file with '.oil' extension  (in makefile of project)
#

#################################################################
# Specific

OS_PROPHEADER=$(OBJ_OUTPUT_PATH)\osprop.h
OS_ORTI_NAME=$(BIN_OUTPUT_PATH)\$(basename $(notdir $(OS_OIL_NAME))).ort


#################################################################
# REGISTRY
# LIBRARIES_TO_BUILD += 
# freescale_oslib_FILES = 

CC_FILES_TO_BUILD += \
	$(OS_SRC_PATH)\os.c \
	$(OS_SRC_PATH)\osset.c \
	$(OS_SRC_PATH)\ossch.c \
	$(OS_SRC_PATH)\ossct.c \
	$(OS_SRC_PATH)\ostsk.c \
	$(OS_SRC_PATH)\osalm.c \
	$(OS_SRC_PATH)\osctr.c \
	$(OS_SRC_PATH)\osres.c \
	$(OS_SRC_PATH)\osevt.c \
	$(OS_SRC_PATH)\osisr.c \
	$(OS_SRC_PATH)\osmem.c \
	$(OS_SRC_PATH)\ostp.c  \
	$(OS_SRC_PATH)\osmsg.c \
	$(OS_SRC_PATH)\ostrg.c

ifeq ($(compiler),cwppc)
LINKER_CMD_FILE  = $(LINKER_CMD_NAME).lcf
CC_FILES_TO_BUILD += $(STARTUP_FOR_CW)
LINKER_CMD_OUTFILE = $(LINKER_CMD_OUTNAME).lcf
endif

ifeq ($(compiler),diabppc)
LINKER_CMD_FILE  = $(LINKER_CMD_NAME).dld
ASM_FILES_TO_BUILD += $(ASM_STARTUP_FOR_DIAB)
LINKER_CMD_OUTFILE = $(LINKER_CMD_OUTNAME).dld
endif

ifeq ($(compiler),ghsppc)
LINKER_CMD_FILE  = $(LINKER_CMD_NAME).ld
LINKER_CMD_OUTFILE = $(LINKER_CMD_OUTNAME).ld
endif


# CPP_FILES_TO_BUILD +=
# ASM_FILES_TO_BUILD +=
#LIBRARIES_LINK_ONLY +=
# OBJECTS_LINK_ONLY +=
# DIRECTORIES_TO_CREATE += 

#MAKE_CLEAN_RULES +=
#MAKE_COMPILE_RULES +=
#MAKE_DEBUG_RULES +=
#MAKE_CONFIG_RULES +=
#MAKE_ADD_RULES +=

.PHONY: os_sysgen_rules
MAKE_GENERATE_RULES += os_sysgen_rules

ifeq ($(cfg),oil)
cfg_file=$(OS_OIL_NAME)
endif

ifeq ($(cfg),epc)
cfg_file=$(OS_OIL_NAME)
endif

ifeq ($(cfg),xdm)
cfg_file=$(OBJ_OUTPUT_PATH)\$(notdir $(basename $(OS_OIL_NAME))).epc
endif

$(OBJ_OUTPUT_PATH)\$(projname)_cfg.c: $(OS_OIL_NAME) $(LINKER_CMD_FILE)
	@echo Processing $<
	@$(MKDIR) -p $(obj_output_path) $(bin_output_path)

ifeq ($(cfg),xdm)
	$(TRESOSBASE)/bin/tresos_cmd.bat legacy convert "$(OS_OIL_NAME)@xdm" "$(cfg_file)@asc:3.0"
endif

ifeq ($(sc),1)
	$(OS_SG_PATH)\sg.exe -c$@ -h$*.h -o$(OS_ORTI_NAME) -i$(OS_SG_PATH) -p$(OS_PROPHEADER) $(cfg_file)
endif
ifeq ($(sc),2)
	$(OS_SG_PATH)\sg.exe -c$@ -h$*.h -o$(OS_ORTI_NAME) -i$(OS_SG_PATH) -p$(OS_PROPHEADER) $(cfg_file)
endif
ifeq ($(sc),3)
	$(OS_SG_PATH)\sg.exe -c$@ -h$*.h -o$(OS_ORTI_NAME) -i$(OS_SG_PATH) -p$(OS_PROPHEADER) -L$(LINKER_CMD_FILE) -M$(LINKER_CMD_OUTFILE)  $(cfg_file)
endif
ifeq ($(sc),4)
	$(OS_SG_PATH)\sg.exe -c$@ -h$*.h -o$(OS_ORTI_NAME) -i$(OS_SG_PATH) -p$(OS_PROPHEADER) -L$(LINKER_CMD_FILE) -M$(LINKER_CMD_OUTFILE) $(cfg_file)
endif
	@$(TOUCH) $@

os_sysgen_rules: $(OS_OIL_CFG_NAME).c
