/**
    @file    Siu_LLD.c
    @version 2.0.0

    @brief   AUTOSAR Dio - SIU Low level driver implementation.
    @details Implementation of the SIU low level driver.

    Project AUTOSAR 3.0 MCAL
    Patform PA
    Peripheral SIU
    Dependencies none

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

@section Siu_LLD_C_REF_1
Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
Macros are used to reduce code complexity

@section Siu_LLD_C_REF_2
Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before "#include"
This is an Autosar requirement about the memory management.

@section Siu_LLD_C_REF_3
Violates MISRA 2004 Required Rules 10.1, Implicit conversion changes signedness, and 10.3,
Cast of complex integer expression to larger type.
All the type conversions are implemented in MACROS. The code was tested successfully with 3
different compilers.

@section Siu_LLD_C_REF_4
Violates MISRA 2004 Required Rules 11.3, Cast from unsigned long to pointer.
This violation is due to the pointer arithematic used to write/ read the data to/from the registers.

@section Siu_LLD_C_REF_5
Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h
There are different kinds of execution code sections.

@section Siu_LLD_C_REF_6
Violates MISRA 2004 Advisory Rule 17.4, pointer arithmetic other than array indexing used.
This violation is due to the use of pointer arithematic, to access the channel parameters,
the indexing of the pointer is taken care and hence the unintended memory location will not
be accessed.

@section Siu_LLD_C_REF_7
Violates MISRA 2004 Advisory Rule 12.6, boolean expression required for operator: '||'; the -strong(B,...) 
option can help provide Boolean-by-enforcement.
Booleans operands are not used for logical operators '&&', '||' and '!'

@section Siu_LLD_C_REF_8
Violates MISRA 2004 Advisory Rule 11.1, Conversions shall not be performed between a pointer to a
function and any type other than an integral type.This rule can not be avoided because it appears 
when addressing memory mapped registers or other hardware specific feature.
*/

#ifdef __cplusplus
extern "C" {
#endif
/**
@brief Module ID where this file is placed.
@details Used to make sure that the file content is not compile twice if at least 2 modules using it
are compiled in the project
*/
#define SIU_LLD_MODULE_ID        120

#include "modules.h"

#include "Reg_Macros.h"


/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@brief Parameters that shall be published within the driver header file and also in the
       module's description file
@remarks Covers BSW00374, BSW00379, BSW00318
@{
*/
#define SIU_VENDOR_ID_LLD_C          43
#define SIU_AR_MAJOR_VERSION_LLD_C   3
#define SIU_AR_MINOR_VERSION_LLD_C   0
#define SIU_AR_PATCH_VERSION_LLD_C   0
#define SIU_SW_MAJOR_VERSION_LLD_C   2
#define SIU_SW_MINOR_VERSION_LLD_C   0
#define SIU_SW_PATCH_VERSION_LLD_C   0
/**@}*/

#if ( (USE_PORT_MODULE == STD_ON) && (SIU_LLD_MODULE_ID == 124) )
/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Port.h"
#include "Reg_eSys_SIU.h"
#include "Siu_LLD.h"

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/**
@file    Siu_LLD.c
@remarks Covers PORT114
*/
#if (SIU_VENDOR_ID_LLD_C != PORT_VENDOR_ID)
    #error "Siu_LLD.c and Port.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((SIU_AR_MAJOR_VERSION_LLD_C != PORT_AR_MAJOR_VERSION) || \
         (SIU_AR_MINOR_VERSION_LLD_C != PORT_AR_MINOR_VERSION) || \
         (SIU_AR_PATCH_VERSION_LLD_C != PORT_AR_PATCH_VERSION))
      #error "AutoSar Version Numbers of Siu_LLD.c and Port.h are different"
    #endif
#endif
#if ((SIU_SW_MAJOR_VERSION_LLD_C != PORT_SW_MAJOR_VERSION) || \
     (SIU_SW_MINOR_VERSION_LLD_C != PORT_SW_MINOR_VERSION) || \
     (SIU_SW_PATCH_VERSION_LLD_C != PORT_SW_PATCH_VERSION))
  #error "Software Version Numbers of Siu_LLD.c and Port.h are different"
#endif

#if (SIU_VENDOR_ID_LLD_C != SIU_VENDOR_ID_REG)
    #error "Siu_LLD.c and Reg_eSys_SIU.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((SIU_AR_MAJOR_VERSION_LLD_C != SIU_AR_MAJOR_VERSION_REG) || \
         (SIU_AR_MINOR_VERSION_LLD_C != SIU_AR_MINOR_VERSION_REG) || \
         (SIU_AR_PATCH_VERSION_LLD_C != SIU_AR_PATCH_VERSION_REG))
      #error "AutoSar Version Numbers of Siu_LLD.c and Reg_eSys_SIU.h are different"
    #endif
#endif
#if ((SIU_SW_MAJOR_VERSION_LLD_C != SIU_SW_MAJOR_VERSION_REG) || \
     (SIU_SW_MINOR_VERSION_LLD_C != SIU_SW_MINOR_VERSION_REG) || \
     (SIU_SW_PATCH_VERSION_LLD_C != SIU_SW_PATCH_VERSION_REG))
  #error "Software Version Numbers of Siu_LLD.c and Reg_eSys_SIU.h are different"
#endif

/** Check if the files Siu_LLD.c and Siu_LLD.h have the same vendor **/
#if (SIU_VENDOR_ID_LLD_C != SIU_VENDOR_ID_LLD_H)
    #error "Siu_LLD.c and Siu_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((SIU_AR_MAJOR_VERSION_LLD_C != SIU_AR_MAJOR_VERSION_LLD_H) || \
         (SIU_AR_MINOR_VERSION_LLD_C != SIU_AR_MINOR_VERSION_LLD_H) || \
         (SIU_AR_PATCH_VERSION_LLD_C != SIU_AR_PATCH_VERSION_LLD_H))
      #error "AutoSar Version Numbers of Siu_LLD.c and Siu_LLD.h are different"
    #endif
#endif
#if ((SIU_SW_MAJOR_VERSION_LLD_C != SIU_SW_MAJOR_VERSION_LLD_H) || \
     (SIU_SW_MINOR_VERSION_LLD_C != SIU_SW_MINOR_VERSION_LLD_H) || \
     (SIU_SW_PATCH_VERSION_LLD_C != SIU_SW_PATCH_VERSION_LLD_H))
  #error "Software Version Numbers of Siu_LLD.c and Siu_LLD.h are different"
#endif
/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/
#if ((PORT_SET_PIN_DIRECTION_API == STD_ON) || (PORT_SET_PIN_MODE_API == STD_ON))
/**
@brief Segment descriptor for data arranged in array
@remarks Covers REQ001, REQ002
@remarks Implements DESIGN001, DESIGN002
*/
STATIC VAR(uint16, PORT_VAR) Port_GPIODirection[PAD_16BLOCK_NO];
#endif/* ((PORT_SET_PIN_DIRECTION_API == STD_ON) || (PORT_SET_PIN_MODE_API == STD_ON)) */

/**
@brief Pointer that after init will contain the address of the low level initialization structure
*/
STATIC P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_DATA) Port_ConfigPtr = NULL_PTR;

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
#define PORT_START_SEC_CODE
/**
@file    Siu_LLD.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" - See @ref Siu_LLD_C_REF_2
@note Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref
Siu_LLD_C_REF_5
*/
#include "MemMap.h"

/**
@brief        Initializes the SIU IP Driver.
@details      The function PORT_Siu_Init will initialize ALL ports and port pins with the
              configuration set pointed to by the parameter ConfigPtr.

@param[in]     ConfigPtr      A pointer to the structure which contains initialization parameters

@return none

@pre    none
@post   No function of the driver is executed without the initialisation of the module.
*/
FUNC(void, PORT_CODE) PORT_Siu_Init
(
    P2CONST(Port_ConfigType,AUTOMATIC,PORT_APPL_DATA) ConfigPtr
)
{
    /* [PORT002]: Initialize all variables */
    VAR(uint16, PORT_VAR) PinIndex;
    VAR(uint16, PORT_VAR) numPins = (uint16)(ConfigPtr->numPins);

    /* [PORT001]: Initialize All Configured Port Pins */
    for (PinIndex= (uint16)0x0; (uint16)PinIndex < (uint16)numPins; (PinIndex)++)
    {
        /** @note: Violates MISRA 2004 Required Rules 17.4, pointer arithmetic other than array indexing used
                     See @ref Siu_LLD_C_REF_6 */
        VAR(uint16, PORT_VAR) pinPad = (uint16)(ConfigPtr->Port_LLD_PinConfPtr[PinIndex].SIUPin);

        /* Set pin to High value */
        /** @note: Violates MISRA 2004 Required Rules 17.4, pointer arithmetic other than array indexing used
                     See @ref Siu_LLD_C_REF_6 */
        if ((uint16)1 == (uint16)(ConfigPtr->Port_LLD_PinConfPtr[PinIndex].PDO))
        {
            REG_WRITE8( SIU_GPDO(pinPad), (uint8)STD_HIGH );
        }
        /* Set pin to Low value */
        /** @note: Violates MISRA 2004 Required Rules 17.4, pointer arithmetic other than array indexing used
                     See @ref Siu_LLD_C_REF_6 */
        if ((uint16)0 == (uint16)(ConfigPtr->Port_LLD_PinConfPtr[PinIndex].PDO))
        {
            REG_WRITE8( SIU_GPDO(pinPad), (uint8)STD_LOW );
        }
        /** @note: Violates MISRA 2004 Required Rules 10.1, Implicit conversion changes signedness,
         and 10.3, Cast of complex integer expression to larger type. See @ref Siu_LLD_C_REF_3 */
        /** @note: Violates MISRA 2004 Required Rules 17.4, pointer arithmetic other than array indexing used
                     See @ref Siu_LLD_C_REF_6*/
        REG_WRITE16( SIU_PCR(pinPad), (uint16)(ConfigPtr->Port_LLD_PinConfPtr[PinIndex].PCR));
    }

#if ((PORT_SET_PIN_DIRECTION_API == STD_ON) || (PORT_SET_PIN_MODE_API == STD_ON))
    /* Initialize the Array with Change Direction Flags for GPIO */
    for (PinIndex= (uint16)0x0; PinIndex < PAD_16BLOCK_NO; PinIndex++)
    {
        Port_GPIODirection[PinIndex] = (uint16)0x0;
    }
#endif

    /* Save pointer to LLD configuration structure */
    Port_ConfigPtr = ConfigPtr;
}

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/**
@brief      Sets the port pin direction.
@details    Sets the pin direction at runtime, changing it only if the pin is configurated as
changeable.

@param[in]     PinIndex                 Pin ID number
@param[in]     chenDirection            Port Pin direction

@return Error code after execution
@retval 0   No error occured
@retval 1   Pin direction cannot be changed

@pre Port_Init must have been called
@post none

@remarks Covers PORT086, PORT117, PORT141
*/
/** @remarks Covers PORT086, PORT117, PORT141 */
FUNC(uint8, PORT_CODE) PORT_Siu_SetPinDirection
(
    VAR(Port_PinType, PORT_VAR) PinIndex,
    VAR(Port_PinDirectionType, PORT_VAR) chenDirection
)
{
    /* Point to the Port Pin PCR register address */
    /** @note: Violates MISRA 2004 Required Rules 17.4, pointer arithmetic other than array indexing used
                     See @ref Siu_LLD_C_REF_6 */
    VAR(uint16, PORT_VAR) pinPad = (uint16)Port_ConfigPtr->Port_LLD_PinConfPtr[PinIndex].SIUPin;

    /* Return value */
    VAR(uint8, PORT_VAR) pinDirError = (uint8)0x0;

    /* Bit Offset and Table value for change direction flag word*/
    VAR(uint16, PORT_VAR) pinDescBitOffset = (uint16)(pinPad & SIU_MODE_BIT_OFFSET_MASK);
    VAR(uint16, PORT_VAR) pinChangeDirFlagWord = Port_GPIODirection[(uint16)((uint16)pinPad>>4)];

    /* Check the Direction changeability option */
    /** @note: Violates MISRA 2004 Required Rules 17.4, pointer arithmetic other than array indexing used
                  See @ref Siu_LLD_C_REF_6 */
    /** @note: Violates MISRA 2004 Required Rules 12.6, boolean expression required for operator: '||'; the -strong(B,...) 
                 option can help provide Boolean-by-enforcement
                 See @ref Siu_LLD_C_REF_7 */
    if ((Port_ConfigPtr->Port_LLD_PinConfPtr[PinIndex].DC) || (pinChangeDirFlagWord & (uint16)(1UL<<pinDescBitOffset)) )
    {
        /* Configures Port Pin as Output */
        if (chenDirection == PORT_PIN_OUT)
        {
            /** @note: Violates MISRA 2004 Required Rules 10.1, Implicit conversion changes
          signedness, and 10.3, Cast of complex integer expression to larger type. See
          @ref Siu_LLD_C_REF_3 */
            REG_BIT_SET16(SIU_PCR(pinPad), SIU_PCR_OBE_ON);
        }
        /* Configures Port Pin as Input */
        else
        {
            /** @note: Violates MISRA 2004 Required Rules 10.1, Implicit conversion changes
                   signedness, and 10.3, Cast of complex integer expression to larger type. See
                   @ref Siu_LLD_C_REF_3 */
            REG_BIT_CLEAR16(SIU_PCR(pinPad), SIU_PCR_OBE_ON);
            REG_BIT_SET16(SIU_PCR(pinPad), SIU_PCR_IBE_ON);
        }
    }
    /* Direction changeability is NOT supported */
    else
    {
        pinDirError = (uint8)0x1;
    }
    return pinDirError;
}
#endif /* PORT_SET_PIN_DIRECTION_API == STD_ON */

/**
@brief      Refreshes port direction.
@details    This service shall refresh the direction of all configured ports to the configured
            direction. The PORT driver shall exclude from refreshing those port pins that are
        configured as pin direction changeable during runtime.

@param[in]     numPins    Number of pins to be refreshed

@return none

@pre  Port_Init must have been called
@post none
@remarks Covers PORT117, PORT142
*/
FUNC(void, PORT_CODE) PORT_Siu_RefreshPortDirection
(
    VAR(uint16, PORT_VAR) numPins
)
{
    /* Index of the port table */
    VAR(uint16, PORT_VAR) PinIndex = (uint16)0x0;

    /* Initialize All Configured Port Pins that aren't direction changable */
    for (PinIndex = (uint16)0x0; PinIndex < numPins; PinIndex++)
    {
        /** @note: Violates MISRA 2004 Required Rules 17.4, pointer arithmetic other than array indexing used
                     See @ref Siu_LLD_C_REF_6 */
        if ((boolean)FALSE == Port_ConfigPtr->Port_LLD_PinConfPtr[PinIndex].DC)
        {
            /* Point to the Port Pin PCR register address*/
            /** @note: Violates MISRA 2004 Required Rules 17.4, pointer arithmetic other than array indexing used
                               See @ref Siu_LLD_C_REF_6 */
            VAR(uint16, PORT_VAR) pinPad = (uint8)Port_ConfigPtr->Port_LLD_PinConfPtr[PinIndex].SIUPin;

           /* Configures Port Pin as Output */
           /** @note: Violates MISRA 2004 Required Rules 17.4, pointer arithmetic other than array indexing used
                            See @ref Siu_LLD_C_REF_6 */
           if (Port_ConfigPtr->Port_LLD_PinConfPtr[PinIndex].PCR & SIU_PCR_OBE)
           {
              /** @note: Violates MISRA 2004 Required Rules 10.1, Implicit conversion changes
        signedness, and 10.3, Cast of complex integer expression to larger type.
        See @ref Siu_LLD_C_REF_3 */
              REG_BIT_SET16(SIU_PCR(pinPad), SIU_PCR_OBE);
           }
           else
           {
              /** @note: Violates MISRA 2004 Required Rules 10.1, Implicit conversion changes
        signedness, and 10.3, Cast of complex integer expression to larger type.
        See @ref Siu_LLD_C_REF_3 */
              REG_BIT_CLEAR16(SIU_PCR(pinPad), SIU_PCR_OBE);
           }
           /* Configures Port Pin as Input */
           /** @note: Violates MISRA 2004 Required Rules 17.4, pointer arithmetic other than array indexing used
                            See @ref Siu_LLD_C_REF_6 */
           if (Port_ConfigPtr->Port_LLD_PinConfPtr[PinIndex].PCR & SIU_PCR_IBE)
           {
              /** @note: Violates MISRA 2004 Required Rules 10.1, Implicit conversion changes
        signedness, and 10.3, Cast of complex integer expression to larger type.
        See @ref Siu_LLD_C_REF_3 */
              REG_BIT_SET16(SIU_PCR(pinPad), SIU_PCR_IBE);
           }
           else
           {
              /** @note: Violates MISRA 2004 Required Rules 10.1, Implicit conversion changes
        signedness, and 10.3, Cast of complex integer expression to larger type.
        See @ref Siu_LLD_C_REF_3 */
              REG_BIT_CLEAR16(SIU_PCR(pinPad), SIU_PCR_IBE);
           }
        }
    }
}

#if (PORT_SET_PIN_MODE_API == STD_ON)
/**
@brief      Sets the port pin mode.
@details    The function will set the port pin mode of the referenced pin during runtime.

@param[in]  PinIndex        Pin ID number
@param[in]  chu8Mode        New Port Pin mode to be set on port pin


@return Error code after execution
@retval 0   No error occured
@retval PORT_E_MODE_UNCHANGEABLE   Pin mode cannot be changed
@retval PORT_E_PARAM_INVALID_MODE  Invalid mode

@pre  Port_Init must have been called
@post none
@remarks Covers PORT117, PORT145
*/
FUNC(uint8, PORT_CODE) PORT_Siu_SetPinMode
(
    VAR(Port_PinType, PORT_VAR) PinIndex,
    VAR(Port_PinModeType, PORT_VAR) chu8Mode
)
{
    /* Pin description variables */
    VAR(uint16, PORT_VAR) pinDescWord, pinDirFlagWord;
    VAR(Port_PinModeType, PORT_VAR) pinModeIndex;
    VAR(uint8, PORT_VAR) pinDescBitOffset;

    /* Return value */
    VAR(uint8, PORT_VAR) pinModeError = (uint8)0x0;

    /* Point to the Port Pin PCR register address*/
    /** @note: Violates MISRA 2004 Required Rules 17.4, pointer arithmetic other than array indexing used
                     See @ref Siu_LLD_C_REF_6 */
    VAR(uint16, PORT_VAR) pinPad = (uint16)Port_ConfigPtr->Port_LLD_PinConfPtr[PinIndex].SIUPin;

    if ((Port_PinModeType)chu8Mode >= PAD_MODE_OPTIONS)
    {
        pinModeError = PORT_E_PARAM_INVALID_MODE;
    }
    else
    {
        /* Code of the pin mode */
        pinModeIndex = (Port_PinModeType)chu8Mode;

        /* Bit offset of Pin index inside the pin description matrix */
        pinDescBitOffset = (uint8)(pinPad & SIU_MODE_BIT_OFFSET_MASK);

        /* Selected word inside the pin description matrix */
        pinDescWord = (uint16)Port_PinDescription[pinModeIndex][(uint8)((uint16)pinPad>>4)];

        /* Check if desired mode is valid for selected pin */
        if (pinDescWord & (uint16)(1UL<<pinDescBitOffset))
        {
            pinDirFlagWord = Port_GPIODirection[(uint8)((uint16)pinPad>>4)];
            if (chu8Mode == PORT_GPIO_MODE)
            {   /* Set the change direction flag */
                pinDirFlagWord |= (uint16)(1UL<<pinDescBitOffset);
            }
            else
            {   /* Reset the change direction flag */
                pinDirFlagWord &= (uint16)(~((uint16)(1UL<<pinDescBitOffset)));
            }
            Port_GPIODirection[(uint8)((uint16)pinPad>>4)] = pinDirFlagWord;

            /** @note: Violates MISRA 2004 Required Rules 10.1, Implicit conversion changes signedness,
                and 10.3, Cast of complex integer expression to larger type. See @ref Siu_LLD_C_REF_3 */
            /* Clear the previous mode */
            REG_BIT_CLEAR16(SIU_PCR(pinPad), (uint16)SIU_PCR_PA);

            /* Set the new mode in PCR */
            REG_BIT_SET16(SIU_PCR(pinPad), ((uint16)chu8Mode<<SIU_PCR_PA_OFFSET));
        }
        else
        {
            /* Check if exist a possible alternative mode for this pin */
            for (pinModeIndex = (uint8)0x1; pinModeIndex < PAD_MODE_OPTIONS; pinModeIndex++)
            {
                pinDescWord = (uint16)Port_PinDescription[pinModeIndex][(uint16)(pinPad>>(uint8)4)];

            /* A possible mode has found */
                if (pinDescWord & (uint16)(1UL<<pinDescBitOffset))
                {
                   break;
                }
            }
            /* No possible modes for this pin. The mode is unchangeable */
            if (pinModeIndex == PAD_MODE_OPTIONS)
            {
                pinModeError = (uint8)PORT_E_MODE_UNCHANGEABLE;
            }
            /* Desired mode is NOT valid for this pin. The mode is invalid */
            else
            {
                pinModeError = (uint8)PORT_E_PARAM_INVALID_MODE;
            }
        }
    }
    
    return pinModeError;
}
#endif /* (PORT_SET_PIN_MODE_API == STD_ON) */

#define PORT_STOP_SEC_CODE
/**
@file  Siu_LLD.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
      "#include" - See @ref Siu_LLD_C_REF_2
@note Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h -
      See @ref Siu_LLD_C_REF_5
*/
#include "MemMap.h"

#endif

/******************************************************************************

  DIO_LLD

 *****************************************************************************/

#if (( USE_DIO_MODULE == STD_ON )  && ((( USE_PORT_MODULE == STD_ON ) && ( SIU_LLD_MODULE_ID == 124 ) ) || (USE_PORT_MODULE == STD_OFF)))

#include "Std_Types.h"
#include "Siu_LLD.h"

/***************** Header Version Information [DIO82] [DIO106] ****************/
/* Reg_eSys_SIU.h version check start */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((SIU_AR_MAJOR_VERSION_REG != SIU_AR_MAJOR_VERSION_LLD_C ) ||\
        (SIU_AR_MINOR_VERSION_REG != SIU_AR_MINOR_VERSION_LLD_C ) || \
        (SIU_AR_PATCH_VERSION_REG != SIU_AR_PATCH_VERSION_LLD_C ) )
        #error "AUTOSAR Version Numbers of Dio.h and Siu_LLD.c are different"
    #endif
#endif
#if ((SIU_SW_MAJOR_VERSION_REG != SIU_SW_MAJOR_VERSION_LLD_C ) ||\
    (SIU_SW_PATCH_VERSION_REG != SIU_SW_PATCH_VERSION_LLD_C ) ||\
    (SIU_SW_MINOR_VERSION_REG != SIU_SW_MINOR_VERSION_LLD_C ))
    #error "Software Version Numbers of Dio.h and Siu_LLD.c are different"
#endif
#if ((SIU_VENDOR_ID_REG != SIU_VENDOR_ID_LLD_C ))
    #error "VENDOR ID for Dio.h and Siu_LLD.c is different"
#endif
/* Reg_eSys_SIU.h version check end */

/* Dio.h version check start */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((DIO_AR_MAJOR_VERSION != SIU_AR_MAJOR_VERSION_LLD_C ) ||\
        (DIO_AR_MINOR_VERSION != SIU_AR_MINOR_VERSION_LLD_C ) || \
        (DIO_AR_PATCH_VERSION != SIU_AR_PATCH_VERSION_LLD_C ) )
        #error "AUTOSAR Version Numbers of Dio.h and Siu_LLD.c are different"
    #endif
#endif
#if ((DIO_SW_MAJOR_VERSION != SIU_SW_MAJOR_VERSION_LLD_C ) ||\
    (DIO_SW_PATCH_VERSION != SIU_SW_PATCH_VERSION_LLD_C ) ||\
    (DIO_SW_MINOR_VERSION != SIU_SW_MINOR_VERSION_LLD_C ))
/** @note See @ref Siu_LLD_C_REF_3 */
    #error "Software Version Numbers of Dio.h and Siu_LLD.c are different"
#endif
#if ((DIO_VENDOR_ID != SIU_VENDOR_ID_LLD_C ))
    #error "VENDOR ID for Dio.h and Siu_LLD.c is different"
#endif
/* Dio.h version check end */

/* Siu_LLD.h version check start */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((SIU_AR_MAJOR_VERSION_LLD_H != SIU_AR_MAJOR_VERSION_LLD_C ) ||\
        (SIU_AR_MINOR_VERSION_LLD_H != SIU_AR_MINOR_VERSION_LLD_C ) || \
        (SIU_AR_PATCH_VERSION_LLD_H != SIU_AR_PATCH_VERSION_LLD_C ) )
        #error "AUTOSAR Version Numbers of Siu_LLD.h and Siu_LLD.c are different"
    #endif
#endif
#if ((SIU_SW_MAJOR_VERSION_LLD_H != SIU_SW_MAJOR_VERSION_LLD_C ) ||\
    (SIU_SW_PATCH_VERSION_LLD_H != SIU_SW_PATCH_VERSION_LLD_C ) ||\
    (SIU_SW_MINOR_VERSION_LLD_H != SIU_SW_MINOR_VERSION_LLD_C ))
    #error "Software Version Numbers of Siu_LLD.h and Siu_LLD.c are different"
#endif
#if ((SIU_VENDOR_ID_LLD_H != SIU_VENDOR_ID_LLD_C ))
    #error "VENDOR ID for Siu_LLD.h and Siu_LLD.c is different"
#endif
/* Siu_LLD.h version check end */


STATIC VAR(Dio_PortLevelType, DIO_VAR) Dio_DummyArray[2] = {STD_LOW,STD_LOW};

/*****************************************************************************
    Local function prototypes
*****************************************************************************/

#define DIO_START_SEC_CODE
/**
@file    Siu_LLD.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
"#include" - See @ref Siu_LLD_C_REF_2
@note Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h - See @ref
Siu_LLD_C_REF_5
*/
#include "MemMap.h"

#if (DIO_REVERSEPORTBITS == STD_ON)
/**
@brief   reverse bits
@details reverses the bits from the input value

@param[in] Level        value to be reversed

@return returns the reversed bits value of the input parameter

@pre this function can be used only if DIO_REVERSEPORTBITS is set in the
plugin, function assumes that port width is 16
@post none
*/
STATIC FUNC(Dio_PortLevelType, DIO_CODE)reverse_bits16( VAR(Dio_PortLevelType, DIO_CODE) Level);
#endif

/*****************************************************************************
    Local functions
*****************************************************************************/

#if (DIO_REVERSEPORTBITS == STD_ON)
/**
@brief   reverse bits
@details reverses the bits from the input value

@param[in] Level        value to be reversed

@return returns the reversed bits value of the input parameter

@pre this function can be used only if DIO_REVERSEPORTBITS is set in the
plugin, function assumes that port width is 16
@post none

*/
STATIC FUNC(Dio_PortLevelType, DIO_CODE)reverse_bits16
(
    VAR(Dio_PortLevelType, DIO_CODE) Level
)
{
    VAR(Dio_PortLevelType, DIO_VAR) r = Level; /* r will be reversed bits of Level; first get LSB of
                          Level */
    VAR(Dio_PortLevelType, DIO_VAR) s = 15; /* count shifts needed due to trailing 0s */

    Level= (Dio_PortLevelType)(Level>>1);

    for (; Level!=0; Level >>= 1)
    {
        r = (Dio_PortLevelType)(r<<1);
        r = (Dio_PortLevelType)(r |((Dio_PortLevelType)(Level & (Dio_PortLevelType)1)));
        s--;
    }
/**@note  Violates MISRA 2004 Advisory Rule 11.1 Conversions shall not be performed between a pointer to 
     a function and any type other than an integral type.This rule can not be avoided  - See Siu_LLD_C_REF_8 */
    r = (Dio_PortLevelType)(r<<s); /* shift when v's highest bits are zero */
    return r;
}
#endif

/*****************************************************************************
    Global functions
*****************************************************************************/

/**
@brief   Returns the value of the specified DIO channel.
@note  Violates MISRA 2004 Advisory Rule 11.1 Conversions shall not be performed between a pointer to 
     a function and any type other than an integral type.This rule can not be avoided  - See Siu_LLD_C_REF_8
@details The function will return the value of the specified DIO channel.

@param[in]     ChannelId          specifies the required channel id

@return returns the level of the corresponding pin as STD_HIGH or STD_LOW
@retval STD_HIGH The physical level of the corresponding Pin is STD_HIGH
@retval STD_LOW The physical level of the corresponding Pin is STD_LOW

@pre none
@post none
*/

FUNC (Dio_LevelType, DIO_CODE) DIO_SIU_ReadChannel
(
    CONST(Dio_ChannelType, DIO_CONST) ChannelId
)
{
    VAR(Dio_LevelType, DIO_VAR) value;
    /** @note Violates MISRA 2004 Required Rules 11.3, Cast from unsigned long to pointer.
This violation is due to the pointer arithematic used to
write/ read the data to/from the registers.See @ref Siu_LLD_C_REF_4 */
    if ((REG_READ16(SIU_PCR((uint32)(ChannelId)))) & SIU_PCR_IBE_ON)
    {
        /** @note Violates MISRA 2004 Required Rules 11.3, Cast from unsigned long to pointer.
                  This violation is due to the pointer arithematic used to
                  write/ read the data to/from the registers.See @ref Siu_LLD_C_REF_4 */
        value = (Dio_LevelType)( REG_READ8(SIU_GPDI((uint32)(ChannelId))) );
    }
    else
    {
        /** @note Violates MISRA 2004 Required Rules 11.3, Cast from unsigned long to pointer.
                  This violation is due to the pointer arithematic used to
                  write/ read the data to/from the registers.See @ref Siu_LLD_C_REF_4 */
        value = (Dio_LevelType)( REG_READ8(SIU_GPDO((uint32)(ChannelId))) );
    }

    return value;
}

/**
@brief   Service to set a level of a channel.
@details If the specified channel is configured as an output channel, the function
         will set the specified Level for the specified channel. If the specified channel is
         configured as an input channel, the function will have no influence on
         the physical output.

@param[in]     ChannelId          specifies the required channel id
@param[in]     Level              specifies the desired level of the channel

@return none

@pre none
@post none
*/
FUNC (void, DIO_CODE) DIO_SIU_WriteChannel
(
    CONST(Dio_ChannelType, DIO_CONST) ChannelId,
    CONST(Dio_LevelType, DIO_CONST) Level
)
{
    /** @note Violates MISRA 2004 Required Rules 11.3, Cast from unsigned long to pointer.
              This violation is due to the pointer arithematic used to
              write/ read the data to/from the registers.See @ref Siu_LLD_C_REF_4 */
     /**@note  Violates MISRA 2004 Advisory Rule 11.1 Conversions shall not be performed between a pointer to 
     a function and any type other than an integral type.This rule can not be avoided  - See Siu_LLD_C_REF_8 */
    REG_WRITE8(SIU_GPDO(ChannelId), (Level));

}

/**
@brief   Returns the level of all channels of that port.
@details The function will return the level of all channels of that port.

@param[in]     PortId          specifies the required port id

@return Level of all channels of that port

@pre none
@post none
*/
FUNC (Dio_PortLevelType, DIO_CODE) DIO_SIU_ReadPort
(
    CONST(Dio_PortType, DIO_CONST) PortId
)
{
#if ((IPV_SIU==IPV_SIU_00_02_11_00) || (IPV_SIU==IPV_SIU_00_02_08_07))
    return (Dio_PortLevelType)Dio_DummyArray[((uint8)(PortId ) & (uint8)0x0)];
#else
/* Function implementaton for all other products */
#if (DIO_READZERO_UNDEFINEDPORTS == STD_OFF)
#if (DIO_REVERSEPORTBITS == STD_ON)
    return reverse_bits16((Dio_PortLevelType)( REG_READ16(SIU_PGPDI( ( (uint32)(PortId )<< 1UL))) ));
#else
    return (Dio_PortLevelType)( REG_READ16(SIU_PGPDI( ( (uint32)(PortId )<< 1UL))) );
#endif
#else
#if (DIO_REVERSEPORTBITS == STD_ON)
    return reverse_bits16((Dio_PortLevelType)( REG_READ16(SIU_PGPDI( ( (uint32)(PortId )<< 1UL))) ) & undefined_portmask[PortId]);
#else
/** @note Violates MISRA 2004 Required Rules 11.3, Cast from unsigned long to pointer. This violation is due to the pointer arithematic used to write/ read the data to/from the registers. 
          - See @refSiu_LLD_C_REF_4
         @note  Violates MISRA 2004 Advisory Rule 11.1 Conversions shall not be performed between a pointer to 
     a function and any type other than an integral type.This rule can not be avoided  - See @ref Siu_LLD_C_REF_8. */
    return (Dio_PortLevelType)( REG_READ16(SIU_PGPDI( ( (uint32)(PortId )<< 1UL))) & undefined_portmask[PortId]);
#endif
#endif
#endif
}


/**
@brief   Service to set a value of the port.
@details The function will set the specified value for the specified port.

@param[in]     PortId          specifies the required port id
@param[in]     Level          specifies the required level for the port pins

@return none

@pre none
@post none
*/
FUNC (void, DIO_CODE) DIO_SIU_WritePort
(
    CONST(Dio_PortType, DIO_CONST) PortId,
    CONST(Dio_PortLevelType, DIO_CONST) Level
)
{
#if ((IPV_SIU==IPV_SIU_00_02_11_00) || (IPV_SIU==IPV_SIU_00_02_08_07))
/**@note  Violates MISRA 2004 Advisory Rule 11.1 Conversions shall not be performed between a pointer to 
     a function and any type other than an integral type.This rule can not be avoided  - See Siu_LLD_C_REF_8 */
    Dio_DummyArray[1] = (Dio_PortLevelType)((uint32)(PortId) + (uint32)(Level));
#else
/* Function implementaton for all other products */
#if (DIO_REVERSEPORTBITS == STD_ON)
    REG_WRITE16(SIU_PGPDO(((uint32)(PortId) << 1UL)), (reverse_bits16(Level)));
#else
/** @note Violates MISRA 2004 Required Rules 11.3, Cast from unsigned long to pointer.
          This violation is due to the pointer arithematic used to
          write/ read the data to/from the registers.See @ref Siu_LLD_C_REF_4*/
    REG_WRITE16(SIU_PGPDO(((uint32)(PortId) << 1UL)), (Level));
#endif
#endif
}


/**
@brief   This Service reads a subset of the adjoining bits of a port.
@details The Dio_ReadChannelGroup function will read a subset of the adjoining bits of a
         port (channel group).

@param[in]     ChannelGroupIdPtr          pointer to the channel group

@return The level channel group pins - Dio_PortLevelType

@pre none
@post none
*/
FUNC (Dio_PortLevelType, DIO_CODE) DIO_SIU_ReadChannelGroup
(
    P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_APPL_CONST) ChannelGroupIdPtr
)
{
#if ((IPV_SIU==IPV_SIU_00_02_11_00) || (IPV_SIU==IPV_SIU_00_02_08_07))
    return (Dio_PortLevelType)Dio_DummyArray[((uint8)(ChannelGroupIdPtr->port ) & (uint8)0x0)];
#else
    /** @note Violates MISRA 2004 Required Rules 11.3, Cast from unsigned long to pointer.This violation is due to the pointer arithematic used to write/ read the data to/from the registers.
    See @ref Siu_LLD_C_REF_4.
    @note  Violates MISRA 2004 Advisory Rule 11.1 Conversions shall not be performed between a pointer to 
     a function and any type other than an integral type.This rule can not be avoided  - See Siu_LLD_C_REF_8 */
/* Function implementaton for all other products */
    return (Dio_PortLevelType)( ( (REG_READ16( SIU_PGPDI(((uint32)(ChannelGroupIdPtr->port) << (uint32)1UL) ) ) ) & (ChannelGroupIdPtr->mask) ) >> (ChannelGroupIdPtr->offset) );
#endif
}


/**
@brief   Service to set a subset of the adjoining bits of a port to a specified level.
@details The function will set a subset of the adjoining bits of
         a port (channel group) to a specified level. The will not change
         the remaining channels of the port and channels which are configured as input. The
         function will do the masking of the channel group. The function
         will do the shifting so that the values written by the function
         are aligned to the LSB.

@param[in]     ChannelGroupIdPtr          pointer to the channel group
@param[in]     Level                      desired level for the channel group

@return none

@pre none
@post none
*/
FUNC (void, DIO_CODE) DIO_SIU_WriteChannelGroup
(
    P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_APPL_CONST) ChannelGroupIdPtr,
    CONST(Dio_PortLevelType, DIO_CONST) Level
)
{
#if ((IPV_SIU==IPV_SIU_00_02_11_00) || (IPV_SIU==IPV_SIU_00_02_08_07))
/**@note  Violates MISRA 2004 Advisory Rule 11.1 Conversions shall not be performed between a pointer to 
     a function and any type other than an integral type.This rule can not be avoided  - See Siu_LLD_C_REF_8 */
    Dio_DummyArray[1] = (Dio_PortLevelType)((uint32)(ChannelGroupIdPtr->port ) + (uint32)(Level));
#else
    /** @note Violates MISRA 2004 Required Rules 11.3, Cast from unsigned long to pointer.
    This violation is due to the pointer arithematic used to
write/ read the data to/from the registers.See @ref Siu_LLD_C_REF_4 */
    REG_WRITE32(SIU_MPGPDO( (uint32) ((uint32)(ChannelGroupIdPtr->port) << (DIO_PORTID_SHIFT))), ( ( ((uint32)(Level) << (ChannelGroupIdPtr->offset)) & (DIO_CHANNELGRP_OFFSET_PINS) ) | (((uint32)(ChannelGroupIdPtr->mask) << (DIO_CHANNELGRP_MASK_PINS ))) ) );
#endif
}


#if (DIO_MASKEDWRITEPORT_API == STD_ON)
/**
@brief   DIO Mask write port using mask
@details writes a DIO port with masked value

@param[in]     PortId        specifies the required port id
@param[in]     Level         specifies the required level for the port pins
@param[in]     Mask          specifies the Mask value of the port

@return none

@pre none
@post none
*/
FUNC (void, DIO_CODE) DIO_SIU_MaskedWritePort
(
 CONST(Dio_PortType, DIO_CONST) PortId,
 CONST(Dio_PortLevelType, DIO_CONST) Level,
 CONST(Dio_PortLevelType, DIO_CONST) Mask
)
{
    /** @note Violates MISRA 2004 Required Rules 11.3, Cast from unsigned long to pointer.
              This violation is due to the pointer arithematic used to
              write/ read the data to/from the registers.See @ref Siu_LLD_C_REF_4*/
    REG_WRITE32(SIU_MPGPDO( (uint32) ((uint32) PortId << DIO_PORTID_SHIFT)),  (((uint32) Mask << DIO_CHANNELGRP_MASK_PINS) | (uint32) Level));
}
#endif /* DIO_MASKEDWRITEPORT_API */
#define DIO_STOP_SEC_CODE
/**
@file  Siu_LLD.c
@note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
      "#include" - See @ref Siu_LLD_C_REF_2
@note Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h -
      See @ref Siu_LLD_C_REF_5
*/
#include "MemMap.h"

#endif /* (( USE_DIO_MODULE == STD_ON )  && ((( USE_PORT_MODULE == STD_ON ) &&
      ( SIU_LLD_MODULE_ID == 124 ) ) || (USE_PORT_MODULE == STD_OFF)))*/


#ifdef __cplusplus
}
#endif

/* End of File */
