#ifndef _WEAPON_MANAGER_H_
#define _WEAPON_MANAGER_H_

class Weapon;

//manage the weapons
class WeaponManager
{
public :
	WeaponManager();
	~WeaponManager();


	inline void setActiveWeapon(Weapon * w){ _activeWeapon = w;}
	Weapon* getActiveWeapon(){ return _activeWeapon; }

	enum WeaponMode { WEAPON_SHOOT, WEAPON_RELOAD, WEAPON_EMPTY, WEAPON_ERROR };

	//from here manage the graphical and other stuffs
	WeaponMode Fire();


private:

	//if no shoot, if no relaod, empty weapon
	bool Shoot();
	bool Reload();
	

	Weapon * _activeWeapon;

};

#endif //_WEAPON_MANAGER_H_
