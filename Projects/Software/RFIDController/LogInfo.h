#ifndef _LOGINFO_
#define _LOGINFO_

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <time.h>
 
using std::cout;
using std::endl;

class LogInfo {

public:
	LogInfo(std::string fileName);
	bool save(std::string date2, std::string time2, std::string id, std::string name , std::string secondname);
private:
	std::string m_fileName;
};

#endif