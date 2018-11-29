'''
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
import ctypes
from vxlapih import *

__all__ = ['vxlapi','XLuint64','XLaccess','XLstatus','XLporthandle','XLevent']
        
XLuint64=ctypes.c_ulonglong
XLaccess=XLuint64
XLstatus=ctypes.c_short
XLporthandle=ctypes.c_long

class s_xl_can_msg(ctypes.Structure):
    _fields_ = [("id", ctypes.c_ulong),
                ("flags", ctypes.c_ushort),
                ("dlc", ctypes.c_ushort),
                ("res1", XLuint64),
                ("data", ctypes.c_ubyte*MAX_MSG_LEN)]

class s_xl_chip_state(ctypes.Structure):
    _fields_ = [("busStatus", ctypes.c_ubyte),
                ("txErrorCounter", ctypes.c_ubyte),
                ("rxErrorCounter", ctypes.c_ubyte),
                ("chipStatte", ctypes.c_ubyte),
                ("flags", ctypes.c_uint)]

class s_xl_lin_crc_info(ctypes.Structure):
    _fields_ = [("id", ctypes.c_ubyte),
                ("flags", ctypes.c_ubyte)]

class s_xl_lin_wake_up(ctypes.Structure):
    _fields_ = [("flag", ctypes.c_ubyte)]

class s_xl_lin_no_ans(ctypes.Structure):
    _fields_ = [("id", ctypes.c_ubyte)]

class s_xl_lin_sleep(ctypes.Structure):
    _fields_ = [("flag", ctypes.c_ubyte)]

class s_xl_lin_msg(ctypes.Structure):
    _fields_ = [("id", ctypes.c_ubyte),
                ("dlc", ctypes.c_ubyte),
                ("flags", ctypes.c_ushort),
                ("data", ctypes.c_ubyte*8),
                ("crc", ctypes.c_ubyte)]

class s_xl_lin_msg_api(ctypes.Union):
    _fields_ = [("s_xl_lin_msg", s_xl_lin_msg),
                ("s_xl_lin_no_ans", s_xl_lin_no_ans),
                ("s_xl_lin_wake_up", s_xl_lin_wake_up),
                ("s_xl_lin_sleep", s_xl_lin_sleep),
                ("s_xl_lin_crc_info", s_xl_lin_crc_info)]

class s_xl_sync_pulse(ctypes.Structure):
    _fields_ = [("pulseCode", ctypes.c_ubyte),
                ("time", XLuint64)]

class s_xl_daio_data(ctypes.Structure):
    _fields_ = [("flags", ctypes.c_ubyte),
                ("timestamp_correction", ctypes.c_uint),
                ("mask_digital", ctypes.c_ubyte),
                ("value_digital", ctypes.c_ubyte),
                ("mask_analog", ctypes.c_ubyte),
                ("reserved", ctypes.c_ubyte),
                ("value_analog", ctypes.c_ubyte*4),
                ("pwm_frequency", ctypes.c_uint),
                ("pwm_value", ctypes.c_ubyte),
                ("reserved1", ctypes.c_uint),
                ("reserved2", ctypes.c_uint)]

class s_xl_transceiver(ctypes.Structure):
    _fields_ = [("event_reason", ctypes.c_ubyte),
                ("is_present", ctypes.c_ubyte)]

class s_xl_tag_data(ctypes.Union):
    _fields_ = [("msg", s_xl_can_msg),
                ("chipState", s_xl_chip_state),
                ("linMsgApi", s_xl_lin_msg_api),
                ("syncPulse", s_xl_sync_pulse),
                ("daioData", s_xl_daio_data),
                ("transceiver", s_xl_transceiver)]

MAX_BUF_SIZE = 10
XLeventtag=ctypes.c_ubyte
class s_xl_event(ctypes.Structure):
    _fields_ =[ ("tag", XLeventtag),
                ("chanIndex", ctypes.c_ubyte),
                ("transId", ctypes.c_ushort),
                ("portHandle", ctypes.c_ushort),
                ("reserved", ctypes.c_ushort),
                ("timeStamp", XLuint64),
                ("tagData", s_xl_tag_data)]

XLevent=s_xl_event
array_XLevent=(MAX_BUF_SIZE*XLevent)

class XLbusParams_can(ctypes.Structure):
    _fields_ =[("bitRate",ctypes.c_uint),
               ("sjw",ctypes.c_ubyte),
               ("tseg1",ctypes.c_ubyte),
               ("tseg2",ctypes.c_ubyte),
               ("sam",ctypes.c_ubyte),
               ("outputMode",ctypes.c_ubyte),
               ("padding",ctypes.c_ubyte*23)]

class XLbusParams(ctypes.Structure):
    _fields_ =[("busType",ctypes.c_uint),
               ("can",XLbusParams_can)]

class s_xl_channel_config(ctypes.Structure):
    _pack_ = 1
    _fields_ =[("name",ctypes.c_char*(XL_MAX_LENGTH+1)),
               ("hwType",ctypes.c_ubyte),
               ("hwIndex",ctypes.c_ubyte),
               ("hwChannel",ctypes.c_ubyte),
               ("transceiverType",ctypes.c_ushort),
               ("transceiverState",ctypes.c_uint),
               ("channelIndex",ctypes.c_ubyte),
               ("channelMask",XLuint64),
               ("channelCapabilities",ctypes.c_uint),
               ("channelBusCapabilities",ctypes.c_uint),
               ("isOnBus",ctypes.c_ubyte),
               ("connectedBusType",ctypes.c_uint),
               ("busParams",XLbusParams),
               ("driverVersion",ctypes.c_uint),
               ("interfaceVersion",ctypes.c_uint),
               ("raw_data",ctypes.c_uint*10),
               ("serialNumber",ctypes.c_uint),
               ("articleNumber",ctypes.c_uint),
               ("transceiverName",ctypes.c_char*(XL_MAX_LENGTH+1)),
               ("specialCabFlags",ctypes.c_uint),
               ("dominantTimeout",ctypes.c_uint),
               ("dominantRecessiveDelay",ctypes.c_ubyte),
               ("recessiveDominantDelay",ctypes.c_ubyte),
               ("connectionInfo",ctypes.c_ubyte),
               ("currentlyAvailableTimestamps",ctypes.c_ubyte),
               ("minimalSupplyVoltage",ctypes.c_ushort),
               ("maximalSupplyVoltage",ctypes.c_ushort),
               ("maximalBaudrate",ctypes.c_uint),
               ("fpgaCoreCapabilities",ctypes.c_ubyte),
               ("specialDeviceStatus",ctypes.c_ubyte),
               ("channelBusActiveCapabilities",ctypes.c_ushort),
               ("breakOffset",ctypes.c_ushort),
               ("delimiterOffset",ctypes.c_ushort),
               ("reserved",ctypes.c_uint*3)]

class s_xl_driver_config(ctypes.Structure):
    _fields_ =[ ("dllVersion",ctypes.c_uint),
                ("channelCount",ctypes.c_uint),
                ("reserved",ctypes.c_uint*10),
                ("channel",s_xl_channel_config*XL_CONFIG_MAX_CHANNELS)]


class vxlapi():
    def __init__(self):
        self.candll = ctypes.windll.LoadLibrary("vxlapi.dll")
        event_list=XLevent(0)
    def xlOpenDriver(self):
        '''The Application calls this function to get access to the driver.
            XLstatus xlOpenDriver(void)
        '''
        status = self.candll.xlOpenDriver()
        if(status != XL_SUCCESS):print('vxapi error: xlOpenDriver failed <%s=%s>.'%(status,self.xlGetErrorString(status)))
        return status
    
    def xlCloseDriver(self):
        '''XLstatus xlCloseDriver(void)'''
        status=self.candll.xlCloseDriver()
        if(status != XL_SUCCESS):print('vxapi error: xlCloseDriver failed <%s=%s>.'%(status,self.xlGetErrorString(status)))
        return  status   
     
    def xlOpenPort(self,userName='xlCANcontrol',accessMask=1,permissionMask=XLaccess(1), \
                   rxQueueSize=256,xlInterfaceVersion=XL_INTERFACE_VERSION,busType=XL_BUS_TYPE_CAN):
        '''
        /*------------------------------------------------------------------------------
            XLstatus xlOpenPort(...):
            --------------------------------------------------------------------------------
            The application tells the driver to which channels
            it wants to get access to and which of these channels
            it wants to get the permission to initialize the channel (on input must be
            in variable where pPermissionMask points).
            Only one port can get the permission to initialize a channel.
            The port handle and permitted init access is returned.
        */
            xlOpenPort() without parameter will open CANcaseXL port0
        '''
        userName = ctypes.c_char_p(bytes(userName,'ascii'))
        portHandle=XLporthandle(XL_INVALID_PORTHANDLE)
        self.candll.xlOpenPort.argtypes=[ctypes.POINTER(XLporthandle), ctypes.c_char_p, XLaccess, ctypes.POINTER(XLaccess), ctypes.c_uint, ctypes.c_uint, ctypes.c_uint]
        status=self.candll.xlOpenPort(portHandle, userName, accessMask, permissionMask, rxQueueSize, xlInterfaceVersion, busType)
        if(status != XL_SUCCESS):print('vxapi error: xlOpenPort failed <%s=%s>.'%(status,self.xlGetErrorString(status)))
        return (status, portHandle, permissionMask)
    
    def xlCanSetChannelBitrate(self,portHandle,accessMask=1,bitrate=125000):
        ''' set device baudrate '''
        self.candll.xlCanSetChannelBitrate.argtypes=[XLporthandle, XLaccess, ctypes.c_ulong]
        status= self.candll.xlCanSetChannelBitrate(portHandle, accessMask, ctypes.c_ulong(bitrate))
        if(status != XL_SUCCESS):print('vxapi error: xlCanSetChannelBitrate failed <%s=%s>.'%(status,self.xlGetErrorString(status)))
        return status
    def xlActivateChannel(self, portHandle, accessMask=1, busType=XL_BUS_TYPE_CAN, flags=XL_ACTIVATE_RESET_CLOCK):
        '''The selected channels go 'on the bus'. Type of the bus is specified by busType parameter.
            Additional parameters can be specified by flags parameter.
        '''
        self.candll.xlActivateChannel.argtypes=[XLporthandle, XLaccess, ctypes.c_uint, ctypes.c_uint]
        status=self.candll.xlActivateChannel(portHandle, accessMask, busType, flags)
        if(status != XL_SUCCESS):print('vxapi error: xlActivateChannel failed <%s=%s>.'%(status,self.xlGetErrorString(status)))
        return status
    
    def xlDeactivateChannel(self, portHandle, accessMask=1):
        self.candll.xlDeactivateChannel.argtypes=[XLporthandle, XLaccess]
        status=self.candll.xlDeactivateChannel(portHandle, accessMask)
        if(status != XL_SUCCESS):print('vxapi error: xlDeactivateChannel failed <%s=%s>.'%(status,self.xlGetErrorString(status)))
        return status    
    def xlReceive(self, portHandle,pEventCount,pEvents):
        '''
            /*------------------------------------------------------------------------------
            xlReceive():
            --------------------------------------------------------------------------------
            The driver is asked to retrieve burst of Events from the
            application's receive queue. This function is optimized
            for speed. pEventCount on start must contain size of the buffer in
            messages, on return it sets number of really received messages (messages
            written to pEvents buffer).
            Application must allocate pEvents buffer big enough to hold number of
            messages requested by pEventCount parameter.
            It returns VERR_QUEUE_IS_EMPTY and *pEventCount=0 if no event
            was received.
            The function only works for CAN, LIN, DAIO. For MOST there is a different
            function
            */
        '''
        self.candll.xlReceive.argtypes=[XLporthandle, ctypes.POINTER(ctypes.c_uint), ctypes.POINTER(XLevent)]
        status=self.candll.xlReceive(portHandle, ctypes.byref(pEventCount), ctypes.byref(pEvents))
        return status 
    
    def xlGetEventString(self, ev):
        self.candll.xlGetEventString.argtypes=[ctypes.POINTER(XLevent)]
        self.candll.xlGetEventString.restype=ctypes.c_char_p
        rec_string=self.candll.xlGetEventString(ctypes.pointer(ev))
        return rec_string   

    def xlGetErrorString(self, err):
        self.candll.xlGetErrorString.argtypes=[XLstatus]
        self.candll.xlGetErrorString.restype=ctypes.c_char_p
        err_string=self.candll.xlGetErrorString(err)
        return err_string   
    
    def xlGetDriverConfig(self, pDriverConfig):
        self.candll.xlGetDriverConfig.argtypes=[ctypes.POINTER(s_xl_driver_config)]
        status=self.candll.xlGetDriverConfig(ctypes.byref(pDriverConfig))
        if(status != XL_SUCCESS):print('vxapi error: xlGetDriverConfig failed <%s=%s>.'%(status,self.xlGetErrorString(status)))
        return status
        
    def xlCanSetChannelTransceiver(self,port_handle,amask,type,line_mode,resNet=ctypes.c_int(0)):
        self.candll.xlCanSetChannelTransceiver.argtypes=[XLporthandle, XLaccess, ctypes.c_int,ctypes.c_int,ctypes.c_int]
        status = self.candll.xlCanSetChannelTransceiver(port_handle,amask,ctypes.c_int(type),ctypes.c_int(line_mode),resNet)
        if(status != XL_SUCCESS):print('vxapi error: xlCanSetChannelTransceiver failed <%s=%s>.'%(status,self.xlGetErrorString(status)))
        return status
   
    def xlCanSetChannelOutput(self,port_handle,amask,mode):
       self.candll.xlCanSetChannelOutput.argtypes=[XLporthandle, XLaccess, ctypes.c_ubyte]
       status = self.candll.xlCanSetChannelOutput(port_handle,amask,ctypes.c_ubyte(mode)) 
       if(status != XL_SUCCESS):print('vxapi error: xlCanSetChannelOutput failed <%s=%s>.'%(status,self.xlGetErrorString(status)))
       return status
   
    def xlCanTransmit(self, port_handle, amask, message_count, p_messages):
        self.candll.xlCanTransmit.argtypes=[XLporthandle, XLaccess, ctypes.POINTER(ctypes.c_uint), ctypes.c_void_p]
        status=self.candll.xlCanTransmit(port_handle, amask, ctypes.byref(message_count), ctypes.byref(p_messages))
        if(status != XL_SUCCESS):print('vxapi error: xlCanTransmit failed <%s=%s>.'%(status,self.xlGetErrorString(status)))
        return status    
    
    def xlGetChannelMask(self, hwType=XL_HWTYPE_CANCASEXL, hwIndex=0, hwChannel=0):
        self.candll.xlGetChannelMask.argtypes=[ctypes.c_int, ctypes.c_int, ctypes.c_int]
        mask=self.candll.xlGetChannelMask(hwType, hwIndex, hwChannel)
        return ctypes.c_ulonglong(mask)
    
    def xlGetApplConfig(self, appName="xlCANcontrol", channel=0, busType=XL_BUS_TYPE_CAN):
        app_name=ctypes.c_char_p(appName)
        app_channel=ctypes.c_uint(channel)
        p_hw_type=ctypes.pointer(ctypes.c_uint())
        p_hw_index=ctypes.pointer(ctypes.c_uint())
        p_hw_channel=ctypes.pointer(ctypes.c_uint())
        bus_type=ctypes.c_uint(busType)
        status=self.candll.xlGetApplConfig(app_name, app_channel, p_hw_type, p_hw_index, p_hw_channel, bus_type)
        if(status != XL_SUCCESS):print('vxapi error: xlGetApplConfig failed <%s=%s>.'%(status,self.xlGetErrorString(status)))
        return status, p_hw_type.contents, p_hw_index.contents, p_hw_channel.contents

    def xlSetApplConfig(self, appName, appChannel, hwType=XL_HWTYPE_CANCASEXL, hwIndex=0,  hwChannel=0, busType=XL_BUS_TYPE_CAN):
        self.candll.xlSetApplConfig.argtypes=[ctypes.c_char_p, ctypes.c_uint, ctypes.c_uint, ctypes.c_uint, ctypes.c_uint, ctypes.c_uint]
        status=self.candll.xlSetApplConfig(ctypes.c_char_p(bytes(appName,'ascii')), ctypes.c_uint(appChannel), ctypes.c_uint(hwType),
                                        ctypes.c_uint(hwIndex), ctypes.c_uint(hwChannel), ctypes.c_uint(busType))
        if(status != XL_SUCCESS):print('vxapi error: xlSetApplConfig failed <%s=%s>.'%(status,self.xlGetErrorString(status)))
        return status    

def __test__():
    # test code
    import time
    event_list=XLevent(0)
    xl = vxlapi()
    xl.xlOpenDriver()
    mask = xl.xlGetChannelMask()
    print('## 0',mask)
    status,portHandle,accessMask = xl.xlOpenPort()
    print('## 1',status,portHandle,accessMask)
    xl.xlCanSetChannelBitrate(portHandle,accessMask,500000)
    xl.xlSetApplConfig('CANcaseXL',0)
    xl.xlActivateChannel(portHandle, accessMask)
    loop = 10
    while loop:
        event_count=ctypes.c_uint(1)
        status = xl.xlReceive(portHandle, event_count, event_list)
        if(status == XL_SUCCESS):
            print(xl.xlGetEventString(event_list))
        else:
            time.sleep(0.01)
        loop = loop -1
    xl.xlCloseDriver()
    print("---> OK")
    
if (__name__ == '__main__'):
    #__GenVxapih__()
    __test__()
    pass