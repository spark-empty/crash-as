#ifdef USE_SG
#include "Sg.h"
#include "Stmo.h"
#include "Dio.h"

#define TT_ON  1
#define TT_OFF SGL_INVALID

#define TT_DEFAULT_HANDLE(name)			\
void CacheTelltale##name(SgWidget* w)	\
{										\
										\
	if(STD_HIGH == Dio_ReadChannel(DIO_CHL_Telltale##name)) \
	{									\
		w->l = TT_ON;					\
	}									\
	else								\
	{									\
		w->l = TT_OFF;					\
	}									\
}										\
void* RefreshTelltale##name(SgWidget* w) { return 0; }

extern int AsWsjOnline(void);

void CacheClusterTachoPointer(SgWidget* w){}
void* RefreshClusterTachoPointer(SgWidget* w)
{
	Stmo_DegreeType degree;

	Stmo_GetPosDegree(STMO_ID_TACHO,&degree);

	if(!AsWsjOnline())
	{
		w->d = (degree/STMO_ONE_DEGREE)%360;
	}
	else
	{
		w->d = degree;
	}

	return 0;
}


void CacheClusterSpeedPointer(SgWidget* w){}
void* RefreshClusterSpeedPointer(SgWidget* w)
{
	Stmo_DegreeType degree;

	Stmo_GetPosDegree(STMO_ID_SPEED,&degree);

	if(!AsWsjOnline())
	{
		w->d = (degree/STMO_ONE_DEGREE)%360;
	}
	else
	{
		w->d = degree;
	}

	return 0;
}

void CacheClusterTempPointer(SgWidget* w){}
void* RefreshClusterTempPointer(SgWidget* w)
{

	Stmo_DegreeType degree;

	Stmo_GetPosDegree(STMO_ID_TEMP,&degree);

	if(!AsWsjOnline())
	{
		w->d = (degree/STMO_ONE_DEGREE)%360;
	}
	else
	{
		w->d = degree;
	}

	return 0;
}

void CacheClusterFuelPointer(SgWidget* w){}
void* RefreshClusterFuelPointer(SgWidget* w)
{

	Stmo_DegreeType degree;

	Stmo_GetPosDegree(STMO_ID_FUEL,&degree);

	if(!AsWsjOnline())
	{
		w->d = (degree/STMO_ONE_DEGREE)%360;
	}
	else
	{
		w->d = degree;
	}

	return 0;
}

TT_DEFAULT_HANDLE(TPMS)
TT_DEFAULT_HANDLE(LowOil)
TT_DEFAULT_HANDLE(PosLamp)
TT_DEFAULT_HANDLE(TurnLeft)
TT_DEFAULT_HANDLE(TurnRight)
TT_DEFAULT_HANDLE(AutoCruise)
TT_DEFAULT_HANDLE(HighBeam)
TT_DEFAULT_HANDLE(SeatbeltDriver)
TT_DEFAULT_HANDLE(SeatbeltPassenger)
TT_DEFAULT_HANDLE(Airbag)
#endif /* widget_refresh.c */
