/**
    @file    Dspi_LLD_CfgEx.h
    @version 2.0.0

    @brief   AUTOSAR Spi - DSPI Configuration LLD header file.
    @details DSPI peripheral LLD configuration structures used by plugin generated configs.

    Project AUTOSAR 3.0 MCAL
    Patform PA
    Peripheral DSPI
    Dependencies 

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

#ifndef DSPI_LLD_CFGEX_H
#define DSPI_LLD_CFGEX_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** @remarks Covers BSW00374, BSW00379, BSW00318 */
/** @remarks Implements DSPI02180 */
#define SPI_AR_MAJOR_VERSION_LLD_CFGEX    3
#define SPI_AR_MINOR_VERSION_LLD_CFGEX    0
#define SPI_AR_PATCH_VERSION_LLD_CFGEX    0
#define SPI_SW_MAJOR_VERSION_LLD_CFGEX    2
#define SPI_SW_MINOR_VERSION_LLD_CFGEX    0
#define SPI_SW_PATCH_VERSION_LLD_CFGEX    0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and SPI configuration header file are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
  #if ((SPI_AR_MAJOR_VERSION_LLD_CFGEX != SPI_AR_MAJOR_VERSION_CFG) || \
       (SPI_AR_MINOR_VERSION_LLD_CFGEX != SPI_AR_MINOR_VERSION_CFG) || \
       (SPI_AR_PATCH_VERSION_LLD_CFGEX != SPI_AR_PATCH_VERSION_CFG))
  #error "AutoSar Version Numbers of Dspi_LLD_CfgEx.h and Spi_Cfg.h are different"
  #endif
#endif

/* Check if source file and SPI configuration header file are of the same software version */
#if ((SPI_SW_MAJOR_VERSION_LLD_CFGEX != SPI_SW_MAJOR_VERSION_CFG) || \
     (SPI_SW_MINOR_VERSION_LLD_CFGEX != SPI_SW_MINOR_VERSION_CFG))
#error "Software Version Numbers of Dspi_LLD_CfgEx.h and Spi_Cfg.h are different"
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

/** @brief Internal structure used to manage the channel attributes */
typedef struct
{
    VAR(uint32, SPI_VAR) CMD;             /**< @brief Channel attributes for CMD in PUSHR (selects CTAR to use). */
#if (SPI_FORCE_DATA_TYPE == STD_ON)    
    VAR(uint8, SPI_VAR)  DataWidth;       /**< @brief Channel attributes for datatype width. */
#endif    
} Spi_LLD_ChannelAttributesConfig;

/** @brief Internal structure used to manage the DSPI unit attributes */
typedef struct
{
    /** @brief Device attributes for CTARs */
#if (SPI_DUAL_CLOCK_MODE == STD_ON)
    VAR(uint32, SPI_VAR) CTAR[2];
#else
    VAR(uint32, SPI_VAR) CTAR;
#endif 
    /** @brief Device attributes for CMD in PUSHR */
    VAR(uint32, SPI_VAR) CMD;
    /** @brief Device CS idle setting */
    VAR(uint32, SPI_VAR) MCR;
} Spi_LLD_DeviceAttributesConfig;

/** @brief Internal structure used to manage LLD attributes */
typedef struct
{
    /** @brief Array of configuration channel attributes */
    P2CONST(Spi_LLD_ChannelAttributesConfig, AUTOMATIC, SPI_CONST)
                ChannelAttributesConfig;
    /** @brief Array of DSPI units attributes */
    P2CONST(Spi_LLD_DeviceAttributesConfig, AUTOMATIC, SPI_CONST)
                DeviceAttributesConfig;
} Spi_AttributesConfig;

#ifdef TSB_MODE_SUPPORTED
#if (SPI_TSB_MODE == STD_ON)
/** @brief Internal structure used to manage the TSB attributes */
typedef struct
{
    /** @brief Device attributes for DSICR*/
    VAR(uint32, SPI_VAR) DSICR;
    /** @brief Device attributes for DSICR1*/
    VAR(uint32, SPI_VAR) DSICR1;
#if (SPI_DUAL_CLOCK_MODE == STD_ON)
    VAR(uint32, SPI_VAR) CTAR[2];
#else
    VAR(uint32, SPI_VAR) CTAR;
#endif
} Spi_LLD_TSBAttributesConfig;
#endif /*SPI_TSB_MODE == STD_ON*/
#endif /*TSB_MODE_SUPPORTED*/
/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

 
#ifdef __cplusplus
}
#endif

#endif /* DSPI_LLD_CFGEX_H */

