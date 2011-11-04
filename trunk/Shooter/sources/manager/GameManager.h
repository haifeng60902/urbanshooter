#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include <config/Settings.h>

class GraphicEngine;
class GameEngine;
class SoundEngine;

class GameManager
{
public:

	GameManager(const std::string & configFilePath);
	~GameManager();

	void run();

private:

	void frame();

	Settings * _settings;

	
	GraphicEngine * _graphicEngine;
	GameEngine *	_gameEngine;
	SoundEngine *	_soundEngine;
};


#endif //_GAME_MANAGER_H_
