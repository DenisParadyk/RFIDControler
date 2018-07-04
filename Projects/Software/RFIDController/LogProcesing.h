#ifndef _LOGPROCESING_
#define _LOGPROCESING_

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <time.h>
#include "RTC.h"
#include "LogInfo.h"
#include <windows.h>

class LogProcesing {

public:
	
    bool save(std::string id, std::string name, std::string secondname);
private:

    RTC a;
    RtcDate date;
    RtcTime time;
    std::string date2;
    std::string time2;
    std::string id;
    std::string folder;
    std::string FileName;
};

#endif#
