/**
    @file        Std_Types.h
    @version     2.0.0

    @brief       AUTOSAR Base Standard types definition.
    @details     Standard types header file. It contains all types that are used across several 
                 modules of the basic software and that are platform and compiler independent
    
    Project      : AUTOSAR 3.0 MCAL
    Patform      : PA
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
@file        Std_Types.h
@remarks Covers STD003, STD004
@remarks Implements DBASE01000
*/

/** 
@page misra_violations MISRA-C:2004 violations

@section Std_Types_h_REF_1
Violates MISRA 2004 Required Rule 19.15, Repeated include file 
This comes from the order of includes in the .c file and from include dependencies. As a safe 
approach, any file must include all its dependencies. Header files are already protected against 
double inclusions.
*/

/**   
@file        Std_Types.h
@remarks Covers STD014
*/
#ifndef STD_TYPES_H
#define STD_TYPES_H

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/** 
@file        Std_Types.h
@brief Include platform types
@remarks Covers STD001, PLATFORM_FSL1, PLATFORM_FSL2
@note Violates MISRA 2004 Required Rule 19.15, Repeated include file - See @ref Std_Types_h_REF_1
*/
#include "Platform_Types.h"
/** 
@file        Std_Types.h
@brief Include compiler abstraction
@remarks Covers STD001, PLATFORM_FSL1, PLATFORM_FSL2, COMPILER052
@note Violates MISRA 2004 Required Rule 19.15, Repeated include file - See @ref Std_Types_h_REF_1
*/
#include "Compiler.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** 
@{
@brief Parameters that shall be published within the standard types header file and also in the 
       module's description file
@remarks Covers STD002
@remarks Implements DBASE01012
*/
#define STD_TYPES_VENDOR_ID        43
#define STD_TYPES_AR_MAJOR_VERSION 1
#define STD_TYPES_AR_MINOR_VERSION 2
#define STD_TYPES_AR_PATCH_VERSION 1
#define STD_TYPES_SW_MAJOR_VERSION 2
#define STD_TYPES_SW_MINOR_VERSION 0
#define STD_TYPES_SW_PATCH_VERSION 0
/**@}*/
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Platform_Types header file are of the same Autosar version */
    #if ((STD_TYPES_AR_MAJOR_VERSION != PLATFORM_AR_MAJOR_VERSION) || \
         (STD_TYPES_AR_MINOR_VERSION != PLATFORM_AR_MINOR_VERSION))
        #error "AutoSar Version Numbers of Std_Types.h and Platform_Types.h are different"
    #endif
         
    /* Check if source file and Compiler header file are of the same Autosar version */
    #if ((STD_TYPES_AR_MAJOR_VERSION != COMPILER_AR_MAJOR_VERSION) || \
         (STD_TYPES_AR_MINOR_VERSION != COMPILER_AR_MINOR_VERSION))
        #error "AutoSar Version Numbers of Std_Types.h and Compiler.h are different"
    #endif
#endif
/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/** 
@brief Physical state 5V or 3.3V
@remarks Covers STD007
@remarks Implements DBASE01006
*/
#define STD_HIGH    0x01
/** 
@brief Physical state 0V.
@remarks Covers STD007
@remarks Implements DBASE01008
*/
#define STD_LOW     0x00

/** 
@brief Logical state active.
@remarks Covers STD013
@remarks Implements DBASE01005
*/
#define STD_ACTIVE  0x01
/** 
@brief Logical state idle.
@remarks Covers STD013
@remarks Implements DBASE01007
*/
#define STD_IDLE    0x00

/** 
@brief ON State.
@remarks Covers STD010
@remarks Implements DBASE01010
*/
#define STD_ON      0x01
/** 
@brief OFF state.
@remarks Covers STD010
@remarks Implements DBASE01009
*/
#define STD_OFF     0x00

/** 
@brief Return code for failure/error.  
@remarks Covers STD006
@remarks Implements DBASE01003
*/
#define E_NOT_OK    0x01

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
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/** 
@brief Because E_OK is already defined within OSEK, the symbol E_OK has to be shared. To avoid name 
       clashes and redefinition problems, the symbols have to be defined in the following way 
       (approved within implementation).
@remarks Covers STD006
*/
#ifndef STATUSTYPEDEFINED 
    #define STATUSTYPEDEFINED 
    /** 
    @brief Success return code  
    @remarks Covers STD006
    @remarks Implements DBASE01004
    */
    #define E_OK      0x00
    /** 
    @brief This type is defined for OSEK compliance.
    @remarks Covers STD006
    @remarks Implements DBASE01011
    */
    typedef unsigned char StatusType;
#endif

/** 
@brief This type can be used as standard API return type which is shared between the RTE and the BSW modules.
@remarks Covers STD005, STD011
@remarks Implements DBASE01002
*/
typedef uint8 Std_ReturnType;

/** 
@brief This type shall be used to request the version of a BSW module using the "ModuleName"_GetVersionInfo() function.
@remarks Covers STD015
@remarks Implements DBASE01001
*/
typedef struct
{
    uint16  vendorID;               /**< @brief vendor ID */
    uint16  moduleID;               /**< @brief BSW module ID */
    uint8   instanceID;             /**< @brief BSW module instance ID */
    uint8   sw_major_version;       /**< @brief BSW module software major version */
    uint8   sw_minor_version;       /**< @brief BSW module software minor version */
    uint8   sw_patch_version;       /**< @brief BSW module software patch version */
} Std_VersionInfoType;

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/


#endif /* #ifndef STD_TYPES_H */
