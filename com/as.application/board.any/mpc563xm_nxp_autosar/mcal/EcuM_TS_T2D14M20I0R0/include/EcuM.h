/**
    @file    EcuM.h
    @version 2.0.0

    @brief   AUTOSAR EcuM - module interface.
    @details This file contains the functions prototypes and data types of the AUTOSAR EcuM.
    
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


#ifndef ECUM_H
#define ECUM_H

#ifdef __cplusplus
extern "C" {
#endif
/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/** @remarks Covers ECUM2676 */
#include "EcuM_Cbk.h"
#include "EcuM_Cfg.h"
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ECUM_VENDOR_ID 43
#define ECUM_MODULE_ID 10

#define ECUM_AR_MAJOR_VERSION 1
#define ECUM_AR_MINOR_VERSION 2
#define ECUM_AR_PATCH_VERSION 1
#define ECUM_SW_MAJOR_VERSION 2
#define ECUM_SW_MINOR_VERSION 0
#define ECUM_SW_PATCH_VERSION 0
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#if (ECUM_VENDOR_ID != ECUM_CBK_VENDOR_ID)
#error "EcuM_Cbk.h and EcuM.h have different vendor ids"
#endif

#if (ECUM_VENDOR_ID != ECUM_CFG_VENDOR_ID)
#error "EcuM_Cfg.h and EcuM.h have different vendor ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
#if ((ECUM_AR_MAJOR_VERSION != ECUM_CBK_AR_MAJOR_VERSION) || \
     (ECUM_AR_MINOR_VERSION != ECUM_CBK_AR_MINOR_VERSION) || \
     (ECUM_AR_PATCH_VERSION != ECUM_CBK_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of EcuM_Cbk.h and EcuM.h are different"
#endif

#if ((ECUM_AR_MAJOR_VERSION != ECUM_CFG_AR_MAJOR_VERSION) || \
     (ECUM_AR_MINOR_VERSION != ECUM_CFG_AR_MINOR_VERSION) || \
     (ECUM_AR_PATCH_VERSION != ECUM_CFG_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of EcuM_Cfg.h and EcuM.h are different"
#endif
#endif /*#ifdef CHECK_AUTOSAR_VERSION*/

#if ((ECUM_SW_MAJOR_VERSION != ECUM_CBK_SW_MAJOR_VERSION) || \
     (ECUM_SW_MINOR_VERSION != ECUM_CBK_SW_MINOR_VERSION) || \
     (ECUM_SW_PATCH_VERSION != ECUM_CBK_SW_PATCH_VERSION))
#error "Software Version Numbers of EcuM_Cbk.h and EcuM.h are different"
#endif

#if ((ECUM_SW_MAJOR_VERSION != ECUM_CFG_SW_MAJOR_VERSION) || \
     (ECUM_SW_MINOR_VERSION != ECUM_CFG_SW_MINOR_VERSION) || \
     (ECUM_SW_PATCH_VERSION != ECUM_CFG_SW_PATCH_VERSION))
#error "Software Version Numbers of EcuM_Cfg.h and EcuM.h are different"
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

#endif /* ECUM_H */

