/**
    @file    Mcu_PBcfg.c
    @version 2.0.0

    @brief   AUTOSAR Mcu - Mcu postbuild configuration parameters.
    @details This file contains the mcu postbuild configuration parameters.
    
    Project AUTOSAR 3.0 MCAL
    Platform PA
    Peripheral FMPLL
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

@section Mcu_PBcfg_c_REF_1
Violates MISRA 2004 Advisory Rule 19.15, : Repeated include file MemMap.h, Precautions shall be
taken in order to prevent the contents of a header file being included twice This is not a violation
since all header files are protected against multiple inclusions

@section Mcu_PBcfg_c_REF_2
Violates  MISRA  2004 Advisory  Rule  19.1,  only preprocessor statements and comments before
'#include'
This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003
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
#include "Mcu_LLD.h"
/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/** @remarks Covers BSW00374, BSW00318 */
#define MCU_VENDOR_ID_PBCFG_C         43
#define MCU_AR_MAJOR_VERSION_PBCFG_C  3
#define MCU_AR_MINOR_VERSION_PBCFG_C  0
#define MCU_AR_PATCH_VERSION_PBCFG_C  0
#define MCU_SW_MAJOR_VERSION_PBCFG_C  2
#define MCU_SW_MINOR_VERSION_PBCFG_C  0
#define MCU_SW_PATCH_VERSION_PBCFG_C  0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and MCU lld header file are of the same vendor */
#if (MCU_VENDOR_ID_PBCFG_C != MCU_LLD_VENDOR_ID)
    #error "Mcu_Cfg.c and Mcu_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Mcu_LLD header file are of the same Autosar version */
    #if ((MCU_AR_MAJOR_VERSION_PBCFG_C != MCU_LLD_AR_MAJOR_VERSION) || \
         (MCU_AR_MINOR_VERSION_PBCFG_C != MCU_LLD_AR_MINOR_VERSION) || \
         (MCU_AR_PATCH_VERSION_PBCFG_C != MCU_LLD_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of Mcu_PBcfg.c and Mcu_LLD.h are different"
    #endif
#endif
/* Check if source file and Mcu_LLD header file are of the same Software version */
#if ((MCU_SW_MAJOR_VERSION_PBCFG_C != MCU_LLD_SW_MAJOR_VERSION) || \
     (MCU_SW_MINOR_VERSION_PBCFG_C != MCU_LLD_SW_MINOR_VERSION) || \
     (MCU_SW_PATCH_VERSION_PBCFG_C != MCU_LLD_SW_PATCH_VERSION))
    #error "Software Version Numbers of Mcu_PBcfg.c and Mcu_LLD.h are different"
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
#define MCU_START_CONFIG_DATA_UNSPECIFIED
/** @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file, See @ref Mcu_PBcfg_c_REF_1*/
#include "MemMap.h"







STATIC CONST(Mcu_ModeConfigType, MCU_CONST) Mcu_ModeConfigPB_1[1] ={
 /* start of Mcu_ModeConfig[0] */
  {
    3000UL,
    (MCU_KEEP_CPU_AND_PLATFORM_CLOCK|
    MCU_KEEP_NDEDI_CLOCK|
    MCU_KEEP_ETPU_CLOCK|
    MCU_KEEP_NPC_CLOCK|
    MCU_KEEP_EBI_CLOCK|
    MCU_KEEP_ADC_CLOCK|
    MCU_KEEP_EMIOS_CLOCK|
    MCU_KEEP_DFILT_CLOCK|
    MCU_KEEP_PIT_CLOCK|
    MCU_KEEP_FLEXCAN_C_CLOCK|
    MCU_KEEP_FLEXCAN_A_CLOCK|
    MCU_KEEP_DSPI_C_CLOCK|
    MCU_KEEP_DSPI_B_CLOCK|
    MCU_KEEP_ESCI_B_CLOCK|
    MCU_KEEP_ESCI_A_CLOCK)
  }
/* end of Mcu_ModeConfig[0] */

};

STATIC CONST(Mcu_ClockConfigType, MCU_CONST) Mcu_ClockConfigPB_1[1] = {/* start of Mcu_ClockConfig[0] */
    {

 
/*Enhanced*/
  (MCU_ENHANCED_MODE|
   MCU_BYPASS_SYSTEM_DIVIDER|
   MCU_DIVIDE_SYSTEM_CLOCK_BY_2),
  (
   MCU_EXT_BUS_TAP_NOT_SELECTED|
   MCU_EXT_BUS_DIV(1)),
   (MCU_EIGHT_VALUE << MCU_SHIFT_TWENTY_EIGHT) |
   (MCU_PLL_NORMAL_MODE|   MCU_PLL_INPUT_DIVIDE_RATIO(0)|
   MCU_PLL_FEEDBACK_DIVIDE_RATIO(32)),  (MCU_PLL_LOSS_OF_CLOCK_DISABLE|   MCU_PLL_LOSS_OF_LOCK_RESET_DISABLE|   MCU_PLL_LOSS_OF_CLOCK_RESET_DISABLE|   MCU_PLL_LOSS_OF_LOCK_INTR_DISABLE|
   MCU_PLL_LOSS_OF_CLOCK_INTR_DISABLE|
   MCU_PLL_OUTPUT_DIVIDE_RATIO(1)),
   FMPLL_SYNFMMR_RESET_VALUE,

   0x14000000UL,   /*  eMIOS */
   0x0000ef00UL    /* BIUCR0 system clock dependent values*/
    }
/* end of Mcu_ClockConfig[0] */
};
STATIC CONST(McuLLD_ConfigType, MCU_CONST) McuLLD_ConfigPB_1 =
    {
        MCU_SW_SYS_RESET,
        {{(uint32)0x0000e4c0UL },      /* EDMA_A.CR */
        {(uint8)0x00U, /* EDMA_A.CPR_A[0] */(uint8)0x01U, /* EDMA_A.CPR_A[1] */(uint8)0x02U, /* EDMA_A.CPR_A[2] */(uint8)0x03U, /* EDMA_A.CPR_A[3] */
        (uint8) 0x04U, /* EDMA_A.CPR_A4 */        (uint8) 0x05U, /* EDMA_A.CPR_A5 */        (uint8) 0x06U, /* EDMA_A.CPR_A6 */        (uint8) 0x07U, /* EDMA_A.CPR_A7 */
        (uint8) 0x08U, /* EDMA_A.CPR_A8 */        (uint8) 0x09U, /* EDMA_A.CPR_A9 */        (uint8) 0x0aU, /* EDMA_A.CPR_A10 */        (uint8) 0x0bU, /* EDMA_A.CPR_A11 */
        (uint8) 0x0cU, /* EDMA_A.CPR_A12 */        (uint8) 0x0dU, /* EDMA_A.CPR_A13 */        (uint8) 0x0eU, /* EDMA_A.CPR_A14 */        (uint8) 0x0fU, /* EDMA_A.CPR_A15 */
        (uint8) 0x00U, /* EDMA_A.CPR_A16 */        (uint8) 0x01U, /* EDMA_A.CPR_A17 */        (uint8) 0x02U, /* EDMA_A.CPR_A18 */        (uint8) 0x03U, /* EDMA_A.CPR_A19 */
        (uint8) 0x04U, /* EDMA_A.CPR_A20 */        (uint8) 0x05U, /* EDMA_A.CPR_A21 */        (uint8) 0x06U, /* EDMA_A.CPR_A22 */        (uint8) 0x07U, /* EDMA_A.CPR_A23 */
        (uint8) 0x08U, /* EDMA_A.CPR_A24 */        (uint8) 0x09U, /* EDMA_A.CPR_A25 */        (uint8) 0x0aU, /* EDMA_A.CPR_A26 */        (uint8) 0x0bU, /* EDMA_A.CPR_A27 */
        (uint8) 0x0cU, /* EDMA_A.CPR_A28 */        (uint8) 0x0dU, /* EDMA_A.CPR_A29 */        (uint8) 0x0eU, /* EDMA_A.CPR_A30 */        (uint8) 0x0fU, /* EDMA_A.CPR_A31 */
         },
    0UL},
        (uint32)0x00000000UL,        /* BIUCR0 */
        (uint32)0xc0000000UL,        /* BIUCR1 */
        (uint32)0x000000ffUL         /* BIUAPR */       
    };
    

CONST(Mcu_ConfigType, MCU_CONST) McuModuleConfiguration_0 =
    {
        MCU_CLOCKNOTIFICATION_ENABLE,    /* globally enable/disable SCM, loss of clock and loss of lock notification */
        0UL,                       /* number of ram sections */
        1UL,                       /* number of low power modes */
        1UL,                       /* number of clock settings */
        0x00002710UL,                                   /* McuTimeout */
        NULL_PTR,             /* pointer to ram section configurations */
        Mcu_ModeConfigPB_1,            /* pointer to low power mode configurations */
        Mcu_ClockConfigPB_1,           /* pointer to clock settings configurations */
        &McuLLD_ConfigPB_1             /*  pointer to low level*/
    };
/* put McuModuleConfiguration_0 structure into specified section */
#define MCU_STOP_CONFIG_DATA_UNSPECIFIED
/** @note Violates MISRA 2004 Advisory Rules 19.1 and 19.15, Repeated include file,
    See @ref Mcu_PBcfg_c_REF_1 and @ref Mcu_PBcfg_c_REF_2*/
#include "MemMap.h"

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

