"""/* Copyright(C) 2013, OpenSAR by Fan Wang(parai). All rights reserved.
 *
 * This file is part of OpenSAR.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Email: parai@foxmail.com
 * Source Open At: https://github.com/parai/OpenSAR/
 */
"""
import sys,os
from .GCF import *
from .util import *

__all__ = ['GenOS','gen_askar']

def GenOS(root,dir):
    global __dir
    GLInit(root)
    if(len(GLGet('TaskList')) == 0):return
    os_list = []
    for lst in root:
        for obj in lst:
            os_list.append(obj)
        if(lst.tag == 'General'):
            os_list.append(lst)
    gen_askar(dir,os_list)
    print('    >>> Gen OS DONE <<<')

def fixupRes(prefix,os_list):
    task_list = ScanFrom(os_list,'Task')
    for res in ScanFrom(os_list,'%sResource'%(prefix)):
        prio = 0;
        for tsk in task_list:
            for res2 in GLGet(tsk, 'ResourceList'):
                if(GAGet(res,'Name') == GAGet(res2,'Name')):
                    GASet(res2,'Type',prefix)
                    if(prio<Integer(GAGet(tsk,'Priority'))):
                       prio=Integer(GAGet(tsk,'Priority'))
        GASet(res,'Priority',str(prio))

def fixupEvt(os_list):
    evList=ScanFrom(os_list,'Event')
    for tsk in ScanFrom(os_list,'Task'):
        masks=[]
        for ev in GLGet(tsk, 'EventList'):
            for ev2 in evList:
                if(GAGet(ev,'Name')==GAGet(ev,'Name')):
                    GASet(ev,'Mask',GAGet(ev2,'Mask'))
                    if(GAGet(ev,'Mask').upper()!='AUTO'):
                        masks.append(Integer(GAGet(ev,'Mask')))
        for ev in GLGet(tsk, 'EventList'):
            if(GAGet(ev,'Mask').upper()=='AUTO'):
                for id in range(0,32):
                    mask = 1<<id
                    try:
                        masks.index(mask)
                    except ValueError:
                        masks.append(mask)
                        GASet(ev,'Mask',hex(mask))
                        break
def fixup(os_list):
    fixupRes('', os_list)
    fixupRes('Internal', os_list)
    fixupEvt(os_list)

def GenH(gendir,os_list):
    fixup(os_list)
    fp = open('%s/Os_Cfg.h'%(gendir),'w')
    fp.write(GHeader('Os',Vendor='askar'))
    fp.write('#ifndef OS_CFG_H_\n#define OS_CFG_H_\n\n')
    fp.write('/* ============================ [ INCLUDES  ] ====================================================== */\n')
    fp.write('#ifndef MACROS_ONLY\n')
    fp.write('#include "kernel.h"\n')
    fp.write('#endif\n')
    fp.write('/* ============================ [ MACROS    ] ====================================================== */\n')
    fp.write('#define __ASKAR_OS__\n\n')
    general = ScanFrom(os_list,'General')[0]
    try:
        if(GAGet(general,'ErrorHook') != 'NULL' and GAGet(general,'ErrorHook') != 'FALSE'):
            fp.write('#define OS_USE_ERROR_HOOK\n')
    except KeyError:
        fp.write('#define OS_USE_ERROR_HOOK\n')
    try:
        if(GAGet(general,'StartupHook') != 'NULL' and GAGet(general,'StartupHook') != 'FALSE'):
            fp.write('#define OS_USE_STARTUP_HOOK\n')
    except KeyError:
        fp.write('#define OS_USE_STARTUP_HOOK\n')
    try:
        if(GAGet(general,'ShutdownHook') != 'NULL' and GAGet(general,'ShutdownHook') != 'FALSE'):
            fp.write('#define OS_USE_SHUTDOWN_HOOK\n')
    except KeyError:
        fp.write('#define OS_USE_SHUTDOWN_HOOK\n')
    try:
        if(GAGet(general,'PreTaskHook') != 'NULL' and GAGet(general,'PreTaskHook') != 'FALSE'):
            fp.write('#define OS_USE_PRETASK_HOOK\n')
    except KeyError:
        fp.write('#define OS_USE_PRETASK_HOOK\n')
    try:
        if(GAGet(general,'PostTaskHook') != 'NULL' and GAGet(general,'PostTaskHook') != 'FALSE'):
            fp.write('#define OS_USE_POSTTASK_HOOK\n')
    except KeyError:
        fp.write('#define OS_USE_POSTTASK_HOOK\n')
    try:
        fp.write('#ifndef USE_PTHREAD\n')
        fp.write('#define OS_PTHREAD_NUM 0\n')
        fp.write('#define OS_PTHREAD_PRIORITY 0\n')
        fp.write('#endif\n')
        fp.write('#ifndef OS_PTHREAD_NUM\n#define OS_PTHREAD_NUM %s\n#endif\n'%(GAGet(general,'PTHREAD')))
        fp.write('#ifndef OS_PTHREAD_PRIORITY\n#define OS_PTHREAD_PRIORITY %s\n#endif\n'%(GAGet(general,'PTHREAD_PRIORITY')))
    except KeyError:
        fp.write('#ifndef OS_PTHREAD_NUM\n#define OS_PTHREAD_NUM 0\n#endif\n')
        fp.write('#ifndef OS_PTHREAD_PRIORITY\n#define OS_PTHREAD_PRIORITY 0\n#endif\n')
    fp.write('#define OS_STATUS %s\n'%(GAGet(general,'Status')))
    fp.write('\n\n')
    task_list = ScanFrom(os_list,'Task')
    maxPrio = 0
    multiPrio = False
    multiAct  = False
    sumAct = 0
    prioList=[]
    prioAct={}
    maxPrioAct=0
    for id,task in enumerate(task_list):
        prio = Integer(GAGet(task,'Priority'))
        act  = Integer(GAGet(task,'Activation'))
        sumAct += act
        try:
            prioAct[prio] += act
        except KeyError:
            prioAct[prio] = act
        if(Integer(GAGet(task,'Activation')) > 1):
            multiAct = True;
        try:
            prioList.index(prio)
            multiPrio = True
        except ValueError:
            prioList.append(prio)
        if(prio > maxPrio):
            maxPrio = prio
    for prio,act in prioAct.items():
        if(maxPrioAct<act):
            maxPrioAct=act
    maxPrioAct+=1 # in case resource ceiling
    seqMask=0
    seqShift=0
    for i in range(1,maxPrioAct+1):
        seqMask|=i
    for i in range(0,32):
        if((seqMask>>i)==0):
            seqShift=i
            break
    fp.write('#define PRIORITY_NUM (OS_PTHREAD_PRIORITY+%s)\n'%(maxPrio))
    fp.write('#define ACTIVATION_SUM (%s+OS_PTHREAD_NUM)\n'%(sumAct+1))
    if(multiPrio):
        fp.write('#define MULTIPLY_TASK_PER_PRIORITY\n')
        fp.write('#define SEQUENCE_MASK 0x%Xu\n'%(seqMask))
        fp.write('#define SEQUENCE_SHIFT %d\n'%(seqShift))
    if(multiAct):
        fp.write('#define MULTIPLY_TASK_ACTIVATION\n')
    fp.write('\n\n')
    for id,task in enumerate(task_list):
        fp.write('#define TASK_ID_%-32s %-3s /* priority = %s */\n'%(GAGet(task,'Name'),id,GAGet(task,'Priority')))
    fp.write('#define TASK_NUM%-32s %s\n\n'%(' ',id+1))
    alarm_list = ScanFrom(os_list,'Alarm')
    appmode = []
    for id,obj in enumerate(task_list+alarm_list):
        for mode in GLGet(obj,'ApplicationModeList'):
            if(GAGet(mode,'Name') != 'OSDEFAULTAPPMODE'):
                try:
                    appmode.index(GAGet(mode,'Name'))
                except ValueError:
                    appmode.append(GAGet(mode,'Name'))
    for id,mode in enumerate(appmode):
        fp.write('#define %s ((AppModeType)(1<<%s))\n'%(mode, id+1))

    withEvt = False
    for id,task in enumerate(task_list):
        for mask,ev in enumerate(GLGet(task,'EventList')):
            withEvt = True
            mask = GAGet(ev,'Mask')
            fp.write('#define EVENT_MASK_%-40s %s\n'%('%s_%s'%(GAGet(task,'Name'),GAGet(ev,'Name')),mask))
    fp.write('\n')
    if(withEvt):
        fp.write('\n#define EXTENDED_TASK\n\n')

    res_list = ScanFrom(os_list, 'Resource')
    for id,res in enumerate(res_list):
        if(GAGet(res,'Name') == 'RES_SCHEDULER'):continue
        fp.write('#define RES_ID_%-32s %s\n'%(GAGet(res,'Name'),id+1))
    fp.write('#define RESOURCE_NUM %s\n\n'%(len(res_list)+1))
    id = -1
    counter_list = ScanFrom(os_list,'Counter')
    for id,counter in enumerate(counter_list):
        fp.write('#define COUNTER_ID_%-32s %s\n'%(GAGet(counter,'Name'),id))
    fp.write('#define COUNTER_NUM%-32s %s\n\n'%(' ',id+1))
    id = -1
    for id,alarm in enumerate(alarm_list):
        fp.write('#define ALARM_ID_%-32s %s\n'%(GAGet(alarm,'Name'),id))
    fp.write('#define ALARM_NUM%-32s %s\n\n'%(' ',id+1))
    isr_list = ScanFrom(os_list,'ISR')
    isr_num = len(isr_list)
    for isr in isr_list:
        if((int(isr.attrib['Vector'],10)+1)>isr_num):
            isr_num = int(isr.attrib['Vector'],10)+1
    fp.write('#define ISR_NUM  %s\n\n'%(isr_num))
    fp.write('\n\n')
    fp.write('/* ============================ [ TYPES     ] ====================================================== */\n')
    fp.write('/* ============================ [ DECLARES  ] ====================================================== */\n')
    fp.write('/* ============================ [ DATAS     ] ====================================================== */\n')
    fp.write('#ifndef MACROS_ONLY\n')
    for id,task in enumerate(task_list):
        fp.write('DeclareTask(%s);\n'%(GAGet(task,'Name')))
    fp.write('\n')
    for id,task in enumerate(task_list):
        for mask,ev in enumerate(GLGet(task,'EventList')):
            fp.write('DeclareEvent(%s);\n'%(GAGet(ev,'Name')))
    fp.write('\n')
    for id,res in enumerate(res_list):
        if(GAGet(res,'Name') == 'RES_SCHEDULER'):continue
        fp.write('DeclareResource(%s);\n'%(GAGet(res,'Name')))
    fp.write('\n')
    for id,counter in enumerate(counter_list):
        fp.write('DeclareCounter(%s);\n'%(GAGet(counter,'Name')))
    fp.write('\n')
    for id,alarm in enumerate(alarm_list):
        fp.write('DeclareAlarm(%s);\n'%(GAGet(alarm,'Name')))
    fp.write('#endif\n')
    fp.write('/* ============================ [ LOCALS    ] ====================================================== */\n')
    fp.write('/* ============================ [ FUNCTIONS ] ====================================================== */\n')
    fp.write('#ifndef MACROS_ONLY\n')
    for id,task in enumerate(task_list):
        fp.write('extern TASK(%s);\n'%(GAGet(task,'Name')))
    fp.write('\n\n')
    for id,alarm in enumerate(alarm_list):
        fp.write('extern ALARM(%s);\n'%(GAGet(alarm,'Name')))
    fp.write('\n\n')
    fp.write('#endif\n')
    fp.write('#endif /*OS_CFG_H_*/\n\n')
    fp.close()
    
def GenC(gendir,os_list):
    fp = open('%s/Os_Cfg.c'%(gendir),'w')
    fp.write(GHeader('Os',Vendor='askar'))
    fp.write('/* ============================ [ INCLUDES  ] ====================================================== */\n')
    fp.write('#include "kernel_internal.h"\n')
    fp.write('/* ============================ [ MACROS    ] ====================================================== */\n')
    fp.write('#ifndef OS_STK_SIZE_SCALER\n#define OS_STK_SIZE_SCALER 1\n#endif\n')
    fp.write('/* ============================ [ TYPES     ] ====================================================== */\n')
    fp.write('/* ============================ [ DECLARES  ] ====================================================== */\n')
    isr_list = ScanFrom(os_list,'ISR')
    for isr in isr_list:
        fp.write('extern void %s (void);\n'%(isr.attrib['Name']))
    fp.write('/* ============================ [ DATAS     ] ====================================================== */\n')
    general = ScanFrom(os_list,'General')[0]
    try:
        pthnum = Integer(GAGet(general,'PTHREAD'))
        pthprio = Integer(GAGet(general,'PTHREAD_PRIORITY'))
    except KeyError:
        pthnum = 0
        pthprio = 0
    task_list = ScanFrom(os_list,'Task')
    for id,task in enumerate(task_list):
        fp.write('static uint32_t %s_Stack[(%s*OS_STK_SIZE_SCALER+sizeof(uint32_t)-1)/sizeof(uint32_t)];\n'%(GAGet(task,'Name'),GAGet(task,'StackSize')))
        if(len(GLGet(task,'EventList')) > 0):
            fp.write('static EventVarType %s_EventVar;\n'%(GAGet(task,'Name')))
    fp.write('#if (OS_STATUS == EXTENDED)\n')
    inres_list = ScanFrom(os_list,'InternalResource')
    for id,task in enumerate(task_list):
        cstr = ''
        for res in GLGet(task,'ResourceList'):
            skip = False
            for ires in inres_list:
                if(GAGet(res,'Name')==GAGet(ires,'Name')):
                    skip = True
            if(not skip): cstr += '\t\tcase RES_ID_%s:\n'%(GAGet(res,'Name'))
        fp.write('''static boolean %s_CheckAccess(ResourceType ResID)
{
    boolean bAccess = FALSE;

    switch(ResID)
    {
        case RES_SCHEDULER:
%s            bAccess = TRUE;
        break;
        default:
            break;
    }

    return bAccess;
}\n'''%(GAGet(task,'Name'),cstr))
    fp.write('#endif\n')
    fp.write('const TaskConstType TaskConstArray[TASK_NUM] =\n{\n')
    for id,task in enumerate(task_list):
        runPrio = GAGet(task,'Priority')
        if(GAGet(task,'Schedule')=='NON'):
            runPrio = 'PRIORITY_NUM'
        else:
            # generall task should has at most one internal resource
            for res in GLGet(task,'ResourceList'):
                for ires in inres_list:
                    if(GAGet(res,'Name')==GAGet(ires,'Name')):
                        if(Integer(GAGet(ires,'Priority')) > Integer(runPrio)):
                            runPrio = GAGet(res,'Priority')
        # for IDLE task, priority is 0.
        if(GAGet(task,'Name')=='TaskIdle'):
            runPrio = '(-OS_PTHREAD_PRIORITY)'
        maxAct = Integer(GAGet(task,'Activation'))
        event  = 'NULL'
        if(len(GLGet(task,'EventList')) > 0):
            if(maxAct > 1):
                raise Exception('Task<%s>: multiple requesting of task activation allowed for basic tasks'%(GAGet(task,'Name')))
            maxAct = 1
            event = '&%s_EventVar'%(GAGet(task,'Name'))
        def AST(task):
            if(GAGet(task,'Autostart').upper() == 'TRUE'):
                cstr = '(0'
                for appmode in GLGet(task, 'ApplicationModeList'):
                    cstr += ' | (%s)'%(GAGet(appmode,'Name'))
                cstr += ')'
                return cstr
            return 0
        fp.write('\t{\n')
        fp.write('\t\t/*.pStack =*/ %s_Stack,\n'%(GAGet(task,'Name')))
        fp.write('\t\t/*.stackSize =*/ sizeof(%s_Stack),\n'%(GAGet(task,'Name')))
        fp.write('\t\t/*.entry =*/ TaskMain%s,\n'%(GAGet(task,'Name')))
        fp.write('\t\t#ifdef EXTENDED_TASK\n')
        fp.write('\t\t/*.pEventVar =*/ %s,\n'%(event))
        fp.write('\t\t#endif\n')
        fp.write('\t\t/*.appModeMask =*/ %s,\n'%(AST(task)))
        fp.write('\t\t#if (OS_STATUS == EXTENDED)\n')
        fp.write('\t\t/*.CheckAccess =*/ %s_CheckAccess,\n'%(GAGet(task,'Name')))
        fp.write('\t\t#endif\n')
        fp.write('\t\t/*.name =*/ "%s",\n'%(GAGet(task,'Name')))
        fp.write('\t\t/*.initPriority =*/ OS_PTHREAD_PRIORITY + %s,\n'%(GAGet(task,'Priority')))
        fp.write('\t\t/*.runPriority =*/ OS_PTHREAD_PRIORITY + %s,\n'%(runPrio))
        fp.write('\t\t#ifdef MULTIPLY_TASK_ACTIVATION\n')
        fp.write('\t\t/*.maxActivation =*/ %s,\n'%(maxAct))
        fp.write('\t\t#endif\n')
        fp.write('\t},\n')
    fp.write('};\n\n')
    fp.write('const ResourceConstType ResourceConstArray[RESOURCE_NUM] =\n{\n')
    fp.write('\t{\n')
    fp.write('\t\t/*.ceilPrio =*/ PRIORITY_NUM, /* RES_SCHEDULER */\n')
    fp.write('\t},\n')
    res_list = ScanFrom(os_list, 'Resource')
    for id,res in enumerate(res_list):
        if(GAGet(res,'Name') == 'RES_SCHEDULER'):continue
        fp.write('\t{\n')
        fp.write('\t\t/*.ceilPrio =*/ OS_PTHREAD_PRIORITY + %s, /* %s */\n'%(GAGet(res,'Priority'),GAGet(res,'Name')))
        fp.write('\t},\n')
    fp.write('};\n\n')
    counter_list = ScanFrom(os_list,'Counter')
    if(len(counter_list) > 0):
        fp.write('CounterVarType CounterVarArray[COUNTER_NUM];\n')
        fp.write('const CounterConstType CounterConstArray[COUNTER_NUM] =\n{\n')
        for id,counter in enumerate(counter_list):
            fp.write('\t{\n')
            fp.write('\t\t/*.name=*/"%s",\n'%(GAGet(counter,'Name')))
            fp.write('\t\t/*.pVar=*/&CounterVarArray[COUNTER_ID_%s],\n'%(GAGet(counter,'Name')))
            fp.write('\t\t/*.base=*/{\n\t\t\t/*.maxallowedvalue=*/%s,\n'%(GAGet(counter,'MaxAllowed')))
            fp.write('\t\t\t/*.ticksperbase=*/%s,\n'%(GAGet(counter,'TicksPerBase')))
            fp.write('\t\t\t/*.mincycle=*/%s\n\t\t}\n'%(GAGet(counter,'MinCycle')))
            fp.write('\t},\n')
        fp.write('};\n\n')
    alarm_list = ScanFrom(os_list,'Alarm')
    if(len(alarm_list) > 0):
        for id,alarm in enumerate(alarm_list):
            fp.write('static void %s_Action(void)\n{\n'%(GAGet(alarm,'Name')))
            if(GAGet(alarm,'Action').upper() == 'ACTIVATETASK'):
                fp.write('\t(void)ActivateTask(TASK_ID_%s);\n'%(GAGet(alarm,'Task')))
            elif(GAGet(alarm,'Action').upper() == 'SETEVENT'):
                fp.write('\t(void)SetEvent(TASK_ID_%s,EVENT_MASK_%s_%s);\n'%(GAGet(alarm,'Task'),GAGet(alarm,'Task'),GAGet(alarm,'Event')))
            elif(GAGet(alarm,'Action').upper() == 'CALLBACK'):
                fp.write('\textern ALARM(%s);\n\tAlarmMain%s();\n'%(GAGet(alarm,'Callback'),GAGet(alarm,'Callback')))
            elif(GAGet(alarm,'Action').upper() == 'SIGNALCOUNTER'):
                fp.write('\t(void)SignalCounter(COUNTER_ID_%s);\n'%(GAGet(alarm,'Counter')))
            else:
                assert(0)
            fp.write('}\n')
        fp.write('AlarmVarType AlarmVarArray[ALARM_NUM];\n')
        fp.write('const AlarmConstType AlarmConstArray[ALARM_NUM] =\n{\n')
        for id,alarm in enumerate(alarm_list):
            def AST(alarm):
                if(GAGet(alarm,'Autostart').upper() != 'FALSE'):
                    cstr = '(0'
                    for appmode in GLGet(alarm, 'ApplicationModeList'):
                        cstr += ' | (%s)'%(GAGet(appmode,'Name'))
                    cstr += ')'
                    return cstr,GAGet(alarm,'StartTime'),GAGet(alarm,'Period')
                return 0,0,0
            fp.write('\t{\n')
            fp.write('\t\t/*.name=*/"%s",\n'%(GAGet(alarm,'Name')))
            fp.write('\t\t/*.pVar=*/&AlarmVarArray[ALARM_ID_%s],\n'%(GAGet(alarm,'Name')))
            fp.write('\t\t/*.pCounter=*/&CounterConstArray[COUNTER_ID_%s],\n'%(GAGet(alarm,'Counter')))
            fp.write('\t\t/*.Action=*/%s_Action,\n'%(GAGet(alarm,'Name')))
            appmode,start,period=AST(alarm)
            fp.write('\t\t/*.appModeMask=*/%s,\n'%(appmode))
            fp.write('\t\t/*.start=*/%s,\n'%(start))
            fp.write('\t\t/*.period=*/%s,\n'%(period))
            fp.write('\t},\n')
        fp.write('};\n\n')

    for id,task in enumerate(task_list):
        fp.write('const TaskType %s = TASK_ID_%s;\n'%(GAGet(task,'Name'),GAGet(task,'Name')))
    fp.write('\n')
    evList=[]
    for id,task in enumerate(task_list):
        for mask,ev in enumerate(GLGet(task,'EventList')):
            try:
                evList.index(GAGet(ev,'Name'))
                print('WARNING: %s for %s is with the same name with others'%(GAGet(ev,'Name'),GAGet(task,'Name')))
            except ValueError:
                evList.append(GAGet(ev,'Name'))
                fp.write('const EventMaskType %s = EVENT_MASK_%s_%s;\n'%(GAGet(ev,'Name'),GAGet(task,'Name'),GAGet(ev,'Name')))
    fp.write('\n')
    for id,res in enumerate(res_list):
        if(GAGet(res,'Name') == 'RES_SCHEDULER'):continue
        fp.write('const ResourceType %s = RES_ID_%s;\n'%(GAGet(res,'Name'),GAGet(res,'Name')))
    fp.write('\n')
    for id,counter in enumerate(counter_list):
        fp.write('const CounterType %s = COUNTER_ID_%s;\n'%(GAGet(counter,'Name'),GAGet(counter,'Name')))
    fp.write('\n')
    for id,alarm in enumerate(alarm_list):
        fp.write('const AlarmType %s = ALARM_ID_%s;\n'%(GAGet(alarm,'Name'),GAGet(alarm,'Name')))

    maxPrio = 0
    for id,task in enumerate(task_list):
        prio = Integer(GAGet(task,'Priority'))
        if(prio > maxPrio):
            maxPrio = prio
    fp.write('#ifdef USE_SCHED_FIFO\n')
    fp.write('#ifdef USE_PTHREAD\n')
    cstr = '\nconst ReadyFIFOType ReadyFIFO[OS_PTHREAD_PRIORITY+PRIORITY_NUM+1]=\n{\n'
    cstr += '#ifdef USE_PTHREAD\n'
    for prio in range(pthprio):
        sumact = pthnum
        fp.write('static TaskType ReadyFIFO_pthread_prio%s[%s];\n'%(prio,sumact))
        cstr += '\t{\n\t\t/*.max=*/%s,\n\t\t/*.pFIFO=*/ReadyFIFO_pthread_prio%s\n\t},\n'%(sumact, prio)
    cstr += '#endif\n'
    fp.write('#endif\n')
    for prio in range(maxPrio+1):
        sumact = 3+2 # 2 for the ceiling of resource and one more additional slow
        comments = ''
        for id,task in enumerate(task_list):
            prio2 = Integer(GAGet(task,'Priority'))
            if(prio2 == prio):
                sumact+= Integer(GAGet(task,'Activation'))
                comments += '%s(Activation=%s),'%(GAGet(task,'Name'),GAGet(task,'Activation'))
        if(sumact > 5):
            fp.write('static TaskType ReadyFIFO_prio%s[%s];\n'%(prio,sumact))
            cstr += '\t{\n\t\t/*.max=*/%s,/* %s */\n\t\t/*.pFIFO=*/ReadyFIFO_prio%s\n\t},\n'%(sumact,comments, prio)
        else:
            cstr += '\t{\n\t\t/*.max=*/0,\n\t\t/*.pFIFO=*/NULL\n\t},\n'
    cstr += '};\n\n'
    fp.write(cstr)
    fp.write('#endif\n')
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
    
    fp.close()

def gen_askar(gendir,os_list):
    GenH(gendir,os_list)
    GenC(gendir,os_list)
