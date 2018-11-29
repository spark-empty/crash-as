/**
    @file    Reg_eSys_EMIOS.c
    @version 2.0.0

    @brief   AUTOSAR Icu - EMIOS common low level driver.
    @details EMIOS common low level driver.

    Project AUTOSAR 3.0 MCAL
    Platform PA
    Peripheral eMIOS200
    Dependencies none

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


/**
@page misra_violations MISRA-C:2004 violations

@section Reg_eSYS_EMIOS_c_1
Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before "#include"
MemMap.h included after each section define in order to set the current memory section

@section Reg_eSYS_EMIOS_c_2
MISRA-C:2004  19.15 Precautions shall be taken in order to prevent the contents of a
header file being included twice.
This is not a violation since all header files are protected against multiple inclusions.
*/

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
#include "modules.h"
#include "Reg_eSys.h"
#include "Reg_eSys_EMIOS.h"


/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
/**
@{
@brief   eMIOS Module Id, The define value is 100 for GPT, 121 for PWM and 122 for ICU
*/
#define EMIOS_COMMON_MODULE_ID                122
/**@}*/

/**
@{
@brief   Source file version information
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define REG_ESYS_EMIOS_C_VENDOR_ID            43
#define REG_ESYS_EMIOS_C_AR_MAJOR_VERSION     3
#define REG_ESYS_EMIOS_C_AR_MINOR_VERSION     0
#define REG_ESYS_EMIOS_C_AR_PATCH_VERSION     0
#define REG_ESYS_EMIOS_C_SW_MAJOR_VERSION     2
#define REG_ESYS_EMIOS_C_SW_MINOR_VERSION     0
#define REG_ESYS_EMIOS_C_SW_PATCH_VERSION     0
/**@}*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and header file are of the same Autosar version */
    #if ((REG_ESYS_EMIOS_C_AR_MAJOR_VERSION != MODULES_AR_MAJOR_VERSION_H) || \
         (REG_ESYS_EMIOS_C_AR_MINOR_VERSION != MODULES_AR_MINOR_VERSION_H))
        #error "AutoSar Version Numbers of Reg_eSys_EMIOS.c and modules.h are different"
    #endif
#endif


/* Check if source file and Reg_eSys_EMIOS.h are of the same vendor */
#if (REG_ESYS_EMIOS_C_VENDOR_ID != REG_ESYS_EMIOS_H_VENDOR_ID)
    #error "Reg_eSys_EMIOS.c and Reg_eSys_EMIOS.h have different vendor ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and header file are of the same Autosar version */
    #if ((REG_ESYS_EMIOS_C_AR_MAJOR_VERSION != REG_ESYS_EMIOS_H_AR_MAJOR_VERSION) || \
         (REG_ESYS_EMIOS_C_AR_MINOR_VERSION != REG_ESYS_EMIOS_H_AR_MINOR_VERSION) || \
         (REG_ESYS_EMIOS_C_AR_PATCH_VERSION != REG_ESYS_EMIOS_H_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of Reg_eSys_EMIOS.c and Reg_eSys_EMIOS.h are different"
    #endif
#endif

/* Check if source file and header file are of the same Software version */
#if ((REG_ESYS_EMIOS_C_SW_MAJOR_VERSION != REG_ESYS_EMIOS_H_SW_MAJOR_VERSION)  || \
     (REG_ESYS_EMIOS_C_SW_MINOR_VERSION != REG_ESYS_EMIOS_H_SW_MINOR_VERSION)  || \
     (REG_ESYS_EMIOS_C_SW_PATCH_VERSION != REG_ESYS_EMIOS_H_SW_PATCH_VERSION))
    #error "Software Version Numbers of Reg_eSys_EMIOS.c and Reg_eSys_EMIOS.h are different"
#endif



/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/

/*lint -save -e961 -e537 -e451 */
#if ((USE_GPT_MODULE==STD_ON) && (EMIOS_COMMON_MODULE_ID==100))
#define EMIOS_VAR GPT_VAR
 /**
 @file  Reg_eSys_EMIOS.c
 @note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before 
        "#include" See @ref Reg_eSYS_EMIOS_c_1 */
#define GPT_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
#endif

#if ((USE_GPT_MODULE==STD_OFF) && (USE_PWM_MODULE==STD_ON) && (EMIOS_COMMON_MODULE_ID==121))
#define EMIOS_VAR PWM_VAR
 /**
 @file  Reg_eSys_EMIOS.c
 @note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before 
        "#include" See @ref Reg_eSYS_EMIOS_c_1 */
#define PWM_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
#endif

#if ((USE_GPT_MODULE==STD_OFF) && (USE_PWM_MODULE==STD_OFF) && (USE_ICU_MODULE==STD_ON) && \
     (EMIOS_COMMON_MODULE_ID==122))
#define EMIOS_VAR ICU_VAR
 /**
 @file  Reg_eSys_EMIOS.c
 @note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before 
        "#include" See @ref Reg_eSYS_EMIOS_c_1 */
#define ICU_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
#endif

#if ((USE_GPT_MODULE==STD_OFF) && (USE_PWM_MODULE==STD_OFF) && (USE_ICU_MODULE==STD_OFF) && \
     (USE_MCU_MODULE==STD_ON) && (EMIOS_COMMON_MODULE_ID==101))
#define EMIOS_VAR MCU_VAR
 /**
 @file  Reg_eSys_EMIOS.c
 @note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before 
        "#include" See @ref Reg_eSYS_EMIOS_c_1 */
#define MCU_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
#endif
/*lint -restore */


#if ( ((USE_GPT_MODULE==STD_ON)  && (EMIOS_COMMON_MODULE_ID==100)) || \
      ((USE_GPT_MODULE==STD_OFF) && (USE_PWM_MODULE==STD_ON)  && (EMIOS_COMMON_MODULE_ID==121)) || \
      ((USE_GPT_MODULE==STD_OFF) && (USE_PWM_MODULE==STD_OFF) && (USE_ICU_MODULE==STD_ON)  && \
       (EMIOS_COMMON_MODULE_ID==122)) || \
      ((USE_GPT_MODULE==STD_OFF) && (USE_PWM_MODULE==STD_OFF) && (USE_ICU_MODULE==STD_OFF) && \
       (USE_MCU_MODULE==STD_ON) && (EMIOS_COMMON_MODULE_ID==101)) )


/**
@brief EMIOS base address array
*/
CONST(uint32, EMIOS_VAR) EMIOS_BASE_ADDR[] = {

/**
@briefcheck if second emios is available on the platform
 */
#ifdef  EMIOSB_BASEADDR

        EMIOSA_BASEADDR,
        EMIOSB_BASEADDR
#else
/**
@brief the platform includes only one emios module
 */
        EMIOS_BASEADDR
#endif

};

/* module check */
#endif 



/*lint -save -e961 -e537 -e451 */
#if ((USE_GPT_MODULE==STD_ON) && (EMIOS_COMMON_MODULE_ID==100))

#define GPT_STOP_SEC_VAR_UNSPECIFIED
 /**
 @file  Reg_eSys_EMIOS.c
 @note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
        "#include" See @ref Reg_eSYS_EMIOS_c_1 */
/*@note Violates MISRA 2004 Advisory Rule 19.15, Repeated include file,
See @ref Reg_eSYS_EMIOS_c_2*/
#include "MemMap.h"
#endif

#if ((USE_GPT_MODULE==STD_OFF) && (USE_PWM_MODULE==STD_ON) && (EMIOS_COMMON_MODULE_ID==121))
#define PWM_STOP_SEC_VAR_UNSPECIFIED
 /**
 @file  Reg_eSys_EMIOS.c
 @note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before 
        "#include" See @ref Reg_eSYS_EMIOS_c_1 */
/*@note Violates MISRA 2004 Advisory Rule 19.15, Repeated include file,
See @ref Reg_eSYS_EMIOS_c_2*/
#include "MemMap.h"
#endif

#if ((USE_GPT_MODULE==STD_OFF) && (USE_PWM_MODULE==STD_OFF) && (USE_ICU_MODULE==STD_ON) && \
     (EMIOS_COMMON_MODULE_ID==122))

#define ICU_STOP_SEC_VAR_UNSPECIFIED
/**
@file  Reg_eSys_EMIOS.c
@note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before 
       "#include" See @ref Reg_eSYS_EMIOS_c_1
@note Violates MISRA 2004 Required Rule 19.15,Precaution shall be taken in order to prevent the
contents of a header file being included twice. - See @ref Reg_eSYS_EMIOS_c_2*/
#include "MemMap.h"
#endif

#if ((USE_GPT_MODULE==STD_OFF) && (USE_PWM_MODULE==STD_OFF) && (USE_ICU_MODULE==STD_OFF) && \
     (USE_MCU_MODULE==STD_ON) && (EMIOS_COMMON_MODULE_ID==101))

#define MCU_STOP_SEC_VAR_UNSPECIFIED
/**
@file Reg_eSys_EMIOS.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before 
      "#include" See @ref Reg_eSYS_EMIOS_c_1 */
/*@note Violates MISRA 2004 Advisory Rule 19.15, Repeated include file,
See @ref Reg_eSYS_EMIOS_c_2*/
#include "MemMap.h"
#endif
/*lint -restore */





/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/


#ifdef __cplusplus
}
#endif
