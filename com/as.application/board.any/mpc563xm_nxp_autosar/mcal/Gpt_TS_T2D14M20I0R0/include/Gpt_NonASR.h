/**
    @file    Gpt_NonASR.h
    @version 2.0.0

    @brief   AUTOSAR Gpt - GPT driver non Autosar header file.
    @details GPT driver header file, containing non Autosar API specification and other variables
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

#ifndef GPT_NONASR_H
#define GPT_NONASR_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
@page misra_violations MISRA-C:2004 violations

@section GPT_NonASR_H_REF_1
Violates MISRA 2004 Advisory Rule 19.1: only preprocessor statements and comments before "#include"
This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement
MEMMAP003.

@section GPT_NonASR_H_REF_2
Violates MISRA 2004 Advisory Rule 19.15 : Repeated include file
This violation is not fixed since all header files are protected against multiple inclusions.

*/


/*=================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
=================================================================================================*/
/**
 @file Gpt_NonASR.h
*/
/**
@file  Gpt_NonASR.h
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref GPT_NonASR_H_2 */
/*lint -save -e537*/
#include "Std_Types.h"
#include "Gpt.h"
/*lint -restore*/


/*=================================================================================================
                               SOURCE FILE VERSION INFORMATION
=================================================================================================*/
/**
@{
@brief   Header file version information
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define GPT_VENDOR_ID_NONASR_H           43
#define GPT_MODULE_ID_NONASR_H           100

#define GPT_AR_MAJOR_VERSION_NONASR_H    3
#define GPT_AR_MINOR_VERSION_NONASR_H    0
#define GPT_AR_PATCH_VERSION_NONASR_H    0
#define GPT_SW_MAJOR_VERSION_NONASR_H    2
#define GPT_SW_MINOR_VERSION_NONASR_H    0
#define GPT_SW_PATCH_VERSION_NONASR_H    0
/**@}*/

/*=================================================================================================
                                      FILE VERSION CHECKS
=================================================================================================*/
/* Check if header file and Std_Types.h file are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((GPT_AR_MAJOR_VERSION_NONASR_H != STD_TYPES_AR_MAJOR_VERSION) || \
         (GPT_AR_MINOR_VERSION_NONASR_H != STD_TYPES_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Gpt_NonASR.h and Std_Types.h are different"
    #endif
#endif

/* Check if source file and GPT configuration header file are of the same vendor */
#if (GPT_VENDOR_ID_NONASR_H != GPT_VENDOR_ID_CFG)
    #error "Gpt_NonASR.h and GPT_Cfg.h have different vendor IDs"
#endif
/* Check if header file and GPT configuration header file are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((GPT_AR_MAJOR_VERSION_NONASR_H != GPT_AR_MAJOR_VERSION_CFG) || \
         (GPT_AR_MINOR_VERSION_NONASR_H != GPT_AR_MINOR_VERSION_CFG) || \
         (GPT_AR_PATCH_VERSION_NONASR_H != GPT_AR_PATCH_VERSION_CFG))
    #error "AutoSar Version Numbers of Gpt_NonASR.h and Gpt_Cfg.h are different"
    #endif
#endif
/* Check if header file and GPT configuration header file are of the same software version */
#if ((GPT_SW_MAJOR_VERSION_NONASR_H != GPT_SW_MAJOR_VERSION_CFG) || \
     (GPT_SW_MINOR_VERSION_NONASR_H != GPT_SW_MINOR_VERSION_CFG) || \
     (GPT_SW_PATCH_VERSION_NONASR_H != GPT_SW_PATCH_VERSION_CFG))
#error "Software Version Numbers of GptNonASR.h and Gpt_Cfg.h are different"
#endif


/*=================================================================================================
                                           CONSTANTS
=================================================================================================*/


/*=================================================================================================
                                       DEFINES AND MACROS
=================================================================================================*/
/**
@brief   API Gpt_SetClockMode service called with wrong parameter
@remarks Covers GPT004
@remarks Covers PR-MCAL-3196
*/
#define GPT_E_PARAM_CLOCK_MODE          0x7AU

/**
@brief   API service ID for Gpt_SetClockMode function
@details Parameters used when raising an error/exception
*/
#define GPT_SET_CLOCK_MODE_ID           0x7BU

/**
@brief Prescaler type
@remarks Covers PR-MCAL-3196
*/

/*lint -save -e961 */
#if (GPT_DUAL_CLOCK_MODE == STD_ON)
/*lint -restore */

typedef enum
{
    GPT_NORMAL    = 0x0U,
    GPT_ALTERNATE = 0x1U
}Gpt_ClockModeType;
#endif /* GPT_DUAL_CLOCK_MODE */

/*=================================================================================================
                                             ENUMS
=================================================================================================*/


/*=================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
=================================================================================================*/


/*=================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
=================================================================================================*/


/*=================================================================================================
                                     FUNCTION PROTOTYPES
=================================================================================================*/

#define GPT_START_SEC_CODE
/**
@file  Gpt_NonASR.h
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before
       "#include" - See @ref GPT_NonASR_H_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h -
       See @ref GPT_NonASR_H_REF_2
*/
/*lint -save -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

#if (GPT_DUAL_CLOCK_MODE == STD_ON)
/*===============================================================================================*/
/**
@brief      This function changes the channel prescaler.
@details    This function sets all channels prescalers based on the input mode.
@param[in]     clkMode        Prescaler type ( Normal or Alternate )
@pre Gpt_Init must be called before.
@remarks Covers PR-MCAL-3195
@remarks Covers GPT002, GPT111, GPT112, GPT022, GPT048
@remarks Implements DGPT06501
*/
/*===============================================================================================*/
extern FUNC (void, GPT_CODE) Gpt_SetClockMode(VAR(Gpt_ClockModeType, AUTOMATIC) clkMode);
#endif


#define GPT_STOP_SEC_CODE
/**
@file  Gpt_NonASR.h
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before
       "#include" - See @ref GPT_NonASR_H_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h -
       See @ref GPT_NonASR_H_REF_2
*/
/*lint -save -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/


#ifdef __cplusplus
}
#endif

#endif  /* GPT_NONASR_H */

