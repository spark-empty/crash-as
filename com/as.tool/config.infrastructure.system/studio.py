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
from PyQt5 import QtCore, QtGui
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
import sys,os
from arxml.Argui import *
from arxml.Arxml import *
from argen.ArGen import *
import xml.etree.ElementTree as ET
import importlib.util
import glob

__all__ = ['easySAR']

gDefault_GEN = '..'

class easyDockWidget(QDockWidget):
    isClosed = False
    def __init__(self,title,parent=None):
        QDockWidget.__init__(self,title,parent)
        self.setAllowedAreas(QtCore.Qt.LeftDockWidgetArea|QtCore.Qt.RightDockWidgetArea)  
        #self.setFeatures(QDockWidget.DockWidgetClosable|QDockWidget.DockWidgetMovable)
    def closeEvent(self,event):
        self.isClosed = True

class easySARGui(QMainWindow):
    def __init__(self):
        global gDefault_GEN
        self.modules = []
        self.docks   = []
        self.actions = []
        self.pdir = ''

        QMainWindow.__init__(self, None)
        self.setWindowTitle('easy OpenSAR Studio( parai@foxmail.com ^_^ @ %s)'%(gDefault_GEN));
        self.setMinimumSize(800, 400)

        self.creStatusBar()
        self.systemDescriptor = ET.parse('./arxml/easySAR.arxml').getroot()
        self.creMenu()
        self.loadPlugins()
        # try to open a default configuration file
        self.mOpen(gDefault_GEN)

        self.showMaximized()

    def loadPlugins(self):
        tMenu=self.menuBar().addMenu(self.tr('Plugin'))
        plgdir = os.path.abspath('./plugin')
        for plg in glob.glob('%s/*.py'%(plgdir)):
            plgName = os.path.basename(plg)[:-3]
            spec = importlib.util.spec_from_file_location(plgName, plg)
            plgM = importlib.util.module_from_spec(spec)
            spec.loader.exec_module(plgM)
            sItem=plgM.Plugin(self)
            tMenu.addAction(sItem)

    def creMenu(self):
        # File
        tMenu=self.menuBar().addMenu(self.tr('File'))
        ## Open Ctrl+O  
        sItem=QAction(self.tr('Open'),self) 
        sItem.setShortcut('Ctrl+O'); 
        sItem.setStatusTip('Open a OpenSAR configure file.')
        sItem.triggered.connect(self.mOpen)
        tMenu.addAction(sItem) 
        ## Save Ctrl+S
        sItem=QAction(self.tr('Save'),self) 
        sItem.setShortcut('Ctrl+S'); 
        sItem.setStatusTip('Save the OpenSAR configure file.')
        sItem.triggered.connect(self.mSave) 
        tMenu.addAction(sItem)  
        ## Save Ctrl+G
        sItem=QAction(self.tr('Generate'),self) 
        sItem.setShortcut('Ctrl+G'); 
        sItem.setStatusTip('Convert the OpenSAR configure file to C Code.')
        sItem.triggered.connect(self.mGen)  
        tMenu.addAction(sItem)
        # easySAR Module
        tMenu=self.menuBar().addMenu(self.tr('Module'))
        for desc in self.systemDescriptor:
            sItem=ArgAction(self.tr(desc.tag),self) 
            sItem.setStatusTip('Open easy%s console.'%(desc.tag)) 
            tMenu.addAction(sItem)
            module = ArgModule(Arxml(desc),self)
            self.modules.append(module)
            self.docks.append(None)

    def removeXml(self, L, R):
        rl = []
        for r in L:
            if(r.attrib['Name'] in R):
                rl.append(r)
        for r in rl:
            L.remove(r)

    def getModule(self, name):
        for module in self.modules:
            if(name == module.tag):
                return module
        return None

    def getURL(self,ref):
        ar = ET.Element('AUTOSAR')
        for module in self.modules:
            ar.append(module.toArxml())
        return ArxmlGetURL(ar,ref)

    def mOpen(self,default=None):
        if(default == None):
            self.pdir = QFileDialog.getExistingDirectory(None,'Open OpenSAR Config',gDefault_GEN,QFileDialog.DontResolveSymlinks)
            if(self.pdir == ''):
                return
        else:
            self.pdir = default
        wfxml = '%s/autosar.arxml'%(self.pdir)
        if(os.path.exists(wfxml)==False):
            return
        root = ET.parse(wfxml).getroot();
        for module in self.modules:
            if(root.find(module.tag) != None):
                module.reloadArxml(Arxml(self.systemDescriptor.find(module.tag),
                                         root.find(module.tag)))
                self.onAction(module.tag)
        if(default == None):
            QMessageBox(QMessageBox.Information, 'Info', 
                        'Open OpenSAR Configuration arxml Successfully !').exec_();
    def mSave(self, alt=''):
        if(self.pdir == ''):
            self.pdir = QFileDialog.getExistingDirectory(None,'Save OpenSAR Configuration',gDefault_GEN,QFileDialog.DontResolveSymlinks)
        if(self.pdir == ''):
            return
        if(alt == False):
            alt = ''
        wfxml = '%s/autosar%s.arxml'%(self.pdir,alt)
        ROOT = ET.Element('AUTOSAR')
        for module in self.modules:
            ROOT.append(module.toArxml())
        tree = ET.ElementTree(ROOT)
        tree.write(wfxml, encoding="utf-8", xml_declaration=True);
        fp = open(wfxml,'r')
        content = fp.read()
        fp.close()
        fp = open(wfxml,'w')
        fp.write(content.replace('>','>\n'))
        fp.close()
        print('!!!Saving to %s done!!!'%(wfxml))
        QMessageBox(QMessageBox.Information, 'Info', 
                    'Save OpenSAR Configuration arxml Successfully !').exec_();
    def mGen(self):
        if(self.pdir == ''):
            QMessageBox(QMessageBox.Information, 'Info', 
                        'Open or Configure a Workspace first !').exec_();
            return
        for module in self.modules:
            ArGen(module.toArxml(),self.pdir, False)
        QMessageBox(QMessageBox.Information, 'Info', 
                        'Generate OpenSAR Configuration C Code Successfully !\n<%s>\n'%(self.pdir)).exec_();
    def onAction(self,text):
        I = 0
        for module in self.modules:
            if(text == module.tag):
                break
            else:
                I += 1
        if(I >= len(self.modules)):
            return
        
        if(self.docks[I]==None):
            self.docks[I] = easyDockWidget(self.modules[I].tag, self)  
            self.docks[I].setWidget(self.modules[I])  
            self.addDockWidget(QtCore.Qt.RightDockWidgetArea, self.docks[I])
        elif(self.docks[I].isClosed==True):
            self.docks[I] = easyDockWidget(self.modules[I].tag, self)  
            self.docks[I].setWidget(self.modules[I])  
            self.addDockWidget(QtCore.Qt.RightDockWidgetArea, self.docks[I])
        else:
            print('%s already started.'%(self.modules[I].tag))
             
        J=I-1
        if(I==0):
            J=1
        if(self.docks[J]!=None):
            self.tabifyDockWidget(self.docks[J],self.docks[I]) 
    def creStatusBar(self):
        self.statusBar = QStatusBar()
        self.setStatusBar(self.statusBar)
        self.statusBar.showMessage('easy OpenSAR Studio Platform',0)
        
def easySAR():
    qtApp = QApplication(sys.argv)
    if(os.name == 'nt'):
        qtApp.setFont(QFont('Consolas')) 
    elif(os.name == 'posix'):
        qtApp.setFont(QFont('Monospace'))
    else:
        print('unKnown platform.')
    qtGui = easySARGui()
    qtGui.show()
    qtApp.exec_()
    

if(__name__ == '__main__'):
    if(len(sys.argv)==2):
        gDefault_GEN = sys.argv[1]
    easySAR()