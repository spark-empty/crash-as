#===================================================================================================
#
#    @file        Makefile
#    @version     2.0.0
#
#    @brief       AUTOSAR - Release Check Sample Application Makefile.
#    @details     File used to build the Release Check Sample Application.
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
# BEART configuration options
################################################################################
-include local_config.mak

################################################################################
# Setup default paths and settings if local_config.mak not defined
################################################################################

################################################################################
# Disable error logging by default
################################################################################
ifeq ($(strip $(BUILD_LOG)),)
BUILD_LOG = None
endif

################################################################################
# Path to the root directory of the project
################################################################################
ifeq ($(ROOT_DIR),)
ROOT_DIR :=  .
endif

################################################################################
# Path to the root directory of development structure
################################################################################
DEV_DIR := $(ROOT_DIR)

#
################################################################################
# Compiler used (default is GHS)
################################################################################
ifeq ($(TOOLCHAIN),)
# GHS used
TOOLCHAIN := ghs
endif

ifeq ($(TOOLCHAIN),ghs)
    ifeq ($(GHS_DIR),)
    GHS_DIR := C:/ghs/multi517
    $(shell echo Default GHS_DIR selected: $(GHS_DIR) 1>&2)
    endif
    TOOLCHAIN_DIR := $(GHS_DIR)
endif
ifeq ($(TOOLCHAIN),diab)
    ifeq ($(DIAB_DIR),)
    DIAB_DIR := C:/WindRiver/diab/5.6.1.0
    $(shell echo Default DIAB_DIR selected: $(DIAB_DIR) 1>&2)
    endif
    TOOLCHAIN_DIR := $(DIAB_DIR)
endif
ifeq ($(TOOLCHAIN),cw)
    ifeq ($(CW_DIR),)
    CW_DIR := C:/Progra~1/Freesc~1/CodeWa~1.3
    $(shell echo Default CW_DIR selected: $(CW_DIR) 1>&2)
    endif
    TOOLCHAIN_DIR := $(CW_DIR)
endif

$(shell echo Using $(TOOLCHAIN) toolchain: TOOLCHAIN_DIR= $(TOOLCHAIN_DIR) 1>&2)
################################################################################
# Setup output directory
################################################################################
BUILD_DIR := $(DEV_DIR)/bin

################################################################################
# Module version information (this numbering is module vendor specific, and it
# is recommended to follow these rules: update SW_VERSION_MAJOR in case of major
# change of module, update SW_VERSION_MINOR in case of minor change of module,
# update SW_VERSION_PATCH in case of bug-fix of module
################################################################################
SW_VERSION_MAJOR = 2
SW_VERSION_MINOR = 0
SW_VERSION_PATCH = 0
SW_VERSION_SUFFIX = RTM

################################################################################
# Tresos target ID (see the Encoding of Architecture and Derivative document for details)
# Target    Manufacturer    Architecture ID ("T")
#   PA      Freescale/STM       2
################################################################################
TRESOS_TARGET_ID=2

################################################################################
# Tresos derivative ID (see the Encoding of Architecture and Derivative document for details)
#   Derivative ID ("D")
#       13          14          11           15          17          19            18         20
#    XPC560XB    XPC563XM    XPC560XP     XPC560XS     XPC56XXL    MPC567XF    MPC5664A    MPC5668X
#    (Bolero)    (Monaco)    (Pictus)    (Spectrum)   (Leopard)    (Mamba)     (Andora)    (Fado)
################################################################################
TRESOS_DERIVATIVE_ID=14

################################################################################
# AUTOSAR package name (i.e. tresos plugin name: TS_T11D3M2I0R0, etc.)
# - use the "M" section for coding major and minor version number
# - use "I" section for coding the patch number, this can contain 1 or more digits.
# - major version number will be left out, if it is "0", in this case the "M" section contains 1 digit only, otherwise it contains 2 digits
################################################################################
ifeq ($(SW_VERSION_MAJOR),0)
    AR_PKG_NAME = TS_T$(TRESOS_TARGET_ID)D$(TRESOS_DERIVATIVE_ID)M$(SW_VERSION_MINOR)I$(SW_VERSION_PATCH)R0
else
    AR_PKG_NAME = TS_T$(TRESOS_TARGET_ID)D$(TRESOS_DERIVATIVE_ID)M$(SW_VERSION_MAJOR)$(SW_VERSION_MINOR)I$(SW_VERSION_PATCH)R0
endif

################################################################################
# AUTOSAR Version Number
################################################################################
AR_VSMD_TYPE=asc:3.0

################################################################################
# Platform, derivative, package
################################################################################
ifeq ($(DERIVATIVE),)
DERIVATIVE := 5634M
endif
PLATFORM := 563xM
$(shell echo Running for $(DERIVATIVE) derivative, on $(PLATFORM) platform 1>&2)

################################################################################
# MCU family name (S12X, MPC etc.)
################################################################################
MCU_FAMILY = PA

################################################################################
# MCU derivative name (s12xep100, 5516 etc.) Used in pathname to product specific files.
################################################################################
MCU_DERIVATIVE = MPC5634M
BUILD_SOURCE=Plugin
TOOLCHAIN_VERSION=OFF

#