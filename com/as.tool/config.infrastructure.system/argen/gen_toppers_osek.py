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

__all__ = ['gen_toppers_osek']

__for_toppers_osek_macro =  \
'''#define ALARM(AlarmName)  ALARMCALLBACK(AlarmName)

/* OSEK OS Debugh helper */
#define LOG_STAOS_ENTER(mode)      ASLOG(OS,"StartOS enter, Appmode=%d\\n",mode)
#define LOG_STAOS_LEAVE()          ASLOG(OS,"StartOS leave\\n")
#define LOG_TERTSK_ENTER()         ASLOG(OS,"TerminateTask enter, runtsk=%d\\n",runtsk)
#define LOG_TERTSK_LEAVE(ercd)     ASLOG(OS,"TerminateTask leave,ercd=%d\\n",ercd)
#define LOG_STUTOS_ENTER(ercd)     ASLOG(OS,"ShutdownOS enter, ercd = %d\\n",ercd)
#define LOG_STUTOS_LEAVE()         ASLOG(OS,"ShutdownOS leave\\n")
#define LOG_ACTTSK_ENTER(tskid)    ASLOG(OS,"ActivateTask enter, tskid=%d\\n",tskid)   
#define LOG_ACTTSK_LEAVE(ercd)     ASLOG(OS,"ActivateTask leave, ercd = %d\\n",ercd)
#define LOG_SIGCNT_ENTER(cntid)    ASLOG(OFF,"SignalCounter enter, cntid=%d\\n",cntid) 
#define LOG_SIGCNT_LEAVE(ercd)     ASLOG(OFF,"SignalCounter leave, ercd = %d\\n",ercd)
#define LOG_SETREL_ENTER(almid, incr, cycle)    ASLOG(OS,"SetRelAlarm enter, almid=%d, incr=%d, cycle=%d\\n",almid,incr,cycle) 
#define LOG_SETREL_LEAVE(ercd)                  ASLOG(OS,"SetRelAlarm leave, ercd=%d\\n",ercd)
#define LOG_SETABS_ENTER(almid, incr, cycle)    ASLOG(OS,"SetAbsAlarm enter, almid=%d, incr=%d, cycle=%d\\n",almid,incr,cycle)
#define LOG_SETABS_LEAVE(ercd)                  ASLOG(OS,"SetAbsAlarm leave, ercd=%d\\n",ercd)
#define LOG_SETEVT_ENTER(tskid, mask)           ASLOG(OS,"SetEvent enter, tskid=%d, mask=%08Xh\\n",tskid,mask)
#define LOG_SETEVT_LEAVE(ercd)                  ASLOG(OS,"SetEvent leave, ercd=%d\\n",ercd)
#define LOG_CLREVT_ENTER(mask)                  ASLOG(OS,"ClearEvent enter, mask=%d\\n",mask)
#define LOG_CLREVT_LEAVE(ercd)                  ASLOG(OS,"ClearEvent leave, ercd=%d\\n",ercd)
#define LOG_GETEVT_ENTER(tskid, p_mask)         ASLOG(OS,"GetEvent enter, tskid=%d\\n",tskid)
#define LOG_GETEVT_LEAVE(ercd, mask)            ASLOG(OS,"GetEvent leave, ercd=%d, mask=%08Xh\\n",ercd,mask)
#define LOG_WAIEVT_ENTER(mask)                  ASLOG(OS,"WaitEvent enter,mask=%08Xh\\n",mask)
#define LOG_WAIEVT_LEAVE(ercd)                  ASLOG(OS,"WaitEvent leave,ercd=%d\\n",ercd)
#define LOG_GETRES_ENTER(resid)                 ASLOG(OS,"GetResource enter, resid=%d\\n",resid)
#define LOG_GETRES_LEAVE(ercd)                  ASLOG(OS,"GetResource leave, ercd=%d\\n",ercd)
#define LOG_RELRES_ENTER(resid)                 ASLOG(OS,"ReleaseResource enter, resid=%d\\n",resid)
#define LOG_RELRES_LEAVE(ercd)                  ASLOG(OS,"ReleaseResource leave, ercd=%d\\n",ercd)
#define LOG_GETALB_ENTER(almid, p_info)         ASLOG(OS,"GelAlarmBase enter, almid=%d\\n",almid)
#define LOG_GETALB_LEAVE(ercd)                  ASLOG(OS,"GelAlarmBase leave, ercd=%d\\n",ercd)
#define LOG_GETALM_ENTER(almid, p_tick)         ASLOG(OS,"GelAlarm enter, almid=%d\\n",almid)
#define LOG_GETALM_LEAVE(ercd)                  ASLOG(OS,"GelAlarmBase leave, ercd=%d\\n",ercd)
#define LOG_CANALM_ENTER(almid)                 ASLOG(OS,"CancelAlarm enter, almid=%d\\n",almid)
#define LOG_CANALM_LEAVE(ercd)                  ASLOG(OS,"CancelAlarm leave, ercd=%d\\n",ercd)
#define LOG_DISINT_ENTER()                      ASLOG(OS,"DisableAllInterrupts enter\\n")
#define LOG_DISINT_LEAVE()                      ASLOG(OS,"DisableAllInterrupts leave\\n")
#define LOG_ENAINT_ENTER()                      ASLOG(OS,"EnableAllInterrupts enter\\n")
#define LOG_ENAINT_LEAVE()                      ASLOG(OS,"EnableAllInterrupts leave\\n")
#define LOG_SUSALL_ENTER()                      ASLOG(OS,"SuspendAllInterrupts enter\\n")
#define LOG_SUSALL_LEAVE()                      ASLOG(OS,"SuspendAllInterrupts leave\\n")
#define LOG_RSMALL_ENTER()                      ASLOG(OS,"ResumeAllInterrupts enter\\n")
#define LOG_RSMALL_LEAVE()                      ASLOG(OS,"ResumeAllInterrupts leave\\n")
#define LOG_SUSOSI_ENTER()                      ASLOG(OS,"SuspendOSInterrupts enter\\n")
#define LOG_SUSOSI_LEAVE()                      ASLOG(OS,"SuspendOSInterrupts leave\\n")
#define LOG_RSMOSI_ENTER()                      ASLOG(OS,"ResumeOSInterrupts enter\\n")
#define LOG_RSMOSI_LEAVE()                      ASLOG(OS,"ResumeOSInterrupts leave\\n")
#define LOG_GETAAM_ENTER()                      ASLOG(OS,"GetActiveApplicationMode enter\\n")
#define LOG_GETAAM_LEAVE(mode)                  ASLOG(OS,"GetActiveApplicationMode leave, appmode=%d\\n",mode)
#define LOG_CHNTSK_ENTER(tskid)                 ASLOG(OS,"ChainTask enter, tskid=%d\\n",tskid)
#define LOG_CHNTSK_LEAVE(ercd)                  ASLOG(OS,"ChainTask leave, ercd=%d\\n",ercd)
#define LOG_SCHED_ENTER()                       ASLOG(OS,"Schedule enter\\n")
#define LOG_SCHED_LEAVE(ercd)                   ASLOG(OS,"Schedule leave, ercd=%d\\n",ercd)
#define LOG_GETTID_ENTER(p_tskid)               ASLOG(OS,"GetTaskID enter\\n")
#define LOG_GETTID_LEAVE(ercd, tskid)           ASLOG(OS,"GetTaskID leave, ercd=%d, tskid=%d\\n",ercd,tskid)
#define LOG_GETTST_ENTER(tskid, p_state)        ASLOG(OS,"GetTaskState enter, tskid=%d\\n",tskid)
#define LOG_GETTST_LEAVE(ercd,  state)          ASLOG(OS,"GetTaskState leave, ercd=%d, tskid=%d\\n",ercd,state)'''


def genForToppersOSEK_H(gendir,os_list):
    fp = open('%s/Os_Cfg.h'%(gendir),'w')
    fp.write(__header)
    fp.write('#ifndef OS_CFG_H\n#define OS_CFG_H\n\n')
    fp.write('/* ============================ [ INCLUDES  ] ====================================================== */\n')
    fp.write('#include "Std_Types.h"\n')
    fp.write('#include "kernel.h"\n')
    fp.write('/* ============================ [ MACROS    ] ====================================================== */\n')
    fp.write('#define __TOPPERS_OSEK__\n\n')
    fp.write("#define OS_TICKS2MS(a) (a)\n\n")
    task_list = ScanFrom(os_list,'Task')
    for id,task in enumerate(task_list):
        fp.write('#define TASK_ID_%-32s %s\n'%(GAGet(task,'Name'),id))
    fp.write('#define TASK_NUM%-32s %s\n\n'%(' ',id+1))
    for id,task in enumerate(task_list):
        fp.write('#define TASK_PRIORITY_%-32s %s\n'%(GAGet(task,'Name'),GAGet(task,'Priority')))
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
        if((int(isr.attrib['Vector'],10)+1)>isr_num):
            isr_num = int(isr.attrib['Vector'],10)+1
    fp.write('#define ISR_NUM  %s\n\n'%(isr_num))
    
    counter_list = ScanFrom(os_list,'Counter')
    for id,counter in enumerate(counter_list):
        fp.write('#define COUNTER_ID_%-32s %s\n'%(GAGet(counter,'Name'),id))
    fp.write('#define COUNTER_NUM%-32s %s\n\n'%(' ',id+1))
    alarm_list = ScanFrom(os_list,'Alarm')
    for id,alarm in enumerate(alarm_list):
        fp.write('#define ALARM_ID_%-32s %s\n'%(GAGet(alarm,'Name'),id))
    fp.write('#define ALARM_NUM%-32s %s\n\n'%(' ',id+1))
    
    fp.write('%s\n'%(__for_toppers_osek_macro))
    fp.write('/* ============================ [ TYPES     ] ====================================================== */\n')
    fp.write('/* ============================ [ DECLARES  ] ====================================================== */\n')
    fp.write('/* ============================ [ DATAS     ] ====================================================== */\n')
    fp.write('/* ============================ [ LOCALS    ] ====================================================== */\n')
    fp.write('/* ============================ [ FUNCTIONS ] ====================================================== */\n')
    for id,task in enumerate(task_list):
        fp.write('extern TASK(%s);\n'%(GAGet(task,'Name')))
    fp.write('\n\n')
    for id,alarm in enumerate(alarm_list):
        fp.write('extern ALARM(%s);\n'%(GAGet(alarm,'Name')))
    fp.write('\n\n')
    fp.write('#endif /* OS_CFG_H */\n\n')
    fp.close()

def genForToppersOSEK_C(gendir,os_list):
    fp = open('%s/Os_Cfg.c'%(gendir),'w')
    fp.write(__header)
    fp.write('/* ============================ [ INCLUDES  ] ====================================================== */\n')
    fp.write('#include "Os.h"\n')
    fp.write('#include "osek_kernel.h"\n')
    fp.write('/* ============================ [ MACROS    ] ====================================================== */\n')
    fp.write('/* ============================ [ TYPES     ] ====================================================== */\n')
    fp.write('typedef void (*void_function_void_t)(void);\n')
    fp.write('/* ============================ [ DECLARES  ] ====================================================== */\n')
    isr_list = ScanFrom(os_list,'ISR')
    for isr in isr_list:
        fp.write('extern void %s (void);\n'%(isr.attrib['Name']))
    fp.write('extern void task_initialize(void);\n')
    fp.write('extern void alarm_initialize(void);\n')
    fp.write('extern void resource_initialize(void);\n')
    fp.write('/* ============================ [ DATAS     ] ====================================================== */\n')
    fp.write('const UINT8 tnum_task    = TASK_NUM;\n')
    fp.write('const UINT8 tnum_exttask = TASK_NUM;\n')
    fp.write('\n')
    task_list = ScanFrom(os_list,'Task')
    fp.write('const Priority  tinib_inipri[TASK_NUM] = {\n')
    for id,task in enumerate(task_list):
        fp.write('\t%s, /* %s */\n'%(GAGet(task,'Priority'),GAGet(task,'Name')))
    fp.write('};\n\n')
    fp.write('const Priority  tinib_exepri[TASK_NUM] = {\n')
    for id,task in enumerate(task_list):
        fp.write('\t%s, /* %s */\n'%(GAGet(task,'Priority'),GAGet(task,'Name')))
    fp.write('};\n\n')
    fp.write('const UINT8  tinib_maxact[TASK_NUM] = {\n')
    for id,task in enumerate(task_list):
        fp.write('\t%s, /* %s */\n'%(GAGet(task,'Activation'),GAGet(task,'Name')))
    fp.write('};\n\n')
    fp.write('const AppModeType  tinib_autoact[TASK_NUM] = {\n')
    for id,task in enumerate(task_list):
        fp.write('\t%s, /* %s */\n'%('OSDEFAULTAPPMODE',GAGet(task,'Name')))
    fp.write('};\n\n')
    fp.write('const FP  tinib_task[TASK_NUM] = {\n')
    for id,task in enumerate(task_list):
        fp.write('\tTASKNAME(%s),\n'%(GAGet(task,'Name')))
    fp.write('};\n\n')
    for id,task in enumerate(task_list):
        fp.write('static UINT8  %s_stk[ %s ];\n'%(GAGet(task,'Name'),GAGet(task,'StackSize')))
    fp.write('const VP  tinib_stk[TASK_NUM] = {\n')
    for id,task in enumerate(task_list):
        fp.write('\t%s_stk,\n'%(GAGet(task,'Name')))
    fp.write('};\n\n')
    fp.write('const UINT16  tinib_stksz[TASK_NUM] = {\n')
    for id,task in enumerate(task_list):
        fp.write('\t%s,/* %s */\n'%(GAGet(task,'StackSize'),GAGet(task,'Name')))
    fp.write('};\n\n')
    
    fp.write('const IPL       ipl_maxisr2 = 1;\n')
    fp.write('/*\n')
    fp.write(' *  os_cfg.c\n')
    fp.write(' *\n')
    fp.write(' *  used to manage tasks < tasks queue, state, proority, activate count >\n')
    fp.write(' */\n')
    fp.write('TaskType        tcb_next[TASK_NUM];         /* task linker,indicate the next task in the queue */\n')
    fp.write('UINT8           tcb_tstat[TASK_NUM];        /* task state */\n')
    fp.write('Priority        tcb_curpri[TASK_NUM];       /* task current priority */\n')
    fp.write('UINT8           tcb_actcnt[TASK_NUM];       /* task current activate count */\n')
    fp.write('EventMaskType   tcb_curevt[TASK_NUM];       /* task current event has been set */\n')
    fp.write('EventMaskType   tcb_waievt[TASK_NUM];       /* task wait event */\n')
    fp.write('ResourceType    tcb_lastres[TASK_NUM];      /* task acquired resource recently */\n')
    fp.write('/*\n')
    fp.write(' *  number of ALARM and Counter\n')
    fp.write(' */\n')
    fp.write('const UINT8     tnum_counter = COUNTER_NUM;                /* Counter number configured */\n')
    fp.write('const UINT8     tnum_alarm = ALARM_NUM;          /* Alarm number configured */\n')
    fp.write('/*\n')
    fp.write(' *  configured information for counter\n')
    fp.write(' */\n')
    counter_list = ScanFrom(os_list,'Counter')
    fp.write('const TickType  cntinib_maxval[COUNTER_NUM] = {\n')
    for id,counter in enumerate(counter_list):
        fp.write('\t%s,/* %s */\n'%(GAGet(counter,'MaxAllowed'),GAGet(counter,'Name')))
    fp.write('};\n\n')
    fp.write('const TickType  cntinib_maxval2[COUNTER_NUM] = {\n')
    for id,counter in enumerate(counter_list):
        fp.write('\t%s*2+1,/* %s */\n'%(GAGet(counter,'MaxAllowed'),GAGet(counter,'Name')))
    fp.write('};\n\n')
    fp.write('const TickType  cntinib_mincyc[COUNTER_NUM] = {\n')
    for id,counter in enumerate(counter_list):
        fp.write('\t%s,/* %s */\n'%(GAGet(counter,'MinCycle'),GAGet(counter,'Name')))
    fp.write('};\n\n')
    fp.write('const TickType  cntinib_tickbase[COUNTER_NUM] = {\n')
    for id,counter in enumerate(counter_list):
        fp.write('\t%s,/* %s */\n'%(GAGet(counter,'TicksPerBase'),GAGet(counter,'Name')))
    fp.write('};\n\n')
    fp.write('/*\n')
    fp.write(' *  counter control block\n')
    fp.write(' */\n')
    fp.write('TickType            cntcb_curval[COUNTER_NUM];      /* counter current value*/\n')
    fp.write('AlarmType           cntcb_almque[COUNTER_NUM];      /* counter queue */\n')
    fp.write('/*\n')
    fp.write(' *  configured information for alarm\n')
    fp.write(' */\n')
    alarm_list = ScanFrom(os_list,'Alarm')
    fp.write('const CounterType alminib_cntid[ALARM_NUM] = {\n')
    for id,alarm in enumerate(alarm_list):
        fp.write('\tCOUNTER_ID_%s, /* %s */\n'%(GAGet(alarm,'Counter'),GAGet(alarm,'Name')))
    fp.write('};\n\n')
    fp.write('const FP             alminib_cback[ALARM_NUM] = {\n')
    for id,alarm in enumerate(alarm_list):
        fp.write('\tALARMCALLBACKNAME(%s),\n'%(GAGet(alarm,'Name')))
    fp.write('};\n\n')
    fp.write('const AppModeType alminib_autosta[ALARM_NUM] = {\n')
    for id,alarm in enumerate(alarm_list):
        if(GAGet(alarm,'Autostart').upper()=='TRUE'):
            fp.write('\t%s, /* %s */\n'%('OSDEFAULTAPPMODE',GAGet(alarm,'Name')))
        else:
            fp.write('\t0, /* %s */\n'%(GAGet(alarm,'Name')))
    fp.write('};\n\n')
    fp.write('const TickType   alminib_almval[ALARM_NUM] = {\n')
    for id,alarm in enumerate(alarm_list):
        fp.write('\t%s, /* %s */\n'%(GAGet(alarm,'StartTime'),GAGet(alarm,'Name')))
    fp.write('};\n\n')
    fp.write('const TickType   alminib_cycle[ALARM_NUM] = {\n')
    for id,alarm in enumerate(alarm_list):
        fp.write('\t%s, /* %s */\n'%(GAGet(alarm,'Period'),GAGet(alarm,'Name')))
    fp.write('};\n\n')
    fp.write('/*\n')
    fp.write(' *  alarm control block\n')
    fp.write(' */\n')
    fp.write('AlarmType       almcb_next[ALARM_NUM];      /* next alarm in queue */\n')
    fp.write('AlarmType       almcb_prev[ALARM_NUM];      /* previous alarm in queue */\n')
    fp.write('TickType        almcb_almval[ALARM_NUM];    /* expire time */\n')
    fp.write('TickType        almcb_cycle[ALARM_NUM];     /* alarm cycle time */\n')
    fp.write('\n')
    fp.write('const UINT8     tnum_resource = 1;\n')
    fp.write('const Priority  resinib_ceilpri[1] =\n')
    fp.write('{\n')
    fp.write('    15,\n')
    fp.write('};\n')
    fp.write('/*\n')
    fp.write(' *  resource control block\n')
    fp.write(' *\n')
    fp.write(' */\n')
    fp.write('Priority            rescb_prevpri[1];    /* previous priority of task which has acquired this res */\n')
    fp.write('ResourceType        rescb_prevres[1];\n')
    fp.write('\n')
    fp.write('const UINT8     tnum_isr2 = 0;\n')
    fp.write('const Priority  isrinib_intpri[] =\n')
    fp.write('{\n')
    fp.write('    0\n')
    fp.write('};\n')
    fp.write('ResourceType        isrcb_lastres[1];\n\n')
    isr_num = len(isr_list)
    for isr in isr_list:
        if((int(isr.attrib['Vector'],10)+1)>isr_num):
            isr_num = int(isr.attrib['Vector'],10)+1
    if(isr_num > 0):
        fp.write('const FP tisr_pc[ %s ] = {\n'%(isr_num))
        for iid in range(isr_num):
            iname = 'NULL'
            for isr in isr_list:
                if(iid == int(isr.attrib['Vector'])):
                    iname = isr.attrib['Name']
                    break
            fp.write('\t%s, /* %s */\n'%(iname,iid))
        fp.write('};\n\n')
    fp.write('/* ============================ [ LOCALS    ] ====================================================== */\n')
    fp.write('/* ============================ [ FUNCTIONS ] ====================================================== */\n')
    fp.write('void object_initialize(void)\n')
    fp.write('{\n')
    fp.write('    task_initialize();\n')
    fp.write('    alarm_initialize();\n')
    fp.write('    resource_initialize();\n')
    fp.write('}\n')
    fp.close()
    
def gen_toppers_osek(gendir,os_list):
    genForToppersOSEK_H(gendir,os_list)
    genForToppersOSEK_C(gendir,os_list)