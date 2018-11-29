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

__all__ = ['gen_contiki']

def genForContiki_H(gendir,os_list):
    fp = open('%s/Os_Cfg.h'%(gendir),'w')
    fp.write(__header)
    fp.write('#ifndef OS_CFG_H\n#define OS_CFG_H\n\n')
    fp.write('/* ============================ [ INCLUDES  ] ====================================================== */\n')
    fp.write('#include "Std_Types.h"\n')
    fp.write('#include "contiki.h"\n')
    fp.write('#include "os_i.h"\n')
    fp.write('/* ============================ [ MACROS    ] ====================================================== */\n')
    fp.write('#define __CONTIKI_OS__\n\n')
    fp.write("#define OS_TICKS2MS(a) (a)\n\n")
    fp.write('#define WaitEvent(mask) E_OK; PROCESS_WAIT_EVENT_UNTIL(taskEvcb[task_id_of(process_pt)]&(mask))\n')
    fp.write('#define GetEvent(tskid, pmask) E_OK; *(pmask)=taskEvcb[tskid]\n')
    fp.write('#define SetEvent(tskid, mask) E_OK; taskEvcb[tskid] |= (mask)\n')
    fp.write('#define ClearEvent(mask) E_OK; taskEvcb[task_id_of(process_pt)] &= ~(mask)\n')
    fp.write('#define TerminateTask() PROCESS_EXIT()\n')
    fp.write('#define GetResource(resid) E_OK; PROCESS_WAIT_EVENT_UNTIL(rescb[resid] == 0)\n')
    fp.write('#define ReleaseResource(resid) E_OK; rescb[resid] = 0\n')
    task_list = ScanFrom(os_list,'Task')
    for id,task in enumerate(task_list):
        fp.write('#define TASK_ID_%-32s %-3s /* priority = %s */\n'%(GAGet(task,'Name'),id,GAGet(task,'Priority')))
    fp.write('#define TASK_NUM%-32s %s\n\n'%(' ',id+1))
    for id,task in enumerate(task_list):
        for mask,ev in enumerate(GLGet(task,'EventList')):
            if(GAGet(ev,'Mask')=='auto'):
                mask = '(1<<%s)'%(mask)
            else:
                mask = GAGet(ev,'Mask')
            fp.write('#define EVENT_MASK_%-40s %s\n'%('%s_%s'%(GAGet(task,'Name'),GAGet(ev,'Name')),mask))
    fp.write('\n')
    
    res_list = ScanFrom(os_list, 'Resource')
    for id,res in enumerate(res_list):
        fp.write('#define RES_ID_%-32s %s\n'%(GAGet(res,'Name'),id+1))
    fp.write('#define RES_NUMBER %s\n\n'%(len(res_list)+1))
    
    alarm_list = ScanFrom(os_list,'Alarm')
    for id,alarm in enumerate(alarm_list):
        fp.write('#define ALARM_ID_%-32s %s\n'%(GAGet(alarm,'Name'),id))
    fp.write('#define ALARM_NUM%-32s %s\n\n'%(' ',id+1))
    fp.write('\n\n')
    fp.write('/* ============================ [ TYPES     ] ====================================================== */\n')
    fp.write('/* ============================ [ DECLARES  ] ====================================================== */\n')
    fp.write('extern EventMaskType taskEvcb[TASK_NUM];\n')
    fp.write('extern boolean       rescb[RES_NUMBER];\n')
    fp.write('extern struct process * const TaskList[TASK_NUM];\n')
    fp.write('/* ============================ [ DATAS     ] ====================================================== */\n')
    fp.write('/* ============================ [ LOCALS    ] ====================================================== */\n')
    fp.write('/* ============================ [ FUNCTIONS ] ====================================================== */\n')
    for id,task in enumerate(task_list):
        fp.write('extern TASK(%s);\n'%(GAGet(task,'Name')))
    fp.write('\n\n')
    for id,alarm in enumerate(alarm_list):
        fp.write('extern ALARM(%s);\n'%(GAGet(alarm,'Name')))
    fp.write('\n\n')
    fp.write('TaskType task_id_of(struct pt* process_pt);\n\n')
    fp.write('#endif /* OS_CFG_H */\n\n')
    fp.close()
def genForContiki_C(gendir,os_list):
    fp = open('%s/Os_Cfg.c'%(gendir),'w')
    fp.write(__header)
    fp.write('/* ============================ [ INCLUDES  ] ====================================================== */\n')
    fp.write('#include "Os.h"\n')
    fp.write('#include "asdebug.h"\n')
    fp.write('/* ============================ [ MACROS    ] ====================================================== */\n')
    fp.write('/* ============================ [ TYPES     ] ====================================================== */\n')
    fp.write('/* ============================ [ DECLARES  ] ====================================================== */\n')
    fp.write('/* ============================ [ DATAS     ] ====================================================== */\n')
    task_list = ScanFrom(os_list,'Task')
    cstr=''
    for id,task in enumerate(task_list):
        fp.write('PROCESS(%s,"%s");\n'%(GAGet(task,'Name'),GAGet(task,'Name')))
        cstr += '\t&%s,\n'%(GAGet(task,'Name'))
        if(GAGet(task,'Autostart').upper()=='TRUE'):
            fp.write('PROTO_AUTOSTART_PROCESS_EXPORT(%s);\n'%(GAGet(task,'Name')))
    fp.write('struct process * const TaskList[TASK_NUM] = {\n%s\n};\n'%(cstr[:-2]))
    alarm_list = ScanFrom(os_list,'Alarm')
    fp.write('CONST(alarm_declare_t,AUTOMATIC) AlarmList[ALARM_NUM] = \n{\n')
    for id,alarm in enumerate(alarm_list):
        fp.write('\tDeclareAlarm(%s),\n'%(GAGet(alarm,'Name')))
    fp.write('};\n\n')
    fp.write('EventMaskType taskEvcb[TASK_NUM];\nboolean       rescb[RES_NUMBER];\n')
    fp.write('/* ============================ [ LOCALS    ] ====================================================== */\n')
    fp.write('/* ============================ [ FUNCTIONS ] ====================================================== */\n')
    fp.write('''TaskType task_id_of(struct pt* process_pt)
{
    TaskType id = -1;
    TaskType i;
    for(i=0; i<TASK_NUM; i++)
    {
        if(process_pt == (&(TaskList[i]->pt)))
        {
            id = i;
        }
    }
    asAssert(id != -1);
    return id;
}
\n\n''')
    fp.close()

def gen_contiki(gendir,os_list):
    genForContiki_H(gendir,os_list)
    genForContiki_C(gendir,os_list)
