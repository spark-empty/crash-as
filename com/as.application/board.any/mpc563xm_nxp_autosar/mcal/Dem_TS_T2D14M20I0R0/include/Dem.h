/**
    @file    Dem.h
    @version 2.0.0

    @brief   AUTOSAR Dem - module interface.
    @details This file contains the functions prototypes and data types of the AUTOSAR Dem.
    
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

#ifndef DEM_H
#define DEM_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Dem_IntErrId.h"
/** @remarks Covers DEM108 */
#include "Dem_Types.h"  

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** @remarks Covers DEM112 */
#define DEM_VENDOR_ID        43
#define DEM_MODULE_ID        54
#define DEM_AR_MAJOR_VERSION 2
#define DEM_AR_MINOR_VERSION 1
#define DEM_AR_PATCH_VERSION 2
#define DEM_SW_MAJOR_VERSION 2
#define DEM_SW_MINOR_VERSION 0
#define DEM_SW_PATCH_VERSION 0
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#if (DEM_VENDOR_ID != DEM_INTERRID_VENDOR_ID)
#error "Dem.h and Dem_IntErrId.h have different vendor ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
#if ((DEM_AR_MAJOR_VERSION != DEM_INTERRID_AR_MAJOR_VERSION) || \
     (DEM_AR_MINOR_VERSION != DEM_INTERRID_AR_MINOR_VERSION) || \
     (DEM_AR_PATCH_VERSION != DEM_INTERRID_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of Dem.h and Dem_IntErrId.h are different"
#endif
#endif

#if ((DEM_SW_MAJOR_VERSION != DEM_INTERRID_SW_MAJOR_VERSION) || \
     (DEM_SW_MINOR_VERSION != DEM_INTERRID_SW_MINOR_VERSION) || \
     (DEM_SW_PATCH_VERSION != DEM_INTERRID_SW_PATCH_VERSION))
#error "Software Version Numbers of Dem.h and Dem_IntErrId.h are different"
#endif

#if (DEM_VENDOR_ID != DEM_TYPES_VENDOR_ID)
#error "Dem.h and Dem_Types.h have different vendor ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
#if ((DEM_AR_MAJOR_VERSION != DEM_TYPES_AR_MAJOR_VERSION) || \
     (DEM_AR_MINOR_VERSION != DEM_TYPES_AR_MINOR_VERSION) || \
     (DEM_AR_PATCH_VERSION != DEM_TYPES_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of Dem.h and Dem_Types.h are different"
#endif
#endif

#if ((DEM_SW_MAJOR_VERSION != DEM_TYPES_SW_MAJOR_VERSION) || \
     (DEM_SW_MINOR_VERSION != DEM_TYPES_SW_MINOR_VERSION) || \
     (DEM_SW_PATCH_VERSION != DEM_TYPES_SW_PATCH_VERSION))
#error "Software Version Numbers of Dem.h and Dem_Types.h are different"
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

extern VAR(Dem_EventIdType    , DEM_VAR) Dem_EventId;      /**< @brief DEM event ID*/
extern VAR(Dem_EventStatusType, DEM_VAR) Dem_EventStatus;  /**< @brief DEM event status*/
extern VAR(Dem_EventIdType    , DEM_VAR) Dem_EventId2;     /**< @brief DEM event ID2*/
extern VAR(Dem_EventStatusType, DEM_VAR) Dem_EventStatus2; /**< @brief DEM event status2*/


/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
/** 
@brief   This function reports the error status. 
@details This is a function stub only. It loads Dem_EventId = EventId and Dem_EventStatus = EventStatus and increments Dem_numEventErrors
    
@param[in]     EventId      ID of the event
@param[in]     EventStatus  status of the event
@return        void         This function does not return anything

@pre  None
@post None

@remarks Covers 
@remarks Implements    
*/
extern FUNC(void, DEM_CODE) Dem_ReportErrorStatus       (VAR(Dem_EventIdType, AUTOMATIC) EventId, VAR(Dem_EventStatusType, AUTOMATIC) EventStatus);

/** 
@brief   This function sets the error status. 
@details This is a function stub only. It loads Dem_EventId2 = EventId and Dem_EventStatus2 = EventStatus and returns success.
    
@param[in]     EventId        ID of the event
@param[in]     EventStatus    status of the event 
@return        Std_ReturnType This function is always successful

@pre  None
@post None

@remarks Covers 
@remarks Implements  
*/
extern FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventStatus(VAR(Dem_EventIdType, AUTOMATIC) EventId, VAR(Dem_EventStatusType, AUTOMATIC) EventStatus);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef DEM_H */
