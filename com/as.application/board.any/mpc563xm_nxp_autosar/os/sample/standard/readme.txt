************************************************************
AUTOSAR OS/MPC56xxAM v.3 sample
readme.txt

Freescale(TM) and the Freescale logo are trademarks of Freescale Semiconductor, Inc. 
All other product or service names are the property of their respective owners. 
(C) Freescale Semiconductor, Inc. 2009-2010

************************************************************
The samples for the following derivatives are provided:
- MPC5634M 
- MPC5644A
- MPC5674F

There are four samples:
- for scalability class 1 (SC1) to work in internal flash memory
- for scalability class 2 (SC2) to work in internal RAM
- for scalability class 3 (SC3) to work in internal RAM
- for scalability class 4 (SC4) to work in internal RAM


The sample directory contains the following subdirectories:

sample\standard\                          ; sample common files;

sample\standard\readme.txt                ; this file
sample\standard\common.mak                ; GNU makefile with common definitions and rules
sample\standard\56xxAM.cmm                ; Lauterbach command file for board initialization

sample\standard\sc1\                      ; sample for SC1
sample\standard\sc1\makefile              ; GNU makefile for building SC1 sample
sample\standard\sc1\src\                  ; SC1 sample source code files
sample\standard\sc1\flash.cmm             ; Lauterbach script for burning sample into flash
sample\standard\sc1\src\sample1.epc       ; SC1 sample AUTOSAR XML OS configuration file
sample\standard\sc1\src\sample1.oil       ; SC1 sample AUTOSAR OS configuration file
sample\standard\sc1\src\sample.h          ; SC1 sample data types
sample\standard\sc1\src\memmap.h          ; SC1 sample memory mapping
sample\standard\sc1\src\samplerv1.c       ; SC1 sample source code
sample\standard\sc1\src\samplets1.c       ; SC1 sample source code
sample\standard\sc1\lcf\                  ; linker command files
sample\standard\sc1\lcf\sample1.lcf       ; linker command file for the CodeWarrior compiler
sample\standard\sc1\lcf\sample1.dld       ; linker command file for the WindRiver compiler
sample\standard\sc1\lcf\sample1.ld        ; linker command file for the GreenHills compiler

sample\standard\sc2\                      ; sample for SC2
sample\standard\sc2\makefile              ; GNU makefile for building SC2 sample
sample\standard\sc2\src\                  ; SC2 sample source code files
sample\standard\sc2\src\sample2.epc       ; SC2 sample AUTOSAR XML OS configuration file
sample\standard\sc2\src\sample2.oil       ; SC2 sample AUTOSAR OS configuration file
sample\standard\sc2\src\sample.h          ; SC2 sample data types
sample\standard\sc2\src\memmap.h          ; SC2 sample memory mapping
sample\standard\sc2\src\samplerv2.c       ; SC2 sample source code
sample\standard\sc2\src\samplets2.c       ; SC2 sample source code
sample\standard\sc2\lcf\                  ; linker command files
sample\standard\sc2\lcf\sample2.lcf       ; linker command file for the CodeWarrior compiler
sample\standard\sc2\lcf\sample2.dld       ; linker command file for the WindRiver compiler
sample\standard\sc2\lcf\sample2.ld        ; linker command file for the GreenHills compiler

sample\standard\sc3\                      ; sample for SC3
sample\standard\sc3\makefile              ; GNU makefile for building SC3 sample
sample\standard\sc3\src\                  ; SC3 sample source code files
sample\standard\sc3\src\sample3.epc       ; SC3 sample AUTOSAR XML OS configuration file
sample\standard\sc3\src\sample3.oil       ; SC3 sample AUTOSAR OS configuration file
sample\standard\sc3\src\sample.h          ; SC3 sample data types
sample\standard\sc3\src\memmap.h          ; SC3 sample memory mapping
sample\standard\sc3\src\samplerv3.c       ; SC3 sample source code
sample\standard\sc3\src\samplets3.c       ; SC3 sample source code
sample\standard\sc3\lcf\                  ; linker command files
sample\standard\sc3\lcf\sample3.lcf       ; linker command file for the CodeWarrior compiler
sample\standard\sc3\lcf\sample3.dld       ; linker command file for the WindRiver compiler
sample\standard\sc3\lcf\sample3.ld        ; linker command file for the GreenHills compiler

sample\standard\sc4\                      ; sample for SC4
sample\standard\sc4\makefile              ; GNU makefile for building SC4 sample
sample\standard\sc4\src\                  ; SC4 sample source code files
sample\standard\sc4\src\sample4.epc       ; SC4 sample AUTOSAR XML OS configuration file
sample\standard\sc4\src\sample4.oil       ; SC4 sample AUTOSAR OS configuration file
sample\standard\sc4\src\sample.h          ; SC4 sample data types
sample\standard\sc4\src\memmap.h          ; SC4 sample memory mapping
sample\standard\sc4\src\samplerv4.c       ; SC4 sample source code
sample\standard\sc4\src\samplets4.c       ; SC4 sample source code
sample\standard\sc4\lcf\                  ; linker command files
sample\standard\sc4\lcf\sample4.lcf       ; linker command file for the CodeWarrior compiler
sample\standard\sc4\lcf\sample4.dld       ; linker command file for the WindRiver compiler
sample\standard\sc4\lcf\sample4.ld        ; linker command file for the GreenHills compiler

sample\standard\hwspec                    ; Hardware-specific and compiler-specific files
sample\standard\hwspec\__ppc_eabi_init.c  ; Interface for board-level initialization and user-level initialization
sample\standard\hwspec\__start.c          ; Metrowerks PowerPC EABI Runtime Initialization 
sample\standard\hwspec\crts.s             ; DIAB Runtime Initialization
sample\standard\hwspec\flashrchw.c        ; RCHW data for BAM boot
sample\standard\hwspec\vector.c           ; Vector table                             
                   

Before starting building process ensure that the following path variables 
are set correctly by OS installation:
in common.mak file:
- CWDIR        - CodeWarrior Compiler path
- GHSDIR       - GreenHills Compiler path
- DIABDIR      - WindRiver Compiler path
- CYGWINDIR    - Cygwin package binary path
- TRESOS_BASE  - tresos Studio path
in each project makefile:
- PROJECT_ROOT - Project path (path to desired sample)
- SSC_ROOT     - standard software core (SSC) path

To build each sample :
 1. Go to directory where desired sample is located ('sample\standard\scN',
    where N is 1..4)

 2. Edit file sample\standard\scN\src\sampleN.oil, where N is 1..4,
    line 'TargetMCU = MPC5634M'. In the line change word 'MPC5634M' as follow:
        'MPC5644A' - for MPC5644A
        'MPC5634M' - for MPC5634M
        'MPC5674F' - for MPC5674F        
    NOTE: This string shall correspond to mcu=xxx option of make file.

 3. Run GNU make utility ver. 3.80:
    
        make [-s] <target> ... [<variable>=<value>] ...

           Targets:
              all   - build sample (target by default)
              clean - clear files for this sample
 
           Variables:
              compiler - type of compiler:
                          ghsppc (by default)  - GreenHills compiler  
                          diabppc              - WindRiver compiler
                          cwppc                - CodeWarrior compiler 
              mcu      - type of derivative: 
                           5634M (by default for sc1,sc2) - for MPC5634M
                           5644A (by default for sc3,sc4) - for MPC5644A 
                           5674F - for MPC5674F                        
              debug    - Generate Lauterbach command file.
                         As a result the file sample\standard\scN\output\bin\sampleN.cmm,
                         where N is 1..4, is created.
                           no (by default)
                           yes
              cfg      - config file source: OIL, EPC or XDM  configutation file
                         (value by default: OIL)

           Examples:
              make                         - build sample
                                             with default compiler - GreenHills
              make compiler=diabppc        - build sample with DIAB compiler
              make debug=yes               - build sample with default (GreenHills) compiler
                                             with generation of Lauterbach command file
              make clean                   - clear file this sample

Note: if you don't have make utility ver.3.80 you can take it from 
      ..\REDIST folder. 

After building process is completed, the following directories are created:

sample\standard\sc1\output\obj - contains object files and configuration files generated by SysGen
sample\standard\sc1\output\bin - contains executable/loadable file, map file, orti file
sample\standard\sc2\output\obj - contains object files and configuration files generated by SysGen
sample\standard\sc2\output\bin - contains executable/loadable file, map file, orti file
sample\standard\sc3\output\obj - contains object files and configuration files generated by SysGen
sample\standard\sc3\output\bin - contains executable/loadable file, map file, orti file
sample\standard\sc4\output\obj - contains object files and configuration files generated by SysGen
sample\standard\sc4\output\bin - contains executable/loadable file, map file, orti file     

To clean each sample project go to directory where desired sample
is located and run:
   make clean

The Sample applications can be executed on the Freescale XPC56XX EVB board 
and on the MPC5674EVBFXMB board. 

Execution Instructions.

As a result of build process corresponding '.ELF' file is created.
It should be loaded and executed on Evaluation Board. To ease this process for
Lauterbach debugging interface it is posssible to generate Lauterbach
script for each sample. To do so please use ‘debug=yes’ makefile option (without
quotes) during ‘make’ utility invocation.

Sample for Scalability Class 1 (sample\standard\sc1) are intended to be executed
from flash. Thus ‘.ELF’ file for scalability class 1 shall be burned into
on-chip flash. If you utilize Lauterbach debugger this could be done by
execution of .\sample\standard\sc1\output\bin\sample1.cmm file.

Additionally, sample for scalability class 1 changes state of GPIO190 pin with
period about 1sec. It is done to indicate execution from flash if sample is 
started w/o debugger. GPIO190 should be connected to LED header on EVB for 
visual indication of the pin state.

Tresos Studio 2009.a-sr.1 configuration sample

All samples makefile can be called with options cfg=xdm or cfg=epc.
If you choose 'epc' the sampleN.epc file will be used by SysGen for code
generation instead of sampleN.oil (where N is 1..4). 
If you use 'xdm' make will use to Os.xdm file provided 
by Tresos Studio configuration sample 
(directory  \os_ts\eclipse\workspace\os_sample_scN) for code generation 
(where N is 1..4). 
The path to the XDM file is defined by  XDM_SAMPLE_PATH  variable in 
makefile for scN (where N is 1..4).

os_sample_sc1\config\OS.xdm, os_sample_sc2\config\OS.xdm,
sample1.epc and sample2.epc were prepared for MPC5634M.
os_sample_sc3\config\OS.xdm, os_sample_sc4\config\OS.xdm,
sample3.epc and sample4.epc were prepared for MPC5644A.

The "sampleN.epc" is configuration information in AUTOSAR XML format. 
This file can be imported by Tresos Studio 2009.a-sr.1.  Please refer 
to the Tresos Studio "User Guide" chapter "4.11. Importing/Exporting" 
how it should be done. 

In some cases the studio may report about the 
following error after import:
The value of node "/AUTOSAR/TOP-LEVEL-PACKAGES/OS/ELEMENTS/Os/OsAppMode
/OsAppMode_0/OsAppModeId" is no long-value: ""

If so "OsAppMode_0" attribute has to be deleted to create correct
configuration.

Please note that existing make file doesn't support full project build
with Tresos Studio. The configuration can be modified in Tresos
Studio. After that code generation can be called from UI or command
line. Please refer to Tresos Studio "User Guide" chapter "4.10. Generating 
code for projects" and chapter "4.12. Working with the command line" how it can be done.  
The make file has to be modified with correct path to the results of code
generation to use them.




