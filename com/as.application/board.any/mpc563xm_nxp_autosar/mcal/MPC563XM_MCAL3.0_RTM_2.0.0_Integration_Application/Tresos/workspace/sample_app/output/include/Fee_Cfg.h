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


/* Pre-processor switch to enable and disable development error detection */
#define FEE_DEV_ERROR_DETECT                STD_ON
                                        
/* Pre-processor switch to enable / disable the API to read out the modules
    version information */
#define FEE_VERSION_INFO_API                STD_ON

/* The size in bytes to which logical blocks shall be aligned */
#define FEE_VIRTUAL_PAGE_SIZE               8U

/* Job end notification routine provided by the upper layer    module (declaration) */
#define FEE_NVM_JOB_END_NOTIFICATION_DECL    extern void Fee_JobEndNotif(void);

/* Job end notification routine provided by the upper layer    module */
#define FEE_NVM_JOB_END_NOTIFICATION        Fee_JobEndNotif();

/* Job error notification routine provided by the upper layer module (declaration) */
#define FEE_NVM_JOB_ERROR_NOTIFICATION_DECL  extern void Fee_JobErrorNotif(void);

/* Job error notification routine provided by the upper layer module */
#define FEE_NVM_JOB_ERROR_NOTIFICATION      Fee_JobErrorNotif();

/* Number of configured Fee cluster groups */
#define FEE_NUMBER_OF_CLUSTER_GROUPS        1U

/* Number of configured Fee blocks */
#define FEE_NUMBER_OF_BLOCKS                1U

/* Management overhead per logical block in bytes */
#define FEE_BLOCK_OVERHEAD                  32U

/* Management overhead per logical cluster in bytes */
#define FEE_CLUSTER_OVERHEAD                32U

/* Size of the data buffer in bytes */
#define FEE_DATA_BUFFER_SIZE                32U

/* The contents of an erased flash memory cell */
#define FEE_ERASED_VALUE                    0xffU

/* Value of the block and cluster validation flag */
#define FEE_VALIDATED_VALUE                0x81U

/* Value of the block and cluster invalidation flag */
#define FEE_INVALIDATED_VALUE              0x18U

/* If reset, power loss etc. occurs here, neither newly nor previously written data is available */
#define FEE_BLOCK_ALWAYS_AVAILABLE          STD_OFF

/* Compile switch to enable /disable the Fls_Cancel function */
#define FEE_CANCEL_API                (STD_ON)

/* Compile switch to enable /disable the Fls_SetMode function */
#define FEE_SET_MODE_API              (STD_ON)


/* Symbolic names of configured Fee blocks */
#define FeeBlockConfiguration_0        1U

#define FEE_START_SEC_CONST_UNSPECIFIED
/** @note Violates MISRA-C:2004 Advisory Rule 19.1,only preprocessor statements and comments before 
          '#include'. See @ref Fee_Cfg_c_REF_1 */
/** @note Violates MISRA-C:2004 Required Rule 19.15, Repeatedly included but does not have a standard 
          include guard. See @ref Fee_Cfg_c_REF_2 */
#include "MemMap.h"


/* Configuration of cluster group FeeClusterGroup_0 */
extern CONST(Fee_ClusterType, FEE_CONST) Fee_FeeClusterGroup_0[2];

/* Configuration of cluster group set */
extern CONST(Fee_ClusterGroupType, FEE_CONST) Fee_ClrGrps[1];

/* Configuration of Fee blocks */
extern CONST(Fee_BlockConfigType, FEE_CONST) Fee_BlockConfig[1];


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
