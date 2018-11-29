/**
    @file    Det.h
    @version 2.0.0

    @brief   AUTOSAR Det - module interface.
    @details This file contains the functions prototypes and data types of the AUTOSAR Det.
    
    Project AUTOSAR 3.0 MCAL
    Platform PA
    Peripheral 
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

#ifndef DET_H
#define DET_H

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
/** @remarks Covers DET003 */
#define DET_VENDOR_ID 43
#define DET_MODULE_ID 15

#define DET_AR_MAJOR_VERSION 2
#define DET_AR_MINOR_VERSION 2
#define DET_AR_PATCH_VERSION 1
#define DET_SW_MAJOR_VERSION 2
#define DET_SW_MINOR_VERSION 0
#define DET_SW_PATCH_VERSION 0
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

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
extern VAR(uint16, DET_VAR) Det_ModuleId;       /**< @brief DET module ID*/
extern VAR(uint8 , DET_VAR) Det_InstanceId;     /**< @brief DET instance ID*/
extern VAR(uint8 , DET_VAR) Det_ApiId;          /**< @brief DET API ID*/
extern VAR(uint8 , DET_VAR) Det_ErrorId;        /**< @brief DET Error ID*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
/** 
@brief   This function initializes the DET module. 
@details This is a function stub only. Functionality is void in this implementation
    
@param[in]     void No input parameters
@return        void This function does not return anything

@pre  None
@post None

@remarks Covers 
@remarks Implements   
*/
FUNC(void, DET_CODE) Det_Init(void);
/** 
@brief   This function provides the service for reporting of development errors. 
@details This is a function stub only. It only loads the global IDs with the IDs of the latest error that occured
    
@param[in]     ModuleId    Module ID of Calling Module
@param[in]     InstanceId  Index of Module starting at 0
@param[in]     ApiId       ID of API with Error
@param[in]     ErrorId     ID of Error
   
@return        void        This function does not return anything

@pre  None
@post None

@remarks Covers 
@remarks Implements    
*/
FUNC(void, DET_CODE) Det_ReportError(VAR(uint16, AUTOMATIC) ModuleId, VAR(uint8, AUTOMATIC) InstanceId, VAR(uint8, AUTOMATIC) ApiId, VAR(uint8, AUTOMATIC) ErrorId);

/** 
@brief   This function provides the starting after the Det_Init has been called. 
@details This is a function stub only.  Det_Init and Det_Start shall always be available. Functionality is void in this implementation
    
@param[in]     void No input parameters  
@return        void This function does not return anything

@pre  None
@post None

@remarks Covers 
@remarks Implements    
*/
FUNC(void, DET_CODE) Det_Start(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef DET_H */
