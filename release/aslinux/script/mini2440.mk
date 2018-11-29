# make file to build the platform for mini2440
# start from a clean directory, 
# ln -fs /as/release/aslinux/script/mini2440.mk makefile

export ARCH=arm

gcc-vivi = $(CURDIR)/opt/usr/loca/arm/2.95.3
gcc-kernel = $(CURDIR)/opt/usr/local/arm/3.4.1
gcc-qt = $(CURDIR)/opt/usr/local/arm/3.3.2
gcc-common = $(CURDIR)/opt/usr/local/arm/3.4.1

out=$(CURDIR)/out
rootfs = $(out)/rootfs
download = $(CURDIR)/download

# first default make
all:$(rootfs) asmini2440-kernel asmini2440-uboot asmini2440-qemu busybox nand
	@echo "  >> build mini2440 done <<"

$(rootfs):
	@mkdir -p $(rootfs)
	@mkdir -p $(rootfs)/lib/modules
	@mkdir -p $(rootfs)/example

extract-kernel:
	@tar -zxvf $(download)/linux-2.6.13-qq2440-20080625.tgz -C $(CURDIR)
	@mv kernel-2.6.13 kernel

kernel/.config:
	@(cd kernel;cp config_n35 .config)
	@(cd kernel;make menuconfig O=.)

kernel-menuconfig:
	@(cd kernel;make menuconfig O=.)

askernel: kernel/.config
	@(cd kernel; make all CROSS_COMPILE=$(gcc-kernel)/bin/arm-linux-)
	@cp -fv kernel/arch/arm/boot/zImage $(rootfs)/zImage
	@cp -fv kernel/vmlinux $(rootfs)/vmlinux
	@find kernel -name "*.ko"|xargs -i cp -v {} $(rootfs)/example

mini2440-qemu:
#	@git clone git://repo.or.cz/qemu/mini2440.git mini2440-qemu
	git clone https://gitcafe.com/parai/min2440-qemu.git

# need to add "LIBS+=-lz -lrt -lm" to Makefile and Makefile.target
asmini2440-qemu:mini2440-qemu
	@(cd mini2440-qemu;./configure --target-list=arm-softmmu 	\
		 --extra-ldflags="-lz -lrt -lm" --prefix=$(CURDIR)/opt;	\
		make install )

mini2440-boot:
#	@git clone git://repo.or.cz/u-boot-openmoko/mini2440.git mini2440-boot
	git clone https://gitcafe.com/parai/min2440-boot.git
asmini2440-boot:mini2440-boot
	@(cd mini2440-boot; make mini2440_config; make -j4 CROSS_COMPILE=arm-linux-gnueabi-; cp u-boot.bin $(out) -v)

mini2440-kernel:
#	@git clone git://repo.or.cz/linux-2.6/mini2440.git mini2440-kernel
	git clone https://gitcafe.com/parai/min2440-kernel.git

asmini2440-kernel:mini2440-kernel
	@(cd mini2440-kernel; make mini2440_defconfig ARCH=arm;	\
		make -j4 ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- uImage;	\
		cp -v arch/arm/boot/uImage $(out))
		
extract-uboot:
	@tar -zxvf $(download)/u-boot-1.1.6_QQ2440.tgz -C $(CURDIR)
	@mv u-boot-1.1.6_QQ2440 u-boot

asuboot:u-boot
	@(cd u-boot;make QQ2440_config)
	@(cd u-boot;make all CROSS_COMPILE=$(gcc-common)/bin/arm-linux-)
	@(cd u-boot;cp -v u-boot $(rootfs))

extract-busybox:
	@bzip2 -dvk $(download)/busybox-1.24.0.tar.bz2
	@tar -xvf $(download)/busybox-1.24.0.tar -C $(CURDIR)
	@rm $(download)/busybox-1.24.0.tar
	@mv busybox-1.24.0 busybox

$(download)/busybox-1.24.0.tar.bz2:
	@(cd $(download);wget http://busybox.net/downloads/busybox-1.24.0.tar.bz2)
	@make extract-busybox

busybox-menuconfig:
	@(cd busybox;make menuconfig)

busybox/.config:
	@(cd busybox;make menuconfig)

asbusybox:$(download)/busybox-1.24.0.tar.bz2 busybox/.config
	@(cd busybox;make all CROSS_COMPILE=arm-linux-gnueabi-)
	@(cd busybox;make install CONFIG_PREFIX=$(rootfs))


extract-glibc:
	@bzip2 -dvk $(download)/glibc-2.22.tar.bz2
	@tar -xvf $(download)/glibc-2.22.tar -C $(CURDIR)
	@rm $(download)/glibc-2.22.tar
	@mv glibc-2.22 glibc

$(download)/glibc-2.22.tar.bz2:
	@(cd $(download;wget http://mirrors.ustc.edu.cn/gnu/libc/glibc-2.22.tar.bz2)
	@make extract-glibc

asglibc:$(download)/glibc-2.22.tar.bz2
	@(cd glibc;mkdir -pv build;	\
		cd build;	\
		../configure arm-linux-gnueabi --target=arm-linux-gnueabi --build=i686-pc-linux-gnu --prefix= --enable-add-ons;	\
		make;	\
		make install install_root=$(rootfs))

$(out)/sdcard.ext3:
	@dd if=/dev/zero of=$@ bs=1G count=2
	@sudo mkfs.ext3 $@

asrootfs:
	@cp aslinux/rootfs/* $(rootfs) -frv

sdcard:$(out)/sdcard.ext3 asrootfs
	@(cd $(out);mkdir -pv tmp;	\
		sudo mount -t ext3 sdcard.ext3 tmp/ -o loop;	\
		sudo cp $(rootfs)/* tmp/ -rvf;	\
		sudo mkdir tmp/dev;	\
		sudo mknod tmp/dev/tty1 c 4 1;	\
		sudo mknod tmp/dev/tty2 c 4 2;	\
		sudo mknod tmp/dev/tty3 c 4 3;	\
		sudo mknod tmp/dev/tty4 c 4 4;	\
		sudo chmod +x tmp/etc/init.d/rcS;	\
		sudo umount tmp;	\
		rm tmp -fr)

nand:
#	@cp -v flashimg/uboot.part $(out)
	@mkdir -p $(rootfs)/dev $(rootfs)/mnt $(rootfs)/tmp
	@(cd $(rootfs)/dev;sudo mknod -m 660 null c 1 3; sudo mknod -m 660 console c 5 1)
	@(cd $(out); mkfs.jffs2 -r $(rootfs) -o rootfs.jffs2 -e 16KiB --pad=0x3aa0000 -s 0x200 -n －b)
	@(cd $(out);	\
		flashimg -s 64M -t nand -f nand.bin -p uboot.part -w boot,u-boot.bin -w kernel,uImage -w root,rootfs.jffs2 -z 512)

run-qemu-mini2440:
	@opt/bin/qemu-system-arm -M mini2440 -serial stdio -mtdblock out/nand.bin -usbdevice mouse
# for the first start of qemu, need do the below command
# MINI2440 # nboot kernel
# MINI2440 # setenv bootargs root=/dev/mtdblock3 rootfstype=jffs2 console=ttySAC0,115200 mini2440=3tb init=/linuxrc
# MINI2440 # saveenv
# MINI2440 # bootm
example:
	@(cd example;make all)

clean:
	@(cd kernel;make clean)
	@(cd u-boot;make clean)
	@(cd busybox;make clean)
