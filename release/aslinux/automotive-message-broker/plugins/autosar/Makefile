#/**
# * AS - the open source Automotive Software on https://github.com/parai
# *
# * Copyright (C) 2015  AS <parai@foxmail.com>
# *
# * This source code is free software; you can redistribute it and/or modify it
# * under the terms of the GNU General Public License version 2 as published by the
# * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
# *
# * This program is distributed in the hope that it will be useful, but
# * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# * for more details.
# */

target-y = $(board)

obj-dir = $(CURDIR)/obj/$(board)
exe-dir = $(CURDIR)/out
src-dir = $(CURDIR)/src/$(board)
inc-dir = $(CURDIR)/src/$(board)/include

prj-dir = $(subst /release/aslinux/automotive-message-broker/plugins/autosar,,$(CURDIR))

INFRASTRUCTURE = $(prj-dir)/com/as.infrastructure
APPLICATION = $(prj-dir)/com/as.application
LUA   = $(prj-dir)/com/as.tool/lua
ASCONFIG = $(prj-dir)/com/as.tool/config.infrastructure.system
PY34 = python3
LNFS  = $(PY34) $(prj-dir)/release/make/lnfs.py
XCC   = $(PY34) xcc.py
STUDIO = $(PY34) studio.py

host = $(shell uname)

work_dir?=~/workspace/qemu-vexpress-ca9

# --------------------------------- [ COMPILER SPECIFICATION ] ---------------------------------------- #
# on C disk do the following command:
## mklink /D IAR "D:/Program Files (x86)/IAR Systems/Embedded Workbench 7.0"
ifeq ($(compiler),posix-gcc)
#cflags-y += -Werror
COMPILER_DIR = 
include $(prj-dir)/release/make/posix.mk
endif
# --------------------------------- [ BOARD SPECIFICATION ] ------------------------------------------- #
ifeq ($(board),posix)
ifeq ($(host),Linux)
def-y += -D__LINUX__
# my computer is 64 bit 
def-y += -D__X86_64__
else
$(error "windows is not supported")
endif	

ifeq ($(host),Linux)
ldflags-y +=-lrt
endif
ldflags-y += -lstdc++ -lm -lpthread
def-y += -DUSE_DET -DUSE_SCHM -DUSE_ECUM -DUSE_KERNEL -DUSE_MCU
def-y += -DUSE_CAN -DUSE_CANIF -DUSE_PDUR -DUSE_COM
def-y += -D__AS_CAN_BUS__ -DUSE_OS
endif

inc-y += -I$(inc-dir)

$(inc-dir):
	@mkdir -p $@
$(src-dir):
	@mkdir -p $@

OS:
	@(cd $(src-dir)/config.infrastructure.system;$(XCC) $(src-dir) false)	

BSW:
	@(cd $(src-dir)/config.infrastructure.system;$(XCC) $(src-dir) true)

studio:
	@(cd $(src-dir)/config.infrastructure.system;$(STUDIO) $(src-dir))	

dep-posix:
	@(cd $(src-dir);$(LNFS) $(ASCONFIG))
	@(cd $(inc-dir);$(LNFS) $(INFRASTRUCTURE)/include FALSE)
	@(cd $(inc-dir);$(LNFS) $(INFRASTRUCTURE)/include/sys)
	@(cd $(inc-dir);$(LNFS) $(INFRASTRUCTURE)/system/kernel/Os.h)
	@(cd $(src-dir);$(LNFS) $(INFRASTRUCTURE)/system/kernel/Os.c)
	@(cd $(src-dir);$(LNFS) $(INFRASTRUCTURE)/system/kernel/tinyos FALSE)
	@(cd $(src-dir);$(LNFS) $(INFRASTRUCTURE)/system/kernel/tinyos/portable/posix FALSE)
	@(cd $(src-dir);$(LNFS) $(INFRASTRUCTURE)/system/EcuM TRUE)
	@(cd $(src-dir);$(LNFS) $(INFRASTRUCTURE)/system/SchM TRUE)
	@(cd $(src-dir);$(LNFS) $(INFRASTRUCTURE)/communication/CanIf TRUE)
	@(cd $(src-dir);$(LNFS) $(INFRASTRUCTURE)/communication/PduR TRUE)
	@(cd $(src-dir);$(LNFS) $(INFRASTRUCTURE)/communication/Com TRUE)
	@(cd $(src-dir);$(LNFS) $(INFRASTRUCTURE)/communication/RPmsg TRUE)
	@(cd $(src-dir);$(LNFS) $(INFRASTRUCTURE)/diagnostic/Det TRUE)
	@(cd $(src-dir);$(LNFS) $(APPLICATION)/common/config/CanIf_SpecialPdus.h)
	@(cd $(src-dir);$(LNFS) $(APPLICATION)/common/config/EcuM_Cfg.h)
	@(cd $(src-dir);$(LNFS) $(APPLICATION)/common/config/EcuM_PBcfg.c)
	@(cd $(src-dir);$(LNFS) $(APPLICATION)/common/config/SchM_cfg.h)
	@(cd $(src-dir);$(LNFS) $(APPLICATION)/common/config/Det_Cfg.h)
	@(cd $(src-dir);$(LNFS) $(APPLICATION)/common/config/RPmsg_Cfg.c)
	@(cd $(src-dir);$(LNFS) $(APPLICATION)/common/config/RPmsg_Cfg.h)
	@(cd $(src-dir);$(LNFS) $(APPLICATION)/common/config/Rproc_Cfg.c)
	@(cd $(src-dir);$(LNFS) $(APPLICATION)/common/config/Rproc_Cfg.h)
	@(cd $(src-dir);$(LNFS) $(APPLICATION)/common/config/VirtQ_Cfg.c)
	@(cd $(src-dir);$(LNFS) $(APPLICATION)/common/config/VirtQ_Cfg.h)
	@(cd $(src-dir);$(LNFS) $(INFRASTRUCTURE)/arch/posix/mcal/Can.c)
	@(cd $(src-dir);$(LNFS) $(INFRASTRUCTURE)/arch/posix/mcal/Mcu.c)
	@(cd $(src-dir);$(LNFS) $(APPLICATION)/board.$(board)/common/Mcu_Cfg.c)
	@(cd $(src-dir);$(LNFS) $(APPLICATION)/board.$(board)/common/Mcu_Cfg.h)
	@(cd $(src-dir);$(LNFS) $(APPLICATION)/board.$(board)/common/Mcu_ConfigTypes.h)
	@(cd $(src-dir);$(LNFS) $(INFRASTRUCTURE)/arch/posix/mcal/Ipc.c)
	@(cd $(src-dir);$(LNFS) $(INFRASTRUCTURE)/arch/posix/mcal/Ipc.h)
	@(cd $(src-dir);$(LNFS) $(APPLICATION)/board.$(board)/common/Ipc_Cfg.c)
	@(cd $(src-dir);$(LNFS) $(APPLICATION)/board.$(board)/common/Ipc_Cfg.h)
	@(cd $(src-dir);$(LNFS) $(CURDIR)/autosar.arxml autosar.arxml)
	@(cd $(src-dir);$(LNFS) $(APPLICATION)/board.$(board)/simulator TRUE)
	@(cd $(src-dir);$(LNFS) $(LUA)/can TRUE)
	@(cd $(src-dir);$(LNFS) $(prj-dir)/com/as.tool/cancasexl.access/vxlapi.h)
	@(cd $(src-dir);$(LNFS) $(prj-dir)/com/as.tool/cancasexl.access/xlLoadlib.cpp xlLoadlib.c)
	@(cd $(src-dir);$(LNFS) $(APPLICATION)/common/infrastructure.xml)
	@(cd $(src-dir);sed -e "5c <OsRef name='tinyos'/>" infrastructure.xml > $(board)_infrastructure.xml)
	@(cd $(src-dir); rm infrastructure.xml)
	@(make BSW)
	@(make OS)
	@(echo "  >> prepare link for posix done")

dep:$(src-dir) $(inc-dir) dep-$(board)

clean: 
	@rm -frv ./obj/*
# ---------------------------------- [ posix       ] ---------------------------------- #
91:
	make dep board=posix compiler=posix-gcc
92:
	make lib board=posix compiler=posix-gcc debug=true
93:
	make lib board=posix compiler=posix-gcc debug=false	

# ---------------------------------- [ AMB BUILD   ] ---------------------------------- #
$(work_dir):
	@(mkdir -p $(work_dir))
	@(cd $(work_dir);git clone https://github.com/otcshare/automotive-message-broker.git)
	@(ln -fs `pwd` $(work_dir)/automotive-message-broker/plugins/autosar)
	@(cd $(work_dir)/automotive-message-broker;	\
		git checkout 0.14;	\
		mkdir -p build;	\
		git apply plugins/autosar/0001-add-amb-autosar-com-stack-as-plugin.patch;	\
		cd build;cmake ..)

$(work_dir)/automotive-message-broker/build/lib/libascore.so:
	@(make 91;make 93)
	@(ln -fs `pwd`/out/libposix.a $(work_dir)/automotive-message-broker/build/lib/libascore.so)

amb: $(work_dir) $(work_dir)/automotive-message-broker/build/lib/libascore.so
	@(echo " >> build @ $(work_dir)")
	@(cd $(work_dir)/automotive-message-broker/build;	\
		make;	\
		sudo make install)
	@(sudo rm -v /etc/ambd/plugins.d/examples*)
	@(sudo cp -v config /etc/ambd/config)
	
# smaple test:
# $	ambd 
# $ cansend can0 100#002200334455667788 && amb-get VehicleSpeed && amb-get EngineSpeed

canutils:
	@(echo " >> build @ $(work_dir)")
	@(cd $(work_dir);	\
		git clone https://github.com/linux-can/can-utils.git;	\
		cd can-utils;make; sudo make install)

	