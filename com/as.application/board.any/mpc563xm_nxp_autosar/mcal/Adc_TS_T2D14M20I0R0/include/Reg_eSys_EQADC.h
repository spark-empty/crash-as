/**
    @file    Reg_eSys_EQADC.h
    @version 2.0.0

    @brief   AUTOSAR Adc - module register and macro definitions.
    @details Adc module registers, and macrodefinitions used to manipulate the module registers.

    Project AUTOSAR 3.0 MCAL
    Patform PA
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

@section Reg_eSys_ADCDig_h_REF_1
Violates MISRA 2004 Advisory Rul e 19.7, use of function like macro. This violation is due to
function like macros defined for register operations. Function like macros are used to reduce code
complexity.
*/

#ifndef REG_eSys_EQADC_H
#define REG_eSys_EQADC_H

#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Reg_eSys.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/**
@{
@brief   Header file version information
@remarks Covers BSW00374, BSW00379, BSW00318, ADC030
*/
#define EQADC_VENDOR_ID_REG           43
#define EQADC_AR_MAJOR_VERSION_REG    3
#define EQADC_AR_MINOR_VERSION_REG    0
#define EQADC_AR_PATCH_VERSION_REG    0
#define EQADC_SW_MAJOR_VERSION_REG    2
#define EQADC_SW_MINOR_VERSION_REG    0
#define EQADC_SW_PATCH_VERSION_REG    0
/**@}*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/
/**
@brief IP version EQADC.01.00.07.00 for Mamba
@{
*/
#define IPV_EQADC_01_00_07_00 1000700UL
/**@}*/

/**
@brief IP version EQADC.01.00.11.01 for Andorra2M and Andorra4M
@{
*/
#define IPV_EQADC_01_00_11_01 1001101UL
/**@}*/

/**
@brief IP version EQADC.01.00.10.00 for Monaco1.5M
@{
*/
#define IPV_EQADC_01_00_10_00 1001000UL
/**@}*/
/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/


/**
@{
@note Violates MISRA 2004 Advisory Rule 19.7, use of function like macro
- See @ref Reg_eSys_ADCDig_h_REF_1
*/
/*lint -save -e961 */
/**
 * @brief EQADC Register address
 */
#define ADC_ADDRESS(EQADCAorB)               (EQADCA_BASEADDR + ((uint32)EQADCAorB<<(uint32)14))

/**
 * @brief EQADC Module Configuration Register
 */
#define EQADC_MCR(EQADCAorB)                 (ADC_ADDRESS(EQADCAorB)+(uint32)0x0000UL)

/* if Andorra2M and Andorra4M or Monaco 1.5M*/
#if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
/**
 * @brief EQADC Test Register
 */
#define EQADC_TST(EQADCAorB)                 (ADC_ADDRESS(EQADCAorB)+(uint32)0x0004UL)
/**
 * @brief EQADC Null Message Send Format Register
 */
#define EQADC_NMSFRTST(EQADCAorB)            (ADC_ADDRESS(EQADCAorB)+(uint32)0x0008UL)
#else
/* Reserved - 0x0004 and 0x0008 */
#endif /* (IPV_EQADC == IPV_EQADC_01_00_11_01)  || (IPV_EQADC == IPV_EQADC_01_00_10_00) */

/**
 * @brief EQADC External Trigger Digital Filter Register
 */
#define EQADC_ETDFR(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x000CUL)

/**
@brief EQADC CFIFO Push Register (0-5)
@{
*/
#define EQADC_CFPR0(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0010UL)
#define EQADC_CFPR1(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0014UL)
#define EQADC_CFPR2(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0018UL)
#define EQADC_CFPR3(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x001CUL)
#define EQADC_CFPR4(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0020UL)
#define EQADC_CFPR5(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0024UL)
/**@}*/

/* Reserved - 0x0028 and 0x002C */

/**
@brief EQADC Result FIFO Pop Register (0-5)
@{
*/
#define EQADC_RFPR0(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0030UL)
#define EQADC_RFPR1(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0034UL)
#define EQADC_RFPR2(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0038UL)
#define EQADC_RFPR3(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x003CUL)
#define EQADC_RFPR4(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0040UL)
#define EQADC_RFPR5(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0044UL)
/**@}*/

/* Reserved - 0x0048 and 0x004C */

/**
@brief EQADC CFIFO Control Register (0-5)
@{
*/
#define EQADC_CFCR0(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0050UL)
#define EQADC_CFCR1(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0052UL)
#define EQADC_CFCR2(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0054UL)
#define EQADC_CFCR3(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0056UL)
#define EQADC_CFCR4(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0058UL)
#define EQADC_CFCR5(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x005AUL)
/**@}*/

/* Reserved - 0x005C */

/**
@brief EQADC Interrupt and DMA Control Register (0-5)
@{
*/
#define EQADC_IDCR0(EQADCAorB)             (ADC_ADDRESS(EQADCAorB)+0x0060UL)
#define EQADC_IDCR1(EQADCAorB)             (ADC_ADDRESS(EQADCAorB)+0x0062UL)
#define EQADC_IDCR2(EQADCAorB)             (ADC_ADDRESS(EQADCAorB)+0x0064UL)
#define EQADC_IDCR3(EQADCAorB)             (ADC_ADDRESS(EQADCAorB)+0x0066UL)
#define EQADC_IDCR4(EQADCAorB)             (ADC_ADDRESS(EQADCAorB)+0x0068UL)
#define EQADC_IDCR5(EQADCAorB)             (ADC_ADDRESS(EQADCAorB)+0x006AUL)
/**@}*/

/* Reserved - 0x006C */

/**
@brief EQADC FIFO and Interrupt Status Register (0-5)
@{
*/
#define EQADC_FISR0(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0070UL)
#define EQADC_FISR1(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0074UL)
#define EQADC_FISR2(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0078UL)
#define EQADC_FISR3(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x007CUL)
#define EQADC_FISR4(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0080UL)
#define EQADC_FISR5(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0084UL)
/**@}*/

/* Reserved - 0x0088 and 0x008C */

/**
@brief EQADC CFIFO Transfer Counter Register (0-2)
@{
*/
#define EQADC_CFTCR0(EQADCAorB)              (ADC_ADDRESS(EQADCAorB)+0x0090UL)
#define EQADC_CFTCR1(EQADCAorB)              (ADC_ADDRESS(EQADCAorB)+0x0092UL)
#define EQADC_CFTCR2(EQADCAorB)              (ADC_ADDRESS(EQADCAorB)+0x0094UL)
#define EQADC_CFTCR3(EQADCAorB)              (ADC_ADDRESS(EQADCAorB)+0x0096UL)
#define EQADC_CFTCR4(EQADCAorB)              (ADC_ADDRESS(EQADCAorB)+0x0098UL)
#define EQADC_CFTCR5(EQADCAorB)              (ADC_ADDRESS(EQADCAorB)+0x009AUL)
/**@}*/

/* Reserved - 0x009C */

/**
@brief EQADC CFIFO Status Snapshot Register (0-1)
@{
*/
#define EQADC_CFSSR0(EQADCAorB)              (ADC_ADDRESS(EQADCAorB)+0x00A0UL)
#define EQADC_CFSSR1(EQADCAorB)              (ADC_ADDRESS(EQADCAorB)+0x00A4UL)
/**@}*/

/* if Andorra2M and Andorra4M or Monaco 1.5M */
#if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
/**
  * @brief EQADC CFIFO Status Snapshot Register 2
 */
#define EQADC_CFSSR2(EQADCAorB)              (ADC_ADDRESS(EQADCAorB)+0x00A8UL)
#else
/* Reserved - 0x00A8 */
#endif /* (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) */

/**
 * @brief EQADC CFIFO Status Register
 */
#define EQADC_CFSR(EQADCAorB)                (ADC_ADDRESS(EQADCAorB)+0x00ACUL)

/* if Andorra2M and Andorra4M or Monaco 1.5M */
#if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
/* Reserved - 0x00B0 */
/**
 * @brief EQADC Synchronous Serial Interface Control Register
 */
#define EQADC_SSICR(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x00B4UL)
/**
 * @brief EQADC Synchronous Serial Interface Receive Data Register
 */
#define EQADC_SSIRDR(EQADCAorB)              (ADC_ADDRESS(EQADCAorB)+0x00B8UL)

/* if Monaco 1.5M */
#if (IPV_EQADC == IPV_EQADC_01_00_10_00)
/* Reserved - 0x00BC to 0x00CC */
/**
 * @brief EQADC STAC Client Configuration Register
 */
#define EQADC_REDLCCR(EQADCAorB)              (ADC_ADDRESS(EQADCAorB)+0x00D0UL)
/* Reserved - 0x00D4 to 0x00FC */
#else
/* Reserved - 0x00BC to 0x00FC */
#endif /* (IPV_EQADC == IPV_EQADC_01_00_10_00) */
#else
/* Reserved - 0x00B0 to 0x00FC */
#endif /* (IPV_EQADC != IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) */

/**
@brief EQADC CFIFO0 Registers (0-3)
@{
*/
#define EQADC_CF0R0(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0100UL)
#define EQADC_CF0R1(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0104UL)
#define EQADC_CF0R2(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0108UL)
#define EQADC_CF0R3(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x010CUL)
/**@}*/

/**
@brief EQADC CFIFO0 Extension Registers (0-3)
@{
*/
#define EQADC_CF0ER0(EQADCAorB)              (ADC_ADDRESS(EQADCAorB)+0x0110UL)
#define EQADC_CF0ER1(EQADCAorB)              (ADC_ADDRESS(EQADCAorB)+0x0114UL)
#define EQADC_CF0ER2(EQADCAorB)              (ADC_ADDRESS(EQADCAorB)+0x0118UL)
#define EQADC_CF0ER3(EQADCAorB)              (ADC_ADDRESS(EQADCAorB)+0x011CUL)
/**@}*/

/* Reserved - 0x0120 and 0x013C */

/**
@brief EQADC CFIFO1 Registers (0-3)
@{
*/
#define EQADC_CF1R0(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0140UL)
#define EQADC_CF1R1(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0144UL)
#define EQADC_CF1R2(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0148UL)
#define EQADC_CF1R3(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x014CUL)
/**@}*/

/* Reserved - 0x0150 and 0x017C */

/**
@brief EQADC CFIFO2 Registers (0-3)
@{
*/
#define EQADC_CF2R0(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0180UL)
#define EQADC_CF2R1(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0184UL)
#define EQADC_CF2R2(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0188UL)
#define EQADC_CF2R3(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x018CUL)
/**@}*/

/* Reserved - 0x0190 and 0x01BC */

/**
@brief EQADC CFIFO3 Registers (0-3)
@{
*/
#define EQADC_CF3R0(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x01C0UL)
#define EQADC_CF3R1(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x01C4UL)
#define EQADC_CF3R2(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x01C8UL)
#define EQADC_CF3R3(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x01CCUL)
/**@}*/

/* Reserved - 0x01D0 and 0x01FC */

/**
@brief EQADC CFIFO4 Registers (0-3)
@{
*/
#define EQADC_CF4R0(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0200UL)
#define EQADC_CF4R1(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0204UL)
#define EQADC_CF4R2(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0208UL)
#define EQADC_CF4R3(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x020CUL)
/**@}*/

/* Reserved - 0x0210 and 0x023C */

/**
@brief EQADC CFIFO5 Registers (0-3)
@{
*/
#define EQADC_CF5R0(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0240UL)
#define EQADC_CF5R1(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0244UL)
#define EQADC_CF5R2(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0248UL)
#define EQADC_CF5R3(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x024CUL)
/**@}*/

/* Reserved - 0x0250 and 0x02FC */

/**
@brief EQADC RFIFO0 Registers (0-3)
@{
*/
#define EQADC_RF0R0(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0300UL)
#define EQADC_RF0R1(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0304UL)
#define EQADC_RF0R2(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0308UL)
#define EQADC_RF0R3(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x030CUL)
/**@}*/

/* Reserved - 0x0310 and 0x033C */

/**
@brief EQADC RFIFO1 Registers (0-3)
@{
*/
#define EQADC_RF1R0(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0340UL)
#define EQADC_RF1R1(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0344UL)
#define EQADC_RF1R2(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0348UL)
#define EQADC_RF1R3(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x034CUL)
/**@}*/

/* Reserved - 0x0350 and 0x037C */

/**
@brief EQADC RFIFO2 Registers (0-3)
@{
*/
#define EQADC_RF2R0(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0380UL)
#define EQADC_RF2R1(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0384UL)
#define EQADC_RF2R2(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0388UL)
#define EQADC_RF2R3(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x038CUL)
/**@}*/

/* Reserved - 0x0390 and 0x03BC */

/**
@brief EQADC RFIFO3 Registers (0-3)
@{
*/
#define EQADC_RF3R0(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x03C0UL)
#define EQADC_RF3R1(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x03C4UL)
#define EQADC_RF3R2(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x03C8UL)
#define EQADC_RF3R3(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x03CCUL)
/**@}*/

/* Reserved - 0x03D0 and 0x03FC */

/**
@brief EQADC RFIFO4 Registers (0-3)
@{
*/
#define EQADC_RF4R0(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0400UL)
#define EQADC_RF4R1(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0404UL)
#define EQADC_RF4R2(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0408UL)
#define EQADC_RF4R3(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x040CUL)
/**@}*/

/* Reserved - 0x0410 and 0x043C */

/**
@brief EQADC RFIFO5 Registers (0-3)
@{
*/
#define EQADC_RF5R0(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0440UL)
#define EQADC_RF5R1(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0444UL)
#define EQADC_RF5R2(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x0448UL)
#define EQADC_RF5R3(EQADCAorB)               (ADC_ADDRESS(EQADCAorB)+0x044CUL)
/**@}*/

/* Reserved - 0x0450 and 0x07FC */

/* if Andorra2M and Andorra4M or Monaco 1.5M */
#if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
/**
@brief Defines for RFIFO channel numbers for DMA
@{
*/
#define EQADC_DMAeQADCA_FISR0_RFDF0        (0x01U)
#define EQADC_DMAeQADCA_FISR1_RFDF1        (0x03U)
#define EQADC_DMAeQADCA_FISR2_RFDF2        (0x05U)
#define EQADC_DMAeQADCA_FISR3_RFDF3        (0x07U)
#define EQADC_DMAeQADCA_FISR4_RFDF4        (0x09U)
#define EQADC_DMAeQADCA_FISR5_RFDF5        (0x0BU)
#else
#define EQADC_DMAeQADCA_FISR0_RFDF0        (0x01U)
#define EQADC_DMAeQADCA_FISR1_RFDF1        (0x03U)
#define EQADC_DMAeQADCA_FISR2_RFDF2        (0x05U)
#define EQADC_DMAeQADCA_FISR3_RFDF3        (0x07U)
#define EQADC_DMAeQADCA_FISR4_RFDF4        (0x09U)
#define EQADC_DMAeQADCA_FISR5_RFDF5        (0x0BU)
#define EQADC_DMAeQADCB_FISR6_RFDF0        (0x01U)
#define EQADC_DMAeQADCB_FISR7_RFDF1        (0x03U)
#define EQADC_DMAeQADCB_FISR8_RFDF2        (0x05U)
#define EQADC_DMAeQADCB_FISR9_RFDF3        (0x07U)
#define EQADC_DMAeQADCB_FISR10_RFDF4    (0x09U)
#define EQADC_DMAeQADCB_FISR11_RFDF5    (0x0BU)
/**@}*/
#endif /* (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)*/

/*lint -restore */
/**@}*/

/* EQADC REGISTERS BITS */

/*---------------------------------------------------------------------------------------------------*/
/*                             EQADC Module Configuration Register (EQADC_MCR)                       */
/*---------------------------------------------------------------------------------------------------*/
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT 9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     | */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/*                                                                                                   */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT16|BIT17|BIT18|BIT19|BIT20|BIT21|BIT22|BIT23|BIT24|BIT25|BIT26|BIT27|BIT28|BIT29|BIT30|BIT31| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* if Andorra2M and Andorra4M or  Monaco 1.5M*/
#if (IPV_EQADC == IPV_EQADC_01_00_11_01)  || (IPV_EQADC == IPV_EQADC_01_00_10_00)
/* |     |     |     |     |     |     |     |     |ICEA0|ICEA1|     |<--ESSIE-->|     |<---DBG--->| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
#else
/* |     |     |     |     |     |     |     |     |ICEA0|ICEA1|     |     |     |     |<---DBG--->| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
#endif /* (IPV_EQADC == IPV_EQADC_01_00_11_01)  || (IPV_EQADC == IPV_EQADC_01_00_10_00) */

#define EQADC_MCR_ICEA0                ((uint32)0x00000080UL)
#define EQADC_MCR_ICEA1                ((uint32)0x00000040UL)
#define EQADC_MCR_DBG                ((uint32)0x00000003UL)
/* if Andorra2M and Andorra4M or  Monaco 1.5M*/
#if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
#define EQADC_MCR_ESSIE                ((uint32)0x00000018UL)
#endif /* (IPV_EQADC == IPV_EQADC_01_00_11_01)  || (IPV_EQADC == IPV_EQADC_01_00_10_00) */

/* if Andorra2M and Andorra4M or  Monaco 1.5M*/
#if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
/*---------------------------------------------------------------------------------------------------*/
/*                            EQADC Null Message Send Format Register (EQADC_NMSFR)                     */
/*---------------------------------------------------------------------------------------------------*/
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT 9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |     |     |     |     |     |     |<--------------------------NMF-----------------------------| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/*                                                                                                   */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT16|BIT17|BIT18|BIT19|BIT20|BIT21|BIT22|BIT23|BIT24|BIT25|BIT26|BIT27|BIT28|BIT29|BIT30|BIT31| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |------------------------------------------------NMF------------------------------------------->| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */

#define EQADC_NMSFR_NMF                ((uint32)0x03FFFFFFUL)
#endif /* (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00) */

/*---------------------------------------------------------------------------------------------------*/
/*                    EQADC External Trigger Digital Filter Register (EQADC_ETDFR)                   */
/*---------------------------------------------------------------------------------------------------*/
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT 9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     | */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/*                                                                                                   */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT16|BIT17|BIT18|BIT19|BIT20|BIT21|BIT22|BIT23|BIT24|BIT25|BIT26|BIT27|BIT28|BIT29|BIT30|BIT31| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |     |     |     |     |     |     |     |     |     |     |     |     |<-------- DFL -------->| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */

#define EQADC_ETDFR_DFL                    ((uint32)0x0000000FUL)

/*---------------------------------------------------------------------------------------------------*/
/*                             EQADC CFIFO Push Register x (EQADC_CFPRx)                             */
/*---------------------------------------------------------------------------------------------------*/
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT 9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |<------------------------------------------CF_PUSHx------------------------------------------->| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/*                                                                                                   */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT16|BIT17|BIT18|BIT19|BIT20|BIT21|BIT22|BIT23|BIT24|BIT25|BIT26|BIT27|BIT28|BIT29|BIT30|BIT31| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |<------------------------------------------CF_PUSHx------------------------------------------->| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */

/*---------------------------------------------------------------------------------------------------*/
/*                             EQADC RFIFO Pop Register x (EQADC_RFPRx)                              */
/*---------------------------------------------------------------------------------------------------*/
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT 9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     | */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/*                                                                                                   */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT16|BIT17|BIT18|BIT19|BIT20|BIT21|BIT22|BIT23|BIT24|BIT25|BIT26|BIT27|BIT28|BIT29|BIT30|BIT31| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |<-------------------------------------------RF_POPx------------------------------------------->| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */

#define EQADC_RFPR_RF_POP          ((uint32)0x0000FFFFUL)

/*----------------------------------------------------------------------------------------------------*/
/*                             EQADC CFIFO Control Register 0 (EQADC_CFCR0)                           */
/*----------------------------------------------------------------------------------------------------*/
/* |-----|-----|-----|-----|-----|-----|------|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6 |BIT 7|BIT 8|BIT 9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15| */
/* |-----|-----|-----|-----|-----|-----|------|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |     |     |     |CFEE0|STRME0|SSE0|CFINV0|     |<---------MODE0------->| <-------AMODE0------->| */
/* |-----|-----|-----|-----|-----|-----|------|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/*                                                                                                    */
/* |-----|-----|-----|-----|-----|-----|------|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT16|BIT17|BIT18|BIT19|BIT20|BIT21|BIT22 |BIT23|BIT24|BIT25|BIT26|BIT27|BIT28|BIT29|BIT30|BIT31| */
/* |-----|-----|-----|-----|-----|-----|------|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |     |     |     |     |     |SSE1 |CFINV1|     |<---------MODE1------->|     |     |     |     | */
/* |-----|-----|-----|-----|-----|-----|------|-----|-----|-----|-----|-----|-----|-----|-----|-----| */

/*----------------------------------------------------------------------------------------------------*/
/*                             EQADC CFIFO Control Register 1 (EQADC_CFCR1)                           */
/*----------------------------------------------------------------------------------------------------*/
/* |-----|-----|-----|-----|-----|-----|------|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6 |BIT 7|BIT 8|BIT 9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15| */
/* |-----|-----|-----|-----|-----|-----|------|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |     |     |     |     |     |SSE2 |CFINV2|     |<---------MODE2------->|     |     |     |     | */
/* |-----|-----|-----|-----|-----|-----|------|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/*                                                                                                    */
/* |-----|-----|-----|-----|-----|-----|------|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT16|BIT17|BIT18|BIT19|BIT20|BIT21|BIT22 |BIT23|BIT24|BIT25|BIT26|BIT27|BIT28|BIT29|BIT30|BIT31| */
/* |-----|-----|-----|-----|-----|-----|------|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |     |     |     |       |   |SSE3 |CFINV3|     |<---------MODE3------->|     |     |     |     | */
/* |-----|-----|-----|-----|-----|-----|------|-----|-----|-----|-----|-----|-----|-----|-----|-----| */

/*----------------------------------------------------------------------------------------------------*/
/*                             EQADC CFIFO Control Register 2 (EQADC_CFCR2)                           */
/*----------------------------------------------------------------------------------------------------*/
/* |-----|-----|-----|-----|-----|-----|------|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6 |BIT 7|BIT 8|BIT 9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15| */
/* |-----|-----|-----|-----|-----|-----|------|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |     |     |     |     |     |SSE4 |CFINV4|     |<---------MODE4------->|     |     |     |     | */
/* |-----|-----|-----|-----|-----|-----|------|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/*                                                                                                    */
/* |-----|-----|-----|-----|-----|-----|------|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT16|BIT17|BIT18|BIT19|BIT20|BIT21|BIT22 |BIT23|BIT24|BIT25|BIT26|BIT27|BIT28|BIT29|BIT30|BIT31| */
/* |-----|-----|-----|-----|-----|-----|------|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |     |     |     |     |     |SSE5 |CFINV5|     |<---------MODE5------->|     |     |     |     | */
/* |-----|-----|-----|-----|-----|-----|------|-----|-----|-----|-----|-----|-----|-----|-----|-----| */

#define EQADC_CFCR0_CFEE0              ((uint16)0x1000UL)
#define EQADC_CFCR0_STRME0             ((uint16)0x0800UL)
#define EQADC_CFCR0_AMODE0             ((uint16)0x000FUL)

#define EQADC_CFCR_SSE                 ((uint16)0x0400UL)
#define EQADC_CFCR_CFINV               ((uint16)0x0200UL)
#define EQADC_CFCR_MODE                ((uint16)0x00F0UL)

#define EQADC_CFCR_MODE_DISABLED       ((uint16)0x0000UL)   /* 0b0000 - Disabled */
#define EQADC_CFCR_MODE_SWSS           ((uint16)0x0010UL)   /* 0b0001 - Software trigger, single scan */
#define EQADC_CFCR_MODE_HWSS_LoL       ((uint16)0x0020UL)   /* 0b0010 - Low level gated external trigger, single scan */
#define EQADC_CFCR_MODE_HWSS_HiL       ((uint16)0x0030UL)   /* 0b0011 - High level gated external trigger, single scan */
#define EQADC_CFCR_MODE_HWSS_FEd       ((uint16)0x0040UL)   /* 0b0100 - Falling edge external trigger, single scan */
#define EQADC_CFCR_MODE_HWSS_REd       ((uint16)0x0050UL)   /* 0b0101 - Rising edge external trigger, single scan */
#define EQADC_CFCR_MODE_HWSS_BEd       ((uint16)0x0060UL)   /* 0b0110 - Falling or rising edge external trigger, single scan */
                                                            /* 0b0111 - 0b1000 - Reserved */
#define EQADC_CFCR_MODE_SWCS           ((uint16)0x0090UL)   /* 0b1001 - Software trigger, continuous scan */
#define EQADC_CFCR_MODE_HWCS_LoL       ((uint16)0x00A0UL)   /* 0b1010 - Low level gated external trigger, continuous scan */
#define EQADC_CFCR_MODE_HWCS_HiL       ((uint16)0x00B0UL)   /* 0b1011 - High level gated external trigger, continuous scan */
#define EQADC_CFCR_MODE_HWCS_FEd       ((uint16)0x00C0UL)   /* 0b1100 - Falling edge external trigger, continuous scan */
#define EQADC_CFCR_MODE_HWCS_REd       ((uint16)0x00D0UL)   /* 0b1101 - Rising edge external trigger, continuous scan */
#define EQADC_CFCR_MODE_HWCS_BEd       ((uint16)0x00E0UL)   /* 0b1110 - Falling or rising edge external trigger, continuous scan */
                                                            /* 0b1110 - Reserved */
/*-------------------------------------------------------------------------------------------------------*/
/*                             EQADC Interrupt and DMA Control Register x (EQADC_IDCRx)                  */
/*-------------------------------------------------------------------------------------------------------*/
/* |-----|------|-----|------|------|-----|-----|-----|-----|-----|-----|-----|------|-----|-----|-----| */
/* |BIT 0|BIT 1 |BIT 2|BIT 3 |BIT 4 |BIT 5|BIT 6|BIT 7|BIT 8|BIT 9|BIT10|BIT11|BIT12 |BIT13|BIT14|BIT15| */
/* |-----|------|-----|------|------|-----|-----|-----|-----|-----|-----|-----|------|-----|-----|-----| */
/* |NCIEx|TORIEx|PIEx |EOQIEx|CFUIEx|     |CFFEx|CFFSx|     |     |     |     |RFOIEx|     |RFDEx|RFDSx| */
/* |-----|------|-----|------|------|-----|-----|-----|-----|-----|-----|-----|------|-----|-----|-----| */
/*                                                                                                       */
/* |-----|------|-----|------|------|-----|-----|-----|-----|-----|-----|-----|------|-----|-----|-----| */
/* |BIT16|BIT17 |BIT18|BIT19 |BIT20 |BIT21|BIT22|BIT23|BIT24|BIT25|BIT26|BIT27|BIT28 |BIT29|BIT30|BIT31| */
/* |-----|------|-----|------|------|-----|-----|-----|-----|-----|-----|-----|------|-----|-----|-----| */
/* |NCIEx|TORIEx|PIEx |EOQIEx|CFUIEx|     |CFFEx|CFFSx|     |     |     |     |RFOIEx|     |RFDEx|RFDSx| */
/* |-----|------|-----|------|------|-----|-----|-----|-----|-----|-----|-----|------|-----|-----|-----| */

#define EQADC_IDCR_NCIE                 ((uint16)0x8000UL)
#define EQADC_IDCR_TORIE                ((uint16)0x4000UL)
#define EQADC_IDCR_PIE                  ((uint16)0x2000UL)
#define EQADC_IDCR_EOQIE                ((uint16)0x1000UL)
#define EQADC_IDCR_CFUIE                ((uint16)0x0800UL)
#define EQADC_IDCR_CFFE                 ((uint16)0x0200UL)
#define EQADC_IDCR_CFFS                 ((uint16)0x0100UL)
#define EQADC_IDCR_RFOIE                ((uint16)0x0008UL)
#define EQADC_IDCR_RFDE                 ((uint16)0x0002UL)
#define EQADC_IDCR_RFDS                 ((uint16)0x0001UL)

/*---------------------------------------------------------------------------------------------------*/
/*                             EQADC FIFO and Interrupt Status Register x (EQADC_FISRx)              */
/*---------------------------------------------------------------------------------------------------*/
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT 9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |NCFx |TORFx|PFx  |EOQFx|CFUFx|SSSx |CFFFx|     |     |     |     |     |RFOFx|     |RFDFx|     | */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/*                                                                                                   */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT16|BIT17|BIT18|BIT19|BIT20|BIT21|BIT22|BIT23|BIT24|BIT25|BIT26|BIT27|BIT28|BIT29|BIT30|BIT31| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |<--------CFCTRx------->|<--------TNXTPTRx----->|<--------RFCTRx------->|<-------POPNXTPTRx---->| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */

#define EQADC_FISRx_CLEAR_MASK             ((uint32)0xF80A0000UL)

#define EQADC_FISRx_NCF                    ((uint32)0x80000000UL)
#define EQADC_FISRx_TORF                   ((uint32)0x40000000UL)
#define EQADC_FISRx_PF                     ((uint32)0x20000000UL)
#define EQADC_FISRx_EOQF                   ((uint32)0x10000000UL)
#define EQADC_FISRx_CFUF                   ((uint32)0x08000000UL)
#define EQADC_FISRx_SSS                    ((uint32)0x04000000UL)
#define EQADC_FISRx_CFFF                   ((uint32)0x02000000UL)
#define EQADC_FISRx_RFOF                   ((uint32)0x00080000UL)
#define EQADC_FISRx_RFDF                   ((uint32)0x00020000UL)
#define EQADC_FISRx_CFCTR                  ((uint32)0x0000F000UL)
#define EQADC_FISRx_TNXTPTR                ((uint32)0x00000F00UL)
#define EQADC_FISRx_RFCTR                  ((uint32)0x000000F0UL)
#define EQADC_FISRx_POPNXTPTR              ((uint32)0x0000000FUL)

#define EQADC_REG32_RESET_VALUE            ((uint32)0x00000000UL)
#define EQADC_REG16_RESET_VALUE            ((uint16)0x0000UL)
#define EQADC_REG8_RESET_VALUE             ((uint8)0x00UL)
#define EQADC_CFSSRx_CLEAR_MASK            ((uint32)0x00007800UL)
#define RESULT_FIFO_0                      ((uint32)0x0000000UL)
#define RESULT_FIFO_1                      ((uint32)0x0100000UL)
#define RESULT_FIFO_2                      ((uint32)0x0200000UL)
#define RESULT_FIFO_3                      ((uint32)0x0300000UL)
#define RESULT_FIFO_4                      ((uint32)0x0400000UL)
#define RESULT_FIFO_5                      ((uint32)0x0500000UL)
#define RESULT_FIFO_OFFSET                 ((uint32)0x0100000UL)
#define EQADCB_DMACH_START                 ((uint8)0x40UL)
#define EQADC_FIFO_MAX_DEPTH               ((uint8)0x04UL)

/*---------------------------------------------------------------------------------------------------*/
/*                             EQADC CFIFO Transfer Counter Register 0 (EQADC_CFTCR0)                */
/*---------------------------------------------------------------------------------------------------*/
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT 9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |     |     |     |     |     |<---------------------------TC_CF0------------------------------>| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/*                                                                                                   */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT16|BIT17|BIT18|BIT19|BIT20|BIT21|BIT22|BIT23|BIT24|BIT25|BIT26|BIT27|BIT28|BIT29|BIT30|BIT31| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |     |     |     |     |     |<---------------------------TC_CF1------------------------------>| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */

/*---------------------------------------------------------------------------------------------------*/
/*                             EQADC CFIFO Transfer Counter Register 1 (EQADC_CFTCR1)                */
/*---------------------------------------------------------------------------------------------------*/
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT 9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |     |     |     |     |     |<---------------------------TC_CF2------------------------------>| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/*                                                                                                   */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT16|BIT17|BIT18|BIT19|BIT20|BIT21|BIT22|BIT23|BIT24|BIT25|BIT26|BIT27|BIT28|BIT29|BIT30|BIT31| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |     |     |     |     |     |<---------------------------TC_CF3------------------------------>| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */

/*---------------------------------------------------------------------------------------------------*/
/*                             EQADC CFIFO Transfer Counter Register 2 (EQADC_CFTCR2)                */
/*---------------------------------------------------------------------------------------------------*/
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT 9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |     |     |     |     |     |<---------------------------TC_CF4------------------------------>| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/*                                                                                                   */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT16|BIT17|BIT18|BIT19|BIT20|BIT21|BIT22|BIT23|BIT24|BIT25|BIT26|BIT27|BIT28|BIT29|BIT30|BIT31| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |     |     |     |     |     |<---------------------------TC_CF5------------------------------>| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */

#define EQADC_CFTCR0_TC_CF0                    ((uint32)0x07FF0000UL)
#define EQADC_CFTCR0_TC_CF1                    ((uint32)0x000007FFUL)
#define EQADC_CFTCR1_TC_CF2                    ((uint32)0x07FF0000UL)
#define EQADC_CFTCR1_TC_CF3                    ((uint32)0x000007FFUL)
#define EQADC_CFTCR2_TC_CF4                    ((uint32)0x07FF0000UL)
#define EQADC_CFTCR2_TC_CF5                    ((uint32)0x000007FFUL)

/*---------------------------------------------------------------------------------------------------*/
/*                             EQADC CFIFO Status Snapshot Register 0 (EQADC_CFSSR0)                 */
/*---------------------------------------------------------------------------------------------------*/
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT 9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* | CFS0_TCB0 | CFS1_TCB0 | CFS2_TCB0 | CFS3_TCB0 | CFS4_TCB0 | CFS5_TCB0 |     |     |     |     | */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/*                                                                                                   */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT16|BIT17|BIT18|BIT19|BIT20|BIT21|BIT22|BIT23|BIT24|BIT25|BIT26|BIT27|BIT28|BIT29|BIT30|BIT31| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |     |<--------LCFTCB0------>|<------------------------------TC_LCFTCB0----------------------->| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */

/*---------------------------------------------------------------------------------------------------*/
/*                             EQADC CFIFO Status Snapshot Register 1 (EQADC_CFSSR1)                 */
/*---------------------------------------------------------------------------------------------------*/
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT 9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* | CFS0_TCB1 | CFS1_TCB1 | CFS2_TCB1 | CFS3_TCB1 | CFS4_TCB1 | CFS5_TCB1 |     |     |     |     | */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/*                                                                                                   */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT16|BIT17|BIT18|BIT19|BIT20|BIT21|BIT22|BIT23|BIT24|BIT25|BIT26|BIT27|BIT28|BIT29|BIT30|BIT31| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |     |<--------LCFTCB1------>|<------------------------------TC_LCFTCB1----------------------->| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */

/* if Andorra2M and Andorra4M of Monaco 1.5M */
#if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
/*---------------------------------------------------------------------------------------------------*/
/*                             EQADC CFIFO Status Snapshot Register 2 (EQADC_CFSSR2)                 */
/*---------------------------------------------------------------------------------------------------*/
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT 9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* | CFS0_TSSI | CFS1_TSSI | CFS2_TSSI | CFS3_TSSI | CFS4_TSSI | CFS5_TSSI |     |     |     |     | */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/*                                                                                                   */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT16|BIT17|BIT18|BIT19|BIT20|BIT21|BIT22|BIT23|BIT24|BIT25|BIT26|BIT27|BIT28|BIT29|BIT30|BIT31| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |ECBNI|<--------LCFTSSI------>|<------------------------------TC_LCFTSSI----------------------->| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
#endif /* (IPV_EQADC == IPV_EQADC_01_00_11_01)  || (IPV_EQADC == IPV_EQADC_01_00_10_00) */

#define EQADC_CFSSR0_CFS0_TCB0               ((uint32)0xC0000000UL)
#define EQADC_CFSSR0_CFS1_TCB0               ((uint32)0x30000000UL)
#define EQADC_CFSSR0_CFS2_TCB0               ((uint32)0x0C000000UL)
#define EQADC_CFSSR0_CFS3_TCB0               ((uint32)0x03000000UL)
#define EQADC_CFSSR0_CFS4_TCB0               ((uint32)0x00C00000UL)
#define EQADC_CFSSR0_CFS5_TCB0               ((uint32)0x00300000UL)
#define EQADC_CFSSR0_LCFTCB0                 ((uint32)0x00007800UL)
#define EQADC_CFSSR0_LCFTCB00                ((uint32)0x00000000UL)        /*  - 0b0000 - Last command was transferred from CFIFO0 */
#define EQADC_CFSSR0_LCFTCB01                ((uint32)0x00000800UL)        /*  - 0b0001 - Last command was transferred from CFIFO1 */
#define EQADC_CFSSR0_LCFTCB02                ((uint32)0x00001000UL)        /*  - 0b0010 - Last command was transferred from CFIFO2 */
#define EQADC_CFSSR0_LCFTCB03                ((uint32)0x00001800UL)        /*  - 0b0011 - Last command was transferred from CFIFO3 */
#define EQADC_CFSSR0_LCFTCB04                ((uint32)0x00002000UL)        /*  - 0b0100 - Last command was transferred from CFIFO4 */
#define EQADC_CFSSR0_LCFTCB05                ((uint32)0x00002800UL)        /*  - 0b0101 - Last command was transferred from CFIFO5 */
#define EQADC_CFSSR0_TC_LCFTCB0              ((uint32)0x000007FFUL)

#define EQADC_CFSSR1_CFS0_TCB1               ((uint32)0xC0000000UL)
#define EQADC_CFSSR1_CFS1_TCB1               ((uint32)0x30000000UL)
#define EQADC_CFSSR1_CFS2_TCB1               ((uint32)0x0C000000UL)
#define EQADC_CFSSR1_CFS3_TCB1               ((uint32)0x03000000UL)
#define EQADC_CFSSR1_CFS4_TCB1               ((uint32)0x00C00000UL)
#define EQADC_CFSSR1_CFS5_TCB1               ((uint32)0x00300000UL)
#define EQADC_CFSSR1_LCFTCB1                 ((uint32)0x00007800UL)
#define EQADC_CFSSR1_LCFTCB10                ((uint32)0x00000000UL)        /*  - 0b0000 - Last command was transferred from CFIFO0 */
#define EQADC_CFSSR1_LCFTCB11                ((uint32)0x00000800UL)        /*  - 0b0001 - Last command was transferred from CFIFO1 */
#define EQADC_CFSSR1_LCFTCB12                ((uint32)0x00001000UL)        /*  - 0b0010 - Last command was transferred from CFIFO2 */
#define EQADC_CFSSR1_LCFTCB13                ((uint32)0x00001800UL)        /*  - 0b0011 - Last command was transferred from CFIFO3 */
#define EQADC_CFSSR1_LCFTCB14                ((uint32)0x00002000UL)        /*  - 0b0100 - Last command was transferred from CFIFO4 */
#define EQADC_CFSSR1_LCFTCB15                ((uint32)0x00002800UL)        /*  - 0b0101 - Last command was transferred from CFIFO5 */
#define EQADC_CFSSR1_TC_LCFTCB1              ((uint32)0x000007FFUL)

/* if Andorra2M and Andorra4M or Monaco 1.5M */
#if (IPV_EQADC == IPV_EQADC_01_00_11_01) || (IPV_EQADC == IPV_EQADC_01_00_10_00)
#define EQADC_CFSSR2_CFS0_TSSI               ((uint32)0xC0000000UL)
#define EQADC_CFSSR2_CFS1_TSSI               ((uint32)0x30000000UL)
#define EQADC_CFSSR2_CFS2_TSSI               ((uint32)0x0C000000UL)
#define EQADC_CFSSR2_CFS3_TSSI               ((uint32)0x03000000UL)
#define EQADC_CFSSR2_CFS4_TSSI               ((uint32)0x00C00000UL)
#define EQADC_CFSSR2_CFS5_TSSI               ((uint32)0x00300000UL)
#define EQADC_CFSSR2_ECBNI                   ((uint32)0x00008000UL)
#define EQADC_CFSSR2_LCFTSSI                 ((uint32)0x00007800UL)
#define EQADC_CFSSR2_LCFTSSI0                ((uint32)0x00000000UL)        /*  - 0b0000 - Last command was transferred from CFIFO0 */
#define EQADC_CFSSR2_LCFTSSI1                ((uint32)0x00000800UL)        /*  - 0b0001 - Last command was transferred from CFIFO1 */
#define EQADC_CFSSR2_LCFTSSI2                ((uint32)0x00001000UL)        /*  - 0b0010 - Last command was transferred from CFIFO2 */
#define EQADC_CFSSR2_LCFTSSI3                ((uint32)0x00001800UL)        /*  - 0b0011 - Last command was transferred from CFIFO3 */
#define EQADC_CFSSR2_LCFTSSI4                ((uint32)0x00002000UL)        /*  - 0b0100 - Last command was transferred from CFIFO4 */
#define EQADC_CFSSR2_LCFTSSI5                ((uint32)0x00002800UL)        /*  - 0b0101 - Last command was transferred from CFIFO5 */
#define EQADC_CFSSR2_TC_LCFTSSI              ((uint32)0x000007FFUL)
#endif /* (IPV_EQADC == IPV_EQADC_01_00_11_01)  || (IPV_EQADC == IPV_EQADC_01_00_10_00) */

/*---------------------------------------------------------------------------------------------------*/
/*                             EQADC CFIFO Status Register (EQADC_CFSR)                              */
/*---------------------------------------------------------------------------------------------------*/
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT 9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |   CFS0    |    CFS1   |    CFS2   |    CFS3   |    CFS4   |    CFS5   |     |     |     |     | */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/*                                                                                                   */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT16|BIT17|BIT18|BIT19|BIT20|BIT21|BIT22|BIT23|BIT24|BIT25|BIT26|BIT27|BIT28|BIT29|BIT30|BIT31| */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */
/* |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     | */
/* |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| */

#define EQADC_CFSR_CFS0                    ((uint32)0xC0000000UL)
#define EQADC_CFSR_CFS1                    ((uint32)0x30000000UL)
#define EQADC_CFSR_CFS2                    ((uint32)0x0C000000UL)
#define EQADC_CFSR_CFS3                    ((uint32)0x03000000UL)
#define EQADC_CFSR_CFS4                    ((uint32)0x00C00000UL)
#define EQADC_CFSR_CFS5                    ((uint32)0x00300000UL)

#define EQADC_CFIFO_IDLE                   0x0U
#define EQADC_CFIFO_WAITING_FOR_TRIGGER    0x2U
#define EQADC_CFIFO_TRIGGERED              0x3U

/**
@brief End Of Queue Bit. The EOQ bit is asserted in the last command of a CQueue to indicate to the EQADC
       that a scan of the CQueue is completed. EOQ instructs the EQADC to reset its current CFIFO transfer
       counter value (TC_CF) to zero. Depending on the CFIFO mode of operation, the CFIFO status will also
       change upon the detection of an asserted EOQ bit on the last transferred command - see Section 26.7.4.6,
       "CFIFO Scan Trigger Modes", for details.
       0 - Not the last entry of the CQueue.
       1 - Last entry of the CQueue.
       Note: If both the PAUSE and EOQ bits are asserted in the same command message the respective flags
             are set, but the CFIFO status changes as if only the EOQ bit were asserted.
*/
#define ADC_WRITE_CONFIG_EOQ               (uint32)0x80000000UL

/**
@brief BN Buffer Number Bit. BN indicates which buffer the message will be stored in.
*/
#define ADC_CONV_COM_BN                    (uint32)0x02000000UL
/**
@brief Message stored in buffer 1.
*/
#define ADC_CONV_COM_BN1                   (uint32)0x02000000UL
/**
@brief Message stored in buffer 0.
*/
#define ADC_CONV_COM_BN0                   (uint32)0x00000000UL

/**
@brief ADC0/ADC1 Configuration Control Register (ADC0_CR, ADC1_CR) Write/Read
*/
#define ADC_CR     ((uint8)0x1U)
/**
@brief ADC0/ADC1 Configuration Control Register (ADC0_CR, ADC1_CR) Write/Read
*/
#define ADC_ACR1   ((uint8)0x30U)
/**
@brief ADC0/ADC1 Configuration Control Register (ADC0_CR, ADC1_CR) Write/Read
*/
#define ADC_ACR2   ((uint8)0x34U)
/**
@brief Time Stamp Control Register (ADC_TSCR) Write/Read
*/
#define ADC_TSCR   ((uint8)0x2U)
/**
@brief Time Base Counter Register (ADC_TBCR) Write/Read
*/
#define ADC_TBCR   ((uint8)0x3U)
/**
@brief ADC0/ADC1 Gain Calibration Constant Register (ADC0_GCCR, ADC1_GCCR) Write/Read
*/
#define ADC_GCCR   ((uint8)0x4U)
/**
@brief ADC0/ADC1 Offset Calibration Constant Register (ADC0_OCCR, ADC1_OCCR)
*/
#define ADC_OCCR   ((uint8)0x5U)
/**
@brief ADC0/ADC1 Alternate Gain 1 Register (ADC0_AGR1, ADC1_AGR1) Write/Read
*/
#define ADC_AG1R   ((uint8)0x31U)
/**
@brief ADC0/ADC1 Alternate Offset 1 Register (ADC0_AOR1, ADC1_AOR1)
*/
#define ADC_AO1R   ((uint8)0x32U)
/**
@brief ADC0/ADC1 Alternate Gain 2 Register (ADC0_AGR2, ADC1_AGR2) Write/Read
*/
#define ADC_AG2R   ((uint8)0x35U)
/**
@brief ADC0/ADC1 Alternate Offset 2 Register (ADC0_AOR2, ADC1_AOR2)
*/
#define ADC_AO2R   ((uint8)0x36U)
/**
@brief ADCn_CLK_SEL : Used for clock selection
*/
#define ADCn_CLK_SEL 0x20U

/**
@brief ADCn_EN: ADCn enable. Enables ADCn to perform A/D conversions.
       0 - ADC is disabled. Clock supply to ADC0/1 is stopped.
       1 - ADC is enabled and ready to perform A/D conversions.
       NOTE: The bias generator circuit inside the ADC ceases functioning
             when both ADC0_EN and ADC1_EN bits are cleared.
             Conversion commands sent to a disabled ADC are ignored by
             the ADC control hardware.
             When the ADCn_EN status is changed from asserted to cleared,
             the ADC clock will not stop until it reaches its low phase.
*/
#define ADC_ADCn_EN        (uint16)0x8000U

/**
@brief ADCn_EMUX: ADCn external multiplexer enable. When ADCn_EMUX is asserted,
       the MA pins will output digital values according to the number
       of the external channel being converted for selecting external
       multiplexer inputs.
       0 - External multiplexer disabled; no external multiplexer channels
           can be selected.
       1 - External multiplexer enabled; external multiplexer channels can be
           selected.
       NOTE: Both ADCn_EMUX bits must not be asserted at the same time.
             The ADCn_EMUX bit must only be written when the ADCn_EN bit is
             cleared (ADC disabled). ADCn_EMUX can be set during the same write
             cycle used to set ADCn_EN.
*/
#define ADC_ADCn_EMUX      (uint16)0x0800U

/**
@{
@brief System Clock Divide Factor for ADC Clock
*/
#define ADC_ADCn_CLK_PS_0     0x00U
#define ADC_ADCn_CLK_PS_1     0x01U
#define ADC_ADCn_CLK_PS_2     0x02U
#define ADC_ADCn_CLK_PS_3     0x03U
#define ADC_ADCn_CLK_PS_4     0x04U
#define ADC_ADCn_CLK_PS_5     0x05U
#define ADC_ADCn_CLK_PS_6     0x06U
#define ADC_ADCn_CLK_PS_7     0x07U
#define ADC_ADCn_CLK_PS_8     0x08U
#define ADC_ADCn_CLK_PS_9     0x09U
#define ADC_ADCn_CLK_PS_10    0x0AU
#define ADC_ADCn_CLK_PS_11    0x0BU
#define ADC_ADCn_CLK_PS_12    0x0CU
#define ADC_ADCn_CLK_PS_13    0x0DU
#define ADC_ADCn_CLK_PS_14    0x0EU
#define ADC_ADCn_CLK_PS_15    0x0FU
#define ADC_ADCn_CLK_PS_16    0x10U
#define ADC_ADCn_CLK_PS_17    0x11U
#define ADC_ADCn_CLK_PS_18    0x12U
#define ADC_ADCn_CLK_PS_19    0x13U
#define ADC_ADCn_CLK_PS_20    0x14U
#define ADC_ADCn_CLK_PS_21    0x15U
#define ADC_ADCn_CLK_PS_22    0x16U
#define ADC_ADCn_CLK_PS_23    0x17U
#define ADC_ADCn_CLK_PS_24    0x18U
#define ADC_ADCn_CLK_PS_25    0x19U
#define ADC_ADCn_CLK_PS_26    0x1AU
#define ADC_ADCn_CLK_PS_27    0x1BU
#define ADC_ADCn_CLK_PS_28    0x1CU
#define ADC_ADCn_CLK_PS_29    0x1DU
#define ADC_ADCn_CLK_PS_30    0x1EU
#define ADC_ADCn_CLK_PS_31    0x1FU
/**@}*/

/**
@brief CAL: Calibration. Indicates if the returning conversion
       result must be calibrated.
       0 - Do not calibrate conversion result.
       1 - Calibrate conversion result.
*/
#define ADC_CONV_COM_CAL                   (uint32)0x01000000UL

/**
@{
@brief eQADC Calibration References
*/
/**
@brief 75% VREF IDEAL (CAL=1)
*/
#define   ADC_IDEAL_RES75       0x3000U
/**
@brief 25% VREF IDEAL (CAL=1)
*/
#define   ADC_IDEAL_RES25       0x1000U

#define   EQADC_COMMAND_CAL_CHANNEL25      (uint32)0x00082C00UL
#define   EQADC_COMMAND_CAL_CHANNEL75      (uint32)0x00002B00UL
/**@}*/

/**
@{
@brief FMT: Conversion data format. FMT specifies to the eQADC how to format
       the 12-bit conversion data returned by the ADCs into the 16-bit
       format which is sent to the RFIFOs.
       0 - Right justified unsigned.
       1 - Right justified signed.
*/
#define ADC_CONV_COM_FMT                   (uint32)0x00010000UL
#define ADC_CONV_COM_FMT_RJU               (uint32)0x00000000UL
#define ADC_CONV_COM_FMT_RJS               (uint32)0x00010000UL
/**@}*/

/**
@brief LST: Long sampling time. These two bits determine the duration of
       the sampling time in ADC clock cycles.
       NOTE: For external mux mode, 64 or 128 sampling cycles is recommended.
*/
#define ADC_CONV_COM_LST                   (uint32)0x000C0000UL
/**
@brief 2 Sampling cycles (ADC Clock Cycles)
*/
#define ADC_CONV_COM_LST_2                 (uint32)0x00000000UL
/**
@brief 8 Sampling cycles (ADC Clock Cycles)
*/
#define ADC_CONV_COM_LST_8                 (uint32)0x00040000UL
/**
@brief 64 Sampling cycles (ADC Clock Cycles)
*/
#define ADC_CONV_COM_LST_64                (uint32)0x00080000UL
/**
@brief 128 Sampling cycles (ADC Clock Cycles)
*/
#define ADC_CONV_COM_LST_128               (uint32)0x000C0000UL

/**
@{
@brief   EQADC clock cycle values
*/
#define ADC_2_CLOCK_CYCLES                   (uint32)0x000000UL
#define ADC_8_CLOCK_CYCLES                   (uint32)0x040000UL
#define ADC_64_CLOCK_CYCLES                (uint32)0x080000UL
#define ADC_128_CLOCK_CYCLES               (uint32)0x0C0000UL
/**@}*/

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

#ifdef __cplusplus
}
#endif

#endif /* #ifndef REG_eSys_EQADC_H */
