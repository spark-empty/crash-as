/**
    @file    Fls_Cfg.h
    @version 2.0.8.0

    @brief   AUTOSAR Fls - AUTOSAR Module Flash Driver
    @details Definitions of all pre-compile configuration parameters

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

#ifndef _FLS_CFG_H_
#define _FLS_CFG_H_

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Fls_Types.h"

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/* STD_ON: Flash access code loaded on job start / unloaded on job end or error */
#define FLS_AC_LOAD_ON_JOB_START    STD_OFF

/* Compile switch to enable and disable the Fls_Cancel function */
#define FLS_CANCEL_API                STD_ON

/* Compile switch to enable and disable the Fls_Compare function */
#define FLS_COMPARE_API                STD_ON

/* Pre-processor switch to enable and disable development error detection */
#define FLS_DEV_ERROR_DETECT        STD_ON

/* Compile switch to enable and disable the Fls_GetJobResult function */
#define FLS_GET_JOB_RESULT_API        STD_ON

/* Compile switch to enable and disable the Fls_GetStatus function */
#define FLS_GET_STATUS_API            STD_ON

/* Compile switch to enable and disable the Fls_SetMode function */
#define FLS_SET_MODE_API            STD_ON

/* Pre-processor switch to enable / disable the API to read out the modules version information */
#define FLS_VERSION_INFO_API        STD_ON

/* Pre-processor switch to enable / disable the API to report data storage (ECC) errors to the flash driver */
#define FLS_DSI_HANDLER_API            STD_OFF

/* Pre-processor switch to enable / disable the erase blank check */
#define FLS_ERASE_BLANK_CHECK        STD_ON

/* Pre-processor switch to enable / disable the write blank check */
#define FLS_WRITE_BLANK_CHECK        STD_ON

/* Pre-processor switch to enable / disable the write verify check */
#define FLS_WRITE_VERIFY_CHECK        STD_ON

/* The maximum number of bytes to blank check in one cycle of the flash driver's job processing function */
#define FLS_MAX_ERASE_BLANK_CHECK    256U

/* Timeout value for Erase and Write operation (also used fot resumed oparation) */
#define FLS_OPT_TIMEOUT_VALUE        2147483647U

/* Timeout value for Abort operation */
#define FLS_ABT_TIMEOUT_VALUE        32767U

/* Number of bytes in RAM needed for the erase flash access code */
#define FLS_AC_SIZE_ERASE            84U

/* Number of bytes in RAM needed for the write flash access code */
#define FLS_AC_SIZE_WRITE            84U

/* The contents of an erased flash memory cell */
#define FLS_ERASED_VALUE            0xffffffffU

/* Fls Driver Index */
#define FLS_DRIVER_INDEX            0U

/*==================================================================================================
                                 GLOBAL CONSTANT DECLARATIONS
==================================================================================================*/

#define FLS_START_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

/* Declaration of configuration structure (FlsConfigSet_0)*/
extern CONST(Fls_ConfigType, FLS_CONST) FlsConfigSet_0;

#define FLS_STOP_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* _FLS_CFG_H_ */
