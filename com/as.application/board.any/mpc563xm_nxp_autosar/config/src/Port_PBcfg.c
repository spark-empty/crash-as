/*!
 * @file    Port_PBCfg.c
 *
 * @version 2.0.0
 * @brief   AUTOSAR Port - PORT driver configuration.
 * @details This file contains the PORT driver postbuild configuration.
 *
 * @addtogroup  Port
 * @{
 */

/***********************************************************************
 * PROJECT              AUTOSAR 3.0 MCAL
 * PLATFORM             PA
 * PERIPHERAL           SIU
 * DEPENDENCIES         none
 *
 * AUTOSAR VERSION      3.0.0
 * AUTOSAR REVISION     ASR_REL_3_0_REV_0003
 * AUTOSAR CONF.VARIANT
 * SW VERSION           2.0.0
 * BUILDVERSION         XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223
 *
 * COPYRIGHT : (c)      2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
 *                      ALL RIGHTS RESERVED
 **************************************************************************/

/*==================================================================================================
==================================================================================================*/
/**
 * @page misra_violations MISRA-C:2004 violations
 *
 * @section PORT_PBCFG_REF_1
 * Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before '#include'
 * This is an Autosar requirement about the memory management.
 *
 * @section PORT_PBCFG_REF_2
 * Violates MISRA 2004 Required Rules 10.1, Implicit conversion changes signedness.
 * Many type conversions are implemented in MACROS. The code was tested successfully with 3 different compilers.
 *
 * @section PORT_PBCFG_REF_3
 * Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h
 * There are different kinds of execution code sections.
*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Port.h"


#ifndef PORT_PRECOMPILE_SUPPORT
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
 * @brief Parameters that shall be published within the Port driver header file and also in the
 *        module's description file
 * @details The integration of incompatible files shall be avoided.
 * @remarks Covers BSW00374, BSW00379, BSW00318
 */
#define PORT_VENDOR_ID_PBCFG_C            43
#define PORT_AR_MAJOR_VERSION_PBCFG_C     3
#define PORT_AR_MINOR_VERSION_PBCFG_C     0
#define PORT_AR_PATCH_VERSION_PBCFG_C     0
#define PORT_SW_MAJOR_VERSION_PBCFG_C     2
#define PORT_SW_MINOR_VERSION_PBCFG_C     0
#define PORT_SW_PATCH_VERSION_PBCFG_C     0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if Port_PBCfg.c and Port.h are of the same vendor */
#if (PORT_VENDOR_ID_PBCFG_C != PORT_VENDOR_ID)
    #error "Port_PBCfg.c and Port.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if Port_PBCfg.c and Port.h are of the same Autosar version */
    #if ((PORT_AR_MAJOR_VERSION_PBCFG_C != PORT_AR_MAJOR_VERSION) || \
         (PORT_AR_MINOR_VERSION_PBCFG_C != PORT_AR_MINOR_VERSION) || \
         (PORT_AR_PATCH_VERSION_PBCFG_C != PORT_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of Port_PBCfg.c and Port.h are different"
    #endif
#endif
/* Check if Port_PBCfg.c and Port.h are of the same software version */
#if ((PORT_SW_MAJOR_VERSION_PBCFG_C != PORT_SW_MAJOR_VERSION) || \
     (PORT_SW_MINOR_VERSION_PBCFG_C != PORT_SW_MINOR_VERSION) || \
     (PORT_SW_PATCH_VERSION_PBCFG_C != PORT_SW_PATCH_VERSION))
    #error "Software Version Numbers of Port_PBCfg.c and Port.h are different"
#endif

#define PORT_START_CONFIG_DATA_UNSPECIFIED
/**
 * @file  Port_PBcfg.c
 * @note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before '#include' - See @ref PORT_PBCFG_REF_1
 * @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref PORT_PBCFG_REF_3
 */
#include "MemMap.h"



/**
 * @brief Pin default configuration data for configPB_0
 */
CONST(Port_LLD_PinConfigType, PORT_CONST) Port_LLD_PinConfigPB_0[PORT_MAX_PIN_SETTINGS_0]=
{
  /**
   * @note: Violates MISRA 2004 Required Rules 10.1,Implicit conversion changes signedness. See @ref PORT_PBCFG_REF_2
   */
  {(uint16)83, (uint16)0x060c, (sint8)1, FALSE},
  {(uint16)84, (uint16)0x050c, (sint8)0, FALSE},
  {(uint16)188, (uint16)0x020c, (sint8)0, FALSE},
  {(uint16)179, (uint16)0x010c, (sint8)0, FALSE}
};

/**
 * @brief This table contains all the Configured Port Pin parameters and the
 * number of Port Pins configured by the tool for the post-build mode PortConfigSet_0
 */
CONST(Port_ConfigType, PORT_CONST) PortConfigSet_0 =
{
  PORT_MAX_PIN_SETTINGS_0,
  Port_LLD_PinConfigPB_0
};

#if (PORT_SET_PIN_MODE_API == STD_ON)

/**
 * @brief Port Pin description data
 * @remarks Covers MCAL2881
 */
CONST (uint16, PORT_VAR) Port_PinDescription[9][26] =
{  
{ (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x1F98, (uint16)0x7FC0, (uint16)0xFFFC, (uint16)0xFFFF, (uint16)0x0003, (uint16)0x0000, (uint16)0xF0A8, (uint16)0x0402, (uint16)0xFBB1, (uint16)0x019B, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0xC000, (uint16)0xFFFF, (uint16)0xFFFF, (uint16)0xFFFF, (uint16)0x3FFF },
{ (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x1F98, (uint16)0x7FC0, (uint16)0xFFFC, (uint16)0xFFFF, (uint16)0x0003, (uint16)0x0000, (uint16)0xF8A8, (uint16)0x0402, (uint16)0x17B1, (uint16)0x0180, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0xC000, (uint16)0xFFFF, (uint16)0xFFFF, (uint16)0xFFFF, (uint16)0x3FFF },
{ (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0618, (uint16)0x79C0, (uint16)0xFFFC, (uint16)0xFFC3, (uint16)0x0003, (uint16)0x0000, (uint16)0x98A8, (uint16)0x0002, (uint16)0xF7B1, (uint16)0x019B, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0xC000, (uint16)0xFFFF, (uint16)0xFFFF, (uint16)0xFFFF, (uint16)0x3FFF },
{ (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x07A0, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000 },
{ (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0784, (uint16)0x3F01, (uint16)0x0003, (uint16)0x0000, (uint16)0x9808, (uint16)0x0002, (uint16)0x0011, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000 },
{ (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000 },
{ (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000 },
{ (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000 },
{ (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0200, (uint16)0x2000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000, (uint16)0x0000 }
};
#endif

#define PORT_STOP_CONFIG_DATA_UNSPECIFIED
/**
 * @file  Port_PBcfg.c
 * @note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before '#include' - See @ref PORT_PBCFG_REF_1
 * @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref PORT_PBCFG_REF_3
 */
#include "MemMap.h"

#endif    /* PORT_PRECOMPILE_SUPPORT*/

#ifdef __cplusplus
}
#endif
/** @} */

/* End of File */
