#################################################################
# 
#   Freescale(TM) and the Freescale logo are trademarks of Freescale Semiconductor, Inc. 
#   All other product or service names are the property of their respective owners. 
#   (C) Freescale Semiconductor, Inc. 2008 - 2009
# 
#   You can use this example for any purpose on any computer system with the
#   following restrictions:
#
#   1. This example is provided "as is", without warranty.
#
#   2. You don't remove this copyright notice from this example or any direct derivation 
#     thereof.
#
#  Description:  makefile for performance ECC1 SC3 benchmark
#
#  Notes:  1. Usage
#             make [-s] <target> ... [<variable>=<value>] ...
#
#          2. Targets:
#             all  - build benchmark
#             clean - clear object and binary files for benchmark
#
#          3. Variables:
#             compiler - type of compiler: diabppc, ghsppc or cwppc
#                        (value by default see below)
#
#          4. Examples:
#             make                  - build benchmark
#             make compiler=diabppc - build benchmark with using DIAB compiler
#             make clean            - clear files for benchmark
#    
#################################################################

# select platform (only mpc56xxAM)
platform = mpc56xxAM

# Project name
projname = pecc1sc3

# Config source file
cfg=oil

#################################################################
# PROJECT_ROOT - path to the project root given by the project makefile
# SSC_ROOT     - path to the ssc root given by the base_makefile
#

SSC_ROOT          = ..\..\..\..
PROJECT_ROOT    = $(SSC_ROOT)\benchmark

#################################################################
# Output paths (relative to PROJECT_ROOT)

OUTPUT_PATH = bin
BIN_OUTPUT_PATH = $(OUTPUT_PATH)
OBJ_OUTPUT_PATH = obj

#################################################################
# Specific (need in freescale_os_rules.mak)

HWSPEC          = $(SSC_ROOT)\ssc\hwspec
PROJECT_SRC     = $(PROJECT_ROOT)\performance\common
LINKER_CMD_NAME = $(PROJECT_ROOT)\performance\common\memoryp
LINKER_CMD_OUTNAME = $(OBJ_OUTPUT_PATH)\memoryp
OS_OIL_NAME     = sources\$(projname).oil

CC_INCLUDE_PATH += $(PROJECT_SRC) $(OBJ_OUTPUT_PATH)

# Files to build

# OS configuration
CC_FILES_TO_BUILD += \
	$(OBJ_OUTPUT_PATH)\$(projname)_cfg.c \
	$(HWSPEC)\vector.c 

# Startup files for CW
STARTUP_FOR_CW = \
	$(HWSPEC)\__start.c \
	$(HWSPEC)\__ppc_eabi_init.c

# Startup assembler file for DIAB
ASM_STARTUP_FOR_DIAB = \
	$(HWSPEC)\crts.s

# User application
CC_FILES_TO_BUILD += \
	$(PROJECT_SRC)\pecc1.c \
	$(PROJECT_ROOT)\common\fmpll.c

PREPROCESSOR_DEFINES += osclassname apptypesh oscfgname ospropname
osclassname_KEY       =__CLASS_SC3
osclassname_VALUE     =1
apptypesh_KEY         =APPTYPESH
apptypesh_VALUE       ="\".\\..\\..\\..\\common\\performance.h\""
oscfgname_KEY         =OSCFGH
oscfgname_VALUE       ="<$(projname)_cfg.h>"
ospropname_KEY        =OSPROPH
ospropname_VALUE      ="\"osprop.h\""

#################################################################
include ../../../common.mak  # base makefile

