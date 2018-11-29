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
from serial import Serial
import time
from binascii import hexlify, unhexlify
import sys,re
from pyas.can import *

__all__ = ['UISerial','search_serial_ports','AsSerial']

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    _fromUtf8 = lambda s: s

class AsCommand():
    def __init__(self, serial):
        self.serial = serial
        self.cmdTracePre = None
        self.cmdList = []
        self.cmdPre = None
        self.taskList = []

    def append(self, cmd):
        self.cmdList.append(cmd)

    def __runcmd(self):
        cmd = self.cmdList.pop(0)
        pre = time.time()
        ercd,result=self.serial.runcmd(cmd)
        if(not ercd):
            self.serial.recv_msg.emit('run cmd %s failed\n'%(cmd))
            return
        now = time.time()
        if(self.cmdPre == None):
            elapsed = 'unknown'
        else:
            elapsed = now - self.cmdPre
        self.cmdPre = now
        if(cmd == 'trace'):
            result = self.__trace_result(result, now, pre)
        msg = 'since last command elapsed %.6s s, cmd "%s" cost %.6s s:\n%s\n'%(elapsed, cmd, now-pre,result)
        self.serial.recv_msg.emit(msg)

    def run(self):
        while(len(self.cmdList)>0):
            self.__runcmd()

    def __trace_result(self,result,now,pre):
        reMatch = re.compile(r'(\d+)\s+(\w+)\s+(\w+)\s+(\w+)\s+(\w+)\s+(\w+)')
        reTask = re.compile(r'^(\w+)\s+(\w+)\s+(\d+)\s+(\d+)\s+(\d+)')
        reFreq = re.compile(r'FREQ=(\d+)')
        if(len(self.taskList) == 0):
            ercd,msg = self.serial.runcmd('ps')
            if(ercd):
                for el in msg.split('\n'):
                    if(reTask.search(el)):
                        self.taskList.append(reTask.search(el).groups()[0])
        L = []
        maxL = 0
        for el in result.split('\n'):
            if(reFreq.search(el)):
                freq = int(reFreq.search(el).groups()[0])
            if(reMatch.search(el)):
                grp = reMatch.search(el).groups()
                id = int(grp[0])
                if(id < len(self.taskList)):
                    id = self.taskList[id]
                if(len(id)>maxL):
                    maxL = len(id)
                sum = float(int(grp[1],16)*(1<<32) +int(grp[2],16))/freq
                max = float(int(grp[3],16))/freq
                min = float(int(grp[4],16))/freq
                times = int(grp[5],16)
                L.append((id,sum,max,min,times))
        tall = 0
        for id,sum,max,min,times in L:
            tall += sum
        if(self.cmdTracePre == None):
            pass
        else:
            tall2 = now - self.cmdTracePre - (now-pre)
            if(tall2>tall):
                tall = tall2

        self.cmdTracePre = now

        usage = 0
        for id,sum,max,min,times in L:
            usage += sum/tall
        L.append(('Others(ISR...)',(1-usage)*tall,0,0,0))

        print('original trace result:\n',result)
        format = '%-'+str(maxL)+'s %-10s %-10s %-10s %-8s %s\n'
        rs = format%('ID','sum','max','min','times','CPU usage all=%.6ss'%(tall))
        for id,sum,max,min,times in L:
            rs += format%(id,'%-10.6f'%(sum),'%-10.6f'%(max),'%-10.6f'%(min),times,'%10.3f%%'%(100*sum/tall))
        return rs

class AsSerial(QThread):
    recv_msg = QtCore.pyqtSignal(str)
    toStr = lambda self,data: ''.join(['%c'%(c) for c in data])
    def __init__(self,parent=None):
        super(QThread, self).__init__(parent)
        self.isCANMode=False
        self.cmd = AsCommand(self)

    def open(self, settings, start=True):
        self.__terminate = False
        if(settings['port'] == 'CAN'):
            self.isCANMode = True
            self.start()
            return (True, 'success')
        try:
            self.serial = Serial(settings['port'], settings['baund'], settings['bytesize'],
                    settings['parity'], settings['stopbits'], settings['timeout'])
            self.serial.flushInput()
            self.serial.flushOutput()
        except:
            return (False, "%s"%(sys.exc_info()[1]))

        if(start == True):
            self.start()
        return (True, 'success')

    def runcmd(self,cmd,runNow=True):
        if(False == runNow):
            self.cmd.append(cmd)
            return True,None
        self.serial.flushOutput()
        self.serial.flushInput()
        if(cmd[-1] != '\n'):
            cmd += '\n'
        ercd = True
        result = ''
        reResult = re.compile(r'exit\((\d+)\)')
        for c in cmd:
            self.send(c)
            r = self.read()
            if(r != c):
                ercd = False
                result = 'bus error'
                break

        while(ercd):
            r = self.read(1, 5)
            if(r == None):
                ercd = False
                break
            result += r
            if('[AS] $' in result):
                result = result[:-6]
                if(reResult.search(result)):
                    r = reResult.search(result).groups()[0]
                    if(r != '0'):
                        ercd = False
                else:
                    ercd = False
                break
        return ercd, result

    def resetArduino(self):
        if(self.isCANMode): return
        self.serial.setDTR(0)
        time.sleep(0.1)
        self.serial.setDTR(1)

    def terminate(self):
        self.__terminate = True

    def send(self, data):
        if(self.isCANMode):
            index = 0
            pdu=[]
            for d in data:
                pdu.append(ord(d))
                index +=1
                if(index == 8):
                    ercd = can_write(0,0x701,pdu)
                    if(False == ercd):
                        print('Seial: send can message failed!')
                    index = 0
                    pdu = []
            if(index > 0):
                ercd = can_write(0,0x701,pdu)
                if(False == ercd):
                    print('Seial: send can message failed!')
            return
        if(type(data) != bytes):
            data = data.encode('utf-8')
        self.serial.write(data)

    def read(self,length=1, timeout=0.1):
        result = bytes()
        t = time.time()
        while(len(result) <length):
            data = self.serial.read(1)
            if(len(data) == 0):
                continue
            else:
                result += data
            if((time.time()-t) > timeout):
                return None
        return self.toStr(result)

    def __recv(self):
        data, quit = bytes(), False
        if(self.isCANMode): data = ''
        while(True):
            if(self.__terminate):
                break
            if(len(self.cmd.cmdList)>0):
                break
            if(self.isCANMode):
                # default on CAN bus0, CANID 0x702
                ercd,canid,d = can_read(0, 0x702)
                if(ercd):
                    for b in d:
                        data += '%c'%(b)
                        if('%c'%(b) =='\n'):
                            quit = True
                if(quit==True):
                    break
                continue
            data = self.serial.read(1)
            if(len(data) == 0):
                continue
            while(True):
                n = self.serial.inWaiting()
                if( n > 0):
                    data += self.serial.read(n)
                    time.sleep(0.02) # data is this interval will be merged
                else:
                    quit = True
                    break
            if(quit==True):
                break
        return self.toStr(data)

    def close(self):
        if(self.isCANMode): return
        if self.serial.isOpen():
            self.serial.close()

    def run(self):
        while(True):
            self.cmd.run()
            data = self.__recv()
            if(len(data) > 0):
                self.recv_msg.emit(data)
        if(self.isCANMode): return
        self.serial.close()  

def search_serial_ports():
    settings = {}
    settings['baund'] = 115200
    settings['bytesize'] = 8
    settings['parity']='N'
    settings['stopbits']=1
    settings['timeout'] = 0.1
    ports = []
    for i in range(0,100):
        settings['port'] = 'COM%s'%(i)
        try:
            serial = Serial(settings['port'], settings['baund'], settings['bytesize'],
                settings['parity'], settings['stopbits'], settings['timeout'])
            ports.append(i)
        except:
            pass
    return ports

class UISerial(QWidget):
    toVisualHex = lambda self,data: ''.join(['%02X'%(ord(c)) for c in data])
    toHex = lambda self,data: unhexlify(data)
    def __init__(self, parent=None):
        super(QWidget, self).__init__(parent)
        self.creGui()
        self.flags = {'opened':False}
        
    def creGui(self):
        vbox = QVBoxLayout()
        grid = QGridLayout()
        grid.addWidget(QLabel('Port:'), 0, 0)
        self.cmdPorts = QComboBox()
        items = []
        for i in search_serial_ports():
            items.append('COM%s'%(i))
        items.append('CAN')
        self.cmdPorts.addItems(items)
        grid.addWidget(self.cmdPorts, 0, 1)
        self.cmdPorts.setCurrentIndex(0)
        self.cmdPorts.setEditable(True)
        
        grid.addWidget(QLabel('Baudrate:'), 0, 2)
        self.cmdBaudrate = QComboBox()
        self.cmdBaudrate.addItems(['4800','7200','9600','14400','19200','38400','57600','115200','128000'])
        grid.addWidget(self.cmdBaudrate, 0, 3)
        self.cmdBaudrate.setCurrentIndex(7)
        self.cmdBaudrate.setEditable(True) 
        
        grid.addWidget(QLabel('Data:'), 0, 4)
        self.cmdData = QComboBox()
        self.cmdData.addItems(['8','7','6','5','4'])
        grid.addWidget(self.cmdData, 0, 5)
        self.cmdData.setCurrentIndex(0) 
        
        grid.addWidget(QLabel('Parity:'), 0, 6)
        self.cmdParity = QComboBox()
        self.cmdParity.addItems(['Odd','Even','Flag','Space','None'])
        grid.addWidget(self.cmdParity, 0, 7)
        self.cmdParity.setCurrentIndex(4)
        
        grid.addWidget(QLabel('Stop:'), 0, 8)
        self.cmdStop = QComboBox()
        self.cmdStop.addItems(['1','1.5','2'])
        grid.addWidget(self.cmdStop, 0, 9)
        self.cmdStop.setCurrentIndex(0)
        
        grid.addWidget(QLabel('FlowControl:'), 0, 10)
        self.cmdFlowControl = QComboBox()
        self.cmdFlowControl.addItems(['Xon / Xoff','Hardware','None'])         
        grid.addWidget(self.cmdFlowControl, 0, 11)
        self.cmdFlowControl.setCurrentIndex(2)                              
    
        self.btnOpenClose = QPushButton('Open')
        self.btnOpenClose.clicked.connect(self.on_btnOpenClose_clicked)
        grid.addWidget(self.btnOpenClose, 1, 11)

        self.btnTraceAs = QPushButton('Trace AS')
        self.btnTraceAs.clicked.connect(self.on_btnTraceAs_clicked)
        grid.addWidget(self.btnTraceAs, 1, 4)

        self.rbAscii = QRadioButton('ASCII')
        self.rbAscii.setChecked(True)
        self.rbHex = QRadioButton('HEX')
        grid.addWidget(self.rbAscii, 1, 0)
        grid.addWidget(self.rbHex, 1, 1)

        self.btnClearHistory = QPushButton('Clear history')
        self.btnClearHistory.clicked.connect(self.on_btnClearHistory_clicked)
        grid.addWidget(self.btnClearHistory, 1, 7)
        vbox.addLayout(grid)

        self.tbHistory = QTextEdit()
        self.tbHistory.setReadOnly(True)
        self.tbHistory.setStyleSheet(_fromUtf8("background-color: rgb(36, 36, 36);\ncolor: rgb(12, 190, 255);"))
        vbox.addWidget(self.tbHistory)

        self.teInput = QTextEdit()
        self.teInput.setMaximumHeight(50)
        self.teInput.setStyleSheet(_fromUtf8("background-color: rgb(36, 36, 36);\ncolor: rgb(12, 190, 255);"))
        vbox.addWidget(self.teInput)
        self.teInput.textChanged.connect(self.on_teInput_textChanged)

        hbox = QHBoxLayout()
        self.btnResetArduin = QPushButton('ResetArduino')
        self.btnSend = QPushButton('Send')
        self.lcdRecvNbr = QLCDNumber()
        self.lcdSendNbr = QLCDNumber()
        self.lcdRecvNbr.display(0)
        self.lcdSendNbr.display(0)
        hbox.addWidget(QLabel('Recv::'))
        hbox.addWidget(self.lcdRecvNbr)
        hbox.addWidget(QLabel('Send::'))
        hbox.addWidget(self.lcdSendNbr)
        hbox.addWidget(self.btnResetArduin)
        hbox.addWidget(self.btnSend)
        self.btnSend.clicked.connect(self.on_btnSend_clicked)

        vbox.addLayout(hbox)

        self.setLayout(vbox)

        self.serial = AsSerial()

    def checkData(self, data):
        if data == '':
            return (False, 'data can\'t be null')

        errch, msg = None, 'success'
        if(self.rbHex.isChecked()):
            if(data[-1]=='\n'):
                data = data[:-1]
            if len(data) % 2 != 0:
                errch, msg = True, 'HEX mode, data length should be odd'
            else:
                for ch in data.upper():
                    if not ('0' <= ch <= '9' or 'A' <= ch <= 'F'):
                        errch, msg = ch, 'invalid char in HEX mode'
                        break           
        return ((not errch), msg)

    def onSendData(self, data=None):
        if(not data): data = self.teInput.toPlainText()
        self.tbHistory.insertPlainText(str(data))
        self.teInput.clear()
        bytes = self.rbAscii.isChecked() and len(data) or len(data) / 2
        self.lcdSendNbr.display(self.lcdSendNbr.intValue() + bytes)

    def on_teInput_textChanged(self):
        data = str(self.teInput.toPlainText())
        if('\n' in data):
            self.on_btnSend_clicked()

    def on_btnSend_clicked(self):
        if(self.flags['opened']==False):
            QMessageBox.information(self, 'Tips', 'Please open COM fistly.')
            return
        data = self.teInput.toPlainText()
        if(self.rbHex.isChecked()):
            if(data[-1]=='\n'):
                data = data[:-1]
        ret, msg = self.checkData(data)
        if not ret:
            QMessageBox.critical(self, 'Error', msg)
            return
        
        self.onSendData(data)
        if(self.rbHex.isChecked()):
            data = self.toHex(data)
        self.serial.send(data)
    def on_message_received(self,data):
        bytes = len(data)
        if(self.rbHex.isChecked()):
            data = self.toVisualHex(data)
        self.tbHistory.insertPlainText(data)
        self.tbHistory.moveCursor(QTextCursor.End)
        self.lcdRecvNbr.display(self.lcdRecvNbr.intValue() + bytes)
        
    def on_btnOpenClose_clicked(self):
        if(self.btnOpenClose.text()=='Open'):
            settings = {}
            settings['port'] = str(self.cmdPorts.currentText())
            settings['baund'] = int(str(self.cmdBaudrate.currentText()),10)
            settings['bytesize'] = int(str(self.cmdData.currentText()),10)
            settings['parity']=str(self.cmdParity.currentText())[:1]
            settings['stopbits']=float(str(self.cmdStop.currentText()))
            settings['timeout'] = 0.1
            self.serial.recv_msg.connect(self.on_message_received)
            ret, msg = self.serial.open(settings)
            if(ret==False): # open failed
                QMessageBox.critical(self, 'Error', msg)
            else:
                self.btnOpenClose.setText('Close')
                self.flags['opened'] = True
        else:
            self.serial.terminate()
            self.serial.close()
            self.btnOpenClose.setText('Open')
            self.flags['opened'] = False

    def on_btnTraceAs_clicked(self):
        self.serial.runcmd('trace', False)

    def on_btnClearHistory_clicked(self):
        pass         