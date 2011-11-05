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


void WeaponManager::Fire()
{
	if(!_activeWeapon)
		return;

	//try to shoot
	if(!Shoot())
	{
		//try to reload automatically
		if(!Reload())
		{
			//empty weapon
			//TODO: display empty on HUD
			std::cout << "Empty weapon" << std::endl;

		}
	}
}

bool WeaponManager::Shoot()
{
	//shoot only if chargeur is not empty
	if(_activeWeapon->GetNbBallesDansChargeur() > 0)
	{
		_activeWeapon->Tire();

		//TODO:play sound
		//TODO:play graphical shoot and animation

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

		//TODO:play sound
		//TODO:play graphical reload animation
		std::cout << "Reload" << std::endl;
		
		return true;
	}
	else
		return false;
}