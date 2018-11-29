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

# default version of yocto want to be used
VERSION?=morty
# "agl" or "poky"
POKY?=agl

# valid: x86, arm, arm64
export ARCH?=arm

ifeq (${ARCH},arm)
export MACHINE?=vexpress-qemu
else
export MACHINE?=qemu${ARCH}
endif

# linux security module(LSM): smack selinux
export security?=smack

rootfs?=$(CURDIR)/$(POKY)/poky/build/tmp/deploy/images/${MACHINE}

ifeq (${ARCH},x86)
export  CROSS_COMPILE?=$(CURDIR)/$(POKY)/poky/build/tmp/sysroots/x86_64-linux/usr/bin/i586-poky-linux/i586-poky-linux-
endif

ifeq (${ARCH},arm)
export  CROSS_COMPILE?=$(CURDIR)/$(POKY)/poky/build/tmp/sysroots/x86_64-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-
endif

ifeq (${ARCH},arm64)
export  CROSS_COMPILE?=$(CURDIR)/$(POKY)/poky/build/tmp/sysroots/x86_64-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-
endif

ifeq (${MACHINE},vexpress-qemu)
# this is as mender layer was used
TARGET ?= core-image-full-cmdline
else
TARGET ?= core-image-minimal
endif

default:all

# ----------------------------- [ issues ] -----------------------------------------------------

# ----------------------------- [ AGL ] -----------------------------------------------------
# https://mirrors.tuna.tsinghua.edu.cn/help/git-repo/
$(HOME)/bin/repo:
	@mkdir -p $(HOME)/bin
	@curl https://mirrors.tuna.tsinghua.edu.cn/git/git-repo -o $@
	@chmod +x $@

# get AGL for a refference for the study of yocto
$(CURDIR)/agl:$(HOME)/bin/repo
	@mkdir -p $@
	@(cd agl;export REPO_URL='https://mirrors.tuna.tsinghua.edu.cn/git/git-repo/';  \
		repo init -b dab -m dab_4.0.0.xml -u https://gerrit.automotivelinux.org/gerrit/AGL/AGL-repo; repo sync)
	@(cd agl/meta-openembedded/meta-oe/recipes-devtools; mkdir -p sip; cd sip; wget http://cgit.openembedded.org/meta-openembedded/plain/meta-oe/recipes-devtools/sip/sip_4.19.bb)

# ----------------------------- [ yocto ] -----------------------------------------------------
$(CURDIR)/$(POKY)/poky:
	@(cd $(POKY);git clone -b $(VERSION) git://git.yoctoproject.org/poky.git)

$(CURDIR)/$(POKY)/openembedded-core:
	@(cd $(POKY);git clone -b $(VERSION) git://git.openembedded.org/openembedded-core)

$(CURDIR)/$(POKY)/meta-openembedded:
	@(cd $(POKY);git clone -b $(VERSION) git://git.openembedded.org/meta-openembedded)

$(CURDIR)/$(POKY)/meta-intel-iot-security:
	(cd $(POKY); git clone -b v1.0.0 https://github.com/01org/meta-intel-iot-security.git)

$(CURDIR)/$(POKY)/meta-amb:
	@(cd $(POKY); git clone https://github.com/tripzero/meta-amb.git)

# remoce the cmake of meta-qt5 as the version is too old.
$(CURDIR)/$(POKY)/meta-qt5:
	@(cd $(POKY); git clone -b $(VERSION) https://github.com/meta-qt5/meta-qt5.git)

# ----------------------------- [ 3rd PART ] ----------------------------------------------------------
$(CURDIR)/$(POKY)/meta-mender:
	@(cd $(POKY); git clone -b $(VERSION) https://github.com/mendersoftware/meta-mender.git)
#	@(echo " >> update ${POKY}/meta-mender/meta-mender-core/classes/mender-sdimg.bbclass 108: set count to 2097152")
#	@(sed -i 's/count=0 seek=/count=2097152 seek=/g' ${POKY}/meta-mender/meta-mender-core/classes/mender-sdimg.bbclass)

$(CURDIR)/$(POKY)/oe-meta-go:
	@(cd $(POKY); git clone https://github.com/mem/oe-meta-go.git)

$(CURDIR)/$(POKY)/meta-selinux:
	@(cd $(POKY); git clone -b $(VERSION) https://git.yoctoproject.org/git/meta-selinux)

# ----------------------------- [ aslinux build ] -----------------------------------------------------
as$(POKY):$(CURDIR)/$(POKY) $(CURDIR)/$(POKY)/meta-intel-iot-security $(CURDIR)/$(POKY)/meta-openembedded \
		$(CURDIR)/$(POKY)/meta-amb $(CURDIR)/$(POKY)/meta-qt5 $(CURDIR)/$(POKY)/meta-mender $(CURDIR)/$(POKY)/oe-meta-go \
		$(CURDIR)/$(POKY)/meta-selinux
	@echo " cd $(POKY)/poky; source oe-init-build-env ; make as$(POKY)setup -C $(CURDIR); bitbake ${TARGET} "
	@echo " runqemu tmp/deploy/images/${MACHINE}/${TARGRT}-${MACHINE}.qemuboot.conf nographic"

as$(POKY)setup:
	@echo "MACHINE ?= \"${MACHINE}\"" >> $(POKY)/poky/build/conf/local.conf
ifeq (${security}, smack)
	@echo "BBLAYERS += \"`readlink -f $(POKY)/meta-intel-iot-security/meta-security-smack`\"" >> $(POKY)/poky/build/conf/bblayers.conf
	@echo "BBLAYERS += \"`readlink -f $(POKY)/meta-intel-iot-security/meta-security-framework`\"" >> $(POKY)/poky/build/conf/bblayers.conf
endif
	@echo "BBLAYERS += \"`readlink -f $(POKY)/meta-openembedded/meta-oe`\"" >> $(POKY)/poky/build/conf/bblayers.conf
	@echo "BBLAYERS += \"`readlink -f $(POKY)/meta-openembedded/meta-python`\"" >> $(POKY)/poky/build/conf/bblayers.conf
	@echo "BBLAYERS += \"`readlink -f $(POKY)/meta-openembedded/meta-efl`\"" >> $(POKY)/poky/build/conf/bblayers.conf
	@echo "BBLAYERS += \"`readlink -f $(POKY)/meta-openembedded/meta-multimedia`\"" >> $(POKY)/poky/build/conf/bblayers.conf
	@echo "BBLAYERS += \"`readlink -f $(POKY)/meta-qt5`\"" >> $(POKY)/poky/build/conf/bblayers.conf
	@echo "BBLAYERS += \"`readlink -f $(POKY)/meta-amb`\"" >> $(POKY)/poky/build/conf/bblayers.conf
	@echo "BBLAYERS += \"`readlink -f $(POKY)/meta-agl/meta-agl`\"" >> $(POKY)/poky/build/conf/bblayers.conf
	@echo "BBLAYERS += \"`readlink -f $(POKY)/meta-agl-demo`\"" >> $(POKY)/poky/build/conf/bblayers.conf
	@echo "BBLAYERS += \"`readlink -f $(POKY)/meta-agl/meta-app-framework`\"" >> $(POKY)/poky/build/conf/bblayers.conf
	@echo "BBLAYERS += \"`readlink -f $(POKY)/meta-agl/meta-ivi-common`\"" >> $(POKY)/poky/build/conf/bblayers.conf
ifeq (${security}, selinux)
	@echo "BBLAYERS += \"`readlink -f $(POKY)/meta-selinux`\"" >> $(POKY)/poky/build/conf/bblayers.conf
endif
ifeq (${MACHINE},vexpress-qemu)
# https://docs.mender.io/1.0/artifacts/building-mender-yocto-image
	@echo "BBLAYERS += \"`readlink -f $(POKY)/oe-meta-go`\"" >> $(POKY)/poky/build/conf/bblayers.conf
	@echo "BBLAYERS += \"`readlink -f $(POKY)/meta-mender/meta-mender-core`\"" >> $(POKY)/poky/build/conf/bblayers.conf
	@echo "BBLAYERS += \"`readlink -f $(POKY)/meta-mender/meta-mender-demo`\"" >> $(POKY)/poky/build/conf/bblayers.conf
	@echo "BBLAYERS += \"`readlink -f $(POKY)/meta-mender/meta-mender-qemu`\"" >> $(POKY)/poky/build/conf/bblayers.conf
	@echo "MENDER_ARTIFACT_NAME = \"release-1\"" >> $(POKY)/poky/build/conf/local.conf
	@echo "INHERIT += \"mender-full\"" >> $(POKY)/poky/build/conf/local.conf
	@echo "IMAGE_FSTYPES = \"ext4\"" >> $(POKY)/poky/build/conf/local.conf
	@echo "INHERIT += \"rm_work\""  >> $(POKY)/poky/build/conf/local.conf
endif
#	@echo "BBLAYERS += \"`readlink -f meta-as`\"" >> $(POKY)/poky/build/conf/bblayers.conf
ifeq (${security}, smack)
# check README of $(POKY)/meta-intel-iot-security/meta-security-smack: enable smack
	@echo "OVERRIDES .= \":smack\"" >> $(POKY)/poky/build/conf/local.conf
	@echo "DISTRO_FEATURES_append = \" smack\"" >> $(POKY)/poky/build/conf/local.conf
	@echo "DISTRO_FEATURES_append = \" pam\"" >> $(POKY)/poky/build/conf/local.conf
	@echo "DISTRO_FEATURES_append += \" systemd\"" >> $(POKY)/poky/build/conf/local.conf
	@echo "VIRTUAL-RUNTIME_init_manager = \"systemd\"" >> $(POKY)/poky/build/conf/local.conf
	@echo "DISTRO_FEATURES_BACKFILL_CONSIDERED = \"sysvinit\"" >> $(POKY)/poky/build/conf/local.conf
	@echo "VIRTUAL-RUNTIME_initscripts = \"\"" >> $(POKY)/poky/build/conf/local.conf
	@echo "CORE_IMAGE_EXTRA_INSTALL += \"coreutils\"" >> $(POKY)/poky/build/conf/local.conf
	@echo "CORE_IMAGE_EXTRA_INSTALL += \"smack-userspace\"" >> $(POKY)/poky/build/conf/local.conf
	@echo "CORE_IMAGE_EXTRA_INSTALL += \"cynara security-manager\"" >> $(POKY)/poky/build/conf/local.conf
endif
ifeq (${security}, selinux)
	@echo "DISTRO = \"poky-selinux\"" >> $(POKY)/poky/build/conf/local.conf
	@echo "DISTRO_FEATURES_remove = \" sysvinit\"" >> $(POKY)/poky/build/conf/local.conf
	@echo "DISTRO_FEATURES_append = \" systemd\"" >> $(POKY)/poky/build/conf/local.conf
	@echo "VIRTUAL-RUNTIME_init_manager = \"systemd\"" >> $(POKY)/poky/build/conf/local.conf
	@echo "DISTRO_FEATURES_BACKFILL_CONSIDERED = \"\"" >> $(POKY)/poky/build/conf/local.conf

endif
# install others
	@echo "CORE_IMAGE_EXTRA_INSTALL += \"python cryptsetup af-binder\"" >> $(POKY)/poky/build/conf/local.conf
	@echo "CORE_IMAGE_EXTRA_INSTALL += \"strace e2fsprogs attr openssh canutils\"" >> $(POKY)/poky/build/conf/local.conf
	@echo "CORE_IMAGE_EXTRA_INSTALL += \"af-main af-binder low-level-can-service\"" >> $(POKY)/poky/build/conf/local.conf
	@echo "AGL_EXTRA_IMAGE_FSTYPES = \"ext4\"" >> $(POKY)/poky/build/conf/local.conf
ifeq (${MACHINE},vexpress-qemu)
	@echo "MENDER_STORAGE_TOTAL_SIZE_MB = \"4096\"" >> $(POKY)/poky/build/conf/local.conf
endif

$(rootfs)/system.img:
	@dd if=/dev/zero of=$@ bs=1G count=2
	@sudo mkfs.ext4 $@

# will be /dev/vdb
$(rootfs)/userdata.img:
	@dd if=/dev/zero of=$@ bs=1G count=1
	@sudo mkfs.ext4 $@

$(rootfs)/rootfs:
	@mkdir -p $@
	@tar xf $(rootfs)/${TARGET}-${MACHINE}.tar.bz2 -C $@

systemimg:$(rootfs)/system.img $(rootfs)/userdata.img $(rootfs)/rootfs
	@(cd $(rootfs);mkdir -p tmp;	\
		parted system.img unit B print;	\
		sudo mount -t ext4 -o loop system.img tmp/; \
		pwd;sudo cp rootfs/* tmp/ -rf; \
		sudo umount tmp)

$(CURDIR)/.qemux86.qemuboot.conf:
	@echo "[config_bsp]" > $@
	@echo "machine = ${MACHINE}" >> $@
	@echo "tune_arch = i586" >> $@
	@echo "deploy_dir_image = $(POKY)/poky/build/tmp/deploy/images/${MACHINE}" >> $@
	@echo "kernel_imagetype = .bzImage" >> $@
	@echo "image_name = system" >> $@
	@echo "image_link_name = .system.img" >> $@
	@echo "staging_dir_native = $(POKY)/poky/build/tmp/sysroots/x86_64-linux" >> $@
	@echo "staging_bindir_native = $(POKY)/poky/build/tmp/sysroots/x86_64-linux/usr/bin" >> $@
	@echo "staging_dir_host = $(POKY)/poky/build/tmp/sysroots/${MACHINE}" >> $@
	@echo "qb_cpu_kvm_x86-64 = -cpu kvm64" >> $@
	@echo "qb_mem = -m 256" >> $@
	@echo "qb_kernel_cmdline_append = vga=0 uvesafb.mode_option=640x480-32 oprofile.timer=1 uvesafb.task_timeout=-1" >> $@
	@echo "qb_cpu_kvm_x86 = -cpu kvm32" >> $@
	@echo "qb_system_name_x86 = qemu-system-i386" >> $@
	@echo "qb_audio_opt = -soundhw ac97,es1370" >> $@
	@echo "qb_default_kernel = .bzImage.bin" >> $@
	@echo "qb_audio_drv = alsa" >> $@
	@echo "qb_cpu_x86 = -cpu qemu32" >> $@
	@echo "qb_serial_opt = -serial mon:stdio -serial null" >> $@
	@echo "qb_opt_append = -vga vmware -show-cursor -usb -usbdevice tablet -device virtio-rng-pci -drive file=$(rootfs)/userdata.img,if=virtio,format=raw" >> $@
	@echo "qb_cpu_x86-64 = -cpu core2duo" >> $@
	@echo "qb_default_fstype = ext4" >> $@
	@echo "qb_system_name_x86-64 = qemu-system-x86_64" >> $@
	@echo "qb_system_name = qemu-system-i386" >> $@
	@echo "qb_cpu_kvm = -cpu kvm32" >> $@
	@echo "qb_cpu = -cpu qemu32" >> $@

$(CURDIR)/.qemuarm.qemuboot.conf:
	@echo "[config_bsp]" > $@
	@echo "machine = qemuarm" >> $@
	@echo "tune_arch = arm" >> $@
	@echo "deploy_dir_image = ${POKY}/poky/build/tmp/deploy/images/qemuarm" >> $@
	@echo "kernel_imagetype = .zImage" >> $@
	@echo "image_name = system" >> $@
	@echo "image_link_name = .system.img" >> $@
	@echo "staging_dir_native = ${POKY}/poky/build/tmp/sysroots/x86_64-linux" >> $@
	@echo "staging_bindir_native = ${POKY}//poky/build/tmp/sysroots/x86_64-linux/usr/bin" >> $@
	@echo "staging_dir_host = ${POKY}/poky/build/tmp/sysroots/qemuarm" >> $@
	@echo "qb_opt_append = -show-cursor -usb -usbdevice tablet -device virtio-rng-pci" >> $@
	@echo "qb_dtb = .zImage-versatile-pb.dtb" >> $@
	@echo "qb_default_fstype = ext4" >> $@
	@echo "qb_mem = -m 256" >> $@
	@echo "qb_serial_opt = -serial mon:stdio -serial null" >> $@
	@echo "qb_system_name = qemu-system-arm" >> $@
	@echo "qb_machine = -machine versatilepb" >> $@
	@echo "qb_kernel_cmdline_append = console=ttyAMA0,115200 console=tty" >> $@
	@echo "qb_default_kernel = .zImage.bin" >> $@

$(CURDIR)/.vexpress-qemu.qemuboot.conf:

$(CURDIR)/.qemuarm64.qemuboot.conf:
	@echo "[config_bsp]" > $@
	@echo "machine = qemuarm64" >> $@
	@echo "tune_arch = aarch64" >> $@
	@echo "deploy_dir_image = ${POKY}/poky/build/tmp/deploy/images/qemuarm64" >> $@
	@echo "kernel_imagetype = .Image" >> $@
	@echo "image_name = system" >> $@
	@echo "image_link_name = .system.img" >> $@
	@echo "staging_dir_native = ${POKY}/poky/build/tmp/sysroots/x86_64-linux" >> $@
	@echo "staging_bindir_native = ${POKY}/poky/build/tmp/sysroots/x86_64-linux/usr/bin" >> $@
	@echo "staging_dir_host = ${POKY}/poky/build/tmp/sysroots/qemuarm64" >> $@
	@echo "qb_mem = -m 512" >> $@
	@echo "qb_default_fstype = ext4" >> $@
	@echo "qb_cpu = -cpu cortex-a57" >> $@
	@echo "qb_serial_opt = -device virtio-serial-device -chardev null,id=virtcon -device virtconsole,chardev=virtcon" >> $@
	@echo "qb_tcpserial_opt =  -device virtio-serial-device -chardev socket,id=virtcon,port=@PORT@,host=127.0.0.1 -device virtconsole,chardev=virtcon" >> $@
	@echo "qb_slirp_opt = -netdev user,id=net0 -device virtio-net-device,netdev=net0" >> $@
	@echo "qb_kernel_cmdline_append = console=ttyAMA0,38400" >> $@
	@echo "qb_opt_append = -show-cursor -device virtio-rng-pci -monitor null" >> $@
	@echo "qb_machine = -machine virt" >> $@
	@echo "qb_system_name = qemu-system-aarch64" >> $@
	@echo "qb_default_kernel = .Image.bin" >> $@
	@echo "qb_rootfs_opt = -drive id=disk0,file=@ROOTFS@,if=none,format=raw -device virtio-blk-device,drive=disk0" >> $@
	@echo "qb_tap_opt = -netdev tap,id=net0,ifname=@TAP@,script=no,downscript=no -device virtio-net-device,netdev=net0,mac=@MAC@" >> $@

$(CURDIR)/.system.img.ext4:
	@ln -fs $(rootfs)/system.img $@

# for example do debug kernel, do: export qemuparams="-s -S"
export qemuparams?="-nographic"
runqemu:$(CURDIR)/.${MACHINE}.qemuboot.conf $(CURDIR)/.system.img.ext4
ifeq (${MACHINE},vexpress-qemu)
# need modify /etc/fstab for not to do mount of uboot and data, and disable service /etc/systemd/system/multi-user.target.wants/mender.service by linked to /dev/null
	$(POKY)/poky/build/tmp/sysroots/x86_64-linux/usr/bin/qemu-system-arm -M vexpress-a9 -m 512M -kernel .zImage -dtb .zImage-vexpress-v2p-ca9.dtb -drive file=.system.img.ext4,if=sd \
		-net nic,macaddr=52:54:00:e3:b1:96 -net user,hostfwd=tcp::8822-:22 -display vnc=:23 $(qemuparams) \
		-append "root=/dev/mmcblk0 rw console=ttyAMA0,115200 console=tty"
else
	@(export PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:$(POKY)/poky/scripts/;$(POKY)/poky/scripts/runqemu $< qemuparams="$(qemuparams)")
endif

runmender:
	@(export BUILDDIR=${POKY}/poky/build;$(POKY)/meta-mender/meta-mender-qemu/scripts/mender-qemu)

killqemu:
	pgrep qemu | xargs -i kill -9 {}

kernel-menuconfig:
	@(cd kernel4.8;make menuconfig O=.)

kernel4.8/.config:
	@(cp $(POKY)/poky/build/tmp/work-shared/${MACHINE}/kernel-build-artifacts/.config $@ -v)

$(CURDIR)/kernel4.8:
	@(cp $(POKY)/poky/build/tmp/work-shared/${MACHINE}/kernel-source $@ -r)

# this is for the purpose to fast build the kernel and debug
kernel:$(CURDIR)/kernel4.8 kernel4.8/.config
	@(cd kernel4.8;make)
ifeq (${ARCH},x86)
	@(ln -fs kernel4.8/arch/i386/boot/bzImage .bzImage)
endif
ifeq (${ARCH},arm)
	@(ln -fs kernel4.8/arch/${ARCH}/boot/zImage .zImage)
ifeq (${MACHINE},vexpress-qemu)
	@(ln -fs kernel4.8//arch/${ARCH}/boot/dts/vexpress-v2p-ca9.dtb .zImage-vexpress-v2p-ca9.dtb)
else
	@(ln -fs kernel4.8//arch/${ARCH}/boot/dts/versatile-pb.dtb .zImage-versatile-pb.dtb)
endif
endif
ifeq (${ARCH},arm64)
	@(ln -fs kernel4.8/arch/${ARCH}/boot/Image .Image)
endif

cc:
ifeq (${CFILE},)
	@echo "Usage:: make cc CFILE=\"path/to/c_source_file\""
	@echo "# base rules for app makefile" > .base.mk
	@echo "CC=${CROSS_COMPILE}gcc --sysroot=$(CURDIR)/$(POKY)/poky/build/tmp/sysroots/$(MACHINE)" >> .base.mk
	@echo "SYSROOTS=$(CURDIR)/$(POKY)/poky/build/tmp/sysroots/$(MACHINE)" >> .base.mk
	@cat .base.mk
else
	${CROSS_COMPILE}gcc --sysroot=$(CURDIR)/$(POKY)/poky/build/tmp/sysroots/$(MACHINE) ${CFLAGS} ${CFILE} -o $(rootfs)/rootfs/home/root/$(basename $(notdir ${CFILE})).exe
endif

all:as$(POKY)

