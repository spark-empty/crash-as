#! /usr/bin/python3
'''/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2017  AS <parai@foxmail.com>
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
import xml.etree.ElementTree as ET
studio=os.path.abspath('../../com/as.tool/config.infrastructure.system/')
sys.path.append(studio)
sys.path.append('%s/aroil'%(studio))

import reoil
from building import *

CTEST='../../com/as.infrastructure/system/kernel/freeosek/tst/ctest'

#/usr/lib/python3.4/re.py
reHeader=re.compile(r'^(\w+):(.+)$')
reCase=re.compile(r'^\s+([^:]+)$')
reVar=re.compile(r'^\s+(\w+):(\w+)$')
def parse():
    import glob
    fp = open('%s/cfg/ctestcases.cfg'%(CTEST),'r')
    cfg = []
    target=''
    case=''
    id = -1
    for el in fp.readlines():
        if(reHeader.search(el)):
            target,desc = reHeader.search(el).groups()
            cfg.append({'desc':desc, 'target':target, 'case':{} })
            id += 1
        elif(reCase.search(el)):
            case = reCase.search(el).groups()[0].strip().replace(' ','-')
            cfg[id]['case'][case]={}
        elif(reVar.search(el)):
            name,val = reVar.search(el).groups()
            cfg[id]['case'][case][name] = val
        else:
            if(el.strip() != ''):
                print('warning:', el)
    fp.close()
    for cc in glob.glob('./Testsuite/std/*') + glob.glob('./Testsuite/ext/*'):
        for sched in glob.glob('%s/*'%(cc)):
            for obj in glob.glob('%s/*'%(sched)):
                for test in glob.glob('%s/*'%(obj)):
                    if(test[-3:]=='inc'):continue
                    cfg.append({'desc':desc, 'target':'test', 'case':{test:{}} })
                    id += 1
    return cfg

def fixXml(xml,vv,isTest=False):
    for obj in xml:
        if(isTest and (obj.tag=='Task')):
            obj.attrib['StackSize']=str(int(obj.attrib['StackSize'])*2)
        if(isTest and (obj.tag=='Alarm') and (obj.attrib['Autostart'].upper()=='TRUE')):
            obj.attrib['StartTime']=str(int(int(obj.attrib['StartTime'])/100))
        fixXml(obj,vv)
        for k,v in obj.items():
            try:
                name = obj.attrib['Name']
            except KeyError:
                name = ''
            try:
                v2 = vv[v]
                obj.attrib[k] = v2
#                print('fix %s %s[%s] from %s to %s'%(obj,name,k,v,v2))
            except KeyError:
                pass

def saveXml(xml,File):
    if(File[:9]=='src/test/'):
        alarm = ET.Element('Alarm')
        alarm.attrib['Name']='AlarmError'
        alarm.attrib['Autostart']='False'
        alarm.attrib['Counter']='SystemTimer'
        alarm.attrib['Action']='ActivateTask'
        alarm.attrib['Task']='TaskError'
        xml.append(alarm)
    root = ET.Element('AS')
    root.append(xml)
    tree = ET.ElementTree(root)
    tree.write(File, encoding="utf-8", xml_declaration=True);
    fp = open(File,'r')
    content = fp.read()
    fp.close()
    fp = open(File,'w')
    fp.write(content.replace('>','>\n'))
    fp.close()

def genCTEST_CFGH(xml, path):
    fp = open('%s/ctest_cfg.h'%(path), 'w')
    fp.write('#ifndef _CTEST_CFG_H_\n#define _CTEST_CFG_H_\n\n')
    general = xml.find('General')
    fp.write('#define CT_ERROR_CHECKING_TYPE	CT_ERROR_CHECKING_%s\n\n'%(general.attrib['Status']))
    for tsk in xml:
        if(tsk.tag == 'Task'):
            if(tsk.attrib['Schedule'] == 'FULL'):
                fp.write('#define CT_SCHEDULING_%s CT_PREEMPTIVE\n\n'%(tsk.attrib['Name']))
            else:
                fp.write('#define CT_SCHEDULING_%s CT_NON_PREEMPTIVE\n\n'%(tsk.attrib['Name']))
    fp.write('#endif\n\n')
    fp.close()

def telnet(uri, port):
    import socket,time
    time.sleep(0.5) # make sure qemu already on line
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((uri, port))
    sock.setblocking(0)
    timeLeft = 100 # *100ms
    string = ''
    while(timeLeft>0):
        time.sleep(0.1)
        timeLeft -= 1
        try:
            string += sock.recv(4096*4096).decode('utf-8')
        except BlockingIOError:
            pass
        if((string.find('FAIL')!=-1) or (string.find('>> END <<')!=-1)):
            break
    sock.close()
    return string

def RunCommand(cmd):
    print(' >> RunCommand "%s"'%(cmd))
    if(os.name != 'nt'):
        cmd += ' > /dev/null'
    if(0 != os.system(cmd)):
        print('FAIL of RunCommand "%s"'%(cmd))
        return -1
    return 0

def check(target,case):
    schedfifo = os.getenv('schedfifo')
    print('>> Starting test for %s %s schedfifo="%s" ...'%(target,case,schedfifo))
    if(0==RunCommand('qemu-system-arm -machine help')):
        qemu = 'qemu-system-arm'
    else:
        qemu = './qemu-system-arm'
        if(not os.path.exists(qemu)):
            RunCommand('wget https://github.com/idrawone/qemu-rpi/raw/master/tools/qemu-system-arm-rpi_UART1.tar.gz && tar xf qemu-system-arm-rpi_UART1.tar.gz')
    cmd='%s -m 128 -M versatilepb -nographic -kernel out/%s/%s/%s -serial tcp:127.0.0.1:1103,server'%(qemu,target,case,target)

    if(os.name == 'nt'):
        cmd = 'start '+cmd
        RunCommand(cmd)
        pid = 1
    else:
        pid = os.fork()
    if(pid == 0):
        RunCommand('pgrep qemu-system-arm | xargs -i kill -9 {}')
        RunCommand(cmd)
        exit(0)
    else:
        result=telnet('127.0.0.1', 1103)
        if(os.name == 'nt'):
            RunCommand('taskkill /IM qemu-system-arm.exe')
        else:
            os.kill(pid,9)
            RunCommand('pgrep qemu-system-arm | xargs -i kill -9 {}')
        if((result.find('FAIL')!=-1) or (result.find('>> END <<')==-1)):
            print('>> Test for %s %s FAIL'%(target,case))
            print(result)
            erp = '>> Test for %s %s FAIL\n'%(target,case)
            erp += result
            exit(-1)
        print('>> Test for %s %s PASS'%(target,case))

def test(target,case,vv):
    if(os.name == 'nt'):
        os.makedirs('src/%s/%s'%(target, case),exist_ok=True)
    else:
        RunCommand('mkdir -p src/%s/%s'%(target, case))
    if(target == 'test'):
        xml = reoil.to_xml('%s/%s.oil'%(case,target))
        fixXml(xml,vv,True)
    else:
        xml = reoil.to_xml('%s/etc/%s.oil'%(CTEST,target))
        fixXml(xml,vv)
        genCTEST_CFGH(xml,'src/%s/%s'%(target, case))
    saveXml(xml, 'src/%s/%s/test.xml'%(target, case))
    RunCommand('make dep-os TARGET=%s CASE=%s'%(target, case))
    RunCommand(cmd='make all TARGET=%s CASE=%s'%(target, case))
    check(target,case)

if(__name__ == '__main__'):
    AppendPythonPath(['../../com/as.tool/config.infrastructure.system',
              '../../com/as.tool/config.infrastructure.system/third_party'])

    if(len(sys.argv) == 2 and sys.argv[1] == 'all'):
        cfg = parse()
        for v in cfg:
            target = v['target']
            for case,vv in v['case'].items():
                test(target,case,vv)
    elif(len(sys.argv) == 2):
        cfg = parse()
        searchflag=True
        for v in cfg:
            target = v['target']
            if(searchflag and target != sys.argv[1]): continue
            searchflag=False
            for case,vv in v['case'].items():
                test(target,case,vv)
    elif(len(sys.argv) == 3):
        cfg = parse()
        for v in cfg:
            target = v['target']
            if(target != sys.argv[1]): continue
            for case,vv in v['case'].items():
                if(case != sys.argv[2]): continue
                test(target,case,vv)
    else:
        print('Usage: %s all'%(sys.argv[0]))
        print('       %s target case\nExample:'%(sys.argv[0]))
        cfg = parse()
        count = 0
        for v in cfg:
            target = v['target']
            for case,vv in v['case'].items():
                print('\t%s %s %s'%(sys.argv[0],target,case))
                count += 1
                if(count > 8):
                    count = 0;
                    c = input('More <Enter> Exit <q>')
                    if(c == 'q'): exit(0)

