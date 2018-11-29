/**
    @file    Fee_Cbk.h
    @version 2.0.2.0

    @brief   AUTOSAR Fee - AUTOSAR Module Flash EEPROM Emulation Driver
    @details Definitions of the callback functions Fee_JobEndNotification 
        and Fee_JobErrorNotification
    
    Project AUTOSAR 3.0 MCAL
    Patform PA
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

@section Fee_Cbk_h_REF_1
Violates MISRA-C: 2004 Required Rule 20.2, Re-use of C90 reserved identifier. This violation is due 
to the use of "_" which is required as per Autosar.

@section Fee_Cbk_h_REF_2
Violates MISRA-C:2004 Required Rule 19.15, Repeatedly included but does not have a standard include guard. 
This violation is due to AUTOSAR requirement MEMMAP003.  

**/

#ifndef _FEE_CBK_H_
/** @note Violates MISRA-C:2004 Required Rule 20.2, Re-use of C90 reserved identifier.: 
          See @ref Fee_Cbk_h_REF_1 */
#define _FEE_CBK_H_

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/** @note Violates MISRA-C:2004 Required Rule 19.15, Repeatedly included but does not have a standard 
          include guard. See @ref Fee_Cbk_h_REF_2 */
#include "Std_Types.h"

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
/** @note Violates MISRA-C:2004 Required Rule 19.15, Repeatedly included but does not have a standard 
          include guard. See @ref Fee_Cbk_h_REF_2 */
#define FEE_START_SEC_CODE
/** @note Violates MISRA-C:2004 Required Rule 19.15, Repeatedly included but does not have a standard 
          include guard. See @ref Fee_Cbk_h_REF_2 */
#include "MemMap.h"

extern FUNC( void, FEE_CODE ) Fee_JobEndNotification( void );
extern FUNC( void, FEE_CODE ) Fee_JobErrorNotification( void );

#define FEE_STOP_SEC_CODE
/** @note Violates MISRA-C:2004 Required Rule 19.15, Repeatedly included but does not have a standard 
          include guard. See @ref Fee_Cbk_h_REF_2 */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* _FEE_CBK_H_ */
