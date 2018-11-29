/*!
 * @file    Wdg_LCfg.c
 * @version 2.0.0
 * 
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

[!INCLUDE "Wdg_VersionCheck_Src_LT.m"!][!//
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

/* Check if source file and WDG header file are of the same vendor */
#if (WDG_VENDOR_ID_CFG_C != WDG_VENDOR_ID)
    #error "Wdg_LCfg.c and Wdg.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and WDG header file are of the same Autosar version */
    #if ((WDG_AR_MAJOR_VERSION_CFG_C != WDG_AR_MAJOR_VERSION) || \
         (WDG_AR_MINOR_VERSION_CFG_C != WDG_AR_MINOR_VERSION) || \
         (WDG_AR_PATCH_VERSION_CFG_C != WDG_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of Wdg_LCfg.c and Wdg.h are different"
    #endif
#endif
/* Check if source file and WDG header file are of the same Software version */
#if ((WDG_SW_MAJOR_VERSION_CFG_C != WDG_SW_MAJOR_VERSION) || \
     (WDG_SW_MINOR_VERSION_CFG_C != WDG_SW_MINOR_VERSION) || \
     (WDG_SW_PATCH_VERSION_CFG_C != WDG_SW_PATCH_VERSION))
    #error "Software Version Numbers of Wdg_LCfg.c and Wdg.h are different"
#endif

#if (WDG_TYPE == WDG_INTERNAL_MODULE)
    /* Check if source file and Reg_eSys_SWT file are of the same vendor */
    #if (WDG_VENDOR_ID_CFG_C != REG_ESYS_SWT_VENDOR_ID)
        #error "Wdg_LCfg.c and Reg_eSys_SWT.h have different vendor ids"
    #endif
    /* Check if source file and Reg_eSys_SWT header file are of the same Autosar version */
    #ifdef CHECK_AUTOSAR_VERSION
        #if ((WDG_AR_MAJOR_VERSION_CFG_C != REG_ESYS_SWT_AR_MAJOR_VERSION) || \
             (WDG_AR_MINOR_VERSION_CFG_C != REG_ESYS_SWT_AR_MINOR_VERSION) || \
             (WDG_AR_PATCH_VERSION_CFG_C != REG_ESYS_SWT_AR_PATCH_VERSION))
            #error "AutoSar Version Numbers of Wdg_LCfg.c and Reg_eSys_SWT.h are different"
        #endif
    #endif
    /* Check if source file and Reg_eSys_SWT file are of the same Software version */
    #if ((WDG_SW_MAJOR_VERSION_CFG_C != REG_ESYS_SWT_SW_MAJOR_VERSION) || \
         (WDG_SW_MINOR_VERSION_CFG_C != REG_ESYS_SWT_SW_MINOR_VERSION) || \
         (WDG_SW_PATCH_VERSION_CFG_C != REG_ESYS_SWT_SW_PATCH_VERSION))
        #error "Software Version Numbers of Wdg_LCfg.c and Reg_eSys_SWT.h are different"
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


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/
/* For the current implementation the file has no parameters. The parameter available
 * at link time are the reference to the external driver - N/A */

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