/*!
 * @file    Wdg_Irq.c
 *
 * @version 2.0.0
 * @brief   AUTOSAR Wdg - Contains the implementation of the
 *          Wdg interrrupt
 * @detaile
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
 * @section Wdg_Irq_c_REF_1
 *          Violates  MISRA  2004 Advisory  Rule  19.1,  only preprocessor statements and comments before '#include'
 *          This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement MEMMAP003.
 * @section Wdg_Irq_c_REF_2
 *          Violates  MISRA  2004 Required Rule 19.15,  Precaution shall be taken in order to prevent the
 *          contents of a header file being included twice.
 *          This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement MEMMAP003.
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
#include "Std_Types.h"
#include "Dem.h"
#include "Reg_eSys_SWT.h"
#include "Wdg_Cfg.h"
#include "Mcal.h"
/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

#define WDG_VENDOR_ID_IRQ               43
#define WDG_AR_MAJOR_VERSION_IRQ        3
#define WDG_AR_MINOR_VERSION_IRQ        0
#define WDG_AR_PATCH_VERSION_IRQ        0
#define WDG_SW_MAJOR_VERSION_IRQ        2
#define WDG_SW_MINOR_VERSION_IRQ        0
#define WDG_SW_PATCH_VERSION_IRQ        0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and WDG header file are of the same Autosar version */
    #if ((WDG_AR_MAJOR_VERSION_IRQ != DEM_AR_MAJOR_VERSION) || \
         (WDG_AR_MINOR_VERSION_IRQ != DEM_AR_MINOR_VERSION))
      #error "AutoSar Version Numbers of Wdg_Irq.c and Dem.h are different"
    #endif
#endif

/* Check if source file and reg_e_sys_swt header file are of the same vendor */
#if (WDG_VENDOR_ID_IRQ != REG_ESYS_SWT_VENDOR_ID)
    #error " Wdg_Irq.h and Reg_eSys_SWT.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and reg_e_sys_swt header file are of the same Autosar version */
    #if ((WDG_AR_MAJOR_VERSION_IRQ != REG_ESYS_SWT_AR_MAJOR_VERSION) || \
         (WDG_AR_MINOR_VERSION_IRQ != REG_ESYS_SWT_AR_MINOR_VERSION) || \
         (WDG_AR_PATCH_VERSION_IRQ != REG_ESYS_SWT_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of Wdg_Irq.c and Reg_eSys_SWT.h are different"
    #endif
#endif
/* Check if source file and reg_e_sys_swt header file are of the same Software version */
#if ((WDG_SW_MAJOR_VERSION_IRQ != REG_ESYS_SWT_SW_MAJOR_VERSION) || \
     (WDG_SW_MINOR_VERSION_IRQ != REG_ESYS_SWT_SW_MINOR_VERSION) || \
     (WDG_SW_PATCH_VERSION_IRQ != REG_ESYS_SWT_SW_PATCH_VERSION))
    #error "Software Version Numbers of Wdg_Irq.c and Reg_eSys_SWT.h are different"
#endif

/* Check if source file and reg_e_sys_swt header file are of the same vendor */
#if (WDG_VENDOR_ID_IRQ != WDG_VENDOR_ID_CFG)
    #error " Wdg_Irq.h and Wdg_Cfg.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and WDG header file are of the same Autosar version */
    #if ((WDG_AR_MAJOR_VERSION_IRQ != WDG_AR_MAJOR_VERSION_CFG) || \
         (WDG_AR_MINOR_VERSION_IRQ != WDG_AR_MINOR_VERSION_CFG) || \
         (WDG_AR_PATCH_VERSION_IRQ != WDG_AR_PATCH_VERSION_CFG))
      #error "AutoSar Version Numbers of Wdg_Irq.c and Wdg_Cfg.h are different"
    #endif
#endif
/* Check if source file and WDG header file are of the same Software version */
#if ((WDG_SW_MAJOR_VERSION_IRQ != WDG_SW_MAJOR_VERSION_CFG) || \
     (WDG_SW_MINOR_VERSION_IRQ != WDG_SW_MINOR_VERSION_CFG) || \
     (WDG_SW_PATCH_VERSION_IRQ != WDG_SW_PATCH_VERSION_CFG))
  #error "Software Version Numbers of Wdg_Irq.c and Wdg_Cfg.h are different"
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
#ifdef WDG_ISR_USED
/*
 * @brief   This function treats the SWT interrupt.
 * @details Interrupt Service Routine Addition
 * @pre    None
 * @post   None
 *
 * @param[in]      None.
 * @param[out]     None
 * @param[in,out]  None
 *
 * @return None
 * @retval None
 *
 * @remarks Implements DWDG04000
*/
ISR(Wdg_Isr);
#endif /* ifdef WDG_ISR_USED */
/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define WDG_START_SEC_CODE
/*
 * @note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and
 *       comments before '#include' - See @ref Wdg_Irq_c_REF_1
 * @note Violates MISRA 2004 Required Rule 19.15,Precaution shall be taken in order
 *       to prevent the contents of a header file being included twice.
 *       - See @ref Wdg_Irq_c_REF_2
*/
/*lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
#if defined(WDG_ISR_USED)  || defined(__DOXYGEN__)
/**
 * @brief   This function treats the SWT interrupt.
 * @details Interrupt Service Routine Addition.
 * @pre    This ISR is only required if the WDG_ISR_USED option is
 *          enabled.
 *
 * @isr
 *
 * @remarks Implements DWDG04000
 */
ISR(Wdg_Isr)
{
    /* Service interrupt flag */
    REG_BIT_SET32(SWT_IR, SWT_IR_CLEAR);

    /* Stop the watchdog*/
    REG_BIT_CLEAR32(SWT_CR, SWT_WDG_ENABLED);

    /* Report to DEM module WDG missed a trigger*/
    Dem_ReportErrorStatus((uint16)WDG_E_MISS_TRIGGER, DEM_EVENT_STATUS_FAILED);

    EXIT_INTERRUPT();
}
#endif
#define WDG_STOP_SEC_CODE
/*
 * @note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
 *       before '#include' - See @ref Wdg_Irq_c_REF_1
 * @note Violates MISRA 2004 Required Rule 19.15,Precaution shall be taken in order to prevent the
         contents of a header file being included twice. - See @ref Wdg_Irq_c_REF_2
*/
/* lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/* lint -restore */

#ifdef __cplusplus
}
#endif

/* End of file */
/** @} */