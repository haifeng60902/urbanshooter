#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <string>

class Settings
{
public:
	Settings(const std::string & configFilePath);
	~Settings();

	int screenNum;
};

#endif //_SETTINGS_H_

