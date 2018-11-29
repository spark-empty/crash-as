[!CODE!][!//
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

[!IF "count(text:grep(FlsConfigSet/*/FlsJobEndNotification | FlsConfigSet/*/FlsJobErrorNotification | FlsConfigSet/*/FlsACCallback, '^(\s*NULL_PTR\s*)|(\s*NULL\s*)$')) != count(FlsConfigSet/*) * 3"!][!//
/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#define FLS_START_SEC_CODE
#include "MemMap.h"

[!LOOP "text:order(text:split(normalize-space(text:join(FlsConfigSet/*/FlsJobEndNotification | FlsConfigSet/*/FlsJobErrorNotification | FlsConfigSet/*/FlsACCallback))))"!][!//
[!IF ". != 'NULL_PTR' and . != 'NULL'"!][!//
/* Declaration of Fls notification function ([!"."!]())*/
extern FUNC( void, FLS_CODE ) [!"."!]( void );

[!ENDIF!][!//
[!ENDLOOP!][!//
#define FLS_STOP_SEC_CODE
#include "MemMap.h"

[!ENDIF!][!//

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

[!IF "FlsGeneral/FlsAcLoadOnJobStart != 'true'"!][!//
#define FLS_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* Position independent erase access code */
extern CONST(uint32, FLS_CONST) Fls_AcErase[];

/* Position independent write access code */
extern CONST(uint32, FLS_CONST) Fls_AcWrite[];

#define FLS_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
[!ELSE!][!//

[!IF "count(text:grep(FlsConfigSet/*/FlsAcErasePointer | FlsConfigSet/*/FlsAcWritePointer, '^(\s*NULL_PTR\s*)|(\s*NULL\s*)$')) != count(FlsConfigSet/*) * 2"!][!//

#define FLS_START_SEC_CODE
#include "MemMap.h"

[!LOOP "text:order(text:split(normalize-space(text:join(FlsConfigSet/*/FlsAcErasePointer | FlsConfigSet/*/FlsAcWritePointer))))"!][!//
[!IF ". != 'NULL_PTR' and . != 'NULL'"!][!//
/* Declaration of Fls Access Code Pointer ([!"."!])*/
extern char [!"."!];

[!ENDIF!][!//
[!ENDLOOP!][!//
#define FLS_STOP_SEC_CODE
#include "MemMap.h"

[!ENDIF!][!//

[!ENDIF!][!//
#define FLS_START_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

[!LOOP "FlsConfigSet/*"!][!//
/* FlsSectorEndAddr[] ([!"node:name(.)"!]) */
STATIC CONST(Fls_AddressType, FLS_CONST) [!"node:name(.)"!]_FlsSectorEndAddr[[!"num:i(count(FlsSectorList/FlsSector/*))"!]] = 
{
[!LOOP "FlsSectorList/FlsSector/*"!][!//
    [!"num:i(./FlsSectorSize + ./FlsSectorStartaddress - 1)"!]U[!IF "not(node:islast())"!],[!ENDIF!] /* FlsSectorEndAddr ([!"node:name(.)"!])*/
[!ENDLOOP!][!//
};

/* FlsPhysicalSector[] ([!"node:name(.)"!]) */
STATIC CONST(Fls_LLD_PhysicalSectorType, FLS_CONST) [!"node:name(.)"!]_FlsPhysicalSector[[!"num:i(count(FlsSectorList/FlsSector/*))"!]] = 
{
[!LOOP "FlsSectorList/FlsSector/*"!][!//
    [!"./FlsPhysicalSector"!][!IF "not(node:islast())"!],[!ENDIF!] /* FlsPhysicalSector ([!"node:name(.)"!]) */
[!ENDLOOP!][!//
};

/* FlsSectorFlags[] ([!"node:name(.)"!]) */
STATIC CONST(uint8, FLS_CONST) [!"node:name(.)"!]_FlsSectorFlags[[!"num:i(count(FlsSectorList/FlsSector/*))"!]] = 
{
[!LOOP "FlsSectorList/FlsSector/*"!][!//
[!VAR "FLS_FLAG" = "0"!][!//
    [!IF "./FlsSectorEraseAsynch"!]FLS_SECTOR_ERASE_ASYNCH[!VAR "FLS_FLAG" = "1"!][!ENDIF!][!//
[!IF "./FlsPageWriteAsynch"!][!IF "$FLS_FLAG = 1"!] | [!ELSE!][!VAR "FLS_FLAG" = "1"!][!ENDIF!]FLS_PAGE_WRITE_ASYNCH[!ENDIF!][!//
[!IF "$FLS_FLAG = 0"!]0U[!ENDIF!][!IF "not(node:islast())"!],[!ENDIF!] /* ([!"node:name(.)"!]) */
[!ENDLOOP!][!//
};

/* FlsPageSize[] ([!"node:name(.)"!]) */
STATIC CONST(Fls_LengthType, FLS_CONST) [!"node:name(.)"!]_FlsPageSize[[!"num:i(count(FlsSectorList/FlsSector/*))"!]] = 
{
[!LOOP "FlsSectorList/FlsSector/*"!][!//
    [!"./FlsPageSize"!]U[!IF "not(node:islast())"!],[!ENDIF!] /* FlsPageSize ([!"node:name(.)"!]) */
[!ENDLOOP!][!//
};

/* FlsSectorUnlock[] ([!"node:name(.)"!]) */
STATIC CONST(uint8, FLS_CONST) [!"node:name(.)"!]_FlsSectorUnlock[[!"num:i(count(FlsSectorList/FlsSector/*))"!]] = 
{
[!LOOP "FlsSectorList/FlsSector/*"!][!//
    [!IF "./FlsPhysicalSectorUnlock"!]1U[!ELSE!]0U[!ENDIF!][!IF "not(node:islast())"!],[!ENDIF!] /* ([!"node:name(.)"!]) */
[!ENDLOOP!][!//
};

/* Fls module initialization data ([!"node:name(.)"!])*/
CONST(Fls_ConfigType, FLS_CONST) [!"node:name(.)"!] = 
{
    (Fls_LLD_AcErasePtrType)[!IF "../../FlsGeneral/FlsAcLoadOnJobStart"!][!IF "normalize-space(./FlsAcErasePointer) = 'NULL_PTR' or normalize-space(./FlsAcErasePointer) = 'NULL'"!][!"normalize-space(./FlsAcErase)"!][!ELSE!]&[!"./FlsAcErasePointer"!][!ENDIF!][!ELSE!]Fls_AcErase[!ENDIF!], /* FlsAcErase */
    (Fls_LLD_AcWritePtrType)[!IF "../../FlsGeneral/FlsAcLoadOnJobStart"!][!IF "normalize-space(./FlsAcWritePointer) = 'NULL_PTR' or normalize-space(./FlsAcWritePointer) = 'NULL'"!][!"normalize-space(./FlsAcWrite)"!][!ELSE!]&[!"./FlsAcWritePointer"!][!ENDIF!][!ELSE!]Fls_AcWrite[!ENDIF!], /* FlsAcWrite */
    [!IF "normalize-space(./FlsACCallback) = 'NULL'"!]NULL_PTR[!ELSE!][!"./FlsACCallback"!][!ENDIF!], /* FlsACCallback */
    [!IF "normalize-space(./FlsJobEndNotification) = 'NULL'"!]NULL_PTR[!ELSE!][!"./FlsJobEndNotification"!][!ENDIF!], /* FlsJobEndNotification */
    [!IF "normalize-space(./FlsJobErrorNotification) = 'NULL'"!]NULL_PTR[!ELSE!][!"./FlsJobErrorNotification"!][!ENDIF!], /* FlsJobErrorNotification */
    [!"./FlsMaxReadFastMode"!]U, /* FlsMaxReadFastMode */
    [!"./FlsMaxReadNormalMode"!]U, /* FlsMaxReadNormalMode */
    [!"./FlsMaxWriteFastMode"!]U, /* FlsMaxWriteFastMode */
    [!"./FlsMaxWriteNormalMode"!]U, /* FlsMaxWriteNormalMode */
    [!"num:i(count(FlsSectorList/FlsSector/*))"!]U, /* FlsSectorCount */
    [!"node:name(.)"!]_FlsSectorEndAddr, /* FlsSectorEndAddr[]  */
    [!"node:name(.)"!]_FlsPhysicalSector, /* FlsPhysicalSector[] */
    [!"node:name(.)"!]_FlsSectorFlags, /* FlsSectorFlags[] */
    [!"node:name(.)"!]_FlsPageSize, /* FlsPageSize[] */
    [!"node:name(.)"!]_FlsSectorUnlock /* FlsSectorUnlock[] */

};

[!ENDLOOP!][!//
[!ENDCODE!][!//
#define FLS_STOP_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

#ifdef __cplusplus
}
#endif
