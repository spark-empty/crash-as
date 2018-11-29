/*!
 * @file    Dio.c
 *
 * @version 2.0.0
 * @brief   AUTOSAR Dio - driver API implementation.
 * @details This file contains the DIO Autosar driver API implementation.
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
 *************************************************************************/

/*==================================================================================================
==================================================================================================*/

/**
 * @page misra_violations MISRA-C:2004 violations
 *
 * @section DIO_C_REF_1
 * Violates MISRA 2004 Required Rule 14.7, Return statement before end of function. 
 * The returned statement is in an error case when the input parameter is out of range.
 *
 * @section DIO_C_REF_2
 * Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor directives or comments before 
 * "#include". This violation is not fixed since the inclusion of MemMap.h is as per Autosar 
 * requirement MEMMAP003.
 *
 * @section DIO_C_REF_3
 * Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to prevent the 
 * contents of a header file being included twice. This is not a violation since all header 
 * files are protected against multiple inclusions.
 *
 * @section DIO_C_REF_4
 * Violates MISRA 2004 Required Rule 8.10, All declarations and definitions of objects or 
 * functions at file scope shall have internal linkage unless external linkage is required. 
 * This is not an issue as the function is an API function requested by Autosar.
 */

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************
 | include files
 |-----------------------------------------------------------------*/
/* Include Files */
#include "Dio.h"
#include "Dio_LLD.h"

/******************************************************************
 | defines and macros (scope: module-local)
 |-----------------------------------------------------------------*/
/*
 * @brief defines for versions checks of the header file
 * @remarks Covers DIO106
 */
#define DIO_VENDOR_ID_C             43
#define DIO_AR_MAJOR_VERSION_C      3
#define DIO_AR_MINOR_VERSION_C      0
#define DIO_AR_PATCH_VERSION_C      0
#define DIO_SW_MAJOR_VERSION_C      2
#define DIO_SW_MINOR_VERSION_C      0
#define DIO_SW_PATCH_VERSION_C      0

/*==================================================================================================
 FILE VERSION CHECKS
 ==================================================================================================*/

#if (DIO_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#ifdef CHECK_AUTOSAR_VERSION
/* Det.h version check start */
#if ((DIO_AR_MAJOR_VERSION_C != DET_AR_MAJOR_VERSION) || \
        (DIO_AR_MINOR_VERSION_C != DET_AR_MINOR_VERSION))
#error "AutoSar Version Numbers of Dio.c and Det.h are different"
#endif /*version check */
/*Det.h version check end */
#endif
#endif/* DIO_DEV_ERROR_DETECT */

#ifdef CHECK_AUTOSAR_VERSION
/* Dio_LLD.h version check start */
#if ((DIO_AR_MAJOR_VERSION_C != DIO_AR_MAJOR_VERSION_LLD) ||\
         (DIO_AR_MINOR_VERSION_C != DIO_AR_MINOR_VERSION_LLD) ||\
         (DIO_AR_PATCH_VERSION_C != DIO_AR_PATCH_VERSION_LLD))
#error "Autosar Version Numbers for Dio.c and Dio_LLD.h are different"
#endif
#endif
#if ((DIO_SW_MAJOR_VERSION_C != DIO_SW_MAJOR_VERSION_LLD) ||\
     (DIO_SW_MINOR_VERSION_C != DIO_SW_MINOR_VERSION_LLD) ||\
     (DIO_SW_PATCH_VERSION_C != DIO_SW_PATCH_VERSION_LLD))
#error "Software Version Numbers of Dio.c and Dio_LLD.h are different"
#endif
#if ((DIO_VENDOR_ID_C != DIO_VENDOR_ID_LLD))
#error "VENDOR ID for Dio.c and Dio_LLD.h is different"
#endif
/* Dio_LLD.h version check end */
#ifdef CHECK_AUTOSAR_VERSION
/* Dio.h version check start */
#if ((DIO_AR_MAJOR_VERSION_C != DIO_AR_MAJOR_VERSION) || \
         (DIO_AR_MINOR_VERSION_C != DIO_AR_MINOR_VERSION) || \
         (DIO_AR_PATCH_VERSION_C != DIO_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of Dio.c and Dio.h are different"
#endif
#endif
#if ((DIO_SW_MAJOR_VERSION_C != DIO_SW_MAJOR_VERSION) || \
     (DIO_SW_MINOR_VERSION_C != DIO_SW_MINOR_VERSION) || \
     (DIO_SW_PATCH_VERSION_C != DIO_SW_PATCH_VERSION))
#error "Software Version Numbers of Dio.c and Dio.h are different"
#endif
#if ((DIO_VENDOR_ID_C != DIO_VENDOR_ID))
#error "VENDOR ID for Dio.c and Dio.h is different"
#endif
/* Dio.h version check end */

/***************************** Dio Driver Macros ****************************/

/* put all DIO variables into defined section */
#define DIO_START_SEC_VAR_UNSPECIFIED
/**
 * @file Dio.c
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h: 
 *       See @ref DIO_C_REF_3
 */
#include "MemMap.h"

#define DIO_STOP_SEC_VAR_UNSPECIFIED
/**
 * @file Dio.c
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h: 
 *       See @ref DIO_C_REF_3
 */
#include "MemMap.h"

#define DIO_START_SEC_CODE
/**
 * @file Dio.c
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h: 
 *       See @ref DIO_C_REF_3
 */
#include "MemMap.h"

/*==================================================================================================
 LOCAL FUNCTION PROTOTYPES
 ==================================================================================================*/

#if ((DIO_DEV_ERROR_DETECT == STD_ON) || defined(__DOXYGEN__))
/**
 * @brief   DIO check pin
 * @details Verifies that that a channel is valid.
 *
 * @param[in] ChannelId        Channel id to be checked.
 *
 * @return Return a value 0 or 1 according to the received parameter.
 * @retval 1  If the pin is invalid.
 * @retval 0  If the pin is valid.
 *
 * @pre This function can be used only if DIO_DEV_ERROR_DETECT is set in the plugin.
 */
STATIC FUNC (uint8, DIO_CODE)invalid_pin( CONST(Dio_ChannelType, DIO_CONST) ChannelId);

/**
 * @brief   DIO check if a port is invalid
 * @details Checks if the port received as parameter is invalid.
 *
 * @param[in] PortId        Port id to be checked.
 *
 * @return Return a value 0 or 1 according to the received parameter.
 * @retval 0  If the port is valid.
 * @retval 1  If port is invalid.
 *
 * @pre This function can be used only if DIO_DEV_ERROR_DETECT is set in the plugin.
 */
STATIC FUNC (uint8, DIO_CODE)invalid_port( CONST(Dio_PortType, DIO_CONST) PortId);
#endif


/******************************************************************
| functions (scope: module-local)
|-----------------------------------------------------------------*/
#if (DIO_DEV_ERROR_DETECT == STD_ON)
/*
 * @brief   DIO check pin.
 * @details Verifies that that a channel is valid.
 *
 * @pre This function can be used only if DIO_DEV_ERROR_DETECT is set in the plugin.
 *
 * @param[in] ChannelId      Channel id to be checked.
 *
 * @return Return a value 0 or 1 according to the received parameter.
 * @retval 0  If the pin is valid.
 * @retval 1  If the pin is invalid.
 */
STATIC FUNC (uint8, DIO_CODE)invalid_pin
(
        CONST(Dio_ChannelType, DIO_CONST) ChannelId
)
{
    /* Check Channel ID if it is within valid limits for the device or not */
    VAR(Dio_ChannelType, DIO_VAR) i = (Dio_ChannelType)0;

    for (i = (Dio_ChannelType)0; i < DIO_PIN_INTERVALS; i+=(Dio_ChannelType)2)
    {
        if ((valid_pin_ranges[i] <= ChannelId) && (ChannelId <= valid_pin_ranges[i + (Dio_ChannelType)1]))
        {
            /**
             * @file Dio.c
             * @note Violates MISRA 2004 Required Rule 14.7, Return statement before end of 
             *       function: See @ref DIO_C_REF_1
             */
            return (uint8)0;
        }
    }

    return (uint8)1;
}

/*
 * @brief   DIO check if a port is invalid.
 * @details Checks if the port received as parameter is invalid.
 *
 * @param[in] PortId        Port id to be checked.
 *
 * @return Return a value 0 or 1 according to the received parameter.
 * @retval 0  If the port is valid.
 * @retval 1  If port is invalid.
 *
 * @pre  This function can be used only if DIO_DEV_ERROR_DETECT is set in the plugin.
 */
STATIC FUNC (uint8, DIO_CODE)invalid_port
(
        CONST(Dio_PortType, DIO_CONST) PortId
)
{
    VAR(Dio_PortType, DIO_VAR) i = (Dio_PortType)0;

    for (i = (Dio_PortType)0; i < DIO_PORT_INTERVALS; i+=(Dio_PortType)2)
    {
        if ((valid_port_ranges[i] <= PortId) && (PortId <= valid_port_ranges[i + (Dio_PortType)1]))
        {
            /**
             * @file Dio.c
             * @note Violates MISRA 2004 Required Rule 14.7, Return statement before end of 
             *       function: See @ref DIO_C_REF_1
             */
            return (uint8)0;
        }
    }

    return (uint8)1;
}
#endif



/******************************************************************
 | functions (scope: module-exported)
 |-----------------------------------------------------------------*/
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
/**
 * @file Dio.c
 * @note Violates MISRA 2004 Required Rule 8.10, External function could be made static: 
 *       See @ref DIO_C_REF_4
 */  
FUNC (void, DIO_CODE)Dio_GetVersionInfo
(
        P2VAR(Std_VersionInfoType, DIO_VAR_FAST, DIO_APPL_DATA) versioninfo
)
{
    /**
     * @remarks Covers DIO073
     */
#if(DIO_DEV_ERROR_DETECT == STD_ON)
    /* Check if versioninfo pointer is NULL */
    if (NULL_PTR == versioninfo)
    {
        Det_ReportError((uint16) DIO_MODULE_ID, DIO_INSTANCE_ID,
                DIO_GETVERSIONINFO_ID, DIO_E_PARAM_INVALID_POINTER);
    }
    else
#endif /* DIO_DEV_ERROR_DETECT */
    {
        (versioninfo)->vendorID = (uint16)DIO_VENDOR_ID;
        (versioninfo)->moduleID = (uint16)DIO_MODULE_ID;
        (versioninfo)->instanceID = (uint8)0;
        (versioninfo)->sw_major_version = (uint8)DIO_SW_MAJOR_VERSION;
        (versioninfo)->sw_minor_version = (uint8)DIO_SW_MINOR_VERSION;
        (versioninfo)->sw_patch_version = (uint8)DIO_SW_PATCH_VERSION;
    }
}
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
/**
 * @file Dio.c
 * @note Violates MISRA 2004 Required Rule 8.10, External function could be made static: 
 *       See @ref DIO_C_REF_4
 */ 
FUNC (Dio_LevelType, DIO_CODE) Dio_ReadChannel
(
        CONST(Dio_ChannelType, DIO_CONST) ChannelId
)
{
    VAR(Dio_LevelType, DIO_VAR) value = (Dio_LevelType) STD_LOW;
    /* @remarks Covers DIO066 */
    /* @remarks Implements DDIO05001 */
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    if (invalid_pin(ChannelId))
    {
        /* @remarks Covers DIO067, DIO074 */
        /* @remarks Implements DDIO05002 */
        Det_ReportError((uint16) DIO_MODULE_ID, DIO_INSTANCE_ID,
                DIO_READCHANNEL_ID,DIO_E_PARAM_INVALID_CHANNEL_ID);
    }
    else
#endif /* DIO_DEV_ERROR_DETECT */
    {
        value = DioLLD_ReadChannel(ChannelId);
    }
    return (value);
}

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
/**
 * @file Dio.c
 * @note Violates MISRA 2004 Required Rule 8.10, External function could be made static: 
 *       See @ref DIO_C_REF_4
 */ 
FUNC (void, DIO_CODE) Dio_WriteChannel
(
        CONST(Dio_ChannelType, DIO_CONST) ChannelId,
        CONST(Dio_LevelType, DIO_CONST) Level
)
{
    /* @remarks Covers DIO066 */
    /* @remarks Implements DDIO05001 */
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    if (invalid_pin(ChannelId))
    {
        /* @remarks Covers DIO067, DIO074 */
        /* @remarks Implements DDIO05002 */
        Det_ReportError((uint16) DIO_MODULE_ID, DIO_INSTANCE_ID,
                DIO_WRITECHANNEL_ID,DIO_E_PARAM_INVALID_CHANNEL_ID);
    }
    else
#endif /* DIO_DEV_ERROR_DETECT */
    {
        /* @remarks Covers DIO067, DIO074 */
        /* @remarks Implements DDIO05002 */
        DioLLD_WriteChannel(ChannelId, Level);
    }
}

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
/**
 * @file Dio.c
 * @note Violates MISRA 2004 Required Rule 8.10, External function could be made static: 
 *       See @ref DIO_C_REF_4
 */  
FUNC (Dio_PortLevelType, DIO_CODE) Dio_ReadPort
(
        CONST(Dio_PortType, DIO_CONST) PortId
)
{
    VAR(Dio_PortLevelType, DIO_VAR) value = (Dio_PortLevelType) STD_LOW;
    /* @remarks Covers DIO066 */
    /* @remarks Implements DDIO05001 */
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    if (invalid_port(PortId))
    {
        /* @remarks Covers DIO067, DIO075 */
        /* @remarks Implements DDIO05002 */
        Det_ReportError((uint16) DIO_MODULE_ID, DIO_INSTANCE_ID,
                DIO_READPORT_ID,DIO_E_PARAM_INVALID_PORT_ID);
    }
    else
#endif
    {
        value = DioLLD_ReadPort(PortId);
    }
    return (value);
}

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
/**
 * @file Dio.c
 * @note Violates MISRA 2004 Required Rule 8.10, External function could be made static: 
 *       See @ref DIO_C_REF_4
 */ 
FUNC (void, DIO_CODE) Dio_WritePort
(
        CONST(Dio_PortType, DIO_CONST) PortId,
        CONST(Dio_PortLevelType, DIO_CONST) Level
)
{
    /* @remarks Covers DIO066 */
    /* @remarks Implements DDIO05001 */
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    if (invalid_port(PortId))
    {
        /* @remarks Covers DIO067 */
        /* @remarks Implements DDIO05002 */
        Det_ReportError((uint16) DIO_MODULE_ID, DIO_INSTANCE_ID,
                DIO_WRITEPORT_ID, DIO_E_PARAM_INVALID_PORT_ID);
    }
    else
#endif
    {
        DioLLD_WritePort(PortId, Level);
    }
}

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
/**
 * @file Dio.c
 * @note Violates MISRA 2004 Required Rule 8.10, External function could be made static: 
 *       See @ref DIO_C_REF_4
 */   
FUNC (Dio_PortLevelType, DIO_CODE) Dio_ReadChannelGroup
(
        P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_APPL_CONST) ChannelGroupIdPtr
)
{
    VAR(Dio_PortLevelType, DIO_VAR) value = (Dio_PortLevelType) STD_LOW;

    /* @remarks Covers DIO066 */
    /* @remarks Implements DDIO05001 */
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    /* Check Channel Group Ptr ID */
    if (NULL_PTR == ChannelGroupIdPtr)
    {
        /* @remarks Covers DIO067, DIO114 */
        /* @remarks Implements DDIO05002 */
        Det_ReportError((uint16) DIO_MODULE_ID, DIO_INSTANCE_ID,
                DIO_READCHANNELGROUP_ID, DIO_E_PARAM_INVALID_GROUP_ID);
    }
    /* Check Port ID */
    else
    {
        if (invalid_port((ChannelGroupIdPtr)->port))
        {
            /* @remarks Covers DIO067 */
            /* @remarks Implements DDIO05001 */
            Det_ReportError((uint16) DIO_MODULE_ID, DIO_INSTANCE_ID,
                    DIO_READCHANNELGROUP_ID, DIO_E_PARAM_INVALID_PORT_ID);
        }
        else
#endif
        {
            value = DioLLD_ReadChannelGroup(ChannelGroupIdPtr);
        }
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    }
#endif
    return (value);
}

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
/**
 * @file Dio.c
 * @note Violates MISRA 2004 Required Rule 8.10, External function could be made static: 
 *       See @ref DIO_C_REF_4
 */ 
FUNC (void, DIO_CODE) Dio_WriteChannelGroup
(
        P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_APPL_CONST) ChannelGroupIdPtr,
        CONST(Dio_PortLevelType,DIO_CONST) Level
)
{
    /* @remarks Covers DIO066 */
    /* @remarks Implements DDIO05001 */
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    /* Check Channel Group Ptr ID */
    if (NULL_PTR == ChannelGroupIdPtr)
    {
        /* @remarks Covers DIO067, DIO114 */
        /* @remarks Implements DDIO05002 */
        Det_ReportError((uint16) DIO_MODULE_ID, DIO_INSTANCE_ID,
                DIO_WRITECHANNELGROUP_ID, DIO_E_PARAM_INVALID_GROUP_ID);
    }
    /* Check Port ID */
    else
    {
        if (invalid_port((ChannelGroupIdPtr)->port))
        {
            /* @remarks Covers DIO067 */
            /* @remarks Implements DDIO05001 */
            Det_ReportError((uint16) DIO_MODULE_ID, DIO_INSTANCE_ID,
                    DIO_WRITECHANNELGROUP_ID, DIO_E_PARAM_INVALID_PORT_ID);
        }
        else
#endif
        {
            DioLLD_WriteChannelGroup(ChannelGroupIdPtr, Level);
        }
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    }
#endif
}

#if (DIO_MASKEDWRITEPORT_API == STD_ON)
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
/**
 * @file Dio.c
 * @note Violates MISRA 2004 Required Rule 8.10, External function could be made static: 
 *       See @ref DIO_C_REF_4
 */
FUNC (void, DIO_CODE) Dio_MaskedWritePort
(
        CONST(Dio_PortType, DIO_CONST) PortId,
        CONST(Dio_PortLevelType, DIO_CONST) Level,
        CONST(Dio_PortLevelType, DIO_CONST) Mask
)
{
    /* @remarks Covers DIO066 */
    /* @remarks Implements DDIO05001 */
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    if (invalid_port(PortId))
    {
        /* @remarks Covers DIO065 */
        /* @remarks Implements DDIO05002 */
        Det_ReportError((uint16) DIO_MODULE_ID, DIO_INSTANCE_ID,
                DIO_MASKEDWRITEPORT_ID, DIO_E_PARAM_INVALID_PORT_ID);
    }
    else
#endif
    {
        DioLLD_MaskedWritePort(PortId, Level, Mask);
    }
}
#endif /* DIO_MASKEDWRITEPORT_API */

#define DIO_STOP_SEC_CODE
/**
 * @file Dio.c
 * @note Violates MISRA 2004 Advisory Rule 19.1, Declaration before '#include': 
 *       See @ref DIO_C_REF_2
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h: 
 *       See @ref DIO_C_REF_3
 */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif
/** @} */

/* End of File */
