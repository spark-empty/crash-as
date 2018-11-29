import autosar

C_VehicleSpeed_IV = autosar.createConstantTemplateFromPhysicalType('C_VehicleSpeed_IV', autosar.UINT16_T)
C_TachoSpeed_IV = autosar.createConstantTemplateFromPhysicalType('C_TachoSpeed_IV', autosar.UINT16_T)
C_Led1Sts_IV = autosar.createConstantTemplateFromPhysicalType('C_Led1Sts_IV', autosar.UINT8_T)
C_Led2Sts_IV = autosar.createConstantTemplateFromPhysicalType('C_Led2Sts_IV', autosar.UINT8_T)
C_Led3Sts_IV = autosar.createConstantTemplateFromPhysicalType('C_Led3Sts_IV', autosar.UINT8_T)
C_year_IV = autosar.createConstantTemplateFromPhysicalType('C_year_IV', autosar.UINT16_T)
C_month_IV = autosar.createConstantTemplateFromPhysicalType('C_month_IV', autosar.UINT8_T)
C_day_IV = autosar.createConstantTemplateFromPhysicalType('C_day_IV', autosar.UINT8_T)
C_hour_IV = autosar.createConstantTemplateFromPhysicalType('C_hour_IV', autosar.UINT8_T)
C_minute_IV = autosar.createConstantTemplateFromPhysicalType('C_minute_IV', autosar.UINT8_T)
C_second_IV = autosar.createConstantTemplateFromPhysicalType('C_second_IV', autosar.UINT8_T)

VehicleSpeed_I = autosar.createSenderReceiverInterfaceTemplate('VehicleSpeed', autosar.UINT16_T)
TachoSpeed_I = autosar.createSenderReceiverInterfaceTemplate('TachoSpeed', autosar.UINT16_T)
Led1Sts_I = autosar.createSenderReceiverInterfaceTemplate('Led1Sts', autosar.UINT8_T)
Led2Sts_I = autosar.createSenderReceiverInterfaceTemplate('Led2Sts', autosar.UINT8_T)
Led3Sts_I = autosar.createSenderReceiverInterfaceTemplate('Led3Sts', autosar.UINT8_T)
year_I = autosar.createSenderReceiverInterfaceTemplate('year', autosar.UINT16_T)
month_I = autosar.createSenderReceiverInterfaceTemplate('month', autosar.UINT8_T)
day_I = autosar.createSenderReceiverInterfaceTemplate('day', autosar.UINT8_T)
hour_I = autosar.createSenderReceiverInterfaceTemplate('hour', autosar.UINT8_T)
minute_I = autosar.createSenderReceiverInterfaceTemplate('minute', autosar.UINT8_T)
second_I = autosar.createSenderReceiverInterfaceTemplate('second', autosar.UINT8_T)

VehicleSpeed = autosar.createSenderReceiverPortTemplate('VehicleSpeed', VehicleSpeed_I, C_VehicleSpeed_IV, aliveTimeout=30)
TachoSpeed = autosar.createSenderReceiverPortTemplate('TachoSpeed', TachoSpeed_I, C_TachoSpeed_IV, aliveTimeout=30)
Led1Sts = autosar.createSenderReceiverPortTemplate('Led1Sts', Led1Sts_I, C_Led1Sts_IV, aliveTimeout=30)
Led2Sts = autosar.createSenderReceiverPortTemplate('Led2Sts', Led2Sts_I, C_Led2Sts_IV, aliveTimeout=30)
Led3Sts = autosar.createSenderReceiverPortTemplate('Led3Sts', Led3Sts_I, C_Led3Sts_IV, aliveTimeout=30)
year = autosar.createSenderReceiverPortTemplate('year', year_I, C_year_IV, aliveTimeout=30)
month = autosar.createSenderReceiverPortTemplate('month', month_I, C_month_IV, aliveTimeout=30)
day = autosar.createSenderReceiverPortTemplate('day', day_I, C_day_IV, aliveTimeout=30)
hour = autosar.createSenderReceiverPortTemplate('hour', hour_I, C_hour_IV, aliveTimeout=30)
minute = autosar.createSenderReceiverPortTemplate('minute', minute_I, C_minute_IV, aliveTimeout=30)
second = autosar.createSenderReceiverPortTemplate('second', second_I, C_second_IV, aliveTimeout=30)