# for windows, install mysys2 and use 
# https://github.com/Alexpux/MINGW-packages/tree/master/mingw-w64-qemu
# to build the qemu locally

# cd ${package-name}
# MINGW_INSTALLS=mingw64 makepkg-mingw -sLf
# pacman -U ${package-name}*.pkg.tar.xz

obj-$(CONFIG_PCI) += ascan.o
obj-$(CONFIG_PCI) += asnet.o
obj-$(CONFIG_PCI) += asblk.o
LIBS += -lpyas -L../hw/char -L./hw/char

test-asnet:
ifeq ($(shell uname), Linux)
	gcc -D__TAPTEST__ asnet.c -o asnet
else
	gcc -D__TAPTEST__ asnet.c -o asnet -I/mingw64/include /mingw64/lib/Packet.lib /mingw64/lib/wpcap.lib
endif
