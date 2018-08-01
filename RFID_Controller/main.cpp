#include <cstdlib>
#include <iostream>
#include "RFID.h"
#include "TTY.h" 
#include "RTC.h"
#include "Db.h"
using namespace std;

int main() {
	int port;
	setlocale(0, "");
	std::string id;
	std::string name;
	Db db("RFIDControler.db");
	std::string secondname;
	std::string newName;
	std::string newSecondname;
	std::string date;
	std::string time;
	RtcDate dt;
	RtcTime tm;
	RTC rtc;
	
	cout << "Enter COMport" << endl;
	cin >> port;
	RFID a(port);

	db.open();
	db.create();

	while (1) {
		id = a.runID();

		dt = rtc.getDate();
		tm = rtc.getTime();

		date = to_string(dt.day);
		date += " : ";
		date += to_string(dt.mon);
		date += " : ";
		date += to_string(dt.year);

		time = to_string(tm.hour);
		time += " : ";
		time += to_string(tm.min);
		time += " : ";
		time += to_string(tm.sec);

		name.erase();
		secondname.erase();

		if (id.length() != 0) {
			db.select(id, name, secondname);
			if (name.length() == 0 || secondname.length() == 0) {
				cout << "Enter new name" << endl;
				cin >> newName;
				cout << "Enter new secondname" << endl;
				cin >> newSecondname;
				name = newName;
				secondname = newSecondname;
			    db.subFunc(id, name, secondname);
			} else {
				db.mainFunc(name, secondname, date, time);
			}
		}
	}
	return 0;
}
