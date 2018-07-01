#include <cstdlib>
#include <iostream>
#include <windows.h>
#include "RFID.h"
#include "LogProcesing.h"
#include "TTY.h" 
#include "RTC.h"
#include "LogInfo.h"
#include "IDInfo.h"


int main() {
    int port;
	LogProcesing b;
	std::string id;
	std::string name;
	std::string secondname;

	CreateDirectory("Id_Names", NULL);
	IDInfo file("Id_Names\\ID.txt");
	

    cout << "Enter port" << endl;
    cin >> port;
    RFID a(port);
    while (1) {
        id = a.runID();
        if (id.length() != 0) {
            Sleep(1000);
            b.save(id);
			file.saveInfo(id, name, secondname);
        }
    }
    system("pause");

    return 0;
}