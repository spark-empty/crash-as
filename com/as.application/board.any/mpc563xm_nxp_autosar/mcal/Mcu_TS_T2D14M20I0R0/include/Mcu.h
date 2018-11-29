/**
    @file    Mcu.h
    @version 2.0.0

    @brief   AUTOSAR Mcu - High level header of MCU driver.
    @details This file contains declarations of the functions defined by AutoSAR.

    Project AUTOSAR 3.0 MCAL
    Platform PA
    Peripheral FMPLL
    Dependencies none

    ARVersion 3.0.0
    ARRevision ASR_REL_3_0_REV_0003
    ARConfVariant
    SWVersion 2.0.0
    BuildVersion XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223

    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
    All Rights Reserved.
 */
/*==================================================================================================
==================================================================================================*/
/**
@page misra_violations MISRA-C:2004 violations

@section Mcu_h_REF_1
Violates MISRA-C:2004 Required Rule 19.15, Repeated include files, Precautions shall be taken in
order to prevent the contents of a header file being included twice This is not a violation since
all header files are protected against multiple inclusions

@section Mcu_h_REF_2
Violates MISRA-C:2004 Required Rule 20.2, Re-use of C90 reserved identifier
This violation is due to the use of "_" which is required as per Autosar

*/

/** @note Violates MISRA-C: 2004 Required Rule 20.2, Re-use of C90 reserved 
identifier: _MCU_H_- See @ref Mcu_h_REF_2 */
#ifndef _MCU_H_
#define _MCU_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/** @note  Violates MISRA-C: 2004 Required Rule 19.15, See @ref Mcu_h_REF_1*/
#include "Std_Types.h"
/** @remarks Covers MCU108 */
#include "Mcu_Cfg.h"
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** @remarks Covers BSW00374, BSW00379, BSW00318, MCU037 */
#define MCU_VENDOR_ID            43
#define MCU_MODULE_ID            101
#define MCU_AR_MAJOR_VERSION     2
#define MCU_AR_MINOR_VERSION     2
#define MCU_AR_PATCH_VERSION     2
#define MCU_SW_MAJOR_VERSION     2
#define MCU_SW_MINOR_VERSION     0
#define MCU_SW_PATCH_VERSION     0


/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/
/** @brief Api IDs for reporting to DET */ /** @remarks Covers MCU112 */
#define MCU_INIT_ID               (uint8)0x00U
#define MCU_INITRAMSECTION_ID     (uint8)0x01U
#define MCU_INITCLOCK_ID          (uint8)0x02U
#define MCU_DISTRIBUTEPLLCLOCK_ID (uint8)0x03U
#define MCU_GETPLLSTATUS_ID       (uint8)0x04U
#define MCU_GETRESETREASON_ID     (uint8)0x05U
#define MCU_GETRESETRAWVALUE_ID   (uint8)0x06U
#define MCU_PERFORMRESET_ID       (uint8)0x07U
#define MCU_SETMODE_ID            (uint8)0x08U
#define MCU_GETVERSIONINFO_ID     (uint8)0x09U
#define MCU_INSTANCE_ID           (uint8)0x0U

#define MCU_INITOSC_ID            (uint8)0x20U
#define MCU_CHANGE_MODE_ID        (uint8)0x21U
#define MCU_CHANGE_LOWPOWER_ID    (uint8)0x22U
#define MCU_APPLY_LOWPOWER_ID     (uint8)0x23U
#define MCU_APPLY_RUNMODE_ID      (uint8)0x24U
#define MCU_APPLY_MODE_ID         (uint8)0x25U 

    /** @brief Error IDs for reporting to DET */ /** @remarks Covers MCU112, MCU012 */
#define MCU_E_PARAM_CONFIG        (uint8)0x0AU /** @remarks Covers MCU018 */
#define MCU_E_PARAM_CLOCK         (uint8)0x0BU /** @remarks Covers MCU019 */
#define MCU_E_PARAM_MODE          (uint8)0x0CU /** @remarks Covers MCU020 */
#define MCU_E_PARAM_RAMSECTION    (uint8)0x0DU /** @remarks Covers MCU021 */
#define MCU_E_PLL_NOT_LOCKED      (uint8)0x0EU /** @remarks Covers MCU122 */
#define MCU_E_UNINIT              (uint8)0x0FU /** @remarks Covers MCU125 */
#define MCU_E_CLOCK_UNINIT        (uint8)0x10U /** @brief Error: Mcu_InitClock() was not executed
                                         before Mcu_GetPllStatus() or Mcu_DistributePllClock() */
#define MCU_E_MODE_NOT_ENABLED    (uint8)0x11U /** @brief Error: Mcu_Apply_Mode() tries to apply 
                                         a disabled mode */
    /** @brief Internal Macros */
    /** @brief Raw Reset Value returned in a case when Mcu_GetResetRawValue() is called before
        Mcu_Init() is called */
#define MCU_RAW_RESET_DEFAULT      (uint32)0xFFFFFFFFUL


#define MCU_E_WRONG_MODE         (uint8)0x20U /** @brief CER Error: Wrong mode */

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
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and MCU configuration header file are of the same vendor */
#if (MCU_VENDOR_ID != MCU_VENDOR_ID_CFG)
    #error "Mcu.h and Mcu_Cfg.h have different vendor ids"
#endif
/** @remarks Covers MCU110 */
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and MCU configuration header file are of the same Autosar version */
    #if ((MCU_AR_MAJOR_VERSION != MCU_AR_MAJOR_VERSION_CFG) || \
         (MCU_AR_MINOR_VERSION != MCU_AR_MINOR_VERSION_CFG) || \
         (MCU_AR_PATCH_VERSION != MCU_AR_PATCH_VERSION_CFG))
    #error "AutoSar Version Numbers of Mcu.h and Mcu_Cfg.h are different"
    #endif
#endif
/* Check if source file and MCU configuration header file are of the same software version */
#if ((MCU_SW_MAJOR_VERSION != MCU_SW_MAJOR_VERSION_CFG) || \
     (MCU_SW_MINOR_VERSION != MCU_SW_MINOR_VERSION_CFG) || \
     (MCU_SW_PATCH_VERSION != MCU_SW_PATCH_VERSION_CFG))
#error "Software Version Numbers of Mcu.h and Mcu_Cfg.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if Std_Types and MCU  header file are of the same Autosar version */
    #if ((MCU_AR_MAJOR_VERSION != STD_TYPES_AR_MAJOR_VERSION) || \
         (MCU_AR_MINOR_VERSION != STD_TYPES_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Mcu.h and Std_Types.h are different"
    #endif
#endif

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#define MCU_START_SEC_CODE
/** @note Violates MISRA-C: 2004 Required Rule 19.15 - See @ref Mcu_h_REF_1*/
#include "MemMap.h"

    /**
    @brief    MCU driver initialization function.
    @details This routine initializes the MCU Driver.
              The intention of this function is to make the configuration setting for power down,
               clock and ram sections visible within the MCU Driver.

    @param[in] ConfigPtr      pointer to configuration structure

    @return void

    @remarks Covers MCU153, MCU026, MCU126, MCU127, MCU013, MCU100, MCU101, MCU016, MCU018
    @remarks Implements DMCU01000, DMCU17026, DMCU17028, DMCU17048
     */
    extern FUNC (void, MCU_CODE) Mcu_Init (P2CONST (Mcu_ConfigType, MCU_VAR, MCU_APPL_CONST) \
        ConfigPtr);

    /**
    @brief    MCU driver initialization of ram sections.
    @details Function intializes the ram section selected by RamSection parameter.
    The section base address, size and value to be written are provided from
    the configuration structure.

    @param[in] RamSection      Index of ram section from config structure to be initialized.

    @return status
    @retval E_OK
    @retval E_NOT_OK

    @pre     Function requires an execution of Mcu_Init() before it can be used, otherwise it
             reports error to DET and returns E_NOT_OK.

    @remarks Covers MCU154, MCU030, MCU011, MCU013, MCU100, MCU101, MCU016, MCU018, MCU125,
             MCU017, MCU021, MCU018
    @remarks Implements DMCU01000, DMCU17034, DMCU17052
     */
    extern FUNC (Std_ReturnType, MCU_CODE) Mcu_InitRamSection (VAR (Mcu_RamSectionType, AUTOMATIC) \
        RamSection);

    /**
    @brief    MCU driver clock initialization function.
    @details This function intializes the PLL and MCU specific clock options. The clock setting is
             provided from the configuration structure.

    @param[in] ClockSetting      Index of clock setting from config structure to be used.

    @return status
    @retval E_OK
    @retval E_NOT_OK

    @pre Function requires an execution of Mcu_Init() before it can be used, otherwise it reports
         error to DET and returns E_NOT_OK.

    @remarks Covers MCU155, MCU031, MCU107, MCU013, MCU100, MCU101, MCU016, MCU018, MCU019, MCU125,
             MCU112, MCU113, MCU017
    @remarks Implements DMCU01000, DMCU17030, DMCU17050, DMCU17032
     */
    extern FUNC (Std_ReturnType, MCU_CODE) Mcu_InitClock (VAR (Mcu_ClockType, AUTOMATIC) \
        ClockSetting);

    /**
    @brief    This function activates the PLL clock to the MCU clock distribution.
    @details Function completes the PLL configuration and then activates the PLL clock
    to MCU. The function also activates the clock failure notification by
    enabling the interrupts from the current clock setting.

    @return void

    @pre Function requires an execution of Mcu_Init() and Mcu_InitClock()  before it can be used,
         otherwise it reports error to DET and returns E_NOT_OK.

    @remarks Covers MCU156, MCU028, MCU053, MCU013, MCU100, MCU101, MCU016, MCU018, MCU125, MCU122
    @remarks Implements DMCU01000, DMCU17000, DMCU17002, DMCU17042
     */
    extern FUNC (void, MCU_CODE) Mcu_DistributePllClock (void);

    /**
    @brief    This function returns the lock status of the pll.
    @details This function  returns the main pll status.

    @return status
    @retval MCU_PLL_LOCKED
    @retval MCU_PLL_UNLOCKED
    @retval MCU_PLL_STATUS_UNDEFINED

    @pre Function requires an execution of Mcu_Init() and Mcu_InitClock() before it can be used,
         otherwise it reports error to DET and returns E_NOT_OK.

    @remarks Covers MCU157, MCU008, MCU132, MCU013, MCU100, MCU101, MCU016, MCU018
    @remarks Implements DMCU01000, DMCU17004, DMCU17006, DMCU17008, DMCU17044
     */
    extern FUNC (Mcu_PllStatusType, MCU_CODE) Mcu_GetPllStatus (void);

    /**
    @brief    This function returns the reset reason.
    @details This routine returns the reset reason that is read from the hardware.

    @return ResetType
    @retval MCU_RESET_UNDEFINED/Mcu_ResetType

    @pre Function requires an execution of Mcu_Init() before it can be used, otherwise it reports
         error to DET and returns E_NOT_OK.

    @remarks Covers MCU158, MCU052, MCU005, MCU133, MCU125, MCU013, MCU100, MCU101, MCU016, MCU018
    @remarks Implements DMCU01000, DMCU17016, DMCU17018, DMCU17020, DMCU17046
     */
    extern FUNC (Mcu_ResetType, MCU_CODE) Mcu_GetResetReason (void);

    /**
    @brief    This function returns the raw reset value.
    @details This routine returns the raw reset value that is read from the hardware.

    @return Description of the returned value
    @retval void

    @pre Function requires an execution of Mcu_Init() and before it can be used, otherwise it
         reports error to DET and returns E_NOT_OK.

    @remarks Covers MCU159, MCU006, MCU125, MCU013, MCU100, MCU101, MCU016, MCU018
    @remarks Implements DMCU01000, DMCU17010, DMCU17012, DMCU17014, DMCU17044
     */
    extern FUNC (Mcu_RawResetType, MCU_CODE) Mcu_GetResetRawValue (void);

    /**
    @brief    This function performs a microcontroller reset.
    @details This function performs a microcontroller reset by using the hardware feature of the
             microcontroller.

    @return void

    @pre Function requires an execution of Mcu_Init() and before it can be used, otherwise it
         reports error to DET and returns E_NOT_OK.

    @remarks Covers MCU160, MCU007, MCU125, MCU013, MCU100, MCU101, MCU016, MCU018
    @remarks Implements DMCU01000, DMCU17036, DMCU17038, DMCU17054
     */
    /** @remarks Covers MCU146 */
#if MCU_PERFORM_RESET_API == STD_ON

    extern FUNC (void, MCU_CODE) Mcu_PerformReset (void);

#endif /* #if MCU_PERFORM_RESET_API == STD_ON */

    /**
    @brief    This function sets the MCU power mode.
    @details This function activates MCU power mode from config structure selected by McuMode
             parameter.

    @param[in] McuMode      Index of mcu mode from config structure to be set

    @return Description of the returned value
    @retval void

    @pre Function requires an execution of Mcu_Init() and before it can be used, otherwise it
         reports error to DET and returns E_NOT_OK.

    @remarks Covers MCU161, MCU164, MCU001, MCU035, MCU013, MCU100, MCU101, MCU016, MCU018,
             MCU020, MCU125, MCU013, MCU163, MCU112
    @remarks Implements DMCU01000, DMCU13000, DMCU17056
     */
    extern FUNC (void, MCU_CODE) Mcu_SetMode (VAR (Mcu_ModeType, AUTOMATIC) McuMode);

    /**
    @brief    This function returns the version information for the MCU module.
    @details This function returns the vendor id, module id, major, minor and patch version.

    @return versioninfo
    @retval Std_VersionInfoType

    @remarks Covers MCU103, MCU104, MCU162, MCU149
    @remarks Implements DMCU01000, DMCU17022, DMCU17024
     */
#if MCU_VERSION_INFO_API == STD_ON  /** @remarks Covers MCU104 */

    extern FUNC (void, MCU_CODE) Mcu_GetVersionInfo (P2VAR (Std_VersionInfoType, AUTOMATIC, \
        MCU_APPL_DATA) versioninfo);

#endif                          /* #if MCU_VERSION_INFO_API == STD_ON */
#define MCU_STOP_SEC_CODE
/** @note  Violates MISRA-C: 2004 Required Rule 19.15 - See @ref Mcu_h_REF_1*/
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* _MCU_H_ */
