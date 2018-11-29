#
#       example/powerpc/crt0.s: startup for Bubble Sort example
#
#       *** Simplified version for Bubble Sort example only. ***
#       *** See src/crtppc/crt0.s for complete version.      ***
#       --------------------------------------------------------
#
#       Copyright 1997-1998 Diab Data, Inc.

        .file           "crt0.c"
        .text
        .extern         usr_init
        .globl          _start
        .align          2
        addi            r0,r0,0         # Debuggers may object to starting at 0.

_start:
        
        .ifdef FLASH_START
        bl  usr_init
        .endif

        addis           r11,r0,__SP_INIT@ha     # Initialize stack pointer r1 to
        addi            r1,r11,__SP_INIT@l      # value in linker command file.
        addis           r13,r0,_SDA_BASE_@ha    # Initialize r13 to sdata base
        addi            r13,r13,_SDA_BASE_@l    # (provided by linker).
        addis           r2,r0,_SDA2_BASE_@ha    # Initialize r2 to sdata2 base
        addi            r2,r2,_SDA2_BASE_@l     # (provided by linker).
        addi            r0,r0,0                 # Clear r0.
        stwu            r0,-64(r1)              # Terminate stack.

#
# Insert other initialize code here.
#

        bl              __init_main     # Finishes initialization (copies .data
                                        # ROM to RAM, clears .bss), then calls
                                        # example main(), which calls exit(),
                                        # which halts.
