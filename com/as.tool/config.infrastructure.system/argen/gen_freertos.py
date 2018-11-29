__header = '''/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
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
 */
'''

from .util import *
from .GCF import *

__all__ = ['gen_freertos']

__for_freertos_macros = \
"""
#define __FREERTOS__

#define OSDEFAULTAPPMODE (0x00000001u)

#define  E_OS_ACCESS  (StatusType)1
#define  E_OS_CALLEVEL   (StatusType)2
#define  E_OS_ID         (StatusType)3
#define  E_OS_LIMIT      (StatusType)4
#define  E_OS_NOFUNC     (StatusType)5
#define  E_OS_RESOURCE   (StatusType)6
#define  E_OS_STATE      (StatusType)7
#define  E_OS_VALUE      (StatusType)8

#define OsWaitEvent_impl(ID,mask)                                \\
     xEventGroupWaitBits (   os_task_events[ID],                 \\
                             mask,                               \\
                             pdFALSE,                            \\
                             pdFALSE,                            \\
                             portMAX_DELAY                       \\
                         )

#define OsClearEvent_impl(ID,mask)       xEventGroupClearBits( os_task_events[ID], mask )
#define OsGetEvent_impl(ID)              xEventGroupClearBits( os_task_events[ID], 0 )
#define OsSetEvent_impl(ID,mask)         xEventGroupSetBits( os_task_events[ID], mask )
#define OsSetEventFromISR_impl(ID,mask)                              \\
 do {                                                                \\
     BaseType_t xHigherPriorityTaskWoken, xResult;                   \\
     xHigherPriorityTaskWoken = pdFALSE;                             \\
     xEventGroupSetBitsFromISR(  os_task_events[ID],                 \\
                                 mask,                               \\
                                 &xHigherPriorityTaskWoken);         \\
     if( xResult == pdPASS )                                         \\
     {                                                               \\
         portYIELD_FROM_ISR( xHigherPriorityTaskWoken );             \\
     }                                                               \\
 while(0)

/*
 * Task maximum activation is 1.
 */
#define OsActivateTask_impl(ID)  OsSetEvent_impl(ID,OS_EVENT_TASK_ACTIVATION)
/*
 * This will only clear the activation bit of the task.
 * Task will terminate itself when it returns from its main function TASK()
 */
#define OsTerminateTask_impl(ID)     OsClearEvent_impl(ID,OS_EVENT_TASK_ACTIVATION)

#define OsSetRelAlarm_impl(ID,Increment,Cycle)                                                   \\
 do {                                                                                            \\
         BaseType_t xResult;                                                                     \\
         TickType offset;                                                                        \\
         offset = Increment;                                                                     \\
         if(offset > 0)                                                                          \\
         {                                                                                       \\
             offset = 1;                                                                         \\
         }                                                                                       \\
         xResult = xTimerChangePeriod(os_alarm_handles[ID],offset,100);                          \\
         os_alarm_increment[ID]  =   offset;                                                     \\
         os_alarm_period[ID] =   Cycle;                                                          \\
         asAssert(xResult == pdPASS);                                                              \\
 }while(0)

#define OsCancelAlarm_impl(ID)      xTimerStop(os_alarm_handles[ID],100)

#define OsWaitEvent(TaskName,mask)                   OsWaitEvent_impl(TASK_ID_##TaskName,mask)
#define OsClearEvent(TaskName,mask)                  OsClearEvent_impl(TASK_ID_##TaskName,mask)
#define OsGetEvent(TaskName)                         OsGetEvent_impl(TASK_ID_##TaskName)
#define OsSetEvent(TaskName,mask)                    OsSetEvent_impl(TASK_ID_##TaskName,mask)
#define OsSetEventFromISR(TaskName,mask)             OsSetEventFromISR_impl(TASK_ID_##TaskName,mask)

#define OsActivateTask(TaskName)                     OsActivateTask_impl(TASK_ID_##TaskName)
#define OsTerminateTask(TaskName)                    OsTerminateTask_impl(TASK_ID_##TaskName)

#define OsSetRelAlarm(AlarmName,Increment,Cycle)     OsSetRelAlarm_impl(ALARM_ID_##AlarmName,Increment,Cycle)
#define OsCancelAlarm(AlarmName)                     OsCancelAlarm_impl(ALARM_ID_##AlarmName)

#define SetRelAlarm OsSetRelAlarm_impl
#define CancelAlarm OsCancelAlarm_impl

#define GetTaskID(t) OsGetTaskID_impl(t)

#define ActivateTask OsActivateTask_impl
#define SetEvent     OsSetEvent_impl
#define WaitEvent(mask)    E_OK; do  { TaskType __tid;GetTaskID(&__tid);OsWaitEvent_impl(__tid,(mask)); } while(0)
#define GetEvent(__tid,pmask)     do  { *(pmask)=OsGetEvent_impl(__tid); } while(0)
#define ClearEvent(mask)  do  { TaskType __tid;GetTaskID(&__tid);OsClearEvent_impl(__tid,(mask)); } while(0)

#define GetResource(r)
#define ReleaseResource(r)

#define DisableAllInterrupts    vPortEnterCritical
#define EnableAllInterrupts     vPortExitCritical
"""

__for_freertos_functions = \
'''/* ============================ [ LOCALS    ] ====================================================== */
static void FreeRTOS_TaskProcess(void* pvParameters)
{
    for( ;; )
    {
        OsWaitEvent_impl((uint32)pvParameters, OS_EVENT_TASK_ACTIVATION);
        os_task_entrys[(uint32)pvParameters]();
    }
}
static void FreeRTOS_AlarmProcess(TimerHandle_t xTimer)
{
    uint32 id = (uint32)pvTimerGetTimerID(xTimer);

    os_alarm_entrys[id]();

    if(os_alarm_increment[id]!=0)
    {
        os_alarm_increment[id] = 0;
        if(0u == os_alarm_period[id])
        {
            OsCancelAlarm_impl(id);
        }
        else
        {
            xTimerChangePeriod(os_alarm_handles[id],os_alarm_period[id] ,100);
        }
    }
}
/* ============================ [ FUNCTIONS ] ====================================================== */
void OsTaskInit(void)
{
    uint32 i;
    for(i=0;i<TASK_NUM;i++)
    {
        os_task_events[i] = xEventGroupCreate();
        asAssert(os_task_events[i]!=NULL);
        xTaskCreate( FreeRTOS_TaskProcess,os_task_names[i], os_task_stack_size[i], (void*)i, os_task_prioritys[i], &os_task_handles[i] );
        asAssert(os_task_handles[i]!=NULL);
    }
    /* Task Automatically activation */
%s
}

void OsAlarmInit(void)
{
    uint32 i;
    for(i=0;i<ALARM_NUM;i++)
    {
        os_alarm_handles[i] = xTimerCreate(os_alarm_names[i],100,pdTRUE,(void*)i,FreeRTOS_AlarmProcess);
        asAssert(os_alarm_handles[i]!=NULL);
    }
%s
}

void StartOS( AppModeType app_mode )
{
    OsTaskInit();
    OsAlarmInit();

    StartupHook();

    vTaskStartScheduler();
}

void ShutdownOS(StatusType ercd)
{
    asAssert(0);
}

unsigned long ulGetRunTimeCounterValue( void )
{
    return 0;
}

void vConfigureTimerForRunTimeStats(void)
{

}
extern TaskHandle_t * volatile pxCurrentTCB;
StatusType OsGetTaskID_impl ( TaskType* TaskID )
{
    uint32 i;
    for(i=0;i<TASK_NUM;i++)
    {
        if(pxCurrentTCB == os_task_handles[i])
        {
            *TaskID = i;
            return E_OK;
        }
    }
    return E_NOT_OK;
}
'''



def genForFreeRTOS_H(gendir,os_list):
    fp = open('%s/Os_Cfg.h'%(gendir),'w')
    fp.write(__header)
    fp.write('#ifndef OS_CFG_H\n#define OS_CFG_H\n\n')
    fp.write('/* ============================ [ INCLUDES  ] ====================================================== */\n')
    fp.write('#include "Std_Types.h"\n')
    fp.write('#include "FreeRTOS.h"\n')
    fp.write('#include "task.h"\n')
    fp.write('#include "semphr.h"\n')
    fp.write('#include "event_groups.h"\n')
    fp.write('/* ============================ [ MACROS    ] ====================================================== */\n')
    fp.write("#define OS_TICKS2MS(a) (a)\n\n")
    fp.write('%s\n'%(__for_freertos_macros))
    task_list = ScanFrom(os_list,'Task')
    for id,task in enumerate(task_list):
        fp.write('#define TASK_ID_%-32s %s\n'%(GAGet(task,'Name'),id))
    fp.write('#define TASK_NUM%-32s %s\n\n'%(' ',id+1))
    for id,task in enumerate(task_list):
        fp.write('#define TASK_PRIORITY_%-32s %s\n'%(GAGet(task,'Name'),GAGet(task,'Priority')))
    fp.write('\n')
    fp.write('#define OS_EVENT_TASK_ACTIVATION                            ( 0x00800000u )\n')
    for id,task in enumerate(task_list):
        for mask,ev in enumerate(GLGet(task,'EventList')):
            if(GAGet(ev,'Mask')=='AUOT'):
                mask = '(1<<%s)'%(mask)
            else:
                mask = GAGet(ev,'Mask')
            fp.write('#define EVENT_MASK_%-40s %s\n'%('%s_%s'%(GAGet(task,'Name'),GAGet(ev,'Name')),mask))
    fp.write('\n')
    fp.write('#define TASK(TaskName)  void OsTaskMain##TaskName (void)\n')
    fp.write('\n')
    alarm_list = ScanFrom(os_list,'Alarm')
    for id,alarm in enumerate(alarm_list):
        fp.write('#define ALARM_ID_%-32s %s\n'%(GAGet(alarm,'Name'),id))
    fp.write('#define ALARM_NUM%-32s %s\n\n'%(' ',id+1))
    fp.write('#define ALARM(AlarmName)  void OsAlarmMain##AlarmName (void)\n')
    fp.write('/* ============================ [ TYPES     ] ====================================================== */\n')
    fp.write('typedef uint32      AppModeType;\n')
    fp.write('typedef uint8       StatusType;\n')
    fp.write('typedef uint16      AlarmType;\n')
    fp.write('typedef uint16      CounterType;\n')
    fp.write('typedef TickType_t  TickType;\n')
    fp.write('typedef uint16      TaskType;\n')
    fp.write('typedef uint32      EventMaskType;\n')
    fp.write('\n')
    fp.write('/* ============================ [ DECLARES  ] ====================================================== */\n')
    fp.write('/* ============================ [ DATAS     ] ====================================================== */\n')    
    fp.write('extern EventGroupHandle_t os_task_events[TASK_NUM];\n')
    fp.write('extern TaskHandle_t       os_task_handles [TASK_NUM ];\n')
    fp.write('extern TimerHandle_t      os_alarm_handles[ALARM_NUM];\n')
    fp.write('extern TickType           os_alarm_increment [ALARM_NUM];\n')
    fp.write('extern TickType           os_alarm_period [ALARM_NUM];\n')
    fp.write('/* ============================ [ LOCALS    ] ====================================================== */\n')
    fp.write('/* ============================ [ FUNCTIONS ] ====================================================== */\n')
    for id,task in enumerate(task_list):
        fp.write('extern TASK(%s);\n'%(GAGet(task,'Name')))
    fp.write('\n\n')
    for id,alarm in enumerate(alarm_list):
        fp.write('extern ALARM(%s);\n'%(GAGet(alarm,'Name')))
    fp.write('\n\n')
    fp.write('extern StatusType OsGetTaskID_impl ( TaskType* TaskID );\n')
    fp.write('#endif /* OS_CFG_H */\n')
    fp.close()

def genForFreeRTOS_C(gendir,os_list):
    fp = open('%s/Os_Cfg.c'%(gendir),'w')
    fp.write(__header)
    fp.write('/* ============================ [ INCLUDES  ] ====================================================== */\n')
    fp.write('#include "Os.h"\n')
    fp.write('/* ============================ [ MACROS    ] ====================================================== */\n')
    fp.write('/* ============================ [ TYPES     ] ====================================================== */\n')
    fp.write('typedef void (*void_function_void_t)(void);\n')
    fp.write('/* ============================ [ DECLARES  ] ====================================================== */\n')
    fp.write('/* ============================ [ DATAS     ] ====================================================== */\n')
    fp.write('EventGroupHandle_t os_task_events  [TASK_NUM ];\n')
    fp.write('TaskHandle_t       os_task_handles [TASK_NUM ];\n')
    fp.write('TimerHandle_t      os_alarm_handles[ALARM_NUM];\n')
    fp.write('TickType           os_alarm_increment [ALARM_NUM];\n')
    fp.write('TickType           os_alarm_period [ALARM_NUM];\n')
    task_list = ScanFrom(os_list,'Task')
    alarm_list = ScanFrom(os_list,'Alarm')
    fp.write('static const void_function_void_t os_task_entrys[TASK_NUM] = { \n')
    for id,task in enumerate(task_list):
        fp.write('\tOsTaskMain%s,\n'%(GAGet(task,'Name')))
    fp.write('};\n\n')
    fp.write('static const char os_task_names[TASK_NUM][32] = { \n')
    for id,task in enumerate(task_list):
        fp.write('\t"%s",\n'%(GAGet(task,'Name')))
    fp.write('};\n\n')   
    fp.write('static const uint16 os_task_stack_size[TASK_NUM] = { \n')
    for id,task in enumerate(task_list):
        fp.write('\t%s,\n'%(GAGet(task,'StackSize')))
    fp.write('};\n\n')  
    fp.write('static const uint8 os_task_prioritys[TASK_NUM] = { \n')
    for id,task in enumerate(task_list):
        fp.write('\t%s,\n'%(GAGet(task,'Priority')))
    fp.write('};\n\n')  
    fp.write('static const void_function_void_t os_alarm_entrys[ALARM_NUM] = { \n')
    for id,alarm in enumerate(alarm_list):
        fp.write('\tOsAlarmMain%s,\n'%(GAGet(alarm,'Name')))
    fp.write('};\n\n')
    fp.write('static const char os_alarm_names[ALARM_NUM][32] = { \n')
    for id,alarm in enumerate(alarm_list):
        fp.write('\t"%s",\n'%(GAGet(alarm,'Name')))
    fp.write('};\n\n')  
    str_activate_task = ''
    for id,task in enumerate(task_list):
        if(GAGet(task,'Autostart').upper()=='TRUE'):
            str_activate_task += '\tOsActivateTask(%s);\n'%(GAGet(task,'Name'))
    str_active_alarm  = ''
    for id,alarm in enumerate(alarm_list):
        if(GAGet(alarm,'Autostart').upper()=='TRUE'):
            str_active_alarm += '\tOsSetRelAlarm(%s,%s,%s);\n'%(GAGet(alarm,'Name'),GAGet(alarm,'StartTime'),GAGet(alarm,'Period'))    
    fp.write(__for_freertos_functions%(str_activate_task,str_active_alarm))           
    fp.close()

def gen_freertos(gendir,os_list):
    genForFreeRTOS_H(gendir,os_list)
    genForFreeRTOS_C(gendir,os_list)
