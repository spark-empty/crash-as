/**
    @file    LinIf_Cbk.h
    @version 2.0.0

    @brief   AUTOSAR LinIf - AUTOSAR LinIf Callback module interface.
    @details AUTOSAR  LinIf Callback module interface.
    
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

#ifndef LIN_IF_CBK_H
#define LIN_IF_CBK_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
==================================================================================================*/


/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define LIN_IF_VENDOR_ID_CKB            43
#define LIN_IF_MODULE_ID_CKB            62
#define LIN_IF_AR_MAJOR_VERSION_CBK     2
#define LIN_IF_AR_MINOR_VERSION_CBK     0
#define LIN_IF_AR_PATCH_VERSION_CBK     1
#define LIN_IF_SW_MAJOR_VERSION_CBK     2
#define LIN_IF_SW_MINOR_VERSION_CBK     0
#define LIN_IF_SW_PATCH_VERSION_CBK     0

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
typedef uint8 LinIf_ChannelIndexType;

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

/*================================================================================================*/
/** 
@brief   This function is used to validate the detection of wake-up event on a given channel. 
@details This is a function stub only. 
    
@param[in]  Channel - Channel ID to validate the wake-up for.

   
@return void

@pre  None
@post None

@remarks Covers LINIF510, LINIF378
@remarks Implements 
*/
/*=================================================================================================*/
FUNC(void,LIN_CODE)LinIf_Cbk_CheckWakeup( VAR(NetworkHandleType,AUTOMATIC) Channel );

#ifdef __cplusplus
}
#endif

#endif /* LIN_IF_CBK_H */
