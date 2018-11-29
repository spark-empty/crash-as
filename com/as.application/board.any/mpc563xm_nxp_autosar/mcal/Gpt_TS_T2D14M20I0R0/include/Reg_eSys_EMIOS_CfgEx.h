/**
    @file    Reg_eSys_EMIOS_CfgEx.h
    @version 2.0.0

    @brief   AUTOSAR Gpt - defines needed by upper layer.
    @details defines needed by upper layer.

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
@file    Reg_eSys_EMIOS_CfgEx.h
*/

/**
@page misra_violations MISRA-C:2004 violations

@section Reg_eSys_EMIOS_CfgEx_h_1
Violates MISRA 2004 Advisory Rule 19.15, :  Repeated include file MemMap.h  Precautions shall be
taken in order to prevent the contents of a header file being included twice This is not a violation
since all header files are protected against multiple inclusions

@section Reg_eSys_EMIOS_CfgEx_h_2
Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
This violation is due to function like macros defined for register operations.
Function like macros are used to reduce code complexity.
*/
#ifndef REG_ESYS_EMIOS_CFGEX_H
#define REG_ESYS_EMIOS_CFGEX_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/*lint -save -e537*/
/**
@file  Reg_eSys_EMIOS_CfgEx.h
@note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header file
       being included twice See @ref Reg_eSys_EMIOS_CfgEx_h_1 */
#include "modules.h"
#include "Reg_eSys.h"
#include "Reg_Macros.h"
/*lint -restore*/

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@{
@brief   Header file version information
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define REG_ESYS_EMIOS_CFGEX_H_VENDOR_ID            43

#define REG_ESYS_EMIOS_CFGEX_H_AR_MAJOR_VERSION     3
#define REG_ESYS_EMIOS_CFGEX_H_AR_MINOR_VERSION     0
#define REG_ESYS_EMIOS_CFGEX_H_AR_PATCH_VERSION     0
#define REG_ESYS_EMIOS_CFGEX_H_SW_MAJOR_VERSION     2
#define REG_ESYS_EMIOS_CFGEX_H_SW_MINOR_VERSION     0
#define REG_ESYS_EMIOS_CFGEX_H_SW_PATCH_VERSION     0
/**@}*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* No checks needed as the included files ( Reg_eSys.h, Reg_Macros.h) do not define versions */


/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/



/**
@{
@brief EMIOS channels defines
*/

/*
 * EMIOS channel encoding
 *
 * [              3 bit | 5 bit                ]
 * [ module id: 7 ... 0 | channel id: 31 ... 0 ]
 */

#define EMIOS_MOD_MASK  (uint8)0xE0
#define EMIOS_MOD_SHIFT (uint8)5U
#define EMIOS_CH_MASK   (uint8)0x1F
#define EMIOS_CH_SHIFT  (uint8)0U


/*lint -save -e961 */
/*
 * EMIOS module and channel decoding
 */
  /**
  @note  Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
  See @ref Reg_eSys_EMIOS_CfgEx_h_2
  */
#define EMIOS_MODULE_INDEX(ch)      (uint8)(((ch) & EMIOS_MOD_MASK) >> EMIOS_MOD_SHIFT)
#define EMIOS_CHANNEL_INDEX(ch)     (uint8)(((ch) & EMIOS_CH_MASK)  >> EMIOS_CH_SHIFT)
/*lint -restore */

/**
@{
@brief EMIOS Channels defines
*/
#define EMIOS_0_CH_0    (uint8)0x00
#define EMIOS_0_CH_1    (uint8)0x01
#define EMIOS_0_CH_2    (uint8)0x02
#define EMIOS_0_CH_3    (uint8)0x03
#define EMIOS_0_CH_4    (uint8)0x04
#define EMIOS_0_CH_5    (uint8)0x05
#define EMIOS_0_CH_6    (uint8)0x06
#define EMIOS_0_CH_7    (uint8)0x07
#define EMIOS_0_CH_8    (uint8)0x08
#define EMIOS_0_CH_9    (uint8)0x09
#define EMIOS_0_CH_10   (uint8)0x0A
#define EMIOS_0_CH_11   (uint8)0x0B
#define EMIOS_0_CH_12   (uint8)0x0C
#define EMIOS_0_CH_13   (uint8)0x0D
#define EMIOS_0_CH_14   (uint8)0x0E
#define EMIOS_0_CH_15   (uint8)0x0F
#define EMIOS_0_CH_16   (uint8)0x10
#define EMIOS_0_CH_17   (uint8)0x11
#define EMIOS_0_CH_18   (uint8)0x12
#define EMIOS_0_CH_19   (uint8)0x13
#define EMIOS_0_CH_20   (uint8)0x14
#define EMIOS_0_CH_21   (uint8)0x15
#define EMIOS_0_CH_22   (uint8)0x16
#define EMIOS_0_CH_23   (uint8)0x17
#define EMIOS_0_CH_24   (uint8)0x18
#define EMIOS_0_CH_25   (uint8)0x19
#define EMIOS_0_CH_26   (uint8)0x1A
#define EMIOS_0_CH_27   (uint8)0x1B
#define EMIOS_0_CH_28   (uint8)0x1C
#define EMIOS_0_CH_29   (uint8)0x1D
#define EMIOS_0_CH_30   (uint8)0x1E
#define EMIOS_0_CH_31   (uint8)0x1F


#define EMIOS_1_CH_0    (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x00)
#define EMIOS_1_CH_1    (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x01)
#define EMIOS_1_CH_2    (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x02)
#define EMIOS_1_CH_3    (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x03)
#define EMIOS_1_CH_4    (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x04)
#define EMIOS_1_CH_5    (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x05)
#define EMIOS_1_CH_6    (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x06)
#define EMIOS_1_CH_7    (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x07)
#define EMIOS_1_CH_8    (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x08)
#define EMIOS_1_CH_9    (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x09)
#define EMIOS_1_CH_10   (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x0A)
#define EMIOS_1_CH_11   (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x0B)
#define EMIOS_1_CH_12   (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x0C)
#define EMIOS_1_CH_13   (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x0D)
#define EMIOS_1_CH_14   (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x0E)
#define EMIOS_1_CH_15   (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x0F)
#define EMIOS_1_CH_16   (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x10)
#define EMIOS_1_CH_17   (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x11)
#define EMIOS_1_CH_18   (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x12)
#define EMIOS_1_CH_19   (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x13)
#define EMIOS_1_CH_20   (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x14)
#define EMIOS_1_CH_21   (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x15)
#define EMIOS_1_CH_22   (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x16)
#define EMIOS_1_CH_23   (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x17)
#define EMIOS_1_CH_24   (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x18)
#define EMIOS_1_CH_25   (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x19)
#define EMIOS_1_CH_26   (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x1A)
#define EMIOS_1_CH_27   (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x1B)
#define EMIOS_1_CH_28   (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x1C)
#define EMIOS_1_CH_29   (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x1D)
#define EMIOS_1_CH_30   (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x1E)
#define EMIOS_1_CH_31   (uint8)((uint8)(1U<<EMIOS_MOD_SHIFT) + (uint8)0x1F)
/**@}*/
/**@}*/


/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif
/* REG_ESYS_EMIOS_CFGEX_H */
#endif 

