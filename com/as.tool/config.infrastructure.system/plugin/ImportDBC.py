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
from arxml.Arxml import *
import xml.etree.ElementTree as ET

class Plugin(QAction):
    def __init__(self, root):
        self.root = root
        super(QAction,self).__init__(root.tr('Import Vector CAN DBC Sinals'), root)
        self.setStatusTip('Import Vector CAN DBC Sinals.')
        self.triggered.connect(self.onAction)

    def onAction(self):
        self.mImportVectorCANDBCSignals()

    def parseCANDBC(self, dbc):
        pydbc = os.path.abspath('../py.can.database.access/ascc')
        assert(os.path.exists(pydbc))
        sys.path.append(pydbc)
        import cc.ascp as ascp
        return ascp.parse(dbc)

    def modifyEcuCbyCANDBC(self, dbc):
        self.root.onAction('EcuC')
        ecuc = self.root.getModule('EcuC')
        arxml = ecuc.toArxml()
        R = []
        for msg in dbc['boList']:
            R.append(msg['bo']['name'])
        PduList = arxml.find('PduList')
        self.root.removeXml(PduList, R)
        for msg in dbc['boList']:
            pdu = ET.Element('Pdu')
            pdu.attrib['Name'] = msg['bo']['name']
            pdu.attrib['Size'] = str(msg['bo']['length']*8)
            PduList.append(pdu)
        ecuc.reloadArxml(Arxml(self.root.systemDescriptor.find('EcuC'),arxml))

    def modifyCanIfbyCANDBC(self, dbc, bus):
        self.root.onAction('CanIf')
        for s in [' ','-']:
            bus = bus.replace(s,'')
        canif = self.root.getModule('CanIf')
        arxml = canif.toArxml()
        chlList = arxml.find('ChannelList')
        chl = None
        for c in chlList:
            if(c.attrib['Name'] == bus):
                chl = c
                break
        if(chl is None):
            chl = ET.Element('Channel')
            chl.attrib['Name']=bus
            chl.append(ET.Element('HthList'))
            chl.append(ET.Element('HrhList'))
            chl.append(ET.Element('TxPduList'))
            chl.append(ET.Element('RxPduList'))
            chlList.append(chl)
        rxList = []
        rR = []
        txList = []
        tR = []
        for msg in dbc['boList']:
            msg = msg['bo']
            if(msg['node'] == self.CAN_SELF_DBC_NODE):
                txList.append(msg)
                tR.append(msg['name'])
            else:
                rxList.append(msg)
                rR.append(msg['name'])
        TxPduList = chl.find('TxPduList')
        RxPduList = chl.find('RxPduList')
        self.root.removeXml(TxPduList, tR)
        self.root.removeXml(RxPduList, rR)
        def appendPduList(pduList, xList):
            for msg in xList:
                pdu = ET.Element('Pdu')
                pdu.attrib['Name'] = msg['name']
                pdu.attrib['EcuCPduRef'] = msg['name']
                pdu.attrib['DataLengthCode'] = str(msg['length'])
                pdu.attrib['Identifier'] = str(msg['id'])
                pduList.append(pdu)
        appendPduList(TxPduList, txList)
        appendPduList(RxPduList, rxList)
        canif.reloadArxml(Arxml(self.root.systemDescriptor.find('CanIf'),arxml))

    def modifyPduRbyCANDBC(self, dbc):
        self.root.onAction('PduR')
        pdur = self.root.getModule('PduR')
        arxml = pdur.toArxml()
        R = []
        for msg in dbc['boList']:
            R.append(msg['bo']['name'])
        RoutineList = arxml.find('RoutineList')
        self.root.removeXml(RoutineList, R)
        for msg in dbc['boList']:
            msg = msg['bo']
            src = ET.Element('Source')
            src.attrib['Name'] = msg['name']
            src.attrib['PduRef'] = msg['name']
            if(msg['node'] == self.CAN_SELF_DBC_NODE):
                src.attrib['Module'] = 'Com'
            else:
                src.attrib['Module'] = 'CanIf'
            dlist = ET.Element('DestinationList')
            dst = ET.Element('Destination')
            dst.attrib['Name'] = msg['name']
            dst.attrib['PduRef'] = msg['name']
            if(msg['node'] == self.CAN_SELF_DBC_NODE):
                dst.attrib['Module'] = 'CanIf'
            else:
                dst.attrib['Module'] = 'Com'
            dlist.append(dst)
            src.append(dlist)
            RoutineList.append(src)
            pdur.reloadArxml(Arxml(self.root.systemDescriptor.find('PduR'),arxml))

    def modifyCombyCANDBC(self, dbc):
        self.root.onAction('Com')
        com = self.root.getModule('Com')
        arxml = com.toArxml()
        R = []
        for msg in dbc['boList']:
            R.append(msg['bo']['name'])
        IPduList = arxml.find('IPduList')
        self.root.removeXml(IPduList, R)
        print('WARNING: This plugin only support BIG_ENDIAN(Motorola) Format signals')
        for msg in dbc['boList']:
            msg = msg['bo']
            ipdu = ET.Element('IPdu')
            ipdu.attrib['Name'] = msg['name']
            ipdu.attrib['PduRef'] = msg['name']
            if(msg['node'] == self.CAN_SELF_DBC_NODE):
                ipdu.attrib['Direction'] = 'SEND'
            else:
                ipdu.attrib['Direction'] = 'RECEIVE'
            slist = ET.Element('SignalList')
            for sg in msg['sgList']:
                sg = sg['sg']
                sig = ET.Element('Signal')
                sig.attrib['Name'] = sg['name']
                sig.attrib['Endianess'] = 'BIG_ENDIAN'
                sig.attrib['StartBit'] = str(sg['start'])
                sig.attrib['Size'] = str(sg['size'])
                try: 
                    sig.attrib['InitialValue'] = str(sg['init']) 
                except KeyError:
                    pass
                slist.append(sig)
            ipdu.append(slist)
            IPduList.append(ipdu)
        com.reloadArxml(Arxml(self.root.systemDescriptor.find('Com'),arxml))

    def mImportVectorCANDBCSignals(self):
        self.CAN_SELF_DBC_NODE = 'AS'
        if(os.getenv('CAN_SELF_DBC_NODE') is not None):
            self.CAN_SELF_DBC_NODE = os.getenv('CAN_SELF_DBC_NODE')
        dbc,_ = QFileDialog.getOpenFileName(None,'Open Vector CAN DBC',
                                '', '*.dbc','*.dbc',
                                QFileDialog.DontResolveSymlinks)
        if(os.path.exists(dbc)):
            bus = os.path.basename(dbc)[:-4]
            dbc = self.parseCANDBC(dbc)
            self.modifyEcuCbyCANDBC(dbc)
            self.modifyCanIfbyCANDBC(dbc,bus)
            self.modifyPduRbyCANDBC(dbc)
            self.modifyCombyCANDBC(dbc)
        self.root.mSave('-import-dbc')
        print('!!!Importing Done!!!')
