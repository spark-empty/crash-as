/**
    @file        Platform_Types.h
    @version     2.0.0

    @brief       AUTOSAR Base - Platform dependend data type definitions.
    @details     AUTOSAR platform types header file. It contains all 
                 platform dependent types and symbols. Those types must be abstracted in order to 
                 become platform and compiler independent.
    
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
@file        Platform_Types.h
@remarks Covers PLATFORM003,PLATFORM001
@remarks Implements DBASE05000
*/

/**   
@file        Platform_Types.h
@remarks Covers PLATFORM002

         It is not allowed to add any extension to this file. Any extension invalidates the AUTOSAR 
         conformity
*/

#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** 
@{
@brief Parameters that shall be published within the platform types header file and also in the 
       module's description file
@remarks Covers PLATFORM012
@remarks Implements DBASE05028
*/
#define PLATFORM_VENDOR_ID          43
#define PLATFORM_AR_MAJOR_VERSION   2
#define PLATFORM_AR_MINOR_VERSION   2
#define PLATFORM_AR_PATCH_VERSION   1
#define PLATFORM_SW_MAJOR_VERSION   2
#define PLATFORM_SW_MINOR_VERSION   0
#define PLATFORM_SW_PATCH_VERSION   0
/**@}*/
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/
/** 
@brief 8bit Type Processor
@remarks Covers PLATFORM057
@remarks Implements DBASE05021
*/
#define CPU_TYPE_8 8

/** 
@brief 16bit Type Processor
@remarks Covers PLATFORM057
@remarks Implements DBASE05019
*/
#define CPU_TYPE_16 16

/** 
@brief 32bit Type Processor
@remarks Covers PLATFORM057
@remarks Implements DBASE05020
*/
#define CPU_TYPE_32 32

/** 
@brief MSB First Processor
@remarks Covers PLATFORM057
@remarks Implements DBASE05026
*/
#define MSB_FIRST 0

/** 
@brief LSB First Processor
@remarks Covers PLATFORM057
@remarks Implements DBASE05025
*/
#define LSB_FIRST 1

/** 
@brief HIGH_BYTE_FIRST Processor
@remarks Covers PLATFORM057
@remarks Implements DBASE05023
*/
#define HIGH_BYTE_FIRST 0

/** 
@brief LOW_BYTE_FIRST Processor
@remarks Covers PLATFORM057
@remarks Implements DBASE05024
*/
#define LOW_BYTE_FIRST 1

/** 
@brief Processor type
@remarks Covers PLATFORM044, PLATFORM045, PLATFORM_FSL01, PLATFORM010
@remarks Implements DBASE05018
*/
#define CPU_TYPE (CPU_TYPE_32)

/** 
@brief Bit order on register level.
@remarks Covers PLATFORM043, PLATFORM048, PLATFORM049, PLATFORM038, PLATFORM010
@remarks Implements DBASE05016
*/
#define CPU_BIT_ORDER (MSB_FIRST)

/** 
@brief The byte order on memory level shall be indicated in the platform types header file using the 
       symbol CPU_BYTE_ORDER.
@remarks Covers PLATFORM046, PLATFORM050, PLATFORM051, PLATFORM039, PLATFORM010
@remarks Implements DBASE05017
*/
#define CPU_BYTE_ORDER (HIGH_BYTE_FIRST)

#ifndef TRUE
    /** 
    @brief Boolean true value
    @remarks Covers PLATFORM054, PLATFORM055, PLATFORM056
    @remarks Implements DBASE05027
    */
    #define TRUE 1
#endif
#ifndef FALSE
    /** 
    @brief Boolean false value
    @remarks Covers PLATFORM054, PLATFORM055, PLATFORM056
    @remarks Implements DBASE05022
    */
    #define FALSE 0
#endif

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/** 
@brief The standard AUTOSAR type boolean shall be implemented on basis of an eight bits long 
       unsigned integer.
@remarks Covers PLATFORM027, PLATFORM026, PLATFORM060, PLATFORM010
@remarks Implements DBASE05001
*/
typedef unsigned char boolean;


/** 
@brief Unsigned 8 bit integer with range of 0 ..+255 (0x00..0xFF) - 
       8 bit
@remarks Covers PLATFORM013, PLATFORM010
@remarks Implements DBASE05002
*/
typedef unsigned char uint8;

/** 
@brief Unsigned 16 bit integer with range of 0 ..+65535 (0x0000..0xFFFF) - 
       16 bit
@remarks Covers PLATFORM014, PLATFORM010
@remarks Implements DBASE05003
*/
typedef unsigned short uint16;

/** 
@brief Unsigned 32 bit integer with range of 0 ..+4294967295 (0x00000000..0xFFFFFFFF) - 
       32 bit
@remarks Covers PLATFORM015, PLATFORM010
@remarks Implements DBASE05004
*/
typedef unsigned long uint32;

/** 
@brief Signed 8 bit integer with range of -128 ..+127 (0x80..0x7F) - 
       7 bit + 1 sign bit 
@remarks Covers PLATFORM016, PLATFORM010
@remarks Implements DBASE05005
*/
typedef signed char sint8;

/** 
@brief Signed 16 bit integer with range of -32768 ..+32767 (0x8000..0x7FFF) - 
       15 bit + 1 sign bit 
@remarks Covers PLATFORM017, PLATFORM010
@remarks Implements DBASE05006
*/
typedef signed short sint16;

/** 
@brief Signed 32 bit integer with range of -2147483648.. +2147483647 (0x80000000..0x7FFFFFFF) - 
       31 bit + 1 sign bit 
@remarks Covers PLATFORM018, PLATFORM010
@remarks Implements DBASE05007
*/
typedef signed long sint32;

/** 
@brief Unsigned integer at least 8 bit long. Range of at least 0 ..+255 (0x00..0xFF) - 
       8 bit
@remarks Covers PLATFORM020, PLATFORM005, PLATFORM010
@remarks Implements DBASE05008
*/
typedef unsigned long uint8_least;

/** 
@brief  Unsigned integer at least 16 bit long. Range of at least 0 ..+65535 (0x0000..0xFFFF) - 
        16 bit
@remarks Covers PLATFORM021, PLATFORM005, PLATFORM010
@remarks Implements DBASE05009
*/
typedef unsigned long uint16_least;

/** 
@brief Unsigned integer at least 32 bit long. Range of at least 0 ..+4294967295 (0x00000000..0xFFFFFFFF) - 
       32 bit
@remarks Covers PLATFORM022, PLATFORM005, PLATFORM010
@remarks Implements DBASE05010
*/
typedef unsigned long uint32_least;

/** 
@brief Signed integer at least 8 bit long. Range - at least -128 ..+127. 
       At least 7 bit + 1 bit sign
@remarks Covers PLATFORM023, PLATFORM005, PLATFORM010
@remarks Implements DBASE05011
*/
typedef signed long sint8_least;

/** 
@brief Signed integer at least 16 bit long. Range - at least -32768 ..+32767. 
       At least 15 bit + 1 bit sign
@remarks Covers PLATFORM024, PLATFORM005, PLATFORM010
@remarks Implements DBASE05012
*/
typedef signed long sint16_least;

/** 
@brief Signed integer at least 32 bit long. Range - at least -2147483648.. +2147483647. 
       At least 31 bit + 1 bit sign
@remarks Covers PLATFORM025, PLATFORM005, PLATFORM010
@remarks Implements DBASE05013
*/
typedef signed long sint32_least;

/** 
@brief 32bit long floating point data type
@remarks Covers PLATFORM041, PLATFORM010
@remarks Implements DBASE05014
*/
typedef float float32;

/** 
@brief 64bit long floating point data type
@remarks Covers PLATFORM042, PLATFORM010
@remarks Implements DBASE05015
*/
typedef double float64;

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/


#endif /* #ifndef PLATFORM_TYPES_H */
