#################################################################
# 
#   Freescale(TM) and the Freescale logo are trademarks of Freescale Semiconductor, Inc. 
#   All other product or service names are the property of their respective owners. 
#   (C) Freescale Semiconductor, Inc. 2009-2010
# 
#   You can use this example for any purpose on any computer system with the
#   following restrictions:
#
#   1. This example is provided "as is", without warranty.
#
#   2. You don't remove this copyright notice from this example or any direct derivation 
#     thereof.
#
# Description:  common makefile for AUTOSAR samples
#
#################################################################

# Cygwin path
CYGWINDIR   = 

# Cygwin utilities
CYGWIN_DIR  = $(call remove_slashes,$(CYGWINDIR))
RM          = $(CYGWIN_DIR)/rm.exe
MKDIR       = $(CYGWIN_DIR)/mkdir.exe
CAT         = $(CYGWIN_DIR)/cat.exe
ECHO        = $(CYGWIN_DIR)/echo.exe
COPY        = $(CYGWIN_DIR)/cp.exe
TOUCH       = $(CYGWIN_DIR)/touch.exe

# Tresos path
TRESOS_BASE =C:\EB\tresos
TRESOSBASE  = $(call remove_slashes,$(TRESOS_BASE))

# Compiler by default
ifeq ($(compiler),)
compiler=ghsppc
endif

# Path to compiler directory
ifeq ($(compiler),cwppc)
CWDIR       = C:\Program Files (x86)\Freescale\CW for MPC55xx and MPC56xx 2.10
endif
ifeq ($(compiler),diabppc)
DIABDIR     = 
endif
ifeq ($(compiler),ghsppc)
GHSDIR       = 
endif

# Check of compiler type
ifneq ($(compiler),cwppc)
ifneq ($(compiler),diabppc)
ifneq ($(compiler),ghsppc)
$(error Undefined compiler type: '$(compiler)', use cwppc or ghsppc or diabppc.)
endif
endif
endif

# MCU type
ifeq ($(mcu),)
ifeq ($(sc),1)
# mcu type by default
mcu=5634M
endif
ifeq ($(sc),2)
mcu=5634M
endif
ifeq ($(sc),3)
mcu=5644A
endif
ifeq ($(sc),4)
mcu=5644A
endif
endif

# Check of mcu type
ifneq ($(mcu),5634M)
ifneq ($(mcu),5644A)
ifneq ($(mcu),5674F)
$(error Undefined mcu type: '$(mcu)', expected one of following: 5634M, 5644A or 5674F)
endif
endif
endif

# Check type of derivative
ifeq ($(mcu),5634M)
ifeq ($(sc),3)
$(error MPC5634M do not have MPU)
endif
endif

ifeq ($(mcu),5634M)
ifeq ($(sc),4)
$(error MPC5634M do not have MPU)
endif
endif

register_define = $(eval $(1)_KEY =$(1));$(eval $(1)_VALUE=$($(1))));$(eval PREPROCESSOR_DEFINES += $(1)))
remove_slashes = $(subst \,/,$(1))
to_dslashes = $(subst \,\\,$(1))

empty       =
space       = $(empty) $(empty)

remove_spaces = $(subst $(space),\$(space),$(1))

$(foreach bsw,$(modulelist),\
$(eval bsw_name=$(call remove_slashes,$($(bsw)_dir)))\
$(eval $(bsw)_cfg_dir?=cfgno)\
$(eval PREPROCESSOR_DEFINES += $(bsw) $(bsw_name) $(bsw)_name_string $(bsw)_cfg_id)\
$(eval $(bsw)_KEY=$(bsw)_integrated)\
$(eval $(bsw)_VALUE=1)\
$(eval $(bsw)_name_string_KEY=$(bsw)_name_string)\
$(eval $(bsw)_name_string_VALUE=$(bsw_name)_string)\
$(eval $(bsw)_cfg_id_KEY=$(bsw)_cfg_id)\
$(eval $(bsw)_cfg_id_VALUE=$(call remove_slashes,$($(bsw)_cfg_dir)_id))\
$(eval $(bsw_name)_KEY=$(bsw_name))\
$(eval $(bsw_name)_VALUE=1))

ifeq ($(debug),yes)
cmm_file = $(call remove_slashes,$(BIN_OUTPUT_PATH)\$(projname).cmm)
endif
obj_output_path = $(call remove_slashes,$(OBJ_OUTPUT_PATH))
bin_output_path = $(call remove_slashes,$(BIN_OUTPUT_PATH))

# set final target
.PHONY: all 
all: $(BIN_OUTPUT_PATH)\$(projname).elf

ifeq ($(platform),mpc56xxAM)
PLATFORM_DEFINE=_MPC56xxAM_
else
$(error What platform?)
endif

$(call register_define,$(PLATFORM_DEFINE))

mak_path=ssc\mak
include $(foreach module, $(modulelist), $(SSC_ROOT)\$($(module)_dir)\$(mak_path)\$(module)_defs.mak)
include $(foreach module, $(modulelist), $(SSC_ROOT)\$($(module)_dir)\$(mak_path)\$(module)_rules.mak)

OBJ_FILE_SUFFIX = o
LIB_FILE_SUFFIX = lib

.SUFFIXES:            # Delete the default suffixes
.SUFFIXES: .c .h .$(OBJ_FILE_SUFFIX) .$(LIB_FILE_SUFFIX)

ifeq ($(compiler),cwppc)
#\/---------- CODE WARRIOR ------------------\/
# CodeWarrior compiler root directory
CW_DIR      = $(call remove_spaces,$(call remove_slashes,$(CWDIR)))

# Compiler paths
cbin        = $(CW_DIR)/PowerPC_EABI_Tools/Command_Line_Tools
cinc        = $(CW_DIR)/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Include
clib        = $(CW_DIR)/PowerPC_EABI_Support/Runtime/Lib
clibinc     = $(CW_DIR)/PowerPC_EABI_Support/Runtime/Include
ceabinc     = $(CW_DIR)/PowerPC_EABI_Support/MSL/MSL_C/PPC_EABI/Include
ceablib     = $(CW_DIR)/PowerPC_EABI_Support/MSL/MSL_C/PPC_EABI/Lib

# Executables
CC          = $(cbin)/mwcceppc
CP          = $(cbin)/mwcceppc
AS          = $(cbin)/mwasmeppc
LI          = $(cbin)/mwldeppc

# Compilers' options
ccopt       = -c -msgstyle gcc -proc Zen -ansi off -Cpp_exceptions off -fp none \
              -g -opt all,nopeep -sdata2 0 -sdata 0 -MMD -gccdep -r \
              -nostdinc -nosyspath  -vle -ppc_asm_to_vle -sym dwarf-2,full -func_align 4 \
              -pragma "read_only_switch_tables on" -w undefmacro 
cpopt       = -nostdinc -nosyspath -DOSCWPPC -I$(cinc) -I$(clib) -I$(clibinc) -I$(ceabinc)
ifeq ($(flashstart),1)
cpopt += -DFLASH_START
endif
asopt       = -msgstyle gcc -proc Zen  -DOSPROPH="\"$(OS_PROPHEADER)\"" -MMD -gccdep -vle -sym dwarf-2,full
LIBRARIES_LINK_ONLY += $(clib)/Runtime.PPCEABI.V.a $(ceablib)/MSL_C.PPCEABI.bare.V.a
ldopt       = -msgstyle gcc -nostdlib -fp none -g -sym dwarf-2,full -map -lcf $(LINKER_CMD_OUTFILE) $(FILES_TO_LINK)

#/\---------- CODE WARRIOR ------------------/\

endif  # $(compiler) == cwppc

ifeq ($(compiler),diabppc)

#\/---------- DIAB ------------------\/

# DIAB compiler root directory
DIAB_DIR    = $(call remove_spaces,$(call remove_slashes,$(DIABDIR)))

# Compiler paths
cbin        = $(DIAB_DIR)/win32/bin
cinc        = $(DIAB_DIR)/include
clib        = $(DIAB_DIR)/PPCVLEE

# Executables
CC          = $(cbin)/dcc
CP          = $(cbin)/dcc
AS          = $(cbin)/das
LI          = $(cbin)/dld

# Compilers' options
ifeq ($(mcu),5634M)
ctrg = PPCE200Z3VEN:simple
endif
ifeq ($(mcu),5644A)
ctrg = PPCE200Z4VEN:simple
endif
ifeq ($(mcu),5674F)
ctrg = PPCE200Z7VEG:simple
endif

ccopt       =  -t$(ctrg) -c -DOSDIABPPC -Xdialect-ansi -Xmake-dependency=4 -g -XO       \
               -Wa,-Xisa-vle -Xdebug-dwarf2 -Xdebug-inline-on -Xdebug-local-all -Xdebug-struct-all \
               -Xdebug-local-cie -Xsmall-data=0 -Xnested-interrupts \
               -Xforce-declarations -ee1481 -Xsemi-is-newline -Xmacro-undefined-warn

cpopt       = -I$(cinc) -DOSDIABPPC
asopt       = -t$(ctrg) -g -Xisa-vle -Xasm-debug-on
ifeq  ($(mcu),5674F)
ldopt       = -tPPCE200Z7VEN:simple -lc -li -m6 -Xelf $(call remove_slashes,$(FILES_TO_LINK)) \
              $(call remove_slashes,$(LINKER_CMD_OUTFILE)) > $(bin_output_path)/$(projname).map  
else
ldopt       = -t$(ctrg) -lc -li -m6 -Xelf $(call remove_slashes,$(FILES_TO_LINK)) \
              $(call remove_slashes,$(LINKER_CMD_OUTFILE)) > $(bin_output_path)/$(projname).map  
endif

ifeq ($(flashstart),1)
asopt +=-D FLASH_START
cpopt +=-D FLASH_START
endif

#/\---------- DIAB ------------------/\

endif  # $(compiler) == diabppc

ifeq ($(compiler),ghsppc)

#\/---------- GREEN HILLS ------------------\/

# GREEN HILLS compiler root directory
GHS_DIR     = $(call remove_spaces,$(call remove_slashes,$(GHSDIR)))

ifeq ($(mcu),5634M)
proc        = ppc563xm
endif
ifeq ($(mcu),5644A)
proc        = ppc5646a
endif
ifeq ($(mcu),5674F)
proc        = ppc5674m
endif

# Compiler paths
cbin        = $(GHS_DIR)
cinc        = $(GHS_DIR)/include
clib        = $(GHS_DIR)/lib/ppc5514
clibinc     = $(GHS_DIR)/include
ceabinc     = $(GHS_DIR)/include
ceablib     = $(GHS_DIR)/lib/ppc5514

# Executables
CC          = $(cbin)/ccppc
CP          = $(cbin)/ccppc
AS          = $(cbin)/asppc
LI          = $(cbin)/elxr

# Compilers' options
ccopt       = -c -cpu=$(proc) -noSPE --no_exceptions -fnone -vle -g -dual_debug -DOSGHSPPC -O2 -sda=0 --diag_error 223 -MD
cpopt       = -I$(cinc) -I$(clib) -I$(clibinc) -I$(ceabinc) -DOSGHSPPC

ifeq ($(flashstart),1)
cpopt += -DFLASH_START
endif

asopt       = -cpu=$(proc) -DOSPROPH="\"$(OS_PROPHEADER)\"" -g -list
ldopt       = -nocpp -uvfd -Mn -delete -ignore_debug_references -keepmap -T $(LINKER_CMD_OUTFILE) \
              -L $(clib) -L $(ceablib) $(clib)\crt0.o -lsys -lstartup -larch -lansi $(FILES_TO_LINK) 

#/\---------- GREEN HILLS ------------------/\

endif  # $(compiler) == ghsppc

# variables check
ifeq ($(CYGWINDIR),) 
$(error Variable CYGWINDIR must be set)
endif

ifeq ($(cfg),xdm)
ifeq ($(TRESOS_BASE),) 
$(error Variable TRESOS_BASE must be set)
endif
endif

ifeq ($(compiler),cwppc)
ifeq ($(CWDIR),) 
$(error Variable CWDIR must be set)
endif
endif

ifeq ($(compiler),diabppc)
ifeq ($(DIABDIR),) 
$(error Variable DIABDIR must be set)
endif
endif

ifeq ($(compiler),ghsppc)
ifeq ($(GHSDIR),) 
$(error Variable GHSDIR must be set)
endif
endif

cpopt      += $(addprefix -I,$(call remove_slashes,$(CC_INCLUDE_PATH)))
cpopt      += $(foreach define,$(PREPROCESSOR_DEFINES),-D$($(define)_KEY)=$($(define)_VALUE))

OBJ_OUTPUT_PATH1=$(OBJ_OUTPUT_PATH)

# C rule
define generate_c_rule
$(addprefix $(OBJ_OUTPUT_PATH1)\,$(addsuffix .$(OBJ_FILE_SUFFIX),$(basename $(notdir $(1))))): $(1)
	@$(ECHO) Processing $$<	
	$(CC) $(ccopt) $(cpopt) $$(subst \,\\,$$<) -o $$(subst \,\\,$$@)
	@$(ECHO) DONE	
endef

# Asm rule
define generate_asm_rule
$(addprefix $(OBJ_OUTPUT_PATH)\,$(addsuffix .$(OBJ_FILE_SUFFIX),$(basename $(notdir $(1))))): $(1)
	@$(ECHO) Processing $(1)
	$(AS) $(asopt) -o $$(subst \,\\,$$@) $$(subst \,\\,$$<)
	@$(ECHO) DONE	
endef

XX_FILES_TO_BUILD = $(CC_FILES_TO_BUILD) $(S_FILES_TO_BUILD) $(ASM_FILES_TO_BUILD)
XX_OBJ_FILES = $(addprefix $(OBJ_OUTPUT_PATH1)\,$(addsuffix .$(OBJ_FILE_SUFFIX),$(basename $(notdir $(XX_FILES_TO_BUILD)))))
FILES_TO_LINK = $(XX_OBJ_FILES) $(LIBRARIES_LINK_ONLY) $(OBJECTS_LINK_ONLY)

# Dependencies
-include $(XX_OBJ_FILES:.o=.d)

# Generation of C and assempler rules
$(foreach file,$(CC_FILES_TO_BUILD),$(eval $(call generate_c_rule,$(file))))
$(foreach file,$(ASM_FILES_TO_BUILD),$(eval $(call generate_asm_rule,$(file))))


# Rule for linking
$(BIN_OUTPUT_PATH)\$(projname).elf: $(FILES_TO_LINK) $(cmm_file) $(LINKER_CMD_OUTFILE)
	@$(ECHO) Linking $@
	@$(MKDIR) -p $(bin_output_path)
	$(LI) $(ldopt)  -o $(subst \,\\,$@)

ifeq ($(debug),yes)
$(cmm_file):
	@$(ECHO) Make CMM file $(cmm_file)
	@$(ECHO) DO ..\\..\\..\\56xxAM.cmm '"'$(mcu)'"'>> $(cmm_file)	
ifeq ($(flashstart),1)
	@$(ECHO) DO ..\\..\\..\\sc1\\flash.cmm $(projname) '"'$(mcu)'"'>> $(cmm_file)
else	 
	@$(ECHO) DATA.LOAD.ELF $(projname).elf /GLOBTYPES /GT /MW /BUGFIX >> $(cmm_file)
endif
	@$(ECHO) DATA.LIST >> $(cmm_file)
	@$(ECHO) SYMBOL.BROWSE.FUNCTION >> $(cmm_file)
endif

# Target for show internal options
showflags:
	@$(ECHO) COMPILEROPTIONS = $(ccopt) $(cpopt)
	@$(ECHO) LINKEROPTIONS = $(ldopt)
	@$(ECHO) PREPROCESSOR_DEFINES = $(PREPROCESSOR_DEFINES)
	@$(ECHO) CC_FILES_TO_BUILD = $(CC_FILES_TO_BUILD)
	@$(ECHO) ASM_FILES_TO_BUILD = $(ASM_FILES_TO_BUILD)
	@$(ECHO) CC_INCLUDE_PATH = $(CC_INCLUDE_PATH)

clean:
	@$(ECHO) Clean...
	@$(RM) -fR $(OUTPUT_PATH)

clean_keep_elf:
	@$(ECHO) Clean with keep elf ...
	@$(RM) -fR $(OBJ_OUTPUT_PATH)
