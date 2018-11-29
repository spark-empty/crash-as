/**
    @file    Dem_IntErrId.h
    @version 2.0.0

    @brief   AUTOSAR Dem - module error codes.
    @details This file contains error IDs of the AUTOSAR Dem.
    
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

#ifndef DEM_INTERRID_H
#define DEM_INTERRID_H

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
#define DEM_INTERRID_VENDOR_ID 43
#define DEM_INTERRID_MODULE_ID 54

#define DEM_INTERRID_AR_MAJOR_VERSION 3
#define DEM_INTERRID_AR_MINOR_VERSION 0
#define DEM_INTERRID_AR_PATCH_VERSION 0
#define DEM_INTERRID_SW_MAJOR_VERSION 2
#define DEM_INTERRID_SW_MINOR_VERSION 0
#define DEM_INTERRID_SW_PATCH_VERSION 0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Note: No included files*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/
/*GPT Event IDs */
#define GPT_E_TIMEOUT_TRANSITION  10001U      /**< @brief GPT timeout event*/

/* WDG Event IDs */
#define WDG_E_MODE_SWITCH_FAILED  10201U      /**< @brief WDG mode switch failed*/
#define WDG_E_DISABLE_REJECTED    10202U      /**< @brief WDG disable request rejected */
#define WDG_E_MISS_TRIGGER        10203U      /**< @brief WDG trigger missed */

/* MCU Event IDs */
#define MCU_E_CLOCK_FAILURE        10301U     /**< @brief MCU clock failure */
#define MCU_E_LOCK_FAILURE         10302U     /**< @brief MCU PLL lock failure */
#define MCU_E_QUARTZ_FAILURE       10303U     /**< @brief MCU quartz failure */
#define MCU_E_TIMEOUT_TRANSITION   10304U     /**< @brief MCU transition timeout */

/* Pwm Event IDs */
#define     PWM_E_UNEXPECTED_IRQ   12101U     /**< @brief unexpected PWM IRQ received */

/* CAN Event IDs */
#define     CAN_E_TIMEOUT           8001U     /**< @brief  Can timeout error */

/* LIN Event IDs */
#define     LIN_E_TIMEOUT           8201U     /**< @brief  LIN timeout error */

/* SPI Event IDs */
#define     SPI_E_TIMEOUT           8301U     /**< @brief  SPI timeout error */

/* ADC Event IDs */
#define     ADC_E_TIMEOUT          12301U     /**< @brief  ADC timeout error */

/* FLS Event IDs */
#define     FLS_E_ERASE_FAILED         9210U  /**< @brief  Flash erase failed (HW) */
#define     FLS_E_WRITE_FAILED         9211U  /**< @brief  Flash write failed (HW) */
#define     FLS_E_READ_FAILED          9212U  /**< @brief  Flash read failed (HW) */
#define     FLS_E_COMPARE_FAILED       9213U  /**< @brief  Flash compare failed (HW) */
#define     FLS_E_UNEXPECTED_FLASH_ID  9220U  /**< @brief  Hardware ID not matched */
#define     FLS_E_TIMEOUT              9221U  /**< @brief  FLS timeout error */

/* FEE Event IDs */
#define     FEE_E_WRITE_FAILED         2101U  /**< @brief  Fee Write failed */

/* FR Event IDs */
#define     FR_E_ACCESS                8101U  /**< @brief  FlexRay error */


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
#ifdef __cplusplus
}
#endif

#endif /* DEM_INTERRID_H */
