/**
    @file    Fls_Types.h
    @version 2.0.11.0

    @brief   AUTOSAR Fls - AUTOSAR Module Flash Driver
    @details Definitions of all Flash driver exported types
    
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

#ifndef FLS_TYPES_H
#define FLS_TYPES_H

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

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/
/* define the return values a module specific handler function could return */
#define FLS_UNHANDLED  0u  /* module doesn't feel responsible (e.g. address does not belong to 
                              its current job)      */

#define FLS_HANDLED_RETRY       1u  /* module feels responsible, but wants to repeat the 
                                     * causing instruction. Maybe: it still uses information in MCM 
                                     * or ECSM module, but they are outdated (e.g. due to an 
                                     * erroneous DMA transfer in the meantime)                    */

#define FLS_HANDLED_SKIP        2u  /* module feels responsible (usually it just would set some 
                                       internal flag?) processing may continue, skipping the 
                                       causing instruction                                        */


#define FLS_HANDLED_STOP        3u  /* module  feels responsible, but the only reaction is to stop 
                                       the system (e.g.: try to shut-down in a quite safe way)    */
/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/** 
    @brief Enumeration of physical flash sectors
    @remarks Implements DFLS31303
*/ 
typedef enum
{
    FLS_CODE_ARRAY_0_A_L00 = 0,
    FLS_CODE_ARRAY_0_A_L01,
    FLS_CODE_ARRAY_0_A_L02,
    FLS_CODE_ARRAY_0_A_L03,
    FLS_CODE_ARRAY_0_A_L04,
    FLS_CODE_ARRAY_0_A_L05,
    FLS_CODE_ARRAY_0_A_L06,
    FLS_CODE_ARRAY_0_A_L07,
    FLS_CODE_ARRAY_0_A_M00,
    FLS_CODE_ARRAY_0_A_M01,
    FLS_CODE_ARRAY_1_B_H00,
    FLS_CODE_ARRAY_1_B_H01,
    FLS_CODE_ARRAY_1_B_H02,
    FLS_CODE_ARRAY_1_B_H03,
    FLS_CODE_ARRAY_1_C_H04,
    FLS_CODE_ARRAY_1_C_H05,
    FLS_CODE_ARRAY_1_C_H06,
    FLS_CODE_ARRAY_1_C_H07,
    FLS_CODE_ARRAY_1_C_TEST,
    FLS_CODE_ARRAY_1_B_TEST,
    FLS_CODE_ARRAY_0_A_TEST,
    FLS_CODE_ARRAY_0_A_SHADOW
}
Fls_LLD_PhysicalSectorType;

/** 
    @brief Enumeration of physical flash sectors page size
    @remarks Implements ...
*/ 
typedef enum
{
    FLS_PAGE_SIZE_04 = 0x4U,
    FLS_PAGE_SIZE_08 = 0x8U
}
Fls_LLD_PageSizeType;

/** 
    @brief Define pointer type of erase access code function
    @remarks Implements DFLS31301
*/
typedef P2FUNC( void, FLS_CODE, Fls_LLD_AcErasePtrType )
    (P2VAR(volatile uint32, AUTOMATIC, FLS_CODE) regBasePtr, P2FUNC(void, FLS_CODE, CallBack), P2VAR(volatile uint32, AUTOMATIC, FLS_CODE) timerCounterAC);   
  
/** 
    @brief Define pointer type of write access code function
    @remarks Implements DFLS31302
*/
typedef P2FUNC( void, FLS_CODE, Fls_LLD_AcWritePtrType )
    (P2VAR(volatile uint32, AUTOMATIC, FLS_CODE) regBasePtr, P2FUNC(void, FLS_CODE, CallBack), P2VAR(volatile uint32, AUTOMATIC, FLS_CODE) timerCounterAC);


/**
    *@brief Address offset from the configured flash base address to access
    *a certain flash memory area 
    *@api
    *@remarks Implements DFLS21300
*/    
typedef uint32 Fls_AddressType;

/**
 * @brief Number of bytes to read/write/erase/compare 
 * @api
 * @remarks Implements DFLS21301
*/
typedef uint32 Fls_LengthType;

/**
 * @brief Number of configured sectors
 * @api
 * @remarks Implements DFLS21302
*/
typedef uint32 Fls_SectorCountType;

/**
 * @brief Pointer type of Fls_AC_Callback function
 * @api 
 * @remarks Implements 
*/
typedef P2FUNC( void, FLS_CODE, Fls_ACCallbackPtrType )  ( void );


/**
 * @brief Pointer type of Fls_JobEndNotification function
 * @api 
 * @remarks Implements DFLS21303
*/
typedef P2FUNC( void, FLS_CODE, Fls_JobEndNotificationPtrType )  ( void );

/**
 * @brief Pointer type of Fls_JobErrorNotification function
 * @api 
 * @remarks Implements DFLS21304
*/
typedef P2FUNC( void, FLS_CODE, Fls_JobErrorNotificationPtrType )  ( void );  

/**
 * @brief Fls module initialization data structure
 * @api
 * @remarks Implements DFLS21305
*/
typedef struct 
{
    /** 
    * @brief pointer to erase access code function in RAM or ROM 
    */
    Fls_LLD_AcErasePtrType acErasePtr; 
    /** 
    * @brief pointer to write access code function in RAM or ROM 
    */
    Fls_LLD_AcWritePtrType acWritePtr;
    /** 
    * @brief pointer to ac callback function 
    */  
    Fls_ACCallbackPtrType acCallBackPtr;
    /** 
    * @brief pointer to job end notification function 
    */
    Fls_JobEndNotificationPtrType jobEndNotificationPtr; 
    /** 
    * @brief pointer to job error notification function 
    */
    Fls_JobErrorNotificationPtrType jobErrorNotificationPtr; 
    /** 
    * @brief max number of bytes to read in one cycle of Fls_MainFunction (fast mode) 
    */
    Fls_LengthType maxReadFastMode; 
    /** 
    * @brief max number of bytes to read in one cycle of  Fls_MainFunction (normal mode) 
    */
    Fls_LengthType maxReadNormalMode; 
    /** 
    * @brief max number of bytes to write in one cycle of Fls_MainFunction (fast mode) 
    */
    Fls_LengthType maxWriteFastMode; 
    /** 
    * @brief max number of bytes to write in one cycle of  Fls_MainFunction (normal mode) 
    */
    Fls_LengthType maxWriteNormalMode; 
    /** 
    * @brief number of configured logical sectors 
    */
    Fls_SectorCountType sectorCount;
    /** 
    * @brief pointer to array containing last logical address of each configured sector 
    */
    CONSTP2CONST( Fls_AddressType, AUTOMATIC, FLS_APPL_CONST ) sectorEndAddr; 
    /**
    * @brief pointer to array containing physical sector ID of each configured sector 
    */
    CONSTP2CONST( Fls_LLD_PhysicalSectorType, AUTOMATIC, FLS_APPL_CONST ) physicalSector; 
    /**
    * @brief pointer to array containing flags set of each configured sector 
    */
    CONSTP2CONST( uint8, AUTOMATIC, FLS_APPL_CONST ) sectorFlags; 
    /**
    * @brief pointer to array containing page size of each configured sector 
    */
    CONSTP2CONST( Fls_LengthType, AUTOMATIC, FLS_APPL_CONST ) sectorPageSize; 
    /**
    * @brief pointer to array containing Unlock information of each configured sector 
    */
    CONSTP2CONST( uint8, AUTOMATIC, FLS_APPL_CONST ) sectorUnlock; 

} Fls_ConfigType;

/* instead of an enum-type, we use a uint8.           *
 * It represents one of the FLS_HANDLED_xxx constants */
typedef uint8_least Fls_CompHandlerReturnType;

typedef const uint8 * Fls_InstructionAddressType;
typedef const void * Fls_DataAddressType;

typedef struct
{
    Fls_InstructionAddressType instruction_pt;
    Fls_DataAddressType        data_pt;
    uint32                     syndrome_u32;
} Fls_ExceptionDetailsType;

typedef const Fls_ExceptionDetailsType *ExceptionDetailsPtrType;

#ifdef __cplusplus
}
#endif

#endif /* _FLS_TYPES_H_ */

/** @}*/
