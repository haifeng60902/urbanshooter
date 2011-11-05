#include <game/GameEngine.h>

#include <graphic/GraphicEngine.h>

#include <game/WeaponManager.h>
#include <game/Sniper.h>

GameEngine::GameEngine()
{
	_weaponManager = new WeaponManager();

}


GameEngine::~GameEngine()
{
	delete _weaponManager;
}

void GameEngine::frame()
{
}

bool GameEngine::isValid()
{
	return true;
}

void GameEngine::initialize()
{
	// add a default weapon
	Sniper * s = new Sniper();
	_weaponManager->setActiveWeapon( s );
	getGraphicEngine()->setActiveWeapon( s );
	
}

void GameEngine::onLeftClic()
{
	_weaponManager->Fire();
}