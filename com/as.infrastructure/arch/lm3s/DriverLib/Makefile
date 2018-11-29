target-y = lm3sdriver

obj-dir = ./obj
exe-dir = ./
src-dir = ./src

host = $(shell uname)

ifeq ($(host), Linux)
COMPILER_PREFIX = arm-linux-gnueabi-
COMPILER_DIR = /usr
else
COMPILER_PREFIX = arm-none-eabi-
COMPILER_DIR = C:/gcc-arm-none-eabi-4_8-2014q1-20140314-win32

#COMPILER_PREFIX = arm-linux-gnueabihf-
#COMPILER_DIR = C:/opt/Linaro/gcc-linaro-arm-linux-gnueabihf-4.8-2014.04
endif

ifeq ($(host), Linux)
include ../../../../../release/make/cortexm3.gcc.mk
else
include ../../../make/cortexm3.gcc.mk
endif

all:lib
	@rm -fr $(obj-dir)
	