#! /usr/bin/python3
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
import os,sys

sys.path.append(os.path.abspath('./pyas'))

from PyQt5 import QtCore, QtGui
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from asserial import UISerial
from pyas.flashloader import *
from pyas.ascan import *
from asdcm import *
from asxcp import *
from assg import *
from ascom import *

class AsAction(QAction):
    action=QtCore.pyqtSignal(str)
    def __init__(self,text,parent=None): 
        super(QAction,self).__init__(text,parent) 
        self.triggered.connect(self.onAction)
 
    def onAction(self):
        self.action.emit(self.text())

class Window(QMainWindow):
    UIList= {'Serial':UISerial,'Flashloader':UIFlashloader,'Can':UICan,'Dcm':UIDcm,'Xcp':UIXcp,
             'Sg':UISg, 'Com':UICom }
    def __init__(self, parent=None):
        super(QMainWindow, self).__init__(parent) 
        self.creGui()
        self.setWindowTitle("AsOne")

    def closeEvent(self,Event):
        pass

    def creMenu(self):
        # easySAR Module
        tMenu=self.menuBar().addMenu(self.tr('MyApp'))
        for name,ui in self.UIList.items():
            sItem=AsAction(self.tr(name),self) 
            sItem.action.connect(self.onAction)
            tMenu.addAction(sItem)

    def onAction(self,text):
        for i in range(self.tabWidget.count()):
            if(text == str(self.tabWidget.tabText(i))):
                return
        for name,ui in self.UIList.items():
            if(text == name):
                self.tabWidget.addTab(ui(), name)
                return

    def creGui(self):
        wid = QWidget()
        grid = QVBoxLayout()
        self.tabWidget = QTabWidget(self)
        grid.addWidget(self.tabWidget)
        wid.setLayout(grid)

        self.setCentralWidget(wid)
        self.creMenu()

        self.onAction('Can')
        self.onAction('Serial')
        self.onAction('Flashloader')
        self.onAction('Dcm')
        self.onAction('Xcp')
        self.onAction('Com')

        self.setMinimumSize(1200, 600)

def main():
    app = QApplication(sys.argv)
    if(os.name == 'nt'):
        app.setFont(QFont('Consolas')) 
    elif(os.name == 'posix'):
        app.setFont(QFont('Monospace'))
    else:
        print('unKnown platform.')
    mWain = Window()
    mWain.show()
    sys.exit(app.exec_()) 

if(__name__ == '__main__'):
    main()
