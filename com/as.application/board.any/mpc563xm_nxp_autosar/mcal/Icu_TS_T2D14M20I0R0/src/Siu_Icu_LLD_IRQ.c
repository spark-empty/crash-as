/**
    @file    SIU_Icu_LLD_IRQ.c
    @version 2.0.0

    @brief   AUTOSAR Icu - SIU source file support for ICU driver.
    @details SIU source file, containing the variables and functions that are exported by the SIU
             driver.

    Project AUTOSAR 3.0 MCAL
    Platform PA
    Peripheral eMIOS200
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
@file    Siu_Icu_LLD_IRQ.c
@remarks Implements DICU09000
*/
/**
@page misra_violations MISRA-C:2004 violations

@section Siu_Icu_LLD_IRQ_c_1
Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before "#include"
MemMap.h included after each section define in order to set the current memory section

@section Siu_Icu_LLD_IRQ_c_2
MISRA-C:2004  19.15 Precautions shall be taken in order to prevent the contents of a
header file being included twice.
This is not a violation since all header files are protected against multiple inclusions.

@section Siu_Icu_LLD_IRQ_c_3
MISRA 2004 Rule 11.3 cast from unsigned long to pointer [Encompasses MISRA 2004 Rule 11.1],
This rule can not be avoided because it appears when addressing memory mapped registers
or other hardware specific feature

@section Siu_Icu_LLD_IRQ_c_4
MISRA-C:2004 17.4: Array indexing shall be the only allowed form of pointer arithmetic.
This violation is due to the use of pointer arithematic, to access the channel parameters,
the indexing of the pointer is taken care and hence the unintended memory location will not
be accessed.


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
#include "Mcal.h"

#include "Reg_eSys_SIU.h"
#include "Siu_Icu_LLD.h"
#include "Siu_Icu_LLD_CfgEx.h"
#include "Icu_LLD.h"
#include "SchM_Icu.h"

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/** @remarks Covers BSW00374, BSW00318 */
#define SIU_ICU_LLD_IRQ_VENDOR_ID_C         43
#define SIU_ICU_LLD_IRQ_AR_MAJOR_VERSION_C  3
#define SIU_ICU_LLD_IRQ_AR_MINOR_VERSION_C  0
#define SIU_ICU_LLD_IRQ_AR_PATCH_VERSION_C  0
#define SIU_ICU_LLD_IRQ_SW_MAJOR_VERSION_C  2
#define SIU_ICU_LLD_IRQ_SW_MINOR_VERSION_C  0
#define SIU_ICU_LLD_IRQ_SW_PATCH_VERSION_C  0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and SIU_Icu_LLD.h file are of the same vendor */
#if (SIU_ICU_LLD_IRQ_VENDOR_ID_C != SIU_ICU_LLD_VENDOR_ID)
    #error "SIU_Icu_LLD_IRQ.c and SIU_Icu_LLD.h have different vendor IDs"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((SIU_ICU_LLD_IRQ_AR_MAJOR_VERSION_C != SIU_ICU_LLD_AR_MAJOR_VERSION) || \
         (SIU_ICU_LLD_IRQ_AR_MINOR_VERSION_C != SIU_ICU_LLD_AR_MINOR_VERSION) || \
         (SIU_ICU_LLD_IRQ_AR_PATCH_VERSION_C != SIU_ICU_LLD_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of SIU_Icu_LLD_IRQ.c and SIU_Icu_LLD.h are different"
    #endif
#endif
/* Check if source file and SIU_Icu_LLD.h header file are of the same Software version */
/** @remarks Covers ICU005 */
#if ((SIU_ICU_LLD_IRQ_SW_MAJOR_VERSION_C != SIU_ICU_LLD_SW_MAJOR_VERSION) || \
     (SIU_ICU_LLD_IRQ_SW_MINOR_VERSION_C != SIU_ICU_LLD_SW_MINOR_VERSION) || \
     (SIU_ICU_LLD_IRQ_SW_PATCH_VERSION_C != SIU_ICU_LLD_SW_PATCH_VERSION))
    #error "Software Version Numbers of SIU_Icu_LLD_IRQ.c and SIU_Icu_LLD.h are different"
#endif


/* Check if source file and Siu_Icu_LLD_CfgEx.h file are of the same vendor */
#if (SIU_ICU_LLD_IRQ_VENDOR_ID_C != SIU_ICU_LLD_CFG_EX_VENDOR_ID)
#error "SIU_Icu_LLD_IRQ.c and Siu_Icu_LLD_CfgEx.h have different vendor IDs"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((SIU_ICU_LLD_IRQ_AR_MAJOR_VERSION_C != SIU_ICU_LLD_CFG_EX_AR_MAJOR_VERSION) || \
         (SIU_ICU_LLD_IRQ_AR_MINOR_VERSION_C != SIU_ICU_LLD_CFG_EX_AR_MINOR_VERSION) || \
         (SIU_ICU_LLD_IRQ_AR_PATCH_VERSION_C != SIU_ICU_LLD_CFG_EX_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of SIU_Icu_LLD_IRQ.c and Siu_Icu_LLD_CfgEx.h are different"
    #endif
#endif
/* Check if source file and Siu_Icu_LLD_CfgEx.h file are of the same Software version */
/** @remarks Covers ICU005 */
#if ((SIU_ICU_LLD_IRQ_SW_MAJOR_VERSION_C != SIU_ICU_LLD_CFG_EX_SW_MAJOR_VERSION) || \
     (SIU_ICU_LLD_IRQ_SW_MINOR_VERSION_C != SIU_ICU_LLD_CFG_EX_SW_MINOR_VERSION) || \
     (SIU_ICU_LLD_IRQ_SW_PATCH_VERSION_C != SIU_ICU_LLD_CFG_EX_SW_PATCH_VERSION))
    #error "Software Version Numbers of SIU_Icu_LLD_IRQ.c and Siu_Icu_LLD_CfgEx.h are different"
#endif


/* Check if source file and Icu_LLD.h file are of the same vendor */
#if (SIU_ICU_LLD_IRQ_VENDOR_ID_C != ICU_LLD_VENDOR_ID)
    #error "SIU_Icu_LLD_IRQ.c and Icu_LLD.h have different vendor IDs"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((SIU_ICU_LLD_IRQ_AR_MAJOR_VERSION_C != ICU_LLD_AR_MAJOR_VERSION) || \
         (SIU_ICU_LLD_IRQ_AR_MINOR_VERSION_C != ICU_LLD_AR_MINOR_VERSION) || \
         (SIU_ICU_LLD_IRQ_AR_PATCH_VERSION_C != ICU_LLD_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of SIU_Icu_LLD_IRQ.c and Icu_LLD.h are different"
    #endif
#endif
/* Check if source file and ICU_LLD.h header file are of the same Software version */
/** @remarks Covers ICU005 */
#if ((SIU_ICU_LLD_IRQ_SW_MAJOR_VERSION_C != ICU_LLD_SW_MAJOR_VERSION) || \
     (SIU_ICU_LLD_IRQ_SW_MINOR_VERSION_C != ICU_LLD_SW_MINOR_VERSION) || \
     (SIU_ICU_LLD_IRQ_SW_PATCH_VERSION_C != ICU_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of SIU_Icu_LLD_IRQ.c and Icu_LLD.h are different"
#endif


/* Check if source file and Reg_eSys_SIU.h file are of the same vendor */
#if (SIU_ICU_LLD_IRQ_VENDOR_ID_C != SIU_VENDOR_ID_REG)
#error "SIU_Icu_LLD_IRQ.c and SIU_Icu_LLD.h have different vendor IDs"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((SIU_ICU_LLD_IRQ_AR_MAJOR_VERSION_C != SIU_AR_MAJOR_VERSION_REG) || \
         (SIU_ICU_LLD_IRQ_AR_MINOR_VERSION_C != SIU_AR_MINOR_VERSION_REG) || \
         (SIU_ICU_LLD_IRQ_AR_PATCH_VERSION_C != SIU_AR_PATCH_VERSION_REG))
    #error "AutoSar Version Numbers of SIU_Icu_LLD_IRQ.c and SIU_Icu_LLD.h are different"
    #endif
#endif
/* Check if source file and SIU_Icu_LLD.h header file are of the same Software version */
#if ((SIU_ICU_LLD_IRQ_SW_MAJOR_VERSION_C != SIU_SW_MAJOR_VERSION_REG) || \
     (SIU_ICU_LLD_IRQ_SW_MINOR_VERSION_C != SIU_SW_MINOR_VERSION_REG) || \
     (SIU_ICU_LLD_IRQ_SW_PATCH_VERSION_C != SIU_SW_PATCH_VERSION_REG))
#error "Software Version Numbers of SIU_Icu_LLD_IRQ.c and Reg_eSys_SIU.h are different"
#endif


#ifdef CHECK_AUTOSAR_VERSION
    #if ((SIU_ICU_LLD_IRQ_AR_MAJOR_VERSION_C != SCHM_ICU_AR_MAJOR_VERSION) || \
         (SIU_ICU_LLD_IRQ_AR_MINOR_VERSION_C != SCHM_ICU_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of SIU_Icu_LLD_IRQ.c and SchM_Icu.h are different"
    #endif
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
#define ICU_START_SEC_VAR_UNSPECIFIED
/**
@file  Siu_Icu_LLD_IRQ.c

@section Siu_Icu_LLD_IRQ_c_1
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
      "#include" See @ref Siu_Icu_LLD_IRQ_c_1


@section Siu_Icu_LLD_IRQ_c_2
MISRA-C:2004  19.15 Precautions shall be taken in order to prevent the contents of a
header file being included twice.
This is not a violation since all header files are protected against multiple inclusions.

@section Siu_Icu_LLD_IRQ_c_3
MISRA 2004 Rule 11.3 cast from unsigned long to pointer [Encompasses MISRA 2004 Rule 11.1],
This rule can not be avoided because it appears when addressing memory mapped registers
or other hardware specific feature

*/

#include "MemMap.h"
/*lint -restore*/


#define ICU_STOP_SEC_VAR_UNSPECIFIED
/**
@file  Siu_Icu_LLD_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
      "#include" See @ref Siu_Icu_LLD_IRQ_c_1 */
/*lint -save -e537 -e451*/
/**
@file  Siu_Icu_LLD_IRQ.c
@note  Violates MISRA 2004 Advisory Rule 19.15, Precautions shall be taken in order to prevent
       the contents of a header file being included twice. See @ref Siu_Icu_LLD_IRQ_c_2 */

#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
#define ICU_START_SEC_CODE
/**
@file  Siu_Icu_LLD_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
      "#include" See @ref Siu_Icu_LLD_IRQ_c_1 */
/**
@file  Siu_Icu_LLD_IRQ.c
@note  Violates MISRA 2004 Advisory Rule 19.15, Precautions shall be taken in order to prevent
       the contents of a header file being included twice. See @ref Siu_Icu_LLD_IRQ_c_2 */
#include "MemMap.h"

#if (defined ICU_IRQ_0_ISR_USED)
ISR(SIU_EXT_IRQ0);
#endif

#if (defined ICU_IRQ_1_ISR_USED)
ISR(SIU_EXT_IRQ1);
#endif

#if (defined ICU_IRQ_2_ISR_USED)
ISR(SIU_EXT_IRQ2);
#endif

#if (defined ICU_IRQ_3_ISR_USED)
ISR(SIU_EXT_IRQ3);
#endif

#if ((defined ICU_IRQ_4_ISR_USED)  || (defined ICU_IRQ_5_ISR_USED)  || \
     (defined ICU_IRQ_6_ISR_USED)  || (defined ICU_IRQ_7_ISR_USED)  || \
     (defined ICU_IRQ_8_ISR_USED)  || (defined ICU_IRQ_9_ISR_USED)  || \
     (defined ICU_IRQ_10_ISR_USED) || (defined ICU_IRQ_11_ISR_USED) || \
     (defined ICU_IRQ_12_ISR_USED) || (defined ICU_IRQ_13_ISR_USED) || \
     (defined ICU_IRQ_14_ISR_USED) || (defined ICU_IRQ_15_ISR_USED))
ISR(SIU_EXT_IRQ4_15);
#endif

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
/*lint -restore*/
#if ((defined ICU_IRQ_0_ISR_USED)||(defined ICU_IRQ_1_ISR_USED)||(defined ICU_IRQ_2_ISR_USED) || \
     (defined ICU_IRQ_3_ISR_USED))
INLINE FUNC(void, ICU_CODE) Siu_Icu_LLD_IRQ_ProcessInterrupt(CONST(uint8, AUTOMATIC) hwChannel)
{
    VAR(uint32, AUTOMATIC) reg_SIU_EISR = REG_READ32(SIU_EISR);
    /* Clear pending interrupt serviced */
    REG_WRITE32(SIU_EISR, SIU_CHANNEL_MASK(hwChannel));

    /* Process interrupt for ICU logical channel */

/**
@note  MISRA-C:2004 17.4: Array indexing shall be the only allowed form of pointer arithmetic.
       See @ref Siu_Icu_LLD_IRQ_c_4
*/
    Icu_ProcessCommonInterrupt(Icu_Cfg_Ptr->Icu_HWMap[IRQ_ICU_CHANNEL(hwChannel)], reg_SIU_EISR);
}
#endif
/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

#if (defined ICU_IRQ_0_ISR_USED)
ISR(SIU_EXT_IRQ0)
{
    Siu_Icu_LLD_IRQ_ProcessInterrupt(SIU_IRQ_0);
    /**
    @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref Siu_Icu_LLD_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif

#if (defined ICU_IRQ_1_ISR_USED)
ISR(SIU_EXT_IRQ1)
{
    Siu_Icu_LLD_IRQ_ProcessInterrupt(SIU_IRQ_1);
    /**
    @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref Siu_Icu_LLD_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif

#if (defined ICU_IRQ_2_ISR_USED)
ISR(SIU_EXT_IRQ2)
{
    Siu_Icu_LLD_IRQ_ProcessInterrupt(SIU_IRQ_2);
    /**
    @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref Siu_Icu_LLD_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif

#if (defined ICU_IRQ_3_ISR_USED)
ISR(SIU_EXT_IRQ3)
{
    Siu_Icu_LLD_IRQ_ProcessInterrupt(SIU_IRQ_3);
    /**
    @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref Siu_Icu_LLD_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif


#if ((defined ICU_IRQ_4_ISR_USED)  || (defined ICU_IRQ_5_ISR_USED)  || \
     (defined ICU_IRQ_6_ISR_USED)  || (defined ICU_IRQ_7_ISR_USED)  || \
     (defined ICU_IRQ_8_ISR_USED)  || (defined ICU_IRQ_9_ISR_USED)  || \
     (defined ICU_IRQ_10_ISR_USED) || (defined ICU_IRQ_11_ISR_USED) || \
     (defined ICU_IRQ_12_ISR_USED) || (defined ICU_IRQ_13_ISR_USED) || \
     (defined ICU_IRQ_14_ISR_USED) || (defined ICU_IRQ_15_ISR_USED))
ISR(SIU_EXT_IRQ4_15)
{
    VAR(uint8, ICU_VAR) irq_channel = SIU_IRQ_4;
    VAR(uint32, AUTOMATIC) channelMask = SIU_CHANNEL_MASK(SIU_IRQ_4);
    VAR(uint32, AUTOMATIC) reg_SIU_EISR = REG_READ32(SIU_EISR);
    VAR(uint32, AUTOMATIC) reg_irq_mask = SIU_IRQ4_IRQ15_MASK;

    /* Get only IRQ4 .. IRQ15 flags that has Interrupt enable bit set*/
    reg_irq_mask &= reg_SIU_EISR & REG_READ32(SIU_DIRER);
    /* Clear pending interrupt serviced */
    REG_WRITE32(SIU_EISR, reg_irq_mask );

    while(0x0U != reg_irq_mask)
    {
        if (0x0U != (reg_irq_mask & channelMask))
        {
            Icu_ProcessCommonInterrupt(Icu_Cfg_Ptr->Icu_HWMap[IRQ_ICU_CHANNEL(irq_channel)],
                               reg_SIU_EISR);
            /* clear the IRQ bit for current IRQ channel*/
            reg_irq_mask &= (uint32)(~channelMask);
        }
        irq_channel++;
        channelMask <<= (uint32)1;
    }
    /**
    @note  MISRA 2004 Rule 11.3 cast from unsigned long to pointer @ref Siu_Icu_LLD_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif

#define ICU_STOP_SEC_CODE
/**
@file  Siu_Icu_LLD_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
      "#include" See @ref Siu_Icu_LLD_IRQ_c_1 */

/**
@file  Siu_Icu_LLD_IRQ.c
@note  Violates MISRA 2004 Advisory Rule 19.15, Precautions shall be taken in order to prevent
       the contents of a header file being included twice. See @ref Siu_Icu_LLD_IRQ_c_2 */
#include "MemMap.h"
/*lint -restore*/


#ifdef __cplusplus
}
#endif

