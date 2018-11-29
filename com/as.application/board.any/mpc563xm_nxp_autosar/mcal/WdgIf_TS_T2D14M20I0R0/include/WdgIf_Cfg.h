/**
    @file    WdgIf_Cfg.h
    @version 2.0.0

    @brief   AUTOSAR WdgIf - contains the configure data for Wdg Interface
    @details 
    
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

#ifndef WDGIF_CFG_H
#define WDGIF_CFG_H

#ifdef __cplusplus
extern "C"{
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
/** @remarks Covers BSW00374, BSW00379, BSW00318 */

/* Inclusion of incompatible header files shall be avoided */
/* The integration of incompatible files shall be avoided. */
#define WDGIF_VENDOR_ID_CFG             43
#define WDGIF_MODULE_ID_CFG             43
#define WDGIF_AR_MAJOR_VERSION_CFG      3
#define WDGIF_AR_MINOR_VERSION_CFG      0
#define WDGIF_AR_PATCH_VERSION_CFG      0
#define WDGIF_SW_MAJOR_VERSION_CFG      2
#define WDGIF_SW_MINOR_VERSION_CFG      0
#define WDGIF_SW_PATCH_VERSION_CFG      0
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/


/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
/** 
@brief  Compile switch to enable/disable development error detection for this module
@remarks Covers WDGIF007
*/
#define WDGIF_DEV_ERROR_DETECT   (STD_ON)

/** 
@brief  Constant specifying the number of controlled watchdog drivers
@remarks 
*/
#define WDGIF_NUMBER_OF_DEVICES   (uint8)1

/** 
@brief  Compile switch to enable/disable the version information
@remarks Covers 
*/
#define WDGIF_VERSION_INFO_API   (STD_ON)


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

#endif /*WDGIF_CFG_H*/


