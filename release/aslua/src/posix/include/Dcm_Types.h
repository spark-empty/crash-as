/* -------------------------------- Arctic Core -> AS ------------------------------
 * Arctic Core - the open source AUTOSAR platform http://arccore.com
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2009  ArcCore AB <contact@arccore.com>
 * Copyright (C) 2015  AS <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * -------------------------------- Arctic Core -> AS ------------------------------*/

#ifndef DCM_TYPES_H_
#define DCM_TYPES_H_
#include "Std_Types.h"

/*
 * Dcm_SecLevelType
 */
typedef uint8 Dcm_SecLevelType;
#define DCM_SEC_LEV_LOCKED		((Dcm_SecLevelType)0x00)
#define DCM_SEC_LEV_L1			((Dcm_SecLevelType)0x01)
#define DCM_SEC_LEV_ALL			((Dcm_SecLevelType)0xFF)

/*
 * Dcm_SesCtrlType
 */
typedef uint8 Dcm_EcuResetType;
#define DCM_HARD_RESET							((Dcm_EcuResetType)0x01)
#define DCM_KEY_OFF_ON_RESET					((Dcm_EcuResetType)0x02)
#define DCM_SOFT_RESET							((Dcm_EcuResetType)0x03)

/*
 * Dcm_SesCtrlType
 */
typedef uint8 Dcm_SesCtrlType;
#define DCM_DEFAULT_SESSION						((Dcm_SesCtrlType)0x01)
#define DCM_PROGRAMMING_SESSION					((Dcm_SesCtrlType)0x02)
#define DCM_EXTENDED_DIAGNOSTIC_SESSION			((Dcm_SesCtrlType)0x03)
#define DCM_SAFTEY_SYSTEM_DIAGNOSTIC_SESSION	((Dcm_SesCtrlType)0x04)
#define DCM_OBD_SESSION							((Dcm_SesCtrlType)0x05)//only used for OBD diagnostic
#define DCM_ALL_SESSION_LEVEL					((Dcm_SesCtrlType)0xFF)

typedef uint8 Dcm_ConfirmationStatusType;
#define DCM_RES_POS_OK							((Dcm_ConfirmationStatusType)0x00)
#define DCM_RES_POS_NOT_OK						((Dcm_ConfirmationStatusType)0x01)
#define DCM_RES_NEG_OK							((Dcm_ConfirmationStatusType)0x02)
#define DECM_RES_NEG_NOT_OK						((Dcm_ConfirmationStatusType)0x03)

/*
 * Dcm_ProtocolType
 */
typedef uint8 Dcm_ProtocolType;
#define DCM_OBD_ON_CAN					((Dcm_ProtocolType)0x00)
#define DCM_UDS_ON_CAN					((Dcm_ProtocolType)0x01)
#define DCM_UDS_ON_FLEAXRAY				((Dcm_ProtocolType)0x02)
#define DCM_ROE_ON_CAN					((Dcm_ProtocolType)0x03)
#define DCM_ROE_ON_FLEXRAY				((Dcm_ProtocolType)0x04)
#define DCM_PERIODIC_TRANS_ON_CAN		((Dcm_ProtocolType)0x05)
#define DCM_PERIODIC_TRANS_ON_FLEXRAY	((Dcm_ProtocolType)0x06)
#define DCM_UDS_ON_DOIP					((Dcm_ProtocolType)0x07)
/*
 * Dcm_ReturnReadMemoryType
 */
typedef uint8 Dcm_ReturnReadMemoryType;
#define DCM_READ_OK						((Dcm_ReturnReadMemoryType)0x00)
#define DCM_READ_PENDING				((Dcm_ReturnReadMemoryType)0x01)
#define	DCM_READ_FAILED					((Dcm_ReturnReadMemoryType)0x02)

/*
 * Dcm_ReturnWriteMemoryType
 */
typedef uint8 Dcm_ReturnWriteMemoryType;
#define DCM_WRITE_OK					((Dcm_ReturnWriteMemoryType)0x00)
#define DCM_WRITE_PENDING				((Dcm_ReturnWriteMemoryType)0x01)
#define DCM_WRITE_FAILED				((Dcm_ReturnWriteMemoryType)0x02)

/*
 * Dcm_ReturnEraseMemoryType
 */
typedef uint8 Dcm_ReturnEraseMemoryType;
#define DCM_ERASE_OK						((Dcm_ReturnEraseMemoryType)0x00)
#define DCM_ERASE_PENDING					((Dcm_ReturnEraseMemoryType)0x01)
#define	DCM_ERASE_FAILED					((Dcm_ReturnEraseMemoryType)0x02)
/*
 * Dcm_OpStatusType
 */
typedef uint8 Dcm_OpStatusType;
#define DCM_INITIAL						((Dcm_OpStatusType)0x00)
#define DCM_PENDING						((Dcm_OpStatusType)0X01)
#define DCM_CANCEL						((Dcm_OpStatusType)0x02)
#define DCM_FORCE_RCRRP_OK				((Dcm_OpStatusType)0X03)

/*
 * Dcm_NegativeResponseCodeType
 * parai: split words by adding "_"
 */
#if !defined(_DEFINED_TYPEDEF_FOR_NegativeResponseCodeType_)
typedef uint8 Dcm_NegativeResponseCodeType;
#define DCM_E_GENERAL_REJECT								((Dcm_NegativeResponseCodeType)0x10)
#define DCM_E_BUSY_REPEAT_REQUEST							((Dcm_NegativeResponseCodeType)0x21)
#define DCM_E_CONDITIONS_NOT_CORRECT						((Dcm_NegativeResponseCodeType)0x22)
#define DCM_E_REQUEST_SEQUENCE_ERROR						((Dcm_NegativeResponseCodeType)0x24)
#define DCM_E_REQUEST_OUT_OF_RANGE							((Dcm_NegativeResponseCodeType)0x31)
#define DCM_E_SECUTITY_ACCESS_DENIED						((Dcm_NegativeResponseCodeType)0x33)
#define DCM_E_INVALID_KEY									((Dcm_NegativeResponseCodeType)0x35)
#define DCM_E_GENERAL_PROGRAMMING_FAILURE					((Dcm_NegativeResponseCodeType)0x72)
#define DCM_E_WRONG_BLOCK_SEQUENCE_COUNTER                  ((Dcm_NegativeResponseCodeType)0x73)
#define DCM_E_SUB_FUNCTION_NOT_SUPPORTED_IN_ACTIVE_SESSION	((Dcm_NegativeResponseCodeType)0x7E)
#define DCM_E_RPM_TOO_HIGH									((Dcm_NegativeResponseCodeType)0x81)
#define DCM_E_RPM_TO_LOW									((Dcm_NegativeResponseCodeType)0x82)
#define DCM_E_ENGINE_IS_RUNNING								((Dcm_NegativeResponseCodeType)0x83)
#define DCM_E_ENGINE_IS_NOT_RUNNING							((Dcm_NegativeResponseCodeType)0x84)
#define DCM_E_ENGINE_RUN_TIME_TOO_LOW						((Dcm_NegativeResponseCodeType)0x85)
#define DCM_E_TEMPERATURE_TOO_HIGH							((Dcm_NegativeResponseCodeType)0x86)
#define DCM_E_TEMPERATURE_TOO_LOW							((Dcm_NegativeResponseCodeType)0x87)
#define DCM_E_VEHICLE_SPEED_TOO_HIGH						((Dcm_NegativeResponseCodeType)0x88)
#define DCM_E_VEHICLE_SPEED_TOO_LOW							((Dcm_NegativeResponseCodeType)0x89)
#define DCM_E_THROTTLE_PEDAL_TOO_HIGH						((Dcm_NegativeResponseCodeType)0x8A)
#define DCM_E_THROTTLE_PEDAL_TOO_LOW						((Dcm_NegativeResponseCodeType)0x8B)
#define DCM_E_TRANSMISSION_RANGE_NOT_IN_NEUTRAL				((Dcm_NegativeResponseCodeType)0x8C)
#define DCM_E_TRANSMISSION_RANGE_NOT_IN_GEAR				((Dcm_NegativeResponseCodeType)0x8D)
#define DCM_E_BRAKE_SWITCH_NOT_CLOSED						((Dcm_NegativeResponseCodeType)0x8F)
#define DCM_E_SHIFTER_LEVER_NOT_IN_PARK						((Dcm_NegativeResponseCodeType)0x90)
#define DCM_E_TORQUE_CONVERTER_CLUTCH_LOCKED				((Dcm_NegativeResponseCodeType)0x91)
#define DCM_E_VOLTAGE_TOO_HIGH								((Dcm_NegativeResponseCodeType)0x92)
#define DCM_E_VOLTAGE_TOO_LOW								((Dcm_NegativeResponseCodeType)0x93)

#define DCM_E_POSITIVE_RESPONSE								((Dcm_NegativeResponseCodeType)0x00)
#define DCM_E_SERVICE_NOT_SUPPORTED							((Dcm_NegativeResponseCodeType)0x11)
#define DCM_E_SUB_FUNCTION_NOT_SUPPORTED					((Dcm_NegativeResponseCodeType)0x12)
#define DCM_E_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT	((Dcm_NegativeResponseCodeType)0x13)
#define DCM_E_RESPONSE_PENDING								((Dcm_NegativeResponseCodeType)0x78)
#define DCM_E_SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION		((Dcm_NegativeResponseCodeType)0x7F)
#endif


typedef uint8 Dcm_StatusType;
#define DCM_E_OK  										(Dcm_StatusType)0x00u
#define DCM_E_COMPARE_KEY_FAILED 						(Dcm_StatusType)0x01u
#define DCM_E_TI_PREPARE_LIMITS 						(Dcm_StatusType)0x02u
#define DCM_E_TI_PREPARE_INCONSTENT 					(Dcm_StatusType)0x03u
#define DCM_E_SESSION_NOT_ALLOWED 						(Dcm_StatusType)0x04u
#define DCM_E_PROTOCOL_NOT_ALLOWED 						(Dcm_StatusType)0x05u
#define DCM_E_ROE_NOT_ACCEPTED 							(Dcm_StatusType)0x06u
#define DCM_E_PERIODICID_NOT_ACCEPTED 					(Dcm_StatusType)0x07u
#define DCM_E_REQUEST_NOT_ACCEPTED 						(Dcm_StatusType)0x08u
#define DCM_E_REQUEST_ENV_NOK 							(Dcm_StatusType)0x09u

typedef uint8 Dcm_PeriodicTransmitModeType;
#define DCM_PERIODIC_TRANSMIT_DEFAULT_MODE      (Dcm_PeriodicTransmitModeType)0x00u
#define DCM_PERIODIC_TRANSMIT_SLOWRATE_MODE 				(Dcm_PeriodicTransmitModeType)0x01u
#define DCM_PERIODIC_TRANSMIT_MEDIUM_MODE 					(Dcm_PeriodicTransmitModeType)0x02u
#define DCM_PERIODIC_TRANSMIT_FAST_MODE 					(Dcm_PeriodicTransmitModeType)0x03u
#define DCM_PERIODIC_TRANSMIT_STOPSENDING_MODE				(Dcm_PeriodicTransmitModeType)0x04u



typedef uint8 Dcm_DDDSubfunctionType;
#define DCM_DDD_SUB_FUNCTION_DEFINEBYDID 				(Dcm_DDDSubfunctionType)0x01u
#define DCM_DDD_SUB_FUNCTION_DEFINEBYADDRESS 			(Dcm_DDDSubfunctionType)0x02u
#define DCM_DDD_SUB_FUNCTION_CLEAR 						(Dcm_DDDSubfunctionType)0x03u


typedef uint8 Dcm_PeriodicDidStartType;
#define	DCM_PERIODIC_TRANISMIT_STOP 					(Dcm_PeriodicDidStartType)0
#define	DCM_PERIODIC_TRANISMIT_START 					(Dcm_PeriodicDidStartType)0x01u

typedef uint8 Dcm_DDDSourceStateType;
#define DCM_DDD_SOURCE_BY_DID 							(Dcm_DDDSourceStateType)0x00u
#define DCM_DDD_SOURCE_BY_ADDRESS 						(Dcm_DDDSourceStateType)0x01u

typedef uint8 Dcm_IOControlParameterType;
#define DCM_RETURN_CONTROL_TO_ECU 					(Dcm_IOControlParameterType)0x0
#define DCM_RESET_TO_DEFAULT 							(Dcm_IOControlParameterType)0x01
#define DCM_FREEZE_CURRENT_STATE						(Dcm_IOControlParameterType)0x02
#define DCM_SHORT_TERM_ADJUSTMENT						(Dcm_IOControlParameterType)0x03

#endif /*DCM_TYPES_H_*/
