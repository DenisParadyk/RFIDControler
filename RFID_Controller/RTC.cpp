#include "RTC.h"

RtcDate RTC::getDate()
{
#ifndef LINUX
    errno_t error;
	tm a;
	time_t now = time(0);
	error = localtime_s(&a, &now);
	RtcDate date;
	date.year = a.tm_year + 1900;
	date.mon = a.tm_mon + 1;
	date.day = a.tm_mday;
    return date;
#else
    time_t now = time(0);
    tm *ltm = localtime(&now);
    RtcDate date;
    date.day = ltm->tm_mday;
    date.mon = 1 + ltm->tm_mon;
    date.year = 1900 + ltm->tm_year;

    return date;
#endif
}

RtcTime RTC::getTime()
{
#ifndef LINUX
	errno_t error;
	tm a;
	time_t now = time(0);
	error = localtime_s(&a, &now);
	RtcTime time;
	time.hour = a.tm_hour;
    time.min  = a.tm_min;
    time.sec  = a.tm_sec;
    return time;
#else
    time_t now = time(0);
    tm *ltm = localtime(&now);
    RtcTime time;
    time.hour = ltm->tm_hour;
    time.min  = ltm->tm_min;
    time.sec  = ltm->tm_sec;

    return time;
#endif
}
