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
import re, os

import xml.etree.ElementTree as ET

__all__ = ['to_xml']

# 1: for comment 
re_comment_type1 = re.compile(r'/\*[^/]*\*/');
re_comment_type2 = re.compile(r'//.*');
## include 
re_include = re.compile(r'\s*#include\s+["<]([^\s]+)[">]');

# 2: for os obj
re_oil_os_obj = re.compile(r'^\s*OS|^\s*TASK|^\s*ALARM|^\s*COUNTER|^\s*RESOURCE|^\s*EVENT')
re_oil_os_obj_type_name = re.compile(r"""
    ^\s*(OS)\s*(\w+)
    |^\s*(TASK)\s*(\w+)
    |^\s*(ALARM)\s*(\w+)
    |^\s*(COUNTER)\s*(\w+)
    |^\s*(RESOURCE)\s*(\w+)
    """, re.VERBOSE)
# 3: for os <general>    
re_oil_os_general = re.compile(r'^\s*(OS)\s*(\w+)')
re_general_STATUS = re.compile(r'STATUS\s*=\s*(\w+)\s*;')
re_general_ERRORHOOK = re.compile(r'ERRORHOOK\s*=\s*(\w+)\s*;')
re_general_PRETASKHOOK = re.compile(r'PRETASKHOOK\s*=\s*(\w+)\s*;')
re_general_POSTTASKHOOK = re.compile(r'POSTTASKHOOK\s*=\s*(\w+)\s*;')
re_general_SHUTDOWNHOOK = re.compile(r'SHUTDOWNHOOK\s*=\s*(\w+)\s*;')
re_general_STARTUPHOOK = re.compile(r'STARTUPHOOK\s*=\s*(\w+)\s*;')
re_general_SystemTimer = re.compile(r'SystemTimer\s*=\s*(\w+)\s*;')
re_general_TickTime = re.compile(r'TickTime\s*=\s*(\w+)\s*;')

# 4: for task
re_oil_os_task = re.compile(r'^\s*(TASK)\s*(\w+)')
re_task_SCHEDULE = re.compile(r'SCHEDULE\s*=\s*(\w+)\s*;')
re_task_PRIORITY = re.compile(r'PRIORITY\s*=\s*(\w+)\s*;')
re_task_ACTIVATION = re.compile(r'ACTIVATION\s*=\s*(\w+)\s*;')
re_task_AUTOSTART = re.compile(r'AUTOSTART\s*=\s*(\w+)\s*[;{]')
re_task_StackSize = re.compile(r'StackSize\s*=\s*(\w+)\s*;') #for MB Test
re_task_STACK = re.compile(r'STACK\s*=\s*(\w+)\s*;') #for FreeOSEK
re_task_appmode_list = re.compile(r'AUTOSTART\s*=\s*TRUE\s*{([^{}]*)}\s*;')
re_task_APPMODE = re.compile(r'APPMODE\s*=\s*(\w+)')
re_task_RESOURCE = re.compile(r'RESOURCE\s*=\s*(\w+)')
re_task_EVENT = re.compile(r'EVENT\s*=\s*(\w+)')

# 6: for counter
re_oil_os_counter = re.compile(r'^\s*(COUNTER)\s*(\w+)')
re_counter_MAXALLOWEDVALUE = re.compile(r'MAXALLOWEDVALUE\s*=\s*(\w+)\s*;')
re_counter_TICKSPERBASE = re.compile(r'TICKSPERBASE\s*=\s*(\w+)\s*;')
re_counter_MINCYCLE = re.compile(r'MINCYCLE\s*=\s*(\w+)\s*;')

# 5: for alarm
re_oil_os_alarm = re.compile(r'^\s*(ALARM)\s*(\w+)')
re_alarm_COUNTER = re.compile(r'COUNTER\s*=\s*(\w+)\s*;')
re_alarm_ACTION = re.compile(r'ACTION\s*=\s*(ACTIVATETASK|SETEVENT|ALARMCALLBACK|INCREMENT)\s*{([^{}]+)}\s*;')
re_action_TASK = re.compile(r'TASK\s*=\s*(\w+)\s*;')
re_action_EVENT = re.compile(r'EVENT\s*=\s*(\w+)\s*;')
re_action_ALARMCALLBACKNAME = re.compile(r'ALARMCALLBACKNAME\s*=\s*"(\w+)"\s*;')
re_action_COUNTER = re.compile(r'COUNTER\s*=\s*(\w+)\s*;')
re_alarm_AUTOSTART = re.compile(r'AUTOSTART\s*=\s*(\w+)\s*[;{]')
re_alarm_appmode_list = re.compile(r'AUTOSTART\s*=\s*TRUE\s*{([^{}]*)}\s*;')
re_alarm_APPMODE = re.compile(r'APPMODE\s*=\s*(\w+)')
re_alarm_ALARMTIME = re.compile(r'ALARMTIME\s*=\s*(\w+)')
re_alarm_CYCLETIME = re.compile(r'CYCLETIME\s*=\s*(\w+)')

# 6: for resource
re_oil_os_resource = re.compile(r'^\s*(RESOURCE)\s*(\w+)')
re_resource_property = re.compile(r'RESOURCEPROPERTY\s*=\s*(STANDARD|LINKED|INTERNAL)\s*;')

# 7: for event
re_oil_os_event = re.compile(r'^\s*(EVENT)\s*(\w+)')
re_event_MASK = re.compile(r'MASK\s*=\s*(\w+)\s*;')

def findObj(oscfg, tag, name):
    tgt=None
    for obj in oscfg:
        if(obj.tag==tag and obj.attrib['Name']==name):
            tgt=obj
            break
    if(tgt is None):
        tgt = ET.Element(tag)
        tgt.attrib['Name'] = name
        oscfg.append(tgt)
    return tgt

def filter_out_comment(text):
    """text should be just a line"""
    #filter out comments like "/* .. */"
    grp = re_comment_type1.split(text)
    result = ''.join(grp);
    #filter out comments like "//...."
    grp = re_comment_type2.split(result);
    result = ''.join(grp);
    result = ''.join(result.split('\n')) #remove the line break
    return(''+result);

def oil_process_os(item, oscfg):
    grp = re_oil_os_general.search(item).groups();
    if(grp[0] != 'OS'):
        return;
    general = oscfg.find('General')
    if(general is None):
        general = ET.Element('General')
        oscfg.append(general)
    if(re_general_STATUS.search(item)):
        general.attrib['Status'] = re_general_STATUS.search(item).groups()[0];
    if(re_general_ERRORHOOK.search(item)):
        general.attrib['ErrorHook'] = re_general_ERRORHOOK.search(item).groups()[0];
    if(re_general_PRETASKHOOK.search(item)):
        general.attrib['PreTaskHook'] = re_general_PRETASKHOOK.search(item).groups()[0];
    if(re_general_POSTTASKHOOK.search(item)):
        general.attrib['PostTaskHook'] = re_general_POSTTASKHOOK.search(item).groups()[0];
    if(re_general_SHUTDOWNHOOK.search(item)):
        general.attrib['ShutdownHook'] = re_general_SHUTDOWNHOOK.search(item).groups()[0];
    if(re_general_STARTUPHOOK.search(item)):
        general.attrib['StartupHook'] = re_general_STARTUPHOOK.search(item).groups()[0];
    if(re_general_SystemTimer.search(item)):
        cnt = findObj(oscfg, 'Counter', 'SystemTimer')
        cnt.attrib['MaxAllowed'] = '32767'
        cnt.attrib['TicksPerBase'] = '1'
        cnt.attrib['MinCycle'] = '1'

def oil_process_task(item, oscfg):
    grp = re_oil_os_task.search(item).groups();
    if(grp[0] != 'TASK'):
        return
    name = grp[1];
    tsk=findObj(oscfg,'Task', name)
    #now start to process it
    if(re_task_SCHEDULE.search(item)):
        tsk.attrib['Schedule'] = re_task_SCHEDULE.search(item).groups()[0];
    # should convert priority,because in gainos, the smaller value of priority has higher
    # priority,so now I am tired....
    if(re_task_PRIORITY.search(item)):
        tsk.attrib['Priority'] = re_task_PRIORITY.search(item).groups()[0];
    if(re_task_ACTIVATION.search(item)):
        tsk.attrib['Activation'] = re_task_ACTIVATION.search(item).groups()[0];
    if(re_task_AUTOSTART.search(item)):
        tsk.attrib['Autostart'] = re_task_AUTOSTART.search(item).groups()[0];
        if(tsk.attrib['Autostart'].upper() == 'TRUE'):
            if(re_task_appmode_list.search(item)):
                appmode = re_task_appmode_list.search(item).groups()[0];
                for mode in appmode.split(';'):
                    if(re_task_APPMODE.search(mode)):
                        modelist = tsk.find('ApplicationModeList')
                        if(modelist is None):
                            modelist = ET.Element('ApplicationModeList')
                            tsk.append(modelist)
                        modename = re_task_APPMODE.search(mode).groups()[0]
                        modend = ET.Element('ApplicationMode')
                        modend.attrib['Name'] = modename
                        modelist.append(modend)
    if(re_task_StackSize.search(item)):
        tsk.attrib['StackSize'] = re_task_StackSize.search(item).groups()[0];
    elif(re_task_STACK.search(item)):
         tsk.attrib['StackSize'] = re_task_STACK.search(item).groups()[0];
    #for resource
    for subitem in item.split(';'): #maybe sereval resource
        if(re_task_RESOURCE.search(subitem)):
            reslist = tsk.find('ResourceList')
            if(reslist is None):
                reslist = ET.Element('ResourceList')
                tsk.append(reslist)
            resname = re_task_RESOURCE.search(subitem).groups()[0]
            resnd = ET.Element('Resource')
            resnd.attrib['Name'] = resname
            reslist.append(resnd)
    # for EVENT
    for subitem in item.split(';'): #maybe sereval event
        if(re_task_EVENT.search(subitem)): 
            name = re_task_EVENT.search(subitem).groups()[0]
            evtlist = tsk.find('EventList')
            if(evtlist is None):
                evtlist = ET.Element('EventList')
                tsk.append(evtlist)
            evnd = ET.Element('Event')
            evnd.attrib['Name'] = name
            evnd.attrib['Mask'] = 'AUTO'
            evtlist.append(evnd)

def oil_process_counter(item, oscfg):
    grp = re_oil_os_counter.search(item).groups();
    if(grp[0] != 'COUNTER'):
        return
    name = grp[1];
    cnt=findObj(oscfg,'Counter', name)
    if(re_counter_MAXALLOWEDVALUE.search(item)):
        cnt.attrib['MaxAllowed'] = re_counter_MAXALLOWEDVALUE.search(item).groups()[0]; 
    if(re_counter_TICKSPERBASE.search(item)):
        cnt.attrib['TicksPerBase'] = re_counter_TICKSPERBASE.search(item).groups()[0]; 
    if(re_counter_MINCYCLE.search(item)):
        cnt.attrib['MinCycle'] = re_counter_MINCYCLE.search(item).groups()[0]; 
    
def oil_process_alarm(item, oscfg):
    grp = re_oil_os_alarm.search(item).groups();
    if(grp[0] != 'ALARM'):
        return
    name = grp[1];
    alm=findObj(oscfg,'Alarm', name)
    if(re_alarm_COUNTER.search(item)):
        alm.attrib['Counter'] = re_alarm_COUNTER.search(item).groups()[0];
    if(re_alarm_ACTION.search(item)):
        action = re_alarm_ACTION.search(item).groups(); 
        if(action[0] == 'ACTIVATETASK'):
            alm.attrib['Action'] = 'ActivateTask';
            if(re_action_TASK.search(action[1])):
                alm.attrib['Task'] = re_action_TASK.search(action[1]).groups()[0]
        elif(action[0] == 'SETEVENT'):
            alm.attrib['Action'] = 'SetEvent';
            if(re_action_TASK.search(action[1])):
                alm.attrib['Task'] = re_action_TASK.search(action[1]).groups()[0]
            if(re_action_EVENT.search(action[1])):
                alm.attrib['Event'] = re_action_EVENT.search(action[1]).groups()[0]
        elif(action[0] == 'ALARMCALLBACK'):
            alm.attrib['Action'] = 'Callback';
            if(re_action_ALARMCALLBACKNAME.search(action[1])):
                alm.attrib['Callback'] = re_action_ALARMCALLBACKNAME.search(action[1]).groups()[0]
        elif(action[0] == 'INCREMENT'):
            alm.attrib['Action'] = 'SignalCounter';
            if(re_action_COUNTER.search(action[1])):
                alm.attrib['Counter'] = re_action_COUNTER.search(action[1]).groups()[0]

    if(re_alarm_AUTOSTART.search(item)):
        alm.attrib['Autostart'] = re_alarm_AUTOSTART.search(item).groups()[0];
        if(alm.attrib['Autostart'].upper() == 'TRUE'):
            if(re_alarm_appmode_list.search(item)):
                appmode = re_alarm_appmode_list.search(item).groups()[0];
                for mode in appmode.split(';'):
                    if(re_alarm_APPMODE.search(mode)):
                        modename = re_alarm_APPMODE.search(mode).groups()[0]
                        modelist = alm.find('ApplicationModeList')
                        if(modelist is None):
                            modelist = ET.Element('ApplicationModeList')
                            alm.append(modelist)
                        modename = re_task_APPMODE.search(mode).groups()[0]
                        modend = ET.Element('ApplicationMode')
                        modend.attrib['Name'] = modename
                        modelist.append(modend)
    if(re_alarm_ALARMTIME.search(item)):
        alm.attrib['StartTime'] = re_alarm_ALARMTIME.search(item).groups()[0]
    if(re_alarm_CYCLETIME.search(item)):
        alm.attrib['Period'] = re_alarm_CYCLETIME.search(item).groups()[0]

def oil_process_resource(item, oscfg):
    grp = re_oil_os_resource.search(item).groups();
    if(grp[0] != 'RESOURCE'):
        return
    name = grp[1];
    if(re_resource_property.search(item)):
        type = re_resource_property.search(item).groups()[0];
        if(type == 'STANDARD'):
            res=findObj(oscfg,'Resource', name)
        elif(type == 'INTERNAL'):
            res=findObj(oscfg,'InternalResource', name)
    else:
        res=findObj(oscfg,'Resource', name)

def oil_process_event(item, oscfg):
    grp = re_oil_os_event.search(item).groups();
    if(grp[0] != 'EVENT'):
        return
    name = grp[1];
    ent=findObj(oscfg,'Event', name)
    ent.attrib['Mask'] = 'AUTO'
    if(re_event_MASK.search(item)):
        ent.attrib['Mask'] = re_event_MASK.search(item).groups()[0]

def oil_process(item, oscfg):
    if(re_oil_os_task.search(item)):
        oil_process_task(item, oscfg);
    elif(re_oil_os_general.search(item)):
        oil_process_os(item, oscfg);
    elif(re_oil_os_counter.search(item)):
        oil_process_counter(item, oscfg);
    elif(re_oil_os_alarm.search(item)):
        oil_process_alarm(item, oscfg);
    elif(re_oil_os_resource.search(item)):
        oil_process_resource(item, oscfg);
    elif(re_oil_os_event.search(item)):
        oil_process_event(item, oscfg);
        
def to_xml(oilfile,cfg=None):
    oscfg = cfg
    if(oscfg is None):
        oscfg = ET.Element('Os')
    fp = open(oilfile, 'r');
    oneitem = ''; #one item is minimum object such as TASK,ALARM ...
    barcenum = 0; #remember the brace number, when encounter " { ", +1; when " } " -1.
    brace_flag = False; #has " { " encountered or not
    process_one_item_start = False #has match an obj start or not
    reFreeOSEK = re.compile(r'^\s*OSEK\s+OSEK\s*{\s*')
    for el in fp.readlines():
        if(reFreeOSEK.search(el)): continue
        #firstly, filter out the comment on this line
        el = filter_out_comment(el);
        if(process_one_item_start == False):
        #{
            oneitem = ''; 
            barcenum = 0;
            brace_flag = False;
            if(re_oil_os_obj.search(el)):
                process_one_item_start = True;
                oneitem += el;
                if(el[-1:]==';'):
                    brace_flag = True;
                if(el.count('{') > 0):  #so at comment should not include '{}'
                    brace_flag = True;
                    barcenum += el.count('{');
                if(el.count('}') > 0):
                    barcenum -= el.count('}');
                if((brace_flag == True) and (barcenum == 0)): #in one line
                    #filter out the multi-line comment
                    oneitem = filter_out_comment(oneitem)
                    oil_process(oneitem, oscfg);
                    process_one_item_start = False
            elif(re_include.search(el)): #include file
                basep = os.path.dirname(oilfile)
                file = re_include.search(el).groups()[0];
                file = basep+'/'+file.replace('\\','/');
                to_xml(file, oscfg);
        #}
        else:
        #{
            if(re_include.search(el)): #include file
                basep = os.path.dirname(oilfile)
                file = re_include.search(el).groups()[0];
                file = basep+'/'+file;
                to_xml(file, oscfg);
                continue;
            if(el.count('{') > 0):  #so at comment should not include '{}'
                brace_flag = True;
                barcenum += el.count('{');
            if(el.count('}') > 0):
                barcenum -= el.count('}');
            oneitem += el;
            if((brace_flag == True) and (barcenum == 0)):
                #filter out the multi-line comment
                oneitem = filter_out_comment(oneitem)
                oil_process(oneitem, oscfg);
                process_one_item_start = False
        #}
    fp.close();
    return oscfg;

if(__name__ == '__main__'):
    import sys
    if(len(sys.argv) != 3):
        print("Usage: %s OIL XML"%(sys.argv[0]))
    else:
        oscfg = to_xml(sys.argv[1])
        # save to xml
        root = ET.Element('AS')
        root.append(oscfg)
        tree = ET.ElementTree(root)
        tree.write(sys.argv[2], encoding="utf-8", xml_declaration=True);
        fp = open(sys.argv[2],'r')
        content = fp.read()
        fp.close()
        fp = open(sys.argv[2],'w')
        fp.write(content.replace('>','>\n'))
        fp.close()
        print(" >> REOIL %s to %s"%(sys.argv[1],sys.argv[2]))
