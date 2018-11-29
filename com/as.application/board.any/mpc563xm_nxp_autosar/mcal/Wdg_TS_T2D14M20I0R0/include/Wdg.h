/*!
 * @file    Wdg.h
 *
 * @version 2.0.0
 * @brief   AUTOSAR Wdg - contains the data exported by the watchodg module
 * @details Contains the information that will be exported by the module, as requested by Autosar.
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
 ************************************************************************/

/*==================================================================================================
==================================================================================================*/

/*
 * @remarks Implements DWDG01000
*/

/*
 * @page misra_violations MISRA-C:2004 violations
 * @section Wdg_h_REF_1
 *          Violates  MISRA  2004 Required Rule 19.15, Precaution shall be
 *          taken in order to prevent the contents of a header file being
 *          included twice. This violation  is not  fixed since  the inclusion
 *          of MemMap.h  is as  per Autosar  requirement MEMMAP003.
*/

#ifndef WDG_H
#define WDG_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

/* @remarks Covers WDG061 */
#include "Std_Types.h"
#include "Wdg_Cfg.h"
#if (WDG_TYPE == WDG_EXTERNAL_MODULE_SPI)
    #include "Spi.h"
#elif(WDG_TYPE == WDG_EXTERNAL_MODULE_DIO)
    #include "Dio.h"
#endif

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/* @remarks Covers BSW00374, BSW00379, BSW00318 */
#define WDG_VENDOR_ID            43
#define WDG_MODULE_ID            102
#define WDG_AR_MAJOR_VERSION     2
#define WDG_AR_MINOR_VERSION     2
#define WDG_AR_PATCH_VERSION     1
#define WDG_SW_MAJOR_VERSION     2
#define WDG_SW_MINOR_VERSION     0
#define WDG_SW_PATCH_VERSION     0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and WDG configuration header file are of the same vendor */
/*
* @remarks Covers WDG087
*/
#if (WDG_VENDOR_ID != WDG_VENDOR_ID_CFG)
    #error "Wdg.h and Wdg_Cfg.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* @remarks Covers WDG087 */
    /* Check if source file and WDG configuration header file are of the same Autosar version */
    #if ((WDG_AR_MAJOR_VERSION != WDG_AR_MAJOR_VERSION_CFG) || \
         (WDG_AR_MINOR_VERSION != WDG_AR_MINOR_VERSION_CFG) || \
         (WDG_AR_PATCH_VERSION != WDG_AR_PATCH_VERSION_CFG))
    #error "AutoSar Version Numbers of Wdg.h and Wdg_Cfg.h are different"
    #endif
#endif
/* Check if source file and WDG configuration header file are of the same software version */
#if ((WDG_SW_MAJOR_VERSION != WDG_SW_MAJOR_VERSION_CFG) || \
     (WDG_SW_MINOR_VERSION != WDG_SW_MINOR_VERSION_CFG) || \
     (WDG_SW_PATCH_VERSION != WDG_SW_PATCH_VERSION_CFG))
#error "Software Version Numbers of Wdg.h and Wdg_Cfg.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Std_Types header file are of the same Autosar version */
    #if ((WDG_AR_MAJOR_VERSION != STD_TYPES_AR_MAJOR_VERSION) || \
         (WDG_AR_MINOR_VERSION != STD_TYPES_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Wdg.h and Std_Types.h are different"
    #endif
#endif

/* Check if source file and WDG external dependencies are of the same Autosar version */
#if (WDG_TYPE == WDG_EXTERNAL_MODULE_SPI)
    #ifdef CHECK_AUTOSAR_VERSION
        #if ((WDG_AR_MAJOR_VERSION != SPI_AR_MAJOR_VERSION) || \
             (WDG_AR_MINOR_VERSION != SPI_AR_MINOR_VERSION))
        #error "AutoSar Version Numbers of Wdg.h and Spi.h are different"
        #endif
    #endif

#elif (WDG_TYPE == WDG_EXTERNAL_MODULE_DIO)
    #ifdef CHECK_AUTOSAR_VERSION
        #if ((WDG_AR_MAJOR_VERSION != DIO_AR_MAJOR_VERSION) || \
             (WDG_AR_MINOR_VERSION != DIO_AR_MINOR_VERSION))
        #error "AutoSar Version Numbers of Wdg.h and Dio.h are different"
        #endif
    #endif
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/


/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*
 * @brief  This enumerated type will contain the service ids for the watchodg functions
 *
 * @pre To define WDG_GETVERSION_ID, WDG_VERSION_INFO_API has to be equal to STD_ON
 *
 *
 * @remarks Implements DWDG01003
*/
enum
{
#if (WDG_VERSION_INFO_API == STD_ON) || defined(__DOXYGEN__)
    WDG_GETVERSION_ID   = 0x04, /*< @brief The service id for the Wdg_GetVersion function,
                                            used when using DET */
#endif
    WDG_INIT_ID         = 0x00, /*< @brief The service id for the Wdg_Init function, used
                                            when using DET */
    WDG_SETMODE_ID      = 0x01, /*< @brief The service id for the Wdg_SetMode function, used
                                            when using DET */
    WDG_TRIGGER_ID      = 0x02  /*< @brief The service id for the Wdg_Trigger function, used
                                            when using DET */
};

/*
 * @brief  Indicates the aditional det errors used by the watchdog driver
 * @remarks Implements DWDG01004
*/
enum
{
    WDG_E_DRIVER_STATE  = 0x10, /*< @brief API service used in wrong context (e.g. driver not
                                            initialized) */
    WDG_E_PARAM_MODE,           /*< @brief = 0x11 API service called with wrong/inconsistent
                                                   parameter(s) */
    WDG_E_PARAM_CONFIG          /*< @brief = 0x12 API service called with wrong/inconsistent
                                                   parameter(s) */
};

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
#define WDG_START_CONFIG_DATA_UNSPECIFIED
/*
 * @brief Include Memory mapping specification
 * @note  Violates MISRA 2004 Required Rule 19.15,Precaution shall be taken in
 *        order to prevent the contents of a header file being included twice.
 *        - See @ref Wdg_h_REF_1
*/
/*lint -save -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

/* @brief  Import extern declarations of WDG configuration from Wdg_Cfg.h */
WDG_CFG_EXTERN_DECLARATIONS

#define WDG_STOP_CONFIG_DATA_UNSPECIFIED
/*
 * @brief Include Memory mapping specification
 * @note Violates MISRA 2004 Required Rule 19.15,Precaution shall be taken in
 *       order to prevent the contents of a header file being included twice.
 *       - See @ref Wdg_h_REF_1
*/
/*lint -save -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#define WDG_START_SEC_CODE
/*
 * @brief Include Memory mapping specification
 * @note Violates MISRA 2004 Required Rule 19.15,Precaution shall be taken in
 *       order to prevent the contents of a header file being included twice.
 *       - See @ref Wdg_h_REF_1
*/
/*lint -save -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

/*
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

FUNC(void, WDG_CODE) Wdg_Init(P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr);


/*
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
FUNC(Std_ReturnType, WDG_CODE) Wdg_SetMode(VAR(WdgIf_ModeType, AUTOMATIC) Mode);


/*
 * @brief   This function triggers the watchdog hardware.
 * @details It has to be called cyclically by some upper layer function (usually
 *          the watchdog manager) in order to prevent the watchdog hardware from
 *          expiring.
 *
 * @pre     The Wdg module's environment shall make sure that the Wdg module has
 *          been initialized before the  @p Wdg_Trigger routine is called.
 *
 *@requirements    WDG036, WDG064, WDG063
 *
 * @remarks Covers WDG036, WDG064, WDG063
 * @remarks Implements DWDG01007, DWDG15000, DWDG19000, DWDG20000, DWDG12000
 *
 * @api
 */
FUNC(void, WDG_CODE) Wdg_Trigger(void);


/*
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
 *@requirements    WDG068
 *
 * @remarks Covers WDG068
 * @remarks Implements DWDG01008, DWDG13000
 */
#if (WDG_VERSION_INFO_API == STD_ON) || defined(__DOXYGEN__)

FUNC(void, WDG_CODE) Wdg_GetVersionInfo
        (P2VAR(Std_VersionInfoType, AUTOMATIC, WDG_APPL_DATA) versioninfo);

#endif /* WDG_VERSION_INFO_API == STD_ON */

#define WDG_STOP_SEC_CODE
/*
 * @brief Include Memory mapping specification
 * @note  Violates MISRA 2004 Required Rule 19.15,Precaution shall be taken in order to prevent the
 *        contents of a header file being included twice. - See @ref Wdg_h_REF_1
*/
/*lint -save -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif

#endif /* WDG_H */
/** @} */
