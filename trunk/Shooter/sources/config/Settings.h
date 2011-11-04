#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <string>

class Settings
{
public:
	Settings(const std::string & configFilePath);
	~Settings();

	int screenNum;
	bool enableEventHandler;
	double viewFinderRed;
	double viewFinderGreen;
	double viewFinderBlue;
	double viewFinderWidth;
};

#endif //_SETTINGS_H_

