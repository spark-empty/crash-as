/**
    @file    Fee.c
    @version 2.0.11.0

    @brief   AUTOSAR Fee - AUTOSAR Module Flash EEPROM Emulation Driver
    @details Flash EEPROM emulation driver source code

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
    @addtogroup FEE
    @{
*/
/*==================================================================================================
==================================================================================================*/
/*================================================================================================*/
/**
@page misra_violations MISRA-C:2004 violations

@section Fee_c_REF_1
Violates MISRA-C: 2004 Advisory Rule 19.7, Function-like macro defined. This violation is due to use 
of macros FEE_SERIALIZE and FEE_DESERIALIZE as functions  

@section Fee_c_REF_2
Violates MISRA-C:2004: Advisory Rule 19.1, only preprocessor statements and comments before '#include'.
This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003. 

@section Fee_c_REF_3                                          
Violates MISRA-C:2004 Required Rule 19.15, Repeatedly included but does not have a standard include guard. 
This violation is due to AUTOSAR requirement MEMMAP003     

@section Fee_c_REF_4
Violates MISRA-C:2004 Required Rule 1.2, No reliance shall be placed on undefined or unspecified behavior.
Not applicable because in ppc, the concept of NEAR and FAR variable is not applicable;

@section Fee_c_REF_5                                             
Violates MISRA-C:2004 Advisory Rule 11.4, Cast from pointer to pointer. This violation is due to casting the 
unsigned char pointer to unsigned long pointer and access these addresses for updating contents of 
that address.

@section Fee_c_REF_6                                      
Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed form of pointer arithmetic.
This violation is due to the use of pointer arithmatic, which is used for the speed optimization, 
the indexing of the pointer is taken care and hence the unintended  memory location will not be 
accessed. 

@section Fee_c_REF_7                     
Violates MISRA-C:2004 Required Rule 11.5, A cast shall not be performed that removes any const or volatile
qualification from the type addressed by a pointer. This has taken care in the driver.

@section Fee_c_REF_8
Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators (&&, || and !) should be effectively 
Boolean. Booleans operands are not used for logical operators '&&', '||' and '!'

@section Fee_c_REF_9
Violates MISRA-C:2004 Required Rule 15.2, An unconditional break statement shall terminate every 
non-empty switch clause. Necessary to simplify the code structure and easier readability.;
**/ 
/*==================================================================================================*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Fee.h"
#include "Fee_InternalTypes.h"
#include "Fee_Cbk.h"

#if( FEE_DEV_ERROR_DETECT == STD_ON )
#include "Det.h"
#endif /* FEE_DEV_ERROR_DETECT == STD_ON */

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/


/** @remarks Covers BSW00374, BSW00318 */
#define FEE_VENDOR_ID_C         43U
#define FEE_AR_MAJOR_VERSION_C  3U
#define FEE_AR_MINOR_VERSION_C  0U
#define FEE_AR_PATCH_VERSION_C  0U
#define FEE_SW_MAJOR_VERSION_C  2U
#define FEE_SW_MINOR_VERSION_C  0U
#define FEE_SW_PATCH_VERSION_C  0U

/**
    @brief Serialize scalar parameter into the buffer
    
    @param[in] paramVal serialized parameter
    @param[in] paramType type of serialized parameter
    @param[in/out] serialPtr pointer to target buffer
    
    @pre serialPtr must be valid pointer
    @post increments the serialPtr by sizeof(paramType)
*/
/** @note Violates MISRA-C:2004 Advisory Rule 19.7, Function-like macro defined. See @ref Fee_c_REF_1 */
#define FEE_SERIALIZE( paramVal, paramType, serialPtr ) \
    *((paramType*)(serialPtr)) = (paramVal); \
    (serialPtr) += sizeof(paramType);
    
/**
    @brief Deserialize scalar parameter from the buffer

    @param[in/out] deserialPtr pointer to source buffer    
    @param[out] paramVal deserialized parameter
    @param[int] paramType type of serialized parameter

    @pre deserialPtr must be valid pointer
    @post increments the deserialPtr by sizeof(paramType)
*/    
/** @note Violates MISRA-C:2004 Advisory Rule 19.7, Function-like macro defined. See @ref Fee_c_REF_1 */
#define FEE_DESERIALIZE( deserialPtr, paramVal, paramType ) \
    (paramVal) = *((paramType*)(deserialPtr)); \
    (deserialPtr) += sizeof(paramType);
    
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and Fee header file are of the same vendor */
#if (FEE_VENDOR_ID_C != FEE_VENDOR_ID)
    #error "Fee.c and Fee.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Fee header file are of the same Autosar version */
    #if ((FEE_AR_MAJOR_VERSION_C != FEE_AR_MAJOR_VERSION) || \
         (FEE_AR_MINOR_VERSION_C != FEE_AR_MINOR_VERSION) || \
         (FEE_AR_PATCH_VERSION_C != FEE_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of Fee.c and Fee.h are different"
    #endif
#endif

/* Check if source file and Fee header file are of the same Software version */
#if ((FEE_SW_MAJOR_VERSION_C != FEE_SW_MAJOR_VERSION) || \
     (FEE_SW_MINOR_VERSION_C != FEE_SW_MINOR_VERSION) || \
         (FEE_SW_PATCH_VERSION_C != FEE_SW_PATCH_VERSION))
    #error "Software Version Numbers of Fee.c and Fee.h are different"
#endif

/* Check if source file and DET header file are of the same version */
#if (FEE_DEV_ERROR_DETECT == STD_ON)
    #ifdef CHECK_AUTOSAR_VERSION
            #if ((FEE_AR_MAJOR_VERSION_C != DET_AR_MAJOR_VERSION) || \
             (FEE_AR_MINOR_VERSION_C != DET_AR_MINOR_VERSION))
            #error "AutoSar Version Numbers of Fee.c and Det.h are different"
        #endif
    #endif
#endif

/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/
#define FEE_START_SEC_VAR_UNSPECIFIED
/** @note Violates MISRA-C:2004 Advisory Rule 19.1,only preprocessor statements and comments before 
          '#include'. See @ref Fee_c_REF_2 */
/** @note Violates MISRA-C:2004 Required Rule 19.15, Repeatedly included but does not have a standard 
          include guard. See @ref Fee_c_REF_3 */
#include "MemMap.h"

/** 
    @brief Internal state of Fee module
    @remarks Implements DFEE20200
*/
STATIC VAR(MemIf_StatusType, AUTOMATIC) Fee_ModuleStatus = MEMIF_UNINIT;

/** 
    @brief Result of last Fee module job
    @remarks Implements DFEE20201
*/
STATIC VAR(MemIf_JobResultType, AUTOMATIC) Fee_JobResult = MEMIF_JOB_OK;

/** 
    @brief Pointer to user data buffer. Used by the read and write Fee jobs
    @remarks Implements DFEE20202
*/
STATIC P2VAR( uint8, AUTOMATIC, FEE_APPL_DATA ) Fee_JobDataDestPtr = NULL_PTR;

/**
    @brief Fee block index. Used by all Fee jobs
    @remarks Implements DFEE20203
*/
STATIC VAR(uint16, AUTOMATIC) Fee_JobBlockIndex = 0U;

/**
    @brief Fee block offset. Used by the read Fee job
    @remarks Implements DFEE20204
*/
STATIC VAR(Fls_LengthType, AUTOMATIC) Fee_JobBlockOffset = 0UL;

/**
    @brief Number of bytes to read. Used by the read Fee job
    @remarks Implements DFEE20205
*/
STATIC VAR(Fls_LengthType, AUTOMATIC) Fee_JobBlockLength = 0UL;

/**
    @brief Currently executed job (including internal one)
    @remarks Implements DFEE20206
*/
STATIC VAR(Fee_JobType, AUTOMATIC) Fee_Job = FEE_JOB_DONE;

/**
    @brief Fee job which started internal management job(s) such as swap...
    @remarks Implements DFEE20207
*/
STATIC VAR(Fee_JobType, AUTOMATIC) Fee_JobIntOriginalJob = FEE_JOB_DONE;

/**
    @brief Internal cluster group iterator. Used by the scan and swap jobs 
           Warning: do not use it outside scan and swap functions 
                    (because it will be Out of Range)   
    @remarks Implements DFEE20208
*/
STATIC VAR(uint8, AUTOMATIC) Fee_JobIntClrGrpIt = (uint8)0;

/**
    @brief Internal cluster iterator. Used by the scan and swap jobs 
    @remarks Implements DFEE20209
*/
STATIC VAR(uint8, AUTOMATIC) Fee_JobIntClrIt = (uint8)0;

/**
    @brief Internal block iterator. Used by the swap job
    @remarks Implements DFEE20210
*/
STATIC VAR(uint16, AUTOMATIC) Fee_JobIntBlockIt = 0U;

/**
    @brief Internal flash helper address iterator. Used by the scan and 
        swap jobs
    @remarks Implements DFEE20211
*/
STATIC VAR(Fls_AddressType, AUTOMATIC) Fee_JobIntAddrIt = 0UL;

/**
    @brief Internal address of current block header. Used by the swap job
    @remarks Implements DFEE20212
*/
STATIC VAR(Fls_AddressType, AUTOMATIC) Fee_JobIntHdrAddr = 0UL;

/**
    @brief Internal address of current data block. Used by the swap job.
    @remarks Implements DFEE20213
*/
STATIC VAR(Fls_AddressType, AUTOMATIC) Fee_JobIntDataAddr = 0UL;

/**
    @brief Run-time information of all configured Fee blocks. Contains
        status, and data information. Used by all jobs
    @remarks Implements DFEE20214
*/
STATIC VAR(Fee_BlockInfoType, AUTOMATIC) Fee_BlockInfo[FEE_NUMBER_OF_BLOCKS];

/**
    @brief Run-time information of all configured cluster groups
    @remarks Implements DFEE20215
*/
STATIC VAR(Fee_ClusterGroupInfoType, AUTOMATIC) Fee_ClrGrpInfo[FEE_NUMBER_OF_CLUSTER_GROUPS];

/**
    @brief Data buffer used by all jobs to store immediate data
    @remarks Implements DFEE20216
*/
STATIC VAR(uint8, AUTOMATIC) Fee_DataBuffer[FEE_DATA_BUFFER_SIZE] = {(uint8)0};

#define FEE_STOP_SEC_VAR_UNSPECIFIED
/** @note Violates MISRA-C:2004 Advisory Rule 19.1,only preprocessor statements and comments before 
          '#include'. See @ref Fee_c_REF_2 */
/** @note Violates MISRA-C:2004 Required Rule 19.15, Repeatedly included but does not have a standard 
          include guard. See @ref Fee_c_REF_3 */
#include "MemMap.h"

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
STATIC FUNC( void, FEE_CODE ) Fee_SerializeBlockHdr( 
    CONST( uint16, FEE_CONST ) BlockNumber, 
    CONST( uint16, FEE_CONST ) Length,
    CONST( Fls_AddressType, FEE_CONST) TargetAddress,    
    CONST( boolean, FEE_CONST ) ImmediateBlock, 
    P2VAR( uint8, AUTOMATIC, FEE_APPL_DATA ) BlockHdrPtr );

STATIC FUNC( Std_ReturnType, FEE_CODE ) Fee_BlankCheck(
    P2CONST( uint8, AUTOMATIC, FEE_APPL_DATA ) targetPtr,
    CONSTP2CONST( uint8, AUTOMATIC, FEE_APPL_DATA ) targetEndPtr );
    
STATIC FUNC( Std_ReturnType, FEE_CODE ) Fee_DeserializeFlag(
    CONSTP2CONST( uint8, AUTOMATIC, FEE_APPL_DATA ) TargetPtr,
    VAR( uint8, AUTOMATIC ) FlagPattern, 
    P2VAR( boolean, AUTOMATIC, FEE_APPL_DATA ) FlagValue );
    
STATIC FUNC( Fee_BlockStatusType, FEE_CODE ) Fee_DeserializeBlockHdr(
    CONSTP2VAR( uint16, AUTOMATIC, FEE_APPL_DATA ) BlockNumber,
    CONSTP2VAR( uint16, AUTOMATIC, FEE_APPL_DATA ) Length,
    CONSTP2VAR( Fls_AddressType, AUTOMATIC, FEE_APPL_DATA ) TargetAddress,
    P2VAR( boolean, AUTOMATIC, FEE_APPL_DATA ) ImmediateBlock,
    P2CONST( uint8, AUTOMATIC, FEE_APPL_DATA ) BlockHdrPtr );
    
STATIC FUNC( Fee_ClusterStatusType, FEE_CODE ) Fee_DeserializeClusterHdr(
    CONSTP2VAR( uint32, AUTOMATIC, FEE_APPL_DATA ) ClrID,
    CONSTP2VAR( Fls_AddressType, AUTOMATIC, FEE_APPL_DATA ) StartAddress,
    CONSTP2VAR( Fls_LengthType, AUTOMATIC, FEE_APPL_DATA ) ClusteSize,
    P2CONST( uint8, AUTOMATIC, FEE_APPL_DATA ) ClrHdrPtr );
    
STATIC FUNC( void, FEE_CODE ) Fee_SerializeClusterHdr(
    CONST( uint32, FEE_CONST ) ClrID,
    CONST( Fls_AddressType, FEE_CONST) StartAddress,
    CONST( Fls_LengthType, FEE_CONST) ClusteSize,
    P2VAR( uint8, AUTOMATIC, FEE_APPL_DATA ) ClrHdrPtr );
    
STATIC FUNC( uint16, FEE_CODE ) Fee_GetBlockIndex(
    CONST( uint16, FEE_CONST ) BlockNumber );
    
STATIC FUNC( uint16, FEE_CODE ) Fee_AlignToVirtualPageSize( 
    VAR( uint16, AUTOMATIC ) BlockSize );
    
STATIC FUNC( void, FEE_CODE ) Fee_CopyDataToPageBuffer(
    P2CONST( uint8, AUTOMATIC, FEE_APPL_DATA ) SourcePtr,
    P2VAR( uint8, AUTOMATIC, FEE_APPL_DATA ) TargetPtr,    
    CONST( uint16, FEE_CONST ) Length );
    
STATIC FUNC( void, FEE_CODE ) Fee_SerializeFlag(
    P2VAR( uint8, AUTOMATIC, FEE_APPL_DATA ) TargetPtr,
    CONST( uint8, FEE_CONST ) FlagPattern );
    
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntSwapClrVld( void );

STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntSwapBlock( void );

STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntSwapClrFmt( void );

STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntSwapClrErase( void );

STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntSwap( void );

STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntScanBlockHdrRead( void );

STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntScanClrErase( void );

STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntScanClr( void );

STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntScanClrFmt( void );

STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntScanClrFmtDone( void );

STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntScanBlockHdrParse(
    CONST( boolean, FEE_CONST ) bufferValid );
    
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntScanClrHdrRead( void );

STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntScan( void );

STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntScanClrHdrParse( 
   CONST( boolean, FEE_CONST) bufferValid );
    
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobRead( void );

STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntSwapBlockVld( void );

STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntSwapDataRead( 
   CONST( boolean, FEE_CONST) bufferValid );
    
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntSwapDataWrite( 
    CONST( boolean, FEE_CONST ) bufferValid );
    
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntSwapClrVldDone( void );

STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobWriteHdr( void );

STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobWriteData( void );

STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobWrite( void );

STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobWriteUnalignedData( void );

STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobWriteValidate( void );

STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobWriteDone( void );

STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobInvalBlock( void );

STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobInvalBlockDone( void );

STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobEraseImmediate( void );

STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobEraseImmediateDone( void );

STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobSchedule( void );

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

#define FEE_START_SEC_CODE
/** @note Violates MISRA-C:2004 Advisory Rule 19.1,only preprocessor statements and comments before 
          '#include'. See @ref Fee_c_REF_2 */
/** @note Violates MISRA-C:2004 Required Rule 19.15, Repeatedly included but does not have a standard 
          include guard. See @ref Fee_c_REF_3 */
#include "MemMap.h"

/** 
    @brief Serialize Fee block parameters into a write buffer

    @param[in] BlockNumber Fee block number
    @param[in] Length Size of Fee block in bytes
    @param[in] TargetAddress Logical address of Fee block in Fls adress space
    @param[in] ImmediateBlock Type of Fee block. Set to TRUE for immediate block
    @param[out] BlockHdrPtr Pointer to serialization buffer
    
    @pre BlockHdrPtr must be valid pointer
    
    @remarks Implements DFEE20100
*/
STATIC FUNC( void, FEE_CODE ) Fee_SerializeBlockHdr( 
    CONST( uint16, FEE_CONST ) BlockNumber, 
    CONST( uint16, FEE_CONST ) Length,
    CONST( Fls_AddressType, FEE_CONST) TargetAddress,    
    CONST( boolean, FEE_CONST ) ImmediateBlock, 
    P2VAR( uint8, AUTOMATIC, FEE_APPL_DATA ) BlockHdrPtr )
{
    VAR( uint32, AUTOMATIC ) checkSum = 0UL;
    P2VAR( uint8, AUTOMATIC, FEE_APPL_DATA ) targetEndPtr = NULL_PTR;
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    targetEndPtr = BlockHdrPtr + FEE_BLOCK_OVERHEAD;
        
    /* Calculate the block header checksum */
    checkSum = (uint32) BlockNumber + (uint32) Length + TargetAddress;

    /* Use MSB of the checksum for the immediate block flag so 
        the checksum is 31-bit */    
    if( ImmediateBlock )
    {
        checkSum += 1U;
        checkSum |= 0x80000000U;
    }
    else
    {
        checkSum &= 0x7fffffffU;
    }
    
    /** @note Violates MISRA-C:2004 Advisory Rule 11.4, Cast from pointer to pointer.: 
              See @ref Fee_c_REF_5 */
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    FEE_SERIALIZE( BlockNumber, uint16, BlockHdrPtr )
    /** @note Violates MISRA-C:2004 Advisory Rule 11.4, Cast from pointer to pointer.: 
              See @ref Fee_c_REF_5 */
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    FEE_SERIALIZE( Length, uint16, BlockHdrPtr )
    /** @note Violates MISRA-C:2004 Advisory Rule 11.4, Cast from pointer to pointer.: 
              See @ref Fee_c_REF_5 */
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    FEE_SERIALIZE( TargetAddress, Fls_AddressType, BlockHdrPtr )
    /** @note Violates MISRA-C:2004 Advisory Rule 11.4, Cast from pointer to pointer.: 
              See @ref Fee_c_REF_5 */
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    FEE_SERIALIZE( checkSum, uint32, BlockHdrPtr )
    
    /* Fill rest of the header with the erase pattern */
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    for( ; BlockHdrPtr != targetEndPtr; BlockHdrPtr++ )
    { 
        *BlockHdrPtr = FEE_ERASED_VALUE;
    }
}

/** 
    @brief Check whether specified data buffer contains only 
        the FEE_ERASED_VALUE value

    @param[in] targetPtr pointer to start of the checked buffer
    @param[in] targetEndPtr pointer to end + 1 of the checked buffer

    @return Std_ReturnType
    @retval E_OK The buffer contains only erased value
    @retval E_NOT_OK The buffer doesn't contain only erased value
    
    @pre targetPtr and targetEndPtr pointers must be valid
    
    @remarks Implements DFEE20101
*/
STATIC FUNC( Std_ReturnType, FEE_CODE ) Fee_BlankCheck(
    P2CONST( uint8, AUTOMATIC, FEE_APPL_DATA ) targetPtr,
    CONSTP2CONST( uint8, AUTOMATIC, FEE_APPL_DATA ) targetEndPtr )
{
    VAR( Std_ReturnType, AUTOMATIC ) RetVal = (Std_ReturnType)E_OK;
    
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    for( ; targetPtr != targetEndPtr; targetPtr++ )
    { 
        if( FEE_ERASED_VALUE == *targetPtr )
        {
            /* Pattern match */
        }
        else
        {
            RetVal = (Std_ReturnType)E_NOT_OK;
            break;
        }
    }
    
    return( RetVal );
}

/** 
    @brief Deserialize the valid or invalid flag from a read buffer

    @param[in] TargetPtr Pointer to the read buffer
    @param[in] FlagPattern FEE_VALIDATED_VALUE or FEE_INVALIDATED_VALUE
    @param[out] FlagValue TRUE if flag of above type is set
    
    @return Std_ReturnType
    @retval E_OK The flag is set or cleared and rest of the read buffer 
        (FEE_VIRTUAL_PAGE_SIZE - 1) contains FEE_ERASED_VALUE
    @retval E_NOT_OK Buffer doesn't contain valid flag data. It's
        garbled...
    
    @pre TargetPtr and FlagValue pointers must be valid
    
    @remarks Implements DFEE20102
*/
STATIC FUNC( Std_ReturnType, FEE_CODE ) Fee_DeserializeFlag(
    CONSTP2CONST( uint8, AUTOMATIC, FEE_APPL_DATA ) TargetPtr,
    VAR( uint8, AUTOMATIC ) FlagPattern, 
    P2VAR( boolean, AUTOMATIC, FEE_APPL_DATA ) FlagValue )
{
    VAR( Std_ReturnType, AUTOMATIC ) RetVal = (Std_ReturnType)E_OK;

    if(( *TargetPtr == FlagPattern ) || ( FEE_ERASED_VALUE == *TargetPtr ))
    {
        /* The bytePattern can be either present or not */
        if( *TargetPtr == FlagPattern )
        {
            *FlagValue = (boolean) TRUE;
        }
        else
        {
            *FlagValue = (boolean) FALSE;
        }
        
        /* Check rest of the FEE_VIRTUAL_PAGE_SIZE */
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
        RetVal = Fee_BlankCheck(TargetPtr + 1, TargetPtr + 
                                    FEE_VIRTUAL_PAGE_SIZE );
    }
    else
    {
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    
    return( RetVal );
}

/** 
    @brief Deserialize Fee block header parameters from read buffer
    
    @param[out] BlockNumber Fee block number
    @param[out] Length Size of Fee block in bytes
    @param[out] Length Size of Fee block in bytes    
    @param[out] TargetAddress Logical address of Fee block in Fls adress space
    @param[out] ImmediateBlock Type of Fee block. Set to TRUE for immediate block
    @param[in] BlockHdrPtr Pointer to read buffer
    
    @return Fee_BlockStatusType
    @retval FEE_BLOCK_VALID Fee block is valid
    @retval FEE_BLOCK_INVALID Fee block is invalid (has been invalidated)
    @retval FEE_BLOCK_INCONSISTENT Fee block is inconsistent, it may contain
        corrupted data...
    @retval FEE_BLOCK_HEADER_INVALID Fee block header is invalid (garbled)
    @retval FEE_BLOCK_HEADER_BLANK Fee block header is filled 
        with FEE_ERASED_VALUE
    
    @pre BlockHdrPtr pointer must be valid
    
    @remarks Implements DFEE20103
*/
STATIC FUNC( Fee_BlockStatusType, FEE_CODE ) Fee_DeserializeBlockHdr(
    CONSTP2VAR( uint16, AUTOMATIC, FEE_APPL_DATA ) BlockNumber,
    CONSTP2VAR( uint16, AUTOMATIC, FEE_APPL_DATA ) Length,
    CONSTP2VAR( Fls_AddressType, AUTOMATIC, FEE_APPL_DATA ) TargetAddress,
    P2VAR( boolean, AUTOMATIC, FEE_APPL_DATA ) ImmediateBlock,
    P2CONST( uint8, AUTOMATIC, FEE_APPL_DATA ) BlockHdrPtr )
{
    VAR( Fee_BlockStatusType, AUTOMATIC ) RetVal = FEE_BLOCK_HEADER_INVALID;

    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    if( Fee_BlankCheck( BlockHdrPtr, 
        BlockHdrPtr + FEE_BLOCK_OVERHEAD ) == (Std_ReturnType)E_OK )
    {
        RetVal = FEE_BLOCK_HEADER_BLANK;    
    }
    else
    {
        VAR( uint32, AUTOMATIC ) readCheckSum;
        VAR( uint32, AUTOMATIC ) calcCheckSum;
        P2CONST( uint8, AUTOMATIC, FEE_APPL_DATA ) targetEndPtr; 
        VAR( boolean, AUTOMATIC ) flagValid;
        VAR( boolean, AUTOMATIC ) flagInvalid;        

        /* Check 1st part of the header */
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
        targetEndPtr = ( BlockHdrPtr + FEE_BLOCK_OVERHEAD ) - 
        ( 2U * FEE_VIRTUAL_PAGE_SIZE );
        
    /** @note Violates MISRA-C:2004 Advisory Rule 11.4, Cast from pointer to pointer.: 
              See @ref Fee_c_REF_5 */
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
        /** @note Violates MISRA-C:2004 Required Rule 11.5, A cast shall not be performed that removes 
                 any const or volatile qualification from the type addressed by a pointer.
                 : See @ref Fee_c_REF_7 */
        FEE_DESERIALIZE( BlockHdrPtr, *BlockNumber, uint16 )
    /** @note Violates MISRA-C:2004 Advisory Rule 11.4, Cast from pointer to pointer.: 
              See @ref Fee_c_REF_5 */
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
        /** @note Violates MISRA-C:2004 Required Rule 11.5, A cast shall not be performed that removes 
                 any const or volatile qualification from the type addressed by a pointer.
                 : See @ref Fee_c_REF_7 */
        FEE_DESERIALIZE( BlockHdrPtr, *Length, uint16 )
    /** @note Violates MISRA-C:2004 Advisory Rule 11.4, Cast from pointer to pointer.: 
              See @ref Fee_c_REF_5 */
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
        /** @note Violates MISRA-C:2004 Required Rule 11.5, A cast shall not be performed that removes 
                 any const or volatile qualification from the type addressed by a pointer.
                 : See @ref Fee_c_REF_7 */
        FEE_DESERIALIZE( BlockHdrPtr, *TargetAddress, Fls_AddressType )
    /** @note Violates MISRA-C:2004 Advisory Rule 11.4, Cast from pointer to pointer.: 
              See @ref Fee_c_REF_5 */
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
        /** @note Violates MISRA-C:2004 Required Rule 11.5, A cast shall not be performed that removes 
                  any const or volatile qualification from the type addressed by a pointer.
                  : See @ref Fee_c_REF_7 */
        FEE_DESERIALIZE( BlockHdrPtr, readCheckSum, uint32 )

        /* Use MSB of checksum for immediate block flag so 
            the checksum is 31-bit long */            
        calcCheckSum = *Length + *TargetAddress + *BlockNumber;

        if( 0U == (readCheckSum & 0x80000000U)  )
        {
            *ImmediateBlock = (boolean) FALSE;
        }
        else
        {
            *ImmediateBlock = (boolean) TRUE;
            calcCheckSum += 1U;
        }

        /* Ignore MSB since it's used for ImmediateBlock flag */
        if( (readCheckSum & 0x7fffffffU) != (calcCheckSum & 0x7fffffffU) )
        {
            /* FEE_BLOCK_HEADER_INVALID */
        }    
        else if( (Std_ReturnType)E_OK != Fee_BlankCheck( BlockHdrPtr, targetEndPtr )  )
        {
            /* FEE_BLOCK_HEADER_INVALID */    
        }
        /** @note Violates MISRA-C:2004 Required Rule 1.2, No reliance shall be placed on undefined 
        or unspecified behavior.: See @ref Fee_c_REF_4 */
        else if( (Std_ReturnType)E_OK != \
        Fee_DeserializeFlag( targetEndPtr, FEE_VALIDATED_VALUE, &flagValid )  )
        {
            /* FEE_BLOCK_HEADER_INVALID */
        }
        /** @note Violates MISRA-C:2004 Required Rule 1.2, No reliance shall be placed on undefined 
        or unspecified behavior.: See @ref Fee_c_REF_4 */
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
        else if( (Std_ReturnType)E_OK != Fee_DeserializeFlag( targetEndPtr + FEE_VIRTUAL_PAGE_SIZE, 
                                         FEE_INVALIDATED_VALUE, &flagInvalid )  )
        {
            /* FEE_BLOCK_HEADER_INVALID */
        }
        else
        {
            /* Block header is valid */
           /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
           (&&, || and !) should be effectively Boolean. Fee_c_REF_8 */
            if(( !flagValid ) && ( !flagInvalid ))
            {
                RetVal = FEE_BLOCK_INCONSISTENT;
            }   
           /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
           (&&, || and !) should be effectively Boolean. Fee_c_REF_8 */          
            else if(( flagValid ) && ( !flagInvalid ))
            {
                RetVal = FEE_BLOCK_VALID;
            }
#if (FEE_BLOCK_ALWAYS_AVAILABLE == STD_ON)
            else if(( flagValid ) && ( flagInvalid ))
            {
                RetVal = FEE_BLOCK_INVALIDATED;
            }
#endif
            else
            {
                RetVal = FEE_BLOCK_INVALID;
            }
        }
    }
    
    return( RetVal );
}

/** 
    @brief Deserialize Fee cluster header parameters from read buffer
    
    @param[out] ClrID 32-bit cluster ID
    @param[out] StartAddress Logical address of Fee cluster in Fls address space
    @param[out] ClusteSize Size of Fee cluster in bytes
    @param[in] ClrHdrPtr Pointer to read buffer
    
    @return Fee_ClusterStatusType
    @retval FEE_CLUSTER_VALID Fee cluster is valid
    @retval FEE_CLUSTER_INVALID Fee cluster has been invalidated
    @retval FEE_CLUSTER_INCONSISTENT Fee cluster is inconsistent, it may contain
        corrupted data
    @retval FEE_CLUSTER_HEADER_INVALID Fee cluster header is invalid (garbled)
    
    @pre ClrHdrPtr pointer must be valid
    
    @remarks Implements DFEE20104
*/
STATIC FUNC( Fee_ClusterStatusType, FEE_CODE ) Fee_DeserializeClusterHdr(
    CONSTP2VAR( uint32, AUTOMATIC, FEE_APPL_DATA ) ClrID,
    CONSTP2VAR( Fls_AddressType, AUTOMATIC, FEE_APPL_DATA ) StartAddress,
    CONSTP2VAR( Fls_LengthType, AUTOMATIC, FEE_APPL_DATA ) ClusteSize,
    P2CONST( uint8, AUTOMATIC, FEE_APPL_DATA ) ClrHdrPtr )
{
    VAR( Fee_ClusterStatusType, AUTOMATIC ) RetVal = FEE_CLUSTER_HEADER_INVALID;
    VAR( uint32, AUTOMATIC ) checkSum = 0UL;
    VAR( boolean, AUTOMATIC ) flagValid = (boolean)0;
    VAR( boolean, AUTOMATIC ) flagInvalid = (boolean)0;
    P2CONST( uint8, AUTOMATIC, FEE_APPL_DATA ) targetEndPtr = NULL_PTR; 
    
    /* Check 1st part of the header */
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    targetEndPtr = ( ClrHdrPtr + FEE_CLUSTER_OVERHEAD ) - 
        ( 2U * FEE_VIRTUAL_PAGE_SIZE );
    
    /** @note Violates MISRA-C:2004 Advisory Rule 11.4, Cast from pointer to pointer.: 
              See @ref Fee_c_REF_5 */
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    /** @note Violates MISRA-C:2004 Required Rule 11.5, A cast shall not be performed that removes 
              any const or volatile qualification from the type addressed by a pointer.
              : See @ref Fee_c_REF_7 */
    FEE_DESERIALIZE( ClrHdrPtr, *ClrID, uint32 )
    /** @note Violates MISRA-C:2004 Advisory Rule 11.4, Cast from pointer to pointer.: 
              See @ref Fee_c_REF_5 */
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    /** @note Violates MISRA-C:2004 Required Rule 11.5, A cast shall not be performed that removes 
              any const or volatile qualification from the type addressed by a pointer.
              : See @ref Fee_c_REF_7 */
    FEE_DESERIALIZE( ClrHdrPtr, *StartAddress, Fls_AddressType )
    /** @note Violates MISRA-C:2004 Advisory Rule 11.4, Cast from pointer to pointer.: 
              See @ref Fee_c_REF_5 */
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
        /** @note Violates MISRA-C:2004 Required Rule 11.5, A cast shall not be performed that removes 
                 any const or volatile qualification from the type addressed by a pointer.
                 : See @ref Fee_c_REF_7 */
    FEE_DESERIALIZE( ClrHdrPtr, *ClusteSize, Fls_LengthType )
    /** @note Violates MISRA-C:2004 Advisory Rule 11.4, Cast from pointer to pointer.: 
              See @ref Fee_c_REF_5 */
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    /** @note Violates MISRA-C:2004 Advisory Rule 19.1, 19.15: See @ref Fee_c_REF_1 */
    FEE_DESERIALIZE( ClrHdrPtr, checkSum, uint32 )

    if(( *ClrID + *StartAddress + *ClusteSize ) != checkSum )
    {
        /* FEE_CLUSTER_HEADER_INVALID */
    }
    else if( (Std_ReturnType)E_OK != Fee_BlankCheck( ClrHdrPtr, targetEndPtr ) )
    {
        /* FEE_CLUSTER_HEADER_INVALID */
    }
    /** @note Violates MISRA-C:2004 Required Rule 1.2, No reliance shall be placed on undefined 
              or unspecified behavior.: See @ref Fee_c_REF_4 */
    else if( (Std_ReturnType)E_OK != Fee_DeserializeFlag( targetEndPtr, FEE_VALIDATED_VALUE,
                                                         &flagValid ) )
    {
        /* FEE_CLUSTER_HEADER_INVALID */
    }
    /** @note Violates MISRA-C:2004 Required Rule 1.2, No reliance shall be placed on undefined 
              or unspecified behavior.: See @ref Fee_c_REF_4 */
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    else if( (Std_ReturnType)E_OK != Fee_DeserializeFlag( targetEndPtr + FEE_VIRTUAL_PAGE_SIZE, 
                                      FEE_INVALIDATED_VALUE, &flagInvalid ) )
    {
        /* FEE_CLUSTER_HEADER_INVALID */
    }    
    else
    {
        /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
                 (&&, || and !) should be effectively Boolean.: See @ref Fee_c_REF_8 */
        if(( !flagValid ) && ( !flagInvalid ))
        {
            RetVal = FEE_CLUSTER_INCONSISTENT;
        }
        /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
                 (&&, || and !) should be effectively Boolean.: See @ref Fee_c_REF_8 */
        if(( flagValid ) && ( !flagInvalid ))
        {
            RetVal = FEE_CLUSTER_VALID;
        }
        else
        {
            RetVal = FEE_CLUSTER_INVALID;
        }
    }

    return( RetVal );
}

/** 
    @brief Serialize Fee cluster header parameters to write buffer
    
    @param[in] ClrID 32-bit cluster ID
    @param[in] StartAddress Logical address of Fee cluster in Fls address space
    @param[in] ClusteSize Size of Fee cluster in bytes
    @param[out] ClrHdrPtr Pointer to write buffer
    
    @pre ClrHdrPtr pointer must be valid
    
    @remarks Implements DFEE20105
*/
STATIC FUNC( void, FEE_CODE ) Fee_SerializeClusterHdr(
    CONST( uint32, FEE_CONST ) ClrID,
    CONST( Fls_AddressType, FEE_CONST) StartAddress,
    CONST( Fls_LengthType, FEE_CONST) ClusteSize,
    P2VAR( uint8, AUTOMATIC, FEE_APPL_DATA ) ClrHdrPtr )
{
    VAR( uint32, AUTOMATIC ) checkSum = 0UL;
    P2VAR( uint8, AUTOMATIC, FEE_APPL_DATA ) targetEndPtr = NULL_PTR; 
    
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    targetEndPtr = ClrHdrPtr + FEE_CLUSTER_OVERHEAD;
    
    /* Calculate the cluster header checksum */
    checkSum = ClrID + StartAddress + ClusteSize;
        
    /** @note Violates MISRA-C:2004 Advisory Rule 11.4, Cast from pointer to pointer.: 
              See @ref Fee_c_REF_5 */  
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    FEE_SERIALIZE( ClrID, uint32, ClrHdrPtr )
    /** @note Violates MISRA-C:2004 Advisory Rule 11.4, Cast from pointer to pointer.: 
              See @ref Fee_c_REF_5 */
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    FEE_SERIALIZE( StartAddress, Fls_AddressType, ClrHdrPtr )
    /** @note Violates MISRA-C:2004 Advisory Rule 11.4, Cast from pointer to pointer.: 
              See @ref Fee_c_REF_5 */
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    FEE_SERIALIZE( ClusteSize, Fls_LengthType, ClrHdrPtr )

    /** @note Violates MISRA-C:2004 Advisory Rule 11.4, Cast from pointer to pointer.: 
              See @ref Fee_c_REF_5 */
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    FEE_SERIALIZE( checkSum, uint32, ClrHdrPtr )
    
    /* Fill rest of the header with the erase pattern */
    for( ; ClrHdrPtr != targetEndPtr; ClrHdrPtr++ )
    { 
        *ClrHdrPtr = FEE_ERASED_VALUE;
    }    
}

/** 
    @brief Searches ordered list of Fee blocks and returns index of block with
        matching BlockNumber
    
    @param[in] BlockNumber Fee block number (FeeBlockNumber)
    
    @return uint16
    @retval Fee block index
    @retval 0xffff if BlockNumber is invalid 
    
    @remarks Implements DFEE20106
*/
STATIC FUNC( uint16, FEE_CODE ) Fee_GetBlockIndex(
    CONST( uint16, FEE_CONST ) BlockNumber )
{
    VAR( sint32, AUTOMATIC ) low = 0L;
    VAR( sint32, AUTOMATIC ) high = (sint32)FEE_NUMBER_OF_BLOCKS - 1;
    VAR( uint16, AUTOMATIC ) RetVal = 0xffffU;

    while( low <= high )
    { 
        VAR( sint32, AUTOMATIC ) middle = low + (( high - low ) / 2);
        if( BlockNumber < Fee_BlockConfig[middle].blockNumber )
        {
            high = middle - 1;
        }
        else if( BlockNumber > Fee_BlockConfig[middle].blockNumber )
        {
            low = middle + 1;
        }
        else
        {
            RetVal = (uint16)middle;
            break;
        }
    }
    
    return( RetVal );
}

/** 
    @brief Adjusts passed size so it's integer multiple
        of pre-configured FEE_VIRTUAL_PAGE_SIZE
    
    @param[in] blockSize Fee block size (FeeBlockSize)
    
    @return uint16
    @retval Adjusted Fee block size to integer multiple    of FEE_VIRTUAL_PAGE_SIZE
    
    @remarks Implements DFEE20107
*/
STATIC FUNC( uint16, FEE_CODE ) Fee_AlignToVirtualPageSize( 
    VAR( uint16, AUTOMATIC ) BlockSize )
{
    /* Check whether the block size is integer multiple 
        of FEE_VIRTUAL_PAGE_SIZE */
    if( 0U == ( BlockSize % FEE_VIRTUAL_PAGE_SIZE ) )
    {
        /* block size is integer multiple of FEE_VIRTUAL_PAGE_SIZE */
    }
    else
    {
        BlockSize = (( BlockSize / FEE_VIRTUAL_PAGE_SIZE ) + 1U ) 
            * FEE_VIRTUAL_PAGE_SIZE;
    }
    
    return( (uint16)BlockSize );
}

/** 
    @brief Copy data from user to internal write buffer and fills
        rest of the write buffer with FEE_ERASED_VALUE
    
    @param[in] sourcePtr Pointer to user data buffer
    @param[out] targetPtr Pointer to internal write buffer
    @param[in] length Number of bytes to copy 
    
    @pre sourcePtr and targetPtr must be valid pointers
    @pre length must be <= FEE_VIRTUAL_PAGE_SIZE
    
    @remarks Implements DFEE20108
*/
STATIC FUNC( void, FEE_CODE ) Fee_CopyDataToPageBuffer(
    P2CONST( uint8, AUTOMATIC, FEE_APPL_DATA ) SourcePtr,
    P2VAR( uint8, AUTOMATIC, FEE_APPL_DATA ) TargetPtr,    
    CONST( uint16, FEE_CONST ) Length )
{
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    P2VAR( uint8, AUTOMATIC, FEE_APPL_DATA ) targetEndPtr = TargetPtr + Length;
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    P2VAR( uint8, AUTOMATIC, FEE_APPL_DATA ) pageEndPtr = TargetPtr + 
        FEE_VIRTUAL_PAGE_SIZE;
    
    /* Copy data to page buffer */
    for( ; TargetPtr != targetEndPtr; TargetPtr++ )
    { 
        *TargetPtr = *SourcePtr;
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
        SourcePtr++;
    }
    
    /* Fill rest of the page buffer with FEE_ERASED_VALUE */
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    for( ; TargetPtr != pageEndPtr; TargetPtr++ )
    { 
        *TargetPtr = FEE_ERASED_VALUE;
    }    
}

/** 
    @brief Serialize validation or invalidation flag to write buffer
    
    @param[out] targetPtr Pointer to write buffer
    @param[in] FlagPattern FEE_VALIDATED_VALUE or FEE_INVALIDATED_VALUE
    
    @pre TargetPtr must be valid pointer
    
    @remarks Implements DFEE20109
*/
STATIC FUNC( void, FEE_CODE ) Fee_SerializeFlag(
    P2VAR( uint8, AUTOMATIC, FEE_APPL_DATA ) TargetPtr,
    CONST( uint8, FEE_CONST ) FlagPattern )
{
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    P2VAR( uint8, AUTOMATIC, FEE_APPL_DATA ) targetEndPtr = 
        TargetPtr + FEE_VIRTUAL_PAGE_SIZE;

    *TargetPtr = FlagPattern;
        
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    for( TargetPtr++ ; TargetPtr != targetEndPtr; TargetPtr++ )
    { 
        *TargetPtr = FEE_ERASED_VALUE;
    }
}

/** 
    @brief Validate current Fee cluster in current Fee cluster group by writing
        FEE_VALIDATED_VALUE into flash
    
    @return MemIf_JobResultType
    @retval MEMIF_JOB_PENDING Underlying Fls accepted the write job
    @retval MEMIF_JOB_FAILED Underlying Fls didn't accept the write job
    
    @pre Fee_JobIntClrGrpIt must contain index of current cluster group
    @pre Fee_JobIntClrIt must contain index of current cluster
    @post Schedule the FEE_JOB_INT_SWAP_CLR_VLD_DONE subsequent job
    
    @remarks Implements DFEE20110
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntSwapClrVld( void )
{
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_OK;
    VAR( Fls_AddressType, AUTOMATIC ) startAddr = 0UL;

    /* Get start address of swap cluster */
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic.: See @ref Fee_c_REF_6 */
    startAddr = Fee_ClrGrps[Fee_JobIntClrGrpIt].clrPtr[Fee_JobIntClrIt].startAddr;
    
    /* Serialize validation pattern to write buffer */
    Fee_SerializeFlag( Fee_DataBuffer, FEE_VALIDATED_VALUE );
    
    /* Write validation pattern to flash */
    if( (Std_ReturnType)E_OK == Fls_Write(( startAddr + FEE_CLUSTER_OVERHEAD ) - \
                   ( 2U * FEE_VIRTUAL_PAGE_SIZE ), Fee_DataBuffer, FEE_VIRTUAL_PAGE_SIZE ) )
    {
        /* Fls write job has been accepted */
        RetVal = MEMIF_JOB_PENDING;    
    }
    else
    {
        /* Fls write job hasn't been accepted */
        RetVal = MEMIF_JOB_FAILED;
    }
    
    /* Schedule subsequent Fee job */
    Fee_Job = FEE_JOB_INT_SWAP_CLR_VLD_DONE;
    
    return( RetVal );
}

/** 
    @brief Copy next block from source to target cluster
    
    @return MemIf_JobResultType
    @retval MEMIF_JOB_PENDING Underlying Fls accepted the write job
    @retval MEMIF_JOB_FAILED Underlying Fls didn't accept the write job
    
    @pre Fee_JobIntBlockIt must contain index of currently swaped Fee block
    @pre Fee_JobBlockIndex must contain index of Fee block which caused the swap
    @pre Fee_JobIntClrGrpIt must contain index of current cluster group
    @pre Fee_JobIntHdrAddr must contain valid address of Fee block header in 
        target cluster
    @post Fee_JobIntHdrAddr is advanced on to next Fee block
    @post Schedule the FEE_JOB_INT_SWAP_DATA_READ, FEE_JOB_INT_SWAP_BLOCK, or
        FEE_JOB_INT_SWAP_CLR_VLD_DONE subsequent job
        
    @remarks Implements DFEE20111
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntSwapBlock( void )
{
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_OK;
    
    /* Find first valid or inconsistent block in same cluster group */
    for( ; Fee_JobIntBlockIt < FEE_NUMBER_OF_BLOCKS; Fee_JobIntBlockIt++ )
    {
        if(
#if (FEE_BLOCK_ALWAYS_AVAILABLE == STD_OFF)        
            ( Fee_JobIntBlockIt != Fee_JobBlockIndex ) &&
#endif
            ( Fee_BlockConfig[Fee_JobIntBlockIt].clrGrp == Fee_JobIntClrGrpIt ) &&
            ( ( FEE_BLOCK_VALID ==  Fee_BlockInfo[Fee_JobIntBlockIt].blockStatus ) ||
            ( FEE_BLOCK_INCONSISTENT == Fee_BlockInfo[Fee_JobIntBlockIt].blockStatus )))
        {
            break;
        }
        else
        {
            /* No match. Try next one... */
        }
    }

    if( FEE_NUMBER_OF_BLOCKS == Fee_JobIntBlockIt )
    {
        /* No more matching blocks. Validate the cluster */
        RetVal = Fee_JobIntSwapClrVld();
    }
    else
    {
        VAR( Fls_AddressType, AUTOMATIC ) dataAddr = 0UL;
        VAR( uint16, AUTOMATIC ) blockSize = 0U;
        VAR( uint16, AUTOMATIC ) alignedBlockSize = 0U;
    
        /* Size of swaped block */
        blockSize = Fee_BlockConfig[Fee_JobIntBlockIt].blockSize;
           /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
           (&&, || and !) should be effectively Boolean.: See @ref Fee_c_REF_8 */
        if(( FEE_BLOCK_VALID == Fee_BlockInfo[Fee_JobIntBlockIt].blockStatus ) ||
            ( Fee_BlockConfig[Fee_JobIntBlockIt].immediateData ))
        {
            /* Align Fee block size to the virtual page boundary */
            alignedBlockSize = Fee_AlignToVirtualPageSize( blockSize );
        
            /* Calculate data address */
            dataAddr = Fee_JobIntDataAddr - alignedBlockSize;

            /* Update the block address info */
            Fee_JobIntDataAddr = dataAddr;

            /* Initialize the data transfer iterator */
            Fee_JobIntAddrIt = dataAddr;
        }
        else
        {
            /* Don't allocate data space for inconsistent and  
                not immediate block */
            dataAddr = 0U;
        }
            
        /* Serialize block header to the write buffer */
        Fee_SerializeBlockHdr( Fee_BlockConfig[Fee_JobIntBlockIt].blockNumber, 
            blockSize, dataAddr, 
            Fee_BlockConfig[Fee_JobIntBlockIt].immediateData, Fee_DataBuffer );
        
        if( FEE_BLOCK_VALID == Fee_BlockInfo[Fee_JobIntBlockIt].blockStatus )
        {
            /* Read block data */
            Fee_Job = FEE_JOB_INT_SWAP_DATA_READ;
        }
        else
        {
            /* Nothing to read. Move on to next block */
            Fee_JobIntBlockIt++;
            Fee_Job = FEE_JOB_INT_SWAP_BLOCK;
        }
        
        /* Write header to flash */
        if( (Std_ReturnType)E_OK != Fls_Write( Fee_JobIntHdrAddr, Fee_DataBuffer, \
                   FEE_BLOCK_OVERHEAD - ( 2U * FEE_VIRTUAL_PAGE_SIZE )) )
        {
            /* Fls write job hasn't been accepted */
            RetVal = MEMIF_JOB_FAILED;
        }
        else
        {
            /* Fls write job has been accepted */
            RetVal = MEMIF_JOB_PENDING;    
        }
        
        /* Move on to next block header */
        Fee_JobIntHdrAddr += FEE_BLOCK_OVERHEAD;
    }
    
    return( RetVal );
}

/** 
    @brief Format current Fee cluster in current Fee cluster group by writing
        cluster header into flash
    
    @return MemIf_JobResultType
    @retval MEMIF_JOB_PENDING Underlying Fls accepted the write job
    @retval MEMIF_JOB_FAILED Underlying Fls didn't accept the write job
    
    @pre Fee_JobIntClrGrpIt must contain index of current cluster group
    @pre Fee_JobIntClrIt must contain index of current cluster
    @post Schedule the FEE_JOB_INT_SWAP_BLOCK subsequent job
    
    @remarks Implements DFEE20112
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntSwapClrFmt( void )
{
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_OK;
    VAR( Fls_AddressType, AUTOMATIC ) startAddr = 0UL;    
    VAR( Fls_LengthType, AUTOMATIC ) length = 0UL;
    VAR( uint32, AUTOMATIC ) actClrID = 0UL;
    

    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    startAddr = Fee_ClrGrps[Fee_JobIntClrGrpIt].clrPtr[Fee_JobIntClrIt].startAddr;
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    length = Fee_ClrGrps[Fee_JobIntClrGrpIt].clrPtr[Fee_JobIntClrIt].length;
    actClrID = Fee_ClrGrpInfo[Fee_JobIntClrGrpIt].actClrID;
    
    /* Build cluster header with new actClrID + 1 */
    Fee_SerializeClusterHdr( actClrID + 1U, startAddr, length, 
        Fee_DataBuffer );
    
    /* Write the cluster header to flash */
    if( (Std_ReturnType)E_OK == Fls_Write( startAddr, Fee_DataBuffer, 
                 FEE_CLUSTER_OVERHEAD - ( 2U * FEE_VIRTUAL_PAGE_SIZE )) )
    {
        /* Fls read job has been accepted */
        RetVal = MEMIF_JOB_PENDING;
    }
    else
    {
        /* Fls write job hasn't been accepted */
        RetVal = MEMIF_JOB_FAILED;
    }    
    
    /* Schedule cluster format done job */
    Fee_Job = FEE_JOB_INT_SWAP_BLOCK;
    
    return( RetVal );
}

/** 
    @brief Erase current Fee cluster in current Fee cluster group by erasing 
        flash
    
    @return MemIf_JobResultType
    @retval MEMIF_JOB_PENDING Underlying Fls accepted the erase job
    @retval MEMIF_JOB_FAILED Underlying Fls didn't accept the erase job
    
    @pre Fee_JobIntClrGrpIt must contain index of current cluster group
    @pre Fee_JobIntClrIt must contain index of current cluster
    @post Schedule the FEE_JOB_INT_SWAP_CLR_FMT subsequent job
    
    @remarks Implements DFEE20113
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntSwapClrErase( void )
{
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_OK;
    VAR( Fls_AddressType, AUTOMATIC ) startAddr = 0UL;    
    VAR( Fls_LengthType, AUTOMATIC ) length = 0UL;
    
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    startAddr = Fee_ClrGrps[Fee_JobIntClrGrpIt].clrPtr[Fee_JobIntClrIt].startAddr;
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    length = Fee_ClrGrps[Fee_JobIntClrGrpIt].clrPtr[Fee_JobIntClrIt].length;
    
    /* Erase cluster */
    if( (Std_ReturnType)E_OK == Fls_Erase( startAddr, length ) )
    {
        /* Fls read job has been accepted */
        RetVal = MEMIF_JOB_PENDING;    
    } 
    else
    {
        /* Fls read job hasn't been accepted */
        RetVal = MEMIF_JOB_FAILED;        
    }

    /* Schedule cluster format job */
    Fee_Job = FEE_JOB_INT_SWAP_CLR_FMT;
    
    return( RetVal );
}

/** 
    @brief Initialize the cluster swap internal operation on 
        current cluster group
    
    @return MemIf_JobResultType
    @retval MEMIF_JOB_PENDING Underlying Fls accepted the erase job
    @retval MEMIF_JOB_FAILED Underlying Fls didn't accept the erase job
    
    @pre Fee_JobIntClrGrpIt must contain index of current cluster group
    @pre Fee_Job must contain type of Fee job which caused the cluster swap
    
    @post Fee module status is set to MEMIF_BUSY_INTERNAL
    @post Fee_Job is stored in Fee_JobIntOriginalJob so it can be rescheduled 
        once the swap operation is finished
    @post Fee internal block iterator Fee_JobIntBlockIt is set to zero
    @post Fee internal cluster iterator Fee_JobIntClrIt is set to 
        the target cluster
    @post Fee_JobIntHdrAddr and Fee_JobIntDataAddr addresses are initialized to 
        point to the target cluster
    @post Schedule erase of the target cluster
    
    @remarks Implements DFEE20114
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntSwap( void )
{
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_OK;
    
    /* Store type of original job so Fee can re-schedule
        this job once the swap is complete */
    Fee_JobIntOriginalJob = Fee_Job;
    
    /* Reset the block iterator */
    Fee_JobIntBlockIt = 0U;
    
    /* Get cluster index the block belongs to */
    Fee_JobIntClrIt = Fee_ClrGrpInfo[Fee_JobIntClrGrpIt].actClr;
    
    /* Calculate index of cluster to swap to */
    Fee_JobIntClrIt++;
    
    if( Fee_JobIntClrIt == Fee_ClrGrps[Fee_JobIntClrGrpIt].clrCount )
    {
        /* Cluster roll over */
        Fee_JobIntClrIt = 0U;
    }
    else
    {
    
    }

    /* Calculate header and data address iterators */    
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    Fee_JobIntHdrAddr = Fee_ClrGrps[Fee_JobIntClrGrpIt].clrPtr[Fee_JobIntClrIt].startAddr;

    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */    
    Fee_JobIntDataAddr = Fee_JobIntHdrAddr + Fee_ClrGrps[Fee_JobIntClrGrpIt].clrPtr[Fee_JobIntClrIt].length;

        

    /* Move on to the first block header */
    Fee_JobIntHdrAddr += FEE_CLUSTER_OVERHEAD;
        
    /* Erase the swap cluster */
    RetVal = Fee_JobIntSwapClrErase();

    return( RetVal );
}

/** 
    @brief Read the Fee block header into internal buffer
    
    @return MemIf_JobResultType
    @retval MEMIF_JOB_PENDING Underlying Fls accepted the read job
    @retval MEMIF_JOB_FAILED Underlying Fls didn't accept the read job
    
    @pre Fee_JobIntAddrIt must contain valid logical address of 
        Fee block header to read
    @post Schedule the FEE_JOB_INT_SCAN_CLR_PARSE subsequent job
    
    @remarks Implements DFEE20115
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntScanBlockHdrRead( void )
{
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_OK;

    /* Read the block header */
    if( (Std_ReturnType)E_OK != Fls_Read( Fee_JobIntAddrIt, Fee_DataBuffer, FEE_BLOCK_OVERHEAD ) )
    {
        /* Fls read job hasn't been accepted */
        RetVal = MEMIF_JOB_FAILED;
    }
    else
    {
        /* Fls read job has been accepted */
        RetVal = MEMIF_JOB_PENDING;
    }
    
    Fee_Job    = FEE_JOB_INT_SCAN_BLOCK_HDR_PARSE;

    return( RetVal );
}

/** 
    @brief Erase first Fee cluster in current cluster group
    
    @return MemIf_JobResultType
    @retval MEMIF_JOB_PENDING Underlying Fls accepted the erase job
    @retval MEMIF_JOB_FAILED Underlying Fls didn't accept the erase job
    
    @pre Fee_JobIntClrGrpIt must contain index of current Fee cluster group
    @post Schedule the FEE_JOB_INT_SCAN_CLR_FMT subsequent job
    
    @remarks Implements DFEE20116
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntScanClrErase( void )
{
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_OK;
    VAR( Fls_AddressType, AUTOMATIC ) startAddr = 0UL;
    VAR( Fls_LengthType, AUTOMATIC ) length = 0UL;    
    
    /* Get address and size of first cluster in the current cluster group */
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    startAddr = Fee_ClrGrps[Fee_JobIntClrGrpIt].clrPtr[0].startAddr;
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    length = Fee_ClrGrps[Fee_JobIntClrGrpIt].clrPtr[0].length;
    
    if( (Std_ReturnType)E_OK == Fls_Erase( startAddr, length ) )
    {
        /* Fls read job has been accepted */
        RetVal = MEMIF_JOB_PENDING;    
    } 
    else
    {
        /* Fls read job hasn't been accepted */
        RetVal = MEMIF_JOB_FAILED;        
    }

    /* Schedule cluster format job */
    Fee_Job = FEE_JOB_INT_SCAN_CLR_FMT;
    
    return( RetVal );
}

/** 
    @brief Scan active cluster of current cluster group or erase and format 
        first cluster if an active cluster can't be found
    
    @return MemIf_JobResultType
    @retval MEMIF_JOB_PENDING Underlying Fls accepted the erase or read job
    @retval MEMIF_JOB_FAILED Underlying Fls didn't accept the erase or read job
    @retval MEMIF_JOB_OK There is no more cluster groups to scan
    
    @pre Fee_JobIntClrGrpIt must contain index of current Fee cluster group
    @post Initialize the Fee_JobIntAddrIt iterator to address of 
        the first Fee block header to scan
    @post Initialize the hdrAddrIt and dataAddrIt iterators to addresses of
        the first Fee block header and data block
    @post Schedule the FEE_JOB_DONE, FEE_JOB_INT_SCAN_CLR_FMT, 
        FEE_JOB_INT_SCAN_CLR_PARSE subsequent job
        
    @remarks Implements DFEE20117
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntScanClr( void )
{
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_OK;

    if( FEE_NUMBER_OF_CLUSTER_GROUPS == Fee_JobIntClrGrpIt )
    {
        /* Nor more cluster groups to scan */
        Fee_Job = FEE_JOB_DONE;
    }
    else
    {
        if( 0U == Fee_ClrGrpInfo[Fee_JobIntClrGrpIt].actClrID )
        {
            /* No active cluster found in current group so erase and format
                the first one... */
            RetVal = Fee_JobIntScanClrErase();
        }
        else
        {
            /* Active cluster found */
            VAR( uint8, AUTOMATIC ) clrIndex = (uint8)0;
            VAR( Fls_AddressType , AUTOMATIC ) clrStartAddr = 0UL;
            VAR( Fls_LengthType , AUTOMATIC ) clrLength = 0UL;
            
            /* Get index of active cluster */
            clrIndex = Fee_ClrGrpInfo[Fee_JobIntClrGrpIt].actClr;
            
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
            clrStartAddr = Fee_ClrGrps[Fee_JobIntClrGrpIt].clrPtr[clrIndex].startAddr;

            /* Calculate logical address of first block header in active cluster */
            Fee_JobIntAddrIt = FEE_CLUSTER_OVERHEAD + clrStartAddr;
        
            /* Initialize the block header pointer */
            Fee_ClrGrpInfo[Fee_JobIntClrGrpIt].hdrAddrIt = Fee_JobIntAddrIt;
            
            /* Initialize the block data pointer */

    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
            clrLength = Fee_ClrGrps[Fee_JobIntClrGrpIt].clrPtr[clrIndex].length;
            Fee_ClrGrpInfo[Fee_JobIntClrGrpIt].dataAddrIt = clrStartAddr + clrLength;
    
            /* Active cluster found so read the first block header */
            RetVal = Fee_JobIntScanBlockHdrRead();
        }
    }    
    
    return( RetVal );
}

/** 
    @brief Format first Fee cluster in current Fee cluster group by writing
        cluster header into flash
    
    @return MemIf_JobResultType
    @retval MEMIF_JOB_PENDING Underlying Fls accepted the erase job
    @retval MEMIF_JOB_FAILED Underlying Fls didn't accept the erase job
    
    @pre Fee_JobIntClrGrpIt must contain index of current Fee cluster group
    @post Schedule the FEE_JOB_INT_SCAN_CLR_FMT_DONE subsequent job
    
    @remarks Implements DFEE20118
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntScanClrFmt( void ) 
{
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_OK;
    VAR( Fls_AddressType, AUTOMATIC ) startAddr = 0UL;
    VAR( Fls_LengthType, AUTOMATIC ) length = 0UL;
    
    /* Get address and size of first cluster in the current cluster group */
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    startAddr = Fee_ClrGrps[Fee_JobIntClrGrpIt].clrPtr[0].startAddr;
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    length = Fee_ClrGrps[Fee_JobIntClrGrpIt].clrPtr[0].length;
    
    /* Build cluster header with clusterID = 1 */
    Fee_SerializeClusterHdr( 1U, startAddr, length, Fee_DataBuffer );
    
    /* Make the cluster valid right away as it's empty anyway... */

    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    Fee_SerializeFlag(( Fee_DataBuffer + FEE_CLUSTER_OVERHEAD ) - 
        (2U * FEE_VIRTUAL_PAGE_SIZE), FEE_VALIDATED_VALUE );
    
    /* Write the cluster header to flash */
    if( (Std_ReturnType)E_OK == Fls_Write( startAddr, Fee_DataBuffer, 
                                FEE_CLUSTER_OVERHEAD - FEE_VIRTUAL_PAGE_SIZE ) )
    {
        /* Fls read job has been accepted */
        RetVal = MEMIF_JOB_PENDING;    
    }
    else
    {
        /* Fls write job hasn't been accepted */
        RetVal = MEMIF_JOB_FAILED;
    }    

    /* Schedule cluster format done job */
    Fee_Job = FEE_JOB_INT_SCAN_CLR_FMT_DONE;
    
    return( RetVal );
}

/** 
    @brief Finalize format of first Fee cluster in current Fee cluster group
    
    @return MemIf_JobResultType
    @retval MEMIF_JOB_PENDING Underlying Fls accepted the erase or read job
    @retval MEMIF_JOB_FAILED Underlying Fls didn't accept the erase or read job
    @retval MEMIF_JOB_OK There is no more cluster groups to scan
    
    @pre Fee_JobIntClrGrpIt must contain index of current Fee cluster group
    @post Assign index (actClr) and ID (actClrID) of active cluster in 
        current cluster group
    @post Initialize the hdrAddrIt and dataAddrIt iterators to addresses of
        the first Fee block header and data block
    @post Advance the Fee_JobIntClrGrpIt iterator to next cluster group
    @post Schedule the FEE_JOB_DONE, FEE_JOB_INT_SCAN_CLR_FMT, 
        FEE_JOB_INT_SCAN_CLR_PARSE subsequent job
        
    @remarks Implements DFEE20119
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntScanClrFmtDone( void ) 
{
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_OK;
    VAR( Fls_AddressType , AUTOMATIC ) clrStartAddr = 0UL;
    VAR( Fls_LengthType , AUTOMATIC ) clrLength = 0UL;
    
    /* Assign Index and ID of active cluster */
    Fee_ClrGrpInfo[Fee_JobIntClrGrpIt].actClr = 0U;
    Fee_ClrGrpInfo[Fee_JobIntClrGrpIt].actClrID = 1U;

    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    clrStartAddr = Fee_ClrGrps[Fee_JobIntClrGrpIt].clrPtr[0].startAddr;
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    clrLength = Fee_ClrGrps[Fee_JobIntClrGrpIt].clrPtr[0].length;
    
    /* Initialize the block header pointer */
    Fee_ClrGrpInfo[Fee_JobIntClrGrpIt].hdrAddrIt = 
        clrStartAddr + FEE_CLUSTER_OVERHEAD;
    
    /* Initialize the block data pointer */
    Fee_ClrGrpInfo[Fee_JobIntClrGrpIt].dataAddrIt = clrStartAddr + clrLength;
    
    /* Move on to next cluster group */
    Fee_JobIntClrGrpIt++;
    
    /* Scan next cluster group if any */
    RetVal = Fee_JobIntScanClr();
    
    return( RetVal );
}

/** 
    @brief Parse Fee block header
    
    @param[in] bufferValid FALSE if previous Fls read job has failed
    
    @return MemIf_JobResultType
    @retval MEMIF_JOB_PENDING Underlying Fls accepted the erase or read job
    @retval MEMIF_JOB_FAILED Underlying Fls didn't accept the erase or read job
    @retval MEMIF_JOB_OK There is no more cluster groups to scan
    
    @pre Fee_JobIntClrGrpIt must contain index of current Fee cluster group
    
    @post Initialize internal recovery swap operation in case of bogus 
        Fee block header or failure of previous read job (perhaps ECC failure..)
    @post Advance the Fee_JobIntClrGrpIt iterator to next cluster group in case
        of blank Fee block header (end of header list)
    @post Update the blockStatus, dataAddr, and invalidAddr block information 
        and the hdrAddrIt and dataAddrIt iterators in case of valid 
        Fee block header
    @post Schedule the FEE_JOB_INT_SCAN_CLR_PARSE subsequent job in case of
        valid Fee block header
        
    @remarks Implements DFEE20120
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntScanBlockHdrParse(
    CONST( boolean, FEE_CONST ) bufferValid )
{
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_FAILED;
    VAR( Fee_BlockStatusType, AUTOMATIC ) blockStatus;
    VAR( uint16, AUTOMATIC ) blockNumber = 0U;
    VAR( uint16, AUTOMATIC ) blockSize = 0U;
    VAR( Fls_AddressType, AUTOMATIC ) dataAddr = 0UL;
    VAR( boolean, AUTOMATIC ) immediateData = (boolean)0;

    /* Deserialize block header from read buffer */
    /** @note Violates MISRA-C:2004 Required Rule 1.2, No reliance shall be placed on undefined 
              or unspecified behavior.: See @ref Fee_c_REF_4 */
    blockStatus = Fee_DeserializeBlockHdr( &blockNumber, &blockSize, 
        &dataAddr, &immediateData, Fee_DataBuffer);


    /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
              (&&, || and !) should be effectively Boolean. Fee_c_REF_8 */
    if(( FEE_BLOCK_HEADER_INVALID  == blockStatus ) || ( !bufferValid ))
    {
        /* Invalidate the block index so Fee won't skip
            the Fee_JobBlockIndex block */
        Fee_JobBlockIndex = 0xffffU;
        
        /* Move on to next block header */
        Fee_JobIntAddrIt += FEE_BLOCK_OVERHEAD;
        
        /* Update the block header pointer */
        Fee_ClrGrpInfo[Fee_JobIntClrGrpIt].hdrAddrIt = Fee_JobIntAddrIt;
    
        /* Update the block data pointer, starting from hdr pointer plus to 2U * FEE_BLOCK_OVERHEAD */
        Fee_ClrGrpInfo[Fee_JobIntClrGrpIt].dataAddrIt = Fee_JobIntAddrIt + (2U * FEE_BLOCK_OVERHEAD );
        
        /* Read next header */
        RetVal = Fee_JobIntScanBlockHdrRead();

    } 
    else if( FEE_BLOCK_HEADER_BLANK  == blockStatus )
    {
        /* End of header list so move on to next cluster group */
        Fee_JobIntClrGrpIt++;
        
        RetVal = Fee_JobIntScanClr();
    }
    else
    {
        /* Look for found block in the block configuration */
        VAR( uint32, AUTOMATIC ) blockIndex = Fee_GetBlockIndex( blockNumber );
        
        if( 0xffffU != blockIndex )
        {
            /* Check whether found block belongs to current cluster group,
                and its size and type match the configuration */
            if(( Fee_BlockConfig[blockIndex].clrGrp == Fee_JobIntClrGrpIt ) &&
                ( Fee_BlockConfig[blockIndex].blockSize == blockSize ) &&
                ( Fee_BlockConfig[blockIndex].immediateData == immediateData ))
            {
                /* Update block run-time information */
#if (FEE_BLOCK_ALWAYS_AVAILABLE == STD_ON)
                  /* Update block information when:
                  - new valid block is found
                  - block was invalidated 
                     - block contains immediate data
                     (basically just ignore INCONSISTENT non-immediate blocks)
                 */
                if ((FEE_BLOCK_INCONSISTENT != blockStatus) ||
                    (immediateData == TRUE))
                {
                     /* Mark invalidated blocks as invalid */
                    if (FEE_BLOCK_INVALIDATED == blockStatus)
                    {
                         blockStatus = FEE_BLOCK_INVALID;
                    }
#endif
                    if((dataAddr < Fee_ClrGrpInfo[Fee_JobIntClrGrpIt].dataAddrIt) && (dataAddr >= Fee_ClrGrpInfo[Fee_JobIntClrGrpIt].hdrAddrIt + (2U * FEE_BLOCK_OVERHEAD)))
                    {
                        Fee_BlockInfo[blockIndex].blockStatus = blockStatus;
                         /* Update the block data pointer */
                        Fee_BlockInfo[blockIndex].dataAddr = dataAddr;
                        Fee_BlockInfo[blockIndex].invalidAddr = ( Fee_JobIntAddrIt + FEE_BLOCK_OVERHEAD ) \
                                                                  - FEE_VIRTUAL_PAGE_SIZE;
                       
                        Fee_ClrGrpInfo[Fee_JobIntClrGrpIt].dataAddrIt = dataAddr;
                    }
                    else
                    {
                        /* data address pointer isn't corrupted or invalid... next write cluster occurs*/
                        Fee_ClrGrpInfo[Fee_JobIntClrGrpIt].dataAddrIt = Fee_JobIntAddrIt + (2U * FEE_BLOCK_OVERHEAD );
                    }
#if (FEE_BLOCK_ALWAYS_AVAILABLE == STD_ON)
                }
                else
                {
                    Fee_ClrGrpInfo[Fee_JobIntClrGrpIt].dataAddrIt = dataAddr;
                }
#endif
            }
            else
            {
                /* Block header doesn't match Fee config... next write cluster occurs */
                Fee_ClrGrpInfo[Fee_JobIntClrGrpIt].dataAddrIt = Fee_JobIntAddrIt + (2U * FEE_BLOCK_OVERHEAD );
            }
        }
        else
        {
            /* Invalid block number (removed from Fee config...) next write cluster occurs */
            Fee_ClrGrpInfo[Fee_JobIntClrGrpIt].dataAddrIt = Fee_JobIntAddrIt + (2U * FEE_BLOCK_OVERHEAD );
        }

        /* Move on to next block header */
        Fee_JobIntAddrIt += FEE_BLOCK_OVERHEAD;
        
        /* Update the block header pointer */
        Fee_ClrGrpInfo[Fee_JobIntClrGrpIt].hdrAddrIt = Fee_JobIntAddrIt;
            
        /* Read next header */
        RetVal = Fee_JobIntScanBlockHdrRead();
    }
    
    return( RetVal );
}

/** 
    @brief Read Fee cluster header
    
    @return MemIf_JobResultType
    @retval MEMIF_JOB_PENDING Underlying Fls accepted the read job
    @retval MEMIF_JOB_FAILED Underlying Fls didn't accept read job
    
    @pre Fee_JobIntClrGrpIt must contain index of current Fee cluster group
    @pre Fee_JobIntClrIt must contain index of current Fee cluster
    @post Schedule the FEE_JOB_INT_SCAN_CLR_HDR_PARSE subsequent job
    
    @remarks Implements DFEE20121
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntScanClrHdrRead( void )
{
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_OK;
    VAR( Fls_AddressType, AUTOMATIC ) readAddress = 0UL;
    
    /* Get address of current cluster */
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */ 
    readAddress = Fee_ClrGrps[Fee_JobIntClrGrpIt].clrPtr[Fee_JobIntClrIt].startAddr;
    
    if( (Std_ReturnType)E_OK != Fls_Read( readAddress, Fee_DataBuffer, FEE_CLUSTER_OVERHEAD ) )
    {
        /* Fls read job hasn't been accepted */
        RetVal = MEMIF_JOB_FAILED;
    }
    else
    {
        /* Fls read job has been accepted */
        RetVal = MEMIF_JOB_PENDING;
    }
        
    /* Schedule cluster scan job */
    Fee_Job = FEE_JOB_INT_SCAN_CLR_HDR_PARSE;
    
    return( RetVal );        
}

/** 
    @brief Initialize the cluster scan job
    
    @return MemIf_JobResultType
    @retval MEMIF_JOB_PENDING Underlying Fls accepted the read job
    @retval MEMIF_JOB_FAILED Underlying Fls didn't accept read job
    
    @post Reset the Fee_JobIntClrGrpIt and Fee_JobIntClrIt iterators
    @post Schedule the FEE_JOB_INT_SCAN_CLR_HDR_PARSE subsequent job
    
    @remarks Implements DFEE20122
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntScan( void )
{
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_OK;

    /* Reset iterators to first cluster of first cluster group */
    Fee_JobIntClrGrpIt = 0U;
    Fee_JobIntClrIt = 0U;
    
    /* Schedule reading of first cluster header */
    RetVal = Fee_JobIntScanClrHdrRead();
    
    return( RetVal );
}

/** 
    @brief Parse Fee cluster header
    
    @param[in] bufferValid FALSE if previous Fls read job has failed
    
    @return MemIf_JobResultType
    @retval MEMIF_JOB_PENDING Underlying Fls accepted the erase or read job
    @retval MEMIF_JOB_FAILED Underlying Fls didn't accept the erase or read job
    
    @pre Fee_JobIntClrGrpIt must contain index of current Fee cluster group
    @pre Fee_JobIntClrIt must contain index of current cluster
    @post Update the Fee_JobIntClrIt and/or Fee_JobIntClrGrpIt iterators to move
        onto next cluster and/or cluster group and read next cluster header if
        there is any
    @post Scan first active cluster if Fee is done with reading 
        the cluster headers
    @post Schedule the FEE_JOB_DONE, FEE_JOB_INT_SCAN_CLR_FMT, 
        FEE_JOB_INT_SCAN_CLR_PARSE, FEE_JOB_INT_SCAN_CLR_HDR_PARSE
        subsequent jobs
        
    @remarks Implements DFEE20123
 */
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntScanClrHdrParse( 
   CONST( boolean, FEE_CONST) bufferValid ) 
{
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_OK;
    VAR( Fee_ClusterStatusType, AUTOMATIC ) clrStatus = FEE_CLUSTER_VALID;
    VAR( uint32, AUTOMATIC ) clrID = 0UL;
    VAR( Fls_AddressType, AUTOMATIC ) clrStartAddr = 0UL;
    VAR( Fls_LengthType, AUTOMATIC ) clrSize = 0UL;
    VAR( Fls_AddressType, AUTOMATIC ) cfgStartAddr = 0UL;
    VAR( Fls_LengthType, AUTOMATIC ) cfgClrSize = 0UL;    
    
    /* Get configured cluster start address and size */
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    cfgStartAddr = Fee_ClrGrps[Fee_JobIntClrGrpIt].clrPtr[Fee_JobIntClrIt].startAddr;
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    cfgClrSize = Fee_ClrGrps[Fee_JobIntClrGrpIt].clrPtr[Fee_JobIntClrIt].length;

    /* Deserialize cluster parameters from the read buffer */
    /** @note Violates MISRA-C:2004 Required Rule 1.2, No reliance shall be placed on undefined 
              or unspecified behavior.: See @ref Fee_c_REF_4 */
    clrStatus = Fee_DeserializeClusterHdr( &clrID, &clrStartAddr, &clrSize,
        Fee_DataBuffer );

    /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
              (&&, || and !) should be effectively Boolean. Fee_c_REF_8 */
    if(( bufferValid ) && ( FEE_CLUSTER_VALID == clrStatus ) && 
        ( clrStartAddr == cfgStartAddr ) && ( clrSize == cfgClrSize ) && 
        ( clrID > Fee_ClrGrpInfo[Fee_JobIntClrGrpIt].actClrID ))
    {
        /* Found valid and active cluster */
        Fee_ClrGrpInfo[Fee_JobIntClrGrpIt].actClr = Fee_JobIntClrIt;
        Fee_ClrGrpInfo[Fee_JobIntClrGrpIt].actClrID = clrID;
    }
    else
    {
        /* Invalid, inconsistent, or cluster with low ID */
    }
    
    /* Move on to next cluster */
    Fee_JobIntClrIt++;
    
    if( Fee_JobIntClrIt == Fee_ClrGrps[Fee_JobIntClrGrpIt].clrCount )
    {
        /* Move on to next cluster group */
        Fee_JobIntClrGrpIt++;
        Fee_JobIntClrIt = 0U;
    }
    else
    {
        /* next cluster in current cluster group */
    }

    if( FEE_NUMBER_OF_CLUSTER_GROUPS == Fee_JobIntClrGrpIt )
    {
        Fee_JobIntClrGrpIt = 0U;
        
        /* Done reading all cluster headers. Now scan active clusters */
        RetVal = Fee_JobIntScanClr();
    }
    else
    {
        /* Read next cluster header */
        RetVal = Fee_JobIntScanClrHdrRead();
    }
    
    return( RetVal );        
}

/** 
    @brief Read Fee block
    
    @return MemIf_JobResultType
    @retval MEMIF_JOB_PENDING Underlying Fls accepted the read job
    @retval MEMIF_JOB_FAILED Underlying Fls didn't accept read job
    @retval MEMIF_BLOCK_INVALID Requested Fee block is invalid
    @retval MEMIF_BLOCK_INCONSISTENT Requested Fee block is inconsistent
    
    @pre Fee_JobBlockIndex must contain index of requested Fee block
    @pre Fee_JobBlockOffset must contain offset in requested Fee block
    @pre Fee_JobBlockLength must contain number of bytes to read from 
        requested Fee block
    @post Schedule the FEE_JOB_DONE    subsequent job
    
    @remarks Implements DFEE20124
 */
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobRead( void )
{
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_FAILED;
    VAR( Fee_BlockStatusType, AUTOMATIC ) blockStatus = FEE_BLOCK_VALID;
    VAR( Fls_AddressType, AUTOMATIC ) blockAddress = 0UL;
        
    blockStatus = Fee_BlockInfo[Fee_JobBlockIndex].blockStatus;
    blockAddress = Fee_BlockInfo[Fee_JobBlockIndex].dataAddr;
    
    if( FEE_BLOCK_VALID == blockStatus )
    {
        if( (Std_ReturnType)E_OK != Fls_Read( blockAddress + Fee_JobBlockOffset, Fee_JobDataDestPtr,
                                              Fee_JobBlockLength ) )
        {
            /* Fls read job hasn't been accepted */
            RetVal = MEMIF_JOB_FAILED;
        }
        else
        {
            /* Fls read job has been accepted */
            RetVal = MEMIF_JOB_PENDING;
        }
    }
    else if( FEE_BLOCK_INVALID == blockStatus )
    {
        RetVal = MEMIF_BLOCK_INVALID;
    }
    else if( FEE_BLOCK_INCONSISTENT == blockStatus )
    {
        if ( Fee_BlockConfig[Fee_JobBlockIndex].immediateData )
        {
            RetVal = MEMIF_BLOCK_INVALID;
        }
        else
        {
            RetVal = MEMIF_BLOCK_INCONSISTENT;
        }
    }
    else
    {
        /* Something is wrong... MEMIF_JOB_FAILED */
    }

    /* There is no consecutive job to schedule */
    Fee_Job = FEE_JOB_DONE;
    
    return( RetVal );
}

/** 
    @brief Validate Fee block
    
    @return MemIf_JobResultType
    @retval MEMIF_JOB_PENDING Underlying Fls accepted the write job
    @retval MEMIF_JOB_FAILED Underlying Fls didn't accept write job
    
    @pre Fee_JobIntHdrAddr must contain address of Fee block header
        to validate
    @post Schedule the FEE_JOB_INT_SWAP_BLOCK subsequent job
    
    @remarks Implements DFEE20125    
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntSwapBlockVld( void ) 
{ 
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_OK;
     
    /* Serialize validation pattern to buffer */
    Fee_SerializeFlag( Fee_DataBuffer, FEE_VALIDATED_VALUE );
    
    /* Write header to flash */
    if( (Std_ReturnType)E_OK != Fls_Write( Fee_JobIntHdrAddr - ( 2U * FEE_VIRTUAL_PAGE_SIZE ), 
                                           Fee_DataBuffer, FEE_VIRTUAL_PAGE_SIZE ) )
    {
        /* Fls read job hasn't been accepted */
        RetVal = MEMIF_JOB_FAILED;
    }
    else
    {
        /* Fls read job has been accepted */
        RetVal = MEMIF_JOB_PENDING;
    }
    
    /* Finalize the write operation */
    Fee_Job = FEE_JOB_INT_SWAP_BLOCK;
    
    return( RetVal );
}

/** 
    @brief Read data from source cluster to internal Fee buffer
    
    @param[in] bufferValid FALSE if previous Fls read job has failed
    
    @return MemIf_JobResultType
    @retval MEMIF_JOB_PENDING Underlying Fls accepted the read job
    @retval MEMIF_JOB_FAILED Underlying Fls didn't accept read job
    
    @pre Fee_JobIntBlockIt must contain index of currently swaped
        Fee block
    @pre Fee_JobIntDataAddr must contain start address of Fee data block
        in the target cluster
    @pre Fee_JobIntAddrIt must contain current address of Fee data block
        in the target cluster
    @post Move on to next block Fee block if bufferValid == FALSE
    @post Validates the Fee block if there is no more data to read
    @post Schedule the FEE_JOB_INT_SWAP_DATA_WRITE subsequent job
    
    @remarks Implements DFEE20126
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntSwapDataRead( 
   CONST( boolean, FEE_CONST) bufferValid )
{
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_FAILED;
    VAR( Fls_AddressType, AUTOMATIC ) readAddr = 0UL;
    VAR( uint16, AUTOMATIC ) alignedBlockSize = 0U;    
    VAR( uint16, AUTOMATIC ) blockSize = 0U;

    /* Get size of swaped block */
    blockSize = Fee_BlockConfig[Fee_JobIntBlockIt].blockSize;
    
    /* Get size of swaped block aligned to virtual page boundary */
    alignedBlockSize = Fee_AlignToVirtualPageSize( blockSize );
    
    /* Calculate remaining number of bytes to read */
    Fee_JobBlockLength = ( Fee_JobIntDataAddr + alignedBlockSize ) - Fee_JobIntAddrIt;
    
     /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
               (&&, || and !) should be effectively Boolean. Fee_c_REF_8 */
    if( !bufferValid )
    {
        /* There was error while reading the source cluster.
            Change the block status to FEE_BLOCK_INCONSISTENT, 
            leave the block (in flash) INCONSITENT and move on to next block */
        Fee_BlockInfo[Fee_JobIntBlockIt].blockStatus = FEE_BLOCK_INCONSISTENT;
        
        Fee_JobIntBlockIt++;

        RetVal = Fee_JobIntSwapBlock();
    }
    else if( 0U == Fee_JobBlockLength )
    {
        /* No more bytes to copy. Validate the block and 
            move on to next block... */
        Fee_JobIntBlockIt++;
        
        RetVal = Fee_JobIntSwapBlockVld();
    }
    else
    {
        if( Fee_JobBlockLength > FEE_DATA_BUFFER_SIZE )
        {
            Fee_JobBlockLength = FEE_DATA_BUFFER_SIZE;
        }
        else
        {
            /* Block data fits into the buffer */
        }
    
        /* Calculate source address */
        readAddr = ( Fee_BlockInfo[Fee_JobIntBlockIt].dataAddr + 
            Fee_JobIntAddrIt ) - Fee_JobIntDataAddr;
        
        /* Read the block data */
        if( (Std_ReturnType)E_OK != Fls_Read( readAddr, Fee_DataBuffer, Fee_JobBlockLength ) )
        {
            /* Fls read job hasn't been accepted */
            RetVal = MEMIF_JOB_FAILED;
        }
        else
        {
            /* Fls read job has been accepted */
            RetVal = MEMIF_JOB_PENDING;
        }    

        Fee_Job = FEE_JOB_INT_SWAP_DATA_WRITE;
    }

    return( RetVal );
}

/** 
    @brief Write data from internal Fee buffer to target cluster
    
    @param[in] bufferValid FALSE if previous Fls read job has failed
    
    @return MemIf_JobResultType
    @retval MEMIF_JOB_PENDING Underlying Fls accepted the write job
    @retval MEMIF_JOB_FAILED Underlying Fls didn't accept write job
    
    @pre Fee_JobBlockLength    must contain size of data block being transfered
        (up to FEE_DATA_BUFFER_SIZE)
    @pre Fee_JobIntAddrIt must contain current address of Fee data block
        in the target cluster        
    @post Update the Fee_JobIntAddrIt data iterator for next data
        transfer if any
    @post Schedule the FEE_JOB_INT_SWAP_DATA_READ subsequent job
    
    @remarks Implements DFEE20127
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntSwapDataWrite( 
    CONST( boolean, FEE_CONST ) bufferValid )
{
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_OK;

    if( bufferValid ) 
    {    
        if( (Std_ReturnType)E_OK == Fls_Write( Fee_JobIntAddrIt, Fee_DataBuffer, \
                                                           Fee_JobBlockLength ))
        {
            /* Fls read job has been accepted */
            RetVal = MEMIF_JOB_PENDING;    
        }
        else
        {
            /* Fls write job hasn't been accepted */
            RetVal = MEMIF_JOB_FAILED;
        }
            
        Fee_JobIntAddrIt += Fee_JobBlockLength;
        
        Fee_Job = FEE_JOB_INT_SWAP_DATA_READ;
    }
    else
    {
        RetVal = Fee_JobIntSwapDataRead( (boolean) FALSE );
    }
    
    return( RetVal );
}

/** 
    @brief Finalize cluster validation

    @return MemIf_JobResultType
    @retval MEMIF_JOB_PENDING Underlying Fls accepted the write job
    @retval MEMIF_JOB_FAILED Underlying Fls didn't accept write job

    @pre Fee_JobIntClrGrpIt must contain index of current Fee cluster group
    @pre Fee_JobIntClrIt must contain index of current cluster
    @post Update the dataAddr and invalidAddr Fee_BlockConfig variables of
        all affected (swaped) Fee blocks
    @post Update actClr, actClrID, hdrAddrIt, dataAddrIt Fee_ClrGrpInfo 
        variables of current cluster group
    @post Change Fee module status from MEMIF_BUSYINTERNAL to MEMIF_BUSY
    @post Re-schedule the Fee_JobIntOriginalJob subsequent job
    
    @remarks Implements DFEE20128
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobIntSwapClrVldDone( void )
{
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_OK;
    VAR( uint16, AUTOMATIC ) blockIt = 0U;
    VAR( Fls_AddressType, AUTOMATIC ) hdrAddrIt = 0UL;
    VAR( Fls_AddressType, AUTOMATIC ) dataAddrIt = 0UL;    
    
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    hdrAddrIt = Fee_ClrGrps[Fee_JobIntClrGrpIt].clrPtr[Fee_JobIntClrIt].startAddr;
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */  
    dataAddrIt = hdrAddrIt + 
        Fee_ClrGrps[Fee_JobIntClrGrpIt].clrPtr[Fee_JobIntClrIt].length;
    
    /* Move on to the first block header */
    hdrAddrIt += FEE_CLUSTER_OVERHEAD;
    
#if (FEE_BLOCK_ALWAYS_AVAILABLE == STD_OFF)
    /* invalidate the block causing the swap unless FEE_BLOCK_ALWAYS_AVAILABLE enabled */
    if( FEE_NUMBER_OF_BLOCKS > Fee_JobBlockIndex )
    {
        Fee_BlockInfo[Fee_JobBlockIndex].blockStatus = FEE_BLOCK_INVALID;
    }
#endif
    /* Sync block info */
    for( blockIt = 0U; blockIt < FEE_NUMBER_OF_BLOCKS; blockIt++ )
    {
        if(
#if (FEE_BLOCK_ALWAYS_AVAILABLE == STD_OFF)
            ( blockIt != Fee_JobBlockIndex ) &&
#endif   
            ( Fee_BlockConfig[blockIt].clrGrp == Fee_JobIntClrGrpIt ) &&
            (( FEE_BLOCK_VALID == Fee_BlockInfo[blockIt].blockStatus ) ||
            ( FEE_BLOCK_INCONSISTENT == Fee_BlockInfo[blockIt].blockStatus )))
        {    
            /* Sync invalidAddr */
            Fee_BlockInfo[blockIt].invalidAddr = ( hdrAddrIt + 
                FEE_BLOCK_OVERHEAD ) - FEE_VIRTUAL_PAGE_SIZE;
            
            hdrAddrIt += FEE_BLOCK_OVERHEAD;

           if(( FEE_BLOCK_VALID == Fee_BlockInfo[blockIt].blockStatus ) ||
           ( Fee_BlockConfig[blockIt].immediateData ) &&
           ( FEE_BLOCK_INCONSISTENT == Fee_BlockInfo[blockIt].blockStatus ))
            {
                VAR( uint16, AUTOMATIC ) blockSize;        
                VAR( uint16, AUTOMATIC ) alignedBlockSize;        
                
                /* Size of swaped block */
                blockSize = Fee_BlockConfig[blockIt].blockSize;
                
                /* Align Fee block size to the virtual page boundary */
                alignedBlockSize = Fee_AlignToVirtualPageSize( blockSize );
            
                /* Update the block address info */
                dataAddrIt -= alignedBlockSize;

                Fee_BlockInfo[blockIt].dataAddr = dataAddrIt;
            }
            else
            {
                /* Use 0 for inconsistent and not immediate block */
                Fee_BlockInfo[blockIt].dataAddr = 0U;
            }
        }
        else
        {
            /* No matching block */
        }
    }
    
    /* Switch to the new cluster */
    Fee_ClrGrpInfo[Fee_JobIntClrGrpIt].actClr = Fee_JobIntClrIt;
    Fee_ClrGrpInfo[Fee_JobIntClrGrpIt].actClrID++;
    Fee_ClrGrpInfo[Fee_JobIntClrGrpIt].hdrAddrIt = hdrAddrIt;
    Fee_ClrGrpInfo[Fee_JobIntClrGrpIt].dataAddrIt = dataAddrIt;
    
    /* restore original Fee_Job after ECC error */ 
    if( FEE_JOB_INT_SCAN_CLR == Fee_JobIntOriginalJob )
    {
        Fee_JobIntClrGrpIt++;
    }
    else
    {
    
    }

    /* Internal job has finished so transition
        from MEMIF_BUSYINTERNAL to MEMIF_BUSY */
    Fee_ModuleStatus = MEMIF_BUSY;

    /* And now cross fingers and re-schedule original job ... */
    Fee_Job = Fee_JobIntOriginalJob;
    
    RetVal = Fee_JobSchedule();
    
    return( RetVal );
}

/** 
    @brief Write Fee block header to flash

    @return MemIf_JobResultType
    @retval MEMIF_JOB_PENDING Underlying Fls accepted the write job
    @retval MEMIF_JOB_FAILED Underlying Fls didn't accept write job

    @pre Fee_JobBlockIndex must contain index of Fee block to write to
    @post Update the dataAddr and invalidAddr Fee_BlockConfig variables of
        written Fee block
    @post Initialize internal cluster swap sequence if requested block
        doesn't fit into current cluster
        
    @remarks Implements DFEE20129
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobWriteHdr( void )
{
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_FAILED;
    VAR( uint16, AUTOMATIC ) blockSize = 0U;
    VAR( uint16, AUTOMATIC ) alignedBlockSize =0U;
    VAR( Fls_LengthType, AUTOMATIC ) availClrSpace = 0UL;
    VAR( uint8, AUTOMATIC ) clrGrpIndex = (uint8)0;
    
    /* Index of cluster group the Fee block belongs to */
    clrGrpIndex = Fee_BlockConfig[Fee_JobBlockIndex].clrGrp;

    /* Calculate available space in active cluster */
    availClrSpace = Fee_ClrGrpInfo[clrGrpIndex].dataAddrIt - 
        Fee_ClrGrpInfo[clrGrpIndex].hdrAddrIt;
    
    /* Get size of Fee block */
    blockSize = Fee_BlockConfig[Fee_JobBlockIndex].blockSize;
    
    /* Align Fee block size to the virtual page boundary */
    alignedBlockSize = Fee_AlignToVirtualPageSize( blockSize );

    /* Mark the block as invalid until the block header is written 
    Fee_BlockInfo[Fee_JobBlockIndex].blockStatus = FEE_BLOCK_INVALID;*/
    
    /* One FEE_BLOCK_OVERHEAD must be left blank to have a clear separation
       between header block space and data block space */
    if(((uint32) alignedBlockSize + (2U * FEE_BLOCK_OVERHEAD )) > availClrSpace )
    {
        /* The block won't fit into current cluster. Init swap sequence... */
        
        /* Get cluster group index the block belongs to */
        Fee_JobIntClrGrpIt = clrGrpIndex;
        
        RetVal = Fee_JobIntSwap();
    } 
    else
    {
        VAR( Fls_AddressType, AUTOMATIC ) dataAddr;
        VAR( Fls_AddressType, AUTOMATIC ) hdrAddr;

        /* Calculate data and header addresses */
        dataAddr = Fee_ClrGrpInfo[clrGrpIndex].dataAddrIt - alignedBlockSize;
        hdrAddr = Fee_ClrGrpInfo[clrGrpIndex].hdrAddrIt;

        /* Serialize block header to the write buffer */
        Fee_SerializeBlockHdr( Fee_BlockConfig[Fee_JobBlockIndex].blockNumber,
            blockSize, dataAddr, 
            Fee_BlockConfig[Fee_JobBlockIndex].immediateData, Fee_DataBuffer );
        

        /* Write header to flash */
        if( (Std_ReturnType)E_OK != Fls_Write( hdrAddr, Fee_DataBuffer, FEE_BLOCK_OVERHEAD - \
                                     ( 2U * FEE_VIRTUAL_PAGE_SIZE )) )
        {
            /* Fls read job hasn't been accepted */
            RetVal = MEMIF_JOB_FAILED;
        }
        else
        {
            /* Fls read job has been accepted */
            RetVal = MEMIF_JOB_PENDING;    
        }
    }

    return( RetVal );
}

/** 
    @brief Write Fee block data to flash

    @return MemIf_JobResultType
    @retval MEMIF_JOB_PENDING Underlying Fls accepted the write job
    @retval MEMIF_JOB_FAILED Underlying Fls didn't accept write job

    @pre Fee_JobBlockIndex must contain index of Fee block to write to
    @pre Fee_JobDataDestPtr must contain valid pointer to user buffer
    @post Update hdrAddrIt, dataAddrIt Fee_ClrGrpInfo variables of current 
        cluster group if immediateData == FALSE only
    @post Changes blockStatus to FEE_BLOCK_INCONSISTENT
    @post Schedule either FEE_JOB_WRITE_VALIDATE or FEE_JOB_WRITE_UNALIGNED_DATA
        subsequent job
        
    @remarks Implements DFEE20130
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobWriteData( void )
{
    VAR( Fls_AddressType, AUTOMATIC ) dataAddr;
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_OK;
    VAR( uint16, AUTOMATIC ) blockSize = 0U;
    VAR( uint16, AUTOMATIC ) alignedBlockSize = 0U;    
    VAR( Fls_LengthType, AUTOMATIC ) writeLength = 0UL;    
    VAR( uint16, AUTOMATIC ) clrGrp =0U;
    P2VAR( uint8, AUTOMATIC, FEE_APPL_DATA ) writeDataPtr = 0;    

#if (FEE_BLOCK_ALWAYS_AVAILABLE == STD_OFF)
    if( !Fee_BlockConfig[Fee_JobBlockIndex].immediateData )
    {
        VAR( Fls_AddressType, AUTOMATIC ) hdrAddr;
        VAR( uint8, AUTOMATIC ) clrGrpIndex = (uint8)0;

        /* Index of cluster group the Fee block belongs to */
        clrGrpIndex = Fee_BlockConfig[Fee_JobBlockIndex].clrGrp;

        /* Get size of Fee block */
        blockSize = Fee_BlockConfig[Fee_JobBlockIndex].blockSize;

        /* Align Fee block size to the virtual page boundary */
        alignedBlockSize = Fee_AlignToVirtualPageSize( blockSize );

        /* Calculate data and header addresses */
        dataAddr = Fee_ClrGrpInfo[clrGrpIndex].dataAddrIt - alignedBlockSize;
        hdrAddr = Fee_ClrGrpInfo[clrGrpIndex].hdrAddrIt;

        Fee_BlockInfo[Fee_JobBlockIndex].dataAddr = dataAddr;
        Fee_BlockInfo[Fee_JobBlockIndex].invalidAddr = ( hdrAddr + FEE_BLOCK_OVERHEAD ) - FEE_VIRTUAL_PAGE_SIZE;
    }
    /* Mark the block as inconsistent since the block header has been written */
    Fee_BlockInfo[Fee_JobBlockIndex].blockStatus = FEE_BLOCK_INCONSISTENT;
#endif
    
    /* Get size of Fee block */
    blockSize = Fee_BlockConfig[Fee_JobBlockIndex].blockSize;

    /* Align Fee block size to the virtual page boundary */
    alignedBlockSize = Fee_AlignToVirtualPageSize( blockSize );

    /* Index of cluster group the Fee block belongs to */
    clrGrp = Fee_BlockConfig[Fee_JobBlockIndex].clrGrp;

    if( Fee_BlockConfig[Fee_JobBlockIndex].immediateData )
    {
        /* Don't update header and data pointes as it's immediate write */
    }
    else
    {
        /* Header has been written so update both header and data addresses */
        Fee_ClrGrpInfo[clrGrp].hdrAddrIt += FEE_BLOCK_OVERHEAD;
        Fee_ClrGrpInfo[clrGrp].dataAddrIt -= alignedBlockSize;
    }
    
    if( blockSize < FEE_VIRTUAL_PAGE_SIZE )
    {
        /* Go through buffer... */
        Fee_CopyDataToPageBuffer( Fee_JobDataDestPtr, Fee_DataBuffer, blockSize );
        writeDataPtr = Fee_DataBuffer;
        writeLength = FEE_VIRTUAL_PAGE_SIZE;
        
        /* Schedule write of validation pattern */
        Fee_Job = FEE_JOB_WRITE_VALIDATE;
    }
    else
    {
        writeDataPtr = Fee_JobDataDestPtr;
        
        if( alignedBlockSize == blockSize )
        {
            writeLength = blockSize;
            
            /* Schedule write of validation pattern */
            Fee_Job = FEE_JOB_WRITE_VALIDATE;
        }
        else
        {
            writeLength = (uint32) alignedBlockSize - FEE_VIRTUAL_PAGE_SIZE;
            
            /* Schedule write of unaligned data */  
            Fee_Job = FEE_JOB_WRITE_UNALIGNED_DATA;            
        }
    }
    
#if (FEE_BLOCK_ALWAYS_AVAILABLE == STD_ON)
    if( Fee_BlockConfig[Fee_JobBlockIndex].immediateData )
    {
#endif
        /* Use Block info because it has been updated into Fee_JobEraseImmediateDone */
        dataAddr = Fee_BlockInfo[Fee_JobBlockIndex].dataAddr;
#if (FEE_BLOCK_ALWAYS_AVAILABLE == STD_ON)
    }
    else
    {
        /* Use ClrGrp info */
        dataAddr = Fee_ClrGrpInfo[clrGrp].dataAddrIt;
    }
#endif   
    if( (Std_ReturnType)E_OK == Fls_Write( dataAddr, writeDataPtr, writeLength ) )
    {
        /* Fls read job has been accepted */
        RetVal = MEMIF_JOB_PENDING;    
    }
    else
    {
        /* Fls write job hasn't been accepted */
        RetVal = MEMIF_JOB_FAILED;
    }
    
    return( RetVal );
}

/** 
    @brief Write Fee block to flash

    @return MemIf_JobResultType
    @retval MEMIF_JOB_PENDING Underlying Fls accepted the write job
    @retval MEMIF_JOB_FAILED Underlying Fls didn't accept write job

    @pre Fee_JobBlockIndex must contain index of Fee block to write to
    @pre Fee_JobDataDestPtr must contain valid pointer to user buffer
    @post Initialize internal cluster swap sequence if requested block
        doesn't fit into current cluster
    @post Schedule FEE_JOB_WRITE_DATA subsequent job
    
    @remarks Implements DFEE20131
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobWrite( void )
{
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_FAILED;
    
    if( Fee_BlockConfig[Fee_JobBlockIndex].immediateData )
    {
        if( FEE_BLOCK_INCONSISTENT == Fee_BlockInfo[Fee_JobBlockIndex].blockStatus )
        {
            /* The immediate block is ready to be written */
            RetVal = Fee_JobWriteData();
        }
        else
        {
            /* The immediate block is not pre-erased and ready to be
                written */
            RetVal = MEMIF_JOB_FAILED;
        }
    }
    else
    {
        /* Write block header */
        RetVal = Fee_JobWriteHdr();
        
        /* Schedule next job */
        if( FEE_JOB_INT_SWAP_CLR_FMT == Fee_Job )
        {        
            /* Block din't fit into the cluster.
                Cluster swap has been enforced... */
        }
        else
        {
            Fee_Job = FEE_JOB_WRITE_DATA;        
        }
    }
    
    return( RetVal );
}

/** 
    @brief Write unaligned rest of Fee block data to flash

    @return MemIf_JobResultType
    @retval MEMIF_JOB_PENDING Underlying Fls accepted the write job
    @retval MEMIF_JOB_FAILED Underlying Fls didn't accept write job

    @pre Fee_JobBlockIndex must contain index of Fee block to write to
    @pre Fee_JobDataDestPtr must contain valid pointer to user buffer
    @post Schedule FEE_JOB_WRITE_VALIDATE subsequent job
    
    @remarks Implements DFEE20132
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobWriteUnalignedData( void )
{
    VAR( Fls_AddressType, AUTOMATIC ) dataAddr;
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_OK;
    VAR( uint16, AUTOMATIC ) writeOffset = 0U;
    VAR( uint16, AUTOMATIC ) writeLength = 0U;
    VAR( uint16, AUTOMATIC ) blockSize = 0U;
#if (FEE_BLOCK_ALWAYS_AVAILABLE == STD_ON)
    VAR( uint16, AUTOMATIC ) clrGrp =0U;

    /* Index of cluster group the Fee block belongs to */
    clrGrp = Fee_BlockConfig[Fee_JobBlockIndex].clrGrp;
#endif
    /* Get size of Fee block */
    blockSize = Fee_BlockConfig[Fee_JobBlockIndex].blockSize;

    /* Calculate number of bytes already written */
    writeOffset = (blockSize / FEE_VIRTUAL_PAGE_SIZE) * FEE_VIRTUAL_PAGE_SIZE;
    
    /* Calculate length remaining data to write */
    writeLength = blockSize % FEE_VIRTUAL_PAGE_SIZE;
    
    /** @note Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed 
              form of pointer arithmetic. See @ref Fee_c_REF_6 */
    Fee_CopyDataToPageBuffer( Fee_JobDataDestPtr + writeOffset, Fee_DataBuffer,
        writeLength );
        
#if (FEE_BLOCK_ALWAYS_AVAILABLE == STD_ON)
    if( Fee_BlockConfig[Fee_JobBlockIndex].immediateData )
    {
#endif
        /* Use Block info because it has been updated into Fee_JobEraseImmediateDone */
        dataAddr = Fee_BlockInfo[Fee_JobBlockIndex].dataAddr;
#if (FEE_BLOCK_ALWAYS_AVAILABLE == STD_ON)
    }
    else
    {
        /* Use ClrGrp info */
        dataAddr = Fee_ClrGrpInfo[clrGrp].dataAddrIt;
    }
#endif

    if( (Std_ReturnType)E_OK == Fls_Write( dataAddr + writeOffset,
                                Fee_DataBuffer,    FEE_VIRTUAL_PAGE_SIZE ) )
    {
        /* Fls write job has been accepted */
        RetVal = MEMIF_JOB_PENDING;    
    }
    else
    {
        /* Fls write job hasn't been accepted */
        RetVal = MEMIF_JOB_FAILED;
    }

    /* Schedule write of validation pattern */
    Fee_Job = FEE_JOB_WRITE_VALIDATE;
    
    return( RetVal );
}

/**
    @brief Validate Fee block by writing validation flag to flash

    @return MemIf_JobResultType
    @retval MEMIF_JOB_PENDING Underlying Fls accepted the write job
    @retval MEMIF_JOB_FAILED Underlying Fls didn't accept write job

    @pre Fee_JobBlockIndex must contain index of Fee block to validate
    @post Schedule FEE_JOB_WRITE_DONE subsequent job
    
    @remarks Implements DFEE20133
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobWriteValidate( void )
{
    VAR( Fls_AddressType, AUTOMATIC ) hdrAddr;
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_OK;
#if (FEE_BLOCK_ALWAYS_AVAILABLE == STD_ON)     
    VAR( uint8, AUTOMATIC ) clrGrpIndex = (uint8)0;
    
    /* Index of cluster group the Fee block belongs to */
    clrGrpIndex = Fee_BlockConfig[Fee_JobBlockIndex].clrGrp;
#endif       
    /* Serialize validation pattern to buffer */
    Fee_SerializeFlag( Fee_DataBuffer, FEE_VALIDATED_VALUE );
    
#if (FEE_BLOCK_ALWAYS_AVAILABLE == STD_ON)
    if( Fee_BlockConfig[Fee_JobBlockIndex].immediateData )
    {
#endif
        /* Use Block info because it has been updated into Fee_JobEraseImmediateDone */
        hdrAddr = (Fee_BlockInfo[Fee_JobBlockIndex].invalidAddr - FEE_VIRTUAL_PAGE_SIZE);
#if (FEE_BLOCK_ALWAYS_AVAILABLE == STD_ON)
    }
    else
    {
        /* Use ClrGrp info */
        hdrAddr = Fee_ClrGrpInfo[clrGrpIndex].hdrAddrIt - (2 *  FEE_VIRTUAL_PAGE_SIZE);
    }
#endif
    
    /* Write validation pattern to flash */
    if( (Std_ReturnType)E_OK == Fls_Write( hdrAddr, Fee_DataBuffer, FEE_VIRTUAL_PAGE_SIZE) )
    {
        /* Fls read job has been accepted */
        RetVal = MEMIF_JOB_PENDING;    
    }
    else
    {
        /* Fls write job hasn't been accepted */
        RetVal = MEMIF_JOB_FAILED;
    }
    
    /* Finalize the write operation */
    Fee_Job = FEE_JOB_WRITE_DONE;
    
    return( RetVal );
}

/**
    @brief Finalize validation of Fee block

    @return MemIf_JobResultType
    @retval MEMIF_JOB_OK

    @pre Fee_JobBlockIndex must contain index of Fee block to write to
    @post change Fee block status to FEE_BLOCK_VALID
    @post Schedule FEE_JOB_DONE subsequent job
    
    @remarks Implements DFEE20134
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobWriteDone( void )
{
#if (FEE_BLOCK_ALWAYS_AVAILABLE == STD_ON)
    VAR( Fls_AddressType, AUTOMATIC ) dataAddr;
    VAR( Fls_AddressType, AUTOMATIC ) hdrAddr;
    VAR( uint8, AUTOMATIC ) clrGrpIndex = (uint8)0;
    
    /* Index of cluster group the Fee block belongs to */
    clrGrpIndex = Fee_BlockConfig[Fee_JobBlockIndex].clrGrp;
    
    /* Calculate data and header addresses */
    dataAddr = Fee_ClrGrpInfo[clrGrpIndex].dataAddrIt;
    hdrAddr = Fee_ClrGrpInfo[clrGrpIndex].hdrAddrIt;

    if( !Fee_BlockConfig[Fee_JobBlockIndex].immediateData )
    {
    /* Update the block address info */
    Fee_BlockInfo[Fee_JobBlockIndex].dataAddr = dataAddr; 
    Fee_BlockInfo[Fee_JobBlockIndex].invalidAddr = ( hdrAddr - FEE_VIRTUAL_PAGE_SIZE);
    }
#endif

    /* Mark the Fee block as valid */
    Fee_BlockInfo[Fee_JobBlockIndex].blockStatus = FEE_BLOCK_VALID;

    /* No more Fls jobs to schedule */
    Fee_Job = FEE_JOB_DONE;
    
    return( MEMIF_JOB_OK );
}

/**
    @brief Invalidate Fee block by writing the invalidation flag to flash

    @return MemIf_JobResultType
    @retval MEMIF_JOB_PENDING Underlying Fls accepted the write job
    @retval MEMIF_JOB_FAILED Underlying Fls didn't accept write job
    @retval MEMIF_JOB_OK The Fee block is already invalid
    
    @pre Fee_JobBlockIndex must contain index of Fee block to invalidate
    @post Schedule FEE_JOB_DONE or FEE_JOB_INVAL_BLOCK_DONE subsequent jobs
    
    @remarks Implements DFEE20135
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobInvalBlock( void )
{
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_OK;
    
    if( FEE_BLOCK_INVALID == Fee_BlockInfo[Fee_JobBlockIndex].blockStatus ) 
    {
        /* No more subsequent Fls jobs to schedule */
        Fee_Job = FEE_JOB_DONE;
        
        /* Fee job completed */
        RetVal = MEMIF_JOB_OK;        
    }
    else
    {
        /* Serialize invalidation pattern to buffer */
        Fee_SerializeFlag( Fee_DataBuffer, FEE_INVALIDATED_VALUE );
        
        /* Write invalidation pattern to flash */
        if( (Std_ReturnType)E_OK == Fls_Write( Fee_BlockInfo[Fee_JobBlockIndex].invalidAddr, \
            Fee_DataBuffer, FEE_VIRTUAL_PAGE_SIZE ) )
        {
            /* Fls read job has been accepted */
            RetVal = MEMIF_JOB_PENDING;    
        }
        else
        {
            /* Fls write job hasn't been accepted */
            RetVal = MEMIF_JOB_FAILED;
        }
        
        /* Finalize the invalidation operation */
        Fee_Job = FEE_JOB_INVAL_BLOCK_DONE;
    }
    
    return( RetVal );
}

/**
    @brief Finalize invalidation of Fee block

    @return MemIf_JobResultType
    @retval MEMIF_JOB_OK

    @pre Fee_JobBlockIndex must contain index of Fee block to write to
    @post change Fee block status to FEE_BLOCK_INVALID
    @post Schedule FEE_JOB_DONE subsequent job
    
    @remarks Implements DFEE20136
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobInvalBlockDone( void )
{
    /* Mark the Fee block as in valid */
    Fee_BlockInfo[Fee_JobBlockIndex].blockStatus = FEE_BLOCK_INVALID;

    /* No more subsequent Fls jobs to schedule */
    Fee_Job = FEE_JOB_DONE;
    
    /* Fee job completed */
    return( MEMIF_JOB_OK );
}

/**
    @brief Erase (pre-allocate) immediate Fee block

    @return MemIf_JobResultType
    @retval MEMIF_JOB_PENDING Underlying Fls accepted the write job
    @retval MEMIF_JOB_FAILED Underlying Fls didn't accept write job
    
    @pre Fee_JobBlockIndex must contain index of Fee block to pre-allocated
    @post Initialize internal cluster swap sequence if requested block
        doesn't fit into current cluster    
    @post Schedule FEE_JOB_ERASE_IMMEDIATE_DONE subsequent jobs
    
    @remarks Implements DFEE20137
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobEraseImmediate( void )
{
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_OK;
    
    /* Write block header */
    RetVal = Fee_JobWriteHdr();
        
    /* Schedule next job */
    if( FEE_JOB_INT_SWAP_CLR_FMT == Fee_Job )
    {
        /* Block din't fit into the cluster.
            Cluster swap has been enforced... */
    }
    else
    {
        Fee_Job = FEE_JOB_ERASE_IMMEDIATE_DONE;
    }

    return( RetVal );
}

/**
    @brief Finalize erase (pre-allocation) of Fee block

    @return MemIf_JobResultType
    @retval MEMIF_JOB_OK

    @pre Fee_JobBlockIndex must contain index of Fee block to write to
    @post change Fee block status to FEE_BLOCK_INCONSISTENT
    @post Schedule FEE_JOB_DONE subsequent job
    
    @remarks Implements DFEE20138
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobEraseImmediateDone( void )
{
    VAR( uint16, AUTOMATIC ) blockSize = 0U;
    VAR( uint16, AUTOMATIC ) alignedBlockSize = 0U;
    VAR( uint16, AUTOMATIC ) clrGrp = 0U;
    
#if (FEE_BLOCK_ALWAYS_AVAILABLE == STD_OFF)
    VAR( Fls_AddressType, AUTOMATIC ) dataAddr;
    VAR( Fls_AddressType, AUTOMATIC ) hdrAddr;

    VAR( uint8, AUTOMATIC ) clrGrpIndex = (uint8)0;
#endif  
    /* Mark the Fee immediate block as inconsistent 
        so it can be written later on */
    Fee_BlockInfo[Fee_JobBlockIndex].blockStatus = FEE_BLOCK_INCONSISTENT;

    /* Get size of Fee block */
    blockSize = Fee_BlockConfig[Fee_JobBlockIndex].blockSize;

    /* Align Fee block size to the virtual page boundary */
    alignedBlockSize = Fee_AlignToVirtualPageSize( blockSize );

    /* Index of cluster group the Fee block belongs to */
    clrGrp = Fee_BlockConfig[Fee_JobBlockIndex].clrGrp;
    
#if (FEE_BLOCK_ALWAYS_AVAILABLE == STD_OFF)

    /* Index of cluster group the Fee block belongs to */
    clrGrpIndex = Fee_BlockConfig[Fee_JobBlockIndex].clrGrp;
    
    dataAddr = Fee_ClrGrpInfo[clrGrpIndex].dataAddrIt - alignedBlockSize;
    hdrAddr = Fee_ClrGrpInfo[clrGrpIndex].hdrAddrIt;

     /* Update the block address info */
    Fee_BlockInfo[Fee_JobBlockIndex].dataAddr = dataAddr;
    Fee_BlockInfo[Fee_JobBlockIndex].invalidAddr = ( hdrAddr + FEE_BLOCK_OVERHEAD ) - FEE_VIRTUAL_PAGE_SIZE;

#endif
    
    /* Header has been written so update both header and data addresses */
    Fee_ClrGrpInfo[clrGrp].hdrAddrIt += FEE_BLOCK_OVERHEAD;
    Fee_ClrGrpInfo[clrGrp].dataAddrIt -= alignedBlockSize;
    
#if (FEE_BLOCK_ALWAYS_AVAILABLE == STD_ON)
    /* As Fee immediate block is inconsistent 
       it is not possible to get previous data, so update Block info */
    Fee_BlockInfo[Fee_JobBlockIndex].invalidAddr = (Fee_ClrGrpInfo[clrGrp].hdrAddrIt - FEE_VIRTUAL_PAGE_SIZE);
    Fee_BlockInfo[Fee_JobBlockIndex].dataAddr = Fee_ClrGrpInfo[clrGrp].dataAddrIt;
#endif
    /* No more subsequent Fls jobs to schedule */
    Fee_Job = FEE_JOB_DONE;
    
    /* Fee job completed */
    return( MEMIF_JOB_OK );
}

/**
    @brief Schedule subsequent jobs

    @return MemIf_JobResultType

    @pre Fee_Job must contain type of job to schedule
    
    @remarks Implements DFEE20139
*/
STATIC FUNC( MemIf_JobResultType, FEE_CODE ) Fee_JobSchedule( void )
{
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_FAILED;
        
    switch( Fee_Job )
    {
        /* Fee_Read() related jobs */
        case FEE_JOB_READ:
            RetVal = Fee_JobRead();
            break;
    
        /* Fee_Write() related jobs */
        case FEE_JOB_WRITE:
            RetVal = Fee_JobWrite();
            break;
            
        case FEE_JOB_WRITE_DATA:
            RetVal = Fee_JobWriteData();
            break;
            
        case FEE_JOB_WRITE_UNALIGNED_DATA:
            RetVal = Fee_JobWriteUnalignedData();
            break;
        
        case FEE_JOB_WRITE_VALIDATE:
            RetVal = Fee_JobWriteValidate();
            break;
        
        case FEE_JOB_WRITE_DONE:
            RetVal = Fee_JobWriteDone();
            break;

        /* Fee_InvalidateBlock() related jobs */
        case FEE_JOB_INVAL_BLOCK:
            RetVal = Fee_JobInvalBlock();
            break;
            
        case FEE_JOB_INVAL_BLOCK_DONE:
            RetVal = Fee_JobInvalBlockDone();
            break;
    
        /* Fee_EraseImmediateBlock() related jobs */
        case FEE_JOB_ERASE_IMMEDIATE:
            RetVal = Fee_JobEraseImmediate();
            break;
    
        case FEE_JOB_ERASE_IMMEDIATE_DONE:
            RetVal = Fee_JobEraseImmediateDone();
            break;
        
        /* Fee_Init() related jobs */
        case FEE_JOB_INT_SCAN:
            RetVal = Fee_JobIntScan();
            break;

        case FEE_JOB_INT_SCAN_CLR:
            RetVal = Fee_JobIntScanClr();
            break;
            
        case FEE_JOB_INT_SCAN_CLR_HDR_PARSE:
            RetVal = Fee_JobIntScanClrHdrParse((boolean) TRUE );
            break;
            
        case FEE_JOB_INT_SCAN_CLR_FMT:
            RetVal = Fee_JobIntScanClrFmt();
            break;
            
        case FEE_JOB_INT_SCAN_CLR_FMT_DONE:
            RetVal = Fee_JobIntScanClrFmtDone();
            break;

        case FEE_JOB_INT_SCAN_BLOCK_HDR_PARSE:
            RetVal = Fee_JobIntScanBlockHdrParse((boolean) TRUE );
            break;

        /* Swap related jobs */
        case FEE_JOB_INT_SWAP_CLR_FMT:
            RetVal = Fee_JobIntSwapClrFmt();
            break;

        case FEE_JOB_INT_SWAP_BLOCK:
            RetVal = Fee_JobIntSwapBlock();
            break;

        case FEE_JOB_INT_SWAP_DATA_READ:
            RetVal = Fee_JobIntSwapDataRead((boolean) TRUE );
            break;        

        case FEE_JOB_INT_SWAP_DATA_WRITE:
            RetVal = Fee_JobIntSwapDataWrite((boolean) TRUE );
            break;

        case FEE_JOB_INT_SWAP_CLR_VLD_DONE:
            RetVal = Fee_JobIntSwapClrVldDone();
            break;
        /* if the job is finished switch case will break */
        case FEE_JOB_DONE:
            /* Do nothing */
            break;
        default:
            Cer_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_JOBSCHEDULE_ID, FEE_E_JOB_UNKNOW);
            /* Compiler_Warning: This break statement will never be reached because a call to Cer_ReporError()
               function causes an infinite loop from which it is impossible to escape.
            */
            break;
    }
    
    return( RetVal );
}

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

/* Job end notification routine provided by the upper layer    module (declaration) */
FEE_NVM_JOB_END_NOTIFICATION_DECL

/* Job error notification routine provided by the upper layer module (declaration) */
FEE_NVM_JOB_ERROR_NOTIFICATION_DECL

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
FUNC( void, FEE_CODE ) Fee_Init( void )
{ 
/**    @remarks Implements DFEE01001 */
#if( FEE_DEV_ERROR_DETECT == STD_ON )
    /**    @remarks Implements DFEE01002 */
    if( MEMIF_BUSY == Fee_ModuleStatus )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_INIT_ID, FEE_E_BUSY );
    }
    /**    @remarks Implements DFEE01003 */
    else if( MEMIF_BUSY_INTERNAL == Fee_ModuleStatus )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_INIT_ID, FEE_E_BUSY_INTERNAL );
    }    
    else
#endif    /* FEE_DEV_ERROR_DETECT == STD_ON */    
    {
        VAR( uint32, AUTOMATIC ) InvalIndex;

        /* Invalidate all blocks */
        /**    @remarks Implements DFEE01004 */
        for( InvalIndex = 0U; InvalIndex < FEE_NUMBER_OF_BLOCKS; InvalIndex++ )
        {
            Fee_BlockInfo[InvalIndex].blockStatus = FEE_BLOCK_INVALID;
        }
        
        /* Invalidate all cluster groups */
        /**    @remarks Implements DFEE01005 */
        for( InvalIndex = 0U; InvalIndex < FEE_NUMBER_OF_CLUSTER_GROUPS; InvalIndex++ )
        {
            Fee_ClrGrpInfo[InvalIndex].actClrID = 0U;
        }        
    
        /* Schedule init job */
        /**    @remarks Implements DFEE01006 */
        Fee_Job = FEE_JOB_INT_SCAN;

        /**    @remarks Implements DFEE01007 */
        Fee_ModuleStatus = MEMIF_BUSY_INTERNAL;
        
        /**    @remarks Implements DFEE01008 */
        Fee_JobResult = MEMIF_JOB_PENDING;
    }
}

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
 *                                   DFEE03003,DFEE03004, DFEE03005, DFEE05052
*/
FUNC( void, FEE_CODE ) Fee_SetMode(
    VAR( MemIf_ModeType, AUTOMATIC) Mode )
{

/* If FEE_SET_MODE_API is disabled Fee_SetMode became an empty function
   Note: this is to avoid robustness issues (in term of internal variables) */
    /** @remarks Implements DFEE05052 */
#if( FEE_SET_MODE_API == STD_OFF )
#if( FEE_DEV_ERROR_DETECT == STD_ON )
    Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_SETMODE_ID, FEE_E_SET_MODE_API );
#endif    /* FEE_DEV_ERROR_DETECT == STD_ON */
#else
/** @remarks Implements DFEE03001 */
#if( FEE_DEV_ERROR_DETECT == STD_ON )
    /** @remarks Implements DFEE03002 */
    if( MEMIF_UNINIT == Fee_ModuleStatus )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_SETMODE_ID, FEE_E_UNINIT );
    }
    /** @remarks Implements DFEE03003 */
    else if( MEMIF_BUSY == Fee_ModuleStatus )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_SETMODE_ID, FEE_E_BUSY );
    }
    /** @remarks Implements DFEE03004 */
    else if( MEMIF_BUSY_INTERNAL == Fee_ModuleStatus )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_SETMODE_ID, FEE_E_BUSY_INTERNAL );
    }        
    else
#endif    /* FEE_DEV_ERROR_DETECT == STD_ON */    
    {
        /** @remarks Implements DFEE03005 */
        Fls_SetMode( Mode );
    }
#endif  /* FEE_SET_MODE_API == STD_OFF */
}

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
FUNC( Std_ReturnType, FEE_CODE ) Fee_Read(
    VAR( uint16, AUTOMATIC ) BlockNumber,
    VAR( uint16, AUTOMATIC ) BlockOffset,
    P2VAR( uint8, AUTOMATIC, FEE_APPL_DATA ) DataBufferPtr,
    VAR( uint16, AUTOMATIC ) Length )
{
    VAR( Std_ReturnType, AUTOMATIC ) RetVal = (Std_ReturnType)E_OK;
    VAR( uint16, AUTOMATIC ) blockIndex = Fee_GetBlockIndex( BlockNumber );

/** @remarks Implements    DFEE02001 */
#if( FEE_DEV_ERROR_DETECT == STD_ON )
    /** @remarks Implements    DFEE02002 */
    if( MEMIF_UNINIT == Fee_ModuleStatus )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_READ_ID, FEE_E_UNINIT );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /** @remarks Implements    DFEE02003 */
    else if( 0xffffU == blockIndex )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_READ_ID, FEE_E_INVALID_BLOCK_NO );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /** @remarks Implements    DFEE02004 */
    else if( BlockOffset >= Fee_BlockConfig[blockIndex].blockSize )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_READ_ID, FEE_E_PARAM_OFFSET );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /** @remarks Implements    DFEE02005 */
    else if(( 0U == Length ) || ((BlockOffset + Length) > Fee_BlockConfig[blockIndex].blockSize ))
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_READ_ID, FEE_E_PARAM_LENGTH );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /** @remarks Implements    DFEE02006 */
    else if( MEMIF_BUSY == Fee_ModuleStatus )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_READ_ID, FEE_E_BUSY );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /** @remarks Implements    DFEE02007 */
    else if( MEMIF_BUSY_INTERNAL == Fee_ModuleStatus )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_READ_ID, FEE_E_BUSY_INTERNAL );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /** @remarks Implements    DFEE02008 */
    else if( NULL_PTR == DataBufferPtr )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_READ_ID, FEE_E_PARAM_DATA );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
#endif    /* FEE_DEV_ERROR_DETECT == STD_ON */

        /* Configure the read job */
        /** @remarks Implements    DFEE02009 */
        Fee_JobBlockIndex = blockIndex;        
        
        /** @remarks Implements    DFEE02010 */
        Fee_JobBlockOffset = BlockOffset;
        
        /** @remarks Implements    DFEE02011 */
        Fee_JobBlockLength = Length;
        
        /** @remarks Implements    DFEE02012 */
        Fee_JobDataDestPtr = DataBufferPtr;
        
        /** @remarks Implements    DFEE02013 */
        Fee_Job = FEE_JOB_READ;

        /** @remarks Implements    DFEE02014 */
        Fee_ModuleStatus = MEMIF_BUSY;
        
        /* Execute the read job */
        /** @remarks Implements    DFEE02015 */
        Fee_JobResult = MEMIF_JOB_PENDING;
        
#if( FEE_DEV_ERROR_DETECT == STD_ON )        
    }
#endif    /* FEE_DEV_ERROR_DETECT == STD_ON */

    return( RetVal );
}

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
FUNC( Std_ReturnType, FEE_CODE ) Fee_Write(
    VAR( uint16, AUTOMATIC ) BlockNumber,
    P2VAR( uint8, AUTOMATIC, FEE_APPL_DATA ) DataBufferPtr) 
{
    VAR( Std_ReturnType, AUTOMATIC ) RetVal = (Std_ReturnType)E_OK;
    VAR( uint16, AUTOMATIC ) blockIndex = Fee_GetBlockIndex( BlockNumber );

/** @remarks Implements    DFEE04001 */
#if( FEE_DEV_ERROR_DETECT == STD_ON )
    /** @remarks Implements    DFEE04002 */
    if( MEMIF_UNINIT == Fee_ModuleStatus )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_WRITE_ID, FEE_E_UNINIT );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /** @remarks Implements    DFEE04003 */
    else if( 0xffffU == blockIndex )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_WRITE_ID, FEE_E_INVALID_BLOCK_NO );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /** @remarks Implements    DFEE04004 */
    else if( MEMIF_BUSY == Fee_ModuleStatus )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_WRITE_ID, FEE_E_BUSY );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /** @remarks Implements    DFEE04005 */
    else if( MEMIF_BUSY_INTERNAL == Fee_ModuleStatus )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_WRITE_ID, FEE_E_BUSY_INTERNAL );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /** @remarks Implements    DFEE04006 */
    else if( NULL_PTR == DataBufferPtr )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_WRITE_ID, FEE_E_PARAM_DATA );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
#endif    /* FEE_DEV_ERROR_DETECT == STD_ON */

        /* Configure the write job */
        /** @remarks Implements    DFEE04007 */
        Fee_JobBlockIndex = blockIndex;
        
        /** @remarks Implements    DFEE04008 */
        Fee_JobDataDestPtr = DataBufferPtr;
        
        /** @remarks Implements    DFEE04009 */
        Fee_Job = FEE_JOB_WRITE;
        
        /** @remarks Implements    DFEE04010 */
        Fee_ModuleStatus = MEMIF_BUSY;
        
        /* Execute the write job */
        /** @remarks Implements    DFEE04011 */
        Fee_JobResult = MEMIF_JOB_PENDING;
        
#if( FEE_DEV_ERROR_DETECT == STD_ON )        
    }
#endif    /* FEE_DEV_ERROR_DETECT == STD_ON */

    return( RetVal );
}

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
 *                                   DFEE05003, DFEE05004, DFEE05005, DFEE05051
*/
FUNC( void, FEE_CODE ) Fee_Cancel( void )
{

/* If FEE_CANCEL_API is disabled Fee_Cancel became an empty function
   Note: this is to avoid robustness issues (in term of internal variables) */
    /** @remarks Implements DFEE05051 */
#if( FEE_CANCEL_API == STD_OFF )
#if( FEE_DEV_ERROR_DETECT == STD_ON )
    Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_CANCEL_ID, FEE_E_CANCEL_API );
#endif    /* FEE_DEV_ERROR_DETECT == STD_ON */
#else

/*     @remarks Implements DFEE05001 */
#if( FEE_DEV_ERROR_DETECT == STD_ON )
    if( MEMIF_UNINIT == Fee_ModuleStatus )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_CANCEL_ID, FEE_E_UNINIT );
    }
    else
#endif    /* FEE_DEV_ERROR_DETECT == STD_ON */
    {
        /*     @remarks Implements DFEE05002 */
        if( MEMIF_JOB_PENDING == Fee_JobResult )
        {
            /*     @remarks Implements DFEE05003 */
            Fee_JobResult = MEMIF_JOB_CANCELLED;
            Fee_Job       = FEE_JOB_DONE;
        
            /* Cancel ongoing Fls job if any */
            /*     @remarks Implements DFEE05004 */
            Fls_Cancel();
        
            /*     @remarks Implements DFEE05005 */
            if( MEMIF_BUSY_INTERNAL == Fee_ModuleStatus )
            {
                /* No notifications from internal jobs */
                Fee_ModuleStatus = MEMIF_IDLE;
            }
            else
            {
                Fee_ModuleStatus = MEMIF_IDLE;
                
                /* Call job error notification function */
                FEE_NVM_JOB_ERROR_NOTIFICATION
            }
        }
        else
        {
            /* Leave the job result unchanged */
        }
    }
#endif   /* FEE_CANCEL_API == STD_OFF */
}

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
FUNC( MemIf_StatusType, FEE_CODE ) Fee_GetStatus( void ) 
{
    /** @remarks Implements DFEE06001 */
    return( Fee_ModuleStatus );
}

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
FUNC( MemIf_JobResultType, FEE_CODE ) Fee_GetJobResult( void )
{
    /** @remarks Implements DFEE07001 */
    return( Fee_JobResult );
}

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
FUNC( Std_ReturnType, FEE_CODE ) Fee_InvalidateBlock(
    VAR( uint16, AUTOMATIC ) BlockNumber )
{
    VAR( Std_ReturnType, AUTOMATIC ) RetVal = (Std_ReturnType)E_OK;
    VAR( uint16, AUTOMATIC ) blockIndex = Fee_GetBlockIndex( BlockNumber );

/**    @remarks Implements DFEE08001 */
#if( FEE_DEV_ERROR_DETECT == STD_ON )
    /**    @remarks Implements DFEE08002 */
    if( MEMIF_UNINIT == Fee_ModuleStatus )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_INVALIDATEBLOCK_ID, FEE_E_UNINIT );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /**    @remarks Implements DFEE08003 */
    else if( 0xffffU == blockIndex )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_INVALIDATEBLOCK_ID, \
                                                 FEE_E_INVALID_BLOCK_NO );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /**    @remarks Implements DFEE08004 */
    else if( MEMIF_BUSY == Fee_ModuleStatus )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_INVALIDATEBLOCK_ID, FEE_E_BUSY );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /**    @remarks Implements DFEE08005 */
    else if( MEMIF_BUSY_INTERNAL == Fee_ModuleStatus )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_INVALIDATEBLOCK_ID, \
                                                 FEE_E_BUSY_INTERNAL );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }    
    else
    {
#endif    /* FEE_DEV_ERROR_DETECT == STD_ON */

        /* Configure the invalidate block job */
        /**    @remarks Implements DFEE08006 */
        Fee_JobBlockIndex = blockIndex;
    
        /**    @remarks Implements DFEE08007 */
        Fee_Job = FEE_JOB_INVAL_BLOCK;
        
        /**    @remarks Implements DFEE08008 */
        Fee_ModuleStatus = MEMIF_BUSY;
        
        /* Execute the invalidate block job */
        /**    @remarks Implements DFEE08009 */
        Fee_JobResult = MEMIF_JOB_PENDING;
#if( FEE_DEV_ERROR_DETECT == STD_ON )        
    }
#endif    /* FEE_DEV_ERROR_DETECT == STD_ON */

    return( RetVal );
}

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
#if(( FEE_VERSION_INFO_API == STD_ON ) || defined(__DOXYGEN__))
FUNC( void, FEE_CODE ) Fee_GetVersionInfo(
    P2VAR( Std_VersionInfoType, AUTOMATIC, FEE_APPL_DATA ) VersionInfoPtr )
{
/** @remarks Implements    DFEE09002 */
#if( FEE_DEV_ERROR_DETECT == STD_ON )
    if( NULL_PTR == VersionInfoPtr )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_GETVERSIONINFO_ID, \
                                                 FEE_E_PARAM_POINTER );
    }
    else
    {
#endif /* FEE_DEV_ERROR_DETECT == STD_ON */
        /** @remarks Implements    DFEE09003 */
        VersionInfoPtr->moduleID = FEE_MODULE_ID;
        VersionInfoPtr->vendorID = FEE_VENDOR_ID;
        VersionInfoPtr->instanceID = FEE_INSTANCE_ID;
        VersionInfoPtr->sw_major_version = FEE_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = FEE_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = FEE_SW_PATCH_VERSION;
#if( FEE_DEV_ERROR_DETECT == STD_ON )
    }
#endif /* FEE_DEV_ERROR_DETECT == STD_ON */
}
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
FUNC( Std_ReturnType, FEE_CODE ) Fee_EraseImmediateBlock(
    VAR( uint16, AUTOMATIC ) BlockNumber )
{
    VAR( Std_ReturnType, AUTOMATIC ) RetVal = (Std_ReturnType)E_OK;
    VAR( uint16, AUTOMATIC ) blockIndex = Fee_GetBlockIndex( BlockNumber );
 
/**    @remarks Implements DFEE10001 */
#if( FEE_DEV_ERROR_DETECT == STD_ON )
    /**    @remarks Implements DFEE10002 */
    if( MEMIF_UNINIT == Fee_ModuleStatus )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_ERASEIMMEDIATEBLOCK_ID, FEE_E_UNINIT );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /**    @remarks Implements DFEE10003 */
    else if( 0xffffU == blockIndex )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_ERASEIMMEDIATEBLOCK_ID, \
                                                 FEE_E_INVALID_BLOCK_NO );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /**    @remarks Implements DFEE10004 */
    else if( !Fee_BlockConfig[blockIndex].immediateData )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_ERASEIMMEDIATEBLOCK_ID, \
                                                 FEE_E_INVALID_BLOCK_NO );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }    
    /**    @remarks Implements DFEE10005 */
    else if( MEMIF_BUSY == Fee_ModuleStatus )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_ERASEIMMEDIATEBLOCK_ID, \
                                                               FEE_E_BUSY );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /**    @remarks Implements DFEE10006 */
    else if( MEMIF_BUSY_INTERNAL == Fee_ModuleStatus )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_ERASEIMMEDIATEBLOCK_ID, \
                                                 FEE_E_BUSY_INTERNAL );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }    
    else
    {
#endif    /* FEE_DEV_ERROR_DETECT == STD_ON */

        /* Configure the erase immediate block job */
        /**    @remarks Implements DFEE10007 */
        Fee_JobBlockIndex = blockIndex;
        
        /**    @remarks Implements DFEE10008 */
        Fee_Job = FEE_JOB_ERASE_IMMEDIATE;
        
        /**    @remarks Implements DFEE10009 */
        Fee_ModuleStatus = MEMIF_BUSY;
        
        /* Execute the erase immediate block job */
        /**    @remarks Implements DFEE10010 */
        Fee_JobResult = MEMIF_JOB_PENDING;
#if( FEE_DEV_ERROR_DETECT == STD_ON )        
    }
#endif    /* FEE_DEV_ERROR_DETECT == STD_ON */

    return( RetVal );
}

/** 
 * @brief   Service to report the FEE module the successful end of 
 *          an asynchronous operation.
 * @details The underlying flash driver shall call the function 
 *          Fee_JobEndNotification to report the successful end of 
 *          an asynchronous operation.   
 * @pre     The module must be initialized
 * @post    Changes Fee_ModuleStatus module status and Fee_JobResult internal 
 *          variables. 
 * @note    The function Autosar Service ID[hex]: 0x10.   
 * @note    Synchronous
 * @note    Non Reentrant                         
 *
 * @api  
 *       
 * @remarks Implements              DFEE21111, DFEE11000, DFEE11001, DFEE11002, 
 *                                  DFEE11003, DFEE11004, DFEE11005, DFEE11006, 
 *                                  DFEE11007, DFEE11008
*/
FUNC( void, FEE_CODE ) Fee_JobEndNotification( void )
{
    /**    @remarks Implements DFEE11001 */
    if( FEE_JOB_DONE == Fee_Job )
    {
        /* Last schedule Fls job finished */
        /**    @remarks Implements DFEE11002 */
        Fee_JobResult = Fls_GetJobResult();
        
        /**    @remarks Implements DFEE11003 */
        if( MEMIF_BUSY_INTERNAL == Fee_ModuleStatus )
        {
            /* no notifications from internal jobs */
            Fee_ModuleStatus = MEMIF_IDLE;
        }
        else
        {
            Fee_ModuleStatus = MEMIF_IDLE;
            
            /* Call job end notification function */
            FEE_NVM_JOB_END_NOTIFICATION
        }
    }
    else
    {
        /**    @remarks Implements DFEE11004 */
        Fee_JobResult = Fee_JobSchedule();

        /**    @remarks Implements DFEE11006 */
        if( MEMIF_JOB_OK == Fee_JobResult )
        {
            /**    @remarks Implements DFEE11007 */
            if( MEMIF_BUSY_INTERNAL == Fee_ModuleStatus )
            {
                /* no notifications from internal jobs */
                Fee_ModuleStatus = MEMIF_IDLE;
            }
            else
            {
                Fee_ModuleStatus = MEMIF_IDLE;

                /* Call job end notification function */
                FEE_NVM_JOB_END_NOTIFICATION
            }
        }
        /**    @remarks Implements DFEE11005 */
        else if( MEMIF_JOB_PENDING == Fee_JobResult )
        {
            /* Nothing to do (ongoing Fls job) */
        }
        else
        {
            /**    @remarks Implements DFEE11008 */
            if( MEMIF_BUSY_INTERNAL == Fee_ModuleStatus )
            {
                /* no notifications from internal jobs */
                Fee_ModuleStatus = MEMIF_IDLE;
            }
            else
            {
                Fee_ModuleStatus = MEMIF_IDLE;
                
                /* Call job error notification function */
                FEE_NVM_JOB_ERROR_NOTIFICATION
            }
        }
    }
}

/** 
 * @brief   Service to report the FEE module the failure of 
 *          an asynchronous operation.
 * @details The underlying flash driver shall call the function 
 *          Fee_JobErrorNotification to report the failure of 
 *          an asynchronous operation.                      
 * @pre     The module must be initialized.
 * @post    Changes Fee_ModuleStatus module status and Fee_JobResult 
 *          internal variables.
 *
 * @note    The function Autosar Service ID[hex]: 0x11.   
 * @note    Synchronous
 * @note    Non Reentrant                              
 *
 * @api  
 *      
 * @remarks Implements               DFEE21112, DFEE12000, DFEE12001, DFEE12002, 
 *                                   DFEE12003, DFEE12004, DFEE12005, DFEE12006
 *          
*/
FUNC( void, FEE_CODE ) Fee_JobErrorNotification( void )
{
    /** @remarks Implements DFEE12001 */
    if( MEMIF_JOB_CANCELLED == Fee_JobResult )
    {
        /* Fls job has been canceled. Do nothing in this callback.
            The NvM_JobErrorNotification() callback will be called from 
            the Fee_Cancel()function which called the Fls_Cancel() function */
    }
    else
    {
        switch( Fee_Job )
        {
            /* Error while reading block header. Treat block header as 
                invalid and    stop reading further block headers */
            /** @remarks Implements DFEE12002 */
            case FEE_JOB_INT_SCAN_BLOCK_HDR_PARSE:
                Fee_JobResult = Fee_JobIntScanBlockHdrParse((boolean) FALSE );
                break;

            /* Error while reading cluster header. Treat cluster as 
                invalid and    move on to next cluster */
            /** @remarks Implements DFEE12003 */
            case FEE_JOB_INT_SCAN_CLR_HDR_PARSE:
                Fee_JobResult = Fee_JobIntScanClrHdrParse((boolean) FALSE );
                break;
                
            /* Error while reading data from source cluster.
                Leave block as INCONSISTENT and move on to next block */
            /** @remarks Implements DFEE12004 */
            case FEE_JOB_INT_SWAP_DATA_WRITE:
                Fee_JobResult = Fee_JobIntSwapDataWrite((boolean) FALSE );
                break;            
          /* for all the following cases based on the Fee module status error notification will
                                be called */
            case FEE_JOB_WRITE:
            case FEE_JOB_WRITE_DATA:                       
            case FEE_JOB_WRITE_UNALIGNED_DATA:
            case FEE_JOB_ERASE_IMMEDIATE:
            case FEE_JOB_ERASE_IMMEDIATE_DONE:
            case FEE_JOB_WRITE_VALIDATE:
            case FEE_JOB_WRITE_DONE:
            {
              VAR( uint8, AUTOMATIC ) clrGrpIndex = Fee_BlockConfig[Fee_JobBlockIndex].clrGrp;
              /** @note Violates MISRA-C:2004 Required Rule 15.2, An unconditional break statement shall 
                   terminate every non-empty switch clause.: See @ref Fee_c_REF_9 */
              /* Something wrong in FlashMemory (cluster swap occurs to next write) */
               Fee_ClrGrpInfo[clrGrpIndex].dataAddrIt = Fee_ClrGrpInfo[clrGrpIndex].hdrAddrIt + (2U * FEE_BLOCK_OVERHEAD );
            }
            case FEE_JOB_READ:
            case FEE_JOB_INVAL_BLOCK:
            case FEE_JOB_INVAL_BLOCK_DONE:
            case FEE_JOB_INT_SCAN:
            case FEE_JOB_INT_SCAN_CLR:
            case FEE_JOB_INT_SCAN_CLR_FMT:
            case FEE_JOB_INT_SCAN_CLR_FMT_DONE:
            case FEE_JOB_INT_SWAP_BLOCK:
            case FEE_JOB_INT_SWAP_CLR_FMT:
            case FEE_JOB_INT_SWAP_DATA_READ:
            case FEE_JOB_INT_SWAP_CLR_VLD_DONE:
            case FEE_JOB_DONE:
            default:
                /** @remarks Implements DFEE12005 */
                Fee_JobResult = Fls_GetJobResult();
        
                /** @remarks Implements DFEE12006 */
                if( MEMIF_BUSY_INTERNAL == Fee_ModuleStatus )
                {
                    /* No notifications from internal jobs */
                    Fee_ModuleStatus = MEMIF_IDLE;
                }
                else
                {
                    Fee_ModuleStatus = MEMIF_IDLE;
                    
                    /* Call job error notification function */
                    FEE_NVM_JOB_ERROR_NOTIFICATION
                }
                break;
        }
    }
}

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
FUNC( void, FEE_CODE ) Fee_MainFunction( void )
{
/**    @remarks Implements DFEE13001 */
#if( FEE_DEV_ERROR_DETECT == STD_ON )
    if( MEMIF_UNINIT == Fee_ModuleStatus )
    {
        Det_ReportError( FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_MAINFUNCTION_ID, 
            FEE_E_UNINIT );
    }
    else
    { 
#endif    /* FEE_DEV_ERROR_DETECT == STD_ON */

        /**    @remarks Implements DFEE13002 */
        if( MEMIF_JOB_PENDING == Fee_JobResult )
        {
        
            /**    @remarks Implements DFEE13003 */
            switch( Fee_Job )
            {
              /* for all the following jobs subsequent jobs will be called in Fee job schedule
                                          function based on Job */
                case FEE_JOB_INT_SCAN:
                case FEE_JOB_READ:
                case FEE_JOB_WRITE:
                case FEE_JOB_INVAL_BLOCK:
                case FEE_JOB_ERASE_IMMEDIATE:
                    Fee_JobResult = Fee_JobSchedule();
                    break;
               /* for all the following jobs job end or job error notification will be called
                                             based on the job result  */
                case FEE_JOB_WRITE_DATA:
                case FEE_JOB_WRITE_UNALIGNED_DATA:
                case FEE_JOB_WRITE_VALIDATE:
                case FEE_JOB_WRITE_DONE:
                case FEE_JOB_INVAL_BLOCK_DONE:
                case FEE_JOB_ERASE_IMMEDIATE_DONE:
                case FEE_JOB_INT_SCAN_CLR_HDR_PARSE:
                case FEE_JOB_INT_SCAN_CLR:
                case FEE_JOB_INT_SCAN_CLR_FMT:
                case FEE_JOB_INT_SCAN_CLR_FMT_DONE:
                case FEE_JOB_INT_SCAN_BLOCK_HDR_PARSE:
                case FEE_JOB_INT_SWAP_BLOCK:
                case FEE_JOB_INT_SWAP_CLR_FMT:
                case FEE_JOB_INT_SWAP_DATA_READ:
                case FEE_JOB_INT_SWAP_DATA_WRITE:
                case FEE_JOB_INT_SWAP_CLR_VLD_DONE:
                case FEE_JOB_DONE:
                default:
                    /* Internal or subsequent job */
                    break;
            }
                    
            /**    @remarks Implements DFEE13004 */
            if( MEMIF_JOB_PENDING == Fee_JobResult )
            {
                /* Nothing to do */
            }
            /**    @remarks Implements DFEE13005 */
            else if( MEMIF_JOB_OK == Fee_JobResult )
            {
                /**    @remarks Implements DFEE13006 */
                if( MEMIF_BUSY_INTERNAL == Fee_ModuleStatus )
                {
                    /* no notifications from internal jobs */
                    Fee_ModuleStatus = MEMIF_IDLE;
                }
                else
                {
                    Fee_ModuleStatus = MEMIF_IDLE;

                    /* Call job end notification function */
                    FEE_NVM_JOB_END_NOTIFICATION
                }
            }
            else
            {
                /**    @remarks Implements DFEE13007 */
                if( MEMIF_BUSY_INTERNAL == Fee_ModuleStatus )
                {
                    /* no notifications from internal jobs */
                    Fee_ModuleStatus = MEMIF_IDLE;
                }
                else
                {
                    Fee_ModuleStatus = MEMIF_IDLE;
                    
                    /* Call job error notification function */
                    FEE_NVM_JOB_ERROR_NOTIFICATION
                }
            }
        }
#if( FEE_DEV_ERROR_DETECT == STD_ON )
    }
#endif    /* FEE_DEV_ERROR_DETECT == STD_ON */
}

#define FEE_STOP_SEC_CODE
/** @note Violates MISRA-C:2004 Advisory Rule 19.1,only preprocessor statements and comments before 
          '#include'. See @ref Fee_c_REF_2 */
/** @note Violates MISRA-C:2004 Required Rule 19.15, Repeatedly included but does not have a standard 
          include guard. See @ref Fee_c_REF_3 */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

/** @}*/
