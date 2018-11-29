
#/**
# * AS - the open source Automotive Software on https://github.com/parai
# *
# * Copyright (C) 2015  AS <parai@foxmail.com>
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

target-y = main

obj-dir = $(CURDIR)/obj
exe-dir = $(CURDIR)/out
src-dir = $(CURDIR)/src
inc-dir = $(CURDIR)/src

download =  $(readlink -f $(CURDIR)/../download)

prj-dir = $(readlink -f $(CURDIR)/../..)

host = $(shell uname)

JDK="C:\Program Files (x86)\Java\jdk1.7.0_01"
include ../make/java.mk

$(src-dir):
	@mkdir -p $(src-dir)

all:exe
	@(cd $(obj-dir);$(JAVA) $(target-y))

clean:
	rm -fr $(obj-dir)

