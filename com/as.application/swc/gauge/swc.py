import sys,os
import autosar

class VehicleSpeed_T(autosar.Template):
   minValue=0
   maxValue=65535
   offset=0
   scaling=1/64
   unit='kmph'
   @classmethod
   def apply(cls, ws):
      package = ws.getDataTypePackage()
      if package.find(cls.__name__) is None:         
         package.createIntegerDataType(cls.__name__, min=cls.minValue, max=cls.maxValue, offset=cls.offset, scaling=cls.scaling, unit=cls.unit)

class EngineSpeed_T(autosar.Template):
   minValue=0
   maxValue=65535
   offset=0
   scaling=1/8
   unit='rpm'
   invalidRangeStart=None
   errorRangeStart=65024
   notAvailableRangeStart=65280
   @classmethod
   def apply(cls, ws):
      package = ws.getDataTypePackage()
      if package.find(cls.__name__) is None:         
         package.createIntegerDataType(cls.__name__, min=cls.minValue, max=cls.maxValue, offset=cls.offset, scaling=cls.scaling, unit=cls.unit)

VehicleSpeed_I = autosar.createSenderReceiverInterfaceTemplate('VehicleSpeed_I', VehicleSpeed_T)
EngineSpeed_I = autosar.createSenderReceiverInterfaceTemplate('EngineSpeed_I', EngineSpeed_T)

C_VehicleSpeed_IV = autosar.createConstantTemplateFromPhysicalType('C_VehicleSpeed_IV', VehicleSpeed_T)
C_EngineSpeed_IV = autosar.createConstantTemplateFromPhysicalType('C_EngineSpeed_IV', EngineSpeed_T)

VehicleSpeed = autosar.createSenderReceiverPortTemplate('VehicleSpeed', VehicleSpeed_I, C_VehicleSpeed_IV, aliveTimeout=30)
EngineSpeed = autosar.createSenderReceiverPortTemplate('EngineSpeed', EngineSpeed_I, C_EngineSpeed_IV, aliveTimeout=30)

class Gauge(autosar.Template):
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
      swc.apply(VehicleSpeed.Receive)
      swc.apply(EngineSpeed.Receive)
   
   @classmethod
   def addBehavior(cls, swc):
      componentName = cls.__name__
      swc.behavior.createRunnable(componentName+'_Init')
      swc.behavior.createRunnable(componentName+'_Exit')
      swc.behavior.createRunnable(componentName+'_Run', portAccess=[x.name for x in swc.requirePorts+swc.providePorts])
      swc.behavior.createTimerEvent(componentName+'_Run', 20)

if(__name__ == '__main__'):
    autosar.asSWCGen(Gauge)

