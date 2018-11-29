
__header = '''/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2017  AS <parai@foxmail.com>
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
'''

from .util import *
from .GCF import *

__all__ = ['gen_trampoline']

__tpl_customer_types__ = '''
#ifndef TPL_APP_CUSTOM_TYPES_H
#define TPL_APP_CUSTOM_TYPES_H

#include "tpl_compiler.h"
#include "tpl_os_std_types.h"

/**
 * tpl_heap_key is the datatype used to store the key of a heap entry.
 */
typedef uint8 tpl_heap_key;

/**
 * tpl_rank_count is the datatype used to store the rank of an activation
 * It is the lower part of a tpl_heap_key
 */
typedef uint8 tpl_rank_count;

/**
 * tpl_proc_id is used for task and isrs identifiers.
 *
 * @warning This data type must be signed
 * because -1 is used for INVALID_TASK and INVALID_ISR
 */
typedef sint16 tpl_proc_id;

/**
 * tpl_appmode_mask is used for AUTOSTART objects.
 *
 * Each bit in the mask corresponds to an application mode. The size of the mask
 * is computed according to the number of application modes.
 */
typedef uint8 tpl_appmode_mask;

/**
 * tpl_priority represents a task's or a resource's priority.
 *
 * @warning This type must be signed.
 */
typedef sint16 tpl_priority;

/**
 * tpl_activate_counter is used to count
 * how many time a task has been activated while
 * it was not suspended.
 */
typedef uint8 tpl_activate_counter;

/**
 * tpl_event_mask is used for event.
 * An event is a bit vector. According to the maximum number of events
 * defined in the application, it can be uint8 (8 events), uint16 (16 events) or
 * uint32 (32 events).
 */
typedef uint32 tpl_event_mask;

/**
 * tpl_alarm_type is used for alarm identifiers.
 */
typedef uint8 tpl_alarm_id;

/**
 * tpl_resource_id is used for resource identifiers.
 *
 * @warning RES_SCHEDULER is set to the higher resource id + 1
 */
typedef uint8 tpl_resource_id;

/**
 * @internal
 *
 * Type used to store the id of an alarm or a schedule table
 * This is used only for tracing
 */
typedef uint8 tpl_timeobj_id;

/**
 * @internal
 *
 * @todo: document this
 */
typedef uint8 tpl_counter_id;

/**
 * @internal
 *
 * @todo: document this
 */
typedef uint8 tpl_schedtable_id;

/**
 * @internal
 *
 * Type used to store the id of an OS Application
 * Its size is computed according to the number of OS Applications
 */
typedef uint8 tpl_app_id;

/**
 * @internal
 *
 * Generic type used in OS Application API
 * Its size is computed by doing the max of all object kind
 */
typedef uint8 tpl_generic_id;

typedef uint32 tpl_ioc_id;

#endif /* TPL_APP_CUSTOM_TYPES_H */

/* End of file tpl_app_custom_types.h */

'''

def Trampoline_TaskList(os_list):
    ret_list = []
    task_list = ScanFrom(os_list,'Task')
    for task in task_list:
        length = len(ret_list)
        if(length == 0):
            ret_list.append(task)
        else:
            prio = int(GAGet(task,'Priority'))
            flag = False
            for i,it in enumerate(ret_list):
                iprio = int(GAGet(it,'Priority'))
                if(prio > iprio):
                    ret_list.insert(i, task)
                    flag = True
                    break
            if(flag == False):
                ret_list.append(task)
    return ret_list

def genForTrampolineMisc_H(gendir,os_list):
    fp = open('%s/tpl_app_define.h'%(gendir),'w')
    fp.write(__header)
    fp.write('#ifndef TPL_APP_DEFINE_H\n#define TPL_APP_DEFINE_H\n\n')
    fp.write('/* ============================ [ INCLUDES  ] ====================================================== */\n')
    fp.write('#include "tpl_config_def.h"\n\n')
    fp.write('/* ============================ [ MACROS    ] ====================================================== */\n')
    fp.write('''#define TARGET_ARCH                      "posix"
#define TARGET_CHIP                      "anything"
#define TARGET_BOARD                     "anything"
#define NUMBER_OF_CORES                  1
#define WITH_OS_EXTENDED                 YES
#define WITH_ORTI                        NO
#define WITH_PAINT_STACK                 YES
#define WITH_PAINT_REGISTERS             YES
#define WITH_STARTUP_HOOK                YES
#define WITH_SHUTDOWN_HOOK               YES
#define WITH_ERROR_HOOK                  YES
#define WITH_PRE_TASK_HOOK               YES
#define WITH_POST_TASK_HOOK              YES
#define WITH_PANIC_HOOK                  YES
#define WITH_USEGETSERVICEID             NO
#define WITH_USEPARAMETERACCESS          NO
#define WITH_USERESSCHEDULER             YES
#ifndef WITH_SYSTEM_CALL
#define WITH_SYSTEM_CALL                 NO
#endif
#define WITH_MEMORY_PROTECTION           NO
#define WITH_MEMMAP                      NO
#define WITH_COMPILER_SETTINGS           YES
#define WITH_AUTOSAR                     NO
#define WITH_PROTECTION_HOOK             NO
#define WITH_STACK_MONITORING            NO
#define WITH_AUTOSAR_TIMING_PROTECTION   NO
#define AUTOSAR_SC                       0
#define WITH_OSAPPLICATION               NO
#define WITH_OSAPPLICATION_STARTUP_HOOK  NO
#define WITH_OSAPPLICATION_SHUTDOWN_HOOK NO
#define WITH_TRACE                       NO
#define WITH_IT_TABLE                    NO
#define WITH_COM                         YES
#define WITH_IOC                         YES
#define WITH_MODULES_INIT                NO
#define WITH_INIT_BOARD                  NO
#define WITH_ISR2_PRIORITY_MASKING       NO
#define WITH_SEMAPHORE                   NO

/* Defines related to the key part of a ready list entry.
 * The key part has in the most significant bits the priority of the job and
 * in the least significant bits the rank of the job. So:
 * - PRIORITY_SHIFT is the number of bit the key has to be shifted to the
 *   right) to get the priority only aligned to the right;
 * - PRIORITY_MASK is the mask to get the priority only (not aligned to the
 *   right with the rank set to 0;
 * - RANK_MASK is the mask to get only the rank.
 */
#define PRIORITY_SHIFT                   1
#define PRIORITY_MASK                    0xFE
#define RANK_MASK                        1\n\n''');
    task_list = Trampoline_TaskList(os_list)
    for id,task in enumerate(task_list):
        fp.write('#define TASK_ID_%-32s %-3s /* priority = %s */\n'%(GAGet(task,'Name'),id,GAGet(task,'Priority')))
    fp.write('#define IDLE_TASK_ID%-28s %s\n'%(' ',id))
    fp.write('#define TASK_NUM%-32s %s\n\n'%(' ',id+1))

    for id,task in enumerate(task_list):
        for mask,ev in enumerate(GLGet(task,'EventList')):
            if(GAGet(ev,'Mask')=='auto'):
                mask = '(1<<%s)'%(mask)
            else:
                mask = GAGet(ev,'Mask')
            fp.write('#define EVENT_MASK_%-40s %s\n'%('%s_%s'%(GAGet(task,'Name'),GAGet(ev,'Name')),mask))

    res_list = ScanFrom(os_list, 'Resource')
    for id,res in enumerate(res_list):
        fp.write('#define RES_ID_%-32s %s\n'%(GAGet(res,'Name'),id+1))
    fp.write('#define RES_NUMBER %s\n\n'%(len(res_list)+1))
    
    alarm_list = ScanFrom(os_list,'Alarm')
    for id,alarm in enumerate(alarm_list):
        fp.write('#define ALARM_ID_%-32s %s\n'%(GAGet(alarm,'Name'),id))
    fp.write('#define ALARM_NUM%-32s %s\n\n'%(' ',id+1))

    fp.write('#define TASK_COUNT TASK_NUM-1\n')
    fp.write('#define EXTENDED_TASK_COUNT TASK_NUM-1\n')
    fp.write('#define ALARM_COUNT ALARM_NUM\n')
    fp.write('#define RESOURCE_COUNT RES_NUMBER\n')

    fp.write('#define COUNTER_COUNT 1\n')
    fp.write('#define SCHEDTABLE_COUNT 0\n')
    fp.write('#define IOC_COUNT 0\n')
    fp.write('#define ISR_COUNT 0\n')
    fp.write('#define APP_COUNT 1\n')
    fp.write('#define NUMBER_OF_OBJECTS 0\n')
    fp.write('#define RES_SCHEDULER_PRIORITY 3\n')

    fp.write('\n#define TRACE_FORMAT() tpl_trace_format_txt();\n')
    fp.write('#define TRACE_FILE "trampoline_os_trace.txt"\n')

    isr_list = ScanFrom(os_list,'ISR')
    isr_num = len(isr_list)
    for isr in isr_list:
        if((int(GAGet(isr,'Vector'),10)+1)>isr_num):
            isr_num = int(GAGet(isr,'Vector'),10)+1
    for id,isr in enumerate(isr_list):
        fp.write('#define ISR_ID_%-32s %s\n'%(GAGet(isr,'Name'),id))
    fp.write('#define ISR_MAX%-32s %s\n\n'%(' ',len(isr_list)))
    for id,isr in enumerate(isr_list):
        fp.write('#define ISR_VECTOR_%-32s %s\n'%(GAGet(isr,'Name'),GAGet(isr,'Vector')))
    fp.write('#define ISR_NUM%-35s  %s\n\n'%(' ',isr_num))
    fp.write('\n\n')
    fp.write('/* ============================ [ TYPES     ] ====================================================== */\n')
    fp.write('/* ============================ [ DECLARES  ] ====================================================== */\n')
    fp.write('/* ============================ [ DATAS     ] ====================================================== */\n')
    fp.write('/* ============================ [ LOCALS    ] ====================================================== */\n')
    fp.write('/* ============================ [ FUNCTIONS ] ====================================================== */\n')
    fp.write('\n\n')
    fp.write('#endif /* TPL_APP_DEFINE_H */\n\n')
    fp.close()

    fp = open('%s/tpl_app_custom_types.h'%(gendir),'w')
    fp.write(__tpl_customer_types__)
    fp.close()

    fp = open('%s/tpl_app_config.h'%(gendir),'w')
    fp.write(__header)
    fp.write('#ifndef TPL_APP_CONFIG_H\n#define TPL_APP_CONFIG_H\n\n')
    fp.write('/* ============================ [ INCLUDES  ] ====================================================== */\n')
    fp.write('#include "tpl_app_define.h"\n\n')
    fp.write('#include "tpl_compiler.h"\n\n')
    fp.write('#include "tpl_os_internal_types.h"\n\n')
    fp.write('/* ============================ [ MACROS    ] ====================================================== */\n')
    fp.write('/* ============================ [ TYPES     ] ====================================================== */\n')
    fp.write('/* ============================ [ DECLARES  ] ====================================================== */\n')
    fp.write('''extern CONSTP2CONST(char, AUTOMATIC, OS_APPL_DATA) proc_name_table[TASK_COUNT + ISR_COUNT + 1];
extern CONST(tpl_tick, OS_CONST) OSTICKSPERBASE;
extern CONST(tpl_tick, OS_CONST) OSMAXALLOWEDVALUE;
extern CONST(tpl_tick, OS_CONST) OSMINCYCLE;\n\n''')
    

    fp.write('/* ============================ [ DATAS     ] ====================================================== */\n')
    fp.write('/* ============================ [ LOCALS    ] ====================================================== */\n')
    fp.write('/* ============================ [ FUNCTIONS ] ====================================================== */\n')
    for id,task in enumerate(task_list):
        fp.write('extern void %s_function(void);\n'%(GAGet(task,'Name')))
    for alarm in alarm_list:
        fp.write('extern void %s_callback(void);\n'%(GAGet(alarm,'Name')))
    fp.write('#endif /* TPL_APP_CONFIG_H */\n')
    fp.close()

def genForTrampoline_H(gendir,os_list):
    fp = open('%s/Os_Cfg.h'%(gendir),'w')
    fp.write(__header)
    fp.write('#ifndef OS_CFG_H\n#define OS_CFG_H\n\n')
    fp.write('/* ============================ [ INCLUDES  ] ====================================================== */\n')
    fp.write('#include "tpl_os.h"\n')
    fp.write('/* ============================ [ MACROS    ] ====================================================== */\n')
    fp.write('#define __TRAMPOLINE_OS__\n\n')
    fp.write('#define ALARM ALARMCALLBACK\n\n')
    fp.write('#define OSDEFAULTAPPMODE 0\n\n')
    fp.write('/* ============================ [ TYPES     ] ====================================================== */\n')
    fp.write('/* ============================ [ DECLARES  ] ====================================================== */\n')
    fp.write('DeclareResource(RES_SCHEDULER);\n\n')
    fp.write('/* ============================ [ DATAS     ] ====================================================== */\n')
    fp.write('/* ============================ [ LOCALS    ] ====================================================== */\n')
    fp.write('/* ============================ [ FUNCTIONS ] ====================================================== */\n')
    fp.write('\n\n')
    fp.write('#endif /* OS_CFG_H */\n\n')
    fp.close()
def genForTrampoline_C(gendir,os_list):
    fp = open('%s/Os_Cfg.c'%(gendir),'w')
    fp.write(__header)
    fp.write('/* ============================ [ INCLUDES  ] ====================================================== */\n')
    fp.write('#include "Os.h"\n')
    fp.write('''#include "tpl_app_config.h"
#include "tpl_os_internal_types.h"
#include "tpl_machine.h"
#include "tpl_os_interrupt.h"
#include "tpl_os_interrupt_kernel.h"
#include "tpl_os_alarm_kernel.h"
#include "tpl_os_alarm.h"
#include "tpl_os_resource_kernel.h"
#include "tpl_os_resource.h"
#include "tpl_os_event_kernel.h"
#include "tpl_os_event.h"
#include "tpl_os_action.h"
#include "tpl_os_kernel.h"
#include "tpl_os_definitions.h"\n\n''')
    fp.write('/* ============================ [ MACROS    ] ====================================================== */\n')
    fp.write('/* ============================ [ TYPES     ] ====================================================== */\n')
    fp.write('/* ============================ [ DECLARES  ] ====================================================== */\n')
    isr_list = ScanFrom(os_list,'ISR')
    for isr in isr_list:
        fp.write('extern ISR(%s);\n'%(GAGet(isr,'Name')))
    fp.write('/* ============================ [ DATAS     ] ====================================================== */\n')
    fp.write('/* ============================ [ LOCALS    ] ====================================================== */\n')
    fp.write('/* ============================ [ FUNCTIONS ] ====================================================== */\n')
    task_list = Trampoline_TaskList(os_list)
    fp.write('CONST(tpl_appmode_mask, OS_CONST) tpl_task_app_mode[TASK_NUM] = {\n')
    for task in task_list:
        mask = 0
        if(GAGet(task,'Autostart').upper() == 'TRUE'):
            mask = '(1<<OSDEFAULTAPPMODE)'
        fp.write('\t%s, /* %s */\n'%(mask,GAGet(task,'Name')))
    fp.write('};\n\n')
    
    alarm_list = ScanFrom(os_list,'Alarm')
    fp.write('CONST(tpl_appmode_mask, OS_CONST) tpl_alarm_app_mode[ALARM_COUNT] = {\n')
    for alarm in alarm_list:
        mask = 0
        if(GAGet(alarm,'Autostart').upper() == 'TRUE'):
            mask = '(1<<OSDEFAULTAPPMODE)'
        fp.write('\t%s, /* %s */\n'%(mask,GAGet(alarm,'Name')))
    fp.write('};\n\n')
    # resource generation not supported now, as ascore doesn't use any
    fp.write('''
/**
 * The scheduler resource descriptor.
 * One scheduler resource is defined per core.
 *
 * @see #RES_SCHEDULER
 */

VAR(tpl_resource, OS_VAR) res_sched_rez_desc = {
  .ceiling_priority = RES_SCHEDULER_PRIORITY,
  .owner_prev_priority= 0,
  .owner = INVALID_PROC_ID,
#if WITH_OSAPPLICATION == YES
  .app_id = INVALID_OSAPPLICATION_ID,
#endif
  .next_res = NULL
};
CONSTP2VAR(tpl_resource, AUTOMATIC, OS_APPL_DATA)
tpl_resource_table[RESOURCE_COUNT] = {
  &res_sched_rez_desc
};\n\n''')

    fp.write('''CONST(tpl_tick, OS_CONST) OSTICKSPERBASE = 1;
CONST(tpl_tick, OS_CONST) OSMAXALLOWEDVALUE = ((tpl_tick)-1)/2;
CONST(tpl_tick, OS_CONST) OSMINCYCLE = 1;

VAR(tpl_counter, OS_VAR) SystemCounter_counter_desc = {
  .ticks_per_base =  1,
  .max_allowed_value = ((tpl_tick)-1)/2,
  .min_cycle = 1,
  .current_tick = 0,
  .current_date = 0,
#if WITH_OSAPPLICATION == YES
    .app_id = INVALID_OSAPPLICATION_ID;  
#endif
    .first_to = NULL_PTR,
    .next_to = NULL_PTR
};

TickType OsTickCounter = 0;

TickType GetOsTick(void)
{
    return OsTickCounter;
}

FUNC(tpl_bool, OS_CODE) tpl_call_counter_tick()
{
  OsTickCounter ++;
  if(0u == OsTickCounter)
  {
    OsTickCounter = 0;
  }

  tpl_counter_tick(&SystemCounter_counter_desc);

  if (tpl_kern.need_schedule)
  {
    tpl_schedule_from_running();
    LOCAL_SWITCH_CONTEXT(0)
  }

  return TRUE;
}\n\n''')

    for task in task_list:
        fp.write('tpl_stack_word %s_stack_zone[(%s*4)/sizeof(tpl_stack_word)];\n'%(GAGet(task,'Name'),GAGet(task,'StackSize')))
        fp.write('struct TPL_CONTEXT %s_context;\n'%(GAGet(task,'Name')))
        fp.write('''CONST(tpl_proc_static, OS_CONST) %s_task_stat_desc = {
  .context = &%s_context,
  .stack = { .stack_zone = %s_stack_zone, .stack_size = sizeof(%s_stack_zone) },
  .entry = %s_function,
  .internal_resource = NULL,
  .id = TASK_ID_%s,
#if WITH_OSAPPLICATION == YES
  .app_id = INVALID_OSAPPLICATION_ID,
#endif
  .base_priority = TASK_NUM - TASK_ID_%s - 1,
  .max_activate_count = 1,
  .type = TASK_EXTENDED,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES
  .executionbudget = 0,
  .timeframe = 0, 
  .timing_protection = NULL
#endif
};

VAR(tpl_proc, OS_VAR) %s_task_desc = {
  .resources = NULL,
#if WITH_OSAPPLICATION == YES
  .trusted_counter =  0,    
#endif /* WITH_OSAPPLICATION */
  .activate_count = 0,
  .priority = 0,
  .state =  SUSPENDED
};\n\n'''%(GAGet(task,'Name'),GAGet(task,'Name'),GAGet(task,'Name'),GAGet(task,'Name'),GAGet(task,'Name'),GAGet(task,'Name'),GAGet(task,'Name'),GAGet(task,'Name')))
    fp.write('CONSTP2CONST(tpl_proc_static, AUTOMATIC, OS_APPL_DATA) tpl_stat_proc_table[TASK_COUNT+ISR_COUNT+NUMBER_OF_CORES] = {\n')
    for task in task_list:
        fp.write('\t&%s_task_stat_desc,\n'%(GAGet(task,'Name')))
    fp.write('};\n')

    fp.write('CONSTP2VAR(tpl_proc, AUTOMATIC, OS_APPL_DATA) tpl_dyn_proc_table[TASK_COUNT+ISR_COUNT+NUMBER_OF_CORES] = {\n')
    for task in task_list:
        fp.write('\t&%s_task_desc,\n'%(GAGet(task,'Name')))
    fp.write('};\n\n')
    for alarm in alarm_list:
        if(GAGet(alarm,'Autostart').upper()=='FALSE'):
            autostart='ALARM_SLEEP'
        else:
            autostart='ALARM_AUTOSTART'
        fp.write('''CONST(tpl_callback_action, OS_CONST) %s_action = {
  .b_desc.action = tpl_action_callback,
  .callback = %s_callback
};\n'''%(GAGet(alarm,'Name'),GAGet(alarm,'Name')))
        fp.write('''CONST(tpl_alarm_static, OS_CONST) %s_static = {
  .b_desc = {
    .counter = &SystemCounter_counter_desc,
    .expire = tpl_raise_alarm,
#if (WITH_TRACE == YES)
    .timeobj_id = ALARM_ID_%s,
#endif
#if WITH_OSAPPLICATION == YES
    .app_id = INVALID_OSAPPLICATION_ID,
#endif
  },
  .action = &%s_action
};
VAR(tpl_time_obj, OS_VAR) %s_alarm_desc = {
    .stat_part = (tpl_time_obj_static *)&%s_static,
    .next_to = NULL,
    .prev_to = NULL,
    .cycle = %s,
    .date = %s,
    .state = %s
};\n\n'''%(GAGet(alarm,'Name'),GAGet(alarm,'Name'),GAGet(alarm,'Name'),GAGet(alarm,'Name'),GAGet(alarm,'Name'),GAGet(alarm,'Period'),
           GAGet(alarm,'StartTime'),autostart))
    fp.write('CONSTP2VAR(tpl_time_obj, AUTOMATIC, OS_APPL_DATA) tpl_alarm_table[ALARM_COUNT] = {\n')
    for alarm in alarm_list:
        fp.write('\t&%s_alarm_desc,\n'%(GAGet(alarm,'Name')))
    fp.write('};\n\n')
    fp.write('VAR(tpl_heap_entry, OS_VAR) tpl_ready_list[TASK_NUM+1];\n')
    fp.write('VAR(tpl_rank_count, OS_VAR) tpl_tail_for_prio[TASK_NUM+1];\n')
    fp.write('''/**
 * @internal
 *
 * tpl_kern gather informations on the current executing object and
 * the previous one
 */
VAR(tpl_kern_state, OS_VAR) tpl_kern =
{
  .s_running = NULL,                      /* no running task static descriptor   */
  .s_elected = &TaskIdle_task_stat_desc,  /* elected task to run is idle task    */
  .running = NULL,                        /* no running task dynamic descriptor  */
  .elected = &TaskIdle_task_desc,         /* elected task to run is idle task    */
  .running_id = INVALID_PROC_ID,          /* no running task so no ID            */
  .elected_id = INVALID_PROC_ID,          /* idle task has no ID                 */
  .need_switch = NO_NEED_SWITCH,          /* no context switch needed at start   */
  .need_schedule = FALSE,                 /* no schedule needed at start         */
#if WITH_MEMORY_PROTECTION == YES
  .running_trusted = 1,                  /* at early system startup, we run in  */
                                         /*  kernel mode, so in trusted mode    */
#endif /* WITH_MEMORY_PROTECTION */
};\n''')
    fp.write('CONSTP2CONST(char, AUTOMATIC, OS_APPL_DATA) proc_name_table[TASK_COUNT + ISR_COUNT + NUMBER_OF_CORES] = {\n')
    for task in task_list:
        fp.write('\t"%s",\n'%(GAGet(task,'Name')))
    fp.write('};\n\n')
    for task in task_list:
        fp.write('VAR(tpl_task_events,OS_VAR) %s_events = {0,0};\n'%(GAGet(task,'Name')))
    fp.write('CONSTP2VAR(tpl_task_events, AUTOMATIC, OS_APPL_DATA) tpl_task_events_table[EXTENDED_TASK_COUNT] = {\n');
    for task in task_list[:-1]:
        fp.write('\t&%s_events,\n'%(GAGet(task,'Name')))
    fp.write('};\n\n')
    isr_num = 0
    for isr in isr_list:
        if((int(GAGet(isr,'Vector'),10)+1)>isr_num):
            isr_num = int(GAGet(isr,'Vector'),10)+1
    if(isr_num > 0):
        fp.write('const tpl_callback_func tisr_pc[ %s ] = {\n'%('ISR_NUM'))
        for iid in range(isr_num):
            iname = 'NULL'
            for isr in isr_list:
                if(iid == int(GAGet(isr,'Vector'))):
                    iname = '%s_function'%(GAGet(isr,'Name'))
                    break
            fp.write('\t%s, /* %s */\n'%(iname,iid))
        fp.write('};\n\n')
    fp.close()

def gen_trampoline(gendir,os_list):
    genForTrampolineMisc_H(gendir,os_list)
    genForTrampoline_H(gendir,os_list)
    genForTrampoline_C(gendir,os_list)

