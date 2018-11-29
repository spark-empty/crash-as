/**
    @file        Reg_Macros.h
    @version     2.0.0

    @brief       AUTOSAR Base - Macros for accessing memory mapped registers.
    @details     Macro definitions used for accessing memory mapped registers.
    
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
@file        Reg_Macros.h
@remarks Implements DBASE06000
*/

/** 
@page misra_violations MISRA-C:2004 violations

@section Reg_Macros_h_REF_1 
Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
This violation is due to function like macros defined for register operations.
Function like macros are used to reduce code complexity.

@section Reg_Macros_h_REF_2
Violates MISRA 2004 Required Rule 19.15, Repeated include file 
This comes from the order of includes in the .c file and from include dependencies. As a safe 
approach, any file must include all its dependencies. Header files are already protected against 
double inclusions.
*/

#ifndef REG_MACROS_H
#define REG_MACROS_H

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
@file        Reg_Macros.h
@brief Include platform types
@note Violates MISRA 2004 Required Rule 19.15, Repeated include file - See @ref Reg_Macros_h_REF_2
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
@{
@brief Bit masks declarations.
@remarks Implements DBASE06025
*/
#define BIT31   ((uint32)0x80000000UL)
#define BIT30   ((uint32)0x40000000UL)
#define BIT29   ((uint32)0x20000000UL)
#define BIT28   ((uint32)0x10000000UL)
#define BIT27   ((uint32)0x08000000UL)
#define BIT26   ((uint32)0x04000000UL)
#define BIT25   ((uint32)0x02000000UL)
#define BIT24   ((uint32)0x01000000UL)
#define BIT23   ((uint32)0x00800000UL)
#define BIT22   ((uint32)0x00400000UL)
#define BIT21   ((uint32)0x00200000UL)
#define BIT20   ((uint32)0x00100000UL)
#define BIT19   ((uint32)0x00080000UL)
#define BIT18   ((uint32)0x00040000UL)
#define BIT17   ((uint32)0x00020000UL)
#define BIT16   ((uint32)0x00010000UL)
#define BIT15   ((uint32)0x00008000UL)
#define BIT14   ((uint32)0x00004000UL)
#define BIT13   ((uint32)0x00002000UL)
#define BIT12   ((uint32)0x00001000UL)
#define BIT11   ((uint32)0x00000800UL)
#define BIT10   ((uint32)0x00000400UL)
#define BIT9    ((uint32)0x00000200UL)
#define BIT8    ((uint32)0x00000100UL)
#define BIT7    ((uint32)0x00000080UL)
#define BIT6    ((uint32)0x00000040UL)
#define BIT5    ((uint32)0x00000020UL)
#define BIT4    ((uint32)0x00000010UL)
#define BIT3    ((uint32)0x00000008UL)
#define BIT2    ((uint32)0x00000004UL)
#define BIT1    ((uint32)0x00000002UL)
#define BIT0    ((uint32)0x00000001UL)
/**@}*/
/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/** 
@brief 8 bits memory write macro
@remarks Implements DBASE06024
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Reg_Macros_h_REF_1
*/
#define REG_WRITE8(address, value)        ((*(volatile uint8*)(address))=  (uint8)(value))
/** 
@brief 16 bits memory write macro.
@remarks Implements DBASE06022
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Reg_Macros_h_REF_1
*/
#define REG_WRITE16(address, value)       ((*(volatile uint16*)(address))= (uint16)(value))
/** 
@brief 32 bits memory write macro.
@remarks Implements DBASE06023
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Reg_Macros_h_REF_1
*/
#define REG_WRITE32(address, value)       ((*(volatile uint32*)(address))= (uint32)(value))


/** 
@brief 8 bits memory read macro.
@remarks Implements DBASE06018
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Reg_Macros_h_REF_1
*/
#define REG_READ8(address)                (*(volatile uint8*)(address))
/** 
@brief 16 bits memory read macro.
@remarks Implements DBASE06016
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Reg_Macros_h_REF_1
*/
#define REG_READ16(address)               (*(volatile uint16*)(address))
/** 
@brief 32 bits memory read macro.
@remarks Implements DBASE06017
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Reg_Macros_h_REF_1
*/
#define REG_READ32(address)               (*(volatile uint32*)(address))


/** 
@brief 8 bits indexed memory write macro.
@remarks Implements DBASE06006
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Reg_Macros_h_REF_1
*/
#define REG_AWRITE8(address, i, value)     (REG_WRITE8 ((address)+(uint32)(i), (value)))
/** 
@brief 16 bits indexed memory write macro.
@remarks Implements DBASE06004
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Reg_Macros_h_REF_1
*/
#define REG_AWRITE16(address, i, value)    (REG_WRITE16((address)+((uint32)(((uint32)(i))<<1U)), (value)))
/** 
@brief 32 bits indexed memory write macro.
@remarks Implements DBASE06005
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Reg_Macros_h_REF_1
*/
#define REG_AWRITE32(address, i, value)    (REG_WRITE32((address)+((uint32)(((uint32)(i))<<2U)), (value)))


/** 
@brief 8 bits indexed memory read macro.
@remarks Implements DBASE06003
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Reg_Macros_h_REF_1
*/
#define REG_AREAD8(address, i )            (REG_READ8 ((address)+(uint32)(i)))
/** 
@brief 16 bits indexed memory read macro.
@remarks Implements DBASE06001
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Reg_Macros_h_REF_1
*/
#define REG_AREAD16(address, i)            (REG_READ16((address)+((uint32)(((uint32)(i))<<1U))))
/** 
@brief 32 bits indexed memory read macro.
@remarks Implements DBASE06002
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Reg_Macros_h_REF_1
*/
#define REG_AREAD32(address, i)            (REG_READ32((address)+((uint32)(((uint32)(i))<<2U))))


/** 
@brief 8 bits bits clearing macro.
@remarks Implements DBASE06009
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Reg_Macros_h_REF_1
*/
#define REG_BIT_CLEAR8(address, mask)     ((*(volatile uint8*)(address))&= ((uint8)~((uint8)(mask))))
/** 
@brief 16 bits bits clearing macro.
@remarks Implements DBASE06007
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Reg_Macros_h_REF_1
*/
#define REG_BIT_CLEAR16(address, mask)    ((*(volatile uint16*)(address))&= ((uint16)~((uint16)(mask))))
/** 
@brief 32 bits bits clearing macro.
@remarks Implements DBASE06008
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Reg_Macros_h_REF_1
*/
#define REG_BIT_CLEAR32(address, mask)    ((*(volatile uint32*)(address))&= ((uint32)~((uint32)(mask))))


/** 
@brief 8 bits bits getting macro.
@remarks Implements DBASE06012
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Reg_Macros_h_REF_1
*/
#define REG_BIT_GET8(address, mask)       ((*(volatile uint8*)(address))& (uint8)(mask))
/** 
@brief 16 bits bits getting macro.
@remarks Implements DBASE06010
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Reg_Macros_h_REF_1
*/
#define REG_BIT_GET16(address, mask)      ((*(volatile uint16*)(address))& (uint16)(mask))
/** 
@brief 32 bits bits getting macro.
@remarks Implements DBASE06011
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Reg_Macros_h_REF_1
*/
#define REG_BIT_GET32(address, mask)      ((*(volatile uint32*)(address))& (uint32)(mask))


/** 
@brief 8 bits bits setting macro.
@remarks Implements DBASE06015
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Reg_Macros_h_REF_1
*/
#define REG_BIT_SET8(address, mask)       ((*(volatile uint8*)(address))|= (uint8)(mask))
/** 
@brief 16 bits bits setting macro.
@remarks Implements DBASE06013
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Reg_Macros_h_REF_1
*/
#define REG_BIT_SET16(address, mask)      ((*(volatile uint16*)(address))|= (uint16)(mask))
/** 
@brief 32 bits bits setting macro.
@remarks Implements DBASE06014
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Reg_Macros_h_REF_1
*/
#define REG_BIT_SET32(address, mask)      ((*(volatile uint32*)(address))|= (uint32)(mask))


/** 
@brief 8 bit clear bits and set with new value
@note In the current implementation, it is caller's (user's) responsability to make sure that value has only "mask" bits set - (value&~mask)==0
@remarks Implements DBASE06021
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Reg_Macros_h_REF_1
*/
#define REG_RMW8(address, mask, value)    (REG_WRITE8((address), ((REG_READ8(address)& ((uint8)~((uint8)(mask))))| ((uint8)(value)))))
/** 
@brief 16 bit clear bits and set with new value
@note In the current implementation, it is caller's (user's) responsability to make sure that value has only "mask" bits set - (value&~mask)==0
@remarks Implements DBASE06019
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Reg_Macros_h_REF_1
*/
#define REG_RMW16(address, mask, value)   (REG_WRITE16((address), ((REG_READ16(address)& ((uint16)~((uint16)(mask))))| ((uint16)(value)))))
/** 
@brief 32 bit clear bits and set with new value
@note In the current implementation, it is caller's (user's) responsability to make sure that value has only "mask" bits set - (value&~mask)==0
@remarks Implements DBASE06020
@note Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined - See @ref Reg_Macros_h_REF_1
*/
#define REG_RMW32(address, mask, value)   (REG_WRITE32((address), ((REG_READ32(address)& ((uint32)~((uint32)(mask))))| ((uint32)(value)))))

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /* #ifndef REG_MACROS_H */
