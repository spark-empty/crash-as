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
import os
import traceback

__all__=['ArGen','ArGenMain']
from .GenOS import GenOS
from .GenCan import GenCan
from .GenCanIf import GenCanIf
from .GenPduR import GenPduR
from .GenCanTp import GenCanTp
from .GenCom import GenCom
from .GenDcm import GenDcm
from .GenFls import GenFls
from .GenFee import GenFee
from .GenEa import GenEa
from .GenNvM import GenNvM
from .GenXcp import GenXcp
from .GenDem  import GenDem
from .GenRte import GenRte
from .GenJ1939Tp import GenJ1939Tp

def dummy(arxml,dir):
    pass

__gen_engine =  {   
    'OS':GenOS,
    'Can':GenCan,'CanIf':GenCanIf,'CanTp':GenCanTp,'PduR':GenPduR,'Com':GenCom,'Dcm':GenDcm,
    'Fls':GenFls,'Fee':GenFee,'Ea':GenEa,'NvM':GenNvM,
    'Rte':GenRte,
    'Xcp':GenXcp,
    'Dem':GenDem,
    'EcuC':dummy,
    'J1939Tp':GenJ1939Tp
}

def ArGen(arxml,dir, skipos=True):
    if(arxml.tag == 'OS' and skipos):
        return # supress OS Gen
    try:
        engine = __gen_engine[arxml.tag]
    except KeyError:
        print('TODO: generator engine for "%s" is not implemented'%(arxml.tag))
        return
    engine(arxml,dir)

def ArGenMain(wfxml,gendir):
    import xml.etree.ElementTree as ET
    if(os.path.exists(wfxml)):
        root = ET.parse(wfxml).getroot();
        for arxml in root:
            ArGen(arxml,gendir)