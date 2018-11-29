/**
    @file    Reg_eSys_PITRTI.h
    @version 2.0.0

    @brief   AUTOSAR Gpt - Brief description.
    @details Detailed description.
    
    Project AUTOSAR 3.0 MCAL
    Platform PA
    Peripheral eMIOS200_Stm_PitRti
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
@page misra_violations MISRA-C:2004 violations


@section REG_ESYS_PITRTI_H_REF_1
Violates MISRA 2004 Advisory Rule  19.7:Use of fucntion like macro.This vioaltion is due to function like
macro defined for register operations .Function like macro are used to reduce code complexity.

@section REG_ESYS_PITRTI_H_REF_2
Violates MISRA 2004 Advisory Rule 19.1: Violates  MISRA 2004  Advisory  Rule 19.1, only preprocessor
statements and comments before "#include"
This violation is not fixed since  the inclusion of MemMap.h is as per Autosar requirement
MEMMAP003.

@section REG_ESYS_PITRTI_H_REF_3
Violates MISRA 2004 Advisory Rule 19.15 : Repeated include file
This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement
MEMMAP003.

*/
#ifndef REG_ESYS_PITRTI_H
#define REG_ESYS_PITRTI_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/**
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file See @ref REG_ESYS_PITRTI_H_REF_3
*/
#include "Reg_eSys.h"
#include "Reg_Macros.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@brief Parameters that shall be published within the Gpt driver header file and also in the
       module's description file
@remarks Covers BSW00374, BSW00379, BSW00318
@{
*/
#define REG_ESYS_PITRTI_VENDOR_ID            43
#define REG_ESYS_PITRTI_AR_MAJOR_VERSION     3
#define REG_ESYS_PITRTI_AR_MINOR_VERSION     0
#define REG_ESYS_PITRTI_AR_PATCH_VERSION     0
#define REG_ESYS_PITRTI_SW_MAJOR_VERSION     2
#define REG_ESYS_PITRTI_SW_MINOR_VERSION     0
#define REG_ESYS_PITRTI_SW_PATCH_VERSION     0
/**@}*/
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* 
*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/* PITRTI Registers */

#define PITRTI_MCR                                          (PITRTI_BASEADDR + (uint32)0x00UL)

/* RTI Channel Registers */
#define PITRTI_LDVAL_RTI                                 (PITRTI_BASEADDR + (uint32)0x00F0UL)
#define PITRTI_CVAL_RTI                                  (PITRTI_BASEADDR + (uint32)0x00F4UL)
#define PITRTI_TCRTL_RTI                                 (PITRTI_BASEADDR + (uint32)0x00F8UL)
#define PITRTI_TFLG_RTI                                  (PITRTI_BASEADDR + (uint32)0x00FCUL)

/* PITRTI Channels Registers */
#define PITRTI_LDVAL0                                    (PITRTI_BASEADDR + (uint32)0x0100UL)
/**
@note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro - See @ref REG_ESYS_PITRTI_H_REF_1
*/
/*lint -save -e961 */
/**
@brief Timer Load Value Register (LDVAL)  Register address where as n is channel number
*/
#define PITRTI_LDVAL(n)                                  (PITRTI_LDVAL0 + (uint32)((n)*0x0010UL))
/**
@brief Current Timer Value Register (CVAL)  Register address
*/
#define PITRTI_CVAL0                                     (PITRTI_BASEADDR + (uint32)0x0104UL)
/**
@note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro - See @ref REG_ESYS_PITRTI_H_REF_1
*/
/**
@brief Current Timer Value Register (CVAL)  Register address where as n is channel number
*/
#define PITRTI_CVAL(n)                                   (PITRTI_CVAL0 + (uint32)((n)*0x0010UL))
/**
@brief Timer Flag Register (TFLG)  Register address
*/
#define PITRTI_TFLG0                                     (PITRTI_BASEADDR + (uint32)0x010CUL)
/**

@note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro - See @ref REG_ESYS_PITRTI_H_REF_1
*/

/**
@brief Timer Flag Register (TFLG)  Register address where as n is channel number
*/
#define PITRTI_TFLG(n)                                   (PITRTI_TFLG0 + (uint32)((n)*0x0010UL))
/*lint -restore */
/**
@brief TFLG - bitfield defines.TIF bits in the Timer Flag Register (TFLG) register
*/
/**
@brief Timer Control Register (TCTRL)  Register address
*/
#define PITRTI_TCTRL0                                     (PITRTI_BASEADDR + (uint32)0x0108UL)
/**

@note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro - See @ref REG_ESYS_PITRTI_H_REF_1
*/
/*lint -save -e961 */

/**
@brief Timer Control Register (TCTRL)  Register address where as n is channel number
*/
#define PITRTI_TCTRL(n)                                     (PITRTI_TCTRL0 + (uint32)((n)*0x0010UL))
/*lint -restore */

/* Bit masks */

/* Bits in the PITRTI_MCR register */
#define PITRTI_MCR_MDIS_RTI                                 (uint32)0x00000004
#define PITRTI_MCR_MDIS                                    (uint32)0x00000002
#define PITRTI_MCR_FRZ                                    (uint32)0x00000001
/* Highest possible loading value for PITRTI channels */
#define PITRTI_LDVAL_MAX_VALUE                           (uint32)0xFFFFFFFFuL
/* Bits in the PITRTI_TFLG register */
#define PITRTI_TFLG_TIF                                  (uint32)0x00000001
/**
@brief TCTRL - bitfield defines. TIE and TEN bits in the Timer Control Register (TCTRL)
*/
#define PITRTI_TCTRL_TIE                                  (uint32)0x00000002
#define PITRTI_TCTRL_TEN                                  (uint32)0x00000001

/* Macros */
/**

@note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro - See @ref REG_ESYS_PITRTI_H_REF_1
*/
/* This is applicable for the following lines of code */
/*lint -save -e961 */
/**
@brief Macro to Enable Clock for PITRTI Timers
*/
#define PITRTI_ENABLE_MODULE()             (REG_BIT_CLEAR32(PITRTI_MCR,PITRTI_MCR_MDIS))
/**
@brief Macro to disable Clock for PITRTI Timers
*/
/**
@note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro - See @ref REG_ESYS_PITRTI_H_REF_1
*/
#define PITRTI_DISABLE_MODULE()            (REG_BIT_SET32(PITRTI_MCR,PITRTI_MCR_MDIS))
#define PITRTI_ENABLE_RTI_CLOCK()          (REG_BIT_CLEAR32(PITRTI_MCR,PITRTI_MCR_MDIS_RTI))
#define PITRTI_DISABLE_RTI_CLOCK()            (REG_BIT_SET32(PITRTI_MCR,PITRTI_MCR_MDIS_RTI))
/**
@brief Macro to Enable the Freeze
*/
/**
@note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro - See @ref REG_ESYS_PITRTI_H_REF_1
*/

#define PITRTI_FREEZE_ENABLE()               (REG_BIT_SET32(PITRTI_MCR,PITRTI_MCR_FRZ))
/**
@brief Macro to disable the Freeze
*/
/**
@note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro - See @ref REG_ESYS_PITRTI_H_REF_1
*/

#define PITRTI_FREEZE_DISABLE()            (REG_BIT_CLEAR32(PITRTI_MCR,PITRTI_MCR_FRZ))
/**
@brief Macro to Enable PITRTI timer
*/
/**
@note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro - See @ref REG_ESYS_PITRTI_H_REF_1
*/

#define PITRTI_TIMER_ENABLE(channel)       (REG_BIT_SET32(PITRTI_TCTRL(channel)  ,(uint32)PITRTI_TCTRL_TEN))
/**
@brief Macro to Disable PITRTI timer
*/
/**
@note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro - See @ref REG_ESYS_PITRTI_H_REF_1
*/
#define PITRTI_TIMER_DISABLE(channel)      (REG_BIT_CLEAR32(PITRTI_TCTRL(channel) ,(uint32)PITRTI_TCTRL_TEN))
/**
@brief Macro to read the PITRTI timer status
*/
/**
@note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro - See @ref REG_ESYS_PITRTI_H_REF_1
*/
#define PITRTI_Read_State(channel)         (REG_READ32(PITRTI_TCTRL(channel))&((uint32)PITRTI_TCTRL_TEN))

/**
@brief Macro to Enable PITRTI interrupt
*/
/**
@note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro - See @ref REG_ESYS_PITRTI_H_REF_1
*/
#define PITRTI_INTERRUPT_ENABLE(channel)   (REG_BIT_SET32(PITRTI_TCTRL(channel),(uint32)PITRTI_TCTRL_TIE))
/**
@brief Macro to Disable the PITRTI interrupt
*/
/**
@note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro - See @ref REG_ESYS_PITRTI_H_REF_1
*/
#define PITRTI_INTERRUPT_DISABLE(channel)  (REG_BIT_CLEAR32(PITRTI_TCTRL(channel),(uint32)PITRTI_TCTRL_TIE))
/**
@brief Macro to clear the interrupt flag
*/
/**
@note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro - See @ref REG_ESYS_PITRTI_H_REF_1
*/
#define PITRTI_CLEAR_INT_FLAG(channel)     (REG_WRITE32(PITRTI_TFLG(channel),(uint32)PITRTI_TFLG_TIF))
/**
@brief Macro to read the flag bit
*/
/**
@note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro - See @ref REG_ESYS_PITRTI_H_REF_1
*/
#define PITRTI_Read_Interrupt(channel)       ((REG_READ32(PITRTI_TFLG(channel)))&((uint32)PITRTI_TFLG_TIF))

/**
@brief Macro to read the timer value
*/
/**
@note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro - See @ref REG_ESYS_PITRTI_H_REF_1
*/
#define PITRTI_READTIMERVALUE(channel)     (REG_READ32(PITRTI_CVAL(channel)))
/**
@brief Macro to write the timeout value into Timer Load Value Register (LDVAL)
*/
/**
@note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro - See @ref REG_ESYS_PITRTI_H_REF_1
*/
#define PITRTI_SETLOADVALUE(channel,value) (REG_WRITE32(PITRTI_LDVAL(channel), value))
/**
@brief Macro to read the timeout value form Timer Load Value Register (LDVAL)
*/
/**
@note  Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro - See @ref REG_ESYS_PITRTI_H_REF_1
*/
#define PITRTI_GETLOADVALUE(channel)       (REG_READ32(PITRTI_LDVAL(channel)))

#define PITRTI_RTC_COUNTER_ENABLE()        (REG_BIT_SET32(PITRTI_TCRTL_RTI, (uint32)PITRTI_TCTRL_TEN))
#define PITRTI_RTC_COUNTER_DISABLE()       (REG_BIT_CLEAR32(PITRTI_TCRTL_RTI, (uint32)PITRTI_TCTRL_TEN))
#define PITRTI_RTC_READ_STATE()            (REG_READ32(PITRTI_TCRTL_RTI) & (uint32)PITRTI_TCTRL_TEN)
#define PITRTI_RTC_INT_ENABLE()            (REG_BIT_SET32(PITRTI_TCRTL_RTI, (uint32)PITRTI_TCTRL_TIE))
#define PITRTI_RTC_INT_DISABLE()           (REG_BIT_CLEAR32(PITRTI_TCRTL_RTI, (uint32)PITRTI_TCTRL_TIE))

#define PITRTI_RTC_CLEAR_INTERRUPT()       (REG_WRITE32(PITRTI_TFLG_RTI,(uint32)PITRTI_TFLG_TIF))
#define PITRTI_RTC_READ_INTERRUPT()           ((REG_READ32(PITRTI_TFLG_RTI))&((uint32)PITRTI_TFLG_TIF))

#define PITRTI_RTC_SET_VALUE(value)        (REG_WRITE32(PITRTI_LDVAL_RTI, value))
#define PITRTI_RTC_GET_VALUE()             (REG_READ32(PITRTI_LDVAL_RTI))
#define PITRTI_RTC_GET_COUNTER()           (REG_READ32(PITRTI_CVAL_RTI))
/* MISRA-C:2004 19.7 VIOLATION: End of code block */  
/*lint -restore */

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

#ifndef GPT_PRECOMPILE_SUPPORT
#define GPT_START_CONFIG_DATA_UNSPECIFIED
/**
@file  Reg_eSys_PITRTI.h
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref REG_ESYS_PITRTI_H_REF_2
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref REG_ESYS_PITRTI_H_REF_3
*/
/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if header file and MemMap.h file are of the same Autosar version */
    #if ((REG_ESYS_PITRTI_AR_MAJOR_VERSION != MEMMAP_AR_MAJOR_VERSION) || \
         (REG_ESYS_PITRTI_AR_MINOR_VERSION != MEMMAP_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Reg_eSys_PITRTI.h and MemMap.h are different"
    #endif
#endif

#define GPT_STOP_CONFIG_DATA_UNSPECIFIED
/**
@file  Reg_eSys_PITRTI.h
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref REG_ESYS_PITRTI_H_REF_2
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref REG_ESYS_PITRTI_H_REF_3
*//*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/
#endif

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /*REG_ESYS_PITRTI_H*/
