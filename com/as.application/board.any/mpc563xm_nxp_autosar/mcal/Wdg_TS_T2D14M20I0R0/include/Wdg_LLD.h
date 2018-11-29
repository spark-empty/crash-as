/*!
 * @file    Wdg_LLD.h
 *
 * @version 2.0.0
 * @brief   AUTOSAR Wdg - Contains the middle layer of the Wdg driver
 * @details Maps the autosar version of the driver with the specific hardware
 *
 * @addtogroup  Wdg
 * @{
 */

/***********************************************************************
 * PROJECT              AUTOSAR 3.0 MCAL
 * PLATFORM             PA
 * PERIPHERAL           Swt
 * DEPENDENCIES         none
 *
 * AUTOSAR VERSION      3.0.0
 * AUTOSAR REVISION     ASR_REL_3_0_REV_0003
 * AUTOSAR CONF.VARIANT
 *
 * SW VERSION           2.0.0
 * BUILDVERSION         XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223
 *
 * COPYRIGHT : (c)      2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
 *                      ALL RIGHTS RESERVED
*************************************************************************/
/*==================================================================================================
==================================================================================================*/
/*
 * @remarks Implements DWDG02000
*/

/*
 * @page misra_violations MISRA-C:2004 violations
 *
 * @section Wdg_LLD_h_REF_1
 *          Violates  MISRA  2004 Required Rule 19.15,  Precaution shall be
 *          taken in order to prevent the contents of a header file being
 *          included twice. This violation  is not  fixed since  the inclusion
 *          of MemMap.h  is as  per Autosar  requirement MEMMAP003.
*/

#ifndef WDG_LLD_H
#define WDG_LLD_H


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
/* @remarks Covers BSW00374, BSW00379, BSW00318 */
#define WDG_LLD_VENDOR_ID            43
#define WDG_LLD_AR_MAJOR_VERSION     3
#define WDG_LLD_AR_MINOR_VERSION     0
#define WDG_LLD_AR_PATCH_VERSION     0
#define WDG_LLD_SW_MAJOR_VERSION     2
#define WDG_LLD_SW_MINOR_VERSION     0
#define WDG_LLD_SW_PATCH_VERSION     0

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


/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#define WDG_START_SEC_CODE
/*
 * @note Violates MISRA 2004 Required Rule 19.15,Precaution shall be taken in
 *       order to prevent the contents of a header file being included twice.
 *       - See @ref Wdg_LLD_h_REF_1
*/
/*lint -save -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

/* This function initializes the hardware of WDG module.*/
FUNC(void, WDG_CODE) Wdg_LLD_Init(P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr);

/*  Switches the watchdog into the mode Mode */
FUNC(Std_ReturnType, WDG_CODE) Wdg_LLD_SetMode(VAR(WdgIf_ModeType, AUTOMATIC) Mode);


/* This function triggers the watchdog hardware.*/
FUNC(void, WDG_CODE) Wdg_LLD_Trigger(void);

/* The function check the settings for the Init parameter.*/
FUNC(Std_ReturnType, WDG_CODE)
    Wdg_LLD_CheckHwInitSettings(P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr);

/* The function check the settings for the mode parameter. */
FUNC(Std_ReturnType, WDG_CODE)
    Wdg_LLD_CheckHwModeSettings(VAR(WdgIf_ModeType, AUTOMATIC) Mode);


#define WDG_STOP_SEC_CODE
/*
 * @note Violates MISRA 2004 Required Rule 19.15,Precaution shall be taken in order to prevent the 
 *        contents of a header file being included twice. - See @ref Wdg_LLD_h_REF_1
*/
/*lint -save -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif

#endif /* WDG_LLD_H */
/** @} */