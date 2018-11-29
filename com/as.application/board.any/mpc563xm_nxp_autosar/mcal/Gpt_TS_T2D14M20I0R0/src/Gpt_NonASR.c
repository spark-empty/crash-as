/**
    @file    Gpt_NonASR.c
    @version 2.0.0

    @brief   AUTOSAR Gpt - GPT Driver non AUTOSAR source file.
    @details GPT driver source file, containing the non Autosar API specification and other variables
             and functions that are exported by the GPT driver.

    Project AUTOSAR 3.0 MCAL
    Platform PA
    Peripheral eMIOS200_Stm_PitRti
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

@section GPT_NonASR_C_REF_1
Violates MISRA 2004 Advisory Rule 19.1: Violates MISRA 2004 Advisory Rule 19.1, only preprocessor
statements and comments before "#include"
This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement
MEMMAP003.

@section GPT_NonASR_C_REF_2
Violates MISRA 2004 Advisory Rule 19.15 : Repeated include file
This violation is not fixed since all header files are protected against multiple inclusions.

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
#include "Gpt.h"
#include "Gpt_NonASR.h"
#include "Gpt_LLD.h"

#if (GPT_DEV_ERROR_DETECT == STD_ON)
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
#define GPT_VENDOR_ID_NONASR_C         43

#define GPT_AR_MAJOR_VERSION_NONASR_C  3
#define GPT_AR_MINOR_VERSION_NONASR_C  0
#define GPT_AR_PATCH_VERSION_NONASR_C  0
#define GPT_SW_MAJOR_VERSION_NONASR_C  2
#define GPT_SW_MINOR_VERSION_NONASR_C  0
#define GPT_SW_PATCH_VERSION_NONASR_C  0
/**@}*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and GPT header file are of the same vendor */
#if (GPT_VENDOR_ID_NONASR_C != GPT_VENDOR_ID)
    #error "Gpt_NonASR.c and Gpt.h have different vendor IDs"
#endif
/* Check if source file and GPT header file are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((GPT_AR_MAJOR_VERSION_NONASR_C != GPT_AR_MAJOR_VERSION) || \
         (GPT_AR_MINOR_VERSION_NONASR_C != GPT_AR_MINOR_VERSION) || \
         (GPT_AR_PATCH_VERSION_NONASR_C != GPT_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Gpt_NonASR.c and Gpt.h are different"
    #endif
#endif
/* Check if source file and GPT header file are of the same Software version */
#if ((GPT_SW_MAJOR_VERSION_NONASR_C != GPT_SW_MAJOR_VERSION) || \
     (GPT_SW_MINOR_VERSION_NONASR_C != GPT_SW_MINOR_VERSION) || \
     (GPT_SW_PATCH_VERSION_NONASR_C != GPT_SW_PATCH_VERSION))
#error "Software Version Numbers of Gpt_NonASR.c and Gpt.h are different"
#endif

/* Check if source file and DET header file are of the same Autosar version */
#if (GPT_DEV_ERROR_DETECT == STD_ON)
    #ifdef CHECK_AUTOSAR_VERSION
        #if ((GPT_AR_MAJOR_VERSION_NONASR_C != DET_AR_MAJOR_VERSION) || \
             (GPT_AR_MINOR_VERSION_NONASR_C != DET_AR_MINOR_VERSION))
        #error "AutoSar Version Numbers of Gpt_NonASR.c and Det.h are different"
        #endif
    #endif
#endif /* GPT_DEV_ERROR_DETECT */

/* Check if source file and GPT_LLD header file are of the same vendor */
#if (GPT_VENDOR_ID_NONASR_C != GPT_LLD_VENDOR_ID)
    #error "Gpt_NonASR.c and Gpt_LLD.h have different vendor IDs"
#endif
/* Check if source file and Gpt_LLD header file are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((GPT_AR_MAJOR_VERSION_NONASR_C != GPT_LLD_AR_MAJOR_VERSION) || \
         (GPT_AR_MINOR_VERSION_NONASR_C != GPT_LLD_AR_MINOR_VERSION) || \
         (GPT_AR_PATCH_VERSION_NONASR_C != GPT_LLD_AR_PATCH_VERSION))
    #error "Autosar Version Numbers of Gpt_NonASR.c and Gpt_LLD.h are different"
    #endif
#endif
/* Check if source file and Gpt_LLD header file are of the same Software Version */
#if ((GPT_SW_MAJOR_VERSION_NONASR_C != GPT_LLD_SW_MAJOR_VERSION) || \
     (GPT_SW_MINOR_VERSION_NONASR_C != GPT_LLD_SW_MINOR_VERSION) || \
     (GPT_SW_PATCH_VERSION_NONASR_C != GPT_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of Gpt_NonASR.c and Gpt_LLD.h are different"
#endif

/* Check if source file and Gpt_NonASR header are of the same vendor */
#if (GPT_VENDOR_ID_NONASR_C != GPT_VENDOR_ID_NONASR_H)
    #error "Gpt_NonASR.c and Gpt_NonASR.h have different vendor ids"
#endif
/* Check if source file and Gpt_NonASR header are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((GPT_AR_MAJOR_VERSION_NONASR_C != GPT_AR_MAJOR_VERSION_NONASR_H) || \
         (GPT_AR_MINOR_VERSION_NONASR_C != GPT_AR_MINOR_VERSION_NONASR_H) || \
         (GPT_AR_PATCH_VERSION_NONASR_C != GPT_AR_PATCH_VERSION_NONASR_H))
        #error "AutoSar Version Numbers of Gpt_NonASR.c and Gpt_NonASR.h are different"
    #endif
#endif
/* Check if source file and Gpt_NonASR.h are of the same Software version */
#if ((GPT_SW_MAJOR_VERSION_NONASR_C != GPT_SW_MAJOR_VERSION_NONASR_H) || \
     (GPT_SW_MINOR_VERSION_NONASR_C != GPT_SW_MINOR_VERSION_NONASR_H) || \
     (GPT_SW_PATCH_VERSION_NONASR_C != GPT_SW_PATCH_VERSION_NONASR_H))
    #error "Software Version Numbers of Gpt_NonASR.c and Gpt_NonASR.h are different"
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
#define GPT_START_SEC_CODE
/**
@file  Gpt_NonASR.c
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before
       "#include" - See @ref GPT_NonASR_C_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h -
       See @ref GPT_NonASR_C_REF_2
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/



 /*lint -save -e961 */
#if (GPT_DUAL_CLOCK_MODE == STD_ON)
/*lint -restore */



/*================================================================================================*/
/**
@brief     This function changes the channel prescaler.
@details   This function sets all channels prescalers based on the input mode.
@param[in] clkMode   prescaler setting ( NORMAL or ALTERNATE )
@pre     Gpt_Init must be called before.
@remarks Covers PR-MCAL-3196
@remarks Covers GPT002, GPT111, GPT112, GPT022, GPT048
@remarks Implements DGPT06501
*/
/*================================================================================================*/
FUNC (void, GPT_CODE) Gpt_SetClockMode(VAR(Gpt_ClockModeType, AUTOMATIC) clkMode)
{

    /* [GPT178]: Detected development errors shall be reported to the */
    /* Det_ReportError service of the Development Error Tracer (DET) */
    /* if the preprocessor switch GPT_DEV_ERROR_DETECT is set */
    /* [GPT204]: If development error detection is enabled for the GPT Driver, */
    /* the following API parameter checking shall be performed according to the */
    /* respective functions (see table below). The error shall be reported to the Development Error Tracer. */
    /* SetClockMode - GPT_E_UNINIT - Function called prior to initialization */
#if (GPT_DEV_ERROR_DETECT == STD_ON)
    if (NULL_PTR == Gpt_Cfg_Ptr)
    {
        /* [GPT220]- If development error detection is enabled and Gpt_DeInit is called prior */
        /* to initializing the driver, the development error code GPT_E_UNINIT will be raised */
        Det_ReportError((uint16)GPT_MODULE_ID, (uint8)GPT_INSTANCE_ID,
                                               (uint8)GPT_SET_CLOCK_MODE_ID, (uint8)GPT_E_UNINIT);
        /* If development error detection is enabled and an error is detected the desired */
        /* functionality shall be skipped and the requested service is left without any action. */
    }
    else if ((GPT_NORMAL != clkMode) && (GPT_ALTERNATE != clkMode))
    {
        /* [GPT231] - If development error detection is enabled the parameter ClockMode is */
        /* tested. If it is invalid, then the error GPT_E_PARAM_CLOCK_MODE is reported to the */
        /* Development Error Tracer. */
        Det_ReportError((uint16)GPT_MODULE_ID, (uint8)0U, (uint8)GPT_SET_CLOCK_MODE_ID,
                                                          (uint8)GPT_E_PARAM_CLOCK_MODE);
        /* If development error detection is enabled and an error is detected the desired */
        /* functionality shall be skipped and the requested service is left without any action. */
    }
    else
#endif /* GPT_DEV_ERROR_DETECT */
    {
        Gpt_LLD_SelectPrescaler(clkMode);
    }
}
 /* GPT_DUAL_CLOCK_MODE */
#endif

/*================================================================================================*/
#define GPT_STOP_SEC_CODE
/**
@file  Gpt_NonASR.c
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before
       "#include" - See @ref GPT_NonASR_C_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h -
       See @ref GPT_NonASR_C_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif

/* End of file */
