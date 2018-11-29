__lic__ = '''
/**
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
from PyQt5 import QtCore, QtGui
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from pyas.can import *
import sys

__all__ = ['UICan']

class UICan(QWidget):
    bus_num = 4
    def __init__(self, parent=None):
        super(QWidget, self).__init__(parent)

        vbox = QVBoxLayout()

        grid = QGridLayout()
        
        self.cmbxCanBus = []
        self.cmbxCanDevice = []
        self.cmbxCanPort = []
        self.cmbxCanBaud = []
        self.btnOpen = []
        self.online=[]

        opens = [self.on_btnOpenClicked_0,self.on_btnOpenClicked_1,self.on_btnOpenClicked_2,self.on_btnOpenClicked_3]

        for i in range(self.bus_num):
            self.cmbxCanBus.append(QComboBox())
            self.cmbxCanDevice.append(QComboBox())
            self.cmbxCanPort.append(QComboBox())
            self.cmbxCanBaud.append(QComboBox())
            self.btnOpen.append(QPushButton('Open'))
            
            self.cmbxCanBus[i].addItems(['bus 0','bus 1','bus 2','bus 3','bus 4','bus 5','bus 6','bus 7'])
            self.cmbxCanDevice[i].addItems(['socket','serial','vxl','peak','tcp','zlg'])
            self.cmbxCanPort[i].addItems(['port 0','port 1','port 2','port 3','port 4','port 5','port 6','port 7'])
            self.cmbxCanPort[i].setToolTip('for serial: e.g COM5 = port 4, support from COM1 to COM16')
            self.cmbxCanBaud[i].addItems(['125000','250000','500000','1000000','115200'])

            self.cmbxCanBus[i].setEditable(True)
            self.cmbxCanPort[i].setEditable(True)
            self.cmbxCanBaud[i].setEditable(True)
            
            self.cmbxCanBus[i].setCurrentIndex(i)
            self.cmbxCanDevice[i].setCurrentIndex(i)
            if(i==1):
                self.cmbxCanBaud[i].setCurrentIndex(4)
            else:
                self.cmbxCanBaud[i].setCurrentIndex(3)

            grid.addWidget(QLabel('Can:'),i,0)
            grid.addWidget(self.cmbxCanBus[i],i,1)
            grid.addWidget(self.cmbxCanDevice[i],i,2)
            grid.addWidget(self.cmbxCanPort[i],i,3)
            grid.addWidget(self.cmbxCanBaud[i],i,4)
            grid.addWidget(self.btnOpen[i],i,5)

            self.btnOpen[i].clicked.connect(opens[i])
            self.online.append(False)
        hbox = QHBoxLayout()
        hbox.addWidget(QLabel('BUS ID:'))
        self.leBusID = QLineEdit()
        self.leBusID.setMaximumWidth(60)
        self.leBusID.setText('0')
        hbox.addWidget(self.leBusID)
        hbox.addWidget(QLabel('CAN ID:'))
        self.leCanID = QLineEdit()
        self.leCanID.setMaximumWidth(120)
        self.leCanID.setText('102')
        self.leCanID.setStatusTip('hex value')
        hbox.addWidget(self.leCanID)
        hbox.addWidget(QLabel('DATA:'))
        self.leCanData = QLineEdit()
        self.leCanData.setText('1122334455667788')
        hbox.addWidget(self.leCanData)
        hbox.addWidget(QLabel('PERIOD:'))
        self.leCanPeriod = QLineEdit()
        self.leCanPeriod.setText('0')
        hbox.addWidget(self.leCanPeriod)
        self.leCanPeriod.setMaximumWidth(120)
        self.btnSend = QPushButton('Send')
        hbox.addWidget(self.btnSend)
        self.btnSend.clicked.connect(self.on_btnSend_clicked)

        self.canTrace = QTextEdit()
        self.canTrace.setReadOnly(True)
        self.canTraceEnable = QCheckBox("CAN trace log enable")
        self.canTraceEnable.setChecked(False)
        vbox.addLayout(grid)
        vbox.addLayout(hbox)
        vbox.addWidget(self.canTraceEnable)
        vbox.addWidget(self.canTrace)
        self.canTraceEnable.stateChanged.connect(self.on_canTraceEnable_stateChanged)
        self.setLayout(vbox)

        self.canSendTimer = None
        self.traceTimer = None

    def canSend(self):
        canid = int(str(self.leCanID.text()),16)
        busid = int(str(self.leBusID.text()),10)
        data = str(self.leCanData.text())
        rdata = []
        for i in range(int(len(data)/2)):
            rdata.append(int(data[2*i:2*i+2],16))
        can_write(busid, canid, rdata)

    def on_btnSend_clicked(self):
        period = int(str(self.leCanPeriod.text()),10)
        if(period > 0):
            if(self.canSendTimer != None):
                self.killTimer(self.canSendTimer)
            self.canSendTimer = self.startTimer(period)
        self.canSend()

    def on_canTraceEnable_stateChanged(self, state):
        if(state):
            self.traceTimer = self.startTimer(1)
            self.timeTick = 0
        else:
            self.killTimer(self.traceTimer)
            self.traceTimer = None

    def timerEvent(self,ev):
        if(ev.timerId() == self.traceTimer):
            self.onTraceTimerEvent()
        elif(ev.timerId() == self.canSendTimer):
            self.canSend()
            period = int(str(self.leCanPeriod.text()),10)
            if(period == 0):
                self.killTimer(self.canSendTimer)
                self.canSendTimer = None
        else:
            assert(0)

    def onTraceTimerEvent(self):
        self.timeTick += 1
        for bus in range(self.bus_num):
            if(self.online[bus]):
                ercd,canid,data = can_read(bus,-2)
                if(ercd):
                    cstr = 'bus=%s canid=%03X data=['%(bus,canid)
                    for d in data:
                        cstr += ' %02X'%(d)
                    cstr += '] @ %d ms'%(self.timeTick)
                    self.canTrace.append(cstr)

    def on_btnOpen(self,id):
        if(str(self.btnOpen[id].text())=='Open'):
            bus = int(str(self.cmbxCanBus[id].currentText()).replace('bus',''))
            device = str(self.cmbxCanDevice[id].currentText())
            if(device == 'tcp'):
                device = "serial" # special treatment for QEMU serial tcp:127.0.0.1:1103 
                port = 0x746370
            else:
                port = int(str(self.cmbxCanPort[id].currentText()).replace('port',''))
            baud = int(str(self.cmbxCanBaud[id].currentText()))
            can_open(bus,device,port,baud)
            self.btnOpen[id].setText('Close')
            self.online[id] = True
        else:
            bus = int(str(self.cmbxCanBus[id].currentText()).replace('bus',''))
            can_close(bus)
            self.btnOpen[id].setText('Open')
            self.online[id] = False
    
    def on_btnOpenClicked_0(self):
        self.on_btnOpen(0)
        
    def on_btnOpenClicked_1(self):
        self.on_btnOpen(1)
        
    def on_btnOpenClicked_2(self):
        self.on_btnOpen(2)
        
    def on_btnOpenClicked_3(self):
        self.on_btnOpen(3)
