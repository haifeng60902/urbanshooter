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

	_graphicEngine->setSettings(_settings);
	_gameEngine->setSettings(_settings);
	_soundEngine->setSettings(_settings);


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

void GameManager::initialize()
{
	_gameEngine->initialize();
	_soundEngine->initialize();
	_graphicEngine->initialize();
}

void GameManager::run()
{
	while(_gameEngine->isValid() && _graphicEngine->isValid() && _soundEngine->isValid())
		frame();
}

void GameManager::frame()
{
	//frame each engine
	_gameEngine->frame();
	_soundEngine->frame();
	_graphicEngine->frame();

}