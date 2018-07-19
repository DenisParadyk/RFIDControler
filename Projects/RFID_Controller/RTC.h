#ifndef _RTC_
#define _RTC_

#include <iostream>
#include <cstdlib>
#include <string>
#include <time.h>

struct RtcDate
{
	int year;
	int mon;
	int day;
};

struct RtcTime
{
	int hour;
	int min;
	int sec;
};

class RTC
{
public:
	RtcDate getDate();
	RtcTime getTime();
};

#endif