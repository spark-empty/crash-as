/**
    @file    EcuM_Cfg.h
    @version 2.0.0

    @brief   AUTOSAR EcuM - module configuration parameters file.
    @details This file contains the generated configuration parameters for the AUTOSAR EcuM.
    
    Project AUTOSAR 3.0 MCAL
    Platform PA
    Peripheral 
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

#ifndef ECUM_CFG_H
#define ECUM_CFG_H

#ifdef __cplusplus
extern "C" {
#endif
/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ECUM_CFG_VENDOR_ID 43
#define ECUM_CFG_MODULE_ID 10

#define ECUM_CFG_AR_MAJOR_VERSION 3
#define ECUM_CFG_AR_MINOR_VERSION 0
#define ECUM_CFG_AR_PATCH_VERSION 0
#define ECUM_CFG_SW_MAJOR_VERSION 2
#define ECUM_CFG_SW_MINOR_VERSION 0
#define ECUM_CFG_SW_PATCH_VERSION 0
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
#if (defined ECUM_INCLUDE_DET) /* to prevent double declaration */
#error ECUM_INCLUDE_DET already defined
#endif
/** \brief Initialize Det module at startup **/
[!IF "EcuMGeneral/EcuMIncludeDet = 'true'"!][!//
#define ECUM_INCLUDE_DET STD_ON
[!ELSE!][!//
#define ECUM_INCLUDE_DET STD_OFF
[!ENDIF!][!//

#if (defined ECUM_INCLUDE_DEM) /* to prevent double declaration */
#error ECUM_INCLUDE_DEM already defined
#endif
/** \brief Initialize Dem module at startup **/
[!IF "EcuMGeneral/EcuMIncludeDem = 'true'"!][!//
#define ECUM_INCLUDE_DEM STD_ON
[!ELSE!][!//
#define ECUM_INCLUDE_DEM STD_OFF
[!ENDIF!][!//

#if (defined ECUM_INCLUDE_NVM) /* to prevent double declaration */
#error ECUM_INCLUDE_NVM already defined
#endif
/** \brief Initialize NvM module at startup **/
[!IF "EcuMGeneral/EcuMIncludeNvramMgr = 'true'"!][!//
#define ECUM_INCLUDE_NVM STD_ON
[!ELSE!][!//
#define ECUM_INCLUDE_NVM STD_OFF
[!ENDIF!][!//

#if (defined ECUM_INCLUDE_WDGM) /* to prevent double declaration */
#error ECUM_INCLUDE_WDGM already defined
#endif
/** \brief Initialize WdgM module at startup **/
[!IF "EcuMGeneral/EcuMIncludeWdgM = 'true'"!][!//
#define ECUM_INCLUDE_WDGM STD_ON
[!ELSE!][!//
#define ECUM_INCLUDE_WDGM STD_OFF
[!ENDIF!][!//

#if (defined ECUM_INCLUDE_RTE) /* to prevent double declaration */
#error ECUM_INCLUDE_RTE already defined
#endif
/** \brief Check if Rte is used in EcuM **/
[!IF "count(as:modconf('Rte')/*) > 0"!][!// if RTE is in the project
#define ECUM_INCLUDE_RTE STD_ON
[!ELSE!][!//
#define ECUM_INCLUDE_RTE STD_OFF
[!ENDIF!][!//

/*------------------[user defined wakeup sources]---------------------------*/
[!LOOP "EcuMConfiguration/*"!]
[!LOOP "EcuMWakeupSource/*"!]
#if (defined [!"node:name('.')"!]) /* to prevent double declaration */
#error [!"node:name('.')"!] already defined
#endif
/** \brief Identifier for wakeup source [!"node:name('.')"!]*/
#define [!"node:name('.')"!] [!"num:inttohex(node:value('./EcuMWakeupSourceId'))"!]U
[!ENDLOOP!]
[!ENDLOOP!]

/*------------------[Sleep modes]-------------------------------------------*/
[!LOOP "EcuMConfiguration/*"!]
[!LOOP "EcuMSleepMode/*"!]
#if (defined [!"node:name('.')"!]) /* to prevent double declaration */
#error [!"node:name('.')"!] already defined
#endif
/** \brief Identifier for wakeup source [!"node:name('.')"!]*/
#define [!"node:name('.')"!] [!"num:inttohex(node:value('./EcuMSleepModeId'))"!]U
[!ENDLOOP!]
[!ENDLOOP!]
/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
typedef uint32 EcuM_WakeupSourceType; /**< @brief variable type for ECU Manager wakeup sources*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* ECUM_CFG_H */

