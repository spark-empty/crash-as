/**
    @file    WdgIf.h
    @version 2.0.0

    @brief   AUTOSAR WdgIf - cWatchdog Interface common header file
    @details Contains the information that will be exported by the module
    
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

#ifndef WDGIF_H
#define WDGIF_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

/** @remarks Covers WDGIF002 */
#include "Std_Types.h"
#include "WdgIf_Cfg.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** @remarks Covers BSW00374, BSW00379, BSW00318 */
#define WDGIF_VENDOR_ID            43
#define WDGIF_MODULE_ID            43
#define WDGIF_AR_MAJOR_VERSION     2
#define WDGIF_AR_MINOR_VERSION     2
#define WDGIF_AR_PATCH_VERSION     1
#define WDGIF_SW_MAJOR_VERSION     2
#define WDGIF_SW_MINOR_VERSION     0
#define WDGIF_SW_PATCH_VERSION     0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and WDGIF configuration header file are of the same Autosar version */
    #if ((WDGIF_AR_MAJOR_VERSION != WDGIF_AR_MAJOR_VERSION_CFG) || \
         (WDGIF_AR_MINOR_VERSION != WDGIF_AR_MINOR_VERSION_CFG) || \
         (WDGIF_AR_PATCH_VERSION != WDGIF_AR_PATCH_VERSION_CFG))
    #error "AutoSar Version Numbers of WdgIf.h and WdgIf_Cfg.h are different"
    #endif
#endif

/* Check if source file and WDGIF configuration header file are of the same software version */
#if ((WDGIF_SW_MAJOR_VERSION != WDGIF_SW_MAJOR_VERSION_CFG) || \
     (WDGIF_SW_MINOR_VERSION != WDGIF_SW_MINOR_VERSION_CFG) || \
     (WDGIF_SW_PATCH_VERSION != WDGIF_SW_PATCH_VERSION_CFG))
#error "Software Version Numbers of WdgIf.h and WdgIf_Cfg.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Std_Types header file are of the same Autosar version */
    #if ((WDGIF_AR_MAJOR_VERSION != STD_TYPES_AR_MAJOR_VERSION) || \
         (WDGIF_AR_MINOR_VERSION != STD_TYPES_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of WdgIf.h and Std_Types.h are different"
    #endif
#endif
/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
/*@brief  This define indicates the error detectable by the Watchdog Driver Interface
  @remarks Covers WDGIF030, WDGIF006
*/
#define WDGIF_E_PARAM_DEVICE    (uint8)0x01

/*@brief  Service id for the setmode function
  @remarks Covers WDGIF042
*/
#define WDGIF_SETMODE_ID   (uint8)0x01

/*@brief  Service id for the trigger function
  @remarks Covers WDGIF044
*/
#define WDGIF_TRIGGER_ID   (uint8)0x02


#if (WDGIF_NUMBER_OF_DEVICES == (uint8)1) 
    /* Only one WDG module defined */

/* @brief  Define the setmode function
   @remarks Covers WDGIF042, WDGIF043
*/  
    #define WdgIf_SetMode(DeviceIndex, WdgMode) Wdg_SetMode(WdgMode) 

/* @brief  Define the setmode function
   @remarks Covers WDGIF044, WDGIF045
*/  
    #define WdgIf_Trigger(DeviceIndex) Wdg_Trigger() 
#else 
    /* More than one WDG modules defined */ 

/* @brief  Define the setmode function
   @remarks Covers WDGIF042, WDGIF043
*/  
   #define WdgIf_SetMode(DeviceIndex, WdgMode)  
        WdgIf_SetModeFctPtr[DeviceIndex](WdgMode) 
 
/* @brief  Define the setmode function
   @remarks Covers WDGIF044, WDGIF045
*/  
    #define WdgIf_Trigger(DeviceIndex) WdgIf_TriggerFctPtr[DeviceIndex]() 
#endif 

#if (WDGIF_VERSION_INFO_API==STD_ON)

    /*@brief  Service id for the trigger function
      @remarks Covers WDGIF046
    */
    #define WDGIF_VERSION_ID   (uint8)0x03
    
    /*@brief  WdgIf_GetVersionInfo function
      @remarks Covers WDGIF046
    */
    
    #define WdgIf_GetVersionInfo(versioninfo) { (versioninfo)->vendorID = WDGIF_VENDOR_ID; \
                                                (versioninfo)->moduleID = WDGIF_MODULE_ID; \
                                                (versioninfo)->sw_major_version = WDGIF_SW_MAJOR_VERSION; \
                                                (versioninfo)->sw_minor_version = WDGIF_SW_MINOR_VERSION; \
                                                (versioninfo)->sw_patch_version = WDGIF_SW_PATCH_VERSION; \
                                              }                                         
#endif /* WDGIF_VERSION_INFO_API==STD_ON */
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


#ifdef __cplusplus
}
#endif

#endif /*WDGIF_H*/
