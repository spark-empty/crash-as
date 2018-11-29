/**
    @file    Fee_Api.h
    @version 2.0.5.0

    @brief   AUTOSAR Fee - AUTOSAR Module Flash EEPROM Emulation Driver
    @details  All external API declarations of flash EEPROM emulation driver

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

@section Fee_Api_h_REF_1
Violates MISRA-C: 2004 Required Rule 20.2, Re-use of C90 reserved identifier. This violation is due 
to the use of "_" which is required as per Autosar.

@section Fee_Api_h_REF_2
Violates MISRA-C:2004 Required Rule 19.15, Repeatedly included but does not have a standard include guard. 
This violation is due to AUTOSAR requirement MEMMAP003.  

**/

#ifndef _FEE_API_H_
/** @note Violates MISRA-C:2004 Required Rule 20.2, Re-use of C90 reserved identifier.: 
          See @ref Fee_Api_h_REF_1 */
#define _FEE_API_H_

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
          include guard. See @ref Fee_Api_h_REF_2 */
#include "Fee_Cfg.h"
#include "Fee_Version.h"
/** @note Violates MISRA-C:2004 Required Rule 19.15, Repeatedly included but does not have a standard 
          include guard. See @ref Fee_Api_h_REF_2 */
#include "MemIf_Types.h"

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#ifdef CHECK_AUTOSAR_VERSION
    /* AUTOSAR major version check */
    #if (FEE_AR_MAJOR_VERSION != 3U)
    #error Wrong FEE_AR_MAJOR_VERSION (Expected version: 3)
    #endif
    
    /* AUTOSAR minor version check */
    #if (FEE_AR_MINOR_VERSION != 0U)
    #error Wrong FEE_AR_MINOR_VERSION (Expected version: 0)
    #endif
    
    /* AUTOSAR patch version check */
    #if (FEE_AR_PATCH_VERSION != 0U)
    #error Wrong FEE_AR_PATCH_VERSION (Expected version: 0)
    #endif
#endif

/* Software major version check */
#if (FEE_SW_MAJOR_VERSION != 2U)
#error Wrong FEE_SW_MAJOR_VERSION wrong (Expected version: 2)
#endif

/* Software minor version check */
#if (FEE_SW_MINOR_VERSION != 0U)
#error Wrong FEE_SW_MINOR_VERSION (Expected version: 0)
#endif

/* Software patch version check */
#if (FEE_SW_PATCH_VERSION != 0U)
#error Wrong FEE_SW_PATCH_VERSION (Expected version: 0)
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/* AUTOSAR module vendor identification */
#define FEE_VENDOR_ID            43U

/* AUTOSAR module identification */
#define FEE_MODULE_ID            21U

/* AUTOSAR module instance identification */
#define FEE_INSTANCE_ID            0U


/** 
    @brief Development error codes (passed to DET)
    @remarks Implements DFEE21300
*/
/* API service called with wrong parameter */
#define FEE_E_INVALID_BLOCK_NO        0x02U
#define FEE_E_PARAM_OFFSET            0x03U
#define FEE_E_PARAM_LENGTH            0x04U
#define FEE_E_PARAM_DATA            0x05U
/* API service called without module initialization */
#define FEE_E_UNINIT                0x06U
/* API service called while driver still busy */
#define FEE_E_BUSY                    0x07U
#define FEE_E_BUSY_INTERNAL            0x08U
/* NULL_PTR passed */
#define FEE_E_PARAM_POINTER            0x09U
/* API service called without configuring */
#define FEE_E_CANCEL_API               0x0AU
/* API service called without configuring */
#define FEE_E_SET_MODE_API               0x0BU

/** 
    @brief All service IDs (passed to DET)
    @remarks Implements DFEE21301
*/
#define FEE_INIT_ID                 0x00U
#define FEE_SETMODE_ID                0x01U
#define FEE_READ_ID                    0x02U
#define FEE_WRITE_ID                0x03U
#define FEE_CANCEL_ID                0x04U
#define FEE_GETSTATUS_ID            0x05U
#define FEE_GETJOBRESULT_ID            0x06U
#define FEE_INVALIDATEBLOCK_ID        0x07U
#define FEE_GETVERSIONINFO_ID        0x08U
#define FEE_ERASEIMMEDIATEBLOCK_ID    0x09U
#define FEE_JOBENDNOTIFICATION_ID    0x10U
#define FEE_JOBERRORNOTIFICATION_ID    0x11U
#define FEE_MAINFUNCTION_ID            0x12U

/** 
    @brief Development error codes (passed to CER)
*/
#define FEE_E_JOB_UNKNOW               0x13U
/** 
    @brief All service IDs (passed to CER)
*/
#define FEE_JOBSCHEDULE_ID            0x14U
/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#define FEE_START_SEC_CODE
/** @note Violates MISRA-C:2004 Required Rule 19.15, Repeatedly included but does not have a standard 
          include guard. See @ref Fee_Api_h_REF_2 */
#include "MemMap.h"

/**
 * @brief   Service to initialize the FEE module.
 * @details The function Fee_Init shall initialize the Flash EEPROM 
 *          Emulation module.         
 * @pre     The FEE module'  s environment shall not call the function  
 *          Fee_Init shall during a running operation of the FEE module.
 * @note    The function Autosar Service ID[hex]: 0x00.   
 * @note    Synchronous
 * @note    Non Reentrant
 *
 * @api
 *
 * @remarks Implements               DFEE21100,DFEE01000,DFEE01001,DFEE01002, 
 *                                   DFEE01003,DFEE01004,DFEE01005,DFEE01006, 
 *                                   DFEE01007,DFEE01008
*/
extern FUNC( void, FEE_CODE ) Fee_Init( void );

/** 
 * @brief   Set the Fee module'  s operation mode to the given Mode.
 * @details Call the Fls_SetMode function of the underlying flash driver.
 * @pre     The module must be initialized and not busy.
 * @note    The function Autosar Service ID[hex]: 0x01.   
 * @note    Synchronous
 * @note    Non Reentrant
 *
 * @param[in]   Mode Either          MEMIF_MODE_FAST or MEMIF_MODE_SLOW
 *
 * @api 
 *
 * @remarks Implements               DFEE21101,DFEE03000, DFEE03001, DFEE03002, 
 *                                   DFEE03003,DFEE03004, DFEE03005
*/
extern FUNC( void, FEE_CODE ) Fee_SetMode(
    VAR( MemIf_ModeType, AUTOMATIC ) Mode );

/** 
 * @brief   Service to initiate a read job
 * @details The function Fee_Read shall take the block start address and 
 *          offset and calculate the corresponding memory read address.  
 * @pre     The module must be initialized, not busy, BlockNumber must be 
 *          valid, Length != 0, DataBufferPtr != NULL_PTR, BlockOffset and 
 *          (BlockOffset + Length - 1) must be in range.  
 * @post    changes Fee_ModuleStatus module status and Fee_JobBlockOffset, 
 *          Fee_JobBlockLength, Fee_JobBlockIndex, Fee_JobDataDestPtr, 
 *          Fee_Job, Fee_JobResult job control internal variables.
 * @note    The function Autosar Service ID[hex]: 0x02.   
 * @note    Asynchronous
 * @note    Non Reentrant 
 *
 * @param[in]   BlockNumber          Number of logical block, also denoting 
 *                                   start address of that block in flash memory.
 * @param[in]   BlockOffset          Read address offset inside the block.
 * @param[out]  DataBufferPtr        Pointer to data buffer.
 * @param[in]   Length               Number of bytes to read.  
 * @return      Std_ReturnType
 * @retval      E_OK                 The read job was accepted by the 
 *                                   underlying memory driver.
 * @retval      E_NOT_OK             The read job has not been accepted 
 *                                   by the underlying memory driver.
 *
 * @api 
 *      
 * @remarks Implements                DFEE21102, DFEE02000, DFEE02001, DFEE02002, 
 *                                    DFEE02003, DFEE02004, DFEE02005, DFEE02006, 
 *                                    DFEE02007, DFEE02008, DFEE02009, DFEE02010, 
 *                                    DFEE02011, DFEE02012, DFEE02013, DFEE02014, 
 *                                    DFEE02015
*/
extern FUNC( Std_ReturnType, FEE_CODE ) Fee_Read(
    VAR( uint16, AUTOMATIC ) BlockNumber,
    VAR( uint16, AUTOMATIC ) BlockOffset,
    P2VAR( uint8, AUTOMATIC, FEE_APPL_DATA ) DataBufferPtr,
    VAR( uint16, AUTOMATIC ) Length );

/** 
 * @brief   Service to initiate a write job.
 * @details The function Fee_Write shall take the block start address and 
 *          calculate the corresponding memory write address. The block 
 *          address offset shall be fixed to zero.
 *          The function Fee_Write shall copy the given / computed 
 *          parameters to module internal variables, initiate a write job, 
 *          set the FEE module status to MEMIF_BUSY, set the job result to 
 *          MEMIF_JOB_PENDING and return with E_OK.The FEE module shall 
 *          execute the write job of the function Fee_Write
 *          asynchronously within the FEE module'  s main function. 
 * @pre     The module must be initialized, not busy, BlockNumber must be 
 *          valid, and DataBufferPtr != NULL_PTR.  
 *          Before call the function "Fee_Write" for immediate date must be 
 *          called the function "Fee_EraseImmediateBlock"
 * @post    changes Fee_ModuleStatus module status and Fee_JobBlockIndex,
 *          Fee_JobDataDestPtr, Fee_Job, Fee_JobResult job control internal 
 *          variables.
 * @note    The function Autosar Service ID[hex]: 0x03.   
 * @note    Asynchronous
 * @note    Non Reentrant  
 *
 * @param[in]   BlockNumber          Number of logical block, also denoting 
 *                                   start address of that block in emulated 
 *                                   EEPROM
 * @param[out]  DataBufferPtr        Pointer to data buffer
 *  
 * @return      Std_ReturnType
 * @retval      E_OK                 The write job was accepted by the 
 *                                   underlying memory driver.
 * @retval      E_NOT_OK             The write job has not been accepted by 
 *                                   the underlying memory driver. 
 *
 * @api 
 *     
 * @remarks Implements               DFEE21103, DFEE04000, DFEE04001, DFEE04002, 
 *                                   DFEE04003, DFEE04004, DFEE04005, DFEE04006, 
 *                                   DFEE04007, DFEE04008, DFEE04009, DFEE04010,
 *                                   DFEE04011
*/
extern FUNC( Std_ReturnType, FEE_CODE ) Fee_Write(
    VAR( uint16, AUTOMATIC ) BlockNumber,
    P2VAR( uint8, AUTOMATIC, FEE_APPL_DATA ) DataBufferPtr);

/** 
 * @brief   Service to call the cancel function of the underlying flash 
 *          driver.
 * @details The function Fee_Cancel and the cancel function of the 
 *          underlying flash driver are asynchronous w.r.t. an ongoing 
 *          read, erase or write job in the flash memory.      
 * @pre     The module must be initialized.
 * @post    Changes Fee_ModuleStatus module status and job result 
 *          Fee_JobResult internal variables.
 * @note    The function Autosar Service ID[hex]: 0x04.   
 * @note    Asynchronous
 * @note    Non Reentrant  
 *
 * @api  
 *  
 * @remarks Implements               DFEE21104, DFEE05000, DFEE05001, DFEE05002, 
 *                                   DFEE05003, DFEE05004, DFEE05005  
*/
extern FUNC( void, FEE_CODE ) Fee_Cancel( void );

/** 
 * @brief   Return the Fee module state.
 * @details Return the Fee module state synchronously.
 * @note    The function Autosar Service ID[hex]: 0x05.   
 * @note    Synchronous
 * @note    Non Reentrant  
 *  
 * @return      Fee_ModuleStatus
 * @retval      MEMIF_UNINIT         Module has not been initialized (yet)
 * @retval      MEMIF_IDLE           Module is currently idle
 * @retval      MEMIF_BUSY           Module is currently busy
 * @retval      MEMIF_BUSY_INTERNAL  Module is busy with internal management
 *                                   operations
 *
 * @api  
 * 
 * @remarks Implements               DFEE21105, DFEE06000, DFEE06001
*/
extern FUNC( MemIf_StatusType, FEE_CODE ) Fee_GetStatus( void );

/** 
 * @brief   Return the result of the last job.
 * @details Return the result of the last job synchronously.
 * @note    The function Autosar Service ID[hex]: 0x06.   
 * @note    Synchronous
 * @note    Non Reentrant   
 *
 * @return      MemIf_JobResultType
 * @retval      MEMIF_JOB_OK             The job has been finished successfully
 * @retval      MEMIF_JOB_FAILED         The job has not been finished 
 *                                       successfully
 * @retval      MEMIF_JOB_PENDING        The job has not yet been finished
 * @retval      MEMIF_JOB_CANCELLED      The job has been cancelled
 * @retval      MEMIF_BLOCK_INCONSISTENT The requested block is inconsistent, 
 *                                       it may contain corrupted data.
 * @retval      MEMIF_BLOCK_INVALID
 *
 * @api  
 *  
 * @remarks Implements               DFEE21106, DFEE07000, DFEE07001
*/
extern FUNC( MemIf_JobResultType, FEE_CODE ) Fee_GetJobResult( void );

/** 
 * @brief   Service to invalidate a logical block
 * @pre     The module must be initialized, not busy, and BlockNumber must be 
 *          valid
 *
 * @post    changes Fee_ModuleStatus module status and Fee_JobBlockIndex, 
 *          Fee_Job, and Fee_JobResult job control internal variables.            
 * @note    The function Autosar Service ID[hex]: 0x07.   
 * @note    Asynchronous
 * @note    Non Reentrant  
 *  
 * @param[in]   BlockNumber         Number of logical block, also denoting 
 *                                  vstart address of that block in emulated 
 *                                  EEPROM.
 * @return      Std_ReturnType
 * @retval      E_OK                The job was accepted by the underlying 
 *                                  memory driver.
 * @retval      E_NOT_OK            The job has not been accepted by the 
 *                                  underlying memory driver                            
 *
 * @api  
 *
 * @remarks Implements              DFEE21107, DFEE08000, DFEE08001, DFEE08002, 
 *                                  DFEE08003, DFEE08004, DFEE08005, DFEE08006, 
 *                                  DFEE08007, DFEE08008, DFEE08009
*/
extern FUNC( Std_ReturnType, FEE_CODE ) Fee_InvalidateBlock(
    VAR( uint16, AUTOMATIC ) BlockNumber );

/** 
 * @brief   Return the version information of the Fee module
 * @details The version information includes: Module Id, Vendor Id,
 *          Vendor specific version numbers
 * @pre     VersionInfoPtr must not be NULL_PTR 
 * @note    The function Autosar Service ID[hex]: 0x08.   
 * @note    Synchronous
 * @note    Non Reentrant  
 *
 * @param[out]  VersionInfoPtr      Pointer to where to store the version
 *                                  information of this module 
 *
 * @api  
 *  
 * @remarks Implements              DFEE21108, DFEE09000, DFEE09001, DFEE09002, 
 *                                  DFEE09003
*/
/** @remarks Implements    DFEE09001 */
#if( FEE_VERSION_INFO_API == STD_ON )
extern FUNC( void, FEE_CODE ) Fee_GetVersionInfo(
    P2VAR( Std_VersionInfoType, AUTOMATIC, FEE_APPL_DATA ) VersionInfoPtr );
#endif /* FEE_VERSION_INFO_API == STD_ON */

/** 
 * @brief   Service to erase a logical block.
 * @details The function Fee_EraseImmediateBlock shall take the block number
 *          and calculate the corresponding memory block address.
 *          The function Fee_EraseImmediateBlock shall ensure that the FEE
 *          module can write immediate data. Whether this involves physically 
 *          erasing a memory area and therefore calling the erase function of 
 *          the underlying driver depends on the implementation.
 *          If development error detection for the FEE module is enabled, 
 *          the function Fee_EraseImmediateBlock shall check whether the 
 *          addressed logical block is configured as containing immediate 
 *          data (configuration parameter FeeImmediate-
 *          Data == TRUE). If not, the function Fee_EraseImmediateBlock shall 
 *          report the error code FEE_E_INVALID_BLOCK_NO.
 * @pre     The module must be initialized, not busy, BlockNumber must be valid, 
 *          and type of Fee block must be immediate         
 * @post    changes Fee_ModuleStatus module status and Fee_JobBlockIndex, 
 *          Fee_Job, and Fee_JobResult job control internal variables.
 * @note    The function Autosar Service ID[hex]: 0x09.   
 * @note    Asynchronous
 * @note    Non Reentrant  
 *
 * @param[in]   BlockNumber          Number of logical block, also denoting 
 *                                   start address of that block in emulated 
 *                                   EEPROM.
 *  
 * @return      Std_ReturnType
 * @retval      E_OK                 The job was accepted by the underlying 
 *                                   memory driver.
 * @retval      E_NOT_OK             The job has not been accepted by the 
 *                                   underlying memory driver.
 *
 * @api  
 *       
 * @remarks Implements DFEE21109
*/
extern FUNC( Std_ReturnType, FEE_CODE ) Fee_EraseImmediateBlock(
    VAR( uint16, AUTOMATIC ) BlockNumber );

/** 
 * @brief   Service to handle the requested read / write / erase jobs 
 *          respectively the internal management operations
 * @details The function shall asynchronously handle the requested 
 *          read / write / erase jobs 
 *          respectively the internal management operations. The function 
 *          shall check, whether 
 *          the block requested for reading has been invalidated by the 
 *          upper layer module. 
 *          If so, the function shall set the job result to MEMIF_BLOCK_INVALID, 
 *          call the job error notification function if configured.
 *          The function shall check the consistency of the logical
 *          block being read before notifying the caller. If an inconsistency 
 *          of the read data is
 *          Specification of FLASH EEPROM Emulation detected, the function 
 *          shall set the job result to MEMIF_BLOCK_INCONSISTENT and call 
 *          the error notification routine of the upper layer.  
 * @pre     The module must be initialized
 * @note    The function Autosar Service ID[hex]: 0x12.    
 *
 * @api  
 *    
 * @remarks Implements               DFEE21110, DFEE13000, DFEE13001, DFEE13002, 
 *                                   DFEE13003, DFEE13004, DFEE13005, DFEE13006, 
 *                                   DFEE13007
*/
extern FUNC( void, FEE_CODE ) Fee_MainFunction( void );

#define FEE_STOP_SEC_CODE
/** @note Violates MISRA-C:2004 Required Rule 19.15, Repeatedly included but does not have a standard 
          include guard. See @ref Fee_Api_h_REF_2 */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* _FEE_API_H _*/
