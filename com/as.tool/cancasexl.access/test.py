
from vxlapi import *
from vxlapih import *

if(__name__ == '__main__'):
    print('start to test vxlapi')
    xlOpenDriver()
    
    status,portHandle,permissionMask = xlOpenPort(bytearray(b'port0'),1,1)
    print(status,portHandle,permissionMask)
    xlCanSetChannelBitrate(portHandle,permissionMask,500000)
    xlSetApplConfig(bytearray(b'CANcaseXL'),0)
    event = s_xl_event()
    status,eventCount= xlReceive(portHandle,1,event)
    print(eventCount,xlGetEventString(event))
    print(xlGetErrorString(status))
    
    event_msg=s_xl_event()
    event_msg.tag=XL_TRANSMIT_MSG
    event_msg.can_msg.id=0x101
    event_msg.can_msg.flags=0
    data = []
    for n in range(0, 8):
        data.append(n)
    event_msg.can_msg.data = data
    event_msg.can_msg.dlc=8
    status= xlCanTransmit(portHandle, permissionMask, 1, event_msg)
    print('xlCanTransmit',xlGetErrorString(status))
    print(event_msg.can_msg.data[2],event_msg.can_msg.data[6])
    xlCloseDriver()
    
    