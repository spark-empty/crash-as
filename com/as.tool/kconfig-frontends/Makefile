# AS - the open source Automotive Software on https://github.com/parai
# Copyright (C) 2016  AS <parai@foxmail.com>
# Simple Makefie to build kconfig both on windows and linux
# prepare: pacman -S ncurses-devel
# run: cmd /C kconfig-mconf.exe Kconfig
KCONF ?= mconf

TARGET = kconfig-$(KCONF)

src-dir = $(CURDIR)

host = $(shell uname)

export V ?= 0
ifeq ($(V),1)
Q=
else
Q=@
endif

CC = gcc
LD = gcc
BISON = bison

ifeq ($(host), MINGW64_NT-10.0)
msys2 = yes
endif
ifeq ($(host), MSYS_NT-10.0)
msys2 = yes
endif

CFLAGS += -c -O3
CFLAGS += -DCURSES_LOC=\"ncurses.h\"
CFLAGS += -DROOTMENU=\"Configuration\"
CFLAGS += -DCONFIG_=\"CONFIG_\"
CFLAGS += -DKBUILD_NO_NLS
CFLAGS += -I$(src-dir)/libs
CFLAGS += -I$(src-dir)/libs/parser
LDFLAGS += -O3
LIBS += -lncurses
CFLAGS += -DGPERF_LEN_TYPE=size_t
ifeq ($(host), Linux)
else
LIBS += -lregex
CFLAGS += -D__WINDOWS__
ifeq ($(msys2), yes)
CFLAGS += -I/c/msys64/usr/include
else
$(error MinGW is not suppoterd)
endif
endif

PARSER += $(src-dir)/libs/parser/yconf.c
PARSER += $(src-dir)/libs/parser/lconf.c
PARSER += $(src-dir)/libs/parser/hconf.c
objs-y += $(src-dir)/libs/lxdialog/checklist.o
objs-y += $(src-dir)/libs/lxdialog/inputbox.o
objs-y += $(src-dir)/libs/lxdialog/menubox.o
objs-y += $(src-dir)/libs/lxdialog/textbox.o
objs-y += $(src-dir)/libs/lxdialog/util.o
objs-y += $(src-dir)/libs/lxdialog/yesno.o
objs-y += $(src-dir)/libs/parser/yconf.o
objs-y += $(src-dir)/frontends/$(KCONF)/$(KCONF).o


default: all

%.o:%.c
	@echo
	@echo "  >> CC $(notdir $<)"
	$(Q) $(CC) $(CFLAGS) -o $@ $<

$(src-dir)/libs/parser/yconf.c:$(src-dir)/libs/parser/yconf.y
	bison -v -t -d $< -o $@

$(src-dir)/libs/parser/lconf.c:$(src-dir)/libs/parser/lconf.l
	flex -o$@ $<

$(src-dir)/libs/parser/hconf.c:$(src-dir)/libs/parser/hconf.gperf
	gperf -t --output-file $@ -a -C -E -g -k 1,3,$$ -p -t $<

all: $(PARSER) $(objs-y)
	@echo
	@echo "  >> LD $(TARGET)"
	$(Q) $(LD) $(LDFLAGS) $(objs-y) $(LIBS) -o $(TARGET)

clean:
	$(Q) rm -fv $(PARSER) $(objs-y) $(TARGET)
