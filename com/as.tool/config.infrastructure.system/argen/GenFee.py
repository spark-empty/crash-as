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
from .GCF import *

__all__ = ['GenFee']

__dir = '.'

def GenFee(root,dir):
    global __dir
    GLInit(root)
    __dir = '%s'%(dir)
    if(len(GLGet('BlockList')) == 0):return
    GenH()
    GenC()
    print('    >>> Gen Fee DONE <<<')
    
def GenH():
    global __dir
    fp = open('%s/Fee_Cfg.h'%(__dir),'w')
    fp.write(GHeader('Fee'))
    General=GLGet('General')
    BlockList = GLGet('BlockList')
    page_size = Integer(GAGet(General,'VirtualPageSize'))
    cstr = ''
    Num = 1
    for block in BlockList:
        if(GAGet(block,'IsArray')=='False'):
            cstr += '#define FEE_BLOCK_NUM_%-32s (%s)\n'%(GAGet(block,'Name'),Num)
            Num += 1
        else:
            for i in range(0,Integer(GAGet(block,'ArraySize'))):
                cstr += '#define FEE_BLOCK_NUM_%s_%s (%s)\n'%(GAGet(block,'Name'),i,Num)
                Num += 1
    cstr += '#define FEE_NUM_OF_BLOCKS  %s\n'%(Num -1)
    fp.write('''#ifndef FEE_CFG_H_
#define FEE_CFG_H_

#include "MemIf_Types.h"
#include "Fee_ConfigTypes.h"
#ifdef USE_NVM
#include "NvM.h"
#endif

#define FEE_DEV_ERROR_DETECT            STD_%s
#define FEE_VERSION_INFO_API            STD_%s
#define FEE_POLLING_MODE                STD_%s

#define FEE_INDEX                        (0xFE)
#define FEE_VIRTUAL_PAGE_SIZE            %s
#define FEE_MAX_NUM_SETS                 1

%s

#endif /*FEE_CFG_H_*/\n'''%(GAGet(General,'DevelopmentErrorDetection'),
                  GAGet(General,'VersionInfoApi'),
                  GAGet(General,'PollingMode'),
                  GAGet(General,'VirtualPageSize'),
                  cstr))
    fp.close()
    
    
def GenC():
    global __dir
    fp = open('%s/Fee_Cfg.c'%(__dir),'w')
    fp.write('#ifdef USE_FEE\n')
    fp.write(GHeader('Fee'))
    General=GLGet('General')
    BlockList = GLGet('BlockList')
    fp.write('#include "Fee.h"\n\n')
    if(GAGet(General,'NvmJobEndNotification') != 'NULL'):
        fp.write('extern void %s(void);\n'%(GAGet(General,'NvmJobEndNotification')))
    if(GAGet(General,'NvmJobErrorNotification') != 'NULL'):
        fp.write('extern void %s(void);\n'%(GAGet(General,'NvmJobErrorNotification')))   
    fp.write('\nstatic const Fee_BlockConfigType BlockConfigList[] = {\n')     
    for block in BlockList:
        if(GAGet(block,'IsArray')=='False'):
            fp.write('\t{    /* %s */\n'%(GAGet(block,'Name')))
            fp.write('\t\t.DeviceIndex = FEE_INDEX,\n')  
            fp.write('\t\t.BlockNumber = FEE_BLOCK_NUM_%s,\n'%(GAGet(block,'Name')))
            fp.write('\t\t#ifdef USE_NVM\n')
            fp.write('\t\t.BlockSize  =  NVM_FEE_BLOCK_SIZE_%s,\n'%(GAGet(block,'Name')))
            fp.write('\t\t#else\n')
            fp.write('\t\t.BlockSize  =  %s,\n'%(GAGet(block,'BlockSize')))
            fp.write('\t\t#endif\n')
            fp.write('\t\t.ImmediateData = %s,\n'%(GAGet(block,'ImmediateData').upper()))
            fp.write('\t\t.NumberOfWriteCycles = %s\n'%(GAGet(block,'NumberOfWriteCycles')))
            fp.write('\t},\n')
        else:
            for i in range(0,Integer(GAGet(block,'ArraySize'))):
                fp.write('\t{    /* %s %s */\n'%(GAGet(block,'Name'),i))
                fp.write('\t\t.DeviceIndex = FEE_INDEX,\n')  
                fp.write('\t\t.BlockNumber = FEE_BLOCK_NUM_%s_%s,\n'%(GAGet(block,'Name'),i))
                fp.write('\t\t#ifdef USE_NVM\n')
                fp.write('\t\t.BlockSize  =  NVM_FEE_BLOCK_SIZE_%s,\n'%(GAGet(block,'Name')))
                fp.write('\t\t#else\n')
                fp.write('\t\t.BlockSize  =  %s,\n'%(GAGet(block,'BlockSize')))
                fp.write('\t\t#endif\n')
                fp.write('\t\t.ImmediateData = %s,\n'%(GAGet(block,'ImmediateData').upper()))
                fp.write('\t\t.NumberOfWriteCycles = %s\n'%(GAGet(block,'NumberOfWriteCycles')))
                fp.write('\t},\n')
    fp.write('};\n\n')  
    fp.write('''const Fee_ConfigType Fee_Config = {
    .General = {
        .NvmJobEndCallbackNotificationCallback = %s,
        .NvmJobErrorCallbackNotificationCallback = %s,
    },
    .BlockConfig = BlockConfigList,
};\n\n'''%(GAGet(General,'NvmJobEndNotification'),GAGet(General,'NvmJobErrorNotification')))
    fp.write('#endif /* USE_FEE */\n')
    fp.close()
    