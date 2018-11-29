/* -------------------------------- Arctic Core ------------------------------
 * Arctic Core - the open source AUTOSAR platform http://arccore.com
 *
 * Copyright (C) 2009  ArcCore AB <contact@arccore.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * -------------------------------- Arctic Core ------------------------------*/

/**
 * @addtogroup EcuM ECU State Manager
 * @{
 *
 * @file EcuM_Types.h
 * Typedefs needed by EcuM module. Note that types that are generated together with
 * Ecum Service Ports should be guarded by _DEFINED_TYPEDEF_FOR_<Type>_ to avoid re-definition.
 */
#ifndef ECUM_TYPES_H_
#define ECUM_TYPES_H_

#include "Std_Types.h"
#include <Os.h>

#if defined(RTE_TYPE_H) && defined(__GNUC__)
//#warning RTE_TYPE included before EcuM_Types.h
#endif

#ifdef CFG_ECUM_USE_SERVICE_COMPONENT
#include "Rte_Type.h"
#endif


#if !defined(_DEFINED_TYPEDEF_FOR_EcuM_StateType_)
/** Possible states */
typedef enum {
	ECUM_STATE_APP_RUN = 0x32,          //!< ECUM_STATE_APP_RUN
	ECUM_STATE_SHUTDOWN = 0x40,         //!< ECUM_STATE_SHUTDOWN
	ECUM_STATE_WAKEUP = 0x20,           //!< ECUM_STATE_WAKEUP
	ECUM_SUBSTATE_MASK = 0x0F,          //!< ECUM_SUBSTATE_MASK
	ECUM_STATE_WAKEUP_WAKESLEEP = 0x25, //!< ECUM_STATE_WAKEUP_WAKESLEEP
	ECUM_STATE_WAKEUP_ONE = 0x21,       //!< ECUM_STATE_WAKEUP_ONE
	ECUM_STATE_OFF = 0x80,              //!< ECUM_STATE_OFF
	ECUM_STATE_STARTUP = 0x10,          //!< ECUM_STATE_STARTUP
	ECUM_STATE_PREP_SHUTDOWN = 0x44,    //!< ECUM_STATE_PREP_SHUTDOWN
	ECUM_STATE_RUN = 0x30,              //!< ECUM_STATE_RUN
	ECUM_STATE_STARTUP_TWO = 0x12,      //!< ECUM_STATE_STARTUP_TWO
	ECUM_STATE_WAKEUP_TTII = 0x26,      //!< ECUM_STATE_WAKEUP_TTII
	ECUM_STATE_WAKEUP_VALIDATION = 0x22,//!< ECUM_STATE_WAKEUP_VALIDATION
	ECUM_STATE_GO_SLEEP = 0x49,         //!< ECUM_STATE_GO_SLEEP
	ECUM_STATE_STARTUP_ONE = 0x11,      //!< ECUM_STATE_STARTUP_ONE
	ECUM_STATE_WAKEUP_TWO = 0x24,       //!< ECUM_STATE_WAKEUP_TWO
	ECUM_STATE_SLEEP = 0x50,            //!< ECUM_STATE_SLEEP
	ECUM_STATE_WAKEUP_REACTION = 0x23,  //!< ECUM_STATE_WAKEUP_REACTION
	ECUM_STATE_APP_POST_RUN = 0x33,     //!< ECUM_STATE_APP_POST_RUN
	ECUM_STATE_GO_OFF_TWO = 0x4e,       //!< ECUM_STATE_GO_OFF_TWO
	ECUM_STATE_RESET = 0x90,            //!< ECUM_STATE_RESET
	ECUM_STATE_GO_OFF_ONE = 0x4d        //!< ECUM_STATE_GO_OFF_ONE
} EcuM_StateType;

#define _DEFINED_TYPEDEF_FOR_EcuM_StateType_

#endif


#if !defined(_DEFINED_TYPEDEF_FOR_EcuM_UserType_)
typedef uint8 EcuM_UserType;

#define _DEFINED_TYPEDEF_FOR_EcuM_UserType_
#endif

#if 0
enum {
	/** Internal reset of �C (bit 2).
	 *  The internal reset typically only resets the �C
	 *  core but not peripherals or memory
	 *  controllers. The exact behavior is hardware
	 *  specific.
	 *  This source may also indicate an unhandled
	 *  exception. */
	ECUM_WKSOURCE_INTERNAL_RESET = 0x04,

	/** Reset by external watchdog (bit 4), if
	 *  detection supported by hardware */
	ECUM_WKSOURCE_EXTERNAL_WDG = 0x10,

	/** Reset by internal watchdog (bit 3) */
	ECUM_WKSOURCE_INTERNAL_WDG = 0x08,

	/** Power cycle (bit 0) */
	ECUM_WKSOURCE_POWER = 0x01,

	/** ~0 to the power of 29 */
	ECUM_WKSOURCE_ALL_SOURCES = 0x3FFFFFFF,

	/** Hardware reset (bit 1).
	 *  If hardware cannot distinguish between a
	 *  power cycle and a reset reason, then this
	 *  shall be the default wakeup source */
	ECUM_WKSOURCE_RESET = 0x02
};


typedef uint32 EcuM_WakeupSourceType;

#endif

typedef enum
{
	ECUM_WKSTATUS_NONE = 0,        /**< No pending wakeup event was detected */
	ECUM_WKSTATUS_PENDING = 1,     /**< The wakeup event was detected but not yet validated */
	ECUM_WKSTATUS_VALIDATED = 2,   /**< The wakeup event is valid */
	ECUM_WKSTATUS_EXPIRED = 3     /**< The wakeup event has not been validated and has expired therefore */
} EcuM_WakeupStatusType;

/* parai: @req4.2.2:SWS_EcuM_04120 */
typedef enum
{	/* Result of the Run Request Protocol sent to BswM */
	ECUM_RUNSTATUS_UNKNOWN = 0,
	ECUM_RUNSTATUS_REQUESTED,
	ECUM_RUNSTATUS_RELEASED

}EcuM_RunStatusType;

#if !defined(_DEFINED_TYPEDEF_FOR_EcuM_BootTargetType_)
typedef enum
{
	ECUM_BOOT_TARGET_APP = 0,          /**< The Ecu will boot into the application */
	ECUM_BOOT_TARGET_BOOTLOADER = 1   /**< The Ecu will boot into the bootloader */
} EcuM_BootTargetType;
#define _DEFINED_TYPEDEF_FOR_EcuM_BootTargetType_
#endif


#if defined(USE_WDGM)
#include "WdgM.h"
#endif

#include "Mcu.h"

#if defined(USE_WDGM)
typedef struct EcuM_WdgM
{
	WdgM_SupervisedEntityIdType EcuMSupervisedEntity;
	WdgM_ModeType EcuMWdgMWakeupMode;
	WdgM_ModeType EcuMWdgMStartupMode;
	WdgM_ModeType EcuMWdgMRunMode;
	WdgM_ModeType EcuMWdgMPostRunMode;
	WdgM_ModeType EcuMWdgMShutdownMode;
} EcuM_WdgMType;
#endif

typedef struct EcuM_WakeupSourceConfig {
	EcuM_WakeupSourceType 	EcuMWakeupSourceId;
	uint32 					EcuMValidationTimeout;
	Mcu_ResetType 			EcuMResetReason;
	boolean 				EcuMWakeupSourcePolling;
	uint8 					EcuMComMChannel;
} EcuM_WakeupSourceConfigType;

typedef struct EcuM_SleepMode
{
   uint8 					EcuMSleepModeId;
   EcuM_WakeupSourceType 	EcuMWakeupSourceMask;
   Mcu_ModeType  			EcuMSleepModeMcuMode;
#if defined(USE_WDGM)
   WdgM_ModeType 			EcuMSleepModeWdgMMode;
#endif
 } EcuM_SleepModeType;

 /* Defines for illegal modes/channels */
#define ECUM_SLEEP_MODE_WDGM_MODE_ILL		0xff
#define ECUM_COMM_CHANNEL_ILL				0xff
#define ECUM_VALIDATION_TIMEOUT_ILL   0xfffffffful

#endif /* ECUM_TYPES_H_ */
/** @} */
