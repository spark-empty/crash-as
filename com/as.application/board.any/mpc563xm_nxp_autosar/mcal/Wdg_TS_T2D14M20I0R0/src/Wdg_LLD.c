/*!
 * @file    Wdg_LLD.c
 *
 * @version 2.0.0
 * @brief   AUTOSAR Wdg - Contains the middle layer of the Wdg driver
 * @details Maps the autosar version of the driver with the specific hardware
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
 **************************************************************************//*==================================================================================================
==================================================================================================*/


/*
 * @page misra_violations   MISRA-C:2004 violations
 *
 * @section Wdg_lld_c_REF_1 Violates  MISRA  2004 Advisory  Rule  19.1, only
 *                          preprocessor statements and comments before
 *                          '#include' This violation  is not  fixed since
 *                          the inclusion  of MemMap.h  is as  per Autosar
 *                          requirement MEMMAP003.
 *
 * @section Wdg_LLD_c_REF_2 Violates  MISRA  2004 Required Rule 19.15,
 *                          Precaution shall be taken in order to prevent the
 *                          contents of a header file being included twice.
 *                          This violation  is not  fixed since  the inclusion
 *                          of MemMap.h  is as  per Autosar  requirement MEMMAP003.
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
#include "Swt_LLD.h"
#include "Wdg_LLD.h"
/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/* @remarks Covers BSW00374, BSW00318 */
#define WDG_LLD_VENDOR_ID_C         43
#define WDG_LLD_AR_MAJOR_VERSION_C  3
#define WDG_LLD_AR_MINOR_VERSION_C  0
#define WDG_LLD_AR_PATCH_VERSION_C  0
#define WDG_LLD_SW_MAJOR_VERSION_C  2
#define WDG_LLD_SW_MINOR_VERSION_C  0
#define WDG_LLD_SW_PATCH_VERSION_C  0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and WDG_LLD header file are of the same vendor */
#if (WDG_LLD_VENDOR_ID_C != WDG_LLD_VENDOR_ID)
    #error "WDG_LLD.c and WDG_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and WDG_LLD header file are of the same Autosar version */
    #if ((WDG_LLD_AR_MAJOR_VERSION_C != WDG_LLD_AR_MAJOR_VERSION) || \
         (WDG_LLD_AR_MINOR_VERSION_C != WDG_LLD_AR_MINOR_VERSION) || \
         (WDG_LLD_AR_PATCH_VERSION_C != WDG_LLD_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of WDG_LLD.c and WDG_LLD.h are different"
    #endif
#endif
/* Check if source file and WDG_LLD header file are of the same Software version */
#if ((WDG_LLD_SW_MAJOR_VERSION_C != WDG_LLD_SW_MAJOR_VERSION) || \
     (WDG_LLD_SW_MINOR_VERSION_C != WDG_LLD_SW_MINOR_VERSION) || \
     (WDG_LLD_SW_PATCH_VERSION_C != WDG_LLD_SW_PATCH_VERSION))
    #error "Software Version Numbers of WDG_LLD.c and WDG_LLD.h are different"
#endif

/* Check if source file and SWT_LLD header file are of the same vendor */
#if (WDG_LLD_VENDOR_ID_C != SWT_LLD_VENDOR_ID)
    #error "Swt_lld.c and WDG_LLD.c have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and SWT_LLD header file are of the same Autosar version */
    #if ((WDG_LLD_AR_MAJOR_VERSION_C != SWT_LLD_AR_MAJOR_VERSION) || \
         (WDG_LLD_AR_MINOR_VERSION_C != SWT_LLD_AR_MINOR_VERSION) || \
         (WDG_LLD_AR_PATCH_VERSION_C != SWT_LLD_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of WDG_LLD.c and Swt_lld.h are different"
    #endif
#endif
/* Check if source file and SWT_LLD header file are of the same Software version */
#if ((WDG_LLD_SW_MAJOR_VERSION_C != SWT_LLD_SW_MAJOR_VERSION) || \
     (WDG_LLD_SW_MINOR_VERSION_C != SWT_LLD_SW_MINOR_VERSION) || \
     (WDG_LLD_SW_PATCH_VERSION_C != SWT_LLD_SW_PATCH_VERSION))
    #error "Software Version Numbers of WDG_LLD.c and Swt_lld.h are different"
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


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define WDG_START_SEC_CODE
/*
 * @note Violates MISRA 2004 Required Rule 19.15,Precaution shall be taken in
 *       order to prevent the contents of a header file being included twice.
 *       - See @ref Wdg_LLD_c_REF_2
*/
/*lint -save -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

/*
 * @brief   This function initializes the hardware of WDG module.
 * @details Calls the initialization function of the hardware that it is in use
 *          (if the wdg is internal calls the SWT initialization function, else
 *          the one that is for the type of the external driver)
 *
 * @param[in] ConfigPtr     Pointer to configuration set.
 *
 * @return    Std_ReturnType
 * @retval    E_OK          The mode switch has been executed completely and successfully
 * @retval    E_NOT_OK      The mode switch has encounter errors
 *
 *
 *
 * @remarks Implements DWDG02001
*/

FUNC(void, WDG_CODE) Wdg_LLD_Init(P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr)
{

    #if (WDG_INTERNAL_MODULE == WDG_TYPE)
        Wdg_SWT_Init(ConfigPtr);
    #elif (WDG_EXTERNAL_MODULE_SPI == WDG_TYPE)
        /* Should add the function for intializing the WDG module connected on SPI*/
        /* N/A for current platform*/
    #elif (WDG_EXTERNAL_MODULE_DIO == WDG_TYPE)
        /* Should add the function for intializing the WDG module connected on DIO*/
        /* N/A for current platform*/
    #endif
}

/*
 * @brief   Switches the watchdog into the mode Mode
 * @details Calls the set mode function specific of the hardware that it is in use
 *
 * @param[in] Mode          One of the following statically configured modes:
 *                          -# WDGIF_OFF_MODE
 *                          -# WDGIF_SLOW_MODE
 *                          -# WDGIF_FAST_MODE
 *                          .
 *
 * @return Std_ReturnType
 * @retval E_OK             The mode switch has been executed completely and successfully
 * @retval E_NOT_OK         The mode switch has encounter errors
 *
 *
 *
 * @remarks Implements DWDG02002
*/

FUNC(Std_ReturnType, WDG_CODE) Wdg_LLD_SetMode(VAR(WdgIf_ModeType, AUTOMATIC) Mode)
{
    VAR(Std_ReturnType, WDG_VAR) ret = (uint8)E_NOT_OK;

    #if (WDG_INTERNAL_MODULE == WDG_TYPE)
        ret = Wdg_SWT_SetMode(Mode);
    #elif (WDG_EXTERNAL_MODULE_SPI == WDG_TYPE)
        /* Should add the function for Mode setting of the WDG module connected on SPI*/
        /* N/A for current platform*/
    #elif (WDG_EXTERNAL_MODULE_DIO == WDG_TYPE)
        /* Should add the function for  Mode setting of the WDG module connected on DIO*/
        /* N/A for current platform*/
    #endif

    return ret;
}


/*
 * @brief   This function triggers the watchdog hardware.
 * @details Calls the trigger function specific of the hardware that it is in use
 *
 * @return Std_ReturnType
 * @retval E_OK             The mode switch has been executed completely and successfully
 * @retval E_NOT_OK         The mode switch has encounter errors
 *
 *
 *
 * @remarks Covers
 * @remarks Implements DWDG02003
*/
FUNC(void, WDG_CODE) Wdg_LLD_Trigger(void)
{

    #if (WDG_INTERNAL_MODULE == WDG_TYPE)
         Wdg_SWT_Trigger();
    #elif (WDG_EXTERNAL_MODULE_SPI == WDG_TYPE)
        /* Should add the function for triggering the WDG module connected on SPI*/
        /* N/A for current platform*/
    #elif (WDG_EXTERNAL_MODULE_DIO == WDG_TYPE)
        /* Should add the function for triggering the WDG module connected on DIO*/
        /* N/A for current platform*/
    #endif
}

/*
 * @brief   The function checks the settings for the Init parameter.
 * @details Calls the function specific of the hardware that it is in use in order
 *          to verify if the given configuration set is within the allowed boundaries
 * @pre     The Wdg module's environment shall make sure that the Wdg module has
 *          been initialized before the Wdg_Trigger routine is called (Req: WDG104)
 *
 * @return Std_ReturnType
 * @retval E_OK        The mode switch has been executed completely and successfully
 * @retval E_NOT_OK    The mode switch has encounter errors
 *
 *
 *
 * @remarks Covers
 * @remarks Implements DWDG02004
*/
FUNC(Std_ReturnType, WDG_CODE)
     Wdg_LLD_CheckHwInitSettings(P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr)
{
    VAR(Std_ReturnType, WDG_VAR) ret = (uint8)E_NOT_OK;

    #if (WDG_INTERNAL_MODULE == WDG_TYPE)
        ret = Wdg_SWT_CheckInitSettings(ConfigPtr);
    #elif (WDG_EXTERNAL_MODULE_SPI == WDG_TYPE)
        /* Should add the function for checking the Init settings of the WDG module connected
         *  on SPI*/
        /* N/A for current platform*/
    #elif (WDG_EXTERNAL_MODULE_DIO == WDG_TYPE)
        /* Should add the function for checking the Init settings of the WDG module connected
         * on DIO*/
        /* N/A for current platform*/
    #endif

    return ret;
}

/*
 * @brief   The function checks the settings for the mode parameter.
 * @details Calls the function specific of the hardware that it is in use in order
 *          to verify if the given configuration set is within the allowed boundaries
 *
 * @return Std_ReturnType
 * @retval E_OK             The mode switch has been executed completely and successfully
 * @retval E_NOT_OK         The mode switch has encounter errors
 *
 *
 *
 * @remarks Covers
 * @remarks Implements DWDG02005
*/
FUNC(Std_ReturnType, WDG_CODE) Wdg_LLD_CheckHwModeSettings(VAR(WdgIf_ModeType, AUTOMATIC) Mode)
{
    VAR(Std_ReturnType, WDG_VAR) ret = (uint8)E_NOT_OK;

    #if (WDG_INTERNAL_MODULE == WDG_TYPE)
        ret = Wdg_SWT_CheckModeSettings(Mode);
    #elif (WDG_EXTERNAL_MODULE_SPI == WDG_TYPE)
        /* Should add the function for checking the Mode settings of the WDG module connected
         * on SPI*/
        /* N/A for current platform*/
    #elif (WDG_EXTERNAL_MODULE_DIO == WDG_TYPE)
        /* Should add the function for checking the Mode settings of the WDG module connected
         * on DIO*/
        /* N/A for current platform*/
    #endif

    return ret;
}


#define WDG_STOP_SEC_CODE
/*
 * @note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
 *       before '#include' - See @ref Wdg_lld_c_REF_1
 * @note Violates MISRA 2004 Required Rule 19.15,Precaution shall be taken in order to prevent the
 *       contents of a header file being included twice. - See @ref Wdg_LLD_c_REF_2
*/
/* lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/* lint -restore */

#ifdef __cplusplus
}
#endif
/** @} */