'''/**
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
import sys,os
from .GCF import *

__all__ = ['GenDem']

__dir = '.'

def GenDem(root,dir):
    global __dir
    GLInit(root)
    __dir = '%s'%(dir)
    if(len(GLGet('EventClassList')) == 0):return
    GenH()
    GenC()
    print('    >>> Gen Dem DONE <<<')

def GenH():
    global __dir
    General= GLGet('General')
    EventParameterList= GLGet('EventParameterList')
    fp = open('%s/Dem_Cfg.h'%(__dir),'w')
    fp.write(GHeader('Dem'))
    fp.write('#ifndef DEM_CFG_H\n#define DEM_CFG_H\n')
    fp.write('/* ============================ [ INCLUDES  ] ====================================================== */\n')
    fp.write('/* ============================ [ MACROS    ] ====================================================== */\n')
    fp.write('#define DEM_VERSION_INFO_API        STD_%s\n'%(GAGet(General,'VersionInfoApi')))
    fp.write('#define DEM_DEV_ERROR_DETECT        STD_%s\n'%(GAGet(General,'DevelopmentErrorDetection')))
    fp.write('#define DEM_USE_NVM                 STD_%s\n'%(GAGet(General,'DEM_USE_NVM')))
    fp.write('#define DEM_OBD_SUPPORT             STD_%s\n'%(GAGet(General,'DEM_OBD_SUPPORT')))
    fp.write('#define DEM_PTO_SUPPORT             STD_%s\n'%(GAGet(General,'DEM_PTO_SUPPORT')))
    fp.write('#define DEM_CLEAR_ALL_EVENTS        STD_%s\n\n'%(GAGet(General,'DEM_CLEAR_ALL_EVENTS')))
    fp.write('#define DEM_TYPE_OF_DTC_SUPPORTED          %s\n'%(GAGet(General,'DEM_TYPE_OF_DTC_SUPPORTED')))
    fp.write('#define DEM_DTC_STATUS_AVAILABILITY_MASK   %s\n'%(GAGet(General,'DEM_DTC_STATUS_AVAILABILITY_MASK')))
    fp.write('#define DEM_MAX_NUMBER_EVENT               %s\n'%(len(EventParameterList)))
    fp.write('#define DEM_MAX_NUMBER_FF_DATA_PRI_MEM     %s\n'%(GAGet(General,'DEM_MAX_NUMBER_FF_DATA_PRI_MEM')))
    fp.write('''#define DEM_FF_DID_LENGTH                    TBD    // Length of DID & PID of FreezeFrames in Bytes.
#define DEM_MAX_NUMBER_EVENT_ENTRY_MIR        0    // Max nr of events stored in mirror memory.
#define DEM_MAX_NUMBER_EVENT_ENTRY_PER        0    // Max nr of events stored in permanent memory.
#define DEM_MAX_NUMBER_EVENT_ENTRY_PRI        DEM_MAX_NUMBER_EVENT    // Max nr of events stored in primary memory.
#define DEM_MAX_NUMBER_EVENT_ENTRY_SEC        0    // Max nr of events stored in secondary memory.
#define DEM_MAX_NUMBER_PRESTORED_FF            0    // Max nr of prestored FreezeFrames. 0=Not supported.

/*
 * Size limitations of the types derived from DemGeneral
 */
#define DEM_MAX_NR_OF_EVENT_DESTINATION             1    // 0..4 according to Autosar

/*
 * Size limitations of storage area
 */
#define DEM_MAX_SIZE_FF_DATA                     10    // Max number of bytes in one freeze frame
#define DEM_MAX_SIZE_EXT_DATA                     10    // Max number of bytes in one extended data record

#define DEM_MAX_NUMBER_EVENT_PRE_INIT             20    // Max number of events status to keep before init
#define DEM_MAX_NUMBER_FF_DATA_PRE_INIT             20    // Max number of freeze frames to store before init
#define DEM_MAX_NUMBER_EXT_DATA_PRE_INIT         20    // Max number of extended data to store before init

#define DEM_MAX_NUMBER_EVENT_PRI_MEM            (DEM_MAX_NUMBER_EVENT_ENTRY_PRI)    // Max number of events status to store in primary memory
#define DEM_MAX_NUMBER_EXT_DATA_PRI_MEM            5                                    // Max number of extended data to store in primary memory

#define DEM_MAX_NUMBER_AGING_PRI_MEM 1
#define DEM_DID_IDENTIFIER_SIZE_OF_BYTES 1
#define DEM_FREEZEFRAME_DEFAULT_VALUE 1\n''')
    fp.write('\n#define HealingMirrorBuffer ((void*)&NvM_Block_%s_DataGroup_RAM)\n\n'%(GAGet(General,'NvMHealingBlock')))
    fp.write('/* ============================ [ TYPES     ] ====================================================== */\n')
    fp.write('/* ============================ [ DECLARES  ] ====================================================== */\n')
    fp.write('/* ============================ [ DATAS     ] ====================================================== */\n')
    fp.write('/* ============================ [ LOCALS    ] ====================================================== */\n')
    fp.write('/* ============================ [ FUNCTIONS ] ====================================================== */\n')
    fp.write('#endif\n\n')

    fp = open('%s/Dem_IntErrId.h'%(__dir),'w')
    fp.write(GHeader('Dem'))
    fp.write('#ifndef DEM_INTERRID_H\n#define DEM_INTERRID_H\n')
    fp.write('/* ============================ [ INCLUDES  ] ====================================================== */\n')
    fp.write('/* ============================ [ MACROS    ] ====================================================== */\n')
    fp.write('''/*
 * Definition of event IDs used by BSW
 * NB! Must be unique for each event!
 */

enum {
    // Event IDs from DEM module
    DEM_EVENT_ID_NULL = 0,            // Do not change this entry!!!\n''')
    for evt in EventParameterList:
        if(GAGet(evt,'EventKind') == 'BSW'):
            fp.write('\t%s,\n'%(GAGet(evt,'Name')))
    fp.write('''    // DEM last event id for BSW
    DEM_EVENT_ID_LAST_FOR_BSW
};\n''')
    fp.write('/* ============================ [ TYPES     ] ====================================================== */\n')
    fp.write('/* ============================ [ DECLARES  ] ====================================================== */\n')
    fp.write('/* ============================ [ DATAS     ] ====================================================== */\n')
    fp.write('/* ============================ [ LOCALS    ] ====================================================== */\n')
    fp.write('/* ============================ [ FUNCTIONS ] ====================================================== */\n')
    fp.write('#endif\n\n')

    fp = open('%s/Dem_IntEvtId.h'%(__dir),'w')
    fp.write(GHeader('Dem'))
    fp.write('#ifndef DEM_INTEVTID_H\n#define DEM_INTEVTID_H\n')
    fp.write('/* ============================ [ INCLUDES  ] ====================================================== */\n')
    fp.write('/* ============================ [ MACROS    ] ====================================================== */\n')
    fp.write('''/*
 * Definition of event IDs used by SW-C
 * NB! Must be unique for each event!
 */
enum {
    // NB! Event IDs below DEM_SWC_EVENT_ID_START not allowed!
    DEM_EVENT_ID_SWC_START = DEM_EVENT_ID_LAST_FOR_BSW,\n''')
    for evt in EventParameterList:
        if(GAGet(evt,'EventKind') == 'SWC'):
            fp.write('\tDEM_EVENT_ID_%s,\n'%(GAGet(evt,'Name')))
    fp.write('};\n')
    fp.write('/* ============================ [ TYPES     ] ====================================================== */\n')
    fp.write('/* ============================ [ DECLARES  ] ====================================================== */\n')
    fp.write('/* ============================ [ DATAS     ] ====================================================== */\n')
    fp.write('/* ============================ [ LOCALS    ] ====================================================== */\n')
    fp.write('/* ============================ [ FUNCTIONS ] ====================================================== */\n')
    fp.write('#endif\n\n')

def GenC():
    global __dir
    global __dir
    General= GLGet('General')
    fp = open('%s/Dem_Cfg.c'%(__dir),'w')
    fp.write(GHeader('Dem'))
    fp.write('#ifdef USE_DEM\n')
    fp.write('/* ============================ [ INCLUDES  ] ====================================================== */\n')
    fp.write('#include "Dem.h"\n\n')
    fp.write('#ifdef USE_NVM\n')
    fp.write('#include "NvM.h"\n')
    fp.write('#endif\n')
    fp.write('#ifdef USE_DCM\n')
    fp.write('#include "Dcm.h"\n')
    fp.write('#endif\n')
    fp.write('/* ============================ [ MACROS    ] ====================================================== */\n')
    FFIdClassList= GLGet('FFIdClassList')
    for id,obj in enumerate(FFIdClassList):
        fp.write('#define INDEX_OF_FFIDCLASS_%s %s\n'%(GAGet(obj,'Name'),id))
    FreezeFrameClassList=GLGet('FreezeFrameClassList')
    for id,obj in enumerate(FreezeFrameClassList):
        fp.write('#define INDEX_OF_FFCLASS_%s %s\n'%(GAGet(obj,'Name'),id))
    ExtendedDataRecordClassList = GLGet('ExtendedDataRecordClassList')
    for id,obj in enumerate(ExtendedDataRecordClassList):
        fp.write('#define INDEX_OF_EDRC_%s %s\n'%(GAGet(obj,'Name'),id))
    fp.write('/* ============================ [ TYPES     ] ====================================================== */\n')
    fp.write('/* ============================ [ DECLARES  ] ====================================================== */\n')
    for id,obj in enumerate(FFIdClassList):
        if(GAGet(obj,'DidConditionCheckReadFnc') != 'NULL'):
            fp.write('#if defined(USE_DCM)\n')
            fp.write('extern Std_ReturnType Dem_DidConditionCheckReadFnc_%s(Dcm_NegativeResponseCodeType *Nrc);\n'%(GAGet(obj,'Name')))
            fp.write('#else\n')
            fp.write('extern Std_ReturnType Dem_DidConditionCheckReadFnc_%s(uint8 *Nrc);\n'%(GAGet(obj,'Name')))
            fp.write('#endif\n')
        if(GAGet(obj,'DidReadDataLengthFnc') != 'NULL'):
            fp.write('extern Std_ReturnType Dem_DidReadDataLengthFnc_%s(uint16 *DidLength);\n'%(GAGet(obj,'Name')))
        if(GAGet(obj,'DidReadFnc') != 'NULL'):
            fp.write('extern Std_ReturnType Dem_DidReadFnc_%s(uint8 *Data);\n'%(GAGet(obj,'Name')))
        if(GAGet(obj,'PidReadFnc') != 'NULL'):
            fp.write('extern Std_ReturnType Dem_PidReadFnc_%s(uint8 *DataValueBuffer);\n'%(GAGet(obj,'Name')))
    for obj in ExtendedDataRecordClassList:
        if(GAGet(obj,'CallbackGetExtDataRecord') != 'NULL'):
            fp.write('extern Std_ReturnType Dem_CallbackGetExtDataRecord_%s(uint8 *ExtendedDataRecord);\n'%(GAGet(obj,'Name')))
    EventParameterList= GLGet('EventParameterList')
    for obj in EventParameterList:
        if(GAGet(obj,'CallbackInitMForEFnc') != 'NULL'):
            fp.write('extern Std_ReturnType Dem_CallbackInitMForEFnc_%s(Dem_InitMonitorKindType InitMonitorKind);\n'%(GAGet(obj,'Name')))
    fp.write('/* ============================ [ DATAS     ] ====================================================== */\n')
    fp.write('static const Dem_PidOrDidType Dem_PidOrDid[]=\n{\n')
    def FFIdFunc(obj,f):
        if(GAGet(obj,f) == 'NULL'):
            return 'NULL'
        else:
            return 'Dem_%s_%s'%(f,GAGet(obj,'Name'))
    for obj in FFIdClassList:
        fp.write('\t{ /* %s */\n'%(GAGet(obj,'Name')))
        fp.write('\t\t.DidConditionCheckReadFnc=%s,\n'%(FFIdFunc(obj,'DidConditionCheckReadFnc')))
        fp.write('\t\t.DidIdentifier=%s,\n'%(GAGet(obj,'DidIdentifier')))
        fp.write('\t\t.DidReadDataLengthFnc=%s,\n'%(FFIdFunc(obj,'DidReadDataLengthFnc')))
        fp.write('\t\t.DidReadFnc=%s,\n'%(FFIdFunc(obj,'DidReadFnc')))
        fp.write('\t\t.PidIndentifier=%s,\n'%(GAGet(obj,'PidIndentifier')))
        fp.write('\t\t.PidOrDidSize=%s,\n'%(GAGet(obj,'PidOrDidSize')))
        fp.write('\t\t.PidOrDidUsePort=%s,\n'%('FALSE'))
        fp.write('\t\t.PidReadFnc=%s,\n'%(FFIdFunc(obj,'PidReadFnc')))
        fp.write('\t},\n')
    fp.write('};\n\n')

    fp.write('static const Dem_ExtendedDataRecordClassType Dem_ExtendedDataRecord[]=\n{\n')
    for obj in ExtendedDataRecordClassList:
        fp.write('\t{ /* %s */\n'%(GAGet(obj,'Name')))
        fp.write('\t\t.RecordNumber=%s,\n'%(GAGet(obj,'RecordNumber')))
        fp.write('\t\t.DataSize=%s,\n'%(GAGet(obj,'DataSize')))
        fp.write('\t\t.UpdateRule=DEM_UPDATE_RECORD_%s,\n'%(GAGet(obj,'UpdateRule')))
        fp.write('\t\t.CallbackGetExtDataRecord=%s,\n'%(FFIdFunc(obj,'CallbackGetExtDataRecord')))
        fp.write('\t\t.InternalDataElement=DEM_%s,\n'%(GAGet(obj,'InternalDataElement')))
        fp.write('\t},\n')
    fp.write('};\n\n')

    DTCClassList= GLGet('DTCClassList')
    for obj in DTCClassList:
        fp.write('static const Dem_DTCClassType DTCClassRef_%s=\n{\n'%(GAGet(obj,'Name')))
        fp.write('\t.DTC=%s,\n'%(GAGet(obj,'DTC')))
        fp.write('\t.DTCFunctionalUnit=%s,\n'%(GAGet(obj,'DTCFunctionalUnit')))
        fp.write('\t.DTCKind=DEM_DTC_KIND_%s,\n'%(GAGet(obj,'DTCKind')))
        fp.write('};\n\n')

    EventClassList= GLGet('EventClassList')
    for cst in EventClassList:
        fp.write('static const Dem_EventClassType EventClass_%s = \n{\n'%(GAGet(cst,'Name')))
        fp.write('\t.ConsiderPtoStatus=%s,\n'%(GAGet(cst,'ConsiderPtoStatus').upper()))
        fp.write('\t.EventDestination={ DEM_DTC_ORIGIN_PRIMARY_MEMORY },\n')
        fp.write('\t.EventPriority=%s,\n'%(GAGet(cst,'EventPriority')))
        fp.write('\t.FFPrestorageSupported=%s,\n'%(GAGet(cst,'FFPrestorageSupported').upper()))
        fp.write('\t.HealingAllowed=%s,\n'%(GAGet(cst,'HealingAllowed').upper()))
        fp.write('\t.OperationCycleRef=DEM_%s,\n'%(GAGet(cst,'OperationCycleRef')))
        fp.write('\t.HealingCycleRef=DEM_%s,\n'%(GAGet(cst,'HealingCycleRef')))
        fp.write('\t.HealingCycleCounter=%s,\n'%(GAGet(cst,'HealingCycleCounter')))
        fp.write('\t.ConfirmationCycleCounterThreshold=%s,\n'%(GAGet(cst,'ConfirmationCycleCounterThreshold')))
        fp.write('};\n\n')

    for obj in FreezeFrameClassList:
        FFIdClassRefList = GLGet(obj,'FFIdClassRefList')
        if(len(FFIdClassRefList) == 0): continue
        fp.write('static const Dem_PidOrDidType *%s_FFIdClassRef[] = \n{\n'%(GAGet(obj,'Name')))
        for ref in FFIdClassRefList:
            fp.write('\t&Dem_PidOrDid[INDEX_OF_FFIDCLASS_%s],\n'%(GAGet(ref,'Name')))
        fp.write('\tNULL\n};\n\n')
    fp.write('static const Dem_FreezeFrameClassType Dem_FreezeFrameClass[]=\n{\n')
    for obj in FreezeFrameClassList:
        fp.write('\t{ /* %s */\n'%(GAGet(obj,'Name')))
        fp.write('\t\t.FFKind=DEM_FREEZE_FRAME_%s,\n'%(GAGet(obj,'FFKind')))
        fp.write('\t\t.FFRecordNumber=%s,\n'%(GAGet(obj,'FFRecordNumber')))
        fp.write('\t\t.FFStorageCondition=DEM_FF_STORAGE_%s,\n'%(GAGet(obj,'FFStorageCondition')))
        fp.write('\t\t.FFIdClassRef=%s_FFIdClassRef,\n'%(GAGet(obj,'Name')))
        fp.write('\t},\n')
    fp.write('};\n\n')

    for obj in EventParameterList:
        FreezeFrameClassRefList = GLGet(obj,'FreezeFrameClassRefList')
        if(len(FreezeFrameClassRefList) == 0): continue
        fp.write('static const Dem_FreezeFrameClassType *%s_FreezeFrameClassRef[] = \n{\n'%(GAGet(obj,'Name')))
        for ref in FreezeFrameClassRefList:
            fp.write('\t&Dem_FreezeFrameClass[INDEX_OF_FFCLASS_%s],\n'%(GAGet(ref,'Name')))
        fp.write('\tNULL\n};\n\n')
        ExtendedDataClassRefList = GLGet(obj,'ExtendedDataClassRefList')
        if(len(ExtendedDataClassRefList) == 0): continue
        fp.write('static const Dem_ExtendedDataRecordClassType *%s_ExtendedDataClassRef[] = \n{\n'%(GAGet(obj,'Name')))
        for ref in ExtendedDataClassRefList:
            fp.write('\t&Dem_ExtendedDataRecord[INDEX_OF_EDRC_%s],\n'%(GAGet(ref,'Name')))
        fp.write('\tNULL\n};\n\n')
    fp.write('static const Dem_EventParameterType EventParameterList[] = \n{\n')
    def FFRef(obj,f):
        lst = GLGet(obj,'%sList'%(f))
        if(len(lst) == 0): return 'NULL'
        return '%s_%s'%(GAGet(obj,'Name'),f)
    def DTCClassRef(obj,f):
        if(GAGet(obj,f) != 'NULL'):
            return '&%s_%s'%(f,GAGet(obj,f))
        return 'NULL'
    for evt in EventParameterList:
        if(GAGet(evt,'EventKind') == 'BSW'):
            fp.write('\t{\n')
            fp.write('\t\t.EventID=%s,\n'%(GAGet(evt,'Name')))
            fp.write('\t\t.EventKind=DEM_EVENT_KIND_%s,\n'%(GAGet(evt,'EventKind')))
            fp.write('\t\t.EventClass=&EventClass_%s,\n'%(GAGet(evt,'EventClassRef')))
            fp.write('\t\t.FreezeFrameClassRef=%s,\n'%(FFRef(evt,'FreezeFrameClassRef')))
            fp.write('\t\t.ExtendedDataClassRef=%s,\n'%(FFRef(evt,'ExtendedDataClassRef')))
            fp.write('\t\t.CallbackInitMForEFnc=%s,\n'%(FFIdFunc(evt,'CallbackInitMForEFnc')))
            fp.write('\t\t.DTCClassRef=%s,\n'%(DTCClassRef(evt,'DTCClassRef')))
            fp.write('\t\t.Arc_EOL=FALSE,\n')
            fp.write('\t},\n')
    for evt in EventParameterList:
        if(GAGet(evt,'EventKind') == 'SWC'):
            fp.write('\t{\n')
            fp.write('\t\t.EventID=DEM_EVENT_ID_%s,\n'%(GAGet(evt,'Name')))
            fp.write('\t\t.EventKind=DEM_EVENT_KIND_%s,\n'%(GAGet(evt,'EventKind')))
            fp.write('\t\t.EventClass=&EventClass_%s,\n'%(GAGet(evt,'EventClassRef')))
            fp.write('\t\t.FreezeFrameClassRef=%s,\n'%(FFRef(evt,'FreezeFrameClassRef')))
            fp.write('\t\t.ExtendedDataClassRef=%s,\n'%(FFRef(evt,'ExtendedDataClassRef')))
            fp.write('\t\t.CallbackInitMForEFnc=%s,\n'%(FFIdFunc(evt,'CallbackInitMForEFnc')))
            fp.write('\t\t.DTCClassRef=%s,\n'%(DTCClassRef(evt,'DTCClassRef')))
            fp.write('\t\t.Arc_EOL=FALSE,\n')
            fp.write('\t},\n')
    fp.write('\t{\n\t\t.Arc_EOL=TRUE\n\t}\n};\n\n')
    fp.write('static const Dem_ConfigSetType DemConfig = \n{\n')
    fp.write('\t.EventParameter=EventParameterList,\n')
    fp.write('};\n\n')
    fp.write('const Dem_ConfigType DEM_Config = { .ConfigSet = &DemConfig };\n\n')
    fp.write('#ifdef USE_NVM\n')
    fp.write('FreezeFrameRecType * const FreezeFrameMirrorBuffer[DEM_MAX_NUMBER_FF_DATA_PRI_MEM] = \n{\n')
    for i in range(0,Integer(GAGet(General,'DEM_MAX_NUMBER_FF_DATA_PRI_MEM'))):
        fp.write('\t(FreezeFrameRecType*)&NvM_Block_%s_DataGroup_RAM[%s],\n'%(GAGet(General,'NvMFreezeFrameBlock'),i))
    fp.write('};\n\n')
    fp.write('const NvM_BlockIdType FreezeFrameBlockId[DEM_MAX_NUMBER_FF_DATA_PRI_MEM] = \n{\n')
    for i in range(0,Integer(GAGet(General,'DEM_MAX_NUMBER_FF_DATA_PRI_MEM'))):
        fp.write('\tNVM_BLOCK_ID_%s_%s,\n'%(GAGet(General,'NvMFreezeFrameBlock'),i))
    fp.write('};\n\n')
    fp.write('const NvM_BlockIdType HealingBlockId = NVM_BLOCK_ID_%s;\n'%(GAGet(General,'NvMHealingBlock')))
    fp.write('#endif /* USE_DCM */\n\n')
    fp.write('/* ============================ [ LOCALS    ] ====================================================== */\n')
    fp.write('/* ============================ [ FUNCTIONS ] ====================================================== */\n')
    fp.write('#endif\n')
    fp.close()
