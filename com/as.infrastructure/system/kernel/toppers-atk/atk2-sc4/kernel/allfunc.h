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
 *  $Id: allfunc.h 504 2015-12-24 01:22:56Z witz-itoyo $
 */

/*
 *		Definition of the order to compile all the function
 */

#ifndef TOPPERS_ALLFUNC_H
#define TOPPERS_ALLFUNC_H

/* alarm.c */
#define TOPPERS_alarm_initialize
#define TOPPERS_GetAlarmBase
#define TOPPERS_GetAlarm
#define TOPPERS_SetRelAlarm
#define TOPPERS_SetAbsAlarm
#define TOPPERS_CancelAlarm
#define TOPPERS_alarm_expire
#define TOPPERS_force_term_osap_alarm

/* counter_manage.c */
#define TOPPERS_IncrementCounter
#define TOPPERS_GetCounterValue
#define TOPPERS_GetElapsedValue
#define TOPPERS_notify_hardware_counter
#define TOPPERS_incr_counter_action
#define TOPPERS_incr_counter_process

/* counter.c */
#define TOPPERS_insert_cnt_expr_que
#define TOPPERS_delete_cnt_expr_que
#define TOPPERS_counter_initialize
#define TOPPERS_counter_terminate
#define TOPPERS_get_reltick
#define TOPPERS_get_abstick
#define TOPPERS_expire_process
#define TOPPERS_force_term_osap_counter

/* event.c */
#define TOPPERS_SetEvent
#define TOPPERS_ClearEvent
#define TOPPERS_GetEvent
#define TOPPERS_WaitEvent
#define TOPPERS_set_event_action

/* interrupt.c */
#define TOPPERS_interrupt_initialize
#define TOPPERS_release_interrupts
#define TOPPERS_exit_isr2

/* interrupt_manage.c */
#define TOPPERS_DisableAllInterrupts
#define TOPPERS_EnableAllInterrupts
#define TOPPERS_SuspendAllInterrupts
#define TOPPERS_ResumeAllInterrupts
#define TOPPERS_SuspendOSInterrupts
#define TOPPERS_ResumeOSInterrupts
#define TOPPERS_GetISRID
#define TOPPERS_DisableInterruptSource
#define TOPPERS_EnableInterruptSource

/* osctl.c */
#define TOPPERS_internal_call_errorhook
#define TOPPERS_call_posttaskhook
#define TOPPERS_call_pretaskhook
#define TOPPERS_call_protectionhk_main
#define TOPPERS_init_stack_magic_region
#define TOPPERS_internal_shutdownos
#define TOPPERS_internal_call_shtdwnhk

/* osctl_manage.c */
#define TOPPERS_StartOS
#define TOPPERS_GetActiveApplicationMode
#define TOPPERS_ShutdownOS
#define TOPPERS_GetFaultyContext

/* resource.c */
#define TOPPERS_resource_initialize
#define TOPPERS_GetResource
#define TOPPERS_ReleaseResource

/* scheduletable.c */
#define TOPPERS_schtbl_initialize
#define TOPPERS_StartScheduleTableRel
#define TOPPERS_StartScheduleTableAbs
#define TOPPERS_StopScheduleTable
#define TOPPERS_NextScheduleTable
#define TOPPERS_GetScheduleTableStatus
#define TOPPERS_schtbl_expire
#define TOPPERS_schtbl_expiry_process
#define TOPPERS_schtbl_head
#define TOPPERS_schtbl_exppoint_process
#define TOPPERS_schtbl_tail
#define TOPPERS_force_term_osap_schtbl

/* task.c */
#define TOPPERS_task_initialize
#define TOPPERS_search_schedtsk
#define TOPPERS_make_runnable
#define TOPPERS_make_non_runnable
#define TOPPERS_make_active
#define TOPPERS_preempt
#define TOPPERS_suspend
#define TOPPERS_release_taskresources
#define TOPPERS_cancel_taskcounters
#define TOPPERS_exit_task
#define TOPPERS_remove_task_from_queue
#define TOPPERS_force_terminate_task
#define TOPPERS_force_term_osap_task
#define TOPPERS_move_schedtsk

/* task_manage.c */
#define TOPPERS_ActivateTask
#define TOPPERS_TerminateTask
#define TOPPERS_ChainTask
#define TOPPERS_Schedule
#define TOPPERS_GetTaskID
#define TOPPERS_GetTaskState
#define TOPPERS_activate_task_action

/* timingprotection.c */
#define TOPPERS_tp_initialize
#define TOPPERS_tp_terminate
#define TOPPERS_tp_start_timer
#define TOPPERS_tp_stop_timer
#define TOPPERS_tp_stop_task_monitor
#define TOPPERS_tp_get_current_time
#define TOPPERS_tp_check_arrival_time
#define TOPPERS_tp_fault_handler
#define TOPPERS_tp_timer_handler

/* memory.c */
#define TOPPERS_search_meminib
#define TOPPERS_check_address_stack
#define TOPPERS_check_osap_memory
#define TOPPERS_check_isr_memory
#define TOPPERS_CheckISRMemoryAccess
#define TOPPERS_check_task_memory
#define TOPPERS_CheckTaskMemoryAccess
#define TOPPERS_probe_memory_access
#define TOPPERS_probe_memory_read
#define TOPPERS_probe_memory_write
#define TOPPERS_probe_memory_read_write
#define TOPPERS_initialize_sections

/* osap.c */
#define TOPPERS_osap_initialize
#define TOPPERS_GetApplicationID
#define TOPPERS_GetApplicationState
#define TOPPERS_CallTrustedFunction
#define TOPPERS_CheckTaskAccess
#define TOPPERS_CheckISRAccess
#define TOPPERS_CheckAlarmAccess
#define TOPPERS_CheckResourceAccess
#define TOPPERS_CheckCounterAccess
#define TOPPERS_CheckScheduleTableAccess
#define TOPPERS_CheckTaskOwnership
#define TOPPERS_CheckISROwnership
#define TOPPERS_CheckAlarmOwnership
#define TOPPERS_CheckCounterOwnership
#define TOPPERS_CheckScheduleTableOwnership
#define TOPPERS_force_term_osap
#define TOPPERS_force_term_osap_main
#define TOPPERS_TerminateApplication
#define TOPPERS_AllowAccess

#endif /* TOPPERS_ALLFUNC_H */
