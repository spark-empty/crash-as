/**
    @file    Siu_LLD_CfgEx.h
    @version 2.0.0

    @brief   AUTOSAR Dio - SIU low level driver exported structures.
    @details Interface between the high level driver (Autosar dependent) and the low level driver(platform dependent).

    Project AUTOSAR 3.0 MCAL
    Patform PA
    Peripheral SIU
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

#ifndef SIU_LLD_EX_H
#define SIU_LLD_EX_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "modules.h"
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** @remarks Covers BSW00374, BSW00379, BSW00318 */
#define SIU_VENDOR_ID_EXT_H           43
#define SIU_AR_MAJOR_VERSION_EXT_H    3
#define SIU_AR_MINOR_VERSION_EXT_H    0
#define SIU_AR_PATCH_VERSION_EXT_H    0
#define SIU_SW_MAJOR_VERSION_EXT_H    2
#define SIU_SW_MINOR_VERSION_EXT_H    0
#define SIU_SW_PATCH_VERSION_EXT_H    0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/


/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
#if (USE_PORT_MODULE == STD_ON)
/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
@brief Data type for the symbolic name of a port pin.
@details Shall cover all available port pins. The type should be chosen for the specific MCU
         platform (best performance).
@remarks Covers PORT013, PORT015
*/

typedef uint32 Port_PinType;

/**
@brief Possible directions of a port pin.
@remarks Covers PORT046
*/
typedef enum
{
    PORT_PIN_IN = 0,
    PORT_PIN_OUT
} Port_PinDirectionType;

/**
@brief Different port pin modes.
@details A port pin shall be configurable with a number of port pin modes (type Port_PinModeType).
        The type Port_PinModeType shall be used with the function call Port_SetPinMode
@remarks Covers PORT124
*/
typedef uint8 Port_PinModeType;
/**
 * @brief   Single pin configuration.
 * @details This structure contains all configuration parameters of a single pin
 *          identified by @p SIUPin.
 *
*/
typedef struct
{
    VAR(uint16, PORT_VAR)   SIUPin; /**< @brief Pin Defined on Part SIUx */
    VAR(uint16, PORT_VAR)   PCR;    /**< @brief Pad Control Register */
    VAR(sint8,  PORT_VAR)   PDO;    /**< @brief Pad Data Output */
    VAR(boolean,PORT_VAR)   DC;     /**< @brief Direction changebility*/
} Port_LLD_PinConfigType;
/**
 * @brief Data type used for Pad Selection Configuration.
 * @details This type should be chosen for the specific MCU platform (best performance).
 *
*/
typedef uint32 Port_LLD_PadSelConfigType;

#endif /*USE_PORT_MODULE*/
/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif  /* SIU_LLD_EX_H */
