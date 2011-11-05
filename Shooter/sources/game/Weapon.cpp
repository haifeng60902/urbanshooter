#include <game/Weapon.h>
#include <iostream>

Weapon::Weapon(unsigned int nb_balles, unsigned int capacite_chargeur)
{
	_capacite_chargeur = capacite_chargeur;
	_nb_balles = nb_balles;
	_nbBallesChargeur = capacite_chargeur;
}


Weapon::~Weapon()
{
}


unsigned int Weapon::GetNbChargeur()
{
	return _nb_balles/_capacite_chargeur + 1;
}


unsigned int Weapon::GetNbBallesDansChargeur()
{
	return _nbBallesChargeur;
}

unsigned int Weapon::GetNbBalles()
{
	return _nb_balles;
}


void Weapon::Tire()
{
	_nb_balles--;
	_nbBallesChargeur--;

	std::cout << "Reste " << GetNbBalles() << " dans " << GetNbChargeur() << " chargeurs" << std::endl;

}

void Weapon::Reload()
{
	if(_nb_balles > _capacite_chargeur)
		_nbBallesChargeur = _capacite_chargeur;
	else
		_nbBallesChargeur = _nb_balles;
}