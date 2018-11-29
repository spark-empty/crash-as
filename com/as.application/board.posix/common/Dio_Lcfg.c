
#include "Dio.h"
#include "Dio_Cfg.h"

const Dio_ChannelType DioChannelConfigData[] = { 
	DIO_CHL_TelltaleTPMS,
	DIO_CHL_TelltaleLowOil,
	DIO_CHL_TelltalePosLamp,
	DIO_CHL_TelltaleTurnLeft,
	DIO_CHL_TelltaleTurnRight,
	DIO_CHL_TelltaleAutoCruise,
	DIO_CHL_TelltaleHighBeam,
	DIO_CHL_TelltaleSeatbeltDriver,
	DIO_CHL_TelltaleSeatbeltPassenger,
	DIO_CHL_TelltaleAirbag,
	DIO_CHANNEL_NAME_LEDS_LED4,
	DIO_CHANNEL_NAME_LEDS_LED5,
	DIO_END_OF_LIST
};

const Dio_PortType DioPortConfigData[] = { 
	DIO_PORT_A,
	DIO_PORT_B,
	DIO_PORT_NAME_LED_PORT,  
	DIO_END_OF_LIST
};

const Dio_ChannelGroupType DioConfigData[] = {
	{ 
	  .port = DIO_END_OF_LIST, 
	  .offset = 0, 
	  .mask = 0, 
	}
};
