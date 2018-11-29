************************************************************
Freescale AUTOSAR OS/MPC56xxAM v.3.0 RTM
Build 3.0.35  31 Mar 2010
readme.txt  
Freescale(TM) and the Freescale logo are trademarks of Freescale Semiconductor, Inc. 
All other product or service names are the property of their respective owners. 
(C) Freescale Semiconductor, Inc. 2010
************************************************************

This package contains Freescale AUTOSAR OS/MPC56xxAM v.3.0 RTM, build 3.0.35.

The product is developed according to the documents:
- AUTOSAR Specification of Module Operating System v.3.0.1 R.3.0 rev.0003
- Specification of ECU Configuration Parameters V2.0.2  R.3.0 rev.0003
- OSEK/VDX Operating System, Version 2.2.2, 05 July 2004
- OSEK/VDX System Generation, OIL: OSEK Implementation
  Language, Version 2.5, 1 July 2004

The product implements Local Communication class CCCB (message exchange)
according to the documents:
- OSEK/VDX Communication, Version 3.0.3, 20 July 2004

The product implements OSEK Run Time Interface (ORTI)
according to the documents:
- OSEK/VDX OSEK Run Time Interface (ORTI) Part A: 
  Language Specification Version: 2.1.1, 4 Mar 2002
- OSEK/VDX OSEK Run Time Interface (ORTI) Part B: 
  OSEK Objects and Attributes Version 2.1, 17 April 2002 

This build includes direct support of the following MPC derivatives:
- MPC5634M 
- MPC5644A
- MPC5674F

It is strongly recommended that the following compiler versions are used:
- Green Hills MULTI for PowerPC v.5.1.6c revision Fri Aug 14 01:49:59 PDT 2009
- Wind River Compiler for PowerPC version 5.7.0.0 with patch Diab5700-1_wind00175250-PPC-SH-IA-CF.zip
- CodeWarrior Development Studio for Freescale MPC5xxx version 2.5, build 91008

This document contains additional information about the product.
The notes presented are the latest available.

The following topics are covered:

1. Installation
2. Support Information
3. Development hardware and software recommendations
4. Tresos support plugin
5. What's new?
6. Known problems
7. Additional Information
8. Release History


1. Installation

1.1 Installation and license file

Please check the Freescale Support website for new versions and updates
(see section 2 for customer support information).

Installation of Standard Software Core, System Generator 
are protected with FLEXlm.

To get the installation decryption key please contact Freescale support.

1.2. To setup Freescale AUTOSAR OS/MPC56xxAM 3.0 Build 3.0.35 on your hard disk:

1.2.1. Run the AUTOSAROS_3_0_35.exe program.

1.2.2. It is strongly recommended to close all other programs and
       login as Administrator before installation. It helps to avoid
       an access error during system icons installation and updating
       Windows Registry.

NOTES: 1. The full Freescale AUTOSAR OS/MPC56xxAM file set takes about 30 MB of disk space.
       2. About 60 MB of disk space is required for the temporary files
          during installation.
       3. It is required to install Freescale AUTOSAR OS/MPC56xxAM into the directory
          without spaces. (Do not install AUTOSAR OS in a directory like "Program Files").         

1.2.3. Select directories.

Target Directory is a directory for AUTOSAR OS source files,
user documentation and platform specific system generator files.
It is mandatory to select directory names without spaces as it is specified by AUTOSAR.

1.2.4. Select components which you want to install.

You can choose Custom installation and select Freescale AUTOSAR OS components
which have to be installed in Custom Installation dialog box.
By default all components are selected.

1.2.5. Follow the prompts and instructions of the installation program.

1.2.6. The installation program copies to the target directory all needed
       files. The directory tree is described in the file FILELIST.TXT.

NOTE: Installation of Adobe Acrobat Reader 5.0 or later is required to view
      the Freescale AUTOSAR OS/MPC56xxAM User's Manual and Technical Reference.

1.2.7. Properly locate license file. 

Freescale AUTOSAR OS System Generator license file "license.dat"
shall be located on your hard disk in the following folders:
        <Target Directory>\os_freescale_mpc56xxAM\ssc\bin\generator - for System Generator

Note: Installation program copies license file given for source code feature into the above 
folders during the product installation. It is recommended to use a single license file 
containing source code and all other features used by System Generator.

1.3. Freescale AUTOSAR OS/MPC56xxAM Uninstallation

To uninstall Freescale AUTOSAR OS/MPC56xxAM use the 'Freescale AUTOSAR OS/MPC56xxAM v.3.0, build 3.0.35' 
item of the Add/Remove Programs module of the Windows Control Panel.


2. Support Information

To order Freescale products or literature, consult your local sales representative. 

For technical support please use the following Web address:
    http://www.freescale.com/support 

To see the list of current support phone numbers 
under the section labeled "Support" click on the link labeled "Contact Us".


3. Development hardware and software recommendations

3.1. Software requirements

This version of the product is to be used on Pentium PC (or higher)
compatible computer.

The PC has to work under Windows XP/Vista during Freescale AUTOSAR OS installation.

The makefiles provided with OS are written for GNU make v.3.80. 
The CygWin 3.1.17 or later package with make utility shall be properly installed and path to
CygWin binaries shall be in the PATH variable.

Freescale AUTOSAR OS SysGen requires Java Runtime Environment JRE 5.0 Update 6 installed 
on your computer. The JRE can be downloaded from the following URL:
    http://java.sun.com/j2se/1.5.0/download.jsp


3.2. Target hardware requirements

The sample applications can be executed on the following boards:
- XPC56XX EVB board with one of XPC563M, XPC564A or MPC5674ADAT516 daughter card


4. Tresos support plugin

The os_ts folder contains tresos ECU.2009a configuration plugins for supported derivates and 
configuration project sample for OS module. The plugin and example have they own 
"readme.txt" files describing some aspects of their installation. 

For any questions about usage and details about installation and configuration 
please refer to tresosECU documentation.


5. What's new?

- this is the first production release of Freescale AUTOSAR OS v.3.0 for
MPC563xM, MPC564xA and MPC567xF fanilies. 
- Direct support of MPC5674F is added

- Defects fixed:
MTWX39115 - StartScheduleTableRel() incorrect parameters check.
MTWX39211 - Unexpected memory protection exception occurs in the OS after application specific. 
            error hook for non-trusted application.
MTWX39485 - Unexpected memory protection violation after ChainTask() call with task arrival 
            TP violation (in SC4).
MTWX39848 - Wrong Os-Application is terminated when TerminateApplication() is called from 
            trusted function or when memory violation occurs in trusted function code.
MTWX39874 - Wrong write access verifying of non-trusted application data in function OSCheckWriteAccess.
MTWX40374 - StartScheduleTableAbs()/StartScheduleTableRel() incorrect scheduletable state setting.
MTWX40401 - Interrupts remain disabled after direct return from task.
MTWX40592 - Sysgen produces unexpected error processing epc file with several packages.
MTWX40751 - Incorrect processing of Machine Check Exception in SC2.


6. Known problems

- none

7. Additional Information


7.1 Freescale AUTOSAR OS Samples

The Sample applications delivered with the Freescale AUTOSAR OS should
help to learn how to use OS. There are four similar samples - for each
of SC1, SC2, SC3 and SC4 classes provided. Samples are provided in the
"standard" form with makefile.

The samples are provided for the following derivatives:
- MPC5634M 
- MPC5644A
- MPC5674F


8. Release History

Freescale AUTOSAR OS/MPC56xxAM v.3.0 RTM, build 3.0.35 - 
see "What's new" section.

Freescale AUTOSAR OS/MPC56xxAM v.3.0 EAR, build 3.0.30 -
- this is the 1st release of AUTOSAR OS v3.0 for MPC5634M and MPC5646A
- it supports Memory protection on MPC5646A but not on MPC5634M 
  due to absence of MPU on it. 

