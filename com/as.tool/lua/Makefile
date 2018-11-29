
host = $(shell uname)
ifeq ($(host), Linux)
PLATFORM = linux
else
PLATFORM = mingw
endif

lua:
	@make $(PLATFORM) -f lua.mk
	
all:lua

clean:
	@make clean -f lua.mk
	
