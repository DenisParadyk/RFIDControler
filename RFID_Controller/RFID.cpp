#include "RFID.h"
#include "TTY.h" 

RFID::RFID(int port)
{
	tty.Connect("COM" + to_string(port), 9600);
}

string RFID::runID() {

	string id;

	std::vector<unsigned char> the_vectsor;;
	tty.Read(the_vectsor, 50);

	for (int i = 0; i < the_vectsor.size(); i++) {
		std::cout << (char)(the_vectsor[i]);
	}

	for (int i = 0; i < the_vectsor.size(); i++) {
		std::cout << to_string(the_vectsor[i]) << "  ";
	}
	if (the_vectsor.size() >= 14) {
		if (the_vectsor[0] == 0x02 && the_vectsor[13] == 0x03) {
			the_vectsor[13] = 0;
			id = (char*)&the_vectsor[1];
		}
	}
	return id;
}