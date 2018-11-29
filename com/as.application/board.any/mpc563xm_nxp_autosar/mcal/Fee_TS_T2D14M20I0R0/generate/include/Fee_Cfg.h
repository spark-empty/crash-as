[!CODE!][!//
/**
    @file    Fee_Cfg.h
    @version 2.0.4.0

    @brief   AUTOSAR Fee - AUTOSAR Module Flash EEPROM Emulation Driver
    @details Definitions of all pre-compile configuration parameters
    
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
*/
/*==================================================================================================
==================================================================================================*/
/*================================================================================================*/
/**
@page misra_violations MISRA-C:2004 violations

@section Fee_Cfg_c_REF_1
Violates MISRA-C:2004: Advisory Rule 19.1, only preprocessor statements and comments before '#include'.
This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003. 

@section Fee_Cfg_c_REF_2
Violates MISRA-C:2004 Required Rule 19.15, Repeatedly included but does not have a standard include guard. 
This violation is due to AUTOSAR requirement MEMMAP003.  

**/
#ifndef _FEE_CFG_H_
#define _FEE_CFG_H_

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Fee_Types.h"

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

[!VAR "FEE_VIRTUAL_PAGE_SIZE" = "num:i(FeeGeneral/FeeVirtualPageSize)"!][!//
[!VAR "FEE_BLOCK_OVERHEAD" = "num:i(ceiling(12 div $FEE_VIRTUAL_PAGE_SIZE + 2) * [!//
                                                     $FEE_VIRTUAL_PAGE_SIZE)"!][!//
[!VAR "FEE_CLUSTER_OVERHEAD" = "num:i(ceiling(16 div $FEE_VIRTUAL_PAGE_SIZE + 2) * [!//
                                                      $FEE_VIRTUAL_PAGE_SIZE)"!][!//

/* Pre-processor switch to enable and disable development error detection */
#define FEE_DEV_ERROR_DETECT                [!IF "FeeGeneral/FeeDevErrorDetect"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
                                        
/* Pre-processor switch to enable / disable the API to read out the modules
    version information */
#define FEE_VERSION_INFO_API                [!IF "FeeGeneral/FeeVersionInfoApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/* The size in bytes to which logical blocks shall be aligned */
#define FEE_VIRTUAL_PAGE_SIZE               [!"$FEE_VIRTUAL_PAGE_SIZE"!]U

/* Job end notification routine provided by the upper layer    module (declaration) */
#define FEE_NVM_JOB_END_NOTIFICATION_DECL   [!IF "normalize-space(FeeGeneral/FeeNvmJobEndNotification) != 'NULL' and normalize-space(FeeGeneral/FeeNvmJobEndNotification) != 'NULL_PTR' "!] extern void [!"normalize-space(FeeGeneral/FeeNvmJobEndNotification)"!](void);[!ENDIF!]

/* Job end notification routine provided by the upper layer    module */
#define FEE_NVM_JOB_END_NOTIFICATION        [!IF "normalize-space(FeeGeneral/FeeNvmJobEndNotification) != 'NULL' and normalize-space(FeeGeneral/FeeNvmJobEndNotification) != 'NULL_PTR' "!][!"normalize-space(FeeGeneral/FeeNvmJobEndNotification)"!]();[!ENDIF!]

/* Job error notification routine provided by the upper layer module (declaration) */
#define FEE_NVM_JOB_ERROR_NOTIFICATION_DECL [!IF "normalize-space(FeeGeneral/FeeNvmJobErrorNotification) != 'NULL' and normalize-space(FeeGeneral/FeeNvmJobErrorNotification) != 'NULL_PTR' "!] extern void [!"normalize-space(FeeGeneral/FeeNvmJobErrorNotification)"!](void);[!ENDIF!]

/* Job error notification routine provided by the upper layer module */
#define FEE_NVM_JOB_ERROR_NOTIFICATION      [!IF "normalize-space(FeeGeneral/FeeNvmJobErrorNotification) != 'NULL' and normalize-space(FeeGeneral/FeeNvmJobErrorNotification) != 'NULL_PTR' "!][!"normalize-space(FeeGeneral/FeeNvmJobErrorNotification)"!]();[!ENDIF!]

/* Number of configured Fee cluster groups */
#define FEE_NUMBER_OF_CLUSTER_GROUPS        [!"num:i(count(FeeClusterGroup/*))"!]U

/* Number of configured Fee blocks */
#define FEE_NUMBER_OF_BLOCKS                [!"num:i(count(FeeBlockConfiguration/*))"!]U

/* Management overhead per logical block in bytes */
#define FEE_BLOCK_OVERHEAD                  [!"$FEE_BLOCK_OVERHEAD"!]U

/* Management overhead per logical cluster in bytes */
#define FEE_CLUSTER_OVERHEAD                [!"$FEE_CLUSTER_OVERHEAD"!]U

/* Size of the data buffer in bytes */
#define FEE_DATA_BUFFER_SIZE                [!"num:i(FeeGeneral/FeeDataBufferSize)"!]U

/* The contents of an erased flash memory cell */
#define FEE_ERASED_VALUE                    [!"num:inttohex(bit:and(as:modconf('Fls')[1]/FlsPublishedInformation/FlsErasedValue,255),2)"!]U

/* Value of the block and cluster validation flag */
#define FEE_VALIDATED_VALUE                [!"num:inttohex(bit:and(bit:xor(as:modconf('Fls')[1]/FlsPublishedInformation/FlsErasedValue,126),255),2)"!]U

/* Value of the block and cluster invalidation flag */
#define FEE_INVALIDATED_VALUE              [!"num:inttohex(bit:and(bit:xor(as:modconf('Fls')[1]/FlsPublishedInformation/FlsErasedValue,231),255),2)"!]U

/* If reset, power loss etc. occurs here, neither newly nor previously written data is available */
#define FEE_BLOCK_ALWAYS_AVAILABLE          [!IF "FeeGeneral/FeeBlockAlwaysAvailable"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!SELECT "as:modconf('Fls')"!][!//
/* Compile switch to enable /disable the Fls_Cancel function */
#define FEE_CANCEL_API                ([!IF "FlsGeneral/FlsCancelApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

/* Compile switch to enable /disable the Fls_SetMode function */
#define FEE_SET_MODE_API              ([!IF "FlsGeneral/FlsSetModeApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
[!ENDSELECT!][!//


/* Symbolic names of configured Fee blocks */
[!LOOP "node:order(FeeBlockConfiguration/*,'node:value(./FeeBlockNumber)')"!][!//
#define [!"node:name(.)"!]        [!"./FeeBlockNumber"!]U
[!ENDLOOP!][!//

#define FEE_START_SEC_CONST_UNSPECIFIED
/** @note Violates MISRA-C:2004 Advisory Rule 19.1,only preprocessor statements and comments before 
          '#include'. See @ref Fee_Cfg_c_REF_1 */
/** @note Violates MISRA-C:2004 Required Rule 19.15, Repeatedly included but does not have a standard 
          include guard. See @ref Fee_Cfg_c_REF_2 */
#include "MemMap.h"

[!LOOP "FeeClusterGroup/*"!][!//

/* Configuration of cluster group [!"node:name(.)"!] */
extern CONST(Fee_ClusterType, FEE_CONST) Fee_[!"node:name(.)"!][[!"num:i(count(FeeCluster/*))"!]];
[!VAR "FEE_SMALLEST_CLUSTER_SIZE" = "2147483647"!][!//
[!VAR "FEE_LOOP_IT" = "count(FeeCluster/*)"!][!//
[!LOOP "FeeCluster/*"!][!//
[!VAR "FEE_CLUSTER_SIZE" = "0"!][!//
[!LOOP "FeeSector/*"!][!//
[!VAR "FEE_CLUSTER_SIZE" = "$FEE_CLUSTER_SIZE + num:i(node:ref(./FeeSectorRef)/FlsSectorSize) * [!//
                                           num:i(node:ref(./FeeSectorRef)/FlsNumberOfSectors)"!][!//
[!ENDLOOP!][!//
[!IF "$FEE_CLUSTER_SIZE < $FEE_SMALLEST_CLUSTER_SIZE"!][!//
[!VAR "FEE_SMALLEST_CLUSTER_SIZE" = "$FEE_CLUSTER_SIZE"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!VAR "FEE_AVAIL_CLUSTER_SIZE" = "$FEE_SMALLEST_CLUSTER_SIZE - $FEE_CLUSTER_OVERHEAD - [!//
                                                               $FEE_BLOCK_OVERHEAD"!][!//
[!LOOP "../../FeeBlockConfiguration/*[node:name(node:ref(FeeClusterGroupRef)) = [!//
                                                        node:current()/@name]"!][!//
[!VAR "FEE_AVAIL_CLUSTER_SIZE" = "$FEE_AVAIL_CLUSTER_SIZE - [!//
    num:i(ceiling(./FeeBlockSize div $FEE_VIRTUAL_PAGE_SIZE) * $FEE_VIRTUAL_PAGE_SIZE) - [!//
                                                               $FEE_BLOCK_OVERHEAD"!][!//
[!IF "$FEE_AVAIL_CLUSTER_SIZE < 0"!][!//
[!ERROR!][!//
The block [!"node:name(.)"!] is too big. The block doesn't fit into the cluster group [!//
                                        [!"node:name(node:ref(./FeeClusterGroupRef))"!].
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDLOOP!][!//

/* Configuration of cluster group set */
extern CONST(Fee_ClusterGroupType, FEE_CONST) Fee_ClrGrps[[!"num:i(count(FeeClusterGroup/*))"!]];

/* Configuration of Fee blocks */
extern CONST(Fee_BlockConfigType, FEE_CONST) Fee_BlockConfig[[!"num:i(count(FeeBlockConfiguration/*))"!]];

[!ENDCODE!][!//

#define FEE_STOP_SEC_CONST_UNSPECIFIED
/** @note Violates MISRA-C:2004 Advisory Rule 19.1,only preprocessor statements and comments before 
          '#include'. See @ref Fee_Cfg_c_REF_1 */
/** @note Violates MISRA-C:2004 Required Rule 19.15, Repeatedly included but does not have a standard 
          include guard. See @ref Fee_Cfg_c_REF_2 */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* _FEE_CFG_H_ */
