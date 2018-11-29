/**
    @file    Dem.c
    @version 2.0.0

    @brief   AUTOSAR Dem - module implementation.
    @details This module implements stubs for the AUTOSAR Dem
    
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

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Std_Types.h"
/** @remarks Covers DEM108 */
#include "Dem.h"

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/** @remarks Covers BSW00374, BSW00318 */
#define DEM_VENDOR_ID_C         43
#define DEM_AR_MAJOR_VERSION_C  3
#define DEM_AR_MINOR_VERSION_C  0
#define DEM_AR_PATCH_VERSION_C  0
#define DEM_SW_MAJOR_VERSION_C  2
#define DEM_SW_MINOR_VERSION_C  0
#define DEM_SW_PATCH_VERSION_C  0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#ifdef CHECK_AUTOSAR_VERSION
/* Check if source file and Std_Types header file are of the same Autosar version */
#if ((DEM_AR_MAJOR_VERSION_C != STD_TYPES_AR_MAJOR_VERSION) || \
     (DEM_AR_MINOR_VERSION_C != STD_TYPES_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Dem.c and Std_Types.h are different"
#endif

/* Check if source file and DEM header file are of the same Autosar version */
#if ((DEM_AR_MAJOR_VERSION_C != DEM_AR_MAJOR_VERSION) || \
     (DEM_AR_MINOR_VERSION_C != DEM_AR_MINOR_VERSION) || \
     (DEM_AR_PATCH_VERSION_C != DEM_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Dem.c and Dem.h are different"
#endif
#endif /*CHECK_AUTOSAR_VERSION*/

/* Check if source file and DEM header file are of the same Software version */
#if ((DEM_SW_MAJOR_VERSION_C != DEM_SW_MAJOR_VERSION) || \
     (DEM_SW_MINOR_VERSION_C != DEM_SW_MINOR_VERSION) || \
     (DEM_SW_PATCH_VERSION_C != DEM_SW_PATCH_VERSION))
    #error "Software Version Numbers of Dem.c and Dem.h are different"
#endif

/* Check if source file and DEM header file are of the same vendor */
#if (DEM_VENDOR_ID_C != DEM_VENDOR_ID)
    #error "Dem.c and Dem.h have different vendor ids"
#endif

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/

/* put all DEM variables into defined section */
#define DEM_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

/* Variable Definition */
VAR(Dem_EventIdType    , DEM_VAR) Dem_EventId;                     /**< @brief DEM event ID*/
VAR(Dem_EventStatusType, DEM_VAR) Dem_EventStatus;                 /**< @brief DEM event status*/
VAR(uint32, DEM_VAR)              Dem_numEventErrors = (uint32)0;  /**< @brief DEM event number of errors*/
VAR(Dem_EventIdType    , DEM_VAR) Dem_EventId2;                    /**< @brief DEM event ID2*/
VAR(Dem_EventStatusType, DEM_VAR) Dem_EventStatus2;                /**< @brief DEM event status2*/

#define DEM_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

/* put all DEM code into defined section */
#define DEM_START_SEC_CODE
#include "MemMap.h"

/*==================================================================================================
                                       GLOBAL FUNCTIONS
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
FUNC(void, DEM_CODE) Dem_ReportErrorStatus(VAR(Dem_EventIdType, AUTOMATIC) EventId, VAR(Dem_EventStatusType, AUTOMATIC) EventStatus)
{
    Dem_EventId = EventId;
    Dem_EventStatus = EventStatus;
    Dem_numEventErrors++;
}

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
FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventStatus(VAR(Dem_EventIdType, AUTOMATIC) EventId, VAR(Dem_EventStatusType, AUTOMATIC) EventStatus)
{
    Dem_EventId2 = EventId;
    Dem_EventStatus2 = EventStatus;
    return(E_OK);
}

#define DEM_STOP_SEC_CODE
#include "MemMap.h"

#ifdef __cplusplus
}
#endif
