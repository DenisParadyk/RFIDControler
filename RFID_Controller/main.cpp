#include <cstdlib>
#include <iostream>
#include "RFID.h"
#include "TTY.h" 
#include "RTC.h"
#include "Db.h"
#include "Sounds.h"
#include "TCPClient.h"
#include "Security.h"

using namespace std;

int main() {

	int port;
    setlocale(0, "");
    std::string id;
	std::string name;
    std::string secondname;
    std::string newName;
    std::string newSecondname;
    std::string date;
    std::string time;
    std::string login;
    std::string password;
    std::string newLogin;
    std::string newPassword;
    Security valid_pass;
    Sounds beep;
    RtcDate dt;
    RtcTime tm;
    RTC rtc;

    port = 0;
    RFID a(port);

    Db db("RFIDControler.db");
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

            beep.playActivate();

            db.select(id, name, secondname, login, password);

            if (name.length() == 0  ) {

                beep.playNotFound();
                cout << "New user detected\n" << "Enter LogIn : ";
                cin >> newLogin;
                cout << "Enter new password : ";
                cin >> newPassword;
                cout << endl;
                cout << "Enter new name : ";
				cin >> newName;
                cout << endl;
                cout << "Enter new secondname : ";
				cin >> newSecondname;
                cout << endl;
				name = newName;
				secondname = newSecondname;
                login = newLogin;
                password = newPassword;

                beep.playNewCard();
                db.subFunc(id, name, secondname, login, password);

            } else {

                cout << " Enter LogIn : ";
                cin >> login;
                cout << endl;

                beep.playOpen();

                valid_pass.check_pass(password);
                db.mainFunc(name, secondname, date, time);
			}
		}
	}
	return 0;
}
