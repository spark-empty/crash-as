[!CODE!][!//
/**
    @file    Icu_Cfg.c
    @version 2.0.0

    @brief   AUTOSAR Icu - contains the data exported by the Icu module
    @details Contains the information that will be exported by the module, as requested by Autosar.


    Project AUTOSAR 3.0 MCAL
    Platform PA
    Peripheral eMIOS200
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

/**
@page misra_violations MISRA-C:2004 violations

@section Icu_Cfg_c_1
Violates MISRA-C 2004 Advisory Rule 19.1 "#include" preceded by non preproc directives.
This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003.

@section Icu_Cfg_c_2
Violates MISRA-C 2004 Advisory Rule 19.15, Precautions shall be taken in order to prevent the
contents of a header file being included twice
This is not a violation since all header files are protected against multiple inclusions
*/


#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Icu.h"
#include "Icu_LLD.h"


#ifdef ICU_PRECOMPILE_SUPPORT

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/**
@{
@brief   Configuration source file version information
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define ICU_VENDOR_ID_PCCFG_C         43
#define ICU_AR_MAJOR_VERSION_PCCFG_C  3
#define ICU_AR_MINOR_VERSION_PCCFG_C  0
#define ICU_AR_PATCH_VERSION_PCCFG_C  0
#define ICU_SW_MAJOR_VERSION_PCCFG_C  2
#define ICU_SW_MINOR_VERSION_PCCFG_C  0
#define ICU_SW_PATCH_VERSION_PCCFG_C  0
/**@}*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/** @remarks Covers ICU005 */
/* Check Icu_Cfg.c against Icu.h file versions */
#if (ICU_VENDOR_ID_PCCFG_C != ICU_VENDOR_ID)
#error "Icu_Cfg.c and Icu.h have different vendor IDs"
#endif
#ifdef CHECK_AUTOSAR_VERSION
#if ((ICU_AR_MAJOR_VERSION_PCCFG_C != ICU_AR_MAJOR_VERSION) || \
     (ICU_AR_MINOR_VERSION_PCCFG_C != ICU_AR_MINOR_VERSION) || \
     (ICU_AR_PATCH_VERSION_PCCFG_C != ICU_AR_PATCH_VERSION))
  #error "AutoSar Version Numbers of Icu_Cfg.c and Icu.h are different"
#endif
#endif
#if ((ICU_SW_MAJOR_VERSION_PCCFG_C != ICU_SW_MAJOR_VERSION) || \
     (ICU_SW_MINOR_VERSION_PCCFG_C != ICU_SW_MINOR_VERSION) || \
     (ICU_SW_PATCH_VERSION_PCCFG_C != ICU_SW_PATCH_VERSION))
       #error "Software Version Numbers of Icu_Cfg.c  and Icu.h are different"
#endif

/* Check Icu_Cfg.c against Icu_LLD.h file versions */
#if (ICU_VENDOR_ID_PCCFG_C != ICU_LLD_VENDOR_ID)
#error "Icu_Cfg.c and Icu_LLD.h have different vendor IDs"
#endif
#ifdef CHECK_AUTOSAR_VERSION
#if ((ICU_AR_MAJOR_VERSION_PCCFG_C != ICU_LLD_AR_MAJOR_VERSION) || \
     (ICU_AR_MINOR_VERSION_PCCFG_C != ICU_LLD_AR_MINOR_VERSION) || \
     (ICU_AR_PATCH_VERSION_PCCFG_C != ICU_LLD_AR_PATCH_VERSION))
  #error "AutoSar Version Numbers of Icu_Cfg.c and Icu_LLD.h are different"
#endif
#endif
#if ((ICU_SW_MAJOR_VERSION_PCCFG_C != ICU_LLD_SW_MAJOR_VERSION) || \
     (ICU_SW_MINOR_VERSION_PCCFG_C != ICU_LLD_SW_MINOR_VERSION) || \
     (ICU_SW_PATCH_VERSION_PCCFG_C != ICU_LLD_SW_PATCH_VERSION))
       #error "Software Version Numbers of Icu_Cfg.c  and Icu_LLD.h are different"
#endif

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/
#define ICU_START_CONFIG_DATA_UNSPECIFIED
/**
@file  Icu_Cfg.c
@note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
       "#include" See @ref Icu_Cfg_c_1
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref Icu_Cfg_c_2
*/

/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/
[!NOCODE!]
[!VAR "IRQ_CHANNELS"   = "num:i(24)"!]
[!VAR "ICU_CHANNELS"   = "num:i(40)"!]

[!VAR "STRLENGTH"   = "num:i(($ICU_CHANNELS - 1)*4 - 1)"!]
[!ENDNOCODE!]

[!NOCODE!][!//
[!VAR "OuterLoopCounter" = "0"!][!//
[!VAR "InnerLoopCounter" = "0"!][!//
[!LOOP "IcuConfigSet/*[1]/IcuChannel/*"!][!//
[!VAR "a" = "IcuMeasurementMode"!]
[!IF "(contains($a,'ICU_MODE_TIMESTAMP') and (IcuTimestampMeasurement/IcuTimestampNotification != 'NULL_PTR') and (IcuTimestampMeasurement/IcuTimestampNotification != 'NULL'))"!]
[!VAR "OuterLoopCounter" = "$OuterLoopCounter + 1"!]
[!VAR "InnerLoopCounter" = "0"!]
[!VAR "Matchcounter" = "0"!]
[!VAR "Notification" = "IcuTimestampMeasurement/IcuTimestampNotification"!]
[!LOOP "../../IcuChannel/*"!][!//
[!VAR "a" = "IcuMeasurementMode"!]
[!IF "(contains($a,'ICU_MODE_TIMESTAMP') and (IcuTimestampMeasurement/IcuTimestampNotification != 'NULL_PTR')and (IcuTimestampMeasurement/IcuTimestampNotification != 'NULL'))"!][!//
[!VAR "InnerLoopCounter" = "$InnerLoopCounter + 1"!]
[!IF "$OuterLoopCounter >= $InnerLoopCounter"!]
[!IF "($Notification = IcuTimestampMeasurement/IcuTimestampNotification)"!]
[!VAR "Matchcounter" = "$Matchcounter + 1"!]
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!IF "$Matchcounter = 1"!][!//
/**
@brief External Notifications for Timestamp
*/
[!CODE!]extern FUNC (void, ICU_CODE) [!"IcuTimestampMeasurement/IcuTimestampNotification"!](void);
[!ENDCODE!]
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!VAR "OuterLoopCounter" = "0"!]
[!VAR "InnerLoopCounter" = "0"!]
[!LOOP "IcuConfigSet/*[1]/IcuChannel/*"!][!//
[!VAR "a" = "IcuMeasurementMode"!]
[!IF "(contains($a,'ICU_MODE_SIGNAL_EDGE_DETECT') and (IcuSignalEdgeDetection/IcuSignalNotification != 'NULL_PTR'))"!]
[!VAR "OuterLoopCounter" = "$OuterLoopCounter + 1"!]
[!VAR "InnerLoopCounter" = "0"!]
[!VAR "Matchcounter" = "0"!]
[!VAR "Notification" = "IcuSignalEdgeDetection/IcuSignalNotification"!]
[!LOOP "../../IcuChannel/*"!][!//
[!VAR "a" = "IcuMeasurementMode"!]
[!IF "(contains($a,'ICU_MODE_SIGNAL_EDGE_DETECT') and (IcuSignalEdgeDetection/IcuSignalNotification != 'NULL_PTR'))"!][!//
[!VAR "InnerLoopCounter" = "$InnerLoopCounter + 1"!]
[!IF "$OuterLoopCounter >= $InnerLoopCounter"!]
[!IF "($Notification = IcuSignalEdgeDetection/IcuSignalNotification)"!]
[!VAR "Matchcounter" = "$Matchcounter + 1"!]
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!IF "$Matchcounter = 1"!][!//
/**
@brief External Notifications for Signal edge detection
*/
[!CODE!]extern FUNC (void, ICU_CODE) [!"IcuSignalEdgeDetection/IcuSignalNotification"!](void);
[!ENDCODE!]
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!][!//
[!LOOP "IcuConfigSet/*[1]"!][!//
[!VAR "count" = "count(IcuChannel/*)"!][!//
[!VAR "str" = "''"!][!//
[!FOR "idx" = "0" TO "$ICU_CHANNELS"!][!//
[!IF "$idx!=$ICU_CHANNELS"!][!VAR "str" = "concat($str,'0xFF,')"!][!ELSE!][!VAR "str" = "concat($str,'0xFF')"!][!ENDIF!][!//
[!ENDFOR!][!//
[!VAR "wkstr" = "''"!][!//
[!FOR "idx" = "0" TO "$ICU_CHANNELS"!][!//
[!IF "$idx!=$ICU_CHANNELS"!][!VAR "wkstr" = "concat($wkstr,'0xFF,')"!][!ELSE!][!VAR "wkstr" = "concat($wkstr,'0xFF')"!][!ENDIF!][!//
[!ENDFOR!][!//
[!VAR "count" = "count(IcuChannel/*)"!][!//
[!VAR "time" = "0"!][!//
[!VAR "duty" = "0"!][!//
[!VAR "meas" = "0"!][!//
[!VAR "edge" = "0"!][!//
[!VAR "idx" = "0"!][!//


[!NOCODE!][!//
[!VAR "OuterLoopCounter" = "0"!][!//
[!LOOP "//IcuConfigSet/*[1]/IcuChannel/*/IcuOverflowNotification"!][!//
    [!VAR "InnerLoopCounter" = "0"!][!//
    [!IF "(. != 'NULL_PTR') and (. != '')"!][!//
        [!VAR "NotificationHandler" = "."!][!//
        [!VAR "skipThis" = "0"!][!//
        [!LOOP "//IcuConfigSet/*[1]/IcuChannel/*/IcuOverflowNotification"!][!//
            [!IF "(. != 'NULL_PTR') and (. != '')"!][!//
                [!VAR "a" = "."!][!//
                [!IF "$OuterLoopCounter > $InnerLoopCounter"!][!//
                    [!IF "contains($a, $NotificationHandler)"!][!//
                        [!VAR "skipThis" = "1"!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
                [!VAR "InnerLoopCounter" = "$InnerLoopCounter + 1"!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!IF "$skipThis!=1"!][!//
           /**
             @brief Overflow notification handlers
            */
            [!CODE!]extern FUNC (void, ICU_CODE) [!"$NotificationHandler"!](void);
[!ENDCODE!]
        [!ENDIF!][!//
        [!VAR "OuterLoopCounter" = "$OuterLoopCounter + 1"!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!]

/**
@brief This index relates the Icu Channel number with the respective global variable, depending on
the measurement mode Each kind of measurement mode has an array(s) in the ICU driver, this
index points to the corresponding variable within the ICU channel
 */
CONST(Icu_ChannelType,ICU_CONST) Icu_InitChannelIndex_PC[[!"num:i($count)"!]] = {[!LOOP "IcuChannel/*"!][!//
(Icu_ChannelType)[!IF "IcuMeasurementMode='ICU_MODE_TIMESTAMP'"!][!"num:inttohex($time,2)"!][!VAR "time" = "$time + 1"!][!ELSE!][!//
[!IF "IcuMeasurementMode='ICU_MODE_SIGNAL_MEASUREMENT'"!][!//
[!IF "IcuSignalMeasurement/IcuSignalMeasurementProperty='ICU_DUTY_CYCLE'"!][!"num:inttohex($duty,2)"!][!VAR "duty" = "$duty + 1"!][!ELSE!][!//
[!"num:inttohex($meas,2)"!][!VAR "meas" = "$meas + 1"!][!ENDIF!][!ELSE!][!//
[!IF "IcuMeasurementMode='ICU_MODE_EDGE_COUNTER'"!][!"num:inttohex($edge,2)"!][!VAR "edge" = "$edge + 1"!][!ELSE!][!//
0x00[!ENDIF!][!ENDIF!][!ENDIF!][!VAR "idx" = "$idx + 1"!][!IF "$idx!=$count"!],[!ENDIF!][!ENDLOOP!]};[!//
[!//


[!NOCODE!][!//
[!VAR "LoopVar"="0"!][!//
[!VAR "idx" = "0"!][!//
[!FOR "x" = "0" TO "num:i(count(IcuChannel/*))"!][!//
[!LOOP "IcuChannel/*"!][!//
[!VAR "Loop"="num:i($LoopVar)"!][!//
[!IF "IcuChannelId = $Loop"!][!//
    [!IF "contains(IcuHwChannel,'EMIOS_0_CH_')"!]
    [!VAR "tempSTR" = "substring-after(IcuHwChannel,'EMIOS_0_CH_')"!]
    [!ELSE!][!IF "contains(IcuHwChannel,'IRQ_')"!]
    [!VAR "tempSTR" = "substring-after(IcuHwChannel,'IRQ_')+$IRQ_CHANNELS"!]
    [!ENDIF!]
    [!ENDIF!][!//
    [!VAR "hwch" = "$tempSTR"!][!//
    [!IF "$hwch<=$ICU_CHANNELS"!][!//
    [!IF "$hwch=0"!][!VAR "str" = "concat(num:inttohex($idx,2),',',substring($str,6))"!][!ELSE!][!IF "$hwch=$ICU_CHANNELS"!][!VAR "str" = "concat(substring($str,0,$STRLENGTH),',',num:inttohex($idx,2))"!][!ELSE!][!//
    [!VAR "str" = "concat(substring($str,1,$hwch*5),num:inttohex($idx,2),',',substring($str,1+(($hwch+1)*5)))"!][!ENDIF!][!ENDIF!][!ENDIF!][!//
    [!VAR "idx" = "$idx + 1"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!VAR "LoopVar"="$LoopVar + 1"!][!//
[!ENDFOR!][!//
[!VAR "strcast" = "''"!][!//
[!FOR "idx" = "0" TO "$ICU_CHANNELS"!][!//
[!VAR "strcast" = "concat($strcast,'(Icu_ChannelType)',substring($str,$idx*5+1,5))"!]
[!ENDFOR!][!//
[!ENDNOCODE!]
/**
@brief This index relates the Hardware channels with the respective ICU channel.
When an normal interrupt is asserted this index is used to locate the corresponding ICU channel
 */

CONST(Icu_ChannelType,ICU_CONST) Icu_InitHWMap_PC[ICU_MAX_HW_CHANNELS + 1U] = {[!"$strcast"!]};
/*lint -restore*/
[!NOCODE!][!//
[!VAR "LoopVar"="0"!][!//
[!VAR "idx" = "0"!][!//
[!FOR "x" = "0" TO "num:i(count(IcuChannel/*))"!][!//
[!LOOP "IcuChannel/*"!][!//
[!VAR "Loop"="num:i($LoopVar)"!][!//
[!IF "IcuChannelId = $Loop"!][!//
    [!IF "contains(IcuHwChannel,'EMIOS_0_CH_')"!][!VAR "tempSTR" = "substring-after(IcuHwChannel,'EMIOS_0_CH_')"!]
    [!ELSE!][!IF "contains(IcuHwChannel,'IRQ_')"!][!VAR "tempSTR" = "substring-after(IcuHwChannel,'IRQ_')+$IRQ_CHANNELS"!]
    [!ENDIF!]
    [!ENDIF!][!//
    [!VAR "hwch" = "$tempSTR"!][!//
    [!IF "IcuWakeupCapability"!][!//

    [!IF "$hwch<=$ICU_CHANNELS"!][!//
        [!IF "$hwch=0"!]
            [!VAR "wkstr" = "concat(num:inttohex($idx,2),',',substring($wkstr,6))"!]
        [!ELSE!]
            [!IF "$hwch=$ICU_CHANNELS"!]
                [!VAR "wkstr" = "concat(substring($wkstr,0,$STRLENGTH),',',num:inttohex($idx,2))"!]
            [!ELSE!][!//
                [!VAR "wkstr" = "concat(substring($wkstr,1,$hwch*5),num:inttohex($idx,2),',',substring($wkstr,1+(($hwch+1)*5)))"!]
            [!ENDIF!]
        [!ENDIF!]
    [!ENDIF!][!//
    [!ENDIF!][!//
    [!VAR "idx" = "$idx + 1"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!VAR "LoopVar"="$LoopVar + 1"!][!//
[!ENDFOR!][!//
[!VAR "strcast" = "''"!][!//
[!FOR "idx" = "0" TO "$ICU_CHANNELS"!][!//
[!VAR "strcast" = "concat($strcast,'(Icu_ChannelType)',substring($wkstr,$idx*5+1,5))"!]
[!ENDFOR!][!//
[!ENDNOCODE!]
/**
@brief This index relates the Wakeup pins with the respective ICU channel
When an wake up interrupt is asserted this index is used to locate the corresponding ICU channel
 */
CONST(Icu_ChannelType,ICU_CONST) Icu_InitHWWKMap_PC[ICU_MAX_HW_CHANNELS + 1U] = {[!"$strcast"!]};

[!VAR "idx" = "1"!][!//
/**@brief Pre-Compile Default Configuration */
[!VAR "LoopVar"="0"!][!//

CONST(Icu_ChannelConfigType, ICU_CONST) Icu_InitChannel_PC[[!"num:i($count)"!]]=
{
[!FOR "x" = "0" TO "num:i(count(IcuChannel/*))"!][!//
[!LOOP "IcuChannel/*"!][!//
[!VAR "Loop"="num:i($LoopVar)"!][!//
[!IF "IcuChannelId = $Loop"!][!//
    /* [!"node:name(.)"!] - [!"IcuHwChannel"!] */
    {
        ([!IF "IcuWakeupCapability"!][!/*
            */!]((Icu_ParamType)ICU_WAKEUP_CAPABLE << ICU_WAKEUP_SHIFT) |[!/*
      */!][!ENDIF!][!/*
      */!]((Icu_ParamType)[!"IcuDefaultStartEdge"!] << ICU_EDGE_PARAM_SHIFT)[!/*
      */!][!IF "IcuMeasurementMode='ICU_MODE_SIGNAL_MEASUREMENT'"!][!/*
        */!][!IF "IcuSignalMeasurement/IcuSignalMeasurementProperty='ICU_HIGH_TIME' or IcuSignalMeasurement/IcuSignalMeasurementProperty='ICU_LOW_TIME'"!][!/*
            */!][!IF "contains(ecu:list(concat('Icu.ChannelType.', IcuHwChannel)), 'IPWM')"!][!/*
                */!] |((Icu_ParamType)EMIOS_UC_IPWM_MODE << ICU_EMIOS_UC_MODE_PARAM_SHIFT)[!/*
            */!][!ELSE!][!/*
                */!] |((Icu_ParamType)EMIOS_UC_SAIC_MODE << ICU_EMIOS_UC_MODE_PARAM_SHIFT)[!/*
            */!][!ENDIF!][!/*
        */!][!ELSEIF "(IcuSignalMeasurement/IcuSignalMeasurementProperty ='ICU_DUTY_CYCLE') and (IcuUserModeForDutycycle = 'IPWM')"!][!/*
                */!] | ((Icu_ParamType)EMIOS_UC_IPWM_MODE << ICU_EMIOS_UC_MODE_PARAM_SHIFT)[!/*
        */!][!ELSEIF "(IcuSignalMeasurement/IcuSignalMeasurementProperty ='ICU_DUTY_CYCLE') and (IcuUserModeForDutycycle = 'SAIC')"!][!/*
                */!] |((Icu_ParamType)EMIOS_UC_SAIC_MODE << ICU_EMIOS_UC_MODE_PARAM_SHIFT)[!/*
        */!][!ELSE!][!/*
            */!][!IF "contains(ecu:list(concat('Icu.ChannelType.', IcuHwChannel)), 'IPM')"!][!/*
                */!] |((Icu_ParamType)EMIOS_UC_IPM_MODE << ICU_EMIOS_UC_MODE_PARAM_SHIFT)[!/*
            */!][!ELSE!][!/*
                */!] |((Icu_ParamType)EMIOS_UC_SAIC_MODE << ICU_EMIOS_UC_MODE_PARAM_SHIFT)[!/*
            */!][!ENDIF!][!/*
       */!][!ENDIF!][!/*
    */!][!ENDIF!][!/*
    */!][!IF "contains(IcuHwChannel,'EMIOS')"!][!/*
        */!][!IF "IcuEmiosFreeze"!][!/*
           */!] | ((Icu_ParamType)EMIOS_FREEZE_ENABLE << ICU_EMIOS_FREEZE_PARAM_SHIFT)[!/*
        */!][!ENDIF!][!/*
        */!]| ((Icu_ParamType)[!"IcuEmiosPrescaler"!] << ICU_EMIOS_PRESCALER_PARAM_SHIFT)[!/*
        */!][!IF "../../../../IcuNonAUTOSAR/IcuEnableDualClockMode"!][!/*
           */!]| ((Icu_ParamType)[!"IcuEmiosPrescaler_Alternate"!] << ICU_EMIOS_PRESC_ALT_PARAM_SHIFT)[!/*
        */!][!ENDIF!][!/*
        */!]| ((Icu_ParamType)[!"IcuEmiosDigitalFilter"!] << ICU_EMIOS_DIG_FILTER_PARAM_SHIFT)[!/*
        */!]| ((Icu_ParamType)[!"IcuEmiosBusSelect"!] << ICU_EMIOS_BUS_SELECT_PARAM_SHIFT)[!/*
    */!][!ENDIF!][!/*
    */!]),
        (Icu_MeasurementModeType)[!"IcuMeasurementMode"!],
        (Icu_MeasurementSubModeType)[!IF "IcuMeasurementMode='ICU_MODE_SIGNAL_EDGE_DETECT'"!]0U[!ENDIF!][!/*
        */!][!IF "IcuMeasurementMode='ICU_MODE_TIMESTAMP'"!][!/*
            */!][!IF "IcuTimestampMeasurement/IcuTimestampMeasurementProperty='ICU_CIRCULAR_BUFFER'"!][!/*
                */!]ICU_CIRCULAR_BUFFER[!/*
            */!][!ELSE!][!/*
                */!]ICU_LINEAR_BUFFER[!/*
            */!][!ENDIF!][!/*
        */!][!ENDIF!][!/*
        */!][!IF "IcuMeasurementMode='ICU_MODE_SIGNAL_MEASUREMENT'"!][!/*
            */!][!IF "IcuSignalMeasurement/IcuSignalMeasurementProperty='ICU_DUTY_CYCLE'"!][!/*
                */!]ICU_DUTY_CYCLE[!/*
            */!][!ENDIF!][!/*
            */!][!IF "IcuSignalMeasurement/IcuSignalMeasurementProperty='ICU_HIGH_TIME'"!][!/*
                */!]ICU_HIGH_TIME[!/*
            */!][!ENDIF!][!/*
            */!][!IF "IcuSignalMeasurement/IcuSignalMeasurementProperty='ICU_LOW_TIME'"!][!/*
                */!]ICU_LOW_TIME[!/*
            */!][!ENDIF!][!/*
            */!][!IF "IcuSignalMeasurement/IcuSignalMeasurementProperty='ICU_PERIOD_TIME'"!][!/*
                */!]ICU_PERIOD_TIME[!/*
            */!][!ENDIF!][!/*
        */!][!ENDIF!][!/*
        */!][!IF "IcuMeasurementMode='ICU_MODE_EDGE_COUNTER'"!][!/*
            */!][!IF "IcuDefaultStartEdge='ICU_BOTH_EDGES'"!][!/*
                */!]ICU_BOTH_EDGES[!/*
            */!][!ENDIF!][!/*
            */!][!IF "IcuDefaultStartEdge='ICU_FALLING_EDGE'"!][!/*
                */!]ICU_FALLING_EDGE[!/*
            */!][!ENDIF!][!/*
            */!][!IF "IcuDefaultStartEdge='ICU_RISING_EDGE'"!][!/*
                */!]ICU_RISING_EDGE[!/*
            */!][!ENDIF!][!/*
        */!][!ENDIF!],
        [!IF "IcuMeasurementMode='ICU_MODE_SIGNAL_MEASUREMENT'"!]NULL_PTR[!ENDIF!][!IF "IcuMeasurementMode='ICU_MODE_EDGE_COUNTER'"!]NULL_PTR[!ENDIF!][!IF "IcuMeasurementMode='ICU_MODE_TIMESTAMP'"!][!IF "IcuTimestampMeasurement/IcuTimestampNotification!=''"!][!"IcuTimestampMeasurement/IcuTimestampNotification"!][!ELSE!]NULL_PTR[!ENDIF!][!ENDIF!][!IF "IcuMeasurementMode='ICU_MODE_SIGNAL_EDGE_DETECT'"!][!IF "IcuSignalEdgeDetection/IcuSignalNotification!=''"!][!"IcuSignalEdgeDetection/IcuSignalNotification"!][!ELSE!]NULL_PTR[!ENDIF!][!ENDIF!],
#if defined(ICU_OVERFLOW_NOTIFICATION_API) && (ICU_OVERFLOW_NOTIFICATION_API == STD_ON)
        [!IF "node:exists(IcuOverflowNotification)"!][!"IcuOverflowNotification"!][!ELSE!]NULL_PTR[!ENDIF!],
/* ICU_OVERFLOW_NOTIFICATION_API */    
#endif
        [!IF "IcuWakeupCapability"!][!SELECT "node:ref(IcuWakeup/IcuChannelWakeupInfo)"!][!"EcuMWakeupSourceId"!]U[!ENDSELECT!][!ELSE!]0U[!ENDIF!]
    }[!IF "$idx!=$count"!],[!ENDIF!]
[!VAR "idx" = "$idx + 1"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!VAR "LoopVar"="$LoopVar + 1"!][!//
[!ENDFOR!][!//
};

[!ENDLOOP!]

/**
 @brief Configured Hardware channels
@{
*/
[!VAR "LoopVar1"="0"!][!//
[!VAR "NoOfChannels" = "num:i(IcuConfigSet/*[1]/IcuMaxChannel - 1)"!][!//
CONST(Icu_ChannelType,ICU_VAR) Icu_ChannelId_PC[[!"num:i(IcuConfigSet/*[1]/IcuMaxChannel)"!]]=
{
    [!FOR "x" = "0" TO "num:i(count(IcuConfigSet/*[1]/IcuChannel/*))"!][!/*
        */!][!LOOP "IcuConfigSet/*[1]/IcuChannel/*"!][!/*
  */!][!VAR "Loop"="num:i($LoopVar1)"!][!/*
  */!][!IF "IcuChannelId = $Loop"!][!/*
      */!]  ICU_[!"IcuHwChannel"!][!/*
          */!][!IF "@index < $NoOfChannels"!],[!ENDIF!]
       [!ENDIF!][!/*
    */!][!ENDLOOP!][!/*
    */!][!VAR "LoopVar1"="$LoopVar1 + 1"!][!/*
    */!][!ENDFOR!]
 };
/**@}*/

/**@brief Pre-Compile Default Configuration */
CONST(Icu_ConfigType, ICU_CONST) Icu_Configs_PC =
{
    (Icu_ChannelType)[!"num:i(IcuConfigSet/*[1]/IcuMaxChannel)"!], /* The number of channels
                                                                   configured*/
    Icu_InitChannel_PC,
    Icu_InitChannelIndex_PC,
    Icu_ChannelId_PC,
    Icu_InitHWMap_PC,
    Icu_InitHWWKMap_PC
};

#define ICU_STOP_CONFIG_DATA_UNSPECIFIED
/**
@file  Icu_Cfg.c
@note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
       "#include"  See @ref Icu_Cfg_c_1
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a
       header file being included twice See @ref Icu_Cfg_c_3 */
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

/* ICU_PRECOMPILE_SUPPORT */
#endif  

#ifdef __cplusplus
}
#endif

[!ENDCODE!]
