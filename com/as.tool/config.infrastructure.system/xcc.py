__header = '''/**
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
import os,sys,re
from argen.KsmGen import *
from argen.OsGen import *
from argen.ArGen import *

__gen__ = [KsmGen,OsGen]

def SetDefaultRTOS(name):
    SetOS(name)

def XCC(gendir, env=None, genEnvOnly=False):
    if(not os.path.exists(gendir)):os.mkdir(gendir)
    if(env is not None):
        fp = open('%s/asmconfig.h'%(gendir),'w')
        fp.write('#ifndef _AS_MCONF_H_\n\n')
        if(env['MODULES'] is not None):
            for m in env['MODULES']:
                fp.write('#ifndef USE_%s\n#define USE_%s 1\n#endif\n\n'%(m,m))
        if(env['CONFIGS'] is not None):
            reD = re.compile(r'([0-9]+|0x[0-9A-Fa-f]+)')
            for m,v in env['CONFIGS'].items():
                print(m,v)
                if(reD.search(v)):
                    fp.write('#ifndef %s\n#define %s %s\n#endif\n\n'%(m,m,v))
                else:
                    fp.write('#ifndef %s\n#define %s "%s"\n#endif\n\n'%(m,m,v))
        if(os.name != 'posix'):
            fp.write('#if defined(USE_RTTHREAD) && defined(USE_ARCH_X86)\n'
                 '#define _EXFUN(N,P) N P\n'
                 '#define _READ_WRITE_RETURN_TYPE int\n'
                 '#endif\n')
        else:
            fp.write('#if defined(USE_RTTHREAD) && defined(USE_ARCH_X86)\n'
                 '#define _EXFUN(N,P) N P\n'
                 '#endif\n')
        if('CPPDEFINES' in env):
            for macro in env['CPPDEFINES']:
                mm = macro.split('=')
                m = mm[0]
                if(len(mm) == 2):
                    v = mm[1]
                    fp.write('#ifndef %s\n#define %s %s\n#endif\n'%(m,m,v))
                else:
                    fp.write('#ifndef %s\n#define %s\n#endif\n'%(m,m))
        fp.write('#endif /* _AS_MCONF_H_ */\n')
        fp.close()
        cfgdone = '%s/config.done'%(gendir)
        if(os.path.exists(cfgdone)):
            return
        if(genEnvOnly==True):
            return
    for g in __gen__:
        print('  %s ...'%(g.__name__))
        g(gendir)

    
if(__name__ == '__main__'):
    gendir = os.path.abspath(sys.argv[1])
    if(sys.argv[2]=='true'): # generate bsw
        ArGenMain('%s/autosar.arxml'%(gendir),gendir)
    else:
        XCC(gendir)
        print('  >> XCC %s/*.xml done.'%(gendir))
    
