#ifdef USE_SG
#include "Sg.h"
#include <time.h>
#if !defined(__WINDOWS__) && !defined(__LINUX__)
time_t __weak time(time_t *result)
{
	return 0;
}
struct tm* __weak localtime(const time_t* t)
{
	static struct tm lt;
	lt.tm_hour = 8;

	return &lt;
}
#endif
void* RefreshPointerHour(SgWidget* w)
{
	time_t t = time(0);
	struct tm* lt = localtime(&t);

	if(lt->tm_hour < 3)
	{
		w->d = 360 - (3-lt->tm_hour)*30;
	}
	else
	{
		w->d = (lt->tm_hour-3)*30;
	}

	w->d += lt->tm_min*30/60;

	return 0;
}

void* RefreshPointerMinute(SgWidget* w)
{
	time_t t = time(0);
	struct tm* lt = localtime(&t);

	if(lt->tm_min < 15)
	{
		w->d = 360 - (15 - lt->tm_min)*6;
	}
	else
	{
		w->d = (lt->tm_min-15)*6;
	}

	w->d += lt->tm_sec*6/60;

	return 0;
}

void* RefresPointerSecond(SgWidget* w)
{
	time_t t = time(0);
	struct tm* lt = localtime(&t);

	if(lt->tm_sec < 15)
	{
		w->d = 360 - (15 -lt->tm_sec)*6;
	}
	else
	{
		w->d = (lt->tm_sec-15)*6;
	}

	return 0;
}

void* RefreshDate(SgWidget* w)
{
	uint8 temp;
	int year;
	static uint16 Text[] = {11,'2','0','1','5',0x5E74,'0','3',0x6708,'2','9',0x65e5,0};

	w->c = 1;

	time_t t = time(0);
	struct tm* lt = localtime(&t);

	year = 1900 + lt->tm_year;
	temp = (year/1000)%10;
	Text[1] = '0' + temp;
	temp = (year/100)%10;
	Text[2] = '0' + temp;
	temp = (year/10)%10;
	Text[3] = '0' + temp;
	temp = (year)%10;
	Text[4] = '0' + temp;

	temp = (lt->tm_mon/10)%10;
	Text[6] = '0' + temp;
	temp = (lt->tm_mon)%10;
	Text[7] = '1' + temp;

	temp = (lt->tm_mday/10)%10;
	Text[9] = '0' + temp;
	temp = (lt->tm_mday)%10;
	Text[10] = '0' + temp;



	return Text;
}
#endif
