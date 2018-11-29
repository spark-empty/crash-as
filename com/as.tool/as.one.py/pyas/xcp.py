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
try:
    from .can import *
except:
    from can import *
import time
from bitarray import bitarray


__all__ = ['xcp','xcpbits']

# Dictionary of XCP error codes, mapping (code -> (error, description))
XCP_ERROR_CODES = {
    0x00:("ERR_CMD_SYNC", "Command processor synchronisation."),
    0x10:("ERR_CMD_BUSY", "Command was not executed."),
    0x11:("ERR_DAQ_ACTIVE", "Command rejected because DAQ is running."),
    0x12:("ERR_PGM_ACTIVE", "Command rejected because PGM is running."),
    0x20:("ERR_CMD_UNKNOWN", "Unknown command or not implemented optional command."),
    0x21:("ERR_CMD_SYNTAX", "Command syntax invalid."),
    0x22:("ERR_OUT_OF_RANGE", "Command syntax valid but command parameter(s) out of range."),
    0x23:("ERR_WRITE_PROTECTED", "The memory location is write protected."),
    0x24:("ERR_ACCESS_DENIED", "The memory location is not accessible."),
    0x25:("ERR_ACCESS_LOCKED", "Access denied, Seed & Key is required."),
    0x26:("ERR_PAGE_NOT_VALID", "Selected page not available."),
    0x27:("ERR_MODE_NOT_VALID", "Selected page mode not available."),
    0x28:("ERR_SEGMENT_NOT_VALID", "Selected segment not valid."),
    0x29:("ERR_SEQUENCE", "Sequence error."),
    0x2A:("ERR_DAQ_CONFIG", "DAQ configuration not valid."),
    0x30:("ERR_MEMORY_OVERFLOW", "Memory overflow error."),
    0x31:("ERR_GENERIC", "Generic error."),
    0x32:("ERR_VERIFY", "The slave internal program verify routine detects an error.")
}
# Dictionary of XCP Command codes
XCP_COMMAND_CODES = {
    0xFF: "CONNECT",
    0xFE: "DISCONNECT",
    0xFD: "GET_STATUS",
    0xFC: "SYNCH",
    0xFB: "GET_COMM_MODE_INFO",
    0xFA: "GET_ID",
    0xF9: "SET_REQUEST",
    0xF8: "GET_SEED",
    0xF7: "UNLOCK",
    0xF6: "SET_MTA",
    0xF5: "UPLOAD",
    0xF4: "SHORT_UPLOAD",
    0xF3: "BUILD_CHECKSUM",
    0xF2: "TRANSPORT_LAYER_CMD",
    0xF1: "USER_CMD",
    0xF0: "DOWNLOAD",
    0xEF: "DOWNLOAD_NEXT",
    0xEE: "DOWNLOAD_MAX",
    0xED: "SHORT_DOWNLOAD",
    0xEC: "MODIFY_BITS",
    0xEB: "SET_CAL_PAGE",
    0xEA: "GET_CAL_PAGE",
    0xE9: "GET_PAG_PROCESSOR_INFO",
    0xE8: "GET_SEGMENT_INFO",
    0xE7: "GET_PAGE_INFO",
    0xE6: "SET_SEGMENT_MODE",
    0xE5: "GET_SEGMENT_MODE",
    0xE4: "COPY_CAL_PAGE",
    0xE3: "CLEAR_DAQ_LIST",
    0xE2: "SET_DAQ_PTR",
    0xE1: "WRITE_DAQ",
    0xE0: "SET_DAQ_LIST_MODE",
    0xDF: "GET_DAQ_LIST_MODE",
    0xDE: "START_STOP_DAQ_LIST",
    0xDD: "START_STOP_SYNCH",
    0xDC: "GET_DAQ_CLOCK",
    0xDB: "READ_DAQ",
    0xDA: "GET_DAQ_PROCESSOR_INFO",
    0xD9: "GET_DAQ_RESOLUTION_INFO",
    0xD8: "GET_DAQ_LIST_INFO",
    0xD7: "GET_DAQ_EVENT_INFO",
    0xD6: "FREE_DAQ",
    0xD5: "ALLOC_DAQ",
    0xD4: "ALLOC_ODT",
    0xD3: "ALLOC_ODT_ENTRY",
    0xD2: "PROGRAM_START",
    0xD1: "PROGRAM_CLEAR",
    0xD0: "PROGRAM",
    0xCF: "PROGRAM_RESET",
    0xCE: "GET_PGM_PROCESSOR_INFO",
    0xCD: "GET_SECTOR_INFO",
    0xCC: "PROGRAM_PREPARE",
    0xCB: "PROGRAM_FORMAT",
    0xCA: "PROGRAM_NEXT",
    0xC9: "PROGRAM_MAX",
    0xC8: "PROGRAM_VERIFY"
}

# 0 = little endian; 1 = big endian
xcp_cpu_endian = 1

class xcpbits():
    global xcp_cpu_endian
    def __init__(self):
        self.bits = bitarray()

    def __len__(self):
        return len(self.toarray())

    def append(self,d, num=8):
        assert(num%8 == 0)
        if(xcp_cpu_endian == 1):  # big endian
            for i in range(num):
                if((d&(1<<(num-1-i))) != 0):
                    self.bits.append(True)
                else:
                    self.bits.append(False)
        else:       # little endian
            bitmap = [ 7, 6, 5, 4, 3, 2, 1, 0,
                      15,14,13,12,11,10, 9, 8,
                      23,22,21,20,19,18,17,16,
                      31,30,29,28,27,26,25,24]
            for i in range(num):
                if((d&(1<<(bitmap[i]))) != 0):
                    self.bits.append(True)
                else:
                    self.bits.append(False)

    def toint(self,pos,num):
        bits = self.bits[pos:pos+num]
        bytes = int((num+4)/8)
        left = bytes*8 - num
        v = 0
        for b in bits.tobytes():
            v = (v<<8) + b
        v =v >> left
        if(xcp_cpu_endian == 0):  # little endian
            bytes = []
            while(v > 0):
                bytes.append(v&0xFF)
                v = v>>8
            for b in bytes:
                 v = (v<<8) + b
        return v
        
    def toarray(self):
        return self.bits.tobytes()

class xcp():
    global xcp_cpu_endian
    def __init__(self,busid,txid,rxid):
        self.busid = busid
        self.rxid  = rxid
        self.txid  = txid
        self.last_response = None

    def get_max_cto(self):
        return 8

    def get_response(self, res=None):
        if(res is None):
            res = self.last_response.toarray()
        err = ''
        if(res[0] != 0xFF):
            if(res[1] in XCP_ERROR_CODES):
                err = 'with error %s '%(XCP_ERROR_CODES[res[1]][1])
            else:
                err = 'with unknown error '
        ss = '  >> xcp response %s= ['%(err)
        length = len(res)
        for i in range(length):
            ss += '%02X,'%(res[i])
        ss+=']'
        return ss

    def poll(self):
        if(self.last_response==None):return
        result,canid,data= can_read(self.busid,self.rxid)
        if((True == result) and (self.rxid == canid)):
            return data
        return None

    def show_request(self,req):
        global XCP_COMMAND_CODES
        if(req[0] in XCP_COMMAND_CODES):
            cmd = XCP_COMMAND_CODES[req[0]]
        else:
            cmd = ''
        ss = '  >> xcp %s request = ['%(cmd)
        length = len(req)
        for i in range(length):
            ss += '%02X,'%(req[i])
        ss+=']'
        print(ss)

    def show_response(self,res):
        ss = self.get_response(res)
        print(ss)

    def transmit(self, req):
        global xcp_cpu_endian
        self.show_request(req)
        can_write(self.busid,self.txid,req)
        ercd = False
        data=None
        pre = time.time()
        while ( ((time.time() - pre) < 5) and (ercd == False)): # 1s timeout
            result,canid,data= can_read(self.busid,self.rxid)
            if((True == result) and (self.rxid == canid)):
                ercd = True
                break
            else:
                time.sleep(0.001) # sleep 1 ms
        
        if (False == ercd):
            print("XCP timeout when receiving a frame! elapsed time = %s ms"%(time.time() -pre))
            return None
      
        self.last_response = xcpbits()
        for d in data:
            self.last_response.append(d, 8)
        self.show_response(self.last_response.toarray())
        if(req[0] == 0xFF):
            xcp_cpu_endian = self.last_response.toarray()[2]&0x01
            print('XCP slave is online with CPU endian %s (0=little,1=big)!'%(xcp_cpu_endian))
        return self.last_response
