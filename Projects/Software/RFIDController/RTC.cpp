#include "RTC.h"

RtcDate RTC::getDate()
{
    errno_t error;
    tm a;
    time_t now = time(0);
    error = localtime_s(&a, &now);
    RtcDate date;
    date.year = a.tm_year + 1900;
    date.mon = a.tm_mon + 1;
    date.day = a.tm_mday;

    return date;
}

RtcTime RTC::getTime()
{
    errno_t error;
    tm a;
    time_t now = time(0);
    error = localtime_s(&a, &now);
    RtcTime time;
    time.hour = a.tm_hour;
    time.min = a.tm_min;
    time.sec = a.tm_sec;

    return time;
}
