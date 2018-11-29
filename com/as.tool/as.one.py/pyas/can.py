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
    from .AS import *
except:
    from AS import *

__all__ = ['can_open','can_write','can_read','can_close','can_reset']

__can__ = can()

def can_open(busid,device,port,baudrate):
    return __can__.open(busid,device.encode('utf-8'),port,baudrate)

def can_write(busid,canid,data):
    '''can request write on can bus <busid>'''
    return __can__.write(busid, canid, len(data), bytearray(data))

def can_read(busid,canid):
    ''' can request read a can frame from <canid> queue of <busid>'''
    result,canid,dlc,data= __can__.read(busid,canid)

    return result,canid,data

def can_close(busid):
    return __can__.close(busid)

def can_reset(busid):
    return __can__.reset(busid)


