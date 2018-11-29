/**
    @file    Reg_FlashMem.h
    @version 2.0.5.0

    @brief   AUTOSAR Fls - AUTOSAR Module Flash Driver
    @details MCU HW IP module registers and bits
    
    Project AUTOSAR 3.0 MCAL
    Patform PA
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

#ifndef REG_FLASHMEM_H
#define REG_FLASHMEM_H

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
                                           CONSTANTS
==================================================================================================*/

#define IPV_FLASH_C90FL3_1024_6_0                   0x1000119UL     /* for XPC56XXL platform */
#define IPV_FLASH_C90FL_2048_4_0_Nh                 0x2048406EUL    /* for SPC56EL70 platform */
#define IPV_FLASH_C90FL_2048_4_0                    0x20484000UL    /* for XPC56XXF platform */
#define IPV_FLASH_C90FL_2048_4_0_238_2048_0_1_238   0x20484123UL    /* for XPC56XXA platform */
#define IPV_FLASH_C90FL_2048_4_0_336                0x20484033UL    /* for XPC56XXA platform */
#define IPV_FLASH_C90FG_2_1568_2_6_1                0x21568261UL    /* for XPC564XB platform */
#define IPV_FLASH_C90FG_1024_2_0                    0x10240020UL    /* for XPC56AXP60 platform */
#define IPV_FLASH_C90FG_512_2_9                     0x05120029UL    /* for XPC560XP50 platform */
#define IPV_FLASH_C90FG_256_1_4                     0x02560014UL    /* for XPC560XP40 platform */
#define IPV_FLASH_C90FG_544_2_9_65                  0x05122965UL    /* for XPC5604B platform */
#define IPV_FLASH_C90FG_1568_2_6_69                 0x15361669UL    /* for XPC5607B platform */
#define IPV_FLASH_C90FL_640_34_61                   0x15364000UL    /* for XPC5634M platform */
#define IPV_FLASH_C90FL_2048_4_0_023                0x20484023UL    /* for XPC5668x platform */
#define IPV_FLASH_C90FG_1024_1_8                    0x10240018UL    /* for XPC5675K platform */
#define IPV_FLASH_C90FG_256_1_4_D                   0x02561444UL    /* for XPC5602D platform */
#define IPV_FLASH_C90FG_1024_2_6_E                  0x1024026EUL    /* for XPC5606S platform */

/* memory array control/configuration registers */
#define FLASHMEM_MCR    0x0000U /**< @brief Module Configuration Register (MCR) */
#define FLASHMEM_LML    0x0001U /**< @brief Low/Mid address space block Locking register (LML) */
#define FLASHMEM_HBL    0x0002U /**< @brief High address space Block Locking register (HBL) */
#define FLASHMEM_SLL    0x0003U /**< @brief Secondary Low/mid address space block Locking register (SLL) */
#define FLASHMEM_LMS    0x0004U /**< @brief Low/Mid address space block Select register (LMS) */
#define FLASHMEM_HBS    0x0005U /**< @brief High address space Block Select register (HBS) */
#define FLASHMEM_ADR    0x0006U /**< @brief Address Register (ADR) */
#define FLASHMEM_BIU0   0x0007U /**< @brief Bus Interface Unit 0 register (BIU0) */
#define FLASHMEM_BIU1   0x0008U /**< @brief Bus Interface Unit 1 register (BIU1) */
#define FLASHMEM_BIU2   0x0009U /**< @brief Bus Interface Unit 2 register (BIU2) */
#define FLASHMEM_UT0    0x000FU /**< @brief User Test 0 register (UT0) */
#define FLASHMEM_UT1    0x0010U /**< @brief User Test 1 register (UT1) */
#define FLASHMEM_UT2    0x0011U /**< @brief User Test 2 register (UT2) */
#define FLASHMEM_UMISR0 0x0012U /**< @brief User Multiple Input Signature Register 0 (UMISR0) */
#define FLASHMEM_UMISR1 0x0013U /**< @brief User Multiple Input Signature Register 1 (UMISR1) */
#define FLASHMEM_UMISR2 0x0014U /**< @brief User Multiple Input Signature Register 2 (UMISR2) */
#define FLASHMEM_UMISR3 0x0015U /**< @brief User Multiple Input Signature Register 3 (UMISR3) */
#define FLASHMEM_UMISR4 0x0016U /**< @brief User Multiple Input Signature Register 4 (UMISR4) */

/* PFC (Platform Flash Controller) control/configuration registers */
#define FLASHMEM_PFCR0 0x0007U /**< @brief Platform Flash Configuration Register 0 (PFCR0) */
#define FLASHMEM_PFCR1 0x0008U /**< @brief Platform Flash Configuration Register 1 (PFCR1) */
#define FLASHMEM_PFAPR 0x0009U /**< @brief Platform Flash Access Protection Register (PFAPR) */

/* MCR register bits */
#ifdef IPV_FLASH
    /*for XPC56XXL, SPC56EL70 or XPC56XXF platform*/
    #if ((IPV_FLASH == IPV_FLASH_C90FL3_1024_6_0) || \
         (IPV_FLASH == IPV_FLASH_C90FL_2048_4_0_Nh) || \
         (IPV_FLASH == IPV_FLASH_C90FL_2048_4_0) || \
         (IPV_FLASH == IPV_FLASH_C90FL_2048_4_0_238_2048_0_1_238) || \
         (IPV_FLASH == IPV_FLASH_C90FL_2048_4_0_336) || \
         (IPV_FLASH == IPV_FLASH_C90FL_2048_4_0_023))
         #define MCR_EDC  0x00002000U  /**< @brief SBC: Single Bit Correction (Read/Clear) */
    #else
        /*for XPC56XXB, XPC56XXP, XPC560XB, XPC5634M and XPC5606S platform */
        #define MCR_EDC  0x80000000U  /**< @brief SBC: Single Bit Correction (Read/Clear) */
    #endif
#endif /*ifdef IPV_FLASH */

#define MCR_EER  0x00008000U  /**< @brief EER: Ecc event ERror (Read/Clear) */
#define MCR_RWE  0x00004000U  /**< @brief RWE: Read-while-Write event Error (Read/Clear) */
#define MCR_PEAS 0x00000800U  /**< @brief PEAS: Program/Erase Access Space (Read Only) */
#define MCR_DONE 0x00000400U  /**< @brief DONE: modify operation DONE (Read Only) */
#define MCR_PEG  0x00000200U  /**< @brief PEG: Program/Erase Good (Read Only) */
#define MCR_PGM  0x00000010U  /**< @brief PGM: ProGraM (Read/Write) */
#define MCR_PSUS 0x00000008U  /**< @brief PSUS: Program SUSpend (Read/Write) */
#define MCR_ERS  0x00000004U  /**< @brief ERS: ERaSe (Read/Write) */
#define MCR_ESUS 0x00000002U  /**< @brief ESUS: Erase SUSpend (Read/Write) */
#define MCR_EHV  0x00000001U  /**< @brief EHV: Enable High Voltage (Read/Write) */

/* LML register bits */
#define LML_LME  0x80000000U  /**< @brief LME: Low/Mid address space block Enable (Read Only) */
#define LML_TSLK 0x00100000U  /**< @brief TSLK: Test/Shadow address space block LocK (Read/Write) */
#define LML_MLK1 0x00020000U  /**< @brief MLK1-0: Mid address space block LocK 1-0(Read/Write) */
#define LML_MLK0 0x00010000U  /**< @brief MLK1-0: Mid address space block LocK 1-0(Read/Write) */
#define LML_LLK9 0x00000200U  /**< @brief LLK15-0: Low address space block LocK 15-0 (Read/Write) */
#define LML_LLK8 0x00000100U  /**< @brief LLK15-0: Low address space block LocK 15-0 (Read/Write) */
#define LML_LLK7 0x00000080U  /**< @brief LLK15-0: Low address space block LocK 15-0 (Read/Write) */
#define LML_LLK6 0x00000040U  /**< @brief LLK15-0: Low address space block LocK 15-0 (Read/Write) */
#define LML_LLK5 0x00000020U  /**< @brief LLK15-0: Low address space block LocK 15-0 (Read/Write) */
#define LML_LLK4 0x00000010U  /**< @brief LLK15-0: Low address space block LocK 15-0 (Read/Write) */
#define LML_LLK3 0x00000008U  /**< @brief LLK15-0: Low address space block LocK 15-0 (Read/Write) */
#define LML_LLK2 0x00000004U  /**< @brief LLK15-0: Low address space block LocK 15-0 (Read/Write) */
#define LML_LLK1 0x00000002U  /**< @brief LLK15-0: Low address space block LocK 15-0 (Read/Write) */
#define LML_LLK0 0x00000001U  /**< @brief LLK15-0: Low address space block LocK 15-0 (Read/Write) */
#define LML_LME_PASSWORD 0xA1A11111U  /**< @brief LME password */

/* SLL register bits */
#define SLL_SLE  0x80000000U  /**< @brief SLE: Secondary Low/Mid address space block Enable (Read Only) */
#define SLL_SLE_PASSWORD 0xC3C33333U  /**< @brief HBE password */

/* HBL register bits */
#define HBL_HBE  0x80000000U  /**< @brief HBE: High address space Block Enable (Read Only) */
#define HBL_HLK7 0x00000080U  /**< @brief HLK11-0: High address space block LocK 11-0 (Read/Write) */
#define HBL_HLK6 0x00000040U  /**< @brief HLK11-0: High address space block LocK 11-0 (Read/Write) */
#define HBL_HLK5 0x00000020U  /**< @brief HLK11-0: High address space block LocK 11-0 (Read/Write) */
#define HBL_HLK4 0x00000010U  /**< @brief HLK11-0: High address space block LocK 11-0 (Read/Write) */
#define HBL_HLK3 0x00000008U  /**< @brief HLK11-0: High address space block LocK 11-0 (Read/Write) */
#define HBL_HLK2 0x00000004U  /**< @brief HLK11-0: High address space block LocK 11-0 (Read/Write) */
#define HBL_HLK1 0x00000002U  /**< @brief HLK11-0: High address space block LocK 11-0 (Read/Write) */
#define HBL_HLK0 0x00000001U  /**< @brief HLK11-0: High address space block LocK 11-0 (Read/Write) */
#define HBL_HBE_PASSWORD 0xB2B22222U  /**< @brief HBE password */

/* LMS register bits */
#define LMS_MSL1 0x00020000U  /**< @brief MSL1-0: Mid address space block SeLect 1-0 (Read/Write) */
#define LMS_MSL0 0x00010000U  /**< @brief MSL1-0: Mid address space block SeLect 1-0 (Read/Write) */
#define LMS_LSL9 0x00000200U  /**< @brief LSL15-0: Low address space block SeLect 15-0 (Read/Write) */
#define LMS_LSL8 0x00000100U  /**< @brief LSL15-0: Low address space block SeLect 15-0 (Read/Write) */
#define LMS_LSL7 0x00000080U  /**< @brief LSL15-0: Low address space block SeLect 15-0 (Read/Write) */
#define LMS_LSL6 0x00000040U  /**< @brief LSL15-0: Low address space block SeLect 15-0 (Read/Write) */
#define LMS_LSL5 0x00000020U  /**< @brief LSL15-0: Low address space block SeLect 15-0 (Read/Write) */
#define LMS_LSL4 0x00000010U  /**< @brief LSL15-0: Low address space block SeLect 15-0 (Read/Write) */
#define LMS_LSL3 0x00000008U  /**< @brief LSL15-0: Low address space block SeLect 15-0 (Read/Write) */
#define LMS_LSL2 0x00000004U  /**< @brief LSL15-0: Low address space block SeLect 15-0 (Read/Write) */
#define LMS_LSL1 0x00000002U  /**< @brief LSL15-0: Low address space block SeLect 15-0 (Read/Write) */
#define LMS_LSL0 0x00000001U  /**< @brief LSL15-0: Low address space block SeLect 15-0 (Read/Write) */

/* HBS register bits */
#define HBS_HSL7 0x00000080U  /**< @brief HSL11-0: High address space block SeLect 11-0 (Read/Write) */
#define HBS_HSL6 0x00000040U  /**< @brief HSL11-0: High address space block SeLect 11-0 (Read/Write) */
#define HBS_HSL5 0x00000020U  /**< @brief HSL11-0: High address space block SeLect 11-0 (Read/Write) */
#define HBS_HSL4 0x00000010U  /**< @brief HSL11-0: High address space block SeLect 11-0 (Read/Write) */
#define HBS_HSL3 0x00000008U  /**< @brief HSL11-0: High address space block SeLect 11-0 (Read/Write) */
#define HBS_HSL2 0x00000004U  /**< @brief HSL11-0: High address space block SeLect 11-0 (Read/Write) */
#define HBS_HSL1 0x00000002U  /**< @brief HSL11-0: High address space block SeLect 11-0 (Read/Write) */
#define HBS_HSL0 0x00000001U  /**< @brief HSL11-0: High address space block SeLect 11-0 (Read/Write) */

/* UT0 register bits */
#define UT0_AIE  0x00000002U  /**< @brief AIE: Array Integrity Enable (Read/Write) */

/* PFCR0 register bits */
#define PFCR0_B02_P1_BFE 0x00000100U  /**< @brief B02_P1_BFE: Bank0+2, Port 1 Buffer Enable */
#define PFCR0_B02_P0_BFE 0x00000001U  /**< @brief B02_P0_BFE: Bank0+2, Port 0 Buffer Enable */

/* PFCR1 register bits */
#define PFCR1_B1_P1_BFE  0x00000100U  /**< @brief B1_P1_BFE: Bank1, Port 1 Buffer Enable */
#define PFCR1_B1_P0_BFE  0x00000001U  /**< @brief B1_P0_BFE: Bank1, Port 0 Buffer Enable */

#ifdef __cplusplus
}
#endif

#endif /* REG_FLASHMEM_H */
