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

__all__ = ['GenFls']

__dir = '.'

def GenFls(root,dir):
    global __dir
    GLInit(root)
    __dir = '%s'%(dir)
    if(len(GLGet('SectorList')) == 0):return
    GenH()
    GenC()
    print('    >>> Gen Fls DONE <<<')
    
def GenH():
    global __dir
    fp = open('%s/Fls_Cfg.h'%(__dir),'w')
    fp.write(GHeader('Fls'))
    General=GLGet('General')
    sector = GLGet('SectorList')[0]
    fp.write('''#ifndef FLS_CFG_H_
#define FLS_CFG_H_

#define USE_FLS_INFO        STD_OFF


/* STD container : Fls
 * FlsConfigSet             1..*
 * FlsGeneral                1
 * FlsPublishedInformation     1
 */

#include "MemIf_Types.h"

/* FlsGeneral, 3.0 OK */
#define FLS_VARIANT_PB                STD_OFF
#define FLS_AC_LOAD_ON_JOB_START     STD_OFF            /* NO SUPPORT */
#define FLS_BASE_ADDRESS             %s
#define FLS_CANCEL_API                STD_OFF            /* NO SUPPORT */
#define FLS_COMPARE_API                STD_ON
#define FLS_DEV_ERROR_DETECT        STD_%s
#define FLS_DRIVER_INDEX            0                /* NO SUPPORT */
#define FLS_GET_JOB_RESULT_API        STD_ON
#define FLS_GET_STATUS_API            STD_ON
#define FLS_SET_MODE_API            STD_ON
#define FLS_USE_INTERRUPTS            STD_OFF            /* NO SUPPORT */
#define FLS_VERSION_INFO_API        STD_%s

/* FlsPublishedInformation, 3.0 OK */
#define FLS_AC_LOCATION_ERASE        0                 /* NO SUPPORT */
#define FLS_AC_LOCATION_WRITE        0                /* NO SUPPORT */
#define FLS_AC_SIZE_ERASE            0                /* NO SUPPORT */
#define FLS_AC_SIZE_WRITE            0                /* NO SUPPORT */
#define FLS_ERASE_TIME                0                /* NO SUPPORT */
#define FLS_ERASED_VALUE            0xff            /* NO SUPPORT */
#define FLS_EXPECTED_HW_ID            0                /* NO SUPPORT */
#define FLS_SPECIFIED_ERASE_CYCLES    0                /* NO SUPPORT */
#define FLS_WRITE_TIME                0                /* NO SUPPORT */

/* MCU Specific for posix simulation: only 1 sector allowed */
#define FLASH_BANK_CNT                %s
#define FLASH_PAGE_SIZE               %s
#define FLASH_MAX_SECTORS             %s
#define FLS_TOTAL_SIZE                (%s*%s)

#include "Fls_ConfigTypes.h"


#endif /*FLS_CFG_H_*/
/** @} */\n\n'''%(GAGet(General,'FlashBaseAddress'),
                  GAGet(General,'DevelopmentErrorDetection'),
                  GAGet(General,'VersionInfoApi'),
                  len(GLGet('SectorList')),
                  GAGet(sector,'PageSize'),
                  GAGet(sector,'NumberOfSectors'),
                  GAGet(sector,'SectorSize'),GAGet(sector,'NumberOfSectors')))
    
    fp.close()
    
def GenC():
    global __dir
    fp = open('%s/Fls_Cfg.c'%(__dir),'w')
    fp.write('#ifdef USE_FLS\n')
    fp.write(GHeader('Fls'))
    fp.write('#include "Fls.h"\n\n')
    SectorList = GLGet('SectorList')
    fp.write('static const Fls_SectorType fls_evbSectorList[] =\n{\n')
    for sector in SectorList:
        fp.write('\t{ /* %s */\n'%(GAGet(sector,'Name')))
        fp.write('\t\t.FlsNumberOfSectors = %s,\n'%(GAGet(sector,'NumberOfSectors')))
        fp.write('\t\t.FlsPageSize        = %s,\n'%(GAGet(sector,'PageSize')))
        fp.write('\t\t.FlsSectorSize      = %s,\n'%(GAGet(sector,'SectorSize')))
        fp.write('\t\t.FlsSectorStartaddress = %s,\n'%(GAGet(sector,'StartAddress')))
        fp.write('\t},\n')
    fp.write('};\n\n')
    General=GLGet('General')
    fp.write('''const Fls_ConfigType FlsConfigSet[]=
{
  {
#if ( FLS_AC_LOAD_ON_JOB_START == STD_ON)
    .FlsAcWrite = __FLS_ERASE_RAM__,
    .FlsAcErase = __FLS_WRITE_RAM__,
#else
    .FlsAcWrite = NULL,
    .FlsAcErase = NULL,
#endif
    .FlsJobEndNotification = NULL,
    .FlsJobErrorNotification = NULL,

    .FlsMaxReadFastMode = %s,
    .FlsMaxReadNormalMode = %s,
    .FlsMaxWriteFastMode = %s,
    .FlsMaxWriteNormalMode = %s,

    .FlsSectorList = &fls_evbSectorList[0],
    .FlsSectorListSize = sizeof(fls_evbSectorList)/sizeof(Fls_SectorType),
//    .FlsBlockToPartitionMap = Fls_BlockToPartitionMap,
  }
};\n\n'''%(GAGet(General,'MaxFastReadSize'),
           GAGet(General,'MaxNormalReadSize'),
           GAGet(General,'MaxFastWriteSize'),
           GAGet(General,'MaxNormalWriteSize'),))
    fp.write('#endif /* USE_EA */\n')
    fp.close()
    