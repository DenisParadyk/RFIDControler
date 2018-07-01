#pragma once

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <time.h>
#include "RTC.h"
#include "LogInfo.h"
#include "TTY.h"
#include <windows.h>

using namespace std;

class RFID {
public:
    RFID(int port);
	string  runID();

private:

	

	TTY tty;
};