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
	setlocale(0, "");
	LogProcesing b;
	std::string id;
	std::string name;
	std::string secondname;
	std::string newName;
	std::string newSecondname;
	IDInfo file("ID.txt");

	cout << "Enter port" << endl;
	cin >> port;
	RFID a(port);
	while (1) {
		id = a.runID();
		Sleep(1000);
 
		name.erase();
		secondname.erase();
		file.readInfo(id, name, secondname);
		if (id.length() != 0) {
			Sleep(1000);
			if (name.length() == 0) {
				cout << "Enter new name" << endl;
				cin >> newName;
				cout << "Enter new secondname" << endl;
				cin >> newSecondname;
				name = newName;
				secondname = newSecondname;
				cout << name << " " << secondname << endl;
				file.saveInfo(id, name, secondname);
			}
			else {
				b.save(id, name, secondname);
			}
			
		}
	}


	system("pause");

	return 0;
}

/*
int main() {
    int port;
	LogProcesing b;
	std::string id;
	std::string name;
	std::string secondname;
	IDInfo file("Id_Names\\ID.txt");

	CreateDirectory("Id_Names", NULL);

    cout << "Enter port" << endl;
    cin >> port;
    RFID a(port);
    while (1) {
        id = a.runID();
		if (id.length() != 0) {
			Sleep(1000);
			b.save(id);
			file.readInfo(id, name, secondname);
		}
		//file.saveInfo(id, name, secondname);
    }
	

    system("pause");

    return 0;
}*/