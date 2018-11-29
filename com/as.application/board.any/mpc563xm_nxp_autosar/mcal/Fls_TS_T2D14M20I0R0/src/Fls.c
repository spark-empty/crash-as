/**
    @file    Fls.c
    @version 2.0.19.0

    @brief   AUTOSAR Fls - AUTOSAR Module Flash Driver
    @details Flash driver source code

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

@section Fls_c_REF_1
Violates MISRA-C: 2004 Advisory Rule 19.1, only preprocessor statements and comments
before '#include'
Violates MISRA-C: 2004 Advisory Rule 19.15, Repeatedly included but does not have a standard include
guard Due to AUTOSAR requirement MEMMAP003

@section Fls_c_REF_2
Violates MISRA-C: 2004 Advisory Rule 10.1, Implicit conversion changes signedness.
Caused by type signedness mismatch between the TRUE and FALSE macros which are defined as signed
integers (PLATFORM056) and the boolean data type (PLATFORM027) which is defined as uint8.


@section Fls_c_REF_3
Violates MISRA-C: 2004 Advisory Rule 11.4, Cast from pointer to pointer.
This violation is caused by casting pointer to the erase and write access functions to pointer to
uint32 which is necessary to implement the access code (un)loader according to the FLS140 and FLS141
AUTOSAR requirements.


@section Fls_c_REF_4
Violates MISRA-C: 2004 Advisory Rule 11.4, Cast from pointer to pointer.
This violation is due to casting the unsigned character pointer to unsigned long pointer and access
these addresses for updating contents in that address.

@section Fls_c_REF_5
Violates MISRA-C: 2004 Advisory Rule 11.4, Cast from pointer to pointer.
This violation is due to casting the structure pointer to unsigned long pointer


@section Fls_c_REF_6
Violates MISRA-C: 2004 Advisory Rule 11.3, Cast from unsigned long to pointer.
This violation is due to casting the unsigned long to pointer and access these addresses for
updating contents in that address.


@section Fls_c_REF_7
Violates MISRA-C: 2004 Advisory Rule 11.3, Cast from pointer to unsigned long.
This violation is due to casting the pointer to unsigned long and access these addresses for
updating contents in that address.


@section Fls_c_REF_8
Violates MISRA-C: 2004 Advisory Rule 11.3, Cast from int to pointer.
This violation is due to casting the int to pointer and access these addresses for updating contents
in that address.


@section Fls_c_REF_9
Violates MISRA-C: 2004 Advisory Rule 12.4, Side effects on right hand of logical operator.
'||' or '&&'. This violation is because of complex statement


@section Fls_c_REF_10
Violates MISRA-C: 2004 Advisory Rule 1.2, Both sides have side effects.
This violation is because of complex statement


@section Fls_c_REF_11
Violates MISRA-C: 2004 Advisory Rule 14.7, Return statement before end of function.
This violation is not fixed since if hardware error is detected it should return from the function


@section Fls_c_REF_12
Violates MISRA-C: 2004 Advisory Rule 14.7, Return statement before end of function.
Return from function as soon as the read/write/erase/operation finished


@section Fls_c_REF_13
Violates MISRA-C: 2004 Advisory Rule 12.6, The operands of logical operators (&&, || and !) should
be effectively Boolean. Booleans operands are not used for logical operators '&&', '||' and '!'


@section Fls_c_REF_14
Violates MISRA-C: 2004 Advisory Rule 11.1, Conversions shall not be performed between a pointer to a
function and any type other than an integral type. This rule can not be avoided because it appears
when addressing memory mapped registers or other hardware specific feature.


@section Fls_c_REF_15
Violates MISRA-C: 2004 Advisory Rule 17.4, Array indexing shall be the only allowed form of pointer
arithmetic.This violation is due to the use of pointer arithmatic, which is used for the speed
optimization, the indexing of the pointer is taken care and hence the unintended  memory location
will not be accessed.


@section Fls_c_REF_16
Violates MISRA-C: 2004 Advisory Rule 10.6, A "U" suffix shall be applied to all constants of
unsigned type. This is not an issue, it doesnot affects the functionality .


@section Fls_c_REF_17
Violates MISRA-C: 2004 Advisory Rule 11.5, A cast shall not be performed that removes any const or
volatile qualification from the type addressed by a pointer.This has taken care in the driver


@section Fls_c_REF_18
Violates MISRA-C: 2004 Advisory Rule 16.4, The identifiers used in the declaration and definition
of a function shall be identical.This is not an issue, it doesnot affects the functionality

@section Fls_c_REF_19
Violates MISRA-C: 2004 Advisory Rule 8.10, This is not an issue, the function is an API function
requested by Autosar .

*/
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

#include "Fls.h"
#include "Fls_InternalTypes.h"
#include "Dem.h"

#if( FLS_DEV_ERROR_DETECT == STD_ON )
#include "Det.h"
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */

#include "SchM_Fls.h"
#include "Mcal.h"
#include "Reg_FlashMem.h"


/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/**
    @brief fill pattern used to clear write and erase access code in RAM
*/
#if( FLS_AC_LOAD_ON_JOB_START == STD_ON )
#define FLS_AC_UNLOAD_PATTERN 0xffffffffU
#endif

/**
    @brief Calculate total flash size in bytes
*/
#if( FLS_DEV_ERROR_DETECT == STD_ON )
#define FLS_TOTAL_SIZE (Fls_ConfigPtr->sectorEndAddr[Fls_ConfigPtr->sectorCount - 1U] + 1U)
#endif

/** @remarks Covers BSW00374, BSW00318 */
#define FLS_VENDOR_ID_C         43U
#define FLS_AR_MAJOR_VERSION_C  3U
#define FLS_AR_MINOR_VERSION_C  0U
#define FLS_AR_PATCH_VERSION_C  0U
#define FLS_SW_MAJOR_VERSION_C  2U
#define FLS_SW_MINOR_VERSION_C  0U
#define FLS_SW_PATCH_VERSION_C  0U

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and Fls header file are of the same vendor */
#if (FLS_VENDOR_ID_C != FLS_VENDOR_ID)
    #error "Fls.c and Fls.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Fls header file are of the same Autosar version */
    #if ((FLS_AR_MAJOR_VERSION_C != FLS_AR_MAJOR_VERSION) || \
         (FLS_AR_MINOR_VERSION_C != FLS_AR_MINOR_VERSION) || \
         (FLS_AR_PATCH_VERSION_C != FLS_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of Fls.c and Fls.h are different"
    #endif
#endif
/* Check if source file and Fls header file are of the same Software version */
#if ((FLS_SW_MAJOR_VERSION_C != FLS_SW_MAJOR_VERSION) || \
     (FLS_SW_MINOR_VERSION_C != FLS_SW_MINOR_VERSION) || \
     (FLS_SW_PATCH_VERSION_C != FLS_SW_PATCH_VERSION))
    #error "Software Version Numbers of Fls.c and Fls.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Dem header file are of the same version */
    #if ((FLS_AR_MAJOR_VERSION_C != DEM_AR_MAJOR_VERSION) || \
         (FLS_AR_MINOR_VERSION_C != DEM_AR_MINOR_VERSION))
        #error "AutoSar Version Numbers of Fls.c and Dem.h are different"
    #endif
#endif

/* Check if source file and DET header file are of the same version */
#if (FLS_DEV_ERROR_DETECT == STD_ON)
    #ifdef CHECK_AUTOSAR_VERSION
        #if ((FLS_AR_MAJOR_VERSION_C != DET_AR_MAJOR_VERSION) || \
             (FLS_AR_MINOR_VERSION_C != DET_AR_MINOR_VERSION))
            #error "AutoSar Version Numbers of Fls.c and Det.h are different"
        #endif
    #endif
#endif

/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/

#define FLS_START_SEC_CONST_UNSPECIFIED
/** @note Violates MISRA-C:2004 Advisory Rule 19.15, Repeatedly included: See @ref Fls_c_REF_1 */
#include "MemMap.h"


#define FLS_LLD_FLASH_SECTOR_COUNT 22U

/**
    @brief FLASH physical sectorization description
*/
static CONST(Fls_LLD_SectorInfoType, FLS_CONST) flsLLDSectorList0[FLS_LLD_FLASH_SECTOR_COUNT]=
{
    {    /* FLS_CODE_ARRAY_0_A_L00 */
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 6 above */
        (volatile uint32*)0x00000000,
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 6 above */
        (volatile uint32*)(FLASHMEM0_ARRAY_0_A_BASEADDR),
        LMS_LSL0,
        LML_LLK0,
        FLASHMEM_LMS,
        FLASHMEM_LML,
        FLASHMEM_SLL,
        FLASHMEM_PFCR0,
        (PFCR0_B02_P0_BFE),
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        FALSE,
        (volatile uint32*)0,
        0U,
        (volatile uint32*)0
    },
    {    /* FLS_CODE_ARRAY_0_A_L01 */
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 8 above */
        (volatile uint32*)0x00004000,
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 6 above */
        (volatile uint32*)(FLASHMEM0_ARRAY_0_A_BASEADDR),
        LMS_LSL1,
        LML_LLK1,
        FLASHMEM_LMS,
        FLASHMEM_LML,
        FLASHMEM_SLL,
        FLASHMEM_PFCR0,
        (PFCR0_B02_P0_BFE),
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        FALSE,
        (volatile uint32*)0,
        0U,
        (volatile uint32*)0        
    },
    {    /* FLS_CODE_ARRAY_0_A_L02 */
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 8 above */
        (volatile uint32*)0x00008000,
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 6 above */
        (volatile uint32*)(FLASHMEM0_ARRAY_0_A_BASEADDR),
        LMS_LSL2,
        LML_LLK2,
        FLASHMEM_LMS,
        FLASHMEM_LML,
        FLASHMEM_SLL,
        FLASHMEM_PFCR0,
        (PFCR0_B02_P0_BFE),
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        FALSE,
        (volatile uint32*)0,
        0U,
        (volatile uint32*)0
    },
    {    /* FLS_CODE_ARRAY_0_A_L03 */
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 8 above */
        (volatile uint32*)0x00010000,
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 6 above */
        (volatile uint32*)(FLASHMEM0_ARRAY_0_A_BASEADDR),
        LMS_LSL3,
        LML_LLK3,
        FLASHMEM_LMS,
        FLASHMEM_LML,
        FLASHMEM_SLL,
        FLASHMEM_PFCR0,
        (PFCR0_B02_P0_BFE),
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        FALSE,
        (volatile uint32*)0,
        0U,
        (volatile uint32*)0
    },
    {    /* FLS_CODE_ARRAY_0_A_L04 */
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 8 above */
        (volatile uint32*)0x00018000,
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 6 above */
        (volatile uint32*)(FLASHMEM0_ARRAY_0_A_BASEADDR),
        LMS_LSL4,
        LML_LLK4,
        FLASHMEM_LMS,
        FLASHMEM_LML,
        FLASHMEM_SLL,
        FLASHMEM_PFCR0,
        (PFCR0_B02_P0_BFE),
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        FALSE,
        (volatile uint32*)0,
        0U,
        (volatile uint32*)0
    },
    {    /* FLS_CODE_ARRAY_0_A_L05 */
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 8 above */
        (volatile uint32*)0x0001C000,
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 6 above */
        (volatile uint32*)(FLASHMEM0_ARRAY_0_A_BASEADDR),
        LMS_LSL5,
        LML_LLK5,
        FLASHMEM_LMS,
        FLASHMEM_LML,
        FLASHMEM_SLL,
        FLASHMEM_PFCR0,
        (PFCR0_B02_P0_BFE),
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        FALSE,
        (volatile uint32*)0,
        0U,
        (volatile uint32*)0
    },
    {    /* FLS_CODE_ARRAY_0_A_L06 */
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 8 above */
        (volatile uint32*)0x00020000,
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 6 above */
        (volatile uint32*)(FLASHMEM0_ARRAY_0_A_BASEADDR),
        LMS_LSL6,
        LML_LLK6,
        FLASHMEM_LMS,
        FLASHMEM_LML,
        FLASHMEM_SLL,
        FLASHMEM_PFCR0,
        (PFCR0_B02_P0_BFE),
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        FALSE,
        (volatile uint32*)0,
        0U,
        (volatile uint32*)0
    },
    {    /* FLS_CODE_ARRAY_0_A_L07 */
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 8 above */
        (volatile uint32*)0x00030000,
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 6 above */
        (volatile uint32*)(FLASHMEM0_ARRAY_0_A_BASEADDR),
        LMS_LSL7,
        LML_LLK7,
        FLASHMEM_LMS,
        FLASHMEM_LML,
        FLASHMEM_SLL,
        FLASHMEM_PFCR0,
        (PFCR0_B02_P0_BFE),
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        FALSE,
        (volatile uint32*)0,
        0U,
        (volatile uint32*)0
    },
    {    /* FLS_CODE_ARRAY_0_A_M00 */
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 8 above */
        (volatile uint32*)0x00040000,
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 6 above */
        (volatile uint32*)(FLASHMEM0_ARRAY_0_A_BASEADDR),
        LMS_MSL0,
        LML_MLK0,
        FLASHMEM_LMS,
        FLASHMEM_LML,
        FLASHMEM_SLL,
        FLASHMEM_PFCR0,
        (PFCR0_B02_P0_BFE),
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        FALSE,
        (volatile uint32*)0,
        0U,
        (volatile uint32*)0
    },
    {    /* FLS_CODE_ARRAY_0_A_M01 */
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 8 above */
        (volatile uint32*)0x00060000,
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 6 above */
        (volatile uint32*)(FLASHMEM0_ARRAY_0_A_BASEADDR),
        LMS_MSL1,
        LML_MLK1,
        FLASHMEM_LMS,
        FLASHMEM_LML,
        FLASHMEM_SLL,
        FLASHMEM_PFCR0,
        (PFCR0_B02_P0_BFE),
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        FALSE,
        (volatile uint32*)0,
        0U,
        (volatile uint32*)0
    },
    {    /* FLS_CODE_ARRAY_1_B_H00 */
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 8 above */
        (volatile uint32*)0x00080000,
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 6 above */
        (volatile uint32*)(FLASHMEM0_ARRAY_1_B_BASEADDR),
        HBS_HSL0,
        HBL_HLK0,
        FLASHMEM_HBS,
        FLASHMEM_HBL,
        FLASHMEM_HBL,
        FLASHMEM_PFCR0,
        (PFCR0_B02_P0_BFE),
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        FALSE,
        (volatile uint32*)0,
        0U,
        (volatile uint32*)0
    },
    {    /* FLS_CODE_ARRAY_1_B_H01 */
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 8 above */
        (volatile uint32*)0x000A0000,
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 6 above */
        (volatile uint32*)(FLASHMEM0_ARRAY_1_B_BASEADDR),
        HBS_HSL1,
        HBL_HLK1,
        FLASHMEM_HBS,
        FLASHMEM_HBL,
        FLASHMEM_HBL,
        FLASHMEM_PFCR0,
        (PFCR0_B02_P0_BFE),
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        FALSE,
        (volatile uint32*)0,
        0U,
        (volatile uint32*)0
    },
    {    /* FLS_CODE_ARRAY_1_B_H02 */
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 8 above */
        (volatile uint32*)0x000C0000,
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 6 above */
        (volatile uint32*)(FLASHMEM0_ARRAY_1_B_BASEADDR),
        HBS_HSL2,
        HBL_HLK2,
        FLASHMEM_HBS,
        FLASHMEM_HBL,
        FLASHMEM_HBL,
        FLASHMEM_PFCR0,
        (PFCR0_B02_P0_BFE),
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        FALSE,
        (volatile uint32*)0,
        0U,
        (volatile uint32*)0
    },
    {    /* FLS_CODE_ARRAY_1_B_H03 */
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 8 above */
        (volatile uint32*)0x000E0000,
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 6 above */
        (volatile uint32*)(FLASHMEM0_ARRAY_1_B_BASEADDR),
        HBS_HSL3,
        HBL_HLK3,
        FLASHMEM_HBS,
        FLASHMEM_HBL,
        FLASHMEM_HBL,
        FLASHMEM_PFCR0,
        (PFCR0_B02_P0_BFE),
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        FALSE,
        (volatile uint32*)0,
        0U,
        (volatile uint32*)0
    },
    {    /* FLS_CODE_ARRAY_1_C_H04 */
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 8 above */
        (volatile uint32*)0x00100000,
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 6 above */
        (volatile uint32*)(FLASHMEM0_ARRAY_1_C_BASEADDR),
        HBS_HSL0,
        HBL_HLK0,
        FLASHMEM_HBS,
        FLASHMEM_HBL,
        FLASHMEM_HBL,
        FLASHMEM_PFCR0,
        (PFCR0_B02_P0_BFE),
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        FALSE,
        (volatile uint32*)0,
        0U,
        (volatile uint32*)0
    },
    {    /* FLS_CODE_ARRAY_1_C_H05 */
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 8 above */
        (volatile uint32*)0x00120000,
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 6 above */
        (volatile uint32*)(FLASHMEM0_ARRAY_1_C_BASEADDR),
        HBS_HSL1,
        HBL_HLK1,
        FLASHMEM_HBS,
        FLASHMEM_HBL,
        FLASHMEM_HBL,
        FLASHMEM_PFCR0,
        (PFCR0_B02_P0_BFE),
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        FALSE,
        (volatile uint32*)0,
        0U,
        (volatile uint32*)0
    },
    {    /* FLS_CODE_ARRAY_1_C_H06 */
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 8 above */
        (volatile uint32*)0x00140000,
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 6 above */
        (volatile uint32*)(FLASHMEM0_ARRAY_1_C_BASEADDR),
        HBS_HSL2,
        HBL_HLK2,
        FLASHMEM_HBS,
        FLASHMEM_HBL,
        FLASHMEM_HBL,
        FLASHMEM_PFCR0,
        (PFCR0_B02_P0_BFE),
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        FALSE,
        (volatile uint32*)0,
        0U,
        (volatile uint32*)0
    },
    {    /* FLS_CODE_ARRAY_1_C_H07 */
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 8 above */
        (volatile uint32*)0x00160000,
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 6 above */
        (volatile uint32*)(FLASHMEM0_ARRAY_1_C_BASEADDR),
        HBS_HSL3,
        HBL_HLK3,
        FLASHMEM_HBS,
        FLASHMEM_HBL,
        FLASHMEM_HBL,
        FLASHMEM_PFCR0,
        (PFCR0_B02_P0_BFE),
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        FALSE,
        (volatile uint32*)0,
        0U,
        (volatile uint32*)0
    },
    {    /* FLS_CODE_ARRAY_1_C_TEST */
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 8 above */
        (volatile uint32*)0x00B7FC00,
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 6 above */
        (volatile uint32*)(FLASHMEM0_ARRAY_1_C_BASEADDR),
        0U,
        LML_TSLK,
        FLASHMEM_LMS,
        FLASHMEM_LML,
        FLASHMEM_SLL,
        FLASHMEM_PFCR0,
        (PFCR0_B02_P0_BFE),
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        FALSE,
        (volatile uint32*)0,
        0U,
        (volatile uint32*)0
    },
    {    /* FLS_CODE_ARRAY_1_B_TEST */
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 8 above */
        (volatile uint32*)0x00BBFC00,
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 6 above */
        (volatile uint32*)(FLASHMEM0_ARRAY_1_B_BASEADDR),
        0U,
        LML_TSLK,
        FLASHMEM_LMS,
        FLASHMEM_LML,
        FLASHMEM_SLL,
        FLASHMEM_PFCR0,
        (PFCR0_B02_P0_BFE),
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        FALSE,
        (volatile uint32*)0,
        0U,
        (volatile uint32*)0
    },    
    {    /* FLS_CODE_ARRAY_0_A_TEST */
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 8 above */
        (volatile uint32*)0x00BFFC00,
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 6 above */
        (volatile uint32*)(FLASHMEM0_ARRAY_0_A_BASEADDR),
        0U,
        LML_TSLK,
        FLASHMEM_LMS,
        FLASHMEM_LML,
        FLASHMEM_SLL,
        FLASHMEM_PFCR0,
        (PFCR0_B02_P0_BFE),
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        FALSE,
        (volatile uint32*)0,
        0U,
        (volatile uint32*)0
    },    
    {    /* FLS_CODE_ARRAY_0_A_SHADOW */
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 8 above */
        (volatile uint32*)0x00FFC000,
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 6 above */
        (volatile uint32*)(FLASHMEM0_ARRAY_0_A_BASEADDR),
        0U,
        LML_TSLK,
        FLASHMEM_LMS, 
        FLASHMEM_LML,
        FLASHMEM_SLL,
        FLASHMEM_PFCR0,
        (PFCR0_B02_P0_BFE),
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        FALSE,
        (volatile uint32*)0,
        0U,
        (volatile uint32*)0
    }
};

#define FLS_LLD_FLASH_ARRAY_COUNT 3U

/**
    @brief FLASH array description
*/
static CONST(Fls_LLD_ArrayInfoType, FLS_CONST) flsLLDArrayList0[FLS_LLD_FLASH_ARRAY_COUNT]=
{
    {    /* FLS_CODE_ARRAY_0_A */
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 6 above */
        (volatile uint32*)(FLASHMEM0_ARRAY_0_A_BASEADDR),
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        FALSE,
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        TRUE
    },
    {    /* FLS_CODE_ARRAY_1_B */
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 6 above */
        (volatile uint32*)(FLASHMEM0_ARRAY_1_B_BASEADDR),
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        FALSE,
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        TRUE
    },
    {    /* FLS_CODE_ARRAY_1_C */
        /* MISRA-C:2004 11.3 VIOLATION: Refer to REF 6 above */
        (volatile uint32*)(FLASHMEM0_ARRAY_1_C_BASEADDR),
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        FALSE,
        /* MISRA-C:2004 10.1 VIOLATION: Refer to REF 2 above */
        TRUE
    }
};

#define FLS_LLD_DATA_BUS_WIDTH_TYPE uint32
#define FLS_LLD_DSI_EXC_SYNDROME 0x00000021UL
#define FLS_LLD_MCI_EXC_SYNDROME 0x00000008UL


#define FLS_STOP_SEC_CONST_UNSPECIFIED
/** @note Violates MISRA-C:2004 Advisory Rule 19.1, 19.15: See @ref Fls_c_REF_1 */
#include "MemMap.h"

/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/

#define FLS_START_SEC_VAR_FAST_UNSPECIFIED
/** @note Violates MISRA-C:2004 Advisory Rule 19.1, 19.15: See @ref Fls_c_REF_1 */
#include "MemMap.h"

/**
    @brief Pointer to current flash module configuration set
    @remarks Implements DFLS20200
*/
STATIC P2CONST(Fls_ConfigType, FLS_PTR_MEMCLASS_CONFIG, FLS_APPL_CONST) Fls_ConfigPtr = NULL_PTR;

/**
    @brief Result of last flash module job
    @remarks Implements DFLS20202
*/
STATIC VAR(MemIf_JobResultType, AUTOMATIC) Fls_JobResult = MEMIF_JOB_OK;

/**
    @brief Maximum number of bytes to read or compare in one cycle of Fls_MainFunction
    @remarks Implements DFLS20203
*/
STATIC VAR(Fls_LengthType, AUTOMATIC) Fls_MaxRead = 0UL;

/**
    @brief Maximum number of bytes to write in one cycle of Fls_MainFunction
    @remarks Implements DFLS20204
*/
STATIC VAR(Fls_LengthType, AUTOMATIC) Fls_MaxWrite = 0UL;

/**
    @brief Type of currently executed job (erase, write, read, or compare)
    @remarks Implements DFLS20205
*/
STATIC VAR(Fls_JobType, AUTOMATIC) Fls_Job = FLS_JOB_ERASE;

/**
    @brief Logical address of data block currently processed by Fls_MainFunction
    @remarks Implements DFLS20206
*/
STATIC VAR(Fls_AddressType, AUTOMATIC) Fls_JobAddrIt = 0UL;

/**
    @brief Last logical address to be processed by a job
    @remarks Implements DFLS20207
*/
STATIC VAR(Fls_AddressType, AUTOMATIC) Fls_JobAddrEnd = 0UL;

/**
    @brief Index of flash sector currently processed by a job
    @details Used by all types of job
    @remarks Implements DFLS20208
*/
STATIC VAR(Fls_SectorIndexType, AUTOMATIC) Fls_JobSectorIt = 0UL;

/**
    @brief Index of last flash sector to be erase by current job
    @details Used only by erase job
    @remarks Implements DFLS20209
*/
STATIC VAR(Fls_SectorIndexType, AUTOMATIC) Fls_JobSectorEnd = 0UL;

/**
    @brief Pointer to current position in source data buffer
    @details Used by both write and compare jobs
    @remarks Implements DFLS20210
*/
STATIC P2CONST( uint8, AUTOMATIC, FLS_APPL_CONST ) Fls_JobDataSrcPtr = NULL_PTR;

/**
    @brief Pointer to current position in target data buffer
    @details Used only by read job
    @remarks Implements DFLS20211
*/
STATIC P2VAR( uint8, AUTOMATIC, FLS_APPL_CONST ) Fls_JobDataDestPtr = NULL_PTR;

/**
    @brief Indicates that new job has been accepted
    @details Used by all types of job
    @remarks Implements DFLS20212
*/
STATIC VAR(uint8, AUTOMATIC) Fls_JobStart = (uint8)0;

/** 
    @brief Result of last flash hardware job
*/
STATIC VAR(MemIf_JobResultType, AUTOMATIC) Fls_LLD_JobResult = MEMIF_JOB_OK;

/** 
    @brief Type of current flash hardware job
*/
STATIC VAR(Fls_LLD_JobType, AUTOMATIC) Fls_LLD_Job = FLS_LLD_JOB_NONE;

/** 
    @brief Memory array control/configuration register base address of current flash hardware job
*/
STATIC P2VAR(volatile uint32, AUTOMATIC, FLS_CODE) Fls_LLD_regBasePtr = NULL_PTR;

/** 
    @brief PFC control/configuration register base address of current flash hardware job
*/
STATIC P2VAR(volatile uint32, AUTOMATIC, FLS_CODE) Fls_LLD_pfcRegBasePtr = NULL_PTR;

/** 
    @brief PFC configuration register offset address of current flash hardware job
*/
STATIC VAR(uint8, AUTOMATIC) Fls_LLD_pfcConfRegOffset = (uint8)0;

/** 
    @brief PFC configuration register invalidation value of current flash hardware job
*/
STATIC VAR(uint32, AUTOMATIC) Fls_LLD_pfcConfRegInvalValue = 0UL;

/** 
    @brief PFC configuration register back-up value of current flash hardware job
*/
STATIC VAR(uint32, AUTOMATIC) Fls_LLD_pfcConfRegValue = 0UL;

/** 
    @brief 'double word program operation' iterator
*/
STATIC VAR(uint32, AUTOMATIC) Fls_LLD_programCycle = 0UL;

/** 
    @brief 'double word program operation' count
*/
STATIC VAR(uint32, AUTOMATIC) Fls_LLD_doubleWordToCopy = 0UL;

/** 
    @brief To inform Mainfunction that this sector is interleaved between Bank0 and Bank1
*/
STATIC VAR(boolean, AUTOMATIC) Fls_LLD_asyncInterleavedBlock = FALSE;

/** 
    @brief To inform Mainfunction how to select the block to be erased in case of async job
*/
STATIC VAR(uint32, AUTOMATIC) Fls_LLD_bloSelValue = 0UL;
/** 
    @brief To inform Mainfunction if erasing a block in Low Mid or High space in case of async job
*/
STATIC VAR(uint8, AUTOMATIC) Fls_LLD_bloSelRegOffset = (uint8)0;
/** 
    @brief To inform Mainfunction where to do an interlock write in case of async Erase
*/
STATIC P2VAR(volatile uint32, AUTOMATIC, FLS_CODE) Fls_LLD_B1targetAddressPtr = NULL_PTR;

/** 
    @brief To inform Mainfunction about the interlock size in case of async Write
*/
STATIC VAR(uint32, AUTOMATIC) Fls_LLD_InterleavedSize = 0UL;

/** 
    @brief 'data copy' auxiliary pointers
*/
STATIC P2VAR(volatile uint32, AUTOMATIC, FLS_CODE) Fls_LLD_targetAddressPtr = NULL_PTR;
STATIC P2CONST(uint32, AUTOMATIC, FLS_CODE) Fls_LLD_sourceAddressPtr = NULL_PTR;
#if( FLS_ERASE_BLANK_CHECK == STD_ON )
STATIC P2VAR(volatile uint32, AUTOMATIC, FLS_CODE) Fls_LLD_endAddressPtr = NULL_PTR;
#endif    /* FLS_ERASE_BLANK_CHECK == STD_ON */

/** 
    @brief Memory array control/configuration register base address of current flash hardware job B1
*/
STATIC P2VAR(volatile uint32, AUTOMATIC, FLS_CODE) Fls_LLD_B1regBasePtr = NULL_PTR;

#if( FLS_DSI_HANDLER_API == STD_ON )
/** 
    @brief Current status of the sector read operation. The Fls_DsiHandler function can terminate
        the read operation by setting this volatile variable to FLS_LLD_E_FAILED
*/
STATIC VAR( volatile Fls_LLD_ReturnType, AUTOMATIC ) Fls_LLD_ReadStatus = FLS_LLD_E_OK;

/** 
    @brief Current status of the sector compare operation. The Fls_DsiHandler function can terminate
        the compare operation by setting this volatile variable to FLS_LLD_E_FAILED
*/
STATIC VAR( volatile Fls_LLD_ReturnType, AUTOMATIC ) Fls_LLD_CompareStatus = FLS_LLD_E_OK;
#endif

/**
    @brief Physical address of currently read uint8, uint32 from flash
*/
STATIC P2CONST( uint8, AUTOMATIC, FLS_APPL_DATA ) volatile Fls_LLD_ReadAddressPtr = NULL_PTR;


/**
    @brief Physical address of currently compared uint8, uint32 from user buffer
*/
STATIC P2CONST( uint8, AUTOMATIC, FLS_APPL_DATA ) volatile Fls_LLD_CompareAddressPtr = NULL_PTR;


#define FLS_STOP_SEC_VAR_FAST_UNSPECIFIED
/** @note Violates MISRA-C:2004 Advisory Rule 19.1, 19.15: See @ref Fls_c_REF_1 */
#include "MemMap.h"

/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/

#if( FLS_AC_LOAD_ON_JOB_START == STD_ON )
#define FLS_START_SEC_CONST_UNSPECIFIED
/** @note Violates MISRA-C:2004 Advisory Rule 19.1, 19.15: See @ref Fls_c_REF_1 */
#include "MemMap.h"

/**
    @brief Position independent implementation of erase access code
*/
extern CONST(uint32, FLS_CONST) Fls_AcErase[];

/**
    @brief Position independent implementation of write access code
*/
extern CONST(uint32, FLS_CONST) Fls_AcWrite[];

#define FLS_STOP_SEC_CONST_UNSPECIFIED
/** @note Violates MISRA-C:2004 Advisory Rule 19.1, 19.15: See @ref Fls_c_REF_1 */
#include "MemMap.h"
#endif /* FLS_AC_LOAD_ON_JOB_START == STD_ON */


/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

#define FLS_START_SEC_RAMCODE
/** @note Violates MISRA-C:2004 Advisory Rule 19.1, 19.15: See @ref Fls_c_REF_1 */
#include "MemMap.h"
STATIC FUNC(void, FLS_CODE)     Fls_InvalidRestore_Ram (CONST(uint32, FLS_CONST) pfcConfRegOffset, \
    CONST(uint32, FLS_CONST) pfcConfRegInvalValue, CONST(uint32, FLS_CONST) pfcConfRegRestoreValue);
#define FLS_STOP_SEC_RAMCODE
/** @note Violates MISRA-C:2004 Advisory Rule 19.1, 19.15: See @ref Fls_c_REF_1 */
#include "MemMap.h"

STATIC FUNC(Fls_SectorIndexType, FLS_CODE) Fls_GetSectorIndexByAddr(
    CONST(Fls_AddressType, FLS_CONST) TargetAddress);
STATIC FUNC( Fls_AddressType, FLS_CODE ) Fls_GetSectorStartAddr(
    CONST(Fls_SectorIndexType, FLS_CONST) SectorIndex );
#if( FLS_DEV_ERROR_DETECT == STD_ON )
STATIC FUNC(boolean, FLS_CODE) Fls_IsAddrPageAligned( CONST(Fls_AddressType, FLS_CONST) \
     TargetAddress );
STATIC FUNC(boolean, FLS_CODE) Fls_IsAddrPageStartAligned( CONST(Fls_AddressType, FLS_CONST) \
     TargetAddress );
STATIC FUNC(boolean, FLS_CODE) Fls_IsLengthAligned(CONST(Fls_AddressType, FLS_CONST) TargetAddress, \
                                                   CONST(Fls_LengthType, FLS_CONST) Length);
STATIC FUNC(boolean, FLS_CODE) Fls_IsAddrSectorStartAligned(
    CONST(Fls_AddressType, FLS_CONST) TargetAddress );
STATIC FUNC(boolean, FLS_CODE) Fls_IsAddrSectorEndAligned(
    CONST(Fls_AddressType, FLS_CONST) TargetAddress );
#endif
#if( FLS_AC_LOAD_ON_JOB_START == STD_ON )
STATIC FUNC( void, FLS_CODE ) Fls_LoadAc(
    CONST( Fls_JobType, FLS_CONST) Job );
STATIC FUNC( void, FLS_CODE ) Fls_UnloadAc(
    CONST( Fls_JobType, FLS_CONST) Job);
#endif
STATIC FUNC( MemIf_JobResultType, FLS_CODE )  Fls_DoJobErase( void );
STATIC FUNC( Fls_AddressType, FLS_CODE ) Fls_CalcMaxTransferAddrEnd(
    CONST( Fls_LengthType, FLS_CONST) MaxTransfer );
STATIC FUNC( Fls_AddressType, FLS_CODE ) Fls_CalcSectorTransferOffset( void );
STATIC FUNC( Fls_AddressType, FLS_CODE ) Fls_CalcSectorTransferLength(
    CONST( Fls_AddressType, FLS_CONST) MaxTransferEndAddr );
STATIC FUNC( Fls_LLD_ReturnType, FLS_CODE ) Fls_DoJobRead(
    CONST( Fls_AddressType, FLS_CONST) SectorOffset,
    CONST( Fls_AddressType, FLS_CONST) Length );
STATIC FUNC( Fls_LLD_ReturnType, FLS_CODE ) Fls_DoJobWrite(
    CONST( Fls_AddressType, FLS_CONST) SectorOffset,
    CONST( Fls_AddressType, FLS_CONST) Length );
#if( FLS_COMPARE_API == STD_ON )
STATIC FUNC( Fls_LLD_ReturnType, FLS_CODE ) Fls_DoJobCompare(
    CONST( Fls_AddressType, FLS_CONST) SectorOffset,
    CONST( Fls_AddressType, FLS_CONST) Length );
#endif
STATIC FUNC( MemIf_JobResultType, FLS_CODE ) Fls_DoJobDataTransfer(
    CONST( Fls_JobType, FLS_CONST) Job,
    CONST( Fls_LengthType, FLS_CONST) MaxTransfer );

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define FLS_START_SEC_VAR_UNSPECIFIED
/** @note Violates MISRA-C:2004 Advisory Rule 19.1, 19.15: See @ref Fls_c_REF_1 */
#include "MemMap.h"
STATIC P2FUNC (void, const, Fls_InvalidRestore) (CONST(uint32, FLS_CONST) pfcConfRegOffset, \
    CONST(uint32, FLS_CONST) pfcConfRegInvalValue, \
    CONST(uint32, FLS_CONST) pfcConfRegRestoreValue) = &Fls_InvalidRestore_Ram;
#define FLS_STOP_SEC_VAR_UNSPECIFIED
/** @note Violates MISRA-C:2004 Advisory Rule 19.1, 19.15: See @ref Fls_c_REF_1 */
#include "MemMap.h"

#define FLS_START_SEC_RAMCODE
/** @note Violates MISRA-C:2004 Advisory Rule 19.1, 19.15: See @ref Fls_c_REF_1 */
#include "MemMap.h"
/**
@brief   This function invalidate and restore Flash configuration register.
@param[in]     pfcConfRegOffset          FLS prefetch configuration register offset
@param[in]     pfcConfRegInvalValue      FLS prefetch configuration register invalidation Value
@param[in]     pfcConfRegRestoreValue    FLS prefetch configuration register velue (to be restored)
@param[out]    None
@param[in,out] None

@return Description of the returned value
@retval void

@remarks Implements
 */
STATIC FUNC(void, FLS_CODE) Fls_InvalidRestore_Ram(CONST(uint32, FLS_CONST) pfcConfRegOffset, \
    CONST(uint32, FLS_CONST) pfcConfRegInvalValue, CONST(uint32, FLS_CONST) pfcConfRegRestoreValue)
{
    /* invalidate PFC page buffers associated with modified memory bank */
    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
    form of pointer arithmetic: See @ref Fls_c_REF_15 */
    Fls_LLD_pfcRegBasePtr[pfcConfRegOffset] &= (~pfcConfRegInvalValue);

    /* restore PFCR0 or PFCR1 */
    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
    form of pointer arithmetic: See @ref Fls_c_REF_15 */
    Fls_LLD_pfcRegBasePtr[pfcConfRegOffset] = pfcConfRegRestoreValue;
}

#define FLS_STOP_SEC_RAMCODE
/** @note Violates MISRA-C:2004 19.1, 19.15: See @ref Fls_c_REF_1 */
#include "MemMap.h"

#define FLS_START_SEC_CODE
/** @note Violates MISRA-C:2004 19.1, 19.15: See @ref Fls_c_REF_1 */
#include "MemMap.h"

/**
    @brief Get status of erase or write hardware job

    @return MemIf_JobResultType
    @retval    MEMIF_JOB_OK The hardware job has been finished succesfully
    @retval    MEMIF_JOB_FAILED The hardware job has not been finished succesfully
    @retval    MEMIF_JOB_PENDING The hardware job has not yet been finished (asynchronous jobs only)
    @retval    MEMIF_JOB_CANCELLED The hardware job has been cancelled
    
    @remarks Implements DFLS31105
*/
/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/
#define SET_TIMEOUT_COUNTER_TO_ZERO   0x00000000U
#define ERASE_TIMEOUT_COUNTER         FLS_OPT_TIMEOUT_VALUE
#define WRITE_TIMEOUT_COUNTER         FLS_OPT_TIMEOUT_VALUE
#define ABT_OPT_TIMEOUT_COUNTER       FLS_ABT_TIMEOUT_VALUE
/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
STATIC FUNC( MemIf_JobResultType, FLS_CODE ) Fls_LLD_GetJobResult( void );
STATIC FUNC( void, FLS_CODE ) Fls_LLD_Init( void );
STATIC FUNC( void, FLS_CODE ) Fls_LLD_ClrJobResult( void );
#if(( FLS_ERASE_BLANK_CHECK == STD_ON ) || ( FLS_WRITE_BLANK_CHECK == STD_ON ))
STATIC FUNC( Fls_LLD_ReturnType, FLS_CODE ) Fls_LLD_VerifyErase(
    CONSTP2CONST(volatile FLS_LLD_DATA_BUS_WIDTH_TYPE, AUTOMATIC, FLS_APPL_DATA ) FlashAreaPtr,
    CONST( Fls_LengthType, FLS_CONST) DataLength );
#endif    /* FLS_ERASE_BLANK_CHECK || FLS_WRITE_BLANK_CHECK */
#if( FLS_WRITE_VERIFY_CHECK == STD_ON )
STATIC FUNC( Fls_LLD_ReturnType, FLS_CODE ) Fls_LLD_VerifyWrite(
    CONSTP2CONST( volatile FLS_LLD_DATA_BUS_WIDTH_TYPE, AUTOMATIC, FLS_APPL_DATA ) FlashAreaPtr,
    CONSTP2CONST( FLS_LLD_DATA_BUS_WIDTH_TYPE, AUTOMATIC, FLS_APPL_DATA ) UserBufferPtr,
    CONST( Fls_LengthType, FLS_CONST) DataLength );
#endif    /* FLS_WRITE_VERIFY_CHECK == STD_ON */
STATIC FUNC( void, FLS_CODE ) Fls_LLD_MainFunction( void );
#if (FLS_CANCEL_API == STD_ON )
STATIC FUNC( void, FLS_CODE ) Fls_LLD_Cancel( void );
#endif   /* FLS_CANCEL_API == STD_ON */
STATIC FUNC(Fls_LLD_ReturnType, FLS_CODE) Fls_LLD_SectorErase
(
    CONST( Fls_LLD_PhysicalSectorType, FLS_CONST) phySector,
#if( FLS_ERASE_BLANK_CHECK == STD_ON )
    CONST( Fls_LengthType, FLS_CONST) physicalSectorSize,
#endif    /* FLS_ERASE_BLANK_CHECK == STD_ON */
    CONST( boolean, FLS_CONST) asynch
);
STATIC FUNC(Fls_LLD_ReturnType, FLS_CODE) Fls_LLD_SectorWrite
(
    CONST( Fls_LLD_PhysicalSectorType, FLS_CONST) phySector,
    CONST(Fls_AddressType, FLS_CONST) sectorOffset,
    CONST(Fls_LengthType, FLS_CONST) dataLength,
    CONSTP2CONST(uint8, AUTOMATIC, FLS_APPL_DATA) dataPtr,
    CONST( boolean, FLS_CONST) asynch
);
STATIC FUNC( uint32, FLS_CODE ) Fls_LLD_CalcInitDataLength( 
    CONSTP2CONST( uint8, AUTOMATIC, FLS_APPL_DATA ) volatile SourceAddrPtr,
    CONST(uint32, FLS_CONST) TotalBytes );
STATIC FUNC( uint32, FLS_CODE ) Fls_LLD_CalcWideDataLength(
    CONST(uint32, FLS_CONST) InitDataLength,
    CONST(uint32, FLS_CONST) TotalBytes );
STATIC FUNC(Fls_LLD_ReturnType, FLS_CODE) Fls_LLD_SectorRead
(
    CONST( Fls_LLD_PhysicalSectorType, FLS_CONST) phySector,
    CONST(Fls_AddressType, FLS_CONST) sectorOffset,
    CONST(Fls_LengthType, FLS_CONST) dataLength,
    P2VAR(uint8, AUTOMATIC, FLS_APPL_DATA) dataPtr
);
#if( FLS_COMPARE_API == STD_ON )
STATIC FUNC(Fls_LLD_ReturnType, FLS_CODE) Fls_LLD_SectorCompare
(
    CONST( Fls_LLD_PhysicalSectorType, FLS_CONST) phySector,
    CONST(Fls_AddressType, FLS_CONST) sectorOffset,
    CONST(Fls_LengthType, FLS_CONST) dataLength,
    CONSTP2CONST(uint8, AUTOMATIC, FLS_APPL_DATA) dataPtr
);
#endif /* FLS_COMPARE_API == STD_ON */


STATIC FUNC( MemIf_JobResultType, FLS_CODE ) Fls_LLD_GetJobResult( void )
{
    return( Fls_LLD_JobResult );
}

/**
    @brief Initialize flash hardware

    @remarks Implements DFLS31106
*/    
STATIC FUNC( void, FLS_CODE ) Fls_LLD_Init( void )
{
    P2VAR(volatile uint32, AUTOMATIC, FLS_CODE) regBasePtr = NULL_PTR;
    P2VAR(volatile uint32, AUTOMATIC, FLS_CODE) regBase1Ptr = NULL_PTR;

    VAR(uint32, AUTOMATIC) mcrValue = 0UL;
    VAR(uint32, AUTOMATIC) lmlValue = 0UL;
    VAR(uint32, AUTOMATIC) sllValue = 0UL;
    VAR(uint32, AUTOMATIC) hblValue = 0UL;
    
    /* Use diffrent iterator for configured array and physical one */
    VAR(uint32, AUTOMATIC) arrayIter = 0UL;
    VAR(uint32, AUTOMATIC) configIter=0UL;
    VAR(uint32, AUTOMATIC) timerCounter = SET_TIMEOUT_COUNTER_TO_ZERO;

    /* process all FLASH sectors */
    for( arrayIter = 0U; arrayIter < FLS_LLD_FLASH_SECTOR_COUNT; arrayIter++ )
    {
        /* Check which phisical sector has been configured */
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed 
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        if (Fls_ConfigPtr->physicalSector[configIter] == (Fls_LLD_PhysicalSectorType)arrayIter)
        {
            /* This sector is configured to be unlocked? */
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            if (1U == Fls_ConfigPtr->sectorUnlock[configIter]) 
            {
                /* Is it High address space or not? */
                if(flsLLDSectorList0[arrayIter].addrSpaceBloPrimLockRegOffset != \
                   flsLLDSectorList0[arrayIter].addrSpaceBloSecoLockRegOffset)
                {
                    /* Read LML register */
                    regBasePtr = flsLLDSectorList0[arrayIter].memArrayRegBasePtr;
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    lmlValue = regBasePtr[FLASHMEM_LML];

                    /* if LML reg is locked for register writes, write PSW to set LME (enable bit)*/
                    /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes 
                    signedness: See @ref Fls_c_REF_2 */
                    if ( FALSE == (lmlValue & LML_LME))
                    {
                        /* write user provided password to block lock register */
                        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be 
                        the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                        regBasePtr[FLASHMEM_LML] = LML_LME_PASSWORD;

                        /* check if the block lock register is enabled */
                        /* for register writes after writing password */
                        #if(FLS_DEV_ERROR_DETECT == STD_ON)
                        lmlValue = regBasePtr[FLASHMEM_LML];
                        /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion 
                        changes signedness: See @ref Fls_c_REF_2 */
                        if (FALSE == (lmlValue & LML_LME))
                        {
                            Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_INIT_ID, \
                                             FLS_E_UNINIT );
                            Fls_LLD_JobResult = MEMIF_JOB_FAILED;
                        }
                        #endif
                    }
                    
                    /* Directly set protection bit */
                   /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                   only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    regBasePtr[FLASHMEM_LML] &= \
                                (~flsLLDSectorList0[arrayIter].addrSpaceBloLockValue);
                    /* Interleave Block for Low Address */        
                    if ( flsLLDSectorList0[arrayIter].interleavedBlo )
                    {
                        /* Read LML register */
                        regBase1Ptr = flsLLDSectorList0[arrayIter].memArrayB1RegBasePtr;
                        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be 
                        the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                        lmlValue = regBase1Ptr[FLASHMEM_LML];

                        /* if LML reg is locked for register writes, write PSW to set LME (enable bit)*/
                        /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion 
                        changes signedness: See @ref Fls_c_REF_2 */
                        if ( FALSE == (lmlValue & LML_LME))
                        {
                            /* write user provided password to block lock register */
                            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall 
                            be the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                            regBase1Ptr[FLASHMEM_LML] = LML_LME_PASSWORD;

                            /* check if the block lock register is enabled */
                            /* for register writes after writing password */
                            #if(FLS_DEV_ERROR_DETECT == STD_ON)
                            lmlValue = regBase1Ptr[FLASHMEM_LML];
                            /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion 
                            changes signedness: See @ref Fls_c_REF_2 */
                            if (FALSE == (lmlValue & LML_LME))
                            {
                                Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_INIT_ID, \
                                                 FLS_E_UNINIT );
                                Fls_LLD_JobResult = MEMIF_JOB_FAILED;
                            }
                            #endif
                        }
                        
                        /* Directly set protection bit */
                        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be 
                        the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                        regBase1Ptr[FLASHMEM_LML] &= \
                                        (~flsLLDSectorList0[arrayIter].addrSpaceBloLockValue);

                    }
 
                    /* Read SLL register */
                    regBasePtr = flsLLDSectorList0[arrayIter].memArrayRegBasePtr;
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    sllValue = regBasePtr[FLASHMEM_SLL];

                    /* if SLL reg is locked for register writes, write PSW to set LME (enable bit)*/
                    /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes 
                    signedness: See @ref Fls_c_REF_2 */
                    if ( FALSE == (sllValue & SLL_SLE))
                    {
                        /* write user provided password to block lock register */
                        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be 
                        the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                        regBasePtr[FLASHMEM_SLL] = SLL_SLE_PASSWORD;

                        /* check if the block lock register is enabled */
                        /* for register writes after writing password */
                        #if(FLS_DEV_ERROR_DETECT == STD_ON)
                        sllValue = regBasePtr[FLASHMEM_SLL];
                        /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion 
                        changes signedness: See @ref Fls_c_REF_2 */
                        if (FALSE == (sllValue & SLL_SLE))
                        {
                            Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_INIT_ID, \
                                             FLS_E_UNINIT );
                            Fls_LLD_JobResult = MEMIF_JOB_FAILED;
                        }
                        #endif
                    }
                    
                    /* Directly set protection bit */
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    regBasePtr[FLASHMEM_SLL] &= (~flsLLDSectorList0[arrayIter].addrSpaceBloLockValue);

                   if ( flsLLDSectorList0[arrayIter].interleavedBlo )
                    {
                        /* Read SLL register */
                        regBase1Ptr = flsLLDSectorList0[arrayIter].memArrayB1RegBasePtr;
                        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be 
                        the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                        sllValue = regBase1Ptr[FLASHMEM_SLL];

                        /* if SLL reg is locked for register writes, write PSW to set LME (enable bit)*/
                        /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes 
                        signedness: See @ref Fls_c_REF_2 */
                        if ( FALSE == (sllValue & SLL_SLE))
                        {
                            /* write user provided password to block lock register */
                            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall 
                            be the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                            regBase1Ptr[FLASHMEM_SLL] = SLL_SLE_PASSWORD;

                            /* check if the block lock register is enabled */
                            /* for register writes after writing password */
                            #if(FLS_DEV_ERROR_DETECT == STD_ON)
                            sllValue = regBase1Ptr[FLASHMEM_SLL];
                            /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion 
                            changes signedness: See @ref Fls_c_REF_2 */
                            if (FALSE == (sllValue & SLL_SLE))
                            {
                                Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_INIT_ID, \
                                                 FLS_E_UNINIT );
                                Fls_LLD_JobResult = MEMIF_JOB_FAILED;
                            }
                            #endif
                        }
                        
                        /* Directly set protection bit */
                        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be 
                        the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                        regBase1Ptr[FLASHMEM_SLL] &= (~flsLLDSectorList0[arrayIter].addrSpaceBloLockValue);
                    }
                }
                else
                {
                    /* Read HBL register */
                    regBasePtr = flsLLDSectorList0[arrayIter].memArrayRegBasePtr;
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    hblValue = regBasePtr[FLASHMEM_HBL];

                    /* if HBL reg is locked for register writes, write PSW to set HBE (enable bit)*/
                    /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes 
                    signedness: See @ref Fls_c_REF_2 */
                    if ( FALSE == (hblValue & HBL_HBE))
                    {
                        /* write user provided password to block lock register */
                        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be 
                        the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                        regBasePtr[FLASHMEM_HBL] = HBL_HBE_PASSWORD;

                        /* check if the block lock register is enabled */
                        /* for register writes after writing password */
                        #if(FLS_DEV_ERROR_DETECT == STD_ON)
                        hblValue = regBasePtr[FLASHMEM_HBL];
                        /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion 
                        changes signedness: See @ref Fls_c_REF_2 */
                        if (FALSE == (hblValue & HBL_HBE))
                        {
                            Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_INIT_ID, \
                            FLS_E_UNINIT );
                            Fls_LLD_JobResult = MEMIF_JOB_FAILED;
                        }
                        #endif
                    }
                    
                    /* Directly set protection bit */
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    regBasePtr[FLASHMEM_HBL] &= (~flsLLDSectorList0[arrayIter].addrSpaceBloLockValue);

                    if ( flsLLDSectorList0[arrayIter].interleavedBlo )
                    {
                        regBase1Ptr = flsLLDSectorList0[arrayIter].memArrayB1RegBasePtr;
                        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be 
                        the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                        hblValue = regBase1Ptr[FLASHMEM_HBL];
                        /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion 
                        changes signedness: See @ref Fls_c_REF_2 */
                        if ( FALSE == (hblValue & HBL_HBE))
                        {
                            /* write user provided password to block lock register */
                            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall 
                            be the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                            regBase1Ptr[FLASHMEM_HBL] = HBL_HBE_PASSWORD;

                            /* check if the block lock register is enabled */
                            /* for register writes after writing password */
                            #if(FLS_DEV_ERROR_DETECT == STD_ON)
                            hblValue = regBase1Ptr[FLASHMEM_HBL];
                            /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion 
                            changes signedness: See @ref Fls_c_REF_2 */
                            if (FALSE == (hblValue & HBL_HBE))
                            {
                                Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, \
                                                                FLS_INIT_ID, FLS_E_UNINIT );
                                Fls_LLD_JobResult = MEMIF_JOB_FAILED;
                            }
                            #endif
                        }
                        /* Directly set protection bit */
                        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be 
                        the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                        regBase1Ptr[FLASHMEM_HBL] &= \
                                    (~flsLLDSectorList0[arrayIter].addrSpaceBloSelValue);
                    }
                    
                }
            }
            configIter++;
        }
    }

    arrayIter = 0U;

    /* process all FLASH arrays */
    for( arrayIter = 0U; arrayIter < FLS_LLD_FLASH_ARRAY_COUNT; arrayIter++ )
    {
        regBasePtr = flsLLDArrayList0[arrayIter].memArrayRegBasePtr;
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed 
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        mcrValue = regBasePtr[FLASHMEM_MCR];

        /* is program suspend operation possible within array? */
        /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes signedness: 
        See @ref Fls_c_REF_2 */
        if(flsLLDArrayList0[arrayIter].programSuspPossible)
        {
            /* manage program suspend operation state */  
            /* is array in program suspend operation state? */
            /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
            (&&, || and !) should be effectively Boolean: See @ref Fls_c_REF_13 */
            if((mcrValue & MCR_PSUS) && (mcrValue & MCR_DONE))
            {
                /* array is in program suspend state */
                /* re-start high voltage in order to allow resume */
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                regBasePtr[FLASHMEM_MCR] |= MCR_EHV;
                /* resume previously suspended erase/program operation */
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                regBasePtr[FLASHMEM_MCR] &= (~MCR_PSUS);
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
                (&&, || and !) should be effectively Boolean: See @ref Fls_c_REF_13 */
                timerCounter = SET_TIMEOUT_COUNTER_TO_ZERO;                
                while((!(regBasePtr[FLASHMEM_MCR] & MCR_DONE)) && \
                        (timerCounter++ < WRITE_TIMEOUT_COUNTER))
                { 
                    /* wait until end of resume */
                }
                if (WRITE_TIMEOUT_COUNTER==(timerCounter-1))
                {
                    /* Timeout happened */
                    Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
                    /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of 
                        function: See @ref Fls_c_REF_11 */
                    Fls_LLD_Job = FLS_LLD_JOB_NONE;
                    Fls_LLD_JobResult = MEMIF_JOB_FAILED;
                }
                /* terminate program operation */    
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                regBasePtr[FLASHMEM_MCR] &= (~MCR_EHV);
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                regBasePtr[FLASHMEM_MCR] &= (~MCR_PGM);
            }
        }
        /* update the value of MCR register */
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed 
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        mcrValue = regBasePtr[FLASHMEM_MCR];
        /* is erase suspend operation possible within array? */
        /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes signedness: 
        See @ref Fls_c_REF_2 */
        if(flsLLDArrayList0[arrayIter].eraseSuspPossible)
        {
            /* manage erase suspend operation state */  
            /* is array in erase suspend operation state? */
            /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
            (&&, || and !) should be effectively Boolean: See @ref Fls_c_REF_13 */
            if((mcrValue & MCR_ESUS) && (mcrValue & MCR_DONE))
            {
                /* array is in erase suspend state */
                /* re-start high voltage in order to allow resume */
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                regBasePtr[FLASHMEM_MCR] |= MCR_EHV;
                /* resume previously suspended erase/program operation */
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                regBasePtr[FLASHMEM_MCR] &= (~MCR_ESUS);
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
               /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
               (&&, || and !) should be effectively Boolean: See @ref Fls_c_REF_13 */
                timerCounter = SET_TIMEOUT_COUNTER_TO_ZERO;
                while((!(regBasePtr[FLASHMEM_MCR] & MCR_DONE)) && \
                         (timerCounter++ < ERASE_TIMEOUT_COUNTER))
                { 
                    /* wait until end of resume */
                }
                if (ERASE_TIMEOUT_COUNTER <= (timerCounter-1))
                {
                    /* Timeout happened */
                    Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
                    /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of 
                        function: See @ref Fls_c_REF_11 */
                    Fls_LLD_Job = FLS_LLD_JOB_NONE;
                    Fls_LLD_JobResult = MEMIF_JOB_FAILED;
                }
                /* terminate erase operation */
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                regBasePtr[FLASHMEM_MCR] &= (~MCR_EHV);
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                regBasePtr[FLASHMEM_MCR] &= (~MCR_ERS);
            }
        }
        /* update the value of MCR register */
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed 
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        mcrValue = regBasePtr[FLASHMEM_MCR];
        /* abort possible pending normal erase/program operation */
        /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
        (&&, || and !) should be effectively Boolean: See @ref Fls_c_REF_13 */
        if((mcrValue & MCR_ERS) || (mcrValue & MCR_PGM))
        {
           /* manage abort possible pending normal erase/program operation */  
            /* abort erase/program operation */
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            regBasePtr[FLASHMEM_MCR] &= (~MCR_EHV);
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
            (&&, || and !) should be effectively Boolean: See @ref Fls_c_REF_13 */
            timerCounter = SET_TIMEOUT_COUNTER_TO_ZERO;
            while((!(regBasePtr[FLASHMEM_MCR] & MCR_DONE)) && \
                     (timerCounter++ < ABT_OPT_TIMEOUT_COUNTER))
            { 
                /* wait until end of resume */
            }
            if (ABT_OPT_TIMEOUT_COUNTER <= (timerCounter-1))
            {
                /* Timeout happened */
                Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
                /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of 
                    function: See @ref Fls_c_REF_11 */
                Fls_LLD_Job = FLS_LLD_JOB_NONE;
                Fls_LLD_JobResult = MEMIF_JOB_FAILED;
            }
            /* terminate erase operation */
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            regBasePtr[FLASHMEM_MCR] &= (~MCR_ERS);
            /* terminate program operation */
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            regBasePtr[FLASHMEM_MCR] &= (~MCR_PGM);
        }

        /* clear possible EDC, EER, RWE events within array */
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        regBasePtr[FLASHMEM_MCR] = regBasePtr[FLASHMEM_MCR]|(MCR_EDC|MCR_EER|MCR_RWE);

        /* clear block select registers */
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        regBasePtr[FLASHMEM_LMS] = 0U;
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        regBasePtr[FLASHMEM_HBS] = 0U;
    }

    Fls_LLD_JobResult = MEMIF_JOB_OK;
}

/**
    @brief Clear status of erase or write hardware job result
    @details Set the internal status to  MEMIF_JOB_OK
    
    @remarks Implements DFLS31107
*/    
STATIC FUNC( void, FLS_CODE ) Fls_LLD_ClrJobResult( void )
{
    Fls_LLD_JobResult = MEMIF_JOB_OK;
}

/**
    @brief Check that the addressed flash memory area is erased
    @details The function compares the contents of the addressed flash memory 
        area against the value of an erased flash cell to check that the block 
        has been completely erased

    @param[in] FlashAreaPtr first address of the addressed flash memory area
        aligned to the MCU bus width
    @param[in] DataLength number of bytes to check (aligned to the bus width)

    @return Fls_LLD_ReturnType
    @retval FLS_LLD_E_OK operation succeeded
    @retval FLS_LLD_E_FAILED operation failed due to hardware error (ECC)
        or contents of the addressed memory area don't match with value of 
        an erased flash cell

    @remarks Report the FLS_E_VERIFY_ERASE_FAILED Det error when the blank 
        check operation failed due to hardware error (ECC) or contents of 
        the addressed memory area didn't match with value of an erased flash 
        cell
*/
#if(( FLS_ERASE_BLANK_CHECK == STD_ON ) || ( FLS_WRITE_BLANK_CHECK == STD_ON ))
STATIC FUNC( Fls_LLD_ReturnType, FLS_CODE ) Fls_LLD_VerifyErase(
    CONSTP2CONST(volatile FLS_LLD_DATA_BUS_WIDTH_TYPE, AUTOMATIC, FLS_APPL_DATA ) FlashAreaPtr,
    CONST(Fls_LengthType, FLS_CONST) DataLength )
{
    VAR(Fls_LLD_ReturnType, AUTOMATIC) RetVal = FLS_LLD_E_OK;
    P2CONST( uint8, AUTOMATIC, FLS_APPL_DATA ) flashAreaEndPtr = \
           ((const uint8 *)FlashAreaPtr) + DataLength;
    
#if( FLS_DSI_HANDLER_API == STD_ON )
    Fls_LLD_ReadStatus = FLS_LLD_E_PENDING;
#endif

    for( Fls_LLD_ReadAddressPtr = ((const uint8 *)FlashAreaPtr); Fls_LLD_ReadAddressPtr != \
         flashAreaEndPtr; Fls_LLD_ReadAddressPtr += sizeof(FLS_LLD_DATA_BUS_WIDTH_TYPE) )
    {
#if( FLS_DSI_HANDLER_API == STD_ON )        
        if((FLS_ERASED_VALUE != *((FLS_LLD_DATA_BUS_WIDTH_TYPE*)Fls_LLD_ReadAddressPtr) ) ||
           ( FLS_LLD_E_PENDING != Fls_LLD_ReadStatus ))
        {
            break;
        }
#else
        if( FLS_ERASED_VALUE != *((FLS_LLD_DATA_BUS_WIDTH_TYPE*)Fls_LLD_ReadAddressPtr) )
        {
            break;
        }
#endif    
    }
    
    if( Fls_LLD_ReadAddressPtr == flashAreaEndPtr )
    {
#if( FLS_DSI_HANDLER_API == STD_ON )
        Fls_LLD_ReadStatus = FLS_LLD_E_OK;
#endif
    }
    else
    {
#if( FLS_DEV_ERROR_DETECT == STD_ON )
        Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_MAINFUNCTION_ID, \
                         FLS_E_VERIFY_ERASE_FAILED );
#endif
#if( FLS_DSI_HANDLER_API == STD_ON )
        Fls_LLD_ReadStatus = FLS_LLD_E_FAILED;
#else
        RetVal = FLS_LLD_E_FAILED;
#endif
    }

#if( FLS_DSI_HANDLER_API == STD_ON )
    RetVal = Fls_LLD_ReadStatus;
#endif
    return RetVal;

}
#endif    /* FLS_ERASE_BLANK_CHECK || FLS_WRITE_BLANK_CHECK */

/**
    @brief Check that the addressed flash memory area is correctly programmed
    
    @details The function compares the contents of the reprogrammed memory area
        against the contents of the provided application buffer to check that 
        the block has been completely reprogrammed

    @param[in] FlashAreaPtr    first address of the addressed flash memory area
        aligned to MCU bus width boundary
    @param[in] UserBufferPtr first address of the application buffer area 
        aligned to MCU bus width boundary            
    @param[in] DataLength number of bytes to compare aligned to the MCU bus
        width

    @return Fls_LLD_ReturnType
    @retval FLS_LLD_E_OK operation succeeded
    @retval FLS_LLD_E_FAILED operation failed due to hardware error (ECC)
        or contents of the reprogrammed memory area don't match with the 
        contents of the provided application buffer

    @remarks Report the FLS_E_VERIFY_WRITE_FAILED Det error when the verify 
        write operation failed due to hardware error (ECC) or contents of 
        the reprogrammed memory area didn't match with the contents of 
        the provided application buffer
*/
#if( FLS_WRITE_VERIFY_CHECK == STD_ON )
STATIC FUNC( Fls_LLD_ReturnType, FLS_CODE ) Fls_LLD_VerifyWrite(
    CONSTP2CONST( volatile FLS_LLD_DATA_BUS_WIDTH_TYPE, AUTOMATIC, FLS_APPL_DATA ) FlashAreaPtr,
    CONSTP2CONST( FLS_LLD_DATA_BUS_WIDTH_TYPE, AUTOMATIC, FLS_APPL_DATA ) UserBufferPtr,
    CONST(Fls_LengthType, FLS_CONST) DataLength )
{
    VAR(Fls_LLD_ReturnType, AUTOMATIC) RetVal = FLS_LLD_E_OK;
    P2CONST( uint8, AUTOMATIC, FLS_APPL_DATA ) flashAreaEndPtr = \
           ((const uint8 *)FlashAreaPtr) + DataLength;

#if( FLS_DSI_HANDLER_API == STD_ON )
    Fls_LLD_CompareStatus = FLS_LLD_E_PENDING;
#endif
    
    Fls_LLD_CompareAddressPtr = ((const uint8 *)UserBufferPtr);
        
    for( Fls_LLD_ReadAddressPtr = ((const uint8 *)FlashAreaPtr); Fls_LLD_ReadAddressPtr != \
         flashAreaEndPtr; Fls_LLD_ReadAddressPtr += sizeof(FLS_LLD_DATA_BUS_WIDTH_TYPE) )
    {

#if( FLS_DSI_HANDLER_API == STD_ON )
        if(( *((FLS_LLD_DATA_BUS_WIDTH_TYPE*)Fls_LLD_ReadAddressPtr) != \
             *((FLS_LLD_DATA_BUS_WIDTH_TYPE*)Fls_LLD_CompareAddressPtr)) || \
           ( Fls_LLD_CompareStatus != FLS_LLD_E_PENDING ))
        {
            break;
        }
#else
        if( *((FLS_LLD_DATA_BUS_WIDTH_TYPE*)Fls_LLD_ReadAddressPtr) != \
            *((FLS_LLD_DATA_BUS_WIDTH_TYPE*)Fls_LLD_CompareAddressPtr) )
        {
            break;
        }

#endif
        
        Fls_LLD_CompareAddressPtr += sizeof(FLS_LLD_DATA_BUS_WIDTH_TYPE);
    }
    
    if( Fls_LLD_ReadAddressPtr == flashAreaEndPtr )
    {
#if( FLS_DSI_HANDLER_API == STD_ON )
        Fls_LLD_CompareStatus = FLS_LLD_E_OK;
#endif
    }
    else
    {
#if( FLS_DEV_ERROR_DETECT == STD_ON )
        Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_MAINFUNCTION_ID, \
                         FLS_E_VERIFY_WRITE_FAILED );
#endif
#if( FLS_DSI_HANDLER_API == STD_ON )
        Fls_LLD_CompareStatus = FLS_LLD_E_FAILED;
#else
        RetVal = FLS_LLD_E_FAILED;
#endif
    }

#if( FLS_DSI_HANDLER_API == STD_ON )
     RetVal = Fls_LLD_CompareStatus;
#endif
    return RetVal;

}
#endif    /* FLS_WRITE_VERIFY_CHECK == STD_ON */

/**
    @brief Process ongoing erase or write hardware job

    @remarks Dem_ReportErrorStatus(FLS_E_ERASE_FAILED, DEM_EVENT_STATUS_FAILED)
        when erase operation failed due to hardware error

    @remarks Dem_ReportErrorStatus(FLS_E_WRITE_FAILED, DEM_EVENT_STATUS_FAILED)
        when write operation failed due to hardware error    
    
    @remarks Implements DFLS31108
*/
STATIC FUNC( void, FLS_CODE ) Fls_LLD_MainFunction( void )
{
    if(MEMIF_JOB_PENDING == Fls_LLD_JobResult )
    {
        /* some hardware job (asynchronous) is pending */
        if (FLS_LLD_JOB_ERASE == Fls_LLD_Job )
        {
            /* FLS_LLD_JOB_ERASE */
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            if(Fls_LLD_regBasePtr[FLASHMEM_MCR] & MCR_DONE)
            {
                /* erase/program high voltage sequence already finished */

                /* invalidate PFC page buffers associated with modified memory bank */
                /* restore PFCR0 or PFCR1 */
                Fls_InvalidRestore((uint32) Fls_LLD_pfcConfRegOffset, \
                (uint32) Fls_LLD_pfcConfRegInvalValue, (uint32) Fls_LLD_pfcConfRegValue);

            
                
                /* verify that erase operation was successful */
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                if(Fls_LLD_regBasePtr[FLASHMEM_MCR] & MCR_PEG)
                {
                    /* disable high voltage */
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_EHV);
                    /* terminate erase operation */
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_ERS);
                    /* clear block select registers */
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_LLD_regBasePtr[FLASHMEM_LMS] = 0U;
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_LLD_regBasePtr[FLASHMEM_HBS] = 0U;
                    /* Check if the block is interleaved */
                    /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical 
                    operators (&&, || and !) should be effectively Boolean: See @ref Fls_c_REF_13 */
                    if(!Fls_LLD_asyncInterleavedBlock)
                    {
#if( FLS_ERASE_BLANK_CHECK == STD_ON )
                        /* schedule erase blank check of flash sector */
                        Fls_LLD_Job = FLS_LLD_JOB_ERASE_BLANK_CHECK;
#else
                        /* erase operation succeed */
                        Fls_LLD_Job = FLS_LLD_JOB_NONE;
                        Fls_LLD_JobResult = MEMIF_JOB_OK;
#endif /* FLS_ERASE_BLANK_CHECK == STD_ON */
                    }
                    else
                    {
                        /* setup a new erase operation for interleaved block */
                        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be 
                        the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                        Fls_LLD_B1regBasePtr[FLASHMEM_MCR] |= MCR_ERS;
                        /* load adequate block select register */
                        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be 
                        the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */                       
                        Fls_LLD_B1regBasePtr[Fls_LLD_bloSelRegOffset] = Fls_LLD_bloSelValue;
                        /* make an erase interlock write, dummy data word write */
                        *Fls_LLD_B1targetAddressPtr = 0xFFFFFFFFU;
                        /* back-up PFCR0 or PFCR1 */
                        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be 
                        the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                        Fls_LLD_pfcConfRegValue = Fls_LLD_pfcRegBasePtr[Fls_LLD_pfcConfRegOffset];
                    
                        /* start internal erase/program sequence */
                        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be 
                        the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                        Fls_LLD_B1regBasePtr[FLASHMEM_MCR] |= MCR_EHV;
                        
                        Fls_LLD_Job = FLS_LLD_JOB_ERASE_TEMP;
                        Fls_LLD_JobResult = MEMIF_JOB_PENDING;
                    }
                    
                }
                else
                {
                    /* disable high voltage */
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_EHV);
                    /* terminate erase operation */
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_ERS);
                    /* clear block select registers */
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_LLD_regBasePtr[FLASHMEM_LMS] = 0U;
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_LLD_regBasePtr[FLASHMEM_HBS] = 0U;
                    /* erase operation failed */
                    Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_ERASE_FAILED, DEM_EVENT_STATUS_FAILED);
                    Fls_LLD_Job = FLS_LLD_JOB_NONE;
                    Fls_LLD_JobResult = MEMIF_JOB_FAILED;
                }
            }
            else
            {
                /* erase/program high voltage sequence didn't finished yet */
                /* wait for another call of Fls_LLD_MainFunction, do nothing */
            }
        }
        /* Erase interleaved hardware job (asynchronous) is pending */
        else if (FLS_LLD_JOB_ERASE_TEMP == Fls_LLD_Job)
        {
            /* FLS_LLD_JOB_ERASE */
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */           
            if(Fls_LLD_B1regBasePtr[FLASHMEM_MCR] & MCR_DONE)
            {
                /* erase/program high voltage sequence already finished */

                /* invalidate PFC page buffers associated with modified memory bank */
                /* restore PFCR0 or PFCR1 */
                Fls_InvalidRestore((uint32) Fls_LLD_pfcConfRegOffset, \
                           (uint32) Fls_LLD_pfcConfRegInvalValue, (uint32) Fls_LLD_pfcConfRegValue);
                
                /* verify that erase operation was successful */
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                if(Fls_LLD_B1regBasePtr[FLASHMEM_MCR] & MCR_PEG)
                {
                    /* disable high voltage */
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_LLD_B1regBasePtr[FLASHMEM_MCR] &= (~MCR_EHV);
                    /* terminate erase operation */
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_LLD_B1regBasePtr[FLASHMEM_MCR] &= (~MCR_ERS);
                    /* clear block select registers */
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_LLD_B1regBasePtr[FLASHMEM_LMS] = 0U;
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_LLD_B1regBasePtr[FLASHMEM_HBS] = 0U;
    #if( FLS_ERASE_BLANK_CHECK == STD_ON )
                    /* schedule erase blank check of flash sector */
                    Fls_LLD_Job = FLS_LLD_JOB_ERASE_BLANK_CHECK;
    #else
                    /* erase operation succeed */
                    Fls_LLD_Job = FLS_LLD_JOB_NONE;
                    Fls_LLD_JobResult = MEMIF_JOB_OK;
    #endif /* FLS_ERASE_BLANK_CHECK == STD_ON */
                }
                else
                {
                    /* disable high voltage */
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_LLD_B1regBasePtr[FLASHMEM_MCR] &= (~MCR_EHV);
                    /* terminate erase operation */
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_LLD_B1regBasePtr[FLASHMEM_MCR] &= (~MCR_ERS);
                    /* clear block select registers */
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_LLD_B1regBasePtr[FLASHMEM_LMS] = 0U;
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_LLD_B1regBasePtr[FLASHMEM_HBS] = 0U;
                    /* erase operation failed */
                    Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_ERASE_FAILED, \
                                                  DEM_EVENT_STATUS_FAILED);
                    Fls_LLD_Job = FLS_LLD_JOB_NONE;
                    Fls_LLD_JobResult = MEMIF_JOB_FAILED;
                }
            }
            else
            {
                /* erase/program high voltage sequence didn't finished yet */
                /* wait for another call of Fls_LLD_MainFunction, do nothing */
            }
        }
        /* Write hardware job (asynchronous) is pending */        
        else if (FLS_LLD_JOB_WRITE == Fls_LLD_Job )
        {
            /* FLS_LLD_JOB_WRITE */
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */           
            if(Fls_LLD_regBasePtr[FLASHMEM_MCR] & MCR_DONE)
            {
                /* erase/program high voltage sequence already finished */

                /* invalidate PFC page buffers associated with modified memory bank */
                /* restore PFCR0 or PFCR1 */
                Fls_InvalidRestore((uint32) Fls_LLD_pfcConfRegOffset, \
                (uint32) Fls_LLD_pfcConfRegInvalValue, (uint32) Fls_LLD_pfcConfRegValue);
                
                /* verify that program operation was successful */
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                if(Fls_LLD_regBasePtr[FLASHMEM_MCR] & MCR_PEG)
                {
                    /* program operation was successful */
                    
                    /* disable high voltage */
                   /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                   only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */                   
                    Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_EHV);
#if( FLS_WRITE_VERIFY_CHECK == STD_ON )                    
                    if( (uint8)FLS_PAGE_SIZE_08 == Fls_ConfigPtr->sectorPageSize[Fls_JobSectorIt] )
                    {
                        if( FLS_LLD_E_OK != Fls_LLD_VerifyWrite( Fls_LLD_targetAddressPtr - \
                                                             (FLS_LLD_DATA_BUS_WIDTH_TYPE)2, \
                                                                   Fls_LLD_sourceAddressPtr - \
                                                                (FLS_LLD_DATA_BUS_WIDTH_TYPE)2, \
                                                              (Fls_LengthType)FLS_PAGE_SIZE_08 ) )
                        {
                            /* terminate program operation */
                            Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_PGM);
                            Fls_LLD_Job = FLS_LLD_JOB_NONE;
                            Fls_LLD_JobResult = MEMIF_JOB_FAILED;
                            /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement 
                            before end of function: See @ref Fls_c_REF_11 */
                            return;                
                        }
                    }
                    else
                    {
                        if( FLS_LLD_E_OK != Fls_LLD_VerifyWrite( Fls_LLD_targetAddressPtr - \
                                                            (FLS_LLD_DATA_BUS_WIDTH_TYPE)1, \
                                                                 Fls_LLD_sourceAddressPtr - \
                                                             (FLS_LLD_DATA_BUS_WIDTH_TYPE)1, \
                                                           (Fls_LengthType)FLS_PAGE_SIZE_04 ) )
                        {
                            /* terminate program operation */
                            Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_PGM);
                            Fls_LLD_Job = FLS_LLD_JOB_NONE;
                            Fls_LLD_JobResult = MEMIF_JOB_FAILED;
                            /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement 
                            before end of function: See @ref Fls_c_REF_11 */
                            return;                
                        }
                    }

#endif    /* FLS_WRITE_VERIFY_CHECK == STD_ON */                    

                    /* more double word program operation to be performed? */
                    if(Fls_LLD_programCycle<Fls_LLD_doubleWordToCopy)
                    {
                        /* continue with next double word program operation */
                        
#if( FLS_WRITE_BLANK_CHECK == STD_ON )                        
                        if( FLS_LLD_E_OK != Fls_LLD_VerifyErase(Fls_LLD_targetAddressPtr, \
                            Fls_ConfigPtr->sectorPageSize[Fls_JobSectorIt]) )
                        {
                            /* terminate program operation */
                            Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_PGM);
                            Fls_LLD_Job = FLS_LLD_JOB_NONE;
                            Fls_LLD_JobResult = MEMIF_JOB_FAILED;
                            /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement 
                            before end of function: See @ref Fls_c_REF_11 */
                            return;                
                        }
#endif    /* FLS_WRITE_BLANK_CHECK == STD_ON */                        
                        if(Fls_LLD_asyncInterleavedBlock)
                        {
                            /* update Fls_LLD_regBasePtr based on targetAddress Bank */
                            /** @note Violates MISRA-C:2004 Advisory Rule 11.1, Conversions between 
                            a pointer to a function: See @ref Fls_c_REF_14 */
                            if(((uint32)Fls_LLD_targetAddressPtr) & Fls_LLD_InterleavedSize)
                            {
                                /* it is Bank1 */
                               /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing 
                               shall be the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */                              
                                Fls_LLD_regBasePtr = \
                                 flsLLDSectorList0[Fls_ConfigPtr->physicalSector[Fls_JobSectorIt]].memArrayB1RegBasePtr;
                            }
                            else
                            {
                                /* it is Bank0 */
                               /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing 
                               shall be the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */                                
                                Fls_LLD_regBasePtr = \
                                  flsLLDSectorList0[Fls_ConfigPtr->physicalSector[Fls_JobSectorIt]].memArrayRegBasePtr;
                            }

                            /* To be sure that PGM bit is set for the interleaved block */
                            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall 
                            be the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                            Fls_LLD_regBasePtr[FLASHMEM_MCR] |=  MCR_PGM;
                        }
                        
                        /* make a program data interlock write, first word data write */
                        *Fls_LLD_targetAddressPtr = *Fls_LLD_sourceAddressPtr;
                        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be 
                        the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                        Fls_LLD_targetAddressPtr += 1;
                        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be 
                        the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                        Fls_LLD_sourceAddressPtr += 1;
                        if ( (uint8)FLS_PAGE_SIZE_08 == \
                        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be 
                        the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                        Fls_ConfigPtr->sectorPageSize[Fls_JobSectorIt] )
                        {
                            /* make a program data write, second word data write */
                            *Fls_LLD_targetAddressPtr = *Fls_LLD_sourceAddressPtr;
                            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall 
                            be the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                            Fls_LLD_targetAddressPtr += 1;
                            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall 
                            be the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                            Fls_LLD_sourceAddressPtr += 1;
                        }
                        
                        /* back-up PFCR0 or PFCR1 */
                        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be 
                        the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                        Fls_LLD_pfcConfRegValue = Fls_LLD_pfcRegBasePtr[Fls_LLD_pfcConfRegOffset];
                        
                        /* start internal erase/program sequence */
                         /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be 
                         the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                         Fls_LLD_regBasePtr[FLASHMEM_MCR] |= MCR_EHV;
                         
                         /* one more double word program operation already initiated */
                        Fls_LLD_programCycle++;
         
                        Fls_LLD_Job = FLS_LLD_JOB_WRITE;
                        Fls_LLD_JobResult = MEMIF_JOB_PENDING;
                    }
                    else
                    {
                        
                        if(Fls_LLD_asyncInterleavedBlock)
                        {
                            /* all double word program operations succeed */
                            /* terminate program operation  on Bank 1 */
                            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall
                            be the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                            Fls_LLD_regBasePtr = \
                              flsLLDSectorList0[Fls_ConfigPtr->physicalSector[Fls_JobSectorIt]].memArrayB1RegBasePtr;
                            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall
                            be the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                            Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_PGM);
                            
                            /* terminate program operation  on Bank 0 */
                            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall
                            be the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                            Fls_LLD_regBasePtr = \
                              flsLLDSectorList0[Fls_ConfigPtr->physicalSector[Fls_JobSectorIt]].memArrayRegBasePtr;
                            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall 
                            be the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                            Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_PGM);
                        }
                        else
                        {

                        /* all double word program operations succeed */
                        /* terminate program operation */    
                        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be 
                        the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                        Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_PGM);
                            
                        }
                        
                        /* For a Write Job in ASYNC mode check if Fls_JobSectorIt should be increased */
                        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be 
                        the only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                        if( (Fls_JobAddrIt > (Fls_ConfigPtr->sectorEndAddr[Fls_JobSectorIt]) ))
                        {
                            /* Move on to the next sector */
                            Fls_JobSectorIt++;
                        }            
                        
                        /* program operation succeed */
                        Fls_LLD_Job = FLS_LLD_JOB_NONE;
                        Fls_LLD_JobResult = MEMIF_JOB_OK;
                    }
                }
                else
                {
                    /* program operation was not successful */
                    
                    /* disable high voltage */
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_EHV);
                    /* terminate program operation */
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_PGM);
                    /* program operation failed */
                    Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_WRITE_FAILED, DEM_EVENT_STATUS_FAILED);
                    Fls_LLD_Job = FLS_LLD_JOB_NONE;
                    Fls_LLD_JobResult = MEMIF_JOB_FAILED;
                }
            }
            else
            {
                /* erase/program high voltage sequence didn't finished yet */
                /* wait for another call of Fls_LLD_MainFunction, do nothing */
            }
        }
        else if ( FLS_LLD_JOB_ERASE_BLANK_CHECK == Fls_LLD_Job )
        {
                /* FLS_LLD_JOB_ERASE_BLANK_CHECK */
#if( FLS_ERASE_BLANK_CHECK == STD_ON )
            while (Fls_LLD_targetAddressPtr < Fls_LLD_endAddressPtr)
            {
                if (((Fls_LLD_endAddressPtr - Fls_LLD_targetAddressPtr)*4) >= \
                      FLS_MAX_ERASE_BLANK_CHECK)
                {
                    /* at least one erase blank check with FLS_MAX_ERASE_BLANK_CHECK size */
                    if( FLS_LLD_E_OK != Fls_LLD_VerifyErase(Fls_LLD_targetAddressPtr, \
                        FLS_MAX_ERASE_BLANK_CHECK) )
                    {
                        Fls_LLD_Job = FLS_LLD_JOB_NONE;
                        Fls_LLD_JobResult = MEMIF_JOB_FAILED;
                        /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before 
                        end of function: See @ref Fls_c_REF_11 */
                        return;
                    }
                    Fls_LLD_targetAddressPtr += FLS_MAX_ERASE_BLANK_CHECK/4;
                    /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end 
                    of function: See @ref Fls_c_REF_11 */
                    return;
                }
                else
                {
                    /* at least one erase blank check with 4 bytes size */
                    if( FLS_LLD_E_OK != Fls_LLD_VerifyErase(Fls_LLD_targetAddressPtr, \
                      (Fls_LLD_endAddressPtr - Fls_LLD_targetAddressPtr)*4) )
                    {
                        Fls_LLD_Job = FLS_LLD_JOB_NONE;
                        Fls_LLD_JobResult = MEMIF_JOB_FAILED;
                        /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before 
                        end of function: See @ref Fls_c_REF_11 */
                        return;
                    }
                    Fls_LLD_targetAddressPtr += Fls_LLD_endAddressPtr - Fls_LLD_targetAddressPtr;
                    /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end 
                    of function: See @ref Fls_c_REF_11 */
                    return;
                }
            }
            /* erase blank check succeeded */
            Fls_LLD_Job = FLS_LLD_JOB_NONE;
            Fls_LLD_JobResult = MEMIF_JOB_OK;
#else
            Fls_LLD_Job = FLS_LLD_JOB_NONE;
            Fls_LLD_JobResult = MEMIF_JOB_OK;
#endif    /* FLS_ERASE_BLANK_CHECK == STD_ON */                
        }
        /* Write interleaved hardware job (asynchronous) is pending */
        else if (FLS_LLD_JOB_NONE == Fls_LLD_Job)
        {
            /* Do nothing */
        }
        else
        /* Compiler_Warning: Added CER for Catastrophic events */
        {
            Cer_ReportError( (uint16) FLS_MODULE_ID, \
                             (uint8)FLS_INSTANCE_ID, \
                             (uint8)FLS_SID_SETCLOCKMODE, \
                             (uint8)FLS_E_DEFAULT);
        }
    }
    else
    {
        /* no hardware job (asynchronous) is pending, do nothing */
    }
}

#if (FLS_CANCEL_API == STD_ON )
/**
    @brief Cancel ongoing erase or write hardware job
    
    @remarks Implements DFLS31109
*/
STATIC FUNC( void, FLS_CODE ) Fls_LLD_Cancel( void )
{
    VAR(uint32, AUTOMATIC) timerCounter = SET_TIMEOUT_COUNTER_TO_ZERO;

    if(MEMIF_JOB_PENDING == Fls_LLD_JobResult )
    {
        /* some hardware job (asynchronous) is pending */
        if (FLS_LLD_JOB_ERASE == Fls_LLD_Job )
        {
            /* FLS_LLD_JOB_ERASE */
            /* hence make erase-abort operation */
            
            /* abort erase/program operation */
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_EHV);
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
            (&&, || and !) should be effectively Boolean: See @ref Fls_c_REF_13 */
            timerCounter = SET_TIMEOUT_COUNTER_TO_ZERO;
            while((!(Fls_LLD_regBasePtr[FLASHMEM_MCR] & MCR_DONE)) && \
                    (timerCounter++ < ABT_OPT_TIMEOUT_COUNTER))
            { 
                /* wait until end of abort */
            }
            if (ABT_OPT_TIMEOUT_COUNTER <= (timerCounter-1))
            {
                /* Timeout happened */
                Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
                /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of 
                    function: See @ref Fls_c_REF_11 */
                Fls_LLD_Job = FLS_LLD_JOB_NONE;
                Fls_LLD_JobResult = MEMIF_JOB_FAILED;
            }
            /* terminate erase operation */
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_ERS);
            
            /* clear block select registers */
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            Fls_LLD_regBasePtr[FLASHMEM_LMS] = 0U;
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            Fls_LLD_regBasePtr[FLASHMEM_HBS] = 0U;
                
            /* invalidate PFC page buffers associated with modified memory bank */
            /* restore PFCR0 or PFCR1 */
            Fls_InvalidRestore((uint32) Fls_LLD_pfcConfRegOffset, \
            (uint32) Fls_LLD_pfcConfRegInvalValue, (uint32) Fls_LLD_pfcConfRegValue);
                
            /* erase operation cancelled */
            Fls_LLD_Job = FLS_LLD_JOB_NONE;
            Fls_LLD_JobResult = MEMIF_JOB_CANCELLED;
        }
        else if (FLS_LLD_JOB_ERASE_TEMP == Fls_LLD_Job )
        {   
            /* FLS_LLD_JOB_ERASE_TEMP */
            /* hence make erase-abort operation on interleaved block */
            
            /* abort erase/program operation */
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            Fls_LLD_B1regBasePtr[FLASHMEM_MCR] &= (~MCR_EHV);
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
            (&&, || and !) should be effectively Boolean: See @ref Fls_c_REF_13 */
            timerCounter = SET_TIMEOUT_COUNTER_TO_ZERO;
            while((!(Fls_LLD_B1regBasePtr[FLASHMEM_MCR] & MCR_DONE)) && \
                    (timerCounter++ < ABT_OPT_TIMEOUT_COUNTER))
            { 
                /* wait until end of abort */
            }
            if (ABT_OPT_TIMEOUT_COUNTER <=(timerCounter-1))
            {
                /* Timeout happened */
                Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
                /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of 
                    function: See @ref Fls_c_REF_11 */
                Fls_LLD_Job = FLS_LLD_JOB_NONE;
                Fls_LLD_JobResult = MEMIF_JOB_FAILED;
            }
            /* terminate erase operation */
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            Fls_LLD_B1regBasePtr[FLASHMEM_MCR] &= (~MCR_ERS);
            
            /* clear block select registers */
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            Fls_LLD_B1regBasePtr[FLASHMEM_LMS] = 0U;
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            Fls_LLD_B1regBasePtr[FLASHMEM_HBS] = 0U;
                
            /* invalidate PFC page buffers associated with modified memory bank */
            /* restore PFCR0 or PFCR1 */
            Fls_InvalidRestore((uint32) Fls_LLD_pfcConfRegOffset, \
            (uint32) Fls_LLD_pfcConfRegInvalValue, (uint32) Fls_LLD_pfcConfRegValue);
                
            /* erase operation cancelled */
            Fls_LLD_Job = FLS_LLD_JOB_NONE;
            Fls_LLD_JobResult = MEMIF_JOB_CANCELLED;
        }
        else
        {
            /* FLS_LLD_JOB_WRITE */
            /* hence make program-abort operation */
                
            /* abort erase/program operation */
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_EHV);
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
           /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
           (&&, || and !) should be effectively Boolean: See @ref Fls_c_REF_13 */
            timerCounter = SET_TIMEOUT_COUNTER_TO_ZERO;
            while((!(Fls_LLD_regBasePtr[FLASHMEM_MCR] & MCR_DONE)) && \
                    (timerCounter++ < ABT_OPT_TIMEOUT_COUNTER))
            { 
                /* wait until end of abort */
            }
            if (ABT_OPT_TIMEOUT_COUNTER <=(timerCounter-1))
            {
                /* Timeout happened */
                Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
                /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of 
                    function: See @ref Fls_c_REF_11 */
                Fls_LLD_Job = FLS_LLD_JOB_NONE;
                Fls_LLD_JobResult = MEMIF_JOB_FAILED;
            }
            /* terminate program operation */
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_PGM);
    
            /* invalidate PFC page buffers associated with modified memory bank */
            /* restore PFCR0 or PFCR1 */
            Fls_InvalidRestore((uint32) Fls_LLD_pfcConfRegOffset, \
            (uint32) Fls_LLD_pfcConfRegInvalValue, (uint32) Fls_LLD_pfcConfRegValue);
                
            /* program operation cancelled */
            Fls_LLD_Job = FLS_LLD_JOB_NONE;
            Fls_LLD_JobResult = MEMIF_JOB_CANCELLED;
        }
    }
    else
    {
        /* no hardware job (asynchronous) is pending, do nothing */
        Fls_LLD_Job = FLS_LLD_JOB_NONE;
        Fls_LLD_JobResult = MEMIF_JOB_CANCELLED;
    }
}
#endif /* FLS_CANCEL_API == STD_ON */

/**
    @brief Erase one complete flash sector

    @param[in] phySector Physical sector ID
    @param[in] asynch set to TRUE for asynchronous and FALSE for synchronous 
        function operation
        
    @return Fls_LLD_ReturnType
    @retval FLS_LLD_E_OK Operation succeeded
    @retval FLS_LLD_E_FAILED Operation failed due to hardware error
    @retval FLS_LLD_E_PENDING The operation has not yet been finished 
        (only for asynchronous operation )
        
    @pre phySector must be in range
    @pre The module must be initialized
    
    @remarks Dem_ReportErrorStatus(FLS_E_ERASE_FAILED, DEM_EVENT_STATUS_FAILED)
    when erase operation failed due to hardware error
    
    @remarks Implements DFLS31100
*/
STATIC FUNC(Fls_LLD_ReturnType, FLS_CODE) Fls_LLD_SectorErase
(
    CONST( Fls_LLD_PhysicalSectorType, FLS_CONST) phySector,
#if( FLS_ERASE_BLANK_CHECK == STD_ON )
    CONST(Fls_LengthType, FLS_CONST) physicalSectorSize,
#endif    /* FLS_ERASE_BLANK_CHECK == STD_ON */
    CONST( boolean, FLS_CONST) asynch
)
{
    VAR(uint8, AUTOMATIC) bloSelRegOffset = flsLLDSectorList0[phySector].sectorBloSelRegOffset;
    VAR(uint32, AUTOMATIC) bloSelValue = flsLLDSectorList0[phySector].addrSpaceBloSelValue;
    VAR(uint8, AUTOMATIC) bloPrimLockRegOffset = \
                          flsLLDSectorList0[phySector].addrSpaceBloPrimLockRegOffset;
    VAR(uint8, AUTOMATIC) bloSecoLockRegOffset = \
                          flsLLDSectorList0[phySector].addrSpaceBloSecoLockRegOffset;
    VAR(uint32, AUTOMATIC) bloLockValue = flsLLDSectorList0[phySector].addrSpaceBloLockValue;
    VAR(boolean, AUTOMATIC) interleavedBlock = flsLLDSectorList0[phySector].interleavedBlo;
    /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes signedness: See 
    @ref Fls_c_REF_2 */
    VAR(boolean, AUTOMATIC) B0OperResult = FALSE;
    /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes signedness: See 
    @ref Fls_c_REF_2 */
    VAR(boolean, AUTOMATIC) B1OperResult = FALSE;
    P2VAR(volatile uint32, AUTOMATIC, FLS_CODE) B1targetAddressPtr = \
    flsLLDSectorList0[phySector].sectorStartB1AddressPtr;
    VAR(volatile uint32, AUTOMATIC) timerCounterAC = SET_TIMEOUT_COUNTER_TO_ZERO;

    Fls_LLD_targetAddressPtr = flsLLDSectorList0[phySector].sectorStartAddressPtr;
    Fls_LLD_regBasePtr = flsLLDSectorList0[phySector].memArrayRegBasePtr;
    /** @note Violates MISRA-C:2004 Advisory Rule 11.3, Cast from unsigned long to pointer: See @ref 
    Fls_c_REF_6 */
    /** @note Violates MISRA-C:2004 Advisory Rule 11.1, Conversions between a pointer to a function: 
    See @ref Fls_c_REF_14 */
    Fls_LLD_pfcRegBasePtr = (volatile uint32*)(FLASHMEM0_PFC0_BASEADDR);
    Fls_LLD_pfcConfRegOffset = flsLLDSectorList0[phySector].platformFlashConfRegOffset;
    Fls_LLD_pfcConfRegInvalValue = flsLLDSectorList0[phySector].platformFlashConfInvalValue;
    Fls_LLD_B1regBasePtr = flsLLDSectorList0[phySector].memArrayB1RegBasePtr;

#if( FLS_ERASE_BLANK_CHECK == STD_ON )
    Fls_LLD_endAddressPtr = \
    (flsLLDSectorList0[phySector].sectorStartAddressPtr + (physicalSectorSize/4));
#endif    /* FLS_ERASE_BLANK_CHECK == STD_ON */

    Fls_LLD_pfcConfRegValue = 0U;

    /* verify that EHV may be set */
    /** @note Violates MISRA-C:2004 Advisory Rule 12.4, Side effects on right hand of logical 
    operator: See @ref Fls_c_REF_9 */
   /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
   (&&, || and !) should be effectively Boolean: See @ref Fls_c_REF_13 */
    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed 
    form of pointer arithmetic: See @ref Fls_c_REF_15 */
    if( ( (Fls_LLD_regBasePtr[FLASHMEM_MCR] & (MCR_ERS|MCR_PGM|MCR_ESUS)) != 0UL ) || \
         ((Fls_LLD_regBasePtr[FLASHMEM_UT0] & (UT0_AIE)) !=0UL ))
    {
        /*  EHV may not be set: modify operation already in progress */
        Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_ERASE_FAILED, DEM_EVENT_STATUS_FAILED);
        /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of 
        function: See @ref Fls_c_REF_11 */
        return FLS_LLD_E_FAILED;
    }
    
    /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes signedness: 
    See @ref Fls_c_REF_2 */
    if(interleavedBlock)
    {
        /* verify that EHV may be set */
        /** @note Violates MISRA-C:2004 Advisory Rule 12.4, Side effects on right hand of logical 
        operator: See @ref Fls_c_REF_9 */
        /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
        (&&, || and !) should be effectively Boolean: See @ref Fls_c_REF_13 */
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        if( ( (Fls_LLD_B1regBasePtr[FLASHMEM_MCR] & (MCR_ERS|MCR_PGM|MCR_ESUS)) != 0UL ) || \
                ( (Fls_LLD_B1regBasePtr[FLASHMEM_UT0] & (UT0_AIE)) != 0UL ))
        {   
            /*  EHV may not be set: modify operation already in progress */
            Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_ERASE_FAILED, DEM_EVENT_STATUS_FAILED);
            /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of function:
            See @ref Fls_c_REF_11 */
            return FLS_LLD_E_FAILED;
        }    
    }

    /* verify that sector is not protected against erase/program operations */
    /** @note Violates MISRA-C:2004 Advisory Rule 12.4, Side effects on right hand of logical operator:
    See @ref Fls_c_REF_9 */
    /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
    (&&, || and !) should be effectively Boolean: See @ref Fls_c_REF_13 */
    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed form
    of pointer arithmetic: See @ref Fls_c_REF_15 */
    if( ( (Fls_LLD_regBasePtr[bloPrimLockRegOffset] & bloLockValue) != 0UL ) || \
       ((Fls_LLD_regBasePtr[bloSecoLockRegOffset] & bloLockValue) != 0UL ))
    {
        /* sector protected: erase operation failed */
        Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_ERASE_FAILED, DEM_EVENT_STATUS_FAILED);
        /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of 
        function: See @ref Fls_c_REF_11 */
        return FLS_LLD_E_FAILED;
    }
    
    /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes signedness: 
    See @ref Fls_c_REF_2 */
    if(interleavedBlock)
    {
        /* verify that sector is not protected against erase/program operations */
        /** @note Violates MISRA-C:2004 Advisory Rule 12.4, Side effects on right hand of logical 
        operator: See @ref Fls_c_REF_9 */
        /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
        (&&, || and !) should be effectively Boolean: See @ref Fls_c_REF_13 */
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
        form of pointer arithmetic: See @ref Fls_c_REF_15 */       
        if( ( (Fls_LLD_B1regBasePtr[bloPrimLockRegOffset] & bloLockValue) != 0UL ) || \
                ( ( (Fls_LLD_B1regBasePtr[bloSecoLockRegOffset] & bloLockValue)) != 0UL ) )
        {
            /* sector protected: erase operation failed */
            Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_ERASE_FAILED, DEM_EVENT_STATUS_FAILED);
            /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of 
            function: See @ref Fls_c_REF_11 */
            return FLS_LLD_E_FAILED;
        }    
    }

    /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes signedness: See 
    @ref Fls_c_REF_2 */
    /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
    (&&, || and !) should be effectively Boolean: See @ref Fls_c_REF_13 */
    if (!asynch)
    {
        /* setup erase operation */
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        Fls_LLD_regBasePtr[FLASHMEM_MCR] |= MCR_ERS;
        /* load adequate block select register */
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        Fls_LLD_regBasePtr[bloSelRegOffset] = bloSelValue;
        /* make an erase interlock write, dummy data word write */
        *Fls_LLD_targetAddressPtr = 0xFFFFFFFFU;
    
        /* start critical section: implementation depends on integrator */
        SchM_Enter_Fls(SCHM_FLS_INSTANCE_0, FLS_EXCLUSIVE_AREA_00);
        
        /* back-up PFCR0 or PFCR1 */
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        Fls_LLD_pfcConfRegValue = Fls_LLD_pfcRegBasePtr[Fls_LLD_pfcConfRegOffset];
        timerCounterAC = SET_TIMEOUT_COUNTER_TO_ZERO;    
        /* call flash access code routine */
        Fls_ConfigPtr->acErasePtr(Fls_LLD_regBasePtr, Fls_ConfigPtr->acCallBackPtr, &timerCounterAC);
    
        if (ERASE_TIMEOUT_COUNTER <= timerCounterAC)
        {
            /* Timeout happened */
            Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
            /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of 
                function: See @ref Fls_c_REF_11 */
            Fls_LLD_Job = FLS_LLD_JOB_NONE;
            Fls_LLD_JobResult = MEMIF_JOB_FAILED; 
        }    

        /* invalidate PFC page buffers associated with modified memory bank */
        /* restore PFCR0 or PFCR1 */
        Fls_InvalidRestore((uint32) Fls_LLD_pfcConfRegOffset, \
         (uint32) Fls_LLD_pfcConfRegInvalValue, (uint32) Fls_LLD_pfcConfRegValue);

        /* end critical section: implementation depends on integrator */
        SchM_Exit_Fls (SCHM_FLS_INSTANCE_0, FLS_EXCLUSIVE_AREA_00);
    
        /* verify that erase operation was successful */
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        if(Fls_LLD_regBasePtr[FLASHMEM_MCR] & MCR_PEG)
        {
            /* disable high voltage */
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_EHV);
            /* terminate erase operation */
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_ERS);
            /* clear adequate block select register */
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            Fls_LLD_regBasePtr[bloSelRegOffset] = 0U;   
            /* erase operation succeed */
            /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes signedness:
            See @ref Fls_c_REF_2 */
            B0OperResult = TRUE;
        }
        else
        {
            /* disable high voltage */
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_EHV);
            /* terminate erase operation */
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_ERS);
            /* clear adequate block select register */
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            Fls_LLD_regBasePtr[bloSelRegOffset] = 0U;
            /* erase operation failed */
            Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_ERASE_FAILED, DEM_EVENT_STATUS_FAILED);
            /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of 
            function: See @ref Fls_c_REF_11 */
            return FLS_LLD_E_FAILED;
        }    
        
        /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes signedness: 
        See @ref Fls_c_REF_2 */
        if(interleavedBlock)
        {
            /* setup erase operation */
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            Fls_LLD_B1regBasePtr[FLASHMEM_MCR] |= MCR_ERS;
            /* load adequate block select register */
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            Fls_LLD_B1regBasePtr[bloSelRegOffset] = bloSelValue;
            /* make an erase interlock write, dummy data word write */
            *B1targetAddressPtr = 0xFFFFFFFFU;
        
            /* start critical section: implementation depends on integrator */
            SchM_Enter_Fls(SCHM_FLS_INSTANCE_0, FLS_EXCLUSIVE_AREA_01);
            
            /* back-up PFCR0 or PFCR1 */
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            Fls_LLD_pfcConfRegValue = Fls_LLD_pfcRegBasePtr[Fls_LLD_pfcConfRegOffset];
            timerCounterAC = SET_TIMEOUT_COUNTER_TO_ZERO;        
            /* call flash access code routine */
            Fls_ConfigPtr->acErasePtr(Fls_LLD_B1regBasePtr, Fls_ConfigPtr->acCallBackPtr, &timerCounterAC);
        
            if (ERASE_TIMEOUT_COUNTER <= timerCounterAC)
            {
                /* Timeout happened */
                Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
                /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of 
                    function: See @ref Fls_c_REF_11 */
                Fls_LLD_Job = FLS_LLD_JOB_NONE;
                Fls_LLD_JobResult = MEMIF_JOB_FAILED; 
            }        
        
            /* invalidate PFC page buffers associated with modified memory bank */
            /* restore PFCR0 or PFCR1 */
            Fls_InvalidRestore((uint32) Fls_LLD_pfcConfRegOffset, \
              (uint32) Fls_LLD_pfcConfRegInvalValue, (uint32) Fls_LLD_pfcConfRegValue);

      
            /* end critical section: implementation depends on integrator */
            SchM_Exit_Fls (SCHM_FLS_INSTANCE_0, FLS_EXCLUSIVE_AREA_01);
        
            /* verify that erase operation was successful */
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            if(Fls_LLD_B1regBasePtr[FLASHMEM_MCR] & MCR_PEG)
            {
                /* disable high voltage */
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                Fls_LLD_B1regBasePtr[FLASHMEM_MCR] &= (~MCR_EHV);
                /* terminate erase operation */
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                Fls_LLD_B1regBasePtr[FLASHMEM_MCR] &= (~MCR_ERS);
                /* clear adequate block select register */
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                Fls_LLD_B1regBasePtr[bloSelRegOffset] = 0U;
                /* erase operation succeed */
                /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes 
                signedness: See @ref Fls_c_REF_2 */
                B1OperResult = TRUE;
            }
            else
            {
                /* disable high voltage */
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                Fls_LLD_B1regBasePtr[FLASHMEM_MCR] &= (~MCR_EHV);
                /* terminate erase operation */
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                Fls_LLD_B1regBasePtr[FLASHMEM_MCR] &= (~MCR_ERS);
                /* clear adequate block select register */
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                Fls_LLD_B1regBasePtr[bloSelRegOffset] = 0U;
                /* erase operation failed */
                Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_ERASE_FAILED, DEM_EVENT_STATUS_FAILED);
                /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of 
                function: See @ref Fls_c_REF_11 */
                return FLS_LLD_E_FAILED;
            }            
        }
        else
        {
            /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes 
            signedness: See @ref Fls_c_REF_2 */
            B1OperResult = TRUE;
        }
        
        /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes signedness: 
        See @ref Fls_c_REF_2 */
        /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
        (&&, || and !) should be effectively Boolean: See @ref Fls_c_REF_13 */
        if((B0OperResult) && (B1OperResult))
        {
#if( FLS_ERASE_BLANK_CHECK == STD_ON )
            if( FLS_LLD_E_OK != Fls_LLD_VerifyErase(Fls_LLD_targetAddressPtr, physicalSectorSize) )
            {
                /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of 
                function: See @ref Fls_c_REF_11 */
                return FLS_LLD_E_FAILED;
            }
#endif    /* FLS_ERASE_BLANK_CHECK == STD_ON */


            /* erase operation succeed */
            /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of 
            function: See @ref Fls_c_REF_12 */
            return FLS_LLD_E_OK;
        }
        else
        {
            /* erase operation failed */
            Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_ERASE_FAILED, DEM_EVENT_STATUS_FAILED);
            /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of 
            function: See @ref Fls_c_REF_11 */
            return FLS_LLD_E_FAILED;
        }
    }
    else /* asynch == TRUE */
    {
        /* setup erase operation */
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed 
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        Fls_LLD_regBasePtr[FLASHMEM_MCR] |= MCR_ERS;
        /* load adequate block select register */
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed 
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        Fls_LLD_regBasePtr[bloSelRegOffset] = bloSelValue;
        /* make an erase interlock write, dummy data word write */
        *Fls_LLD_targetAddressPtr = 0xFFFFFFFFU;
        
        /* back-up PFCR0 or PFCR1 */
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed 
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        Fls_LLD_pfcConfRegValue = Fls_LLD_pfcRegBasePtr[Fls_LLD_pfcConfRegOffset];
        
        /* start internal erase/program sequence */
         /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed 
         form of pointer arithmetic: See @ref Fls_c_REF_15 */
         Fls_LLD_regBasePtr[FLASHMEM_MCR] |= MCR_EHV;
        
        Fls_LLD_Job = FLS_LLD_JOB_ERASE;
        Fls_LLD_JobResult = MEMIF_JOB_PENDING;
        /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of function: 
        See @ref Fls_c_REF_12 */
        return FLS_LLD_E_PENDING;                
    }
}

/** 
    @brief Write one or more complete flash pages into given flash sector

    @param[in] phySector Physical sector ID
    @param[in] sectorOffset sector offset in bytes
    @param[in] dataLength data length in bytes
    @param[in] dataPtr data to be written
    @param[in] asynch set to TRUE for asynchronous and FALSE for synchronous 
        function operation
    
    @return Fls_LLD_ReturnType
    @retval FLS_LLD_E_OK Operation succeeded
    @retval FLS_LLD_E_FAILED Operation failed due to hardware error    
    @retval FLS_LLD_E_PENDING The operation has not yet been finished 
        (only for asynchronous operation )
        
    @pre sectorOffset must be double word aligned
    @pre dataLength must be multiple double word length
    @pre phySector must be in range
    @pre The module must be initialized
    
    @remarks Dem_ReportErrorStatus(FLS_E_WRITE_FAILED, DEM_EVENT_STATUS_FAILED)
        when write operation failed due to hardware error        
    
    @remarks Implements DFLS31101
*/
STATIC FUNC(Fls_LLD_ReturnType, FLS_CODE) Fls_LLD_SectorWrite
(
    CONST( Fls_LLD_PhysicalSectorType, FLS_CONST) phySector,
    CONST(Fls_AddressType, FLS_CONST) sectorOffset,
    CONST(Fls_LengthType, FLS_CONST) dataLength,
    CONSTP2CONST(uint8, AUTOMATIC, FLS_APPL_DATA) dataPtr,
    CONST( boolean, FLS_CONST) asynch
)
{
    VAR(uint8, AUTOMATIC) bloPrimLockRegOffset = \
    flsLLDSectorList0[phySector].addrSpaceBloPrimLockRegOffset;
    VAR(uint8, AUTOMATIC) bloSecoLockRegOffset = \
    flsLLDSectorList0[phySector].addrSpaceBloSecoLockRegOffset;
    VAR(uint32, AUTOMATIC) bloLockValue = flsLLDSectorList0[phySector].addrSpaceBloLockValue;
    VAR(boolean, AUTOMATIC) interleavedBlock = flsLLDSectorList0[phySector].interleavedBlo;
    VAR(uint32, AUTOMATIC) interleavedSize = flsLLDSectorList0[phySector].interleavedSize;
    VAR(Fls_LengthType, AUTOMATIC) verifyBackLength = 1U;
    VAR(volatile uint32, AUTOMATIC) timerCounterAC = SET_TIMEOUT_COUNTER_TO_ZERO;
    
    /** @note Violates MISRA-C:2004 Advisory Rule 11.4, Cast from pointer to pointer: 
    See @ref Fls_c_REF_4 */
    Fls_LLD_sourceAddressPtr = (const uint32*)(dataPtr);
    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed form 
    of pointer arithmetic: See @ref Fls_c_REF_15 */
    Fls_LLD_targetAddressPtr = flsLLDSectorList0[phySector].sectorStartAddressPtr + \
                               (sectorOffset/4U);
    Fls_LLD_regBasePtr = flsLLDSectorList0[phySector].memArrayRegBasePtr;
    /** @note Violates MISRA-C:2004 Advisory Rule 11.3, Cast from unsigned long to pointer: 
    See @ref Fls_c_REF_6 */
    /** @note Violates MISRA-C:2004 Advisory Rule 11.1, Conversions between a pointer to a function: 
    See @ref Fls_c_REF_14 */
    Fls_LLD_pfcRegBasePtr = (volatile uint32*)(FLASHMEM0_PFC0_BASEADDR);
    Fls_LLD_pfcConfRegOffset = flsLLDSectorList0[phySector].platformFlashConfRegOffset;
    Fls_LLD_pfcConfRegInvalValue = flsLLDSectorList0[phySector].platformFlashConfInvalValue;
    Fls_LLD_B1regBasePtr = flsLLDSectorList0[phySector].memArrayB1RegBasePtr;

    Fls_LLD_pfcConfRegValue = 0U;

    /* one program operation = double word program (i.e.64bits=8bytes) \
       or word program (i.e.32bits=4bytes) */
    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed 
    form of pointer arithmetic: See @ref Fls_c_REF_15 */
    Fls_LLD_doubleWordToCopy = dataLength/Fls_ConfigPtr->sectorPageSize[Fls_JobSectorIt];
    Fls_LLD_programCycle = 0U;

    /* verify that EHV may be set */
    /** @note Violates MISRA-C:2004 Advisory Rule 12.4, Side effects on right hand of logical 
    operator: See @ref Fls_c_REF_9 */
    /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
    (&&, || and !) should be effectively Boolean: See @ref Fls_c_REF_13 */
    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed form
    of pointer arithmetic: See @ref Fls_c_REF_15 */
    if( ( (Fls_LLD_regBasePtr[FLASHMEM_MCR] & (MCR_ERS|MCR_PGM|MCR_ESUS)) != 0UL ) || \
         ((Fls_LLD_regBasePtr[FLASHMEM_UT0] & (UT0_AIE)) !=0UL ))
    {
        /*  EHV may not be set: modify operation already in progress */
        Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_WRITE_FAILED, DEM_EVENT_STATUS_FAILED);
        /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of function: 
        See @ref Fls_c_REF_11 */
        return FLS_LLD_E_FAILED;
    }

    /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes signedness: 
    See @ref Fls_c_REF_2 */
    if(interleavedBlock)
    {
        /* verify that EHV may be set */
        /** @note Violates MISRA-C:2004 Advisory Rule 12.4, Side effects on right hand of logical 
        operator: See @ref Fls_c_REF_9 */
        /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
        (&&, || and !) should be effectively Boolean: See @ref Fls_c_REF_13 */
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed 
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        if( ( (Fls_LLD_B1regBasePtr[FLASHMEM_MCR] & (MCR_ERS|MCR_PGM|MCR_ESUS)) != 0UL ) || \
                ( (Fls_LLD_B1regBasePtr[FLASHMEM_UT0] & (UT0_AIE)) != 0UL ))
        {
            /*  EHV may not be set: modify operation already in progress */
            Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_WRITE_FAILED, DEM_EVENT_STATUS_FAILED);
            /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of 
            function: See @ref Fls_c_REF_11 */
            return FLS_LLD_E_FAILED;
        }    
    }    
    
    /* verify that sector is not protected against erase/program operations */
    /** @note Violates MISRA-C:2004 Advisory Rule 12.4, Side effects on right hand of logical 
    operator: See @ref Fls_c_REF_9 */
    /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
    (&&, || and !) should be effectively Boolean: See @ref Fls_c_REF_13 */
    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed 
    form of pointer arithmetic: See @ref Fls_c_REF_15 */
    if( ( (Fls_LLD_regBasePtr[bloPrimLockRegOffset] & bloLockValue) != 0UL ) || \
       ((Fls_LLD_regBasePtr[bloSecoLockRegOffset] & bloLockValue) != 0UL ))
    {
        /* sector protected: program operation failed */
        Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_WRITE_FAILED, DEM_EVENT_STATUS_FAILED);
        /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of function: 
        See @ref Fls_c_REF_11 */
        return FLS_LLD_E_FAILED;
    }
    
    /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes signedness: 
    See @ref Fls_c_REF_2 */
    if(interleavedBlock)
    {
        /* verify that sector is not protected against erase/program operations */
        /** @note Violates MISRA-C:2004 Advisory Rule 12.4, Side effects on right hand of logical 
        operator: See @ref Fls_c_REF_9 */
        /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
        (&&, || and !) should be effectively Boolean: See @ref Fls_c_REF_13 */
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        if( ( (Fls_LLD_B1regBasePtr[bloPrimLockRegOffset] & bloLockValue) != 0UL ) || \
                ( ( (Fls_LLD_B1regBasePtr[bloSecoLockRegOffset] & bloLockValue)) != 0UL ) )
        {
            /* sector protected: erase operation failed */
            Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_WRITE_FAILED, DEM_EVENT_STATUS_FAILED);
            /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of 
            function: See @ref Fls_c_REF_11 */
            return FLS_LLD_E_FAILED;
        }    
    }    

    /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes signedness: 
    See @ref Fls_c_REF_2 */
    /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
    (&&, || and !) should be effectively Boolean: See @ref Fls_c_REF_13 */
    if (!asynch)
    {
        /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes signedness: 
        See @ref Fls_c_REF_2 */
        /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators 
        (&&, || and !) should be effectively Boolean: See @ref Fls_c_REF_13 */
        if(!interleavedBlock)
        {
            /* setup program operation */
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            Fls_LLD_regBasePtr[FLASHMEM_MCR] |= MCR_PGM;
        
            /* process all double word program operations */
            for( Fls_LLD_programCycle=0U; Fls_LLD_programCycle < Fls_LLD_doubleWordToCopy; \
                 Fls_LLD_programCycle++ )
            {
#if( FLS_WRITE_BLANK_CHECK == STD_ON )                
                if( FLS_LLD_E_OK != Fls_LLD_VerifyErase(Fls_LLD_targetAddressPtr, \
                    Fls_ConfigPtr->sectorPageSize[Fls_JobSectorIt]) )
                {
                    /* terminate program operation */
                    Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_PGM);
                    /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end 
                    of function: See @ref Fls_c_REF_11 */
                    return FLS_LLD_E_FAILED;                
                }
#endif    /* FLS_WRITE_BLANK_CHECK == STD_ON */                

                /* make a program data interlock write, first word data write */
                *Fls_LLD_targetAddressPtr = *Fls_LLD_sourceAddressPtr;
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                Fls_LLD_targetAddressPtr += 1;
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                Fls_LLD_sourceAddressPtr += 1;
                
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                if ( (uint8)FLS_PAGE_SIZE_08 == Fls_ConfigPtr->sectorPageSize[Fls_JobSectorIt] )
                {
                    /* make a program data write, second word data write */
                    *Fls_LLD_targetAddressPtr = *Fls_LLD_sourceAddressPtr;
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_LLD_targetAddressPtr += 1;
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_LLD_sourceAddressPtr += 1;
                    verifyBackLength += 1U;
                }
                /* start critical section: implementation depends on integrator */
                SchM_Enter_Fls(SCHM_FLS_INSTANCE_0, FLS_EXCLUSIVE_AREA_02);
                
                /* back-up PFCR0 or PFCR1 */
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                Fls_LLD_pfcConfRegValue = Fls_LLD_pfcRegBasePtr[Fls_LLD_pfcConfRegOffset];
                timerCounterAC = SET_TIMEOUT_COUNTER_TO_ZERO;                
                /* call flash access code routine */
                Fls_ConfigPtr->acWritePtr(Fls_LLD_regBasePtr, Fls_ConfigPtr->acCallBackPtr, &timerCounterAC);
                
                if (WRITE_TIMEOUT_COUNTER <= timerCounterAC)
                {
                    /* Timeout happened */
                    Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
                    /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of 
                        function: See @ref Fls_c_REF_11 */
                    Fls_LLD_Job = FLS_LLD_JOB_NONE;
                    Fls_LLD_JobResult = MEMIF_JOB_FAILED;  
                }                
                
                /* invalidate PFC page buffers associated with modified memory bank */
                /* restore PFCR0 or PFCR1 */
                Fls_InvalidRestore((uint32) Fls_LLD_pfcConfRegOffset, \
                  (uint32) Fls_LLD_pfcConfRegInvalValue, (uint32) Fls_LLD_pfcConfRegValue);
                
                /* end critical section: implementation depends on integrator */
                SchM_Exit_Fls (SCHM_FLS_INSTANCE_0, FLS_EXCLUSIVE_AREA_02);
        
                /* verify that program operation was successful */
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                if(Fls_LLD_regBasePtr[FLASHMEM_MCR] & MCR_PEG)
                {
                    /* disable high voltage */
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_EHV);
#if( FLS_WRITE_VERIFY_CHECK == STD_ON )                    
                    if( FLS_LLD_E_OK != Fls_LLD_VerifyWrite( Fls_LLD_targetAddressPtr - \
                        verifyBackLength, Fls_LLD_sourceAddressPtr - verifyBackLength, \
                        Fls_ConfigPtr->sectorPageSize[Fls_JobSectorIt] ) )
                    {
                        /* terminate program operation */
                        Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_PGM);
                        /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before 
                        end of function: See @ref Fls_c_REF_11 */
                        return FLS_LLD_E_FAILED;
                    }
#endif    /* FLS_WRITE_VERIFY_CHECK == STD_ON */                    

                    /* program operation succeed */
                    /* continue with next double word program operation */
                }
                else
                {
                    /* disable high voltage */
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_EHV);
                    /* terminate program operation */
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_PGM);
                    /* program operation failed */
                    Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_WRITE_FAILED, DEM_EVENT_STATUS_FAILED);
                    /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end 
                    of function: See @ref Fls_c_REF_11 */
                    return FLS_LLD_E_FAILED;
                }
            }
            
            /* all double word program operations succeed */
            /* terminate program operation */    
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_PGM);
            /* program operation succeed */
            /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of 
            function: See @ref Fls_c_REF_12 */
            return FLS_LLD_E_OK;
        }
        else
        {
            /* interleavedBlock == TRUE */

            /* process all double word program operations */
            for( Fls_LLD_programCycle=0U; Fls_LLD_programCycle < Fls_LLD_doubleWordToCopy; \
                 Fls_LLD_programCycle++ )
            {
                /* update Fls_LLD_regBasePtr based on targetAddress Bank */
                /** @note Violates MISRA-C:2004 Advisory Rule 11.3, Cast from pointer to unsigned 
                long: See @ref Fls_c_REF_7 */
               /** @note Violates MISRA-C:2004 Advisory Rule 11.1, Conversions between a pointer to 
               a function: See @ref Fls_c_REF_14 */
                if(((uint32)Fls_LLD_targetAddressPtr) & interleavedSize)
                {
                    /* it is Bank1 */
                    Fls_LLD_regBasePtr = flsLLDSectorList0[phySector].memArrayB1RegBasePtr;
                }
                else
                {
                    /* it is Bank0 */
                    Fls_LLD_regBasePtr = flsLLDSectorList0[phySector].memArrayRegBasePtr;
                }
                
                /* setup program operation */
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                Fls_LLD_regBasePtr[FLASHMEM_MCR] |= MCR_PGM;
                
#if( FLS_WRITE_BLANK_CHECK == STD_ON )                
                if(FLS_LLD_E_OK != Fls_LLD_VerifyErase(Fls_LLD_targetAddressPtr, \
                                                 (Fls_LengthType)FLS_PAGE_SIZE_08))
                {
                    /* terminate program operation */
                    Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_PGM);
                    /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end 
                    of function: See @ref Fls_c_REF_11 */
                    return FLS_LLD_E_FAILED;                
                }
#endif    /* FLS_WRITE_BLANK_CHECK == STD_ON */                

                /* make a program data interlock write, first word data write */
                *Fls_LLD_targetAddressPtr = *Fls_LLD_sourceAddressPtr;
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                Fls_LLD_targetAddressPtr += 1;
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                Fls_LLD_sourceAddressPtr += 1;

                /* Data Flash Optimized has no interleaved sectors, write always double word */
                /* make a program data write, second word data write */
                *Fls_LLD_targetAddressPtr = *Fls_LLD_sourceAddressPtr;
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                Fls_LLD_targetAddressPtr += 1;
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                Fls_LLD_sourceAddressPtr += 1;
        
                /* start critical section: implementation depends on integrator */
                SchM_Enter_Fls(SCHM_FLS_INSTANCE_0, FLS_EXCLUSIVE_AREA_03);
                
                /* back-up PFCR0 or PFCR1 */
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                Fls_LLD_pfcConfRegValue = Fls_LLD_pfcRegBasePtr[Fls_LLD_pfcConfRegOffset];
                timerCounterAC = SET_TIMEOUT_COUNTER_TO_ZERO;
                /* call flash access code routine */
                Fls_ConfigPtr->acWritePtr(Fls_LLD_regBasePtr, Fls_ConfigPtr->acCallBackPtr, &timerCounterAC);
                
                if (WRITE_TIMEOUT_COUNTER <= timerCounterAC)
                {
                    /* Timeout happened */
                    Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
                    /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of 
                        function: See @ref Fls_c_REF_11 */
                    Fls_LLD_Job = FLS_LLD_JOB_NONE;
                    Fls_LLD_JobResult = MEMIF_JOB_FAILED;        
                }                
                
                /* invalidate PFC page buffers associated with modified memory bank */
                /* restore PFCR0 or PFCR1 */
                Fls_InvalidRestore((uint32) Fls_LLD_pfcConfRegOffset, \
                  (uint32) Fls_LLD_pfcConfRegInvalValue, (uint32) Fls_LLD_pfcConfRegValue);
                
                /* end critical section: implementation depends on integrator */
                SchM_Exit_Fls (SCHM_FLS_INSTANCE_0, FLS_EXCLUSIVE_AREA_03);
        
                /* verify that program operation was successful */
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only
                allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                if(Fls_LLD_regBasePtr[FLASHMEM_MCR] & MCR_PEG)
                {
                    /* disable high voltage */
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_EHV);
                    /* terminate program operation */
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_PGM);

#if( FLS_WRITE_VERIFY_CHECK == STD_ON )                    
                    if( FLS_LLD_E_OK != Fls_LLD_VerifyWrite( Fls_LLD_targetAddressPtr - \
                                                        (FLS_LLD_DATA_BUS_WIDTH_TYPE)2, \
                                                              Fls_LLD_sourceAddressPtr - \
                                                         (FLS_LLD_DATA_BUS_WIDTH_TYPE)2, \
                                                      (Fls_LengthType)FLS_PAGE_SIZE_08 ) )
                    {
                        /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before 
                        end of function: See @ref Fls_c_REF_11 */
                        return FLS_LLD_E_FAILED;
                    }
#endif    /* FLS_WRITE_VERIFY_CHECK == STD_ON */                    

                    /* program operation succeed */
                    /* continue with next double word program operation */
                }
                else
                {
                    /* disable high voltage */
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_EHV);
                    /* terminate program operation */
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the 
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_PGM);
                    /* program operation failed */
                    Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_WRITE_FAILED, DEM_EVENT_STATUS_FAILED);
                    /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end 
                    of function: See @ref Fls_c_REF_11 */
                    return FLS_LLD_E_FAILED;
                }
            }

            /* all double word program operations succeed */
            /* program operation succeed */
            /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of 
            function: See @ref Fls_c_REF_12 */
            return FLS_LLD_E_OK;
        }
    }
    else /* asynch == TRUE */
    {
        if(interleavedBlock)
        {
            /* update Fls_LLD_regBasePtr based on targetAddress Bank */
            /** @note Violates MISRA-C:2004 Advisory Rule 11.1, Conversions between a pointer to a 
            function: See @ref Fls_c_REF_14 */
            if(((uint32)Fls_LLD_targetAddressPtr) & interleavedSize)
            {
                /* it is Bank1 */
                Fls_LLD_regBasePtr = flsLLDSectorList0[phySector].memArrayB1RegBasePtr;
            }
            else
            {
                /* it is Bank0 */
                Fls_LLD_regBasePtr = flsLLDSectorList0[phySector].memArrayRegBasePtr;
            }
        }    
        /* setup program operation */
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        Fls_LLD_regBasePtr[FLASHMEM_MCR] |= MCR_PGM;
        
        /* first double word program operation */
        Fls_LLD_programCycle=0U;
        
#if( FLS_WRITE_BLANK_CHECK == STD_ON )        
        if( FLS_LLD_E_OK != Fls_LLD_VerifyErase(Fls_LLD_targetAddressPtr, \
            Fls_ConfigPtr->sectorPageSize[Fls_JobSectorIt]) )
        {
            /* terminate program operation */
            Fls_LLD_regBasePtr[FLASHMEM_MCR] &= (~MCR_PGM);
            /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of 
            function: See @ref Fls_c_REF_11 */
            return FLS_LLD_E_FAILED;                
        }
#endif    /* FLS_WRITE_BLANK_CHECK == STD_ON */        

        /* make a program data interlock write, first word data write */
        *Fls_LLD_targetAddressPtr = *Fls_LLD_sourceAddressPtr;
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed 
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        Fls_LLD_targetAddressPtr += 1;
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        Fls_LLD_sourceAddressPtr += 1;
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed 
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        if ( (uint8)FLS_PAGE_SIZE_08 == Fls_ConfigPtr->sectorPageSize[Fls_JobSectorIt] )
        {
            /* make a program data write, second word data write */
            *Fls_LLD_targetAddressPtr = *Fls_LLD_sourceAddressPtr;
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            Fls_LLD_targetAddressPtr += 1;
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
            allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            Fls_LLD_sourceAddressPtr += 1;
        }
        
        /* back-up PFCR0 or PFCR1 */
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        Fls_LLD_pfcConfRegValue = Fls_LLD_pfcRegBasePtr[Fls_LLD_pfcConfRegOffset];
        
        /* start internal erase/program sequence */
         /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
         form of pointer arithmetic: See @ref Fls_c_REF_15 */
         Fls_LLD_regBasePtr[FLASHMEM_MCR] |= MCR_EHV;
         
         /* one double word program operation already initiated */
        Fls_LLD_programCycle++;
         
        Fls_LLD_Job = FLS_LLD_JOB_WRITE;
        Fls_LLD_JobResult = MEMIF_JOB_PENDING;
        /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of function:
        See @ref Fls_c_REF_12 */
        return FLS_LLD_E_PENDING;
    }
}

/** 
    @brief Calculate length of initial 8-bit flash read
    
    @details Calculate number of bytes to read from flash until
        the source pointer is aligned to the data  width and
        optimized wide (32-bit or 64-bit) flash reads can begin
    
    @param[in] SourceAddrPtr Source pointer
    @param[in] TotalBytes Total number of bytes to read
    
    @retval length of initial 8-bit flash reads in bytes
*/
STATIC FUNC( uint32, FLS_CODE ) Fls_LLD_CalcInitDataLength( 
    CONSTP2CONST( uint8, AUTOMATIC, FLS_APPL_DATA ) volatile SourceAddrPtr,
    CONST(uint32, FLS_CONST) TotalBytes )
{
    /* Calc length of initial 8-bit transfer */
    /** @note Violates MISRA-C:2004 Advisory Rule 11.3, Cast from pointer to unsigned long: 
    See @ref Fls_c_REF_7 */
    VAR(uint32, AUTOMATIC) length = 
  /** @note Violates MISRA-C:2004 Advisory Rule 11.1, Conversions between a pointer to a function:
  See @ref Fls_c_REF_14 */
        ( (uint32)SourceAddrPtr ) & ( sizeof(FLS_LLD_DATA_BUS_WIDTH_TYPE) - 1UL );
    
    if ( length != 0U )
    {
        length = sizeof(FLS_LLD_DATA_BUS_WIDTH_TYPE) - length;
    }
    else
    {
        /* length == 0 */
    }

    if( length > TotalBytes ) 
    {
        length = TotalBytes;
    }
    else
    {
        /* length <=  TotalBytes */
    }
    
    return length;
}

/** 
    @brief Calculate length of optimized wide flash reads
    
    @details Calculate number of bytes to read from flash until
        the source pointer is not aligned to the data bus width
    
    @param[in] InitDataLength Calculated by Fls_LLD_CalcInitDataLength
    @param[in] TotalBytes Total number of bytes to read
    
    @retval length of optimized 32-bit or 64-bit flash reads in bytes
*/
STATIC FUNC( uint32, FLS_CODE ) Fls_LLD_CalcWideDataLength(
    CONST(uint32, FLS_CONST) InitDataLength,
    CONST(uint32, FLS_CONST) TotalBytes )
{
    VAR(uint32, AUTOMATIC) length =
        (( TotalBytes - InitDataLength ) & (~( sizeof(FLS_LLD_DATA_BUS_WIDTH_TYPE) - 1UL )));

    return length;
}

/** 
    @brief Read one or more bytes from given flash sector

    @param[in] phySector Physical sector ID
    @param[in] sectorOffset sector offset in bytes
    @param[in] dataLength data length in bytes
    @param[out] dataPtr where read data to be written
    
    @return Fls_LLD_ReturnType
    @retval FLS_LLD_E_OK Operation succeeded

    @remarks Implements DFLS31102
*/
STATIC FUNC(Fls_LLD_ReturnType, FLS_CODE) Fls_LLD_SectorRead
(
    CONST( Fls_LLD_PhysicalSectorType, FLS_CONST) phySector,
    CONST(Fls_AddressType, FLS_CONST) sectorOffset,
    CONST(Fls_LengthType, FLS_CONST) dataLength,
    P2VAR(uint8, AUTOMATIC, FLS_APPL_DATA) dataPtr
)
{
    VAR(uint32, AUTOMATIC) initDataLength = 0UL;
    VAR(Fls_LLD_ReturnType, AUTOMATIC) RetVal = FLS_LLD_E_OK;
    P2CONST(uint8, AUTOMATIC, FLS_CODE) volatile readAddressEndPtr = NULL_PTR;
    P2CONST(uint8, AUTOMATIC, FLS_CODE) volatile readBlockAddressEndPtr = NULL_PTR;
    
    /* Physical flash address to read */
    /** @note Violates MISRA-C:2004 Advisory Rule 11.4, Cast from pointer to pointer: 
    See @ref Fls_c_REF_5 */
    /** @note Violates MISRA-C:2004 Advisory Rule 11.5 : See @ref Fls_c_REF_17 */
    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed form
    of pointer arithmetic: See @ref Fls_c_REF_15 */
    Fls_LLD_ReadAddressPtr = (const uint8 *)(flsLLDSectorList0[phySector].sectorStartAddressPtr) + \
                              sectorOffset;

    /* End of read pointer */
    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed form 
    of pointer arithmetic: See @ref Fls_c_REF_15 */
    readAddressEndPtr = Fls_LLD_ReadAddressPtr + dataLength;
    
    /* Calculate end address of initial 8-bit transfer */
    initDataLength = Fls_LLD_CalcInitDataLength( Fls_LLD_ReadAddressPtr, dataLength );
    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed form
    of pointer arithmetic: See @ref Fls_c_REF_15 */
    readBlockAddressEndPtr = Fls_LLD_ReadAddressPtr + initDataLength;

#if( FLS_DSI_HANDLER_API == STD_ON )
    Fls_LLD_ReadStatus = FLS_LLD_E_PENDING;
    
    /* Initial 8-bit flash read (until the data bus alignment boundary) */ 
    /** @note Violates MISRA-C:2004 Advisory Rule 1.2, Both sides have side effects.: 
    See @ref Fls_c_REF_10 */
    for( ; ( Fls_LLD_ReadAddressPtr != readBlockAddressEndPtr ) && \
       ( FLS_LLD_E_PENDING == Fls_LLD_ReadStatus ); Fls_LLD_ReadAddressPtr++)
#else
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        /** @note Violates MISRA-C:2004 Advisory Rule 1.2, Both sides have side effects.: See @ref Fls_c_REF_10 */
    for( ; Fls_LLD_ReadAddressPtr != readBlockAddressEndPtr; Fls_LLD_ReadAddressPtr++)
#endif    
    {
        *dataPtr = *Fls_LLD_ReadAddressPtr;
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed 
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        dataPtr++;
    }

    /* Calculate end address of wide 32-bit or 64-bit flash read */
    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed form 
    of pointer arithmetic: See @ref Fls_c_REF_15 */
    readBlockAddressEndPtr += Fls_LLD_CalcWideDataLength( initDataLength, dataLength );

    /* Data bus width transfer */    
    /** @note Violates MISRA-C:2004 Advisory Rule 1.2, Both sides have side effects.: See @ref Fls_c_REF_10 */
#if( FLS_DSI_HANDLER_API == STD_ON )
    for( ; ( Fls_LLD_ReadAddressPtr != readBlockAddressEndPtr ) && \
       ( FLS_LLD_E_PENDING == Fls_LLD_ReadStatus ); Fls_LLD_ReadAddressPtr += \
         sizeof(FLS_LLD_DATA_BUS_WIDTH_TYPE))
#else
        /** @note Violates MISRA-C:2004 Advisory Rule 1.2, Both sides have side effects.: See @ref Fls_c_REF_10 */
    for( ; Fls_LLD_ReadAddressPtr != readBlockAddressEndPtr; Fls_LLD_ReadAddressPtr += \
           /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
           allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
           sizeof(FLS_LLD_DATA_BUS_WIDTH_TYPE))
#endif    
    {
        /** @note Violates MISRA-C:2004 Advisory Rule 11.4, Cast from pointer to pointer: See @ref Fls_c_REF_4 */
        *((FLS_LLD_DATA_BUS_WIDTH_TYPE*)dataPtr) = \
        /** @note Violates MISRA-C:2004 Advisory Rule 11.5 : See @ref Fls_c_REF_17 */
        *((FLS_LLD_DATA_BUS_WIDTH_TYPE*)Fls_LLD_ReadAddressPtr);
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        dataPtr += sizeof(FLS_LLD_DATA_BUS_WIDTH_TYPE);
    }
    
    /* Final 8-bit transfer */
    /** @note Violates MISRA-C:2004 Advisory Rule 1.2, Both sides have side effects.: See @ref Fls_c_REF_10 */
#if( FLS_DSI_HANDLER_API == STD_ON )    
    for( ; ( Fls_LLD_ReadAddressPtr != readAddressEndPtr ) && \
       ( FLS_LLD_E_PENDING == Fls_LLD_ReadStatus ); Fls_LLD_ReadAddressPtr++)
#else
         /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed 
         form of pointer arithmetic: See @ref Fls_c_REF_15 */
        /** @note Violates MISRA-C:2004 Advisory Rule 1.2, Both sides have side effects.: 
        See @ref Fls_c_REF_10 */
    for( ; Fls_LLD_ReadAddressPtr != readAddressEndPtr; Fls_LLD_ReadAddressPtr++)
#endif    
    {
        *dataPtr = *Fls_LLD_ReadAddressPtr;
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        dataPtr++;
    }

#if( FLS_DSI_HANDLER_API == STD_ON )    
    if( FLS_LLD_E_PENDING == Fls_LLD_ReadStatus )
    {
        Fls_LLD_ReadStatus = FLS_LLD_E_OK;
    }
    else
    {
    
    }
    
    RetVal = Fls_LLD_ReadStatus;
#else
    RetVal = FLS_LLD_E_OK;
#endif    
    return RetVal;
}

/** 
    @brief Compare data buffer with content of given flash sector

    @param[in] phySector Physical sector ID
    @param[in] sectorOffset sector offset in bytes
    @param[in] dataLength data length in bytes
    @param[in] dataPtr data to be compared
    
    @return Fls_LLD_ReturnType
    @retval FLS_LLD_E_OK Operation succeeded
    @retval FLS_LLD_E_BLOCK_INCONSISTENT Data buffer doesn't match with content of flash sector

    @remarks Implements DFLS31103
*/
#if( FLS_COMPARE_API == STD_ON )
STATIC FUNC(Fls_LLD_ReturnType, FLS_CODE) Fls_LLD_SectorCompare
(
    CONST( Fls_LLD_PhysicalSectorType, FLS_CONST) phySector,
    CONST(Fls_AddressType, FLS_CONST) sectorOffset,
    CONST(Fls_LengthType, FLS_CONST) dataLength,
    CONSTP2CONST(uint8, AUTOMATIC, FLS_APPL_DATA) dataPtr
)
{
    VAR(uint32, AUTOMATIC) initDataLength = 0UL;
    P2CONST( uint8, AUTOMATIC, FLS_CODE ) volatile readAddressEndPtr = NULL_PTR;
    P2CONST( uint8, AUTOMATIC, FLS_CODE ) volatile readBlockAddressEndPtr = NULL_PTR;
    
    /* Physical flash address to read */
    /** @note Violates MISRA-C:2004 Advisory Rule 11.4, Cast from pointer to pointer: See @ref Fls_c_REF_5 */
    /** @note Violates MISRA-C:2004 Advisory Rule 11.5 : See @ref Fls_c_REF_17 */
    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed 
    form of pointer arithmetic: See @ref Fls_c_REF_15 */
    Fls_LLD_ReadAddressPtr = (const uint8 *)(flsLLDSectorList0[phySector].sectorStartAddressPtr) + \
                              sectorOffset;
    Fls_LLD_CompareAddressPtr = dataPtr;
    
    /* End of read pointer */
    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed 
    form of pointer arithmetic: See @ref Fls_c_REF_15 */
    readAddressEndPtr = Fls_LLD_ReadAddressPtr + dataLength;
    
    /* Calculate end address of initial 8-bit transfer */
    initDataLength = Fls_LLD_CalcInitDataLength( Fls_LLD_ReadAddressPtr, dataLength );
    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed 
    form of pointer arithmetic: See @ref Fls_c_REF_15 */
    readBlockAddressEndPtr = Fls_LLD_ReadAddressPtr + initDataLength;

#if( FLS_DSI_HANDLER_API == STD_ON )
    Fls_LLD_CompareStatus = FLS_LLD_E_PENDING;
    
    /* Initial 8-bit flash read (until the data bus alignment boundary) */ 
    /** @note Violates MISRA-C:2004 Advisory Rule 1.2, Both sides have side effects.: See @ref Fls_c_REF_10 */
    for( ; ( Fls_LLD_ReadAddressPtr != readBlockAddressEndPtr ) && \
       ( FLS_LLD_E_PENDING == Fls_LLD_CompareStatus ); Fls_LLD_ReadAddressPtr++ )
#else
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed 
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        /** @note Violates MISRA-C:2004 Advisory Rule 1.2, Both sides have side effects.: 
        See @ref Fls_c_REF_10 */
    for( ; Fls_LLD_ReadAddressPtr != readBlockAddressEndPtr; Fls_LLD_ReadAddressPtr++)
#endif    
    {
        /** @note Violates MISRA-C:2004 Advisory Rule 1.2, Both sides have side effects.: 
        See @ref Fls_c_REF_10 */
        if( *Fls_LLD_CompareAddressPtr != *Fls_LLD_ReadAddressPtr )
        {
#if( FLS_DSI_HANDLER_API == STD_ON )
            if( FLS_LLD_E_PENDING == Fls_LLD_CompareStatus )
            { 
                Fls_LLD_CompareStatus = FLS_LLD_E_BLOCK_INCONSISTENT;
            }
            else
            {
                /* FLS_LLD_E_PENDING != Fls_LLD_CompareStatus */
            }
#else
            /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of 
            function: See @ref Fls_c_REF_11 */
            return FLS_LLD_E_BLOCK_INCONSISTENT;
#endif            
        }
        else
        {
            /* *Fls_LLD_CompareAddressPtr == *Fls_LLD_ReadAddressPtr */
        }
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        Fls_LLD_CompareAddressPtr++;
    }

    /* Calculate end address of wide 32-bit or 64-bit flash read */
    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed form 
    of pointer arithmetic: See @ref Fls_c_REF_15 */
    readBlockAddressEndPtr += Fls_LLD_CalcWideDataLength( initDataLength, dataLength );

    /* Data bus width transfer */    
    /** @note Violates MISRA-C:2004 Advisory Rule 1.2, Both sides have side effects.: See @ref Fls_c_REF_10 */
#if( FLS_DSI_HANDLER_API == STD_ON )
    for( ; ( Fls_LLD_ReadAddressPtr != readBlockAddressEndPtr ) && \
       ( FLS_LLD_E_PENDING == Fls_LLD_CompareStatus ); Fls_LLD_ReadAddressPtr += \
         sizeof(FLS_LLD_DATA_BUS_WIDTH_TYPE))
#else
        /** @note Violates MISRA-C:2004 Advisory Rule 1.2, Both sides have side effects.: See @ref Fls_c_REF_10 */
    for( ; Fls_LLD_ReadAddressPtr != readBlockAddressEndPtr; Fls_LLD_ReadAddressPtr += \
         /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
         form of pointer arithmetic: See @ref Fls_c_REF_15 */
         sizeof(FLS_LLD_DATA_BUS_WIDTH_TYPE))
#endif    
    {
        /** @note Violates MISRA-C:2004 Advisory Rule 11.4, Cast from pointer to pointer: See @ref Fls_c_REF_4 */
        /** @note Violates MISRA-C:2004 Advisory Rule 1.2, Both sides have side effects.: See @ref Fls_c_REF_10 */
        /** @note Violates MISRA-C:2004 Advisory Rule 11.5 : See @ref Fls_c_REF_17 */
        if( *((FLS_LLD_DATA_BUS_WIDTH_TYPE*)Fls_LLD_CompareAddressPtr) != \
            *((FLS_LLD_DATA_BUS_WIDTH_TYPE*)Fls_LLD_ReadAddressPtr) )
        {
#if( FLS_DSI_HANDLER_API == STD_ON )
            if( FLS_LLD_E_PENDING == Fls_LLD_CompareStatus )
            { 
                Fls_LLD_CompareStatus = FLS_LLD_E_BLOCK_INCONSISTENT;
            }
            else
            {
                /* FLS_LLD_E_PENDING != Fls_LLD_CompareStatus */
            }
#else
            /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of 
            function: See @ref Fls_c_REF_11 */
            return FLS_LLD_E_BLOCK_INCONSISTENT;
#endif
        }
        else
        {
            /* *((FLS_LLD_DATA_BUS_WIDTH_TYPE*)Fls_LLD_CompareAddressPtr) = \
               *((FLS_LLD_DATA_BUS_WIDTH_TYPE*)Fls_LLD_ReadAddressPtr) */
        }
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only 
        allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
        Fls_LLD_CompareAddressPtr += sizeof(FLS_LLD_DATA_BUS_WIDTH_TYPE);
    }
    
    /* Final 8-bit transfer */
    /** @note Violates MISRA-C:2004 Advisory Rule 1.2, Both sides have side effects.: See @ref Fls_c_REF_10 */
#if( FLS_DSI_HANDLER_API == STD_ON )    
    for( ; ( Fls_LLD_ReadAddressPtr != readAddressEndPtr ) && \
           ( FLS_LLD_E_PENDING == Fls_LLD_CompareStatus ); Fls_LLD_ReadAddressPtr++)
#else
    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed 
    form of pointer arithmetic: See @ref Fls_c_REF_15 */
    /** @note Violates MISRA-C:2004 Advisory Rule 1.2, Both sides have side effects.: See @ref Fls_c_REF_10 */
    for( ; Fls_LLD_ReadAddressPtr != readAddressEndPtr; Fls_LLD_ReadAddressPtr++)
#endif    
    {
        /** @note Violates MISRA-C:2004 Advisory Rule 1.2, Both sides have side effects.: See @ref Fls_c_REF_10 */
        /** @note Violates MISRA-C:2004 Advisory Rule 1.2, Both sides have side effects.: See @ref Fls_c_REF_10 */
        if( *Fls_LLD_CompareAddressPtr != *Fls_LLD_ReadAddressPtr )
        {
#if( FLS_DSI_HANDLER_API == STD_ON )
            if( FLS_LLD_E_PENDING == Fls_LLD_CompareStatus )
            { 
                Fls_LLD_CompareStatus = FLS_LLD_E_BLOCK_INCONSISTENT;
            }
            else
            {
                /* FLS_LLD_E_PENDING != Fls_LLD_CompareStatus */
            }
#else
            /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of 
            function: See @ref Fls_c_REF_11 */
            return FLS_LLD_E_BLOCK_INCONSISTENT;
#endif
        }
        else
        {
            /* *Fls_LLD_CompareAddressPtr == *Fls_LLD_ReadAddressPtr */
        }
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        Fls_LLD_CompareAddressPtr++;
    }

#if( FLS_DSI_HANDLER_API == STD_ON )    
    if( FLS_LLD_E_PENDING == Fls_LLD_CompareStatus )
    {
        Fls_LLD_CompareStatus = FLS_LLD_E_OK;
    }
    else
    {
    
    }
    /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of function: 
    See @ref Fls_c_REF_11 */
    return Fls_LLD_CompareStatus;
#else
    /** @note Violates MISRA-C:2004 Advisory Rule 14.7, Return statement before end of function: 
    See @ref Fls_c_REF_11 */
    return FLS_LLD_E_OK;
#endif    
}
#endif /* FLS_COMPARE_API == STD_ON */

/** 
    @brief Low level data storage exception handler

    @details This function is called by the high level data storage exception 
        handler to determine whether the exception was (FLS_HANDLED_SKIP) or 
        was NOT (FLS_UNHANDLED) caused by currently pending flash read or 
        flash compare job. The functions sets the Fls_LLD_ReadStatus 
        (Fls_LLD_CompareStatus) status variable to FLS_LLD_E_FAILED in order to
        terminate (MEMIF_JOB_FAILED) currently pending flash read or flash 
        compare job.

    @param[in] ExceptionDetailsPtr Pointer to structure which holds effective
        address of a byte within the page whose access caused the violation and
        value of the exception syndrome register (hardware specific)
    
    @return Fls_CompHandlerReturnType
    @retval FLS_HANDLED_SKIP The data storage exception was 
        caused by currently pending flash read or compare job
    @retval FLS_UNHANDLED The data storage exception was 
        NOT caused by currently pending flash read or compare job
*/
#if( FLS_DSI_HANDLER_API == STD_ON )
FUNC( Fls_CompHandlerReturnType, FLS_CODE ) Fls_DsiHandler(
    P2CONST( Fls_ExceptionDetailsType, AUTOMATIC, FLS_APPL_DATA ) ExceptionDetailsPtr )
{
    VAR( Fls_CompHandlerReturnType, AUTOMATIC ) RetVal = FLS_UNHANDLED;

    /*     Check whether there is [1] pending read, compare, erase or write job, 
        [2] exception syndrome register indicates DSI reason, and [3] data_pt
        matches address currently accessed by pending flash read or flash 
        compare job */
    /** @note Violates MISRA-C:2004 Advisory Rule 12.4, Side effects on right hand of logical 
    operator: See @ref Fls_c_REF_9 */        
    if(( FLS_LLD_E_PENDING == Fls_LLD_ReadStatus ) && 
        ( FLS_LLD_DSI_EXC_SYNDROME == (ExceptionDetailsPtr->syndrome_u32 & \
          FLS_LLD_DSI_EXC_SYNDROME) ) && \
        ( ExceptionDetailsPtr->data_pt == Fls_LLD_ReadAddressPtr ))
    {
        Fls_LLD_ReadStatus = FLS_LLD_E_FAILED;
        RetVal = FLS_HANDLED_SKIP;
    }
    /** @note Violates MISRA-C:2004 Advisory Rule 12.4, Side effects on right hand of logical 
    operator: See @ref Fls_c_REF_9 */
    else if(( FLS_LLD_E_PENDING == Fls_LLD_CompareStatus ) && \
        ( FLS_LLD_DSI_EXC_SYNDROME == \
        (ExceptionDetailsPtr->syndrome_u32 & FLS_LLD_DSI_EXC_SYNDROME) ) && \
        (( ExceptionDetailsPtr->data_pt == Fls_LLD_ReadAddressPtr ) || \
        ( ExceptionDetailsPtr->data_pt == Fls_LLD_CompareAddressPtr )))
    {
        Fls_LLD_CompareStatus = FLS_LLD_E_FAILED;
        RetVal = FLS_HANDLED_SKIP;
    }
    else
    {
        /* FLS_UNHANDLED */
    }

    return RetVal;
}
#ifdef IPV_FLASH
    /* for XPC560XP, XPC560XB and XPC560XS platforms */
    #if ((IPV_FLASH == IPV_FLASH_C90FG_1024_2_0) || \
         (IPV_FLASH == IPV_FLASH_C90FG_512_2_9) || \
         (IPV_FLASH == IPV_FLASH_C90FG_256_1_4) || \
         (IPV_FLASH == IPV_FLASH_C90FG_544_2_9_65) || \
         (IPV_FLASH == IPV_FLASH_C90FG_1568_2_6_69) || \
         (IPV_FLASH == IPV_FLASH_C90FG_256_1_4_D) || \
         (IPV_FLASH == IPV_FLASH_C90FG_1024_2_6_E) || \
         (IPV_FLASH == IPV_FLASH_C90FL_640_34_61))

    FUNC( Fls_CompHandlerReturnType, FLS_CODE ) Fls_MciHandler(
        P2CONST( Fls_ExceptionDetailsType, AUTOMATIC, FLS_APPL_DATA ) ExceptionDetailsPtr )
    {
        VAR( Fls_CompHandlerReturnType, AUTOMATIC ) RetVal = FLS_UNHANDLED;

        /*  In case of IVOR1 on Z0 check whether there is:
            [1] pending read, compare, erase or write job, 
            [2] exception syndrome register indicates DSI reason, and 
            [3] data_pt matches address currently accessed by pending flash read or flash compare job 
            [-] There is NO MCAR nor DEAR special register so address currently accessed can be taken 
                from Platform Flash ECC Address Register (PFEAR) on ECSM when after 
                ECC Configuration Register (ECR) has been configured.
        */
        /** @note Violates MISRA-C:2004 Advisory Rule 12.4, Side effects on right hand of logical 
        operator: See @ref Fls_c_REF_9 */        
        if(( FLS_LLD_E_PENDING == Fls_LLD_ReadStatus ) && 
            ( FLS_LLD_MCI_EXC_SYNDROME == (ExceptionDetailsPtr->syndrome_u32 & \
              FLS_LLD_MCI_EXC_SYNDROME) ) && \
            ( ExceptionDetailsPtr->data_pt == Fls_LLD_ReadAddressPtr ))
        {
            Fls_LLD_ReadStatus = FLS_LLD_E_FAILED;
            RetVal = FLS_HANDLED_SKIP;
        }
        /** @note Violates MISRA-C:2004 Advisory Rule 12.4, Side effects on right hand of logical 
        operator: See @ref Fls_c_REF_9 */
        else if(( FLS_LLD_E_PENDING == Fls_LLD_CompareStatus ) && \
            ( FLS_LLD_MCI_EXC_SYNDROME == \
            (ExceptionDetailsPtr->syndrome_u32 & FLS_LLD_MCI_EXC_SYNDROME) ) && \
            (( ExceptionDetailsPtr->data_pt == Fls_LLD_ReadAddressPtr ) || \
            ( ExceptionDetailsPtr->data_pt == Fls_LLD_CompareAddressPtr )))
        {
            Fls_LLD_CompareStatus = FLS_LLD_E_FAILED;
            RetVal = FLS_HANDLED_SKIP;
        }
        else
        {
            /* FLS_UNHANDLED */
        }

        return RetVal;
    }
    #endif /* for XPC560XP, XPC560XB and XPC560XS platforms */
#endif /*ifdef IPV_FLASH */


#endif /* FLS_DSI_HANDLER_API == STD_ON */


/**
    @brief Maps TargetAddress to sector index
    @details Calculate index of logical sector TargetAddress belongs to

    @param[in] TargetAddress Target address in flash memory

    @return Zero based index of logical sector
    @retval 0 .. (Fls_ConfigPtr->sectorCount - 1)

    @pre The module must be initialized
    @pre TargetAddress must be in configured flash boundary

    @remarks Implements DFLS20103
*/
STATIC FUNC(Fls_SectorIndexType, FLS_CODE) Fls_GetSectorIndexByAddr(
    CONST(Fls_AddressType, FLS_CONST) TargetAddress)
{
    VAR( Fls_SectorIndexType, AUTOMATIC ) sectorIndex = 0UL;

    for( sectorIndex = 0U; sectorIndex < Fls_ConfigPtr->sectorCount;
        sectorIndex++ )
    {

        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        if( TargetAddress <= Fls_ConfigPtr->sectorEndAddr[sectorIndex] )
        {
            /* TargetAddress belongs to sector with index sectorIndex */
            break;
        }
        else
        {
            /* Check next sector */
        }
    }

    return sectorIndex;
}

/**
    @brief Return start address of given sector
    @details Calculate start address (in linear space) of logical sector
        specified by the SectorIndex parameter

    @param[in] SectorIndex Index of logical sector

    @return Start address of SectorIndex sector
    @retval 0 .. (FLS_TOTAL_SIZE - 1)

    @pre The module must be initialized
    @pre SectorIndex must be in range 0 .. (Fls_ConfigPtr->sectorCount - 1)

    @remarks Implements DFLS20104
*/
STATIC FUNC( Fls_AddressType, FLS_CODE ) Fls_GetSectorStartAddr(
    CONST(Fls_SectorIndexType, FLS_CONST) SectorIndex )
{
    VAR( Fls_AddressType, AUTOMATIC ) TargetAddress = 0U;

    if( 0U != SectorIndex )
    {
        /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
        form of pointer arithmetic: See @ref Fls_c_REF_15 */
        TargetAddress = Fls_ConfigPtr->sectorEndAddr[SectorIndex - 1U] + 1U;
    }
    else
    {
        /* First sector starts with address 0 */
    }

    return TargetAddress;
}

/**
    @brief Check whether TargetAddress is page aligned
    @details Check whether TargetAddress is integer multiple of FLS_PAGE_SIZE

    @param[in] TargetAddress Target address in flash memory

    @return boolean
    @retval TRUE TargetAddress is page aligned
    @retval FALSE TargetAddress is not page aligned

    @remarks Implements DFLS20100
*/
#if( FLS_DEV_ERROR_DETECT == STD_ON )
STATIC FUNC(boolean, FLS_CODE) Fls_IsAddrPageAligned(
    CONST(Fls_AddressType, FLS_CONST) TargetAddress )
{
    /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes
    signedness: See @ref Fls_c_REF_2 */
    VAR( boolean, AUTOMATIC ) RetVal = FALSE;

    /* Aligned to Double Word or Word depending if CODE/DATA Flash or DFO */
    if(!(TargetAddress % Fls_ConfigPtr->sectorPageSize[Fls_GetSectorIndexByAddr( TargetAddress )]))
    {
       /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes
        signedness: See @ref Fls_c_REF_2 */
        RetVal = TRUE;
    }
    else
    {
        /* TargetAddress is not page aligned */
    }

    return( RetVal );
}

/**
    @brief Check whether TargetAddress is page start aligned
    @details Check whether TargetAddress is in range and aligned to first
        byte of flash page

    @param[in] TargetAddress Target address in flash memory

    @return boolean
    @retval TRUE TargetAddress is in range and aligned to start of the page
    @retval FALSE TargetAddress is not in range or aligned to start of the page

    @pre The module must be initialized

    @remarks Implements DFLS20101
*/
STATIC FUNC(boolean, FLS_CODE) Fls_IsAddrPageStartAligned(
    CONST(Fls_AddressType, FLS_CONST) TargetAddress )
{
   /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes
    signedness: See @ref Fls_c_REF_2 */
    VAR( boolean, AUTOMATIC ) RetVal = FALSE;

   /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes
    signedness: See @ref Fls_c_REF_2 */
    if(( TargetAddress < FLS_TOTAL_SIZE ) &&
        ( Fls_IsAddrPageAligned( TargetAddress ) ))
    {
       /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes
        signedness: See @ref Fls_c_REF_2 */
        RetVal = TRUE;
    }
    else
    {
        /* TargetAddress is not in range or aligned to start of the page */
    }

    return( RetVal );
}

/**
    @brief Check whether TargetAddress is page start aligned
    @details Check whether Length is in range and aligned to
        flash page

    @param[in] TargetAddress Target address in flash memory
     @param[in] Length size of current write

    @return boolean
    @retval TRUE TargetAddress is in range and aligned to end of the page
    @retval FALSE TargetAddress is not in range or aligned to end of the page

    @pre The module must be initialized

    @remarks Implements DFLS20102
*/
STATIC FUNC(boolean, FLS_CODE) Fls_IsLengthAligned(
    CONST(Fls_AddressType, FLS_CONST) TargetAddress,
    CONST(Fls_LengthType, FLS_CONST) Length
    )
{
   /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes
    signedness: See @ref Fls_c_REF_2 */
    VAR( boolean, AUTOMATIC ) RetVal = FALSE;

   /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes
    signedness: See @ref Fls_c_REF_2 */
    if(( (TargetAddress + Length -1U)< FLS_TOTAL_SIZE ) &&
       (!(Length % Fls_ConfigPtr->sectorPageSize[Fls_GetSectorIndexByAddr( TargetAddress )])))
    {
       /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes
        signedness: See @ref Fls_c_REF_2 */
        RetVal = TRUE;
    }
    else
    {
        /* TargetAddress is not in range or aligned to end of the page */
    }

    return( RetVal );
}


/**
    @brief Check whether TargetAddress is sector start aligned
    @details Check whether TargetAddress is in range and aligned to first
        byte of flash sector

    @param[in] TargetAddress Target address in flash memory

    @return boolean
    @retval TRUE TargetAddress is in range and aligned to start of the sector
    @retval FALSE TargetAddress is not in range or not aligned to
        start of the sector

    @pre The module must be initialized

    @remarks Implements DFLS20105
*/
STATIC FUNC(boolean, FLS_CODE) Fls_IsAddrSectorStartAligned(
    CONST(Fls_AddressType, FLS_CONST) TargetAddress )
{
   /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes
    signedness: See @ref Fls_c_REF_2 */
    VAR( boolean, AUTOMATIC ) RetVal = FALSE;

    if(( TargetAddress < FLS_TOTAL_SIZE ) &&
        ( TargetAddress == Fls_GetSectorStartAddr( Fls_GetSectorIndexByAddr( TargetAddress ))))
    {
       /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes
        signedness: See @ref Fls_c_REF_2 */
        RetVal = TRUE;
    }
    else
    {
        /* TargetAddress is not in range or
            not aligned to start of the sector */
    }

    return RetVal;
}

/**
    @brief Check whether TargetAddress is sector end aligned
    @details Check whether TargetAddress is in range and aligned to last
        byte of flash sector

    @param[in] TargetAddress Target address in flash memory

    @return boolean
    @retval TRUE TargetAddress is in range and aligned to end of the sector
    @retval FALSE TargetAddress is not in range or not aligned to
        end of the sector

    @pre The module must be initialized

    @remarks Implements DFLS20106
*/
STATIC FUNC(boolean, FLS_CODE) Fls_IsAddrSectorEndAligned(
    CONST(Fls_AddressType, FLS_CONST) TargetAddress )
{
   /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes
    signedness: See @ref Fls_c_REF_2 */
    VAR( boolean, AUTOMATIC ) RetVal = FALSE;
    VAR( Fls_SectorIndexType, AUTOMATIC ) sectorIndex = 0UL;

    sectorIndex = Fls_GetSectorIndexByAddr( TargetAddress );

    if(( TargetAddress < FLS_TOTAL_SIZE ) &&
        ( TargetAddress == Fls_ConfigPtr->sectorEndAddr[sectorIndex] ))
    {
       /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes
        signedness: See @ref Fls_c_REF_2 */
        RetVal =  TRUE;
    }
    else
    {
        /* TargetAddress is not in range or not aligned to end of the sector */
    }

    return RetVal;
}
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */

/**
    @brief Load access code to RAM
    @details Load erase or write access code to statically
        pre-configured location in RAM

    @param[in] Job Type of access code to load. Can be either
        FLS_JOB_ERASE or FLS_JOB_WRITE

    @pre The module must be initialized

    @remarks Implements DFLS20107
*/
#if( FLS_AC_LOAD_ON_JOB_START == STD_ON )
STATIC FUNC( void, FLS_CODE ) Fls_LoadAc(
    CONST( Fls_JobType, FLS_CONST) Job )
{
    P2CONST( uint32, AUTOMATIC, FLS_APPL_CONST ) romPtr = NULL_PTR;
    P2CONST( uint32, AUTOMATIC, FLS_APPL_CONST ) romEndPtr = NULL_PTR;
    P2VAR( uint32, AUTOMATIC, FLS_APPL_CONST ) ramPtr = NULL_PTR;

    switch( Job )
    {
        case FLS_JOB_ERASE:
            romPtr = Fls_AcErase;
            romEndPtr = romPtr + (FLS_AC_SIZE_ERASE/4U);
           /** @note Violates MISRA-C:2004 Advisory Rule 11.4, Cast from pointer to pointer: See
           @ref Fls_c_REF_3 */
            ramPtr = (uint32*)(Fls_ConfigPtr->acErasePtr);
        break;

        case FLS_JOB_WRITE:
            romPtr = Fls_AcWrite;
            romEndPtr = romPtr + (FLS_AC_SIZE_WRITE/4U);
           /** @note Violates MISRA-C:2004 Advisory Rule 11.4, Cast from pointer to pointer: See
           @ref Fls_c_REF_3 */
            ramPtr = (uint32*)(Fls_ConfigPtr->acWritePtr);
        break;

        default:
            /* Compiler_Warning: Added CER for Catastrophic events */
            Cer_ReportError( (uint16) FLS_MODULE_ID, (uint8)FLS_INSTANCE_ID, (uint8)FLS_SID_SETCLOCKMODE, (uint8)FLS_E_DEFAULT);
        break;
    }

    /* Copy erase or write access code to RAM */
    for(; romPtr != romEndPtr; romPtr++)
    {
        *ramPtr = *romPtr;
        ramPtr++;
    }
}

/**
    @brief Unload access code to RAM
    @details Erase write or erase access code from statically
        pre-configured location in RAM. Fills the RAM location
        with FLS_AC_UNLOAD_PATTERN

    @param[in] Job Type of access code to unload. Can be either
        FLS_JOB_ERASE or FLS_JOB_WRITE

    @pre The module must be initialized

    @remarks Implements DFLS20108
*/
STATIC FUNC( void, FLS_CODE ) Fls_UnloadAc(
    CONST( Fls_JobType, FLS_CONST) Job)
{
    P2VAR( uint32, AUTOMATIC, FLS_APPL_CONST ) ramPtr = NULL_PTR;
    P2VAR( uint32, AUTOMATIC, FLS_APPL_CONST ) ramEndPtr = NULL_PTR;

    switch( Job )
    {
        case FLS_JOB_ERASE:
           /** @note Violates MISRA-C:2004 Advisory Rule 11.4, Cast from pointer to pointer: See
           @ref Fls_c_REF_3 */
            ramPtr = (uint32*)(Fls_ConfigPtr->acErasePtr);
            ramEndPtr = ramPtr + (FLS_AC_SIZE_ERASE/4U);
        break;

        case FLS_JOB_WRITE:
           /** @note Violates MISRA-C:2004 Advisory Rule 11.4, Cast from pointer to pointer: See
           @ref Fls_c_REF_3 */
            ramPtr = (uint32*)(Fls_ConfigPtr->acWritePtr);
            ramEndPtr = ramPtr + (FLS_AC_SIZE_WRITE/4U);
        break;

        default:
            /* Compiler_Warning: Added CER for Catastrophic events */
            Cer_ReportError( (uint16) FLS_MODULE_ID, (uint8)FLS_INSTANCE_ID, (uint8)FLS_SID_SETCLOCKMODE, (uint8)FLS_E_DEFAULT);
        break;
    }

    /* Unload (erase) write or erase access code from RAM */
    for(; ramPtr != ramEndPtr; ramPtr++)
    {
        *ramPtr = FLS_AC_UNLOAD_PATTERN;
    }
}
#endif /* FLS_AC_LOAD_ON_JOB_START */

/**
    @brief Erase one complete flash sector
    @details Call low level flash driver service
        to erase one complete flash sector specified by the Fls_JobSectorIt
        internal job variable

    @return MemIf_JobResultType
    @retval MEMIF_JOB_OK erase operation succeeded and there
        is no more sectors to erase
    @retval MEMIF_JOB_PENDING erase operation succeeded and there
        is still one or more sectors to erase
    @retval MEMIF_JOB_FAILED operation failed due to hardware error

    @pre The module must be initialized, the Fls_JobSectorIt internal
        job variable must contain index of logical sector to be erased, and
        Fls_JobSectorEnd must contain index of last logical sector to be erased

    @post increments the Fls_JobSectorIt internal job variable

    @remarks Implements DFLS20109, DFLS11201, DFLS11202, DFLS11203, DFLS11204,
        DFLS11205
*/
STATIC FUNC( MemIf_JobResultType, FLS_CODE )  Fls_DoJobErase( void )
{
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_PENDING;

    /** @remarks Implements DFLS11201 */
    if( Fls_JobSectorIt > Fls_JobSectorEnd )
    {
        /* No more sectors to erase */
        RetVal = MEMIF_JOB_OK;
    }
    else
    {
        VAR( Fls_LLD_PhysicalSectorType, AUTOMATIC ) physicalSectorId;
#if( FLS_ERASE_BLANK_CHECK == STD_ON )
        VAR( Fls_LengthType, AUTOMATIC ) physicalSectorSize = 0UL;
#endif    /* FLS_ERASE_BLANK_CHECK == STD_ON */
        VAR( boolean, AUTOMATIC ) asynch = (boolean)0;
        VAR( Fls_LLD_ReturnType, AUTOMATIC ) lldRetVal = FLS_LLD_E_OK;

        /* Map logical sector index to physical sector ID */
       /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
       form of pointer arithmetic: See @ref Fls_c_REF_15 */
        physicalSectorId = Fls_ConfigPtr->physicalSector[Fls_JobSectorIt];

#if( FLS_ERASE_BLANK_CHECK == STD_ON )
        /* Calculate size of the physical sector */
        physicalSectorSize = (Fls_ConfigPtr->sectorEndAddr[Fls_JobSectorIt] -
            Fls_GetSectorStartAddr( Fls_JobSectorIt )) + 1;
#endif    /* FLS_ERASE_BLANK_CHECK == STD_ON */

        /* Get the Fls_LLD_SectorErase function operation mode */
       /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
       form of pointer arithmetic: See @ref Fls_c_REF_15 */
        if( Fls_ConfigPtr->sectorFlags[Fls_JobSectorIt] &
            FLS_SECTOR_ERASE_ASYNCH )
        {
           /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes
           signedness: See @ref Fls_c_REF_2 */
            asynch = TRUE;
        }
        else
        {
           /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes
           signedness: See @ref Fls_c_REF_2 */
            asynch = FALSE;
        }

        /* To inform Mainfunction how to erase an interleaved block - in async mode only */
        Fls_LLD_asyncInterleavedBlock = flsLLDSectorList0[physicalSectorId].interleavedBlo;
        Fls_LLD_bloSelValue = flsLLDSectorList0[physicalSectorId].addrSpaceBloSelValue;
        Fls_LLD_bloSelRegOffset = flsLLDSectorList0[physicalSectorId].sectorBloSelRegOffset;
        Fls_LLD_B1targetAddressPtr = flsLLDSectorList0[physicalSectorId].sectorStartB1AddressPtr;


        /** @remarks Implements DFLS11202 */
        /* Call Low-Level driver to erase one sector with
            the Fls_JobSectorIt sector index */
#if( FLS_ERASE_BLANK_CHECK == STD_ON )
        lldRetVal = Fls_LLD_SectorErase( physicalSectorId, physicalSectorSize,
            asynch );
#else
        lldRetVal = Fls_LLD_SectorErase( physicalSectorId, asynch );
#endif
        /** @remarks Implements DFLS11203 */
        if(( FLS_LLD_E_OK == lldRetVal ) && ( Fls_JobSectorIt == Fls_JobSectorEnd ))
        {
            RetVal = MEMIF_JOB_OK;
        }
        /** @remarks Implements DFLS11204 */
        else if( FLS_LLD_E_FAILED == lldRetVal )
        {
            RetVal = MEMIF_JOB_FAILED;
        }
        else
        {
            /** @remarks Implements DFLS11205 */
            /* The erase operation is either pending (FLS_LLD_E_PENDING)
            in hardware in case of asynchronous operation or
            finished (FLS_LLD_E_OK) in case of synchronous operation
            and there is more sectors to erase */
            Fls_JobSectorIt++;
        }
    }

    return( RetVal );
}

/**
    @brief Calculate last logical address to read, write, or compare
        from in current cycle of Fls_MainFunction
    @details Calculate last logical address of Fls_DoJobDataTransfer
        loop to limit number of bytes transferred to/from flash memory
        in one cycle of Fls_MainFunction

    @param[in] MaxTransfer Maximum number of bytes to read, write, or compare
        in current cycle of Fls_MainFunction

    @return Fls_AddressType
    @retval 0 .. (FLS_TOTAL_SIZE - 1)

    @pre Fls_JobAddrIt must contain current, and Fls_JobAddrEnd last
        logical address of current job

    @remarks Implements DFLS20110
*/
STATIC FUNC( Fls_AddressType, FLS_CODE ) Fls_CalcMaxTransferAddrEnd(
    CONST( Fls_LengthType, FLS_CONST) MaxTransfer )
{
    VAR( Fls_AddressType, AUTOMATIC ) MaxTransferEndAddr = Fls_JobAddrEnd;

    /* Adjust the MaxTransferEndAddr address to transfer only
        the MaxTransfer bytes in one Fls_MainFunction() call */
    if( MaxTransferEndAddr >= (Fls_JobAddrIt + MaxTransfer) )
    {
        MaxTransferEndAddr = (Fls_JobAddrIt + MaxTransfer) - 1U;
    }
    else
    {
        /* No adjustment is necessary. Job will finish in this cycle
            of Fls_MainFunction */
    }

    return( MaxTransferEndAddr );
}

/**
    @brief Calculate sector offset to read, write, or compare
        from current sector
    @details Calculate sector offset in bytes for low-level driver
        services

    @return Fls_AddressType
    @retval 0 .. (FLS_SECTOR_SIZE - 1)

    @pre The module must be initialized, Fls_JobSectorIt internal job
        variable must contain index of current logical sector,
        Fls_JobAddrIt must contain current logical address

    @remarks Implements DFLS20111
*/
STATIC FUNC( Fls_AddressType, FLS_CODE ) Fls_CalcSectorTransferOffset( void )
{
    VAR( Fls_AddressType, AUTOMATIC ) sectorAddrStart = 0UL;

    /* Get first address of Fls_JobSectorIt sector */
    sectorAddrStart = Fls_GetSectorStartAddr( Fls_JobSectorIt );

    /* Calculate the sector offset */
    return( Fls_JobAddrIt - sectorAddrStart );
}

/**
    @brief Calculate number of bytes to read, write, or compare
        from current sector
    @details Calculate sector transfer length for low-level driver
        services

    @param[in] MaxTransferEndAddr Last address to read, write,
        or compare data from in this cycle of Fls_MainFunction

    @return Fls_AddressType
    @retval 1 .. (FLS_SECTOR_SIZE - 1)

    @pre The module must be initialized, Fls_JobSectorIt internal job
        variable must contain index of current logical sector,
        Fls_JobAddrIt must contain current logical address, and
        MaxTransferEndAddr must be >= Fls_JobAddrIt and lie within
        the specified lower and upper flash address boundaries

    @remarks Implements DFLS20112
*/
STATIC FUNC( Fls_AddressType, FLS_CODE ) Fls_CalcSectorTransferLength(
    CONST( Fls_AddressType, FLS_CONST) MaxTransferEndAddr )
{
    VAR( Fls_AddressType, AUTOMATIC ) sectorEndAddr = 0UL;

    /* Get last address of Fls_JobSectorIt sector */
    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
    form of pointer arithmetic: See @ref Fls_c_REF_15 */
    sectorEndAddr = Fls_ConfigPtr->sectorEndAddr[Fls_JobSectorIt];

    /* Adjust the sectorEndAddr according to max number of bytes to transfer
        during one cycle of Fls_MainFunction */
    if( sectorEndAddr > MaxTransferEndAddr )
    {
        sectorEndAddr = MaxTransferEndAddr;
    }
    else
    {
        /* No adjustment is necessary. There is more sectors
            to transfer */
    }

    /* Calculate number of bytes to read from the sector */
    return(( sectorEndAddr - Fls_JobAddrIt ) + 1U );
}

/**
    @brief Read up to one physical flash sector
    @details Call low level flash driver service to read given number of bytes
        from given sector offset.

    @param[in] SectorOffset Flash sector offset to read data from
    @param[in] Length Number of bytes to read

    @return Fls_LLD_ReturnType
    @retval FLS_LLD_E_OK read operation succeeded
    @retval FLS_LLD_E_FAILED read operation failed due to a hardware error

    @pre The module must be initialized, the Fls_JobSectorIt internal job
        variable must contain valid index of logical sector to read,
        SectorOffset and Length must be in physical    sector boundary,
        Fls_JobDataDestPtr internal job variable must point to data read buffer

    @remarks Implements DFLS20113, DFLS11300, DFLS11301, DFLS11302
*/
STATIC FUNC( Fls_LLD_ReturnType, FLS_CODE ) Fls_DoJobRead(
    CONST( Fls_AddressType, FLS_CONST) SectorOffset,
    CONST( Fls_AddressType, FLS_CONST) Length )
{
    VAR( Fls_LLD_ReturnType, AUTOMATIC ) RetVal = FLS_LLD_E_OK;
    VAR( Fls_LLD_PhysicalSectorType, AUTOMATIC ) physicalSector;

    /* Map logical sector index to physical sector ID */
    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
    form of pointer arithmetic: See @ref Fls_c_REF_15 */
    physicalSector = Fls_ConfigPtr->physicalSector[Fls_JobSectorIt];

    /** @remarks Implements    DFLS11301 */
    /* Do physical sector read */
    if( FLS_LLD_E_OK != Fls_LLD_SectorRead( physicalSector, SectorOffset,
        Length, Fls_JobDataDestPtr ))
    {
        /** @remarks Implements    DFLS11302 */
        Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_READ_FAILED, DEM_EVENT_STATUS_FAILED);

        RetVal = FLS_LLD_E_FAILED;
    }
    else
    {
        /* Physical sector read succeeded */
    }

    return( RetVal );
}

/**
    @brief Write up to one physical flash sector
    @details Call low level flash driver service to write given number of bytes
        at given sector offset

    @param[in] SectorOffset Flash sector offset to write data to
    @param[in] Length Number of bytes to write

    @return Fls_LLD_ReturnType
    @retval FLS_LLD_E_OK write operation succeeded
    @retval FLS_LLD_E_FAILED write operation failed due to a hardware error

    @pre The module must be initialized, the Fls_JobSectorIt internal job
        variable must contain valid index of logical sector to write,
        SectorOffset and Length must be in physical sector boundary and page
        aligned, Fls_JobDataSrcPtr internal job variable must point to data
        write buffer

    @remarks Implements DFLS20114, DFLS11400, DFLS11401
*/
STATIC FUNC( Fls_LLD_ReturnType, FLS_CODE ) Fls_DoJobWrite(
    CONST( Fls_AddressType, FLS_CONST) SectorOffset,
    CONST( Fls_AddressType, FLS_CONST) Length )
{
    VAR( Fls_LLD_ReturnType, AUTOMATIC ) RetVal = FLS_LLD_E_OK;
    VAR( Fls_LLD_PhysicalSectorType, AUTOMATIC ) physicalSector;
    VAR( boolean, AUTOMATIC ) asynch = (boolean)0;

    /* Map logical sector index to physical sector ID */
    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
    form of pointer arithmetic: See @ref Fls_c_REF_15 */
    physicalSector = Fls_ConfigPtr->physicalSector[Fls_JobSectorIt];

    /* Get the Fls_LLD_SectorWrite function operation mode */
    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
    form of pointer arithmetic: See @ref Fls_c_REF_15 */
    if( Fls_ConfigPtr->sectorFlags[Fls_JobSectorIt] & FLS_PAGE_WRITE_ASYNCH )
    {
        /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes signedness:
        See @ref Fls_c_REF_2 */
        asynch = TRUE;
    }
    else
    {
        /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes signedness:
        See @ref Fls_c_REF_2 */
        asynch = FALSE;
    }


    /* To inform Mainfunction how to write an interleaved block - in async mode only */
    Fls_LLD_asyncInterleavedBlock = flsLLDSectorList0[physicalSector].interleavedBlo;
    Fls_LLD_InterleavedSize = flsLLDSectorList0[physicalSector].interleavedSize;

    /** @remarks Implements    DFLS11401 */
    RetVal = Fls_LLD_SectorWrite( physicalSector, SectorOffset, Length,
        Fls_JobDataSrcPtr, asynch );

    return( RetVal );
}

/**
    @brief Compare up to one physical flash sector with data buffer
    @details Call low level flash driver service to compare given
        number of bytes at given sector offset with data buffer

    @param[in] SectorOffset Flash sector offset to compare data with
    @param[in] Length Number of bytes to compare

    @return Fls_LLD_ReturnType
    @retval FLS_LLD_E_OK compare operation succeeded
    @retval FLS_LLD_E_FAILED compare operation failed due to a hardware error
    @retval FLS_LLD_E_BLOCK_INCONSISTENT compare operation failed
        due to data mismatch

    @pre The module must be initialized, the Fls_JobSectorIt internal job
        variable must contain valid index of logical sector to compare,
        SectorOffset and Length must be in physical sector boundary,
        Fls_JobDataSrcPtr internal job variable must point to
        compare data buffer

    @remarks Implements DFLS20115, DFLS11500, DFLS11501, DFLS11502, DFLS11503
*/
/** @remarks Implements    DFLS11501 */
#if( FLS_COMPARE_API == STD_ON )
STATIC FUNC( Fls_LLD_ReturnType, FLS_CODE ) Fls_DoJobCompare(
    CONST( Fls_AddressType, FLS_CONST) SectorOffset,
    CONST( Fls_AddressType, FLS_CONST) Length )
{
    VAR( Fls_LLD_ReturnType, AUTOMATIC ) RetVal = FLS_LLD_E_OK;
    VAR( Fls_LLD_PhysicalSectorType, AUTOMATIC ) physicalSector;

    /* Map logical sector index to physical sector ID */
    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the only allowed
    form of pointer arithmetic: See @ref Fls_c_REF_15 */
    physicalSector = Fls_ConfigPtr->physicalSector[Fls_JobSectorIt];

    /** @remarks Implements    DFLS11502 */
    RetVal = Fls_LLD_SectorCompare( physicalSector, SectorOffset,
        Length, Fls_JobDataSrcPtr );

    /** @remarks Implements    DFLS11503 */
    if( FLS_LLD_E_FAILED == RetVal )
    {
        Dem_ReportErrorStatus((Dem_EventIdType)FLS_E_COMPARE_FAILED, DEM_EVENT_STATUS_FAILED);
    }
    else
    {
        /* physical sector compare succeeded or
            FLS_LLD_E_BLOCK_INCONSISTENT */
    }

    return( RetVal );
}
#endif /* FLS_COMPARE_API == STD_ON */

/**
    @brief Read, write, or compare flash data
    @details Call Fls_DoJobRead, Fls_DoJobWrite, or Fls_DoJobCompare
        functions to read, write, or compare flash data. The functions
        ensures that only pre-configured maximum number of bytes is
        read, written, or compared during one cycle of
        the Fls_MainFunction call

    @return MemIf_JobResultType
    @retval MEMIF_JOB_OK read, write, or compare operation succeeded and there
        is no more data to read, write, or compare
    @retval MEMIF_JOB_PENDING read, write, or compare operation succeeded
        and there is still some data to read, write, or compare
    @retval MEMIF_JOB_FAILED read, write, or compare operation failed due
        to a hardware error
    @retval MEMIF_BLOCK_INCONSISTENT Compared data from a flash compare
        job are not equal

    @pre The module must be initialized, the Fls_JobSectorIt internal
        job variable must contain index of logical sector to read, write,
        or compare, the Fls_JobAddrIt must contain logical address to read,
        write or compare, and Fls_JobAddrEnd must contain last address to read,
        write or compare.

    @post Updates the Fls_JobSectorIt, Fls_JobDataSrcPtr, Fls_JobDataDestPtr,
        and Fls_JobAddrIt internal job variables

    @remarks Implements DFLS20116, DFLS11100, DFLS11101, DFLS11102, DFLS11103,
        DFLS11400, DFLS11300, DFLS11500, DFLS11204, DFLS11205, DFLS11206,
        DFLS11207, DFLS11208, DFLS11209
*/
STATIC FUNC( MemIf_JobResultType, FLS_CODE ) Fls_DoJobDataTransfer(
    CONST( Fls_JobType, FLS_CONST) Job,
    CONST( Fls_LengthType, FLS_CONST) MaxTransfer )
{
    VAR( MemIf_JobResultType, AUTOMATIC ) RetVal = MEMIF_JOB_PENDING;

    /** @remarks Implements    DFLS11209 */
    /* No more data to write */
    if( Fls_JobAddrIt > Fls_JobAddrEnd )
    {
        RetVal = MEMIF_JOB_OK;
    }
    else
    {
        VAR( Fls_AddressType, AUTOMATIC ) maxTransferAddrEnd = 0UL;
        VAR( Fls_LLD_ReturnType, AUTOMATIC ) TransferRetVal = FLS_LLD_E_FAILED;

        /** @remarks Implements    DFLS11101 */
        /* Last address to transfer data to/from in this call of
            the Fls_MainFunction() functions */
        maxTransferAddrEnd = Fls_CalcMaxTransferAddrEnd( MaxTransfer );

        /** @remarks Implements    DFLS11109 */
        /* Transfer sector by sector until the maxTransferAddrEnd address is reached
            or error is detected */
        do
        {
            VAR( Fls_AddressType, AUTOMATIC ) sectorTransferOffset = 0UL;
            VAR( Fls_AddressType, AUTOMATIC ) sectorTransferLength = 0UL;

            /** @remarks Implements    DFLS11102 */
            /* Calculate offset and length of the sector data transfer */
            sectorTransferOffset = Fls_CalcSectorTransferOffset();
            sectorTransferLength = Fls_CalcSectorTransferLength( maxTransferAddrEnd );

            /** @remarks Implements    DFLS11203 */
            /* Call Low-level driver to transfer data to/from
                physical flash device */
            switch( Job )
            {
                case FLS_JOB_WRITE:
                    /** @remarks Implements    DFLS11400 */
                    TransferRetVal =  Fls_DoJobWrite(
                        sectorTransferOffset,
                        sectorTransferLength );

                    /* Update the source data pointer for next write */
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_JobDataSrcPtr += sectorTransferLength;
                    break;

                case FLS_JOB_READ:
                    /** @remarks Implements    DFLS11300 */
                    TransferRetVal =  Fls_DoJobRead(
                        sectorTransferOffset,
                        sectorTransferLength );

                    /* Update the destination data pointer for next read */
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_JobDataDestPtr += sectorTransferLength;
                    break;

/** @remarks Implements    DFLS11500 */
#if( FLS_COMPARE_API == STD_ON )
                case FLS_JOB_COMPARE:
                    TransferRetVal =  Fls_DoJobCompare(
                        sectorTransferOffset,
                        sectorTransferLength );

                    /* Update the source data pointer for next compare */
                    /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the
                    only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                    Fls_JobDataSrcPtr += sectorTransferLength;
                    break;
#endif /* FLS_COMPARE_API == STD_ON */

                case FLS_JOB_ERASE:
        /* If the case corresponds to FLS_JOB_ERASE the switch case will  break */
                   break;
                default:
                    /* Compiler_Warning: Added CER for Catastrophic events */
                    Cer_ReportError( (uint16) FLS_MODULE_ID, (uint8)FLS_INSTANCE_ID, (uint8)FLS_SID_SETCLOCKMODE, (uint8)FLS_E_DEFAULT);
                  break;
            }

            /** @remarks Implements    DFLS11204 */
            /* Update the Fls_JobAddressIt iterator */
            Fls_JobAddrIt += sectorTransferLength;

            /** @remarks Implements    DFLS11206 */
            /* Fls_JobSectorIt should be increased here only for SYNC mode and for read/compare job
               For a Write Job in ASYNC mode it should be set by Fls_LLD_MainFunction just before
               completing the Job */
            /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the
            only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
            /** @note Violates MISRA-C:2004 Advisory Rule 12.6, The operands of logical operators
            (&&, || and !) should be effectively Boolean: See @ref Fls_c_REF_13 */
            if ( (!(Fls_ConfigPtr->sectorFlags[Fls_JobSectorIt] & FLS_PAGE_WRITE_ASYNCH))  ||    \
                   (FLS_JOB_READ == Job )                                                  ||    \
                   (FLS_JOB_COMPARE == Job )                                                     \
            )
            {
                /** @note Violates MISRA-C:2004 Advisory Rule 17.4, Array indexing shall be the
                only allowed form of pointer arithmetic: See @ref Fls_c_REF_15 */
                if( (Fls_JobAddrIt > Fls_ConfigPtr->sectorEndAddr[Fls_JobSectorIt]))
                {
                    /* Move on to the next sector */
                    Fls_JobSectorIt++;
                }

            }
        }
        /** @remarks Implements    DFLS11205, DFLS11207 */
        while(( Fls_JobAddrIt <= maxTransferAddrEnd ) &&
            ( TransferRetVal == FLS_LLD_E_OK ));

        /** @remarks Implements    DFLS11205 */
        if( FLS_LLD_E_FAILED == TransferRetVal )
        {
            RetVal = MEMIF_JOB_FAILED;
        }
        /** @remarks Implements    DFLS11205 */
        else if( FLS_LLD_E_BLOCK_INCONSISTENT == TransferRetVal )
        {
            /* compare job only */
            RetVal = MEMIF_BLOCK_INCONSISTENT;
        }
        /** @remarks Implements    DFLS11208 */
        else if(( Fls_JobAddrIt > Fls_JobAddrEnd ) &&
            ( FLS_LLD_E_OK == TransferRetVal ))
        {
            /* All desired job data has been successfully transferred */
            RetVal = MEMIF_JOB_OK;
        }
        else
        {
            /* The write operation is either pending (FLS_LLD_E_PENDING)
            in hardware in case of asynchronous operation or
            finished (FLS_LLD_E_OK) in case of synchronous operation
            and there is more pages to write */
        }
    }

    return( RetVal );
}

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

/**
 * @brief       The function initializes Fls module.
 * @details     The function sets the internal module variables according to given
 *              configuration set.
 * @pre         @p ConfigPtr must not be @p NULL_PTR and the module status must not
 *              be @p MEMIF_BUSY.
 *
 * @param[in] ConfigPtr        Pointer to flash driver configuration set.
 *
 * @api
 *
 * @remarks Implements DFLS21102, DFLS01000, DFLS01001, DFLS01002, DFLS01003,
 *          DFLS01004, DFLS01005, DFLS01006, DFLS01007
*/
/** @note Violates MISRA-C:2004 Advisory Rule 8.10: See @ref Fls_c_REF_19 */
FUNC( void, FLS_CODE ) Fls_Init(
    P2CONST( Fls_ConfigType, AUTOMATIC, FLS_APPL_CONST ) ConfigPtr )
{
/** @remarks Implements DFLS01001 */
#if( FLS_DEV_ERROR_DETECT == STD_ON )
    /** @remarks Implements DFLS01002 */
    if( NULL_PTR == ConfigPtr )
    {
        Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_INIT_ID, FLS_E_PARAM_CONFIG );
    }
    /** @remarks Implements DFLS01003 */
    else if( MEMIF_JOB_PENDING == Fls_JobResult )
    {
        Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_INIT_ID, FLS_E_BUSY );
    }
    else
#endif    /* FLS_DEV_ERROR_DETECT == STD_ON */
    {
        /** @remarks Implements DFLS01004 */
        Fls_ConfigPtr = ConfigPtr;

        /** @remarks Implements DFLS01005 */
        /* Set the max number of bytes to read/write
            during Fls_MainFunction call */
        Fls_MaxRead = Fls_ConfigPtr->maxReadNormalMode;
        Fls_MaxWrite = Fls_ConfigPtr->maxWriteNormalMode;

        /** @remarks Implements DFLS01007 */
        /* Initialize flash hardware */
        Fls_LLD_Init();

        /** @remarks Implements DFLS01006 */
        Fls_JobResult = MEMIF_JOB_OK;
    }
}

/**
 * @brief       Erase one or more complete flash sectors.
 * @details     Starts an erase job asynchronously. The actual job is performed
 *              by the @p Fls_MainFunction.
 * @pre         The module has to be initialized and not busy.
 * @post        @p Fls_Erase changes module status and some internal variables
 *              (@p Fls_JobSectorIt, @p Fls_JobSectorEnd, @p Fls_Job,
 *              @p Fls_JobResult).
 *
 * @param[in] TargetAddress        Target address in flash memory.
 * @param[in] Length               Number of bytes to erase.
 *
 * @return Std_ReturnType
 * @retval E_OK                    Erase command has been accepted.
 * @retval E_NOT_OK                Erase command has not been accepted.
 *
 * @api
 *
 * @remarks Implements DFLS21101, DFLS02000, DFLS02001, DFLS02002, DFLS02003,
 *          DFLS02004, DFLS02005, DFLS02007, DFLS02009, DFLS02011
*/
/** @note Violates MISRA-C:2004 Advisory Rule 8.10: See @ref Fls_c_REF_19 */
FUNC( Std_ReturnType, FLS_CODE ) Fls_Erase(
    VAR( Fls_AddressType, FLS_VAR) TargetAddress,
    VAR( Fls_LengthType, FLS_VAR) Length )
{
   VAR( Std_ReturnType, AUTOMATIC ) RetVal = (Std_ReturnType)E_OK;
    VAR( Fls_SectorIndexType, AUTOMATIC ) tmpJobSectorIt = 0UL;
    VAR( Fls_SectorIndexType, AUTOMATIC ) tmpJobSectorEnd = 0UL;

/** @remarks Implements DFLS02001 */
#if( FLS_DEV_ERROR_DETECT == STD_ON )
    /** @remarks Implements    DFLS02002 */
    if( NULL_PTR == Fls_ConfigPtr )
    {
        Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_ERASE_ID, FLS_E_UNINIT );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /** @remarks Implements DFLS02003 */
    /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes signedness:
    See @ref Fls_c_REF_2 */
    else if( !(Fls_IsAddrSectorStartAligned( TargetAddress )) )
    {
        Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_ERASE_ID, FLS_E_PARAM_ADDRESS );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /** @remarks Implements DFLS02004 */
    /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes signedness:
    See @ref Fls_c_REF_2 */
    else if(( 0U == Length ) || ( !(Fls_IsAddrSectorEndAligned(( TargetAddress + Length ) - 1U ))) )
    {
        Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_ERASE_ID, FLS_E_PARAM_LENGTH );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
#endif    /* FLS_DEV_ERROR_DETECT == STD_ON */

        /* Perform calculations outside the critical section in order
            to limit time spend in the CS */
        tmpJobSectorIt = Fls_GetSectorIndexByAddr( TargetAddress );
        tmpJobSectorEnd = Fls_GetSectorIndexByAddr(( TargetAddress + Length ) - 1U );

#if( FLS_DEV_ERROR_DETECT == STD_ON )
        /** @remarks Implements DFLS02011 */
        SchM_Enter_Fls( SCHM_FLS_INSTANCE_0, FLS_EXCLUSIVE_AREA_10 );
        /** @remarks Implements    DFLS02005 */
#endif    /* FLS_DEV_ERROR_DETECT == STD_ON */
        if( MEMIF_JOB_PENDING == Fls_JobResult )
        {
#if( FLS_DEV_ERROR_DETECT == STD_ON )
            Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_ERASE_ID, FLS_E_BUSY );
#endif    /* FLS_DEV_ERROR_DETECT == STD_ON */
            RetVal = (Std_ReturnType)E_NOT_OK;
        }
        else
        {

            /* Configure the erase job */
            /** @remarks Implements    DFLS02007 */
            Fls_JobSectorIt = tmpJobSectorIt;
            Fls_JobSectorEnd = tmpJobSectorEnd;
            Fls_Job = FLS_JOB_ERASE;
            Fls_JobStart = 1U;

            /* Execute the erase job */
            /** @remarks Implements    DFLS02009 */
            Fls_JobResult = MEMIF_JOB_PENDING;
        }
#if( FLS_DEV_ERROR_DETECT == STD_ON )
        /** @remarks Implements DFLS02011 */
        SchM_Exit_Fls( SCHM_FLS_INSTANCE_0, FLS_EXCLUSIVE_AREA_10 );
    }
#endif    /* FLS_DEV_ERROR_DETECT == STD_ON */

    return( RetVal );
}

/**
 * @brief       Write one or more complete flash pages to the flash device.
 * @details     Starts a write job asynchronously. The actual job is performed by
 *              @p Fls_MainFunction.
 * @pre         The module has to be initialized and not busy.
 * @post        @p Fls_Write changes module status and some internal variables
 *              (@p Fls_JobSectorIt, @p Fls_JobAddrIt, @p Fls_JobAddrEnd,
 *              @p Fls_JobDataSrcPtr, @p Fls_Job, @p Fls_JobResult).
 *
 * @param[in] TargetAddress        Target address in flash memory.
 * @param[in] SourceAddressPtr     Pointer to source data buffer.
 * @param[in] Length               Number of bytes to write.
 * @return Std_ReturnType
 * @retval E_OK                    Write command has been accepted.
 * @retval E_NOT_OK                Write command has not been accepted.
 *
 * @api
 *
 * @remarks Implements DFLS21104, DFLS03000, DFLS03001, DFLS03002, DFLS03003,
 *          DFLS03004, DFLS03005, DFLS03006, DFLS03008, DFLS03010, DFLS03012
*/
/** @note Violates MISRA-C:2004 Advisory Rule 8.10: See @ref Fls_c_REF_19 */
FUNC( Std_ReturnType, FLS_CODE ) Fls_Write(
    VAR( Fls_AddressType, FLS_VAR) TargetAddress,
    P2CONST( uint8, AUTOMATIC, FLS_APPL_CONST ) SourceAddressPtr,
    VAR( Fls_LengthType, FLS_VAR) Length )
{
    VAR( Std_ReturnType, AUTOMATIC ) RetVal = (Std_ReturnType)E_OK;
    VAR( Fls_SectorIndexType, AUTOMATIC ) tmpJobSectorIt = 0UL;
    VAR( Fls_AddressType, AUTOMATIC ) tmpJobAddrEnd = 0UL;

/** @remarks Implements DFLS03001 */
#if( FLS_DEV_ERROR_DETECT == STD_ON )
    /** @remarks Implements DFLS03002 */
    if( NULL_PTR == Fls_ConfigPtr )
    {
        Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_WRITE_ID, FLS_E_UNINIT );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /** @remarks Implements DFLS03003 */
    /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes signedness:
    See @ref Fls_c_REF_2 */
    else if( !(Fls_IsAddrPageStartAligned( TargetAddress )))
    {
        Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_WRITE_ID, FLS_E_PARAM_ADDRESS );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /** @remarks Implements DFLS03004 */
    /** @note Violates MISRA-C:2004 Advisory Rule 10.1, Implicit conversion changes signedness:
    See @ref Fls_c_REF_2 */
    else if(( 0U == Length ) || ( !(Fls_IsLengthAligned( TargetAddress, Length ) )))
    {
        Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_WRITE_ID, FLS_E_PARAM_LENGTH );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /** @remarks Implements DFLS03006 */
    else if( NULL_PTR == SourceAddressPtr )
    {
        Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_WRITE_ID, FLS_E_PARAM_DATA );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
#endif    /* FLS_DEV_ERROR_DETECT == STD_ON */

        /* Perform calculations outside the critical section in order
            to limit time spend in the CS */
        tmpJobSectorIt = Fls_GetSectorIndexByAddr(TargetAddress);
        tmpJobAddrEnd = ( TargetAddress + Length ) - 1U;

#if( FLS_DEV_ERROR_DETECT == STD_ON )
        /** @remarks Implements DFLS03012 */
        SchM_Enter_Fls( SCHM_FLS_INSTANCE_0, FLS_EXCLUSIVE_AREA_11 );
        /** @remarks Implements DFLS03005 */
#endif    /* FLS_DEV_ERROR_DETECT == STD_ON */
        if( MEMIF_JOB_PENDING == Fls_JobResult )
        {
#if( FLS_DEV_ERROR_DETECT == STD_ON )
            Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_WRITE_ID, FLS_E_BUSY );
#endif    /* FLS_DEV_ERROR_DETECT == STD_ON */
            RetVal = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
            /* Configure the write job */
            /** @remarks Implements DFLS03008 */
            Fls_JobSectorIt = tmpJobSectorIt;
            Fls_JobAddrIt = TargetAddress;
            Fls_JobAddrEnd = tmpJobAddrEnd;
            Fls_JobDataSrcPtr = SourceAddressPtr;
            Fls_Job = FLS_JOB_WRITE;
            Fls_JobStart = 1U;

            /* Execute the write job */
            /** @remarks Implements DFLS03010 */
            Fls_JobResult = MEMIF_JOB_PENDING;

        }
#if( FLS_DEV_ERROR_DETECT == STD_ON )
        /** @remarks Implements DFLS03012 */
        SchM_Exit_Fls( SCHM_FLS_INSTANCE_0, FLS_EXCLUSIVE_AREA_11 );
    }
#endif    /* FLS_DEV_ERROR_DETECT == STD_ON */

    return( RetVal );
}

/**
 * @brief       Cancel an ongoing flash read, write, erase or compare job.
 * @details     Abort a running job synchronously so that directly after returning
 *              from this function a new job can be started.
 * @pre         The module must be initialized.
 * @post        @p Fls_Cancel changes module status and @p Fls_JobResult
 *              internal variable.
 *
 * @api
 *
 * @remarks Implements DFLS21100, DFLS04000, DFLS04001, DFLS04002, DFLS04003,
 *          DFLS04004, DFLS04005, DFLS04006, DFLS04007
*/
/** @remarks Implements    DFLS04001 */
#if ( FLS_CANCEL_API == STD_ON ) || defined(__DOXYGEN__)
/** @note Violates MISRA-C:2004 Advisory Rule 8.10: See @ref Fls_c_REF_19 */
FUNC( void, FLS_CODE ) Fls_Cancel( void )
{
/** @remarks Implements DFLS04002 */
#if( FLS_DEV_ERROR_DETECT == STD_ON )
    if( NULL_PTR == Fls_ConfigPtr )
    {
        Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_CANCEL_ID, FLS_E_UNINIT );
    }
    else
    {
#endif    /* FLS_DEV_ERROR_DETECT == STD_ON */

        /** @remarks Implements    DFLS04004 */
        if( MEMIF_JOB_PENDING == Fls_JobResult )
        {
            /** @remarks Implements    DFLS04007 */
            /* Cancel ongoing hardware job */
            Fls_LLD_Cancel();

/** @remarks Implements    DFLS04005 */
#if( FLS_AC_LOAD_ON_JOB_START == STD_ON )
            if(( FLS_JOB_ERASE == Fls_Job ) || ( FLS_JOB_WRITE == Fls_Job ))
            {
                Fls_UnloadAc( Fls_Job );
            }
            else
            {
                /* The FLS_JOB_READ    and FLS_JOB_COMPARE jobs
                    don't use the access code */
            }
#endif
            /** @remarks Implements    DFLS04003 */
            Fls_JobResult = MEMIF_JOB_CANCELLED;

            /** @remarks Implements    DFLS04006 */
            if( NULL_PTR != Fls_ConfigPtr->jobErrorNotificationPtr )
            {
                /* Call FlsJobErrorNotification function if configured */
                Fls_ConfigPtr->jobErrorNotificationPtr();
            }
            else
            {
                /* Callback notification configured as null pointer */
            }
        }
        else
        {
            /* Leave the job result unchanged */
        }
#if( FLS_DEV_ERROR_DETECT == STD_ON )
    }
#endif    /* FLS_DEV_ERROR_DETECT == STD_ON */
}
#endif    /* FLS_CANCEL_API == STD_ON */

/**
 * @brief       Returns the FLS module status.
 * @details     Returns the FLS module status synchronously.
 *
 * @return MemIf_StatusType
 * @retval MEMIF_UNINIT        Module has not been initialized (yet).
 * @retval MEMIF_IDLE          Module is currently idle.
 * @retval MEMIF_BUSY          Module is currently busy.
 *
 * @api
 *
 * @remarks Implements DFLS21103, DFLS05000, DFLS05001, DFLS05002
*/
/** @remarks Implements    DFLS05001 */
#if(( FLS_GET_STATUS_API == STD_ON ) || defined (__DOXYGEN__))
/** @note Violates MISRA-C:2004 Advisory Rule 8.10: See @ref Fls_c_REF_19 */
FUNC( MemIf_StatusType, FLS_CODE ) Fls_GetStatus( void )
{
    VAR( MemIf_StatusType, AUTOMATIC ) RetVal = MEMIF_IDLE;

    /** @remarks Implements    DFLS05002 */
    if( NULL_PTR == Fls_ConfigPtr )
    {
        RetVal = MEMIF_UNINIT;
    }
    else if( MEMIF_JOB_PENDING == Fls_JobResult )
    {
        RetVal = MEMIF_BUSY;
    }
    else
    {
        RetVal = MEMIF_IDLE;
    }

    return( RetVal );
}
#endif    /* FLS_GET_STATUS_API == STD_ON */

/**
 * @brief       Returns last job result.
 * @details     Returns synchronously the result of the last job.
 *
 * @return MemIf_JobResultType
 * @retval MEMIF_JOB_OK              Successfully completed job.
 * @retval MEMIF_JOB_FAILED          Not successfully completed job.
 * @retval MEMIF_JOB_PENDING         Still pending job (not yet completed).
 * @retval MEMIF_JOB_CANCELLED       Job has been cancelled.
 * @retval MEMIF_BLOCK_INCONSISTENT  Inconsistent block requested, it may
 *                                   contains corrupted data.
 * @retval MEMIF_BLOCK_INVALID       Invalid block requested.
 *
 * @api
 *
 * @remarks Implements DFLS21105, DFLS06000, DFLS06001, DFLS06002
*/
/** @remarks Implements    DFLS06001 */
#if ( FLS_GET_JOB_RESULT_API == STD_ON )||  defined (__DOXYGEN__)
/** @note Violates MISRA-C:2004 Advisory Rule 8.10: See @ref Fls_c_REF_19 */
FUNC( MemIf_JobResultType, FLS_CODE ) Fls_GetJobResult( void )
{
    /** @remarks Implements    DFLS06002 */
    return( Fls_JobResult );
}
#endif    /* FLS_GET_JOB_RESULT_API == STD_ON */

/**
 * @brief       Reads from flash memory.
 * @details     Starts a read job asynchronously. The actual job is performed by
 *              @p Fls_MainFunction.
 * @pre         The module has to be initialized and not busy.
 * @post        @p Fls_Read changes module status and some internal variables
 *              (@p Fls_JobSectorIt, @p Fls_JobAddrIt, @p Fls_JobAddrEnd,
 *              @p Fls_JobDataDestPtr, @p Fls_Job, @p Fls_JobResult).
 *
 * @param[in] SourceAddress        Source address in flash memory.
 * @param[in] Length               Number of bytes to read.
 * @param[out] TargetAddressPtr    Pointer to target data buffer.
 * @return Std_ReturnType
 * @retval E_OK                    Read command has been accepted.
 * @retval E_NOT_OK                Read command has not been accepted.
 *
 * @api
 *
 * @remarks Implements DFLS21107, DFLS21106, DFLS07000, DFLS07001, DFLS07002,
 *          DFLS07003, DFLS07004, DFLS07005, DFLS07006, DFLS07007, DFLS07009,
 *          DFLS07011
*/
/** @note Violates MISRA-C:2004 Advisory Rule 8.10: See @ref Fls_c_REF_19 */
FUNC( Std_ReturnType, FLS_CODE ) Fls_Read(
    VAR( Fls_AddressType, FLS_VAR) SourceAddress,
    P2VAR( uint8, AUTOMATIC, FLS_APPL_CONST ) TargetAddressPtr,
    VAR( Fls_LengthType, FLS_VAR) Length )
{
    VAR( Std_ReturnType, AUTOMATIC ) RetVal = (Std_ReturnType)E_OK;
    VAR( Fls_SectorIndexType, AUTOMATIC ) tmpJobSectorIt = 0UL;
    VAR( Fls_AddressType, AUTOMATIC ) tmpJobAddrEnd = 0UL;

/** @remarks Implements    DFLS07001 */
#if( FLS_DEV_ERROR_DETECT == STD_ON )
    /** @remarks Implements    DFLS07002 */
    if( NULL_PTR == Fls_ConfigPtr )
    {
        Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_READ_ID, FLS_E_UNINIT );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /** @remarks Implements    DFLS07003 */
    else if( SourceAddress >= FLS_TOTAL_SIZE )
    {
        Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_READ_ID, FLS_E_PARAM_ADDRESS );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /** @remarks Implements    DFLS07004 */
    else if(( 0U == Length ) || ((SourceAddress + Length) > FLS_TOTAL_SIZE ))
    {
        Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_READ_ID, FLS_E_PARAM_LENGTH );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /** @remarks Implements    DFLS07006 */
    else if( NULL_PTR == TargetAddressPtr )
    {
        Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_READ_ID, FLS_E_PARAM_DATA );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
#endif    /* FLS_DEV_ERROR_DETECT == STD_ON */

        /* Perform calculations outside the critical section in order
            to limit time spend in the CS */
        tmpJobSectorIt = Fls_GetSectorIndexByAddr( SourceAddress );
        tmpJobAddrEnd = ( SourceAddress + Length ) - 1U;

#if( FLS_DEV_ERROR_DETECT == STD_ON )
        /** @remarks Implements    DFLS07011 */
        SchM_Enter_Fls( SCHM_FLS_INSTANCE_0, FLS_EXCLUSIVE_AREA_12 );
        /** @remarks Implements    DFLS07005 */
#endif    /* FLS_DEV_ERROR_DETECT == STD_ON */
        if( MEMIF_JOB_PENDING == Fls_JobResult )
        {
#if( FLS_DEV_ERROR_DETECT == STD_ON )
            Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_READ_ID, FLS_E_BUSY );
#endif    /* FLS_DEV_ERROR_DETECT == STD_ON */
            RetVal = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
            /* Configure the read job */
            /** @remarks Implements    DFLS07007 */
            Fls_JobSectorIt = tmpJobSectorIt;
            Fls_JobAddrIt = SourceAddress;
            Fls_JobAddrEnd = tmpJobAddrEnd;
            Fls_JobDataDestPtr = TargetAddressPtr;
            Fls_Job = FLS_JOB_READ;
            Fls_JobStart = 1U;

            /** @remarks Implements    DFLS07009 */
            /* Execute the read job */
            Fls_JobResult = MEMIF_JOB_PENDING;

        }
#if( FLS_DEV_ERROR_DETECT == STD_ON )
        /** @remarks Implements    DFLS07011 */
        SchM_Exit_Fls( SCHM_FLS_INSTANCE_0, FLS_EXCLUSIVE_AREA_12 );
    }
#endif    /* FLS_DEV_ERROR_DETECT == STD_ON */

    return( RetVal );
}

/**
 * @brief       Compares a flash memory area with an application data buffer.
 * @details     Starts a compare job asynchronously. The actual job is performed by
 *              @p Fls_MainFunction.
 * @pre         The module has to be initialized and not busy.
 * @post        @p Fls_Read changes module status and some internal variables
 *              (@p Fls_JobSectorIt, @p Fls_JobAddrIt, @p Fls_JobAddrEnd,
 *              @p Fls_JobDataSrcPtr, @p Fls_Job, @p Fls_JobResult).
 *
 * @param[in] SourceAddress          Source address in flash memory.
 * @param[in] TargetAddressPtr       Pointer to source data buffer.
 * @param[in] Length                 Number of bytes to compare.
 * @return Std_ReturnType
 * @retval E_OK                      Compare command has been accepted.
 * retval E_NOT_OK                   Compare command has not been accepted.
 *
 * @api
 *
 * @remarks Implements DFLS08000, DFLS08001, DFLS08002, DFLS08003,
 *          DFLS08004, DFLS08005, DFLS08006, DFLS08007, DFLS08008, DFLS08010,
 *          DFLS08012
*/
/** @remarks Implements    DFLS08001 */
#if( FLS_COMPARE_API == STD_ON ) || defined(__DOXYGEN__)
/** @note Violates MISRA-C:2004 Advisory Rule 8.10: See @ref Fls_c_REF_19 */
FUNC( Std_ReturnType, FLS_CODE ) Fls_Compare(
    VAR( Fls_AddressType, FLS_VAR) SourceAddress,
    P2CONST( uint8, AUTOMATIC, FLS_APPL_CONST ) TargetAddressPtr,
    VAR( Fls_LengthType, FLS_VAR) Length )
{
    VAR( Std_ReturnType, AUTOMATIC ) RetVal = (Std_ReturnType)E_OK;
    VAR( Fls_SectorIndexType, AUTOMATIC ) tmpJobSectorIt = 0UL;
    VAR( Fls_AddressType, AUTOMATIC ) tmpJobAddrEnd = 0UL;

/** @remarks Implements    DFLS08002 */
#if( FLS_DEV_ERROR_DETECT == STD_ON )
    /** @remarks Implements    DFLS08003 */
    if( NULL_PTR == Fls_ConfigPtr )
    {
        Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_COMPARE_ID, FLS_E_UNINIT );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /** @remarks Implements    DFLS08004 */
    else if( SourceAddress >= FLS_TOTAL_SIZE )
    {
        Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_COMPARE_ID, FLS_E_PARAM_ADDRESS );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /** @remarks Implements    DFLS08005 */
    else if(( 0U == Length ) || ((SourceAddress + Length) > FLS_TOTAL_SIZE ))
    {
        Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_COMPARE_ID, FLS_E_PARAM_LENGTH );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /** @remarks Implements    DFLS08007 */
    else if( NULL_PTR == TargetAddressPtr )
    {
        Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_COMPARE_ID, FLS_E_PARAM_DATA );
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
#endif    /* FLS_DEV_ERROR_DETECT == STD_ON */

        /* Perform calculations outside the critical section in order
            to limit time spend in the CS */
        tmpJobSectorIt = Fls_GetSectorIndexByAddr( SourceAddress );
        tmpJobAddrEnd = ( SourceAddress + Length ) - 1U;

#if( FLS_DEV_ERROR_DETECT == STD_ON )
        /** @remarks Implements    DFLS08012 */
        SchM_Enter_Fls( SCHM_FLS_INSTANCE_0, FLS_EXCLUSIVE_AREA_13 );
        /** @remarks Implements    DFLS08006 */
#endif    /* FLS_DEV_ERROR_DETECT == STD_ON */
        if( MEMIF_JOB_PENDING == Fls_JobResult )
        {
#if( FLS_DEV_ERROR_DETECT == STD_ON )
            Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_COMPARE_ID, FLS_E_BUSY );
#endif    /* FLS_DEV_ERROR_DETECT == STD_ON */
            RetVal = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
            /** @remarks Implements    DFLS08008 */
            Fls_JobSectorIt = tmpJobSectorIt;
            Fls_JobAddrIt = SourceAddress;
            Fls_JobAddrEnd = tmpJobAddrEnd;
            Fls_JobDataSrcPtr = TargetAddressPtr;
            Fls_Job = FLS_JOB_COMPARE;
            Fls_JobStart = 1U;

            /** @remarks Implements    DFLS08010 */
            /* Execute the read job */
            Fls_JobResult = MEMIF_JOB_PENDING;

        }
#if( FLS_DEV_ERROR_DETECT == STD_ON )
        /** @remarks Implements    DFLS08012 */
        SchM_Exit_Fls( SCHM_FLS_INSTANCE_0, FLS_EXCLUSIVE_AREA_13 );
    }
#endif    /* FLS_DEV_ERROR_DETECT == STD_ON */

    return( RetVal );
}
#endif /* FLS_COMPARE_API == STD_ON */

/**
 * @brief       Sets the FLS module's operation mode to the given Mode.
 * @details     Every given mode determinates maximum bytes for read/write
 *              operations. Every mode has a set of pre-configured values.
 * @pre         The module has to be initialized and not busy.
 * @post        @p Fls_SetMode changes internal variables @p Fls_MaxRead and
 *              @p Fls_MaxWrite.
 *
 * @param[in] Mode        MEMIF_MODE_FAST or MEMIF_MODE_SLOW.
 *
 * @api
 *
 * @remarks Implements DFLS21108, DFLS09000, DFLS09001, DFLS09002, DFLS09003,
 *          DFLS09004, DFLS09005
*/
/** @remarks Implements    DFLS09001 */
#if( FLS_SET_MODE_API == STD_ON )|| defined (__DOXYGEN__)
/** @note Violates MISRA-C:2004 Advisory Rule 8.10: See @ref Fls_c_REF_19 */
FUNC( void, FLS_CODE ) Fls_SetMode(
    VAR( MemIf_ModeType, FLS_VAR ) Mode )
{
/** @remarks Implements    DFLS09002 */
#if( FLS_DEV_ERROR_DETECT == STD_ON )
    /** @remarks Implements    DFLS09003 */
    if( NULL_PTR == Fls_ConfigPtr )
    {
        Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SETMODE_ID, FLS_E_UNINIT );
    }
    /** @remarks Implements    DFLS09004 */
    else if( MEMIF_JOB_PENDING == Fls_JobResult )
    {
        Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SETMODE_ID, FLS_E_BUSY );
    }
    else
    {
#endif    /* FLS_DEV_ERROR_DETECT == STD_ON */
        /** @remarks Implements    DFLS09005 */
        /* Set the max number of bytes to read/write
            during Fls_MainFunction call */
        switch( Mode )
        {
            case MEMIF_MODE_FAST:
                Fls_MaxRead = Fls_ConfigPtr->maxReadFastMode;
                Fls_MaxWrite = Fls_ConfigPtr->maxWriteFastMode;
                break;

            case MEMIF_MODE_SLOW:
                Fls_MaxRead = Fls_ConfigPtr->maxReadNormalMode;
                Fls_MaxWrite = Fls_ConfigPtr->maxWriteNormalMode;
                break;

            default:
                /* Compiler_Warning: Added CER for Catastrophic events */
                Cer_ReportError( (uint16) FLS_MODULE_ID, (uint8)FLS_INSTANCE_ID, (uint8)FLS_SID_SETCLOCKMODE, (uint8)FLS_E_DEFAULT);
            break;
        }
#if( FLS_DEV_ERROR_DETECT == STD_ON )
    }
#endif    /* FLS_DEV_ERROR_DETECT == STD_ON */
}
#endif /* FLS_SET_MODE_API == STD_ON */

/**
 * @brief       Returns version information about FLS module.
 * @details     Version information includes:
 *              - Module Id,
 *              - Vendor Id,
 *              - Vendor specific version numbers.
 *              .
 *
 * @param[in,out] VersionInfoPtr     Where to store module version informations.
 *
 * @api
 *
 * @remarks Implements DFLS21109, DFLS10000, DFLS10001, DFLS10002, DFLS10003
*/
/** @remarks Implements    DFLS10001 */
#if( FLS_VERSION_INFO_API == STD_ON )|| defined(__DOXYGEN__)
/** @note Violates MISRA-C:2004 Advisory Rule 8.10: See @ref Fls_c_REF_19 */
FUNC( void, FLS_CODE ) Fls_GetVersionInfo(
    P2VAR( Std_VersionInfoType, AUTOMATIC, FLS_APPL_DATA ) VersionInfoPtr )
/** @note Violates MISRA-C:2004 Advisory Rule 16.4, The identifiers used in the declaration and
definition of a function shall be identical: See @ref Fls_c_REF_18 */
{
/** @remarks Implements    DFLS10002 */
#if( FLS_DEV_ERROR_DETECT == STD_ON )
    if( VersionInfoPtr == NULL_PTR )
    {
        Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_GETVERSIONINFO_ID, \
                 FLS_E_PARAM_POINTER );
    }
    else
    {
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
        /** @remarks Implements    DFLS10003 */
        VersionInfoPtr->moduleID = FLS_MODULE_ID;
        VersionInfoPtr->vendorID = FLS_VENDOR_ID;
        VersionInfoPtr->instanceID = FLS_INSTANCE_ID;
        VersionInfoPtr->sw_major_version = FLS_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = FLS_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = FLS_SW_PATCH_VERSION;
#if( FLS_DEV_ERROR_DETECT == STD_ON )
    }
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
}
#endif /* FLS_VERSION_INFO_API == STD_ON */

/**
 * @brief       Performs actual flash read, write, erase and compare jobs.
 * @details     Bytes number processed per cycle depends by job type (read, write,
 *              compare) and current FLS module's operating mode (normal, fast).
 * @pre         The module has to be initialized.
 * @note        This function have to be called ciclically by the Basic Software
 *              Module; it will do nothing if there aren't pending job.
 *
 * @api
 *
 * @remarks Implements DFLS21110, DFLS11000, DFLS11001, DFLS11002, DFLS11003,
 *          DFLS11200, DFLS11100, DFLS11005, DFLS11006, DFLS11007, DFLS11008,
 *          DFLS11009, DFLS11010, DFLS11011, DFLS11012, DFLS11013
*/
/** @note Violates MISRA-C:2004 Advisory Rule 8.10: See @ref Fls_c_REF_19 */
FUNC( void, FLS_CODE ) Fls_MainFunction( void )
{
/** @remarks Implements    DFLS11001 */
#if( FLS_DEV_ERROR_DETECT == STD_ON )
    if( NULL_PTR == Fls_ConfigPtr )
    {
        Det_ReportError( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_MAINFUNCTION_ID,
            FLS_E_UNINIT );
    }
    else
    {
#endif    /* FLS_DEV_ERROR_DETECT == STD_ON */
        /** @remarks Implements    DFLS11002 */
        if( MEMIF_JOB_PENDING == Fls_JobResult )
        {
            /** @remarks Implements    DFLS11010 */
            VAR(MemIf_JobResultType, AUTOMATIC) workResult = MEMIF_JOB_OK;

            /** @remarks Implements    DFLS11013 */
            if( 1U == Fls_JobStart )
            {
                Fls_JobStart = 0U;

/** @remarks Implements    DFLS11012  */
#if( FLS_AC_LOAD_ON_JOB_START == STD_ON )
                /* Load position independent access code */
                if(( FLS_JOB_ERASE == Fls_Job ) || ( FLS_JOB_WRITE == Fls_Job ))
                {
                    Fls_LoadAc( Fls_Job );
                }
                else
                {
                    /* Fls_Job != FLS_JOB_ERASE &&  Fls_Job != FLS_JOB_WRITE */
                }
#endif /* FLS_AC_LOAD_ON_JOB_START == STD_ON */

                /* Clear result of hardware job */
                /** @remarks Implements    DFLS11011 */
                Fls_LLD_ClrJobResult();
            }
            else
            {
                /* Fls_JobStart != 1U */
            }

            /** @remarks Implements    DFLS11010 */
            if(( FLS_JOB_ERASE == Fls_Job ) || ( FLS_JOB_WRITE == Fls_Job ))
            {
                /* Process ongoing erase or write asynchronous hardware job */
                Fls_LLD_MainFunction();

                /* Get status/result of ongoing erase or write asynchronous
                    hardware job */
                workResult = Fls_LLD_GetJobResult();
            }
            else
            {
                /* FLS_JOB_READ and FLS_JOB_COMPARE jobs are
                    always synchronous */
            }

            if( MEMIF_JOB_OK == workResult )
            {
                /** @remarks Implements    DFLS11003 */
                switch( Fls_Job )
                {
                    case FLS_JOB_ERASE:
                            /** @remarks Implements    DFLS11200 */
                            workResult = Fls_DoJobErase();
                        break;
                    case FLS_JOB_WRITE:
                            /** @remarks Implements    DFLS11100 */
                            workResult = Fls_DoJobDataTransfer(
                                Fls_Job, Fls_MaxWrite );
                        break;
                    case FLS_JOB_READ:
    /* For Read and Compare jobs the static function Fls_DoJobDataTransfer( )
                will be used with the same input parameters */
#if( FLS_COMPARE_API == STD_ON )
                    case FLS_JOB_COMPARE:
#endif /* FLS_COMPARE_API == STD_ON */
                            /** @remarks Implements    DFLS11100 */
                            workResult = Fls_DoJobDataTransfer(
                                Fls_Job, Fls_MaxRead );
                        break;
                    default:
                        /* Compiler_Warning: Added CER for Catastrophic events */
                        Cer_ReportError( (uint16) FLS_MODULE_ID, (uint8)FLS_INSTANCE_ID, (uint8)FLS_SID_SETCLOCKMODE, (uint8)FLS_E_DEFAULT);
                        break;
                }
            }
            else
            {
                /* workResult != MEMIF_JOB_OK */
            }

/** @remarks Implements    DFLS11005 */
#if( FLS_AC_LOAD_ON_JOB_START == STD_ON )
            if(( MEMIF_JOB_PENDING != workResult ) &&
                (( FLS_JOB_ERASE == Fls_Job ) || ( FLS_JOB_WRITE == Fls_Job )))
            {
                Fls_UnloadAc( Fls_Job );
            }
#endif

            /** @remarks Implements    DFLS11006 */
            Fls_JobResult = workResult;

            /** @remarks Implements    DFLS11004, DFLS11007 */
            if( MEMIF_JOB_OK == workResult )
            {
                /** @remarks Implements    DFLS11009 */
                if( NULL_PTR != Fls_ConfigPtr->jobEndNotificationPtr )
                {
                    /* Call FlsJobEndNotification function if configured */
                    Fls_ConfigPtr->jobEndNotificationPtr();
                }
                else
                {
                    /* Callback notification configured as null pointer */
                }
            }
            /** @remarks Implements    DFLS11007 */
            else if(( MEMIF_JOB_FAILED == workResult ) ||
                ( MEMIF_BLOCK_INCONSISTENT == workResult ))
            {
                /** @remarks Implements    DFLS11008 */
                if( NULL_PTR != Fls_ConfigPtr->jobErrorNotificationPtr )
                {
                    /* Call FlsJobErrorNotification function if configured */
                    Fls_ConfigPtr->jobErrorNotificationPtr();
                }
                else
                {
                    /* Callback notification configured as null pointer */
                }
            }
            else
            {
                /* Not done yet. There is more data to transfer in following
                    Fls_MainFunction call */
            }
        }
        else
        {
            /* Nothing to do since no job is pending */
        }
#if( FLS_DEV_ERROR_DETECT == STD_ON )
    }
#endif    /* FLS_DEV_ERROR_DETECT == STD_ON */
}

#define FLS_STOP_SEC_CODE
/** @note Violates MISRA-C:2004 Advisory Rule 19.1, 19.15: See @ref Fls_c_REF_1 */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

/** @}*/
