/**
    @file    SchM_Adc.h
    @version 2.0.0

    @brief   AUTOSAR SchM - module interface.
    @details This file contains the functions prototypes and data types of the AUTOSAR SchM.
    
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

#ifndef SCHM_ADC_H
#define SCHM_ADC_H

#ifdef __cplusplus
extern "C" {
#endif
/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#ifdef SCHM_USE_MACROS
#include "Mcal.h"
#endif
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SCHM_ADC_MODULE_ID           130
#define SCHM_ADC_VENDOR_ID           43
#define SCHM_ADC_AR_MAJOR_VERSION    3
#define SCHM_ADC_AR_MINOR_VERSION    0
#define SCHM_ADC_AR_PATCH_VERSION    0

#define SCHM_ADC_SW_MAJOR_VERSION    2
#define SCHM_ADC_SW_MINOR_VERSION    0
#define SCHM_ADC_SW_PATCH_VERSION    0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/
#define SCHM_ADC_INSTANCE_0        (uint8)0U   /**< @brief unique instance ID*/

#define ADC_EXCLUSIVE_AREA_00      (uint8)0U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_01      (uint8)1U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_02      (uint8)2U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_03      (uint8)3U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_04      (uint8)4U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_05      (uint8)5U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_06      (uint8)6U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_07      (uint8)7U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_08      (uint8)8U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_09      (uint8)9U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_10      (uint8)10U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_11      (uint8)11U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_12      (uint8)12U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_13      (uint8)13U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_14      (uint8)14U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_15      (uint8)15U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_16      (uint8)16U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_17      (uint8)17U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_18      (uint8)18U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_19      (uint8)19U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_20      (uint8)20U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_21      (uint8)21U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_22      (uint8)22U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_23      (uint8)23U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_24      (uint8)24U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_25      (uint8)25U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_26      (uint8)26U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_27      (uint8)27U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_28      (uint8)28U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_29      (uint8)29U   /**< @brief unique exclusive area ID*/
#define ADC_EXCLUSIVE_AREA_30      (uint8)30U   /**< @brief unique exclusive area ID*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
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
#ifdef SCHM_USE_MACROS
 #define SchM_Enter_Adc(InstanceId, ExclusiveArea) SuspendAllInterrupts()
#else 
 #define SchM_Enter_Adc(InstanceId, ExclusiveArea) SchM_Enter_##ExclusiveArea() 
#endif

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
#ifdef SCHM_USE_MACROS
 #define SchM_Exit_Adc(InstanceId, ExclusiveArea) ResumeAllInterrupts()
#else 
 #define SchM_Exit_Adc(InstanceId, ExclusiveArea) SchM_Exit_##ExclusiveArea()
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

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
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
FUNC(void, SCHM_CODE) SchM_Check_adc(void);
#endif /*MCAL_TESTING_ENVIRONMENT*/

#ifndef SCHM_USE_MACROS
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_00(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_01(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_02(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_03(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_04(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_05(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_06(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_07(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_08(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_09(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_10(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_11(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_12(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_13(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_14(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_15(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_16(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_17(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_18(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_19(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_20(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_21(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_22(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_23(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_24(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_25(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_26(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_27(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_28(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_29(void);
extern FUNC(void, SCHM_CODE) SchM_Enter_ADC_EXCLUSIVE_AREA_30(void);

extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_00(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_01(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_02(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_03(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_04(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_05(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_06(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_07(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_08(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_09(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_10(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_11(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_12(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_13(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_14(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_15(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_16(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_17(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_18(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_19(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_20(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_21(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_22(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_23(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_24(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_25(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_26(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_27(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_28(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_29(void);
extern FUNC(void, SCHM_CODE) SchM_Exit_ADC_EXCLUSIVE_AREA_30(void);

#endif /*SCHM_USE_MACROS*/

#ifdef __cplusplus
}
#endif

#endif /* SCHM_ADC_H */
