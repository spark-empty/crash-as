/**
@file    eMIOS_Pwm_LLD_IRQ.c
@version 2.0.0

@brief   AUTOSAR Pwm - Pwm Emios LLD interrupt handling routines.
@details Pwm Emios LLD interrupt handling routines.

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

@section eMIOS_Pwm_LLD_IRQ_C_REF_1
Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
                                        before "#include"
MemMap.h included after each section define in order to set the current memory section

@section eMIOS_Pwm_LLD_IRQ_C_REF_2
Violates MISRA 2004 Advisory Rule 19.15, :  Repeated include files,  Precautions shall be taken in
order to prevent the contents of a header file being included twice This is not a violation since
all header files are protected against multiple inclusions

@section eMIOS_Pwm_LLD_IRQ_C_REF_3
Violates MISRA 2004 Advisory Rule MISRA 2004 Rules 1.2, 1.4 and 5.1 : Identifier clash
All compiler used to validate the code can make the difference between two symbols

@section eMIOS_Pwm_LLD_IRQ_C_REF_4
Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer
To access Memory
@section eMIOS_Pwm_LLD_IRQ_C_REF_5
Violates MISRA 2004 Advisory Rule 8.8, function previously declared
*/


#ifdef __cplusplus
extern "C" {
#endif

/*===============================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
===============================================================================================*/
#include "Mcal.h"

#include "Pwm.h"
#include "Pwm_LLD.h"
#include "eMIOS_Pwm_LLD.h"
/*lint -save -e537 */
/** @file eMIOS_Pwm_LLD_IRQ.c
    @note Violates MISRA 2004 Advisory Rule 19.1,19.15 : See @ref eMIOS_Pwm_LLD_IRQ_C_REF_2 */
#include "eMIOS_Pwm_LLD_CfgEx.h"
/*lint -restore */

#include "Reg_eSys_EMIOS.h"

#include "Dem.h"

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
#define PWM_VENDOR_ID_EMIOS_LLD_IRQ_C         43
/*lint -e621 */
/** @file eMIOS_Pwm_LLD_IRQ.c
    @note Violates MISRA 2004 Advisory Rule 1.2, 1.4 and 5.1 : See @ref eMIOS_Pwm_LLD_IRQ_C_REF_3 */
#define PWM_AR_MAJOR_VERSION_EMIOS_LLD_IRQ_C  3
#define PWM_AR_MINOR_VERSION_EMIOS_LLD_IRQ_C  0
#define PWM_AR_PATCH_VERSION_EMIOS_LLD_IRQ_C  0
#define PWM_SW_MAJOR_VERSION_EMIOS_LLD_IRQ_C  2
#define PWM_SW_MINOR_VERSION_EMIOS_LLD_IRQ_C  0
#define PWM_SW_PATCH_VERSION_EMIOS_LLD_IRQ_C  0
/*lint -restore */
/**@}*/

/*===============================================================================================
                                      FILE VERSION CHECKS
===============================================================================================*/

/* Check if source file and PWM header file are of the same vendor */
#if (PWM_VENDOR_ID_EMIOS_LLD_IRQ_C != PWM_VENDOR_ID)
    #error "eMIOS_Pwm_LLD_IRQ.c and Pwm.h have different vendor ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and PWM header file are of the same Autosar version */
    #if ((PWM_AR_MAJOR_VERSION_EMIOS_LLD_IRQ_C != PWM_AR_MAJOR_VERSION) || \
         (PWM_AR_MINOR_VERSION_EMIOS_LLD_IRQ_C != PWM_AR_MINOR_VERSION) || \
         (PWM_AR_PATCH_VERSION_EMIOS_LLD_IRQ_C != PWM_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of eMIOS_Pwm_LLD_IRQ.c and Pwm.h are different"
    #endif
#endif

/* Check if source file and PWM header file are of the same software version */
#if ((PWM_SW_MAJOR_VERSION_EMIOS_LLD_IRQ_C != PWM_SW_MAJOR_VERSION) || \
     (PWM_SW_MINOR_VERSION_EMIOS_LLD_IRQ_C != PWM_SW_MINOR_VERSION) || \
     (PWM_SW_PATCH_VERSION_EMIOS_LLD_IRQ_C != PWM_SW_PATCH_VERSION))
#error "Software Version Numbers of eMIOS_Pwm_LLD_IRQ.c and Pwm.h are different"
#endif



/* Check if source file and eMIOS_Pwm_LLD_IRQ.h are of the same vendor */
#if (PWM_VENDOR_ID_EMIOS_LLD_IRQ_C != PWM_VENDOR_ID_EMIOS_LLD_H)
    #error "eMIOS_Pwm_LLD_IRQ.c and eMIOS_Pwm_LLD.h have different vendor ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and eMIOS_Pwm_LLD_IRQ.h are of the same Autosar version */
    #if ((PWM_AR_MAJOR_VERSION_EMIOS_LLD_IRQ_C != PWM_AR_MAJOR_VERSION_EMIOS_LLD_H) || \
         (PWM_AR_MINOR_VERSION_EMIOS_LLD_IRQ_C != PWM_AR_MINOR_VERSION_EMIOS_LLD_H) || \
         (PWM_AR_PATCH_VERSION_EMIOS_LLD_IRQ_C != PWM_AR_PATCH_VERSION_EMIOS_LLD_H))
    #error "AutoSar Version Numbers of eMIOS_Pwm_LLD_IRQ.c and eMIOS_Pwm_LLD.h are different"
    #endif
#endif

/* Check if source file and eMIOS_Pwm_LLD_IRQ.h are of the same software version */
#if ((PWM_SW_MAJOR_VERSION_EMIOS_LLD_IRQ_C != PWM_SW_MAJOR_VERSION_EMIOS_LLD_H) || \
     (PWM_SW_MINOR_VERSION_EMIOS_LLD_IRQ_C != PWM_SW_MINOR_VERSION_EMIOS_LLD_H) || \
     (PWM_SW_PATCH_VERSION_EMIOS_LLD_IRQ_C != PWM_SW_PATCH_VERSION_EMIOS_LLD_H))
#error "Software Version Numbers of eMIOS_Pwm_LLD_IRQ.c and eMIOS_Pwm_LLD.h are different"
#endif



/* Check if source file and eMIOS_Pwm_LLD_CfgEx.h are of the same vendor */
#if (PWM_VENDOR_ID_EMIOS_LLD_IRQ_C != PWM_VENDOR_ID_EMIOS_LLD_CFGEX_H)
    #error "eMIOS_Pwm_LLD_IRQ.c and eMIOS_Pwm_LLD_CfgEx.h have different vendor ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and eMIOS_Pwm_LLD_CfgEx.h are of the same Autosar version */
    #if ((PWM_AR_MAJOR_VERSION_EMIOS_LLD_IRQ_C != PWM_AR_MAJOR_VERSION_EMIOS_LLD_CFGEX_H) || \
         (PWM_AR_MINOR_VERSION_EMIOS_LLD_IRQ_C != PWM_AR_MINOR_VERSION_EMIOS_LLD_CFGEX_H) || \
         (PWM_AR_PATCH_VERSION_EMIOS_LLD_IRQ_C != PWM_AR_PATCH_VERSION_EMIOS_LLD_CFGEX_H))
    #error "AutoSar Version Numbers of eMIOS_Pwm_LLD_IRQ.c and eMIOS_Pwm_LLD_CfgEx.h differe"
    #endif
#endif

/* Check if source file and eMIOS_Pwm_LLD_CfgEx.h are of the same software version */
#if ((PWM_SW_MAJOR_VERSION_EMIOS_LLD_IRQ_C != PWM_SW_MAJOR_VERSION_EMIOS_LLD_CFGEX_H) || \
     (PWM_SW_MINOR_VERSION_EMIOS_LLD_IRQ_C != PWM_SW_MINOR_VERSION_EMIOS_LLD_CFGEX_H)  || \
     (PWM_SW_PATCH_VERSION_EMIOS_LLD_IRQ_C != PWM_SW_PATCH_VERSION_EMIOS_LLD_CFGEX_H))
#error "Software Version Numbers of eMIOS_Pwm_LLD_IRQ.c and eMIOS_Pwm_LLD_CfgEx.h are different"
#endif



/* Check if source file and Reg_ESYS_EMIOS.h are of the same vendor */
#if (PWM_VENDOR_ID_EMIOS_LLD_IRQ_C != REG_ESYS_EMIOS_H_VENDOR_ID)
    #error "eMIOS_Pwm_LLD_IRQ.c and Reg_ESYS_EMIOS.h have different vendor ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Reg_ESYS_EMIOS_PWM.h are of the same Autosar version */
    #if ((PWM_AR_MAJOR_VERSION_EMIOS_LLD_IRQ_C != REG_ESYS_EMIOS_H_AR_MAJOR_VERSION) || \
         (PWM_AR_MINOR_VERSION_EMIOS_LLD_IRQ_C != REG_ESYS_EMIOS_H_AR_MINOR_VERSION) || \
         (PWM_AR_PATCH_VERSION_EMIOS_LLD_IRQ_C != REG_ESYS_EMIOS_H_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of eMIOS_Pwm_LLD_IRQ.c and Reg_ESYS_EMIOS.h are different"
    #endif
#endif

/* Check if source file and Reg_ESYS_EMIOS.h are of the same software version */
#if ((PWM_SW_MAJOR_VERSION_EMIOS_LLD_IRQ_C != REG_ESYS_EMIOS_H_SW_MAJOR_VERSION) || \
     (PWM_SW_MINOR_VERSION_EMIOS_LLD_IRQ_C != REG_ESYS_EMIOS_H_SW_MINOR_VERSION)  || \
     (PWM_SW_PATCH_VERSION_EMIOS_LLD_IRQ_C != REG_ESYS_EMIOS_H_SW_PATCH_VERSION))
#error "Software Version Numbers of eMIOS_Pwm_LLD_IRQ.c and Reg_ESYS_EMIOS.h are different"
#endif




#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and DEM header file are of the same version */
    #if ((PWM_AR_MAJOR_VERSION_EMIOS_LLD_IRQ_C != DEM_AR_MAJOR_VERSION) || \
         (PWM_AR_MINOR_VERSION_EMIOS_LLD_IRQ_C != DEM_AR_MINOR_VERSION))
        #error "AutoSar Version Numbers of eMIOS_Pwm_LLD_IRQ.c and Dem.h are different"
    #endif
#endif

/* Check if source file and DET header file are of the same version */
#if (PWM_DEV_ERROR_DETECT == STD_ON)
    #ifdef CHECK_AUTOSAR_VERSION
        #if ((PWM_AR_MAJOR_VERSION_EMIOS_LLD_IRQ_C != DET_AR_MAJOR_VERSION) || \
             (PWM_AR_MINOR_VERSION_EMIOS_LLD_IRQ_C != DET_AR_MINOR_VERSION))
            #error "AutoSar Version Numbers of eMIOS_Pwm_LLD_IRQ.c and Det.h are different"
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
#define PWM_START_SEC_CODE
/*lint -save -e961 -e537 -e451 */
/** @file eMIOS_Pwm_LLD_IRQ.c
    @note Violates MISRA 2004 Advisory Rule 19.1, 19.15 : See @ref eMIOS_Pwm_LLD_IRQ_C_REF_1,
    eMIOS_Pwm_LLD_IRQ_C_REF_2 */
#include "MemMap.h"
/*lint -restore */




/*===============================================================================================
                                       LOCAL FUNCTIONS
===============================================================================================*/

/*===============================================================================================
                                       GLOBAL FUNCTIONS
===============================================================================================*/

/**
@brief   Interrupt service routine to process the eMIOS interrupt
@details This function
         - clears the unified channel interrupt flag bit in Control register
         - calls the LLD layer handler

@param[in]     hw_ch_id      EMIOS channel ID that triggered the interrupt
@remarks Covers PWM005, PWM025, PWM026, PWM062, PWM115
*/

#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
FUNC (void, PWM_CODE) EMIOS_Pwm_LLD_ProcessInterrupt( VAR(Pwm_ChannelType, AUTOMATIC) hw_ch_id )
{
    VAR(Pwm_ChannelType, AUTOMATIC) ch_id;  /*  logical channel */

    VAR(Pwm_ChannelType, AUTOMATIC) mIdx;   /*  assigned eMIOS HW module  index */
    VAR(Pwm_ChannelType, AUTOMATIC) chIdx;  /*  assigned eMIOS HW channel index */

    /* store the associated hw channel ID */

    mIdx  = (uint8)((uint8)hw_ch_id >> EMIOS_MOD_SHIFT);
    chIdx = (uint8)((uint8)hw_ch_id &  EMIOS_CH_MASK);

   /** @file eMIOS_Pwm_LLD_IRQ.c
    @note Violates MISRA 2004 Advisory Rule 11.1 : See @ref eMIOS_Pwm_LLD_IRQ_C_REF_4
    */
    /*lint -save -e923 */
    /* clear unified channel interrupt flag */
    REG_WRITE32( EMIOS_CSR(mIdx, chIdx), CSR_FLAG_BIT );

    /* get logical channel ID */
    ch_id = Pwm_EMIOS_LLD_RevHardwareTable[hw_ch_id];

    /* Call Common Interrupt Routine */

    if ( 0xffU != ch_id ) {
        Pwm_LLD_ProcessInterrupt( ch_id ); /* call LLD layer handler */
    } else {
        /* IRQ received for HW channel but corresponding logical channel is not known -
           channel not configured by pwm driver */

        Dem_ReportErrorStatus((uint16) PWM_E_UNEXPECTED_IRQ, DEM_EVENT_STATUS_FAILED);
    }

}
#endif



#define PWM_STOP_SEC_CODE
/*lint -save -e961 -e537 -e451 */
/** @file eMIOS_Pwm_LLD_IRQ.c
    @note Violates MISRA 2004 Advisory Rule 19.1, 19.15 : See @ref eMIOS_Pwm_LLD_IRQ_C_REF_1,
    eMIOS_Pwm_LLD_IRQ_C_REF_2 */
#include "MemMap.h"
/*lint -restore */

#ifdef __cplusplus
}
#endif
