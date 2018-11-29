/**
    @file    Fls_InternalTypes.h
    @version 2.0.8.0

    @brief   AUTOSAR Fls - AUTOSAR Module Flash Driver
    @details Definitions of all Flash driver private types
    
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
    
    @addtogroup Fls
    @{
*/
/*==================================================================================================
==================================================================================================*/
/*==================================================================================================*/
/**
@page misra_violations MISRA-C:2004 violations

@section Fls_InternalTypes_h_REF_1
Violates MISRA-C: 2004 Advisory Rule 20.2, Re-use of C90 reserved identifier.
This violation is due to the use of "_" which is required as per Autosar

*/
/*==================================================================================================*/


#ifndef _FLS_INTERNALTYPES_H_
/** @note Violates MISRA-C:2004 Advisory Rule 20.2, Re-use of C90 reserved identifier: 
See @ref Fls_InternalTypes_h_REF_1 */
#define _FLS_INTERNALTYPES_H_

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/** 
    @brief Type of job currently executed by Fls_MainFunction
    @api
    @remarks Implements DFLS20300
*/
typedef enum
{
    /**
    * @brief erase one or more complete flash sectors
    */
    FLS_JOB_ERASE = 0,    
    /**
    * @brief write one or more complete flash pages 
    */
    FLS_JOB_WRITE,        
    /**
    * @brief read one or more bytes from flash memory 
    */
    FLS_JOB_READ,     
    /**
    * @brief compare data buffer with content of flash memory
    */
    FLS_JOB_COMPARE      
} Fls_JobType;

/** 
    @brief Result of low-level flash operation
    
    @remarks Implements DFLS31300
*/
typedef enum {
    FLS_LLD_E_OK = 0,                /**< @brief operation succeeded */
    FLS_LLD_E_FAILED,                /**< @brief operation failed due to hardware error */
    FLS_LLD_E_BLOCK_INCONSISTENT,    /**< @brief data buffer doesn't match with content of flash memory */
    FLS_LLD_E_PENDING                /**< @brief operation is pending */
} Fls_LLD_ReturnType;

/** 
    @brief Type of job currently executed by Fls_LLD_MainFunction
    @remarks Implements DFLS31304
*/
typedef enum
{
    /**
    * @brief no job executed by Fls_LLD_MainFunction 
    */    
    FLS_LLD_JOB_NONE = 0, 
    /**
    * @brief erase one flash sector 
    */    
    FLS_LLD_JOB_ERASE, 
    /**
    * @brief complete erase and start an interleaved erase flash sector 
    */
    FLS_LLD_JOB_ERASE_TEMP,
    /**
    * @brief write one or more complete flash pages 
    */
    FLS_LLD_JOB_WRITE, 
    /**
    * @brief erase blank check of flash sector
    */    
    FLS_LLD_JOB_ERASE_BLANK_CHECK 
} Fls_LLD_JobType;

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/** 
    @brief Logical sector index
    @api
    @remarks Implements DFLS20301
*/
typedef uint32 Fls_SectorIndexType;

/** 
    @brief FLASH physical sector description
    @remarks Implements DFLS30300
*/
typedef struct
{
    P2VAR(volatile uint32, AUTOMATIC, FLS_CODE) sectorStartAddressPtr; /**< @brief FLASH physical sector start address */
    P2VAR(volatile uint32, AUTOMATIC, FLS_CODE) memArrayRegBasePtr; /**< @brief memory array control/configuration register base address */
    uint32 addrSpaceBloSelValue; /**< @brief address space block select value */
    uint32 addrSpaceBloLockValue; /**< @brief address space block lock value */
    uint8 sectorBloSelRegOffset; /**< @brief block select register offset */
    uint8 addrSpaceBloPrimLockRegOffset; /**< @brief address space block primary lock register offset */
    uint8 addrSpaceBloSecoLockRegOffset; /**< @brief address space block secondary lock register offset */
    uint8 platformFlashConfRegOffset; /**< @brief PFC configuration register offset */
    uint32 platformFlashConfInvalValue; /**< @brief PFC configuration register line/page buffer invalidation value */
    boolean interleavedBlo; /**< @brief block that consists of two FLASH physical sectors */
    P2VAR(volatile uint32, AUTOMATIC, FLS_CODE) memArrayB1RegBasePtr; /**< @brief memory array control/configuration register base address Bank1 */
    uint32 interleavedSize; /**< @brief interleaved size for each Bank */
    P2VAR(volatile uint32, AUTOMATIC, FLS_CODE) sectorStartB1AddressPtr; /**< @brief FLASH physical sector start address Bank1 */    
} Fls_LLD_SectorInfoType;

/** 
    @brief FLASH array description
    @remarks Implements DFLS30301
*/
typedef struct
{
    P2VAR(volatile uint32, AUTOMATIC, FLS_CODE) memArrayRegBasePtr; /**< @brief memory array control/configuration register base address */
    boolean programSuspPossible; /**< @brief is Program suspend operation possible within FLASH array */
    boolean eraseSuspPossible; /**< @brief is Erase suspend operation possible within FLASH array */
} Fls_LLD_ArrayInfoType;


#ifdef __cplusplus
}
#endif

#endif /* _FLS_INTERNALTYPES_H_ */
/** @}*/
