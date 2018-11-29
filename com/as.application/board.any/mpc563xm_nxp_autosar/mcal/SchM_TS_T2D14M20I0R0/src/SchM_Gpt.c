/**
    @file    SchM_Gpt.c
    @version 2.0.0

    @brief   AUTOSAR SchM - module implementation.
    @details This module implements stubs for the AUTOSAR SchM
    
    Project AUTOSAR 3.0 MCAL
    Platform PA
    Peripheral 
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

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Std_Types.h"
#include "Mcal.h"
#include "SchM_Gpt.h"
#ifdef MCAL_TESTING_ENVIRONMENT
#include "EUnit.h" /* EUnit Test Suite */
#endif

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
#define SCHM_GPT_VENDOR_ID_C         43
#define SCHM_GPT_AR_MAJOR_VERSION_C  3
#define SCHM_GPT_AR_MINOR_VERSION_C  0
#define SCHM_GPT_AR_PATCH_VERSION_C  0
#define SCHM_GPT_SW_MAJOR_VERSION_C  2
#define SCHM_GPT_SW_MINOR_VERSION_C  0
#define SCHM_GPT_SW_PATCH_VERSION_C  0

#define ISR_ON(msr)                    (uint32)((uint32)(msr) & (uint32)(ISR_STATE_MASK)) 
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#ifdef CHECK_AUTOSAR_VERSION
/* Check if SchM_Gpt source file and Std_Types header file are of the same ASR version */
#if ((SCHM_GPT_AR_MAJOR_VERSION_C != STD_TYPES_AR_MAJOR_VERSION) || \
     (SCHM_GPT_AR_MINOR_VERSION_C != STD_TYPES_AR_MINOR_VERSION))
#error "AutoSar Version Numbers of SchM_Gpt.c and Std_Types.h are different"
#endif

/* No ASR version exported by Mcal.h header file - skip check*/

/* Check if SchM_Gpt source file and SchM_Gpt header file are of the same version */
#if ((SCHM_GPT_AR_MAJOR_VERSION_C != SCHM_GPT_AR_MAJOR_VERSION) || \
     (SCHM_GPT_AR_MINOR_VERSION_C != SCHM_GPT_AR_MINOR_VERSION) || \
     (SCHM_GPT_AR_PATCH_VERSION_C != SCHM_GPT_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of SchM_Gpt.c and SchM_Gpt.h are different"
#endif
#endif /*CHECK_AUTOSAR_VERSION*/

#if ((SCHM_GPT_SW_MAJOR_VERSION_C != SCHM_GPT_SW_MAJOR_VERSION) || \
     (SCHM_GPT_SW_MINOR_VERSION_C != SCHM_GPT_SW_MINOR_VERSION) || \
     (SCHM_GPT_SW_PATCH_VERSION_C != SCHM_GPT_SW_PATCH_VERSION))
#error "Software Version Numbers of SchM_Gpt.c and SchM_Gpt.h are different"
#endif

#if (SCHM_GPT_VENDOR_ID_C != SCHM_GPT_VENDOR_ID)
#error "SchM_Gpt.c and SchM_Gpt.h have different vendor ids"
#endif
/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/
#define ISR_STATE_MASK     ((uint32)0x00008000UL)   /**< @brief EE bit of MSR */

/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/
#ifndef SCHM_USE_MACROS
static uint32 msr_00;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_01;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_02;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_03;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_04;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_05;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_06;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_07;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_08;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_09;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_10;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_11;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_12;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_13;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_14;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_15;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_16;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_17;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_18;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_19;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_20;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_21;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_22;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_23;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_24;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_25;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_26;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_27;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_28;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_29;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_30;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_31;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_32;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_33;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_34;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_35;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_36;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_37;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_38;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_39;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_40;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_41;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_42;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_43;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_44;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_45;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_46;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_47;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_48;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_49;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_50;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_51;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_52;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_53;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_54;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_55;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_56;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_57;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_58;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_59;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_60;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_61;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_62;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_63;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_64;    /**< @brief exclusive area MSR state upon entering*/
static volatile uint32 reentry_guard_00 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_01 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_02 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_03 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_04 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_05 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_06 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_07 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_08 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_09 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_10 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_11 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_12 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_13 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_14 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_15 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_16 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_17 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_18 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_19 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_20 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_21 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_22 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_23 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_24 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_25 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_26 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_27 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_28 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_29 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_30 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_31 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_32 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_33 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_34 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_35 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_36 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_37 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_38 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_39 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_40 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_41 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_42 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_43 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_44 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_45 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_46 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_47 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_48 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_49 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_50 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_51 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_52 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_53 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_54 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_55 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_56 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_57 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_58 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_59 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_60 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_61 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_62 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_63 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_64 = 0; /**< @brief guard for the msr variable against overwrite*/
#endif /*SCHM_USE_MACROS*/

/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

#ifndef SCHM_USE_MACROS
#ifndef _COSMIC_C_MPC563XM_
/** 
@brief   This function returns the MSR register value (32 bits). 
@details This function returns the MSR register value (32 bits). 
    
@param[in]     void        No input parameters
@return        uint32 msr  This function returns the MSR register value (32 bits). 

@pre  None
@post None

@remarks Covers 
@remarks Implements 
*/
FUNC(uint32, SCHM_CODE) Gpt_schm_read_msr(void); 
#endif /*ifndef _COSMIC_C_MPC563XM_*/

FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_00(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_01(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_02(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_03(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_04(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_05(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_06(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_07(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_08(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_09(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_10(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_11(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_12(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_13(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_14(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_15(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_16(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_17(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_18(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_19(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_20(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_21(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_22(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_23(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_24(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_25(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_26(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_27(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_28(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_29(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_30(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_31(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_32(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_33(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_34(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_35(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_36(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_37(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_38(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_39(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_40(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_41(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_42(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_43(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_44(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_45(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_46(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_47(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_48(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_49(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_50(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_51(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_52(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_53(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_54(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_55(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_56(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_57(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_58(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_59(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_60(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_61(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_62(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_63(void);
FUNC(void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_64(void);

FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_00(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_01(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_02(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_03(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_04(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_05(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_06(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_07(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_08(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_09(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_10(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_11(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_12(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_13(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_14(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_15(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_16(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_17(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_18(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_19(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_20(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_21(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_22(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_23(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_24(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_25(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_26(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_27(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_28(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_29(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_30(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_31(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_32(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_33(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_34(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_35(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_36(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_37(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_38(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_39(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_40(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_41(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_42(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_43(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_44(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_45(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_46(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_47(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_48(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_49(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_50(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_51(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_52(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_53(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_54(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_55(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_56(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_57(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_58(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_59(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_60(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_61(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_62(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_63(void);
FUNC(void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_64(void);

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define SCHM_START_SEC_CODE
#include "MemMap.h"

#ifndef _COSMIC_C_MPC563XM_
/** 
@brief   This function returns the MSR register value (32 bits). 
@details This function returns the MSR register value (32 bits). 
    
@param[in]     void        No input parameters
@return        uint32 msr  This function returns the MSR register value (32 bits). 

@pre  None
@post None

@remarks Covers 
@remarks Implements 
*/
ASM_KEYWORD FUNC(uint32, SCHM_CODE) Gpt_schm_read_msr(void)
{
    mfmsr r3
}
#else  /*_COSMIC_C_MPC563XM_ compiler only*/
/** 
@brief   This macro returns the MSR register value (32 bits). 
@details This macro function implementation returns the MSR register value in r3 (32 bits). 
    
@pre  None
@post None

@remarks Covers 
@remarks Implements 
*/
#define Gpt_schm_read_msr() ASM_KEYWORD("mfmsr r3")
#endif /*#ifndef _COSMIC_C_MPC563XM_*/


/** 
@brief   This function is called to allow the BSW module to enter the critical region. 
@details This is a function stub only, implemented as a macro. The actual implementation will be 
         done by the MCAL integrator. The ENTER_##ExclusiveArea label is only used for profiling.
    
@param[in]     InstanceId         [INTEGR102],[INTEGR051] Parameter for identifying a unique instance of 
                                   the calling BSW module
                                  [INTEGR102], [INTEGR052] This parameter can be omitted in case there is 
                                   only one instance of the BSW module possible in the system. 
@param[in]     ExclusiveArea      [INTEGR053] Parameter for identifying a unique internal resource of the 
                                   BSW module. It will be different for each unique critical section used.  
@return        void               [INTEGR102] This function does not return anything

@pre  None
@post None

@remarks Covers 
@remarks Implements 
*/

FUNC (void, SCHM_CODE) SchM_Enter_Gpt(VAR(uint8, AUTOMATIC) Gpt_InstanceId, VAR(uint8, AUTOMATIC) Gpt_ExclusiveArea)
{

    if (Gpt_InstanceId == SCHM_GPT_INSTANCE_0)
    {
     
     switch (Gpt_ExclusiveArea) {
 
            case GPT_EXCLUSIVE_AREA_00: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_00(); 
                break;         
            case GPT_EXCLUSIVE_AREA_01: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_01(); 
                break;         
            case GPT_EXCLUSIVE_AREA_02: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_02(); 
                break;         
            case GPT_EXCLUSIVE_AREA_03: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_03(); 
                break;         
            case GPT_EXCLUSIVE_AREA_04: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_04(); 
                break;         
            case GPT_EXCLUSIVE_AREA_05: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_05(); 
                break;         
            case GPT_EXCLUSIVE_AREA_06: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_06(); 
                break;         
            case GPT_EXCLUSIVE_AREA_07: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_07(); 
                break;         
            case GPT_EXCLUSIVE_AREA_08: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_08(); 
                break;         
            case GPT_EXCLUSIVE_AREA_09: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_09(); 
                break;         
            case GPT_EXCLUSIVE_AREA_10: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_10(); 
                break;         
            case GPT_EXCLUSIVE_AREA_11: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_11(); 
                break;         
            case GPT_EXCLUSIVE_AREA_12: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_12(); 
                break;         
            case GPT_EXCLUSIVE_AREA_13: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_13(); 
                break;         
            case GPT_EXCLUSIVE_AREA_14: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_14(); 
                break;         
            case GPT_EXCLUSIVE_AREA_15: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_15(); 
                break;         
            case GPT_EXCLUSIVE_AREA_16: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_16(); 
                break;         
            case GPT_EXCLUSIVE_AREA_17: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_17(); 
                break;         
            case GPT_EXCLUSIVE_AREA_18: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_18(); 
                break;         
            case GPT_EXCLUSIVE_AREA_19: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_19(); 
                break;         
            case GPT_EXCLUSIVE_AREA_20: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_20(); 
                break;         
            case GPT_EXCLUSIVE_AREA_21: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_21(); 
                break;         
            case GPT_EXCLUSIVE_AREA_22: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_22(); 
                break;         
            case GPT_EXCLUSIVE_AREA_23: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_23(); 
                break;         
            case GPT_EXCLUSIVE_AREA_24: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_24(); 
                break;         
            case GPT_EXCLUSIVE_AREA_25: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_25(); 
                break;         
            case GPT_EXCLUSIVE_AREA_26: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_26(); 
                break;         
            case GPT_EXCLUSIVE_AREA_27: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_27(); 
                break;         
            case GPT_EXCLUSIVE_AREA_28: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_28(); 
                break;         
            case GPT_EXCLUSIVE_AREA_29: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_29(); 
                break;         
            case GPT_EXCLUSIVE_AREA_30: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_30(); 
                break;         
            case GPT_EXCLUSIVE_AREA_31: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_31(); 
                break;         
            case GPT_EXCLUSIVE_AREA_32: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_32(); 
                break;         
            case GPT_EXCLUSIVE_AREA_33: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_33(); 
                break;         
            case GPT_EXCLUSIVE_AREA_34: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_34(); 
                break;         
            case GPT_EXCLUSIVE_AREA_35: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_35(); 
                break;         
            case GPT_EXCLUSIVE_AREA_36: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_36(); 
                break;         
            case GPT_EXCLUSIVE_AREA_37: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_37(); 
                break;         
            case GPT_EXCLUSIVE_AREA_38: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_38(); 
                break;         
            case GPT_EXCLUSIVE_AREA_39: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_39(); 
                break;         
            case GPT_EXCLUSIVE_AREA_40: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_40(); 
                break;         
            case GPT_EXCLUSIVE_AREA_41: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_41(); 
                break;         
            case GPT_EXCLUSIVE_AREA_42: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_42(); 
                break;         
            case GPT_EXCLUSIVE_AREA_43: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_43(); 
                break;         
            case GPT_EXCLUSIVE_AREA_44: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_44(); 
                break;         
            case GPT_EXCLUSIVE_AREA_45: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_45(); 
                break;         
            case GPT_EXCLUSIVE_AREA_46: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_46(); 
                break;         
            case GPT_EXCLUSIVE_AREA_47: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_47(); 
                break;         
            case GPT_EXCLUSIVE_AREA_48: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_48(); 
                break;         
            case GPT_EXCLUSIVE_AREA_49: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_49(); 
                break;         
            case GPT_EXCLUSIVE_AREA_50: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_50(); 
                break;         
            case GPT_EXCLUSIVE_AREA_51: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_51(); 
                break;         
            case GPT_EXCLUSIVE_AREA_52: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_52(); 
                break;         
            case GPT_EXCLUSIVE_AREA_53: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_53(); 
                break;         
            case GPT_EXCLUSIVE_AREA_54: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_54(); 
                break;         
            case GPT_EXCLUSIVE_AREA_55: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_55(); 
                break;         
            case GPT_EXCLUSIVE_AREA_56: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_56(); 
                break;         
            case GPT_EXCLUSIVE_AREA_57: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_57(); 
                break;         
            case GPT_EXCLUSIVE_AREA_58: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_58(); 
                break;         
            case GPT_EXCLUSIVE_AREA_59: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_59(); 
                break;         
            case GPT_EXCLUSIVE_AREA_60: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_60(); 
                break;         
            case GPT_EXCLUSIVE_AREA_61: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_61(); 
                break;         
            case GPT_EXCLUSIVE_AREA_62: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_62(); 
                break;         
            case GPT_EXCLUSIVE_AREA_63: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_63(); 
                break;         
            case GPT_EXCLUSIVE_AREA_64: 
                SchM_Enter_GPT_EXCLUSIVE_AREA_64(); 
                break;         
 
            default:
                 /**
                 @brief the code reached this point because
                        SchM_Enter_Gpt was called with an invalid Gpt_ExclusiveArea
                 */
                while(1) {};  /*wait here for user debug intervention*/
                /*break; */
        }

    }

}




/** 
@brief   This function is called to allow the BSW module to exit the critical region. 
@details This is a function stub only, implemented as a macro. The actual implementation will be 
         done by the MCAL integrator. The EXIT_##ExclusiveArea label is only used for profiling.
    
@param[in]    InstanceId       [INTEGR103],[INTEGR054] Parameter for identifying a unique instance of 
                                the calling BSW module
                               [INTEGR103], [INTEGR056] This parameter can be omitted in case there is 
                                only one instance of the BSW module possible in the system. 
@param[in]    ExclusiveArea    [INTEGR055] Parameter for identifying a unique internal resource of the 
                                BSW module. It will be different for each unique critical section used.  
@return       void             [INTEGR103] This function does not return anything

@pre  None
@post None

@remarks Covers 
@remarks Implements    
*/

FUNC (void, SCHM_CODE) SchM_Exit_Gpt(VAR(uint8, AUTOMATIC) Gpt_InstanceId, VAR(uint8, AUTOMATIC) Gpt_ExclusiveArea)
{

    if (Gpt_InstanceId == SCHM_GPT_INSTANCE_0)
    {
     
     switch (Gpt_ExclusiveArea) {
    
            case GPT_EXCLUSIVE_AREA_00: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_00(); 
                break;  
            case GPT_EXCLUSIVE_AREA_01: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_01(); 
                break;  
            case GPT_EXCLUSIVE_AREA_02: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_02(); 
                break;  
            case GPT_EXCLUSIVE_AREA_03: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_03(); 
                break;  
            case GPT_EXCLUSIVE_AREA_04: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_04(); 
                break;  
            case GPT_EXCLUSIVE_AREA_05: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_05(); 
                break;  
            case GPT_EXCLUSIVE_AREA_06: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_06(); 
                break;  
            case GPT_EXCLUSIVE_AREA_07: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_07(); 
                break;  
            case GPT_EXCLUSIVE_AREA_08: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_08(); 
                break;  
            case GPT_EXCLUSIVE_AREA_09: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_09(); 
                break;  
            case GPT_EXCLUSIVE_AREA_10: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_10(); 
                break;  
            case GPT_EXCLUSIVE_AREA_11: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_11(); 
                break;  
            case GPT_EXCLUSIVE_AREA_12: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_12(); 
                break;  
            case GPT_EXCLUSIVE_AREA_13: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_13(); 
                break;  
            case GPT_EXCLUSIVE_AREA_14: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_14(); 
                break;  
            case GPT_EXCLUSIVE_AREA_15: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_15(); 
                break;  
            case GPT_EXCLUSIVE_AREA_16: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_16(); 
                break;  
            case GPT_EXCLUSIVE_AREA_17: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_17(); 
                break;  
            case GPT_EXCLUSIVE_AREA_18: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_18(); 
                break;  
            case GPT_EXCLUSIVE_AREA_19: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_19(); 
                break;  
            case GPT_EXCLUSIVE_AREA_20: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_20(); 
                break;  
            case GPT_EXCLUSIVE_AREA_21: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_21(); 
                break;  
            case GPT_EXCLUSIVE_AREA_22: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_22(); 
                break;  
            case GPT_EXCLUSIVE_AREA_23: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_23(); 
                break;  
            case GPT_EXCLUSIVE_AREA_24: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_24(); 
                break;  
            case GPT_EXCLUSIVE_AREA_25: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_25(); 
                break;  
            case GPT_EXCLUSIVE_AREA_26: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_26(); 
                break;  
            case GPT_EXCLUSIVE_AREA_27: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_27(); 
                break;  
            case GPT_EXCLUSIVE_AREA_28: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_28(); 
                break;  
            case GPT_EXCLUSIVE_AREA_29: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_29(); 
                break;  
            case GPT_EXCLUSIVE_AREA_30: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_30(); 
                break;  
            case GPT_EXCLUSIVE_AREA_31: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_31(); 
                break;  
            case GPT_EXCLUSIVE_AREA_32: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_32(); 
                break;  
            case GPT_EXCLUSIVE_AREA_33: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_33(); 
                break;  
            case GPT_EXCLUSIVE_AREA_34: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_34(); 
                break;  
            case GPT_EXCLUSIVE_AREA_35: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_35(); 
                break;  
            case GPT_EXCLUSIVE_AREA_36: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_36(); 
                break;  
            case GPT_EXCLUSIVE_AREA_37: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_37(); 
                break;  
            case GPT_EXCLUSIVE_AREA_38: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_38(); 
                break;  
            case GPT_EXCLUSIVE_AREA_39: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_39(); 
                break;  
            case GPT_EXCLUSIVE_AREA_40: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_40(); 
                break;  
            case GPT_EXCLUSIVE_AREA_41: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_41(); 
                break;  
            case GPT_EXCLUSIVE_AREA_42: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_42(); 
                break;  
            case GPT_EXCLUSIVE_AREA_43: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_43(); 
                break;  
            case GPT_EXCLUSIVE_AREA_44: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_44(); 
                break;  
            case GPT_EXCLUSIVE_AREA_45: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_45(); 
                break;  
            case GPT_EXCLUSIVE_AREA_46: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_46(); 
                break;  
            case GPT_EXCLUSIVE_AREA_47: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_47(); 
                break;  
            case GPT_EXCLUSIVE_AREA_48: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_48(); 
                break;  
            case GPT_EXCLUSIVE_AREA_49: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_49(); 
                break;  
            case GPT_EXCLUSIVE_AREA_50: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_50(); 
                break;  
            case GPT_EXCLUSIVE_AREA_51: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_51(); 
                break;  
            case GPT_EXCLUSIVE_AREA_52: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_52(); 
                break;  
            case GPT_EXCLUSIVE_AREA_53: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_53(); 
                break;  
            case GPT_EXCLUSIVE_AREA_54: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_54(); 
                break;  
            case GPT_EXCLUSIVE_AREA_55: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_55(); 
                break;  
            case GPT_EXCLUSIVE_AREA_56: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_56(); 
                break;  
            case GPT_EXCLUSIVE_AREA_57: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_57(); 
                break;  
            case GPT_EXCLUSIVE_AREA_58: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_58(); 
                break;  
            case GPT_EXCLUSIVE_AREA_59: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_59(); 
                break;  
            case GPT_EXCLUSIVE_AREA_60: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_60(); 
                break;  
            case GPT_EXCLUSIVE_AREA_61: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_61(); 
                break;  
            case GPT_EXCLUSIVE_AREA_62: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_62(); 
                break;  
            case GPT_EXCLUSIVE_AREA_63: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_63(); 
                break;  
            case GPT_EXCLUSIVE_AREA_64: 
                SchM_Exit_GPT_EXCLUSIVE_AREA_64(); 
                break;  

            default:
                 /**
                 @brief the code reached this point because
                        SchM_Exit_Gpt was called with an invalid Gpt_ExclusiveArea
                 */
                while(1) {}; /*wait here for user debug intervention*/
                /*break; */
 
        }
 
    }

}

/** 
@brief   This function is called to allow GPT to enter the specific critical region. 
@details This is a local function stub only. 
    
@param[in]     void     No input parameters
@return        void     This function does not return anything

@pre  None
@post None

@remarks Covers 
@remarks Implements 
*/
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_00(void)
{
        reentry_guard_00++;
        if(1UL == reentry_guard_00)
        {
           msr_00 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_00)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_01(void)
{
        reentry_guard_01++;
        if(1UL == reentry_guard_01)
        {
           msr_01 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_01)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_02(void)
{
        reentry_guard_02++;
        if(1UL == reentry_guard_02)
        {
           msr_02 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_02)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_03(void)
{
        reentry_guard_03++;
        if(1UL == reentry_guard_03)
        {
           msr_03 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_03)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_04(void)
{
        reentry_guard_04++;
        if(1UL == reentry_guard_04)
        {
           msr_04 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_04)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_05(void)
{
        reentry_guard_05++;
        if(1UL == reentry_guard_05)
        {
           msr_05 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_05)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_06(void)
{
        reentry_guard_06++;
        if(1UL == reentry_guard_06)
        {
           msr_06 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_06)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_07(void)
{
        reentry_guard_07++;
        if(1UL == reentry_guard_07)
        {
           msr_07 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_07)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_08(void)
{
        reentry_guard_08++;
        if(1UL == reentry_guard_08)
        {
           msr_08 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_08)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_09(void)
{
        reentry_guard_09++;
        if(1UL == reentry_guard_09)
        {
           msr_09 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_09)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_10(void)
{
        reentry_guard_10++;
        if(1UL == reentry_guard_10)
        {
           msr_10 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_10)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_11(void)
{
        reentry_guard_11++;
        if(1UL == reentry_guard_11)
        {
           msr_11 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_11)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_12(void)
{
        reentry_guard_12++;
        if(1UL == reentry_guard_12)
        {
           msr_12 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_12)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_13(void)
{
        reentry_guard_13++;
        if(1UL == reentry_guard_13)
        {
           msr_13 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_13)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_14(void)
{
        reentry_guard_14++;
        if(1UL == reentry_guard_14)
        {
           msr_14 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_14)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_15(void)
{
        reentry_guard_15++;
        if(1UL == reentry_guard_15)
        {
           msr_15 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_15)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_16(void)
{
        reentry_guard_16++;
        if(1UL == reentry_guard_16)
        {
           msr_16 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_16)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_17(void)
{
        reentry_guard_17++;
        if(1UL == reentry_guard_17)
        {
           msr_17 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_17)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_18(void)
{
        reentry_guard_18++;
        if(1UL == reentry_guard_18)
        {
           msr_18 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_18)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_19(void)
{
        reentry_guard_19++;
        if(1UL == reentry_guard_19)
        {
           msr_19 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_19)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_20(void)
{
        reentry_guard_20++;
        if(1UL == reentry_guard_20)
        {
           msr_20 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_20)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_21(void)
{
        reentry_guard_21++;
        if(1UL == reentry_guard_21)
        {
           msr_21 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_21)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_22(void)
{
        reentry_guard_22++;
        if(1UL == reentry_guard_22)
        {
           msr_22 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_22)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_23(void)
{
        reentry_guard_23++;
        if(1UL == reentry_guard_23)
        {
           msr_23 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_23)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_24(void)
{
        reentry_guard_24++;
        if(1UL == reentry_guard_24)
        {
           msr_24 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_24)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_25(void)
{
        reentry_guard_25++;
        if(1UL == reentry_guard_25)
        {
           msr_25 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_25)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_26(void)
{
        reentry_guard_26++;
        if(1UL == reentry_guard_26)
        {
           msr_26 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_26)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_27(void)
{
        reentry_guard_27++;
        if(1UL == reentry_guard_27)
        {
           msr_27 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_27)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_28(void)
{
        reentry_guard_28++;
        if(1UL == reentry_guard_28)
        {
           msr_28 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_28)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_29(void)
{
        reentry_guard_29++;
        if(1UL == reentry_guard_29)
        {
           msr_29 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_29)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_30(void)
{
        reentry_guard_30++;
        if(1UL == reentry_guard_30)
        {
           msr_30 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_30)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_31(void)
{
        reentry_guard_31++;
        if(1UL == reentry_guard_31)
        {
           msr_31 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_31)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_32(void)
{
        reentry_guard_32++;
        if(1UL == reentry_guard_32)
        {
           msr_32 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_32)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_33(void)
{
        reentry_guard_33++;
        if(1UL == reentry_guard_33)
        {
           msr_33 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_33)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_34(void)
{
        reentry_guard_34++;
        if(1UL == reentry_guard_34)
        {
           msr_34 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_34)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_35(void)
{
        reentry_guard_35++;
        if(1UL == reentry_guard_35)
        {
           msr_35 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_35)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_36(void)
{
        reentry_guard_36++;
        if(1UL == reentry_guard_36)
        {
           msr_36 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_36)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_37(void)
{
        reentry_guard_37++;
        if(1UL == reentry_guard_37)
        {
           msr_37 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_37)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_38(void)
{
        reentry_guard_38++;
        if(1UL == reentry_guard_38)
        {
           msr_38 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_38)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_39(void)
{
        reentry_guard_39++;
        if(1UL == reentry_guard_39)
        {
           msr_39 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_39)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_40(void)
{
        reentry_guard_40++;
        if(1UL == reentry_guard_40)
        {
           msr_40 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_40)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_41(void)
{
        reentry_guard_41++;
        if(1UL == reentry_guard_41)
        {
           msr_41 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_41)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_42(void)
{
        reentry_guard_42++;
        if(1UL == reentry_guard_42)
        {
           msr_42 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_42)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_43(void)
{
        reentry_guard_43++;
        if(1UL == reentry_guard_43)
        {
           msr_43 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_43)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_44(void)
{
        reentry_guard_44++;
        if(1UL == reentry_guard_44)
        {
           msr_44 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_44)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_45(void)
{
        reentry_guard_45++;
        if(1UL == reentry_guard_45)
        {
           msr_45 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_45)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_46(void)
{
        reentry_guard_46++;
        if(1UL == reentry_guard_46)
        {
           msr_46 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_46)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_47(void)
{
        reentry_guard_47++;
        if(1UL == reentry_guard_47)
        {
           msr_47 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_47)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_48(void)
{
        reentry_guard_48++;
        if(1UL == reentry_guard_48)
        {
           msr_48 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_48)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_49(void)
{
        reentry_guard_49++;
        if(1UL == reentry_guard_49)
        {
           msr_49 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_49)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_50(void)
{
        reentry_guard_50++;
        if(1UL == reentry_guard_50)
        {
           msr_50 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_50)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_51(void)
{
        reentry_guard_51++;
        if(1UL == reentry_guard_51)
        {
           msr_51 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_51)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_52(void)
{
        reentry_guard_52++;
        if(1UL == reentry_guard_52)
        {
           msr_52 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_52)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_53(void)
{
        reentry_guard_53++;
        if(1UL == reentry_guard_53)
        {
           msr_53 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_53)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_54(void)
{
        reentry_guard_54++;
        if(1UL == reentry_guard_54)
        {
           msr_54 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_54)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_55(void)
{
        reentry_guard_55++;
        if(1UL == reentry_guard_55)
        {
           msr_55 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_55)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_56(void)
{
        reentry_guard_56++;
        if(1UL == reentry_guard_56)
        {
           msr_56 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_56)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_57(void)
{
        reentry_guard_57++;
        if(1UL == reentry_guard_57)
        {
           msr_57 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_57)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_58(void)
{
        reentry_guard_58++;
        if(1UL == reentry_guard_58)
        {
           msr_58 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_58)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_59(void)
{
        reentry_guard_59++;
        if(1UL == reentry_guard_59)
        {
           msr_59 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_59)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_60(void)
{
        reentry_guard_60++;
        if(1UL == reentry_guard_60)
        {
           msr_60 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_60)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_61(void)
{
        reentry_guard_61++;
        if(1UL == reentry_guard_61)
        {
           msr_61 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_61)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_62(void)
{
        reentry_guard_62++;
        if(1UL == reentry_guard_62)
        {
           msr_62 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_62)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_63(void)
{
        reentry_guard_63++;
        if(1UL == reentry_guard_63)
        {
           msr_63 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_63)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
FUNC (void, SCHM_CODE) SchM_Enter_GPT_EXCLUSIVE_AREA_64(void)
{
        reentry_guard_64++;
        if(1UL == reentry_guard_64)
        {
           msr_64 = Gpt_schm_read_msr();  /*read MSR (to store interrupts state)*/
           if (ISR_ON(msr_64)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
           {
             SuspendAllInterrupts();
           }
        }
}
/** 
@brief   This function is called to allow GPT to exit the specific critical region. 
@details This is a local function stub only. It will resume interrupts if no other 
         critical area is still executing.
    
@param[in]     void     No input parameters
@return        void     This function does not return anything

@pre  None
@post None

@remarks Covers 
@remarks Implements    
*/
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_00(void)
{
    reentry_guard_00--;
    if ((ISR_ON(msr_00))&&(0UL == reentry_guard_00))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_01(void)
{
    reentry_guard_01--;
    if ((ISR_ON(msr_01))&&(0UL == reentry_guard_01))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_02(void)
{
    reentry_guard_02--;
    if ((ISR_ON(msr_02))&&(0UL == reentry_guard_02))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_03(void)
{
    reentry_guard_03--;
    if ((ISR_ON(msr_03))&&(0UL == reentry_guard_03))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_04(void)
{
    reentry_guard_04--;
    if ((ISR_ON(msr_04))&&(0UL == reentry_guard_04))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_05(void)
{
    reentry_guard_05--;
    if ((ISR_ON(msr_05))&&(0UL == reentry_guard_05))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_06(void)
{
    reentry_guard_06--;
    if ((ISR_ON(msr_06))&&(0UL == reentry_guard_06))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_07(void)
{
    reentry_guard_07--;
    if ((ISR_ON(msr_07))&&(0UL == reentry_guard_07))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_08(void)
{
    reentry_guard_08--;
    if ((ISR_ON(msr_08))&&(0UL == reentry_guard_08))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_09(void)
{
    reentry_guard_09--;
    if ((ISR_ON(msr_09))&&(0UL == reentry_guard_09))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_10(void)
{
    reentry_guard_10--;
    if ((ISR_ON(msr_10))&&(0UL == reentry_guard_10))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_11(void)
{
    reentry_guard_11--;
    if ((ISR_ON(msr_11))&&(0UL == reentry_guard_11))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_12(void)
{
    reentry_guard_12--;
    if ((ISR_ON(msr_12))&&(0UL == reentry_guard_12))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_13(void)
{
    reentry_guard_13--;
    if ((ISR_ON(msr_13))&&(0UL == reentry_guard_13))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_14(void)
{
    reentry_guard_14--;
    if ((ISR_ON(msr_14))&&(0UL == reentry_guard_14))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_15(void)
{
    reentry_guard_15--;
    if ((ISR_ON(msr_15))&&(0UL == reentry_guard_15))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_16(void)
{
    reentry_guard_16--;
    if ((ISR_ON(msr_16))&&(0UL == reentry_guard_16))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_17(void)
{
    reentry_guard_17--;
    if ((ISR_ON(msr_17))&&(0UL == reentry_guard_17))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_18(void)
{
    reentry_guard_18--;
    if ((ISR_ON(msr_18))&&(0UL == reentry_guard_18))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_19(void)
{
    reentry_guard_19--;
    if ((ISR_ON(msr_19))&&(0UL == reentry_guard_19))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_20(void)
{
    reentry_guard_20--;
    if ((ISR_ON(msr_20))&&(0UL == reentry_guard_20))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_21(void)
{
    reentry_guard_21--;
    if ((ISR_ON(msr_21))&&(0UL == reentry_guard_21))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_22(void)
{
    reentry_guard_22--;
    if ((ISR_ON(msr_22))&&(0UL == reentry_guard_22))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_23(void)
{
    reentry_guard_23--;
    if ((ISR_ON(msr_23))&&(0UL == reentry_guard_23))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_24(void)
{
    reentry_guard_24--;
    if ((ISR_ON(msr_24))&&(0UL == reentry_guard_24))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_25(void)
{
    reentry_guard_25--;
    if ((ISR_ON(msr_25))&&(0UL == reentry_guard_25))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_26(void)
{
    reentry_guard_26--;
    if ((ISR_ON(msr_26))&&(0UL == reentry_guard_26))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_27(void)
{
    reentry_guard_27--;
    if ((ISR_ON(msr_27))&&(0UL == reentry_guard_27))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_28(void)
{
    reentry_guard_28--;
    if ((ISR_ON(msr_28))&&(0UL == reentry_guard_28))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_29(void)
{
    reentry_guard_29--;
    if ((ISR_ON(msr_29))&&(0UL == reentry_guard_29))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_30(void)
{
    reentry_guard_30--;
    if ((ISR_ON(msr_30))&&(0UL == reentry_guard_30))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_31(void)
{
    reentry_guard_31--;
    if ((ISR_ON(msr_31))&&(0UL == reentry_guard_31))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_32(void)
{
    reentry_guard_32--;
    if ((ISR_ON(msr_32))&&(0UL == reentry_guard_32))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_33(void)
{
    reentry_guard_33--;
    if ((ISR_ON(msr_33))&&(0UL == reentry_guard_33))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_34(void)
{
    reentry_guard_34--;
    if ((ISR_ON(msr_34))&&(0UL == reentry_guard_34))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_35(void)
{
    reentry_guard_35--;
    if ((ISR_ON(msr_35))&&(0UL == reentry_guard_35))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_36(void)
{
    reentry_guard_36--;
    if ((ISR_ON(msr_36))&&(0UL == reentry_guard_36))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_37(void)
{
    reentry_guard_37--;
    if ((ISR_ON(msr_37))&&(0UL == reentry_guard_37))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_38(void)
{
    reentry_guard_38--;
    if ((ISR_ON(msr_38))&&(0UL == reentry_guard_38))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_39(void)
{
    reentry_guard_39--;
    if ((ISR_ON(msr_39))&&(0UL == reentry_guard_39))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_40(void)
{
    reentry_guard_40--;
    if ((ISR_ON(msr_40))&&(0UL == reentry_guard_40))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_41(void)
{
    reentry_guard_41--;
    if ((ISR_ON(msr_41))&&(0UL == reentry_guard_41))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_42(void)
{
    reentry_guard_42--;
    if ((ISR_ON(msr_42))&&(0UL == reentry_guard_42))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_43(void)
{
    reentry_guard_43--;
    if ((ISR_ON(msr_43))&&(0UL == reentry_guard_43))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_44(void)
{
    reentry_guard_44--;
    if ((ISR_ON(msr_44))&&(0UL == reentry_guard_44))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_45(void)
{
    reentry_guard_45--;
    if ((ISR_ON(msr_45))&&(0UL == reentry_guard_45))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_46(void)
{
    reentry_guard_46--;
    if ((ISR_ON(msr_46))&&(0UL == reentry_guard_46))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_47(void)
{
    reentry_guard_47--;
    if ((ISR_ON(msr_47))&&(0UL == reentry_guard_47))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_48(void)
{
    reentry_guard_48--;
    if ((ISR_ON(msr_48))&&(0UL == reentry_guard_48))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_49(void)
{
    reentry_guard_49--;
    if ((ISR_ON(msr_49))&&(0UL == reentry_guard_49))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_50(void)
{
    reentry_guard_50--;
    if ((ISR_ON(msr_50))&&(0UL == reentry_guard_50))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_51(void)
{
    reentry_guard_51--;
    if ((ISR_ON(msr_51))&&(0UL == reentry_guard_51))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_52(void)
{
    reentry_guard_52--;
    if ((ISR_ON(msr_52))&&(0UL == reentry_guard_52))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_53(void)
{
    reentry_guard_53--;
    if ((ISR_ON(msr_53))&&(0UL == reentry_guard_53))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_54(void)
{
    reentry_guard_54--;
    if ((ISR_ON(msr_54))&&(0UL == reentry_guard_54))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_55(void)
{
    reentry_guard_55--;
    if ((ISR_ON(msr_55))&&(0UL == reentry_guard_55))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_56(void)
{
    reentry_guard_56--;
    if ((ISR_ON(msr_56))&&(0UL == reentry_guard_56))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_57(void)
{
    reentry_guard_57--;
    if ((ISR_ON(msr_57))&&(0UL == reentry_guard_57))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_58(void)
{
    reentry_guard_58--;
    if ((ISR_ON(msr_58))&&(0UL == reentry_guard_58))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_59(void)
{
    reentry_guard_59--;
    if ((ISR_ON(msr_59))&&(0UL == reentry_guard_59))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_60(void)
{
    reentry_guard_60--;
    if ((ISR_ON(msr_60))&&(0UL == reentry_guard_60))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_61(void)
{
    reentry_guard_61--;
    if ((ISR_ON(msr_61))&&(0UL == reentry_guard_61))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_62(void)
{
    reentry_guard_62--;
    if ((ISR_ON(msr_62))&&(0UL == reentry_guard_62))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_63(void)
{
    reentry_guard_63--;
    if ((ISR_ON(msr_63))&&(0UL == reentry_guard_63))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}
FUNC (void, SCHM_CODE) SchM_Exit_GPT_EXCLUSIVE_AREA_64(void)
{
    reentry_guard_64--;
    if ((ISR_ON(msr_64))&&(0UL == reentry_guard_64))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
    }
}

#ifdef MCAL_TESTING_ENVIRONMENT
/** 
@brief   This function checks that all entered exclusive areas were also exited. 
@details This function checks that all entered exclusive areas were also exited. The check
         is done by verifying that all reentry_guard_* static variables are back to the
         zero value.
    
@param[in]     void       No input parameters
@return        void       This function does not return a value. Test asserts are used instead. 

@pre  None
@post None

@remarks Covers 
@remarks Implements 
*/
FUNC(void, SCHM_CODE) SchM_Check_gpt(void)
{
    EU_ASSERT(0UL == reentry_guard_00);
    EU_ASSERT(0UL == reentry_guard_01);
    EU_ASSERT(0UL == reentry_guard_02);
    EU_ASSERT(0UL == reentry_guard_03);
    EU_ASSERT(0UL == reentry_guard_04);
    EU_ASSERT(0UL == reentry_guard_05);
    EU_ASSERT(0UL == reentry_guard_06);
    EU_ASSERT(0UL == reentry_guard_07);
    EU_ASSERT(0UL == reentry_guard_08);
    EU_ASSERT(0UL == reentry_guard_09);
    EU_ASSERT(0UL == reentry_guard_10);
    EU_ASSERT(0UL == reentry_guard_11);
    EU_ASSERT(0UL == reentry_guard_12);
    EU_ASSERT(0UL == reentry_guard_13);
    EU_ASSERT(0UL == reentry_guard_14);
    EU_ASSERT(0UL == reentry_guard_15);
    EU_ASSERT(0UL == reentry_guard_16);
    EU_ASSERT(0UL == reentry_guard_17);
    EU_ASSERT(0UL == reentry_guard_18);
    EU_ASSERT(0UL == reentry_guard_19);
    EU_ASSERT(0UL == reentry_guard_20);
    EU_ASSERT(0UL == reentry_guard_21);
    EU_ASSERT(0UL == reentry_guard_22);
    EU_ASSERT(0UL == reentry_guard_23);
    EU_ASSERT(0UL == reentry_guard_24);
    EU_ASSERT(0UL == reentry_guard_25);
    EU_ASSERT(0UL == reentry_guard_26);
    EU_ASSERT(0UL == reentry_guard_27);
    EU_ASSERT(0UL == reentry_guard_28);
    EU_ASSERT(0UL == reentry_guard_29);
    EU_ASSERT(0UL == reentry_guard_30);
    EU_ASSERT(0UL == reentry_guard_31);
    EU_ASSERT(0UL == reentry_guard_32);
    EU_ASSERT(0UL == reentry_guard_33);
    EU_ASSERT(0UL == reentry_guard_34);
    EU_ASSERT(0UL == reentry_guard_35);
    EU_ASSERT(0UL == reentry_guard_36);
    EU_ASSERT(0UL == reentry_guard_37);
    EU_ASSERT(0UL == reentry_guard_38);
    EU_ASSERT(0UL == reentry_guard_39);
    EU_ASSERT(0UL == reentry_guard_40);
    EU_ASSERT(0UL == reentry_guard_41);
    EU_ASSERT(0UL == reentry_guard_42);
    EU_ASSERT(0UL == reentry_guard_43);
    EU_ASSERT(0UL == reentry_guard_44);
    EU_ASSERT(0UL == reentry_guard_45);
    EU_ASSERT(0UL == reentry_guard_46);
    EU_ASSERT(0UL == reentry_guard_47);
    EU_ASSERT(0UL == reentry_guard_48);
    EU_ASSERT(0UL == reentry_guard_49);
    EU_ASSERT(0UL == reentry_guard_50);
    EU_ASSERT(0UL == reentry_guard_51);
    EU_ASSERT(0UL == reentry_guard_52);
    EU_ASSERT(0UL == reentry_guard_53);
    EU_ASSERT(0UL == reentry_guard_54);
    EU_ASSERT(0UL == reentry_guard_55);
    EU_ASSERT(0UL == reentry_guard_56);
    EU_ASSERT(0UL == reentry_guard_57);
    EU_ASSERT(0UL == reentry_guard_58);
    EU_ASSERT(0UL == reentry_guard_59);
    EU_ASSERT(0UL == reentry_guard_60);
    EU_ASSERT(0UL == reentry_guard_61);
    EU_ASSERT(0UL == reentry_guard_62);
    EU_ASSERT(0UL == reentry_guard_63);
    EU_ASSERT(0UL == reentry_guard_64);
    reentry_guard_00 = 0UL; /*reset reentry_guard_00 for the next test in the suite*/
    reentry_guard_01 = 0UL; /*reset reentry_guard_01 for the next test in the suite*/
    reentry_guard_02 = 0UL; /*reset reentry_guard_02 for the next test in the suite*/
    reentry_guard_03 = 0UL; /*reset reentry_guard_03 for the next test in the suite*/
    reentry_guard_04 = 0UL; /*reset reentry_guard_04 for the next test in the suite*/
    reentry_guard_05 = 0UL; /*reset reentry_guard_05 for the next test in the suite*/
    reentry_guard_06 = 0UL; /*reset reentry_guard_06 for the next test in the suite*/
    reentry_guard_07 = 0UL; /*reset reentry_guard_07 for the next test in the suite*/
    reentry_guard_08 = 0UL; /*reset reentry_guard_08 for the next test in the suite*/
    reentry_guard_09 = 0UL; /*reset reentry_guard_09 for the next test in the suite*/
    reentry_guard_10 = 0UL; /*reset reentry_guard_10 for the next test in the suite*/
    reentry_guard_11 = 0UL; /*reset reentry_guard_11 for the next test in the suite*/
    reentry_guard_12 = 0UL; /*reset reentry_guard_12 for the next test in the suite*/
    reentry_guard_13 = 0UL; /*reset reentry_guard_13 for the next test in the suite*/
    reentry_guard_14 = 0UL; /*reset reentry_guard_14 for the next test in the suite*/
    reentry_guard_15 = 0UL; /*reset reentry_guard_15 for the next test in the suite*/
    reentry_guard_16 = 0UL; /*reset reentry_guard_16 for the next test in the suite*/
    reentry_guard_17 = 0UL; /*reset reentry_guard_17 for the next test in the suite*/
    reentry_guard_18 = 0UL; /*reset reentry_guard_18 for the next test in the suite*/
    reentry_guard_19 = 0UL; /*reset reentry_guard_19 for the next test in the suite*/
    reentry_guard_20 = 0UL; /*reset reentry_guard_20 for the next test in the suite*/
    reentry_guard_21 = 0UL; /*reset reentry_guard_21 for the next test in the suite*/
    reentry_guard_22 = 0UL; /*reset reentry_guard_22 for the next test in the suite*/
    reentry_guard_23 = 0UL; /*reset reentry_guard_23 for the next test in the suite*/
    reentry_guard_24 = 0UL; /*reset reentry_guard_24 for the next test in the suite*/
    reentry_guard_25 = 0UL; /*reset reentry_guard_25 for the next test in the suite*/
    reentry_guard_26 = 0UL; /*reset reentry_guard_26 for the next test in the suite*/
    reentry_guard_27 = 0UL; /*reset reentry_guard_27 for the next test in the suite*/
    reentry_guard_28 = 0UL; /*reset reentry_guard_28 for the next test in the suite*/
    reentry_guard_29 = 0UL; /*reset reentry_guard_29 for the next test in the suite*/
    reentry_guard_30 = 0UL; /*reset reentry_guard_30 for the next test in the suite*/
    reentry_guard_31 = 0UL; /*reset reentry_guard_31 for the next test in the suite*/
    reentry_guard_32 = 0UL; /*reset reentry_guard_32 for the next test in the suite*/
    reentry_guard_33 = 0UL; /*reset reentry_guard_33 for the next test in the suite*/
    reentry_guard_34 = 0UL; /*reset reentry_guard_34 for the next test in the suite*/
    reentry_guard_35 = 0UL; /*reset reentry_guard_35 for the next test in the suite*/
    reentry_guard_36 = 0UL; /*reset reentry_guard_36 for the next test in the suite*/
    reentry_guard_37 = 0UL; /*reset reentry_guard_37 for the next test in the suite*/
    reentry_guard_38 = 0UL; /*reset reentry_guard_38 for the next test in the suite*/
    reentry_guard_39 = 0UL; /*reset reentry_guard_39 for the next test in the suite*/
    reentry_guard_40 = 0UL; /*reset reentry_guard_40 for the next test in the suite*/
    reentry_guard_41 = 0UL; /*reset reentry_guard_41 for the next test in the suite*/
    reentry_guard_42 = 0UL; /*reset reentry_guard_42 for the next test in the suite*/
    reentry_guard_43 = 0UL; /*reset reentry_guard_43 for the next test in the suite*/
    reentry_guard_44 = 0UL; /*reset reentry_guard_44 for the next test in the suite*/
    reentry_guard_45 = 0UL; /*reset reentry_guard_45 for the next test in the suite*/
    reentry_guard_46 = 0UL; /*reset reentry_guard_46 for the next test in the suite*/
    reentry_guard_47 = 0UL; /*reset reentry_guard_47 for the next test in the suite*/
    reentry_guard_48 = 0UL; /*reset reentry_guard_48 for the next test in the suite*/
    reentry_guard_49 = 0UL; /*reset reentry_guard_49 for the next test in the suite*/
    reentry_guard_50 = 0UL; /*reset reentry_guard_50 for the next test in the suite*/
    reentry_guard_51 = 0UL; /*reset reentry_guard_51 for the next test in the suite*/
    reentry_guard_52 = 0UL; /*reset reentry_guard_52 for the next test in the suite*/
    reentry_guard_53 = 0UL; /*reset reentry_guard_53 for the next test in the suite*/
    reentry_guard_54 = 0UL; /*reset reentry_guard_54 for the next test in the suite*/
    reentry_guard_55 = 0UL; /*reset reentry_guard_55 for the next test in the suite*/
    reentry_guard_56 = 0UL; /*reset reentry_guard_56 for the next test in the suite*/
    reentry_guard_57 = 0UL; /*reset reentry_guard_57 for the next test in the suite*/
    reentry_guard_58 = 0UL; /*reset reentry_guard_58 for the next test in the suite*/
    reentry_guard_59 = 0UL; /*reset reentry_guard_59 for the next test in the suite*/
    reentry_guard_60 = 0UL; /*reset reentry_guard_60 for the next test in the suite*/
    reentry_guard_61 = 0UL; /*reset reentry_guard_61 for the next test in the suite*/
    reentry_guard_62 = 0UL; /*reset reentry_guard_62 for the next test in the suite*/
    reentry_guard_63 = 0UL; /*reset reentry_guard_63 for the next test in the suite*/
    reentry_guard_64 = 0UL; /*reset reentry_guard_64 for the next test in the suite*/
}
#endif /*MCAL_TESTING_ENVIRONMENT*/

#define SCHM_STOP_SEC_CODE
#include "MemMap.h"

#endif /*SCHM_USE_MACROS*/

#ifdef __cplusplus
}
#endif
