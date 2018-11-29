/**
    @file    SchM_Gpt.h
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

#ifndef SCHM_GPT_H
#define SCHM_GPT_H

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
#define SCHM_GPT_MODULE_ID           130
#define SCHM_GPT_VENDOR_ID           43
#define SCHM_GPT_AR_MAJOR_VERSION    3
#define SCHM_GPT_AR_MINOR_VERSION    0
#define SCHM_GPT_AR_PATCH_VERSION    0

#define SCHM_GPT_SW_MAJOR_VERSION    2
#define SCHM_GPT_SW_MINOR_VERSION    0
#define SCHM_GPT_SW_PATCH_VERSION    0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/
#define SCHM_GPT_INSTANCE_0         (uint8)0U   /**< @brief unique instance ID */

#define GPT_EXCLUSIVE_AREA_00      (uint8)0U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_01      (uint8)1U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_02      (uint8)2U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_03      (uint8)3U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_04      (uint8)4U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_05      (uint8)5U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_06      (uint8)6U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_07      (uint8)7U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_08      (uint8)8U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_09      (uint8)9U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_10      (uint8)10U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_11      (uint8)11U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_12      (uint8)12U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_13      (uint8)13U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_14      (uint8)14U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_15      (uint8)15U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_16      (uint8)16U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_17      (uint8)17U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_18      (uint8)18U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_19      (uint8)19U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_20      (uint8)20U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_21      (uint8)21U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_22      (uint8)22U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_23      (uint8)23U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_24      (uint8)24U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_25      (uint8)25U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_26      (uint8)26U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_27      (uint8)27U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_28      (uint8)28U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_29      (uint8)29U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_30      (uint8)30U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_31      (uint8)31U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_32      (uint8)32U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_33      (uint8)33U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_34      (uint8)34U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_35      (uint8)35U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_36      (uint8)36U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_37      (uint8)37U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_38      (uint8)38U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_39      (uint8)39U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_40      (uint8)40U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_41      (uint8)41U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_42      (uint8)42U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_43      (uint8)43U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_44      (uint8)44U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_45      (uint8)45U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_46      (uint8)46U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_47      (uint8)47U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_48      (uint8)48U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_49      (uint8)49U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_50      (uint8)50U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_51      (uint8)51U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_52      (uint8)52U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_53      (uint8)53U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_54      (uint8)54U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_55      (uint8)55U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_56      (uint8)56U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_57      (uint8)57U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_58      (uint8)58U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_59      (uint8)59U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_60      (uint8)60U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_61      (uint8)61U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_62      (uint8)62U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_63      (uint8)63U   /**< @brief unique exclusive area ID*/
#define GPT_EXCLUSIVE_AREA_64      (uint8)64U   /**< @brief unique exclusive area ID*/


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
 #define SchM_Enter_Gpt(InstanceId, ExclusiveArea) SuspendAllInterrupts()
#else 
 extern FUNC (void, SCHM_CODE) SchM_Enter_Gpt(VAR(uint8, AUTOMATIC) InstanceId, VAR(uint8, AUTOMATIC) ExclusiveArea);
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
 #define SchM_Exit_Gpt(InstanceId, ExclusiveArea) ResumeAllInterrupts()
#else 
  extern FUNC (void, SCHM_CODE) SchM_Exit_Gpt(VAR(uint8, AUTOMATIC) InstanceId, VAR(uint8, AUTOMATIC) ExclusiveArea);
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
FUNC(void, SCHM_CODE) SchM_Check_gpt(void);
#endif /*MCAL_TESTING_ENVIRONMENT*/

#ifdef __cplusplus
}
#endif

#endif /* SCHM_GPT_H */
