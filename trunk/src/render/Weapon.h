#ifndef _WEAPON_H_
#define _WEAPON_H_

#include <osg/PositionAttitudeTransform>


class Weapon : public osg::PositionAttitudeTransform
{

public:

	Weapon(unsigned int nb_balles, unsigned int capacite_chargeur);
	~Weapon();


	//nombre de chargeurs non vides
	unsigned int GetNbChargeur();

	//nombre de balles dans le chargeur en cours
	unsigned int GetNbBallesDansChageur();

	//décompte une balle
	void Tire();


	bool LoadModel(std::string filename);	

private:

	unsigned int _capacite_chargeur;
	unsigned int _nb_balles;

};

#endif //_WEAPON_H_
