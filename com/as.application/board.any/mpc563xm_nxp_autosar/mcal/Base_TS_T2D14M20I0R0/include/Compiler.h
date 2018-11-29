/**
    @file        Compiler.h
    @version     2.0.0

    @brief       AUTOSAR Base - SWS Compiler abstraction.
    @details     The file Compiler.h provides macros for the encapsulation of definitions and declarations.

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
@file        Compiler.h
@remarks Covers COMPILER004
@remarks Implements DBASE03000
*/

/**
@page misra_violations MISRA-C:2004 violations

@section Compiler_h_REF_1
Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
Compiler abstraction specified in AutoSar Specification of Compiler Abstraction.
@section Compiler_h_REF_2
Violates MISRA 2004 Advisory Rule 20.2, Re-use of C90 reserved identifier
This violation is due to the use of "_" which is required as per Autosar SWS COMPILER010.
*/

/**
@file        Compiler.h
@remarks Covers COMPILER047
*/
#ifndef COMPILER_H
#define COMPILER_H

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/**
@file        Compiler.h
@brief Include compiler memory types
@remarks Covers COMPILER052
*/
#include "Compiler_Cfg.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@brief Parameters that shall be published within the compiler abstraction header file and also in the
       module's description file
@remarks Covers COMPILER-FSL1, COMPILER043
@remarks Implements DBASE03023
@{
*/
#define COMPILER_VENDOR_ID           43
#define COMPILER_AR_MAJOR_VERSION    2
#define COMPILER_AR_MINOR_VERSION    0
#define COMPILER_AR_PATCH_VERSION    1
#define COMPILER_SW_MAJOR_VERSION    2
#define COMPILER_SW_MINOR_VERSION    0
#define COMPILER_SW_PATCH_VERSION    0
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

#ifdef __ghs__
    /**
    @brief Symbol required to be defined when GreenHills compiler is used.
    @remarks Covers COMPILER012, COMPILER010
    @remarks Implements DBASE03003
    @note Violates MISRA 2004 Advisory Rule 20.2, Re-use of C90 reserved identifier - See @ref Compiler_h_REF_2
    */
    #define _GREENHILLS_C_MPC563XM_
#endif
#ifdef __DCC__
    /**
    @brief Symbol required to be defined when Diab compiler is used.
    @remarks Covers COMPILER012, COMPILER010
    @remarks Implements DBASE03002
    */
    #define _DIABDATA_C_MPC563XM_
#endif
#ifdef __MWERKS__
    /**
    @brief Symbol required to be defined when Codewarrior compiler is used.
    @remarks Covers COMPILER012, COMPILER010
    @remarks Implements DBASE03001
    */
    #define _CODEWARRIOR_C_MPC563XM_
#endif
#ifdef __CSMC__
    /**
    @brief Symbol required to be defined when Cosmic compiler is used.
    @remarks Covers COMPILER012, COMPILER010
    @remarks Implements DBASE03001
    */
  #define _COSMIC_C_MPC563XM_
#endif

/**
@brief The memory class AUTOMATIC shall be provided as empty definition, used for the declaration of
       local pointers.
@remarks Covers COMPILER046,COMPILER005
@remarks Implements DBASE03004
*/
#define AUTOMATIC

/**
@brief The memory class TYPEDEF shall be provided as empty definition. This memory class shall be
       used within type definitions, where no memory qualifier can be specified. This can be necessary
       for defining pointer types, with e.g. P2VAR, where the macros require two parameters. First
       parameter can be specified in the type definition (distance to the memory location referenced
       by the pointer), but the second one (memory allocation of the pointer itself) cannot be defined
       at this time. Hence memory class TYPEDEF shall be applied.
@remarks Covers COMPILER059,COMPILER005
@remarks Implements DBASE03011
*/
#define TYPEDEF

/**
@brief The compiler abstraction shall provide the STATIC define for abstraction of compiler keyword static.
@remarks Covers COMPILER049
@remarks Implements DBASE03010
*/
#define STATIC static

/**
@brief The compiler abstraction shall provide the NULL_PTR define with a void pointer to zero definition.
@remarks Covers COMPILER051
@remarks Implements DBASE03009
*/
#define NULL_PTR ((void *)0)

/**************************************** Green Hills *********************************************/
#ifdef _GREENHILLS_C_MPC563XM_
    /* Prototypes for intrinsic functions */
    /**
    @brief The compiler abstraction shall provide the INLINE define for abstraction of the keyword inline.
    @remarks Covers COMPILER057
    @remarks Implements DBASE03007
    */
    #define INLINE              __inline

    /**
    @brief Compiler abstraction for specifying an interrupt handler.
    @remarks Covers
    @remarks Implements DBASE03008
    */
    #define INTERRUPT_FUNC      __interrupt
#endif /* #ifdef _GREENHILLS_C_MPC563XM_ */

/**************************************** Wind River Diab *****************************************/
#ifdef _DIABDATA_C_MPC563XM_
    /* Prototypes for intrinsic functions */
    /**
    @brief The compiler abstraction shall provide the INLINE define for abstraction of the keyword inline.
    @remarks Covers COMPILER057
    @remarks Implements DBASE03007
    */
    #define INLINE              __inline__

    /**
    @brief Compiler abstraction for specifying an interrupt handler.
    @remarks Covers
    @remarks Implements DBASE03008
    */
    #define INTERRUPT_FUNC      __interrupt__
#endif /* #ifdef _DIABDATA_C_MPC563XM_ */

/*************************************** CodeWarrior **********************************************/
#ifdef _CODEWARRIOR_C_MPC563XM_
    /* Prototypes for intrinsic functions */
    /**
    @brief The compiler abstraction shall provide the INLINE define for abstraction of the keyword inline.
    @remarks Covers COMPILER057
    @remarks Implements DBASE03007
    */
    #define INLINE              inline

    /**
    @brief Compiler abstraction for specifying an interrupt handler.
    @remarks Covers
    @remarks Implements DBASE03008
    */
    #define INTERRUPT_FUNC      __declspec(interrupt nowarn)
#endif /* #ifdef _CODEWARRIOR_C_MPC563XM_ */

/*************************************** Cosmic ***************************************************/
#ifdef _COSMIC_C_MPC563XM_
    /* Prototypes for intrinsic functions */
    /**
    @brief The compiler abstraction shall provide the INLINE define for abstraction of the keyword inline.
    @remarks Covers COMPILER057
    @remarks Implements DBASE03007
    */
    #define INLINE @inline
    /**
    @brief Compiler abstraction for specifying an interrupt handler.
    @remarks Covers
    @remarks Implements DBASE03008
    */
    #define INTERRUPT_FUNC @interrupt
#endif /* #ifdef _COSMIC_C_MPC563XM_ */


/**
@brief The compiler abstraction shall define the FUNC macro for the declaration and definition of
       functions, that ensures correct syntax of function declarations as required by a specific compiler.
@remarks Covers COMPILER001,COMPILER058
@remarks Implements DBASE03015
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Compiler_h_REF_1
*/
#define FUNC(rettype, memclass) rettype

/**
@brief The compiler abstraction shall define the P2VAR macro for the declaration and definition of
       pointers in RAM, pointing to variables.
@remarks Covers COMPILER006
@remarks Implements DBASE03019
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Compiler_h_REF_1
*/
#define P2VAR(ptrtype, memclass, ptrclass) ptrtype *

/**
@brief The compiler abstraction shall define the P2CONST macro for the declaration and definition of
       pointers in RAM pointing to constants.
@remarks Covers COMPILER013
@remarks Implements DBASE03017
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Compiler_h_REF_1
*/
#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype *

/**
@brief The compiler abstraction shall define the CONSTP2VAR macro for the declaration and definition
       of constant pointers accessing variables.
@remarks Covers COMPILER031
@remarks Implements DBASE03014
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Compiler_h_REF_1
*/
#define CONSTP2VAR(ptrtype, memclass, ptrclass) ptrtype * const

/**
@brief The compiler abstraction shall define the CONSTP2CONST macro for the declaration and
       definition of constant pointers accessing constants.
@remarks Covers COMPILER032
@remarks Implements DBASE03013
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Compiler_h_REF_1
*/
#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype * const

/**
@brief The compiler abstraction shall define the P2FUNC macro for the type definition of pointers
       to functions.
@remarks Covers COMPILER039
@remarks Implements DBASE03018
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Compiler_h_REF_1
*/
#define P2FUNC(rettype, ptrclass, fctname) rettype (*fctname)

/**
@brief The compiler abstraction shall define the CONST macro for the declaration and definition of
       constants.
@remarks Covers COMPILER023
@remarks Implements DBASE03012
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Compiler_h_REF_1
*/
#define CONST(consttype, memclass) const consttype

/**
@brief The compiler abstraction shall define the VAR macro for the declaration and definition of
       variables.
@remarks Covers COMPILER026
@remarks Implements DBASE03022
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Compiler_h_REF_1
*/
#define VAR(vartype, memclass) vartype

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


#endif /* #ifndef COMPILER_H */
