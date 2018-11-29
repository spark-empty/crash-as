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
import sys,os
from cc.ascp import ASCP
def ASCC(file,args):
    if(file[-4:].upper() == '.DBC'):
        ASCP(file,args)

if(__name__ == '__main__'):
    if len(sys.argv) >= 2:
        ASCC(sys.argv[1],sys.argv[2:])
    else:
        print("Usage: ASCC file **args")