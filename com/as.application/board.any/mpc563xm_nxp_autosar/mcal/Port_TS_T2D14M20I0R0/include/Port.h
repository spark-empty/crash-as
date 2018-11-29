/*!
 * @file    Port.h
 *
 * @version 2.0.0
 * @brief   AUTOSAR Port - driver API.
 * @details This file contains the PORT Autosar driver API.
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
/*
 * @page misra_violations MISRA-C:2004 violations
 *
 * @section PORT_H_REF_1
 * Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before '#include'
 * This is an Autosar memory management requirement.
 *
 * @section PORT_H_REF_2
 * Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h
 * There are different kinds of execution code sections.
 *
 * @section PORT_H_REF_3
 * Violates MISRA 2004 Advisory Rule 19.15, Repeated include file Std_Types.h
 * This comes from the order of includes in the .c file and from include dependencies.
 * As a safe approach, any file must include all its dependencies.
 */

#ifndef PORT_H
#define PORT_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/*
 * @brief Parameters that shall be published within the Port driver header file and also in the
 *        module's description file
 * @remarks Covers BSW00374, BSW00379, BSW00318
 */
#define PORT_VENDOR_ID           43
#define PORT_MODULE_ID           124
#define PORT_AR_MAJOR_VERSION    3
#define PORT_AR_MINOR_VERSION    0
#define PORT_AR_PATCH_VERSION    2
#define PORT_SW_MAJOR_VERSION    2
#define PORT_SW_MINOR_VERSION    0
#define PORT_SW_PATCH_VERSION    0

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/*
 * @file    Port.h
 * @remarks Covers PORT129
 */
/*
 * @file  Port.h
 * @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file Std_Types.h - See @ref PORT_H_REF_3
 */
#include "Std_Types.h"

/*
 * @file    Port.h
 * @remarks Covers PORT130
 */
#include "Port_Cfg.h"

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/*
 * @file    Port.h
 * @remarks Covers PORT114
 */
/* Check if the files Port.h and Port_Cfg.h have the same vendor */
#if (PORT_VENDOR_ID != PORT_VENDOR_ID_CFG_H)
    #error "Port.h and Port_Cfg.h have different vendor ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if the files Port.h and Port_Cfg.h have the same version */
    #if ((PORT_AR_MAJOR_VERSION != PORT_AR_MAJOR_VERSION_CFG_H) || \
         (PORT_AR_MINOR_VERSION != PORT_AR_MINOR_VERSION_CFG_H) || \
         (PORT_AR_PATCH_VERSION != PORT_AR_PATCH_VERSION_CFG_H))
      #error "AutoSar Version Numbers of Port.h and Port_Cfg.h are different"
    #endif
#endif
#if ((PORT_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION_CFG_H) || \
     (PORT_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION_CFG_H) || \
     (PORT_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION_CFG_H))
  #error "Software Version Numbers of Port.h and Port_Cfg.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if the files Port.h and Std_Types.h have the same version */
    #if ((PORT_AR_MAJOR_VERSION != STD_TYPES_AR_MAJOR_VERSION) || \
         (PORT_AR_MINOR_VERSION != STD_TYPES_AR_MINOR_VERSION))
      #error "AutoSar Version Numbers of Port.h and Std_Types.h are different"
    #endif
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/
/**
 * @brief   Instance ID of this port driver.
 */
#define PORT_INSTANCE_ID         (uint8)0x0

/**
 * @brief   Invalid Port Pin ID requested.
 * @details Errors and exceptions that will be detected by the PORT driver.
 *
 * @requirements    PORT031, PORT038, PORT051, PORT115, PORT087, PORT115.
 *
 * @api
 *
 * @remarks Covers PORT031, PORT038, PORT051, PORT115, PORT087, PORT115.
 */
#define PORT_E_PARAM_PIN                (uint8)0x0A
/**
 * @brief   Port Pin not configured as changeable.
 * @details Errors and exceptions that will be detected by the PORT driver.
 *
 * @requirements    PORT031, PORT038, PORT051, PORT115, PORT087, PORT115.
 *
 * @api
 *
 * @remarks Covers PORT031, PORT038, PORT051, PORT115, PORT087, PORT115.
 */
#define PORT_E_DIRECTION_UNCHANGEABLE   (uint8)0x0B
/**
 * @brief   API Port_Init() service called with wrong parameter.
 * @details Errors and exceptions that will be detected by the PORT driver.
 *
 * @requirements    PORT031, PORT038, PORT051, PORT115, PORT087, PORT115.
 *
 * @api
 *
 * @remarks Covers PORT031, PORT038, PORT051, PORT115, PORT087, PORT115.
 */
#define PORT_E_PARAM_CONFIG             (uint8)0x0C
/**
 * @brief   API Port_SetPinMode() service called when mode is unchangeable.
 * @details Errors and exceptions that will be detected by the PORT driver.
 *
 * @requirements    PORT031, PORT038, PORT051, PORT115, PORT087, PORT115.
 *
 * @api
 *
 * @remarks Covers PORT031, PORT038, PORT051, PORT115, PORT087, PORT115.
 */
#define PORT_E_PARAM_INVALID_MODE       (uint8)0x0D
/**
 * @brief   API Port_SetPinMode() service called when mode is unchangeable.
 * @details Errors and exceptions that will be detected by the PORT driver.
 *
 * @requirements    PORT031, PORT038, PORT051, PORT115, PORT087, PORT115.
 *
 * @api
 *
 * @remarks Covers PORT031, PORT038, PORT051, PORT115, PORT087, PORT115.
 */
#define PORT_E_MODE_UNCHANGEABLE        (uint8)0x0E
/**
 * @brief   API service called without module initialization.
 * @details Errors and exceptions that will be detected by the PORT driver.
 *
 * @requirements    PORT031, PORT038, PORT051, PORT115, PORT087, PORT115.
 *
 * @api
 *
 * @remarks Covers PORT031, PORT038, PORT051, PORT115, PORT087, PORT115.
 */
#define PORT_E_UNINIT                   (uint8)0x0F
/**
 * @brief   API service called with NULL pointer.
 * @details Errors and exceptions that will be detected by the PORT driver.
 *
 * @requirements    PORT038, PORT077.
 *
 * @api
 *
 * @remarks Covers PORT038, PORT077.
 */
#define  PORT_E_INVALID_POINTER         (uint8)0x10
/**
 * @brief   API service called with invalid direction.
 * @details Errors and exceptions that will be detected by the PORT driver.
 *
 * @requirements    PORT038, PORT077.
 *
 * @api
 *
 * @remarks Covers PORT038, PORT077.
 */
#define  PORT_E_INVALID_DIRECTION       (uint8)0x11

/* Service IDs */
/**
 * @brief   API service ID for PORT Init function.
 * @details Parameters used when raising an error/exception.
 *
 * @api
 *
 */
#define PORT_INIT_ID                    (uint8)0x00
/**
 * @brief   API service ID for PORT set pin direction function.
 * @details Parameters used when raising an error/exception.
 *
 * @api
 *
 */
#define PORT_SETPINDIRECTION_ID         (uint8)0x01
/**
 * @brief   API service ID for PORT refresh pin direction function.
 * @details Parameters used when raising an error/exception.
 *
 * @api
 *
 */
#define PORT_REFRESHPINDIRECTION_ID     (uint8)0x02
/**
 * @brief   API service ID for PORT get version info function.
 * @details Parameters used when raising an error/exception.
 *
 * @api
 *
 */
#define PORT_GETVERSIONINFO_ID          (uint8)0x03
/**
 * @brief   API service ID for PORT set pin mode.
 * @details Parameters used when raising an error/exception.
 *
 * @api
 *
 */
#define PORT_SETPINMODE_ID              (uint8)0x04


#ifdef PORT_PRECOMPILE_SUPPORT
PORT_CONFIG_PC
#endif

#ifndef PORT_PRECOMPILE_SUPPORT
PORT_CONFIG_PB
#endif

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
/* Allocate defined section for PORT code */
#define PORT_START_SEC_CODE
/*
 * @file  Port.h
 * @note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before '#include' - See @ref PORT_H_REF_1
 * @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref PORT_H_REF_2
 */
#include "MemMap.h"

/**
 * @brief   Initializes the Port Driver module.
 * @details The function @p Port_Init() will initialize ALL ports and port pins
 *          with the configuration set pointed to by the parameter @p ConfigPtr.
 * @post    Port_Init() must be called before all other Port Driver module's functions
 *          otherwise no operation can occur on the MCU ports and port pins.
 *
 * @param[in] ConfigPtr     A pointer to the structure which contains
 *                          initialization parameters.
 *
 * @requirements    PORT078, PORT071, PORT113, PORT140, PORT100, PORT107,
 *                  PORT031, PORT051, PORT087, PORT105, PORT121, PORT002,
 *                  PORT003, PORT005, PORT113, PORT041, PORT042, PORT043.
 *
 * @api
 *
 * @remarks Covers PORT078, PORT071, PORT55, PORT140
 * @remarks Covers PORT100, PORT107
 * @remarks Covers PORT031, PORT051, PORT087
 * @remarks Covers PORT105
 * @remarks Covers PORT121
 * @remarks Covers PORT002, PORT003, PORT005, PORT113
 * @remarks Covers PORT041, PORT042, PORT043
 * @remarks Implements DESIGN001, DESIGN002, DPORT01013, DPORT01030
 * @remarks Implements DPORT01011, DPORT01015, DPORT01014, DPORT05000
 */
extern FUNC(void, PORT_CODE) Port_Init
(
    P2CONST(Port_ConfigType,AUTOMATIC,PORT_APPL_DATA) ConfigPtr
);

/**
 * @brief   Sets the port pin direction.
 * @details The function @p Port_SetPinDirection() will set the port pin direction
 *          during runtime.
 * @pre     @p Port_Init() must have been called first. In order to change the
 *          pin direction the PortPinDirectionChangeable flag must have been set
 *          to @p TRUE.
 *
 * @param[in] Pin           Pin ID number.
 * @param[in] Direction     Port Pin direction.
 *
 * @requirements    PORT059, PORT063, PORT086, PORT117, PORT141.
 *
 * @api
 *
 * @remarks Covers PORT059, PORT063, PORT086, PORT117, PORT141
 * @remarks Implements DESIGN001, DESIGN002, DPORT01013
 */
#if (PORT_SET_PIN_DIRECTION_API == STD_ON) || defined(__DOXYGEN__)
extern FUNC(void, PORT_CODE) Port_SetPinDirection
(
    VAR(Port_PinType, PORT_VAR) Pin,
    VAR(Port_PinDirectionType, PORT_VAR) Direction
);
#endif

/**
 * @brief   Refreshes port direction.
 * @details This function will refresh the direction of all configured ports to
 *          the configured direction.<br>
 *          The PORT driver will exclude from refreshing those port pins that
 *          are configured as "pin direction changeable during runtime".
 * @pre     @p Port_Init() must have been called first.
 *
 * @requirements    PORT060, PORT061, PORT117, PORT142.
 *
 * @api
 *
 * @remarks Covers PORT060, PORT061, PORT117, PORT142
 * @remarks Implements DESIGN001, DESIGN002, DPORT01012
 * @remarks Test_case TST_CS_001, TST_CS_001
 */
extern FUNC(void, PORT_CODE) Port_RefreshPortDirection
(
    void
);

/**
 * @brief   Sets the port pin mode.
 * @details The function @p Port_SetPinMode() will set the port pin mode of the
 *          referenced pin during runtime.
 * @pre     @p Port_Init() must have been called first.
 *
 * @param[in] Pin       Pin ID number.
 * @param[in] Mode      New Port Pin mode to be set on port pin.
 *
 * @requirements    PORT117, PORT145.
 *
 * @api
 *
 * @remarks Covers PORT117, PORT145
 * @remarks Implements DESIGN001, DESIGN002, DPORT01014
 */
#if (PORT_SET_PIN_MODE_API == STD_ON) || defined(__DOXYGEN__)
extern FUNC(void, PORT_CODE) Port_SetPinMode
(
    VAR(Port_PinType, PORT_VAR) Pin,
    VAR(Port_PinModeType, PORT_VAR) Mode
);
#endif

/**
 * @brief   Returns the version information of this module.
 * @details The function @p Port_GetVersionInfo() will return the version
 *          information of this module. The version information includes:<br>
 *          - Module Id,
 *          - Vendor Id,
 *          - Vendor specific version numbers.
 *          .
 *
 * @param[in,out] pVersionInfo      Pointer to where to store the version
 *                                  information of this module.
 *
 * @requirements    PORT103
 *
 * @api
 *
 * @remarks Covers PORT103
 * @remarks Implements DESIGN001, DESIGN002, DPORT01015
 */
#if  (PORT_VERSION_INFO_API == STD_ON) || defined(__DOXYGEN__)
extern FUNC (void, PORT_CODE) Port_GetVersionInfo(P2VAR(Std_VersionInfoType, PORT_VAR_FAST, PORT_APPL_DATA) pVersionInfo);
#endif /* PORT_VERSION_INFO_API == STD_ON */

#define PORT_STOP_SEC_CODE
/*
 * @file  Port.h
 * @note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before '#include' - See @ref PORT_H_REF_1
 * @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref PORT_H_REF_2
 */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* PORT_H */

/** @} */
