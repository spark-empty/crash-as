#ifndef COM_AS_INFRASTRUCTURE_INCLUDE_TM_H_
#define COM_AS_INFRASTRUCTURE_INCLUDE_TM_H_
/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2016  AS <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"

/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
typedef uint16 Tm_PredefTimer1us16bitType;
typedef uint32 Tm_PredefTimer1us24bitType;
typedef uint32 Tm_PredefTimer1us32bitType;
typedef uint32 Tm_PredefTimer100us32bitType;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
Std_ReturnType Tm_ResetTimer1us16bit(Tm_PredefTimer1us16bitType* TimerPtr);
Std_ReturnType Tm_GetTimeSpan1us16bit(const Tm_PredefTimer1us16bitType* TimerPtr,uint16* TimeSpanPtr);
void Tm_ShiftTimer1us16bit(Tm_PredefTimer1us16bitType* TimerPtr,uint16 TimeValue);
void Tm_SyncTimer1us16bit(Tm_PredefTimer1us16bitType* TimerDstPtr,const Tm_PredefTimer1us16bitType* TimerSrcPtr);
Std_ReturnType Tm_BusyWait1us16bit(uint8 WaitingTimeMin);

Std_ReturnType Tm_ResetTimer1us24bit(Tm_PredefTimer1us24bitType* TimerPtr);
Std_ReturnType Tm_GetTimeSpan1us24bit(const Tm_PredefTimer1us24bitType* TimerPtr,uint32* TimeSpanPtr);
void Tm_ShiftTimer1us24bit(Tm_PredefTimer1us24bitType* TimerPtr,uint32 TimeValue);
void Tm_SyncTimer1us24bit(Tm_PredefTimer1us24bitType* TimerDstPtr,const Tm_PredefTimer1us24bitType* TimerSrcPtr);
Std_ReturnType Tm_BusyWait1us24bit(uint8 WaitingTimeMin);

Std_ReturnType Tm_ResetTimer1us32bit(Tm_PredefTimer1us32bitType* TimerPtr);
Std_ReturnType Tm_GetTimeSpan1us32bit(const Tm_PredefTimer1us32bitType* TimerPtr,uint32* TimeSpanPtr);
void Tm_ShiftTimer1us32bit(Tm_PredefTimer1us32bitType* TimerPtr,uint32 TimeValue);
void Tm_SyncTimer1us32bit(Tm_PredefTimer1us32bitType* TimerDstPtr,const Tm_PredefTimer1us32bitType* TimerSrcPtr);
Std_ReturnType Tm_BusyWait1us32bit(uint8 WaitingTimeMin);

Std_ReturnType Tm_ResetTimer100us32bit(Tm_PredefTimer100us32bitType* TimerPtr);
Std_ReturnType Tm_GetTimeSpan100us32bit(const Tm_PredefTimer100us32bitType* TimerPtr,uint32* TimeSpanPtr);
void Tm_ShiftTimer100us32bit(Tm_PredefTimer100us32bitType* TimerPtr,uint32 TimeValue);
void Tm_SyncTimer100us32bit(Tm_PredefTimer100us32bitType* TimerDstPtr,const Tm_PredefTimer100us32bitType* TimerSrcPtr);

#endif /* COM_AS_INFRASTRUCTURE_INCLUDE_TM_H_ */
