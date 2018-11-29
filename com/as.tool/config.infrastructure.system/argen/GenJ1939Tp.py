'''/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2018  AS <parai@foxmail.com>
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

__all__ = ['GenJ1939Tp']

__dir = '.'

def GenJ1939Tp(root,dir):
    global __dir
    GLInit(root)
    __dir = '%s'%(dir)
    if(len(GLGet('ChannelList')) == 0):return
    GenH()
    GenC()
    print('    >>> Gen J1939Tp DONE <<<')

def GenH():
    global __dir
    General= GLGet('General')
    fp = open('%s/J1939Tp_Cfg.h'%(__dir),'w')
    fp.write(GHeader('J1939Tp'))
    fp.write('#ifndef J1939TP_CFG_H\n#define J1939TP_CFG_H\n')
    fp.write('/* ============================ [ INCLUDES  ] ====================================================== */\n')
    fp.write('#include "SchM_cfg.h"\n')
    fp.write('/* ============================ [ MACROS    ] ====================================================== */\n')
    fp.write('#define J1939TP_VERSION_INFO_API        STD_%s\n'%(GAGet(General,'VersionInfoApi')))
    fp.write('#define J1939TP_DEV_ERROR_DETECT        STD_%s\n'%(GAGet(General,'DevelopmentErrorDetection')))
    fp.write('#define J1939TP_MAIN_FUNCTION_PERIOD MAIN_FUNCTION_PERIOD(J1939TP)\n')
    fp.write('#define J1939TP_TX_CONF_TIMEOUT MIAN_FUNCTION_MS2TICKS(J1939TP,%s)\n'%(GAGet(General,'TX_CONF_TIMEOUT')))
    fp.write('#define J1939TP_PACKETS_PER_BLOCK %s\n\n'%(GAGet(General,'PACKETS_PER_BLOCK')))
    ChannelList = GLGet('ChannelList')
    rxList = []
    txList = []
    for id,chl in enumerate(ChannelList):
        fp.write('#define J1939TP_CHL_%s %s\n'%(GAGet(chl,'Name'), id))
        if(GAGet(chl,'Direction') == 'RX'):
            rxList.append((chl))
        else:
            txList.append((chl))
    PduInfoList = GLGet('PduInfoList')
    ParameterGroupList = GLGet('ParameterGroupList')
    fp.write('#define J1939TP_TX_CHANNEL_COUNT %s\n'%(len(txList)))
    fp.write('#define J1939TP_RX_CHANNEL_COUNT %s\n'%(len(rxList)))
    fp.write('#define J1939TP_CHANNEL_COUNT (J1939TP_TX_CHANNEL_COUNT+J1939TP_RX_CHANNEL_COUNT)\n\n')
    for id,pdu in enumerate(PduInfoList):
        fp.write('#define J1939TP_ID_%s %s\n'%(GAGet(pdu,'Name'), id))
    fp.write('#define J1939TP_RX_PDU_COUNT %s\n\n'%(len(PduInfoList)))
    for id,pg in enumerate(ParameterGroupList):
        fp.write('#define J1939TP_PGID_%s %s\n'%(GAGet(pg,'Name'), id))
        fp.write('#define J1939TP_ID_%s %s\n'%(GAGet(pg,'NSdu'), id))
    fp.write('#define J1939TP_PG_COUNT %s\n\n'%(len(ParameterGroupList)))
    fp.write('/* ============================ [ TYPES     ] ====================================================== */\n')
    fp.write('/* ============================ [ DECLARES  ] ====================================================== */\n')
    fp.write('/* ============================ [ DATAS     ] ====================================================== */\n')
    fp.write('/* ============================ [ LOCALS    ] ====================================================== */\n')
    fp.write('/* ============================ [ FUNCTIONS ] ====================================================== */\n')
    fp.write('#endif /* J1939TP_CFG_H */\n')
    fp.close();

def GenC():
    global __dir
    fp = open('%s/J1939Tp_Cfg.c'%(__dir),'w')
    fp.write(GHeader('J1939Tp'))
    fp.write('#ifdef USE_J1939TP\n')
    fp.write('/* ============================ [ INCLUDES  ] ====================================================== */\n')
    fp.write('#include "J1939Tp.h"\n')
    fp.write('#include "PduR.h"\n')
    fp.write('#include "CanIf.h"\n')
    ChannelList = GLGet('ChannelList')
    PduInfoList = GLGet('PduInfoList')
    ParameterGroupList = GLGet('ParameterGroupList')
    fp.write('/* ============================ [ MACROS    ] ====================================================== */\n')
    fp.write('#define J1939TP_TBD -1\n')
    fp.write('/* ============================ [ TYPES     ] ====================================================== */\n')
    fp.write('/* ============================ [ DECLARES  ] ====================================================== */\n')
    fp.write('/* ============================ [ DATAS     ] ====================================================== */\n')
    fp.write('static const J1939Tp_PgType J1939Tp_Pgs[];\n')
    for chl in ChannelList:
        fp.write('static const J1939Tp_PgType* J1939Tp_PgsRefs_%s[] =\n{\n'%(GAGet(chl,'Name')))
        for id,pg in enumerate(ParameterGroupList):
            if(GAGet(pg,'Channel') == GAGet(chl,'Name')):
                fp.write('\t&J1939Tp_Pgs[%d],\n'%(id));
        fp.write('\tNULL')
        fp.write('};\n\n')
    fp.write('static const J1939Tp_ChannelType J1939Tp_Channels[] =\n{\n')
    for chl in ChannelList:
        FcNPdu = -1
        if(GAGet(chl,'Protocol')=='CMDT'):
            FcNPdu = 'CANIF_ID_%s'%(GAGet(chl,'FcNPdu'))
        fp.write('\t{\n')
        fp.write('\t\t.Protocol = J1939TP_PROTOCOL_%s,\n'%(GAGet(chl,'Protocol')))
        fp.write('\t\t.DtNPdu = CANIF_ID_%s,\n'%(GAGet(chl,'DtNPdu')))
        fp.write('\t\t.CmNPdu = CANIF_ID_%s,\n'%(GAGet(chl,'CmNPdu')))
        fp.write('\t\t.CmNPdu = CANIF_ID_%s,\n'%(GAGet(chl,'CmNPdu')))
        fp.write('\t\t.FcNPdu = %s,\n'%(FcNPdu))
        fp.write('\t\t.Direction = J1939TP_%s,\n'%(GAGet(chl,'Direction')))
        fp.write('\t\t.PgCount = (sizeof(J1939Tp_PgsRefs_%s)/sizeof(J1939Tp_PgType*)-1),\n'%(GAGet(chl,'Name')))
        fp.write('\t\t.Pgs = J1939Tp_PgsRefs_%s,\n'%(GAGet(chl,'Name')))
        fp.write('\t},\n')
    fp.write('};\n\n')
    fp.write('static const J1939Tp_PgType J1939Tp_Pgs[] =\n{\n')
    for pg in ParameterGroupList:
        DirectNPdu = -1
        if(GAGet(pg,'DynLength').upper() == 'TRUE'):
            DirectNPdu = 'CANIF_ID_%s'%(GAGet(pg,'DirectNPdu'))
        fp.write('\t{\n')
        fp.write('\t\t.DynLength = %s,\n'%(GAGet(pg,'DynLength').upper()))
        fp.write('\t\t.Pgn = %s,\n'%(GAGet(pg,'PgnType')))
        fp.write('\t\t.DirectNPdu = %s,\n'%(DirectNPdu))
        fp.write('\t\t.NSdu = PDUR_ID_%s,\n'%(GAGet(pg,'NSdu')))
        fp.write('\t\t.Channel = &J1939Tp_Channels[J1939TP_CHL_%s]\n'%(GAGet(pg,'Channel')))
        fp.write('\t},\n')
    fp.write('};\n\n')
    fp.write('static const J1939Tp_RxPduInfoType J1939Tp_RxPdus[] =\n{\n')
    for pdu in PduInfoList:
        fp.write('\t{\n')
        fp.write('\t\t.PacketType = J1939TP_%s,\n'%(GAGet(pdu,'PacketType')))
        fp.write('\t\t.ChannelIndex = J1939TP_CHL_%s,\n'%(GAGet(pdu,'Channel')))
        fp.write('\t\t.PgPtr = &J1939Tp_Pgs[J1939TP_PGID_%s]\n'%(GAGet(pdu,'ParameterGroup')))
        fp.write('\t},\n')
    fp.write('};\n\n')
    fp.write('static const J1939Tp_RxPduInfoType* J1939Tp_RxPdusRefs[] =\n{\n')
    for id,pdu in enumerate(PduInfoList):
        fp.write('\t&J1939Tp_RxPdus[%s],\n'%(id))
    fp.write('};\n\n')
    fp.write('static const J1939Tp_RxPduInfoRelationsType J1939Tp_RxPduRelations[] =\n{\n')
    for id,pdu in enumerate(PduInfoList):
        fp.write('\t{\n')
        fp.write('\t\t.RxPdus = &J1939Tp_RxPdusRefs[%s],\n'%(id))
        fp.write('\t\t.RxPduCount = 1\n')
        fp.write('\t},\n')
    fp.write('};\n\n')
    fp.write('const J1939Tp_ConfigType J1939Tp_Config =\n{\n')
    fp.write('\t.RxPduRelations = J1939Tp_RxPduRelations,\n')
    fp.write('\t.Channels = J1939Tp_Channels,\n')
    fp.write('\t.Pgs = J1939Tp_Pgs\n')
    fp.write('};\n')
    fp.write('/* ============================ [ LOCALS    ] ====================================================== */\n')
    fp.write('/* ============================ [ FUNCTIONS ] ====================================================== */\n')
    fp.write('#endif /* USE_J1939TP */\n')
    fp.close();