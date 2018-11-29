/**
    @file        MemMap.h
    @version     2.0.0

    @brief       AUTOSAR Base - Memory mapping specification.
    @details     This document specifies mechanisms for the mapping of code and data to specific
                 memory sections via memory mapping file. For many ECUs and microcontroller platforms
                 it is of utmost necessity to be able to map code, variables and constants module
                 wise to specific memory sections.

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
@file        MemMap.h
@remarks Covers MEMMAP002,MEMMAP004,MEMMAP005,MEMMAP015,MEMMAP006,MEMMAP011,MEMMAP013
@remarks Implements DBASE02000
*/

/**
@page misra_violations MISRA-C:2004 violations

@section MemMap_h_REF_1
Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged
This is due to #undef MEMMAP_ERROR and #undef <section_type> and cannot be removed as it is
required by Autosar Specification - Specification of Memory Mapping.

@section MemMap_h_REF_2
Violates MISRA 2004 Required Rule 19.15, Repeated include file
This comes from the order of includes in the .c file and from include dependencies. As a safe
approach, any file must include all its dependencies. Header files are already protected against
double inclusions.

@section MemMap_h_REF_3
Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before '#include'
This comes from the order of includes in the .c. MemMap is required by AutoSAR to be included in
the middle of the source file(s).
*/

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/**
@file        MemMap.h
@note Violates MISRA 2004 Required Rule 19.15, Repeated include file  - See @ref MemMap_h_REF_2
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before '#include' - See @ref MemMap_h_REF_3
*/
#include "Compiler.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@{
@brief Parameters that shall be published within the memory map header file and also in the
       module's description file
@remarks Covers MEMMAP_FSL03
@remarks Implements DBASE02001
*/
#define MEMMAP_VENDOR_ID            43
#define MEMMAP_AR_MAJOR_VERSION     1
#define MEMMAP_AR_MINOR_VERSION     1
#define MEMMAP_AR_PATCH_VERSION     1
#define MEMMAP_SW_MAJOR_VERSION     2
#define MEMMAP_SW_MINOR_VERSION     0
#define MEMMAP_SW_PATCH_VERSION     0
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


/**
@brief Symbol used for checking correctness of the includes
@remarks Covers MEMMAP007
@remarks Implements DBASE02001
*/
#define MEMMAP_ERROR

/* [MEMMAP004]: Each AUTOSAR software module shall support the configuration */
/* of at least the following different memory types. It is allowed to add */
/* module specific sections as they are mapped and thus are configurable */
/* within the module's configuration file. The shortcut 'MSN' means 'module */
/* short name of BSW module list', e.g. 'EEP' or 'CAN'.  The shortcut 'SIZE' */
/* means the variable size. Possible SIZE postfixes are */
/* 8BIT, used for variables and constants of size 8 bit */
/* 16BIT, used for variables and constants of size 16 bit */
/* 32BIT, used for variables and constants of size 32 bit */
/* UNSPECIFIED, used for variables and constants of unknown size */

#ifndef AUTOSAR_OS_NOT_USED
    #ifdef OSMEMPROTECTION
        #include "osmemmap.h"
    #endif
#endif

/**************************************************************************************************/
/********************************************* GREENHILLS *****************************************/
/**************************************************************************************************/
#ifdef _GREENHILLS_C_MPC563XM_
/**************************************** ADC *******************************/
#ifdef ADC_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section const=".pbadc_cfg"
#endif

#ifdef ADC_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef ADC_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ADC_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ADC_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ADC_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ADC_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ADC_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** CAN *******************************/
#ifdef CAN_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section const=".pbcan_cfg"
#endif

#ifdef CAN_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef CAN_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef CAN_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef CAN_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef CAN_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef CAN_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef CAN_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** DEM *******************************/
#ifdef DEM_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section const=".pbdem_cfg"
#endif

#ifdef DEM_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef DEM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DEM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DEM_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DEM_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DEM_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DEM_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** DET *******************************/
#ifdef DET_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DET_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DET_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DET_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DET_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DET_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DET_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DET_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DET_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DET_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DET_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DET_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** DIO *******************************/
#ifdef DIO_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DIO_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DIO_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DIO_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DIO_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DIO_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DIO_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section  const ".pbdio_cfg"
#endif

#ifdef DIO_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

/**************************************** ECUM *******************************/
#ifdef ECUM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ECUM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ECUM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ECUM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ECUM_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ECUM_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ECUM_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ECUM_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** FEE *******************************/
#ifdef FEE_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FEE_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FEE_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FEE_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FEE_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FEE_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FEE_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FEE_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FEE_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FEE_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FEE_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FEE_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** FLS *******************************/
#ifdef FLS_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section const=".pbfls_cfg"
#endif

#ifdef FLS_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef FLS_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_START_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_START_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* define new section */
    #pragma ghs section text=".ramcode"
    /* force compiler to not introduce jumps to compiler prologue functions */
    #pragma ghs inlineprologue
#endif

#ifdef FLS_STOP_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_STOP_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* default section for CODE */
    #pragma ghs section
    /* disable the option to force compiler to not introduce jumps to compiler prologue functions */
    #pragma ghs noinlineprologue
#endif

#ifdef FLS_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_START_SEC_VAR_FAST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_START_SEC_VAR_FAST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_STOP_SEC_VAR_FAST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** FR *******************************/
#ifdef FR_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section const=".pbfr_cfg"
#endif

#ifdef FR_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef FR_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FR_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FR_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FR_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FR_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FR_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** GPT *******************************/
#ifdef GPT_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section const=".pbgpt_cfg"
#endif

#ifdef GPT_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef GPT_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef GPT_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef GPT_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef GPT_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef GPT_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef GPT_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** ICU *******************************/
#ifdef ICU_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section const=".pbicu_cfg"
#endif

#ifdef ICU_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef ICU_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ICU_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ICU_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ICU_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ICU_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ICU_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** LIN *******************************/
#ifdef LIN_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section const=".pblin_cfg"
#endif

#ifdef LIN_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef LIN_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef LIN_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef LIN_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef LIN_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef LIN_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef LIN_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** MCU *******************************/
#ifdef MCU_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section const=".pbmcu_cfg"
#endif

#ifdef MCU_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef MCU_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef MCU_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef MCU_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef MCU_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef MCU_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef MCU_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef MCU_START_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_START_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* define new section */
    #pragma ghs section text=".ramcode"
    /* force compiler to not introduce jumps to compiler prologue functions */
    #pragma ghs inlineprologue
#endif

#ifdef MCU_STOP_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_STOP_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* default section for CODE */
    #pragma ghs section
    /* disable the option to force compiler to not introduce jumps to compiler prologue functions */
    #pragma ghs noinlineprologue
#endif
/**************************************** PORT *******************************/
#ifdef PORT_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section const=".pbport_cfg"
#endif

#ifdef PORT_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef PORT_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PORT_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PORT_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PORT_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PORT_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PORT_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** PWM *******************************/
#ifdef PWM_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section const=".pbpwm_cfg"
#endif

#ifdef PWM_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef PWM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PWM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PWM_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PWM_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PWM_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PWM_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** SPI *******************************/
#ifdef SPI_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section const=".pbspi_cfg"
#endif

#ifdef SPI_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef SPI_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef SPI_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef SPI_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef SPI_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef SPI_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef SPI_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** WDG *******************************/
#ifdef WDG_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section const=".pbwdg_cfg"
#endif

#ifdef WDG_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef WDG_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef WDG_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef WDG_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef WDG_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef WDG_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef WDG_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/*************************************** IOHWAB ******************************/
#ifdef IOHWAB_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef IOHWAB_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef IOHWAB_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef IOHWAB_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef IOHWAB_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef IOHWAB_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef IOHWAB_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef IOHWAB_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef IOHWAB_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef IOHWAB_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef IOHWAB_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef IOHWAB_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** RAMTST *******************************/
#ifdef RAMTST_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef RAMTST_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef RAMTST_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef RAMTST_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef RAMTST_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef RAMTST_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef RAMTST_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef RAMTST_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef RAMTST_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef RAMTST_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef RAMTST_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef RAMTST_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/*************************************** SCHM ******************************/
#ifdef SCHM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SCHM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef SCHM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SCHM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************************************************************************/
/********************************************* DIAB ***********************************************/
/**************************************************************************************************/
#elif defined(_DIABDATA_C_MPC563XM_)
/**************************************** ADC *******************************/
#ifdef ADC_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const ".pbadc_cfg"
#endif

#ifdef ADC_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section
#endif

#ifdef ADC_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ADC_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ADC_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ADC_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ADC_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ADC_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** CAN *******************************/
#ifdef CAN_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const ".pbcan_cfg"
#endif

#ifdef CAN_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section
#endif

#ifdef CAN_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef CAN_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef CAN_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef CAN_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef CAN_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef CAN_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** DEM *******************************/
#ifdef DEM_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const ".pbdem_cfg"
#endif

#ifdef DEM_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section
#endif

#ifdef DEM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DEM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DEM_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DEM_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DEM_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DEM_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** DET *******************************/
#ifdef DET_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DET_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DET_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DET_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DET_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DET_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DET_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DET_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DET_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DET_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DET_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DET_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** DIO *******************************/
#ifdef DIO_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const ".pbdio_cfg"
#endif

#ifdef DIO_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section
#endif

#ifdef DIO_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DIO_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DIO_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DIO_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DIO_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DIO_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** ECUM *******************************/
#ifdef ECUM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ECUM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ECUM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ECUM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ECUM_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ECUM_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ECUM_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ECUM_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** FEE *******************************/
#ifdef FEE_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FEE_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FEE_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FEE_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FEE_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FEE_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FEE_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FEE_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FEE_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FEE_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FEE_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FEE_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** FLS *******************************/
#ifdef FLS_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const ".pbfls_cfg"
#endif

#ifdef FLS_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section
#endif

#ifdef FLS_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_START_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_START_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* define new section */
    #pragma section CODE ".ramcode" far-absolute
#endif

#ifdef FLS_STOP_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_STOP_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* default section for CODE */
    #pragma section CODE
#endif

#ifdef FLS_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_START_SEC_VAR_FAST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_START_SEC_VAR_FAST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_STOP_SEC_VAR_FAST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** FR *******************************/
#ifdef FR_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const ".pbfr_cfg"
#endif

#ifdef FR_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section
#endif

#ifdef FR_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FR_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FR_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FR_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FR_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FR_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** GPT *******************************/
#ifdef GPT_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const ".pbgpt_cfg"
#endif

#ifdef GPT_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section
#endif

#ifdef GPT_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef GPT_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef GPT_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef GPT_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef GPT_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef GPT_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** ICU *******************************/
#ifdef ICU_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const ".pbicu_cfg"
#endif

#ifdef ICU_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section
#endif

#ifdef ICU_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ICU_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ICU_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ICU_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ICU_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ICU_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** LIN *******************************/
#ifdef LIN_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const ".pblin_cfg"
#endif

#ifdef LIN_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section
#endif

#ifdef LIN_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef LIN_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef LIN_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef LIN_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef LIN_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef LIN_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** MCU *******************************/
#ifdef MCU_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const ".pbmcu_cfg"
#endif

#ifdef MCU_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section
#endif

#ifdef MCU_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef MCU_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef MCU_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef MCU_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef MCU_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef MCU_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef MCU_START_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_START_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* define new section */
    #pragma section CODE ".ramcode" far-absolute
#endif

#ifdef MCU_STOP_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_STOP_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* default section for CODE */
    #pragma section CODE
#endif
/**************************************** PORT *******************************/
#ifdef PORT_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const ".pbport_cfg"
#endif

#ifdef PORT_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section
#endif

#ifdef PORT_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PORT_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PORT_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PORT_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PORT_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PORT_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** PWM *******************************/
#ifdef PWM_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const ".pbpwm_cfg"
#endif

#ifdef PWM_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section
#endif

#ifdef PWM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PWM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PWM_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PWM_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PWM_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PWM_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** SPI *******************************/
#ifdef SPI_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const ".pbspi_cfg"
#endif

#ifdef SPI_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section
#endif

#ifdef SPI_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef SPI_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef SPI_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef SPI_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef SPI_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef SPI_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** WDG *******************************/
#ifdef WDG_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const ".pbwdg_cfg"
#endif

#ifdef WDG_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section
#endif

#ifdef WDG_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef WDG_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef WDG_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef WDG_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef WDG_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef WDG_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/*************************************** IOHWAB ******************************/
#ifdef IOHWAB_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef IOHWAB_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef IOHWAB_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef IOHWAB_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef IOHWAB_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef IOHWAB_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef IOHWAB_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef IOHWAB_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef IOHWAB_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef IOHWAB_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef IOHWAB_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef IOHWAB_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** RAMTST *******************************/
#ifdef RAMTST_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef RAMTST_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef RAMTST_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef RAMTST_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef RAMTST_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef RAMTST_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef RAMTST_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef RAMTST_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef RAMTST_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef RAMTST_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef RAMTST_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef RAMTST_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/*************************************** SCHM ******************************/
#ifdef SCHM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SCHM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef SCHM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SCHM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************************************************************************/
/******************************************* CodeWarrior ******************************************/
/**************************************************************************************************/
#elif defined(_CODEWARRIOR_C_MPC563XM_)
/**************************************** ADC *******************************/
#ifdef ADC_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section const ".pbadc_cfg" */
#endif

#ifdef ADC_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section */
#endif

#ifdef ADC_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ADC_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ADC_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ADC_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ADC_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ADC_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** CAN *******************************/
#ifdef CAN_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section const ".pbcan_cfg"  */
#endif

#ifdef CAN_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section */
#endif

#ifdef CAN_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef CAN_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef CAN_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef CAN_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef CAN_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef CAN_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** DEM *******************************/
#ifdef DEM_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section const ".pbdem_cfg"  */
#endif

#ifdef DEM_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section */
#endif

#ifdef DEM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DEM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DEM_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DEM_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DEM_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DEM_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** DET *******************************/
#ifdef DET_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DET_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DET_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DET_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DET_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DET_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DET_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DET_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DET_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DET_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DET_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DET_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** DIO *******************************/
#ifdef DIO_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section const ".pbdio_cfg" */
#endif

#ifdef DIO_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section */
#endif

#ifdef DIO_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DIO_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DIO_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DIO_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DIO_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DIO_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** ECUM *******************************/
#ifdef ECUM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ECUM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ECUM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ECUM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ECUM_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ECUM_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ECUM_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ECUM_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** FEE *******************************/
#ifdef FEE_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FEE_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FEE_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FEE_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FEE_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FEE_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FEE_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FEE_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FEE_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FEE_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FEE_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FEE_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** FLS *******************************/
#ifdef FLS_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section const ".pbfls_cfg" */
#endif

#ifdef FLS_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section  */
#endif

#ifdef FLS_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_START_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_START_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* define new section */
    #pragma section code_type ".ramcode"
#endif

#ifdef FLS_STOP_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_STOP_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* default section for CODE */
    #pragma section code_type ".text_vle"
#endif

#ifdef FLS_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_START_SEC_VAR_FAST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_START_SEC_VAR_FAST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_STOP_SEC_VAR_FAST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** FR *******************************/
#ifdef FR_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section const ".pbfr_cfg" */
#endif

#ifdef FR_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section */
#endif

#ifdef FR_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FR_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FR_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FR_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FR_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FR_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** GPT *******************************/
#ifdef GPT_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section const ".pbgpt_cfg"  */
#endif

#ifdef GPT_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section */
#endif

#ifdef GPT_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef GPT_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef GPT_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef GPT_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef GPT_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef GPT_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** ICU *******************************/
#ifdef ICU_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section const ".pbicu_cfg" */
#endif

#ifdef ICU_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section */
#endif

#ifdef ICU_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ICU_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ICU_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ICU_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ICU_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ICU_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** LIN *******************************/
#ifdef LIN_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section const ".pblin_cfg" */
#endif

#ifdef LIN_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section */
#endif

#ifdef LIN_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef LIN_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef LIN_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef LIN_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef LIN_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef LIN_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** MCU *******************************/
#ifdef MCU_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section const ".pbmcu_cfg" */
#endif

#ifdef MCU_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section */
#endif

#ifdef MCU_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef MCU_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef MCU_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef MCU_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef MCU_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef MCU_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef MCU_START_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_START_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* define new section */
    #pragma section code_type ".ramcode"
#endif

#ifdef MCU_STOP_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_STOP_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* default section for CODE */
    #pragma section code_type ".text_vle"
#endif
/**************************************** PORT *******************************/
#ifdef PORT_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section const ".pbport_cfg" */
#endif

#ifdef PORT_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section */
#endif

#ifdef PORT_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PORT_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PORT_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PORT_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PORT_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PORT_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** PWM *******************************/
#ifdef PWM_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section const ".pbpwm_cfg" */
#endif

#ifdef PWM_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section */
#endif

#ifdef PWM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PWM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PWM_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PWM_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PWM_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PWM_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** SPI *******************************/
#ifdef SPI_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section const ".pbspi_cfg" */
#endif

#ifdef SPI_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section */
#endif

#ifdef SPI_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef SPI_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef SPI_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef SPI_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef SPI_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef SPI_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** WDG *******************************/
#ifdef WDG_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section const ".pbwdg_cfg" */
#endif

#ifdef WDG_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* #pragma section */
#endif

#ifdef WDG_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef WDG_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef WDG_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef WDG_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef WDG_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef WDG_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/*************************************** IOHWAB ******************************/
#ifdef IOHWAB_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef IOHWAB_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef IOHWAB_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef IOHWAB_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef IOHWAB_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef IOHWAB_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef IOHWAB_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef IOHWAB_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef IOHWAB_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef IOHWAB_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef IOHWAB_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef IOHWAB_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** RAMTST *******************************/
#ifdef RAMTST_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef RAMTST_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef RAMTST_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef RAMTST_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef RAMTST_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef RAMTST_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef RAMTST_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef RAMTST_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef RAMTST_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef RAMTST_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef RAMTST_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef RAMTST_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/*************************************** SCHM ******************************/
#ifdef SCHM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SCHM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef SCHM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SCHM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************************************************************************/
/******************************************* Cosmic ***********************************************/
/**************************************************************************************************/
#elif defined(_COSMIC_C_MPC563XM_)
/**************************************** ADC *******************************/
#ifdef ADC_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {pbadc_cfg}
#endif

#ifdef ADC_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {}
#endif

#ifdef ADC_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ADC_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ADC_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ADC_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ADC_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ADC_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ADC_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** CAN *******************************/
#ifdef CAN_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {pbcan_cfg}
#endif

#ifdef CAN_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {}
#endif

#ifdef CAN_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef CAN_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef CAN_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef CAN_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef CAN_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef CAN_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef CAN_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** DEM *******************************/
#ifdef DEM_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {pbdem_cfg}
#endif

#ifdef DEM_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {}
#endif

#ifdef DEM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DEM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DEM_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DEM_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DEM_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DEM_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DEM_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** DET *******************************/
#ifdef DET_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DET_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DET_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DET_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DET_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DET_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DET_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DET_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DET_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DET_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DET_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DET_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** DIO *******************************/
#ifdef DIO_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {pbdio_cfg}
#endif

#ifdef DIO_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {}
#endif

#ifdef DIO_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DIO_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DIO_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DIO_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DIO_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef DIO_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef DIO_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** ECUM *******************************/
#ifdef ECUM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ECUM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ECUM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ECUM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ECUM_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ECUM_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ECUM_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ECUM_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** FEE *******************************/
#ifdef FEE_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FEE_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FEE_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FEE_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FEE_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FEE_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FEE_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FEE_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FEE_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FEE_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FEE_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FEE_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** FLS *******************************/
#ifdef FLS_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {pbfls_cfg}
#endif

#ifdef FLS_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {}
#endif

#ifdef FLS_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_START_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_START_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* define new section */
    #pragma section (ramcode)
#endif

#ifdef FLS_STOP_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_STOP_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* default section for CODE */
    #pragma section ()
#endif

#ifdef FLS_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_START_SEC_VAR_FAST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_START_SEC_VAR_FAST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FLS_STOP_SEC_VAR_FAST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** FR *******************************/
#ifdef FR_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {pbfr_cfg}
#endif

#ifdef FR_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {}
#endif

#ifdef FR_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FR_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FR_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FR_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FR_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef FR_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef FR_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** GPT *******************************/
#ifdef GPT_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {pbgpt_cfg}
#endif

#ifdef GPT_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {}
#endif

#ifdef GPT_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef GPT_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef GPT_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef GPT_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef GPT_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef GPT_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef GPT_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** ICU *******************************/
#ifdef ICU_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {pbicu_cfg}
#endif

#ifdef ICU_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {}
#endif

#ifdef ICU_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ICU_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ICU_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ICU_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ICU_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef ICU_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef ICU_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** LIN *******************************/
#ifdef LIN_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {pblin_cfg}
#endif

#ifdef LIN_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {}
#endif

#ifdef LIN_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef LIN_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef LIN_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef LIN_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef LIN_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef LIN_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef LIN_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** MCU *******************************/
#ifdef MCU_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {pbmcu_cfg}
#endif

#ifdef MCU_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {}
#endif

#ifdef MCU_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef MCU_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef MCU_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef MCU_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef MCU_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef MCU_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef MCU_START_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_START_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* define new section */
    #pragma section (ramcode)
#endif

#ifdef MCU_STOP_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MCU_STOP_SEC_RAMCODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* default section for CODE */
    #pragma section ()
#endif
/**************************************** PORT *******************************/
#ifdef PORT_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {pbport_cfg}
#endif

#ifdef PORT_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {}
#endif

#ifdef PORT_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PORT_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PORT_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PORT_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PORT_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PORT_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PORT_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** PWM *******************************/
#ifdef PWM_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {pbpwm_cfg}
#endif

#ifdef PWM_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {}
#endif

#ifdef PWM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PWM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PWM_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PWM_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PWM_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef PWM_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef PWM_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** SPI *******************************/
#ifdef SPI_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {pbspi_cfg}
#endif

#ifdef SPI_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {}
#endif

#ifdef SPI_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef SPI_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef SPI_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef SPI_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef SPI_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef SPI_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SPI_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** WDG *******************************/
#ifdef WDG_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_START_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {pbwdg_cfg}
#endif

#ifdef WDG_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_STOP_CONFIG_DATA_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    #pragma section const {}
#endif

#ifdef WDG_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef WDG_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef WDG_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef WDG_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef WDG_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef WDG_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef WDG_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/*************************************** IOHWAB ******************************/
#ifdef IOHWAB_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef IOHWAB_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef IOHWAB_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef IOHWAB_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef IOHWAB_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef IOHWAB_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef IOHWAB_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef IOHWAB_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef IOHWAB_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef IOHWAB_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef IOHWAB_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef IOHWAB_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/**************************************** RAMTST *******************************/
#ifdef RAMTST_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef RAMTST_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef RAMTST_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef RAMTST_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef RAMTST_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef RAMTST_START_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef RAMTST_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef RAMTST_STOP_SEC_VAR_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef RAMTST_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef RAMTST_START_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef RAMTST_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef RAMTST_STOP_SEC_CONST_UNSPECIFIED
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

/*************************************** SCHM ******************************/
#ifdef SCHM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SCHM_START_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#ifdef SCHM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef SCHM_STOP_SEC_CODE
    /**
    @file MemMap.h
    @note Violates MISRA 2004 Required Rule 19.6, use of '#undef' is discouraged - See @ref MemMap_h_REF_1
    */
    #undef MEMMAP_ERROR
    /* no definition -> default compiler settings are used */
#endif

#endif


/**************************************************************************************************/
/****************************************** Report error ******************************************/
/**************************************************************************************************/
#ifdef MEMMAP_ERROR
    #error "MemMap.h, no valid memory mapping symbol defined."
#endif

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
