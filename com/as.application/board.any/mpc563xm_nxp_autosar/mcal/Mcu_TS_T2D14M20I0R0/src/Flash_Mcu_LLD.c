/**
    @file    Flash_Mcu_LLD.c
    @version 2.0.0

    @brief   AUTOSAR Mcu - File used by MCU to configure some flash parameters.
    @details This file contains a function used for initializing global parameters for the flash
             memory.

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

@section Flash_Mcu_LLD_C_REF_1
Violates  MISRA-C:2004 Advisory  Rule 19.1,  only preprocessor statements and comments before
'#include'
This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003

@section Flash_Mcu_LLD_C_REF_2
Violates MISRA-C:2004  Advisory Rule 19.15, Precautions shall be taken in order to prevent the contents of a
header file being included twice.
This is not a violation since all header files are protected against multiple inclusions.

@section Flash_Mcu_LLD_C_REF_3
Violates MISRA-C:2004 Advisory Rule 11.1, Conversions shall not be performed between a pointer to a
function and any type other than an integral type.This violation is due to cast from 
unsigned long to pointer.The cast can not be avoided as it is used to access memory 
mapped registers.
*/
#ifdef __cplusplus
extern "C" {
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
#define FLASH_MCU_LLD_VENDOR_ID_C         43
#define FLASH_MCU_LLD_AR_MAJOR_VERSION_C  3
#define FLASH_MCU_LLD_AR_MINOR_VERSION_C  0
#define FLASH_MCU_LLD_AR_PATCH_VERSION_C  0
#define FLASH_MCU_LLD_SW_MAJOR_VERSION_C  2
#define FLASH_MCU_LLD_SW_MINOR_VERSION_C  0
#define FLASH_MCU_LLD_SW_PATCH_VERSION_C  0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and MCU_LLD header file are of the same vendor */
#if (FLASH_MCU_LLD_VENDOR_ID_C != MCU_LLD_VENDOR_ID)
#error "Flash_Mcu_LLD.c and Mcu_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and MCU_LLD header file are of the same Autosar version */
    #if ((FLASH_MCU_LLD_AR_MAJOR_VERSION_C != MCU_LLD_AR_MAJOR_VERSION) || \
         (FLASH_MCU_LLD_AR_MINOR_VERSION_C != MCU_LLD_AR_MINOR_VERSION) || \
         (FLASH_MCU_LLD_AR_PATCH_VERSION_C != MCU_LLD_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Flash_Mcu_LLD.c and Mcu_LLD.h are different"
    #endif
#endif
/* Check if source file and MCU_LLD header file are of the same Software version */
#if ((FLASH_MCU_LLD_SW_MAJOR_VERSION_C != MCU_LLD_SW_MAJOR_VERSION) || \
     (FLASH_MCU_LLD_SW_MINOR_VERSION_C != MCU_LLD_SW_MINOR_VERSION) || \
     (FLASH_MCU_LLD_SW_PATCH_VERSION_C != MCU_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of Flash_Mcu_LLD.c and Mcu_LLD.h are different"
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

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define MCU_START_SEC_RAMCODE
/** @note Violates MISRA 2004  19.1, 19.15 :See @ref Flash_Mcu_LLD_C_REF_1, Flash_Mcu_LLD_C_REF_2 above*/
#include "MemMap.h"
FUNC(void, MCU_RAM_CODE) Mcu_Flash_Init_Ram(P2CONST(McuLLD_ConfigType, AUTOMATIC, MCU_APPL_DATA) \
        ConfigLLDPtr);
FUNC(void, MCU_RAM_CODE) Mcu_Flash_Configure_Ram(VAR(uint32, MCU_VAR) Mcu_CFlash_Conf, \
        VAR(uint32, MCU_VAR) Mcu_DFlash_Conf);
#define MCU_STOP_SEC_RAMCODE
/** @note Violates MISRA 2004  19.1, 19.15 :See @ref Flash_Mcu_LLD_C_REF_1, Flash_Mcu_LLD_C_REF_2 above*/
#include "MemMap.h"
/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
#define MCU_START_SEC_VAR_UNSPECIFIED
/** @note Violates MISRA 2004  19.1, 19.15 : See @ref Flash_Mcu_LLD_C_REF_1, Flash_Mcu_LLD_C_REF_2 above*/
#include "MemMap.h"
P2FUNC (void, const, Mcu_Flash_Init)(P2CONST(McuLLD_ConfigType, AUTOMATIC, MCU_APPL_DATA) \
        ConfigLLDPtr) = &Mcu_Flash_Init_Ram;
P2FUNC (void, const, Mcu_Flash_Configure)(VAR(uint32, MCU_VAR) Mcu_CFlash_Conf, \
        VAR(uint32, MCU_VAR) Mcu_DFlash_Conf) = &Mcu_Flash_Configure_Ram;
#define MCU_STOP_SEC_VAR_UNSPECIFIED
/** @note Violates MISRA 2004  19.1, 19.15 : See @ref Flash_Mcu_LLD_C_REF_1, Flash_Mcu_LLD_C_REF_2 above*/
#include "MemMap.h"

#define MCU_START_SEC_RAMCODE
/** @note Violates MISRA 2004  19.1, 19.15 : See @ref Flash_Mcu_LLD_C_REF_1, Flash_Mcu_LLD_C_REF_2 above*/
#include "MemMap.h"
/**
@brief   This function initializes global settings for the flash memory.
@details The function initializes settings like Address Pipelining Control, Write Wait State
               Control, Read Wait State Control, Read-While-Write Control, Page Buffer
           Configuration, Page Buffer Configuration, Data Prefetch Enable, Instruction Prefetch
           Enable, Prefetch Limit, Buffer Enable, Arbitration Mode, Master Prefetch Disable,
           Master Access Protection.
@param[in]     ConfigLLDPtr      Mcu configuration pointer

@return Description of the returned value

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers MCU116
@remarks Implements DMCU01700
 */
FUNC(void, MCU_RAM_CODE) Mcu_Flash_Init_Ram(P2CONST(McuLLD_ConfigType, AUTOMATIC, MCU_APPL_DATA) \
    ConfigLLDPtr) {

#ifdef IPV_FLASH
  #if (IPV_FLASH == IPV_FLASH_C90FL_2048_4_0_023) /* if XPC5668x */
    /* This is applicable for the following lines of code */
    /** @remarks Covers MCU116 */
    /** @note Violates MISRA 2004  11.1 : See @ref Flash_Mcu_LLD_C_REF_3 above*/    
    /*lint -save -e923*/
    REG_RMW32(PFCR0_FLASH,(~((uint32)(CFLASH_PFCR0_APC | CFLASH_PFCR0_WWSC | CFLASH_PFCR0_RWSC))), \
            (uint32) (ConfigLLDPtr->flashPFCR0));

    REG_RMW32(PFCR1_FLASH,(~((uint32)(CFLASH_PFCR1_APC | CFLASH_PFCR1_WWSC | CFLASH_PFCR1_RWSC))), \
            (uint32) (ConfigLLDPtr->flashPFCR1));

    REG_WRITE32(PFAPR_FLASH, (uint32) (ConfigLLDPtr->flashPFAPR));
    /*lint -restore*/

  #elif ((IPV_FLASH == IPV_FLASH_C90FL3_1024_6_0) || \
         (IPV_FLASH == IPV_FLASH_C90FL_2048_4_0_Nh))  /* if XPC56XXL / XPC56EL70 */
    /* This is applicable for the following lines of code */
    /** @remarks Covers MCU116 */
    /** @note Violates MISRA 2004  11.1 : See @ref Flash_Mcu_LLD_C_REF_3 above*/
    /*lint -save -e923*/
    REG_RMW32(CFLASH_PFCR0, (~((uint32) (CFLASH_PFCR0_B02_APC | CFLASH_PFCR0_B02_WWSC | \
            CFLASH_PFCR0_B02_RWSC))), (uint32) (ConfigLLDPtr->flashPFCR0));

    REG_WRITE32(FLASH_PFAPR, (uint32) (ConfigLLDPtr->flashPFAPR));
    /*lint -restore*/

  #elif ((IPV_FLASH == IPV_FLASH_C90FL_2048_4_0_238_2048_0_1_238)|| \
         (IPV_FLASH == IPV_FLASH_C90FL_2048_4_0) || (IPV_FLASH == IPV_FLASH_C90FL_640_34_61)|| \
         (IPV_FLASH == IPV_FLASH_C90FL_2048_4_0_336)) /* if XPC56XXA / XPC56XXF / XPC5634M */
  /* This is applicable for the following lines of code */
    /** @remarks Covers MCU116 */
    /** @note Violates MISRA 2004  11.1 : See @ref Flash_Mcu_LLD_C_REF_3 above*/
    /*lint -save -e923*/
    REG_RMW32(FLASH_BIUCR0,(~((uint32)(FLASH_BIUCR0_APC | FLASH_BIUCR0_WWSC | FLASH_BIUCR0_RWSC))),\
           (uint32) (ConfigLLDPtr->flashBIUCR0));

    REG_WRITE32(FLASH_BIUCR1, (uint32) (ConfigLLDPtr->flashBIUCR1));

    REG_WRITE32(FLASH_BIUAPR, (uint32) (ConfigLLDPtr->flashBIUAPR));
    /*lint -restore*/
  /* if PICTUS XPC560XP40/XPC560XP50/XPC560XP60/XPC5675K/XPC560XD platforms */
  #elif ((IPV_FLASH == IPV_FLASH_C90FG_512_2_9) || (IPV_FLASH == IPV_FLASH_C90FG_256_1_4) || \
            (IPV_FLASH == IPV_FLASH_C90FG_1024_2_0) || (IPV_FLASH == IPV_FLASH_C90FG_1024_1_8)|| \
            (IPV_FLASH ==IPV_FLASH_C90FG_256_1_4_D))
    /* This is applicable for the following lines of code */
    /** @remarks Covers MCU116 */
    /** @note Violates MISRA 2004  11.1 : See @ref Flash_Mcu_LLD_C_REF_3 above*/
    /*lint -save -e923*/
    REG_RMW32(CFLASH_PFCR0, (~((uint32) (CFLASH_PFCR0_B02_APC | CFLASH_PFCR0_B02_WWSC | \
            CFLASH_PFCR0_B02_RWSC))), (uint32) (ConfigLLDPtr->flashPFCR0));

    REG_RMW32(DFLASH_PFCR1, (~((uint32) (DFLASH_PFCR1_B1_APC | DFLASH_PFCR1_B1_WWSC | \
            DFLASH_PFCR1_B1_RWSC))), (uint32) (ConfigLLDPtr->flashPFCR1));

    REG_WRITE32(FLASH_PFAPR, (uint32) (ConfigLLDPtr->flashPFAPR));
    /*lint -restore*/
  #else
    /* This is applicable for the following lines of code */
    /** @remarks Covers MCU116 */
    /** @note Violates MISRA 2004  11.1 : See @ref Flash_Mcu_LLD_C_REF_3 above*/
    /*lint -save -e923*/
    REG_RMW32(CFLASH_PFCR0, (~((uint32) (CFLASH_PFCR0_B02_APC | CFLASH_PFCR0_B02_WWSC | \
            CFLASH_PFCR0_B02_RWSC))), (uint32) (ConfigLLDPtr->flashPFCR0));

    REG_RMW32(DFLASH_PFCR1, (~((uint32) (DFLASH_PFCR1_B1_APC | DFLASH_PFCR1_B1_WWSC | \
            DFLASH_PFCR1_B1_RWSC))), (uint32) (ConfigLLDPtr->flashPFCR1));

    REG_WRITE32(FLASH_PFAPR, (uint32) (ConfigLLDPtr->flashPFAPR));
    /*lint -restore*/
  #endif
#endif
}

/**
@brief   This function configures clock dependent settings for the flash memory.
@details The function configures clock dependent settings like Address Pipelining Control,
         Write Wait State Control, Read Wait State Control.
@param[in]     Mcu_CFlash_Conf      Mcu code flash configuration value
@param[in]     Mcu_DFlash_Conf      Mcu data flash configuration value

@return Description of the returned value

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers MCU116
@remarks Implements 
 */
FUNC(void, MCU_RAM_CODE) Mcu_Flash_Configure_Ram(VAR(uint32, MCU_VAR) Mcu_CFlash_Conf, \
    VAR(uint32, MCU_VAR) Mcu_DFlash_Conf) {
    /* This is applicable for the following lines of code */
  
#ifdef IPV_FLASH
  #if (IPV_FLASH == IPV_FLASH_C90FL_2048_4_0_023) /* if XPC5668x */
    /** @remarks Covers MCU116 */
    /** @note Violates MISRA 2004  11.1 : See @ref Flash_Mcu_LLD_C_REF_3 above*/
    /*lint -save -e923*/
    REG_RMW32(PFCR0_FLASH, CFLASH_PFCR0_APC, Mcu_CFlash_Conf);
    REG_RMW32(PFCR0_FLASH, CFLASH_PFCR0_WWSC, Mcu_CFlash_Conf);
    REG_RMW32(PFCR0_FLASH, CFLASH_PFCR0_RWSC, Mcu_CFlash_Conf);

    REG_RMW32(PFCR1_FLASH, CFLASH_PFCR1_APC, Mcu_DFlash_Conf);
    REG_RMW32(PFCR1_FLASH, CFLASH_PFCR1_WWSC, Mcu_DFlash_Conf);
    REG_RMW32(PFCR1_FLASH, CFLASH_PFCR1_RWSC, Mcu_DFlash_Conf);
    /*lint -restore*/

  #elif ((IPV_FLASH == IPV_FLASH_C90FL3_1024_6_0) || \
         (IPV_FLASH == IPV_FLASH_C90FL_2048_4_0_Nh))  /* if XPC56XXL / XPC56EL70 */
  /* for MISRA */
    Mcu_DFlash_Conf = Mcu_DFlash_Conf;
    /** @remarks Covers MCU116 */
    /** @note Violates MISRA 2004  11.1 : See @ref Flash_Mcu_LLD_C_REF_3 above*/
    /*lint -save -e923*/
    REG_RMW32(CFLASH_PFCR0, CFLASH_PFCR0_B02_APC, Mcu_CFlash_Conf);
    REG_RMW32(CFLASH_PFCR0, CFLASH_PFCR0_B02_WWSC, Mcu_CFlash_Conf);
    REG_RMW32(CFLASH_PFCR0, CFLASH_PFCR0_B02_RWSC, Mcu_CFlash_Conf);
    /*lint -restore*/
  
  #elif ((IPV_FLASH == IPV_FLASH_C90FL_2048_4_0_238_2048_0_1_238)|| \
         (IPV_FLASH == IPV_FLASH_C90FL_2048_4_0) || (IPV_FLASH == IPV_FLASH_C90FL_640_34_61) || \
         (IPV_FLASH == IPV_FLASH_C90FL_2048_4_0_336)) /* if XPC56XXA / XPC56XXF / XPC5634M */
    /* for MISRA */
    Mcu_DFlash_Conf = Mcu_DFlash_Conf;
    /** @note Violates MISRA 2004  11.1 : See @ref Flash_Mcu_LLD_C_REF_3 above*/
    /*lint -save -e923*/
    if( (uint32)(Mcu_CFlash_Conf & FLASH_BIUCR0_APC) <  \
            (uint32)(REG_READ32(FLASH_BIUCR0) & FLASH_BIUCR0_APC ))
    {
        /** @remarks Covers MCU116 */
        REG_RMW32(FLASH_BIUCR0, FLASH_BIUCR0_RWSC, (Mcu_CFlash_Conf & FLASH_BIUCR0_RWSC));
        REG_RMW32(FLASH_BIUCR0, FLASH_BIUCR0_APC, (Mcu_CFlash_Conf & FLASH_BIUCR0_APC)); 
        REG_RMW32(FLASH_BIUCR0, FLASH_BIUCR0_RWSC, Mcu_CFlash_Conf);
    }
    else
    {
        /** @remarks Covers MCU116 */
        REG_RMW32(FLASH_BIUCR0, FLASH_BIUCR0_APC, (Mcu_CFlash_Conf & FLASH_BIUCR0_APC)); 
        REG_RMW32(FLASH_BIUCR0, FLASH_BIUCR0_RWSC, (Mcu_CFlash_Conf & FLASH_BIUCR0_RWSC));
        REG_RMW32(FLASH_BIUCR0, FLASH_BIUCR0_RWSC, Mcu_CFlash_Conf);       
    }
    /*lint -restore*/
  #elif ((IPV_FLASH == IPV_FLASH_C90FG_2_1568_2_6_1) || (IPV_FLASH == IPV_FLASH_C90FG_544_2_9_65) \
         || (IPV_FLASH == IPV_FLASH_C90FG_1568_2_6_69) \
         || (IPV_FLASH ==IPV_FLASH_C90FG_256_1_4_D)) /* if XPC564XB / XPC5604B / XPC5607B / XPC560XD*/
    /** @note Violates MISRA 2004  11.1 : See @ref Flash_Mcu_LLD_C_REF_3 above*/
    /*lint -save -e923*/
    if( (uint32)(Mcu_CFlash_Conf & CFLASH_PFCR0_B02_APC) <  \
            (uint32)(REG_READ32(CFLASH_PFCR0) & CFLASH_PFCR0_B02_APC ))
    {
        /** @remarks Covers MCU116 */
        REG_RMW32(CFLASH_PFCR0, CFLASH_PFCR0_B02_RWSC, (Mcu_CFlash_Conf & CFLASH_PFCR0_B02_RWSC));
        REG_RMW32(CFLASH_PFCR0, CFLASH_PFCR0_B02_APC, (Mcu_CFlash_Conf & CFLASH_PFCR0_B02_APC)); 
        REG_RMW32(DFLASH_PFCR1, DFLASH_PFCR1_B1_RWSC,(Mcu_DFlash_Conf & DFLASH_PFCR1_B1_RWSC)); 
        REG_RMW32(DFLASH_PFCR1, DFLASH_PFCR1_B1_APC, (Mcu_DFlash_Conf & DFLASH_PFCR1_B1_APC)); 
    }
    else
    {
        /** @remarks Covers MCU116 */
        REG_RMW32(CFLASH_PFCR0, CFLASH_PFCR0_B02_APC, (Mcu_CFlash_Conf & CFLASH_PFCR0_B02_APC)); 
        REG_RMW32(CFLASH_PFCR0, CFLASH_PFCR0_B02_RWSC, (Mcu_CFlash_Conf & CFLASH_PFCR0_B02_RWSC));
        REG_RMW32(DFLASH_PFCR1, DFLASH_PFCR1_B1_APC, (Mcu_DFlash_Conf & DFLASH_PFCR1_B1_APC)); 
        REG_RMW32(DFLASH_PFCR1, DFLASH_PFCR1_B1_RWSC,(Mcu_DFlash_Conf & DFLASH_PFCR1_B1_RWSC)); 
    }
    /*lint -restore*/
  /* if XPC560XP40/XPC560XP50/XPC560XP60/XPC5675K platforms */
  #elif ((IPV_FLASH == IPV_FLASH_C90FG_512_2_9) || (IPV_FLASH == IPV_FLASH_C90FG_256_1_4) || \
         (IPV_FLASH == IPV_FLASH_C90FG_1024_2_0) || (IPV_FLASH == IPV_FLASH_C90FG_1024_1_8))
    /** @note Violates MISRA 2004  11.1 : See @ref Flash_Mcu_LLD_C_REF_3 above*/
    /*lint -save -e923*/   
  if( (uint32)(Mcu_CFlash_Conf & CFLASH_PFCR0_B02_APC) <  (uint32)(REG_READ32(CFLASH_PFCR0) & \
        CFLASH_PFCR0_B02_APC ))
    {
        /** @remarks Covers MCU116 */
        REG_RMW32(CFLASH_PFCR0, CFLASH_PFCR0_B02_RWSC, (Mcu_CFlash_Conf & CFLASH_PFCR0_B02_RWSC));
        REG_RMW32(CFLASH_PFCR0, CFLASH_PFCR0_B02_APC, (Mcu_CFlash_Conf & CFLASH_PFCR0_B02_APC)); 
        REG_RMW32(CFLASH_PFCR0, CFLASH_PFCR0_B02_WWSC, (Mcu_CFlash_Conf & CFLASH_PFCR0_B02_WWSC)); 
        REG_RMW32(DFLASH_PFCR1, DFLASH_PFCR1_B1_RWSC,(Mcu_DFlash_Conf & DFLASH_PFCR1_B1_RWSC)); 
        REG_RMW32(DFLASH_PFCR1, DFLASH_PFCR1_B1_APC, (Mcu_DFlash_Conf & DFLASH_PFCR1_B1_APC)); 
        REG_RMW32(DFLASH_PFCR1, DFLASH_PFCR1_B1_WWSC, (Mcu_CFlash_Conf & DFLASH_PFCR1_B1_WWSC)); 
    }
    else
    {
        /** @remarks Covers MCU116 */
        REG_RMW32(CFLASH_PFCR0, CFLASH_PFCR0_B02_APC, (Mcu_CFlash_Conf & CFLASH_PFCR0_B02_APC)); 
        REG_RMW32(CFLASH_PFCR0, CFLASH_PFCR0_B02_RWSC, (Mcu_CFlash_Conf & CFLASH_PFCR0_B02_RWSC));
        REG_RMW32(CFLASH_PFCR0, CFLASH_PFCR0_B02_WWSC, (Mcu_CFlash_Conf & CFLASH_PFCR0_B02_WWSC)); 
        REG_RMW32(DFLASH_PFCR1, DFLASH_PFCR1_B1_APC, (Mcu_DFlash_Conf & DFLASH_PFCR1_B1_APC)); 
        REG_RMW32(DFLASH_PFCR1, DFLASH_PFCR1_B1_RWSC,(Mcu_DFlash_Conf & DFLASH_PFCR1_B1_RWSC)); 
        REG_RMW32(DFLASH_PFCR1, DFLASH_PFCR1_B1_WWSC, (Mcu_CFlash_Conf & DFLASH_PFCR1_B1_WWSC)); 
    }
     /*lint -restore*/
  #else    
    /** @remarks Covers MCU116 */
    /** @note Violates MISRA 2004  11.1 : See @ref Flash_Mcu_LLD_C_REF_3 above*/
    /*lint -save -e923*/
    REG_RMW32(CFLASH_PFCR0, CFLASH_PFCR0_B02_APC, Mcu_CFlash_Conf);
    REG_RMW32(CFLASH_PFCR0, CFLASH_PFCR0_B02_WWSC, Mcu_CFlash_Conf);
    REG_RMW32(CFLASH_PFCR0, CFLASH_PFCR0_B02_RWSC, Mcu_CFlash_Conf);

    REG_RMW32(DFLASH_PFCR1, DFLASH_PFCR1_B1_APC, Mcu_DFlash_Conf);
    REG_RMW32(DFLASH_PFCR1, DFLASH_PFCR1_B1_WWSC, Mcu_DFlash_Conf);
    REG_RMW32(DFLASH_PFCR1, DFLASH_PFCR1_B1_RWSC, Mcu_DFlash_Conf);
    /*lint -restore*/
  #endif
#endif
}

#define MCU_STOP_SEC_RAMCODE
/** @note Violates MISRA 2004  19.1, 19.15 :See @ref Flash_Mcu_LLD_C_REF_1, Flash_Mcu_LLD_C_REF_2 above*/
#include "MemMap.h"

#ifdef __cplusplus
}
#endif
