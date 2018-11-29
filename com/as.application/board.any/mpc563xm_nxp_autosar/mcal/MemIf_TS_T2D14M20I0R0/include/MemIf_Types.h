/**
    @file        MemIf_Types.h
    @version     2.0.0

    @brief       AUTOSAR MemIf - module interface.
    @details     Stub for MemIf module - contains some typedefs needed by other components.
    
    Project      : AUTOSAR 3.0 MCAL
    Patform      : PA
    Peripheral   : XPC563XM
    Dependencies : none
    
    Autosar Version       : 3.0.0
    Autosar Revision      : ASR_REL_3_0_REV_0003
    Autosar Conf. Variant : 
    Software Version      : 2.0.0
    Build Version         : XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223

    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
    All Rights Reserved.
*/
/*==================================================================================================
==================================================================================================*/
/**
@addtogroup MEMIF_TYPES
@{
 */
#ifndef MEMIF_TYPES_H
#define MEMIF_TYPES_H

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
/** @remarks Covers MemIf005, MemIf028 */
#define MEMIF_TYPES_VENDOR_ID           43
#define MEMIF_TYPES_MODULE_ID           22
#define MEMIF_TYPES_AR_MAJOR_VERSION    1
#define MEMIF_TYPES_AR_MINOR_VERSION    2
#define MEMIF_TYPES_AR_PATCH_VERSION    1
#define MEMIF_TYPES_SW_MAJOR_VERSION    2
#define MEMIF_TYPES_SW_MINOR_VERSION    0
#define MEMIF_TYPES_SW_PATCH_VERSION    0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

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
@brief This type denotes the current status of the underlying abstraction module and device driver. 
       It shall be used as the return value of the corresponding driver's "GetStatus" function. 
@remarks Covers MemIf015
*/
typedef enum
{
    MEMIF_UNINIT = 0,           /**< @brief The underlying abstraction module or device driver has not been initialized (yet)*/
    MEMIF_IDLE,                 /**< @brief The underlying abstraction module or device driver is currently idle */
    MEMIF_BUSY,                 /**< @brief The underlying abstraction module or device driver is currently busy */
    MEMIF_BUSY_INTERNAL         /**< @brief The underlying abstraction module is busy with internal management operations.
                                            The underlying device driver can be busy or idle */
}MemIf_StatusType;


/** 
@brief This type denotes the result of the last job.
@remarks Covers MemIf016
*/
typedef enum
{
    MEMIF_JOB_OK = 0,               /**< @brief The job has been finished succesfully */
    MEMIF_JOB_FAILED,               /**< @brief The job has not been finished succesfully */
    MEMIF_JOB_PENDING,              /**< @brief The job has not yet been finished */
    MEMIF_JOB_CANCELLED,            /**< @brief The job has been cancelled */
    MEMIF_BLOCK_INCONSISTENT,       /**< @brief The requested block is inconsistent, it may contain corrupted data */
    MEMIF_BLOCK_INVALID             /**< @brief The requested block has been marked as invalid, the requested operation can not be performed */
}MemIf_JobResultType;


/** 
@brief This type denotes the operation mode of the underlying abstraction modules and device drivers.
@remarks Covers MemIf021
*/
typedef enum
{
    MEMIF_MODE_SLOW = 0,        /**< @brief The underlying memory abstraction modules and drivers are working in slow mode */
    MEMIF_MODE_FAST             /**< @brief The underlying memory abstraction modules and drivers are working in fast mode */
}MemIf_ModeType;

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

#endif /* MEMIF_TYPES_H */

/** @} */

