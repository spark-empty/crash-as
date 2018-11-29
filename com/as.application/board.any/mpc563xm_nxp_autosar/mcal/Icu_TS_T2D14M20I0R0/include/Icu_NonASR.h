/**
    @file    Icu_NonASR.h
    @version 2.0.0

    @brief   AUTOSAR Icu - ICU driver non Autosar header file.
    @details ICU driver header file, containing non Autosar API specification and other variables
             and functions that are exported by the ICU driver.

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

#ifndef ICU_NONASR_H
#define ICU_NONASR_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
@file    Icu_NonASR.h
*/

/**
@page misra_violations MISRA-C:2004 violations

@section Icu_NonASR_h_1
Violates MISRA-C:2004 Advisory Rule 19.15 Precautions shall be taken in order to prevent the
contents of a header file being included twice
This is not a violation since all header files are protected against multiple inclusions
*/


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/**
 @file Icu_NonASR.h
*/
/**
@file  Icu_NonASR.h
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref Icu_NonASR_h_1 */
/*lint -save -e537*/
#include "Std_Types.h"
#include "Icu.h"
/*lint -restore*/


/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@{
@brief   Header file version information
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define ICU_NONASR_VENDOR_ID_H           43

#define ICU_NONASR_AR_MAJOR_VERSION_H    3
#define ICU_NONASR_AR_MINOR_VERSION_H    0
#define ICU_NONASR_AR_PATCH_VERSION_H    0
#define ICU_NONASR_SW_MAJOR_VERSION_H    2
#define ICU_NONASR_SW_MINOR_VERSION_H    0
#define ICU_NONASR_SW_PATCH_VERSION_H    0
/**@}*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if Icu_NonASR.h and Std_Types.h are of the same Autosar version */
    #if ((ICU_NONASR_AR_MAJOR_VERSION_H != STD_TYPES_AR_MAJOR_VERSION) || \
         (ICU_NONASR_AR_MINOR_VERSION_H != STD_TYPES_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Icu_NonASR.h and Std_Types.h are different"
    #endif
#endif

/* Check if Icu_NonASR.h and Icu.h are of the same vendor */
#if (ICU_NONASR_VENDOR_ID_H != ICU_VENDOR_ID)
#error "Vendor IDs of Icu_NonASR.h and Icu.h are different"
#endif

/* Check if Icu_NonASR.h and Icu.h are of the same Software version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((ICU_NONASR_AR_MAJOR_VERSION_H != ICU_AR_MAJOR_VERSION) || \
         (ICU_NONASR_AR_MINOR_VERSION_H != ICU_AR_MINOR_VERSION) || \
         (ICU_NONASR_AR_PATCH_VERSION_H != ICU_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Icu_NonASR.h and Icu.h are different"
    #endif
#endif

/* Check if Icu_NonASR.h and Icu.h are of the same Software version */
#if ((ICU_NONASR_SW_MAJOR_VERSION_H != ICU_SW_MAJOR_VERSION) || \
     (ICU_NONASR_SW_MINOR_VERSION_H != ICU_SW_MINOR_VERSION) || \
     (ICU_NONASR_SW_PATCH_VERSION_H != ICU_SW_PATCH_VERSION))
#error "Software Version Numbers of Icu_NonASR.h and Icu.h are different"
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
#if (ICU_DUAL_CLOCK_MODE == STD_ON)
/**
@brief   API Icu_SetClockMode service called with wrong parameter
@remarks Covers PR-MCAL-3195
*/
#define ICU_E_PARAM_CLOCK_MODE          0x7AU

/**
@brief   API service ID for Icu_SetClockMode function
@details Parameters used when raising an error/exception
@remarks Covers PR-MCAL-3195
*/
#define ICU_SET_CLOCK_MODE_ID           0x7BU
/* ICU_DUAL_CLOCK_MODE */
#endif 

/*==================================================================================================
                                             ENUMS
==================================================================================================*/
/**
@enum    Icu_SelectPrescalerType
         Enumeration of available prescalers.
@remarks Covers PR-MCAL-3195
@remarks Implements DICU50008
*/
#if (ICU_DUAL_CLOCK_MODE == STD_ON)
typedef enum
{
    /** Default channel prescaler option */
    ICU_NORMAL    = 0x0U,
    /** Alternative prescaler to be used depending on user application ( e.g. low power modes ) */
    ICU_ALTERNATE = 0x1U
} Icu_SelectPrescalerType;
/* ICU_DUAL_CLOCK_MODE */
#endif 

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#define ICU_START_SEC_CODE
/**
@file  Icu_NonASR.h
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref Icu_NonASR_h_1
*/
/*lint -save -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/


#if (ICU_DUAL_CLOCK_MODE == STD_ON)
/*================================================================================================*/
/**
@brief      This function changes the channel prescaler.
@details    This function sets all channels prescalers based on the input mode.
@param[in]  Prescaler - Prescaler type ( Normal or Alternate )
@pre        Icu_Init must be called before.
@remarks    Covers ICU002, ICU111, ICU112, ICU022, ICU048, PR-MCAL-3195
@remarks    Implements DICU10021
*/
/*================================================================================================*/
extern FUNC (void, ICU_CODE) Icu_SetClockMode(VAR(Icu_SelectPrescalerType, AUTOMATIC) Prescaler);
#endif


#define ICU_STOP_SEC_CODE
/**
@file  Icu_NonASR.h
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref Icu_NonASR_h_1
*/
/*lint -save -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/


#ifdef __cplusplus
}
#endif
/* ICU_NONASR_H */
#endif  

