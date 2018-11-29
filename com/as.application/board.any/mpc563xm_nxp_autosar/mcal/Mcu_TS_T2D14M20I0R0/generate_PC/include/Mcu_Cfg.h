/**
    @file    Mcu_Cfg.h
    @version 2.0.0

    @brief   AUTOSAR Mcu - Mcu configuration header file.
    @details This file contains mcu configuration defines.

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
#ifndef MCU_CFG_H
#define MCU_CFG_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Dma_LLD.h"
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** @remarks Covers BSW00374, BSW00379, BSW00318 */
#define MCU_VENDOR_ID_CFG         43
#define MCU_AR_MAJOR_VERSION_CFG  3
#define MCU_AR_MINOR_VERSION_CFG  0
#define MCU_AR_PATCH_VERSION_CFG  0
#define MCU_SW_MAJOR_VERSION_CFG  2
#define MCU_SW_MINOR_VERSION_CFG  0
#define MCU_SW_PATCH_VERSION_CFG  0

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

    /**
     * @brief   Development error detection enabled/disabled (STD_ON/STD_OFF)      
     *
     * @requirements         MCU118.
     * 
     * @api
     */
    /** @remarks Covers MCU118 */
#define MCU_DEV_ERROR_DETECT                    ([!IF "McuGeneralConfiguration/McuDevErrorDetect"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

    /**
     * @brief   version info API enabled/disabled (STD_ON/STD_OFF)
     *
     * @api
     */
#define MCU_VERSION_INFO_API                    ([!IF "McuGeneralConfiguration/McuVersionInfoApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

    /**
     * @brief   the Api function Mcu_PerformReset is/isn't available (STD_ON/STD_OFF)
     *
     * @api
     */
#define MCU_PERFORM_RESET_API                   ([!IF "McuGeneralConfiguration/McuPerformResetApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

    /**
     * @brief   the Api function Mcu_Flash_Configure is/isn't available (STD_ON/STD_OFF)
     *
     * @api
     */
#define MCU_FLASH_CONFIGURATION_USED        ([!IF "McuGeneralConfiguration/McuConfigureFlash = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

    /**
     * @brief   the ISR Mcu_ClockLoss_ISR is/isn't available (STD_ON/STD_OFF)
     *
     * @api
     */
#define MCU_CLOCKLOSS_ISR_USED                  ([!IF "count(McuModuleConfiguration/*/McuInterrupt/McuClockLoss[. = 'true'])>=1"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

    /**
     * @brief   the ISR Mcu_LockLoss_ISR complete is/isn't available (STD_ON/STD_OFF)
     *
     * @api
     */
#define MCU_LOCKLOSS_ISR_USED                   ([!IF "count(McuModuleConfiguration/*/McuInterrupt/McuLockLoss[. = 'true'])>=1"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

    /**
     * @brief   if enter low power mode transition enabled (STD_ON/STD_OFF)
     *
     * @api
     */
#define MCU_ENTER_LOW_POWER_MODE     ([!IF "McuGeneralConfiguration/McuEnterLowPowerMode = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

    /**
     * @brief   the callout reset is/isn't available (STD_ON/STD_OFF)
     *
     * @api
     */
#define MCU_RESET_CALLOUT_USED                  ([!IF "node:exists('McuGeneralConfiguration/McuCalloutBeforePerformReset')"!][!IF "McuGeneralConfiguration/McuCalloutBeforePerformReset"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!ELSE!]STD_OFF[!ENDIF!])

[!IF "node:exists('McuGeneralConfiguration/McuCalloutBeforePerformReset')"!]
[!IF "McuGeneralConfiguration/McuCalloutBeforePerformReset"!]
/* the callout reset */
#define MCU_RESET_CALLOUT ([!"McuGeneralConfiguration/McuPerformResetCallout"!])
[!ENDIF!]
[!ENDIF!]

[!NOCODE!][!//

/* Indicates that default configuration is supported */[!//
[!CODE!][!//
[!IF "IMPLEMENTATION_CONFIG_VARIANT ='VariantPreCompile'"!][!//
/* Mcu Pre Compile Switch */
#define MCU_PRECOMPILE_SUPPORT
[!ELSE!][!//
[!ENDIF!][!//
[!ENDCODE!][!//

[!ENDNOCODE!][!//
[!//

[!IF "IMPLEMENTATION_CONFIG_VARIANT='VariantPostBuild'"!][!//
/* Extern declarations */
#define MCU_CFG_EXTERNS
[!NOCODE!][!VAR "var_count1"="num:i(count(McuModuleConfiguration/*))"!][!VAR "w"="0"!][!ENDNOCODE!][!//
#define MCU_CONF_PB \
[!LOOP "McuModuleConfiguration/*"!][!VAR "w"="$w + 1"!] extern CONST(Mcu_ConfigType, MCU_CONST)  [!"node:name(.)"!];[!IF "$w < $var_count1"!]\[!ENDIF!]
[!ENDLOOP!]
[!ELSE!]
#define MCU_CONF_PC extern CONST(Mcu_ConfigType, MCU_CONST) MCU_INIT_CONFIG_PC;
[!ENDIF!]

[!LOOP "McuModuleConfiguration/*"!][!//
/** @brief associate index to McuClockReferencePoint settings */
[!LOOP "McuClockSettingConfig/McuClockReferencePoint/*"!][!//
#define [!"name(.)"!]   [!"@index"!]
[!ENDLOOP!][!//

/** @brief associate index to McuModeSettingConf settings */
[!LOOP "McuModeSettingConf/*"!][!//
#define [!"name(.)"!]   [!"@index"!]
[!ENDLOOP!][!//

/** @brief associate index to McuRamSectorSettingConf settings */
[!LOOP "McuRamSectorSettingConf/*"!][!//
#define [!"name(.)"!]   [!"@index"!]
[!ENDLOOP!][!//

[!ENDLOOP!]
/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
                                             ENUMS
==================================================================================================*/
    /**
     * @brief   Clock failure notification.     
     * @details Enable/disable clock failure interrupt generated by the MCU.
     *
     * @requirements         MCU054.
     * 
     * @api
     */
    /** @remarks Covers MCU054 */
    typedef enum
    {
        MCU_CLOCKNOTIFICATION_DISABLE = 0,
        MCU_CLOCKNOTIFICATION_ENABLE
    } Mcu_ClockNotificationType;
    /**
     * @brief   Lock status of the PLL.
     * @details This is a status value returned by the function Mcu_GettPllStatus
     * of the MCU module.
     *
     * @requirements         MCU054. 
     *
     * @api
     */
    typedef enum
    {
        MCU_PLL_LOCKED = 0,
        MCU_PLL_UNLOCKED,
        MCU_PLL_STATUS_UNDEFINED
    } Mcu_PllStatusType;

    /**
     * @brief   Contains the subset of reset sources.     
     *
     * @requirements         MCU134.
     * 
     * @api  
     */
    /** @remarks Covers MCU134 */
    typedef enum
    {
     /**
      * @brief   Power On Reset event.
      */
        MCU_POWER_ON_RESET = 0,
     /**
      * @brief   External Reset event.
      */
        MCU_EXTERNAL_RESET,
     /**
      * @brief   Loss of Lock Reset event.
      */
        MCU_LOSS_OF_LOCK_RESET,
     /**
      * @brief   Loss of Clock Reset event.
      */
        MCU_LOSS_OF_CLOCK_RESET,
     /**
      * @brief   Watchdog Reset event.
      */
        MCU_WATCHDOG_RESET,
     /**
      * @brief   Checkstop Reset event.
      */
        MCU_CHECKSTOP_RESET,
     /**
      * @brief   Software Watchdog Timer Reset event.
      */
        MCU_SW_WATCHDOG_RESET,
     /**
      * @brief   Software System Reset event.
      */
        MCU_SW_RESET,
     /**
      * @brief   Software External Reset event
      */
        MCU_SW_EXT_RESET,
     /**
      * @brief   Undefined Reset event
      */
        MCU_RESET_UNDEFINED
    } Mcu_ResetType;
/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
    /**
     * @brief   Identifies a RAM section in the configuration structure.  
     * @details The range is dependent on the number of RAM sections provided
     *          in the configuration structure.
     * 
     * @api  
     */
    typedef uint32 Mcu_RamSectionType;
    /**
     * @brief   Identifies a MCU mode in the configuration structure.   
     * @details The range is dependent on the the number of MCU modes provided
     *          in the configuration structure.
     * 
     * @api
     */
    typedef uint32 Mcu_ModeType;
    /**
     * @brief   Identifies a clock setting in the configuration structure. 
     * @details The range is dependent on the the number of clock settings
     *           provided in the configuration structure.
     * 
     * @api
     */
    typedef uint32 Mcu_ClockType;
    /**
     * @brief   Identifies the reset reason in raw status register format. 
     * 
     * @api
     */
    typedef uint32 Mcu_RawResetType;

    /**
     * @brief   Definition of a RAM section within the configuration structure.
     * 
     * @requirements         MCU030.
     *
     * @api
     */
    typedef struct
    {
    /**
     * @brief   RAM section base address.
     */
        P2VAR (uint32, MCU_VAR, MCU_APPL_VAR) RamBaseAddr;
    /**
     * @brief   RAM section size.
     */
        VAR (uint32, MCU_VAR) RamSize;
    /**
     * @brief   RAM default value.
     */
        VAR (uint32, MCU_VAR) RamDefaultValue;
    } Mcu_RamConfigType;
    /** @remarks Covers MCU165 */
    /** @brief Modes configuration structure */
    typedef struct
    {
        VAR (uint32, MCU_VAR) HLTACKTimeOut;
        VAR (uint32, MCU_VAR) SIU_Hlt;
    } Mcu_ModeConfigType;

    /**
     * @brief   Definition of a MCU mode section in the configuration structure.
     * @details Specifies the system behaviour during the selected target mode. 
     * 
     * @requirements         MCU035.
     *
     * @api
     */
    /** @remarks Covers MCU035 */
    typedef struct
    {
    /**
     * @brief   Specifies if the system clock divider is/isn't bypassed and the 
     *          system clock divider. It contains the configuration of the 
     *          SIU_SYSDIV register.
     */
        VAR (uint32, MCU_VAR) SystemClockParam;
    /**
     * @brief   Specifies the timing relationship between the system clock and 
     *          the external clock CLKOUT. It contains the configuration of the 
     *          SIU_ECCR register.
     */
        VAR (uint32, MCU_VAR) ExternalClockParam;
    /**
     * @brief   Specifies the configuration of the PLL in terms of FMPLL 
     *          Pre-divider, FMPLL feedback loop divider, FMPLL operating mode 
     *          (Bypass/normal mode). It contains the configuration of the 
     *          ESYNCR1 register.
     */
        VAR (uint32, MCU_VAR) Pll_ESYNCR1;
    /**
     * @brief   Specifies the configuration of the PLL in terms of FMPLL 
     *          output divider, monitor of loss-of-clock, loss-of-lock reset,
     *          loss-of-clock reset, loss-of-lock interrupt request, Loss-of-clock
     *          interrupt request It contains the configuration of the 
     *          ESYNCR2 register.
     */
        VAR (uint32, MCU_VAR) Pll_ESYNCR2;
    /**
     * @brief   Specifies the configuration of the PLL modulation in terms of 
     *          modulation period, modulation depth, modulation selection  FMPLL 
     *          It contains the configuration of the SYNFMMR register.
     */
        VAR (uint32, MCU_VAR) Pll_SYNFMMR;
    /**
     * @brief   Specifies the configuration of the eMIOS200 block.
     *          It contains the configuration of the EMIOS_MCR register.
     */
        VAR (uint32, MCU_VAR) EMIOS_MCR;
    /**
     * @brief   Specifies the global configuration of all attached flash arrays.
     *          It contains the configuration of the BIUCR register.
     */
        VAR (uint32, MCU_VAR) FLASH_BIUCR; /* BIUCR system clock dependent  values*/
    } Mcu_ClockConfigType;
[!CODE!][!//
[!SELECT "as:modconf('Resource')[1]"!][!//
/**
 * @brief   Mcu driver configuration structure.
 * 
 * @requirements             MCU131
 *
 * @api
 */    
    /** @remarks Covers MCU131 */
    typedef struct
    {
      /** 
       * @brief   Field for the RESET Options.
       * @details Allows software to generate a software system reset or
       *          a software external reset or a checkstop reset.
       * @note    It affects SIU_SRCR register.
       *
       * @requirements       MCU131        
       */
      /** @remarks Covers MCU131*/
        VAR (uint32, MCU_VAR) SWReseType;
    /**
     * @brief   Specifies the configuration of the DMA.
     */
        VAR (Dma_ConfigType, MCU_VAR) DmaConfig;
    /**
     * @brief   Specifies the configuration of the flash in terms of Address 
     *          pipelining control, Write Wait State Control and Read Wait State
     *          Control. It affects the value of the BIUCR register
     */        
        VAR (uint32, MCU_VAR) flashBIUCR0;
    /**
     * @brief   Defines the logical partitioning of the four page buffers.
     *          It affects the value of the BIUCR2 register
     */
        VAR (uint32, MCU_VAR) flashBIUCR1;
    /**
     * @brief   Controls the read or write access permissions to the flash. 
     *          It affects the value of the BIUAPR register
     */
        VAR (uint32, MCU_VAR) flashBIUAPR;       
    } McuLLD_ConfigType;
[!ENDSELECT!][!//
[!ENDCODE!]
/**
 * @brief   The structure contains the initialization data for the MCU driver.
 * @details A pointer to such a structure is provided to the MCU initialization
 *          routines for configuration.
 * 
 * @requirements             MCU131, MCU054, MCU035, MCU031, MCU030
 *
 * @api
*/
    /** @remarks Covers MCU131, MCU054, MCU035, MCU031, MCU030 */
    /** @brief Mcu driver configuration structure */
    typedef struct
    {
      /**
       * @brief   Clock failure notification.     
       * @details Enable/disable clock failure interrupt generated by the MCU.
       */
        VAR (Mcu_ClockNotificationType, MCU_VAR) clkNotification;
      /**
       * @brief   Identifies a RAM section in the configuration structure.  
       * @details The range is dependent on the number of RAM sections provided
       *          in the configuration structure.
       */
        VAR (Mcu_RamSectionType, MCU_VAR) noRamSections;
      /**
       * @brief   Identifies a MCU mode in the configuration structure.   
       * @details The range is dependent on the the number of MCU modes provided
       *          in the configuration structure.
       */  
        VAR (Mcu_ModeType, MCU_VAR) noModes;
      /**
       * @brief   Identifies a clock setting in the configuration structure. 
       * @details The range is dependent on the the number of clock settings
       *           provided in the configuration structure.
       */
        VAR (Mcu_ClockType, MCU_VAR) noClockSettings;
        VAR (uint32, MCU_VAR) McuTimeout;        
      /**
       * @brief   Identifies a Ram setting in the configuration structure. 
       */
        P2CONST (Mcu_RamConfigType, MCU_VAR, MCU_APPL_CONST) Mcu_RamConfig;
      /**
       * @brief   Identifies a mode configuration in the configuration structure. 
       */
        P2CONST (Mcu_ModeConfigType, MCU_VAR, MCU_APPL_CONST) Mcu_ModeConfig;
      /**
       * @brief   Identifies a system clock configuration.
       */
        P2CONST (Mcu_ClockConfigType, MCU_VAR, MCU_APPL_CONST) Mcu_ClockConfig;
      /**
       * @brief   Mcu driver configuration.
       */
        P2CONST (McuLLD_ConfigType, MCU_VAR, MCU_APPL_CONST) McuLLD_Config;
    } Mcu_ConfigType;
    /** @remarks Covers MCU108 */
#ifndef MCU_PRECOMPILE_SUPPORT
    MCU_CONF_PB
#else
    MCU_CONF_PC
#endif

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and dma types header file are of the same vendor */
#if (MCU_VENDOR_ID_CFG != DMA_VENDOR_ID)
    #error "Mcu_Cfg.h and Dma_types.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if Dma_types and dma types  header file are of the same Autosar version */
    #if ((MCU_AR_MAJOR_VERSION_CFG != DMA_AR_MAJOR_VERSION) || \
         (MCU_AR_MINOR_VERSION_CFG != DMA_MINOR_VERSION) || \
         (MCU_AR_PATCH_VERSION_CFG != DMA_PATCH_VERSION))
    #error "AutoSar Version Numbers of Mcu_Cfg.h and Dma_types.h are different"
    #endif
#endif
/* Check if Dma_types and dma types header file are of the same software version */
#if ((MCU_SW_MAJOR_VERSION_CFG != DMA_SW_MAJOR_VERSION) || \
     (MCU_SW_MINOR_VERSION_CFG != DMA_SW_MINOR_VERSION) || \
     (MCU_SW_PATCH_VERSION_CFG != DMA_SW_PATCH_VERSION))
#error "Software Version Numbers of Mcu_Cfg.h and Dma_types.h are different"
#endif
/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
[!IF "node:exists('McuGeneralConfiguration/McuCalloutBeforePerformReset')"!]
[!IF "McuGeneralConfiguration/McuCalloutBeforePerformReset"!]
extern FUNC(void,MCU_CODE) MCU_RESET_CALLOUT(void);
[!ENDIF!]
[!ENDIF!]

#ifdef __cplusplus
}
#endif

#endif /* #ifndef MCU_CFG_H */
/** @} */
