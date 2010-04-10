#include <Weapon.h>

#include <osgDB/ReadFile>

Weapon::Weapon(unsigned int nb_balles, unsigned int capacite_chargeur)
{
	_capacite_chargeur = capacite_chargeur;
	_nb_balles = nb_balles;
}


Weapon::~Weapon()
{
}


unsigned int Weapon::GetNbChargeur()
{
	return _nb_balles/_capacite_chargeur + 1;
}


unsigned int Weapon::GetNbBallesDansChageur()
{
	return _nb_balles % _capacite_chargeur;
}


void Weapon::Tire()
{
	_nb_balles--;
}


bool Weapon::LoadModel(std::string filename)
{
	osg::ref_ptr< osg::Node > model = osgDB::readNodeFile(filename);
	
	if(model.valid())
		return this->addChild(model);
	else
		return false;
}