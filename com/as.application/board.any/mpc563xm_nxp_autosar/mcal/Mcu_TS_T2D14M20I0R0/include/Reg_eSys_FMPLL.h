/**
    @file    Reg_eSys_FMPLL.h
    @version 2.0.0

@brief   AUTOSAR Mcu - Brief description.
@details Detailed description.

Project AUTOSAR 3.0 MCAL
Patform PA
Peripheral FMPLL
Dependencies none

ARVersion 3.0.0
ARRevision ASR_REL_3_0_REV_0003
ARConfVariant
SWVersion 2.0.0
BuildVersion XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223

(c) Copyright 2006-2011 Freescale Semiconductor Inc. & PITicroelectronics
All Rights Reserved.
*/
/*==================================================================================================
==================================================================================================*/
/**
@page misra_violations MISRA-C:2004 violations

@section Reg_eSys_FMPLL_REF_1
MISRA-C:2004  19.15 Precautions shall be taken in order to prevent the contents of a
header file being included twice.
This is not a violation since all header files are protected against multiple inclusions.

@section Reg_eSys_FMPLL_REF_2
MISRA-C:2004 19.7 VIOLATION: Use of function like macro.
This violation is due to function like macros defined for register operations.
Function like macros are used to reduce code complexity.

@section Reg_eSys_FMPLL_REF_3
MISRA 2004 Advisory Rule 20.2, Re-use of C90 reserved identifier
This violation is due to the use of "_" which is required as per Autosar
*/

/**
@note Violates MISRA 2004 Advisory Rule 20.2, Re-use of C90 reserved 
identifier:_REG_ESYS_FMPLL_H_- See @ref Reg_eSys_FMPLL_REF_3
*/
#ifndef _REG_ESYS_FMPLL_H_
#define _REG_ESYS_FMPLL_H_

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
/** @note   Violates MISRA 2004 Advisory Rule 19.15, Repeated include file,
See @ref Reg_eSys_FMPLL_REF_1*/
#include "Mcu.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/** @remarks Covers BSW00374, BSW00379, BSW00318 */
#define REG_ESYS_FMPLL_VENDOR_ID            43

#define REG_ESYS_FMPLL_AR_MAJOR_VERSION     3
#define REG_ESYS_FMPLL_AR_MINOR_VERSION     0
#define REG_ESYS_FMPLL_AR_PATCH_VERSION     0
#define REG_ESYS_FMPLL_SW_MAJOR_VERSION     2
#define REG_ESYS_FMPLL_SW_MINOR_VERSION     0
#define REG_ESYS_FMPLL_SW_PATCH_VERSION     0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if header file and Mcu.h file are of the same vendor */
#if (REG_ESYS_FMPLL_VENDOR_ID != MCU_VENDOR_ID_CFG)
#error "Reg_eSys_FMPll.h and Mcu.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
/* Check if source file and Gpt header file are of the same Autosar version */
#if ((REG_ESYS_FMPLL_AR_MAJOR_VERSION != MCU_AR_MAJOR_VERSION) || \
(REG_ESYS_FMPLL_AR_MINOR_VERSION != MCU_AR_MINOR_VERSION) || \
(REG_ESYS_FMPLL_AR_PATCH_VERSION != MCU_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of Reg_eSys_FMPll.h and Mcu.h are different"
#endif
#endif

/* Check if source file and Mcu header file are of the same software version */
#if ((REG_ESYS_FMPLL_SW_MAJOR_VERSION != MCU_SW_MAJOR_VERSION) || \
(REG_ESYS_FMPLL_SW_MINOR_VERSION != MCU_SW_MINOR_VERSION) || \
(REG_ESYS_FMPLL_SW_PATCH_VERSION != MCU_SW_PATCH_VERSION))
#error "Software Version Numbers of Reg_eSys_FMPll.h and Mcu.h are different"
#endif
/* 
*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/**************************  IP versions supported by LLD driver definitions *********************/                               
                  
#define IPV_FMPLL_01_01_07_00   0x01010700UL /**< IP version for Andorra */
#define IPV_FMPLL_01_01_02_00   0x01010200UL /**< IP version for Monaco */
#define IPV_FMPLL_00_00_01_02   0x00000102UL /**< IP version for FADO */

/* FMPLL synthesizer status register */
#define FMPLL_SYNSR             (FMPLL_BASEADDR + 0x0004UL)
/* FMPLL enhanced synthesizer control register 1 */
#define FMPLL_ESYNCR1           (FMPLL_BASEADDR + 0x0008UL)
/* FMPLL enhanced synthesizer control register 2 */
#define FMPLL_ESYNCR2           (FMPLL_BASEADDR + 0x000CUL)

/* FMPLL Synthesizer FM Control Register */
#define FMPLL_SYNFMCR           (FMPLL_BASEADDR + 0x0020UL)

/* FMPLL Synthesizer FM Control Register */
#define FMPLL_SYNFMMR           (FMPLL_BASEADDR + 0x0018UL)
        

/*************************FMPLL SYNSR  ************************************************/

/* Loss- of-Lock Flag. */
#define FMPLL_SYNSR_LOLF        (uint32)0x00000200UL
/* Loss-Of-Clock Status*/
#define FMPLL_SYNSR_LOC         (uint32)0x00000100UL
/* Clock Mode */
#define FMPLL_SYNSR_MODE        (uint32)0x00000080UL
/* PLL Mode Select */
#define FMPLL_SYNSR_PLLSEL      (uint32)0x00000040UL
/* PLL Clock Reference Source*/
#define FMPLL_SYNSR_PLLREF      (uint32)0x00000020UL
/* Sticky PLL Lock Status Bit */
#define FMPLL_SYNSR_LOCKS       (uint32)0x00000010UL
/* PLL Lock Status Bit*/
#define FMPLL_SYNSR_LOCK        (uint32)0x00000008UL
/* Loss-of-Clock Flag */
#define FMPLL_SYNSR_LOCF        (uint32)0x00000004UL
/* Calibration Complete*/
#define FMPLL_SYNSR_CALDONE     (uint32)0x00000002UL
/* Calibration Passed */
#define FMPLL_SYNSR_CALPASS     (uint32)0x00000001UL

/*************************FMPLL ESYNCR1  ************************************************/

/*Clock Configuration */
#define FMPLL_ESYNCR1_CLKCFG        (uint32)0x70000000UL
/* Enhanced Pre-Divider */
#define FMPLL_ESYNCR1_EPREDIV       (uint32)0x000F0000UL
/* Enhanced Multiplication Factor Divider*/
#define FMPLL_ESYNCR1_EMFD          (uint32)0x000000FFUL

/*************************FMPLL ESYNCR2  ************************************************/

/*Loss-of-Clock Enable */
#define FMPLL_ESYNCR2_LOCEN             (uint32)0x00800000UL
/*Loss-of-Lock Reset Enable */
#define FMPLL_ESYNCR2_LOLRE             (uint32)0x00400000UL
/*Loss-of-Clock Reset Enable */
#define FMPLL_ESYNCR2_LOCRE             (uint32)0x00200000UL
/*Loss-of-Lock Interrupt Request*/
#define FMPLL_ESYNCR2_LOLIRQ            (uint32)0x00100000UL
/*Loss- of-Clock Interrupt Request */
#define FMPLL_ESYNCR2_LOCIRQ            (uint32)0x00080000UL
/*Enhanced ModULation Rate */
#define FMPLL_ESYNCR2_ERATE             (uint32)0x00030000UL
/*The CLKCFG_DIS bit */
#define FMPLL_ESYNCR2_CLKCFG_DIS        (uint32)0x00008000UL
/*Enhanced Modulation Depth */
#define FMPLL_ESYNCR2_EDEPTH            (uint32)0x00000700UL
/*Enhanced Reduced Frequency Divider */
#define FMPLL_ESYNCR2_ERFD              (uint32)0x0000003FUL

#define MCU_PLL_OFF_MODE                        (uint32)0x00000000UL
#define MCU_PLL_NORMAL_MODE                     (uint32)0x70000000UL
#define MCU_PLL_NORMAL_MODE_EXT_REFERENCE       (uint32)0x60000000UL
#define MCU_PLL_NORMAL_MODE_CRYSTAL_REFERENCE   (uint32)0x70000000UL
#define MCU_PLL_DISABLE_CLOCK_CONFIGURATION     (uint32)0x00008000UL
#define MCU_PLL_ENABLE_CLOCK_CONFIGURATION      (uint32)0x00000000UL
#define MCU_PLL_LOSS_OF_CLOCK_ENABLE            (uint32)0x00800000UL
#define MCU_PLL_LOSS_OF_CLOCK_DISABLE           (uint32)0x00000000UL
#define MCU_PLL_LOSS_OF_LOCK_RESET_ENABLE       (uint32)0x00400000UL
#define MCU_PLL_LOSS_OF_LOCK_RESET_DISABLE      (uint32)0x00000000UL
#define MCU_PLL_LOSS_OF_CLOCK_RESET_ENABLE      (uint32)0x00200000UL
#define MCU_PLL_LOSS_OF_CLOCK_RESET_DISABLE     (uint32)0x00000000UL
#define MCU_PLL_LOSS_OF_LOCK_INTR_ENABLE        (uint32)0x00100000UL
#define MCU_PLL_LOSS_OF_LOCK_INTR_DISABLE       (uint32)0x00000000UL
#define MCU_PLL_LOSS_OF_CLOCK_INTR_ENABLE       (uint32)0x00080000UL
#define MCU_PLL_LOSS_OF_CLOCK_INTR_DISABLE      (uint32)0x00000000UL
#define MCU_PLL_MODULATION_RATE_FXDIV80         (uint32)0x00000000UL
#define MCU_PLL_MODULATION_RATE_FXDIV40         (uint32)0x00010000UL
#define MCU_PLL_MODULATION_RATE_FXDIV20         (uint32)0x00020000UL

/** @note   Violates MISRA 2004 Advisory Rule 19.7, See @ref Reg_eSys_FMPLL_REF_2*/
#define MCU_PLL_INPUT_DIVIDE_RATIO(x)       ((uint32)(((uint32)x)<<16))
/** @note   Violates MISRA 2004 Advisory Rule 19.7, See @ref Reg_eSys_FMPLL_REF_2*/
#define MCU_PLL_FEEDBACK_DIVIDE_RATIO(x)    ((uint32)(((uint32)x)<<0))
/** @note   Violates MISRA 2004 Advisory Rule 19.7, See @ref Reg_eSys_FMPLL_REF_2*/
#define MCU_PLL_OUTPUT_DIVIDE_RATIO(x)      ((uint32)(((uint32)x)<<0))
/** @note   Violates MISRA 2004 Advisory Rule 19.7, See @ref Reg_eSys_FMPLL_REF_2*/
#define MCU_PLL_MODULATION_DEPTH(x)         ((uint32)(((uint32)x)<<8))

/*************************FMPLL ESYNCR2  ************************************************/
/* Frequency Modulation Register Enable */
#define FMPLL_SYNFMCR_FMDACEN               (uint32)0x40000000UL


/************************* FMPLL SYNFMMR  ************************************************/

#define FMPLL_SYNFMMR_MODEN_EN                (uint32)0x40000000UL
#define FMPLL_SYNFMMR_MODEN_DIS               (uint32)0x00000000UL

#define FMPLL_SYNFMMR_BSY                     (uint32)0x80000000UL

/* MODSEL field */
#define FMPLL_SYNFMMR_MODSEL_CENTERED         (uint32)0x00000000UL
#define FMPLL_SYNFMMR_MODSEL_BELOW            (uint32)0x20000000UL

/** @note   Violates MISRA 2004 Advisory Rule 19.7, See @ref Reg_eSys_FMPLL_REF_2*/
/*lint -save -e961*/
/* MODPERIOD field */
#define FMPLL_SYNFMMR_MODPERIOD(x)            ((uint32)(((uint32)x)<<16))

/* MODPERIOD field */
#define FMPLL_SYNFMMR_INCSTEP(x)              ((uint32)(((uint32)x)<<0))
/*lint -restore*/

#define FMPLL_SYNFMMR_RESET_VALUE             (uint32)0x00000000UL   

#define FMPLL_SYNFMMR_MODPERIOD_MASK           (uint32)0x1FFF0000UL 
#define FMPLL_SYNFMMR_INCSTEP_MASK             (uint32)0x00007FFFUL
#define FMPLL_SYNFMMR_MODSEL_MASK              (uint32)0x20000000UL


/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
#define MCU_START_SEC_CODE
/** @note   Violates MISRA 2004 Advisory Rule  19.15 , Refer to  Reg_eSys_FMPLL_REF_1 above*/
/*lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

#define MCU_STOP_SEC_CODE
/** @note   Violates MISRA 2004 Advisory Rule  19.15 , Refer to  Reg_eSys_FMPLL_REF_1 above*/
/*lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif
#endif                                            /*_REG_ESYS_FMPLL_H_*/
