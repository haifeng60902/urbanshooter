#include <render/WeaponManager.h>

#include <render/WeaponHandler.h>

WeaponManager::WeaponManager()
{
	_weapon = NULL;
}

WeaponManager::~WeaponManager()
{
}

void WeaponManager::setHandler(WeaponHandler* wh)
{
	_wh = wh;
}



void WeaponManager::Tire()
{
	if(_weapon->GetNbBalles() > 0)
		_weapon->Tire();

}
