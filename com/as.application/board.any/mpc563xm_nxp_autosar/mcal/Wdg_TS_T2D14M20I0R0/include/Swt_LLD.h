/*!
 *  @file    SWT_LLD.h
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
 * @section Swt_LLD_h_REF_1
 *          Violates  MISRA  2004 Required Rule 19.15,  Precaution shall be 
 *          taken in order to prevent the contents of a header file being 
 *          included twice. This violation  is not  fixed since  the inclusion
 *          of MemMap.h  is as  per Autosar  requirement MEMMAP003.
*/

#ifndef SWT_LLD_H
#define SWT_LLD_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Std_Types.h"
#include "Wdg_Cfg.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/*
 * @brief Parameters that shall be published within the driver header file 
 *        and also in the module's description file
 *        
 * @remarks  Covers BSW00374, BSW00379, BSW00318
*/
#define SWT_LLD_VENDOR_ID            43
#define SWT_LLD_AR_MAJOR_VERSION     3
#define SWT_LLD_AR_MINOR_VERSION     0
#define SWT_LLD_AR_PATCH_VERSION     0
#define SWT_LLD_SW_MAJOR_VERSION     2
#define SWT_LLD_SW_MINOR_VERSION     0
#define SWT_LLD_SW_PATCH_VERSION     0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and Std_Types header file are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((SWT_LLD_AR_MAJOR_VERSION != STD_TYPES_AR_MAJOR_VERSION) || \
         (SWT_LLD_AR_MINOR_VERSION != STD_TYPES_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Swt_LLD.h and Std_Types.h are different"
    #endif
#endif

/* Check if source file and Wdg_Cfg header file are of the same vendor */
#if (SWT_LLD_VENDOR_ID != WDG_VENDOR_ID_CFG)
    #error "Swt_LLD.h and Wdg_Cfg.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Wdg_Cfg header file are of the same Autosar version */
    #if ((SWT_LLD_AR_MAJOR_VERSION != WDG_AR_MAJOR_VERSION_CFG) || \
         (SWT_LLD_AR_MINOR_VERSION != WDG_AR_MINOR_VERSION_CFG) || \
         (SWT_LLD_AR_PATCH_VERSION != WDG_AR_PATCH_VERSION_CFG))
        #error "AutoSar Version Numbers of Swt_LLD.h and Wdg_Cfg.h are different"
    #endif
#endif
/* Check if source file and Wdg_Cfg header file are of the same Software version */
#if ((SWT_LLD_SW_MAJOR_VERSION != WDG_SW_MAJOR_VERSION_CFG) || \
     (SWT_LLD_SW_MINOR_VERSION != WDG_SW_MINOR_VERSION_CFG) || \
     (SWT_LLD_SW_PATCH_VERSION != WDG_SW_PATCH_VERSION_CFG))
    #error "Software Version Numbers of Swt_LLD.h and Wdg_Cfg.h are different"
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

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#define WDG_START_SEC_CODE
/*
 * @brief Include Memory mapping specification
 * @note Violates MISRA 2004 Required Rule 19.15, Precaution shall be taken in order to prevent the
 *       contents of a header file being included twice. - See @ref Swt_LLD_h_REF_1
*/
/* lint -save -e537 -e451*/
#include "MemMap.h"
/* lint -restore*/
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

FUNC(void, WDG_CODE) Wdg_SWT_Init(P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr);

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

FUNC(Std_ReturnType, WDG_CODE) Wdg_SWT_SetMode(CONST(WdgIf_ModeType, AUTOMATIC) Mode);



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
FUNC(void, WDG_CODE) Wdg_SWT_Trigger(void);



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
     Wdg_SWT_CheckInitSettings(P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr);


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
FUNC(Std_ReturnType, WDG_CODE) Wdg_SWT_CheckModeSettings(CONST(WdgIf_ModeType, AUTOMATIC) Mode);



#define WDG_STOP_SEC_CODE
/*
 * @brief Include Memory mapping specification
 * @note Violates MISRA 2004 Required Rule 19.15, Precaution shall be taken in order to prevent the
 *       contents of a header file being included twice. - See @ref Swt_LLD_h_REF_1
*/
/* lint -save -e537 -e451*/
#include "MemMap.h"
/* lint -restore*/

#ifdef __cplusplus
}
#endif

#endif /* SWT_LLD_H */

/** @} */
