#include <manager/GameManager.h>

#include <string>

GameManager::GameManager(const std::string & configFilePath)
{
	_settings = new Settings(configFilePath);
}

GameManager::~GameManager()
{

	delete _settings;
}
