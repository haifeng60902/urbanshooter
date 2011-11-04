#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include <config/Settings.h>

class GameManager
{
public:

	GameManager(const std::string & configFilePath);
	~GameManager();

private:

	Settings * _settings;

	
};


#endif //_GAME_MANAGER_H_
