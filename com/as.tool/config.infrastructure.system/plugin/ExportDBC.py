'''/**
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
from PyQt5 import QtCore, QtGui
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from argen.GCF import *

_dbc_header = '''VERSION "HNPBNNNYYNYNNYYNNNNNNNNNNNNNNNYNNNNYNNNNNN/4/%%%/4/'%**4NNN///"


NS_ : 
    NS_DESC_
    CM_
    BA_DEF_
    BA_
    VAL_
    CAT_DEF_
    CAT_
    FILTER
    BA_DEF_DEF_
    EV_DATA_
    ENVVAR_DATA_
    SGTYPE_
    SGTYPE_VAL_
    BA_DEF_SGTYPE_
    BA_SGTYPE_
    SIG_TYPE_REF_
    VAL_TABLE_
    SIG_GROUP_
    SIG_VALTYPE_
    SIGTYPE_VALTYPE_
    BO_TX_BU_
    BA_DEF_REL_
    BA_REL_
    BA_DEF_DEF_REL_
    BU_SG_REL_
    BU_EV_REL_
    BU_BO_REL_
    SG_MUL_VAL_

BS_:

BU_: AS Other\n'''
class Plugin(QAction):
    def __init__(self, root):
        self.root = root
        super(QAction,self).__init__(root.tr('Export as Vector CAN DBC'), root)
        self.setStatusTip('Export COM signals as Vector CAN DBC')
        self.triggered.connect(self.onAction)

    def GetSigPos(self, sig):
        Size = Integer(GAGet(sig, 'Size'))
        StartBit = Integer(GAGet(sig, 'StartBit'))
        return StartBit, Size

    def GenBO(self, fp, canifPdu, comPdu):
        if(canifPdu['dir'] == 'Tx'):
            node = 'AS'
        else:
            node = 'Other'
        pdu = canifPdu['pdu']
        fp.write('\nBO_ %s %s: %s %s\n'%(Integer(pdu.attrib['Identifier']),
                                     pdu.attrib['EcuCPduRef'],
                                     pdu.attrib['DataLengthCode'],node))
        for gsigL in GLGet(comPdu, 'GroupSignalList'):
            for gsig in GLGet(gsigL, 'SignalList'):
                StartBit, Size = self.GetSigPos(gsig)
                if(GAGet(gsig, 'Endianess') == 'BIG_ENDIAN'):
                    endian = 0
                else:
                    endian = 1
                fp.write('SG_ %s_%s : %s|%s@%s+ (1,0) [0|4294967295] "" %s\n'%(
                    GAGet(gsigL,'Name'), GAGet(gsig, 'Name'),
                    StartBit, Size, endian, node))
        for sig in GLGet(comPdu,'SignalList'):
            StartBit, Size = self.GetSigPos(sig)
            if(GAGet(sig, 'Endianess') == 'BIG_ENDIAN'):
                endian = 0
            else:
                endian = 1
            fp.write('SG_ %s : %s|%s@%s+ (1,0) [0|4294967295] "" %s\n'%(
                    GAGet(sig, 'Name'), StartBit, Size, endian, node))

    def onAction(self):
        com = self.root.getModule('Com').toArxml()
        canif = self.root.getModule('CanIf').toArxml()
        dbc = QFileDialog.getExistingDirectory(None,'Save as Vector CAN DBC', '.', QFileDialog.ShowDirsOnly)
        if(not os.path.exists(dbc)):
            return
        CANIF = {}
        for chl in canif.find('ChannelList'):
            CANIF[chl.attrib['Name']] = {}
            for pdu in chl.find('TxPduList'):
                CANIF[chl.attrib['Name']][pdu.attrib['EcuCPduRef']] = { 'pdu': pdu , 'dir':'Tx' }
            for pdu in chl.find('RxPduList'):
                CANIF[chl.attrib['Name']][pdu.attrib['EcuCPduRef']] = { 'pdu': pdu , 'dir':'Rx' }
        COM = {}
        for pdu in com.find('IPduList'):
            COM[pdu.attrib['PduRef']] = pdu
        for chl,val in CANIF.items():
            fp = open('%s/%s.dbc'%(dbc,chl),'w')
            fp.write(_dbc_header)
            for pduName, pdu in val.items():
                if(pduName in COM):
                    self.GenBO(fp, pdu, COM[pduName])
            fp.write('\n\n\n\n')
            fp.close()
        QMessageBox(QMessageBox.Information, 'Info', 
                    'Export COM signals as Vector CAN DBC Successfully !').exec_()
