/**
    @file    Fee_Version.h
    @version 2.0.2.0

    @brief   AUTOSAR Fee - AUTOSAR Module Flash EEPROM Emulation Driver
    @details Flash EEPROM emulation driver version information

    Project AUTOSAR 3.0 MCAL
    Platform PA
    Peripheral none
    Dependencies Fls
    
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
/*================================================================================================*/
/**
@page misra_violations MISRA-C:2004 violations

@section Fee_Version_h_REF_1
Violates MISRA-C: 2004 Required Rule 20.2, Re-use of C90 reserved identifier. This violation is due 
to the use of "_" which is required as per Autosar.

**/

#ifndef _FEE_VERSION_H_ 
/** @note Violates MISRA-C:2004 Required Rule 20.2, Re-use of C90 reserved identifier.: 
          See @ref Fee_Version_h_REF_1 */
#define _FEE_VERSION_H_

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/* FEE module AUTOSAR major version */
#define FEE_AR_MAJOR_VERSION  1U

/* FEE module AUTOSAR minor version */
#define FEE_AR_MINOR_VERSION  2U

/* FEE module AUTOSAR patch version */
#define FEE_AR_PATCH_VERSION  0U

/* FEE module software  major version */
#define FEE_SW_MAJOR_VERSION  2U

/* FEE module software minor version */
#define FEE_SW_MINOR_VERSION  0U

/* FEE module software patch version */
#define FEE_SW_PATCH_VERSION  0U

#ifdef __cplusplus
}
#endif

#endif /* _FEE_VERSION_H_ */
