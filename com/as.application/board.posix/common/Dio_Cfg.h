

#if !(((DIO_SW_MAJOR_VERSION == 1) && (DIO_SW_MINOR_VERSION == 0)) )
#error Dio: Configuration file expected BSW module version to be 1.0.*
#endif


#ifndef DIO_CFG_H_
#define DIO_CFG_H_

#define DIO_VERSION_INFO_API    STD_OFF
#if defined(USE_DET)
#define DIO_DEV_ERROR_DETECT    STD_ON
#else
#define DIO_DEV_ERROR_DETECT    STD_OFF
#endif

#define DIO_END_OF_LIST  (-1u)

// Physical ports
typedef enum
{
  DIO_PORT_A = 0,
  DIO_PORT_B = 1,
  DIO_PORT_C = 2,
  DIO_PORT_D = 3,
  DIO_PORT_E = 4,
  DIO_PORT_F = 5,
  DIO_PORT_G = 6,
  DIO_PORT_H = 7,
  DIO_PORT_I = 8,
  DIO_PORT_J = 9,
  DIO_PORT_K = 10,
  DIO_PORT_NUM
} Dio_PortTypesType;


// Channels	
#define DIO_CHL_TelltaleTPMS                             0
#define DIO_CHL_TelltaleLowOil                           1
#define DIO_CHL_TelltalePosLamp                          2
#define DIO_CHL_TelltaleTurnLeft                         3
#define DIO_CHL_TelltaleTurnRight                        4
#define DIO_CHL_TelltaleAutoCruise                       5
#define DIO_CHL_TelltaleHighBeam                         6
#define DIO_CHL_TelltaleSeatbeltDriver                   7
#define DIO_CHL_TelltaleSeatbeltPassenger                8
#define DIO_CHL_TelltaleAirbag                           9
#define DIO_CHANNEL_NAME_LEDS_LED4	52
#define DIO_CHANNEL_NAME_LEDS_LED5	53

// Channel group

// Ports
#define DIO_PORT_NAME_LED_PORT 		(DIO_PORT_D)




// Pointers for convenience.
// Channels	
extern const Dio_ChannelType DioChannelConfigData[];
// Channel group
extern const Dio_ChannelGroupType DioConfigData[];
// Port
extern const Dio_PortType DioPortConfigData[];

#endif /*DIO_CFG_H_*/
