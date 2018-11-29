/*!
 * @file    Port_LLD.h
 *
 * @version 2.0.0
 * @brief   AUTOSAR Port - PORT driver low level driver interface.
 * @details Interface between the high level driver (Autosar dependent) and the low level driver(IP dependent).
 *          It is platform specific.
 *
 * @addtogroup  Port
 * @{
 */

/***********************************************************************
 * PROJECT              AUTOSAR 3.0 MCAL
 * PLATFORM             PA
 * PERIPHERAL           SIU
 * DEPENDENCIES         none
 *
 * AUTOSAR VERSION      3.0.0
 * AUTOSAR REVISION     ASR_REL_3_0_REV_0003
 * AUTOSAR CONF.VARIANT
 * SW VERSION           2.0.0
 * BUILDVERSION         XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223
 *
 * COPYRIGHT : (c)      2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
 *                      ALL RIGHTS RESERVED
 **************************************************************************/

/*==================================================================================================
==================================================================================================*/

#ifndef PORT_LLD_H
#define PORT_LLD_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
 * @brief Parameters that shall be published within the Port driver header file and also in the
 *        module's description file
 * @remarks Covers BSW00374, BSW00379, BSW00318
*/
#define PORT_VENDOR_ID_LLD_H            43
#define PORT_AR_MAJOR_VERSION_LLD_H     3
#define PORT_AR_MINOR_VERSION_LLD_H     0
#define PORT_AR_PATCH_VERSION_LLD_H     0
#define PORT_SW_MAJOR_VERSION_LLD_H     2
#define PORT_SW_MINOR_VERSION_LLD_H     0
#define PORT_SW_PATCH_VERSION_LLD_H     0

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Siu_LLD.h"

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/** Check if the files Port_LLD.h and Siu_LLD.h have the same vendor **/
#if (PORT_VENDOR_ID_LLD_H != SIU_VENDOR_ID_LLD_H)
    #error "Port_LLD.h and Siu_LLD.h have different vendor ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /** Check if Port_LLD.h and Siu_LLD.h file are of the same Autosar version */
    /**
     * @file    Port_LLD.h
     * @remarks Covers PORT114
    */
    #if ((PORT_AR_MAJOR_VERSION_LLD_H != SIU_AR_MAJOR_VERSION_LLD_H) || \
         (PORT_AR_MINOR_VERSION_LLD_H != SIU_AR_MINOR_VERSION_LLD_H) || \
         (PORT_AR_PATCH_VERSION_LLD_H != SIU_AR_PATCH_VERSION_LLD_H))
      #error "AutoSar Version Numbers of Port_LLD.h and Siu_LLD.h are different"
    #endif
#endif

#if ((PORT_SW_MAJOR_VERSION_LLD_H != SIU_SW_MAJOR_VERSION_LLD_H) || \
     (PORT_SW_MINOR_VERSION_LLD_H != SIU_SW_MINOR_VERSION_LLD_H) || \
     (PORT_SW_PATCH_VERSION_LLD_H != SIU_SW_PATCH_VERSION_LLD_H))
  #error "Software Version Numbers of Port_LLD.h and Siu_LLD.h are different"
#endif

/*==================================================================================================
                                      DEFINES
==================================================================================================*/
/**
@brief  Mapping between low level layer and high level layer for PORT_LLD_Init function.
*/
#define PORT_LLD_Init                   PORT_Siu_Init
/**
@brief  Mapping between low level layer and high level layer for PORT_LLD_SetPinDirection function.
*/
#define PORT_LLD_SetPinDirection        PORT_Siu_SetPinDirection
/**
@brief  Mapping between low level layer and high level layer for PORT_LLD_RefreshPortDirection function.
*/
#define PORT_LLD_RefreshPortDirection   PORT_Siu_RefreshPortDirection
/**
@brief  Mapping between low level layer and high level layer for PORT_LLD_SetPinMode function.
*/
#define PORT_LLD_SetPinMode             PORT_Siu_SetPinMode



#ifdef __cplusplus
}
#endif

#endif /*PORT_LLD_H*/
/** @} */
