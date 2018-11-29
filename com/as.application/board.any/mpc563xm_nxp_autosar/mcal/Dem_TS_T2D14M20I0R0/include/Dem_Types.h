/**
    @file    Dem_Types.h
    @version 2.0.0

    @brief   AUTOSAR Dem - module header.
    @details This file contains data types of the AUTOSAR Dem.
    
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

#ifndef DEM_TYPES_H
#define DEM_TYPES_H

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
#define DEM_TYPES_VENDOR_ID 43
#define DEM_TYPES_MODULE_ID 54

#define DEM_TYPES_AR_MAJOR_VERSION 3
#define DEM_TYPES_AR_MINOR_VERSION 0
#define DEM_TYPES_AR_PATCH_VERSION 0
#define DEM_TYPES_SW_MAJOR_VERSION 2
#define DEM_TYPES_SW_MINOR_VERSION 0
#define DEM_TYPES_SW_PATCH_VERSION 0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/
#define DEM_EVENT_STATUS_PASSED     (uint8)0x00U             /**< @brief dem event passed */
#define DEM_EVENT_STATUS_FAILED     (uint8)0x01U             /**< @brief dem event failed */
#define DEM_EVENT_STATUS_PREPASSED  (uint8)0x02U             /**< @brief dem event pre-passed */
#define DEM_EVENT_STATUS_PREFAILED  (uint8)0x03U             /**< @brief dem event pre-failed */

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/* 8.2.1.1 Dem_EventIdType */
typedef uint16 Dem_EventIdType;                              /**< @brief dem event ID type */

/* 8.2.1.4 Dem_EventStatusType */
typedef uint8 Dem_EventStatusType;                           /**< @brief dem event status type */
/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef DEM_TYPES_H */
