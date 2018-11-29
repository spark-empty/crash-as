""" * AS - the open source Automotive Software on https://github.com/parai
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
"""
import sys,os
from .GCF import *

__all__ = ['GenXcp']

__dir = '.'

def GenXcp(root,dir):
    global __dir,__root
    GLInit(root)
    General=GLGet('General')
    if((len(GLGet('XcpStaticDaqList')) == 0) and (GAGet(General,'XcpDaqConfigType') == 'DAT_STATIC')):return
    __dir = '%s'%(dir)
    GenH()
    GenC()
    print("    >>> Gen Xcp DONE <<<")

def GenH():
    global __dir
    fp = open('%s/Xcp_Cfg.h'%(__dir),'w')
    fp.write(GHeader('XCP'))
    General=GLGet('General')
    
    fp.write('#ifndef XCP_CFG_H\n#define XCP_CFG_H\n\n')
    fp.write('/* ============================ [ INCLUDES  ] ====================================================== */\n')
    fp.write('#include "Xcp_ConfigTypes.h"\n')
    fp.write('#include "CanIf.h"\n')
    fp.write('/* ============================ [ MACROS    ] ====================================================== */\n')
    fp.write('#define XCP_DEV_ERROR_DETECT STD_%s\n'%(GAGet(General,'DevelopmentErrorDetection')))
    fp.write('#define XCP_VERSION_INFO_API STD_%s\n'%(GAGet(General,'VersionInfoApi')))
    fp.write('#define XCP_FEATURE_GET_SLAVE_ID STD_ON\n')
    fp.write('\n#define DAQ_DYNAMIC 0\n#define DAQ_STATIC 1\n')
    fp.write('#define XCP_DAQ_CONFIG_TYPE %s\n'%(GAGet(General,'XcpDaqConfigType')))
    fp.write('#define XCP_IDENTIFICATION XCP_IDENTIFICATION_%s\n'%(GAGet(General,'XcpIdentificationFieldType')))
    fp.write('#define XCP_DAQ_COUNT  %s\n'%(GAGet(General,'XcpDaqCount')))
    fp.write('#define XCP_ODT_COUNT  %s\n'%(GAGet(General,'XcpOdtCount')))
    fp.write('#define XCP_ODT_ENTRIES_COUNT %s\n'%(GAGet(General,'XcpOdtEntriesCount')))
    fp.write('#define XCP_MAX_CTO %s\n'%(GAGet(General,'XcpMaxCto')))
    fp.write('#define XCP_MAX_DTO %s\n'%(GAGet(General,'XcpMaxDto')))
    fp.write('#define XCP_MAX_RXTX_QUEUE %s\n'%(GAGet(General,'XcpMaxRxTxQueue')))
    fp.write('#define XCP_PROTOCOL XCP_PROTOCOL_CAN\n')
    fp.write('#define XCP_PDU_ID_TX CANIF_ID_XCP_TX\n')
    fp.write('#define XCP_PDU_ID_RX 0\n')
    fp.write('#define XCP_CAN_ID_RX 0\n')
    fp.write('#define XCP_PDU_ID_BROADCAST 0\n')
    fp.write('#define XCP_ID_XCP_RX XCP_PDU_ID_RX\n')
    fp.write('#define XCP_ID_XCP_TX XCP_PDU_ID_TX\n\n')
    fp.write('#define XCP_FEATURE_PROTECTION STD_ON\n')
    fp.write('#define XCP_FEATURE_PGM STD_ON\n')
    fp.write('#define XCP_FEATURE_BLOCKMODE STD_ON\n')
    fp.write('#define XCP_FEATURE_CALPAG STD_ON\n\n')
    
    for id,evchl in enumerate(GLGet('XcpEventChannelList')):
        fp.write('#define XCP_EVCHL_%-32s %s\n'%(GAGet(evchl,'Name'),id))
    fp.write('\n')
    for id,daq in enumerate(GLGet('XcpStaticDaqList')):
        fp.write('#define XCP_STATIC_DAQ_ID_%-32s %s\n'%(GAGet(daq,'Name'),id))
    fp.write('#define XCP_STATIC_DAQ_COUNT %s\n'%(len(GLGet('XcpStaticDaqList'))))

    fp.write('/* ============================ [ TYPES     ] ====================================================== */\n')
    fp.write('/* ============================ [ DECLARES  ] ====================================================== */\n')
    fp.write('/* ============================ [ DATAS     ] ====================================================== */\n')
    fp.write('extern const Xcp_ConfigType XcpConfig;\n')
    fp.write('extern uint8_t xcpSimMTAMemory[];\n')
    fp.write('/* ============================ [ LOCALS    ] ====================================================== */\n')
    fp.write('/* ============================ [ FUNCTIONS ] ====================================================== */\n')
    fp.write('#endif\n')
    fp.close()
    
    fp = open('%s/XcpOnCan_Cfg.h'%(__dir),'w')
    fp.write(GHeader('XCP'))
    fp.write('#ifndef XCP_ON_CAN_CFG_H\n#define XCP_ON_CAN_CFG_H\n\n')
    fp.write('/* ============================ [ INCLUDES  ] ====================================================== */\n')
    fp.write('/* ============================ [ MACROS    ] ====================================================== */\n')
    fp.write('/* ============================ [ TYPES     ] ====================================================== */\n')
    fp.write('/* ============================ [ DECLARES  ] ====================================================== */\n')
    fp.write('/* ============================ [ DATAS     ] ====================================================== */\n')
    fp.write('/* ============================ [ LOCALS    ] ====================================================== */\n')
    fp.write('/* ============================ [ FUNCTIONS ] ====================================================== */\n')
    fp.write('#endif\n')
    fp.close()

def GenC():
    global __dir
    fp = open('%s/Xcp_Cfg.c'%(__dir),'w')
    fp.write(GHeader('XCP'))
    fp.write('#if defined(USE_XCP) && !defined(USE_XCP_MINI)\n')
    fp.write('/* ============================ [ INCLUDES  ] ====================================================== */\n')
    fp.write('#include "Xcp.h"\n')
    fp.write('#include "Xcp_Internal.h"\n')
    fp.write('/* ============================ [ MACROS    ] ====================================================== */\n')
    fp.write('#define XCP_EVENT_CHL_NUM %s\n'%(len(GLGet('XcpEventChannelList'))))
    fp.write('/* ============================ [ TYPES     ] ====================================================== */\n')
    fp.write('/* ============================ [ DECLARES  ] ====================================================== */\n')
    fp.write('/* ============================ [ DATAS     ] ====================================================== */\n')
    General=GLGet('General')
    XCP_DAQ_COUNT = XCP_ODT_COUNT = XCP_ODT_ENTRIES_COUNT = 0;
    for daq in GLGet('XcpStaticDaqList'):
        XCP_DAQ_COUNT += 1
        for odt in GLGet(daq,'XcpOdtList'):
            XCP_ODT_COUNT += 1
            for entry in GLGet(odt,'XcpOdtEntryList'):
                 XCP_ODT_ENTRIES_COUNT += 1
    fp.write('#if XCP_STATIC_DAQ_COUNT > 0\n')
    fp.write('static Xcp_OdtEntryType xcpOdtEntry[%s] = \n{\n'%(XCP_ODT_ENTRIES_COUNT))
    for daq in GLGet('XcpStaticDaqList'):
        for odt in GLGet(daq,'XcpOdtList'):
            for entry in GLGet(odt,'XcpOdtEntryList'):
                fp.write('    { /* %s of %s of %s */\n'%(GAGet(entry,'Name'),GAGet(odt,'Name'),GAGet(daq,'Name')))
                fp.write('        .XcpOdtEntryExtension=XCP_MTA_EXTENSION_%s,\n'%(GAGet(entry,'Extension')))
                fp.write('        .XcpOdtEntryAddress=(void*)%s,\n'%(GAGet(entry,'Address')))
                fp.write('        .XcpOdtEntryLength=%s,\n'%(GAGet(entry,'Length')))
                fp.write('    },\n')
    fp.write('};\n\n')
    fp.write('static Xcp_OdtType xcpOdt[%s] = \n{\n'%(XCP_ODT_COUNT))
    odt_entry_pos=0;
    for daq in GLGet('XcpStaticDaqList'):
        for odt in GLGet(daq,'XcpOdtList'):
            fp.write('    { /* %s of %s*/\n'%(GAGet(odt,'Name'),GAGet(daq,'Name')));
            fp.write('        .XcpMaxOdtEntries = %s,\n'%(len(GLGet(odt,'XcpOdtEntryList'))))
            fp.write('        .XcpOdtEntry = &xcpOdtEntry[%s],\n'%(odt_entry_pos))
            fp.write('        .XcpOdtEntriesValid = %s,\n'%(len(GLGet(odt,'XcpOdtEntryList'))))
            fp.write('    },\n')
            odt_entry_pos += len(GLGet(odt,'XcpOdtEntryList'))
        fp.write('};\n')
    fp.write('static Xcp_DaqListParams xcpStaticDaqParams[%s];\n'%(len(GLGet('XcpStaticDaqList'))))
    fp.write('static const Xcp_DaqListType xcpDaqList[%s] = \n{\n'%(len(GLGet('XcpStaticDaqList'))))
    for id,daq in enumerate(GLGet('XcpStaticDaqList')):
        fp.write('    {/* %s */\n'%(GAGet(daq,'Name')))
        fp.write('        .XcpOdtCount = %s,\n'%(len(GLGet(daq,'XcpOdtList'))))
        fp.write('        .XcpMaxOdt = %s,\n'%(len(GLGet(daq,'XcpOdtList'))))
        fp.write('        .XcpOdt = &xcpOdt[%d],\n'%(id))
        fp.write('        .XcpParams=&xcpStaticDaqParams[%d]\n'%(id))
        fp.write('    },\n')
    fp.write('};\n')
    fp.write('#endif\n')
    fp.write('#if(XCP_DAQ_CONFIG_TYPE == DAQ_DYNAMIC)\n')
    fp.write('static Xcp_DaqListParams xcpDaqParamsDYN[XCP_DAQ_COUNT];\n')
    fp.write('static Xcp_DaqListType xcpDaqListDYN[XCP_DAQ_COUNT];\n')
    fp.write('static Xcp_OdtType xcpOdtDYN[XCP_DAQ_COUNT * XCP_ODT_COUNT];\n')
    fp.write('static Xcp_OdtEntryType xcpOdtEntryDYN[XCP_DAQ_COUNT * XCP_ODT_COUNT * XCP_ODT_ENTRIES_COUNT];\n')
    fp.write('#endif\n')
    fp.write('#if XCP_EVENT_CHL_NUM>0\n')
    for evchl in GLGet('XcpEventChannelList'):
        fp.write('static const Xcp_DaqListType* XcpEventChannelTriggeredDaqListRef_%s[%s]'%(
                                                        GAGet(evchl,'Name'),
                                                        GAGet(evchl,'DAQListRefSize')))
        if(len(GLGet(evchl,'XcpStaticDaqList'))>0):
            fp.write(' =\n{\n')
            for daq in GLGet(evchl,'XcpStaticDaqList'):
                fp.write('    &xcpDaqList[XCP_STATIC_DAQ_ID_%s],\n'%(GAGet(daq,'Name')))
            fp.write('};\n')
        else:
            fp.write(';\n')
    fp.write('static Xcp_EventChannelType xcpEventChannel[%s] = \n{\n'%(len(GLGet('XcpEventChannelList'))))
    for id,evchl in enumerate(GLGet('XcpEventChannelList')):
        if(len(GLGet(evchl,'XcpStaticDaqList'))>0):
            XcpEventChannelDaqCount = len(GLGet(evchl,'XcpStaticDaqList'))
        else:
            XcpEventChannelDaqCount = 0
        fp.write('    {\n')
        fp.write('        .XcpEventChannelName = "%s",\n'%(GAGet(evchl,'Name')))
        fp.write('        .XcpEventChannelNumber=%s,\n'%(id))
        fp.write('        .XcpEventChannelMaxDaqList = %s,\n'%(GAGet(evchl,'DAQListRefSize')))
        fp.write('        .XcpEventChannelTriggeredDaqListRef=XcpEventChannelTriggeredDaqListRef_%s,\n'%(GAGet(evchl,'Name')))
        fp.write('        .XcpEventChannelDaqCount=%s,\n'%(XcpEventChannelDaqCount))
        fp.write('    },\n')
    fp.write('};\n#endif\n')
    fp.write('''
Std_ReturnType __weak Xcp_UnlockFn(Xcp_ProtectType res, const uint8* seed,
            uint8 seed_len, const uint8* key, uint8 key_len)
{
    Std_ReturnType ercd = E_OK;
    if( (4==seed_len) && (4==key_len))
    {
        if( 0 == memcmp(seed,key,4))
        {
        }
        else
        {
            ercd = E_NOT_OK;
        }
    }
    else
    {
        ercd = E_NOT_OK;
    }

    return ercd;
}
uint8 __weak Xcp_SeedFn(Xcp_ProtectType res, uint8* seed)
{
    uint8 seed_r[4];    /* use stack local random value */
    memcpy(seed,seed_r,4);
    return 4;
}
Std_ReturnType __weak Xcp_UserFn(void* data, int len)
{
    return E_NOT_OK;
}
const Xcp_ConfigType XcpConfig =
{
#if XCP_EVENT_CHL_NUM>0
    .XcpEventChannel = xcpEventChannel,
#else
    .XcpEventChannel = NULL,
#endif
    .XcpMaxEventChannel = %s,
#if XCP_STATIC_DAQ_COUNT > 0
    .XcpDaqList = xcpDaqList,
#else
    .XcpDaqList = NULL,
#endif
    .XcpMinDaq = XCP_STATIC_DAQ_COUNT,
    .XcpProtect = (Xcp_ProtectType)0xFFFFFFFFUL,
#if(XCP_DAQ_CONFIG_TYPE == DAQ_DYNAMIC)
    .ptrDynamicDaqParams = xcpDaqParamsDYN,
    .ptrDynamicDaq = xcpDaqListDYN,
    .ptrDynamicOdt = xcpOdtDYN,
    .ptrDynamicOdtEntry = xcpOdtEntryDYN,
#endif
    .XcpSeedFn = Xcp_SeedFn,
    .XcpUnlockFn = Xcp_UnlockFn,
    .XcpUserFn = Xcp_UserFn,
};
'''%(len(GLGet('XcpEventChannelList'))))

    fp.write('/* ============================ [ LOCALS    ] ====================================================== */\n')
    fp.write('/* ============================ [ FUNCTIONS ] ====================================================== */\n')
    fp.write('#endif /* USE_XCP */\n')
    fp.close()
