/**
    @file     Lin_Cfg.h
    @version  2.0.0
    
    @brief    AUTOSAR Lin - Brief description.
    @details  Header file for configuration variants of the Lin module.
    
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
#ifdef __cplusplus
extern "C" {
#endif

#ifndef LIN_CFG_H
#define LIN_CFG_H

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "EcuM.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**@remarks Covers LIN062 */
[!NOCODE!][!//
[!INCLUDE "Lin_VersionCheck_Inc.m"!][!//
[!ENDNOCODE!][!//

/* Inclusion of incompatible header files shall be avoided */
#define LIN_AR_MAJOR_VERSION_CFG_H        [!"CommonPublishedInformation/ArMajorVersion"!]
#define LIN_AR_MINOR_VERSION_CFG_H        [!"CommonPublishedInformation/ArMinorVersion"!]
#define LIN_AR_PATCH_VERSION_CFG_H        [!"CommonPublishedInformation/ArPatchVersion"!]
#define LIN_SW_MAJOR_VERSION_CFG_H        [!"CommonPublishedInformation/SwMajorVersion"!]
#define LIN_SW_MINOR_VERSION_CFG_H        [!"CommonPublishedInformation/SwMinorVersion"!]
#define LIN_SW_PATCH_VERSION_CFG_H        [!"CommonPublishedInformation/SwPatchVersion"!]

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#ifdef CHECK_AUTOSAR_VERSION
#if ((LIN_AR_MAJOR_VERSION_CFG_H != ECUM_AR_MAJOR_VERSION) || \
     (LIN_AR_MINOR_VERSION_CFG_H != ECUM_AR_MINOR_VERSION) || \
     (LIN_AR_PATCH_VERSION_CFG_H != ECUM_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Lin_Cfg.h. and EcuM.h are different"
#endif
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/
[!IF "IMPLEMENTATION_CONFIG_VARIANT='VariantPreCompile'"!]
#define LIN_PRECOMPILE_SUPPORT
[!ENDIF!]

/** @brief No of Channels configured */
#define LIN_HW_MAX_MODULES [!"num:i(count(LinGlobalConfig/*[1]/LinChannel/*))"!]U[!//*/

/** @brief Total number of available hardware lin channels */
#define LIN_HW_MAX_AVAILABLE_MODULES [!"num:i(ecu:get('Lin.LinGlobalConfig.LinChannel'))"!]U

/** @brief Max data length */
#define LIN_MAX_DATA_LENGTH  8U

/** @brief Number of loops before returning LIN_E_TIMEOUT */
#define  LIN_TIMEOUT_LOOPS [!"LinGeneral/LinTimeoutDuration"!]U

/**
 * @brief Pre-Compile Parameter Defines
 * @remarks Implements DLIN16002
 * @remarks Covers LIN049
 */
#define LIN_DEV_ERROR_DETECT      [!IF "LinGeneral/LinDevErrorDetect"!]STD_ON  /* Enable Development Error Detection */[!ELSE!]STD_OFF /* Disable Development Error Detection */[!ENDIF!]
/** @remarks Implements DLIN16003 */
#define LIN_VERSION_INFO_API      [!IF "LinGeneral/LinVersionInfoApi"!]STD_ON  /* Enable API Lin_GetVersionInfo      */[!ELSE!]STD_OFF /* Disable API Lin_GetVersionInfo     */[!ENDIF!]

#define LIN_DUAL_CLOCK_MODE       [!IF "NonAutosar/LinEnableDualClockMode"!]STD_ON  /* Enable API Lin_SetClockMode        */[!ELSE!]STD_OFF /* Disable API Lin_SetClockMode       */[!ENDIF!]
[!NOCODE!]
[!// check for duplicated channel id, or hw channel id
[!VAR "iconf" = "0"!]
[!VAR "ichnn" = "0"!]
[!VAR "iter" = "0"!]
[!VAR "tmp_wakeup_support" = "0"!]
[!VAR "nconf" = "count(LinGlobalConfig/*)"!]
[!FOR "iconf" = "1" TO "$nconf"!]
    [!VAR "nchnn" = "count(LinGlobalConfig/*[$iconf]/LinChannel/*)"!]
    [!FOR "ichnn" = "1" TO "$nchnn"!]
        [!VAR "hwLoopChannel" = "substring-after(LinGlobalConfig/*[$iconf]/LinChannel/*[$ichnn]/LinHwChannel,'_')"!]
        [!VAR "chnnID" = "LinGlobalConfig/*[$iconf]/LinChannel/*[$ichnn]/LinChannelId"!]
        [!FOR "iter" = "$ichnn + 1" TO "$nchnn"!]
            [!ASSERT "$hwLoopChannel != substring-after(LinGlobalConfig/*[$iconf]/LinChannel/*[$iter + 1 - 1]/LinHwChannel,'_')", "Duplicate LinHwChannel IDs"!]
            [!ASSERT "$chnnID != LinGlobalConfig/*[$iconf]/LinChannel/*[$iter + 1 - 1]/LinChannelId", "Duplicate LinChannelId"!]
            [!IF "LinGlobalConfig/*[$iconf]/LinChannel/*[$iter]/LinChannelWakeUpSupport ='true'"!]
                [!VAR "tmp_wakeup_support" = "1"!]
            [!ENDIF!]
        [!ENDFOR!]
    [!ENDFOR!]
[!ENDFOR!]
[!// end check for duplicated channel id, or hw channel id

[!VAR "I"="1"!][!//
[!VAR "NC" = "0"!]
[!VAR "NN"="count(LinGlobalConfig/*)"!][!//
[!VAR "NCS" = "count(LinGlobalConfig/*[1]/LinChannel/*)"!]
[!LOOP "LinGlobalConfig/*"!]
    [!VAR "NC" ="count(LinChannel/*)"!]
    [!ASSERT "$NC = $NCS", "The configurations must have the same number of channels"!]
[!ENDLOOP!]

[!IF "$tmp_wakeup_support = 1"!]
    [!CODE!]
/* at least 1 LIN channel has WAKEUP support enabled */
#define  LIN_GLOBAL_WAKEUP_SUPPORT
    [!ENDCODE!]
[!ENDIF!]

/** 
 * @brief Link Lin channels symbolic names with Lin channel IDs
 * @remarks Covers LIN151
 */
[!LOOP "LinGlobalConfig/*[1]/LinChannel/*"!]
[!NOCODE!]
[!IF "LinHwChannel = 'eSCI_A'"!]
    [!VAR "HardwareChannel" = "num:i(0)"!]
[!ELSEIF "LinHwChannel = 'eSCI_B'"!]
    [!VAR "HardwareChannel" = "num:i(1)"!]
[!ENDIF!]
[!ENDNOCODE!]
    [!CODE!]
#define LinHWCh_[!"$HardwareChannel"!]    [!"$HardwareChannel"!]U[!//
    [!ENDCODE!]
[!ENDLOOP!]
[!ENDNOCODE!]

[!NOCODE!]
[!VAR "tmp_LinUseDMA"="0"!]
[!LOOP "LinGlobalConfig/*[1]/LinChannel/*"!][!//
[!IF "(LinHwChannel ='eSCI_A')"!][!//
[!IF "LinChannelDmaActivation"!][!//
   [!VAR "tmp_LinUseDMA" = "1"!]
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!]

[!IF "$tmp_LinUseDMA = 1 "!][!//
    [!CODE!]
/* at least 1 LIN channel has DMA support enabled */
#define LIN_USE_DMA

/** @brief No of bytes to be transferd */
#define LIN_NUM_BYTES [!"num:inttohex(node:value(LinGlobalConfig/*[1]/LinChannel/*[1]/DMAsettings/iterationCount))"!]U[!//*/

    [!ENDCODE!]
[!ENDIF!][!//
/** @brief define DMA usage */
[!LOOP "LinGlobalConfig/*[1]/LinChannel/*"!][!//
[!IF "LinHwChannel ='eSCI_A'"!][!//
#define LIN_HWCh_0_USE_DMA [!IF "LinChannelDmaActivation"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
[!ENDIF!][!//
[!IF "LinHwChannel ='eSCI_B'"!][!//
#define LIN_HWCh_1_USE_DMA STD_OFF
[!ENDIF!][!//
[!ENDLOOP!][!//

[!NOCODE!]
[!VAR "tmp_LinUseMSC"="0"!]
[!VAR "tmp_polling"="0"!]
[!LOOP "LinGlobalConfig/*[1]/LinChannel/*"!][!//
[!IF "LinChannelMSCSupport"!][!//
   [!VAR "tmp_LinUseMSC" = "1"!]
[!IF "MicroSecondChannel/PollingMode"!][!//
   [!VAR "tmp_polling" = "1"!]
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!]

[!IF "$tmp_LinUseMSC = 1 "!][!//
    [!CODE!]
/* at least 1 LIN channel has MSC support enabled */
#define LIN_USE_MSC
    [!ENDCODE!]
[!ENDIF!][!//
[!IF "$tmp_polling = 1 "!][!//
    [!CODE!]
/* at least 1 MSC channel has polling mode enabled */
#define MSC_RX_POLLING_MODE
    [!ENDCODE!]
[!ENDIF!][!//

/** @brief define MSC usage */
[!LOOP "LinGlobalConfig/*[1]/LinChannel/*"!][!//
[!IF "LinHwChannel ='eSCI_A'"!][!//
#define LIN_HWCh_0_USE_MSC [!IF "LinChannelMSCSupport"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
[!ENDIF!][!//
[!IF "LinHwChannel ='eSCI_B'"!][!//
#define LIN_HWCh_1_USE_MSC [!IF "LinChannelMSCSupport"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
[!ENDIF!][!//
[!ENDLOOP!][!//

/** @brief Symbolic Names for configured channels */
[!LOOP "LinGlobalConfig/*[1]/LinChannel/*"!][!//
#define [!"node:name(.)"!]         [!"LinChannelId"!]
[!ENDLOOP!][!//

/**
 * @brief This is the type of the external data structure containing the
 *        Frame ID, data length, Checksum, Timeout value for LIN Frame.
 */
typedef struct
{
  VAR(uint8, LIN_VAR)  HEADER[4];    /*!< Lin message header information.*/
  VAR(uint8, LIN_VAR)  DATA[LIN_MAX_DATA_LENGTH];    /*!< Data length from 0 to 7 bytes.*/
  VAR(uint8, LIN_VAR)  TYPE;    /*!< Master response or slave response.*/
}Lin_BuffType;


#ifdef LIN_USE_MSC
/**
 * @brief This type is used to specify the Polarity for the Serial
 *        Input (SI) of the MSC.
 */
typedef enum
{
    MSC_NORMAL,    /**< @brief  A RX low level bit at SI is stored
                                in the upstream channel as logic 0
                                A RX high level bit at SI is stored
                                in the upstream channel as logic 1.*/
    MSC_INVERTED   /**< @brief  A RX low level bit at SI is stored
                                in the upstream channel as logic 1
                                A RX high level bit at SI is stored
                                in the upstream channel as logic 0.*/
} Msc_PolarityType;

/**
 * @brief This type is used to specify the Parity as Even or Odd
 *        for the upstream MSC frame.
 */
typedef enum
{
    MSC_EVEN,    /**< @brief  even number of ones in character clears
                              the parity bit */
    MSC_ODD      /**< @brief  odd number of ones in character clears
                              the parity bit */
} Msc_ParityType;

/**
 * @brief This type is used to specify the number of bits of the
 *        asynchronous serial upstream frame on a MSC.
 */
typedef enum
{
    MSC_16_BITS,    /**< @brief 4-bits address field is included in the
                                frame format.*/
    MSC_12_BITS     /**< @brief 4-bits address field is not included in
                                the frame format.*/
} Msc_FrameFormatType;
#endif

/**
 * @brief This is the type of the external data structure containing the
 *        overall initialization data for one LIN Channel. A pointer to such a
 *        structure is provided to the LIN channel initialization routine for
 *        configuration of the LIN hardware channel.
 * 
 * @remarks Implements DLIN16007, DLIN04100, DLIN04101
 * @remarks Covers LIN013
 * 
 * @api
 */
typedef struct
{
#ifdef LIN_USE_MSC
    VAR(uint8, LIN_VAR) MscEnabled;                        /*!< Is MSC supported.*/
    VAR(Msc_ParityType, LIN_VAR) MscParity;                /*!< MSC parity.*/
    VAR(Msc_PolarityType, LIN_VAR) MscPolarity;            /*!< MSC polarity.*/
    VAR(Msc_FrameFormatType, LIN_VAR) Msc_FrameFormat;     /*!< MSC frame format.*/
    VAR(uint8, LIN_VAR) MscPollingMode;                    /*!< MSC polling mode */
    VAR(uint16, LIN_VAR) Msc_BaudRate_RegValue;            /*!< MSC upstream channel baudrate value.*/
#endif
    VAR(uint8, LIN_VAR) RieEnabled;                        /*!< Receiver Full Interrupt Enable.*/
    VAR(uint8, LIN_VAR) LinChannelID;                      /*!< Hardware channel.*/
[!NOCODE!]
  [!IF "NonAutosar/LinEnableDualClockMode"!]
    [!CODE!]    VAR(uint16, LIN_VAR) Lin_BaudRate_RegValue;   /*!< LIN baudrate value.*/
    VAR(uint16, LIN_VAR) Lin_BaudRate_RegValue_Alternate;     /*!< LIN baudrate value with alternate clock.*/[!ENDCODE!]
  [!ELSE!]
    [!CODE!]    VAR(uint16, LIN_VAR) Lin_BaudRate_RegValue;   /*!< LIN baudrate value.*/[!ENDCODE!]
  [!ENDIF!]
[!ENDNOCODE!]
    VAR(uint16, LIN_VAR) LinChannelWakeUpSupport; /*!< Is wake-up supported by the LIN channel ?.*/
    VAR(EcuM_WakeupSourceType, LIN_VAR) LinChannelEcuMWakeUpSource;    /*!< [LIN098] This parameter contains a reference to the Wakeup Source for this controller as defined in the ECU State Manager.*/
#ifdef LIN_USE_DMA
    VAR(uint8, LIN_VAR) LinDMAEnabled;            /*!< Is DMA supported.*/
    VAR(uint8, LIN_VAR) LinTxDMAChannel;          /*!< TxDMAChannel.*/
    VAR(uint8, LIN_VAR) LinRxDMAChannel;          /*!< RxDMAChannel.*/
    VAR(uint8, LIN_VAR) LinDMAtransferSize;       /*!< Size of transfered data. (ssize)*/
    VAR(uint16, LIN_VAR) LinDMAnbytesToTransfer;  /*!< Number of byte to transfer. (nbytes)*/
    VAR(uint16, LIN_VAR) LinDMAiterationCnt;      /*!< Current iteration count (citer, biter).*/
    VAR(uint16, LIN_VAR) LinDMAdestinationOffset; /*!< offset of destination address. (doff)*/
    VAR(uint32, LIN_VAR) LinDMAaddressAdjustment; /*!< Adjustment value to the destination address (dlast).*/
    VAR(uint8, LIN_VAR) LinDMAInterruptFlags;     /*!< TCD interrupt flags (int_half, int_maj).*/
#endif
} Lin_ChannelConfigType;

/**
 * @brief This is the type of the pointer to the external data
 *        structure containing the overall initialization data for all
 *        LIN Channels.
 *        A pointer of such a structure is provided to the LIN channel
 *        initialization routine for configuration of the LIN hardware
 *        channel.
 * 
 * @remarks Implements DLIN04000
 * @remarks Covers LIN013
 * 
 * @api
 */
typedef struct
{
    /**
     * @brief   Hardware channel.
     * @brief   Constant pointer of the constant external data
     *          structure containing the overall initialization data
     *          for all the LIN Channels.
     */
    CONSTP2CONST (Lin_ChannelConfigType,LIN_APPL_CONST,LIN_VAR) Lin_Channel[LIN_HW_MAX_MODULES];  /*!< array of constant pointers to Lin_ChannelConfigType .*/
} Lin_ConfigType;
/** @remarks Implements DLIN16006 */
[!NOCODE!][!//
[!LOOP "LinGlobalConfig/*"!][!//
[!VAR "nodeName" = "node:name(.)"!][!//
[!VAR "shortNodeName" = "concat('_C', @index)"!]
[!CODE!]

/**
 * @brief Lin Configuration data for [!"$nodeName"!].
 * 
 * @remarks Implements DLIN16006
 * 
 * @api
 */
extern CONST(Lin_ConfigType,LIN_APPL_CONST)[!"node:name(.)"!];
[!ENDCODE!][!//
[!LOOP "LinChannel/*"!][!//
[!CODE!][!//

/**
 * @brief Configuration for Lin Channel [!"LinChannelId"!] - Configuration:
 *        [!"$nodeName"!].
 * 
 * @remarks Implements DLIN16006
 * 
 * @api
 */
extern CONST(Lin_ChannelConfigType,LIN_APPL_CONST)Lin_[!"node:name(.)"!][!"$shortNodeName"!];
[!ENDCODE!][!//
[!ENDLOOP!]
[!ENDLOOP!][!//
[!ENDNOCODE!]

#endif /* LIN_CFG_H */

#ifdef __cplusplus
extern "C" }
#endif
