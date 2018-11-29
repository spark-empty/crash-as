/**
@file    Pwm_LLD.c
@version 2.0.0

@brief   AUTOSAR Pwm - PWM LLD API implementation.
@details PWM LLD API implementation.

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
/*===============================================================================================
===============================================================================================*/


/**
@page misra_violations MISRA-C:2004 violations

@section Pwm_LLD_C_REF_1
Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
                                        before "#include"
MemMap.h included after each section define in order to set the current memory section
*/




#ifdef __cplusplus
extern "C"{
#endif

/*===============================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
===============================================================================================*/

#include "Pwm.h"
#include "Pwm_LLD.h"


#if (PWM_DEV_ERROR_DETECT == STD_ON)
    #include "Det.h"
#endif




/*===============================================================================================
                                        LOCAL MACROS
===============================================================================================*/

/**
@{
@brief Parameters that shall be published within the Pwm driver header file and also in the
       module's description file
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define PWM_VENDOR_ID_LLD_C         43
#define PWM_AR_MAJOR_VERSION_LLD_C  3
#define PWM_AR_MINOR_VERSION_LLD_C  0
#define PWM_AR_PATCH_VERSION_LLD_C  0
#define PWM_SW_MAJOR_VERSION_LLD_C  2
#define PWM_SW_MINOR_VERSION_LLD_C  0
#define PWM_SW_PATCH_VERSION_LLD_C  0
/**@}*/

/*===============================================================================================
                                      FILE VERSION CHECKS
===============================================================================================*/

#if (PWM_VENDOR_ID_LLD_C != PWM_VENDOR_ID)
    #error "Pwm_LLD.c and Pwm.h have different vendor ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    #if ((PWM_AR_MAJOR_VERSION_LLD_C != PWM_AR_MAJOR_VERSION) || \
         (PWM_AR_MINOR_VERSION_LLD_C != PWM_AR_MINOR_VERSION) || \
         (PWM_AR_PATCH_VERSION_LLD_C != PWM_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Pwm_LLD.c and Pwm.h are different"
    #endif
#endif

#if ((PWM_SW_MAJOR_VERSION_LLD_C != PWM_SW_MAJOR_VERSION) || \
    (PWM_SW_MINOR_VERSION_LLD_C != PWM_SW_MINOR_VERSION)  || \
    (PWM_SW_PATCH_VERSION_LLD_C != PWM_SW_PATCH_VERSION))
#error "Software Version Numbers of Pwm_LLD.c and Pwm.h are different"
#endif



#if (PWM_VENDOR_ID_LLD_C != PWM_VENDOR_ID_LLD_H)
    #error "Pwm_LLD.c and Pwm_LLD.h have different vendor ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    #if ((PWM_AR_MAJOR_VERSION_LLD_C != PWM_AR_MAJOR_VERSION_LLD_H) || \
         (PWM_AR_MINOR_VERSION_LLD_C != PWM_AR_MINOR_VERSION_LLD_H) || \
         (PWM_AR_PATCH_VERSION_LLD_C != PWM_AR_PATCH_VERSION_LLD_H))
    #error "AutoSar Version Numbers of Pwm_LLD.c and Pwm_LLD.h are different"
    #endif
#endif

#if ((PWM_SW_MAJOR_VERSION_LLD_C != PWM_SW_MAJOR_VERSION_LLD_H) || \
    (PWM_SW_MINOR_VERSION_LLD_C != PWM_SW_MINOR_VERSION_LLD_H)  || \
    (PWM_SW_PATCH_VERSION_LLD_C != PWM_SW_PATCH_VERSION_LLD_H))
#error "Software Version Numbers of Pwm_LLD.c and Pwm_LLD.h are different"
#endif


/* Check if source file and DET header file are of the same version */
#if (PWM_DEV_ERROR_DETECT == STD_ON)
    #ifdef CHECK_AUTOSAR_VERSION
        #if ((PWM_AR_MAJOR_VERSION_LLD_C != DET_AR_MAJOR_VERSION) || \
             (PWM_AR_MINOR_VERSION_LLD_C != DET_AR_MINOR_VERSION))
            #error "AutoSar Version Numbers of Pwm_LLD.c and Det.h are different"
        #endif
    #endif
#endif

/*===============================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
===============================================================================================*/


/*===============================================================================================
                                       LOCAL CONSTANTS
===============================================================================================*/


/*===============================================================================================
                                       LOCAL VARIABLES
===============================================================================================*/


/*===============================================================================================
                                       GLOBAL CONSTANTS
===============================================================================================*/


/*===============================================================================================
                                       GLOBAL VARIABLES
===============================================================================================*/

/*===============================================================================================
                                   LOCAL FUNCTION PROTOTYPES
===============================================================================================*/


/*===============================================================================================
                                       LOCAL FUNCTIONS
===============================================================================================*/

/*===============================================================================================
                                       GLOBAL FUNCTIONS
===============================================================================================*/

/*lint -save -e961 -e537 -e451 */
/** @file Pwm_LLD.c
    @note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
                                                  before "#include": See @ref Pwm_LLD_C_REF_1 */
#define PWM_START_SEC_CODE
#include "MemMap.h"
/*lint -restore */



/*lint -save -e961 -e537 -e451 */
/** @file Pwm_LLD.c
    @note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
                                                  before "#include": See @ref Pwm_LLD_C_REF_1 */
#define PWM_STOP_SEC_CODE
#include "MemMap.h"
/*lint -restore */




#ifdef __cplusplus
}
#endif
