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
#  Description:  makefile for SC2 sample
#
#  Notes:  1. Usage
#             make [-s] <target> ... [<variable>=<value>] ...
#
#          2. Targets:
#             all  - build SC2 sample (target by default)
#             clean - clear object and binary files for SC2 sample
#             clean_keep_elf - clear only object files for SC2 sample
#             showflags - show options, list of source files etc.
#
#          3. Variables:
#             compiler - type of compiler:
#                        ghsppc          - GreenHills compiler  
#                        diabppc         - WindRiver compiler
#                        cwppc           - CodeWarrior compiler 
#                        (value by default see below)
#             mcu      - type of derivative: 
#                        5634M (by default) 
#                        5644A
#                        5674F
#             debug    - debugging support: yes or no
#                        debug=yes - generate a script for lauterbach debugger
#                                    in the directory output/bin
#                        (value by default: no)
#             cfg      - config file source: OIL, EPC or XDM  configutation file
#                        (value by default: OIL)
#
#          4. Some useful options:
#             -s    - silent mode (don't echo commands)
#
#          5. Examples:
#             make                        - build SC2 sample
#             make cfg=xdm                - build SC2 sample with XDM
#                                           configuration file
#             make compiler=diabppc       - build SC2 sample with 
#                                           using WindRiver compiler
#             make debug=yes mcu=5644A    - build sample with default (GHS) compiler
#                                           with generation of Lauterbach command file
#             make clean                  - clear files for SC2 sample
#    
#################################################################

# select platform (only mpc56xxAM)
platform = mpc56xxAM

# Config source file
ifeq ($(cfg),)
cfg=oil
endif

# Project name
projname = sample2

# Explicitly set Scalability Class
sc = 2

#################################################################
# define the list of modules to be integrated
# define the directory where the module is located in the
# next section (bsw_dir) and the configuration (if available)
# bsw_cfg_dir. bsw_cfg_dir must be placed in bsw_dir.

modulelist      = os
os_dir          = os_freescale_mpc56xxAM
os_cfg_dir      =

#################################################################
# PROJECT_ROOT - path to the project root given by the project makefile
# SSC_ROOT     - path to the ssc root given by the base_makefile
# XDM_SAMPLE_PATH - path to the xdm sample

SSC_ROOT        = C:\Freescale\AUTOSAR
PROJECT_ROOT   := $(dir $(shell cygpath -a -w makefile))
XDM_SAMPLE_PATH  = $(SSC_ROOT)\$(os_dir)\os_ts\eclipse\workspace\os_sample_sc2\config

#################################################################
# Output paths (relative to PROJECT_ROOT)

OUTPUT_PATH = $(PROJECT_ROOT)output
OBJ_OUTPUT_PATH = $(OUTPUT_PATH)\obj
BIN_OUTPUT_PATH = $(OUTPUT_PATH)\bin

#################################################################
# Specific (need in freescale_os_rules.mak)

HWSPEC          = $(PROJECT_ROOT)..\hwspec
PROJECT_SRC     = $(PROJECT_ROOT)src
ifeq ($(cfg),oil)
OS_OIL_NAME     = $(PROJECT_SRC)\$(projname).oil
endif
ifeq ($(cfg),epc)
OS_OIL_NAME     = $(PROJECT_SRC)\$(projname).epc
endif
ifeq ($(cfg),xdm)
OS_OIL_NAME     = $(XDM_SAMPLE_PATH)\OS.xdm
endif

LINKER_CMD_NAME = $(PROJECT_ROOT)lcf\$(projname)
LINKER_CMD_OUTNAME = $(LINKER_CMD_NAME)

CC_INCLUDE_PATH += $(PROJECT_SRC) $(OBJ_OUTPUT_PATH)

# Files to build

# OS configuration
CC_FILES_TO_BUILD += \
	$(OBJ_OUTPUT_PATH)\$(projname)_cfg.c \
	$(HWSPEC)\vector.c \
	$(HWSPEC)\flashrchw.c  

# Startup files for CW
STARTUP_FOR_CW = \
	$(HWSPEC)\__start.c \
	$(HWSPEC)\__ppc_eabi_init.c

# Startup assembler file for DIAB
ASM_STARTUP_FOR_DIAB = \
	$(HWSPEC)\crts.s

# User application
CC_FILES_TO_BUILD += \
	$(PROJECT_SRC)\samplets2.c \
	$(PROJECT_SRC)\samplerv2.c


PREPROCESSOR_DEFINES += apptypesh oscfgname ospropname
apptypesh_KEY         =APPTYPESH
apptypesh_VALUE       ="<sample.h>"
oscfgname_KEY         =OSCFGH
oscfgname_VALUE       ="<$(projname)_cfg.h>"
ospropname_KEY        =OSPROPH
ospropname_VALUE      ="\"$(call remove_slashes,$(OS_PROPHEADER))\""

#################################################################
include ../common.mak  # base makefile
