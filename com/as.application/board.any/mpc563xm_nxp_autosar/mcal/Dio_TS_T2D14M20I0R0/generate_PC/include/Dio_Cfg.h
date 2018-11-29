[!CODE!][!//
/*!
 * @file    Dio_Cfg.h
 *
 * @version 2.0.0
 * @brief   AUTOSAR Dio - DIO driver config.
 * @details This file contains the precompile configuration for the DIO driver.
 *
 * @addtogroup  Dio
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

/* PROG044 */
#ifndef DIO_CFG_H
#define DIO_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * @brief defines for versions checks of the header file
 * @remarks Covers DIO106
 */
/* The integration of incompatible files shall be avoided. */
#define DIO_VENDOR_ID_CFG_H         43
#define DIO_AR_MAJOR_VERSION_CFG_H  3
#define DIO_AR_MINOR_VERSION_CFG_H  0
#define DIO_AR_PATCH_VERSION_CFG_H  0
#define DIO_SW_MAJOR_VERSION_CFG_H  2
#define DIO_SW_MINOR_VERSION_CFG_H  0
#define DIO_SW_PATCH_VERSION_CFG_H  0

/* General Container Definitions */
/*
 * @brief Enable/Disable Development Error Detection
 */
#define DIO_DEV_ERROR_DETECT    ([!IF "DioGeneral/DioDevErrorDetect"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
/*
 * @brief Use/remove Port_GetVersionInfo function from the compiled driver
 */
#define DIO_VERSION_INFO_API    ([!IF "DioGeneral/DioVersionInfoApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
/*
 * @brief Read as zero the undefined ports
 */
#define DIO_READZERO_UNDEFINEDPORTS    STD_OFF
/*
 * @brief emove Dio_MaskedWritePort function from the compiled driver
 */
#define DIO_MASKEDWRITEPORT_API    STD_OFF

[!IF "DioGeneral/DioDevErrorDetect"!]
/*
 * @brief Number of pin intervals - used for DET checking
 */
#define DIO_PIN_INTERVALS (uint8)[!"num:inttohex(count(ecu:list('Dio.AvailablePins')))"!]
[!ELSE!]
[!ENDIF!][!//
[!IF "DioGeneral/DioDevErrorDetect"!]
/*
 * @brief Number of port intervals - used for DIO_READZERO_UNDEFINEDPORTS
 */
#define DIO_PORT_INTERVALS (uint8)[!"num:inttohex(count(ecu:list('Dio.AvailablePorts')))"!]
[!ELSE!][!//
[!ENDIF!][!//

[!//check if the proper number of intervals is present in the resource files
[!IF "DioGeneral/DioDevErrorDetect"!][!//
[!IF "count(ecu:list('Dio.AvailablePins')) mod 2 = 1"!][!ERROR "one of the pins intervals is not complete. check resource file"!][!ENDIF!][!//
[!IF "count(ecu:list('Dio.AvailablePorts')) mod 2 = 1"!][!ERROR "one of the ports intervals is not complete. check resource file"!][!ENDIF!][!//
[!ENDIF!][!//

[!IF "IMPLEMENTATION_CONFIG_VARIANT='VariantPreCompile'"!][!//
/*
 * @brief Dio driver Pre-Compile configuration switch
 */

#define DIO_PRECOMPILE_SUPPORT[!//
[!ELSE!][!//
[!ENDIF!][!//


/*
 * @brief Flag to disable reversed port functionality because not supported in Monaco
 */
#define DIO_REVERSEPORTBITS STD_OFF

/*
 * @brief   Implementation specific.
 * details Dio_PortType can be uint8,uint16,uint32, it gives numeric ID of a DIO port
 *
 * @api
 *
 * @remarks Covers DIO018
 * @remarks Implements DDIO01010
 */
typedef uint8 Dio_PortType;



/*
 * @brief   Implementation specific.
 * @details Dio_ChannelType can be uint8,uint16,uint32,it gives numeric ID
 *          of a DIO channel.
 *
 * @api
 *
 * @remarks Covers DIO015
 * @remarks Implements DDIO01008
 */
typedef uint8 Dio_ChannelType;



/*
 * @brief   Implementation specific.
 * @detayls Dio_PortLevelType can be uint8,uint16,uint32.it inherits the
 *          size of largest port
 *
 * @api
 *
 * @remarks Covers DIO024
 * @remarks Implements DDIO01009
 */
typedef uint16 Dio_PortLevelType;



/*
 * @brief   Implementation specific.
 * details  Dio_ChannelGroupType is a structure with elements:<br>
 *          - port,
 *          - offset,
 *          - mask.
 *          .
 *
 * @api
 *
 * @remarks Covers DIO021, DIO056
 * @remarks Implements DDIO03001
 */
typedef struct
{
    VAR(Dio_PortType, DIO_VAR) port; /**< @brief PORT ID */
    VAR(Dio_PortLevelType, DIO_VAR) offset; /**< @brief offset */
    VAR(Dio_PortLevelType, DIO_VAR) mask; /**< @brief mask */
} Dio_ChannelGroupType;

/*
 * @brief valid_pin_ranges is an array containing valid pin intervals, intervals are closed
 */
[!IF "DioGeneral/DioDevErrorDetect"!]extern CONST(Dio_ChannelType, DIO_CONST)valid_pin_ranges[DIO_PIN_INTERVALS];[!ENDIF!]

/*
 * @brief valid_port_ranges is an array containing valid port intervals, intervals are closed
 */
[!IF "DioGeneral/DioDevErrorDetect"!]extern CONST(Dio_PortType, DIO_CONST)valid_port_ranges[DIO_PORT_INTERVALS];[!ENDIF!]

[!NOCODE!]
[!//first check that macro names for Channel Groups are unique...this can't be done in the plugin
[!LOOP "DioPort/*/DioChannelGroup/*"!]
[!VAR "crt_name"="node:name(.)"!]
[!VAR "occurences"="0"!]
[!LOOP "../../../*/DioChannelGroup/*"!]
[!IF "$crt_name=node:name(.)"!][!VAR "occurences"="$occurences+1"!][!ENDIF!]
[!ENDLOOP!]
[!IF "$occurences > 1"!][!ERROR "ChannelGroup name duplicated. Channel group name must be unique even across Ports"!][!ENDIF!]
[!ENDLOOP!]

[!//first check that macro names for Channels are unique...this can't be done in the plugin
[!LOOP "DioPort/*/DioChannel/*"!]
[!VAR "crt_name"="node:name(.)"!]
[!VAR "occurences"="0"!]
[!LOOP "../../../*/DioChannel/*"!]
[!IF "$crt_name=node:name(.)"!][!VAR "occurences"="$occurences+1"!][!ENDIF!]
[!ENDLOOP!]
[!IF "$occurences > 1"!][!ERROR "Channel name duplicated. Channel name must be unique even across Ports"!][!ENDIF!]
[!ENDLOOP!]
[!ENDNOCODE!]
[!LOOP "DioPort/*"!][!//
[!VAR "PortId" = "DioPortId"!][!//
/* ---------- [!"node:name(.)"!] ---------- */

/*
 * @brief Symbolic name for the port [!"node:name(.)"!]
 */
#define [!"node:name(.)"!] (Dio_PortType)[!"num:inttohex($PortId,2)"!]U
[!LOOP "DioChannel/*"!][!//
[!VAR "PortChannelId" = "DioChannelId"!][!//
[!VAR "ChannelId" = "16*$PortId + $PortChannelId"!][!//

/*
 * @brief Symbolic name for the channel [!"node:name(.)"!]
 */
#define [!"node:name(.)"!]  (Dio_ChannelType)[!"num:inttohex($ChannelId,2)"!]U[!//

[!ENDLOOP!]
[!LOOP "DioChannelGroup/*"!][!//
/*
 * @brief external declaration for the structure containing the details of channel group [!"DioChannelGroupIdentification"!]
 */
extern CONST(Dio_ChannelGroupType, DIO_CONST) [!"DioChannelGroupIdentification"!];
/*
 * @brief Symbolic name for the channel group [!"node:name(.)"!]
 */
#define [!"node:name(.)"!]  &[!"DioChannelGroupIdentification"!]

[!ENDLOOP!][!//

[!ENDLOOP!]

#ifdef __cplusplus
}
#endif

#endif  /* DIO_CFG_H */


/** @} */

/* End of File */
[!ENDCODE!][!//
