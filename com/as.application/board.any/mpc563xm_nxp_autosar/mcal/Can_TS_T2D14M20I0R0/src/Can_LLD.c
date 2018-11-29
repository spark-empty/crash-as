/**
    @file             Can_LLD.c
    @version          2.0.0

    @brief            AUTOSAR Can module interface
    @details          API implementation for CAN driver.

    Project           AUTOSAR 3.0 MCAL
    Platform          PA
    Patform           PA
    Peripheral        FLEXCAN
    Dependencies      

    ARVersion         3.0.0
    ARRevision        ASR_REL_3_0_REV_0003
    ARConfVariant
    SWVersion         2.0.0
    BuildVersion      XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223

    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
    All Rights Reserved.
*/
/*==================================================================================================
==================================================================================================*/

/**
@page misra_violations MISRA-C:2004 violations

@section Can_LLD_c_REF_1
Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives.
This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003.

@section Can_LLD_c_REF_2
Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h
There are different kinds of execution code sections.
*/


#ifdef __cplusplus
extern "C"
{
#endif


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Can.h"
#include "Can_LLD.h"


/*==================================================================================================
                        DEFINES AND MACROS
==================================================================================================*/
/* The integration of incompatible files shall be avoided. */
#define CAN_LLD_VENDOR_ID_C         43
#define CAN_LLD_AR_MAJOR_VERSION_C  3
#define CAN_LLD_AR_MINOR_VERSION_C  0
#define CAN_LLD_AR_PATCH_VERSION_C  0
#define CAN_LLD_SW_MAJOR_VERSION_C  2
#define CAN_LLD_SW_MINOR_VERSION_C  0
#define CAN_LLD_SW_PATCH_VERSION_C  0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/


#if (CAN_LLD_VENDOR_ID_C != CAN_VENDOR_ID)
#error "Can_LLD.c and Can.h have different vendor ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
#if ((CAN_LLD_AR_MAJOR_VERSION_C != CAN_AR_MAJOR_VERSION) || \
     (CAN_LLD_AR_MINOR_VERSION_C != CAN_AR_MINOR_VERSION) || \
     (CAN_LLD_AR_PATCH_VERSION_C != CAN_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of Can_LLD.c and Can.h are different"
#endif
#endif

#if ((CAN_LLD_SW_MAJOR_VERSION_C != CAN_SW_MAJOR_VERSION) || \
     (CAN_LLD_SW_MINOR_VERSION_C != CAN_SW_MINOR_VERSION))
#error "Software Version Numbers of Can_LLD.c and Can.h are different"
#endif


/* Check if source file and CAN_LLD header file are of the same vendor */
#if (CAN_LLD_VENDOR_ID_C != CAN_LLD_VENDOR_ID)
#error "Can_LLD.c and Can_LLD.h have different vendor ids"
#endif

/* Check if source file and CAN_LLD header file are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((CAN_LLD_AR_MAJOR_VERSION_C != CAN_LLD_AR_MAJOR_VERSION) || \
        (CAN_LLD_AR_MINOR_VERSION_C != CAN_LLD_AR_MINOR_VERSION) || \
        (CAN_LLD_AR_PATCH_VERSION_C != CAN_LLD_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Can_LLD.c and Can_LLD.h are different"
    #endif
#endif
/* Check if source file and CAN_LLD header file are of the same Software version */
#if ((CAN_LLD_SW_MAJOR_VERSION_C != CAN_LLD_SW_MAJOR_VERSION) || \
     (CAN_LLD_SW_MINOR_VERSION_C != CAN_LLD_SW_MINOR_VERSION) || \
     (CAN_LLD_SW_PATCH_VERSION_C != CAN_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of Can_LLD.c and Can_LLD.h are different"
#endif

/*==================================================================================================
                        GLOBAL FUNCTIONS
==================================================================================================*/
#define CAN_START_SEC_CODE
/**
@file  Can_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives. - See @ref Can_LLD_c_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref Can_LLD_c_REF_2
*/
/*lint -save -e537 -e961*/
#include "MemMap.h"
/*lint -restore*/


#if ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WKP_EXT_SUPPORT == STD_ON))
/*================================================================================================*/
/**
@brief        Acknoledge WKPU int bit (WISR)
@details      Function used only when External Wakeup is enabled (External Wakeup involve using of WKPU external signals)

@param[in]    wkpu_channel WKPU channel that is set
*/
/*================================================================================================*/
FUNC(void, CAN_CODE) Can_AckInt_ExtWkp(VAR(uint8, CAN_VAR) wkpu_channel)
    {

         /* Do nothing - Wake-up is done by ICU */
    }

#endif /* ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WKP_EXT_SUPPORT == STD_ON)) */

#if ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WKP_EXT_SUPPORT == STD_ON))
/*================================================================================================*/
/**
@brief         Configure WKPU in case of external wakeup used
@details       Function used only when External Wakeup is enabled (External Wakeup involve using of WKPU external signals)

@param[in]     wkpu_channel WKPU channel that is set
@param[in]     int_en interrupt request enable: IRER
@param[in]     wak_req_en external wakeup request enable: WRER
*/
/*================================================================================================*/
FUNC(void, CAN_CODE) Can_EnDis_ExtWkp( VAR(uint8, CAN_VAR) wkpu_channel, VAR(uint8, CAN_VAR) int_en, VAR(uint8, CAN_VAR) wak_req_en )
    {

    /* Do nothing - Wake-up is done by ICU */

    }
#endif /* ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WKP_EXT_SUPPORT == STD_ON)) */


#if ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WKP_EXT_SUPPORT == STD_ON))
/*================================================================================================*/
/**
@brief         Init WKPU in case of external wakeup used
@details       Function used only when External Wakeup is enabled (External Wakeup involve using of WKPU external signals)

@param[in]     wkpu_channel - WKPU channel that is set
*/
/*================================================================================================*/
FUNC(void, CAN_CODE) Can_Init_ExtWkp( VAR(uint8, CAN_VAR) wkpu_channel)
    {
         /* Do nothing - Wake-up is done by ICU */
    }
#endif /* ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WKP_EXT_SUPPORT == STD_ON)) */


#if ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WKP_EXT_SUPPORT == STD_ON))
/*================================================================================================*/
/**
@brief         Get WKPU status channel in case of external wakeup used
@details       Function used only when External Wakeup is enabled (External Wakeup involve using of WKPU external signals)

@param[in]     wkpu_channel WKPU channel that is set

@return        Std_ReturnType Return value
@retval        E_OK wakeup detected
@retval        E_NOT_OK wakeup not detected
*/
/*================================================================================================*/
FUNC( Std_ReturnType, CAN_CODE) Can_GetStatus_ExtWkp( VAR(uint8, CAN_VAR) wkpu_channel)
    {
        /* Return value */
        VAR(boolean, CAN_VAR) ret_val = (uint8)E_NOT_OK;

        /* Do nothing - Wake-up is done by ICU */

        return (ret_val);
    }
#endif /* ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WKP_EXT_SUPPORT == STD_ON)) */


#if ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WKP_EXT_SUPPORT == STD_ON))
/*================================================================================================*/
/**
@brief         Process external wakeup event
@details       Function used only when External Wakeup is enabled (External Wakeup involve using of WKPU external signals)

@param[in]     vector one of the WKPU vectors (0, 1, 2)
*/
/*================================================================================================*/
FUNC(void, CAN_CODE) Can_Process_ExtWkp( VAR(uint8, CAN_VAR) vector)
    {
    /* Do nothing - Wake-up is done by ICU */

    }
#endif /* ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WKP_EXT_SUPPORT == STD_ON)) */


#define CAN_STOP_SEC_CODE
/**
@file  Can_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives. - See @ref Can_LLD_c_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref Can_LLD_c_REF_2
*/
/*lint -save -e537 -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif

