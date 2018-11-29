# Make file that for the study purpose of lwip on host machine ubuntu

target-y = aslwip

obj-dir = $(CURDIR)/obj
exe-dir = $(CURDIR)/out
src-dir = $(CURDIR)/src
inc-dir = $(CURDIR)/src

download = $(CURDIR)/../../download

INFRASTRUCTURE = $(CURDIR)/../../../com/as.infrastructure

ldflags-y += -lpthread
ldflags-y += -lstdc++ -lm

inc-y += -I$(INFRASTRUCTURE)/include
inc-y += -I$(download)/lwip/src/include
inc-y += -I$(download)/lwip/src/include/ipv4
inc-y += -I$(download)/lwip-contrib/ports/unix/include

VPATH += $(INFRASTRUCTURE)/diagnostic/Det
obj-y += $(obj-dir)/asdebug.o
def-y += -DUSE_DET -D__LINUX__

dir-y += $(download)/lwip/src/core
dir-y += $(download)/lwip/src/core/ipv4
dir-y += $(download)/lwip/src/api
dir-y += $(download)/lwip/src/netif
dir-y += $(download)/lwip/src/ppp

dir-y += $(download)/lwip-contrib/ports/unix
dir-y += $(download)/lwip-contrib/ports/unix/netif
dir-y += $(download)/lwip-contrib/ports/unix/proj/lib

dir-y += $(download)/lwip-contrib/apps/httpserver
dir-y += $(CURDIR)/app

def-y += -DLWIP_DEBUG=LWIP_DBG_ON
def-y += -DIP_DEBUG=LWIP_DBG_ON
def-y += -DTCP_DEBUG=LWIP_DBG_ON
def-y += -DTCP_INPUT_DEBUG=LWIP_DBG_ON

def-y += -DDELIF_DEBUG=LWIP_DBG_ON
def-y += -DSIO_FIFO_DEBUG=LWIP_DBG_ON
def-y += -DTAPIF_DEBUG=LWIP_DBG_ON

include ../../make/posix.mk

all: $(src-dir) $(download) aslwip exe


clean: clean-obj

$(src-dir):
	@mkdir -p $@

$(download):
	@mkdir -p $@

$(download)/lwip:
	@(cd $(download);git clone git://git.savannah.nongnu.org/lwip.git;cd lwip;git checkout STABLE-1_4_1)

$(download)/lwip-contrib:
	@(cd $(download);git clone git://git.savannah.nongnu.org/lwip/lwip-contrib.git;	\
		cd lwip-contrib;git checkout STABLE-1_4_1;	\
		git apply $(CURDIR)/app/0001-tap0-bringup-for-lwip-1.4.1.patch)

aslwip: $(download)/lwip $(download)/lwip-contrib

