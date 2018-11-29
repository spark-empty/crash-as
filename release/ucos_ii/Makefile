#/**
# * AS - the open source Automotive Software on https://github.com/parai
# *
# * Copyright (C) 2016  AS <parai@foxmail.com>
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

# CPU architecture setting: win32 posix cm3 raspi 9s12xep100 dos ...
ifeq ($(shell uname), Linux)
export ARCH ?= posix
else
export ARCH ?= dos
endif

TARGET = ucOS_II_Demo

obj-dir = $(CURDIR)/objs
out-dir = $(CURDIR)/out

COM = $(CURDIR)/../../com
KERNEL = ${COM}/as.infrastructure/system/kernel/ucos_ii

ifeq ($(shell uname), Linux)
PY27 = python2
else
PY27 = C:Python27/python
endif

LNFS  = $(PY27) $(CURDIR)/../../release/make/lnfs.py

# default compilers
ifeq (${ARCH}, posix)
CC = gcc
LD = gcc
endif

ifeq (${ARCH}, win32)
CC = gcc
LD = gcc
endif

ifeq (${ARCH}, dos)
CC = gcc
LD = gcc
endif

ifeq (${ARCH}, cm3)
export CROSS_COMPILE ?= arm-none-eabi-
# board select: stm32f107vc at91sam3s
export BOARD ?= stm32f107vc
AS = ${CROSS_COMPILE}as
CC = ${CROSS_COMPILE}gcc
LD = ${CROSS_COMPILE}ld
endif

ifeq (${ARCH}, raspi)
export CROSS_COMPILE ?= arm-none-eabi-
AS = ${CROSS_COMPILE}as
CC = ${CROSS_COMPILE}gcc
LD = ${CROSS_COMPILE}ld
endif

ifeq (${ARCH}, 9s12xep100)
ifeq ($(shell uname), Linux)
CW ?= /opt/CWS12
WINE = wine
else
# codewarrior path, C:\> mklink /D C:\CWS12 "C:\Program Files (x86)\Freescale\CWS12v5.2"
CW ?= C:/CWS12
WINE =
endif
AS = $(CW)/Prog/ahc12.exe
CC = $(CW)/Prog/chc12.exe
LD = $(CW)/Prog/linker.exe
endif

# make verbose or not
export V ?= 0
ifeq ($(V),1)
Q=
else
Q=@
endif

ifeq (${ARCH}, 9s12xep100)
obj-dir = ./objs
CFLAGS += -WErrFileOff -WOutFileOff -EnvOBJPATH=$(obj-dir)
CFLAGS += -I$(CW)/lib/hc12c/include -Mb -CpuHCS12 -D__9S12__ -D__arch_${ARCH}__
LDFLAGS += -WErrFileOff -WOutFileOff -EnvOBJPATH=$(obj-dir)
LDFLAGS += -M -WmsgNu=abcet -Add($(CW)/lib/hc12c/lib/ansibi.lib)
ASFLAGS += $(CFLAGS)
else
# default FLAGS
CFLAGS += -O0 -g -D__arch_${ARCH}__ -std=gnu99
LDFLAGS += -O0 -g
endif

ifeq (${ARCH}, posix)
LDFLAGS += -lpthread -lncurses -lm
LDFLAGS += -Wl,-Map,${out-dir}/${TARGET}.map
endif

ifeq (${ARCH}, win32)
LDFLAGS += -lwinmm
LDFLAGS += -Wl,-Map,${out-dir}/${TARGET}.map
endif

ifeq (${ARCH}, dos)
LDFLAGS += -lwinmm
LDFLAGS += -Wl,-Map,${out-dir}/${TARGET}.map
endif

ifeq (${ARCH}, cm3)
ASFLAGS += -mcpu=cortex-m3  -mthumb
CFLAGS  += -mcpu=cortex-m3  -mthumb
LDFLAGS += -T ${COM}/as.application/board.${BOARD}/script/linker-app.lds
LDFLAGS += -Map ${out-dir}/${TARGET}.map
endif

ifeq (${ARCH}, raspi)
ASFLAGS += -mcpu=arm1176jzf-s -fpic -ffreestanding
CFLAGS  += -mcpu=arm1176jzf-s -fpic -ffreestanding
LDFLAGS += -lc -lgcc -L/usr/lib/arm-none-eabi/newlib -L/usr/lib/gcc/arm-none-eabi/4.8.2
LDFLAGS += -T ${COM}/as.infrastructure/arch/bcm2835/bsp/linker.lds
LDFLAGS += -Map ${out-dir}/${TARGET}.map
endif

ifeq (${ARCH}, posix)
VPATH += ${KERNEL}/portable/posix
VPATH += ${COM}/as.tool/lua/can/rs232
CFLAGS += -I${KERNEL}/portable/posix -I${COM}/as.tool/lua/can/rs232
obj-y += ${obj-dir}/os_cpu_c.o ${obj-dir}/pc.o ${obj-dir}/rs232.o
VPATH += ${CURDIR}/demo/example
# choose one example: ex1/ex2/ex3/ex4
ex ?= ex1
obj-y += ${obj-dir}/${ex}.o
ifeq (${ex},ex3)
CFLAGS += -DNO_TASK_STAT_HOOK -DNO_OS_TASK_SWITCH_HOOK
endif
endif

ifeq (${ARCH}, win32)
VPATH += ${KERNEL}/portable/win32
CFLAGS += -I${KERNEL}/portable/win32
obj-y += ${obj-dir}/os_cpu_c.o ${obj-dir}/os_trace.o 
endif

ifeq (${ARCH}, dos)
VPATH += ${KERNEL}/portable/dos
VPATH += ${COM}/as.tool/lua/can/rs232
CFLAGS += -I${KERNEL}/portable/dos -I${COM}/as.tool/lua/can/rs232
obj-y += ${obj-dir}/os_cpu_c.o ${obj-dir}/pc.o ${obj-dir}/rs232.o
VPATH += ${CURDIR}/demo/example
# choose one example: ex1/ex2/ex3/ex4
ex ?= ex1
obj-y += ${obj-dir}/${ex}.o
ifeq (${ex},ex3)
CFLAGS += -DNO_TASK_STAT_HOOK -DNO_OS_TASK_SWITCH_HOOK
endif
endif

ifeq (${ARCH}, cm3)
VPATH += ${KERNEL}/portable/cortex-m3/gnu
CFLAGS += -I${KERNEL}/portable/cortex-m3/gnu
obj-y += ${obj-dir}/os_cpu_c.o ${obj-dir}/os_cpu_a.o ${obj-dir}/startup.o
endif

ifeq (${ARCH}, raspi)
VPATH += ${KERNEL}/portable/raspi/gnu ${COM}/as.infrastructure/arch/bcm2835/bsp
CFLAGS += -I${KERNEL}/portable/raspi/gnu -I${COM}/as.infrastructure/arch/bcm2835/bsp
obj-y += ${obj-dir}/os_cpu_c.o ${obj-dir}/os_cpu_a.o ${obj-dir}/startup.o
obj-y += ${obj-dir}/interrupts.o ${obj-dir}/syscalls.o ${obj-dir}/timer.o ${obj-dir}/uart.o
endif

ifeq (${ARCH}, 9s12xep100)
CFLAGS += -Itmp9s12src/core
CFLAGS += -Itmp9s12src
CFLAGS += -Idemo
CFLAGS += -Itmp9s12src/portable/s12cpuv2
objs += tmp9s12src/core/ucos_ii.o
objs += tmp9s12src/os_cpu_c.o
objs += tmp9s12src/start12.o
objs += tmp9s12src/datapage.o
objs += demo/main.o
obj-link = $(foreach x,$(objs),$(notdir $(x)))
else
VPATH += ${KERNEL}/core
CFLAGS += -I${KERNEL}/core
obj-y += ${obj-dir}/ucos_ii.o

VPATH += ${CURDIR}/demo
CFLAGS += -I${CURDIR}/demo
obj-y += ${obj-dir}/main.o
ifeq (${ARCH}, cm3)
obj-y += ${obj-dir}/apphooks.o
endif
endif # 9s12xep100


default:all

$(obj-dir)/%.o:%.asm
	@echo
	@echo "  >> AS $(notdir $<)"	
	${Q} $(AS) $(ASFLAGS) -o $@ -c $<

$(obj-dir)/%.o:%.s
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

$(CURDIR)/qemu-system-arm-rpi_UART1.tar.gz:
	@wget https://github.com/idrawone/qemu-rpi/raw/master/tools/qemu-system-arm-rpi_UART1.tar.gz
	@tar xf $@

qemuparams?="-nographic"
qemu-rpi:$(CURDIR)/qemu-system-arm-rpi_UART1.tar.gz
	@(./qemu-system-arm -cpu arm1176 -m 128 -M raspi ${qemuparams} -kernel $(out-dir)/$(TARGET))

dep-win32:

dep-dos:

dep-posix:

dep-cm3:

dep-raspi:

$(out-dir)/makefile:
	@echo "CC = $(CC)" > $@
	@echo "AS = $(AS)" >> $@
	@echo "LD = $(LD)" >> $@
	@echo "ASFLAGS = $(ASFLAGS)" >> $@
	@echo "CFLAGS = $(CFLAGS)" >> $@
	@echo "LDFLAGS = $(LDFLAGS)" >> $@
	@cat demo/Makefile >> $@
	@echo "all:$(objs)"  > $@.tmp
	@sed -i 's/\//\\/g' $@.tmp
	@cat $@.tmp >> $@
	@echo "	$(LD) $(CW)/lib/hc12c/prm/mc9s12xep100.prm $(LDFLAGS) -Add($(obj-link)) -M -O$(TARGET).abs"  >> $@
	@echo "generate Makefile $@ done"

$(CURDIR)/tmp9s12src:
	mkdir -p $@

dep-9s12xep100: $(CURDIR)/tmp9s12src ${out-dir} $(out-dir)/makefile
	@(cd $<; $(LNFS) ${KERNEL}/core)
	@(cd $<; $(LNFS) ${KERNEL}/portable/s12cpuv2  TRUE)
	@(cd $<; cp -v ${CW}/lib/hc12c/src/start12.c .)
	@(cd $<; cp -v ${CW}/lib/hc12c/src/mc9s12xep100.c .)
	@(cd $<; cp -v ${CW}/lib/hc12c/src/DATAPAGE.C datapage.c)
	@(cd $<; cp -v ${CW}/\(CodeWarrior_Examples\)/HCS12X/S12XE_XGATE_setup/Full_Chip_Simulation.ini .)
	@(cd $<; cp -v ${CW}/\(CodeWarrior_Examples\)/HCS12X/S12XE_XGATE_setup/C_Layout.hwl .)
	@(cd $<; cp -v ${CW}/\(CodeWarrior_Examples\)/HCS12X/S12XE_XGATE_setup/Default.mem .)
	@(cd $<; cp -v ${CW}/\(CodeWarrior_Examples\)/HCS12X/S12XE_XGATE_setup/cmd . -r)

all: ${obj-dir} ${out-dir} ${obj-y} dep-${ARCH}
ifeq (${ARCH}, 9s12xep100)
	$(WINE) $(CW)/Prog/piper.exe $(CW)/Prog/maker.exe $(out-dir)/makefile
else
	@echo "  >> LD $(TARGET)"
	${Q} $(LD) $(obj-y) $(LDFLAGS) -o $(out-dir)/$(TARGET)
endif	

clean:
	@rm -frv ${obj-dir} ${out-dir}

run:
ifeq (${ARCH}, 9s12xep100)
	$(WINE) $(CW)/Prog/hiwave.exe -W -Prod=Full_Chip_Simulation.ini -instance=sim $(TARGET).abs
#	$(WINE) $(CW)/Prog/hiwave.exe -W -Prod=TBDML.ini -instance=tbdml $(TARGET).abs -CMD="Go"
endif
