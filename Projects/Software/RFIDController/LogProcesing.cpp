#include "LogProcesing.h"
#include "LogInfo.h"
#include "IDInfo.h"

bool LogProcesing::save(std::string id, std::string name, std::string secondname)
{
	date = a.getDate();
	time = a.getTime();

	folder = std::to_string(date.mon);
	folder += ".";
	folder += std::to_string(date.year);


	date2 = std::to_string(date.day);
	date2 += "/";
	date2 += std::to_string(date.mon);
	date2 += "/";
	date2 += std::to_string(date.year);

	time2 = std::to_string(time.hour);
	time2 += "/";
	time2 += std::to_string(time.min);
	time2 += "/";
	time2 += std::to_string(time.sec);


	CreateDirectory(folder.c_str(), NULL);


	FileName = std::to_string(date.day);
	FileName += ".";
	FileName += std::to_string(date.mon);

	LogInfo file(folder + "\\" + FileName + ".txt");

	if (file.save(date2, time2, id, name, secondname )) {
		return true;
	}
	return false;
}
