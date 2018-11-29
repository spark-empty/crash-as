/*!
 * @file    Dio.h
 *
 * @version 2.0.0
 * @brief   AUTOSAR Dio - driver API.
 * @details This file contains the DIO Autosar driver API.
 *
 * @addtogroup Dio
 * @{
 */

/***********************************************************************
 * PROJECT              AUTOSAR 3.0 MCAL
 * PLATFORM             PA
 * PERIPHERAL           SIU
 * DEPENDENCIES         none
 *
 * AUTOSAR VERSION      3.0.0
 * AUTOSAR REVISION     ASR_REL_3_0_REV_0003
 * AUTOSAR CONF.VARIANT
 * SW VERSION           2.0.0
 * BUILDVERSION         XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223
 *
 * COPYRIGHT : (c)      2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
 *                      ALL RIGHTS RESERVED
 ************************************************************************/

/*==================================================================================================
==================================================================================================*/

/**
 * @page misra_violations MISRA-C:2004 violations
 *
 * @section DIO_H_REF_1
 * Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to prevent the 
 * contents of a header file being included twice. This is not a violation since all header files 
 * are protected against multiple inclusions.
 */

#ifndef DIO_H
#define DIO_H

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************/
    /* Includes */
    /* 1) system and project includes */
    /* 2) needed interfaces from external units */
    /* 3) internal and external interfaces from this unit */
/******************************************************************/

/*************************** Include Files ************************/
/**
 * @file Dio.h
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file: 
 *       See @ref DIO_H_REF_1
 */
#include "Std_Types.h"
#include "Dio_Cfg.h"

/******************************************************************
| defines and macros (scope: module-local)
|-----------------------------------------------------------------*/
/*
 * @brief defines for versions checks of the header file
 * @remarks Covers DIO106
 */
#define DIO_MODULE_ID           120
#define DIO_VENDOR_ID           43
#define DIO_AR_MAJOR_VERSION    2
#define DIO_AR_MINOR_VERSION    2
#define DIO_AR_PATCH_VERSION    1

#define DIO_SW_MAJOR_VERSION    2
#define DIO_SW_MINOR_VERSION    0
#define DIO_SW_PATCH_VERSION    0


/******************************************************************
| File Version Checks
|-----------------------------------------------------------------*/

#ifdef CHECK_AUTOSAR_VERSION
    /* Std_Types.h version check start */
    #if ((DIO_AR_MAJOR_VERSION != STD_TYPES_AR_MAJOR_VERSION ) ||\
         (DIO_AR_MINOR_VERSION != STD_TYPES_AR_MINOR_VERSION ))
    #error "AUTOSAR Version Numbers of Dio.h and Std_Types.h are different"
    #endif
    /* Std_Types.h version check end */
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Dio_Cfg.h version check start */
    #if ((DIO_AR_MAJOR_VERSION != DIO_AR_MAJOR_VERSION_CFG_H ) ||\
        (DIO_AR_MINOR_VERSION != DIO_AR_MINOR_VERSION_CFG_H ) ||\
        (DIO_AR_PATCH_VERSION != DIO_AR_PATCH_VERSION_CFG_H ))
        #error "AUTOSAR Version Numbers of Dio.h and Dio_Cfg.h are different"
    #endif
#endif
#if ((DIO_SW_MAJOR_VERSION != DIO_SW_MAJOR_VERSION_CFG_H ) ||\
    (DIO_SW_PATCH_VERSION != DIO_SW_PATCH_VERSION_CFG_H ) ||\
    (DIO_SW_MINOR_VERSION != DIO_SW_MINOR_VERSION_CFG_H ))
    #error "Software Version Numbers of Dio.h and Dio_Cfg.h are different"
#endif
#if ((DIO_VENDOR_ID != DIO_VENDOR_ID_CFG_H ))
    #error "VENDOR ID for Dio.h and Dio_cfg.h is different"
#endif
/* Dio_Cfg.h version check end */


/******************************************************************
| Global Variable
|-----------------------------------------------------------------*/

/**
 * @brief   Invalid channel name requested.
 * @details Errors and exceptions that will be detected by the DIO driver.
 *
 * @requirements    DIO065.
 *
 * @api
 *
 * @remarks Covers DIO065
 */
#define DIO_E_PARAM_INVALID_CHANNEL_ID          (uint8)0x0AU
/**
 * @brief   Invalid port name requested.
 * @details Errors and exceptions that will be detected by the DIO driver.
 *
 * @requirements    DIO065.
 *
 * @api
 *
 * @remarks Covers DIO065
 */
#define DIO_E_PARAM_INVALID_PORT_ID             (uint8)0x14U
/**
 * @brief   Invalid ChannelGroup id passed.
 * @details Errors and exceptions that will be detected by the DIO driver.
 *
 * @requirements    DIO065.
 *
 * @api
 *
 * @remarks Covers DIO065
 */
#define DIO_E_PARAM_INVALID_GROUP_ID            (uint8)0x1FU
/**
 * @brief   API service called with NULL pointer.
 * @details Errors and exceptions that will be detected by the DIO driver.
 *
 * @requirements    DIO073.
 *
 * @api
 *
 * @remarks Covers DIO073
 */
#define  DIO_E_PARAM_INVALID_POINTER            (uint8)0x20U

/************************* API Service IDs ****************************/
/* DIO API numbers */

/**
 * @brief   API service ID for DIO Read Channel function.
 * @details Parameters used when raising an error/exception.
 *
 * @api
 *
 */
#define DIO_READCHANNEL_ID          (uint8)0x00U
/**
 * @brief   API service ID for DIO Write Channel function.
 * @details Parameters used when raising an error/exception.
 *
 * @api
 *
 */
#define DIO_WRITECHANNEL_ID         (uint8)0x01U
/**
 * @brief   API service ID for DIO Read Port function.
 * @details Parameters used when raising an error/exception.
 *
 * @api
 *
 */
#define DIO_READPORT_ID             (uint8)0x02U
/**
 * @brief   API service ID for DIO Write Port function.
 * @details Parameters used when raising an error/exception.
 *
 * @api
 *
 */
#define DIO_WRITEPORT_ID            (uint8)0x03U
/**
 * @brief   API service ID for DIO Read Channel Group function.
 * @details Parameters used when raising an error/exception.
 *
 * @api
 *
 */
#define DIO_READCHANNELGROUP_ID     (uint8)0x04U
/**
 * @brief   API service ID for DIO Write Channel Group function.
 * @details Parameters used when raising an error/exception.
 *
 * @api
 *
 */
#define DIO_WRITECHANNELGROUP_ID    (uint8)0x05U
/**
 * @brief   API service ID for DIO Get Version Info function.
 * @details Parameters used when raising an error/exception.
 *
 * @api
 *
 */
#define DIO_GETVERSIONINFO_ID       (uint8)0x12U
/**
 * @brief   API service ID for DIO Masked Write Port function.
 * @details Parameters used when raising an error/exception.
 *
 * @api
 *
 */
#define DIO_MASKEDWRITEPORT_ID      (uint8)0x06U

/*
 * @brief Instance ID of this dio driver.
 */
#define DIO_INSTANCE_ID             (uint8)0x00U

/*
 * @brief This provides levels(STD_HIGH or STD_LOW) of a DIO channel
 * @brief Dio_LevelType can be uint8,uint16,uint32
 * @remarks Covers DIO023
 * @remarks Implements DDIO01007
 */
typedef uint8 Dio_LevelType;


/******************************************************************
| exported function prototypes
|-----------------------------------------------------------------*/

/* Allocate defined section for DIO code */
#define DIO_START_SEC_CODE
/**
 * @file Dio.h
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h: 
 *       See @ref DIO_H_REF_1
 */
#include "MemMap.h"

#if ((DIO_VERSION_INFO_API == STD_ON) || defined(__DOXYGEN__))

/** 
 * @brief   Service to get the version information of this module.
 * @details The @p Dio_GetVersionInfo() function shall return the version
 *          information of this module. The version information includes:<br>
 *          - Module Id,
 *          - Vendor Id,
 *          - Vendor specific version numbers.
 *
 * @pre     This function can be used only if @p DIO_VERSION_INFO_API has been
 *          set in the plugin.
 *
 * @param[in,out] versioninfo       Pointer to where to store the version
 *                                  information of this module.
 *
 * @requirements    DIO139, DIO123, DIO124, DIO126.
 *
 * @api
 *
 * @remarks Covers DIO139, DIO123, DIO124, DIO126
 */
FUNC (void, DIO_CODE)Dio_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, DIO_VAR_FAST, DIO_APPL_DATA) versioninfo
);
#endif /* DIO_VERSION_INFO_API == STD_ON */

/**
 * @brief   Returns the value of the specified DIO channel.
 * @details The @p Dio_ReadChannel() function will return the value of the
 *          specified DIO channel.
 *
 * @param[in] ChannelId     Specifies the required channel id.
 * @return                  Returns the level of the corresponding pin as
 *                          @p STD_HIGH or @p STD_LOW.
 * @retval STD_HIGH         The logical level of the corresponding pin is 1.
 * @retval STD_LOW          The logical level of the corresponding Pin is 0.
 *
 * @requirements    DIO027, DIO058, DIO083, DIO084, DIO005, DIO085, DIO118,
 *                  DIO011, DIO012, DIO133.
 *
 * @api
 *
 * @remarks Covers DIO027, DIO058, DIO083, DIO084, DIO005, DIO085, DIO118, DIO011, DIO012,DIO133
 * @remarks Implements DDIO01001
 */
FUNC (Dio_LevelType, DIO_CODE) Dio_ReadChannel
(
    CONST(Dio_ChannelType, DIO_CONST) ChannelId
);

/**
 * @brief   Service to set a level of a channel.
 * @details If the specified channel is configured as an output channel, the @p
 *          Dio_WriteChannel() function shall set the specified Level for the
 *          specified channel. If the specified channel is configured as an
 *          input channel, the @p Dio_WriteChannel() function shall have no
 *          influence on the physical output and on the result of the next
 *          Read-Service.
 *
 * @param[in] ChannelId     Specifies the required channel id.
 * @param[in] Level         Specifies the channel desired level.
 *
 * @requirements    DIO028, DIO029, DIO057, DIO079, DIO119, DIO005, DIO006,
 *                  DIO064, DIO070, DIO134.
 *
 * @api
 *
 * @remarks Covers DIO028, DIO029, DIO057, DIO079, DIO119, DIO005, DIO006, DIO064, DIO070,DIO134
 * @remarks Implements DDIO01002
 */
FUNC (void, DIO_CODE) Dio_WriteChannel
(
    CONST(Dio_ChannelType, DIO_CONST) ChannelId,
    CONST(Dio_LevelType, DIO_CONST) Level
);

/**
 * @brief   Returns the level of all channels of specified port.
 * @details The @p Dio_ReadPort() function will return the level of all channels
 *          of specified port.
 *
 * @param[in] PortId        Specifies the required port id.
 * @return                  Level of all channels of specified port.
 *
 * @requirements    DIO031, DIO058, DIO104, DIO118, DIO005, DIO012, DIO013
 *                  DIO135.
 *
 * @api
 *
 * @remarks Covers DIO031, DIO058, DIO104, DIO118, DIO005, DIO012, DIO013, DIO135
 * @remarks Implements DDIO01003
 */
FUNC (Dio_PortLevelType, DIO_CODE) Dio_ReadPort
(
    CONST(Dio_PortType, DIO_CONST) PortId
);

/**
 * @brief   Service to set a value of the port.
 * @details The @p Dio_WritePort() function will set the specified value for the
 *          specified port.
 *
 * @param[in] PortId        Specifies the required port id.
 * @param[in] Level         Specifies the required level for the port pin.
 *
 * @requirements    DIO034, DIO035, DIO057, DIO105, DIO108, DIO119, DIO005,
 *                  DIO004, DIO005, DIO007, DIO064, DIO070, DIO136.
 *
 * @api
 *
 * @remarks Covers DIO034, DIO035, DIO057, DIO105, DIO108, DIO119, DIO005, DIO004, DIO005,
 * DIO007, DIO064, DIO070, DIO136
 * @remarks Implements DDIO01004
 */
FUNC (void, DIO_CODE) Dio_WritePort
(
    CONST(Dio_PortType, DIO_CONST) PortId,
    CONST(Dio_PortLevelType, DIO_CONST) Level
);

/**
 * @brief   This service reads a subset of the adjoining bits of a port.
 * @details The @p Dio_ReadChannelGroup() function will read a subset of the
 *          adjoining bits of a port (channel group).
 *          The @p Dio_WriteChannelGroup() function will do the masking of the
 *          channel and will do the shifting so that the values written by the
 *          function are aligned to the LSB.
 *
 * @param[in] ChannelGroupIdPtr     Pointer to the channel group.
 * @return                          The port level.
 *
 * @requirements    DIO037, DIO058, DIO092, DIO093, DIO056, DIO084, DIO118,
 *                  DIO005, DIO012,DIO014, DIO137.
 *
 * @api
 *
 * @remarks Covers DIO037, DIO058, DIO092, DIO093, DIO056, DIO084, DIO118, DIO005, DIO012,DIO014, DIO137
 * @remarks Implements DDIO01005
 */
FUNC (Dio_PortLevelType, DIO_CODE) Dio_ReadChannelGroup
(
  P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_APPL_CONST) ChannelGroupIdPtr
);

/**
 * @brief   Service to set a subset of the adjoining bits of a port to a
 *          specified level.
 * @details The @p Dio_WriteChannelGroup() function will set a subset of the
 *          adjoining bits of a port (channel group) to a specified level
 *          without changing the remaining channels of the port and channels
 *          which are configured as input. The @p Dio_WriteChannelGroup() function
 *          will do the masking of the channel and will do the shifting so that
 *          the values written by the function are aligned to the LSB.
 *
 * @param[in] ChannelGroupIdPtr     Pointer to the channel group.
 * @param[in] Level                 Desired level for the channel group.
 *
 * @requirements    DIO039, DIO040, DIO057, DIO090, DIO091, DIO056, DIO119,
 *                  DIO005, DIO008, DIO064, DIO070, DIO138.
 *
 * @api
 *
 * @remarks Covers DIO039, DIO040, DIO057, DIO090, DIO091, DIO056, DIO119, DIO005, DIO008,
 * DIO064, DIO070, DIO138
 * @remarks Implements DDIO01006
 */
FUNC (void, DIO_CODE) Dio_WriteChannelGroup
(
    P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_APPL_CONST) ChannelGroupIdPtr,
    CONST(Dio_PortLevelType, DIO_CONST) Level
);

#if ((DIO_MASKEDWRITEPORT_API == STD_ON) || defined (__DOXYGEN__))
/**
 * @brief   DIO Mask write port using mask.
 * @details Writes a DIO port with masked value.
 *
 * @param[in] PortId    Specifies the required port id.
 * @param[in] Level     Specifies the required level for the port pins.
 * @param[in] Mask      Specifies the Mask value of the port.
 *
 * @requirements     ENGR123885
 *
 * @remarks Covers PR-MCAL-3159
 * @remarks Implements DDIO06006
 */
FUNC (void, DIO_CODE) Dio_MaskedWritePort
(
    CONST(Dio_PortType, DIO_CONST) PortId,
    CONST(Dio_PortLevelType, DIO_CONST) Level,
    CONST(Dio_PortLevelType, DIO_CONST) Mask
);

#endif /* DIO_MASKEDWRITEPORT_API */

#define DIO_STOP_SEC_CODE
/**
 * @file Dio.h
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h: 
 *       See @ref DIO_H_REF_1
 */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* DIO_H */

/** @} */

/* End of File */
