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

import os,sys,time
import threading
from bitarray import bitarray
from pyas.can import *

__all__ = ['Network']



# big endian bits map
_bebm = []

#cstr = 'COM big endian bits map:\n'
for i in range(64):
#    cstr += '\n\tB%2d '%(i)
    for j in range(8):
        _bebm.append(i*8 + 7-j)
#        cstr += '%3d '%(i*8 + 7-j)
#print(cstr)

class Sdu():
    def __init__(self, length):
        self.data = []
        for i in range(0,length):
            self.data.append(0x5A)

    def __iter__(self):
        for v in self.data:
            yield v

    def __len__(self):
        return len(self.data)

    def beset(self, start, size, value):
        rBit = size-1
        nBit = _bebm.index(start)
        wByte = 0
        wBit = 0
        for i in range(size):
            wBit = _bebm[nBit]
            wByte = int(wBit/8)
            wBit  = wBit%8
            if(value&(1<<rBit) != 0):
                self.data[wByte] |= 1<<wBit
            else:
                self.data[wByte] &= ~(1<<wBit)
            nBit += 1
            rBit -= 1

    def leset(self, start, size, value):
        rBit = size-1
        nBit = start+size-1
        wByte = 0
        wBit = 0
        for i in range(size):
            wBit = nBit
            wByte = int(wBit/8)
            wBit  = wBit%8
            if(value&(1<<rBit) != 0):
                self.data[wByte] |= 1<<wBit
            else:
                self.data[wByte] &= ~(1<<wBit)
            nBit -= 1
            rBit -= 1

    def set(self, sig, value):
        start = sig['start']
        size = sig['size']
        endian = sig['endian'] # 1:Little 0: BIG
        if(endian == 0):
            self.beset(start, size, value)
        else:
            self.leset(start, size, value)

    def beget(self, start, size):
        nBit = _bebm.index(start)
        value = 0
        for i in range(size):
            rBit = _bebm[nBit]
            rByte = int(rBit/8)
            if(self.data[rByte]&(1<<(rBit%8)) != 0):
                value = (value<<1)+1
            else:
                value = (value<<1)+0
            nBit += 1
        return value

    def leget(self, start, size):
        nBit = start+size-1
        value = 0
        for i in range(size):
            rBit = nBit
            rByte = int(rBit/8)
            if(self.data[rByte]&(1<<(rBit%8)) != 0):
                value = (value<<1)+1
            else:
                value = (value<<1)+0
            nBit -= 1
        return value

    def get(self, sig):
        # for big endian only
        start = sig['start']
        size = sig['size']
        endian = sig['endian'] # 1:Little 0: BIG
        if(endian == 0):
            return self.beget(start, size)
        else:
            return self.leget(start, size)

    def __str__(self):
        cstr = ''
        for b in self.data:
            cstr += '%02X'%(b)
        return cstr

class Signal():
    def __init__(self, sg):
        self.sg = sg
        self.mask = (1<<sg['size'])-1
        self.set_value(0)

    def set_value(self, v):
        self.value = v&self.mask

    def get_value(self):
        return self.value&self.mask

    def __str__(self):
        return str(self.sg)

    def __getitem__(self, key):
        return  self.sg[key]

class Message():
    def __init__(self, msg, busid):
        self.msg = msg
        self.busid = busid
        self.sgs = {}
        self.sdu = Sdu(msg['length'])
        if('period' in msg):
            self.period = msg['period']
        else:
            self.period = 1000
        self.timer = time.time()
        for sg in msg['sgList']:
            sg = sg['sg']
            self.sgs[sg['name']] = Signal(sg)

    def attrib(self, key):
        return self.msg[key]

    def set_period(self, period):
        self.period = period

    def get_period(self):
        return self.period

    def transmit(self):
        for sig in self:
            self.sdu.set(sig, sig.value)
        ercd = can_write(self.busid, self.msg['id'], self.sdu)
        if(ercd == False):
            print('cansend can%s %03X#%s failed'%(self.busid, self.msg['id'], self.sdu))

    def ProcessTX(self):
        if(self.period <= 0): return
        elapsed = time.time() - self.timer
        if(self.period <= elapsed*1000):
            self.timer = time.time()
            self.transmit()

    def ProcessRX(self):
        result,canid,data = can_read(self.busid, self.msg['id'])
        if(result):
            self.sdu.data = data
            for sig in self:
                sig.value = self.sdu.get(sig)

    def IsTransmit(self):
        if(self.msg['node'] != 'AS'):
            return True
        return False

    def Process(self):
        if(self.msg['node'] != 'AS'):
            self.ProcessTX()
        else:
            self.ProcessRX()

    def __str__(self):
        return str(self.msg)

    def __iter__(self):
        for key,sig in self.sgs.items():
            yield sig

    def __getitem__(self, key):
        self.sgs[key].value = self.sdu.get(self.sgs[key])
        return  self.sgs[key].value

    def __setitem__(self, key, value):
        self.sgs[key].set_value(value)

class Network(threading.Thread):
    def __init__(self, dbcf, busid=DFTBUS):
        threading.Thread.__init__(self)
        dbc = self.parseCANDBC(dbcf)
        self.msgs = {}
        for msg in dbc['boList']:
            msg = msg['bo']
            self.msgs[msg['name']] = Message(msg, busid)
        self.start()

    def stop(self):
        self.is_running = False

    def run(self):
        self.is_running = True
        while(self.is_running):
            for msg in self:
                msg.Process()
            time.sleep(0.001)

    def __iter__(self):
        for key,msg in self.msgs.items():
            yield msg

    def __getitem__(self, key):
        return  self.msgs[key]

    def parseCANDBC(self, dbc):
        pydbc = os.path.abspath('../py.can.database.access/ascc')
        assert(os.path.exists(pydbc))
        sys.path.append(pydbc)
        import cc.ascp as ascp
        return ascp.parse(dbc)

if(__name__ == '__main__'):
    can_open(0, 'socket', 0, 1000000)
    nt = Network(sys.argv[1])
    nt['RxMsgAbsInfo'].set_period(100)
    nt['RxMsgAbsInfo']['VehicleSpeed'] = 24000
    nt['RxMsgAbsInfo']['TachoSpeed'] = 8000
    nt['RxMsgAbsInfo']['Led1Sts'] = 1
    nt['RxMsgAbsInfo']['Led2Sts'] = 2
    nt['RxMsgAbsInfo']['Led3Sts'] = 3
    time.sleep(1)
    print('year is', nt['TxMsgTime']['SystemTime_year'])
    print('month is', nt['TxMsgTime']['SystemTime_month'])
    print('day is', nt['TxMsgTime']['SystemTime_day'])
    print('hour is', nt['TxMsgTime']['SystemTime_hour'])
    print('minute is', nt['TxMsgTime']['SystemTime_minute'])
    print('second is', nt['TxMsgTime']['SystemTime_second'])

    nt.stop()

