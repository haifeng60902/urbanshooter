#include <game/GameEngine.h>

#include <sound/SoundEngine.h>

#include <graphic/GraphicEngine.h>

#include <game/WeaponManager.h>
#include <game/TargetManager.h>
#include <game/Sniper.h>
#include <game/Score.h>

GameEngine::GameEngine()
{
	_weaponManager = new WeaponManager();
	_targetManager = new TargetManager();
	_score = new Score();
}


GameEngine::~GameEngine()
{
	delete _weaponManager;
	delete _targetManager;
	delete _score;
}

void GameEngine::frame()
{

	//update the hud
	getGraphicEngine()->setBulletNum(_weaponManager->getActiveWeapon()->GetNbBalles());
	getGraphicEngine()->setScore(_score->get());
	getGraphicEngine()->setRemainingTime(0);

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
	
	//init the bullet hud
	getGraphicEngine()->setBulletNum(_weaponManager->getActiveWeapon()->GetNbBalles());

}

void GameEngine::onLeftClic(osgUtil::LineSegmentIntersector::Intersection intersection)
{
	//make the weapon fire
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


	//get the result
	TargetManager::ShootResult sres = _targetManager->Intersect(intersection);

	switch(sres)
	{
		case TargetManager::TARGET_WRONG :
			_score->addWrongShoot();
			break;

		case TargetManager::TARGET_MISSED :
			_score->addVoidShoot();
			break;

		case TargetManager::TARGET_REACHED :
			_score->addTargetShoot();
			break;
	}

}