monitor reset
monitor halt
monitor speed 8000
monitor endian little
monitor reg cpsr = 0xd3

echo WDT setup WTCON
monitor memU32 0x53000000 = 0x00000000      

echo PLL setup
monitor memU32 0x4C000000 = 0xFFFFFFFF      
monitor memU32 0x4C000004 = 0x0005C011      
monitor memU32 0x4C000008 = 0x00038022      
monitor memU32 0x4C00000C = 0x00FFFFF0      
monitor memU32 0x4C000010 = 0x00000004      
monitor memU32 0x4C000014 = 0x00000005      
monitor memU32 0x4C000018 = 0x00000000  
    
echo MEMCTRL setup 
monitor memU32 0x48000000 = 0x22011110      
monitor memU32 0x48000004 = 0x00000700      
monitor memU32 0x48000008 = 0x00000700       
monitor memU32 0x4800000c = 0x00000700
monitor memU32 0x48000010 = 0x00000700
monitor memU32 0x48000014 = 0x00000700
monitor memU32 0x48000018 = 0x00000700
monitor memU32 0x4800001C = 0x00018005      
monitor memU32 0x48000020 = 0x00018005
monitor memU32 0x48000024 = 0x008C07A3      
monitor memU32 0x48000028 = 0x000000B1      
monitor memU32 0x4800002C = 0x00000030      
monitor memU32 0x48000030 = 0x00000030