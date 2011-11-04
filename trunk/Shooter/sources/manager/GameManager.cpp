#include <manager/GameManager.h>

#include <string>

#include <game/GameEngine.h>
#include <graphic/GraphicEngine.h>
#include <sound/SoundEngine.h>

GameManager::GameManager(const std::string & configFilePath)
{
	_settings = new Settings(configFilePath);

	_graphicEngine	= new GraphicEngine();
	_gameEngine		= new GameEngine();
	_soundEngine	= new SoundEngine();


	_graphicEngine->setGameEngine(_gameEngine);
	_graphicEngine->setSoundEngine(_soundEngine);

	_gameEngine->setGraphicEngine(_graphicEngine);
	_gameEngine->setSoundEngine(_soundEngine);

	_soundEngine->setGameEngine(_gameEngine);
	_soundEngine->setGraphicEngine(_graphicEngine);

}

GameManager::~GameManager()
{

	delete _settings;

	delete _gameEngine;
	delete _soundEngine;
	delete _graphicEngine;
}


void GameManager::run()
{
	while(NULL) //graphic engine : valid (all engines, when one die, all are killed)
		frame();
}

void GameManager::frame()
{
	//frame each engine

}