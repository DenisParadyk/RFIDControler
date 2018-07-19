#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <time.h>
#include "RTC.h"
#include "TTY.h"
#include <vector>

using namespace std;

class RFID
{
public:
	RFID(int port);
	string  runID();

private:
	TTY tty;
};