/**
    @file        modules.h
    @version     2.0.0

    @brief       AUTOSAR Base Project configuration.
    @details     Header file describing all Autosar MCAL modules present in the current project.
    
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
@file        modules.h
@remarks Implements 
*/

#ifndef MODULES_H
#define MODULES_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/** 
@file        modules.h
@brief Include Standard types & defines
*/
#include "Std_Types.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/** 
@{
@brief Parameters that shall be published within the modules header file.
       The integration of incompatible files shall be avoided.
*/
#define MODULES_VENDOR_ID               43
#define MODULES_AR_MAJOR_VERSION_H      3
#define MODULES_AR_MINOR_VERSION_H      0
#define MODULES_AR_PATCH_VERSION_H      0
#define MODULES_SW_MAJOR_VERSION_H      2
#define MODULES_SW_MINOR_VERSION_H      0
#define MODULES_SW_PATCH_VERSION_H      0
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
@brief This constant used for other modules to check if ADC is present in the project.  
*/
#define USE_ADC_MODULE              (STD_ON)

/** 
@brief This constant used for other modules to check if CAN is present in the project.  
*/
#define USE_CAN_MODULE              (STD_ON)

/** 
@brief This constant used for other modules to check if DIO is present in the project.  
*/
#define USE_DIO_MODULE              (STD_ON)

/** 
@brief This constant used for other modules to check if FEE is present in the project.  
*/
#define USE_FEE_MODULE              (STD_ON)

/** 
@brief This constant used for other modules to check if FLS is present in the project.  
*/
#define USE_FLS_MODULE              (STD_ON)

/** 
@brief This constant used for other modules to check if Fr is present in the project.  
*/
#define USE_FR_MODULE              (STD_OFF)

/** 
@brief This constant used for other modules to check if GPT is present in the project.  
*/
#define USE_GPT_MODULE              (STD_ON)

/** 
@brief This constant used for other modules to check if ICU is present in the project.  
*/
#define USE_ICU_MODULE              (STD_ON)

/** 
@brief This constant used for other modules to check if LIN is present in the project.  
*/
#define USE_LIN_MODULE              (STD_ON)

/** 
@brief This constant used for other modules to check if MCU is present in the project.  
*/
#define USE_MCU_MODULE              (STD_ON)

/** 
@brief This constant used for other modules to check if PORT is present in the project.  
*/
#define USE_PORT_MODULE             (STD_ON)

/** 
@brief This constant used for other modules to check if PWM is present in the project.  
*/
#define USE_PWM_MODULE              (STD_ON)

/** 
@brief This constant used for other modules to check if SPI is present in the project.  
*/
#define USE_SPI_MODULE              (STD_ON)

/** 
@brief This constant used for other modules to check if WDG is present in the project.  
*/
#define USE_WDG_MODULE              (STD_ON)

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

#endif /* MODULES_H */

