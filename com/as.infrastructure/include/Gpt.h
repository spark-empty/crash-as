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


/*
 * Include structure:
 *
 *
 *                    Gpt.h
 *                      ^
 *                      |
 *       `---------- Gpt_xxx.c ---> Memmap.h
 *
 *
 */

/** @addtogroup Gpt GPT Driver
 *  @{ */

/** @file Gpt.h
 * API and type definitions for GPT Driver.
 */

#ifndef GPT_H_
#define GPT_H_

#include "Std_Types.h"
#include "Modules.h"

#define GPT_VENDOR_ID             VENDOR_ID_ARCCORE
#define GPT_MODULE_ID         		 1

#define GPT_SW_MAJOR_VERSION	1
#define GPT_SW_MINOR_VERSION   	0
#define GPT_SW_PATCH_VERSION	1

#define GPT_AR_MAJOR_VERSION     3
#define GPT_AR_MINOR_VERSION     1
#define GPT_AR_PATCH_VERSION     5

/** @name Error Codes */
//@{
#define GPT_E_UNINIT                        0x0a
#define GPT_E_BUSY 				                  0x0b
#define GPT_E_NOT_STARTED 			            0x0c
#define GPT_E_ALREADY_INITIALIZED           0x0d
#define GPT_E_PARAM_CHANNEL                 0x14
#define GPT_E_PARAM_VALUE 			            0x15
#define GPT_E_PARAM_MODE 			              0x1f
#define GPT_E_PARAM_CONFIG                  0x0e // TODO: Not in spec. Find real value
//@}

/** @name Service id's */
//@{
#define GPT_INIT_SERVICE_ID                 0x01
#define GPT_DEINIT_SERVICE_ID               0x02
#define GPT_GETTIMEELAPSED_SERVICE_ID       0x03
#define GPT_GETTIMEREMAINING_SERVICE_ID     0x04
#define GPT_STARTTIMER_SERVICE_ID           0x05
#define GPT_STOPTIMER_SERVICE_ID            0x06
#define GPT_ENABLENOTIFICATION_SERVICE_ID   0x07
#define GPT_DISABLENOTIFICATION_SERVICE_ID  0x08
#define GPT_SETMODE_SERVIVCE_ID             0x09
#define GPT_DISABLEWAKEUP_SERVICE_ID        0x0a
#define GPT_ENABLEWAKEUP_SERVICE_ID         0x0b
#define GPT_CBK_CHECKWAKEUP_SERVICE_ID      0x0c
//@}

/** Channel time value type */
typedef uint32_t Gpt_ValueType;

/** Channel behavior */
typedef enum
{
  GPT_MODE_ONESHOT=0,
  GPT_MODE_CONTINUOUS
} Gpt_ChannelMode;

typedef enum
{
  GPT_MODE_NORMAL=0,
  GPT_MODE_SLEEP
} Gpt_ModeType;

/** Channel id type */
typedef uint8_t Gpt_ChannelType;

/** parai: @req 4.2.2/SWS_Gpt_00389 */
typedef enum
{
	GPT_PREDEF_TIMER_1US_16BIT,
	GPT_PREDEF_TIMER_1US_24BIT,
	GPT_PREDEF_TIMER_1US_32BIT,
	GPT_PREDEF_TIMER_100US_32BIT
} Gpt_PredefTimerType;

/* Needs Gpt_ConfigType */
#include "Gpt_Cfg.h"		/* @req 4.0.3/GPT259 */

/* The config needs EcuM_WakeupSourceType from EcuM */

#if (GPT_VERSION_INFO_API == STD_ON)
#define Gpt_GetVersionInfo(_vi) STD_GET_VERSION_INFO(_vi,GPT)
#endif

void Gpt_Init( const Gpt_ConfigType * );

#if GPT_DEINIT_API == STD_ON
void Gpt_DeInit( void );
#endif

#if ( GPT_TIME_ELAPSED_API == STD_ON )
Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType channel);
#endif

#if ( GPT_TIME_REMAINING_API == STD_ON )
Gpt_ValueType Gpt_GetTimeRemaining( Gpt_ChannelType channel );
#endif

void Gpt_StartTimer(Gpt_ChannelType channel, Gpt_ValueType value);

void Gpt_StopTimer(Gpt_ChannelType channel);

#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
void Gpt_EnableNotification( Gpt_ChannelType channel);

void Gpt_DisableNotification( Gpt_ChannelType channel);
#endif

#if ( GPT_WAKEUP_FUNCTIONALITY_API == STD_ON )
void Gpt_SetMode( Gpt_ModeType mode );

void Gpt_DisableWakeup( Gpt_ChannelType channel );

void Gpt_EnableWakeup( Gpt_ChannelType channel );

void Gpt_Cbk_CheckWakeup( EcuM_WakeupSourceType wakeupSource );
#endif

/** GPT292 */
extern void Gpt_Notification_0( void );
extern void Gpt_Notification_1( void );
extern void Gpt_Notification_2( void );
extern void Gpt_Notification_3( void );

#endif /*GPT_H_*/
/** @} */
