# for the purpose to study AGL apbinder

LIB_MH_VERSION?=0.9.54
export LIBMICRODEST?=/usr
export PKG_CONFIG_PATH=${LIBMICRODEST}/lib/pkgconfig

default:all

$(CURDIR)/libmicrohttpd-${LIB_MH_VERSION}.tar.gz:
	@wget https://ftp.gnu.org/gnu/libmicrohttpd/libmicrohttpd-${LIB_MH_VERSION}.tar.gz

$(CURDIR)/libmicrohttpd-${LIB_MH_VERSION}:$(CURDIR)/libmicrohttpd-${LIB_MH_VERSION}.tar.gz
	@tar -xzf libmicrohttpd-${LIB_MH_VERSION}.tar.gz

$(CURDIR)/app-framework-binder:
	git clone https://gerrit.automotivelinux.org/gerrit/src/app-framework-binder

$(CURDIR)/low-level-can-service:
	git clone https://gerrit.automotivelinux.org/gerrit/p/apps/low-level-can-service.git

$(CURDIR)/CAN_signaling_OBSOLETE:
	git clone https://github.com/iotbzh/CAN_signaling_OBSOLETE.git
	@(cd CAN_signaling_OBSOLETE/CAN-binder/conf.d/app-templates; mkdir cmake; cd cmake; \
	    wget https://raw.githubusercontent.com/iotbzh/CAN_signaling_OBSOLETE/35985a359af2f6a48be151c4c2414a83cb4e91dc/CAN-binder/etc/macros.cmake)

prepare:
	sudo apt-get install libmagic-dev libjson-c-dev uuid-dev libsystemd-dev libssl-dev \
		libasound2-dev libpulse-dev librtlsdr-dev libglib2.0-dev libgupnp-av-1.0-dev \
		gcc make pkg-config cmake
	@touch .prepare.done

all: $(CURDIR)/libmicrohttpd-${LIB_MH_VERSION} $(CURDIR)/app-framework-binder \
	$(CURDIR)/CAN_signaling_OBSOLETE
	@(cd libmicrohttpd-${LIB_MH_VERSION};./configure --prefix=${LIBMICRODEST}; \
		make;sudo make install-strip)
	@(cd $(CURDIR)/app-framework-binder;mkdir -p build;cd build; \
		cmake ..; make; sudo make install)
	@(cd $(CURDIR)/CAN_signaling_OBSOLETE; ./build.sh)

clean:
	@(cd libmicrohttpd-${LIB_MH_VERSION};make clean)
	@rm -fr $(CURDIT)/app-framework-binder/build

