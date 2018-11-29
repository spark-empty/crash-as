/*
 *  TOPPERS ATK2
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *      Automotive Kernel Version 2
 *
 *  Copyright (C) 2011-2015 by Center for Embedded Computing Systems
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2011-2015 by FUJI SOFT INCORPORATED, JAPAN
 *  Copyright (C) 2011-2013 by Spansion LLC, USA
 *  Copyright (C) 2011-2015 by NEC Communication Systems, Ltd., JAPAN
 *  Copyright (C) 2011-2015 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
 *  Copyright (C) 2011-2014 by Renesas Electronics Corporation, JAPAN
 *  Copyright (C) 2011-2015 by Sunny Giken Inc., JAPAN
 *  Copyright (C) 2011-2015 by TOSHIBA CORPORATION, JAPAN
 *  Copyright (C) 2011-2015 by Witz Corporation
 *  Copyright (C) 2014-2015 by AISIN COMCRUISE Co., Ltd., JAPAN
 *  Copyright (C) 2014-2015 by eSOL Co.,Ltd., JAPAN
 *  Copyright (C) 2014-2015 by SCSK Corporation, JAPAN
 *  Copyright (C) 2015 by SUZUKI MOTOR CORPORATION
 *  Copyright (C) 2016 by Fan Wang(parai@foxmail.com), China
 * 
 * The above copyright holders grant permission gratis to use,
 * duplicate, modify, or redistribute (hereafter called use) this
 * software (including the one made by modifying this software),
 * provided that the following four conditions (1) through (4) are
 * satisfied.
 * 
 * (1) When this software is used in the form of source code, the above
 *    copyright notice, this use conditions, and the disclaimer shown
 *    below must be retained in the source code without modification.
 *
 * (2) When this software is redistributed in the forms usable for the
 *    development of other software, such as in library form, the above
 *    copyright notice, this use conditions, and the disclaimer shown
 *    below must be shown without modification in the document provided
 *    with the redistributed software, such as the user manual.
 *
 * (3) When this software is redistributed in the forms unusable for the
 *    development of other software, such as the case when the software
 *    is embedded in a piece of equipment, either of the following two
 *    conditions must be satisfied:
 *
 *  (a) The above copyright notice, this use conditions, and the
 *      disclaimer shown below must be shown without modification in
 *      the document provided with the redistributed software, such as
 *      the user manual.
 *
 *  (b) How the software is to be redistributed must be reported to the
 *      TOPPERS Project according to the procedure described
 *      separately.
 *
 * (4) The above copyright holders and the TOPPERS Project are exempt
 *    from responsibility for any type of damage directly or indirectly
 *    caused from the use of this software and are indemnified by any
 *    users or end users of this software from any and all causes of
 *    action whatsoever.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS." THE ABOVE COPYRIGHT HOLDERS AND
 * THE TOPPERS PROJECT DISCLAIM ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, ITS APPLICABILITY TO A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS AND THE
 * TOPPERS PROJECT BE LIABLE FOR ANY TYPE OF DAMAGE DIRECTLY OR
 * INDIRECTLY CAUSED FROM THE USE OF THIS SOFTWARE.
 *
 *  $Id: svc_table.c 504 2015-12-24 01:22:56Z witz-itoyo $
 */

/*  This file is generated from svc.def by gensvc_atk. */

#include "kernel_int.h"
#include "portable.h"

void * const svc_table[TMAX_SVCID + 1] = {
	(void *) &StartOS,
	(void *) &ShutdownOS,
	(void *) &ActivateTask,
	(void *) &TerminateTask,
	(void *) &ChainTask,
	(void *) &Schedule,
	(void *) &GetTaskID,
	(void *) &GetTaskState,
	(void *) &EnableAllInterrupts,
	(void *) &DisableAllInterrupts,
	(void *) &ResumeAllInterrupts,
	(void *) &SuspendAllInterrupts,
	(void *) &ResumeOSInterrupts,
	(void *) &SuspendOSInterrupts,
	(void *) &GetISRID,
	(void *) &DisableInterruptSource,
	(void *) &EnableInterruptSource,
	(void *) &GetResource,
	(void *) &ReleaseResource,
	(void *) &SetEvent,
	(void *) &ClearEvent,
	(void *) &GetEvent,
	(void *) &WaitEvent,
	(void *) &GetAlarmBase,
	(void *) &GetAlarm,
	(void *) &SetRelAlarm,
	(void *) &SetAbsAlarm,
	(void *) &CancelAlarm,
	(void *) &IncrementCounter,
	(void *) &GetCounterValue,
	(void *) &GetElapsedValue,
	(void *) &CheckISRMemoryAccess,
	(void *) &CheckTaskMemoryAccess,
	(void *) &CheckTaskAccess,
	(void *) &CheckISRAccess,
	(void *) &CheckAlarmAccess,
	(void *) &CheckResourceAccess,
	(void *) &CheckCounterAccess,
	(void *) &CheckScheduleTableAccess,
	(void *) &CheckTaskOwnership,
	(void *) &CheckISROwnership,
	(void *) &CheckAlarmOwnership,
	(void *) &CheckCounterOwnership,
	(void *) &CheckScheduleTableOwnership,
	(void *) &GetApplicationID,
	(void *) &CallTrustedFunction,
	(void *) &GetApplicationState,
	(void *) &GetActiveApplicationMode,
	(void *) &StartScheduleTableRel,
	(void *) &StartScheduleTableAbs,
	(void *) &StopScheduleTable,
	(void *) &NextScheduleTable,
	(void *) &GetScheduleTableStatus,
	(void *) &GetFaultyContext,
	(void *) &ioc_send_generic,
	(void *) &ioc_write_generic,
	(void *) &ioc_receive_generic,
	(void *) &ioc_read_generic,
	(void *) &ioc_empty_queue_generic,
	(void *) &AllowAccess,
	(void *) &TerminateApplication,
	(void *) &exit_task,
	TARGET_SVC_TABLE
};
