/**
    @file    EcuM_Cbk.h
    @version 2.0.0

    @brief   AUTOSAR EcuM - module interface.
    @details This file contains functions prototypes and data types of the AUTOSAR EcuM.
    
    Project AUTOSAR 3.0 MCAL
    Patform PA
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
#ifndef ECUM_CBK_H
#define ECUM_CBK_H

#ifdef __cplusplus
extern "C" {
#endif
/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

#include "EcuM_Cfg.h"
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ECUM_CBK_VENDOR_ID 43
#define ECUM_CBK_MODULE_ID 10

#define ECUM_CBK_AR_MAJOR_VERSION 3
#define ECUM_CBK_AR_MINOR_VERSION 0
#define ECUM_CBK_AR_PATCH_VERSION 0
#define ECUM_CBK_SW_MAJOR_VERSION 2
#define ECUM_CBK_SW_MINOR_VERSION 0
#define ECUM_CBK_SW_PATCH_VERSION 0
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/


#if (ECUM_CBK_VENDOR_ID != ECUM_CFG_VENDOR_ID)
#error "EcuM_Cbk.h and EcuM_Cfg.h have different vendor ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
#if ((ECUM_CBK_AR_MAJOR_VERSION != ECUM_CFG_AR_MAJOR_VERSION) || \
     (ECUM_CBK_AR_MINOR_VERSION != ECUM_CFG_AR_MINOR_VERSION) || \
     (ECUM_CBK_AR_PATCH_VERSION != ECUM_CFG_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of EcuM_Cbk.h and EcuM_Cfg.h are different"
#endif
#endif

#if ((ECUM_CBK_SW_MAJOR_VERSION != ECUM_CFG_SW_MAJOR_VERSION) || \
     (ECUM_CBK_SW_MINOR_VERSION != ECUM_CFG_SW_MINOR_VERSION) || \
     (ECUM_CBK_SW_PATCH_VERSION != ECUM_CFG_SW_PATCH_VERSION))
#error "Software Version Numbers of EcuM_Cbk.h and EcuM_Cfg.h are different"
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
extern EcuM_WakeupSourceType EcuMLastWakeupEvent; /**< @brief last wakeup event to EcuM (source ID)*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
/** 
@brief   This function sets the last wakeup event of the ECUM. 
@details This is a function stub only. 
    
@param[in]     events  last wakeup event   
@return This function does not return anything

@pre  None
@post None

@remarks Covers 
@remarks Implements 
*/
FUNC(void, ECUM_CODE) EcuM_SetWakeupEvent(VAR(EcuM_WakeupSourceType, AUTOMATIC) events);

/** 
@brief   This function validates the wakeup event. 
@details This is a function stub only. Functionality is void in this implementation
    
@param[in]     events wakeup event to validate  
@return This function does not return anything

@pre  None
@post None

@remarks Covers 
@remarks Implements   
*/
FUNC(void, ECUM_CODE) EcuM_ValidateWakeupEvent(VAR(EcuM_WakeupSourceType, AUTOMATIC) events);

/** 
@brief   This function checks the wakeup source agains possible sources of wakeup. 
@details This is a function stub only. It calls the wakeup interfaces of CANIf, GPT and LIN with the wakeupSource parameter.
    
@param[in]     wakeupSource  wakeup source ID 
@return This function does not return anything

@pre  None
@post None

@remarks Covers 
@remarks Implements 
*/
FUNC(void, ECUM_CODE) EcuM_CheckWakeup(VAR(EcuM_WakeupSourceType, AUTOMATIC) wakeupSource);


#ifdef __cplusplus
}
#endif

#endif /* ECUM_CBK_H */

