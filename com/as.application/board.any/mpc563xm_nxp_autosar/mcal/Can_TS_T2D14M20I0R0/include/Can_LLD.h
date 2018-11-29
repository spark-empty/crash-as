/**
    @file             Can_LLD.h
    @version          2.0.0

    @brief            AUTOSAR Can module interface
    @details          Main header file - can include different IPV models.

    Project           AUTOSAR 3.0 MCAL
    Platform          PA
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

@section Can_h_REF_1
Violates MISRA 2004 Advisory Rule 20.2, Re-use of C90 reserved identifier
This violation is due to the use of "_" which is required as per Autosar .
@section Can_h_REF_2
Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h
here are different kinds of execution code sections.
*/

#ifndef _CAN_LLD_H_
/**
@note Violates MISRA 2004 Advisory Rule 20.2, Re-use of C90 reserved identifier: _CAN_LLD_H_. - See @ref Can_h_REF_1
*/
#define _CAN_LLD_H_

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "FlexCan_LLD.h"


/*==================================================================================================
                                    SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define CAN_LLD_VENDOR_ID            43
#define CAN_LLD_MODULE_ID            80
#define CAN_LLD_AR_MAJOR_VERSION     3
#define CAN_LLD_AR_MINOR_VERSION     0
#define CAN_LLD_AR_PATCH_VERSION     0
#define CAN_LLD_SW_MAJOR_VERSION     2
#define CAN_LLD_SW_MINOR_VERSION     0
#define CAN_LLD_SW_PATCH_VERSION     0

#define CAN_START_SEC_CODE
/* MISRA-C:2004 19.15 VIOLATION: Refer to REF 2 above */
#include "MemMap.h"
#if ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WKP_EXT_SUPPORT == STD_ON))
/*================================================================================================*/
/**
@brief         Acknoledge WKPU int bit (WISR)
@details       Function used only when External Wakeup is enabled (External Wakeup involve using of WKPU external signals)

@param[in]     wkpu_channel WKPU channel that is set

@pre           External wakeup must be enabled
*/
/*================================================================================================*/
FUNC(void, CAN_CODE) Can_AckInt_ExtWkp(VAR(uint8, CAN_VAR) wkpu_channel);
#endif /* ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WKP_EXT_SUPPORT == STD_ON)) */


#if ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WKP_EXT_SUPPORT == STD_ON))
/*================================================================================================*/
/**
@brief         Configure WKPU in case of external wakeup used
@details       Function used only when External Wakeup is enabled (External Wakeup involve using of WKPU external signals)

@param[in]     wkpu_channel WKPU channel that is set
@param[in]     int_en interrupt request enable: IRER
@param[in]     wak_req_en external wakeup request enable: WRER

@pre           External wakeup must be enabled
*/
/*================================================================================================*/
FUNC(void, CAN_CODE) Can_EnDis_ExtWkp( VAR(uint8, CAN_VAR) wkpu_channel,
                                       VAR(uint8, CAN_VAR) int_en,
                                       VAR(uint8, CAN_VAR) wak_req_en );
#endif /* ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WKP_EXT_SUPPORT == STD_ON)) */


#if ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WKP_EXT_SUPPORT == STD_ON))
/*================================================================================================*/
/**
@brief         Init WKPU in case of external wakeup used
@details       Function used only when External Wakeup is enabled (External Wakeup involve using of WKPU external signals)

@param[in]     wkpu_channel - WKPU channel that is set

@pre           External wakeup must be enabled
*/
/*================================================================================================*/
FUNC(void, CAN_CODE) Can_Init_ExtWkp( VAR(uint8, CAN_VAR) wkpu_channel);
#endif /* ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WKP_EXT_SUPPORT == STD_ON)) */


#if ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WKP_EXT_SUPPORT == STD_ON))
/*================================================================================================*/
/**
@brief         Get WKPU status channel in case of external wakeup used
@details       Function used only when External Wakeup is enabled (External Wakeup involve using of WKPU external signals)

@param[in]     wkpu_channel WKPU channel that is set

@return        Std_ReturnType  Return value
@retval        E_OK a wakeup was detected for the given controller.
@retval        E_NOT_OK no wakeup was detected for the given controller.

@pre           External wakeup must be enabled
*/
/*================================================================================================*/
FUNC(Std_ReturnType, CAN_CODE) Can_GetStatus_ExtWkp( VAR(uint8, CAN_VAR) wkpu_channel);
#endif /* ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WKP_EXT_SUPPORT == STD_ON)) */


#if ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WKP_EXT_SUPPORT == STD_ON))
/*================================================================================================*/
/**
@brief         Process external wakeup event
@details       Function used only when External Wakeup is enabled (External Wakeup involve using of WKPU external signals)

@param[in]     vector one of the WKPU vectors (0, 1, 2)

@pre           External wakeup must be enabled
*/
/*================================================================================================*/
FUNC(void, CAN_CODE) Can_Process_ExtWkp( VAR(uint8, CAN_VAR) vector);
#endif /* ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WKP_EXT_SUPPORT == STD_ON)) */

#define CAN_STOP_SEC_CODE
/* MISRA-C:2004 19.15 VIOLATION: Refer to REF 2 above */
#include "MemMap.h"

#endif  /* _CAN_LLD_H_ */


