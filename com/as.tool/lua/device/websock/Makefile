target-y = aws
src-dir = $(CURDIR)
obj-dir = $(CURDIR)/obj
exe-dir = $(CURDIR)/out

prj-dir = $(subst /com/as.tool/lua/device/websock,,$(CURDIR))
INFRASTRUCTURE = $(prj-dir)/com/as.infrastructure
LUA   = $(prj-dir)/com/as.tool/lua
download = $(prj-dir)/release/download

host = $(shell uname)

ifeq ($(host), Linux)
cflags-y += -D__LINUX__
else
cflags-y += -D__WINDOWS__
endif
termux?=no
ifeq ($(termux), yes)
cflags-y += -D__TERMUX__
endif
cflags-y += -I$(INFRASTRUCTURE)/include
ifeq ($(host), Linux)
else
ldflags-y += -lwsock32
endif

dir-y += $(download)/json-c
inc-y += -I$(download)
def-y += -DUSE_JSONC
ifeq ($(host),Linux)
else
def-y += -D_MSC_VER
ifeq ($(msys2),yes)
$(warning need modify the /c/msys64/mingw64/x86_64-w64-mingw32/include/winnt.h line 2100/8474, \
	add "FORCEINLINE" to each of the inline function)
endif
endif
ifeq ($(host),Linux)
# for mingw need to install gnutls from ftp://ftp.gnu.org/gnu/gnutls/w32/gnutls-3.0.22-w32.zip
dir-y += $(download)/libmicrohttpd-0.9.55/src/microhttpd
endif
inc-y += -I$(download)/libmicrohttpd-0.9.55/src/include
ifeq ($(host),Linux)
inc-y += -I$(download)/libmicrohttpd-0.9.55/
else
inc-y += -I$(download)/libmicrohttpd-0.9.55/w32/common
endif
def-y += -DUSE_MICROHTTPD -D__forceinline=inline

$(download)/json-c:
	@(cd $(download);git clone https://github.com/json-c/json-c.git;)
ifeq ($(host),Linux)
	@(cd $(download)/json-c;sh ./autogen.sh; ./configure; make)
else
	@(cd $(download)/json-c;cp config.h.win32 config.h;cp json_config.h.win32 json_config.h)
	@(sed -i "116c //" $(download)/json-c/config.h)
	@(sed -i "117c //" $(download)/json-c/config.h)
	@(sed -i "11c #include <windows.h>" $(download)/json-c/json_util.c)
endif

asjson-c:$(download)/json-c

$(download)/libmicrohttpd-0.9.55.tar.gz:
	@(cd $(download);wget ftp://ftp.gnu.org/gnu/libmicrohttpd/libmicrohttpd-0.9.55.tar.gz)

$(download)/libmicrohttpd-0.9.55:$(download)/libmicrohttpd-0.9.55.tar.gz
	@(cd $(download);tar xf libmicrohttpd-0.9.55.tar.gz)
ifeq ($(host),Linux)
	@(cd $(download)/libmicrohttpd-0.9.55; sh ./configure)
endif
	@(cd $(download)/libmicrohttpd-0.9.55;	\
		sed -i "28c #ifdef HTTPS_SUPPORT" src/microhttpd/connection_https.c; \
		sed -i "200c #endif /* HTTPS_SUPPORT */" src/microhttpd/connection_https.c; \
		rm src/microhttpd/test_*.c -frv)

aslibmicrohttpd:$(download)/libmicrohttpd-0.9.55

default:all

include $(prj-dir)/release/make/posix.mk

all: asjson-c #aslibmicrohttpd
	make lib

clean:clean-obj

