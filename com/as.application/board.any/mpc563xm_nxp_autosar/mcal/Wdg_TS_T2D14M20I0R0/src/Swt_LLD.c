/*!
 *  @file    SWT_LLD.c
 *
 * @version 2.0.0
 * @brief   AUTOSAR Wdg - Software Watchdog Timer (SWT) Registers
 * @details Contains information about the SWT's registers
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
*************************************************************************/

/*==================================================================================================
==================================================================================================*/

/*
 * @page misra_violations MISRA-C:2004 violations
 *
 * @section Swt_lld_c_REF_1
 *          Violates  MISRA  2004 Advisory  Rule  19.1,  only preprocessor
 *          statements and comments before '#include' This violation  is
 *          not  fixed since  the inclusion  of MemMap.h  is as  per Autosar
 *          requirement MEMMAP003.
 *
 * @section Swt_LLD_c_REF_2
 *          Violates  MISRA  2004 Required Rule 19.15,  Precaution shall be
 *          taken in order to prevent the contents of a header file being
 *          included twice.This violation  is not  fixed since  the inclusion
 *          of MemMap.h  is as  per Autosar  requirement MEMMAP003.
 *
 * @section Swt_LLD_c_REF_3
 *          Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer.
 *          This macro compute the address of any register by using the hardware ofsset
 *          of the controller.The address calculated as an unsigned int is passed to a
 *          macro for initializing the pointer with that address.(ex:see REG_WRITE32 macro).
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
#include "Reg_eSys_SWT.h"

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
/*
 * @brief  Parameters that shall be published within the driver header file
 *         and also in the module's description file
 * @remarks Covers BSW00374, BSW00318
*/
#define SWT_VENDOR_ID_C         43
#define SWT_AR_MAJOR_VERSION_C  3
#define SWT_AR_MINOR_VERSION_C  0
#define SWT_AR_PATCH_VERSION_C  0
#define SWT_SW_MAJOR_VERSION_C  2
#define SWT_SW_MINOR_VERSION_C  0
#define SWT_SW_PATCH_VERSION_C  0
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and SWT_LLD_C header file are of the same vendor */
#if (SWT_VENDOR_ID_C != SWT_LLD_VENDOR_ID)
    #error "Swt_lld.c and Swt_lld.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and SWT_LLD_C header file are of the same Autosar version */
    #if ((SWT_AR_MAJOR_VERSION_C != SWT_LLD_AR_MAJOR_VERSION) || \
         (SWT_AR_MINOR_VERSION_C != SWT_LLD_AR_MINOR_VERSION) || \
         (SWT_AR_PATCH_VERSION_C != SWT_LLD_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of Swt_lld.c and Swt_lld.h are different"
    #endif
#endif
/* Check if source file and SWT header file are of the same Software version */
#if ((SWT_SW_MAJOR_VERSION_C != SWT_LLD_SW_MAJOR_VERSION) || \
     (SWT_SW_MINOR_VERSION_C != SWT_LLD_SW_MINOR_VERSION) || \
     (SWT_SW_PATCH_VERSION_C != SWT_LLD_SW_PATCH_VERSION))
    #error "Software Version Numbers of Swt_lld.c and Swt_lld.h are different"
#endif

/* Check if source file and SWT register header file are of the same vendor */
#if (SWT_VENDOR_ID_C != REG_ESYS_SWT_VENDOR_ID)
    #error "Swt_lld.c and Reg_eSys_SWT.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and SWT register header file are of the same Autosar version */
    #if ((SWT_AR_MAJOR_VERSION_C != REG_ESYS_SWT_AR_MAJOR_VERSION) || \
         (SWT_AR_MINOR_VERSION_C != REG_ESYS_SWT_AR_MINOR_VERSION) || \
         (SWT_AR_PATCH_VERSION_C != REG_ESYS_SWT_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of Swt_lld.c and Reg_eSys_SWT.h are different"
    #endif
#endif
/* Check if source file and SWT register header file are of the same Software version */
#if ((SWT_SW_MAJOR_VERSION_C != REG_ESYS_SWT_SW_MAJOR_VERSION) || \
     (SWT_SW_MINOR_VERSION_C != REG_ESYS_SWT_SW_MINOR_VERSION) || \
     (SWT_SW_PATCH_VERSION_C != REG_ESYS_SWT_SW_PATCH_VERSION))
    #error "Software Version Numbers of Swt_lld.c and Reg_eSys_SWT.h are different"
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
#define WDG_START_SEC_VAR_UNSPECIFIED
/*
 * @note Violates MISRA 2004 Required Rule 19.15,Precaution shall be taken in order to prevent the
 *       contents of a header file being included twice. - See @ref Swt_LLD_c_REF_2
*/
/*lint -save -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

STATIC P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_APPL_CONST) Ram_LLD_ConfigPtr = NULL_PTR;

/*
 * @brief The mode used to service the watchdog; it can be used either the fixed
 *        sequence or the keyed sequence. It is set up at initialization.
 *
 * @remarks Implements DWDG03007
*/
#ifdef WDG_KEYED_SERVICE_USED
STATIC VAR(Wdg_ServiceModeType, WDG_VAR) Wdg_ServiceMode;
#endif
#define WDG_STOP_SEC_VAR_UNSPECIFIED

/*
 * @note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
 *       before '#include' - See @ref Swt_lld_c_REF_1
 * @note Violates MISRA 2004 Required Rule 19.15,Precaution shall be taken in order to prevent the
 *       contents of a header file being included twice. - See @ref Swt_LLD_c_REF_2
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
#define WDG_START_SEC_CODE
/*
 * @note Violates MISRA 2004 Advisory Rule 19.1 - See @ref Swt_lld_c_REF_1
 * @note Violates MISRA 2004 Required Rule 19.15- See @ref Swt_lld_c_REF_2
*/
/* lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/* lint -restore */
/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
/*
 * @brief   This function initializes the hardware of WDG module.
 * @details Sets up the values such as timeout value, window value
 *
 * @param[in]      ConfigPtr      Pointer to configuration set.
 *
 *
 *
 * @remarks Implements DWDG03002, DWDG14000,
*/

FUNC(void, WDG_CODE) Wdg_SWT_Init(P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr)
{

    CONST(WdgIf_ModeType, WDG_CONST)Wdg_DefaultMode = ConfigPtr->Wdg_CfgDefaultMode;
    CONST(SWT_HwSettingsType, WDG_CONST) DefaultConfig = ConfigPtr->Config_Wdg_Internal[Wdg_DefaultMode];
#ifdef WDG_KEYED_SERVICE_USED
    CONST(Wdg_ServiceKeyWidthType, WDG_CONST)Wdg_KeyServiceValue = ConfigPtr->Wdg_KeyServiceValue ;
#endif

    Ram_LLD_ConfigPtr = ConfigPtr;
#ifdef WDG_KEYED_SERVICE_USED
    Wdg_ServiceMode     = Ram_LLD_ConfigPtr->Wdg_CfgServiceMode;
#endif
    /* Unlock the possible lock condition   */

/*
 *@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref Swt_lld_c_REF_3
*/
    REG_WRITE32(SWT_SR, SWT_UNLOCK_SEQ1);
/*
 *@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref Swt_lld_c_REF_3
*/
    REG_WRITE32(SWT_SR, SWT_UNLOCK_SEQ2);

    /* Disable watchdog */
/*
 *@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref Swt_lld_c_REF_3
*/
    REG_BIT_CLEAR32(SWT_CR, SWT_WDG_ENABLED);

    /* Set Timer-out register */
/*
 *@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref Swt_lld_c_REF_3
*/
    REG_WRITE32(SWT_TO, DefaultConfig.WDG_TO);

    /* Set window register */
/*
 *@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref Swt_lld_c_REF_3
*/
    REG_WRITE32(SWT_WN, DefaultConfig.WDG_WN);

    /* Activate the default configuration  */

#ifdef WDG_KEYED_SERVICE_USED
    if (WDG_KEYED_SERVICE == Wdg_ServiceMode)
    {
        REG_WRITE32(SWT_SK, Wdg_KeyServiceValue);
    }
#endif
/*
 *@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref Swt_lld_c_REF_3
*/
    REG_WRITE32(SWT_CR,(SWT_MAP_ENABLE_BITS |DefaultConfig.WDG_CR));
}
/*
 * @brief   Switches the watchdog into the mode Mode
 * @details Sets up the specific parameters on the hardware for mode requested
 * @param[in]  Mode      One of the following statically configured modes:
 *                       -# WDGIF_OFF_MODE
 *                       -# WDGIF_SLOW_MODE
 *                       -# WDGIF_FAST_MODE
 *                       .
 *
 * @return Std_ReturnType
 * @retval E_OK        The mode switch has been executed completely and successfully
 * @retval E_NOT_OK    The mode switch has encounter errors
 *
 *
 * remarks Implements DWDG03003, DWDG16000
*/

FUNC(Std_ReturnType, WDG_CODE) Wdg_SWT_SetMode(CONST(WdgIf_ModeType, AUTOMATIC) Mode)
{
    VAR(Std_ReturnType, WDG_VAR) response = (Std_ReturnType)E_OK;
    CONST(SWT_HwSettingsType, WDG_CONST) CrtConfig = Ram_LLD_ConfigPtr->Config_Wdg_Internal[Mode];

/*
 *@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref Swt_lld_c_REF_3
*/
    if( (SWT_WDG_SOFT_LOCK) == ( REG_READ32(SWT_CR) & SWT_WDG_SOFT_LOCK ))
    {
        response =  (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        /* Disable watchdog */
/*
 *@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref Swt_lld_c_REF_3
*/

        REG_BIT_CLEAR32(SWT_CR, SWT_WDG_ENABLED);

        /* Set Timer-out register */
/*
 *@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref Swt_lld_c_REF_3
*/

        REG_WRITE32(SWT_TO, CrtConfig.WDG_TO);

        /* Set window register */
/*
 *@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref Swt_lld_c_REF_3
*/

        REG_WRITE32(SWT_WN, CrtConfig.WDG_WN);

        /* Set the Control Register*/
/*
 *@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref Swt_lld_c_REF_3
*/

        REG_WRITE32(SWT_CR,(SWT_MAP_ENABLE_BITS | CrtConfig.WDG_CR));
    }
return response;
}

/*
 * @brief   This function triggers the watchdog hardware.
 * @details Writes the trigger sequence on the hardware
 *
 *
 *
 * @pre The Wdg module's environment shall make sure that the Wdg module has
 *      been initialized before the Wdg_Trigger routine is called (Req: WDG104)
 *
 * @remarks Implements DWDG03004, DWDG15000
*/
FUNC(void, WDG_CODE) Wdg_SWT_Trigger(void)
{
#ifdef WDG_KEYED_SERVICE_USED
    if (WDG_KEYED_SERVICE == Wdg_ServiceMode)
    {
        VAR(uint32, WDG_VAR) keyed_value = SWT_GET_KEYED_SERVICE_SEQ1;
        REG_WRITE32(SWT_SR, keyed_value);
        keyed_value = ((17UL * keyed_value) + 3UL) & 0x0000FFFFUL;
        REG_WRITE32(SWT_SR, keyed_value);
    }
    else
    {
#endif
/*
 *@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref Swt_lld_c_REF_3
*/
        REG_WRITE32(SWT_SR, SWT_FIXED_SERVICE_SEQ1);
/*
 *@note Violates MISRA 2004 Advisory Rule 11.1, cast from unsigned long to pointer. - See @ref Swt_lld_c_REF_3
*/
        REG_WRITE32(SWT_SR, SWT_FIXED_SERVICE_SEQ2);

#ifdef WDG_KEYED_SERVICE_USED
    }
#endif
}


/*
 * @brief   The function check the settings for the Init parameter.
 * @details Verifies if the given configuration set is within the allowed boundaries
 *
 * @pre The Wdg module's environment shall make sure that the Wdg module has
 *      been initialized before the Wdg_Trigger routine is called (Req: WDG104)
 *
 *
 * @return Std_ReturnType
 * @return @retval E_OK        The mode switch has been executed completely and successfully
 *
 * @retval E_NOT_OK    The mode switch has encounter errors
 * @remarks Implements DWDG03005,
*/
FUNC(Std_ReturnType, WDG_CODE)
     Wdg_SWT_CheckInitSettings(P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr)
{
    VAR(Std_ReturnType, WDG_VAR) response = (Std_ReturnType)E_OK;
    CONST(SWT_HwSettingsType, WDG_CONST)
          DefaultConfig = ConfigPtr->Config_Wdg_Internal[ConfigPtr->Wdg_CfgDefaultMode];

    if ( SWT_TRIGGER_MODE_WINDOW == (DefaultConfig.WDG_CR & SWT_TRIGGER_MODE_WINDOW))
    {
        if (DefaultConfig.WDG_TO < DefaultConfig.WDG_WN)
        {
            response = (Std_ReturnType)E_NOT_OK;
        }
    }
    return response;
}

/*
 * @brief   The function check the settings for the Init parameter.
 * @details Verifies if the given configuration set is within the allowed boundaries
 * @pre     The Wdg module's environment shall make sure that the Wdg module has
 *          been initialized before the Wdg_Trigger routine is called (Req: WDG104)
 *
 * @return Std_ReturnType
 * @retval E_OK        The mode switch has been executed completely and successfully
 * @retval E_NOT_OK    The mode switch has encounter errors
 *
 *
 * @remarks Implements DWDG03006
*/
FUNC(Std_ReturnType, WDG_CODE) Wdg_SWT_CheckModeSettings(CONST(WdgIf_ModeType, AUTOMATIC) Mode)
{
    VAR(Std_ReturnType, WDG_VAR) response = (Std_ReturnType)E_OK;
    CONST(SWT_HwSettingsType, WDG_CONST) CrtConfig = Ram_LLD_ConfigPtr->Config_Wdg_Internal[Mode];

    if ( SWT_TRIGGER_MODE_WINDOW == (CrtConfig.WDG_CR & SWT_TRIGGER_MODE_WINDOW))
    {
        if (CrtConfig.WDG_TO < CrtConfig.WDG_WN)
        {
            response = (Std_ReturnType)E_NOT_OK;
        }
    }
 return response;
}

#define WDG_STOP_SEC_CODE
/*
 * @note Violates MISRA 2004 Advisory Rule 19.1 - See @ref Swt_lld_c_REF_1
 * @note Violates MISRA 2004 Required Rule 19.15- See @ref Swt_lld_c_REF_2
*/
/* lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/* lint -restore */
#ifdef __cplusplus
}
#endif

/** @} */
