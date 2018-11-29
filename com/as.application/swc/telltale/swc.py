import sys,os
import autosar

from BSWCOM import *

class InactiveActive_T(autosar.Template):
   valueTable=['InactiveActive_Inactive',
               'InactiveActive_Active',
               'InactiveActive_Error',
               'InactiveActive_NotAvailable']
   @classmethod
   def apply(cls, ws):
      package = ws.getDataTypePackage()
      if package.find(cls.__name__) is None:
         package.createIntegerDataType(cls.__name__, valueTable=cls.valueTable)

class OnOff_T(autosar.Template):
   valueTable=['OnOff_Off',
               'OnOff_On',
               'OnOff_1Hz',
               'OnOff_2Hz',
               'OnOff_3Hz']
   @classmethod
   def apply(cls, ws):
      package = ws.getDataTypePackage()
      if package.find(cls.__name__) is None:
         package.createIntegerDataType(cls.__name__, valueTable=cls.valueTable)

ttList=['TPMS','LowOil','PosLamp','TurnLeft','TurnRight','AutoCruise','HighBeam',
                'SeatbeltDriver','SeatbeltPassenger','Airbag']
# TelltaleStatus: means the COM signals which control the related Telltale status
# TelltaleState: means the state of Telltale: on, off or flash
C_TelltaleStatus_IV = {}
C_TelltaleState_IV = {}
TelltaleStatus_I = {}
TelltaleState_I = {}
TelltaleStatus = {}
TelltaleState = {}
for tt in ttList:
    C_TelltaleStatus_IV[tt] = autosar.createConstantTemplateFromEnumerationType('C_%sStatus_IV'%(tt), InactiveActive_T, 3)
    C_TelltaleState_IV[tt] = autosar.createConstantTemplateFromEnumerationType('C_Telltale%sStatus_IV'%(tt), OnOff_T, 3)
    TelltaleStatus_I[tt] = autosar.createSenderReceiverInterfaceTemplate("%sStatus_I"%(tt),InactiveActive_T,"%sStatus"%(tt))
    TelltaleState_I[tt] = autosar.createSenderReceiverInterfaceTemplate("Telltale%sStatus_I"%(tt),OnOff_T,"Telltale%sStatus"%(tt))
    TelltaleStatus[tt] = autosar.createSenderReceiverPortTemplate('%sStatusPort'%(tt), TelltaleStatus_I[tt], C_TelltaleStatus_IV[tt], aliveTimeout=30)
    TelltaleState[tt] = autosar.createSenderReceiverPortTemplate('Telltale%sStatusPort'%(tt), TelltaleState_I[tt], C_TelltaleState_IV[tt], aliveTimeout=30)

class Telltale(autosar.Template):
    @classmethod
    def apply(cls, ws):
        componentName = cls.__name__
        package = ws.getComponentTypePackage()
        if package.find(componentName) is None:
            swc = package.createApplicationSoftwareComponent(componentName)
            cls.addPorts(swc)
            cls.addBehavior(swc)

    @classmethod
    def addPorts(cls, swc):
        componentName = cls.__name__
        for tt in ttList:
            #swc.apply(TelltaleStatus[tt].Receive)
            swc.apply(TelltaleState[tt].Send)
        swc.apply(Led1Sts.Receive)
        swc.apply(Led2Sts.Receive)
        swc.apply(Led3Sts.Receive)

    @classmethod
    def addBehavior(cls, swc):
         swc.behavior.createRunnable('Telltale_run', portAccess=[x.name for x in swc.requirePorts+swc.providePorts])
         swc.behavior.createTimingEvent('Telltale_run', period=20)

if(__name__ == '__main__'):
    autosar.asSWCGen(Telltale)