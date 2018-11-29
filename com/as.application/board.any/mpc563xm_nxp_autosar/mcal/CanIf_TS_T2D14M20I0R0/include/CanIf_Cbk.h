/**
    @file    CanIf_Cbk.h
    @version 2.0.0

    @brief   AUTOSAR CanIf - CanIf module interface.
    @details AUTOSAR CanIf module interface - Stub version.
    
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

#ifndef CANIF_CBK_H
#define CANIF_CBK_H

#ifdef  __cplusplus
extern "C"
{
#endif
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** @remarks Covers CAN085  */
#define CANIF_CBK_VENDOR_ID                         43
#define CANIF_CBK_MODULE_ID                         60
#define CANIF_CBK_AR_MAJOR_VERSION                  3
#define CANIF_CBK_AR_MINOR_VERSION                  0
#define CANIF_CBK_AR_PATCH_VERSION                  2
#define CANIF_CBK_SW_MAJOR_VERSION                  2
#define CANIF_CBK_SW_MINOR_VERSION                  0
#define CANIF_CBK_SW_PATCH_VERSION                  0

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/* Structure of this type contains configuration information for one receive buffer. */

typedef P2CONST(uint8, CAN_VAR, CAN_APPL_CONST) uint8Ptr;

typedef enum
{
    CANIF_CONTROLLER_WAKEUP = 0,
    CANIF_TRANSCEIVER_WAKEUP
} CanIf_WakeupSourceType;

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

FUNC (void, CAN_CODE) CanIf_TxConfirmation(PduIdType CanTxPduId);

FUNC (void, CAN_CODE) CanIf_RxIndication(uint8 Hrh, Can_IdType CanId, uint8 CanDlc, uint8Ptr CanSduPtr);

FUNC (void, CAN_CODE) CanIf_CancelTxConfirmation(const Can_PduType * PduInfoPtr);

FUNC (void, CAN_CODE) CanIf_ControllerBusOff(uint8 Controller);


#ifdef __cplusplus
}
#endif

#endif                          /* CANIF_CBK_H */
