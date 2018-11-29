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

import sys,os
from .util import *
from .gen_freeosek import *
from .gen_toppers_osek import *
from .gen_tinyos import *
from .gen_freertos import *
from .gen_toppers_atk2_sc4 import *
from .gen_contiki import *
from .gen_ucosii import *
from .gen_trampoline import *
from .GenOS import *
import glob

__all__ = ['OsGen','SetOS']

defaultOS=None

def SetOS(name):
    global defaultOS
    defaultOS=name

def gen_osal(gendir,os_list):
    gen_ucosii(gendir,os_list)
    os_ref = getOsRef(os_list)
    os.system('sed -i "23c #define __%s_OS__" %s/Os_Cfg.h'%(os_ref.upper(),gendir))
    if(os_ref == 'rtthread'):
        os.system('sed -i "16c #include <rtthread.h>" %s/Os_Cfg.c'%(gendir))
        fp = open('%s/Os_Cfg.c'%(gendir),'a')
        fp.write('''void tpl_call_counter_tick(void)
{
  OsTick();
  rt_tick_increase();
}\n\n''')
    else:
        os.system('sed -i "16c /* COMMON OSAL */" %s/Os_Cfg.c'%(gendir))
    
__osgen__ = {'freeosek':gen_freeosek,
             'toppers_osek':gen_toppers_osek,
             'tinyos':gen_tinyos,
             'freertos':gen_freertos,
             'atk2-sc4':gen_toppers_atk2_sc4,
             'contiki':gen_contiki,
             'posix':gen_toppers_osek,
             'ucosii':gen_ucosii,
             'trampoline':gen_trampoline,
             'rtthread':gen_osal,
             'tinix':gen_osal,
             'askar':gen_askar,
             'anyos':gen_osal,
            }

def getOsRef(os_list):
    if(defaultOS is not None):
        return defaultOS
    for each in os_list:
        if(each.tag == 'OsRef'):
            return each.attrib['name']
    # default os
    return 'askar'
    
def OsGen(gendir):
    os_list = ScanXML(gendir,'Os')
    if(len(ScanFrom(os_list,'General')) == 0):return
    os_ref = getOsRef(os_list)
    gen = __osgen__[os_ref]
    gen(gendir,os_list)
