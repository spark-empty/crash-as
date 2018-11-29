[!NOCODE!]
/**
    @file    Mcu_RegOperations.m
    @version 2.0.0

    @brief   AUTOSAR Mcu - Register operations.
    @details Register operations.

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

[!// **************************************************************************
[!// Translate 'ItemName' into the item found in 'EnumTranslationList' (e.g. 'WAIT:0;STOP:1;SLEEP:2') 

[!MACRO "TranslateEnum", "ItemName" = "'1'","EnumTranslationList" = "'1'"!][!//
[!VAR "TyKokot" = "412"!][!//  Dummy variable to feed TRESOS parser
[!VAR "TranslationResult" = "substring-after(text:grep(text:split($EnumTranslationList,';'),concat('^',$ItemName,':.*'))[1],':')"!][!//
[!ENDMACRO!][!// 


[!// **************************************************************************
[!// Write 'value' into the selected bit position

[!MACRO "BitGroup2RegValue", "RegValue" = "1", "Value"= "1", "StartBit" = "1", "BitWidth" = "1", "RegWidth"="32"!][!//
[!VAR "TyKokot" = "412"!][!//  Dummy variable to feed TRESOS parse
[!IF "not(num:isnumber($RegValue))"!]   
   [!INFO "Assertion failed: BitGroup2RegValue:RegValue is not a number"!]
   [!ERROR "''"!]
[!ENDIF!]
[!IF "not(num:isnumber($Value))"!]   
   [!INFO "Assertion failed: BitGroup2RegValue:Value is not a number"!]
   [!ERROR "''"!]
[!ENDIF!]

[!VAR "StartBit" = "num:i(number($RegWidth)-number($StartBit)-1)"!]


[!VAR "TmpMask" = "bit:xor((bit:shl(1,32)-1),bit:shl((bit:shl(1,$BitWidth)-1),$StartBit))"!][!//
[!VAR "TmpValue" = "bit:shl($Value,$StartBit)"!][!//
[!VAR "RegValue" = "bit:or(bit:and($RegValue,$TmpMask),$TmpValue)"!][!//
[!ENDMACRO!][!//

[!// **************************************************************************
[!// Translate 'ItemName' and write corresponding value into the register variable

[!MACRO "Enum2RegValue" , "RegValue" = "1", "ItemName" = "'1'", "Descriptor" = "'1'"!]
[!VAR "TyKokot" = "412"!][!//  Dummy variable to feed TRESOS parser
[!VAR "EnumTranslationList" = "concat(text:split($Descriptor,'##')[2],';')"!]
[!VAR "BitDesc" = "text:split($Descriptor,'##')[1]"!]
[!VAR "TranslationResult" = "substring-after(text:grep(text:split($EnumTranslationList,';'),concat('^',$ItemName,':.*'))[1],':')"!][!//
[!VAR "TranslationResult"="string($TranslationResult)"!]

[!IF "string-length($TranslationResult)=0"!]    
   [!INFO!]
   [!"$TranslationResult"!]
   [!"'Error: Translation literal not found: '"!] -[!"$ItemName"!]-
   [!"$EnumTranslationList"!]
   [!ENDINFO!]
   [!ERROR "''"!]
[!ENDIF!]

[!VAR "B1" = "0"!]
[!VAR "B2" = "0"!]
[!VAR "RegWidth" = "32"!]

[!IF "string-length(text:split($BitDesc,',')[1])>0"!]
   [!VAR "B1" = "text:split($BitDesc,',')[1]"!]
[!ENDIF!] 

[!IF "string-length(text:split($BitDesc,',')[2])>0"!]
   [!VAR "B2" = "text:split($BitDesc,',')[2]"!]
[!ELSE!] 
   [!VAR "B2" = "$B1"!]
[!ENDIF!] 

[!IF "string-length(text:split($RegWidth,',')[3])>0"!]
   [!VAR "BitWidth" = "text:split($RegWidth,',')[3]"!]
[!ENDIF!] 

[!VAR "tBitWidth" = "num:i(number($B2)-number($B1)+1)"!]
[!CALL "BitGroup2RegValue", "RegValue" = "$RegValue","Value"= "num:i(number($TranslationResult))", "StartBit" = "number($B2)", "BitWidth" = "$tBitWidth", "RegWidth"="32"!][!//
[!ENDMACRO!][!// 
[!ENDNOCODE!]