#include <game/WeaponManager.h>
#include <iostream>

#include <game/Weapon.h>


WeaponManager::WeaponManager()
{
	_activeWeapon = NULL;
}

WeaponManager::~WeaponManager()
{
	delete _activeWeapon;
}


WeaponManager::WeaponMode WeaponManager::Fire()
{
	if(!_activeWeapon)
		return WEAPON_ERROR;

	//try to shoot
	if(!Shoot())
	{
		//try to reload automatically
		if(!Reload())
		{
			//empty weapon
			//TODO: display empty on HUD
			std::cout << "Empty weapon" << std::endl;
			return WEAPON_EMPTY;
		}
		else
			return WEAPON_RELOAD;
	}
	else
		return WEAPON_SHOOT;
}

bool WeaponManager::Shoot()
{
	//shoot only if chargeur is not empty
	if(_activeWeapon->GetNbBallesDansChargeur() > 0)
	{
		_activeWeapon->Tire();

		std::cout << "Shoot" << std::endl;
		
		return true;
	}
	else
		return false;
}

bool WeaponManager::Reload()
{
	if(_activeWeapon->GetNbBalles() > 0)
	{
		_activeWeapon->Reload();

		std::cout << "Reload" << std::endl;
		
		return true;
	}
	else
		return false;
}