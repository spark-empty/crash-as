/**
    @file    Mcu_checkvalues.m
    @version 2.0.0

    @brief   AUTOSAR Mcu - File used by the C generation templates.
    @details This file contains macros used by the C generation templates.

    Project AUTOSAR 3.0 MCAL
    Platform PA
    Peripheral FMPLL
    Dependencies none

    ARVersion 3.0.0
    ARRevision ASR_REL_3_0_REV_0003
    ARConfVariant
    SWVersion 2.0.0
    BuildVersion XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223

    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
    All Rights Reserved.
 */
/*==================================================================================================
==================================================================================================*/

/* Macro to check one clock setting */

/* Macro to check one ram section */
[!MACRO "MCheckRamSection"!]
    [!VAR "tmp_m"="0"!]


    [!// stop generation if ram section base address is not aligned to 4 bytes
    [!VAR "tmp_m"="McuRamSectionBaseAddress"!]
    [!IF "$tmp_m mod 4 != 0"!]
        [!INFO!]
*****************
Error: Ram Section Base Address in [!"text:replace(node:path(.),'\/.+\/McuGeneralConfiguration','')"!] is not aligned to 4 bytes (current value: [!"$tmp_m"!])!
*****************
        [!ENDINFO!]
        [!//[!VAR "error"="$error+1"!]
    [!ENDIF!]

    [!// stop generation if ram section size is not multiple of 4
    [!VAR "tmp_m"="McuRamSectionSize"!]
    [!IF "$tmp_m mod 4 != 0"!]
        [!INFO!]
*****************
Error: Ram Section Size in [!"text:replace(node:path(.),'\/.+\/McuGeneralConfiguration','')"!] is not multiple of 4 (current value: [!"$tmp_m"!])!
*****************
        [!ENDINFO!]
        [!//[!VAR "error"="$error+1"!]
    [!ENDIF!]

[!ENDMACRO!]

[!MACRO "BOOL2INT", "VALUE"!]
    [!IF "$VALUE = 'true'"!]
        [!"1"!]
    [!ELSE!]
        [!"0"!]
    [!ENDIF!]
[!ENDMACRO!]

[!MACRO "EDMACR" , "ERGA", "ERCA","EDBG", "EBW", "GRP0PRI", "GRP1PRI", "GRP2PRI", "GRP3PRI"!]
        [!VAR "SERGA"!]
                        [!CALL "BOOL2INT", "VALUE"="$ERGA"!]
        [!ENDVAR!]
        [!VAR "SERCA"!]
                        [!CALL "BOOL2INT", "VALUE"="$ERCA"!]
        [!ENDVAR!]
        [!VAR "SEDBG"!]
                        [!CALL "BOOL2INT", "VALUE"="$EDBG"!]
        [!ENDVAR!]
        [!VAR "SEBW"!]
                        [!CALL "BOOL2INT", "VALUE"="$EBW"!]
        [!ENDVAR!]

        [!"bit:shl($GRP3PRI,14) + bit:shl($GRP2PRI,12) + bit:shl($GRP1PRI,10) + bit:shl($GRP0PRI,8) + bit:shl(1,7) + bit:shl(1,6) + bit:shl($SERGA,3) + bit:shl($SERCA,2) + bit:shl($SEDBG,1) + bit:shl($SEBW,0)"!]
[!ENDMACRO!]

[!MACRO "MCUFlashBIUCR0","GCE","M3PFE","M2PFE","M1PFE","M0PFE","IPFEN", "DPFEN", "PFLIM","BFEN"!]

 [!VAR "GCE"!]
  [!CALL "BOOL2INT", "VALUE"="$GCE"!]
 [!ENDVAR!]
 [!VAR "M3PFE"!]
  [!CALL "BOOL2INT", "VALUE"="$M3PFE"!]
 [!ENDVAR!]
 [!VAR "M2PFE"!]
  [!CALL "BOOL2INT", "VALUE"="$M2PFE"!]
 [!ENDVAR!]
 [!VAR "M1PFE"!]
  [!CALL "BOOL2INT", "VALUE"="$M1PFE"!]
 [!ENDVAR!]
 [!VAR "M0PFE"!]
  [!CALL "BOOL2INT", "VALUE"="$M0PFE"!]
 [!ENDVAR!]
 [!VAR "IPFEN"!]
  [!CALL "BOOL2INT", "VALUE"="$IPFEN"!]
 [!ENDVAR!]
 [!VAR "DPFEN"!]
  [!CALL "BOOL2INT", "VALUE"="$DPFEN"!]
 [!ENDVAR!]
 [!VAR "BFEN"!]
  [!CALL "BOOL2INT", "VALUE"="$BFEN"!]
 [!ENDVAR!]

 [!"bit:shl($GCE,24) + bit:shl($M3PFE,19) + bit:shl($M2PFE,18) + bit:shl($M1PFE,17) + bit:shl($M0PFE,16) + bit:shl($DPFEN,6) +  bit:shl($IPFEN,4) + bit:shl($PFLIM,1) + bit:shl($BFEN,0)"!]

[!ENDMACRO!]

[!MACRO "MCUFlashBIUAPR", "M3AP","M2AP","M1AP","M0AP"!]

 [!"bit:shl($M3AP,6) + bit:shl($M2AP,4) +  bit:shl($M1AP,2) + bit:shl($M0AP,0)"!]

[!ENDMACRO!]

[!MACRO "MCUFlashBIUCR1", "LBCFG"!]

 [!"bit:shl($LBCFG,30)"!]

[!ENDMACRO!]


[!MACRO "MCUFlashclkdep0","F","APC","WWSC","RWSC"!]

[!VAR "tmp_B02APC"="$APC"!]
[!VAR "tmp_B02WWSC"="$WWSC"!]
[!VAR "tmp_B02RWSC"="$RWSC"!]

[!IF "$tmp_B02APC!=8"!]        

    [!IF "($F>0) and ($F<=40000000)"!]
        [!IF "$tmp_B02APC>1"!]
            [!INFO!]
*****************
Warning: The value [!"$tmp_B02APC"!] used for APC is not the recommended one.
*****************
            [!ENDINFO!]
        [!ELSEIF "$tmp_B02APC=1"!]
        
        [!ELSE!]
            [!INFO!]
*****************
Error: The value [!"$tmp_B02APC"!] used for APC is not permitted due to system clock frequency restrictions, using default value
*****************
            [!VAR "tmp_B02APC"="1"!]
            [!ENDINFO!]
        [!ENDIF!]
    [!ELSEIF "($F>40000000) and ($F<=64000000)"!]
        [!IF "$tmp_B02APC>2"!]
            [!INFO!]
*****************
Warning: The value [!"$tmp_B02APC"!] used for APC is not the recommended one.
*****************
            [!ENDINFO!]
        [!ELSEIF "$tmp_B02APC=2"!]
        
        [!ELSE!]
            [!INFO!]
*****************
Error: The value [!"$tmp_B02APC"!] used for APC is not permitted due to system clock frequency restrictions, using default value
*****************
            [!VAR "tmp_B02APC"="2"!]
            [!ENDINFO!]
        [!ENDIF!]
    [!ELSEIF "($F>64000000) and ($F<=80000000)"!]
        [!IF "$tmp_B02APC>3"!]
            [!INFO!]
*****************
Warning: The value [!"$tmp_B02APC"!] used for APC is not the recommended one.
*****************
            [!ENDINFO!]
        [!ELSEIF "$tmp_B02APC=3"!]
        
        [!ELSE!]
            [!INFO!]
*****************
Error: The value [!"$tmp_B02APC"!] used for APC is not permitted due to system clock frequency restrictions, using default value
*****************
            [!VAR "tmp_B02APC"="3"!]
            [!ENDINFO!]
        [!ENDIF!]

    [!ENDIF!]

[!ELSE!]

    [!IF "($F>0) and ($F<=40000000)"!]
        [!VAR "tmp_B02APC"="1"!]
    [!ELSEIF "($F>40000000) and ($F<=64000000)"!]
        [!VAR "tmp_B02APC"="2"!]
    [!ELSEIF "($F>64000000) and ($F<=80000000)"!]
        [!VAR "tmp_B02APC"="3"!]
    [!ELSE!]
        [!VAR "tmp_B02APC"="7"!]
    [!ENDIF!]

[!ENDIF!]

[!IF "$tmp_B02WWSC!=4"!]        
        [!IF "($F>0) and ($F<=80000000)"!]
                [!IF "$tmp_B02WWSC!=1"!]
                        [!INFO!]
                        *****************
                        Error: The value [!"$tmp_B02WWSC"!] used for WWSC is not permitted due to system clock frequency restrictions, using default value
                        *****************
                        [!VAR "tmp_B02WWSC"="1"!]
                        [!ENDINFO!]
                [!ENDIF!]
        [!ELSE!]
                [!IF "$tmp_B02WWSC!=3"!]
                        [!INFO!]
                        *****************
                        Error: The value [!"$tmp_B02WWSC"!] used for WWSC is not permitted due to system clock frequency restrictions, using default value
                        *****************
                        [!VAR "tmp_B02WWSC"="3"!]
                        [!ENDINFO!]
                [!ENDIF!]
        [!ENDIF!]
[!ELSE!]
        [!IF "($F>0) and ($F<=80000000)"!]
                [!VAR "tmp_B02WWSC"="1"!]
        [!ELSE!]
                [!VAR "tmp_B02WWSC"="3"!]
        [!ENDIF!]
[!ENDIF!]


[!IF "$tmp_B02RWSC!=8"!]
    [!IF "($F>0) and ($F<=40000000)"!]
        [!IF "$tmp_B02RWSC>1"!]
            [!INFO!]
*****************
Warning: The value [!"$tmp_B02RWSC"!] used for RWSC is not the recommended one.
*****************
            [!ENDINFO!]
        [!ELSEIF "$tmp_B02RWSC=1"!]
        
        [!ELSE!]
            [!INFO!]
*****************
Error: The value [!"$tmp_B02RWSC"!] used for RWSC is not permitted due to system clock frequency restrictions, using default value
*****************
            [!VAR "tmp_B02RWSC"="1"!]
            [!ENDINFO!]
        [!ENDIF!]
    [!ELSEIF "($F>40000000) and ($F<=64000000)"!]
        [!IF "$tmp_B02RWSC>2"!]
            [!INFO!]
*****************
Warning: The value [!"$tmp_B02RWSC"!] used for RWSC is not the recommended one.
*****************
            [!ENDINFO!]
        [!ELSEIF "$tmp_B02RWSC=2"!]
        
        [!ELSE!]
            [!INFO!]
*****************
Error: The value [!"$tmp_B02RWSC"!] used for RWSC is not permitted due to system clock frequency restrictions, using default value
*****************
            [!VAR "tmp_B02RWSC"="2"!]
            [!ENDINFO!]
        [!ENDIF!]
    [!ELSEIF "($F>64000000) and ($F<=80000000)"!]
        [!IF "$tmp_B02RWSC>3"!]
            [!INFO!]
*****************
Warning: The value [!"$tmp_B02RWSC"!] used for RWSC is not the recommended one.
*****************
            [!ENDINFO!]
        [!ELSEIF "$tmp_B02RWSC=3"!]
        
        [!ELSE!]
            [!INFO!]
*****************
Error: The value [!"$tmp_B02RWSC"!] used for RWSC is not permitted due to system clock frequency restrictions, using default value
*****************
            [!VAR "tmp_B02RWSC"="3"!]
            [!ENDINFO!]
        [!ENDIF!]

    [!ENDIF!]
[!ELSE!]

    [!IF "($F>0) and ($F<=40000000)"!]
        [!VAR "tmp_B02RWSC"="1"!]
    [!ELSEIF "($F>40000000) and ($F<=64000000)"!]
        [!VAR "tmp_B02RWSC"="2"!]
    [!ELSEIF "($F>64000000) and ($F<=80000000)"!]
        [!VAR "tmp_B02RWSC"="3"!]
    [!ELSE!]
        [!VAR "tmp_B02RWSC"="7"!]
    [!ENDIF!]

[!ENDIF!]

 [!"bit:shl($tmp_B02APC,13) + bit:shl($tmp_B02WWSC,11) + bit:shl($tmp_B02RWSC,8)"!]

[!ENDMACRO!]