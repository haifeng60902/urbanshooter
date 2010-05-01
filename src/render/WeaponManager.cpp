#include <WeaponManager.h>

#include <WeaponHandler.h>

WeaponManager::WeaponManager()
{
	_weapon = NULL;
}

WeaponManager::~WeaponManager()
{
}


void WeaponManager::Tire()
{
	if(_weapon->GetNbBalles() > 0)
		_weapon->Tire();

}
