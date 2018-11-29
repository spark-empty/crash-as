/**
    @file    Icu_PBCfg.c
    @version 2.0.0

    @brief   AUTOSAR Icu - contains the data exported by the Icu module
    @details Contains the information that will be exported by the module, as requested by Autosar.


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

/**
@page misra_violations MISRA-C:2004 violations

@section Icu_PBcfg_c_1
Violates MISRA-C 2004 Advisory Rule 19.1, "#include" preceded by non preproc directives.
This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement
MEMMAP003.

@section Icu_PBcfg_c_2
Violates MISRA-C 2004 Advisory Rule 19.15, Precautions shall be taken in order to prevent
the contents of a header file being included twice
This is not a violation since all header files are protected against multiple inclusions
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
#include "Icu.h"
#include "Icu_LLD.h"


/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/**
@{
@brief   Configuration source file version information
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define ICU_VENDOR_ID_PBCFG_C         43
#define ICU_AR_MAJOR_VERSION_PBCFG_C  3
#define ICU_AR_MINOR_VERSION_PBCFG_C  0
#define ICU_AR_PATCH_VERSION_PBCFG_C  0
#define ICU_SW_MAJOR_VERSION_PBCFG_C  2
#define ICU_SW_MINOR_VERSION_PBCFG_C  0
#define ICU_SW_PATCH_VERSION_PBCFG_C  0
/**@}*/
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/** @remarks Covers ICU005 */
/* Check Icu_PBCfg.c against Icu.h file versions */
#if (ICU_VENDOR_ID_PBCFG_C != ICU_VENDOR_ID)
    #error "Icu_PBcfg.c and Icu.h have different vendor IDs"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((ICU_AR_MAJOR_VERSION_PBCFG_C != ICU_AR_MAJOR_VERSION) || \
         (ICU_AR_MINOR_VERSION_PBCFG_C != ICU_AR_MINOR_VERSION) || \
         (ICU_AR_PATCH_VERSION_PBCFG_C != ICU_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Icu_PBcfg.c and Icu.h are different"
    #endif
#endif
#if ((ICU_SW_MAJOR_VERSION_PBCFG_C != ICU_SW_MAJOR_VERSION) || \
     (ICU_SW_MINOR_VERSION_PBCFG_C != ICU_SW_MINOR_VERSION) || \
     (ICU_SW_PATCH_VERSION_PBCFG_C != ICU_SW_PATCH_VERSION))
#error "Software Version Numbers of Icu_PBcfg.c and Icu.h are different"
#endif

/* Check Icu_PBCfg.c against Icu_LLD.h file versions */
#if (ICU_VENDOR_ID_PBCFG_C != ICU_LLD_VENDOR_ID)
#error "Icu_PBcfg.c and Icu_LLD.h have different vendor IDs"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((ICU_AR_MAJOR_VERSION_PBCFG_C != ICU_LLD_AR_MAJOR_VERSION) || \
         (ICU_AR_MINOR_VERSION_PBCFG_C != ICU_LLD_AR_MINOR_VERSION) || \
         (ICU_AR_PATCH_VERSION_PBCFG_C != ICU_LLD_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Icu_PBCfg.c and Icu_LLD.h are different"
    #endif
#endif
#if ((ICU_SW_MAJOR_VERSION_PBCFG_C != ICU_LLD_SW_MAJOR_VERSION) || \
     (ICU_SW_MINOR_VERSION_PBCFG_C != ICU_LLD_SW_MINOR_VERSION) || \
     (ICU_SW_PATCH_VERSION_PBCFG_C != ICU_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of Icu_PBCfg.c and Icu_LLD.h are different"
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
#define ICU_START_CONFIG_DATA_UNSPECIFIED
/**
 @file  Icu_PBcfg.c
 @note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
 "#include"  See @ref Icu_PBcfg_c_1
 @note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header
 file being included twice See @ref Icu_PBcfg_c_2
*/

/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/






/**
@brief  This index relates the Icu Channel number with the respective global variable, depending on
the measurement mode Each kind of measurement mode has an array(s) in the ICU driver, this index
points to the corresponding variable within the ICU channel
 */

CONST(Icu_ChannelType,ICU_CONST) Icu_InitPBChannelIndex_0[1] = {(Icu_ChannelType)0x00};


/**
@brief  This index relates the Hardware channels with the respective ICU channel.
When an normal interrupt is asserted this index is used to locate the corresponding ICU channel
 */

CONST(Icu_ChannelType,ICU_CONST) Icu_InitPBHWMap_0[ICU_MAX_HW_CHANNELS + 1U] = {(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0x00,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF};


/**
@brief  This index relates the Wakeup pins with the respective ICU channel
When an wake up interrupt is asserted this index is used to locate the corresponding ICU channel
 */

CONST(Icu_ChannelType,ICU_CONST) Icu_InitPBHWWKMap_0[ICU_MAX_HW_CHANNELS + 1U] = {(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF,(Icu_ChannelType)0xFF};



/**@brief PostBuild Configuration */

CONST(Icu_ChannelConfigType, ICU_CONST) Icu_InitPBChannel_0[1] =
{
    /* Pwm_measure - EMIOS_0_CH_8 */
    {
         (((Icu_ParamType)ICU_RISING_EDGE << ICU_EDGE_PARAM_SHIFT) | ((Icu_ParamType)EMIOS_UC_IPWM_MODE << ICU_EMIOS_UC_MODE_PARAM_SHIFT) | ((Icu_ParamType)EMIOS_FREEZE_ENABLE << ICU_EMIOS_FREEZE_PARAM_SHIFT)| ((Icu_ParamType)EMIOS_PRESCALER_DIVIDE_4 << ICU_EMIOS_PRESCALER_PARAM_SHIFT)| ((Icu_ParamType)EMIOS_DIGITAL_FILTER_BYPASSED << ICU_EMIOS_DIG_FILTER_PARAM_SHIFT)| ((Icu_ParamType)EMIOS_BUS_INTERNAL_COUNTER << ICU_EMIOS_BUS_SELECT_PARAM_SHIFT)),
        (Icu_MeasurementModeType)ICU_MODE_SIGNAL_MEASUREMENT,
        (Icu_MeasurementSubModeType)ICU_DUTY_CYCLE,
        NULL_PTR,
#if defined(ICU_OVERFLOW_NOTIFICATION_API) && (ICU_OVERFLOW_NOTIFICATION_API == STD_ON)
        NULL_PTR,
/* ICU_OVERFLOW_NOTIFICATION_API */    
#endif  
        0U
    }
};



/**
 @brief Configured Hardware channels
@{
*/

CONST(Icu_ChannelType,ICU_VAR) Icu_ChannelId_0[1]=
{
      ICU_EMIOS_0_CH_8 
       
 };

/**@}*/

/**@brief PostBuild Configuration */

CONST(Icu_ConfigType, ICU_CONST) IcuConfigSet_0 =
{
    (Icu_ChannelType)1, /* The number of channels configured*/
    Icu_InitPBChannel_0,
    Icu_InitPBChannelIndex_0,
    Icu_ChannelId_0,
    Icu_InitPBHWMap_0,
    Icu_InitPBHWWKMap_0
};


#define ICU_STOP_CONFIG_DATA_UNSPECIFIED
/**
 @file  Icu_PBcfg.c
 @note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
 "#include"  See @ref Icu_PBcfg_c_1
 @note  Violates MISRA 2004 Advisory Rule 19.15, precautions to prevent the contents of a header
 file  being included twice See @ref Icu_PBcfg_c_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/
/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/



#ifdef __cplusplus
}
#endif


