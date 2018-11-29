#/**
# * AS - the open source Automotive Software on https://github.com/parai
# *
# * Copyright (C) 2017  AS <parai@foxmail.com>
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

# CPU architecture setting: versatilepb
export ARCH ?= versatilepb

TARGET ?= ctest_rm_04
CASE ?= Mixed-preemptive-2

schedfifo ?= no

to_winpath = $(shell echo "$(1)" | sed -e 's,/\([a-zA-Z]\),\1:,')

ifeq ($(shell uname), Linux)
CWD = $(CURDIR)
else
CWD = $(call to_winpath,$(CURDIR))
endif

obj-dir = $(CWD)/objs/$(TARGET)/$(CASE)
out-dir = $(CWD)/out/$(TARGET)/$(CASE)
src-dir = $(CWD)/src/$(TARGET)/$(CASE)

COM = $(CWD)/../../com
KERNEL = ${COM}/as.infrastructure/system/kernel/askar
CTEST  = ${COM}/as.infrastructure/system/kernel/freeosek/tst/ctest
MTEST  = $(CWD)/Testsuite

ifeq ($(shell uname), Linux)
PY27 = python2
PY34 = python3
else
PY27 = C:/Python27/python
PY34 = C:/Anaconda3/python
endif

LNFS  = $(PY27) $(CWD)/../../release/make/lnfs.py
XCC   = $(PY34) ${COM}/as.tool/config.infrastructure.system/xcc.py
REOIL = $(PY34) ${COM}/as.tool/config.infrastructure.system/aroil/reoil.py

# default compilers
ifeq (${ARCH}, versatilepb)
ifeq ($(shell uname), Linux)
export CROSS_COMPILE ?= arm-none-eabi-
else
export COMPILER_DIR ?= ${COM}/../release/download/gcc-arm-none-eabi-5_4-2016q3-20160926-win32
export CROSS_COMPILE ?= ${COMPILER_DIR}/bin/arm-none-eabi-
endif
AS = ${CROSS_COMPILE}as
CC = ${CROSS_COMPILE}gcc
LD = ${CROSS_COMPILE}ld
endif

# make verbose or not
export V ?= 0
ifeq ($(V),1)
Q=
else
Q=@
endif

# default FLAGS
ASFLAGS += -g
CFLAGS += -O0 -g -D__arch_${ARCH}__ -std=gnu99
LDFLAGS += -O0 -g
CFLAGS += -ffunction-sections -fdata-sections
LDFLAGS += --gc-sections


ifeq (${ARCH}, versatilepb)
ASFLAGS += -mcpu=arm926ej-s -marm -fpic
CFLAGS  += -mcpu=arm926ej-s -marm -fpic
ifeq ($(shell uname), Linux)
LDFLAGS += -lc -lgcc -L/usr/lib/arm-none-eabi/newlib -L/usr/lib/gcc/arm-none-eabi/4.8.2
else
LDFLAGS += -lc -lgcc -L${COMPILER_DIR}/arm-none-eabi/lib -L${COMPILER_DIR}/lib/gcc/arm-none-eabi/5.4.1
endif
LDFLAGS += -T ${COM}/as.infrastructure/arch/bcm2835/bsp/linker.lds
LDFLAGS += -Map ${out-dir}/${TARGET}.map
# 128MB
CFLAGS += -DMEMORY_SIZE=0x8000000
CFLAGS += -DSYSTEM_REGION_START=0x10000000
CFLAGS += -DSYSTEM_REGION_END=0x101f4000
CFLAGS += -DPAGE_SIZE=0x1000
CFLAGS += -DOS_STK_SIZE_SCALER=4
endif

ifeq (${ARCH}, versatilepb)
VPATH += ${KERNEL}/portable/arm ${COM}/as.infrastructure/arch/versatilepb/bsp
CFLAGS += -I${KERNEL}/portable/arm -I${COM}/as.infrastructure/arch/versatilepb/bsp
obj-y += ${obj-dir}/portable.o ${obj-dir}/portableS.o ${obj-dir}/startup.o
obj-y += ${obj-dir}/irq.o \
		 ${obj-dir}/pl031.o \
		 ${obj-dir}/serial.o \
		 ${obj-dir}/timer.o \
		 ${obj-dir}/vic.o \

endif

CFLAGS += -I${KERNEL}/include \
		  -I${KERNEL}/kernel \
		  -I${COM}/as.infrastructure/include \
		  -I${COM}/as.infrastructure/system/kernel \


ifeq ($(schedfifo),yes)
CFLAGS += -DUSE_SCHED_FIFO
endif

VPATH += ${KERNEL}/kernel
obj-y += ${obj-dir}/alarm.o \
		 ${obj-dir}/counter.o \
		 ${obj-dir}/event.o \
		 ${obj-dir}/kernel.o \
		 ${obj-dir}/resource.o \
		 ${obj-dir}/sched-bubble.o \
		 ${obj-dir}/sched-fifo.o \
		 ${obj-dir}/task.o \


VPATH += ${src-dir} \
		 $(CWD)/util \
	     ${COM}/as.infrastructure/clib \

ASFLAGS += -I${src-dir}

CFLAGS += -D$(TARGET)
CFLAGS += -D__CTEST_WITH_PRINTF__
CFLAGS += -I${src-dir}
obj-y += ${obj-dir}/Os_Cfg.o \
		 ${obj-dir}/$(TARGET).o \
		 ${obj-dir}/util.o \
		 ${obj-dir}/stdio_printf.o \


ifeq ($(TARGET), test)
VPATH  += $(CASE) $(MTEST)/cpuxx_comyy/src
CFLAGS += -DTestSubNr=0
CFLAGS += -DMTEST
CFLAGS += -I$(CASE) -I$(MTEST)/include -I$(MTEST)/cpuxx_comyy/inc
obj-y += ${obj-dir}/test_api.o
else
VPATH  += $(CTEST)/src
CFLAGS += -I$(CTEST)/inc
obj-y += ${obj-dir}/ctest_rst.o
endif


default:all

$(obj-dir)/%.o:%.S
	@echo
	@echo "  >> AS $(notdir $<)"	
	${Q} $(CC) $(ASFLAGS) -o $@ -c $<


$(obj-dir)/%.o:%.c
	@echo
	@echo "  >> CC $(notdir $<)"
	@$(CC) $(CFLAGS) -MM -MF $(patsubst %.o,%.d,$@) -MT $@ $<
	${Q} $(CC) $(CFLAGS) -o $@ -c $<

${obj-dir}:
	mkdir -p $@

${out-dir}:
	mkdir -p $@

${src-dir}:
	mkdir -p $@

dep-versatilepb:

dep-os: $(src-dir)
	@$(XCC) $(src-dir) false
ifeq ($(TARGET), test)
	@echo "#include \"Os.h\"" > $(src-dir)/osek.h
else
ifeq ($(shell uname), Linux)
	@echo "#include \"Os.h\"" > $(src-dir)/os.h
endif
	@echo "#include \"Std_Types.h\"" > $(src-dir)/Types.h
endif
	@echo " >> pre-process for $(TARGET) $(CASE) done"

all: ${obj-dir} ${out-dir} dep-${ARCH} ${obj-y}
	@echo "  >> LD $(TARGET)"
	${Q} $(LD) $(obj-y) $(LDFLAGS) -o $(out-dir)/$(TARGET)

qemuparams ?= -gdb tcp::1234 -S
test:
	@echo "sleep 0.05" > .check.sh
	@echo "telnet 127.0.0.1 1103" >> .check.sh
	@echo "qemu-system-arm -m 128 -M versatilepb -nographic -kernel $(out-dir)/$(TARGET) -serial tcp:127.0.0.1:1103,server $(qemuparams) & sh .check.sh" > .qemu.sh
	@chmod +x .qemu.sh
ifeq ($(shell uname), Linux)
	@gnome-terminal -x $(CWD)/.qemu.sh
else
	@sh $(CWD)/.qemu.sh
endif
	@echo "Test for $(TARGET) $(CASE)"

clean:
	@rm -frv objs/* out/* src/*

kill:
	@pgrep qemu-system-arm|xargs -i kill -9 {}
