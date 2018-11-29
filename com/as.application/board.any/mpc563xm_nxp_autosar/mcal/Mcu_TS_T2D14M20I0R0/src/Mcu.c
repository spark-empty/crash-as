/**
    @file    Mcu.c
    @version 2.0.0

    @brief   AUTOSAR Mcu - High level part of MCU driver.
    @details  This file contains the functions defined by AutoSAR.

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
/*!

 *  @addtogroup MCU
 *  @{
 */
 /**
@page misra_violations MISRA-C:2004 violations

@section Mcu_c_REF_1
Violates MISRA-C:2004 Required Rule 19.15, Repeated include file MemMap.h,  Precautions shall be
taken in order to prevent the contents of a header file being included twice This is not a violation
since all header files are protected against multiple inclusions

@section Mcu_c_REF_2
Violates MISRA-C:2004 Required Rule 17.4, Array indexing shall be the only allowed form of pointer
arithmetic. This violation is due to the use of pointer arithematic, to access the channel parameters,
the indexing of the pointer is taken care and hence the unintended memory location will not
be accessed

@section Mcu_c_REF_3
Violates MISRA-C:2004 Required Rule 14.3, Before preprocessing, a null statement shall only occur 
on a line by itself; it may be followed by a comment provided that the first
character following the null statement is a white-space character.This violation is due to use 
of extra ';'(semicolon) symbol

@section Mcu_c_REF_4
Violates MISRA-C:2004 Advisory  Rule 19.1,  only preprocessor statements and comments before
'#include'.This violation is not fixed since the inclusion of MemMap.h is as per 
Autosar requirement MEMMAP003
*/
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
/** @remarks Covers MCU108, MCU109 */

#include "Mcu.h"
#include "Mcu_LLD.h"
/**@remarks Covers MCU051, MCU109 */
#include "Dem.h"
#if (MCU_DEV_ERROR_DETECT == STD_ON) /**@remarks Covers MCU013, MCU100, MCU163 */
#include "Det.h"
#endif

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/** @remarks Covers BSW00374, BSW00318 */
#define MCU_VENDOR_ID_C         43
#define MCU_AR_MAJOR_VERSION_C  3
#define MCU_AR_MINOR_VERSION_C  0
#define MCU_AR_PATCH_VERSION_C  0
#define MCU_SW_MAJOR_VERSION_C  2
#define MCU_SW_MINOR_VERSION_C  0
#define MCU_SW_PATCH_VERSION_C  0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and MCU header file are of the same vendor */
#if (MCU_VENDOR_ID_C != MCU_VENDOR_ID)
#error "Mcu.c and Mcu.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and MCU header file are of the same Autosar version */
    /** @remarks Covers MCU110 */
    #if ((MCU_AR_MAJOR_VERSION_C != MCU_AR_MAJOR_VERSION) || \
         (MCU_AR_MINOR_VERSION_C != MCU_AR_MINOR_VERSION) || \
         (MCU_AR_PATCH_VERSION_C != MCU_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Mcu.c and Mcu.h are different"
    #endif
#endif
/* Check if source file and MCU header file are of the same Software version */
#if ((MCU_SW_MAJOR_VERSION_C != MCU_SW_MAJOR_VERSION) || \
     (MCU_SW_MINOR_VERSION_C != MCU_SW_MINOR_VERSION) || \
     (MCU_SW_PATCH_VERSION_C != MCU_SW_PATCH_VERSION))
#error "Software Version Numbers of Mcu.c and Mcu.h are different"
#endif

/* Check if source file and MCU_LLD header file are of the same Autosar version */
/* Check if source file and MCU header file are of the same vendor */
#if (MCU_VENDOR_ID_C != MCU_LLD_VENDOR_ID)
#error "Mcu.c and Mcu.h have different vendor ids"
#endif
/** @remarks Covers MCU110 */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((MCU_AR_MAJOR_VERSION_C != MCU_LLD_AR_MAJOR_VERSION) || \
         (MCU_AR_MINOR_VERSION_C != MCU_LLD_AR_MINOR_VERSION) || \
         (MCU_AR_PATCH_VERSION_C != MCU_LLD_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Mcu.c and Mcu_LLD.h are different"
    #endif
#endif
/* Check if source file and MCU_LLD header file are of the same Software version */
#if ((MCU_SW_MAJOR_VERSION_C != MCU_LLD_SW_MAJOR_VERSION) || \
     (MCU_SW_MINOR_VERSION_C != MCU_LLD_SW_MINOR_VERSION) || \
     (MCU_SW_PATCH_VERSION_C != MCU_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of Mcu.c and Mcu_LLD.h are different"
#endif

/* Check if source file and Dem header file are of the same version */
/** @remarks Covers MCU110 */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((MCU_AR_MAJOR_VERSION_C != DEM_AR_MAJOR_VERSION) || \
         (MCU_AR_MINOR_VERSION_C != DEM_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Mcu.c and Dem.h are different"
    #endif
#endif

/* Check if source file and DET header file are of the same version */ 
/**@remarks Covers MCU110 */
#if (MCU_DEV_ERROR_DETECT == STD_ON)
    #ifdef CHECK_AUTOSAR_VERSION
        #if ((MCU_AR_MAJOR_VERSION_C != DET_AR_MAJOR_VERSION) || \
             (MCU_AR_MINOR_VERSION_C != DET_AR_MINOR_VERSION))
        #error "AutoSar Version Numbers of Mcu.c and Det.h are different"
        #endif
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


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/
#define MCU_START_SEC_VAR_UNSPECIFIED
/** @note Violates MISRA-C: 2004  19.1, 19.15 - See @ref Mcu_c_REF_1, Mcu_c_REF_4*/
#include "MemMap.h"
/**
 * @brief   Pointer to initialization structure.
 *
 * @requirements             MCU126
 *
 * @api
 *
 * @remarks covers MCU126
 */
    P2CONST (Mcu_ConfigType, MCU_VAR, MCU_APPL_CONST) Mcu_Cfg_Ptr = NULL_PTR;

#define MCU_STOP_SEC_VAR_UNSPECIFIED
/** @note Violates MISRA-C: 2004  19.1, 19.15 - See @ref Mcu_c_REF_1, Mcu_c_REF_4*/
#include "MemMap.h"

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define MCU_START_SEC_CODE
/** @note Violates MISRA-C: 2004  19.1, 19.15 - See @ref Mcu_c_REF_1, Mcu_c_REF_4*/
#include "MemMap.h"

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

/**
 * @brief   MCU driver initialization function.
 * @details This routine initializes the MCU Driver.
 *          The intention of this function is to make the configuration setting 
 *          for power down,clock and ram sections visible within the MCU Driver.
 *
 * @param[in] ConfigPtr      Pointer to MCU configuration structure.
 *
 * @requirements             MCU153, MCU026, MCU126, MCU127, MCU013, MCU100, 
 *                           MCU101, MCU016, MCU018.
 *
 * @api
 *
 * @remarks Covers MCU153, MCU026, MCU126, MCU127, MCU013, MCU100, MCU101, MCU016, MCU018
 * @remarks Implements DMCU01000, DMCU17026, DMCU17028, DMCU17048
 */
     FUNC (void, MCU_CODE) Mcu_Init (P2CONST (Mcu_ConfigType, MCU_VAR, MCU_APPL_CONST) ConfigPtr)
    {
        Mcu_Cfg_Ptr = NULL_PTR; /** @remarks Covers MCU126, MCU127 */
#ifndef MCU_PRECOMPILE_SUPPORT
#if (MCU_DEV_ERROR_DETECT == STD_ON)    /** @remarks Covers MCU013, MCU100 */
        if (NULL_PTR == ConfigPtr) /** @remarks Covers MCU101 */
        {
            /** @remarks Covers MCU016, MCU018 */
            Det_ReportError ( (uint16) MCU_MODULE_ID, (uint8) MCU_INSTANCE_ID, \
            (uint8) MCU_INIT_ID, (uint8) MCU_E_PARAM_CONFIG);
        }
        else
        {
#endif
#endif
#ifdef MCU_PRECOMPILE_SUPPORT
            if (NULL_PTR == ConfigPtr)
            {
                Mcu_Cfg_Ptr = &MCU_INIT_CONFIG_PC;
            }
            else
#endif
            {
                /* Copy pointer to config structure */
                Mcu_Cfg_Ptr = ConfigPtr;
            }
            Mcu_LLD_Init (Mcu_Cfg_Ptr->McuLLD_Config);
#ifndef MCU_PRECOMPILE_SUPPORT
#if (MCU_DEV_ERROR_DETECT == STD_ON)    /** @remarks Covers MCU013, MCU100 */
        }
#endif
#endif
    }

/**
 * @brief   MCU driver initialization of ram sections.
 * @details Function intializes the ram section selected by RamSection parameter.
 *          The section base address, size and value to be written are provided 
 *          from the configuration structure.
 * @pre     Function requires an execution of @p Mcu_Init() before it can be 
 *          used, otherwise it reports error to @p DET and returns @p E_NOT_OK.
 * 
 * @param[in] RamSection     Index of ram section from config structure to be 
 *                           initialized.
 * @return                   Std_ReturnType.
 * @retval E_OK              Command has been accepted.
 * @retval E_NOT_OK          Command has not been accepted.
 *
 * @requirements             MCU154, MCU030, MCU011, MCU013, MCU100, MCU101, 
 *                           MCU016, MCU018, MCU125, MCU017, MCU021, MCU018.
 *
 * @api
 *
 * @remarks Covers MCU154, MCU030, MCU011, MCU013, MCU100, MCU101, MCU016, MCU018, MCU125, MCU017,
 *                 MCU021, MCU018
 * @remarks Implements DMCU01000, DMCU17034, DMCU17052
 */
    FUNC (Std_ReturnType, MCU_CODE) Mcu_InitRamSection (VAR (Mcu_RamSectionType, AUTOMATIC) \
        RamSection)
    {
        VAR (Std_ReturnType, AUTOMATIC) status = (Std_ReturnType)E_OK;
        VAR (uint32, AUTOMATIC) i;
        P2CONST (Mcu_RamConfigType, AUTOMATIC, MCU_APPL_DATA) pRam;

#if (MCU_DEV_ERROR_DETECT == STD_ON)    /** @remarks Covers MCU013, MCU100 */
        if (NULL_PTR == Mcu_Cfg_Ptr) /** @remarks Covers MCU101 */
        {
            /* Error: Mcu_Init() was not executed */
            /** @remarks Covers [MCU016] , MCU018, MCU125 */
            Det_ReportError ( (uint16) MCU_MODULE_ID, (uint8) MCU_INSTANCE_ID, \
            (uint8) MCU_INITRAMSECTION_ID, (uint8) MCU_E_UNINIT);
            status = (Std_ReturnType)E_NOT_OK; /** @remarks Covers MCU017 */
        }
        else if (RamSection >= Mcu_Cfg_Ptr->noRamSections) /** @remarks Covers MCU101 */
        {
            /* Error: function parameter out of range */
            /** @remarks Covers MCU016, MCU021 */
            Det_ReportError ( (uint16) MCU_MODULE_ID, (uint8) MCU_INSTANCE_ID, \
            (uint8) MCU_INITRAMSECTION_ID, (uint8) MCU_E_PARAM_RAMSECTION);
            status = (Std_ReturnType)E_NOT_OK; /** @remarks Covers MCU017 */
        }
        else if (NULL_PTR == Mcu_Cfg_Ptr->Mcu_RamConfig) /** @remarks Covers MCU018 */
        {
            /* Error: pointer to ram section in config structure is NULL */
            /** @remarks Covers MCU016 */
            Det_ReportError ( (uint16) MCU_MODULE_ID, (uint8) MCU_INSTANCE_ID, \
            (uint8) MCU_INITRAMSECTION_ID, (uint8) MCU_E_PARAM_RAMSECTION);
            status = (Std_ReturnType)E_NOT_OK; /** @remarks Covers MCU017 */
        }
        else
        {
#endif
            /** @note Violates MISRA-C: 2004 Required Rules 17.4 - See @ref Mcu_c_REF_2*/
            pRam = &Mcu_Cfg_Ptr->Mcu_RamConfig[RamSection];

            /* init ram section, 4 bytes per one pass through the loop */

            for (i = 0UL; i < ( (uint32) (pRam->RamSize) / (uint32) 4UL); i++)
            {
                /** @note Violates MISRA-C: 2004 Required Rules 17.4 - See @ref Mcu_c_REF_2*/
                (pRam->RamBaseAddr) [i] = pRam->RamDefaultValue;
            }

            for (i = 0UL; i < ( (uint32) (pRam->RamSize) / (uint32) 4UL); i++)
            {
                /** @note Violates MISRA-C: 2004 Required Rules 17.4 - See @ref Mcu_c_REF_2*/
                if ( (pRam->RamBaseAddr) [i] != pRam->RamDefaultValue)
                {
                    status = (Std_ReturnType)E_NOT_OK;
                    break;
                }
            }

#if (MCU_DEV_ERROR_DETECT == STD_ON)    /** @remarks Covers MCU013, MCU100 */
        }
#endif

        return status;
    }

/**
 * @brief   MCU driver clock initialization function.
 * @details This function intializes the PLL and MCU specific clock options. 
 *          The clock setting is provided from the configuration structure.
 * @pre     Function requires an execution of @p Mcu_Init() before it can be 
 *          used, otherwise it reports error to @p DET and returns @p E_NOT_OK.
 * 
 * @param[in] ClockSetting   Index of clock setting from config structure to be 
 *                           used.
 * @return                   Std_ReturnType.
 * @retval E_OK              Command has been accepted.
 * @retval E_NOT_OK          Command has not been accepted.
 *
 * @requirements             MCU155, MCU031, MCU107, MCU013, MCU100, MCU101, 
 *                           MCU016, MCU018, MCU019, MCU125, MCU112, MCU113, 
 *                           MCU017.
 *
 * @api
 *
 * @remarks Covers MCU155, MCU031, MCU107, MCU013, MCU100, MCU101, MCU016, MCU018, MCU019, MCU125,
 *                 MCU112, MCU113, MCU017
 * @remarks Implements DMCU01000, DMCU17030, DMCU17050, DMCU17032
 */
    FUNC (Std_ReturnType, MCU_CODE) Mcu_InitClock (VAR (Mcu_ClockType, AUTOMATIC) ClockSetting)
    {
        VAR (Std_ReturnType, AUTOMATIC) status = (Std_ReturnType)E_OK;

#if (MCU_DEV_ERROR_DETECT == STD_ON)   /** @remarks Covers MCU013, MCU100 */
        if (NULL_PTR == Mcu_Cfg_Ptr) /** @remarks Covers MCU101 */
        {
            /* Error: Mcu_Init() was not executed */
            /** @remarks Covers MCU016, MCU018, MCU125 */
            Det_ReportError ( (uint16) MCU_MODULE_ID, (uint8) MCU_INSTANCE_ID, \
            (uint8) MCU_INITCLOCK_ID, (uint8) MCU_E_UNINIT);
            status = (Std_ReturnType)E_NOT_OK; /** @remarks Covers MCU017 */
        }
        else if (ClockSetting >= Mcu_Cfg_Ptr->noClockSettings)
        {
            /* Error: function parameter out of range */
            /** @remarks Covers MCU016, MCU019 */
            Det_ReportError ( (uint16) MCU_MODULE_ID, (uint8) MCU_INSTANCE_ID, \
            (uint8) MCU_INITCLOCK_ID, (uint8) MCU_E_PARAM_CLOCK);
            status = (Std_ReturnType)E_NOT_OK; /** @remarks Covers MCU017 */
        }
        else if (NULL_PTR == Mcu_Cfg_Ptr->Mcu_ClockConfig)
        {
            /* Error: pointer to clock setting in config structure is NULL */
            /** @remarks Covers MCU016, MCU013 */
            /** @remarks Covers MCU163, MCU112 */
            Det_ReportError ( (uint16) MCU_MODULE_ID, (uint8) 0, (uint8) MCU_INITCLOCK_ID, \
            (uint8) MCU_E_PARAM_CLOCK);
            status = (Std_ReturnType)E_NOT_OK; /** @remarks Covers MCU017 */
        }
        else
        {
#endif
            /** @note Violates MISRA-C: 2004 Required Rules 17.4 - See @ref Mcu_c_REF_2*/
            status = Mcu_LLD_InitClock (&Mcu_Cfg_Ptr->Mcu_ClockConfig[ClockSetting], \
            Mcu_Cfg_Ptr->clkNotification);
#if (MCU_DEV_ERROR_DETECT == STD_ON)    /** @remarks Covers MCU013, MCU100 */
        }
#endif
        return status;
    }

/**
 * @brief   This function activates the main PLL as the system clock source.
 * @details This function sets the main PLL clock as the system clock and also 
 *          enables monitoring of the main PLL clock. A clock failure notification
 *          is generated when a mismatch with the PLL monitor occurs by 
 *          enabling the interrupts from the current clock setting. 
 * @pre     Function requires the status of the PLL has been detected as locked
 *          by the function @p Mcu_GetPllStatus.
 * @note    Function has to be executed if the MCU module needs a separate 
 *          request to activate the PLL clock after the PLL is locked. 
 *
 * @requirements             MCU156, MCU028, MCU053, MCU013, MCU100, MCU101, 
 *                           MCU016, MCU018, MCU125, MCU122.
 *
 * @api
 *
 * @remarks Covers MCU156, MCU028, MCU053, MCU013, MCU100, MCU101, MCU016, MCU018, MCU125, MCU122
 * @remarks Implements DMCU01000, DMCU17000, DMCU17002, DMCU17042
 */
    FUNC (void, MCU_CODE) Mcu_DistributePllClock (void)
    {
#if (MCU_DEV_ERROR_DETECT == STD_ON)    /** @remarks Covers MCU013, MCU100 */
        if (NULL_PTR == Mcu_Cfg_Ptr) /** @remarks Covers MCU101 */
        {
            /* Error: Mcu_Init() was not executed */
            /** @remarks Covers MCU016, MCU018, MCU125 */
            Det_ReportError ( (uint16) MCU_MODULE_ID, (uint8) MCU_INSTANCE_ID, \
            (uint8) MCU_DISTRIBUTEPLLCLOCK_ID, (uint8) MCU_E_UNINIT);
        }        
        else
        {
#endif   
            /** @note Violates MISRA-C: 2004 Required Rules 14.3 - See @ref Mcu_c_REF_3*/
            Mcu_LLD_DistributePllClock (Mcu_Cfg_Ptr->clkNotification);
#if (MCU_DEV_ERROR_DETECT == STD_ON)    /** @remarks Covers MCU013, MCU100 */
        }
#endif
    }

/**
 * @brief   This function returns the lock status of the PLL.
 * @details This function returns the @p MCU_PLL_STATUS_UNDEFINED if this 
 *          function is called prior to calling of the function Mcu_Init.
 * @pre     Function requires an execution of Mcu_Init() and Mcu_InitClock() 
            before it can be used, otherwise it reports error to DET.
 *
 * @return                           Mcu_PllStatusType.
 * @retval MCU_PLL_LOCKED            PLL is locked.
 * @retval MCU_PLL_UNLOCKED          PLL is unlocked.
 * @retval MCU_PLL_STATUS_UNDEFINED  PLL Status in unknown.
 *
 * @requirements                     MCU157, MCU008, MCU132, MCU013, MCU100, 
 *                                   MCU101, MCU016, MCU018
 *
 * @api
 *
 * @remarks Covers MCU157, MCU008, MCU132, MCU013, MCU100, MCU101, MCU016, MCU018
 * @remarks Implements DMCU01000, DMCU17004, DMCU17006, DMCU17008, DMCU17044
 */
    FUNC (Mcu_PllStatusType, MCU_CODE) Mcu_GetPllStatus (void)
    {
        /* Set status to MCU_PLL_STATUS_UNDEFINED */
        VAR (Mcu_PllStatusType, AUTOMATIC) status = MCU_PLL_STATUS_UNDEFINED; /*MCU132*/

#if (MCU_DEV_ERROR_DETECT == STD_ON)    /** @remarks Covers MCU013, MCU100 */
        if (NULL_PTR == Mcu_Cfg_Ptr) /** @remarks Covers MCU101 */
        {
            /* Error: Mcu_Init() was not executed */
            /** @remarks Covers MCU016 , MCU018, MCU125 */
            Det_ReportError ( (uint16) MCU_MODULE_ID, (uint8) MCU_INSTANCE_ID, \
            (uint8) MCU_GETPLLSTATUS_ID, (uint8) MCU_E_UNINIT);
        }
        else
        {
#endif
            status = Mcu_LLD_GetPllStatus();

#if (MCU_DEV_ERROR_DETECT == STD_ON)     /** @remarks Covers MCU013, MCU100 */
        }
#endif

        return status;
    }

/**
 * @brief   This function returns the reset reason.
 * @details This function returns the reset reason from the hardware and return
 *          this reason if supported by the hardware.
 * @pre     Function requires an execution of Mcu_Init() and Mcu_InitClock() 
            before it can be used, otherwise it returns @p MCU_RESET_UNDEFINED.
 * @note    If the hardware does not support the hardware detection of the reset
 *          reason, the function return value is always MCU_POWER_ON_RESET.
 * 
* @return                           One of the possible reset reasons defined in Mcu_ResetType.
*
 * @see                              Mcu_ResetType
 *
 * @requirements                     MCU158, MCU052, MCU005, MCU133, MCU125, 
 *                                   MCU013, MCU100, MCU101, MCU016, MCU018.
 *
 * @api
 *
 * @remarks Covers MCU158, MCU052, MCU005, MCU133, MCU125, MCU013, MCU100, MCU101, MCU016, MCU018
 * @remarks Implements DMCU01000, DMCU17016, DMCU17018, DMCU17020, DMCU17046
 */
    FUNC (Mcu_ResetType, MCU_CODE) Mcu_GetResetReason (void)
    {
        VAR (Mcu_ResetType, AUTOMATIC) ResetType = MCU_RESET_UNDEFINED; /** @remarks Covers MCU133*/

#if (MCU_DEV_ERROR_DETECT == STD_ON)   /** @remarks Covers MCU013, MCU100 */
        if (NULL_PTR == Mcu_Cfg_Ptr) /** @remarks Covers MCU101 */
        {
            /* Error: Mcu_Init() was not executed */
            /** @remarks Covers MCU016 , MCU018, MCU125 */
            Det_ReportError ( (uint16) MCU_MODULE_ID, (uint8) MCU_INSTANCE_ID, \
            (uint8) MCU_GETRESETREASON_ID, (uint8) MCU_E_UNINIT);
        }
        else
        {
#endif
            ResetType = Mcu_LLD_GetResetReason();
#if (MCU_DEV_ERROR_DETECT == STD_ON)   /** @remarks Covers MCU013, MCU100 */
        }
#endif

        return ResetType;
    }

/**
 * @brief   This function returns the raw reset value.
 * @details This function returns the raw reset value from the hardware register
 *          and return this reason if supported by the hardware.
 * @pre     Function requires an execution of @p Mcu_Init() before it can be 
 *          used, otherwise it returns an implementation specific vlue which 
 *          does not correspond to a valid value of the reset status register 
 *          and is not equal to 0.
 * @note    If the hardware does not support the hardware detection of the reset
 *          reason, the function return value is always 0x0.
 *
 * @return                   Mcu_RawResetType.
 *
 * @requirements             MCU159, MCU006, MCU125, MCU013, MCU100, MCU101, 
 *                           MCU016, MCU018.
 *
 * @api
 *
 * @remarks Covers MCU159, MCU006, MCU125, MCU013, MCU100, MCU101, MCU016, MCU018
 * @remarks Implements DMCU01000, DMCU17010, DMCU17012, DMCU17014, DMCU17044
 */
    FUNC (Mcu_RawResetType, MCU_CODE) Mcu_GetResetRawValue (void)
    {
        VAR (Mcu_RawResetType, AUTOMATIC) RawResetValue = MCU_RAW_RESET_DEFAULT;

#if (MCU_DEV_ERROR_DETECT == STD_ON)    /** @remarks Covers MCU013, MCU100 */
        if (NULL_PTR == Mcu_Cfg_Ptr) /** @remarks Covers MCU101 */
        {
            /* Error: Mcu_Init() was not executed */
            /** @remarks Covers MCU016 , MCU018, MCU125 */
            Det_ReportError ( (uint16) MCU_MODULE_ID, (uint8) MCU_INSTANCE_ID, \
            (uint8) MCU_GETRESETRAWVALUE_ID, (uint8) MCU_E_UNINIT);
        }
        else
        {
#endif
            RawResetValue = Mcu_LLD_GetResetRawValue();
#if (MCU_DEV_ERROR_DETECT == STD_ON)   /** @remarks Covers MCU013, MCU100 */
        }
#endif
        return RawResetValue;
    }

/**
 * @brief   This function performs a microcontroller reset.
 * @details This function performs the reset type which is configured in the  
 *          configuration set by using feature of the microcontroller.
 * @pre     Function requires an execution of @p Mcu_Init() before it can be 
 *          used.
 * @note    The function is available if the parameter @p McuPerformResetApi
 *          is set to @p TRUE.
 *
 * @requirements             MCU160, MCU007, MCU125, MCU013, MCU100, MCU101, 
 *                           MCU016, MCU018, MCU146.
 *
 * @api
 *
 * @remarks Covers MCU160, MCU007, MCU125, MCU013, MCU100, MCU101, MCU016, MCU018
 * @remarks Implements DMCU01000, DMCU17036, DMCU17038, DMCU17054
 */
    /** @remarks Covers MCU146 */
#if (MCU_PERFORM_RESET_API == STD_ON) || defined(__DOXYGEN__)

    FUNC (void, MCU_CODE) Mcu_PerformReset (void)
    {
#if (MCU_DEV_ERROR_DETECT == STD_ON)    /** @remarks Covers MCU013, MCU100 */
        if (NULL_PTR == Mcu_Cfg_Ptr) /** @remarks Covers MCU101 */
        {
            /* Error: Mcu_Init() was not executed */
            /** @remarks Covers MCU016 , MCU018, MCU125 */
            Det_ReportError ( (uint16) MCU_MODULE_ID, (uint8) MCU_INSTANCE_ID, \
            (uint8) MCU_PERFORMRESET_ID, (uint8) MCU_E_UNINIT);
        }
        else
        {
#endif

#if (MCU_RESET_CALLOUT_USED == STD_ON)
            /** @remarks Covers PR-MCAL-3133 */
            MCU_RESET_CALLOUT();
#endif
            Mcu_LLD_PerformReset();

#if (MCU_DEV_ERROR_DETECT == STD_ON)   /** @remarks Covers MCU013, MCU100 */
        }
#endif
    }
#endif /* #if MCU_PERFORM_RESET_API == STD_ON */

/**
 * @brief   This function sets the MCU power mode.
 * @details This function sets MCU power modes configured in the configuration
 *          set.
 * @pre     Function requires an execution of @p Mcu_Init() before it can be 
 *          used.
 * @note    If CPU is switched off, the function returs after it has performed 
 *          a wake-up.
 *
 * @param[in] McuMode        The parameter represents the MCU mode settings.
 *
 * @requirements             MCU161, MCU164, MCU001, MCU035, MCU013, MCU100, 
 *                           MCU101, MCU016, MCU018, MCU020, MCU125, MCU013, 
 *                           MCU163, MCU112
 *
 * @api
 *
 * @remarks Covers MCU161, MCU164, MCU001, MCU035, MCU013, MCU100, MCU101, MCU016, MCU018,
 *                 MCU020, MCU125, MCU013, MCU163, MCU112
 * @remarks Implements DMCU01000, DMCU13000, DMCU17056
 */
    FUNC (void, MCU_CODE) Mcu_SetMode (VAR (Mcu_ModeType, AUTOMATIC) McuMode)
    {
#if (MCU_DEV_ERROR_DETECT == STD_ON)   /** @remarks Covers MCU013, MCU100 */
        if (NULL_PTR == Mcu_Cfg_Ptr) /** @remarks Covers MCU101 */
        {
            /* Error: Mcu_Init() was not executed */
            /** @remarks Covers MCU016, MCU018, MCU125 */
            Det_ReportError ( (uint16) MCU_MODULE_ID, (uint8) MCU_INSTANCE_ID, \
            (uint8) MCU_SETMODE_ID, (uint8) MCU_E_UNINIT);
        }
        else if (McuMode >= Mcu_Cfg_Ptr->noModes) /** @remarks Covers MCU101 */
        {
            /* Error: McuMode parameter is out of valid range */
            /** @remarks Covers MCU016, MCU020 */
            Det_ReportError ( (uint16) MCU_MODULE_ID, (uint8) MCU_INSTANCE_ID, \
            (uint8) MCU_SETMODE_ID, (uint8) MCU_E_PARAM_MODE);
        }
        else if (NULL_PTR == Mcu_Cfg_Ptr->Mcu_ModeConfig)
        {
            /* Error: pointer to mode in config structure is NULL */
            /** @remarks Covers MCU016, MCU013 */
            /** @remarks Covers MCU163, MCU112 */
            Det_ReportError ( (uint16) MCU_MODULE_ID, (uint8) 0, (uint8) MCU_SETMODE_ID, \
            (uint8) MCU_E_PARAM_MODE);
        }
        else
        {
#endif
            Mcu_LLD_Apply_Mode(McuMode);
#if (MCU_DEV_ERROR_DETECT == STD_ON)   /** @remarks Covers MCU013, MCU100 */
        }
#endif
    }

/**
 * @brief   This function returns the version information for the MCU module.
 * @details The version information includes: 
 *          - Module Id, 
 *          - Vendor Id,
 *          - Vendor specific version numbers.
 *          .
 * @note    The function is pre-compile time configurable on/off by the 
 *          configuration parameter @p McuVersionInfoApi.
 *
 * @param[out] versioninfo   Pointer for storing the version information of this
 *                           module.
 *
 * @requirements             MCU103, MCU104, MCU162, MCU149.
 *
 * @api
 *
 * @remarks Covers MCU103, MCU104, MCU162, MCU149
 * @remarks Implements DMCU01000, DMCU17022, DMCU17024
 */
#if (MCU_VERSION_INFO_API == STD_ON) || defined(__DOXYGEN__)  /** @remarks Covers MCU104 */

    FUNC (void, MCU_CODE) Mcu_GetVersionInfo (P2VAR (Std_VersionInfoType, AUTOMATIC, \
        MCU_APPL_DATA) versioninfo)
    {
        (versioninfo)->vendorID = (uint16) MCU_VENDOR_ID;
        (versioninfo)->moduleID = (uint8) MCU_MODULE_ID;
        (versioninfo)->sw_major_version = (uint8) MCU_SW_MAJOR_VERSION;
        (versioninfo)->sw_minor_version = (uint8) MCU_SW_MINOR_VERSION;
        (versioninfo)->sw_patch_version = (uint8) MCU_SW_PATCH_VERSION;
        (versioninfo)->instanceID = (uint8) 0;
    }
#endif                          /* #if MCU_VERSION_INFO_API == STD_ON */
#define MCU_STOP_SEC_CODE
/** @note Violates MISRA-C: 2004  19.1, 19.15 - See @ref Mcu_c_REF_1, Mcu_c_REF_4*/
#include "MemMap.h"

#ifdef __cplusplus
}
#endif
/** @} */
