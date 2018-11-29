/**
    @file    Reg_eSys_EMIOS_IRQ.c
    @version 2.0.0

    @brief   AUTOSAR Pwm - EMIOS common low level driver.
    @details EMIOS common low level driver.

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
@file    Reg_eSys_EMIOS_IRQ.c
*/
/**
@page misra_violations MISRA-C:2004 violations

@section Reg_eSys_EMIOS_IRQ_c_1
Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before "#include"
MemMap.h included after each section define in order to set the current memory section

@section Reg_eSys_EMIOS_IRQ_c_2
Violates MISRA 2004 Advisory Rule 19.15 : Repeated include file
This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement
MEMMAP003.

@section Reg_eSys_EMIOS_IRQ_c_3
Violates MISRA 2004 Advisory Rule 11.1 : cast from unsigned int to pointer.
This violation is due to the Casting pointers to other types used in macros
for Reading or writing data from address location of controller register


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
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note  Violates MISRA 2004 Advisory Rule 19.15, Precautions shall be taken in order to prevent
       the contents of a header file being included twice. See @ref Reg_eSys_EMIOS_IRQ_c_2 */
/*lint -save -e537*/
#include "Std_Types.h"
/*lint -restore*/
#include "modules.h"
#include "Reg_eSys.h"
#include "Reg_eSys_EMIOS.h"
#include "Reg_eSys_EMIOS_CfgEx.h"


#if (USE_GPT_MODULE==STD_ON)
#include "Gpt.h"
#include "Gpt_LLD.h"
#endif

#if (USE_PWM_MODULE==STD_ON)
#include "Pwm.h"
#include "Pwm_LLD.h"
#endif

#if (USE_ICU_MODULE==STD_ON)
#include "Icu.h"
#include "eMIOS_Icu_LLD.h"
#endif


/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
/**
@{
@brief   eMIOS Module Id, The define value is 100 for GPT, 121 for PWM and 122 for ICU
*/
#define EMIOS_COMMON_MODULE_ID                121
/**@}*/

/**
@{
@brief   Source file version information
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define REG_ESYS_EMIOS_IRQ_C_VENDOR_ID            43
#define REG_ESYS_EMIOS_IRQ_C_AR_MAJOR_VERSION     3
#define REG_ESYS_EMIOS_IRQ_C_AR_MINOR_VERSION     0
#define REG_ESYS_EMIOS_IRQ_C_AR_PATCH_VERSION     0
#define REG_ESYS_EMIOS_IRQ_C_SW_MAJOR_VERSION     2
#define REG_ESYS_EMIOS_IRQ_C_SW_MINOR_VERSION     0
#define REG_ESYS_EMIOS_IRQ_C_SW_PATCH_VERSION     0
/**@}*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and header file are of the same Autosar version */
    #if ((REG_ESYS_EMIOS_IRQ_C_AR_MAJOR_VERSION != MODULES_AR_MAJOR_VERSION_H) || \
         (REG_ESYS_EMIOS_IRQ_C_AR_MINOR_VERSION != MODULES_AR_MINOR_VERSION_H))
        #error "AutoSar Version Numbers of Reg_eSys_EMIOS_IRQ.c and modules.h are different"
    #endif
#endif


/* Check if source file and Reg_eSys_EMIOS.h are of the same vendor */
#if (REG_ESYS_EMIOS_IRQ_C_VENDOR_ID != REG_ESYS_EMIOS_H_VENDOR_ID)
    #error "Reg_eSys_EMIOS_IRQ.c and Reg_eSys_EMIOS.h have different vendor ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and header file are of the same Autosar version */
    #if ((REG_ESYS_EMIOS_IRQ_C_AR_MAJOR_VERSION != REG_ESYS_EMIOS_H_AR_MAJOR_VERSION) || \
         (REG_ESYS_EMIOS_IRQ_C_AR_MINOR_VERSION != REG_ESYS_EMIOS_H_AR_MINOR_VERSION) || \
         (REG_ESYS_EMIOS_IRQ_C_AR_PATCH_VERSION != REG_ESYS_EMIOS_H_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of Reg_eSys_EMIOS_IRQ.c and Reg_eSys_EMIOS.h are different"
    #endif
#endif

/* Check if source file and header file are of the same Software version */
#if ((REG_ESYS_EMIOS_IRQ_C_SW_MAJOR_VERSION != REG_ESYS_EMIOS_H_SW_MAJOR_VERSION)  || \
     (REG_ESYS_EMIOS_IRQ_C_SW_MINOR_VERSION != REG_ESYS_EMIOS_H_SW_MINOR_VERSION)  || \
     (REG_ESYS_EMIOS_IRQ_C_SW_PATCH_VERSION != REG_ESYS_EMIOS_H_SW_PATCH_VERSION))
    #error "Software Version Numbers of Reg_eSys_EMIOS_IRQ.c and Reg_eSys_EMIOS.h are different"
#endif


/* Check if source file and Reg_eSys_EMIOS_CfgEx.h are of the same vendor */
#if (REG_ESYS_EMIOS_IRQ_C_VENDOR_ID != REG_ESYS_EMIOS_CFGEX_H_VENDOR_ID)
    #error "Reg_eSys_EMIOS_IRQ.c and Reg_eSys_EMIOS_CfgEx.h have different vendor ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and header file are of the same Autosar version */
    #if ((REG_ESYS_EMIOS_IRQ_C_AR_MAJOR_VERSION != REG_ESYS_EMIOS_CFGEX_H_AR_MAJOR_VERSION) || \
         (REG_ESYS_EMIOS_IRQ_C_AR_MINOR_VERSION != REG_ESYS_EMIOS_CFGEX_H_AR_MINOR_VERSION) || \
         (REG_ESYS_EMIOS_IRQ_C_AR_PATCH_VERSION != REG_ESYS_EMIOS_CFGEX_H_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of Reg_eSys_EMIOS_IRQ.c and Reg_eSys_EMIOS_CfgEx.h are \
               different"
    #endif
#endif

/* Check if source file and header file are of the same Software version */
#if ((REG_ESYS_EMIOS_IRQ_C_SW_MAJOR_VERSION != REG_ESYS_EMIOS_CFGEX_H_SW_MAJOR_VERSION)  || \
     (REG_ESYS_EMIOS_IRQ_C_SW_MINOR_VERSION != REG_ESYS_EMIOS_CFGEX_H_SW_MINOR_VERSION)  || \
     (REG_ESYS_EMIOS_IRQ_C_SW_PATCH_VERSION != REG_ESYS_EMIOS_CFGEX_H_SW_PATCH_VERSION))
    #error "Software Version Numbers of Reg_eSys_EMIOS_IRQ.c and Reg_eSys_EMIOS_CfgEx.h are \
           different"
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

/*==================================================================================================
                                   GLOBAL FUNCTIONS PROTOTYPES
==================================================================================================*/

/**
@brief EMIOS_0 common ISR declarations
@{
*/
ISR(EMIOS_0_CH_0_CH_1_ISR);
ISR(EMIOS_0_CH_2_CH_3_ISR);
ISR(EMIOS_0_CH_4_CH_5_ISR);
ISR(EMIOS_0_CH_6_CH_7_ISR);
ISR(EMIOS_0_CH_8_CH_9_ISR);
ISR(EMIOS_0_CH_10_CH_11_ISR);
ISR(EMIOS_0_CH_12_CH_13_ISR);
ISR(EMIOS_0_CH_14_CH_15_ISR);
ISR(EMIOS_0_CH_16_CH_17_ISR);
ISR(EMIOS_0_CH_18_CH_19_ISR);
ISR(EMIOS_0_CH_20_CH_21_ISR);
ISR(EMIOS_0_CH_22_CH_23_ISR);
ISR(EMIOS_0_CH_24_CH_25_ISR);
ISR(EMIOS_0_CH_26_CH_27_ISR);
ISR(EMIOS_0_CH_28_CH_29_ISR);
ISR(EMIOS_0_CH_30_CH_31_ISR);
/**@}*/

/**
@brief EMIOS_1 common ISR declarations
@{
*/
ISR(EMIOS_1_CH_0_CH_1_ISR);
ISR(EMIOS_1_CH_2_CH_3_ISR);
ISR(EMIOS_1_CH_4_CH_5_ISR);
ISR(EMIOS_1_CH_6_CH_7_ISR);
ISR(EMIOS_1_CH_8_CH_9_ISR);
ISR(EMIOS_1_CH_10_CH_11_ISR);
ISR(EMIOS_1_CH_12_CH_13_ISR);
ISR(EMIOS_1_CH_14_CH_15_ISR);
ISR(EMIOS_1_CH_16_CH_17_ISR);
ISR(EMIOS_1_CH_18_CH_19_ISR);
ISR(EMIOS_1_CH_20_CH_21_ISR);
ISR(EMIOS_1_CH_22_CH_23_ISR);
ISR(EMIOS_1_CH_24_CH_25_ISR);
ISR(EMIOS_1_CH_26_CH_27_ISR);
ISR(EMIOS_1_CH_28_CH_29_ISR);
ISR(EMIOS_1_CH_30_CH_31_ISR);
/**@}*/

/**
@brief EMIOS_0 independent ISR declarations
@{
*/
ISR(EMIOS_0_CH_0_ISR);
ISR(EMIOS_0_CH_1_ISR);
ISR(EMIOS_0_CH_2_ISR);
ISR(EMIOS_0_CH_3_ISR);
ISR(EMIOS_0_CH_4_ISR);
ISR(EMIOS_0_CH_5_ISR);
ISR(EMIOS_0_CH_6_ISR);
ISR(EMIOS_0_CH_7_ISR);
ISR(EMIOS_0_CH_8_ISR);
ISR(EMIOS_0_CH_9_ISR);
ISR(EMIOS_0_CH_10_ISR);
ISR(EMIOS_0_CH_11_ISR);
ISR(EMIOS_0_CH_12_ISR);
ISR(EMIOS_0_CH_13_ISR);
ISR(EMIOS_0_CH_14_ISR);
ISR(EMIOS_0_CH_15_ISR);
ISR(EMIOS_0_CH_16_ISR);
ISR(EMIOS_0_CH_17_ISR);
ISR(EMIOS_0_CH_18_ISR);
ISR(EMIOS_0_CH_19_ISR);
ISR(EMIOS_0_CH_20_ISR);
ISR(EMIOS_0_CH_21_ISR);
ISR(EMIOS_0_CH_22_ISR);
ISR(EMIOS_0_CH_23_ISR);
ISR(EMIOS_0_CH_24_ISR);
ISR(EMIOS_0_CH_25_ISR);
ISR(EMIOS_0_CH_26_ISR);
ISR(EMIOS_0_CH_27_ISR);
ISR(EMIOS_0_CH_28_ISR);
ISR(EMIOS_0_CH_29_ISR);
ISR(EMIOS_0_CH_30_ISR);
ISR(EMIOS_0_CH_31_ISR);
/**@}*/

/**
@brief EMIOS_1 independent ISR declarations
@{
*/
ISR(EMIOS_1_CH_0_ISR);
ISR(EMIOS_1_CH_1_ISR);
ISR(EMIOS_1_CH_2_ISR);
ISR(EMIOS_1_CH_3_ISR);
ISR(EMIOS_1_CH_4_ISR);
ISR(EMIOS_1_CH_5_ISR);
ISR(EMIOS_1_CH_6_ISR);
ISR(EMIOS_1_CH_7_ISR);
ISR(EMIOS_1_CH_8_ISR);
ISR(EMIOS_1_CH_9_ISR);
ISR(EMIOS_1_CH_10_ISR);
ISR(EMIOS_1_CH_11_ISR);
ISR(EMIOS_1_CH_12_ISR);
ISR(EMIOS_1_CH_13_ISR);
ISR(EMIOS_1_CH_14_ISR);
ISR(EMIOS_1_CH_15_ISR);
ISR(EMIOS_1_CH_16_ISR);
ISR(EMIOS_1_CH_17_ISR);
ISR(EMIOS_1_CH_18_ISR);
ISR(EMIOS_1_CH_19_ISR);
ISR(EMIOS_1_CH_20_ISR);
ISR(EMIOS_1_CH_21_ISR);
ISR(EMIOS_1_CH_22_ISR);
ISR(EMIOS_1_CH_23_ISR);
ISR(EMIOS_1_CH_24_ISR);
ISR(EMIOS_1_CH_25_ISR);
ISR(EMIOS_1_CH_26_ISR);
ISR(EMIOS_1_CH_27_ISR);
ISR(EMIOS_1_CH_28_ISR);
ISR(EMIOS_1_CH_29_ISR);
ISR(EMIOS_1_CH_30_ISR);
ISR(EMIOS_1_CH_31_ISR);
/**@}*/


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/


/*lint -save -e961 -e537 -e451 */
#if ((USE_GPT_MODULE==STD_ON) && (EMIOS_COMMON_MODULE_ID==100))
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
#define GPT_START_SEC_CODE
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, 19.15 : See @ref Reg_eSys_EMIOS_IRQ_c_1,
      Reg_eSys_EMIOS_IRQ_c_2 */
#include "MemMap.h"
#endif

#if ((USE_GPT_MODULE==STD_OFF) && (USE_PWM_MODULE==STD_ON) && (EMIOS_COMMON_MODULE_ID==121))
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
#define PWM_START_SEC_CODE
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, 19.15 : See @ref Reg_eSys_EMIOS_IRQ_c_1,
      Reg_eSys_EMIOS_IRQ_c_2 */
#include "MemMap.h"
#endif

#if ((USE_GPT_MODULE==STD_OFF) && (USE_PWM_MODULE==STD_OFF) && (USE_ICU_MODULE==STD_ON) && \
      (EMIOS_COMMON_MODULE_ID==122))
#define ICU_START_SEC_CODE
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, 19.15 : See @ref Reg_eSys_EMIOS_IRQ_c_1,
      Reg_eSys_EMIOS_IRQ_c_2 */
#include "MemMap.h"
#endif
/*lint -restore */



#if ( ((USE_GPT_MODULE==STD_ON)  && (EMIOS_COMMON_MODULE_ID==100)) || \
      ((USE_GPT_MODULE==STD_OFF) && (USE_PWM_MODULE==STD_ON)  && (EMIOS_COMMON_MODULE_ID==121)) || \
      ((USE_GPT_MODULE==STD_OFF) && (USE_PWM_MODULE==STD_OFF) && (USE_ICU_MODULE==STD_ON) && \
       (EMIOS_COMMON_MODULE_ID==122)) )




#ifdef EMIOS_COMMON_ISR_HANDLER

  #if  (EMIOS_COMMON_ISR_HANDLER == STD_ON)



/*******************************************************************************/
/********* COMMON EMIOS CHANNELS INTERRUPT SERVICE ROUTINES DEFINITION *********/
/*******************************************************************************/



/*********************************** EMIOS 0 common interrupts START ******************************/


/**
@brief EMIOS module:0 channels:0,1 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_0
*/
#if  ((defined GPT_EMIOS_0_CH_0_ISR_USED) && (defined PWM_EMIOS_0_CH_0_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_0"
#endif

#if  ((defined PWM_EMIOS_0_CH_0_ISR_USED) && (defined ICU_EMIOS_0_CH_0_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_0"
#endif

#if  ((defined ICU_EMIOS_0_CH_0_ISR_USED) && (defined GPT_EMIOS_0_CH_0_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_0"
#endif


/**
@brief resource conflict check for EMIOS_0_CH_1
*/
#if  ((defined GPT_EMIOS_0_CH_1_ISR_USED) && (defined PWM_EMIOS_0_CH_1_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_1"
#endif

#if  ((defined PWM_EMIOS_0_CH_1_ISR_USED) && (defined ICU_EMIOS_0_CH_1_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_1"
#endif

#if  ((defined ICU_EMIOS_0_CH_1_ISR_USED) && (defined GPT_EMIOS_0_CH_1_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_1"
#endif

#if ( (defined GPT_EMIOS_0_CH_0_ISR_USED) || (defined GPT_EMIOS_0_CH_1_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_0_ISR_USED) || (defined PWM_EMIOS_0_CH_1_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_0_ISR_USED) || (defined ICU_EMIOS_0_CH_1_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 0 and 1 for eMIOS_0 module
@details   Process the interrupt of eMIOS channels 0 and 1

@remarks   This will be defined only if eMIOS channels 0 or 1 are configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_0_CH_1_ISR)
{
     #if ( (defined GPT_EMIOS_0_CH_0_ISR_USED) || \
           (defined PWM_EMIOS_0_CH_0_ISR_USED) || \
           (defined ICU_EMIOS_0_CH_0_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_0 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 0)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_0 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 0)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_0_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_0);
                #endif

                #if(defined PWM_EMIOS_0_CH_0_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_0);
                #endif

                #if(defined ICU_EMIOS_0_CH_0_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_0);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_0_CH_1_ISR_USED) || \
          (defined PWM_EMIOS_0_CH_1_ISR_USED) || \
          (defined ICU_EMIOS_0_CH_1_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 1)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 1)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_1_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_1);
                #endif

                #if(defined PWM_EMIOS_0_CH_1_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_1);
                #endif

                #if(defined ICU_EMIOS_0_CH_1_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_1);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channels:2,3 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_2
*/
#if  ((defined GPT_EMIOS_0_CH_2_ISR_USED) && (defined PWM_EMIOS_0_CH_2_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_2"
#endif

#if  ((defined PWM_EMIOS_0_CH_2_ISR_USED) && (defined ICU_EMIOS_0_CH_2_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_2"
#endif

#if  ((defined ICU_EMIOS_0_CH_2_ISR_USED) && (defined GPT_EMIOS_0_CH_2_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_2"
#endif


/**
@brief resource conflict check for EMIOS_0_CH_3
*/
#if  ((defined GPT_EMIOS_0_CH_3_ISR_USED) && (defined PWM_EMIOS_0_CH_3_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_3"
#endif

#if  ((defined PWM_EMIOS_0_CH_3_ISR_USED) && (defined ICU_EMIOS_0_CH_3_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_3"
#endif

#if  ((defined ICU_EMIOS_0_CH_3_ISR_USED) && (defined GPT_EMIOS_0_CH_3_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_3"
#endif

#if ( (defined GPT_EMIOS_0_CH_2_ISR_USED) || (defined GPT_EMIOS_0_CH_3_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_2_ISR_USED) || (defined PWM_EMIOS_0_CH_3_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_2_ISR_USED) || (defined ICU_EMIOS_0_CH_3_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 2 and 3 for eMIOS_0 module
@details   Process the interrupt of eMIOS channels 2 and 3

@remarks   This will be defined only if eMIOS channels 2 or 3 are configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_2_CH_3_ISR)
{
     #if ( (defined GPT_EMIOS_0_CH_2_ISR_USED) || \
           (defined PWM_EMIOS_0_CH_2_ISR_USED) || \
           (defined ICU_EMIOS_0_CH_2_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_2 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    /**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned int to pointer
                               - See Reg_eSys_EMIOS_IRQ_c_3 */
    if ( (REG_READ32(EMIOS_CCR(0, 2)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_2 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    /**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned int to pointer
                               - See Reg_eSys_EMIOS_IRQ_c_3 */
        if ( ( REG_READ32(EMIOS_CSR(0, 2)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_2_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_2);
                #endif

                #if(defined PWM_EMIOS_0_CH_2_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_2);
                #endif

                #if(defined ICU_EMIOS_0_CH_2_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_2);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_0_CH_3_ISR_USED) || \
          (defined PWM_EMIOS_0_CH_3_ISR_USED) || \
          (defined ICU_EMIOS_0_CH_3_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_3 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 3)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_3 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 3)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_3_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_3);
                #endif

                #if(defined PWM_EMIOS_0_CH_3_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_3);
                #endif

                #if(defined ICU_EMIOS_0_CH_3_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_3);
                #endif
        }
    }
    #endif
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned int to pointer
                               - See Reg_eSys_EMIOS_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channels:4,5 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_4
*/
#if  ((defined GPT_EMIOS_0_CH_4_ISR_USED) && (defined PWM_EMIOS_0_CH_4_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_4"
#endif

#if  ((defined PWM_EMIOS_0_CH_4_ISR_USED) && (defined ICU_EMIOS_0_CH_4_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_4"
#endif

#if  ((defined ICU_EMIOS_0_CH_4_ISR_USED) && (defined GPT_EMIOS_0_CH_4_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_4"
#endif


/**
@brief resource conflict check for EMIOS_0_CH_5
*/
#if  ((defined GPT_EMIOS_0_CH_5_ISR_USED) && (defined PWM_EMIOS_0_CH_5_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_5"
#endif

#if  ((defined PWM_EMIOS_0_CH_5_ISR_USED) && (defined ICU_EMIOS_0_CH_5_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_5"
#endif

#if  ((defined ICU_EMIOS_0_CH_5_ISR_USED) && (defined GPT_EMIOS_0_CH_5_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_5"
#endif

#if ( (defined GPT_EMIOS_0_CH_4_ISR_USED) || (defined GPT_EMIOS_0_CH_5_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_4_ISR_USED) || (defined PWM_EMIOS_0_CH_5_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_4_ISR_USED) || (defined ICU_EMIOS_0_CH_5_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 4 and 5 for eMIOS_0 module
@details   Process the interrupt of eMIOS channels 4 and 5

@remarks   This will be defined only if eMIOS channels 4 or 5 are configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_4_CH_5_ISR)
{
     #if ( (defined GPT_EMIOS_0_CH_4_ISR_USED) || \
           (defined PWM_EMIOS_0_CH_4_ISR_USED) || \
           (defined ICU_EMIOS_0_CH_4_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_4 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 4)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_4 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 4)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_4_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_4);
                #endif

                #if(defined PWM_EMIOS_0_CH_4_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_4);
                #endif

                #if(defined ICU_EMIOS_0_CH_4_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_4);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_0_CH_5_ISR_USED) || \
          (defined PWM_EMIOS_0_CH_5_ISR_USED) || \
          (defined ICU_EMIOS_0_CH_5_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_5 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 5)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_5 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 5)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_5_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_5);
                #endif

                #if(defined PWM_EMIOS_0_CH_5_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_5);
                #endif

                #if(defined ICU_EMIOS_0_CH_5_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_5);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channels:6,7 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_6
*/
#if  ((defined GPT_EMIOS_0_CH_6_ISR_USED) && (defined PWM_EMIOS_0_CH_6_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_6"
#endif

#if  ((defined PWM_EMIOS_0_CH_6_ISR_USED) && (defined ICU_EMIOS_0_CH_6_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_6"
#endif

#if  ((defined ICU_EMIOS_0_CH_6_ISR_USED) && (defined GPT_EMIOS_0_CH_6_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_6"
#endif


/**
@brief resource conflict check for EMIOS_0_CH_7
*/
#if  ((defined GPT_EMIOS_0_CH_7_ISR_USED) && (defined PWM_EMIOS_0_CH_7_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_7"
#endif

#if  ((defined PWM_EMIOS_0_CH_7_ISR_USED) && (defined ICU_EMIOS_0_CH_7_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_7"
#endif

#if  ((defined ICU_EMIOS_0_CH_7_ISR_USED) && (defined GPT_EMIOS_0_CH_7_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_7"
#endif

#if ( (defined GPT_EMIOS_0_CH_6_ISR_USED) || (defined GPT_EMIOS_0_CH_7_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_6_ISR_USED) || (defined PWM_EMIOS_0_CH_7_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_6_ISR_USED) || (defined ICU_EMIOS_0_CH_7_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 6 and 7 for eMIOS_0 module
@details   Process the interrupt of eMIOS channels 6 and 7

@remarks   This will be defined only if eMIOS channels 6 or 7 are configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_6_CH_7_ISR)
{
     #if ( (defined GPT_EMIOS_0_CH_6_ISR_USED) || \
           (defined PWM_EMIOS_0_CH_6_ISR_USED) || \
           (defined ICU_EMIOS_0_CH_6_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_6 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 6)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_6 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 6)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_6_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_6);
                #endif

                #if(defined PWM_EMIOS_0_CH_6_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_6);
                #endif

                #if(defined ICU_EMIOS_0_CH_6_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_6);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_0_CH_7_ISR_USED) || \
          (defined PWM_EMIOS_0_CH_7_ISR_USED) || \
          (defined ICU_EMIOS_0_CH_7_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_7 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 7)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_7 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 7)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_7_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_7);
                #endif

                #if(defined PWM_EMIOS_0_CH_7_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_7);
                #endif

                #if(defined ICU_EMIOS_0_CH_7_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_7);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channels:8,9 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_8
*/
#if  ((defined GPT_EMIOS_0_CH_8_ISR_USED) && (defined PWM_EMIOS_0_CH_8_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_8"
#endif

#if  ((defined PWM_EMIOS_0_CH_8_ISR_USED) && (defined ICU_EMIOS_0_CH_8_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_8"
#endif

#if  ((defined ICU_EMIOS_0_CH_8_ISR_USED) && (defined GPT_EMIOS_0_CH_8_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_8"
#endif


/**
@brief resource conflict check for EMIOS_0_CH_9
*/
#if  ((defined GPT_EMIOS_0_CH_9_ISR_USED) && (defined PWM_EMIOS_0_CH_9_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_9"
#endif

#if  ((defined PWM_EMIOS_0_CH_9_ISR_USED) && (defined ICU_EMIOS_0_CH_9_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_9"
#endif

#if  ((defined ICU_EMIOS_0_CH_9_ISR_USED) && (defined GPT_EMIOS_0_CH_9_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_9"
#endif

#if ( (defined GPT_EMIOS_0_CH_8_ISR_USED) || (defined GPT_EMIOS_0_CH_9_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_8_ISR_USED) || (defined PWM_EMIOS_0_CH_9_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_8_ISR_USED) || (defined ICU_EMIOS_0_CH_9_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 8 and 9 for eMIOS_0 module
@details   Process the interrupt of eMIOS channels 8 and 9

@remarks   This will be defined only if eMIOS channels 8 or 9 are configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_8_CH_9_ISR)
{
     #if ( (defined GPT_EMIOS_0_CH_8_ISR_USED) || \
           (defined PWM_EMIOS_0_CH_8_ISR_USED) || \
           (defined ICU_EMIOS_0_CH_8_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_8 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 8)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_8 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 8)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_8_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_8);
                #endif

                #if(defined PWM_EMIOS_0_CH_8_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_8);
                #endif

                #if(defined ICU_EMIOS_0_CH_8_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_8);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_0_CH_9_ISR_USED) || \
          (defined PWM_EMIOS_0_CH_9_ISR_USED) || \
          (defined ICU_EMIOS_0_CH_9_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_9 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 9)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_9 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 9)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_9_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_9);
                #endif

                #if(defined PWM_EMIOS_0_CH_9_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_9);
                #endif

                #if(defined ICU_EMIOS_0_CH_9_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_9);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channels:10,11 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_10
*/
#if  ((defined GPT_EMIOS_0_CH_10_ISR_USED) && (defined PWM_EMIOS_0_CH_10_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_10"
#endif

#if  ((defined PWM_EMIOS_0_CH_10_ISR_USED) && (defined ICU_EMIOS_0_CH_10_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_10"
#endif

#if  ((defined ICU_EMIOS_0_CH_10_ISR_USED) && (defined GPT_EMIOS_0_CH_10_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_10"
#endif


/**
@brief resource conflict check for EMIOS_0_CH_11
*/
#if  ((defined GPT_EMIOS_0_CH_11_ISR_USED) && (defined PWM_EMIOS_0_CH_11_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_11"
#endif

#if  ((defined PWM_EMIOS_0_CH_11_ISR_USED) && (defined ICU_EMIOS_0_CH_11_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_11"
#endif

#if  ((defined ICU_EMIOS_0_CH_11_ISR_USED) && (defined GPT_EMIOS_0_CH_11_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_11"
#endif

#if ( (defined GPT_EMIOS_0_CH_10_ISR_USED) || (defined GPT_EMIOS_0_CH_11_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_10_ISR_USED) || (defined PWM_EMIOS_0_CH_11_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_10_ISR_USED) || (defined ICU_EMIOS_0_CH_11_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 10 and 11 for eMIOS_0 module
@details   Process the interrupt of eMIOS channels 10 and 11

@remarks   This will be defined only if eMIOS channels 10 or 11 are configured in GPT, ICU or
           PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_10_CH_11_ISR)
{
     #if ( (defined GPT_EMIOS_0_CH_10_ISR_USED) || \
           (defined PWM_EMIOS_0_CH_10_ISR_USED) || \
           (defined ICU_EMIOS_0_CH_10_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_10 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 10)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_10 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 10)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_10_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_10);
                #endif

                #if(defined PWM_EMIOS_0_CH_10_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_10);
                #endif

                #if(defined ICU_EMIOS_0_CH_10_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_10);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_0_CH_11_ISR_USED) || \
          (defined PWM_EMIOS_0_CH_11_ISR_USED) || \
          (defined ICU_EMIOS_0_CH_11_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_11 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 11)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_11 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 11)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_11_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_11);
                #endif

                #if(defined PWM_EMIOS_0_CH_11_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_11);
                #endif

                #if(defined ICU_EMIOS_0_CH_11_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_11);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channels:12,13 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_12
*/
#if  ((defined GPT_EMIOS_0_CH_12_ISR_USED) && (defined PWM_EMIOS_0_CH_12_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_12"
#endif

#if  ((defined PWM_EMIOS_0_CH_12_ISR_USED) && (defined ICU_EMIOS_0_CH_12_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_12"
#endif

#if  ((defined ICU_EMIOS_0_CH_12_ISR_USED) && (defined GPT_EMIOS_0_CH_12_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_12"
#endif


/**
@brief resource conflict check for EMIOS_0_CH_13
*/
#if  ((defined GPT_EMIOS_0_CH_13_ISR_USED) && (defined PWM_EMIOS_0_CH_13_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_13"
#endif

#if  ((defined PWM_EMIOS_0_CH_13_ISR_USED) && (defined ICU_EMIOS_0_CH_13_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_13"
#endif

#if  ((defined ICU_EMIOS_0_CH_13_ISR_USED) && (defined GPT_EMIOS_0_CH_13_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_13"
#endif

#if ( (defined GPT_EMIOS_0_CH_12_ISR_USED) || (defined GPT_EMIOS_0_CH_13_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_12_ISR_USED) || (defined PWM_EMIOS_0_CH_13_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_12_ISR_USED) || (defined ICU_EMIOS_0_CH_13_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 12 and 13 for eMIOS_0 module
@details   Process the interrupt of eMIOS channels 12 and 13

@remarks   This will be defined only if eMIOS channels 12 or 13 are configured in GPT,
           ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_12_CH_13_ISR)
{
     #if ( (defined GPT_EMIOS_0_CH_12_ISR_USED) || \
           (defined PWM_EMIOS_0_CH_12_ISR_USED) || \
           (defined ICU_EMIOS_0_CH_12_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_12 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 12)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_12 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 12)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_12_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_12);
                #endif

                #if(defined PWM_EMIOS_0_CH_12_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_12);
                #endif

                #if(defined ICU_EMIOS_0_CH_12_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_12);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_0_CH_13_ISR_USED) || \
          (defined PWM_EMIOS_0_CH_13_ISR_USED) || \
          (defined ICU_EMIOS_0_CH_13_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_13 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 13)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_13 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 13)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_13_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_13);
                #endif

                #if(defined PWM_EMIOS_0_CH_13_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_13);
                #endif

                #if(defined ICU_EMIOS_0_CH_13_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_13);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channels:14,15 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_14
*/
#if  ((defined GPT_EMIOS_0_CH_14_ISR_USED) && (defined PWM_EMIOS_0_CH_14_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_14"
#endif

#if  ((defined PWM_EMIOS_0_CH_14_ISR_USED) && (defined ICU_EMIOS_0_CH_14_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_14"
#endif

#if  ((defined ICU_EMIOS_0_CH_14_ISR_USED) && (defined GPT_EMIOS_0_CH_14_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_14"
#endif


/**
@brief resource conflict check for EMIOS_0_CH_15
*/
#if  ((defined GPT_EMIOS_0_CH_15_ISR_USED) && (defined PWM_EMIOS_0_CH_15_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_15"
#endif

#if  ((defined PWM_EMIOS_0_CH_15_ISR_USED) && (defined ICU_EMIOS_0_CH_15_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_15"
#endif

#if  ((defined ICU_EMIOS_0_CH_15_ISR_USED) && (defined GPT_EMIOS_0_CH_15_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_15"
#endif

#if ( (defined GPT_EMIOS_0_CH_14_ISR_USED) || (defined GPT_EMIOS_0_CH_15_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_14_ISR_USED) || (defined PWM_EMIOS_0_CH_15_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_14_ISR_USED) || (defined ICU_EMIOS_0_CH_15_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 14 and 15 for eMIOS_0 module
@details   Process the interrupt of eMIOS channels 14 and 15

@remarks   This will be defined only if eMIOS channels 14 or 15 are configured in GPT,
           ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_14_CH_15_ISR)
{
     #if ( (defined GPT_EMIOS_0_CH_14_ISR_USED) || \
           (defined PWM_EMIOS_0_CH_14_ISR_USED) || \
           (defined ICU_EMIOS_0_CH_14_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_14 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 14)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_14 */
        if ( ( REG_READ32(EMIOS_CSR(0, 14)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_14_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_14);
                #endif

                #if(defined PWM_EMIOS_0_CH_14_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_14);
                #endif

                #if(defined ICU_EMIOS_0_CH_14_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_14);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_0_CH_15_ISR_USED) || \
          (defined PWM_EMIOS_0_CH_15_ISR_USED) || \
          (defined ICU_EMIOS_0_CH_15_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_15 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 15)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_15 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 15)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_15_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_15);
                #endif

                #if(defined PWM_EMIOS_0_CH_15_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_15);
                #endif

                #if(defined ICU_EMIOS_0_CH_15_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_15);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channels:16,17 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_16
*/
#if  ((defined GPT_EMIOS_0_CH_16_ISR_USED) && (defined PWM_EMIOS_0_CH_16_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_16"
#endif

#if  ((defined PWM_EMIOS_0_CH_16_ISR_USED) && (defined ICU_EMIOS_0_CH_16_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_16"
#endif

#if  ((defined ICU_EMIOS_0_CH_16_ISR_USED) && (defined GPT_EMIOS_0_CH_16_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_16"
#endif


/**
@brief resource conflict check for EMIOS_0_CH_17
*/
#if  ((defined GPT_EMIOS_0_CH_17_ISR_USED) && (defined PWM_EMIOS_0_CH_17_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_17"
#endif

#if  ((defined PWM_EMIOS_0_CH_17_ISR_USED) && (defined ICU_EMIOS_0_CH_17_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_17"
#endif

#if  ((defined ICU_EMIOS_0_CH_17_ISR_USED) && (defined GPT_EMIOS_0_CH_17_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_17"
#endif

#if ( (defined GPT_EMIOS_0_CH_16_ISR_USED) || (defined GPT_EMIOS_0_CH_17_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_16_ISR_USED) || (defined PWM_EMIOS_0_CH_17_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_16_ISR_USED) || (defined ICU_EMIOS_0_CH_17_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 16 and 17 for eMIOS_0 module
@details   Process the interrupt of eMIOS channels 16 and 17

@remarks   This will be defined only if eMIOS channels 16 or 17 are configured in GPT,
           ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_16_CH_17_ISR)
{
     #if ( (defined GPT_EMIOS_0_CH_16_ISR_USED) || \
           (defined PWM_EMIOS_0_CH_16_ISR_USED) || \
           (defined ICU_EMIOS_0_CH_16_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_16 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 16)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_16 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 16)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_16_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_16);
                #endif

                #if(defined PWM_EMIOS_0_CH_16_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_16);
                #endif

                #if(defined ICU_EMIOS_0_CH_16_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_16);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_0_CH_17_ISR_USED) || \
          (defined PWM_EMIOS_0_CH_17_ISR_USED) || \
          (defined ICU_EMIOS_0_CH_17_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_17 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 17)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_17 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 17)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_17_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_17);
                #endif

                #if(defined PWM_EMIOS_0_CH_17_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_17);
                #endif

                #if(defined ICU_EMIOS_0_CH_17_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_17);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channels:18,19 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_18
*/
#if  ((defined GPT_EMIOS_0_CH_18_ISR_USED) && (defined PWM_EMIOS_0_CH_18_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_18"
#endif

#if  ((defined PWM_EMIOS_0_CH_18_ISR_USED) && (defined ICU_EMIOS_0_CH_18_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_18"
#endif

#if  ((defined ICU_EMIOS_0_CH_18_ISR_USED) && (defined GPT_EMIOS_0_CH_18_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_18"
#endif


/**
@brief resource conflict check for EMIOS_0_CH_19
*/
#if  ((defined GPT_EMIOS_0_CH_19_ISR_USED) && (defined PWM_EMIOS_0_CH_19_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_19"
#endif

#if  ((defined PWM_EMIOS_0_CH_19_ISR_USED) && (defined ICU_EMIOS_0_CH_19_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_19"
#endif

#if  ((defined ICU_EMIOS_0_CH_19_ISR_USED) && (defined GPT_EMIOS_0_CH_19_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_19"
#endif

#if ( (defined GPT_EMIOS_0_CH_18_ISR_USED) || (defined GPT_EMIOS_0_CH_19_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_18_ISR_USED) || (defined PWM_EMIOS_0_CH_19_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_18_ISR_USED) || (defined ICU_EMIOS_0_CH_19_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 18 and 19 for eMIOS_0 module
@details   Process the interrupt of eMIOS channels 18 and 19

@remarks   This will be defined only if eMIOS channels 18 or 19 are configured in GPT, ICU or PWM
           mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_18_CH_19_ISR)
{
     #if ( (defined GPT_EMIOS_0_CH_18_ISR_USED) || \
           (defined PWM_EMIOS_0_CH_18_ISR_USED) || \
           (defined ICU_EMIOS_0_CH_18_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_18 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 18)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_18 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 18)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_18_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_18);
                #endif

                #if(defined PWM_EMIOS_0_CH_18_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_18);
                #endif

                #if(defined ICU_EMIOS_0_CH_18_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_18);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_0_CH_19_ISR_USED) || \
          (defined PWM_EMIOS_0_CH_19_ISR_USED) || \
          (defined ICU_EMIOS_0_CH_19_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_19 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 19)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_19 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 19)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_19_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_19);
                #endif

                #if(defined PWM_EMIOS_0_CH_19_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_19);
                #endif

                #if(defined ICU_EMIOS_0_CH_19_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_19);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channels:20,21 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_20
*/
#if  ((defined GPT_EMIOS_0_CH_20_ISR_USED) && (defined PWM_EMIOS_0_CH_20_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_20"
#endif

#if  ((defined PWM_EMIOS_0_CH_20_ISR_USED) && (defined ICU_EMIOS_0_CH_20_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_20"
#endif

#if  ((defined ICU_EMIOS_0_CH_20_ISR_USED) && (defined GPT_EMIOS_0_CH_20_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_20"
#endif


/**
@brief resource conflict check for EMIOS_0_CH_21
*/
#if  ((defined GPT_EMIOS_0_CH_21_ISR_USED) && (defined PWM_EMIOS_0_CH_21_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_21"
#endif

#if  ((defined PWM_EMIOS_0_CH_21_ISR_USED) && (defined ICU_EMIOS_0_CH_21_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_21"
#endif

#if  ((defined ICU_EMIOS_0_CH_21_ISR_USED) && (defined GPT_EMIOS_0_CH_21_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_21"
#endif

#if ( (defined GPT_EMIOS_0_CH_20_ISR_USED) || (defined GPT_EMIOS_0_CH_21_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_20_ISR_USED) || (defined PWM_EMIOS_0_CH_21_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_20_ISR_USED) || (defined ICU_EMIOS_0_CH_21_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 20 and 21 for eMIOS_0 module
@details   Process the interrupt of eMIOS channels 20 and 21

@remarks   This will be defined only if eMIOS channels 20 or 21 are configured in GPT,
           ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_20_CH_21_ISR)
{
     #if ( (defined GPT_EMIOS_0_CH_20_ISR_USED) || \
           (defined PWM_EMIOS_0_CH_20_ISR_USED) || \
           (defined ICU_EMIOS_0_CH_20_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_20 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 20)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_20 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 20)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_20_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_20);
                #endif

                #if(defined PWM_EMIOS_0_CH_20_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_20);
                #endif

                #if(defined ICU_EMIOS_0_CH_20_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_20);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_0_CH_21_ISR_USED) || \
          (defined PWM_EMIOS_0_CH_21_ISR_USED) || \
          (defined ICU_EMIOS_0_CH_21_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_21 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 21)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_21 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 21)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_21_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_21);
                #endif

                #if(defined PWM_EMIOS_0_CH_21_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_21);
                #endif

                #if(defined ICU_EMIOS_0_CH_21_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_21);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channels:22,23 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_22
*/
#if  ((defined GPT_EMIOS_0_CH_22_ISR_USED) && (defined PWM_EMIOS_0_CH_22_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_22"
#endif

#if  ((defined PWM_EMIOS_0_CH_22_ISR_USED) && (defined ICU_EMIOS_0_CH_22_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_22"
#endif

#if  ((defined ICU_EMIOS_0_CH_22_ISR_USED) && (defined GPT_EMIOS_0_CH_22_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_22"
#endif


/**
@brief resource conflict check for EMIOS_0_CH_23
*/
#if  ((defined GPT_EMIOS_0_CH_23_ISR_USED) && (defined PWM_EMIOS_0_CH_23_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_23"
#endif

#if  ((defined PWM_EMIOS_0_CH_23_ISR_USED) && (defined ICU_EMIOS_0_CH_23_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_23"
#endif

#if  ((defined ICU_EMIOS_0_CH_23_ISR_USED) && (defined GPT_EMIOS_0_CH_23_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_23"
#endif

#if ( (defined GPT_EMIOS_0_CH_22_ISR_USED) || (defined GPT_EMIOS_0_CH_23_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_22_ISR_USED) || (defined PWM_EMIOS_0_CH_23_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_22_ISR_USED) || (defined ICU_EMIOS_0_CH_23_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 22 and 23 for eMIOS_0 module
@details   Process the interrupt of eMIOS channels 22 and 23

@remarks   This will be defined only if eMIOS channels 22 or 23 are configured in GPT,
           ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_22_CH_23_ISR)
{
     #if ( (defined GPT_EMIOS_0_CH_22_ISR_USED) || \
           (defined PWM_EMIOS_0_CH_22_ISR_USED) || \
           (defined ICU_EMIOS_0_CH_22_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_22 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 22)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_22 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 22)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_22_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_22);
                #endif

                #if(defined PWM_EMIOS_0_CH_22_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_22);
                #endif

                #if(defined ICU_EMIOS_0_CH_22_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_22);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_0_CH_23_ISR_USED) || \
          (defined PWM_EMIOS_0_CH_23_ISR_USED) || \
          (defined ICU_EMIOS_0_CH_23_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_23 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 23)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_23 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 23)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_23_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_23);
                #endif

                #if(defined PWM_EMIOS_0_CH_23_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_23);
                #endif

                #if(defined ICU_EMIOS_0_CH_23_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_23);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channels:24,25 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_24
*/
#if  ((defined GPT_EMIOS_0_CH_24_ISR_USED) && (defined PWM_EMIOS_0_CH_24_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_24"
#endif

#if  ((defined PWM_EMIOS_0_CH_24_ISR_USED) && (defined ICU_EMIOS_0_CH_24_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_24"
#endif

#if  ((defined ICU_EMIOS_0_CH_24_ISR_USED) && (defined GPT_EMIOS_0_CH_24_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_24"
#endif


/**
@brief resource conflict check for EMIOS_0_CH_25
*/
#if  ((defined GPT_EMIOS_0_CH_25_ISR_USED) && (defined PWM_EMIOS_0_CH_25_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_25"
#endif

#if  ((defined PWM_EMIOS_0_CH_25_ISR_USED) && (defined ICU_EMIOS_0_CH_25_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_25"
#endif

#if  ((defined ICU_EMIOS_0_CH_25_ISR_USED) && (defined GPT_EMIOS_0_CH_25_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_25"
#endif

#if ( (defined GPT_EMIOS_0_CH_24_ISR_USED) || (defined GPT_EMIOS_0_CH_25_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_24_ISR_USED) || (defined PWM_EMIOS_0_CH_25_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_24_ISR_USED) || (defined ICU_EMIOS_0_CH_25_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 24 and 25 for eMIOS_0 module
@details   Process the interrupt of eMIOS channels 24 and 25

@remarks   This will be defined only if eMIOS channels 24 or 25 are configured in GPT,
           ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_24_CH_25_ISR)
{
     #if ( (defined GPT_EMIOS_0_CH_24_ISR_USED) || \
           (defined PWM_EMIOS_0_CH_24_ISR_USED) || \
           (defined ICU_EMIOS_0_CH_24_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_24 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 24)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_24 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 24)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_24_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_24);
                #endif

                #if(defined PWM_EMIOS_0_CH_24_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_24);
                #endif

                #if(defined ICU_EMIOS_0_CH_24_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_24);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_0_CH_25_ISR_USED) || \
          (defined PWM_EMIOS_0_CH_25_ISR_USED) || \
          (defined ICU_EMIOS_0_CH_25_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_25 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 25)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_25 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 25)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_25_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_25);
                #endif

                #if(defined PWM_EMIOS_0_CH_25_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_25);
                #endif

                #if(defined ICU_EMIOS_0_CH_25_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_25);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channels:26,27 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_26
*/
#if  ((defined GPT_EMIOS_0_CH_26_ISR_USED) && (defined PWM_EMIOS_0_CH_26_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_26"
#endif

#if  ((defined PWM_EMIOS_0_CH_26_ISR_USED) && (defined ICU_EMIOS_0_CH_26_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_26"
#endif

#if  ((defined ICU_EMIOS_0_CH_26_ISR_USED) && (defined GPT_EMIOS_0_CH_26_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_26"
#endif


/**
@brief resource conflict check for EMIOS_0_CH_27
*/
#if  ((defined GPT_EMIOS_0_CH_27_ISR_USED) && (defined PWM_EMIOS_0_CH_27_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_27"
#endif

#if  ((defined PWM_EMIOS_0_CH_27_ISR_USED) && (defined ICU_EMIOS_0_CH_27_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_27"
#endif

#if  ((defined ICU_EMIOS_0_CH_27_ISR_USED) && (defined GPT_EMIOS_0_CH_27_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_27"
#endif

#if ( (defined GPT_EMIOS_0_CH_26_ISR_USED) || (defined GPT_EMIOS_0_CH_27_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_26_ISR_USED) || (defined PWM_EMIOS_0_CH_27_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_26_ISR_USED) || (defined ICU_EMIOS_0_CH_27_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 26 and 27 for eMIOS_0 module
@details   Process the interrupt of eMIOS channels 26 and 27

@remarks   This will be defined only if eMIOS channels 26 or 27 are configured in GPT,
           ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_26_CH_27_ISR)
{
     #if ( (defined GPT_EMIOS_0_CH_26_ISR_USED) || \
           (defined PWM_EMIOS_0_CH_26_ISR_USED) || \
           (defined ICU_EMIOS_0_CH_26_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_26 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 26)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_26 */
                        /**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 26)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_26_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_26);
                #endif

                #if(defined PWM_EMIOS_0_CH_26_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_26);
                #endif

                #if(defined ICU_EMIOS_0_CH_26_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_26);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_0_CH_27_ISR_USED) || \
          (defined PWM_EMIOS_0_CH_27_ISR_USED) || \
          (defined ICU_EMIOS_0_CH_27_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_27 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 27)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_27 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 27)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_27_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_27);
                #endif

                #if(defined PWM_EMIOS_0_CH_27_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_27);
                #endif

                #if(defined ICU_EMIOS_0_CH_27_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_27);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channels:28,29 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_28
*/
#if  ((defined GPT_EMIOS_0_CH_28_ISR_USED) && (defined PWM_EMIOS_0_CH_28_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_28"
#endif

#if  ((defined PWM_EMIOS_0_CH_28_ISR_USED) && (defined ICU_EMIOS_0_CH_28_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_28"
#endif

#if  ((defined ICU_EMIOS_0_CH_28_ISR_USED) && (defined GPT_EMIOS_0_CH_28_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_28"
#endif


/**
@brief resource conflict check for EMIOS_0_CH_29
*/
#if  ((defined GPT_EMIOS_0_CH_29_ISR_USED) && (defined PWM_EMIOS_0_CH_29_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_29"
#endif

#if  ((defined PWM_EMIOS_0_CH_29_ISR_USED) && (defined ICU_EMIOS_0_CH_29_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_29"
#endif

#if  ((defined ICU_EMIOS_0_CH_29_ISR_USED) && (defined GPT_EMIOS_0_CH_29_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_29"
#endif

#if ( (defined GPT_EMIOS_0_CH_28_ISR_USED) || (defined GPT_EMIOS_0_CH_29_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_28_ISR_USED) || (defined PWM_EMIOS_0_CH_29_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_28_ISR_USED) || (defined ICU_EMIOS_0_CH_29_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 28 and 29 for eMIOS_0 module
@details   Process the interrupt of eMIOS channels 28 and 29

@remarks   This will be defined only if eMIOS channels 28 or 29 are configured in GPT,
           ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_28_CH_29_ISR)
{
     #if ( (defined GPT_EMIOS_0_CH_28_ISR_USED) || \
           (defined PWM_EMIOS_0_CH_28_ISR_USED) || \
           (defined ICU_EMIOS_0_CH_28_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_28 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 28)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_28 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 28)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_28_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_28);
                #endif

                #if(defined PWM_EMIOS_0_CH_28_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_28);
                #endif

                #if(defined ICU_EMIOS_0_CH_28_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_28);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_0_CH_29_ISR_USED) || \
          (defined PWM_EMIOS_0_CH_29_ISR_USED) || \
          (defined ICU_EMIOS_0_CH_29_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_29 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 29)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_29 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 29)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_29_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_29);
                #endif

                #if(defined PWM_EMIOS_0_CH_29_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_29);
                #endif

                #if(defined ICU_EMIOS_0_CH_29_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_29);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channels:30,31 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_30
*/
#if  ((defined GPT_EMIOS_0_CH_30_ISR_USED) && (defined PWM_EMIOS_0_CH_30_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_30"
#endif

#if  ((defined PWM_EMIOS_0_CH_30_ISR_USED) && (defined ICU_EMIOS_0_CH_30_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_30"
#endif

#if  ((defined ICU_EMIOS_0_CH_30_ISR_USED) && (defined GPT_EMIOS_0_CH_30_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_30"
#endif


/**
@brief resource conflict check for EMIOS_0_CH_31
*/
#if  ((defined GPT_EMIOS_0_CH_31_ISR_USED) && (defined PWM_EMIOS_0_CH_31_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_31"
#endif

#if  ((defined PWM_EMIOS_0_CH_31_ISR_USED) && (defined ICU_EMIOS_0_CH_31_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_31"
#endif

#if  ((defined ICU_EMIOS_0_CH_31_ISR_USED) && (defined GPT_EMIOS_0_CH_31_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_31"
#endif

#if ( (defined GPT_EMIOS_0_CH_30_ISR_USED) || (defined GPT_EMIOS_0_CH_31_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_30_ISR_USED) || (defined PWM_EMIOS_0_CH_31_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_30_ISR_USED) || (defined ICU_EMIOS_0_CH_31_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 30 and 31 for eMIOS_0 module
@details   Process the interrupt of eMIOS channels 30 and 31

@remarks   This will be defined only if eMIOS channels 30 or 31 are configured in GPT,
ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_30_CH_31_ISR)
{
     #if ( (defined GPT_EMIOS_0_CH_30_ISR_USED) || \
           (defined PWM_EMIOS_0_CH_30_ISR_USED) || \
           (defined ICU_EMIOS_0_CH_30_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_30 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 30)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_30 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 30)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_30_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_30);
                #endif

                #if(defined PWM_EMIOS_0_CH_30_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_30);
                #endif

                #if(defined ICU_EMIOS_0_CH_30_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_30);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_0_CH_31_ISR_USED) || \
          (defined PWM_EMIOS_0_CH_31_ISR_USED) || \
          (defined ICU_EMIOS_0_CH_31_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_31 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
    if ( (REG_READ32(EMIOS_CCR(0, 31)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_31 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
        if ( ( REG_READ32(EMIOS_CSR(0, 31)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_0_CH_31_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_31);
                #endif

                #if(defined PWM_EMIOS_0_CH_31_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_31);
                #endif

                #if(defined ICU_EMIOS_0_CH_31_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_31);
                #endif
        }
    }
    #endif
    EXIT_INTERRUPT();
}
#endif



/*********************************** EMIOS 0 common interrupts END ********************************/



/*********************************** EMIOS 1 common interrupts START ******************************/


/**
@brief EMIOS module:1 channels:0,1 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_0
*/
#if  ((defined GPT_EMIOS_1_CH_0_ISR_USED) && (defined PWM_EMIOS_1_CH_0_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_0"
#endif

#if  ((defined PWM_EMIOS_1_CH_0_ISR_USED) && (defined ICU_EMIOS_1_CH_0_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_0"
#endif

#if  ((defined ICU_EMIOS_1_CH_0_ISR_USED) && (defined GPT_EMIOS_1_CH_0_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_0"
#endif


/**
@brief resource conflict check for EMIOS_1_CH_1
*/
#if  ((defined GPT_EMIOS_1_CH_1_ISR_USED) && (defined PWM_EMIOS_1_CH_1_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_1"
#endif

#if  ((defined PWM_EMIOS_1_CH_1_ISR_USED) && (defined ICU_EMIOS_1_CH_1_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_1"
#endif

#if  ((defined ICU_EMIOS_1_CH_1_ISR_USED) && (defined GPT_EMIOS_1_CH_1_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_1"
#endif

#if ( (defined GPT_EMIOS_1_CH_0_ISR_USED) || (defined GPT_EMIOS_1_CH_1_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_0_ISR_USED) || (defined PWM_EMIOS_1_CH_1_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_0_ISR_USED) || (defined ICU_EMIOS_1_CH_1_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 0 and 1 for eMIOS_1 module
@details   Process the interrupt of eMIOS channels 0 and 1

@remarks   This will be defined only if eMIOS channels 0 or 1 are configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_0_CH_1_ISR)
{
     #if ( (defined GPT_EMIOS_1_CH_0_ISR_USED) || \
           (defined PWM_EMIOS_1_CH_0_ISR_USED) || \
           (defined ICU_EMIOS_1_CH_0_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_0 */
    if ( (REG_READ32(EMIOS_CCR(1, 0)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_0 */
        if ( ( REG_READ32(EMIOS_CSR(1, 0)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_0_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_0);
                #endif

                #if(defined PWM_EMIOS_1_CH_0_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_0);
                #endif

                #if(defined ICU_EMIOS_1_CH_0_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_0);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_1_CH_1_ISR_USED) || \
          (defined PWM_EMIOS_1_CH_1_ISR_USED) || \
          (defined ICU_EMIOS_1_CH_1_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_1 */
    if ( (REG_READ32(EMIOS_CCR(1, 1)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_1 */
        if ( ( REG_READ32(EMIOS_CSR(1, 1)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_1_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_1);
                #endif

                #if(defined PWM_EMIOS_1_CH_1_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_1);
                #endif

                #if(defined ICU_EMIOS_1_CH_1_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_1);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channels:2,3 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_2
*/
#if  ((defined GPT_EMIOS_1_CH_2_ISR_USED) && (defined PWM_EMIOS_1_CH_2_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_2"
#endif

#if  ((defined PWM_EMIOS_1_CH_2_ISR_USED) && (defined ICU_EMIOS_1_CH_2_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_2"
#endif

#if  ((defined ICU_EMIOS_1_CH_2_ISR_USED) && (defined GPT_EMIOS_1_CH_2_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_2"
#endif


/**
@brief resource conflict check for EMIOS_1_CH_3
*/
#if  ((defined GPT_EMIOS_1_CH_3_ISR_USED) && (defined PWM_EMIOS_1_CH_3_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_3"
#endif

#if  ((defined PWM_EMIOS_1_CH_3_ISR_USED) && (defined ICU_EMIOS_1_CH_3_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_3"
#endif

#if  ((defined ICU_EMIOS_1_CH_3_ISR_USED) && (defined GPT_EMIOS_1_CH_3_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_3"
#endif

#if ( (defined GPT_EMIOS_1_CH_2_ISR_USED) || (defined GPT_EMIOS_1_CH_3_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_2_ISR_USED) || (defined PWM_EMIOS_1_CH_3_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_2_ISR_USED) || (defined ICU_EMIOS_1_CH_3_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 2 and 3 for eMIOS_1 module
@details   Process the interrupt of eMIOS channels 2 and 3

@remarks   This will be defined only if eMIOS channels 2 or 3 are configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_2_CH_3_ISR)
{
     #if ( (defined GPT_EMIOS_1_CH_2_ISR_USED) || \
           (defined PWM_EMIOS_1_CH_2_ISR_USED) || \
           (defined ICU_EMIOS_1_CH_2_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_2 */
    if ( (REG_READ32(EMIOS_CCR(1, 2)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_2 */
        if ( ( REG_READ32(EMIOS_CSR(1, 2)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_2_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_2);
                #endif

                #if(defined PWM_EMIOS_1_CH_2_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_2);
                #endif

                #if(defined ICU_EMIOS_1_CH_2_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_2);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_1_CH_3_ISR_USED) || \
          (defined PWM_EMIOS_1_CH_3_ISR_USED) || \
          (defined ICU_EMIOS_1_CH_3_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_3 */
    if ( (REG_READ32(EMIOS_CCR(1, 3)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_3 */
        if ( ( REG_READ32(EMIOS_CSR(1, 3)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_3_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_3);
                #endif

                #if(defined PWM_EMIOS_1_CH_3_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_3);
                #endif

                #if(defined ICU_EMIOS_1_CH_3_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_3);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channels:4,5 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_4
*/
#if  ((defined GPT_EMIOS_1_CH_4_ISR_USED) && (defined PWM_EMIOS_1_CH_4_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_4"
#endif

#if  ((defined PWM_EMIOS_1_CH_4_ISR_USED) && (defined ICU_EMIOS_1_CH_4_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_4"
#endif

#if  ((defined ICU_EMIOS_1_CH_4_ISR_USED) && (defined GPT_EMIOS_1_CH_4_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_4"
#endif


/**
@brief resource conflict check for EMIOS_1_CH_5
*/
#if  ((defined GPT_EMIOS_1_CH_5_ISR_USED) && (defined PWM_EMIOS_1_CH_5_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_5"
#endif

#if  ((defined PWM_EMIOS_1_CH_5_ISR_USED) && (defined ICU_EMIOS_1_CH_5_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_5"
#endif

#if  ((defined ICU_EMIOS_1_CH_5_ISR_USED) && (defined GPT_EMIOS_1_CH_5_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_5"
#endif

#if ( (defined GPT_EMIOS_1_CH_4_ISR_USED) || (defined GPT_EMIOS_1_CH_5_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_4_ISR_USED) || (defined PWM_EMIOS_1_CH_5_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_4_ISR_USED) || (defined ICU_EMIOS_1_CH_5_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 4 and 5 for eMIOS_1 module
@details   Process the interrupt of eMIOS channels 4 and 5

@remarks   This will be defined only if eMIOS channels 4 or 5 are configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_4_CH_5_ISR)
{
     #if ( (defined GPT_EMIOS_1_CH_4_ISR_USED) || \
           (defined PWM_EMIOS_1_CH_4_ISR_USED) || \
           (defined ICU_EMIOS_1_CH_4_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_4 */
    if ( (REG_READ32(EMIOS_CCR(1, 4)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_4 */
        if ( ( REG_READ32(EMIOS_CSR(1, 4)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_4_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_4);
                #endif

                #if(defined PWM_EMIOS_1_CH_4_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_4);
                #endif

                #if(defined ICU_EMIOS_1_CH_4_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_4);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_1_CH_5_ISR_USED) || \
          (defined PWM_EMIOS_1_CH_5_ISR_USED) || \
          (defined ICU_EMIOS_1_CH_5_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_5 */
    if ( (REG_READ32(EMIOS_CCR(1, 5)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_5 */
        if ( ( REG_READ32(EMIOS_CSR(1, 5)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_5_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_5);
                #endif

                #if(defined PWM_EMIOS_1_CH_5_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_5);
                #endif

                #if(defined ICU_EMIOS_1_CH_5_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_5);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channels:6,7 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_6
*/
#if  ((defined GPT_EMIOS_1_CH_6_ISR_USED) && (defined PWM_EMIOS_1_CH_6_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_6"
#endif

#if  ((defined PWM_EMIOS_1_CH_6_ISR_USED) && (defined ICU_EMIOS_1_CH_6_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_6"
#endif

#if  ((defined ICU_EMIOS_1_CH_6_ISR_USED) && (defined GPT_EMIOS_1_CH_6_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_6"
#endif


/**
@brief resource conflict check for EMIOS_1_CH_7
*/
#if  ((defined GPT_EMIOS_1_CH_7_ISR_USED) && (defined PWM_EMIOS_1_CH_7_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_7"
#endif

#if  ((defined PWM_EMIOS_1_CH_7_ISR_USED) && (defined ICU_EMIOS_1_CH_7_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_7"
#endif

#if  ((defined ICU_EMIOS_1_CH_7_ISR_USED) && (defined GPT_EMIOS_1_CH_7_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_7"
#endif

#if ( (defined GPT_EMIOS_1_CH_6_ISR_USED) || (defined GPT_EMIOS_1_CH_7_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_6_ISR_USED) || (defined PWM_EMIOS_1_CH_7_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_6_ISR_USED) || (defined ICU_EMIOS_1_CH_7_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 6 and 7 for eMIOS_1 module
@details   Process the interrupt of eMIOS channels 6 and 7

@remarks   This will be defined only if eMIOS channels 6 or 7 are configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_6_CH_7_ISR)
{
     #if ( (defined GPT_EMIOS_1_CH_6_ISR_USED) || \
           (defined PWM_EMIOS_1_CH_6_ISR_USED) || \
           (defined ICU_EMIOS_1_CH_6_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_6 */
    if ( (REG_READ32(EMIOS_CCR(1, 6)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_6 */
        if ( ( REG_READ32(EMIOS_CSR(1, 6)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_6_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_6);
                #endif

                #if(defined PWM_EMIOS_1_CH_6_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_6);
                #endif

                #if(defined ICU_EMIOS_1_CH_6_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_6);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_1_CH_7_ISR_USED) || \
          (defined PWM_EMIOS_1_CH_7_ISR_USED) || \
          (defined ICU_EMIOS_1_CH_7_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_7 */
    if ( (REG_READ32(EMIOS_CCR(1, 7)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_7 */
        if ( ( REG_READ32(EMIOS_CSR(1, 7)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_7_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_7);
                #endif

                #if(defined PWM_EMIOS_1_CH_7_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_7);
                #endif

                #if(defined ICU_EMIOS_1_CH_7_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_7);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channels:8,9 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_8
*/
#if  ((defined GPT_EMIOS_1_CH_8_ISR_USED) && (defined PWM_EMIOS_1_CH_8_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_8"
#endif

#if  ((defined PWM_EMIOS_1_CH_8_ISR_USED) && (defined ICU_EMIOS_1_CH_8_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_8"
#endif

#if  ((defined ICU_EMIOS_1_CH_8_ISR_USED) && (defined GPT_EMIOS_1_CH_8_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_8"
#endif


/**
@brief resource conflict check for EMIOS_1_CH_9
*/
#if  ((defined GPT_EMIOS_1_CH_9_ISR_USED) && (defined PWM_EMIOS_1_CH_9_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_9"
#endif

#if  ((defined PWM_EMIOS_1_CH_9_ISR_USED) && (defined ICU_EMIOS_1_CH_9_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_9"
#endif

#if  ((defined ICU_EMIOS_1_CH_9_ISR_USED) && (defined GPT_EMIOS_1_CH_9_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_9"
#endif

#if ( (defined GPT_EMIOS_1_CH_8_ISR_USED) || (defined GPT_EMIOS_1_CH_9_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_8_ISR_USED) || (defined PWM_EMIOS_1_CH_9_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_8_ISR_USED) || (defined ICU_EMIOS_1_CH_9_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 8 and 9 for eMIOS_1 module
@details   Process the interrupt of eMIOS channels 8 and 9

@remarks   This will be defined only if eMIOS channels 8 or 9 are configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_8_CH_9_ISR)
{
     #if ( (defined GPT_EMIOS_1_CH_8_ISR_USED) || \
           (defined PWM_EMIOS_1_CH_8_ISR_USED) || \
           (defined ICU_EMIOS_1_CH_8_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_8 */
    if ( (REG_READ32(EMIOS_CCR(1, 8)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_8 */
        if ( ( REG_READ32(EMIOS_CSR(1, 8)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_8_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_8);
                #endif

                #if(defined PWM_EMIOS_1_CH_8_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_8);
                #endif

                #if(defined ICU_EMIOS_1_CH_8_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_8);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_1_CH_9_ISR_USED) || \
          (defined PWM_EMIOS_1_CH_9_ISR_USED) || \
          (defined ICU_EMIOS_1_CH_9_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_9 */
    if ( (REG_READ32(EMIOS_CCR(1, 9)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_9 */
        if ( ( REG_READ32(EMIOS_CSR(1, 9)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_9_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_9);
                #endif

                #if(defined PWM_EMIOS_1_CH_9_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_9);
                #endif

                #if(defined ICU_EMIOS_1_CH_9_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_9);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channels:10,11 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_10
*/
#if  ((defined GPT_EMIOS_1_CH_10_ISR_USED) && (defined PWM_EMIOS_1_CH_10_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_10"
#endif

#if  ((defined PWM_EMIOS_1_CH_10_ISR_USED) && (defined ICU_EMIOS_1_CH_10_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_10"
#endif

#if  ((defined ICU_EMIOS_1_CH_10_ISR_USED) && (defined GPT_EMIOS_1_CH_10_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_10"
#endif


/**
@brief resource conflict check for EMIOS_1_CH_11
*/
#if  ((defined GPT_EMIOS_1_CH_11_ISR_USED) && (defined PWM_EMIOS_1_CH_11_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_11"
#endif

#if  ((defined PWM_EMIOS_1_CH_11_ISR_USED) && (defined ICU_EMIOS_1_CH_11_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_11"
#endif

#if  ((defined ICU_EMIOS_1_CH_11_ISR_USED) && (defined GPT_EMIOS_1_CH_11_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_11"
#endif

#if ( (defined GPT_EMIOS_1_CH_10_ISR_USED) || (defined GPT_EMIOS_1_CH_11_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_10_ISR_USED) || (defined PWM_EMIOS_1_CH_11_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_10_ISR_USED) || (defined ICU_EMIOS_1_CH_11_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 10 and 11 for eMIOS_1 module
@details   Process the interrupt of eMIOS channels 10 and 11

@remarks   This will be defined only if eMIOS channels 10 or 11 are configured in GPT,
           ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_10_CH_11_ISR)
{
     #if ( (defined GPT_EMIOS_1_CH_10_ISR_USED) || \
           (defined PWM_EMIOS_1_CH_10_ISR_USED) || \
           (defined ICU_EMIOS_1_CH_10_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_10 */
    if ( (REG_READ32(EMIOS_CCR(1, 10)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_10 */
        if ( ( REG_READ32(EMIOS_CSR(1, 10)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_10_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_10);
                #endif

                #if(defined PWM_EMIOS_1_CH_10_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_10);
                #endif

                #if(defined ICU_EMIOS_1_CH_10_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_10);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_1_CH_11_ISR_USED) || \
          (defined PWM_EMIOS_1_CH_11_ISR_USED) || \
          (defined ICU_EMIOS_1_CH_11_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_11 */
    if ( (REG_READ32(EMIOS_CCR(1, 11)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_11 */
        if ( ( REG_READ32(EMIOS_CSR(1, 11)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_11_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_11);
                #endif

                #if(defined PWM_EMIOS_1_CH_11_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_11);
                #endif

                #if(defined ICU_EMIOS_1_CH_11_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_11);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channels:12,13 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_12
*/
#if  ((defined GPT_EMIOS_1_CH_12_ISR_USED) && (defined PWM_EMIOS_1_CH_12_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_12"
#endif

#if  ((defined PWM_EMIOS_1_CH_12_ISR_USED) && (defined ICU_EMIOS_1_CH_12_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_12"
#endif

#if  ((defined ICU_EMIOS_1_CH_12_ISR_USED) && (defined GPT_EMIOS_1_CH_12_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_12"
#endif


/**
@brief resource conflict check for EMIOS_1_CH_13
*/
#if  ((defined GPT_EMIOS_1_CH_13_ISR_USED) && (defined PWM_EMIOS_1_CH_13_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_13"
#endif

#if  ((defined PWM_EMIOS_1_CH_13_ISR_USED) && (defined ICU_EMIOS_1_CH_13_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_13"
#endif

#if  ((defined ICU_EMIOS_1_CH_13_ISR_USED) && (defined GPT_EMIOS_1_CH_13_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_13"
#endif

#if ( (defined GPT_EMIOS_1_CH_12_ISR_USED) || (defined GPT_EMIOS_1_CH_13_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_12_ISR_USED) || (defined PWM_EMIOS_1_CH_13_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_12_ISR_USED) || (defined ICU_EMIOS_1_CH_13_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 12 and 13 for eMIOS_1 module
@details   Process the interrupt of eMIOS channels 12 and 13

@remarks   This will be defined only if eMIOS channels 12 or 13 are configured in GPT,
           ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_12_CH_13_ISR)
{
     #if ( (defined GPT_EMIOS_1_CH_12_ISR_USED) || \
           (defined PWM_EMIOS_1_CH_12_ISR_USED) || \
           (defined ICU_EMIOS_1_CH_12_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_12 */
    if ( (REG_READ32(EMIOS_CCR(1, 12)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_12 */
        if ( ( REG_READ32(EMIOS_CSR(1, 12)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_12_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_12);
                #endif

                #if(defined PWM_EMIOS_1_CH_12_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_12);
                #endif

                #if(defined ICU_EMIOS_1_CH_12_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_12);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_1_CH_13_ISR_USED) || \
          (defined PWM_EMIOS_1_CH_13_ISR_USED) || \
          (defined ICU_EMIOS_1_CH_13_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_13 */
    if ( (REG_READ32(EMIOS_CCR(1, 13)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_13 */
        if ( ( REG_READ32(EMIOS_CSR(1, 13)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_13_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_13);
                #endif

                #if(defined PWM_EMIOS_1_CH_13_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_13);
                #endif

                #if(defined ICU_EMIOS_1_CH_13_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_13);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channels:14,15 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_14
*/
#if  ((defined GPT_EMIOS_1_CH_14_ISR_USED) && (defined PWM_EMIOS_1_CH_14_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_14"
#endif

#if  ((defined PWM_EMIOS_1_CH_14_ISR_USED) && (defined ICU_EMIOS_1_CH_14_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_14"
#endif

#if  ((defined ICU_EMIOS_1_CH_14_ISR_USED) && (defined GPT_EMIOS_1_CH_14_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_14"
#endif


/**
@brief resource conflict check for EMIOS_1_CH_15
*/
#if  ((defined GPT_EMIOS_1_CH_15_ISR_USED) && (defined PWM_EMIOS_1_CH_15_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_15"
#endif

#if  ((defined PWM_EMIOS_1_CH_15_ISR_USED) && (defined ICU_EMIOS_1_CH_15_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_15"
#endif

#if  ((defined ICU_EMIOS_1_CH_15_ISR_USED) && (defined GPT_EMIOS_1_CH_15_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_15"
#endif

#if ( (defined GPT_EMIOS_1_CH_14_ISR_USED) || (defined GPT_EMIOS_1_CH_15_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_14_ISR_USED) || (defined PWM_EMIOS_1_CH_15_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_14_ISR_USED) || (defined ICU_EMIOS_1_CH_15_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 14 and 15 for eMIOS_1 module
@details   Process the interrupt of eMIOS channels 14 and 15

@remarks   This will be defined only if eMIOS channels 14 or 15 are configured in GPT,
           ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_14_CH_15_ISR)
{
     #if ( (defined GPT_EMIOS_1_CH_14_ISR_USED) || \
           (defined PWM_EMIOS_1_CH_14_ISR_USED) || \
           (defined ICU_EMIOS_1_CH_14_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_14 */
    if ( (REG_READ32(EMIOS_CCR(1, 14)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_14 */
        if ( ( REG_READ32(EMIOS_CSR(1, 14)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_14_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_14);
                #endif

                #if(defined PWM_EMIOS_1_CH_14_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_14);
                #endif

                #if(defined ICU_EMIOS_1_CH_14_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_14);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_1_CH_15_ISR_USED) || \
          (defined PWM_EMIOS_1_CH_15_ISR_USED) || \
          (defined ICU_EMIOS_1_CH_15_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_15 */
    if ( (REG_READ32(EMIOS_CCR(1, 15)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_15 */
        if ( ( REG_READ32(EMIOS_CSR(1, 15)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_15_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_15);
                #endif

                #if(defined PWM_EMIOS_1_CH_15_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_15);
                #endif

                #if(defined ICU_EMIOS_1_CH_15_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_15);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channels:16,17 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_16
*/
#if  ((defined GPT_EMIOS_1_CH_16_ISR_USED) && (defined PWM_EMIOS_1_CH_16_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_16"
#endif

#if  ((defined PWM_EMIOS_1_CH_16_ISR_USED) && (defined ICU_EMIOS_1_CH_16_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_16"
#endif

#if  ((defined ICU_EMIOS_1_CH_16_ISR_USED) && (defined GPT_EMIOS_1_CH_16_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_16"
#endif


/**
@brief resource conflict check for EMIOS_1_CH_17
*/
#if  ((defined GPT_EMIOS_1_CH_17_ISR_USED) && (defined PWM_EMIOS_1_CH_17_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_17"
#endif

#if  ((defined PWM_EMIOS_1_CH_17_ISR_USED) && (defined ICU_EMIOS_1_CH_17_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_17"
#endif

#if  ((defined ICU_EMIOS_1_CH_17_ISR_USED) && (defined GPT_EMIOS_1_CH_17_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_17"
#endif

#if ( (defined GPT_EMIOS_1_CH_16_ISR_USED) || (defined GPT_EMIOS_1_CH_17_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_16_ISR_USED) || (defined PWM_EMIOS_1_CH_17_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_16_ISR_USED) || (defined ICU_EMIOS_1_CH_17_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 16 and 17 for eMIOS_1 module
@details   Process the interrupt of eMIOS channels 16 and 17

@remarks   This will be defined only if eMIOS channels 16 or 17 are configured in GPT,
           ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_16_CH_17_ISR)
{
     #if ( (defined GPT_EMIOS_1_CH_16_ISR_USED) || \
           (defined PWM_EMIOS_1_CH_16_ISR_USED) || \
           (defined ICU_EMIOS_1_CH_16_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_16 */
/**
 @file  Reg_eSys_EMIOS_IRQ.c
@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned int to pointer
                               - See Reg_eSys_EMIOS_IRQ_c_3 */
    if ( (REG_READ32(EMIOS_CCR(1, 16)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_16 */
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned int to pointer
                               - See Reg_eSys_EMIOS_IRQ_c_3 */
        if ( ( REG_READ32(EMIOS_CSR(1, 16)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_16_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_16);
                #endif

                #if(defined PWM_EMIOS_1_CH_16_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_16);
                #endif

                #if(defined ICU_EMIOS_1_CH_16_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_16);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_1_CH_17_ISR_USED) || \
          (defined PWM_EMIOS_1_CH_17_ISR_USED) || \
          (defined ICU_EMIOS_1_CH_17_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_17 */
    if ( (REG_READ32(EMIOS_CCR(1, 17)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_17 */
        if ( ( REG_READ32(EMIOS_CSR(1, 17)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_17_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_17);
                #endif

                #if(defined PWM_EMIOS_1_CH_17_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_17);
                #endif

                #if(defined ICU_EMIOS_1_CH_17_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_17);
                #endif
        }
    }
    #endif
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned int to pointer
                               - See Reg_eSys_EMIOS_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channels:18,19 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_18
*/
#if  ((defined GPT_EMIOS_1_CH_18_ISR_USED) && (defined PWM_EMIOS_1_CH_18_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_18"
#endif

#if  ((defined PWM_EMIOS_1_CH_18_ISR_USED) && (defined ICU_EMIOS_1_CH_18_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_18"
#endif

#if  ((defined ICU_EMIOS_1_CH_18_ISR_USED) && (defined GPT_EMIOS_1_CH_18_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_18"
#endif


/**
@brief resource conflict check for EMIOS_1_CH_19
*/
#if  ((defined GPT_EMIOS_1_CH_19_ISR_USED) && (defined PWM_EMIOS_1_CH_19_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_19"
#endif

#if  ((defined PWM_EMIOS_1_CH_19_ISR_USED) && (defined ICU_EMIOS_1_CH_19_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_19"
#endif

#if  ((defined ICU_EMIOS_1_CH_19_ISR_USED) && (defined GPT_EMIOS_1_CH_19_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_19"
#endif

#if ( (defined GPT_EMIOS_1_CH_18_ISR_USED) || (defined GPT_EMIOS_1_CH_19_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_18_ISR_USED) || (defined PWM_EMIOS_1_CH_19_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_18_ISR_USED) || (defined ICU_EMIOS_1_CH_19_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 18 and 19 for eMIOS_1 module
@details   Process the interrupt of eMIOS channels 18 and 19

@remarks   This will be defined only if eMIOS channels 18 or 19 are configured in GPT,
           ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_18_CH_19_ISR)
{
     #if ( (defined GPT_EMIOS_1_CH_18_ISR_USED) || \
           (defined PWM_EMIOS_1_CH_18_ISR_USED) || \
           (defined ICU_EMIOS_1_CH_18_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_18 */
    if ( (REG_READ32(EMIOS_CCR(1, 18)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_18 */
        if ( ( REG_READ32(EMIOS_CSR(1, 18)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_18_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_18);
                #endif

                #if(defined PWM_EMIOS_1_CH_18_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_18);
                #endif

                #if(defined ICU_EMIOS_1_CH_18_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_18);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_1_CH_19_ISR_USED) || \
          (defined PWM_EMIOS_1_CH_19_ISR_USED) || \
          (defined ICU_EMIOS_1_CH_19_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_19 */
    if ( (REG_READ32(EMIOS_CCR(1, 19)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_19 */
        if ( ( REG_READ32(EMIOS_CSR(1, 19)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_19_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_19);
                #endif

                #if(defined PWM_EMIOS_1_CH_19_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_19);
                #endif

                #if(defined ICU_EMIOS_1_CH_19_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_19);
                #endif
        }
    }
    #endif
    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channels:20,21 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_20
*/
#if  ((defined GPT_EMIOS_1_CH_20_ISR_USED) && (defined PWM_EMIOS_1_CH_20_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_20"
#endif

#if  ((defined PWM_EMIOS_1_CH_20_ISR_USED) && (defined ICU_EMIOS_1_CH_20_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_20"
#endif

#if  ((defined ICU_EMIOS_1_CH_20_ISR_USED) && (defined GPT_EMIOS_1_CH_20_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_20"
#endif


/**
@brief resource conflict check for EMIOS_1_CH_21
*/
#if  ((defined GPT_EMIOS_1_CH_21_ISR_USED) && (defined PWM_EMIOS_1_CH_21_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_21"
#endif

#if  ((defined PWM_EMIOS_1_CH_21_ISR_USED) && (defined ICU_EMIOS_1_CH_21_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_21"
#endif

#if  ((defined ICU_EMIOS_1_CH_21_ISR_USED) && (defined GPT_EMIOS_1_CH_21_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_21"
#endif

#if ( (defined GPT_EMIOS_1_CH_20_ISR_USED) || (defined GPT_EMIOS_1_CH_21_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_20_ISR_USED) || (defined PWM_EMIOS_1_CH_21_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_20_ISR_USED) || (defined ICU_EMIOS_1_CH_21_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 20 and 21 for eMIOS_1 module
@details   Process the interrupt of eMIOS channels 20 and 21

@remarks   This will be defined only if eMIOS channels 20 or 21 are configured in GPT,
           ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_20_CH_21_ISR)
{
     #if ( (defined GPT_EMIOS_1_CH_20_ISR_USED) || \
           (defined PWM_EMIOS_1_CH_20_ISR_USED) || \
           (defined ICU_EMIOS_1_CH_20_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_20 */
    if ( (REG_READ32(EMIOS_CCR(1, 20)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_20 */
        if ( ( REG_READ32(EMIOS_CSR(1, 20)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_20_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_20);
                #endif

                #if(defined PWM_EMIOS_1_CH_20_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_20);
                #endif

                #if(defined ICU_EMIOS_1_CH_20_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_20);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_1_CH_21_ISR_USED) || \
          (defined PWM_EMIOS_1_CH_21_ISR_USED) || \
          (defined ICU_EMIOS_1_CH_21_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_21 */
    if ( (REG_READ32(EMIOS_CCR(1, 21)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_21 */
        if ( ( REG_READ32(EMIOS_CSR(1, 21)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_21_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_21);
                #endif

                #if(defined PWM_EMIOS_1_CH_21_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_21);
                #endif

                #if(defined ICU_EMIOS_1_CH_21_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_21);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channels:22,23 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_22
*/
#if  ((defined GPT_EMIOS_1_CH_22_ISR_USED) && (defined PWM_EMIOS_1_CH_22_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_22"
#endif

#if  ((defined PWM_EMIOS_1_CH_22_ISR_USED) && (defined ICU_EMIOS_1_CH_22_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_22"
#endif

#if  ((defined ICU_EMIOS_1_CH_22_ISR_USED) && (defined GPT_EMIOS_1_CH_22_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_22"
#endif


/**
@brief resource conflict check for EMIOS_1_CH_23
*/
#if  ((defined GPT_EMIOS_1_CH_23_ISR_USED) && (defined PWM_EMIOS_1_CH_23_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_23"
#endif

#if  ((defined PWM_EMIOS_1_CH_23_ISR_USED) && (defined ICU_EMIOS_1_CH_23_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_23"
#endif

#if  ((defined ICU_EMIOS_1_CH_23_ISR_USED) && (defined GPT_EMIOS_1_CH_23_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_23"
#endif

#if ( (defined GPT_EMIOS_1_CH_22_ISR_USED) || (defined GPT_EMIOS_1_CH_23_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_22_ISR_USED) || (defined PWM_EMIOS_1_CH_23_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_22_ISR_USED) || (defined ICU_EMIOS_1_CH_23_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 22 and 23 for eMIOS_1 module
@details   Process the interrupt of eMIOS channels 22 and 23

@remarks   This will be defined only if eMIOS channels 22 or 23 are configured in GPT,
           ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_22_CH_23_ISR)
{
     #if ( (defined GPT_EMIOS_1_CH_22_ISR_USED) || \
           (defined PWM_EMIOS_1_CH_22_ISR_USED) || \
           (defined ICU_EMIOS_1_CH_22_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_22 */
    if ( (REG_READ32(EMIOS_CCR(1, 22)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_22 */
        if ( ( REG_READ32(EMIOS_CSR(1, 22)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_22_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_22);
                #endif

                #if(defined PWM_EMIOS_1_CH_22_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_22);
                #endif

                #if(defined ICU_EMIOS_1_CH_22_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_22);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_1_CH_23_ISR_USED) || \
          (defined PWM_EMIOS_1_CH_23_ISR_USED) || \
          (defined ICU_EMIOS_1_CH_23_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_23 */
    if ( (REG_READ32(EMIOS_CCR(1, 23)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_23 */
        if ( ( REG_READ32(EMIOS_CSR(1, 23)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_23_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_23);
                #endif

                #if(defined PWM_EMIOS_1_CH_23_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_23);
                #endif

                #if(defined ICU_EMIOS_1_CH_23_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_23);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channels:24,25 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_24
*/
#if  ((defined GPT_EMIOS_1_CH_24_ISR_USED) && (defined PWM_EMIOS_1_CH_24_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_24"
#endif

#if  ((defined PWM_EMIOS_1_CH_24_ISR_USED) && (defined ICU_EMIOS_1_CH_24_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_24"
#endif

#if  ((defined ICU_EMIOS_1_CH_24_ISR_USED) && (defined GPT_EMIOS_1_CH_24_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_24"
#endif


/**
@brief resource conflict check for EMIOS_1_CH_25
*/
#if  ((defined GPT_EMIOS_1_CH_25_ISR_USED) && (defined PWM_EMIOS_1_CH_25_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_25"
#endif

#if  ((defined PWM_EMIOS_1_CH_25_ISR_USED) && (defined ICU_EMIOS_1_CH_25_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_25"
#endif

#if  ((defined ICU_EMIOS_1_CH_25_ISR_USED) && (defined GPT_EMIOS_1_CH_25_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_25"
#endif

#if ( (defined GPT_EMIOS_1_CH_24_ISR_USED) || (defined GPT_EMIOS_1_CH_25_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_24_ISR_USED) || (defined PWM_EMIOS_1_CH_25_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_24_ISR_USED) || (defined ICU_EMIOS_1_CH_25_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 24 and 25 for eMIOS_1 module
@details   Process the interrupt of eMIOS channels 24 and 25

@remarks   This will be defined only if eMIOS channels 24 or 25 are configured in GPT,
           ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_24_CH_25_ISR)
{
     #if ( (defined GPT_EMIOS_1_CH_24_ISR_USED) || \
           (defined PWM_EMIOS_1_CH_24_ISR_USED) || \
           (defined ICU_EMIOS_1_CH_24_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_24 */
    if ( (REG_READ32(EMIOS_CCR(1, 24)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_24 */
        if ( ( REG_READ32(EMIOS_CSR(1, 24)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_24_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_24);
                #endif

                #if(defined PWM_EMIOS_1_CH_24_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_24);
                #endif

                #if(defined ICU_EMIOS_1_CH_24_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_24);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_1_CH_25_ISR_USED) || \
          (defined PWM_EMIOS_1_CH_25_ISR_USED) || \
          (defined ICU_EMIOS_1_CH_25_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_25 */
    if ( (REG_READ32(EMIOS_CCR(1, 25)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_25 */
        if ( ( REG_READ32(EMIOS_CSR(1, 25)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_25_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_25);
                #endif

                #if(defined PWM_EMIOS_1_CH_25_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_25);
                #endif

                #if(defined ICU_EMIOS_1_CH_25_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_25);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channels:26,27 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_26
*/
#if  ((defined GPT_EMIOS_1_CH_26_ISR_USED) && (defined PWM_EMIOS_1_CH_26_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_26"
#endif

#if  ((defined PWM_EMIOS_1_CH_26_ISR_USED) && (defined ICU_EMIOS_1_CH_26_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_26"
#endif

#if  ((defined ICU_EMIOS_1_CH_26_ISR_USED) && (defined GPT_EMIOS_1_CH_26_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_26"
#endif


/**
@brief resource conflict check for EMIOS_1_CH_27
*/
#if  ((defined GPT_EMIOS_1_CH_27_ISR_USED) && (defined PWM_EMIOS_1_CH_27_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_27"
#endif

#if  ((defined PWM_EMIOS_1_CH_27_ISR_USED) && (defined ICU_EMIOS_1_CH_27_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_27"
#endif

#if  ((defined ICU_EMIOS_1_CH_27_ISR_USED) && (defined GPT_EMIOS_1_CH_27_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_27"
#endif

#if ( (defined GPT_EMIOS_1_CH_26_ISR_USED) || (defined GPT_EMIOS_1_CH_27_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_26_ISR_USED) || (defined PWM_EMIOS_1_CH_27_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_26_ISR_USED) || (defined ICU_EMIOS_1_CH_27_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 26 and 27 for eMIOS_1 module
@details   Process the interrupt of eMIOS channels 26 and 27

@remarks   This will be defined only if eMIOS channels 26 or 27 are configured in GPT,
           ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_26_CH_27_ISR)
{
     #if ( (defined GPT_EMIOS_1_CH_26_ISR_USED) || \
           (defined PWM_EMIOS_1_CH_26_ISR_USED) || \
           (defined ICU_EMIOS_1_CH_26_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_26 */
    if ( (REG_READ32(EMIOS_CCR(1, 26)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_26 */
        if ( ( REG_READ32(EMIOS_CSR(1, 26)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_26_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_26);
                #endif

                #if(defined PWM_EMIOS_1_CH_26_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_26);
                #endif

                #if(defined ICU_EMIOS_1_CH_26_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_26);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_1_CH_27_ISR_USED) || \
          (defined PWM_EMIOS_1_CH_27_ISR_USED) || \
          (defined ICU_EMIOS_1_CH_27_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_27 */
    if ( (REG_READ32(EMIOS_CCR(1, 27)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_27 */
        if ( ( REG_READ32(EMIOS_CSR(1, 27)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_27_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_27);
                #endif

                #if(defined PWM_EMIOS_1_CH_27_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_27);
                #endif

                #if(defined ICU_EMIOS_1_CH_27_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_27);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channels:28,29 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_28
*/
#if  ((defined GPT_EMIOS_1_CH_28_ISR_USED) && (defined PWM_EMIOS_1_CH_28_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_28"
#endif

#if  ((defined PWM_EMIOS_1_CH_28_ISR_USED) && (defined ICU_EMIOS_1_CH_28_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_28"
#endif

#if  ((defined ICU_EMIOS_1_CH_28_ISR_USED) && (defined GPT_EMIOS_1_CH_28_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_28"
#endif


/**
@brief resource conflict check for EMIOS_1_CH_29
*/
#if  ((defined GPT_EMIOS_1_CH_29_ISR_USED) && (defined PWM_EMIOS_1_CH_29_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_29"
#endif

#if  ((defined PWM_EMIOS_1_CH_29_ISR_USED) && (defined ICU_EMIOS_1_CH_29_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_29"
#endif

#if  ((defined ICU_EMIOS_1_CH_29_ISR_USED) && (defined GPT_EMIOS_1_CH_29_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_29"
#endif

#if ( (defined GPT_EMIOS_1_CH_28_ISR_USED) || (defined GPT_EMIOS_1_CH_29_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_28_ISR_USED) || (defined PWM_EMIOS_1_CH_29_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_28_ISR_USED) || (defined ICU_EMIOS_1_CH_29_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 28 and 29 for eMIOS_1 module
@details   Process the interrupt of eMIOS channels 28 and 29

@remarks   This will be defined only if eMIOS channels 28 or 29 are configured in GPT,
           ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_28_CH_29_ISR)
{
     #if ( (defined GPT_EMIOS_1_CH_28_ISR_USED) || \
           (defined PWM_EMIOS_1_CH_28_ISR_USED) || \
           (defined ICU_EMIOS_1_CH_28_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_28 */
    if ( (REG_READ32(EMIOS_CCR(1, 28)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_28 */
        if ( ( REG_READ32(EMIOS_CSR(1, 28)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_28_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_28);
                #endif

                #if(defined PWM_EMIOS_1_CH_28_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_28);
                #endif

                #if(defined ICU_EMIOS_1_CH_28_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_28);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_1_CH_29_ISR_USED) || \
          (defined PWM_EMIOS_1_CH_29_ISR_USED) || \
          (defined ICU_EMIOS_1_CH_29_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_29 */
    if ( (REG_READ32(EMIOS_CCR(1, 29)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_29 */
        if ( ( REG_READ32(EMIOS_CSR(1, 29)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_29_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_29);
                #endif

                #if(defined PWM_EMIOS_1_CH_29_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_29);
                #endif

                #if(defined ICU_EMIOS_1_CH_29_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_29);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channels:30,31 common interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_30
*/
#if  ((defined GPT_EMIOS_1_CH_30_ISR_USED) && (defined PWM_EMIOS_1_CH_30_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_30"
#endif

#if  ((defined PWM_EMIOS_1_CH_30_ISR_USED) && (defined ICU_EMIOS_1_CH_30_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_30"
#endif

#if  ((defined ICU_EMIOS_1_CH_30_ISR_USED) && (defined GPT_EMIOS_1_CH_30_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_30"
#endif


/**
@brief resource conflict check for EMIOS_1_CH_31
*/
#if  ((defined GPT_EMIOS_1_CH_31_ISR_USED) && (defined PWM_EMIOS_1_CH_31_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_31"
#endif

#if  ((defined PWM_EMIOS_1_CH_31_ISR_USED) && (defined ICU_EMIOS_1_CH_31_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_31"
#endif

#if  ((defined ICU_EMIOS_1_CH_31_ISR_USED) && (defined GPT_EMIOS_1_CH_31_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_31"
#endif

#if ( (defined GPT_EMIOS_1_CH_30_ISR_USED) || (defined GPT_EMIOS_1_CH_31_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_30_ISR_USED) || (defined PWM_EMIOS_1_CH_31_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_30_ISR_USED) || (defined ICU_EMIOS_1_CH_31_ISR_USED) )

/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channels : 30 and 31 for eMIOS_1 module
@details   Process the interrupt of eMIOS channels 30 and 31

@remarks   This will be defined only if eMIOS channels 30 or 31 are configured in GPT,
           ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_30_CH_31_ISR)
{
     #if ( (defined GPT_EMIOS_1_CH_30_ISR_USED) || \
           (defined PWM_EMIOS_1_CH_30_ISR_USED) || \
           (defined ICU_EMIOS_1_CH_30_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_30 */
    if ( (REG_READ32(EMIOS_CCR(1, 30)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_30 */
        if ( ( REG_READ32(EMIOS_CSR(1, 30)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_30_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_30);
                #endif

                #if(defined PWM_EMIOS_1_CH_30_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_30);
                #endif

                #if(defined ICU_EMIOS_1_CH_30_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_30);
                #endif
        }
    }
    #endif

    #if ( (defined GPT_EMIOS_1_CH_31_ISR_USED) || \
          (defined PWM_EMIOS_1_CH_31_ISR_USED) || \
          (defined ICU_EMIOS_1_CH_31_ISR_USED) )


    /* Check that a match event generates an interrupt and interrupts are enabled for EMIOS_31 */
    if ( (REG_READ32(EMIOS_CCR(1, 31)) & (CCR_DMA_MASK | CCR_FEN_MASK)) ==
         ((CCR_DMA_ASSIGN_INT << CCR_DMA_SHIFT) | ( CCR_FEN_ENABLE << CCR_FEN_SHIFT ))) {

        /* Check if match event occured on EMIOS_31 */
        if ( ( REG_READ32(EMIOS_CSR(1, 31)) & CSR_FLAG_MASK) != 0U ) {

                #if(defined GPT_EMIOS_1_CH_31_ISR_USED)
                        EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_31);
                #endif

                #if(defined PWM_EMIOS_1_CH_31_ISR_USED)
                        EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_31);
                #endif

                #if(defined ICU_EMIOS_1_CH_31_ISR_USED)
                        EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_31);
                #endif
        }
    }
    #endif

    EXIT_INTERRUPT();
}
#endif



/*********************************** EMIOS 1 common interrupts END ********************************/



#else  /* EMIOS_COMMON_ISR_HANDLER == STD_OFF */




/*******************************************************************************/
/******* CHANNEL INDEPENDENT EMIOS INTERRUPT SERVICE ROUTINES DEFINITION *******/
/*******************************************************************************/



/*********************************** EMIOS 0 independent interrupts START *************************/


/**
@brief EMIOS module:0 channel:0 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_0
*/
#if  ((defined GPT_EMIOS_0_CH_0_ISR_USED) && (defined PWM_EMIOS_0_CH_0_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_0"
#endif

#if  ((defined PWM_EMIOS_0_CH_0_ISR_USED) && (defined ICU_EMIOS_0_CH_0_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_0"
#endif

#if  ((defined ICU_EMIOS_0_CH_0_ISR_USED) && (defined GPT_EMIOS_0_CH_0_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_0"
#endif


#if ( (defined GPT_EMIOS_0_CH_0_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_0_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_0_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 0 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 0

@remarks   This will be defined only if eMIOS channel 0 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_0_ISR)
{

    #if(defined GPT_EMIOS_0_CH_0_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_0);
    #endif

    #if(defined PWM_EMIOS_0_CH_0_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_0);
    #endif

    #if(defined ICU_EMIOS_0_CH_0_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_0);
    #endif
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned int to pointer
                               - See Reg_eSys_EMIOS_IRQ_c_3 */
    EXIT_INTERRUPT();

}
#endif


/**
@brief EMIOS module:0 channel:1 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_1
*/
#if  ((defined GPT_EMIOS_0_CH_1_ISR_USED) && (defined PWM_EMIOS_0_CH_1_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_1"
#endif

#if  ((defined PWM_EMIOS_0_CH_1_ISR_USED) && (defined ICU_EMIOS_0_CH_1_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_1"
#endif

#if  ((defined ICU_EMIOS_0_CH_1_ISR_USED) && (defined GPT_EMIOS_0_CH_1_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_1"
#endif


#if ( (defined GPT_EMIOS_0_CH_1_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_1_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_1_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 1 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 1

@remarks   This will be defined only if eMIOS channel 1 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_1_ISR)
{

    #if(defined GPT_EMIOS_0_CH_1_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_1);
    #endif

    #if(defined PWM_EMIOS_0_CH_1_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_1);
    #endif

    #if(defined ICU_EMIOS_0_CH_1_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_1);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:2 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_2
*/
#if  ((defined GPT_EMIOS_0_CH_2_ISR_USED) && (defined PWM_EMIOS_0_CH_2_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_2"
#endif

#if  ((defined PWM_EMIOS_0_CH_2_ISR_USED) && (defined ICU_EMIOS_0_CH_2_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_2"
#endif

#if  ((defined ICU_EMIOS_0_CH_2_ISR_USED) && (defined GPT_EMIOS_0_CH_2_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_2"
#endif


#if ( (defined GPT_EMIOS_0_CH_2_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_2_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_2_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 2 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 2

@remarks   This will be defined only if eMIOS channel 2 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_2_ISR)
{

    #if(defined GPT_EMIOS_0_CH_2_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_2);
    #endif

    #if(defined PWM_EMIOS_0_CH_2_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_2);
    #endif

    #if(defined ICU_EMIOS_0_CH_2_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_2);
    #endif


    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:3 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_3
*/
#if  ((defined GPT_EMIOS_0_CH_3_ISR_USED) && (defined PWM_EMIOS_0_CH_3_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_3"
#endif

#if  ((defined PWM_EMIOS_0_CH_3_ISR_USED) && (defined ICU_EMIOS_0_CH_3_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_3"
#endif

#if  ((defined ICU_EMIOS_0_CH_3_ISR_USED) && (defined GPT_EMIOS_0_CH_3_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_3"
#endif


#if ( (defined GPT_EMIOS_0_CH_3_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_3_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_3_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 3 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 3

@remarks   This will be defined only if eMIOS channel 3 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_3_ISR)
{

    #if(defined GPT_EMIOS_0_CH_3_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_3);
    #endif

    #if(defined PWM_EMIOS_0_CH_3_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_3);
    #endif

    #if(defined ICU_EMIOS_0_CH_3_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_3);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:4 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_4
*/
#if  ((defined GPT_EMIOS_0_CH_4_ISR_USED) && (defined PWM_EMIOS_0_CH_4_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_4"
#endif

#if  ((defined PWM_EMIOS_0_CH_4_ISR_USED) && (defined ICU_EMIOS_0_CH_4_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_4"
#endif

#if  ((defined ICU_EMIOS_0_CH_4_ISR_USED) && (defined GPT_EMIOS_0_CH_4_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_4"
#endif


#if ( (defined GPT_EMIOS_0_CH_4_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_4_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_4_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 4 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 4

@remarks   This will be defined only if eMIOS channel 4 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_4_ISR)
{

    #if(defined GPT_EMIOS_0_CH_4_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_4);
    #endif

    #if(defined PWM_EMIOS_0_CH_4_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_4);
    #endif

    #if(defined ICU_EMIOS_0_CH_4_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_4);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:5 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_5
*/
#if  ((defined GPT_EMIOS_0_CH_5_ISR_USED) && (defined PWM_EMIOS_0_CH_5_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_5"
#endif

#if  ((defined PWM_EMIOS_0_CH_5_ISR_USED) && (defined ICU_EMIOS_0_CH_5_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_5"
#endif

#if  ((defined ICU_EMIOS_0_CH_5_ISR_USED) && (defined GPT_EMIOS_0_CH_5_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_5"
#endif


#if ( (defined GPT_EMIOS_0_CH_5_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_5_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_5_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 5 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 5

@remarks   This will be defined only if eMIOS channel 5 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_5_ISR)
{

    #if(defined GPT_EMIOS_0_CH_5_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_5);
    #endif

    #if(defined PWM_EMIOS_0_CH_5_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_5);
    #endif

    #if(defined ICU_EMIOS_0_CH_5_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_5);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:6 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_6
*/
#if  ((defined GPT_EMIOS_0_CH_6_ISR_USED) && (defined PWM_EMIOS_0_CH_6_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_6"
#endif

#if  ((defined PWM_EMIOS_0_CH_6_ISR_USED) && (defined ICU_EMIOS_0_CH_6_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_6"
#endif

#if  ((defined ICU_EMIOS_0_CH_6_ISR_USED) && (defined GPT_EMIOS_0_CH_6_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_6"
#endif


#if ( (defined GPT_EMIOS_0_CH_6_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_6_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_6_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 6 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 6

@remarks   This will be defined only if eMIOS channel 6 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_6_ISR)
{

    #if(defined GPT_EMIOS_0_CH_6_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_6);
    #endif

    #if(defined PWM_EMIOS_0_CH_6_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_6);
    #endif

    #if(defined ICU_EMIOS_0_CH_6_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_6);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:7 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_7
*/
#if  ((defined GPT_EMIOS_0_CH_7_ISR_USED) && (defined PWM_EMIOS_0_CH_7_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_7"
#endif

#if  ((defined PWM_EMIOS_0_CH_7_ISR_USED) && (defined ICU_EMIOS_0_CH_7_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_7"
#endif

#if  ((defined ICU_EMIOS_0_CH_7_ISR_USED) && (defined GPT_EMIOS_0_CH_7_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_7"
#endif


#if ( (defined GPT_EMIOS_0_CH_7_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_7_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_7_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 7 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 7

@remarks   This will be defined only if eMIOS channel 7 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_7_ISR)
{

    #if(defined GPT_EMIOS_0_CH_7_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_7);
    #endif

    #if(defined PWM_EMIOS_0_CH_7_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_7);
    #endif

    #if(defined ICU_EMIOS_0_CH_7_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_7);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:8 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_8
*/
#if  ((defined GPT_EMIOS_0_CH_8_ISR_USED) && (defined PWM_EMIOS_0_CH_8_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_8"
#endif

#if  ((defined PWM_EMIOS_0_CH_8_ISR_USED) && (defined ICU_EMIOS_0_CH_8_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_8"
#endif

#if  ((defined ICU_EMIOS_0_CH_8_ISR_USED) && (defined GPT_EMIOS_0_CH_8_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_8"
#endif


#if ( (defined GPT_EMIOS_0_CH_8_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_8_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_8_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 8 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 8

@remarks   This will be defined only if eMIOS channel 8 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_8_ISR)
{

    #if(defined GPT_EMIOS_0_CH_8_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_8);
    #endif

    #if(defined PWM_EMIOS_0_CH_8_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_8);
    #endif

    #if(defined ICU_EMIOS_0_CH_8_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_8);
    #endif

/**
@file  Reg_eSys_EMIOS_IRQ.c
@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned int to pointer
                               - See Reg_eSys_EMIOS_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:9 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_9
*/
#if  ((defined GPT_EMIOS_0_CH_9_ISR_USED) && (defined PWM_EMIOS_0_CH_9_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_9"
#endif

#if  ((defined PWM_EMIOS_0_CH_9_ISR_USED) && (defined ICU_EMIOS_0_CH_9_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_9"
#endif

#if  ((defined ICU_EMIOS_0_CH_9_ISR_USED) && (defined GPT_EMIOS_0_CH_9_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_9"
#endif


#if ( (defined GPT_EMIOS_0_CH_9_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_9_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_9_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 9 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 9

@remarks   This will be defined only if eMIOS channel 9 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_9_ISR)
{

    #if(defined GPT_EMIOS_0_CH_9_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_9);
    #endif

    #if(defined PWM_EMIOS_0_CH_9_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_9);
    #endif

    #if(defined ICU_EMIOS_0_CH_9_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_9);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:10 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_10
*/
#if  ((defined GPT_EMIOS_0_CH_10_ISR_USED) && (defined PWM_EMIOS_0_CH_10_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_10"
#endif

#if  ((defined PWM_EMIOS_0_CH_10_ISR_USED) && (defined ICU_EMIOS_0_CH_10_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_10"
#endif

#if  ((defined ICU_EMIOS_0_CH_10_ISR_USED) && (defined GPT_EMIOS_0_CH_10_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_10"
#endif


#if ( (defined GPT_EMIOS_0_CH_10_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_10_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_10_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 10 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 10

@remarks   This will be defined only if eMIOS channel 10 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_10_ISR)
{

    #if(defined GPT_EMIOS_0_CH_10_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_10);
    #endif

    #if(defined PWM_EMIOS_0_CH_10_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_10);
    #endif

    #if(defined ICU_EMIOS_0_CH_10_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_10);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:11 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_11
*/
#if  ((defined GPT_EMIOS_0_CH_11_ISR_USED) && (defined PWM_EMIOS_0_CH_11_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_11"
#endif

#if  ((defined PWM_EMIOS_0_CH_11_ISR_USED) && (defined ICU_EMIOS_0_CH_11_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_11"
#endif

#if  ((defined ICU_EMIOS_0_CH_11_ISR_USED) && (defined GPT_EMIOS_0_CH_11_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_11"
#endif


#if ( (defined GPT_EMIOS_0_CH_11_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_11_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_11_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 11 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 11

@remarks   This will be defined only if eMIOS channel 11 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_11_ISR)
{

    #if(defined GPT_EMIOS_0_CH_11_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_11);
    #endif

    #if(defined PWM_EMIOS_0_CH_11_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_11);
    #endif

    #if(defined ICU_EMIOS_0_CH_11_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_11);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:12 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_12
*/
#if  ((defined GPT_EMIOS_0_CH_12_ISR_USED) && (defined PWM_EMIOS_0_CH_12_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_12"
#endif

#if  ((defined PWM_EMIOS_0_CH_12_ISR_USED) && (defined ICU_EMIOS_0_CH_12_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_12"
#endif

#if  ((defined ICU_EMIOS_0_CH_12_ISR_USED) && (defined GPT_EMIOS_0_CH_12_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_12"
#endif


#if ( (defined GPT_EMIOS_0_CH_12_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_12_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_12_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 12 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 12

@remarks   This will be defined only if eMIOS channel 12 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_12_ISR)
{

    #if(defined GPT_EMIOS_0_CH_12_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_12);
    #endif

    #if(defined PWM_EMIOS_0_CH_12_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_12);
    #endif

    #if(defined ICU_EMIOS_0_CH_12_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_12);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:13 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_13
*/
#if  ((defined GPT_EMIOS_0_CH_13_ISR_USED) && (defined PWM_EMIOS_0_CH_13_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_13"
#endif

#if  ((defined PWM_EMIOS_0_CH_13_ISR_USED) && (defined ICU_EMIOS_0_CH_13_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_13"
#endif

#if  ((defined ICU_EMIOS_0_CH_13_ISR_USED) && (defined GPT_EMIOS_0_CH_13_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_13"
#endif


#if ( (defined GPT_EMIOS_0_CH_13_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_13_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_13_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 13 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 13

@remarks   This will be defined only if eMIOS channel 13 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_13_ISR)
{

    #if(defined GPT_EMIOS_0_CH_13_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_13);
    #endif

    #if(defined PWM_EMIOS_0_CH_13_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_13);
    #endif

    #if(defined ICU_EMIOS_0_CH_13_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_13);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:14 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_14
*/
#if  ((defined GPT_EMIOS_0_CH_14_ISR_USED) && (defined PWM_EMIOS_0_CH_14_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_14"
#endif

#if  ((defined PWM_EMIOS_0_CH_14_ISR_USED) && (defined ICU_EMIOS_0_CH_14_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_14"
#endif

#if  ((defined ICU_EMIOS_0_CH_14_ISR_USED) && (defined GPT_EMIOS_0_CH_14_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_14"
#endif


#if ( (defined GPT_EMIOS_0_CH_14_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_14_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_14_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 14 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 14

@remarks   This will be defined only if eMIOS channel 14 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_14_ISR)
{

    #if(defined GPT_EMIOS_0_CH_14_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_14);
    #endif

    #if(defined PWM_EMIOS_0_CH_14_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_14);
    #endif

    #if(defined ICU_EMIOS_0_CH_14_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_14);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:15 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_15
*/
#if  ((defined GPT_EMIOS_0_CH_15_ISR_USED) && (defined PWM_EMIOS_0_CH_15_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_15"
#endif

#if  ((defined PWM_EMIOS_0_CH_15_ISR_USED) && (defined ICU_EMIOS_0_CH_15_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_15"
#endif

#if  ((defined ICU_EMIOS_0_CH_15_ISR_USED) && (defined GPT_EMIOS_0_CH_15_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_15"
#endif


#if ( (defined GPT_EMIOS_0_CH_15_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_15_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_15_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 15 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 15

@remarks   This will be defined only if eMIOS channel 15 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_15_ISR)
{

    #if(defined GPT_EMIOS_0_CH_15_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_15);
    #endif

    #if(defined PWM_EMIOS_0_CH_15_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_15);
    #endif

    #if(defined ICU_EMIOS_0_CH_15_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_15);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:16 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_16
*/
#if  ((defined GPT_EMIOS_0_CH_16_ISR_USED) && (defined PWM_EMIOS_0_CH_16_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_16"
#endif

#if  ((defined PWM_EMIOS_0_CH_16_ISR_USED) && (defined ICU_EMIOS_0_CH_16_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_16"
#endif

#if  ((defined ICU_EMIOS_0_CH_16_ISR_USED) && (defined GPT_EMIOS_0_CH_16_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_16"
#endif


#if ( (defined GPT_EMIOS_0_CH_16_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_16_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_16_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 16 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 16

@remarks   This will be defined only if eMIOS channel 16 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_16_ISR)
{

    #if(defined GPT_EMIOS_0_CH_16_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_16);
    #endif

    #if(defined PWM_EMIOS_0_CH_16_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_16);
    #endif

    #if(defined ICU_EMIOS_0_CH_16_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_16);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:17 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_17
*/
#if  ((defined GPT_EMIOS_0_CH_17_ISR_USED) && (defined PWM_EMIOS_0_CH_17_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_17"
#endif

#if  ((defined PWM_EMIOS_0_CH_17_ISR_USED) && (defined ICU_EMIOS_0_CH_17_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_17"
#endif

#if  ((defined ICU_EMIOS_0_CH_17_ISR_USED) && (defined GPT_EMIOS_0_CH_17_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_17"
#endif


#if ( (defined GPT_EMIOS_0_CH_17_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_17_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_17_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 17 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 17

@remarks   This will be defined only if eMIOS channel 17 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_17_ISR)
{

    #if(defined GPT_EMIOS_0_CH_17_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_17);
    #endif

    #if(defined PWM_EMIOS_0_CH_17_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_17);
    #endif

    #if(defined ICU_EMIOS_0_CH_17_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_17);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:18 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_18
*/
#if  ((defined GPT_EMIOS_0_CH_18_ISR_USED) && (defined PWM_EMIOS_0_CH_18_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_18"
#endif

#if  ((defined PWM_EMIOS_0_CH_18_ISR_USED) && (defined ICU_EMIOS_0_CH_18_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_18"
#endif

#if  ((defined ICU_EMIOS_0_CH_18_ISR_USED) && (defined GPT_EMIOS_0_CH_18_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_18"
#endif


#if ( (defined GPT_EMIOS_0_CH_18_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_18_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_18_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 18 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 18

@remarks   This will be defined only if eMIOS channel 18 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_18_ISR)
{

    #if(defined GPT_EMIOS_0_CH_18_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_18);
    #endif

    #if(defined PWM_EMIOS_0_CH_18_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_18);
    #endif

    #if(defined ICU_EMIOS_0_CH_18_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_18);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:19 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_19
*/
#if  ((defined GPT_EMIOS_0_CH_19_ISR_USED) && (defined PWM_EMIOS_0_CH_19_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_19"
#endif

#if  ((defined PWM_EMIOS_0_CH_19_ISR_USED) && (defined ICU_EMIOS_0_CH_19_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_19"
#endif

#if  ((defined ICU_EMIOS_0_CH_19_ISR_USED) && (defined GPT_EMIOS_0_CH_19_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_19"
#endif


#if ( (defined GPT_EMIOS_0_CH_19_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_19_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_19_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 19 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 19

@remarks   This will be defined only if eMIOS channel 19 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_19_ISR)
{

    #if(defined GPT_EMIOS_0_CH_19_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_19);
    #endif

    #if(defined PWM_EMIOS_0_CH_19_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_19);
    #endif

    #if(defined ICU_EMIOS_0_CH_19_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_19);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:20 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_20
*/
#if  ((defined GPT_EMIOS_0_CH_20_ISR_USED) && (defined PWM_EMIOS_0_CH_20_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_20"
#endif

#if  ((defined PWM_EMIOS_0_CH_20_ISR_USED) && (defined ICU_EMIOS_0_CH_20_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_20"
#endif

#if  ((defined ICU_EMIOS_0_CH_20_ISR_USED) && (defined GPT_EMIOS_0_CH_20_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_20"
#endif


#if ( (defined GPT_EMIOS_0_CH_20_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_20_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_20_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 20 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 20

@remarks   This will be defined only if eMIOS channel 20 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_20_ISR)
{

    #if(defined GPT_EMIOS_0_CH_20_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_20);
    #endif

    #if(defined PWM_EMIOS_0_CH_20_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_20);
    #endif

    #if(defined ICU_EMIOS_0_CH_20_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_20);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:21 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_21
*/
#if  ((defined GPT_EMIOS_0_CH_21_ISR_USED) && (defined PWM_EMIOS_0_CH_21_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_21"
#endif

#if  ((defined PWM_EMIOS_0_CH_21_ISR_USED) && (defined ICU_EMIOS_0_CH_21_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_21"
#endif

#if  ((defined ICU_EMIOS_0_CH_21_ISR_USED) && (defined GPT_EMIOS_0_CH_21_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_21"
#endif


#if ( (defined GPT_EMIOS_0_CH_21_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_21_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_21_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 21 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 21

@remarks   This will be defined only if eMIOS channel 21 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_21_ISR)
{

    #if(defined GPT_EMIOS_0_CH_21_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_21);
    #endif

    #if(defined PWM_EMIOS_0_CH_21_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_21);
    #endif

    #if(defined ICU_EMIOS_0_CH_21_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_21);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:22 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_22
*/
#if  ((defined GPT_EMIOS_0_CH_22_ISR_USED) && (defined PWM_EMIOS_0_CH_22_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_22"
#endif

#if  ((defined PWM_EMIOS_0_CH_22_ISR_USED) && (defined ICU_EMIOS_0_CH_22_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_22"
#endif

#if  ((defined ICU_EMIOS_0_CH_22_ISR_USED) && (defined GPT_EMIOS_0_CH_22_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_22"
#endif


#if ( (defined GPT_EMIOS_0_CH_22_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_22_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_22_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 22 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 22

@remarks   This will be defined only if eMIOS channel 22 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_22_ISR)
{

    #if(defined GPT_EMIOS_0_CH_22_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_22);
    #endif

    #if(defined PWM_EMIOS_0_CH_22_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_22);
    #endif

    #if(defined ICU_EMIOS_0_CH_22_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_22);
    #endif

/**
@file  Reg_eSys_EMIOS_IRQ.c
@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned int to pointer
                               - See Reg_eSys_EMIOS_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:23 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_23
*/
#if  ((defined GPT_EMIOS_0_CH_23_ISR_USED) && (defined PWM_EMIOS_0_CH_23_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_23"
#endif

#if  ((defined PWM_EMIOS_0_CH_23_ISR_USED) && (defined ICU_EMIOS_0_CH_23_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_23"
#endif

#if  ((defined ICU_EMIOS_0_CH_23_ISR_USED) && (defined GPT_EMIOS_0_CH_23_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_23"
#endif


#if ( (defined GPT_EMIOS_0_CH_23_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_23_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_23_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 23 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 23

@remarks   This will be defined only if eMIOS channel 23 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_23_ISR)
{

    #if(defined GPT_EMIOS_0_CH_23_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_23);
    #endif

    #if(defined PWM_EMIOS_0_CH_23_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_23);
    #endif

    #if(defined ICU_EMIOS_0_CH_23_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_23);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:24 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_24
*/
#if  ((defined GPT_EMIOS_0_CH_24_ISR_USED) && (defined PWM_EMIOS_0_CH_24_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_24"
#endif

#if  ((defined PWM_EMIOS_0_CH_24_ISR_USED) && (defined ICU_EMIOS_0_CH_24_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_24"
#endif

#if  ((defined ICU_EMIOS_0_CH_24_ISR_USED) && (defined GPT_EMIOS_0_CH_24_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_24"
#endif


#if ( (defined GPT_EMIOS_0_CH_24_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_24_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_24_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 24 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 24

@remarks   This will be defined only if eMIOS channel 24 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_24_ISR)
{

    #if(defined GPT_EMIOS_0_CH_24_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_24);
    #endif

    #if(defined PWM_EMIOS_0_CH_24_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_24);
    #endif

    #if(defined ICU_EMIOS_0_CH_24_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_24);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:25 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_25
*/
#if  ((defined GPT_EMIOS_0_CH_25_ISR_USED) && (defined PWM_EMIOS_0_CH_25_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_25"
#endif

#if  ((defined PWM_EMIOS_0_CH_25_ISR_USED) && (defined ICU_EMIOS_0_CH_25_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_25"
#endif

#if  ((defined ICU_EMIOS_0_CH_25_ISR_USED) && (defined GPT_EMIOS_0_CH_25_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_25"
#endif


#if ( (defined GPT_EMIOS_0_CH_25_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_25_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_25_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 25 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 25

@remarks   This will be defined only if eMIOS channel 25 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_25_ISR)
{

    #if(defined GPT_EMIOS_0_CH_25_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_25);
    #endif

    #if(defined PWM_EMIOS_0_CH_25_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_25);
    #endif

    #if(defined ICU_EMIOS_0_CH_25_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_25);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:26 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_26
*/
#if  ((defined GPT_EMIOS_0_CH_26_ISR_USED) && (defined PWM_EMIOS_0_CH_26_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_26"
#endif

#if  ((defined PWM_EMIOS_0_CH_26_ISR_USED) && (defined ICU_EMIOS_0_CH_26_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_26"
#endif

#if  ((defined ICU_EMIOS_0_CH_26_ISR_USED) && (defined GPT_EMIOS_0_CH_26_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_26"
#endif


#if ( (defined GPT_EMIOS_0_CH_26_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_26_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_26_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 26 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 26

@remarks   This will be defined only if eMIOS channel 26 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_26_ISR)
{

    #if(defined GPT_EMIOS_0_CH_26_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_26);
    #endif

    #if(defined PWM_EMIOS_0_CH_26_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_26);
    #endif

    #if(defined ICU_EMIOS_0_CH_26_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_26);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:27 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_27
*/
#if  ((defined GPT_EMIOS_0_CH_27_ISR_USED) && (defined PWM_EMIOS_0_CH_27_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_27"
#endif

#if  ((defined PWM_EMIOS_0_CH_27_ISR_USED) && (defined ICU_EMIOS_0_CH_27_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_27"
#endif

#if  ((defined ICU_EMIOS_0_CH_27_ISR_USED) && (defined GPT_EMIOS_0_CH_27_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_27"
#endif


#if ( (defined GPT_EMIOS_0_CH_27_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_27_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_27_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 27 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 27

@remarks   This will be defined only if eMIOS channel 27 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_27_ISR)
{

    #if(defined GPT_EMIOS_0_CH_27_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_27);
    #endif

    #if(defined PWM_EMIOS_0_CH_27_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_27);
    #endif

    #if(defined ICU_EMIOS_0_CH_27_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_27);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:28 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_28
*/
#if  ((defined GPT_EMIOS_0_CH_28_ISR_USED) && (defined PWM_EMIOS_0_CH_28_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_28"
#endif

#if  ((defined PWM_EMIOS_0_CH_28_ISR_USED) && (defined ICU_EMIOS_0_CH_28_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_28"
#endif

#if  ((defined ICU_EMIOS_0_CH_28_ISR_USED) && (defined GPT_EMIOS_0_CH_28_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_28"
#endif


#if ( (defined GPT_EMIOS_0_CH_28_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_28_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_28_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 28 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 28

@remarks   This will be defined only if eMIOS channel 28 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_28_ISR)
{

    #if(defined GPT_EMIOS_0_CH_28_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_28);
    #endif

    #if(defined PWM_EMIOS_0_CH_28_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_28);
    #endif

    #if(defined ICU_EMIOS_0_CH_28_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_28);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:29 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_29
*/
#if  ((defined GPT_EMIOS_0_CH_29_ISR_USED) && (defined PWM_EMIOS_0_CH_29_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_29"
#endif

#if  ((defined PWM_EMIOS_0_CH_29_ISR_USED) && (defined ICU_EMIOS_0_CH_29_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_29"
#endif

#if  ((defined ICU_EMIOS_0_CH_29_ISR_USED) && (defined GPT_EMIOS_0_CH_29_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_29"
#endif


#if ( (defined GPT_EMIOS_0_CH_29_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_29_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_29_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 29 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 29

@remarks   This will be defined only if eMIOS channel 29 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_29_ISR)
{

    #if(defined GPT_EMIOS_0_CH_29_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_29);
    #endif

    #if(defined PWM_EMIOS_0_CH_29_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_29);
    #endif

    #if(defined ICU_EMIOS_0_CH_29_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_29);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:30 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_30
*/
#if  ((defined GPT_EMIOS_0_CH_30_ISR_USED) && (defined PWM_EMIOS_0_CH_30_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_30"
#endif

#if  ((defined PWM_EMIOS_0_CH_30_ISR_USED) && (defined ICU_EMIOS_0_CH_30_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_30"
#endif

#if  ((defined ICU_EMIOS_0_CH_30_ISR_USED) && (defined GPT_EMIOS_0_CH_30_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_30"
#endif


#if ( (defined GPT_EMIOS_0_CH_30_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_30_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_30_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 30 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 30

@remarks   This will be defined only if eMIOS channel 30 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_30_ISR)
{

    #if(defined GPT_EMIOS_0_CH_30_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_30);
    #endif

    #if(defined PWM_EMIOS_0_CH_30_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_30);
    #endif

    #if(defined ICU_EMIOS_0_CH_30_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_30);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:0 channel:31 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_0_CH_31
*/
#if  ((defined GPT_EMIOS_0_CH_31_ISR_USED) && (defined PWM_EMIOS_0_CH_31_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_0_31"
#endif

#if  ((defined PWM_EMIOS_0_CH_31_ISR_USED) && (defined ICU_EMIOS_0_CH_31_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_0_31"
#endif

#if  ((defined ICU_EMIOS_0_CH_31_ISR_USED) && (defined GPT_EMIOS_0_CH_31_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_0_31"
#endif


#if ( (defined GPT_EMIOS_0_CH_31_ISR_USED) || \
      (defined PWM_EMIOS_0_CH_31_ISR_USED) || \
      (defined ICU_EMIOS_0_CH_31_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 31 for eMIOS_0 module
@details   Process the interrupt of eMIOS channel 31

@remarks   This will be defined only if eMIOS channel 31 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_0_CH_31_ISR)
{

    #if(defined GPT_EMIOS_0_CH_31_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_0_CH_31);
    #endif

    #if(defined PWM_EMIOS_0_CH_31_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_0_CH_31);
    #endif

    #if(defined ICU_EMIOS_0_CH_31_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_0_CH_31);
    #endif

    EXIT_INTERRUPT();
}
#endif



/*********************************** EMIOS 0 independent interrupts END ***************************/



/*********************************** EMIOS 1 independent interrupts START *************************/


/**
@brief EMIOS module:1 channel:0 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_0
*/
#if  ((defined GPT_EMIOS_1_CH_0_ISR_USED) && (defined PWM_EMIOS_1_CH_0_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_0"
#endif

#if  ((defined PWM_EMIOS_1_CH_0_ISR_USED) && (defined ICU_EMIOS_1_CH_0_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_0"
#endif

#if  ((defined ICU_EMIOS_1_CH_0_ISR_USED) && (defined GPT_EMIOS_1_CH_0_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_0"
#endif


#if ( (defined GPT_EMIOS_1_CH_0_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_0_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_0_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 0 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 0

@remarks   This will be defined only if eMIOS channel 0 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_0_ISR)
{

    #if(defined GPT_EMIOS_1_CH_0_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_0);
    #endif

    #if(defined PWM_EMIOS_1_CH_0_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_0);
    #endif

    #if(defined ICU_EMIOS_1_CH_0_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_0);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:1 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_1
*/
#if  ((defined GPT_EMIOS_1_CH_1_ISR_USED) && (defined PWM_EMIOS_1_CH_1_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_1"
#endif

#if  ((defined PWM_EMIOS_1_CH_1_ISR_USED) && (defined ICU_EMIOS_1_CH_1_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_1"
#endif

#if  ((defined ICU_EMIOS_1_CH_1_ISR_USED) && (defined GPT_EMIOS_1_CH_1_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_1"
#endif


#if ( (defined GPT_EMIOS_1_CH_1_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_1_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_1_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 1 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 1

@remarks   This will be defined only if eMIOS channel 1 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_1_ISR)
{

    #if(defined GPT_EMIOS_1_CH_1_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_1);
    #endif

    #if(defined PWM_EMIOS_1_CH_1_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_1);
    #endif

    #if(defined ICU_EMIOS_1_CH_1_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_1);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:2 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_2
*/
#if  ((defined GPT_EMIOS_1_CH_2_ISR_USED) && (defined PWM_EMIOS_1_CH_2_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_2"
#endif

#if  ((defined PWM_EMIOS_1_CH_2_ISR_USED) && (defined ICU_EMIOS_1_CH_2_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_2"
#endif

#if  ((defined ICU_EMIOS_1_CH_2_ISR_USED) && (defined GPT_EMIOS_1_CH_2_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_2"
#endif


#if ( (defined GPT_EMIOS_1_CH_2_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_2_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_2_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 2 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 2

@remarks   This will be defined only if eMIOS channel 2 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_2_ISR)
{

    #if(defined GPT_EMIOS_1_CH_2_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_2);
    #endif

    #if(defined PWM_EMIOS_1_CH_2_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_2);
    #endif

    #if(defined ICU_EMIOS_1_CH_2_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_2);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:3 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_3
*/
#if  ((defined GPT_EMIOS_1_CH_3_ISR_USED) && (defined PWM_EMIOS_1_CH_3_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_3"
#endif

#if  ((defined PWM_EMIOS_1_CH_3_ISR_USED) && (defined ICU_EMIOS_1_CH_3_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_3"
#endif

#if  ((defined ICU_EMIOS_1_CH_3_ISR_USED) && (defined GPT_EMIOS_1_CH_3_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_3"
#endif


#if ( (defined GPT_EMIOS_1_CH_3_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_3_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_3_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 3 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 3

@remarks   This will be defined only if eMIOS channel 3 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_3_ISR)
{

    #if(defined GPT_EMIOS_1_CH_3_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_3);
    #endif

    #if(defined PWM_EMIOS_1_CH_3_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_3);
    #endif

    #if(defined ICU_EMIOS_1_CH_3_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_3);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:4 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_4
*/
#if  ((defined GPT_EMIOS_1_CH_4_ISR_USED) && (defined PWM_EMIOS_1_CH_4_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_4"
#endif

#if  ((defined PWM_EMIOS_1_CH_4_ISR_USED) && (defined ICU_EMIOS_1_CH_4_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_4"
#endif

#if  ((defined ICU_EMIOS_1_CH_4_ISR_USED) && (defined GPT_EMIOS_1_CH_4_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_4"
#endif


#if ( (defined GPT_EMIOS_1_CH_4_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_4_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_4_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 4 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 4

@remarks   This will be defined only if eMIOS channel 4 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_4_ISR)
{

    #if(defined GPT_EMIOS_1_CH_4_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_4);
    #endif

    #if(defined PWM_EMIOS_1_CH_4_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_4);
    #endif

    #if(defined ICU_EMIOS_1_CH_4_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_4);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:5 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_5
*/
#if  ((defined GPT_EMIOS_1_CH_5_ISR_USED) && (defined PWM_EMIOS_1_CH_5_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_5"
#endif

#if  ((defined PWM_EMIOS_1_CH_5_ISR_USED) && (defined ICU_EMIOS_1_CH_5_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_5"
#endif

#if  ((defined ICU_EMIOS_1_CH_5_ISR_USED) && (defined GPT_EMIOS_1_CH_5_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_5"
#endif


#if ( (defined GPT_EMIOS_1_CH_5_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_5_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_5_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 5 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 5

@remarks   This will be defined only if eMIOS channel 5 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_5_ISR)
{

    #if(defined GPT_EMIOS_1_CH_5_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_5);
    #endif

    #if(defined PWM_EMIOS_1_CH_5_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_5);
    #endif

    #if(defined ICU_EMIOS_1_CH_5_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_5);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:6 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_6
*/
#if  ((defined GPT_EMIOS_1_CH_6_ISR_USED) && (defined PWM_EMIOS_1_CH_6_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_6"
#endif

#if  ((defined PWM_EMIOS_1_CH_6_ISR_USED) && (defined ICU_EMIOS_1_CH_6_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_6"
#endif

#if  ((defined ICU_EMIOS_1_CH_6_ISR_USED) && (defined GPT_EMIOS_1_CH_6_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_6"
#endif


#if ( (defined GPT_EMIOS_1_CH_6_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_6_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_6_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 6 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 6

@remarks   This will be defined only if eMIOS channel 6 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_6_ISR)
{

    #if(defined GPT_EMIOS_1_CH_6_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_6);
    #endif

    #if(defined PWM_EMIOS_1_CH_6_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_6);
    #endif

    #if(defined ICU_EMIOS_1_CH_6_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_6);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:7 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_7
*/
#if  ((defined GPT_EMIOS_1_CH_7_ISR_USED) && (defined PWM_EMIOS_1_CH_7_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_7"
#endif

#if  ((defined PWM_EMIOS_1_CH_7_ISR_USED) && (defined ICU_EMIOS_1_CH_7_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_7"
#endif

#if  ((defined ICU_EMIOS_1_CH_7_ISR_USED) && (defined GPT_EMIOS_1_CH_7_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_7"
#endif


#if ( (defined GPT_EMIOS_1_CH_7_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_7_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_7_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 7 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 7

@remarks   This will be defined only if eMIOS channel 7 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_7_ISR)
{

    #if(defined GPT_EMIOS_1_CH_7_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_7);
    #endif

    #if(defined PWM_EMIOS_1_CH_7_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_7);
    #endif

    #if(defined ICU_EMIOS_1_CH_7_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_7);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:8 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_8
*/
#if  ((defined GPT_EMIOS_1_CH_8_ISR_USED) && (defined PWM_EMIOS_1_CH_8_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_8"
#endif

#if  ((defined PWM_EMIOS_1_CH_8_ISR_USED) && (defined ICU_EMIOS_1_CH_8_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_8"
#endif

#if  ((defined ICU_EMIOS_1_CH_8_ISR_USED) && (defined GPT_EMIOS_1_CH_8_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_8"
#endif


#if ( (defined GPT_EMIOS_1_CH_8_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_8_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_8_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 8 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 8

@remarks   This will be defined only if eMIOS channel 8 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_8_ISR)
{

    #if(defined GPT_EMIOS_1_CH_8_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_8);
    #endif

    #if(defined PWM_EMIOS_1_CH_8_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_8);
    #endif

    #if(defined ICU_EMIOS_1_CH_8_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_8);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:9 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_9
*/
#if  ((defined GPT_EMIOS_1_CH_9_ISR_USED) && (defined PWM_EMIOS_1_CH_9_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_9"
#endif

#if  ((defined PWM_EMIOS_1_CH_9_ISR_USED) && (defined ICU_EMIOS_1_CH_9_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_9"
#endif

#if  ((defined ICU_EMIOS_1_CH_9_ISR_USED) && (defined GPT_EMIOS_1_CH_9_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_9"
#endif


#if ( (defined GPT_EMIOS_1_CH_9_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_9_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_9_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 9 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 9

@remarks   This will be defined only if eMIOS channel 9 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_9_ISR)
{

    #if(defined GPT_EMIOS_1_CH_9_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_9);
    #endif

    #if(defined PWM_EMIOS_1_CH_9_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_9);
    #endif

    #if(defined ICU_EMIOS_1_CH_9_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_9);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:10 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_10
*/
#if  ((defined GPT_EMIOS_1_CH_10_ISR_USED) && (defined PWM_EMIOS_1_CH_10_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_10"
#endif

#if  ((defined PWM_EMIOS_1_CH_10_ISR_USED) && (defined ICU_EMIOS_1_CH_10_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_10"
#endif

#if  ((defined ICU_EMIOS_1_CH_10_ISR_USED) && (defined GPT_EMIOS_1_CH_10_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_10"
#endif


#if ( (defined GPT_EMIOS_1_CH_10_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_10_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_10_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 10 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 10

@remarks   This will be defined only if eMIOS channel 10 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_10_ISR)
{

    #if(defined GPT_EMIOS_1_CH_10_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_10);
    #endif

    #if(defined PWM_EMIOS_1_CH_10_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_10);
    #endif

    #if(defined ICU_EMIOS_1_CH_10_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_10);
    #endif

    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:11 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_11
*/
#if  ((defined GPT_EMIOS_1_CH_11_ISR_USED) && (defined PWM_EMIOS_1_CH_11_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_11"
#endif

#if  ((defined PWM_EMIOS_1_CH_11_ISR_USED) && (defined ICU_EMIOS_1_CH_11_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_11"
#endif

#if  ((defined ICU_EMIOS_1_CH_11_ISR_USED) && (defined GPT_EMIOS_1_CH_11_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_11"
#endif


#if ( (defined GPT_EMIOS_1_CH_11_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_11_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_11_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 11 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 11

@remarks   This will be defined only if eMIOS channel 11 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_11_ISR)
{

    #if(defined GPT_EMIOS_1_CH_11_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_11);
    #endif

    #if(defined PWM_EMIOS_1_CH_11_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_11);
    #endif

    #if(defined ICU_EMIOS_1_CH_11_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_11);
    #endif
/**
@file  Reg_eSys_EMIOS_IRQ.c
    @note Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned int to pointer
    @ref Reg_eSys_EMIOS_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:12 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_12
*/
#if  ((defined GPT_EMIOS_1_CH_12_ISR_USED) && (defined PWM_EMIOS_1_CH_12_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_12"
#endif

#if  ((defined PWM_EMIOS_1_CH_12_ISR_USED) && (defined ICU_EMIOS_1_CH_12_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_12"
#endif

#if  ((defined ICU_EMIOS_1_CH_12_ISR_USED) && (defined GPT_EMIOS_1_CH_12_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_12"
#endif


#if ( (defined GPT_EMIOS_1_CH_12_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_12_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_12_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 12 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 12

@remarks   This will be defined only if eMIOS channel 12 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_12_ISR)
{

    #if(defined GPT_EMIOS_1_CH_12_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_12);
    #endif

    #if(defined PWM_EMIOS_1_CH_12_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_12);
    #endif

    #if(defined ICU_EMIOS_1_CH_12_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_12);
    #endif
/**
@file  Reg_eSys_EMIOS_IRQ.c
    @note Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned int to pointer
    @ref Reg_eSys_EMIOS_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:13 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_13
*/
#if  ((defined GPT_EMIOS_1_CH_13_ISR_USED) && (defined PWM_EMIOS_1_CH_13_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_13"
#endif

#if  ((defined PWM_EMIOS_1_CH_13_ISR_USED) && (defined ICU_EMIOS_1_CH_13_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_13"
#endif

#if  ((defined ICU_EMIOS_1_CH_13_ISR_USED) && (defined GPT_EMIOS_1_CH_13_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_13"
#endif


#if ( (defined GPT_EMIOS_1_CH_13_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_13_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_13_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 13 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 13

@remarks   This will be defined only if eMIOS channel 13 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_13_ISR)
{

    #if(defined GPT_EMIOS_1_CH_13_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_13);
    #endif

    #if(defined PWM_EMIOS_1_CH_13_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_13);
    #endif

    #if(defined ICU_EMIOS_1_CH_13_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_13);
    #endif
/**
@file  Reg_eSys_EMIOS_IRQ.c
    @note Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned int to pointer
    @ref Reg_eSys_EMIOS_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:14 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_14
*/
#if  ((defined GPT_EMIOS_1_CH_14_ISR_USED) && (defined PWM_EMIOS_1_CH_14_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_14"
#endif

#if  ((defined PWM_EMIOS_1_CH_14_ISR_USED) && (defined ICU_EMIOS_1_CH_14_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_14"
#endif

#if  ((defined ICU_EMIOS_1_CH_14_ISR_USED) && (defined GPT_EMIOS_1_CH_14_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_14"
#endif


#if ( (defined GPT_EMIOS_1_CH_14_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_14_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_14_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 14 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 14

@remarks   This will be defined only if eMIOS channel 14 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_14_ISR)
{

    #if(defined GPT_EMIOS_1_CH_14_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_14);
    #endif

    #if(defined PWM_EMIOS_1_CH_14_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_14);
    #endif

    #if(defined ICU_EMIOS_1_CH_14_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_14);
    #endif
/**
@file  Reg_eSys_EMIOS_IRQ.c
    @note Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned int to pointer
    @ref Reg_eSys_EMIOS_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:15 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_15
*/
#if  ((defined GPT_EMIOS_1_CH_15_ISR_USED) && (defined PWM_EMIOS_1_CH_15_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_15"
#endif

#if  ((defined PWM_EMIOS_1_CH_15_ISR_USED) && (defined ICU_EMIOS_1_CH_15_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_15"
#endif

#if  ((defined ICU_EMIOS_1_CH_15_ISR_USED) && (defined GPT_EMIOS_1_CH_15_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_15"
#endif


#if ( (defined GPT_EMIOS_1_CH_15_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_15_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_15_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 15 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 15

@remarks   This will be defined only if eMIOS channel 15 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_15_ISR)
{

    #if(defined GPT_EMIOS_1_CH_15_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_15);
    #endif

    #if(defined PWM_EMIOS_1_CH_15_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_15);
    #endif

    #if(defined ICU_EMIOS_1_CH_15_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_15);
    #endif
    /**@file  Reg_eSys_EMIOS_IRQ.c
    @note Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned int to pointer
    @ref Reg_eSys_EMIOS_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:16 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_16
*/
#if  ((defined GPT_EMIOS_1_CH_16_ISR_USED) && (defined PWM_EMIOS_1_CH_16_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_16"
#endif

#if  ((defined PWM_EMIOS_1_CH_16_ISR_USED) && (defined ICU_EMIOS_1_CH_16_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_16"
#endif

#if  ((defined ICU_EMIOS_1_CH_16_ISR_USED) && (defined GPT_EMIOS_1_CH_16_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_16"
#endif


#if ( (defined GPT_EMIOS_1_CH_16_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_16_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_16_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 16 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 16

@remarks   This will be defined only if eMIOS channel 16 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_16_ISR)
{

    #if(defined GPT_EMIOS_1_CH_16_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_16);
    #endif

    #if(defined PWM_EMIOS_1_CH_16_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_16);
    #endif

    #if(defined ICU_EMIOS_1_CH_16_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_16);
    #endif
/**
@file  Reg_eSys_EMIOS_IRQ.c
        @note Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned int to pointer
    @ref Reg_eSys_EMIOS_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:17 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_17
*/
#if  ((defined GPT_EMIOS_1_CH_17_ISR_USED) && (defined PWM_EMIOS_1_CH_17_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_17"
#endif

#if  ((defined PWM_EMIOS_1_CH_17_ISR_USED) && (defined ICU_EMIOS_1_CH_17_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_17"
#endif

#if  ((defined ICU_EMIOS_1_CH_17_ISR_USED) && (defined GPT_EMIOS_1_CH_17_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_17"
#endif


#if ( (defined GPT_EMIOS_1_CH_17_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_17_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_17_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 17 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 17

@remarks   This will be defined only if eMIOS channel 17 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_17_ISR)
{

    #if(defined GPT_EMIOS_1_CH_17_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_17);
    #endif

    #if(defined PWM_EMIOS_1_CH_17_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_17);
    #endif

    #if(defined ICU_EMIOS_1_CH_17_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_17);
    #endif
/**
@file  Reg_eSys_EMIOS_IRQ.c
        @note Violates MISRA 2004 Advisory Rule  11.1 cast from unsigned int to pointer
    @ref Reg_eSys_EMIOS_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:18 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_18
*/
#if  ((defined GPT_EMIOS_1_CH_18_ISR_USED) && (defined PWM_EMIOS_1_CH_18_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_18"
#endif

#if  ((defined PWM_EMIOS_1_CH_18_ISR_USED) && (defined ICU_EMIOS_1_CH_18_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_18"
#endif

#if  ((defined ICU_EMIOS_1_CH_18_ISR_USED) && (defined GPT_EMIOS_1_CH_18_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_18"
#endif


#if ( (defined GPT_EMIOS_1_CH_18_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_18_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_18_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 18 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 18

@remarks   This will be defined only if eMIOS channel 18 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_18_ISR)
{

    #if(defined GPT_EMIOS_1_CH_18_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_18);
    #endif

    #if(defined PWM_EMIOS_1_CH_18_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_18);
    #endif

    #if(defined ICU_EMIOS_1_CH_18_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_18);
    #endif
/**
@file  Reg_eSys_EMIOS_IRQ.c
        @note Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned int to pointer
    @ref Reg_eSys_EMIOS_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:19 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_19
*/
#if  ((defined GPT_EMIOS_1_CH_19_ISR_USED) && (defined PWM_EMIOS_1_CH_19_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_19"
#endif

#if  ((defined PWM_EMIOS_1_CH_19_ISR_USED) && (defined ICU_EMIOS_1_CH_19_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_19"
#endif

#if  ((defined ICU_EMIOS_1_CH_19_ISR_USED) && (defined GPT_EMIOS_1_CH_19_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_19"
#endif


#if ( (defined GPT_EMIOS_1_CH_19_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_19_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_19_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 19 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 19

@remarks   This will be defined only if eMIOS channel 19 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_19_ISR)
{

    #if(defined GPT_EMIOS_1_CH_19_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_19);
    #endif

    #if(defined PWM_EMIOS_1_CH_19_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_19);
    #endif

    #if(defined ICU_EMIOS_1_CH_19_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_19);
    #endif
/**
@file  Reg_eSys_EMIOS_IRQ.c
        @note Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned int to pointer
    @ref Reg_eSys_EMIOS_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:20 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_20
*/
#if  ((defined GPT_EMIOS_1_CH_20_ISR_USED) && (defined PWM_EMIOS_1_CH_20_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_20"
#endif

#if  ((defined PWM_EMIOS_1_CH_20_ISR_USED) && (defined ICU_EMIOS_1_CH_20_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_20"
#endif

#if  ((defined ICU_EMIOS_1_CH_20_ISR_USED) && (defined GPT_EMIOS_1_CH_20_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_20"
#endif


#if ( (defined GPT_EMIOS_1_CH_20_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_20_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_20_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 20 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 20

@remarks   This will be defined only if eMIOS channel 20 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_20_ISR)
{

    #if(defined GPT_EMIOS_1_CH_20_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_20);
    #endif

    #if(defined PWM_EMIOS_1_CH_20_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_20);
    #endif

    #if(defined ICU_EMIOS_1_CH_20_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_20);
    #endif
/**
@file  Reg_eSys_EMIOS_IRQ.c
    @note Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned int to pointer
    @ref Reg_eSys_EMIOS_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:21 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_21
*/
#if  ((defined GPT_EMIOS_1_CH_21_ISR_USED) && (defined PWM_EMIOS_1_CH_21_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_21"
#endif

#if  ((defined PWM_EMIOS_1_CH_21_ISR_USED) && (defined ICU_EMIOS_1_CH_21_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_21"
#endif

#if  ((defined ICU_EMIOS_1_CH_21_ISR_USED) && (defined GPT_EMIOS_1_CH_21_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_21"
#endif


#if ( (defined GPT_EMIOS_1_CH_21_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_21_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_21_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 21 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 21

@remarks   This will be defined only if eMIOS channel 21 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_21_ISR)
{

    #if(defined GPT_EMIOS_1_CH_21_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_21);
    #endif

    #if(defined PWM_EMIOS_1_CH_21_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_21);
    #endif

    #if(defined ICU_EMIOS_1_CH_21_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_21);
    #endif
/**
@file  Reg_eSys_EMIOS_IRQ.c
        @note Violates MISRA 2004 Advisory Rule  11.1 cast from unsigned int to pointer
    @ref Reg_eSys_EMIOS_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:22 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_22
*/
#if  ((defined GPT_EMIOS_1_CH_22_ISR_USED) && (defined PWM_EMIOS_1_CH_22_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_22"
#endif

#if  ((defined PWM_EMIOS_1_CH_22_ISR_USED) && (defined ICU_EMIOS_1_CH_22_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_22"
#endif

#if  ((defined ICU_EMIOS_1_CH_22_ISR_USED) && (defined GPT_EMIOS_1_CH_22_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_22"
#endif


#if ( (defined GPT_EMIOS_1_CH_22_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_22_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_22_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 22 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 22

@remarks   This will be defined only if eMIOS channel 22 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_22_ISR)
{

    #if(defined GPT_EMIOS_1_CH_22_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_22);
    #endif

    #if(defined PWM_EMIOS_1_CH_22_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_22);
    #endif

    #if(defined ICU_EMIOS_1_CH_22_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_22);
    #endif
/**
@file  Reg_eSys_EMIOS_IRQ.c
        @note Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned int to pointer
    @ref Reg_eSys_EMIOS_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:23 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_23
*/
#if  ((defined GPT_EMIOS_1_CH_23_ISR_USED) && (defined PWM_EMIOS_1_CH_23_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_23"
#endif

#if  ((defined PWM_EMIOS_1_CH_23_ISR_USED) && (defined ICU_EMIOS_1_CH_23_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_23"
#endif

#if  ((defined ICU_EMIOS_1_CH_23_ISR_USED) && (defined GPT_EMIOS_1_CH_23_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_23"
#endif


#if ( (defined GPT_EMIOS_1_CH_23_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_23_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_23_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 23 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 23

@remarks   This will be defined only if eMIOS channel 23 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_23_ISR)
{

    #if(defined GPT_EMIOS_1_CH_23_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_23);
    #endif

    #if(defined PWM_EMIOS_1_CH_23_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_23);
    #endif

    #if(defined ICU_EMIOS_1_CH_23_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_23);
    #endif
/**
@file  Reg_eSys_EMIOS_IRQ.c
        @note Violates MISRA 2004 Advisory Rule  11.1 cast from unsigned int to pointer
    @ref Reg_eSys_EMIOS_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:24 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_24
*/
#if  ((defined GPT_EMIOS_1_CH_24_ISR_USED) && (defined PWM_EMIOS_1_CH_24_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_24"
#endif

#if  ((defined PWM_EMIOS_1_CH_24_ISR_USED) && (defined ICU_EMIOS_1_CH_24_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_24"
#endif

#if  ((defined ICU_EMIOS_1_CH_24_ISR_USED) && (defined GPT_EMIOS_1_CH_24_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_24"
#endif


#if ( (defined GPT_EMIOS_1_CH_24_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_24_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_24_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 24 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 24

@remarks   This will be defined only if eMIOS channel 24 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_24_ISR)
{

    #if(defined GPT_EMIOS_1_CH_24_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_24);
    #endif

    #if(defined PWM_EMIOS_1_CH_24_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_24);
    #endif

    #if(defined ICU_EMIOS_1_CH_24_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_24);
    #endif
/**
@file  Reg_eSys_EMIOS_IRQ.c
       @note Violates MISRA 2004 Advisory Rule  11.1 cast from unsigned int to pointer
       @ref Reg_eSys_EMIOS_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:25 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_25
*/
#if  ((defined GPT_EMIOS_1_CH_25_ISR_USED) && (defined PWM_EMIOS_1_CH_25_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_25"
#endif

#if  ((defined PWM_EMIOS_1_CH_25_ISR_USED) && (defined ICU_EMIOS_1_CH_25_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_25"
#endif

#if  ((defined ICU_EMIOS_1_CH_25_ISR_USED) && (defined GPT_EMIOS_1_CH_25_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_25"
#endif


#if ( (defined GPT_EMIOS_1_CH_25_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_25_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_25_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 25 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 25

@remarks   This will be defined only if eMIOS channel 25 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_25_ISR)
{

    #if(defined GPT_EMIOS_1_CH_25_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_25);
    #endif

    #if(defined PWM_EMIOS_1_CH_25_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_25);
    #endif

    #if(defined ICU_EMIOS_1_CH_25_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_25);
    #endif
/**
@file  Reg_eSys_EMIOS_IRQ.c
       @note Violates MISRA 2004 Advisory Rule  11.1 cast from unsigned int to pointer
       @ref Reg_eSys_EMIOS_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:26 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_26
*/
#if  ((defined GPT_EMIOS_1_CH_26_ISR_USED) && (defined PWM_EMIOS_1_CH_26_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_26"
#endif

#if  ((defined PWM_EMIOS_1_CH_26_ISR_USED) && (defined ICU_EMIOS_1_CH_26_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_26"
#endif

#if  ((defined ICU_EMIOS_1_CH_26_ISR_USED) && (defined GPT_EMIOS_1_CH_26_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_26"
#endif


#if ( (defined GPT_EMIOS_1_CH_26_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_26_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_26_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 26 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 26

@remarks   This will be defined only if eMIOS channel 26 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_26_ISR)
{

    #if(defined GPT_EMIOS_1_CH_26_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_26);
    #endif

    #if(defined PWM_EMIOS_1_CH_26_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_26);
    #endif

    #if(defined ICU_EMIOS_1_CH_26_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_26);
    #endif
/**
@file  Reg_eSys_EMIOS_IRQ.c
        @note Violates MISRA 2004 Advisory Rule  11.1 cast from unsigned int to pointer
    @ref Reg_eSys_EMIOS_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:27 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_27
*/
#if  ((defined GPT_EMIOS_1_CH_27_ISR_USED) && (defined PWM_EMIOS_1_CH_27_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_27"
#endif

#if  ((defined PWM_EMIOS_1_CH_27_ISR_USED) && (defined ICU_EMIOS_1_CH_27_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_27"
#endif

#if  ((defined ICU_EMIOS_1_CH_27_ISR_USED) && (defined GPT_EMIOS_1_CH_27_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_27"
#endif


#if ( (defined GPT_EMIOS_1_CH_27_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_27_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_27_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 27 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 27

@remarks   This will be defined only if eMIOS channel 27 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_27_ISR)
{

    #if(defined GPT_EMIOS_1_CH_27_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_27);
    #endif

    #if(defined PWM_EMIOS_1_CH_27_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_27);
    #endif

    #if(defined ICU_EMIOS_1_CH_27_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_27);
    #endif
/**
@file  Reg_eSys_EMIOS_IRQ.c
        @note Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned int to pointer
    @ref Reg_eSys_EMIOS_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:28 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_28
*/
#if  ((defined GPT_EMIOS_1_CH_28_ISR_USED) && (defined PWM_EMIOS_1_CH_28_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_28"
#endif

#if  ((defined PWM_EMIOS_1_CH_28_ISR_USED) && (defined ICU_EMIOS_1_CH_28_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_28"
#endif

#if  ((defined ICU_EMIOS_1_CH_28_ISR_USED) && (defined GPT_EMIOS_1_CH_28_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_28"
#endif


#if ( (defined GPT_EMIOS_1_CH_28_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_28_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_28_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 28 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 28

@remarks   This will be defined only if eMIOS channel 28 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_28_ISR)
{

    #if(defined GPT_EMIOS_1_CH_28_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_28);
    #endif

    #if(defined PWM_EMIOS_1_CH_28_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_28);
    #endif

    #if(defined ICU_EMIOS_1_CH_28_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_28);
    #endif
/**
@file  Reg_eSys_EMIOS_IRQ.c
        @note Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned int to pointer
    @ref Reg_eSys_EMIOS_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:29 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_29
*/
#if  ((defined GPT_EMIOS_1_CH_29_ISR_USED) && (defined PWM_EMIOS_1_CH_29_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_29"
#endif

#if  ((defined PWM_EMIOS_1_CH_29_ISR_USED) && (defined ICU_EMIOS_1_CH_29_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_29"
#endif

#if  ((defined ICU_EMIOS_1_CH_29_ISR_USED) && (defined GPT_EMIOS_1_CH_29_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_29"
#endif


#if ( (defined GPT_EMIOS_1_CH_29_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_29_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_29_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 29 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 29

@remarks   This will be defined only if eMIOS channel 29 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_29_ISR)
{

    #if(defined GPT_EMIOS_1_CH_29_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_29);
    #endif

    #if(defined PWM_EMIOS_1_CH_29_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_29);
    #endif

    #if(defined ICU_EMIOS_1_CH_29_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_29);
    #endif
/**
@file  Reg_eSys_EMIOS_IRQ.c
        @note Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned int to pointer
    @ref Reg_eSys_EMIOS_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:30 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_30
*/
#if  ((defined GPT_EMIOS_1_CH_30_ISR_USED) && (defined PWM_EMIOS_1_CH_30_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_30"
#endif

#if  ((defined PWM_EMIOS_1_CH_30_ISR_USED) && (defined ICU_EMIOS_1_CH_30_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_30"
#endif

#if  ((defined ICU_EMIOS_1_CH_30_ISR_USED) && (defined GPT_EMIOS_1_CH_30_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_30"
#endif


#if ( (defined GPT_EMIOS_1_CH_30_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_30_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_30_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 30 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 30

@remarks   This will be defined only if eMIOS channel 30 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_30_ISR)
{

    #if(defined GPT_EMIOS_1_CH_30_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_30);
    #endif

    #if(defined PWM_EMIOS_1_CH_30_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_30);
    #endif

    #if(defined ICU_EMIOS_1_CH_30_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_30);
    #endif
/**
@file  Reg_eSys_EMIOS_IRQ.c
        @note Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned int to pointer
        @ref Reg_eSys_EMIOS_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif


/**
@brief EMIOS module:1 channel:31 independent interrupt handler
*/

/**
@brief resource conflict check for EMIOS_1_CH_31
*/
#if  ((defined GPT_EMIOS_1_CH_31_ISR_USED) && (defined PWM_EMIOS_1_CH_31_ISR_USED))
#error "GPT and PWM resource conflict for EMIOS unified channel EMIOS_1_31"
#endif

#if  ((defined PWM_EMIOS_1_CH_31_ISR_USED) && (defined ICU_EMIOS_1_CH_31_ISR_USED))
#error "PWM and ICU resource conflict for EMIOS unified channel EMIOS_1_31"
#endif

#if  ((defined ICU_EMIOS_1_CH_31_ISR_USED) && (defined GPT_EMIOS_1_CH_31_ISR_USED))
#error "ICU and GPT resource conflict for EMIOS unified channel EMIOS_1_31"
#endif


#if ( (defined GPT_EMIOS_1_CH_31_ISR_USED) || \
      (defined PWM_EMIOS_1_CH_31_ISR_USED) || \
      (defined ICU_EMIOS_1_CH_31_ISR_USED) )
/*================================================================================================*/
/**
@brief     Interrupt handler for eMIOS channel : 31 for eMIOS_1 module
@details   Process the interrupt of eMIOS channel 31

@remarks   This will be defined only if eMIOS channel 31 is configured in GPT, ICU or PWM mode
*/
/*================================================================================================*/
ISR(EMIOS_1_CH_31_ISR)
{

    #if(defined GPT_EMIOS_1_CH_31_ISR_USED)
         EMIOS_Gpt_LLD_ProcessInterrupt(EMIOS_1_CH_31);
    #endif

    #if(defined PWM_EMIOS_1_CH_31_ISR_USED)
         EMIOS_Pwm_LLD_ProcessInterrupt(EMIOS_1_CH_31);
    #endif

    #if(defined ICU_EMIOS_1_CH_31_ISR_USED)
         EMIOS_Icu_LLD_ProcessInterrupt(EMIOS_1_CH_31);
    #endif
/**
@file  Reg_eSys_EMIOS_IRQ.c
    @note  MISRA 2004 Rule 11.1 cast from unsigned int to pointer @ref Reg_eSys_EMIOS_IRQ_c_3 */
    EXIT_INTERRUPT();
}
#endif



/*********************************** EMIOS 1 independent interrupts END ***************************/


/* EMIOS_COMMON_ISR_HANDLER == STD_ON */
#endif  

#else

#error "Unknown EMIOS interrupt handler type, EMIOS_COMMON_ISR_HANDLER is undefined";
/* #ifdef EMIOS_COMMON_ISR_HANDLER */
#endif 

/* module check */
#endif 


/*lint -save -e961 -e537 -e451 */
#if ((USE_GPT_MODULE==STD_ON) && (EMIOS_COMMON_MODULE_ID==100))
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
#define GPT_STOP_SEC_CODE
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, 19.15 : See @ref Reg_eSys_EMIOS_IRQ_c_1,
      Reg_eSys_EMIOS_IRQ_c_2 */
#include "MemMap.h"
#endif

#if ((USE_GPT_MODULE==STD_OFF) && (USE_PWM_MODULE==STD_ON) && (EMIOS_COMMON_MODULE_ID==121))
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
#define PWM_STOP_SEC_CODE
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, 19.15 : See @ref Reg_eSys_EMIOS_IRQ_c_1,
      Reg_eSys_EMIOS_IRQ_c_2 */
#include "MemMap.h"
#endif

#if ((USE_GPT_MODULE==STD_OFF) && (USE_PWM_MODULE==STD_OFF) && (USE_ICU_MODULE==STD_ON) && \
     (EMIOS_COMMON_MODULE_ID==122))
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" See @ref Reg_eSys_EMIOS_IRQ_c_1 */
#define ICU_STOP_SEC_CODE
/**
@file  Reg_eSys_EMIOS_IRQ.c
@note Violates MISRA 2004 Advisory Rule 19.1, 19.15 : See @ref Reg_eSys_EMIOS_IRQ_c_1,
      Reg_eSys_EMIOS_IRQ_c_2 */
#include "MemMap.h"
#endif
/*lint -restore */


#ifdef __cplusplus
}
#endif
