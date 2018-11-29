# specific target as libcan.a
target-y = FreeRTOS

obj-dir = ./obj
exe-dir = ./out
src-dir = ./Source

dir-y += ./Config

obj-y += $(obj-dir)/portable.o		\
		 $(obj-dir)/heap_3.o

VPATH += ./Source/portable/MemMang	\
		 ./Source/portable/MSVC-MingW

inc-y += -I./Source/include		 
inc-y += -I./Source/portable/MemMang	\
		 -I./Source/portable/MSVC-MingW
		 
ldflags-y += -lm -lwinmm		 

include ../../../../release/make/Makefile

	
all: exe

clean: clean-obj
	
	
 

