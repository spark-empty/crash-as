/**
    @file    Fls.h
    @version 2.0.4.0

    @brief   AUTOSAR Fls - AUTOSAR Module Flash Driver
    @details Include all external API declarations and definitions of
        all pre-compile parameters

    Project AUTOSAR 3.0 MCAL
    Patform PA
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

@section Fls_h_REF_1
Violates MISRA-C: 2004 Advisory Rule 20.2, Re-use of C90 reserved identifier.
This violation is due to the use of "_" which is required as per Autosar

*/
/*==================================================================================================*/
#ifndef _FLS_H_
/** @note Violates MISRA-C:2004 Advisory Rule 20.2, Re-use of C90 reserved identifier:
See @ref Fls_h_REF_1 */
#define _FLS_H_

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Fls_Cfg.h"
#include "Fls_Api.h"


#ifdef __cplusplus
}
#endif

#endif /* _FLS_H_ */
