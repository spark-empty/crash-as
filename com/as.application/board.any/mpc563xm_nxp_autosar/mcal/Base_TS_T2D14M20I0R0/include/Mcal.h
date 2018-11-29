/**
    @file        Mcal.h
    @version     2.0.0

    @brief       AUTOSAR Base - SWS Compiler abstraction specific for MCAL.
    @details     The file Mcal.h provides MCAL specific macros used for compiler abstraction.

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
@file        Mcal.h
@remarks Covers
@remarks Implements
*/

/**
@page misra_violations MISRA-C:2004 violations

@section Mcal_h_REF_1
Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
Compiler abstraction need to implement function-like macros to hide compiler specifics from the implementation.

@section Mcal_h_REF_2
Violates MISRA 2004 Required Rule 19.15, Repeated include file
This comes from the order of includes in the .c file and from include dependencies. As a safe
approach, any file must include all its dependencies. Header files are already protected against
double inclusions.
*/

#ifndef MCAL_H
#define MCAL_H

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/**
@file        Mcal.h
@brief Include compiler abstraction
@note Violates MISRA 2004 Required Rule 19.15, Repeated include file - See @ref Mcal_h_REF_2
*/
#include "Compiler.h"
/**
@file        Mcal.h
@brief Include standard types
@note Violates MISRA 2004 Required Rule 19.15, Repeated include file - See @ref Mcal_h_REF_2
*/
#include "Std_Types.h"
/**
@file        Mcal.h
@brief Include standard types
@note Violates MISRA 2004 Required Rule 19.15, Repeated include file - See @ref Mcal_h_REF_2
*/
#include "Cer.h"
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/**************************************** Green Hills *********************************************/
#ifdef _GREENHILLS_C_MPC563XM_
    /**
    @brief Compiler abstraction for the asm keyword.
    @remarks Covers
    @remarks Implements DBASE03024
    */
    #define ASM_KEYWORD  __asm


    /**
    @brief Compiler abstraction for the intrinsic wait instruction.
    @remarks Covers
    @remarks Implements DBASE03005
    @note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Mcal_h_REF_1
    */
    #define EXECUTE_WAIT()      ASM_KEYWORD("  wait")

    /**
    @brief Compiler abstraction for the data alignment
    @remarks Covers
    @remarks Implements DBASE03050
    */
    #define ALIGNED_VARS_START(sec_name, align)
    /**
    @brief Compiler abstraction for the data alignment
    @remarks Covers
    @remarks Implements DBASE03027
    */
    #define VAR_ALIGN(v, size) __attribute__(( aligned(size) )) v;
    /**
    @brief Compiler abstraction for the data alignment
    @remarks Covers
    @remarks Implements DBASE03051
    */
    #define ALIGNED_VARS_STOP()

#endif /* #ifdef _GREENHILLS_C_MPC563XM_ */

/**************************************** Wind River Diab *****************************************/
#ifdef _DIABDATA_C_MPC563XM_
    /**
    @brief Compiler abstraction for the asm keyword.
    @remarks Covers
    @remarks Implements DBASE03024
    */
    #define ASM_KEYWORD  asm volatile

    /**
    @brief Compiler abstraction for the intrinsic wait instruction.
    @remarks Covers
    @remarks Implements DBASE03005
    @note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Mcal_h_REF_1
    */
    #define EXECUTE_WAIT()      ASM_KEYWORD("  .word 0x7C00007C")

    /**
    @brief Compiler abstraction for the data alignment
    @remarks Covers
    @remarks Implements DBASE03050
    */
    #define ALIGNED_VARS_START(sec_name, align)
    /**
    @brief Compiler abstraction for the data alignment
    @remarks Covers
    @remarks Implements DBASE03027
    */
    #define VAR_ALIGN(v, size) __attribute__(( aligned(size) )) v;
    /**
    @brief Compiler abstraction for the data alignment
    @remarks Covers
    @remarks Implements DBASE03051
    */
    #define ALIGNED_VARS_STOP()

#endif /* #ifdef _DIABDATA_C_MPC563XM_ */

/*************************************** CodeWarrior **********************************************/
#ifdef _CODEWARRIOR_C_MPC563XM_
    /**
    @brief Compiler abstraction for the asm keyword.
    @remarks Covers
    @remarks Implements DBASE03024
    */
    #define ASM_KEYWORD  asm

    /**
    @brief Compiler abstraction for the intrinsic wait instruction.
    @remarks Covers
    @remarks Implements DBASE03005
    @note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Mcal_h_REF_1
    */
    #define EXECUTE_WAIT()      ASM_KEYWORD (" opword 0x7C00007C")

    /**
    @brief Compiler abstraction for the data alignment
    @remarks Covers
    @remarks Implements DBASE03050
    */
    #define ALIGNED_VARS_START(sec_name, align)
    /**
    @brief Compiler abstraction for the data alignment
    @remarks Covers
    @remarks Implements DBASE03027
    */
    #define VAR_ALIGN(v, size) v __attribute__(( aligned(size) ));

    /**
    @brief Compiler abstraction for the data alignment
    @remarks Covers
    @remarks Implements DBASE03051
    */
    #define ALIGNED_VARS_STOP()

#endif /* #ifdef _CODEWARRIOR_C_MPC563XM_ */

/*************************************** Cosmic ***************************************************/
#ifdef _COSMIC_C_MPC563XM_
    /**
    @brief Compiler abstraction for the asm keyword.
    @remarks Covers
    @remarks Implements DBASE03024
    */
    #define ASM_KEYWORD  _asm
    /* for example
     *     void f(void)
     *     {
     *         ASM_PUBLIC_LABEL(label);
     *      }
     */
    /**
    @brief Compiler abstraction for the asm keyword.
    @remarks Covers
    @remarks Implements DBASE03052
    */
    #define ASM_PUBLIC_LABEL(label)  _asm("\txdef\t" #label "\n" #label ":")

    /**
    @brief Compiler abstraction for the intrinsic wait instruction.
    @remarks Covers
    @remarks Implements DBASE03005
    @note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Mcal_h_REF_1
    */
    #define EXECUTE_WAIT()      ASM_KEYWORD (" dc.l 0x7C00007C")
   /**
    @brief Compiler abstraction for the data alignment
    @remarks Covers
    @remarks Implements DBASE03050
    */
    #define ALIGNED_VARS_START(sec_name, align) \#pragma section [sec_name ## align]
   /**
    @brief Compiler abstraction for the data alignment
    @remarks Covers
    @remarks Implements DBASE03027
    */
    #define VAR_ALIGN(v, size) v;
   /**
    @brief Compiler abstraction for the data alignment
    @remarks Covers
    @remarks Implements DBASE03051
    */
    #define ALIGNED_VARS_STOP() \#pragma section []
#endif /* #ifdef _COSMIC_C_MPC563XM_ */


#if defined(AUTOSAR_OS_NOT_USED)
    #if defined (USE_SW_VECTOR_MODE)
        /**
        @brief Compiler abstraction for creating an interrupt handler if no OS is present.
        @remarks Covers
        @remarks Implements DBASE03016
        @note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Mcal_h_REF_1
        */
        #define ISR(IsrName)       void IsrName(void)

        /**
        @brief Compiler abstraction for returning from an ISR if no OS is present.
        @remarks Covers
        @remarks Implements DBASE03006
        @note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Mcal_h_REF_1
        */
        #define EXIT_INTERRUPT()
    #else
        /**
        @brief Compiler abstraction for creating an interrupt handler if no OS is present.
        @remarks Covers
        @remarks Implements DBASE03016
        @note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Mcal_h_REF_1
        */
        #define ISR(IsrName)       INTERRUPT_FUNC void IsrName(void)

        /**
        @brief Compiler abstraction for returning from an ISR if no OS is present.
        @remarks Covers
        @remarks Implements DBASE03006
        @note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Mcal_h_REF_1
        */
        #define EXIT_INTERRUPT()        SuspendAllInterrupts(); *((volatile uint32 *)(0xFFF48000U+0x0018U)) = 0U
    #endif /*USE_SW_VECTOR_MODE*/

    /**
    @brief Compiler abstraction for disabling all interrupts if no OS is present.
    @remarks Covers
    @remarks Implements DBASE03021
    @note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Mcal_h_REF_1
    */
    #define SuspendAllInterrupts() ASM_KEYWORD(" wrteei 0")

    /**
    @brief Compiler abstraction for re-enabling all interrupts if no OS is present.
    @remarks Covers
    @remarks Implements DBASE03020
    @note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Mcal_h_REF_1
    */
    #define ResumeAllInterrupts() ASM_KEYWORD(" wrteei 1")
#else
    /* MISRA-C:2004 19.1 VIOLATION: Refer to REF 2 above */
    #include "os.h"
    /**
    @brief Compiler abstraction for returning from an ISR if OS is present must be empty.
    @remarks Covers
    @remarks Implements DBASE03006
    @note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Mcal_h_REF_1
    */
    #define EXIT_INTERRUPT()
#endif

/**
@brief The compiler abstraction for pointer to pointer to variable.
@remarks Implements DBASE03025
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Mcal_h_REF_1
*/
#define P2P2VAR(ptrtype, memclass, ptrclass) ptrtype **

/**
@brief The compiler abstraction for pointer to pointer to constant.
@remarks Implements DBASE03026
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Mcal_h_REF_1
*/
#define P2P2CONST(ptrtype, memclass, ptrclass) const ptrtype **
/**
@brief The compiler abstraction shall define the CONSTP2FUNC macro for the type definition of pointers
       to functions.
@remarks Covers PR-MCAL-3238
@remarks Implements DBASE03053
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Mcal_h_REF_1
*/
#define CONSTP2FUNC(rettype, ptrclass, fctname) rettype (* const fctname)

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


#endif /* #ifndef MCAL_H */
