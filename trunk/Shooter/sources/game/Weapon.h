#ifndef _WEAPON_H_
#define _WEAPON_H_


//base class for weapon
class Weapon
{
	
public:

	Weapon(unsigned int nb_balles, unsigned int capacite_chargeur);
	~Weapon();


	//nombre de chargeurs non vides
	unsigned int GetNbChargeur();

	//nombre de balles dans le chargeur en cours
	unsigned int GetNbBallesDansChargeur();

	//nombre de balles
	unsigned int GetNbBalles();

	//décompte une balle
	void Tire();

	//reload
	void Reload();

private:

	unsigned int _capacite_chargeur;
	unsigned int _nb_balles;

	unsigned int _nbBallesChargeur;
};

#endif //_WEAPON_H_

