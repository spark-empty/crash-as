/**
    @file eMIOS_Mcu_LLD.c
    @version 2.0.0

    @brief   AUTOSAR Mcu - eMIOS source file support for MCU driver.
    @details eMIOS source file, containing the variables and functions that are exported by the
             eMIOS driver.

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

@section eMIOS_Mcu_LLD_C_1
Violates  MISRA  2004 Advisory  Rule  19.1,  only preprocessor statements and comments before
'#include'
This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003

@section eMIOS_Mcu_LLD_C_2
MISRA-C:2004  19.15 Precautions shall be taken in order to prevent the contents of a
header file being included twice.
This is not a violation since all header files are protected against multiple inclusions.

@section eMIOS_Mcu_LLD_C_3
MISRA-C 2004  11.1 VIOLATION, cast from unsigned long to pointer.
The cast can not be avoided as it is used to access memory mapped registers.
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
#define EMIOS_MCU_LLD_VENDOR_ID_C           43

#define EMIOS_MCU_LLD_AR_MAJOR_VERSION_C    3
#define EMIOS_MCU_LLD_AR_MINOR_VERSION_C    0
#define EMIOS_MCU_LLD_AR_PATCH_VERSION_C    0
#define EMIOS_MCU_LLD_SW_MAJOR_VERSION_C    2
#define EMIOS_MCU_LLD_SW_MINOR_VERSION_C    0
#define EMIOS_MCU_LLD_SW_PATCH_VERSION_C    0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Mcu_LLD header file are of the same Autosar version */
    #if ((EMIOS_MCU_LLD_AR_MAJOR_VERSION_C != MCU_LLD_AR_MAJOR_VERSION) || \
         (EMIOS_MCU_LLD_AR_MINOR_VERSION_C != MCU_LLD_AR_MINOR_VERSION) || \
         (EMIOS_MCU_LLD_AR_PATCH_VERSION_C != MCU_LLD_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of eMIOS_Mcu_LLD.c and Mcu_LLD.h are different"
    #endif
#endif

/* Check if source file and Mcu_LLD header file are of the same Software version */
#if ((EMIOS_MCU_LLD_SW_MAJOR_VERSION_C != MCU_LLD_SW_MAJOR_VERSION) || \
     (EMIOS_MCU_LLD_SW_MINOR_VERSION_C != MCU_LLD_SW_MINOR_VERSION) || \
     (EMIOS_MCU_LLD_SW_PATCH_VERSION_C != MCU_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of eMIOS_Mcu_LLD.c and Mcu_LLD.h are different"
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
#define MCU_START_SEC_VAR_UNSPECIFIED
/** @note Violates MISRA 2004  19.1, 19.15 :See @ref eMIOS_Mcu_LLD_C_1, eMIOS_Mcu_LLD_C_2 above*/
/*lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/


#define MCU_STOP_SEC_VAR_UNSPECIFIED
/** @note Violates MISRA 2004  19.1, 19.15 :See @ref eMIOS_Mcu_LLD_C_1, eMIOS_Mcu_LLD_C_2 above*/
/*lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/



/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define MCU_START_SEC_CODE
/** @note Violates MISRA 2004  19.1, 19.15 :See @ref eMIOS_Mcu_LLD_C_1, eMIOS_Mcu_LLD_C_2 above*/
/*lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

/**
@brief      Initializes the EMIOS MCR register for EMIOS_A and EMIOS_B
@details function to initialize the Emios MCR register value configured

@param[in]      ClockPtr
*/

FUNC (void, MCU_CODE) Mcu_EMIOS_Init (P2CONST(Mcu_ClockConfigType, AUTOMATIC, MCU_APPL_DATA) \
       ClockPtr)
{
    /* Configure EMIOS_MCR*/
    /** @note Violates MISRA 2004  11.1 :See @ref eMIOS_Mcu_LLD_C_3 above*/    
    REG_WRITE32(EMIOS_MCR(0), ClockPtr->EMIOS_MCR);
}


#define MCU_STOP_SEC_CODE
/** @note Violates MISRA 2004  19.1, 19.15 :See @ref eMIOS_Mcu_LLD_C_1, eMIOS_Mcu_LLD_C_2 above*/
/*lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif
