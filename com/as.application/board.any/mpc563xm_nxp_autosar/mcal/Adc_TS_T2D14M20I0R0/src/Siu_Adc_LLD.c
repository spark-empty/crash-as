/**
    @file    Siu_Adc_LLD.c
    @version 2.0.0

    @brief   AUTOSAR Adc - SIU source file support for ADC driver.
    @details SIU source file, containing the variables and functions that are exported by the SIU driver.

    Project AUTOSAR 3.0 MCAL
    Platform PA
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
@page misra_violations MISRA-C:2004 violations

@section Siu_Adc_LLD_c_1
Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before "#include".
The usage of the MemMap.h file violates this rule, but this mechanism is used to properly
place into their sections the code and variables.

@section Siu_Adc_LLD_c_2
Violates MISRA 2004 Advisory Rule 19.15, Repeated include file
This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement
MEMMAP003.

@section Siu_Adc_LLD_c_3
Violates MISRA 2004 Rule 11.1: Casting operation to a pointer.
This violation is due to the Casting pointers to other types used in macros
for Reading or writing data from address location of controller register
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

#include "Siu_Adc_LLD.h"
#include "Adc_LLD.h"

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/**
@{
@brief   Source file version information
@remarks Covers BSW00374, BSW00318
*/
#define SIU_ADC_LLD_VENDOR_ID_C         43
#define SIU_ADC_LLD_AR_MAJOR_VERSION_C  3
#define SIU_ADC_LLD_AR_MINOR_VERSION_C  0
#define SIU_ADC_LLD_AR_PATCH_VERSION_C  0
#define SIU_ADC_LLD_SW_MAJOR_VERSION_C  2
#define SIU_ADC_LLD_SW_MINOR_VERSION_C  0
#define SIU_ADC_LLD_SW_PATCH_VERSION_C  0
/**@}*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and SIU_Adc_LLD.h file are of the same vendor */
#if (SIU_ADC_LLD_VENDOR_ID_C != SIU_ADC_LLD_VENDOR_ID)
#error "Siu_Adc_LLD.c and Siu_Adc_LLD.h have different vendor IDs"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((SIU_ADC_LLD_AR_MAJOR_VERSION_C != SIU_ADC_LLD_AR_MAJOR_VERSION) || \
         (SIU_ADC_LLD_AR_MINOR_VERSION_C != SIU_ADC_LLD_AR_MINOR_VERSION) || \
         (SIU_ADC_LLD_AR_PATCH_VERSION_C != SIU_ADC_LLD_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Siu_Adc_LLD.c and Siu_Adc_LLD.h are different"
    #endif
#endif
/* Check if source file and Siu_Adc_LLD.h header file are of the same Software version */
#if ((SIU_ADC_LLD_SW_MAJOR_VERSION_C != SIU_ADC_LLD_SW_MAJOR_VERSION) || \
     (SIU_ADC_LLD_SW_MINOR_VERSION_C != SIU_ADC_LLD_SW_MINOR_VERSION) || \
     (SIU_ADC_LLD_SW_PATCH_VERSION_C != SIU_ADC_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of Siu_Adc_LLD.c and Siu_Adc_LLD.h are different"
#endif

/* Check if source file and Reg_eSys_SIU.h file are of the same vendor */
#if (SIU_ADC_LLD_VENDOR_ID_C != SIU_VENDOR_ID_REG)
#error "Siu_Adc_LLD.c and Siu_Adc_LLD.h have different vendor IDs"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((SIU_ADC_LLD_AR_MAJOR_VERSION_C != SIU_AR_MAJOR_VERSION_REG) || \
         (SIU_ADC_LLD_AR_MINOR_VERSION_C != SIU_AR_MINOR_VERSION_REG) || \
         (SIU_ADC_LLD_AR_PATCH_VERSION_C != SIU_AR_PATCH_VERSION_REG))
    #error "AutoSar Version Numbers of Siu_Adc_LLD.c and Reg_eSys_SIU.h are different"
    #endif
#endif
/* Check if source file and SIU_Adc_LLD.h header file are of the same Software version */
#if ((SIU_ADC_LLD_SW_MAJOR_VERSION_C != SIU_SW_MAJOR_VERSION_REG) || \
     (SIU_ADC_LLD_SW_MINOR_VERSION_C != SIU_SW_MINOR_VERSION_REG) || \
     (SIU_ADC_LLD_SW_PATCH_VERSION_C != SIU_SW_PATCH_VERSION_REG))
#error "Software Version Numbers of Siu_Adc_LLD.c and Reg_eSys_SIU.h are different"
#endif

/* Check if source file and Adc_LLD.h file are of the same vendor */
#if (SIU_ADC_LLD_VENDOR_ID_C != ADC_VENDOR_ID_LLD_H)
#error "Siu_Adc_LLD.c and Adc_LLD.h have different vendor IDs"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((SIU_ADC_LLD_AR_MAJOR_VERSION_C != ADC_AR_MAJOR_VERSION_LLD_H) || \
         (SIU_ADC_LLD_AR_MINOR_VERSION_C != ADC_AR_MINOR_VERSION_LLD_H) || \
         (SIU_ADC_LLD_AR_PATCH_VERSION_C != ADC_AR_PATCH_VERSION_LLD_H))
    #error "AutoSar Version Numbers of Siu_Adc_LLD.c and Adc_LLD.h are different"
    #endif
#endif
/* Check if source file and Adc_LLD.h header file are of the same Software version */
#if ((SIU_ADC_LLD_SW_MAJOR_VERSION_C != ADC_SW_MAJOR_VERSION_LLD_H) || \
     (SIU_ADC_LLD_SW_MINOR_VERSION_C != ADC_SW_MINOR_VERSION_LLD_H) || \
     (SIU_ADC_LLD_SW_PATCH_VERSION_C != ADC_SW_PATCH_VERSION_LLD_H))
#error "Software Version Numbers of Siu_Adc_LLD.c and Adc_LLD.h are different"
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
@file  Siu_Adc_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before "#include"
       See @ref Siu_Adc_LLD_c_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h  See @ref Siu_Adc_LLD_c_2
*/
/* lint -save -e961 -e537 -e451 */
#include "MemMap.h"
/*lint -restore*/


#define ADC_STOP_SEC_VAR_UNSPECIFIED
/**
@file  Siu_Adc_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before "#include"
       See @ref Siu_Adc_LLD_c_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h  See @ref Siu_Adc_LLD_c_2
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
@file  Siu_Adc_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before "#include"
       See @ref Siu_Adc_LLD_c_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h  See @ref Siu_Adc_LLD_c_2
*/
/* lint -save -e961 -e537 -e451 */
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
/* if ! Fado */
#if (IPV_SIU != IPV_SIU_00_02_07_03_5)
#if (STD_ON == ADC_HW_TRIGGER_API)
/*================================================================================================*/
/**
@brief      SIU_LLD_ResetAllHwTrigger
@details    Resets all hardware triggers
*/
/*================================================================================================*/
FUNC (void, ADC_CODE) SIU_LLD_ResetAllHwTrigger(void)
{
    #if ((IPV_SIU==IPV_SIU_00_02_11_00) || (IPV_SIU==IPV_SIU_00_02_08_07))
    /* set SIU_ISEL3 and SIU_ETISR at default reset value */
    REG_WRITE32(SIU_ISEL3, EQADC_REG32_RESET_VALUE);
    REG_WRITE32(SIU_ETISR, EQADC_REG32_RESET_VALUE);
    #else
    /* set SIU_ISEL(4-7) default reset value */
    /**
    @note  Violates MISRA 2004 Rule 11.1, cast from unsigned long to pointer  See @ref Siu_Adc_LLD_c_3
    */
    /*lint -save -e961 */
    REG_WRITE32(SIU_ISEL4, EQADC_REG32_RESET_VALUE);
    REG_WRITE32(SIU_ISEL5, EQADC_REG32_RESET_VALUE);
    REG_WRITE32(SIU_ISEL6, EQADC_REG32_RESET_VALUE);
    REG_WRITE32(SIU_ISEL7, EQADC_REG32_RESET_VALUE);
    /*lint -restore */
    #endif
}

/*================================================================================================*/
/**
@brief      SIU_LLD_EnableHwTrigger
@details    This function will enable the hardware trigger source for the called FIFO.

@param[in]  GrpPtr - Pointer to group configurration
@param[in]  eQADC_AorB - eQADCA or eQADCB
@param[in]  Fifo_no - Fifo number
*/
/*================================================================================================*/
FUNC (void, ADC_CODE) SIU_LLD_EnableHwTrigger(P2CONST(Adc_LLD_GroupConfiguration, AUTOMATIC, ADC_APPL_DATA) GrpPtr, VAR(uint8, AUTOMATIC) eQADC_AorB, VAR(uint8, AUTOMATIC) Fifo_no)
{
    #if ((IPV_SIU==IPV_SIU_00_02_11_00) || (IPV_SIU==IPV_SIU_00_02_08_07))
    eQADC_AorB = (uint8)ADC_EQADC_A;
    REG_WRITE32(SIU_ETISR, EQADC_REG32_RESET_VALUE);
    REG_BIT_SET32(SIU_ISEL3, (uint32)((uint32)(GrpPtr->HwResource)<<(uint32)((uint32)5*(uint32)Fifo_no)));
    #else
    if (eQADC_AorB == (uint8)ADC_EQADC_A)
    {
        /**
        @note  Violates MISRA 2004 Rule 11.1, cast from unsigned long to pointer  See @ref Siu_Adc_LLD_c_3
        */
        /*lint -save -e961 */
        REG_WRITE8(SIU_ISEL4 + (uint32)((uint32)5U-(uint32)Fifo_no), (GrpPtr->HwResource));
        /*lint -restore */
    }
    else
    {
        /**
        @note  Violates MISRA 2004 Rule 11.1, cast from unsigned long to pointer  See @ref Siu_Adc_LLD_c_3
        */
        /*lint -save -e961 */
        REG_WRITE8((SIU_ISEL6 + (uint32)((uint32)5U-(uint32)Fifo_no)), (GrpPtr->HwResource));
        /*lint -restore */
    }
    #endif
}

/*================================================================================================*/
/**
@brief      SIU_LLD_DisableHwTrigger
@details    This function will disables the hardware trigger source for the called FIFO.

@param[in]  eQADC_AorB - eQADCA or eQADCB
@param[in]  Fifo_no - Fifo number
*/
/*================================================================================================*/
FUNC (void, ADC_CODE) SIU_LLD_DisableHwTrigger(VAR(uint8, AUTOMATIC) eQADC_AorB, VAR(uint8, AUTOMATIC) Fifo_no)
{
    #if ((IPV_SIU==IPV_SIU_00_02_11_00) || (IPV_SIU==IPV_SIU_00_02_08_07))
    eQADC_AorB = (uint8)ADC_EQADC_A;
    REG_WRITE32(SIU_ETISR, EQADC_REG32_RESET_VALUE);
    REG_BIT_CLEAR32(SIU_ISEL3, (uint32)(((uint32)(0x1F))<<(uint32)(5U*(uint32)Fifo_no)));
    #else
    /* Reset the trigger source */
    if (eQADC_AorB == (uint8)ADC_EQADC_A)
    {
        /**
        @note  Violates MISRA 2004 Rule 11.1, cast from unsigned long to pointer  See @ref Siu_Adc_LLD_c_3
        */
        /*lint -save -e961 */
        REG_WRITE8((SIU_ISEL4 + (uint32)((uint32)5U-(uint32)Fifo_no)), EQADC_REG8_RESET_VALUE);
        /*lint -restore */
    }
    else
    {
        /**
        @note  Violates MISRA 2004 Rule 11.1, cast from unsigned long to pointer  See @ref Siu_Adc_LLD_c_3
        */
        /*lint -save -e961 */
        REG_WRITE8((SIU_ISEL6 + (uint32)((uint32)5U-(uint32)Fifo_no)), EQADC_REG8_RESET_VALUE);
        /*lint -restore */
    }

    #endif
}
#endif /* #if (STD_ON == ADC_HW_TRIGGER_API) */
#endif /* #if (IPV_SIU != IPV_SIU_00_02_07_03_5) */

#define ADC_STOP_SEC_CODE
/**
@file  Siu_Adc_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before "#include"
       See @ref Siu_Adc_LLD_c_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h  See @ref Siu_Adc_LLD_c_2
*/
/* lint -save -e961 -e537 -e451 */
#include "MemMap.h"
/*lint -restore*/


#ifdef __cplusplus
}
#endif

