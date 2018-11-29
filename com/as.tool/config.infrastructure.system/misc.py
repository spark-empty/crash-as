import sys,os

def parse_as_xls_com(filename):
    import xlrd
    scom = {}
    book = xlrd.open_workbook(filename)
    sheet = book.sheet_by_name('COM')
    for row in range(5,sheet.nrows):
        signal = []
        for col in range(1,sheet.ncols):
            signal.append(str(sheet.cell(row,col).value))
        name = signal[0]
        try:
            scom[name].append(signal)
        except KeyError:
            scom[name]=[signal]
    return scom

def test_as_xls_com():
    for name,signals in parse_as_xls_com('AS.xlsm').items():
        print('%s = {'%(name))
        for sig in signals:
            print('\t%s'%(sig))
        print('}')

def test_autosar():
    sys.path.append(os.path.abspath('./third_party'))
    import autosar
    ws=autosar.workspace()
    
    dataTypes=ws.createPackage('DataType')
    dataTypes.createSubPackage('DataTypeSemantics', role='CompuMethod')
    dataTypes.createSubPackage('DataTypeUnits', role='Unit')
    
    dataTypes.createIntegerDataType('EngineSpeed_T', min=0, max=65535, offset=0, scaling=1/8, unit='rpm')
    dataTypes.createIntegerDataType('VehicleSpeed_T', min=0, max=65535, offset=0, scaling=1/64,unit='kph')
    dataTypes.createIntegerDataType('Percent_T', min=0, max=255, offset=0, scaling=0.4, unit='Percent')
    dataTypes.createIntegerDataType('CoolantTemp_T', min=0, max=255, offset=-40, scaling=0.5, unit='DegreeC')
    dataTypes.createIntegerDataType('InactiveActive_T', valueTable=[
         'InactiveActive_Inactive',
         'InactiveActive_Active',
         'InactiveActive_Error',
         'InactiveActive_NotAvailable'])
    dataTypes.createIntegerDataType('OnOff_T', valueTable=[
        "OnOff_Off",
        "OnOff_On",
        "OnOff_Error",
        "OnOff_NotAvailable"])
    
    package=ws.createPackage('Constant', role='Constant')
    package.createConstant('C_AntiLockBrakingActive_IV', '/DataType/InactiveActive_T', 3)
    package.createConstant('C_TelltaleAntiLockBrakingActive_IV', '/DataType/OnOff_T', 0)
    
    package = ws.createPackage('PortInterface', role='PortInterface')
    package.createSenderReceiverInterface("AntiLockBrakingActive_I", autosar.DataElement('AntiLockBrakingStatus', '/DataType/InactiveActive_T'))
    package.createSenderReceiverInterface("TelltaleAntiLockBrakingActive_I", autosar.DataElement('TelltaleAntiLockBrakingStatus', '/DataType/OnOff_T'))

    package=ws.createPackage("ComponentType", role="ComponentType")
    swc = package.createApplicationSoftwareComponent('AntiLockBraking')
    swc.createRequirePort('AntiLockBrakingActive', 'AntiLockBrakingActive_I', initValueRef='C_AntiLockBrakingActive_IV')
    swc.createProvidePort('TelltaleAntiLockBrakingActive', 'TelltaleAntiLockBrakingActive_I', initValueRef='C_TelltaleAntiLockBrakingActive_IV')
    
    portAccessList = ['AntiLockBrakingActive', 'TelltaleAntiLockBrakingActive']
    swc.behavior.createRunnable('AntiLockBrakingActive_run', portAccess=portAccessList)
    swc.behavior.createTimingEvent('AntiLockBrakingActive_run', period=20)
    rtegen = autosar.RteGenerator()
    rtegen.writeComponentHeaders(swc, 'derived')

if(__name__ == '__main__'):
    test_autosar()
