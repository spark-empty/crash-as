/**
    @file        Reg_eSys_DMA.h
    @version     2.0.0

    @brief       AUTOSAR Adc - eDMA Registers and Macros Definitions
    @details     eDMA Registers and Macros Definitions

    Project      : AUTOSAR 3.0 MCAL
    Platform     : PA
    Peripheral   : ADC_10B
    Dependencies : none

    Autosar Version       : 3.0.0
    Autosar Revision      : ASR_REL_3_0_REV_0003
    Autosar Conf. Variant :
    Software Version      : 2.0.0
    Build Version         : XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223

    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
    All Rights Reserved.
*/
/*==================================================================================================
==================================================================================================*/

/**
@page misra_violations MISRA-C:2004 violations

@section Reg_eSys_DMA_REF_1
Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
This violation is due to function like macros defined for register operations.
Function like macros are used to reduce code complexity.

@section Reg_eSys_DMA_REF_2
MISRA 2004 Advisory Rule 20.2, Re-use of C90 reserved identifier
This violation is due to the use of "_" which is required as per Autosar
*/

/**
@note Violates MISRA 2004 Advisory Rule 20.2, Re-use of C90 reserved
identifier:_REG_ESYS_DMA_H_- See @ref Reg_eSys_DMA_REF_2
*/
#ifndef _REG_ESYS_DMA_H_
#define _REG_ESYS_DMA_H_

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Reg_eSys.h"
#include "Reg_Macros.h"


/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** @remarks Covers BSW00374, BSW00379, BSW00318 */
#define DMA_VENDOR_ID_REG            43
#define DMA_AR_MAJOR_VERSION_REG     3
#define DMA_AR_MINOR_VERSION_REG     0
#define DMA_AR_PATCH_VERSION_REG     0
#define DMA_SW_MAJOR_VERSION_REG     2
#define DMA_SW_MINOR_VERSION_REG     0
#define DMA_SW_PATCH_VERSION_REG     0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                             ENUMS
==================================================================================================*/


/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/* for backward compatibility:
      - if DMA_NB_CONTOLERS not defined by Reg_eSys.h is supposed that only one controller exist
      - if DMA_NB_CHANNELS not defined by Reg_eSys.h is supposed that DMA support only 16 channels*/

#ifndef DMA_NB_CONTROLLERS
    #define DMA_NB_CONTROLLERS           (0x01U)
#endif

#ifndef DMA_NB_CHANNELS
    #define DMA_NB_CHANNELS              (0x10U)
#endif

/**
@brief Mask used to select the DMA controller for a given channel
*/
#define DMA_CTRL_MAX_CHANNELS_MASK       (0x3FU)

/**
@brief Define to identify max number of channels per DMA controller
*/
#define DMA_CTRL_MAX_CHANNELS            (0x40U)


/*lint -save -e961 */
#if (DMA_NB_CONTROLLERS == 2U)
    /**
    @brief Macro to get the DMA Module address by module index.
    @note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined -
       See @ref Reg_eSys_DMA_REF_1
    */
    #define DMA_MOD_BASE_ADDR(mIdx) \
        (uint32)(((mIdx)>0U) ? DMAB_BASEADDR : DMAA_BASEADDR)
    /**
    @brief macro to get the DMA Module base address by channel
    @note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined -
       See @ref Reg_eSys_DMA_REF_1
    */
    #define DMA_MOD_BASE_ADDR_CH(channel) \
        (uint32)(DMA_MOD_BASE_ADDR(channel & ((uint8)(~DMA_CTRL_MAX_CHANNELS_MASK))))
    /**
    @brief macro to get the DMA Module index by channel
    @note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined -
       See @ref Reg_eSys_DMA_REF_1
    */
    #define DMA_MOD_IDX(channel) \
        (uint8)(((channel & ((uint8)(~DMA_CTRL_MAX_CHANNELS_MASK)))>0U)? 1U : 0U)
#else
    /**
    @brief macro to get the DMA Module address by module index
    */
    #define DMA_MOD_BASE_ADDR(mIdx)         (uint32)(DMA_BASEADDR)
     /**
    @brief macro to get the DMA Module base address by channel
    */
    #define DMA_MOD_BASE_ADDR_CH(channel)   (uint32)(DMA_BASEADDR)
    /**
    @brief macro to get the DMA Module index by channel
    */
    #define DMA_MOD_IDX(channel)            (uint8)(0U)
#endif

/**
@brief Macro to get the DMA Registers's address by DMA index (begin section)
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined -
   See @ref Reg_eSys_DMA_REF_1
*/

/*lint -save -e961*/
#define DMA_CR(mIdx)        (uint32)( DMA_MOD_BASE_ADDR(mIdx))
#define DMA_ES(mIdx)        (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000004UL )
#define DMA_ERQH(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000008UL )
#define DMA_ERQL(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000000CUL )
#define DMA_EEIH(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000010UL )
#define DMA_EEIL(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000014UL )

#define DMA_SERQ(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000018UL )
#define DMA_CERQ(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000019UL )
#define DMA_SEEI(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000001AUL )
#define DMA_CEEI(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000001BUL )
#define DMA_CINT(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000001CUL )
#define DMA_CERR(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000001DUL )
#define DMA_SSRT(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000001EUL )
#define DMA_CDNE(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000001FUL )

#define DMA_INTH(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000020UL )
#define DMA_INTL(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000024UL )
#define DMA_EERH(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000028UL )
#define DMA_EERL(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000002CUL )
#define DMA_HRSH(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000030UL )
#define DMA_HRSL(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000034UL )
#define DMA_GPOR(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000038UL )

#define DMA_CPR0(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000100UL )
#define DMA_CPR1(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000101UL )
#define DMA_CPR2(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000102UL )
#define DMA_CPR3(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000103UL )
#define DMA_CPR4(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000104UL )
#define DMA_CPR5(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000105UL )
#define DMA_CPR6(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000106UL )
#define DMA_CPR7(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000107UL )
#define DMA_CPR8(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000108UL )
#define DMA_CPR9(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000109UL )
#define DMA_CPR10(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000010AUL )
#define DMA_CPR11(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000010BUL )
#define DMA_CPR12(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000010CUL )
#define DMA_CPR13(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000010DUL )
#define DMA_CPR14(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000010EUL )
#define DMA_CPR15(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000010FUL )
#define DMA_CPR16(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000110UL )
#define DMA_CPR17(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000111UL )
#define DMA_CPR18(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000112UL )
#define DMA_CPR19(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000113UL )
#define DMA_CPR20(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000114UL )
#define DMA_CPR21(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000115UL )
#define DMA_CPR22(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000116UL )
#define DMA_CPR23(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000117UL )
#define DMA_CPR24(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000118UL )
#define DMA_CPR25(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000119UL )
#define DMA_CPR26(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000011AUL )
#define DMA_CPR27(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000011BUL )
#define DMA_CPR28(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000011CUL )
#define DMA_CPR29(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000011DUL )
#define DMA_CPR30(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000011EUL )
#define DMA_CPR31(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000011FUL )
#define DMA_CPR32(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000120UL )
#define DMA_CPR33(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000121UL )
#define DMA_CPR34(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000122UL )
#define DMA_CPR35(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000123UL )
#define DMA_CPR36(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000124UL )
#define DMA_CPR37(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000125UL )
#define DMA_CPR38(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000126UL )
#define DMA_CPR39(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000127UL )
#define DMA_CPR40(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000128UL )
#define DMA_CPR41(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000129UL )
#define DMA_CPR42(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000012AUL )
#define DMA_CPR43(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000012BUL )
#define DMA_CPR44(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000012CUL )
#define DMA_CPR45(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000012DUL )
#define DMA_CPR46(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000012EUL )
#define DMA_CPR47(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000012FUL )
#define DMA_CPR48(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000130UL )
#define DMA_CPR49(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000131UL )
#define DMA_CPR50(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000132UL )
#define DMA_CPR51(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000133UL )
#define DMA_CPR52(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000134UL )
#define DMA_CPR53(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000135UL )
#define DMA_CPR54(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000136UL )
#define DMA_CPR55(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000137UL )
#define DMA_CPR56(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000138UL )
#define DMA_CPR57(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00000139UL )
#define DMA_CPR58(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000013AUL )
#define DMA_CPR59(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000013BUL )
#define DMA_CPR60(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000013CUL )
#define DMA_CPR61(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000013DUL )
#define DMA_CPR62(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000013EUL )
#define DMA_CPR63(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x0000013FUL )

#define DMA_TCD0(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001000UL )
#define DMA_TCD1(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001020UL )
#define DMA_TCD2(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001040UL )
#define DMA_TCD3(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001060UL )
#define DMA_TCD4(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001080UL )
#define DMA_TCD5(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x000010A0UL )
#define DMA_TCD6(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x000010C0UL )
#define DMA_TCD7(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x000010E0UL )
#define DMA_TCD8(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001100UL )
#define DMA_TCD9(mIdx)      (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001120UL )
#define DMA_TCD10(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001140UL )
#define DMA_TCD11(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001160UL )
#define DMA_TCD12(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001180UL )
#define DMA_TCD13(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x000011A0UL )
#define DMA_TCD14(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x000011C0UL )
#define DMA_TCD15(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x000011E0UL )
#define DMA_TCD16(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001200UL )
#define DMA_TCD17(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001220UL )
#define DMA_TCD18(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001240UL )
#define DMA_TCD19(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001260UL )
#define DMA_TCD20(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001280UL )
#define DMA_TCD21(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x000012A0UL )
#define DMA_TCD22(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x000012C0UL )
#define DMA_TCD23(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x000012E0UL )
#define DMA_TCD24(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001300UL )
#define DMA_TCD25(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001320UL )
#define DMA_TCD26(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001340UL )
#define DMA_TCD27(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001360UL )
#define DMA_TCD28(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001380UL )
#define DMA_TCD29(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x000013A0UL )
#define DMA_TCD30(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x000013C0UL )
#define DMA_TCD31(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x000013E0UL )
#define DMA_TCD32(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001400UL )
#define DMA_TCD33(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001420UL )
#define DMA_TCD34(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001440UL )
#define DMA_TCD35(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001460UL )
#define DMA_TCD36(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001480UL )
#define DMA_TCD37(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x000014A0UL )
#define DMA_TCD38(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x000014C0UL )
#define DMA_TCD39(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x000014E0UL )
#define DMA_TCD40(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001500UL )
#define DMA_TCD41(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001520UL )
#define DMA_TCD42(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001540UL )
#define DMA_TCD43(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001560UL )
#define DMA_TCD44(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001580UL )
#define DMA_TCD45(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x000015A0UL )
#define DMA_TCD46(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x000015C0UL )
#define DMA_TCD47(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x000015E0UL )
#define DMA_TCD48(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001600UL )
#define DMA_TCD49(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001620UL )
#define DMA_TCD50(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001640UL )
#define DMA_TCD51(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001660UL )
#define DMA_TCD52(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001680UL )
#define DMA_TCD53(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x000016A0UL )
#define DMA_TCD54(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x000016C0UL )
#define DMA_TCD55(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x000016E0UL )
#define DMA_TCD56(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001700UL )
#define DMA_TCD57(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001720UL )
#define DMA_TCD58(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001740UL )
#define DMA_TCD59(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001760UL )
#define DMA_TCD60(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x00001780UL )
#define DMA_TCD61(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x000017A0UL )
#define DMA_TCD62(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x000017C0UL )
#define DMA_TCD63(mIdx)     (uint32)( DMA_MOD_BASE_ADDR(mIdx) + 0x000017E0UL )
/**
@brief Macro to get the DMA Registers's address by DMA index (end section)
@note  All the above macros are violating the MISRA rule 19.7,Function-like macro defined -
   See @ref Reg_eSys_DMA_REF_1
*/
/*lint -restore*/
/**
@brief Task control block address offset
*/
#define DMA_TCD_OFFSET     ((uint32) (0x1000UL))
/**
@brief Channel priority block address offset
*/
#define DMA_CPT_OFFSET     ((uint32) (0x0100UL))
/**
@brief Offset to Source address in TCD - Transfer Control Descriptor structure.
*/
#define DMA_TCD_SADDR_OFFSET        ((uint32) 0x00UL)
/**
@brief Offset to smod, ssize, dmod, dsize, soff fields in TCD-Transfer Control Descriptor structure.
*/
#define DMA_TCD_TA_SOFF_OFFSET      ((uint32) 0x04UL)
/**
@brief Offset to smloe, dmloe, mloff, nbytes fields in TCD - Transfer Control Descriptor structure.
*/
#define DMA_TCD_SMLO_NBTYES_OFFSET  ((uint32) 0x08UL)
/**
@brief Offset to slast field in TCD - Transfer Control Descriptor structure.
*/
#define DMA_TCD_SLAST_OFFSET        ((uint32) 0x0CUL)
/**
@brief Offset to destination address field in TCD - Transfer Control Descriptor structure.
*/
#define DMA_TCD_DADDR_OFFSET        ((uint32) 0x10UL)
/**
@brief Offset to citer, doff fields in TCD - Transfer Control Descriptor structure.
*/
#define DMA_TCD_CITER_DOFF_OFFSET   ((uint32) 0x14UL)
/**
@brief Offset to dlast_sga field in TCD - Transfer Control Descriptor structure.
*/
#define DMA_TCD_DLAST_SGA_OFFSET    ((uint32) 0x18UL)
/**
@brief Offset to biter, channle control/status fields in TCD - Transfer Control Descriptor structure
*/
#define DMA_TCD_BITER_CCS_OFFSET    ((uint32) 0x1CUL)

/**
@brief TCD Fields's address.
*/
#define DMA_TCD_DONE            (0x00000080U)
#define DMA_TCD_ACTIVE          (0x00000040U)
#define DMA_TCD_MAJOR_E_LINK    (0x00000020U)
#define DMA_TCD_SGA             (0x00000010U)
#define DMA_TCD_DISABLE_REQ     (0x00000008U)
#define DMA_TCD_INT_HALF        (0x00000004U)
#define DMA_TCD_INT_MAJOR       (0x00000002U)
#define DMA_TCD_START           (0x00000001U)

/**
@brief TCD Fields's masks.
*/
#define DMA_TCD_MINOR_E_LINK_MASK   ((uint32) 0xFE000000U)
#define DMA_TCD_MINOR_ITER_MASK     ((uint32) 0x01FF0000U)
#define DMA_TCD_MINOR_DOFF_MASK     ((uint32) 0x0000FFFFU)
#define DMA_TCD_MINOR_SOFF_MASK     ((uint32) 0x0000FFFFU)

/**
@brief For DMA TCDs which do not use e_link field, major loop iteration count
       is on 15 bits.
 */
#define DMA_MAX_UNLINKED_ITER_CNT   (0x7FFFu)
/**
@brief For DMA TCDs using e_link field, major loop iteration count is on 9 bits
 */
#define DMA_MAX_LINKED_ITER_CNT     ((uint16) (0x1FFU))

/**
@brief Low Level Macros used to access DMA registers for read/write operations.
@note  Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined -
   See @ref Reg_eSys_DMA_REF_1
*/
/*lint -save -e961*/
#define DMA_TCD_SIZE        (0x20u)
#define DMA_CPR(Channel) \
    (uint32)(DMA_MOD_BASE_ADDR_CH(Channel) + DMA_CPT_OFFSET + \
    ((uint32)Channel & DMA_CTRL_MAX_CHANNELS_MASK))
#define DMA_TCD(Channel) \
    (uint32)(DMA_MOD_BASE_ADDR_CH(Channel) + DMA_TCD_OFFSET + \
    (((uint32)Channel & DMA_CTRL_MAX_CHANNELS_MASK)<<5))
#define DMA_TCD_CHANNEL(Channel, Offset) (uint32)(DMA_TCD(Channel) + Offset)
#define DMA_TCD_SR(Channel) \
    (*(volatile uint32*)(DMA_TCD_CHANNEL(Channel, DMA_TCD_BITER_CCS_OFFSET)))
#define LLM_Wr_DMA_SERQ(channel) \
    REG_WRITE8(DMA_SERQ(DMA_MOD_IDX(channel)), (channel & DMA_CTRL_MAX_CHANNELS_MASK))
#define LLM_Wr_DMA_CDNE(channel) \
    REG_WRITE8(DMA_CDNE(DMA_MOD_IDX(channel)), (channel & DMA_CTRL_MAX_CHANNELS_MASK))
#define LLM_Wr_DMA_SSRT(channel) \
    REG_WRITE8(DMA_SSRT(DMA_MOD_IDX(channel)), (channel & DMA_CTRL_MAX_CHANNELS_MASK))
#define LLM_Wr_DMA_CINT(channel) \
    REG_WRITE8(DMA_CINT(DMA_MOD_IDX(channel)), (channel & DMA_CTRL_MAX_CHANNELS_MASK))
#define LLM_Wr_DMA_SERQ_IDX(mIdx,value) REG_WRITE8(DMA_SERQ(mIdx), (value))
#define LLM_Wr_DMA_CDNE_IDX(mIdx,value) REG_WRITE8(DMA_CDNE(mIdx), (value))
#define LLM_Wr_DMA_SSRT_IDX(mIdx,value) REG_WRITE8(DMA_SSRT(mIdx), (value))
#define LLM_Wr_DMA_CINT_IDX(mIdx,value) REG_WRITE8(DMA_CINT(mIdx), (value))
#define LLM_Wr_DMA_TCD_DADDR(Channel, dest_addr) \
   REG_WRITE32(DMA_TCD(Channel) + DMA_TCD_DADDR_OFFSET, dest_addr)
#define LLM_Wr_DMA_TCD_SADDR(Channel, src_addr) \
   REG_WRITE32(DMA_TCD(Channel) + DMA_TCD_SADDR_OFFSET, src_addr)
#define LLM_Rd_DMA_INTH(mIdx)           REG_READ32(DMA_INTH(mIdx))
#define LLM_Rd_DMA_INTL(mIdx)           REG_READ32(DMA_INTL(mIdx))
/**
@brief Low Level Macros for TCD fields access
*/
#define LLM_Wr_DMA_TCDADDR_SADDR(TcdAddr, src_addr) \
   REG_WRITE32((uint32)(TcdAddr) + DMA_TCD_SADDR_OFFSET, (uint32)(src_addr))
#define LLM_Wr_DMA_TCDADDR_DADDR(TcdAddr, dest_addr) \
   REG_WRITE32((uint32)(TcdAddr) + DMA_TCD_DADDR_OFFSET, (uint32)(dest_addr))
#define LLM_Wr_DMA_TCDADDR_SOFF(TcdAddr, src_off) \
   REG_WRITE16((uint32)(TcdAddr) + DMA_TCD_TA_SOFF_OFFSET + 2u, (uint16)(src_off))
#define LLM_Wr_DMA_TCDADDR_CITER_DOFF(TcdAddr, link_iter_doff) \
   REG_WRITE32((uint32)(TcdAddr) + DMA_TCD_CITER_DOFF_OFFSET, (uint32)(link_iter_doff))
#define LLM_Wr_DMA_TCDADDR_CITER(TcdAddr, link_iter) \
   REG_WRITE16((uint32)(TcdAddr) + DMA_TCD_CITER_DOFF_OFFSET, (uint16)(link_iter))
#define LLM_Wr_DMA_TCDADDR_BITER(TcdAddr, link_iter) \
   REG_WRITE16((uint32)(TcdAddr) + DMA_TCD_BITER_CCS_OFFSET, (uint16)(link_iter))
#define LLM_Wr_DMA_TCDADDR_DLAST_SGA(TcdAddr, dlast_sg_addr) \
   REG_WRITE32((uint32)(TcdAddr) + DMA_TCD_DLAST_SGA_OFFSET, (uint32)(dlast_sg_addr))
#define LLM_Wr_DMA_TCDADDR_FLAGS(TcdAddr, flags) \
   REG_WRITE8((uint32)(TcdAddr) + DMA_TCD_BITER_CCS_OFFSET + 3u, (uint8)(flags))
#define LLM_Rd_DMA_TCDADDR_FLAGS(TcdAddr) \
   REG_READ8((uint32)(TcdAddr) + DMA_TCD_BITER_CCS_OFFSET + 3u)
#define LLM_Set_DMA_TCDADDR_INT(TcdAddr) \
    REG_BIT_SET32((uint32)(TcdAddr) + DMA_TCD_BITER_CCS_OFFSET, \
        (uint32)(DMA_TCD_INT_MAJOR))
#define LLM_Clear_DMA_TCDADDR_INT(TcdAddr) \
    REG_BIT_CLEAR32((uint32)(TcdAddr) + DMA_TCD_BITER_CCS_OFFSET, \
        (uint32)(DMA_TCD_INT_MAJOR))
#define LLM_Get_DMA_Status(Channel) \
   REG_BIT_GET32(DMA_TCD_CHANNEL(Channel, (uint32) DMA_TCD_BITER_CCS_OFFSET), BIT7)
/**
@brief Low Level Macros used to access DMA registers for read/write operations (end section)
@note  All the above macros are violating the MISRA rule 19.7,Function-like macro defined -
   See @ref Reg_eSys_DMA_REF_1
*/
/*lint -restore */

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/**
@brief   Dma Transfer Control Descriptor related types.
*/
typedef VAR(uint8, AUTOMATIC) DmaTcdType[DMA_TCD_SIZE];
typedef P2VAR(uint8, AUTOMATIC, AUTOMATIC) DmaTcdPointerType;

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /*_REG_ESYS_DMA_H_*/
