[!NOCODE!][!//

/*!
    @file Adc_RegOperations_PB.m
    @version 0.0.0.0

    \brief AUTOSAR Adc module implementation
    \project
    \author

    \platform PA
    \peripheral ADC_10B
    \dependencies none
    \arversion 3.0.0
  \arrevision ASR_REL_3_0_REV_0003
  \arconfvariant
  \swversion 2.0.0
  \buildversion XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223
    @lastmodusr
    @lastmoddate

    Freescale Semiconductor Inc. & STMicroelectronics
    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
    ALL RIGHTS RESERVED.
*/

[!ENDNOCODE!][!//

[!MACRO "HWRESOURCE" , "SOURCE"!]
    [!NOCODE!]
        [!IF "contains($SOURCE,'eMIOS_A_Ch')"!]
            [!CODE!][!"num:i(text:replace($SOURCE,'eMIOS_A_Ch',''))"!][!ENDCODE!]
            [!ELSEIF "contains($SOURCE,'eMIOS_B_Ch')"!]
            [!CODE!][!"32 + num:i(text:replace($SOURCE,'eMIOS_B_Ch',''))"!][!ENDCODE!]
        [!ELSEIF "contains($SOURCE,'PIT3')"!]
            [!CODE!][!"23"!][!ENDCODE!]
        [!ELSEIF "contains($SOURCE,'PIT7')"!]
            [!CODE!][!"55"!][!ENDCODE!]
        [!ENDIF!]
    [!ENDNOCODE!]
[!ENDMACRO!]
