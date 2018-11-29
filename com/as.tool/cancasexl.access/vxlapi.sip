/* Define the SIP wrapper to the vxlapi library. 
 * python version 3 */  
%Module(name=vxlapi, language="C")  

typedef unsigned long XLuint64;
typedef XLuint64 XLaccess;
typedef short XLstatus;
typedef long XLportHandle;


struct s_xl_can_msg {
	unsigned long id;
	unsigned short flags;
	unsigned short dlc;
	XLuint64 res1;
	//unsigned char data [8];
	unsigned char* data
	{
		%GetCode
			sipPy = PyList_New(8);
			for(int i=0;i<8;i++)
			{
				PyList_SetItem(sipPy,i,PyLong_FromLong(sipCpp->data[i]));
			}
		%End
		
		%SetCode
			if(PyList_Size(sipPy)!=8)
			{
				PyErr_SetString(PyExc_ValueError,"the data must be exactly 8 bytes");
				sipErr = 1;
			}
			else
			{
				for(int i=0;i<8;i++)
				{
					sipCpp->data[i] = PyLong_AsLong(PyList_GetItem(sipPy,i));
				}
			}
		%End
	};
	XLuint64 res2;
};

typedef unsigned char XLeventTag;

struct s_xl_event {
	/*XLeventTag*/int tag;
	unsigned char chanIndex;
	unsigned short transId;
	unsigned short portHandle;
	unsigned char flags;
	unsigned char reserved;
	XLuint64 timeStamp;
	//union s_xl_tag_data tagData;
	s_xl_can_msg can_msg
	{
		%GetCode 
	    	sipPy = sipConvertFromType(&sipCpp->tagData.msg, sipType_s_xl_can_msg, NULL);
		%End
		
		%SetCode
			struct s_xl_can_msg*sipVal;
			int sipIsErr = 0;

		    sipVal = (struct s_xl_can_msg *)sipForceConvertToType(sipPy,sipType_s_xl_can_msg,NULL,SIP_NOT_NONE,NULL,&sipIsErr);

		    if (sipIsErr)
		        return -1;

		    sipCpp->tagData.msg = *sipVal;
		%End
	};
};

typedef s_xl_event XLevent;

typedef char *XLstringType;
struct s_xl_bus_params{
  unsigned int busType;
//  union {
//    struct {
//      unsigned int bitRate;
//      unsigned char sjw;
//      unsigned char tseg1;
//      unsigned char tseg2;
//      unsigned char sam;
//      unsigned char outputMode;
//    } can;
//    struct {
//      unsigned int activeSpeedGrade;
//      unsigned int compatibleSpeedGrade;
//      unsigned int inicFwVersion;
//    } most;
//    struct {
//
//      unsigned int status;
//      unsigned int cfgMode;
//      unsigned int baudrate;
//    } flexray;
//    struct {
//      unsigned char macAddr[6];
//      unsigned char connector;
//      unsigned char phy;
//      unsigned char link;
//      unsigned char speed;
//      unsigned char clockMode;
//      unsigned char bypass;
//    } ethernet;
//    unsigned char raw[32];
//  } data;
};
typedef s_xl_bus_params XLbusParams;
struct s_xl_channel_config {
	char* name/* [31 + 1]*/
	{
		%GetCode
			sipPy = PyBytes_FromStringAndSize(sipCpp->name, 32);
		%End
		
		%SetCode
			char *ptr;
			int length;

			if (PyBytes_AsStringAndSize(sipPy, &ptr, &length) == -1)
			{
				sipErr = 1;
			}
			else if (length >= 32)
			{
				/*
				 * Raise an exception because the length isn't exactly
				 * right.
				 */

				PyErr_SetString(PyExc_ValueError,
						"the name must be exactly < 32 bytes");
				sipErr = 1;
			}
			else
			{
				memcpy(sipCpp->name, ptr, length);
			}
		%End
	};
	unsigned char hwType;
	unsigned char hwIndex;
	unsigned char hwChannel;
	unsigned short transceiverType;
	unsigned short transceiverState;
	unsigned short configError;
	unsigned char channelIndex;
	XLuint64 channelMask;
	unsigned int channelCapabilities;
	unsigned int channelBusCapabilities;
	
	
	
	unsigned char isOnBus;
	unsigned int connectedBusType;
	XLbusParams busParams;
	
	unsigned int driverVersion;
	unsigned int interfaceVersion;
	unsigned int* raw_data/*[10]*/
	{
		%GetCode
			sipPy = PyList_New(10);
			for(int i=0;i<10;i++)
			{
				PyList_SetItem(sipPy,i,PyLong_FromLong(sipCpp->raw_data[i]));
			}
		%End
		
		%SetCode
			if(PyList_Size(sipPy)!=10)
			{
				PyErr_SetString(PyExc_ValueError,"the raw_data must be exactly 10 integers");
				sipErr = 1;
			}
			else
			{
				for(int i=0;i<10;i++)
				{
					sipCpp->raw_data[i] = PyLong_AsLong(PyList_GetItem(sipPy,i));
				}
			}
		%End
	};
	
	unsigned int serialNumber;
	unsigned int articleNumber;
	
	char* transceiverName/* [31 + 1]*/
	{
		%GetCode
			sipPy = PyBytes_FromStringAndSize(sipCpp->transceiverName, 32);
		%End
		
		%SetCode
			char *ptr;
			int length;

			if (PyBytes_AsStringAndSize(sipPy, &ptr, &length) == -1)
			{
				sipErr = 1;
			}
			else if (length >= 32)
			{
				/*
				 * Raise an exception because the length isn't exactly
				 * right.
				 */

				PyErr_SetString(PyExc_ValueError,
						"the transceiverName must be exactly < 32 bytes");
				sipErr = 1;
			}
			else
			{
				memcpy(sipCpp->transceiverName, ptr, length);
			}
		%End
	};
	
	unsigned int specialCabFlags;
	unsigned int dominantTimeout;
	unsigned char dominantRecessiveDelay;
	unsigned char recessiveDominantDelay;
	unsigned char connectionInfo;
	unsigned char currentlyAvailableTimestamps;
	unsigned short minimalSupplyVoltage;
	unsigned short maximalSupplyVoltage;
	unsigned int maximalBaudrate;
	unsigned char fpgaCoreCapabilities;
	unsigned char specialDeviceStatus;
	unsigned short channelBusActiveCapabilities;
	unsigned short breakOffset;
	unsigned short delimiterOffset;
	//unsigned int* reserved/*[3]*/;
} ;
typedef s_xl_channel_config XL_CHANNEL_CONFIG;
typedef XL_CHANNEL_CONFIG XLchannelConfig;
struct s_xl_driver_config {
	unsigned int dllVersion;
	unsigned int channelCount;
	//unsigned int* reserved/*[10]*/
	XLchannelConfig* channel /*[64]*/
	{
		%GetCode 
			sipPy = PyList_New(64);
			for(int i=0;i<64;i++)
			{
				PyList_SetItem(sipPy,i,sipConvertFromType(&sipCpp->channel[i], sipType_s_xl_channel_config, NULL));
			}
		%End
		
		%SetCode
			if(PyList_Size(sipPy)!=64)
			{
				PyErr_SetString(PyExc_ValueError,"the channel must be exactly 64 s_xl_channel_config");
				sipErr = 1;
			}
			else
			{
				struct s_xl_channel_config*sipVal;
				int sipIsErr = 0;
				for(int i=0;i<64;i++)
				{
				    sipVal = (struct s_xl_channel_config *)sipForceConvertToType(sipPy,sipType_s_xl_channel_config,NULL,SIP_NOT_NONE,NULL,&sipIsErr);

				    if (sipIsErr)
				        return -1;

				    sipCpp->channel[i] = *sipVal;
				}
			}
		%End
	};
} ;
typedef s_xl_driver_config XL_DRIVER_CONFIG;
typedef XL_DRIVER_CONFIG XLdriverConfig;
struct s_xl_can_tx_msg {
  unsigned int canId;
  unsigned int msgFlags;
  unsigned char dlc;
  //unsigned char reserved[7];
  unsigned char* data/*[64]*/
 {
		%GetCode
			sipPy = PyList_New(64);
			for(int i=0;i<64;i++)
			{
				PyList_SetItem(sipPy,i,PyLong_FromLong(sipCpp->data[i]));
			}
		%End
		
		%SetCode
			int length = PyList_Size(sipPy);
			if(length >=64)
			{
				PyErr_SetString(PyExc_ValueError,"the data must be exactly <= 64 bytes");
				sipErr = 1;
			}
			else
			{
				for(int i=0;i<length;i++)
				{
					sipCpp->data[i] = PyLong_AsLong(PyList_GetItem(sipPy,i));
				}
			}
		%End
	};
} ;
typedef s_xl_can_tx_msg XL_CAN_TX_MSG;
struct s_xl_can_tx_event {
  unsigned short tag;
  unsigned short transId;
  unsigned char channelIndex;
  //unsigned char reserved[3];

  //union {
    XL_CAN_TX_MSG canMsg
	{
		%GetCode 
			sipPy = sipConvertFromType(&sipCpp->tagData.canMsg, sipType_s_xl_can_tx_msg, NULL);
		%End
		
		%SetCode
			struct s_xl_can_tx_msg*sipVal;
			int sipIsErr = 0;

			sipVal = (struct s_xl_can_tx_msg *)sipForceConvertToType(sipPy,sipType_s_xl_can_tx_msg,NULL,SIP_NOT_NONE,NULL,&sipIsErr);

			if (sipIsErr)
				return -1;

			sipCpp->tagData.canMsg = *sipVal;
		%End
	};
  //} tagData;
};
typedef s_xl_can_tx_event XLcanTxEvent;

XLstatus   xlOpenDriver(void);
XLstatus   xlCloseDriver(void);
/*
 * status,portHandle,permissionMask = xlOpenPort( userName,	// bytearray(b'port0')
 * 											accessMask,
 * 											permissionMask,
 * 											rxQueueSize=512,
 * 											xlInterfaceVersion=XL_INTERFACE_VERSION,
 * 											busType=XL_BUS_TYPE_CAN )
 */
XLstatus   xlOpenPort ( XLportHandle *pPortHandle, char *userName, XLaccess accessMask, 
					XLaccess *pPermissionMask /In,Out/,
					unsigned int rxQueueSize=512, 
					unsigned int xlInterfaceVersion=XL_INTERFACE_VERSION, 
					unsigned int busType=XL_BUS_TYPE_CAN);

XLstatus   xlCanSetChannelBitrate ( XLportHandle portHandle=0, XLaccess accessMask=1,
					unsigned long bitrate=500000);
XLstatus   xlActivateChannel ( XLportHandle portHandle=0, XLaccess accessMask=1, 
					unsigned int busType=XL_BUS_TYPE_CAN, 
					unsigned int flags=XL_ACTIVATE_RESET_CLOCK);
XLstatus   xlDeactivateChannel ( XLportHandle portHandle=0, XLaccess accessMask=1);
/*
 * event = s_xl_event()
 * status,eventCount= xlReceive(portHandle,1,event)
 */
XLstatus   xlReceive ( XLportHandle portHandle, 
					unsigned int *pEventCount /In,Out/, 
					XLevent *pEvents /In/);

XLstringType   xlGetEventString( XLevent *pEv /In/);
XLstringType   xlGetErrorString( XLstatus err );

XLaccess   xlGetChannelMask(
  int hwType = XL_HWTYPE_CANCASEXL,
  int hwIndex = 0,
  int hwChannel = 0
);

XLstatus   xlGetDriverConfig (XLdriverConfig *pDriverConfig /In,Out/);

XLstatus   xlCanSetChannelTransceiver ( XLportHandle portHandle, 
						XLaccess accessMask,
						int type, 
						int lineMode, 
						int resNet=0);

XLstatus   xlCanSetChannelOutput ( XLportHandle portHandle, XLaccess accessMask, int mode);

XLstatus   xlCanTransmitEx ( XLportHandle portHandle, 
							XLaccess accessMask, 
							unsigned int msgCnt, 
							unsigned int* pMsgCntSent, 
							XLcanTxEvent* pXlCanTxEvt);

XLstatus   xlCanTransmit ( XLportHandle portHandle, XLaccess accessMask, 
				unsigned int *pEventCount /In/, 
				XLevent /*void*/ *pEvents /In/);


XLaccess   xlGetChannelMask(
  int hwType,
  int hwIndex,
  int hwChannel
);

XLstatus   xlGetApplConfig ( char *appName, 
		unsigned int appChannel, 
		unsigned int *pHwType, 
		unsigned int *pHwIndex, 
		unsigned int *pHwChannel, 
		unsigned int busType=XL_BUS_TYPE_CAN );

XLstatus   xlSetApplConfig ( char *appName, 
					unsigned int appChannel, 
					unsigned int hwType=XL_HWTYPE_CANCASEXL, 
					unsigned int hwIndex=0, 
					unsigned int hwChannel=0, 
					unsigned int busType=XL_BUS_TYPE_CAN );



