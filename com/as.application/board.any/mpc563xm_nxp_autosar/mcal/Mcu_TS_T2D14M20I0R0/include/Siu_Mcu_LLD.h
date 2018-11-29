/**
    @file    SIU_Mcu_LLD.h
    @version 2.0.0

@brief   AUTOSAR Mcu - Brief description.
@details Detailed description.

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

@section Siu_Mcu_LLD_H_REF_1
MISRA-C:2004  19.15 Precautions shall be taken in order to prevent the contents of a
header file being included twice.
This is not a violation since all header files are protected against multiple inclusions.

@section Siu_Mcu_LLD_H_REF_2
MISRA-C:2004 19.7 VIOLATION: Use of function like macro.
This violation is due to function like macros defined for register operations.
Function like macros are used to reduce code complexity.

@section Siu_Mcu_LLD_H_REF_3
MISRA 2004 Advisory Rule 20.2, Re-use of C90 reserved identifier
This violation is due to the use of "_" which is required as per Autosar
*/

/**
@note Violates MISRA 2004 Advisory Rule 20.2, Re-use of C90 reserved 
identifier:_SIU_MCU_LLD_H_- See @ref Siu_Mcu_LLD_H_REF_3
*/
#ifndef _SIU_MCU_LLD_H_
#define _SIU_MCU_LLD_H_

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
/** @note   Violates MISRA 2004 Advisory Rule 19.15, Repeated include files,
See @ref Siu_Mcu_LLD_H_REF_1*/
/*lint -save -e537*/
#include "Mcu.h"
#include "Reg_eSys_SIU.h"
/*lint -restore*/

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** @remarks Covers BSW00374, BSW00379, BSW00318 */
#define SIU_MCU_LLD_VENDOR_ID            43

#define SIU_MCU_LLD_AR_MAJOR_VERSION     3
#define SIU_MCU_LLD_AR_MINOR_VERSION     0
#define SIU_MCU_LLD_AR_PATCH_VERSION     0
#define SIU_MCU_LLD_SW_MAJOR_VERSION     2
#define SIU_MCU_LLD_SW_MINOR_VERSION     0
#define SIU_MCU_LLD_SW_PATCH_VERSION     0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if header file and Mcu.h file are of the same vendor */
#if (SIU_MCU_LLD_VENDOR_ID != MCU_VENDOR_ID_CFG)
#error "SIU_Mcu_LLD.h and Mcu.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
#if ((SIU_MCU_LLD_AR_MAJOR_VERSION != MCU_AR_MAJOR_VERSION_CFG) || \
(SIU_MCU_LLD_AR_MINOR_VERSION != MCU_AR_MINOR_VERSION_CFG) || \
(SIU_MCU_LLD_AR_PATCH_VERSION != MCU_AR_PATCH_VERSION_CFG))
#error "AutoSar Version Numbers of SIU_Mcu_LLD.h and Mcu.h are different"
#endif
#endif
/* Check if source file and MCU header file are of the same Software version */
#if ((SIU_MCU_LLD_SW_MAJOR_VERSION != MCU_SW_MAJOR_VERSION_CFG) || \
(SIU_MCU_LLD_SW_MINOR_VERSION != MCU_SW_MINOR_VERSION_CFG) || \
(SIU_MCU_LLD_SW_PATCH_VERSION != MCU_SW_PATCH_VERSION_CFG))
#error "Software Version Numbers of SIU_Mcu_LLD.h and Mcu.h are different"
#endif

/* Check if header file and Reg_eSys_SIU.h file are of the same vendor */
#if (SIU_MCU_LLD_VENDOR_ID != SIU_VENDOR_ID_REG)
#error "SIU_Mcu_LLD.h and Reg_eSys_SIU.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
#if ((SIU_MCU_LLD_AR_MAJOR_VERSION != SIU_AR_MAJOR_VERSION_REG) || \
(SIU_MCU_LLD_AR_MINOR_VERSION != SIU_AR_MINOR_VERSION_REG) || \
(SIU_MCU_LLD_AR_PATCH_VERSION != SIU_AR_PATCH_VERSION_REG))
#error "AutoSar Version Numbers of SIU_Mcu_LLD.h and Reg_eSys_SIU.h are different"
#endif
#endif
/* Check if source file and Reg_eSys_SIU header file are of the same Software version */
#if ((SIU_MCU_LLD_SW_MAJOR_VERSION != SIU_SW_MAJOR_VERSION_REG) || \
(SIU_MCU_LLD_SW_MINOR_VERSION != SIU_SW_MINOR_VERSION_REG) || \
(SIU_MCU_LLD_SW_PATCH_VERSION != SIU_SW_PATCH_VERSION_REG))
#error "Software Version Numbers of SIU_Mcu_LLD.h and Reg_eSys_SIU.h are different"
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
/**************************** SIU_RSR Memory Map ******************************/

                                                  /* Power On Reset Status */
#define  SIU_RSR_PORS                       (uint32)0x80000000UL
                                                  /* External Reset Status */
#define  SIU_RSR_ERS                        (uint32)0x40000000UL
                                                  /* Loss of lock Reset Status */
#define  SIU_RSR_LLRS                       (uint32)0x20000000UL
                                                  /* Loss of clock Reset Status */
#define  SIU_RSR_LCRS                       (uint32)0x10000000UL
                                                  /* Watchdog Timer/Debug Reset Status */
#define  SIU_RSR_WDRS                       (uint32)0x08000000UL
                                                  /* Checkstop Reset Status */
#define  SIU_RSR_CRS                        (uint32)0x04000000UL
                                                  /* Platform software watch dog reset status */
#define  SIU_RSR_SWTRS                      (uint32)0x02000000UL
                                                  /* Software System Reset Status */
#define  SIU_RSR_SSRS                       (uint32)0x00020000UL
                                                  /* Software External Reset Status*/
#define  SIU_RSR_SERS                       (uint32)0x00010000UL
                                                  /* Weak pull configuration pin status*/
#define  SIU_RSR_WKPCFG                     (uint32)0x00008000UL
                                                  /* Auto Baud Rate*/
#define  SIU_RSR_ABR                        (uint32)0x00000008UL
                                                  /* Reset glitch flag*/
#define  SIU_RSR_RGF                        (uint32)0x00000001UL



/**************************** SIU_SRCR Memory Map ******************************/

                                                  /* Software System Reset */
#define  SIU_SRCR_SSR                       (uint32)0x80000000UL
                                                  /* Software External Reset */
#define  SIU_SRCR_SER                       (uint32)0x40000000UL

/* *************************** SIU_ECCR ***************************************/
#define  MCU_EXT_CLOCK_ENABLE               (uint32)0x00000008UL
#define  MCU_EXT_CLOCK_DIVIDE_BY_1          (uint32)0x00000000UL
#define  MCU_EXT_CLOCK_DIVIDE_BY_2          (uint32)0x000000001L
#define  MCU_EXT_CLOCK_DIVIDE_BY_4          (uint32)0x000000002L
#define  MCU_EXT_CLOCK_DIVIDE_BY_8          (uint32)0x000000003L
#define  MCU_EXT_CLOCK_DISABLE              (uint32)0x00000000UL

#ifdef IPV_SIU
    #if (IPV_SIU == IPV_SIU_00_02_07_03_5) /* if Fado */

        /* *************************** SIU_SYSCLK ***************************************/
        #define MCU_SYSCLOCK_SEL_FMPLL              (uint32)0x80000000UL
        #define MCU_SYSCLOCK_SEL_XTAL               (uint32)0x40000000UL
        #define MCU_SYSCLOCK_SEL_IRC_16MHz          (uint32)0x00000000UL

        #define MCU_DIVIDE_SYSTEM_CLOCK_BY_1        (uint32)0x00000000UL
        #define MCU_DIVIDE_SYSTEM_CLOCK_BY_2        (uint32)0x08000000UL
        #define MCU_DIVIDE_SYSTEM_CLOCK_BY_4        (uint32)0x10000000UL
        #define MCU_DIVIDE_SYSTEM_CLOCK_BY_8        (uint32)0x18000000UL
        #define MCU_DIVIDE_SYSTEM_CLOCK_BY_16       (uint32)0x20000000UL

        #define MCU_PER_SET1_CLOCK_DIV_BY_1         (uint32)0x00000000UL
        #define MCU_PER_SET1_CLOCK_DIV_BY_2         (uint32)0x00000001UL
        #define MCU_PER_SET1_CLOCK_DIV_BY_4         (uint32)0x00000002UL
        #define MCU_PER_SET1_CLOCK_DIV_BY_8         (uint32)0x00000003UL

        #define MCU_PER_SET2_CLOCK_DIV_BY_1         (uint32)0x00000000UL
        #define MCU_PER_SET2_CLOCK_DIV_BY_2         (uint32)0x00000004UL
        #define MCU_PER_SET2_CLOCK_DIV_BY_4         (uint32)0x00000008UL
        #define MCU_PER_SET2_CLOCK_DIV_BY_8         (uint32)0x0000000CUL

        #define MCU_PER_SET3_CLOCK_DIV_BY_1         (uint32)0x00000000UL
        #define MCU_PER_SET3_CLOCK_DIV_BY_2         (uint32)0x00000010UL
        #define MCU_PER_SET3_CLOCK_DIV_BY_4         (uint32)0x00000020UL
        #define MCU_PER_SET3_CLOCK_DIV_BY_8         (uint32)0x00000030UL

        #define MCU_PER_SET4_CLOCK_DIV_BY_1   (uint32)0x00000000UL
        #define MCU_PER_SET4_CLOCK_DIV_BY_2   (uint32)0x00000040UL
        #define MCU_PER_SET4_CLOCK_DIV_BY_4   (uint32)0x00000080UL
        #define MCU_PER_SET4_CLOCK_DIV_BY_8   (uint32)0x000000C0UL

    #else

        /***************************** SIU_SYSDIV  Memory Map **************************/
                                                     /* SYSCLKDIV field */
        #define SIU_SYSDIV_SYSCLKDIV                (uint32)0x0000000CUL
                                                     /*IPCLKDIV field */
        #define SIU_SYSDIV_IPCLKDIV                 (uint32)0x00000300UL
                                                     /*BYPASS field */
        #define SIU_SYSDIV_BYPASS                   (uint32)0x00000010UL

        #define MCU_ENG_CLOCK_SOURCE_SYSTEM_CLOCK   0x0
        #define MCU_ENG_CLOCK_SOURCE_EXTAL_CLOCK    0x1

        #define MCU_ENHANCED_MODE                   (uint32)0x00000000UL
        #define MCU_FULL_MODE                       (uint32)0x00000100UL
        #define MCU_LEGACY_MODE                     (uint32)0x00000300UL
        #define MCU_BYPASS_SYSTEM_DIVIDER           (uint32)0x00000010UL
        #define MCU_USE_SYSTEM_DIVIDER              (uint32)0x0000000CUL
        #define MCU_NO_BYPASS_SYSTEM_DIVIDER        (uint32)0x00000000UL
        #define MCU_CAN_HALF_SYSTEM_FREQ            (uint32)0x00010000UL
        #define MCU_CAN_SYSTEM_FREQ                 (uint32)0x00000000UL

        #define MCU_DIVIDE_SYSTEM_CLOCK_BY_2        (uint32)0x00000000UL
        #define MCU_DIVIDE_SYSTEM_CLOCK_BY_4        (uint32)0x00000004UL
        #define MCU_DIVIDE_SYSTEM_CLOCK_BY_8        (uint32)0x00000008UL
        #define MCU_DIVIDE_SYSTEM_CLOCK_BY_16       (uint32)0x0080000CUL


      #endif /* #if (IPV_SIU == IPV_SIU_00_02_07_03_5) */
#endif

/** @note   Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro,
See @ref Siu_Mcu_LLD_H_REF_2*/
#define MCU_ENG_CLOCK_SOURCE(x)             ((uint32)(((uint32)x)<<7))

#define MCU_EXT_BUS_TAP_SELECTED            (uint32)0x00000000UL
#define MCU_EXT_BUS_TAP_NOT_SELECTED        (uint32)0x00000008UL
/** @note   Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro,
See @ref Siu_Mcu_LLD_H_REF_2*/
#define MCU_ENG_CLOCK_DIV(x)                ((uint32)(((uint32)x)<<8))
/** @note   Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro,
See @ref Siu_Mcu_LLD_H_REF_2*/
#define MCU_EXT_BUS_DIV(x)                  ((uint32)(((uint32)x)<<0))

#define MCU_SW_SYS_RESET                    (uint32)0x80000000UL
#define MCU_SW_EXT_RESET                    (uint32)0x40000000UL
    #if (IPV_SIU == IPV_SIU_00_02_08_07) /* if Monaco */
#define MCU_CHKSTOP_RESET                    (uint32)0x00008000UL
    #endif

#ifdef IPV_SIU
    #if (IPV_SIU == IPV_SIU_00_02_07_03_5) /* if Fado */

        /* HALT */
        #define MCU_SIUHLT_TIMEOUT_NONE             (uint32)0x00000000UL
        #define MCU_SIUHLT0_NONE                    (uint32)0x00000000UL
        #define MCU_SIUHLT1_NONE                    (uint32)0x00000000UL
        #define MCU_SIUHLT0_ALL                     (uint32)0x037FFF3DUL
        #define MCU_SIUHLT1_ALL                     (uint32)0x18000F3CUL

        #define MCU_HALT_EMIOS200_CLOCK             (uint32)0x02000000UL
        #define MCU_KEEP_EMIOS200_CLOCK             (uint32)0x00000000UL
        #define MCU_HALT_PIT_CLOCK                  (uint32)0x01000000UL
        #define MCU_KEEP_PIT_CLOCK                  (uint32)0x00000000UL
        #define MCU_HALT_CTU_CLOCK                  (uint32)0x00400000UL
        #define MCU_KEEP_CTU_CLOCK                  (uint32)0x00000000UL
        #define MCU_HALT_FLEXCAN_F_CLOCK            (uint32)0x00200000UL
        #define MCU_KEEP_FLEXCAN_F_CLOCK            (uint32)0x00000000UL
        #define MCU_HALT_FLEXCAN_E_CLOCK            (uint32)0x00100000UL
        #define MCU_KEEP_FLEXCAN_E_CLOCK            (uint32)0x00000000UL
        #define MCU_HALT_FLEXCAN_D_CLOCK            (uint32)0x00080000UL
        #define MCU_KEEP_FLEXCAN_D_CLOCK            (uint32)0x00000000UL
        #define MCU_HALT_FLEXCAN_C_CLOCK            (uint32)0x00040000UL
        #define MCU_KEEP_FLEXCAN_C_CLOCK            (uint32)0x00000000UL
        #define MCU_HALT_FLEXCAN_B_CLOCK            (uint32)0x00020000UL
        #define MCU_KEEP_FLEXCAN_B_CLOCK            (uint32)0x00000000UL
        #define MCU_HALT_FLEXCAN_A_CLOCK            (uint32)0x00010000UL
        #define MCU_KEEP_FLEXCAN_A_CLOCK            (uint32)0x00000000UL
        #define MCU_HALT_ESCI_H_CLOCK               (uint32)0x00008000UL
        #define MCU_KEEP_ESCI_H_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_ESCI_G_CLOCK               (uint32)0x00004000UL
        #define MCU_KEEP_ESCI_G_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_ESCI_F_CLOCK               (uint32)0x00002000UL
        #define MCU_KEEP_ESCI_F_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_ESCI_E_CLOCK               (uint32)0x00001000UL
        #define MCU_KEEP_ESCI_E_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_ESCI_D_CLOCK               (uint32)0x00000800UL
        #define MCU_KEEP_ESCI_D_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_ESCI_C_CLOCK               (uint32)0x00000400UL
        #define MCU_KEEP_ESCI_C_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_ESCI_B_CLOCK               (uint32)0x00000200UL
        #define MCU_KEEP_ESCI_B_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_ESCI_A_CLOCK               (uint32)0x00000100UL
        #define MCU_KEEP_ESCI_A_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_DSPI_B_CLOCK               (uint32)0x00000020UL
        #define MCU_KEEP_DSPI_B_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_DSPI_A_CLOCK               (uint32)0x00000010UL
        #define MCU_KEEP_DSPI_A_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_I2C_B_CLOCK                (uint32)0x00000008UL
        #define MCU_KEEP_I2C_B_CLOCK                (uint32)0x00000000UL
        #define MCU_HALT_I2C_A_CLOCK                (uint32)0x00000004UL
        #define MCU_KEEP_I2C_A_CLOCK                (uint32)0x00000000UL
        #define MCU_HALT_ADC_CLOCK                  (uint32)0x00000001UL
        #define MCU_KEEP_ADC_CLOCK                  (uint32)0x00000000UL

        #define MCU_HALT_DMA_CLOCK                  (uint32)0x10000000UL
        #define MCU_KEEP_DMA_CLOCK                  (uint32)0x00000000UL
        #define MCU_HALT_NPC_CLOCK                  (uint32)0x08000000UL
        #define MCU_KEEP_NPC_CLOCK                  (uint32)0x00000000UL
        #define MCU_HALT_ESCI_M_CLOCK               (uint32)0x00000800UL
        #define MCU_KEEP_ESCI_M_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_ESCI_L_CLOCK               (uint32)0x00000400UL
        #define MCU_KEEP_ESCI_L_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_ESCI_K_CLOCK               (uint32)0x00000200UL
        #define MCU_KEEP_ESCI_K_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_ESCI_J_CLOCK               (uint32)0x00000100UL
        #define MCU_KEEP_ESCI_J_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_DSPI_D_CLOCK               (uint32)0x00000020UL
        #define MCU_KEEP_DSPI_D_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_DSPI_C_CLOCK               (uint32)0x00000010UL
        #define MCU_KEEP_DSPI_C_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_I2C_D_CLOCK                (uint32)0x00000008UL
        #define MCU_KEEP_I2C_D_CLOCK                (uint32)0x00000000UL
        #define MCU_HALT_I2C_C_CLOCK                (uint32)0x00000004UL
        #define MCU_KEEP_I2C_C_CLOCK                (uint32)0x00000000UL

    /* if Andorra 4M or Monaco */
    #elif ((IPV_SIU == IPV_SIU_00_02_11_00) || (IPV_SIU == IPV_SIU_00_02_08_07) )

        /** @brief HALT related defines */
        #define MCU_HALT_CPU_AND_PLATFORM_CLOCK     (uint32)0x80000000UL
        #define MCU_KEEP_CPU_AND_PLATFORM_CLOCK     (uint32)0x00000000UL
        #define MCU_HALT_NDEDI_CLOCK                (uint32)0x08000000UL
        #define MCU_KEEP_NDEDI_CLOCK                (uint32)0x00000000UL
        #define MCU_HALT_ETPU_CLOCK                 (uint32)0x04000000UL
        #define MCU_KEEP_ETPU_CLOCK                 (uint32)0x00000000UL
        #define MCU_HALT_NPC_CLOCK                  (uint32)0x02000000UL
        #define MCU_KEEP_NPC_CLOCK                  (uint32)0x00000000UL
        #define MCU_HALT_EBI_CLOCK                  (uint32)0x01000000UL
        #define MCU_KEEP_EBI_CLOCK                  (uint32)0x00000000UL
        #define MCU_HALT_ADC_CLOCK                  (uint32)0x00800000UL
        #define MCU_KEEP_ADC_CLOCK                  (uint32)0x00000000UL
        #define MCU_HALT_EMIOS_CLOCK                (uint32)0x00200000UL
        #define MCU_KEEP_EMIOS_CLOCK                (uint32)0x00000000UL
        #define MCU_HALT_DFILT_CLOCK                (uint32)0x00100000UL
        #define MCU_KEEP_DFILT_CLOCK                (uint32)0x00000000UL
        #define MCU_HALT_PIT_CLOCK                  (uint32)0x00040000UL
        #define MCU_KEEP_PIT_CLOCK                  (uint32)0x00000000UL
        #define MCU_HALT_FLEXCAN_C_CLOCK            (uint32)0x00004000UL
        #define MCU_KEEP_FLEXCAN_C_CLOCK            (uint32)0x00000000UL
        #define MCU_HALT_FLEXCAN_B_CLOCK            (uint32)0x00002000UL
        #define MCU_KEEP_FLEXCAN_B_CLOCK            (uint32)0x00000000UL
        #define MCU_HALT_FLEXCAN_A_CLOCK            (uint32)0x00001000UL
        #define MCU_KEEP_FLEXCAN_A_CLOCK            (uint32)0x00000000UL
        #define MCU_HALT_DSPI_D_CLOCK               (uint32)0x00000800UL
        #define MCU_KEEP_DSPI_D_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_DSPI_C_CLOCK               (uint32)0x00000400UL
        #define MCU_KEEP_DSPI_C_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_DSPI_B_CLOCK               (uint32)0x00000200UL
        #define MCU_KEEP_DSPI_B_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_ESCI_C_CLOCK               (uint32)0x00000004UL
        #define MCU_KEEP_ESCI_C_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_ESCI_B_CLOCK               (uint32)0x00000002UL
        #define MCU_KEEP_ESCI_B_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_ESCI_A_CLOCK               (uint32)0x00000001UL
        #define MCU_KEEP_ESCI_A_CLOCK               (uint32)0x00000000UL

    #else /* Mamba */

        /** @brief HALT related defines */
        #define MCU_HALT_CPU_AND_PLATFORM_CLOCK     (uint32)0x80000000UL
        #define MCU_KEEP_CPU_AND_PLATFORM_CLOCK     (uint32)0x00000000UL
        #define MCU_HALT_ETPU_A_CLOCK               (uint32)0x04000000UL
        #define MCU_KEEP_ETPU_A_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_NPC_CLOCK                  (uint32)0x02000000UL
        #define MCU_KEEP_NPC_CLOCK                  (uint32)0x00000000UL
        #define MCU_HALT_EBI_CLOCK                  (uint32)0x01000000UL
        #define MCU_KEEP_EBI_CLOCK                  (uint32)0x00000000UL
        #define MCU_HALT_EQADC_CLOCK                (uint32)0x00800000UL
        #define MCU_KEEP_EQADC_CLOCK                (uint32)0x00000000UL
        #define MCU_HALT_EMIOS_A_CLOCK              (uint32)0x00200000UL
        #define MCU_KEEP_EMIOS_A_CLOCK              (uint32)0x00000000UL
        #define MCU_HALT_DFILT_CLOCK                (uint32)0x00100000UL
        #define MCU_KEEP_DFILT_CLOCK                (uint32)0x00000000UL
        #define MCU_HALT_PIT_CLOCK                  (uint32)0x00040000UL
        #define MCU_KEEP_PIT_CLOCK                  (uint32)0x00000000UL
        #define MCU_HALT_FLEXCAN_D_CLOCK            (uint32)0x00008000UL
        #define MCU_KEEP_FLEXCAN_D_CLOCK            (uint32)0x00000000UL
        #define MCU_HALT_FLEXCAN_C_CLOCK            (uint32)0x00004000UL
        #define MCU_KEEP_FLEXCAN_C_CLOCK            (uint32)0x00000000UL
        #define MCU_HALT_FLEXCAN_B_CLOCK            (uint32)0x00002000UL
        #define MCU_KEEP_FLEXCAN_B_CLOCK            (uint32)0x00000000UL
        #define MCU_HALT_FLEXCAN_A_CLOCK            (uint32)0x00001000UL
        #define MCU_KEEP_FLEXCAN_A_CLOCK            (uint32)0x00000000UL
        #define MCU_HALT_DSPI_D_CLOCK               (uint32)0x00000800UL
        #define MCU_KEEP_DSPI_D_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_DSPI_C_CLOCK               (uint32)0x00000400UL
        #define MCU_KEEP_DSPI_C_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_DSPI_B_CLOCK               (uint32)0x00000200UL
        #define MCU_KEEP_DSPI_B_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_DSPI_A_CLOCK               (uint32)0x00000100UL
        #define MCU_KEEP_DSPI_A_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_ESCI_C_CLOCK               (uint32)0x00000004UL
        #define MCU_KEEP_ESCI_C_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_ESCI_B_CLOCK               (uint32)0x00000002UL
        #define MCU_KEEP_ESCI_B_CLOCK               (uint32)0x00000000UL
        #define MCU_HALT_ESCI_A_CLOCK               (uint32)0x00000001UL
        #define MCU_KEEP_ESCI_A_CLOCK               (uint32)0x00000000UL

      #endif /* #if (IPV_SIU == IPV_SIU_00_02_07_03_5) */
#endif


/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

#define MCU_START_CONFIG_DATA_UNSPECIFIED
/** @note   Violates MISRA 2004 Advisory Rule 19.15, Repeated include files,
See @ref Siu_Mcu_LLD_H_REF_1*/
/*lint -save -e537*/
#include "MemMap.h"
/*lint -restore*/

/* Check if header file and MemMap.h file are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
#if ((SIU_MCU_LLD_AR_MAJOR_VERSION != MEMMAP_AR_MAJOR_VERSION) || \
(SIU_MCU_LLD_AR_MINOR_VERSION != MEMMAP_AR_MINOR_VERSION) || \
(SIU_MCU_LLD_AR_PATCH_VERSION != MEMMAP_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of SIU_Mcu_LLD.h and MemMap.h are different"
#endif
#endif

#define MCU_STOP_CONFIG_DATA_UNSPECIFIED
/** @note   Violates MISRA 2004 Advisory Rule 19.15, Repeated include files,
See @ref Siu_Mcu_LLD_H_REF_1*/
/*lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
#define MCU_START_SEC_CODE
/** @note   Violates MISRA 2004 Advisory Rule 19.15, Repeated include files,
See @ref Siu_Mcu_LLD_H_REF_1*/
/*lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

/**
@brief   This function retruns the reset reason.
@details The function reads the reset reason from hardware and returns the reason.

@return RawReset reset reason

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers MCU052, MCU005
@remarks Implements DMCU04000
*/
    extern FUNC(Mcu_ResetType, MCU_CODE) Mcu_SIU_GetResetReason(VAR(void, MCU_VAR));

/**
@brief   This function returns the raw reset value.
@details This function reads the reset raw value from the hardware register.

@return         RawResetReg raw reset reason

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers MCU006, MCU135
@remarks Implements DMCU04000
*/
    extern FUNC(Mcu_RawResetType, MCU_CODE) Mcu_SIU_GetResetRawValue(VAR(void, MCU_VAR));

/**
@brief   This function performs a microcontroller reset.
@details This function performs a microcontroller reset by using the hardware feature of the
         microcontroller.

@param[in]     Mcu_Cfg_Ptr

@return     None
@retval     None

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers MCU055, MCU143, MCU144
@remarks Implements DMCU04000
*/
#if MCU_PERFORM_RESET_API == STD_ON
    extern FUNC(void, MCU_CODE) Mcu_SIU_PerformReset( \
        P2CONST (Mcu_ConfigType, AUTOMATIC, MCU_APPL_DATA) Mcu_Cfg_Ptr);
#endif

/**
   @brief   This function initializes the ExternalClock Register
   @details The ExternalClock Register is initialised with configured External Clock  parameters

@param[in]     ClockPtr      Pointer to clock configuration structure

@return void

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers MCU137
@remarks Implements DMCU04000
*/
    extern FUNC(void, MCU_CODE) Mcu_SIU_Init_ExternalClock( \
        P2CONST(Mcu_ClockConfigType, AUTOMATIC, MCU_APPL_DATA) ClockPtr);

/**
  @brief   This function initializes the System Clock Register
  @details The System Clock Register is initialised with the configured system clock parameters

@param[in]     ClockPtr      Pointer to clock configuration structure

@return void

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers MCU137
@remarks Implements DMCU04000
*/
    extern FUNC(void, MCU_CODE) Mcu_SIU_Init_SystemClock( \
        P2CONST(Mcu_ClockConfigType, AUTOMATIC, MCU_APPL_DATA) ClockPtr);

/**
@brief   This function initializes the Halt Register
@details The Halt Register is initialised with configured Halt bit parameters

@param[in]     ModePtr      Pointer to mode configuration structure

@return void

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers MCU147
@remarks Implements DMCU04000
*/
    extern FUNC(void, MCU_CODE) Mcu_SIU_Init_Halt( \
        P2CONST(Mcu_ModeConfigType, AUTOMATIC, MCU_APPL_DATA) ModePtr);

/**
@brief   This function Halts all the periferals
@details This function will set the system clock to 16MHz IRC and will
         halt all preiferals used prior to entering the sleep mode

@param[in]     timeout - timeout for the while loop waitng for the periferals to halt

@return void

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers MCU147
@remarks Implements DMCU04000
*/
    extern FUNC(void, AUTOMATIC) Mcu_SIU_Halt_All(VAR(uint32, AUTOMATIC) timeout);

#define MCU_STOP_SEC_CODE
/** @note   Violates MISRA 2004 Advisory Rule 19.15,Repeated include files,
 See @ref Siu_Mcu_LLD_H_REF_1*/
/*lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif
#endif                                            /* _SIU_MCU_LLD_H_*/
