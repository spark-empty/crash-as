[!CODE!][!//
/*!
 * @file    Port_PBCfg.c
 *
 * @version 2.0.0
 * @brief   AUTOSAR Port - PORT driver configuration.
 * @details This file contains the PORT driver postbuild configuration.
 *
 * @addtogroup  Port
 * @{
 */

/***********************************************************************
 * PROJECT              AUTOSAR 3.0 MCAL
 * PLATFORM             PA
 * PERIPHERAL           SIU
 * DEPENDENCIES         none
 *
 * AUTOSAR VERSION      3.0.0
 * AUTOSAR REVISION     ASR_REL_3_0_REV_0003
 * AUTOSAR CONF.VARIANT
 * SW VERSION           2.0.0
 * BUILDVERSION         XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223
 *
 * COPYRIGHT : (c)      2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
 *                      ALL RIGHTS RESERVED
 **************************************************************************/

/*==================================================================================================
==================================================================================================*/
/**
 * @page misra_violations MISRA-C:2004 violations
 *
 * @section PORT_PBCFG_REF_1
 * Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before '#include'
 * This is an Autosar requirement about the memory management.
 *
 * @section PORT_PBCFG_REF_2
 * Violates MISRA 2004 Required Rules 10.1, Implicit conversion changes signedness.
 * Many type conversions are implemented in MACROS. The code was tested successfully with 3 different compilers.
 *
 * @section PORT_PBCFG_REF_3
 * Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h
 * There are different kinds of execution code sections.
*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Port.h"

[!INCLUDE "Port_VersionCheck_Src_PB.m"!][!//
#ifndef PORT_PRECOMPILE_SUPPORT
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
 * @brief Parameters that shall be published within the Port driver header file and also in the
 *        module's description file
 * @details The integration of incompatible files shall be avoided.
 * @remarks Covers BSW00374, BSW00379, BSW00318
 */
#define PORT_VENDOR_ID_PBCFG_C            43
#define PORT_AR_MAJOR_VERSION_PBCFG_C     3
#define PORT_AR_MINOR_VERSION_PBCFG_C     0
#define PORT_AR_PATCH_VERSION_PBCFG_C     0
#define PORT_SW_MAJOR_VERSION_PBCFG_C     2
#define PORT_SW_MINOR_VERSION_PBCFG_C     0
#define PORT_SW_PATCH_VERSION_PBCFG_C     0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if Port_PBCfg.c and Port.h are of the same vendor */
#if (PORT_VENDOR_ID_PBCFG_C != PORT_VENDOR_ID)
    #error "Port_PBCfg.c and Port.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if Port_PBCfg.c and Port.h are of the same Autosar version */
    #if ((PORT_AR_MAJOR_VERSION_PBCFG_C != PORT_AR_MAJOR_VERSION) || \
         (PORT_AR_MINOR_VERSION_PBCFG_C != PORT_AR_MINOR_VERSION) || \
         (PORT_AR_PATCH_VERSION_PBCFG_C != PORT_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of Port_PBCfg.c and Port.h are different"
    #endif
#endif
/* Check if Port_PBCfg.c and Port.h are of the same software version */
#if ((PORT_SW_MAJOR_VERSION_PBCFG_C != PORT_SW_MAJOR_VERSION) || \
     (PORT_SW_MINOR_VERSION_PBCFG_C != PORT_SW_MINOR_VERSION) || \
     (PORT_SW_PATCH_VERSION_PBCFG_C != PORT_SW_PATCH_VERSION))
    #error "Software Version Numbers of Port_PBCfg.c and Port.h are different"
#endif

#define PORT_START_CONFIG_DATA_UNSPECIFIED
/**
 * @file  Port_PBcfg.c
 * @note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before '#include' - See @ref PORT_PBCFG_REF_1
 * @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref PORT_PBCFG_REF_3
 */
#include "MemMap.h"
[!NOCODE!][!//
[!/******************************************************************************/!][!//
[!/* Variable used to store Mode selected option                                */!][!//
[!/******************************************************************************/!][!//
[!/* Include package file in order to get valid Pins */!][!//
[!INCLUDE "MONACO_Resource.m"!][!//
[!//
[!//
[!/*****************************************************************************/!][!//
[!/*                          MACRO GetAltConf                                 */!][!//
[!/*****************************************************************************/!][!//
[!/* Get the Alternative Mode configuration for selected pin */!][!//
[!MACRO "GetAltConf"!][!//
[!NOCODE!][!//
[!/* Alternative Mode 0 is the GPIO */!][!//
[!IF "text:match(./PortPinMode,'GPIO')"!][!//
  [!VAR "PinMode"="string('GPIO')"!][!//
[!ELSE!][!//
  [!VAR "PinMode"="concat(./PortPinMode,'_PORT',number(./PortPinPcr))"!][!//
[!ENDIF!][!//
[!VAR "PinAltConf"="number(substring-after(substring-before((substring-after($PinMap,$PinMode)),':'),';'))"!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!/*****************************************************************************/!][!//
[!//
[!//
[!/*****************************************************************************/!][!//
[!/*                            MACRO GetPCR                                   */!][!//
[!/*****************************************************************************/!][!//
[!/* Fill the PCR register for the selected pin */!][!//
[!MACRO "GetPCR"!][!//
[!NOCODE!][!//
[!VAR "PinPCR"="num:i(0)"!][!//
[!/* Get the Alternative Mode configuration and fill the PCR */!][!//
[!CALL "GetAltConf"!][!//
[!VAR "PinPCR"="bit:or($PinPCR,bit:shl($PinAltConf,10))"!][!//

[!/* Check if the pin is configured as input or output */!][!//
[!IF "boolean(./PortPinDirection)"!][!//
  [!IF "text:match(./PortPinDirection,'PortPinDirectionOut')"!][!//
    [!VAR "PinPCR"="bit:or($PinPCR,bit:shl(1,9))"!][!//
  [!ELSE!][!//
    [!VAR "PinPCR"="bit:or($PinPCR,bit:shl(1,8))"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//

[!/* Check if open drain output is enabled */!][!//
[!IF "boolean(./PortPinOde)"!][!//
  [!IF "./PortPinOde"!][!//
    [!VAR "PinPCR"="bit:or($PinPCR,bit:shl(1,5))"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//

[!/* Check if input hysteresis is enabled */!][!//
[!IF "./PortPinHysteresis"!][!//
  [!VAR "PinPCR"="bit:or($PinPCR,bit:shl(1,4))"!][!//
[!ENDIF!][!//

[!/* Check if weak pull up/down is enabled */!][!//
[!IF "./PortPinWpe"!][!//
  [!VAR "PinPCR"="bit:or($PinPCR,bit:shl(1,1))"!][!//
[!ENDIF!][!//

[!/* Check whether weak pull-up or weak pull-down is selected */!][!//
[!IF "./PortPinWps"!][!//
  [!VAR "PinPCR"="bit:or($PinPCR,1)"!][!//
[!ENDIF!][!//

[!/* Set output slew rate*/!][!//
[!IF "text:match(./PortPinSlewRate,'MaximumValue')"!][!//
  [!VAR "PinPCR"="bit:or($PinPCR,bit:shl(3,2))"!][!//
[!ELSEIF "text:match(./PortPinSlewRate,'MediumValue')"!][!//
    [!VAR "PinPCR"="bit:or($PinPCR,bit:shl(1,2))"!][!//
[!ELSEIF "text:match(./PortPinSlewRate,'MinimumValue')"!][!//
  [!VAR "PinPCR"="bit:or($PinPCR,bit:shl(0,2))"!][!//
  [!ENDIF!][!//

[!/* Set Drive Strength Control */!][!//
[!IF "text:match(./PortPinDriveStrength,'DriveStrength_10pF')"!][!//
  [!VAR "PinPCR"="bit:or($PinPCR,bit:shl(0,6))"!][!//
[!ELSEIF "text:match(./PortPinDriveStrength,'DriveStrength_20pF')"!][!//
  [!VAR "PinPCR"="bit:or($PinPCR,bit:shl(1,6))"!][!//
[!ELSEIF "text:match(./PortPinDriveStrength,'DriveStrength_30pF')"!][!//
  [!VAR "PinPCR"="bit:or($PinPCR,bit:shl(1,7))"!][!//
[!ELSEIF "text:match(./PortPinDriveStrength,'DriveStrength_50pF')"!][!//
  [!VAR "PinPCR"="bit:or($PinPCR,bit:shl(3,6))"!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!"num:inttohex($PinPCR,4)"!][!//
[!ENDMACRO!][!//
[!/*****************************************************************************/!][!//
[!//
[!//
[!/*****************************************************************************/!][!//
[!/*                            MACRO GetPDO                                   */!][!//
[!/*****************************************************************************/!][!//
[!/* Get the Alternative Mode configuration for selected pin */!][!//
[!MACRO "GetPDO"!][!//
[!NOCODE!][!//
[!/* Alternative Mode 0 is the GPIO */!][!//
[!IF "boolean(./PortPinLevelValue)"!][!//
  [!IF "text:match(./PortPinLevelValue,'PortPinLevelLow')"!][!//
    [!VAR "PinPDO"="num:i(0)"!][!//
  [!ELSE!][!//
    [!VAR "PinPDO"="num:i(1)"!][!//
  [!ENDIF!][!//
[!ELSE!][!//
  [!VAR "PinPDO"="num:i(-1)"!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!"$PinPDO"!][!//
[!ENDMACRO!][!//
[!/*****************************************************************************/!][!//
[!//
[!//
[!/*****************************************************************************/!][!//
[!/*                          MACRO GetDirConf                                 */!][!//
[!/*****************************************************************************/!][!//
[!/* Get the Alternative Mode configuration for selected pin */!][!//
[!MACRO "GetDirConf"!][!//
[!NOCODE!][!//
[!/* Alternative Mode 0 is the GPIO */!][!//
[!IF "boolean(./PortPinDirectionChangeable)"!][!//
  [!IF "./PortPinDirectionChangeable"!][!//
    [!VAR "Direction"= "string('TRUE')"!][!//
  [!ELSE!][!//
    [!VAR "Direction"= "string('FALSE')"!][!//
  [!ENDIF!][!//
[!ELSE!][!//
  [!VAR "Direction"= "string('FALSE')"!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!"$Direction"!][!//
[!ENDMACRO!][!//
[!ENDNOCODE!][!//



[!LOOP "PortConfigSet/*"!][!//
[!VAR "count"= "1"!][!//
[!VAR "Maxcount"= "num:i(count(PortContainer/*/PortPin/*))-1"!][!//
/**
 * @brief Pin default configuration data for configPB_[!"@index"!]
 */
CONST(Port_LLD_PinConfigType, PORT_CONST) Port_LLD_PinConfigPB_[!"@index"!][PORT_MAX_PIN_SETTINGS_[!"@index"!]]=
{
  /**
   * @note: Violates MISRA 2004 Required Rules 10.1,Implicit conversion changes signedness. See @ref PORT_PBCFG_REF_2
   */
[!LOOP "PortContainer/*"!][!//
[!LOOP "PortPin/*"!][!//
[!IF "$Maxcount>=$count"!][!//
  {(uint16)[!"./PortPinPcr"!], (uint16)[!CALL "GetPCR"!], (sint8)[!CALL "GetPDO"!], [!CALL "GetDirConf"!]},
[!ELSE!][!//
  {(uint16)[!"./PortPinPcr"!], (uint16)[!CALL "GetPCR"!], (sint8)[!CALL "GetPDO"!], [!CALL "GetDirConf"!]}
[!ENDIF!][!//
[!VAR "count"= "$count+1"!][!//
[!ENDLOOP!][!//
[!ENDLOOP!][!//
};

/**
 * @brief This table contains all the Configured Port Pin parameters and the
 * number of Port Pins configured by the tool for the post-build mode [!"@name"!]
 */
CONST(Port_ConfigType, PORT_CONST) [!"@name"!] =
{
  PORT_MAX_PIN_SETTINGS_[!"@index"!],
  Port_LLD_PinConfigPB_[!"@index"!]
};
[!ENDLOOP!][!//

#if (PORT_SET_PIN_MODE_API == STD_ON)
[!IF "(ecu:get('PortPackage') = 'Port_P208pin_BGA')"!]
/**
 * @brief Port Pin description data
 * @remarks Covers MCAL2881
 */
CONST (uint16, PORT_VAR) Port_PinDescription[[!"ecu:get('PortPadModeNumber')"!]][[!"ecu:get('PortPin16BlocksNo')"!]] =
{  [!"$CHECK_3"!]};
[!ENDIF!][!//
[!IF "(ecu:get('PortPackage') = 'Port_P176pin_QFP')"!]
/**
 * @brief Port Pin description data
 * @remarks Covers MCAL2881
 */
CONST (uint16, PORT_VAR) Port_PinDescription[[!"ecu:get('PortPadModeNumber')"!]][[!"ecu:get('PortPin16BlocksNo')"!]] =
{  [!"$CHECK_2"!]};
[!ENDIF!][!//
[!IF "(ecu:get('PortPackage') = 'Port_P144pin_QFP')"!]
/**
 * @brief Port Pin description data
 * @remarks Covers MCAL2881
 */
CONST (uint16, PORT_VAR) Port_PinDescription[[!"ecu:get('PortPadModeNumber')"!]][[!"ecu:get('PortPin16BlocksNo')"!]] =
{  [!"$CHECK_1"!]};
[!ENDIF!][!//
#endif

#define PORT_STOP_CONFIG_DATA_UNSPECIFIED
/**
 * @file  Port_PBcfg.c
 * @note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before '#include' - See @ref PORT_PBCFG_REF_1
 * @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref PORT_PBCFG_REF_3
 */
#include "MemMap.h"

#endif    /* PORT_PRECOMPILE_SUPPORT*/

#ifdef __cplusplus
}
#endif
/** @} */

/* End of File */
[!NOCODE!][!//
[!ENDNOCODE!][!//
[!ENDCODE!][!//
