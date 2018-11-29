/**
    @file    Siu_LLD.h
    @version 2.0.0

    @brief   AUTOSAR Port - SIU low level driver interface.
    @details API of the SIU low level driver.

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

@section SIU_LLD_H_REF_1
Violates MISRA 2004 Advisory Rule 19.15, Repeated include files modules.h, Port_Cfg.h and
Siu_LLD_CfgEx.h
This comes from the order of includes in the .c file and from include dependencies.
As a safe approach, any file must include all its dependencies. The h files are guarded against
multiple inclusion.

@section SIU_LLD_H_REF_2
Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h
There are different kinds of execution code sections.
*/

#ifndef SIU_LLD_H
#define SIU_LLD_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
@file  Siu_LLD.h
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file modules.h -
       See @ref SIU_LLD_H_REF_1
*/
#include "modules.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@brief Parameters that shall be published within the driver header file and also in the
       module's description file
@remarks Covers BSW00374, BSW00379, BSW00318
@remarks Covers DIO106
@{
*/
#define SIU_VENDOR_ID_LLD_H           43
#define SIU_AR_MAJOR_VERSION_LLD_H    3
#define SIU_AR_MINOR_VERSION_LLD_H    0
#define SIU_AR_PATCH_VERSION_LLD_H    0

#define SIU_SW_MAJOR_VERSION_LLD_H    2
#define SIU_SW_MINOR_VERSION_LLD_H    0
#define SIU_SW_PATCH_VERSION_LLD_H    0
/**@}*/

#if (USE_PORT_MODULE == STD_ON)
/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/**
@file  Siu_LLD.h
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include files Port_Cfg.h and
Siu_LLD_CfgEx.h - See @ref SIU_LLD_H_REF_1
*/
#include "Port_Cfg.h"
#include "Siu_LLD_CfgEx.h"

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if the files Siu_LLD.h and Port_Cfg.h have the same vendor */
#if (SIU_VENDOR_ID_LLD_H != PORT_VENDOR_ID_CFG_H)
    #error "Siu_LLD.h and Port_Cfg.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if the files Siu_LLD.h and Port_Cfg.h have the same version */
    #if ((SIU_AR_MAJOR_VERSION_LLD_H != PORT_AR_MAJOR_VERSION_CFG_H) || \
         (SIU_AR_MINOR_VERSION_LLD_H != PORT_AR_MINOR_VERSION_CFG_H) || \
         (SIU_AR_PATCH_VERSION_LLD_H != PORT_AR_PATCH_VERSION_CFG_H))
      #error "AutoSar Version Numbers of Siu_LLD.h and Port_Cfg.h are different"
    #endif
#endif
#if ((SIU_SW_MAJOR_VERSION_LLD_H != PORT_SW_MAJOR_VERSION_CFG_H) || \
     (SIU_SW_MINOR_VERSION_LLD_H != PORT_SW_MINOR_VERSION_CFG_H) || \
     (SIU_SW_PATCH_VERSION_LLD_H != PORT_SW_PATCH_VERSION_CFG_H))
  #error "Software Version Numbers of Siu_LLD.h and Port_Cfg.h are different"
#endif

/**
@file    Siu_LLD.h
@remarks Covers PORT114
*/
#if (SIU_VENDOR_ID_LLD_H != SIU_VENDOR_ID_EXT_H)
    #error "Siu_LLD.h and Siu_LLD_CfgEx.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    #if ((SIU_AR_MAJOR_VERSION_LLD_H != SIU_AR_MAJOR_VERSION_EXT_H) || \
         (SIU_AR_MINOR_VERSION_LLD_H != SIU_AR_MINOR_VERSION_EXT_H) || \
         (SIU_AR_PATCH_VERSION_LLD_H != SIU_AR_PATCH_VERSION_EXT_H))
      #error "AutoSar Version Numbers of Siu_LLD.h and Siu_LLD_CfgEx.h are different"
    #endif
#endif
#if ((SIU_SW_MAJOR_VERSION_LLD_H != SIU_SW_MAJOR_VERSION_EXT_H) || \
     (SIU_SW_MINOR_VERSION_LLD_H != SIU_SW_MINOR_VERSION_EXT_H) || \
     (SIU_SW_PATCH_VERSION_LLD_H != SIU_SW_PATCH_VERSION_EXT_H))
  #error "Software Version Numbers of Siu_LLD.h and Siu_LLD_CfgEx.h are different"
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
/**
@brief Allocate defined section for PORT code
*/
#define PORT_START_SEC_CODE
/**
@file  Siu_LLD.h
@note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h -
       See @ref SIU_LLD_H_REF_2
*/
#include "MemMap.h"


/**
@brief        Initializes the SIU IP Driver
@details      The function PORT_Siu_Init will initialize ALL ports and port pins with the
              configuration set pointed to by the parameter ConfigPtr.

@param[in]     ConfigPtr      A pointer to the structure which contains initialization parameters

@return none

@pre    none
@post   No function of the driver is executed without the initialisation of the module.
*/
FUNC(void, PORT_CODE) PORT_Siu_Init(P2CONST(Port_ConfigType,AUTOMATIC,PORT_APPL_DATA) ConfigPtr);


/**
@brief   Sets the port pin direction
@details Sets the pin direction at runtime, changing it only if the pin is configurated as changeable.

@param[in]     PinIndex             Pin ID number
@param[in]     chenDirection            Port Pin direction

@return Error code after execution
@retval 0   No error occured
@retval 1   Pin direction cannot be changed

@pre  Port_Init must have been called
@post none

@remarks Covers PORT086, PORT117, PORT141
*/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
FUNC (uint8, PORT_CODE) PORT_Siu_SetPinDirection(VAR(Port_PinType, PORT_VAR) PinIndex,
                                                VAR(Port_PinDirectionType, PORT_VAR) chenDirection);
#endif


/**
@brief   Refreshes port direction.
@details This service shall refresh the direction of all configured ports to the configured direction.
         The PORT driver shall exclude from refreshing those port pins that are configured as pin
         direction changeable during runtime.

@param[in]     numPins    Number of pins to be refreshed

@return none

@pre  Port_Init must have been called
@post none

@remarks Covers PORT117, PORT142
*/
FUNC (void, PORT_CODE) PORT_Siu_RefreshPortDirection(VAR(uint16, PORT_VAR) numPins);


#if (PORT_SET_PIN_MODE_API == STD_ON)
/**
@brief   Sets the port pin mode.
@details The function will set the port pin mode of the referenced pin during runtime

@param[in]     PinIndex     Pin ID number
@param[in]     chu8Mode        New Port Pin mode to be set on port pin

@return Error code after execution
@retval 0   No error occured
@retval PORT_E_MODE_UNCHANGEABLE   Pin mode cannot be changed
@retval PORT_E_PARAM_INVALID_MODE  Invalid mode

@pre  Port_Init must have been called
@post none

@remarks Covers PORT117, PORT145
*/
FUNC (uint8, PORT_CODE) PORT_Siu_SetPinMode(VAR(Port_PinType, PORT_VAR) PinIndex,
                                            VAR(Port_PinModeType, PORT_VAR) chu8Mode);
#endif

#define PORT_STOP_SEC_CODE
#include "MemMap.h"
#endif  /*USE_PORT_MODULE */

#if (USE_DIO_MODULE == STD_ON)
#include "Reg_eSys.h"
#include "Reg_eSys_SIU.h"
#include "Dio.h"

#define DIO_PORTID_SHIFT                    (uint32)2UL
#define DIO_CHANNELGRP_OFFSET_PINS          (uint32)0x0000FFFFUL
#define DIO_CHANNELGRP_MASK_PINS            (uint32)16UL

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and Dio header file are of the same vendor */
#if (SIU_VENDOR_ID_LLD_H != DIO_VENDOR_ID)
    #error "Siu_LLD.h and Dio.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Dio header file are of the same Autosar version */
    #if ((SIU_AR_MAJOR_VERSION_LLD_H != DIO_AR_MAJOR_VERSION) || \
         (SIU_AR_MINOR_VERSION_LLD_H != DIO_AR_MINOR_VERSION) || \
         (SIU_AR_PATCH_VERSION_LLD_H != DIO_AR_PATCH_VERSION))
      #error "AutoSar Version Numbers of Siu_LLD.h and Dio.h are different"
    #endif
#endif
/* Check if source file and Dio header file are of the same Software version */
#if ((SIU_SW_MAJOR_VERSION_LLD_H != DIO_SW_MAJOR_VERSION) || \
     (SIU_SW_MINOR_VERSION_LLD_H != DIO_SW_MINOR_VERSION) || \
     (SIU_SW_PATCH_VERSION_LLD_H != DIO_SW_PATCH_VERSION))
  #error "Software Version Numbers of Siu_LLD.h and Dio.h are different"
#endif


#define DIO_START_SEC_CODE
#include "MemMap.h"

/**
@brief   Returns the value of the specified DIO channel.
@details The  function will return the value of the specified DIO channel.

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
);

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
);

/**
@brief   Returns the level of all channels of that port.
@details The function will return the level of all channels of that port.

@param[in]     PortId          specifies the required port id

@return returns the level of the port pins
@retval Dio_PortLevelType

@pre none
@post none
*/
FUNC (Dio_PortLevelType, DIO_CODE) DIO_SIU_ReadPort
(
    CONST(Dio_PortType, DIO_CONST) PortId
);

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
);

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
);

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
);

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
 );
#endif /* DIO_MASKEDWRITEPORT_API */


#define DIO_STOP_SEC_CODE
#include "MemMap.h"
#endif /*USE_DIO_MODULE*/

#ifdef __cplusplus
}
#endif

#endif /* SIU_LLD_H */
