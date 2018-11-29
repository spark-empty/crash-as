/**
    @file    Fee_Types.h
    @version 2.0.7.0

    @brief   AUTOSAR Fee - AUTOSAR Module Flash EEPROM Emulation Driver
    @details Definitions of all flash EEPROM emulation driver exported types
    
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
    
    @addtogroup FEE
    @{
*/
/*==================================================================================================
==================================================================================================*/
/*================================================================================================*/
/**
@page misra_violations MISRA-C:2004 violations

@section Fee_Types_h_REF_1
Violates MISRA-C: 2004 Required Rule 20.2, Re-use of C90 reserved identifier. This violation is due 
to the use of "_" which is required as per Autosar.

**/

#ifndef _FEE_TYPES_H_
/** @note Violates MISRA-C:2004 Required Rule 20.2, Re-use of C90 reserved identifier.: 
          See @ref Fee_Types_h_REF_1 */
#define _FEE_TYPES_H_

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Std_Types.h"
#include "Fls.h"

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/** 
 * @brief Fee block configuration structure
 * @api
 * @remarks Implements DFEE21302
*/
typedef struct 
{
/**
 * @brief Fee block number
 */ 
  uint16 blockNumber;       
/**
 * @brief Size of Fee block in bytes 
 */ 
  uint16 blockSize;        
/**
 * @brief Index of cluster group the Fee block belongs to
 */ 
  uint8 clrGrp;          
/**
 * @brief TRUE if immediate data block 
 */ 
  boolean immediateData;   
} Fee_BlockConfigType;

/**
 * @brief Fee cluster configuration structure
 * @api
 * @remarks Implements DFEE21303
*/
typedef struct 
{
/**
 * @brief Address of Fee cluster in flash 
 */ 
  Fls_AddressType startAddr;   
/**
 * @brief Size of Fee cluster in bytes 
 */ 
  Fls_LengthType length;       
} Fee_ClusterType;

/**
 * @brief Fee cluster group configuration structure
 * @api
 * @remarks Implements DFEE21304
*/
typedef struct 
{
/**
 * @brief Pointer to array of Fee cluster configurations
 */ 
 CONSTP2CONST( Fee_ClusterType, AUTOMATIC, FEE_APPL_CONST ) clrPtr;
 /**
 * @brief Number of clusters in cluster group 
 */ 
 uint32 clrCount; 
} Fee_ClusterGroupType;

#ifdef __cplusplus
}
#endif

#endif /* _FEE_TYPES_H_ */

/** @}*/
