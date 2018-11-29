# Makefile for asvirt-remoteproc

# for ARCH=arm, call
#  make MAKE="ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- BUILDER=/path/to/kernel KVERSION=?version/of/kernel"

# arm, x86
ARCH ?= x86

ifeq ($(ARCH),x86)
BUILDER ?= /lib/modules/$(shell uname -r)/build
KVERSION ?= $(shell uname -r|cut -d "-" -f 1)
endif

MAJOR = $(shell echo $(KVERSION) | cut -d "." -f 1)
MINOR = $(shell echo $(KVERSION) | cut -d "." -f 2)
PATCH = $(shell echo $(KVERSION) | cut -d "." -f 3)


obj-m += asvirt_remoteproc.o
asvirt_remoteproc-objs := rproc-asvirt/RPmsg.o \
		rproc-asvirt/RPmsg_Cfg.o \
		rproc-asvirt/Rproc_Cfg.o \
		rproc-asvirt/VirtQ.o \
		rproc-asvirt/VirtQ_Cfg.o \
		rproc-asvirt/Ipc_Cfg.o \
		rproc-asvirt/Ipc.o \
		asphystovirt.o \


default:all

dep:
	@(cd rproc-asvirt;make dep)
	@(wget https://raw.githubusercontent.com/torvalds/linux/v$(MAJOR).$(MINOR)/drivers/remoteproc/remoteproc_internal.h -O remoteproc_internal.h)
	@(cd rproc-asvirt;mv Std_Types.h .tmp; cp `readlink -f .tmp` ./Std_Types.h -v; sed -i "17c #define CONFIG_ARCH_VEXPRESS 1" Std_Types.h)
	@(cd rproc-asvirt;mv Ipc.c .tmp; cp `readlink -f .tmp` ./Ipc.c -v; sed -i "15c #define CONFIG_ARCH_VEXPRESS 1" Ipc.c)
	@(tail -n 17 asvirt_remoteproc.c | head -n 12 > asphystovirt.c)

all:
	$(MAKE) -C $(BUILDER) M=$(PWD) modules

clean:
	$(MAKE) -C $(BUILDER) M=$(PWD) clean
