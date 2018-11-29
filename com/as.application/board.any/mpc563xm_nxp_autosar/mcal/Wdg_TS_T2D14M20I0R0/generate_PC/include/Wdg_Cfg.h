/*!
 * @file     Wdg_Cfg.h
 *
 * @version  2.0.0
 * @brief    AUTOSAR Wdg - Contains the implementation of the Watchdog API
 * @details  It contains the layer requested by autosar. The functions are independent of
 *           hardware settings.
 *
 * @remarks  Implements DWDG01000
 *
 * @addtogroup  Wdg
 * @{
 */

/***********************************************************************
 * PROJECT              AUTOSAR 3.0 MCAL
 * PLATFORM             PA
 * PERIPHERAL           Swt
 * DEPENDENCIES         none
 *
 * AUTOSAR VERSION      3.0.0
 * AUTOSAR REVISION     ASR_REL_3_0_REV_0003
 * AUTOSAR CONF.VARIANT
 *
 * SW VERSION           2.0.0
 * BUILDVERSION         XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223
 *
 * COPYRIGHT : (c)      2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
 *                      ALL RIGHTS RESERVED
 *
 *************************************************************************/

/*==================================================================================================
==================================================================================================*/

#ifndef WDG_CFG_H
#define WDG_CFG_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

#include "WdgIf_Types.h"
[!INCLUDE "Wdg_VersionCheck_Inc.m"!][!//
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/* @remarks Covers BSW00374, BSW00379, BSW00318 */
/* Inclusion of incompatible header files shall be avoided */
/* The integration of incompatible files shall be avoided. */
#define WDG_VENDOR_ID_CFG         43
#define WDG_AR_MAJOR_VERSION_CFG  3
#define WDG_AR_MINOR_VERSION_CFG  0
#define WDG_AR_PATCH_VERSION_CFG  0
#define WDG_SW_MAJOR_VERSION_CFG  2
#define WDG_SW_MINOR_VERSION_CFG  0
#define WDG_SW_PATCH_VERSION_CFG  0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* @remarks Covers WDG087 */
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and WDGIF_TYPES configuration header file are of the same Autosar version */
    #if (( WDG_AR_MAJOR_VERSION_CFG!= WDGIF_TYPES_AR_MAJOR_VERSION) || \
         ( WDG_AR_MINOR_VERSION_CFG!= WDGIF_TYPES_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Wdg_Cfg.h and WdgIf.h are different"
    #endif
#endif
/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/*
 * @brief  This constant specifies what value of the CR's master access protection will be used
 * @remarks Implements DWDG05000
*/
#define SWT_MAP_ENABLE_BITS      SWT_MAP_ENABLE_8BITS

/*
 * @brief  This define indicate that the watchdog is internal
 * @remarks Implements DWDG05001
*/
#define WDG_INTERNAL_MODULE         0

/*
 * @brief  This define indicate that the watchdog is external connected on SPI
 * @remarks Implements DWDG05001
*/


#define WDG_EXTERNAL_MODULE_SPI     1

/*
 * @brief  This define indicate that the watchdog is external connected on DIO
 * @remarks Implements DWDG05001
*/
#define WDG_EXTERNAL_MODULE_DIO     2

/*
 * @brief  This variable will indicate which type of driver is in use
 * @remarks Implements DWDG05000
*/
#define WDG_TYPE [!//
[!IF "text:match('',string(WdgExternalConfiguration/WdgExternalContainerRef))"!][!//
          WDG_INTERNAL_MODULE[!//
[!ELSEIF "text:match('Spi',substring-before(substring-after([!//
          WdgExternalConfiguration/WdgExternalContainerRef,'/'),'/'))"!][!//
          WDG_EXTERNAL_MODULE_SPI[!//
[!ELSE!][!//
          WDG_EXTERNAL_MODULE_DIO[!//
[!ENDIF!]
/*
 * @brief  Compile switch to enable/disable development error detection for this module
 * @remarks Implements DWDG05000
*/
#define WDG_DEV_ERROR_DETECT   [!IF "WdgGeneral/WdgDevErrorDetect"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/*
 * @brief  Compile switch to allow/forbid disabling the watchdog driver during runtime
 * @remarks Implements DWDG05000
*/
#define WDG_DISABLE_ALLOWED    [!IF "WdgGeneral/WdgDisableAllowed"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/*
 * @brief  Compile switch to enable/disable the version information
 * @remarks Implements DWDG05000
*/
#define WDG_VERSION_INFO_API   [!IF "WdgGeneral/WdgVersionInfoApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/*
 * @brief  This variable will indicate the index of the driver that it is in use
 * @remarks Implements DWDG05000
*/
#define [!"node:name(WdgGeneral/WdgIndex)"!] (uint8)[!"num:i(WdgGeneral/WdgIndex)"!]

[!LOOP "WdgModeConfig/*"!][!//
[!IF "./WdgSettingsSlow/WdgOperationMode = 'Interrupt' [!//
        or ./WdgSettingsFast/WdgOperationMode = 'Interrupt'"!]
/*
* @brief  This variable will indicate if the ISR is used
* @remarks Implements DWDG05000
*/
#define  WDG_ISR_USED
[!BREAK!]
[!ENDIF!]
[!ENDLOOP!]

 [!LOOP "WdgModeConfig/*"!][!//
 [!IF "./WdgKeyedService"!]
 /*
 * @brief  This variable will indicate if that the WdgKeyedServuce is used
 * @remarks Implements DWDG05000
 */
 #define  WDG_KEYED_SERVICE_USED
 [!BREAK!]
 [!ENDIF!]
 [!ENDLOOP!]

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*
 * @brief  Structure containing the hardware data for the Software Watchdog Timer (SWT)
 *         - the IP on which the internal Watchodg is mapped
 * @remarks Implements DWDG03001
*/


typedef struct
{
   uint32   WDG_CR;     /**< @brief The control register of SWT IP */
   uint32   WDG_TO;     /**< @brief The timeout value register of SWT IP */
   uint32   WDG_WN;     /**< @brief The window value register of SWT IP */
} SWT_HwSettingsType;

/*
 * @brief  This enumerated type will contain the watchdog driver's possible modes to be triggered
 * @remarks Implements DWDG01009
*/
typedef enum
{
    WDG_KEYED_SERVICE   = 0x00,  /**< @brief The watchdog driver is serviced using keyed sequence */
    WDG_FIXED_SERVICE            /**< @brief The watchdog driver is serviced using a fix sequence */
} Wdg_ServiceModeType;

/*
 * @brief Implementation specific. This type shall be chosen in order to have the most efficient
 *        implementation on a specific microcontroller platform.
 *        Range: 0 ... <width of the watchdog service code>
 *        Description: Width of the watchdog service code
 */
typedef uint16 Wdg_ServiceKeyWidthType;

/**
 * @brief   Structure to hold the watchdog driver configuration set.
 * @details Used for pointers to structures holding configuration data provided
 *          to the Wdg module initialization routine for configuration of the
 *          module and watchdog hardware.
 *
 * @api
 * @remarks Implements DWDG01002
*/

typedef struct
{
#if (WDG_TYPE == WDG_INTERNAL_MODULE)
    SWT_HwSettingsType    Config_Wdg_Internal[3];  /**< @brief The configuration for watchdog
                                                                 driver on SWT */
#elif (WDG_TYPE == WDG_EXTERNAL_MODULE_SPI)
    Spi_SequenceConfig      Config_Wdg_External_Spi; /**< @brief The configuration for watchdog
                                                                 driver on SPI */
#elif(WDG_TYPE == WDG_EXTERNAL_MODULE_DIO)
    Dio_ChannelGroupType    Config_Wdg_External_Dio; /**< @brief The configuration for watchdog
                                                                 driver on DIO */
#endif
    WdgIf_ModeType          Wdg_CfgDefaultMode;     /**< @brief The default mode for watchdog
                                                                 driver's configuration */
#if (WDG_TYPE == WDG_INTERNAL_MODULE)
    Wdg_ServiceModeType     Wdg_CfgServiceMode;     /**< @brief The type of the trigger mode for
                                                                watchdog driver on SWT */
    Wdg_ServiceKeyWidthType Wdg_KeyServiceValue;    /**< @brief Initial value of the service key */
#endif
} Wdg_ConfigType;

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

[!IF "IMPLEMENTATION_CONFIG_VARIANT='VariantPostBuild'"!][!//
/*
 * @brief Defines the use of Post-Build(PB) support
 * @remarks Implements DWDG05003
*/
#define WDG_CFG_EXTERN_DECLARATIONS \
[!NOCODE!][!//
    [!VAR "Wdg_NumberOfCfg"="num:i(count(WdgModeConfig/*))"!][!//
    [!VAR "Wdg_CrtNoOfCfg"="0"!][!//
[!ENDNOCODE!][!//
[!LOOP "WdgModeConfig/*"!][!//
    extern CONST(Wdg_ConfigType, WDG_CONST) [!"node:name(.)"!];[!//
[!IF "(num:i(@index)+1) < $Wdg_NumberOfCfg"!]\[!ENDIF!]
[!ENDLOOP!][!//
[!ENDIF!][!//

[!IF "IMPLEMENTATION_CONFIG_VARIANT='VariantPreCompile'"!][!//
#define WDG_PRECOMPILE_SUPPORT
/*
* @brief Defines the use of Pre compile (PC) support
* @remarks Implements DWDG05002
*/
#define WDG_CFG_EXTERN_DECLARATIONS \
    extern CONST(Wdg_ConfigType, WDG_CONST) Wdg_ConfigPC;
[!ENDIF!][!//

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /* WDG_CFG_H */
/** @} */

