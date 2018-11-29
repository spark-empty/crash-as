/**
    @file    Siu_Icu_LLD_CfgEx.h
    @version 2.0.0

    @brief   AUTOSAR Icu - SIU low level driver exported structures.
    @details Interface between the high level driver (Autosar dependent) and the low level driver
    (platform dependent).

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
/*==================================================================================================
==================================================================================================*/

#ifndef SIU_ICU_LLD_EX_H
#define SIU_ICU_LLD_EX_H

#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** @remarks Covers BSW00374, BSW00379, BSW00318 */
#define SIU_ICU_LLD_CFG_EX_VENDOR_ID          43
#define SIU_ICU_LLD_CFG_EX_AR_MAJOR_VERSION   3
#define SIU_ICU_LLD_CFG_EX_AR_MINOR_VERSION   0
#define SIU_ICU_LLD_CFG_EX_AR_PATCH_VERSION   0
#define SIU_ICU_LLD_CFG_EX_SW_MAJOR_VERSION   2
#define SIU_ICU_LLD_CFG_EX_SW_MINOR_VERSION   0
#define SIU_ICU_LLD_CFG_EX_SW_PATCH_VERSION   0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/


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
@brief SIU External Interrupt Channels defines
@remarks
*/
#define SIU_IRQ_0    (uint8) 0U
#define SIU_IRQ_1    (uint8) 1U
#define SIU_IRQ_2    (uint8) 2U
#define SIU_IRQ_3    (uint8) 3U
#define SIU_IRQ_4    (uint8) 4U
#define SIU_IRQ_5    (uint8) 5U
#define SIU_IRQ_6    (uint8) 6U
#define SIU_IRQ_7    (uint8) 7U
#define SIU_IRQ_8    (uint8) 8U
#define SIU_IRQ_9    (uint8) 9U
#define SIU_IRQ_10   (uint8)10U
#define SIU_IRQ_11   (uint8)11U
#define SIU_IRQ_12   (uint8)12U
#define SIU_IRQ_13   (uint8)13U
#define SIU_IRQ_14   (uint8)14U
#define SIU_IRQ_15   (uint8)15U
/**@}*/

#define SIU_INT_FILTER_ENABLE  0x1U


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

#endif  /* SIU_ICU_LLD_EX_H */
