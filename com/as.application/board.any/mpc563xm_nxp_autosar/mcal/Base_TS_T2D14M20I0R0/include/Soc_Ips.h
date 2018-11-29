/**
    @file        Soc_Ips.h
    @version     2.0.0

    @brief       AUTOSAR Base - IP module versions.
    @details     The IP modules versions used on PA hardware platform and
                 IP specific defines

    Project      : AUTOSAR 3.0 MCAL
    Platform     : PA
    Peripheral   : XPC563XM
    Dependencies : none

    Autosar Version       : 3.0.0
    Autosar Revision      : ASR_REL_3_0_REV_0003
    Autosar Conf. Variant :
    Software Version      : 2.0.0
    Build Version         : XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223

    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
    All Rights Reserved.
*/
/*==================================================================================================
==================================================================================================*/

/**
@file        Soc_Ips.h
@remarks Implements DBASE08000
*/

/**
@page misra_violations MISRA-C:2004 violations

@section Soc_Ips_h_REF_1
Violates MISRA 2004 Required Rule 19.15, Repeated include file
This comes from the order of includes in the .c file and from include dependencies. As a safe
approach, any file must include all its dependencies. Header files are already protected against
double inclusions.
*/

#ifndef SOC_IPS_H
#define SOC_IPS_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/**
@file        Soc_Ips.h
@brief Include platform types
@note Violates MISRA 2004 Required Rule 19.15, Repeated include file - See @ref Soc_Ips_h_REF_1
*/
#include "Platform_Types.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/**
@brief PA IP Versions
@remarks Implements DBASE08001
@details FLASH IP Version: STA1_FLH7_544K_C90FG@v3.4.a on Monaco
*/
#define IPV_FLASH                0x15364000UL

/**
@brief PA IP Versions
@remarks Implements DBASE08001
@details SIU IP Version: siu_ipi.00.02.08.07
*/
#define IPV_SIU                 0x00020807UL

/**
@brief eSCI P Version: eSCI v07.02.01.01
@details XPC563XM IP Version
@remarks Implements DBASE08001
*/
#define IPV_ESCI                0x07020101UL

/**
@brief PA IP Versions
@remarks Implements DBASE08001
@details FMPLL IP Version: 01010200
*/
#define IPV_FMPLL               0x01010200UL

/**
@brief Number of DMA controllers available
@details XPC563XM Platform Defines/Configurations
*/
#define DMA_NB_CONTROLLERS           (0x01U)
/**
@brief Number of DMA channels available
@details XPC563XM Platform Defines/Configurations
*/
#define DMA_NB_CHANNELS              (0x20U)

/**
@{
@brief Defines which AutoSAR drivers use the common eDMA IP driver
*/
#define LIN_USE_DMA_LLD         (STD_ON)
#define ADC_USE_DMA_LLD         (STD_ON)
#define SPI_USE_DMA_LLD         (STD_ON)
#define MCU_USE_DMA_LLD         (STD_ON)
/**@}*/

/**
@brief EMIOS interrupts are handled by common ISRs
@details XPC563XM Platform specific Defines/Configurations for EMIOS
*/
#define EMIOS_COMMON_ISR_HANDLER     (STD_OFF)
/**
@brief EMIOS UCDIS register is available
@details XPC563XM Platform specific Defines/Configurations for EMIOS
*/
#define EMIOS_UCDIS_AVAILABLE        (STD_ON)

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

#ifdef __cplusplus
}
#endif

#endif /* #ifndef SOC_IPS_H*/

