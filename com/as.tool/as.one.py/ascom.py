__lic__ = '''
/**
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
from PyQt5 import QtCore, QtGui
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from pyas.signal import *

__all__ = ['UICom']

class UIMsg(QScrollArea):
    def __init__(self, msg, parent=None):
        super(QScrollArea, self).__init__(parent)
        self.msg = msg
        wd = QWidget()
        grid = QGridLayout()
        self.leData = {}
        row = col = 0
        for sig in self.msg:
            grid.addWidget(QLabel(sig['name']), row, col)
            self.leData[sig['name']] = QLineEdit('0')
            grid.addWidget(self.leData[sig['name']], row, col+1)
            col += 2
            if(col > 3):
                col = 0
                row += 1
        row += 1
        if(self.msg.IsTransmit()):
            grid.addWidget(QLabel('period(ms):'), row, 0)
            self.lePeriod = QLineEdit('%s'%(self.msg.get_period()))
            grid.addWidget(self.lePeriod, row, 1)
            self.btnUpdate = QPushButton('update')
            self.btnUpdate.setToolTip('if period is 0, will update message and send it once\n'
                                      'if period is not 0, will only update the period and message value')
            grid.addWidget(self.btnUpdate, row, 2)
            self.btnUpdate.clicked.connect(self.on_btnUpdate_clicked)
        else:
            for sig in self.msg:
                self.leData[sig['name']].setReadOnly(True)
        wd.setLayout(grid)
        self.setWidget(wd)

    def toInteger(self, strnum):
        if(strnum.find('0x')!=-1 or strnum.find('0X')!=-1):
            return int(strnum,16)
        else:
            return int(strnum,10)

    def updateMsg(self):
        for sig in self.msg:
            try:
                sig.set_value(self.toInteger(str(self.leData[sig['name']].text())))
            except ValueError:
                pass # as just type '0x' maybe
        period = self.toInteger(str(self.lePeriod.text()))
        self.msg.set_period(period)

    def on_btnUpdate_clicked(self):
        self.updateMsg()
        if(self.msg.get_period() == 0):
            self.msg.transmit()

    def Period(self):
        if(self.msg.IsTransmit()):
            self.updateMsg()
        else:
            for sig in self.msg:
                self.leData[sig['name']].setText('%s(%s)'%(hex(sig.get_value()), sig.get_value()))

class UICom(QWidget):
    def __init__(self, parent=None):
        super(QWidget, self).__init__(parent)
        self.vbox = QVBoxLayout()

        hbox = QHBoxLayout()
        hbox.addWidget(QLabel('load CAN database:'))
        self.leDbc= QLineEdit()
        hbox.addWidget(self.leDbc)
        self.btnOpenDbc = QPushButton('...')
        hbox.addWidget(self.btnOpenDbc)

        self.vbox.addLayout(hbox)
        self.tabWidget = QTabWidget(self)
        self.vbox.addWidget(self.tabWidget)

        self.setLayout(self.vbox)

        self.network = None
        self.btnOpenDbc.clicked.connect(self.on_btnOpenDbc_clicked)

    def __del__(self):
        if(self.network != None):
            self.network.stop()

    def timerEvent(self, ev):
        for key, msg in self.msgs.items():
            msg.Period()

    def on_btnOpenDbc_clicked(self):
        rv = QFileDialog.getOpenFileName(None,'Vector CAN database', '','CAN database (*.dbc)')
        if(rv[0] != ''):
            self.leDbc.setText(rv[0])
            self.loadDbc(rv[0])

    def loadDbc(self,dbc):
        self.tabWidget.clear()
        if(self.network != None):
            self.network.stop()
        self.network = Network(dbc)
        self.msgs = {}
        for msg in self.network:
            self.msgs[msg.attrib('name')] = UIMsg(msg)
            self.tabWidget.addTab(self.msgs[msg.attrib('name')], msg.attrib('name'))

        self.startTimer(100)


