/*!
 * @file    Reg_eSys_SWT.h
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


#ifndef REG_ESYS_SWT_H
#define REG_ESYS_SWT_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Reg_eSys.h"
#include "Reg_Macros.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/*
 * @brief  Parameters that shall be published within the driver header file and also in the 
 * module's description file
 * @remarks Covers BSW00374, BSW00379, BSW00318 
*/
#define REG_ESYS_SWT_VENDOR_ID            43
#define REG_ESYS_SWT_AR_MAJOR_VERSION     3
#define REG_ESYS_SWT_AR_MINOR_VERSION     0
#define REG_ESYS_SWT_AR_PATCH_VERSION     0
#define REG_ESYS_SWT_SW_MAJOR_VERSION     2
#define REG_ESYS_SWT_SW_MINOR_VERSION     0
#define REG_ESYS_SWT_SW_PATCH_VERSION     0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*
 * @brief This constant specifies the SWT Control Register
 * @remarks Implements DWDG06000
*/
#define SWT_CR                              (uint32)(SWT_BASEADDR + (uint32)0x00UL)

/*
 * @brief This constant specifies the SWT Interrupt Register
 * @remarks Implements DWDG06000
*/
#define SWT_IR                              (uint32)(SWT_BASEADDR + (uint32)0x04UL)

/*
 * @brief This constant specifies the SWT Time-out Register
 * @remarks Implements DWDG06000
*/
#define SWT_TO                              (uint32)(SWT_BASEADDR + (uint32)0x08UL)

/*
 * @brief This constant specifies the SWT Window Register
 * @remarks Implements DWDG06000
*/
#define SWT_WN                              (uint32)(SWT_BASEADDR + (uint32)0x0CUL)

/*
 * @brief This constant specifies the SWT Service Register
 * @remarks Implements DWDG06000
*/
#define SWT_SR                              (uint32)(SWT_BASEADDR + (uint32)0x10UL)

/*
 * @brief This constant specifies the SWT Output Register
 * @remarks Implements DWDG06000
*/
#define SWT_CO                              (uint32)(SWT_BASEADDR + (uint32)0x14UL)

/*
 * @brief This constant specifies the SWT Service Key Register
 * @remarks Implements DWDG06000
*/
#define SWT_SK                              (uint32)(SWT_BASEADDR + (uint32)0x18UL)

/*
 * @brief This constant specifies the value of the CR's Wdg enable bit if enabled
 * @remarks Implements DWDG06000
*/
#define SWT_WDG_ENABLED                     0x00000001UL

/*
 * @brief This constant specifies the value of the CR's Wdg enable bit if disabled
 * @remarks Implements DWDG06000
*/
#define SWT_WDG_DISABLED                    0x00000000UL

/*
 * @brief This constant specifies the value of the CR's debug mode control bit if enabled
 * @remarks Implements DWDG06000
*/
#define SWT_WDG_STOP_IN_DEBUG               0x00000002UL

/*
 * @brief This constant specifies the value of the CR's debug mode control bit if disabled
 * @remarks Implements DWDG06000
*/
#define SWT_WDG_RUN_IN_DEBUG                0x00000000UL

/*
 * @brief This constant specifies the value of the CR's stop mode control bit if enabled
 * @remarks Implements DWDG06000
*/
#define SWT_WDG_STOP_IN_HALT                0x00000004UL

/*
 * @brief This constant specifies the value of the CR's stop mode control bit if disabled
 * @remarks Implements DWDG06000
*/
#define SWT_WDG_RUN_IN_HALT                 0x00000000UL

/*
 * @brief This constant specifies the value of the CR's clock selection bit if enabled
 * @remarks Implements DWDG06000
*/
#define SWT_WDG_OSCILLATOR                  0x00000008UL

/*
 * @brief This constant specifies the value of the CR's clock selection bit if disabled
 * @remarks Implements DWDG06000
*/
#define SWT_WDG_SYSTEM_CLOCK                0x00000000UL

/*
 * @brief This constant specifies the value of the CR's soft lock bit if enabled
 * @remarks Implements DWDG06000
*/
#define SWT_WDG_SOFT_LOCK                   0x00000010UL

/*
 * @brief This constant specifies the value of the CR's soft lock bit if disabled
 * @remarks Implements DWDG06000
*/
#define SWT_WDG_NO_SOFT_LOCK                0x00000000UL

/*
 * @brief This constant specifies the value of the CR's hard lock bit if enabled
 * @remarks Implements DWDG06000
*/
#define SWT_WDG_HARD_LOCK                   0x00000020UL

/*
 * @brief This constant specifies the value of the CR's hard lock bit if disabled
 * @remarks Implements DWDG06000
*/
#define SWT_WDG_NO_HARD_LOCK                0x00000000UL

/*
 * @brief This constant specifies the value of the CR's interrupt then reset bit if disabled
 *        Generate an interrupt on an initial time-out, reset on a second consecutive time-out
 * @remarks Implements DWDG06000
*/
#define SWT_INTERRUPT_TOGGLE                0x00000040UL

/*
 * @brief This constant specifies the value of the CR's interrupt then reset bit if enabled
 *        Generate Reset on a time-out
 * @remarks Implements DWDG06000
*/
#define SWT_RESET_ON_TIMEOUT                0x00000000UL

/*
 * @brief This constant specifies the value of the CR's window mode bit if enabled
 *        Windowed mode, the service sequence is only valid when the down counter
 *        is less then value in the SWT_WN register
 * @remarks Implements DWDG06000
*/
#define SWT_TRIGGER_MODE_WINDOW             0x00000080UL

/*
 * @brief This constant specifies the value of the CR's window mode bit if disabled
 *        Regular mode, service sequence can be done at any time
 * @remarks Implements DWDG06000
*/
#define SWT_TRIGGER_MODE_REGULAR            0x00000000UL

/*
 * @brief This constant specifies the value of the CR's reset on invalid access bit if enabled
 *        Invalid access to the SWT causes a system reset if WEN = 1
 *        @remarks Implements DWDG06000
*/
#define SWT_INVALID_ACCESS_GEN_SYSTEM_RESET 0x00000100UL

/*
 * @brief This constant specifies the value of the CR's reset on invalid access bit if disabled
 *        Invalid access to the SWT generates a bus error+
 * @remarks Implements DWDG06000
*/
#define SWT_INVALID_ACCESS_GEN_BUS_ERROR    0x00000000UL

/*
 * @brief This constant specifies the value of the CR's master access protection
 *        Master acces protection enabled
 * @remarks Implements DWDG06000
*/
#define SWT_MAP_ENABLE_4BITS                 0xF0000000UL

/*
 * @brief This constant specifies the value of the CR's master access protection
 * Master acces protection enabled
 * @remarks Implements DWDG06000
*/

#define SWT_MAP_ENABLE_8BITS                0xFF000000UL

/*
 * @brief This constant specifies the value of the CR's master access protection
 *        Master acces protection enabled
 * @remarks Implements DWDG06000
*/

#define SWT_MAP_ENABLE_6BITS                0xCF000000UL


/*
 * @brief This constant indicates that the fixed service sequence is chosen
 * @remarks Implements DWDG06000
*/

#define SWT_FIXED_SERVICE_SEQ               0x00000000UL

/*
 * @brief This constant indicates that the keyed service sequence is chosen
 * @remarks Implements DWDG06000
*/

#define SWT_KEYED_SERVICE_SEQ               0x00000200UL

/*
 * @brief This constant specifies the value of the first part of the unlock sequence
 *        which clears the soft lock
 * @remarks Implements DWDG06000
*/
#define SWT_UNLOCK_SEQ1                     0x0000C520UL

/*
 * @brief This constant specifies the value of the second part of the unlock sequence
 *        which clears the soft lock
 * @remarks Implements DWDG06000
*/
#define SWT_UNLOCK_SEQ2                     0x0000D928UL

/*
 * @brief This constant specifies the value of the first part of the fixed service
 *        sequence which resets the timeout
 *@remarks Implements DWDG06000
*/

#define SWT_FIXED_SERVICE_SEQ1              0x0000A602UL

/*
 * @brief This constant specifies the value of the second part of the fixed service
 *        sequence which resets the timeout
 * @remarks Implements DWDG06000
*/
#define SWT_FIXED_SERVICE_SEQ2              0x0000B480UL

/*
 * @brief This constant specifies the value of the second part of the fixed service
 *        sequence which resets the timeout
 *        value = (((17UL * REG_READ32(SWT_SK)) + 3UL) mod 2^16)
 * @remarks Implements DWDG06000
*/
#define SWT_GET_KEYED_SERVICE_SEQ1  (uint32) ((((17UL * REG_READ32(SWT_SK))) + 3UL) & 0x0000FFFFUL)
/*
 * @brief  This constant specifies the value that clears the flag and the interrupt. It is
 *         written in SWT_IR on the TIF bit
 * @remarks Implements DWDG06000
*/
#define SWT_IR_CLEAR                        0x00000001UL

#ifdef __cplusplus
}
#endif

#endif  /* REG_ESYS_SWT_H */

/** @} */
