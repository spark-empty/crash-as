/**
    @file Reg_eSys_SIU.h
    @version 2.0.0

    @brief   AUTOSAR Port - SIU low level driver register defines.
    @details The description of the registers of the SIU module.

    Project AUTOSAR 3.0 MCAL
    Platform PA
    Peripheral SIU
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

@section Reg_eSys_SIU_REF_1
Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
Macros are used to reduce code complexity

@section Reg_eSys_SIU_REF_2
MISRA-C:2004  19.15 Precautions shall be taken in order to prevent the contents of a
header file being included twice.
This is not a violation since all header files are protected against multiple inclusions.

@section Reg_eSys_SIU_REF_3
MISRA 2004 Advisory Rule 20.2, Re-use of C90 reserved identifier
This violation is due to the use of "_" which is required as per Autosar
*/

/**
@note Violates MISRA 2004 Advisory Rule 20.2, Re-use of C90 reserved 
identifier:_REG_ESYS_SIU_H_- See @ref Reg_eSys_SIU_REF_3
*/
#ifndef _REG_ESYS_SIU_H_
#define _REG_ESYS_SIU_H_

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/**
@note Violates MISRA 2004 Required Rule 19.15,Precaution shall be taken in order to prevent the
      contents of a header file being included twice. - See @ref Reg_eSys_SIU_REF_2
*/
/*lint -save -e537*/
#include "Std_Types.h"
/*lint -restore*/
#include "Reg_eSys.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@remarks Covers BSW00374, BSW00379, BSW00318
*/
/**
Not defined to be MISRA compliant
*/
#define SIU_VENDOR_ID_REG         43
#define SIU_AR_MAJOR_VERSION_REG  3
#define SIU_AR_MINOR_VERSION_REG  0
#define SIU_AR_PATCH_VERSION_REG  0
#define SIU_SW_MAJOR_VERSION_REG  2
#define SIU_SW_MINOR_VERSION_REG  0
#define SIU_SW_PATCH_VERSION_REG  0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#ifdef CHECK_AUTOSAR_VERSION
/**
    Check if Std_Types.h file and SIU register header file are of the same Autosar version
*/
    #if ((SIU_AR_MAJOR_VERSION_REG != STD_TYPES_AR_MAJOR_VERSION) || \
         (SIU_AR_MINOR_VERSION_REG != STD_TYPES_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Reg_eSys_SIU.h and Std_Types.h are different"
    #endif
#endif

/*lint -save -e961*/
/*==================================================================================================
                                DEFINES AND MACROS
==================================================================================================*/
/**************************  IP versions supported by LLD driver definitions *********************/
#define IPV_SIU_00_02_07_03_5  0x0207035UL /** IP version for Fado */
#define IPV_SIU_00_02_11_00    0x021100UL /** IP version for Andorra */
#define IPV_SIU_00_02_07_03_3  0x02070303UL  /** IP version for MAMBA */
#define IPV_SIU_00_02_08_07    0x00020807UL  /** IP version siu_ipi.00.02.08.07 */

#if (IPV_SIU == IPV_SIU_00_02_07_03_3)
#define GPDI_OFFSET 0x0E00UL
#else
#define GPDI_OFFSET 0x0800UL
#endif


/************************** Registers definition *********************/
#define SIU_MIDR                 (SIU_BASEADDR + 0x0004UL)  /**MCU ID Register */
#define SIU_MIDR1_PARTNUM         (uint32)0xFFFF0000UL
#define SIU_MIDR1_PKG             (uint32)0x0000F000UL
#define SIU_MIDR1_MAJOR_MASK      (uint32)0x000000F0UL
#define SIU_MIDR1_MINOR_MASK      (uint32)0x0000000FUL

#define SIU_RSR                 (SIU_BASEADDR + 0x000CUL)  /**Reset status register */
#define SIU_SRCR                (SIU_BASEADDR + 0x0010UL)  /**System reset control register */

#define SIU_EISR                (SIU_BASEADDR + 0x0014UL) /**External interrupt status register */
#define SIU_ISR_EIF              (uint32)0x0000FFFFUL

#define SIU_DIRER               (SIU_BASEADDR + 0x0018UL)  /**DMA/interrupt request enable reg */
#define SIU_DIRER_EIRE           (uint32)0x0000FFFFUL
#define SIU_DIRER_NMISEL8        (uint32)0x80000000UL
#define SIU_DIRER_NMISEL0        (uint32)0x00800000UL

#define SIU_DIRSR               (SIU_BASEADDR + 0x001CUL)  /**DMA/interrupt request select reg */
#define SIU_DIRSR_DIRS3          (uint32)0x00000008UL
#define SIU_DIRSR_DIRS2          (uint32)0x00000004UL
#define SIU_DIRSR_DIRS1          (uint32)0x00000002UL
#define SIU_DIRSR_DIRS0          (uint32)0x00000001UL

#define SIU_OSR                 (SIU_BASEADDR + 0x0020UL)  /**Overrun status register */
#define SIU_OSR_OVF              (uint32)0x0000FFFFUL

#define SIU_ORER                (SIU_BASEADDR + 0x0024UL)  /**Overrun request enable register */
#define SIU_ORER_ORE             (uint32)0x0000FFFFUL

/**IRQ rising-edge event enable register */
#define SIU_IREER               (SIU_BASEADDR + 0x0028UL)
#define SIU_IREER_IREE           (uint32)0x0000FFFFUL
#define SIU_IREER_IREE_NMISEL8   (uint32)0x80000000UL
#define SIU_IREER_IREE_NMISEL0   (uint32)0x00800000UL

/**IRQ falling-edge event enable register */
#define SIU_IFEER               (SIU_BASEADDR + 0x002CUL)
#define SIU_IFEER_IFEE           (uint32)0x0000FFFFUL
#define SIU_IFEER_IFEE_NMISEL8   (uint32)0x80000000UL
#define SIU_IFEER_IFEE_NMISEL0   (uint32)0x00800000UL

#define SIU_IDFR                (SIU_BASEADDR + 0x0030UL)  /**IRQ digital filter register */
#define SIU_IDER_DFL             (uint32)0x0000000FUL

#define SIU_IFIR                (SIU_BASEADDR + 0x0034UL)  /**IRQ filtered input register */

/**
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined -
See @ref Reg_eSys_SIU_REF_1
*/

/**Pad Configuration Register 0->511 */
#define SIU_PCR(PIN)             ((uint32)SIU_BASEADDR + (uint32)0x0040UL + (((uint32)PIN)<<1))
#define SIU_PCR_PA               (uint16)0x1C00U
#define SIU_PCR_OBE              (uint16)0x0200U
#define SIU_PCR_IBE              (uint16)0x0100U
#define SIU_PCR_DSC              (uint16)0x00C0U
#define SIU_PCR_ODE              (uint16)0x0020U
#define SIU_PCR_HYS              (uint16)0x0010U
#define SIU_PCR_SRC              (uint16)0x000CU
#define SIU_PCR_WPE              (uint16)0x0002U
#define SIU_PCR_WPS              (uint16)0x0001U
/**
PCR bit register values
*/
#define SIU_PCR_PA_GPIO          (uint16)0x0000U
#define SIU_PCR_PA_ALT1          (uint16)0x0400U
#define SIU_PCR_PA_ALT2          (uint16)0x0800U
#define SIU_PCR_PA_ALT3          (uint16)0x0C00U
#define SIU_PCR_PA_ALT4          (uint16)0x1000U
#define SIU_PCR_PA_ALT5          (uint16)0x1400U
#define SIU_PCR_PA_ALT6          (uint16)0x1800U
#define SIU_PCR_PA_ALT7          (uint16)0x1C00U
#define SIU_PCR_PA_ALT8          (uint16)0x2000U
#define SIU_PCR_OBE_ON           (uint16)0x0200U
#define SIU_PCR_OBE_OFF          (uint16)0x0000U
#define SIU_PCR_IBE_ON           (uint16)0x0100U
#define SIU_PCR_IBE_OFF          (uint16)0x0000U
#define SIU_PCR_DSC_50           (uint16)0x00C0U
#define SIU_PCR_DSC_30           (uint16)0x0080U
#define SIU_PCR_DSC_20           (uint16)0x0040U
#define SIU_PCR_DSC_10           (uint16)0x0000U
#define SIU_PCR_ODE_ON           (uint16)0x0020U
#define SIU_PCR_ODE_OFF          (uint16)0x0000U
#define SIU_PCR_HYS_ON           (uint16)0x0010U
#define SIU_PCR_HYS_OFF          (uint16)0x0000U
#define SIU_PCR_SRC_MAX          (uint16)0x000CU
#define SIU_PCR_SRC_MED          (uint16)0x0004U
#define SIU_PCR_SRC_MIN          (uint16)0x0000U
#define SIU_PCR_WPE_ON           (uint16)0x0002U
#define SIU_PCR_WPE_OFF          (uint16)0x0000U
#define SIU_PCR_WPS_ON           (uint16)0x0001U
#define SIU_PCR_WPS_OFF          (uint16)0x0000U

#define SIU_PCR_PA_OFFSET        (uint8)10
#define SIU_MODE_BIT_OFFSET_MASK (uint16)0x000F

/**
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined -
See @ref Reg_eSys_SIU_REF_1
*/
/** GPIO Pin Data Output Register 0->511 */
#define SIU_GPDO(PIN)            (SIU_BASEADDR + (uint32)0x0600UL + (uint32)(PIN))
#define SIU_GPDO_PDO_0           (uint32)0x01000000UL
#define SIU_GPDO_PDO_1           (uint32)0x00010000UL
#define SIU_GPDO_PDO_2           (uint32)0x00000100UL
#define SIU_GPDO_PDO_3           (uint32)0x00000001UL

/**
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined -
See @ref Reg_eSys_SIU_REF_1
*/
/** GPIO Pin Data Input Register */
#define SIU_GPDI(PIN)            (SIU_BASEADDR + (uint32)GPDI_OFFSET + (uint32)(PIN))

/**
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined -
See @ref Reg_eSys_SIU_REF_1
*/
/** GPIO Pin Data Input Register */
#define SIU_GPDI8(PIN)           (SIU_BASEADDR + (uint32)GPDI_OFFSET + (uint32)(PIN))

/**
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined -
See @ref Reg_eSys_SIU_REF_1
*/
/** GPIO PIN Data Input Register 0->511 NEW IMPLEMENTATION*/
#define SIU_GPDI32(PIN)  (SIU_BASEADDR + (uint32)GPDI_OFFSET + (PIN))
#define SIU_GPDI_PDI_0           (uint32)0x01000000UL
#define SIU_GPDI_PDI_1           (uint32)0x00010000UL
#define SIU_GPDI_PDI_2           (uint32)0x00000100UL
#define SIU_GPDI_PDI_3           (uint32)0x00000001UL

/** eQADC trigger IMUX Select Register */
#define SIU_ETISR                (SIU_BASEADDR + 0x0900UL)
/** External IRQ input select register */
#define SIU_EIISR                (SIU_BASEADDR + 0x0904UL)
/** DSPI input select register */
#define SIU_DISR                 (SIU_BASEADDR + 0x0908UL)
/** SIU_EIISR is sometimes reffered as SIU_ISEL1 */
#define SIU_ISEL1                SIU_EIISR
/** SIU_DISR is sometimes reffered as SIU_ISEL2 */
#define SIU_ISEL2                SIU_DISR
/** eQADC Command FIFO Trigger Source Select-IMUX Select 3 register */
#define SIU_ISEL3                (SIU_BASEADDR + 0x090CUL)
/** eQADC Command FIFO Trigger Source Select-IMUX Select 4 register */
#define SIU_ISEL4                (SIU_BASEADDR + 0x0910UL)
/** eQADC Command FIFO Trigger Source Select-IMUX Select 5 register */
#define SIU_ISEL5                (SIU_BASEADDR + 0x0914UL)
/** eQADC Command FIFO Trigger Source Select-IMUX Select 6 register */
#define SIU_ISEL6                (SIU_BASEADDR + 0x0918UL)
/** eQADC Command FIFO Trigger Source Select-IMUX Select 7 register */
#define SIU_ISEL7                (SIU_BASEADDR + 0x091CUL)
/** eTPU input select register */
#define SIU_ISEL8                (SIU_BASEADDR + 0x0920UL)
/** eQADC Advance Trigger Selection */
#define SIU_ISEL9                (SIU_BASEADDR + 0x0924UL)
/** External interrupt select register 2A */
#define SIU_ISEL2A               (SIU_BASEADDR + 0x09C4UL)

#define SIU_DECFIL1              (SIU_BASEADDR + 0x0928UL)  /** Decimation Filter register 1 */
#define SIU_DECFIL2              (SIU_BASEADDR + 0x092CUL)  /** Decimation Filter register 2 */

#define SIU_CCR                  (SIU_BASEADDR + 0x0980UL)  /** Chip configuration register */
#define SIU_ECCR                 (SIU_BASEADDR + 0x0984UL)  /** External clock control register */

#define SIU_CBRH                 (SIU_BASEADDR + 0x0990UL)  /** Compare B high register */
#define SIU_CBRL                 (SIU_BASEADDR + 0x0994UL)  /** Compare B low register */

#define SIU_SYSDIV               (SIU_BASEADDR + 0x09A0UL)  /** System clock register */
#define SIU_HLT                  (SIU_BASEADDR + 0x09A4UL)  /** Halt register */
#define SIU_HLTACK               (SIU_BASEADDR + 0x09A8UL)  /** Halt acknowledge register */
#define SIU_HLT0                 (SIU_BASEADDR + 0x09A4UL)  /** Halt0 register */
#define SIU_HLT1                 (SIU_BASEADDR + 0x09A8UL)  /** Halt1 register */
#define SIU_HLTACK0              (SIU_BASEADDR + 0x09ACUL)  /** Halt0 acknowledge register */
#define SIU_HLTACK1              (SIU_BASEADDR + 0x09B0UL)  /** Halt1 acknowledge register */

/**
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined -
See @ref Reg_eSys_SIU_REF_1
*/
/** Parallel GPIO Pin Data Output Register 0->15 */
#define SIU_PGPDO(PGPDO_OFFSET)  (SIU_BASEADDR + (uint32)0x0C00UL + (PGPDO_OFFSET))
/**
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined -
See @ref Reg_eSys_SIU_REF_1
*/
/** Parallel GPIO Pin Data Input Register 0->15 */
#define SIU_PGPDI(PGPDI_OFFSET)  (SIU_BASEADDR + (uint32)0x0C40UL + (PGPDI_OFFSET))
/**
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined -
See @ref Reg_eSys_SIU_REF_1
*/
/** Masked Parallel GPIO Pin Data Output Register 0->31 */
#define SIU_MPGPDO(MPGPDO_OFFSET)(SIU_BASEADDR + (uint32)0x0C80UL + (MPGPDO_OFFSET))
#define SIU_MPGPDO_MASK           0xFFFF0000UL
#define SIU_MPGPDO_DATA           0x0000FFFFUL

/**
Masked Serial GPO Register for DSPI
*/
/** DSPIA GP Mask-Output High Register */
#define SIU_DSPIAH               (SIU_BASEADDR + 0x0D00UL)
/** DSPIA GP Mask-Output Low Register */
#define SIU_DSPIAL               (SIU_BASEADDR + 0x0D04UL)
/** DSPIB GP Mask-Output High Register */
#define SIU_DSPIBH               (SIU_BASEADDR + 0x0D08UL)
/** DSPIB GP Mask-Output Low Register */
#define SIU_DSPIBL               (SIU_BASEADDR + 0x0D0CUL)
/** DSPIC GP Mask-Output High Register */
#define SIU_DSPICH               (SIU_BASEADDR + 0x0D10UL)
/** DSPIC GP Mask-Output Low Register */
#define SIU_DSPICL               (SIU_BASEADDR + 0x0D14UL)
/** DSPID GP Mask-Output High Register */
#define SIU_DSPIDH               (SIU_BASEADDR + 0x0D18UL)
/** DSPID GP Mask-Output Low Register */
#define SIU_DSPIDL               (SIU_BASEADDR + 0x0D1CUL)

/** DSPIA eTPUB Select Register */
#define SIU_ETPUBA               (SIU_BASEADDR + 0x0D40UL)
/** DSPIA eMIOS Select Register */
#define SIU_EMIOSA               (SIU_BASEADDR + 0x0D44UL)
/** DSPIA SIU_DSPIAH/L Select Register */
#define SIU_DSPIAHLA             (SIU_BASEADDR + 0x0D48UL)

/** DSPIB eTPUB Select Register */
#define SIU_ETPUAB               (SIU_BASEADDR + 0x0D50UL)
/** DSPIB eMIOS Select Register */
#define SIU_EMIOSB               (SIU_BASEADDR + 0x0D54UL)
/** DSPIB SIU_DSPIAH/L Select Register */
#define SIU_DSPIBHLB             (SIU_BASEADDR + 0x0D58UL)

/** DSPIC eTPUB Select Register */
#define SIU_ETPUAC               (SIU_BASEADDR + 0x0D60UL)
/** DSPIC eMIOS Select Register */
#define SIU_EMIOSC               (SIU_BASEADDR + 0x0D64UL)
/** DSPIC SIU_DSPIAH/L Select Register */
#define SIU_DSPIBHLC             (SIU_BASEADDR + 0x0D68UL)

/** DSPID eTPUB Select Register */
#define SIU_ETPUAD               (SIU_BASEADDR + 0x0D70UL)
/** DSPID eMIOS Select Register */
#define SIU_EMIOSD               (SIU_BASEADDR + 0x0D74UL)
/** DSPID SIU_DSPIAH/L Select Register */
#define SIU_DSPIBHLD             (SIU_BASEADDR + 0x0D78UL)

/*lint -restore*/


#ifdef __cplusplus
}
#endif

#endif /* _REG_ESYS_SIU_H_ */
