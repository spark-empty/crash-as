/**
    @file    WdgIf_Types.h
    @version 2.0.0

    @brief   AUTOSAR WdgIf - cWatchdog Interface common header file
    @details Contains the information that will be exported by the module
    
    Project AUTOSAR 3.0 MCAL
    Patform PA
    Peripheral generic
    Dependencies 
    
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

#ifndef WDGIF_TYPES_H
#define WDGIF_TYPES_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

/** @remarks Covers WDGIF002 */
#include "Std_Types.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** @remarks Covers BSW00374, BSW00379, BSW00318 */
#define WDGIF_TYPES_VENDOR_ID            43
#define WDGIF_TYPES_MODULE_ID            43
#define WDGIF_TYPES_AR_MAJOR_VERSION     3
#define WDGIF_TYPES_AR_MINOR_VERSION     0
#define WDGIF_TYPES_AR_PATCH_VERSION     0
#define WDGIF_TYPES_SW_MAJOR_VERSION     2
#define WDGIF_TYPES_SW_MINOR_VERSION     0
#define WDGIF_TYPES_SW_PATCH_VERSION     0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and WDGIF_TYPES configuration header file are of the same Autosar version */
    #if ((WDGIF_TYPES_AR_MAJOR_VERSION != STD_TYPES_AR_MAJOR_VERSION) || \
         (WDGIF_TYPES_AR_MINOR_VERSION != STD_TYPES_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of WdgIf.h and Std_Types.h are different"
    #endif
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
                                             ENUMS
==================================================================================================*/
/** 
@brief  This enumerated type will contain the watchdog driver's possible states 
@remarks Covers WDGIF010, WDGIF011, WDGIF014
*/
typedef enum
{
    WDGIF_UNINIT         = 0x00,  /**< @brief The watchdog driver is not uninitialized.  This shall be the default value after reset */
    WDGIF_IDLE,                   /**< @brief = 0x01 The watchdog driver is currently idle, i.e not beeing triggered or mode changed */
    WDGIF_BUSY                    /**< @brief = 0x02 The watchdog driver is currently busy, i.e triggered or switchd between modes */
}WdgIf_StatusType;

/** 
@brief  This enumerated type will contain the watchdog driver's possible modes 
@remarks Covers WDGIF016
*/

typedef enum {
    WDGIF_OFF_MODE      = 0,/**< @brief  In this mode, the watchdog driver is disabled (switched off). */
    WDGIF_SLOW_MODE,        /**< @brief  =0x01 In this mode, the watchdog driver is set up for a long timeout period (slow triggering).*/
    WDGIF_FAST_MODE         /**< @brief  =0x02 In this mode, the watchdog driver is set up for a short timeout period (fast triggering).*/
} WdgIf_ModeType;
/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /*WDGIF_TYPES_H*/
