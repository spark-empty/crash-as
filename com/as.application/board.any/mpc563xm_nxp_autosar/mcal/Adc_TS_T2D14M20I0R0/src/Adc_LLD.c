/*!
 * @addtogroup ADC
 * @{
 */
/**
    @file    Adc_LLD.c
    @version 2.0.0

    @brief   AUTOSAR Adc - Separation layer of high-low level drivers.
    @details Detailed description.

    Project AUTOSAR 3.0 MCAL
    Patform PA
    Peripheral ADC_10B
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
 * @page    misra_violations MISRA-C:2004 violations
 *
 * @section Adc_LLD_c_REF_1
 *          Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
 *          '#include'. The usage of the MemMap.h file violates this rule, but this mechanism is
 *          used to properly place into their sections the code and variables.
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
#include "Adc.h"
#include "Adc_LLD.h"

#include "Dem.h"
#if (ADC_DEV_ERROR_DETECT == STD_ON)
    #include "Det.h"
#endif

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/**
@{
@brief   Source file version information
@remarks Covers BSW00374, BSW00318
*/
#define ADC_VENDOR_ID_LLD_C         43
#define ADC_AR_MAJOR_VERSION_LLD_C  3
#define ADC_AR_MINOR_VERSION_LLD_C  0
#define ADC_AR_PATCH_VERSION_LLD_C  0
#define ADC_SW_MAJOR_VERSION_LLD_C  2
#define ADC_SW_MINOR_VERSION_LLD_C  0
#define ADC_SW_PATCH_VERSION_LLD_C  0
/**@}*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and ADC header file are of the same vendor */
#if (ADC_VENDOR_ID_LLD_C != ADC_VENDOR_ID)
    #error "Adc_LLD.c and ADC.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and ADC header file are of the same Autosar version */
    #if ((ADC_AR_MAJOR_VERSION_LLD_C != ADC_AR_MAJOR_VERSION) || \
         (ADC_AR_MINOR_VERSION_LLD_C != ADC_AR_MINOR_VERSION) || \
         (ADC_AR_PATCH_VERSION_LLD_C != ADC_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of Adc_LLD.c and ADC.h are different"
    #endif
#endif
/* Check if source file and ADC header file are of the same Software version */
#if ((ADC_SW_MAJOR_VERSION_LLD_C != ADC_SW_MAJOR_VERSION) || \
     (ADC_SW_MINOR_VERSION_LLD_C != ADC_SW_MINOR_VERSION) || \
     (ADC_SW_PATCH_VERSION_LLD_C != ADC_SW_PATCH_VERSION))
    #error "Software Version Numbers of Adc_LLD.c and ADC.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Dem header file are of the same version */
    #if ((ADC_AR_MAJOR_VERSION_LLD_C != DEM_AR_MAJOR_VERSION) || \
         (ADC_AR_MINOR_VERSION_LLD_C != DEM_AR_MINOR_VERSION))
        #error "AutoSar Version Numbers of Adc_LLD.c and Dem.h are different"
    #endif
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and DET header file are of the same version */
    #if (ADC_DEV_ERROR_DETECT == STD_ON)
        #if ((ADC_AR_MAJOR_VERSION_LLD_C != DET_AR_MAJOR_VERSION) || \
             (ADC_AR_MINOR_VERSION_LLD_C != DET_AR_MINOR_VERSION))
            #error "AutoSar Version Numbers of Adc_LLD.c and Det.h are different"
        #endif
    #endif
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
#define ADC_START_SEC_VAR_UNSPECIFIED
/**
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
'#include' - See @ref Adc_LLD_c_REF_1
*/
/*lint -save -e961 -e537 -e451 */
#include "MemMap.h"
/*lint -restore*/


#define ADC_STOP_SEC_VAR_UNSPECIFIED
/**
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
'#include' - See @ref Adc_LLD_c_REF_1
*/
/* lint -save -e961 -e537 -e451 */
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define ADC_START_SEC_CODE
/**
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
'#include' - See @ref Adc_LLD_c_REF_1
*/
/* lint -save -e961 -e537 -e451 */
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/



#define ADC_STOP_SEC_CODE
/**
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
'#include' - See @ref Adc_LLD_c_REF_1
*/
/* lint -save -e961 -e537 -e451 */
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif
/** @} */