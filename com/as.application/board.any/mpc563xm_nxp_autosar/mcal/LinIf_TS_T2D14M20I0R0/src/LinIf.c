/**
    @file    LinIf.c
    @version 2.0.0

    @brief   AUTOSAR LinIf - LinIf module interface.
    @details LinIf module interface.
    
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

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Lin.h"
#include "LinIf.h"
#include "LinIf_Cbk.h"
#include "EcuM.h"



/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/** @remarks Covers LINIF383 */
#define LIN_IF_VENDOR_ID_C            43
#define LIN_IF_MODULE_ID_C            62
#define LIN_IF_AR_MAJOR_VERSION_C     3
#define LIN_IF_AR_MINOR_VERSION_C     0
#define LIN_IF_AR_PATCH_VERSION_C     0
#define LIN_IF_SW_MAJOR_VERSION_C     2
#define LIN_IF_SW_MINOR_VERSION_C     0
#define LIN_IF_SW_PATCH_VERSION_C     0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#if (LIN_IF_VENDOR_ID_C != LIN_IF_VENDOR_ID)
#error "LinIf.c and LinIF.h have different vendor Ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
#if ((LIN_IF_AR_MAJOR_VERSION_C != LIN_IF_AR_MAJOR_VERSION) || \
     (LIN_IF_AR_MINOR_VERSION_C != LIN_IF_AR_MINOR_VERSION) || \
     (LIN_IF_AR_PATCH_VERSION_C != LIN_IF_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of LinIf.c and LinIf.h are different"
#endif
#endif

#if ((LIN_IF_SW_MAJOR_VERSION_C != LIN_IF_SW_MAJOR_VERSION) || \
     (LIN_IF_SW_MINOR_VERSION_C != LIN_IF_SW_MINOR_VERSION))
#error "Software Version Numbers of LinIf.c and LinIf.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
#if ((LIN_IF_AR_MAJOR_VERSION_C != LIN_AR_MAJOR_VERSION) || \
     (LIN_IF_AR_MINOR_VERSION_C != LIN_AR_MINOR_VERSION))
#error "AutoSar Version Numbers of LinIf.c and Lin.h are different"
#endif
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


/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
/** 
@brief   This function is used to validate the detection of wake-up event on a given channel. 
@details This is a function stub only. 
    
@param[in]  Channel - Channel ID to validate the wake-up for

   
@return void

@pre  None
@post None

@remarks Covers LINIF510, LINIF378
@remarks Implements 

*/
void LinIf_Cbk_CheckWakeup(VAR(NetworkHandleType, AUTOMATIC) Channel)
{

    /* Lin_WakeUpValidation(Channel); */
    return;
}



#ifdef __cplusplus
}
#endif




