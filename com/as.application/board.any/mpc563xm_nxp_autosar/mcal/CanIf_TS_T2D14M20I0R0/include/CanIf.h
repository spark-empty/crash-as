/**
    @file    CanIf.h
    @version 2.0.0

    @brief   AUTOSAR CanIf - CanIf module interface.
    @details AUTOSAR CanIf module interface.- Stub Version
    
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
#ifndef CANIF_H
#define CANIF_H

#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
                                         INCLUDE FILES
==================================================================================================*/
#include "EcuM.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** @remarks Covers CAN085  */
#define CANIF_VENDOR_ID                         43
#define CANIF_MODULE_ID                         60
#define CANIF_AR_MAJOR_VERSION                  3
#define CANIF_AR_MINOR_VERSION                  0
#define CANIF_AR_PATCH_VERSION                  2
#define CANIF_SW_MAJOR_VERSION                  2
#define CANIF_SW_MINOR_VERSION                  0
#define CANIF_SW_PATCH_VERSION                  0

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
#define CANIF_WAKEUP_SUPPORT  (STD_ON)

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
/** 
@brief   This function is used to checks, whether an underlying CAN driver or CAN Transceiver driver
          already signals an wakeup event by the CAN network. 
@details This is a function stub only. 
    
@param[in]  WakeupSource - Source device, who initiated the wakeup event:
                           CANcontroller or CAN transceiver

   
@return Std_ReturnType

@pre  None
@post None

@remarks Covers CANIF219
@remarks Implements 

*/
/*================================================================================================*/
#if (CANIF_WAKEUP_SUPPORT == STD_ON)
      FUNC (Std_ReturnType, CANIF_CODE) CanIf_CheckWakeup(VAR(EcuM_WakeupSourceType, CANIF_VAR) WakeupSource);
#endif

#ifdef __cplusplus
}
#endif

#endif                          /* CANIF_H */
