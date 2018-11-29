[!CODE!][!//
/*!
 * @file    Port_Cfg.h
 *
 * @version 2.0.0
 * @brief   AUTOSAR Port - PORT driver configuration.
 * @details This file contains the PORT driver precompile configuration.
 *
 * @addtogroup Port
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

/* PROG044 */
#ifndef PORT_CFG_H
#define PORT_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

[!INCLUDE "Port_VersionCheck_Inc.m"!][!//
/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Siu_LLD_CfgEx.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/**
 * @brief Parameters that shall be published within the Port driver header file and also in the
 *        module's description file
 * @details The integration of incompatible files shall be avoided.
 * @remarks Covers BSW00374, BSW00379, BSW00318
 */
#define PORT_VENDOR_ID_CFG_H            43
#define PORT_AR_MAJOR_VERSION_CFG_H     3
#define PORT_AR_MINOR_VERSION_CFG_H     0
#define PORT_AR_PATCH_VERSION_CFG_H     0
#define PORT_SW_MAJOR_VERSION_CFG_H     2
#define PORT_SW_MINOR_VERSION_CFG_H     0
#define PORT_SW_PATCH_VERSION_CFG_H     0

/*==================================================================================================
                                FILE VERSION CHECKS
==================================================================================================*/
/**
 * @file    Port_Cfg.h
 * @remarks Covers PORT114
 */
#if (PORT_VENDOR_ID_CFG_H != SIU_VENDOR_ID_EXT_H)
    #error "Port_Cfg.h and Siu_LLD_CfgEx.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((PORT_AR_MAJOR_VERSION_CFG_H != SIU_AR_MAJOR_VERSION_EXT_H) || \
         (PORT_AR_MINOR_VERSION_CFG_H != SIU_AR_MINOR_VERSION_EXT_H) || \
         (PORT_AR_PATCH_VERSION_CFG_H != SIU_AR_PATCH_VERSION_EXT_H))
      #error "AutoSar Version Numbers of Port_Cfg.h and Siu_LLD_CfgEx.h are different"
    #endif
#endif
#if ((PORT_SW_MAJOR_VERSION_CFG_H != SIU_SW_MAJOR_VERSION_EXT_H) || \
     (PORT_SW_MINOR_VERSION_CFG_H != SIU_SW_MINOR_VERSION_EXT_H) || \
     (PORT_SW_PATCH_VERSION_CFG_H != SIU_SW_PATCH_VERSION_EXT_H))
  #error "Software Version Numbers of Port_Cfg.h and Siu_LLD_CfgEx.h are different"
#endif

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
 * @brief   Structure needed by @p Port_Init().
 * @details The structure @p Port_ConfigType is a type for the external data
 *          structure containing the initialization data for the PORT Driver.
 * @note    The user must use the symbolic names defined in the configuration
 *          tool.
 *
 * @requirements    REQ001, REQ002, PORT018, PORT072, PORT073, PORT075, PORT079,
 *                  PORT133.
 *
 * @api
 *
 * @remarks Covers REQ001, REQ002
 * @remarks Implements DESIGN001, DESIGN002
 * @remarks Covers PORT018, PORT072, PORT073, PORT075, PORT079, PORT133
 */
typedef struct
{
    VAR(uint16,PORT_VAR) numPins; /* Number of pins Configured */
    P2CONST(Port_LLD_PinConfigType,AUTOMATIC,PORT_APPL_DATA) Port_LLD_PinConfPtr;
} Port_ConfigType;


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
/**
 * @brief Port GPIO Mode
 */
#define PORT_GPIO_MODE                  (Port_PinModeType)0
/**
 * @brief Port Primary Mode
 */
#define PORT_PRIMARY_MODE               (Port_PinModeType)1
/**
 * @brief Port Alternate 1 Mode
 */
#define PORT_ALT1_FUNC_MODE             (Port_PinModeType)2
/**
 * @brief Port Analog input Mode
 */
#define PORT_ANALOG_INPUT_MODE          (Port_PinModeType)3
/**
 * @brief Port Alternate 2 Mode
 */
#define PORT_ALT2_FUNC_MODE             (Port_PinModeType)4
/**
 * @brief Port Alternate 3 Mode
 */
#define PORT_ALT3_FUNC_MODE             (Port_PinModeType)8


/**
 * @brief Enable/Disable Development Error Detection
 * @remark Covers PORT100, PORT101
 */
#define PORT_DEV_ERROR_DETECT           [!IF "PortGeneral/PortDevErrorDetect"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
/**
 * @brief Use/remove Port_SetPinDirection function from the compiled driver
 * @remark Covers PORT117
 */
#define PORT_SET_PIN_DIRECTION_API      [!IF "PortGeneral/PortSetPinDirectionApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
/**
 * @brief Use/remove Port_SetPinMode function from the compiled driver
 * @remark Covers PORT117
 */
#define PORT_SET_PIN_MODE_API           [!IF "PortGeneral/PortSetPinModeApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
/**
 * @brief Use/remove Port_GetVersionInfo function from the compiled driver
 */
#define PORT_VERSION_INFO_API           [!IF "PortGeneral/PortVersionInfoApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!LOOP "PortConfigSet/*"!]
[!NOCODE!][!//
[!VAR "OuterLoopCounter" = "0"!][!//
[!VAR "InnerLoopCounter" = "0"!][!//
[!LOOP "PortContainer/*"!][!//
[!LOOP "PortPin/*"!][!//
[!VAR "OuterLoopCounter" = "$OuterLoopCounter + 1"!]
[!VAR "InnerLoopCounter" = "0"!]
[!VAR "Matchcounter" = "0"!]
[!VAR "Id" = "PortPinPcr"!]
[!VAR "Name" = "node:name(.)"!]
[!LOOP "../../../../PortContainer/*"!][!//
[!LOOP "PortPin/*"!][!//
[!VAR "InnerLoopCounter" = "$InnerLoopCounter + 1"!]
[!IF "$OuterLoopCounter >= $InnerLoopCounter"!]
[!IF "($Id = PortPinPcr)"!]
[!VAR "Matchcounter" = "$Matchcounter + 1"!]
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDLOOP!][!//
[!IF "$Matchcounter = 1"!]
[!ELSE!]
[!ERROR "PortPinPcr is repeated for two or more ports."!]
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDLOOP!][!//
[!LOOP "PortContainer/*"!][!//
[!LOOP "PortPin/*"!][!//
[!VAR "PortPinPcrVar" = "PortPinPcr"!][!//
[!IF "($PortPinPcrVar>ecu:get('PortMaxPinNumber'))"!][!//
[!ERROR!][!//
[!"name(.)"!] [!"': PortPinPcr '"!] [!"string($PortPinPcrVar)"!] [!"concat('- Physical pin numbers greater then ',ecu:get('PortMaxPinNumber'),' are not available in this package')"!][!//
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!][!//
[!ENDLOOP!][!//
/**
 * @brief Port Pin symbolic names
 * @details Get All Symbolic Names from configuration tool
 * @remark Covers PORT076
 */
[!VAR "OutConfigLoopCounter" = "0"!][!//
[!LOOP "PortConfigSet/*"!][!//
[!VAR "OutConfigLoopCounter" = "$OutConfigLoopCounter + 1"!][!//
[!VAR "OutPinLoopCounter" = "0"!][!//
[!LOOP "PortContainer/*"!][!//
[!VAR "ContName" = "node:name(.)"!][!//
[!LOOP "PortPin/*"!][!//
[!VAR "OutPinLoopCounter" = "$OutPinLoopCounter + 1"!][!//
[!VAR "Name" = "node:name(.)"!][!//
[!VAR "MatchCounter" = "0"!][!//
[!VAR "InConfigLoopCounter" = "0"!][!//
[!LOOP "../../../../../../PortConfigSet/*"!][!//
[!VAR "InConfigLoopCounter" = "$InConfigLoopCounter + 1"!][!//
[!VAR "InPinLoopCounter" = "0"!][!//
[!LOOP "PortContainer/*"!][!//
[!VAR "ContNameNew" = "node:name(.)"!][!//
[!LOOP "PortPin/*"!][!//
[!VAR "InPinLoopCounter" = "$InPinLoopCounter + 1"!][!//
[!IF "$InConfigLoopCounter < $OutConfigLoopCounter"!][!//
[!IF "($ContName = $ContNameNew)"!][!//
[!IF "($Name = node:name(.))"!][!//
[!IF "$InPinLoopCounter = $OutPinLoopCounter"!][!//
[!VAR "MatchCounter" = "$MatchCounter + 1"!][!//
[!ELSE!][!//
[!ERROR!][!//
[!"concat('- The same Abstract Name ',($Name),' is used for different index values')"!][!//
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDLOOP!][!//
[!ENDLOOP!][!//
[!IF "$MatchCounter = 0"!][!//
#define [!"concat(($ContName),'_',node:name(.))"!]      [!"num:i($OutPinLoopCounter - 1)"!]
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDLOOP!][!//
[!ENDLOOP!][!//

[!IF "IMPLEMENTATION_CONFIG_VARIANT='VariantPostBuild'"!]
#ifndef PORT_PRECOMPILE_SUPPORT
/**
 * @brief Declaration of config sets for PostBuild configuration
 */
#define PORT_CONFIG_PB
/**
 * @brief The maximum number of configured pins
 */
[!LOOP "PortConfigSet/*"!]
#define PORT_MAX_PIN_SETTINGS_[!"@index"!]   (uint8)[!"num:i(count(PortContainer/*/PortPin/*))"!][!ENDLOOP!]
[!LOOP "PortConfigSet/*"!]
/**
 * @brief External declaration of the Port configuration structures for post-build mode
 */
extern CONST(Port_ConfigType, PORT_CONST) [!"node:name(.)"!];[!ENDLOOP!]

/**
 * @brief Platform constant: number of available pad modes
 */
#define PAD_MODE_OPTIONS        (Port_PinModeType)[!"ecu:get('PortPadModeNumber')"!]
#endif
[!ENDIF!][!//

[!IF "IMPLEMENTATION_CONFIG_VARIANT='VariantPreCompile'"!]
/**
 * @brief Port driver Pre-Compile configuration switch
 */
#define PORT_PRECOMPILE_SUPPORT

/**
 * @brief Declaration of configuration settings for PC configuration
 */
#define PORT_CONFIG_PC
/**
 * @brief The maximum number of configured pins
 */
#define PORT_MAX_PIN_SETTINGS   (uint8)[!"num:i(count(PortConfigSet/*[1]/PortContainer/*/PortPin/*))"!]

/**
 * @brief External declaration of the Port configuration structure for pre-compiled mode
 */
extern CONST(Port_ConfigType, PORT_CONST) Port_ConfigPC;

/**
 * @brief Platform constant: number of available pad modes
 */
#define PAD_MODE_OPTIONS        (uint8)[!"ecu:get('PortPadModeNumber')"!]
[!ENDIF!][!//
/**
 * @brief Platform constant: number of available pad modes
 */
#define PAD_16BLOCK_NO          (uint8)[!"ecu:get('PortPin16BlocksNo')"!]

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
#if (PORT_SET_PIN_MODE_API == STD_ON)
/**
 * @brief External declaration of the Port pin description array
 */
extern CONST(uint16, PORT_VAR) Port_PinDescription[[!"ecu:get('PortPadModeNumber')"!]][[!"ecu:get('PortPin16BlocksNo')"!]];
#endif

#ifdef __cplusplus
}
#endif

#endif /* PORT_CFG_H */

/** @} */

/* End of File */
[!NOCODE!][!//
[!ENDNOCODE!][!//
[!ENDCODE!][!//
