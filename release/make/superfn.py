#/**
# * AS - the open source Automotive Software on https://github.com/parai
# *
# * Copyright (C) 2016  AS <parai@foxmail.com>
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

import os,sys,glob

def replace_file_all(argv):
    file = argv[0]
    # special process for character '$' in Makefile
    old = argv[1].replace('\\x24','$')
    new = argv[2]
    print(old,new)
    fp = open(file)
    fout = open('%s.tmp'%(file),'w')
    for el in fp.readlines():
        fout.write(el.replace(old,new))
    fout.close()
    fp.close()
    os.system('mv -fv %s %s'%('%s.tmp'%(file),file))

__superfn__ = { 'replace.file.all':replace_file_all }

if __name__ == '__main__':
    if(len(sys.argv) > 1):
        __superfn__[sys.argv[1]](sys.argv[2:])
    else:
        print('usage : %s fn *args ..'%(sys.argv[0]))

