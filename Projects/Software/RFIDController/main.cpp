#include <cstdlib>
#include <iostream>
#include "RFID.h"
#include "LogProcesing.h"
#include "TTY.h" 
#include "RTC.h"
#include "LogInfo.h"

using std::cout;
using std::endl;


int main() {
	int port;
	cout << "Enter port" << endl;
	cin >> port;
	RFID a(port);
	LogProcesing b;
	std::string id;
	while (1) {
		id = a.runID();
		if (id.length() != 0) {
			Sleep(1000);
			b.save(id);
		}
	}
    system("pause");

	return 0;
}