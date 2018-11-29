# Make file that for the study purpose of cryptography on host machine ubuntu

target-y = ascrypto

obj-dir = $(CURDIR)/obj
exe-dir = $(CURDIR)/out
src-dir = $(CURDIR)/src
inc-dir = $(CURDIR)/src

download = $(CURDIR)/../download

host = $(shell uname)

ifeq ($(host), Linux)
PY27 = python2
PY34 = python3
else
PY27 = C:Python27/python
PY34 = C:Python34/python
endif

libraries += $(download)/libtomcrypt-1.17/libtomcrypt.a
ldflags-y += -L$(download)/libtomcrypt-1.17 -ltomcrypt
inc-y += -I$(download)/libtomcrypt-1.17/src/headers

libraries += $(download)/cryptopp-CRYPTOPP_5_6_5/libcryptopp.a
ldflags-y += -L$(download)/cryptopp-CRYPTOPP_5_6_5 -lcryptopp
inc-y += -I$(download)/cryptopp-CRYPTOPP_5_6_5

VPATH += $(download)/libtomcrypt-1.17/demos
obj-y += $(obj-dir)/encrypt.o

#cflags-y += -Wall -Wsign-compare -W -Wshadow -Wno-unused-parameter -DLTC_SOURCE -funroll-loops -fomit-frame-pointer

LNFS  = $(PY34) $(CURDIR)/../make/lnfs.py

trace_callstack = no

default:all

include ../make/posix.mk

$(download)/libtomcrypt-1.17/libtomcrypt.a:
	@(cd $(download)/libtomcrypt-1.17;make clean;make library)

$(download)/cryptopp-CRYPTOPP_5_6_5/libcryptopp.a:
	@(cd $(download)/cryptopp-CRYPTOPP_5_6_5; make clean; make)

all: $(src-dir) $(download) $(libraries) exe

clean: clean-obj

$(src-dir):
	@mkdir -p $@

$(download):
	@mkdir -p $@

$(download)/crypt-1.17.tar.bz2:
	@(cd $(download);	\
		wget https://github.com/libtom/libtomcrypt/releases/download/1.17/crypt-1.17.tar.bz2;	\
		)

$(download)/libtomcrypt-1.17:$(download)/crypt-1.17.tar.bz2
	@(cd $(download);	\
		bzip2 -dk $(download)/crypt-1.17.tar.bz2;	\
		tar -xf $(download)/crypt-1.17.tar -C .;	\
		rm $(download)/crypt-1.17.tar )

$(download)/ltm-1.0.tar.xz:
	@(cd $(download);	\
		wget https://github.com/libtom/libtommath/releases/download/v1.0/ltm-1.0.tar.xz;	\
		)

$(download)/libtommath-1.0:$(download)/ltm-1.0.tar.xz
	@(cd $(download);	\
		xz -dk $(download)/ltm-1.0.tar.xz;	\
		tar -xf $(download)/ltm-1.0.tar -C .;	\
		rm $(download)/ltm-1.0.tar )

$(download)/tfm-0.13.tar.bz2:
	@(cd $(download);	\
		wget https://github.com/libtom/tomsfastmath/releases/download/v0.13.0/tfm-0.13.tar.bz2;	\
		)

$(download)/tomsfastmath-0.13:$(download)/tfm-0.13.tar.bz2
	@(cd $(download);	\
		bzip2 -dk $(download)/tfm-0.13.tar.bz2;	\
		tar -xf $(download)/tfm-0.13.tar -C .;	\
		rm $(download)/tfm-0.13.tar )

$(download)/ltp-0.04.tar.bz2:
	@(cd $(download);	\
		wget https://github.com/libtom/libtompoly/releases/download/0.04/ltp-0.04.tar.bz2;	\
		)

$(download)/libtompoly-0.04:$(download)/ltp-0.04.tar.bz2
	@(cd $(download);	\
		bzip2 -dk $(download)/ltp-0.04.tar.bz2;	\
		tar -xf $(download)/ltp-0.04.tar -C .;	\
		rm $(download)/ltp-0.04.tar )

$(download)/ltf-0.02.tar.bz2:
	@(cd $(download);	\
		wget https://github.com/libtom/libtomfloat/releases/download/0.02/ltf-0.02.tar.bz2;	\
		)

$(download)/libtomfloat-0.02:$(download)/ltf-0.02.tar.bz2
	@(cd $(download);	\
		bzip2 -dk $(download)/ltf-0.02.tar.bz2;	\
		tar -xf $(download)/ltf-0.02.tar -C .;	\
		rm $(download)/ltf-0.02.tar )

aslibtom:	$(download)/libtomcrypt-1.17	\
			$(download)/libtommath-1.0		\
			$(download)/tomsfastmath-0.13	\
			$(download)/libtompoly-0.04		\
			$(download)/libtomfloat-0.02

$(download)/CRYPTOPP_5_6_5.tar.gz:
	@(cd $(download); wget https://github.com/weidai11/cryptopp/archive/CRYPTOPP_5_6_5.tar.gz)

$(download)/cryptopp-CRYPTOPP_5_6_5:$(download)/CRYPTOPP_5_6_5.tar.gz
	@(cd $(download); tar xf $(download)/CRYPTOPP_5_6_5.tar.gz)

ascryptopp:$(download)/cryptopp-CRYPTOPP_5_6_5


