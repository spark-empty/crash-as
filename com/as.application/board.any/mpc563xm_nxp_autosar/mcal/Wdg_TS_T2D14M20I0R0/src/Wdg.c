/*!
 * @file     Wdg.c
 *
 * @version  2.0.0
 * @brief    AUTOSAR Wdg - Contains the implementation of the Watchdog API
 * @details  It contains the layer requested by autosar. The functions are independent of
 *           hardware settings.
 *
 * @remarks  Implements DWDG01000
 *
 * @addtogroup  Wdg
 * @{
 */

/***********************************************************************
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
 *
 *************************************************************************/


/*==================================================================================================
==================================================================================================*/
/*
 * @remarks Implements DWDG01000
*/

/*
 * @page misra_violations MISRA-C:2004 violations
 * @section Wdg_c_REF_1
 *          Violates  MISRA  2004 Advisory  Rule  19.1,  only preprocessor
 *          statements and comments before '#include'. This violation  is
 *          not  fixed since  the inclusion  of MemMap.h  is as  per Autosar
 *          requirement MEMMAP003.
 * @section Wdg_c_REF_2
 *          Violates  MISRA  2004 Required Rule 19.15,  Precaution shall be
 *          taken in order to prevent the contents of a header file being
 *          included twice. This violation  is not  fixed since  the inclusion
 *          of MemMap.h  is as  per Autosar  requirement MEMMAP003.
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
/*
 * @remarks Covers WDG061
 */
#include "Wdg.h"
#include "Wdg_LLD.h"
/*
 * @remarks Covers WDG080, WDG110
 * @remarks Implements DWDG19010
 */
#include "Dem.h"
#if (WDG_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
#include "SchM_Wdg.h"

#include "Mcal.h"

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
/*
 * @brief  Parameters that shall be published within the Wdg driver header file and also in the
 *         module's description file
 * @remarks Covers BSW00374, BSW00318
 */
#define WDG_VENDOR_ID_C         43
#define WDG_AR_MAJOR_VERSION_C  3
#define WDG_AR_MINOR_VERSION_C  0
#define WDG_AR_PATCH_VERSION_C  0
#define WDG_SW_MAJOR_VERSION_C  2
#define WDG_SW_MINOR_VERSION_C  0
#define WDG_SW_PATCH_VERSION_C  0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/*
 * @remarks Covers WDG087
*/

/* Check if source file and WDG header file are of the same vendor */
#if (WDG_VENDOR_ID_C != WDG_VENDOR_ID)
    #error "Wdg.c and Wdg.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and WDG header file are of the same Autosar version */
    #if ((WDG_AR_MAJOR_VERSION_C != WDG_AR_MAJOR_VERSION) || \
         (WDG_AR_MINOR_VERSION_C != WDG_AR_MINOR_VERSION) || \
         (WDG_AR_PATCH_VERSION_C != WDG_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of Wdg.c and Wdg.h are different"
    #endif
#endif
/* Check if source file and WDG header file are of the same Software version */
#if ((WDG_SW_MAJOR_VERSION_C != WDG_SW_MAJOR_VERSION) || \
     (WDG_SW_MINOR_VERSION_C != WDG_SW_MINOR_VERSION) || \
     (WDG_SW_PATCH_VERSION_C != WDG_SW_PATCH_VERSION))
    #error "Software Version Numbers of Wdg.c and Wdg.h are different"
#endif

/* Check if source file and WDG_LLD header file are of the same vendor */
#if (WDG_VENDOR_ID_C != WDG_LLD_VENDOR_ID)
    #error "Wdg.c and Wdg_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and WDG header file are of the same Autosar version */
    #if ((WDG_AR_MAJOR_VERSION_C != WDG_LLD_AR_MAJOR_VERSION) || \
         (WDG_AR_MINOR_VERSION_C != WDG_LLD_AR_MINOR_VERSION) || \
         (WDG_AR_PATCH_VERSION_C != WDG_LLD_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of Wdg.c and Wdg_LLD.h are different"
    #endif
#endif
/* Check if source file and WDG header file are of the same Software version */
#if ((WDG_SW_MAJOR_VERSION_C != WDG_LLD_SW_MAJOR_VERSION) || \
     (WDG_SW_MINOR_VERSION_C != WDG_LLD_SW_MINOR_VERSION) || \
     (WDG_SW_PATCH_VERSION_C != WDG_LLD_SW_PATCH_VERSION))
    #error "Software Version Numbers of Wdg.c and Wdg_LLD.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Dem header file are of the same version */
    #if ((WDG_AR_MAJOR_VERSION_C != DEM_AR_MAJOR_VERSION) || \
         (WDG_AR_MINOR_VERSION_C != DEM_AR_MINOR_VERSION))
        #error "AutoSar Version Numbers of Wdg.c and Dem.h are different"
    #endif
#endif

/* Check if source file and DET header file are of the same version */
#if (WDG_DEV_ERROR_DETECT == STD_ON)
    #ifdef CHECK_AUTOSAR_VERSION
        #if ((WDG_AR_MAJOR_VERSION_C != DET_AR_MAJOR_VERSION) || \
             (WDG_AR_MINOR_VERSION_C != DET_AR_MINOR_VERSION))
            #error "AutoSar Version Numbers of Wdg.c and Det.h are different"
        #endif
    #endif
#endif

#ifdef CHECK_AUTOSAR_VERSION
    #if ((WDG_AR_MAJOR_VERSION_C != SCHM_WDG_AR_MAJOR_VERSION) || \
         (WDG_AR_MINOR_VERSION_C != SCHM_WDG_AR_MINOR_VERSION))
        #error "AutoSar Version Numbers of Wdg.c and SchM_Wdg.h are different"
    #endif
#endif


/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/
/**
 * @brief  This enumerated type will contain the watchdog driver's possible states
 *
 * @api
 * @remarks Implements DWDG01005, DWDG20000
 */
typedef enum
{
    WDG_UNINIT         = 0x00,  /**< @brief The watchdog driver is not uninitialized */
    WDG_IDLE,                   /**< @brief = 0x01 The watchdog driver is currently idle,
                                                   i.e not beeing triggered or mode changed */
    WDG_BUSY                    /**< @brief = 0x02 The watchdog driver is currently busy,
                                                   i.e triggered or switchd between modes */
} Wdg_StatusType;

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
#define WDG_START_SEC_VAR_UNSPECIFIED
/*
 * @brief Include Memory mapping specification
 * @note Violates MISRA 2004 Advisory Rule 19.1 - See @ref Wdg_c_REF_1
 * @note Violates MISRA 2004 Required Rule 19.15- See @ref Wdg_c_REF_2
 */

/*lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

#if (WDG_DEV_ERROR_DETECT == STD_ON)
/*
 *  @brief Variable that indicated the state of the driver if the WDG_DEV_ERROR_DETECT is on
 *  @remarks Implements DWDG20000
 */
STATIC VAR(Wdg_StatusType, WDG_VAR) Wdg_Status = WDG_UNINIT;
#endif

#define WDG_STOP_SEC_VAR_UNSPECIFIED
/*
 * @brief Include Memory mapping specification
 * @note Violates MISRA 2004 Advisory Rule 19.1 - See @ref Wdg_c_REF_1
 * @note Violates MISRA 2004 Required Rule 19.15- See @ref Wdg_c_REF_2
 */
/*lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/*lint -restore */
/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define WDG_START_SEC_CODE
/*
 * @brief Include Memory mapping specification
 * @note Violates MISRA 2004 Advisory Rule 19.1 - See @ref Wdg_c_REF_1
 * @note Violates MISRA 2004 Required Rule 19.15- See @ref Wdg_c_REF_2
 */
/*lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/*lint -restore */
/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

/**
 * @brief   This function initializes the WDG module.
 * @details The @p Wdg_Init function shall initialize the Wdg module and the
 *          watchdog hardware, i.e. it shall set the default watchdog mode and
 *          timeout period as provided in the configuration set.
 *
 * @param[in] ConfigPtr     Pointer to configuration set.
 *
 *@requirements    WDG064, WDG063, WDG065.
 *
 * @remarks Covers WDG064, WDG063, WDG065
 * @remarks Implements DWDG01005, DWDG14000, DWDG17000, DWDG20000, DWDG12000
 *
 * @api
 */

FUNC(void, WDG_CODE) Wdg_Init(P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr)
{
    VAR (WdgIf_ModeType, WDG_VAR)   Wdg_DefaultMode;
#if (WDG_DEV_ERROR_DETECT == STD_ON)
    VAR (Std_ReturnType, AUTOMATIC) ret = (Std_ReturnType)E_NOT_OK;
#endif /* (WDG_DEV_ERROR_DETECT == STD_ON) */

#ifdef WDG_PRECOMPILE_SUPPORT
    /* If precompile support enable, initialize the configuration pointer
     * with the default pointer */
    ConfigPtr = &Wdg_ConfigPC;
#endif    /* #ifdef WDG_PRECOMPILE_SUPPORT */

#if (WDG_DEV_ERROR_DETECT == STD_ON)
#ifndef WDG_PRECOMPILE_SUPPORT
    if (NULL_PTR == ConfigPtr)
    {
        Det_ReportError((uint16)WDG_MODULE_ID, WdgIndex,(uint8)WDG_INIT_ID,
                        (uint8)WDG_E_PARAM_CONFIG);
    }
    else
    {
#endif /* #ifndef WDG_PRECOMPILE_SUPPORT */
#endif /* (WDG_DEV_ERROR_DETECT == STD_ON)*/

        Wdg_DefaultMode = ConfigPtr->Wdg_CfgDefaultMode;

        /* If the mode that will be set up in initialization is off mode and the driver
         * does not support disabling the hardware then do not execute the initialization
         * and report the error */
#if (WDG_DISABLE_ALLOWED == STD_OFF)
        if (WDGIF_OFF_MODE == Wdg_DefaultMode)
        {
            Dem_ReportErrorStatus(WDG_E_DISABLE_REJECTED, DEM_EVENT_STATUS_FAILED);
        }
        else
        {
#endif /* (WDG_DISABLE_ALLOWED == STD_OFF) */

#if (WDG_DEV_ERROR_DETECT == STD_ON)
            if ((Wdg_DefaultMode != WDGIF_OFF_MODE) &&
                (Wdg_DefaultMode != WDGIF_SLOW_MODE)&&
                (Wdg_DefaultMode != WDGIF_FAST_MODE))
            {
                /* If the mode is not in the allowed boundaries of configuration
                 * do not execute initialization */
                Det_ReportError((uint16)WDG_MODULE_ID, WdgIndex,(uint8) WDG_INIT_ID,
                                (uint8) WDG_E_PARAM_CONFIG);
            }
            else
            {
                /* If the hardware specific contents of the given configuration set
                 * is not in allowed boundaries do not execute initialization
                 */
                ret = Wdg_LLD_CheckHwInitSettings(ConfigPtr);

                if ((Std_ReturnType)E_NOT_OK == ret)
                {
                    Det_ReportError((uint16)WDG_MODULE_ID, WdgIndex, (uint8)WDG_INIT_ID,
                                    (uint8)WDG_E_PARAM_CONFIG);
                }
                else
                {
#endif /* (WDG_DEV_ERROR_DETECT == STD_ON)*/

                   /* Set up the the hardware settings */
                    Wdg_LLD_Init(ConfigPtr);

#if (WDG_DEV_ERROR_DETECT == STD_ON)
                        Wdg_Status = WDG_IDLE;
                }
            }

#endif /* WDG_DEV_ERROR_DETECT == STD_ON */

#if (WDG_DISABLE_ALLOWED == STD_OFF)
        }
#endif /* (WDG_DISABLE_ALLOWED == STD_OFF) */

#if (WDG_DEV_ERROR_DETECT == STD_ON)
#ifndef WDG_PRECOMPILE_SUPPORT
    }
#endif /*#ifndef WDG_PRECOMPILE_SUPPORT */
#endif /* WDG_DEV_ERROR_DETECT == STD_ON */
}

/**
 * @brief   Switches the watchdog into the mode Mode.
 * @details By choosing one of a limited number of statically configured
 *          settings (e.g. toggle or window watchdog, different timeout periods)
 *          the Wdg module and the watchdog hardware can be switched between the
 *          following three different watchdog modes using the @p Wdg_SetMode
 *          function:<br>
 *          - WDGIF_OFF_MODE,
 *          - WDGIF_SLOW_MODE,
 *          - WDGIF_FAST_MODE.
 *          .
 *
 * @param[in] Mode      One of the following statically configured modes:<br>
 *                      -# WDGIF_OFF_MODE,
 *                      -# WDGIF_SLOW_MODE,
 *                      -# WDGIF_FAST_MODE.
 *                      .
 *
 * @return              Std_ReturnType.
 * @retval  E_OK        Mode switch executed completely and successfully.
 * @retval  E_NOT_OK    The mode switch encountered errors.
 *
 *  @requirements    WDG064, WDG031, WDG063, WDG065
 *
 * @remarks Covers WDG064, WDG031, WDG063, WDG065
 * @remarks Implements DWDG01006, DWDG16000, DWDG18000, DWDG20000, DWDG12000
 *
 * @api
 */

FUNC(Std_ReturnType, WDG_CODE) Wdg_SetMode(VAR(WdgIf_ModeType, AUTOMATIC) Mode)
{
    VAR(Std_ReturnType, AUTOMATIC) ret = (Std_ReturnType)E_OK;

#if (WDG_DEV_ERROR_DETECT == STD_ON)
    VAR(Std_ReturnType, AUTOMATIC) ret_hw = (Std_ReturnType)E_NOT_OK;

    /* If the state of the driver is not idle, i.e that the hardware is
     * currently been trigger or the mode is changeing, do not execute the
     * switching of the mode and report the error */
    if (WDG_IDLE != Wdg_Status)
    {
        Det_ReportError((uint16)WDG_MODULE_ID, WdgIndex, (uint8)WDG_SETMODE_ID,
                        (uint8)WDG_E_DRIVER_STATE);
        ret = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        /* Change the state indicating that the driver is currently beeing switched */
        Wdg_Status = WDG_BUSY;

        /* Check if <Mode> is within allowed range */
        if ((Mode != WDGIF_OFF_MODE) &&
            (Mode != WDGIF_SLOW_MODE)&&
            (Mode != WDGIF_FAST_MODE))
        {
            Det_ReportError((uint16)WDG_MODULE_ID, WdgIndex,(uint8)WDG_SETMODE_ID,
                            (uint8) WDG_E_PARAM_MODE);
            ret = (Std_ReturnType)E_NOT_OK;
        }
        /* If the hardware specific contents of the given configuration set
         * is not in allowed boundaries do not execute initialization
         */
        else
        {
            ret_hw = Wdg_LLD_CheckHwModeSettings(Mode);
            if ((Std_ReturnType)E_NOT_OK == ret_hw)
            {
                Det_ReportError((uint16)WDG_MODULE_ID, WdgIndex, (uint8)WDG_SETMODE_ID,
                                (uint8)WDG_E_PARAM_MODE);
                ret = (Std_ReturnType)E_NOT_OK;
            }
            else
            {
#endif /* WDG_DEV_ERROR_DETECT == STD_ON */

        /* If the mode that will be set up is off mode and the driver does not support
         * disabling the hardware then do not change the mode and report the error */
#if (WDG_DISABLE_ALLOWED == STD_OFF)
                if (WDGIF_OFF_MODE == Mode)
                {
                    Dem_ReportErrorStatus(WDG_E_DISABLE_REJECTED, DEM_EVENT_STATUS_FAILED);
                    ret = (Std_ReturnType)E_NOT_OK;
                }
                else
                {
#endif /* WDG_DISABLE_ALLOWED == STD_OFF */
            /* If an error occurred when trying to set up the hardware */
                    ret = Wdg_LLD_SetMode( Mode);
                    if ((Std_ReturnType)E_NOT_OK == ret)
                    {
                        Dem_ReportErrorStatus((uint16)WDG_E_MODE_SWITCH_FAILED,
                                               DEM_EVENT_STATUS_FAILED);
                    }

#if (WDG_DISABLE_ALLOWED == STD_OFF)
                }
#endif /* WDG_DISABLE_ALLOWED == STD_OFF */

#if (WDG_DEV_ERROR_DETECT == STD_ON)
            }
        }
        Wdg_Status = WDG_IDLE;
    }
#endif /* WDG_DEV_ERROR_DETECT == STD_ON */

    return (ret);
}


/**
 * @brief   This function triggers the watchdog hardware.
 * @details It has to be called cyclically by some upper layer function (usually
 *          the watchdog manager) in order to prevent the watchdog hardware from
 *          expiring.
 *
 * @pre     The Wdg module's environment shall make sure that the Wdg module has
 *          been initialized before the  @p Wdg_Trigger routine is called.
 *
 *@requirements    WDG036, WDG064, WDG063.
 *
 * @remarks Covers WDG036, WDG064, WDG063
 * @remarks Implements DWDG01007, DWDG15000, DWDG19000, DWDG20000, DWDG12000
 *
 * @api
 */
FUNC(void, WDG_CODE) Wdg_Trigger(void)
{

 /*  If development error detection is enabled */
#if (WDG_DEV_ERROR_DETECT == STD_ON)
    /* If the state of the driver is not idle, i.e that the hardware is
     * currently been trigger or the mode is changeing, do not execute the
     * switching of the mode and report the error */
    if (WDG_IDLE != Wdg_Status)
    {
        Det_ReportError((uint16)WDG_MODULE_ID, WdgIndex, (uint8)WDG_TRIGGER_ID,
                        (uint8)WDG_E_DRIVER_STATE);
    }
    else
    {
        /* Change the state indicating that the driver is currently beeing triggered */
        Wdg_Status = WDG_BUSY;
#endif
        Wdg_LLD_Trigger();
#if (WDG_DEV_ERROR_DETECT == STD_ON)
        Wdg_Status = WDG_IDLE;
    }
#endif
}




/**
 * @brief   Returns the version information of the module.
 * @details The  Wdg_GetVersionInfo function shall return the version
 *          information of this module. The version information includes:
 *          - Module Id,
 *          - Vendor Id,
 *          - Vendor specific version numbers.
 *          .
 *
 * @pre    This ISR is only required if the WDG_VERSION_INFO_API has to be
 *         equal STD_ON.
 *
 * @param[in,out] versioninfo   Pointer to where to store the version
 *                              information of this module.
 *
 * @api
 *
 * @requirements    WDG068
 *
 * @remarks Covers WDG068
 * @remarks Implements DWDG01008, DWDG13000
 */

#if (WDG_VERSION_INFO_API == STD_ON) || defined(__DOXYGEN__)

FUNC(void, WDG_CODE) Wdg_GetVersionInfo
                    (P2VAR(Std_VersionInfoType, AUTOMATIC, WDG_APPL_DATA) versioninfo)
{
    (versioninfo)->vendorID         = (uint16)WDG_VENDOR_ID;
    (versioninfo)->moduleID         = (uint8)WDG_MODULE_ID;
    (versioninfo)->instanceID       = (uint8)WdgIndex;
    (versioninfo)->sw_major_version = (uint8)WDG_SW_MAJOR_VERSION;
    (versioninfo)->sw_minor_version = (uint8)WDG_SW_MINOR_VERSION;
    (versioninfo)->sw_patch_version = (uint8)WDG_SW_PATCH_VERSION;
}
#endif /* WDG_VERSION_INFO_API == STD_ON */

#define WDG_STOP_SEC_CODE
/*
 * @brief Include Memory mapping specification
 * @note Violates MISRA 2004 Advisory Rule 19.1 - See @ref Wdg_c_REF_1
 * @note Violates MISRA 2004 Required Rule 19.15- See @ref Wdg_c_REF_2
 */
/* lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/* lint -restore */
#ifdef __cplusplus
}
#endif
/** @} */
