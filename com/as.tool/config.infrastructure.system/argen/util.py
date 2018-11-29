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
import glob
import xml.etree.ElementTree as ET
__all__ = ['ScanXML','ScanFrom']

def ScanFrom(root,tag):
    a_list = []
    for each in root:
        if(each.tag==tag):
            a_list.append(each)
    return a_list

def OsAppend(oslist, obj):
    def compare(a,b):
        if(str(a.items()) != str(b.items())):
            return True
        for ss in obj:
            # there is sub items
            return True
        return False

    for old in oslist:
        if(old.tag == obj.tag):
            if((old.tag == 'General') or (old.attrib['Name'] == obj.attrib['Name'])):
                if(compare(old, obj)):
                    print('WARNING: replace %s from \n\t%s\n\tto\n\t%s!'%(obj.tag, old.items(),obj.items()))
                    oslist.remove(old)
                    oslist.append(obj)
                return
    oslist.append(obj)

def ScanXML(gendir,tag):
    a_list = []
    for xml in glob.glob('%s/*.xml'%(gendir))+glob.glob('%s/*.arxml'%(gendir)):
        root = ET.parse(xml).getroot();
        if((root.tag=='AS') or (root.tag=='AUTOSAR')):
            for each in root:
                if(each.tag==tag):
                    for sub in each:
                        a_list.append(sub)
                elif((each.tag=='OS') and (tag=='Os')):
                    for sub in each:
                        if(sub.tag == 'General'):
                            OsAppend(a_list, sub)
                        else:
                            for ss in sub:
                                OsAppend(a_list, ss)
    return a_list
