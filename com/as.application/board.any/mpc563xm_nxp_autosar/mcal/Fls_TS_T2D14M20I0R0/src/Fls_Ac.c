/**
    @file    Fls_Ac.c
    @version 2.0.6.0

    @brief   AUTOSAR Fls - AUTOSAR Module Flash Driver
    @details Position independent erase and write access code

    Project AUTOSAR 3.0 MCAL
    Platform PA
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
/*==================================================================================================*/
/**
@page misra_violations MISRA-C:2004 violations

@section Fls_c_REF_1
Violates MISRA-C: 2004 Advisory Rule 19.1, only preprocessor statements and comments
before '#include'
Violates MISRA-C: 2004 Advisory Rule 19.15, Repeatedly included but does not have a standard include
guard due to AUTOSAR requirement MEMMAP003

 */
/*==================================================================================================*/


#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Fls.h"


/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
/** @remarks Covers BSW00374, BSW00318 */
#define FLS_AC_VENDOR_ID_C         43U
#define FLS_AC_AR_MAJOR_VERSION_C  3U
#define FLS_AC_AR_MINOR_VERSION_C  0U
#define FLS_AC_AR_PATCH_VERSION_C  0U
#define FLS_AC_SW_MAJOR_VERSION_C  2U
#define FLS_AC_SW_MINOR_VERSION_C  0U
#define FLS_AC_SW_PATCH_VERSION_C  0U

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and Fls header file are of the same vendor */
#if (FLS_AC_VENDOR_ID_C != FLS_VENDOR_ID)
    #error "Fls_Ac.c and Fls.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Fls header file are of the same Autosar version */
    #if ((FLS_AC_AR_MAJOR_VERSION_C != FLS_AR_MAJOR_VERSION) || \
         (FLS_AC_AR_MINOR_VERSION_C != FLS_AR_MINOR_VERSION) || \
         (FLS_AC_AR_PATCH_VERSION_C != FLS_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of Fls_Ac.c and Fls.h are different"
    #endif
#endif
/* Check if source file and Fls header file are of the same Software version */
#if ((FLS_AC_SW_MAJOR_VERSION_C != FLS_SW_MAJOR_VERSION) || \
     (FLS_AC_SW_MINOR_VERSION_C != FLS_SW_MINOR_VERSION) || \
     (FLS_AC_SW_PATCH_VERSION_C != FLS_SW_PATCH_VERSION))
    #error "Software Version Numbers of Fls_Ac.c and Fls.h are different"
#endif
/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/

#define FLS_START_SEC_CONST_UNSPECIFIED
/** @note Violates MISRA-C:2004 Advisory Rule 19.15: See @ref Fls_Ac_c_REF_1 */
#include "MemMap.h"
/* void Fls_AcErase(volatile uint32* regBasePtr, \            */
/*                         void (*CallBack)(), \              */
/*                         volatile uint32* timerCounterAC)   */
/* {                                                          */
/*     regBasePtr[FLASHMEM_MCR] |= MCR_EHV;                   */
/*                                                            */
/*     while((!(regBasePtr[FLASHMEM_MCR] & MCR_DONE)) &&      */
/*             ((*timerCounterAC)++ < 0x7FFFFFFFU))           */
/*     {                                                      */
/*         if (NULL_PTR != CallBack)                          */
/*           CallBack();                                      */
/*     }                                                      */
/* }                                                          */
/* Position independent erase access code */
CONST(uint32, FLS_CONST) Fls_AcErase[21] =
{
    0x182106E0, 0x0080D901, 0xD7F1D6E1, 0xD5D1013F,
    0x014D015E, 0xC00F65F0, 0xD00FE808, 0x48000DD0,
    0xE60502D4, 0x7D8903A6, 0x0007C00F, 0x7400056B,
    0x2A00E209, 0xC04E1C04, 0x0001D00E, 0x62032403,
    0x0D34E4ED, 0xC7F1C6E1, 0xC5D1C901, 0x009021F1,
    0x00044400
};

/* void Fls_AcWrite(volatile uint32* regBasePtr, \            */
/*                         void (*CallBack)(), \              */
/*                         volatile uint32* timerCounterAC)   */
/* {                                                          */
/*     regBasePtr[FLASHMEM_MCR] |= MCR_EHV;                   */
/*                                                            */
/*     while((!(regBasePtr[FLASHMEM_MCR] & MCR_DONE)) &&      */
/*             ((*timerCounterAC)++ < 0x7FFFFFFFU))           */
/*     {                                                      */
/*         if (NULL_PTR != CallBack)                          */
/*           CallBack();                                      */
/*     }                                                      */
/* }                                                          */
/* Position independent write access code */
CONST(uint32, FLS_CONST) Fls_AcWrite[21] =
{
    0x182106E0, 0x0080D901, 0xD7F1D6E1, 0xD5D1013F,
    0x014D015E, 0xC00F65F0, 0xD00FE808, 0x48000DD0,
    0xE60502D4, 0x7D8903A6, 0x0007C00F, 0x7400056B,
    0x2A00E209, 0xC04E1C04, 0x0001D00E, 0x62032403,
    0x0D34E4ED, 0xC7F1C6E1, 0xC5D1C901, 0x009021F1,
    0x00044400
};

#define FLS_STOP_SEC_CONST_UNSPECIFIED
/** @note Violates MISRA-C:2004 Advisory Rule 19.1, 19.15: See @ref Fls_Ac_c_REF_1 */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif
