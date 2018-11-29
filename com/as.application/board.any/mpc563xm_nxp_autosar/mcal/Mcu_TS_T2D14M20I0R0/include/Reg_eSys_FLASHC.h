/**
    @file    Reg_eSys_FLASHC.h
    @version 2.0.0

    @brief   AUTOSAR Mcu - Defines used to access the Flash registers.
    @details This file contains defines used to access the Flash registers.
    
    Project AUTOSAR 3.0 MCAL
    Patform PA
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

@section Reg_eSys_FLASHC_h_REF_1
Violates MISRA-C:2004 Advisory Rule 19.15, Repeated include files, Precautions shall be taken in
order to prevent the contents of a header file being included twice This is not a violation since
all header files are protected against multiple inclusions

@section Reg_eSys_FLASHC_h_REF_2
Violates MISRA-C:2004 Advisory Rule 20.2, Re-use of C90 reserved identifier
This violation is due to the use of "_" which is required as per Autosar

@section Reg_eSys_FLASHC_h_REF_3
Violates MISRA-C:2004 Advisory Rule 19.7, Use of function like macro. This
violation is due to function like macros defined for register operations.
Function like macros are used to reduce code complexity.
*/

/**
@note Violates MISRA 2004 Advisory Rule 20.2, Re-use of C90 reserved 
identifier _REG_ESYS_FLASHC_H_- See @ref Reg_eSys_FLASHC_h_REF_2
*/
#ifndef _REG_ESYS_FLASHC_H_
#define _REG_ESYS_FLASHC_H_

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/** @note Violates MISRA 2004 Advisory Rule 19.15, Repeated include file -
See @ref Reg_eSys_FLASHC_h_REF_1*/
#include "Reg_eSys.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/* for XPC5668x platform */
#define IPV_FLASH_C90FL_2048_4_0_023 0x20484023UL

/* for XPC56XXA platform */
#define IPV_FLASH_C90FL_2048_4_0_238_2048_0_1_238 0x20484123UL

/* for XPC56XXA platform */
#define IPV_FLASH_C90FL_2048_4_0_336    0x20484033UL

/* for XPC564XB platform */
#define IPV_FLASH_C90FG_2_1568_2_6_1    0x21568261UL

/* for XPC560XP50 platform */
#define IPV_FLASH_C90FG_512_2_9         0x05120029UL

/* for XPC560XP40 platform */
#define IPV_FLASH_C90FG_256_1_4         0x02560014UL

/* for XPC56AXP60 platform */
#define IPV_FLASH_C90FG_1024_2_0        0x10240020UL

/* for XPC56XXL platform */
#define IPV_FLASH_C90FL3_1024_6_0       0x1000119UL

/* for XPC56EL70 platform */
#define IPV_FLASH_C90FL_2048_4_0_Nh     0x2048406EUL

/* for XPC56XXF platform */
#define IPV_FLASH_C90FL_2048_4_0        0x20484000UL

/* for XPC5604B platform */
#define IPV_FLASH_C90FG_544_2_9_65      0x05122965UL

/* for XPC5607B platform */
#define IPV_FLASH_C90FG_1568_2_6_69     0x15361669UL

/* for XPC5634M platform */
#define IPV_FLASH_C90FL_640_34_61       0x15364000UL

/* for XPC5675K platform */
#define IPV_FLASH_C90FG_1024_1_8         0x10240018UL

/* for XPC560XD platform */
#define IPV_FLASH_C90FG_256_1_4_D         0x02561444UL

/** @brief Module Configuration Register */
#define FLASH_MCR       ((uint32)FLASH_BASEADDR + (uint32)0x00UL)
/** @brief Low/Mid Address Space Block Locking Register */
#define FLASH_LML       ((uint32)FLASH_BASEADDR + (uint32)0x04UL)
/** @brief High Address Space Block Locking Register */
#define FLASH_HBL       ((uint32)FLASH_BASEADDR + (uint32)0x08UL)
/** @brief Secondary Low/Mid Address Space Block Locking Register */
#define FLASH_SLL       ((uint32)FLASH_BASEADDR + (uint32)0x0CUL)
/** @brief Low/Mid Address Space Block Select Register */
#define FLASH_LMS       ((uint32)FLASH_BASEADDR + (uint32)0x10UL)
/** @brief High Address Space Block Select Register */
#define FLASH_HBS       ((uint32)FLASH_BASEADDR + (uint32)0x14UL)
/** @brief Address Register */
#define FLASH_ADR       ((uint32)FLASH_BASEADDR + (uint32)0x18UL)

#ifdef IPV_FLASH
  /* if XPC560XP40/XPC560XP50/XPC560XP60/XPC5675K/XPC560XD platforms */
  #if ((IPV_FLASH == IPV_FLASH_C90FG_512_2_9) || (IPV_FLASH == IPV_FLASH_C90FG_256_1_4) ||\
     (IPV_FLASH == IPV_FLASH_C90FG_1024_1_8) || (IPV_FLASH == IPV_FLASH_C90FG_1024_2_0) ||\
     (IPV_FLASH == IPV_FLASH_C90FG_256_1_4_D))
     /** @brief Platform Flash Configuration Register0 */
     #define CFLASH_PFCR0    ((uint32)0xC3F8801CUL)
     /** @brief Platform Flash Configuration Register1 */
     #define DFLASH_PFCR1    ((uint32)0xC3F88020UL)
     /** @brief Platform Flash Access Protection Register */
     #define FLASH_PFAPR     ((uint32)0xC3F88024UL)
  #elif (IPV_FLASH == IPV_FLASH_C90FG_2_1568_2_6_1) /* if XPC564XB */
     /** @brief Platform Flash Configuration Register0(for Code Flash) */
     #define CFLASH_PFCR0    ((uint32)0xFFE8801CUL)
     /** @brief Platform Flash Configuration Register1(for Data Flash) */
     #define DFLASH_PFCR1    ((uint32)0xFFE88020UL)
     /** @brief Platform Flash Access Protection Register */  
     #define FLASH_PFAPR     ((uint32)0xFFE88024UL)
  #elif (IPV_FLASH == IPV_FLASH_C90FL_2048_4_0_023) /* if XPC5668x */
     /** @brief Platform Flash Configuration Register0 */
     #define PFCR0_FLASH      ((uint32)0xFFFF801CUL)
     /** @brief Platform Flash Configuration Register1 */
     #define PFCR1_FLASH      ((uint32)0xFFFF8020UL)
     /** @brief Platform Flash Access Protection Register */
     #define PFAPR_FLASH      ((uint32)0xFFFF8024UL)
  #elif ((IPV_FLASH == IPV_FLASH_C90FL3_1024_6_0) || \
         (IPV_FLASH == IPV_FLASH_C90FL_2048_4_0_Nh))  /* if XPC56XXL / XPC56EL70*/
     /** @brief Platform Flash Configuration Register0(for Code Flash) */
     #define CFLASH_PFCR0    ((uint32)0xFFE8801CUL)
     /** @brief Platform Flash Access Protection Register */
     #define FLASH_PFAPR     ((uint32)0xFFE88024UL)
  #elif ((IPV_FLASH == IPV_FLASH_C90FL_2048_4_0_238_2048_0_1_238)|| \
         (IPV_FLASH == IPV_FLASH_C90FL_2048_4_0) || (IPV_FLASH == IPV_FLASH_C90FL_640_34_61) || \
         (IPV_FLASH == IPV_FLASH_C90FL_2048_4_0_336))  /* if XPC56XXA / XPC56XXF / XPC5634M */
     /** @brief Bus Interface Unit Configuration Register 1  */
     #define FLASH_BIUCR0    ((uint32)0xC3F8801CUL)
     /** @brief Bus Interface Unit Access Protection Register  */
     #define FLASH_BIUAPR    ((uint32)0xC3F88020UL)
     /** @brief Bus Interface Unit Configuration Register 2  */
     #define FLASH_BIUCR1    ((uint32)0xC3F88024UL)
#else
     /** @brief Platform Flash Configuration Register0(for Code Flash) */
     #define CFLASH_PFCR0    ((uint32)0xFFE8801CUL)
     /** @brief Platform Flash Configuration Register1(for Data Flash) */
     #define DFLASH_PFCR1    ((uint32)0xFFE88020UL)
     /** @brief Platform Flash Access Protection Register */
     #define FLASH_PFAPR     ((uint32)0xFFE88024UL)
  #endif
#endif

#ifdef IPV_FLASH
    #if ((IPV_FLASH == IPV_FLASH_C90FL_2048_4_0_238_2048_0_1_238)|| \
         (IPV_FLASH == IPV_FLASH_C90FL_2048_4_0) || (IPV_FLASH == IPV_FLASH_C90FL_640_34_61) || \
         (IPV_FLASH == IPV_FLASH_C90FL_2048_4_0_336)) /* if XPC56XXA / XPC56XXF / XPC5634M */
       /** @brief  Address Pipelining Control */
       #define FLASH_BIUCR0_APC            ((uint32)0x0000E000L)
       /** @brief Write Wait State Control */
       #define FLASH_BIUCR0_WWSC           ((uint32)0x00001800UL)
       /** @brief  Read Wait State Control */
       #define FLASH_BIUCR0_RWSC           ((uint32)0x00000700UL)
       /** @brief  Reset value of RWS, WWS, APC */
       #define RESET_BIUCR_APC_WWSC_RWSC    ((uint32)0x0000FF00UL)
    #elif (IPV_FLASH == IPV_FLASH_C90FL_2048_4_0_023) /* else if XPC5668x */
       /** @brief Address Pipelining Control */
       #define CFLASH_PFCR0_APC            ((uint32)0x0000E000L)
       /** @brief Write Wait State Control */
       #define CFLASH_PFCR0_WWSC           ((uint32)0x00001800UL)
       /** @brief Read Wait State Control */
       #define CFLASH_PFCR0_RWSC           ((uint32)0x00000700UL)
       /** @brief Address Pipelining Control */
       #define CFLASH_PFCR1_APC            ((uint32)0x0000E000L)
       /** @brief Write Wait State Control */
       #define CFLASH_PFCR1_WWSC           ((uint32)0x00001800UL)
       /** @brief Read Wait State Control */
       #define CFLASH_PFCR1_RWSC           ((uint32)0x00000700UL)
       /** @brief Reset value of RWS, WWS, APC */
       #define RESET_PFCR_APC_WWSC_RWSC    ((uint32)0x0000FF00UL)
    #else /* for XPC560XD platform */
       /** @brief Bit fields of Flash BIU Control Register 0 */
       /** @brief Bank0+2 Address Pipelining Control */
       #define CFLASH_PFCR0_B02_APC        ((uint32)0xF8000000UL)
       /** @brief Bank0+2 Write Wait State Control */
       #define CFLASH_PFCR0_B02_WWSC       ((uint32)0x07C00000UL)
       /** @brief Bank0+2 Read Wait State Control */
       #define CFLASH_PFCR0_B02_RWSC       ((uint32)0x003E0000UL)

       /** @brief Bank1 Address Pipelining Control */
       #define DFLASH_PFCR1_B1_APC         ((uint32)0xF8000000UL)
       /** @brief Bank1 Write Wait State Control */
       #define DFLASH_PFCR1_B1_WWSC        ((uint32)0x07C00000UL)
       /** @brief Bank1 Read Wait State Control */
       #define DFLASH_PFCR1_B1_RWSC        ((uint32)0x003E0000UL)
    #endif
#endif

/** @brief Bit fields of Module Configuration Register */
#define FLASH_MCR_EDC       ((uint32)0x80000000UL)  /** @brief ECC Data Correction */
#define FLASH_MCR_SIZE      ((uint32)0x07000000UL)  /** @brief Array Space Size */
#define FLASH_MCR_LAS       ((uint32)0x00700000UL)  /** @brief Low Address Space Size */
#define FLASH_MCR_MAS       ((uint32)0x00010000UL)  /** @brief Mid Address Space Size */
#define FLASH_MCR_EER       ((uint32)0x00008000UL)  /** @brief ECC Event Error */
#define FLASH_MCR_RWE       ((uint32)0x00004000UL)  /** @brief RWW Event Error */
#define FLASH_MCR_PEAS      ((uint32)0x00000800UL)  /** @brief Program/Erase Access Space */
#define FLASH_MCR_DONE      ((uint32)0x00000400UL)  /** @brief State Machine Status */
#define FLASH_MCR_PEG       ((uint32)0x00000200UL)  /** @brief Program/Erase Good */
#define FLASH_MCR_PGM       ((uint32)0x00000010UL)  /** @brief Program */
#define FLASH_MCR_PSUS      ((uint32)0x00000008UL)  /** @brief Program Suspend */
#define FLASH_MCR_ERS       ((uint32)0x00000004UL)  /** @brief Erase */
#define FLASH_MCR_ESUS      ((uint32)0x00000002UL)  /** @brief Erase Suspend */
#define FLASH_MCR_EHV       ((uint32)0x00000001UL)  /** @brief Enable High Voltage */

/** @brief Bit fields of Low/Mid Address Space Block Locking Register */
#define FLASH_LML_LME       ((uint32)0x80000000UL)  /** @brief Low and Mid Address Lock Enable */
#define FLASH_LML_TLOCK     ((uint32)0x00100000UL)  /** @brief Test Lock */
#define FLASH_LML_MLOCK     ((uint32)0x00030000UL)  /** @brief Mid Address Block Lock */
#define FLASH_LML_LLOCK     ((uint32)0x0000FFFFUL)  /** @brief Low Address Block Lock */

/** @brief Bit fields of EEPROM High Address Space Block Locking Register */
#define FLASH_HBL_HBE       ((uint32)0x80000000UL)  /** @brief High Address Lock Enable */
#define FLASH_HBL_HLOCK     ((uint32)0x0000003FUL)  /** @brief High Address Space Block Lock */

/** @brief Bit fields of Secondary Low/Mid Address Space Block Locking Register */
#define FLASH_SLL_SLE       ((uint32)0x80000000UL) /** @brief Secondary Low, Mid Addr Lock Enable*/
#define FLASH_SLL_SSLOCK    ((uint32)0x00100000UL) /** @brief Secondary Shadow Lock */
#define FLASH_SLL_SMLOCK    ((uint32)0x00030000UL) /** @brief Secondary Mid Address Block Lock */
#define FLASH_SLL_SLLOCK    ((uint32)0x0000FFFFUL) /** @brief Secondary Low Address Block Lock */

/** @brief Bit fields of Low/Mid Address Space Block Select Register */
#define FLASH_LMS_MSEL      ((uint32)0x00030000UL)  /** @brief Mid Address Space Block Select */
#define FLASH_LMS_LSEL      ((uint32)0x0000FFFFUL)  /** @brief Low Address Space Block Select */

/** @brief Bit fields of High Address Space Block Select Register */
#define FLASH_HBS_HBSEL     ((uint32)0x0000003FUL)  /** @brief High Address Space Block Select */


/** @brief ECC status register */
#define FLS_MCM_ESR          ((uint32)0xFFF40047UL)
#define FLS_MCM_ESR_FNCE     ((uint8)0x01U)

/** @brief Set FLASHC_MCR bits without affecting MCR_EDC, MCR_EER and MCR_RWE
  (writing zero will not affect these bits) */
/** @note Violates MISRA 2004 Advisory Rule 19.7 - See @ref Reg_eSys_FLASHC_h_REF_3*/
#define LLM_Flash_MCR_bit_set(MCRAddress, mask) \
    { \
        uint32 value = (REG_READ32(MCRAddress) | (mask)); \
        value &= (~(FLASH_MCR_EDC | FLASH_MCR_EER | FLASH_MCR_RWE)); \
        REG_WRITE32((MCRAddress), value); \
    }

/** @brief Clear FLASHC_MCR bits without affecting MCR_EDC, MCR_EER and MCR_RWE
  (writing zero will not affect these bits) */
/** @note Violates MISRA 2004 Advisory Rule 19.7 - See @ref Reg_eSys_FLASHC_h_REF_3*/
#define LLM_Flash_MCR_bit_clear(MCRAddress, mask) \
    { \
        uint32 value = (REG_READ32(MCRAddress) & (~(mask))); \
        value &= (~(FLASH_MCR_EDC | FLASH_MCR_EER | FLASH_MCR_RWE)); \
        REG_WRITE32((MCRAddress), value); \
    }

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/


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

#endif /* _REG_ESYS_FLASHC_H_ */
