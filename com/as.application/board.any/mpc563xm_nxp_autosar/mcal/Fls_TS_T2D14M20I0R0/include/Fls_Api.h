/**
    @file    Fls_Api.h
    @version 2.0.7.0

    @brief   AUTOSAR Fls - AUTOSAR Module Flash Driver
    @details  All external API declarations of Flash driver
    
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
    
    @addtogroup Fls
    @{
*/
/*==================================================================================================
==================================================================================================*/
/*==================================================================================================*/
/**
@page misra_violations MISRA-C:2004 violations

 @section Fls_Api_h_REF_1
Violates MISRA-C: 2004 Advisory Rule 19.15, Repeated include file, Could not be fixed because Fls_Cfg.h
included in Fls.h as per AUTOSAR FLS107

@section Fls_Api_h_REF_2
Violates MISRA-C: 2004 Advisory Rule 19.15, Repeatedly included but does not have a standard include
guard because of Autosar requirement MEMMAP003 of memory  mapping
 
@section Fls_Api_h_REF_3
Violates MISRA-C: 2004 Advisory Rule 20.2, Re-use of C90 reserved identifier.
This violation is due to the use of "_" which is required as per Autosar

*/
/*==================================================================================================*/

#ifndef _FLS_API_H_
/** @note Violates MISRA-C:2004 Advisory Rule 20.2, Re-use of C90 reserved identifier: 
See @ref Fls_Api_h_REF_3 */
#define _FLS_API_H_

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/** @note Violates MISRA-C:2004 Advisory Rule 19.15, Repeated include: 
See @ref Fls_Api_h_REF_1 */
#include "Fls_Cfg.h"
#include "Fls_Version.h"
#include "MemIf_Types.h"

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#ifdef CHECK_AUTOSAR_VERSION
    #if (FLS_AR_MAJOR_VERSION != 3U)
    #error Wrong FLS_AR_MAJOR_VERSION (Expected version: 3)
    #endif

    /* AUTOSAR minor version check */
    #if (FLS_AR_MINOR_VERSION != 0U)
    #error Wrong FLS_AR_MINOR_VERSION (Expected version: 0)
    #endif

    /* AUTOSAR patch version check */
    #if (FLS_AR_PATCH_VERSION != 0U)
    #error Wrong FLS_AR_PATCH_VERSION (Expected version: 0)
    #endif
#endif

/* Software major version check */
#if (FLS_SW_MAJOR_VERSION != 2U)
#error Wrong FLS_SW_MAJOR_VERSION wrong (Expected version: 2)
#endif

/* Software minor version check */
#if (FLS_SW_MINOR_VERSION != 0U)
#error Wrong FLS_SW_MINOR_VERSION (Expected version: 0)
#endif

/* Software patch version check */
#if (FLS_SW_PATCH_VERSION != 0U)
#error Wrong FLS_SW_PATCH_VERSION (Expected version: 0)
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/* AUTOSAR module vendor identification */
#define FLS_VENDOR_ID            43U

/* AUTOSAR module identification */
#define FLS_MODULE_ID            92U

/* AUTOSAR module instance identification */
#define FLS_INSTANCE_ID            0U

/* macro used in CER identification */
#define  FLS_SID_SETCLOCKMODE  0x11U  
#define  FLS_E_DEFAULT         0x12U


/** 
    @brief Development error codes (passed to DET)
    @remarks Implements DFLS21306
*/
/* API service called with wrong parameter */
#define FLS_E_PARAM_CONFIG            0x01U
#define FLS_E_PARAM_ADDRESS            0x02U
#define FLS_E_PARAM_LENGTH            0x03U
#define FLS_E_PARAM_DATA            0x04U
/* API service called without module initialization */
#define FLS_E_UNINIT                0x05U
/* API service called while driver still busy */
#define FLS_E_BUSY                    0x06U
/* Erase verification (blank check) failed */
#define FLS_E_VERIFY_ERASE_FAILED    0x07U
/* Write verification (compare) failed */
#define FLS_E_VERIFY_WRITE_FAILED    0x08U
/* NULL_PTR passed */
#define FLS_E_PARAM_POINTER            0x09U

/** 
    @brief All service IDs (passed to DET)
    @remarks Implements DFLS21307
*/
#define FLS_INIT_ID                0x00U
#define FLS_ERASE_ID            0x01U
#define FLS_WRITE_ID            0x02U
#define FLS_CANCEL_ID            0x03U
#define FLS_GETSTATUS_ID        0x04U
#define FLS_GETJOBRESULT_ID        0x05U
#define FLS_MAINFUNCTION_ID        0x06U
#define FLS_READ_ID                0x07U
#define FLS_COMPARE_ID            0x08U
#define FLS_SETMODE_ID            0x09U
#define FLS_GETVERSIONINFO_ID    0x10U

/**
    @brief All sector flags
    @remarks Implements DFLS21308
*/
#define FLS_SECTOR_ERASE_ASYNCH    0x01U
#define FLS_PAGE_WRITE_ASYNCH    0x02U

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#define FLS_START_SEC_CODE
/** @note Violates MISRA-C:2004 Advisory Rule 19.15, Repeated include: 
See @ref Fls_Api_h_REF_2 */
#include "MemMap.h"

extern FUNC( void, FLS_CODE ) Fls_Init(
    P2CONST( Fls_ConfigType, AUTOMATIC, FLS_APPL_CONST ) ConfigPtr );

extern FUNC( Std_ReturnType, FLS_CODE ) Fls_Write(
    VAR( Fls_AddressType, FLS_VAR) TargetAddress, 
    P2CONST( uint8, AUTOMATIC, FLS_APPL_CONST ) SourceAddressPtr,
    VAR( Fls_LengthType, FLS_VAR) Length );

extern FUNC( Std_ReturnType, FLS_CODE ) Fls_Erase( 
    VAR( Fls_AddressType, FLS_VAR) TargetAddress,
    VAR( Fls_LengthType, FLS_VAR) Length );

#if( FLS_CANCEL_API == STD_ON )
extern FUNC( void, FLS_CODE ) Fls_Cancel( void );
#endif    /* FLS_CANCEL_API == STD_ON */

#if( FLS_GET_STATUS_API == STD_ON )
extern FUNC( MemIf_StatusType, FLS_CODE ) Fls_GetStatus( void );
#endif    /* FLS_GET_STATUS_API == STD_ON */

#if( FLS_GET_JOB_RESULT_API == STD_ON )
extern FUNC( MemIf_JobResultType, FLS_CODE ) Fls_GetJobResult( void );
#endif    /* FLS_GET_JOB_RESULT_API == STD_ON */

extern FUNC( Std_ReturnType, FLS_CODE ) Fls_Read( 
    VAR( Fls_AddressType, FLS_VAR) SourceAddress, 
    P2VAR( uint8, AUTOMATIC, FLS_APPL_CONST ) TargetAddressPtr,    
    VAR( Fls_LengthType, FLS_VAR) Length );

#if( FLS_COMPARE_API == STD_ON )
extern FUNC( Std_ReturnType, FLS_CODE ) Fls_Compare(
    VAR( Fls_AddressType, FLS_VAR) SourceAddress, 
    P2CONST( uint8, AUTOMATIC, FLS_APPL_CONST ) TargetAddressPtr, 
    VAR( Fls_LengthType, FLS_VAR) Length );
#endif /* FLS_COMPARE_API == STD_ON */

#if( FLS_SET_MODE_API == STD_ON )
extern FUNC( void, FLS_CODE ) Fls_SetMode (
    VAR( MemIf_ModeType, FLS_VAR ) Mode );
#endif /* FLS_SET_MODE_API == STD_ON */

#if( FLS_VERSION_INFO_API == STD_ON )
extern FUNC( void, FLS_CODE ) Fls_GetVersionInfo( 
    P2VAR( Std_VersionInfoType, AUTOMATIC, FLS_APPL_DATA ) VersionInfo );
#endif /* FLS_VERSION_INFO_API == STD_ON */

extern FUNC( void, FLS_CODE ) Fls_MainFunction( void );

#if( FLS_DSI_HANDLER_API == STD_ON )
extern FUNC( Fls_CompHandlerReturnType, FLS_CODE ) Fls_DsiHandler(
    P2CONST( Fls_ExceptionDetailsType, AUTOMATIC, FLS_APPL_DATA ) ExceptionDetailsPtr );
extern FUNC( Fls_CompHandlerReturnType, FLS_CODE ) Fls_MciHandler(
    P2CONST( Fls_ExceptionDetailsType, AUTOMATIC, FLS_APPL_DATA ) ExceptionDetailsPtr );
#endif /* FLS_DSI_HANDLER_API == STD_ON */

#define FLS_STOP_SEC_CODE
/** @note Violates MISRA-C:2004 Advisory Rule 19.15, Repeated include: 
See @ref Fls_Api_h_REF_2 */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* _FLS_API_H_ */

/** @}*/
