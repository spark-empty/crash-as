#/**
# * AS - the open source Automotive Software on https://github.com/parai
# *
# * Copyright (C) 2015  AS <parai@foxmail.com>
# *
# * This source code is free software; you can redistribute it and/or modify it
# * under the terms of the GNU General Public License version 2 as published by the
# * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
# *
# * This program is distributed in the hope that it will be useful, but
# * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# * for more details.
# */
import os
import sys
import glob

def LNFS(res,tgt):
    abs = os.path.abspath(res)
    if(False == os.path.exists(abs)):
        print("  >> error: lnfs %s %s"%(res,tgt))
        return
    if(os.path.isdir(abs) and (tgt=='TRUE' or tgt=='FALSE')):
        for res2 in glob.glob('%s/*'%(abs)):
            # fork sub directory only if tgt is TRUE
            if(tgt == 'TRUE' and os.path.isdir(res2)):
                LNFS(res2,'TRUE')
            elif(False == os.path.isdir(res2)):
                LNFS(res2,os.path.basename(res2))
    elif(os.path.exists(res)):
        if(os.name=='nt'):
            if(os.path.isdir(abs)):
                os.system('mklink /D %s %s'%(tgt,abs))
            else:
                os.system('mklink %s %s'%(tgt,abs))
        else:
            if(os.path.isdir(abs) and os.path.exists(tgt)):os.system('rm -rv %s'%(tgt))
            os.system('ln -sv %s %s'%(res,tgt))
            

def LNFS2(res):
    tgt = os.path.basename(res)
    abs = os.path.abspath(res)
    if(os.name=='nt'):
        if(os.path.isdir(abs)):
            os.system('mklink /D %s %s'%(tgt,abs))
        elif(os.path.exists(res)):
            os.system('mklink %s %s'%(tgt,abs))
        else:
            print("  >> error: lnfs %s"%(res))
    else:
        if(os.path.isdir(abs)):
            if(os.path.exists(tgt)):os.system('rm -rv %s'%(tgt))
            os.system('ln -sv %s %s'%(res,tgt))
        elif(os.path.exists(res)):
            os.system('ln -sv %s %s'%(res,tgt))
        else:
            print(" >> error: lnfs %s"%(res))
            

if(__name__ == '__main__'):
    if(len(sys.argv) == 3):
        LNFS(sys.argv[1],sys.argv[2])
    elif(len(sys.argv) == 2):
        LNFS2(sys.argv[1])
    else:
        print("usage:lnfs.py resource_location target_link")
