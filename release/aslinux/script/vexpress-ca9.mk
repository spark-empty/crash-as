# make file to build the platform for vexpress-ca9
# start from a clean directory, 
# ln -fs /as/release/aslinux/script/vexpress-ca9.mk makefile

#   As in China that often some URL resoure especial GOOGLE is not accessable, so a mirror is an alternate 
# solution, such as https://mirrors.tuna.tsinghua.edu.cn/
# for x86_64, most of the module can be build manully by the below command:
# ./configure --prefix=`readlink -f ../out/rootfs`

export ARCH?=arm
ifeq ($(ARCH),arm)
export HOST=arm-linux-gnueabi
export CROSS_COMPILE=$(HOST)-
else
export HOST=x86
export CROSS_COMPILE=
endif

out=$(CURDIR)/out
rootfs = $(out)/rootfs
download = $(CURDIR)/download

SUPERFN = python $(CURDIR)/../../make/superfn.py

# first default make
#all:$(rootfs) askernel asuboot asglibc asbusybox astslib asqt sdcard
all:$(rootfs) askernel asglibc asbusybox asamb ascanutil sdcard
	@echo "  >> build vexpress-a9 done <<"

# 4.8.6 or 5.5.1
qt-version?=4.8.6

$(rootfs):
	@mkdir -p $(rootfs)
	@mkdir -p $(rootfs)/lib/modules
	@mkdir -p $(rootfs)/lib/modules/3.18.0+
	@mkdir -p $(rootfs)/example
	@mkdir -p $(download)

$(download)/bzip2-1.0.6.tar.gz:
	@(cd $(download);wget http://www.bzip.org/1.0.6/bzip2-1.0.6.tar.gz)

$(CURDIR)/bzip2:$(download)/bzip2-1.0.6.tar.gz
	@(tar xf $(download)/bzip2-1.0.6.tar.gz -C .; mv bzip2-1.0.6 bzip2)

asbzip2:$(CURDIR)/bzip2
	@(cd bzip2;sed -i "18c CC=$(CROSS_COMPILE)gcc" Makefile;	\
		sed -i "19c AR=$(CROSS_COMPILE)ar" Makefile;	\
		sed -i "20c RANLIB=$(CROSS_COMPILE)ranlib" Makefile;	\
		sed -i "27c PREFIX=$(rootfs)"  Makefile;	\
		make install )

$(CURDIR)/ustr:
	@(git clone https://github.com/certik/ustr.git)

asustr:$(CURDIR)/ustr
	@(cd ustr;sed -i "31c CC=$(CROSS_COMPILE)gcc" Makefile;	\
		sed -i "32c AR=$(CROSS_COMPILE)ar" Makefile;	\
		sed -i "33c RANLIB=$(CROSS_COMPILE)ranlib" Makefile;	\
		sed -i "11c DESTDIR=$(rootfs)"  Makefile;	\
		sed -i "23c # define USTR_CONF_HAVE_64bit_SIZE_MAX     0" ustr-conf-debug.h;	\
		sed -i "23c # define USTR_CONF_HAVE_64bit_SIZE_MAX     0" ustr-conf.h;	\
		make install )

$(CURDIR)/selinux:
	@(git clone https://github.com/SELinuxProject/selinux.git;cd selinux;git checkout sepolgen-2.6)

asselinux:$(CURDIR)/selinux
	@(cd selinux;	\
		CC=$(CROSS_COMPILE)gcc make install DESTDIR=$(rootfs) \
			CFLAGS=" -O3 -gdwarf-2 -fno-strict-aliasing -Wall -Wshadow -I$(rootfs)/include " \
			LDFLAGS=" -L$(rootfs)/lib -Wl,-rpath,$(rootfs)/lib ")

$(CURDIR)/dbus:
	@(git clone https://anongit.freedesktop.org/git/dbus/dbus.git; cd dbus;git checkout dbus-1.10.0)

asdbus:$(CURDIR)/dbus
	@(cd dbus;./autogen.sh;./configure --host=$(HOST) CC=$(CROSS_COMPILE)gcc; \
		find . -name Makefile | xargs -i $(SUPERFN) replace.file.all {} /usr/local /usr;  \
		make ; make install DESTDIR=$(rootfs))

$(CURDIR)/zlib:
	@(git clone https://github.com/madler/zlib.git;cd zlib;git checkout v1.2.10)

aszlib:$(CURDIR)/zlib
	@(cd zlib; CC=$(CROSS_COMPILE)gcc ./configure --prefix=$(rootfs); \
		make ; make install)

$(download)/pcre-8.40.tar.gz:
	@(cd $(download);wget https://ftp.pcre.org/pub/pcre/pcre-8.40.tar.gz)

$(CURDIR)/pcre:$(download)/pcre-8.40.tar.gz
	@(tar xf $(download)/pcre-8.40.tar.gz -C .;mv pcre-8.40 pcre)

#need: sudo apt-get install g++-arm-linux-gnueabi
aspcre:$(CURDIR)/pcre
	@(cd pcre;./configure --host=$(HOST) CC=$(CROSS_COMPILE)gcc LDFLAGS="--sysroot=$(rootfs)" --prefix=$(rootfs); \
		make ; make install)

# need: sudo apt-get install texinfo
$(CURDIR)/libffi:
	@(git clone https://github.com/libffi/libffi.git;cd libffi;git checkout v3.2.1)

aslibffi:$(CURDIR)/libffi
	@(cd libffi; ./autogen.sh; \
		./configure --host=$(HOST) CC=$(CROSS_COMPILE)gcc --prefix=$(rootfs); \
		make ; make install)

$(download)/util-linux-2.29.1.tar.gz:
	@(cd $(download);wget https://www.kernel.org/pub/linux/utils/util-linux/v2.29/util-linux-2.29.1.tar.gz)

$(CURDIR)/util-linux:$(download)/util-linux-2.29.1.tar.gz
	@(tar xf $(download)/util-linux-2.29.1.tar.gz -C .; mv util-linux-2.29.1 util-linux)

asutillinux:$(CURDIR)/util-linux
	@(cd util-linux;./autogen.sh;	\
		./configure --host=$(HOST) CC=$(CROSS_COMPILE)gcc --prefix=$(rootfs); \
		make; make install)

glib-version?=2.44

$(download)/glib-2.0.0.tar.gz:
	@(cd $(download);wget https://ftp.acc.umu.se/pub/gnome/sources/glib/2.0/glib-2.0.0.tar.gz)

$(download)/glib-2.44.1.tar.xz:
	@(cd $(download);wget https://ftp.acc.umu.se/pub/gnome/sources/glib/2.44/glib-2.44.1.tar.xz)

$(download)/glib-2.50.2.tar.xz:
	@(cd $(download);wget https://ftp.acc.umu.se/pub/gnome/sources/glib/2.50/glib-2.50.2.tar.xz)

$(CURDIR)/glib:$(download)/glib-2.50.2.tar.xz $(download)/glib-2.0.0.tar.gz $(download)/glib-2.44.1.tar.xz
ifeq ($(glib-version),2.5)
	@(tar -xJf $(download)/glib-2.50.2.tar.xz -C .;mv glib-2.50.2 glib)
else
ifeq ($(glib-version),2.44)
	@(tar -xJf $(download)/glib-2.44.1.tar.xz -C .;mv glib-2.44.1 glib)
else
	@(tar -xf $(download)/glib-2.0.0.tar.gz -C .;mv glib-2.0.0 glib)
endif
endif

$(CURDIR)/glib/arm.cache:
	@echo "glib_cv_long_long_format=yes" > $@
	@echo "glib_cv_stack_grows=no" >> $@
	@echo "glib_cv_working_bcopy=no" >> $@
	@echo "glib_cv_uscore=no" >> $@
	@echo "ac_cv_func_posix_getpwuid_r=yes" >> $@
	@echo "ac_cv_func_nonposix_getpwuid_r=no" >> $@
	@echo "ac_cv_func_posix_getgrgid_r=no" >> $@

# reconfigure need make distclean
asglib:$(CURDIR)/glib $(CURDIR)/glib/arm.cache
	@(cd $(rootfs)/include; ln -fs ../lib/libffi-3.2.1/include/ffi.h ffi.h; ln -fs ../lib/libffi-3.2.1/include/ffitarget.h ffitarget.h)
ifeq ($(glib-version),2.5)
# somehow, it would failed as missing some API, use "make -i"
	@(cd glib;	\
		sed -i "457c #PKG_CHECK_MODULES(LIBFFI, [libffi >= 3.0.0])" ./configure.ac;	\
		sed -i "458c #AC_SUBST(LIBFFI_CFLAGS)" ./configure.ac;	\
		sed -i "459c #AC_SUBST(LIBFFI_LIBS)" ./configure.ac;	\
		sed -i "1758c have_libmount=yes" ./configure.ac)
	@(cd glib;./autogen.sh --cache-file=arm.cache --host=$(HOST) CC=$(CROSS_COMPILE)gcc --prefix=$(rootfs) \
			CFLAGS=" -I$(rootfs)/include " LDFLAGS=" -lffi --sysroot=$(rootfs) "; \
		make; make install)
else
ifeq ($(glib-version),2.44)
	@(cd glib;	\
		sed -i "445c #PKG_CHECK_MODULES(LIBFFI, [libffi >= 3.0.0])" ./configure.ac;	\
		sed -i "446c #AC_SUBST(LIBFFI_CFLAGS)" ./configure.ac;	\
		sed -i "447c #AC_SUBST(LIBFFI_LIBS)" ./configure.ac)
	@(cd glib;./autogen.sh --cache-file=arm.cache --host=$(HOST) CC=$(CROSS_COMPILE)gcc --prefix=$(rootfs) \
			CFLAGS=" -I$(rootfs)/include " LDFLAGS=" -lffi --sysroot=$(rootfs) "; \
		make; make install)
else
#	@(cd glib;$(SUPERFN) replace.file.all ./configure '(exit 1); exit 1;' '(echo 1); echo 1;';chmod +x ./configure)
	@(cd glib;./configure prefix=$(rootfs); make all CC=$(CROSS_COMPILE)gcc CFLAGS=" -I$(rootfs)/include " LDFLAGS=" -lffi --sysroot=$(rootfs) "; \
		sed -i "66c CC=$(CROSS_COMPILE)gcc" glib/Makefile;	\
		sed -i "66c CC=$(CROSS_COMPILE)gcc" gthread/Makefile;	\
		sed -i "70c CC=$(CROSS_COMPILE)gcc" gobject/Makefile;	\
		sed -i "67c CC=\"$(CROSS_COMPILE)gcc\"" libtool;	\
		make install LDFLAGS="--sysroot=$(rootfs)")
endif
endif

$(download)/npth-1.3.tar.bz2:
	@(cd $(download);wget https://gnupg.org/ftp/gcrypt/npth/npth-1.3.tar.bz2)

$(download)/libassuan-2.4.3.tar.bz2:
	@(cd $(download);wget https://gnupg.org/ftp/gcrypt/libassuan/libassuan-2.4.3.tar.bz2)

$(download)/libksba-1.3.5.tar.bz2:
	@(cd $(download);wget https://gnupg.org/ftp/gcrypt/libksba/libksba-1.3.5.tar.bz2)

$(download)/libgcrypt-1.7.6.tar.bz2:
	@(cd $(download);wget https://gnupg.org/ftp/gcrypt/libgcrypt/libgcrypt-1.7.6.tar.bz2)

$(CURDIR)/libgcrypt:$(download)/libgcrypt-1.7.6.tar.bz2
	@(tar jxf $(download)/libgcrypt-1.7.6.tar.bz2 -C .; mv libgcrypt-* libgcrypt)

aslibgcrypt:$(CURDIR)/libgcrypt
	@(cd libgcrypt; \
		sed -i "14288c GPG_ERROR_LIBS=\" -L$(rootfs)/lib -lgpg-error  \"" ./configure;	\
		./configure --host=$(HOST) CC=$(CROSS_COMPILE)gcc --prefix=$(rootfs); \
		make all CFLAGS=" -I$(rootfs)/include --include \"gpg-error.h\" " ; make install LDFLAGS=" $(rootfs)/lib/libgpg-error.so -lpthread ")

$(download)/libgpg-error-1.26.tar.bz2:
	@(cd $(download);wget https://gnupg.org/ftp/gcrypt/libgpg-error/libgpg-error-1.26.tar.bz2)

$(CURDIR)/libgpg-error:$(download)/libgpg-error-1.26.tar.bz2
	@(tar jxf $(download)/libgpg-error-1.26.tar.bz2 -C .; mv libgpg-error-* libgpg-error)

aslibgpg-error:$(CURDIR)/libgpg-error
	@(cd libgpg-error; ./autogen.sh; \
		./configure --host=$(HOST) CC=$(CROSS_COMPILE)gcc --prefix=$(rootfs); make all; make install)

$(download)/gnupg-2.1.18.tar.bz2:
	@(cd $(download);https://gnupg.org/ftp/gcrypt/gnupg/gnupg-2.1.18.tar.bz2)

$(CURDIR)/cynara:
	@git clone https://github.com/Samsung/cynara.git
	@(cd cynara;git checkout v0.8.0)

ascynara:$(CURDIR)/cynara
	@(cd cynara; \
		sed -i "31c #" src/helpers/creds-dbus/CMakeLists.txt; \
		sed -i "32c #" src/helpers/creds-dbus/CMakeLists.txt; \
		sed -i "33c #" src/helpers/creds-dbus/CMakeLists.txt; \
		sed -i "34c #" src/helpers/creds-dbus/CMakeLists.txt; \
		sed -i "31c #" src/CMakeLists.txt; \
		sed -i "32c #" src/CMakeLists.txt; \
		sed -i "33c #" src/CMakeLists.txt; \
		sed -i "34c #" src/CMakeLists.txt; \
		mkdir -p build;cd build; \
		CXX=$(CROSS_COMPILE)g++ CC=$(CROSS_COMPILE)gcc LINKER=$(CROSS_COMPILE)ld \
		RANLIB=$(CROSS_COMPILE)ranlib AR=$(CROSS_COMPILE)ar \
		CXXFLAGS="-I$(rootfs)/include " LDFLAGS="--sysroot=$(rootfs)" cmake ..; \
		make; make install DESTDIR=$(rootfs) )

$(download)/OpenSSL-fips-2_0_13.tar.gz:
	@(cd $(download);wget https://github.com/openssl/openssl/archive/OpenSSL-fips-2_0_13.tar.gz)

$(CURDIR)/openssl:$(download)/OpenSSL-fips-2_0_13.tar.gz
	@(tar xf $(download)/OpenSSL-fips-2_0_13.tar.gz -C .; mv openssl-OpenSSL-fips-2_0_13 openssl)

asopenssl:$(CURDIR)/openssl
	@(cd openssl; ./Configure $(ARCH) compiler:gcc --prefix=$(rootfs); make ; make install -i)

$(download)/ruby-2.4.0.tar.gz:
	@(cd $(download);wget https://cache.ruby-lang.org/pub/ruby/2.4/ruby-2.4.0.tar.gz)

$(CURDIR)/ruby-2.4.0:$(download)/ruby-2.4.0.tar.gz
	@tar xf $(download)/ruby-2.4.0.tar.gz -C .

# make for host machine ubuntu: need install openssl before build.
# $ gem install openssl
# $ gem sources --add https://gems.ruby-china.org/ --remove https://rubygems.org/
# $ gem install jekyll -v 3.3.0
asruby:$(CURDIR)/ruby-2.4.0
	@(cd ruby-2.4.0;./configure --with-openssl-dir=/usr/local/ssl;make)

$(CURDIR)/jekyll:
	@git clone git://github.com/jekyll/jekyll.git
	@(cd jekyll; git checkout v3.3.0)

asjekyll:$(CURDIR)/jekyll
	@(cd jekyll ; script/bootstrap; bundle exec rake build; ls pkg/*.gem | head -n 1 | xargs sudo gem install -l)

$(CURDIR)/strace:
	@git clone https://github.com/strace/strace.git
	@(cd strace;git checkout v4.15)

asstrace:$(CURDIR)/strace
	@(cd strace; ./bootstrap; autoreconf -i; ./configure --host=$(ARCH) CC=$(CROSS_COMPILE)gcc --prefix=$(rootfs); make ; make install)

$(CURDIR)/lk:
	@(git clone https://github.com/littlekernel/lk.git)

aslk:$(CURDIR)/lk
$(download)/libcap-2.24.tar.xz:
	@(cd $(download);wget https://www.kernel.org/pub/linux/libs/security/linux-privs/libcap2/libcap-2.24.tar.xz)

$(CURDIR)/libcap:$(download)/libcap-2.24.tar.xz
	@(tar -xJf $(download)/libcap-2.24.tar.xz -C .; mv libcap-* libcap)

aslibcap:$(CURDIR)/libcap
	@(cd libcap;	\
		make all BUILD_CC=$(CROSS_COMPILE)gcc CC=$(CROSS_COMPILE)gcc AR=$(CROSS_COMPILE)ar RANLIB=$(CROSS_COMPILE)ranlib LDFLAGS=" -L$(rootfs)/lib -L$(rootfs)/lib64 ";	\
		make install DESTDIR=$(rootfs) )

$(download)/kmod-17.tar.gz:
	@(cd $(download);wget https://www.kernel.org/pub/linux/utils/kernel/kmod/kmod-17.tar.gz)

$(CURDIR)/kmod:$(download)/kmod-17.tar.gz
	@(tar -xzf $(download)/kmod-17.tar.gz -C .; mv kmod-* kmod)

askmod:$(CURDIR)/kmod
	@(cd kmod;./configure --host=$(ARCH) CC=$(CROSS_COMPILE)gcc ; make all; make install DESTDIR=$(rootfs))

# http://wiki.beyondlogic.org/index.php?title=Cross_Compiling_SystemD_for_ARM
$(CURDIR)/systemd:
	@(git clone https://github.com/systemd/systemd.git;cd systemd;git checkout v212)
# need sudo apt-get install gtk-doc-tools
assystemd:$(CURDIR)/systemd
	@(cd systemd; ./autogen.sh; mkdir -p build;)
	@(cd systemd/build;    \
		sed -i "589c have_gcrypt=no" ../configure;	\
		sed -i "591c #" ../configure;sed -i "592c #" ../configure;sed -i "593c #" ../configure;	\
		sed -i "594c #" ../configure;sed -i "595c #" ../configure;sed -i "596c #" ../configure;	\
		sed -i "130c #define HAVE_MALLOC 1" ../config.h.in;	\
		sed -i "384c //#undef malloc" ../config.h.in; )
	@(cd systemd/build;../configure --host=$(HOST) CC=$(CROSS_COMPILE)gcc \
			CFLAGS=" -I$(rootfs)/include -I$(rootfs)/usr/include " \
			LDFLAGS=" --sysroot=$(rootfs) -L$(rootfs)/lib -L$(rootfs)/lib64 "; \
		make ; make install DESTDIR=$(rootfs))

$(CURDIR)/smack:
	@(git clone https://github.com/smack-team/smack.git;cd smack; git checkout v1.3.0)

assmack:$(CURDIR)/smack
#sed -i "4385c #LT_INIT(disable-static)" configure;
	@(cd smack; ./autogen.sh; \
		./configure --host=$(ARCH) CC=$(CROSS_COMPILE)gcc --prefix=$(rootfs); make all; make install)

$(download)/attr-2.4.47.src.tar.gz:
	@(cd $(download);wget http://download.savannah.gnu.org/releases/attr/attr-2.4.47.src.tar.gz)

$(CURDIR)/attr:$(download)/attr-2.4.47.src.tar.gz
	@(tar xf $(download)/attr-2.4.47.src.tar.gz -C .; mv attr-* attr)

asattr:$(CURDIR)/attr
	@(cd attr;./configure --host=$(ARCH) CC=$(CROSS_COMPILE)gcc --prefix=$(rootfs); make ; make install;	\
		cp -v libattr/.libs/* $(rootfs)/lib)

$(download)/jre-6u45-linux-i586.bin:
	@(cd $(download);wget http://download.oracle.com/otn/java/jdk/6u45-b06/jre-6u45-linux-i586.bin;  \
		wget http://download.oracle.com/otn/java/jdk/6u43-b01/jdk-6u43-linux-i586.bin)

asjava:$(download)/jre-6u45-linux-i586.bin

$(download)/qemu_v2.0.0.tar.gz:
	@(cd $(download);wget https://github.com/qemu/qemu/archive/v2.0.0.tar.gz -O qemu_v2.0.0.tar.gz)

$(download)/qemu:$(download)/qemu_v2.0.0.tar.gz
	@(tar xf $(download)/qemu_v2.0.0.tar.gz -C .; mv qemu-2.0.0 qemu)

# need install "libpixman-1-dev libglib2.0-dev"
asqemu:$(download)/qemu
	@(cd qemu;./configure;make)

$(download)/sqlite-amalgamation-3.5.6.tar.gz:
	@(cd $(download);wget http://www.sqlite.org/sqlite-amalgamation-3.5.6.tar.gz)

sqlite-3.5.6:$(download)/sqlite-amalgamation-3.5.6.tar.gz
	@tar zxf $(download)/sqlite-amalgamation-3.5.6.tar.gz -C .

assqlite:sqlite-3.5.6
	@(cd sqlite-3.5.6;./configure --host=$(ARCH) CC=$(CROSS_COMPILE)gcc --prefix=$(rootfs)  \
		 --enable-shared --disable-readline --disable-dynamic-extensions;  	\
		make; make install)

$(download)/Python-2.5.1.tar.bz2:
	@(cd $(download);wget http://www.python.org/ftp/python/2.5.1/Python-2.5.1.tar.bz2)

Python-2.5.1:$(download)/Python-2.5.1.tar.bz2
	@(tar jxf $(download)/Python-2.5.1.tar.bz2 -C .)

aspython:Python-2.5.1
	@(cd Python-2.5.1;mkdir -p build.pc;cd build.pc;SVNVERSION="Unversioned directory" ../configure CC=gcc --host=x86 ;make all;)
# modify the configure to disable the %zd printf format check
# For some PC, when do configure, should add 'SVNVERSION="Unversioned directory"', don't ask me why
	@(cd Python-2.5.1;mkdir build.arm;cd build.arm;  \
		sed -i "22092c if 0; then" ../configure;	\
		sed -i "22168c fi" ../configure;	\
		SVNVERSION="Unversioned directory" ../configure --prefix=$(rootfs) --disable-ipv6 --host=$(ARCH) CC=$(CROSS_COMPILE)gcc --enable-shared;  \
		$(SUPERFN) replace.file.all Makefile './\x24(BUILDPYTHON)' ../build.pc/python;  \
		make all;make install)

can-utils:
	@git clone  https://github.com/linux-can/can-utils.git

ascanutil: can-utils
	@(cd can-utils;./autogen.sh;	\
		./configure --host=$(ARCH) --prefix=$(rootfs) CC=$(CROSS_COMPILE)gcc;	\
		make clean;make all;make install)

libsocketcan:
	@git clone git://git.pengutronix.de/git/tools/libsocketcan.git
	@(cd libsocketcan;git checkout v0.0.10)

canutils:
	@git clone git://git.pengutronix.de/tools/canutils
	@(cd canutils;git checkout canutils-4.0.6)

ascanutils: libsocketcan canutils 
	(cd libsocketcan;./autogen.sh;	\
		./configure --host=$(ARCH) CC=$(CROSS_COMPILE)gcc;	\
		make clean;make all)
	(cd canutils;./autogen.sh;	\
		sed -i "12522c pkg_failed=no" configure;	\
		./configure --host=$(ARCH) --prefix=$(rootfs) CC=$(CROSS_COMPILE)gcc CFLAGS=-I$(CURDIR)/libsocketcan/include LDFLAGS="-lsocketcan -L$(CURDIR)/libsocketcan/src/.libs";	\
		make clean;make all;make install)

automotive-message-broker:
	@git clone https://github.com/otcshare/automotive-message-broker.git
	@(cd automotive-message-broker;git checkout 0.14;mkdir build)

asamb:automotive-message-broker
	@(cd automotive-message-broker/build; cmake ..; make)

# see http://www.redhat.com/archives/dm-devel/2016-February/msg00199.html
# init: add support to directly boot to a mapped device
patch-kernel-dm-boot:
	@(cd kernel; wget https://patchwork.kernel.org/patch/104860/raw/ -O v4-2-3-dm-export-a-table-mapped-device-to-the-ioctl-interface.patch;  \
		patch -p1 < v4-2-3-dm-export-a-table-mapped-device-to-the-ioctl-interface.patch)
	@(cd kernel; wget https://patchwork.kernel.org/patch/104861/raw/ -O v4-3-3-init-add-support-to-directly-boot-to-a-mapped-device.patch; \
		patch -p1 < v4-3-3-init-add-support-to-directly-boot-to-a-mapped-device.patch)
	@(cd kernel; sed -i "396c dm_table_destroy(table);" init/do_mounts_dm.c)
	@(cd kernel; sed -i "308c extern void dm_table_destroy(struct dm_table* t);" init/do_mounts_dm.c)

kernel-version ?= linux-3.18.48

patch-kernel:
	@(cd ../kernel/drivers/remoteproc/rproc-asvirt; make dep)
	@(cp ../kernel . -rvf)
	@(cd kernel; patch -p1 < aspatch/0001-aslinux-add-virtual-pinctrl-and-rpmsg-driver.patch)
	@(cd kernel; patch -p1 < aspatch/0002-aslinux-add-virtual-CAN-driver-based-on-RPMSG.patch)

extract-kernel:
	@xz -dk $(download)/$(kernel-version).tar.xz
	@tar -xf $(download)/$(kernel-version).tar -C $(CURDIR)
	@rm $(download)/$(kernel-version).tar
	@mv $(kernel-version) kernel
	@make patch-kernel

$(download)/$(kernel-version).tar.xz:
	@(cd $(download);wget https://www.kernel.org/pub/linux/kernel/v`echo $(kernel-version)|cut -b 7`.x/$(kernel-version).tar.xz)
	@make extract-kernel

kernel/.config:
#	@(cd kernel;cp arch/arm/configs/vexpress_defconfig .config)
#	@(cd kernel;make menuconfig O=.)
ifeq ($(ARCH),arm)
	@(cd kernel;cp aspatch/vexpress_defconfig .config)
else
	@(cd kernel;make menuconfig O=.)
endif

kernel-menuconfig:
	@(cd kernel;make menuconfig O=.)

askernel:$(rootfs) $(download)/$(kernel-version).tar.xz kernel/.config
#make uImage -j2 LOADADDR=0x60003000
	@(cd kernel;make all)
	@cp -f kernel/arch/$(ARCH)/boot/zImage $(rootfs)/zImage
	@cp -f kernel/vmlinux $(rootfs)/vmlinux
	@find kernel -name "*.ko"|xargs -i cp -v {} $(rootfs)/example
ifeq ($(ARCH),arm)
	@cp -f kernel/arch/arm/boot/dts/vexpress-v2p-ca9.dtb $(rootfs)
endif

u-boot:
	@git clone git://git.denx.de/u-boot.git

asuboot:u-boot
	@(cd u-boot;make vexpress_ca9x4_defconfig)
	@(cd u-boot;make all)
	@(cd u-boot;cp -v u-boot $(rootfs))

$(CURDIR)/busybox: $(download)/busybox-1.24.0.tar.bz2
	@bzip2 -dk $(download)/busybox-1.24.0.tar.bz2
	@tar -xf $(download)/busybox-1.24.0.tar -C $(CURDIR)
	@rm $(download)/busybox-1.24.0.tar
	@mv busybox-1.24.0 busybox

$(download)/busybox-1.24.0.tar.bz2:
	@(cd $(download);wget http://busybox.net/downloads/busybox-1.24.0.tar.bz2)

busybox-menuconfig:
	@(cd busybox;make menuconfig)

busybox/.config:
	#@(cd busybox;make menuconfig)
	@(cd busybox;cp ../kernel/aspatch/busybox_defconfig .config)

asbusybox:$(CURDIR)/busybox busybox/.config
	@(cd busybox;make all)
	@(cd busybox;make install CONFIG_PREFIX=$(rootfs))

extract-glibc:
	@bzip2 -dk $(download)/glibc-2.22.tar.bz2
	@tar -xf $(download)/glibc-2.22.tar -C $(CURDIR)
	@rm $(download)/glibc-2.22.tar
	@mv glibc-2.22 glibc

$(download)/glibc-2.22.tar.bz2:
	@(cd $(download);wget http://mirrors.ustc.edu.cn/gnu/libc/glibc-2.22.tar.bz2)
	@make extract-glibc

$(download)/glibc-2.25.tar.bz2:
	@(cd $(download); wget http://ftp.gnu.org/gnu/libc/glibc-2.25.tar.bz2)

$(CURDIR)/glibc:$(download)/glibc-2.25.tar.bz2
	@(tar xf $(download)/glibc-2.25.tar.bz2 -C .; mv glibc-2.25 glibc)

asglibc:$(CURDIR)/glibc
ifeq ($(ARCH),arm)
	@(cd glibc;mkdir -pv build;	\
		cd build;	\
		../configure $(HOST) --target=$(HOST) --build=i686-pc-linux-gnu --prefix= --enable-add-ons;	\
		make;	\
		make install install_root=$(rootfs))
else
	@(cd glibc;mkdir -p build; cd build; ../configure --disable-sanity-checks; make; make install install_root=$(rootfs))
endif

$(download)/qt-everywhere-opensource-src-5.5.1.tar.gz:$(rootfs)
	@(cd $(download);wget http://101.44.1.124/files/A165000004244025/anychimirror101.mirrors.tds.net/pub/Qt/archive/qt/5.5/5.5.1/single/qt-everywhere-opensource-src-5.5.1.tar.gz)
	@make extract-qt

extract-qt-5.5.1:$(download)/qt-everywhere-opensource-src-5.5.1.tar.gz
	@(gunzip -k $(download)/qt-everywhere-opensource-src-5.5.1.tar.gz)
	@(tar -xf$(download)/qt-everywhere-opensource-src-5.5.1.tar -C $(CURDIR))
	@rm $(download)/qt-everywhere-opensource-src-5.5.1.tar

extract-qt-4.8.6:$(download)/qt-everywhere-opensource-src-4.8.6.tar.gz
	@(gunzip -k $(download)/qt-everywhere-opensource-src-4.8.6.tar.gz)
	@(tar -xf$(download)/qt-everywhere-opensource-src-4.8.6.tar -C $(CURDIR))
	@rm $(download)/qt-everywhere-opensource-src-4.8.6.tar

$(download)/qt-everywhere-opensource-src-4.8.6.tar.gz:
	@(cd $(download);wget http://101.44.1.117/files/82540000020A32A4/mirrors.ustc.edu.cn/qtproject/archive/qt/4.8/4.8.6/qt-everywhere-opensource-src-4.8.6.tar.gz)
	@make extract-qt-4.8.6

asqt-4.8.6:
	@(cd qt-everywhere-opensource-src-$(qt-version);	\
		./configure \
			-opensource \
			-confirm-license \
			-release -shared \
			-embedded arm \
			-xplatform qws/linux-arm-g++ \
			-depths 16,18,24 \
			-fast \
			-optimized-qmake \
			-pch \
			-qt-sql-sqlite \
			-qt-libjpeg \
			-qt-zlib \
			-qt-libpng \
			-qt-freetype \
			-little-endian -host-little-endian \
			-no-qt3support \
			-no-libtiff -no-libmng \
			-no-opengl \
			-no-mmx -no-sse -no-sse2 \
			-no-3dnow \
			-no-openssl \
			-no-webkit \
			-no-qvfb \
			-no-phonon \
			-no-nis \
			-no-opengl \
			-no-cups \
			-no-glib \
			-no-xcursor -no-xfixes -no-xrandr -no-xrender \
			-no-separate-debug-info \
			-nomake examples -nomake tools -nomake docs \
			-qt-mouse-tslib \
			-I$(rootfs)/include \
			-L$(rootfs)/lib;	\
		make;	\
		make install INSTALL_ROOT=$(rootfs)/qt)

asqt-5.5.1:
	@(echo "  >> I don't know how to build"

asqt: $(download)/qt-everywhere-opensource-src-$(qt-version).tar.gz asqt-$(qt-version)
	@(cd qt-everywhere-opensource-src-$(qt-version);./configure -embedded arm;make;make install INSTALL_ROOT=$(rootfs)/qt)

tslib:
	@git clone https://github.com/kergoth/tslib.git
	@(cd tslib;git checkout 1.1 -f;git st|xargs -i rm {} -fvr)

# something wrong, do manual build step by step
astslib:tslib
	@(cd tslib;./autogen.sh;	\
		echo "av_cv_func_malloc_0_nonnull=yes" > arm-linux-gnueabi.cache;	\
		./configure --host=arm-linux-gnueabi --cache-file=arm-linux-gnueabi.cache \
		-prefix=$(CURDIR)/tslib/install)
	@(cd tslib;make install)
	@(cd tslib;cp -frv install/* $(rootfs))

$(out)/sdcard.img:
	@dd if=/dev/zero of=$@ bs=1G count=2
#	@sudo mkfs.ext3 $@
	@echo " >> use fdisk to creat 2 primary partition, p1=+512M@2048, p2=left"
	@echo "$@Device Boot  Start         End      Blocks   Id  System"
	@echo "$@p1            2048     1050623      524288   83  Linux"
	@echo "$@p2         1050624     4194303     1571840   83  Linux"
	@fdisk $@
	@echo "  >> use parted to mkfs the 2 partition to ext2 filesyste"
	@parted $@

asrootfs:

sdcard:$(out)/sdcard.img asrootfs
	@(cd $(out);mkdir -p tmp;	\
		parted sdcard.img unit B print;	\
		sudo mount -o loop,offset=537919488 sdcard.img tmp;	\
		sudo cp $(rootfs)/* tmp/ -rf;	\
		sudo mkdir -p tmp/dev;	\
		sudo mknod tmp/dev/tty1 c 4 1;	\
		sudo mknod tmp/dev/tty2 c 4 2;	\
		sudo mknod tmp/dev/tty3 c 4 3;	\
		sudo mknod tmp/dev/tty4 c 4 4;	\
		sudo mkdir tmp/proc tmp/tmp tmp/sys;	\
		sudo mkdir -p tmp/mnt/mmcblk0p1;	\
		sudo mkdir -p tmp/smack tmp/root tmp/home/root;	\
		sudo cp ../../rootfs/* tmp/ -rvf;	\
		sudo chmod +x tmp/etc/init.d/rcS;	\
		sudo cp /usr/arm-linux-gnueabi/lib/*.so* tmp/lib)
#	@(cd $(out);sudo mv tmp/lib64/* tmp/lib; sudo rm -fr tmp/lib64; \
		sudo ln -fs ../../../../lib/systemd/system/getty@.service tmp/usr/etc/systemd/system/getty.target.wants/getty@ttyAMA0.service)
#  don't rm inittab and securetty if systemd want to be used
	@(cd $(out);sudo rm -fr tmp/etc/inittab tmp/etc/securetty)
	@(cd $(out);sudo umount tmp;rm tmp -fr)

test_initrd ?= no

$(out)/ramdisk:
	@mkdir -p $@
ifeq ($(test_initrd),no)
	@(echo "   >> please set busybox build option to static"; sleep 1)
	@(cd busybox;make menuconfig;make all;make install CONFIG_PREFIX=$(out)/ramdisk)
endif

ramdisk:$(out)/ramdisk
ifeq ($(test_initrd),yes)
	@(cd $(out)/ramdisk; echo "#include <stdio.h>" > init.c;	 \
		echo "int main(int argc, char* argv[]) { printf(\"Hello World!\\n\"); while(1); }" >> init.c;  \
		$(CROSS_COMPILE)gcc -o init init.c -static;  \
		echo init | cpio -o --format=newc > $(out)/ramdisk.cpio )
else
	@(cd $(out)/ramdisk;	\
		mkdir ./dev;	\
		sudo mknod ./dev/tty1 c 4 1;	\
		sudo mknod ./dev/tty2 c 4 2;	\
		sudo mknod ./dev/tty3 c 4 3;	\
		sudo mknod ./dev/tty4 c 4 4;	\
		mkdir ./proc ./tmp ./sys;	\
		cp ../../../rootfs/* ./ -rvf;	\
		echo "echo \"  >> This is a ramdisk rootfs <<\"" >> ./etc/init.d/rcS;		\
		chmod +x ./etc/init.d/rcS)
	@(cd $(out)/ramdisk; find . | cpio -o --format=newc > $(out)/ramdisk.cpio)
endif

$(out)/initrd.img:
	@dd if=/dev/zero of=$@ bs=4096 count=1024
	@sudo mkfs.ext3 $@

initrd:$(out)/initrd.img
	@(cd $(out);mkdir -p tmp;	\
		sudo mount -t ext3 initrd.img tmp/ -o loop;	\
		sudo mkdir tmp/dev;	\
		sudo mknod tmp/dev/tty1 c 4 1;	\
		sudo mknod tmp/dev/tty2 c 4 2;	\
		sudo mknod tmp/dev/tty3 c 4 3;	\
		sudo mknod tmp/dev/tty4 c 4 4;	\
		sudo mknod tmp/dev/ram b 1 0;  \
		sudo mkdir tmp/proc tmp/tmp tmp/sys;	\
		sudo cp ../../initrd/* tmp/ -rvf;	\
		sudo chmod +x tmp/etc/init.d/rcS;	\
		sudo umount tmp;	\
		rm tmp -fr)

example:
	@(cd example;make all)

clean:
	@(cd kernel;make clean)
	@(cd u-boot;make clean)
	@(cd busybox;make clean)
	@(cd glibc/build;make clean)
	@(cd example;make clean)
	@(cd tslib;make clean;./autogen-clean.sh)
	@(cd can-utils;make clean)
	@(cd canutils;make clean)
	@(cd libsocketcan;make clean)
