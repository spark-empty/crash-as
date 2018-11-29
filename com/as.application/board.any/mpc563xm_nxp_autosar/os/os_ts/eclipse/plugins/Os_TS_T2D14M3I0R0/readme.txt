************************************************************
AUTOSAR OS/xpc563xm v.3.0 
build 3.0.35
TresosECU plugin readme.txt

Freescale(TM) and the Freescale logo are trademarks of Freescale Semiconductor, Inc. 
All other product or service names are the property of their respective owners. 
(C) Freescale Semiconductor, Inc. 2008-2010

************************************************************


This directory contains Os_TS_T2D14M3I0R0 configuration plugin for XPC563XM.

The  Os_TS_T2D14M3I0R0 directory contains the following subdirectories:

Os_TS_T2D14M3I0R0\autosar\               ; OS configuration directory
Os_TS_T2D14M3I0R0\autosar\Os.epd         ; OS configuration file

Os_TS_T2D14M3I0R0\config                 ; TresosECU OS plugin configuration directory
Os_TS_T2D14M3I0R0\config\Os.xdm          ; TresosECU OS plugin configuration file

Os_TS_T2D14M3I0R0\make
Os_TS_T2D14M3I0R0\make\os_defs.mak       ; AUTOSAR OS defines makefile
Os_TS_T2D14M3I0R0\make\os_rules.mak      ; AUTOSAR OS rules makefile

Os_TS_T2D14M3I0R0\META-INF               ; TresosECU OS plugin manifest directory
Os_TS_T2D14M3I0R0\META-INF\MANIFEST.MF   ; TresosECU OS plugin manifest file
Os_TS_T2D14M3I0R0\META-INF\cryptomanifest.mf     ; TresosECU OS plugin cryptomanifest
Os_TS_T2D14M3I0R0\META-INFf\cryptomanifestsig.mf ; TresosECU OS plugin cryptosignature

Os_TS_T2D14M3I0R0\anchors.xml             ; TresosECU OS plugin help definition file
Os_TS_T2D14M3I0R0\plugin.xml             ; TresosECU OS plugin declaration file
Os_TS_T2D14M3I0R0\readme.txt             ; this file


        INSTALLATION

For using this directory with TresosECU, please follow the steps below:

1) Create a text file with the extension ".link" into the TresosECU 
installation in a folder called "links" 
(e.g. <MyTresosIntallation>\links\Os.link)

2) Put the following text in the "Os.link" file: 
"path=<MyDirectoryPath>/<MyDirectoryName>", please make sure the path is 
described with forward slashes.
 
 3) If you change the installation path, please don't forget that it 
 should be  
 "<NewDirectoryPath>/<NewDirectoryName>/eclipse/plugins/Os_TS_T2D14M3I0R0"
 
 For more detail information about plugins installation please refer to 
 original eclipse documentation:  
 http://www.ibm.com/developerworks/opensource/library/os-ecfeat/
 
       FUNCTIONALITY RESTRICTIONS
 				
This plugin has been tested with Tresos 2009.a.

       KNOWN PROBLEMS

Os_TS_T2D14M3I0R0\plugin.xml is prepared in such a way,
that Tresos 2009.a can run SysGen (Tresos External Generator applicable to Os) for created EPC-file.
The command line in Os_TS_T2D14M3I0R0\plugin.xml contains SysGen call applicable
for SC1 and SC2.
To apply SysGen for SC3 and SC4, the user has to modify in Os_TS_T2D14M3I0R0\plugin.xml line:
     value="${pluginPath}\..\..\..\..\ssc\bin\generator\sg.exe  ${outputDir}\epc\project.epc"/>
into
     value="${pluginPath}\..\..\..\..\ssc\bin\generator\sg.exe  -L <your-path-to-LCF-input> -M <your-path-to-LCF-output> ${outputDir}\epc\project.epc"/>

				
The is a number of inconsistencies between AUTOSAR SWS and XML specifications, 
which have been fixed in Os.bmd(epd) file:

-	The SysGen follows the AUTOSAR_SWS_OS specification in part of OIL, which 
	requires that some parameters have to be is set to AUTO if don’t specify 
	them. But XML does not allow "AUTO" for integer parameters. In such situation 
	you may need to “switch of” this parameter, if multiplicity tag allows. 
	The Sysgen will interpret this parameter as “AUTO”.
	  
-	Only INTERNAL driver is supported if “OsCounterType” is HARDWARE. So it will
    be used. There is no any another possibility for configuration.

 				