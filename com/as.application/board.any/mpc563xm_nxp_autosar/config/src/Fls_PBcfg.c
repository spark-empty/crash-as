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
STATIC CONST(Fls_AddressType, FLS_CONST) FlsConfigSet_0_FlsSectorEndAddr[2] = 
{
    65535U, /* FlsSectorEndAddr (FlsSector_0)*/
    131071U /* FlsSectorEndAddr (FlsSector_1)*/
};

/* FlsPhysicalSector[] (FlsConfigSet_0) */
STATIC CONST(Fls_LLD_PhysicalSectorType, FLS_CONST) FlsConfigSet_0_FlsPhysicalSector[2] = 
{
    FLS_CODE_ARRAY_0_A_L06, /* FlsPhysicalSector (FlsSector_0) */
    FLS_CODE_ARRAY_0_A_L07 /* FlsPhysicalSector (FlsSector_1) */
};

/* FlsSectorFlags[] (FlsConfigSet_0) */
STATIC CONST(uint8, FLS_CONST) FlsConfigSet_0_FlsSectorFlags[2] = 
{
    0U, /* (FlsSector_0) */
    0U /* (FlsSector_1) */
};

/* FlsPageSize[] (FlsConfigSet_0) */
STATIC CONST(Fls_LengthType, FLS_CONST) FlsConfigSet_0_FlsPageSize[2] = 
{
    8U, /* FlsPageSize (FlsSector_0) */
    8U /* FlsPageSize (FlsSector_1) */
};

/* FlsSectorUnlock[] (FlsConfigSet_0) */
STATIC CONST(uint8, FLS_CONST) FlsConfigSet_0_FlsSectorUnlock[2] = 
{
    1U, /* (FlsSector_0) */
    1U /* (FlsSector_1) */
};

/* Fls module initialization data (FlsConfigSet_0)*/
CONST(Fls_ConfigType, FLS_CONST) FlsConfigSet_0 = 
{
    (Fls_LLD_AcErasePtrType)Fls_AcErase, /* FlsAcErase */
    (Fls_LLD_AcWritePtrType)Fls_AcWrite, /* FlsAcWrite */
    NULL_PTR, /* FlsACCallback */
    NULL_PTR, /* FlsJobEndNotification */
    NULL_PTR, /* FlsJobErrorNotification */
    1048576U, /* FlsMaxReadFastMode */
    1024U, /* FlsMaxReadNormalMode */
    256U, /* FlsMaxWriteFastMode */
    8U, /* FlsMaxWriteNormalMode */
    2U, /* FlsSectorCount */
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
