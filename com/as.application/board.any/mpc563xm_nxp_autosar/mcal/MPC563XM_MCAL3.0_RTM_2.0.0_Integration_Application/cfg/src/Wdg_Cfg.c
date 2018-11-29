/*!
 * @file    Wdg_Cfg.c
 * @version 2.0.0
 * @brief   AUTOSAR Wdg - contains the data exported by the watchodg module
 * @details Contains the information that will be exported by the module, as requested by Autosar.
 *
 * @addtogroup  Wdg
 * @{
 */

/************************************************************************
 * PROJECT              AUTOSAR 3.0 MCAL
 * PLATFORM             PA
 * PERIPHERAL           Swt
 * DEPENDENCIES         none
 *
 * AUTOSAR VERSION      3.0.0
 * AUTOSAR REVISION     ASR_REL_3_0_REV_0003
 * AUTOSAR CONF.VARIANT
 *
 * SW VERSION           2.0.0
 * BUILDVERSION         XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223
 *
 * COPYRIGHT : (c)      2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
 *                      ALL RIGHTS RESERVED
 **************************************************************************/
/*==================================================================================================
==================================================================================================*/

/*
 * @page misra_violations MISRA-C:2004 violations
 *
 * @section Wdg_Cfg_c_REF_1
 * Violates  MISRA  2004 Advisory  Rule  19.1,  only preprocessor statements and comments before '#include'
 * This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement MEMMAP003.
 *
 * @section Wdg_Cfg_c_REF_2
 * Violates  MISRA  2004 Required Rule 19.15,  Precaution shall be taken in order to prevent the
 * contents of a header file being included twice.
 * This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement MEMMAP003.
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
#include "Wdg.h"
#if (WDG_TYPE == WDG_INTERNAL_MODULE)
    #include "Reg_eSys_SWT.h"
#endif

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/* @remarks Covers BSW00374, BSW00318 */
#define WDG_VENDOR_ID_CFG_C         43
#define WDG_AR_MAJOR_VERSION_CFG_C  3
#define WDG_AR_MINOR_VERSION_CFG_C  0
#define WDG_AR_PATCH_VERSION_CFG_C  0
#define WDG_SW_MAJOR_VERSION_CFG_C  2
#define WDG_SW_MINOR_VERSION_CFG_C  0
#define WDG_SW_PATCH_VERSION_CFG_C  0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* @remarks Covers WDG087 */
/* Check if source file and WDG header file are of the same vendor */
#if (WDG_VENDOR_ID_CFG_C != WDG_VENDOR_ID)
    #error "Wdg_Cfg.c and Wdg.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Wdg_Cfg header file are of the same Autosar version */
    #if ((WDG_AR_MAJOR_VERSION_CFG_C != WDG_AR_MAJOR_VERSION) || \
         (WDG_AR_MINOR_VERSION_CFG_C != WDG_AR_MINOR_VERSION) || \
         (WDG_AR_PATCH_VERSION_CFG_C != WDG_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of Wdg_Cfg.c and Wdg.h are different"
    #endif
#endif
/* Check if source file and wdg_cfg file are of the same Software version */
#if ((WDG_SW_MAJOR_VERSION_CFG_C != WDG_SW_MAJOR_VERSION) || \
     (WDG_SW_MINOR_VERSION_CFG_C != WDG_SW_MINOR_VERSION) || \
     (WDG_SW_PATCH_VERSION_CFG_C != WDG_SW_PATCH_VERSION))
    #error "Software Version Numbers of Wdg_Cfg.c and Wdg.h are different"
#endif

#if (WDG_TYPE == WDG_INTERNAL_MODULE)
    /* Check if source file and Reg_eSys_SWT file are of the same vendor */
    #if (WDG_VENDOR_ID_CFG_C != REG_ESYS_SWT_VENDOR_ID)
        #error "Wdg_Cfg.c and Reg_eSys_SWT.h have different vendor ids"
    #endif
    #ifdef CHECK_AUTOSAR_VERSION
        /* Check if source file and Reg_eSys_SWT header file are of the same Autosar version */
        #if ((WDG_AR_MAJOR_VERSION_CFG_C != REG_ESYS_SWT_AR_MAJOR_VERSION) || \
             (WDG_AR_MINOR_VERSION_CFG_C != REG_ESYS_SWT_AR_MINOR_VERSION) || \
             (WDG_AR_PATCH_VERSION_CFG_C != REG_ESYS_SWT_AR_PATCH_VERSION))
            #error "AutoSar Version Numbers of Wdg_Cfg.c and Reg_eSys_SWT.h are different"
        #endif
    #endif
    /* Check if source file and Reg_eSys_SWT file are of the same Software version */
    #if ((WDG_SW_MAJOR_VERSION_CFG_C != REG_ESYS_SWT_SW_MAJOR_VERSION) || \
         (WDG_SW_MINOR_VERSION_CFG_C != REG_ESYS_SWT_SW_MINOR_VERSION) || \
         (WDG_SW_PATCH_VERSION_CFG_C != REG_ESYS_SWT_SW_PATCH_VERSION))
        #error "Software Version Numbers of Wdg_Cfg.c and Reg_eSys_SWT.h are different"
    #endif
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
#define WDG_START_SEC_VAR_UNSPECIFIED
/*
 * @note Violates MISRA 2004 Required Rule 19.15,Precaution shall be taken in order to prevent the
 *       contents of a header file being included twice. - See @ref Wdg_Cfg_c_REF_2
*/
/* lint -save -e537 -e451*/
#include "MemMap.h"
/* lint -restore*/

#ifdef WDG_PRECOMPILE_SUPPORT


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/

/*
 * @brief  This constant contains the configuration set for the precompile time
 * @remarks Covers WDG051
 * @remarks Implements DWDG05002, DWDG01002
*/
CONST(Wdg_ConfigType, WDG_CONST) Wdg_ConfigPC =
{
    {
       /* OFF Mode */
       {
           ( SWT_WDG_DISABLED | SWT_WDG_NO_HARD_LOCK| SWT_WDG_NO_SOFT_LOCK),
           0x00000000UL, /* Time-out config */
           0x00000000UL  /* Window config */
       },
       /* SLOW Mode */
       {
           ( SWT_WDG_ENABLED |SWT_WDG_NO_HARD_LOCK | SWT_WDG_NO_SOFT_LOCK |     SWT_TRIGGER_MODE_REGULAR |     SWT_FIXED_SERVICE_SEQ |     SWT_WDG_STOP_IN_HALT |     SWT_WDG_STOP_IN_DEBUG |     SWT_WDG_OSCILLATOR |     SWT_INTERRUPT_TOGGLE|     SWT_INVALID_ACCESS_GEN_BUS_ERROR      ), /* WDG Control and configuration */
           0x01000000UL,  /* Time-out config */
           0x00000000UL   /* Window config */
       },
       /* FAST Mode */
       {
           ( SWT_WDG_ENABLED | SWT_WDG_NO_HARD_LOCK | SWT_WDG_NO_SOFT_LOCK |     SWT_TRIGGER_MODE_REGULAR |     SWT_FIXED_SERVICE_SEQ |     SWT_WDG_STOP_IN_HALT |     SWT_WDG_STOP_IN_DEBUG |     SWT_WDG_OSCILLATOR |     SWT_INTERRUPT_TOGGLE|     SWT_INVALID_ACCESS_GEN_BUS_ERROR      ), /* WDG Control and configuration */
           0x01000000UL,  /* Time-out config */
           0x00000000UL   /* Window config */
        }
    },
    WDGIF_SLOW_MODE,
    WDG_FIXED_SERVICE,
    (Wdg_ServiceKeyWidthType)0
};

#endif
#define WDG_STOP_SEC_VAR_UNSPECIFIED
/*
 * @note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
 *       before '#include' - See @ref Wdg_Cfg_c_REF_1
 *
 * @note Violates MISRA 2004 Required Rule 19.15,Precaution shall be taken in order to prevent the
 *       contents of a header file being included twice. - See @ref Wdg_Cfg_c_REF_2
*/
/* lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/* lint -restore */

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
/** @} */
