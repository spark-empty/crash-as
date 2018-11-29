/**
    @file    Stm_Gpt_LLD_IRQ.c
    @version 2.0.0

    @brief   AUTOSAR Gpt - Brief description.
    @details Detailed description.

    Project AUTOSAR 3.0 MCAL
    Patform PA
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

@section STM_GPT_LLD_IRQ_C_REF_1
Violates   MISRA  2004  Advisory  Rule   19.1: only preprocessor statements and comments before "#include".
This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement MEMMAP003.

@section STM_GPT_LLD_IRQ_C_REF_2
Violates MISRA 2004 Advisory Rule 19.15 : Repeated include file
This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement
MEMMAP003.

@section STM_GPT_LLD_IRQ_C_REF_3
Violates MISRA 2004 Advisory Rule 11.1 : cast from unsigned long to pointer.
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
#include "Gpt.h"
#include "Reg_eSys_STM.h"
#include "Mcal.h"
#include "Gpt_LLD.h"

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/**
@brief Parameters that shall be published within the Gpt driver header file and also in the
       module's description file
@remarks Covers BSW00374, BSW00379, BSW00318
@{
*/

#define STM_GPT_LLD_IRQ_VENDOR_ID_C         43
#define STM_GPT_LLD_IRQ_AR_MAJOR_VERSION_C  3
#define STM_GPT_LLD_IRQ_AR_MINOR_VERSION_C  0
#define STM_GPT_LLD_IRQ_AR_PATCH_VERSION_C  0
#define STM_GPT_LLD_IRQ_SW_MAJOR_VERSION_C  2
#define STM_GPT_LLD_IRQ_SW_MINOR_VERSION_C  0
#define STM_GPT_LLD_IRQ_SW_PATCH_VERSION_C  0
/**@}*/
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#if (STM_GPT_LLD_IRQ_VENDOR_ID_C != REG_ESYS_STM_VENDOR_ID)
#error "Stm_Gpt_LLD_IRQ.c and Reg_eSys_STM.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if header file and Gpt header file are of the same Autosar version */
    #if ((STM_GPT_LLD_IRQ_AR_MAJOR_VERSION_C != REG_ESYS_STM_AR_MAJOR_VERSION) || \
         (STM_GPT_LLD_IRQ_AR_MINOR_VERSION_C != REG_ESYS_STM_AR_MINOR_VERSION) || \
         (STM_GPT_LLD_IRQ_AR_PATCH_VERSION_C != REG_ESYS_STM_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Stm_Gpt_LLD_IRQ.c and Reg_eSys_STM.h are different"
    #endif
#endif
/* Check if source file and GPT header file are of the same Software version */
#if ((STM_GPT_LLD_IRQ_SW_MAJOR_VERSION_C != REG_ESYS_STM_SW_MAJOR_VERSION) || \
     (STM_GPT_LLD_IRQ_SW_MINOR_VERSION_C != REG_ESYS_STM_SW_MINOR_VERSION) || \
     (STM_GPT_LLD_IRQ_SW_PATCH_VERSION_C != REG_ESYS_STM_SW_PATCH_VERSION) )
    #error "Software Version Numbers of Stm_Gpt_LLD_IRQ.c and Reg_eSys_STM.h are different"
#endif

#if (STM_GPT_LLD_IRQ_VENDOR_ID_C != GPT_VENDOR_ID)
#error "Stm_Gpt_LLD_IRQ.c and Gpt_Cfg.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if header file and Gpt header file are of the same Autosar version */
    #if ((STM_GPT_LLD_IRQ_AR_MAJOR_VERSION_C != GPT_AR_MAJOR_VERSION) || \
         (STM_GPT_LLD_IRQ_AR_MINOR_VERSION_C != GPT_AR_MINOR_VERSION) || \
         (STM_GPT_LLD_IRQ_AR_PATCH_VERSION_C != GPT_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Stm_Gpt_LLD_IRQ.c and Gpt.h are different"
    #endif
#endif
/* Check if source file and GPT header file are of the same Software version */
#if ((STM_GPT_LLD_IRQ_SW_MAJOR_VERSION_C != GPT_SW_MAJOR_VERSION) || \
     (STM_GPT_LLD_IRQ_SW_MINOR_VERSION_C != GPT_SW_MINOR_VERSION) || \
     (STM_GPT_LLD_IRQ_SW_PATCH_VERSION_C != GPT_SW_PATCH_VERSION) )
    #error "Software Version Numbers of Stm_Gpt_LLD_IRQ.c and Gpt.h are different"
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
#ifdef GPT_STM_CH_0_ISR_USED
ISR(Gpt_STM_Ch_0_ISR);
#endif

#ifdef GPT_STM_CH_1_ISR_USED
ISR(Gpt_STM_Ch_1_ISR);
#endif

#ifdef GPT_STM_CH_2_ISR_USED
ISR(Gpt_STM_Ch_2_ISR);
#endif

#ifdef GPT_STM_CH_3_ISR_USED
ISR(Gpt_STM_Ch_3_ISR);
#endif

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define GPT_START_SEC_CODE
/**
@file   Stm_Gpt_LLD_IRQ.c
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref STM_GPT_LLD_IRQ_C_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref STM_GPT_LLD_IRQ_C_REF_2
*/


/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

#ifdef GPT_STM_CH_0_ISR_USED
/*************************************************************************************************/
/**
@brief   Interrupt handler for STM channels.
@details Interrupt Service Routine corresponding to Gpt_STM_Ch_0 hw channel.

*/
/*************************************************************************************************/

ISR(Gpt_STM_Ch_0_ISR)
{
    STM_Gpt_ProcessInterrupt((Gpt_ChannelType)STM_CH_0);
    EXIT_INTERRUPT();
}
#endif
#ifdef GPT_STM_CH_1_ISR_USED
/*************************************************************************************************/
/**
@brief   Interrupt handler for STM channels.
@details Interrupt Service Routine corresponding to Gpt_STM_Ch_1 hw channel.

*/
/*************************************************************************************************/

ISR(Gpt_STM_Ch_1_ISR)
{
#ifndef GPT_STM_ISR_1_SHARED
    STM_Gpt_ProcessInterrupt((Gpt_ChannelType)STM_CH_1);
#else
     /**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer
                               - See STM_GPT_LLD_IRQ_C_REF_3 */
    if (STM_CH_READ_ISR_REQ(STM_CH_1))

    {
        STM_Gpt_ProcessInterrupt((Gpt_ChannelType)STM_CH_1);
    }
     /**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer
                               - See STM_GPT_LLD_IRQ_C_REF_3 */
    else if (STM_CH_READ_ISR_REQ(STM_CH_2))
    {
        STM_Gpt_ProcessInterrupt((Gpt_ChannelType)STM_CH_2);
    }
     /**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer
                               - See STM_GPT_LLD_IRQ_C_REF_3 */
    else if (STM_CH_READ_ISR_REQ(STM_CH_3))
    {
        STM_Gpt_ProcessInterrupt((Gpt_ChannelType)STM_CH_3);
    }
    else
    {
    }
#endif
 /**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned int to pointer
                     - See STM_GPT_LLD_IRQ_C_REF_3 */
    EXIT_INTERRUPT();
}
#endif

#ifndef GPT_STM_ISR_1_SHARED
#ifdef GPT_STM_CH_2_ISR_USED
/*************************************************************************************************/
/**
@brief   Interrupt handler for STM channels.
@details Interrupt Service Routine corresponding to Gpt_STM_Ch_2 hw channel.

*/
/*************************************************************************************************/

ISR(Gpt_STM_Ch_2_ISR)
{
    STM_Gpt_ProcessInterrupt((Gpt_ChannelType)STM_CH_2);
 /**@note  Violates MISRA 2004 Advisory Rule 11.1 cast from unsigned long to pointer
                               - See STM_GPT_LLD_IRQ_C_REF_3 */
    EXIT_INTERRUPT();
}
#endif
#ifdef GPT_STM_CH_3_ISR_USED
/*************************************************************************************************/
/**
@brief   Interrupt handler for STM channels.
@details Interrupt Service Routine corresponding to Gpt_STM_Ch_3 hw channel.

*/
/*************************************************************************************************/

ISR(Gpt_STM_Ch_3_ISR)
{
    STM_Gpt_ProcessInterrupt((Gpt_ChannelType)STM_CH_3);
    EXIT_INTERRUPT();
}
#endif

#endif


#define GPT_STOP_SEC_CODE
/**
@file   Stm_Gpt_LLD_IRQ.c
@note  Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before "#include" - See @ref STM_GPT_LLD_IRQ_C_REF_1
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref STM_GPT_LLD_IRQ_C_REF_2
*/

/*lint -save -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif
