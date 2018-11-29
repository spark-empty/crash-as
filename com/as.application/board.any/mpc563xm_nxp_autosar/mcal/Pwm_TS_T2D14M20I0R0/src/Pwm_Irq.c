/**
@file    Pwm_Irq.c
@version 2.0.0

@brief   AUTOSAR Pwm - Pwm LLD Irq handling routine.
@details  Pwm LLD Irq handling routine.

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

@section Pwm_IRQ_C_REF_1
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

#include "Dem.h"


/*===============================================================================================
                                        LOCAL MACROS
===============================================================================================*/
/**
@{
@brief Parameters that shall be published within the Pwm driver header file and also in the
       module's description file
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define PWM_VENDOR_ID_IRQ_C         43
#define PWM_AR_MAJOR_VERSION_IRQ_C  3
#define PWM_AR_MINOR_VERSION_IRQ_C  0
#define PWM_AR_PATCH_VERSION_IRQ_C  0
#define PWM_SW_MAJOR_VERSION_IRQ_C  2
#define PWM_SW_MINOR_VERSION_IRQ_C  0
#define PWM_SW_PATCH_VERSION_IRQ_C  0
/**@}*/

/*===============================================================================================
                                      FILE VERSION CHECKS
===============================================================================================*/

#if (PWM_VENDOR_ID_IRQ_C != PWM_VENDOR_ID)
    #error "Pwm_Irq.c and Pwm.h have different vendor ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    #if ((PWM_AR_MAJOR_VERSION_IRQ_C != PWM_AR_MAJOR_VERSION) || \
         (PWM_AR_MINOR_VERSION_IRQ_C != PWM_AR_MINOR_VERSION) || \
         (PWM_AR_PATCH_VERSION_IRQ_C != PWM_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of Pwm_Irq.c and Pwm.h are different"
    #endif
#endif

#if ((PWM_SW_MAJOR_VERSION_IRQ_C != PWM_SW_MAJOR_VERSION) || \
    (PWM_SW_MINOR_VERSION_IRQ_C != PWM_SW_MINOR_VERSION)  || \
    (PWM_SW_PATCH_VERSION_IRQ_C != PWM_SW_PATCH_VERSION))
#error "Software Version Numbers of Pwm_Irq.c and Pwm.h are different"
#endif


#if (PWM_VENDOR_ID_IRQ_C != PWM_VENDOR_ID_LLD_H)
    #error "Pwm_Irq.c and Pwm_LLD.h have different vendor ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    #if ((PWM_AR_MAJOR_VERSION_IRQ_C != PWM_AR_MAJOR_VERSION_LLD_H) || \
         (PWM_AR_MINOR_VERSION_IRQ_C != PWM_AR_MINOR_VERSION_LLD_H) || \
         (PWM_AR_PATCH_VERSION_IRQ_C != PWM_AR_PATCH_VERSION_LLD_H))
        #error "AutoSar Version Numbers of Pwm_Irq.c and Pwm_LLD.h are different"
    #endif
#endif

#if ((PWM_SW_MAJOR_VERSION_IRQ_C != PWM_SW_MAJOR_VERSION_LLD_H) || \
    (PWM_SW_MINOR_VERSION_IRQ_C != PWM_SW_MINOR_VERSION_LLD_H)  || \
    (PWM_SW_PATCH_VERSION_IRQ_C != PWM_SW_PATCH_VERSION_LLD_H))
#error "Software Version Numbers of Pwm_Irq.c and Pwm_LLD.h are different"
#endif


#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and DEM header file are of the same version */
    #if ((PWM_AR_MAJOR_VERSION_IRQ_C != DEM_AR_MAJOR_VERSION) || \
         (PWM_AR_MINOR_VERSION_IRQ_C != DEM_AR_MINOR_VERSION))
        #error "AutoSar Version Numbers of Pwm_Irq.c and Dem.h are different"
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
/*lint -save -e961 -e537 -e451 */
/** @file Pwm_Irq.c
    @note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
                                                  before "#include": See @ref Pwm_IRQ_C_REF_1 */
#define PWM_START_SEC_CODE
#include "MemMap.h"
/*lint -restore */



/*lint -save -e961 -e537 -e451 */
/** @file Pwm_Irq.c
    @note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
                                                  before "#include": See @ref Pwm_IRQ_C_REF_1 */
#define PWM_STOP_SEC_CODE
#include "MemMap.h"
/*lint -restore */

/*===============================================================================================
                                       LOCAL FUNCTIONS
===============================================================================================*/

/*===============================================================================================
                                       GLOBAL FUNCTIONS
===============================================================================================*/
/*lint -save -e961 -e537 -e451 */
/** @file Pwm_Irq.c
    @note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
                                                  before "#include": See @ref Pwm_IRQ_C_REF_1 */
#define PWM_START_SEC_CODE
#include "MemMap.h"
/*lint -restore */

/**
@brief   Pwm_LLD_ProcessInterrupt
@details handle PWM interrupt and call user notification, called from device specific ISR

@param[in]     ch_id      logical channel that triggered the interrupt

@remarks Covers PWM005, PWM025, PWM115


*/

/** @remarks Covers PWM115 */
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
FUNC (void, PWM_CODE) Pwm_LLD_ProcessInterrupt( VAR(Pwm_ChannelType, AUTOMATIC) ch_id )
{
    if (NULL_PTR != Pwm_Cfg_Ptr)
    {
        /* Note: For PWM, interrupts are not enabled if the notification function is
         * a NULL_PTR. Therefore the code does not check for NULL_PTR before calling
         * the notification function
         */

        /** @remarks Covers PWM025 */
        Pwm_Cfg_Ptr->ChannelsPtr[ ch_id ].Pwm_Channel_Notification();

    } else { /* Pwm_Cfg_Ptr == NULL_PTR */

        /* if IRQs are received even if the driver is not initialized then
           report the error to DEM */
        /** @remarks Covers PWM005 */
        Dem_ReportErrorStatus((uint16) PWM_E_UNEXPECTED_IRQ, DEM_EVENT_STATUS_FAILED);
    }

}
#endif

/*lint -save -e961 -e537 -e451 */
/** @file Pwm_Irq.c
    @note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
                                                  before "#include": See @ref Pwm_IRQ_C_REF_1 */
#define PWM_STOP_SEC_CODE
#include "MemMap.h"
/*lint -restore */



#ifdef __cplusplus
}
#endif
