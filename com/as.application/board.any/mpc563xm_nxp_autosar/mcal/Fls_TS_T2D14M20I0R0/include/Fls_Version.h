/**
    @file    Fls_Version.h
    @version 2.0.4.0

    @brief   AUTOSAR Fls - AUTOSAR Module Flash Driver
    @details Flash driver version information
    
    Project AUTOSAR 3.0 MCAL
    Platform PA
    Peripheral Flash_Memory
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
/*==================================================================================================*/
/**

@page misra_violations MISRA-C:2004 violations

@section Fls_Version_h_REF_1
Violates MISRA-C: 2004 Advisory Rule 20.2, Re-use of C90 reserved identifier.
This violation is due to the use of "_" which is required as per Autosar

*/
/*==================================================================================================*/

#ifndef _FLS_VERSION_H_ 
/** @note Violates MISRA-C:2004 Advisory Rule 20.2, Re-use of C90 reserved identifier: 
See @ref Fls_Version_h_REF_1 */
#define _FLS_VERSION_H_

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/* FLS module AUTOSAR major version */
#define FLS_AR_MAJOR_VERSION  2U

/* FLS module AUTOSAR minor version */
#define FLS_AR_MINOR_VERSION  2U

/* FLS module AUTOSAR patch version */
#define FLS_AR_PATCH_VERSION  2U

/* FLS module software  major version */
#define FLS_SW_MAJOR_VERSION  2U

/* FLS module software minor version */
#define FLS_SW_MINOR_VERSION  0U

/* FLS module software patch version */
#define FLS_SW_PATCH_VERSION  0U

#ifdef __cplusplus
}
#endif

#endif /* _FLS_VERSION_H_ */
