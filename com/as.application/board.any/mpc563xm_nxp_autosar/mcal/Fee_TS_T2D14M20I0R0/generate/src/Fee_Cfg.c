[!CODE!][!//
/**
    @file    Fee_Cfg.c
    @version 2.0.8.0

    @brief   AUTOSAR Fee - AUTOSAR Module Flash Driver
    @details Definitions of all post-build configuration structures
    
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
/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/


/** @remarks Covers BSW00374, BSW00318 */
#define FEE_CFG_VENDOR_ID_C         43U
#define FEE_CFG_AR_MAJOR_VERSION_C  3U
#define FEE_CFG_AR_MINOR_VERSION_C  0U
#define FEE_CFG_AR_PATCH_VERSION_C  0U
#define FEE_CFG_SW_MAJOR_VERSION_C  2U
#define FEE_CFG_SW_MINOR_VERSION_C  0U
#define FEE_CFG_SW_PATCH_VERSION_C  0U

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and Fee header file are of the same vendor */
#if (FEE_CFG_VENDOR_ID_C != FEE_VENDOR_ID)
    #error "Fee_Cfg.c and Fee.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Fee header file are of the same Autosar version */
    #if ((FEE_CFG_AR_MAJOR_VERSION_C != FEE_AR_MAJOR_VERSION) || \
         (FEE_CFG_AR_MINOR_VERSION_C != FEE_AR_MINOR_VERSION) || \
         (FEE_CFG_AR_PATCH_VERSION_C != FEE_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of Fee_Cfg.c and Fee.h are different"
    #endif
#endif

/* Check if source file and Fee header file are of the same Software version */
#if ((FEE_CFG_SW_MAJOR_VERSION_C != FEE_SW_MAJOR_VERSION) || \
     (FEE_CFG_SW_MINOR_VERSION_C != FEE_SW_MINOR_VERSION) || \
     (FEE_CFG_SW_PATCH_VERSION_C != FEE_SW_PATCH_VERSION))
    #error "Software Version Numbers of Fee_Cfg.c and Fee.h are different"
#endif

#define FEE_START_SEC_CONST_UNSPECIFIED
/** @note Violates MISRA-C:2004 Advisory Rule 19.1,only preprocessor statements and comments before 
          '#include'. See @ref Fee_Cfg_c_REF_1 */
/** @note Violates MISRA-C:2004 Required Rule 19.15, Repeatedly included but does not have a standard 
          include guard. See @ref Fee_Cfg_c_REF_2 */
#include "MemMap.h"

/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/

[!VAR "FEE_VIRTUAL_PAGE_SIZE" = "num:i(FeeGeneral/FeeVirtualPageSize)"!][!//
[!VAR "FEE_BLOCK_OVERHEAD" = "num:i(ceiling(12 div $FEE_VIRTUAL_PAGE_SIZE + 2) * [!//
                                                    $FEE_VIRTUAL_PAGE_SIZE)"!][!//
[!VAR "FEE_CLUSTER_OVERHEAD" = "num:i(ceiling(16 div $FEE_VIRTUAL_PAGE_SIZE + 2) * [!//
                                                     $FEE_VIRTUAL_PAGE_SIZE)"!][!//

[!LOOP "FeeClusterGroup/*"!][!//

/* Configuration of cluster group [!"node:name(.)"!] */
CONST(Fee_ClusterType, FEE_CONST) Fee_[!"node:name(.)"!][[!"num:i(count(FeeCluster/*))"!]] =
{
[!VAR "FEE_SMALLEST_CLUSTER_SIZE" = "2147483647"!][!//
[!VAR "FEE_LOOP_IT" = "count(FeeCluster/*)"!][!//
[!LOOP "FeeCluster/*"!][!//
[!VAR "FEE_CLUSTER_SIZE" = "0"!][!//
[!LOOP "FeeSector/*"!][!//
[!VAR "FEE_CLUSTER_SIZE" = "$FEE_CLUSTER_SIZE + num:i(node:ref(./FeeSectorRef)/FlsSectorSize) * [!//
                                        num:i(node:ref(./FeeSectorRef)/FlsNumberOfSectors)"!][!//
[!ENDLOOP!][!//
    /* [!"node:name(.)"!] */
    {
        [!"num:i(node:ref(FeeSector/*[1]/FeeSectorRef)/FlsSectorStartaddress)"!]U, /* Start address */
        [!"num:i($FEE_CLUSTER_SIZE)"!]U /* Size */
    }[!VAR "FEE_LOOP_IT" = "$FEE_LOOP_IT - 1"!][!IF "$FEE_LOOP_IT != 0"!],[!ENDIF!]
[!IF "$FEE_CLUSTER_SIZE < $FEE_SMALLEST_CLUSTER_SIZE"!][!//
[!VAR "FEE_SMALLEST_CLUSTER_SIZE" = "$FEE_CLUSTER_SIZE"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
};
[!VAR "FEE_AVAIL_CLUSTER_SIZE" = "$FEE_SMALLEST_CLUSTER_SIZE - $FEE_CLUSTER_OVERHEAD - [!//
                                                              $FEE_BLOCK_OVERHEAD"!][!//
[!LOOP "../../FeeBlockConfiguration/*[node:name(node:ref(FeeClusterGroupRef)) = [!//
                                                        node:current()/@name]"!][!//
[!VAR "FEE_AVAIL_CLUSTER_SIZE" = "$FEE_AVAIL_CLUSTER_SIZE - [!//
 num:i(ceiling(./FeeBlockSize div $FEE_VIRTUAL_PAGE_SIZE) * [!//
 $FEE_VIRTUAL_PAGE_SIZE) - $FEE_BLOCK_OVERHEAD"!][!//
[!IF "$FEE_AVAIL_CLUSTER_SIZE < 0"!][!//
[!ERROR!][!//
The block [!"node:name(.)"!] is too big. The block doesn't fit into the cluster group [!//
                                        [!"node:name(node:ref(./FeeClusterGroupRef))"!].
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDLOOP!][!//

/* Configuration of cluster group set */
CONST(Fee_ClusterGroupType, FEE_CONST) Fee_ClrGrps[[!"num:i(count(FeeClusterGroup/*))"!]] =
{
[!VAR "FEE_LOOP_IT" = "count(FeeClusterGroup/*)"!][!//
[!LOOP "FeeClusterGroup/*"!][!//
    /* [!"node:name(.)"!] */
    {
        Fee_[!"node:name(.)"!], /* Cluster set */
        [!"num:i(count(./FeeCluster/*))"!]U /* Number of clusters */
    }[!VAR "FEE_LOOP_IT" = "$FEE_LOOP_IT - 1"!][!IF "$FEE_LOOP_IT != 0"!],[!ENDIF!]
[!ENDLOOP!][!//
};

/* Configuration of Fee blocks */
CONST(Fee_BlockConfigType, FEE_CONST) Fee_BlockConfig[[!"num:i(count(FeeBlockConfiguration/*))"!]] =
{
[!VAR "FEE_LOOP_IT" = "count(FeeBlockConfiguration/*)"!][!//
[!LOOP "node:order(FeeBlockConfiguration/*,'node:value(./FeeBlockNumber)')"!][!//
    /* [!"node:name(.)"!] */
    {
        [!"node:name(.)"!], /* FeeBlockNumber */
        [!"./FeeBlockSize"!]U, /* FeeBlockSize */
        [!"node:ref(./FeeClusterGroupRef)/@index"!]U, /* FeeClusterGroup */
        (boolean) [!IF "./FeeImmediateData"!]TRUE[!ELSE!]FALSE[!ENDIF!], /* FeeImmediateData */
    }[!VAR "FEE_LOOP_IT" = "$FEE_LOOP_IT - 1"!][!IF "$FEE_LOOP_IT != 0"!],[!ENDIF!]
[!ENDLOOP!][!//
};

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
