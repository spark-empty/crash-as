/**
    @file    Fee_InternalTypes.h
    @version 2.0.4.0

    @brief   AUTOSAR Fee - AUTOSAR Module Flash EEPROM Emulation Driver
    @details Definitions of all flash EEPROM emulation driver private types
    
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

@section Fee_InternalTypes_h_REF_1
Violates MISRA-C: 2004 Required Rule 20.2, Re-use of C90 reserved identifier. This violation is due 
to the use of "_" which is required as per Autosar.

**/

#ifndef _FEE_INTERNALTYPES_H_
/** @note Violates MISRA-C:2004 Required Rule 20.2, Re-use of C90 reserved identifier.: 
          See @ref Fee_InternalTypes_h_REF_1 */
#define _FEE_INTERNALTYPES_H_

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/**
 * @brief Status of Fee block header
 * @api
 * @remarks Implements DFEE20300
*/
typedef enum
{
    /**
     * @brief Fee block is valid 
    */
    FEE_BLOCK_VALID = 0,       
    /**
     * @brief Fee block is invalid (has been invalidated)
    */
    FEE_BLOCK_INVALID,        
    /**
     * @brief Fee block is inconsistent (contains bogus data) 
    */
    FEE_BLOCK_INCONSISTENT,     
    /**
     * @brief Fee block header is garbled 
    */
    FEE_BLOCK_HEADER_INVALID,    
    /**
     * @brief Fee block header is invalidated by Fee_InvalidateBlock()
     * @details Not used when FEE_BLOCK_ALWAYS_AVAILABLE == STD_OFF
     */
    FEE_BLOCK_INVALIDATED,        
    /**
     * @brief Fee block header is blank (end of Fee block header list) 
     */
    FEE_BLOCK_HEADER_BLANK  
} Fee_BlockStatusType;

/**
 *
 * @brief Status of Fee cluster header
 * @api  
 * @remarks Implements DFEE20301
*/
typedef enum
{
    /**
     * @brief Fee cluster is valid 
    */
    FEE_CLUSTER_VALID = 0,        
    /**
     * @brief Fee cluster is invalid 
    */
    FEE_CLUSTER_INVALID,       
    /**
     * @brief Fee cluster is inconsistent (contains bogus data) 
    */
    FEE_CLUSTER_INCONSISTENT,    
    /**
     * @brief Fee cluster header is garbled 
    */    
    FEE_CLUSTER_HEADER_INVALID    
} Fee_ClusterStatusType;

/** 
 * @brief Type of job currently executed by Fee_MainFunction
 * @api     
 * @remarks Implements DFEE20302
*/
typedef enum
{
    /* Fee_Read() related jobs */
    /**
     * @brief Read Fee block
    */    
    FEE_JOB_READ = 0,                

    /* Fee_Write() related jobs */
    /**
     * @brief Write Fee block to flash 
    */
    FEE_JOB_WRITE,                   
    /**
     * @brief Write Fee block data to flash 
    */
    FEE_JOB_WRITE_DATA,               
    /**
     * @brief Write unaligned rest of Fee block data to flashn 
    */
    FEE_JOB_WRITE_UNALIGNED_DATA,   
    /**
     * @brief    Validate Fee block by writing validation flag to flash 
    */ 
    FEE_JOB_WRITE_VALIDATE,            
    /**
     * @brief    Finalize validation of Fee block 
    */    
    FEE_JOB_WRITE_DONE,                
    /* Fee_InvalidateBlock() related jobs */
    /**
     * @brief Invalidate Fee block by writing the invalidation flag to flash
    */
    FEE_JOB_INVAL_BLOCK,            
    /**
     * @brief Finalize invalidation of Fee block
    */
    FEE_JOB_INVAL_BLOCK_DONE,       

    /* Fee_EraseImmediateBlock() related jobs */
    /**
     * @brief    Erase (pre-allocate) immediate Fee block 
    */
    FEE_JOB_ERASE_IMMEDIATE,        
    /**
     * @brief Finalize erase (pre-allocation) of Fee block 
    */
    FEE_JOB_ERASE_IMMEDIATE_DONE,    

    /* Fee_Init() realted jobs */
    /**
     * @brief Initialize the cluster scan job 
    */    
    FEE_JOB_INT_SCAN,                
    /**
     * @brief Parse Fee cluster header 
    */
    FEE_JOB_INT_SCAN_CLR_HDR_PARSE,    
    /**
     * @brief Scan active cluster of current cluster group 
    */
    FEE_JOB_INT_SCAN_CLR,            
    /**
     * @brief Format first Fee cluster 
    */
    FEE_JOB_INT_SCAN_CLR_FMT,       
    /**
     * @brief Finalize format of first Fee cluster 
    */
    FEE_JOB_INT_SCAN_CLR_FMT_DONE,    
    /**
     * @brief Parse Fee block header 
    */
    FEE_JOB_INT_SCAN_BLOCK_HDR_PARSE, 
    
    /* Internal swap jobs */
    /**
     * @brief Copy next block from source to target cluster 
    */        
    FEE_JOB_INT_SWAP_BLOCK,           
    /**
     * @brief Format current Fee cluster in current Fee cluster group 
    */
    FEE_JOB_INT_SWAP_CLR_FMT,        
    /**
     * @brief Read data from source cluster to internal Fee buffer 
    */
    FEE_JOB_INT_SWAP_DATA_READ,       
    /**
     * @brief Write data from internal Fee buffer to target cluster 
    */
    FEE_JOB_INT_SWAP_DATA_WRITE,   
    /**
     * @brief Finalize cluster validation 
    */    
    FEE_JOB_INT_SWAP_CLR_VLD_DONE,   
    
    /* Fee system jobs */
    /**
     * @brief    No more subsequent jobs to schedule 
    */
    FEE_JOB_DONE                   
} Fee_JobType;

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/** 
 * @brief Fee cluster group run-time status
 * @api
 * @remarks Implements DFEE20303
*/
typedef struct 
{
/**
 * @brief Address of current Fee data block in flash 
 */    
  Fls_AddressType dataAddrIt;    
/**
 * @brief Address of current Fee block header in flash
 */         
  Fls_AddressType hdrAddrIt; 
/**
 * @brief ID of active cluster 
 */             
  uint32 actClrID;          
/**
 * @brief Index of active cluster
 */     
  uint8 actClr;            
} Fee_ClusterGroupInfoType;

/** 
 * @brief Fee block run-time status
 * @api
 * @remarks Implements DFEE20304
*/
typedef struct
{
/**
 * @brief Address of Fee block data in flash 
 */ 
  Fls_AddressType dataAddr;         
/**
 * @brief    Address of Fee block invalidation field in flash 
 */ 
  Fls_AddressType invalidAddr;        
/**
 * @brief    Current status of Fee block 
 */ 
  Fee_BlockStatusType blockStatus;   

} Fee_BlockInfoType;

#ifdef __cplusplus
}
#endif

#endif /* _FEE_INTERNALTYPES_H_ */

/** @}*/
