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
[!INCLUDE "Wdg_VersionCheck_Src.m"!][!//
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
[!NOCODE!]
[!VAR "MS_TO_S" = "1000"!]
[!ENDNOCODE!]
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
           ( SWT_WDG_DISABLED | SWT_WDG_NO_HARD_LOCK| [!IF "WdgModeConfig/*[1]/WdgSettingsOff/WdgReadOnly"!]SWT_WDG_SOFT_LOCK[!ELSE!]SWT_WDG_NO_SOFT_LOCK[!ENDIF!]),[!//

           0x00000000UL, /* Time-out config */
           0x00000000UL  /* Window config */
       },
       /* SLOW Mode */
       {
           ( SWT_WDG_ENABLED |SWT_WDG_NO_HARD_LOCK | [!IF "WdgModeConfig/*[1]/WdgSettingsSlow/WdgReadOnly"!]SWT_WDG_SOFT_LOCK |[!ELSE!]SWT_WDG_NO_SOFT_LOCK |[!ENDIF!][!//
     [!IF "WdgModeConfig/*[1]/WdgSettingsSlow/WdgWindowMode"!]SWT_TRIGGER_MODE_WINDOW |[!ELSE!]SWT_TRIGGER_MODE_REGULAR |[!ENDIF!][!//
     [!IF "WdgModeConfig/*[1]/WdgKeyedService"!]SWT_KEYED_SERVICE_SEQ |[!ELSE!]SWT_FIXED_SERVICE_SEQ |[!ENDIF!][!//
     [!IF "WdgModeConfig/*[1]/WdgSettingsSlow/WdgRunsInStopMode"!]SWT_WDG_RUN_IN_HALT |[!ELSE!]SWT_WDG_STOP_IN_HALT |[!ENDIF!][!//
     [!IF "WdgModeConfig/*[1]/WdgSettingsSlow/WdgRunsInDebugMode"!]SWT_WDG_RUN_IN_DEBUG |[!ELSE!]SWT_WDG_STOP_IN_DEBUG |[!ENDIF!][!//
     [!IF "WdgModeConfig/*[1]/WdgSettingsSlow/WdgClockSelection = 'OscillatorClock'"!]SWT_WDG_OSCILLATOR |[!ELSE!]  SWT_WDG_SYSTEM_CLOCK |[!ENDIF!][!//
     [!IF "WdgModeConfig/*[1]/WdgSettingsSlow/WdgOperationMode = 'Interrupt'"!]SWT_INTERRUPT_TOGGLE|[!ELSE!][!//
     [!IF "WdgModeConfig/*[1]/WdgSettingsSlow/WdgOperationMode = 'ResetOnTimeOut'"!]SWT_RESET_ON_TIMEOUT |[!ENDIF!][!ENDIF!][!//
     [!IF "WdgModeConfig/*[1]/WdgSettingsSlow/WdgResetOnInvalidAccess = 'BusError'"!]SWT_INVALID_ACCESS_GEN_BUS_ERROR[!ELSE!][!//
     [!IF "WdgModeConfig/*[1]/WdgSettingsSlow/WdgResetOnInvalidAccess = 'SystemReset'"!]SWT_INVALID_ACCESS_GEN_SYSTEM_RESET[!ENDIF!][!ENDIF!][!//
      ), /* WDG Control and configuration */
           [!"num:inttohex(WdgModeConfig/*[1]/WdgSettingsSlow/WdgTimeoutPeriod ,8)"!]UL,  /* Time-out config */
           [!"num:inttohex(WdgModeConfig/*[1]/WdgSettingsSlow/WdgWindowPeriod ,8)"!]UL   /* Window config */
       },
       /* FAST Mode */
       {
           ( SWT_WDG_ENABLED | SWT_WDG_NO_HARD_LOCK | [!IF "WdgModeConfig/*[1]/WdgSettingsFast/WdgReadOnly"!]SWT_WDG_SOFT_LOCK |[!ELSE!]SWT_WDG_NO_SOFT_LOCK |[!ENDIF!][!//
     [!IF "WdgModeConfig/*[1]/WdgSettingsFast/WdgWindowMode"!]SWT_TRIGGER_MODE_WINDOW |[!ELSE!]SWT_TRIGGER_MODE_REGULAR |[!ENDIF!][!//
     [!IF "WdgModeConfig/*[1]/WdgKeyedService"!]SWT_KEYED_SERVICE_SEQ |[!ELSE!]SWT_FIXED_SERVICE_SEQ |[!ENDIF!][!//
     [!IF "WdgModeConfig/*[1]/WdgSettingsFast/WdgRunsInStopMode"!]SWT_WDG_RUN_IN_HALT |[!ELSE!]SWT_WDG_STOP_IN_HALT |[!ENDIF!][!//
     [!IF "WdgModeConfig/*[1]/WdgSettingsFast/WdgRunsInDebugMode"!]SWT_WDG_RUN_IN_DEBUG |[!ELSE!]SWT_WDG_STOP_IN_DEBUG |[!ENDIF!][!//
     [!IF "WdgModeConfig/*[1]/WdgSettingsFast/WdgClockSelection = 'OscillatorClock'"!]SWT_WDG_OSCILLATOR |[!ELSE!]  SWT_WDG_SYSTEM_CLOCK |[!ENDIF!][!//
     [!IF "WdgModeConfig/*[1]/WdgSettingsFast/WdgOperationMode = 'Interrupt'"!]SWT_INTERRUPT_TOGGLE|[!ELSE!][!//
     [!IF "WdgModeConfig/*[1]/WdgSettingsFast/WdgOperationMode = 'ResetOnTimeOut'"!]SWT_RESET_ON_TIMEOUT |[!ENDIF!][!ENDIF!][!//
     [!IF "WdgModeConfig/*[1]/WdgSettingsFast/WdgResetOnInvalidAccess = 'BusError'"!]SWT_INVALID_ACCESS_GEN_BUS_ERROR[!ELSE!][!//
     [!IF "WdgModeConfig/*[1]/WdgSettingsFast/WdgResetOnInvalidAccess = 'SystemReset'"!]SWT_INVALID_ACCESS_GEN_SYSTEM_RESET[!ENDIF!][!ENDIF!][!//
      ), /* WDG Control and configuration */
           [!"num:inttohex(WdgModeConfig/*[1]/WdgSettingsFast/WdgTimeoutPeriod ,8)"!]UL,  /* Time-out config */
           [!"num:inttohex(WdgModeConfig/*[1]/WdgSettingsFast/WdgWindowPeriod ,8)"!]UL   /* Window config */
        }
    },
    [!IF "WdgModeConfig/*[1]/WdgDefaultMode = 'FastMode'"!]WDGIF_FAST_MODE[!ELSE!][!IF "WdgModeConfig/*[1]/WdgDefaultMode = 'OffMode'"!]WDGIF_OFF_MODE[!ELSE!][!IF "WdgModeConfig/*[1]/WdgDefaultMode = 'SlowMode'"!]WDGIF_SLOW_MODE[!ENDIF!][!ENDIF!][!ENDIF!],
    [!IF "WdgModeConfig/*[1]/WdgKeyedService"!]WDG_KEYED_SERVICE[!ELSE!]WDG_FIXED_SERVICE[!ENDIF!],
    (Wdg_ServiceKeyWidthType)[!"WdgModeConfig/*[1]/WdgServiceKeyValue"!]
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