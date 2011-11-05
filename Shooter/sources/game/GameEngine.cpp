#include <game/GameEngine.h>

#include <sound/SoundEngine.h>

#include <graphic/GraphicEngine.h>

#include <game/WeaponManager.h>
#include <game/TargetManager.h>
#include <game/Sniper.h>

GameEngine::GameEngine()
{
	_weaponManager = new WeaponManager();
	_targetManager = new TargetManager();
}


GameEngine::~GameEngine()
{
	delete _weaponManager;
	delete _targetManager;
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

void GameEngine::onLeftClic(osgUtil::LineSegmentIntersector::Intersection intersection)
{
	WeaponManager::WeaponMode wmode = _weaponManager->Fire();

	switch(wmode)
	{
		case WeaponManager::WEAPON_SHOOT :
			getSoundEngine()->playFire();
			break;

		case WeaponManager::WEAPON_RELOAD :
			getSoundEngine()->playReload();
			break;

		case WeaponManager::WEAPON_EMPTY :
			getSoundEngine()->playEmpty();
			break;

		case WeaponManager::WEAPON_ERROR :
			break;
	}


	_targetManager->Intersect(intersection);


}