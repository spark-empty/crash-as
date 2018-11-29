/**
    @file    Spi_LLD.h
    @version 2.0.0

    @brief   AUTOSAR Spi - Brief description.
    @details Detailed description.

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
/**
@page misra_violations MISRA-C:2004 violations

@section Spi_LLD_h_REF_1
Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements
and comments before "#include". AUTOSAR imposes the specification of the
sections in which certain parts of the driver must be placed.
@section Spi_LLD_h_REF_2
Violates MISRA 2004 Rule 19.15, precautions shall be taken in order to prevent the content of a
header file to be included twice. The inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
*/

#ifndef SPI_LLD_H
#define SPI_LLD_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Dspi_LLD.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@brief Parameters that shall be published within the low level driver header file and also in the
       module's description file
@remarks Covers BSW00374, BSW00379, BSW00318
@{
*/
#define SPI_LLD_VENDOR_ID            43
#define SPI_LLD_MODULE_ID            83
#define SPI_LLD_AR_MAJOR_VERSION     3
#define SPI_LLD_AR_MINOR_VERSION     0
#define SPI_LLD_AR_PATCH_VERSION     0
#define SPI_LLD_SW_MAJOR_VERSION     2
#define SPI_LLD_SW_MINOR_VERSION     0
#define SPI_LLD_SW_PATCH_VERSION     0
/**@}*/
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

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

#if (SPI_CONFIG_VARIANT != SPI_VARIANT_PRECOMPILE)
#define SPI_START_CONFIG_DATA_UNSPECIFIED
/**
@file Spi_LLD.h
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_LLD_h_REF_1 & @ref Spi_LLD_h_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/


#define SPI_STOP_CONFIG_DATA_UNSPECIFIED
/**
@file Spi_LLD.h
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_LLD_h_REF_1 & @ref Spi_LLD_h_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/
#endif /* (SPI_CONFIG_VARIANT != SPI_VARIANT_PRECOMPILE) */

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /*SPI_LLD_H*/
