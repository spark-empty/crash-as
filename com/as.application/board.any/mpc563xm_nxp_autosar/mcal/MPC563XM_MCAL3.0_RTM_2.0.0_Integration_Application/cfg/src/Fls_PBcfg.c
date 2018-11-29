/**
    @file    Fls_PBcfg.c
    @version 2.0.8.0

    @brief   AUTOSAR Fls - AUTOSAR Module Flash Driver
    @details Definitions of all post-build configuration structures
    
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

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#define FLS_START_SEC_CODE
#include "MemMap.h"

/* Declaration of Fls notification function (Fee_JobEndNotification())*/
extern FUNC( void, FLS_CODE ) Fee_JobEndNotification( void );

/* Declaration of Fls notification function (Fee_JobErrorNotification())*/
extern FUNC( void, FLS_CODE ) Fee_JobErrorNotification( void );

#define FLS_STOP_SEC_CODE
#include "MemMap.h"


/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

#define FLS_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* Position independent erase access code */
extern CONST(uint32, FLS_CONST) Fls_AcErase[];

/* Position independent write access code */
extern CONST(uint32, FLS_CONST) Fls_AcWrite[];

#define FLS_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#define FLS_START_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

/* FlsSectorEndAddr[] (FlsConfigSet_0) */
STATIC CONST(Fls_AddressType, FLS_CONST) FlsConfigSet_0_FlsSectorEndAddr[12] = 
{
    16383U, /* FlsSectorEndAddr (FlsSector_0)*/
    32767U, /* FlsSectorEndAddr (FlsSector_1)*/
    65535U, /* FlsSectorEndAddr (FlsSector_2)*/
    98303U, /* FlsSectorEndAddr (FlsSector_3)*/
    114687U, /* FlsSectorEndAddr (FlsSector_4)*/
    131071U, /* FlsSectorEndAddr (FlsSector_5)*/
    196607U, /* FlsSectorEndAddr (FlsSector_6)*/
    262143U, /* FlsSectorEndAddr (FlsSector_7)*/
    393215U, /* FlsSectorEndAddr (FlsSector_8)*/
    524287U, /* FlsSectorEndAddr (FlsSector_9)*/
    655359U, /* FlsSectorEndAddr (FlsSector_10)*/
    786431U /* FlsSectorEndAddr (FlsSector_11)*/
};

/* FlsPhysicalSector[] (FlsConfigSet_0) */
STATIC CONST(Fls_LLD_PhysicalSectorType, FLS_CONST) FlsConfigSet_0_FlsPhysicalSector[12] = 
{
    FLS_CODE_ARRAY_0_A_L00, /* FlsPhysicalSector (FlsSector_0) */
    FLS_CODE_ARRAY_0_A_L01, /* FlsPhysicalSector (FlsSector_1) */
    FLS_CODE_ARRAY_0_A_L02, /* FlsPhysicalSector (FlsSector_2) */
    FLS_CODE_ARRAY_0_A_L03, /* FlsPhysicalSector (FlsSector_3) */
    FLS_CODE_ARRAY_0_A_L04, /* FlsPhysicalSector (FlsSector_4) */
    FLS_CODE_ARRAY_0_A_L05, /* FlsPhysicalSector (FlsSector_5) */
    FLS_CODE_ARRAY_0_A_L06, /* FlsPhysicalSector (FlsSector_6) */
    FLS_CODE_ARRAY_0_A_L07, /* FlsPhysicalSector (FlsSector_7) */
    FLS_CODE_ARRAY_0_A_M00, /* FlsPhysicalSector (FlsSector_8) */
    FLS_CODE_ARRAY_0_A_M01, /* FlsPhysicalSector (FlsSector_9) */
    FLS_CODE_ARRAY_1_B_H00, /* FlsPhysicalSector (FlsSector_10) */
    FLS_CODE_ARRAY_1_B_H01 /* FlsPhysicalSector (FlsSector_11) */
};

/* FlsSectorFlags[] (FlsConfigSet_0) */
STATIC CONST(uint8, FLS_CONST) FlsConfigSet_0_FlsSectorFlags[12] = 
{
    0U, /* (FlsSector_0) */
    0U, /* (FlsSector_1) */
    0U, /* (FlsSector_2) */
    0U, /* (FlsSector_3) */
    0U, /* (FlsSector_4) */
    0U, /* (FlsSector_5) */
    0U, /* (FlsSector_6) */
    0U, /* (FlsSector_7) */
    FLS_SECTOR_ERASE_ASYNCH, /* (FlsSector_8) */
    FLS_SECTOR_ERASE_ASYNCH, /* (FlsSector_9) */
    0U, /* (FlsSector_10) */
    0U /* (FlsSector_11) */
};

/* FlsPageSize[] (FlsConfigSet_0) */
STATIC CONST(Fls_LengthType, FLS_CONST) FlsConfigSet_0_FlsPageSize[12] = 
{
    8U, /* FlsPageSize (FlsSector_0) */
    8U, /* FlsPageSize (FlsSector_1) */
    8U, /* FlsPageSize (FlsSector_2) */
    8U, /* FlsPageSize (FlsSector_3) */
    8U, /* FlsPageSize (FlsSector_4) */
    8U, /* FlsPageSize (FlsSector_5) */
    8U, /* FlsPageSize (FlsSector_6) */
    8U, /* FlsPageSize (FlsSector_7) */
    8U, /* FlsPageSize (FlsSector_8) */
    8U, /* FlsPageSize (FlsSector_9) */
    8U, /* FlsPageSize (FlsSector_10) */
    8U /* FlsPageSize (FlsSector_11) */
};

/* FlsSectorUnlock[] (FlsConfigSet_0) */
STATIC CONST(uint8, FLS_CONST) FlsConfigSet_0_FlsSectorUnlock[12] = 
{
    1U, /* (FlsSector_0) */
    1U, /* (FlsSector_1) */
    1U, /* (FlsSector_2) */
    1U, /* (FlsSector_3) */
    1U, /* (FlsSector_4) */
    1U, /* (FlsSector_5) */
    1U, /* (FlsSector_6) */
    1U, /* (FlsSector_7) */
    1U, /* (FlsSector_8) */
    1U, /* (FlsSector_9) */
    1U, /* (FlsSector_10) */
    1U /* (FlsSector_11) */
};

/* Fls module initialization data (FlsConfigSet_0)*/
CONST(Fls_ConfigType, FLS_CONST) FlsConfigSet_0 = 
{
    (Fls_LLD_AcErasePtrType)Fls_AcErase, /* FlsAcErase */
    (Fls_LLD_AcWritePtrType)Fls_AcWrite, /* FlsAcWrite */
    NULL_PTR, /* FlsACCallback */
    Fee_JobEndNotification, /* FlsJobEndNotification */
    Fee_JobErrorNotification, /* FlsJobErrorNotification */
    1048576U, /* FlsMaxReadFastMode */
    1024U, /* FlsMaxReadNormalMode */
    256U, /* FlsMaxWriteFastMode */
    16U, /* FlsMaxWriteNormalMode */
    12U, /* FlsSectorCount */
    FlsConfigSet_0_FlsSectorEndAddr, /* FlsSectorEndAddr[]  */
    FlsConfigSet_0_FlsPhysicalSector, /* FlsPhysicalSector[] */
    FlsConfigSet_0_FlsSectorFlags, /* FlsSectorFlags[] */
    FlsConfigSet_0_FlsPageSize, /* FlsPageSize[] */
    FlsConfigSet_0_FlsSectorUnlock /* FlsSectorUnlock[] */

};

#define FLS_STOP_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

#ifdef __cplusplus
}
#endif
