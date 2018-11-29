
#include "Nm.h"
#include "CanNm.h"
#include "ComM.h"

const Nm_ChannelType Nm_Channels[] = {
	{
		.BusType =  NM_BUSNM_CANNM,
		.BusNmNetworkHandle =  CANNM_CHANNEL_LS,
		.ComMNetworkHandle =  COMM_CHL_LS,
	},
#if (MM_CHL_COUNT == 2)
	{
		.BusType =  NM_BUSNM_CANNM,
		.BusNmNetworkHandle =  CANNM_CHANNEL_HS,
		.ComMNetworkHandle =  COMM_CHL_HS,
	}
#endif
};

const Nm_ConfigType Nm_Config = 
{
	.Channels =  Nm_Channels
};

