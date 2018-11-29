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
#common compilers

JAVA=$(JDK)/bin/java
JAVAC=$(JDK)/bin/javac

export verbose ?= yes
ifeq ($(verbose),no)
Q=@
else
Q=
endif

jflags-y += -g -d $(obj-dir)

dir-y += $(src-dir)

VPATH += $(dir-y)

obj-y += $(patsubst %.java,$(obj-dir)/%.class,$(foreach x,$(dir-y),$(notdir $(wildcard $(addprefix $(x)/*,.java)))))	

$(obj-dir):
	@mkdir -p $(obj-dir)

$(exe-dir):
	@mkdir -p $(exe-dir)

$(obj-dir)/%.class:%.java
	@echo
	@echo "  >> JAVAC $(notdir $<)"
	$(Q) $(JAVAC) $(jflags-y) $<	

.PHONY:all exe clean

exe: $(obj-dir) $(exe-dir) $(obj-y)
	@echo "  >> LD $(target-y).exe"
	@echo ">>>>>>>>>>>>>>>>>  BUILD $(exe-dir)/$(target-y)  DONE   <<<<<<<<<<<<<<<<<<<<<<"	
