/**
    @file    Icu_NonASR.c
    @version 2.0.0

    @brief   AUTOSAR Icu - ICU Driver non AUTOSAR source file.
    @details ICU driver source file, containing the non Autosar API specification and other 
             variables
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

/**
@file    Icu_NonASR.c
*/

/**
@page misra_violations MISRA-C:2004 violations

@section Icu_NonASR_c_1
Violates MISRA-C 2004  Advisory  Rule   19.1,  only preprocessor
statements and comments before "#include"
This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement
MEMMAP003.

@section Icu_NonASR_c_2
Violates MISRA-C:2004  19.15 Precautions shall be taken in order to prevent the contents of a
header file being included twice
This is not a violation since all header files are protected against multiple inclusions
*/


#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Icu_NonASR.h"
#include "Icu_LLD.h"

#if (ICU_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif


/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/**
@{
@brief   Source file version information
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define ICU_NONASR_VENDOR_ID_C         43

#define ICU_NONASR_AR_MAJOR_VERSION_C  3
#define ICU_NONASR_AR_MINOR_VERSION_C  0
#define ICU_NONASR_AR_PATCH_VERSION_C  0
#define ICU_NONASR_SW_MAJOR_VERSION_C  2
#define ICU_NONASR_SW_MINOR_VERSION_C  0
#define ICU_NONASR_SW_PATCH_VERSION_C  0
/**@}*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if Icu_NonASR.c and Icu_NonASR.h are of the same vendor */
#if (ICU_NONASR_VENDOR_ID_C != ICU_NONASR_VENDOR_ID_H)
    #error "Vendor IDs of Icu_NonASR.c and Icu_NonASR.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if Icu_NonASR.c and Icu_NonASR.h are of the same Autosar version */
    #if ((ICU_NONASR_AR_MAJOR_VERSION_C != ICU_NONASR_AR_MAJOR_VERSION_H) || \
         (ICU_NONASR_AR_MINOR_VERSION_C != ICU_NONASR_AR_MINOR_VERSION_H) || \
         (ICU_NONASR_AR_PATCH_VERSION_C != ICU_NONASR_AR_PATCH_VERSION_H))
        #error "AutoSar Version Numbers of Icu_NonASR.c and Icu_NonASR.h are different"
    #endif
#endif

/* Check if Icu_NonASR.c and Icu_NonASR.h are of the same Software version */
#if ((ICU_NONASR_SW_MAJOR_VERSION_C != ICU_NONASR_SW_MAJOR_VERSION_H) || \
     (ICU_NONASR_SW_MINOR_VERSION_C != ICU_NONASR_SW_MINOR_VERSION_H) || \
     (ICU_NONASR_SW_PATCH_VERSION_C != ICU_NONASR_SW_PATCH_VERSION_H))
    #error "Software Version Numbers of Icu_NonASR.c and Icu_NonASR.h are different"
#endif

/* Check if Icu_NonASR.c and Icu_LLD.h are of the same vendor */
#if (ICU_NONASR_VENDOR_ID_C != ICU_LLD_VENDOR_ID)
    #error "Vendor IDs of Icu_NonASR.c and Icu_LLD.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if Icu_NonASR.c and Icu_LLD.h are of the same Autosar version */
    #if ((ICU_NONASR_AR_MAJOR_VERSION_C != ICU_LLD_AR_MAJOR_VERSION) || \
         (ICU_NONASR_AR_MINOR_VERSION_C != ICU_LLD_AR_MINOR_VERSION) || \
         (ICU_NONASR_AR_PATCH_VERSION_C != ICU_LLD_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of Icu_NonASR.c and Icu_LLD.h are different"
    #endif
#endif

/* Check if Icu_NonASR.c and Icu_LLD.h are of the same Software version */
#if ((ICU_NONASR_SW_MAJOR_VERSION_C != ICU_LLD_SW_MAJOR_VERSION) || \
     (ICU_NONASR_SW_MINOR_VERSION_C != ICU_LLD_SW_MINOR_VERSION) || \
     (ICU_NONASR_SW_PATCH_VERSION_C != ICU_LLD_SW_PATCH_VERSION))
    #error "Software Version Numbers of Icu_NonASR.c and Icu_LLD.h are different"
#endif

/* Check if Icu_NonASR.c and Det.h are of the same version */
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    #ifdef CHECK_AUTOSAR_VERSION
        #if ((ICU_NONASR_AR_MAJOR_VERSION_C != DET_AR_MAJOR_VERSION) || \
             (ICU_NONASR_AR_MINOR_VERSION_C != DET_AR_MINOR_VERSION))
        #error "AutoSar Version Numbers of Icu_NonASR.c and Det.h are different"
        #endif
    #endif
/* ICU_DEV_ERROR_DETECT */
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


/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define ICU_START_SEC_CODE
/**
@file  Icu_NonASR.c
@note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
       "#include". See @ref Icu_NonASR_c_1
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref Icu_NonASR_c_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/


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
FUNC (void, ICU_CODE) Icu_SetClockMode(VAR(Icu_SelectPrescalerType, AUTOMATIC) Prescaler)
{
    VAR(Icu_ChannelType, AUTOMATIC) numChl;
    P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_APPL_CONST) tempPtr;

    /* [ICU002]: Detected development errors shall be reported to the Det_ReportError service of the
    Development Error Tracer (DET) if the pre-processor switch ICU_DEV_ERROR_DETECT is set
    */
    /* [ICU111]: The detection of development errors is configurable (ON / OFF) at precompile  time.
    The switch ICU_DEV_ERROR_DETECT  shall activate or  deactivate the detection  of all development
    errors.
    */
    /* [ICU112]: If the switch ICU_DEV_ERROR_DETECT is enabled, API parameter checking is enabled.*/
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* If Development  Error Detection is  enabled, report error  Icu is uninitialized  is passed as
    a NULL Pointer
     */
    if (NULL_PTR == Icu_Cfg_Ptr)
    {
        /* [ICU022]  - The  service Icu_Init()  shall be  called first  before calling any other ICU
        services. If not respected, the error code ICU_E_UNINIT will be reported to the  Development
        Error Tracer (if development error detection is enabled).
        */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, 
                        (uint8)ICU_SET_CLOCK_MODE_ID, (uint8)ICU_E_UNINIT);

        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    else if ((ICU_NORMAL != Prescaler) && (ICU_ALTERNATE != Prescaler))
    {
        /* [ICU125] - If development error detection is enabled, the parameter Mode shall be checked
        by this service.  If Mode is invalid,  then the error ICU_E_PARAM_MODE shall be reported  to
        the Development Error Tracer.
         */
        Det_ReportError((uint16)ICU_MODULE_ID, (uint8)0U, 
                        (uint8)ICU_SET_CLOCK_MODE_ID, (uint8)ICU_E_PARAM_CLOCK_MODE);
        /* [ICU048] - If development error detection is enabled and an error is detected the desired
        functionality shall be skipped and the requested service is left without any action.
        */
    }
    else
/* ICU_DEV_ERROR_DETECT */
#endif 
    {
        for (numChl = 0U; numChl < Icu_Cfg_Ptr->Icu_MaxChannels; numChl++)
        {
            tempPtr = &Icu_Cfg_Ptr->Icu_ChannelConfigPtr[numChl];

            /* Call low level function */
            Icu_LLD_SelectPrescaler(tempPtr, numChl, Prescaler);
        }
    }
}
/* ICU_DUAL_CLOCK_MODE */
#endif

/*================================================================================================*/
#define ICU_STOP_SEC_CODE
/**
@file  Icu_NonASR.c
@note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
       "#include". See @ref Icu_NonASR_c_1
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref Icu_NonASR_c_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif

/* End of file */
