"""/* Copyright(C) 2013, OpenSAR by Fan Wang(parai). All rights reserved.
 *
 * This file is part of OpenSAR.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Email: parai@foxmail.com
 * Source Open At: https://github.com/parai/OpenSAR/
 */
"""
import sys,os
from .GCF import *

if(sys.version_info > (3,0)):
    import autosar

__all__ = ['GenRte']

__dir = '.'


def handleDataTypeInteger(dataTypes, data):
    if(GAGet(data,'Minimum') != 'TBD'):
        Minimum = Integer(GAGet(data,'Minimum'))
    else:
        Minimum = None
    if(GAGet(data,'Maximum') != 'TBD'):
        Maximum = Integer(GAGet(data,'Maximum'))
    else:
        Maximum = None
    if(GAGet(data,'ValueTable') != 'TBD'):
        ValueTable = []
        for v in GAGet(data,'ValueTable').split(','):
            v = v.strip()
            if(v != ''):
                ValueTable.append(v)
    else:
        ValueTable = None
    dataTypes.createIntegerDataType(GAGet(data,'Name'),
                    min = Minimum,
                    max = Maximum,
                    valueTable=ValueTable)

def handleSWC(swc, ws, componentType, portInterface):
    swcpkg = componentType.createApplicationSoftwareComponent(GAGet(swc,'Name'))
    portAccessList = []
    for port in GLGet(swc,'PortList'):
        portAccessList.append('%sPort'%(GAGet(port,'Name')))
        portInterface.createSenderReceiverInterface('%s_I'%(GAGet(port,'Name')),
                        autosar.DataElement('%s'%(GAGet(port,'Name')),
                        '/DataType/'+GAGet(port,'DataTypeRef')))
        if(GAGet(port,'Type') == 'Require'):
            swcpkg.createRequirePort('%sPort'%(GAGet(port,'Name')),
                                     '%s_I'%(GAGet(port,'Name')),
                                     initValueRef=GAGet(port,'InitValueRef'))
        else:
            swcpkg.createProvidePort('%sPort'%(GAGet(port,'Name')),
                                     '%s_I'%(GAGet(port,'Name')),
                                     initValueRef=GAGet(port,'InitValueRef'))
    swcpkg.behavior.createRunnable(GAGet(swc,'Runnable'), portAccess=portAccessList)
    partition = autosar.rte.Partition()
    partition.addComponent(swcpkg)
    rtegen = autosar.rte.TypeGenerator(partition)
    dirp = __dir + '/' + GAGet(swc,'Name')
    MKDir(dirp)
    rtegen.generate(dirp)
#    rtegen = autosar.rte.MockRteGenerator(partition)
#    rtegen.generate(dirp)
    rtegen = autosar.rte.ComponentHeaderGenerator(partition)
    rtegen.generate(dirp)
#    rtegen = autosar.rte.RteGenerator(partition)
#    rtegen.generate(dirp)


def GenRte(root,dir):
    global __dir
    if(sys.version_info < (3,0)):
        print('python3 is required for RTE generator')
        return
    GLInit(root)
    __dir = '%s'%(dir)
    if(len(GLGet('SwcList')) == 0):return
    ws=autosar.workspace()
    dataTypes=ws.createPackage('DataType')
    dataTypes.createSubPackage('DataTypeSemantics', role='CompuMethod')
    dataTypes.createSubPackage('DataTypeUnits', role='Unit')
    for data in GLGet('DataTypeList'):
        if(GAGet(data,'Type') == 'Integer'):
            handleDataTypeInteger(dataTypes, data)
    constpkg=ws.createPackage('Constant', role='Constant')
    for const in GLGet('ConstantList'):
        constpkg.createConstant(GAGet(const,'Name'),
                               '/DataType/'+GAGet(const,'Type'),
                               Integer(GAGet(const,'Value')))
    portInterface = ws.createPackage('PortInterface', role='PortInterface')
    componentType=ws.createPackage('ComponentType', role='ComponentType')
    for swc in GLGet('SwcList'):
        handleSWC(swc, ws, componentType, portInterface)
    print('    >>> Gen Rte DONE <<<')
