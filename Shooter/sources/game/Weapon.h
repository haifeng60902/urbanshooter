#ifndef _WEAPON_H_
#define _WEAPON_H_

#include <string>

//base class for weapon
class Weapon
{
	
public:

	Weapon(std::string filename, unsigned int nb_balles, unsigned int capacite_chargeur);
	~Weapon();


	std::string getFileName();

	//nombre de chargeurs non vides
	unsigned int GetNbChargeur();

	//nombre de balles dans le chargeur en cours
	unsigned int GetNbBallesDansChargeur();

	//nombre de balles
	unsigned int GetNbBalles();

	unsigned int GetCapaciteChargeur(){ return _capacite_chargeur; }

	//décompte une balle
	void Tire();

	//reload
	void Reload();

private:

	unsigned int _capacite_chargeur;
	unsigned int _nb_balles;

	unsigned int _nbBallesChargeur;

	std::string _fileName;

};

#endif //_WEAPON_H_

