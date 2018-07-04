#include "LogInfo.h"

LogInfo::LogInfo(std::string fileName)
{
    m_fileName = fileName;
}

bool LogInfo::save(std::string date2, std::string time2, std::string id,  std::string name , std::string secondname)
{

	std::ofstream l_file;
	l_file.open(m_fileName, std::ios_base::app);
	if (l_file.is_open()) {
		l_file << date2 << " " << time2 << " " << id << " " << name << " " << secondname << endl;
		l_file.close();
		return true;
	}
	return false;
}
