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
AS  ?= gcc
CC  ?= gcc
LD  = $(CC)
AR  ?= ar
RM  ?= rm

export V ?= 0
ifeq ($(V),1)
Q=
else
Q=@
endif

# generate pre-preocess C files if set to yes
export gen-cpp?=no

cflags-y += ${CFLAGS}
ldflags-y += ${LDFLAGS}

ifeq ($(shell uname), Linux)
cflags-y  += -fPIC
ldflags-y += -fPIC
endif
cflags-y  += -std=gnu99
ldflags-y += -std=gnu99
ifeq ($(shell uname), Linux)
# for call stack trace purpose
trace_callstack ?= yes
ifeq ($(trace_callstack),yes)
cflags-y  += -rdynamic
ldflags-y += -rdynamic
endif
endif
#common flags
debug ?= true
ifeq ($(debug),true)
cflags-y   += -c -g  -O0 -Wall
ldflags-y  += -g  -O0 -Wall	
else
cflags-y   += -c -O2 -Wall
ldflags-y  += -O2 -Wall	
endif

dir-y += $(src-dir)

VPATH += $(dir-y)
inc-y += $(foreach x,$(dir-y),$(addprefix -I,$(x)))

ldflags-y += -Wl,-Map,$(exe-dir)/$(target-y).map	

dllflags-y += -shared
#dllflags-y += --share
	
obj-y += $(patsubst %.c,$(obj-dir)/%.o,$(foreach x,$(dir-y),$(notdir $(wildcard $(addprefix $(x)/*,.c)))))	
obj-y += $(patsubst %.cpp,$(obj-dir)/%.o,$(foreach x,$(dir-y),$(notdir $(wildcard $(addprefix $(x)/*,.cpp)))))	

#common rules
$(obj-dir)/%.o:%.cpp
	@echo
	@echo "  >> CC $(notdir $<)"
	@$(CC) $(cflags-y) $(inc-y) $(def-y) -MM -MF $(patsubst %.o,%.d,$@) -MT $@ $<
ifeq ($(gen-mk),yes)
	@echo "echo \"  >> CC $(notdir $<)\"" >> build.bat
	@echo "$(CC) $(cflags-y) $(inc-y) $(def-y) -o $@ $<" >> build.bat
endif
	$(Q) $(CC) $(cflags-y) $(inc-y) $(def-y) -o $@ $<
	
$(obj-dir)/%.o:%.c
	@echo
	@echo "  >> CC $(notdir $<)"
ifeq ($(gen-cpp),yes)
	@$(CC) $(cflags-y) $(inc-y) $(def-y) -o $@.cpp -E $<
endif
	@$(CC) $(cflags-y) $(inc-y) $(def-y) -MM -MF $(patsubst %.o,%.d,$@) -MT $@ $<
ifeq ($(gen-mk),yes)	
	@echo "echo \"  >> CC $(notdir $<)\"" >> build.bat
	@echo "$(CC) $(cflags-y) $(inc-y) $(def-y) -o $@ $<" >> build.bat
endif
	$(Q) $(CC) $(cflags-y) $(inc-y) $(def-y) -o $@ $<	
	
.PHONY:all clean

$(obj-dir):
	@mkdir -p $(obj-dir)
	
$(exe-dir):
	@mkdir -p $(exe-dir)
		
ifeq ($(host), Linux)
include $(wildcard $(obj-dir)/*.d)
else
-include $(obj-dir)/as.dep
endif

gen_mk_start:
ifeq ($(gen-mk),yes)
	@echo "@echo off" > build.bat
endif	

exe: gen_mk_start $(obj-dir) $(exe-dir) $(obj-y)
	@echo "  >> LD $(target-y).exe"
ifeq ($(gen-mk),yes)	
	@echo "echo \"  >> LD $(target-y).exe\"" >> build.bat
	@echo "$(LD) $(obj-y) $(ldflags-y) -o $(exe-dir)/$(target-y).exe" >> build.bat
endif
	$(Q) $(LD) $(obj-y) $(ldflags-y) -o $(exe-dir)/$(target-y).exe 
	@echo ">>>>>>>>>>>>>>>>>  BUILD $(exe-dir)/$(target-y)  DONE   <<<<<<<<<<<<<<<<<<<<<<"	
	
dll: gen_mk_start $(obj-dir) $(exe-dir) $(obj-y) exe
	@echo "  >> LD $(target-y).DLL"
ifeq ($(gen-mk),yes)	
	@echo "echo \"  >> LD $(target-y).DLL\"" >> build.bat
	@echo "$(CC) $(dllflags-y) $(obj-y) $(ldflags-y) -o $(exe-dir)/$(target-y).dll" >> build.bat
	@echo "pause" >> build.bat
endif
	$(Q) $(CC) $(dllflags-y) $(obj-y) $(ldflags-y) -o $(exe-dir)/$(target-y).dll 
	@echo ">>>>>>>>>>>>>>>>>  BUILD $(exe-dir)/$(target-y)  DONE   <<<<<<<<<<<<<<<<<<<<<<"

lib:$(obj-dir) $(exe-dir) $(obj-y)
	@echo "  >> LD $(target-y).LIB"
	$(Q) $(AR) -r $(exe-dir)/lib$(target-y).a $(obj-y)
	@echo ">>>>>>>>>>>>>>>>>  BUILD $(exe-dir)/$(target-y)  DONE   <<<<<<<<<<<<<<<<<<<<<<"		

clean-obj:
	@rm -fv $(obj-dir)/*
	@rm -fv $(exe-dir)/*
	
clean-obj-src:clean-obj
	@rm -fv $(src-dir)/*

