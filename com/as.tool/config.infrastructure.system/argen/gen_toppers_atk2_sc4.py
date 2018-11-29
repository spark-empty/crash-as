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

__all__ = ['gen_toppers_atk2_sc4']

def genH(gendir,os_list):
    fp = open('%s/Os_Cfg.h'%(gendir),'w')
    fp.write(__header)
    fp.write('#ifndef OS_CFG_H\n#define OS_CFG_H\n\n')
    fp.write('/* ============================ [ INCLUDES  ] ====================================================== */\n')
    fp.write('#include "Std_Types.h"\n')
    fp.write('/* ============================ [ MACROS    ] ====================================================== */\n')
    fp.write('#define __TOPPERS_ATK2_SC4__\n\n')
    fp.write('#define ALLFUNC\n\n')
    fp.write('#define CFG_USE_ERRORHOOK\n')
    fp.write('#define CFG_USE_POSTTASKHOOK\n')
    fp.write('#define CFG_USE_PRETASKHOOK\n')
    fp.write('#define CFG_USE_STACKMONITORING\n')
    fp.write('#define CFG_USE_PROTECTIONHOOK\n')
    fp.write('#define CFG_USE_SHUTDOWNHOOK\n')
    fp.write('#define CFG_USE_STARTUPHOOK\n')
    fp.write('\n')
    appmode_list = ScanFrom(os_list,'ApplicationMode')
    for id,appmode in enumerate(appmode_list):
        fp.write('#define %-32s %s\n'%(GAGet(appmode,'Name'),id))
    fp.write('#define APP_MODE_NUM%-20s %s\n\n'%(' ',id+1))
    app_list = ScanFrom(os_list,'Application')
    for id,app in enumerate(app_list):
        fp.write('#define APP_ID_%-32s %s\n'%(GAGet(app,'Name'),id))
    fp.write('#define APP_NUM%-32s %s\n\n'%(' ',id+1))
    res_list = ScanFrom(os_list,'Resource')
    for id,res in enumerate(res_list):
        fp.write('#define %-32s %s\n'%(GAGet(res,'Name'),id))
    fp.write('#define RES_NUM%-25s %s\n\n'%(' ',id+1))
        
    task_list = ScanFrom(os_list,'Task')
    for id,task in enumerate(task_list):
        fp.write('#define TASK_ID_%-32s %s\n'%(GAGet(task,'Name'),id))
    fp.write('#define TASK_NUM%-32s %s\n\n'%(' ',id+1))
    fp.write('/*0 is the highest priority, TMAX_TPRI is the lowest */\n')
    for id,task in enumerate(task_list):
        fp.write('#define TASK_PRIORITY_%-32s (TMAX_TPRI-%s)\n'%(GAGet(task,'Name'),GAGet(task,'Priority')))
    fp.write('\n')
    for id,task in enumerate(task_list):
        cstr = '( 0 | (1<<APP_ID_%s)'%(GAGet(task,'Application'))
        for app in GLGet(task,'ApplicationList'):
                cstr += ' | (1<<APP_ID_%s)'%(GAGet(app,'Name'))
        cstr += ' )'
        fp.write('#define TASK_APP_ACCESS_MASK_%-32s %s\n'%(GAGet(task,'Name'),cstr))
    fp.write('\n')
    for id,task in enumerate(task_list):
        cstr = '( 0'
        if(GAGet(task,'Autostart').upper() == 'TRUE'):
            for appmode in GLGet(task,'ApplicationModeList'):
                cstr += ' | (1<<%s)'%(GAGet(appmode,'Name'))
        cstr += ' )'
        fp.write('#define TASK_APPMODE_MASK_%-32s %s\n'%(GAGet(task,'Name'),cstr))
    fp.write('\n')
    for id,task in enumerate(task_list):
        for mask,ev in enumerate(GLGet(task,'EventList')):
            if(GAGet(ev,'Mask')=='AUTO'):
                mask = '(1<<%s)'%(mask)
            else:
                mask = GAGet(ev,'Mask')
            fp.write('#define EVENT_MASK_%-40s %s\n'%('%s_%s'%(GAGet(task,'Name'),GAGet(ev,'Name')),mask))
    fp.write('\n')
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
    for id,isr in enumerate(isr_list):
        cstr = '( 0 | (1<<APP_ID_%s)'%(GAGet(isr,'Application'))
        for app in GLGet(isr,'ApplicationList'):
                cstr += ' | (1<<APP_ID_%s)'%(GAGet(app,'Name'))
        cstr += ' )'
        fp.write('#define ISR_APP_ACCESS_MASK_%-32s %s\n'%(GAGet(isr,'Name'),cstr)) 
    fp.write('\n')   
    counter_list = ScanFrom(os_list,'Counter')
    for id,counter in enumerate(counter_list):
        fp.write('#define COUNTER_ID_%-32s %s\n'%(GAGet(counter,'Name'),id))
    fp.write('#define COUNTER_NUM%-32s %s\n\n'%(' ',id+1))
    for id,counter in enumerate(counter_list):
        cstr = '( 0 | (1<<APP_ID_%s)'%(GAGet(counter,'Application'))
        for app in GLGet(counter,'ApplicationList'):
                cstr += ' | (1<<APP_ID_%s)'%(GAGet(app,'Name'))
        cstr += ' )'
        fp.write('#define COUNTER_APP_ACCESS_MASK_%-32s %s\n'%(GAGet(counter,'Name'),cstr))
    fp.write('\n')
    alarm_list = ScanFrom(os_list,'Alarm')
    for id,alarm in enumerate(alarm_list):
        fp.write('#define ALARM_ID_%-32s %s\n'%(GAGet(alarm,'Name'),id))
    fp.write('#define ALARM_NUM%-32s %s\n\n'%(' ',id+1))
    for id,alarm in enumerate(alarm_list):
        cstr = '( 0'
        if(GAGet(alarm,'Autostart').upper() == 'TRUE'):
            for appmode in GLGet(alarm,'ApplicationModeList'):
                cstr += ' | (1<<%s)'%(GAGet(appmode,'Name'))
        cstr += ' )'
        fp.write('#define ALARM_APPMODE_MASK_%-32s %s\n'%(GAGet(alarm,'Name'),cstr))
    fp.write('\n')
    for id,alarm in enumerate(alarm_list):
        cstr = '( 0 | (1<<APP_ID_%s)'%(GAGet(alarm,'Application'))
        for app in GLGet(alarm,'ApplicationList'):
                cstr += ' | (1<<APP_ID_%s)'%(GAGet(app,'Name'))
        cstr += ' )'
        fp.write('#define ALARM_APP_ACCESS_MASK_%-32s %s\n'%(GAGet(alarm,'Name'),cstr))
    fp.write('\n')
    
    fp.write('\n#define ALARM(a)  void AlarmMain##a(void)\n\n')
    
    fp.write('#include "atk_os.h"\n')
    fp.write('/* ============================ [ TYPES     ] ====================================================== */\n')
    fp.write('/* ============================ [ DECLARES  ] ====================================================== */\n')
    fp.write('/* ============================ [ DATAS     ] ====================================================== */\n')
    fp.write('/* ============================ [ LOCALS    ] ====================================================== */\n')
    fp.write('/* ============================ [ FUNCTIONS ] ====================================================== */\n')
    fp.write('extern void object_initialize(void);\n')
    fp.write('extern void object_terminate(void);\n\n')
    for id,task in enumerate(task_list):
        fp.write('extern TASK(%s);\n'%(GAGet(task,'Name')))
    fp.write('\n\n')
    for id,alarm in enumerate(alarm_list):
        fp.write('extern ALARM(%s);\n'%(GAGet(alarm,'Name')))
    fp.write('\n#endif /* OS_CFG_H_ */\n\n')
    fp.close()

def genC(gendir,os_list):
    fp = open('%s/Os_Cfg.c'%(gendir),'w')
    fp.write(__header)
    fp.write('/* ============================ [ INCLUDES  ] ====================================================== */\n')
    fp.write('#include "Std_Types.h"\n')
    fp.write('#include "Os.h"\n')
    fp.write('#include "kernel_impl.h"\n')
    fp.write('#include "osap.h"\n')
    fp.write('#include "counter.h"\n')
    fp.write('#include "interrupt.h"\n')
    fp.write('#include "scheduletable.h"\n')
    fp.write('#include "task.h"\n')
    fp.write('#include "alarm.h"\n')
    fp.write('#include "ioc_impl.h"\n')
    fp.write('#include "memory.h"\n')
    fp.write('/* ============================ [ MACROS    ] ====================================================== */\n')
    fp.write('/* ============================ [ TYPES     ] ====================================================== */\n')
    fp.write('typedef void (*void_function_void_t)(void);\n')
    fp.write('/* ============================ [ DECLARES  ] ====================================================== */\n')
    isr_list = ScanFrom(os_list,'ISR')
    for isr in isr_list:
        fp.write('extern ISR(%s);\n'%(GAGet(isr,'Name')))
    fp.write('/* ============================ [ DATAS     ] ====================================================== */\n')
    fp.write('const TaskType tnum_task    = TASK_NUM;\n')
    fp.write('const TaskType tnum_exttask = TASK_NUM;\n')
    fp.write('TCB            *p_runtsk;\n')
    fp.write('TCB            *p_schedtsk;\n')
    fp.write('PriorityType    nextpri;\n')
    fp.write('QUEUE        ready_queue[TNUM_TPRI];\n')
    fp.write('uint16        ready_primap;\n')
    fp.write('TCB            tcb_table[TASK_NUM];\n')
    task_list = ScanFrom(os_list,'Task')
    for id,task in enumerate(task_list):
        fp.write('static StackType  %s_stk[ (%s+sizeof(StackType)-1)/sizeof(StackType) ];\n'%(GAGet(task,'Name'),GAGet(task,'StackSize')))
    fp.write('const TINIB    tinib_table[TASK_NUM] = \n{\n')
    for id,task in enumerate(task_list):
        fp.write('\t{ /* %s */\n'%(GAGet(task,'Name')))
        fp.write('\t\t.task=TaskMain%s,\n'%(GAGet(task,'Name')))
        fp.write('\t\t.sstksz=%s,\n'%(GAGet(task,'StackSize')))
        fp.write('\t\t.sstk=(void*)%s_stk,\n'%(GAGet(task,'Name')))
        fp.write('\t\t.ustksz=%s, /* TODO: ?? */\n'%(GAGet(task,'StackSize')))
        fp.write('\t\t.ustk=(void*)%s_stk, /* TODO: ?? */\n'%(GAGet(task,'Name')))
        fp.write('\t\t.p_osapcb=&osapcb_table[APP_ID_%s],\n'%(GAGet(task,'Application')))
        fp.write('\t\t.acsbtmp=TASK_APP_ACCESS_MASK_%s,\n'%(GAGet(task,'Name')))
        fp.write('\t\t.inipri=TASK_PRIORITY_%s,\n'%(GAGet(task,'Name')))
        fp.write('\t\t.exepri=TASK_PRIORITY_%s,\n'%(GAGet(task,'Name')))
        fp.write('\t\t.maxact=%s,\n'%(GAGet(task,'Activation')))
        fp.write('\t\t.autoact=TASK_APPMODE_MASK_%s,\n'%(GAGet(task,'Name')))
        fp.write('\t\t.time_frame.tfcount=%s,\n'%('0'))
        fp.write('\t\t.time_frame.tftick=%s,\n'%('0'))
        fp.write('\t\t.execution_budget=%s,\n'%('1'))
        fp.write('\t\t.monitoring=%s,\n'%('1'))
        fp.write('\t},\n')
    fp.write('};\n\n')
    fp.write('const AppModeType    tnum_appmode = APP_MODE_NUM;\n')
    fp.write('\n')
    
    counter_list = ScanFrom(os_list,'Counter')
    fp.write('const CounterType    tnum_counter=COUNTER_NUM;\n')
    fp.write('const CNTINIB        cntinib_table[COUNTER_NUM] = \n{\n')
    for counter in counter_list:
        fp.write('\t{ /* %s */\n'%(GAGet(counter,'Name')))
        fp.write('\t\t.maxval=%s,\n'%(GAGet(counter,'MaxAllowed')))
        fp.write('\t\t.maxval2=(%s*2)+1,\n'%(GAGet(counter,'MaxAllowed')))
        fp.write('\t\t.tickbase=%s,\n'%(GAGet(counter,'TicksPerBase')))
        fp.write('\t\t.mincyc=%s,\n'%(GAGet(counter,'MinCycle')))
        fp.write('\t\t.p_osapcb=&osapcb_table[APP_ID_%s],\n'%(GAGet(counter,'Application')))
        fp.write('\t\t.acsbtmp=COUNTER_APP_ACCESS_MASK_%s,\n'%(GAGet(counter,'Name')))
        fp.write('\t},\n')
    fp.write('};\n\n')
    fp.write('CNTCB                cntcb_table[COUNTER_NUM];\n')
    
    fp.write('const CounterType    tnum_hardcounter=0;\n')
    fp.write('const HWCNTINIB        hwcntinib_table[1];\n')
    fp.write('\n')
    isr_list = ScanFrom(os_list,'ISR')
    isr_num = len(isr_list)
    
    fp.write('const InterruptNumberType    tnum_intno = %s;\n'%('ISR_MAX'))
    fp.write('const ISRType    tnum_isr2=%s;\n'%('ISR_MAX'))
    fp.write('const INTINIB    intinib_table[%s] = \n{\n'%('ISR_MAX'))
    for isr in isr_list:
        fp.write('\t{ /* %s */\n'%(GAGet(isr,'Name')))
        fp.write('\t\t.intno=%s,\n'%(GAGet(isr,'Vector')))
        fp.write('\t\t.intatr=%s,\n'%(0))
        fp.write('\t\t.intpri=%s,\n'%(0))
        fp.write('\t\t#if defined(TOPPERS_CFG1_OUT) || defined(CFG_USE_STACKMONITORING)\n')
        fp.write('\t\t.remain_stksz=%s,\n'%(0))
        fp.write('\t\t#endif\n')
        fp.write('\t},\n')
    fp.write('};\n\n')
    fp.write('const ISRINIB    isrinib_table[%s] = \n{\n'%('ISR_MAX'))
    for isr in isr_list:
        fp.write('\t{ /* %s */\n'%(GAGet(isr,'Name')))
        fp.write('\t\t.p_intinib=&isrinib_table[ISR_ID_%s],\n'%(GAGet(isr,'Name')))
        fp.write('\t\t.p_osapcb=&osapcb_table[APP_ID_%s],\n'%(GAGet(isr,'Application')))
        fp.write('\t\t.acsbtmp=ISR_APP_ACCESS_MASK_%s,\n'%(GAGet(isr,'Name')))
        fp.write('\t\t.time_frame=%s,\n'%(0))
        fp.write('\t},\n')
    fp.write('};\n\n')    
    for isr in isr_list:
        if((int(GAGet(isr,'Vector'),10)+1)>isr_num):
            isr_num = int(GAGet(isr,'Vector'),10)+1
    if(isr_num > 0):
        fp.write('const FunctionRefType tisr_pc[ %s ] = {\n'%('ISR_NUM'))
        for iid in range(isr_num):
            iname = 'NULL'
            for isr in isr_list:
                if(iid == int(GAGet(isr,'Vector'))):
                    iname = 'ISRMain%s'%(GAGet(isr,'Name'))
                    break
            fp.write('\t%s, /* %s */\n'%(iname,iid))
        fp.write('};\n\n')
        fp.write('const ISRType tisr_id[ %s ] = {\n'%(isr_num))
        for iid in range(isr_num):
            iname = 'INVALID_ISR'
            for isr in isr_list:
                if(iid == int(GAGet(isr,'Vector'))):
                    iname = 'ISR_ID_%s'%(GAGet(isr,'Name'))
                    break
            fp.write('\t%s, /* %s */\n'%(iname,iid))
        fp.write('};\n\n')        
    fp.write('ISRCB            isrcb_table[ISR_NUM];\n')
    fp.write('ISRCB            *p_runisr;\n')
    fp.write('uint8            sus_all_cnt;\n')
    fp.write('uint8            sus_os_cnt;\n')
    fp.write('PriorityType        sus_os_prevpri;\n')
    fp.write('const TickType    osinterruptlock_budget;\n')
    fp.write('TickType            os_difftime;\n')
    fp.write('MonitoringType    os_saved_watchtype;\n')
    fp.write('\n')
    fp.write('const ScheduleTableType    tnum_scheduletable=0;\n')
    fp.write('const ScheduleTableType    tnum_implscheduletable=0;\n')
    fp.write('const SCHTBLINIB            schtblinib_table[1];\n')
    fp.write('SCHTBLCB                    schtblcb_table[1];\n')
    fp.write('\n')
    fp.write('\n')
    app_list = ScanFrom(os_list,'Application')
    fp.write('const ApplicationType            tnum_osap=APP_NUM;\n')
    fp.write('const OSAPINIB    osapinib_table[APP_NUM] = \n{\n')
    for app in app_list:
        fp.write('\t{ /* %s*/\n'%(GAGet(app,'Name')))
        if(GAGet(app,'UseRestartTask').upper()=='TRUE'):
            fp.write('\t\t.p_restart_tcb=&tcb_table[TASK_ID_%s],\n'%(GAGet(app,'RestartTask')))
        else:
            fp.write('\t\t.p_restart_tcb=%s,\n'%(NULL))
        fp.write('\t\t.osap_trusted=%s,\n'%(GAGet(app,'UseRestartTask').upper()))
        fp.write('\t\t.btptn=%s,/* TODO */\n'%(0))
        fp.write('\t},\n')
    fp.write('};\n\n')
    fp.write('const TrustedFunctionIndexType    tnum_tfn=0;\n')
    fp.write('OSAPCB            osapcb_table[APP_NUM];\n')
    fp.write('OSAPCB            *p_runosap;\n')
    
    fp.write('const TFINIB        tfinib_table[1];\n')
    fp.write('\n')
    fp.write('\n')
    alarm_list = ScanFrom(os_list,'Alarm')
    fp.write('const AlarmType    tnum_alarm=ALARM_NUM;\n')
    fp.write('const ALMINIB    alminib_table[ALARM_NUM] = \n{\n')
    for id,alarm in enumerate(alarm_list):
        fp.write('\t{ /* %s */\n'%(GAGet(alarm,'Name')))
        fp.write('\t\t.p_cntcb=&cntcb_table[COUNTER_ID_%s],\n'%(GAGet(alarm,'Counter')))
        fp.write('\t\t.action=AlarmMain%s,\n'%(GAGet(alarm,'Name')))
        fp.write('\t\t.autosta=ALARM_APPMODE_MASK_%s,\n'%(GAGet(alarm,'Name')))
        fp.write('\t\t.almval=%s,\n'%(GAGet(alarm,'StartTime')))
        fp.write('\t\t.cycle=%s,\n'%(GAGet(alarm,'Period')))
        fp.write('\t\t.p_osapcb=&osapcb_table[APP_ID_%s],\n'%(GAGet(alarm,'Application')))
        fp.write('\t\t.acsbtmp=ALARM_APP_ACCESS_MASK_%s,\n'%(GAGet(alarm,'Name')))
        fp.write('\t},\n')
    fp.write('};\n\n')
    fp.write('ALMCB            almcb_table[ALARM_NUM];\n')
    fp.write('\n')
    fp.write('const IocType    tnum_ioc=0;\n')
    fp.write('const IocType    tnum_queueioc=0;\n')
    fp.write('const IOCWRPINIB    iocwrpinib_table[1];\n')
    fp.write('const IOCINIB    iocinib_table[1];\n')
    fp.write('IOCCB            ioccb_table[1];\n')
    fp.write('const IOCWRPINIB    iocwrpinib_table[1];\n')
    fp.write('void                *ioc_inival_table[1];\n')
    fp.write('\n')
    fp.write('const ResourceType    tnum_stdresource=RES_NUM;\n')
    fp.write('const RESINIB        resinib_table[1];\n')
    fp.write('RESCB                rescb_table[1];\n')
    fp.write('\n')
    fp.write('const uint32        tnum_meminib=0;\n')
    fp.write('void * const    memtop_table[1];\n')
    fp.write('const MEMINIB    meminib_table[1];\n')
    fp.write('\n')
    fp.write('const uint32            tnum_datasec=0;\n')
    fp.write('const DATASECINIB    datasecinib_table[1];\n')
    fp.write('const uint32        tnum_bsssec=0;\n')
    fp.write('const BSSSECINIB    bsssecinib_table[1];\n')
    fp.write('/* ============================ [ LOCALS    ] ====================================================== */\n')
    fp.write('/* ============================ [ FUNCTIONS ] ====================================================== */\n')
    fp.write('void object_initialize(void)\n')
    fp.write('{\n')
    fp.write('\ttask_initialize();\n')
    fp.write('\tcounter_initialize();\n')
    fp.write('\talarm_initialize();\n')
    fp.write('\tresource_initialize();\n')
    fp.write('\tosap_initialize();\n')
    fp.write('}\n')
    fp.write('void object_terminate(void)  {}\n')
    fp.write('\n')

def gen_toppers_atk2_sc4(gendir,os_list):
    genH(gendir,os_list)
    genC(gendir,os_list)