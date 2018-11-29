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

__types = '''
typedef uint8 KSMState_Type;
typedef void (*KsmFunction_Type) (void);
typedef struct
{
    KSMState_Type KsLimit;
    const KsmFunction_Type* Ksm;
}KSM_Type;    /* Kernel State Machine */
'''
import sys,os
from .util import *

__all__ = ['KsmGen']

def KsmGen(gendir):
    ksm_list = ScanXML(gendir,'KSM')
    fp = open('%s/ksm_cfg.h'%(gendir),'w')
    fp.write(__header)
    fp.write('#ifndef KSM_CFG_H\n#define KSM_CFG_H\n\n')
    fp.write('/* ============================ [ INCLUDES  ] ====================================================== */\n')
    fp.write('#include "Os.h"\n')
    fp.write('/* ============================ [ MACROS    ] ====================================================== */\n')
    for id,ksm in enumerate(ksm_list):
        fp.write('#define KSM_ID_%-32s %s\n'%(ksm.tag,id))
    fp.write('#define KSM_%-35s %s\n\n'%('NUM',len(ksm_list)))
    for id,ksm in enumerate(ksm_list):
        fp.write('#define KSM_%-32s %s\n'%('%s_%s'%(ksm.tag,'Init'),0))
        fp.write('#define KSM_%-32s %s\n'%('%s_%s'%(ksm.tag,'Start'),1))
        fp.write('#define KSM_%-32s %s\n'%('%s_%s'%(ksm.tag,'Stop'),2))
        for sid,state in enumerate(ksm):
            fp.write('#define KSM_%-32s %s\n'%('%s_%s'%(ksm.tag,state.tag),sid+3))
        fp.write('#define KSM_%-32s %s\n\n'%('%s_%s'%(ksm.tag,'STATE_LIMIT'),len(ksm)+3))   
    fp.write('/* ============================ [ TYPES     ] ====================================================== */\n')
    fp.write(__types)
    fp.write('/* ============================ [ DECLARES  ] ====================================================== */\n')
    if(len(ksm_list)>0):
        fp.write('extern const KSM_Type KSM_Config[KSM_NUM];\n')
    fp.write('/* ============================ [ DATAS     ] ====================================================== */\n')
    fp.write('/* ============================ [ LOCALS    ] ====================================================== */\n')
    fp.write('/* ============================ [ FUNCTIONS ] ====================================================== */\n')  
    fp.write('#endif\n\n')
    
    if(len(ksm_list)==0):
        return
    fp = open('%s/ksm_cfg.c'%(gendir),'w')
    fp.write(__header)
    fp.write('/* ============================ [ INCLUDES  ] ====================================================== */\n')
    fp.write('#include "Os.h"\n')
    fp.write('/* ============================ [ MACROS    ] ====================================================== */\n')
    fp.write('/* ============================ [ TYPES     ] ====================================================== */\n')
    fp.write('/* ============================ [ DECLARES  ] ====================================================== */\n')
    for id,ksm in enumerate(ksm_list):
        fp.write('extern void Ksm%-32s(void);\n'%('%s_%s'%(ksm.tag,'Init')))
        fp.write('extern void Ksm%-32s(void);\n'%('%s_%s'%(ksm.tag,'Start')))
        fp.write('extern void Ksm%-32s(void);\n'%('%s_%s'%(ksm.tag,'Stop')))
        for sid,state in enumerate(ksm):
            fp.write('extern void Ksm%-32s(void);\n'%('%s_%s'%(ksm.tag,state.tag)))
    fp.write('/* ============================ [ DATAS     ] ====================================================== */\n')
    for id,ksm in enumerate(ksm_list):
        fp.write('static const KsmFunction_Type Ksm%s_FunctionList[%s] = \n{\n'%(ksm.tag,len(ksm)+3))
        fp.write('\tKsm%-32s,\n'%('%s_%s'%(ksm.tag,'Init')))
        fp.write('\tKsm%-32s,\n'%('%s_%s'%(ksm.tag,'Start')))
        fp.write('\tKsm%-32s,\n'%('%s_%s'%(ksm.tag,'Stop')))
        for sid,state in enumerate(ksm):
            fp.write('\tKsm%-32s,\n'%('%s_%s'%(ksm.tag,state.tag)))
        fp.write('};\n')
    fp.write('const KSM_Type KSM_Config[KSM_NUM] = \n{\n')
    for id,ksm in enumerate(ksm_list):
        fp.write('\t{ /* %s */\n'%(ksm.tag))
        fp.write('\t\t%s,\n'%(len(ksm)+3))
        fp.write('\t\tKsm%s_FunctionList\n'%(ksm.tag))
        fp.write('\t},\n')
    fp.write('};\n\n')
    fp.write('/* ============================ [ LOCALS    ] ====================================================== */\n')

    fp.write('/* ============================ [ FUNCTIONS ] ====================================================== */\n')  
   
if(__name__ == '__main__'):
    GenerateKSM(sys.argv[1])