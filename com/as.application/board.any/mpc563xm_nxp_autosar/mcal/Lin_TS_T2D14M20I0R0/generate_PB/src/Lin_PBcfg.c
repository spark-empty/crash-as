/**
    @file     Lin_PBcfg.c
    @version  2.0.0
    
    @brief    Post build configuration data.
    @details  Post build configuration data.
    
    Project        AUTOSAR 3.0 MCAL
    Platform       PA
    Peripheral     ESCI
    Dependencies   
    
    ARVersion      3.0.0
    ARRevision     ASR_REL_3_0_REV_0003
    ARConfVariant  
    SWVersion      2.0.0
    BuildVersion   XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223
    
    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
    All Rights Reserved.
*/
/*==================================================================================================
==================================================================================================*/

/**
 * @page misra_violations MISRA-C:2004 violations
 * 
 * @section LIN_PBCFG_C_REF_1
 * Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor directives or comments before 
 * "#include". This violation is not fixed since the inclusion of MemMap.h is as per Autosar 
 * requirement MEMMAP003.
 * 
 * @section LIN_PBCFG_C_REF_2
 * Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to prevent the 
 * contents of a header file being included twice. This is not a violation since all header 
 * files are protected against multiple inclusions.
 * 
 * @section LIN_PBCFG_C_REF_3
 * Violates MISRA 2004 Required Rule 9.2, Braces shall be used to indicate and match the structure 
 * in the non-zero initialization of arrays and structures. 
 * This violation is not fixed since "Lin_ChannelConfigType" structure is generated as independent 
 * structure and not as an array of structures. So there should not be braces in "Lin_ConfigType" 
 * structure.
 */

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
**                            Include Files                                 **
*****************************************************************************/
#include "Std_Types.h"
#include "Lin.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**@remarks Covers LIN062 */
#define LIN_AR_MAJOR_VERSION_PBCFG_C  [!"CommonPublishedInformation/ArMajorVersion"!]
#define LIN_AR_MINOR_VERSION_PBCFG_C  [!"CommonPublishedInformation/ArMinorVersion"!]
#define LIN_AR_PATCH_VERSION_PBCFG_C  [!"CommonPublishedInformation/ArPatchVersion"!]
#define LIN_SW_MAJOR_VERSION_PBCFG_C  [!"CommonPublishedInformation/SwMajorVersion"!]
#define LIN_SW_MINOR_VERSION_PBCFG_C  [!"CommonPublishedInformation/SwMinorVersion"!]
#define LIN_SW_PATCH_VERSION_PBCFG_C  [!"CommonPublishedInformation/SwPatchVersion"!]

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/**@remarks Covers LIN062 */
[!NOCODE!][!//
[!INCLUDE "Lin_VersionCheck_Src_PB.m"!][!//
[!ENDNOCODE!][!//
#ifdef CHECK_AUTOSAR_VERSION
  #if ((LIN_AR_MAJOR_VERSION_PBCFG_C != LIN_AR_MAJOR_VERSION) || \
       (LIN_AR_MINOR_VERSION_PBCFG_C != LIN_AR_MINOR_VERSION) || \
       (LIN_AR_PATCH_VERSION_PBCFG_C != LIN_AR_PATCH_VERSION))
      #error "AutoSar Version Numbers of Lin_PBcfg.c and Lin.h are different"
  #endif
#endif

#if ((LIN_SW_MAJOR_VERSION_PBCFG_C != LIN_SW_MAJOR_VERSION) || \
     (LIN_SW_MINOR_VERSION_PBCFG_C != LIN_SW_MINOR_VERSION))
    #error "Software Version Numbers of Lin_PBcfg.c and Lin.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
  #if ((LIN_AR_MAJOR_VERSION_PBCFG_C != STD_TYPES_AR_MAJOR_VERSION) || \
       (LIN_AR_MINOR_VERSION_PBCFG_C != STD_TYPES_AR_MINOR_VERSION) || \
       (LIN_AR_PATCH_VERSION_PBCFG_C != STD_TYPES_AR_PATCH_VERSION))
      #error "AutoSar Version Numbers of Lin_PBcfg.c and Std_Types.h are different"
  #endif
#endif

#ifdef CHECK_AUTOSAR_VERSION
  #if ((LIN_AR_MAJOR_VERSION_PBCFG_C != ECUM_CFG_AR_MAJOR_VERSION) || \
       (LIN_AR_MINOR_VERSION_PBCFG_C != ECUM_CFG_AR_MINOR_VERSION) || \
       (LIN_AR_PATCH_VERSION_PBCFG_C != ECUM_CFG_AR_PATCH_VERSION))
      #error "AutoSar Version Numbers of Lin_PBcfg.c and EcuM_Cfg.h are different"
  #endif
#endif


/*****************************************************************************
**                               Global Variable                            **
*****************************************************************************/


#define LIN_START_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

[!NOCODE!][!//
[!VAR "SBR"="0"!][!//
[!VAR "temp1" = "0"!][!//
[!VAR "temp2" = "0"!][!//
[!VAR "ESCISBR" = "0"!][!//
[!VAR "ECUM_WAKE_UP_SOURCE" = "0"!][!//
[!VAR "DUALCLOCK"!][!"NonAutosar/LinEnableDualClockMode"!][!ENDVAR!][!//
[!ENDNOCODE!][!//

#ifndef LIN_PRECOMPILE_SUPPORT


[!LOOP "LinGlobalConfig/*"!][!//
[!VAR "nodeName" = "node:name(.)"!][!//
[!VAR "shortNodeName" = "concat('_C', @index)"!]
[!LOOP "LinChannel/*"!][!//
/**
 * @brief Configuration for Lin Channel [!"LinChannelId"!] - Configuration: [!"$nodeName"!]
 * @remarks Covers LIN064
 * 
 * @api
 */
CONST(Lin_ChannelConfigType,LIN_APPL_CONST) Lin_[!"node:name(.)"!][!"$shortNodeName"!]=
    {
#ifdef LIN_USE_MSC
[!IF "LinChannelMSCSupport"!][!//
    (uint8)STD_ON, /* MSC support enabled */
  [!IF "(MicroSecondChannel/Parity ='Even')"!]  MSC_EVEN[!ELSE!]  MSC_ODD[!ENDIF!],    /* MSC parity */
  [!IF "(MicroSecondChannel/Polarity ='Normal')"!]  MSC_NORMAL[!ELSE!]  MSC_INVERTED[!ENDIF!],    /* MSC polarity */
  [!IF "(MicroSecondChannel/FrameFormat ='Format_16_bits')"!]  MSC_16_BITS[!ELSE!]  MSC_12_BITS[!ENDIF!],   /* MSC frame format */
  [!IF "MicroSecondChannel/PollingMode"!]  STD_ON,  /* MSC polling mode Enabled */[!ELSE!]  STD_OFF, /* MSC polling mode Disabled */[!ENDIF!]
[!NOCODE!]
    [!VAR "IntegerClkDiv" = "substring-after(MicroSecondChannel/ClockDivisor,'_')"!]
        [!IF "$IntegerClkDiv = 8"!]
          [!VAR "VarClkDiv"="8"!]
        [!ELSEIF "$IntegerClkDiv = 16"!]
          [!VAR "VarClkDiv"="16"!]
        [!ELSEIF "$IntegerClkDiv = 32"!]
          [!VAR "VarClkDiv"="32"!]
        [!ELSEIF "$IntegerClkDiv = 64"!]
          [!VAR "VarClkDiv"="64"!]
        [!ELSEIF "$IntegerClkDiv = 128"!]
          [!VAR "VarClkDiv"="128"!]
        [!ELSEIF "$IntegerClkDiv = 256"!]
          [!VAR "VarClkDiv"="256"!]
        [!ELSE!]
          [!VAR "VarClkDiv"="512"!]
        [!ENDIF!]
    [!VAR "tmpMscBR" = "MicroSecondChannel/ClockFrequency"!]
    [!VAR "MscBR" = "($tmpMscBR div $VarClkDiv)"!]
    [!VAR "linBaudrate" = "num:i($MscBR)"!]
    [!SELECT "node:ref(LinClockRef)"!]
    [!INCLUDE "Lin_BaudRate_Comp.m"!]
    [!ENDSELECT!]
[!ENDNOCODE!][!//
  [!CODE!]  [!"$ESCISBR"!]U,               /* MSC upstream channel baudrate [!"num:i($MscBR)"!] ; Baudrate difference = [!"$temp2"!] */ [!ENDCODE!][!//
[!ELSE!][!//
      (uint8)STD_OFF, /* MSC support disabled */
      MSC_EVEN,        /* MSC Parity */
      MSC_NORMAL,     /* MSC polarity */
      MSC_16_BITS,    /* MSC frame format */
      STD_OFF,        /* MSC polling mode */
      0x0000U,         /* Default MSC upstream channel baudrate value as MSC support is disabled for this channel */[!//
[!ENDIF!]
#endif[!//
[!NOCODE!]
[!IF "LinHwChannel = 'eSCI_A'"!]
    [!VAR "HardwareChannel" = "num:i(0)"!]
[!ELSEIF "LinHwChannel = 'eSCI_B'"!]
    [!VAR "HardwareChannel" = "num:i(1)"!]
[!ENDIF!]
[!ENDNOCODE!]
    [!IF "(ReceiverFullInterruptEnable ='true')"!](uint8)STD_ON[!ELSE!](uint8)STD_OFF[!ENDIF!],    /* Receiver Full Interrupt Enable */
    LinHWCh_[!"$HardwareChannel"!],     /* Lin Hardware channel*/
[!NOCODE!]
  [!IF "$DUALCLOCK"!]
      [!NOCODE!]
      [!VAR "linBaudrate" = "LinChannelBaudRate"!]
      [!SELECT "node:ref(LinClockRef)"!]
      [!INCLUDE "Lin_BaudRate_Comp.m"!]
      [!ENDSELECT!]
      [!ENDNOCODE!]
      [!CODE!]    [!"$ESCISBR"!]U,               /* Baudrate [!"LinChannelBaudRate"!] ; Baudrate difference = [!"$temp2"!] */ [!ENDCODE!]
      [!NOCODE!]
      [!VAR "linBaudrate" = "LinChannelBaudRate"!]
      [!SELECT "node:ref(LinClockRef_Alternate)"!]
      [!INCLUDE "Lin_BaudRate_Comp.m"!]
      [!ENDSELECT!]
      [!ENDNOCODE!]
      [!CODE!]
    [!"$ESCISBR"!]U,               /* Alternate Baudrate [!"LinChannelBaudRate"!] ; Baudrate difference = [!"$temp2"!] */[!ENDCODE!]
  [!ELSE!]
      [!NOCODE!]
      [!VAR "linBaudrate" = "LinChannelBaudRate"!]
      [!SELECT "node:ref(LinClockRef)"!]
      [!INCLUDE "Lin_BaudRate_Comp.m"!]
      [!ENDSELECT!]
      [!ENDNOCODE!]
      [!CODE!]    [!"$ESCISBR"!]U,               /* Baudrate [!"LinChannelBaudRate"!] ; Baudrate difference = [!"$temp2"!] */[!ENDCODE!]
  [!ENDIF!]
[!ENDNOCODE!][!//
[!IF "LinChannelWakeUpSupport"!]
    (uint16)STD_ON,        /* Wakeup support enabled */
[!ELSE!]
    (uint16)STD_OFF,    /* Wakeup support disabled */
[!ENDIF!]
[!IF "LinChannelWakeUpSupport ='true'"!][!//
[!NOCODE!][!//
    [!SELECT "node:ref(LinChannelEcuMWakeUpSource)"!]
        [!VAR "ECUM_WAKE_UP_SOURCE" = "num:i(EcuMWakeupSourceId)"!]
    [!ENDSELECT!]
[!ENDNOCODE!][!//
    [!"num:inttohex($ECUM_WAKE_UP_SOURCE, 2)"!]U,    /* Wakeup Source transmitted to the Ecu State Manager (used only when Wakeup Support is true) */
[!ELSE!][!//
    0x00U,                /* Default Wakeup Source as the Wakeup Support is disabled for this channel */
[!ENDIF!][!//
#ifdef LIN_USE_DMA
[!IF "(LinHwChannel ='eSCI_A')"!][!//
[!IF "LinChannelDmaActivation"!][!//
    (uint8)STD_ON,        /* DMA support enabled */
  [!"ecu:get('LinDMAChannelForeSCIATX')"!]U,        /* eSCI_A TX DMA Channel */
  [!"ecu:get('LinDMAChannelForeSCIARX')"!]U,        /* eSCI_A RX DMA Channel */
[!NOCODE!]
[!IF "LinChannelDmaActivation"!][!//
    [!VAR "DMAtransferSize" = "node:value(DMAsettings/DMADataSize)"!]
    [!IF "$DMAtransferSize = 'Size_8_bits'"!]
            [!VAR "VarDmaSize"="0"!]
        [!ELSEIF "$DMAtransferSize = 'Size_16_bits'"!]
            [!VAR "VarDmaSize"="1"!]
        [!ELSEIF "$DMAtransferSize = 'Size_32_bits'"!]
            [!VAR "VarDmaSize"="2"!]
        [!ELSEIF "$DMAtransferSize = 'Size_64_bits'"!]
            [!VAR "VarDmaSize"="3"!]
        [!ELSEIF "$DMAtransferSize = 'Size_16_bytes'"!]
            [!VAR "VarDmaSize"="4"!]
        [!ELSEIF "$DMAtransferSize = 'Size_32_bytes'"!]
            [!VAR "VarDmaSize"="5"!]
        [!ELSE!]
            [!VAR "VarDmaSize"="0"!]
    [!ENDIF!]
    [!VAR "HALFINT" = "node:value(DMAsettings/TheHalfPointInterrupt)"!]
    [!VAR "MAJINT" = "node:value(DMAsettings/TheEndOfMajorLoopInterrupt)"!]
    [!IF "$MAJINT = 'true'"!]
        [!IF "$HALFINT = 'true'"!]
            [!VAR "INTMASK" = "6"!]
            [!VAR "IntrDescr" = "'int_half and int_maj'"!]
        [!ELSE!]
            [!VAR "INTMASK" = "2"!]
            [!VAR "IntrDescr" = "'int_maj'"!]
        [!ENDIF!]
    [!ELSEIF "$HALFINT = 'true'"!]
        [!VAR "INTMASK" = "4"!]
        [!VAR "IntrDescr" = "'int_half'"!]
    [!ELSE!]
        [!VAR "INTMASK" = "0"!]
        [!VAR "IntrDescr" = "'no'"!]
    [!ENDIF!]
    [!VAR "INTRMASK" = "num:inttohex($INTMASK,2)"!][!//
    [!VAR "DMAnbytes" = "node:value(DMAsettings/nBytesToTransfer)"!]
    [!VAR "DMAcnt" = "node:value(DMAsettings/iterationCount)"!]
    [!VAR "DMAdoff" = "node:value(DMAsettings/destinationAddressOffset)"!]
    [!VAR "DMAdlast" = "node:value(DMAsettings/lastDestinationAddress)"!]
    [!VAR "SSIZE" = "num:inttohex($VarDmaSize,2)"!][!//
    [!VAR "NBYTE" = "num:inttohex($DMAnbytes,8)"!][!//
    [!VAR "CITER" = "num:inttohex($DMAcnt,4)"!][!//
    [!VAR "DOFF" = "num:inttohex($DMAdoff,4)"!][!//
    [!VAR "DLAST" = "num:inttohex($DMAdlast,8)"!][!//
[!ENDIF!][!ENDNOCODE!]  [!"$SSIZE"!]U,       /*!< Size of transfered data set to [!"$DMAtransferSize"!]. (ssize)*/
  [!"$NBYTE"!]U,    /*!< Number of byte to transfer. (nbytes)*/
  [!"$CITER"!]U,    /*!< Current iteration count (citer, biter).*/
  [!"$DOFF"!]U,     /*!< offset of destination address. (doff)*/
  [!"$DLAST"!]U,    /*!< Adjustment value to the destination address (dlast).*/
  [!"$INTRMASK"!]U  /*!< Set [!"$IntrDescr"!] interrupt flags.*/
[!ELSE!][!//
  (uint8)STD_OFF,   /* DMA support disabled */
  0U,               /* No DMA channel assigned */
  0U,               /* No DMA channel assigned */
  0U,
  0U,
  0U,
  0U,
  0U
[!ENDIF!][!//
[!ELSE!][!//
  (uint8)STD_OFF,   /* No DMA support for eSCI_B */
  0U,               /* No DMA channel assigned */
  0U,               /* No DMA channel assigned */
  0U,
  0U,
  0U,
  0U,
  0U
[!ENDIF!][!//
#endif
    };

[!ENDLOOP!][!//
[!ENDLOOP!][!//

[!LOOP "LinGlobalConfig/*"!]
[!VAR "nodeName" = "node:name(.)"!][!//
[!VAR "shortNodeName" = "concat('_C', @index)"!]
/**
 * @brief  Lin Configuration data for [!"@name"!]
 * @remarks Covers LIN031
 *
 * @api
 */
/**
 * @file Lin_PBcfg.c
 * @note Violates MISRA 2004 Required Rule 9.2, omitted braces within an initializer: 
 *       See @ref LIN_PBCFG_C_REF_3
 */
CONST(Lin_ConfigType,LIN_APPL_CONST)[!"@name"!] =
    {
[!VAR "LoopVar"="0"!][!//
[!VAR "Comma"="0"!][!//
[!VAR "MaxCount" = "num:i(count(LinChannel/*))"!][!//
[!FOR "count" = "0" TO "num:i(count(LinChannel/*))"!][!//
[!LOOP "LinChannel/*"!][!//
[!IF "$LoopVar = num:i(LinChannelId)"!][!//
[!VAR "Comma"="$Comma + 1"!][!//
/** @brief Configuration for Lin Channel [!"LinChannelId"!] --------- */
    &Lin_[!"node:name(.)"!][!"$shortNodeName"!][!IF "$Comma < $MaxCount"!][!CODE!],[!ENDCODE!] [!ELSE!] [!ENDIF!]
[!ENDIF!][!//
[!ENDLOOP!][!//
[!VAR "LoopVar"="$LoopVar + 1"!][!//
[!ENDFOR!][!//

    };

[!ENDLOOP!][!//
#endif /* #ifndef LIN_PRECOMPILE_SUPPORT */

#define LIN_STOP_CONFIG_DATA_UNSPECIFIED
/**
 * @file Lin_PBcfg.c
 * @note Violates MISRA 2004 Advisory Rule 19.1, Declaration before '#include': 
 *       See @ref LIN_PBCFG_C_REF_1
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h: 
 *       See @ref LIN_PBCFG_C_REF_2
 */
#include "MemMap.h"

#ifdef __cplusplus
extern "C" }
#endif

